#ifndef GS_PRIM_HPP
#define GS_PRIM_HPP
#include <global.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>

struct GSgfxVF;
struct GSgfxShader { u8 state[0xbc]; };
struct GSgfxMatrix { u32 dirty; Mtx matrix; };
struct GSgfxMatrixStack { u32 reserved; GSgfxMatrix* current; };

// Layer state offsets are shared with the GSgfx render-state cache.
struct GSgfxLayer {
    u8 reserved00[0x28];
    u32 id;
    u8 reserved2c[0xd34 - 0x2c];
    u8 lineWidth;
    u8 reservedD35[3];
    u32 lineTexOffset;
    u8 pointSize;
    u8 reservedD3d[3];
    u32 pointTexOffset;
    u8 reservedD44[0xd54 - 0xd44];
    u32 projectionType;
    f32 projection[6];
    u8 reservedD70[0xd8c - 0xd70];
    u32 cullMode;
    u8 reservedD90[0xf70 - 0xd90];
    u32 tevColorInputs[4];
    u8 reservedF80[0x1070 - 0xf80];
    u32 tevAlphaInputs[4];
    u8 reserved1080[0x1170 - 0x1080];
    u32 tevColorOperation, tevColorBias, tevColorScale;
    u8 tevColorClamp;
    u8 reserved117d[3];
    u32 tevColorOutput;
    u8 reserved1184[0x12b0 - 0x1184];
    u32 tevAlphaOperation, tevAlphaBias, tevAlphaScale;
    u8 tevAlphaClamp;
    u8 reserved12bd[3];
    u32 tevAlphaOutput;
    u8 reserved12c4[0x13fc - 0x12c4];
    u32 tevConstantIndex;
    GXColorS10 tevConstant;
    u8 reserved1408[0x1644 - 0x1408];
    u32 blendMode, blendSource, blendDestination, blendLogic;
    u8 reserved1654[2];
    u8 colorUpdate, alphaUpdate, destinationAlpha;
    u8 reserved1659[3];
    u8 depthEnable;
    u8 reserved165d[3];
    u32 depthFunction;
    u32 alphaFunction0, alphaOperation, alphaFunction1;
    u8 alphaReference0, alphaReference1, depthBeforeTexture;
    u8 reserved1673[0x1684 - 0x1673];
    f32 depthNear, depthFar;
    u8 reserved168c[0x16a6 - 0x168c];
    u8 fogRangeAdjust, fogEnable;
    u32 dirty, rasterDirty;
    u8 reserved16b0[8];
    u32 transformDirty;
    u8 reserved16bc[0x16d4 - 0x16bc];
    u32 tevColorInputDirty, tevAlphaInputDirty, tevColorOperationDirty, tevAlphaOperationDirty, tevConstantDirty;
    u8 reserved16e8[0x170c - 0x16e8];
    u32 pixelDirty;
    u8 reserved1710[0x173c - 0x1710];
    u32 textureDirty;
    GStexture* texture;
    u8 reserved1744[0x1760 - 0x1744];
    u32 savedDirty, savedRasterDirty;
    u8 reserved1768[8];
    u32 savedTransformDirty;
    u8 reserved1774[0x178c - 0x1774];
    u32 savedTevColorInputDirty, savedTevAlphaInputDirty, savedTevColorOperationDirty, savedTevAlphaOperationDirty, savedTevConstantDirty;
    u8 reserved17a0[0x17c4 - 0x17a0];
    u32 savedPixelDirty;
    u8 reserved17c8[0x17f4 - 0x17c8];
    u32 savedTextureDirty;
    GStexture* savedTexture;
    u8 reserved17fc[0x1818 - 0x17fc];
    GSgfxShader shaders[2];
    GSgfxShader* shader;
    s32 shaderIndex;
    u32 primitive;
    u8 reserved199c[4];
    GSgfxMatrixStack* matrixStack;

    void setRenderStateAndSelect(GSgfxVF*);
    void beginSurface(u16);
    void endSurface();
    inline void setTexture(GStexture* value) {
        if (texture != value || savedTexture != value || value->dirty) {
            texture = value; textureDirty |= 1;
            savedTexture = value; savedTextureDirty |= 1;
        }
    }
    inline void setLineWidth(u8 width, u32 offset) {
        lineWidth = width; lineTexOffset = offset;
        rasterDirty |= 4; dirty |= 1; savedRasterDirty |= 4; savedDirty |= 1;
    }
    inline void setPointSize(u8 size, u32 offset) {
        pointSize = size; pointTexOffset = offset;
        rasterDirty |= 8; dirty |= 1; savedRasterDirty |= 8; savedDirty |= 1;
    }
    inline void setTevConstant(GXColorS10 value) {
        tevConstantIndex = 1;
        tevConstant.r = value.r > -1024 ? value.r : -1024;
        tevConstant.r = tevConstant.r < 1023 ? tevConstant.r : 1023;
        tevConstant.g = value.g > -1024 ? value.g : -1024;
        tevConstant.g = tevConstant.g < 1023 ? tevConstant.g : 1023;
        tevConstant.b = value.b > -1024 ? value.b : -1024;
        tevConstant.b = tevConstant.b < 1023 ? tevConstant.b : 1023;
        tevConstant.a = value.a > -1024 ? value.a : -1024;
        tevConstant.a = tevConstant.a < 1023 ? tevConstant.a : 1023;
        tevConstantDirty |= 2; dirty |= 8;
        savedTevConstantDirty |= 2; savedDirty |= 8;
    }
    inline void setTevColorOperation(u32 operation, u32 bias, u32 scale, u8 clamp, u32 output) {
        tevColorOperation = operation; tevColorBias = bias; tevColorScale = scale;
        tevColorClamp = clamp; tevColorOutput = output;
        tevColorOperationDirty |= 1; dirty |= 8; savedTevColorOperationDirty |= 1; savedDirty |= 8;
    }
    inline void setTevAlphaOperation(u32 operation, u32 bias, u32 scale, u8 clamp, u32 output) {
        tevAlphaOperation = operation; tevAlphaBias = bias; tevAlphaScale = scale;
        tevAlphaClamp = clamp; tevAlphaOutput = output;
        tevAlphaOperationDirty |= 1; dirty |= 8; savedTevAlphaOperationDirty |= 1; savedDirty |= 8;
    }
    inline void setTevColorInputs(u32 a, u32 b, u32 c, u32 d) {
        tevColorInputs[0] = a; tevColorInputs[1] = b; tevColorInputs[2] = c; tevColorInputs[3] = d;
        tevColorInputDirty |= 1; dirty |= 8; savedTevColorInputDirty |= 1; savedDirty |= 8;
    }
    inline void setTevAlphaInputs(u32 a, u32 b, u32 c, u32 d) {
        tevAlphaInputs[0] = a; tevAlphaInputs[1] = b; tevAlphaInputs[2] = c; tevAlphaInputs[3] = d;
        tevAlphaInputDirty |= 1; dirty |= 8; savedTevAlphaInputDirty |= 1; savedDirty |= 8;
    }
    inline void selectShader(s32 index) {
        if (shaderIndex != index) {
            shaderIndex = index;
            shader = &shaders[shaderIndex];
        }
    }
    inline void markPixel(u32 mask) {
        pixelDirty |= mask; dirty |= 0x40;
        savedPixelDirty |= mask; savedDirty |= 0x40;
    }
    inline void setBlend(u32 mode, u32 source, u32 destination, u32 logic) {
        blendMode = mode; blendSource = source; blendDestination = destination; blendLogic = logic;
        markPixel(1);
    }
    inline void setColorUpdate(u8 color, u8 alpha, u8 destination) {
        colorUpdate = color; alphaUpdate = alpha; destinationAlpha = destination; markPixel(4);
    }
    inline void setDepth(u8 enable, u32 function) {
        depthEnable = enable; depthFunction = function; markPixel(8);
    }
    inline void setAlpha(u32 first, u8 ref0, u32 operation, u32 second, u8 ref1, u8 before) {
        alphaFunction0 = first; alphaReference0 = ref0; alphaOperation = operation;
        alphaFunction1 = second; alphaReference1 = ref1; depthBeforeTexture = before; markPixel(0x10);
    }
    inline void setCull(u32 mode) {
        cullMode = mode; transformDirty |= 2; dirty |= 2;
        savedTransformDirty |= 2; savedDirty |= 2;
    }
};
typedef char GSgfxLayerIdOffset[offsetof(GSgfxLayer, id) == 0x28 ? 1 : -1];
typedef char GSgfxLayerProjectionOffset[offsetof(GSgfxLayer, projectionType) == 0xd54 ? 1 : -1];
typedef char GSgfxLayerTevConstantOffset[offsetof(GSgfxLayer, tevConstant) == 0x1400 ? 1 : -1];
typedef char GSgfxLayerBlendOffset[offsetof(GSgfxLayer, blendMode) == 0x1644 ? 1 : -1];
typedef char GSgfxLayerShaderOffset[offsetof(GSgfxLayer, shader) == 0x1990 ? 1 : -1];
typedef char GSgfxLayerMatrixStackOffset[offsetof(GSgfxLayer, matrixStack) == 0x19a0 ? 1 : -1];
struct GSvec2 { f32 x, y; };
struct GSprimPixel { s16 x, y; };
struct GSprimData { GSgfxLayer* layer; s32 lineState; f32 lineWidth, textWidth; s32 quadOrder; u32 quadPrimitive; };
typedef char GSprimDataSizeCheck[sizeof(GSprimData) == 0x18 ? 1 : -1];
extern GSprimData primData;
inline GSgfxLayer* GSprimLayer() { return primData.layer; }
extern "C" {
u32 GSgfxLayerGetActive();
GSgfxLayer* GSgfxLayerFindByID(u32);
void GSgfxLayerSetActive(u32);
void GScameraLoadActiveCameraMatrix(u32);
GSgfxVF* GSgfxVFGetPredef(u32);
void GSprimSetQuadVertexOrder(s32);
void GSprimSetLineWidth(f32);
void GSprimSetBlendMode(s32);
void GSprimSetTextSize(f32, f32);
void GSprimSetTextWidth(f32);
void GSmtx44Ortho(Mtx44, f32, f32, f32, f32, f32, f32);
}
void GSprimSetRenderLayer(GSgfxLayer*);
void GSprimSetup3DRender(GSgfxLayer*);
void GSprimSetup2DRender(GSgfxLayer*);
extern "C" {
void GSprimDraw2DTexQuad4VCA(const GSvec2*, const GSvec2*, GStexture*, const GXColor*, const GXColorS10*);
void GSprimDraw2DTexQuad4V(const GSvec2*, const GSvec2*, GStexture*, const GXColor*);
void GSprimDraw2DTexQuad(f32, f32, f32, f32, GStexture*, const GXColor*);
void GSprimDraw2DQuad4V(const GSvec2*, const GXColor*);
void GSprimDraw2DQuadWH(f32, f32, f32, f32, const GXColor*);
void GSprimDraw2DQuad(f32, f32, f32, f32, const GXColor*);
void GSprimDraw2DPixelListC(const GSprimPixel*, u32, const GXColor*);
void GSprimDraw2DLineListC(const GSvec2*, u32, const GXColor*);
void GSprimDraw2DVLine(f32, f32, f32, const GXColor*);
void GSprimDraw2DHLine(f32, f32, f32, const GXColor*);
void GSprimDraw2DLine(f32, f32, f32, f32, const GXColor*, const GXColor*);
void GSprimWriteStr(f32, f32, const char*, ...);
void GSprimWriteChar(f32, f32, char);
void GSprimSetTextColor(const u8*);
}
extern Mtx mtxIdent;
#endif
