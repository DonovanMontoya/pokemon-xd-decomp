#include <game/pxdvs/app/wazaSequence/leaffxPrivate.hpp>
void operator delete(void *);
typedef f32 LeafMtx[3][4];
extern "C" {
f32 HSD_Randf();
double sin(double);
double cos(double);
void GSmodelSetVisibility(GSmodel *, u8);
void GSmodelFree(GSmodel *);
GSmodel *GSmodelClone(GSmodel *);
void GSmodelSetMatrix(GSmodel *, LeafMtx);
void GSmaterialSetAlpha(GSmaterial *, f32);
void GSmemFree(void *);
void *GSmemAllocClr(u32);
void GSlogWrite(const char *, ...);
u8 GSgfxVideoGetVsyncRate();
u32 __cvt_fp2unsigned(f32);
void GSbezierCalculateVector(GSvec *, leafData *, f32);
void C_QUATSlerp(LeafQuat *, LeafQuat *, LeafQuat *, f32);
void C_QUATRotAxisRad(LeafQuat *, GSvec *, f32);
void PSMTXQuat(LeafMtx, LeafQuat *);
void PSMTXScaleApply(LeafMtx, LeafMtx, f32, f32, f32);
void PSMTXTransApply(LeafMtx, LeafMtx, f32, f32, f32);
void PSVECSubtract(GSvec *, GSvec *, GSvec *);
void PSVECNormalize(GSvec *, GSvec *);
void PSVECScale(GSvec *, GSvec *, f32);
void PSVECAdd(GSvec *, GSvec *, GSvec *);
u32 wazaSequenceSysGetResID();
void loadModel(u32, u32, u32, u32);
void GSresFreeResource(u32, u32);
void GSresIsUniqueID(u32, u32, u32);
void *GSresGetResource(u32, u32);
}

static inline void setModelAlpha(GSmodel *model, f32 alpha) {
    u32 count = model ? model->materialCount : 0;
    GSmaterial *material = model ? model->materials : 0;
    for (u32 i = 0; i < count; i++, material++) {
        GSmaterialSetAlpha(material, alpha);
    }
}

leafEffect::~leafEffect() {
    Stop();
    if (resourceId) GSresFreeResource(20000, resourceId);
}

void leafEffect::_stop() {
    if (leaves) {
        u32 i = 0;
        leafData *leaf = leaves;
        for (; i < leafCount; i++, leaf++) {
            if (leaf->model) {
                GSmodelSetVisibility(leaf->model, 0);
                GSmodelFree(leaf->model);
                leaf->model = 0;
            }
        }
        setModelAlpha(model, 1.0f);
        GSmemFree(leaves);
    }
}

bool leafEffect::_update(f32 delta) {
    if (!model) return false;
    elapsed += delta;
    if (elapsed >= duration) return false;
    f32 step = value34 * (f32)(u32)(delta * (f32)GSgfxVideoGetVsyncRate());
    if (elapsed < fallLimit) {
        step *= 2.0f - elapsed / fallLimit;
    } else {
        f32 fade = 1.0f - (elapsed - fallLimit) / (duration - fallLimit);
        setModelAlpha(model, fade);
    }
    u32 i = 0;
    leafData *leaf = leaves;
    for (; i < leafCount; i++, leaf++) {
        if (leaf->model) {
            leaf->progress += step;
            if (leaf->progress >= 1.0f) UpdateLeafData(leaf);
            GSvec position;
            GSbezierCalculateVector(&position, leaf, leaf->progress);
            if (position.param2 < 0.0f) {
                GSmodelSetVisibility(leaf->model, 0);
                GSmodelFree(leaf->model);
                leaf->model = 0;
            } else {
                GSmodel *target = leaf->model;
                f32 size = leaf->scale;
                LeafQuat rotation;
                C_QUATSlerp(&leaf->rotFrom, &leaf->rotTo, &rotation, leaf->progress);
                LeafMtx matrix;
                PSMTXQuat(matrix, &rotation);
                PSMTXScaleApply(matrix, matrix, size, size, size);
                PSMTXTransApply(matrix, matrix, position.param1, position.param2, position.param3);
                GSmodelSetMatrix(target, matrix);
            }
        }
    }
    return true;
}

bool leafEffect::_start() {
    if (leafCount > 0x20) leafCount = 0x20;
    if (!model) return false;
    leaves = (leafData *)GSmemAllocClr(leafCount * sizeof(leafData));
    if (!leaves) return false;
    leafData *leaf = leaves;
    elapsed = 0.0f;
    u32 i = 0;
    for (; i < leafCount; i++, leaf++) {
        GenerateLeafData(leaf);
    }
    return true;
}

leafEffect::leafEffect(u8 **cursor, f32 time) {
    sizeScale = 1.0f;
    elapsed = 0.0f;
    duration = time;
    origin.param1 = 0.0f;
    origin.param2 = 0.0f;
    origin.param3 = 0.0f;
    leafParams *params = (leafParams *)*cursor;
    leaves = 0;
    sizeBase = params->value[0];
    sizeRange = params->value[1];
    spreadBase = params->value[2];
    spreadRange = params->value[3];
    driftBase = params->value[4];
    driftRange = params->value[5];
    liftOffset = params->value[6];
    value34 = params->value[7];
    radialBase = params->value[8];
    radialRange = params->value[9];
    leafCount = (u16)params->leafCount;
    fallLimit = params->fallLimit;
    *cursor += 0x40;
    *cursor = (u8 *)(((u32)*cursor + 31) & ~31);
    resourceId = 0;
    u32 modelData = params->modelData;
    if (modelData) {
        resourceId = wazaSequenceSysGetResID();
        loadModel(modelData, 20000, 0, resourceId);
        GSresIsUniqueID(20000, resourceId, 0);
        model = (GSmodel *)GSresGetResource(20000, resourceId);
        if (model) GSmodelSetVisibility(model, 0);
    }
    *cursor += (params->trailingSize + 31) & ~31;
}

void leafEffect::UpdateLeafData(leafData *leaf) {
    leaf->progress -= 1.0f;
    leaf->rotFrom.x = leaf->rotTo.x;
    leaf->rotFrom.y = leaf->rotTo.y;
    leaf->rotFrom.z = leaf->rotTo.z;
    leaf->rotFrom.w = leaf->rotTo.w;
    f32 b;
    f32 a;
    a = 6.2831855f * HSD_Randf();
    b = 3.1415927f * HSD_Randf();
    f32 sinB = sin(b);
    f32 sinA = sin(a);
    f32 cosB = cos(b);
    f32 cosA = cos(a);
    GSvec axis;
    axis.param1 = sinB * cosA;
    axis.param2 = cosB;
    axis.param3 = sinB * sinA;
    C_QUATRotAxisRad(&leaf->rotTo, &axis, 6.2831855f * HSD_Randf());
    leaf->point0.param1 = leaf->point1.param1;
    leaf->point0.param2 = leaf->point1.param2;
    leaf->point0.param3 = leaf->point1.param3;
    leaf->point2.param1 = leaf->point3.param1;
    leaf->point2.param2 = leaf->point3.param2;
    leaf->point2.param3 = leaf->point3.param3;
    GSvec *p2 = &leaf->point2;
    PSVECSubtract(p2, &leaf->point1, p2);
    PSVECNormalize(p2, p2);
    f32 scale2 = driftBase + driftRange * (2.0f * HSD_Randf() - 1.0f);
    scale2 = scale2 * leaf->scale;
    PSVECScale(p2, p2, -scale2);
    PSVECAdd(p2, &leaf->point0, p2);
    {
    GSvec *p1 = &leaf->point1;
    f32 sinB1;
    f32 sinA1;
    f32 b1;
    f32 scale1;
    f32 a1;
    a1 = 6.2831855f * HSD_Randf();
    b1 = 3.1415927f * HSD_Randf();
    sinB1 = sin(b1);
    scale1 = spreadBase + spreadRange * (2.0f * HSD_Randf() - 1.0f);
    scale1 = scale1 * leaf->scale;
    sinA1 = sin(a1);
    f32 cosB1 = cos(b1);
    f32 cosA1 = cos(a1);
    p1->param1 = sinB1 * cosA1;
    p1->param2 = cosB1;
    p1->param3 = sinB1 * sinA1;
    PSVECScale(p1, p1, scale1);
    p1->param2 = p1->param2 + liftOffset;
    PSVECAdd(p1, &leaf->point0, p1);
    }
    {
    GSvec *p3 = &leaf->point3;
    f32 a3;
    f32 sinB3;
    f32 sinA3;
    f32 b3;
    f32 scale3;
    a3 = 6.2831855f * HSD_Randf();
    b3 = 3.1415927f * HSD_Randf();
    sinB3 = sin(b3);
    scale3 = driftBase + driftRange * (2.0f * HSD_Randf() - 1.0f);
    scale3 = scale3 * leaf->scale;
    sinA3 = sin(a3);
    f32 cosB3 = cos(b3);
    f32 cosA3 = cos(a3);
    p3->param1 = sinB3 * cosA3;
    p3->param2 = cosB3;
    p3->param3 = sinB3 * sinA3;
    PSVECScale(p3, p3, scale3);
    PSVECAdd(p3, &leaf->point1, p3);
    }
}

bool leafEffect::GenerateLeafData(leafData *leaf) {
    leaf->model = GSmodelClone(model);
    if (!leaf->model) {
        GSlogWrite("_leaffxGenerateLeafData: Could not create leaf clone model.\n");
        return false;
    }
    GSmodelSetVisibility(leaf->model, 1);
    leaf->scale = sizeBase + sizeRange * (2.0f * HSD_Randf() - 1.0f);
    leaf->scale = leaf->scale * sizeScale;
    leaf->progress = 0.0f;
    f32 b;
    f32 a;
    a = 6.2831855f * HSD_Randf();
    b = 3.1415927f * HSD_Randf();
    f32 sinB = sin(b);
    f32 sinA = sin(a);
    f32 cosB = cos(b);
    f32 cosA = cos(a);
    GSvec axis;
    axis.param1 = sinB * cosA;
    axis.param2 = cosB;
    axis.param3 = sinB * sinA;
    C_QUATRotAxisRad(&leaf->rotFrom, &axis, 6.2831855f * HSD_Randf());
    {
        f32 sinB2;
        f32 sinA2;
        f32 b2;
        f32 a2;
        a2 = 6.2831855f * HSD_Randf();
        b2 = 3.1415927f * HSD_Randf();
        sinB2 = sin(b2);
        sinA2 = sin(a2);
        f32 cosB2 = cos(b2);
        f32 cosA2 = cos(a2);
        GSvec axis2;
        axis2.param1 = sinB2 * cosA2;
        axis2.param2 = cosB2;
        axis2.param3 = sinB2 * sinA2;
        C_QUATRotAxisRad(&leaf->rotTo, &axis2, 6.2831855f * HSD_Randf());
    }
    leaf->point0.param1 = origin.param1;
    leaf->point0.param2 = origin.param2;
    leaf->point0.param3 = origin.param3;
    GSvec *p2 = &leaf->point2;
    {
        f32 sinB3;
        f32 sinA3;
        f32 b3;
        f32 scale2;
        f32 a3;
        scale2 = driftBase + driftRange * (2.0f * HSD_Randf() - 1.0f);
        scale2 = scale2 * leaf->scale;
        a3 = 6.2831855f * HSD_Randf();
        b3 = 3.1415927f * HSD_Randf();
        sinB3 = sin(b3);
        sinA3 = sin(a3);
        f32 cosB3 = cos(b3);
        f32 cosA3 = cos(a3);
        p2->param1 = sinB3 * cosA3;
        p2->param2 = cosB3;
        p2->param3 = sinB3 * sinA3;
        PSVECScale(p2, p2, scale2);
        PSVECAdd(p2, &origin, p2);
    }
    GSvec *p1 = &leaf->point1;
    {
        f32 a4;
        f32 sinB4;
        f32 sinA4;
        f32 b4;
        f32 scale4;
        a4 = 6.2831855f * HSD_Randf();
        b4 = 1.5707964f * HSD_Randf();
        sinB4 = sin(b4);
        scale4 = spreadBase + spreadRange * (2.0f * HSD_Randf() - 1.0f);
        scale4 = scale4 * (radialBase + radialRange * (2.0f * HSD_Randf() - 1.0f));
        scale4 = scale4 * leaf->scale;
        sinA4 = sin(a4);
        f32 cosB4 = cos(b4);
        f32 cosA4 = cos(a4);
        p1->param1 = sinB4 * cosA4;
        p1->param2 = cosB4;
        p1->param3 = sinB4 * sinA4;
        PSVECScale(p1, p1, scale4);
        PSVECAdd(p1, &origin, p1);
    }
    GSvec *p3 = &leaf->point3;
    {
        f32 a5;
        f32 sinB5;
        f32 sinA5;
        f32 b5;
        f32 scale5;
        a5 = 6.2831855f * HSD_Randf();
        b5 = 3.1415927f * HSD_Randf();
        sinB5 = sin(b5);
        scale5 = driftBase + driftRange * (2.0f * HSD_Randf() - 1.0f);
        scale5 = scale5 * leaf->scale;
        sinA5 = sin(a5);
        f32 cosB5 = cos(b5);
        f32 cosA5 = cos(a5);
        p3->param1 = sinB5 * cosA5;
        p3->param2 = cosB5;
        p3->param3 = sinB5 * sinA5;
        PSVECScale(p3, p3, scale5);
        PSVECAdd(p3, &leaf->point1, p3);
    }
    LeafMtx matrix;
    PSMTXQuat(matrix, &leaf->rotFrom);
    PSMTXScaleApply(matrix, matrix, leaf->scale, leaf->scale, leaf->scale);
    PSMTXTransApply(matrix, matrix, origin.param1, origin.param2, origin.param3);
    GSmodelSetMatrix(leaf->model, matrix);
    return true;
}
