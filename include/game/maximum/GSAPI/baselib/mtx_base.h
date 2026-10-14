#ifndef HSD_MTX_BASE_H
#define HSD_MTX_BASE_H
#include "game/maximum/GSAPI/baselib/quatlib.h"
#include "game/maximum/GSAPI/baselib/objalloc.h"
typedef float HSD_Mtx[3][4];
#ifdef __cplusplus
extern "C" {
#endif
extern HSD_Mtx HSD_identityMtx;
void HSD_MtxInitAllocData(void);
HSD_ObjAllocData* HSD_MtxGetAllocData(void);
void HSD_VecInitAllocData(void);
HSD_ObjAllocData* HSD_VecGetAllocData(void);
void HSD_MtxFree(void* arg0);
void* HSD_MtxAlloc(void);
void HSD_VecFree(void* arg0);
void* HSD_VecAlloc(void);
void HSD_VecGetOrthogonal(HSD_Vec3* src, HSD_Vec3* dst);
void HSD_MtxScaledAdd(HSD_Mtx arg0, HSD_Mtx arg1, HSD_Mtx arg2, float arg3);
void HSD_MtxSRTQuat(HSD_Mtx m, HSD_Vec3* scale, HSD_Quaternion* rotation, HSD_Vec3* translation,
                    HSD_Vec3* parent_scale);
void HSD_MtxSRT(HSD_Mtx m, HSD_Vec3* vec1, HSD_Vec3* vec2, HSD_Vec3* vec3, HSD_Vec3* vec4);
void HSD_MkRotationMtx(HSD_Mtx arg0, HSD_Vec3* arg1);
void HSD_MtxGetScale(HSD_Mtx m, HSD_Vec3* out);
void HSD_MtxGetTranslate(HSD_Mtx mat, HSD_Vec3* vec);
void HSD_MtxGetRotationMtx(HSD_Mtx src, HSD_Mtx dst, signed char primary, signed char secondary);
void HSD_MtxGetRotation(HSD_Mtx m, HSD_Vec3* vec);
int HSD_MtxInverseConcat(HSD_Mtx inv, HSD_Mtx src, HSD_Mtx dest);
#ifdef __cplusplus
}
#endif
#endif
