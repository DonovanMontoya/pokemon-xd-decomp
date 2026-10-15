#include "graphics_round1.h"
// This revision's VI mode uses the original 0x3c-byte GX layout.
struct VideoMode { u32 tv; u16 width,height,xfbHeight,xOrigin,yOrigin,viWidth,viHeight; u8 pad12[2]; u32 xfbMode; u8 field,aa; u8 samples[12][2]; u8 filter[7]; u8 pad39[3]; };
struct VideoBuffer { s32 state; void *ptr; };
struct Viewport { float x,y,width,height,nearZ,farZ; };
struct VideoState { VideoMode mode; VideoBuffer buffers[3]; VideoBuffer *displayed; volatile u8 count; u8 rate,field,pad5b; volatile u16 requestedHeight;u16 maxHeight; s32 vsync,system; void(*callback)(u32); s32 missed,presented; float elapsed,lastElapsed; u8 pad7c[4]; s64 lastTime; volatile s32 lockRate; u8 lockCount,lockActive; u8 pad8e[2]; s32 copyMode,pixelFormat; float yScale; GXColor color; u32 depth; u8 padA4[4]; };
#pragma pack(push,1)
struct CopyParams { u16 x,y,width,height,stride; u8 padA[2]; s32 format,unused,mode; float scale; u8 clear; u32 color; u8 pad21[3]; u32 depth; };
#pragma pack(pop)
ABI_SIZE(VideoMode,0x3c); ABI_OFF(VideoMode,samples,0x1a); ABI_OFF(VideoMode,filter,0x32);
ABI_SIZE(VideoBuffer,8); ABI_SIZE(Viewport,0x18); ABI_SIZE(VideoState,0xa8); ABI_OFF(VideoState,count,0x58); ABI_OFF(VideoState,lastTime,0x80); ABI_OFF(VideoState,color,0x9c);
ABI_SIZE(CopyParams,0x28); ABI_OFF(CopyParams,color,0x1d); ABI_OFF(CopyParams,depth,0x24);
struct ModeEntry { s32 id; GXRenderModeObj *ntsc,*pal,*eurgb,*mpal; };
ABI_SIZE(ModeEntry,0x14);
extern "C" {
extern GXRenderModeObj GXPal264Ds,GXPal264DsAa,GXPal264Int,GXPal264IntAa,GXPal528Int,GXPal528IntDf,GXPal524IntAa,GXNtsc480ProgSoft;
extern u8 _gcGlobalRegState[];


void GSgfxSSGetViewportOffset__FPfPf(float*,float*);
u8 *GSgfx_GCWriteCopyFilterDirect(void*,u8,void*,u8,void*);
u8 *GSgfx_GCWriteCopyDispDirect(void*,CopyParams*,void*,u8,u8,u8);
void GSgfx_GCWriteCopyFilter(u8,void*,u8,void*);
void GSgfx_GCWriteCopyDisp(CopyParams*,void*,u8,u8,u8);
static void _videoUpdateViewport__Fb(bool);
static u8 _videoSetupRenderMode__F14GSgfxVideoMode15GSgfxVideoFrameb16GSgfxVideoFilterb(s32,s32,bool,s32,bool);
static void _videoPostRetraceFunc__FUl(u32); static void _videoPreRetraceFunc__FUl(u32);
void GSgfxVideoSetViewport__Fffffb(float,float,float,float,bool);
}
static ModeEntry _videoModeList[]={
 {1,&GXNtsc240Ds,&GXPal264Ds,&GXEurgb60Hz240Ds,&GXMpal240Ds},
 {2,&GXNtsc240DsAa,&GXPal264DsAa,&GXEurgb60Hz240DsAa,&GXMpal240DsAa},
 {3,&GXNtsc240Int,&GXPal264Int,&GXEurgb60Hz240Int,&GXMpal240Int},
 {4,&GXNtsc240IntAa,&GXPal264IntAa,&GXEurgb60Hz240IntAa,&GXMpal240IntAa},
 {5,&GXNtsc480Int,&GXPal528Int,&GXEurgb60Hz480Int,&GXMpal480Int},
 {6,&GXNtsc480IntDf,&GXPal528IntDf,&GXEurgb60Hz480IntDf,&GXMpal480IntDf},
 {7,&GXNtsc480IntAa,&GXPal524IntAa,&GXEurgb60Hz480IntAa,&GXMpal480IntAa},
 {8,&GXNtsc480Prog,0,0,0},{9,&GXNtsc480ProgSoft,0,0,0},{10,&GXNtsc480ProgAa,0,0,0},{0,0,0,0,0}
};
static VideoState _videoState; static Viewport _viewport; static u8 _videoDefaultFilter[7]={8,8,10,12,10,8,8}; static void(*_videoOneShotPostCB)(void*);
inline VideoBuffer *findPointer(void *ptr) { VideoState *scan=&_videoState; s32 i=0;while(i<_videoState.count) {if(scan->buffers[0].ptr==ptr) return &_videoState.buffers[i];scan=(VideoState*)((u8*)scan+8);i++;}return 0; }
inline VideoBuffer *findState(s32 state) { VideoState *scan=&_videoState;s32 i=0;while(i<_videoState.count) {if(scan->buffers[0].state==state) return &_videoState.buffers[i];scan=(VideoState*)((u8*)scan+8);i++;}return 0; }
inline VideoBuffer *freeBuffer(bool wait) {
    if(_videoState.count==3) { findState(4); }
    if(_videoState.count==1) return 0;
    GSgfxRenderWaitData data; GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(&data);
    for(;;) { BOOL intr=OSDisableInterrupts(); VideoBuffer *b=findState(3); OSRestoreInterrupts(intr);
        if(b) { GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(&data); return b; }
        if(!wait) { GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(&data); return 0; }
        GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(&data);
    }
}
inline void copyParams(CopyParams &p) { p.x=0;p.y=0;p.width=640;p.height=480;p.stride=640;p.format=3;p.unused=0;p.mode=_videoState.copyMode;p.scale=_videoState.yScale;p.clear=1;p.color=*(u32*)&_videoState.color;p.depth=_videoState.depth; }
extern "C" {
u32 GSgfxVideoBuildEFB2XFBCopy__FPvPv(void *cmd,void *xfb) {
    VideoBuffer *b=findPointer(xfb); b->state=4; CopyParams p;copyParams(p);
    void *out=GSgfx_GCWriteCopyFilterDirect(cmd,_videoState.mode.aa,_videoState.mode.samples,1,_videoState.mode.filter);
    u8 *end=GSgfx_GCWriteCopyDispDirect(out,&p,b->ptr,1,1,1); u32 size=end-(u8*)cmd; u32 rounded=(size+31)&~31; if(rounded-size) memset(end,0,rounded-size); DCFlushRange(cmd,rounded); return rounded;
}
VideoMode *GSgfxVideoGetRenderMode__Fv() { return &_videoState.mode; }
Viewport *GSgfxVideoGetViewport() { return &_viewport; }
void GSgfxVideoResetViewport__Fb(bool noOffset) { GSgfxVideoSetViewport__Fffffb(0,0,0.5f*_videoState.mode.width,0.5f*_videoState.mode.height,noOffset); }
void GSgfxVideoSetViewport__Fffffb(float x,float y,float right,float bottom,bool noOffset) {
    _viewport.x=x; _viewport.y=y; _viewport.width=2.0f*(right-x); _viewport.height=2.0f*(bottom-y); _viewport.nearZ=0; _viewport.farZ=1; _videoUpdateViewport__Fb(noOffset);
}
inline void GSgfx_GCWritePixelFmt(s32 format,u8 depth) {
    static u8 pxf2hw[8]={0,1,2,3,4,4,4,5}; static u8 yuvmap[4]={0,1,2,2};
    _gcGlobalRegState[3]=depth; _gcGlobalRegState[2]=pxf2hw[format]; if(format<4) _gcGlobalRegState[4]=0;else _gcGlobalRegState[4]=yuvmap[format-4];gsgfxState->dirty|=0x18;
}
void GSgfxVideoSetupNextFrame__Fv() {
    _videoState.lastElapsed=_videoState.elapsed; _gcGlobalRegState[1]=_videoState.mode.field; _gcGlobalRegState[0]=(_videoState.mode.viHeight>=2*_videoState.mode.xfbHeight); gsgfxState->dirty|=0x1400;
    if(_videoState.mode.aa==1) GSgfx_GCWritePixelFmt(2,0);else GSgfx_GCWritePixelFmt(_videoState.pixelFormat,0);
    _videoState.field=VIGetNextField(); GSgfxVideoResetViewport__Fb(false); GSgfx_GCFlushState();
}
inline u8 ready(void *ptr) {
    BOOL intr=OSDisableInterrupts(); VideoBuffer *b;
    if(_videoState.count==1) b=_videoState.displayed;
    else {
        b=findPointer(ptr); if(!b) { OSRestoreInterrupts(intr); return 0; }
        if(_videoState.count==3) { VideoBuffer *old=findState(2); if(old) old->state=3; }
        s64 now=OSGetTime(); float delta=(float)(now-_videoState.lastTime); _videoState.lastTime=now; _videoState.elapsed=delta/(float)(((*(u32*)0x800000f8)>>2)/_videoState.rate);
    }
    b->state=2; OSRestoreInterrupts(intr); return 1;
}
void *GSgfxVideoCopyEFBToXFB__Fv() {
    if(_videoState.count==1) { ready(0); VIWaitForRetrace();return 0; }
    VideoBuffer *b=freeBuffer(true); b->state=4; void *ptr=b->ptr; CopyParams p;copyParams(p); GSgfx_GCWriteCopyFilter(_videoState.mode.aa,_videoState.mode.samples,1,_videoState.mode.filter); GSgfx_GCWriteCopyDisp(&p,ptr,1,1,1); return b->ptr;
}
void GSgfxVideoGetEFBSize(u16 *width,u16 *height) { if(width) *width=_videoState.mode.width; if(height) *height=_videoState.mode.height; }
float GSgfxVideoGetLastRealRenderTime() { return _videoState.lastElapsed; }
float GSgfxVideoGetLastRenderTime() { if(GSgfxRenderIsPaused()==1) return 0; if(_videoState.lockActive==1) return _videoState.lastElapsed; return (float)(u32)(_videoState.lockRate+1); }
s32 GSgfxVideoGetVsyncCount() { return _videoState.vsync; }
u8 GSgfxVideoGetVsyncRate() { return _videoState.rate; }
u8 GSgfxVideoSetXFBReady__FPv(void *ptr) { return ready(ptr); }
void *GSgfxVideoFindFreeXFB__Fb(bool wait) { VideoBuffer *b=freeBuffer(wait); if(!b) return 0; return b->ptr; }
u8 GSgfxVideoGetXFBCount() { return _videoState.count; }
u8 GSgfxVideoGetLockFrameActive() { return _videoState.lockActive; }
s32 GSgfxVideoGetLockFrameRate() { return _videoState.lockRate; }
void GSgfxVideoSetLockFrameActive(u8 active) { _videoState.lockActive=active; }
void GSgfxVideoSetLockFrameRate(s32 rate) { if(_videoState.lockRate!=rate) { _videoState.lockRate=rate;_videoState.lockCount=_videoState.lockRate; } }
void GSgfxVideoSetFilter(u8 *filter) { VideoState *state=&_videoState; if(!filter) { memcpy(state->mode.filter,_videoDefaultFilter,7);return; } memcpy(state->mode.filter,filter,7); }
void GSgfxVideoGetClearColor(GXColor *color) { color->r=_videoState.color.r;color->g=_videoState.color.g;color->b=_videoState.color.b;color->a=_videoState.color.a; }
void GSgfxVideoSetClearColor(GXColor *color) { _videoState.color.r=color->r;_videoState.color.g=color->g;_videoState.color.b=color->b;_videoState.color.a=color->a; }
void (*GSgfxVideoSetVSyncCallback(void(*cb)(u32)))(u32) { void(*old)(u32)=_videoState.callback;_videoState.callback=cb;return old; }
void GSgfxVideoSetOneShotPostCallback__FPFPv_v(void(*cb)(void*)) { _videoOneShotPostCB=cb; }
u8 GSgfxVideoSetMode(s32 mode,s32 frame,bool interlace,s32 filter,bool progressive) {
    if(progressive==1) { if(mode!=0) return 0;if(frame!=1) return 0; }
    if(mode==1 && _videoState.maxHeight!=528) return 0;
    if(!_videoSetupRenderMode__F14GSgfxVideoMode15GSgfxVideoFrameb16GSgfxVideoFilterb(mode,frame,interlace,filter,progressive)) return 0;
    VISetBlack(1);VIConfigure((GXRenderModeObj*)&_videoState.mode);VIFlush();VIWaitForRetrace();VIWaitForRetrace();VISetBlack(0);VIFlush();return 1;
}
void GSgfxVideoShutdown__Fv() { VISetPreRetraceCallback(0);VISetPostRetraceCallback(0);VISetBlack(1);VIFlush();VIWaitForRetrace(); }
void GSgfxVideoSecondInit__Fv() {
    void *ptr=_videoState.displayed->ptr; CopyParams p;copyParams(p); GSgfx_GCWriteCopyFilter(_videoState.mode.aa,_videoState.mode.samples,1,_videoState.mode.filter);GSgfx_GCWriteCopyDisp(&p,ptr,1,1,1);
    ptr=_videoState.displayed->ptr; CopyParams q;copyParams(q); GSgfx_GCWriteCopyFilter(_videoState.mode.aa,_videoState.mode.samples,1,_videoState.mode.filter);GSgfx_GCWriteCopyDisp(&q,ptr,1,1,1);GXDrawDone();VISetBlack(0);VIFlush();
}
void GSgfxVideoInit__FUcUs14GSgfxVideoMode(u8 count,u16 height,s32 mode) {
    if(count==0 || count>3 || height>528) return;
    VIInit();_videoState.count=count;_videoState.requestedHeight=height;_videoState.callback=0;_videoState.vsync=0;_videoOneShotPostCB=0;
    _videoSetupRenderMode__F14GSgfxVideoMode15GSgfxVideoFrameb16GSgfxVideoFilterb(mode,1,false,1,false);
    switch(mode) {case 0:_videoState.maxHeight=480;break;default:_videoState.maxHeight=528;break;case 3:_videoState.maxHeight=480;break;}
    u32 area=((_videoState.mode.width+15)&0xfff0)*_videoState.maxHeight; s32 bytes=area*2; u32 words=area>>1;
    for(s32 i=0;i<3;i++) { VideoBuffer *b=&_videoState.buffers[i];if(i<_videoState.count) { b->ptr=GSmemAlloc(bytes);b->state=3;u32 *p=(u32*)b->ptr;for(u32 j=0;j<words;j++) *p++=0x10801080;DCFlushRange(b->ptr,bytes); }else {b->ptr=0;b->state=0;} }
    VISetPreRetraceCallback(_videoPreRetraceFunc__FUl);VISetPostRetraceCallback(_videoPostRetraceFunc__FUl);_videoState.buffers[0].state=1;VISetNextFrameBuffer(_videoState.buffers[0].ptr);_videoState.displayed=&_videoState.buffers[0];
    _videoState.copyMode=0;_videoState.color.r=0;_videoState.color.g=0;_videoState.color.b=0;_videoState.color.a=0;_videoState.depth=0xffffff;_videoState.pixelFormat=0;_videoState.missed=0;_videoState.presented=0;_videoState.elapsed=0;_videoState.lastElapsed=0;_videoState.lastTime=OSGetTime();_videoState.lockRate=0;_videoState.lockCount=0;_videoState.lockActive=0;
    VISetBlack(1);VIConfigure((GXRenderModeObj*)&_videoState.mode);VIFlush();VIWaitForRetrace();VIWaitForRetrace();
}

inline void writeViewport(float x,float y,float width,float height,float nearZ,float farZ,u32 field) {
    if(gsgfxState->vx!=x || gsgfxState->vy!=y || gsgfxState->vw!=width || gsgfxState->vh!=height || gsgfxState->vnear!=nearZ || gsgfxState->vfar!=farZ || gsgfxState->field!=field) {
        if(field==0) y-=0.5f;
        *(volatile u8*)0xcc008000=0x10;
        float hh=height*0.5f;
        *(volatile u16*)0xcc008000=5;
        float hw=width*0.5f;float z=farZ*16777216.0f;
        *(volatile u16*)0xcc008000=0x101a;
        *(volatile float*)0xcc008000=hw;
        *(volatile float*)0xcc008000=-hh;
        *(volatile float*)0xcc008000=-(nearZ*16777216.0f-z);
        *(volatile float*)0xcc008000=342.0f+(x+hw);
        *(volatile float*)0xcc008000=342.0f+(y+hh);
        *(volatile float*)0xcc008000=z+0.0f;
        gsgfxState->vx=x;gsgfxState->vy=y;gsgfxState->vw=width;gsgfxState->vh=height;gsgfxState->vnear=nearZ;gsgfxState->vfar=farZ;gsgfxState->field=field;
    }
}
static void _videoUpdateViewport__Fb(bool noOffset) {
    VideoState *state=&_videoState;float x,y;
    if(!noOffset) GSgfxSSGetViewportOffset__FPfPf(&x,&y);else {x=0;y=0;}
    if(state->mode.field) writeViewport(_viewport.x+x,_viewport.y+y,_viewport.width,_viewport.height,_viewport.nearZ,_viewport.farZ,_videoState.field);
    else writeViewport(_viewport.x+x,_viewport.y+y,_viewport.width,_viewport.height,_viewport.nearZ,_viewport.farZ,1);
}

static u8 _videoSetupRenderMode__F14GSgfxVideoMode15GSgfxVideoFrameb16GSgfxVideoFilterb(s32 mode,s32 frame,bool interlace,s32 filter,bool progressive) {
    s32 id=0;
    if(frame==0) { if(!interlace) { if(filter!=2) id=1;else id=2; } else if(filter!=2) id=3;else id=4; }
    else if(!progressive) { switch(filter) {case 0:id=5;break;case 1:id=6;break;case 2:id=7;break;} }
    else {switch(filter) {case 0:id=8;break;case 1:id=9;break;case 2:id=10;break;} }
    if(id==0) return 0;
    GXRenderModeObj *chosen=0; ModeEntry *entry=_videoModeList;
    s32 entryId;while((entryId=entry->id)!=0) { if(entryId==id) {switch(mode) {case 0:chosen=entry->ntsc;break;case 1:chosen=entry->pal;break;case 2:chosen=entry->eurgb;break;case 3:chosen=entry->mpal;break;}break;}entry++; }
    if(!chosen) return 0;
    VideoMode *renderMode=&_videoState.mode;memcpy(renderMode,chosen,0x3c);if(_videoState.requestedHeight!=0) renderMode->height=_videoState.requestedHeight;
    renderMode->xOrigin=30;renderMode->viWidth=660;_videoState.system=mode;if(mode==1) _videoState.rate=50;else _videoState.rate=60;
    _videoState.yScale=GXGetYScaleFactor(renderMode->height,renderMode->xfbHeight);return 1;
}
static void _videoPostRetraceFunc__FUl(u32 count) {
    _videoState.vsync++;
    if(_videoState.count!=1 && _videoOneShotPostCB) { VideoBuffer *b=freeBuffer(false);if(b) {void(*cb)(void*)=_videoOneShotPostCB;_videoOneShotPostCB=0;cb(b->ptr);} }
    if(_videoState.callback) _videoState.callback(count);
}
static void _videoPreRetraceFunc__FUl(u32) {
    if(_videoState.count!=1) {
        if(_videoState.lockActive==1 && _videoState.lockCount!=0) { _videoState.lockCount--;return; }
        VideoBuffer *b=findState(2);if(!b) {_videoState.missed++;return;}
        _videoState.presented++;VISetNextFrameBuffer(b->ptr);VIFlush();b->state=1;_videoState.displayed->state=3;_videoState.displayed=b;_videoState.lockCount=_videoState.lockRate;
    }
}
}
