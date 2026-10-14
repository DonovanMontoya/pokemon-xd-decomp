/* Debug menu entries for the waza viewer launcher. */
#include <global.h>

typedef struct DbgWazaViewerData {
    u8 unk0[0x16];
    u8 unk16;
    u8 unk17;
    u8 unk18[0x18];
    s32 unk30;
} DbgWazaViewerData;

extern "C" {
void GSfloorPop(void);
void GSfloorPush(s32);
void GSthreadSwitch(void);
void menuClose(s32);
u8 menuIsCheck(s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSetPosition(s32, s32, s32);

extern DbgWazaViewerData wazaViewerData;

s32 dbgMenuWazaDebugStop(void) {
    if (wazaViewerData.unk30 != 0) {
        GSfloorPop();
    }
    return 0;
}

s32 dbgMenuPokemonDebugSelect(void) {
    if (menuIsCheck(0x26)) {
        menuClose(0x26);
    } else {
        wazaViewerData.unk16 = 0;
        wazaViewerData.unk17 = 0;
        menuOpenCustom(0x26, 0, 0, 0, 1, 0);
        menuSetPosition(0x26, 0xC, 0xA);
    }
    return 0;
}

s32 dbgMenuWazaDebugSelect(void) {
    if (menuIsCheck(0x15)) {
        menuClose(0x15);
    } else {
        menuOpenCustom(0x15, 0, 0, 0, 1, 0);
        menuSetPosition(0x15, 0xC, 0xA);
    }
    return 0;
}

s32 dbgMenuWazaDebugStart(void) {
    if (menuIsCheck(0x11)) {
        menuClose(0x11);
    }
    if (wazaViewerData.unk30 == 0) {
        GSfloorPush(0x3E7);
        GSthreadSwitch();
    }
    return 0;
}

s32 dbgMenuWazaMain(void) {
    return 1;
}
}
