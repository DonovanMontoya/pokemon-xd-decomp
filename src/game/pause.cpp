#include <global.h>

extern "C" {
void GSgfxRenderUnpause();
void GSgfxRenderPause();
void GSsndPopVolumeALL(u32, u32, u32);
void GSsndPushVolumeALL(u32, u32, u32, u32);
void GSgappPauseOff();
void GSgappPauseOn();
u32 soundGetBGMID();
void GSsndContinue(u32, u32, u32);
void GSsndPause(u32, u32, u32);
void GSmovieAllContinue();
void GSmovieAllPause();
u32 GSgappCreate(u32, u32, u32, void (*)(u32, u32));
}

static u8 _pauseFlag;
static u8 _enablePauseFlag;
static u32 _sound_id;
static u32 _gappPadReadHandle;

extern "C" u8 pauseIsPause() { return _pauseFlag; }

extern "C" void pauseOff() {
    if (_pauseFlag != 0) {
        _pauseFlag = 0;
        GSgfxRenderUnpause();
        GSsndPopVolumeALL(0, 0, 1);
        GSgappPauseOff();
        if (_sound_id != 0xFFFFFFFF) GSsndContinue(_sound_id, 0x32, 0);
        GSmovieAllContinue();
    }
}

extern "C" void pauseOn() {
    if (_pauseFlag == 0 && _enablePauseFlag != 0) {
        _pauseFlag = 1;
        GSgfxRenderPause();
        GSsndPushVolumeALL(0, 0, 0, 1);
        GSgappPauseOn();
        _sound_id = soundGetBGMID();
        if (_sound_id != 0xFFFFFFFF) GSsndPause(_sound_id, 0x32, 0);
        GSmovieAllPause();
    }
}

static void _pauseDaemon(u32, u32) {}

extern "C" void pauseInit() {
    _pauseFlag = 0;
    _enablePauseFlag = 1;
    _gappPadReadHandle = GSgappCreate(1, 0, 0, _pauseDaemon);
}
