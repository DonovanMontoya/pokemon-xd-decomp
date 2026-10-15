#ifndef GSCOLSYS2_WALK_PRIVATE_HPP
#define GSCOLSYS2_WALK_PRIVATE_HPP
#include <dolphin/mtx.h>
struct GSvec { f32 x,y,z; };
struct WalkHeight { f32 height; u16 upper,lower; s8 layer,floor; u16 reserved; };
struct WalkPolygon { GSvec vertices[3],normal; u8 attributes[4]; };
struct WalkCell { u32 first,count; };
struct WalkModel {
    WalkPolygon *polygons; u32 count;
    WalkCell *cells; u32 *indices;
    u16 width,depth;
    f32 cellWidth,cellDepth,originX,originZ;
};
struct WalkObject { u8 transform[0x24]; WalkModel *model; u8 other[0x14]; u16 flags,padding; };
struct WalkFile { WalkObject *objects; u32 count; };
extern "C" {
WalkFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjEnable(s32,u8 *);
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
s32 GScolsys2WalkGetHeight(GSvec *,WalkHeight *);
}
#endif
