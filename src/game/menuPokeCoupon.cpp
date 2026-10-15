#pragma force_active on
#include <dolphin/types.h>
extern "C" {void GSfloorChange(s32);void __assert(const char*,s32,const char*);void menuShopOpen(s32);}
static s32 _menuPokeCouponWork = -1;

extern "C" void menuPokeCouponExit(void) {
    _menuPokeCouponWork = -1;
}

extern "C" void menuPokeCouponMain(void) {
    switch ((s32) _menuPokeCouponWork) {            /* irregular */
    case 0:
        menuShopOpen(9);
        break;
    case 1:
        menuShopOpen(0xA);
        break;
    }
    GSfloorChange(0x395);
}

extern "C" void menuPokeCouponInit(void) {
    if ((s32) _menuPokeCouponWork == -1) {
        __assert("menuPokeCoupon.c", 0x3C, "POKECOUPONREFER_INVALID != _menuPokeCouponWork.m_eRefer");
    }
}

#pragma force_active reset
