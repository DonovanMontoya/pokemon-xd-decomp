#include "game/maximum/GSAPI/baselib/spline.h"
#include "game/maximum/GSAPI/baselib/math_support.h"
extern "C" {
float splArcLength(const float[5], float, float);
static inline int hsdFloatClassify(float);
static inline float hsdSqrt(float);
void splArcLengthPoint(HSD_Vec3* vec3, HSD_Spline* spline, float farg0)
{
    splGetSplinePoint(vec3, spline, splArcLengthGetParameter(spline, farg0));
}

float splArcLengthGetParameter(HSD_Spline* spl, float arg1)
{
    int idx = 0;
    float start = 0.0F;
    float end = 1.0F;
    float result;

    if (arg1 <= 0.0F) {
        return start;
    }

    if (arg1 >= 1.0F) {
        return end;
    }

    while (spl->segLength[idx + 1] < arg1) {
        idx++;
    }

    switch (spl->type) {
    case 0: {
        result = (arg1 - spl->segLength[idx]) /
                 (spl->segLength[idx + 1] - spl->segLength[idx]);
    } break;
    case 1:
    case 2:
    case 3: {
        // i belive the bulk of this math is applying simpson's rule
        // https://en.wikipedia.org/wiki/Simpson%27s_rule
        float var_f22 = spl->totalLength * (arg1 - spl->segLength[idx]);

        while (((start - end) < 0.0F ? -(start - end) : (start - end)) >= 0.00001F) {
            const float* coeffs = spl->segPoly[idx];
            float dx;
            float middle;
            float simpsons;

            result = (start + end) / 2.0F;
            simpsons = splArcLength(coeffs, start, result);
            if (var_f22 < (0.00001F + simpsons)) {
                end = result;
            } else {
                start = result;
                var_f22 -= simpsons;
            }
        }
    } break;
    }

    return (result + idx) / (spl->numcv - 1.0F);
}

static inline float splArcLengthPolynomial(const float coeffs[5], float t)
{
    float t2 = t * t;
    float t3 = t2 * t;
    float t4 = t3 * t;
    float result = (coeffs[0] * t4) + (coeffs[1] * t3) + (coeffs[2] * t2) +
                 (coeffs[3] * t) + coeffs[4];

    if ((result < 0.0F) && (result > -0.001F)) {
        result = 0.0F;
    }

    return hsdSqrt(result);
}

float splArcLength(const float coeffs[5], float start, float end) {
    float dx = (end - start) / 8.0F;
    float t = start + dx;
    float sum = 0.0F;
    int i;
    for (i = 2; i <= 8; ++i) {
        if (!(i & 1)) {
            sum += 4.0F * splArcLengthPolynomial(coeffs, t);
        } else {
            sum += 2.0F * splArcLengthPolynomial(coeffs, t);
        }
        t += dx;
    }
    return dx * (sum + splArcLengthPolynomial(coeffs, start) +
                 splArcLengthPolynomial(coeffs, end)) / 3.0F;
}

static inline void splGetCardinalPoint(HSD_Vec3* p, HSD_Vec3* cp, float tension, float u)
{
    float u2 = u * u;
    float u3 = u2 * u;
    float car0 = tension * (-u3 + 2.0F * u2 - u);
    float car1 = ((2.0F - tension) * u3) + ((tension - 3.0F) * u2) + 1.0F;
    float car2 = ((tension - 2.0F) * u3) + ((3.0F - (2.0F * tension)) * u2) +
               (tension * u);
    float car3 = tension * (u3 - u2);

    p->x = (cp[0].x * car0) + (cp[1].x * car1) + (cp[2].x * car2) +
           (cp[3].x * car3);
    p->y = (cp[0].y * car0) + (cp[1].y * car1) + (cp[2].y * car2) +
           (cp[3].y * car3);
    p->z = (cp[0].z * car0) + (cp[1].z * car1) + (cp[2].z * car2) +
           (cp[3].z * car3);
}

static inline void splGetBSplinePoint(HSD_Vec3* p, HSD_Vec3* cp, float u)
{
    float u2 = u * u;
    float u3 = u2 * u;
    float u_1 = 1.0F - u;
    float k1_6 = (1.0F / 6.0F);
    float b0 = k1_6 * u_1 * u_1 * u_1;
    float b1 = k1_6 * (4.0F + (3.0F * u3 - 6.0F * u2));
    float b2 = k1_6 * (3.0F * (-u3 + u2 + u) + 1.0F);
    float b3 = k1_6 * u3;

    p->x = (cp[0].x * b0) + (cp[1].x * b1) + (cp[2].x * b2) + (cp[3].x * b3);
    p->y = (cp[0].y * b0) + (cp[1].y * b1) + (cp[2].y * b2) + (cp[3].y * b3);
    p->z = (cp[0].z * b0) + (cp[1].z * b1) + (cp[2].z * b2) + (cp[3].z * b3);
}

static inline void splGetBezierPoint(HSD_Vec3* p, HSD_Vec3* cp, float u)
{
    float u_1 = 1.0F - u;
    float u2 = u * u;
    float u_12 = u_1 * u_1;
    float bez0 = u_12 * u_1;
    float bez1 = 3.0F * u * u_12;
    float bez2 = 3.0F * u2 * u_1;
    float bez3 = u2 * u;

    p->x = (cp[0].x * bez0) + (cp[1].x * bez1) + (cp[2].x * bez2) +
           (cp[3].x * bez3);
    p->y = (cp[0].y * bez0) + (cp[1].y * bez1) + (cp[2].y * bez2) +
           (cp[3].y * bez3);
    p->z = (cp[0].z * bez0) + (cp[1].z * bez1) + (cp[2].z * bez2) +
           (cp[3].z * bez3);
}

void splGetSplinePoint(HSD_Vec3* p, HSD_Spline* spline, float u)
{
    HSD_Vec3* cp;
    short idx;
    if (u < 0.0F || u > 1.0F) {
        return;
    }

    if (u < 1.0F) {
        float t = (u * (spline->numcv - 1));
        idx = t;
        t = t - (float) idx;
        switch (spline->type) {
        case 0:
            // lerp
            cp = &spline->cv[idx];
            p->x = (t * (cp[1].x - cp[0].x)) + cp[0].x;
            p->y = (t * (cp[1].y - cp[0].y)) + cp[0].y;
            p->z = (t * (cp[1].z - cp[0].z)) + cp[0].z;
            return;
        case 1:
            cp = &spline->cv[idx * 3];
            splGetBezierPoint(p, cp, t);
            return;
        case 2:
            cp = &spline->cv[idx];
            splGetBSplinePoint(p, cp, t);
            return;
        case 3: {
            cp = &spline->cv[idx];
            splGetCardinalPoint(p, cp, spline->tension, t);
            return;
        }
        }
    } else {
        idx = spline->numcv - 1;
        switch (spline->type) {
        case 0:
            __memcpy(p, &spline->cv[idx], sizeof(*p));
            return;
        case 1:
            __memcpy(p, &spline->cv[idx * 3], sizeof(*p));
            return;
        case 2:
            cp = &spline->cv[idx] - 1;
            splGetBSplinePoint(p, cp, 1.0f);
            return;
        case 3:
            cp = &spline->cv[idx];
            __memcpy(p, &cp[1], sizeof(*p));
            return;
        }
    }
}

float splGetHelmite(float fterm, float time, float p0, float p1, float d0, float d1)
{
    float _3t2_T2;
    float _2t3_T3;
    float t3_T2;
    float t2_T;
    float t2;
    float _1_T2;

    _1_T2 = time * time;
    t2 = fterm * fterm;
    t2_T = _1_T2 * fterm;
    t3_T2 = t2 * (_1_T2 * time);
    _2t3_T3 = 2.0f * t3_T2 * fterm;
    _3t2_T2 = 3.0f * _1_T2 * t2;

    return (d1 * (t3_T2 - t2_T)) + ((d0 * (time + ((t3_T2 - t2_T) - t2_T))) +
                                    ((p0 * (1.0f + (_2t3_T3 - _3t2_T2))) +
                                     (p1 * (-_2t3_T3 + _3t2_T2))));
}
}
