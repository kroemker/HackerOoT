#ifndef OBJECT_H
#define OBJECT_H

#include "ultra64.h"
#include "dma.h"

struct PlayState;

#ifdef LEGACY_OBJECT_SYSTEM
// HackerOoT: dedicated object space for player transformation actors (see `Object_LoadTransform`).
// The slot index is deliberately outside the range of `ObjectContextLegacy.slots`.
#define TRANSFORM_OBJECT_SPACE (500 * 1024)
#define TRANSFORM_OBJECT_SLOT 64

typedef struct ObjectEntryLegacy {
    /* 0x00 */ s16 id;
    /* 0x04 */ void* segment;
    /* 0x08 */ DmaRequest dmaRequest;
    /* 0x28 */ OSMesgQueue loadQueue;
    /* 0x40 */ OSMesg loadMsg;
} ObjectEntryLegacy; // size = 0x44

typedef struct ObjectContextLegacy {
    /* 0x0000 */ void* spaceStart;
    /* 0x0004 */ void* spaceEnd;          // original name: "endSegment"
    /* 0x0008 */ u8 numEntries;           // total amount of used entries
    /* 0x0009 */ u8 numPersistentEntries; // amount of entries that won't be reused when loading a new object list (when
                                          // loading a new room)
    /* 0x000A */ u8 mainKeepSlot;         // "gameplay_keep" slot
    /* 0x000B */ u8 subKeepSlot;          // "gameplay_field_keep" or "gameplay_dangeon_keep" slot
    /* 0x000C */ ObjectEntryLegacy slots[19];
    // HackerOoT: object currently loaded into the transform space (-1 if none), see `Object_LoadTransform`
    s16 loadedTransformObjectId;
    // HackerOoT: the transform space is double-buffered (like the engine's own graphics pools) so
    // that loading a new transform object never DMAs over the buffer a still in-flight display
    // list (built on a previous frame, for the actor that just stopped using it) might still be
    // referencing on the RCP. `transformSpaceIndex` selects which of the two buffers is the one
    // currently in use by `loadedTransformObjectId`; `Object_LoadTransform` always DMAs into the
    // other one before switching over.
    void* transformSpaceStart[2];
    s32 transformSpaceIndex;
} ObjectContextLegacy;
#endif

#define MAX_OBJECT_ENTRIES 32
typedef struct ObjectEntry {
    /* 0x00 */ s16 id;
    /* 0x04 */ void* start;
    /* 0x08 */ void* end;
} ObjectEntry;

typedef struct ObjectContext {
    /* 0x0000 */ void* start;
    /* 0x0004 */ void* end;
    /* 0x0008 */ u8 numEntries; // total amount of used entries
    /* 0x0009 */ ObjectEntry entries[MAX_OBJECT_ENTRIES];
} ObjectContext;

#define DEFINE_OBJECT(_0, enum) enum,
#define DEFINE_OBJECT_EMPTY(_0, enum) enum,
#define DEFINE_OBJECT_UNSET(enum) enum,

typedef enum ObjectId {
#include "tables/object_table.h"
    /* 0x0194 */ OBJECT_ID_MAX
} ObjectId;

#undef DEFINE_OBJECT
#undef DEFINE_OBJECT_EMPTY
#undef DEFINE_OBJECT_UNSET

void Object_InitContext(PlayState* play, ObjectContext* objectCtx);
void* Object_LoadSync(ObjectContext* objectCtx, s16 objectId);
void Object_LoadAsync(ObjectContext* objectCtx, s16 objectId);
void Object_Unload(ObjectContext* objectCtx, s16 objectId);
s32 Object_IsLoaded(ObjectContext* objectCtx, s16 objectId);

extern u32 gObjectTableSize;
extern RomFile gObjectTable[OBJECT_ID_MAX];

#endif
