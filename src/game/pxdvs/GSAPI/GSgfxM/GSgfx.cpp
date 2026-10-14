#include "graphics_round1.h"
enum GSscratchNotify { ScratchOut, ScratchIn };
struct _GSgfxInitParms { u8 halt; u8 pad1[3]; u8 buffers; u8 pad5; u16 height; s32 mode; u32 a,b,c; };
ABI_SIZE(_GSgfxInitParms,0x18); ABI_OFF(_GSgfxInitParms,buffers,4); ABI_OFF(_GSgfxInitParms,a,0xc);
class GSgfxLayer;
extern "C" {
void *GSscratchAlloc(u32,void(*)(GSscratchNotify,void*,u8));
void GSgfxHaltInit__Fv(); void GSmathInit(); void GSgfxRenderInit__Fv(); void GSgfxVFInit__Fv(); void GSgfxLayerInit__Fv(); void GSgfxPerfbarInit__FUc(u8); void GSgfxBackFBInit__Fv(); void GSgfxResetInit__Fv(); void HSD_Init(); void GSgfxRenderSetupFirstFrame__Fv();
void GSlogWrite(const char*,...);
GSgfxLayer *__ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(void*,s32,char*,u32,u32,u32,s32);
}
static GraphicsState _gfxMemoryState;
extern "C" { GraphicsState *gsgfxState; }
extern "C" { static void _gfxScratchNotify__F15GSscratchNotifyPvUc(GSscratchNotify,void*,u8); }
extern "C" void GSgfxRelocToScratch() {
    GraphicsState *state = (GraphicsState*)GSscratchAlloc(12,_gfxScratchNotify__F15GSscratchNotifyPvUc);
    memcpy(state,gsgfxState,sizeof(GraphicsState)); gsgfxState=state;
}
extern "C" void GSgfxShutdown__Fv() { GSgfxVideoShutdown__Fv(); GSgfxGPUShutdown__Fv(); }
extern "C" void GSgfxInit__FP15_GSgfxInitParms(_GSgfxInitParms *p) {
    gsgfxState=&_gfxMemoryState; memset(&_gfxMemoryState,0,sizeof(GraphicsState));
    GSgfx_GCFirstInit(); GSgfx_GCInitState(); GSgfxVideoInit__FUcUs14GSgfxVideoMode(p->buffers,p->height,p->mode); GSgfxGPUInit__Fv(); GSgfxVideoSecondInit__Fv();
    if(p->halt==1) GSgfxHaltInit__Fv();
    GSmathInit(); GSgfxRenderInit__Fv(); GSgfxVFInit__Fv(); GSgfxLayerInit__Fv(); GSgfxTokenInit__Fv(); GSgfxPerfbarInit__FUc(4); GSgfxBackFBInit__Fv(); GSgfxResetInit__Fv(); HSD_Init();
    void *layer=operator new(0x1a14); if(layer) __ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(layer,2,"main",p->a,p->b,p->c,0);
    GSgfxRenderSetupFirstFrame__Fv(); GSlogWrite("GSgfx: Init OK, state located at %08Xh (size=%d)\n",gsgfxState,0xc64);
}
static void _gfxScratchNotify__F15GSscratchNotifyPvUc(GSscratchNotify n,void *p,u8) {
    switch(n) { case ScratchOut: memcpy(&_gfxMemoryState,p,sizeof(GraphicsState)); gsgfxState=&_gfxMemoryState; break;
    case ScratchIn: memcpy(p,&_gfxMemoryState,sizeof(GraphicsState)); gsgfxState=(GraphicsState*)p; break; }
}
