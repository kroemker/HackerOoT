#include "hm_jam_dung_scene.h"

/**
 * Header Child Day (Default)
*/
SceneCmd hm_jam_dung_scene_header00[] = {
    SCENE_CMD_COL_HEADER(&hm_jam_dung_scene_collisionHeader),
    SCENE_CMD_ROOM_LIST(1, hm_jam_dung_scene_roomList),
    SCENE_CMD_SOUND_SETTINGS(0x00, 0x00, NA_BGM_ICE_CAVERN),
    SCENE_CMD_MISC_SETTINGS(0x00, 0x00),
    SCENE_CMD_SPECIAL_FILES(0x00, OBJECT_GAMEPLAY_DANGEON_KEEP),
    SCENE_CMD_SKYBOX_SETTINGS(0x00, 0x00, LIGHT_MODE_TIME),
    SCENE_CMD_ENV_LIGHT_SETTINGS(4, hm_jam_dung_scene_header00_lightSettings),
    SCENE_CMD_ENTRANCE_LIST(hm_jam_dung_scene_header00_entranceList),
    SCENE_CMD_SPAWN_LIST(1, hm_jam_dung_scene_header00_playerEntryList),
    SCENE_CMD_END(),
};

RomFile hm_jam_dung_scene_roomList[] = {
    { (uintptr_t)_hm_jam_dung_room_0SegmentRomStart, (uintptr_t)_hm_jam_dung_room_0SegmentRomEnd },
};

ActorEntry hm_jam_dung_scene_header00_playerEntryList[] = {
    // Link / Spawn point
    {
        /* Actor ID   */ ACTOR_PLAYER,
        /* Position   */ { 0, -120, 218 },
        /* Rotation   */ { DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000), DEG_TO_BINANG(0.000) },
        /* Parameters */ (0x0F00 | ((0xFF & 0x00FF)))
    },
};

Spawn hm_jam_dung_scene_header00_entranceList[] = {
    // { Spawn Actor List Index, Room Index }
    { 0, 0 },
};

EnvLightSettings hm_jam_dung_scene_header00_lightSettings[4] = {
    // Dawn Lighting
    {
        {    70,    45,    57 },   // Ambient Color
        {    73,   -73,    73 },   // Diffuse0 Direction
        {   180,   154,   138 },   // Diffuse0 Color
        {   -73,    73,   -73 },   // Diffuse1 Direction
        {    20,    20,    60 },   // Diffuse1 Color
        {   140,   120,   100 },   // Fog Color
        ((1 << 10) | 993),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Day Lighting
    {
        {   105,    90,    90 },   // Ambient Color
        {    73,   -73,    73 },   // Diffuse0 Direction
        {   255,   255,   240 },   // Diffuse0 Color
        {   -73,    73,   -73 },   // Diffuse1 Direction
        {    50,    50,    90 },   // Diffuse1 Color
        {   100,   100,   120 },   // Fog Color
        ((1 << 10) | 996),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Dusk Lighting
    {
        {   120,    90,     0 },   // Ambient Color
        {    73,   -73,    73 },   // Diffuse0 Direction
        {   250,   135,    50 },   // Diffuse0 Color
        {   -73,    73,   -73 },   // Diffuse1 Direction
        {    30,    30,    60 },   // Diffuse1 Color
        {   120,    70,    50 },   // Fog Color
        ((1 << 10) | 995),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
    // Night Lighting
    {
        {    40,    70,   100 },   // Ambient Color
        {    73,   -73,    73 },   // Diffuse0 Direction
        {    20,    20,    35 },   // Diffuse0 Color
        {   -73,    73,   -73 },   // Diffuse1 Direction
        {    50,    50,   100 },   // Diffuse1 Color
        {     0,     0,    30 },   // Fog Color
        ((1 << 10) | 992),         // Blend Rate & Fog Near
        12800,                     // Fog Far
    },
};

SurfaceType hm_jam_dung_scene_polygonTypes[1] = {
    { SURFACETYPE0(0, 0, 0x00, 0, 0x00, 0x00, 0, 0), SURFACETYPE1(0x00, 0x00, 0, 0, 0, 0, 0, 0) },
};

Vec3s hm_jam_dung_scene_vertices[16] = {
    {   -300,   -120,    300 },
    {    300,   -120,    300 },
    {    300,   -120,   -300 },
    {   -300,   -120,   -300 },
    {    300,    160,    300 },
    {    300,    160,   -300 },
    {   -300,    160,   -300 },
    {   -300,    160,    300 },
    {   1700,   -120,    300 },
    {   2300,   -120,    300 },
    {   2300,   -120,   -300 },
    {   1700,   -120,   -300 },
    {   2300,    160,    300 },
    {   2300,    160,   -300 },
    {   1700,    160,   -300 },
    {   1700,    160,    300 },
};

CollisionPoly hm_jam_dung_scene_polygons[20] = {
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(2), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 120 },
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(3), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 120 },
    { 0, COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(5), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 300 },
    { 0, COLPOLY_VTX(1, COLPOLY_IGNORE_NONE), COLPOLY_VTX(5, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(2), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 300 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(6, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(7), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 300 },
    { 0, COLPOLY_VTX(3, COLPOLY_IGNORE_NONE), COLPOLY_VTX(7, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(0), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 300 },
    { 0, COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX(5, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(6), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 300 },
    { 0, COLPOLY_VTX(2, COLPOLY_IGNORE_NONE), COLPOLY_VTX(6, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(3), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 300 },
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(7, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(4), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 300 },
    { 0, COLPOLY_VTX(0, COLPOLY_IGNORE_NONE), COLPOLY_VTX(4, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(1), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 300 },
    { 0, COLPOLY_VTX(8, COLPOLY_IGNORE_NONE), COLPOLY_VTX(9, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(10), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 120 },
    { 0, COLPOLY_VTX(8, COLPOLY_IGNORE_NONE), COLPOLY_VTX(10, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(11), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(7.549790126404332e-08) }, 120 },
    { 0, COLPOLY_VTX(9, COLPOLY_IGNORE_NONE), COLPOLY_VTX(12, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(13), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 2300 },
    { 0, COLPOLY_VTX(9, COLPOLY_IGNORE_NONE), COLPOLY_VTX(13, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(10), { COLPOLY_SNORMAL(-1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 2300 },
    { 0, COLPOLY_VTX(11, COLPOLY_IGNORE_NONE), COLPOLY_VTX(14, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(15), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 63836 },
    { 0, COLPOLY_VTX(11, COLPOLY_IGNORE_NONE), COLPOLY_VTX(15, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(8), { COLPOLY_SNORMAL(1.0), COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(0.0) }, 63836 },
    { 0, COLPOLY_VTX(10, COLPOLY_IGNORE_NONE), COLPOLY_VTX(13, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(14), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 300 },
    { 0, COLPOLY_VTX(10, COLPOLY_IGNORE_NONE), COLPOLY_VTX(14, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(11), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(-7.549790126404332e-08), COLPOLY_SNORMAL(1.0) }, 300 },
    { 0, COLPOLY_VTX(8, COLPOLY_IGNORE_NONE), COLPOLY_VTX(15, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(12), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 300 },
    { 0, COLPOLY_VTX(8, COLPOLY_IGNORE_NONE), COLPOLY_VTX(12, COLPOLY_IGNORE_NONE), COLPOLY_VTX_INDEX(9), { COLPOLY_SNORMAL(0.0), COLPOLY_SNORMAL(7.549790126404332e-08), COLPOLY_SNORMAL(-1.0) }, 300 },
};

CollisionHeader hm_jam_dung_scene_collisionHeader = {
    { -300, -120, -300 },
    { 2300, 160, 300 },
    ARRAY_COUNT(hm_jam_dung_scene_vertices), hm_jam_dung_scene_vertices,
    ARRAY_COUNT(hm_jam_dung_scene_polygons), hm_jam_dung_scene_polygons,
    hm_jam_dung_scene_polygonTypes,
    NULL,
    0, NULL
};

