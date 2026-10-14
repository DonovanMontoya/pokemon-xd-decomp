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
    u8 unmodelled164[0x40];
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
    u8 unmodelled3F8[0x86C];
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
