#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
#include <game/maximum/GSAPI/baselib/dobj.h>
#include <libc/string.h>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
extern "C" {
void* GSmemAlloc(u32);
void GSmodelUpdate(GSmodel*);
u8 GSmodelIsBlending(GSmodel*);
void GSlogWrite(const char*, ...);
void HSD_JObjWalkTree(HSD_JObj*, void (*)(HSD_JObj*, void**, s32), void**);
}
extern "C" {
static void _partFindShapeAnimCB__FP19_HSD_ShapeAnimJointPPvi(HSD_ShapeAnimJoint* node, void**, s32);
static void _partFindMatAnimCB__FP17_HSD_MatAnimJointPPvi(HSD_MatAnimJoint* node, void**, s32);
static void _partFindAnimCB__FP14_HSD_AnimJointPPvi(HSD_AnimJoint* node, void**, s32);
static void _partFindJObjCB__FP9_HSD_JObjPPvi(HSD_JObj* joint, void**, s32);
static void _partFindIndexCB__FP9_HSD_JObjPPvi(HSD_JObj* joint, void**, s32);
}

static GSpart* _partStructList;
static u32 _partStructCount;
static u8 _partFound;
static u32 _partToFindIdx, _partFindCurIdx;
static HSD_ShapeAnimJoint* _partFoundShapeAnim;
static HSD_MatAnimJoint* _partFoundMatAnim;
static HSD_AnimJoint* _partFoundAnim;
static HSD_JObj* _partFoundJObj;
static HSD_JObj* _partToFindJObj;
static u32 _partFoundIndex;
extern "C" {
static void _partShapeAnimWalkTree0__FP19_HSD_ShapeAnimJointPFP19_HSD_ShapeAnimJointPPvi_vPPv(HSD_ShapeAnimJoint* node, GSpartShapeAnimCallback callback, void** data);

#pragma dont_inline on
void GSpartShapeAnimWalkTree(HSD_ShapeAnimJoint* node, GSpartShapeAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 0);
        HSD_ShapeAnimJoint* child = node->child;
        while (child) {
            _partShapeAnimWalkTree0__FP19_HSD_ShapeAnimJointPFP19_HSD_ShapeAnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
#pragma dont_inline reset
#pragma dont_inline on
HSD_ShapeAnimJoint* GSpartGetShapeAnimPtr(HSD_ShapeAnimJoint* node, u32 index) {
    if (index == 0) return node;
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundShapeAnim = 0;
    GSpartShapeAnimWalkTree(node, _partFindShapeAnimCB__FP19_HSD_ShapeAnimJointPPvi, 0);
    return _partFoundShapeAnim;
}
#pragma dont_inline reset

}

extern "C" {
static void _partMatAnimWalkTree0__FP17_HSD_MatAnimJointPFP17_HSD_MatAnimJointPPvi_vPPv(HSD_MatAnimJoint* node, GSpartMatAnimCallback callback, void** data);

#pragma dont_inline on
void GSpartMatAnimWalkTree(HSD_MatAnimJoint* node, GSpartMatAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 0);
        HSD_MatAnimJoint* child = node->child;
        while (child) {
            _partMatAnimWalkTree0__FP17_HSD_MatAnimJointPFP17_HSD_MatAnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
#pragma dont_inline reset
#pragma dont_inline on
HSD_MatAnimJoint* GSpartGetMatAnimPtr(HSD_MatAnimJoint* node, u32 index) {
    if (index == 0) return node;
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundMatAnim = 0;
    GSpartMatAnimWalkTree(node, _partFindMatAnimCB__FP17_HSD_MatAnimJointPPvi, 0);
    return _partFoundMatAnim;
}
#pragma dont_inline reset

}

extern "C" {
static void _partAnimWalkTree0__FP14_HSD_AnimJointPFP14_HSD_AnimJointPPvi_vPPv(HSD_AnimJoint* node, GSpartAnimCallback callback, void** data);

#pragma dont_inline on
void GSpartAnimWalkTree(HSD_AnimJoint* node, GSpartAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 0);
        HSD_AnimJoint* child = node->child;
        while (child) {
            _partAnimWalkTree0__FP14_HSD_AnimJointPFP14_HSD_AnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
#pragma dont_inline reset
#pragma dont_inline on
HSD_AnimJoint* GSpartGetAnimPtr(HSD_AnimJoint* node, u32 index) {
    if (index == 0) return node;
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundAnim = 0;
    GSpartAnimWalkTree(node, _partFindAnimCB__FP14_HSD_AnimJointPPvi, 0);
    return _partFoundAnim;
}
#pragma dont_inline reset

}
extern "C" {


#pragma dont_inline on
HSD_JObj* GSpartGetJObjPtr(HSD_JObj* joint, u32 index) {
    if (index == 0) return joint;
    _partFound = 0;
    _partToFindIdx = index;
    _partFindCurIdx = 0;
    _partFoundJObj = 0;
    HSD_JObjWalkTree(joint, _partFindJObjCB__FP9_HSD_JObjPPvi, 0);
    return _partFoundJObj;
}
#pragma dont_inline reset
#pragma dont_inline on
u32 GSpartGetJObjIndex(HSD_JObj* root, HSD_JObj* joint) {
    if (root == joint) return 0;
    _partFound = 0;
    _partToFindJObj = joint;
    _partFindCurIdx = 0;
    _partFoundIndex = -1;
    HSD_JObjWalkTree(root, _partFindIndexCB__FP9_HSD_JObjPPvi, 0);
    return _partFoundIndex;
}
#pragma dont_inline reset
void GSpartGetMatrix(GSpart* part, Mtx matrix) {
    HSD_JObj* joint = part->joint;
    if (matrix) {
        GSmodelUpdate(part->model);
        PSMTXCopy(HSD_JObjGetMtxPtr(joint), matrix);
    }
}
static inline HSD_JObj* partGetParent(HSD_JObj* joint) { return joint ? joint->parent : 0; }
static inline f32 partGetJointRotationX(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 748, "jobj"); return joint->rotate.x; }
static inline f32 partGetJointRotationY(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 762, "jobj"); return joint->rotate.y; }
static inline f32 partGetJointRotationZ(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 776, "jobj"); return joint->rotate.z; }
static inline f32 partGetJointScaleX(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 899, "jobj"); return joint->scale.x; }
static inline f32 partGetJointScaleY(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 911, "jobj"); return joint->scale.y; }
static inline f32 partGetJointScaleZ(HSD_JObj* joint) { if (!joint) __assert("jobj.h", 923, "jobj"); return joint->scale.z; }
void GSpartGetTransform(GSpart* part, Vec* position, Vec* rotation, Vec* scale) {
    Vec localRotation, totalRotation;
    f32 scaleX, scaleY, scaleZ;
    f32 x, y, z;
    static HSD_JObj* parentList[24];
    HSD_JObj* joint = part->joint;
    u32 count = 0;
    GSmodelUpdate(part->model);
    if (!GSmodelIsBlending(part->model)) {
        HSD_JObjSetupMatrix(joint);
        x = joint->mtx[0][3];
        y = joint->mtx[1][3];
        z = joint->mtx[2][3];
    } else if (joint->flags & 0x600000) {
        x = joint->translate.x;
        y = joint->translate.y;
        z = joint->translate.z;
    } else {
        x = joint->mtx[0][3];
        y = joint->mtx[1][3];
        z = joint->mtx[2][3];
    }
    if (rotation || scale) {
        while (joint) {
            parentList[count++] = joint;
            joint = partGetParent(joint);
            if (count >= 24) {
                GSlogWrite("GSpart: child node too deep\n");
                joint = 0;
            }
        }
        if (rotation) {
            totalRotation.x = 0.0f;
            totalRotation.y = 0.0f;
            totalRotation.z = 0.0f;
            HSD_JObj** parent = &parentList[count];
            for (u32 i = count; i; --i, --parent) {
                HSD_JObj* joint = parent[-1];
                localRotation.x = partGetJointRotationX(joint);
                localRotation.y = partGetJointRotationY(joint);
                localRotation.z = partGetJointRotationZ(joint);
                PSVECAdd(&totalRotation, &localRotation, &totalRotation);
            }
        }
        if (scale) {
            scaleX = 1.0f;
            scaleY = 1.0f;
            scaleZ = 1.0f;
            HSD_JObj** parent = &parentList[count];
            for (u32 i = count; i; --i, --parent) {
                HSD_JObj* joint = parent[-1];
                f32 x = partGetJointScaleX(joint);
                f32 y = partGetJointScaleY(joint);
                f32 z = partGetJointScaleZ(joint);
                scaleX *= x;
                scaleY *= y;
                scaleZ *= z;
            }
        }
    }
    if (position) { position->x = x; position->y = y; position->z = z; }
    if (rotation) *rotation = totalRotation;
    if (scale) { scale->x = scaleX; scale->y = scaleY; scale->z = scaleZ; }
}
static inline s32 partJointHasMaterials(HSD_JObj* joint) { return (joint->flags & 0x4020) ? 0 : 1; }
static inline HSD_MObj* partFindMaterial(HSD_DObj* dobj, u32 index, s32* count) {
    u32 i = 0;
    while (dobj) {
        if (i++ == index) {
            if (count) *count = -1;
            return dobj->mobj;
        }
        dobj = dobj->next;
    }
    if (count) *count = i;
    return 0;
}
void GSpartInitMaterial(GSpartMaterial* material, GSpart* part, u32 index) {
    material->object = 0;
    HSD_DObj* dobj = partJointHasMaterials(part->joint) ? part->joint->u.dobj : 0;
    if (dobj) material->object = partFindMaterial(dobj, index, 0);
}
static inline GSpartMaterial* partGetMaterialList(GSmodel* model) {
    return model ? model->materials : 0;
}
static inline u32 partGetMaterialListCount(GSmodel* model) {
    return model ? model->materialCount : 0;
}
GSpartMaterial* GSpartGetMaterial(GSpart* part, u32 index) {
    HSD_DObj* dobj = partJointHasMaterials(part->joint) ? part->joint->u.dobj : 0;
    if (!dobj) return 0;
    HSD_MObj* object = partFindMaterial(dobj, index, 0);
    if (!object) return 0;
    GSpartMaterial* list = partGetMaterialList(part->model);
    u32 count = partGetMaterialListCount(part->model);
    if (!list || !count) return 0;
    for (u32 i = 0; i < count; ++i, ++list) {
        if (list->object == object) return list;
    }
    return 0;
}
s32 GSpartGetMaterialCount(GSpart* part) {
    HSD_DObj* dobj = partJointHasMaterials(part->joint) ? part->joint->u.dobj : 0;
    if (!dobj) return 0;
    s32 count;
    partFindMaterial(dobj, -1, &count);
    return count;
}
void GSpartFree(GSpart* part) { part->inUse = 0; }
static inline GSpart* partFindFree() {
    GSpart* part = _partStructList;
    for (u32 i = 0; i < _partStructCount; ++i, ++part) {
        if (!part->inUse) return part;
    }
    return 0;
}
GSpart* GSpartCreate() {
    GSpart* part = partFindFree();
    if (!part) return 0;
    part->inUse = 1;
    return part;
}
void GSpartInit(u32 count) {
    _partStructCount = count;
    _partStructList = (GSpart*)GSmemAlloc(count * sizeof(GSpart));
    if (_partStructList) {
        for (u32 i = 0; i < _partStructCount; ++i) _partStructList[i].inUse = 0;
    }
}
}

extern "C" {
static void _partShapeAnimWalkTree0__FP19_HSD_ShapeAnimJointPFP19_HSD_ShapeAnimJointPPvi_vPPv(HSD_ShapeAnimJoint* node, GSpartShapeAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 1);
        HSD_ShapeAnimJoint* child = node->child;
        while (child) {
            _partShapeAnimWalkTree0__FP19_HSD_ShapeAnimJointPFP19_HSD_ShapeAnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
static void _partMatAnimWalkTree0__FP17_HSD_MatAnimJointPFP17_HSD_MatAnimJointPPvi_vPPv(HSD_MatAnimJoint* node, GSpartMatAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 1);
        HSD_MatAnimJoint* child = node->child;
        while (child) {
            _partMatAnimWalkTree0__FP17_HSD_MatAnimJointPFP17_HSD_MatAnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
static void _partAnimWalkTree0__FP14_HSD_AnimJointPFP14_HSD_AnimJointPPvi_vPPv(HSD_AnimJoint* node, GSpartAnimCallback callback, void** data) {
    if (node) {
        if (callback) callback(node, data, 1);
        HSD_AnimJoint* child = node->child;
        while (child) {
            _partAnimWalkTree0__FP14_HSD_AnimJointPFP14_HSD_AnimJointPPvi_vPPv(child, callback, data);
            child = child->next;
        }
    }
}
static void _partFindShapeAnimCB__FP19_HSD_ShapeAnimJointPPvi(HSD_ShapeAnimJoint* node, void**, s32) {
    if (_partFound != 1) {
        if (_partFindCurIdx == _partToFindIdx) {
            _partFoundShapeAnim = node;
            _partFound = 1;
        }
        ++_partFindCurIdx;
    }
}
static void _partFindMatAnimCB__FP17_HSD_MatAnimJointPPvi(HSD_MatAnimJoint* node, void**, s32) {
    if (_partFound != 1) {
        if (_partFindCurIdx == _partToFindIdx) {
            _partFoundMatAnim = node;
            _partFound = 1;
        }
        ++_partFindCurIdx;
    }
}
static void _partFindAnimCB__FP14_HSD_AnimJointPPvi(HSD_AnimJoint* node, void**, s32) {
    if (_partFound != 1) {
        if (_partFindCurIdx == _partToFindIdx) {
            _partFoundAnim = node;
            _partFound = 1;
        }
        ++_partFindCurIdx;
    }
}
static void _partFindJObjCB__FP9_HSD_JObjPPvi(HSD_JObj* joint, void**, s32) {
    if (_partFound != 1) {
        if (_partFindCurIdx == _partToFindIdx) {
            _partFoundJObj = joint;
            _partFound = 1;
        }
        ++_partFindCurIdx;
    }
}
static void _partFindIndexCB__FP9_HSD_JObjPPvi(HSD_JObj* joint, void**, s32) {
    if (_partFound != 1) {
        if (_partToFindJObj == joint) {
            u32 foundIndex = _partFindCurIdx;
            _partFound = 1;
            _partFoundIndex = foundIndex;
        }
        ++_partFindCurIdx;
    }
}
}

extern "C" {
u8 GSmodelCanAnimate(GSmodel*);
u8 GSmodelCanShapeAnimate(GSmodel*);
u32 GSmodelGetMaxAnimIndex(GSmodel*);
void HSD_JObjRemoveAnim(HSD_JObj*);
void HSD_JObjAddAnim(HSD_JObj*, HSD_AnimJoint*, HSD_MatAnimJoint*, HSD_ShapeAnimJoint*);
void HSD_JObjReqAnim(HSD_JObj*, f32);
s32 GSpartSetAnimIndex(GSpart* part, s32 index, s32 mode, f32 frame) {
    GSmodel* model = part->model;
    HSD_JObj* joint = part->joint;
    if (index < 0) return -1;
    if (!GSmodelCanAnimate(model)) return -1;
    if ((u32)index >= GSmodelGetMaxAnimIndex(model)) return -1;
    GSmodelPartAnimation* slot = model->partAnimations;
    s32 slotIndex;
    for (slotIndex = 0; slotIndex < 8; ++slotIndex, ++slot) {
        if (!slot->animation) break;
    }
    if (slotIndex >= 8) return -1;
    HSD_AnimJoint* animation = GSpartGetAnimPtr(model->scene->animations[index], part->index);
    HSD_ShapeAnimJoint* shape;
    if (GSmodelCanShapeAnimate(model)) shape = GSpartGetShapeAnimPtr(model->scene->shapeAnimations[index], part->index);
    else shape = 0;
    if (!animation && !shape) return -1;
    if (!shape && !animation->aobjdesc) return -1;
    HSD_JObjRemoveAnim(joint);
    HSD_JObjAddAnim(joint, animation, 0, shape);
    HSD_JObjReqAnim(joint, frame);
    HSD_AObj* aobj = joint->aobj;
    if (!aobj) return -1;
    slot->animation = aobj;
    slot->mode = mode;
    slot->animationIndex = index;
    slot->rate = model->animationRate;
    slot->frame = frame;
    slot->requestedFrame = slot->frame;
    slot->endFrame = aobj->end_frame;
    switch (slot->mode) {
    case 0: HSD_AObjClearFlags(slot->animation, AOBJ_LOOP); break;
    case 1: HSD_AObjSetFlags(slot->animation, AOBJ_LOOP); break;
    }
    model->partAnimationChanged = 1;
    return slotIndex;
}
void GSpartStopAnimIndex(GSpart* part, s32 index) {
    GSmodel* model = part->model;
    if (index >= 0) {
        if (index >= 8) return;
        GSmodelPartAnimation* slot = &model->partAnimations[index];
        if (slot->animation) {
            slot->animation = 0;
            model->partAnimations[GSpartSetAnimIndex(part, 0, 1, 0.0f)].animation = 0;
        }
    }
}
}

extern "C" {
void HSD_TObjRemoveAnim(HSD_TObj*);
void HSD_TObjAddAnim(HSD_TObj*, HSD_TexAnim*);
void HSD_TObjReqAnim(HSD_TObj*, f32);
s32 GSpartSetTexAnimIndex(GSpart* part, s32 materialIndex, s32 animationIndex, s32 mode, f32 frame) {
    GSmodel* model = part->model;
    if (materialIndex < 0 || animationIndex < 0) return -1;
    if (!GSmodelCanTexAnimate(model)) return -1;
    if ((u32)animationIndex >= GSmodelGetMaxTexAnimIndex(model)) return -1;
    GSmodelPartAnimation* slot = model->partTextureAnimations;
    s32 slotIndex;
    for (slotIndex = 0; slotIndex < 4; ++slotIndex, ++slot) {
        if (!slot->animation) break;
    }
    if (slotIndex >= 4) return -1;
    HSD_MatAnimJoint* node = GSpartGetMatAnimPtr(model->scene->materialAnimations[animationIndex], part->index);
    if (!node) return -1;
    HSD_MatAnim* animation = node->animations;
    s32 remaining = materialIndex;
    while (remaining--) {
        animation = animation->next;
        if (!animation) return -1;
    }
    GSpartMaterial* material = GSpartGetMaterial(part, materialIndex);
    if (!material) return -1;
    HSD_TObj* texture = material->object->tobj;
    if (!texture) return -1;
    HSD_TObjRemoveAnim(texture);
    HSD_TObjAddAnim(texture, (HSD_TexAnim*)animation->texanim);
    HSD_TObjReqAnim(texture, frame);
    HSD_AObj* aobj = texture->aobj;
    slot->animation = aobj;
    slot->mode = mode;
    slot->animationIndex = animationIndex;
    slot->rate = model->textureAnimationRate;
    slot->frame = frame;
    slot->requestedFrame = slot->frame;
    slot->endFrame = aobj->end_frame;
    switch (slot->mode) {
    case 0: HSD_AObjClearFlags(slot->animation, AOBJ_LOOP); break;
    case 1: HSD_AObjSetFlags(slot->animation, AOBJ_LOOP); break;
    }
    model->partTextureAnimationChanged = 1;
    return slotIndex;
}
void GSpartUnregisterAnimMix(GSpart* part, s32 identifier) {
    GSmodel* model = part->model;
    for (s32 i = 0; i < 16; ++i) {
        GSmodelPartAnimMix* mix = &model->partAnimMixes[i];
        if (mix->identifier && mix->identifier == identifier && mix->partIndex == part->index) {
            mix->identifier = 0;
            return;
        }
    }
}
static inline GSmodelPartAnimMix* partFindFreeMix(GSpart* part, s32 identifier) {
    GSmodel* model = part->model;
    for (s32 i = 0; i < 16; ++i) {
        GSmodelPartAnimMix* mix = &model->partAnimMixes[i];
        if (mix->identifier && mix->identifier == identifier && mix->partIndex == part->index) return 0;
    }
    for (s32 i = 0; i < 16; ++i) {
        GSmodelPartAnimMix* mix = &model->partAnimMixes[i];
        if (!mix->identifier) return mix;
    }
    return 0;
}
void GSpartRegisterAnimMix(GSpart* part, s32 identifier, s32 animationIndex, u32 flags, s32 mode) {
    if (!identifier || !flags) return;
    GSmodelPartAnimMix* mix = partFindFreeMix(part, identifier);
    if (!mix) return;
    mix->identifier = identifier;
    mix->partIndex = part->index;
    mix->flags = flags;
    mix->mode = mode;
    mix->animationIndex = animationIndex;
    HSD_JObj* joint = part->joint;
    if (!joint) __assert("jobj.h", 996, "jobj");
    if (&mix->position == 0) __assert("jobj.h", 997, "translate");
    mix->position.param1 = joint->translate.x;
    mix->position.param2 = joint->translate.y;
    mix->position.param3 = joint->translate.z;
    joint = part->joint;
    if (!joint) __assert("jobj.h", 733, "jobj");
    HSD_Quaternion rotation = joint->rotate;
    joint = part->joint;
    if (!joint) __assert("jobj.h", 849, "jobj");
    if (&mix->scale == 0) __assert("jobj.h", 850, "scale");
    mix->scale.param1 = joint->scale.x;
    mix->scale.param2 = joint->scale.y;
    mix->scale.param3 = joint->scale.z;
    mix->rotation.param1 = rotation.x;
    mix->rotation.param2 = rotation.y;
    mix->rotation.param3 = rotation.z;
}
}
