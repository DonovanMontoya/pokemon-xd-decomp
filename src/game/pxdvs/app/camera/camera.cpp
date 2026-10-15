#pragma defer_codegen on
#include <game/pxdvs/app/camera/camera.hpp>
#include <game/pxdvs/GSAPI/GSres/GSres.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <libc/string.h>
extern "C" {
#include <libc/math.h>
}
extern "C" {
f64 atan2(f64,f64);
u32 GSfloorGetCurrent();
extern u32* floordata_number;
void GSthreadSwitch();
void* GSthreadGetCurrentThread();
void GSlogWrite(const char*, ...);
u8 GSgfxVideoGetVsyncRate();
s32 GSgfxVideoGetLockFrameRate();
u8 floorFieldCameraDataExist();
void floorFieldCameraEnable();
void floorFieldCameraBlend(f32);
}
static CameraWork _cameraWork;
static CameraWork _cameraWorkBak;
struct CameraUpVector : GSvec { CameraUpVector() { param1=0.0f; param2=1.0f; param3=0.0f; } };
static CameraUpVector gUpVec;
extern "C" { CameraWork* pCamWork = &_cameraWork; }
static FloorCamera* _pFloorCamera;

static inline FloorCamera* currentFloorCamera() {
    u32 id = GSfloorGetCurrent();
    FloorCamera* camera = _pFloorCamera;
    for (s32 i = 0; (u32)i < *floordata_number; ++camera, ++i)
        if (id == camera->floorID) return &_pFloorCamera[i];
    return 0;
}
static inline GScamera* animationCamera(CameraWork* work) {
    GScamera* camera = (GScamera*)GSresGetResource(work->animationGroup, work->animationID);
    if (!camera) camera = (GScamera*)GSresGetResourceAllGroup(work->animationID);
    return camera;
}
static inline void copyVector(GSvec* to,const GSvec* from) { f32* d=(f32*)to; const f32* s=(const f32*)from; d[0]=s[0]; d[1]=s[1]; d[2]=s[2]; }
static inline Vec* vec(GSvec* v) { return (Vec*)v; }
static inline Vec* vec(const GSvec* v) { return (Vec*)v; }
extern "C" {
void fn_80196A14(u8 flag) { if (flag) pCamWork->flags |= 0x20; else pCamWork->flags &= ~0x20; }
void cameraLockYTarget(u8 flag) { if (flag) pCamWork->flags |= 0x18; else pCamWork->flags &= ~8; }
void cameraSetMirrorFlag(s32 flags) { pCamWork->flags &= 0x18; pCamWork->flags |= flags; }
#pragma scheduling off
void cameraSetOffsetScale(const GSvec* v) { CameraWork* work=pCamWork; work->offsetScale.param1=v->param1; work->offsetScale.param2=v->param2; work->offsetScale.param3=v->param3; }
void cameraSetOffsetRotation(const GSvec* v) { CameraWork* work=pCamWork; work->offsetRotation.param1=v->param1; work->offsetRotation.param2=v->param2; work->offsetRotation.param3=v->param3; }
void cameraSetOffsetPosition(const GSvec* v) { CameraWork* work=pCamWork; work->offsetPosition.param1=v->param1; work->offsetPosition.param2=v->param2; work->offsetPosition.param3=v->param3; }
#pragma scheduling reset
f32 cameraGetFov() { return pCamWork->fov; }
f32 cameraGetRotY() { return pCamWork->rotation.param2; }
f32 cameraGetDistance() { return pCamWork->distance; }
f32 cameraGetHeight() { return pCamWork->height; }
void cameraSetFov(f32 value) {
    if (value < 3.0f) value = 3.0f;
    if (value > 120.0f) value = 120.0f;
    FloorCamera* floor = currentFloorCamera();
    if (floor) floor->fov = value;
    pCamWork->fov = value;
}
void cameraSetRotY(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->rotation=value; pCamWork->rotation.param2=value; }
void cameraSetDistance(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->distance=value; pCamWork->distance=value; }
void cameraSetHeight(f32 value) { FloorCamera* floor=currentFloorCamera(); if (floor) floor->height=value; pCamWork->height=value; }
void cameraSetRotationXYZ(f32 x,f32 y,f32 z) {
    GSvec rotation; rotation.param1=x; rotation.param2=y; rotation.param3=z;
    GScamera* camera=(GScamera*)GSresGetResource(0,0);
    copyVector(&pCamWork->rotation,&rotation);
    GScameraSetRotation(camera,vec(&rotation));
}
void cameraSetTargetPosXYZ(f32 x,f32 y,f32 z) { CameraWork* work=pCamWork; work->targetPosition.param1=x; work->targetPosition.param2=y; work->targetPosition.param3=z; }
void cameraSetTargetOfsXYZ(f32 x,f32 y,f32 z) { CameraWork* work=pCamWork; work->targetOffset.param1=x; work->targetOffset.param2=y; work->targetOffset.param3=z; }
void cameraSetAnimeRate(f32 rate) { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraSetAnimRate(camera,rate); }
void cameraResumeAnime() { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraStartAnimation(camera); }
void cameraPauseAnime() { GScamera* camera=animationCamera(pCamWork); if(camera) GScameraStopAnimation(camera); }
void cameraStopAnime() {
    GScamera* camera=animationCamera(pCamWork);
    pCamWork->animationGroup=0; pCamWork->animationID=0;
    if(camera) GScameraStopAnimation(camera);
}
s32 cameraWaitSyncAnime(u8 wait) {
    GScamera* camera=animationCamera(pCamWork);
    if(!camera) return 0;
    if(wait) {
        for(;;) {
            if(GScameraHasAnimationEnded(camera)) break;
            if(!GSthreadGetCurrentThread()) { GSlogWrite("cameraWaitSyncAnime()  スレッドから呼ぶようにしてください\n"); break; }
            GSthreadSwitch();
        }
    } else if(!GScameraHasAnimationEnded(camera)) return 1;
    return 0;
}
void cameraPlayOffsetAnime(u32 group,u32 id,s32 frame,u8 loop) {
    if(pCamWork->animationGroup || pCamWork->animationID) cameraStopAnime();
    pCamWork->previousType=cameraSetType(8);
    pCamWork->animationGroup=group; pCamWork->animationID=id;
    GScamera* camera=animationCamera(pCamWork);
    if(camera) {
        GScameraSetAnimIndex(camera,0); GScameraSetAnimType(camera,loop ? 1 : 0);
        GScameraSetAnimRate(camera,0.5f); GScameraSetAnimFrame(camera,(f32)frame); GScameraStartAnimation(camera);
        pCamWork->offsetPosition.param1=0.0f; pCamWork->offsetPosition.param2=0.0f; pCamWork->offsetPosition.param3=0.0f;
        pCamWork->offsetRotation.param1=0.0f; pCamWork->offsetRotation.param2=0.0f; pCamWork->offsetRotation.param3=0.0f;
        pCamWork->offsetScale.param1=1.0f; pCamWork->offsetScale.param2=1.0f; pCamWork->offsetScale.param3=1.0f;
        GScameraSetActiveCamera((GScamera*)GSresGetResource(0,0));
    }
}
void cameraPlayAnime(u32 group,u32 id,u8 loop,f32 frame) {
    if(pCamWork->animationGroup || pCamWork->animationID) cameraStopAnime();
    pCamWork->previousType=cameraSetType(4);
    pCamWork->animationGroup=group; pCamWork->animationID=id;
    GScamera* camera=animationCamera(pCamWork);
    if(camera) {
        GScameraSetAnimIndex(camera,0); GScameraSetAnimType(camera,loop ? 1 : 0);
        GScameraSetAnimRate(camera,0.5f); GScameraSetAnimFrame(camera,frame); GScameraStartAnimation(camera); GScameraSetActiveCamera(camera);
    }
}
void cameraMoveStop() {
    pCamWork->targetAnimation.stop(); pCamWork->offsetAnimation.stop(); pCamWork->positionAnimation.stop(); pCamWork->rotationAnimation.stop(); pCamWork->fovAnimation.stop(); pCamWork->moving=0;
}
s32 cameraMoveEndCheckSpecial(u8 wait) {
    for(;;) {
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove()) return 0;
        if(wait) GSthreadSwitch(); else return 1;
    }
}
s32 cameraMoveEndCheck(u8 wait) {
    for(;;) {
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->offsetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove() && !pCamWork->fovAnimation.isMove()) return 0;
        if(wait) GSthreadSwitch(); else return 1;
    }
}
void cameraMoveFovAcc(f32 acceleration) { pCamWork->fovAnimation.setAcceleration(acceleration); }
void cameraMoveRotationAcc(f32 acceleration) { pCamWork->rotationAnimation.setAcceleration(acceleration); }
void cameraMovePositionAcc(f32 acceleration) { pCamWork->positionAnimation.setAcceleration(acceleration); }
void cameraMoveTargetOfsAcc(f32 acceleration) { pCamWork->offsetAnimation.setAcceleration(acceleration); }
void cameraMoveTargetPosAcc(f32 acceleration) { pCamWork->targetAnimation.setAcceleration(acceleration); }
void cameraMoveRotationXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec rotation; rotation.param1=x; rotation.param2=y; rotation.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetRotation(&rotation); return; }
    pCamWork->moving=1; pCamWork->rotationAnimation.start(&pCamWork->rotation,&rotation,duration);
}
void cameraMoveRotation(u32 mode,const GSvec* rotation,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetRotation(rotation); return; }
    pCamWork->moving=1; pCamWork->rotationAnimation.start(&pCamWork->rotation,rotation,duration);
}
void cameraMoveFov(u32 mode,f32 fov,f32 duration) { pCamWork->moving=1; pCamWork->fovAnimation.start(&pCamWork->fov,&fov,duration); }
void cameraMovePositionXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec position; position.param1=x; position.param2=y; position.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetPosition(&position); return; }
    pCamWork->moving=1; pCamWork->positionAnimation.start(&pCamWork->position,&position,duration);
}
void cameraMovePosition(u32 mode,const GSvec* position,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetPosition(position); return; }
    pCamWork->moving=1; pCamWork->positionAnimation.start(&pCamWork->position,position,duration);
}
void cameraMoveTargetXYZ(u32 mode,f32 x,f32 y,f32 z,f32 duration) {
    GSvec position; position.param1=x; position.param2=y; position.param3=z;
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetTargetPos(&position); return; }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,&position,duration);
}
void cameraMoveTargetOfs(u32 mode,const GSvec* position,f32 duration) { pCamWork->moving=1; pCamWork->offsetAnimation.start(&pCamWork->targetOffset,position,duration); }
void cameraMoveTargetPos(u32 mode,const GSvec* position,f32 duration) {
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetTargetPos(position); return; }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,position,duration);
}
void cameraMoveTarget(u32 mode,u32 group,u32 id,f32 duration) {
    GSvec position={0.0f,0.0f,0.0f};
    cameraSetTarget(group,id);
    GSmodel* model=(GSmodel*)GSresGetResource(group,id);
    if(model) GSmodelGetPosition(model,&position);
    if(duration < 1e-7f && duration > -1e-7f) { cameraSetTargetPos(&position); return; }
    pCamWork->moving=1; pCamWork->targetAnimation.start(&pCamWork->targetPosition,&position,duration);
}
void cameraGetRotation(GSvec* out) { copyVector(out,&pCamWork->rotation); }
void cameraSetRotation(const GSvec* value) { GScamera* camera=(GScamera*)GSresGetResource(0,0); CameraWork* work=pCamWork; work->rotation.param1=value->param1; work->rotation.param2=value->param2; work->rotation.param3=value->param3; GScameraSetRotation(camera,vec(value)); }
void cameraGetPosition(GSvec* out) { copyVector(out,&pCamWork->position); }
#pragma scheduling off
void cameraSetPosition(const GSvec* value) { CameraWork* work=pCamWork; work->position.param1=value->param1; work->position.param2=value->param2; work->position.param3=value->param3; }
#pragma scheduling reset
void cameraGetTargetPos(GSvec* out) { copyVector(out,&pCamWork->targetPosition); }
#pragma scheduling off
void cameraSetTargetPos(const GSvec* value) { CameraWork* work=pCamWork; work->targetPosition.param1=value->param1; work->targetPosition.param2=value->param2; work->targetPosition.param3=value->param3; }
#pragma scheduling reset
void cameraGetTargetOfs(GSvec* out) { copyVector(out,&pCamWork->targetOffset); }
#pragma scheduling off
void cameraSetTargetOfs(const GSvec* value) { CameraWork* work=pCamWork; work->targetOffset.param1=value->param1; work->targetOffset.param2=value->param2; work->targetOffset.param3=value->param3; }
#pragma scheduling reset
#pragma scheduling off
void cameraSetPartTargetOffset(const GSvec* value) {
    CameraWork* work=pCamWork; work->partTargetOffset.param1=value->param1; work->partTargetOffset.param2=value->param2; work->partTargetOffset.param3=value->param3;
}
#pragma scheduling reset
void cameraSetTargetExt(u32 group,u32 id,s32 part) {
    pCamWork->targetGroup=group; pCamWork->targetID=id; pCamWork->targetPart=part;
    GSvec* offset=&pCamWork->partTargetOffset; offset->param1=0.0f; offset->param2=0.0f; offset->param3=0.0f;
}
void cameraSetTarget(u32 group,u32 id) { pCamWork->targetGroup=group; pCamWork->targetID=id; pCamWork->targetPart=-1; }
GScamera* cameraGetActive() {
    GScamera* camera=GScameraGetActiveCamera();
    if(camera) return camera;
    camera=(GScamera*)GSresGetResource(0,0); GScameraSetActiveCamera(camera); return camera;
}
u8 cameraGetType() { return pCamWork->type; }
u8 cameraSetType(u8 type) {
    pCamWork->flags=0;
    if(pCamWork->type!=type) { u8 previous=pCamWork->type; pCamWork->type=type; pCamWork->flags &= ~0x20; return previous; }
    return type;
}
void cameraRefreshTargetPos() {
    if(pCamWork->targetGroup || pCamWork->targetID) {
        GSmodel* model=(GSmodel*)GSresGetResource(pCamWork->targetGroup,pCamWork->targetID);
        if(model) {
            GSmodelGetPosition(model,&pCamWork->targetPosition);
            if(pCamWork->targetPart>=0) {
                GSpart* part=GSmodelGetPart(model,pCamWork->targetPart);
                if(part) {
                    GSpartGetTransform(part,vec(&pCamWork->targetOffset),0,0);
                    PSVECSubtract(vec(&pCamWork->targetOffset),vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset));
                    PSVECAdd(vec(&pCamWork->targetOffset),vec(&pCamWork->partTargetOffset),vec(&pCamWork->targetOffset));
                    GSpartFree(part);
                }
            }
        }
    }
}
void cameraResetFloor() {
    if(pCamWork->type==6) cameraSetType(0);
    FloorCamera* floor=currentFloorCamera();
    if(floor) {
        cameraSetHeight(floor->defaultHeight); cameraSetDistance(floor->defaultDistance);
        cameraSetRotY(floor->defaultRotation); cameraSetFov(floor->defaultFov);
    }
}
void cameraSetFloorDefault(f32 height,f32 distance,f32 rotation) {
    FloorCamera* floor=currentFloorCamera();
    if(floor) {
        floor->defaultHeight=height; floor->defaultDistance=distance; floor->defaultRotation=rotation;
        if(floor->state==1) { floor->state=2; cameraSetHeight(height); cameraSetDistance(distance); cameraSetRotY(rotation); }
    }
}
void cameraSetGScamera(GScamera* camera) {
    if(camera) {
        f32 fov,aspect,nearPlane,farPlane;
        Vec distance;
        GScamera* target=(GScamera*)GSresGetResource(0,0);
        GScameraGetPerspective(camera,&fov,&aspect,&nearPlane,&farPlane);
        GScameraSetPerspective(target,fov,aspect,nearPlane,farPlane);
        GScameraGetDistanceVector(camera,&distance);
        cameraSetType(3);
        target->interest=camera->interest;
        target->position=camera->position;
        f32 rotation=(f32)atan2(distance.x,distance.z);
        f32 height=distance.y, depth=distance.z;
        FloorCamera* floor=currentFloorCamera();
        if(floor) {
            if(floor->state) { height=floor->height; depth=floor->distance; rotation=floor->rotation; }
            else {
                if(height<0.0f) height=0.0f;
                if(depth<10.0f) { depth=30.0f; height=0.0f; }
                else if(depth>500.0f) depth=500.0f;
                floor->state=1; floor->defaultHeight=height; floor->defaultDistance=depth; floor->defaultRotation=rotation; floor->defaultFov=fov;
            }
        }
        cameraSetHeight(height); cameraSetDistance(depth); cameraSetRotY(rotation); cameraSetFov(fov);
    }
}
void cameraReturn(u8 wait,f32 duration) {
    GScamera* camera=GScameraGetActiveCamera();
    if(floorFieldCameraDataExist()) {
        if(pCamWork->type==3) {
            GSvec offset=pCamWork->targetOffset;
            Vec front,position;
            GScameraGetFrontVector(camera,&front);
            PSVECScale(&front,&front,pCamWork->distance);
            GScameraGetPosition(camera,&position);
            PSVECAdd(&position,&front,&position);
            PSVECSubtract(&position,vec(&offset),&position);
            pCamWork->targetPosition.param1=position.x; pCamWork->targetPosition.param2=position.y; pCamWork->targetPosition.param3=position.z;
        }
        cameraSetType(0); floorFieldCameraEnable(); floorFieldCameraBlend(duration);
    } else {
        cameraSetType(0);
        FloorCamera* floor=currentFloorCamera();
        if(floor) { cameraSetHeight(floor->defaultHeight); cameraSetDistance(floor->defaultDistance); cameraSetFov(floor->defaultFov); }
        cameraMoveTarget(0,0,100,duration);
        GSvec rotation={0.0f,floor->defaultRotation,0.0f};
        cameraMoveRotation(0,&rotation,duration);
    }
    while((pCamWork->targetAnimation.isMove() || pCamWork->offsetAnimation.isMove() || pCamWork->positionAnimation.isMove() || pCamWork->rotationAnimation.isMove() || pCamWork->fovAnimation.isMove()) && wait) GSthreadSwitch();
}
}

static inline void interpolate(f32* out,const f32* a,const f32* b,f32 t) { f32 from=*a; *out=from+(*b-from)*t; }
static inline void interpolate(GSvec* out,const GSvec* a,const GSvec* b,f32 t) {
    Vec delta;
    PSVECSubtract(vec(b),vec(a),&delta);
    PSVECScale(&delta,&delta,t);
    PSVECAdd(vec(a),&delta,vec(out));
}
#pragma dont_inline on
template<class T> CameraAnimation<T>::CameraAnimation() { moving=0; accelerating=0; accelerateOut=0; accelerateIn=0; acceleration=0.05f; }
#pragma dont_inline off
template<class T> void CameraAnimation<T>::start(const T* from,const T* to,f32 seconds) {
    if(seconds < 1e-7f && seconds > -1e-7f) return;
    moving=1; duration=seconds; elapsed=0.0f; startPosition=*from; endPosition=*to; acceleration=0.05f; speed=0.0f; phase=0;
}
template<class T> void CameraAnimation<T>::stop() { moving=0; accelerating=0; }
template<class T> u8 CameraAnimation<T>::isMove() const { return moving; }
template<class T> u8 CameraAnimation<T>::update(f32 delta) {
    if(!moving) return 0;
    if(accelerating) return updateAcceleration(delta);
    firstUpdate=0;
    elapsed+=delta;
    f32 end, time; time=elapsed; end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    interpolate(&currentPosition,&startPosition,&endPosition,time/end);
    return 1;
}
template<class T> u8 CameraAnimation<T>::updateAcceleration(f32 delta) {
    if(!moving) return 0;
    if(firstUpdate) {
        if(!accelerateIn && accelerateOut) {
            f32 frame;
            f32 braking=0.0f;
            speed=1.0f;
            frame=1.0f/(f32)GSgfxVideoGetVsyncRate();
            if(GSgfxVideoGetLockFrameRate()==1) frame*=2.0f;
            for(f32 amount=0.0f; amount<1.0f; amount+=acceleration) braking+=frame*amount;
            brakeTime=duration-braking; phase=1;
        }
        firstUpdate=0;
    }
    elapsed+=delta*speed;
    f32 time=elapsed, end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    interpolate(&currentPosition,&startPosition,&endPosition,time/end);
    switch(phase) {
    case 0: speed+=acceleration; if(speed>=1.0f) { phase=1; brakeTime=duration-elapsed; } break;
    case 1: if(accelerateOut && elapsed>=brakeTime) phase=2; break;
    case 2: speed-=acceleration; if(speed<acceleration) speed=acceleration; break;
    }
    return 1;
}
template<class T> void CameraAnimation<T>::setAcceleration(f32 amount) { acceleration=amount; accelerating=1; accelerateOut=1; accelerateIn=1; }
template<class T> const T* CameraAnimation<T>::getCurrentPos() const { return &currentPosition; }
#pragma fp_contract off
#pragma dont_inline on
template<> u8 CameraAnimation<f32>::update(f32 delta) {
    if(!moving) return 0;
    if(accelerating) return updateAcceleration(delta);
    firstUpdate=0;
    elapsed+=delta;
    f32 time=elapsed, end=duration;
    if(time>=end) { currentPosition=endPosition; elapsed=0.0f; moving=0; accelerating=0; return 1; }
    f32 from=startPosition;
    currentPosition=(endPosition-from)*(time/end)+from;
    return 1;
}
#pragma dont_inline off
#pragma fp_contract on
#pragma dont_inline on
template class CameraAnimation<GSvec>;
template class CameraAnimation<f32>;
#pragma dont_inline off

struct FloorModuleInterface {
    u32 reserved[6];
    const char* (*name)();
    void (*save)(s32,void*,u32);
    void (*restore)(s32,void*,u32);
    s32 (*size)(s32);
    s32 (*uid)();
};
extern "C" {
FloorModuleInterface _floorModuleCamera;
void FloorModuleInterface_clear(FloorModuleInterface*);
s32 floorRegisterModule(u8,u8,FloorModuleInterface*);
extern s32 _hModuleField;
extern u8* floordata;
void* GSmemAllocClr(u32);
static const char* _cameraGetModuleName__Fv() { return "camera"; }
static s32 _cameraGetUID__Fv() { return 17; }
static s32 _cameraGetStateSize__F14FloorStateMode(s32 mode) { if(mode==1 || mode==2) return 0x274; return 0; }
static void _cameraRestoreStateData__F14FloorStateModePvUl(s32 mode,void* data,u32 size) {
    if(mode==1 || mode==2) {
        memcpy(pCamWork,data,sizeof(CameraWork));
        CameraWork* work=pCamWork;
        GScamera* camera=(GScamera*)GSresGetResource(0,0);
        if(work->type==4 || work->type==8) camera=animationCamera(work);
        if(pCamWork->flags & 8) pCamWork->flags |= 0x10;
        GScameraPopState(camera,(GScameraState*)((u8*)data+sizeof(CameraWork)));
        GScameraSetActiveCamera(camera);
    }
}
static void _cameraMakeStateData__F14FloorStateModePvUl(s32 mode,void* data,u32 size) {
    if(mode==1 || mode==2) {
        CameraWork* work=pCamWork;
        GScamera* camera=(GScamera*)GSresGetResource(0,0);
        if(work->type==4 || work->type==8) camera=animationCamera(work);
        memcpy(data,pCamWork,sizeof(CameraWork));
        GScameraPushState(camera,(GScameraState*)((u8*)data+sizeof(CameraWork)));
    }
}
void cameraInit() {
    GSvec offset={0.0f,0.0f,14.0f}, up={0.0f,1.0f,0.0f}, position={0.0f,0.0f,100.0f};
    memset(&_cameraWork,0,sizeof(CameraWork)); pCamWork=&_cameraWork;
    GScamera* camera=GScameraCreate();
    GSresRegisterResource(camera,0,0,0);
    cameraSetType(0); cameraSetTarget(0,100); cameraSetTargetOfs(&offset);
    _pFloorCamera=(FloorCamera*)GSmemAllocClr(*floordata_number*sizeof(FloorCamera));
    for(u32 i=0; i<*floordata_number; ++i) { _pFloorCamera[i].state=0; _pFloorCamera[i].floorID=*(u16*)(floordata+i*0x40+2); }
    pCamWork->offsetPosition.param1=0.0f; pCamWork->offsetPosition.param2=0.0f; pCamWork->offsetPosition.param3=0.0f;
    pCamWork->offsetRotation.param1=0.0f; pCamWork->offsetRotation.param2=0.0f; pCamWork->offsetRotation.param3=0.0f;
    pCamWork->offsetScale.param1=1.0f; pCamWork->offsetScale.param2=1.0f; pCamWork->offsetScale.param3=1.0f;
    pCamWork->fov=30.0f;
    FloorModuleInterface_clear(&_floorModuleCamera);
    _floorModuleCamera.save=_cameraMakeStateData__F14FloorStateModePvUl;
    _floorModuleCamera.restore=_cameraRestoreStateData__F14FloorStateModePvUl;
    _floorModuleCamera.size=_cameraGetStateSize__F14FloorStateMode;
    _floorModuleCamera.uid=_cameraGetUID__Fv;
    _floorModuleCamera.name=_cameraGetModuleName__Fv;
    _hModuleField=floorRegisterModule(0x80,0,&_floorModuleCamera);
    GScameraLookAt(camera,vec(&up),vec(&offset));
    GScameraSetPosition(camera,vec(&position)); GScameraSetActiveCamera(camera); GScameraLoadActiveCameraMatrix(0);
}
}

#include <game/pxdvs/GSAPI/GSinput/GSinput.hpp>
#include <game/maximum/GSAPI/baselib/quatlib.h>
extern "C" {
f32 GSgfxVideoGetLastRenderTime();
f32 timeGetLastFrameSec();
u8 dbgMenuIsOpen();
u8 floorFieldCameraGetEnabled();
u8 menuIsCheck(s32);
void menuClose(s32);
void menuOpenCustom(s32,s32,s32,s32,u8,s32);
void menuSetPosition(s32,s32,s32);
}
extern "C" f32 __float_nan[];
static inline s32 cameraFloatClass(f32 value) {
    union { f32 value; u32 bits; } number;
    number.value=value;
    switch(number.bits & 0x7f800000) {
    case 0x7f800000:
        if(number.bits & 0x7fffff) return 1;
        return 2;
    case 0:
        if(number.bits & 0x7fffff) return 5;
        return 3;
    default: return 4;
    }
}
static inline f32 cameraSqrt(f32 value) {
    if(value>0.0f) {
        f64 guess=__frsqrte(value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        guess=0.5*guess*(3.0-guess*guess*value);
        value=(f32)(value*guess);
    } else if(value<0.0) return __float_nan[0];
    else if(cameraFloatClass(value)==1) return __float_nan[0];
    return value;
}
static inline void cameraApplyLockedY(Vec* target) {
    if(pCamWork->flags & 0x10) { pCamWork->flags &= ~0x10; pCamWork->lockedTargetY=target->y; }
    else if(pCamWork->flags & 8) target->y=pCamWork->lockedTargetY;
}
static inline void cameraApplyFov(GScamera* camera) {
    f32 fov,aspect,nearPlane,farPlane;
    GScameraGetPerspective(camera,&fov,&aspect,&nearPlane,&farPlane);
    GScameraSetPerspective(camera,pCamWork->fov,aspect,nearPlane,farPlane);
}
extern "C" {
static void _cameraOffsetAnimeUpdate__FP9_GScamera(GScamera* camera) {
    GScamera* animation=animationCamera(pCamWork);
    if(animation && animation!=camera && GScameraIsAnimating(animation)) {
        if(GScameraHasAnimationEnded(animation)) return;
        f32 fov,aspect,nearPlane,farPlane;
        Vec up,target,position;
        Quaternion quaternion,inverse;
        Mtx positionMatrix,targetMatrix,upMatrix;
        GScameraGetPerspective(animation,&fov,&aspect,&nearPlane,&farPlane);
        GScameraGetLookAt(animation,&up,&target); GScameraGetPosition(animation,&position);
        up.x=0.0f; up.y=1.0f; up.z=0.0f;
        target.x*=pCamWork->offsetScale.param1; position.x*=pCamWork->offsetScale.param1;
        target.y*=pCamWork->offsetScale.param2; position.y*=pCamWork->offsetScale.param2;
        target.z*=pCamWork->offsetScale.param3; position.z*=pCamWork->offsetScale.param3;
        HSD_Quaternion rotation;
        EulerToQuat((HSD_Vec3*)&pCamWork->offsetRotation,&rotation);
        quaternion.x=rotation.x; quaternion.y=rotation.y; quaternion.z=rotation.z; quaternion.w=rotation.w;
        PSMTXQuat(positionMatrix,&quaternion); PSMTXMultVecSR(positionMatrix,&position,&position);
        PSMTXQuat(targetMatrix,&quaternion); PSMTXMultVecSR(targetMatrix,&target,&target);
        PSQUATInverse(&quaternion,&inverse);
        Quaternion inverseCopy=inverse;
        PSMTXQuat(upMatrix,&inverseCopy); PSMTXMultVecSR(upMatrix,&up,&up);
        if(pCamWork->flags & 1) { target.x*=-1.0f; up.x*=-1.0f; position.x*=-1.0f; }
        if(pCamWork->flags & 2) { target.y*=-1.0f; up.y*=-1.0f; position.y*=-1.0f; }
        if(pCamWork->flags & 4) { target.z*=-1.0f; up.z*=-1.0f; position.z*=-1.0f; }
        PSVECAdd(&position,vec(&pCamWork->offsetPosition),&position);
        PSVECAdd(&target,vec(&pCamWork->offsetPosition),&target);
        cameraApplyLockedY(&target);
        GScameraSetPerspective(camera,fov,aspect,nearPlane,farPlane);
        GScameraSetPosition(camera,&position); GScameraLookAt(camera,&up,&target);
        copyVector(&pCamWork->position,(GSvec*)&position);
        copyVector(&pCamWork->targetPosition,&pCamWork->offsetPosition);
        Vec offset;
        PSVECSubtract(&target,vec(&pCamWork->targetPosition),&offset);
        copyVector(&pCamWork->targetOffset,(GSvec*)&offset);
        PSVECSubtract(&position,&target,&position);
        pCamWork->height=position.y;
        pCamWork->distance=cameraSqrt(position.x*position.x+position.z*position.z);
        pCamWork->rotation.param2=(f32)atan2(position.x,position.z);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
    }
}
static void _cameraPadRotateUpdate__FP9_GScamera(GScamera* camera) {
    if(!dbgMenuIsOpen()) {
        s32 render=(s32)GSgfxVideoGetLastRenderTime();
        s32 horizontal=(s8)GSinputGetRightStickXData(1,1)*render;
        render=(s32)GSgfxVideoGetLastRenderTime();
        s32 vertical=(s8)GSinputGetRightStickYData(1,1)*render;
        f32 height=pCamWork->height, distance=pCamWork->distance;
        f32 angle=(f32)atan2(height,distance);
        f32 radius=cameraSqrt(height*height+distance*distance);
        if(GSinputButtonsPressed(1)&0x20) cameraSetFov((f32)vertical*0.015625f+pCamWork->fov);
        else if(GSinputButtonsPressed(1)&0x40) radius+=(f32)vertical*0.015625f;
        else angle-=(f32)vertical/4096.0f;
        pCamWork->height=radius*(f32)sin(angle);
        pCamWork->distance=radius*(f32)cos(angle);
        if(pCamWork->distance<10.0f) pCamWork->distance=10.0f;
        else if(pCamWork->distance>500.0f) pCamWork->distance=500.0f;
        cameraSetHeight(pCamWork->height); cameraSetDistance(pCamWork->distance);
        Vec displacement={0.0f,pCamWork->height,pCamWork->distance};
        pCamWork->rotation.param2+=(f32)horizontal/2048.0f;
        cameraSetRotY(pCamWork->rotation.param2);
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        Vec target;
        PSVECAdd(vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset),&target);
        PSVECAdd(&target,&displacement,vec(&pCamWork->position));
        cameraApplyLockedY(&target);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraLookAt(camera,vec(&gUpVec),&target);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera);
    }
}
static void _cameraPadMoveUpdate__FP9_GScamera(GScamera* camera) {
    f32 render=GSgfxVideoGetLastRenderTime(), divisor=64.0f;
    if(!dbgMenuIsOpen()) {
        u32 changed=GSinputButtonsChanged(1);
        if(GSinputButtonsPressed(1)&changed&0x400) {
            if(menuIsCheck(6)) menuClose(6);
            else { menuOpenCustom(6,0,0,0,1,0); menuSetPosition(6,20,260); }
        }
        Mtx matrix,yMatrix,zMatrix;
        PSMTXRotRad(matrix,'X',pCamWork->rotation.param1); PSMTXRotRad(yMatrix,'Y',pCamWork->rotation.param2); PSMTXConcat(yMatrix,matrix,matrix);
        PSMTXRotRad(zMatrix,'Z',pCamWork->rotation.param3); PSMTXConcat(zMatrix,matrix,matrix);
        f32 x=render*(f32)(s8)GSinputGetLeftStickXData(1,0), y=render*(f32)(s8)GSinputGetLeftStickYData(1,0);
        f32 rx=render*(f32)(s8)GSinputGetRightStickXData(1,0), ry=render*(f32)(s8)GSinputGetRightStickYData(1,0);
        if(GSinputButtonsPressed(1)&0x40) divisor=64.0f*4.0f;
        Vec local,world;
        if(GSinputButtonsPressed(1)&0x800) { local.z=0.0f; local.x=x/divisor; local.y=-y/divisor; }
        else { local.y=0.0f; local.x=x/divisor; local.z=y/divisor; }
        PSMTXMultVec(matrix,&local,&world); PSVECAdd(vec(&pCamWork->position),&world,vec(&pCamWork->position));
        if(GSinputButtonsPressed(1)&0x20) cameraSetFov(ry/divisor+pCamWork->fov);
        else pCamWork->rotation.param1-=ry/(32.0f*divisor);
        pCamWork->rotation.param2-=rx/(32.0f*divisor);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraSetRotation(camera,vec(&pCamWork->rotation)); cameraApplyFov(camera);
    }
}
static inline u8 cameraAnyMoving() {
    return pCamWork->targetAnimation.isMove() || pCamWork->offsetAnimation.isMove() || pCamWork->positionAnimation.isMove() || pCamWork->rotationAnimation.isMove() || pCamWork->fovAnimation.isMove();
}
void cameraUpdate() {
    GScamera* camera=(GScamera*)GSresGetResource(0,0);
    CameraWork* work=pCamWork;
    if(work->moving==1) {
        f32 delta=timeGetLastFrameSec();
        if(pCamWork->targetAnimation.update(delta)) copyVector(&pCamWork->targetPosition,pCamWork->targetAnimation.getCurrentPos());
        if(pCamWork->offsetAnimation.update(delta)) copyVector(&pCamWork->targetOffset,pCamWork->offsetAnimation.getCurrentPos());
        if(pCamWork->positionAnimation.update(delta)) copyVector(&pCamWork->position,pCamWork->positionAnimation.getCurrentPos());
        if(pCamWork->rotationAnimation.update(delta)) copyVector(&pCamWork->rotation,pCamWork->rotationAnimation.getCurrentPos());
        if(pCamWork->fovAnimation.update(delta)) pCamWork->fov=*pCamWork->fovAnimation.getCurrentPos();
        Vec distance;
        switch(pCamWork->type) {
        case 0:
        case 1:
        case 5:
            if(floorFieldCameraDataExist() && floorFieldCameraGetEnabled()) {
                PSVECAdd(vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset),&distance);
                PSVECSubtract(vec(&pCamWork->position),&distance,&distance);
                pCamWork->height=distance.y;
                pCamWork->distance=cameraSqrt(distance.x*distance.x+distance.z*distance.z);
            }
            break;
        case 6:
            break;
        case 7: {
            PSVECSubtract(vec(&pCamWork->position),vec(&pCamWork->targetPosition),&distance);
            pCamWork->height=distance.y;
            pCamWork->distance=cameraSqrt(distance.x*distance.x+distance.z*distance.z);
            if(!pCamWork->rotationAnimation.isMove() && !(pCamWork->flags&0x20)) pCamWork->rotation.param2=(f32)atan2(distance.x,distance.z);
            break;
        }
        case 8:
            break;
        }
        u8 busy;
        if(!pCamWork->targetAnimation.isMove() && !pCamWork->offsetAnimation.isMove() && !pCamWork->positionAnimation.isMove() && !pCamWork->rotationAnimation.isMove() && !pCamWork->fovAnimation.isMove()) busy=0;
        else busy=1;
        if(!busy) pCamWork->moving=0;
    } else {
        switch(work->type) {
        case 0: case 1: case 5: case 7: cameraRefreshTargetPos(); break;
        case 4:
            camera=animationCamera(work);
            if(!camera) { pCamWork->animationGroup=0; pCamWork->animationID=0; cameraSetType(pCamWork->previousType); cameraSetTarget(0,100); camera=(GScamera*)GSresGetResource(0,0); }
            break;
        case 2: case 3: case 6: case 8:
            break;
        }
    }
    switch(pCamWork->type) {
    case 0: {
        Vec distance,displacement,target;
        displacement.y=pCamWork->height; displacement.x=0.0f; displacement.z=pCamWork->distance;
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        PSVECAdd(vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset),&target); PSVECAdd(&target,&displacement,vec(&pCamWork->position));
        PSVECSubtract(vec(&pCamWork->position),&target,&distance);
        if(distance.x<0.00001f && distance.x>-0.00001f && distance.z<0.00001f && distance.z>-0.00001f) pCamWork->position.param3+=1.0f;
        cameraApplyLockedY(&target);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraLookAt(camera,vec(&gUpVec),&target);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera); break;
    }
    case 1: case 2: {
        Vec distance,target;
        PSVECAdd(vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset),&target); cameraApplyLockedY(&target);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraLookAt(camera,vec(&gUpVec),&target);
        PSVECSubtract(vec(&pCamWork->position),&target,&distance);
        pCamWork->height=distance.y; pCamWork->distance=cameraSqrt(distance.x*distance.x+distance.z*distance.z);
        pCamWork->rotation.param2=(f32)atan2(distance.x,distance.z); pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance);
        cameraApplyFov(camera); break;
    }
    case 6: _cameraPadMoveUpdate__FP9_GScamera(camera); break;
    case 5: _cameraPadRotateUpdate__FP9_GScamera(camera); break;
    case 3: {
        Vec up,target;
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraSetRotation(camera,vec(&pCamWork->rotation)); GScameraGetLookAt(camera,&up,&target);
        PSVECSubtract(&target,vec(&pCamWork->targetOffset),vec(&pCamWork->targetPosition)); cameraApplyFov(camera); break;
    }
    case 8: _cameraOffsetAnimeUpdate__FP9_GScamera(camera); GScameraLoadActiveCameraMatrix(-1); return;
    case 7: {
        Vec displacement,target;
        displacement.y=pCamWork->height; displacement.x=0.0f; displacement.z=pCamWork->distance;
        Mtx matrix;
        PSMTXRotRad(matrix,'Y',pCamWork->rotation.param2); PSMTXMultVec(matrix,&displacement,&displacement);
        PSVECAdd(vec(&pCamWork->targetPosition),&displacement,vec(&pCamWork->position));
        PSVECAdd(vec(&pCamWork->targetPosition),vec(&pCamWork->targetOffset),&target);
        PSMTXRotRad(matrix,'Z',pCamWork->offsetRotation.param3); PSMTXMultVec(matrix,vec(&gUpVec),&displacement);
        PSVECAdd(&target,vec(&pCamWork->offsetPosition),&target); cameraApplyLockedY(&target);
        GScameraSetPosition(camera,vec(&pCamWork->position)); GScameraLookAt(camera,&displacement,&target);
        pCamWork->rotation.param1=-(f32)atan2(pCamWork->height,pCamWork->distance); cameraApplyFov(camera); break;
    }
    }
    GScameraSetActiveCamera(camera); GScameraLoadActiveCameraMatrix(-1);
}
}
