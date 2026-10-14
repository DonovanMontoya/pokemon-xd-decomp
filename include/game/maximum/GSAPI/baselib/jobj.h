#ifndef HSD_JOBJ_H
#define HSD_JOBJ_H
#include "game/maximum/GSAPI/baselib/animation_objects.h"
#include "game/maximum/GSAPI/baselib/mtx_base.h"
#ifdef __cplusplus
extern "C" {
#endif
void __assert(const char*, int, const char*);
void HSD_JObjSetupMatrixSub(HSD_JObj*);
void HSD_JObjUnrefThis(HSD_JObj*);
void HSD_JObjMakeMatrix(HSD_JObj*);
#ifdef __cplusplus
}
#endif
static inline int HSD_JObjMtxIsDirty(HSD_JObj* jobj) {
    int result;
    if (!jobj) __assert("jobj.h", 605, "jobj");
    result = 0;
    if (!(jobj->flags & (1 << 23)) && (jobj->flags & (1 << 6))) result = 1;
    return result;
}
static inline void HSD_JObjSetupMatrix(HSD_JObj* jobj) {
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) return;
    HSD_JObjSetupMatrixSub(jobj);
}
static inline float (*HSD_JObjGetMtxPtr(HSD_JObj* jobj))[4] {
    if (!jobj) __assert("jobj.h", 1148, "jobj");
    HSD_JObjSetupMatrix(jobj);
    return jobj->mtx;
}
static inline void HSD_JObjRefThis(HSD_JObj* jobj) {
    if (jobj) {
        ++jobj->object.ref_count_individual;
        if (!jobj->object.ref_count_individual)
            __assert("object.h", 158, "HSD_OBJ(o)->ref_count_individual != 0");
    }
}
#endif
