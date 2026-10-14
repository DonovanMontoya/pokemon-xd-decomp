#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
static u8 g_primitiveEditorMode;
static u8 g_moduleInited;
static f32 g_primitiveFrameSec;
static u16 g_primitiveAnimation;
static u16 g_shapeRenderNum;
static GsShapeRender** g_shapeRender;

extern "C" {
u32 shapeGetInstancedMemorySizeAll() { return g_instancedMemorySizeAll; }
u32 shapeGetUsedMemorySize(u16 index) {
    if(index>=g_shapeRenderNum) return 0;
    if(g_shapeRender[index]) return g_shapeRender[index]->GetUsedMemorySizeAll();
    return 0;
}
void shapeFreePrimitiveInstance(u16 index,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->FreeShapeRenderDrawBuffer(instance);
}
s16 shapeCreatePrimitiveInstance(u16 index) {
    if(index>=g_shapeRenderNum) return -1;
    if(g_shapeRender[index]) return g_shapeRender[index]->CreateShapeRenderDrawBuffer();
    return -1;
}
s32 shapeGenerateIndex() {
    for(u16 i=0;i<g_shapeRenderNum;i++) {
        GsShapeRender* render=g_shapeRender[i];
        if(!render) return i;
        if(!render->animation) return i;
    }
    return -1;
}
void shapeRelease(u16 index) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) {
        g_shapeRender[index]->FreeShapeRender(); GSmemFree(g_shapeRender[index]); g_shapeRender[index]=0;
    }
}
void shapeRender(u16 index,s16 instance,GSgfxLayerID layer) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Render(instance,layer);
}
void shapeUpdate(u16 index,f32 seconds,s16 instance) {
    if(index<g_shapeRenderNum && g_shapeRender[index]) g_shapeRender[index]->Update(seconds,instance);
}
bool shapeLoad(u16 index,void* file) {
    if(index>=g_shapeRenderNum) return false;
    if(g_shapeRender[index]) GSmemFree(g_shapeRender[index]);
    g_shapeRender[index]=(GsShapeRender*)GSmemAlloc(sizeof(GsShapeRender));
    if(!g_shapeRender[index]) return false;
    g_shapeRender[index]->InitShapeRender(); g_shapeRender[index]->LoadShapeRender(file);
    return true;
}
}

extern "C" void shapePrimitiveEditorRender(GSgfxLayerID);
extern "C" u32 GSgfxPerfbarCPUEntry(u32);
static void _shapePreUpdate(f32) {
    for(u16 i=0;i<g_shapeRenderNum;i++) {
        if(g_shapeRender[i] && g_shapeRender[i]->animation) g_shapeRender[i]->SwapBuffers();
    }
}
static void _shapeFastRender() {
    if(g_primitiveEditorMode) {
        GSgfxLayerID layer;
        if(!g_primitiveEditorMode) layer=GS_SHAPE_LAYER_DEFAULT;
        else if(g_shapeRenderNum && g_shapeRender[0] && g_shapeRender[0]->animation) layer=g_shapeRender[0]->GetLayerId();
        else layer=GS_SHAPE_LAYER_DEFAULT;
        u32 saved=GSgfxPerfbarCPUEntry(0xFF00);
        shapePrimitiveEditorRender(layer);
        GSgfxPerfbarCPUEntry(saved);
    }
}
struct GsShapeRenderModuleData {
    void (*preRender)(); void (*preUpdate)(f32); void (*render)();
    void (*fastRender)(); void (*postUpdate)(f32); void (*postRender)(); u32 parameter;
};
struct GSgfxRenderModule;
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);
extern "C" bool shapeInit(u16 count) {
    u16 i=0;
    g_primitiveEditorMode=0;
    for(;i<g_shapeRenderNum;i++) {
        if(g_shapeRender[i]) {
            g_shapeRender[i]->FreeShapeRender();
            GSmemFree(g_shapeRender[i]); g_shapeRender[i]=0;
        }
    }
    if(g_shapeRender) { GSmemFree(g_shapeRender); g_shapeRender=0; }
    g_shapeRenderNum=0;
    if(!g_moduleInited) {
        GsShapeRenderModuleData module={0,_shapePreUpdate,0,_shapeFastRender,0,0,0xB29A48E1};
        GSgfxRenderModuleRegister(0x50,(GSgfxRenderModule*)&module,0); g_moduleInited=1;
    }
    g_shapeRender=(GsShapeRender**)GSmemAllocClr(count*4);
    if(!g_shapeRender) { g_shapeRenderNum=0; return false; }
    g_shapeRenderNum=count;
    return true;
}
