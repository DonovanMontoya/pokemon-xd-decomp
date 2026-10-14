#include <game/pxdvs/GSAPI/GSmodel/runtime.hpp>
#include <game/pxdvs/GSAPI/GSlight/GSlight.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
struct HSD_Shadow { void* camera; u32 flags; HSD_TObj* texture; };
struct GSmodelShadowReceiver {
    GSmodel* model;
    u8 reserved04[0x4c];
    u8 active, reserved51;
    u16 token;
    HSD_Shadow* shadow;
};
extern "C" {
static GSmodelShadowReceiver _modelShadowReceiveList[5];
static f32 _modelShadowMarukageDist = 350.0f, _modelShadowOffDist = 400.0f;
s32 modelShadowLayerID = -1;
static u8 _modelShadowIntensity;
static s32 _modelShadowXsize, _modelShadowYsize;
static f32 _modelShadowCutoffDist, _modelShadowBoundExpansion;
static u32 _modelShadowLayerUseCount, _modelShadowActiveCount;
static GStexture* _modelShadowMarukageTex;
static u8 _shadowCheckCameraHeight;
void GSgfxRenderWaitForDrawComplete__Fv();
void HSD_ShadowFreeTexture(HSD_Shadow*);
void HSD_ShadowSetActive(HSD_Shadow*, u8);
HSD_Shadow* HSD_ShadowAlloc();
void HSD_ShadowSetDebug(u8);
void* GSmemAlloc(u32);
void GSmemFree(void*);
void* memcpy(void*, const void*, unsigned long);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32);
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char*, u32, u32, u32, s32, bool, bool, bool, s32, s32);
void HSD_JObjWalkTree(HSD_JObj*, void (*)(HSD_JObj*, void**, s32), void**);
void GSmodelSetShadowToCameraHeightCheck(u8 enable) { _shadowCheckCameraHeight = enable; }
void GSmodelSetGroundPlane(GSmodel* model, f32 height, u8 enable) {
    modelRuntime(model)->groundPlane = height;
    if (enable) model->animationFlags |= 4;
    else model->animationFlags &= ~4;
}
void GSmodelSetMarukageTexture(GStexture* texture) { _modelShadowMarukageTex = texture; GStextureSetFilter(texture, 2, 2, 0); }
void GSmodelSetShadowDistLimits(f32 nearDistance, f32 farDistance) { _modelShadowMarukageDist = nearDistance; _modelShadowOffDist = farDistance; }
void GSmodelFreeAllShadowTextures() {
    GSmodelShadowReceiver* receiver = _modelShadowReceiveList;
    for (u32 i = 0; i < 5; ++i, ++receiver) {
        HSD_Shadow* shadow = receiver->shadow;
        u8 hasTexture = 0;
        if (shadow && shadow->texture && shadow->texture->imagedesc && *(void**)shadow->texture->imagedesc) hasTexture = 1;
        if (hasTexture) { GSgfxRenderWaitForDrawComplete__Fv(); HSD_ShadowFreeTexture(receiver->shadow); }
        HSD_ShadowSetActive(receiver->shadow, 0); receiver->active = 0;
    }
}
void GSmodelSetShadowBoundExpansion(f32 value) { _modelShadowBoundExpansion = value; }
void GSmodelSetShadowCutoffDist(f32 value) { _modelShadowCutoffDist = value * value; }
void GSmodelSetShadowDebug(u8 enable) { HSD_ShadowSetDebug(enable); }
void GSmodelSetShadowTextureSize(s32 width, s32 height) {
    if (width & 1) ++width;
    if (height & 1) ++height;
    if (width >= 2 && height >= 2) {
        if (width > 640) width = 640;
        if (height > 528) height = 528;
        _modelShadowXsize = width; _modelShadowYsize = height;
    }
}
void GSmodelSetShadowLight(GSmodel* model, GSlight* light) {
    if (light && !(light->object->flags & 3)) light = 0;
    modelRuntime(model)->shadowLight = light;
}
void GSmodelSetShadowSurface(GSmodel* model, s32 count, GSmodel** surfaces) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if (count >= 0 && count <= 8) {
        if (count == 0 || !surfaces) {
            if (runtime->shadowSurfaces) {
                GSmemFree(runtime->shadowSurfaces); runtime->shadowSurfaceCount = 0; runtime->shadowSurfaces = 0;
                if (--_modelShadowLayerUseCount == 0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(modelShadowLayerID); modelShadowLayerID = -1; }
            }
        } else {
            if (!runtime->shadowSurfaces) {
                runtime->shadowSurfaces = (GSmodel**)GSmemAlloc(0x20); runtime->shadowSurfaceCount = 0;
                if (!_modelShadowLayerUseCount) modelShadowLayerID = Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset("model shadow", 0, 0x40000, 4, 0, false, false, false, -1, 3);
                ++_modelShadowLayerUseCount;
            }
            runtime->shadowSurfaceCount = count;
            memcpy(runtime->shadowSurfaces, surfaces, runtime->shadowSurfaceCount * 4);
        }
    }
}
void GSmodelClearShadowFlags(GSmodel* model, u32 flags) {
    if (flags & 1) model->flags &= ~0x10000000;
    if (flags & 4) model->flags &= ~0x40000000;
}
void GSmodelSetShadowFlags(GSmodel* model, u32 flags) {
    if (flags & 1) model->flags |= 0x10000000;
    if (flags & 4) model->flags |= 0x40000000;
}
static void _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi(HSD_JObj* joint, void** context, s32) {
    if (!(joint->flags & 0x4020)) {
        for (HSD_DObj* object = joint->u.dobj; object; object = object->next) {
            if (object->mobj) {
                if (context != 0) object->mobj->rendermode |= 0x4000000;
                else object->mobj->rendermode &= ~0x4000000;
            }
        }
    }
}
void modelShadowPrepare__FP8_GSmodelb(GSmodel* model, bool enable) {
    u8 found = 0;
    for (u32 i = 0; i < 5; ++i) if (_modelShadowReceiveList[i].model == model) { found = 1; break; }
    if (found) {
        HSD_JObj* joint = modelGetRenderJObj__FP8_GSmodel(model);
        if (!enable) HSD_JObjWalkTree(joint, _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi, (void**)0);
        else HSD_JObjWalkTree(joint, _modelShadowSetShadowFlag__FP9_HSD_JObjPPvi, (void**)1);
        GSmodelShadowReceiver* receiver = _modelShadowReceiveList;
        for (u32 i = 0; i < 5; ++i, ++receiver) if (receiver->active && receiver->model == model) HSD_ShadowSetActive(receiver->shadow, enable);
    }
}
void modelShadowFreeModelList__FP8_GSmodel(GSmodel* model) {
    GSmodelRuntime* runtime = modelRuntime(model);
    if (runtime->shadowSurfaces) {
        GSmemFree(runtime->shadowSurfaces); runtime->shadowSurfaceCount = 0; runtime->shadowSurfaces = 0;
        if (--_modelShadowLayerUseCount == 0) { Remove__16GSgfxLayerConfigF12GSgfxLayerID(modelShadowLayerID); modelShadowLayerID = -1; }
    }
}
void modelShadowInit__Fv() {
    GSmodelShadowReceiver* receiver = _modelShadowReceiveList;
    _modelShadowIntensity = 128; _modelShadowXsize = 384; _modelShadowYsize = 384;
    _modelShadowCutoffDist = 0.0f; _modelShadowBoundExpansion = 0.0f;
    for (u32 i = 0; i < 5; ++i, ++receiver) {
        receiver->active = 0; receiver->shadow = HSD_ShadowAlloc(); HSD_ShadowSetActive(receiver->shadow, 0);
        receiver->model = 0; receiver->token = 0;
    }
}
}
