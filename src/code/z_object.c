#include "object.h"
#include "printf.h"
#include "play_state.h"
#include "segmented_address.h"

ObjectEntry* Object_CreateEntry(ObjectContext* objectCtx, u32 size);

void Object_InitContext(PlayState* play, ObjectContext* objectCtx) {
    objectCtx->start = GAME_STATE_ALLOC(&play->state, OBJECT_BANK_SIZE, __FILE__, __LINE__);
    objectCtx->end = (void*)((uintptr_t)objectCtx->start + OBJECT_BANK_SIZE);

    PRINTF_COLOR_GREEN();
    PRINTF("[OBJECT_SYSTEM] start=%08X end=%08X size=%08X\n", objectCtx->start, objectCtx->end, OBJECT_BANK_SIZE);
    PRINTF_RST();

    void* gameplayKeepSpaceStart = Object_LoadSync(objectCtx, OBJECT_GAMEPLAY_KEEP);
    gSegments[4] = OS_K0_TO_PHYSICAL(gameplayKeepSpaceStart);
}

void* Object_LoadSync(ObjectContext* objectCtx, s16 objectId) {
    u32 size = gObjectTable[objectId].vromEnd - gObjectTable[objectId].vromStart;

    PRINTF("[OBJECT_SYSTEM] loading object sync: id=%04X(%d) size=%d bytes\n", objectId, objectId, size);

    ObjectEntry* newEntry = Object_CreateEntry(objectCtx, size);

    DMA_REQUEST_SYNC(newEntry->start, gObjectTable[objectId].vromStart, size, __FILE__, __LINE__);

    PRINTF("[OBJECT_SYSTEM] loaded object sync: id=%04X(%d) size=%d bytes memory=%08X\n", objectId, objectId, size,
           newEntry->start);

    return newEntry;
}

void Object_LoadAsync(ObjectContext* objectCtx, s16 objectId) {
    // TODO implement
}

void Object_Unload(ObjectContext* objectCtx, s16 objectId) {
    s32 i = 0;
    while (i < objectCtx->numEntries) {
        if (objectCtx->entries[i].id == objectId) {
            if (i != objectCtx->numEntries - 1) {
                memmove(&objectCtx->entries[i], &objectCtx->entries[i + 1],
                        (objectCtx->numEntries - i - 1) * sizeof(ObjectEntry));
            }
            objectCtx->numEntries--;
            return;
        }
    }
}

s32 Object_IsLoaded(ObjectContext* objectCtx, s16 objectId) {
    s32 i = 0;
    while (i < objectCtx->numEntries) {
        if (objectCtx->entries[i].id == objectId) {
            return true;
        }
    }
    return false;
}

ObjectEntry* Object_CreateEntry(ObjectContext* objectCtx, u32 size) {
    s32 i;
    void* previousEntrySpaceEnd;
    ObjectEntry* newEntry;

    if (objectCtx->numEntries >= MAX_OBJECT_ENTRIES) {
        PRINTF_COLOR_RED();
        PRINTF("[OBJECT_SYSTEM] Unable to create new object entry, max object entries reached!\n");
        PRINTF_RST();
        return NULL;
    }

    if (objectCtx->numEntries == 0) {
        newEntry = &objectCtx->entries[objectCtx->numEntries];
        newEntry->start = objectCtx->start;
        newEntry->end = (void*)((uintptr_t)newEntry->start + size);
        return newEntry;
    }

    i = 0;
    previousEntrySpaceEnd = objectCtx->start;
    while (i < objectCtx->numEntries) {
        ObjectEntry* current = &objectCtx->entries[i];
        u32 freeBetween = ((u32)current->start) - (u32)previousEntrySpaceEnd;
        if (freeBetween >= size) {
            break;
        }
        previousEntrySpaceEnd = current->end;
        i++;
    }

    if (i < objectCtx->numEntries) {
        memmove(&objectCtx->entries[i + 1], &objectCtx->entries[i], (objectCtx->numEntries - i) * sizeof(ObjectEntry));
    }

    newEntry = &objectCtx->entries[i];
    newEntry->start = previousEntrySpaceEnd;
    newEntry->end = (void*)((uintptr_t)newEntry->start + size);

    objectCtx->numEntries++;

    return newEntry;
}