#ifndef OBJECT_IK_TRANSFORM_H
#define OBJECT_IK_TRANSFORM_H

#include "animation.h"
#include "tex_len.h"
#include "ultra64.h"

// HackerOoT: like G_RM_AA_ZB_XLU_SURF2, but also updates the Z-buffer (Z_UPD). This object's
// materials render through the XLU pass unconditionally so the whole model can cross-fade via
// TransformFade (see TransformIk_Draw), but without Z_UPD the model's own limbs don't occlude
// each other correctly (XLU draws test the depth buffer but don't write it, so overlap is decided
// by skeleton draw order instead of actual depth). Since this only affects self-occlusion within
// the model, writing Z here is safe and matches how the vanilla OPA-rendered body behaves.
#define G_RM_IK_TRANSFORM_XLU_SURF2                                                   \
    (AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL | ZMODE_XLU | \
     GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA))

extern s16 object_ik_transform_Anim_00035C_06000000_FrameData[];
extern JointIndex object_ik_transform_Anim_00035C_06000350_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_00035C;
extern StandardLimb object_ik_transform_000370_Limb;
extern void* object_ik_transform_Skel_000380_0600037C_Limbs[];
typedef enum object_ik_transform_Skel_000380Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_000380_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_000370,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_000380_MAX
} object_ik_transform_Skel_000380Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_000380;
extern s16 object_ik_transform_Anim_000634_06000390_FrameData[];
extern JointIndex object_ik_transform_Anim_000634_06000628_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_000634;
extern StandardLimb object_ik_transform_000650_Limb;
extern void* object_ik_transform_Skel_000660_0600065C_Limbs[];
typedef enum object_ik_transform_Skel_000660Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_000660_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_000650,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_000660_MAX
} object_ik_transform_Skel_000660Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_000660;
extern s16 object_ik_transform_Anim_0008DC_06000670_FrameData[];
extern JointIndex object_ik_transform_Anim_0008DC_060008D0_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_0008DC;
extern StandardLimb object_ik_transform_0008F0_Limb;
extern void* object_ik_transform_Skel_000900_060008FC_Limbs[];
typedef enum object_ik_transform_Skel_000900Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_000900_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_0008F0,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_000900_MAX
} object_ik_transform_Skel_000900Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_000900;
extern s16 object_ik_transform_Anim_000C6C_06000910_FrameData[];
extern JointIndex object_ik_transform_Anim_000C6C_06000C60_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_000C6C;
extern StandardLimb object_ik_transform_000C80_Limb;
extern void* object_ik_transform_Skel_000C90_06000C8C_Limbs[];
typedef enum object_ik_transform_Skel_000C90Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_000C90_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_000C80,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_000C90_MAX
} object_ik_transform_Skel_000C90Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_000C90;
extern s16 object_ik_transform_Anim_000F0C_06000CA0_FrameData[];
extern JointIndex object_ik_transform_Anim_000F0C_06000F00_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_000F0C;
extern StandardLimb object_ik_transform_000F20_Limb;
extern void* object_ik_transform_Skel_000F30_06000F2C_Limbs[];
typedef enum object_ik_transform_Skel_000F30Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_000F30_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_000F20,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_000F30_MAX
} object_ik_transform_Skel_000F30Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_000F30;
extern s16 gIronKnuckleTransformVerticalAttackFrameData[];
extern JointIndex gIronKnuckleTransformVerticalAttackJointIndices[];
extern AnimationHeader gIronKnuckleTransformVerticalAttackAnim;
extern s16 gIronKnuckleTransformRecoverFromVerticalAttackFrameData[];
extern JointIndex gIronKnuckleTransformRecoverFromVerticalAttackJointIndices[];
extern AnimationHeader gIronKnuckleTransformRecoverFromVerticalAttackAnim;
extern s16 gIronKnuckleTransformAxeStuckFrameData[];
extern JointIndex gIronKnuckleTransformAxeStuckJointIndices[];
extern AnimationHeader gIronKnuckleTransformAxeStuckAnim;
extern s16 gIronKnuckleTransformHorizontalAttackFrameData[];
extern JointIndex gIronKnuckleTransformHorizontalAttackJointIndices[];
extern AnimationHeader gIronKnuckleTransformHorizontalAttackAnim;
extern s16 gIronKnuckleTransformRecoverFromHorizontalAttackFrameData[];
extern JointIndex gIronKnuckleTransformRecoverFromHorizontalAttackJointIndices[];
extern AnimationHeader gIronKnuckleTransformRecoverFromHorizontalAttackAnim;
extern s16 gIronKnuckleTransformBackHitFrameData[];
extern JointIndex gIronKnuckleTransformBackHitJointIndices[];
extern AnimationHeader gIronKnuckleTransformBackHitAnim;
extern s16 gIronKnuckleTransformBlockFrameData[];
extern JointIndex gIronKnuckleTransformBlockJointIndices[];
extern AnimationHeader gIronKnuckleTransformBlockAnim;
extern s16 gIronKnuckleTransformDeathFrameData[];
extern JointIndex gIronKnuckleTransformDeathJointIndices[];
extern AnimationHeader gIronKnuckleTransformDeathAnim;
extern s16 gIronKnuckleTransformFrontHitFrameData[];
extern JointIndex gIronKnuckleTransformFrontHitJointIndices[];
extern AnimationHeader gIronKnuckleTransformFrontHitAnim;
extern s16 gIronKnuckleTransformRunFrameData[];
extern JointIndex gIronKnuckleTransformRunJointIndices[];
extern AnimationHeader gIronKnuckleTransformRunAnim;
extern s16 gIronKnuckleTransformNabooruSummonAxeFrameData[];
extern JointIndex gIronKnuckleTransformNabooruSummonAxeJointIndices[];
extern AnimationHeader gIronKnuckleTransformNabooruSummonAxeAnim;
extern s16 gIronKnuckleTransformStandUpFrameData[];
extern JointIndex gIronKnuckleTransformStandUpJointIndices[];
extern AnimationHeader gIronKnuckleTransformStandUpAnim;
extern s16 object_ik_transform_Anim_00DD50_0600CD80_FrameData[];
extern JointIndex object_ik_transform_Anim_00DD50_0600DC9C_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_00DD50;
extern s16 gIronKnuckleTransformUnused1FrameData[];
extern JointIndex gIronKnuckleTransformUnused1JointIndices[];
extern AnimationHeader gIronKnuckleTransformUnused1Anim;
extern s16 gIronKnuckleTransformWalkFrameData[];
extern JointIndex gIronKnuckleTransformWalkJointIndices[];
extern AnimationHeader gIronKnuckleTransformWalkAnim;
extern s16 gIronKnuckleTransformUnused2FrameData[];
extern JointIndex gIronKnuckleTransformUnused2JointIndices[];
extern AnimationHeader gIronKnuckleTransformUnused2Anim;
//#define object_ik_transform_Tlut_00F630_TLUT_COUNT 184
extern u64 object_ik_transform_Tlut_00F630[];
#define gIronKnuckleTransformMetalTex_WIDTH 32
#define gIronKnuckleTransformMetalTex_HEIGHT 64
extern u64 gIronKnuckleTransformMetalTex[TEX_LEN(u64, gIronKnuckleTransformMetalTex_WIDTH, gIronKnuckleTransformMetalTex_HEIGHT, 4)];
#define gIronKnuckleTransformBigRivetTex_WIDTH 32
#define gIronKnuckleTransformBigRivetTex_HEIGHT 32
extern u64 gIronKnuckleTransformBigRivetTex[TEX_LEN(u64, gIronKnuckleTransformBigRivetTex_WIDTH, gIronKnuckleTransformBigRivetTex_HEIGHT, 8)];
#define gIronKnuckleTransformBlockPatternTex_WIDTH 16
#define gIronKnuckleTransformBlockPatternTex_HEIGHT 16
extern u64 gIronKnuckleTransformBlockPatternTex[TEX_LEN(u64, gIronKnuckleTransformBlockPatternTex_WIDTH, gIronKnuckleTransformBlockPatternTex_HEIGHT, 16)];
#define gIronKnuckleTransformChainMailTex_WIDTH 16
#define gIronKnuckleTransformChainMailTex_HEIGHT 16
extern u64 gIronKnuckleTransformChainMailTex[TEX_LEN(u64, gIronKnuckleTransformChainMailTex_WIDTH, gIronKnuckleTransformChainMailTex_HEIGHT, 16)];
#define object_ik_transform_Tex_0103A0_WIDTH 32
#define object_ik_transform_Tex_0103A0_HEIGHT 32
extern u64 object_ik_transform_Tex_0103A0[TEX_LEN(u64, object_ik_transform_Tex_0103A0_WIDTH, object_ik_transform_Tex_0103A0_HEIGHT, 16)];
#define gIronKnuckleTransformGerudoEyeTex_WIDTH 32
#define gIronKnuckleTransformGerudoEyeTex_HEIGHT 32
extern u64 gIronKnuckleTransformGerudoEyeTex[TEX_LEN(u64, gIronKnuckleTransformGerudoEyeTex_WIDTH, gIronKnuckleTransformGerudoEyeTex_HEIGHT, 16)];
#define gIronKnuckleTransformNabooruLipTex_WIDTH 8
#define gIronKnuckleTransformNabooruLipTex_HEIGHT 8
extern u64 gIronKnuckleTransformNabooruLipTex[TEX_LEN(u64, gIronKnuckleTransformNabooruLipTex_WIDTH, gIronKnuckleTransformNabooruLipTex_HEIGHT, 16)];
#define gIronKnuckleTransformJewelTex_WIDTH 16
#define gIronKnuckleTransformJewelTex_HEIGHT 16
extern u64 gIronKnuckleTransformJewelTex[TEX_LEN(u64, gIronKnuckleTransformJewelTex_WIDTH, gIronKnuckleTransformJewelTex_HEIGHT, 8)];
#define gIronKnuckleTransformNabooruForeheadJewelTex_WIDTH 16
#define gIronKnuckleTransformNabooruForeheadJewelTex_HEIGHT 16
extern u64 gIronKnuckleTransformNabooruForeheadJewelTex[TEX_LEN(u64, gIronKnuckleTransformNabooruForeheadJewelTex_WIDTH, gIronKnuckleTransformNabooruForeheadJewelTex_HEIGHT, 8)];
#define object_ik_transform_Tex_011620_WIDTH 8
#define object_ik_transform_Tex_011620_HEIGHT 8
extern u64 object_ik_transform_Tex_011620[TEX_LEN(u64, object_ik_transform_Tex_011620_WIDTH, object_ik_transform_Tex_011620_HEIGHT, 8)];
#define gIronKnuckleTransformNabooruHair1Tex_WIDTH 16
#define gIronKnuckleTransformNabooruHair1Tex_HEIGHT 16
extern u64 gIronKnuckleTransformNabooruHair1Tex[TEX_LEN(u64, gIronKnuckleTransformNabooruHair1Tex_WIDTH, gIronKnuckleTransformNabooruHair1Tex_HEIGHT, 8)];
#define object_ik_transform_Tex_011760_WIDTH 8
#define object_ik_transform_Tex_011760_HEIGHT 16
extern u64 object_ik_transform_Tex_011760[TEX_LEN(u64, object_ik_transform_Tex_011760_WIDTH, object_ik_transform_Tex_011760_HEIGHT, 8)];
#define object_ik_transform_Tex_0117E0_WIDTH 8
#define object_ik_transform_Tex_0117E0_HEIGHT 16
extern u64 object_ik_transform_Tex_0117E0[TEX_LEN(u64, object_ik_transform_Tex_0117E0_WIDTH, object_ik_transform_Tex_0117E0_HEIGHT, 8)];
#define object_ik_transform_Tex_011860_WIDTH 16
#define object_ik_transform_Tex_011860_HEIGHT 16
extern u64 object_ik_transform_Tex_011860[TEX_LEN(u64, object_ik_transform_Tex_011860_WIDTH, object_ik_transform_Tex_011860_HEIGHT, 8)];
#define object_ik_transform_Tex_011960_WIDTH 16
#define object_ik_transform_Tex_011960_HEIGHT 16
extern u64 object_ik_transform_Tex_011960[TEX_LEN(u64, object_ik_transform_Tex_011960_WIDTH, object_ik_transform_Tex_011960_HEIGHT, 8)];
extern Vtx object_ik_transform_Vtx_011A60[];
extern Vtx object_ik_transform_Vtx_011D20[];
extern Vtx gIronKnuckleTransformNabooruHelmetVtx[];
extern Vtx gIronKnuckleTransformAxeVtx[];
extern Vtx gIronKnuckleTransformShockedNabooruHeadVtx[];
extern Vtx object_ik_transform_Vtx_013A70[];
extern Vtx object_ik_transform_Vtx_013C40[];
extern Vtx object_ik_transform_Vtx_013D20[];
extern Vtx object_ik_transform_Vtx_013F10[];
extern Vtx object_ik_transform_Vtx_013FF0[];
extern Vtx object_ik_transform_Vtx_014140[];
extern Vtx gIronKnuckleTransformSplitHelmetLeftVtx[];
extern Vtx gIronKnuckleTransformSplitHelmetRightVtx[];
extern Vtx gIronKnuckleTransformArmorRivetAndSymbolVtx[];
extern Vtx object_ik_transform_Vtx_0149A0[];
extern Vtx object_ik_transform_Vtx_014A40[];
extern Vtx object_ik_transform_Vtx_014D30[];
extern Vtx object_ik_transform_Vtx_014E10[];
extern Vtx object_ik_transform_Vtx_014EF0[];
extern Vtx object_ik_transform_Vtx_015070[];
extern Gfx object_ik_transform_DL_0151F0[50];
extern Gfx object_ik_transform_DL_015380[44];
extern Gfx gIronKnuckleTransformNabooruHelmetDL[108];
extern Gfx gIronKnuckleTransformAxeDL[88];
extern Gfx gIronKnuckleTransformShockedNabooruHeadDL[195];
extern Gfx object_ik_transform_DL_016118[44];
extern Gfx object_ik_transform_DL_016278[25];
extern Gfx object_ik_transform_DL_016340[44];
extern Gfx object_ik_transform_DL_0164A0[25];
extern Gfx object_ik_transform_DL_016568[30];
extern Gfx object_ik_transform_DL_016658[30];
extern Gfx gIronKnuckleTransformSplitHelmetLeftDL[84];
extern Gfx gIronKnuckleTransformSplitHelmetRightDL[63];
extern Gfx gIronKnuckleTransformArmorRivetAndSymbolDL[31];
extern Gfx object_ik_transform_DL_016CD8[22];
extern Gfx object_ik_transform_DL_016D88[44];
extern Gfx object_ik_transform_DL_016EE8[20];
extern Gfx object_ik_transform_DL_016F88[20];
extern Gfx object_ik_transform_DL_017028[41];
extern Gfx object_ik_transform_DL_017170[35];
//#define object_ik_transform_Tlut_017288_TLUT_COUNT 120
extern u64 object_ik_transform_Tlut_017288[];
#define object_ik_transform_Tex_017378_WIDTH 16
#define object_ik_transform_Tex_017378_HEIGHT 16
extern u64 object_ik_transform_Tex_017378[TEX_LEN(u64, object_ik_transform_Tex_017378_WIDTH, object_ik_transform_Tex_017378_HEIGHT, 8)];
#define object_ik_transform_Tex_017478_WIDTH 8
#define object_ik_transform_Tex_017478_HEIGHT 8
extern u64 object_ik_transform_Tex_017478[TEX_LEN(u64, object_ik_transform_Tex_017478_WIDTH, object_ik_transform_Tex_017478_HEIGHT, 8)];
#define gIronKnuckleTransformHair2Tex_WIDTH 16
#define gIronKnuckleTransformHair2Tex_HEIGHT 16
extern u64 gIronKnuckleTransformHair2Tex[TEX_LEN(u64, gIronKnuckleTransformHair2Tex_WIDTH, gIronKnuckleTransformHair2Tex_HEIGHT, 8)];
#define object_ik_transform_Tex_0175B8_WIDTH 8
#define object_ik_transform_Tex_0175B8_HEIGHT 16
extern u64 object_ik_transform_Tex_0175B8[TEX_LEN(u64, object_ik_transform_Tex_0175B8_WIDTH, object_ik_transform_Tex_0175B8_HEIGHT, 8)];
#define object_ik_transform_Tex_017638_WIDTH 8
#define object_ik_transform_Tex_017638_HEIGHT 16
extern u64 object_ik_transform_Tex_017638[TEX_LEN(u64, object_ik_transform_Tex_017638_WIDTH, object_ik_transform_Tex_017638_HEIGHT, 8)];
#define object_ik_transform_Tex_0176B8_WIDTH 16
#define object_ik_transform_Tex_0176B8_HEIGHT 16
extern u64 object_ik_transform_Tex_0176B8[TEX_LEN(u64, object_ik_transform_Tex_0176B8_WIDTH, object_ik_transform_Tex_0176B8_HEIGHT, 8)];
extern Vtx gIronKnuckleTransformHelmetVtx[];
extern Vtx gIronKnuckleTransformGerudoHeadVtx[];
extern Vtx gIronKnuckleTransformHelmetMarkingVtx[];
extern Gfx gIronKnuckleTransformHelmetDL[81];
extern Gfx gIronKnuckleTransformGerudoHeadDL[417];
extern Gfx gIronKnuckleTransformHelmetMarkingDL[38];
extern Vtx object_ik_transform_Vtx_019F38[];
extern Vtx object_ik_transform_Vtx_01A0F8[];
extern Vtx object_ik_transform_Vtx_01A1E8[];
extern Vtx object_ik_transform_Vtx_01A3F8[];
extern Vtx object_ik_transform_Vtx_01A5B8[];
extern Vtx object_ik_transform_Vtx_01A6A8[];
extern Vtx object_ik_transform_Vtx_01A8C8[];
extern Vtx object_ik_transform_Vtx_01ACA8[];
extern Vtx object_ik_transform_Vtx_01AEB8[];
extern Vtx object_ik_transform_Vtx_01B048[];
extern Vtx object_ik_transform_Vtx_01B258[];
extern Vtx gIronKnuckleTransformTorsoVtx[];
extern Vtx object_ik_transform_Vtx_01B8D8[];
extern Gfx gIronKnuckleTransformTorsoDL[132];
extern Gfx object_ik_transform_DL_01BE98[83];
extern Gfx object_ik_transform_DL_01C130[49];
extern Gfx object_ik_transform_DL_01C2B8[83];
extern Gfx object_ik_transform_DL_01C550[49];
extern Gfx object_ik_transform_DL_01C6D8[28];
extern Gfx object_ik_transform_DL_01C7B8[116];
extern Gfx object_ik_transform_DL_01CB58[41];
extern Gfx object_ik_transform_DL_01CCA0[72];
extern Gfx object_ik_transform_DL_01CEE0[122];
extern Gfx object_ik_transform_DL_01D2B0[41];
extern Gfx object_ik_transform_DL_01D3F8[72];
extern Gfx object_ik_transform_DL_01D638[110];
//#define object_ik_transform_Tlut_01D9A8_TLUT_COUNT 256
extern u64 object_ik_transform_Tlut_01D9A8[];
#define object_ik_transform_Tex_01DBA8_WIDTH 16
#define object_ik_transform_Tex_01DBA8_HEIGHT 16
extern u64 object_ik_transform_Tex_01DBA8[TEX_LEN(u64, object_ik_transform_Tex_01DBA8_WIDTH, object_ik_transform_Tex_01DBA8_HEIGHT, 16)];
#define gIronKnuckleTransformHair3Tex_WIDTH 16
#define gIronKnuckleTransformHair3Tex_HEIGHT 16
extern u64 gIronKnuckleTransformHair3Tex[TEX_LEN(u64, gIronKnuckleTransformHair3Tex_WIDTH, gIronKnuckleTransformHair3Tex_HEIGHT, 8)];
#define gIronKnuckleTransformNabooruChestJewelTex_WIDTH 16
#define gIronKnuckleTransformNabooruChestJewelTex_HEIGHT 16
extern u64 gIronKnuckleTransformNabooruChestJewelTex[TEX_LEN(u64, gIronKnuckleTransformNabooruChestJewelTex_WIDTH, gIronKnuckleTransformNabooruChestJewelTex_HEIGHT, 8)];
extern StandardLimb object_ik_transform_01DFA8_Limb;
extern StandardLimb object_ik_transform_01DFB4_Limb;
extern StandardLimb object_ik_transform_01DFC0_Limb;
extern StandardLimb object_ik_transform_01DFCC_Limb;
extern StandardLimb object_ik_transform_01DFD8_Limb;
extern StandardLimb object_ik_transform_01DFE4_Limb;
extern StandardLimb object_ik_transform_01DFF0_Limb;
extern StandardLimb object_ik_transform_01DFFC_Limb;
extern StandardLimb object_ik_transform_01E008_Limb;
extern StandardLimb object_ik_transform_01E014_Limb;
extern StandardLimb object_ik_transform_01E020_Limb;
extern StandardLimb object_ik_transform_01E02C_Limb;
extern StandardLimb object_ik_transform_01E038_Limb;
extern StandardLimb object_ik_transform_01E044_Limb;
extern StandardLimb object_ik_transform_01E050_Limb;
extern StandardLimb object_ik_transform_01E05C_Limb;
extern StandardLimb object_ik_transform_01E068_Limb;
extern StandardLimb object_ik_transform_01E074_Limb;
extern StandardLimb object_ik_transform_01E080_Limb;
extern StandardLimb object_ik_transform_01E08C_Limb;
extern StandardLimb object_ik_transform_01E098_Limb;
extern StandardLimb object_ik_transform_01E0A4_Limb;
extern StandardLimb object_ik_transform_01E0B0_Limb;
extern StandardLimb object_ik_transform_01E0BC_Limb;
extern StandardLimb object_ik_transform_01E0C8_Limb;
extern StandardLimb object_ik_transform_01E0D4_Limb;
extern StandardLimb object_ik_transform_01E0E0_Limb;
extern StandardLimb object_ik_transform_01E0EC_Limb;
extern StandardLimb object_ik_transform_01E0F8_Limb;
extern void* gIronKnuckleTransformLimbs[];
typedef enum gIronKnuckleTransformSkelLimb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_01E178_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_01DFA8,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_01DFB4,
    /*  3 */ LIMB_OBJECT_IK_TRANSFORM_01DFC0,
    /*  4 */ LIMB_OBJECT_IK_TRANSFORM_01DFCC,
    /*  5 */ LIMB_OBJECT_IK_TRANSFORM_01DFD8,
    /*  6 */ LIMB_OBJECT_IK_TRANSFORM_01DFE4,
    /*  7 */ LIMB_OBJECT_IK_TRANSFORM_01DFF0,
    /*  8 */ LIMB_OBJECT_IK_TRANSFORM_01DFFC,
    /*  9 */ LIMB_OBJECT_IK_TRANSFORM_01E008,
    /* 10 */ LIMB_OBJECT_IK_TRANSFORM_01E014,
    /* 11 */ LIMB_OBJECT_IK_TRANSFORM_01E020,
    /* 12 */ LIMB_OBJECT_IK_TRANSFORM_01E02C,
    /* 13 */ LIMB_OBJECT_IK_TRANSFORM_01E038,
    /* 14 */ LIMB_OBJECT_IK_TRANSFORM_01E044,
    /* 15 */ LIMB_OBJECT_IK_TRANSFORM_01E050,
    /* 16 */ LIMB_OBJECT_IK_TRANSFORM_01E05C,
    /* 17 */ LIMB_OBJECT_IK_TRANSFORM_01E068,
    /* 18 */ LIMB_OBJECT_IK_TRANSFORM_01E074,
    /* 19 */ LIMB_OBJECT_IK_TRANSFORM_01E080,
    /* 20 */ LIMB_OBJECT_IK_TRANSFORM_01E08C,
    /* 21 */ LIMB_OBJECT_IK_TRANSFORM_01E098,
    /* 22 */ LIMB_OBJECT_IK_TRANSFORM_01E0A4,
    /* 23 */ LIMB_OBJECT_IK_TRANSFORM_01E0B0,
    /* 24 */ LIMB_OBJECT_IK_TRANSFORM_01E0BC,
    /* 25 */ LIMB_OBJECT_IK_TRANSFORM_01E0C8,
    /* 26 */ LIMB_OBJECT_IK_TRANSFORM_01E0D4,
    /* 27 */ LIMB_OBJECT_IK_TRANSFORM_01E0E0,
    /* 28 */ LIMB_OBJECT_IK_TRANSFORM_01E0EC,
    /* 29 */ LIMB_OBJECT_IK_TRANSFORM_01E0F8,
    /* 30 */ LIMB_OBJECT_IK_TRANSFORM_01E178_MAX
} gIronKnuckleTransformSkelLimb;
extern FlexSkeletonHeader gIronKnuckleTransformSkel;
extern s16 gIronKnuckleTransformUnused3FrameData[];
extern JointIndex gIronKnuckleTransformUnused3JointIndices[];
extern AnimationHeader gIronKnuckleTransformUnused3Anim;
extern s16 object_ik_transform_Anim_01EB14_0601E830_FrameData[];
extern JointIndex object_ik_transform_Anim_01EB14_0601EB08_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_01EB14;
extern StandardLimb object_ik_transform_01EB30_Limb;
extern void* object_ik_transform_Skel_01EB40_0601EB3C_Limbs[];
typedef enum object_ik_transform_Skel_01EB40Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_01EB40_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_01EB30,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_01EB40_MAX
} object_ik_transform_Skel_01EB40Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_01EB40;
extern s16 object_ik_transform_Anim_01EE34_0601EB50_FrameData[];
extern JointIndex object_ik_transform_Anim_01EE34_0601EE28_JointIndices[];
extern AnimationHeader object_ik_transform_Anim_01EE34;
extern StandardLimb object_ik_transform_01EE50_Limb;
extern void* object_ik_transform_Skel_01EE60_0601EE5C_Limbs[];
typedef enum object_ik_transform_Skel_01EE60Limb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_01EE60_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_01EE50,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_01EE60_MAX
} object_ik_transform_Skel_01EE60Limb;
extern FlexSkeletonHeader object_ik_transform_Skel_01EE60;
extern s16 gIronKnuckleTransformNabooruDeathFrameData[];
extern JointIndex gIronKnuckleTransformNabooruDeathJointIndices[];
extern AnimationHeader gIronKnuckleTransformNabooruDeathAnim;
extern StandardLimb object_ik_transform_0203F0_Limb;
extern StandardLimb object_ik_transform_0203FC_Limb;
extern StandardLimb object_ik_transform_020408_Limb;
extern StandardLimb object_ik_transform_020414_Limb;
extern StandardLimb object_ik_transform_020420_Limb;
extern StandardLimb object_ik_transform_02042C_Limb;
extern StandardLimb object_ik_transform_020438_Limb;
extern StandardLimb object_ik_transform_020444_Limb;
extern StandardLimb object_ik_transform_020450_Limb;
extern StandardLimb object_ik_transform_02045C_Limb;
extern StandardLimb object_ik_transform_020468_Limb;
extern StandardLimb object_ik_transform_020474_Limb;
extern StandardLimb object_ik_transform_020480_Limb;
extern StandardLimb object_ik_transform_02048C_Limb;
extern StandardLimb object_ik_transform_020498_Limb;
extern StandardLimb object_ik_transform_0204A4_Limb;
extern StandardLimb object_ik_transform_0204B0_Limb;
extern StandardLimb object_ik_transform_0204BC_Limb;
extern StandardLimb object_ik_transform_0204C8_Limb;
extern StandardLimb object_ik_transform_0204D4_Limb;
extern StandardLimb object_ik_transform_0204E0_Limb;
extern StandardLimb object_ik_transform_0204EC_Limb;
extern StandardLimb object_ik_transform_0204F8_Limb;
extern StandardLimb object_ik_transform_020504_Limb;
extern StandardLimb object_ik_transform_020510_Limb;
extern StandardLimb object_ik_transform_02051C_Limb;
extern StandardLimb object_ik_transform_020528_Limb;
extern StandardLimb object_ik_transform_020534_Limb;
extern StandardLimb object_ik_transform_020540_Limb;
extern void* gIronKnuckleTransformDefeatLimbs[];
typedef enum gIronKnuckleTransformDefeatSkelLimb {
    /*  0 */ LIMB_OBJECT_IK_TRANSFORM_0205C0_NONE,
    /*  1 */ LIMB_OBJECT_IK_TRANSFORM_0203F0,
    /*  2 */ LIMB_OBJECT_IK_TRANSFORM_0203FC,
    /*  3 */ LIMB_OBJECT_IK_TRANSFORM_020408,
    /*  4 */ LIMB_OBJECT_IK_TRANSFORM_020414,
    /*  5 */ LIMB_OBJECT_IK_TRANSFORM_020420,
    /*  6 */ LIMB_OBJECT_IK_TRANSFORM_02042C,
    /*  7 */ LIMB_OBJECT_IK_TRANSFORM_020438,
    /*  8 */ LIMB_OBJECT_IK_TRANSFORM_020444,
    /*  9 */ LIMB_OBJECT_IK_TRANSFORM_020450,
    /* 10 */ LIMB_OBJECT_IK_TRANSFORM_02045C,
    /* 11 */ LIMB_OBJECT_IK_TRANSFORM_020468,
    /* 12 */ LIMB_OBJECT_IK_TRANSFORM_020474,
    /* 13 */ LIMB_OBJECT_IK_TRANSFORM_020480,
    /* 14 */ LIMB_OBJECT_IK_TRANSFORM_02048C,
    /* 15 */ LIMB_OBJECT_IK_TRANSFORM_020498,
    /* 16 */ LIMB_OBJECT_IK_TRANSFORM_0204A4,
    /* 17 */ LIMB_OBJECT_IK_TRANSFORM_0204B0,
    /* 18 */ LIMB_OBJECT_IK_TRANSFORM_0204BC,
    /* 19 */ LIMB_OBJECT_IK_TRANSFORM_0204C8,
    /* 20 */ LIMB_OBJECT_IK_TRANSFORM_0204D4,
    /* 21 */ LIMB_OBJECT_IK_TRANSFORM_0204E0,
    /* 22 */ LIMB_OBJECT_IK_TRANSFORM_0204EC,
    /* 23 */ LIMB_OBJECT_IK_TRANSFORM_0204F8,
    /* 24 */ LIMB_OBJECT_IK_TRANSFORM_020504,
    /* 25 */ LIMB_OBJECT_IK_TRANSFORM_020510,
    /* 26 */ LIMB_OBJECT_IK_TRANSFORM_02051C,
    /* 27 */ LIMB_OBJECT_IK_TRANSFORM_020528,
    /* 28 */ LIMB_OBJECT_IK_TRANSFORM_020534,
    /* 29 */ LIMB_OBJECT_IK_TRANSFORM_020540,
    /* 30 */ LIMB_OBJECT_IK_TRANSFORM_0205C0_MAX
} gIronKnuckleTransformDefeatSkelLimb;
extern FlexSkeletonHeader gIronKnuckleTransformDefeatSkel;

#endif
