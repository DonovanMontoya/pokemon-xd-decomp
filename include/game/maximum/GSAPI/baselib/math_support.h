#ifndef HSD_MATH_SUPPORT_H
#define HSD_MATH_SUPPORT_H
#ifdef __cplusplus
extern "C" {
#endif
extern float __float_nan[], __float_min[], __float_epsilon[];
#ifdef __cplusplus
}
#endif
/* MSL float classification and reciprocal-square-root refinement used by XD. */
static inline int hsdFloatClassify(float value) {
    const int exponent = 0x7f800000;
    const int mantissa = 0x007fffff;
    switch (*(int*)&value & exponent) {
    case exponent: if (*(int*)&value & mantissa) return 1; else return 2;
    case 0: if (*(int*)&value & mantissa) return 5; else return 3;
    default: return 4;
    }
}

static inline float hsdSqrt(float value) {
    if (value > 0.0f) {
        double guess = __frsqrte((double)value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        guess = 0.5 * guess * (3.0 - guess * guess * value);
        return (float)(value * guess);
    } else if (value < 0.0) {
        return __float_nan[0];
    } else if (hsdFloatClassify(value) == 1) {
        return __float_nan[0];
    }
    return value;
}


#endif
