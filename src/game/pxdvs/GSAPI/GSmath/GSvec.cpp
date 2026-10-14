#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>

struct GSaxisVector {
    f32 x;
    f32 y;
    f32 z;

    GSaxisVector(f32 xValue, f32 yValue, f32 zValue)
        : x(xValue), y(yValue), z(zValue) {}
};

GSaxisVector xAxisVector(1.0f, 0.0f, 0.0f);
GSaxisVector yAxisVector(0.0f, 1.0f, 0.0f);
GSaxisVector zAxisVector(0.0f, 0.0f, 1.0f);
GSaxisVector zeroVector(0.0f, 0.0f, 0.0f);
GSaxisVector unitScaleVector(1.0f, 1.0f, 1.0f);

extern "C" double asin(double);
extern "C" double atan(double);
#include <dolphin/mtx.h>


extern "C" void GSvecMakeFromQuat(Vec* result, const Quaternion* quat) {
    const f32 x = quat->x, y = quat->y, z = quat->z, w = quat->w;
    const f32 xx = x * x, yy = y * y, zz = z * z, ww = w * w;
    result->x = asin(-2.0f * (x * z - w * y));
    result->y = atan((2.0f * (x * y + w * z)) / (ww + xx - yy - zz));
    result->z = atan((2.0f * (w * x + y * z)) / (zz + (ww - xx - yy)));
}
extern "C" void GSvecTransformQuat(Vec* result, const Quaternion* quat, const Vec* vector) {
    const f32 x = quat->x, y = quat->y, z = quat->z, w = quat->w;
    const f32 vx = vector->x, vy = vector->y, vz = vector->z;
    const f32 dot = vx * x + vy * y + vz * z;
    const f32 ix = vx * w + y * vz - vy * z;
    const f32 iy = vy * w + z * vx - vz * x;
    const f32 iz = vz * w + x * vy - vx * y;
    result->x = ix * w + x * dot + y * iz - iy * z;
    result->y = iy * w + y * dot + z * ix - iz * x;
    result->z = iz * w + z * dot + x * iy - ix * y;
}
