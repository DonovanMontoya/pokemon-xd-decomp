#include <game/pxdvs/app/menu/menuOffScreenPrivate.hpp>
#include <dolphin/gx.h>
#include <libc/string.h>
extern "C" {
f32 GSgfxVideoGetLastRenderTime();
u8 GSgfxVideoGetVsyncRate();
GSgfxLayer *GSgfxLayerFindByID(s32);
GSgfxVF *GSgfxVFGetPredef(s32);
void GSmtx44Ortho(f32 *,f32,f32,f32,f32,f32,f32);
GStexture *GStextureCreate(s32,s32,u32,void *,u32);
void GStextureFree(GStexture *);
void GSgfxBeginBackFBCapture(GStexture *,s32 (*)(GStexture *,unsigned long,void *),void *);
void GSthreadSwitch();
extern Mtx mtxIdent;
}
static u8 _menuOffScreenPrio=1;
static u8 _onoff=1;
static u8 _menuOffScreenEnable;
static u8 _menuOffScreenUsing;
static u8 _menuOffScreenDisp;
static u8 _menuOffScreenType;
static GStexture *_menuOffScreenTex;
static f32 _menuOffScreenStartRate;
static f32 _menuOffScreenCurrRate;
static f32 _menuOffScreenEndRate;
static f32 _menuOffScreenTime;
static f32 _menuOffScreenCnt;
static s32 _menuCBOffScreen(GStexture *,unsigned long,void *);
extern "C" {
void menuOffScreenDraw() {
    if (_onoff != 0) {
        if (_menuOffScreenType != 0) {
            u8 rate=GSgfxVideoGetVsyncRate();
            _menuOffScreenCnt += GSgfxVideoGetLastRenderTime()/static_cast<f32>(rate);
            if (_menuOffScreenCnt >= _menuOffScreenTime) { _menuOffScreenCnt=_menuOffScreenTime;_menuOffScreenType=0; }
        }
        if (_menuOffScreenDisp != 0 && _menuOffScreenEnable != 0) {
            _menuOffScreenCurrRate=(_menuOffScreenCnt/_menuOffScreenTime)*(_menuOffScreenEndRate-_menuOffScreenStartRate)+_menuOffScreenStartRate;
            u8 alpha=static_cast<s32>(255.0f-(255.0f*_menuOffScreenCurrRate)/100.0f);
            s32 layerID;
            if (_menuOffScreenPrio != 0) layerID=7; else layerID=0;
            GSgfxLayer *layer=GSgfxLayerFindByID(layerID);
            if (layer != 0) {
                if (layer->blendSelection == 0) {
                    if (layer->blendIndex != 0) { layer->blendIndex=0;layer->currentBlend=&layer->blendRecords[layer->blendIndex]; }
                    layer->blendMode=0;layer->blendSource=1;layer->blendDestination=1;layer->logicOperation=5;
                    layer->pixelDirty|=1;layer->dirty|=0x40;layer->savedPixelDirty|=1;layer->savedDirty|=0x40;
                } else {
                    if (layer->blendIndex != 1) { layer->blendIndex=1;layer->currentBlend=&layer->blendRecords[layer->blendIndex]; }
                    layer->blendMode=1;layer->blendSource=1;layer->blendDestination=0;layer->logicOperation=5;
                    layer->pixelDirty|=1;layer->dirty|=0x40;layer->savedPixelDirty|=1;layer->savedDirty|=0x40;
                }
                f32 projection[16];
                GSmtx44Ortho(projection,0.0f,480.0f,0.0f,640.0f,0.0f,-30000.0f);
                layer->projectionType=1;
                layer->projectionParameters[0]=projection[0];
                layer->projectionParameters[1]=projection[3];
                layer->projectionParameters[2]=projection[5];
                layer->projectionParameters[3]=projection[7];
                layer->projectionParameters[4]=projection[10];
                layer->projectionParameters[5]=projection[11];
                GSgfxMatrixStack *stack=layer->matrixStack;
                memcpy(stack->current->matrix,mtxIdent,sizeof(Mtx));
                stack->current->flags|=1;
                layer->fogNear=0.0f;layer->fogFar=30000.0f;
                if (layer->fogEnabled != 0) {
                    if (layer->fogRangeEnabled != 0) { layer->pixelDirty|=0x100;layer->savedPixelDirty|=0x100; }
                    layer->pixelDirty|=0x40;layer->dirty|=0x40;layer->savedPixelDirty|=0x40;layer->savedDirty|=0x40;
                }
                layer->lineDirty|=0x20;layer->dirty|=1;layer->savedLineDirty|=0x20;layer->savedDirty|=1;
                layer->colorUpdate=1;layer->alphaUpdate=1;layer->depthBeforeTexture=0;
                layer->pixelDirty|=4;layer->dirty|=0x40;layer->savedPixelDirty|=4;layer->savedDirty|=0x40;
                layer->depthEnable=0;layer->depthCompare=3;
                layer->pixelDirty|=8;layer->dirty|=0x40;layer->savedPixelDirty|=8;layer->savedDirty|=0x40;
                layer->cullMode=0;layer->cullDirty|=2;layer->dirty|=2;layer->savedCullDirty|=2;layer->savedDirty|=2;
                layer->primitiveType=0x98;
                layer->setRenderStateAndSelect(GSgfxVFGetPredef(7));
                if (layer->textures[0] != reinterpret_cast<TextureRecord *>(_menuOffScreenTex) || layer->savedTextures[0] != reinterpret_cast<TextureRecord *>(_menuOffScreenTex) || reinterpret_cast<TextureRecord *>(_menuOffScreenTex)->dirty != 0) {
                    layer->textures[0]=reinterpret_cast<TextureRecord *>(_menuOffScreenTex);layer->textureDirty|=1;
                    layer->savedTextures[0]=reinterpret_cast<TextureRecord *>(_menuOffScreenTex);layer->savedTextureDirty|=1;
                }
                layer->beginSurface(4);
                GXWGFifo.s16=0;GXWGFifo.s16=0;
                GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=255;
                GXWGFifo.f32=0.0f;GXWGFifo.f32=0.0f;
                GXWGFifo.s16=640;GXWGFifo.s16=0;
                GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=255;
                GXWGFifo.f32=1.0f;GXWGFifo.f32=0.0f;
                GXWGFifo.s16=0;GXWGFifo.s16=480;
                GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=255;
                GXWGFifo.f32=0.0f;GXWGFifo.f32=1.0f;
                GXWGFifo.s16=640;GXWGFifo.s16=480;
                GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=alpha;GXWGFifo.u8=255;
                GXWGFifo.f32=1.0f;GXWGFifo.f32=1.0f;
                layer->endSurface();
            }
        }
    }
}
s32 menuOffScreenFadeSync(u8 wait) { while(wait!=0 && _menuOffScreenType!=0) GSthreadSwitch();return _menuOffScreenType!=0; }
void menuOffScreenFadeSet(f32 end,f32 time) {
    _menuOffScreenType=1;_menuOffScreenStartRate=_menuOffScreenCurrRate;_menuOffScreenEndRate=end;_menuOffScreenCurrRate=0.0f;
    _menuOffScreenTime=time;_menuOffScreenCnt=0.0f;
    if(time==0.0f) { _menuOffScreenTime=1.0f;_menuOffScreenCnt=1.0f; }
}
u8 menuOffScreenSetPriority(u8 priority) { u8 previous=_menuOffScreenPrio;_menuOffScreenPrio=priority;return previous; }
u8 menuOffScreenSetDisp(u8 display) { u8 previous=_menuOffScreenDisp;_menuOffScreenDisp=display;return previous; }
u8 menuOffScreenIsDoing() { return _menuOffScreenUsing; }
GStexture *menuOffScreenGetPtr() { return _menuOffScreenTex; }
u8 menuOffScreenCheckEnable(u8 wait) { while(wait!=0 && _menuOffScreenEnable==0) GSthreadSwitch();return _menuOffScreenEnable; }
void menuOffScreenRelease() {
    _menuOffScreenType=0;_menuOffScreenUsing=0;_menuOffScreenEnable=0;_menuOffScreenDisp=0;
    if(_menuOffScreenTex!=0) { GStextureFree(_menuOffScreenTex);_menuOffScreenTex=0; }
}
void menuOffScreenCreate(u8 wait) {
    _menuOffScreenType=0;_menuOffScreenUsing=1;_menuOffScreenEnable=0;_menuOffScreenDisp=0;
    _menuOffScreenStartRate=0.0f;_menuOffScreenCurrRate=0.0f;_menuOffScreenEndRate=0.0f;_menuOffScreenTime=0.0f;_menuOffScreenCnt=0.0f;
    if(_menuOffScreenTex==0) _menuOffScreenTex=GStextureCreate(0,0,0x44,0,0);
    GSgfxBeginBackFBCapture(_menuOffScreenTex,_menuCBOffScreen,0);
    menuOffScreenCheckEnable(wait);
}
void menuOffScreenInit() {
    _menuOffScreenUsing=0;_menuOffScreenEnable=0;_menuOffScreenDisp=0;_menuOffScreenPrio=1;_menuOffScreenType=0;
    _menuOffScreenTime=0.0f;_menuOffScreenCnt=0.0f;_menuOffScreenStartRate=0.0f;_menuOffScreenCurrRate=0.0f;_menuOffScreenEndRate=0.0f;
}
}
static s32 _menuCBOffScreen(GStexture *,unsigned long,void *) { _menuOffScreenEnable=1;return 0; }
