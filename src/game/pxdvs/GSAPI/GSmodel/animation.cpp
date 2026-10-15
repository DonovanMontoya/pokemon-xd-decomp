#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
extern "C" {
extern GSmodel* _modelTopPtr;
u8 GSgfxVideoGetVsyncRate();
u32 GSgfxPerfbarCPUEntry(u32);
void HSD_JObjReqAnimAllByFlags(HSD_JObj*, u32, f32);
void GSpartAnimWalkTree(HSD_AnimJoint*, void (*)(HSD_AnimJoint*, void**, s32), void**);
}
#include <dolphin/mtx.h>
#include <game/maximum/GSAPI/baselib/quatlib.h>
struct HSD_MatAnimJoint { HSD_MatAnimJoint *child, *next; void* animations; };
struct HSD_ShapeAnimJoint { HSD_ShapeAnimJoint *child, *next; void** animations; };
struct GSpart { u8 inUse, reserved; u16 index; GSmodel* model; HSD_JObj* joint; };
extern "C" {
s32 GSpartSetAnimIndex(GSpart*, s32, s32, f32);
s32 GSpartSetTexAnimIndex(GSpart*, s32, s32, s32, f32);
void GSpartFree(GSpart*);
void __assert(const char*, int, const char*);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
static inline u8 HSD_JObjMtxIsDirty(HSD_JObj* joint) {
    u32 flags;
    int result;
    if (!joint) __assert("jobj.h", 605, "jobj");
    result = 0;
    flags = joint->flags;
    if (!(flags & 0x800000) && (flags & 0x40)) result = 1;
    return result;
}
static inline void HSD_JObjSetupMatrix(HSD_JObj* joint) {
    if (!joint || !HSD_JObjMtxIsDirty(joint)) return;
    HSD_JObjSetupMatrixSub(joint);
}
}
extern "C" void HSD_JObjSetMtxDirtySub(HSD_JObj*);
static inline void setQuaternion(f32* q, f32 x, f32 y, f32 z, f32 w) { q[0] = x; q[1] = y; q[2] = z; q[3] = w; }
static inline void HSD_JObjSetMtxDirty(HSD_JObj* joint) {
    if (joint && !HSD_JObjMtxIsDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
}
static inline void HSD_JObjSetTranslate(HSD_JObj* joint, GSvec* translate) {
    if (!joint) __assert("jobj.h", 937, "jobj");
    if (!translate) __assert("jobj.h", 938, "translate");
    joint->translate.x = translate->param1;
    joint->translate.y = translate->param2;
    joint->translate.z = translate->param3;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
static inline void HSD_JObjSetRotation(HSD_JObj* joint, HSD_Quaternion* rotate) {
    if (!joint) __assert("jobj.h", 656, "jobj");
    if (!rotate) __assert("jobj.h", 657, "rotate");
    joint->rotate = *rotate;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
static inline void HSD_JObjSetScale(HSD_JObj* joint, GSvec* scale) {
    if (!joint) __assert("jobj.h", 790, "jobj");
    if (!scale) __assert("jobj.h", 791, "scale");
    joint->scale.x = scale->param1;
    joint->scale.y = scale->param2;
    joint->scale.z = scale->param3;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
extern "C" void GSmodelRemoveRootJointAnimation(GSmodel* m) { m->flags |= 0x20000000; m->flags &= ~0x400; }
extern "C" void GSmodelUseRootJointAnimation(GSmodel* m, u8 use) { if (use) { m->flags |= 0x400; m->flags &= ~0x20000000; } else m->flags &= ~0x400; }
extern "C" u8 GSmodelIsNullAnimation(GSmodel* m, u32 index) {
    if (!m || !m->scene) return 1;
    if (index >= m->animationCount) return 1;
    HSD_AnimJoint* anim = m->scene->animations[index];
    if (!anim->child && !anim->next && !anim->aobjdesc && !anim->robj_anim && !anim->flags) return 1;
    return 0;
}
extern "C" {
static void _modelGetAnimFrameCountCB__FP14_HSD_AnimJointPPvi(HSD_AnimJoint* joint, void** context, s32) {
    if (!joint) return;
    HSD_AObjDesc* anim = joint->aobjdesc;
    if (!anim) return;
    if (anim->end_frame > *(f32*)context) *(f32*)context = anim->end_frame;
}
}
extern "C" f32 GSmodelGetAnimFrameCount(GSmodel* m, u32 index) {
    if (!(m->flags & 4)) return 0.0f;
    f32 end = 0.0f;
    GSpartAnimWalkTree(m->scene->animations[index], _modelGetAnimFrameCountCB__FP14_HSD_AnimJointPPvi, (void**)&end);
    return 1.0f + end;
}
extern "C" void GSmodelForceAnimTransformUpdate(GSmodel* m) {
    m->flags &= 0xffbffdff;
    u32 perf = GSgfxPerfbarCPUEntry(0xff0000);
    modelApplyAnimation__FP8_GSmodel(m); modelUpdateAttachments__FP8_GSmodel(m);
    modelUpdateTransform__FP8_GSmodel(m); modelApplyPartAnimMixes__FP8_GSmodel(m);
    GSgfxPerfbarCPUEntry(perf);
}
extern "C" void GSmodelSetAnimEndedCallback(GSmodel* m, void (*callback)(GSmodel*, void*), void* context) { m->endedCallback = callback; m->endedContext = context; }
extern "C" void GSmodelSetForceUseFractionalFramesFlag(GSmodel* m, u8 enable) { if (enable == 1) m->animationFlags |= 2; else m->animationFlags &= ~2; }
extern "C" void GSmodelSetSkipFractionalFramesFlag(GSmodel* m, u8 enable) { if (enable == 1) m->animationFlags |= 1; else m->animationFlags &= ~1; }
extern "C" void GSmodelSet60fpsAnimFlag(GSmodel* m, u8 enable) { if (enable == 1) m->flags |= 0x800; else m->flags &= ~0x800; }
extern "C" void GSmodelLinkTexAnimToAnim(GSmodel* m, u8 enable) { if (enable) m->flags |= 0x2000; else m->flags &= ~0x2000; }
extern "C" u32 GSmodelGetMaxTexAnimIndex(GSmodel* m) { return m->textureAnimationCount; }
extern "C" u32 GSmodelGetMaxAnimIndex(GSmodel* m) { return m->animationCount; }
extern "C" u8 GSmodelCanShapeAnimate(GSmodel* m) { return (m->flags >> 4) & 1; }
extern "C" u8 GSmodelCanTexAnimate(GSmodel* m) { return (m->flags >> 3) & 1; }
extern "C" u8 GSmodelCanAnimate(GSmodel* m) { return (m->flags >> 2) & 1; }
extern "C" u8 GSmodelHasTexAnimationEnded(GSmodel* m) { return (m->flags >> 15) & 1; }
extern "C" void GSmodelStopTexAnimation(GSmodel* m) { m->flags &= ~0x40; }
extern "C" void GSmodelStartTexAnimation(GSmodel* m) { if (m->flags & 8) { m->flags |= 0x40; m->flags &= ~0x8000; } }
extern "C" void GSmodelSetTexAnimFrame(GSmodel* m, f32 frame) {
    u32 flags = m->flags;
    HSD_JObj* joint = m->joint;
    if (flags & 8) {
        if ((flags & 0x20000) == 0x20000) joint = joint->child;
        m->textureAnimationFrame = frame; m->textureRequestedFrame = frame;
        HSD_JObjReqAnimAllByFlags(joint, 0x634, m->textureRequestedFrame);
        m->flags &= ~0x8000;
    }
}
extern "C" f32 fn_800F2298(GSmodel* m) {
    if (!(m->flags & 8)) return 0.0f;
    f32 rate = m->textureAnimationRate;
    if (GSgfxVideoGetVsyncRate() == 50) rate /= 1.2f;
    return rate;
}
extern "C" void GSmodelSetTexAnimRate(GSmodel* m, f32 rate) {
    if (m->flags & 8) {
        m->textureAnimationRate = rate;
        if (GSgfxVideoGetVsyncRate() == 50) m->textureAnimationRate *= 1.2f;
    }
}
extern "C" void GSmodelGetFrameCount(GSmodel* m, f32* first, f32* second) {
    if (!(m->flags & 0x80)) {
        if (first) *first = 1.0f + m->endFrame;
        if (second) *second = -1.0f;
    } else {
        if (first) *first = 1.0f + m->endFrame;
        if (second) *second = 1.0f + m->blendEndFrame;
    }
}
extern "C" f32 GSmodelGetAnimFrame(GSmodel* m) { if (!(m->flags & 4)) return 0.0f; if (m->flags & 0x80) return m->blendFrame; return m->animationFrame; }
extern "C" s32 GSmodelGetAnimType(GSmodel* m) { return m->animationType; }
extern "C" f32 GSmodelGetAnimRate(GSmodel* m) { f32 rate; if (m->flags & 0x80) rate = m->blendRate; else rate = m->animationRate; if (GSgfxVideoGetVsyncRate() == 50) rate /= 1.2f; return rate; }
extern "C" void GSmodelGetAnimIndex(GSmodel* m, u32* first, u32* second) {
    if (!(m->flags & 0x80)) { if (first) *first = m->animationIndex; if (second) *second = -1; }
    else { if (first) *first = m->animationIndex; if (second) *second = m->blendIndex; }
}
extern "C" u8 GSmodelIsBlending(GSmodel* m) { return (m->flags >> 7) & 1; }
extern "C" void GSmodelSetBlendFactor(GSmodel* m, f32 blend) {
    if (m->flags & 4) {
        if (m->flags & 0x80) {
            if (blend < 0.0f) blend = 0.0f; else if (blend > 1.0f) blend = 1.0f;
            m->blendFactor = blend;
        }
    }
}
extern "C" void GSmodelSetBlendAnimFrameForce(GSmodel* m, f32 first, f32 second) {
    m->animationRate = 0.0f; m->blendRate = 0.0f;
    m->animationFrame = first; m->blendFrame = second;
    m->requestedFrame = m->animationFrame; m->blendRequestedFrame = m->blendFrame;
}
extern "C" void GSmodelAllUnpauseAnimation() { for (GSmodel* m = _modelTopPtr; m; m = m->next) m->flags &= ~0x100; }
extern "C" void GSmodelAllPauseAnimation() { for (GSmodel* m = _modelTopPtr; m; m = m->next) m->flags |= 0x100; }
extern "C" u8 GSmodelHasAnimationEnded(GSmodel* m) { return (m->flags >> 14) & 1; }
extern "C" u8 GSmodelIsAnimating(GSmodel* m) { return (m->flags >> 5) & 1; }
extern "C" void GSmodelStopAnimation(GSmodel* m) { if (m->flags & 4) m->flags &= ~0x20; if (m->flags & 0x2000) m->flags &= ~0x40; }
extern "C" void GSmodelStartAnimation(GSmodel* m) {
    if (m->flags & 4) { m->flags |= 0x20; m->flags &= ~0x4000; }
    if (m->flags & 0x2000) { if (m->flags & 8) { m->flags |= 0x40; m->flags &= ~0x8000; } }
}
extern "C" void GSmodelSetDontResetPartAnimFlag(GSmodel* m, u8 enable) { if (enable) m->animationFlags |= 0x10; else m->animationFlags &= ~0x10; }
extern "C" void GSmodelSetKeepPartAnimFlag(GSmodel* m, u8 enable) { if (enable) m->flags |= 0x80000000; else m->flags &= ~0x80000000; }
extern "C" u8 modelProcessAt60fps__FP8_GSmodel(GSmodel* m) {
    if (m->animationFlags & 2) return 0;
    if ((m->flags & 0x800) == 0x800 || (m->attachmentMode != 0 && m->attachmentModel)) return 1;
    return 0;
}
extern "C" void _modelGetEndFrame(HSD_AObj* aobj, f32* frame) {
    if (!aobj) __assert("aobj.h", 172, "aobj");
    if (aobj->end_frame > *frame) *frame = aobj->end_frame;
}

extern "C" {
void HSD_JObjAddAnimAll(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*, HSD_ShapeAnimJoint*);
void HSD_JObjRemoveAnim(HSD_JObj*);
void HSD_JObjAnimAll(HSD_JObj*);
static void _modelSetLoopFlag__FP9_HSD_AObjUl(HSD_AObj* aobj, u32 loop) {
    if (!(HSD_AObjGetFlags(aobj) & 0x10000)) {
        if (!loop) HSD_AObjClearFlags(aobj, AOBJ_LOOP);
        else HSD_AObjSetFlags(aobj, AOBJ_LOOP);
    }
}
static void _modelGetAObjFunc__FP9_HSD_AObjPv(HSD_AObj* aobj, void* context) { if (aobj && !*(HSD_AObj**)context) *(HSD_AObj**)context = aobj; }
}
extern "C" void GSmodelSetTexAnimType(GSmodel* m, s32 type) {
    HSD_JObj* joint = m->joint;
    if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
    m->textureAnimationType = type;
    switch (m->textureAnimationType) {
    case 0: HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x64db, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 0); break;
    case 1: HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x64db, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 1); break;
    }
}
extern "C" void GSmodelSetTexAnimIndex(GSmodel* m, u32 index) {
    HSD_JObj* joint = m->joint;
    if ((m->flags & 8) && index < m->textureAnimationCount) {
        if (index != m->textureAnimationIndex || m->partTextureAnimationChanged == 1) {
            if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
            m->textureAnimationIndex = index;
            HSD_JObjAddAnimAll(joint, 0, m->scene->materialAnimations[m->textureAnimationIndex], 0);
            if ((m->flags & 0x20000000) && joint->aobj) HSD_JObjRemoveAnim(joint);
            m->textureEndFrame = 0.0f;
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x64db, (void*)_modelGetEndFrame, AOBJ_ARG_AV, &m->textureEndFrame);
            HSD_AObj* aobj = 0;
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x480, (void*)_modelGetAObjFunc__FP9_HSD_AObjPv, AOBJ_ARG_AV, &aobj);
            m->textureAnimation = aobj;
        }
        GSmodelSetTexAnimFrame(m, 0.0f);
        GSmodelSetTexAnimType(m, m->textureAnimationType);
        m->partTextureAnimations[0].animation = 0;
        m->partTextureAnimations[1].animation = 0;
        m->partTextureAnimations[2].animation = 0;
        m->partTextureAnimations[3].animation = 0;
        m->partTextureAnimationChanged = 0;
    }
}
// IEEE-754 classification, following the runtime's five-class float contract.
static inline s32 classifyAnimationFrame(f32 value) {
    union { f32 value; u32 bits; } representation;
    representation.value = value;
    switch (representation.bits & 0x7f800000) {
    case 0x7f800000: if (representation.bits & 0x7fffff) return 1; return 2;
    case 0: if (representation.bits & 0x7fffff) return 5; return 3;
    default: return 4;
    }
}
extern "C" void GSmodelSetAnimRate(GSmodel* m, f32 rate) {
    if (!(rate < 0.0f) && classifyAnimationFrame(rate) != 1) {
    if (m->flags & 4) {
        f32 adjusted = rate;
        if (GSgfxVideoGetVsyncRate() == 50) adjusted *= 1.2f;
        if (!(m->flags & 0x80)) m->animationRate = adjusted;
        else {
            f32 first = 1.0f + m->endFrame;
            f32 second = 1.0f + m->blendEndFrame;
            m->blendRate = adjusted;
            m->animationRate = adjusted * (first / second);
        }
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimRate(m, rate);
    }
}
extern "C" void GSmodelSetAnimFrame(GSmodel* m, f32 frame) {
    s32 i;
    HSD_JObj* joint;
    if (!(frame < 0.0f) && classifyAnimationFrame(frame) != 1) {
    if (m->flags & 4) {
        if (!(m->flags & 0x80)) {
            joint = m->joint;
            if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
            m->animationFrame = frame; m->requestedFrame = m->animationFrame;
            if (m->flags & 0x80000000) {
                for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjSetFlags(m->partAnimations[i].animation, 0x10000);
            }
            HSD_JObjReqAnimAllByFlags(joint, 0x1cb, m->requestedFrame);
            HSD_JObjAnimAll(joint);
            if (m->flags & 0x80000000) {
                for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjClearFlags(m->partAnimations[i].animation, 0x10000);
            }
        } else {
            f32 ratio = m->blendRate != 0.0f ? m->animationRate / m->blendRate : 1.0f;
            m->animationFrame = frame * ratio; m->requestedFrame = m->animationFrame;
            m->blendFrame = frame; m->blendRequestedFrame = m->blendFrame;
            HSD_JObjReqAnimAllByFlags(m->joint, 0x1cb, m->requestedFrame);
            HSD_JObjReqAnimAllByFlags(m->animationBlendJoint, 0x1cb, m->blendRequestedFrame);
            HSD_JObjAnimAll(m->joint); HSD_JObjAnimAll(m->animationBlendJoint);
        }
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimFrame(m, frame);
    m->flags &= ~0x4000;
    }
}

static inline void modelSetAnimTypeInline(GSmodel* m, s32 type) {
    if (m->flags & 4) {
        s32 i, j;
        HSD_JObj* joint = m->joint;
        HSD_JObj* blend = m->animationBlendJoint;
        if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
        m->animationType = type; m->blendType = type;
        if (m->flags & 0x80000000) {
            for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjSetFlags(m->partAnimations[i].animation, 0x10000);
        }
        switch (m->animationType) {
        case 0:
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 0);
            if (m->flags & 0x80) HSD_ForeachAnim(blend, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 0);
            break;
        case 1:
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 1);
            if (m->flags & 0x80) HSD_ForeachAnim(blend, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelSetLoopFlag__FP9_HSD_AObjUl, AOBJ_ARG_AU, 1);
            break;
        }
        if (m->flags & 0x80000000) {
            for (j = 0; j < 8; ++j) if (m->partAnimations[j].animation) HSD_AObjClearFlags(m->partAnimations[j].animation, 0x10000);
        }
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimType(m, type);
}
extern "C" void GSmodelSetAnimType(GSmodel* m, s32 type) { modelSetAnimTypeInline(m, type); }
extern "C" void modelCalculatePartMix__FP5GSvecP5GSvecUl(GSvec* out, GSvec* value, u32 mode) {
    switch (mode & 0xff) {
    case 0: break;
    case 1: out->param1 = value->param1; break;
    case 2: out->param1 += value->param1; break;
    }
    switch (mode & 0xff00) {
    case 0: break;
    case 0x100: out->param2 = value->param2; break;
    case 0x200: out->param2 += value->param2; break;
    }
    switch (mode & 0xff0000) {
    case 0: break;
    case 0x10000: out->param3 = value->param3; break;
    case 0x20000: out->param3 += value->param3; break;
    }
}
extern "C" void GSmodelSetPartAnimIndex(GSmodel* m, u32 part, s32 index, f32 blend, s32 flag) {
    GSpart* p = GSmodelGetPart(m, part);
    if (p) {
        GSpartSetAnimIndex(p, index, flag, blend);
        GSpartFree(p);
    }
}
extern "C" void GSmodelSetPartTexAnimIndex(GSmodel* m, u32 part, s32 index, s32 a, s32 b, f32 blend) {
    GSpart* p = GSmodelGetPart(m, part);
    if (p) {
        GSpartSetTexAnimIndex(p, index, a, b, blend);
        GSpartFree(p);
    }
}
extern "C" {
static void _modelResetPartAnimMixes__FP8_GSmodel(GSmodel* m) {
    s32 i;
    for (i = 0; i < 16; ++i) {
        GSmodelPartAnimMix* mix = &m->partAnimMixes[i];
        if (mix->identifier != 0) {
            GSpart* part = GSmodelGetPart(m, mix->partIndex);
            if (part) {
                switch (mix->identifier) {
                case 1:
                    HSD_JObjSetTranslate(part->joint, &mix->position);
                    break;
                case 2: {
                    f32 rotate[4];
                    setQuaternion(rotate, mix->rotation.param1, mix->rotation.param2, mix->rotation.param3, 0.0f);
                    HSD_JObjSetRotation(part->joint, (HSD_Quaternion*)rotate);
                    break;
                }
                case 3:
                    HSD_JObjSetScale(part->joint, &mix->scale);
                    break;
                }
                GSpartFree(part);
            }
        }
    }
}
void HSD_JObjAddAnim(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*, HSD_ShapeAnimJoint*);
static void _jobjAddAnimAll__FP9_HSD_JObjP14_HSD_AnimJointP17_HSD_MatAnimJointP19_HSD_ShapeAnimJoint(HSD_JObj* joint, HSD_AnimJoint* animation, HSD_MatAnimJoint* material, HSD_ShapeAnimJoint* shape) {
    if (joint) {
        if (!joint->aobj || !(HSD_AObjGetFlags(joint->aobj) & 0x10000)) HSD_JObjAddAnim(joint, animation, material, shape);
        if (!(joint->flags & 0x1000)) {
            HSD_JObj* child = joint->child;
            HSD_AnimJoint* childAnimation = animation ? animation->child : 0;
            HSD_MatAnimJoint* childMaterial = material ? material->child : 0;
            HSD_ShapeAnimJoint* childShape = shape ? shape->child : 0;
            while (child) {
                _jobjAddAnimAll__FP9_HSD_JObjP14_HSD_AnimJointP17_HSD_MatAnimJointP19_HSD_ShapeAnimJoint(child, childAnimation, childMaterial, childShape);
                child = child->next;
                childAnimation = childAnimation ? childAnimation->next : 0;
                childMaterial = childMaterial ? childMaterial->next : 0;
                childShape = childShape ? childShape->next : 0;
            }
        }
    }
}
static void _modelRecalcMatrixAll__FP9_HSD_JObj(HSD_JObj* joint) {
    if (joint) {
        HSD_JObjSetupMatrix(joint);
        if (!(joint->flags & 0x1000)) {
            HSD_JObj* child = joint->child;
            while (child) {
                _modelRecalcMatrixAll__FP9_HSD_JObj(child);
                child = child->next;
            }
        }
    }
}
}

extern "C" {
void GSvecTransformQuat(GSvec*, HSD_Quaternion*, GSvec*);
void GSmodelDetachFromGSpart(GSmodel*, u8);
void GSpartGetTransform(GSpart*, GSvec*, GSvec*, GSvec*);
}
static inline void HSD_JObjSetMtx(HSD_JObj* joint, Mtx mtx) {
    if (!joint) __assert("jobj.h", 1173, "jobj");
    if (!mtx) __assert("jobj.h", 1174, "mtx");
    PSMTXCopy(mtx, joint->mtx);
    joint->flags |= 0x3800000;
    HSD_JObjSetMtxDirty(joint);
}
extern "C" void modelUpdateAttachments__FP8_GSmodel(GSmodel* m) {
    if (m->attachmentMode == 0) return;
    if (m->flags & 0x400000) return;
    {
        GSpart* part;
        GSvec position, rotation, scale;
        HSD_Quaternion quaternion;
        GSvec offset;
        m->flags |= 0x800000;
        modelUpdateAttachments__FP8_GSmodel(m->attachmentModel);
        modelUpdateTransform__FP8_GSmodel(m->attachmentModel);
        part = GSmodelGetPart(m->attachmentModel, m->attachmentPart);
        GSpartGetTransform(part, &position, &rotation, &scale);
        GSpartFree(part);
        EulerToQuat((HSD_Vec3*)&rotation, &quaternion);
        GSvecTransformQuat(&offset, &quaternion, &m->attachmentPosition);
        PSVECAdd((Vec*)&position, (Vec*)&offset, (Vec*)&position);
        PSVECAdd((Vec*)&rotation, (Vec*)&m->attachmentRotation, (Vec*)&rotation);
        scale.param1 = scale.param1 * m->attachmentScale.param1;
        scale.param2 = scale.param2 * m->attachmentScale.param2;
        scale.param3 = scale.param3 * m->attachmentScale.param3;
        modelSetPos__FP8_GSmodelP5GSvec(m, &m->attachmentPosition);
        modelSetRot__FP8_GSmodelP5GSvec(m, &m->attachmentRotation);
        modelSetScl__FP8_GSmodelP5GSvec(m, &m->attachmentScale);
        switch (m->attachmentMode) {
        case 1: modelSetPos__FP8_GSmodelP5GSvec(m, &position); break;
        case 2: modelSetRot__FP8_GSmodelP5GSvec(m, &rotation); break;
        case 3: modelSetScl__FP8_GSmodelP5GSvec(m, &scale); break;
        case 4:
            modelSetPos__FP8_GSmodelP5GSvec(m, &position);
            modelSetRot__FP8_GSmodelP5GSvec(m, &rotation);
            break;
        case 5:
            modelSetRot__FP8_GSmodelP5GSvec(m, &rotation);
            modelSetScl__FP8_GSmodelP5GSvec(m, &scale);
            break;
        case 6:
            modelSetPos__FP8_GSmodelP5GSvec(m, &position);
            modelSetScl__FP8_GSmodelP5GSvec(m, &scale);
            break;
        case 7:
            modelSetPos__FP8_GSmodelP5GSvec(m, &position);
            modelSetRot__FP8_GSmodelP5GSvec(m, &rotation);
            modelSetScl__FP8_GSmodelP5GSvec(m, &scale);
            break;
        case 8: {
            Mtx rotationMatrix, axisMatrix;
            modelSetPos__FP8_GSmodelP5GSvec(m, &position);
            modelSetRot__FP8_GSmodelP5GSvec(m, &rotation);
            modelSetScl__FP8_GSmodelP5GSvec(m, &scale);
            PSMTXRotRad(rotationMatrix, 'z', rotation.param3);
            PSMTXRotRad(axisMatrix, 'y', rotation.param2);
            PSMTXConcat(axisMatrix, rotationMatrix, rotationMatrix);
            PSMTXRotRad(axisMatrix, 'x', rotation.param1);
            PSMTXConcat(axisMatrix, rotationMatrix, rotationMatrix);
            PSMTXTrans(axisMatrix, position.param1, position.param2, position.param3);
            PSMTXConcat(axisMatrix, rotationMatrix, rotationMatrix);
            HSD_JObjSetMtx(m->joint, rotationMatrix);
            break;
        }
        }
        if (m->flags & 0x40000) GSmodelDetachFromGSpart(m, 0);
        m->flags |= 0x400000;
        m->flags &= ~0x800000;
    }
}

struct PartMixView {
    s32 identifier;
    u32 partIndex;
    f32 (*callback)(GSpart*, s32, u32, GSvec*);
    u32 argument;
    u32 mode;
    GSvec position, rotation, scale;
};
extern "C" {
HSD_JObj* GSpartGetJObjPtr(HSD_JObj*, u32);
}
static inline void HSD_JObjGetTranslate(HSD_JObj* joint, GSvec* translate) {
    if (!joint) __assert("jobj.h", 996, "jobj");
    if (!translate) __assert("jobj.h", 997, "translate");
    translate->param1 = joint->translate.x;
    translate->param2 = joint->translate.y;
    translate->param3 = joint->translate.z;
}
static inline void HSD_JObjGetRotation(HSD_JObj* joint, HSD_Quaternion* rotate) {
    if (!joint) __assert("jobj.h", 733, "jobj");
    if (!rotate) __assert("jobj.h", 734, "rotate");
    *rotate = joint->rotate;
}
static inline void HSD_JObjGetScale(HSD_JObj* joint, GSvec* scale) {
    if (!joint) __assert("jobj.h", 849, "jobj");
    if (!scale) __assert("jobj.h", 850, "scale");
    scale->param1 = joint->scale.x;
    scale->param2 = joint->scale.y;
    scale->param3 = joint->scale.z;
}
static inline void modelEvaluatePartMix(GSmodel* m, PartMixView* mix, GSpart* part, GSvec* out) {
    GSpart* use = part;
    if (!use) {
        use = GSmodelGetPart(m, mix->partIndex);
        if (!use) return;
    }
    f32 weight = mix->callback(use, mix->identifier, mix->argument, out);
    if (weight != 1.0f) PSVECScale((Vec*)out, (Vec*)out, weight);
    if (!part) GSpartFree(use);
}
extern "C" void modelApplyPartAnimMixes__FP8_GSmodel(GSmodel* m) {
    s32 i;
    f32 vector[3];
    GSvec value;
    f32 quaternion[4];
    for (i = 0; i < 16; ++i) {
        PartMixView* mix = (PartMixView*)&m->partAnimMixes[i];
        if (mix->identifier != 0) {
            GSpart* part = GSmodelGetPart(m, mix->partIndex);
            if (part) {
                modelEvaluatePartMix(m, mix, part, &value);
                if (!(m->flags & 0x80)) {
                    switch (mix->identifier) {
                    case 1:
                        HSD_JObjGetTranslate(part->joint, (GSvec*)vector);
                        modelCalculatePartMix__FP5GSvecP5GSvecUl((GSvec*)vector, &value, mix->mode);
                        HSD_JObjSetTranslate(part->joint, (GSvec*)vector);
                        break;
                    case 2:
                        HSD_JObjGetRotation(part->joint, (HSD_Quaternion*)quaternion);
                        modelCalculatePartMix__FP5GSvecP5GSvecUl((GSvec*)quaternion, &value, mix->mode);
                        HSD_JObjSetRotation(part->joint, (HSD_Quaternion*)quaternion);
                        break;
                    case 3:
                        HSD_JObjGetScale(part->joint, (GSvec*)vector);
                        modelCalculatePartMix__FP5GSvecP5GSvecUl((GSvec*)vector, &value, mix->mode);
                        HSD_JObjSetScale(part->joint, (GSvec*)vector);
                        break;
                    }
                } else {
                    HSD_JObj* blendA = GSpartGetJObjPtr(m->joint, mix->partIndex);
                    HSD_JObj* blendB = GSpartGetJObjPtr(m->animationBlendJoint, mix->partIndex);
                    if (blendA && blendB) {
                        switch (mix->identifier) {
                        case 1: modelIntpJObjTrans__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(blendA, blendB, part->joint, m->blendFactor, &value, mix->mode); break;
                        case 2: modelIntpJObjRotate__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(blendA, blendB, part->joint, m->blendFactor, &value, mix->mode); break;
                        case 3: modelIntpJObjScale__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(blendA, blendB, part->joint, m->blendFactor, &value, mix->mode); break;
                        }
                    }
                }
                GSpartFree(part);
            }
        }
    }
}

struct GSbound;
extern "C" void GSboundSetAnimFrame(GSbound*, f32);
struct ModelAnimEvent { u32 flags; s32 index; void* context; };
extern "C" void GSmodelAdvanceAnimation(GSmodel* m, f32 delta) {
    s32 type, index;
    u32 stopMask, endMask;
    s32 i;
    if (!(m->flags & 0x100)) {
        if (m->flags & 0x4000) {
            s32 animIndex, animType;
            u32 animStopMask, animEndMask;
            if (!(m->flags & 0x80)) {
                animIndex = m->animationIndex;
                animType = m->animationType;
                animEndMask = 0x4000;
                animStopMask = 0x20;
            } else {
                animIndex = m->blendIndex;
                animType = m->blendType;
                animEndMask = 0x4000;
                animStopMask = 0x20;
            }
            switch (animType) {
            case 0: m->flags &= ~animStopMask; break;
            case 1: m->flags &= ~animEndMask; break;
            }
            bool looped = (animType == 1);
            if (m->endedCallback) {
                ModelAnimEvent event;
                event.flags = 0;
                event.flags |= 1;
                if (looped == 1) event.flags |= 4;
                event.index = animIndex;
                event.context = m->endedContext;
                m->endedCallback(m, &event);
            }
        }
        if (m->flags & 0x8000) {
            if (!(m->flags & 0x80)) {
                index = m->textureAnimationIndex;
                type = m->textureAnimationType;
                endMask = 0x8000;
                stopMask = 0x40;
            }
            switch (type) {
            case 0: m->flags &= ~stopMask; break;
            case 1: m->flags &= ~endMask; break;
            }
            bool looped = (type == 1);
            if (m->endedCallback) {
                ModelAnimEvent event;
                event.flags = 0;
                event.flags |= 2;
                if (looped == 1) event.flags |= 4;
                event.index = index;
                event.context = m->endedContext;
                m->endedCallback(m, &event);
            }
        }
        if (m->partAnimationChanged == 1) {
            for (i = 0; i < 8; ++i) {
                if (m->partAnimations[i].animation) {
                    if (m->partAnimations[i].requestedFrame >= m->partAnimations[i].endFrame - 0.0001f && !(m->animationFlags & 0x10)) {
                        if (m->partAnimations[i].mode == 0) m->partAnimations[i].animation = 0;
                        bool looped = (m->partAnimations[i].mode == 1);
                        s32 eventIndex = m->partAnimations[i].animationIndex;
                        if (m->endedCallback) {
                            ModelAnimEvent event;
                            event.flags = 0;
                            event.flags |= 1;
                            if (looped == 1) event.flags |= 4;
                            event.index = eventIndex;
                            event.flags |= 8;
                            event.context = m->endedContext;
                            m->endedCallback(m, &event);
                        }
                    }
                }
            }
        }
        if (m->partTextureAnimationChanged == 1) {
            for (i = 0; i < 4; ++i) {
                if (m->partTextureAnimations[i].animation) {
                    if (m->partTextureAnimations[i].requestedFrame >= m->partTextureAnimations[i].endFrame - 0.0001f && !(m->animationFlags & 0x10)) {
                        if (m->partTextureAnimations[i].mode == 0) m->partTextureAnimations[i].animation = 0;
                        bool looped = (m->partTextureAnimations[i].mode == 1);
                        s32 eventIndex = m->partTextureAnimations[i].animationIndex;
                        if (m->endedCallback) {
                            ModelAnimEvent event;
                            event.flags = 0;
                            event.flags |= 2;
                            if (looped == 1) event.flags |= 4;
                            event.index = eventIndex;
                            event.flags |= 8;
                            event.context = m->endedContext;
                            m->endedCallback(m, &event);
                        }
                    }
                }
            }
        }
        if (m->flags & 0x20) {
            f32 step = m->animationRate * delta;
            if (step != 0.0f) {
                m->animationFrame += step;
                switch (m->animationType) {
                case 0:
                    if (m->animationFrame >= m->endFrame) {
                        m->animationFrame = m->endFrame;
                        m->flags |= 0x4000;
                    }
                    break;
                case 1:
                    if (m->animationFrame >= m->endFrame - 0.001f) {
                        m->animationFrame -= m->endFrame;
                        if (m->animationFrame < 0.0f) m->animationFrame = 0.0f;
                        m->flags |= 0x4000;
                    }
                    break;
                }
            }
            GSboundSetAnimFrame((GSbound*)m->boundStorage, m->animationFrame);
            if (m->flags & 0x80) {
                f32 blendStep = m->blendRate * delta;
                if (blendStep != 0.0f) {
                    m->blendFrame += blendStep;
                    switch (m->blendType) {
                    case 0:
                        if (m->blendFrame >= m->blendEndFrame) {
                            m->blendFrame = m->blendEndFrame;
                            m->flags |= 0x4000;
                        }
                        break;
                    case 1:
                        if (m->blendFrame >= m->blendEndFrame - 0.001f) {
                            m->blendFrame -= m->blendEndFrame;
                            if (m->blendFrame < 0.0f) m->blendFrame = 0.0f;
                            m->flags |= 0x4000;
                        }
                        break;
                    }
                }
            }
        }
        if (m->flags & 0x40) {
            f32 step = m->textureAnimationRate * delta;
            if (step != 0.0f) {
                m->textureAnimationFrame += step;
                switch (m->textureAnimationType) {
                case 0:
                    if (m->textureAnimationFrame >= m->textureEndFrame) {
                        m->textureAnimationFrame = m->textureEndFrame;
                        m->flags |= 0x8000;
                    }
                    break;
                case 1:
                    if (m->textureAnimationFrame >= m->textureEndFrame - 0.001f) {
                        m->textureAnimationFrame -= m->textureEndFrame;
                        if (m->textureAnimationFrame < 0.0f) m->textureAnimationFrame = 0.0f;
                        m->flags |= 0x8000;
                    }
                    break;
                }
            }
        }
    }
}

extern "C" {
void modelUpdateCenterNull__FP8_GSmodel(GSmodel*);
HSD_JObj* modelGetRenderJObj__FP8_GSmodel(GSmodel*);
}
static inline void HSD_JObjSetRotationX(HSD_JObj* joint, f32 x) {
    if (!joint) __assert("jobj.h", 676, "jobj");
    if (joint->flags & 0x20000) __assert("jobj.h", 677, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.x = x;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
static inline void HSD_JObjSetRotationY(HSD_JObj* joint, f32 y) {
    if (!joint) __assert("jobj.h", 696, "jobj");
    if (joint->flags & 0x20000) __assert("jobj.h", 697, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.y = y;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
static inline void HSD_JObjSetRotationZ(HSD_JObj* joint, f32 z) {
    if (!joint) __assert("jobj.h", 716, "jobj");
    if (joint->flags & 0x20000) __assert("jobj.h", 717, "!(jobj->flags & JOBJ_USE_QUATERNION)");
    joint->rotate.z = z;
    if (!(joint->flags & 0x2000000)) HSD_JObjSetMtxDirty(joint);
}
static inline f32 HSD_JObjGetRotationX(HSD_JObj* joint) {
    if (!joint) __assert("jobj.h", 748, "jobj");
    return joint->rotate.x;
}
static inline void modelClampScale(f32* scale) {
    f32 value = *scale;
    if (value < 0.00001f && value > -0.00001f) {
        *scale = (value < 0.0f) ? -0.00001f : 0.00001f;
    }
}
extern "C" void modelUpdateTransform__FP8_GSmodel(GSmodel* m) {
    if (!(m->flags & 0x200)) {
        HSD_JObj* joint;
        modelUpdateCenterNull__FP8_GSmodel(m);
        joint = modelGetRenderJObj__FP8_GSmodel(m);
        modelClampScale(&m->scale.param1);
        modelClampScale(&m->scale.param2);
        modelClampScale(&m->scale.param3);
        if (m->flags & 0x80) {
            f32 quaternion[4];
            EulerToQuat((HSD_Vec3*)&m->rotation, (HSD_Quaternion*)quaternion);
            HSD_JObjSetTranslate(joint, &m->position);
            HSD_JObjSetRotation(joint, (HSD_Quaternion*)quaternion);
            HSD_JObjSetScale(joint, &m->scale);
            _modelRecalcMatrixAll__FP9_HSD_JObj(joint);
        } else {
            if (m->flags & 0x400) {
                HSD_JObjGetTranslate(joint, &m->position);
                m->rotation.param1 = HSD_JObjGetRotationX(joint);
                m->rotation.param2 = HSD_JObjGetRotationX(joint);
                m->rotation.param3 = HSD_JObjGetRotationX(joint);
                HSD_JObjGetScale(joint, &m->scale);
            } else {
                HSD_JObjSetTranslate(joint, &m->position);
                HSD_JObjSetRotationX(joint, m->rotation.param1);
                HSD_JObjSetRotationY(joint, m->rotation.param2);
                HSD_JObjSetRotationZ(joint, m->rotation.param3);
                HSD_JObjSetScale(joint, &m->scale);
            }
            if ((m->flags & 0x20000) == 0x20000) HSD_JObjSetupMatrix(joint->child);
            HSD_JObjSetupMatrix(joint);
        }
        m->flags |= 0x200;
    }
}

extern "C" double fmod(double, double);
extern "C" f32 GSgfxVideoGetLastRenderTime();
extern "C" void modelCalculateBlendModel__FP8_GSmodelf(GSmodel*, f32);
#define MODEL_CALC_RATE(rate, FRAME, END, REQUESTED, TYPE) \
    u8 at60 = modelProcessAt60fps__FP8_GSmodel(m); \
    f32 rate = 0.0f; \
    f32 frame; \
    if ((m->animationFlags & 1) == 1 && at60 == 0) frame = (f32)(s32)m->FRAME; \
    else frame = m->FRAME; \
    if (m->END > 0.0f) { \
        switch (m->TYPE) { \
        case 0: \
            if (frame >= m->END) frame = m->END; \
            break; \
        case 1: \
            if (frame >= m->END - 0.001f) frame = (f32)fmod(frame, m->END); \
            break; \
        } \
    } \
    if (frame != m->REQUESTED) { \
        if (frame < m->REQUESTED) { \
            if (m->TYPE == 1) rate = frame + (m->END - m->REQUESTED); \
            else rate = 0.0f; \
        } else { \
            rate = frame - m->REQUESTED; \
        } \
    } \
    if (rate < 0.0f) rate = 0.0f;
extern "C" void modelApplyAnimation__FP8_GSmodel(GSmodel* m) {
    if (m->flags & 0xc) {
        if (m->flags & 0x80) {
            if ((m->flags & 4) && m->animation && m->blendAnimation) {
                MODEL_CALC_RATE(rate, animationFrame, endFrame, requestedFrame, animationType)
                HSD_ForeachAnim(m->joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, rate);
                {
                MODEL_CALC_RATE(blendRate, blendFrame, blendEndFrame, blendRequestedFrame, blendType)
                HSD_ForeachAnim(m->animationBlendJoint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, blendRate);
                }
            }
            HSD_JObjAnimAll(m->joint);
            HSD_JObjAnimAll(m->animationBlendJoint);
            if (m->flags & 4) {
                if (m->animation && m->blendAnimation) {
                    s32 i;
                    m->requestedFrame = m->animation->curr_frame;
                    m->blendRequestedFrame = m->blendAnimation->curr_frame;
                    if (m->partAnimationChanged == 1) {
                        for (i = 0; i < 8; ++i) {
                            if (m->partAnimations[i].animation) m->partAnimations[i].requestedFrame = m->partAnimations[i].animation->curr_frame;
                        }
                    }
                }
            }
            f32 rate;
            if (m->flags & 0x80) rate = m->blendRate;
            else rate = m->animationRate;
            if (GSgfxVideoGetVsyncRate() == 50) rate /= 1.2f;
            modelCalculateBlendModel__FP8_GSmodelf(m, rate * GSgfxVideoGetLastRenderTime() / 2.0f);
            return;
        }
        _modelResetPartAnimMixes__FP8_GSmodel(m);
        HSD_JObj* joint = m->joint;
        if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
        if ((m->flags & 4) && m->animation) {
            MODEL_CALC_RATE(rate, animationFrame, endFrame, requestedFrame, animationType)
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, rate);
        }
        if ((m->flags & 8) && m->textureAnimation) {
            MODEL_CALC_RATE(rate, textureAnimationFrame, textureEndFrame, textureRequestedFrame, textureAnimationType)
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x64db, (void*)HSD_AObjSetRate, AOBJ_ARG_AF, rate);
        }
        HSD_JObjAnimAll(joint);
        if (m->flags & 4) {
            if (m->animation) {
                s32 i;
                m->requestedFrame = m->animation->curr_frame;
                if (m->partAnimationChanged == 1) {
                    for (i = 0; i < 8; ++i) {
                        if (m->partAnimations[i].animation) m->partAnimations[i].requestedFrame = m->partAnimations[i].animation->curr_frame;
                    }
                }
            }
        }
        if (m->flags & 8) {
            if (m->textureAnimation) {
                s32 i;
                m->textureRequestedFrame = m->textureAnimation->curr_frame;
                if (m->partTextureAnimationChanged == 1) {
                    for (i = 0; i < 4; ++i) {
                        if (m->partTextureAnimations[i].animation) m->partTextureAnimations[i].requestedFrame = m->partTextureAnimations[i].animation->curr_frame;
                    }
                }
            }
        }
    }
}

extern "C" void GSboundSetAnimIndex(GSbound*, u32);
extern "C" void GSmodelSetAnimIndex(GSmodel* m, u32 index) {
    f32 rate;
    if (m->flags & 4) {
        if (index >= m->animationCount) return;
        if (GSmodelIsNullAnimation(m, index)) return;
        if (m->flags & 0x80) rate = m->blendRate;
        else rate = m->animationRate;
        if (GSgfxVideoGetVsyncRate() == 50) rate /= 1.2f;
        if (index != m->animationIndex || (m->flags & 0x80) || m->partAnimationChanged == 1) {
            HSD_JObj* joint = m->joint;
            void** shape;
            if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
            m->flags &= ~0x80;
            m->animationIndex = index;
            if (m->flags & 0x10) shape = (void**)m->scene->shapeAnimations[m->animationIndex];
            else shape = 0;
            if (m->flags & 0x80000000) {
                s32 i;
                for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjSetFlags(m->partAnimations[i].animation, 0x10000);
            }
            _jobjAddAnimAll__FP9_HSD_JObjP14_HSD_AnimJointP17_HSD_MatAnimJointP19_HSD_ShapeAnimJoint(joint, m->scene->animations[m->animationIndex], 0, (HSD_ShapeAnimJoint*)shape);
            if ((m->flags & 0x20000000) && joint->aobj) HSD_JObjRemoveAnim(joint);
            m->endFrame = 0.0f;
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelGetEndFrame, AOBJ_ARG_AV, &m->endFrame);
            HSD_AObj* aobj = 0;
            HSD_ForeachAnim(joint, JOBJ_TYPE, (HSD_TypeMask)0x20, (void*)_modelGetAObjFunc__FP9_HSD_AObjPv, AOBJ_ARG_AV, &aobj);
            m->animation = aobj;
            if (m->flags & 0x80000000) {
                s32 i;
                for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjClearFlags(m->partAnimations[i].animation, 0x10000);
            }
        }
        GSmodelSetAnimFrame(m, 0.0f);
        modelSetAnimTypeInline(m, m->animationType);
        GSmodelSetAnimRate(m, rate);
        if (!(m->flags & 0x80000000)) {
            m->partAnimations[0].animation = 0;
            m->partAnimations[1].animation = 0;
            m->partAnimations[2].animation = 0;
            m->partAnimations[3].animation = 0;
            m->partAnimations[4].animation = 0;
            m->partAnimations[5].animation = 0;
            m->partAnimations[6].animation = 0;
            m->partAnimations[7].animation = 0;
        }
        GSboundSetAnimIndex((GSbound*)m->boundStorage, index);
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimIndex(m, index);
    GSmodelForceAnimTransformUpdate(m);
}

extern "C" void GSmodelRemoveNull(GSmodel*);
extern "C" void GSmodelSetAnimBlend(GSmodel* m, u32 first, u32 second) {
    f32 zero[3];
    HSD_AObj* aobj;
    HSD_AObj* blendAObj;
    if (m->flags & 4) {
        if (first > m->animationCount || second > m->animationCount) return;
        if ((m->flags & 0x20000) == 0x20000) GSmodelRemoveNull(m);
        u8 firstNull = GSmodelIsNullAnimation(m, first);
        u8 secondNull = GSmodelIsNullAnimation(m, second);
        if (firstNull != 1 || secondNull != 1) {
            f32 rate;
            if (m->flags & 0x80) rate = m->blendRate;
            else rate = m->animationRate;
            if (GSgfxVideoGetVsyncRate() == 50) rate /= 1.2f;
            m->flags |= 0x80;
            m->animationIndex = first;
            m->blendIndex = second;
            m->blendFactor = 0.0f;
            HSD_JObjAddAnimAll(m->joint, m->scene->animations[m->animationIndex], 0, 0);
            HSD_JObjAddAnimAll(m->animationBlendJoint, m->scene->animations[m->blendIndex], 0, 0);
            HSD_JObjReqAnimAllByFlags(m->joint, 0x1cb, 0.0f);
            HSD_JObjReqAnimAllByFlags(m->animationBlendJoint, 0x1cb, 0.0f);
            HSD_JObjAnimAll(m->joint);
            HSD_JObjAnimAll(m->animationBlendJoint);
            m->endFrame = 0.0f;
            HSD_ForeachAnim(m->joint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelGetEndFrame, AOBJ_ARG_AV, &m->endFrame);
            m->blendEndFrame = 0.0f;
            HSD_ForeachAnim(m->animationBlendJoint, JOBJ_TYPE, (HSD_TypeMask)0x9b2f, (void*)_modelGetEndFrame, AOBJ_ARG_AV, &m->blendEndFrame);
            aobj = 0;
            HSD_ForeachAnim(m->joint, JOBJ_TYPE, (HSD_TypeMask)0x20, (void*)_modelGetAObjFunc__FP9_HSD_AObjPv, AOBJ_ARG_AV, &aobj);
            m->animation = aobj;
            blendAObj = 0;
            HSD_ForeachAnim(m->animationBlendJoint, JOBJ_TYPE, (HSD_TypeMask)0x20, (void*)_modelGetAObjFunc__FP9_HSD_AObjPv, AOBJ_ARG_AV, &blendAObj);
            m->blendAnimation = blendAObj;
            GSmodelSetAnimRate(m, rate);
            modelSetAnimTypeInline(m, m->animationType);
            GSmodelSetAnimFrame(m, 0.0f);
            zero[0] = 0.0f; zero[1] = 0.0f; zero[2] = 0.0f;
            HSD_JObjSetTranslate(m->joint, (GSvec*)zero);
            HSD_JObjSetRotationX(m->joint, zero[0]);
            HSD_JObjSetRotationY(m->joint, zero[1]);
            HSD_JObjSetRotationZ(m->joint, zero[2]);
            zero[0] = 1.0f; zero[1] = 1.0f; zero[2] = 1.0f;
            HSD_JObjSetScale(m->joint, (GSvec*)zero);
        } else {
            return;
        }
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimIndex(m, second);
    GSmodelForceAnimTransformUpdate(m);
}
