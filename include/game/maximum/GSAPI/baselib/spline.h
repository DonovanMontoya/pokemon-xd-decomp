#ifndef HSD_SPLINE_H
#define HSD_SPLINE_H
#include "game/maximum/GSAPI/baselib/quatlib.h"
typedef struct HSD_Spline {
    unsigned char type;
    short numcv;
    float tension;
    HSD_Vec3* cv;
    float totalLength;
    float* segLength;
    float (*segPoly)[5];
} HSD_Spline;
#ifdef __cplusplus
extern "C" {
#endif
float splGetHelmite(float, float, float, float, float, float);
void splGetSplinePoint(HSD_Vec3*, HSD_Spline*, float);
float splArcLengthGetParameter(HSD_Spline*, float);
void splArcLengthPoint(HSD_Vec3*, HSD_Spline*, float);
#ifdef __cplusplus
}
#endif
#endif
