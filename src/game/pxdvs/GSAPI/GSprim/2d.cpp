#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <dolphin/gx/GXVert.h>

static inline void position(GSvec2 vertex) { GXWGFifo.f32 = vertex.x; GXWGFifo.f32 = vertex.y; }
static inline void color(GXColor value) { GXColor1u32(*(u32*)&value); }
static inline void lineState() {
    if (primData.lineState != 1) {
        GSprimLayer()->setLineWidth((s32)(6.0f * primData.lineWidth), 0);
        primData.lineState = 1;
    }
}
static inline void selectFormat(u32 id) {
    GSprimData* data = &primData;
    GSgfxVF* format = GSgfxVFGetPredef(id);
    data->layer->setRenderStateAndSelect(format);
}
static inline void beginQuad() {
    GSprimLayer()->primitive = primData.quadPrimitive;
    GSprimLayer()->beginSurface(4);
}

extern "C" void GSprimDraw2DTexQuad4VCA(const GSvec2* vertices, const GSvec2* uv, GStexture* texture, const GXColor* tint, const GXColorS10* addition) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    GSprimLayer()->setTevConstant(*addition);
    GSprimLayer()->setTevColorOperation(0, 0, 0, 1, 0);
    GSprimLayer()->setTevColorInputs(15, 10, 8, 2);
    GSprimLayer()->setTevAlphaOperation(0, 0, 0, 1, 0);
    GSprimLayer()->setTevAlphaInputs(7, 5, 4, 1);
    beginQuad();
    position(vertices[0]); color(*tint); GXTexCoord2f32(uv[0].x, uv[0].y);
    position(vertices[1]); color(*tint); GXTexCoord2f32(uv[1].x, uv[1].y);
    position(vertices[2]); color(*tint); GXTexCoord2f32(uv[2].x, uv[2].y);
    position(vertices[3]); color(*tint); GXTexCoord2f32(uv[3].x, uv[3].y);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DTexQuad4V(const GSvec2* vertices, const GSvec2* uv, GStexture* texture, const GXColor* tint) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    beginQuad();
    position(vertices[0]); color(*tint); GXTexCoord2f32(uv[0].x, uv[0].y);
    position(vertices[1]); color(*tint); GXTexCoord2f32(uv[1].x, uv[1].y);
    position(vertices[2]); color(*tint); GXTexCoord2f32(uv[2].x, uv[2].y);
    position(vertices[3]); color(*tint); GXTexCoord2f32(uv[3].x, uv[3].y);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DTexQuad(f32 x0, f32 y0, f32 x1, f32 y1, GStexture* texture, const GXColor* tint) {
    selectFormat(6);
    GSprimLayer()->setTexture(texture);
    beginQuad();
    GXPosition2f32(x0, y0); color(*tint); GXTexCoord2f32(0.0f, 0.0f);
    GXPosition2f32(x1, y0); color(*tint); GXTexCoord2f32(1.0f, 0.0f);
    GXPosition2f32(x0, y1); color(*tint); GXTexCoord2f32(0.0f, 1.0f);
    GXPosition2f32(x1, y1); color(*tint); GXTexCoord2f32(1.0f, 1.0f);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DQuad4V(const GSvec2* vertices, const GXColor* tint) {
    selectFormat(2);
    beginQuad();
    position(vertices[0]); color(*tint);
    position(vertices[1]); color(*tint);
    position(vertices[2]); color(*tint);
    position(vertices[3]); color(*tint);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DQuadWH(f32 x, f32 y, f32 width, f32 height, const GXColor* tint) {
    GXColor copy = *tint;
    selectFormat(2);
    beginQuad();
    GXPosition2f32(x, y); color(copy);
    GXPosition2f32(x + width, y); color(copy);
    GXPosition2f32(x, y + height); color(copy);
    GXPosition2f32(x + width, y + height); color(copy);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DQuad(f32 x0, f32 y0, f32 x1, f32 y1, const GXColor* tint) {
    selectFormat(2);
    beginQuad();
    GXPosition2f32(x0, y0); color(*tint);
    GXPosition2f32(x1, y0); color(*tint);
    GXPosition2f32(x0, y1); color(*tint);
    GXPosition2f32(x1, y1); color(*tint);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DVLine(f32 x, f32 y0, f32 y1, const GXColor* tint) {
    GXColor first = *tint, second = *tint;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    GXPosition2f32(x, y0); color(first);
    GXPosition2f32(x, y1); color(second);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DHLine(f32 x0, f32 x1, f32 y, const GXColor* tint) {
    GXColor first = *tint, second = *tint;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    GXPosition2f32(x0, y); color(first);
    GXPosition2f32(x1, y); color(second);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DLine(f32 x0, f32 y0, f32 x1, f32 y1, const GXColor* first, const GXColor* second) {
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(2);
    GXPosition2f32(x0, y0); color(*first);
    GXPosition2f32(x1, y1); color(*second);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DPixelListC(const GSprimPixel* vertices, u32 count, const GXColor* colors) {
    if (count == 0) return;
    GSprimLayer()->setPointSize(6, 0);
    selectFormat(3);
    GSprimLayer()->primitive = 0xb8;
    GSprimLayer()->beginSurface(count);
    while (count--) {
        GXPosition2s16(vertices->x, vertices->y);
        GXColor1u32(*(const u32*)colors++);
        ++vertices;
    }
    GSprimLayer()->endSurface();
}
extern "C" void GSprimDraw2DLineListC(const GSvec2* vertices, u32 count, const GXColor* colors) {
    if (count < 1) return;
    lineState();
    selectFormat(2);
    GSprimLayer()->primitive = 0xa8;
    GSprimLayer()->beginSurface(count * 2);
    while (count--) {
        position(*vertices++); color(*colors++);
        position(*vertices++); color(*colors++);
    }
    GSprimLayer()->endSurface();
}
