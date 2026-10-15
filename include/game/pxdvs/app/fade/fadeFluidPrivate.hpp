#ifndef APP_FADE_FLUID_PRIVATE_HPP
#define APP_FADE_FLUID_PRIVATE_HPP
#include <global.h>

struct FluidVec {f32 x,y,z;};
struct FluidUV {f32 u,v;};
struct FluidWork {
    u32 width,height;
    f32 a,b,c,speed,damping,spacing,screenX,screenY;
    FluidVec *vertices[2],*normal,*tangent;
    FluidUV *uv;
};
struct GStexture {u8 pad00[7];u8 dirty;};
struct GSgfxVF;
class GSgfxLayer {
public:
    u8 pad00[0xD8C];u32 fieldD8C;
    u8 padD90[0x8B4];
    u32 field1644,field1648,field164C,field1650;
    u8 pad1654[2],field1656,field1657,field1658,pad1659[3],field165C,pad165D[3];
    u32 field1660,field1664,field1668,field166C;
    u8 field1670,field1671,field1672,pad1673[0x35];
    u32 field16A8;u8 pad16AC[0xC];u32 field16B8;
    u8 pad16BC[0x50];u32 field170C;
    u8 pad1710[0x2C];u32 field173C;GStexture *texture0;
    u8 pad1744[0x1C];u32 field1760;
    u8 pad1764[0xC];u32 field1770;
    u8 pad1774[0x50];u32 field17C4;
    u8 pad17C8[0x2C];u32 field17F4;GStexture *texture1;
    u8 pad17FC[0x1C];u8 shaders[2][0xBC];
    void *shader; s32 shaderIndex;u32 primitive;
    void setRenderStateAndSelect(GSgfxVF *);
    void beginSurface(u16);
    void endSurface();
};
extern "C" {
GSgfxLayer *GSgfxLayerFindByID(s32);
GSgfxVF *GSgfxVFBuildTemp(u32,u32,u32,u32,u32,u32,u32,u32,u32);
void GSlerpGetLinearInterpolationVector(FluidVec *,FluidVec *,FluidVec *,f32);
void spriteSetEnv(s32);
void GSmemFree(void *);
s32 GSmemGetCurrentHeap();
s32 GSmemSetAllocMethodHeap(s32,s32);
void *GSmemAllocAlign(unsigned long,u32);
void OSReport(const char *,...);
}
typedef char FluidWorkSizeCheck[(sizeof(FluidWork)==0x3C)?1:-1];
typedef char FluidVecSizeCheck[(sizeof(FluidVec)==12)?1:-1];
typedef char FluidLayerRegisterSizeCheck[(sizeof(GSgfxLayer)==0x199C)?1:-1];
#endif
