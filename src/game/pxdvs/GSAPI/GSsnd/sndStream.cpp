#include <game/pxdvs/GSAPI/GSsnd/GSsnd.hpp>
#include <dolphin/os.h>
#include <libc/string.h>

extern "C" {

u32 GSfsysStreamGetCacheSize();
u8 GSfsysStreamGetData(u32, u32, void*, u32, u32, void (*)(u8, u8, GSsndStream*), u8, GSsndStream*);
void sndStreamARAMUpdate(u32, u32, u32, u32, u32);
void sndStreamActivate(u32);
void sndStreamFrq(u32, u32);
void sndStreamADPCMParameter(u32, void*);
void sndStreamMixParameterEx(u32, u8, u32, u8, u8, u8);
#pragma dont_inline on
static void _sndStreamPrepareGetData_Exec(GSsndStream*, GSsndStream*, u32);
static void _sndStreamPrepareGetData_GetOldData(GSsndStream*, GSsndStream*, u32);
static void _sndStreamPrepareGetData_GetNewData(GSsndStream*, GSsndStream*, u32);
static void _sndStreamPrepareGetDataCallback(u8, u8, GSsndStream*);
static void _sndStreamPrepareGetDataCallback_Exec(GSsndStream*, GSsndStream*, GSsndStreamBufferState*, u32, u32);
static void _sndStreamARAMUpdate(GSsndStream*, GSsndStreamBufferState*);
u32 _sndStreamNibble_HeaderOFF2ON(u32 samples) { f64 value = samples; value *= 8.0 / 7.0; return (u32)value; }
u32 _sndStreamNibble_HeaderON2OFF(u32 nibbles) { f64 value = nibbles; value *= 0.875; return (u32)value; }
static u32 _sndStreamNibble_GetHeaderPos(u16 nibbles) { f64 value = nibbles; value *= 0.5; return (u32)value & ~7U; }
void _sndStreamPrepareGetData(GSsndStream* stream) {
    BOOL interrupts = OSDisableInterrupts();
    GSsndStream* first;
    if (stream->first) first = stream->first; else first = stream;
    if (!(&first->buffers[stream->channel].ready)[stream->initialized])
        _sndStreamPrepareGetData_Exec(stream, first, stream->initialized);
    OSRestoreInterrupts(interrupts);
}
static void _sndStreamPrepareGetData_Exec(GSsndStream* stream, GSsndStream* first, u32 half) {
    switch (first->buffers[stream->channel].state) {
    case 1: _sndStreamPrepareGetData_GetNewData(stream, first, half); return;
    case 3: _sndStreamPrepareGetData_GetOldData(stream, first, half); return;
    case 2: return;
    }
}
static void _sndStreamPrepareGetData_GetOldData(GSsndStream* stream, GSsndStream* first, u32 half) {
    GSsndStreamBufferState* state = &first->buffers[stream->channel];
    state->state = 4;
    _sndStreamPrepareGetDataCallback_Exec(stream, first, state, state->length, half);
}
static void _sndStreamPrepareGetData_GetNewData(GSsndStream* stream, GSsndStream* first, u32 half) {
    GSsndStreamBufferState* state = &first->buffers[stream->channel];
    u32 oldState = state->state;
    state->state = 2;
    void* destination = (u8*)stream->buffer + 0x10000;
    u32 offset;
    if (stream->first) offset = first->pendingBytes + (stream->bufferSize >> 1);
    else offset = first->pendingBytes;
    if (!first->header.loop && stream->readOffset >= first->header.reserved[3]) {
        memset(destination, 0, 0x8000);
        _sndStreamPrepareGetDataCallback(0, half, stream);
        return;
    }
    if (!GSfsysStreamGetData(first->identifier, first->resource, destination, 0x8000, offset,
        _sndStreamPrepareGetDataCallback, half, stream)) state->state = oldState;
}
static void _sndStreamPrepareGetDataCallback_Exec(GSsndStream* stream, GSsndStream* first, GSsndStreamBufferState* state, u32 offset, u32 half) {
    u8 bufferHalf = half;
    GSsndStreamBufferState* selected = (GSsndStreamBufferState*)((u8*)state + bufferHalf * 4);
    u32 length = 0x8000 - offset;
    u8* buffer = (u8*)stream->buffer;
    u32 position = selected->readOffset;
    void* destination;
    if (half) destination = buffer + ((stream->bufferSize >> 1) + position);
    else destination = buffer + position;
    void* source = buffer + 0x10000 + offset;
    if (position + length > 0x8000) {
        length = 0x8000 - position;
        state->length = offset + length; state->state = 3;
    } else { state->length = 0; state->state = 1; }
    memcpy(destination, source, length);
    selected->readOffset += length;
    if (selected->readOffset >= 0x8000) {
        selected->readOffset = 0; (&state->ready)[half] = 1;
    } else (&state->ready)[half] = 0;
}
static void _sndStreamARAMUpdate(GSsndStream* stream, GSsndStreamBufferState* state) {
    u32 offset;
    if (stream->initialized) offset = stream->sampleCount >> 1; else offset = 0;
    sndStreamARAMUpdate(stream->voice, offset, stream->sampleCount >> 1, 0, 0);
    (&state->ready)[stream->initialized] = 0;
    stream->initialized ^= 1;
}
void _sndStreamCtrl(GSsndStream* stream, u8 action) {
    switch (action) {
    case 1: stream->inUse = 10; return;
    case 2: stream->paused = 1; return;
    case 3: stream->paused = 1; return;
    case 0: default: stream->paused = 0; return;
    }
}
static void _sndStreamFadePostProcess(GSsndStream* stream) { _sndStreamCtrl(stream, stream->fadeAction); }
s32 _sndStreamGetData(GSsndStream* stream, void (*callback)(u8, u8, GSsndStream*)) {
    BOOL interrupts = OSDisableInterrupts();
    GSsndStream* first;
    if (stream->first) first = stream->first; else first = stream;
    if (!(&first->buffers[stream->channel].ready)[stream->initialized]) {
        OSRestoreInterrupts(interrupts); return 0;
    }
    void* buffer;
    if (stream->initialized) buffer = (u8*)stream->buffer + (stream->bufferSize >> 1);
    else buffer = stream->buffer;
    DCFlushRange(buffer, stream->bufferSize >> 1);
    if (callback) callback(0, 0, stream);
    OSRestoreInterrupts(interrupts); return 1;
}
void _sndStreamGetDataCallback_EXEC_UPDATE(u8, u8, GSsndStream* stream) {
    GSsndStream* first;
    if (stream->first) first = stream->first; else first = stream;
    _sndStreamARAMUpdate(stream, &first->buffers[stream->channel]);
}
void _sndStreamGetDataCallback_START(u8, u8, GSsndStream* stream) {
    GSsndStream *first, *second;
    switch ((s32)stream->inUse) {
    case 3: case 4:
        if (stream->first) { first = stream->first; second = stream; }
        else { first = stream; second = stream->second; }
        stream->inUse = 5;
        if (first->inUse == 5 && second->inUse == 5) {
            _sndStreamARAMUpdate(first, &first->buffers[first->channel]); first->inUse = 6;
            _sndStreamARAMUpdate(second, &first->buffers[second->channel]); second->inUse = 6;
        }
        break;
    }
}
void _sndStreamGetDataCallback_ACTIVATE(u8, u8, GSsndStream* stream) {
    GSsndStream *second;
    GSsndStream* activeStream = stream;
    GSsndStream* first;
    switch ((s32)activeStream->inUse) {
    case 6: case 7:
        if (activeStream->first) { first = activeStream->first; second = activeStream; }
        else { first = activeStream; second = activeStream->second; }
        sndStreamMixParameterEx(activeStream->voice, activeStream->currentVolume, activeStream->channel ? 127 : 0, 0, 0, 0);
        sndStreamFrq(activeStream->voice, first->header.reserved[2]);
        sndStreamADPCMParameter(activeStream->voice, &first->buffers[activeStream->channel]);
        activeStream->inUse = 8;
        if (first->inUse == 8 && second->inUse == 8) {
            _sndStreamARAMUpdate(first, &first->buffers[first->channel]);
            sndStreamActivate(first->voice); first->inUse = 9;
            _sndStreamARAMUpdate(second, &first->buffers[second->channel]);
            sndStreamActivate(second->voice); second->inUse = 9;
        }
        break;
    }
}
static void _sndStreamPrepareGetDataCallback(u8, u8 half, GSsndStream* userData) {
    GSsndStream* stream = userData;
    GSsndStream *first, *second;
    GSsndStreamBufferState* state;
    u32 headerPosition;
    if (stream->first) { first = stream->first; second = stream; }
    else { first = stream; second = stream->second; }
    state = &first->buffers[stream->channel];
    u32 start = _sndStreamNibble_HeaderOFF2ON(stream->readOffset);
    u32 end = start + 0x10000;
    u32 loopStart;
    if (first->header.loop == 1 && first->header.reserved31 == 1 && start <= (loopStart = first->header.loopStart - 2) && loopStart < end)
        headerPosition = _sndStreamNibble_GetHeaderPos(loopStart);
    else headerPosition = 0;
    stream->readOffset += stream->sampleCount >> 1;
    if (first->header.loop == 1 && stream->readOffset >= first->header.loopEndSamples) {
        stream->readOffset = first->header.loopStartSamples; first->header.reserved31 = 1;
    }
    stream->active = 1;
    if (first->active && second->active) {
        first->pendingBytes += first->bufferSize;
        if (first->pendingBytes >= (first->header.reserved[4] & 0x3ffffffe)) first->pendingBytes = 0;
        else if (first->pendingBytes >= GSfsysStreamGetCacheSize()) first->pendingBytes = 0;
        second->active = 0; first->active = 0;
    }
    _sndStreamPrepareGetDataCallback_Exec(stream, first, state, headerPosition, half);
}
extern GSsndDescriptor* snd_data;
void sndStreamDeactivate(u32);
void sndStreamMixParameterVolume(u32, s32, u8, u8);
u32 _sndStreamCallback(u32 firstOffset, u32 firstLength, u32 secondOffset, u32 secondLength, GSsndStream* stream) {
    GSsndStream *first, *second;
    if (stream->first) { first = stream->first; second = stream; }
    else { first = stream; second = stream->second; }
    if (!firstOffset && !secondOffset && !firstLength && !secondLength) {
        OSReport("--- Drop Stream Voice!! ---\n");
        first->inUse = 13; second->inUse = 13; return 0;
    }
    u8 target = stream->targetVolume;
    if (stream->currentVolume != target) {
        u16 time = stream->fadeTime;
        if (!time) { stream->currentVolume = target; _sndStreamFadePostProcess(stream); }
        else {
            u8 previous = stream->previousVolume;
            u8 step = stream->fadeStep;
            f32 targetFloat = target;
            stream->fadeStep = step + 1;
            f32 delta = ((targetFloat - (f32)previous) / (f32)time) * (f32)(step * 20);
            f32 volume = (f32)previous + delta;
            if (delta > 0.0f && volume >= targetFloat) { volume = targetFloat; _sndStreamFadePostProcess(stream); }
            else if (delta < 0.0f && volume <= targetFloat) { volume = targetFloat; _sndStreamFadePostProcess(stream); }
            stream->currentVolume = (s32)volume;
        }
    }
    if (stream->paused == 1 || stream->stopped == 1) sndStreamMixParameterVolume(stream->voice, 0, 0, 0);
    else {
        f32 scale = (f32)snd_data[stream->soundID].reserved01 * 0.0078125f;
        f32 volume = (f32)stream->currentVolume * scale;
        sndStreamMixParameterVolume(stream->voice, (s32)volume, 0, 0);
    }
    if (stream->inUse != 9) return 0;
    if (!first->header.loop && (&first->buffers[0].ready)[first->initialized] == 1 &&
        (&first->buffers[1].ready)[second->initialized] == 1 &&
        firstLength + secondLength + stream->writeOffset >= first->header.sampleCount) {
        sndStreamDeactivate(first->voice); first->inUse = 10;
        sndStreamDeactivate(second->voice); second->inUse = 10; return 0;
    }
    if (firstLength + secondLength < (stream->sampleCount >> 1)) return 0;
    if ((&first->buffers[0].ready)[first->initialized] == 1 && (&first->buffers[1].ready)[second->initialized] == 1) {
        void* buffer;
        if (first->initialized) buffer = (u8*)first->buffer + (first->bufferSize >> 1); else buffer = first->buffer;
        DCFlushRange(buffer, first->bufferSize >> 1);
        _sndStreamARAMUpdate(first, &first->buffers[first->channel]);
        (&first->header.reserved32)[first->channel] = 1;
        first->writeOffset += stream->sampleCount >> 1;
        if (first->header.loop == 1 && first->writeOffset >= first->header.loopEndSamples) first->writeOffset = first->header.loopStartSamples;
        if (second->initialized) buffer = (u8*)second->buffer + (second->bufferSize >> 1); else buffer = second->buffer;
        DCFlushRange(buffer, second->bufferSize >> 1);
        _sndStreamARAMUpdate(second, &first->buffers[second->channel]);
        (&first->header.reserved32)[second->channel] = 1;
        second->writeOffset += stream->sampleCount >> 1;
        if (first->header.loop == 1 && second->writeOffset >= first->header.loopEndSamples) second->writeOffset = first->header.loopStartSamples;
    }
    if ((&first->header.reserved32)[stream->channel] == 1) {
        (&first->header.reserved32)[stream->channel] = 0; return stream->sampleCount >> 1;
    }
    return 0;
}
#pragma dont_inline reset
}
