#include "transform_fade.h"
#include "config.h"
#include "z_math.h"
#include "printf.h"

// Alpha change per frame such that a full 0<->255 ramp takes TRANSFORM_FADE_DURATION frames
#define TRANSFORM_FADE_STEP ((255 + TRANSFORM_FADE_DURATION - 1) / TRANSFORM_FADE_DURATION)

static s32 sFadeAlpha = 255;
static s32 sFadeTarget = 255;

void TransformFade_Reset(void) {
    sFadeAlpha = 255;
    sFadeTarget = 255;
}

void TransformFade_BeginFadeIn(void) {
    sFadeAlpha = 0;
    sFadeTarget = 255;
}

void TransformFade_BeginFadeOut(void) {
    sFadeTarget = 0;
}

s32 TransformFade_Update(void) {
    PRINTF("TransformFade alpha: %d\n", sFadeAlpha);
    if (sFadeAlpha < sFadeTarget) {
        sFadeAlpha = CLAMP(sFadeAlpha + TRANSFORM_FADE_STEP, 0, sFadeTarget);
    } else if (sFadeAlpha > sFadeTarget) {
        sFadeAlpha = CLAMP(sFadeAlpha - TRANSFORM_FADE_STEP, sFadeTarget, 255);
    }

    return sFadeAlpha == sFadeTarget;
}

u8 TransformFade_GetAlpha(void) {
    return sFadeAlpha;
}

s32 TransformFade_IsActive(void) {
    return sFadeAlpha != sFadeTarget;
}
