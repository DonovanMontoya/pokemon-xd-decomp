/* XD USA camera/material implementation adapted from the baselib reference. */
#include "game/maximum/GSAPI/baselib/cobj.h"
typedef int bool;
#define true 1
#define false 0
#include "game/maximum/GSAPI/baselib/math_support.h"
#define FILE_NAME "cobj.c"
#define FLT_MIN (__float_min[0])
#define GX_PERSPECTIVE 0
#define GX_ORTHOGRAPHIC 1
void __assert(const char*,int,const char*);
void* memcpy(void*,const void*,unsigned long);
void* memset(void*,int,unsigned long);
void* hsdAllocMemPiece(int); void hsdFreeMemPiece(void*,int);
#define HSD_ASSERT(line, cond) do { if (!(cond)) __assert(FILE_NAME, line, #cond); } while (0)
double __fabs(double); float atan2f(float,float); double atan2(double,double); double fabs(double); int __fpclassifyf(float); void OSReport(const char*,...);
#define fabsf(v) ((float)__fabs(v))
#define fabsf_bitwise(v) ((float)__fabs(v))
#define sqrtf(v) hsdSqrt(v)
void PSVECNormalize(Vec3*,Vec3*); void PSVECSubtract(Vec3*,Vec3*,Vec3*); float PSVECMag(Vec3*); float PSVECDotProduct(Vec3*,Vec3*);
#define VECSubtract PSVECSubtract
#define VECNormalize PSVECNormalize
#define VECMag PSVECMag
#define VECDotProduct PSVECDotProduct
void PSMTXMultVecSR(Mtx,Vec3*,Vec3*); void PSMTXRotAxisRad(Mtx,Vec3*,float); void C_MTXLookAt(Mtx,Vec3*,Vec3*,Vec3*); void PSMTXCopy(Mtx,Mtx); int PSMTXInverse(Mtx,Mtx);
void C_MTXPerspective(Mtx44,float,float,float,float); void C_MTXFrustum(Mtx44,float,float,float,float,float,float); void C_MTXOrtho(Mtx44,float,float,float,float,float,float);
#define MTXPerspective C_MTXPerspective
#define MTXFrustum C_MTXFrustum
#define MTXOrtho C_MTXOrtho
static inline void HSD_WObjClearFlags(HSD_WObj* wobj, unsigned int flags) { wobj->flags &= ~flags; }
static inline int WObjRefDec(HSD_WObj* wobj) { int ret; if ((ret = (wobj->parent.ref_count == 0xffff))) return ret; return wobj->parent.ref_count-- == 0; }
static inline void HSD_WObjUnref(HSD_WObj* wobj) { if (wobj && WObjRefDec(wobj)) hsdDelete(wobj); }
static HSD_ClassInfo* default_class; static HSD_CObj* current;

static void CObjInfoInit(void);
HSD_CObjInfo hsdCObj = { CObjInfoInit };
typedef char CObjSizeCheck[sizeof(HSD_CObj)==0x8C?1:-1];
typedef char CObjRuntimeSizeCheck[sizeof(HSD_CObjRuntime)==0x8C?1:-1];
typedef char CObjInfoSizeCheck[sizeof(HSD_CObjInfo)==0x44?1:-1];
static inline int vec_normalize_check(Vec3* src,Vec3* dst) { if (!src || !dst) return -1; if (__fabs(src->x)<=FLT_MIN && __fabs(src->y)<=FLT_MIN && __fabs(src->z)<=FLT_MIN) return -1; PSVECNormalize(src,dst); return 0; }
static inline int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye);
static inline HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj);
static inline HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj);
static inline void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags);
static inline void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags);
static inline bool HSD_CObjMtxIsDirty(HSD_CObj* cobj);
static inline int get_up_vector_for_viewing_mtx_inner(HSD_CObj* cobj, Vec3* up);
static inline int get_up_vector_for_viewing_mtx(HSD_CObj* cobj, Vec3* up);
static inline void CObjResetFlags(HSD_CObj* cobj, u32 flags);
static inline void HSD_CObjSetViewport(HSD_CObj* cobj, HSD_RectS16* viewport);
static inline void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor* scissor);
static inline f32 vec_get_x(Vec3* v);
static inline f64 vec_get_abs_y(Vec3* v);
static inline f32 cobj_get_up_x(Vec3* up);
static void CObjInfoInit(void);
static void CObjAmnesia(HSD_ClassInfo* info);
static void CObjRelease(HSD_Class* o);
static int CObjInit(HSD_Class* o);
HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc);
static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* desc);
HSD_CObj* HSD_CObjAlloc(void);
HSD_CObj* HSD_CObjGetCurrent(void);
void HSD_CObjGetOrtho(HSD_CObj* cobj, float* top, float* bottom, float* left,
                      float* right);
void HSD_CObjGetPerspective(HSD_CObj* cobj, float* top, float* bottom);
void HSD_CObjSetOrtho(HSD_CObj* cobj, float top, float bottom, float left,
                      float right);
void HSD_CObjSetFrustum(HSD_CObj* cobj, float top, float bottom, float left,
                        float right);
void HSD_CObjSetPerspective(HSD_CObj* cobj, float fov, float aspect);
void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type);
int HSD_CObjGetProjectionType(HSD_CObj* cobj);
void HSD_CObjSetViewportfx4(HSD_CObj* cobj, float left, float right, float top,
                            float bottom);
void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top,
                          u16 bottom);
void HSD_CObjSetFar(HSD_CObj* cobj, float far);
float HSD_CObjGetFar(HSD_CObj* cobj);
void HSD_CObjSetNear(HSD_CObj* cobj, float near);
float HSD_CObjGetNear(HSD_CObj* cobj);
void HSD_CObjSetAspect(HSD_CObj* cobj, float aspect);
void HSD_CObjSetFov(HSD_CObj* cobj, float fov);
void HSD_CObjSetRoll(HSD_CObj* cobj, float roll);
MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj);
MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj);
void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx);
void HSD_CObjSetMtxDirty(HSD_CObj* cobj);
void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up);
int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up);
static int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll);
static float upvec2roll(HSD_CObj* cobj, Vec3* up);
float HSD_CObjGetEyeDistance(HSD_CObj* cobj);
void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position);
void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position);
void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest);
void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest);
bool HSD_CObjSetCurrent(HSD_CObj* cobj);
void HSD_CObjSetupViewingMtx(HSD_CObj* cobj);
GXProjectionType HSD_CObjMakeProjectionMtx(HSD_CObj* cobj, Mtx44 mtx);
void HSD_CObjReqAnim(HSD_CObj* cobj, float startframe);
void HSD_CObjAnim(HSD_CObj* cobj);
static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim);
void HSD_CObjRemoveAnim(HSD_CObj* cobj);


static inline int HSD_CObjGetEyeVector(HSD_CObj* cobj, Vec3* eye) { Vec3 eyepos, interest; if (!cobj || !cobj->eyepos || !cobj->interest) return 0; HSD_CObjGetEyePosition(cobj, &eyepos); HSD_CObjGetInterest(cobj, &interest); VECSubtract(&interest, &eyepos, eye); return vec_normalize_check(eye,eye) == 0; }

static inline HSD_WObj* HSD_CObjGetEyePositionWObj(HSD_CObj* cobj)
{
    HSD_ASSERT(630, cobj);
    return cobj->eyepos;
}

static inline HSD_WObj* HSD_CObjGetInterestWObj(HSD_CObj* cobj)
{
    HSD_ASSERT(606, cobj);
    return cobj->interest;
}

static inline void HSD_CObjClearFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags &= ~flags;
}

static inline void HSD_CObjSetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags |= flags;
}

static inline bool HSD_CObjMtxIsDirty(HSD_CObj* cobj)
{
    return (cobj->flags & (1 << 30)) ||
           (cobj->eyepos != NULL && (cobj->eyepos->flags & 2)) ||
           (cobj->interest != NULL && (cobj->interest->flags & 2));
}

static inline int get_up_vector_for_viewing_mtx_inner(HSD_CObj* cobj, Vec3* up)
{
    return HSD_CObjGetUpVector(cobj, up);
}

static inline int get_up_vector_for_viewing_mtx(HSD_CObj* cobj, Vec3* up)
{
    return get_up_vector_for_viewing_mtx_inner(cobj, up);
}

static inline void CObjResetFlags(HSD_CObj* cobj, u32 flags)
{
    if (cobj == NULL) {
        return;
    }
    cobj->flags = (cobj->flags & 0xC0000000) | (flags & ~0xC0000000);
}

static inline void HSD_CObjSetViewport(HSD_CObj* cobj, HSD_RectS16* viewport)
{
    if (cobj == NULL) {
        return;
    }
    COBJ_EXT(cobj)->viewport.xmin = viewport->xmin;
    COBJ_EXT(cobj)->viewport.xmax = viewport->xmax;
    COBJ_EXT(cobj)->viewport.ymin = viewport->ymin;
    COBJ_EXT(cobj)->viewport.ymax = viewport->ymax;
}

static inline void HSD_CObjSetScissor(HSD_CObj* cobj, Scissor* scissor)
{
    if (cobj == NULL) {
        return;
    }
    COBJ_EXT(cobj)->scissor = *scissor;
}

static inline f32 vec_get_x(Vec3* v)
{
    return v->x;
}

static inline f64 vec_get_abs_y(Vec3* v)
{
    return fabsf(v->y);
}

static inline f32 cobj_get_up_x(Vec3* up)
{
    return up->x;
}

static void CObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdCObj), &hsdObj,
                     "sysdolphin_base_library", "hsd_cobj",
                     sizeof(HSD_CObjInfo), sizeof(HSD_CObj));

    HSD_CLASS_INFO(&hsdCObj)->init = CObjInit;
    HSD_CLASS_INFO(&hsdCObj)->release = CObjRelease;
    HSD_CLASS_INFO(&hsdCObj)->amnesia = CObjAmnesia;
    hsdCObj.load = CObjLoad;
    hsdCObj.update = CObjUpdateFunc;
}

static void CObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdCObj)) {
        current = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->amnesia(info);
}

static void CObjRelease(HSD_Class* o)
{
    HSD_WObj* eyepos;
    HSD_WObj* interest;
    HSD_CObj* cobj = HSD_COBJ(o);

    HSD_AObjRemove(cobj->aobj);
    eyepos = HSD_CObjGetEyePositionWObj(cobj);
    HSD_WObjUnref(eyepos);
    interest = HSD_CObjGetInterestWObj(cobj);
    HSD_WObjUnref(interest);
    if (COBJ_EXT(cobj)->proj_mtx != NULL) {
        HSD_MtxFree(COBJ_EXT(cobj)->proj_mtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdCObj)->release(o);
}

static int CObjInit(HSD_Class* o)
{
    HSD_CObj* cobj;
    int status = HSD_OBJECT_PARENT_INFO(&hsdCObj)->init(o);
    if (status < 0) {
        return status;
    }
    cobj = HSD_COBJ(o);
    if (cobj != NULL) {
        HSD_CObjSetMtxDirty(cobj);
    }
    cobj->eyepos = HSD_WObjAlloc();
    cobj->interest = HSD_WObjAlloc();
    return 0;
}

HSD_CObj* HSD_CObjLoadDesc(HSD_CObjDesc* desc)
{
    HSD_ClassInfo* info;
    HSD_CObj* cobj;

    if (desc != NULL) {
        if (desc->class_name == NULL ||
            (info = hsdSearchClassInfo(desc->class_name)) == NULL)
        {
            cobj = HSD_CObjAlloc();
        } else {
            cobj = hsdNew(info);
            HSD_ASSERT(1927, cobj);
        }
        HSD_COBJ_METHOD(cobj)->load(cobj, desc);
        return cobj;
    }
    return NULL;
}

static int CObjLoad(HSD_CObj* cobj, HSD_CObjDesc* desc)
{
    static Vec3 y_axis = { 0.0f, 1.0f, 0.0f };
    cobj->flags = desc->common.flags;
    CObjResetFlags(cobj, desc->common.flags);
    HSD_CObjSetViewport(cobj, &desc->common.viewport);
    HSD_CObjSetScissor(cobj, &desc->common.scissor);
    HSD_WObjInit(cobj->eyepos, desc->common.eyepos);
    HSD_WObjInit(cobj->interest, desc->common.interest);
    HSD_CObjSetNear(cobj, desc->common.nnear);
    HSD_CObjSetFar(cobj, desc->common.ffar);
    if (desc->common.flags & 1) {
        if (desc->common.up_vector != NULL) {
            HSD_CObjSetUpVector(cobj, desc->common.up_vector);
        } else {
            HSD_CObjSetUpVector(cobj, &y_axis);
        }
    } else {
        HSD_CObjSetRoll(cobj, desc->common.roll);
    }
    switch (desc->common.projection_type) {
    case PROJ_PERSPECTIVE:
        HSD_CObjSetPerspective(cobj, desc->perspective.fov,
                               desc->perspective.aspect);
        break;
    case PROJ_ORTHO:
        HSD_CObjSetOrtho(cobj, desc->ortho.top, desc->ortho.bottom,
                         desc->ortho.left, desc->ortho.right);
        break;
    case PROJ_FRUSTUM:
        HSD_CObjSetFrustum(cobj, desc->frustum.top, desc->frustum.bottom,
                           desc->frustum.left, desc->frustum.right);
        break;
    default:
        HSD_ASSERT(1888, 0);
        break;
    }
    return 0;
}

HSD_CObj* HSD_CObjAlloc(void)
{
    HSD_CObj* cobj = HSD_COBJ(
        hsdNew(default_class ? default_class : &hsdCObj.parent));
    HSD_ASSERT(1842, cobj);
    return cobj;
}

HSD_CObj* HSD_CObjGetCurrent(void)
{
    return current;
}

void HSD_CObjGetOrtho(HSD_CObj* cobj, float* top, float* bottom, float* left,
                      float* right)
{
    if (cobj == NULL || cobj->projection_type != PROJ_ORTHO) {
        return;
    }
    if (top != NULL) {
        *top = COBJ_EXT(cobj)->projection_param.ortho.top;
    }
    if (bottom != NULL) {
        *bottom = COBJ_EXT(cobj)->projection_param.ortho.bottom;
    }
    if (left != NULL) {
        *left = COBJ_EXT(cobj)->projection_param.ortho.left;
    }
    if (right != NULL) {
        *right = COBJ_EXT(cobj)->projection_param.ortho.right;
    }
}

void HSD_CObjGetPerspective(HSD_CObj* cobj, float* top, float* bottom)
{
    if (cobj == NULL || cobj->projection_type != PROJ_PERSPECTIVE) {
        return;
    }
    if (top != NULL) {
        *top = COBJ_EXT(cobj)->projection_param.perspective.fov;
    }
    if (bottom != NULL) {
        *bottom = COBJ_EXT(cobj)->projection_param.perspective.aspect;
    }
}

void HSD_CObjSetOrtho(HSD_CObj* cobj, float top, float bottom, float left,
                      float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_ORTHO;
    COBJ_EXT(cobj)->projection_param.ortho.top = top;
    COBJ_EXT(cobj)->projection_param.ortho.bottom = bottom;
    COBJ_EXT(cobj)->projection_param.ortho.left = left;
    COBJ_EXT(cobj)->projection_param.ortho.right = right;
}

void HSD_CObjSetFrustum(HSD_CObj* cobj, float top, float bottom, float left,
                        float right)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_FRUSTUM;
    COBJ_EXT(cobj)->projection_param.frustum.top = top;
    COBJ_EXT(cobj)->projection_param.frustum.bottom = bottom;
    COBJ_EXT(cobj)->projection_param.frustum.left = left;
    COBJ_EXT(cobj)->projection_param.frustum.right = right;
}

void HSD_CObjSetPerspective(HSD_CObj* cobj, float fov, float aspect)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = PROJ_PERSPECTIVE;
    COBJ_EXT(cobj)->projection_param.perspective.fov = fov;
    COBJ_EXT(cobj)->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetProjectionType(HSD_CObj* cobj, u32 proj_type)
{
    if (cobj == NULL) {
        return;
    }
    cobj->projection_type = proj_type;
}

int HSD_CObjGetProjectionType(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 1;
    }
    return cobj->projection_type;
}

void HSD_CObjSetViewportfx4(HSD_CObj* cobj, float left, float right, float top,
                            float bottom)
{
    if (cobj == NULL) {
        return;
    }
    COBJ_EXT(cobj)->viewport.xmin = left;
    COBJ_EXT(cobj)->viewport.xmax = right;
    COBJ_EXT(cobj)->viewport.ymin = top;
    COBJ_EXT(cobj)->viewport.ymax = bottom;
}

void HSD_CObjSetScissorx4(HSD_CObj* cobj, u16 left, u16 right, u16 top,
                          u16 bottom)
{
    if (cobj == NULL) {
        return;
    }
    COBJ_EXT(cobj)->scissor.left = left;
    COBJ_EXT(cobj)->scissor.right = right;
    COBJ_EXT(cobj)->scissor.top = top;
    COBJ_EXT(cobj)->scissor.bottom = bottom;
}

void HSD_CObjSetFar(HSD_CObj* cobj, float far)
{
    if (cobj != NULL) {
        cobj->far = far;
    }
}

float HSD_CObjGetFar(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->far;
}

void HSD_CObjSetNear(HSD_CObj* cobj, float near)
{
    if (cobj != NULL) {
        cobj->near = near;
    }
}

float HSD_CObjGetNear(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return 0.0f;
    }
    return cobj->near;
}

void HSD_CObjSetAspect(HSD_CObj* cobj, float aspect)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    COBJ_EXT(cobj)->projection_param.perspective.aspect = aspect;
}

void HSD_CObjSetFov(HSD_CObj* cobj, float fov)
{
    if (cobj == NULL || cobj->projection_type != 1) {
        return;
    }
    COBJ_EXT(cobj)->projection_param.perspective.fov = fov;
}

void HSD_CObjSetRoll(HSD_CObj* cobj, float roll)
{
    Vec3 up;

    if (!cobj) {
        return;
    }

    if ((cobj->flags & 1) != 0) {
        roll2upvec(cobj, &up, roll);
        HSD_CObjSetUpVector(cobj, &up);
    } else {
        if (cobj->u.roll != roll) {
            cobj->flags |= 0xC0000000;
        }
        cobj->u.roll = roll;
    }
}

MtxPtr HSD_CObjGetViewingMtxPtr(HSD_CObj* cobj) { HSD_CObjSetupViewingMtx(cobj); return cobj->view_mtx; }

MtxPtr HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj* cobj)
{
    if (cobj->flags & (1 << 31)) {
        if (COBJ_EXT(cobj)->proj_mtx == NULL) {
            COBJ_EXT(cobj)->proj_mtx = HSD_MtxAlloc();
        }
        PSMTXInverse(cobj->view_mtx, *COBJ_EXT(cobj)->proj_mtx);
        HSD_CObjClearFlags(cobj, (1 << 31));
    }
    return *COBJ_EXT(cobj)->proj_mtx;
}

void HSD_CObjGetViewingMtx(HSD_CObj* cobj, Mtx mtx)
{
    PSMTXCopy(HSD_CObjGetViewingMtxPtr(cobj), mtx);
}

void HSD_CObjSetMtxDirty(HSD_CObj* cobj)
{
    cobj->flags |= (1 << 30) | (1 << 31);
}

void HSD_CObjSetUpVector(HSD_CObj* cobj, Vec3* up)
{
    Vec3 v;
    if (!cobj || !up) {
        return;
    }
    if ((cobj->flags & 1) != 0) {
        if (vec_normalize_check(up, &v)) {
            OSReport("illegal up vector."); HSD_ASSERT(882, 0);
        }
        up = &v;

        if (cobj->u.up.x != cobj_get_up_x(up) || cobj->u.up.y != up->y ||
            cobj->u.up.z != up->z)
        {
            HSD_CObjSetMtxDirty(cobj);
        }
        cobj->u.up = *up;
    } else {
        HSD_CObjSetRoll(cobj, upvec2roll(cobj, up));
    }
}

int HSD_CObjGetUpVector(HSD_CObj* cobj, Vec3* up) { if (!cobj || !up) return 0; if (cobj->flags & 1) { *up = cobj->u.up; return 1; } return roll2upvec(cobj, up, cobj->u.roll); }

static int roll2upvec(HSD_CObj* cobj, Vec3* up, float roll)
{
    int res;
    Vec3 eye;
    Vec3 v0;
    Vec3 v1;
    Mtx m;

    res = HSD_CObjGetEyeVector(cobj, &eye);
    if (res == 0) {
        return 0;
    }
    if (1.0 - vec_get_abs_y(&eye) < 0.0001) {
        v0.x = sqrtf(eye.y * eye.y + eye.z * eye.z);
        v0.y = eye.y * (-vec_get_x(&eye) / v0.x);
        v0.z = eye.z * (-eye.x / v0.x);
    } else {
        v0.y = sqrtf(eye.x * eye.x + eye.z * eye.z);
        v0.x = eye.x * (-eye.y / v0.y);
        v0.z = eye.z * (-eye.y / v0.y);
    }
    PSMTXRotAxisRad(m, &eye, -roll);
    PSMTXMultVecSR(m, &v0, &v1);
    VECNormalize(&v1, up);
    return 1;
}

static float upvec2roll(HSD_CObj* cobj, Vec3* up)
{
    static Vec3 orig = {0.0F,0.0F,0.0F};
    static Vec3 uy = {0.0F,1.0F,0.0F};
    Vec3 v;
    Vec3 eye;
    Mtx vmtx;
    f32 dot;

    if (!HSD_CObjGetEyeVector(cobj, &eye)) {
        dot = 0.0f;
    } else {
        dot = fabsf(VECDotProduct(up, &eye));
        dot = 1.0f - dot;
        if (dot < FLT_MIN) {
            dot = 0.0f;
        } else {
            C_MTXLookAt(vmtx, &orig, &uy, &eye);
            PSMTXMultVecSR(vmtx, up, &v);
            if (v.y == 0.0f) {
                dot = -v.x >= 0.0f ? 1.5707963267948966F : -1.5707963267948966F;
            } else {
                dot = (float)atan2(-v.x, v.y);
            }
        }
    }
    return dot;
}

float HSD_CObjGetEyeDistance(HSD_CObj* cobj)
{
    Vec3 position;
    Vec3 interest;
    Vec3 look_vector;

    if (cobj == NULL) {
        return 0.0f;
    }
    HSD_ASSERT(737, cobj->eyepos);
    HSD_ASSERT(738, cobj->interest);
    HSD_CObjGetEyePosition(cobj, &position);
    HSD_CObjGetInterest(cobj, &interest);
    VECSubtract(&interest, &position, &look_vector);
    return VECMag(&look_vector);
}

void HSD_CObjSetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT(690, cobj);
    HSD_WObjSetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjGetEyePosition(HSD_CObj* cobj, Vec3* position)
{
    HSD_ASSERT(678, cobj);
    HSD_WObjGetPosition(HSD_CObjGetEyePositionWObj(cobj), position);
}

void HSD_CObjSetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT(666, cobj);
    HSD_WObjSetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

void HSD_CObjGetInterest(HSD_CObj* cobj, Vec3* interest)
{
    HSD_ASSERT(654, cobj);
    HSD_WObjGetPosition(HSD_CObjGetInterestWObj(cobj), interest);
}

bool HSD_CObjSetCurrent(HSD_CObj* cobj) { Mtx44 mtx; GXProjectionType type; if (cobj == NULL) return false; current = cobj; type = HSD_CObjMakeProjectionMtx(cobj, mtx); GXSetProjection(mtx, type); HSD_CObjSetupViewingMtx(cobj); return true; }

void HSD_CObjSetupViewingMtx(HSD_CObj* cobj)
{
    Vec3 eyepos;
    Vec3 up_vec;
    Vec3 interest;

    if (!(cobj->flags & 2) && HSD_CObjMtxIsDirty(cobj)) {
        HSD_CObjGetEyePosition(cobj, &eyepos);
        if (!HSD_CObjGetUpVector(cobj, &up_vec)) { up_vec.x = 0.0F; up_vec.y = 1.0F; up_vec.z = 0.0F; }
        HSD_CObjGetInterest(cobj, &interest);
        C_MTXLookAt(cobj->view_mtx, &eyepos, &up_vec, &interest);
        HSD_WObjClearFlags(cobj->eyepos, 2);
        HSD_WObjClearFlags(cobj->interest, 2);
        HSD_CObjClearFlags(cobj, 0x40000000);
        HSD_CObjSetFlags(cobj, 0x80000000);
    }
}

GXProjectionType HSD_CObjMakeProjectionMtx(HSD_CObj* cobj, Mtx44 mtx)
{
    GXProjectionType projection_type;
    current = cobj;
    switch (cobj->projection_type) {
    case PROJ_PERSPECTIVE:
        projection_type = GX_PERSPECTIVE;
        MTXPerspective(mtx, COBJ_EXT(cobj)->projection_param.perspective.fov,
                       COBJ_EXT(cobj)->projection_param.perspective.aspect, cobj->near,
                       cobj->far);
        break;
    case PROJ_FRUSTUM:
        projection_type = GX_PERSPECTIVE;
        MTXFrustum(mtx, COBJ_EXT(cobj)->projection_param.perspective.fov,
                   COBJ_EXT(cobj)->projection_param.perspective.aspect,
                   COBJ_EXT(cobj)->projection_param.frustum.left,
                   COBJ_EXT(cobj)->projection_param.frustum.right, cobj->near,
                   cobj->far);
        break;
    case PROJ_ORTHO:
        projection_type = GX_ORTHOGRAPHIC;
        MTXOrtho(mtx, COBJ_EXT(cobj)->projection_param.perspective.fov,
                 COBJ_EXT(cobj)->projection_param.perspective.aspect,
                 COBJ_EXT(cobj)->projection_param.frustum.left,
                 COBJ_EXT(cobj)->projection_param.frustum.right, cobj->near, cobj->far);
        break;
    }
    return projection_type;
}

void HSD_CObjReqAnim(HSD_CObj* cobj, float startframe)
{
    if (cobj == NULL) {
        return;
    }

    if (cobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(cobj->aobj, startframe);
    HSD_WObjReqAnim(cobj->eyepos, startframe);
    HSD_WObjReqAnim(cobj->interest, startframe);
}

void HSD_CObjAnim(HSD_CObj* cobj)
{
    if (cobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(cobj->aobj, cobj, HSD_COBJ_METHOD(cobj)->update);
    HSD_WObjInterpretAnim(cobj->eyepos);
    HSD_WObjInterpretAnim(cobj->interest);
}

static void CObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_CObj* cobj = obj;
    Vec3 vec;

    if (cobj == NULL) {
        return;
    }

    switch (type) {
    case 1:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 2:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.y = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 3:
        HSD_CObjGetEyePosition(cobj, &vec);
        vec.z = val->fv;
        HSD_CObjSetEyePosition(cobj, &vec);
        break;
    case 5:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 6:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 7:
        HSD_CObjGetInterest(cobj, &vec);
        vec.x = val->fv;
        HSD_CObjSetInterest(cobj, &vec);
        break;
    case 9:
        HSD_CObjSetRoll(cobj, val->fv);
        break;
    case 10:
        HSD_CObjSetFov(cobj, val->fv);
        break;
    case 11:
        HSD_CObjSetNear(cobj, val->fv);
        break;
    case 12:
        HSD_CObjSetFar(cobj, val->fv);
        break;
    }
}

void HSD_CObjAddAnim(HSD_CObj* cobj, HSD_CameraAnim* canim)
{
    if (cobj == NULL) {
        return;
    }

    if (canim == NULL) {
        return;
    }

    if (cobj->aobj != NULL) {
        HSD_AObjRemove(cobj->aobj);
    }
    cobj->aobj = HSD_AObjLoadDesc(canim->aobjdesc);
    HSD_WObjAddAnim(HSD_CObjGetEyePositionWObj(cobj), canim->eye_anim);
    HSD_WObjAddAnim(HSD_CObjGetInterestWObj(cobj), canim->interest_anim);
}

void HSD_CObjRemoveAnim(HSD_CObj* cobj) { HSD_WObj* wobj; if (cobj == NULL) return; if (cobj == NULL) return; HSD_AObjRemove(cobj->aobj); cobj->aobj = NULL; wobj = HSD_CObjGetEyePositionWObj(cobj); HSD_WObjRemoveAnim(wobj); wobj = HSD_CObjGetInterestWObj(cobj); HSD_WObjRemoveAnim(wobj); }
