#include "graphics_round1.h"
static GSgfx_GCFifoObj _gpuFifo[2];
extern "C" { s32 gsgfx_gpu_mode; }
static s32 _gpuMode; static void *_gpuImmedBuf; static GSgfx_GCFifoObj *_gpuImmedFifo,*_gpuBufferFifo; static volatile s32 _gpuNextFifo;
static u8 _gpuIgnoreDrawDone,_gpuIgnoreDrawSync,_gpuIgnoreBreakpoint;
static void (*_gpuDrawDoneUserCB)(); static void (*_gpuDrawSyncUserCB)(u16); static void (*_gpuBreakpointUserCB)();
extern "C" {
static void _gpuBreakpointCallback__Fv(); static void _gpuDrawSyncCallback__FUs(u16); static void _gpuDrawDoneCallback__Fv();
void GSgfxGPUGetBPTick__FPlPl(s32 *a,s32 *b) { *a=-1; *b=-1; }
void GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(GSgfx_GCFifoObj *f,void *start,void *end) {
    GSgfx_GCFifoObj *next; BOOL interrupts=OSDisableInterrupts(); next=&_gpuFifo[_gpuNextFifo++]; if(_gpuNextFifo>1) _gpuNextFifo=0;
    u32 size=GXGetFifoSize(sdk(f)); void *base=GXGetFifoBase(sdk(f));
    next->base=base; next->end=(u8*)base+size-4; next->size=size; next->high=size-(size>>4); next->low=size>>1; next->read=base; next->write=base; next->count=0; next->wrap=0; next->link=0;
    GXInitFifoPtrs(sdk(next),start,end);
    gsgfxState->sourceFifo=f; gsgfxState->gpuFifo=next; gsgfxState->start=start; gsgfxState->end=end; gsgfxState->complete=0; gsgfxState->active=1;
    GXEnableBreakPt(end); GXSetGPFifo(sdk(next)); OSRestoreInterrupts(interrupts);
}
void GSgfxGPUInitFifoBase__FP15GSgfx_GCFifoObjPvUl(GSgfx_GCFifoObj *f,void *base,u32 size) {
    f->base=base; f->end=(u8*)base+size-4; f->size=size; f->high=size-(size>>4); f->low=size>>1; f->read=base; f->write=base; f->count=0; f->wrap=0; f->link=0;
}
void GSgfxGPUSetBreakpointCallback__FPFv_v(void(*cb)()) { _gpuBreakpointUserCB=cb; }
void GSgfxGPUSetDrawSyncCallback__FPFUs_v(void(*cb)(u16)) { _gpuDrawSyncUserCB=cb; }
void GSgfxGPUSetDrawDoneCallback__FPFv_v(void(*cb)()) { _gpuDrawDoneUserCB=cb; }
void GSgfxGPUEnterBufferedMode__FP15GSgfx_GCFifoObj(GSgfx_GCFifoObj *f) { GSgfxGPUSetMode(2); GXSetCPUFifo(sdk(f)); }
inline void setRead(GSgfx_GCFifoObj *f,void *ptr) { void *read,*write; BOOL intr=OSDisableInterrupts(); GXGetFifoPtrs(sdk(f),&read,&write); GXInitFifoPtrs(sdk(f),ptr,write); OSRestoreInterrupts(intr); }
inline void setWrite(GSgfx_GCFifoObj *f,void *ptr) { void *read,*write; BOOL intr=OSDisableInterrupts(); GXGetFifoPtrs(sdk(f),&read,&write); GXInitFifoPtrs(sdk(f),read,ptr); OSRestoreInterrupts(intr); }
s32 GSgfxGPUSetMode(s32 mode) {
    s32 old=_gpuMode;
    if(mode!=0) {
    if(old==mode) return old;
    switch(mode) {
    case 1:
        GSgfxRenderAbortFrame__Fv(); _gpuBufferFifo=(GSgfx_GCFifoObj*)GXGetCPUFifo(); GXSaveCPUFifo(sdk(_gpuBufferFifo)); GXSaveGPFifo(GXGetGPFifo());
        memset(_gpuImmedBuf,0,0x10000); DCFlushRange(_gpuImmedBuf,0x10000); setRead(_gpuImmedFifo,_gpuImmedBuf); setWrite(_gpuImmedFifo,_gpuImmedBuf);
        GXSetCPUFifo(sdk(_gpuImmedFifo)); GXSetGPFifo(sdk(_gpuImmedFifo)); GXDisableBreakPt(); GSgfx_GCReset(); _gpuIgnoreDrawDone=1; GXDrawDone(); VIWaitForRetrace(); _gpuIgnoreDrawDone=0; break;
    case 2: switch(old) {
        case 0: _gpuIgnoreDrawDone=1; GXDrawDone(); VIWaitForRetrace(); _gpuIgnoreDrawDone=0; GXSaveCPUFifo(sdk(_gpuImmedFifo)); break;
        case 1: GSgfxRenderAbortFrame__Fv(); GXSaveCPUFifo(sdk(_gpuImmedFifo)); GXSetCPUFifo(sdk(_gpuBufferFifo)); GSgfx_GCReset(); break;
        } break;
    }
    _gpuMode=mode; gsgfx_gpu_mode=mode; return old;
    }
    return mode;
}
GSgfx_GCFifoObj *GSgfxGPUGetImmediateFifo__Fv() { return _gpuImmedFifo; }
void GSgfxGPUShutdown__Fv() { GXBool idle,dummy; GXGetGPStatus(&dummy,&dummy,&idle,&dummy,&dummy); if(idle!=1) GXAbortFrame(); GXSetDrawDoneCallback(0); GXSetDrawSyncCallback(0); GXSetBreakPtCallback(0); }
void GSgfxGPUInit__Fv() {
    _gpuImmedBuf=GSmemAlloc(0x10000); DCFlushRange(_gpuImmedBuf,0x10000); _gpuImmedFifo=(GSgfx_GCFifoObj*)GXInit(_gpuImmedBuf,0x10000);
    _gpuMode=0; gsgfx_gpu_mode=0; gsgfxState->sourceFifo=0; gsgfxState->gpuFifo=0; gsgfxState->start=0; gsgfxState->end=0; gsgfxState->complete=0; gsgfxState->active=0;
    _gpuIgnoreDrawDone=0; _gpuIgnoreDrawSync=0; _gpuIgnoreBreakpoint=0; _gpuDrawDoneUserCB=0; _gpuDrawSyncUserCB=0; _gpuBreakpointUserCB=0;
    GXSetDrawDoneCallback(_gpuDrawDoneCallback__Fv); GXSetDrawSyncCallback(_gpuDrawSyncCallback__FUs); GXSetBreakPtCallback(_gpuBreakpointCallback__Fv);
}
static void _gpuBreakpointCallback__Fv() {
    void *end; GXFifoObj *fifo=GXGetGPFifo(); if(fifo!=sdk(_gpuImmedFifo)) {
        OSEnableInterrupts(); GXBool idle,dummy; do { GXGetGPStatus(&dummy,&dummy,&idle,&dummy,&dummy); } while(idle!=1);
        OSDisableInterrupts(); GXSaveGPFifo(fifo); gsgfxState->complete=1; gsgfxState->active=0;
        GSgfx_GCFifoObj *source=gsgfxState->sourceFifo; end=gsgfxState->end; setRead(source,end); source->complete=1;
        if(_gpuIgnoreBreakpoint!=1 && _gpuBreakpointUserCB) _gpuBreakpointUserCB();
    }
}
bool GSgfxGPUIsIdle__Fv() { GXBool dummy,idle; GXGetGPStatus(&dummy,&dummy,&idle,&dummy,&dummy); return idle==1; }
void GSgfxGPUSetFifoWritePtr__FP15GSgfx_GCFifoObjPv(GSgfx_GCFifoObj *f,void *ptr) { void *read,*write; BOOL intr=OSDisableInterrupts(); GXGetFifoPtrs(sdk(f),&read,&write); GXInitFifoPtrs(sdk(f),read,ptr); OSRestoreInterrupts(intr); }
static void _gpuDrawSyncCallback__FUs(u16 token) { if(_gpuIgnoreDrawSync!=1 && _gpuDrawSyncUserCB) _gpuDrawSyncUserCB(token); }
static void _gpuDrawDoneCallback__Fv() { if(_gpuIgnoreDrawDone!=1 && _gpuDrawDoneUserCB) _gpuDrawDoneUserCB(); }
}
