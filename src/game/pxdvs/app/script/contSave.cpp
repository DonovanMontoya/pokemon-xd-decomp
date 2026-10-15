#include <global.h>

extern "C" {
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s8 menuSubOpenYesNoField();
s32 GSfloorChange(s32);
}

static s32 _coutineSave() {
    s32 state = 0;
    s32 done = 0;
    do {
        switch (state) {
        case 2:
            break;
        case 0: {
            winMsgOpen(2, 1, 1, 1);
            s8 result = menuSubOpenYesNoField();
            winMsgClose(1);
            if (result != 0) done = 1;
            else state = 2;
            break;
        }
        case 3:
            GSfloorChange(0x395);
            state = 4;
            break;
        case 4:
            done = 1;
            break;
        }
    } while (done == 0);
    return 0;
}

extern "C" s32 scriptBattleMountainEnd(s32) {
    GSfloorChange(0x395);
    return 0;
}

extern "C" s32 scriptContinueSave() {
    return _coutineSave();
}
