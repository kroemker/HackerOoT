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

extern SceneCmd hm_jam_dung_scene_header00[];
extern RomFile hm_jam_dung_scene_roomList[];
extern u8 _hm_jam_dung_room_0SegmentRomStart[];
extern u8 _hm_jam_dung_room_0SegmentRomEnd[];
extern ActorEntry hm_jam_dung_scene_header00_playerEntryList[];
extern Spawn hm_jam_dung_scene_header00_entranceList[];
extern EnvLightSettings hm_jam_dung_scene_header00_lightSettings[4];
extern SurfaceType hm_jam_dung_scene_polygonTypes[1];
extern Vec3s hm_jam_dung_scene_vertices[16];
extern CollisionPoly hm_jam_dung_scene_polygons[20];
extern CollisionHeader hm_jam_dung_scene_collisionHeader;
extern SceneCmd hm_jam_dung_room_0_header00[];
extern Gfx hm_jam_dung_room_0_shapeHeader_entry_0_opaque[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_ci8[];
extern u64 hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_pal_rgba16[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_ci4[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_pal_rgba16[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_ci4[];
extern u64 hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_pal_rgba16[];
extern Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[4];
extern Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_0[];
extern Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[8];
extern Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_1[];
extern Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_cull[8];
extern Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_0[8];
extern Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_0[];
extern Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_1[4];
extern Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_1[];
extern Gfx mat_hm_jam_dung_room_0_dl_snow_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_snow_mat_layerOpaque[];
extern Gfx mat_hm_jam_dung_room_0_dl_wall_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_wall_mat_layerOpaque[];
extern Gfx mat_hm_jam_dung_room_0_dl_stone_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_stone_mat_layerOpaque[];
extern Gfx mat_hm_jam_dung_room_0_dl_ground_mat_layerOpaque[];
extern Gfx mat_revert_hm_jam_dung_room_0_dl_ground_mat_layerOpaque[];
extern Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque[];
extern Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque[];
extern RoomShapeNormal hm_jam_dung_room_0_shapeHeader;
extern RoomShapeDListsEntry hm_jam_dung_room_0_shapeDListsEntry[1];

#endif
