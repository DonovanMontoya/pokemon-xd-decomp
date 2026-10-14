#include "layer_private.h"
static const u32 defaultColor=0x80808080;
extern "C" {
u8 GSgfxRenderModuleIsRendering__Fv();
u8 GSgfxVFGetColorCount(void*); u8 GSgfxVFGetTextureCount(void*); u8 GSgfxVFHasElement(void*,s32);
void SetupRenderState__10GSgfxLayerFv(void*); void SetupGPUState__10GSgfxLayerFv(void*);
void GSgfxLayerUpdateActiveFifoStats__Fv();
void setRenderState__10GSgfxLayerFP7GSgfxVF(void*,void*);
void setRenderState__10GSgfxLayerFbUcb(void*,u8,u8,u8);
void renderState_NL_NVC_NT__10GSgfxLayerFv(void*);
void renderState_NL_NVC_T__10GSgfxLayerFUc(void*,u8);
void renderState_NL_VC_T__10GSgfxLayerFUc(void*,u8);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(void*,u8,s32,s32,void*,bool,void*);
void tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(void*,u8,u32);
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(void*,u8,s32,s32,s32,u32,void**,s32,s32);
void FlushState__10GSgfxLayerFv(void *arg0) {
    SetupFifo__10GSgfxLayerFv(arg0);
    SetupRenderState__10GSgfxLayerFv(arg0);
    GSgfxLayerUpdateActiveFifoStats__Fv();
}

void InvalidateState__10GSgfxLayerFv(void *arg0) {
    if (GSgfxRenderModuleIsRendering__Fv() == 1) {
        GXFlush();
    }
    memset(static_cast<u8*>(arg0) + 0x16A8, 0, 0xB8);
    memset(static_cast<u8*>(arg0) + 0x1760, 0, 0xB8);
    layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x80000000);
}

void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void *arg0, void* arg1) {
    setRenderState__10GSgfxLayerFP7GSgfxVF(arg0, arg1);
    layerField<void*>(arg0, 0x199C) = arg1;
}

void setRenderState__10GSgfxLayerFP7GSgfxVF(void *arg0, void *arg1) {
    u8 temp_r30;
    u8 temp_r31;
    u8 var_r29;

    temp_r31 = GSgfxVFGetColorCount(arg1);
    temp_r30 = GSgfxVFGetTextureCount(arg1);
    var_r29 = 0;
    if ((GSgfxVFHasElement(arg1, 0xA) != 0) || (GSgfxVFHasElement(arg1, 0x19) != 0)) {
        var_r29 = 1;
    }
    if (temp_r31 == 0) {
        setRenderState__10GSgfxLayerFbUcb(arg0, 0U, temp_r30, var_r29);
        return;
    }
    setRenderState__10GSgfxLayerFbUcb(arg0, 1U, temp_r30, var_r29);
}

void setRenderState__10GSgfxLayerFbUcb(void *arg0, u8 arg1, u8 arg2, u8 arg3) {
    s32 sp8;

    if (arg3 == 0) {
        if (arg1 == 0) {
            if (arg2 == 0) {
                renderState_NL_NVC_NT__10GSgfxLayerFv(arg0);
                return;
            }
            renderState_NL_NVC_T__10GSgfxLayerFUc(arg0,arg2);
            return;
        }
        if (arg2 == 0) {
            layerField<u8>(arg0, 0xDB8) = 1;
            layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
            layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
            layerField<u8>(arg0, 0xC70) = 0;
            layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
            layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
            layerField<u8>(arg0, 0xEAC) = 1;
            layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
            layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
            layerField<u8>(arg0, 0x14B0) = 0;
            layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
            layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
            sp8 = 0;
            cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,1,0,0,2,0);
            layerField<u32>(arg0, 0xEB0) = 0xFF;
            layerField<u32>(arg0, 0xEB4) = 0xFF;
            layerField<u32>(arg0, 0xEB8) = 4;
            layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
            layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, 0U, 4);
            layerField<u32>(arg0, 0x1584) = 0;
            layerField<u32>(arg0, 0x1588) = 0;
            layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | 1);
            layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
            layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | 1);
            layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
            return;
        }
        renderState_NL_VC_T__10GSgfxLayerFUc(arg0,arg2);
    }
}

void ResetVertexFormat__10GSgfxLayerFP7GSgfxVF(void *arg0, u32 arg1) {
    s32 var_ctr;
    u8 *temp_r5;
    u8 *var_r6;

    var_r6 = static_cast<u8*>(arg0) + 0x16A8;
    if (arg1 == (u32) layerField<u32>(arg0, 0x199C)) {
        layerField<u32>(arg0, 0x199C) = 0U;
    }
    var_ctr = 2;
    do {
        if ((u32) layerField<u32>(var_r6, 0x88) == arg1) {
            layerField<u32>(var_r6, 0x88) = 0U;
        }
        if ((u32) layerField<u32>(var_r6, 0x68) == arg1) {
            layerField<u32>(var_r6, 0x68) = 0U;
        }
        if ((u32) layerField<u32>(var_r6, 0x6C) == arg1) {
            layerField<u32>(var_r6, 0x6C) = 0U;
        }
        temp_r5 = var_r6 + 8;
        if ((u32) layerField<u32>(var_r6, 0x70) == arg1) {
            layerField<u32>(temp_r5, 0x68) = 0;
        }
        if ((u32) layerField<u32>(temp_r5, 0x6C) == arg1) {
            layerField<u32>(temp_r5, 0x6C) = 0U;
        }
        if ((u32) layerField<u32>(temp_r5, 0x70) == arg1) {
            layerField<u32>(temp_r5, 0x70) = 0U;
        }
        if ((u32) layerField<u32>(temp_r5, 0x74) == arg1) {
            layerField<u32>(temp_r5, 0x74) = 0U;
        }
        if ((u32) layerField<u32>(temp_r5, 0x78) == arg1) {
            layerField<u32>(temp_r5, 0x78) = 0U;
        }
        if ((u32) layerField<u32>(temp_r5, 0x7C) == arg1) {
            layerField<u32>(temp_r5, 0x7C) = 0U;
        }
        var_r6 += 0xB8;
        var_ctr -= 1;
    } while (var_ctr != 0);
}

void renderState_NL_VC_T__10GSgfxLayerFUc(void *arg0, u8 arg1) {
    s32 sp8;
    s32 temp_r31;
    u8 var_r29;
    u8 var_r30;
    u8 *temp_r4;
    u8 *temp_r5;

    layerField<u8>(arg0, 0xDB8) = 1;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = arg1;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = arg1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
    sp8 = 0;
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,1,0,0,2,0);
    var_r30 = 0;
loop_2:
    if (var_r30 < arg1) {
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg0, var_r30, 1, var_r30 + 4, 0, 0, 0);
        var_r30 += 1;
        goto loop_2;
    }
    var_r29 = 0;
loop_8:
    if (var_r29 < arg1) {
        temp_r31 = 1 << var_r29;
        layerField<s32>(arg0,var_r29*0x24+0x1420) = 0;
        temp_r5 = static_cast<u8*>(arg0) + (var_r29 * 0xC);
        layerField<u32>(arg0, 0x16E8) = (s32) (layerField<u32>(arg0, 0x16E8) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x17A0) = (s32) (layerField<u32>(arg0, 0x17A0) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        layerField<u32>(temp_r5, 0xEB0) = (s32) var_r29;
        layerField<u32>(temp_r5, 0xEB4) = (s32) var_r29;
        layerField<u32>(temp_r5, 0xEB8) = 4;
        layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        if (var_r29 == 0) {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29, 0);
        } else {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29, 7);
        }
        temp_r4 = static_cast<u8*>(arg0) + (var_r29 * 8);
        var_r29 += 1;
        layerField<u32>(temp_r4, 0x1584) = 0;
        layerField<u32>(temp_r4, 0x1588) = 0;
        layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
        layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
        goto loop_8;
    }
}

void renderState_NL_NVC_T__10GSgfxLayerFUc(void *arg0, u8 arg1) {
    s32 temp_r31;
    u8 var_r29;
    u8 var_r29_2;
    u8 *temp_r4;
    u8 *temp_r5;

    var_r29 = 0;
    layerField<u8>(arg0, 0xDB8) = 0;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = arg1;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = arg1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
loop_2:
    if (var_r29 < arg1) {
        tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(arg0, var_r29, 1, var_r29 + 4, 0, 0, 0);
        var_r29 += 1;
        goto loop_2;
    }
    var_r29_2 = 0;
loop_8:
    if (var_r29_2 < arg1) {
        temp_r31 = 1 << var_r29_2;
        layerField<s32>(arg0,var_r29_2*0x24+0x1420) = 0;
        temp_r5 = static_cast<u8*>(arg0) + (var_r29_2 * 0xC);
        layerField<u32>(arg0, 0x16E8) = (s32) (layerField<u32>(arg0, 0x16E8) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x17A0) = (s32) (layerField<u32>(arg0, 0x17A0) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        layerField<u32>(temp_r5, 0xEB0) = (s32) var_r29_2;
        layerField<u32>(temp_r5, 0xEB4) = (s32) var_r29_2;
        layerField<u32>(temp_r5, 0xEB8) = 0xFF;
        layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
        layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
        if (var_r29_2 == 0) {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29_2, 3);
        } else {
            tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, var_r29_2, 5);
        }
        temp_r4 = static_cast<u8*>(arg0) + (var_r29_2 * 8);
        var_r29_2 += 1;
        layerField<u32>(temp_r4, 0x1584) = 0;
        layerField<u32>(temp_r4, 0x1588) = 0;
        layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | temp_r31);
        layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
        layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | temp_r31);
        layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
        goto loop_8;
    }
}

void renderState_NL_NVC_NT__10GSgfxLayerFv(void *arg0) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 sp8;

    layerField<u8>(arg0, 0xDB8) = 1;
    sp18 = defaultColor;
    layerField<u32>(arg0, 0x16BC) = (s32) (layerField<u32>(arg0, 0x16BC) | 1);
    sp10 = defaultColor;
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    sp14 = defaultColor;
    layerField<u32>(arg0, 0x1774) = (s32) (layerField<u32>(arg0, 0x1774) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    layerField<u8>(arg0, 0xC70) = 0;
    layerField<u32>(arg0, 0x16AC) = (s32) (layerField<u32>(arg0, 0x16AC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 1);
    layerField<u32>(arg0, 0x1764) = (s32) (layerField<u32>(arg0, 0x1764) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 1);
    layerField<u8>(arg0, 0xEAC) = 1;
    layerField<u32>(arg0, 0x16CC) = (s32) (layerField<u32>(arg0, 0x16CC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1784) = (s32) (layerField<u32>(arg0, 0x1784) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    layerField<u8>(arg0, 0x14B0) = 0;
    layerField<u32>(arg0, 0x16EC) = (s32) (layerField<u32>(arg0, 0x16EC) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x80);
    layerField<u32>(arg0, 0x17A4) = (s32) (layerField<u32>(arg0, 0x17A4) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x80);
    layerField<u32>(arg0, 0xE9C) = (s32) defaultColor;
    layerField<u32>(arg0, 0xEA4) = (s32) defaultColor;
    layerField<u32>(arg0, 0x16C4) = (s32) (layerField<u32>(arg0, 0x16C4) | 1);
    layerField<u32>(arg0, 0x16C8) = (s32) (layerField<u32>(arg0, 0x16C8) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 4);
    layerField<u32>(arg0, 0x177C) = (s32) (layerField<u32>(arg0, 0x177C) | 1);
    layerField<u32>(arg0, 0x1780) = (s32) (layerField<u32>(arg0, 0x1780) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 4);
    sp8 = 0;
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(arg0,0,2,0,0,0,0,2,0);
    layerField<u32>(arg0, 0xEB0) = 0xFF;
    layerField<u32>(arg0, 0xEB4) = 0xFF;
    layerField<u32>(arg0, 0xEB8) = 4;
    layerField<u32>(arg0, 0x16D0) = (s32) (layerField<u32>(arg0, 0x16D0) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 8);
    layerField<u32>(arg0, 0x1788) = (s32) (layerField<u32>(arg0, 0x1788) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 8);
    tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(arg0, 0U, 4);
    layerField<u32>(arg0, 0x1584) = 0;
    layerField<u32>(arg0, 0x1588) = 0;
    layerField<u32>(arg0, 0x1704) = (s32) (layerField<u32>(arg0, 0x1704) | 1);
    layerField<u32>(arg0, 0x16A8) = (s32) (layerField<u32>(arg0, 0x16A8) | 0x20);
    layerField<u32>(arg0, 0x17BC) = (s32) (layerField<u32>(arg0, 0x17BC) | 1);
    layerField<u32>(arg0, 0x1760) = (s32) (layerField<u32>(arg0, 0x1760) | 0x20);
}

}

extern "C" {
void* _layerStateLastHWState;
s32 _foo;
void GSgfx_GCInvalidateState();
void PPCSync();
void Load__10GSgfxLightFUc(void*,u8);
void GSgfx_GCWriteLoadTlut(void*,s32); void GSgfx_GCWriteLoadTexObj(void*,s32);
void GSgfx_GCWriteVtxDesc(void*); void GSgfx_GCWriteVtxAttrFmt(s32,void*);
void GSgfx_GCWriteArray(s32,void*,u8);
void LoadHWState__10GSgfxLayerFv(void* layer) {
    u8* hardware=static_cast<u8*>(layer)+0x30;
    if (_layerStateLastHWState!=hardware) {
        if (_layerStateLastHWState) memcpy(_layerStateLastHWState,gsgfxState,0xc40);
        memcpy(gsgfxState,hardware,0xc40); _layerStateLastHWState=hardware;
    }
}
}
struct LayerArray { u16 flags; u8 stride,padding; s32 attribute; void* data; u32 size; };
ABI_SIZE(LayerArray,0x10);
static void loadLayerMatrix(void* layer,u8* dirty) {
    GSgfxMatrixStack* stack=layerField<GSgfxMatrixStack*>(layer,0x19a0);
    GSgfxMatrixStack::Entry* entry=stack->current;
    if ((entry->flags&1) || entry!=layerField<GSgfxMatrixStack::Entry*>(dirty,0x8c)) {
        GXLoadPosMtxImm(entry->matrix,0x1b);
        if (stack->current->flags&1) {
            PSMTXInvXpose(stack->current->matrix,stack->current->inverse);
            stack->current->flags&=~1;
        }
        GXLoadNrmMtxImm(stack->current->inverse,0x1b);
        layerField<GSgfxMatrixStack::Entry*>(dirty,0x8c)=stack->current;
    }
    if (layerField<u8>(dirty,0x90)==0) {
        layerField<u8>(gsgfxState,0x1f3)=(layerField<u8>(gsgfxState,0x1f3)&~0x3f)|0x1b;
        gsgfxState->dirty|=0x40; layerField<u8>(dirty,0x90)=1;
    }
}
extern "C" void SetupRenderState__10GSgfxLayerFv(void* layer) {
    LoadHWState__10GSgfxLayerFv(layer);
    u32& flags=layerField<u32>(layer,4);
    if (flags&0x80000000) { GSgfx_GCInvalidateState(); flags&=~0x80000000; }
    if (flags&0x20000000) { gsgfxState->dirty|=0x10; flags&=~0x20000000; }
    if (flags&0x08000000) { *(volatile u8*)0xcc008000=0x48; flags&=~0x08000000; }
    if (flags&0x10000000) {
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=0x0f;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=0x66001000;
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=0x66001100;
        gsgfxState->dirty|=0x800; flags&=~0x10000000;
    }
    if (flags&0x40000000) {
        *(volatile u8*)0xcc008000=0x61; *(volatile u32*)0xcc008000=0x63000000;
        flags&=~0x40000000;
    }
    u8* state=static_cast<u8*>(layer)+0xc70;
    u8* dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
    if ((layerField<u32>(dirty,0)&4) && (layerField<u32>(dirty,0x14)&0x10)) {
        u8 count=layerField<u8>(state,0x124);
        for (u8 i=0;i<count;i++) Load__10GSgfxLightFUc(layerField<void*>(state,0x128+i*4),i);
        layerField<u32>(dirty,0x14)&=~0x10;
    }
    SetupGPUState__10GSgfxLayerFv(layer);
    dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
    if (layerField<u32>(dirty,0x94) && layerField<u8>(layer,0xc70)) {
        for (s32 i=0;i<8;i++) if (layerField<u32>(dirty,0x94)&(1<<i)) {
            u8* tex=layerField<u8*>(dirty,0x98+i*4);
            if (!layerField<u16>(tex,0) || !layerField<u16>(tex,2)) ++_foo;
            if (layerField<void*>(tex,0x48)) {
                GXInitTexObjTlut(reinterpret_cast<GXTexObj*>(tex+0x54),i);
                GSgfx_GCWriteLoadTlut(tex+0x74,i);
            }
            GSgfx_GCWriteLoadTexObj(tex+0x54,i); layerField<u8>(tex,7)=0;
        }
        layerField<u32>(dirty,0x94)=0;
    }
    u8* format=layerField<u8*>(layer,0x199c);
    if (format) {
        dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
        if (layerField<void*>(dirty,0x88)!=format || (layerField<u16>(format,0)&4)) {
            GSgfx_GCWriteVtxDesc(format+0x1b8);
            for (LayerArray* a=reinterpret_cast<LayerArray*>(format+0x290);a->attribute!=255;a++)
                GSgfx_GCWriteArray(a->attribute,a->data,a->stride);
            layerField<void*>(dirty,0x88)=format;
        }
        u32 index=layerField<u32>(format,4);
        if (layerField<void*>(dirty,0x68+index*4)!=format || (layerField<u16>(format,0)&2)) {
            GSgfx_GCWriteVtxAttrFmt(index,format+8); layerField<void*>(dirty,0x68+index*4)=format;
        }
        u8 sync=0;
        for (LayerArray* a=reinterpret_cast<LayerArray*>(format+0x290);a->attribute!=255;a++) if (a->flags&1) {
            DCStoreRangeNoSync(a->data,a->size); sync=1; a->flags&=~1;
        }
        if (sync==1) PPCSync();
        if (layerField<u16>(format,0)&8) *(volatile u8*)0xcc008000=0x48;
        layerField<u16>(format,0)&=~6;
        if (GSgfxVFHasElement(layerField<void*>(layer,0x199c),0)==0) {
            dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
            loadLayerMatrix(layer,dirty);
        }
    } else {
        dirty=static_cast<u8*>(layer)+layerField<s32>(layer,0x1994)*0xb8+0x16a8;
        loadLayerMatrix(layer,dirty);
    }
    GSgfx_GCFlushState();
}

#define LAYER_STATE_FIELD(type, base, offset) (*reinterpret_cast<type*>(reinterpret_cast<u8*>(base) + (offset)))
struct LayerBlendCache { u8 reserved[0xBB4]; s32 mode; s32 source; s32 destination; s32 operation; };
struct LayerSwapTableCache { u8 reserved[0xB24]; s32 red; s32 green; s32 blue; s32 alpha; };
struct LayerIndScaleCache { u8 reserved[0xB94]; s32 s; s32 t; };
struct LayerIndOrderCache { u8 reserved[0xB74]; s32 coordinate; s32 map; };
struct LayerTevAlphaInputCache { u8 reserved[0x690]; s32 a; s32 b; s32 c; s32 d; };
struct LayerTevColorInputCache { u8 reserved[0x590]; s32 a; s32 b; s32 c; s32 d; };
struct LayerTevAlphaOperationCache { u8 reserved[0x8D0]; s32 operation; s32 bias; s32 scale; u8 clamp; u8 padding[3]; s32 output; };
struct LayerTevColorOperationCache { u8 reserved[0x790]; s32 operation; s32 bias; s32 scale; u8 clamp; u8 padding[3]; s32 output; };
struct LayerTevOrderCache { u8 reserved[0x4CC]; s32 coordinate; s32 map; s32 color; };
struct LayerScissorCache { u8 reserved[0x444]; u16 x; u16 y; u16 width; u16 height; s32 offsetX; s32 offsetY; };
struct LayerAlphaCompareCache { u8 reserved[0xbc8]; s32 compare0,operation,compare1; u8 reference0,reference1; };
ABI_OFF(LayerAlphaCompareCache,reference0,0xbd4);
// Cached hardware setters recovered from layerState's weak assembly bodies.
extern "C" {
static const u8 layerTevColorChannel[16]={0,1,0,1,0,1,7,5,6,0,0,0,0,0,0,7};
static const u8 layerCullMode[4]={0,2,1,3};
void GSgfx_GCWriteTexCoordGen(s32,s32,s32,u32,u8,u32);
void GSgfx_GCWriteFog(s32,float,float,float,float);
void GSgfx_GCWriteTevIndBumpST(s32,u8,s32);
void GSgfx_GCWriteTevIndTile(s32,u8,u16,u16,u16,u16,s32,s32,u8,u8);
void* GSgfxVideoGetViewport();
void GSgfxVideoSetViewport__Fffffb(float,float,float,float,bool);
__declspec(weak) void GSgfx_GCSetFogRangeAdj(u8 arg0, u16 arg1, u8 *arg2);
__declspec(weak) void GSgfx_GCSetAlphaCompare(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4);
__declspec(weak) void GSgfx_GCSetBlendMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
__declspec(weak) void GSgfx_GCSetTevSwapModeTable(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevKColor(s32 arg0, u32 *arg1);
__declspec(weak) void GSgfx_GCSetIndTexCoordScale(s32 arg0, s32 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetIndTexOrder(s32 arg0, s32 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetTevIndRepeat(s32 arg0);
__declspec(weak) void GSgfx_GCSetTevIndBumpXYZ(s32 arg0, u8 arg1, s32 arg2);
__declspec(weak) void GSgfx_GCSetTevIndWarp(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevIndirect(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg_sp8, s32 arg_spC);
__declspec(weak) void GSgfx_GCSetTevDirect(s32 arg0);
__declspec(weak) void GSgfx_GCSetTevAlphaOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetTevColorOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetTevAlphaIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevColorIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
__declspec(weak) void GSgfx_GCSetTevOrder(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
__declspec(weak) void GSgfx_GCSetMatColor(s32 arg0, u32 *arg1);
__declspec(weak) void GSgfx_GCSetAmbColor(s32 arg0, u32 *arg1);
__declspec(weak) void GSgfx_GCSetChanCtrl(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
__declspec(weak) void GSgfx_GCSetScissor(u16 arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5);
__declspec(weak) void GSgfx_GCSetProjection(s32 arg0, u8 *arg1);

void SetupGPUState__10GSgfxLayerFv(void *arg0) {
    Mtx44 fogProjection;
    s32 sp38;
    s32 sp34;
    u32 sp30;
    u32 sp2C;
    u32 sp28;
    u32 sp24;
    u32 sp20;
    s32 sp1C;
    u32 sp18;
    u32 sp14;
    s32 spC;
    s32 sp8;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r11;
    s32 temp_r12_2;
    s32 temp_r12_3;
    s32 temp_r24_2;
    s32 temp_r25;
    s32 temp_r3_3;
    s32 temp_r4_3;
    s32 temp_r4_4;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 temp_r7_2;
    s32 temp_r7_3;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r8_3;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 var_ctr;
    s32 var_r24_2;
    s32 var_r25;
    s32 var_r26;
    s32 var_r26_10;
    s32 var_r26_11;
    s32 var_r26_2;
    s32 var_r26_3;
    s32 var_r26_4;
    s32 var_r26_5;
    s32 var_r26_6;
    s32 var_r26_7;
    s32 var_r26_8;
    s32 var_r26_9;
    s32 var_r27;
    s32 var_r28;
    s32 var_r28_2;
    s32 var_r29_3;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r5;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r6;
    s32 var_r6_3;
    s32 var_r7;
    u32 temp_r0;
    u32 temp_r0_4;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u8 temp_r0_5;
    u8 temp_r12;
    u8 temp_r24;
    u8 temp_r4;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_12;
    u8 temp_r4_13;
    u8 temp_r4_2;
    u8 temp_r4_5;
    u8 temp_r4_7;
    u8 temp_r4_8;
    u8 temp_r4_9;
    u8 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;
    u8 temp_r5_5;
    u8 var_r28_3;
    u8 var_r5_2;
    u8 **var_r6_2;
    u8 *temp_r30;
    u8 *temp_r31;
    u8 *temp_r3;
    u8 *temp_r3_2;
    u8 *temp_r3_6;
    u8 *temp_r4_6;
    u8 *temp_r7;
    u8 *temp_r7_4;
    u8 *var_r24;
    u8 *var_r25_10;
    u8 *var_r25_11;
    u8 *var_r25_12;
    u8 *var_r25_2;
    u8 *var_r25_3;
    u8 *var_r25_4;
    u8 *var_r25_5;
    u8 *var_r25_6;
    u8 *var_r25_7;
    u8 *var_r25_8;
    u8 *var_r25_9;
    u8 *var_r29;
    u8 *var_r29_2;
    u8 *var_r3;
    u8 *var_r3_2;
    u8 *var_r3_3;
    u8 *var_r3_4;
    u8 *var_r3_5;

    temp_r30 = static_cast<u8*>(arg0) + ((LAYER_STATE_FIELD(s32, arg0, 0x1994) * 0xB8) + 0x16A8);
    temp_r0 = LAYER_STATE_FIELD(s32, temp_r30, 0x0);
    if (temp_r0 != 0) {
        temp_r31 = static_cast<u8*>(arg0) + 0xC70;
        if (temp_r0 & 1) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 1) {
                temp_r4 = LAYER_STATE_FIELD(u8, arg0, 0xC70);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x3F8) != temp_r4) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x33) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x33) & ~0xF) | (temp_r4 & 0xF));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x02000000 | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x3F8) = temp_r4;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x8) != 0) {
                var_r29 = temp_r31;
                var_r28 = 0;
                var_r27 = 0;
loop_17:
                if (var_r28 < (s32) LAYER_STATE_FIELD(u8, arg0, 0xC70)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x8) & (1 << var_r28)) {
                        temp_r3 = LAYER_STATE_FIELD(u8*, var_r29, 0x18);
                        if (temp_r3 != NULL) {
                            LAYER_STATE_FIELD(s32, var_r29, 0x4) = (s32) (LAYER_STATE_FIELD(u8, temp_r3, 0x7C) + 2);
                        }
                        temp_r3_2 = reinterpret_cast<u8*>(gsgfxState) + var_r27;
                        if (((s32) LAYER_STATE_FIELD(s32, temp_r3_2, 0x358) != (s32) LAYER_STATE_FIELD(s32, var_r29, 0x4)) || ((s32) LAYER_STATE_FIELD(s32, temp_r3_2, 0x35C) != (s32) LAYER_STATE_FIELD(s32, var_r29, 0x8)) || ((u32) LAYER_STATE_FIELD(u32, temp_r3_2, 0x360) != (u32) LAYER_STATE_FIELD(u32, var_r29, 0xC)) || ((u8) LAYER_STATE_FIELD(u8, temp_r3_2, 0x364) != (u8) LAYER_STATE_FIELD(u8, var_r29, 0x10)) || ((u32) LAYER_STATE_FIELD(u32, temp_r3_2, 0x368) != (u32) LAYER_STATE_FIELD(u32, var_r29, 0x14))) {
                            GSgfx_GCWriteTexCoordGen(var_r28, LAYER_STATE_FIELD(s32, var_r29,4), LAYER_STATE_FIELD(s32, var_r29,8), LAYER_STATE_FIELD(u32, var_r29,12), LAYER_STATE_FIELD(u8, var_r29,16), LAYER_STATE_FIELD(u32, var_r29,20));
                        }
                    }
                    var_r29 += 0x18;
                    var_r28 += 1;
                    var_r27 += 0x14;
                    goto loop_17;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x8) = 0U;
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 4) && ((temp_r5 = LAYER_STATE_FIELD(u8, temp_r31, 0xC4), temp_r6 = LAYER_STATE_FIELD(s32, temp_r31, 0xC8), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x3FC) == temp_r5) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x400) != temp_r6))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1EF) = temp_r5;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) & ~7) | (temp_r6 & 7));
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x400);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3FC) = temp_r5;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x400) = temp_r6;
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 8) && ((temp_r5_2 = LAYER_STATE_FIELD(u8, temp_r31, 0xCC), temp_r6_2 = LAYER_STATE_FIELD(s32, temp_r31, 0xD0), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x404) == temp_r5_2) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x408) != temp_r6_2))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1EE) = temp_r5_2;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x1ED) & ~0x38) | ((temp_r6_2 << 3) & 0x38));
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x400);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x404) = temp_r5_2;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x408) = temp_r6_2;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0xC) != 0) {
                var_r3 = temp_r31;
                var_r4 = 0;
                var_r5 = 0;
                var_r6 = 0;
loop_34:
                if (var_r4 < (s32) LAYER_STATE_FIELD(u8, arg0, 0xC70)) {
                    if ((LAYER_STATE_FIELD(s32, temp_r30, 0xC) & (1 << var_r4)) && ((temp_r12 = LAYER_STATE_FIELD(u8, var_r3, 0xD4), temp_r7 = reinterpret_cast<u8*>(gsgfxState) + var_r6, temp_r24 = LAYER_STATE_FIELD(u8, var_r3, 0xD5), (((u8) LAYER_STATE_FIELD(u8, temp_r7, 0x40C) == temp_r12) == 0)) || ((u8) LAYER_STATE_FIELD(u8, temp_r7, 0x40D) != temp_r24))) {
                        temp_r11 = var_r5 + 0x1AD;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~4) | ((temp_r12 << 2) & 4);
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~8) | ((temp_r24 << 3) & 8);
                        LAYER_STATE_FIELD(s32, gsgfxState, 0xC) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0xC) | (1 << var_r4));
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + (var_r6 + 0x40C), 0) = temp_r12;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + (var_r6 + 0x40D), 0) = temp_r24;
                    }
                    var_r3 += 2;
                    var_r4 += 1;
                    var_r5 += 4;
                    var_r6 += 2;
                    goto loop_34;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0xC) = 0U;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x4) & 0x20) {
                GSgfx_GCSetProjection(LAYER_STATE_FIELD(s32, temp_r31, 0xE4), temp_r31 + 0xE8);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x4) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 2) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 8) {
                temp_r4_2 = LAYER_STATE_FIELD(u8, temp_r31, 0x118);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x438) != temp_r4_2) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x31) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x31) & ~8) | ((temp_r4_2 << 3) & 8));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x438) = temp_r4_2;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 2) {
                temp_r4_3 = LAYER_STATE_FIELD(s32, temp_r31, 0x11C);
                if ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x43C) != temp_r4_3) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x32) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x32) & ~0xC0) | ((*(layerCullMode + temp_r4_3) << 6) & 0xC0));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x43C) = temp_r4_3;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 4) {
                temp_r4_4 = LAYER_STATE_FIELD(s32, temp_r31, 0x120);
                if ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0x440) != temp_r4_4) {
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x54) = temp_r4_4;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x04000000);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x440) = temp_r4_4;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 1) {
                GSgfx_GCSetScissor(LAYER_STATE_FIELD(u16, temp_r31, 0x100), LAYER_STATE_FIELD(u16, temp_r31, 0x102), LAYER_STATE_FIELD(u16, temp_r31, 0x104), LAYER_STATE_FIELD(u16, temp_r31, 0x106), 0, 0);
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x10) & 0x10) {
                GSgfxVideoSetViewport__Fffffb( LAYER_STATE_FIELD(float, temp_r31, 0x108), LAYER_STATE_FIELD(float, temp_r31, 0x10C), LAYER_STATE_FIELD(float, temp_r31, 0x110), LAYER_STATE_FIELD(float, temp_r31, 0x114), false);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x10) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 4) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x14) & 1) {
                temp_r4_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x148);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x454) != temp_r4_5) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x33) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x33) & ~0x30) | ((temp_r4_5 << 4) & 0x30));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x01000000 | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x454) = temp_r4_5;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x18) != 0) {
                var_r25 = 0;
                var_r24 = temp_r31;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x18) & (1 << var_r25)) {
                        if ((u8) LAYER_STATE_FIELD(u8, var_r24, 0x14C) != 0) {
                            temp_r8 = LAYER_STATE_FIELD(s32, var_r24, 0x160);
                            var_r6_2 = reinterpret_cast<u8**>(var_r24 + 0x164);
                            var_r7 = 0;
loop_71:
                            temp_r4_6 = *var_r6_2;
                            if (temp_r4_6 != NULL) {
                                var_r5_2 = 0;
loop_69:
                                if (var_r5_2 < 8U) {
                                    temp_r0_2 = LAYER_STATE_FIELD(s32, temp_r4_6, 0x4);
                                    if ((temp_r8 == temp_r0_2) || ((temp_r8 == 2) && (temp_r0_2 == 1))) {
                                        var_r7 |= 1 << LAYER_STATE_FIELD(u8, temp_r4_6, 0x7C);
                                    }
                                    var_r5_2 += 1;
                                    goto loop_69;
                                }
                                ++var_r6_2;
                                goto loop_71;
                            }
                            LAYER_STATE_FIELD(s32, var_r24, 0x158) = var_r7;
                        } else {
                            LAYER_STATE_FIELD(s32, var_r24, 0x158) = 0;
                        }
                        GSgfx_GCSetChanCtrl(var_r25, LAYER_STATE_FIELD(u8, var_r24, 0x14C), LAYER_STATE_FIELD(s32, var_r24, 0x150), LAYER_STATE_FIELD(s32, var_r24, 0x154), LAYER_STATE_FIELD(s32, var_r24, 0x158), LAYER_STATE_FIELD(s32, var_r24, 0x15C), LAYER_STATE_FIELD(s32, var_r24, 0x160));
                    }
                    var_r25 += 1;
                    var_r24 += 0x38;
                } while (var_r25 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x18) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x1C) != 0) {
                var_r25_2 = temp_r31;
                var_r26 = 0;
loop_82:
                if (var_r26 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x148)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x1C) & (1 << var_r26)) {
                        sp30 = LAYER_STATE_FIELD(s32, var_r25_2, 0x22C);
                        GSgfx_GCSetAmbColor(var_r26 + 4, &sp30);
                    }
                    var_r25_2 += 4;
                    var_r26 += 1;
                    goto loop_82;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x1C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x20) != 0) {
                var_r25_3 = temp_r31;
                var_r26_2 = 0;
loop_89:
                if (var_r26_2 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x148)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x20) & (1 << var_r26_2)) {
                        sp2C = LAYER_STATE_FIELD(s32, var_r25_3, 0x234);
                        GSgfx_GCSetMatColor(var_r26_2 + 4, &sp2C);
                    }
                    var_r25_3 += 4;
                    var_r26_2 += 1;
                    goto loop_89;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x20) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x14) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 8) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x24) & 1) {
                temp_r4_7 = LAYER_STATE_FIELD(u8, temp_r31, 0x23C);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x58C) != temp_r4_7) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x32) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x32) & ~0x3C) | (((temp_r4_7 - 1) << 2) & 0x3C));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x58C) = temp_r4_7;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x28) != 0) {
                var_r25_4 = temp_r31;
                var_r26_3 = 0;
loop_101:
                if (var_r26_3 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x28) & (1 << var_r26_3)) {
                        GSgfx_GCSetTevOrder(var_r26_3, LAYER_STATE_FIELD(s32, var_r25_4, 0x240), LAYER_STATE_FIELD(s32, var_r25_4, 0x244), LAYER_STATE_FIELD(s32, var_r25_4, 0x248));
                    }
                    var_r25_4 += 0xC;
                    var_r26_3 += 1;
                    goto loop_101;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x28) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x2C) != 0) {
                var_r25_5 = temp_r31;
                var_r26_4 = 0;
loop_108:
                if (var_r26_4 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x2C) & (1 << var_r26_4)) {
                        GSgfx_GCSetTevColorIn(var_r26_4, LAYER_STATE_FIELD(s32, var_r25_5, 0x300), LAYER_STATE_FIELD(s32, var_r25_5, 0x304), LAYER_STATE_FIELD(s32, var_r25_5, 0x308), LAYER_STATE_FIELD(s32, var_r25_5, 0x30C));
                    }
                    var_r25_5 += 0x10;
                    var_r26_4 += 1;
                    goto loop_108;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x2C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x30) != 0) {
                var_r25_6 = temp_r31;
                var_r26_5 = 0;
loop_115:
                if (var_r26_5 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x30) & (1 << var_r26_5)) {
                        GSgfx_GCSetTevAlphaIn(var_r26_5, LAYER_STATE_FIELD(s32, var_r25_6, 0x400), LAYER_STATE_FIELD(s32, var_r25_6, 0x404), LAYER_STATE_FIELD(s32, var_r25_6, 0x408), LAYER_STATE_FIELD(s32, var_r25_6, 0x40C));
                    }
                    var_r25_6 += 0x10;
                    var_r26_5 += 1;
                    goto loop_115;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x30) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x34) != 0) {
                var_r25_7 = temp_r31;
                var_r26_6 = 0;
loop_122:
                if (var_r26_6 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x34) & (1 << var_r26_6)) {
                        GSgfx_GCSetTevColorOp(var_r26_6, LAYER_STATE_FIELD(s32, var_r25_7, 0x500), LAYER_STATE_FIELD(s32, var_r25_7, 0x504), LAYER_STATE_FIELD(s32, var_r25_7, 0x508), LAYER_STATE_FIELD(u8, var_r25_7, 0x50C), LAYER_STATE_FIELD(s32, var_r25_7, 0x510));
                    }
                    var_r25_7 += 0x14;
                    var_r26_6 += 1;
                    goto loop_122;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x34) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x38) != 0) {
                var_r25_8 = temp_r31;
                var_r26_7 = 0;
loop_129:
                if (var_r26_7 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x38) & (1 << var_r26_7)) {
                        GSgfx_GCSetTevAlphaOp(var_r26_7, LAYER_STATE_FIELD(s32, var_r25_8, 0x640), LAYER_STATE_FIELD(s32, var_r25_8, 0x644), LAYER_STATE_FIELD(s32, var_r25_8, 0x648), LAYER_STATE_FIELD(u8, var_r25_8, 0x64C), LAYER_STATE_FIELD(s32, var_r25_8, 0x650));
                    }
                    var_r25_8 += 0x14;
                    var_r26_7 += 1;
                    goto loop_129;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x38) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x3C) != 0) {
                var_r3_2 = temp_r31;
                var_r4_2 = 0;
                var_r5_3 = 0;
                var_ctr = 4;
                do {
                    temp_r0_3 = 1 << var_r4_2;
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x3C) & temp_r0_3) {
                        if ((u32) LAYER_STATE_FIELD(u32, var_r3_2, 0x780) == 0U) {
                            temp_r9 = var_r5_3 + 0x2A6;
                            temp_r10 = var_r5_3 + 0x2A4;
                            sp1C = LAYER_STATE_FIELD(s32, var_r3_2, 0x784);
                            temp_r8_2 = var_r5_3 + 0x2B6;
                            temp_r7_2 = var_r5_3 + 0x2B4;
                            LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x7FF) | (LAYER_STATE_FIELD(u8, &sp1C,0) & 0x7FF);
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x7FF000) | ((LAYER_STATE_FIELD(u8, &sp1C,3) << 0xC) & 0x7FF000);
                            LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) & ~0x7FF) | (LAYER_STATE_FIELD(u8, &sp1C,2) & 0x7FF);
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r7_2, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r7_2, 0) & ~0x7FF000) | ((LAYER_STATE_FIELD(u8, &sp1C,1) << 0xC) & 0x7FF000);
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x24) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x24) | temp_r0_3);
                        } else {
                            temp_r10_2 = var_r5_3 + 0x2A6;
                            temp_r12_2 = var_r5_3 + 0x2A4;
                            sp34 = LAYER_STATE_FIELD(s32, var_r3_2, 0x784);
                            temp_r8_3 = var_r5_3 + 0x2B6;
                            temp_r7_3 = var_r5_3 + 0x2B4;
                            sp38 = LAYER_STATE_FIELD(s32, var_r3_2, 0x788);
                            LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) & ~0x7FF) | (LAYER_STATE_FIELD(s16, &sp34,0) & 0x7FF);
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0) & ~0x7FF000) | (((LAYER_STATE_FIELD(u16, &sp38,2) & 0x7FF) << 0xC) & 0x7FF000);
                            LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r8_3, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r8_3, 0) & ~0x7FF) | (LAYER_STATE_FIELD(s16, &sp38,0) & 0x7FF & 0x7FF);
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r7_3, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r7_3, 0) & ~0x7FF000) | (((LAYER_STATE_FIELD(u16, &sp34,2) & 0x7FF) << 0xC) & 0x7FF000);
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x24) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x24) | temp_r0_3);
                        }
                    }
                    var_r3_2 += 0xC;
                    var_r4_2 += 1;
                    var_r5_3 += 4;
                    var_ctr -= 1;
                } while (var_ctr != 0);
                LAYER_STATE_FIELD(s32, temp_r30, 0x3C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x40) != 0) {
                var_r28_2 = 0;
                var_r29_2 = temp_r31;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x40) & (1 << var_r28_2)) {
                        temp_r0_4 = LAYER_STATE_FIELD(s32, var_r29_2, 0x7B0);
                        switch (temp_r0_4) {
                        case 0:
                            GSgfx_GCSetTevDirect(var_r28_2);
                            break;
                        case 1:
                            sp8 = (s32) LAYER_STATE_FIELD(u8, var_r29_2, 0x7D1);
                            spC = LAYER_STATE_FIELD(s32, var_r29_2, 0x7CC);
                            GSgfx_GCSetTevIndirect(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8), LAYER_STATE_FIELD(s32, var_r29_2, 0x7BC), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C0), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C8), LAYER_STATE_FIELD(u8, var_r29_2, 0x7D0), sp8, spC);
                            break;
                        case 2:
                            GSgfx_GCSetTevIndWarp(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(u8, var_r29_2, 0x7B5), LAYER_STATE_FIELD(u8, var_r29_2, 0x7B6), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 3:
                            sp8 = LAYER_STATE_FIELD(s32, var_r29_2, 0x7C8);
                            spC = LAYER_STATE_FIELD(s32, var_r29_2, 0x7CC);
                            GSgfx_GCWriteTevIndTile(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7B6), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7B8), LAYER_STATE_FIELD(u16, var_r29_2, 0x7BA), (u16) LAYER_STATE_FIELD(u16, var_r29_2, 0x7BC), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C0), LAYER_STATE_FIELD(s32, var_r29_2, 0x7C4), sp8, spC);
                            break;
                        case 4:
                            GSgfx_GCWriteTevIndBumpST(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 5:
                            GSgfx_GCSetTevIndBumpXYZ(var_r28_2, LAYER_STATE_FIELD(u8, var_r29_2, 0x7B4), LAYER_STATE_FIELD(s32, var_r29_2, 0x7B8));
                            break;
                        case 6:
                            GSgfx_GCSetTevIndRepeat(var_r28_2);
                            break;
                        }
                    }
                    var_r28_2 += 1;
                    var_r29_2 += 0x24;
                } while (var_r28_2 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x40) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x24) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x80) {
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x44) & 1) {
                temp_r4_8 = LAYER_STATE_FIELD(u8, temp_r31, 0x840);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0x58D) != temp_r4_8) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x31) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x31) & ~7) | (temp_r4_8 & 7));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x58D) = temp_r4_8;
                }
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x48) != 0) {
                var_r25_9 = temp_r31;
                var_r26_8 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x48) & (1 << var_r26_8)) {
                        GSgfx_GCSetIndTexOrder(var_r26_8, LAYER_STATE_FIELD(s32, var_r25_9, 0x844), LAYER_STATE_FIELD(s32, var_r25_9, 0x848));
                    }
                    var_r26_8 += 1;
                    var_r25_9 += 8;
                } while (var_r26_8 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x48) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x4C) != 0) {
                var_r25_10 = temp_r31;
                var_r26_9 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x4C) & (1 << var_r26_9)) {
                        GSgfx_GCSetIndTexCoordScale(var_r26_9, LAYER_STATE_FIELD(s32, var_r25_10, 0x864), LAYER_STATE_FIELD(s32, var_r25_10, 0x868));
                    }
                    var_r26_9 += 1;
                    var_r25_10 += 8;
                } while (var_r26_9 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x4C) = 0U;
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x44) = 0;
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x10) {
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x50) != 0) {
                var_r25_11 = temp_r31;
                var_r26_10 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x50) & (1 << var_r26_10)) {
                        sp28 = LAYER_STATE_FIELD(s32, var_r25_11, 0x884);
                        GSgfx_GCSetTevKColor(var_r26_10, &sp28);
                    }
                    var_r26_10 += 1;
                    var_r25_11 += 4;
                } while (var_r26_10 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x50) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x54) != 0) {
                var_r3_3 = temp_r31;
                var_r4_3 = 0;
                var_r5_4 = 0;
loop_187:
                if (var_r4_3 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x54) & (1 << var_r4_3)) {
                        temp_r9_2 = LAYER_STATE_FIELD(s32, var_r3_3, 0x894);
                        if ((s32) LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_4 + 0xA24), 0) != temp_r9_2) {
                            temp_r10_3 = var_r4_3 >> 1;
                            if (var_r4_3 & 1) {
                                temp_r6_3 = (temp_r10_3 * 4) + 0x204;
                                LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r6_3, 0) = (LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + temp_r6_3, 0) & ~0x7C000) | ((temp_r9_2 << 0xE) & 0x7C000);
                            } else {
                                temp_r6_4 = (temp_r10_3 * 4) + 0x206;
                                LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r6_4, 0) = (LAYER_STATE_FIELD(u16, reinterpret_cast<u8*>(gsgfxState) + temp_r6_4, 0) & ~0x1F0) | ((temp_r9_2 << 4) & 0x1F0);
                            }
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x18) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x18) | (1 << temp_r10_3));
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_4 + 0xA24), 0) = temp_r9_2;
                        }
                    }
                    var_r3_3 += 4;
                    var_r4_3 += 1;
                    var_r5_4 += 4;
                    goto loop_187;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x54) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x58) != 0) {
                var_r3_4 = temp_r31;
                var_r4_4 = 0;
                var_r5_5 = 0;
loop_198:
                if (var_r4_4 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x58) & (1 << var_r4_4)) {
                        temp_r9_3 = LAYER_STATE_FIELD(s32, var_r3_4, 0x8D4);
                        if ((s32) LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_5 + 0xA64), 0) != temp_r9_3) {
                            temp_r10_4 = var_r4_4 >> 1;
                            if (var_r4_4 & 1) {
                                temp_r6_5 = (temp_r10_4 * 4) + 0x205;
                                LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_5, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_5, 0) & ~0xF8) | ((temp_r9_3 << 3) & 0xF8);
                            } else {
                                temp_r6_6 = (temp_r10_4 * 4) + 0x206;
                                LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_6, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r6_6, 0) & ~0x3E) | ((temp_r9_3 << 1) & 0x3E);
                            }
                            LAYER_STATE_FIELD(s32, gsgfxState, 0x18) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x18) | (1 << temp_r10_4));
                            LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r5_5 + 0xA64), 0) = temp_r9_3;
                        }
                    }
                    var_r3_4 += 4;
                    var_r4_4 += 1;
                    var_r5_5 += 4;
                    goto loop_198;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x58) = 0U;
            }
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x20) {
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x5C) != 0) {
                var_r3_5 = temp_r31;
                var_r4_5 = 0;
                var_r5_6 = 0;
                var_r6_3 = 0;
loop_208:
                if (var_r4_5 < (s32) LAYER_STATE_FIELD(s32, temp_r31, 0x23C)) {
                    if ((LAYER_STATE_FIELD(s32, temp_r30, 0x5C) & (1 << var_r4_5)) && ((temp_r24_2 = LAYER_STATE_FIELD(s32, var_r3_5, 0x914), temp_r7_4 = reinterpret_cast<u8*>(gsgfxState) + var_r6_3, temp_r25 = LAYER_STATE_FIELD(s32, var_r3_5, 0x918), (((s32) LAYER_STATE_FIELD(s32, temp_r7_4, 0xAA4) == temp_r24_2) == 0)) || ((s32) LAYER_STATE_FIELD(s32, temp_r7_4, 0xAA8) != temp_r25))) {
                        temp_r12_3 = var_r5_6 + 0x267;
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) & ~3) | (temp_r24_2 & 3);
                        LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) = (LAYER_STATE_FIELD(u8, reinterpret_cast<u8*>(gsgfxState) + temp_r12_3, 0) & ~0xC) | ((temp_r25 << 2) & 0xC);
                        LAYER_STATE_FIELD(s32, gsgfxState, 0x20) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x20) | (1 << var_r4_5));
                        LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r6_3 + 0xAA4), 0) = temp_r24_2;
                        LAYER_STATE_FIELD(u32, reinterpret_cast<u8*>(gsgfxState) + (var_r6_3 + 0xAA8), 0) = temp_r25;
                    }
                    var_r3_5 += 8;
                    var_r4_5 += 1;
                    var_r5_6 += 4;
                    var_r6_3 += 8;
                    goto loop_208;
                }
                LAYER_STATE_FIELD(s32, temp_r30, 0x5C) = 0U;
            }
            if ((u32) LAYER_STATE_FIELD(u32, temp_r30, 0x60) != 0) {
                var_r25_12 = temp_r31;
                var_r26_11 = 0;
                do {
                    if (LAYER_STATE_FIELD(s32, temp_r30, 0x60) & (1 << var_r26_11)) {
                        GSgfx_GCSetTevSwapModeTable(var_r26_11, LAYER_STATE_FIELD(s32, var_r25_12, 0x994), LAYER_STATE_FIELD(s32, var_r25_12, 0x998), LAYER_STATE_FIELD(s32, var_r25_12, 0x99C), LAYER_STATE_FIELD(s32, var_r25_12, 0x9A0));
                    }
                    var_r26_11 += 1;
                    var_r25_12 += 0x10;
                } while (var_r26_11 < 4);
                LAYER_STATE_FIELD(s32, temp_r30, 0x60) = 0U;
            }
        }
        if (LAYER_STATE_FIELD(s32, temp_r30, 0x0) & 0x40) {
            var_r29_3 = LAYER_STATE_FIELD(s32, temp_r31, 0x9F0);
            temp_r0_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x9EC) != 0;
            var_r28_3 = temp_r0_5;
            if (((u8) LAYER_STATE_FIELD(u8, temp_r31, 0x9E8) == 1) && (temp_r0_5 == 0)) {
                var_r28_3 = 1;
                var_r29_3 = 7;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 1) {
                GSgfx_GCSetBlendMode(LAYER_STATE_FIELD(s32, temp_r31, 0x9D4), LAYER_STATE_FIELD(s32, temp_r31, 0x9D8), LAYER_STATE_FIELD(s32, temp_r31, 0x9DC), LAYER_STATE_FIELD(s32, temp_r31, 0x9E0));
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 2) && ((temp_r4_9 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E4), temp_r5_3 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E5), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF2) == temp_r4_9) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF3) != temp_r5_3))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3E) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x3E) & ~1) | (temp_r4_9 & 1));
                LAYER_STATE_FIELD(u8, gsgfxState, 0x3F) = temp_r5_3;
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 8);
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBF2) = temp_r4_9;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBF3) = temp_r5_3;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 4) {
                temp_r4_10 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E6);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBC4) != temp_r4_10) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) & ~8) | ((temp_r4_10 << 3) & 8));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBC4) = temp_r4_10;
                }
                temp_r4_11 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E7);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBC5) != temp_r4_11) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) & ~0x10) | ((temp_r4_11 << 4) & 0x10));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBC5) = temp_r4_11;
                }
                temp_r5_4 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E8);
                if (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) != var_r28_3) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) != var_r29_3) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) != temp_r5_4)) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~1) | (var_r28_3 & 1));
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~0xE) | ((var_r29_3 << 1) & 0xE));
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~0x10) | ((temp_r5_4 << 4) & 0x10));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 2);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) = var_r28_3;
                    LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) = var_r29_3;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) = temp_r5_4;
                }
            }
            if ((LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 8) && ((temp_r5_5 = LAYER_STATE_FIELD(u8, temp_r31, 0x9E8), (((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) == var_r28_3) == 0)) || ((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) != var_r29_3) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) != temp_r5_5))) {
                LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~1) | (var_r28_3 & 1));
                LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~0xE) | ((var_r29_3 << 1) & 0xE));
                LAYER_STATE_FIELD(u8, gsgfxState, 0x37) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x37) & ~0x10) | ((temp_r5_5 << 4) & 0x10));
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 2);
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBE4) = var_r28_3;
                LAYER_STATE_FIELD(s32, gsgfxState, 0xBE8) = var_r29_3;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xBEC) = temp_r5_5;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x10) {
                GSgfx_GCSetAlphaCompare(LAYER_STATE_FIELD(s32, temp_r31, 0x9F4), LAYER_STATE_FIELD(u8, temp_r31, 0xA00), LAYER_STATE_FIELD(s32, temp_r31, 0x9F8), LAYER_STATE_FIELD(s32, temp_r31, 0x9FC), LAYER_STATE_FIELD(u8, temp_r31, 0xA01));
                temp_r4_12 = LAYER_STATE_FIELD(u8, temp_r31, 0xA02);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF0) != temp_r4_12) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x43) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x43) & ~0x40) | ((temp_r4_12 << 6) & 0x40));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x10);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBF0) = temp_r4_12;
                }
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x20) {
                temp_r4_13 = LAYER_STATE_FIELD(u8, temp_r31, 0xA04);
                if ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xBF1) != temp_r4_13) {
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) = (u8) ((LAYER_STATE_FIELD(u8, gsgfxState, 0x3B) & ~4) | ((temp_r4_13 << 2) & 4));
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 4);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xBF1) = temp_r4_13;
                }
            }
            temp_r3_3 = LAYER_STATE_FIELD(s32, temp_r30, 0x64);
            if (temp_r3_3 & 0x40) {
                if ((u8) LAYER_STATE_FIELD(u8, temp_r31, 0xA37) == 1) {
                    var_r24_2 = LAYER_STATE_FIELD(s32, temp_r31, 0xA08);
                    if (var_r24_2 == 0) {
                        LAYER_STATE_FIELD(u8, temp_r31, 0xA37) = 0U;
                    }
                } else {
                    var_r24_2 = 0;
                }
                if (((s32) LAYER_STATE_FIELD(s32, gsgfxState, 0xBF4) != var_r24_2) || (LAYER_STATE_FIELD(float, gsgfxState, 0xBF8) != LAYER_STATE_FIELD(float, temp_r31, 0xA0C)) || (LAYER_STATE_FIELD(float, gsgfxState, 0xBFC) != LAYER_STATE_FIELD(float, temp_r31, 0xA10)) || (LAYER_STATE_FIELD(float, gsgfxState, 0xC00) != LAYER_STATE_FIELD(float, temp_r31, 0xA14)) || (LAYER_STATE_FIELD(float, gsgfxState, 0xC04) != LAYER_STATE_FIELD(float, temp_r31, 0xA18))) {
                    GSgfx_GCWriteFog(var_r24_2, LAYER_STATE_FIELD(float, temp_r31,0xA0C), LAYER_STATE_FIELD(float, temp_r31,0xA10), LAYER_STATE_FIELD(float, temp_r31,0xA14), LAYER_STATE_FIELD(float, temp_r31,0xA18));
                }
                if ((var_r24_2 != 0) && ((temp_r3_4 = LAYER_STATE_FIELD(s32, temp_r31, 0xA1C), sp24 = temp_r3_4, (((u32) LAYER_STATE_FIELD(u32, gsgfxState, 0xC09) == temp_r3_4) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) == 1))) {
                    sp18 = sp24;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F5) = LAYER_STATE_FIELD(u8, &sp18,0);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F6) = LAYER_STATE_FIELD(u8, &sp18,1);
                    LAYER_STATE_FIELD(u8, gsgfxState, 0x2F7) = LAYER_STATE_FIELD(u8, &sp18,2);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x20000);
                    LAYER_STATE_FIELD(s32, gsgfxState, 0xC09) = sp24;
                    LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) = 0U;
                }
            } else if ((temp_r3_3 & 0x80) && ((temp_r3_5 = LAYER_STATE_FIELD(s32, temp_r31, 0xA1C), sp20 = temp_r3_5, (((u32) LAYER_STATE_FIELD(u32, gsgfxState, 0xC09) == temp_r3_5) == 0)) || ((u8) LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) == 1))) {
                sp14 = sp20;
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F5) = LAYER_STATE_FIELD(u8, &sp14,0);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F6) = LAYER_STATE_FIELD(u8, &sp14,1);
                LAYER_STATE_FIELD(u8, gsgfxState, 0x2F7) = LAYER_STATE_FIELD(u8, &sp14,2);
                LAYER_STATE_FIELD(s32, gsgfxState, 0x0) = (s32) (LAYER_STATE_FIELD(s32, gsgfxState, 0x0) | 0x20000);
                LAYER_STATE_FIELD(s32, gsgfxState, 0xC09) = sp20;
                LAYER_STATE_FIELD(u8, gsgfxState, 0xC08) = 0U;
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x100) {
                memset(fogProjection,0,sizeof(fogProjection));
                temp_r3_6 = static_cast<u8*>(GSgfxVideoGetViewport());
                if ((s32) LAYER_STATE_FIELD(s32, temp_r31, 0xE4) == 0) {
                    fogProjection[0][0] = LAYER_STATE_FIELD(float, temp_r31, 0xE8);
                    fogProjection[0][2] = LAYER_STATE_FIELD(float, temp_r31, 0xEC);
                    fogProjection[0][3] = 0.0f;
                    fogProjection[1][1] = LAYER_STATE_FIELD(float, temp_r31, 0xF0);
                    fogProjection[1][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF4);
                    fogProjection[1][3] = 0.0f;
                    fogProjection[2][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF8);
                    fogProjection[2][3] = LAYER_STATE_FIELD(float, temp_r31, 0xFC);
                    fogProjection[3][2] = -1.0f;
                    fogProjection[3][3] = 0.0f;
                } else {
                    fogProjection[0][0] = LAYER_STATE_FIELD(float, temp_r31, 0xE8);
                    fogProjection[0][2] = 0.0f;
                    fogProjection[0][3] = LAYER_STATE_FIELD(float, temp_r31, 0xEC);
                    fogProjection[1][1] = LAYER_STATE_FIELD(float, temp_r31, 0xF0);
                    fogProjection[1][2] = 0.0f;
                    fogProjection[1][3] = LAYER_STATE_FIELD(float, temp_r31, 0xF4);
                    fogProjection[2][2] = LAYER_STATE_FIELD(float, temp_r31, 0xF8);
                    fogProjection[2][3] = LAYER_STATE_FIELD(float, temp_r31, 0xFC);
                    fogProjection[3][2] = -1.0f;
                    fogProjection[3][3] = 0.0f;
                }
                // SDK fast-cast uses GQR3 unsigned-halfword quantization here.
                register float viewportWidth=LAYER_STATE_FIELD(float, temp_r3_6,8);
                u16 fogWidth;
                register u16* fogWidthStorage=&fogWidth;
                asm { psq_st viewportWidth, 0(fogWidthStorage), 1, 3 }
                GXInitFogAdjTable(reinterpret_cast<GXFogAdjTable*>(temp_r31 + 0xA20), fogWidth, fogProjection);
            }
            if (LAYER_STATE_FIELD(s32, temp_r30, 0x64) & 0x200) {
                GSgfx_GCSetFogRangeAdj(LAYER_STATE_FIELD(u8, temp_r31, 0xA36), LAYER_STATE_FIELD(u16, temp_r31, 0xA34), temp_r31 + 0xA20);
            }
            LAYER_STATE_FIELD(s32, temp_r30, 0x64) = 0;
        }
        LAYER_STATE_FIELD(s32, temp_r30, 0x0) = 0U;
    }
}

__declspec(weak) void GSgfx_GCSetFogRangeAdj(u8 arg0, u16 arg1, u8 *arg2) {
    u8 var_r7;

    if ((arg0 != (u8) layerField<u8>(gsgfxState, 0xC0D)) || (arg1 != (u16) layerField<u16>(gsgfxState, 0xC0E))) {
        var_r7 = 1;
    } else {
        var_r7 = 0;
        if ((u32) layerField<u32>(gsgfxState, 0xC10) != (u32) layerField<u32>(arg2, 0x0)) {
            var_r7 = 1;
        } else if ((u32) layerField<u32>(gsgfxState, 0xC14) != (u32) layerField<u32>(arg2, 0x4)) {
            var_r7 = 1;
        } else if ((u32) layerField<u32>(gsgfxState, 0xC18) != (u32) layerField<u32>(arg2, 0x8)) {
            var_r7 = 1;
        } else if ((u32) layerField<u32>(gsgfxState, 0xC1C) != (u32) layerField<u32>(arg2, 0xC)) {
            var_r7 = 1;
        } else if ((u32) layerField<u32>(gsgfxState, 0xC20) != (u32) layerField<u32>(arg2, 0x10)) {
            var_r7 = 1;
        }
    }
    if (var_r7 == 1) {
        layerField<u8>(gsgfxState, 0x2FA) = (u8) ((layerField<u8>(gsgfxState, 0x2FA) & ~4) | ((arg0 << 2) & 4));
        layerField<u16>(gsgfxState, 0x2FA) = (s16) (((u16) layerField<u16>(gsgfxState, 0x2FA) & ~0x3FF) | ((u16) (arg1 + 0x156) & 0x3FF));
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x40000);
        layerField<u8>(gsgfxState, 0xC0D) = arg0;
        layerField<u16>(gsgfxState, 0xC0E) = arg1;
        if (arg0 == 1) {
            layerField<u16>(gsgfxState, 0x2FE) = (u16) ((layerField<u16>(gsgfxState, 0x2FE) & ~0xFFF) | ((u16) layerField<u16>(arg2, 0x0) & 0xFFF));
            layerField<u32>(gsgfxState, 0x2FC) = (s32) ((layerField<u32>(gsgfxState, 0x2FC) & ~0xFFF000) | ((layerField<u16>(arg2, 0x2) << 0xC) & 0xFFF000));
            layerField<u16>(gsgfxState, 0x302) = (u16) ((layerField<u16>(gsgfxState, 0x302) & ~0xFFF) | ((u16) layerField<u16>(arg2, 0x4) & 0xFFF));
            layerField<u32>(gsgfxState, 0x300) = (s32) ((layerField<u32>(gsgfxState, 0x300) & ~0xFFF000) | ((layerField<u16>(arg2, 0x6) << 0xC) & 0xFFF000));
            layerField<u16>(gsgfxState, 0x306) = (u16) ((layerField<u16>(gsgfxState, 0x306) & ~0xFFF) | ((u16) layerField<u16>(arg2, 0x8) & 0xFFF));
            layerField<u32>(gsgfxState, 0x304) = (s32) ((layerField<u32>(gsgfxState, 0x304) & ~0xFFF000) | ((layerField<u16>(arg2, 0xA) << 0xC) & 0xFFF000));
            layerField<u16>(gsgfxState, 0x30A) = (u16) ((layerField<u16>(gsgfxState, 0x30A) & ~0xFFF) | ((u16) layerField<u16>(arg2, 0xC) & 0xFFF));
            layerField<u32>(gsgfxState, 0x308) = (s32) ((layerField<u32>(gsgfxState, 0x308) & ~0xFFF000) | ((layerField<u16>(arg2, 0xE) << 0xC) & 0xFFF000));
            layerField<u16>(gsgfxState, 0x30E) = (u16) ((layerField<u16>(gsgfxState, 0x30E) & ~0xFFF) | ((u16) layerField<u16>(arg2, 0x10) & 0xFFF));
            layerField<u32>(gsgfxState, 0x30C) = (s32) ((layerField<u32>(gsgfxState, 0x30C) & ~0xFFF000) | ((layerField<u16>(arg2, 0x12) << 0xC) & 0xFFF000));
            layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x80000);
            layerField<s32>(gsgfxState, 0xC10) = (u32) layerField<u32>(arg2, 0x0);
            layerField<s32>(gsgfxState, 0xC14) = (u32) layerField<u32>(arg2, 0x4);
            layerField<s32>(gsgfxState, 0xC18) = (u32) layerField<u32>(arg2, 0x8);
            layerField<s32>(gsgfxState, 0xC1C) = (u32) layerField<u32>(arg2, 0xC);
            layerField<s32>(gsgfxState, 0xC20) = (u32) layerField<u32>(arg2, 0x10);
        }
    }
}

__declspec(weak) void GSgfx_GCSetAlphaCompare(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4) {
    if (((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare0 != arg0) || ((u8) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference0 != arg1) || ((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->operation != arg2) || ((s32) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare1 != arg3) || ((u8) reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference1 != arg4)) {
        layerField<u8>(gsgfxState, 0x1FB) = arg1;
        layerField<u8>(gsgfxState, 0x1FA) = arg4;
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~7) | (arg0 & 7));
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~0x38) | ((arg3 << 3) & 0x38));
        layerField<u8>(gsgfxState, 0x1F9) = (u8) ((layerField<u8>(gsgfxState, 0x1F9) & ~0xC0) | ((arg2 << 6) & 0xC0));
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x100);
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare0 = arg0;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference0 = arg1;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->operation = arg2;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->compare1 = arg3;
        reinterpret_cast<LayerAlphaCompareCache*>(gsgfxState)->reference1 = arg4;
    }
}

__declspec(weak) void GSgfx_GCSetBlendMode(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_r0;

    if (((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->mode != arg0) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->source != arg1) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->destination != arg2) || ((s32) reinterpret_cast<LayerBlendCache*>(gsgfxState)->operation != arg3)) {
        var_r0 = 0;
        if ((arg0 == 1) || (arg0 == 3)) {
            var_r0 = 1;
        }
        layerField<u8>(gsgfxState, 0x3B) = (u8) ((layerField<u8>(gsgfxState, 0x3B) & ~1) | (var_r0 & 1));
        layerField<u8>(gsgfxState, 0x3B) = (u8) ((layerField<u8>(gsgfxState, 0x3B) & ~2) | (((u8) (arg0 == 2) << 1) & 2));
        layerField<u8>(gsgfxState, 0x3A) = (u8) ((layerField<u8>(gsgfxState, 0x3A) & ~7) | (arg1 & 7));
        layerField<u8>(gsgfxState, 0x3B) = (u8) ((layerField<u8>(gsgfxState, 0x3B) & ~0xE0) | ((arg2 << 5) & 0xE0));
        layerField<u8>(gsgfxState, 0x3A) = (u8) ((layerField<u8>(gsgfxState, 0x3A) & ~8) | (((u8) (arg0 == 3) << 3) & 8));
        layerField<u8>(gsgfxState, 0x3A) = (u8) ((layerField<u8>(gsgfxState, 0x3A) & ~0x10) | ((arg3 << 4) & 0x10));
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 4);
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->mode = arg0;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->source = arg1;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->destination = arg2;
        reinterpret_cast<LayerBlendCache*>(gsgfxState)->operation = arg3;
    }
}

__declspec(weak) void GSgfx_GCSetTevSwapModeTable(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r0;
    s32 temp_r12;
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;
    u8 *temp_r8;

    temp_r8 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0x10);
    if (((s32) reinterpret_cast<LayerSwapTableCache*>(temp_r8)->red != arg1) || ((s32) reinterpret_cast<LayerSwapTableCache*>(temp_r8)->green != arg2) || ((s32) reinterpret_cast<LayerSwapTableCache*>(temp_r8)->blue != arg3) || ((s32) reinterpret_cast<LayerSwapTableCache*>(temp_r8)->alpha != arg4)) {
        temp_r27 = arg0 * 2;
        temp_r29 = (arg0 * 8) + 0x207;
        temp_r28 = temp_r27 + 1;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r29, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r29, 0) & ~3) | (arg1 & 3);
        temp_r12 = (temp_r28 * 4) + 0x207;
        temp_r0 = arg0 * 0x10;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r29, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r29, 0) & ~0xC) | ((arg2 << 2) & 0xC);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) & ~3) | (arg3 & 3);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) & ~0xC) | ((arg4 << 2) & 0xC);
        layerField<s32>(gsgfxState, 0x18) = (s32) (layerField<s32>(gsgfxState, 0x18) | (1 << temp_r27));
        layerField<s32>(gsgfxState, 0x18) = (s32) (layerField<s32>(gsgfxState, 0x18) | (1 << temp_r28));
        reinterpret_cast<LayerSwapTableCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r0)->red = arg1;
        reinterpret_cast<LayerSwapTableCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r0)->green = arg2;
        reinterpret_cast<LayerSwapTableCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r0)->blue = arg3;
        reinterpret_cast<LayerSwapTableCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r0)->alpha = arg4;
    }
}

__declspec(weak) void GSgfx_GCSetTevKColor(s32 arg0, u32 *arg1) {
    u32 sp8;
    s32 temp_r10;
    s32 temp_r12;
    s32 temp_r4;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r7;
    s32 temp_r8;
    u32 temp_r30;

    temp_r6 = arg0 * 5;
    if (((u32) layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r6 + 0xA11), 0) != (u32) *arg1) || ((u8) layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6, 0xA10) == 1)) {
        temp_r30 = *arg1;
        temp_r12 = arg0 * 4;
        temp_r6_2 = temp_r12 + 0x2C6;
        sp8 = temp_r30;
        temp_r4 = arg0 * 5;
        temp_r10 = temp_r12 + 0x2C4;
        temp_r8 = temp_r12 + 0x2D6;
        layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r6_2, 0) = (layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r6_2, 0) & ~0x7FF) | (layerField<u8>(&sp8,0) & 0x7FF);
        temp_r7 = temp_r12 + 0x2D4;
        layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x7FF000) | ((layerField<u8>(&sp8,3) << 0xC) & 0x7FF000);
        layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = (layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~0x7FF) | (layerField<u8>(&sp8,2) & 0x7FF);
        layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~0x7FF000) | ((layerField<u8>(&sp8,1) << 0xC) & 0x7FF000);
        layerField<s32>(gsgfxState, 0x28) = (s32) (layerField<s32>(gsgfxState, 0x28) | (1 << arg0));
        layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r4 + 0xA11), 0) = temp_r30;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r4, 0xA10) = 0;
    }
}

__declspec(weak) void GSgfx_GCSetIndTexCoordScale(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r11;
    s32 temp_r6_2;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r8;
    s32 temp_r9;
    u8 *temp_r6;

    temp_r6 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 8);
    if (((s32) reinterpret_cast<LayerIndScaleCache*>(temp_r6)->s != arg1) || ((s32) reinterpret_cast<LayerIndScaleCache*>(temp_r6)->t != arg2)) {
        temp_r9 = arg0 >> 1;
        if (arg0 & 1) {
            temp_r8 = (temp_r9 * 4) + 0x7E;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~0xF) | (arg1 & 0xF);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~0xF0) | ((arg2 << 4) & 0xF0);
        } else {
            temp_r11 = temp_r9 * 4;
            temp_r7 = temp_r11 + 0x7F;
            temp_r6_2 = temp_r11 + 0x7E;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~0xF) | (arg1 & 0xF);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6_2, 0) & ~0xF0) | ((arg2 << 4) & 0xF0);
        }
        temp_r7_2 = arg0 * 8;
        layerField<s32>(gsgfxState, 0x8) = (s32) (layerField<s32>(gsgfxState, 0x8) | (1 << temp_r9));
        reinterpret_cast<LayerIndScaleCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7_2)->s = arg1;
        reinterpret_cast<LayerIndScaleCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7_2)->t = arg2;
    }
}

__declspec(weak) void GSgfx_GCSetIndTexOrder(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_r7;
    u8 *temp_r6;

    temp_r6 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 8);
    if (((s32) reinterpret_cast<LayerIndOrderCache*>(temp_r6)->coordinate != arg1) || ((s32) reinterpret_cast<LayerIndOrderCache*>(temp_r6)->map != arg2)) {
        switch (arg0) {                             /* irregular */
        case 0:
            layerField<u8>(gsgfxState, 0x7B) = (u8) ((layerField<u8>(gsgfxState, 0x7B) & ~7) | (arg2 & 7));
            layerField<u8>(gsgfxState, 0x7B) = (u8) ((layerField<u8>(gsgfxState, 0x7B) & ~0x38) | ((arg1 << 3) & 0x38));
            break;
        case 1:
            layerField<u16>(gsgfxState, 0x7A) = (u16) ((layerField<u16>(gsgfxState, 0x7A) & ~0x1C0) | ((arg2 << 6) & 0x1C0));
            layerField<u8>(gsgfxState, 0x7A) = (s8) (((u8) layerField<u8>(gsgfxState, 0x7A) & ~0xE) | ((arg1 << 1) & 0xE));
            break;
        case 2:
            layerField<u8>(gsgfxState, 0x7A) = (s8) (((u8) layerField<u8>(gsgfxState, 0x7A) & ~0x70) | ((arg2 << 4) & 0x70));
            layerField<u32>(gsgfxState, 0x78) = (s32) ((layerField<u32>(gsgfxState, 0x78) & ~0x38000) | ((arg1 << 0xF) & 0x38000));
            break;
        case 3:
            layerField<u8>(gsgfxState, 0x79) = (u8) ((layerField<u8>(gsgfxState, 0x79) & ~0x1C) | ((arg2 << 2) & 0x1C));
            layerField<u8>(gsgfxState, 0x79) = (u8) ((layerField<u8>(gsgfxState, 0x79) & ~0xE0) | ((arg1 << 5) & 0xE0));
            break;
        }
        temp_r7 = arg0 * 8;
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x2000);
        layerField<s32>(gsgfxState, 0xC) = (s32) (layerField<s32>(gsgfxState, 0xC) | (1 << arg1));
        reinterpret_cast<LayerIndOrderCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7)->coordinate = arg1;
        reinterpret_cast<LayerIndOrderCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7)->map = arg2;
    }
}

__declspec(weak) void GSgfx_GCSetTevIndRepeat(s32 arg0) {
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r5;
    s32 temp_r8;

    temp_r5 = arg0 * 4;
    temp_r11 = temp_r5 + 0x313;
    temp_r10 = temp_r5 + 0x312;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~3;
    temp_r8 = temp_r5 + 0x311;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~0xC;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~0x70;
    layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x180;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x1E;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0xE0) | 0xC0;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~7) | 6;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~8;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) | 0x10;
    layerField<s32>(gsgfxState, 0x2C) = (s32) (layerField<s32>(gsgfxState, 0x2C) | (1 << arg0));
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 2;
}

__declspec(weak) void GSgfx_GCSetTevIndBumpXYZ(s32 arg0, u8 arg1, s32 arg2) {
    s32 temp_r12;
    s32 temp_r31;
    s32 temp_r7;
    s32 temp_r9;

    temp_r31 = arg0 * 4;
    temp_r12 = temp_r31 + 0x313;
    temp_r9 = temp_r31 + 0x312;
    temp_r7 = temp_r31 + 0x311;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) & ~3) | (arg1 & 3);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) & ~0xC;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r12, 0) | 0x70;
    layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x180;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x1E) | ((((u8)arg2) << 1) & 0x1E);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0xE0;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~7;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~8;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~0x10;
    layerField<s32>(gsgfxState, 0x2C) = (s32) (layerField<s32>(gsgfxState, 0x2C) | (1 << arg0));
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 2;
}

__declspec(weak) void GSgfx_GCSetTevIndWarp(s32 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    s32 temp_r10;
    s32 temp_r31;
    s32 temp_r5;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_r12;
    s32 var_r8;

    var_r12 = 0;
    if (arg3 != 0) {
        var_r12 = 6;
    }
    temp_r31 = arg0 * 4;
    temp_r6 = temp_r31 + 0x313;
    var_r8 = 0;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6, 0) & ~3) | (arg1 & 3);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r6, 0) & ~0xC;
    if (arg2 != 0) {
        var_r8 = 7;
    }
    temp_r5 = temp_r31 + 0x313;
    temp_r10 = temp_r31 + 0x312;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r5, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r5, 0) & ~0x70) | ((var_r8 << 4) & 0x70);
    temp_r7 = temp_r31 + 0x311;
    layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x180;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x1E) | ((((u8)arg4) << 1) & 0x1E);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0xE0) | ((var_r12 << 5) & 0xE0);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~7) | (var_r12 & 7);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~8;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~0x10;
    layerField<s32>(gsgfxState, 0x2C) = (s32) (layerField<s32>(gsgfxState, 0x2C) | (1 << arg0));
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 2;
}

__declspec(weak) void GSgfx_GCSetTevIndirect(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, u8 arg_sp8, s32 arg_spC) {
    s32 temp_r26;
    s32 temp_r27;
    s32 temp_r31;
    s32 temp_r7;

    temp_r26 = arg0 * 4;
    temp_r27 = temp_r26 + 0x313;
    temp_r31 = temp_r26 + 0x312;
    temp_r7 = temp_r26 + 0x311;
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) & ~3) | (arg1 & 3);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) & ~0xC) | ((((u8)arg2) << 2) & 0xC);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r27, 0) & ~0x70) | ((((u8)arg3) << 4) & 0x70);
    layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x180) | (((u16) arg_spC << 7) & 0x180);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x1E) | ((((u8)arg4) << 1) & 0x1E);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xE0) | ((((u8)arg5) << 5) & 0xE0);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~7) | (((u8)arg6) & 7);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~8) | ((arg_sp8 << 3) & 8);
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r7, 0) & ~0x10) | ((arg7 << 4) & 0x10);
    layerField<s32>(gsgfxState, 0x2C) = (s32) (layerField<s32>(gsgfxState, 0x2C) | (1 << arg0));
    layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 2;
}

__declspec(weak) void GSgfx_GCSetTevDirect(s32 arg0) {
    s32 temp_r10;
    s32 temp_r4;
    s32 temp_r8;
    s32 temp_r9;

    if ((u8) layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) != 1) {
        temp_r4 = arg0 * 4;
        temp_r10 = temp_r4 + 0x313;
        temp_r9 = temp_r4 + 0x312;
        temp_r8 = temp_r4 + 0x311;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~3;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0xC;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x70;
        layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x180;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x1E;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0xE0;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~7;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~8;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~0x10;
        layerField<s32>(gsgfxState, 0x2C) = (s32) (layerField<s32>(gsgfxState, 0x2C) | (1 << arg0));
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 2;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + arg0, 0xB64) = 1;
    }
}

__declspec(weak) void GSgfx_GCSetTevAlphaOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    s32 temp_r11;
    s32 temp_r31;
    s32 temp_r31_2;
    u8 *temp_r10;

    temp_r10 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0x14);
    if (((s32) reinterpret_cast<LayerTevAlphaOperationCache*>(temp_r10)->operation != arg1) || ((s32) reinterpret_cast<LayerTevAlphaOperationCache*>(temp_r10)->bias != arg2) || ((s32) reinterpret_cast<LayerTevAlphaOperationCache*>(temp_r10)->scale != arg3) || ((u8) reinterpret_cast<LayerTevAlphaOperationCache*>(temp_r10)->clamp != arg4) || ((s32) reinterpret_cast<LayerTevAlphaOperationCache*>(temp_r10)->output != arg5)) {
        if (arg1 <= 1) {
            temp_r31 = (arg0 * 4) + 0x265;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~3) | (arg2 & 3);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~4) | ((arg1 << 2) & 4);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~8) | ((arg4 << 3) & 8);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x30) | ((arg3 << 4) & 0x30);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xC0) | ((arg5 << 6) & 0xC0);
        } else {
            temp_r31_2 = (arg0 * 4) + 0x265;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) | 3;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~4) | ((arg1 << 2) & 4);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~8) | ((arg4 << 3) & 8);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~0x30) | ((arg1 << 3) & 0x30);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~0xC0) | ((arg5 << 6) & 0xC0);
        }
        temp_r11 = arg0 * 0x14;
        layerField<s32>(gsgfxState, 0x20) = (s32) (layerField<s32>(gsgfxState, 0x20) | (1 << arg0));
        reinterpret_cast<LayerTevAlphaOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->operation = arg1;
        reinterpret_cast<LayerTevAlphaOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->bias = arg2;
        reinterpret_cast<LayerTevAlphaOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->scale = arg3;
        reinterpret_cast<LayerTevAlphaOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->clamp = arg4;
        reinterpret_cast<LayerTevAlphaOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->output = arg5;
    }
}

__declspec(weak) void GSgfx_GCSetTevColorOp(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    s32 temp_r11;
    s32 temp_r31;
    s32 temp_r31_2;
    u8 *temp_r10;

    temp_r10 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0x14);
    if (((s32) reinterpret_cast<LayerTevColorOperationCache*>(temp_r10)->operation != arg1) || ((s32) reinterpret_cast<LayerTevColorOperationCache*>(temp_r10)->bias != arg2) || ((s32) reinterpret_cast<LayerTevColorOperationCache*>(temp_r10)->scale != arg3) || ((u8) reinterpret_cast<LayerTevColorOperationCache*>(temp_r10)->clamp != arg4) || ((s32) reinterpret_cast<LayerTevColorOperationCache*>(temp_r10)->output != arg5)) {
        if (arg1 <= 1) {
            temp_r31 = (arg0 * 4) + 0x225;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~3) | (arg2 & 3);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~4) | ((arg1 << 2) & 4);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~8) | ((arg4 << 3) & 8);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x30) | ((arg3 << 4) & 0x30);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xC0) | ((arg5 << 6) & 0xC0);
        } else {
            temp_r31_2 = (arg0 * 4) + 0x225;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) | 3;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~4) | ((arg1 << 2) & 4);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~8) | ((arg4 << 3) & 8);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~0x30) | ((arg1 << 3) & 0x30);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31_2, 0) & ~0xC0) | ((arg5 << 6) & 0xC0);
        }
        temp_r11 = arg0 * 0x14;
        layerField<s32>(gsgfxState, 0x1C) = (s32) (layerField<s32>(gsgfxState, 0x1C) | (1 << arg0));
        reinterpret_cast<LayerTevColorOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->operation = arg1;
        reinterpret_cast<LayerTevColorOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->bias = arg2;
        reinterpret_cast<LayerTevColorOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->scale = arg3;
        reinterpret_cast<LayerTevColorOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->clamp = arg4;
        reinterpret_cast<LayerTevColorOperationCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r11)->output = arg5;
    }
}

__declspec(weak) void GSgfx_GCSetTevAlphaIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 temp_r8_2;
    u8 *temp_r8;

    temp_r8 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0x10);
    if (((s32) reinterpret_cast<LayerTevAlphaInputCache*>(temp_r8)->a != arg1) || ((s32) reinterpret_cast<LayerTevAlphaInputCache*>(temp_r8)->b != arg2) || ((s32) reinterpret_cast<LayerTevAlphaInputCache*>(temp_r8)->c != arg3) || ((s32) reinterpret_cast<LayerTevAlphaInputCache*>(temp_r8)->d != arg4)) {
        temp_r30 = arg0 * 4;
        temp_r31 = temp_r30 + 0x266;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xE0) | ((arg1 << 5) & 0xE0);
        temp_r8_2 = temp_r30 + 0x267;
        temp_r30_2 = arg0 * 0x10;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x1C) | ((arg2 << 2) & 0x1C);
        layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0x380) | ((arg3 << 7) & 0x380);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) & ~0x70) | ((arg4 << 4) & 0x70);
        layerField<s32>(gsgfxState, 0x20) = (s32) (layerField<s32>(gsgfxState, 0x20) | (1 << arg0));
        reinterpret_cast<LayerTevAlphaInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30_2)->a = arg1;
        reinterpret_cast<LayerTevAlphaInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30_2)->b = arg2;
        reinterpret_cast<LayerTevAlphaInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30_2)->c = arg3;
        reinterpret_cast<LayerTevAlphaInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30_2)->d = arg4;
    }
}

__declspec(weak) void GSgfx_GCSetTevColorIn(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r30;
    s32 temp_r31;
    u8 *temp_r8;

    temp_r8 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0x10);
    if (((s32) reinterpret_cast<LayerTevColorInputCache*>(temp_r8)->a != arg1) || ((s32) reinterpret_cast<LayerTevColorInputCache*>(temp_r8)->b != arg2) || ((s32) reinterpret_cast<LayerTevColorInputCache*>(temp_r8)->c != arg3) || ((s32) reinterpret_cast<LayerTevColorInputCache*>(temp_r8)->d != arg4)) {
        temp_r10 = arg0 * 4;
        temp_r31 = temp_r10 + 0x226;
        temp_r30 = arg0 * 0x10;
        temp_r10_2 = temp_r10 + 0x227;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xF0) | ((arg1 << 4) & 0xF0);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r31, 0) & ~0xF) | (arg2 & 0xF);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) & ~0xF0) | ((arg3 << 4) & 0xF0);
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10_2, 0) & ~0xF) | (arg4 & 0xF);
        layerField<s32>(gsgfxState, 0x1C) = (s32) (layerField<s32>(gsgfxState, 0x1C) | (1 << arg0));
        reinterpret_cast<LayerTevColorInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30)->a = arg1;
        reinterpret_cast<LayerTevColorInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30)->b = arg2;
        reinterpret_cast<LayerTevColorInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30)->c = arg3;
        reinterpret_cast<LayerTevColorInputCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r30)->d = arg4;
    }
}

__declspec(weak) void GSgfx_GCSetTevOrder(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_r0;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r7_2;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r9;
    s32 temp_r9_2;
    u8 var_r8;
    u8 var_r8_2;
    u8 *temp_r7;

    temp_r7 = reinterpret_cast<u8*>(gsgfxState) + (arg0 * 0xC);
    if (((s32) reinterpret_cast<LayerTevOrderCache*>(temp_r7)->coordinate != arg1) || ((s32) reinterpret_cast<LayerTevOrderCache*>(temp_r7)->map != arg2) || ((s32) reinterpret_cast<LayerTevOrderCache*>(temp_r7)->color != arg3)) {
        temp_r0 = arg0 >> 1;
        if (arg0 & 1) {
            temp_r31 = temp_r0 * 4;
            temp_r8 = temp_r31 + 0x5A;
            temp_r9 = temp_r31 + 0x58;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r8, 0) & ~0x70) | ((arg2 << 4) & 0x70);
            var_r8 = 0;
            layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) = (layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + temp_r9, 0) & ~0x38000) | ((arg1 << 0xF) & 0x38000);
            if ((arg2 != 0xFF) && !(arg2 & 0x100)) {
                var_r8 = 1;
            }
            temp_r10 = temp_r31 + 0x59;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~4) | ((var_r8 << 2) & 4);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r10, 0) & ~0x38) | ((*(layerTevColorChannel + (arg3 & 0xF)) << 3) & 0x38);
        } else {
            temp_r31_2 = temp_r0 * 4;
            temp_r11 = temp_r31_2 + 0x5B;
            var_r8_2 = 0;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~7) | (arg2 & 7);
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0) & ~0x38) | ((arg1 << 3) & 0x38);
            if ((arg2 != 0xFF) && !(arg2 & 0x100)) {
                var_r8_2 = 1;
            }
            temp_r9_2 = temp_r31_2 + 0x5B;
            layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9_2, 0) = (layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r9_2, 0) & ~0x40) | ((var_r8_2 << 6) & 0x40);
            temp_r8_2 = temp_r31_2 + 0x5A;
            layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) = (layerField<u16>(reinterpret_cast<u8*>(gsgfxState) + temp_r8_2, 0) & ~0x380) | ((*(layerTevColorChannel + (arg3 & 0xF)) << 7) & 0x380);
        }
        layerField<s32>(gsgfxState, 0x4) = (s32) (layerField<s32>(gsgfxState, 0x4) | (1 << temp_r0));
        if (arg1 != 0xFF) {
            layerField<s32>(gsgfxState, 0xC) = (s32) (layerField<s32>(gsgfxState, 0xC) | (1 << arg1));
        }
        temp_r7_2 = arg0 * 0xC;
        reinterpret_cast<LayerTevOrderCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7_2)->coordinate = arg1;
        reinterpret_cast<LayerTevOrderCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7_2)->map = arg2;
        reinterpret_cast<LayerTevOrderCache*>(reinterpret_cast<u8*>(gsgfxState) + temp_r7_2)->color = arg3;
    }
}

__declspec(weak) void GSgfx_GCSetMatColor(s32 arg0, u32 *arg1) {
    u32 sp8;
    s32 temp_r11;
    u32 temp_r9;

    temp_r11 = (arg0 - 4) * 5;
    if (((u32) layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r11 + 0x4C3), 0) != (u32) *arg1) || ((u8) layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0x4C2) == 1)) {
        temp_r9 = *arg1;
        sp8 = temp_r9;
        *(volatile u8*)0xCC008000 = 0x10;
        *(volatile u16*)0xCC008000 = 0;
        *(volatile u16*)0xCC008000 = (s16) ((arg0 & 1) + 0x100C);
        *(volatile u32*)0xCC008000 = (s32) (layerField<u8>(&sp8,3) | (((((layerField<u8>(&sp8,1) << 0x10) & ~0xFF000000) | (layerField<u8>(&sp8,0) << 0x18)) & ~0xFF00) | ((layerField<u8>(&sp8,2) << 8) & 0xFF00)));
        layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r11 + 0x4C3), 0) = temp_r9;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0x4C2) = 0;
    }
}

__declspec(weak) void GSgfx_GCSetAmbColor(s32 arg0, u32 *arg1) {
    u32 sp8;
    s32 temp_r11;
    u32 temp_r9;

    temp_r11 = (arg0 - 4) * 5;
    if (((u32) layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r11 + 0x4B9), 0) != (u32) *arg1) || ((u8) layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0x4B8) == 1)) {
        temp_r9 = *arg1;
        sp8 = temp_r9;
        *(volatile u8*)0xCC008000 = 0x10;
        *(volatile u16*)0xCC008000 = 0;
        *(volatile u16*)0xCC008000 = (s16) ((arg0 & 1) + 0x100A);
        *(volatile u32*)0xCC008000 = (s32) (layerField<u8>(&sp8,3) | (((((layerField<u8>(&sp8,1) << 0x10) & ~0xFF000000) | (layerField<u8>(&sp8,0) << 0x18)) & ~0xFF00) | ((layerField<u8>(&sp8,2) << 8) & 0xFF00)));
        layerField<u32>(reinterpret_cast<u8*>(gsgfxState) + (temp_r11 + 0x4B9), 0) = temp_r9;
        layerField<u8>(reinterpret_cast<u8*>(gsgfxState) + temp_r11, 0x4B8) = 0;
    }
}

__declspec(weak) void GSgfx_GCSetChanCtrl(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_r12;
    s32 temp_r12_2;
    s32 var_r27;
    u8 *temp_r10;
    u8 *temp_r11;

    temp_r12 = arg0 * 0x18;
    temp_r11 = reinterpret_cast<u8*>(gsgfxState) + 0x458;
    if (((u8) layerField<u8>(temp_r11 + temp_r12, 0) != arg1) || (temp_r10 = reinterpret_cast<u8*>(gsgfxState) + temp_r12, (((s32) layerField<s32>(temp_r10, 0x45C) == arg2) == 0)) || (arg3 != (s32) layerField<s32>(temp_r10, 0x460)) || (arg4 != (s32) layerField<s32>(temp_r10, 0x464)) || (arg5 != (s32) layerField<s32>(temp_r10, 0x468)) || (arg6 != (s32) layerField<s32>(temp_r10, 0x46C))) {
        var_r27 = arg5;
        if (arg6 == 0) {
            var_r27 = 0;
        }
        *(volatile u8*)0xCC008000 = 0x10;
        *(volatile u16*)0xCC008000 = 0;
        *(volatile u16*)0xCC008000 = (s16) ((arg0 & 3) + 0x100E);
        temp_r12_2 = arg0 * 0x18;
        *(volatile u32*)0xCC008000 = (s32) (((arg4 << 7) & 0x7800) | ((((u32) (-arg6 | arg6) >> 0x15U) & 0x400) | ((((u32) ((2 - arg6) | (arg6 - 2)) >> 0x16U) & 0x200) | ((arg2 << 6) | (((arg4 * 4) & 0x3C) | (arg3 | ((arg1 * 2) & 0x1FE))) | (var_r27 << 7)))));
        layerField<u8>(temp_r11 + temp_r12_2, 0) = arg1;
        layerField<s32>(reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0x45C) = arg2;
        layerField<s32>(reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0x460) = arg3;
        layerField<s32>(reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0x464) = arg4;
        layerField<s32>(reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0x468) = arg5;
        layerField<s32>(reinterpret_cast<u8*>(gsgfxState) + temp_r12_2, 0x46C) = arg6;
    }
}

__declspec(weak) void GSgfx_GCSetScissor(u16 arg0, u16 arg1, u16 arg2, u16 arg3, s32 arg4, s32 arg5) {
    if (((u16) reinterpret_cast<LayerScissorCache*>(gsgfxState)->x != arg0) || ((u16) reinterpret_cast<LayerScissorCache*>(gsgfxState)->y != arg1) || ((u16) reinterpret_cast<LayerScissorCache*>(gsgfxState)->width != arg2) || ((u16) reinterpret_cast<LayerScissorCache*>(gsgfxState)->height != arg3) || ((s32) reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetX != arg4) || ((s32) reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetY != arg5)) {
        layerField<u32>(gsgfxState, 0x4C) = (u32) ((layerField<u32>(gsgfxState, 0x4C) & ~0xFFF000) | (((arg0 + (arg4 + 0x156)) << 0xC) & 0xFFF000));
        layerField<u16>(gsgfxState, 0x4E) = (u16) ((layerField<u16>(gsgfxState, 0x4E) & ~0xFFF) | ((u16) (arg1 + (arg5 + 0x156)) & 0xFFF));
        layerField<u32>(gsgfxState, 0x50) = (s32) ((layerField<u32>(gsgfxState, 0x50) & ~0xFFF000) | ((((((u32) layerField<u32>(gsgfxState, 0x4C) >> 0xCU) & 0xFFF) + (arg2 - 1)) << 0xC) & 0xFFF000));
        layerField<u16>(gsgfxState, 0x52) = (u16) ((layerField<u16>(gsgfxState, 0x52) & ~0xFFF) | (((layerField<u16>(gsgfxState, 0x4E) & 0xFFF) + (arg3 - 1)) & 0xFFF));
        layerField<s32>(gsgfxState, 0x0) = (s32) (layerField<s32>(gsgfxState, 0x0) | 0x4000);
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->x = arg0;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->y = arg1;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->width = arg2;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->height = arg3;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetX = arg4;
        reinterpret_cast<LayerScissorCache*>(gsgfxState)->offsetY = arg5;
    }
}

__declspec(weak) void GSgfx_GCSetProjection(s32 arg0, u8 *arg1) {
    u8 var_r9;
    u8 *temp_r6;
    u8 *temp_r8;

    if (arg0 != (s32) layerField<s32>(gsgfxState, 0x41C)) {
        var_r9 = 1;
    } else {
        var_r9 = 0;
        if ((u32) layerField<u32>(gsgfxState, 0x420) != (u32) layerField<u32>(arg1, 0x0)) {
            var_r9 = 1;
        } else {
            temp_r6 = reinterpret_cast<u8*>(gsgfxState) + 0x424;
            if ((u32) layerField<u32>(gsgfxState, 0x424) != (u32) layerField<u32>(arg1, 0x4)) {
                var_r9 = 1;
            } else {
                temp_r8 = arg1 + 8;
                if ((u32) layerField<u32>(temp_r6, 0x4) != (u32) layerField<u32>(arg1, 0x8)) {
                    var_r9 = 1;
                } else if ((u32) layerField<u32>(temp_r6, 0x8) != (u32) layerField<u32>(temp_r8, 0x4)) {
                    var_r9 = 1;
                } else if ((u32) layerField<u32>(temp_r6, 0xC) != (u32) layerField<u32>(temp_r8, 0x8)) {
                    var_r9 = 1;
                } else if ((u32) layerField<u32>(temp_r6, 0x10) != (u32) layerField<u32>(temp_r8, 0xC)) {
                    var_r9 = 1;
                }
            }
        }
    }
    if (var_r9 == 1) {
        *(volatile u8*)0xCC008000 = 0x10;
        *(volatile u16*)0xCC008000 = 6;
        *(volatile u16*)0xCC008000 = 0x1020;
        *(volatile float*)0xCC008000 = layerField<float>(arg1, 0x0);
        *(volatile float*)0xCC008000 = layerField<float>(arg1, 0x4);
        *(volatile float*)0xCC008000 = layerField<float>(arg1, 0x8);
        *(volatile float*)0xCC008000 = (f32) layerField<f32>(arg1, 0xC);
        *(volatile float*)0xCC008000 = (f32) layerField<f32>(arg1, 0x10);
        *(volatile float*)0xCC008000 = (f32) layerField<f32>(arg1, 0x14);
        *(volatile u32*)0xCC008000 = arg0;
        layerField<s32>(gsgfxState, 0x41C) = arg0;
        layerField<s32>(gsgfxState, 0x420) = (u32) layerField<u32>(arg1, 0x0);
        layerField<s32>(gsgfxState, 0x424) = (u32) layerField<u32>(arg1, 0x4);
        layerField<s32>(gsgfxState, 0x428) = (u32) layerField<u32>(arg1, 0x8);
        layerField<u32>(gsgfxState, 0x42C) = layerField<u32>(arg1, 0xC);
        layerField<u32>(gsgfxState, 0x430) = layerField<u32>(arg1, 0x10);
        layerField<u32>(gsgfxState, 0x434) = layerField<u32>(arg1, 0x14);
    }
}

}

#undef LAYER_STATE_FIELD
