#include "hm_jam_dung_scene.h"

/**
 * Header Child Day (Default)
*/
SceneCmd hm_jam_dung_room_0_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&hm_jam_dung_room_0_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x02),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x01, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(12, 0, 0),
    SCENE_CMD_END(),
};

RoomShapeNormal hm_jam_dung_room_0_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_jam_dung_room_0_shapeDListsEntry),
    hm_jam_dung_room_0_shapeDListsEntry,
    hm_jam_dung_room_0_shapeDListsEntry + ARRAY_COUNT(hm_jam_dung_room_0_shapeDListsEntry)
};

RoomShapeDListsEntry hm_jam_dung_room_0_shapeDListsEntry[1] = {
    { hm_jam_dung_room_0_shapeHeader_entry_0_opaque, NULL }
};

Gfx hm_jam_dung_room_0_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque),
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_jam_dung_room_0_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8[] = {
	0xc7ffcaffddf8eda3, 0xcee2daf5fabac8ee, 0xf2fff6fce1d9e7ff, 0xf5e9ffc4e5ffffe7, 0xdeccc8fcbfe9bbff, 0xf1e7ffccdfceeee9, 0xf0c7c2dae8fcf8dd, 0xf2bff5bce5eedadb, 
	0xdaf0cbf8dfefe5f0, 0xb0ffffc3e6fffffe, 0xe9fff5e1ffe3d2f5, 0xdfd3edddffe5d0c0, 0xc3f2d9ebc2fcdde1, 0xffffd3c4fff8b8cc, 0xf6d6ebfff0bcc8ff, 0xfffcf1d7d2f0f5ff, 
	0xeae9feddfffdcfff, 0xd0e7d7fbffeed7ff, 0xd5dff6ddf4e1ffff, 0xc8cbdbcbffe1ced7, 0xd3ffe1b3e6b8dffa, 0xdbf1c0e6f1f0dff6, 0xe1f0e6f4bec8e5d3, 0xc2ffe5fdffd3f9da, 
	0xb0f9befcffe1f2ff, 0xffd9e7ffdde9f1c2, 0xc2ebcbd7d0fadfd6, 0xd9f8b3ccc2c4fff8, 0xe3f0d9fff2cad3ff, 0xcfbceec3ffceb4e5, 0xffffcee3f0dfccf9, 0xfffff4fff1ffe7c7, 
	0xffffe5dbdfd3f9ff, 0xd2d2e5cef8c0e1ff, 0xe3b7c2fff9ffffff, 0xc8e1eeccf8ebddff, 0xc2c8d9f9f4dfd6d0, 0xd3fff5ffe7dad9ff, 0xd2e5feffbce7cfd3, 0xdaffdfe3e9eecebe, 
	0xfffccbcac8fff1e6, 0xcff2c2d9f5ebe1ff, 0xddffd5e9e1d6ddc4, 0xe9f8d2e2d7f4f5ff, 0xd5baccfff4ffcbb6, 0xf1d6ccfff1c0cbff, 0xddbcb8d9dae5f1c2, 0xffe2d9cbf6e9f1cc, 
	0xfcffffced2edc8fd, 0xf6e3ffffc3d9f1ff, 0xe5ffe7f9f4f2f1e7, 0xf1daf2f0ffc0ddf6, 0xe1f8c2dafff0ffed, 0xdfced7f4e6fdf6da, 0xbfb7f4dfeee1ffdf, 0xffe1f8fecbe9fff1, 
	0xfff4cefffffce3ce, 0xffe6e3f4b7c4d9c3, 0xf6faffd2eaf9f0df, 0xffeaf9edbeeadadb, 0xe7e9fff6bbbbbcfc, 0xd3cedefff8f9ffd9, 0xeae7eed7d7f6dbb7, 0xf6f2c7f2daf9e2d6, 
	0xe3f2cec8daf6fffd, 0xe1fff9dfe5cef1bb, 0xffffc7e7eaedc0d2, 0xf0d9bcf8bcd0e5ff, 0xfdedffffdae7e6ca, 0xfff1e6f1e7daffe6, 0xfbbcd3ffd6f2ffff, 0xfff4f1f9cfffedc3, 
	0xf4f6cfb7dadfddd6, 0xded3f4daadffedee, 0xf5fdeedbf1ccd7be, 0xf8d9e9e5c8f4ccff, 0xffdde6daffebffef, 0xe7e1c7daf8ffd2df, 0xd9d2d5ffdfceffff, 0xffeff0f2dff9bcbe, 
	0xe2dbd6bce9cae3df, 0xdad0ffd9f6feebba, 0xdad7e9f1c6ffe9ce, 0xc0c2dae6c3f6e9fa, 0xd2f8b3f9dffee3f5, 0xc2f2dee3f6b8e3c6, 0xe7d3d3e7f4d9c4e5, 0xcefdf5ffe9f0b7c7, 
	0xe1ffd7f8e7e7f6ff, 0xe7eef2f5b3eeead7, 0xffffffffddd6fff5, 0xcffff2ebd2fffaff, 0xffe7d2caf1dee1c8, 0xbfdaffdfd3ffe1ff, 0xebe6f4c0baeac8c7, 0xe7cee3dbf0ddb4d0, 
	0xffd3fbe5ebd6e8ea, 0xffffd5c6e5e6d6eb, 0xdadfd2c0ffedfae5, 0xf8e7fed7ded9ffff, 0xffd2dff9fcfff0e7, 0xe1e1d3f8d0fff6e7, 0xc7eaead9fecbffe3, 0xe9dfdffbd6d6bbaf, 
	0xf6d2dadaf1c0bef0, 0xfcc7f9cfd6feb8e2, 0xf5ffedf8ffd5e5db, 0xdfd3f0f1c8f6dae6, 0xffd6f9ffffbffeff, 0xcfddf0cbffeaf9ff, 0xcedbcee3e5fff9ff, 0xe2e5f5d6f8e2d2ef, 
	0xf9d0f4bfdecbd9f8, 0xf9e5e5ffffe3edcb, 0xe7c8ffe5ddeabbdf, 0xc2dfbfe9e5d6e2e2, 0xd5cacccaf6bfffff, 0xbeb8f1d3cfd7edd2, 0xfff0f4d7d3def6fc, 0xd2f2f4ffd3ceebf5, 
	0xbce3ddd3dae7fcda, 0xe3f4e3e5dce6f2ee, 0xceb4dfe5c8dfffbb, 0xc0eeddf6ddf9e7c4, 0xd3dff4dbdfebeeea, 0xfec4cef1d2fcffe1, 0xe3d7ffb8f0e6e5c8, 0xf0f0e7ffcedbc2e3, 
	
};

u64 hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_ci8[] = {
	0x0001020302040506, 0x0507020208090a0b, 0x0c0d0e0f100e0211, 0x051213140204020f, 0x1500101602020506, 0x0507020214081700, 0x18170e190e0e0203, 0x050313091a1b1c1d, 
	0x1e1f0c2009021306, 0x0507020208212223, 0x242526100e090205, 0x0606050203052715, 0x2829000b0e020706, 0x0511020209172a29, 0x2b2c0d102d090211, 0x062e0502052f3028, 
	0x2828153132141105, 0x0511021433341535, 0x2b18360d20370911, 0x062e0502142c3839, 0x1529393a0b091106, 0x053b07083c3a3d3e, 0x393f404142370911, 0x0643050944454615, 
	0x4729481549201305, 0x063b070a01394848, 0x3d4a4b4c4d100211, 0x062e13414e382b47, 0x4f2b50393a515205, 0x061114534b3e5050, 0x35391554550f0911, 0x061b0e493846564b, 
	0x574b39353f0c4413, 0x0513102a393d5048, 0x3d394a4758593711, 0x1b165a355b5c492a, 0x254c56285d575e5f, 0x050459154a393e39, 0x235660613a221011, 0x05622b5063002222, 
	0x530c5c462964012d, 0x05090165472b3923, 0x3a3a314e15491766, 0x021d673e604c5153, 0x3c595a1d4e60010f, 0x1417232b3f2b2368, 0x4c0101495c696a08, 0x62466730576b1717, 
	0x0d0d0f44256c270e, 0x080b3e4b3a4b496d, 0x5959250b49696d0e, 0x6e452b68253c173c, 0x090909090e0e6f09, 0x08276c6a6d702d0e, 0x0e102071596d4419, 0x72735e6d593c0f10, 
	0x0204160202021113, 0x0e190e0e100e6611, 0x04140e10200f1910, 0x0e520f44440f205f, 0x0707076602070309, 0x5910160209020505, 0x0504020909370e26, 0x1010100d20201002, 
	0x133b116602031374, 0x4b6d110702040606, 0x0605070202020810, 0x593c0e100d0d0e04, 0x13030514751b141d, 0x392c086602070506, 0x0603070202090844, 0x1d0c0a0e10100e07, 
	0x0503060207056223, 0x1e4b206602020506, 0x060507020209210b, 0x5c680d0e2d266f07, 0x05121b0213141d3d, 0x763d683702020506, 0x0605070202081764, 0x3923597720080e07, 
	0x05121b026662633d, 0x78792b0f02021106, 0x0605070202100b15, 0x7a305a0d200e3702, 0x050643021069482b, 0x1e357b6d08140306, 0x0605070208593a35, 0x3d2b49360d0d3702, 
	0x054306376d453815, 0x1f3d7b490a140312, 0x1b050713374c1548, 0x3d293f4041412607, 0x062e05174b382b3f, 0x473d7c2317140303, 0x0605071417603e50, 0x7d3d154b4c411004, 
	0x061b6f2a7d385664, 0x4b3d50460c260503, 0x0612020a4c393e48, 0x483d394a64552014, 0x067e70397f2b314c, 0x68613580640a1305, 0x0603088156393d48, 0x3d2b154a47344108, 
	0x0508007b484b4c55, 0x0c6815823f3c0405, 0x060510493929393d, 0x15563a4b4a3a5108, 0x0574457b2b492253, 0x592c2428296d0205, 0x0504705c2b4a3915, 0x8331314923243408, 
	0x0e1d7c464b228117, 0x590c602b3d640a05, 0x060840464a232300, 0x0c6d0c0c49841d0e, 0x4445673057811717, 0x41590c1d235c4413, 0x050e6046233a1d6d, 0x44201759515a6c0e, 
	0x85864e2c59870d10, 0x0d100f446d6c8808, 0x1462694b57018810, 0x0e3710201759880e, 0x898a88201010100e, 0x3709090e0e0f6226, 0x0e62270125881909, 0x0202090e100d0f52, 
	
};

u64 hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_pal_rgba16[] = {
	0x657575f7bf3dcf7d, 0xc73fcf7fd77fc73d, 0xb73fb73da6ff7e39, 0x7df99efdaefd9ebb, 0xa6fdc77dd77dc77f, 0xbf3f4cf3bf7d96bd, 0x6573a6bbc73bd7bf, 0xb6fb6d7544f34cf5, 
	0x9ebda73d7e3b54f3, 0x4cf1863baf3f85f7, 0x3cb144b36db94cb1, 0x75b7a6bddfbfaebd, 0x54b165b79679a6fb, 0x76393c718679af3d, 0x442f44b15d75cf3d, 0x96bb44713c6f5535, 
	0x6df78ebb96fbdf7f, 0x967b4c6f446f54f5, 0x3c2f6db74cb35d35, 0x75f986bb5cf35d37, 0x342f867bb6fd8ebd, 0x65357e7b553375b9, 0x75fb8e7b7df73bf1, 0x54f14d3585f9aeff, 
	0x5d3354b39e7b4c71, 0x657744afbf7f3c2d, 0x6d7765338e3b867d, 0x75b586399639aefb, 0x8e79967d9e3985b7, 0x9e79bf3b3cf3a73f, 0x44f134314473342d, 0x33ed3c31cfbf33ef, 
	0x346f8e7d3cb35d77, 0x5cf16d73442d96fd, 0x8e3975337d750000
};

u64 hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_ci4[] = {
	0x0112310140000000, 0x0113310140000001, 0x3332253132333222, 0x3335253132333232, 0x0336256552522232, 0x0325256551522633, 0x1326262576836232, 0x1326262577936232, 
	0x1255266678857232, 0x3355276678757236, 0x0325577267667226, 0x0355576267667226, 0x0225265567867628, 0x0225266567867629, 0x3265667576967627, 0x3265667576967627, 
	0x1525656678877657, 0x1525656578877657, 0x0356767776779726, 0x0356677786779725, 0x1223777757777668, 0x1222775757777668, 0x3265255577787768, 0x3255257567787768, 
	0x3225557558577778, 0x3256255758577778, 0x1262255555777775, 0x1252265555777775, 0x0522555555576567, 0x0522555555576567, 0x3568575187827558, 0x2568575187827558, 
	0x13301415a1131440, 0x13301415a1131440, 0x56256559a5267277, 0x56256559a5267277, 0x6625656815567177, 0x6625656815567177, 0x8775625716557157, 0x8775625716557157, 
	0x7866626626527277, 0x8866626626527277, 0x7766666616558586, 0x7766666616558586, 0x7776677537766567, 0x7776677537766567, 0x7777666226777776, 0x7777666226777776, 
	0x7777726517777667, 0x7777726517777667, 0x8666766806677779, 0x7666766806677779, 0x7666726606667779, 0x7666726606667777, 0x6767625516766676, 0x6667625516765777, 
	0x6656656736676277, 0x6756656736676267, 0x6566666636666665, 0x6566666636666665, 0x5625226706225655, 0x5625226706355655, 0x5222266933525555, 0x5222266933625556, 
	
};

u64 hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_pal_rgba16[] = {
	0xddd5c4d3b3cdc48f, 0xde1bab8b9b478ac5, 0x7a457203ee9d0000
};

u64 hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_ci4[] = {
	0x0100222322044205, 0x3036311441370223, 0x3300332224424367, 0x3336631734670700, 0x0030133423330466, 0x4223771311074200, 0x5122341413200376, 0x1033310620220220, 
	0x7324330030003787, 0x2236037330242000, 0x0141033630030056, 0x4230775032242000, 0x5300300030667788, 0x0307647042340077, 0x7033233220310607, 0x7200310144247720, 
	0x6133300000003075, 0x2033603311232200, 0x0330304200200037, 0x3231776342202232, 0x7037020220220237, 0x0322877000222200, 0x7340022002202207, 0x0340704000702020, 
	0x5000002022303007, 0x0207303207323220, 0x5007020023000007, 0x7000220071443007, 0x8667320220227077, 0x0222110700300000, 0x5773203202207046, 0x2020207077503036, 
	0x5885877885895885, 0x3222407020200301, 0x6301356603670770, 0x0044360002076770, 0x0300100330060660, 0x3423300002273406, 0x6007605050323633, 0x7300203003720030, 
	0x0770013050000323, 0x2203130000242066, 0x5030330300720007, 0x3207320022224370, 0x0230311177732307, 0x0037700070023777, 0x6330313300003007, 0x0227070002242000, 
	0x0330113100333338, 0x0200342002223220, 0x1333003200014337, 0x0203570033307000, 0x3330301100313016, 0x4222700020342200, 0x6020114307607037, 0x2243007200222003, 
	0x0146003007770115, 0x3130070230033303, 0x3116031370222115, 0x5733070003770007, 0x5306123720000229, 0x5730776222007700, 0x3333242023222439, 0x8885555158885898, 
	
};

u64 hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_pal_rgba16[] = {
	0x9b4fbbd1b3d3b3d1, 0xc45592cb930d8acd, 0x7a4961c700000000
};

Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-300, -120, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-300, 160, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-300, 160, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-300, -120, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, -120, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, 160, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, 160, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {300, -120, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_0[4] = {
	{{ {-300, -120, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {300, -120, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {300, -120, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
	{{ {-300, -120, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
};

Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Vtx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_1[8] = {
	{{ {300, -120, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {300, 160, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {300, 160, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
	{{ {-300, -120, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {-300, 160, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {-300, -120, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {-300, 160, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {300, -120, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
};

Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_1 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 4, 1, 0, 5, 4, 3, 0),
	gsSP2Triangles(5, 6, 4, 0, 7, 6, 5, 0),
	gsSP2Triangles(7, 2, 6, 0, 0, 2, 7, 0),
	gsSPEndDisplayList(),
};

Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {1700, -120, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1700, 160, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1700, 160, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {1700, -120, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {2300, -120, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {2300, 160, 300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {2300, 160, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {2300, -120, -300}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_0[8] = {
	{{ {2300, -120, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {2300, 160, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {2300, 160, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
	{{ {1700, -120, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {1700, 160, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {1700, -120, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {1700, 160, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
	{{ {2300, -120, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
};

Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_0 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 3, 1, 0, 0),
	gsSP2Triangles(3, 4, 1, 0, 5, 4, 3, 0),
	gsSP2Triangles(5, 6, 4, 0, 7, 6, 5, 0),
	gsSP2Triangles(7, 2, 6, 0, 0, 2, 7, 0),
	gsSPEndDisplayList(),
};

Vtx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_1[4] = {
	{{ {1700, -120, 300}, 0, {-16, 1008}, {255, 255, 255, 255} }},
	{{ {2300, -120, 300}, 0, {1008, 1008}, {255, 255, 255, 255} }},
	{{ {2300, -120, -300}, 0, {1008, -16}, {255, 255, 255, 255} }},
	{{ {1700, -120, -300}, 0, {-16, -16}, {255, 255, 255, 255} }},
};

Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_1 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_0_dl_snow_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_FOG | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TT_NONE | G_CD_MAGICSQ | G_TF_BILERP | G_TP_PERSP | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_TL_TILE | G_CK_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_jam_dung_room_0_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_0_dl_snow_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_AC_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_0_dl_wall_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_FOG | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_CD_MAGICSQ | G_TF_BILERP | G_TP_PERSP | G_TT_RGBA16 | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_TL_TILE | G_CK_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 138),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_jam_dung_room_0_dl_ice_doukutu_room_9_00005460_Tex_rgba16_ci8),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_0_dl_wall_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_AC_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_0_dl_stone_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_FOG | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_CD_MAGICSQ | G_TF_BILERP | G_TP_PERSP | G_TT_RGBA16 | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_TL_TILE | G_CK_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 10),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, hm_jam_dung_room_0_dl_HIDAN_scene_00018B70_CITex_ci4_tlut_HIDAN_scene_00018B50_TLUT_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 255, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_0_dl_stone_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_AC_NONE),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_0_dl_ground_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_ZBUFFER | G_FOG | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_CD_MAGICSQ | G_TF_BILERP | G_TP_PERSP | G_TT_RGBA16 | G_PM_NPRIMITIVE | G_CYC_2CYCLE | G_TL_TILE | G_CK_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_AC_NONE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_pal_rgba16),
	gsDPSetTile(0, 0, 0, 256, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadTLUTCmd(5, 9),
	gsDPSetTextureImage(G_IM_FMT_CI, G_IM_SIZ_16b, 1, hm_jam_dung_room_0_dl_HIDAN_room_0_00005CC0_CITex_ci4_tlut_HIDAN_scene_00018B30_TLUT_ci4),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 255, 1024),
	gsDPSetTile(G_IM_FMT_CI, G_IM_SIZ_4b, 2, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_0_dl_ground_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2 | G_ZS_PIXEL | G_AC_NONE),
	gsSPEndDisplayList(),
};

Gfx hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_jam_dung_room_0_dl_snow_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_0_dl_snow_mat_layerOpaque),
	gsSPDisplayList(mat_hm_jam_dung_room_0_dl_wall_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_0_dl_wall_mat_layerOpaque),
	gsSPEndDisplayList(),
};

Gfx hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_jam_dung_room_0_dl_stone_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_0_dl_stone_mat_layerOpaque),
	gsSPDisplayList(mat_hm_jam_dung_room_0_dl_ground_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_0_dl_Floor_001_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_0_dl_ground_mat_layerOpaque),
	gsSPEndDisplayList(),
};

