#ifndef _Z_TRANSFORM_WOLFOS_H_
#define _Z_TRANSFORM_WOLFOS_H_

#include "ultra64.h"
#include "actor.h"

#include "../ovl_En_Wf/z_en_wf.h"

struct TransformWolfos;

typedef void (*TransformWolfosActionFunc)(struct TransformWolfos*, struct PlayState*);

typedef struct TransformWolfos {
    Actor actor;
    SkelAnime skelAnime;
    Vec3s jointTable[WOLFOS_LIMB_MAX];
    Vec3s morphTable[WOLFOS_LIMB_MAX];
    TransformWolfosActionFunc actionFunc;
    ColliderJntSph clawsColliderSphere;
    ColliderJntSphElement clawsColliderSphereElements[4];
    ColliderCylinder bodyColliderCylinder;
    ColliderCylinder tailColliderCylinder;
    u8 eyeIndex;
    s16 invincibilityTimer;
    u8 playedSfx;
    u8 queuedAttack;
    u8 shieldState;
    u8 attackState;
} TransformWolfos;

#endif
