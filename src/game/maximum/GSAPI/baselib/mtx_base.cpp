#include "game/maximum/GSAPI/baselib/mtx_base.h"
#include "game/maximum/GSAPI/baselib/math_support.h"
#define EPSILON 0.0000000001f
#ifdef __cplusplus
extern "C" {
#endif
void __assert(const char*, int, const char*);
double sin(double); double cos(double); double asin(double); double atan2(double, double);
void PSMTXCopy(const HSD_Mtx, HSD_Mtx);
void PSMTXScale(HSD_Mtx, float, float, float);
void PSMTXQuat(HSD_Mtx, const HSD_Quaternion*);
void PSMTXConcat(const HSD_Mtx, const HSD_Mtx, HSD_Mtx);
void PSVECScale(const HSD_Vec3*, HSD_Vec3*, float);
void PSVECSubtract(const HSD_Vec3*, const HSD_Vec3*, HSD_Vec3*);
float PSVECDotProduct(const HSD_Vec3*, const HSD_Vec3*);
void PSVECCrossProduct(const HSD_Vec3*, const HSD_Vec3*, HSD_Vec3*);
void PSVECNormalize(const HSD_Vec3*, HSD_Vec3*);
float PSVECSquareMag(const HSD_Vec3*);
float PSVECMag(const HSD_Vec3*);
#define VECScale PSVECScale
#define VECSubtract PSVECSubtract
#define VECDotProduct PSVECDotProduct
#define VECCrossProduct PSVECCrossProduct
#define VECNormalize PSVECNormalize
#define VECMag PSVECMag
#define MTXCopy PSMTXCopy
#define MTXScale PSMTXScale
#define MTXQuat PSMTXQuat
#define MTXConcat PSMTXConcat
HSD_Mtx HSD_identityMtx = {
    {1.0F, 0.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F, 0.0F},
    {0.0F, 0.0F, 1.0F, 0.0F}
};
static HSD_ObjAllocData mtx_alloc_data, vec_alloc_data;
#define HSD_ASSERT(line, condition) do { if (!(condition)) __assert("mtx.c", line, #condition); } while (0)
static inline float hsdSafeReciprocal(float value) {
    if (value >= 0.0F) return 1.0F / (value + __float_epsilon[0]);
    else return 1.0F / (value - __float_epsilon[0]);
}
void HSD_MtxInitAllocData(void)
{
    HSD_ObjAllocInit(&mtx_alloc_data, sizeof(HSD_Mtx), 4);
}

HSD_ObjAllocData* HSD_MtxGetAllocData(void)
{
    return &mtx_alloc_data;
}

void HSD_VecInitAllocData(void)
{
    HSD_ObjAllocInit(&vec_alloc_data, sizeof(HSD_Vec3), 4);
}

HSD_ObjAllocData* HSD_VecGetAllocData(void)
{
    return &vec_alloc_data;
}

void HSD_MtxFree(void* arg0)
{
    if (arg0 != 0) {
        HSD_ObjFree(&mtx_alloc_data, arg0);
    }
}

void* HSD_MtxAlloc(void)
{
    void* mtx;

    mtx = HSD_ObjAlloc(&mtx_alloc_data);
    HSD_ASSERT(0x3AB, mtx);
    return mtx;
}

void HSD_VecFree(void* arg0)
{
    if (arg0 != 0) {
        HSD_ObjFree(&vec_alloc_data, arg0);
    }
}

void* HSD_VecAlloc(void)
{
    void* vec = HSD_ObjAlloc(&vec_alloc_data);

    HSD_ASSERT(0x38C, vec);

    return vec;
}

void HSD_VecGetOrthogonal(HSD_Vec3* src, HSD_Vec3* dst) {
    HSD_Vec3 axis;
    if (src->x <= src->y) {
        if (src->x <= src->z) {
            axis.x = 1.0F; axis.y = 0.0F; axis.z = 0.0F;
            VECCrossProduct(&axis, src, dst);
        } else {
            axis.x = 0.0F; axis.y = 0.0F; axis.z = 1.0F;
            VECCrossProduct(&axis, src, dst);
        }
    } else {
        if (src->y <= src->z) {
            axis.x = 0.0F; axis.y = 1.0F; axis.z = 0.0F;
            VECCrossProduct(&axis, src, dst);
        } else {
            axis.x = 0.0F; axis.y = 0.0F; axis.z = 1.0F;
            VECCrossProduct(&axis, src, dst);
        }
    }
}

void HSD_MtxScaledAdd(HSD_Mtx arg0, HSD_Mtx arg1, HSD_Mtx arg2, float arg3)
{
    float* arr0 = (&arg0[0][0]);
    float* arr1 = (&arg1[0][0]);
    float* arr2 = (&arg2[0][0]);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);

    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
    *arr2++ = *arr1++ + (arg3 * *arr0++);
}

void HSD_MtxSRTQuat(HSD_Mtx m, HSD_Vec3* scale, HSD_Quaternion* rotation, HSD_Vec3* translation,
                    HSD_Vec3* parent_scale) {
    HSD_Mtx temp;
    MTXScale(m, scale->x, scale->y, scale->z);
    MTXQuat(temp, rotation);
    if (parent_scale != 0) {
        float inverse_x = hsdSafeReciprocal(parent_scale->x);
        float inverse_y = hsdSafeReciprocal(parent_scale->y);
        float inverse_z = hsdSafeReciprocal(parent_scale->z);
        temp[0][1] *= parent_scale->y * inverse_x;
        temp[0][2] *= parent_scale->y * inverse_x;
        temp[1][0] *= parent_scale->x * inverse_y;
        temp[1][2] *= parent_scale->z * inverse_y;
        temp[2][0] *= parent_scale->x * inverse_z;
        temp[2][1] *= parent_scale->y * inverse_z;
    }
    MTXConcat(temp, m, m);
    m[0][3] = translation->x;
    m[1][3] = translation->y;
    m[2][3] = translation->z;
}

void HSD_MtxSRT(HSD_Mtx m, HSD_Vec3* vec1, HSD_Vec3* vec2, HSD_Vec3* vec3, HSD_Vec3* vec4)
{
    float sinX, cosX, sinY, cosY, sinZ, cosZ;
    float vec1x_2;
    float vec1y_2;
    float vec1z_2;
    float vec1x_1;
    float vec1y_1;
    float vec1z_1;
    float vec1x;
    float vec1y;
    float vec1z;

    sinX = (float) sin(vec2->x);
    cosX = (float) cos(vec2->x);
    sinY = (float) sin(vec2->y);
    cosY = (float) cos(vec2->y);
    sinZ = (float) sin(vec2->z);
    cosZ = (float) cos(vec2->z);

    vec1x_2 = vec1x_1 = vec1x = vec1->x;
    vec1y_2 = vec1y_1 = vec1y = vec1->y;
    vec1z_2 = vec1z_1 = vec1z = vec1->z;

    if (vec4 != 0) {
        float temp1 = (vec4->x >= 0.0F ? 1.0F / (vec4->x + __float_epsilon[0]) : 1.0F / (vec4->x - __float_epsilon[0]));
        float temp2 = (vec4->y >= 0.0F ? 1.0F / (vec4->y + __float_epsilon[0]) : 1.0F / (vec4->y - __float_epsilon[0]));
        float temp3 = (vec4->z >= 0.0F ? 1.0F / (vec4->z + __float_epsilon[0]) : 1.0F / (vec4->z - __float_epsilon[0]));

        vec1y_2 *= vec4->y * temp1;
        vec1z_2 *= vec4->z * temp1;
        vec1x_1 *= vec4->x * temp2;
        vec1z_1 *= vec4->z * temp2;
        vec1x *= vec4->x * temp3;
        vec1y *= vec4->y * temp3;
    }

    m[0][0] = cosZ * (vec1x_2 * cosY);
    m[1][0] = sinZ * (vec1x_1 * cosY);
    m[2][0] = -vec1x * sinY;
    m[0][1] = vec1y_2 * ((cosZ * (sinX * sinY)) - (cosX * sinZ));
    m[1][1] = vec1y_1 * ((sinZ * (sinX * sinY)) + (cosX * cosZ));
    m[2][1] = cosY * (vec1y * sinX);
    m[0][2] = vec1z_2 * ((cosZ * (cosX * sinY)) + (sinX * sinZ));
    m[1][2] = vec1z_1 * ((sinZ * (cosX * sinY)) - (sinX * cosZ));
    m[2][2] = cosY * (vec1z * cosX);
    m[0][3] = vec3->x;
    m[1][3] = vec3->y;
    m[2][3] = vec3->z;
}

void HSD_MkRotationMtx(HSD_Mtx arg0, HSD_Vec3* arg1)
{
    float sinX;
    float cosX;
    float sinY;
    float cosY;
    float sinZ;
    float cosZ;
    float temp1;
    float temp2;

    sinX = (float) sin(arg1->x);
    cosX = (float) cos(arg1->x);
    sinY = (float) sin(arg1->y);
    cosY = (float) cos(arg1->y);
    sinZ = (float) sin(arg1->z);
    cosZ = (float) cos(arg1->z);

    temp1 = sinX * sinY;
    arg0[0][0] = cosY * cosZ;
    arg0[1][0] = cosY * sinZ;
    arg0[2][0] = -sinY;
    temp2 = cosX * sinY;
    arg0[0][1] = (cosZ * temp1) - (cosX * sinZ);
    arg0[1][1] = (sinZ * temp1) + (cosX * cosZ);
    arg0[2][1] = sinX * cosY;
    arg0[0][2] = (cosZ * temp2) + (sinX * sinZ);
    arg0[1][2] = (sinZ * temp2) - (sinX * cosZ);
    arg0[2][2] = cosX * cosY;
    arg0[0][3] = 0;
    arg0[1][3] = 0;
    arg0[2][3] = 0;
}

void HSD_MtxGetScale(HSD_Mtx m, HSD_Vec3* out) {
    float square;
    float inverse_length;
    double sign;
    HSD_Vec3 x, y, z, projection;
    x.x = m[0][0]; x.y = m[1][0]; x.z = m[2][0];
    square = PSVECSquareMag(&x);
    if (square > EPSILON) {
        inverse_length = hsdSqrt(1.0F / square);
        out->x = 1.0F / inverse_length;
        VECScale(&x, &x, inverse_length);
        y.x = m[0][1]; y.y = m[1][1]; y.z = m[2][1];
        VECScale(&x, &projection, VECDotProduct(&x, &y));
        VECSubtract(&y, &projection, &y);
        square = PSVECSquareMag(&y);
        if (square > EPSILON) {
            inverse_length = hsdSqrt(1.0F / square);
            out->y = 1.0F / inverse_length;
            VECScale(&y, &y, inverse_length);
            z.x = m[0][2]; z.y = m[1][2]; z.z = m[2][2];
            VECScale(&y, &projection, VECDotProduct(&y, &z));
            VECSubtract(&z, &projection, &z);
            VECScale(&x, &projection, VECDotProduct(&x, &z));
            VECSubtract(&z, &projection, &z);
            square = PSVECSquareMag(&z);
            if (square > EPSILON) {
                out->z = hsdSqrt(square);
                VECCrossProduct(&y, &z, &projection);
                if (VECDotProduct(&x, &projection) < 0.0) {
                    sign = -1.0;
                    out->x *= sign; out->y *= sign; out->z *= sign;
                }
            } else {
                out->z = 0.0F;
            }
        } else {
            out->y = 0.0F;
            z.x = m[0][2]; z.y = m[1][2]; z.z = m[2][2];
            VECScale(&x, &projection, VECDotProduct(&x, &z));
            VECSubtract(&z, &projection, &z);
            square = PSVECSquareMag(&z);
            if (square > EPSILON) out->z = hsdSqrt(square);
            else out->z = 0.0F;
        }
    } else {
        out->x = 0.0F;
        y.x = m[0][1]; y.y = m[1][1]; y.z = m[2][1];
        square = PSVECSquareMag(&y);
        if (square > EPSILON) {
            inverse_length = hsdSqrt(1.0F / square);
            out->y = 1.0F / inverse_length;
            VECScale(&y, &y, inverse_length);
            z.x = m[0][2]; z.y = m[1][2]; z.z = m[2][2];
            VECScale(&y, &projection, VECDotProduct(&y, &z));
            VECSubtract(&z, &projection, &z);
            out->z = VECMag(&z);
        } else {
            out->y = 0.0F;
            z.x = m[0][2]; z.y = m[1][2]; z.z = m[2][2];
            out->z = VECMag(&z);
        }
    }
}

void HSD_MtxGetTranslate(HSD_Mtx mat, HSD_Vec3* vec)
{
    vec->x = mat[0][3];
    vec->y = mat[1][3];
    vec->z = mat[2][3];
}

void HSD_MtxGetRotationMtx(HSD_Mtx src, HSD_Mtx dst, signed char primary, signed char secondary) {
    HSD_Vec3 x, y, z;
    switch (primary) {
    case 'x': case 'X':
        x.x = src[0][0]; x.y = src[1][0]; x.z = src[2][0];
        VECNormalize(&x, &x);
        switch (secondary) {
        case 'z': case 'Z':
            z.x = src[0][2]; z.y = src[1][2]; z.z = src[2][2];
            VECNormalize(&z, &z);
            VECCrossProduct(&z, &x, &y);
            VECCrossProduct(&x, &y, &z);
            break;
        default:
            y.x = src[0][1]; y.y = src[1][1]; y.z = src[2][1];
            VECNormalize(&y, &y);
            VECCrossProduct(&x, &y, &z);
            VECCrossProduct(&z, &x, &y);
            break;
        }
        break;
    case 'y': case 'Y':
        y.x = src[0][1]; y.y = src[1][1]; y.z = src[2][1];
        VECNormalize(&y, &y);
        switch (secondary) {
        case 'x': case 'X':
            x.x = src[0][0]; x.y = src[1][0]; x.z = src[2][0];
            VECNormalize(&x, &x);
            VECCrossProduct(&x, &y, &z);
            VECCrossProduct(&y, &z, &x);
            break;
        default:
            z.x = src[0][2]; z.y = src[1][2]; z.z = src[2][2];
            VECNormalize(&z, &z);
            VECCrossProduct(&y, &z, &x);
            VECCrossProduct(&x, &y, &z);
            break;
        }
        break;
    default:
        z.x = src[0][2]; z.y = src[1][2]; z.z = src[2][2];
        VECNormalize(&z, &z);
        switch (secondary) {
        case 'y': case 'Y':
            y.x = src[0][1]; y.y = src[1][1]; y.z = src[2][1];
            VECNormalize(&y, &y);
            VECCrossProduct(&y, &z, &x);
            VECCrossProduct(&z, &x, &y);
            break;
        default:
            x.x = src[0][0]; x.y = src[1][0]; x.z = src[2][0];
            VECNormalize(&x, &x);
            VECCrossProduct(&z, &x, &y);
            VECCrossProduct(&y, &z, &x);
            break;
        }
        break;
    }
    dst[0][0] = x.x; dst[1][0] = x.y; dst[2][0] = x.z;
    dst[0][1] = y.x; dst[1][1] = y.y; dst[2][1] = y.z;
    dst[0][2] = z.x; dst[1][2] = z.y; dst[2][2] = z.z;
    dst[0][3] = 0.0F; dst[1][3] = 0.0F; dst[2][3] = 0.0F;
}

static inline float calcVal(float x, float y)
{
    if (x == 0.0F) {
        if (y >= 0) {
            return 1.5707963267948966F;
        } else {
            return -1.5707963267948966F;
        }
    } else {
        return (float) atan2(y, x);
    }
}

void HSD_MtxGetRotation(HSD_Mtx m, HSD_Vec3* vec)
{
    float length0;
    float length1;
    float length2;
    float testVal_1;
    float val_01;

    length0 = hsdSqrt(m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0]);
    if (!(length0 < __float_min[0])) {
        length1 =
            hsdSqrt(m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1]);
        if (!(length1 < __float_min[0])) {
            length2 = hsdSqrt(m[0][2] * m[0][2] + m[1][2] * m[1][2] +
                            m[2][2] * m[2][2]);
            if (!(length2 < __float_min[0])) {
                testVal_1 = -m[2][0];
                testVal_1 /= length0;

                if (testVal_1 >= 1.0f) {
                    val_01 = 1.5707963267948966F;
                } else if (testVal_1 <= -1) {
                    val_01 = -1.5707963267948966F;
                } else {
                    val_01 = (float) asin(testVal_1);
                }

                vec->y = val_01;

                if ((float) cos(vec->y) >= __float_min[0]) {
                    float testVal_2_pre = m[2][2] / length2;
                    float testVal_3_pre = m[2][1] / length1;

                    vec->x = calcVal(testVal_2_pre, testVal_3_pre);
                    vec->z = calcVal(m[0][0], m[1][0]);
                    return;
                }

                vec->x = calcVal(m[1][1], m[0][1]);
                vec->z = 0;
                return;
            }
        }
    }

    vec->x = 0;
    vec->y = 0;
    vec->z = 0;
}

static inline float HSD_CalcDeterminantMatrix3x4(HSD_Mtx m)
{
    return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] +
           m[0][2] * m[1][0] * m[2][1] - m[2][0] * m[1][1] * m[0][2] -
           m[1][0] * m[0][1] * m[2][2] - m[0][0] * m[2][1] * m[1][2];
}

int HSD_MtxInverseConcat(HSD_Mtx inv, HSD_Mtx src, HSD_Mtx dest)
{
    HSD_Mtx m;
    float det;
    float temp1;
    float temp2;
    float temp3;
    float temp4;
    float temp5;
    float temp6;
    float temp7;
    float temp8;
    float temp9;
    float temp10;
    float temp11;
    float temp12;

    det = HSD_CalcDeterminantMatrix3x4(inv);

    if (det == 0.0F) {
        return 0;
    } else {
        det = 1.0f / det;
        temp1 = ((inv[1][1] * inv[2][2]) - (inv[2][1] * inv[1][2])) * det;
        temp2 = (-((inv[0][1] * inv[2][2]) - (inv[2][1] * inv[0][2]))) * det;
        temp3 = (-((inv[1][0] * inv[2][2]) - (inv[2][0] * inv[1][2]))) * det;
        temp7 = ((inv[0][1] * inv[1][2]) - (inv[1][1] * inv[0][2])) * det;
        temp4 = ((inv[0][0] * inv[2][2]) - (inv[2][0] * inv[0][2])) * det;
        temp8 = (-((inv[0][0] * inv[1][2]) - (inv[1][0] * inv[0][2]))) * det;
        temp5 = ((inv[1][0] * inv[2][1]) - (inv[2][0] * inv[1][1])) * det;
        temp6 = (-((inv[0][0] * inv[2][1]) - (inv[2][0] * inv[0][1]))) * det;
        temp9 = ((inv[0][0] * inv[1][1]) - (inv[1][0] * inv[0][1])) * det;
        temp10 = -((temp7 * inv[2][3]) -
                   (((-temp1) * inv[0][3]) - (temp2 * inv[1][3])));
        temp11 = -((temp8 * inv[2][3]) -
                   (((-temp3) * inv[0][3]) - (temp4 * inv[1][3])));
        temp12 = -((temp9 * inv[2][3]) -
                   (((-temp5) * inv[0][3]) - (temp6 * inv[1][3])));

        if (inv == dest || src == dest) {
            m[0][0] =
                temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            m[0][1] =
                temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            m[0][2] =
                temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            m[0][3] = temp7 * src[2][3] +
                      (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            m[1][0] =
                temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            m[1][1] =
                temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            m[1][2] =
                temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            m[1][3] = temp8 * src[2][3] +
                      (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            m[2][0] =
                temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            m[2][1] =
                temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            m[2][2] =
                temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            m[2][3] = temp9 * src[2][3] +
                      (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;

            MTXCopy(m, dest);
        } else {
            dest[0][0] =
                temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            dest[0][1] =
                temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            dest[0][2] =
                temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            dest[0][3] = temp7 * src[2][3] +
                         (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            dest[1][0] =
                temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            dest[1][1] =
                temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            dest[1][2] =
                temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            dest[1][3] = temp8 * src[2][3] +
                         (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            dest[2][0] =
                temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            dest[2][1] =
                temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            dest[2][2] =
                temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            dest[2][3] = temp9 * src[2][3] +
                         (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;
        }
    }
    return 1;
}

#ifdef __cplusplus
}
#endif
