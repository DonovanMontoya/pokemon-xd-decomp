#ifndef GSSND_HPP
#define GSSND_HPP
#include <dolphin/mtx.h>
struct GSsndWork { u8 inUse, volume, pan, surround, volumeDepth, savedVolume[3]; u32 voice; u32 context, options; };
struct GSsndDescriptor { u8 parameters, reserved01; union { u8 flags; struct { u8 environment : 1, streaming : 1, effect : 1, reserved : 1, opened : 1, paused : 1, reservedLow : 2; } bits; }; u8 reserved03; u16 effect, file; GSsndWork* work; };
struct GSsndEmitter { u8 inUse, volume, pan, reserved03; u32 identifier; f32 distance, attenuation; Vec position, velocity; u32 emitterStorage[20]; };
struct GSsndListener { u8 inUse, volume, reserved02[2]; f32 distance, attenuation, scale; Vec position, velocity, direction, up; u32 listenerStorage[36]; };
struct GSsndStreamFileHeader { u32 reserved[7]; s32 loop; u32 loopStart, loopEnd, nibbleCount, reserved2C; u8 reserved30, reserved31, reserved32, reserved33; u32 loopStartSamples, loopEndSamples, sampleCount; };
struct GSsndStreamBufferState { u8 reserved[46]; u8 ready, consumed; u32 readOffset, writeOffset, length; s32 state; };
struct GSsndStream { GSsndStream *first, *second; s32 inUse; u32 voice; void* buffer; u32 bufferSize, sampleCount, readOffset, writeOffset, pendingBytes; u32 identifier; u32 resource, soundID; u16 fadeTime; u8 fadeAction, currentVolume, targetVolume, fadeStep, previousVolume, channel, active, paused, stopped, initialized; GSsndStreamFileHeader header; GSsndStreamBufferState buffers[2]; };
typedef char GSsndEmitterSizeCheck[sizeof(GSsndEmitter) == 0x78 ? 1 : -1];
typedef char GSsndListenerSizeCheck[sizeof(GSsndListener) == 0xd0 ? 1 : -1];
typedef char GSsndStreamSizeCheck[sizeof(GSsndStream) == 0x100 ? 1 : -1];
extern "C" {
void GSsndUpdateSettingsReverbHI(u32);
void GSsndSetVolume(u8, u16, u32, u32);
void GSsndQuit();
s32 GSsndOpenWaveDVD(u32, u32, u32, u32, u32, u32, u32);
s32 GSsndInit(u32, u32, u32, u32, u32);
s32 GSsndIsPlayingStream(u32);
void* GSsndStreamPreFunc(u32);
void GSsndStreamPostFunc(u32, u32);
s32 GSsndPlayNow(u32);
s32 GSsndPlayVolume(u32, u16, u32, u32);
s32 GSsndPlay(u32, u16, u32);
u32 GSsndPopVolumeALL(u16, u32, u32);
u32 GSsndPushVolumeALL(u16, u8, u32, u32);
s32 GSsndGetStatus(u32);
s32 GSsndContinue(u32, u16);
s32 GSsndPause(u32, u16);
s32 GSsndStop(u32, u32, u32);
s32 GSsndStopNow(u32);
s32 GSsndOpen(u32, u32, u32);
s32 GSsndClose(u32);
s32 GSsndGetOutputMode();
void GSsndSetOutputMode(s32);
void GSsndSetMasterVolume(u8, u16, u8, u8);
s32 GSsndCheckEnv(u32);
s32 GSsndCheckStream(u32);
s32 GSsndCheckSE(u32);
void GSsndSetPushVolumeID(u32, u8*);
void GSsndGetPushVolumeID(u32, u8*);
u8 GSsndGetVolume(u32);
s32 GSsndPopVolumeID(u32, u16);
s32 GSsndPushVolumeID(u32, u16, u8);
s32 GSsndSetOriginalVolume(u32, u16, u8);
s32 GSsndCheckEmitter(GSsndEmitter*);
s32 GSsndUpdateEmitter(GSsndEmitter*, Vec*);
s32 GSsndFreeEmitter(GSsndEmitter*);
s32 GSsndUpdateListenerParam(GSsndListener*, Vec*, Vec*, Vec*);
s32 GSsndFreeListener(GSsndListener*);
GSsndEmitter* GSsndCreateEmitter(u32, Vec*);
GSsndEmitter* GSsndCreateEmitterParam(u32, Vec*, Vec*, s8, s8, f32, f32);
GSsndListener* GSsndCreateListener(Vec*);
GSsndListener* GSsndCreateListenerParam(Vec*, Vec*, Vec*, Vec*, s8, f32, f32, f32);
}
#endif
