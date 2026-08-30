/*
 * File: z_transform_wolfos.c
 * Overlay: ovl_Transform_Wolfos
 * Description: Wolfos Transform
 */

#include "z_transform_wolfos.h"
#include "assets/objects/object_wf/object_wf.h"

#include "libc64/qrand.h"
#include "array_count.h"
#include "gfx.h"
#include "gfx_setupdl.h"
#include "ichain.h"
#include "printf.h"
#include "rand.h"
#include "segmented_address.h"
#include "sfx.h"
#include "sys_matrix.h"
#include "terminal.h"
#include "translation.h"
#include "z_lib.h"
#include "effect.h"
#include "play_state.h"
#include "player.h"
#include "save.h"
#include "controller.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED | ACTOR_FLAG_DRAW_CULLING_DISABLED)

#define BACKFLIP_SPEED -14.0f
#define BACKFLIP_DEACCELERATION 0.7f
#define JUMP_VERTICAL_SPEED 9.0f

void TransformWolfos_Init(Actor* thisx, PlayState* play);
void TransformWolfos_Destroy(Actor* thisx, PlayState* play);
void TransformWolfos_Update(Actor* thisx, PlayState* play);
void TransformWolfos_Draw(Actor* thisx, PlayState* play);

void TransformWolfos_SetupAction(TransformWolfos* this, PlayState* play, TransformWolfosActionFunc actionFunc);
void TransformWolfos_Action_Run(TransformWolfos* this, PlayState* play);
void TransformWolfos_Action_Idle(TransformWolfos* this, PlayState* play);
void TransformWolfos_Action_Attack(TransformWolfos* this, PlayState* play);
void TransformWolfos_Action_Block(TransformWolfos* this, PlayState* play);
void TransformWolfos_Action_Backflip(TransformWolfos* this, PlayState* play);
void TransformWolfos_Action_Howl(TransformWolfos* this, PlayState* play);

ActorProfile Transform_Wolfos_Profile = {
    /**/ ACTOR_TRANSFORM_WOLFOS,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_WF,
    /**/ sizeof(TransformWolfos),
    /**/ TransformWolfos_Init,
    /**/ TransformWolfos_Destroy,
    /**/ TransformWolfos_Update,
    /**/ TransformWolfos_Draw,
};

static ColliderJntSphElementInit sClawsColliderElements[] = {
    {
        {
            ELEM_MATERIAL_UNK0,
            { 0xFFCFFFFF, HIT_SPECIAL_EFFECT_NONE, 0x04 },
            { 0xFFC3FFFF, HIT_BACKLASH_NONE, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_NONE,
        },
        { WOLFOS_LIMB_FRONT_RIGHT_CLAW, { { 0, 0, 0 }, 15 }, 100 },
    },
    {
        {
            ELEM_MATERIAL_UNK0,
            { 0xFFCFFFFF, HIT_SPECIAL_EFFECT_NONE, 0x04 },
            { 0xFFC3FFFF, HIT_BACKLASH_NONE, 0x00 },
            ATELEM_ON | ATELEM_SFX_NORMAL,
            ACELEM_ON,
            OCELEM_NONE,
        },
        { WOLFOS_LIMB_FRONT_LEFT_CLAW, { { 0, 0, 0 }, 15 }, 100 },
    },
};

static ColliderJntSphInit sClawsCollider = {
    {
        COL_MATERIAL_METAL,
        AT_ON | AT_TYPE_PLAYER,
        AC_ON | AC_HARD | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sClawsColliderElements),
    sClawsColliderElements,
};

static ColliderCylinderInit sBodyCollider = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK1,
        { 0x00000000, HIT_SPECIAL_EFFECT_NONE, 0x00 },
        { 0xFFCFFFFF, HIT_BACKLASH_NONE, 0x00 },
        ATELEM_NONE,
        ACELEM_ON,
        OCELEM_ON,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sTailCollider = {
    {
        COL_MATERIAL_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    {
        ELEM_MATERIAL_UNK1,
        { 0x00000000, HIT_SPECIAL_EFFECT_NONE, 0x00 },
        { 0xFFCFFFFF, HIT_BACKLASH_NONE, 0x00 },
        ATELEM_NONE,
        ACELEM_ON,
        OCELEM_NONE,
    },
    { 15, 20, -15, { 0, 0, 0 } },
};

void TransformWolfos_CheckButtonActions(TransformWolfos* this, PlayState* play) {
    if (CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_Z | BTN_A)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Backflip);
    } else if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Attack);
    } else if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_A)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Howl);
    } else if (CHECK_BTN_ALL(play->state.input[0].press.button, BTN_R)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Block);
    }
}

void TransformWolfos_Action_Idle(TransformWolfos* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    if (speedTarget != 0.0f) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Run);
    } else {
        Math_ScaledStepToS(&this->actor.world.rot.y, yawTarget, 1200);
        this->actor.shape.rot.y = this->actor.world.rot.y;
    }

    SkelAnime_Update(&this->skelAnime);

    TransformWolfos_CheckButtonActions(this, play);
}

void TransformWolfos_Action_Run(TransformWolfos* this, PlayState* play) {
    f32 speedTarget;
    s16 yawTarget;
    s32 prevFrame;
    s32 beforeCurFrame;
    s32 absPlaySpeed;

    Actor_GetMovementSpeedAndYaw(&this->actor, &speedTarget, &yawTarget, 1, 1, play);

    this->actor.world.rot.y = this->actor.shape.rot.y = yawTarget;
    Math_StepToF(&this->actor.speed, speedTarget, 0.9f);

    this->skelAnime.playSpeed = this->actor.speed * 0.175f;

    if (this->actor.speed == 0.0f) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }

    prevFrame = (s32)this->skelAnime.curFrame;
    SkelAnime_Update(&this->skelAnime);
    beforeCurFrame = (s32)(this->skelAnime.curFrame - ABS(this->skelAnime.playSpeed));
    absPlaySpeed = (s32)(f32)ABS(this->skelAnime.playSpeed);

    TransformWolfos_CheckButtonActions(this, play);

    if ((prevFrame != (s32)this->skelAnime.curFrame) && (beforeCurFrame <= 0) && ((absPlaySpeed + prevFrame) > 0)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_WALK);
        Actor_SpawnFloorDustRing(play, &this->actor, &this->actor.world.pos, 20.0f, 3, 3.0f, 50, 50, true);
    }
}

void TransformWolfos_Action_Attack(TransformWolfos* this, PlayState* play) {
    if ((this->skelAnime.curFrame > 7.0f) && CHECK_BTN_ALL(play->state.input[0].press.button, BTN_B) &&
        (this->queuedAttack == 0)) {
        this->queuedAttack = 1;
        this->skelAnime.endFrame = Animation_GetLastFrame(&gWolfosSlashingAnim);
    }

    if ((this->skelAnime.curFrame > 9.0f) && (this->skelAnime.curFrame < 12.0f)) {
        if (this->playedSfx < 1) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_ATTACK);
            this->playedSfx = 1;
        }
        this->attackState = 1;
    } else if ((this->skelAnime.curFrame > 17.0f) && (this->skelAnime.curFrame < 19.0f)) {
        if (this->playedSfx < 2) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_ATTACK);
            this->playedSfx = 2;
        }
        this->attackState = 1;
    } else {
        this->attackState = 0;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }
}

void TransformWolfos_Action_Block(TransformWolfos* this, PlayState* play) {
    if (!CHECK_BTN_ALL(play->state.input[0].cur.button, BTN_R)) {
        this->skelAnime.playSpeed = 1.0f;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }
}

void TransformWolfos_Action_Backflip(TransformWolfos* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.speed = 0.0f;
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }

    Math_ApproachZeroF(&this->actor.speed, 0.2f, BACKFLIP_DEACCELERATION);
}

void TransformWolfos_Action_Howl(TransformWolfos* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }

    if (!this->playedSfx && this->skelAnime.curFrame > 6.0f) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_CRY);
        this->playedSfx = 1;
    }
}

void TransformWolfos_Action_GetHit(TransformWolfos* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }
}

void TransformWolfos_Action_Fall(TransformWolfos* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
    }
    Math_SmoothStepToF(&this->actor.speed, 0.0f, 1.0f, 1.0f, 0.0f);

    SkelAnime_Update(&this->skelAnime);
}

void TransformWolfos_Action_Jump(TransformWolfos* this, PlayState* play) {
}

void TransformWolfos_SetupAction(TransformWolfos* this, PlayState* play, TransformWolfosActionFunc actionFunc) {
    this->actionFunc = actionFunc;

    Interface_SetDoAction(play, DO_ACTION_NONE);
    Interface_LoadActionLabelB(play, DO_ACTION_ATTACK);

    this->attackState = 0;
    this->shieldState = 0;
    this->queuedAttack = 0;
    this->playedSfx = 0;

    if (this->actionFunc == TransformWolfos_Action_Idle) {
        Animation_Change(&this->skelAnime, &gWolfosWaitingAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gWolfosWaitingAnim),
                         ANIMMODE_LOOP_INTERP, 4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Run) {
        Animation_Change(&this->skelAnime, &gWolfosRunningAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gWolfosRunningAnim),
                         ANIMMODE_LOOP_INTERP, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Attack) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gWolfosSlashingAnim, 1.0f, 0.0f, 15.0f, ANIMMODE_ONCE_INTERP, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Block) {
        this->actor.speed = 0.0f;
        this->shieldState = 1;
        Animation_Change(&this->skelAnime, &gWolfosBlockingAnim, 0.0f, 0.0f,
                         Animation_GetLastFrame(&gWolfosBlockingAnim), ANIMMODE_ONCE_INTERP, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Backflip) {
        this->actor.speed = BACKFLIP_SPEED;
        Actor_PlaySfx(&this->actor, NA_SE_EN_STAL_JUMP);
        Animation_MorphToPlayOnce(&this->skelAnime, &gWolfosBackflippingAnim, -3.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Howl) {
        this->actor.speed = 0.0f;
        Animation_Change(&this->skelAnime, &gWolfosRearingUpFallingOverAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gWolfosRearingUpFallingOverAnim), ANIMMODE_ONCE_INTERP, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_GetHit) {
        this->actor.speed = 0.0f;
        Animation_MorphToPlayOnce(&this->skelAnime, &gWolfosDamagedAnim, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Fall) {
        Animation_Change(&this->skelAnime, &gWolfosRunningAnim, 1.0f, 0.0f, 3.0f, ANIMMODE_ONCE_INTERP, -4.0f);
    } else if (this->actionFunc == TransformWolfos_Action_Jump) {
    }
}

void TransformWolfos_Init(Actor* thisx, PlayState* play) {
    TransformWolfos* this = (TransformWolfos*)thisx;

    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawCircle, 70.0f);

    Collider_InitJntSph(play, &this->clawsColliderSphere);
    Collider_SetJntSph(play, &this->clawsColliderSphere, thisx, &sClawsCollider, this->clawsColliderSphereElements);
    Collider_InitCylinder(play, &this->bodyColliderCylinder);
    Collider_SetCylinder(play, &this->bodyColliderCylinder, thisx, &sBodyCollider);
    Collider_InitCylinder(play, &this->tailColliderCylinder);
    Collider_SetCylinder(play, &this->tailColliderCylinder, thisx, &sTailCollider);

    SkelAnime_InitFlex(play, &this->skelAnime, &gWolfosNormalSkel, &gWolfosWaitingAnim, this->jointTable,
                       this->morphTable, WOLFOS_LIMB_MAX);
    Actor_SetScale(thisx, 0.0075f);

    thisx->colChkInfo.mass = MASS_HEAVY;
    thisx->colChkInfo.health = 30;
    thisx->gravity = -1.0f;
    thisx->speedCap = 10.0f;

    this->eyeIndex = 0;
    this->actor.speed = GET_PLAYER(play)->actor.speed;
    this->actor.room = -1;

    TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Idle);
}

void TransformWolfos_Destroy(Actor* thisx, PlayState* play) {
    TransformWolfos* this = (TransformWolfos*)thisx;

    Collider_DestroyJntSph(play, &this->clawsColliderSphere);
    Collider_DestroyCylinder(play, &this->bodyColliderCylinder);
    Collider_DestroyCylinder(play, &this->tailColliderCylinder);
}

void TransformWolfos_UpdateCollision(TransformWolfos* this, PlayState* play) {
    if (this->clawsColliderSphere.base.acFlags & AC_BOUNCED) {
        this->clawsColliderSphere.base.acFlags &= ~AC_BOUNCED;
        this->bodyColliderCylinder.base.acFlags &= ~AC_HIT;
        this->tailColliderCylinder.base.acFlags &= ~AC_HIT;
    } else if (this->clawsColliderSphere.base.atFlags & AT_HIT) {
        this->clawsColliderSphere.base.atFlags &= ~AT_HIT;
    } else if ((this->bodyColliderCylinder.base.acFlags & AC_HIT) ||
               (this->tailColliderCylinder.base.acFlags & AC_HIT)) {
        s32 damageFactor = this->tailColliderCylinder.base.acFlags & AC_HIT ? -2 : -1;

        this->bodyColliderCylinder.base.acFlags &= ~AC_HIT;
        this->tailColliderCylinder.base.acFlags &= ~AC_HIT;

        Actor_SetColorFilter(&this->actor, COLORFILTER_COLORFLAG_RED, 255, COLORFILTER_BUFFLAG_OPA, 12);

        play->damagePlayer(play, damageFactor * this->actor.colChkInfo.damage);
        this->invincibilityTimer = 30;

        if (gSaveContext.save.info.playerData.health == 0) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_DEAD);
            Enemy_StartFinishingBlow(play, &this->actor);
            Actor_Kill(&this->actor);
        }

        Actor_PlaySfx(&this->actor, NA_SE_EN_WOLFOS_DAMAGE);

        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_GetHit);
    }
}

void TransformWolfos_UpdateEyeBlink(TransformWolfos* this, PlayState* play) {
    if (this->eyeIndex == 0) {
        if ((Rand_ZeroOne() < 0.2f) && ((play->gameplayFrames % 4) == 0) && (this->actor.colorFilterTimer == 0)) {
            this->eyeIndex++;
        }
    } else {
        this->eyeIndex = (this->eyeIndex + 1) & 3;
    }
}

void TransformWolfos_CheckFalling(TransformWolfos* this, PlayState* play) {
    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actionFunc != TransformWolfos_Action_Fall)) {
        TransformWolfos_SetupAction(this, play, TransformWolfos_Action_Fall);
    }
}

void TransformWolfos_Update(Actor* thisx, PlayState* play) {
    TransformWolfos* this = (TransformWolfos*)thisx;

    Actor_SetPlayerLocation(&this->actor, play, 25.0f);
    Actor_SetFocus(&this->actor, 25.0f);

    TransformWolfos_UpdateCollision(this, play);

    Actor_HandleZTarget(&this->actor, play);
    Actor_MoveXZGravity(&this->actor);

    Actor_UpdateBgCheckInfo(play, &this->actor, 32.0f, 30.0f, 60.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 |
                                UPDBGCHECKINFO_FLAG_4);
    Actor_TriggerDynapolyIfPossible(&this->actor, play);
    Actor_CheckVoidOut(&this->actor, play);
    Actor_CheckExit(&this->actor, play);
    TransformWolfos_CheckFalling(this, play);

    this->actionFunc(this, play);

    Collider_UpdateCylinder(&this->actor, &this->bodyColliderCylinder);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyColliderCylinder.base);

    this->invincibilityTimer = DECR(this->invincibilityTimer);

    if ((gSaveContext.save.info.playerData.health > 0) && (this->actor.colorFilterTimer == 0) &&
        (this->invincibilityTimer == 0)) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->bodyColliderCylinder.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->tailColliderCylinder.base);
    }
    if (this->attackState > 0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->clawsColliderSphere.base);
    }
    if (this->shieldState > 0) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->clawsColliderSphere.base);
    }

    TransformWolfos_UpdateEyeBlink(this, play);
}

static void* sWolfosNormalEyeTextures[] = { gWolfosNormalEyeOpenTex, gWolfosNormalEyeHalfTex, gWolfosNormalEyeNarrowTex,
                                            gWolfosNormalEyeHalfTex };
static void* sWolfosWhiteEyeTextures[] = { gWolfosWhiteEyeOpenTex, gWolfosWhiteEyeHalfTex, gWolfosWhiteEyeNarrowTex,
                                           gWolfosWhiteEyeHalfTex };

void TransformWolfos_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx) {
    static Vec3f colliderVec = { 1200.0f, 0.0f, 0.0f };
    TransformWolfos* this = (TransformWolfos*)thisx;

    Collider_UpdateSpheres(limbIndex, &this->clawsColliderSphere);

    if (limbIndex == WOLFOS_LIMB_TAIL) {
        Vec3f colliderPos;

        Matrix_MultVec3f(&colliderVec, &colliderPos);
        this->tailColliderCylinder.dim.pos.x = colliderPos.x;
        this->tailColliderCylinder.dim.pos.y = colliderPos.y;
        this->tailColliderCylinder.dim.pos.z = colliderPos.z;
    }
}

void TransformWolfos_Draw(Actor* thisx, PlayState* play) {
    TransformWolfos* this = (TransformWolfos*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sWolfosNormalEyeTextures[this->eyeIndex]));
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          TransformWolfos_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}