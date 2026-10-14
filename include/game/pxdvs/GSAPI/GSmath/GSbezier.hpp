#ifndef GS_BEZIER_H
#define GS_BEZIER_H

#include <dolphin/mtx.h>

struct GSbezier {
    Vec start;
    Vec end;
    Vec startControl;
    Vec endControl;
};

extern "C" void GSbezierCalculateVector(Vec*, const GSbezier*, f32);

#endif
