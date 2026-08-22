/*
 * Drives the alpha ramp used to cross-fade a player transformation's creature mesh in/out,
 * replacing the old full-screen fade/flash. See src/code/z_transform_fade.c.
 *
 * The creature actor (ovl_Transform_Baby_Gohma, ovl_Transform_Ik) only ever reads
 * `TransformFade_GetAlpha` to drive its own draw call; `z_player.c` owns calling
 * `TransformFade_Update` each frame and orchestrating the begin/end of each phase.
 */
#ifndef TRANSFORM_FADE_H
#define TRANSFORM_FADE_H

#include "ultra64.h"

void TransformFade_Reset(void);
void TransformFade_BeginFadeIn(void);
void TransformFade_BeginFadeOut(void);
s32 TransformFade_Update(void);
u8 TransformFade_GetAlpha(void);
s32 TransformFade_IsActive(void);

#endif
