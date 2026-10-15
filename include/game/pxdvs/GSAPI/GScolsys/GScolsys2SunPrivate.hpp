#ifndef GSCOLSYS2_SUN_PRIVATE_HPP
#define GSCOLSYS2_SUN_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/string.h>
struct GSvec { f32 x,y,z; };
struct SunPolygon { GSvec vertices[3], normal; };
struct SunModel { SunPolygon *polygons; u32 count; };
struct SunObject { u8 data[0x38]; SunModel *model; u32 reserved; };
struct SunFile { SunObject *objects; u32 count; };
extern "C" {
SunFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjEnable(s32,u8 *);
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
u8 GScolsys2UtilGetCpPlaneLine(Vec *,f32 *,Vec *,Vec *,Vec *,Vec *);
u8 GScolsy2UtilChkInTri(Vec *,Vec *,Vec *);
}
#endif
