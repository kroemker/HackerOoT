#include "hm_jam_dung_scene.h"

/**
 * Header Child Day (Default)
*/
SceneCmd hm_jam_dung_room_1_header00[] = {
    SCENE_CMD_ROOM_SHAPE(&hm_jam_dung_room_1_shapeHeader),
    SCENE_CMD_ECHO_SETTINGS(0x10),
    SCENE_CMD_ROOM_BEHAVIOR(0x00, 0x01, false, false),
    SCENE_CMD_SKYBOX_DISABLES(true, true),
    SCENE_CMD_TIME_SETTINGS(255, 255, 0),
    SCENE_CMD_END(),
};

RoomShapeNormal hm_jam_dung_room_1_shapeHeader = {
    ROOM_SHAPE_TYPE_NORMAL,
    ARRAY_COUNT(hm_jam_dung_room_1_shapeDListsEntry),
    hm_jam_dung_room_1_shapeDListsEntry,
    hm_jam_dung_room_1_shapeDListsEntry + ARRAY_COUNT(hm_jam_dung_room_1_shapeDListsEntry)
};

RoomShapeDListsEntry hm_jam_dung_room_1_shapeDListsEntry[1] = {
    { hm_jam_dung_room_1_shapeHeader_entry_0_opaque, NULL }
};

Gfx hm_jam_dung_room_1_shapeHeader_entry_0_opaque[] = {
	gsSPDisplayList(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque),
	gsSPEndDisplayList(),
};

u64 hm_jam_dung_room_1_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8[] = {
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

u64 hm_jam_dung_room_1_dl_ice_doukutu_room_11_000031D8_Tex_rgba16_rgba16[] = {
	0xafbf6e7f343d4cff, 0x64bf547b54fb75bd, 0x3d3d1b7b443bbf7f, 0x7ebd8eff447b4379, 0x5479347b75bf967f, 0xaf7fafbf65bd44fb, 0x3cfb963f763f1bf5, 0x3cbd8e7f967f5c7b, 
	0xaf3f9f7f5d3d6dff, 0x3c3d6cfb54fb553b, 0x5dbd343d2bbb9ebf, 0xb7bf7ebf5cfb6cbb, 0x6cb933f96dbf967f, 0x9f3fa77f65bb3cb9, 0x34798dff75ff2439, 0x3c3b963fa73f7e3d, 
	0x86bf9f7f6d7d6dff, 0x453d6cbd657b6dfd, 0x557d4d3d3bbd8dff, 0x7dfd86ff7dfb8dbb, 0x8dfd3c393cbd7e3f, 0xa6ffa73f7e7d44f9, 0x1bf7753d963f243b, 0x3bf97e3daf7fa73f, 
	0x8effb77f85ff557f, 0x557f757f5d7b4d39, 0x4d3b4d3d3bbd8dff, 0x96bf9f3f8e7d8539, 0x85bd4cfd2c7d5dbf, 0x8e7f9f3f55bb44fb, 0x2cbb74fdbeff443b, 0x4cbb5dbdaf3faf3f, 
	0x86bfdfff75ff44bf, 0x65bf85bf65bf4539, 0x44b95dbd343d9e3f, 0xc77fb7bfa77f6cf9, 0x74fd453d3d7f4d7f, 0x7dffb77f5dbd247b, 0x34fb853dc73f85fd, 0x65bd65ff7e7f9f3f, 
	0x65bfb7bf6e7f343d, 0x6dbf96ff6e3f2cbb, 0x3cfb5dbb65bd7dbf, 0xa6bf9f3f8f3f3bf9, 0x43bb23f9457d8ebf, 0x8e7fa73f763d13f9, 0x24bb85bdbf3f963d, 0x657b7ebf663f973f, 
	0x5dfd8ebd763f54fd, 0x763f8ebf7ebf663d, 0x34b95d3965bd7cff, 0x8e3f6e3f6e7f6dbf, 0x547b23fb3479767f, 0x8e7faeff96ff34bb, 0x457bb6ffaebf5cb9, 0x8e7f96ff767f9f3f, 
	0x3d3d5d795d3b3c7d, 0x6dff967fafbf7ebd, 0x3cfb5d79763d6dfd, 0x753d763f76bf6dff, 0x4c7d3c3d3cbd7e7f, 0x75ff8e7f7e3d4d7d, 0x4d7baeffc77f5477, 0x64fba73f6e7d9f3f, 
	0x2cbb763d657d343b, 0x6dff9ebfbfff96fd, 0x453d55bb863d8ebf, 0x7dbf763f7ebf7e7f, 0x33bb33bd347d8dff, 0x8dff9e7f8e3d5dbb, 0x55bbaeffb73f4477, 0x1b396e3f973f9f3f, 
	0x4d7f65fd44bb347b, 0x5d7fa6bfdfff663d, 0x453b44fb867d9f3f, 0xa6ff863f763d763f, 0x43fb1a73343d8ebf, 0xb6bfb6bf7e7d65bb, 0x4d3bb73faf3f33f9, 0x1aad553da7bf9f3f, 
	0x5d3f7e7f44bb3c7b, 0x5dbfc77fd7ff7ebf, 0x453b2bf965bdc7ff, 0xaf7faf3f75ff5d3d, 0x6cfd22b12bfb8e7f, 0xbebfbeff973f6dfd, 0x453b8e7f7e7f3cbb, 0x12ad553b9f3f9f3f, 
	0x3cbf96ff6d7b44bb, 0x55bfd7ffd7bf76bf, 0x453b2bf944fbcfbf, 0xbfbf96bd867f54fd, 0x5cfd1af544397dbf, 0x9e3fae7faf3f7e3d, 0x5dbb7e3f65ff553b, 0x2c7b7e7d85bf5cbf, 
	0x237d763f5cfb4479, 0x4d7db77fdfff8f3f, 0x453b343944fbb7bf, 0xcfffb77f7dff653f, 0x3bfb33795c796d7d, 0x7dbf967f863f7e3d, 0x86bd9efd767f75b9, 0x3cf97e3d763f54bf, 
	0x23fb54ff343933f7, 0x55bd6d7dc7bf76bf, 0x44fb3c793c798ebf, 0xdfffc73f6dff4cbd, 0x85bf2b792b794cbd, 0x967f8e3f757f4bf9, 0x553d9efd763f967d, 0x34f93cfb34fb3cff, 
	0x2cbd6d3f3c394479, 0x55ff54bb963d5dbd, 0x44b954fb65bd767d, 0x9f3f85fd5d7f5cff, 0x43fb2b391b394cbd, 0x757f75bd75ff23bb, 0x5d7da6fd7ebf7e7b, 0x2439457d453d457f, 
	0x2c3996bf44393bf9, 0x4dbd5d3b8dfd5d7b, 0x33f954fb7e3d8ebf, 0x9eff8dff6dbf4d3f, 0x447d1af71af73cbd, 0x343b96bf863f6dbf, 0x553d973f8ebf7e3d, 0x2c7965bd65fd663f, 
	0x2c7b6e7f3c3933b9, 0x34398e7f967d5d3b, 0x33f944797e3fa6ff, 0x8ebf6dbf7dff553f, 0x447f33392b793c3b, 0x4d3fbf7f96ff8e7f, 0x653d8ebf8e7f65bd, 0x3cbb8ebd663d86bf, 
	0x23b74dbf553b3c39, 0x343baf3fcfff767f, 0x2c3933f765bdc7bf, 0xd7bf9eff8e3f4cbf, 0x5d3f443b2bf9553d, 0x7ebfc7bf9eff8dff, 0x5d7f8e7f653f5d3d, 0x2bf7763d7e3d65fd, 
	0x23b74d7d75fd4cb9, 0x34bb9f3fcfbf663f, 0x34792bf944fbc77f, 0xefffc7bf6dff34bd, 0x5dbf54bb5d3f557f, 0x9f3f9ebfbf7f85bf, 0x65ff967f75bf5dbf, 0x557d96ff867b4d39, 
	0x2bf7557d75fd5d3b, 0x5dbd9f3fb77f6e7f, 0x44fb44fb65fd9efd, 0xc77fbfbf75fd34fd, 0x8ebf9e7d5cfb23fb, 0x6dff6dbd6d7d85ff, 0x4dbf96bf653d343d, 0x5cfb5d7d763b54f7, 
	0x23b55dbd75fd5d3b, 0x6dfbaf7fa73f7e7f, 0x5dbd453b65fd7e3d, 0x763d9f3f867d347b, 0x6dbf6dbb1bb754fd, 0x1b39443b8dff657d, 0x34bd8dff75bf443f, 0x653d75bd4d3b54f7, 
	0x23f7557b863d5d3b, 0x65bbc7bfdfff7e7f, 0x6dfd3cbb4c7b7dbf, 0x6dfd557b9f3f4c79, 0x64fb65ff347d2bfb, 0x1af7963d9ebf863f, 0x443d8d7f657f44bf, 0x64ff9e7f867f5dbb, 
	0x23f72c798ebd7dfd, 0x3cfbaf7fdfff8ebf, 0x763d763d44fb9ebf, 0x9ebf6dbfa77f6d79, 0x44b95dbf2bfb12f7, 0x133b8e7fb77fa6ff, 0x5c7d8d3f5cfd2c7d, 0x65bf963faeff7ebd, 
	0x2bf7347975ff9e7d, 0x763d973fefff9f7f, 0x457d7e3d763da73f, 0xa6ff75ffaf7f7e3b, 0x5dbd763f2c791ab3, 0x12fb8e7fc73f867f, 0x54fb7d3d543d1ab7, 0x75ff9f3f96ff7efd, 
	0x1b752c39867f763d, 0xa6ffaf7fdfff9fbf, 0x453b6dfd763d86bf, 0x86bf4d3da6ff9efd, 0x7ebf6e3f34bb1b33, 0x12f93c7baeff7e3f, 0x657db6bf4bfb1a77, 0x64ffc7bf9f3f55bd, 
	0x1a3123f77e3d5cfd, 0x6d3bb77fdfffa7bf, 0x3cfb3c798ebd867d, 0x8eff34bb7dffd7ff, 0x9f3f7eff453b3479, 0x2379553d7e3f967f, 0x85ff9e7f7d7b4c79, 0x6d3fb77faf3f65bd, 
	0x1a3533b96e7d5d7f, 0x8dffb77fcfffb77f, 0x453b44f9af3dcfff, 0xafbf3cfb447bcfff, 0x9f3f8eff3cbd2c39, 0x653b443b65bd5dbd, 0x6d7f967faefd4c7b, 0x6dbba6fd9eff44fb, 
	0x23fb4cf97e7d4d7b, 0x75bfaf3fb7bfb7bf, 0x453b453bc7bfbfbf, 0xa77f557b2c39bf7f, 0xa77f667f247d557d, 0xa6ff54fb657d65bd, 0x75ff5cfd75bd23bb, 0x5d7975b9657d3c7d, 
	0x357b6d777e3b4477, 0x2bfd867fa77fb7bf, 0x44fb44fbbf7fc7bf, 0xb7bf6e3d557b8e7d, 0xaf7f3d3b1c396dbd, 0xcfbf967d7dfd65bd, 0x5d7d65bd33fb1ab5, 0x2b7b65bd5d3d2c3b, 
	0x3d3d4cf7557986bd, 0x2bb97e3f96bf8eff, 0x2c3944fbcfbfcfff, 0x96ff6e7f6e3dc73f, 0x96ff55393cfb767f, 0xb77faf3f9f3f5dbd, 0x65bd863d6dbd1279, 0x1af97e3f6dff2c7b, 
	0x55ff23f723f77e7f, 0x44bb8e3f8ebd7e7f, 0x1b31347bdfffd7ff, 0x86bf4dbf767fb73f, 0x6e3d86bf44f9667f, 0x7ebf8eff7e7d65fd, 0x7dfdbf3f9e3f1277, 0x3b7baeff96ff65fd, 
	0x8eff24371aef247b, 0x557d967f7e3d86bf, 0x247923fb5dbdcfff, 0x7e7d5dfd9fbf86bf, 0x347b5dbd763d767d, 0x5dff767f86ff5dbd, 0x4d7b967fa6bf1a33, 0x7cbdc77faf7f6e3f, 
	
};

Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_cull[8] = {
	{{ {-1195, -91, 1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, 1508, 1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, 1508, -1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-1195, -91, -1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5195, -91, 1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5195, 1508, 1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5195, 1508, -1195}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {5195, -91, -1195}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_0[8] = {
	{{ {2805, -91, 1195}, 0, {-4986, 5978}, {255, 255, 255, 255} }},
	{{ {5195, -91, 1195}, 0, {5978, 5978}, {255, 255, 255, 0} }},
	{{ {5195, -91, -1195}, 0, {5978, -4986}, {255, 255, 255, 255} }},
	{{ {2805, -91, -1195}, 0, {-4986, -4986}, {255, 255, 255, 255} }},
	{{ {-1195, -91, 1195}, 0, {-4986, 5978}, {255, 255, 255, 255} }},
	{{ {1195, -91, 1195}, 0, {5978, 5978}, {255, 255, 255, 0} }},
	{{ {1195, -91, -1195}, 0, {5978, -4986}, {255, 255, 255, 255} }},
	{{ {-1195, -91, -1195}, 0, {-4986, -4986}, {255, 255, 255, 255} }},
};

Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_0[] = {
	gsSPVertex(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_0 + 0, 8, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSPEndDisplayList(),
};

Vtx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_1[48] = {
	{{ {5195, -91, 1195}, 0, {-3703, 2456}, {255, 255, 255, 0} }},
	{{ {5195, 1024, 1195}, 0, {-3703, -1464}, {0, 0, 0, 255} }},
	{{ {5195, 1024, -1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {5195, -91, -1195}, 0, {4695, 2456}, {255, 255, 255, 255} }},
	{{ {2805, 1024, -1195}, 0, {-3703, -1464}, {0, 0, 0, 255} }},
	{{ {2805, -91, -1195}, 0, {-3703, 2456}, {255, 255, 255, 255} }},
	{{ {2805, -91, -1195}, 0, {4695, 2456}, {255, 255, 255, 255} }},
	{{ {2805, 1024, -1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {2805, 1024, 1195}, 0, {-3703, -1464}, {0, 0, 0, 0} }},
	{{ {2805, -91, 1195}, 0, {-3703, 2456}, {255, 255, 255, 255} }},
	{{ {5195, 1024, 1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {5195, -91, 1195}, 0, {4695, 2456}, {255, 255, 255, 0} }},
	{{ {1195, -91, 1195}, 0, {-3703, 2456}, {255, 255, 255, 0} }},
	{{ {1195, 1024, 1195}, 0, {-3703, -1464}, {0, 0, 0, 255} }},
	{{ {1195, 1024, -1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {1195, -91, -1195}, 0, {4695, 2456}, {255, 255, 255, 255} }},
	{{ {-1195, 1024, -1195}, 0, {-3703, -1464}, {0, 0, 0, 255} }},
	{{ {-1195, -91, -1195}, 0, {-3703, 2456}, {255, 255, 255, 255} }},
	{{ {-1195, -91, -1195}, 0, {4695, 2456}, {255, 255, 255, 255} }},
	{{ {-1195, 1024, -1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {-1195, 1024, 1195}, 0, {-3703, -1464}, {0, 0, 0, 0} }},
	{{ {-1195, -91, 1195}, 0, {-3703, 2456}, {255, 255, 255, 255} }},
	{{ {1195, 1024, 1195}, 0, {4695, -1464}, {0, 0, 0, 255} }},
	{{ {1195, -91, 1195}, 0, {4695, 2456}, {255, 255, 255, 0} }},
	{{ {4190, 1024, -1114}, 0, {947, 45}, {0, 0, 0, 255} }},
	{{ {4190, 1508, -734}, 0, {947, 947}, {0, 0, 0, 255} }},
	{{ {4190, 1508, -1114}, 0, {947, 45}, {0, 0, 0, 255} }},
	{{ {4190, 1024, -734}, 0, {947, 947}, {0, 0, 0, 255} }},
	{{ {5195, 1024, -1195}, 0, {1008, -16}, {0, 0, 0, 255} }},
	{{ {2805, 1024, -1195}, 0, {-16, -16}, {0, 0, 0, 255} }},
	{{ {3810, 1024, -1114}, 0, {45, 45}, {0, 0, 0, 255} }},
	{{ {3810, 1508, -1114}, 0, {45, 45}, {0, 0, 0, 255} }},
	{{ {3810, 1024, -734}, 0, {45, 947}, {0, 0, 0, 255} }},
	{{ {3810, 1508, -734}, 0, {45, 947}, {0, 0, 0, 255} }},
	{{ {5195, 1024, 1195}, 0, {1008, 1008}, {0, 0, 0, 255} }},
	{{ {2805, 1024, 1195}, 0, {-16, 1008}, {0, 0, 0, 0} }},
	{{ {190, 1024, -1114}, 0, {947, 45}, {0, 0, 0, 255} }},
	{{ {190, 1508, -734}, 0, {947, 947}, {0, 0, 0, 255} }},
	{{ {190, 1508, -1114}, 0, {947, 45}, {0, 0, 0, 255} }},
	{{ {190, 1024, -734}, 0, {947, 947}, {0, 0, 0, 255} }},
	{{ {1195, 1024, -1195}, 0, {1008, -16}, {0, 0, 0, 255} }},
	{{ {-1195, 1024, -1195}, 0, {-16, -16}, {0, 0, 0, 255} }},
	{{ {-190, 1024, -1114}, 0, {45, 45}, {0, 0, 0, 255} }},
	{{ {-190, 1508, -1114}, 0, {45, 45}, {0, 0, 0, 255} }},
	{{ {-190, 1024, -734}, 0, {45, 947}, {0, 0, 0, 255} }},
	{{ {-190, 1508, -734}, 0, {45, 947}, {0, 0, 0, 255} }},
	{{ {1195, 1024, 1195}, 0, {1008, 1008}, {0, 0, 0, 255} }},
	{{ {-1195, 1024, 1195}, 0, {-16, 1008}, {0, 0, 0, 0} }},
};

Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_1[] = {
	gsSPVertex(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_1 + 0, 48, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
	gsSP2Triangles(9, 8, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(15, 14, 16, 0, 15, 16, 17, 0),
	gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
	gsSP2Triangles(21, 20, 22, 0, 21, 22, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 24, 27, 25, 0),
	gsSP2Triangles(27, 24, 28, 0, 24, 29, 28, 0),
	gsSP2Triangles(24, 30, 29, 0, 30, 24, 26, 0),
	gsSP2Triangles(30, 26, 31, 0, 32, 30, 31, 0),
	gsSP2Triangles(32, 31, 33, 0, 27, 32, 33, 0),
	gsSP2Triangles(27, 33, 25, 0, 32, 27, 34, 0),
	gsSP2Triangles(27, 28, 34, 0, 32, 34, 35, 0),
	gsSP2Triangles(30, 32, 35, 0, 30, 35, 29, 0),
	gsSP2Triangles(36, 37, 38, 0, 36, 39, 37, 0),
	gsSP2Triangles(39, 36, 40, 0, 36, 41, 40, 0),
	gsSP2Triangles(36, 42, 41, 0, 42, 36, 38, 0),
	gsSP2Triangles(42, 38, 43, 0, 44, 42, 43, 0),
	gsSP2Triangles(44, 43, 45, 0, 39, 44, 45, 0),
	gsSP2Triangles(39, 45, 37, 0, 44, 39, 46, 0),
	gsSP2Triangles(39, 40, 46, 0, 44, 46, 47, 0),
	gsSP2Triangles(42, 44, 47, 0, 42, 47, 41, 0),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_1_dl_snow_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_FOG | G_SHADE | G_CULL_BACK | G_ZBUFFER | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TF_BILERP | G_TP_PERSP | G_CYC_2CYCLE | G_TT_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT | G_CK_NONE | G_CD_MAGICSQ | G_TL_TILE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_RM_FOG_SHADE_A | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, hm_jam_dung_room_1_dl_ice_doukutu_scene_0000FBF0_Tex_i8_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 511, 512),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_1_dl_snow_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_RM_AA_ZB_OPA_SURF | G_ZS_PIXEL),
	gsSPEndDisplayList(),
};

Gfx mat_hm_jam_dung_room_1_dl_wall_mat_layerOpaque[] = {
	gsSPLoadGeometryMode(G_FOG | G_SHADE | G_CULL_BACK | G_ZBUFFER | G_SHADING_SMOOTH),
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_TF_BILERP | G_TP_PERSP | G_CYC_2CYCLE | G_TT_NONE | G_TD_CLAMP | G_AD_NOISE | G_TC_FILT | G_CK_NONE | G_CD_MAGICSQ | G_TL_TILE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_RM_FOG_SHADE_A | G_ZS_PIXEL),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, hm_jam_dung_room_1_dl_ice_doukutu_room_11_000031D8_Tex_rgba16_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsSPEndDisplayList(),
};

Gfx mat_revert_hm_jam_dung_room_1_dl_wall_mat_layerOpaque[] = {
	gsDPPipeSync(),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_RM_AA_ZB_OPA_SURF2 | G_AC_NONE | G_RM_AA_ZB_OPA_SURF | G_ZS_PIXEL),
	gsSPEndDisplayList(),
};

Gfx hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_hm_jam_dung_room_1_dl_snow_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_0),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_1_dl_snow_mat_layerOpaque),
	gsSPDisplayList(mat_hm_jam_dung_room_1_dl_wall_mat_layerOpaque),
	gsSPDisplayList(hm_jam_dung_room_1_dl_Geometry_001_mesh_layer_Opaque_tri_1),
	gsSPDisplayList(mat_revert_hm_jam_dung_room_1_dl_wall_mat_layerOpaque),
	gsSPEndDisplayList(),
};

