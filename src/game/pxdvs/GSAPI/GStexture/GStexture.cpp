#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <dolphin/os.h>
#include <libc/string.h>

extern void GSgfxRenderWaitForDrawComplete();
extern "C" void GSmemFree(void*);
extern "C" void* GSmemAlloc(u32);

static u16 _texXformBuf[0xa00];
static GStexture* _textureStructList;
static u32 _textureStructCount;

static inline s32 textureGetGXformat(const GStexture* texture, u8 direct) {
    s32 result;
    switch (texture->format) {
    case 0: return GX_TF_C4;
    case 1: return GX_TF_C8;
    case 0x30: return GX_TF_C14X2;
    case 0x40: return GX_TF_I4;
    case 0x41: return GX_TF_IA4;
    case 0x42: return GX_TF_I8;
    case 0x43: return GX_TF_IA8;
    case 0x44: return GX_TF_RGB565;
    case 0x45: return GX_TF_RGBA8;
    case 0x90: return GX_TF_RGB5A3;
    case 0xb0: return GX_TF_CMPR;
    case 0xa0: result = GX_CTF_A8; if (direct) return GX_TF_I8; return result;
    case 0xa1: result = GX_CTF_R8; if (direct) return GX_TF_I8; return result;
    case 0xa2: result = GX_CTF_G8; if (direct) return GX_TF_I8; return result;
    case 0xa3: result = GX_CTF_B8; if (direct) return GX_TF_I8; return result;
    default: return -1;
    }
}
extern "C" {
void GStextureConvertToHW(GStexture* texture) {
    if ((texture->format == 0x44 || texture->format == 0x90) && !(texture->width & 2)) {
        if (texture->height & 2) return;
        ++texture->lockCount;
        u8* image = (u8*)texture->images[0];
        for (s32 y = 0; y < texture->height; y += 4) {
            u16* out = _texXformBuf;
            s32 byteOffset = 0;
            for (s32 x = 0; x < texture->width; x += 4) {
                u16* row = (u16*)(image + y * texture->width * 2 + byteOffset);
                byteOffset += 8;
                out[0] = row[0]; out[1] = row[1]; out[2] = row[2]; out[3] = row[3];
                row += texture->width;
                out[4] = row[0]; out[5] = row[1]; out[6] = row[2]; out[7] = row[3];
                row += texture->width;
                out[8] = row[0]; out[9] = row[1]; out[10] = row[2]; out[11] = row[3];
                row += texture->width;
                out[12] = row[0]; out[13] = row[1]; out[14] = row[2]; out[15] = row[3];
                out += 16;
            }
            memcpy(image + y * texture->width * 2, _texXformBuf, texture->width * 8);
        }
        DCStoreRange(texture->images[0], texture->imageSize);
        GXInvalidateTexAll();
        --texture->lockCount;
    }
}

void GStextureConvertFromHW(GStexture* texture) {
    if ((texture->format == 0x44 || texture->format == 0x90) && !(texture->width & 2)) {
        if (texture->height & 2) return;
        ++texture->lockCount;
        u8* image = (u8*)texture->images[0];
        for (s32 y = 0; y < texture->height; y += 4) {
            u16* out = _texXformBuf;
            u16* tile = (u16*)(image + y * texture->width * 2);
            for (s32 x = 0; x < texture->width; x += 4) {
                u16* row = out;
                row[0] = tile[0]; row[1] = tile[1]; row[2] = tile[2]; row[3] = tile[3];
                out += 4;
                row += texture->width;
                row[0] = tile[4]; row[1] = tile[5]; row[2] = tile[6]; row[3] = tile[7];
                row += texture->width;
                row[0] = tile[8]; row[1] = tile[9]; row[2] = tile[10]; row[3] = tile[11];
                row += texture->width;
                row[0] = tile[12]; row[1] = tile[13]; row[2] = tile[14]; row[3] = tile[15];
                tile += 16;
            }
            memcpy(image + y * texture->width * 2, _texXformBuf, texture->width * 8);
        }
        DCStoreRange(texture->images[0], texture->imageSize);
        GXInvalidateTexAll();
        --texture->lockCount;
    }
}

s32 GStextureGetGXformat(const GStexture* texture, u8 direct) {
    s32 result;
    switch (texture->format) {
    case 0: return GX_TF_C4;
    case 1: return GX_TF_C8;
    case 0x30: return GX_TF_C14X2;
    case 0x40: return GX_TF_I4;
    case 0x41: return GX_TF_IA4;
    case 0x42: return GX_TF_I8;
    case 0x43: return GX_TF_IA8;
    case 0x44: return GX_TF_RGB565;
    case 0x45: return GX_TF_RGBA8;
    case 0x90: return GX_TF_RGB5A3;
    case 0xb0: return GX_TF_CMPR;
    case 0xa0: result = GX_CTF_A8; if (direct) return GX_TF_I8; return result;
    case 0xa1: result = GX_CTF_R8; if (direct) return GX_TF_I8; return result;
    case 0xa2: result = GX_CTF_G8; if (direct) return GX_TF_I8; return result;
    case 0xa3: result = GX_CTF_B8; if (direct) return GX_TF_I8; return result;
    default: return -1;
    }
}
s32 GStextureGetTlutFormat(const GStexture* texture) { return texture->tlutFormat; }
s32 GStextureGetFormat(const GStexture* texture) { return texture->format; }
u8 GStextureGetMiplevels(const GStexture* texture) { return texture->mipCount - 1; }
u16 GStextureGetYsize(const GStexture* texture) { return texture->height; }
u16 GStextureGetXsize(const GStexture* texture) { return texture->width; }
void GStextureUnlockImage(GStexture* texture) {
    DCStoreRange(texture->images[0], texture->imageSize);
    GXInvalidateTexAll();
    --texture->lockCount;
}
void* GStextureLockImage(GStexture* texture, u8 level) {
    if (level >= 8) return 0;
    ++texture->lockCount;
    return texture->images[level];
}
void GStextureSetFilter(GStexture* texture, s32 minFilter, s32 magFilter, s32 mipFilter) {
    s32 filter = minFilter;
    texture->minFilter = filter;
    texture->magFilter = magFilter;
    texture->mipFilter = mipFilter;
    switch (texture->mipFilter) {
    case 0: if (texture->minFilter == 2) filter = GX_LINEAR; else filter = GX_NEAR; break;
    case 1: if (texture->minFilter == 2) filter = GX_LIN_MIP_NEAR; else filter = GX_NEAR_MIP_NEAR; break;
    case 2: if (texture->minFilter == 2) filter = GX_LIN_MIP_LIN; else filter = GX_NEAR_MIP_LIN; break;
    }
    GXInitTexObjLOD(&texture->texObj, (GXTexFilter)filter, (GXTexFilter)(texture->magFilter == 2 ? 1 : 0), 0.0f, (f32)(texture->mipCount - 1), 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    texture->dirty = 1;
}
void GStextureSetWrap(GStexture* texture, s32 wrapS, s32 wrapT) {
    s32 s = wrapS;
    s32 t = wrapT;
    texture->wrapS = s;
    texture->wrapT = t;
    switch (texture->wrapS) {
    case 0: s = GX_CLAMP; break;
    case 1: s = GX_REPEAT; break;
    case 2: s = GX_MIRROR; break;
    }
    switch (texture->wrapT) {
    case 0: t = GX_CLAMP; break;
    case 1: t = GX_REPEAT; break;
    case 2: t = GX_MIRROR; break;
    }
    GXInitTexObjWrapMode(&texture->texObj, (GXTexWrapMode)s, (GXTexWrapMode)t);
    texture->dirty = 1;
}
void GStextureFree(GStexture* texture) {
    if (texture->inUse) {
        GSgfxRenderWaitForDrawComplete();
        texture->inUse = 0;
        if (texture->allocation) GSmemFree(texture->allocation);
    }
}
void GStextureInit(u32 count) {
    _textureStructCount = count;
    _textureStructList = (GStexture*)GSmemAlloc(count * sizeof(GStexture));
    if (_textureStructList) {
        for (u32 i = 0; i < _textureStructCount; ++i) _textureStructList[i].inUse = 0;
    }
}

s32 GXFmtToGStextureFmt(GXTexFmt format) {
    switch (format) {
    case GX_TF_C4: return 0;
    case GX_TF_C8: return 1;
    case GX_TF_C14X2: return 0x30;
    case GX_TF_I4: return 0x40;
    case GX_TF_IA4: return 0x41;
    case GX_TF_I8: return 0x42;
    case GX_TF_IA8: return 0x43;
    case GX_TF_RGB565: return 0x44;
    case GX_TF_RGBA8: return 0x45;
    case GX_TF_RGB5A3: return 0x90;
    case GX_TF_CMPR: return 0xb0;
    case GX_CTF_A8: return 0xa0;
    case GX_CTF_R8: return 0xa1;
    case GX_CTF_G8: return 0xa2;
    case GX_CTF_B8: return 0xa3;
    default: return -1;
    }
}

}

static inline s32 textureSetBitDepth(GStexture* texture, s32 format) {
    s32 entries = 0;
    switch (format) {
    case 0: entries = 16; texture->bitsPerPixel = 4; break;
    case 1: entries = 256; texture->bitsPerPixel = 8; break;
    case 0x30: entries = 1024; texture->bitsPerPixel = 16; break;
    case 0x40: case 0xb0: texture->bitsPerPixel = 4; break;
    case 0x41: case 0x42: case 0xa0: case 0xa1: case 0xa2: case 0xa3: texture->bitsPerPixel = 8; break;
    case 0x43: case 0x44: case 0x90: texture->bitsPerPixel = 16; break;
    case 0x45: texture->bitsPerPixel = 32; break;
    default: return -1;
    }
    return entries;
}

static inline void textureInitHardware(GStexture* texture) {
    u16 entries = 0;
    if (texture->palette) {
        GXTexFmt format;
        switch (texture->format) {
        case 0: format = (GXTexFmt)GX_TF_C4; break;
        case 1: format = (GXTexFmt)GX_TF_C8; break;
        case 0x30: format = (GXTexFmt)GX_TF_C14X2; break;
        default: format = (GXTexFmt)-1; break;
        }
        switch (texture->format) {
        case 0: entries = 16; break;
        case 1: entries = 256; break;
        case 0x30: entries = 1024; break;
        }
        GXTlutFmt tlutFormat;
        switch (texture->tlutFormat) {
        case 1: tlutFormat = GX_TL_IA8; break;
        case 2: tlutFormat = GX_TL_RGB565; break;
        case 3: tlutFormat = GX_TL_RGB5A3; break;
        }
        GXInitTlutObj(&texture->tlutObj, texture->palette, tlutFormat, entries);
        GXInitTexObjCI(&texture->texObj, texture->images[0], texture->width, texture->height,
                      (GXCITexFmt)format, GX_CLAMP, GX_CLAMP, texture->mipCount > 1, 0);
    } else {
        GXTexFmt format = (GXTexFmt)textureGetGXformat(texture, 1);
        GXInitTexObj(&texture->texObj, texture->images[0], texture->width, texture->height,
                     format, GX_CLAMP, GX_CLAMP, texture->mipCount > 1);
    }
}

static inline void textureSetMipImages(GStexture* texture, u32 imageBytes) {
    for (s32 i = 1; i < 8; ++i) {
        if (i < texture->mipCount) {
            texture->images[i] = (u8*)texture->images[i - 1] + imageBytes;
            imageBytes >>= 1;
        } else {
            texture->images[i] = 0;
        }
    }
    if (texture->tlutFormat > 0 && texture->tlutFormat < 4) {
        texture->palette = (u8*)texture->images[texture->mipCount - 1] + imageBytes;
    } else {
        texture->palette = 0;
    }
}

extern "C" s32 GStextureCreateFromMemory(GStexture* texture, u16 width, u16 height,
                                         void* image, s32 format, s32 tlutFormat, u8 mipLevels) {
    s32 entries = 0;
    memset(texture, 0, sizeof(GStexture));
    texture->width = width;
    texture->height = height;
    switch (format) {
    case 0: entries = 16;
    case 0x40: case 0xb0: texture->bitsPerPixel = 4; break;
    case 1: entries = 256;
    case 0x41: case 0x42: case 0xa0: case 0xa1: case 0xa2: case 0xa3: texture->bitsPerPixel = 8; break;
    case 0x30: entries = 1024;
    case 0x43: case 0x44: case 0x90: texture->bitsPerPixel = 16; break;
    case 0x45: texture->bitsPerPixel = 32; break;
    default: return 0;
    }
    texture->mipCount = mipLevels + 1;
    s32 pixelCount = width * height;
    s32 i = 0;
    texture->inUse = 1;
    texture->dirty = 1;
    texture->format = format;
    texture->tlutFormat = tlutFormat;
    texture->wrapS = 0;
    texture->wrapT = 0;
    texture->minFilter = 2;
    texture->magFilter = 2;
    texture->mipFilter = 0;
    texture->allocation = 0;
    texture->images[0] = image;
    texture->images[1] = 0;
    texture->palette = 0;
    u32 size = (u32)(texture->bitsPerPixel * pixelCount) >> 3;
    texture->imageSize = 0;
    for (; i < mipLevels; ++i) {
        texture->imageSize += (size + 31) & ~31;
        size >>= 1;
    }
    if (entries) {
        if (tlutFormat == 0 || tlutFormat < 0 || tlutFormat >= 4) return 0;
        texture->imageSize += (entries * 16) >> 3;
    }
    textureSetMipImages(texture, (u32)(texture->bitsPerPixel * pixelCount) >> 3);
    textureInitHardware(texture);
    DCStoreRange(texture->images[0], texture->imageSize);
    return 1;
}

extern "C" void GSgfxVideoGetEFBSize(u16* width, u16* height);
extern "C" void GSlogWrite(const char* format, ...);
extern "C" void* GSmemAllocAlign(u32 size, u16 alignment);

extern "C" GStexture* GStextureCreate(u16 width, u16 height, s32 format,
                                      s32 tlutFormat, u8 mipLevels) {
    if (width == 0 && height == 0) GSgfxVideoGetEFBSize(&width, &height);
    if (width > 1024 || height > 1024 || width < 4 || height < 4) return 0;
    s32 alignment;
    switch (format) {
    case 0: case 0x40: case 0x41: case 0xb0: alignment = 8; break;
    case 1: case 0x30: case 0x42: case 0x43: case 0x44: case 0x45: case 0x90:
    case 0xa0: case 0xa1: case 0xa2: case 0xa3: alignment = 4; break;
    default:
        GSlogWrite("GStexture: invalid texture format\n");
        return 0;
    }
    u16 alignedWidth = (width + alignment - 1) & ~(alignment - 1);
    u16 alignedHeight = (height + alignment - 1) & ~(alignment - 1);
    if (alignedWidth != width || alignedHeight != height) {
        GSlogWrite("GStexture: warning -- texture size adjusted from [%d,%d] to [%d,%d]\n",
                   width, height, alignedWidth, alignedHeight);
    }
    width = alignedWidth;
    height = alignedHeight;
    u16 mipWidth = width;
    u16 mipHeight = height;
    u8 maxMip = 0;
    while (mipWidth > 4 && mipHeight > 4 && maxMip < 7) {
        mipWidth >>= 1;
        mipHeight >>= 1;
        ++maxMip;
    }
    if (mipLevels > maxMip) mipLevels = maxMip;
    GStexture* texture = _textureStructList;
    u32 i;
    for (i = 0; i < _textureStructCount; ++i, ++texture) {
        if (!texture->inUse) break;
    }
    if (i == _textureStructCount) texture = 0;
    if (!texture) return 0;
    s32 entries = textureSetBitDepth(texture, format);
    if (entries < 0) return 0;
    u8 mipCount = mipLevels + 1;
    texture->imageSize = 0;
    u32 size = (u32)(texture->bitsPerPixel * (width * height)) >> 3;
    for (s32 level = 0; level < mipCount; ++level) {
        texture->imageSize += (size + 31) & ~31;
        size >>= 1;
    }
    if (entries) {
        if (tlutFormat == 0 || tlutFormat < 0 || tlutFormat >= 4) return 0;
        texture->imageSize += (entries * 16) >> 3;
    }
    texture->allocation = GSmemAllocAlign(texture->imageSize, 32);
    if (!texture->allocation) return 0;
    texture->images[0] = texture->allocation;
    DCStoreRange(texture->images[0], texture->imageSize);
    texture->inUse = 1;
    texture->width = width;
    texture->height = height;
    texture->mipCount = mipCount;
    texture->format = format;
    texture->tlutFormat = tlutFormat;
    texture->wrapS = 0;
    texture->wrapT = 0;
    texture->minFilter = 2;
    texture->magFilter = 2;
    texture->mipFilter = mipCount > 1 ? 2 : 0;
    texture->lockCount = 0;
    texture->reserved = 0;
    textureSetMipImages(texture, (u32)(texture->bitsPerPixel * (width * height)) >> 3);
    textureInitHardware(texture);
    texture->dirty = 1;
    return texture;
}

extern "C" GStexture* GStextureLoad(void* serialized) {
    GStexture* texture = (GStexture*)serialized;
    for (s32 i = 0; i < texture->mipCount; ++i) {
        texture->images[i] = (u8*)texture + (u32)texture->images[i];
    }
    for (s32 i = texture->mipCount; i < 8; ++i) texture->images[i] = 0;
    if (texture->palette) texture->palette = (u8*)texture + (u32)texture->palette;
    textureInitHardware(texture);
    GStextureSetWrap(texture, texture->wrapS, texture->wrapT);
    GStextureSetFilter(texture, texture->minFilter, texture->magFilter, texture->mipFilter);
    texture->dirty = 1;
    texture->allocation = 0;
    DCStoreRange(texture->images[0], texture->imageSize);
    return texture;
}
