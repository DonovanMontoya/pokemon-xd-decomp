#include <game/pxdvs/GSAPI/GSgfxM/gamecube_private.hpp>
#include <libc/string.h>

extern "C" {

extern GCGraphicsState *gsgfxState;
struct GCTmemRegion { u32 even, odd; };
GCTmemRegion GSgfx_GCTmemRegions[8] = {
    {0, 0x80000}, {0x10000, 0x88000}, {0x20000, 0x90000}, {0x30000, 0x98000},
    {0x40000, 0xa0000}, {0x50000, 0xa8000}, {0x60000, 0xb0000}, {0x70000, 0xb8000}
};
u32 GSgfx_GCTlutRegions[20] = {
    0xc0000, 0xc2000, 0xc4000, 0xc6000, 0xc8000, 0xca000, 0xcc000, 0xce000,
    0xd0000, 0xd2000, 0xd4000, 0xd6000, 0xd8000, 0xda000, 0xdc000, 0xde000,
    0xe0000, 0xe8000, 0xf0000, 0xf8000
};
static GCAASamplePattern _gcDefaultAASample = {{{6,6,6,6,6,6},{6,6,6,6,6,6},{6,6,6,6,6,6},{6,6,6,6,6,6}}};
u8 GSgfx_GCTexMode0Ids[8] = {0x80, 0x81, 0x82, 0x83, 0xa0, 0xa1, 0xa2, 0xa3};
u8 GSgfx_GCTexMode1Ids[8] = {0x84, 0x85, 0x86, 0x87, 0xa4, 0xa5, 0xa6, 0xa7};
u8 GSgfx_GCTexImage0Ids[8] = {0x88, 0x89, 0x8a, 0x8b, 0xa8, 0xa9, 0xaa, 0xab};
u8 GSgfx_GCTexImage1Ids[8] = {0x8c, 0x8d, 0x8e, 0x8f, 0xac, 0xad, 0xae, 0xaf};
u8 GSgfx_GCTexImage2Ids[8] = {0x90, 0x91, 0x92, 0x93, 0xb0, 0xb1, 0xb2, 0xb3};
u8 GSgfx_GCTexImage3Ids[8] = {0x94, 0x95, 0x96, 0x97, 0xb4, 0xb5, 0xb6, 0xb7};
u8 GSgfx_GCTexTlutIds[8] = {0x98, 0x99, 0x9a, 0x9b, 0xb8, 0xb9, 0xba, 0xbb};

static u8 _gcDefaultVFilt[7] = {0,0,21,22,21,0,0};

static GXTlutObj *_gcLastTlutObj;
static GXTlut _gcLastTlutName;
static GCGlobalRegisterState _gcGlobalRegState;

#define GC_REGISTER(offset) (*reinterpret_cast<GCBPRegister *>(reinterpret_cast<u8 *>(gsgfxState) + (offset)))
#define GC_BYTE(offset) (*(reinterpret_cast<u8 *>(gsgfxState) + (offset)))
#define GC_HALF(offset) (*reinterpret_cast<u16 *>(reinterpret_cast<u8 *>(gsgfxState) + (offset)))
#define GC_FLOAT(offset) (*reinterpret_cast<f32 *>(reinterpret_cast<u8 *>(gsgfxState) + (offset)))
#define GC_WORD(offset) (*reinterpret_cast<u32 *>(reinterpret_cast<u8 *>(gsgfxState) + (offset)))

static inline u8 *GCAppendBP(u8 *destination, const void *registerValue) {
    u8 *out = static_cast<u8 *>(destination);
    out[0] = GX_LOAD_BP_REG;
    *reinterpret_cast<u32 *>(out + 1) = *static_cast<const u32 *>(registerValue);
    return out + 5;
}

u8 *GSgfx_GCWriteCopyFilterDirect(u8 *destination, u8 antialias, const GCAASamplePattern *samples, u8 verticalFilter, const u8 filter[7]) {
    if (antialias == 0) samples = &_gcDefaultAASample;
    if (verticalFilter == 0) filter = _gcDefaultVFilt;
    GCAASampleRegister sample;
    GCCopyFilterRegister coefficients;
    for (s32 i = 0; i < 4; ++i) {
        sample.fields.address = i + 1;
        sample.fields.sample0 = samples->groups[i][0];
        sample.fields.sample1 = samples->groups[i][1];
        sample.fields.sample2 = samples->groups[i][2];
        sample.fields.sample3 = samples->groups[i][2];
        sample.fields.sample4 = samples->groups[i][4];
        sample.fields.sample5 = samples->groups[i][4];
        destination = GCAppendBP(destination, &sample);
    }
    coefficients.fields.address = 0x53;
    coefficients.fields.coefficient0 = filter[0];
    coefficients.fields.coefficient1 = filter[1];
    coefficients.fields.coefficient2 = filter[2];
    coefficients.fields.coefficient3 = filter[3];
    destination = GCAppendBP(destination, &coefficients);
    coefficients.fields.address = 0x54;
    coefficients.fields.coefficient0 = filter[4];
    coefficients.fields.coefficient1 = filter[5];
    coefficients.fields.coefficient2 = filter[6];
    coefficients.fields.coefficient3 = 0;
    return GCAppendBP(destination, &coefficients);
}

void GSgfx_GCWriteCopyFilter( u8 antialias, const GCAASamplePattern *samples, u8 verticalFilter, const u8 filter[7]) {
    if (antialias == 0) samples = &_gcDefaultAASample;
    if (verticalFilter == 0) filter = _gcDefaultVFilt;
    GCAASampleRegister sample;
    GCCopyFilterRegister coefficients;
    for (s32 i = 0; i < 4; ++i) {
        sample.fields.address = i + 1;
        sample.fields.sample0 = samples->groups[i][0];
        sample.fields.sample1 = samples->groups[i][1];
        sample.fields.sample2 = samples->groups[i][2];
        sample.fields.sample3 = samples->groups[i][2];
        sample.fields.sample4 = samples->groups[i][4];
        sample.fields.sample5 = samples->groups[i][4];
        GCWriteByte(GX_LOAD_BP_REG);
        GCWriteWord(sample.value);
    }
    coefficients.fields.address = 0x53;
    coefficients.fields.coefficient0 = filter[0];
    coefficients.fields.coefficient1 = filter[1];
    coefficients.fields.coefficient2 = filter[2];
    coefficients.fields.coefficient3 = filter[3];
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(coefficients.value);
    coefficients.fields.address = 0x54;
    coefficients.fields.coefficient0 = filter[4];
    coefficients.fields.coefficient1 = filter[5];
    coefficients.fields.coefficient2 = filter[6];
    coefficients.fields.coefficient3 = 0;
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(coefficients.value);
}

void GSgfx_GCWriteFog(u32 type, f32 start, f32 end, f32 nearPlane, f32 farPlane) {
    f32 c;
    f32 a;
    s32 exponent;
    s32 function = type & 7;
    u32 projection = (type >> 3) & 1;
    if (function != 0) {
        u32 magnitude;
        if (projection != 0) {
            if (farPlane == nearPlane || end == start) {
                a = 0.0f;
                c = 0.0f;
            } else {
                f32 reciprocal = 1.0f / (end - start);
                a = reciprocal * (farPlane - nearPlane);
                c = reciprocal * (start - nearPlane);
            }
            exponent = 0;
            magnitude = 0;
        } else {
            f32 numerator;
            f32 mantissa;
            if (farPlane == nearPlane || end == start) {
                numerator = 0.0f;
                mantissa = 0.5f;
                c = 0.0f;
            } else {
                f32 depthRange = farPlane - nearPlane;
                f32 fogRange = end - start;
                mantissa = farPlane / depthRange;
                numerator = (farPlane * nearPlane) / (depthRange * fogRange);
                c = start / fogRange;
            }
            exponent = 1;
            while (mantissa > 1.0f) {
                mantissa *= 0.5f;
                ++exponent;
            }
            while (mantissa > 0.0f && mantissa < 0.5f) {
                mantissa *= 2.0f;
                --exponent;
            }
            a = numerator / static_cast<f32>(1 << exponent);
            magnitude = static_cast<u32>(8.388638e6f * mantissa);
        }
        u32 aBits = *reinterpret_cast<u32 *>(&a);
        u32 cBits = *reinterpret_cast<u32 *>(&c);
        gsgfxState->fogA.parameter = aBits >> 12;
        gsgfxState->fogB.parameter = magnitude;
        gsgfxState->fogExponent.parameter = exponent;
        gsgfxState->fogC.parameter = cBits >> 12;
        gsgfxState->fogC.projection = projection;
        GC_WORD(0) |= 0x8000;
    }
    gsgfxState->fogC.function = function;
    GC_WORD(0) |= 0x10000;
    GC_WORD(0xBF4) = type;
    GC_FLOAT(0xBF8) = start;
    GC_FLOAT(0xBFC) = end;
    GC_FLOAT(0xC00) = nearPlane;
    GC_FLOAT(0xC04) = farPlane;
}

static inline void GCSetTevIndirect(s32 stage, u8 indirectStage, s32 format, s32 bias, s32 matrix, s32 wrapS, s32 wrapT, s32 addPrevious, s32 originalLod, s32 alpha) {
    gsgfxState->tevIndirect[stage].indirect.stage = indirectStage;
    gsgfxState->tevIndirect[stage].indirect.format = format;
    gsgfxState->tevIndirect[stage].indirect.bias = bias;
    gsgfxState->tevIndirect[stage].indirect.alpha = alpha;
    gsgfxState->tevIndirect[stage].indirect.matrix = matrix;
    gsgfxState->tevIndirect[stage].indirect.wrapS = wrapS;
    gsgfxState->tevIndirect[stage].indirect.wrapT = wrapT;
    gsgfxState->tevIndirect[stage].indirect.originalLod = originalLod;
    gsgfxState->tevIndirect[stage].indirect.addPrevious = addPrevious;
    gsgfxState->dirtyGroups[10] |= 1 << stage;
    GC_BYTE(0xB64 + stage) = 2;
}

void GSgfx_GCWriteTevIndBumpST(s32 stage, u8 indirectStage, s32 matrix) {
    s32 sMatrix;
    u8 tMatrix;
    switch (matrix) {
    case 1: sMatrix = 5; tMatrix = 9; break;
    case 2: sMatrix = 6; tMatrix = 10; break;
    case 3: sMatrix = 7; tMatrix = 11; break;
    default: return;
    }
    GCSetTevIndirect(stage, indirectStage, 0, 3, sMatrix, 6, 6, 0, 0, 0);
    GCSetTevIndirect(stage + 1, indirectStage, 0, 3, tMatrix, 6, 6, 1, 0, 0);
    GCSetTevIndirect(stage + 2, indirectStage, 0, 0, 0, 0, 0, 1, 0, 0);
}

void GSgfx_GCWriteTevIndTile(s32 stage, u8 indirectStage, u16 tileSizeS, u16 tileSizeT, u16 spacingS, u16 spacingT, s32 format, s32 matrix, s32 bias, s32 alpha) {
    s32 wrapS;
    s32 wrapT;
    switch (tileSizeS) {
    case 256: wrapS = 1; break;
    case 128: wrapS = 2; break;
    case 64: wrapS = 3; break;
    case 32: wrapS = 4; break;
    case 16: wrapS = 5; break;
    default: return;
    }
    switch (tileSizeT) {
    case 256: wrapT = 1; break;
    case 128: wrapT = 2; break;
    case 64: wrapT = 3; break;
    case 32: wrapT = 4; break;
    case 16: wrapT = 5; break;
    default: return;
    }
    f32 scaleS = static_cast<f32>(spacingS) * 0.0009765625f;
    f32 scaleT = static_cast<f32>(spacingT) * 0.0009765625f;
    u16 index = spacingS;
    switch (matrix) {
    case 1: index = 0; break;
    case 2: index = 3; break;
    case 3: index = 6; break;
    }
    s32 zero = static_cast<s32>(0.0f);
    GCWriteByte(0x61);
    GCWriteWord(((index + 6) << 24) | (((zero << 11) & 0x3FF800) | (static_cast<s32>(1024.0f * scaleS) & 0x7FF) | 0xC00000));
    GCWriteByte(0x61);
    GCWriteWord(((index + 7) << 24) | (((static_cast<s32>(1024.0f * scaleT) << 11) & 0x3FF800) | (zero & 0x7FF) | 0x800000));
    GCWriteByte(0x61);
    GCWriteWord(((index + 8) << 24) | ((zero & 0x7FF) | ((zero << 11) & 0x3FF800) | 0x400000));
    GCSetTevIndirect(stage, indirectStage, format, bias, matrix, wrapS, wrapT, 0, 1, alpha);
}

void GSgfx_GCWriteIndTexMtx(GXIndTexMtxID index, const GCIndirectMatrix *matrix, s32 exponentInput) {
    switch (index) {
    case GX_ITM_0: index = static_cast<GXIndTexMtxID>(0); break;
    case GX_ITM_1: index = static_cast<GXIndTexMtxID>(3); break;
    case GX_ITM_2: index = static_cast<GXIndTexMtxID>(6); break;
    }
    s8 exponent = exponentInput + 17;
    s32 a, b;
    u32 word;
    a = static_cast<int>(1024.0f * matrix->a0);
    b = static_cast<int>(1024.0f * matrix->b0);
    word = (b << 11) & 0x3FF800;
    word = (word & ~0x7FF) | (a & 0x7FF);
    word = (word & ~0xC00000) | ((exponent << 22) & 0xC00000);
    word = (word & ~0xFF000000) | ((index + 6) << 24);
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(word);
    a = static_cast<int>(1024.0f * matrix->a1);
    b = static_cast<int>(1024.0f * matrix->b1);
    word = (b << 11) & 0x3FF800;
    word = (word & ~0x7FF) | (a & 0x7FF);
    word = (word & ~0xC00000) | ((exponent << 20) & 0xC00000);
    word = (word & ~0xFF000000) | ((index + 7) << 24);
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(word);
    a = static_cast<int>(1024.0f * matrix->a2);
    b = static_cast<int>(1024.0f * matrix->b2);
    word = (b << 11) & 0x3FF800;
    word = (word & ~0x7FF) | (a & 0x7FF);
    word = (word & ~0xC00000) | ((exponent << 18) & 0xC00000);
    word = (word & ~0xFF000000) | ((index + 8) << 24);
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(word);
}

void GSgfx_GCWriteTexCoordGen(u32 coordinate, s32 type, u32 source, s32 matrix, u8 normalize, s32 postMatrix) {
    u32 inputForm = 0;
    u32 generationMode;
    u32 projection = 0;
    u32 sourceRow = 5;
    u32 embossSource = 5;
    u32 embossLight = 0;
    switch (source) {
    case 0: sourceRow = 0; inputForm = 1; break;
    case 1: sourceRow = 1; inputForm = 1; break;
    case 2: sourceRow = 3; inputForm = 1; break;
    case 3: sourceRow = 4; inputForm = 1; break;
    case 19: sourceRow = 2; break;
    case 20: sourceRow = 2; break;
    case 4: sourceRow = 5; break;
    case 5: sourceRow = 6; break;
    case 6: sourceRow = 7; break;
    case 7: sourceRow = 8; break;
    case 8: sourceRow = 9; break;
    case 9: sourceRow = 10; break;
    case 10: sourceRow = 11; break;
    case 11: sourceRow = 12; break;
    case 12: embossSource = 0; break;
    case 13: embossSource = 1; break;
    case 14: embossSource = 2; break;
    case 15: embossSource = 3; break;
    case 16: embossSource = 4; break;
    case 17: embossSource = 5; break;
    case 18: embossSource = 6; break;
    }
    switch (type) {
    case 1: generationMode = 0; break;
    case 0: generationMode = 0; projection = 1; break;
    case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
        embossLight = type - 2; generationMode = 1; break;
    case 10:
        if (static_cast<s32>(source) == 19) generationMode = 2;
        else generationMode = 3;
        break;
    }
    switch (coordinate) {
    case 0:
        reinterpret_cast<GCTextureMatrixIndex0 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f0)->texture0 = matrix;
        gsgfxState->dirty |= 0x40;
        break;
    case 1:
        reinterpret_cast<GCTextureMatrixIndex0 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f0)->texture1 = matrix;
        gsgfxState->dirty |= 0x40;
        break;
    case 2:
        reinterpret_cast<GCTextureMatrixIndex0 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f0)->texture2 = matrix;
        gsgfxState->dirty |= 0x40;
        break;
    case 3:
        reinterpret_cast<GCTextureMatrixIndex0 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f0)->texture3 = matrix;
        gsgfxState->dirty |= 0x40;
        break;
    case 4:
        reinterpret_cast<GCTextureMatrixIndex1 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f4)->texture4 = matrix;
        gsgfxState->dirty |= 0x80;
        break;
    case 5:
        reinterpret_cast<GCTextureMatrixIndex1 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f4)->texture5 = matrix;
        gsgfxState->dirty |= 0x80;
        break;
    case 6:
        reinterpret_cast<GCTextureMatrixIndex1 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f4)->texture6 = matrix;
        gsgfxState->dirty |= 0x80;
        break;
    case 7:
        reinterpret_cast<GCTextureMatrixIndex1 *>(reinterpret_cast<u8 *>(gsgfxState) + 0x1f4)->texture7 = matrix;
        gsgfxState->dirty |= 0x80;
        break;
    }
    GCWriteByte(GX_LOAD_XF_REG);
    GCWriteHalf(0);
    GCWriteHalf(coordinate + 0x1040);
    GCWriteWord((embossLight << 15) | ((embossSource << 12) | ((sourceRow << 7) | ((generationMode << 4) | ((projection * 2) | (inputForm * 4))))));
    GCWriteByte(GX_LOAD_XF_REG);
    GCWriteHalf(0);
    GCWriteHalf(coordinate + 0x1050);
    GCWriteWord((postMatrix - 0x40) | ((normalize << 8) & 0xFF00));
    gsgfxState->textureGenerators[coordinate].type = type;
    gsgfxState->textureGenerators[coordinate].source = source;
    gsgfxState->textureGenerators[coordinate].matrix = matrix;
    gsgfxState->textureGenerators[coordinate].normalize = normalize;
    gsgfxState->textureGenerators[coordinate].postMatrix = postMatrix;
}

void GSgfx_GCWriteLoadTlut(GXTlutObj *object, GXTlut name) {
    _gcLastTlutObj = object;
    _gcLastTlutName = name;
}

void GSgfx_GCWriteVtxAttrFmt(s32 formatIndex, const GCVertexAttributeFormat *formats) {
    s32 positionCount;
    s32 positionType;
    s32 positionFraction;
    s32 normalCount;
    s32 normalType;
    s32 normalIndex3;
    s32 color0Count;
    s32 color0Type;
    s32 color1Count;
    s32 color1Type;
    s32 tex0Count;
    s32 tex0Type;
    u8 tex0Fraction;
    s32 tex1Count;
    s32 tex1Type;
    u8 tex1Fraction;
    s32 tex2Count;
    s32 tex2Type;
    u8 tex2Fraction;
    s32 tex3Count;
    s32 tex3Type;
    u8 tex3Fraction;
    s32 tex4Count;
    s32 tex4Type;
    u8 tex4Fraction;
    s32 tex5Count;
    s32 tex5Type;
    u8 tex5Fraction;
    s32 tex6Count;
    s32 tex6Type;
    u8 tex6Fraction;
    s32 tex7Count;
    s32 tex7Type;
    u8 tex7Fraction;
    s32 attribute;
    s32 count;
    const GCVertexAttributeFormat *format;

    format = formats;
    tex0Type = 4;
    tex1Count = 1;
    tex1Type = 4;
    color0Count = 1;
    tex1Fraction = 0;
    tex2Count = 1;
    color0Type = 5;
    tex2Type = 4;
    tex2Fraction = 0;
    positionCount = 1;
    tex3Count = 1;
    tex3Type = 4;
    color1Count = 1;
    tex3Fraction = 0;
    tex4Count = 1;
    positionType = 4;
    tex4Type = 4;
    tex4Fraction = 0;
    color1Type = 5;
    tex5Count = 1;
    tex5Type = 4;
    positionFraction = 0;
    normalCount = 0;
    tex5Fraction = 0;
    tex6Count = 1;
    normalType = 4;
    normalIndex3 = 0;
    tex6Type = 4;
    tex6Fraction = 0;
    tex0Count = 1;
    tex0Fraction = 0;
    tex7Count = 1;
    tex7Type = 4;
    tex7Fraction = 0;
while ((attribute = format->attribute) != 0xFF) {
        switch (attribute) {
        case 9:
            positionCount = format->count;
            positionType = format->type;
            positionFraction = (s32) format->fraction;
            break;
        case 10:
        case 25:
            count = format->count;
            normalType = format->type;
            if (count == 2) {
                normalCount = 1;
                normalIndex3 = 1;
            } else {
                normalCount = count;
                normalIndex3 = 0;
            }
            break;
        case 11:
            color0Count = format->count;
            color0Type = format->type;
            break;
        case 12:
            color1Count = format->count;
            color1Type = format->type;
            break;
        case 13:
            tex0Type = format->type;
            tex0Count = format->count;
            tex0Fraction = format->fraction;
            break;
        case 14:
            tex1Count = format->count;
            tex1Type = format->type;
            tex1Fraction = format->fraction;
            break;
        case 15:
            tex2Count = format->count;
            tex2Type = format->type;
            tex2Fraction = format->fraction;
            break;
        case 16:
            tex3Count = format->count;
            tex3Type = format->type;
            tex3Fraction = format->fraction;
            break;
        case 17:
            tex4Count = format->count;
            tex4Type = format->type;
            tex4Fraction = format->fraction;
            break;
        case 18:
            tex5Count = format->count;
            tex5Type = format->type;
            tex5Fraction = format->fraction;
            break;
        case 19:
            tex6Count = format->count;
            tex6Type = format->type;
            tex6Fraction = format->fraction;
            break;
        case 20:
            tex7Count = format->count;
            tex7Type = format->type;
            tex7Fraction = format->fraction;
            break;
        }
        ++format;
    }
    GCWriteByte(8);
    GCWriteByte(formatIndex + 0x70);
    GCWriteWord((s32) ((normalIndex3 << 0x1F) | ((tex0Fraction << 0x19) | ((tex0Type << 0x16) | ((tex0Count << 0x15) | ((color1Type << 0x12) | ((color1Count << 0x11) | ((color0Type << 0xE) | ((color0Count << 0xD) | ((normalType << 0xA) | ((normalCount << 9) | ((positionFraction * 0x10) | (positionCount | (positionType * 2))))))))))) | 0x40000000)));
    GCWriteByte(8);
    GCWriteByte(formatIndex + 0x80);
    GCWriteWord((s32) ((tex4Type << 0x1C) | ((tex4Count << 0x1B) | ((tex3Fraction << 0x16) | ((tex3Type << 0x13) | ((tex3Count << 0x12) | ((tex2Fraction << 0xD) | ((tex2Type << 0xA) | ((tex2Count << 9) | ((tex1Fraction * 0x10) | (tex1Count | (tex1Type * 2)))))))))) | 0x80000000));
    GCWriteByte(8);
    GCWriteByte(formatIndex + 0x90);
    GCWriteWord((s32) ((tex7Fraction << 0x1B) | ((tex7Type << 0x18) | ((tex7Count << 0x17) | ((tex6Fraction << 0x12) | ((tex6Type << 0xF) | ((tex6Count << 0xE) | ((tex5Fraction << 9) | ((tex5Type << 6) | (tex4Fraction | (tex5Count << 5)))))))))));
}


void GSgfx_GCWriteArray(GXAttr attribute, const void *base, u8 stride) {
    s32 index = 1;
    if (attribute != GX_VA_NBT) index = attribute - GX_VA_POS;
    GCWriteByte(GX_LOAD_CP_REG);
    GCWriteByte(index + 0xA0);
    GCWriteWord(reinterpret_cast<u32>(base) & 0x3FFFFFFF);
    GCWriteByte(GX_LOAD_CP_REG);
    GCWriteByte(index + 0xB0);
    GCWriteWord(stride);
}

void GSgfx_GCWriteVtxDesc(const GCVertexDescriptor *descriptors) {
    s32 normalComponents;
    s32 colorComponents;
    s32 textureComponents;
    s32 positionMatrix;
    s32 textureMatrices;
    s32 position;
    s32 normal;
    s32 color0;
    s32 color1;
    s32 tex0;
    s32 tex1;
    s32 tex2;
    s32 tex3;
    s32 tex4;
    s32 tex5;
    s32 tex6;
    s32 tex7;
    s32 attribute;
    s32 normalType;
    s32 nbtType;
    const GCVertexDescriptor *descriptor;

    descriptor = descriptors;
    normalComponents = 0;
    colorComponents = 0;
    textureComponents = 0;
    positionMatrix = 0;
    textureMatrices = 0;
    position = 1;
    normal = 0;
    color0 = 0;
    color1 = 0;
    tex0 = 0;
    tex1 = 0;
    tex2 = 0;
    tex3 = 0;
    tex4 = 0;
    tex5 = 0;
    tex6 = 0;
    tex7 = 0;
while ((attribute = descriptor->attribute) != 0xFF) {
        {
            switch (attribute) {
            case 0:
                positionMatrix = descriptor->type;
                break;
            case 1:
                textureMatrices = (textureMatrices & 0xFFFFFFFE) | descriptor->type;
                break;
            case 2:
                textureMatrices = (textureMatrices & 0xFFFFFFFD) | (descriptor->type * 2);
                break;
            case 3:
                textureMatrices = (textureMatrices & 0xFFFFFFFB) | (descriptor->type * 4);
                break;
            case 4:
                textureMatrices = (textureMatrices & 0xFFFFFFF7) | (descriptor->type * 8);
                break;
            case 5:
                textureMatrices = (textureMatrices & 0xFFFFFFEF) | (descriptor->type * 0x10);
                break;
            case 6:
                textureMatrices = (textureMatrices & 0xFFFFFFDF) | (descriptor->type << 5);
                break;
            case 7:
                textureMatrices = (textureMatrices & 0xFFFFFFBF) | (descriptor->type << 6);
                break;
            case 8:
                textureMatrices = (textureMatrices & 0xFFFFFF7F) | (descriptor->type << 7);
                break;
            case 9:
                position = descriptor->type;
                break;
            case 10:
                normalType = descriptor->type;
                if (normalType != 0) {
                    normal = normalType;
                    normalComponents = 1;
                }
                break;
            case 25:
                nbtType = descriptor->type;
                if (nbtType != 0) {
                    normal = nbtType;
                    normalComponents = 2;
                }
                break;
            case 11:
                color0 = descriptor->type;
                colorComponents += color0 != 0;
                break;
            case 12:
                color1 = descriptor->type;
                colorComponents += color1 != 0;
                break;
            case 13:
                tex0 = descriptor->type;
                textureComponents += tex0 != 0;
                break;
            case 14:
                tex1 = descriptor->type;
                textureComponents += tex1 != 0;
                break;
            case 15:
                tex2 = descriptor->type;
                textureComponents += tex2 != 0;
                break;
            case 16:
                tex3 = descriptor->type;
                textureComponents += tex3 != 0;
                break;
            case 17:
                tex4 = descriptor->type;
                textureComponents += tex4 != 0;
                break;
            case 18:
                tex5 = descriptor->type;
                textureComponents += tex5 != 0;
                break;
            case 19:
                tex6 = descriptor->type;
                textureComponents += tex6 != 0;
                break;
            case 20:
                tex7 = descriptor->type;
                textureComponents += tex7 != 0;
                break;
            }
        }
        ++descriptor;
    }
    GCWriteByte(8);
    GCWriteByte(0x50);
    GCWriteWord((s32) ((color1 << 0xF) | ((color0 << 0xD) | ((normal << 0xB) | ((position << 9) | (positionMatrix | (textureMatrices * 2)))))));
    GCWriteByte(8);
    GCWriteByte(0x60);
    GCWriteWord((s32) ((tex7 << 0xE) | ((tex6 << 0xC) | ((tex5 << 0xA) | ((tex4 << 8) | ((tex3 << 6) | ((tex2 * 0x10) | (tex0 | (tex1 * 4)))))))));
    GCWriteByte(0x10);
    GCWriteHalf(0);
    GCWriteHalf(0x1008);
    GCWriteWord((s32) ((textureComponents * 0x10) | (colorComponents | (normalComponents * 4))));
}


void GSgfx_GCInvalidateState(void) {
    u32 invalid = 0xFEFEFEFE;
    GC_WORD(0x358) = invalid;
    GC_WORD(0x35C) = invalid;
    GC_WORD(0x360) = invalid;
    GC_BYTE(0x364) = 0xFE;
    GC_WORD(0x368) = invalid;
    GC_WORD(0x36C) = invalid;
    GC_WORD(0x370) = invalid;
    GC_WORD(0x374) = invalid;
    GC_BYTE(0x378) = 0xFE;
    GC_WORD(0x37C) = invalid;
    GC_WORD(0x380) = invalid;
    GC_WORD(0x384) = invalid;
    GC_WORD(0x388) = invalid;
    GC_BYTE(0x38C) = 0xFE;
    GC_WORD(0x390) = invalid;
    GC_WORD(0x394) = invalid;
    GC_WORD(0x398) = invalid;
    GC_WORD(0x39C) = invalid;
    GC_BYTE(0x3A0) = 0xFE;
    GC_WORD(0x3A4) = invalid;
    GC_WORD(0x3A8) = invalid;
    GC_WORD(0x3AC) = invalid;
    GC_WORD(0x3B0) = invalid;
    GC_BYTE(0x3B4) = 0xFE;
    GC_WORD(0x3B8) = invalid;
    GC_WORD(0x3BC) = invalid;
    GC_WORD(0x3C0) = invalid;
    GC_WORD(0x3C4) = invalid;
    GC_BYTE(0x3C8) = 0xFE;
    GC_WORD(0x3CC) = invalid;
    GC_WORD(0x3D0) = invalid;
    GC_WORD(0x3D4) = invalid;
    GC_WORD(0x3D8) = invalid;
    GC_BYTE(0x3DC) = 0xFE;
    GC_WORD(0x3E0) = invalid;
    GC_WORD(0x3E4) = invalid;
    GC_WORD(0x3E8) = invalid;
    GC_WORD(0x3EC) = invalid;
    GC_BYTE(0x3F0) = 0xFE;
    GC_WORD(0x3F4) = invalid;
    GC_BYTE(0x3F8) = 0xFE;
    GC_BYTE(0x3FC) = 0;
    GC_WORD(0x400) = invalid;
    GC_BYTE(0x404) = 0;
    GC_WORD(0x408) = invalid;
    GC_BYTE(0x40C) = 0xFE;
    GC_BYTE(0x40D) = 0xFE;
    GC_BYTE(0x40E) = 0xFE;
    GC_BYTE(0x40F) = 0xFE;
    GC_BYTE(0x410) = 0xFE;
    GC_BYTE(0x411) = 0xFE;
    GC_BYTE(0x412) = 0xFE;
    GC_BYTE(0x413) = 0xFE;
    GC_BYTE(0x414) = 0xFE;
    GC_BYTE(0x415) = 0xFE;
    GC_BYTE(0x416) = 0xFE;
    GC_BYTE(0x417) = 0xFE;
    GC_BYTE(0x418) = 0xFE;
    GC_BYTE(0x419) = 0xFE;
    GC_BYTE(0x41A) = 0xFE;
    GC_BYTE(0x41B) = 0xFE;
    GC_WORD(0x41C) = invalid;
    GC_BYTE(0x438) = 0xFE;
    GC_WORD(0x43C) = invalid;
    GC_WORD(0x440) = invalid;
    GC_HALF(0x444) = 0xFEFE;
    GC_HALF(0x446) = 0xFEFE;
    GC_HALF(0x448) = 0xFEFE;
    GC_HALF(0x44A) = 0xFEFE;
    GC_WORD(0x44C) = invalid;
    GC_WORD(0x450) = invalid;
    GC_FLOAT(0xC24) = -1.0f;
    GC_FLOAT(0xC28) = -1.0f;
    GC_FLOAT(0xC2C) = -1.0f;
    GC_FLOAT(0xC30) = -1.0f;
    GC_FLOAT(0xC34) = 0.0f;
    GC_FLOAT(0xC38) = 1.0f;
    GC_WORD(0xC3C) = invalid;
    GC_BYTE(0x454) = 0xFE;
    GC_BYTE(0x458) = 0xFE;
    GC_WORD(0x45C) = invalid;
    GC_WORD(0x460) = invalid;
    GC_WORD(0x464) = invalid;
    GC_WORD(0x468) = invalid;
    GC_WORD(0x46C) = invalid;
    GC_BYTE(0x470) = 0xFE;
    GC_WORD(0x474) = invalid;
    GC_WORD(0x478) = invalid;
    GC_WORD(0x47C) = invalid;
    GC_WORD(0x480) = invalid;
    GC_WORD(0x484) = invalid;
    GC_BYTE(0x488) = 0xFE;
    GC_WORD(0x48C) = invalid;
    GC_WORD(0x490) = invalid;
    GC_WORD(0x494) = invalid;
    GC_WORD(0x498) = invalid;
    GC_WORD(0x49C) = invalid;
    GC_BYTE(0x4A0) = 0xFE;
    GC_WORD(0x4A4) = invalid;
    GC_WORD(0x4A8) = invalid;
    GC_WORD(0x4AC) = invalid;
    GC_WORD(0x4B0) = invalid;
    GC_WORD(0x4B4) = invalid;
    GC_BYTE(0x4B8) = 1;
    GC_BYTE(0x4C2) = 1;
    GC_BYTE(0x4BD) = 1;
    GC_BYTE(0x4C7) = 1;
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->stageOrders[i].coordinate = invalid;
        gsgfxState->stageOrders[i].texture = invalid;
        gsgfxState->stageOrders[i].channel = invalid;
    }
    GC_BYTE(0x58C) = 0xFE;
    GC_BYTE(0x58D) = 0xFE;
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->colorInputs[i].a = invalid;
        gsgfxState->colorInputs[i].b = invalid;
        gsgfxState->colorInputs[i].c = invalid;
        gsgfxState->colorInputs[i].d = invalid;
    }
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->alphaInputs[i].a = invalid;
        gsgfxState->alphaInputs[i].b = invalid;
        gsgfxState->alphaInputs[i].c = invalid;
        gsgfxState->alphaInputs[i].d = invalid;
    }
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->colorOperations[i].operation = invalid;
        gsgfxState->colorOperations[i].bias = invalid;
        gsgfxState->colorOperations[i].scale = invalid;
        gsgfxState->colorOperations[i].clamp = 0xFE;
        gsgfxState->colorOperations[i].output = invalid;
    }
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->alphaOperations[i].operation = invalid;
        gsgfxState->alphaOperations[i].bias = invalid;
        gsgfxState->alphaOperations[i].scale = invalid;
        gsgfxState->alphaOperations[i].clamp = 0xFE;
        gsgfxState->alphaOperations[i].output = invalid;
    }
    GC_BYTE(0xA10) = 1;
    GC_BYTE(0xA15) = 1;
    GC_BYTE(0xA1A) = 1;
    GC_BYTE(0xA1F) = 1;
    GC_WORD(0xA24) = invalid;
    GC_WORD(0xA28) = invalid;
    GC_WORD(0xA2C) = invalid;
    GC_WORD(0xA30) = invalid;
    GC_WORD(0xA34) = invalid;
    GC_WORD(0xA38) = invalid;
    GC_WORD(0xA3C) = invalid;
    GC_WORD(0xA40) = invalid;
    GC_WORD(0xA44) = invalid;
    GC_WORD(0xA48) = invalid;
    GC_WORD(0xA4C) = invalid;
    GC_WORD(0xA50) = invalid;
    GC_WORD(0xA54) = invalid;
    GC_WORD(0xA58) = invalid;
    GC_WORD(0xA5C) = invalid;
    GC_WORD(0xA60) = invalid;
    GC_WORD(0xA64) = invalid;
    GC_WORD(0xA68) = invalid;
    GC_WORD(0xA6C) = invalid;
    GC_WORD(0xA70) = invalid;
    GC_WORD(0xA74) = invalid;
    GC_WORD(0xA78) = invalid;
    GC_WORD(0xA7C) = invalid;
    GC_WORD(0xA80) = invalid;
    GC_WORD(0xA84) = invalid;
    GC_WORD(0xA88) = invalid;
    GC_WORD(0xA8C) = invalid;
    GC_WORD(0xA90) = invalid;
    GC_WORD(0xA94) = invalid;
    GC_WORD(0xA98) = invalid;
    GC_WORD(0xA9C) = invalid;
    GC_WORD(0xAA0) = invalid;
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->stageSwaps[i].raster = invalid;
        gsgfxState->stageSwaps[i].texture = invalid;
    }
    GC_WORD(0xB24) = invalid;
    GC_WORD(0xB28) = invalid;
    GC_WORD(0xB2C) = invalid;
    GC_WORD(0xB30) = invalid;
    GC_WORD(0xB34) = invalid;
    GC_WORD(0xB38) = invalid;
    GC_WORD(0xB3C) = invalid;
    GC_WORD(0xB40) = invalid;
    GC_WORD(0xB44) = invalid;
    GC_WORD(0xB48) = invalid;
    GC_WORD(0xB4C) = invalid;
    GC_WORD(0xB50) = invalid;
    GC_WORD(0xB54) = invalid;
    GC_WORD(0xB58) = invalid;
    GC_WORD(0xB5C) = invalid;
    GC_WORD(0xB60) = invalid;
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->indirectMode[i] = 0xFE;
    }
    GC_WORD(0xB74) = invalid;
    GC_WORD(0xB78) = invalid;
    GC_WORD(0xB7C) = invalid;
    GC_WORD(0xB80) = invalid;
    GC_WORD(0xB84) = invalid;
    GC_WORD(0xB88) = invalid;
    GC_WORD(0xB8C) = invalid;
    GC_WORD(0xB90) = invalid;
    GC_WORD(0xB94) = invalid;
    GC_WORD(0xB98) = invalid;
    GC_WORD(0xB9C) = invalid;
    GC_WORD(0xBA0) = invalid;
    GC_WORD(0xBA4) = invalid;
    GC_WORD(0xBA8) = invalid;
    GC_WORD(0xBAC) = invalid;
    GC_WORD(0xBB0) = invalid;
    GC_WORD(0xBB4) = invalid;
    GC_WORD(0xBB8) = invalid;
    GC_WORD(0xBBC) = invalid;
    GC_WORD(0xBC0) = invalid;
    GC_BYTE(0xBC4) = 0xFE;
    GC_BYTE(0xBC5) = 0xFE;
    GC_WORD(0xBC8) = invalid;
    GC_WORD(0xBCC) = invalid;
    GC_WORD(0xBD0) = invalid;
    GC_BYTE(0xBD4) = 0xFE;
    GC_BYTE(0xBD5) = 0xFE;
    GC_WORD(0xBD8) = invalid;
    GC_WORD(0xBDC) = invalid;
    GC_WORD(0xBE0) = invalid;
    GC_BYTE(0xBE4) = 0xFE;
    GC_WORD(0xBE8) = invalid;
    GC_BYTE(0xBEC) = 0xFE;
    GC_BYTE(0xBF0) = 0xFE;
    GC_BYTE(0xBF1) = 0xFE;
    GC_BYTE(0xBF2) = 0xFE;
    GC_BYTE(0xBF3) = 0xFE;
    GC_WORD(0xBF4) = invalid;
    GC_FLOAT(0xBF8) = 4.2781243e9f;
    GC_FLOAT(0xBFC) = 4.2781243e9f;
    GC_FLOAT(0xC00) = 4.2781243e9f;
    GC_FLOAT(0xC04) = 4.2781243e9f;
    GC_BYTE(0xC08) = 1;
    GC_HALF(0xC0E) = 0xFEFE;
    GC_BYTE(0xC0D) = 0xFE;
}

void GSgfx_GCInitState(void) {
    u32 i = 0;
    gsgfxState->bp30[0].value = 0;
    gsgfxState->bp30[0].fields.address = 0x0;
    gsgfxState->bp30[1].value = 0;
    gsgfxState->bp30[1].fields.address = 0x40;
    gsgfxState->bp30[2].value = 0;
    gsgfxState->bp30[2].fields.address = 0x41;
    gsgfxState->bp30[3].value = 0;
    gsgfxState->bp30[3].fields.address = 0x42;
    gsgfxState->bp30[4].value = 0;
    gsgfxState->bp30[4].fields.address = 0x43;
    gsgfxState->bp30[5].value = 0;
    gsgfxState->bp30[5].fields.address = 0x47;
    gsgfxState->bp30[6].value = 0;
    gsgfxState->bp30[6].fields.address = 0x48;
    gsgfxState->tevOrder[0].value = 0;
    gsgfxState->tevOrder[0].fields.address = 0x28;
    gsgfxState->tevOrder[1].value = 0;
    gsgfxState->tevOrder[1].fields.address = 0x29;
    gsgfxState->tevOrder[2].value = 0;
    gsgfxState->tevOrder[2].fields.address = 0x2a;
    gsgfxState->tevOrder[3].value = 0;
    gsgfxState->tevOrder[3].fields.address = 0x2b;
    gsgfxState->tevOrder[4].value = 0;
    gsgfxState->tevOrder[4].fields.address = 0x2c;
    gsgfxState->tevOrder[5].value = 0;
    gsgfxState->tevOrder[5].fields.address = 0x2d;
    gsgfxState->tevOrder[6].value = 0;
    gsgfxState->tevOrder[6].fields.address = 0x2e;
    gsgfxState->tevOrder[7].value = 0;
    gsgfxState->tevOrder[7].fields.address = 0x2f;
    gsgfxState->indirectReference.value = 0;
    gsgfxState->indirectReference.fields.address = 0x27;
    gsgfxState->indirectScale[0].value = 0;
    gsgfxState->indirectScale[0].fields.address = 0x25;
    gsgfxState->indirectScale[1].value = 0;
    gsgfxState->indirectScale[1].fields.address = 0x26;
    for (; i < 8; ++i) {
        gsgfxState->textureMode0[i].value = 0;
        gsgfxState->textureMode1[i].value = 0;
        gsgfxState->textureImage0[i].value = 0;
        gsgfxState->textureImage1[i].value = 0;
        gsgfxState->textureImage2[i].value = 0;
        gsgfxState->textureImage3[i].value = 0;
        gsgfxState->textureTlut[i].value = 0;
        gsgfxState->textureMode0[i].fields.address = GSgfx_GCTexMode0Ids[i];
        gsgfxState->textureMode1[i].fields.address = GSgfx_GCTexMode1Ids[i];
        gsgfxState->textureImage0[i].fields.address = GSgfx_GCTexImage0Ids[i];
        gsgfxState->textureImage1[i].fields.address = GSgfx_GCTexImage1Ids[i];
        gsgfxState->textureImage2[i].fields.address = GSgfx_GCTexImage2Ids[i];
        gsgfxState->textureImage3[i].fields.address = GSgfx_GCTexImage3Ids[i];
        gsgfxState->textureTlut[i].fields.address = GSgfx_GCTexTlutIds[i];
    }
    gsgfxState->bp1A4[0].value = 0;
    gsgfxState->bp1A4[0].fields.address = 0x64;
    gsgfxState->bp1A4[1].value = 0;
    gsgfxState->bp1A4[1].fields.address = 0x65;
    gsgfxState->textureSizeS[0].value = 0;
    gsgfxState->textureSizeT[0].value = 0;
    gsgfxState->textureSizeS[0].fields.address = 0x30;
    gsgfxState->textureSizeT[0].fields.address = 0x31;
    gsgfxState->textureSizeS[1].value = 0;
    gsgfxState->textureSizeT[1].value = 0;
    gsgfxState->textureSizeS[1].fields.address = 0x32;
    gsgfxState->textureSizeT[1].fields.address = 0x33;
    gsgfxState->textureSizeS[2].value = 0;
    gsgfxState->textureSizeT[2].value = 0;
    gsgfxState->textureSizeS[2].fields.address = 0x34;
    gsgfxState->textureSizeT[2].fields.address = 0x35;
    gsgfxState->textureSizeS[3].value = 0;
    gsgfxState->textureSizeT[3].value = 0;
    gsgfxState->textureSizeS[3].fields.address = 0x36;
    gsgfxState->textureSizeT[3].fields.address = 0x37;
    gsgfxState->textureSizeS[4].value = 0;
    gsgfxState->textureSizeT[4].value = 0;
    gsgfxState->textureSizeS[4].fields.address = 0x38;
    gsgfxState->textureSizeT[4].fields.address = 0x39;
    gsgfxState->textureSizeS[5].value = 0;
    gsgfxState->textureSizeT[5].value = 0;
    gsgfxState->textureSizeS[5].fields.address = 0x3a;
    gsgfxState->textureSizeT[5].fields.address = 0x3b;
    gsgfxState->textureSizeS[6].value = 0;
    gsgfxState->textureSizeT[6].value = 0;
    gsgfxState->textureSizeS[6].fields.address = 0x3c;
    gsgfxState->textureSizeT[6].fields.address = 0x3d;
    gsgfxState->textureSizeS[7].value = 0;
    gsgfxState->textureSizeT[7].value = 0;
    gsgfxState->textureSizeS[7].fields.address = 0x3e;
    gsgfxState->textureSizeT[7].fields.address = 0x3f;
    gsgfxState->bp1EC.value = 0;
    gsgfxState->bp1EC.fields.address = 0x22;
    GC_REGISTER(0x1f0).value = 0;
    GC_REGISTER(0x1f4).value = 0;
    gsgfxState->bp1F8[0].value = 0;
    gsgfxState->bp1F8[0].fields.address = 0xf3;
    gsgfxState->tevColorA[0].value = 0;
    gsgfxState->tevColorB[0].value = 0;
    gsgfxState->tevColorA[0].fields.address = 0xe0;
    gsgfxState->tevColorB[0].fields.address = 0xe1;
    gsgfxState->tevColorA[0].color.bank = 0;
    gsgfxState->tevColorB[0].color.bank = 0;
    gsgfxState->tevColorA[1].value = 0;
    gsgfxState->tevColorB[1].value = 0;
    gsgfxState->tevColorA[1].fields.address = 0xe2;
    gsgfxState->tevColorB[1].fields.address = 0xe3;
    gsgfxState->tevColorA[1].color.bank = 0;
    gsgfxState->tevColorB[1].color.bank = 0;
    gsgfxState->tevColorA[2].value = 0;
    gsgfxState->tevColorB[2].value = 0;
    gsgfxState->tevColorA[2].fields.address = 0xe4;
    gsgfxState->tevColorB[2].fields.address = 0xe5;
    gsgfxState->tevColorA[2].color.bank = 0;
    gsgfxState->tevColorB[2].color.bank = 0;
    gsgfxState->tevColorA[3].value = 0;
    gsgfxState->tevColorB[3].value = 0;
    gsgfxState->tevColorA[3].fields.address = 0xe6;
    gsgfxState->tevColorB[3].fields.address = 0xe7;
    gsgfxState->tevColorA[3].color.bank = 0;
    gsgfxState->tevColorB[3].color.bank = 0;
    gsgfxState->tevConstantColorA[0].value = 0;
    gsgfxState->tevConstantColorB[0].value = 0;
    gsgfxState->tevConstantColorA[0].fields.address = 0xe0;
    gsgfxState->tevConstantColorB[0].fields.address = 0xe1;
    gsgfxState->tevConstantColorA[0].color.bank = 1;
    gsgfxState->tevConstantColorB[0].color.bank = 1;
    gsgfxState->tevConstantColorA[1].value = 0;
    gsgfxState->tevConstantColorB[1].value = 0;
    gsgfxState->tevConstantColorA[1].fields.address = 0xe2;
    gsgfxState->tevConstantColorB[1].fields.address = 0xe3;
    gsgfxState->tevConstantColorA[1].color.bank = 1;
    gsgfxState->tevConstantColorB[1].color.bank = 1;
    gsgfxState->tevConstantColorA[2].value = 0;
    gsgfxState->tevConstantColorB[2].value = 0;
    gsgfxState->tevConstantColorA[2].fields.address = 0xe4;
    gsgfxState->tevConstantColorB[2].fields.address = 0xe5;
    gsgfxState->tevConstantColorA[2].color.bank = 1;
    gsgfxState->tevConstantColorB[2].color.bank = 1;
    gsgfxState->tevConstantColorA[3].value = 0;
    gsgfxState->tevConstantColorB[3].value = 0;
    gsgfxState->tevConstantColorA[3].fields.address = 0xe6;
    gsgfxState->tevConstantColorB[3].fields.address = 0xe7;
    gsgfxState->tevConstantColorA[3].color.bank = 1;
    gsgfxState->tevConstantColorB[3].color.bank = 1;
    gsgfxState->bp1F8[1].value = 0;
    gsgfxState->bp1F8[1].fields.address = 0xf4;
    gsgfxState->bp200.value = 0;
    gsgfxState->bp200.fields.address = 0xf5;
    gsgfxState->tevConstantSelect[0].value = 0;
    gsgfxState->tevConstantSelect[0].fields.address = 0xf6;
    gsgfxState->tevConstantSelect[1].value = 0;
    gsgfxState->tevConstantSelect[1].fields.address = 0xf7;
    gsgfxState->tevConstantSelect[2].value = 0;
    gsgfxState->tevConstantSelect[2].fields.address = 0xf8;
    gsgfxState->tevConstantSelect[3].value = 0;
    gsgfxState->tevConstantSelect[3].fields.address = 0xf9;
    gsgfxState->tevConstantSelect[4].value = 0;
    gsgfxState->tevConstantSelect[4].fields.address = 0xfa;
    gsgfxState->tevConstantSelect[5].value = 0;
    gsgfxState->tevConstantSelect[5].fields.address = 0xfb;
    gsgfxState->tevConstantSelect[6].value = 0;
    gsgfxState->tevConstantSelect[6].fields.address = 0xfc;
    gsgfxState->tevConstantSelect[7].value = 0;
    gsgfxState->tevConstantSelect[7].fields.address = 0xfd;
    for (i = 0; i < 8; i += 2) {
        gsgfxState->tevConstantSelect[i].swap.selector0 = 0;
        gsgfxState->tevConstantSelect[i].swap.selector1 = 1;
        gsgfxState->tevConstantSelect[i + 1].swap.selector0 = 2;
        gsgfxState->tevConstantSelect[i + 1].swap.selector1 = 3;
    }
    for (i = 0; i < 16; ++i) {
        gsgfxState->tevColorEnvironment[i].value = 0;
        gsgfxState->tevAlphaEnvironment[i].value = 0;
        gsgfxState->tevColorEnvironment[i].fields.address = 0xC0 + i * 2;
        gsgfxState->tevAlphaEnvironment[i].fields.address = 0xC1 + i * 2;
    }
    for (i = 0; i < 16; ++i) {
        gsgfxState->tevIndirect[i].value = 0;
        gsgfxState->tevIndirect[i].fields.address = 0x10 + i;
    }
    gsgfxState->bp350.value = 0;
    gsgfxState->bp350.fields.address = 0xf;
    *reinterpret_cast<u32 *>(&gsgfxState->fogA) = 0;
    *reinterpret_cast<u32 *>(&gsgfxState->fogB) = 0;
    *reinterpret_cast<u32 *>(&gsgfxState->fogExponent) = 0;
    *reinterpret_cast<u32 *>(&gsgfxState->fogC) = 0;
    gsgfxState->fogA.address = 0xee;
    gsgfxState->fogB.address = 0xef;
    gsgfxState->fogExponent.address = 0xf0;
    gsgfxState->fogC.address = 0xf1;
    gsgfxState->fogColor.value = 0;
    gsgfxState->fogColor.fields.address = 0xf2;
    gsgfxState->bp2F8[0].value = 0;
    gsgfxState->bp2F8[0].fields.address = 0xe8;
    gsgfxState->bp2F8[1].value = 0;
    gsgfxState->bp2F8[1].fields.address = 0xe9;
    gsgfxState->bp2F8[2].value = 0;
    gsgfxState->bp2F8[2].fields.address = 0xea;
    gsgfxState->bp2F8[3].value = 0;
    gsgfxState->bp2F8[3].fields.address = 0xeb;
    gsgfxState->bp2F8[4].value = 0;
    gsgfxState->bp2F8[4].fields.address = 0xec;
    gsgfxState->bp2F8[5].value = 0;
    gsgfxState->bp2F8[5].fields.address = 0xed;
    gsgfxState->bp354.value = 0;
    gsgfxState->bp354.fields.address = 0x68;
    gsgfxState->bp30[7].value = 0;
    gsgfxState->bp30[7].fields.address = 0x20;
    gsgfxState->bp30[8].value = 0;
    gsgfxState->bp30[8].fields.address = 0x21;
    gsgfxState->dirty = 0;
    gsgfxState->dirtyGroups[0] = 0;
    gsgfxState->dirtyGroups[1] = 0;
    gsgfxState->dirtyGroups[2] = 0;
    gsgfxState->dirtyGroups[3] = 0;
    gsgfxState->dirtyGroups[4] = 0;
    gsgfxState->dirtyGroups[6] = 0;
    gsgfxState->dirtyGroups[7] = 0;
    gsgfxState->dirtyGroups[8] = 0;
    gsgfxState->dirtyGroups[9] = 0;
    gsgfxState->dirtyGroups[5] = 0;
    gsgfxState->dirtyGroups[10] = 0;
}

void GSgfx_GCFirstInit(void) {
    memset(&_gcGlobalRegState, 0, sizeof(_gcGlobalRegState));
    _gcGlobalRegState.field0 = 0;
    _gcGlobalRegState.field1 = 0;
    _gcGlobalRegState.pixelFormat = 0;
    _gcGlobalRegState.depthFormat = 0;
    _gcGlobalRegState.field4 = 0;
}

static inline void GCFlushXF(u16 address, u32 value) {
    GCWriteByte(0x10); GCWriteHalf(0); GCWriteHalf(address); GCWriteWord(value);
}
static inline void GCFlushCP(u8 address, u32 value) {
    GCWriteByte(8); GCWriteByte(address); GCWriteWord(value);
}
static inline void GCFlushBP(u32 value) { GCWriteByte(GX_LOAD_BP_REG); GCWriteWord(value); }
#define GC_FLUSH_BP(value) GCFlushBP(value)
void GSgfx_GCFlushState(void) {
    u32 i;
    gsgfxState->bp1EC.coordinateBias.flag = _gcGlobalRegState.field0;
    gsgfxState->bp354.mode.enabled = _gcGlobalRegState.field1;
    gsgfxState->bp30[4].pixel.pixelFormat = _gcGlobalRegState.pixelFormat;
    gsgfxState->bp30[4].pixel.depthFormat = _gcGlobalRegState.depthFormat;
    gsgfxState->bp30[3].field.mode = _gcGlobalRegState.field4;
    if (gsgfxState->dirty & 0x1000) GC_FLUSH_BP(gsgfxState->bp354.value);
    if (gsgfxState->dirtyGroups[3]) {
        for (i = 0; i < 8; ++i) {
            if (gsgfxState->dirtyGroups[3] & (1 << i)) {
                s32 format = gsgfxState->textureImage0[i].image.format;
                switch (format) {
                case 8: case 9: case 10:
                    GC_FLUSH_BP(gsgfxState->textureTlut[i].value);
                    break;
                default: break;
                }
                GC_FLUSH_BP(gsgfxState->textureMode0[i].value);
                GC_FLUSH_BP(gsgfxState->textureMode1[i].value);
                GC_FLUSH_BP(gsgfxState->textureImage0[i].value);
                GC_FLUSH_BP(gsgfxState->textureImage1[i].value);
                GC_FLUSH_BP(gsgfxState->textureImage2[i].value);
                GC_FLUSH_BP(gsgfxState->textureImage3[i].value);
            }
        }
        gsgfxState->dirtyGroups[3] = 0;
    }
    if (gsgfxState->dirtyGroups[2]) {
        for (i = 0; (s32)i < (GC_BYTE(0x31) & 7); ++i) {
            s32 coordinate = gsgfxState->indirectOrders[i].coordinate;
            if (gsgfxState->dirtyGroups[2] & (1 << coordinate)) {
                u32 texture = gsgfxState->indirectOrders[i].texture & 7;
                gsgfxState->textureSizeS[coordinate].dimension.size = gsgfxState->textureImage0[texture].image.width;
                gsgfxState->textureSizeT[coordinate].dimension.size = gsgfxState->textureImage0[texture].image.height;
            }
        }
        for (i = 0; (s32)i < ((GC_BYTE(0x32) >> 2) & 15) + 1; ++i) {
            s32 coordinate = gsgfxState->stageOrders[i].coordinate;
            if (coordinate != 255 && (gsgfxState->dirtyGroups[2] & (1 << coordinate))) {
                u32 texture = gsgfxState->stageOrders[i].texture & 7;
                gsgfxState->textureSizeS[coordinate].dimension.size = gsgfxState->textureImage0[texture].image.width;
                gsgfxState->textureSizeT[coordinate].dimension.size = gsgfxState->textureImage0[texture].image.height;
            }
        }
        for (i = 0; i < 8; ++i) {
            if (gsgfxState->dirtyGroups[2] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->textureSizeS[i].value);
                GC_FLUSH_BP(gsgfxState->textureSizeT[i].value);
            }
        }
        gsgfxState->dirtyGroups[2] = 0;
    }
    if (gsgfxState->dirtyGroups[4]) {
        i = 0;
        GC_FLUSH_BP(gsgfxState->bp350.value);
        for (; i < 8; ++i) {
            if (gsgfxState->dirtyGroups[4] & (1 << i)) {
                gsgfxState->bp1A4[0].tlutSource.source = gsgfxState->tlutUploads[i].source;
                gsgfxState->bp1A4[1].tlutRegion.count = gsgfxState->tlutUploads[i].count;
                gsgfxState->bp1A4[1].tlutRegion.region = gsgfxState->tlutUploads[i].region;
                GC_FLUSH_BP(gsgfxState->bp1A4[0].value);
                GC_FLUSH_BP(gsgfxState->bp1A4[1].value);
                GC_FLUSH_BP(gsgfxState->bp350.value);
            }
        }
        gsgfxState->dirty &= ~0x800;
        gsgfxState->dirtyGroups[4] = 0;
    }
    if (gsgfxState->dirty & 0x1) {
        GC_FLUSH_BP(GC_WORD(0x30));
    }
    if (gsgfxState->dirty & 0x2) {
        GC_FLUSH_BP(GC_WORD(0x34));
    }
    if (gsgfxState->dirty & 0x4) {
        GC_FLUSH_BP(GC_WORD(0x38));
    }
    if (gsgfxState->dirty & 0x8) {
        GC_FLUSH_BP(GC_WORD(0x3c));
    }
    if (gsgfxState->dirty & 0x10) {
        GC_FLUSH_BP(GC_WORD(0x40));
    }
    if (gsgfxState->dirty & 0x20) {
        GC_FLUSH_BP(GC_WORD(0x48));
        GC_FLUSH_BP(GC_WORD(0x44));
    }
    if (gsgfxState->dirty & 0x100) {
        GC_FLUSH_BP(GC_WORD(0x1f8));
    }
    if (gsgfxState->dirty & 0x200) {
        GC_FLUSH_BP(GC_WORD(0x1fc));
        GC_FLUSH_BP(GC_WORD(0x200));
    }
    if (gsgfxState->dirty & 0x400) {
        GC_FLUSH_BP(GC_WORD(0x1ec));
    }
    if (gsgfxState->dirtyGroups[0]) {
        for (i = 0; i < 8; ++i) {
            if (gsgfxState->dirtyGroups[0] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevOrder[i].value);
            }
        }
        gsgfxState->dirtyGroups[0] = 0;
    }
    if (gsgfxState->dirty & 0x2000) GC_FLUSH_BP(gsgfxState->indirectReference.value);
    if (gsgfxState->dirtyGroups[1]) {
        for (i = 0; i < 2; ++i) {
            if (gsgfxState->dirtyGroups[1] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->indirectScale[i].value);
            }
        }
        gsgfxState->dirtyGroups[1] = 0;
    }
    if (gsgfxState->dirtyGroups[6]) {
        for (i = 0; i < 16; ++i) {
            if (gsgfxState->dirtyGroups[6] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevColorEnvironment[i].value);
            }
        }
        gsgfxState->dirtyGroups[6] = 0;
    }
    if (gsgfxState->dirtyGroups[7]) {
        for (i = 0; i < 16; ++i) {
            if (gsgfxState->dirtyGroups[7] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevAlphaEnvironment[i].value);
            }
        }
        gsgfxState->dirtyGroups[7] = 0;
    }
    if (gsgfxState->dirtyGroups[8]) {
        for (i = 0; i < 4; ++i) {
            if (gsgfxState->dirtyGroups[8] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevColorA[i].value);
                GC_FLUSH_BP(gsgfxState->tevColorB[i].value);
                GC_FLUSH_BP(gsgfxState->tevColorB[i].value);
                GC_FLUSH_BP(gsgfxState->tevColorB[i].value);
            }
        }
        gsgfxState->dirtyGroups[8] = 0;
    }
    if (gsgfxState->dirtyGroups[9]) {
        for (i = 0; i < 4; ++i) {
            if (gsgfxState->dirtyGroups[9] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevConstantColorA[i].value);
                GC_FLUSH_BP(gsgfxState->tevConstantColorB[i].value);
            }
        }
        gsgfxState->dirtyGroups[9] = 0;
    }
    if (gsgfxState->dirtyGroups[5]) {
        for (i = 0; i < 8; ++i) {
            if (gsgfxState->dirtyGroups[5] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevConstantSelect[i].value);
            }
        }
        gsgfxState->dirtyGroups[5] = 0;
    }
    if (gsgfxState->dirtyGroups[10]) {
        for (i = 0; i < 16; ++i) {
            if (gsgfxState->dirtyGroups[10] & (1 << i)) {
                GC_FLUSH_BP(gsgfxState->tevIndirect[i].value);
            }
        }
        gsgfxState->dirtyGroups[10] = 0;
    }
    if (gsgfxState->dirty & 0x8000) {
        GC_FLUSH_BP(GC_WORD(0x2e4));
        GC_FLUSH_BP(GC_WORD(0x2e8));
        GC_FLUSH_BP(GC_WORD(0x2ec));
    }
    if (gsgfxState->dirty & 0x10000) {
        GC_FLUSH_BP(GC_WORD(0x2f0));
    }
    if (gsgfxState->dirty & 0x20000) {
        GC_FLUSH_BP(GC_WORD(0x2f4));
    }
    if (gsgfxState->dirty & 0x80000) {
        GC_FLUSH_BP(GC_WORD(0x2fc));
        GC_FLUSH_BP(GC_WORD(0x300));
        GC_FLUSH_BP(GC_WORD(0x304));
        GC_FLUSH_BP(GC_WORD(0x308));
        GC_FLUSH_BP(GC_WORD(0x30c));
    }
    if (gsgfxState->dirty & 0x40000) {
        GC_FLUSH_BP(GC_WORD(0x2f8));
    }
    if (gsgfxState->dirty & 0x4000) {
        GC_FLUSH_BP(GC_WORD(0x4c));
        GC_FLUSH_BP(GC_WORD(0x50));
    }
    if (gsgfxState->dirty & 0x800) {
        GC_FLUSH_BP(GC_WORD(0x350));
    }
    if (gsgfxState->dirty & 0x1000000) {
        GCFlushXF(0x1009, (GC_BYTE(0x33) >> 4) & 3);
    }
    if (gsgfxState->dirty & 0x2000000) {
        GCFlushXF(0x103f, GC_BYTE(0x33) & 15);
    }
    if (gsgfxState->dirty & 0x4000000) {
        GCFlushXF(0x1005, GC_WORD(0x54));
    }
    if (gsgfxState->dirty & 0xc0) {
        if (gsgfxState->dirty & 0x40) {
            GCFlushCP(0x30, gsgfxState->matrixIndices[0]);
        }
        if (gsgfxState->dirty & 0x80) {
            GCFlushCP(0x40, gsgfxState->matrixIndices[1]);
        }
        if ((gsgfxState->dirty & 0xc0) == 0xc0) {
            GCWriteByte(0x10);
            GCWriteHalf(1);
            GCWriteHalf(0x1018);
            GCWriteWord(gsgfxState->matrixIndices[0]);
            GCWriteWord(gsgfxState->matrixIndices[1]);
        } else if (gsgfxState->dirty & 0x40) {
            GCFlushXF(0x1018, gsgfxState->matrixIndices[0]);
        } else {
            GCFlushXF(0x1019, gsgfxState->matrixIndices[1]);
        }
    }
    gsgfxState->dirty = 0;
}
#undef GC_FLUSH_BP

void GSgfx_GCWriteLoadTexObj(const GXTexObj* object, s32 map) {
    gsgfxState->textureMode0[map].fields.payload = object->dummy[0];
    gsgfxState->textureMode1[map].fields.payload = object->dummy[1];
    gsgfxState->textureImage0[map].fields.payload = object->dummy[2];
    gsgfxState->textureImage1[map].imageCache.type = 0;
    gsgfxState->textureImage1[map].imageCache.base = GSgfx_GCTmemRegions[map].even >> 5;
    gsgfxState->textureImage1[map].imageCache.width = 3;
    gsgfxState->textureImage1[map].imageCache.height = 3;
    gsgfxState->textureImage2[map].imageCache.base = GSgfx_GCTmemRegions[map].odd >> 5;
    gsgfxState->textureImage2[map].imageCache.width = 3;
    gsgfxState->textureImage2[map].imageCache.height = 3;
    gsgfxState->textureImage3[map].fields.payload = object->dummy[3];
    switch (gsgfxState->textureImage0[map].image.format) {
    case 8: case 9: case 10: {
        u16 region = (GSgfx_GCTlutRegions[_gcLastTlutName] - 0x80000) >> 9;
        gsgfxState->textureTlut[map].fields.payload = _gcLastTlutObj->dummy[0];
        gsgfxState->textureTlut[map].texturePalette.region = region;
        gsgfxState->tlutUploads[map].source = _gcLastTlutObj->dummy[1] & 0xffffff;
        gsgfxState->tlutUploads[map].count = (s32)*reinterpret_cast<u16 *>(reinterpret_cast<u8 *>(_gcLastTlutObj) + 8) >> 4;
        gsgfxState->tlutUploads[map].region = region;
        gsgfxState->dirtyGroups[4] |= 1 << map;
        break;
    }
    default: break;
    }
    switch (GC_BYTE(0x31) & 7) {
    case 4:
        if (gsgfxState->indirectReference.indirectOrder.texture3 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->indirectReference.indirectOrder.coordinate3;
    case 3:
        if (gsgfxState->indirectReference.indirectOrder.texture2 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->indirectReference.indirectOrder.coordinate2;
    case 2:
        if (gsgfxState->indirectReference.indirectOrder.texture1 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->indirectReference.indirectOrder.coordinate1;
    case 1:
        if (gsgfxState->indirectReference.indirectOrder.texture0 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->indirectReference.indirectOrder.coordinate0;
        break;
    }
    for (u32 i = 0; (s32)i <= ((s32)((GC_BYTE(0x32) >> 2) & 15) >> 1); ++i) {
        if (gsgfxState->tevOrder[i].order.texture0 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->tevOrder[i].order.coordinate0;
        if (gsgfxState->tevOrder[i].order.texture1 == map)
            gsgfxState->dirtyGroups[2] |= 1 << gsgfxState->tevOrder[i].order.coordinate1;
    }
    gsgfxState->dirtyGroups[3] |= 1 << map;
}

static inline void GCFlushRegister(const GCBPRegister* reg) {
    GCWriteByte(GX_LOAD_BP_REG);
    GCWriteWord(reg->value);
}
u8* GSgfx_GCWriteCopyDispDirect(u8* output, const GCCopyDisplayInfo* info, u32 destination, u32 colorUpdate, u32 alphaUpdate, u32 depthUpdate) {
    GCBPRegister clearColor, clearDepth, blend, depth, pixel, scale, source, size, stride, address, control;
    if (info->clear == 1) {
        pixel.value = 0;
        blend.value = 0;
        pixel.copyPixel.pixelFormat = _gcGlobalRegState.pixelFormat;
        blend.copyBlend.blend = 0;
        pixel.copyPixel.depthFormat = _gcGlobalRegState.depthFormat;
        blend.copyBlend.color = (u8)colorUpdate;
        depth.value = 0;
        blend.fields.address = 0x41;
        depth.fields.address = 0x40;
        pixel.fields.address = 0x43;
        pixel.copyPixel.compare = 0;
        blend.copyBlend.alpha = (u8)alphaUpdate;
        if ((u8)depthUpdate == 1) {
            depth.copyDepth.test = 1;
            depth.copyDepth.function = 7;
            depth.copyDepth.update = 1;
        } else {
            depth.copyDepth.test = 0;
            depth.copyDepth.update = 0;
        }
        output = GCAppendBP(output, &blend);
        output = GCAppendBP(output, &depth);
        output = GCAppendBP(output, &pixel);
    }
    clearColor.value = 0;
    clearColor.fields.address = 0x4f;
    clearColor.bytes.payload[1] = info->alpha;
    clearColor.bytes.payload[2] = info->red;
    output = GCAppendBP(output, &clearColor);
    clearDepth.fields.address = 0x51;
    clearColor.fields.address = 0x50;
    clearColor.bytes.payload[1] = info->green;
    clearColor.bytes.payload[2] = info->blue;
    output = GCAppendBP(output, &clearColor);
    scale.value = 0;
    source.value = 0;
    clearDepth.fields.payload = info->depth;
    output = GCAppendBP(output, &clearDepth);
    size.value = 0;
    stride.value = 0;
    address.value = 0;
    control.value = 0;
    scale.fields.address = 0x4e;
    source.fields.address = 0x49;
    size.fields.address = 0x4a;
    stride.fields.address = 0x4d;
    address.fields.address = 0x4b;
    control.fields.address = 0x52;
    control.copyControl.display = 1;
    control.copyControl.clamp = info->clamp;
    control.copyControl.fieldMode = info->fieldMode;
    source.copyRectangle.x = info->x;
    scale.copyScale.scale = (u16)(u32)(256.0f / info->scale);
    size.copyRectangle.x = info->width - 1;
    control.copyControl.gamma = info->gamma;
    control.copyControl.clear = info->clear;
    source.copyRectangle.y = info->y;
    size.copyRectangle.y = info->height - 1;
    stride.copyStride.stride = (s32)info->stride >> 4;
    address.tlutSource.source = destination >> 5;
    if (scale.copyScale.scale == 256) control.copyControl.scale = 0;
    else control.copyControl.scale = 1;
    output = GCAppendBP(output, &scale);
    output = GCAppendBP(output, &source);
    output = GCAppendBP(output, &size);
    output = GCAppendBP(output, &stride);
    output = GCAppendBP(output, &address);
    output = GCAppendBP(output, &control);
    return output;
}

void GSgfx_GCWriteCopyDisp(const GCCopyDisplayInfo* info, u32 destination, u32 colorUpdate, u32 alphaUpdate, u32 depthUpdate) {
    GCBPRegister clearColor, clearDepth, blend, depth, pixel, scale, source, size, stride, address, control;
    if (info->clear == 1) {
        blend.value = 0;
        pixel.value = 0;
        pixel.copyPixel.pixelFormat = _gcGlobalRegState.pixelFormat;
        blend.copyBlend.blend = 0;
        pixel.copyPixel.depthFormat = _gcGlobalRegState.depthFormat;
        blend.copyBlend.color = (u8)colorUpdate;
        depth.value = 0;
        blend.fields.address = 0x41;
        depth.fields.address = 0x40;
        pixel.fields.address = 0x43;
        pixel.copyPixel.compare = 0;
        blend.copyBlend.alpha = (u8)alphaUpdate;
        if ((u8)depthUpdate == 1) {
            depth.copyDepth.test = 1;
            depth.copyDepth.function = 7;
            depth.copyDepth.update = 1;
        } else {
            depth.copyDepth.test = 0;
            depth.copyDepth.update = 0;
        }
        GCFlushRegister(&blend);
        GCFlushRegister(&depth);
        GCFlushRegister(&pixel);
    }
    clearColor.value = 0;
    clearColor.fields.address = 0x4f;
    clearColor.bytes.payload[1] = info->alpha;
    clearColor.bytes.payload[2] = info->red;
    GCFlushRegister(&clearColor);
    clearDepth.fields.address = 0x51;
    clearColor.fields.address = 0x50;
    clearColor.bytes.payload[1] = info->green;
    clearColor.bytes.payload[2] = info->blue;
    GCFlushRegister(&clearColor);
    scale.value = 0;
    source.value = 0;
    clearDepth.fields.payload = info->depth;
    GCFlushRegister(&clearDepth);
    size.value = 0;
    stride.value = 0;
    address.value = 0;
    control.value = 0;
    scale.fields.address = 0x4e;
    source.fields.address = 0x49;
    size.fields.address = 0x4a;
    stride.fields.address = 0x4d;
    address.fields.address = 0x4b;
    control.fields.address = 0x52;
    scale.copyScale.scale = (u32)(256.0f / info->scale);
    size.copyRectangle.x = info->width - 1;
    source.copyRectangle.x = info->x;
    size.copyRectangle.y = info->height - 1;
    stride.copyStride.stride = (s32)info->stride >> 4;
    source.copyRectangle.y = info->y;
    address.tlutSource.source = destination >> 5;
    GCFlushRegister(&scale);
    GCFlushRegister(&source);
    GCFlushRegister(&size);
    GCFlushRegister(&stride);
    GCFlushRegister(&address);
    control.copyControl.display = 1;
    control.copyControl.clamp = info->clamp;
    control.copyControl.fieldMode = info->fieldMode;
    control.copyControl.gamma = info->gamma;
    control.copyControl.clear = info->clear;
    GCFlushRegister(&control);
}

void GSgfx_GCWriteCopyTex(const GCCopyTextureInfo* info, u32 destination) {
    s32 savedBlend = 0xfefefefe;
    u8 savedCompare = 0xfe;
    u32 savedFormat;
    if (info->format & 0x10) {
        savedFormat = gsgfxState->bp30[4].pixel.pixelFormat;
        gsgfxState->bp30[4].pixel.pixelFormat = 3;
        gsgfxState->dirty |= 0x10;
    }
    if (info->clear == 1) {
        u8 compare = GC_BYTE(0xbf0);
        if (compare != 0) {
            savedCompare = compare;
            gsgfxState->bp30[4].copyPixel.compare = 0;
            gsgfxState->dirty |= 0x10;
        }
        s32 blend = GC_WORD(0xbb4);
        if (blend != 0) {
            savedBlend = blend;
            gsgfxState->bp30[2].copyBlend.blend = 0;
            gsgfxState->dirty |= 4;
        }
        if (gsgfxState->dirty & 0x10) GCFlushBP(gsgfxState->bp30[4].value);
        if (gsgfxState->dirty & 4) GCFlushBP(gsgfxState->bp30[2].value);
        gsgfxState->dirty &= ~0x14;
    }
    GCBPRegister source, size, stride, address, control;
    source.value = 0;
    size.value = 0;
    source.fields.address = 0x49;
    s32 format = info->format;
    source.copyRectangle.x = info->x;
    stride.value = 0;
    address.value = 0;
    control.value = 0;
    size.fields.address = 0x4a;
    size.copyRectangle.x = info->width - 1;
    stride.fields.address = 0x4d;
    address.fields.address = 0x4b;
    control.fields.address = 0x52;
    source.copyRectangle.y = info->y;
    size.copyRectangle.y = info->height - 1;
    s32 blockWidth;
    switch (format) {
    case 0: case 1: case 2: case 0xe: case 0x11: case 0x20: case 0x22:
    case 0x27: case 0x28: case 0x29: case 0x2a: case 0x30: case 0x39: case 0x3a:
        blockWidth = 8; break;
    case 3: case 4: case 5: case 0x13: case 0x23: case 0x2b: case 0x2c: case 0x3c:
        blockWidth = 4; break;
    case 6: case 0x16: case 0x26:
        blockWidth = 2; break;
    default: blockWidth = 0; break;
    }
    switch (blockWidth) {
    case 2: stride.copyStride.stride = info->stride >> 1; break;
    case 4: stride.copyStride.stride = info->stride >> 2; break;
    case 8: stride.copyStride.stride = info->stride >> 3; break;
    }
    control.copyControl.clamp = info->clamp;
    format = info->format;
    control.copyControl.depth = (format >> 3) & 1;
    control.copyControl.mipmap = info->mipmap;
    control.copyControl.clear = info->clear;
    address.tlutSource.source = destination >> 5;
    control.copyControl.conversion = 1;
    control.copyControl.format = format;
    if (format >= 0 && format < 4) control.copyControl.intensity = 1;
    else control.copyControl.intensity = 0;
    GCFlushBP(source.value);
    GCFlushBP(size.value);
    GCFlushBP(stride.value);
    GCFlushBP(address.value);
    GCFlushBP(control.value);
    if (info->format & 0x10) {
        gsgfxState->bp30[4].pixel.pixelFormat = savedFormat;
        gsgfxState->dirty |= 0x10;
    }
    if (info->clear == 1) {
        if (savedCompare != 0xfe) {
            gsgfxState->bp30[4].copyPixel.compare = savedCompare;
            gsgfxState->dirty |= 0x10;
        }
        if (savedBlend != (s32)0xfefefefe) {
            gsgfxState->bp30[2].copyBlend.blend = 1;
            gsgfxState->dirty |= 4;
        }
        if (gsgfxState->dirty & 0x10) GCFlushBP(gsgfxState->bp30[4].value);
        if (gsgfxState->dirty & 4) GCFlushBP(gsgfxState->bp30[2].value);
        gsgfxState->dirty &= ~0x14;
    }
}


extern void GSgfxVideoGetEFBSize(u16 *width, u16 *height);

void GSgfx_GCReset(void) {
    for (u32 i = 0; i < 8; ++i) {
        gsgfxState->textureGenerators[i].type = 1;
        gsgfxState->textureGenerators[i].source = i + 4;
        gsgfxState->textureGenerators[i].matrix = 60;
        gsgfxState->textureGenerators[i].normalize = 0;
        gsgfxState->textureGenerators[i].postMatrix = 125;
        GSgfx_GCWriteTexCoordGen(i, 1, i + 4, 60, 0, 125);
    }
    GC_BYTE(0x3f8) = 1;
    GC_BYTE(0x33) = (GC_BYTE(0x33) & ~15) | 1;
    gsgfxState->dirty |= 0x02000001;
    GC_BYTE(0x3f8) = 1;
    GC_BYTE(0x3fc) = 6; GC_WORD(0x400) = 0;
    GC_BYTE(0x1ef) = 6; GC_BYTE(0x1ed) &= ~7;
    gsgfxState->dirty |= 0x400;
    GC_BYTE(0x3fc) = 6; GC_WORD(0x400) = 0;
    GC_BYTE(0x404) = 6; GC_WORD(0x408) = 0;
    GC_BYTE(0x1ee) = 6; GC_BYTE(0x1ed) &= ~0x38;
    gsgfxState->dirty |= 0x400;
    GC_BYTE(0x404) = 6; GC_WORD(0x408) = 0;
    for (u32 i = 0; i < 8; ++i) {
        GC_BYTE(0x40c + i * 2) = 0; GC_BYTE(0x40d + i * 2) = 0;
        GC_BYTE(0x1ad + i * 4) &= ~4;
        GC_BYTE(0x1ad + i * 4) &= ~8;
        gsgfxState->dirtyGroups[2] |= 1 << i;
        GC_BYTE(0x40c + i * 2) = 0; GC_BYTE(0x40d + i * 2) = 0;
    }
    GC_BYTE(0x438) = 0; GC_BYTE(0x31) &= ~8;
    gsgfxState->dirty |= 1; GC_BYTE(0x438) = 0;
    GC_WORD(0x43c) = 2; GC_BYTE(0x32) = (GC_BYTE(0x32) & ~0xc0) | 0x40;
    gsgfxState->dirty |= 1; GC_WORD(0x43c) = 2;
    GC_WORD(0x440) = 0; GC_WORD(0x54) = 0;
    gsgfxState->dirty |= 0x04000000; GC_WORD(0x440) = 0;
    GC_HALF(0x444) = 0; GC_HALF(0x446) = 0;
    GC_WORD(0x44c) = 0; GC_WORD(0x450) = 0;
    GSgfxVideoGetEFBSize(&GC_HALF(0x448), &GC_HALF(0x44a));
    u16 width = GC_HALF(0x448), height = GC_HALF(0x44a);
    GC_WORD(0x4c) = (GC_WORD(0x4c) & ~0xfff000) | 0x156000;
    GC_HALF(0x4e) = (GC_HALF(0x4e) & ~0xfff) | 342;
    GC_WORD(0x50) = (GC_WORD(0x50) & ~0xfff000) | (((((GC_WORD(0x4c) >> 12) & 0xfff) + width - 1) << 12) & 0xfff000);
    GC_HALF(0x52) = (GC_HALF(0x52) & ~0xfff) | (((GC_HALF(0x4e) & 0xfff) + height - 1) & 0xfff);
    gsgfxState->dirty |= 0x4000;
    GC_HALF(0x444) = 0; GC_HALF(0x446) = 0;
    GC_HALF(0x448) = width; GC_HALF(0x44a) = height;
    GC_WORD(0x44c) = 0; GC_WORD(0x450) = 0;
    GC_FLOAT(0xc24) = 0.0f; GC_FLOAT(0xc28) = 0.0f;
    GC_FLOAT(0xc2c) = (f32)GC_HALF(0x448);
    GC_FLOAT(0xc30) = (f32)GC_HALF(0x44a);
    GC_FLOAT(0xc34) = 0.0f; GC_FLOAT(0xc38) = 1.0f;
    GC_WORD(0xc3c) = 1;
    u32 viewportMode = GC_WORD(0xc3c);
    f32 farPlane = GC_FLOAT(0xc38), nearPlane = GC_FLOAT(0xc34);
    f32 viewportHeight = GC_FLOAT(0xc30), viewportWidth = GC_FLOAT(0xc2c);
    f32 y = GC_FLOAT(0xc28), x = GC_FLOAT(0xc24);
    if (viewportMode == 0) y -= 0.5f;
    f32 halfHeight = viewportHeight * 0.5f, halfWidth = viewportWidth * 0.5f;
    f32 farDepth = farPlane * 16777216.0f;
    GCWriteByte(0x10); GCWriteHalf(5); GCWriteHalf(0x101a);
    GXWGFifo.f32 = halfWidth;
    GXWGFifo.f32 = -halfHeight;
    GXWGFifo.f32 = -((nearPlane * 16777216.0f) - farDepth);
    GXWGFifo.f32 = 342.0f + (x + halfWidth);
    GXWGFifo.f32 = 342.0f + (y + halfHeight);
    GXWGFifo.f32 = farDepth + 0.0f;
    GC_FLOAT(0xc24) = x; GC_FLOAT(0xc28) = y;
    GC_FLOAT(0xc2c) = viewportWidth; GC_FLOAT(0xc30) = viewportHeight;
    GC_FLOAT(0xc34) = nearPlane; GC_FLOAT(0xc38) = farPlane;
    GC_WORD(0xc3c) = viewportMode;
    GC_BYTE(0x454) = 0; GC_BYTE(0x33) &= ~0x30;
    gsgfxState->dirty |= 0x01000001; GC_BYTE(0x454) = 0;
    for (u32 i = 0; i < 4; ++i) {
        GC_BYTE(0x458 + i * 24) = 0; GC_WORD(0x45c + i * 24) = 0;
        GC_WORD(0x460 + i * 24) = 1; GC_WORD(0x464 + i * 24) = 0;
        GC_WORD(0x468 + i * 24) = 0; GC_WORD(0x46c + i * 24) = 2;
        GCFlushXF(0x100e + (i & 3), 0x401);
        GC_BYTE(0x458 + i * 24) = 0; GC_WORD(0x45c + i * 24) = 0;
        GC_WORD(0x460 + i * 24) = 1; GC_WORD(0x464 + i * 24) = 0;
        GC_WORD(0x468 + i * 24) = 0; GC_WORD(0x46c + i * 24) = 2;
    }
    for (u32 i = 0; i < 4; ++i) {
        GC_WORD(0x4b9 + i * 5) = 0;
        GCFlushXF(0x100a + ((i + 4) & 1), 0);
        GC_WORD(0x4b9 + i * 5) = 0; GC_BYTE(0x4b8 + i * 5) = 0;
    }
    for (u32 i = 0; i < 4; ++i) {
        GC_WORD(0x4c3 + i * 5) = 0xffffffff;
        GCFlushXF(0x100c + ((i + 4) & 1), 0xffffffff);
        GC_WORD(0x4c3 + i * 5) = 0xffffffff; GC_BYTE(0x4c2 + i * 5) = 0;
    }
    for (u32 i = 0; i < 16; ++i) {
        s32 coordinate = i < 8 ? i : 255;
        s32 texture = i < 8 ? i : 255;
        s32 channel = i < 8 ? 4 : 255;
        gsgfxState->stageOrders[i].coordinate = coordinate;
        gsgfxState->stageOrders[i].texture = texture;
        gsgfxState->stageOrders[i].channel = channel;
        if (i & 1) {
            gsgfxState->tevOrder[i >> 1].order.texture1 = texture & 7;
            gsgfxState->tevOrder[i >> 1].order.coordinate1 = coordinate & 7;
            gsgfxState->tevOrder[i >> 1].order.enabled1 = texture != 255 && !(texture & 0x100);
            gsgfxState->tevOrder[i >> 1].order.channel1 = i < 8 ? 0 : 7;
        } else {
            gsgfxState->tevOrder[i >> 1].order.texture0 = texture & 7;
            gsgfxState->tevOrder[i >> 1].order.coordinate0 = coordinate & 7;
            gsgfxState->tevOrder[i >> 1].order.enabled0 = texture != 255 && !(texture & 0x100);
            gsgfxState->tevOrder[i >> 1].order.channel0 = i < 8 ? 0 : 7;
        }
        gsgfxState->dirtyGroups[0] |= 1 << (i >> 1);
        if (coordinate != 255) gsgfxState->dirtyGroups[2] |= 1 << coordinate;
        gsgfxState->stageOrders[i].coordinate = coordinate;
        gsgfxState->stageOrders[i].texture = texture;
        gsgfxState->stageOrders[i].channel = channel;
    }
    GC_BYTE(0x58c) = 1; GC_BYTE(0x32) &= ~0x3c;
    gsgfxState->dirty |= 1; GC_BYTE(0x58c) = 1;
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->colorInputs[i].a = 15; gsgfxState->colorInputs[i].b = 10;
        gsgfxState->colorInputs[i].c = 8; gsgfxState->colorInputs[i].d = 15;
        GC_BYTE(0x226 + i * 4) |= 0xf0;
        GC_BYTE(0x226 + i * 4) = (GC_BYTE(0x226 + i * 4) & ~15) | 10;
        GC_BYTE(0x227 + i * 4) = (GC_BYTE(0x227 + i * 4) & ~0xf0) | 0x80;
        GC_BYTE(0x227 + i * 4) |= 15;
        gsgfxState->dirtyGroups[6] |= 1 << i;
        gsgfxState->colorInputs[i].a = 15; gsgfxState->colorInputs[i].b = 10;
        gsgfxState->colorInputs[i].c = 8; gsgfxState->colorInputs[i].d = 15;
        gsgfxState->alphaInputs[i].a = 7; gsgfxState->alphaInputs[i].b = 5;
        gsgfxState->alphaInputs[i].c = 4; gsgfxState->alphaInputs[i].d = 7;
        GC_BYTE(0x266 + i * 4) |= 0xe0;
        GC_BYTE(0x266 + i * 4) = (GC_BYTE(0x266 + i * 4) & ~0x1c) | 0x14;
        GC_HALF(0x266 + i * 4) = (GC_HALF(0x266 + i * 4) & ~0x380) | 0x200;
        GC_BYTE(0x267 + i * 4) |= 0x70;
        gsgfxState->dirtyGroups[7] |= 1 << i;
        gsgfxState->alphaInputs[i].a = 7; gsgfxState->alphaInputs[i].b = 5;
        gsgfxState->alphaInputs[i].c = 4; gsgfxState->alphaInputs[i].d = 7;
        gsgfxState->colorOperations[i].operation = 0; gsgfxState->colorOperations[i].bias = 0;
        gsgfxState->colorOperations[i].scale = 0; gsgfxState->colorOperations[i].clamp = 1;
        gsgfxState->colorOperations[i].output = 0;
        GC_BYTE(0x225 + i * 4) &= ~3; GC_BYTE(0x225 + i * 4) &= ~4;
        GC_BYTE(0x225 + i * 4) |= 8; GC_BYTE(0x225 + i * 4) &= ~0x30;
        GC_BYTE(0x225 + i * 4) &= ~0xc0;
        gsgfxState->dirtyGroups[6] |= 1 << i;
        gsgfxState->colorOperations[i].operation = 0; gsgfxState->colorOperations[i].bias = 0;
        gsgfxState->colorOperations[i].scale = 0; gsgfxState->colorOperations[i].clamp = 1;
        gsgfxState->colorOperations[i].output = 0;
        gsgfxState->alphaOperations[i].operation = 0; gsgfxState->alphaOperations[i].bias = 0;
        gsgfxState->alphaOperations[i].scale = 0; gsgfxState->alphaOperations[i].clamp = 1;
        gsgfxState->alphaOperations[i].output = 0;
        GC_BYTE(0x265 + i * 4) &= ~3; GC_BYTE(0x265 + i * 4) &= ~4;
        GC_BYTE(0x265 + i * 4) |= 8; GC_BYTE(0x265 + i * 4) &= ~0x30;
        GC_BYTE(0x265 + i * 4) &= ~0xc0;
        gsgfxState->dirtyGroups[7] |= 1 << i;
        gsgfxState->alphaOperations[i].operation = 0; gsgfxState->alphaOperations[i].bias = 0;
        gsgfxState->alphaOperations[i].scale = 0; gsgfxState->alphaOperations[i].clamp = 1;
        gsgfxState->alphaOperations[i].output = 0;
    }
    for (u32 i = 0; i < 4; ++i) {
        GC_WORD(0xa11 + i * 5) = 0;
        gsgfxState->tevConstantColorA[i].value &= ~0x7ff;
        gsgfxState->tevConstantColorA[i].value &= ~0x7ff000;
        gsgfxState->tevConstantColorB[i].value &= ~0x7ff;
        gsgfxState->tevConstantColorB[i].value &= ~0x7ff000;
        gsgfxState->dirtyGroups[9] |= 1 << i;
        GC_WORD(0xa11 + i * 5) = 0; GC_BYTE(0xa10 + i * 5) = 0;
    }
    for (u32 i = 0; i < 16; ++i) {
        GC_WORD(0xa24 + i * 4) = 12;
        if (i & 1) gsgfxState->tevConstantSelect[i >> 1].value = (gsgfxState->tevConstantSelect[i >> 1].value & ~0x7c000) | 0x30000;
        else GC_HALF(0x206 + (i >> 1) * 4) = (GC_HALF(0x206 + (i >> 1) * 4) & ~0x1f0) | 0xc0;
        gsgfxState->dirtyGroups[5] |= 1 << (i >> 1);
        GC_WORD(0xa24 + i * 4) = 12;
        GC_WORD(0xa64 + i * 4) = 28;
        if (i & 1) GC_BYTE(0x205 + (i >> 1) * 4) = (GC_BYTE(0x205 + (i >> 1) * 4) & ~0xf8) | 0xe0;
        else GC_BYTE(0x206 + (i >> 1) * 4) = (GC_BYTE(0x206 + (i >> 1) * 4) & ~0x3e) | 0x38;
        gsgfxState->dirtyGroups[5] |= 1 << (i >> 1);
        GC_WORD(0xa64 + i * 4) = 28;
        gsgfxState->stageSwaps[i].raster = 0; gsgfxState->stageSwaps[i].texture = 0;
        GC_BYTE(0x267 + i * 4) &= ~3; GC_BYTE(0x267 + i * 4) &= ~12;
        gsgfxState->dirtyGroups[7] |= 1 << i;
        gsgfxState->stageSwaps[i].raster = 0; gsgfxState->stageSwaps[i].texture = 0;
    }
    for (u32 i = 0; i < 4; ++i) {
        GC_WORD(0xb24 + i * 16) = 0; GC_WORD(0xb28 + i * 16) = 1;
        GC_WORD(0xb2c + i * 16) = 2; GC_WORD(0xb30 + i * 16) = 3;
        gsgfxState->tevConstantSelect[i * 2].swap.selector0 = 0;
        gsgfxState->tevConstantSelect[i * 2].swap.selector1 = 1;
        gsgfxState->tevConstantSelect[i * 2 + 1].swap.selector0 = 2;
        gsgfxState->tevConstantSelect[i * 2 + 1].swap.selector1 = 3;
        gsgfxState->dirtyGroups[5] |= 1 << (i * 2);
        gsgfxState->dirtyGroups[5] |= 1 << (i * 2 + 1);
        GC_WORD(0xb24 + i * 16) = 0; GC_WORD(0xb28 + i * 16) = 1;
        GC_WORD(0xb2c + i * 16) = 2; GC_WORD(0xb30 + i * 16) = 3;
    }
    for (u32 i = 0; i < 16; ++i) {
        gsgfxState->indirectMode[i] = 1;
        gsgfxState->tevIndirect[i].indirect.stage = 0;
        gsgfxState->tevIndirect[i].indirect.format = 0;
        gsgfxState->tevIndirect[i].indirect.bias = 0;
        gsgfxState->tevIndirect[i].indirect.alpha = 0;
        gsgfxState->tevIndirect[i].indirect.matrix = 0;
        gsgfxState->tevIndirect[i].indirect.wrapS = 0;
        gsgfxState->tevIndirect[i].indirect.wrapT = 0;
        gsgfxState->tevIndirect[i].indirect.originalLod = 0;
        gsgfxState->tevIndirect[i].indirect.addPrevious = 0;
        gsgfxState->dirtyGroups[10] |= 1 << i;
        gsgfxState->indirectMode[i] = 2; gsgfxState->indirectMode[i] = 1;
    }
    GC_BYTE(0x58d) = 0; GC_BYTE(0x31) &= ~7;
    gsgfxState->dirty |= 1; GC_BYTE(0x58d) = 0;
    for (u32 i = 0; i < 4; ++i) {
        gsgfxState->indirectOrders[i].coordinate = i; gsgfxState->indirectOrders[i].texture = i;
        switch (i) {
        case 0: gsgfxState->indirectReference.indirectOrder.texture0 = i; gsgfxState->indirectReference.indirectOrder.coordinate0 = i; break;
        case 1: gsgfxState->indirectReference.indirectOrder.texture1 = i; gsgfxState->indirectReference.indirectOrder.coordinate1 = i; break;
        case 2: gsgfxState->indirectReference.indirectOrder.texture2 = i; gsgfxState->indirectReference.indirectOrder.coordinate2 = i; break;
        case 3: gsgfxState->indirectReference.indirectOrder.texture3 = i; gsgfxState->indirectReference.indirectOrder.coordinate3 = i; break;
        }
        gsgfxState->dirty |= 0x2000; gsgfxState->dirtyGroups[2] |= 1 << i;
        gsgfxState->indirectOrders[i].coordinate = i; gsgfxState->indirectOrders[i].texture = i;
        GC_WORD(0xb94 + i * 8) = 0; GC_WORD(0xb98 + i * 8) = 0;
        if (i & 1) {
            GC_BYTE(0x7e + (i >> 1) * 4) &= ~15;
            GC_BYTE(0x7e + (i >> 1) * 4) &= ~0xf0;
        } else {
            GC_BYTE(0x7f + (i >> 1) * 4) &= ~15;
            GC_BYTE(0x7e + (i >> 1) * 4) &= ~0xf0;
        }
        gsgfxState->dirtyGroups[1] |= 1 << (i >> 1);
        GC_WORD(0xb94 + i * 8) = 0; GC_WORD(0xb98 + i * 8) = 0;
    }
    GC_WORD(0xbb4) = 0;
    GC_WORD(0xbb8) = 4;
    GC_WORD(0xbbc) = 5;
    GC_WORD(0xbc0) = 0;
    GC_BYTE(0x3b) = (u8) (GC_BYTE(0x3b) & ~1);
    GC_BYTE(0x3b) = (u8) (GC_BYTE(0x3b) & ~2);
    GC_BYTE(0x3a) = (u8) ((GC_BYTE(0x3a) & ~7) | 4);
    GC_BYTE(0x3b) = (u8) ((GC_BYTE(0x3b) & ~0xE0) | 0xA0);
    GC_BYTE(0x3a) = (u8) (GC_BYTE(0x3a) & ~8);
    GC_BYTE(0x3a) = (u8) (GC_BYTE(0x3a) & ~0x10);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 4);
    GC_WORD(0xbb4) = 0;
    GC_WORD(0xbb8) = 4;
    GC_WORD(0xbbc) = 5;
    GC_WORD(0xbc0) = 0;
    GC_BYTE(0xbc4) = 1;
    GC_BYTE(0x3b) = (u8) (GC_BYTE(0x3b) | 8);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 4);
    GC_BYTE(0xbc4) = 1;
    GC_BYTE(0xbc5) = 1;
    GC_BYTE(0x3b) = (u8) (GC_BYTE(0x3b) | 0x10);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 4);
    GC_BYTE(0xbc5) = 1;
    GC_BYTE(0xbe4) = 1;
    GC_WORD(0xbe8) = 3;
    GC_BYTE(0xbec) = 1;
    GC_BYTE(0x37) = (u8) (GC_BYTE(0x37) | 1);
    GC_BYTE(0x37) = (u8) ((GC_BYTE(0x37) & ~0xE) | 6);
    GC_BYTE(0x37) = (u8) (GC_BYTE(0x37) | 0x10);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 2);
    GC_BYTE(0xbe4) = 1;
    GC_WORD(0xbe8) = 3;
    GC_BYTE(0xbec) = 1;
    GC_BYTE(0xbf0) = 1;
    GC_BYTE(0x43) = (u8) (GC_BYTE(0x43) | 0x40);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 0x10);
    GC_BYTE(0xbf0) = 1;
    GC_BYTE(0xbf1) = 1;
    GC_BYTE(0x3b) = (u8) (GC_BYTE(0x3b) | 4);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 4);
    GC_BYTE(0xbf1) = 1;
    GC_BYTE(0xbf2) = 0;
    GC_BYTE(0xbf3) = 0;
    GC_BYTE(0x3e) = (u8) (GC_BYTE(0x3e) & ~1);
    GC_BYTE(0x3f) = 0;
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 8);
    GC_BYTE(0xbf2) = 0;
    GC_BYTE(0xbf3) = 0;
    GC_WORD(0xbc8) = 7;
    GC_BYTE(0xbd4) = 0;
    GC_WORD(0xbcc) = 0;
    GC_WORD(0xbd0) = 7;
    GC_BYTE(0xbd5) = 0;
    GC_BYTE(0x1fb) = 0;
    GC_BYTE(0x1fa) = 0;
    GC_BYTE(0x1f9) = (u8) (GC_BYTE(0x1f9) | 7);
    GC_BYTE(0x1f9) = (u8) (GC_BYTE(0x1f9) | 0x38);
    GC_BYTE(0x1f9) = (u8) (GC_BYTE(0x1f9) & ~0xC0);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 0x100);
    GC_WORD(0xbc8) = 7;
    GC_BYTE(0xbd4) = 0;
    GC_WORD(0xbcc) = 0;
    GC_WORD(0xbd0) = 7;
    GC_BYTE(0xbd5) = 0;
    GC_WORD(0xbd8) = 0;
    GC_WORD(0xbdc) = 0x11;
    GC_WORD(0xbe0) = 0;
    GC_WORD(0x1fc) = (s32) (GC_WORD(0x1fc) & ~0xFFFFFF);
    GC_BYTE(0x203) = (u8) (GC_BYTE(0x203) & ~3);
    GC_BYTE(0x203) = (u8) (GC_BYTE(0x203) & ~0xC);
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 0x200);
    GC_WORD(0xbd8) = 0;
    GC_WORD(0xbdc) = 0x11;
    GC_WORD(0xbe0) = 0;
    GC_WORD(0xbf4) = 0;
    GC_FLOAT(0xbf8) = 0.0f;
    GC_FLOAT(0xbfc) = 1000.0f;
    GC_FLOAT(0xc00) = 0.0f;
    GC_FLOAT(0xc04) = 1000.0f;
    GC_WORD(0xc09) = 0;
    GSgfx_GCWriteFog(0, 0.0f, 1000.0f, 0.0f, 1000.0f);
    GC_BYTE(0x2f5) = 0;
    GC_BYTE(0x2f6) = 0;
    GC_BYTE(0x2f7) = 0;
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 0x20000);
    GC_WORD(0xc09) = 0;
    GC_BYTE(0xc08) = 0;
    GC_HALF(0xc0e) = 0;
    GC_BYTE(0xc0d) = 0;
    GC_BYTE(0x2fa) = (u8) (GC_BYTE(0x2fa) & ~4);
    GC_HALF(0x2fa) = (GC_HALF(0x2fa) & ~0x3ff) | 0x156;
    GC_WORD(0x0) = (s32) (GC_WORD(0x0) | 0x40000);
    GC_BYTE(0xc0d) = 0;
    GC_HALF(0xc0e) = 0;
    GSgfx_GCFlushState();
}

}
