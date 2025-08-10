#ifndef HM_JAM_DUNG_SCENE_H
#define HM_JAM_DUNG_SCENE_H

#include "ultra64.h"
#include "romfile.h"
#include "array_count.h"
#include "sequence.h"
#include "actor_profile.h"
#include "bgcheck.h"
#include "camera.h"
#include "cutscene.h"
#include "cutscene_commands.h"
#include "environment.h"
#include "z_math.h"
#include "object.h"
#include "ocarina.h"
#include "path.h"
#include "player.h"
#include "room.h"
#include "scene.h"

// For older decomp versions
#ifndef SCENE_CMD_PLAYER_ENTRY_LIST
#define SCENE_CMD_PLAYER_ENTRY_LIST(length, playerEntryList) \
    { SCENE_CMD_ID_SPAWN_LIST, length, CMD_PTR(playerEntryList) }
#undef SCENE_CMD_SPAWN_LIST
#define SCENE_CMD_SPAWN_LIST(spawnList) \
    { SCENE_CMD_ID_ENTRANCE_LIST, 0, CMD_PTR(spawnList) }
#endif

extern SceneCmd hm_jam_dung_scene_header00[];
extern RomFile hm_jam_dung_scene_roomList[];
extern u8 _hm_jam_dung_room_0SegmentRomStart[];
extern u8 _hm_jam_dung_room_0SegmentRomEnd[];
extern u8 _hm_jam_dung_room_1SegmentRomStart[];
extern u8 _hm_jam_dung_room_1SegmentRomEnd[];
extern ActorEntry hm_jam_dung_scene_header00_playerEntryList[];
extern Spawn hm_jam_dung_scene_header00_entranceList[];
extern TransitionActorEntry hm_jam_dung_scene_header00_transitionActors[];
extern EnvLightSettings hm_jam_dung_scene_header00_lightSettings[4];
extern SurfaceType hm_jam_dung_scene_polygonTypes[2];
extern Vec3s hm_jam_dung_scene_vertices[64];
extern CollisionPoly hm_jam_dung_scene_polygons[104];
extern CollisionHeader hm_jam_dung_scene_collisionHeader;
extern SceneCmd hm_jam_dung_room_0_header00[];
extern s16 hm_jam_dung_room_0_header00_objectList[];
extern ActorEntry hm_jam_dung_room_0_header00_actorList[];
extern Gfx hm_jam_dung_room_0_shapeHeader_entry_0_opaque[];
extern Gfx hm_jam_dung_room_0_shapeHeader_entry_0_transparent[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_room_7_000040E8_Tex_i8_i8[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_room_4_00005670_Tex_rgba16_ci8[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_room_4_00005670_Tex_rgba16_pal_rgba16[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_room_18_00002F78_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_ci4[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_room_18_00002F78_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_pal_rgba16[];
extern Vtx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque_vtx_0[24];
extern Gfx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque_tri_0[];
extern Vtx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque_vtx_1[24];
extern Gfx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque_tri_1[];
extern Vtx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Transparent_vtx_cull[8];
extern Vtx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Transparent_vtx_0[8];
extern Gfx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Transparent_tri_0[];
extern Gfx mat_hm_jam_dung_room_0_dl_wall_mat_001_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_wall_mat_001_layerOpaque[];
extern Gfx mat_hm_jam_dung_room_0_dl_ice_mat_layerTransparent[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_ice_mat_layerTransparent[];
extern Gfx mat_hm_jam_dung_room_0_dl_stone_mat_001_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_stone_mat_001_layerOpaque[];
extern Gfx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Opaque[];
extern Gfx hm_jam_dung_room_0_dl_Geometry_mesh_layer_Transparent[];
extern RoomShapeNormal hm_jam_dung_room_0_shapeHeader;
extern RoomShapeDListsEntry hm_jam_dung_room_0_shapeDListsEntry[1];
extern SceneCmd hm_jam_dung_room_1_header00[];
extern Gfx hm_jam_dung_room_1_shapeHeader_entry_0_opaque[];
extern u64 hm_jam_dung_room_1_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8[];
extern u64 hm_jam_dung_room_1_dl_ice_doukutu_room_11_000031D8_Tex_rgba16_rgba16[];
extern Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_0[8];
extern Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_0[];
extern Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_1[48];
extern Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_1[];
extern Gfx mat_hm_jam_dung_room_1_dl_snow_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_1_dl_snow_mat_layerOpaque[];
extern Gfx mat_hm_jam_dung_room_1_dl_wall_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_1_dl_wall_mat_layerOpaque[];
extern Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque[];
extern RoomShapeNormal hm_jam_dung_room_1_shapeHeader;
extern RoomShapeDListsEntry hm_jam_dung_room_1_shapeDListsEntry[1];

#endif
