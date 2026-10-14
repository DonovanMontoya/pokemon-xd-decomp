#ifndef GSGFX_LAYER_PRIVATE_H
#define GSGFX_LAYER_PRIVATE_H
#include "graphics_round1.h"
#include <game/pxdvs/GSAPI/GSgfxM/c_interface.hpp>
// The layer ABI contains packed state groups. Offset views preserve accesses to
// groups whose complete public types have not yet been recovered.
template <class T> inline T& layerField(void* p, unsigned offset) {
    return *reinterpret_cast<T*>(static_cast<u8*>(p) + offset);
}
struct LayerVertexFormat { u32 flags, format; u8 reserved8[0x1b0]; GXVtxDescList descriptors[27]; };
struct LayerDisplayList { u16 flags, reserved; void* data; u32 size; LayerVertexFormat* format; };
struct LayerTexGen { s32 function, source, matrix; u8 normalize; u8 padding[3]; s32 postMatrix, reserved; };
struct LayerChannel { u8 enabled; u8 padding[3]; s32 ambient, material, mask, diffuse, attenuation; void* lights[8]; };
ABI_SIZE(LayerTexGen,0x18); ABI_SIZE(LayerChannel,0x38);
ABI_OFF(LayerVertexFormat,descriptors,0x1b8); ABI_SIZE(LayerDisplayList,0x10);
inline void selectLayerPass(GraphicsLayerState* layer, s32 pass) {
    if (layer->blendIndex != pass) {
        layer->blendIndex = pass;
        layer->currentBlend = &layer->blendRecords[layer->blendIndex];
    }
}
extern "C" {
extern u8 gsgfx_layer_inPrimitive;
void SetupFifo__10GSgfxLayerFv(void*);
void FlushState__10GSgfxLayerFv(void*);
void InvalidateState__10GSgfxLayerFv(void*);
void GSgfx_GCWriteIndTexMtx(s32,const float (*)[3],s8);
void GXDrawSphere1(u8); void GXDrawSphere(u8,u8); void GXDrawTorus(float,u8,u8);
void GXDrawOctahedron(); void GXDrawIcosahedron(); void GXDrawDodeca(); void GXDrawCylinder(u8); void GXDrawCube();
}
struct LayerNode { LayerNode* next; u8 reserved4[0x24]; s32 id; };
struct LayerConfigData { s32 id; char* name; s32 type; u8 clearColor,clearAlpha,clearDepth,visible; u32 opaqueSize,translucentSize,matrixCount; };
ABI_OFF(LayerNode,id,0x28); ABI_SIZE(LayerConfigData,0x1c);
extern "C" {
LayerNode* GetLayerList__10GSgfxLayerFv();
LayerNode* GSgfxLayerFindByName(char*);
void* __nw__FUl(u32);
LayerNode* __ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(void*,s32,char*,u32,u32,u32,s32);
void* __dt__10GSgfxLayerFv(void*,s16);
void SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(void*,s32,void*);
void SetLayerType__10GSgfxLayerF14GSgfxLayerType(void*,s32);
void SetWantClearFlags__10GSgfxLayerFbbb(void*,bool,bool,bool);
void SetPassVisibility__10GSgfxLayerFbb(void*,bool,bool);
void SetLayerVisibility__10GSgfxLayerFb(void*,bool);
void GSgfxLayerSetActive(s32);
}
inline LayerNode* findConfigLayer(s32 id) {
    for (LayerNode* p=GetLayerList__10GSgfxLayerFv();p;p=p->next) if (p->id==id) return p;
    return 0;
}
inline s32 freeConfigLayerID() {
    for (u32 id=8;id<16;id++) {
        u8 found=0;
        for (LayerNode* p=GetLayerList__10GSgfxLayerFv();p;p=p->next) if (p->id==id) { found=1; break; }
        if (!found) return id;
    }
    return -1;
}
#endif
