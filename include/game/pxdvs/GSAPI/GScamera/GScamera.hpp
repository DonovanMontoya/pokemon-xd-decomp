#ifndef GSCAMERA_HPP
#define GSCAMERA_HPP
#include <dolphin/mtx.h>
#include <game/maximum/GSAPI/baselib/aobj.h>
struct GSgfxLayer;
struct GScameraPositionDesc { const char* className; Vec position; void* animation; };
struct GScameraDesc {
    const char* className;
    u16 flags, projectionType;
    s16 viewport[4];
    u16 scissor[4];
    GScameraPositionDesc *eye, *interest;
    f32 roll;
    void* animation;
    f32 nearPlane, farPlane, fieldOfView, aspect;
};
struct GScameraResource { GScameraDesc* descriptor; void** animations; };
struct GScamera {
    u8 inUse, lookAt, dirty, canAnimate;
    GScameraResource* resource;
    HSD_CObj* object;
    GScameraPositionDesc eyeDescriptor, interestDescriptor;
    GScameraDesc descriptor;
    Vec position, previousPosition, rotation;
    Mtx matrix, inverseMatrix;
    Vec up, interest;
    s32 animationType;
    u32 animationCount, animationIndex;
    f32 animationRate, frame, frameCount;
    u8 animationEnded;
    s8 animationDirection;
    u8 animating, clippingFlags;
};
struct GScameraState {
    u8 animating, animationEnded;
    Vec position, previousPosition, rotation;
    Mtx matrix, inverseMatrix;
    Vec up, interest;
    s32 animationType;
    u32 animationIndex;
    f32 animationRate, frame;
};
extern "C" {
void GScameraPopState(GScamera*, GScameraState*);
void GScameraPushState(GScamera*, GScameraState*);
f32 GScameraGetAnimFrame(GScamera*);
u8 GScameraHasAnimationEnded(GScamera*);
void GScameraStopAnimation(GScamera*);
void GScameraStartAnimation(GScamera*);
void GScameraSetAnimType(GScamera*, s32);
void GScameraSetAnimFrame(GScamera*, f32);
void GScameraSetAnimRate(GScamera*, f32);
void GScameraSetAnimIndex(GScamera*, u32);
u8 GScameraIsAnimating(GScamera*);
void GScameraGetDistanceVector(GScamera*, Vec*);
f32 (*GScameraGetProjMatrixPtr(GScamera*))[4];
f32 (*GScameraGetInvMatrixPtr(GScamera*))[4];
f32 (*GScameraGetMatrixPtr(GScamera*))[4];
void GScameraGetLookAt(GScamera*, Vec*, Vec*);
void GScameraLookAt(GScamera*, Vec*, Vec*);
void GScameraGetFrontVector(GScamera*, Vec*);
void GScameraGetRotation(GScamera*, Vec*);
void GScameraGetPosition(GScamera*, Vec*);
void GScameraGetPerspective(GScamera*, f32*, f32*, f32*, f32*);
void GScameraSetRotation(GScamera*, Vec*);
void GScameraSetPosition(GScamera*, Vec*);
void GScameraSetPerspective(GScamera*, f32, f32, f32, f32);
void GScameraSetScissor(GScamera*, u8, s32, s32, s32, s32);
void GScameraSetViewport(GScamera*, u8, f32, f32, f32, f32);
s32 GScameraIsValid(GScamera*);
GScamera* GScameraLoad(GScameraResource*);
GScamera* GScameraCreate();
void GScameraInit(u32);
void GScameraFree(GScamera*);
GScamera* GScameraGetActiveCamera();
void GScameraSetActiveCamera(GScamera*);
void GScameraLoadProjection(GScamera*, GSgfxLayer*);
void GScameraLoadCameraMatrix(GScamera*, s32);
void GScameraLoadActiveCameraMatrix(s32);
}
#endif
