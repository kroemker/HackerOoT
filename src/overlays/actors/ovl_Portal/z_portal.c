#include "z_portal.h"

#include "gfx.h"
#include "gfx_setupdl.h"
#include "ichain.h"
#include "sfx.h"
#include "sys_matrix.h"
#include "tex_len.h"
#include "translation.h"
#include "z_lib.h"
#include "play_state.h"
#include "printf.h"
#include "player.h"
#include "save.h"
#include "effect.h"
#include "array_count.h"

#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED | ACTOR_FLAG_UPDATE_DURING_OCARINA)

#define WARP_RANGE 80.0f
#define X_WARP_OFFSET 2000.0f
#define WARP_SPEED 12.0f
#define WARP_SCALE_ADJUSTMENT 0.001f
#define WARP_SCALE 0
#define ORB_PORTAL_DISTANCE 50.0f
#define ORB_SIZE 12000

static s32 sTeleportableActors[] = { ACTOR_PLAYER, ACTOR_EN_ARROW, ACTOR_EN_BOM };

void Portal_Init(Actor* thisx, PlayState* play);
void Portal_Destroy(Actor* thisx, PlayState* play);
void Portal_Update(Actor* thisx, PlayState* play);
void Portal_Draw(Actor* thisx, PlayState* play);

void Portal_Action_Idle(Portal* this, PlayState* play);
void Portal_Action_MoveWarpOrb(Portal* this, PlayState* play);
void Portal_Action_CreateWarpOrb(Portal* this, PlayState* play);
void Portal_Action_PreEndWarp(Portal* this, PlayState* play);
void Portal_Action_EndWarp(Portal* this, PlayState* play);
void Portal_Action_JustWarped(Portal* this, PlayState* play);
void Portal_Action_Despawn(Portal* this, PlayState* play);

ActorProfile Portal_Profile = {
    /**/ ACTOR_PORTAL,
    /**/ ACTORCAT_DOOR,
    /**/ FLAGS,
    /**/ OBJECT_GAMEPLAY_KEEP,
    /**/ sizeof(Portal),
    /**/ Portal_Init,
    /**/ Portal_Destroy,
    /**/ Portal_Update,
    /**/ Portal_Draw,
};

void Portal_RemoveOldestIfNecessary(Portal* this, PlayState* play) {
    int numPortals = 0;
    Portal* oldestPortal = NULL;
    Actor* current = play->actorCtx.actorLists[ACTORCAT_DOOR].head;
    while (current != NULL) {
        if (current != &this->actor && current->id == ACTOR_PORTAL && current->parent == NULL &&
            ((Portal*)current)->actionFunc != Portal_Action_Despawn) {
            oldestPortal = (Portal*)current;
            numPortals++;
        }
        current = current->next;
    }

    if (numPortals > 1) {
        oldestPortal->timer = 30;
        oldestPortal->actionFunc = Portal_Action_Despawn;
    }
}

f32 Portal_CalcWarpOffset(Portal* this, PlayState* play) {
    f32 direction = this->world == ICE_WORLD ? 1.0f : -1.0f;
    return direction * X_WARP_OFFSET;
}

s32 Portal_IsYDominatingAxis(Vec3f* normal) {
    return ABS(normal->y) > ABS(normal->x) && ABS(normal->y) > ABS(normal->z);
}

void Portal_SpawnOrbEffect(Portal* this, PlayState* play, Vec3f* position, s16 scale) {
    Vec3f velocity = { 0, 0, 0 };
    Vec3f accel = { 0, 0, 0 };
    Color_RGBA8 primColor = { 255, 255, 255, 255 };
    Color_RGBA8 envColor = { 128, 0, 128, 255 };
    u32 i;

    for (i = 0; i < 6; i++) {
        EffectSsKiraKira_SpawnFocused(play, position, &velocity, &accel, &primColor, &envColor, scale, 24);
    }
}

s32 Portal_IsActorTeleportable(Actor* actor) {
    int j;
    for (j = 0; j < ARRAY_COUNT(sTeleportableActors); j++) {
        if (actor->id == sTeleportableActors[j]) {
            return true;
        }
    }
    return false;
}

Actor* Portal_GetWarpActor(Portal* this, PlayState* play) {
    s32 i;

    for (i = 0; i < ACTORCAT_MAX; i++) {
        Actor* current = play->actorCtx.actorLists[i].head;
        while (current != NULL) {
            if (Portal_IsActorTeleportable(current) &&
                Math_Vec3f_DistXYZ(&current->world.pos, &this->actor.world.pos) < WARP_RANGE) {
                return current;
            }
            current = current->next;
        }
    }
    return NULL;
}

void Portal_DimLighting(PlayState* play, f32 intensity) {
    s32 i;
    f32 colorScale;
    f32 fogScale;

    if (play->roomCtx.curRoom.type != ROOM_TYPE_BOSS) {
        intensity = CLAMP_MIN(intensity, 0.0f);
        intensity = CLAMP_MAX(intensity, 1.0f);
        fogScale = intensity - 0.2f;

        if (intensity < 0.2f) {
            fogScale = 0.0f;
        }

        play->envCtx.adjFogNear = (850.0f - play->envCtx.lightSettings.fogNear) * fogScale;

        if (intensity == 0.0f) {
            for (i = 0; i < ARRAY_COUNT(play->envCtx.adjFogColor); i++) {
                play->envCtx.adjFogColor[i] = 0;
            }
        } else {
            colorScale = intensity * 5.0f;

            if (colorScale > 1.0f) {
                colorScale = 1.0f;
            }

            for (i = 0; i < ARRAY_COUNT(play->envCtx.adjFogColor); i++) {
                play->envCtx.adjFogColor[i] = -(s16)(play->envCtx.lightSettings.fogColor[i] * colorScale);
            }
        }
    }
}

void Portal_SetupAction(Portal* this, PortalActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void Portal_Action_SpawnChildPortal(Portal* this, PlayState* play) {
    Portal* childPortal = (Portal*)Actor_SpawnAsChild(
        &play->actorCtx, &this->actor, play, ACTOR_PORTAL, this->actor.world.pos.x + Portal_CalcWarpOffset(this, play),
        this->actor.world.pos.y, this->actor.world.pos.z, this->actor.world.rot.x, this->actor.world.rot.y + 0x8000,
        this->actor.world.rot.z, 0x8000 | ((this->world + 1) % 2));

    Math_Vec3f_Copy(&childPortal->wallNormal, &this->wallNormal);

    this->actionFunc = Portal_Action_Idle;
}

void Portal_Action_Idle(Portal* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 targetSpeed = this->timer <= 25 ? -1.0f : 1.0f;
    Actor* warpActor = NULL;

    Math_ApproachF(&this->texSpeed, targetSpeed, 1.0f, 0.04f);
    Math_ApproachF(&this->alpha, 255.0f, 1.0f, 10.2f);

    if (DECR(this->timer) != 0) {
        return;
    }

    if ((warpActor = Portal_GetWarpActor(this, play)) != NULL) {
        PRINTF("Portal: Warping actor %p, id=0x%X\n", warpActor, warpActor->id);

        this->warpActor = warpActor;
        if (Portal_IsYDominatingAxis(&this->wallNormal)) {
            this->orbBasePos.x = this->actor.world.pos.x;
            this->orbBasePos.y = this->actor.world.pos.y + this->wallNormal.y * ORB_PORTAL_DISTANCE;
            this->orbBasePos.z = this->actor.world.pos.z;
        } else {
            this->orbBasePos.x = this->actor.world.pos.x + this->wallNormal.x * ORB_PORTAL_DISTANCE;
            this->orbBasePos.y = this->actor.world.pos.y;
            this->orbBasePos.z = this->actor.world.pos.z + this->wallNormal.z * ORB_PORTAL_DISTANCE;
        }
        Math_Vec3f_Copy(&this->warpActorScale, &this->warpActor->scale);
        this->warpActorGravity = this->warpActor->gravity;
        this->warpActorDrawFunc = this->warpActor->draw;
        this->timer = 15;
        this->actionFunc = Portal_Action_CreateWarpOrb;

        if (this->warpActor == &player->actor) {
            Cutscene_StartManual(play, &play->csCtx);
        }
        Actor_PlaySfx(&this->actor, NA_SE_EV_FANTOM_WARP_S);
    }
}

void Portal_Action_CreateWarpOrb(Portal* this, PlayState* play) {
    f32 orb_warp_actor_dist;

    Portal_SpawnOrbEffect(this, play, &this->orbBasePos, ORB_SIZE);

    Math_ApproachF(&this->warpActor->world.pos.x, this->orbBasePos.x, 0.2f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.y, this->orbBasePos.y, 0.2f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.z, this->orbBasePos.z, 0.2f, WARP_SPEED);

    Math_Vec3f_Copy(&this->warpActor->prevPos, &this->warpActor->world.pos);
    Math_Vec3f_Copy(&this->warpActor->home.pos, &this->warpActor->world.pos);
    this->warpActor->gravity = 0.0f;

    Math_ApproachF(&this->warpActor->scale.x, WARP_SCALE, 0.2f, WARP_SCALE_ADJUSTMENT);
    Math_ApproachF(&this->warpActor->scale.y, WARP_SCALE, 0.2f, WARP_SCALE_ADJUSTMENT);
    Math_ApproachF(&this->warpActor->scale.z, WARP_SCALE, 0.2f, WARP_SCALE_ADJUSTMENT);
    if (this->warpActor->scale.x < 0.0001f) {
        this->warpActor->draw = NULL;
    }

    if (this->timer >= 10) {
        Portal_DimLighting(play, (15 - this->timer) * 0.2f);
    }

    orb_warp_actor_dist = Math_Vec3f_DistXYZ(&this->warpActor->world.pos, &this->orbBasePos);
    // PRINTF("Portal: orbPos=(%.2f, %.2f, %.2f)\n", this->orbBasePos.x, this->orbBasePos.y, this->orbBasePos.z);
    // PRINTF("Portal: warpActor pos=(%.2f, %.2f, %.2f), scale=(%.2f, %.2f, %.2f)\n", this->warpActor->world.pos.x,
    //        this->warpActor->world.pos.y, this->warpActor->world.pos.z, this->warpActor->scale.x,
    //        this->warpActor->scale.y, this->warpActor->scale.z);
    PRINTF("Portal: orb_warp_actor_dist=%.2f\n", orb_warp_actor_dist);

    if (DECR(this->timer) == 0 && orb_warp_actor_dist < 25.0f) {
        this->actionFunc = Portal_Action_MoveWarpOrb;
    }
}

void Portal_Action_MoveWarpOrb(Portal* this, PlayState* play) {
    Math_ApproachF(&this->warpActor->world.pos.x, this->actor.world.pos.x, 0.1f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.y, this->actor.world.pos.y, 0.1f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.z, this->actor.world.pos.z, 0.1f, WARP_SPEED);

    Math_Vec3f_Copy(&this->warpActor->prevPos, &this->warpActor->world.pos);
    Math_Vec3f_Copy(&this->warpActor->home.pos, &this->warpActor->world.pos);
    this->warpActor->gravity = 0.0f;

    Portal_SpawnOrbEffect(this, play, &this->warpActor->world.pos, ORB_SIZE);

    if (Math_Vec3f_DistXYZ(&this->warpActor->world.pos, &this->actor.world.pos) < 25.0f) {
        Player* player = GET_PLAYER(play);
        Portal* correspondingPortal =
            this->type == PORTAL_TYPE_PARENT ? (Portal*)this->actor.child : (Portal*)this->actor.parent;
        f32 offset = Portal_CalcWarpOffset(this, play);

        this->warpActor->world.pos.x += offset;
        this->warpActor->prevPos.x += offset;
        this->warpActor->home.pos.x += offset;
        this->warpActor->shape.rot.y += 0x8000;

        if (this->warpActor == &player->actor) {
            play->mainCamera.eye.x += offset;
            play->mainCamera.eyeNext.x += offset;
            play->mainCamera.at.x += offset;
            gSaveContext.save.world = gSaveContext.save.world == ICE_WORLD ? FIRE_WORLD : ICE_WORLD;
        }

        if (Portal_IsYDominatingAxis(&this->wallNormal)) {
            this->orbBasePos.x = correspondingPortal->actor.world.pos.x;
            this->orbBasePos.y =
                correspondingPortal->actor.world.pos.y + correspondingPortal->wallNormal.y * ORB_PORTAL_DISTANCE;
            this->orbBasePos.z = correspondingPortal->actor.world.pos.z;
        } else {
            this->orbBasePos.x =
                correspondingPortal->actor.world.pos.x + correspondingPortal->wallNormal.x * ORB_PORTAL_DISTANCE;
            this->orbBasePos.y = correspondingPortal->actor.world.pos.y;
            this->orbBasePos.z =
                correspondingPortal->actor.world.pos.z + correspondingPortal->wallNormal.z * ORB_PORTAL_DISTANCE;
        }

        if (this->actor.parent != NULL) {
            ((Portal*)this->actor.parent)->actionFunc = Portal_Action_JustWarped;
            ((Portal*)this->actor.parent)->warpActor = this->warpActor;
        }
        if (this->actor.child != NULL) {
            ((Portal*)this->actor.child)->actionFunc = Portal_Action_JustWarped;
            ((Portal*)this->actor.child)->warpActor = this->warpActor;
        }

        this->timer = 15;
        this->actionFunc = Portal_Action_PreEndWarp;
    }
}

void Portal_Action_PreEndWarp(Portal* this, PlayState* play) {
    Math_ApproachF(&this->warpActor->world.pos.x, this->orbBasePos.x, 0.1f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.y, this->orbBasePos.y, 0.1f, WARP_SPEED);
    Math_ApproachF(&this->warpActor->world.pos.z, this->orbBasePos.z, 0.1f, WARP_SPEED);
    Portal_SpawnOrbEffect(this, play, &this->warpActor->world.pos, ORB_SIZE);
    this->warpActor->gravity = 0.0f;

    PRINTF("Portal: pre end warp: timer=%d\n", this->timer);
    if (DECR(this->timer) == 0) {
        this->timer = 15;
        this->actionFunc = Portal_Action_EndWarp;
    }
}

void Portal_Action_EndWarp(Portal* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f orbPos;

    Math_ApproachF(&this->warpActor->scale.x, this->warpActorScale.x, 0.2f, WARP_SCALE_ADJUSTMENT);
    Math_ApproachF(&this->warpActor->scale.y, this->warpActorScale.y, 0.2f, WARP_SCALE_ADJUSTMENT);
    Math_ApproachF(&this->warpActor->scale.z, this->warpActorScale.z, 0.2f, WARP_SCALE_ADJUSTMENT);
    Math_ApproachF(&this->warpActor->gravity, this->warpActorGravity, 0.2f, 0.2f);

    Math_Vec3f_Copy(&orbPos, &this->warpActor->world.pos);
    orbPos.y = this->actor.world.pos.y;

    if (this->timer >= 15) {
        Portal_SpawnOrbEffect(this, play, &orbPos, ORB_SIZE * (1.0f / this->timer));
        this->warpActor->draw = this->warpActorDrawFunc;
    }

    Portal_DimLighting(play, this->timer * (1 / 15.0f));

    if (DECR(this->timer) == 0) {
        Math_Vec3f_Copy(&this->warpActor->scale, &this->warpActorScale);
        this->warpActor->gravity = this->warpActorGravity;
        this->warpActor->draw = this->warpActorDrawFunc;

        if (this->warpActor == &player->actor) {
            Cutscene_StopManual(play, &play->csCtx);
        }
        this->warpActor = NULL;
        this->actionFunc = Portal_Action_Idle;
        Portal_DimLighting(play, 0);
    }
}

void Portal_Action_JustWarped(Portal* this, PlayState* play) {
    if (this->warpActor == NULL ||
        (Math_Vec3f_DistXYZ(&this->warpActor->world.pos, &this->actor.world.pos) > WARP_RANGE * 1.5f)) {
        this->warpActor = NULL;
        this->actionFunc = Portal_Action_Idle;
    }
}

void Portal_Action_Despawn(Portal* this, PlayState* play) {
    if (this->actor.child != NULL && ((Portal*)this->actor.child)->actionFunc != Portal_Action_Despawn) {
        ((Portal*)this->actor.child)->actionFunc = Portal_Action_Despawn;
    }

    Math_ApproachZeroF(&this->texSpeed, 1.0f, 0.04f);
    Math_ApproachZeroF(&this->alpha, 1.0f, 10.2f);

    if (DECR(this->timer) == 0) {
        Actor_Kill(&this->actor);
    }
}

void Portal_Init(Actor* thisx, PlayState* play) {
    Portal* this = (Portal*)thisx;

    this->type = (this->actor.params >> 15) & 1;
    this->world = this->actor.params & 0xFF;

    Actor_SetScale(&this->actor, 4.0f);
    this->actor.scale.z = 1.0f;
    this->timer = 30;
    if (this->type == PORTAL_TYPE_CHILD) {
        this->actor.shape.rot.y += 0x8000;
    }

    Portal_RemoveOldestIfNecessary(this, play);

    this->actionFunc = this->type == PORTAL_TYPE_PARENT ? Portal_Action_SpawnChildPortal : Portal_Action_Idle;
}

void Portal_Destroy(Actor* thisx, PlayState* play) {
    Portal* this = (Portal*)thisx;
}

void Portal_Update(Actor* thisx, PlayState* play) {
    Portal* this = (Portal*)thisx;

    this->tex1X += 25.0f * this->texSpeed;
    this->tex1Y -= 40.0f * this->texSpeed;
    this->tex2X += 5.0f * this->texSpeed;
    this->tex2Y -= 30.0f * this->texSpeed;

    this->actionFunc(this, play);
}

void Portal_Draw(Actor* thisx, PlayState* play) {
    Portal* this = (Portal*)thisx;

    OPEN_DISPS(play->state.gfxCtx, __FILE__, __LINE__);

    Gfx_SetupDL_25Xlu(play->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, (u8)this->alpha);
    gDPSetEnvColor(POLY_XLU_DISP++, 90, 50, 95, (s8)(this->alpha * 0.5f));
    gDPPipeSync(POLY_XLU_DISP++);
    MATRIX_FINALIZE_AND_LOAD(POLY_XLU_DISP++, play->state.gfxCtx, __LINE__, __FILE__);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, G_TX_RENDERTILE, (s16)this->tex1X, (s16)this->tex1Y, 0x40, 0x40, 1,
                                (s16)this->tex2X, (s16)this->tex2Y, 0x40, 0x40));
    gSPDisplayList(POLY_XLU_DISP++, gPortalDL);

    CLOSE_DISPS(play->state.gfxCtx, __FILE__, __LINE__);
}
