#ifndef PEOPLE_COLISION_PRIVATE_HPP
#define PEOPLE_COLISION_PRIVATE_HPP
#include <game/pxdvs/app/people/runtime.hpp>
struct Resource { u8 used; };
extern "C" {
tagPeopleWork* peopleGet(u32,u32);
GSvec* peopleBiosGetPosPtr(tagPeopleWork*);
GSvec* peopleBiosGetPrevPosPtr(tagPeopleWork*);
PeopleInfo* peopleInfoBiosGetPtr(u32);
f32 peopleInfoBiosGetColBallSize(PeopleInfo*);
void peopleBiosSetPos(tagPeopleWork*,GSvec*);
void heroMoveSetLockFrame(s32);
Resource* GSresGetResource(u32,u32);
void PSVECSubtract(GSvec*,GSvec*,GSvec*);
void PSVECAdd(GSvec*,GSvec*,GSvec*);
void PSVECNormalize(GSvec*,GSvec*);
void PSVECScale(GSvec*,GSvec*,f32);
f32 PSVECMag(GSvec*);
f32 PSVECDotProduct(GSvec*,GSvec*);
f32 PSVECSquareDistance(GSvec*,GSvec*);
void GSgfxLayerSetActive(s32);
void GScameraLoadActiveCameraMatrix(s32);
void GSgfxCullMode(s32);
void GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void GSgfxSetupRenderAndSelect(void);
void GSgfxBlendMode(s32,s32,s32);
void GSgfxZCompare(s32,s32);
void GSgfxPixelMode(s32,s32,s32);
void GSgfxAlphaCompare(s32,s32,s32,s32,s32,s32);
void GSgfxSetPrimitiveType(s32);
void GSgfxBeginSurface(s32);
void GSgfxVertex3f(f32,f32,f32);
void GSgfxColor4u8(u8,u8,u8,u8);
void GSgfxEndSurface(void);
f32 GScolsy2UtilGetSidePlanePoint(GSvec*,GSvec*,GSvec*);
void GScolsy2UtilGetCpPlanePoint(GSvec*,GSvec*,GSvec*,GSvec*);
s32 GScolsy2UtilChkInTri(GSvec*,GSvec*,GSvec*);
void GScolsy2UtilGetPointExtentionLine(GSvec*,GSvec*,GSvec*,f32);
u8 GScolsys2HitCollision(GSvec*,GSvec*,GSvec*,f32);
u8 peopleLineCheck(u32,u32,f32,f32,f32,f32,u8);
u8 peopleRectCheck(u32,u32,f32,f32,f32,f32);
static u8 _peopleGetCrossPoint__FP5GSvecP5GSvecfP5GSvecP5GSvecP5GSvec(GSvec*,GSvec*,f32,GSvec*,GSvec*,GSvec*);
static u8 getCpPointPoly__FP5GSvecP5GSvecfP5GSvecP5GSvec(GSvec*,GSvec*,f32,GSvec*,GSvec*);
}
#endif
