#ifndef GSTEXTURE_HPP
#define GSTEXTURE_HPP
#include <dolphin/gx.h>

struct GStexture {
    u16 width;
    u16 height;
    u8 bitsPerPixel;
    u8 mipCount;
    u8 inUse;
    u8 dirty;
    s32 format;
    s32 tlutFormat;
    s32 wrapS;
    s32 wrapT;
    s32 minFilter;
    s32 magFilter;
    s32 mipFilter;
    void* allocation;
    void* images[8];
    void* palette;
    u32 imageSize;
    u16 lockCount;
    u16 reserved;
    GXTexObj texObj;
    GXTlutObj tlutObj;
};
typedef char GStextureSizeCheck[sizeof(GStexture) == 0x80 ? 1 : -1];
extern "C" {
void GStextureConvertToHW(GStexture* texture);
void GStextureConvertFromHW(GStexture* texture);
s32 GStextureGetGXformat(const GStexture* texture, u8 direct);
s32 GStextureGetTlutFormat(const GStexture* texture);
s32 GStextureGetFormat(const GStexture* texture);
u8 GStextureGetMiplevels(const GStexture* texture);
u16 GStextureGetYsize(const GStexture* texture);
u16 GStextureGetXsize(const GStexture* texture);
void GStextureUnlockImage(GStexture* texture);
void* GStextureLockImage(GStexture* texture, u8 level);
void GStextureSetFilter(GStexture* texture, s32 minFilter, s32 magFilter, s32 mipFilter);
void GStextureSetWrap(GStexture* texture, s32 wrapS, s32 wrapT);
void GStextureFree(GStexture* texture);
void GStextureInit(u32 count);
s32 GStextureCreateFromMemory(GStexture* texture, u16 width, u16 height, void* image, s32 format, s32 tlutFormat, u8 mipLevels);
s32 GXFmtToGStextureFmt(GXTexFmt format);
GStexture* GStextureCreate(u16 width, u16 height, s32 format, s32 tlutFormat, u8 mipLevels);
GStexture* GStextureLoad(void* serialized);
}
#endif
