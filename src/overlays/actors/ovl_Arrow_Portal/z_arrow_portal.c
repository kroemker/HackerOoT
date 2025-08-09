#include "z_arrow_portal.h"
#include "overlays/actors/ovl_En_Arrow/z_en_arrow.h"

#include "gfx.h"
#include "gfx_setupdl.h"
#include "ichain.h"
#include "sfx.h"
#include "sys_matrix.h"
#include "tex_len.h"
#include "translation.h"
#include "z_lib.h"
#include "play_state.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED | ACTOR_FLAG_UPDATE_DURING_OCARINA)

void ArrowPortal_Init(Actor* thisx, PlayState* play);
void ArrowPortal_Destroy(Actor* thisx, PlayState* play);
void ArrowPortal_Update(Actor* thisx, PlayState* play);
void ArrowPortal_Draw(Actor* thisx, PlayState* play);

void ArrowPortal_Charge(ArrowPortal* this, PlayState* play);
void ArrowPortal_Fly(ArrowPortal* this, PlayState* play);
void ArrowPortal_Hit(ArrowPortal* this, PlayState* play);

#define s1Tex_WIDTH 64
#define s1Tex_HEIGHT 32
static u64 s1Tex[TEX_LEN(u64, s1Tex_WIDTH, s1Tex_HEIGHT, 8)] = {
#include "assets/overlays/ovl_Arrow_Light/s1Tex.i8.inc.c"
    // #include "assets/overlays/ovl_Arrow_Ice/s1Tex.i8.inc.c"
};

#define s2Tex_WIDTH 64
#define s2Tex_HEIGHT 32
static u64 s2Tex[TEX_LEN(u64, s2Tex_WIDTH, s2Tex_HEIGHT, 8)] = {
// #include "assets/overlays/ovl_Arrow_Light/s2Tex.i8.inc.c"
#include "assets/overlays/ovl_Arrow_Fire/s2Tex.i8.inc.c"
};

static Vtx sVtx[] = {
#include "assets/overlays/ovl_Arrow_Light/sVtx.inc.c"
};

static Gfx sMaterialDL[22] = {
#include "assets/overlays/ovl_Arrow_Light/sMaterialDL.inc.c"
};

static Gfx sModelDL[24] = {
#include "assets/overlays/ovl_Arrow_Light/sModelDL.inc.c"
};

ActorProfile Arrow_Portal_Profile = {
    /**/ ACTOR_ARROW_PORTAL,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(ArrowPortal),
    /**/ ArrowPortal_Init,
    /**/ ArrowPortal_Destroy,
    /**/ ArrowPortal_Update,
    /**/ ArrowPortal_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(cullingVolumeDistance, 2000, ICHAIN_STOP),
};

void ArrowPortal_SetupAction(ArrowPortal* this, ArrowPortalActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArrowPortal_Init(Actor* thisx, PlayState* play) {
    ArrowPortal* this = (ArrowPortal*)thisx;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->radius = 0;
    this->unk_160 = 1.0f;
    ArrowPortal_SetupAction(this, ArrowPortal_Charge);
    Actor_SetScale(&this->actor, 0.01f);
    this->alpha = 130;
    this->timer = 0;
    this->unk_164 = 0.0f;
}

void ArrowPortal_Destroy(Actor* thisx, PlayState* play) {
    Magic_Reset(play);
    LOG_STRING_T("消滅", "Disappearance", "../z_arrow_portal.c", 403);
}

void ArrowPortal_Charge(ArrowPortal* this, PlayState* play) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;

    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->radius < 10) {
        this->radius += 1;
    }
    // copy position and rotation from arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;

    Actor_PlaySfx_Flagged(&this->actor, NA_SE_PL_ARROW_CHARGE_LIGHT - SFX_FLAG);

    // if arrow has no parent, player has fired the arrow
    if (arrow->actor.parent == NULL) {
        this->unkPos = this->actor.world.pos;
        this->radius = 10;
        ArrowPortal_SetupAction(this, ArrowPortal_Fly);
        this->alpha = 255;
    }
}

void Arrow_Portal_80869E6C(Vec3f* unkPos, Vec3f* lightPos, f32 scale) {
    unkPos->x += ((lightPos->x - unkPos->x) * scale);
    unkPos->y += ((lightPos->y - unkPos->y) * scale);
    unkPos->z += ((lightPos->z - unkPos->z) * scale);
}

void ArrowPortal_Hit(ArrowPortal* this, PlayState* play) {
    f32 scale;
    f32 offset;
    u16 timer;

    if (this->actor.projectedW < 50.0f) {
        scale = 10.0f;
    } else {
        if (950.0f < this->actor.projectedW) {
            scale = 310.0f;
        } else {
            scale = this->actor.projectedW;
            scale = ((scale - 50.0f) * (1.0f / 3.0f)) + 10.0f;
        }
    }

    timer = this->timer;
    if (timer != 0) {
        this->timer--;

        if (this->timer >= 8) {
            offset = ((this->timer - 8) * (1.0f / 24.0f));
            offset = SQ(offset);
            this->radius = (((1.0f - offset) * scale) + 10.0f);
            this->unk_160 += ((2.0f - this->unk_160) * 0.1f);
            if (this->timer < 16) {
                this->alpha = ((this->timer * 0x23) - 0x118);
            }
        }
    }

    if (this->timer >= 9) {
        if (this->unk_164 < 1.0f) {
            this->unk_164 += 0.25f;
        }
    } else {
        if (this->unk_164 > 0.0f) {
            this->unk_164 -= 0.125f;
        }
    }

    if (this->timer < 8) {
        this->alpha = 0;
    }

    if (this->timer == 0) {
        this->timer = 255;
        Actor_Kill(&this->actor);
    }
}

void ArrowPortal_Fly(ArrowPortal* this, PlayState* play) {
    EnArrow* arrow = (EnArrow*)this->actor.parent;
    f32 distanceScaled;
    s32 pad;

    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        Actor_Kill(&this->actor);
        return;
    }
    // copy position and rotation from parent arrow
    this->actor.world.pos = arrow->actor.world.pos;
    this->actor.shape.rot = arrow->actor.shape.rot;
    distanceScaled = Math_Vec3f_DistXYZ(&this->unkPos, &this->actor.world.pos) * (1.0f / 24.0f);
    this->unk_160 = distanceScaled;
    if (distanceScaled < 1.0f) {
        this->unk_160 = 1.0f;
    }
    Arrow_Portal_80869E6C(&this->unkPos, &this->actor.world.pos, 0.05f);

    if (arrow->hitFlags & 1) {
        ArrowPortal_SetupAction(this, ArrowPortal_Hit);
        this->timer = 32;
        this->alpha = 255;
    } else if (arrow->timer < 34) {
        if (this->alpha < 35) {
            Actor_Kill(&this->actor);
        } else {
            this->alpha -= 0x19;
        }
    }
}

void ArrowPortal_Update(Actor* thisx, PlayState* play) {
    ArrowPortal* this = (ArrowPortal*)thisx;

    // See `ACTOROVL_ALLOC_ABSOLUTE`
    //! @bug This condition is too broad, the actor will also be killed by warp songs. But warp songs do not use an
    //! actor which uses `ACTOROVL_ALLOC_ABSOLUTE`. There is no reason to kill the actor in this case.
    if ((play->msgCtx.msgMode == MSGMODE_OCARINA_CORRECT_PLAYBACK) || (play->msgCtx.msgMode == MSGMODE_SONG_PLAYED)) {
        Actor_Kill(&this->actor);
        return;
    }

    this->actionFunc(this, play);
}

void ArrowPortal_Draw(Actor* thisx, PlayState* play) {
    ArrowPortal* this = (ArrowPortal*)thisx;
    s32 pad;
    u32 stateFrames = play->state.frames;
    EnArrow* arrow = (EnArrow*)this->actor.parent;
    Actor* transform;

    if ((arrow == NULL) || (arrow->actor.update == NULL)) {
        return;
    }

    if (this->timer >= 255) {
        return;
    }

    transform = (arrow->hitFlags & 2) ? &this->actor : &arrow->actor;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Matrix_Translate(transform->world.pos.x, transform->world.pos.y, transform->world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(BINANG_TO_RAD(transform->shape.rot.y), MTXMODE_APPLY);
    Matrix_RotateX(BINANG_TO_RAD(transform->shape.rot.x), MTXMODE_APPLY);
    Matrix_RotateZ(BINANG_TO_RAD(transform->shape.rot.z), MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

    // Draw effect over the screen when arrow hits
    if (this->unk_164 > 0) {
        POLY_XLU_DISP = Gfx_SetupDL_57(POLY_XLU_DISP);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (s32)(10.0f * this->unk_164) & 0xFF, 0,
                        (s32)(20.0f * this->unk_164) & 0xFF, (s32)(150.0f * this->unk_164) & 0xFF);
        gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_DISABLE);
        gDPSetColorDither(POLY_XLU_DISP++, G_CD_DISABLE);
        gDPFillRectangle(POLY_XLU_DISP++, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    }

    // Draw light on the arrow
    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 200, 50, 200, this->alpha);
    gDPSetEnvColor(POLY_XLU_DISP++, 128, 0, 128, 128);
    Matrix_RotateZYX(0x4000, 0x0, 0x0, MTXMODE_APPLY);
    if (this->timer != 0) {
        Matrix_Translate(0.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    } else {
        Matrix_Translate(0.0f, 1500.0f, 0.0f, MTXMODE_APPLY);
    }
    Matrix_Scale(this->radius * 0.2f, this->unk_160 * 4.0f, this->radius * 0.2f, MTXMODE_APPLY);
    Matrix_Translate(0.0f, -700.0f, 0.0f, MTXMODE_APPLY);
    MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx, __FILE__, __LINE__);
    gSPDisplayList(POLY_XLU_DISP++, sMaterialDL);
    gSPDisplayList(POLY_XLU_DISP++,
                   Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, 511 - (stateFrames * 5) % 512, 0, 4, 32, 1,
                                    511 - (stateFrames * 10) % 512, 511 - (stateFrames * 30) % 512, 8, 16));
    gSPDisplayList(POLY_XLU_DISP++, sModelDL);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}
