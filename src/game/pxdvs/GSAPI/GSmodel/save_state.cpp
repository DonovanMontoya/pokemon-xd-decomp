#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
extern "C" {
void GSmodelAddNull(GSmodel*, GSvec*, GSvec*, GSvec*);
void GSmodelSetAnimIndex(GSmodel*, u32);
void GSmodelSetAnimType(GSmodel*, s32);
f32 fn_800F2298(GSmodel*);
void __assert(const char*, int, const char*);
void GSmodelPopState(GSmodel* model, GSmodelState* state) {
    model->flags &= ~0x322962;
    model->flags |= state->flags;
    GSmodelSetPosition(model, &state->position);
    GSmodelSetRotation(model, &state->rotation);
    GSmodelSetScale(model, &state->scale);
    if (state->flags & 0x20000) {
        model->flags ^= 0x20000;
        GSmodelAddNull(model, &state->rootPosition, &state->rootRotation, &state->rootScale);
    }
    model->animationIndex = -1;
    model->textureAnimationIndex = -1;
    GSmodelSetAnimIndex(model, state->animationIndex);
    GSmodelSetAnimFrame(model, state->animationFrame);
    GSmodelSetAnimRate(model, state->animationRate);
    GSmodelSetAnimType(model, state->animationType);
    GSmodelSetTexAnimIndex(model, state->textureAnimationIndex);
    GSmodelSetTexAnimFrame(model, state->textureAnimationFrame);
    GSmodelSetTexAnimRate(model, state->textureAnimationRate);
    GSmodelSetTexAnimType(model, state->textureAnimationType);
    if (state->flags & 0x20) GSmodelStartAnimation(model);
    if (state->flags & 0x40) GSmodelStartTexAnimation(model);
    modelApplyAnimation__FP8_GSmodel(model);
}
void GSmodelPushState(GSmodel* model, GSmodelState* state) {
    state->flags = model->flags & 0x322962;
    GSvec* value = GSmodelGetPositionPtr(model);
    state->position.param1 = value->param1; state->position.param2 = value->param2; state->position.param3 = value->param3;
    value = GSmodelGetRotationPtr(model);
    state->rotation.param1 = value->param1; state->rotation.param2 = value->param2; state->rotation.param3 = value->param3;
    value = GSmodelGetScalePtr(model);
    state->scale.param1 = value->param1; state->scale.param2 = value->param2; state->scale.param3 = value->param3;
    state->animationIndex = model->animationIndex;
    state->textureAnimationIndex = model->textureAnimationIndex;
    state->animationFrame = model->animationFrame;
    state->animationRate = GSmodelGetAnimRate(model);
    state->animationType = model->animationType;
    state->textureAnimationFrame = model->textureAnimationFrame;
    state->textureAnimationRate = fn_800F2298(model);
    state->textureAnimationType = model->textureAnimationType;
    if (state->flags & 0x20000) {
        HSD_JObj* joint = model->joint->child;
        if (!joint) __assert("jobj.h", 996, "jobj");
        if (!&state->rootPosition) __assert("jobj.h", 997, "translate");
        state->rootPosition.param1 = joint->translate.x; state->rootPosition.param2 = joint->translate.y; state->rootPosition.param3 = joint->translate.z;
        if (!joint) __assert("jobj.h", 748, "jobj");
        state->rootRotation.param1 = joint->rotate.x;
        if (!joint) __assert("jobj.h", 762, "jobj");
        state->rootRotation.param2 = joint->rotate.y;
        if (!joint) __assert("jobj.h", 776, "jobj");
        state->rootRotation.param3 = joint->rotate.z;
        if (!joint) __assert("jobj.h", 849, "jobj");
        if (!&state->rootScale) __assert("jobj.h", 850, "scale");
        state->rootScale.param1 = joint->scale.x; state->rootScale.param2 = joint->scale.y; state->rootScale.param3 = joint->scale.z;
    }
}
}
