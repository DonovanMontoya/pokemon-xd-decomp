#ifndef GSPART_HPP
#define GSPART_HPP
#include <dolphin/mtx.h>
#include <game/maximum/GSAPI/baselib/aobj.h>
#include <game/maximum/GSAPI/baselib/jobj.h>
#include <game/maximum/GSAPI/baselib/dobj.h>
#include <game/pxdvs/GSAPI/GSmaterial/GSmaterial.hpp>
struct GSmodel;
struct HSD_TexAnim;
struct HSD_MatAnimJoint { HSD_MatAnimJoint *child, *next; HSD_MatAnim* animations; };
struct HSD_ShapeAnimJoint { HSD_ShapeAnimJoint *child, *next; void** animations; };
struct GSpart { u8 inUse, reserved; u16 index; GSmodel* model; HSD_JObj* joint; };
typedef GSmaterial GSpartMaterial;
typedef void (*GSpartAnimCallback)(HSD_AnimJoint*, void**, s32);
typedef void (*GSpartMatAnimCallback)(HSD_MatAnimJoint*, void**, s32);
typedef void (*GSpartShapeAnimCallback)(HSD_ShapeAnimJoint*, void**, s32);
extern "C" {
void GSpartAnimWalkTree(HSD_AnimJoint*, GSpartAnimCallback, void**);
void GSpartMatAnimWalkTree(HSD_MatAnimJoint*, GSpartMatAnimCallback, void**);
void GSpartShapeAnimWalkTree(HSD_ShapeAnimJoint*, GSpartShapeAnimCallback, void**);
HSD_AnimJoint* GSpartGetAnimPtr(HSD_AnimJoint*, u32);
HSD_MatAnimJoint* GSpartGetMatAnimPtr(HSD_MatAnimJoint*, u32);
HSD_ShapeAnimJoint* GSpartGetShapeAnimPtr(HSD_ShapeAnimJoint*, u32);
HSD_JObj* GSpartGetJObjPtr(HSD_JObj*, u32);
u32 GSpartGetJObjIndex(HSD_JObj*, HSD_JObj*);
void GSpartGetMatrix(GSpart*, Mtx);
void GSpartGetTransform(GSpart*, Vec*, Vec*, Vec*);
void GSpartInitMaterial(GSpartMaterial*, GSpart*, u32);
GSpartMaterial* GSpartGetMaterial(GSpart*, u32);
s32 GSpartGetMaterialCount(GSpart*);
s32 GSpartSetAnimIndex(GSpart*, s32, s32, f32);
s32 GSpartSetTexAnimIndex(GSpart*, s32, s32, s32, f32);
void GSpartUnregisterAnimMix(GSpart*, s32);
void GSpartRegisterAnimMix(GSpart*, s32, s32, u32, s32);
void GSpartStopAnimIndex(GSpart*, s32);
void GSpartFree(GSpart*);
GSpart* GSpartCreate();
void GSpartInit(u32);
}
#endif
