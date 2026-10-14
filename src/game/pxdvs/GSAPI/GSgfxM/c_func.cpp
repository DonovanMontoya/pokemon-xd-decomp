#include "graphics_round1.h"
#include <game/pxdvs/GSAPI/GSgfxM/c_interface.hpp>
#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
extern "C" {
void tokenMark__10GSgfxLayerFv(void*);
void dlDraw__10GSgfxLayerFP7GSgfxDL(void*, void*);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void*, void*);
void endSurface__10GSgfxLayerFv(void*);
void beginSurface__10GSgfxLayerFUs(void*, u16);
}
extern "C" void GSgfxSetPrimitiveType(s32 type) {
    ((GraphicsLayerState*)gsgfxState->layer)->primitiveType = type;
}
extern "C" void GSgfxBeginSurface(u16 count) { beginSurface__10GSgfxLayerFUs(gsgfxState->layer, count); }
extern "C" void GSgfxEndSurface() { endSurface__10GSgfxLayerFv(gsgfxState->layer); }
extern "C" void GSgfxVertex3f(f32 x, f32 y, f32 z) {
    *(volatile f32*)0xcc008000 = x; *(volatile f32*)0xcc008000 = y; *(volatile f32*)0xcc008000 = z;
}
extern "C" void GSgfxVertex2f(f32 x, f32 y) {
    *(volatile f32*)0xcc008000 = x; *(volatile f32*)0xcc008000 = y;
}
extern "C" void GSgfxVertex2s16(s16 x, s16 y) {
    *(volatile s16*)0xcc008000 = x; *(volatile s16*)0xcc008000 = y;
}
extern "C" void GSgfxColor4u8(u8 r, u8 g, u8 b, u8 a) {
    *(volatile u8*)0xcc008000 = r; *(volatile u8*)0xcc008000 = g;
    *(volatile u8*)0xcc008000 = b; *(volatile u8*)0xcc008000 = a;
}
extern "C" void GSgfxTexCoord2f(f32 s, f32 t) {
    *(volatile f32*)0xcc008000 = s; *(volatile f32*)0xcc008000 = t;
}
extern "C" void GSgfxSetLineWidth(f32 width) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    layer->lineWidth = (u8)(6.f * width); layer->lineOffset = 0;
    layer->lineDirty |= 4; layer->dirty |= 1;
    layer->savedLineDirty |= 4; layer->savedDirty |= 1;
}
extern "C" void GSgfxBlendMode(s32 mode, s32 source, s32 destination) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    if (mode == 0) {
        if (layer->blendIndex != 0) { layer->blendIndex = 0; layer->currentBlend = &layer->blendRecords[layer->blendIndex]; }
        layer->blendMode = 0; layer->blendSource = 1; layer->blendDestination = 1; layer->logicOperation = 5;
    } else {
        if (layer->blendIndex != 1) { layer->blendIndex = 1; layer->currentBlend = &layer->blendRecords[layer->blendIndex]; }
        layer->blendMode = mode; layer->blendSource = source; layer->blendDestination = destination; layer->logicOperation = 5;
    }
    layer->pixelDirty |= 1; layer->dirty |= 0x40; layer->savedPixelDirty |= 1; layer->savedDirty |= 0x40;
}
extern "C" void GSgfxPixelMode(u8 color, u8 alpha, u8 depth) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    if (color == 1) layer->colorUpdate = 1; else layer->colorUpdate = 0;
    if (alpha == 1) layer->alphaUpdate = 1; else layer->alphaUpdate = 0;
    if (depth == 1) layer->depthBeforeTexture = 1; else layer->depthBeforeTexture = 0;
    layer->pixelDirty |= 4; layer->dirty |= 0x40; layer->savedPixelDirty |= 4; layer->savedDirty |= 0x40;
}
extern "C" void GSgfxZCompare(u8 enabled, s32 comparison) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    if (enabled == 1) layer->depthEnable = 1; else layer->depthEnable = 0; layer->depthCompare = comparison;
    layer->pixelDirty |= 8; layer->dirty |= 0x40; layer->savedPixelDirty |= 8; layer->savedDirty |= 0x40;
}
extern "C" void GSgfxAlphaCompare(u8 enabled, s32 first, u8 ref0, s32 combine, s32 second, u8 ref1) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    if (enabled == 1) {
        layer->alphaCompare0 = first; layer->alphaReference0 = ref0; layer->alphaCombine = combine;
        layer->alphaCompare1 = second; layer->alphaReference1 = ref1; layer->alphaDisabled = 0;
    } else {
        layer->alphaCompare0 = 7; layer->alphaReference0 = 0; layer->alphaCombine = 0;
        layer->alphaCompare1 = 7; layer->alphaReference1 = 0; layer->alphaDisabled = 1;
    }
    layer->pixelDirty |= 0x10; layer->dirty |= 0x40; layer->savedPixelDirty |= 0x10; layer->savedDirty |= 0x40;
}
extern "C" void GSgfxCullMode(s32 mode) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    layer->cullMode = mode; layer->cullDirty |= 2; layer->dirty |= 2; layer->savedCullDirty |= 2; layer->savedDirty |= 2;
}
extern "C" void GSgfxSelectTexture(u8 unit, TextureRecord* texture) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    if (layer->textures[unit] != texture || layer->savedTextures[unit] != texture || texture->dirty) {
        layer->textures[unit] = texture; u32 bit = 1 << unit; layer->textureDirty |= bit;
        layer->savedTextures[unit] = texture; layer->savedTextureDirty |= bit;
    }
}
extern "C" void GSgfxSetTUnitUserColorOp(u8 unit, s32 op, s32 bias, s32 scale, u8 clamp, s32 output) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    TevOperation* value = &layer->colorOperations[unit];
    value->op = op; u32 bit = 1 << unit; value->bias = bias; value->scale = scale; value->clamp = clamp != 0; value->output = output;
    layer->colorOperationDirty |= bit; layer->dirty |= 8; layer->savedColorOperationDirty |= bit; layer->savedDirty |= 8;
}
extern "C" void GSgfxSetTUnitUserColorArg(u8 unit, s32 a, s32 b, s32 c, s32 d) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    u32 bit = 1 << unit; s32* values = layer->colorArguments[unit];
    values[0] = a; values[1] = b; values[2] = c; values[3] = d;
    layer->colorArgumentDirty |= bit; layer->dirty |= 8; layer->savedColorArgumentDirty |= bit; layer->savedDirty |= 8;
}
extern "C" void GSgfxSetTUnitUserAlphaOp(u8 unit, s32 op, s32 bias, s32 scale, u8 clamp, s32 output) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    TevOperation* value = &layer->alphaOperations[unit];
    value->op = op; u32 bit = 1 << unit; value->bias = bias; value->scale = scale; value->clamp = clamp != 0; value->output = output;
    layer->alphaOperationDirty |= bit; layer->dirty |= 8; layer->savedAlphaOperationDirty |= bit; layer->savedDirty |= 8;
}
extern "C" void GSgfxSetTUnitUserAlphaArg(u8 unit, s32 a, s32 b, s32 c, s32 d) {
    GraphicsLayerState* layer = (GraphicsLayerState*)gsgfxState->layer;
    u32 bit = 1 << unit; s32* values = layer->alphaArguments[unit];
    values[0] = a; values[1] = b; values[2] = c; values[3] = d;
    layer->alphaArgumentDirty |= bit; layer->dirty |= 8; layer->savedAlphaArgumentDirty |= bit; layer->savedDirty |= 8;
}
extern "C" void GSgfxSetupRenderAndSelect(void* format) { setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(gsgfxState->layer, format); }
extern "C" void GSgfxDLDraw(void* list) { dlDraw__10GSgfxLayerFP7GSgfxDL(gsgfxState->layer, list); }
extern "C" void GSgfxTokenMark() { tokenMark__10GSgfxLayerFv(gsgfxState->layer); }
extern "C" f32 (*GSgfxMatrixGetPtr(s32 type))[4] {
    switch (type) {
    case 0: return ((GraphicsLayerState*)gsgfxState->layer)->matrixStack->current->matrix;
    case 1: {
        GSgfxMatrixStack* stack = ((GraphicsLayerState*)gsgfxState->layer)->matrixStack;
        if (stack->current->flags & 1) {
            PSMTXInvXpose(stack->current->matrix, stack->current->inverse);
            stack->current->flags &= ~1;
        }
        return stack->current->inverse;
    }
    default:
        GScamera* camera = GScameraGetActiveCamera();
        if (!camera) return 0;
        switch (type) {
        case 2: return GScameraGetMatrixPtr(camera);
        case 3: return GScameraGetInvMatrixPtr(camera);
        case 4: return GScameraGetProjMatrixPtr(camera);
        default: return 0;
        }
    }
}
