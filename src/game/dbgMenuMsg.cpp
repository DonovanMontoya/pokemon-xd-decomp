#include <global.h>

extern "C" {
void fadeSet(s32, f32);
void fadeCheck(s32);
void winMsgOpenError(s32, s32, s32);
void winMsgClose(s32);
void winMsgCloseFight(s32);
void winMsgCloseError(s32);
void winMsgOpenField(s32, s32, s32);
void winMsgCloseField(s32);
void GSthreadSwitch(void);
void msgctrlSetValue(s32, s32);
u32 GSinputButtonsPressed(s32);
u8 menuSubOpenNumberInputDigit(s32, s32*);
void menuSubKeyWait(void);

s32 dbgMenuMsgTest(s32 unused, s32 mode) {
    switch (mode) {
    case 0:
        fadeSet(3, 0.5f);
        fadeCheck(1);
        winMsgOpenError(1, 1, 0);
        winMsgClose(1);
        fadeSet(2, 0.5f);
        fadeCheck(1);
        break;
    case 1:
        winMsgCloseFight(1);
        winMsgCloseError(1);
        break;
    case 2:
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
        winMsgCloseFight(0);
        GSthreadSwitch();
        GSthreadSwitch();
        break;
    case 3:
        msgctrlSetValue(0x31, 0x7DA);
        break;
    }
    return 0;
}

s32 dbgMenuMsgCheck(void) {
    s32 value;
    if (GSinputButtonsPressed(1) & 0x20) {
        if (!menuSubOpenNumberInputDigit(0, &value)) {
            return -1;
        }
        winMsgOpenField(value, 1, 0);
        menuSubKeyWait();
        winMsgCloseField(1);
        return 0;
    }
    return 1;
}
}
