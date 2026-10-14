#ifndef APP_CAMERA_HPP
#define APP_CAMERA_HPP
#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>

template<class T> class CameraAnimation {
public:
    s32 phase;
    u8 moving, firstUpdate, accelerating, accelerateIn, accelerateOut;
    u8 reserved09[3];
    f32 speed, acceleration, brakeTime, duration, elapsed;
    T startPosition, endPosition, currentPosition;
    CameraAnimation();
    void start(const T*, const T*, f32);
    void stop();
    u8 isMove() const;
    u8 update(f32);
    u8 updateAcceleration(f32);
    void setAcceleration(f32);
    const T* getCurrentPos() const;
};
// The original unit stores one scalar and four vector interpolators inline.
typedef char CameraScalarAnimationSizeCheck[sizeof(CameraAnimation<f32>) == 0x2c ? 1 : -1];
typedef char CameraVectorAnimationSizeCheck[sizeof(CameraAnimation<GSvec>) == 0x44 ? 1 : -1];
struct CameraWork {
    u8 type, moving, previousType, flags;
    GSvec position, rotation, targetPosition, targetOffset;
    u32 targetGroup, targetID;
    s32 targetPart;
    f32 height, distance, fov, lockedTargetY;
    CameraAnimation<f32> fovAnimation;
    CameraAnimation<GSvec> targetAnimation, offsetAnimation, positionAnimation, rotationAnimation;
    u32 animationGroup, animationID;
    GSvec offsetPosition, offsetRotation, offsetScale, partTargetOffset;
};
struct FloorCamera {
    s32 state;
    u32 floorID;
    f32 defaultHeight, defaultDistance, defaultRotation, defaultFov;
    f32 height, distance, rotation, fov;
};
typedef char CameraWorkSizeCheck[sizeof(CameraWork) == 0x1c4 ? 1 : -1];
typedef char FloorCameraSizeCheck[sizeof(FloorCamera) == 0x28 ? 1 : -1];
extern "C" {
extern CameraWork* pCamWork;
void fn_80196A14(u8);
void cameraLockYTarget(u8);
void cameraSetMirrorFlag(s32);
void cameraSetOffsetScale(const GSvec*);
void cameraSetOffsetRotation(const GSvec*);
void cameraSetOffsetPosition(const GSvec*);
f32 cameraGetFov();
f32 cameraGetRotY();
f32 cameraGetDistance();
f32 cameraGetHeight();
void cameraSetFov(f32);
void cameraSetRotY(f32);
void cameraSetDistance(f32);
void cameraSetHeight(f32);
void cameraSetRotationXYZ(f32,f32,f32);
void cameraSetTargetPosXYZ(f32,f32,f32);
void cameraSetTargetOfsXYZ(f32,f32,f32);
void cameraSetAnimeRate(f32);
void cameraResumeAnime();
void cameraPauseAnime();
void cameraStopAnime();
s32 cameraWaitSyncAnime(u8);
void cameraPlayOffsetAnime(u32,u32,s32,u8);
void cameraPlayAnime(u32,u32,u8,f32);
void cameraMoveStop();
s32 cameraMoveEndCheckSpecial(u8);
s32 cameraMoveEndCheck(u8);
void cameraReturn(u8,f32);
void cameraMoveFovAcc(f32);
void cameraMoveRotationAcc(f32);
void cameraMovePositionAcc(f32);
void cameraMoveTargetOfsAcc(f32);
void cameraMoveTargetPosAcc(f32);
// Movement entry points retain an unused leading mode argument in the original ABI.
void cameraMoveRotationXYZ(u32,f32,f32,f32,f32);
void cameraMoveRotation(u32,const GSvec*,f32);
void cameraMoveFov(u32,f32,f32);
void cameraMovePositionXYZ(u32,f32,f32,f32,f32);
void cameraMovePosition(u32,const GSvec*,f32);
void cameraMoveTargetXYZ(u32,f32,f32,f32,f32);
void cameraMoveTargetOfs(u32,const GSvec*,f32);
void cameraMoveTargetPos(u32,const GSvec*,f32);
void cameraMoveTarget(u32,u32,u32,f32);
void cameraGetRotation(GSvec*);
void cameraSetRotation(const GSvec*);
void cameraGetPosition(GSvec*);
void cameraSetPosition(const GSvec*);
void cameraGetTargetPos(GSvec*);
void cameraSetTargetPos(const GSvec*);
void cameraGetTargetOfs(GSvec*);
void cameraSetTargetOfs(const GSvec*);
void cameraSetPartTargetOffset(const GSvec*);
void cameraSetTargetExt(u32,u32,s32);
void cameraSetTarget(u32,u32);
GScamera* cameraGetActive();
u8 cameraGetType();
u8 cameraSetType(u8);
void cameraInit();
void cameraUpdate();
void cameraRefreshTargetPos();
void cameraSetGScamera(GScamera*);
void cameraResetFloor();
void cameraSetFloorDefault(f32,f32,f32);
}
#endif
