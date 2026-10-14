#ifndef GSINPUT_HPP
#define GSINPUT_HPP
#include <dolphin/types.h>
extern "C" {
void GSinputClearButtonData(s32, s32);
void GSinputMotorStart(s32, u8, u8, s32, u8);
u8 GSinputGetRightStickYData(s32, s32);
u8 GSinputGetRightStickXData(s32, s32);
u8 GSinputGetLeftStickYData(s32, s32);
u8 GSinputGetLeftStickXData(s32, s32);
s32 GSinputButtonsRepeat(s32);
s32 GSinputButtonsChanged(s32);
u16 GSinputButtonsPressed(s32);
s32 GSinputGetSubType(s32);
void GSinputResetRightSmoothing(s32, s8, s8);
void GSinputResetLeftSmoothing(s32, s8, s8);
void GSinputSetSmoothingFunc(s32, s32);
void GSinputSetSmoothingRate(s32, u8);
void GSinputSetClamping(s32, s32);
s32 GSinputIsConnected(s32);
s32 GSinputRead(s32);
void GSinputReadEnd();
void GSinputReadStart();
s32 GSinputOpen(s32);
void GSinputInit();
}
#endif
