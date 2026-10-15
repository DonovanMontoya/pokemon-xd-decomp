#include <global.h>
static const f32 _screenshotZero = 0.0f;
extern "C" {
void GSgfxSSUpdate__Fv() {}
void GSgfxSSGetViewportOffset__FPfPf(f32* x, f32* y) {
    *x = _screenshotZero;
    *y = _screenshotZero;
}
}
