#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <dolphin/mtx.h>
extern "C" {
extern GSmodel* _modelTopPtr;
u32 GSgfxPerfbarCPUEntry(u32);
void GSparticleDestroyAllGenerators(GSparticleBank*, u8);
void GSparticleSetBankVisibility(GSparticleBank*, u8);
}
extern "C" void GSmodelIterateList(void (*callback)(GSmodel*, void*), void* context) {
    for (GSmodel* model = _modelTopPtr; model; model = model->next) callback(model, context);
}
extern "C" GSmodel* GSmodelSearchModelList(HSD_JObj* joint) {
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        HSD_JObj* render = (model->flags & 0x80) ? model->blendJoint : model->joint;
        if (render == joint) return model;
    }
    return 0;
}
extern "C" void GSmodelSetRenderCamera(GSmodel* model, GScamera* camera) { model->camera = camera; }
extern "C" void GSmodelSetRenderLayer(GSmodel* model, s32 count, const s32* layers) {
    for (s32 i = 0; i < 8; ++i) { if (i < count) model->renderLayers[i] = layers[i]; else model->renderLayers[i] = 255; }
}
extern "C" void GSmodelDestroyLinkedParticles(GSmodel* model) { if (model->particleBank) GSparticleDestroyAllGenerators(model->particleBank, 1); }
extern "C" s32 GSmodelGetGSparticleLinkAttachMode(GSmodel* model) { return model->particleAttachMode; }
extern "C" GSparticleBank* GSmodelGetLinkedGSparticleBank(GSmodel* model) { return model->particleBank; }
extern "C" void GSmodelSetGSparticleLinkAttachMode(GSmodel* model, s32 mode) { model->particleAttachMode = mode; }
extern "C" void GSmodelLinkToGSparticleBank(GSmodel* model, GSparticleBank* bank) {
    if (model->particleBank != bank) {
        model->particleBank = bank;
        if (model->particleBank) {
            model->animationFlags |= 8;
            GSmodelSetAnimFrame(model, model->animationFrame);
            GSmodelForceAnimTransformUpdate(model);
        } else model->animationFlags &= ~8;
    }
}
extern "C" GSbound* GSmodelGetBound(GSmodel* model) { return (GSbound*)model->boundStorage; }
extern "C" void GSmodelSetBoundCheck(GSmodel* model, u8 enable) { if (enable) model->flags |= 0x100000; else model->flags &= ~0x100000; }
extern "C" void GSmodelSetFogState(GSmodel* model, u8 first, u8 second) {
    if (first) model->flags |= 0x1000000; else model->flags &= ~0x1000000;
    if (second) model->flags |= 0x2000000; else model->flags &= ~0x2000000;
}
extern "C" void GSmodelUpdate(GSmodel* model) {
    u32 perf = GSgfxPerfbarCPUEntry(0xff0000);
    modelUpdateAttachments__FP8_GSmodel(model); modelUpdateTransform__FP8_GSmodel(model);
    GSgfxPerfbarCPUEntry(perf);
}
extern "C" u8 GSmodelGetVisibility(GSmodel* model) { return (model->flags >> 1) & 1; }
extern "C" void GSmodelSetVisibility(GSmodel* model, u8 visible) {
    if (visible) { model->flags |= 2; if (model->particleBank) GSparticleSetBankVisibility(model->particleBank, 1); }
    else { model->flags &= ~2; if (model->particleBank) GSparticleSetBankVisibility(model->particleBank, 0); }
}
extern "C" GSvec* GSmodelGetScalePtr(GSmodel* model) { return &model->scale; }
extern "C" void GSmodelGetScale(GSmodel* model, GSvec* out) { out->param1 = model->scale.param1; out->param2 = model->scale.param2; out->param3 = model->scale.param3; }
extern "C" void GSmodelSetScale(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->scale.param1 = value->param1; model->scale.param2 = value->param2; model->scale.param3 = value->param3; }
    } else { model->attachmentScale.param1 = value->param1; model->attachmentScale.param2 = value->param2; model->attachmentScale.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" GSvec* GSmodelGetRotationPtr(GSmodel* model) { return &model->rotation; }
extern "C" void GSmodelGetRotation(GSmodel* model, GSvec* out) { out->param1 = model->rotation.param1; out->param2 = model->rotation.param2; out->param3 = model->rotation.param3; }
extern "C" void GSmodelSetRotation(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->rotation.param1 = value->param1; model->rotation.param2 = value->param2; model->rotation.param3 = value->param3; }
    } else { model->attachmentRotation.param1 = value->param1; model->attachmentRotation.param2 = value->param2; model->attachmentRotation.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" GSvec* GSmodelGetPositionPtr(GSmodel* model) { return &model->position; }
extern "C" void GSmodelGetPosition(GSmodel* model, GSvec* out) { out->param1 = model->position.param1; out->param2 = model->position.param2; out->param3 = model->position.param3; }
extern "C" void GSmodelSetPosition(GSmodel* model, GSvec* value) {
    if (model->attachmentMode == 0) {
        if (!(model->flags & 0x400)) { model->position.param1 = value->param1; model->position.param2 = value->param2; model->position.param3 = value->param3; }
    } else { model->attachmentPosition.param1 = value->param1; model->attachmentPosition.param2 = value->param2; model->attachmentPosition.param3 = value->param3; }
    model->flags &= ~0x200;
}
extern "C" void GSmodelAddPosition(GSmodel* model, GSvec* delta) {
    GSvec value;
    if (model->attachmentMode == 0) { value.param1 = model->position.param1; value.param2 = model->position.param2; value.param3 = model->position.param3; }
    else { value.param1 = model->attachmentPosition.param1; value.param2 = model->attachmentPosition.param2; value.param3 = model->attachmentPosition.param3; }
    PSVECAdd((const Vec*)&value, (const Vec*)delta, (Vec*)&value);
    GSmodelSetPosition(model, &value);
}
extern "C" HSD_JObj* modelGetRenderJObj__FP8_GSmodel(GSmodel* model) { if (model->flags & 0x80) return model->blendJoint; return model->joint; }
extern "C" void modelSetScl__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->scale.param1 = v->param1; model->scale.param2 = v->param2; model->scale.param3 = v->param3; }
extern "C" void modelSetRot__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->rotation.param1 = v->param1; model->rotation.param2 = v->param2; model->rotation.param3 = v->param3; }
extern "C" void modelSetPos__FP8_GSmodelP5GSvec(GSmodel* model, GSvec* v) { if (model->flags & 0x400) return; model->position.param1 = v->param1; model->position.param2 = v->param2; model->position.param3 = v->param3; }

extern "C" {
static u32 _modelInUseCount;
void GSgfxRenderWaitForDrawComplete__Fv();
void modelShadowFreeModelList__FP8_GSmodel(GSmodel*);
void modelMaterialFree__FP10GSmaterial(GSmaterial*);
void GSmodelRemoveNull(GSmodel*);
void modelRemoveCenterNull__FP8_GSmodel(GSmodel*);
void GSmodelDisableAnimBlend(GSmodel*);
void HSD_JObjUnref(HSD_JObj*);
void GSmodelFreeDistortion(GSmodel*);
void GSboundFree(GSbound*);
void modelBankReleaseModel__FP8_GSmodel(GSmodel*);
void GSmemFree(void*);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void __assert(const char*, u32, const char*);
}
// Matches the SDK's lazy matrix setup and assertion contract.
static inline u8 modelJointMatrixDirty(HSD_JObj* joint) {
    if (!joint) __assert("jobj.h", 605, "jobj");
    u8 dirty = 0;
    if (!(joint->flags & 0x800000) && (joint->flags & 0x40)) dirty = 1;
    return dirty;
}
extern "C" f32 (*GSmodelGetMatrixPtr(GSmodel* model))[4] {
    HSD_JObj* joint = model->joint;
    if (joint && modelJointMatrixDirty(joint)) HSD_JObjSetupMatrixSub(joint);
    return model->joint->mtx;
}
extern "C" void GSmodelSetMatrix(GSmodel* model, Mtx matrix) {
    HSD_JObj* joint = model->joint;
    if (!joint) __assert("jobj.h", 1173, "jobj");
    if (!matrix) __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(matrix, joint->mtx);
    joint->flags |= 0x3800000;
    if (joint && !modelJointMatrixDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
}
extern "C" void GSmodelFree(GSmodel* model) {
    GSgfxRenderWaitForDrawComplete__Fv();
    modelShadowFreeModelList__FP8_GSmodel(model);
    GSmaterial* material;
    u32 count;
    count = model->materialCount;
    material = model->materials;
    if (count && material) {
        for (u32 i = 0; i < count; ++i, ++material) modelMaterialFree__FP10GSmaterial(material);
        GSmemFree(model->materials);
        model->materialCount = 0; model->materials = 0;
    }
    GSmodelRemoveNull(model); modelRemoveCenterNull__FP8_GSmodel(model);
    GSmodelDisableAnimBlend(model); HSD_JObjUnref(model->joint);
    if (model->particleBank) GSparticleDestroyAllGenerators(model->particleBank, 1);
    GSmodelFreeDistortion(model); GSboundFree((GSbound*)model->boundStorage);
    --_modelInUseCount;
    modelBankReleaseModel__FP8_GSmodel(model);
}

#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
extern "C" {
void GSboundGetWorldPosition(GSbound*, Vec*);
s32 GSboundIsInViewFast(GSbound*);
void GSgfxProjectSetupParameters();
void modelDustUpdate__FP8_GSmodel(GSmodel*);
void modelShadowUpdate__Fv();
}
extern "C" f32 GSmodelGetDistanceFromCamera(GSmodel* model) {
    GScamera* camera = model->camera;
    if (!camera) camera = GScameraGetActiveCamera();
    if (!camera) return 0.0f;
    Vec position;
    GSboundGetWorldPosition((GSbound*)model->boundStorage, &position);
    return PSVECDistance(&position, &camera->position);
}
// These callbacks are retained while the render-module registration is recovered.
#pragma push
#pragma force_active on
extern "C" {
static void _modelPostUpdate60fps__Fv() {
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (modelProcessAt60fps__FP8_GSmodel(model) == 1) GSmodelAdvanceAnimation(model, 1.0f);
    }
    GSgfxPerfbarCPUEntry(perf);
}
static void _modelPostUpdate__Ff(f32 delta) {
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (!modelProcessAt60fps__FP8_GSmodel(model)) GSmodelAdvanceAnimation(model, delta);
        modelDustUpdate__FP8_GSmodel(model);
    }
    GSgfxPerfbarCPUEntry(perf);
}
static void _modelPreUpdate__Ff(f32) {
    GSgfxProjectSetupParameters();
    u32 perf = GSgfxPerfbarCPUEntry(0x80);
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        model->flags &= 0xfbbffdff;
        if (model->flags & 2) {
            if (!model->camera && (model->flags & 0x100000)) {
                if (GSboundIsInViewFast((GSbound*)model->boundStorage)) model->flags |= 0x4000000;
            } else model->flags |= 0x4000000;
            if ((model->flags & 0x4000000) || (model->animationFlags & 8)) modelApplyAnimation__FP8_GSmodel(model);
        }
    }
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (model->flags & 2) { modelUpdateAttachments__FP8_GSmodel(model); modelUpdateTransform__FP8_GSmodel(model); }
    }
    for (GSmodel* model = _modelTopPtr; model; model = model->next) {
        if (model->flags & 0x4000000) modelApplyPartAnimMixes__FP8_GSmodel(model);
    }
    modelShadowUpdate__Fv();
    GSgfxPerfbarCPUEntry(perf);
}
}
#pragma pop
