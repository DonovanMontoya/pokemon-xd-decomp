#include <global.h>
#include <libc/string.h>
static u32 _vtrGSgappHdlList[4];
static u8 _vtrEnabled;
static s32 _vtrState,_vtrBlockState;
static u32 _vtrGSgappCount,_vtrSlowPlayFrame;
static u8 _vtrTexDisp,_vtrTexDispBorder;
static void* _vtrTex;
static u8 _vtrGSgfxIsPaused;
static void _vtrUpdateFunc(unsigned long,unsigned long);
static void _vtrTexDispFunc();
extern "C" {
void GSgappUnblock(u32); void GSgappBlock(u32);
u32 GSgappCreate(s32,u8,u32,void(*)(unsigned long,unsigned long));
void GSgappSetName(u32,const char*);
void GSgfxRenderPause(); void GSgfxRenderUnpause();
void* GSresGetResourceAllGroup(u32);
void GSthreadExecuteGroup(u32);
void GSvtrSlowPlay() { _vtrState=4; _vtrBlockState=3; _vtrSlowPlayFrame=0; }
void GSvtrSingleStep() { _vtrState=3; _vtrBlockState=3; }
void GSvtrPlay() { _vtrState=2; _vtrBlockState=3; }
void GSvtrPause() { _vtrState=1; if(_vtrBlockState!=2) _vtrBlockState=1; }
u8 GSvtrGetInfoDisp() { return _vtrTexDisp; }
void GSvtrSetInfoDisp(u8 display,u8 border) { _vtrTexDisp=display; _vtrTexDispBorder=border; }
s32 GSvtrGetState() { return _vtrState; }
u8 GSvtrIsActive() { return _vtrEnabled; }
void GSvtrDisable() {
    u32* handles=_vtrGSgappHdlList;
    _vtrState=0; _vtrEnabled=0;
    for(u32 i=0;i<_vtrGSgappCount;++i,++handles) if(*handles) GSgappUnblock(*handles);
    if(_vtrGSgfxIsPaused==1) { GSgfxRenderUnpause(); _vtrGSgfxIsPaused=0; }
}
void GSvtrEnable() { _vtrEnabled=1; _vtrState=2; _vtrBlockState=3; }
void GSvtrLoadTexture() { _vtrTex=GSresGetResourceAllGroup(0x0ab21200); }
u8 GSvtrRegisterGSgapp(u32 handle) {
    if(_vtrGSgappCount+1>=4) return 0;
    u32* item=_vtrGSgappHdlList;
    for(s32 i=0;i<4;++i,++item) {
        if(!*item) { *item=handle; ++_vtrGSgappCount; return 1; }
    }
    return 0;
}
void GSvtrInit() {
    _vtrEnabled=0; _vtrState=0; _vtrGSgappCount=0; _vtrTex=0; _vtrTexDisp=1;
    memset(_vtrGSgappHdlList,0,sizeof(_vtrGSgappHdlList));
    u32 handle=GSgappCreate(1,0xfd,10,_vtrUpdateFunc);
    GSgappSetName(handle,"GSvtr");
}
}
static void _vtrUpdateFunc(unsigned long,unsigned long) {
    if(_vtrEnabled) {
        _vtrTexDispFunc();
        u8 paused;
        switch(_vtrBlockState) {
        case 0: paused=0; break;
        case 1: {
            _vtrBlockState=2;
            u32* item=_vtrGSgappHdlList;
            for(u32 i=0;i<_vtrGSgappCount;++i,++item) if(*item) GSgappBlock(*item);
            paused=1; break;
        }
        case 2: paused=1; break;
        case 3: {
            u32 i=0;
            _vtrBlockState=0;
            u32* item=_vtrGSgappHdlList;
            for(;i<_vtrGSgappCount;++i,++item) if(*item) GSgappUnblock(*item);
            paused=0; break;
        }
        }
        if(paused!=_vtrGSgfxIsPaused) {
            if(paused==1) GSgfxRenderPause(); else GSgfxRenderUnpause();
            _vtrGSgfxIsPaused=paused;
        }
        switch(_vtrState) {
        case 3: if(_vtrBlockState!=2) _vtrBlockState=1; break;
        case 4: {
            s32 state=2;
            if(_vtrBlockState==0) state=1;
            _vtrBlockState=state;
            if(++_vtrSlowPlayFrame>=5) { _vtrBlockState=3; _vtrSlowPlayFrame=0; }
            break;
        }
        }
        if(_vtrBlockState==2) { GSthreadExecuteGroup(0xe38f910b); GSthreadExecuteGroup(0x175f4322); }
    }
}
struct GSgfxLayer {
    u8 reserved00[0x28]; s32 id; u8 reserved2c[0x1644-0x2c]; u32 blendMode,blendSource,blendDestination,blendLogic;
    u8 reserved1654[0x16a8-0x1654]; u32 dirty;
    u8 reserved16ac[0x170c-0x16ac]; u32 pixelDirty;
    u8 reserved1710[0x1760-0x1710]; u32 savedDirty;
    u8 reserved1764[0x17c4-0x1764]; u32 savedPixelDirty;
    u8 reserved17c8[0x1818-0x17c8]; u8 shaders[2][0xbc]; void* shader; s32 shaderIndex;
};
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(u32);
void GSprimSetup2DRender__FP10GSgfxLayer(GSgfxLayer*);
void GSprimDraw2DQuad(const void*,f32,f32,f32,f32);
void GSprimDraw2DTexQuad(void*,const void*,f32,f32,f32,f32);
void GSprint(s32,s32,s32,s32,const char*,...);
}
static void _vtrTexDispFunc() {
    struct Color {u8 r,g,b,a;};
    Color border={255,0,0,255};
    Color color={255,255,255,255};
    if(_vtrEnabled) {
    if(!_vtrTexDisp) return;
    if(!_vtrTex) return;
    GSgfxLayer* layer=GSgfxLayerFindByID(7);
    if(layer) {
        GSprimSetup2DRender__FP10GSgfxLayer(layer);
        if(layer->shaderIndex!=1) { layer->shaderIndex=1; layer->shader=&layer->shaders[layer->shaderIndex]; }
        layer->blendMode=1; layer->blendSource=1; layer->blendDestination=0; layer->blendLogic=5;
        layer->pixelDirty|=1; layer->dirty|=0x40; layer->savedPixelDirty|=1; layer->savedDirty|=0x40;
        if(_vtrTexDispBorder) { Color c=border; GSprimDraw2DQuad(&c,6,24,634,68); }
        Color c=color; GSprimDraw2DTexQuad(_vtrTex,&c,12,28,628,64);
        switch(_vtrState) {
        case 0: GSprint(layer->id,560,44,-1,"???"); break;
        case 1: GSprint(layer->id,560,44,-1,"Pause"); break;
        case 2: GSprint(layer->id,560,44,-1,"Play"); break;
        case 3:
            switch(_vtrBlockState) {
            case 0: case 1: GSprint(layer->id,560,44,-1,"SStep"); break;
            case 2: case 3: GSprint(layer->id,560,44,-1,"Pause"); break;
            }
            break;
        case 4: GSprint(layer->id,560,44,-1,"Slow"); break;
        }
    }
}
}
