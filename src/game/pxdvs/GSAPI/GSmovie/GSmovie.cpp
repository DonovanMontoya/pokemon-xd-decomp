#include <game/pxdvs/GSAPI/GSmovie/moviePrivate.hpp>
#include <libc/string.h>
static u8 _initFlag;
static s32 _movieDaemonHDL;
static u32 _maxStreaming;
static __GSmovieStreaming* _movieStreaming;
static __GSmovieStreaming* _activeMovieStreaming;
static u8 _movieValidScratch;
static void (*OldVIPostCallback)(u32);
static u8 _readWaitFlag;
static u8* _readAddr;
static u32 _readOffset,_readBytes;
static s32 _movieLayerUseCount;
static s32 _movieLayerID=-1;
extern "C" {
void GSgfxRenderWaitForDrawComplete__Fv();
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
void GSfsysCancel(u32); void GSthreadSwitch(); void GSscratchSetValid();
void (*GSgfxVideoSetVSyncCallback(void(*)(u32)))(u32);
u32 GSfsysStreamGetCacheSize();
u8 GSfsysStreamGetData(u32,u32,void*,u32,u32,void(*)(s32,void*,s32),void*,s32);
}
static inline __GSmovieStreaming* findMovie(u32 handle) {
    u32 base;
    __GSmovieStreaming* movie;
    s32 offset;
    u32 count;
    count=_maxStreaming;
    offset=0;
    base=(u32)_movieStreaming;
    for(u32 i=0;i<count;++i) {
        movie=(__GSmovieStreaming*)(base+offset);
        if(movie->state && handle==movie->handle) return movie;
        offset+=0x20;
    }
    return 0;
}
static void _movieStreamTHPPlayerPrepareGetDataCallback(s32,void* context,s32) {
    __GSmovieStreaming* movie=(__GSmovieStreaming*)context;
    s32 interrupts;
    MovieDecoder* decoder=movie->decoder;
    _readOffset+=0x8000;
    if(_readOffset>=decoder->movieBytes) _readOffset=0;
    if(_readOffset>=GSfsysStreamGetCacheSize()) _readOffset=0;
    _readAddr+=0x8000; _readBytes+=0x8000;
    if(_readBytes>=decoder->movieBytes) { _readWaitFlag=1; return; }
    interrupts=OSDisableInterrupts();
    u8 success;
    if(GSfsysStreamGetData(movie->handle,0,_readAddr,0x8000,_readOffset,_movieStreamTHPPlayerPrepareGetDataCallback,movie,0)==1) { success=1; _readWaitFlag=0; }
    else success=0;
    OSRestoreInterrupts(interrupts);
    if(!success) _readWaitFlag=1;
}
extern "C" {
void GSmovieAllContinue() {
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* current=&_movieStreaming[i];
        if(current->state && _initFlag) { __GSmovieStreaming* movie=findMovie(current->handle); if(movie) movie->decoder->paused=0; }
    }
}
void GSmovieAllPause() {
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* current=&_movieStreaming[i];
        if(current->state && _initFlag) { __GSmovieStreaming* movie=findMovie(current->handle); if(movie) movie->decoder->paused=1; }
    }
}
void GSmovieStop(u32 handle) {
    if(_initFlag) {
        __GSmovieStreaming* movie=findMovie(handle);
        if(movie) {
            GSgfxRenderWaitForDrawComplete__Fv();
            if(movie->layer && --_movieLayerUseCount==0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(_movieLayerID); _movieLayerID=-1; }
            GSfsysCancel(movie->handle);
            MovieDecoder* decoder=movie->decoder;
            if(decoder->state) {
                decoder->nextState=0; decoder->state=0;
                if(decoder->hasAudio) _StreamQuit(movie);
                decoder->videoError=0; decoder->audioError=0;
            }
            GSmemFree(movie->workBuffer);
            if(movie==_activeMovieStreaming) _activeMovieStreaming=0;
            s32 interrupts=OSDisableInterrupts();
            movie->state=0; movie->handle=0;
            if(movie->decoder) { GSmemFree(movie->decoder); movie->decoder=0; }
            OSRestoreInterrupts(interrupts);
            if(_movieValidScratch==1) {
                u8 active=0;
                for(u32 i=0;i<_maxStreaming;++i) if(_movieStreaming[i].state) active=1;
                if(!active) { GSscratchSetValid(); _movieValidScratch=0; GSgfxVideoSetVSyncCallback(OldVIPostCallback); OldVIPostCallback=0; }
            }
        }
    }
}
void GSmoviePlayWait(u32 handle) {
    if(_initFlag) {
        for(;;) {
            __GSmovieStreaming* movie=findMovie(handle);
            if(!movie) return;
            switch(movie->state) { case 0: case 9: case 10: case 11: return; }
            GSthreadSwitch();
        }
    }
}
s32 fn_801E3C5C(u32 handle) {
    if(!_initFlag) return -2;
    __GSmovieStreaming* movie=findMovie(handle);
    if(!movie) return -1;
    MovieDecoder* decoder=movie->decoder;
    if(decoder->paused==1) return 2;
    switch(decoder->state) {case 5:return -2;case 3:return 0;default:case 4:return 1;}
}
s32 GSmoviePlayCheck(u32 handle) { if(!_initFlag) return 0; __GSmovieStreaming* movie=findMovie(handle); if(!movie) return 0; return 1; }
}

#pragma force_active on
static s32 _THPPlayerSetBuffer(__GSmovieStreaming* movie) {
    MovieDecoder* decoder=movie->decoder;
    if(decoder->state==0) {
        u8* memory=movie->workBuffer;
        if(decoder->preload) { decoder->preloadBuffer=memory; memory+=decoder->movieBytes; }
        for(s32 i=0;i<10;++i) {
            THPReadBuffer* buffer=&decoder->reads[i];
            buffer->data=memory; buffer->valid=0; buffer->video=0;
            if(decoder->hasAudio) buffer->audio=0; else buffer->audio=1;
            buffer->size=0; memory+=(decoder->maxBufferSize+31)&~31;
        }
        u32 pixels=decoder->width*decoder->height;
        u32 yBytes=(pixels+31)&~31;
        u32 uvBytes=((pixels>>2)+31)&~31;
        for(u32 i=0;i<3;++i) {
            THPTextureSet* texture=&decoder->textures[i];
            texture->y=memory; DCInvalidateRange(memory,yBytes); memory+=yBytes;
            texture->u=memory; DCInvalidateRange(memory,uvBytes); memory+=uvBytes;
            texture->v=memory; DCInvalidateRange(memory,uvBytes); memory+=uvBytes;
            texture->valid=0; texture->displayed=0;
        }
        if(decoder->hasAudio) {
            for(s32 i=0;i<6;++i) {
                THPAudioBuffer* buffer=&decoder->audio[i];
                buffer->buffer=(s16*)memory; buffer->current=(s16*)memory; buffer->samples=0; buffer->flags=0;
                memory+=((decoder->maxAudioSamples*4)+31)&~31;
            }
            decoder->leftBuffer=(s16*)memory;
            memory+=((((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)*2)&~63);
            if(decoder->channels==2) {
                decoder->rightBuffer=(s16*)memory;
                memory+=((((u32)(0.5f+(f32)(decoder->sampleRate*60)/1000.0f)+31)*2)&~63);
            }
        }
        *(u8**)((u8*)decoder+0x8074)=memory;
        return 1;
    }
    return 0;
}

#pragma force_active reset

extern "C" MovieDecoder* GSmovieStreamPreFunc(u32 handle) {
    if(!_initFlag) return 0;
    __GSmovieStreaming* movie=findMovie(handle);
    if(!movie) return 0;
    return movie->decoder;
}
extern "C" void GSfsysStreamSetLoopFlag(u32,u32,u8);
extern "C" void GSmovieStreamPostFunc(u32 handle,u32 resource) {
    if(_initFlag) {
        __GSmovieStreaming* movie=findMovie(handle);
        if(movie) { movie->state=3; GSfsysStreamSetLoopFlag(handle,resource,movie->loop); }
    }
}
struct GSgfxLayer;
enum GSgfxLayerPass { MOVIE_PASS_DEFAULT };
extern void _movieRender(GSgfxLayer*,GSgfxLayerPass);
extern void _movieDaemon();
extern "C" void GSgfxTokenWaitForClearAndReset(u16*);
#pragma force_active on
static void _movieBeforeRender(f32) {
    u8 active=0;
    s32 offset=0;
    for(u32 i=0;i<_maxStreaming;++i) {
        __GSmovieStreaming* movie=(__GSmovieStreaming*)((u8*)_movieStreaming+offset);
        if(movie->state && GSmoviePlayCheck(movie->handle)) {
            active=1;
            switch((s32)movie->decoder->state) {
            case 3:case 5: movie->state=10;break;
            case 4:break;
            }
        }
        offset+=0x20;
    }
    if(active==1) {
        s32 offset=0;
        for(u32 i=0;i<_maxStreaming;++i) {
            __GSmovieStreaming* movie=(__GSmovieStreaming*)((u8*)_movieStreaming+offset);
            if(movie->state) {
                MovieDecoder* decoder=movie->decoder;
                GSgfxTokenWaitForClearAndReset(&movie->token);
                for(s32 j=0;j<3;++j) {
                    THPTextureSet* texture=&decoder->textures[j];
                    if(texture->displayed==1) {texture->displayed=0;texture->valid=0;}
                }
            }
            offset+=0x20;
        }
    }
}
#pragma force_active reset
struct GSgfxRenderModule {void* reserved00;void(*update)(f32);void(*render)(GSgfxLayer*,GSgfxLayerPass);void(*fastRender)();void* reserved10;void* reserved14;u32 id;};
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);
extern "C" u32 GSgappCreate(s32,u8,u32,void(*)(u32,u32));
extern "C" void GSgappSetName(u32,const char*);
extern "C" void GSmovieInit() {
    GSgfxRenderModule module={0,_movieBeforeRender,_movieRender,0,0,0,0xb29a48e1};
    if(_initFlag!=1) {
        _maxStreaming=4;
        _movieStreaming=(__GSmovieStreaming*)GSmemAllocAlignFromEnd(0x80,0x20);
        u8 success;
        if(!_movieStreaming) success=0;
        else {
            u32 i=0;
            s32 offset=i;
            u32 handle=i;
            s32 state=i;
            MovieDecoder* decoder=(MovieDecoder*)i;
            for(;i<_maxStreaming;++i) {
                __GSmovieStreaming* movie=(__GSmovieStreaming*)((u8*)_movieStreaming+offset);
                movie->handle=handle;movie->state=state;movie->decoder=decoder;
                offset+=0x20;
            }
            success=1;
        }
        if(success) {
            _movieDaemonHDL=GSgappCreate(1,30,0,(void(*)(u32,u32))_movieDaemon);
            GSgappSetName(_movieDaemonHDL,"GSmovieDaemon");
            _activeMovieStreaming=0;_movieValidScratch=0;
            GSgfxRenderModuleRegister(8,&module,0);_initFlag=1;
        }
    }
}
extern void _PlayControlExec(__GSmovieStreaming*);
#pragma force_active on
static void _PlayControl(u32 count) {
    if(OldVIPostCallback) OldVIPostCallback(count);
    s32 offset;
    u32 i;
    i=0;
    offset=0;
    for(;i<_maxStreaming;) {
        __GSmovieStreaming* movie=(__GSmovieStreaming*)((u8*)_movieStreaming+offset);
        if(movie->state) _PlayControlExec(movie);
        ++i;
        offset+=0x20;
    }
}
#pragma force_active reset
