#include <game/pxdvs/GSAPI/GSinput/GSinput.hpp>
#include <dolphin/os.h>
#include <dolphin/pad.h>
#include <dolphin/si.h>
#include <libc/string.h>
#include <PowerPC_EABI_Support/MSL_C/MSL_Common/Include/cmath>

struct InputDevice {
    s32 id, subType, clamping, error;
    u8 smoothingRate;
    u8 smoothingProgress;
    u8 reserved[2];
    s32 smoothingFunction, repeatState;
    u32 repeatButtons, repeatedButtons;
    f32 repeatTimer;
    PADStatus sampled, current;
    u32 previousButtons;
    s8 previousLeftX, previousLeftY, previousRightX, previousRightY;
    f32 leftStepX, leftStepY, rightStepX, rightStepY;
    f32 smoothLeftX, smoothLeftY, smoothRightX, smoothRightY;
    s8 leftX, leftY, rightX, rightY;
    s32 motorState;
    u32 motorIntensity, motorDuration;
    u8 motorFade;
};
static InputDevice _inputData[4];
static s32 _padMotorLevel[4];
static u32 _padRumble[4];
static u8 _padMotorFlag = 1;
static u8 _inputInitRead;
static s32 _padCallbackCount;
static s32 _padLastVsync;
static u32 _padResetBits;
typedef char InputDeviceSizeCheck[sizeof(InputDevice) == 0x7c ? 1 : -1];
extern "C" {
f32 GSgfxVideoGetLastRenderTime();
u8 GSgfxVideoGetVsyncRate();
static InputDevice* _inputFindDevice(s32);
static void _inputCheckConnect();
static void _inputPadCallback();
static void _inputUpdateMotors();
static void _inputDoRepeat(InputDevice*);
static void _inputInitRepeat(InputDevice*);
static void _inputUpdateSmoothing(InputDevice*);
static void _inputDoSmoothing(InputDevice*, s8, s8, s8*, s8*, f32*, f32*, f32*, f32*);
static void _inputDoClamping(InputDevice*);
static void ClampCircle(s8*, s8*, s8, s8);

void GSinputClearButtonData(s32 id, s32 buttons) {
    InputDevice* device = _inputFindDevice(id);
    if (device) device->current.button &= ~buttons;
}
void GSinputMotorStart(s32 id, u8 mode, u8 intensity, s32 duration, u8 fade) {
    if (_padMotorFlag) {
        InputDevice* device = _inputFindDevice(id);
        if (device && mode == 0) {
            device->motorState = 1;
            device->motorIntensity = intensity * 15;
            device->motorDuration = duration;
            device->motorFade = fade;
        }
    }
}
u8 GSinputGetRightStickYData(s32 id, s32 smoothed) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    if (smoothed == 1) return device->rightY;
    return device->current.substickY;
}
u8 GSinputGetRightStickXData(s32 id, s32 smoothed) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    if (smoothed == 1) return device->rightX;
    return device->current.substickX;
}
u8 GSinputGetLeftStickYData(s32 id, s32 smoothed) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    if (smoothed == 1) return device->leftY;
    return device->current.stickY;
}
u8 GSinputGetLeftStickXData(s32 id, s32 smoothed) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    if (smoothed == 1) return device->leftX;
    return device->current.stickX;
}
s32 GSinputButtonsRepeat(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    return device->repeatedButtons;
}
s32 GSinputButtonsChanged(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    return device->current.button ^ device->previousButtons;
}
u16 GSinputButtonsPressed(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    return device->current.button;
}
s32 GSinputGetSubType(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 2;
    return device->subType;
}
void GSinputResetRightSmoothing(s32 id, s8 x, s8 y) {
    InputDevice* device = _inputFindDevice(id);
    if (device) {
        device->previousRightX = x;
        device->previousRightY = y;
        device->smoothRightX = x;
        device->smoothRightY = y;
    }
}
void GSinputResetLeftSmoothing(s32 id, s8 x, s8 y) {
    InputDevice* device = _inputFindDevice(id);
    if (device) {
        device->previousLeftX = x;
        device->previousLeftY = y;
        device->smoothLeftX = x;
        device->smoothLeftY = y;
    }
}
void GSinputSetSmoothingFunc(s32 id, s32 function) {
    InputDevice* device = _inputFindDevice(id);
    if (device) device->smoothingFunction = function;
}
void GSinputSetSmoothingRate(s32 id, u8 rate) {
    InputDevice* device = _inputFindDevice(id);
    if (device) device->smoothingRate = rate;
}
void GSinputSetClamping(s32 id, s32 clamping) {
    InputDevice* device = _inputFindDevice(id);
    if (device) device->clamping = clamping;
}
s32 GSinputIsConnected(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 0;
    if (device->error == 0) return 1;
    return 0;
}
s32 GSinputRead(s32 id) {
    InputDevice* device = _inputFindDevice(id);
    if (!device) return 2;
    device->previousButtons = device->current.button;
    BOOL interrupts = OSDisableInterrupts();
    memcpy(&device->current, &device->sampled, sizeof(PADStatus));
    OSRestoreInterrupts(interrupts);
    if (_inputInitRead) {
        _inputCheckConnect();
        if (_padResetBits) PADReset(_padResetBits);
        _inputInitRead = 0;
    }
    _inputUpdateSmoothing(device);
    _inputDoClamping(device);
    _inputDoRepeat(device);
    return device->error;
}
void GSinputReadEnd() { _inputInitRead = 0; }
void GSinputReadStart() { _inputInitRead = 1; }
static void _inputCheckConnect() {
    _padResetBits = 0;
    for (s32 channel = 0; channel < 4; ++channel) {
        InputDevice* device = _inputFindDevice(channel + 1);
        if (device) {
            u32 bit;
            s32 type;
            BOOL interrupts;
            interrupts = OSDisableInterrupts();
            bit = 0x80000000 >> channel;
            type = SIProbe(channel);
            OSRestoreInterrupts(interrupts);
            switch (type) {
            case 0x09000000: case 0x8b100000:
                device->subType = 0;
                if (device->current.err == PAD_ERR_NO_CONTROLLER) {
                    _padResetBits |= bit;
                    device->sampled.err = PAD_ERR_NOT_READY;
                    device->error = 3;
                } else device->error = 0;
                break;
            default:
                device->error = 3;
                device->subType = 2;
                device->sampled.err = PAD_ERR_NO_CONTROLLER;
                break;
            }
        }
    }
}
s32 GSinputOpen(s32 id) {
    InputDevice* device = _inputFindDevice(0);
    if (!device) return 4;
    switch (id) {
    case 1: case 2: case 3: case 4: device->id = id; break;
    default: return 1;
    }
    return 0;
}
void GSinputInit() {
    _padCallbackCount = 0;
    _padResetBits = 0xf0000000;
    _padLastVsync = 0;
    for (s32 i = 0; i < 4; ++i) {
        _inputData[i].id = 0;
        _inputData[i].clamping = 0;
        _inputData[i].error = 3;
        _inputData[i].smoothingRate = 0;
        _inputData[i].smoothingFunction = 0;
        _inputData[i].previousButtons = 0;
        memset(&_inputData[i].sampled, 0, sizeof(PADStatus));
        memset(&_inputData[i].current, 0, sizeof(PADStatus));
        _inputData[i].previousLeftX = 0;
        _inputData[i].previousLeftY = 0;
        _inputData[i].previousRightX = 0;
        _inputData[i].previousRightY = 0;
        _inputData[i].smoothLeftX = 0.0f;
        _inputData[i].smoothLeftY = 0.0f;
        _inputData[i].smoothRightX = 0.0f;
        _inputData[i].smoothRightY = 0.0f;
        _inputData[i].motorState = 3;
        _inputData[i].motorIntensity = 0;
        _inputData[i].motorDuration = 0;
        _inputData[i].motorFade = 0;
        _inputInitRepeat(&_inputData[i]);
        _padRumble[i] = PAD_MOTOR_STOP_HARD;
        _padMotorLevel[i] = 0;
    }
    PADSetAnalogMode(0);
    PADInit();
    PADControlAllMotors(_padRumble);
    PADRecalibrate(_padResetBits);
    SISetSamplingRate(11);
    PADSetSamplingCallback(_inputPadCallback);
}
static void _inputPadCallback() {
    PADStatus status[4];
    PADRead(status);
    for (s32 i = 0; i < 4; ++i) {
        PADStatus* pad = &status[i];
        InputDevice* device = _inputFindDevice(i + 1);
        if (device && pad->err != PAD_ERR_TRANSFER) {
            pad->stickY = -pad->stickY;
            pad->substickY = -pad->substickY;
            memcpy(&device->sampled, pad, sizeof(PADStatus));
        }
    }
    _inputUpdateMotors();
    ++_padCallbackCount;
}
static void _inputUpdateMotors() {
    u8 changed = 0;
    for (s32 i = 0; i < 4; ++i) {
        InputDevice* device = _inputFindDevice(i + 1);
        if (device && device->error == 0) {
            switch (device->motorState) {
            case 1:
                if (device->motorIntensity > 3600 && _padRumble[i] != PAD_MOTOR_RUMBLE) {
                    changed = 1;
                    _padRumble[i] = PAD_MOTOR_RUMBLE;
                } else if (device->motorIntensity < 100 && _padRumble[i] != PAD_MOTOR_STOP) {
                    changed = 1;
                    _padRumble[i] = PAD_MOTOR_STOP;
                } else {
                    _padMotorLevel[i] += device->motorIntensity;
                    if (_padMotorLevel[i] > 3600) {
                        _padMotorLevel[i] = 0;
                        if (_padRumble[i] != PAD_MOTOR_RUMBLE) { changed = 1; _padRumble[i] = PAD_MOTOR_RUMBLE; }
                    } else if (_padRumble[i] != PAD_MOTOR_STOP) { changed = 1; _padRumble[i] = PAD_MOTOR_STOP; }
                }
                break;
            case 2:
                if (_padRumble[i] != PAD_MOTOR_STOP) { changed = 1; _padRumble[i] = PAD_MOTOR_STOP; }
                break;
            case 3:
                if (_padRumble[i] != PAD_MOTOR_STOP_HARD) { changed = 1; _padRumble[i] = PAD_MOTOR_STOP_HARD; }
                break;
            }
            if (device->motorDuration && --device->motorDuration == 0) device->motorState = 2;
            if (device->motorFade) {
                if (device->motorIntensity < device->motorFade) { device->motorState = 2; device->motorFade = 0; }
                else device->motorIntensity -= device->motorFade;
            }
        }
    }
    if (changed) PADControlAllMotors(_padRumble);
}
static void _inputDoRepeat(InputDevice* device) {
    u32 pressed = device->current.button;
    pressed &= ~0x60;
    u32 changed = device->current.button & (device->current.button ^ device->previousButtons);
    changed &= ~0x60;
    switch (device->repeatState) {
    case 0:
        device->repeatedButtons = 0;
        device->repeatState = 1;
    case 1:
        if (!changed) { device->repeatedButtons = 0; return; }
        device->repeatButtons = changed;
        device->repeatedButtons = changed;
        device->repeatTimer = 0.6f;
        device->repeatState = 2;
        return;
    case 2: {
        device->repeatedButtons = 0;
        f32 frequency = GSgfxVideoGetVsyncRate();
        device->repeatTimer -= GSgfxVideoGetLastRenderTime() / frequency;
        if (pressed != device->repeatButtons) { device->repeatState = 0; return; }
        if (device->repeatTimer < 0.0f) { device->repeatedButtons = device->repeatButtons; device->repeatTimer = 0.1f; }
        return;
    }
    }
}
static void _inputInitRepeat(InputDevice* device) { device->repeatState = 0; device->repeatedButtons = 0; device->repeatButtons = 0; }
static void _inputUpdateSmoothing(InputDevice* device) {
    _inputDoSmoothing(device, device->current.stickX, device->current.stickY, &device->previousLeftX, &device->previousLeftY, &device->leftStepX, &device->leftStepY, &device->smoothLeftX, &device->smoothLeftY);
    _inputDoSmoothing(device, device->current.substickX, device->current.substickY, &device->previousRightX, &device->previousRightY, &device->rightStepX, &device->rightStepY, &device->smoothRightX, &device->smoothRightY);
}
static void _inputDoSmoothing(InputDevice* device, s8 x, s8 y, s8* oldX, s8* oldY, f32* stepX, f32* stepY, f32* positionX, f32* positionY) {
    f32 absX, absY;
    s32 signX, signY;
    if (*oldX < x - 2 || *oldX > x + 2 || *oldY < y - 2 || *oldY > y + 2) {
        if (device->smoothingFunction == 0) {
            *stepX = ((f32)x - *positionX) / device->smoothingRate;
            *stepY = ((f32)y - *positionY) / device->smoothingRate;
        } else if (device->smoothingFunction == 1) {
            *stepX = ((f32)x - *positionX) / ((f32)device->smoothingRate / 4.0f);
            *stepY = ((f32)y - *positionY) / ((f32)device->smoothingRate / 4.0f);
        }
        device->smoothingProgress = 0;
    }
    *oldX = x;
    *oldY = y;
    *positionX += *stepX;
    *positionY += *stepY;
    if (device->smoothingFunction == 1) {
        ++device->smoothingProgress;
        if (device->smoothingProgress < (u8)device->smoothingRate) {
            *stepX *= 0.5f;
            *stepY *= 0.5f;
            if (*stepX > 0.0f) absX = *stepX;
            else absX = -*stepX;
            if (absX < 1.0f) {
                if (*stepX > 0.0f) signX = 1;
                else signX = -1;
                *stepX = (f32)signX;
            }
            if (*stepY > 0.0f) absY = *stepY;
            else absY = -*stepY;
            // The original uses the X-step sign when clamping the Y step.
            if (absY < 1.0f) {
                if (*stepX > 0.0f) signY = 1;
                else signY = -1;
                *stepY = (f32)signY;
            }
        }
    }
    if (*stepX < 0.0f) { if (*positionX < *oldX) *positionX = *oldX; }
    else if (*positionX > *oldX) *positionX = *oldX;
    if (*stepY < 0.0f) { if (*positionY < *oldY) *positionY = *oldY; }
    else if (*positionY > *oldY) *positionY = *oldY;
}
static void _inputDoClamping(InputDevice* device) {
    switch (device->clamping) {
    case 0:
        device->leftX = (s8)device->smoothLeftX;
        device->leftY = (s8)device->smoothLeftY;
        device->rightX = (s8)device->smoothRightX;
        device->rightY = (s8)device->smoothRightY;
        return;
    case 2: {
        ClampCircle(&device->current.stickX, &device->current.stickY, 56, 10);
        ClampCircle(&device->current.substickX, &device->current.substickY, 44, 10);
        s8 x = (s8)device->smoothLeftX, y = (s8)device->smoothLeftY;
        ClampCircle(&x, &y, 56, 10);
        device->leftX = x; device->leftY = y;
        x = (s8)device->smoothRightX; y = (s8)device->smoothRightY;
        ClampCircle(&x, &y, 44, 10);
        device->rightX = x; device->rightY = y;
    }
    case 1: return;
    }
}
static InputDevice* _inputFindDevice(s32 id) {
    for (s32 i = 0; i < 4; ++i) {
        InputDevice* device = &_inputData[i];
        if (device->id == id) return device;
    }
    return 0;
}
static void ClampCircle(s8* px, s8* py, s8 radius, s8 min) {
    s32 x = *px, y = *py;
    if ((s8)-min < x && x < min) x = 0;
    else if (x > 0) x -= min;
    else x += min;
    if ((s8)-min < y && y < min) y = 0;
    else if (y > 0) y -= min;
    else y += min;
    s32 squared = x * x + y * y;
    if (radius * radius < squared) {
        s32 length = sqrtf(squared);
        x = x * radius / length;
        y = y * radius / length;
    }
    *px = x; *py = y;
}
}
