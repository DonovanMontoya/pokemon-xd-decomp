#ifndef GSCOLSYS2_HIT_PRIVATE_HPP
#define GSCOLSYS2_HIT_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSvec { f32 x,y,z; };
struct GSmtx { f32 m[3][4]; };
struct HitPolygon { Vec vertices[3],normal; u16 edgeFlags,reserved; };
struct HitCell { u32 first,count; };
struct CCD_HITMDL_HEAD {
    HitPolygon *polygons; u32 count;
    HitCell *cells; u32 *indices;
    u16 width,depth;
    f32 cellWidth,cellDepth,originX,originZ;
};
struct HitObject { u8 transform[0x28]; CCD_HITMDL_HEAD *model; u8 other[8]; CCD_HITMDL_HEAD *npcModel; u32 reserved; u16 flags,padding; };
struct HitFile { HitObject *objects; u32 count; };
typedef char HitPolygonSize[sizeof(HitPolygon)==52?1:-1];
typedef char HitObjectSize[sizeof(HitObject)==64?1:-1];
typedef char HitObjectNpcOffset[offsetof(HitObject,npcModel)==0x34?1:-1];
typedef char HitObjectModelOffset[offsetof(HitObject,model)==0x28?1:-1];
typedef char HitObjectFlagsOffset[offsetof(HitObject,flags)==0x3c?1:-1];
typedef char HitModelCellsOffset[offsetof(CCD_HITMDL_HEAD,cells)==8?1:-1];
typedef char HitModelOriginOffset[offsetof(CCD_HITMDL_HEAD,originX)==28?1:-1];
extern "C" {
HitFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjEnable(s32,u8 *);
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
u8 GScolsy2UtilChkInTri(Vec *,Vec *,Vec *);
void GScolsy2UtilGetCpPlanePoint(Vec *,Vec *,Vec *,Vec *);
f32 GScolsy2UtilGetSidePlanePoint(Vec *,Vec *,Vec *);
f32 GScolsys2UtilGetCpLinePoint(Vec *,Vec *,Vec *,Vec *);
void GScolsy2UtilGetPointExtentionLine(Vec *,Vec *,Vec *,f32);
}
#endif
