#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
extern "C" {
extern GSmodel* _modelTopPtr;
u8 GSgfxVideoGetVsyncRate();
u32 GSgfxPerfbarCPUEntry(u32);
void HSD_JObjReqAnimAllByFlags(HSD_JObj*, u32, f32);
void __assert(const char*, u32, const char*);
void GSpartAnimWalkTree(HSD_AnimJoint*, void (*)(HSD_AnimJoint*, void**, s32), void**);
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
    if (!(m->flags & 4)) return;
    if (!(m->flags & 0x80)) return;
    if (blend < 0.0f) blend = 0.0f; else if (blend > 1.0f) blend = 1.0f;
    m->blendFactor = blend;
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
    if (rate >= 0.0f && classifyAnimationFrame(rate) != 1) {
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
    if (frame >= 0.0f && classifyAnimationFrame(frame) != 1) {
    if (m->flags & 4) {
        if (!(m->flags & 0x80)) {
            HSD_JObj* joint = m->joint;
            if ((m->flags & 0x20000) == 0x20000) joint = joint->child;
            m->animationFrame = frame; m->requestedFrame = m->animationFrame;
            if (m->flags & 0x80000000) {
                for (s32 i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjSetFlags(m->partAnimations[i].animation, 0x10000);
            }
            HSD_JObjReqAnimAllByFlags(joint, 0x1cb, m->requestedFrame);
            HSD_JObjAnimAll(joint);
            if (m->flags & 0x80000000) {
                for (s32 i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjClearFlags(m->partAnimations[i].animation, 0x10000);
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

extern "C" void GSmodelSetAnimType(GSmodel* m, s32 type) {
    if (m->flags & 4) {
        s32 i;
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
            for (i = 0; i < 8; ++i) if (m->partAnimations[i].animation) HSD_AObjClearFlags(m->partAnimations[i].animation, 0x10000);
        }
    }
    if (m->flags & 0x2000) GSmodelSetTexAnimType(m, type);
}
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
