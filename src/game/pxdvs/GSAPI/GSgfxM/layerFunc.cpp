#include "layer_private.h"

extern "C" {
inline void tunitSetColorOp(GraphicsLayerState* layer, u8 unit, s32 op, s32 bias, s32 scale, u8 clamp, s32 output) {
    layer->colorOperations[unit].op = op; layer->colorOperations[unit].bias = bias; layer->colorOperations[unit].scale = scale; layer->colorOperations[unit].clamp = clamp != 0; layer->colorOperations[unit].output = output; u32 bit = 1 << unit;
    layer->colorOperationDirty |= bit; layer->dirty |= 8; layer->savedColorOperationDirty |= bit; layer->savedDirty |= 8;
}
inline void tunitSetAlphaOp(GraphicsLayerState* layer, u8 unit, s32 op, s32 bias, s32 scale, u8 clamp, s32 output) {
    layer->alphaOperations[unit].op = op; layer->alphaOperations[unit].bias = bias; layer->alphaOperations[unit].scale = scale; layer->alphaOperations[unit].clamp = clamp != 0; layer->alphaOperations[unit].output = output; u32 bit = 1 << unit;
    layer->alphaOperationDirty |= bit; layer->dirty |= 8; layer->savedAlphaOperationDirty |= bit; layer->savedDirty |= 8;
}
inline void tunitSetColorArg(GraphicsLayerState* layer, u8 unit, s32 a, s32 b, s32 c, s32 d) {
    layer->colorArguments[unit][0] = a; layer->colorArguments[unit][1] = b; layer->colorArguments[unit][2] = c; layer->colorArguments[unit][3] = d; u32 bit = 1 << unit;
    layer->colorArgumentDirty |= bit; layer->dirty |= 8; layer->savedColorArgumentDirty |= bit; layer->savedDirty |= 8;
}
inline void tunitSetAlphaArg(GraphicsLayerState* layer, u8 unit, s32 a, s32 b, s32 c, s32 d) {
    layer->alphaArguments[unit][0] = a; layer->alphaArguments[unit][1] = b; layer->alphaArguments[unit][2] = c; layer->alphaArguments[unit][3] = d; u32 bit = 1 << unit;
    layer->alphaArgumentDirty |= bit; layer->dirty |= 8; layer->savedAlphaArgumentDirty |= bit; layer->savedDirty |= 8;
}
void tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(GraphicsLayerState* layer, u8 unit, u32 function) {
    switch (function) {
    case 0:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 15, 10, 8, 15);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 7, 5, 4, 7);
        return;
    case 1:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 10, 8, 9, 15);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 7, 7, 7, 5);
        return;
    case 2:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 10, 12, 8, 15);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 7, 5, 4, 7);
        return;
    case 3:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 8, 15, 15, 15);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 4, 7, 7, 7);
        return;
    case 4:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 10, 15, 15, 15);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 5, 7, 7, 7);
        return;
    case 5:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 8, 15, 15, 0);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 4, 7, 7, 0);
        return;
    case 6:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 10, 15, 15, 0);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 5, 7, 7, 0);
        return;
    case 7:
        tunitSetColorOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetColorArg(layer, unit, 15, 10, 8, 0);
        tunitSetAlphaOp(layer, unit, 0, 0, 0, 1, 0);
        tunitSetAlphaArg(layer, unit, 7, 5, 4, 0);
        return;
    default:
        return;
    }
}


}

extern "C" {
void SetDistortionParams__10GSgfxLayerFPA3_fSc(void* layer, float (*matrix)[3], s8 exponent) {
    float* out = &layerField<float>(layer, 0x19bc);
    out[0] = matrix[0][0]; out[1] = matrix[0][1]; out[2] = matrix[0][2];
    out[3] = matrix[1][0]; out[4] = matrix[1][1]; out[5] = matrix[1][2];
    layerField<s8>(layer, 0x19b8) = exponent;
}
void tokenMark__10GSgfxLayerFv(void* layer) {
    SetupFifo__10GSgfxLayerFv(layer); GSgfxTokenMark_Sub__Fv();
}
void tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(GraphicsLayerState* layer, s32 id, float (*matrix)[3], s8 exponent) {
    SetupFifo__10GSgfxLayerFv(layer); GSgfx_GCWriteIndTexMtx(id,matrix,exponent);
    s32 saved = layer->blendIndex; u8 other = saved == 0;
    if (layer->blendRecords[other].fifo != 0) {
        selectLayerPass(layer,other); SetupFifo__10GSgfxLayerFv(layer);
        GSgfx_GCWriteIndTexMtx(id,matrix,exponent);
        selectLayerPass(layer,saved); SetupFifo__10GSgfxLayerFv(layer);
    }
}
struct LayerTexGenView { u8 pad[0xc74]; LayerTexGen gens[8]; };
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(GraphicsLayerState* layer,u8 unit,s32 function,s32 source,float (*matrix)[4],bool normalize,float (*post)[4]) {
    LayerTexGenView* view=(LayerTexGenView*)layer; u8 load=0; view->gens[unit].function=function; view->gens[unit].source=source; view->gens[unit].normalize=normalize; view->gens[unit].reserved=0;
    if (!matrix) view->gens[unit].matrix=0x3c; else { load=1; view->gens[unit].matrix=unit*3+0x1e; }
    if (!post) view->gens[unit].postMatrix=0x7d; else { load=1; view->gens[unit].postMatrix=unit*3+0x40; }
    if (load==1) {
        SetupFifo__10GSgfxLayerFv(layer);
        if (matrix) { if (function==1) GXLoadTexMtxImm(matrix,view->gens[unit].matrix,GX_MTX2x4); else GXLoadTexMtxImm(matrix,view->gens[unit].matrix,GX_MTX3x4); }
        // The original intentionally passes matrix for the post-matrix load too.
        if (post) GXLoadTexMtxImm(matrix,view->gens[unit].postMatrix,GX_MTX3x4);
        s32 saved=layer->blendIndex; u8 other=saved==0;
        if (layer->blendRecords[other].fifo!=0) {
            selectLayerPass(layer,other); SetupFifo__10GSgfxLayerFv(layer);
            if (matrix) { if (function==1) GXLoadTexMtxImm(matrix,view->gens[unit].matrix,GX_MTX2x4); else GXLoadTexMtxImm(matrix,view->gens[unit].matrix,GX_MTX3x4); }
            if (post) GXLoadTexMtxImm(matrix,view->gens[unit].postMatrix,GX_MTX3x4);
            selectLayerPass(layer,saved); SetupFifo__10GSgfxLayerFv(layer);
        }
    }
    layerField<u32>(layer,0x16b0)|=1<<unit; layer->dirty|=1;
    layerField<u32>(layer,0x1768)|=1<<unit; layer->savedDirty|=1;
}
struct LayerChannelView { u8 pad[0xdbc]; LayerChannel channels[8]; };
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(GraphicsLayerState* layer,u8 unit,s32 alpha,s32 ambient,s32 material,u32 count,void** lights,s32 attenuation,s32 diffuse) {
    u32 idx=unit; s32 alphaUnit=unit+2; u8 enabled=0;
    if (lights && count) enabled=1;
    if (!enabled) { attenuation=2; diffuse=0; } else if (!attenuation) diffuse=0;
    if (alpha==0 || alpha==2) {
        ((LayerChannelView*)layer)->channels[idx].enabled=enabled; ((LayerChannelView*)layer)->channels[idx].ambient=ambient; ((LayerChannelView*)layer)->channels[idx].material=material;
        ((LayerChannelView*)layer)->channels[idx].mask=0; ((LayerChannelView*)layer)->channels[idx].diffuse=diffuse; ((LayerChannelView*)layer)->channels[idx].attenuation=attenuation;
        if (enabled) for (u32 i=0;i<8;i++) { if (i<count) ((LayerChannelView*)layer)->channels[idx].lights[i]=lights[i]; else ((LayerChannelView*)layer)->channels[idx].lights[i]=0; }
        else memset(((LayerChannelView*)layer)->channels[idx].lights,0,0x20);
        layerField<u32>(layer,0x16c0)|=1<<idx; layerField<u32>(layer,0x1778)|=1<<idx;
    }
    if (alpha==1 || alpha==2) {
        ((LayerChannelView*)layer)->channels[alphaUnit].enabled=enabled; ((LayerChannelView*)layer)->channels[alphaUnit].ambient=ambient; ((LayerChannelView*)layer)->channels[alphaUnit].material=material;
        ((LayerChannelView*)layer)->channels[alphaUnit].mask=0; ((LayerChannelView*)layer)->channels[alphaUnit].diffuse=diffuse; ((LayerChannelView*)layer)->channels[alphaUnit].attenuation=attenuation;
        // Both branches write the light list for the color unit in the original.
        if (enabled) for (u32 i=0;i<8;i++) { if (i<count) ((LayerChannelView*)layer)->channels[idx].lights[i]=lights[i]; else ((LayerChannelView*)layer)->channels[idx].lights[i]=0; }
        else memset(((LayerChannelView*)layer)->channels[idx].lights,0,0x20);
        layerField<u32>(layer,0x16c0)|=1<<alphaUnit; layerField<u32>(layer,0x1778)|=1<<alphaUnit;
    }
    layer->dirty|=4; layer->savedDirty|=4;
}
void drawSphere__10GSgfxLayerFUc(void* layer,u8 rings) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawSphere1(rings); InvalidateState__10GSgfxLayerFv(layer);
}
void drawSphere__10GSgfxLayerFUcUc(void* layer,u8 a,u8 b) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawSphere(b,a); InvalidateState__10GSgfxLayerFv(layer);
}
void drawTorus__10GSgfxLayerFfUcUc(void* layer,float radius,u8 a,u8 b) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawTorus(radius,a,b); InvalidateState__10GSgfxLayerFv(layer);
}
void drawCylinder__10GSgfxLayerFUc(void* layer,u8 sides) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawCylinder(sides); InvalidateState__10GSgfxLayerFv(layer);
}
void drawOctahedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawOctahedron(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawIcosahedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawIcosahedron(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawDodecaedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawDodeca(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawCube__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawCube(); InvalidateState__10GSgfxLayerFv(layer);
}
void dlDraw__10GSgfxLayerFP7GSgfxDL(void* layer,LayerDisplayList* list) {
    if (list->flags&2) { DCStoreRange(list->data,list->size); list->flags&=~2; }
    LayerVertexFormat* saved=layerField<LayerVertexFormat*>(layer,0x199c);
    layerField<LayerVertexFormat*>(layer,0x199c)=list->format;
    FlushState__10GSgfxLayerFv(layer);
    void* data; u32 size; size=list->size; data=list->data;
    *(volatile u8*)0xcc008000=0x40;
    *(void* volatile*)0xcc008000=data;
    *(volatile u32*)0xcc008000=size;
    layerField<LayerVertexFormat*>(layer,0x199c)=saved;
}
void dlDrawExt__10GSgfxLayerFPUcUl(void* layer,u8* data,u32 size) {
    layerField<LayerVertexFormat*>(layer,0x199c)->format=0;
    FlushState__10GSgfxLayerFv(layer);
    *(volatile u8*)0xcc008000=0x40;
    *(volatile u32*)0xcc008000=(u32)data;
    *(volatile u32*)0xcc008000=size;
}
void endSurface__10GSgfxLayerFv(void*) { gsgfx_layer_inPrimitive=0; }
void beginSurface__10GSgfxLayerFUs(GraphicsLayerState* layer,u16 vertices) {
    FlushState__10GSgfxLayerFv(layer);
    *(volatile u8*)0xcc008000=layer->primitiveType|layerField<LayerVertexFormat*>(layer,0x199c)->format;
    *(volatile u16*)0xcc008000=vertices; gsgfx_layer_inPrimitive=1;
}
}
