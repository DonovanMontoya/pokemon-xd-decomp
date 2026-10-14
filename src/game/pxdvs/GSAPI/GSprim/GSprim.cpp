#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <libc/string.h>

GSprimData primData;

extern "C" void GSprimSetQuadVertexOrder(s32 order) {
    primData.quadOrder = order;
    switch (order) {
    case 0:
        primData.quadPrimitive = 0x98;
        break;
    case 1:
        primData.quadPrimitive = 0x80;
        break;
    }
}

extern "C" void GSprimSetLineWidth(f32 width) {
    primData.lineWidth = width;
    primData.lineState = 0;
}

extern "C" void GSprimSetBlendMode(s32 mode) {
    switch (mode) {
    case 0: { GSgfxLayer* layer = GSprimLayer(); layer->selectShader(0); layer->setBlend(0, 1, 1, 5); break; }
    case 1: { GSgfxLayer* layer = GSprimLayer(); layer->selectShader(1); layer->setBlend(1, 4, 5, 5); break; }
    case 2: { GSgfxLayer* layer = GSprimLayer(); layer->selectShader(1); layer->setBlend(1, 1, 1, 5); break; }
    case 3: { GSgfxLayer* layer = GSprimLayer(); layer->selectShader(1); layer->setBlend(3, 1, 1, 5); break; }
    }
}
void GSprimSetRenderLayer(GSgfxLayer* layer) {
    if (!layer) layer = GSgfxLayerFindByID(GSgfxLayerGetActive());
    primData.layer = layer;
}
void GSprimSetup3DRender(GSgfxLayer* layer) {
    GSprimSetRenderLayer(layer);
    GSgfxLayerSetActive(GSprimLayer()->id);
    GScameraLoadActiveCameraMatrix(GSprimLayer()->id);
    GSprimLayer()->setColorUpdate(1, 1, 1);
    GSprimLayer()->setDepth(1, 3);
    GSprimLayer()->setAlpha(7, 0, 0, 7, 0, 1);
    GSprimLayer()->setCull(0);
    GSprimSetBlendMode(0);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
}
void GSprimSetup2DRender(GSgfxLayer* layer) {
    GSprimSetRenderLayer(layer);
    layer = GSprimLayer();
    Mtx44 projection;
    GSmtx44Ortho(projection, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
    layer->projectionType = 1;
    layer->projection[0] = projection[0][0];
    layer->projection[1] = projection[0][3];
    layer->projection[2] = projection[1][1];
    layer->projection[3] = projection[1][3];
    layer->projection[4] = projection[2][2];
    layer->projection[5] = projection[2][3];
    GSgfxMatrixStack* stack = layer->matrixStack;
    memcpy(stack->current->matrix, mtxIdent, sizeof(Mtx));
    stack->current->dirty |= 1;
    layer->depthNear = 0.0f;
    layer->depthFar = 30000.0f;
    if (layer->fogEnable) {
        if (layer->fogRangeAdjust) {
            layer->pixelDirty |= 0x100;
            layer->savedPixelDirty |= 0x100;
        }
        layer->markPixel(0x40);
    }
    layer->rasterDirty |= 0x20; layer->dirty |= 1;
    layer->savedRasterDirty |= 0x20; layer->savedDirty |= 1;
    GSprimLayer()->setColorUpdate(1, 0, 0);
    GSprimLayer()->setDepth(0, 3);
    GSprimLayer()->setAlpha(7, 0, 0, 7, 0, 1);
    GSprimLayer()->setCull(0);
    GSprimSetBlendMode(0);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f, 10.0f);
    GSprimSetTextWidth(1.0f);
}
