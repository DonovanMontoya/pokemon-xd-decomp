#ifndef GSLIGHT_HPP
#define GSLIGHT_HPP
#include <dolphin/types.h>
#include <dolphin/gx.h>
#include <game/maximum/GSAPI/baselib/aobj.h>

struct GSlightResource {
    void* descriptor;
    void** animations;
};

struct GSlightPositionDescriptor {
    const char* className;
    HSD_Vec3 position;
    void* animation;
};
struct GSlightDescriptor {
    const char* className;
    void* next;
    u16 flags, priority;
    GXColor color;
    GSlightPositionDescriptor *position, *interest;
    f32* shininess;
};

struct GSlight {
    u8 inUse, active, canAnimate, animating;
    s32 type;
    GSlightResource* resource;
    HSD_LObj* object;
    GSlightPositionDescriptor positionDescriptor, interestDescriptor;
    GSlightDescriptor lightDescriptor;
    f32 shininess;
    u32 animationCount;
    s32 animationType;
    u32 animationIndex;
    f32 animationRate, frame, frameCount;
    u8 animationEnded;
    s8 animationDirection;
    u8 reserved[2];
};

struct GSlightState {
    u8 active, animating, animationEnded;
    s8 animationDirection;
    HSD_Vec3 position, interest;
    u32 animationIndex;
    f32 frame, animationRate;
    s32 animationType;
};

extern "C" {
void GSlightDeleteCurrentAll();
void GSlightSetupLights(HSD_CObj*);
void GSlightPushState(GSlight*, GSlightState*);
void GSlightPopState(GSlight*, GSlightState*);
u8 GSlightHasAnimationEnded(GSlight*);
void GSlightStopAnimation(GSlight*);
void GSlightStartAnimation(GSlight*);
void GSlightSetAnimType(GSlight*, s32);
void GSlightSetAnimFrame(GSlight*, f32);
void GSlightSetAnimRate(GSlight*, f32);
void GSlightSetAnimIndex(GSlight*, u32);
u8 GSlightCanAnimate(GSlight*);
u8 GSlightGetActive(GSlight*);
void GSlightGetTarget(GSlight*, HSD_Vec3*);
s32 GSlightGetPosition(GSlight*, HSD_Vec3*);
s32 GSlightGetType(GSlight*);
void GSlightGetColor(GSlight*, GXColor*);
void GSlightSetActive(GSlight*, u8);
void GSlightSetTarget(GSlight*, HSD_Vec3*);
void GSlightSetPosition(GSlight*, HSD_Vec3*);
void GSlightSetColor(GSlight*, GXColor*);
void GSlightSetType(GSlight*, s32);
void GSlightFree(GSlight*);
GSlight* GSlightLoad(GSlightResource*);
GSlight* GSlightCreate();
void GSlightInit(u32);
}
#endif
