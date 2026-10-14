/* Debug menu entries for the GS video/capture tool. */
#include <global.h>

extern "C" {
void GSgfxCaptureMovieStart(s32);
void GSgfxCaptureMovieStop(void);
void GSgfxCaptureSetTarget(s32);
u32 GSinputButtonsChanged(s32);
u32 GSinputButtonsPressed(s32);
void GSvtrDisable(void);
void GSvtrEnable(void);
u8 GSvtrGetInfoDisp(void);
u8 GSvtrIsActive(void);
void GSvtrPause(void);
void GSvtrPlay(void);
void GSvtrSetInfoDisp(u8, u8);
void GSvtrSingleStep(void);
void GSvtrSlowPlay(void);
void soundOpenPlay(s32, s32, s32);
}

static u8 _vtrWantCapture;
static u8 _vtrIsCapturing;

extern "C" {

void dbgMenuGSvtrCaptureUpdate(void) {
    u32 changed = GSinputButtonsChanged(1);

    if (GSinputButtonsPressed(1) & changed & 0x10) {
        switch (_vtrIsCapturing) {
        case 0:
            if (_vtrWantCapture != 0) {
                soundOpenPlay(8, 0, 0);
                GSgfxCaptureMovieStart(0x4650);
                _vtrWantCapture = 0;
                _vtrIsCapturing = 1;
            }
            break;
        case 1:
            GSgfxCaptureMovieStop();
            _vtrIsCapturing = 0;
            break;
        }
    }
}

s32 dbgMenuGSvtrCaptureSD(void) {
    GSgfxCaptureSetTarget(1);
    _vtrWantCapture = 1;
    GSvtrSetInfoDisp(GSvtrGetInfoDisp(), 1);
    return 0;
}

s32 dbgMenuGSvtrCaptureBBA(void) {
    GSgfxCaptureSetTarget(0);
    _vtrWantCapture = 1;
    GSvtrSetInfoDisp(GSvtrGetInfoDisp(), 1);
    return 0;
}

s32 dbgMenuGSvtrSlow(void) {
    GSvtrSlowPlay();
    return 0;
}

s32 dbgMenuGSvtrStep(void) {
    GSvtrSingleStep();
    return 0;
}

s32 dbgMenuGSvtrPause(void) {
    GSvtrPause();
    return 0;
}

s32 dbgMenuGSvtrPlay(void) {
    GSvtrPlay();
    return 0;
}

s32 dbgMenuGSvtrChangeDisp(void) {
    GSvtrSetInfoDisp(GSvtrGetInfoDisp() == 0, _vtrWantCapture);
    return 0;
}

s32 dbgMenuGSvtrChangeActive(void) {
    if (GSvtrIsActive() == 0) {
        GSvtrEnable();
    } else {
        GSvtrDisable();
    }
    return 0;
}

}
