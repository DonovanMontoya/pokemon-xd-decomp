#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <game/maximum/GSAPI/baselib/jobj.h>
extern "C" {
void GSgfxRenderWaitForDrawComplete__Fv();
void HSD_JObjUnref(HSD_JObj*);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void HSD_JObjSetFlags(HSD_JObj*, u32);
void HSD_JObjClearFlags(HSD_JObj*, u32);
void HSD_JObjSetMtxDirtySub(HSD_JObj*);
void HSD_JObjAnim(HSD_JObj*);
void modelCalculatePartMix__FP5GSvecP5GSvecUl(GSvec*, GSvec*, u32);
}
static inline void dirtyJoint(HSD_JObj* joint) {
    if (!(joint->flags & 0x2000000)) {
        if (joint && !(u8)HSD_JObjMtxIsDirty(joint)) HSD_JObjSetMtxDirtySub(joint);
    }
}
static inline void getTranslation(HSD_JObj* joint, GSvec* out) {
    if (!joint) __assert("jobj.h", 996, "jobj");
    out->param1 = joint->translate.x; out->param2 = joint->translate.y; out->param3 = joint->translate.z;
}
static inline void getScale(HSD_JObj* joint, GSvec* out) {
    if (!joint) __assert("jobj.h", 849, "jobj");
    out->param1 = joint->scale.x; out->param2 = joint->scale.y; out->param3 = joint->scale.z;
}
static inline void setTranslation(HSD_JObj* joint, GSvec* value) {
    if (!joint) __assert("jobj.h", 937, "jobj");
    joint->translate.x = value->param1; joint->translate.y = value->param2; joint->translate.z = value->param3;
    dirtyJoint(joint);
}
static inline void setScale(HSD_JObj* joint, GSvec* value) {
    if (!joint) __assert("jobj.h", 790, "jobj");
    joint->scale.x = value->param1; joint->scale.y = value->param2; joint->scale.z = value->param3;
    dirtyJoint(joint);
}
static inline void interpolate(GSvec* a, GSvec* b, GSvec* out, f32 factor, f32 inverse) {
    out->param1 = a->param1 * inverse + b->param1 * factor;
    out->param2 = a->param2 * inverse + b->param2 * factor;
    out->param3 = a->param3 * inverse + b->param3 * factor;
}
#pragma fp_contract off
extern "C" void modelIntpJObjRotate__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(HSD_JObj* a, HSD_JObj* b, HSD_JObj* out, f32 factor, GSvec* mix, u32 flags) {
    GSvec ea, eb;
    HSD_Quaternion result, qa, qb;
    if (!a) __assert("jobj.h", 733, "jobj");
    qa = a->rotate;
    if (!b) __assert("jobj.h", 733, "jobj");
    qb = b->rotate;
    ea.param1 = qa.x; ea.param2 = qa.y; ea.param3 = qa.z;
    eb.param1 = qb.x; eb.param2 = qb.y; eb.param3 = qb.z;
    if (mix) { modelCalculatePartMix__FP5GSvecP5GSvecUl(&ea, mix, flags); modelCalculatePartMix__FP5GSvecP5GSvecUl(&eb, mix, flags); }
    EulerToQuat((HSD_Vec3*)&ea, &qa); EulerToQuat((HSD_Vec3*)&eb, &qb);
    f32 dy = qa.y - qb.y, sy = qa.y + qb.y;
    f32 dx = qa.x - qb.x, sx = qa.x + qb.x;
    f32 dz = qa.z - qb.z, sz = qa.z + qb.z;
    f32 dw = qa.w - qb.w, sw = qa.w + qb.w;
    if (dw*dw + (dz*dz + (dx*dx + dy*dy)) > sw*sw + (sz*sz + (sx*sx + sy*sy))) {
        qb.x = -qb.x; qb.y = -qb.y; qb.z = -qb.z; qb.w = -qb.w;
    }
    QuatSlerp(&qa, &qb, &result, factor);
    if (!out) __assert("jobj.h", 656, "jobj");
    out->rotate = result;
    dirtyJoint(out);
}
#pragma fp_contract on
extern "C" void modelIntpJObjScale__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(HSD_JObj* a, HSD_JObj* b, HSD_JObj* out, f32 factor, GSvec* mix, u32 flags) {
    f32 inverse = 1.0f - factor;
    GSvec va, vb, value;
    getScale(a, &va); getScale(b, &vb);
    interpolate(&va, &vb, &value, factor, inverse);
    if (mix) modelCalculatePartMix__FP5GSvecP5GSvecUl(&value, mix, flags);
    setScale(out, &value);
}
extern "C" void modelIntpJObjTrans__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(HSD_JObj* a, HSD_JObj* b, HSD_JObj* out, f32 factor, GSvec* mix, u32 flags) {
    f32 inverse = 1.0f - factor;
    GSvec va, vb, value;
    getTranslation(a, &va); getTranslation(b, &vb);
    interpolate(&va, &vb, &value, factor, inverse);
    if (mix) modelCalculatePartMix__FP5GSvecP5GSvecUl(&value, mix, flags);
    setTranslation(out, &value);
}
extern "C" {
static void _modelIntpJObj__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjf(HSD_JObj* a, HSD_JObj* b, HSD_JObj* out, f32 factor) {
    f32 inverse = 1.0f - factor;
    GSvec va, vb, value;
    getTranslation(a, &va); getTranslation(b, &vb);
    interpolate(&va, &vb, &value, factor, inverse); setTranslation(out, &value);
    getScale(a, &va); getScale(b, &vb);
    interpolate(&va, &vb, &value, factor, inverse); setScale(out, &value);
    modelIntpJObjRotate__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjfP5GSvecUl(a, b, out, factor, 0, 0);
}
static void _modelIntpJObjAll__FP8_GSmodelP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjff(GSmodel* model, HSD_JObj* a, HSD_JObj* b, HSD_JObj* out, f32 factor, f32 rate) {
    if (a && b && out) {
        u8 partAnimation = 0;
        if (out->aobj) {
            for (u32 i = 0; i < 8; ++i) if (model->partAnimations[i].animation == out->aobj) { partAnimation = 1; break; }
        }
        if (partAnimation) {
            HSD_JObjClearFlags(out, 0x20000); HSD_AObjSetRate(out->aobj, rate); HSD_JObjAnim(out);
        } else _modelIntpJObj__FP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjf(a, b, out, factor);
        if (!(a->flags & 0x1000)) {
            a = a->child; b = b->child; out = out->child;
            while (a) {
                _modelIntpJObjAll__FP8_GSmodelP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjff(model, a, b, out, factor, rate);
                a = a->next; b = b->next; out = out->next;
            }
        }
    }
}
static void _modelSetRotateEulerToQuatAll__FP9_HSD_JObj(HSD_JObj* joint) {
    if (joint) {
        HSD_JObjSetFlags(joint, 0x20000);
        if (!(joint->flags & 0x1000)) {
            for (HSD_JObj* child = joint->child; child; child = child->next) _modelSetRotateEulerToQuatAll__FP9_HSD_JObj(child);
        }
    }
}
void GSmodelDisableAnimBlend(GSmodel* model) {
    f32 rate = GSmodelGetAnimRate(model);
    model->flags &= ~0x80;
    if (model->blendJoint) {
        GSmodelSetAnimRate(model, rate); GSgfxRenderWaitForDrawComplete__Fv();
        HSD_JObjUnref(model->animationBlendJoint); HSD_JObjUnref(model->blendJoint);
        model->animationBlendJoint = 0; model->blendJoint = 0;
    }
}
void GSmodelEnableAnimBlend(GSmodel* model) {
    if (!model->blendJoint) {
        model->animationBlendJoint = HSD_JObjLoadJoint(model->scene->joint);
        model->blendJoint = HSD_JObjLoadJoint(model->scene->joint);
        _modelSetRotateEulerToQuatAll__FP9_HSD_JObj(model->blendJoint);
    }
}
void modelCalculateBlendModel__FP8_GSmodelf(GSmodel* model, f32 rate) {
    if (model->blendJoint) {
        _modelIntpJObjAll__FP8_GSmodelP9_HSD_JObjP9_HSD_JObjP9_HSD_JObjff(model, model->joint, model->animationBlendJoint, model->blendJoint, model->blendFactor, rate);
        model->flags &= ~0x200;
    }
}
}
