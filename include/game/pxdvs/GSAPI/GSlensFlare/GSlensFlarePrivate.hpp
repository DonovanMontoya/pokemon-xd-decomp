#ifndef GS_LENS_FLARE_PRIVATE_HPP
#define GS_LENS_FLARE_PRIVATE_HPP
#include <global.h>
#include <libc/stddef.h>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
#include <game/pxdvs/GSAPI/GSgfxM/matrixStack.hpp>
struct GSgfxVF;
struct GStexture { u8 reserved[7]; u8 dirty; };
struct GSgfxLayer {
 u8 reserved0[0x28];
 s32 id;
 s32 mode;
 u8 reserved30[0xD24];
 s32 projectionType;
 f32 p0;
 f32 p1;
 f32 p2;
 f32 p3;
 f32 p4;
 f32 p5;
 u8 reservedD70[0x1C];
 s32 fieldD8C;
 u8 reservedD90[0x8B4];
 s32 field1644;
 s32 field1648;
 s32 field164C;
 s32 field1650;
 u8 reserved1654[0x2];
 u8 field1656;
 u8 field1657;
 u8 field1658;
 u8 reserved1659[0x3];
 u8 field165C;
 u8 reserved165D[0x3];
 s32 field1660;
 s32 field1664;
 s32 field1668;
 s32 field166C;
 u8 field1670;
 u8 field1671;
 u8 field1672;
 u8 reserved1673[0x11];
 f32 field1684;
 f32 field1688;
 u8 reserved168C[0x1A];
 u8 field16A6;
 u8 field16A7;
 s32 field16A8;
 s32 field16AC;
 u8 reserved16B0[0x8];
 s32 field16B8;
 u8 reserved16BC[0x50];
 s32 field170C;
 u8 reserved1710[0x2C];
 s32 field173C;
 GStexture* field1740;
 u8 reserved1744[0x1C];
 s32 field1760;
 s32 field1764;
 u8 reserved1768[0x8];
 s32 field1770;
 u8 reserved1774[0x50];
 s32 field17C4;
 u8 reserved17C8[0x2C];
 s32 field17F4;
 GStexture* field17F8;
 u8 reserved17FC[0x194];
 void* field1990;
 s32 field1994;
 s32 field1998;
 u8 reserved199C[0x4];
 GSgfxMatrixStack* matrixStack;
 void SetLayerVisibility(bool);
 void setRenderStateAndSelect(GSgfxVF*);
 void beginSurface(u16);
 void endSurface();
};

struct LensElement { u16 flags, texture; f32 divisor, scale; u8 color[4]; };
struct LensHeader { u32 magic; u16 textureCount, elementCount; u32 flags, outerRadius, fadeStart, fadePeak; f32 frontTint, backTint, scaleFactor, minDistance, sampleRadius; };
struct LensTextureRecord { u16 index, reserved; u32 data; };
struct LensFlareWork {
 u8 visible; u8 reserved[3]; GSvec sun; f32 alpha; LensHeader* header; LensElement* elements; GStexture* textures[64];
 LensFlareWork() { visible=0; sun.param1=0.0f; sun.param2=0.0f; sun.param3=0.0f; header=0; elements=0; }
};
struct LensRenderModule { void (*init)(void*); void (*pre)(f32); void (*render)(GSgfxLayer*,s32); void (*fast)(); void (*post)(f32); void (*tick)(); u32 cookie; };
typedef char LensWorkSize[sizeof(LensFlareWork)==0x11c?1:-1];
typedef char LensHeaderSize[sizeof(LensHeader)==0x2c?1:-1];
typedef char LensElementSize[sizeof(LensElement)==0x10?1:-1];
typedef char LensMatrixStackOffset[offsetof(GSgfxLayer,matrixStack)==0x19a0?1:-1];
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
GStexture* GStextureLoad(void*);
void GStextureSetFilter(GStexture*,s32,s32,s32);
u16 GStextureGetXsize(const GStexture*);
u16 GStextureGetYsize(const GStexture*);
void GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(u8,LensRenderModule*,void*);
void* GScameraGetActiveCamera();
f32 (*GScameraGetMatrixPtr(void*))[4];
void GScameraGetPosition(void*,GSvec*);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxProjectSetupParameters();
s32 GSgfxProjectFast(GSvec*,GSvec*);
u8 GScolsys2SunArray(u8*,GSvec*,GSvec*,u16);
u8 GScolsys2Sun(GSvec*,GSvec*);
void GSmtx44Ortho(f32 (*)[4],f32,f32,f32,f32,f32,f32);
GSgfxVF* GSgfxVFGetPredef(s32);
extern Mtx mtxIdent;
void __ct__5GSvecFv(GSvec*);
void __construct_array(void*,void (*)(GSvec*),void*,u32,u32);
f64 atan2(f64,f64);
void GSlensFlareSetVisible(u32,bool);
void GSlensFlareSetSunPosition(u32,GSvec*);
void GSlensFlareFree(u32);
u32 GSlensFlareLoad(LensHeader*);
void GSlensFlareInit();
static void _lensFlareRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer*,s32);
}
#endif
