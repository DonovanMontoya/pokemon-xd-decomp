#include <game/pxdvs/GSAPI/GSsnd/GSsnd.hpp>
#include <game/pxdvs/GSAPI/GSmemman/GSmemman.hpp>
#include <dolphin/os.h>
extern "C" {
extern GSsndDescriptor* snd_data;
extern u32* snd_data_number;
s32 sndEmitterVoiceID(void*);
u8 sndCheckEmitter(void*);
s32 sndFXCheck(u32);
s32 sndFXKeyOff(u32);
void sndRemoveEmitter(void*);
void sndRemoveListener(void*);
u8 sndUpdateEmitter(void*, Vec*, Vec*, u8, u32);
u8 sndUpdateListener(void*, Vec*, Vec*, Vec*, Vec*, u8, u32);
void sndFXCtrl(u32, u8, u8);
void sndSeqVolume(u8, u32, u32, u8);
}
static u8 _initFlag;
static s32 _sndDaemonHDL;
static GSsndStream* _sndStreaming;
static u32 _maxStreaming;
static u32 _SampleDataFileOffset;
static void* _SampleDataFileInfo;
static void* _SampleDataUploadBuffer;
static GSsndEmitter* _sndEmitter;
static u32 _maxEmitter;
static GSsndListener* _sndListener;
static u32 _maxListener;
static u8* _sndStack;
static u32 _maxStack;
static GSsndWork* _sndWork;
static u32 _maxSndWork, _revH_now_parm_id, _maxSoundID;
#pragma dont_inline on
extern "C" {
static u8 _sndCheckEmitter(GSsndEmitter*);
static void _sndFreeEmitter(GSsndEmitter*);
static void _sndFreeListener(GSsndListener*);
static u8 _sndGetProperVolume(GSsndDescriptor*, u32);
static s32 _sndSetVolume(GSsndDescriptor*, u16, u8);
static void _sndStreamVolume(u8, u32, u32, u8);
s32 GSsndCheckEnv(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    return snd_data[id].bits.environment;
}
s32 GSsndCheckStream(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    return snd_data[id].bits.streaming;
}
s32 GSsndCheckSE(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    return snd_data[id].bits.effect;
}
void GSsndSetPushVolumeID(u32 id, u8* volume) {
    if (_initFlag && id != ~0U) {
        if (id >= *snd_data_number) return;
        GSsndWork* work = snd_data[id].work;
        if (work && volume && *volume < 3) {
            work->volumeDepth = *volume;
            for (s32 i = 0; i < *volume; ++i) work->savedVolume[i] = volume[i + 1];
        }
    }
}
void GSsndGetPushVolumeID(u32 id, u8* volume) {
    if (_initFlag && id != ~0U) {
        if (id >= *snd_data_number) return;
        GSsndWork* work = snd_data[id].work;
        if (work && volume && work->volumeDepth < 3) {
            *volume = work->volumeDepth;
            for (s32 i = 0; i < *volume; ++i) volume[i + 1] = work->savedVolume[i];
        }
    }
}
u8 GSsndGetVolume(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    if (((descriptor->flags >> 3) & 1) != 1) return 0;
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    return work->volume;
}
s32 GSsndPopVolumeID(u32 id, u16 time) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndWork* work = snd_data[id].work;
    if (!work) return 0;
    u8 depth = work->volumeDepth;
    if (!depth) return 0;
    work->volumeDepth = depth - 1;
    return GSsndSetOriginalVolume(id, time, work->savedVolume[work->volumeDepth]);
}
s32 GSsndPushVolumeID(u32 id, u16 time, u8 volume) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (work->volumeDepth >= 3) return 0;
    u8 newVolume = _sndGetProperVolume(descriptor, volume);
    u8 originalVolume = work->volume;
    if ((s32)originalVolume < (s32)newVolume) newVolume = originalVolume;
    work->savedVolume[work->volumeDepth] = originalVolume;
    u8 depth = work->volumeDepth;
    if (depth < 2) work->volumeDepth = depth + 1;
    return GSsndSetOriginalVolume(id, time, newVolume);
}
s32 GSsndSetOriginalVolume(u32 id, u16 time, u8 volume) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if (!((flags >> 5) & 1) && (u32)((flags >> 3) & 1) != 1U) return 0;
    return _sndSetVolume(descriptor, time, volume);
}
s32 GSsndCheckEmitter(GSsndEmitter* emitter) {
    if (!_initFlag) return 0;
    if (!emitter) return 0;
    return _sndCheckEmitter(emitter) != 0;
}
s32 GSsndUpdateEmitter(GSsndEmitter* emitter, Vec* position) {
    Vec velocity;
    if (!_initFlag) return 0;
    if (!emitter) return 0;
    if (!_sndCheckEmitter(emitter)) return 0;
    PSVECSubtract(&emitter->position, position, &velocity);
    if (sndUpdateEmitter(emitter->emitterStorage, position, &velocity, emitter->volume, 0)) {
        emitter->position.x = position->x; emitter->position.y = position->y; emitter->position.z = position->z;
        emitter->velocity.x = velocity.x; emitter->velocity.y = velocity.y; emitter->velocity.z = velocity.z;
        return 1;
    }
    return 0;
}
s32 GSsndFreeEmitter(GSsndEmitter* emitter) {
    if (!_initFlag) return 0;
    if (!emitter) return 0;
    if (!emitter->inUse) return 1;
    u32 voice = sndEmitterVoiceID(emitter->emitterStorage);
    if (voice != ~0U) sndFXKeyOff(voice);
    sndRemoveEmitter(emitter->emitterStorage);
    _sndFreeEmitter(emitter);
    return 1;
}
s32 GSsndUpdateListenerParam(GSsndListener* listener, Vec* position, Vec* direction, Vec* up) {
    Vec velocity;
    if (!_initFlag) return 0;
    if (!listener) return 0;
    PSVECSubtract(&listener->position, position, &velocity);
    if (sndUpdateListener(listener->listenerStorage, position, &velocity, direction, up, listener->volume, 0) == 1) {
        listener->position.x = position->x; listener->position.y = position->y; listener->position.z = position->z;
        listener->velocity.x = velocity.x; listener->velocity.y = velocity.y; listener->velocity.z = velocity.z;
        listener->direction.x = direction->x; listener->direction.y = direction->y; listener->direction.z = direction->z;
        listener->up.x = up->x; listener->up.y = up->y; listener->up.z = up->z;
        return 1;
    }
    return 0;
}
s32 GSsndFreeListener(GSsndListener* listener) {
    if (!_initFlag) return 0;
    if (!listener) return 0;
    sndRemoveListener(listener->listenerStorage);
    _sndFreeListener(listener);
    return 1;
}
static u8 _sndCheckEmitter(GSsndEmitter* emitter) {
    if (!emitter->inUse) return 0;
    u32 voice = sndEmitterVoiceID(emitter->emitterStorage);
    if (voice == ~0U) return 0;
    if (!sndCheckEmitter(emitter->emitterStorage)) { sndFXKeyOff(voice); return 0; }
    if ((u32)sndFXCheck(voice) == ~0U) { sndFXKeyOff(voice); return 0; }
    return 1;
}
static u8 _sndGetProperVolume(GSsndDescriptor* descriptor, u32 value) {
    u8 volume = value;
    if (volume == 255) {
        if ((u32)((descriptor->flags >> 5) & 1) == 1U) volume = 100;
        else volume = 127;
    }
    if (volume > 127) volume = 127;
    return volume;
}
static s32 _sndSetVolume(GSsndDescriptor* descriptor, u16 time, u8 volume) {
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    work->volume = _sndGetProperVolume(descriptor, volume);
    u32 voice = work->voice;
    if (voice != ~0U) {
        u8 flags = descriptor->flags;
        if ((u32)((flags >> 6) & 1) == 1U) _sndStreamVolume(work->volume, time, voice, 0);
        else if ((u32)((flags >> 5) & 1) == 1U) sndFXCtrl(voice, 7, work->volume);
        else sndSeqVolume(work->volume, time, voice, 0);
        return 1;
    }
    return 0;
}
static void _sndFreeEmitter(GSsndEmitter* emitter) { BOOL interrupts = OSDisableInterrupts(); emitter->inUse = 0; OSRestoreInterrupts(interrupts); }
static void _sndFreeListener(GSsndListener* listener) { BOOL interrupts = OSDisableInterrupts(); listener->inUse = 0; OSRestoreInterrupts(interrupts); }
static void _sndFreeSndWork(GSsndWork* work) { BOOL interrupts = OSDisableInterrupts(); work->inUse = 0; OSRestoreInterrupts(interrupts); }
static void _sndFreeStream(GSsndStream* stream) { BOOL interrupts = OSDisableInterrupts(); stream->inUse = 0; stream->identifier = 0; OSRestoreInterrupts(interrupts); }
}
#pragma dont_inline reset

#pragma dont_inline on
extern "C" {
static GSsndStream* _sndGetNewStream() {
    BOOL interrupts = OSDisableInterrupts();
    GSsndStream* result = 0;
    s32 index = 0;
    GSsndStream* entry = _sndStreaming;
    for (u32 count = _maxStreaming; count > 0; --count) {
        if (entry->inUse == 0) {
            _sndStreaming[index].inUse = 1;
            result = &_sndStreaming[index];
            break;
        }
        ++entry;
        ++index;
    }
    OSRestoreInterrupts(interrupts);
    return result;
}
static GSsndEmitter* _sndGetNewEmitter() {
    BOOL interrupts = OSDisableInterrupts();
    GSsndEmitter* result = 0;
    s32 index = 0;
    GSsndEmitter* entry = _sndEmitter;
    for (u32 count = _maxEmitter; count > 0; --count) {
        if (entry->inUse != 1) {
            _sndEmitter[index].inUse = 1;
            result = &_sndEmitter[index];
            break;
        }
        ++entry;
        ++index;
    }
    OSRestoreInterrupts(interrupts);
    return result;
}
static GSsndListener* _sndGetNewListener() {
    BOOL interrupts = OSDisableInterrupts();
    GSsndListener* result = 0;
    s32 index = 0;
    GSsndListener* entry = _sndListener;
    for (u32 count = _maxListener; count > 0; --count) {
        if (entry->inUse != 1) {
            _sndListener[index].inUse = 1;
            result = &_sndListener[index];
            break;
        }
        ++entry;
        ++index;
    }
    OSRestoreInterrupts(interrupts);
    return result;
}
static GSsndWork* _sndGetNewSndWork() {
    BOOL interrupts = OSDisableInterrupts();
    GSsndWork* result = 0;
    s32 index = 0;
    GSsndWork* entry = _sndWork;
    for (u32 count = _maxSndWork; count > 0; --count) {
        if (entry->inUse != 1) {
            _sndWork[index].inUse = 1;
            result = &_sndWork[index];
            break;
        }
        ++entry;
        ++index;
    }
    OSRestoreInterrupts(interrupts);
    return result;
}
static void _sndInitEmitter() {
    for (u32 i = 0; i < _maxEmitter; ++i) _sndEmitter[i].inUse = 0;
}
static void _sndInitListener() {
    for (u32 i = 0; i < _maxListener; ++i) _sndListener[i].inUse = 0;
}
static void _sndInitSndWork() {
    for (u32 i = 0; i < _maxSndWork; ++i) _sndWork[i].inUse = 0;
}
static void _sndInitStack() {
    for (u32 i = 0; i < _maxStack; ++i) _sndStack[i] = 0;
}
static void _sndInitParms(GSsndDescriptor* descriptor, GSsndWork* work) {
    BOOL interrupts = OSDisableInterrupts();
    descriptor->bits.opened = 1;
    descriptor->bits.paused = 0;
    descriptor->work = work;
    work->voice = ~0U;
    work->volumeDepth = 0;
    work->volume = 127;
    work->pan = 64;
    work->surround = 64;
    OSRestoreInterrupts(interrupts);
}
static void _sndDoFree(void* data) { GSmemFree(data); }
static void* _sndDoMalloc(u32 size) { return GSmemAllocAlign(size, 32); }
}
#pragma dont_inline reset

extern "C" {
void sndAddEmitter(void*, Vec*, Vec*, u32, u16, s32, s32, u32, f32, f32);
u8 sndAddListener(void*, Vec*, Vec*, Vec*, Vec*, u32, s32, f32*, f32, f32, f32);
#pragma dont_inline on
GSsndEmitter* GSsndCreateEmitter(u32 id, Vec* position) {
    Vec velocity;
    velocity.x = 0.0f; velocity.y = 0.0f; velocity.z = 0.0f;
    return GSsndCreateEmitterParam(id, position, &velocity, 127, 0, 10000.0f, 0.0f);
}
GSsndEmitter* GSsndCreateEmitterParam(u32 id, Vec* position, Vec* velocity, s8 volume, s8 pan, f32 distance, f32 attenuation) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    GSsndEmitter* emitter = _sndGetNewEmitter();
    if (!emitter) return 0;
    sndAddEmitter(emitter->emitterStorage, position, velocity, 0x9f, descriptor->effect, volume, pan, 0, distance, attenuation);
    emitter->position.x = position->x; emitter->position.y = position->y; emitter->position.z = position->z;
    emitter->velocity.x = velocity->x; emitter->velocity.y = velocity->y; emitter->velocity.z = velocity->z;
    emitter->volume = volume;
    emitter->pan = pan;
    emitter->distance = distance;
    emitter->attenuation = attenuation;
    emitter->identifier = id;
    if (sndCheckEmitter(emitter->emitterStorage) == 1) return emitter;
    _sndFreeEmitter(emitter);
    return 0;
}
GSsndListener* GSsndCreateListener(Vec* position) {
    Vec velocity, direction, up;
    velocity.x = 0.0f; velocity.y = 0.0f; velocity.z = 0.0f;
    direction.x = 0.0f; direction.y = 0.0f; direction.z = -1.0f;
    up.x = 0.0f; up.y = 1.0f; up.z = 0.0f;
    return GSsndCreateListenerParam(position, &velocity, &direction, &up, 127, 250.0f, 250.0f, 1000.0f);
}
GSsndListener* GSsndCreateListenerParam(Vec* position, Vec* velocity, Vec* direction, Vec* up, s8 volume, f32 distance, f32 attenuation, f32 scale) {
    static f32 expParam = 1.0f;
    if (!_initFlag) return 0;
    GSsndListener* listener = _sndGetNewListener();
    if (!listener) return 0;
    if (sndAddListener(listener->listenerStorage, position, velocity, direction, up, 1, volume, &expParam, distance, attenuation, scale) == 1) {
        listener->position.x = position->x; listener->position.y = position->y; listener->position.z = position->z;
        listener->velocity.x = velocity->x; listener->velocity.y = velocity->y; listener->velocity.z = velocity->z;
        listener->direction.x = direction->x; listener->direction.y = direction->y; listener->direction.z = direction->z;
        listener->up.x = up->x; listener->up.y = up->y; listener->up.z = up->z;
        listener->distance = distance;
        listener->attenuation = attenuation;
        listener->scale = scale;
        listener->volume = volume;
        return listener;
    }
    _sndFreeListener(listener);
    return 0;
}
#pragma dont_inline reset
}

extern "C" {
u8 sndSeqGetValid(u32);
void sndSeqContinue(u32);
void sndSeqPause(u32);
void sndStreamDeactivate(u32);
s32 GSfsysGetStatus(u32);
void GSfsysCancel(u32);
void _sndStreamCtrl(GSsndStream*, u8);
void GSsndUpdateSettingsReverbHI(u32);
void sndOutputMode(s32);
void sndMasterVolume(u8, u16, u8, u8);
void GSlogWrite(const char*, ...);
struct GSsndFile { u32 identifier, size, resource; };
extern GSsndFile* snd_file;
#pragma dont_inline on
static GSsndStream* _sndGetStream(u32);
static u8 _sndStreamGetValid(u32);
static s32 _sndClose(u32, u8);
static s32 _sndStopSTREAM(GSsndDescriptor*);
static s32 _sndStopSE(GSsndDescriptor*);
static s32 _sndStopBGM(GSsndDescriptor*, u32);
static void _sndCheckSndWorkALL();
s32 GSsndGetStatus(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if ((u32)((flags >> 3) & 1) != 1U) return 0;
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if ((u32)((flags >> 6) & 1) == 1U) {
        if ((u32)((flags >> 2) & 1) == 1U) return 3;
        if (work->voice != ~0U && _sndStreamGetValid(work->voice) == 1) return 2;
        _sndClose(id, 1);
        return 0;
    }
    if ((u32)((flags >> 5) & 1) == 1U) {
        if (work->voice != ~0U && (u32)sndFXCheck(work->voice) != ~0U) return 2;
        _sndClose(id, 1);
        return 0;
    }
    if ((u32)((flags >> 2) & 1) == 1U) return 3;
    if (work->voice != ~0U && sndSeqGetValid(work->voice) == 1) return 2;
    _sndClose(id, 1);
    return 0;
}
s32 GSsndContinue(u32 id, u16 time) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if ((u32)((flags >> 5) & 1) == 1U) return 0;
    if ((u32)((flags >> 3) & 1) != 1U) return 0;
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (work->voice == ~0U) return 0;
    if ((u32)((flags >> 2) & 1) != 1U) return 0;
    GSsndUpdateSettingsReverbHI(descriptor->parameters & 15);
    if (id == 8) return 1;
    if (descriptor->bits.streaming == 1U) _sndStreamVolume(work->volume, time, work->voice, 0);
    else { sndSeqContinue(work->voice); sndSeqVolume(work->volume, time, work->voice, 0); }
    descriptor->bits.paused = 0;
    return 1;
}
s32 GSsndPause(u32 id, u16 time) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if ((u32)((flags >> 5) & 1) == 1U) return 0;
    if ((u32)((flags >> 3) & 1) != 1U) return 0;
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (work->voice == ~0U) return 0;
    if ((u32)((flags >> 2) & 1) == 1U) return 0;
    if (id == 8) return 1;
    if ((u32)((flags >> 6) & 1) == 1U) _sndStreamVolume(0, time, work->voice, 2);
    else { sndSeqVolume(0, time, work->voice, 0); sndSeqPause(work->voice); }
    descriptor->bits.paused = 1;
    return 1;
}
s32 GSsndStopNow(u32 id) { return GSsndStop(id, 0, 0); }
s32 GSsndStop(u32 id, u32 time, u32 reserved) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if ((u32)((flags >> 6) & 1) == 1U) return _sndStopSTREAM(descriptor);
    if ((u32)((flags >> 5) & 1) == 1U) return _sndStopSE(descriptor);
    return _sndStopBGM(descriptor, time);
}
s32 GSsndOpen(u32 id, u32 context, u32 options) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    if (descriptor->bits.opened == 1U) return 0;
    GSsndWork* work = _sndGetNewSndWork();
    if (!work) { _sndCheckSndWorkALL(); work = _sndGetNewSndWork(); if (!work) return 0; }
    _sndInitParms(descriptor, work);
    work->context = context;
    work->options = options;
    return 1;
}
s32 GSsndClose(u32 id) { return _sndClose(id, 1); }
s32 GSsndGetOutputMode() {
    switch (OSGetSoundMode()) { case 1: return 1; case 0: return 0; default: return 0; }
}
void GSsndSetOutputMode(s32 mode) {
    if (_initFlag) {
        sndOutputMode(mode);
        switch (mode) { case 0: OSSetSoundMode(0); break; case 1: case 2: OSSetSoundMode(1); break; }
    }
}
void GSsndSetMasterVolume(u8 volume, u16 time, u8 music, u8 effects) { if (_initFlag) sndMasterVolume(volume, time, music, effects); }
static GSsndStream* _sndGetStream(u32 id) {
    s32 index = 0;
    GSsndStream* stream = _sndStreaming;
    for (u32 count = _maxStreaming; count > 0; --count) {
        if (stream->inUse && stream->identifier == id) return &_sndStreaming[index];
        ++stream;
        ++index;
    }
    return 0;
}
static u8 _sndStreamGetValid(u32 id) { if (_sndGetStream(id) || GSfsysGetStatus(id) == 1) return 1; return 0; }
static s32 _sndStreamGetSndID(u32 id) {
    GSsndStream* stream = _sndGetStream(id);
    if (!stream) return -1;
    if (stream->first) stream = stream->first;
    return stream->soundID;
}
static void _sndStreamVolume(u8 volume, u32 time, u32 id, u8 action) {
    BOOL interrupts = OSDisableInterrupts();
    GSsndStream* stream = _sndGetStream(id);
    if (!stream) { OSRestoreInterrupts(interrupts); return; }
    GSsndStream *first, *second;
    if (stream->first) { first = stream->first; second = stream; }
    else { first = stream; second = stream->second; }
    if (first->paused == 1 && action == 0) { _sndStreamCtrl(first, 0); _sndStreamCtrl(second, 0); }
    first->previousVolume = first->currentVolume;
    first->targetVolume = volume;
    first->fadeStep = 0;
    first->fadeTime = time;
    first->fadeAction = action;
    // Both channels use the first channel's current volume in the original.
    second->previousVolume = first->currentVolume;
    second->targetVolume = volume;
    second->fadeStep = 0;
    second->fadeTime = time;
    second->fadeAction = action;
    OSRestoreInterrupts(interrupts);
}
static s32 _sndStopSTREAM(GSsndDescriptor* descriptor) {
    GSsndWork* work = descriptor->work;
    if (!work || work->voice == ~0U) return 0;
    GSfsysCancel(work->voice);
    work->voice = ~0U;
    GSsndStream* stream = _sndGetStream(snd_file[descriptor->file].identifier);
    if (!stream) return 0;
    GSsndStream *first, *second;
    if (stream->first) { first = stream->first; second = stream; }
    else { first = stream; second = stream->second; }
    sndStreamDeactivate(first->voice);
    sndStreamDeactivate(second->voice);
    _sndFreeStream(first);
    _sndFreeStream(second);
    return 1;
}
static s32 _sndStopSE(GSsndDescriptor* descriptor) {
    GSsndWork* work = descriptor->work;
    if (!work || work->voice == ~0U) return 0;
    s32 result;
    if ((u32)sndFXCheck(work->voice) != ~0U) result = sndFXKeyOff(work->voice);
    else result = 0;
    work->voice = ~0U;
    return result;
}
static s32 _sndStopBGM(GSsndDescriptor* descriptor, u32 time) {
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (descriptor->bits.opened != 1U) return 0;
    if (work->voice == ~0U) return 0;
    sndSeqVolume(0, time, work->voice, 1);
    work->voice = ~0U;
    return 1;
}
static void _sndCheckSndWorkALL() {
    GSlogWrite("_sndCheckSndWorkALL:Start\n");
    for (u32 i = 0; i < _maxSoundID; ++i) GSsndGetStatus(i);
    GSlogWrite("_sndCheckSndWorkALL:End\n");
}
static s32 _sndClose(u32 id, u8 stop) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    if (descriptor->bits.opened != 1U) return 0;
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (stop == 1) GSsndStop(id, 0, 0);
    _sndInitParms(descriptor, work);
    _sndFreeSndWork(work);
    descriptor->work = 0;
    descriptor->bits.opened = 0;
    return 1;
}
#pragma dont_inline reset
}

#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
struct GSsndSequenceParameters {
    u32 flags, reserved04, reserved08;
    u16 speed, reserved0E;
    u8 reserved10, padding11, reserved12, padding13;
    u32 reserved14;
    u8 reserved18, padding19[3];
    u32 reserved1C;
};
extern "C" {
u32 sndFXStartEx(u16, u8, u8, u32);
u32 sndSeqPlayEx(u32, u16, void*, GSsndSequenceParameters*, u32);
extern u32* snd_file_number;
static s32 _sndPlaySTREAM(GSsndDescriptor*, u32, u16, u8, u32);
#pragma dont_inline on
static s32 _sndPlaySE(GSsndDescriptor*, u32, u8);
static s32 _sndPlayBGM(GSsndDescriptor*, u32, u16, u8, u32);
static s32 _sndPlay(u32, u16, u32, u32);
s32 GSsndPlayNow(u32 id) { return _sndPlay(id, 0, 127, 0); }
s32 GSsndPlayVolume(u32 id, u16 time, u32 volume, u32 flags) { return _sndPlay(id, time, volume, flags); }
s32 GSsndPlay(u32 id, u16 time, u32 flags) { return _sndPlay(id, time, 127, flags); }
u32 GSsndPopVolumeALL(u16 time, u32 music, u32 effects) {
    u32 id;
    for (id = 0; id < _maxSoundID; ++id) {
        u8 flags = snd_data[id].flags;
        if ((u32)((flags >> 3) & 1) == 1U) {
            if (((u32)((flags >> 5) & 1) == 1U && effects) || ((u32)((flags >> 5) & 1) != 1U && music)) GSsndPopVolumeID(id, time);
        }
    }
    return id;
}
u32 GSsndPushVolumeALL(u16 time, u8 volume, u32 music, u32 effects) {
    u32 id;
    for (id = 0; id < _maxSoundID; ++id) {
        u8 flags = snd_data[id].flags;
        if ((u32)((flags >> 3) & 1) == 1U) {
            if (((u32)((flags >> 5) & 1) == 1U && effects) || ((u32)((flags >> 5) & 1) != 1U && music)) GSsndPushVolumeID(id, time, volume);
        }
    }
    return id;
}
static s32 _sndPlay(u32 id, u16 time, u32 volume, u32 flags) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 properVolume = _sndGetProperVolume(descriptor, volume);
    u8 soundFlags = descriptor->flags;
    if ((u32)((soundFlags >> 6) & 1) == 1U) return _sndPlaySTREAM(descriptor, id, time, properVolume, flags);
    if ((u32)((soundFlags >> 5) & 1) == 1U) return _sndPlaySE(descriptor, id, properVolume);
    return _sndPlayBGM(descriptor, id, time, properVolume, flags);
}
static s32 _sndPlaySE(GSsndDescriptor* descriptor, u32 id, u8 volume) {
    if (descriptor->bits.opened != 1U) GSsndOpen(id, 0, 0);
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    work->volume = volume;
    work->voice = sndFXStartEx(descriptor->effect, volume, work->pan, 0);
    sndFXCtrl(work->voice, 7, volume);
    return 1;
}
static s32 _sndPlayBGM(GSsndDescriptor* descriptor, u32 id, u16 time, u8 volume, u32 flags) {
    GSsndSequenceParameters parameters;
    void* sequence;
    if (descriptor->bits.opened != 1U) {
        u16 file = descriptor->file;
        if (file >= *snd_file_number) return 0;
        GSsndOpen(id, snd_file[file].identifier, snd_file[file].resource);
    }
    GSsndWork* work = descriptor->work;
    if (!work) return 0;
    if (descriptor->bits.opened != 1U) return 0;
    if (work->voice != ~0U) return 0;
    sequence = GSresGetResource(work->context, work->options);
    if (!sequence) return 0;
    GSsndUpdateSettingsReverbHI(descriptor->parameters & 15);
    parameters.flags = 4;
    parameters.reserved04 = 0;
    parameters.reserved08 = 0;
    parameters.speed = 256;
    parameters.reserved0E = 0;
    parameters.reserved10 = 0;
    parameters.reserved12 = 0;
    parameters.reserved14 = 0;
    parameters.reserved18 = 0;
    parameters.reserved1C = 0;
    work->volume = volume;
    work->voice = sndSeqPlayEx((descriptor->parameters >> 4) & 15, descriptor->effect, sequence, &parameters, 0);
    sndSeqVolume(volume, time, work->voice, 0);
    return 1;
}
static u32 _sndDesc2Id(u32 voice) {
    GSsndDescriptor* descriptor = snd_data;
    for (u32 id = 0; id < _maxSoundID; ++id, ++descriptor) {
        GSsndWork* work = descriptor->work;
        if (work && !descriptor->bits.streaming && work->voice == voice) return id;
    }
    return 0;
}
#pragma dont_inline reset
}

struct GSsndReverbParameters { f32 coloration, mix, time, damping, preDelay, crossTalk; };
struct GSsndReverbHI { u32 state[113]; u8 disabled, reserved1C5[3]; GSsndReverbParameters parameters; };
typedef char GSsndReverbSizeCheck[sizeof(GSsndReverbHI) == 0x1e0 ? 1 : -1];
static GSsndReverbHI _revH;
extern "C" {
extern GSsndReverbParameters* snd_rev_data;
extern u32* snd_rev_data_number;
void sndAuxCallbackUpdateSettingsReverbHI(GSsndReverbHI*);
void sndVolume(u8, u32, u8);
u8 sndIsInstalled();
void sndQuit();
void GSgappTerminate(s32);
#pragma dont_inline on
static void _sndSetReverbParm(u32);
static s32 _sndSetVolumeWork(u32, u8);
void GSsndUpdateSettingsReverbHI(u32 id) {
    if (_initFlag && id < *snd_rev_data_number && id != 0 && _revH_now_parm_id != id) {
        _sndSetReverbParm(id);
        sndAuxCallbackUpdateSettingsReverbHI(&_revH);
    }
}
static void _sndSetReverbParm(u32 id) {
    _revH.disabled = 0;
    GSsndReverbParameters* parameters = &snd_rev_data[id];
    _revH.parameters.coloration = parameters->coloration;
    _revH.parameters.mix = parameters->mix;
    _revH.parameters.time = parameters->time;
    _revH.parameters.damping = parameters->damping;
    _revH.parameters.preDelay = parameters->preDelay;
    _revH.parameters.crossTalk = parameters->crossTalk;
    _revH_now_parm_id = id;
}
static s32 _sndSetVolumeWork(u32 id, u8 volume) {
    GSsndDescriptor* descriptor = &snd_data[id];
    u8 flags = descriptor->flags;
    if ((u32)((flags >> 3) & 1) != 1U) {
        if ((u32)((flags >> 5) & 1) == 1U) GSsndOpen(id, 0, 0);
        else return 0;
    }
    GSsndWork* work = descriptor->work;
    if (work) work->volume = volume & 127;
    return 1;
}
void GSsndSetVolume(u8 volume, u16 time, u32 music, u32 effects) {
    if (!_initFlag) return;
    s32 group;
    if (music == 1 && effects == 1) group = 255;
    else if (music == 1 && effects != 1) group = 253;
    else if (music != 1 && effects == 1) group = 254;
    else return;
    for (u32 id = 0; id < _maxSoundID; ++id) {
        GSsndDescriptor* descriptor = &snd_data[id];
        u8 flags = descriptor->flags;
        if ((u32)((flags >> 3) & 1) == 1U) {
            switch (group) {
            case 253: if ((u32)((flags >> 5) & 1) == 1U) continue; break;
            case 254: if (!((flags >> 5) & 1)) continue; break;
            }
            _sndSetVolumeWork(id, volume);
            if (descriptor->bits.streaming == 1U) _sndSetVolume(descriptor, time, volume);
        }
    }
    sndVolume(volume, time, group);
}
void GSsndQuit() {
    if (_initFlag && sndIsInstalled() == 1) {
        GSsndSetVolume(0, 0, 1, 1);
        sndQuit();
        GSgappTerminate(_sndDaemonHDL);
        _sndDaemonHDL = 0;
    }
}
static void _sndReceiveMessage(u32 voice) {
    u32 id = _sndDesc2Id(voice);
    if (id != 0) _sndClose(id, 0);
}
#pragma dont_inline reset
}

extern "C" {
void GSfsysWait(u32);
u32 GSfsysGetInvalidID();
u8 GSfsysReadStreamingEX(u32, u32, u32);
#pragma dont_inline on
void* GSsndStreamPreFunc(u32 id) {
    if (!_initFlag) return 0;
    GSsndStream* stream = _sndGetStream(id);
    if (stream) return &stream->header;
    return 0;
}
s32 GSsndIsPlayingStream(u32 id) {
    if (!_initFlag) return 0;
    if (id == ~0U || id >= *snd_data_number) return 0;
    GSsndDescriptor* descriptor = &snd_data[id];
    if (descriptor->bits.streaming == 1U) {
        GSsndWork* work = descriptor->work;
        if (!work) return 0;
        if (work->voice == ~0U) return 0;
        if (!_sndStreamGetValid(work->voice)) return 0;
        GSsndStream* stream = _sndGetStream(work->voice);
        if (stream) return stream->inUse == 9;
        return 0;
    }
    return id;
}
static s32 _sndPlaySTREAM(GSsndDescriptor* descriptor, u32 id, u16 time, u8 volume, u32 flags) {
    GSsndStream *first, *second;
    GSsndWork* work;
    u32 identifier, secondaryID, resource;
    if (descriptor->bits.opened != 1U) GSsndOpen(id, 0, 0);
    work = descriptor->work;
    if (!work) return 0;
    if (!descriptor->bits.effect && work->voice != ~0U) return 0;
    identifier = snd_file[descriptor->file].identifier;
    secondaryID = snd_file[descriptor->file].size;
    resource = snd_file[descriptor->file].resource;
    if (_sndStreamGetValid(identifier) == 1) {
        GSfsysWait(identifier);
        GSsndClose(_sndStreamGetSndID(identifier));
        GSfsysWait(identifier);
        GSsndOpen(id, 0, 0);
        work = descriptor->work;
        if (!work) return 0;
    } else {
        GSfsysCancel(identifier);
        GSfsysWait(identifier);
    }
    first = _sndGetNewStream();
    if (!first) { _sndClose(id, 0); return 0; }
    first->first = 0; first->second = 0; first->inUse = 2;
    first->identifier = identifier; first->resource = resource;
    first->currentVolume = 0; first->previousVolume = 0; first->targetVolume = volume;
    first->fadeStep = 0; first->channel = 0; first->initialized = 0;
    first->readOffset = 0; first->writeOffset = 0; first->pendingBytes = 0;
    first->active = 0; first->paused = 0; first->stopped = 0;
    first->soundID = id; first->fadeTime = time; first->fadeAction = 0;
    second = _sndGetNewStream();
    if (!second) { _sndClose(id, 0); _sndFreeStream(first); return 0; }
    second->first = 0; second->second = 0; second->inUse = 2;
    second->identifier = 0; second->resource = 0;
    second->currentVolume = 0; second->previousVolume = 0; second->targetVolume = volume;
    second->fadeStep = 0; second->channel = 1; second->initialized = 0;
    second->readOffset = 0; second->writeOffset = 0; second->pendingBytes = 0;
    second->active = 0; second->paused = 0; second->stopped = 0;
    second->soundID = id; second->fadeTime = time; second->fadeAction = 0;
    first->second = second; second->first = first;
    if (!secondaryID) secondaryID = GSfsysGetInvalidID();
    if (!GSfsysReadStreamingEX(identifier, secondaryID, resource)) {
        _sndClose(id, 0); _sndFreeStream(first); _sndFreeStream(second); return 0;
    }
    work->volume = volume; work->voice = identifier;
    return 1;
}
#pragma dont_inline reset
}

struct GSsndHooks { void* (*allocate)(u32); void (*release)(void*); };
extern "C" {
void sndSetHooks(GSsndHooks*);
s32 sndInit(u32, u32, u32, u32, u32, u32);
void sndAuxCallbackPrepareReverbHI(GSsndReverbHI*);
void sndAuxCallbackReverbHI(u8, void*, void*);
void sndSetAuxProcessingCallbacks(u8, void (*)(u8, void*, void*), void*, u8, u8, void (*)(u8, void*, void*), void*, u8, u8);
void sndSetReceiveMessageCallback(void (*)(u32));
s32 GSgappCreate(u32, u32, u32, void (*)());
void GSgappSetName(s32, const char*);
u32 _sndStreamCallback(u32, u32, u32, u32, GSsndStream*);
u32 sndStreamAllocEx(u8, void*, u32, u32, u8, u8, u8, u8, u8, u8, u32, u32 (*)(u32, u32, u32, u32, GSsndStream*), void*, u32);
static void _sndDaemon();
#pragma dont_inline on
static u8 _sndStreamInit(u32 count) {
    _maxStreaming = count;
    _sndStreaming = (GSsndStream*)_sndDoMalloc(count * sizeof(GSsndStream));
    if (!_sndStreaming) return 0;
    GSsndStream* stream;
    for (u32 index = 0; index < _maxStreaming; ++index) {
        stream = &_sndStreaming[index];
        stream->first = 0; stream->second = 0; stream->inUse = 0;
        stream->currentVolume = 0; stream->previousVolume = 0;
        stream->targetVolume = 0; stream->channel = 0;
        stream->bufferSize = 0x10000;
        stream->sampleCount = (stream->bufferSize >> 3) * 14;
        stream->buffer = _sndDoMalloc(0x18000);
        stream->initialized = 0; stream->readOffset = 0; stream->writeOffset = 0;
        stream->pendingBytes = 0; stream->identifier = 0; stream->soundID = 0;
        stream->fadeTime = 0; stream->fadeAction = 0; stream->active = 0;
        stream->paused = 0; stream->stopped = 0;
        stream->voice = sndStreamAllocEx(255, stream->buffer, stream->sampleCount, 32000,
            stream->currentVolume, 64, 0, 0, 0, 0, 0x30001, _sndStreamCallback, stream, 0);
    }
    return 1;
}
static const char _sndDaemonName[] = "GSmovieDaemon";
s32 GSsndInit(u32 effectCount, u32 stackCount, u32 sequenceCount, u32 listenerCount, u32 emitterCount) {
    GSsndHooks hooks = { _sndDoMalloc, _sndDoFree };
    if (_initFlag == 1) return 0;
    u32 workCount = effectCount + sequenceCount;
    if (workCount >= 64) return 0;
    _maxSoundID = *snd_data_number; _revH_now_parm_id = ~0U; _maxSndWork = workCount;
    _sndWork = (GSsndWork*)_sndDoMalloc(workCount * sizeof(GSsndWork));
    if (!_sndWork) return 0;
    _sndInitSndWork();
    _maxStack = stackCount; _sndStack = (u8*)_sndDoMalloc(stackCount);
    if (!_sndStack) return 0;
    _sndInitStack();
    _maxListener = listenerCount; _sndListener = (GSsndListener*)_sndDoMalloc(listenerCount * sizeof(GSsndListener));
    if (!_sndListener) return 0;
    _sndInitListener();
    _maxEmitter = emitterCount; _sndEmitter = (GSsndEmitter*)_sndDoMalloc(emitterCount * sizeof(GSsndEmitter));
    if (!_sndEmitter) return 0;
    _sndInitEmitter();
    sndSetHooks(&hooks);
    if (sndInit(64, 48, 16, 1, 2, 0x5fc000)) return 0;
    _sndSetReverbParm(0);
    sndAuxCallbackPrepareReverbHI(&_revH);
    sndSetAuxProcessingCallbacks(0, sndAuxCallbackReverbHI, &_revH, 255, 0, 0, 0, 255, 0);
    sndSetReceiveMessageCallback(_sndReceiveMessage);
    _sndDaemonHDL = GSgappCreate(1, 30, 0, _sndDaemon);
    GSgappSetName(_sndDaemonHDL, _sndDaemonName);
    if (!_sndStreamInit(4)) return 0;
    _initFlag = 1;
    GSsndSetVolume(127, 0, 1, 0); GSsndSetVolume(100, 0, 0, 1);
    GSsndSetOutputMode(GSsndGetOutputMode());
    return 1;
}
#pragma dont_inline reset
}

extern "C" {
s32 GSfsysGetDriveStatus();
void _sndStreamPrepareGetData(GSsndStream*);
s32 _sndStreamGetData(GSsndStream*, void (*)(u8, u8, GSsndStream*));
void _sndStreamGetDataCallback_START(u8, u8, GSsndStream*);
void _sndStreamGetDataCallback_ACTIVATE(u8, u8, GSsndStream*);
void _sndStreamGetDataCallback_EXEC_UPDATE(u8, u8, GSsndStream*);
u32 _sndStreamNibble_HeaderON2OFF(u32);
void GSfsysStreamSetLoopFlag(u32, u32, u8);
void GSfsysStreamSetLoopPoint(u32, u32, u32, u32);
#pragma dont_inline on
// The original stream daemon has an empty body.
static void _sndStreamDaemon(GSsndStream*) {}
static void _sndDaemon() {
    BOOL interrupts;
    GSsndStream* stream;
    s32 stopped;
    u32 index;
    GSsndStream *first, *second;
    switch (GSfsysGetDriveStatus()) {
    case -1: case 3: case 4: case 5: case 6: case 8: case 11: stopped = 1; break;
    default: stopped = 0; break;
    }
    for (index = 0; index < _maxStreaming; ++index) {
        stream = &_sndStreaming[index];
        if (stream->first) { first = stream->first; second = stream; }
        else { first = stream; second = stream->second; }
        switch ((s32)stream->inUse) {
        case 0: case 1: case 2: case 10: case 11: case 13: break;
        default: _sndStreamPrepareGetData(stream); break;
        }
        stream->stopped = stopped;
        interrupts = OSDisableInterrupts();
        switch (stream->inUse) {
        case 3: _sndStreamGetData(stream, _sndStreamGetDataCallback_START); break;
        case 6: _sndStreamGetData(stream, _sndStreamGetDataCallback_ACTIVATE); break;
        case 9: _sndStreamDaemon(stream); break;
        case 10:
            stream->inUse = 11;
            if (!stream->first) GSsndClose(stream->soundID);
            break;
        case 13:
            sndStreamDeactivate(stream->voice);
            if (first->header.loop == 0) stream->inUse = 10;
            else stream->inUse = 12;
            break;
        case 12:
            if (!first->initialized && !second->initialized) stream->inUse = 3;
            else if (stream->initialized) _sndStreamGetData(stream, _sndStreamGetDataCallback_EXEC_UPDATE);
            break;
        }
        OSRestoreInterrupts(interrupts);
    }
}
void GSsndStreamPostFunc(u32 id, u32 resource) {
    if (_initFlag) {
        GSsndStream* stream = _sndGetStream(id);
        if (stream) {
            stream->inUse = 3;
            if (stream->second) stream->second->inUse = 3;
            GSfsysStreamSetLoopFlag(id, resource, stream->header.loop);
            stream->buffers[0].ready = 0; stream->buffers[0].consumed = 0;
            stream->buffers[0].readOffset = 0; stream->buffers[0].writeOffset = 0;
            stream->buffers[0].length = 0; stream->buffers[0].state = 1;
            stream->buffers[1].ready = 0; stream->buffers[1].consumed = 0;
            stream->buffers[1].readOffset = 0; stream->buffers[1].writeOffset = 0;
            stream->buffers[1].length = 0; stream->buffers[1].state = 1;
            stream->header.reserved31 = 0; stream->header.reserved32 = 0; stream->header.reserved33 = 0;
            stream->header.loopStartSamples = ((stream->header.loopStart - 2) >> 16) * 0xe000;
            stream->header.loopEndSamples = ((stream->header.loopEnd + 0xffff) >> 16) * 0xe000;
            stream->header.sampleCount = _sndStreamNibble_HeaderON2OFF(stream->header.nibbleCount);
            u32 start, end;
            if (stream->header.loop == 1) {
                start = ((stream->header.loopStart - 2) >> 1) & 0x7fff8000;
                end = ((stream->header.loopEnd + 0xffff) >> 1) & 0x7fff8000;
            } else {
                start = 0;
                end = ((stream->header.nibbleCount + 0xffff) >> 1) & 0x7fff8000;
            }
            GSfsysStreamSetLoopPoint(id, resource, start * 2, end * 2);
        }
    }
}
#pragma dont_inline reset
}

struct GSsndWave { u8 reserved00, opened; u16 group; u32 reserved04[5]; };
extern "C" {
extern GSsndWave* snd_wave_data;
extern u32* snd_wave_data_number;
u32 ARGetDMAStatus();
u32 ARQGetChunkSize();
void* GSdvdOpen(u32);
void GSdvdClose(void*);
s32 GSdvdRead(void*, void*, u32, u32);
void sndSetSampleDataUploadCallback(void* (*)(u32, u32), u32);
u8 sndPushGroup(void*, u16, void*, void*, void*);
#pragma dont_inline on
static void* _sndSetSampleDataUploadCallbackFunction(u32 offset, u32 length) {
    while (ARGetDMAStatus()) {}
    for (;;) {
        s32 result = GSdvdRead(_SampleDataFileInfo, _SampleDataUploadBuffer, length, offset + _SampleDataFileOffset);
        switch (result) { case -3: case -1: continue; default: break; }
        break;
    }
    return _SampleDataUploadBuffer;
}
static s32 _sndOpenWave(u32 id, u32 fromDVD, u32 file, u32 offset, u32 resourceID, u32 samplesID, u32 projectID, u32 poolID) {
    GSsndWave* wave;
    void *project, *sampleAddress, *pool, *samples;
    if (!_initFlag) return 0;
    if (id >= *snd_wave_data_number) return 0;
    wave = &snd_wave_data[id];
    if (wave->opened == 1) return 0;
    project = GSresGetResource(resourceID, projectID);
    if (!project) return 0;
    pool = GSresGetResource(resourceID, poolID);
    if (!pool) return 0;
    samples = GSresGetResource(resourceID, samplesID);
    if (!samples) return 0;
    if (fromDVD == 1) {
        sampleAddress = 0;
        sndSetSampleDataUploadCallback(_sndSetSampleDataUploadCallbackFunction, ARQGetChunkSize());
        _SampleDataFileInfo = GSdvdOpen(file);
        if (!_SampleDataFileInfo) return 0;
        _SampleDataFileOffset = offset;
        _SampleDataUploadBuffer = _sndDoMalloc(ARQGetChunkSize());
        if (!_SampleDataUploadBuffer) { GSdvdClose(_SampleDataFileInfo); return 0; }
    } else {
        sampleAddress = (void*)file;
        sndSetSampleDataUploadCallback(0, 0);
    }
    if (!sndPushGroup(project, wave->group, sampleAddress, pool, samples)) {
        if (fromDVD == 1) GSdvdClose(_SampleDataFileInfo);
        return 0;
    }
    if (fromDVD == 1) { _sndDoFree(_SampleDataUploadBuffer); GSdvdClose(_SampleDataFileInfo); }
    wave->opened = 1;
    return 1;
}
s32 GSsndOpenWaveDVD(u32 id, u32 file, u32 offset, u32 resourceID, u32 samplesID, u32 projectID, u32 poolID) {
    return _sndOpenWave(id, 1, file, offset, resourceID, samplesID, projectID, poolID);
}
#pragma dont_inline reset
}
