#include <game/pxdvs/GSAPI/GScolsys/GScolsys2DrawPrivate.hpp>
#include <libc/string.h>
static DrawList _colsysDL;
#pragma dont_inline on
static void drawHitMdl(CCD_HITMDL_HEAD *model, GSmtx *matrix, GSmtx *rotation) {
 DrawPolygon *polygon=model->polygons;
 Vec transformed[3];
 GXColor color={255,255,255,255};
 u8 green,blue,alpha,red;
 alpha=color.a; blue=color.b; green=color.g; red=color.r;
 Vec *base=transformed;
 u32 p;
 for(p=0;p<model->count;++p,++polygon) {
  Vec *src;
  Vec *dst=base;
  src=polygon->vertices;
  for(int i=0;i<3;++i,++src,++dst) PSMTXMultVec(matrix->m,src,dst);
  GSgfxDLPrimitiveType(0xa8);
  Vec *vertex;
  int i=0;
  vertex=base;
  for(;i<3;++i,++vertex) {
   int next=i+1; if(next>=3) next=0;
   GSgfxDLBeginSurface(2);
   GXWGFifo.f32=vertex->x; GXWGFifo.f32=vertex->y; GXWGFifo.f32=vertex->z;
   GXWGFifo.u8=red; GXWGFifo.u8=green; GXWGFifo.u8=blue; GXWGFifo.u8=alpha;
   Vec *end=&transformed[next];
   GXWGFifo.f32=end->x; GXWGFifo.f32=end->y; GXWGFifo.f32=end->z;
   GXWGFifo.u8=red; GXWGFifo.u8=green; GXWGFifo.u8=blue; GXWGFifo.u8=alpha;
   GSgfxDLEndSurface();
  }
 }
}
static void drawWalkMdl(CCD_WALKMDL_HEAD *model, GSmtx *matrix, GSmtx *rotation) {
 Vec transformed;
 GXColor color;
 GSgfxDLPrimitiveType(0x90);
 u32 p;
 DrawPolygon *polygon=model->polygons;
 for(p=0;p<model->count;++p,++polygon) {
  memset(&color,0,4); color.a=0xc0;
  u8 attribute=polygon->attribute;
  int blue=(attribute&15)+1;
  color.g=(s8)(127.0f*((f32)((attribute>>4)&15)/15.0f)+128.0f);
  if(blue>=16) blue=0;
  color.b=(s8)(255.0f*((f32)blue/15.0f));
  int red=(polygon->flags>>4)&15;
  if(red>0) color.r=red*4+0xc0;
  GSgfxDLBeginSurface(3);
  Vec *src;
  int i=0;
  src=polygon->vertices;
  for(;i<3;++i,++src) {
   PSMTXMultVec(matrix->m,src,&transformed);
   GXWGFifo.f32=transformed.x; GXWGFifo.f32=0.1f+transformed.y; GXWGFifo.f32=transformed.z;
   GXWGFifo.u8=color.r; GXWGFifo.u8=color.g; GXWGFifo.u8=color.b; GXWGFifo.u8=color.a;
  }
  GSgfxDLEndSurface();
 }
}
#pragma dont_inline reset
static DrawList *makeDisplayListFixedObj() {
GSmtx matrix,rotation;
 Vec thruVertex,checkVertex,sunVertex;
 GXColor thruColor,checkColor,sunColor;
 DrawFile *head=GScolsys2GetCCDFileHead();
 if(!head) return 0;
 memset(&_colsysDL,0,16);
 GSgfxDLBegin(&_colsysDL,GScolsys2.format,0x400,0x8000);
 u32 index;
 DrawObject *object=head->objects;
 for(index=0;index<head->count;++index,++object) {
 if(!(object->flags&1)) {
GScolsys2GetObjMatrix(matrix.m,index);
 GScolsys2GetObjRotMatrix(rotation.m,index);
 if(object->walk) drawWalkMdl(object->walk,&matrix,&rotation);
 if(object->hit) drawHitMdl(object->hit,&matrix,&rotation);
{
  CCD_HITMDL_HEAD *model=object->thru;
  if(model) {
   DrawPolygon *polygon=model->polygons;
   const GXColor color={255,0,255,192}; thruColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&thruVertex);
     GXWGFifo.f32=thruVertex.x; GXWGFifo.f32=thruVertex.y; GXWGFifo.f32=thruVertex.z; GXWGFifo.u8=thruColor.r; GXWGFifo.u8=thruColor.g; GXWGFifo.u8=thruColor.b; GXWGFifo.u8=thruColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
{
  CCD_HITMDL_HEAD *model=object->check;
  if(model) {
   DrawPolygon *polygon=model->polygons;
   const GXColor color={255,255,0,192}; checkColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&checkVertex);
     GXWGFifo.f32=checkVertex.x; GXWGFifo.f32=checkVertex.y; GXWGFifo.f32=checkVertex.z; GXWGFifo.u8=checkColor.r; GXWGFifo.u8=checkColor.g; GXWGFifo.u8=checkColor.b; GXWGFifo.u8=checkColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
if(object->npc) drawHitMdl(object->npc,&matrix,&rotation);
{
  DrawSunModel *model=object->sun;
  if(model) {
   DrawSunPolygon *polygon=model->polygons;
   const GXColor color={0,255,255,192}; sunColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&sunVertex);
     GXWGFifo.f32=sunVertex.x; GXWGFifo.f32=sunVertex.y; GXWGFifo.f32=sunVertex.z; GXWGFifo.u8=sunColor.r; GXWGFifo.u8=sunColor.g; GXWGFifo.u8=sunColor.b; GXWGFifo.u8=sunColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
 }
 }
 GSgfxDLEnd();
 return &_colsysDL;
}
extern "C" void GScolsys2Draw() {
GSmtx matrix,rotation;
 Vec thruVertex,checkVertex,sunVertex;
 GXColor thruColor,checkColor,sunColor;
 DrawFile *head=GScolsys2GetCCDFileHead();
 if(!head) return;
 if(GSinputButtonsPressed(1)&0x40) floorMapSetDisp(0);
 else if(GSinputButtonsPressed(1)&0x20) floorMapSetDisp(1);
 GSgfxLayerSetActive(2); GScameraLoadActiveCameraMatrix(2);
 GSgfxCullMode(1); GSgfxSetupRenderAndSelect(GScolsys2.format);
 GSgfxBlendMode(1,4,5); GSgfxZCompare(1,3); GSgfxPixelMode(1,1,1);
 u32 index;
 DrawObject *object=head->objects;
 DrawStateObject *state=GScolsys2.floors[GScolsys2.currentFloor].objects;
 for(index=0;index<head->count;++index,++object,++state) {
 if(!(state->flags&1)&&(object->flags&1)) {
GScolsys2GetObjMatrix(matrix.m,index);
 GScolsys2GetObjRotMatrix(rotation.m,index);
 if(object->walk) drawWalkMdl(object->walk,&matrix,&rotation);
 if(object->hit) drawHitMdl(object->hit,&matrix,&rotation);
{
  CCD_HITMDL_HEAD *model=object->thru;
  if(model) {
   DrawPolygon *polygon=model->polygons;
   const GXColor color={255,0,255,192}; thruColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&thruVertex);
     GXWGFifo.f32=thruVertex.x; GXWGFifo.f32=thruVertex.y; GXWGFifo.f32=thruVertex.z; GXWGFifo.u8=thruColor.r; GXWGFifo.u8=thruColor.g; GXWGFifo.u8=thruColor.b; GXWGFifo.u8=thruColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
{
  CCD_HITMDL_HEAD *model=object->check;
  if(model) {
   DrawPolygon *polygon=model->polygons;
   const GXColor color={255,255,0,192}; checkColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&checkVertex);
     GXWGFifo.f32=checkVertex.x; GXWGFifo.f32=checkVertex.y; GXWGFifo.f32=checkVertex.z; GXWGFifo.u8=checkColor.r; GXWGFifo.u8=checkColor.g; GXWGFifo.u8=checkColor.b; GXWGFifo.u8=checkColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
if(object->npc) drawHitMdl(object->npc,&matrix,&rotation);
{
  DrawSunModel *model=object->sun;
  if(model) {
   DrawSunPolygon *polygon=model->polygons;
   const GXColor color={0,255,255,192}; sunColor=color;
   GSgfxDLPrimitiveType(0x90);
   for(u32 p=0;p<model->count;++p,++polygon) {
    GSgfxDLBeginSurface(3);
    Vec *src=polygon->vertices;
    for(int i=0;i<3;++i,++src) {
     PSMTXMultVec(matrix.m,src,&sunVertex);
     GXWGFifo.f32=sunVertex.x; GXWGFifo.f32=sunVertex.y; GXWGFifo.f32=sunVertex.z; GXWGFifo.u8=sunColor.r; GXWGFifo.u8=sunColor.g; GXWGFifo.u8=sunColor.b; GXWGFifo.u8=sunColor.a;
    }
    GSgfxDLEndSurface();
   }
  }
 }
 }
 }
 if(!GScolsys2.displayList) GScolsys2.displayList=makeDisplayListFixedObj();
 if(GScolsys2.displayList) GSgfxDLDraw(GScolsys2.displayList);
 GScolsys2HumanDispColision();
}
