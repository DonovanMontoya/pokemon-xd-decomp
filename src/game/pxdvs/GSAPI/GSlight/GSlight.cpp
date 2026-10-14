#include <game/pxdvs/GSAPI/GSlight/GSlight.hpp>
#include <game/maximum/GSAPI/baselib/class.h>
#include <libc/string.h>

extern "C" {
void HSD_LObjDeleteCurrentAll(HSD_LObj*);
void HSD_LObjAddCurrentAll(HSD_LObj*);
void HSD_LObjSetupInit(HSD_CObj*);
void HSD_LObjReqAnimAll(HSD_LObj*, f32);
void HSD_LObjAnimAll(HSD_LObj*);
void HSD_LObjReqAnim(HSD_LObj*, f32);
void HSD_LObjAnim(HSD_LObj*);
void HSD_LObjRemoveAnimAll(HSD_LObj*);
void HSD_LObjAddAnimAll(HSD_LObj*, void*);
void HSD_LObjGetInterest(HSD_LObj*, HSD_Vec3*);
s32 HSD_LObjGetPosition(HSD_LObj*, HSD_Vec3*);
void HSD_LObjSetInterest(HSD_LObj*, HSD_Vec3*);
void HSD_LObjSetPosition(HSD_LObj*, HSD_Vec3*);
u32 HSD_LObjGetFlags(HSD_LObj*);
void HSD_LObjSetFlags(HSD_LObj*, u32);
void HSD_LObjClearFlags(HSD_LObj*, u32);
void HSD_LObjGetColor(HSD_LObj*, GXColor*);
void HSD_LObjSetColor(HSD_LObj*, GXColor);
u8 GSgfxVideoGetVsyncRate();
void __assert(const char*, u32, const char*);
void* GSmemAlloc(u32);
HSD_LObj* HSD_LObjLoadDesc(void*);
}

static GSlight* _lightStructList;
static u32 _lightStructCount;
static f32 _frameCount;
typedef char GSlightSizeCheck[sizeof(GSlight) == 0x74 ? 1 : -1];

extern "C" {
static void lightGetFrameCount__FP9_HSD_AObj(HSD_AObj* aobj) {
    if (!aobj) __assert("aobj.h", 172, "aobj");
    _frameCount = 1.0f + aobj->end_frame;
}
}

extern "C" void GSlightDeleteCurrentAll() { HSD_LObjDeleteCurrentAll(0); }

static inline s32 lightFindActiveIndex() {
    GSlight* light = _lightStructList;
    for (s32 i = 0; i < _lightStructCount; ++light, ++i) {
        if (light->inUse == 1 && light->active) return i;
    }
    return -1;
}

extern "C" void GSlightSetupLights(HSD_CObj* camera) {
    HSD_LObjDeleteCurrentAll(0);
    s32 first = lightFindActiveIndex();
    if (first != -1) {
        GSlight* previous;
        u32 i;
        GSlight* light;
        previous = &_lightStructList[first];
        for (i = first + 1; i < _lightStructCount; ++i) {
            light = &_lightStructList[i];
            if (light->inUse == 1 && light->active) {
                previous->object->next = light->object;
                previous = light;
            }
        }
        previous->object->next = 0;
        HSD_LObjAddCurrentAll(_lightStructList[first].object);
    }
    HSD_LObjSetupInit(camera);
}

static void _lightPostUpdate(f32 delta) {
    for (u32 i = 0; i < _lightStructCount; ++i) {
        GSlight* light = &_lightStructList[i];
        if (light->inUse == 1 && light->animating == 1) {
            f32 lastFrame;
            f32 step;
            step = light->animationRate * delta;
            s32 type = light->animationType;
            lastFrame = light->frameCount - 1.0f;
            if (light->animationDirection == -1) light->frame -= step;
            else if (light->animationDirection == 1) light->frame += step;
            switch (type) {
            case 0:
                if (light->frame >= lastFrame - 0.1f) {
                    light->animationEnded = 1;
                    light->animationDirection = 0;
                    light->frame = lastFrame - 0.1f;
                }
                break;
            case 1:
                if (light->frame >= lastFrame) light->frame -= lastFrame;
                break;
            case 2:
                if (light->frame >= lastFrame) light->animationDirection = -1;
                else if (light->frame <= 0.0f) light->animationDirection = 1;
                break;
            }
        }
    }
}

static void _lightPreUpdate(f32) {
    for (u32 i = 0; i < _lightStructCount; ++i) {
        GSlight* light = &_lightStructList[i];
        if (light->inUse == 1 && light->animating == 1) {
            HSD_LObjReqAnimAll(light->object, light->frame);
            HSD_LObjAnimAll(light->object);
        }
    }
}

extern "C" void GSlightPopState(GSlight* light, GSlightState* state) {
    state->active = light->active;
    GSlightSetPosition(light, &state->position);
    switch (GSlightGetType(light)) {
    case 2: case 3: GSlightSetTarget(light, &state->interest); break;
    }
    GSlightSetAnimIndex(light, state->animationIndex);
    GSlightSetAnimFrame(light, state->frame);
    GSlightSetAnimRate(light, state->animationRate);
    GSlightSetAnimType(light, state->animationType);
    light->animationEnded = state->animationEnded;
    light->animationDirection = state->animationDirection;
    if (light->animating) GSlightStartAnimation(light);
}

extern "C" void GSlightPushState(GSlight* light, GSlightState* state) {
    state->active = light->active;
    state->animating = light->animating;
    HSD_LObjGetPosition(light->object, &state->position);
    HSD_LObjGetInterest(light->object, &state->interest);
    state->animationIndex = light->animationIndex;
    state->frame = light->frame;
    state->animationRate = light->animationRate;
    state->animationType = light->animationType;
    state->animationEnded = light->animationEnded;
    state->animationDirection = light->animationDirection;
}

extern "C" u8 GSlightHasAnimationEnded(GSlight* light) { return light->animationEnded; }
extern "C" void GSlightStopAnimation(GSlight* light) { light->animating = 0; }
extern "C" void GSlightStartAnimation(GSlight* light) {
    if (light->canAnimate) {
        light->animating = 1;
        light->animationEnded = 0;
        light->animationDirection = 1;
    }
}
extern "C" void GSlightSetAnimType(GSlight* light, s32 type) { light->animationType = type; }
extern "C" void GSlightSetAnimFrame(GSlight* light, f32 frame) {
    if (light->canAnimate) {
        light->frame = frame;
        HSD_ForeachAnim(light->object, LOBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, 0.0f);
        HSD_LObjReqAnim(light->object, light->frame);
        HSD_LObjAnim(light->object);
        HSD_ForeachAnim(light->object, LOBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, light->animationRate);
    }
}
extern "C" void GSlightSetAnimRate(GSlight* light, f32 rate) {
    if (light->canAnimate) {
        if (GSgfxVideoGetVsyncRate() == 50) rate *= 1.2f;
        light->animationRate = rate;
        HSD_ForeachAnim(light->object, LOBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, light->animationRate);
    }
}
extern "C" void GSlightSetAnimIndex(GSlight* light, u32 index) {
    if (light->canAnimate) {
        HSD_LObjRemoveAnimAll(light->object);
        if (index <= light->animationCount) {
            light->animationIndex = index;
            HSD_LObjAddAnimAll(light->object, light->resource->animations[light->animationIndex]);
            HSD_LObjReqAnimAll(light->object, 0.0f);
            _frameCount = 0.0f;
            HSD_ForeachAnim(light->object, LOBJ_TYPE, (HSD_TypeMask)0xffff, (void*)lightGetFrameCount__FP9_HSD_AObj, AOBJ_ARG_A);
            light->frameCount = _frameCount;
            GSlightSetAnimFrame(light, 0.0f);
        }
    }
}
extern "C" u8 GSlightCanAnimate(GSlight* light) { return light->canAnimate; }
extern "C" u8 GSlightGetActive(GSlight* light) { return light->active; }
extern "C" void GSlightGetTarget(GSlight* light, HSD_Vec3* target) { HSD_LObjGetInterest(light->object, target); }
extern "C" s32 GSlightGetPosition(GSlight* light, HSD_Vec3* position) { return HSD_LObjGetPosition(light->object, position) != 0; }
extern "C" s32 GSlightGetType(GSlight* light) {
    switch (HSD_LObjGetFlags(light->object) & 3) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    default: return 0xff;
    }
}
extern "C" void GSlightGetColor(GSlight* light, GXColor* color) { if (color) HSD_LObjGetColor(light->object, color); }
extern "C" void GSlightSetActive(GSlight* light, u8 active) { light->active = active; }
extern "C" void GSlightSetTarget(GSlight* light, HSD_Vec3* target) { HSD_LObjSetInterest(light->object, target); }
extern "C" void GSlightSetPosition(GSlight* light, HSD_Vec3* position) { HSD_LObjSetPosition(light->object, position); }
static inline GXColor lightCopyColor(GXColor* color) {
    GXColor copy;
    copy.r = color->r;
    copy.g = color->g;
    copy.b = color->b;
    copy.a = color->a;
    return copy;
}
extern "C" void GSlightSetColor(GSlight* light, GXColor* color) {
    GXColor copy = lightCopyColor(color);
    HSD_LObjSetColor(light->object, copy);
}
extern "C" void GSlightSetType(GSlight* light, s32 type) {
    HSD_LObjClearFlags(light->object, 3);
    switch (type) {
    case 0: HSD_LObjSetFlags(light->object, 0); break;
    case 1: HSD_LObjSetFlags(light->object, 1); break;
    case 2: HSD_LObjSetFlags(light->object, 2); break;
    case 3: HSD_LObjSetFlags(light->object, 3); break;
    }
    light->type = type;
}
static inline s32 lightUnref(HSD_LObj* object) {
    u8 release = object->parent.ref_count == 0xffff;
    if (release) return release;
    else {
        release = object->parent.ref_count-- == 0;
        return release;
    }
}
extern "C" void GSlightFree(GSlight* light) {
    HSD_LObj* object = light->object;
    if (object) {
        if (lightUnref(object)) hsdDelete(object);
    }
    light->active = 0;
    light->inUse = 0;
}


static inline GSlight* lightFindFree() {
    GSlight* light = _lightStructList;
    for (u32 i = 0; i < _lightStructCount; ++i, ++light) {
        if (!light->inUse) return light;
    }
    return 0;
}

extern "C" GSlight* GSlightLoad(GSlightResource* resource) {
    GSlight* light = lightFindFree();
    if (!light) return 0;
    memset(light, 0, sizeof(GSlight));
    light->resource = resource;
    light->object = HSD_LObjLoadDesc(light->resource->descriptor);
    light->inUse = 1;
    light->active = 0;
    light->animating = 0;
    if (light->resource->animations) {
        light->canAnimate = 1;
        light->animationRate = 1.0f;
        light->animationType = 1;
        light->animationEnded = 0;
        light->animationCount = 0;
        while (light->resource->animations[light->animationCount]) ++light->animationCount;
        GSlightSetAnimIndex(light, 0);
    } else {
        light->canAnimate = 0;
    }
    return light;
}

extern "C" GSlight* GSlightCreate() {
    GSlight* light = lightFindFree();
    if (!light) return 0;
    memset(light, 0, sizeof(GSlight));
    light->positionDescriptor.className = 0;
    light->positionDescriptor.position.x = 0.0f;
    light->positionDescriptor.position.y = 0.0f;
    light->positionDescriptor.position.z = 0.0f;
    light->positionDescriptor.animation = 0;
    light->interestDescriptor.className = 0;
    light->interestDescriptor.position.x = 0.0f;
    light->interestDescriptor.position.y = 0.0f;
    light->interestDescriptor.position.z = 0.0f;
    light->interestDescriptor.animation = 0;
    light->shininess = 16.0f;
    light->lightDescriptor.className = 0;
    light->lightDescriptor.next = 0;
    light->lightDescriptor.flags = 4;
    light->lightDescriptor.priority = 0;
    light->lightDescriptor.color.r = 128;
    light->lightDescriptor.color.g = 128;
    light->lightDescriptor.color.b = 128;
    light->lightDescriptor.color.a = 0;
    light->lightDescriptor.position = &light->positionDescriptor;
    light->lightDescriptor.interest = &light->interestDescriptor;
    light->lightDescriptor.shininess = &light->shininess;
    light->object = HSD_LObjLoadDesc(&light->lightDescriptor);
    light->inUse = 1;
    light->active = 0;
    return light;
}

struct GSgfxRenderModule {
    void (*callbacks[6])(f32);
    u32 parameter;
};
extern void GSgfxRenderModuleRegister(u8, GSgfxRenderModule*, void*);

extern "C" void GSlightInit(u32 count) {
    _lightStructCount = count;
    GSgfxRenderModule module = { {0, _lightPreUpdate, 0, 0, _lightPostUpdate, 0}, 0xb29a48e1 };
    _lightStructList = (GSlight*)GSmemAlloc(count * sizeof(GSlight));
    if (_lightStructList) {
        for (u32 i = 0; i < _lightStructCount; ++i) _lightStructList[i].inUse = 0;
        GSgfxRenderModuleRegister(4, &module, 0);
    }
}
