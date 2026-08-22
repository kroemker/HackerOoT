/**
 * @file z_morph.c
 *
 * HackerOoT: vertex-level morphing for player transformations.
 *
 * A morph mutates the `Vtx` data of a transformation actor's mesh in place. This is possible
 * because transformation objects are loaded into the dedicated transform object space (see
 * `Object_LoadTransform`), which is a plain RAM buffer: the modified vertices are picked up by the
 * normal `SkelAnime` draw path with no extra draw code.
 *
 * The "other side" of a morph is a `MorphSnapshot`: a point cloud of posed world-space vertex
 * positions stored relative to an anchor point. Transforming in unfolds the creature's vertices
 * from their nearest snapshot points to their true positions; transforming back collapses them
 * onto the snapshot before the actual model swap happens (masked by a short screen flash).
 *
 * Both poses are frozen for the morph duration, so the lerp endpoints are computed once in
 * limb-local space (`Morph_Begin`) and each frame is just an eased s16 lerp (`Morph_Update`).
 *
 * The player side requests morphs (`Morph_RequestUnfold`/`Morph_RequestCollapse`); the creature
 * consumes the requests from its own Init/Update (`Morph_TryBeginUnfold`/`Morph_TryBeginCollapse`)
 * because only it knows its `SkelAnime`. Any code path that abandons a morph must call
 * `Morph_Restore` so the transform space never caches a warped mesh (`Object_LoadTransform` skips
 * the re-DMA when the same object is requested again).
 */
#include "morph.h"

#if TRANSFORM_USE_MORPH

#include "actor.h"
#include "play_state.h"
#include "player.h"
#include "object.h"
#include "sys_matrix.h"
#include "segmented_address.h"
#include "array_count.h"
#include "printf.h"
#include "rand.h"
#include "effect.h"

typedef struct MorphVertex {
    Vtx* vtx;      // vertex in the transform object space
    Vec3s origPos; // authored limb-local position
    Vec3s altPos;  // collapsed limb-local position (on the snapshot shape)
    u8 hasNormal;  // true if this vertex was loaded while G_LIGHTING was active (n/a otherwise)
    s8 origNormal[3];  // authored limb-local normal, only meaningful if hasNormal
    u8 overshootWeight; // 0-255, scales how much unfold overshoot applies (see Morph_Begin)
} MorphVertex;

// One limb with a display list, in draw-recursion order. For flex skeletons this order matches
// the segment 0x0D matrix buffer that `SkelAnime_DrawFlexOpa` fills (one slot per limb whose
// authored dList is non-NULL), so `G_MTX` commands inside the DLs can be resolved against it.
typedef struct MorphFlexEntry {
    MtxF mtx;
    Gfx* dList; // already resolved into the transform space
} MorphFlexEntry;

typedef struct MorphState {
    struct Actor* owner;
    s32 numVerts;
    s32 timer;
    s32 duration;
    MorphDirection direction;
    u8 active;                  // a morph is lerping right now
    u8 meshDirty;               // vertex data differs from origPos
    u8 collapsedHeld;           // a collapse finished; the mesh is held on the snapshot shape
    u8 unfoldRequested;         // consumed by Morph_TryBeginUnfold
    u8 collapseRequested;       // consumed by Morph_TryBeginCollapse
    u8 monsterCaptureRequested; // consumed by Morph_CaptureMonsterSnapshot (run by the creature)
    u8 monsterCaptured;         // the next unfold should use the monster snapshot, not Link's
} MorphState;

static MorphState sMorph;
static MorphVertex sMorphVerts[MORPH_MAX_VERTS];
// Captured at every Link->creature transformation; reused as the collapse target when
// transforming back (Link's body part positions go stale while he is hidden).
static MorphSnapshot sLinkSnapshot;
// Captured from the outgoing creature when switching directly between transformations
static MorphSnapshot sMonsterSnapshot;

// Working state while walking a mesh (Morph_Begin / Morph_CaptureMonsterSnapshot)
static void* sBuildObjectSegment;
static MorphSnapshot* sBuildSnapshot;
static Vec3f sBuildAnchor;
static MtxF sBuildLimbMtx;
static MorphFlexEntry sFlexEntries[MORPH_MAX_FLEX_ENTRIES];
static s32 sNumFlexEntries;
// Display lists an actor's draw callbacks add on top of the limb hierarchy (MORPH_LIMB_ADD, or
// a replacement on a limb without an authored dList); walked after the main entries
static MorphFlexEntry sExtraEntries[16];
static s32 sNumExtraEntries;
static MorphLimbSwap* sBuildSwaps;
static s32 sBuildNumSwaps;
static u8 sBuildCaptureMode; // collect snapshot points instead of morph vertices
static MorphSnapshot* sBuildCaptureTarget;
static u32 sBuildGeometryMode; // tracks G_LIGHTING across the DL walk, see Morph_CollectDListVertices
static u8 sTruncationWarned; // one-shot warning per walk if MORPH_MAX_VERTS/MORPH_SNAPSHOT_MAX_POINTS is hit

// Uniform grid over the snapshot points to accelerate the nearest-point search in Morph_Begin
#define MORPH_GRID_DIM 8
#define MORPH_GRID_CELLS (MORPH_GRID_DIM * MORPH_GRID_DIM * MORPH_GRID_DIM)
static u16 sGridCellStart[MORPH_GRID_CELLS + 1];
static u16 sGridPointIndex[MORPH_SNAPSHOT_MAX_POINTS];
static Vec3f sGridMin;
static Vec3f sGridCellSize;
static u8 sGridValid;

void Morph_Reset(void) {
    sMorph.owner = NULL;
    sMorph.numVerts = 0;
    sMorph.active = false;
    sMorph.meshDirty = false;
    sMorph.collapsedHeld = false;
    sMorph.unfoldRequested = false;
    sMorph.collapseRequested = false;
    sMorph.monsterCaptureRequested = false;
    sMorph.monsterCaptured = false;
    sLinkSnapshot.numPoints = 0;
    sMonsterSnapshot.numPoints = 0;
}

void Morph_RequestUnfold(void) {
    sMorph.unfoldRequested = true;
    // The unfold source is decided now; a pending capture that never happened is stale
    sMorph.monsterCaptureRequested = false;
}

void Morph_RequestMonsterCapture(void) {
    sMorph.monsterCaptureRequested = true;
}

s32 Morph_MonsterCaptureRequested(void) {
    return sMorph.monsterCaptureRequested;
}

s32 Morph_MonsterCaptureDone(void) {
    return sMorph.monsterCaptured;
}

void Morph_RequestCollapse(void) {
    sMorph.collapseRequested = true;
}

s32 Morph_CollapseRequested(void) {
    return sMorph.collapseRequested;
}

s32 Morph_IsActiveFor(Actor* actor) {
    return sMorph.active && (sMorph.owner == actor);
}

s32 Morph_IsCollapsedFor(Actor* actor) {
    return sMorph.collapsedHeld && (sMorph.owner == actor);
}

s32 Morph_IsBusy(void) {
    return sMorph.active;
}

static void Morph_WalkMesh(struct PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps,
                           s32 numSwaps);
static void Morph_CaptureLinkSnapshotFallback(struct Player* player);

/**
 * Captures Link's current posed shape as a snapshot by walking his authored limb display lists
 * (his `LodLimb`s alias `StandardLimb` for the first dList, and his flex `G_MTX` references are
 * resolved like any other flex skeleton). Falls back to points sampled along his body part
 * "bones" (`bodyPartsPos`) if the mesh walk yields nothing.
 */
void Morph_CaptureLinkSnapshot(PlayState* play, Player* player) {
    sLinkSnapshot.numPoints = 0;
    sMorph.monsterCaptured = false;

    if (player->skelAnime.skeleton != NULL) {
        sBuildCaptureMode = true;
        sBuildCaptureTarget = &sLinkSnapshot;
        Morph_WalkMesh(play, &player->actor, &player->skelAnime, NULL, 0);
        sBuildCaptureMode = false;
    }

    PRINTF("MORPH: captured Link snapshot, %d points\n", sLinkSnapshot.numPoints);

    if (sLinkSnapshot.numPoints > 0) {
        return;
    }

    Morph_CaptureLinkSnapshotFallback(player);
}

/**
 * Fallback Link snapshot: points sampled along his body part "bones" (`bodyPartsPos` holds
 * posed world positions from his last drawn frame).
 */
static void Morph_CaptureLinkSnapshotFallback(Player* player) {
    static u8 sBonePairs[][2] = {
        { PLAYER_BODYPART_WAIST, PLAYER_BODYPART_TORSO },
        { PLAYER_BODYPART_TORSO, PLAYER_BODYPART_COLLAR },
        { PLAYER_BODYPART_COLLAR, PLAYER_BODYPART_HEAD },
        { PLAYER_BODYPART_HEAD, PLAYER_BODYPART_HAT },
        { PLAYER_BODYPART_COLLAR, PLAYER_BODYPART_L_SHOULDER },
        { PLAYER_BODYPART_L_SHOULDER, PLAYER_BODYPART_L_FOREARM },
        { PLAYER_BODYPART_L_FOREARM, PLAYER_BODYPART_L_HAND },
        { PLAYER_BODYPART_COLLAR, PLAYER_BODYPART_R_SHOULDER },
        { PLAYER_BODYPART_R_SHOULDER, PLAYER_BODYPART_R_FOREARM },
        { PLAYER_BODYPART_R_FOREARM, PLAYER_BODYPART_R_HAND },
        { PLAYER_BODYPART_WAIST, PLAYER_BODYPART_L_THIGH },
        { PLAYER_BODYPART_L_THIGH, PLAYER_BODYPART_L_SHIN },
        { PLAYER_BODYPART_L_SHIN, PLAYER_BODYPART_L_FOOT },
        { PLAYER_BODYPART_WAIST, PLAYER_BODYPART_R_THIGH },
        { PLAYER_BODYPART_R_THIGH, PLAYER_BODYPART_R_SHIN },
        { PLAYER_BODYPART_R_SHIN, PLAYER_BODYPART_R_FOOT },
    };
#define MORPH_BONE_SAMPLES 4
    Vec3f anchor = player->actor.world.pos;
    s32 i;
    s32 j;

    sLinkSnapshot.numPoints = 0;
    sMorph.monsterCaptured = false;

    for (i = 0; i < ARRAY_COUNT(sBonePairs); i++) {
        Vec3f* a = &player->bodyPartsPos[sBonePairs[i][0]];
        Vec3f* b = &player->bodyPartsPos[sBonePairs[i][1]];

        for (j = 0; j < MORPH_BONE_SAMPLES; j++) {
            f32 t = (f32)j / (MORPH_BONE_SAMPLES - 1);
            Vec3s* point;

            if (sLinkSnapshot.numPoints >= MORPH_SNAPSHOT_MAX_POINTS) {
                return;
            }
            point = &sLinkSnapshot.points[sLinkSnapshot.numPoints++];
            point->x = (s16)(a->x + (b->x - a->x) * t - anchor.x);
            point->y = (s16)(a->y + (b->y - a->y) * t - anchor.y);
            point->z = (s16)(a->z + (b->z - a->z) * t - anchor.z);
        }
    }
}

/**
 * Transforms `world` into the local space of the limb matrix `m`, assuming `m` is a rigid
 * transform with (possibly non-uniform) scale: local = D^-1 * R^T * (world - t), where the
 * columns of the 3x3 part are the scaled basis vectors and D holds their squared norms.
 */
static void Morph_WorldToLimb(MtxF* m, Vec3f* world, Vec3f* out) {
    f32 dx = world->x - m->xw;
    f32 dy = world->y - m->yw;
    f32 dz = world->z - m->zw;
    f32 sq0 = SQ(m->xx) + SQ(m->yx) + SQ(m->zx);
    f32 sq1 = SQ(m->xy) + SQ(m->yy) + SQ(m->zy);
    f32 sq2 = SQ(m->xz) + SQ(m->yz) + SQ(m->zz);

    if (sq0 < 1e-12f || sq1 < 1e-12f || sq2 < 1e-12f) {
        out->x = out->y = out->z = 0.0f;
        return;
    }

    out->x = (m->xx * dx + m->yx * dy + m->zx * dz) / sq0;
    out->y = (m->xy * dx + m->yy * dy + m->zy * dz) / sq1;
    out->z = (m->xz * dx + m->yz * dy + m->zz * dz) / sq2;
}

static s16 Morph_ClampS16(f32 x) {
    if (x > 32767.0f) {
        return 32767;
    }
    if (x < -32768.0f) {
        return -32768;
    }
    return (s16)x;
}

static s8 Morph_ClampS8(f32 x) {
    if (x > 127.0f) {
        return 127;
    }
    if (x < -128.0f) {
        return -128;
    }
    return (s8)x;
}

static s32 Morph_GridCellCoord(f32 v, f32 minV, f32 cellSize) {
    s32 c = (s32)((v - minV) / cellSize);

    if (c < 0) {
        return 0;
    }
    if (c >= MORPH_GRID_DIM) {
        return MORPH_GRID_DIM - 1;
    }
    return c;
}

#define MORPH_GRID_CELL(cx, cy, cz) (((cz)*MORPH_GRID_DIM + (cy)) * MORPH_GRID_DIM + (cx))

/**
 * Builds a uniform grid over the snapshot points (counting sort into per-cell index runs) to
 * accelerate the nearest-point queries in `Morph_Begin`. Small snapshots stay brute force.
 */
static void Morph_BuildGrid(MorphSnapshot* snapshot) {
    static u16 sGridCursor[MORPH_GRID_CELLS];
    Vec3f max;
    s32 i;

    sGridValid = false;

    if (snapshot->numPoints < 64) {
        return;
    }

    sGridMin.x = sGridMin.y = sGridMin.z = 32767.0f;
    max.x = max.y = max.z = -32768.0f;
    for (i = 0; i < snapshot->numPoints; i++) {
        Vec3s* point = &snapshot->points[i];

        if (point->x < sGridMin.x) sGridMin.x = point->x;
        if (point->y < sGridMin.y) sGridMin.y = point->y;
        if (point->z < sGridMin.z) sGridMin.z = point->z;
        if (point->x > max.x) max.x = point->x;
        if (point->y > max.y) max.y = point->y;
        if (point->z > max.z) max.z = point->z;
    }

    sGridCellSize.x = (max.x - sGridMin.x) / MORPH_GRID_DIM + 1.0f;
    sGridCellSize.y = (max.y - sGridMin.y) / MORPH_GRID_DIM + 1.0f;
    sGridCellSize.z = (max.z - sGridMin.z) / MORPH_GRID_DIM + 1.0f;

    for (i = 0; i <= MORPH_GRID_CELLS; i++) {
        sGridCellStart[i] = 0;
    }
    for (i = 0; i < snapshot->numPoints; i++) {
        Vec3s* point = &snapshot->points[i];
        s32 cell = MORPH_GRID_CELL(Morph_GridCellCoord(point->x, sGridMin.x, sGridCellSize.x),
                                   Morph_GridCellCoord(point->y, sGridMin.y, sGridCellSize.y),
                                   Morph_GridCellCoord(point->z, sGridMin.z, sGridCellSize.z));

        sGridCellStart[cell + 1]++;
    }
    for (i = 0; i < MORPH_GRID_CELLS; i++) {
        sGridCellStart[i + 1] += sGridCellStart[i];
        sGridCursor[i] = sGridCellStart[i];
    }
    for (i = 0; i < snapshot->numPoints; i++) {
        Vec3s* point = &snapshot->points[i];
        s32 cell = MORPH_GRID_CELL(Morph_GridCellCoord(point->x, sGridMin.x, sGridCellSize.x),
                                   Morph_GridCellCoord(point->y, sGridMin.y, sGridCellSize.y),
                                   Morph_GridCellCoord(point->z, sGridMin.z, sGridCellSize.z));

        sGridPointIndex[sGridCursor[cell]++] = i;
    }

    sGridValid = true;
}

/**
 * Finds the (approximately) nearest snapshot point by scanning grid cells in expanding
 * Chebyshev rings around the query, stopping one ring after the first hit.
 */
static s32 Morph_GridFindNearest(MorphSnapshot* snapshot, Vec3f* p) {
    s32 cx = Morph_GridCellCoord(p->x, sGridMin.x, sGridCellSize.x);
    s32 cy = Morph_GridCellCoord(p->y, sGridMin.y, sGridCellSize.y);
    s32 cz = Morph_GridCellCoord(p->z, sGridMin.z, sGridCellSize.z);
    f32 bestDistSq = 1e30f;
    s32 best = -1;
    s32 foundRadius = -1;
    s32 r;

    for (r = 0; r < MORPH_GRID_DIM; r++) {
        s32 x;
        s32 y;
        s32 z;

        if ((foundRadius >= 0) && (r > foundRadius + 1)) {
            break;
        }

        for (z = cz - r; z <= cz + r; z++) {
            if ((z < 0) || (z >= MORPH_GRID_DIM)) {
                continue;
            }
            for (y = cy - r; y <= cy + r; y++) {
                if ((y < 0) || (y >= MORPH_GRID_DIM)) {
                    continue;
                }
                for (x = cx - r; x <= cx + r; x++) {
                    s32 cell;
                    s32 i;

                    if ((x < 0) || (x >= MORPH_GRID_DIM)) {
                        continue;
                    }
                    // Only the outer shell of the cube is new at this radius
                    if ((ABS(x - cx) != r) && (ABS(y - cy) != r) && (ABS(z - cz) != r)) {
                        continue;
                    }

                    cell = MORPH_GRID_CELL(x, y, z);
                    for (i = sGridCellStart[cell]; i < sGridCellStart[cell + 1]; i++) {
                        Vec3s* point = &snapshot->points[sGridPointIndex[i]];
                        f32 distSq = SQ(p->x - point->x) + SQ(p->y - point->y) + SQ(p->z - point->z);

                        if (distSq < bestDistSq) {
                            bestDistSq = distSq;
                            best = sGridPointIndex[i];
                        }
                    }
                }
            }
        }

        if ((best != -1) && (foundRadius < 0)) {
            foundRadius = r;
        }
    }

    return best;
}

/**
 * Resolves a segment 6 address into the transform object space. Returns NULL for addresses in
 * other segments (e.g. gameplay_keep references), which the walker skips.
 */
static void* Morph_ResolveSegment(void* segAddr) {
    if (SEGMENT_NUMBER(segAddr) != 6) {
        return NULL;
    }
    return (u8*)sBuildObjectSegment + SEGMENT_OFFSET(segAddr);
}

static s32 Morph_VertexKnown(Vtx* vtx) {
    s32 i;

    for (i = 0; i < sMorph.numVerts; i++) {
        if (sMorphVerts[i].vtx == vtx) {
            return true;
        }
    }
    return false;
}

static void Morph_AddVertex(Vtx* vtx) {
    MorphVertex* mv;
    Vec3f local;
    Vec3f world;
    Vec3f collapsedWorld;
    Vec3f collapsedLocal;
    f32 bestDistSq;
    s32 best;
    s32 i;

    if (sBuildCaptureMode) {
        // Snapshot capture: just record the posed, anchor-relative world position
        if (sBuildCaptureTarget->numPoints < MORPH_SNAPSHOT_MAX_POINTS) {
            Vec3s* point = &sBuildCaptureTarget->points[sBuildCaptureTarget->numPoints++];

            local.x = vtx->v.ob[0];
            local.y = vtx->v.ob[1];
            local.z = vtx->v.ob[2];
            Matrix_MultVec3fExt(&local, &world, &sBuildLimbMtx);
            point->x = Morph_ClampS16(world.x - sBuildAnchor.x);
            point->y = Morph_ClampS16(world.y - sBuildAnchor.y);
            point->z = Morph_ClampS16(world.z - sBuildAnchor.z);
        } else if (!sTruncationWarned) {
            sTruncationWarned = true;
            PRINTF_COLOR_RED();
            PRINTF("MORPH: snapshot truncated at %d points! Raise MORPH_SNAPSHOT_MAX_POINTS.\n",
                   MORPH_SNAPSHOT_MAX_POINTS);
            PRINTF_RST();
        }
        return;
    }

    if (Morph_VertexKnown(vtx)) {
        return;
    }

    if (sMorph.numVerts >= MORPH_MAX_VERTS) {
        if (!sTruncationWarned) {
            sTruncationWarned = true;
            PRINTF_COLOR_RED();
            PRINTF("MORPH: vertex list truncated at %d verts! Raise MORPH_MAX_VERTS.\n", MORPH_MAX_VERTS);
            PRINTF_RST();
        }
        return;
    }

    local.x = vtx->v.ob[0];
    local.y = vtx->v.ob[1];
    local.z = vtx->v.ob[2];
    Matrix_MultVec3fExt(&local, &world, &sBuildLimbMtx);

    // Nearest snapshot point (anchor-relative)
    world.x -= sBuildAnchor.x;
    world.y -= sBuildAnchor.y;
    world.z -= sBuildAnchor.z;
    if (sGridValid) {
        best = Morph_GridFindNearest(sBuildSnapshot, &world);
        if (best < 0) {
            best = 0;
        }
    } else {
        best = 0;
        bestDistSq = 1e30f;
        for (i = 0; i < sBuildSnapshot->numPoints; i++) {
            Vec3s* point = &sBuildSnapshot->points[i];
            f32 distSq = SQ(world.x - point->x) + SQ(world.y - point->y) + SQ(world.z - point->z);

            if (distSq < bestDistSq) {
                bestDistSq = distSq;
                best = i;
            }
        }
    }

    collapsedWorld.x = sBuildAnchor.x + sBuildSnapshot->points[best].x;
    collapsedWorld.y = sBuildAnchor.y + sBuildSnapshot->points[best].y;
    collapsedWorld.z = sBuildAnchor.z + sBuildSnapshot->points[best].z;
    Morph_WorldToLimb(&sBuildLimbMtx, &collapsedWorld, &collapsedLocal);

    mv = &sMorphVerts[sMorph.numVerts++];
    mv->vtx = vtx;
    mv->origPos.x = vtx->v.ob[0];
    mv->origPos.y = vtx->v.ob[1];
    mv->origPos.z = vtx->v.ob[2];
    mv->altPos.x = Morph_ClampS16(collapsedLocal.x);
    mv->altPos.y = Morph_ClampS16(collapsedLocal.y);
    mv->altPos.z = Morph_ClampS16(collapsedLocal.z);

    // Only treat these bytes as a normal if lighting is actually active for this vertex --
    // otherwise they hold vertex color (Vtx_t.cn aliases Vtx_tn.n at the same offset)
    mv->hasNormal = (sBuildGeometryMode & G_LIGHTING) != 0;
    if (mv->hasNormal) {
        mv->origNormal[0] = vtx->n.n[0];
        mv->origNormal[1] = vtx->n.n[1];
        mv->origNormal[2] = vtx->n.n[2];
    }
}

/**
 * Walks a display list collecting every vertex it loads. Follows `G_DL` calls and branches,
 * tracks `G_MTX` loads from the flex matrix buffer (segment 0x0D) so flex-skeleton vertices are
 * attributed to the limb matrix that actually transforms them, and tracks `G_GEOMETRYMODE`
 * (`newMode = (oldMode & clearMask) | setMask`, per the F3DEX2 gSPGeometryMode encoding) so
 * vertices are only treated as carrying a lit normal when `G_LIGHTING` is actually active --
 * otherwise the same bytes hold vertex color, and reinterpreting them as a normal would corrupt
 * an unlit mesh's colors. Other commands are ignored.
 */
static void Morph_CollectDListVertices(Gfx* dList, s32 depth) {
    Gfx* cmd;

    if ((dList == NULL) || (depth > 8)) {
        return;
    }

    for (cmd = dList;; cmd++) {
        u32 opcode = cmd->words.w0 >> 24;

        if (opcode == G_ENDDL) {
            break;
        } else if (opcode == G_GEOMETRYMODE) {
            u32 clearMask = ~cmd->words.w0 & 0x00FFFFFF;
            sBuildGeometryMode = (sBuildGeometryMode & clearMask) | cmd->words.w1;
        } else if (opcode == G_DL) {
            Gfx* target = Morph_ResolveSegment((void*)cmd->words.w1);

            if (((cmd->words.w0 >> 16) & 0xFF) == G_DL_NOPUSH) {
                if (target == NULL) {
                    break;
                }
                cmd = target - 1; // branch: continue in the target list
            } else if (target != NULL) {
                Morph_CollectDListVertices(target, depth + 1);
            }
        } else if (opcode == G_VTX) {
            s32 numVtx = (cmd->words.w0 >> 12) & 0xFF;
            Vtx* vtx = Morph_ResolveSegment((void*)cmd->words.w1);
            s32 i;

            if (vtx != NULL) {
                for (i = 0; i < numVtx; i++) {
                    Morph_AddVertex(&vtx[i]);
                }
            }
        } else if (opcode == G_MTX) {
            void* addr = (void*)cmd->words.w1;

            if (SEGMENT_NUMBER(addr) == 0x0D) {
                s32 mtxIndex = SEGMENT_OFFSET(addr) / sizeof(Mtx);

                if (mtxIndex < sNumFlexEntries) {
                    sBuildLimbMtx = sFlexEntries[mtxIndex].mtx;
                }
            }
        }
    }
}

/**
 * Pass 1: mirrors the `SkelAnime_Draw(Flex)Opa` limb recursion (translation/rotation conventions
 * included) to record every limb that has a display list, together with its posed matrix, in
 * draw order. That order matches the flex matrix buffer indices (a slot is consumed for every
 * limb whose authored dList is non-NULL).
 */
static void Morph_WalkLimb(void** skeleton, Vec3s* jointTable, s32 limbIndex) {
    StandardLimb* limb = Morph_ResolveSegment(skeleton[limbIndex]);
    Vec3f pos;
    Vec3s rot;

    if (limb == NULL) {
        return;
    }

    if (limbIndex == 0) {
        pos.x = jointTable[0].x;
        pos.y = jointTable[0].y;
        pos.z = jointTable[0].z;
    } else {
        pos.x = limb->jointPos.x;
        pos.y = limb->jointPos.y;
        pos.z = limb->jointPos.z;
    }
    rot = jointTable[limbIndex + 1];

    Matrix_Push();
    Matrix_TranslateRotateZYX(&pos, &rot);

    {
        // Apply what the actor's draw callbacks do to this limb (1-based index there)
        Gfx* mainDL = limb->dList;
        s32 i;

        for (i = 0; i < sBuildNumSwaps; i++) {
            MorphLimbSwap* swap = &sBuildSwaps[i];

            if (swap->limb != limbIndex + 1) {
                continue;
            }
            if (swap->op == MORPH_LIMB_REPLACE) {
                mainDL = swap->dList;
            } else if (swap->op == MORPH_LIMB_HIDE) {
                mainDL = NULL;
            } else if ((swap->op == MORPH_LIMB_ADD) && (sNumExtraEntries < ARRAY_COUNT(sExtraEntries))) {
                MorphFlexEntry* extra = &sExtraEntries[sNumExtraEntries++];

                Matrix_Get(&extra->mtx);
                extra->dList = Morph_ResolveSegment(swap->dList);
            }
        }

        if (limb->dList != NULL) {
            // A flex matrix slot is consumed for every limb with an authored dList, even when
            // the draw callbacks replace or hide it, so record the entry either way to keep
            // the segment 0x0D indices aligned
            if (sNumFlexEntries < MORPH_MAX_FLEX_ENTRIES) {
                MorphFlexEntry* entry = &sFlexEntries[sNumFlexEntries++];

                Matrix_Get(&entry->mtx);
                entry->dList = Morph_ResolveSegment(mainDL); // NULL when hidden
            }
        } else if ((mainDL != NULL) && (sNumExtraEntries < ARRAY_COUNT(sExtraEntries))) {
            // Replacement on a limb without an authored dList: no flex slot, treat as extra
            MorphFlexEntry* extra = &sExtraEntries[sNumExtraEntries++];

            Matrix_Get(&extra->mtx);
            extra->dList = Morph_ResolveSegment(mainDL);
        }
    }

    if (limb->child != LIMB_DONE) {
        Morph_WalkLimb(skeleton, jointTable, limb->child);
    }

    Matrix_Pop();

    if ((limbIndex != 0) && (limb->sibling != LIMB_DONE)) {
        Morph_WalkLimb(skeleton, jointTable, limb->sibling);
    }
}

/**
 * Walks the whole posed mesh of `actor`: pass 1 records limb matrices (so forward `G_MTX`
 * references into the flex buffer resolve), pass 2 collects the vertices of each limb's DL.
 */
static void Morph_WalkMesh(PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps, s32 numSwaps) {
    s32 i;

    sBuildObjectSegment = Actor_GetObjectSegment(play, actor);
    sBuildAnchor = actor->world.pos;
    sBuildSwaps = swaps;
    sBuildNumSwaps = (swaps != NULL) ? numSwaps : 0;
    sNumFlexEntries = 0;
    sNumExtraEntries = 0;
    // Actors are drawn via Gfx_SetupDL_25Opa (lit, textured, opaque), so default to lit; a
    // G_GEOMETRYMODE command mid-DL updates this if a limb's mesh explicitly changes it
    sBuildGeometryMode = G_LIGHTING;
    sTruncationWarned = false;

    Matrix_SetTranslateRotateYXZ(actor->world.pos.x, actor->world.pos.y, actor->world.pos.z, &actor->shape.rot);
    Matrix_Scale(actor->scale.x, actor->scale.y, actor->scale.z, MTXMODE_APPLY);
    Morph_WalkLimb(skelAnime->skeleton, skelAnime->jointTable, 0);

    for (i = 0; i < sNumFlexEntries; i++) {
        if (sFlexEntries[i].dList != NULL) {
            sBuildLimbMtx = sFlexEntries[i].mtx;
            Morph_CollectDListVertices(sFlexEntries[i].dList, 0);
        }
    }
    for (i = 0; i < sNumExtraEntries; i++) {
        if (sExtraEntries[i].dList != NULL) {
            sBuildLimbMtx = sExtraEntries[i].mtx;
            Morph_CollectDListVertices(sExtraEntries[i].dList, 0);
        }
    }
}

/**
 * Captures the creature's current posed shape into the monster snapshot. Run by the creature
 * itself (it knows its `SkelAnime`) when the player requested it for a transformation switch.
 */
void Morph_CaptureMonsterSnapshot(PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps,
                                  s32 numSwaps) {
    sMorph.monsterCaptureRequested = false;
    sMorph.monsterCaptured = false;

    if ((skelAnime->skeleton == NULL) || (actor->objectSlot != TRANSFORM_OBJECT_SLOT)) {
        return;
    }

    sMonsterSnapshot.numPoints = 0;
    sBuildCaptureMode = true;
    sBuildCaptureTarget = &sMonsterSnapshot;
    Morph_WalkMesh(play, actor, skelAnime, swaps, numSwaps);
    sBuildCaptureMode = false;

    sMorph.monsterCaptured = (sMonsterSnapshot.numPoints > 0);

    PRINTF("MORPH: captured monster snapshot, %d points\n", sMonsterSnapshot.numPoints);
}

/**
 * Blends a vertex's normal from the "collapsed" approximation (t=0) to its authored normal
 * (t=1). Callers pass the fraction toward the *authored* shape, not raw morph progress --
 * see the call site in Morph_WriteVertices for the per-direction mapping.
 */
static void Morph_WriteNormal(MorphVertex* mv, f32 t) {
    // Approximate the "collapsed" normal as the radial direction from the limb's local origin
    // through the collapsed position -- there is no real target normal for a nearest-neighbor
    // position match, but this reads reasonably for a roughly-convex creature body and, unlike
    // leaving the normal untouched, at least turns to face somewhere plausible as the vertex
    // moves far from its authored position.
    f32 ax = mv->altPos.x, ay = mv->altPos.y, az = mv->altPos.z;
    f32 altLenSq = SQ(ax) + SQ(ay) + SQ(az);
    f32 ox = mv->origNormal[0], oy = mv->origNormal[1], oz = mv->origNormal[2];
    f32 nx, ny, nz;
    f32 lenSq;

    if (altLenSq < 1.0f) {
        // Collapses onto (or very near) the limb origin: no meaningful radial direction,
        // fall back to the authored normal unchanged
        ax = ox;
        ay = oy;
        az = oz;
        altLenSq = SQ(ax) + SQ(ay) + SQ(az);
        if (altLenSq < 1.0f) {
            return;
        }
    }
    {
        f32 altInvLen = 1.0f / sqrtf(altLenSq);

        ax *= altInvLen;
        ay *= altInvLen;
        az *= altInvLen;
    }

    // Original normal bytes are roughly unit-length * 127; lerp from radial (t=0) to authored (t=1)
    nx = ax * 127.0f + (ox - ax * 127.0f) * t;
    ny = ay * 127.0f + (oy - ay * 127.0f) * t;
    nz = az * 127.0f + (oz - az * 127.0f) * t;

    lenSq = SQ(nx) + SQ(ny) + SQ(nz);
    if (lenSq < 1.0f) {
        return;
    }
    {
        f32 scale = 127.0f / sqrtf(lenSq);

        mv->vtx->n.n[0] = Morph_ClampS8(nx * scale);
        mv->vtx->n.n[1] = Morph_ClampS8(ny * scale);
        mv->vtx->n.n[2] = Morph_ClampS8(nz * scale);
    }
}

static void Morph_WriteVertices(f32 progress) {
    f32 eSmooth = progress * progress * (3.0f - 2.0f * progress);
    f32 eOvershoot = eSmooth;
    f32 normalT = CLAMP(progress, 0.0f, 1.0f);
    s32 i;

    if ((sMorph.direction == MORPH_DIR_UNFOLD) && (TRANSFORM_MORPH_OVERSHOOT > 0.0f)) {
        // easeOutBack: overshoots past the authored shape, then settles
        f32 c1 = TRANSFORM_MORPH_OVERSHOOT;
        f32 c3 = c1 + 1.0f;
        f32 u = progress - 1.0f;

        eOvershoot = 1.0f + c3 * u * u * u + c1 * u * u;
    }

    for (i = 0; i < sMorph.numVerts; i++) {
        MorphVertex* mv = &sMorphVerts[i];
        Vec3s* from;
        Vec3s* to;
        f32 e;

        if (sMorph.direction == MORPH_DIR_UNFOLD) {
            from = &mv->altPos;
            to = &mv->origPos;
            // Scale the overshoot by how far this specific vertex travels, so vertices that
            // barely move don't buzz with the same bounce as vertices crossing the whole model
            e = eSmooth + (eOvershoot - eSmooth) * (mv->overshootWeight * (1.0f / 255.0f));
        } else {
            from = &mv->origPos;
            to = &mv->altPos;
            e = eSmooth;
        }

        mv->vtx->v.ob[0] = Morph_ClampS16(from->x + (to->x - from->x) * e);
        mv->vtx->v.ob[1] = Morph_ClampS16(from->y + (to->y - from->y) * e);
        mv->vtx->v.ob[2] = Morph_ClampS16(from->z + (to->z - from->z) * e);

        if (mv->hasNormal) {
            // Normals always use the plain linear progress (not the overshoot-eased position
            // easing) to avoid the lit surface flickering/inverting during the bounce
            Morph_WriteNormal(mv, (sMorph.direction == MORPH_DIR_UNFOLD) ? normalT : 1.0f - normalT);
        }
    }
}

static s32 Morph_Begin(PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps, s32 numSwaps,
                       MorphSnapshot* snapshot, MorphDirection direction, s32 duration) {
    if (sMorph.active || sMorph.meshDirty || (snapshot->numPoints == 0) || (skelAnime->skeleton == NULL) ||
        (actor->objectSlot != TRANSFORM_OBJECT_SLOT) || (duration < 1)) {
        return false;
    }

    sBuildSnapshot = snapshot;
    sMorph.numVerts = 0;

    Morph_BuildGrid(snapshot);
    Morph_WalkMesh(play, actor, skelAnime, swaps, numSwaps);

    PRINTF("MORPH: %d verts, %d snapshot points, dir=%d\n", sMorph.numVerts, snapshot->numPoints, direction);

    if (sMorph.numVerts == 0) {
        return false;
    }

    // Weight each vertex's overshoot by its own displacement relative to the largest
    // displacement in this morph (see Morph_WriteVertices)
    {
        f32 maxDistSq = 0.0f;
        s32 i;

        for (i = 0; i < sMorph.numVerts; i++) {
            MorphVertex* mv = &sMorphVerts[i];
            f32 distSq = SQ(mv->origPos.x - mv->altPos.x) + SQ(mv->origPos.y - mv->altPos.y) +
                        SQ(mv->origPos.z - mv->altPos.z);

            if (distSq > maxDistSq) {
                maxDistSq = distSq;
            }
        }

        for (i = 0; i < sMorph.numVerts; i++) {
            MorphVertex* mv = &sMorphVerts[i];

            if (maxDistSq < 1.0f) {
                mv->overshootWeight = 255;
            } else {
                f32 distSq = SQ(mv->origPos.x - mv->altPos.x) + SQ(mv->origPos.y - mv->altPos.y) +
                            SQ(mv->origPos.z - mv->altPos.z);

                mv->overshootWeight = (u8)(sqrtf(distSq / maxDistSq) * 255.0f);
            }
        }
    }

    sMorph.owner = actor;
    sMorph.direction = direction;
    sMorph.timer = 0;
    sMorph.duration = duration;
    sMorph.active = true;
    sMorph.meshDirty = true;
    sMorph.collapsedHeld = false;

    // Write the start shape immediately so the very first drawn frame is already morphed
    Morph_WriteVertices(0.0f);

    return true;
}

s32 Morph_TryBeginUnfold(PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps, s32 numSwaps,
                         s32 duration) {
    MorphSnapshot* source;

    if (!sMorph.unfoldRequested) {
        return false;
    }
    sMorph.unfoldRequested = false;

    // Unfold from the outgoing creature's shape when switching between transformations,
    // from Link's shape otherwise
    if (sMorph.monsterCaptured) {
        source = &sMonsterSnapshot;
        duration = TRANSFORM_MORPH_DURATION_SWITCH;
    } else {
        source = &sLinkSnapshot;
    }
    sMorph.monsterCaptured = false;

    return Morph_Begin(play, actor, skelAnime, swaps, numSwaps, source, MORPH_DIR_UNFOLD, duration);
}

s32 Morph_TryBeginCollapse(PlayState* play, Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps, s32 numSwaps,
                           s32 duration) {
    if (!sMorph.collapseRequested) {
        return false;
    }
    sMorph.collapseRequested = false;

    return Morph_Begin(play, actor, skelAnime, swaps, numSwaps, &sLinkSnapshot, MORPH_DIR_COLLAPSE, duration);
}

/**
 * Advances the active morph by one frame. Returns true when no morph is running (anymore).
 */
s32 Morph_Update(PlayState* play, Actor* actor) {
    if (!sMorph.active) {
        return true;
    }

#if TRANSFORM_MORPH_SPARKLES
    if (sMorph.owner == actor) {
        static Color_RGBA8 sSparklePrimColor = { 170, 255, 255, 255 };
        static Color_RGBA8 sSparkleEnvColor = { 50, 150, 255, 0 };
        static Vec3f sSparkleAccel = { 0.0f, 0.1f, 0.0f };
        Vec3f velocity = { 0.0f, 1.0f, 0.0f };
        Vec3f pos;
        s32 i;

        for (i = 0; i < 2; i++) {
            pos.x = actor->world.pos.x + (Rand_ZeroOne() - 0.5f) * 60.0f;
            pos.y = actor->world.pos.y + Rand_ZeroOne() * 60.0f;
            pos.z = actor->world.pos.z + (Rand_ZeroOne() - 0.5f) * 60.0f;
            EffectSsKiraKira_SpawnDispersed(play, &pos, &velocity, &sSparkleAccel, &sSparklePrimColor,
                                            &sSparkleEnvColor, 1500, 16);
        }
    }
#endif

    sMorph.timer++;

    if (sMorph.timer >= sMorph.duration) {
        Morph_WriteVertices(1.0f);
        sMorph.active = false;

        if (sMorph.direction == MORPH_DIR_UNFOLD) {
            // Vertices are back at their authored positions
            sMorph.meshDirty = false;
            sMorph.owner = NULL;
        } else {
            // Hold the collapsed shape until the owner is removed (see Morph_Restore)
            sMorph.collapsedHeld = true;
        }
        return true;
    }

    Morph_WriteVertices((f32)sMorph.timer / sMorph.duration);
    return false;
}

/**
 * Restores the mesh to its authored vertex positions if `actor` owns morphed vertex data, and
 * clears the morph. Must be called before the actor's object is evicted from the transform space
 * (actor Destroy at the latest, or explicitly before `Object_LoadTransform` replaces the object).
 * Idempotent; a NULL or non-owning actor is a no-op.
 */
void Morph_Restore(Actor* actor) {
    s32 i;

    if ((actor == NULL) || (sMorph.owner != actor)) {
        return;
    }

    if (sMorph.meshDirty) {
        for (i = 0; i < sMorph.numVerts; i++) {
            MorphVertex* mv = &sMorphVerts[i];

            mv->vtx->v.ob[0] = mv->origPos.x;
            mv->vtx->v.ob[1] = mv->origPos.y;
            mv->vtx->v.ob[2] = mv->origPos.z;

            if (mv->hasNormal) {
                mv->vtx->n.n[0] = mv->origNormal[0];
                mv->vtx->n.n[1] = mv->origNormal[1];
                mv->vtx->n.n[2] = mv->origNormal[2];
            }
        }
    }

    sMorph.owner = NULL;
    sMorph.numVerts = 0;
    sMorph.active = false;
    sMorph.meshDirty = false;
    sMorph.collapsedHeld = false;
}

#endif
