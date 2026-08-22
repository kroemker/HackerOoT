#ifndef OBJECT_GOL_BABY_H
#define OBJECT_GOL_BABY_H

#include "animation.h"
#include "tex_len.h"
#include "ultra64.h"

extern s16 gObjectGolBabyLandFromJumpFrameData[];
extern JointIndex gObjectGolBabyLandFromJumpJointIndices[];
extern AnimationHeader gObjectGolBabyLandFromJumpAnim;
extern s16 gObjectGolBabyDeadTwitchingFrameData[];
extern JointIndex gObjectGolBabyDeadTwitchingJointIndices[];
extern AnimationHeader gObjectGolBabyDeadTwitchingAnim;
extern s16 gObjectGolBabyJumpHeadbuttFrameData[];
extern JointIndex gObjectGolBabyJumpHeadbuttJointIndices[];
extern AnimationHeader gObjectGolBabyJumpHeadbuttAnim;
extern s16 gObjectGolBabyDamagedFrameData[];
extern JointIndex gObjectGolBabyDamagedJointIndices[];
extern AnimationHeader gObjectGolBabyDamagedAnim;
extern s16 gObjectGolBabyDeathFrameData[];
extern JointIndex gObjectGolBabyDeathJointIndices[];
extern AnimationHeader gObjectGolBabyDeathAnim;
extern s16 gObjectGolBabyPrepareJumpFrameData[];
extern JointIndex gObjectGolBabyPrepareJumpJointIndices[];
extern AnimationHeader gObjectGolBabyPrepareJumpAnim;
extern s16 gObjectGolBabyWalkFrameData[];
extern JointIndex gObjectGolBabyWalkJointIndices[];
extern AnimationHeader gObjectGolBabyWalkAnim;
extern s16 gObjectGolBabyStandFrameData[];
extern JointIndex gObjectGolBabyStandJointIndices[];
extern AnimationHeader gObjectGolBabyStandAnim;
extern Vtx gObjectGolBabyLeftFootVtx[];
extern Gfx gObjectGolBabyLeftFootDL[24];
extern Vtx gObjectGolBabyLeftThighVtx[];
extern Gfx gObjectGolBabyLeftThighDL[31];
extern Vtx gObjectGolBabyLeftShinVtx[];
extern Gfx gObjectGolBabyLeftShinDL[18];
extern Vtx gObjectGolBabyRightFootVtx[];
extern Gfx gObjectGolBabyRightFootDL[24];
extern Vtx gObjectGolBabyRightThighVtx[];
extern Gfx gObjectGolBabyRightThighDL[31];
extern Vtx gObjectGolBabyRightShinVtx[];
extern Gfx gObjectGolBabyRightShinDL[18];
extern Vtx gObjectGolBabyBodyVtx[];
extern Gfx gObjectGolBabyBodyDL[60];
extern Vtx gObjectGolBabyEggVtx[];
extern Gfx gObjectGolBabyEggDL[46];
extern Vtx gObjectGolBabyEyeIrisVtx[];
extern Gfx gObjectGolBabyEyeIrisDL[17];
extern Vtx gObjectGolBabyAntennaVtx[];
extern Gfx gObjectGolBabyAntennaDL[35];
#define gObjectGolBabyShellTex_WIDTH 16
#define gObjectGolBabyShellTex_HEIGHT 16
extern u64 gObjectGolBabyShellTex[TEX_LEN(u64, gObjectGolBabyShellTex_WIDTH, gObjectGolBabyShellTex_HEIGHT, 16)];
#define gObjectGolBabySkinTex_WIDTH 16
#define gObjectGolBabySkinTex_HEIGHT 16
extern u64 gObjectGolBabySkinTex[TEX_LEN(u64, gObjectGolBabySkinTex_WIDTH, gObjectGolBabySkinTex_HEIGHT, 16)];
#define gObjectGolBabyEyeWhiteTex_WIDTH 16
#define gObjectGolBabyEyeWhiteTex_HEIGHT 16
extern u64 gObjectGolBabyEyeWhiteTex[TEX_LEN(u64, gObjectGolBabyEyeWhiteTex_WIDTH, gObjectGolBabyEyeWhiteTex_HEIGHT, 16)];
#define gObjectGolBabyEyeIrisTex_WIDTH 16
#define gObjectGolBabyEyeIrisTex_HEIGHT 16
extern u64 gObjectGolBabyEyeIrisTex[TEX_LEN(u64, gObjectGolBabyEyeIrisTex_WIDTH, gObjectGolBabyEyeIrisTex_HEIGHT, 16)];
#define gObjectGolBabyEggTex_WIDTH 16
#define gObjectGolBabyEggTex_HEIGHT 16
extern u64 gObjectGolBabyEggTex[TEX_LEN(u64, gObjectGolBabyEggTex_WIDTH, gObjectGolBabyEggTex_HEIGHT, 16)];
extern StandardLimb gObjectGolBabyRoot1Limb;
extern StandardLimb gObjectGolBabyRoot2Limb;
extern StandardLimb gObjectGolBabyBodyLimb;
extern StandardLimb gObjectGolBabyAntennaRoot1Limb;
extern StandardLimb gObjectGolBabyAntennaRoot2Limb;
extern StandardLimb gObjectGolBabyAntennaLimb;
extern StandardLimb gObjectGolBabyEyeIrisRoot1Limb;
extern StandardLimb gObjectGolBabyEyeIrisRoot2Limb;
extern StandardLimb gObjectGolBabyEyeIrisLimb;
extern StandardLimb gObjectGolBabyLeftLegRoot1Limb;
extern StandardLimb gObjectGolBabyLeftLegRoot2Limb;
extern StandardLimb gObjectGolBabyLeftShinRootLimb;
extern StandardLimb gObjectGolBabyLeftFootRootLimb;
extern StandardLimb gObjectGolBabyLeftFootLimb;
extern StandardLimb gObjectGolBabyLeftShinLimb;
extern StandardLimb gObjectGolBabyLeftThighLimb;
extern StandardLimb gObjectGolBabyRightLegRoot1Limb;
extern StandardLimb gObjectGolBabyRightLegRoot2Limb;
extern StandardLimb gObjectGolBabyRightShinRootLimb;
extern StandardLimb gObjectGolBabyRightFootRootLimb;
extern StandardLimb gObjectGolBabyRightFootLimb;
extern StandardLimb gObjectGolBabyRightShinLimb;
extern StandardLimb gObjectGolBabyRightThighLimb;
extern void* gObjectGolBabyLimbs[];
typedef enum gObjectGolBabySkelLimb {
    /*  0 */ LIMB_OBJECT_GOL_BABY_003B40_NONE,
    /*  1 */ LIMB_OBJECT_GOL_BABY_0039D0,
    /*  2 */ LIMB_OBJECT_GOL_BABY_0039DC,
    /*  3 */ LIMB_OBJECT_GOL_BABY_0039E8,
    /*  4 */ LIMB_OBJECT_GOL_BABY_0039F4,
    /*  5 */ LIMB_OBJECT_GOL_BABY_003A00,
    /*  6 */ LIMB_OBJECT_GOL_BABY_003A0C,
    /*  7 */ LIMB_OBJECT_GOL_BABY_003A18,
    /*  8 */ LIMB_OBJECT_GOL_BABY_003A24,
    /*  9 */ LIMB_OBJECT_GOL_BABY_003A30,
    /* 10 */ LIMB_OBJECT_GOL_BABY_003A3C,
    /* 11 */ LIMB_OBJECT_GOL_BABY_003A48,
    /* 12 */ LIMB_OBJECT_GOL_BABY_003A54,
    /* 13 */ LIMB_OBJECT_GOL_BABY_003A60,
    /* 14 */ LIMB_OBJECT_GOL_BABY_003A6C,
    /* 15 */ LIMB_OBJECT_GOL_BABY_003A78,
    /* 16 */ LIMB_OBJECT_GOL_BABY_003A84,
    /* 17 */ LIMB_OBJECT_GOL_BABY_003A90,
    /* 18 */ LIMB_OBJECT_GOL_BABY_003A9C,
    /* 19 */ LIMB_OBJECT_GOL_BABY_003AA8,
    /* 20 */ LIMB_OBJECT_GOL_BABY_003AB4,
    /* 21 */ LIMB_OBJECT_GOL_BABY_003AC0,
    /* 22 */ LIMB_OBJECT_GOL_BABY_003ACC,
    /* 23 */ LIMB_OBJECT_GOL_BABY_003AD8,
    /* 24 */ LIMB_OBJECT_GOL_BABY_003B40_MAX
} gObjectGolBabySkelLimb;
extern SkeletonHeader gObjectGolBabySkel;
extern s16 gObjectGolBabyRunningFrameData[];
extern JointIndex gObjectGolBabyRunningJointIndices[];
extern AnimationHeader gObjectGolBabyRunningAnim;
extern s16 gObjectGolBabyStopRunningFrameData[];
extern JointIndex gObjectGolBabyStopRunningJointIndices[];
extern AnimationHeader gObjectGolBabyStopRunningAnim;
extern s16 gObjectGolBabyStartRunningFrameData[];
extern JointIndex gObjectGolBabyStartRunningJointIndices[];
extern AnimationHeader gObjectGolBabyStartRunningAnim;

#endif
