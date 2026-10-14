#include <global.h>

extern "C" {
u8 menuIsCheck(s32);
void menuClose(s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSetPosition(s32, s32, s16);
u8 GSgfxLayerGetStatsRenderMode(void);
void GSgfxLayerSetStatsRenderMode(u8);

s32 dbgMenuGSgfxChangeDisp(void) {
    if (menuIsCheck(8)) {
        menuClose(8);
    } else {
        menuOpenCustom(8, 0, 0, 0, 1, 0);
        menuSetPosition(8, 0x17C, 0x20);
    }
    return 0;
}

s32 dbgMenuLayerFifoDisp(void) {
    if (!GSgfxLayerGetStatsRenderMode()) {
        GSgfxLayerSetStatsRenderMode(1);
    } else {
        GSgfxLayerSetStatsRenderMode(0);
    }
    return 0;
}
}
