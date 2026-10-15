#include <global.h>

extern "C" {
u8 pauseIsPause();
f32 GSgfxVideoGetLastRenderTime();
u8 GSgfxVideoGetVsyncRate();
}

extern "C" s32 timeGetLastFrameTime() {
    u32 paused = pauseIsPause();
    if (paused != 0) return 0;
    return (u32)(0.5f + GSgfxVideoGetLastRenderTime());
}

extern "C" f32 timeGetLastFrameSec() {
    u32 paused = pauseIsPause();
    if (paused > 0) return 0.0f;
    f32 rate = (f32)GSgfxVideoGetVsyncRate();
    f32 renderTime = GSgfxVideoGetLastRenderTime();
    return renderTime / rate;
}
