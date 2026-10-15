#include <game/pxdvs/GSAPI/GSgfxM/layerEffectPrivate.hpp>

GStexture* GSgfxLayer::fbTexPtr;
GStexture* GSgfxLayer::distTexPtr;
s16 GSgfxLayer::fbTexRefCount;
s16 GSgfxLayer::distTexRefCount;

void GSgfxLayer::textureCopy(GSgfxLayerPass selected,GStexture* texture,bool mipmap,u8* filter,bool clearColor,bool clearDepth,bool clearAlpha) {
    if(pass!=selected) {
        pass=selected;
        currentPass=&passes[pass];
    }
    EffectTextureCopy(texture,mipmap,filter,clearColor,clearDepth,clearAlpha);
}
void GSgfxLayer::PrepareDistortion() {
    const GXColor black={0,0,0,0};
    if(!(flags&0x200) || frameBufferTexture!=fbTexPtr) {
        if(pass!=1) {
            pass=1;
            currentPass=&passes[pass];
        }
        copyState[0]=2;copyState[1]=2;copyState[2]=2;copyState[3]=3;
        copyDirty|=1;dirty|=0x20;savedCopyDirty|=1;savedDirty|=0x20;
        GXColor color=savedClearColor;
        GSgfxVideoGetClearColor(&color);
        GXColor clear=black;
        GSgfxVideoSetClearColor(&clear);
        EffectTextureCopy(fbTexPtr,false,0,true,true,false);
    }
}
void GSgfxLayer::PrepareFBCopy() {
    if(!(flags&0x200) || frameBufferTexture!=fbTexPtr) {
        if(pass!=1) {
            pass=1;
            currentPass=&passes[pass];
        }
        EffectTextureCopy(fbTexPtr,false,0,false,false,false);
    }
}


#include <libc/string.h>
struct CopyTex {s16 left,top;u16 width,height,destWidth;u16 reserved;s32 format,mode;u8 mipmap,clear;};
struct RenderMode {u8 reserved[0x19];u8 aa;u8 samples[12][2];};
static u8 _layerTexCopyDefaultFilter[7]={8,8,10,12,10,8,8};
extern "C" {
extern Mtx mtxIdent;
void FlushState__10GSgfxLayerFv(GSgfxLayer*);
GSgfxVF* GSgfxVFGetPredef(u32);
void GSgfxVideoGetEFBSize(u16*,u16*);
RenderMode* GSgfxVideoGetRenderMode__Fv();
void GSgfxVideoResetViewport__Fb(bool);
void GSgfx_GCWriteCopyFilter(u8,u8 (*)[2],u8,const u8*);
void GSgfx_GCWriteCopyTex(const CopyTex*,void*);
void GSmtx44Ortho(Mtx44,f32,f32,f32,f32,f32,f32);
void beginSurface__10GSgfxLayerFUs(GSgfxLayer*,u16);
void endSurface__10GSgfxLayerFv(GSgfxLayer*);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(GSgfxLayer*,GSgfxVF*);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(GSgfxLayer*,u8,s32,s32,void*,bool,void*);
void tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(GSgfxLayer*,s32,f32 (*)[3],s8);
}

void GSgfxLayer::EffectTextureCopy(GStexture *arg1, bool arg2, u8 *arg3, bool arg4, bool arg5, bool arg6) {
    CopyTex copy;
    u16 width,height;
    bool clear;
    RenderMode *renderMode;
    u8 savedColorUpdate,savedAlphaUpdate,savedDepthBeforeTexture,savedDepthEnable;
    s32 savedDepthCompare;

    switch(arg1->format) {
    case 0x40: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45:
    case 0x90: case 0xA0: case 0xA1: case 0xA2: case 0xA3:
        renderMode = GSgfxVideoGetRenderMode__Fv();
        GSgfxVideoGetEFBSize(&width, &height);
        width=arg1->width<width?arg1->width:width;
        height=arg1->height<height?arg1->height:height;
        clear = 0;
        if ((arg4 != 0) || (arg5 != 0) || (arg6 != 0)) {
            clear = 1;
        }
        if (clear == 1) {
            savedDepthCompare = this->depthCompare;
            savedColorUpdate = this->colorUpdate != 0;
            savedAlphaUpdate = this->alphaUpdate != 0;
            savedDepthBeforeTexture = this->depthBeforeTexture != 0;
            savedDepthEnable = this->depthEnable != 0;
            if (arg4 == 1) {
                this->colorUpdate = 1;
            } else {
                this->colorUpdate = 0;
            }
            if (arg5 == 1) {
                this->alphaUpdate = 1;
            } else {
                this->alphaUpdate = 0;
            }
            if (arg6 == 1) {
                this->depthBeforeTexture = 1;
            } else {
                this->depthBeforeTexture = 0;
            }
            this->pixelDirty |= 4;
            this->dirty |= 0x40;
            this->savedPixelDirty |= 4;
            this->savedDirty |= 0x40;
            this->depthEnable = 1;
            this->depthCompare = 7;
            this->pixelDirty |= 8;
            this->dirty |= 0x40;
            this->savedPixelDirty |= 8;
            this->savedDirty |= 0x40;
        }
        FlushState__10GSgfxLayerFv(this);
        if (arg2 != 0) {
            if (arg3 == 0) {
                GSgfx_GCWriteCopyFilter(renderMode->aa, (u8 (*)[2]) renderMode->samples[0], 1U, _layerTexCopyDefaultFilter);
            } else {
                GSgfx_GCWriteCopyFilter(renderMode->aa, (u8 (*)[2]) renderMode->samples[0], 1U, arg3);
            }
        } else {
            GSgfx_GCWriteCopyFilter(renderMode->aa, (u8 (*)[2]) renderMode->samples[0], 0U, 0);
        }
        copy.left = 0;
        copy.top = 0;
        copy.width = width;
        copy.height = height;
        copy.destWidth = width;
        copy.format = GStextureGetGXformat(arg1, 0U);
        copy.mode = 3;
        copy.mipmap = 0;
        copy.clear = clear;
        GSgfx_GCWriteCopyTex(&copy, arg1->images[0]);
        if (clear == 1) {
            if (savedColorUpdate == 1) {
                this->colorUpdate = 1;
            } else {
                this->colorUpdate = 0;
            }
            if (savedAlphaUpdate == 1) {
                this->alphaUpdate = 1;
            } else {
                this->alphaUpdate = 0;
            }
            if (savedDepthBeforeTexture == 1) {
                this->depthBeforeTexture = 1;
            } else {
                this->depthBeforeTexture = 0;
            }
            this->pixelDirty |= 4;
            this->dirty |= 0x40;
            this->savedPixelDirty |= 4;
            this->savedDirty |= 0x40;
            if (savedDepthEnable == 1) {
                this->depthEnable = 1;
            } else {
                this->depthEnable = 0;
            }
            this->depthCompare = savedDepthCompare;
            this->pixelDirty |= 8;
            this->dirty |= 0x40;
            this->savedPixelDirty |= 8;
            this->savedDirty |= 0x40;
        }
        this->flags |= 0x30000000;
        break;
    }
}

void GSgfxLayer::EffectScreenClear(bool arg1, bool arg2, bool arg3) {
    Mtx44 projection;
    LayerMatrixFrame *temp_r3;
    LayerMatrixStack *temp_r30;

    if ((arg1 != 0) || (arg2 != 0) || (arg3 != 0)) {
        if (arg1 == 1) {
            this->colorUpdate = 1;
        } else {
            this->colorUpdate = 0;
        }
        if (arg2 == 1) {
            this->alphaUpdate = 1;
        } else {
            this->alphaUpdate = 0;
        }
        if (arg3 == 1) {
            this->depthBeforeTexture = 1;
        } else {
            this->depthBeforeTexture = 0;
        }
        this->pixelDirty |= 4;
        this->dirty |= 0x40;
        this->savedPixelDirty |= 4;
        this->savedDirty |= 0x40;
        GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
        this->projectionType = 1;
        this->projectionScaleX = projection[0][0];
        this->projectionOffsetX = projection[0][3];
        this->projectionScaleY = projection[1][1];
        this->projectionOffsetY = projection[1][3];
        this->projectionScaleZ = projection[2][2];
        this->projectionOffsetZ = projection[2][3];
        temp_r30 = this->matrixStack;
        memcpy(temp_r30->frame->matrix[0], mtxIdent, 0x30U);
        temp_r3 = temp_r30->frame;
        temp_r3->flags |= 1;
        this->depthRangeNear = 0.0f;
        this->depthRangeFar = 30000.0f;
        if ((u8) this->projectionDepthEnabled != 0) {
            if ((u8) this->projectionDepthDirty != 0) {
                this->pixelDirty |= 0x100;
                this->savedPixelDirty |= 0x100;
            }
            this->pixelDirty |= 0x40;
            this->dirty |= 0x40;
            this->savedPixelDirty |= 0x40;
            this->savedDirty |= 0x40;
        }
        this->unk16AC |= 0x20;
        this->dirty |= 1;
        this->unk1764 |= 0x20;
        this->savedDirty |= 1;
        this->blendMode = 0;
        this->blendSource = 1;
        this->blendDestination = 1;
        this->logicOperation = 5;
        this->pixelDirty |= 1;
        this->dirty |= 0x40;
        this->savedPixelDirty |= 1;
        this->savedDirty |= 0x40;
        this->depthEnable = 0;
        this->depthCompare = 3;
        this->pixelDirty |= 8;
        this->dirty |= 0x40;
        this->savedPixelDirty |= 8;
        this->savedDirty |= 0x40;
        this->unk1664 = 7;
        this->unk1670 = 0;
        this->unk1668 = 0;
        this->unk166C = 7;
        this->unk1671 = 0;
        this->unk1672 = 1;
        this->pixelDirty |= 0x10;
        this->dirty |= 0x40;
        this->savedPixelDirty |= 0x10;
        this->savedDirty |= 0x40;
        this->unkD8C = 0;
        this->unk16B8 |= 2;
        this->dirty |= 2;
        this->unk1770 |= 2;
        this->savedDirty |= 2;
        this->unkD90 = 1;
        this->unk16B8 |= 4;
        this->dirty |= 2;
        this->unk1770 |= 4;
        this->savedDirty |= 2;
        setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(this, GSgfxVFGetPredef(0U));
        this->primitiveType = 0x98;
        beginSurface__10GSgfxLayerFUs(this, 4U);
        f32 zero=0.0f, depth=29999.0f, width=640.0f, height=480.0f;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = depth;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile f32 *)0xCC008000 = width;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = depth;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile f32 *)0xCC008000 = zero;
        *(volatile f32 *)0xCC008000 = height;
        *(volatile f32 *)0xCC008000 = depth;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile f32 *)0xCC008000 = width;
        *(volatile f32 *)0xCC008000 = height;
        *(volatile f32 *)0xCC008000 = depth;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        *(volatile u8 *)0xCC008000 = 0;
        endSurface__10GSgfxLayerFv(this);
    }
}

void GSgfxLayer::EffectDistortion() {
    GXColor color;
    Mtx44 projection;
    LayerMatrixFrame *temp_r3;
    LayerMatrixStack *temp_r30;

    if ((u8) this->projectionDepthEnabled != 0) {
        this->projectionDepthEnabled = 0;
        this->pixelDirty |= 0x40;
        this->savedPixelDirty |= 0x40;
        this->dirty |= 0x40;
        this->savedDirty |= 0x40;
    }
    if ((s32) this->pass != 1) {
        this->pass = 1;
        this->currentPass = &this->passes[this->pass];
    }
    EffectTextureCopy(distTexPtr, true, 0, false, false, false);
    GSgfxVideoResetViewport__Fb(1U);
    this->copyState[0] = 0;
    this->copyState[1] = 1;
    this->copyState[2] = 2;
    this->copyState[3] = 3;
    this->copyDirty |= 1;
    this->dirty |= 0x20;
    this->savedCopyDirty |= 1;
    this->savedDirty |= 0x20;
    this->unkD8C = 2;
    this->unk16B8 |= 2;
    this->dirty |= 2;
    this->unk1770 |= 2;
    this->savedDirty |= 2;
    this->blendMode = 0;
    this->blendSource = 1;
    this->blendDestination = 1;
    this->logicOperation = 5;
    this->pixelDirty |= 1;
    this->dirty |= 0x40;
    this->savedPixelDirty |= 1;
    this->savedDirty |= 0x40;
    this->colorUpdate = 1;
    this->alphaUpdate = 0;
    this->depthBeforeTexture = 0;
    this->pixelDirty |= 4;
    this->dirty |= 0x40;
    this->savedPixelDirty |= 4;
    this->savedDirty |= 0x40;
    this->depthEnable = 0;
    this->depthCompare = 3;
    this->pixelDirty |= 8;
    this->dirty |= 0x40;
    this->savedPixelDirty |= 8;
    this->savedDirty |= 0x40;
    this->unk1664 = 7;
    this->unk1670 = 0;
    this->unk1668 = 0;
    this->unk166C = 7;
    this->unk1671 = 0;
    this->unk1672 = 1;
    this->pixelDirty |= 0x10;
    this->dirty |= 0x40;
    this->savedPixelDirty |= 0x10;
    this->savedDirty |= 0x40;
    this->unkD90 = 0;
    this->unk16B8 |= 4;
    this->dirty |= 2;
    this->unk1770 |= 4;
    this->savedDirty |= 2;
    this->unkC70 = 1;
    this->unk16AC |= 1;
    this->dirty |= 1;
    this->unk1764 |= 1;
    this->savedDirty |= 1;
    tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(this, 0U, 1, 4, 0, 0U, 0);
    this->unkEAC = 1;
    this->unk16CC |= 1;
    this->dirty |= 8;
    this->unk1784 |= 1;
    this->savedDirty |= 8;
    this->unk14B0 = 1;
    this->unk16EC |= 1;
    this->dirty |= 0x80;
    this->unk17A4 |= 1;
    this->savedDirty |= 0x80;
    this->unkDB8 = 0;
    this->unk16BC |= 1;
    this->dirty |= 4;
    this->unk1774 |= 1;
    this->savedDirty |= 4;
    this->unk14B4 = 0;
    this->unk14B8 = 1;
    this->unk16F0 |= 1;
    this->dirty |= 0x80;
    this->unk17A8 |= 1;
    this->savedDirty |= 0x80;
    this->unk14D4 = 0;
    this->unk14D8 = 0;
    this->unk16F4 |= 1;
    this->dirty |= 0x80;
    this->unk17AC |= 1;
    this->savedDirty |= 0x80;
    tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(this, 1, (f32 (*)[3]) this->distortionMatrix[0], this->distortionExponent);
    this->unk1420 = 2;
    this->unk1424 = 0;
    this->unk1425 = 0;
    this->unk1426 = 0;
    this->unk1428 = 1;
    this->unk16E8 |= 1;
    this->dirty |= 8;
    this->unk17A0 |= 1;
    this->savedDirty |= 8;
    this->unkEB0 = 0;
    this->unkEB4 = 0;
    this->unkEB8 = 0xFF;
    this->unk16D0 |= 1;
    this->dirty |= 8;
    this->unk1788 |= 1;
    this->savedDirty |= 8;
    this->unk1170 = 0;
    this->unk1174 = 0;
    this->unk1178 = 0;
    this->unk117C = 0;
    this->unk1180 = 0;
    this->unk16DC |= 1;
    this->dirty |= 8;
    this->unk1794 |= 1;
    this->savedDirty |= 8;
    this->unk12B0 = 0;
    this->unk12B4 = 0;
    this->unk12B8 = 0;
    this->unk12BC = 0;
    this->unk12C0 = 0;
    this->unk16E0 |= 1;
    this->dirty |= 8;
    this->unk1798 |= 1;
    this->savedDirty |= 8;
    this->unkF70 = 0xF;
    this->unkF74 = 0xF;
    this->unkF78 = 0xF;
    this->unkF7C = 8;
    this->unk16D4 |= 1;
    this->dirty |= 8;
    this->unk178C |= 1;
    this->savedDirty |= 8;
    this->unk1070 = 7;
    this->unk1074 = 7;
    this->unk1078 = 7;
    this->unk107C = 7;
    this->unk16D8 |= 1;
    this->dirty |= 8;
    this->unk1790 |= 1;
    this->savedDirty |= 8;
    GStexture* texture=fbTexPtr;
    if (((GStexture *) this->texture0 != (GStexture *) texture) || ((GStexture *) this->savedTexture0 != (GStexture *) texture) || ((u8) texture->dirty != 0)) {
        this->texture0 = texture;
        this->textureDirty |= 1;
        this->savedTexture0 = texture;
        this->savedTextureDirty |= 1;
    }
    texture=distTexPtr;
    if (((GStexture *) this->texture1 != (GStexture *) texture) || ((GStexture *) this->savedTexture1 != (GStexture *) texture) || ((u8) texture->dirty != 0)) {
        this->texture1 = texture;
        this->textureDirty |= 2;
        this->savedTexture1 = texture;
        this->savedTextureDirty |= 2;
    }
    this->vertexFormat = GSgfxVFGetPredef(8U);
    GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    this->projectionType = 1;
    this->projectionScaleX = projection[0][0];
    this->projectionOffsetX = projection[0][3];
    this->projectionScaleY = projection[1][1];
    this->projectionOffsetY = projection[1][3];
    this->projectionScaleZ = projection[2][2];
    this->projectionOffsetZ = projection[2][3];
    temp_r30 = this->matrixStack;
    memcpy(temp_r30->frame->matrix[0], mtxIdent, 0x30U);
    temp_r3 = temp_r30->frame;
    temp_r3->flags |= 1;
    this->depthRangeNear = 0.0f;
    this->depthRangeFar = 30000.0f;
    if ((u8) this->projectionDepthEnabled != 0) {
        if ((u8) this->projectionDepthDirty != 0) {
            this->pixelDirty |= 0x100;
            this->savedPixelDirty |= 0x100;
        }
        this->pixelDirty |= 0x40;
        this->dirty |= 0x40;
        this->savedPixelDirty |= 0x40;
        this->savedDirty |= 0x40;
    }
    this->unk16AC |= 0x20;
    this->dirty |= 1;
    this->unk1764 |= 0x20;
    this->savedDirty |= 1;
    this->primitiveType = 0x98;
    beginSurface__10GSgfxLayerFUs(this, 4U);
    *(volatile s16 *)0xCC008000 = 0;
    *(volatile s16 *)0xCC008000 = 0;
    *(volatile u8 *)0xCC008000 = 0;
    *(volatile u8 *)0xCC008000 = 0;
    *(volatile s16 *)0xCC008000 = 0x280;
    *(volatile s16 *)0xCC008000 = 0;
    *(volatile u8 *)0xCC008000 = 1;
    *(volatile u8 *)0xCC008000 = 0;
    *(volatile s16 *)0xCC008000 = 0;
    *(volatile s16 *)0xCC008000 = 0x1E0;
    *(volatile u8 *)0xCC008000 = 0;
    *(volatile u8 *)0xCC008000 = 1;
    *(volatile s16 *)0xCC008000 = 0x280;
    *(volatile s16 *)0xCC008000 = 0x1E0;
    *(volatile u8 *)0xCC008000 = 1;
    *(volatile u8 *)0xCC008000 = 1;
    endSurface__10GSgfxLayerFv(this);
    this->unk14B0 = 0;
    this->unk16EC |= 1;
    this->dirty |= 0x80;
    this->unk17A4 |= 1;
    this->savedDirty |= 0x80;
    this->unk1420 = 0;
    this->unk16E8 |= 1;
    this->dirty |= 8;
    this->unk17A0 |= 1;
    this->savedDirty |= 8;
    FlushState__10GSgfxLayerFv(this);
    *(u32*)&color = *(u32*)&this->savedClearColor;
    GSgfxVideoSetClearColor(&color);
    GSgfxVideoResetViewport__Fb(0U);
}
