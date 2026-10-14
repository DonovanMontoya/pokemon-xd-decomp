#include <dolphin/mtx.h>

static inline void copyVector(volatile Vec* result, const volatile Vec* source) {
    result->x = source->x;
    result->y = source->y;
    result->z = source->z;
}

extern "C" {

void GSlerpGetLinearInterpolationVector(Vec* result, const Vec* start,
                                      const Vec* end, f32 t) {
    if (t <= 0.0f) {
        copyVector(result, start);
    } else if (t >= 1.0f) {
        copyVector(result, end);
    } else {
        PSVECSubtract(end, start, result);
        PSVECScale(result, result, t);
        PSVECAdd(result, start, result);
    }
}

f32 GSlerpGetLinearInterpolationFloat(f32 start, f32 end, f32 t) {
    if (t <= 0.0f) {
        return start;
    }
    if (t >= 1.0f) {
        return end;
    }
    return start + t * (end - start);
}

}
