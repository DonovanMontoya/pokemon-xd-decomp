#ifndef HSD_QUATLIB_H
#define HSD_QUATLIB_H
typedef struct HSD_Vec3 { float x, y, z; } HSD_Vec3;
typedef struct HSD_Quaternion { float x, y, z, w; } HSD_Quaternion;
#ifdef __cplusplus
extern "C" {
#endif
int QuatSlerp(HSD_Quaternion*, HSD_Quaternion*, HSD_Quaternion*, float);
int EulerToQuat(HSD_Vec3*, HSD_Quaternion*);
#ifdef __cplusplus
}
#endif
#endif
