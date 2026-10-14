#include <global.h>

extern "C" {
u8 menuIsCheck(s32);
void menuClose(s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSetPosition(s32, s32, s16);
s32 GSfloorGetCurrent(void);
void* floorDataBiosGetPtr(s32);
u8 floorFieldCameraDataExist(void);
void floorFieldCameraEnable(void);
void floorFieldCameraDisable(void);
void floorUnblockMainScript(void);
void floorBlockMainScript(void);

s32 dbgMenuDispChangePartyInfo(void) {
    if (menuIsCheck(0xC)) {
        menuClose(0xC);
    } else {
        menuOpenCustom(0xC, 0, 0, 0, 1, 0);
        menuSetPosition(0xC, 0x190, 0x28);
    }
    return 0;
}

s32 dbgMenuPeopleOpenEdit(void) {
    floorDataBiosGetPtr(GSfloorGetCurrent());
    if (menuIsCheck(0xA)) {
        if (floorFieldCameraDataExist()) {
            floorFieldCameraEnable();
        }
        menuClose(0xA);
        floorUnblockMainScript();
    } else {
        floorFieldCameraDisable();
        menuOpenCustom(0xA, 0, 0, 0, 0, 0);
        floorBlockMainScript();
    }
    return 0;
}
}
