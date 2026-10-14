#include <global.h>

extern "C" {
void cameraResetFloor(void);
void cameraSetType(s32);
u8 menuIsCheck(s32);
void menuClose(s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSetPosition(s32, s32, s16);

s32 dbgMenuCameraResetFloor(void) {
    cameraResetFloor();
    return 0;
}

s32 dbgMenuCameraChangeDisp(void) {
    if (menuIsCheck(6)) {
        menuClose(6);
    } else {
        menuOpenCustom(6, 0, 0, 0, 1, 0);
        menuSetPosition(6, 0x14, 0x104);
    }
    return 0;
}

s32 dbgMenuCameraSetType(s32 unused, s32 type) {
    switch (type) {
    case 0:
    default:
        cameraSetType(0);
        break;
    case 1:
        cameraSetType(5);
        break;
    case 2:
        cameraSetType(6);
        break;
    }
    return 0;
}
}
