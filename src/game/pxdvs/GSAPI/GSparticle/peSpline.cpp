#include <game/pxdvs/GSAPI/GSparticle/peSplinePrivate.hpp>

// The retail routine uses quantized byte loads and stores for these channels.
// This scalar implementation remains nonmatching until those operations are recovered.
static inline u8 interpolateChannel(u8 a, u8 b, f32 weight) {
    f32 value = weight * ((f32)b - (f32)a) + (f32)a;
    if (value <= 0.0f) return 0;
    if (value >= 255.0f) return 255;
    return (u8)value;
}
static inline void copyColor(PeColor *destination, const PeColor *source) {
    destination->r = source->r;
    destination->g = source->g;
    destination->b = source->b;
}
extern "C" void peColorSplineGetValue(PeColor *result, PeColorSpline *spline, f32 time) {
    u8 count = spline->count;
    if (count < 2) return;
    PeColor *points = spline->points;
    if (time <= 0.0f) { copyColor(result, points); return; }
    if (time >= 1.0f) { copyColor(result, &points[count - 1]); return; }
    f32 difference = spline->time - time;
    if (difference < 0.0f) difference = -difference;
    if (difference <= 0.00001f) { copyColor(result, &spline->value); return; }
    spline->time = time;
    u8 interval = 0;
    f32 weight = time;
    if (count != 2) {
        interval = spline->interval;
        f32 *times = (f32 *)(points + count);
        f32 *scales = times + count;
        if (time < times[interval]) {
            interval = 0;
            spline->interval = 0;
        }
        while (times[interval + 1] < time) {
            interval++;
            spline->interval = interval;
            if (interval >= count) return;
        }
        weight = (time - times[interval]) * scales[interval];
    }
    spline->value.r = interpolateChannel(points[interval].r, points[interval + 1].r, weight);
    spline->value.g = interpolateChannel(points[interval].g, points[interval + 1].g, weight);
    spline->value.b = interpolateChannel(points[interval].b, points[interval + 1].b, weight);
    copyColor(result, &spline->value);
}

extern "C" f32 peSplineGetValue(PeSpline *spline, f32 time) {
    s32 type = spline->flags & 3;
    if (type == 0) return 1.0f;
    u8 last = spline->count - 1;
    if (last < 1) return 1.0f;
    f32 *points = spline->points;
    if (time <= 0.0f) return points[0];
    if (time >= 1.0f) return points[last];
    spline->time = time;
    if (last == 1) {
        switch (type) {
        case 1: break;
        case 3: spline->value = points[4] * time + points[0]; break;
        case 2: spline->value = points[1]; break;
        default: goto general;
        }
        return spline->value;
    }
general:
    u8 interval = 0;
    f32 *duration = points + (last + 1);
    f32 length;
    while ((length = *duration) < time) {
        interval++;
        time -= length;
        duration++;
        if (interval >= last) return 1.0f;
    }
    {
        f32 *inverse = duration + last;
        f32 *point = points + interval;
        f32 *tangent = inverse + last;
        time *= *inverse;
        switch (type) {
        case 3: {
            f32 t2 = time * time;
            f32 t3 = t2 * time;
            f32 h11 = t3 - t2;
            f32 h01 = (2.0f * t2 - t3) - h11;
            f32 minimum;
            if (spline->flags & 4) minimum = -1.0f;
            else minimum = 0.0f;
            f32 value = length * ((time + (h11 - t2)) * *tangent + h11 * tangent[last])
                + (h01 * point[1] + (1.0f - h01) * point[0]);
            if (value < minimum) value = minimum;
            else if (value > 1.0f) value = 1.0f;
            spline->value = value;
            break;
        }
        case 1: spline->value = *tangent * time + point[0]; break;
        case 2: spline->value = point[1]; break;
        }
        return spline->value;
    }
}
