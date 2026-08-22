#include "object_gol_baby.h"

#include "array_count.h"
#include "gfx.h"
#include "sys_matrix.h"
#include "ultra64.h"

s16 gObjectGolBabyLandFromJumpFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLandFromJumpFrameData.inc.c"
};

JointIndex gObjectGolBabyLandFromJumpJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLandFromJumpJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyLandFromJumpAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLandFromJumpAnim.inc.c"
};

u8 object_gol_baby_zeros_00018C[4] = { 0 };

s16 gObjectGolBabyDeadTwitchingFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeadTwitchingFrameData.inc.c"
};

JointIndex gObjectGolBabyDeadTwitchingJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeadTwitchingJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyDeadTwitchingAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeadTwitchingAnim.inc.c"
};

u8 object_gol_baby_zeros_000344[12] = { 0 };

s16 gObjectGolBabyJumpHeadbuttFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyJumpHeadbuttFrameData.inc.c"
};

JointIndex gObjectGolBabyJumpHeadbuttJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyJumpHeadbuttJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyJumpHeadbuttAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyJumpHeadbuttAnim.inc.c"
};

u8 object_gol_baby_zeros_000554[12] = { 0 };

s16 gObjectGolBabyDamagedFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDamagedFrameData.inc.c"
};

JointIndex gObjectGolBabyDamagedJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDamagedJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyDamagedAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDamagedAnim.inc.c"
};

u8 object_gol_baby_zeros_000848[8] = { 0 };

s16 gObjectGolBabyDeathFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeathFrameData.inc.c"
};

JointIndex gObjectGolBabyDeathJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeathJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyDeathAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyDeathAnim.inc.c"
};

u8 object_gol_baby_zeros_000B88[8] = { 0 };

s16 gObjectGolBabyPrepareJumpFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyPrepareJumpFrameData.inc.c"
};

JointIndex gObjectGolBabyPrepareJumpJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyPrepareJumpJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyPrepareJumpAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyPrepareJumpAnim.inc.c"
};

u8 object_gol_baby_zeros_000E5C[4] = { 0 };

s16 gObjectGolBabyWalkFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyWalkFrameData.inc.c"
};

JointIndex gObjectGolBabyWalkJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyWalkJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyWalkAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyWalkAnim.inc.c"
};

u8 object_gol_baby_zeros_0011C4[12] = { 0 };

s16 gObjectGolBabyStandFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStandFrameData.inc.c"
};

JointIndex gObjectGolBabyStandJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStandJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyStandAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStandAnim.inc.c"
};

u8 object_gol_baby_zeros_001558[8] = { 0 };

Vtx gObjectGolBabyLeftFootVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftFootVtx.inc.c"
};

Gfx gObjectGolBabyLeftFootDL[24] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftFootDL.inc.c"
};

Vtx gObjectGolBabyLeftThighVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftThighVtx.inc.c"
};

Gfx gObjectGolBabyLeftThighDL[31] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftThighDL.inc.c"
};

Vtx gObjectGolBabyLeftShinVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftShinVtx.inc.c"
};

Gfx gObjectGolBabyLeftShinDL[18] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftShinDL.inc.c"
};

Vtx gObjectGolBabyRightFootVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightFootVtx.inc.c"
};

Gfx gObjectGolBabyRightFootDL[24] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightFootDL.inc.c"
};

Vtx gObjectGolBabyRightThighVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightThighVtx.inc.c"
};

Gfx gObjectGolBabyRightThighDL[31] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightThighDL.inc.c"
};

Vtx gObjectGolBabyRightShinVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightShinVtx.inc.c"
};

Gfx gObjectGolBabyRightShinDL[18] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightShinDL.inc.c"
};

Vtx gObjectGolBabyBodyVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyBodyVtx.inc.c"
};

Gfx gObjectGolBabyBodyDL[60] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyBodyDL.inc.c"
};

Vtx gObjectGolBabyEggVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEggVtx.inc.c"
};

Gfx gObjectGolBabyEggDL[46] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEggDL.inc.c"
};

Vtx gObjectGolBabyEyeIrisVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisVtx.inc.c"
};

Gfx gObjectGolBabyEyeIrisDL[17] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisDL.inc.c"
};

Vtx gObjectGolBabyAntennaVtx[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyAntennaVtx.inc.c"
};

Gfx gObjectGolBabyAntennaDL[35] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyAntennaDL.inc.c"
};

u64 gObjectGolBabyShellTex[TEX_LEN(u64, gObjectGolBabyShellTex_WIDTH, gObjectGolBabyShellTex_HEIGHT, 16)] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyShellTex.rgba16.inc.c"
};

u64 gObjectGolBabySkinTex[TEX_LEN(u64, gObjectGolBabySkinTex_WIDTH, gObjectGolBabySkinTex_HEIGHT, 16)] = {
#include "assets/objects/object_gol_baby/gObjectGolBabySkinTex.rgba16.inc.c"
};

u64 gObjectGolBabyEyeWhiteTex[TEX_LEN(u64, gObjectGolBabyEyeWhiteTex_WIDTH, gObjectGolBabyEyeWhiteTex_HEIGHT, 16)] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeWhiteTex.rgba16.inc.c"
};

u64 gObjectGolBabyEyeIrisTex[TEX_LEN(u64, gObjectGolBabyEyeIrisTex_WIDTH, gObjectGolBabyEyeIrisTex_HEIGHT, 16)] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisTex.rgba16.inc.c"
};

u64 gObjectGolBabyEggTex[TEX_LEN(u64, gObjectGolBabyEggTex_WIDTH, gObjectGolBabyEggTex_HEIGHT, 16)] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEggTex.rgba16.inc.c"
};

StandardLimb gObjectGolBabyRoot1Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRoot1Limb.inc.c"
};

StandardLimb gObjectGolBabyRoot2Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRoot2Limb.inc.c"
};

StandardLimb gObjectGolBabyBodyLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyBodyLimb.inc.c"
};

StandardLimb gObjectGolBabyAntennaRoot1Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyAntennaRoot1Limb.inc.c"
};

StandardLimb gObjectGolBabyAntennaRoot2Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyAntennaRoot2Limb.inc.c"
};

StandardLimb gObjectGolBabyAntennaLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyAntennaLimb.inc.c"
};

StandardLimb gObjectGolBabyEyeIrisRoot1Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisRoot1Limb.inc.c"
};

StandardLimb gObjectGolBabyEyeIrisRoot2Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisRoot2Limb.inc.c"
};

StandardLimb gObjectGolBabyEyeIrisLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyEyeIrisLimb.inc.c"
};

StandardLimb gObjectGolBabyLeftLegRoot1Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftLegRoot1Limb.inc.c"
};

StandardLimb gObjectGolBabyLeftLegRoot2Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftLegRoot2Limb.inc.c"
};

StandardLimb gObjectGolBabyLeftShinRootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftShinRootLimb.inc.c"
};

StandardLimb gObjectGolBabyLeftFootRootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftFootRootLimb.inc.c"
};

StandardLimb gObjectGolBabyLeftFootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftFootLimb.inc.c"
};

StandardLimb gObjectGolBabyLeftShinLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftShinLimb.inc.c"
};

StandardLimb gObjectGolBabyLeftThighLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLeftThighLimb.inc.c"
};

StandardLimb gObjectGolBabyRightLegRoot1Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightLegRoot1Limb.inc.c"
};

StandardLimb gObjectGolBabyRightLegRoot2Limb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightLegRoot2Limb.inc.c"
};

StandardLimb gObjectGolBabyRightShinRootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightShinRootLimb.inc.c"
};

StandardLimb gObjectGolBabyRightFootRootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightFootRootLimb.inc.c"
};

StandardLimb gObjectGolBabyRightFootLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightFootLimb.inc.c"
};

StandardLimb gObjectGolBabyRightShinLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightShinLimb.inc.c"
};

StandardLimb gObjectGolBabyRightThighLimb = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRightThighLimb.inc.c"
};

void* gObjectGolBabyLimbs[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyLimbs.inc.c"
};

SkeletonHeader gObjectGolBabySkel = {
#include "assets/objects/object_gol_baby/gObjectGolBabySkel.inc.c"
};

u8 object_gol_baby_zeros_003B48[8] = { 0 };

s16 gObjectGolBabyRunningFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRunningFrameData.inc.c"
};

JointIndex gObjectGolBabyRunningJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRunningJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyRunningAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyRunningAnim.inc.c"
};

u8 object_gol_baby_zeros_003D88[8] = { 0 };

s16 gObjectGolBabyStopRunningFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStopRunningFrameData.inc.c"
};

JointIndex gObjectGolBabyStopRunningJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStopRunningJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyStopRunningAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStopRunningAnim.inc.c"
};

s16 gObjectGolBabyStartRunningFrameData[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStartRunningFrameData.inc.c"
};

JointIndex gObjectGolBabyStartRunningJointIndices[] = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStartRunningJointIndices.inc.c"
};

AnimationHeader gObjectGolBabyStartRunningAnim = {
#include "assets/objects/object_gol_baby/gObjectGolBabyStartRunningAnim.inc.c"
};

u8 object_gol_baby_zeros_004214[12] = { 0 };

