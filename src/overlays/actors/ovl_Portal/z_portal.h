#ifndef Z_PORTAL_H
#define Z_PORTAL_H

#include "ultra64.h"
#include "actor.h"

struct Portal;

typedef void (*PortalActionFunc)(struct Portal*, struct PlayState*);

typedef enum PortalType {
    PORTAL_TYPE_PARENT,
    PORTAL_TYPE_CHILD
} PortalType;

typedef struct Portal {
    Actor actor;
    f32 tex1X;
    f32 tex1Y;
    f32 tex2X;
    f32 tex2Y;
    f32 texSpeed;
    f32 alpha;
    s32 timer;
    u8 world;
    PortalType type;
    Vec3f wallNormal;
    Actor* warpActor;
    Vec3f warpActorScale;
    f32 warpActorGravity;
    void* warpActorDrawFunc;
    Vec3f orbBasePos;
    PortalActionFunc actionFunc;
} Portal;

#endif
