#ifndef GSCOLSYS2_CHECK_PRIVATE_HPP
#define GSCOLSYS2_CHECK_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSvec { f32 x,y,z; GSvec(); };
struct GSmtx { f32 m[3][4]; };
typedef struct { GSvec vertices[3]; Vec normal; u16 eventID, padding; } CCDCheckEvent;
typedef char CheckEventSize[sizeof(CCDCheckEvent)==0x34 ? 1 : -1];
typedef char CheckEventVerticesOffset[offsetof(CCDCheckEvent,vertices)==0 ? 1 : -1];
typedef char CheckEventNormalOffset[offsetof(CCDCheckEvent,normal)==0x24 ? 1 : -1];
typedef char CheckEventIDOffset[offsetof(CCDCheckEvent,eventID)==0x30 ? 1 : -1];
struct CCD_CHECKMDL_HEAD { CCDCheckEvent *triangles; u32 count; };
struct CCDCheckObject { u8 transform[0x30]; CCD_CHECKMDL_HEAD *checks; u8 rest[12]; };
struct CCDCheckFile { CCDCheckObject *objects; u32 count; };
extern "C" {
CCDCheckFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjEnable(s32,u8 *);
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
u8 GScolsys2UtilGetCpPlaneLine(Vec *,f32 *,Vec *,Vec *,Vec *,Vec *);
u8 GScolsy2UtilChkInTri(Vec *,Vec *,Vec *);
}
#endif
