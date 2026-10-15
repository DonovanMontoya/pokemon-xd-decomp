#ifndef GAME_PXDVS_GSAPI_GSGFXM_GAMECUBE_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_GAMECUBE_PRIVATE_HPP

#include <dolphin/types.h>
#include <dolphin/gx.h>
#include <libc/stddef.h>

union GCBPRegister {
    u32 value;
    struct { u8 address; u8 payload[3]; } bytes;
    struct { u32 address:8, payload:24; } fields;
    struct { u32 address:8, bank:1, payload:23; } color;
    struct { u32 address:8, format:4, height:10, width:10; } image;
    struct { u32 address:8, reserved:2, type:1, height:3, width:3, base:15; } imageCache;
    struct { u32 address:8, reserved:14, region:10; } texturePalette;
    struct { u32 address:8, coordinate3:3, texture3:3, coordinate2:3, texture2:3, coordinate1:3, texture1:3, coordinate0:3, texture0:3; } indirectOrder;
    struct { u32 address:8, reserved1:2, channel1:3, enabled1:1, coordinate1:3, texture1:3, reserved0:2, channel0:3, enabled0:1, coordinate0:3, texture0:3; } order;
    struct { u16 header, size; } dimension;
    struct { u32 address:8, reserved:4, y:10, x:10; } copyRectangle;
    struct { u32 address:8, reserved:14, stride:10; } copyStride;
    struct { u32 address:8, reserved:15, scale:9; } copyScale;
    struct { u32 address:8, reserved:7, conversion:1, intensity:1, display:1, gamma:2, clear:1, scale:1, mipmap:1, fieldMode:2, format:3, depth:1, reserved2:1, clamp:2; } copyControl;
    struct { u32 address:8, reserved:19, alpha:1, color:1, dither:1, logic:1, blend:1; } copyBlend;
    struct { u32 address:8, reserved:19, update:1, function:3, test:1; } copyDepth;
    struct { u32 address:8, reserved:17, compare:1, reserved5:1, depthFormat:2, pixelFormat:3; } copyPixel;
    struct { u32 address:8, reserved:3, source:21; } tlutSource;
    struct { u32 address:8, reserved:3, count:11, region:10; } tlutRegion;
    struct { u32 address:8, reserved:1, flag:1, payload:22; } coordinateBias;
    struct { u32 address:8, payload:23, enabled:1; } mode;
    struct { u32 address:8, reserved:19, depthFormat:2, pixelFormat:3; } pixel;
    struct { u32 address:8, reserved:13, mode:2, payload:9; } field;
    struct { u32 address:8, payload:20, selector1:2, selector0:2; } swap;
    struct { u32 address:8, reserved:3, addPrevious:1, originalLod:1, wrapT:3, wrapS:3, matrix:4, alpha:2, bias:3, format:2, stage:2; } indirect;
};
struct GCFogRegister { u32 address:8, function:3, projection:1, parameter:20; };
struct GCFogFullParameterRegister { u32 address:8, parameter:24; };
struct GCTextureGeneratorCache {
    s32 type;
    u32 source;
    s32 matrix;
    u8 normalize;
    u8 padding11[3];
    s32 postMatrix;
};
struct GCIndirectOrderCache { s32 coordinate, texture; };
struct GCStageOrderCache { s32 coordinate, texture, channel; };
struct GCCombinerInputs { s32 a, b, c, d; };
struct GCCombinerOperation { s32 operation, bias, scale; u8 clamp; u8 padding[3]; s32 output; };
struct GCStageSwapCache { s32 raster, texture; };
struct GCTlutUploadCache { u32 source; u16 count, region; };
struct GCGraphicsState {
    u32 dirty;
    u32 dirtyGroups[11];
    GCBPRegister bp30[9];
    u8 unmodelled054[4];
    GCBPRegister tevOrder[8];
    GCBPRegister indirectReference;
    GCBPRegister indirectScale[2];
    GCBPRegister textureMode0[8];
    GCBPRegister textureMode1[8];
    GCBPRegister textureImage0[8];
    GCBPRegister textureImage1[8];
    GCBPRegister textureImage2[8];
    GCBPRegister textureImage3[8];
    GCBPRegister textureTlut[8];
    GCTlutUploadCache tlutUploads[8];
    GCBPRegister bp1A4[2];
    GCBPRegister textureSizeS[8];
    GCBPRegister textureSizeT[8];
    GCBPRegister bp1EC;
    u32 matrixIndices[2];
    GCBPRegister bp1F8[2];
    GCBPRegister bp200;
    GCBPRegister tevConstantSelect[8];
    GCBPRegister tevColorEnvironment[16];
    GCBPRegister tevAlphaEnvironment[16];
    GCBPRegister tevColorA[4];
    GCBPRegister tevColorB[4];
    GCBPRegister tevConstantColorA[4];
    GCBPRegister tevConstantColorB[4];
    GCFogRegister fogA;
    GCFogFullParameterRegister fogB;
    GCFogFullParameterRegister fogExponent;
    GCFogRegister fogC;
    GCBPRegister fogColor;
    GCBPRegister bp2F8[6];
    GCBPRegister tevIndirect[16];
    GCBPRegister bp350;
    GCBPRegister bp354;
    GCTextureGeneratorCache textureGenerators[8];
    u8 unmodelled3F8[0x4CC - 0x3F8];
    GCStageOrderCache stageOrders[16];
    u8 unmodelled58C[4];
    GCCombinerInputs colorInputs[16];
    GCCombinerInputs alphaInputs[16];
    GCCombinerOperation colorOperations[16];
    GCCombinerOperation alphaOperations[16];
    u8 unmodelledA10[0xAA4 - 0xA10];
    GCStageSwapCache stageSwaps[16];
    u8 unmodelledB24[0xB64 - 0xB24];
    u8 indirectMode[16];
    GCIndirectOrderCache indirectOrders[4];
    u8 unmodelledB94[0xC64 - 0xB94];
};
typedef char GCTextureGeneratorCacheSizeCheck[sizeof(GCTextureGeneratorCache) == 0x14 ? 1 : -1];
typedef char GCGraphicsStateSizeCheck[sizeof(GCGraphicsState) == 0xC64 ? 1 : -1];
typedef char GCGraphicsStateFogOffsetCheck[offsetof(GCGraphicsState, fogA) == 0x2E4 ? 1 : -1];
typedef char GCGraphicsStateTexGenOffsetCheck[offsetof(GCGraphicsState, textureGenerators) == 0x358 ? 1 : -1];
typedef char GCGraphicsStateTextureModeOffsetCheck[offsetof(GCGraphicsState, textureMode0) == 0x84 ? 1 : -1];
typedef char GCGraphicsStateMatrixIndexOffsetCheck[offsetof(GCGraphicsState, matrixIndices) == 0x1F0 ? 1 : -1];
typedef char GCGraphicsStateColorOffsetCheck[offsetof(GCGraphicsState, tevColorA) == 0x2A4 ? 1 : -1];
typedef char GCGraphicsStateIndirectOffsetCheck[offsetof(GCGraphicsState, tevIndirect) == 0x310 ? 1 : -1];
typedef char GCGraphicsStateKonstSelectOffsetCheck[offsetof(GCGraphicsState, tevConstantSelect) == 0x204 ? 1 : -1];
typedef char GCGraphicsStateTlutUploadOffsetCheck[offsetof(GCGraphicsState, tlutUploads) == 0x164 ? 1 : -1];
typedef char GCGraphicsStateStageOrderOffsetCheck[offsetof(GCGraphicsState, stageOrders) == 0x4CC ? 1 : -1];
typedef char GCGraphicsStateColorInputsOffsetCheck[offsetof(GCGraphicsState, colorInputs) == 0x590 ? 1 : -1];
typedef char GCGraphicsStateAlphaInputsOffsetCheck[offsetof(GCGraphicsState, alphaInputs) == 0x690 ? 1 : -1];
typedef char GCGraphicsStateColorOperationOffsetCheck[offsetof(GCGraphicsState, colorOperations) == 0x790 ? 1 : -1];
typedef char GCGraphicsStateAlphaOperationOffsetCheck[offsetof(GCGraphicsState, alphaOperations) == 0x8D0 ? 1 : -1];
typedef char GCGraphicsStateStageSwapOffsetCheck[offsetof(GCGraphicsState, stageSwaps) == 0xAA4 ? 1 : -1];
typedef char GCGraphicsStateIndirectModeOffsetCheck[offsetof(GCGraphicsState, indirectMode) == 0xB64 ? 1 : -1];
typedef char GCGraphicsStateIndirectOrdersOffsetCheck[offsetof(GCGraphicsState, indirectOrders) == 0xB74 ? 1 : -1];
struct GCTextureMatrixIndex0 { u32 reserved:2, texture3:6, texture2:6, texture1:6, texture0:6, position:6; };
struct GCTextureMatrixIndex1 { u32 reserved:8, texture7:6, texture6:6, texture5:6, texture4:6; };
struct GCIndirectMatrix { f32 a0, a1, a2, b0, b1, b2; };
struct GCAASamplePattern { u8 groups[4][6]; };
typedef char GCAASamplePatternSizeCheck[sizeof(GCAASamplePattern) == 24 ? 1 : -1];
union GCAASampleRegister {
    u32 value;
    struct { u32 address:8, sample5:4, sample4:4, sample3:4, sample2:4, sample1:4, sample0:4; } fields;
};
union GCCopyFilterRegister {
    u32 value;
    struct { u32 address:8, coefficient3:6, coefficient2:6, coefficient1:6, coefficient0:6; } fields;
};
struct GCCopyTextureInfo {
    u16 x, y, width, height;
    u16 stride;
    u8 paddingA[2];
    s32 format;
    u32 clamp;
    u8 mipmap, clear;
    u8 padding16[2];
};
typedef char GCCopyTextureInfoSizeCheck[sizeof(GCCopyTextureInfo) == 0x18 ? 1 : -1];
struct GCCopyDisplayInfo {
    u16 x, y, width, height;
    u32 stride;
    u32 clamp, gamma, fieldMode;
    f32 scale;
    u8 clear, red, green, blue, alpha;
    u8 padding21[3];
    u32 depth;
};
typedef char GCCopyDisplayInfoSizeCheck[sizeof(GCCopyDisplayInfo) == 0x28 ? 1 : -1];
struct GCVertexAttributeFormat { s32 attribute, count, type; u8 fraction; u8 padding[3]; };
struct GCVertexDescriptor { s32 attribute, type; };
struct GCGlobalRegisterState {
    u8 field0, field1, pixelFormat, depthFormat, field4;
};
typedef char GCBPRegisterSizeCheck[sizeof(GCBPRegister) == 4 ? 1 : -1];
typedef char GCGlobalRegisterStateSizeCheck[sizeof(GCGlobalRegisterState) == 5 ? 1 : -1];

inline void GCWriteByte(u8 value) { GXWGFifo.u8 = value; }
inline void GCWriteHalf(u16 value) { GXWGFifo.u16 = value; }
inline void GCWriteWord(u32 value) { GXWGFifo.u32 = value; }

#endif
