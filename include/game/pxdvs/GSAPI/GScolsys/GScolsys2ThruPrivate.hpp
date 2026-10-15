#ifndef GSCOLSYS2_THRU_PRIVATE_HPP
#define GSCOLSYS2_THRU_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSvec { f32 x,y,z; GSvec(); };
struct GSmtx { f32 m[3][4]; };
struct ThruEvent { GSvec vertices[3]; Vec normal; u16 eventID,padding; };
struct ThruPolygon { Vec vertices[3],normal; u16 edgeFlags,eventID; };
struct ThruCell { u32 first,count; };
struct CCD_THRUMDL_HEAD {
    ThruPolygon *polygons; u32 count;
    ThruCell *cells; u32 *indices;
    u16 width,depth;
    f32 cellWidth,cellDepth,originX,originZ;
};
struct ThruObject { u8 transform[0x2c]; CCD_THRUMDL_HEAD *model; u8 other[12]; u16 flags,padding; };
struct ThruFile { ThruObject *objects; u32 count; };
typedef char ThruEventSize[sizeof(ThruEvent)==52?1:-1];
typedef char ThruEventNormalOffset[offsetof(ThruEvent,normal)==36?1:-1];
typedef char ThruEventIDOffset[offsetof(ThruEvent,eventID)==48?1:-1];
typedef char ThruPolygonSize[sizeof(ThruPolygon)==52?1:-1];
typedef char ThruPolygonFlagsOffset[offsetof(ThruPolygon,edgeFlags)==48?1:-1];
typedef char ThruPolygonIDOffset[offsetof(ThruPolygon,eventID)==50?1:-1];
typedef char ThruObjectSize[sizeof(ThruObject)==64?1:-1];
typedef char ThruModelCellsOffset[offsetof(CCD_THRUMDL_HEAD,cells)==8?1:-1];
typedef char ThruModelIndicesOffset[offsetof(CCD_THRUMDL_HEAD,indices)==12?1:-1];
typedef char ThruModelWidthOffset[offsetof(CCD_THRUMDL_HEAD,width)==16?1:-1];
typedef char ThruModelOriginOffset[offsetof(CCD_THRUMDL_HEAD,originX)==28?1:-1];
typedef char ThruObjectModelOffset[offsetof(ThruObject,model)==44?1:-1];
typedef char ThruObjectFlagsOffset[offsetof(ThruObject,flags)==60?1:-1];
extern "C" {
ThruFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjEnable(s32,u8 *);
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
u8 GScolsys2UtilGetCpPlaneLine(Vec *,f32 *,Vec *,Vec *,Vec *,Vec *);
u8 GScolsy2UtilChkInTri(Vec *,Vec *,Vec *);
void GScolsy2UtilGetCpPlanePoint(Vec *,Vec *,Vec *,Vec *);
f32 GScolsy2UtilGetSidePlanePoint(Vec *,Vec *,Vec *);
f32 GScolsys2UtilGetCpLinePoint(Vec *,Vec *,Vec *,Vec *);
}
#endif
