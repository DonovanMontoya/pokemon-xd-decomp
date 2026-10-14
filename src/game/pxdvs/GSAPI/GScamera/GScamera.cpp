#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
#include <game/maximum/GSAPI/baselib/class.h>
#include <libc/string.h>
extern "C" {
void HSD_CObjReqAnim(HSD_CObj*, f32);
void HSD_CObjAnim(HSD_CObj*);
void HSD_CObjGetEyePosition(HSD_CObj*, Vec*);
void HSD_CObjGetUpVector(HSD_CObj*, Vec*);
void HSD_CObjGetInterest(HSD_CObj*, Vec*);
f32 (*HSD_CObjGetViewingMtxPtr(HSD_CObj*))[4];
void HSD_CObjGetPerspective(HSD_CObj*, f32*, f32*);
void HSD_CObjGetOrtho(HSD_CObj*, f32*, f32*, f32*, f32*);
f32 HSD_CObjGetNear(HSD_CObj*);
f32 HSD_CObjGetFar(HSD_CObj*);
void HSD_CObjSetEyePosition(HSD_CObj*, Vec*);
void HSD_CObjSetProjectionType(HSD_CObj*, u8);
void HSD_CObjSetPerspective(HSD_CObj*, f32, f32);
void HSD_CObjSetNear(HSD_CObj*, f32);
void HSD_CObjSetFar(HSD_CObj*, f32);
void HSD_CObjRemoveAnim(HSD_CObj*);
void HSD_CObjAddAnim(HSD_CObj*, void*);
HSD_CObj* HSD_CObjLoadDesc(GScameraDesc*);
u8 GSgfxVideoGetVsyncRate();
void GSgfxVideoGetEFBSize(u16*, u16*);
void* GSmemAlloc(u32);
void __assert(const char*, u32, const char*);
void GSmtx44Perspective(Mtx44, f32, f32, f32, f32);
void GSmtx44Ortho(Mtx44, f32, f32, f32, f32, f32, f32);
extern f32 __float_epsilon[];
}
static GScamera* _cameraStructList;
static u32 _cameraStructCount;
static GScamera* _activeCamera;
static GScamera* _newActiveCamera;
static f32 _frameCount;
typedef char GScameraSizeCheck[sizeof(GScamera) == 0x124 ? 1 : -1];
extern "C" {
static void cameraGetFrameCount__FP9_HSD_AObj(HSD_AObj* aobj) {
    if (!aobj) __assert("aobj.h", 172, "aobj");
    _frameCount = 1.0f + aobj->end_frame;
}
}
static void _cameraPostUpdate(f32 delta) {
    for (u32 i = 0; i < _cameraStructCount; ++i) {
        GScamera* camera = &_cameraStructList[i];
        if (camera->inUse == 1 && camera->animating == 1) {
            f32 lastFrame;
            f32 step;
            step = camera->animationRate * delta;
            s32 type = camera->animationType;
            lastFrame = camera->frameCount - 1.0f;
            if (camera->animationDirection == -1) camera->frame -= step;
            else if (camera->animationDirection == 1) camera->frame += step;
            switch (type) {
            case 0:
                if (camera->frame >= lastFrame - 0.1f) {
                    camera->animationEnded = 1;
                    camera->animationDirection = 0;
                    camera->frame = lastFrame - 0.1f;
                }
                break;
            case 1:
                if (camera->frame >= lastFrame) camera->frame -= lastFrame;
                break;
            case 2:
                if (camera->frame >= lastFrame) camera->animationDirection = -1;
                else if (camera->frame <= 0.0f) camera->animationDirection = 1;
                break;
            }
            camera->dirty = 1;
        }
    }
    if (_newActiveCamera) {
        if (_newActiveCamera->inUse) _activeCamera = _newActiveCamera;
        _newActiveCamera = 0;
    }
}
static inline f32 cameraAbs(f32 value) { return value > 0.0f ? value : -value; }
static inline void cameraUpdateMatrix(GScamera* camera) {
    Mtx zMatrix, yMatrix;
    Vec distance;
    if (camera->animating) {
        PSMTXCopy(HSD_CObjGetViewingMtxPtr(camera->object), camera->matrix);
        HSD_CObjGetEyePosition(camera->object, &camera->position);
        HSD_CObjGetUpVector(camera->object, &camera->up);
        HSD_CObjGetInterest(camera->object, &camera->interest);
    } else if (camera->lookAt == 1) {
        PSVECSubtract(&camera->position, &camera->interest, &distance);
        if (cameraAbs(distance.x) < __float_epsilon[0] &&
            cameraAbs(distance.y) < __float_epsilon[0] &&
            cameraAbs(distance.z) < __float_epsilon[0]) camera->interest.x += 0.01;
        C_MTXLookAt(camera->matrix, &camera->position, &camera->up, &camera->interest);
    } else {
        PSMTXRotRad(camera->matrix, 'X', camera->rotation.x);
        PSMTXRotRad(yMatrix, 'Y', camera->rotation.y);
        PSMTXConcat(yMatrix, camera->matrix, camera->matrix);
        PSMTXRotRad(zMatrix, 'Z', camera->rotation.z);
        PSMTXConcat(zMatrix, camera->matrix, camera->matrix);
        PSMTXTransApply(camera->matrix, camera->matrix, camera->position.x, camera->position.y, camera->position.z);
        PSMTXInverse(camera->matrix, camera->matrix);
    }
    camera->dirty = 0;
}
static void _cameraPreUpdate(f32) {
    for (u32 i = 0; i < _cameraStructCount; ++i) {
        GScamera* camera = &_cameraStructList[i];
        if (camera->inUse == 1) {
            camera->previousPosition = camera->position;
            if (camera->animating == 1) {
                HSD_CObjReqAnim(camera->object, camera->frame);
                HSD_CObjAnim(camera->object);
                HSD_CObjGetEyePosition(camera->object, &camera->position);
                HSD_CObjGetUpVector(camera->object, &camera->up);
                HSD_CObjGetInterest(camera->object, &camera->interest);
                camera->dirty = 1;
            }
            cameraUpdateMatrix(camera);
        }
    }
}
extern "C" void GScameraPopState(GScamera* camera, GScameraState* state) {
    camera->position = state->position;
    camera->previousPosition = state->previousPosition;
    camera->rotation = state->rotation;
    PSMTXCopy(state->matrix, camera->matrix);
    PSMTXCopy(state->inverseMatrix, camera->inverseMatrix);
    camera->up = state->up;
    camera->interest = state->interest;
    camera->animationEnded = state->animationEnded;
    if (!state->animationEnded && state->animating) {
        GScameraSetAnimIndex(camera, state->animationIndex);
        GScameraSetAnimType(camera, state->animationType);
        GScameraSetAnimRate(camera, state->animationRate);
        GScameraSetAnimFrame(camera, state->frame);
        GScameraStartAnimation(camera);
    }
}
extern "C" void GScameraPushState(GScamera* camera, GScameraState* state) {
    state->animating = camera->animating;
    state->position = camera->position;
    state->previousPosition = camera->previousPosition;
    state->rotation = camera->rotation;
    PSMTXCopy(camera->matrix, state->matrix);
    PSMTXCopy(camera->inverseMatrix, state->inverseMatrix);
    state->up = camera->up;
    state->interest = camera->interest;
    state->animationType = camera->animationType;
    state->animationIndex = camera->animationIndex;
    state->animationRate = camera->animationRate;
    state->frame = camera->frame;
    state->animationEnded = camera->animationEnded;
}
extern "C" f32 GScameraGetAnimFrame(GScamera* camera) { return camera->frame; }
extern "C" u8 GScameraHasAnimationEnded(GScamera* camera) { return camera->animationEnded; }
extern "C" void GScameraStopAnimation(GScamera* camera) {
    camera->animating = 0;
    camera->lookAt = 1;
    HSD_CObjGetEyePosition(camera->object, &camera->position);
    HSD_CObjGetUpVector(camera->object, &camera->up);
    HSD_CObjGetInterest(camera->object, &camera->interest);
}
extern "C" void GScameraStartAnimation(GScamera* camera) {
    if (camera->canAnimate) {
        camera->animating = 1;
        camera->animationEnded = 0;
        camera->animationDirection = 1;
        GScameraSetAnimFrame(camera, camera->frame);
    }
}
extern "C" void GScameraSetAnimType(GScamera* camera, s32 type) { camera->animationType = type; }
extern "C" void GScameraSetAnimFrame(GScamera* camera, f32 frame) {
    if (camera->canAnimate) {
        camera->frame = frame;
        HSD_ForeachAnim(camera->object, COBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, 0.0f);
        HSD_CObjReqAnim(camera->object, camera->frame);
        HSD_CObjAnim(camera->object);
        HSD_CObjGetEyePosition(camera->object, &camera->position);
        HSD_CObjGetUpVector(camera->object, &camera->up);
        HSD_CObjGetInterest(camera->object, &camera->interest);
        HSD_ForeachAnim(camera->object, COBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, camera->animationRate);
    }
}
extern "C" void GScameraSetAnimRate(GScamera* camera, f32 rate) {
    if (camera->canAnimate) {
        if (GSgfxVideoGetVsyncRate() == 50) rate *= 1.2f;
        camera->animationRate = rate;
        HSD_ForeachAnim(camera->object, COBJ_TYPE, (HSD_TypeMask)0xffff, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, camera->animationRate);
    }
}
extern "C" void GScameraSetAnimIndex(GScamera* camera, u32 index) {
    if (camera->canAnimate) {
        HSD_CObjRemoveAnim(camera->object);
        if (index <= camera->animationCount) {
            camera->animationIndex = index;
            HSD_CObjAddAnim(camera->object, camera->resource->animations[camera->animationIndex]);
            _frameCount = 0.0f;
            HSD_ForeachAnim(camera->object, COBJ_TYPE, (HSD_TypeMask)0xffff, (void*)cameraGetFrameCount__FP9_HSD_AObj, AOBJ_ARG_A);
            camera->frameCount = _frameCount;
            GScameraSetAnimFrame(camera, 0.0f);
        }
    }
}
extern "C" u8 GScameraIsAnimating(GScamera* camera) { return camera->animating; }
extern "C" void GScameraGetDistanceVector(GScamera* camera, Vec* distance) { if (distance) PSVECSubtract(&camera->position, &camera->interest, distance); }
static inline void cameraGetOrtho(GScamera* camera, f32* top, f32* bottom, f32* left, f32* right) {
    if (top && bottom && left && right) HSD_CObjGetOrtho(camera->object, top, bottom, left, right);
}
extern "C" f32 (*GScameraGetProjMatrixPtr(GScamera* camera))[4] {
    static Mtx44 projMtx;
    if (camera->object->projection_type == 1) {
        f32 fov, aspect, nearPlane, farPlane;
        GScameraGetPerspective(camera, &fov, &aspect, &nearPlane, &farPlane);
        GSmtx44Perspective(projMtx, fov, aspect, nearPlane, farPlane);
    } else {
        f32 left, top, right, bottom;
        cameraGetOrtho(camera, &top, &bottom, &left, &right);
        GSmtx44Ortho(projMtx, top, bottom, left, right, 0.1f, 2000.0f);
    }
    return projMtx;
}
extern "C" f32 (*GScameraGetInvMatrixPtr(GScamera* camera))[4] {
    if (camera->dirty) cameraUpdateMatrix(camera);
    PSMTXInverse(camera->matrix, camera->inverseMatrix);
    return camera->inverseMatrix;
}
extern "C" f32 (*GScameraGetMatrixPtr(GScamera* camera))[4] {
    if (camera->dirty) cameraUpdateMatrix(camera);
    return camera->matrix;
}
extern "C" void GScameraGetLookAt(GScamera* camera, Vec* up, Vec* interest) { if (up) *up = camera->up; if (interest) *interest = camera->interest; }
extern "C" void GScameraLookAt(GScamera* camera, Vec* up, Vec* interest) { if (up) camera->up = *up; if (interest) camera->interest = *interest; camera->dirty = 1; camera->lookAt = 1; }
extern "C" void GScameraGetFrontVector(GScamera* camera, Vec* front) {
    Vec position;
    Mtx zMatrix, yMatrix, matrix;
    if (!camera || !front) return;
    if (camera->lookAt) {
        GScameraGetPosition(camera, &position);
        PSVECSubtract(&camera->interest, &position, front);
    } else {
        front->x = 0.0f; front->y = 0.0f; front->z = -1.0f;
        PSMTXRotRad(matrix, 'X', camera->rotation.x);
        PSMTXRotRad(yMatrix, 'Y', camera->rotation.y);
        PSMTXConcat(yMatrix, matrix, matrix);
        PSMTXRotRad(zMatrix, 'Z', camera->rotation.z);
        PSMTXConcat(zMatrix, matrix, matrix);
        PSMTXMultVec(matrix, front, front);
    }
    PSVECNormalize(front, front);
}
extern "C" void GScameraGetRotation(GScamera* camera, Vec* rotation) { if (rotation) *rotation = camera->rotation; }
extern "C" void GScameraGetPosition(GScamera* camera, Vec* position) { if (position) { if (camera->animating) HSD_CObjGetEyePosition(camera->object, &camera->position); *position = camera->position; } }
extern "C" void GScameraGetPerspective(GScamera* camera, f32* fov, f32* aspect, f32* nearPlane, f32* farPlane) {
    f32 localFov, localAspect;
    HSD_CObjGetPerspective(camera->object, &localFov, &localAspect);
    if (fov) *fov = localFov;
    if (aspect) *aspect = localAspect;
    if (nearPlane) *nearPlane = HSD_CObjGetNear(camera->object);
    if (farPlane) *farPlane = HSD_CObjGetFar(camera->object);
}
extern "C" void GScameraSetRotation(GScamera* camera, Vec* rotation) { camera->rotation = *rotation; camera->dirty = 1; camera->lookAt = 0; }
extern "C" void GScameraSetPosition(GScamera* camera, Vec* position) { HSD_CObjSetEyePosition(camera->object, position); camera->position = *position; camera->dirty = 1; }
extern "C" void GScameraSetPerspective(GScamera* camera, f32 fov, f32 aspect, f32 nearPlane, f32 farPlane) {
    HSD_CObjSetProjectionType(camera->object, 1);
    HSD_CObjSetPerspective(camera->object, fov, aspect);
    HSD_CObjSetNear(camera->object, nearPlane);
    HSD_CObjSetFar(camera->object, farPlane);
    camera->dirty = 1;
}
extern "C" void GScameraSetScissor(GScamera* camera, u8 overrideClipping, s32 x, s32 y, s32 width, s32 height) {
    if (!camera || !camera->inUse) return;
    camera->object->scissor[0] = x;
    camera->object->scissor[2] = y;
    camera->object->scissor[1] = x + width;
    camera->object->scissor[3] = y + height;
    if (overrideClipping) camera->clippingFlags |= 4;
    else camera->clippingFlags &= ~4;
}
extern "C" void GScameraSetViewport(GScamera* camera, u8 overrideClipping, f32 x, f32 y, f32 width, f32 height) {
    if (!camera || !camera->inUse) return;
    camera->object->viewport[0] = x;
    camera->object->viewport[2] = y;
    camera->object->viewport[1] = 2.0f * (width - x) + x;
    camera->object->viewport[3] = 2.0f * (height - y) + y;
    if (overrideClipping) camera->clippingFlags |= 2;
    else camera->clippingFlags &= ~2;
}
extern "C" s32 GScameraIsValid(GScamera* camera) {
    if (!camera) return 0;
    if (camera->inUse != 1) return 0;
    if (!camera->object) return 0;
    GScamera* current = _cameraStructList;
    for (u32 i = 0; i < _cameraStructCount; ++i, ++current) if (current == camera) return 1;
    return 0;
}
static inline GScamera* cameraFindFree() {
    GScamera* camera = _cameraStructList;
    for (u32 i = 0; i < _cameraStructCount; ++i, ++camera) if (!camera->inUse) return camera;
    return 0;
}
extern "C" GScamera* GScameraLoad(GScameraResource* resource) {
    GScamera* camera = cameraFindFree();
    if (!camera) return 0;
    memset(camera, 0, sizeof(GScamera));
    camera->resource = resource;
    camera->object = HSD_CObjLoadDesc(camera->resource->descriptor);
    if (!camera->object) return 0;
    camera->inUse = 1;
    camera->animating = 0;
    if (camera->resource->animations) {
        camera->canAnimate = 1;
        camera->animationRate = 1.0f;
        camera->animationType = 1;
        camera->animationEnded = 0;
        camera->animationCount = 0;
        while (camera->resource->animations[camera->animationCount]) ++camera->animationCount;
        GScameraSetAnimIndex(camera, 0);
    } else camera->canAnimate = 0;
    u16 width, height;
    GSgfxVideoGetEFBSize(&width, &height);
    camera->clippingFlags = 1;
    if (camera->descriptor.viewport[0] || camera->descriptor.viewport[2] || camera->descriptor.viewport[1] != width || camera->descriptor.viewport[3] != height) camera->clippingFlags |= 2;
    if (camera->descriptor.scissor[0] || camera->descriptor.scissor[2] || camera->descriptor.scissor[1] != width || camera->descriptor.scissor[3] != height) camera->clippingFlags |= 4;
    camera->descriptor.scissor[0] = 0;
    camera->descriptor.scissor[2] = 0;
    camera->descriptor.scissor[1] = width;
    camera->descriptor.scissor[3] = height;
    camera->inUse = 1;
    camera->lookAt = 0;
    HSD_CObjGetEyePosition(camera->object, &camera->position);
    HSD_CObjGetUpVector(camera->object, &camera->up);
    HSD_CObjGetInterest(camera->object, &camera->interest);
    return camera;
}
extern "C" GScamera* GScameraCreate() {
    GScamera* camera = cameraFindFree();
    if (!camera) return 0;
    memset(camera, 0, sizeof(GScamera));
    u16 width, height;
    GSgfxVideoGetEFBSize(&width, &height);
    camera->eyeDescriptor.className = 0;
    camera->eyeDescriptor.position.x = 0.0f;
    camera->eyeDescriptor.position.y = 0.0f;
    camera->eyeDescriptor.position.z = 0.0f;
    camera->eyeDescriptor.animation = 0;
    camera->interestDescriptor.className = 0;
    camera->interestDescriptor.position.x = 0.0f;
    camera->interestDescriptor.position.y = 0.0f;
    camera->interestDescriptor.position.z = 1.0f;
    camera->interestDescriptor.animation = 0;
    camera->descriptor.className = 0;
    camera->descriptor.flags = 0;
    camera->descriptor.projectionType = 1;
    camera->descriptor.viewport[0] = 0;
    camera->descriptor.viewport[2] = 0;
    camera->descriptor.viewport[1] = width;
    camera->descriptor.viewport[3] = height;
    camera->descriptor.scissor[0] = 0;
    camera->descriptor.scissor[2] = 0;
    camera->descriptor.scissor[1] = width;
    camera->descriptor.scissor[3] = height;
    camera->descriptor.eye = &camera->eyeDescriptor;
    camera->descriptor.interest = &camera->interestDescriptor;
    camera->descriptor.roll = 0.0f;
    camera->descriptor.animation = 0;
    camera->descriptor.nearPlane = 0.1f;
    camera->descriptor.farPlane = 2000.0f;
    camera->descriptor.fieldOfView = 60.0f;
    camera->descriptor.aspect = 1.333333f;
    camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
    camera->clippingFlags = 3;
    camera->object = HSD_CObjLoadDesc(&camera->descriptor);
    if (!camera->object) return 0;
    HSD_CObjGetEyePosition(camera->object, &camera->position);
    HSD_CObjGetUpVector(camera->object, &camera->up);
    HSD_CObjGetInterest(camera->object, &camera->interest);
    camera->inUse = 1;
    camera->lookAt = 0;
    camera->animating = 0;
    camera->canAnimate = 0;
    camera->resource = 0;
    return camera;
}
struct GSgfxRenderModule { void (*callbacks[6])(f32); u32 parameter; };
extern void GSgfxRenderModuleRegister(u8, GSgfxRenderModule*, void*);
extern "C" void GScameraInit(u32 count) {
    _cameraStructCount = count;
    GSgfxRenderModule module = {{0, _cameraPreUpdate, 0, 0, _cameraPostUpdate, 0}, 0xb29a48e1};
    _cameraStructList = (GScamera*)GSmemAlloc(count * sizeof(GScamera));
    if (_cameraStructList) {
        for (u32 i = 0; i < _cameraStructCount; ++i) _cameraStructList[i].inUse = 0;
        GSgfxRenderModuleRegister(0, &module, 0);
    }
}
static inline s32 cameraUnref(HSD_CObj* object) {
    u8 release = object->parent.ref_count == 0xffff;
    if (release) return release;
    else { release = object->parent.ref_count-- == 0; return release; }
}
extern "C" void GScameraFree(GScamera* camera) {
    if (camera == _activeCamera) _activeCamera = 0;
    if (camera == _newActiveCamera) _newActiveCamera = 0;
    HSD_CObj* object = camera->object;
    if (object && cameraUnref(object)) hsdDelete(object);
    camera->inUse = 0;
}
extern "C" GScamera* GScameraGetActiveCamera() { return _activeCamera; }

extern "C" void GScameraSetActiveCamera(GScamera* camera) {
    if (camera) {
        GScamera* active = _activeCamera;
        if (!active) _activeCamera = camera;
        if (active) _newActiveCamera = camera;
        cameraUpdateMatrix(camera);
    }
}

#include <game/pxdvs/GSAPI/GScamera/GScameraLayer.hpp>
extern "C" {
GSgfxLayer* GSgfxLayerFindByID(s32);
void HSD_CObjMakeProjectionMtx(HSD_CObj*, Mtx44);
void HSD_CObjSetupViewingMtx(HSD_CObj*);
extern Mtx mtxIdent;
}
typedef char GSgfxCameraStateSizeCheck[sizeof(GSgfxCameraRenderState) == 0xb8 ? 1 : -1];
typedef char GSgfxCameraLayerSizeCheck[sizeof(GSgfxLayer) == 0x19a4 ? 1 : -1];

static inline void cameraSetLayerProjection(GSgfxLayer* layer, Mtx44 matrix, s32 type) {
    layer->projectionType = type;
    layer->projection[0] = matrix[0][0];
    layer->projection[1] = type ? matrix[0][3] : matrix[0][2];
    layer->projection[2] = matrix[1][1];
    layer->projection[3] = type ? matrix[1][3] : matrix[1][2];
    layer->projection[4] = matrix[2][2];
    layer->projection[5] = matrix[2][3];
}
static inline void cameraSetLayerPlanes(GSgfxLayer* layer, f32 nearPlane, f32 farPlane) {
    layer->nearPlane = nearPlane;
    layer->farPlane = farPlane;
    if (layer->fogEnabled) {
        if (layer->lightingEnabled) {
            layer->renderState[0].lighting |= 0x100;
            layer->renderState[1].lighting |= 0x100;
        }
        layer->renderState[0].lighting |= 0x40;
        layer->renderState[0].dirty |= 0x40;
        layer->renderState[1].lighting |= 0x40;
        layer->renderState[1].dirty |= 0x40;
    }
    layer->renderState[0].projection |= 0x20;
    layer->renderState[0].dirty |= 1;
    layer->renderState[1].projection |= 0x20;
    layer->renderState[1].dirty |= 1;
}
static inline void cameraResetLayerMatrix(GSgfxLayer* layer) {
    GSgfxCameraMatrixStack* stack = layer->matrixStack;
    memcpy(stack->top->matrix, mtxIdent, sizeof(Mtx));
    stack->top->dirty |= 1;
}
static inline void cameraConcatLayerMatrix(GSgfxLayer* layer, Mtx matrix) {
    GSgfxCameraMatrixStack* stack = layer->matrixStack;
    PSMTXConcat(stack->top->matrix, matrix, stack->top->matrix);
    stack->top->dirty |= 1;
}
// GQR3 holds the SDK signed-16 conversion format.
static inline f32 cameraSigned16ToFloat(register const s16* address) {
    register f32 value;
    asm { psq_l value, 0(address), 1, 3 }
    return value;
}
static inline void cameraMarkViewport(GSgfxLayer* layer, u32 flags) {
    layer->renderState[0].clipping |= flags;
    layer->renderState[0].dirty |= 2;
    layer->renderState[1].clipping |= flags;
    layer->renderState[1].dirty |= 2;
}
extern "C" {
static void _cameraLoadClipping__FP9_GScameraP10GSgfxLayer(GScamera* camera, GSgfxLayer* layer) {
    if (camera->clippingFlags & 1) {
        if (camera->clippingFlags & 2) {
            HSD_CObj* object = camera->object;
            f32 left = object->viewport[0];
            f32 top = object->viewport[2];
            layer->viewport[0] = left;
            layer->viewport[1] = top;
            layer->viewport[2] = 0.5f * (object->viewport[1] - left) + left;
            layer->viewport[3] = 0.5f * (object->viewport[3] - top) + top;
            cameraMarkViewport(layer, 0x10);
        } else {
            u16 width, height;
            GSgfxVideoGetEFBSize(&width, &height);
            s16 halfWidth = width >> 1;
            s16 halfHeight = height >> 1;
            layer->viewport[0] = 0.0f;
            layer->viewport[1] = 0.0f;
            layer->viewport[2] = cameraSigned16ToFloat(&halfWidth);
            layer->viewport[3] = cameraSigned16ToFloat(&halfHeight);
            cameraMarkViewport(layer, 0x10);
        }
        if (camera->clippingFlags & 4) {
            HSD_CObj* object = camera->object;
            u16 top = object->scissor[2];
            u16 left = object->scissor[0];
            layer->scissor[0] = left;
            layer->scissor[1] = top;
            layer->scissor[2] = object->scissor[1] - left;
            layer->scissor[3] = object->scissor[3] - top;
            cameraMarkViewport(layer, 1);
            return;
        }
        layer->scissor[0] = 0;
        layer->scissor[1] = 0;
        GSgfxVideoGetEFBSize(&layer->scissor[2], &layer->scissor[3]);
        cameraMarkViewport(layer, 1);
    }
}
static void _cameraLoadCameraMatrix__FP9_GScamera12GSgfxLayerID(GScamera* camera, s32 layerID) {
    GSgfxLayer* layer = layerID == -1 ? 0 : GSgfxLayerFindByID(layerID);
    f32 fov, aspect, nearPlane, farPlane;
    if (camera->animating) {
        HSD_CObj* object = camera->object;
        if (!object) __assert("cobj.h", 426, "cobj");
        object->flags &= ~2;
        PSMTXCopy(HSD_CObjGetViewingMtxPtr(camera->object), camera->matrix);
        HSD_CObjGetEyePosition(camera->object, &camera->position);
        HSD_CObjGetUpVector(camera->object, &camera->up);
        HSD_CObjGetInterest(camera->object, &camera->interest);
        if (layer) {
            Mtx44 projection;
            GScameraGetPerspective(camera, &fov, &aspect, &nearPlane, &farPlane);
            GSmtx44Perspective(projection, fov, aspect, nearPlane, farPlane);
            cameraSetLayerProjection(layer, projection, 0);
            cameraSetLayerPlanes(layer, nearPlane, farPlane);
            cameraResetLayerMatrix(layer);
            cameraConcatLayerMatrix(layer, camera->matrix);
        }
    } else if (camera->object->projection_type == 1) {
        GScameraGetMatrixPtr(camera);
        HSD_CObj* object = camera->object;
        if (!object) __assert("cobj.h", 414, "cobj");
        object->flags |= 0x80000002;
        PSMTXCopy(camera->matrix, object->view_mtx);
        if (layer) {
            Mtx44 projection;
            GScameraGetPerspective(camera, &fov, &aspect, &nearPlane, &farPlane);
            GSmtx44Perspective(projection, fov, aspect, nearPlane, farPlane);
            cameraSetLayerProjection(layer, projection, 0);
            cameraSetLayerPlanes(layer, nearPlane, farPlane);
            cameraResetLayerMatrix(layer);
            cameraConcatLayerMatrix(layer, camera->matrix);
        }
    } else if (layer) {
        Mtx44 projection;
        cameraGetOrtho(camera, &aspect, &farPlane, &fov, &nearPlane);
        GSmtx44Ortho(projection, aspect, farPlane, fov, nearPlane, 0.0f, -30000.0f);
        cameraSetLayerProjection(layer, projection, 1);
        cameraResetLayerMatrix(layer);
        cameraSetLayerPlanes(layer, 0.0f, 30000.0f);
        cameraResetLayerMatrix(layer);
    }
    if (layer) _cameraLoadClipping__FP9_GScameraP10GSgfxLayer(camera, layer);
}
void GScameraLoadCameraMatrix(GScamera* camera, s32 layerID) {
    if (!camera) {
        if (_activeCamera) _cameraLoadCameraMatrix__FP9_GScamera12GSgfxLayerID(_activeCamera, layerID);
    } else _cameraLoadCameraMatrix__FP9_GScamera12GSgfxLayerID(camera, layerID);
}
void GScameraLoadActiveCameraMatrix(s32 layerID) {
    if (_activeCamera) _cameraLoadCameraMatrix__FP9_GScamera12GSgfxLayerID(_activeCamera, layerID);
}
void GScameraLoadProjection(GScamera* camera, GSgfxLayer* layer) {
    if (camera) {
        HSD_CObj* object = camera->object;
        if (object) {
            Mtx44 projection;
            GScameraLoadCameraMatrix(camera, layer->id);
            HSD_CObjMakeProjectionMtx(object, projection);
            HSD_CObjSetupViewingMtx(object);
        }
    }
}
}
