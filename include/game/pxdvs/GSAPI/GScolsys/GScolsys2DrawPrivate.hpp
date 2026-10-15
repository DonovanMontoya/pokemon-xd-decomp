#ifndef GSCOLSYS2_DRAW_PRIVATE_HPP
#define GSCOLSYS2_DRAW_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <dolphin/gx.h>
#include <libc/stddef.h>
struct GSmtx { Mtx m; };
struct DrawPolygon { Vec vertices[3],normal; u8 attribute,flags; u16 id; };
struct DrawSunPolygon { Vec vertices[3],normal; };
struct CCD_HITMDL_HEAD { DrawPolygon *polygons; u32 count; u8 grid[32]; };
struct CCD_WALKMDL_HEAD { DrawPolygon *polygons; u32 count; u8 grid[32]; };
struct DrawSunModel { DrawSunPolygon *polygons; u32 count; };
struct DrawObject {
 f32 position[3],rotation[3],scale[3];
 CCD_WALKMDL_HEAD *walk;
 CCD_HITMDL_HEAD *hit,*thru,*check,*npc;
 DrawSunModel *sun;
 u16 flags,padding;
};
struct DrawFile { DrawObject *objects; u32 count; };
struct DrawStateObject { f32 transform[9]; u16 flags,padding; };
struct DrawFloor { DrawStateObject objects[64]; u8 humans[0x3c0]; };
struct DrawList { u16 flags,stride; void *data; u32 size; void *format; };
struct DrawState { DrawFile *head; DrawFloor floors[1]; s32 currentFloor; void *format; DrawList *displayList; };
typedef char DrawListSize[sizeof(DrawList)==16?1:-1];
typedef char DrawSunPolygonSize[sizeof(DrawSunPolygon)==48?1:-1];
typedef char DrawObjectFlags[offsetof(DrawObject,flags)==0x3c?1:-1];
typedef char DrawObjectWalk[offsetof(DrawObject,walk)==0x24?1:-1];
typedef char DrawStateFlags[offsetof(DrawStateObject,flags)==0x24?1:-1];
typedef char DrawObjectSize[sizeof(DrawObject)==64?1:-1];
typedef char DrawPolygonSize[sizeof(DrawPolygon)==52?1:-1];
typedef char DrawFloorSize[sizeof(DrawFloor)==0xdc0?1:-1];
typedef char DrawStateFormat[offsetof(DrawState,format)==0xdc8?1:-1];
extern "C" {
extern DrawState GScolsys2;
DrawFile *GScolsys2GetCCDFileHead();
s32 GScolsys2GetObjMatrix(Mtx,u32);
s32 GScolsys2GetObjRotMatrix(Mtx,u32);
void GSgfxDLPrimitiveType(s32);
void GSgfxDLBeginSurface(u16);
void GSgfxDLEndSurface();
void GSgfxDLBegin(DrawList *,void *,u16,u16);
void GSgfxDLEnd();
void GSgfxDLDraw(DrawList *);
void GSgfxSetupRenderAndSelect(void *);
void GSgfxLayerSetActive(s32);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxCullMode(s32);
void GSgfxBlendMode(s32,s32,s32);
void GSgfxZCompare(s32,s32);
void GSgfxPixelMode(s32,s32,s32);
u32 GSinputButtonsPressed(s32);
void floorMapSetDisp(s32);
void GScolsys2HumanDispColision();
}
#endif
