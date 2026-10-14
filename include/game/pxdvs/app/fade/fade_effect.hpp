#ifndef APP_FADE_EFFECT_HPP
#define APP_FADE_EFFECT_HPP
#include <global.h>

// Each effect is installed in the fade controller with a no-argument initializer.
extern "C" {
void fadeEffectInit();
void fadeEffectHookFunction_virtual_end_Init();
void fadeEffectHookFunction_trainer_second_Init();
void fadeEffectHookFunction_slide_ball_Init();
void fadeEffectHookFunction_four_ball_Init();
void fadeEffectHookFunction_distortion_strip_yoko_Init();
void fadeEffectHookFunction_distortion_strip_tate_Init();
void fadeEffectHookFunction_dist_yoko_Init();
void fadeEffectHookFunction_dist_zoom_out_Init();
void fadeEffectHookFunction_dist_zoom_in_Init();
void fadeEffectHookFunction_blur_ball_Init();
void fadeEffectHookFunction_tear_off_Init();
void fadeEffectHookFunction_ball_second_Init();
void fadeEffectHookFunction_bound_ball_Init();
void fadeEffectHookFunction_dist_ball_Init();
void fadeEffectHookFunction_boss_second_Init();
void fadeEffectHookFunction_distortion_Init();
void fadeEffectHookFunction_Doku_Init();
void fadeEffectHookFunction_trainer_Init();
void fadeEffectHookFunction_fadein_Init();
void fadeEffectHookFunction_fadeout_in_Init();
void fadeEffectHookFunction_carde_Init();
void fadeEffectHookFunction_boss_Init();
void fadeEffectHookFunction_ball_Init();
void fadeEffectHookFunction_tate_Init();
void fadeEffectHookFunction_yoko_Init();
void fadeEffectHookFunction_yoko_or_tate_Init();
void fadeEffectHookFunction_yoko_or_tate_or_ball_Init();
}
#endif
