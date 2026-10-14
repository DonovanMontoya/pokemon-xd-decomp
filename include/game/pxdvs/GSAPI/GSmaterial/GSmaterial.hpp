#ifndef GSMATERIAL_HPP
#define GSMATERIAL_HPP
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <game/maximum/GSAPI/baselib/animation_objects.h>
struct GSimageDesc { void* image; u16 width, height; GXTexFmt format; u32 mipmap; f32 minLOD, maxLOD; };
struct GSmaterial {
    u16 alpha, extensions;
    u32 savedFlags;
    HSD_MObj* object;
    GXColor modulate;
    u8 channels[4];
    HSD_TObj* environment;
    GSimageDesc* environmentImage;
    GStexture* environmentTexture;
    s32 environmentSource, environmentMode;
    f32 environmentBlend;
    GSimageDesc* savedImage;
    void* savedPE;
};
typedef char GSmaterialSizeCheck[sizeof(GSmaterial) == 0x34 ? 1 : -1];
extern "C" {
void GSmaterialInit();
void GSmaterialResetTexture(GSmaterial*);
void GSmaterialGetTexture(GSmaterial*, GStexture*);
void GSmaterialSetTexture(GSmaterial*, GStexture*);
void GSmaterialGetModulate(GSmaterial*, GXColor*);
void GSmaterialResetAlpha(GSmaterial*);
void GSmaterialStoreAlpha(GSmaterial*);
void GSmaterialSetEnvMapBlendValue(GSmaterial*, f32);
void GSmaterialSetEnvMapParams(GSmaterial*, s32, s32, GStexture*, f32);
void GSmaterialSetModulate(GSmaterial*, GXColor*);
void GSmaterialSetColorChannels(GSmaterial*, u8*);
void GSmaterialSetAlpha(GSmaterial*, f32);
u32 GSmaterialGetEnabledExtensions(GSmaterial*);
void GSmaterialDisableExtension(GSmaterial*, u32);
void GSmaterialEnableExtension(GSmaterial*, u32);
u32 GSmaterialGetFlags(GSmaterial*);
void GSmaterialResetPEdescr(GSmaterial*);
void GSmaterialSetPEdescr(GSmaterial*, void*);
void GSmaterialResetFlags(GSmaterial*);
void GSmaterialSetFlags(GSmaterial*, u32);
}
#endif
