#ifndef GSGFX_RECOVERY_H
#define GSGFX_RECOVERY_H
#include <dolphin/gx.h>
#include <dolphin/vi.h>
#include <dolphin/os.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
#include <libc/string.h>
#define ABI_SIZE(t,s) typedef char abi_size_##t[(sizeof(t)==(s))?1:-1]
#define ABI_OFF(t,f,o) typedef char abi_offset_##t##_##f[(offsetof(t,f)==(o))?1:-1]
struct GSgfx_GCFifoObj {
    void *base, *end; u32 size, high, low; void *read, *write;
    s32 count; u8 wrap, link; u8 pad22[0x2a]; u32 complete; u8 pad50[0x30];
};
ABI_SIZE(GSgfx_GCFifoObj,0x80); ABI_OFF(GSgfx_GCFifoObj,complete,0x4c);
struct RenderEntry { GSgfx_GCFifoObj *fifo; void *start,*end; u32 color; void (*callback)(void*); void *arg; };
ABI_SIZE(RenderEntry,0x18); ABI_OFF(RenderEntry,callback,0x10);
struct GraphicsState {
    u32 dirty; u8 pad4[0xc20]; float vx,vy,vw,vh,vnear,vfar; u32 field;
    void *layer; void *xfb; s32 copyState; RenderEntry *list;
    GSgfx_GCFifoObj *sourceFifo,*gpuFifo; void *start,*end; u8 complete,active; u8 padC62[2];
};
ABI_SIZE(GraphicsState,0xc64); ABI_OFF(GraphicsState,vx,0xc24); ABI_OFF(GraphicsState,layer,0xc40); ABI_OFF(GraphicsState,sourceFifo,0xc50); ABI_OFF(GraphicsState,complete,0xc60);
struct GSgfxRenderWaitData { s32 vsync; u32 perf; };
ABI_SIZE(GSgfxRenderWaitData,8); ABI_OFF(GSgfxRenderWaitData,perf,4);
inline GXFifoObj *sdk(GSgfx_GCFifoObj *f) { return reinterpret_cast<GXFifoObj *>(f); }
extern "C" {
extern GraphicsState *gsgfxState; extern s32 gsgfx_gpu_mode;
void *GSmemAlloc(u32);
void GSgfx_GCReset(); void GSgfx_GCFirstInit(); void GSgfx_GCInitState(); void GSgfx_GCFlushState();
void GSgfxRenderAbortFrame__Fv(); void GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(GSgfxRenderWaitData*); void GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(GSgfxRenderWaitData*); void GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(GSgfxRenderWaitData*);
u8 GSgfxRenderIsPaused();
void GSgfxGPUInit__Fv(); void GSgfxGPUShutdown__Fv();
GSgfx_GCFifoObj *GSgfxGPUGetImmediateFifo__Fv();
void GSgfxGPUInitFifoBase__FP15GSgfx_GCFifoObjPvUl(GSgfx_GCFifoObj*,void*,u32);
void GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(GSgfx_GCFifoObj*,void*,void*);
bool GSgfxGPUIsIdle__Fv(); s32 GSgfxGPUSetMode(s32);
void GSgfxGPUSetDrawSyncCallback__FPFUs_v(void(*)(u16));
void GSgfxGPUSetDrawDoneCallback__FPFv_v(void(*)()); void GSgfxGPUSetBreakpointCallback__FPFv_v(void(*)());
void GSgfxVideoSetupNextFrame__Fv(); void GSgfxVideoShutdown__Fv(); void GSgfxVideoSecondInit__Fv(); void GSgfxVideoInit__FUcUs14GSgfxVideoMode(u8,u16,s32);
float GSgfxVideoGetLastRenderTime(); s32 GSgfxVideoGetVsyncCount(); u8 GSgfxVideoGetVsyncRate(); u8 GSgfxVideoGetXFBCount();
u8 GSgfxVideoSetXFBReady__FPv(void*); void *GSgfxVideoCopyEFBToXFB__Fv(); void *GSgfxVideoFindFreeXFB__Fb(bool);
u32 GSgfxVideoBuildEFB2XFBCopy__FPvPv(void*,void*);
void GSgfxVideoSetOneShotPostCallback__FPFPv_v(void(*)(void*));
void GSgfxTokenInit__Fv(); void GSgfxTokenAbortFrame__Fv(); void GSgfxTokenMarkFrame__Fv(); u16 GSgfxTokenMark_Sub__Fv(); u8 GSgfxTokenCleared(u16);
void GSgfxPerfbarCPUStart__Fv(); void GSgfxPerfbarCPUEnd__Fv(); void GSgfxPerfbarGPUStart__Fv(); void GSgfxPerfbarGPUEnd__Fv(); u32 GSgfxPerfbarCPUEntry(u32); void GSgfxPerfbarGPUEntry__FUl(u32);
void GSgfxLayerInvalidateAll__Fv();
}
#endif
