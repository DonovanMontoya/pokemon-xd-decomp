#ifndef APP_SCRIPT_OBJ_CAMERA_PRIVATE_HPP
#define APP_SCRIPT_OBJ_CAMERA_PRIVATE_HPP
#include <game/pxdvs/app/script/appScriptPrivate.hpp>
inline GSvec::GSvec() {}
extern "C" {
void GScameraGetPerspective(void *,f32 *,f32 *,f32 *,f32 *);void GScameraSetPerspective(void *,f32,f32,f32,f32);void GScameraSetPosition(void *,GSvec *);
f32 cameraGetFov();void cameraGetPosition(GSvec *);void cameraGetRotation(GSvec *);
u8 cameraMoveEndCheck(u8);void cameraMoveFov(u8,f32,f32);void cameraMoveFovAcc(f32);
void cameraMovePositionAcc(f32);void cameraMovePositionXYZ(u8,f32,f32,f32,f32);
void cameraMoveRotationAcc(f32);void cameraMoveRotationXYZ(s32,f32,f32,f32,f32);
void cameraMoveTarget(u8,u32,u32,f32);void cameraMoveTargetPosAcc(f32);void cameraMoveTargetXYZ(u8,f32,f32,f32,f32);
void cameraPauseAnime();void cameraPlayAnime(u32,u32,u8,f32);void cameraResumeAnime();void cameraReturn(u8,f32);
void cameraSetAnimeRate(f32);void cameraSetDistance(f32);void cameraSetFloorDefault(f32,f32,f32);void cameraSetFov(f32);void cameraSetHeight(f32);
void cameraSetPartTargetOffset(GSvec *);void cameraSetPosition(GSvec *);void cameraSetRotY(f32);void cameraSetRotationXYZ(f32,f32,f32);
void cameraSetTarget(u32,u32);void cameraSetTargetExt(u32,u32,s32);void cameraSetTargetOfsXYZ(f32,f32,f32);void cameraSetTargetPosXYZ(f32,f32,f32);
void cameraSetType(u8);void cameraStopAnime();void cameraUpdate();u8 cameraWaitSyncAnime(u8);
void floorFieldCameraBlend(f32);void floorFieldCameraDisable();void floorFieldCameraEnable();
}
static inline GSresID *cameraScriptPeople(GSscript::tigaVariant *v) {
 if(v->type==0x23)return (GSresID*)v->value.pointer;
 GSscript::tigaErrMessage("people not access");return 0;
}
#endif
