#include "global.h"
#undef MSL_INLINE
#define MSL_INLINE __declspec(weak)
#include <float.h>

__declspec(weak) float acosf(float x) { return acos(x); }
__declspec(weak) float cosf(float x) { return cos(x); }
__declspec(weak) float sinf(float x) { return sin(x); }
__declspec(weak) float tanf(float x) { return tan(x); }

__declspec(weak) float sqrtf(float mag) {
    static const double _half = 0.5;
    static const double _three = 3.0;
    if (mag > 0.0f) {
        double dmag = (double)mag;
        double tmpd = __frsqrte(dmag);
        tmpd = _half * tmpd * (_three - tmpd * tmpd * dmag);
        tmpd = _half * tmpd * (_three - tmpd * tmpd * dmag);
        tmpd = _half * tmpd * (_three - tmpd * tmpd * dmag);
        return (float)(dmag * tmpd);
    } else if (mag < 0.0) {
        return *(float*)__float_nan;
    } else if (isnan(mag)) {
        return *(float*)__float_nan;
    } else {
        return mag;
    }
}

__declspec(weak) double fabs(double x) { return __fabs(x); }
