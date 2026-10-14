#include <game/pxdvs/GSAPI/GSgfxM/gamecube_private.hpp>
#include <libc/string.h>

extern "C" {

extern GCGraphicsState *gsgfxState;
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
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r10;
    s32 temp_r10_2;
    s32 temp_r10_3;
    s32 temp_r10_4;
    s32 temp_r10_5;
    s32 temp_r10_6;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r11_4;
    s32 temp_r11_5;
    s32 temp_r11_6;
    s32 temp_r12;
    s32 temp_r12_2;
    s32 temp_r12_3;
    s32 temp_r12_4;
    s32 temp_r12_5;
    s32 temp_r12_6;
    s32 temp_r14;
    s32 temp_r14_2;
    s32 temp_r14_3;
    s32 temp_r14_4;
    s32 temp_r14_5;
    s32 temp_r15;
    s32 temp_r15_2;
    s32 temp_r15_3;
    s32 temp_r15_4;
    s32 temp_r15_5;
    s32 temp_r15_6;
    s32 temp_r16;
    s32 temp_r16_2;
    s32 temp_r16_3;
    s32 temp_r16_4;
    s32 temp_r16_5;
    s32 temp_r17;
    s32 temp_r17_2;
    s32 temp_r17_3;
    s32 temp_r17_4;
    s32 temp_r17_5;
    s32 temp_r18;
    s32 temp_r18_2;
    s32 temp_r18_3;
    s32 temp_r18_4;
    s32 temp_r18_5;
    s32 temp_r19;
    s32 temp_r19_2;
    s32 temp_r19_3;
    s32 temp_r19_4;
    s32 temp_r19_5;
    s32 temp_r20;
    s32 temp_r20_2;
    s32 temp_r20_3;
    s32 temp_r20_4;
    s32 temp_r20_5;
    s32 temp_r21;
    s32 temp_r21_2;
    s32 temp_r21_3;
    s32 temp_r21_4;
    s32 temp_r21_5;
    s32 temp_r22;
    s32 temp_r22_2;
    s32 temp_r22_3;
    s32 temp_r23;
    s32 temp_r23_2;
    s32 temp_r23_3;
    s32 temp_r24;
    s32 temp_r24_2;
    s32 temp_r24_3;
    s32 temp_r25;
    s32 temp_r25_2;
    s32 temp_r26;
    s32 temp_r26_2;
    s32 temp_r27;
    s32 temp_r27_2;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    s32 temp_r6_6;
    s32 temp_r7;
    s32 temp_r7_2;
    s32 temp_r7_3;
    s32 temp_r7_4;
    s32 temp_r7_5;
    s32 temp_r7_6;
    s32 temp_r8;
    s32 temp_r8_2;
    s32 temp_r8_3;
    s32 temp_r8_4;
    s32 temp_r8_5;
    s32 temp_r8_6;
    s32 temp_r9;
    s32 temp_r9_2;
    s32 temp_r9_3;
    s32 temp_r9_4;
    s32 temp_r9_5;
    s32 temp_r9_6;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_ctr_6;
    s32 var_r16;
    s32 var_r29;
    s32 var_r3;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;

    GC_WORD(0x358) = 0xFEFEFEFE;
    GC_WORD(0x35C) = 0xFEFEFEFE;
    GC_WORD(0x360) = 0xFEFEFEFE;
    GC_BYTE(0x364) = 0xFE;
    GC_WORD(0x368) = 0xFEFEFEFE;
    GC_WORD(0x36C) = 0xFEFEFEFE;
    GC_WORD(0x370) = 0xFEFEFEFE;
    GC_WORD(0x374) = 0xFEFEFEFE;
    GC_BYTE(0x378) = 0xFE;
    GC_WORD(0x37C) = 0xFEFEFEFE;
    GC_WORD(0x380) = 0xFEFEFEFE;
    GC_WORD(0x384) = 0xFEFEFEFE;
    GC_WORD(0x388) = 0xFEFEFEFE;
    GC_BYTE(0x38C) = 0xFE;
    GC_WORD(0x390) = 0xFEFEFEFE;
    GC_WORD(0x394) = 0xFEFEFEFE;
    GC_WORD(0x398) = 0xFEFEFEFE;
    GC_WORD(0x39C) = 0xFEFEFEFE;
    GC_BYTE(0x3A0) = 0xFE;
    GC_WORD(0x3A4) = 0xFEFEFEFE;
    GC_WORD(0x3A8) = 0xFEFEFEFE;
    GC_WORD(0x3AC) = 0xFEFEFEFE;
    GC_WORD(0x3B0) = 0xFEFEFEFE;
    GC_BYTE(0x3B4) = 0xFE;
    GC_WORD(0x3B8) = 0xFEFEFEFE;
    GC_WORD(0x3BC) = 0xFEFEFEFE;
    GC_WORD(0x3C0) = 0xFEFEFEFE;
    var_r4 = 0;
    GC_WORD(0x3C4) = 0xFEFEFEFE;
    GC_BYTE(0x3C8) = 0xFE;
    GC_WORD(0x3CC) = 0xFEFEFEFE;
    GC_WORD(0x3D0) = 0xFEFEFEFE;
    GC_WORD(0x3D4) = 0xFEFEFEFE;
    GC_WORD(0x3D8) = 0xFEFEFEFE;
    GC_BYTE(0x3DC) = 0xFE;
    GC_WORD(0x3E0) = 0xFEFEFEFE;
    GC_WORD(0x3E4) = 0xFEFEFEFE;
    GC_WORD(0x3E8) = 0xFEFEFEFE;
    GC_WORD(0x3EC) = 0xFEFEFEFE;
    GC_BYTE(0x3F0) = 0xFE;
    GC_WORD(0x3F4) = 0xFEFEFEFE;
    GC_BYTE(0x3F8) = 0xFE;
    GC_BYTE(0x3FC) = 0;
    GC_WORD(0x400) = 0xFEFEFEFE;
    GC_BYTE(0x404) = 0;
    GC_WORD(0x408) = 0xFEFEFEFE;
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
    GC_WORD(0x41C) = 0xFEFEFEFE;
    GC_BYTE(0x438) = 0xFE;
    GC_WORD(0x43C) = 0xFEFEFEFE;
    GC_WORD(0x440) = 0xFEFEFEFE;
    GC_HALF(0x444) = 0xFEFE;
    GC_HALF(0x446) = 0xFEFE;
    GC_HALF(0x448) = 0xFEFE;
    GC_HALF(0x44A) = 0xFEFE;
    GC_WORD(0x44C) = 0xFEFEFEFE;
    GC_WORD(0x450) = 0xFEFEFEFE;
    GC_FLOAT(0xC24) = -1.0f;
    GC_FLOAT(0xC28) = -1.0f;
    GC_FLOAT(0xC2C) = -1.0f;
    GC_FLOAT(0xC30) = -1.0f;
    GC_FLOAT(0xC34) = 0.0f;
    GC_FLOAT(0xC38) = 1.0f;
    GC_WORD(0xC3C) = 0xFEFEFEFE;
    GC_BYTE(0x454) = 0xFE;
    GC_BYTE(0x458) = 0xFE;
    GC_WORD(0x45C) = 0xFEFEFEFE;
    GC_WORD(0x460) = 0xFEFEFEFE;
    GC_WORD(0x464) = 0xFEFEFEFE;
    GC_WORD(0x468) = 0xFEFEFEFE;
    GC_WORD(0x46C) = 0xFEFEFEFE;
    GC_BYTE(0x470) = 0xFE;
    GC_WORD(0x474) = 0xFEFEFEFE;
    GC_WORD(0x478) = 0xFEFEFEFE;
    GC_WORD(0x47C) = 0xFEFEFEFE;
    GC_WORD(0x480) = 0xFEFEFEFE;
    GC_WORD(0x484) = 0xFEFEFEFE;
    GC_BYTE(0x488) = 0xFE;
    GC_WORD(0x48C) = 0xFEFEFEFE;
    GC_WORD(0x490) = 0xFEFEFEFE;
    GC_WORD(0x494) = 0xFEFEFEFE;
    GC_WORD(0x498) = 0xFEFEFEFE;
    GC_WORD(0x49C) = 0xFEFEFEFE;
    GC_BYTE(0x4A0) = 0xFE;
    GC_WORD(0x4A4) = 0xFEFEFEFE;
    GC_WORD(0x4A8) = 0xFEFEFEFE;
    GC_WORD(0x4AC) = 0xFEFEFEFE;
    GC_WORD(0x4B0) = 0xFEFEFEFE;
    GC_WORD(0x4B4) = 0xFEFEFEFE;
    GC_BYTE(0x4B8) = 1;
    GC_BYTE(0x4C2) = 1;
    GC_BYTE(0x4BD) = 1;
    GC_BYTE(0x4C7) = 1;
    var_ctr = 2;
    do {
        GC_WORD((var_r4 + 0x4CC)) = 0xFEFEFEFE;
        temp_r24 = var_r4 + 0x4DC;
        temp_r23 = var_r4 + 0x4E0;
        temp_r22 = var_r4 + 0x4E4;
        temp_r21 = var_r4 + 0x4E8;
        temp_r20 = var_r4 + 0x4EC;
        GC_WORD((var_r4 + 0x4D0)) = 0xFEFEFEFE;
        temp_r19 = var_r4 + 0x4F0;
        temp_r18 = var_r4 + 0x4F4;
        temp_r17 = var_r4 + 0x4F8;
        temp_r16 = var_r4 + 0x4FC;
        temp_r15 = var_r4 + 0x500;
        temp_r14 = var_r4 + 0x504;
        GC_WORD((var_r4 + 0x4D4)) = 0xFEFEFEFE;
        temp_r12 = var_r4 + 0x508;
        temp_r11 = var_r4 + 0x50C;
        temp_r10 = var_r4 + 0x510;
        temp_r9 = var_r4 + 0x514;
        temp_r8 = var_r4 + 0x518;
        temp_r7 = var_r4 + 0x51C;
        GC_WORD((var_r4 + 0x4D8)) = 0xFEFEFEFE;
        temp_r6 = var_r4 + 0x520;
        temp_r5 = var_r4 + 0x524;
        temp_r0 = var_r4 + 0x528;
        var_r4 += 0x60;
        GC_WORD(temp_r24) = 0xFEFEFEFE;
        GC_WORD(temp_r23) = 0xFEFEFEFE;
        GC_WORD(temp_r22) = 0xFEFEFEFE;
        GC_WORD(temp_r21) = 0xFEFEFEFE;
        GC_WORD(temp_r20) = 0xFEFEFEFE;
        GC_WORD(temp_r19) = 0xFEFEFEFE;
        GC_WORD(temp_r18) = 0xFEFEFEFE;
        GC_WORD(temp_r17) = 0xFEFEFEFE;
        GC_WORD(temp_r16) = 0xFEFEFEFE;
        GC_WORD(temp_r15) = 0xFEFEFEFE;
        GC_WORD(temp_r14) = 0xFEFEFEFE;
        GC_WORD(temp_r12) = 0xFEFEFEFE;
        GC_WORD(temp_r11) = 0xFEFEFEFE;
        GC_WORD(temp_r10) = 0xFEFEFEFE;
        GC_WORD(temp_r9) = 0xFEFEFEFE;
        GC_WORD(temp_r8) = 0xFEFEFEFE;
        GC_WORD(temp_r7) = 0xFEFEFEFE;
        GC_WORD(temp_r6) = 0xFEFEFEFE;
        GC_WORD(temp_r5) = 0xFEFEFEFE;
        GC_WORD(temp_r0) = 0xFEFEFEFE;
        var_ctr -= 1;
    } while (var_ctr != 0);
    GC_BYTE(0x58C) = 0xFE;
    var_r16 = 0;
    GC_BYTE(0x58D) = 0xFE;
    var_ctr_2 = 2;
    do {
        GC_WORD((var_r16 + 0x590)) = 0xFEFEFEFE;
        temp_r18_2 = var_r16 + 0x5A4;
        sp10 = var_r16 + 0x608;
        temp_r15_2 = var_r16 + 0x60C;
        temp_r19_2 = var_r16 + 0x5A8;
        temp_r20_2 = var_r16 + 0x5AC;
        GC_WORD((var_r16 + 0x594)) = 0xFEFEFEFE;
        temp_r21_2 = var_r16 + 0x5B0;
        temp_r22_2 = var_r16 + 0x5B4;
        temp_r23_2 = var_r16 + 0x5B8;
        temp_r24_2 = var_r16 + 0x5BC;
        temp_r25 = var_r16 + 0x5C0;
        temp_r26 = var_r16 + 0x5C4;
        GC_WORD((var_r16 + 0x598)) = 0xFEFEFEFE;
        temp_r27 = var_r16 + 0x5C8;
        temp_r28 = var_r16 + 0x5CC;
        temp_r29 = var_r16 + 0x5D0;
        temp_r30 = var_r16 + 0x5D4;
        temp_r31 = var_r16 + 0x5D8;
        temp_r12_2 = var_r16 + 0x5DC;
        GC_WORD((var_r16 + 0x59C)) = 0xFEFEFEFE;
        temp_r11_2 = var_r16 + 0x5E0;
        temp_r10_2 = var_r16 + 0x5E4;
        temp_r9_2 = var_r16 + 0x5E8;
        temp_r8_2 = var_r16 + 0x5EC;
        temp_r7_2 = var_r16 + 0x5F0;
        temp_r6_2 = var_r16 + 0x5F4;
        GC_WORD((var_r16 + 0x5A0)) = 0xFEFEFEFE;
        temp_r5_2 = var_r16 + 0x5F8;
        temp_r4 = var_r16 + 0x5FC;
        temp_r3 = var_r16 + 0x600;
        temp_r0_2 = var_r16 + 0x604;
        sp8 = temp_r15_2;
        var_r16 += 0x80;
        GC_WORD(temp_r18_2) = 0xFEFEFEFE;
        GC_WORD(temp_r19_2) = 0xFEFEFEFE;
        GC_WORD(temp_r20_2) = 0xFEFEFEFE;
        GC_WORD(temp_r21_2) = 0xFEFEFEFE;
        GC_WORD(temp_r22_2) = 0xFEFEFEFE;
        GC_WORD(temp_r23_2) = 0xFEFEFEFE;
        GC_WORD(temp_r24_2) = 0xFEFEFEFE;
        GC_WORD(temp_r25) = 0xFEFEFEFE;
        GC_WORD(temp_r26) = 0xFEFEFEFE;
        GC_WORD(temp_r27) = 0xFEFEFEFE;
        GC_WORD(temp_r28) = 0xFEFEFEFE;
        GC_WORD(temp_r29) = 0xFEFEFEFE;
        GC_WORD(temp_r30) = 0xFEFEFEFE;
        GC_WORD(temp_r31) = 0xFEFEFEFE;
        GC_WORD(temp_r12_2) = 0xFEFEFEFE;
        GC_WORD(temp_r11_2) = 0xFEFEFEFE;
        GC_WORD(temp_r10_2) = 0xFEFEFEFE;
        GC_WORD(temp_r9_2) = 0xFEFEFEFE;
        GC_WORD(temp_r8_2) = 0xFEFEFEFE;
        GC_WORD(temp_r7_2) = 0xFEFEFEFE;
        GC_WORD(temp_r6_2) = 0xFEFEFEFE;
        GC_WORD(temp_r5_2) = 0xFEFEFEFE;
        GC_WORD(temp_r4) = 0xFEFEFEFE;
        GC_WORD(temp_r3) = 0xFEFEFEFE;
        GC_WORD(temp_r0_2) = 0xFEFEFEFE;
        GC_WORD(sp10) = 0xFEFEFEFE;
        GC_WORD(temp_r15_2) = 0xFEFEFEFE;
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    var_r29 = 0;
    var_ctr_3 = 2;
    do {
        GC_WORD((var_r29 + 0x690)) = 0xFEFEFEFE;
        temp_r27_2 = var_r29 + 0x6A4;
        sp14 = var_r29 + 0x708;
        temp_r30_2 = var_r29 + 0x70C;
        temp_r26_2 = var_r29 + 0x6A8;
        temp_r25_2 = var_r29 + 0x6AC;
        GC_WORD((var_r29 + 0x694)) = 0xFEFEFEFE;
        temp_r24_3 = var_r29 + 0x6B0;
        temp_r23_3 = var_r29 + 0x6B4;
        temp_r22_3 = var_r29 + 0x6B8;
        temp_r21_3 = var_r29 + 0x6BC;
        temp_r20_3 = var_r29 + 0x6C0;
        temp_r19_3 = var_r29 + 0x6C4;
        GC_WORD((var_r29 + 0x698)) = 0xFEFEFEFE;
        temp_r18_3 = var_r29 + 0x6C8;
        temp_r17_2 = var_r29 + 0x6CC;
        temp_r16_2 = var_r29 + 0x6D0;
        temp_r15_3 = var_r29 + 0x6D4;
        temp_r14_2 = var_r29 + 0x6D8;
        temp_r12_3 = var_r29 + 0x6DC;
        GC_WORD((var_r29 + 0x69C)) = 0xFEFEFEFE;
        temp_r11_3 = var_r29 + 0x6E0;
        temp_r10_3 = var_r29 + 0x6E4;
        temp_r9_3 = var_r29 + 0x6E8;
        temp_r8_3 = var_r29 + 0x6EC;
        temp_r7_3 = var_r29 + 0x6F0;
        temp_r6_3 = var_r29 + 0x6F4;
        GC_WORD((var_r29 + 0x6A0)) = 0xFEFEFEFE;
        temp_r5_3 = var_r29 + 0x6F8;
        temp_r4_2 = var_r29 + 0x6FC;
        temp_r3_2 = var_r29 + 0x700;
        temp_r0_3 = var_r29 + 0x704;
        spC = temp_r30_2;
        var_r29 += 0x80;
        GC_WORD(temp_r27_2) = 0xFEFEFEFE;
        GC_WORD(temp_r26_2) = 0xFEFEFEFE;
        GC_WORD(temp_r25_2) = 0xFEFEFEFE;
        GC_WORD(temp_r24_3) = 0xFEFEFEFE;
        GC_WORD(temp_r23_3) = 0xFEFEFEFE;
        GC_WORD(temp_r22_3) = 0xFEFEFEFE;
        GC_WORD(temp_r21_3) = 0xFEFEFEFE;
        GC_WORD(temp_r20_3) = 0xFEFEFEFE;
        GC_WORD(temp_r19_3) = 0xFEFEFEFE;
        GC_WORD(temp_r18_3) = 0xFEFEFEFE;
        GC_WORD(temp_r17_2) = 0xFEFEFEFE;
        GC_WORD(temp_r16_2) = 0xFEFEFEFE;
        GC_WORD(temp_r15_3) = 0xFEFEFEFE;
        GC_WORD(temp_r14_2) = 0xFEFEFEFE;
        GC_WORD(temp_r12_3) = 0xFEFEFEFE;
        GC_WORD(temp_r11_3) = 0xFEFEFEFE;
        GC_WORD(temp_r10_3) = 0xFEFEFEFE;
        GC_WORD(temp_r9_3) = 0xFEFEFEFE;
        GC_WORD(temp_r8_3) = 0xFEFEFEFE;
        GC_WORD(temp_r7_3) = 0xFEFEFEFE;
        GC_WORD(temp_r6_3) = 0xFEFEFEFE;
        GC_WORD(temp_r5_3) = 0xFEFEFEFE;
        GC_WORD(temp_r4_2) = 0xFEFEFEFE;
        GC_WORD(temp_r3_2) = 0xFEFEFEFE;
        GC_WORD(temp_r0_3) = 0xFEFEFEFE;
        GC_WORD(sp14) = 0xFEFEFEFE;
        GC_WORD(temp_r30_2) = 0xFEFEFEFE;
        var_ctr_3 -= 1;
    } while (var_ctr_3 != 0);
    var_r4_2 = 0;
    var_ctr_4 = 2;
    do {
        GC_WORD((var_r4_2 + 0x790)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x794)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x798)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_2 + 0x79C)) = 0xFE;
        GC_WORD((var_r4_2 + 0x7A0)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7A4)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7A8)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7AC)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_2 + 0x7B0)) = 0xFE;
        GC_WORD((var_r4_2 + 0x7B4)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7B8)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7BC)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7C0)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_2 + 0x7C4)) = 0xFE;
        GC_WORD((var_r4_2 + 0x7C8)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7CC)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7D0)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7D4)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_2 + 0x7D8)) = 0xFE;
        GC_WORD((var_r4_2 + 0x7DC)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7E0)) = 0xFEFEFEFE;
        GC_WORD((var_r4_2 + 0x7E4)) = 0xFEFEFEFE;
        temp_r21_4 = var_r4_2 + 0x7F0;
        temp_r20_4 = var_r4_2 + 0x7F4;
        temp_r19_4 = var_r4_2 + 0x7F8;
        temp_r18_4 = var_r4_2 + 0x7FC;
        temp_r17_3 = var_r4_2 + 0x800;
        temp_r16_3 = var_r4_2 + 0x804;
        GC_WORD((var_r4_2 + 0x7E8)) = 0xFEFEFEFE;
        temp_r15_4 = var_r4_2 + 0x808;
        temp_r14_3 = var_r4_2 + 0x80C;
        temp_r12_4 = var_r4_2 + 0x810;
        temp_r11_4 = var_r4_2 + 0x814;
        temp_r10_4 = var_r4_2 + 0x818;
        temp_r9_4 = var_r4_2 + 0x81C;
        GC_BYTE((var_r4_2 + 0x7EC)) = 0xFE;
        temp_r8_4 = var_r4_2 + 0x820;
        temp_r7_4 = var_r4_2 + 0x824;
        temp_r6_4 = var_r4_2 + 0x828;
        temp_r5_4 = var_r4_2 + 0x82C;
        var_r4_2 += 0xA0;
        GC_WORD(temp_r21_4) = 0xFEFEFEFE;
        GC_WORD(temp_r20_4) = 0xFEFEFEFE;
        GC_WORD(temp_r19_4) = 0xFEFEFEFE;
        GC_WORD(temp_r18_4) = 0xFEFEFEFE;
        GC_BYTE(temp_r17_3) = 0xFE;
        GC_WORD(temp_r16_3) = 0xFEFEFEFE;
        GC_WORD(temp_r15_4) = 0xFEFEFEFE;
        GC_WORD(temp_r14_3) = 0xFEFEFEFE;
        GC_WORD(temp_r12_4) = 0xFEFEFEFE;
        GC_BYTE(temp_r11_4) = 0xFE;
        GC_WORD(temp_r10_4) = 0xFEFEFEFE;
        GC_WORD(temp_r9_4) = 0xFEFEFEFE;
        GC_WORD(temp_r8_4) = 0xFEFEFEFE;
        GC_WORD(temp_r7_4) = 0xFEFEFEFE;
        GC_BYTE(temp_r6_4) = 0xFE;
        GC_WORD(temp_r5_4) = 0xFEFEFEFE;
        var_ctr_4 -= 1;
    } while (var_ctr_4 != 0);
    var_r4_3 = 0;
    var_ctr_5 = 2;
    do {
        GC_WORD((var_r4_3 + 0x8D0)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8D4)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8D8)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_3 + 0x8DC)) = 0xFE;
        GC_WORD((var_r4_3 + 0x8E0)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8E4)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8E8)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8EC)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_3 + 0x8F0)) = 0xFE;
        GC_WORD((var_r4_3 + 0x8F4)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8F8)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x8FC)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x900)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_3 + 0x904)) = 0xFE;
        GC_WORD((var_r4_3 + 0x908)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x90C)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x910)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x914)) = 0xFEFEFEFE;
        GC_BYTE((var_r4_3 + 0x918)) = 0xFE;
        GC_WORD((var_r4_3 + 0x91C)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x920)) = 0xFEFEFEFE;
        GC_WORD((var_r4_3 + 0x924)) = 0xFEFEFEFE;
        temp_r21_5 = var_r4_3 + 0x930;
        temp_r20_5 = var_r4_3 + 0x934;
        temp_r19_5 = var_r4_3 + 0x938;
        temp_r18_5 = var_r4_3 + 0x93C;
        temp_r17_4 = var_r4_3 + 0x940;
        temp_r16_4 = var_r4_3 + 0x944;
        GC_WORD((var_r4_3 + 0x928)) = 0xFEFEFEFE;
        temp_r15_5 = var_r4_3 + 0x948;
        temp_r14_4 = var_r4_3 + 0x94C;
        temp_r12_5 = var_r4_3 + 0x950;
        temp_r11_5 = var_r4_3 + 0x954;
        temp_r10_5 = var_r4_3 + 0x958;
        temp_r9_5 = var_r4_3 + 0x95C;
        GC_BYTE((var_r4_3 + 0x92C)) = 0xFE;
        temp_r8_5 = var_r4_3 + 0x960;
        temp_r7_5 = var_r4_3 + 0x964;
        temp_r6_5 = var_r4_3 + 0x968;
        temp_r5_5 = var_r4_3 + 0x96C;
        var_r4_3 += 0xA0;
        GC_WORD(temp_r21_5) = 0xFEFEFEFE;
        GC_WORD(temp_r20_5) = 0xFEFEFEFE;
        GC_WORD(temp_r19_5) = 0xFEFEFEFE;
        GC_WORD(temp_r18_5) = 0xFEFEFEFE;
        GC_BYTE(temp_r17_4) = 0xFE;
        GC_WORD(temp_r16_4) = 0xFEFEFEFE;
        GC_WORD(temp_r15_5) = 0xFEFEFEFE;
        GC_WORD(temp_r14_4) = 0xFEFEFEFE;
        GC_WORD(temp_r12_5) = 0xFEFEFEFE;
        GC_BYTE(temp_r11_5) = 0xFE;
        GC_WORD(temp_r10_5) = 0xFEFEFEFE;
        GC_WORD(temp_r9_5) = 0xFEFEFEFE;
        GC_WORD(temp_r8_5) = 0xFEFEFEFE;
        GC_WORD(temp_r7_5) = 0xFEFEFEFE;
        GC_BYTE(temp_r6_5) = 0xFE;
        GC_WORD(temp_r5_5) = 0xFEFEFEFE;
        var_ctr_5 -= 1;
    } while (var_ctr_5 != 0);
    GC_BYTE(0xA10) = 1;
    var_r3 = 0;
    GC_BYTE(0xA15) = 1;
    GC_BYTE(0xA1A) = 1;
    GC_BYTE(0xA1F) = 1;
    GC_WORD(0xA24) = 0xFEFEFEFE;
    GC_WORD(0xA28) = 0xFEFEFEFE;
    GC_WORD(0xA2C) = 0xFEFEFEFE;
    GC_WORD(0xA30) = 0xFEFEFEFE;
    GC_WORD(0xA34) = 0xFEFEFEFE;
    GC_WORD(0xA38) = 0xFEFEFEFE;
    GC_WORD(0xA3C) = 0xFEFEFEFE;
    GC_WORD(0xA40) = 0xFEFEFEFE;
    GC_WORD(0xA44) = 0xFEFEFEFE;
    GC_WORD(0xA48) = 0xFEFEFEFE;
    GC_WORD(0xA4C) = 0xFEFEFEFE;
    GC_WORD(0xA50) = 0xFEFEFEFE;
    GC_WORD(0xA54) = 0xFEFEFEFE;
    GC_WORD(0xA58) = 0xFEFEFEFE;
    GC_WORD(0xA5C) = 0xFEFEFEFE;
    GC_WORD(0xA60) = 0xFEFEFEFE;
    GC_WORD(0xA64) = 0xFEFEFEFE;
    GC_WORD(0xA68) = 0xFEFEFEFE;
    GC_WORD(0xA6C) = 0xFEFEFEFE;
    GC_WORD(0xA70) = 0xFEFEFEFE;
    GC_WORD(0xA74) = 0xFEFEFEFE;
    GC_WORD(0xA78) = 0xFEFEFEFE;
    GC_WORD(0xA7C) = 0xFEFEFEFE;
    GC_WORD(0xA80) = 0xFEFEFEFE;
    GC_WORD(0xA84) = 0xFEFEFEFE;
    GC_WORD(0xA88) = 0xFEFEFEFE;
    GC_WORD(0xA8C) = 0xFEFEFEFE;
    GC_WORD(0xA90) = 0xFEFEFEFE;
    GC_WORD(0xA94) = 0xFEFEFEFE;
    GC_WORD(0xA98) = 0xFEFEFEFE;
    GC_WORD(0xA9C) = 0xFEFEFEFE;
    GC_WORD(0xAA0) = 0xFEFEFEFE;
    var_ctr_6 = 2;
    do {
        GC_WORD((var_r3 + 0xAA4)) = 0xFEFEFEFE;
        temp_r17_5 = var_r3 + 0xAB0;
        temp_r16_5 = var_r3 + 0xAB4;
        temp_r15_6 = var_r3 + 0xAB8;
        temp_r14_5 = var_r3 + 0xABC;
        temp_r12_6 = var_r3 + 0xAC0;
        temp_r11_6 = var_r3 + 0xAC4;
        GC_WORD((var_r3 + 0xAA8)) = 0xFEFEFEFE;
        temp_r10_6 = var_r3 + 0xAC8;
        temp_r9_6 = var_r3 + 0xACC;
        temp_r8_6 = var_r3 + 0xAD0;
        temp_r7_6 = var_r3 + 0xAD4;
        temp_r6_6 = var_r3 + 0xAD8;
        temp_r5_6 = var_r3 + 0xADC;
        GC_WORD((var_r3 + 0xAAC)) = 0xFEFEFEFE;
        temp_r4_3 = var_r3 + 0xAE0;
        var_r3 += 0x40;
        GC_WORD(temp_r17_5) = 0xFEFEFEFE;
        GC_WORD(temp_r16_5) = 0xFEFEFEFE;
        GC_WORD(temp_r15_6) = 0xFEFEFEFE;
        GC_WORD(temp_r14_5) = 0xFEFEFEFE;
        GC_WORD(temp_r12_6) = 0xFEFEFEFE;
        GC_WORD(temp_r11_6) = 0xFEFEFEFE;
        GC_WORD(temp_r10_6) = 0xFEFEFEFE;
        GC_WORD(temp_r9_6) = 0xFEFEFEFE;
        GC_WORD(temp_r8_6) = 0xFEFEFEFE;
        GC_WORD(temp_r7_6) = 0xFEFEFEFE;
        GC_WORD(temp_r6_6) = 0xFEFEFEFE;
        GC_WORD(temp_r5_6) = 0xFEFEFEFE;
        GC_WORD(temp_r4_3) = 0xFEFEFEFE;
        var_ctr_6 -= 1;
    } while (var_ctr_6 != 0);
    GC_WORD(0xB24) = 0xFEFEFEFE;
    GC_WORD(0xB28) = 0xFEFEFEFE;
    GC_WORD(0xB2C) = 0xFEFEFEFE;
    GC_WORD(0xB30) = 0xFEFEFEFE;
    GC_WORD(0xB34) = 0xFEFEFEFE;
    GC_WORD(0xB38) = 0xFEFEFEFE;
    GC_WORD(0xB3C) = 0xFEFEFEFE;
    GC_WORD(0xB40) = 0xFEFEFEFE;
    GC_WORD(0xB44) = 0xFEFEFEFE;
    GC_WORD(0xB48) = 0xFEFEFEFE;
    GC_WORD(0xB4C) = 0xFEFEFEFE;
    GC_WORD(0xB50) = 0xFEFEFEFE;
    GC_WORD(0xB54) = 0xFEFEFEFE;
    GC_WORD(0xB58) = 0xFEFEFEFE;
    GC_WORD(0xB5C) = 0xFEFEFEFE;
    GC_WORD(0xB60) = 0xFEFEFEFE;
    GC_BYTE(0xB64) = 0xFE;
    GC_BYTE(0xB65) = 0xFE;
    GC_BYTE(0xB66) = 0xFE;
    GC_BYTE(0xB67) = 0xFE;
    GC_BYTE(0xB68) = 0xFE;
    GC_BYTE(0xB69) = 0xFE;
    GC_BYTE(0xB6A) = 0xFE;
    GC_BYTE(0xB6B) = 0xFE;
    GC_BYTE(0xB6C) = 0xFE;
    GC_BYTE(0xB6D) = 0xFE;
    GC_BYTE(0xB6E) = 0xFE;
    GC_BYTE(0xB6F) = 0xFE;
    GC_BYTE(0xB70) = 0xFE;
    GC_BYTE(0xB71) = 0xFE;
    GC_BYTE(0xB72) = 0xFE;
    GC_BYTE(0xB73) = 0xFE;
    GC_WORD(0xB74) = 0xFEFEFEFE;
    GC_WORD(0xB78) = 0xFEFEFEFE;
    GC_WORD(0xB7C) = 0xFEFEFEFE;
    GC_WORD(0xB80) = 0xFEFEFEFE;
    GC_WORD(0xB84) = 0xFEFEFEFE;
    GC_WORD(0xB88) = 0xFEFEFEFE;
    GC_WORD(0xB8C) = 0xFEFEFEFE;
    GC_WORD(0xB90) = 0xFEFEFEFE;
    GC_WORD(0xB94) = 0xFEFEFEFE;
    GC_WORD(0xB98) = 0xFEFEFEFE;
    GC_WORD(0xB9C) = 0xFEFEFEFE;
    GC_WORD(0xBA0) = 0xFEFEFEFE;
    GC_WORD(0xBA4) = 0xFEFEFEFE;
    GC_WORD(0xBA8) = 0xFEFEFEFE;
    GC_WORD(0xBAC) = 0xFEFEFEFE;
    GC_WORD(0xBB0) = 0xFEFEFEFE;
    GC_WORD(0xBB4) = 0xFEFEFEFE;
    GC_WORD(0xBB8) = 0xFEFEFEFE;
    GC_WORD(0xBBC) = 0xFEFEFEFE;
    GC_WORD(0xBC0) = 0xFEFEFEFE;
    GC_BYTE(0xBC4) = 0xFE;
    GC_BYTE(0xBC5) = 0xFE;
    GC_WORD(0xBC8) = 0xFEFEFEFE;
    GC_WORD(0xBCC) = 0xFEFEFEFE;
    GC_WORD(0xBD0) = 0xFEFEFEFE;
    GC_BYTE(0xBD4) = 0xFE;
    GC_BYTE(0xBD5) = 0xFE;
    GC_WORD(0xBD8) = 0xFEFEFEFE;
    GC_WORD(0xBDC) = 0xFEFEFEFE;
    GC_WORD(0xBE0) = 0xFEFEFEFE;
    GC_BYTE(0xBE4) = 0xFE;
    GC_WORD(0xBE8) = 0xFEFEFEFE;
    GC_BYTE(0xBEC) = 0xFE;
    GC_BYTE(0xBF0) = 0xFE;
    GC_BYTE(0xBF1) = 0xFE;
    GC_BYTE(0xBF2) = 0xFE;
    GC_BYTE(0xBF3) = 0xFE;
    GC_WORD(0xBF4) = 0xFEFEFEFE;
    GC_FLOAT(0xBF8) = 4.2781243e9f;
    GC_FLOAT(0xBFC) = 4.2781243e9f;
    GC_FLOAT(0xC00) = 4.2781243e9f;
    GC_FLOAT(0xC04) = 4.2781243e9f;
    GC_BYTE(0xC08) = 1;
    GC_HALF(0xC0E) = 0xFEFE;
    GC_BYTE(0xC0D) = 0xFE;
}

void GSgfx_GCInitState(void) {
    s32 i = 0;
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
    for (i = 0; i < 4; ++i) {
        gsgfxState->tevConstantSelect[i * 2].swap.selector0 = 0;
        gsgfxState->tevConstantSelect[i * 2].swap.selector1 = 1;
        gsgfxState->tevConstantSelect[i * 2 + 1].swap.selector0 = 2;
        gsgfxState->tevConstantSelect[i * 2 + 1].swap.selector1 = 3;
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

}
