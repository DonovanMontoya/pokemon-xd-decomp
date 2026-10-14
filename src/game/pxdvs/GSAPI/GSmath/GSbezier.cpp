#include <game/pxdvs/GSAPI/GSmath/GSbezier.hpp>

static inline f32 clamp(f32 value, f32 minimum, f32 maximum) {
    if (value < minimum) {
        value = minimum;
    }
    if (value > maximum) {
        value = maximum;
    }
    return value;
}

void GSbezierCalculateVector(Vec* result, const GSbezier* curve, f32 t) {
    Vec term;
    t = clamp(t, 0.0f, 1.0f);

    f32 tSquared = t * t;
    f32 inverseT = 1.0f - t;
    f32 inverseTSquared = inverseT * inverseT;

    PSVECScale(&curve->start, result, inverseTSquared * inverseT);
    PSVECScale(&curve->startControl, &term, (3.0f * t) * inverseTSquared);
    PSVECAdd(result, &term, result);
    PSVECScale(&curve->endControl, &term, (3.0f * tSquared) * inverseT);
    PSVECAdd(result, &term, result);
    PSVECScale(&curve->end, &term, tSquared * t);
    PSVECAdd(result, &term, result);
}
