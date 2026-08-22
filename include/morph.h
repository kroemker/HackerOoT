#ifndef MORPH_H
#define MORPH_H

#include "ultra64.h"
#include "animation.h"
#include "config.h"

struct PlayState;
struct Player;
struct Actor;

// HackerOoT: vertex-level morphing for player transformations (see src/code/z_morph.c).
// A morph always mutates the mesh of a transformation actor (whose object lives in the
// transform object space); the "other side" of the morph is a snapshot: a point cloud of
// posed, anchor-relative world-space vertex positions.

// Maximum vertices of a morphing (destination) mesh. Must comfortably exceed the largest
// transform actor's walked vertex count (the Iron Knuckle's object data totals ~1700 across all
// declared Vtx arrays, though not all are reachable at once) -- Morph_AddVertex silently drops
// (freezes) any vertex past this cap, so keep real headroom above what actors actually need.
#define MORPH_MAX_VERTS 2048
// Maximum points in a source shape snapshot. Must comfortably exceed Link's walked vertex count
// (his current child model alone is 1348 vertices) -- points past this cap are silently dropped
// from the correspondence data, so keep real headroom.
#define MORPH_SNAPSHOT_MAX_POINTS 2048
// Maximum limbs with display lists per skeleton (also the flex matrix buffer size)
#define MORPH_MAX_FLEX_ENTRIES 48

typedef enum MorphDirection {
    MORPH_DIR_UNFOLD,  // vertices start collapsed onto the snapshot and lerp to their true positions
    MORPH_DIR_COLLAPSE // vertices start at their true positions and lerp onto the snapshot
} MorphDirection;

typedef struct MorphSnapshot {
    s32 numPoints;
    Vec3s points[MORPH_SNAPSHOT_MAX_POINTS]; // world space, relative to the anchor at capture time
} MorphSnapshot;

typedef enum MorphLimbOp {
    MORPH_LIMB_REPLACE, // draw callbacks replace this limb's display list with another one
    MORPH_LIMB_ADD,     // draw callbacks draw an additional display list with this limb's matrix
    MORPH_LIMB_HIDE     // draw callbacks suppress this limb's display list
} MorphLimbOp;

// Mirrors what an actor's override/post limb draw callbacks do to its mesh, so the morph walker
// sees the same geometry the player sees. `limb` uses the same 1-based indices the draw
// callbacks receive (e.g. the `*_LIMB_*` enums).
typedef struct MorphLimbSwap {
    u8 limb;
    u8 op;      // MorphLimbOp
    Gfx* dList; // segmented address in the actor's object (unused for MORPH_LIMB_HIDE)
} MorphLimbSwap;

#if TRANSFORM_USE_MORPH

void Morph_Reset(void);
void Morph_CaptureLinkSnapshot(struct PlayState* play, struct Player* player);
void Morph_RequestMonsterCapture(void);
s32 Morph_MonsterCaptureRequested(void);
s32 Morph_MonsterCaptureDone(void);
void Morph_CaptureMonsterSnapshot(struct PlayState* play, struct Actor* actor, SkelAnime* skelAnime,
                                  MorphLimbSwap* swaps, s32 numSwaps);
void Morph_RequestUnfold(void);
void Morph_RequestCollapse(void);
s32 Morph_CollapseRequested(void);
s32 Morph_TryBeginUnfold(struct PlayState* play, struct Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps,
                         s32 numSwaps, s32 duration);
s32 Morph_TryBeginCollapse(struct PlayState* play, struct Actor* actor, SkelAnime* skelAnime, MorphLimbSwap* swaps,
                           s32 numSwaps, s32 duration);
s32 Morph_IsActiveFor(struct Actor* actor);
s32 Morph_IsCollapsedFor(struct Actor* actor);
s32 Morph_IsBusy(void);
s32 Morph_Update(struct PlayState* play, struct Actor* actor);
void Morph_Restore(struct Actor* actor);

#endif

#endif
