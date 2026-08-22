#ifndef _Z_TRANSFORM_IK_H_
#define _Z_TRANSFORM_IK_H_

#include "ultra64.h"
#include "actor.h"

#include "../ovl_En_Ik/z_en_ik.h"

struct TransformIk;

typedef void (*TransformIkActionFunc)(struct TransformIk*, struct PlayState*);

typedef struct TransformIk {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[IRON_KNUCKLE_LIMB_MAX];
    Vec3s morphTable[IRON_KNUCKLE_LIMB_MAX];
    TransformIkActionFunc actionFunc;
    ColliderCylinder bodyCollider;
    ColliderQuad axeCollider;
    ColliderTris shieldCollider;
    ColliderTrisElement shieldColliderItems[2];
    s32 blureIdx;
    u32 playedSfx;
    u32 queuedAttack;
    u32 attackState;
    u32 shieldState;
    AnimationHeader* recoverAnimation;
    s32 animationTimer;
    u8 previousFrameInWater;
    s16 invincibilityTimer;
} TransformIk;

#endif
