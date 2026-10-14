#include "graphics_round1.h"
static u8 _renderXFBCommandBuf[0x10000]; static GSgfx_GCFifoObj _renderXFBCommandFifo; static RenderEntry _renderFifoList[64];
static void *_renderLastXFBPtr; static u32 _renderPauseCount; static void *_renderPrepareFrameStart,*_renderPrepareFrameEnd; static u16 _renderXFBCopyToken;
extern "C" {
extern Mtx mtxIdent; extern void *gsgfx_layer_activeFifo; extern u8 gsgfx_layer_inPrimitive;
void GSgfxRenderModuleDoPreUpdate__Ff(float); void GSgfxRenderModuleDoPostUpdate__Ff(float); void GSgfxRenderModuleInit__Fv();
void GSgfxPerfbarRender__FP10GSgfxLayer(void*); void GSgfxResetUpdate__Fv(); void GSgfxSSUpdate__Fv(); void GSgfxCaptureUpdate__FPv(void*);
s32 GSgfxLayerPrerender__Fv(); void GSgfxCaptureRenderFrameNumber__FP10GSgfxLayer(void*); void GSgfxBackFBDoFrame__FP10GSgfxLayer(void*); void GSgfxLayerRenderStats__FP10GSgfxLayer(void*);
void GSgfxLayerBuildRenderList__Fv(); void GSgfxLayerPrepareNextFrame__Fv(); void GSgfxLayerUpdateActiveFifoStats__Fv();
static void _renderResetGX__Fv(); static void _renderBreakpointCallback__Fv(); static void _renderCopyEFB__FPv(void*); static void _renderDrawDoneCallback__Fv();
inline void waitComplete() {
    s32 then; u32 perf=GSgfxPerfbarCPUEntry(0xffff00); then=GSgfxVideoGetVsyncCount();
    while(gsgfxState->xfb) {
        OSYieldThread(); if(GSgfxGPUIsIdle__Fv()!=1) {
            s32 now=GSgfxVideoGetVsyncCount();u32 limit=GSgfxVideoGetVsyncRate()*3; s32 elapsed=now-then;
            if(elapsed<0) then=now;else if((u32)elapsed>limit) {
                gsgfx_layer_inPrimitive=0;GSgfxVideoSetOneShotPostCallback__FPFPv_v(0);GXAbortFrame();GSgfxTokenAbortFrame__Fv();
                void *xfb=gsgfxState->xfb;if(xfb && xfb!=(void*)0xfefefefe) GSgfxVideoSetXFBReady__FPv(xfb);
                gsgfxState->copyState=0;gsgfxState->xfb=0;GSgfxLayerInvalidateAll__Fv();_renderResetGX__Fv();
            }
        }
    }
    GSgfxPerfbarCPUEntry(perf);
}
void GSgfxRender(void) {
    void *sp8;
    RenderEntry *temp_r28_4;
    f32 var_f31;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 temp_r28_3;
    s32 temp_r29_2;
    s32 temp_r30;
    s32 temp_r3;
    s32 temp_r3_3;
    s32 var_r29;
    s32 var_r30;

    u32 temp_r0;
    u32 temp_r0_2;
    void *temp_r29;
    void *temp_r3_2;
    void *temp_r3_4;


    var_f31 = GSgfxVideoGetLastRenderTime();
    GSgfxRenderModuleDoPreUpdate__Ff(var_f31);
    switch ((s32) gsgfx_gpu_mode) {                 /* irregular */
    case 1:
        GSgfxTokenMark_Sub__Fv();
        GSgfxPerfbarCPUEnd__Fv();
        GSgfxPerfbarGPUEnd__Fv();
        GSgfxPerfbarRender__FP10GSgfxLayer(gsgfxState->layer);
        if(GSgfxVideoGetXFBCount()>1) waitComplete();
        GSgfxResetUpdate__Fv();
        GSgfxSSUpdate__Fv();
        GSgfxCaptureUpdate__FPv(_renderLastXFBPtr);
        temp_r29 = GSgfxVideoCopyEFBToXFB__Fv();
        if (GSgfxVideoGetXFBCount() > 1U) {
            gsgfxState->xfb = (void*)temp_r29;
            GXSetDrawDone();
        }
        GSgfxPerfbarCPUStart__Fv();
        GSgfxPerfbarGPUStart__Fv();
        GSgfxLayerInvalidateAll__Fv();
        break;
    case 2:
        temp_r28_2 = GSgfxLayerPrerender__Fv();
        GSgfxCaptureRenderFrameNumber__FP10GSgfxLayer((void*)temp_r28_2);
        GSgfxBackFBDoFrame__FP10GSgfxLayer((void*)temp_r28_2);
        GSgfxPerfbarCPUEnd__Fv();
        GSgfxPerfbarRender__FP10GSgfxLayer((void*)temp_r28_2);
        GSgfxLayerRenderStats__FP10GSgfxLayer((void*)temp_r28_2);
        if(GSgfxVideoGetXFBCount()>1) waitComplete();
        _renderXFBCopyToken = GSgfxTokenMark_Sub__Fv();
        GSgfxResetUpdate__Fv();
        GSgfxSSUpdate__Fv();
        GSgfxCaptureUpdate__FPv(_renderLastXFBPtr);
        gsgfxState->xfb = (void*)0xFEFEFEFE;
        _renderFifoList[0].fifo = GSgfxGPUGetImmediateFifo__Fv();
        _renderFifoList[0].start = _renderPrepareFrameStart;
        _renderFifoList[0].end = _renderPrepareFrameEnd;
        _renderFifoList[0].color = 0x808080;
        _renderFifoList[1].fifo = 0;
        gsgfxState->list = &_renderFifoList[1];
        GSgfxLayerBuildRenderList__Fv();
        GSgfxPerfbarGPUStart__Fv();
        gsgfxState->list = _renderFifoList;
        temp_r28_4 = gsgfxState->list;
        GSgfxPerfbarGPUEntry__FUl(temp_r28_4->color);
        GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(temp_r28_4->fifo, temp_r28_4->start, temp_r28_4->end);
        GSgfxPerfbarCPUStart__Fv();
        break;
    }
    GSgfx_GCFifoObj *var_r31;
    if ((s32) gsgfx_gpu_mode == 2) {
        GSgfxLayerPrepareNextFrame__Fv();
        GSgfxLayerUpdateActiveFifoStats__Fv();
        var_r31 = GSgfxGPUGetImmediateFifo__Fv();
        GXSetCPUFifo(sdk(var_r31));
        GXGetFifoPtrs(sdk(var_r31), &sp8, &_renderPrepareFrameStart);
    }
    GSgfxVideoSetupNextFrame__Fv();
    if ((s32) gsgfx_gpu_mode == 2) {
        GXSaveCPUFifo(sdk(var_r31));
        GXGetFifoPtrs(sdk(var_r31), &sp8, &_renderPrepareFrameEnd);
        GXSetCPUFifo((GXFifoObj*)((u8*)gsgfx_layer_activeFifo+8));
    }
    GSgfxTokenMarkFrame__Fv();
    if ((u32) _renderPauseCount != 0U) {
        var_f31 = 0.0f;
    }
    GSgfxRenderModuleDoPostUpdate__Ff(var_f31);
}

u8 GSgfxRenderIsPaused(void) {
    return _renderPauseCount != 0U;
}

void GSgfxRenderUnpause(void) {
    if ((u32) _renderPauseCount != 0U) {
        _renderPauseCount -= 1;
    }
}

void GSgfxRenderPause(void) {
    _renderPauseCount += 1;
}

void GSgfxRenderSetupFirstFrame__Fv(void) {
    void *sp8;
    GSgfx_GCFifoObj *var_r31;


    if ((s32) gsgfx_gpu_mode == 2) {
        GSgfxLayerPrepareNextFrame__Fv();
        GSgfxLayerUpdateActiveFifoStats__Fv();
        var_r31 = GSgfxGPUGetImmediateFifo__Fv();
        GXSetCPUFifo(sdk(var_r31));
        GXGetFifoPtrs(sdk(var_r31), &sp8, &_renderPrepareFrameStart);
    }
    GSgfxVideoSetupNextFrame__Fv();
    if ((s32) gsgfx_gpu_mode == 2) {
        GXSaveCPUFifo(sdk(var_r31));
        GXGetFifoPtrs(sdk(var_r31), &sp8, &_renderPrepareFrameEnd);
        GXSetCPUFifo((GXFifoObj*)((u8*)gsgfx_layer_activeFifo+8));
    }
    GSgfxTokenMarkFrame__Fv();
}

void GSgfxRenderAddToFifoList__FP15GSgfx_GCFifoObjPvPvUlPFPv_vPv(GSgfx_GCFifoObj *fifo,void *start,void *end,u32 color,void(*cb)(void*),void *arg) {
    if(start!=end) { fifo->complete=0; gsgfxState->list->fifo=fifo; gsgfxState->list->start=start; gsgfxState->list->end=end; gsgfxState->list->color=color; gsgfxState->list->callback=cb; gsgfxState->list->arg=arg; ++gsgfxState->list; gsgfxState->list->fifo=0; }
}

void GSgfxRenderWaitForDrawComplete__Fv() { waitComplete(); }

void GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(GSgfxRenderWaitData *arg0) {
    GSgfxPerfbarCPUEntry(arg0->perf);
}

void GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(GSgfxRenderWaitData *arg0) {
    s32 temp_r0;
    s32 temp_r31;
    u32 temp_r3;
    void *temp_r3_2;

    OSYieldThread();
    if (GSgfxGPUIsIdle__Fv() != 1) {
        temp_r31 = GSgfxVideoGetVsyncCount();
        temp_r3 = GSgfxVideoGetVsyncRate() * 3;
        temp_r0 = temp_r31 - arg0->vsync;
        if (temp_r0 < 0) {
            arg0->vsync = temp_r31;
            return;
        }
        if ((u32) temp_r0 > temp_r3) {
            gsgfx_layer_inPrimitive = 0;
            GSgfxVideoSetOneShotPostCallback__FPFPv_v(0);
            GXAbortFrame();
            GSgfxTokenAbortFrame__Fv();
            temp_r3_2 = gsgfxState->xfb;
            if ((temp_r3_2 != 0) && (temp_r3_2 != (void*)0xfefefefe)) {
                GSgfxVideoSetXFBReady__FPv((void*)temp_r3_2);
            }
            gsgfxState->copyState = 0;
            gsgfxState->xfb = 0;
            GSgfxLayerInvalidateAll__Fv();
            _renderResetGX__Fv();
        }
    }
}

void GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(GSgfxRenderWaitData *arg0) {
    arg0->perf = GSgfxPerfbarCPUEntry(0xFFFF00);
    arg0->vsync = GSgfxVideoGetVsyncCount();
}

void GSgfxRenderAbortFrame__Fv(void) {
    void *temp_r3;

    gsgfx_layer_inPrimitive = 0;
    GSgfxVideoSetOneShotPostCallback__FPFPv_v(0);
    GXAbortFrame();
    GSgfxTokenAbortFrame__Fv();
    temp_r3 = gsgfxState->xfb;
    if ((temp_r3 != 0) && (temp_r3 != (void*)0xfefefefe)) {
        GSgfxVideoSetXFBReady__FPv((void*)temp_r3);
    }
    gsgfxState->copyState = 0;
    gsgfxState->xfb = 0;
    GSgfxLayerInvalidateAll__Fv();
    _renderResetGX__Fv();
}

void GSgfxRenderInit__Fv(void) {
    gsgfxState->xfb = 0;
    gsgfxState->copyState = 0;
    GSgfxGPUInitFifoBase__FP15GSgfx_GCFifoObjPvUl(&_renderXFBCommandFifo, _renderXFBCommandBuf, 0x10000);
    GXInitFifoPtrs(sdk(&_renderXFBCommandFifo), &_renderXFBCommandBuf, &_renderXFBCommandBuf);
    GSgfxGPUSetDrawDoneCallback__FPFv_v(_renderDrawDoneCallback__Fv);
    GSgfxGPUSetBreakpointCallback__FPFv_v(_renderBreakpointCallback__Fv);
    GXLoadPosMtxImm(mtxIdent, 0);
    GXSetCurrentMtx(0);
    GSgfx_GCReset();
    GSgfxRenderModuleInit__Fv();
}

static void _renderResetGX__Fv(void) {
    Mtx sp10;
    GXColor spC={0,0,0,0};
    s32 var_r31;
    s32 var_r31_2;

    PSMTXIdentity(sp10);
    GXSetTexCoordGen2((GXTexCoordID)0,(GXTexGenType)1,(GXTexGenSrc)4, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)1,(GXTexGenType)1,(GXTexGenSrc)5, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)2,(GXTexGenType)1,(GXTexGenSrc)6, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)3,(GXTexGenType)1,(GXTexGenSrc)7, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)4,(GXTexGenType)1,(GXTexGenSrc)8, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)5,(GXTexGenType)1,(GXTexGenSrc)9, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)6,(GXTexGenType)1,(GXTexGenSrc)0xA, 0x3C, 0, 0x7D);
    GXSetTexCoordGen2((GXTexCoordID)7,(GXTexGenType)1,(GXTexGenSrc)0xB, 0x3C, 0, 0x7D);
    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6,(GXTexOffset)0);
    GXSetPointSize(6,(GXTexOffset)0);
    GXEnableTexOffsets((GXTexCoordID)0, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)1, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)2, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)3, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)4, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)5, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)6, 0, 0);
    GXEnableTexOffsets((GXTexCoordID)7, 0, 0);
    GXLoadPosMtxImm(sp10, 0);
    GXLoadNrmMtxImm(sp10, 0);
    GXSetCurrentMtx(0);
    GXLoadTexMtxImm(sp10, 0x3C,(GXTexMtxType)0);
    GXLoadTexMtxImm(sp10, 0x7D,(GXTexMtxType)0);
    GXSetCoPlanar(0);
    GXSetCullMode((GXCullMode)2);
    GXSetClipMode((GXClipMode)0);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);
    GXSetChanCtrl((GXChannelID)4, 0,(GXColorSrc)0,(GXColorSrc)1, 0,(GXDiffuseFn)0,(GXAttnFn)2);
    GXSetChanCtrl((GXChannelID)5, 0,(GXColorSrc)0,(GXColorSrc)1, 0,(GXDiffuseFn)0,(GXAttnFn)2);
    GXInvalidateTexAll();
    GXSetTevOrder((GXTevStageID)0,(GXTexCoordID)0,(GXTexMapID)0,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)1,(GXTexCoordID)1,(GXTexMapID)1,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)2,(GXTexCoordID)2,(GXTexMapID)2,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)3,(GXTexCoordID)3,(GXTexMapID)3,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)4,(GXTexCoordID)4,(GXTexMapID)4,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)5,(GXTexCoordID)5,(GXTexMapID)5,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)6,(GXTexCoordID)6,(GXTexMapID)6,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)7,(GXTexCoordID)7,(GXTexMapID)7,(GXChannelID)4);
    GXSetTevOrder((GXTevStageID)8,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)9,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xA,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xB,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xC,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xD,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xE,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetTevOrder((GXTevStageID)0xF,(GXTexCoordID)0xFF,(GXTexMapID)0xFF,(GXChannelID)0xFF);
    GXSetNumTevStages(1);
    GXSetTevOp((GXTevStageID)0,(GXTevMode)3);
    GXSetAlphaCompare((GXCompare)7, 0,(GXAlphaOp)0,(GXCompare)7, 0);
    GXSetZTexture((GXZTexOp)0,(GXTexFmt)0x11, 0);
    var_r31 = 0;
    do {
        GXSetTevKColorSel((GXTevStageID)var_r31,(GXTevKColorSel)6);
        GXSetTevKAlphaSel((GXTevStageID)var_r31,(GXTevKAlphaSel)0);
        GXSetTevSwapMode((GXTevStageID)var_r31,(GXTevSwapSel)0,(GXTevSwapSel)0);
        var_r31 += 1;
    } while (var_r31 < 0x10);
    GXSetTevSwapModeTable((GXTevSwapSel)0,(GXTevColorChan)0,(GXTevColorChan)1,(GXTevColorChan)2,(GXTevColorChan)3);
    GXSetTevSwapModeTable((GXTevSwapSel)1,(GXTevColorChan)0,(GXTevColorChan)0,(GXTevColorChan)0,(GXTevColorChan)3);
    GXSetTevSwapModeTable((GXTevSwapSel)2,(GXTevColorChan)1,(GXTevColorChan)1,(GXTevColorChan)1,(GXTevColorChan)3);
    GXSetTevSwapModeTable((GXTevSwapSel)3,(GXTevColorChan)2,(GXTevColorChan)2,(GXTevColorChan)2,(GXTevColorChan)3);
    var_r31_2 = 0;
    do {
        GXSetTevDirect((GXTevStageID)var_r31_2);
        var_r31_2 += 1;
    } while (var_r31_2 < 0x10);
    GXSetNumIndStages(0);
    GXSetIndTexCoordScale((GXIndTexStageID)0,(GXIndTexScale)0,(GXIndTexScale)0);
    GXSetIndTexCoordScale((GXIndTexStageID)1,(GXIndTexScale)0,(GXIndTexScale)0);
    GXSetIndTexCoordScale((GXIndTexStageID)2,(GXIndTexScale)0,(GXIndTexScale)0);
    GXSetIndTexCoordScale((GXIndTexStageID)3,(GXIndTexScale)0,(GXIndTexScale)0);
    GXSetFog((GXFogType)0,0.0f,1.0f,0.1f,1.0f,spC);
    GXSetFogRangeAdj(0, 0, 0);
    GXSetBlendMode((GXBlendMode)0,(GXBlendFactor)4,(GXBlendFactor)5,(GXLogicOp)0);
    GXSetColorUpdate(1);
    GXSetAlphaUpdate(1);
    GXSetZMode(1,(GXCompare)3, 1);
    GXSetZCompLoc(1);
    GXSetDither(1);
    GXSetDstAlpha(0, 0);
    GXSetPixelFmt((GXPixelFmt)0,(GXZFmt16)0);
    GXSetFieldMask(1, 1);
    GXPokeColorUpdate(1);
    GXPokeAlphaUpdate(1);
    GXPokeDither(0);
    GXPokeBlendMode((GXBlendMode)0,(GXBlendFactor)0,(GXBlendFactor)1,(GXLogicOp)0xF);
    GXPokeAlphaMode((GXCompare)7, 0);
    GXPokeAlphaRead((GXAlphaReadMode)1);
    GXPokeDstAlpha(0, 0);
    GXPokeZMode(1,(GXCompare)7, 1);
    GXSetGPMetric((GXPerf0)0x23,(GXPerf1)0x16);
    GXClearGPMetric();
}

static void _renderBreakpointCallback__Fv(void) {
    s32 temp_r0;
    s32 temp_r31;
    void *temp_r3;
    void *temp_r3_2;
    RenderEntry *temp_r30;
    RenderEntry *temp_r30_2;

    temp_r0 = gsgfxState->copyState;
    switch (temp_r0) {                              /* irregular */
    case 0:
        temp_r30 = gsgfxState->list;
        if (temp_r30->callback != 0) {
            temp_r31 = OSEnableInterrupts();
            temp_r30->callback(temp_r30->arg);
            OSRestoreInterrupts(temp_r31);
        }
        ++gsgfxState->list;
        temp_r30_2 = gsgfxState->list;
        if (temp_r30_2->fifo != 0) {
            GSgfxPerfbarGPUEntry__FUl(temp_r30_2->color);
            GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(temp_r30_2->fifo, temp_r30_2->start, temp_r30_2->end);
            return;
        }
        GSgfxPerfbarGPUEnd__Fv();
        temp_r3 = GSgfxVideoFindFreeXFB__Fb(0);
        if (temp_r3 == 0) {
            GSgfxVideoSetOneShotPostCallback__FPFPv_v(_renderCopyEFB__FPv);
            return;
        }
        gsgfxState->xfb = (void*)temp_r3;
        gsgfxState->copyState = 1;
        GSgfxVideoBuildEFB2XFBCopy__FPvPv(_renderXFBCommandBuf,gsgfxState->xfb);
        if (GSgfxTokenCleared(_renderXFBCopyToken) == 0) {
            GSgfxVideoGetVsyncCount();
            do {

            } while (GSgfxTokenCleared(_renderXFBCopyToken) == 0);
        }
        GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(&_renderXFBCommandFifo, &_renderXFBCommandBuf, _renderXFBCommandBuf + 0x60);
        return;
    case 1:
        temp_r3_2 = gsgfxState->xfb;
        _renderLastXFBPtr = temp_r3_2;
        GSgfxVideoSetXFBReady__FPv(temp_r3_2);
        gsgfxState->copyState = 0;
        gsgfxState->xfb = 0;
        return;
    }
}

static void _renderCopyEFB__FPv(void *arg0) {
    gsgfxState->xfb = arg0;
    gsgfxState->copyState = 1;
    GSgfxVideoBuildEFB2XFBCopy__FPvPv(_renderXFBCommandBuf,gsgfxState->xfb);
    if (GSgfxTokenCleared(_renderXFBCopyToken) == 0) {
        GSgfxVideoGetVsyncCount();
        do {

        } while (GSgfxTokenCleared(_renderXFBCopyToken) == 0);
    }
    GSgfxGPUProcessBlock__FP15GSgfx_GCFifoObjPvPv(&_renderXFBCommandFifo, &_renderXFBCommandBuf, _renderXFBCommandBuf + 0x60);
}

static void _renderDrawDoneCallback__Fv(void) {
    void *temp_r3;

    if (GSgfxVideoGetXFBCount() != 1) {
        temp_r3 = gsgfxState->xfb;
        _renderLastXFBPtr = temp_r3;
        GSgfxVideoSetXFBReady__FPv(temp_r3);
        gsgfxState->xfb = 0;
    }
}

}
