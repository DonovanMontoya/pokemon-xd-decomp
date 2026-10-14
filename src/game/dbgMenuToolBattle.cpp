/* Debug menu entries for the battle tool (GBA coupon / connection toggles). */
#include <global.h>

extern "C" {
void menuCBDebug_SkipAGBConnection(u8);
void menuClose(s32);
s32 menuOpen(s32, s32);

s32 dbgMenuGBAAddCoupon_value;
s32 dbgMenuGBAResetCoupon_on;
s32 dbgMenuGBASetClearFlag_on;
s32 dbgMenuGBAClearCouponFlag_on;

s32 dbgMenuGBAClearCouponFlag(void) {
    dbgMenuGBASetClearFlag_on = 0;
    dbgMenuGBAClearCouponFlag_on++;
    return 0;
}

s32 dbgMenuGBASetClearFlag(void) {
    dbgMenuGBASetClearFlag_on += 1;
    return 0;
}

s32 dbgMenuGBAResetCoupon(void) {
    dbgMenuGBAAddCoupon_value = 0;
    dbgMenuGBAResetCoupon_on++;
    return 0;
}

s32 dbgMenuGBAAddCoupon(void) {
    s32 value = menuOpen(2, 1);

    menuClose(2);
    if (value >= 0) {
        dbgMenuGBAAddCoupon_value += value;
    }
    return 0;
}

s32 dbgToolBattleDebugSetAGBConnectionMode(s32 unused, s32 mode) {
    menuCBDebug_SkipAGBConnection(mode == 0);
    return 0;
}
}
