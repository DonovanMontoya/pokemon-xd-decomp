#include <global.h>

extern "C" {
u8 menuIsCheck(s32);
s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
void menuSetPosition(s32, s32, s16);
u32 GSfloorGetCurrent(void);
u32 floorFieldCameraEditorGetFloorID(void);
void floorInitFieldCameraEditor(u32);
}

static s32 gSelected_row;
static s32 gSelected_column;
static s32 gSelectedMenu_column;
static u8 gSaveResult;

extern "C" {
s32 dbgMenuFieldCameraChangeDisp(void) {
    if (!menuIsCheck(0x23)) {
        u32 floor = GSfloorGetCurrent();
        if (floor != floorFieldCameraEditorGetFloorID()) {
            floorInitFieldCameraEditor(floor);
            gSelected_row = 0;
            gSelected_column = 0;
            gSelectedMenu_column = 0;
        }
        gSaveResult = 0;
        menuOpenCustom(0x23, 0, 0, 0, 1, 0);
        menuSetPosition(0x23, 0xC, 0xA);
    }
    return 0;
}
}
