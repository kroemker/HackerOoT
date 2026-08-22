# Vertex Morph Transformation — Implementation Plan

> **Status:** Phases 0–5 implemented (`src/code/z_morph.c`, `include/morph.h`,
> `TRANSFORM_USE_MORPH` in `config_game.h`). `Transform_Ik` (D-Right) is the second transform
> actor; monster↔monster switches capture the outgoing creature's shape via a one-frame
> request handshake. Link's own posed mesh is now walked directly (his `LodLimb` skeleton is
> read through the `StandardLimb` layout, which aliases at the `dList` field, and his flex
> `G_MTX` references resolve like any other flex skeleton); the body-part-bone sampling is
> kept only as a fallback if the walk yields no vertices. `MorphLimbSwap` tables let a
> a transform actor tell the walker about override/post-draw display lists (used for the IK's
> helmet/head swap and pauldron/chest-armor overlays, which now morph instead of popping in).
> Phase 5 additions: a uniform grid accelerates the nearest-point search for snapshots ≥64
> points, monster→monster switches use a shorter duration
> (`TRANSFORM_MORPH_DURATION_SWITCH`), unfolds ease with a configurable overshoot
> (`TRANSFORM_MORPH_OVERSHOOT`, easeOutBack), and sparkle particles spawn around the actor
> while a morph plays (`TRANSFORM_MORPH_SPARKLES`).
>
> Not yet verified in-emulator: the real Link mesh extraction is the biggest behavioral change
> in this pass and should be tested for visual correctness (vertex count sanity via the
> `MORPH:` debug prints, and whether the collapsed creature shape reads as "Link-ish").

Replaces the gray screen-fill in the player transformation flow (see the
`Player_Action_Transform*` functions in `z_player.c`) with a vertex-level morph:
destination creature vertices start collapsed onto the source's shape and lerp to
their true positions (or the reverse, for morphing back). One shared mechanism
covers Link→monster, monster→monster, and monster→Link.

## Core invariants

1. **Only monster meshes are mutated** — always the object in the transform space
   buffer (`ObjectContext.transformSpaceStart`). Link's mesh is never written.
2. **The "other side" of a morph is a snapshot**: a point cloud of posed
   world-space vertex positions, stored **relative to an anchor point** (the
   actor's world position). This keeps it source-agnostic, position-independent,
   and lets the source object be evicted from the transform space mid-morph.
3. **Both poses are frozen for the morph duration**, so lerp endpoints are
   precomputed once in limb-local space and each frame is just an eased s16 lerp
   written into the `Vtx` data.

## New module: `src/code/z_morph.c` + `include/morph.h`

Added to the `code` segment in `spec`.

- **`MorphVertex`** — per-vertex state: `Vtx*` (into transform space), limb
  index, `startLocal`/`endLocal` (s16 local-space positions).
- **`MorphState`** — singleton (one morph at a time): vertex array, count,
  timer, duration, direction, `active` flag. Budget ~1024 vertices (~20 KB);
  allocate a `MORPH_SCRATCH` buffer alongside the transform space in
  `Object_InitContext` so lifetime matches the transform system.
- **`Morph_CollectVertices`** — DL walker: for each limb, parse the display
  list (`gbi.h` command layout), collecting `G_VTX` loads (resolve segment-6
  addresses into the transform space copy), following `G_DL`, stopping at
  `G_ENDDL`. Dedupe overlapping vertex ranges by address. Standard skeletons
  only — no `G_MTX` tracking needed.
- **`Morph_ComputeLimbMatrices`** — mirror the `SkelAnime_DrawOpa` recursion
  with `Matrix_Push`/`Matrix_TranslateRotateZYX`, storing each limb's `MtxF`.
- **`Morph_CaptureSnapshot(actor)`** — walker + limb matrices → anchor-relative
  world positions into a snapshot buffer (`Vec3s`, ~6 KB @ 1024 verts).
- **`Morph_CaptureLinkSnapshot(player)`** — v1: bone-capsule approximation
  (nearest point on limb segments from the player's joint table). v2 (Phase 4):
  true flex-skeleton vertex extraction.
- **`Morph_Begin(destActor, snapshot, direction, durationFrames)`** — computes
  dest limb matrices once, then per dest vertex: world position → nearest
  snapshot point (brute force v1) → inverse limb matrix → collapsed local
  position. `MORPH_UNFOLD`: start = collapsed, end = original;
  `MORPH_COLLAPSE`: reversed. Original positions saved here (= restore data).
- **`Morph_Update()`** — eased lerp (smoothstep), write positions into the
  `Vtx` structs; returns done. Normals untouched in v1.
- **`Morph_Abort()`** — instantly restore original positions, clear `active`.
  Must be called from the transform actor's `Destroy` if a morph is active, so
  a scene transition/kill mid-morph never leaves a warped mesh cached in the
  transform space (`loadedTransformObjectId` would skip the re-DMA).

## Player state machine changes (`z_player.c`)

Keep the ported action structure; only the fade is replaced. Gate behind a
config flag (e.g. `TRANSFORM_USE_MORPH`) with the gray fill as fallback.

- **`Player_Action_Transform`**: no fill fade. In one frame, masked by a 2–3
  frame white flash (`screenFillColor`): capture source snapshot (Link capsule,
  or current monster if switching), kill old creature if switching,
  `Object_LoadTransform`, spawn creature, hide Link
  (`PLAYER_STATE2_29 | PLAYER_STATE2_15`). The creature spawns already
  collapsed (its first Update calls `Morph_Begin(UNFOLD)`) — no visible pop.
  Player action waits on `gMorphState.active == false` →
  `Player_Action_Transformed`.
- **`Player_Action_TransformBack`**: capture Link capsule snapshot at the
  creature's position, `Morph_Begin(COLLAPSE)` on the creature; when done:
  white flash, `Player_DisableTransform` (creature `Destroy` restores the
  mesh), `Player_Action_TransformEnd` (now just the flash fade-out).
- **Monster→monster switch**: `Player_CheckTransform` path snapshots the
  *current creature* instead of Link, then reuses the transform-in flow.

## Creature-side shared hooks

Each transform actor gets two thin actions using shared helpers:
`Action_MorphIn` (anim held on idle frame 0, input locked, colliders off, runs
`Morph_Update` until done → Idle) and `Action_MorphOut` (same, signals
completion). ~25 lines per actor; part of the new-transform-actor template.

## Phases

| Phase | Work | Est. | Milestone |
|---|---|---|---|
| 0 | Module skeleton, spec entry, scratch alloc, config flag | ½ day | Builds, no behavior change |
| 1 | Walker + limb matrices + capsule Link snapshot + `UNFOLD`; hook into transform-in | 2–3 days | Gohma unfolds out of Link's silhouette |
| 2 | `COLLAPSE` + transform-back + flashes + abort/restore safety | 1 day | Full round trip, robust vs. scene exits mid-morph |
| 3 | Monster→monster switch path | ½–1 day | Needs a 2nd transform actor — port `Transform_Ik`/`Transform_Keese` from `hm-comp-2` as test vehicle |
| 4 | Real Link vertex extraction (flex skeleton walk, shared-matrix verts) | 2–5 days | Collapse shape is recognizably Link |
| 5 | Polish: per-pair durations/easing, spatial grid for the nearest-point search if `Morph_Begin` hitches on console (~1–3 frames brute force), particles/sfx | open | Feel pass |

Each phase ends runnable in emulator; test on console (or accurate-timing emu)
at Phases 4–5 for search cost and DL walker correctness.

## Known risks

- **Vtx aliasing** between limbs → vertex morphed twice; walker dedupe must be
  correct. Verify with a per-limb count dump on first run.
- **Transform-space cache integrity**: every path abandoning a morph must
  restore originals (centralized in actor `Destroy` + `Morph_Abort`).
- **s16 anchor-relative snapshot range** (±32k): fine for sane creature sizes;
  assert on capture.
- **Nearest-neighbor aesthetics**: writhing/organic look, texture stretch at
  endpoints hidden by the flash. Judged at the Phase 1 milestone — also the
  decision point for whether Phase 4's exact Link shape is worth it.

Phase 1 is the go/no-go gate: it exercises every novel mechanism (walker,
matrices, correspondence, in-place Vtx writes) with the cheap snapshot;
everything after is incremental.
