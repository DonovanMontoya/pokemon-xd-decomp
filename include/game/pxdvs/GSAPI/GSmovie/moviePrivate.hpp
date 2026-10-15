#ifndef MOVIE_PRIVATE_HPP
#define MOVIE_PRIVATE_HPP
#include <global.h>
struct THPReadBuffer { u8* data; u32 frame; u8 valid,video,audio,reserved; u32 size; };
struct THPTextureSet {u8 *y,*u,*v; u32 frame; u8 valid,displayed; u8 reserved[2];};
struct THPAudioBuffer {s16 *buffer,*current; u32 samples; union { u32 flags; u8 state[4]; };};
struct MovieDecoder {
    u32 magic,version,maxBufferSize,maxAudioSamples; f32 frameRate; u32 frames,firstFrameSize,movieBytes,componentOffset,offsetTableOffset,firstFrameOffset,lastFrameOffset;
    u32 componentCount; u8 componentTypes[16]; u32 width,height,videoType,channels,sampleRate,audioSamples,tracks;
    u8 streamBuffer[0x8000]; s32 fetchState; u32 streamOffset; u32 fetchArg,fetchSize,fetchPos; void* videoWork;
    u8 state,nextState,loop,hasAudio; s32 videoError,audioError;
    u8 preload,startAudio,paused,visible;
    u8* preloadBuffer; u32 currentOffset,currentSize,currentFrame;
    s64 videoTicks; s64 audioTicks; u32 framesDecoded,audioTrack; s32 lastAudioFrame,playedAudioFrame;
    u16 token1,token2; THPTextureSet* displayTexture; THPAudioBuffer* currentAudio;
    THPReadBuffer reads[10]; u32 readWrite,readVideo,readAudio;
    THPTextureSet textures[3]; u32 texWrite,texRead;
    THPAudioBuffer audio[6]; u32 audioWrite,audioRead;
    u32 leftStream,rightStream; s16* leftBuffer; s16* rightBuffer;
    u32 reserved822c; u64 marks[5]; u32 markRead; s32 markWrite; u32 reserved8260[4]; u64 samplesPlayed;
};
struct __GSmovieStreaming {s32 state; u32 layer,handle; u16 x,y; u8* workBuffer; u8 ready,reading,loop,track; u16 token; u16 reserved1a; MovieDecoder* decoder;};
typedef char MovieDescriptorSize[sizeof(__GSmovieStreaming)==0x20?1:-1];
extern "C" {
void sndStreamFree(u32); u8 sndStreamActivate(u32); void sndStreamDeactivate(u32);
void* GSmemAllocAlignFromEnd(u32,u32); void GSmemFree(void*);
s32 OSDisableInterrupts(); void OSRestoreInterrupts(s32);
void DCInvalidateRange(void*,u32);
void _StreamQuit(__GSmovieStreaming*); u8 _StreamPlay(__GSmovieStreaming*);
void _movieStreamPrepareGetData(__GSmovieStreaming*); void _movieStreamDecode(__GSmovieStreaming*);
u8 _StreamInit(__GSmovieStreaming*);u8 _StreamInitFillStreamBuffer(__GSmovieStreaming*);
}
#endif
