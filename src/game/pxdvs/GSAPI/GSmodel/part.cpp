#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>
#include <game/pxdvs/GSAPI/GSpart/GSpart.hpp>
extern "C" {
static u32 _modelCurPartIdx, _modelDestPartIdx;
static HSD_JObj* _modelFoundJObj;
static void _modelFindJObj__FP9_HSD_JObjPPvi(HSD_JObj*, void**, s32);
void HSD_JObjWalkTree(HSD_JObj*, void (*)(HSD_JObj*, void**, s32), void**);
u32 GSmodelGetPartCount(GSmodel* model) {
    _modelCurPartIdx = 0;
    _modelDestPartIdx = -1;
    HSD_JObjWalkTree(model->joint, _modelFindJObj__FP9_HSD_JObjPPvi, 0);
    if ((model->flags & 0x20000) == 0x20000) --_modelCurPartIdx;
    return _modelCurPartIdx;
}
GSpart* GSmodelGetPart(GSmodel* model, u32 index) {
    u32 jointIndex = index;
    if ((model->flags & 0x20000) == 0x20000) ++jointIndex;
    HSD_JObj* joint = GSpartGetJObjPtr(modelGetRenderJObj__FP8_GSmodel(model), jointIndex);
    if (!joint) return 0;
    GSpart* part = GSpartCreate();
    if (!part) return 0;
    part->model = model; part->joint = joint; part->index = index;
    return part;
}
static void _modelFindJObj__FP9_HSD_JObjPPvi(HSD_JObj* joint, void**, s32) {
    if (_modelCurPartIdx++ == _modelDestPartIdx) _modelFoundJObj = joint;
}
}
