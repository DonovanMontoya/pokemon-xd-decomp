/* XD joint traversal, animation attachment and matrix construction. */
#include "game/maximum/GSAPI/baselib/jobj.h"
typedef char jobj_flags_offset_check[(unsigned long)&((HSD_JObj*)0)->flags == 0x14 ? 1 : -1];
typedef char jobj_mtx_offset_check[(unsigned long)&((HSD_JObj*)0)->mtx == 0x44 ? 1 : -1];
typedef char jobj_aobj_offset_check[(unsigned long)&((HSD_JObj*)0)->aobj == 0x7C ? 1 : -1];
typedef char jobj_robj_offset_check[(unsigned long)&((HSD_JObj*)0)->robj == 0x80 ? 1 : -1];
typedef char jobj_id_offset_check[(unsigned long)&((HSD_JObj*)0)->id == 0x84 ? 1 : -1];
typedef char JObjRuntimeSizeCheck[sizeof(HSD_JObj) == 0x88 ? 1 : -1];
#include "game/maximum/GSAPI/baselib/dobj.h"
#include "game/maximum/GSAPI/baselib/robj.h"

typedef struct HSD_JObjInfo {
    HSD_ClassInfo parent;
    int (*load)(HSD_JObj*, HSD_Joint*, HSD_JObj*);
    void (*make_mtx)(HSD_JObj*);
    void (*make_pmtx)(HSD_JObj*,HSD_Mtx,HSD_Mtx);
    void (*disp)(HSD_JObj*,HSD_Mtx,HSD_Mtx,unsigned int,unsigned int);
    void (*release_child)(HSD_JObj*);
    HSD_ObjUpdateFunc update;
} HSD_JObjInfo;
struct HSD_Joint { char* class_name; unsigned int flags; HSD_Joint* child; HSD_Joint* next; union { HSD_DObjDesc* dobjdesc; void* spline; HSD_SList* ptcl; } u; HSD_Vec3 rotation,scale,position; HSD_Mtx* mtx; HSD_RObjDesc* robjdesc; };
#define HSD_JOBJ_METHOD(o) ((HSD_JObjInfo*)(o)->object.class_info)
#define HSD_OBJECT_PARENT_INFO(o) ((o)->parent.head.parent)
static void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };
extern HSD_ClassInfo hsdObj;
static int JObjInit(HSD_Class*);
static void JObjRelease(HSD_Class*);
static void JObjAmnesia(HSD_ClassInfo*);
static void JObjReleaseChild(HSD_JObj*);
static int JObjLoad(HSD_JObj*,HSD_Joint*,HSD_JObj*);
void HSD_JObjMakePositionMtx(HSD_JObj*,HSD_Mtx,HSD_Mtx);
void HSD_JObjDispSub(HSD_JObj*,HSD_Mtx,HSD_Mtx,unsigned int,unsigned int);
static void JObjUpdateFunc(void*,int,HSD_ObjData*);

static HSD_ClassInfo* default_class;
static HSD_SList* ufc_callbacks;
typedef void (*DPCtlCallback)(int,int,int,HSD_JObj*);
static DPCtlCallback dptcl_callback;
static void (*jsound_callback)(int);
static void (*ptcltgt_callback)(HSD_JObj*,int);
static HSD_JObj* current_jobj;
#define JOBJ_ROOT_MASK (7U << 28)
#define HSD_ASSERTREPORT(line, cond, msg) do { if (!(cond)) { OSReport(msg); __assert("jobj.c",line,#cond); } } while(0)
void OSReport(const char*,...);
void* HSD_IDGetDataFromTable(void*,unsigned int,void*);
void HSD_IDRemoveByIDFromTable(void*,unsigned int);

static int JObjInit(HSD_Class* o);
static void JObjReleaseChild(HSD_JObj* jobj);
static void JObjRelease(HSD_Class* o);
static void JObjAmnesia(HSD_ClassInfo* info);
void HSD_JObjUnref(HSD_JObj* jobj);
void HSD_JObjUnrefThis(HSD_JObj* jobj);
static inline HSD_JObj* HSD_JObjGetPrev(HSD_JObj* jobj);
HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj);
static inline void HSD_JObjRemoveAll(HSD_JObj* jobj);
static inline void RecalcParentTrspBits(HSD_JObj* jobj);
static inline void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child);
void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child);
static inline HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent);
void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next);
void HSD_JObjSetCurrent(HSD_JObj* jobj);
HSD_JObj* HSD_JObjGetCurrent(void);
void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint);
void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint);
void HSD_JObjCountVertices(HSD_JObj* jobj, unsigned int* vertices, unsigned int* triangles);
#define FILE_NAME "jobj.c"
typedef unsigned int u32; typedef float f32; typedef int s32; typedef int bool; typedef unsigned char u8;
#define NULL 0
#define false 0
#define true 1
void HSD_Panic(const char*, int, const char*);
void* memcpy(void*, const void*, unsigned long);
void* memset(void*, int, unsigned long);
#define HSD_ASSERT(line, cond) do { if (!(cond)) __assert(FILE_NAME, line, #cond); } while (0)

typedef HSD_Vec3 Vec3;
typedef struct HSD_MatAnimJoint { struct HSD_MatAnimJoint *child, *next; HSD_MatAnim* matanim; } HSD_MatAnimJoint;
typedef struct HSD_ShapeAnimJoint { struct HSD_ShapeAnimJoint *child, *next; HSD_ShapeAnimDObj* shapeanimdobj; } HSD_ShapeAnimJoint;
typedef void (*HSD_JObjWalkTreeCallback)(HSD_JObj*, float**, unsigned int);
#define JOBJ_CLASSICAL_SCALE (1 << 3)
#define JOBJ_MTX_DIRTY (1 << 6)
#define JOBJ_JOINT1 (1 << 21)
#define JOBJ_JOINT2 (2 << 21)
#define JOBJ_EFFECTOR (3 << 21)
#define JOBJ_USER_DEF_MTX (1 << 23)
#define JOBJ_MTX_INDEP_PARENT (1 << 24)
void PSMTXConcat(HSD_Mtx, HSD_Mtx, HSD_Mtx);
void PSMTXMultVec(HSD_Mtx, Vec3*, Vec3*);
#define MTXMultVec PSMTXMultVec
#define TYPE_JOBJ 12
void HSD_JObjCheckDepend(HSD_JObj* jobj);
static void HSD_JObjWalkTree0(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                       f32** cb_args);
void HSD_JObjWalkTree(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                      f32** cb_args);
static inline bool has_scl(HSD_JObj* jobj);
void HSD_JObjMakeMatrix(HSD_JObj* jobj);
void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjRemoveAnim(HSD_JObj* jobj);
void HSD_JObjRemoveAnimAll(HSD_JObj* jobj);
inline void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame);
void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame);
void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame);
void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame);
void JObjSortAnim(HSD_AObj* aobj);
inline void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* an_joint,
                     HSD_MatAnimJoint* mat_joint, HSD_ShapeAnimJoint* sh_joint);
void HSD_JObjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* ajoint,
                        HSD_MatAnimJoint* mjoint, HSD_ShapeAnimJoint* sjoint);
HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj);
void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj);
static inline HSD_RObj* robj_set_next(HSD_RObj* robj, HSD_RObj* next);
void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj);
void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj);
u32 HSD_JObjGetFlags(HSD_JObj* jobj);
inline void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags);
void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 flags);
inline void HSD_JObjClearFlags(HSD_JObj* jobj, u32 arg1);
void HSD_JObjClearFlagsAll(HSD_JObj* jobj, u32 flags);
void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj);

typedef int enum_t;
typedef void (*ufc_callback)(HSD_JObj*,unsigned int,float);
#define JOBJ_MTX_INDEP_SRT (1 << 25)
#define JOBJ_USE_QUATERNION (1 << 17)
#define JOBJ_HIDDEN (1 << 4)
#define union_type_spline(o) (((o)->flags & JOBJ_SPLINE) >> 14)
#define union_type_ptcl(o) (((o)->flags & JOBJ_PTCL) != 0)
void PSMTXIdentity(HSD_Mtx);
void PSMTXCopy(HSD_Mtx,HSD_Mtx);
void HSD_IDInsertToTable(void*,unsigned int,void*);
void splArcLengthPoint(HSD_Vec3*,void*,float);
HSD_JObj* HSD_JObjAlloc(void);

#define HSD_A_J_ROTX 1
#define HSD_A_J_ROTY 2
#define HSD_A_J_ROTZ 3
#define HSD_A_J_PATH 4
#define HSD_A_J_TRAX 5
#define HSD_A_J_TRAY 6
#define HSD_A_J_TRAZ 7
#define HSD_A_J_SCAX 8
#define HSD_A_J_SCAY 9
#define HSD_A_J_SCAZ 10
#define HSD_A_J_NODE 11
#define HSD_A_J_BRANCH 12
#define HSD_A_J_SETBYTE0 20
#define HSD_A_J_SETBYTE1 21
#define HSD_A_J_SETBYTE2 22
#define HSD_A_J_SETBYTE3 23
#define HSD_A_J_SETBYTE4 24
#define HSD_A_J_SETBYTE5 25
#define HSD_A_J_SETBYTE6 26
#define HSD_A_J_SETBYTE7 27
#define HSD_A_J_SETBYTE8 28
#define HSD_A_J_SETBYTE9 29
#define HSD_A_J_SETFLOAT0 30
#define HSD_A_J_SETFLOAT1 31
#define HSD_A_J_SETFLOAT2 32
#define HSD_A_J_SETFLOAT3 33
#define HSD_A_J_SETFLOAT4 34
#define HSD_A_J_SETFLOAT5 35
#define HSD_A_J_SETFLOAT6 36
#define HSD_A_J_SETFLOAT7 37
#define HSD_A_J_SETFLOAT8 38
#define HSD_A_J_SETFLOAT9 39

static void JObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);
void HSD_JObjAnim(HSD_JObj* jobj);
static void JObjAnimAll(HSD_JObj* jobj);
void HSD_JObjAnimAll(HSD_JObj* jobj);
static inline HSD_JObj* JObjLoadJointSub(HSD_Joint* joint, HSD_JObj* parent);
static s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* arg0);

static inline int ref_CNT(HSD_JObj* o);
static inline int iref_CNT(HSD_JObj* o);
static inline int ref_DEC(HSD_JObj* o);
static inline int iref_DEC(HSD_JObj* o);
static inline void iref_INC(HSD_JObj* o);
static inline void HSD_JObjRef(HSD_JObj* o);
static inline float fabsf_bitwise(float x);
static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj);
static inline void HSD_JObjSetTranslateX(HSD_JObj* jobj, float x);
static inline void HSD_JObjSetTranslateY(HSD_JObj* jobj, float y);
static inline void HSD_JObjSetTranslateZ(HSD_JObj* jobj, float z);
static inline void HSD_JObjSetRotationX(HSD_JObj* jobj, float x);
static inline void HSD_JObjSetRotationY(HSD_JObj* jobj, float y);
static inline void HSD_JObjSetRotationZ(HSD_JObj* jobj, float z);
static inline void HSD_JObjSetScaleX(HSD_JObj* jobj, float x);
static inline void HSD_JObjSetScaleY(HSD_JObj* jobj, float y);
static inline void HSD_JObjSetScaleZ(HSD_JObj* jobj, float z);
static inline void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags);
static inline void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags);
static inline void HSD_JObjRemoveAnimAll(HSD_JObj* jobj);
static inline HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj);
static inline void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj);
static inline void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj);
static inline void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj);
void HSD_JObjSetDPtclCallback(DPCtlCallback cb);
void HSD_JObjSetPtclTargetCallback(void (*cb)(HSD_JObj*,int));

#include "game/maximum/GSAPI/baselib/math_support.h"
#define sqrtf hsdSqrt
#define JOBJ_JOINT (3 << 21)
#define M_PI 3.14159265358979323846F
double acos(double);
void PSVECAdd(HSD_Vec3*,HSD_Vec3*,HSD_Vec3*);
void PSVECSubtract(HSD_Vec3*,HSD_Vec3*,HSD_Vec3*);
void PSVECScale(HSD_Vec3*,HSD_Vec3*,float);
void PSVECCrossProduct(HSD_Vec3*,HSD_Vec3*,HSD_Vec3*);
void PSVECNormalize(HSD_Vec3*,HSD_Vec3*);
float PSVECDotProduct(HSD_Vec3*,HSD_Vec3*);
void PSMTXRotAxisRad(HSD_Mtx,HSD_Vec3*,float);
#define VECScale PSVECScale
#define VECAdd PSVECAdd
#define VECSubtract PSVECSubtract
#define VECDotProduct PSVECDotProduct
#define VECCrossProduct PSVECCrossProduct
#define VECNormalize PSVECNormalize
static inline HSD_JObj* jobj_get_joint2(HSD_JObj* jobj);
static inline HSD_JObj* jobj_get_effector(HSD_JObj* jobj);
static inline HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff);
static void resolveIKJoint1(HSD_JObj* jobj);
static void resolveIKJoint2(HSD_JObj* jobj);
void HSD_JObjSetupMatrixSub(HSD_JObj* jobj);

HSD_CObj* HSD_CObjGetCurrent(void);
void HSD_JObjDisp(HSD_JObj*,HSD_Mtx,unsigned int,unsigned int);
int PSMTXInverse(HSD_Mtx,HSD_Mtx);

static inline void setupInstanceMtx(HSD_Mtx view, HSD_JObj* jobj, HSD_Mtx out);
void HSD_JObjDispAll(HSD_JObj* jobj, HSD_Mtx view, unsigned int flags, unsigned int rendermode);

static inline int ref_CNT(HSD_JObj* o) { return o->object.ref_count == 0xffff ? -1 : o->object.ref_count; }

static inline float fabsf_bitwise(float x) { union { float f; unsigned int u; } v; v.f=x; v.u &= 0x7fffffff; return v.f; }

static inline void HSD_JObjSetTranslateX(HSD_JObj* jobj, float x)
{
    if (!(jobj)) __assert("jobj.h",932,"jobj");
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateY(HSD_JObj* jobj, float y)
{
    if (!(jobj)) __assert("jobj.h",947,"jobj");
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetTranslateZ(HSD_JObj* jobj, float z)
{
    if (!(jobj)) __assert("jobj.h",962,"jobj");
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationX(HSD_JObj* jobj, float x)
{
    if (!(jobj)) __assert("jobj.h",639,"jobj");
    if (!(!(jobj->flags & JOBJ_USE_QUATERNION))) __assert("jobj.h",640,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj* jobj, float y)
{
    if (!(jobj)) __assert("jobj.h",660,"jobj");
    if (!(!(jobj->flags & JOBJ_USE_QUATERNION))) __assert("jobj.h",661,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetRotationZ(HSD_JObj* jobj, float z)
{
    if (!(jobj)) __assert("jobj.h",681,"jobj");
    if (!(!(jobj->flags & JOBJ_USE_QUATERNION))) __assert("jobj.h",682,"!(jobj->flags & JOBJ_USE_QUATERNION)");
    jobj->rotate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleX(HSD_JObj* jobj, float x)
{
    if (!(jobj)) __assert("jobj.h",776,"jobj");
    jobj->scale.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj* jobj, float y)
{
    if (!(jobj)) __assert("jobj.h",791,"jobj");
    jobj->scale.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline void HSD_JObjSetScaleZ(HSD_JObj* jobj, float z)
{
    if (!(jobj)) __assert("jobj.h",806,"jobj");
    jobj->scale.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline bool has_scl(HSD_JObj* jobj)
{
    bool result = false;
    if (jobj != NULL && jobj->scl != NULL) {
        result = true;
    }
    return result;
}

static inline void HSD_JObjRemoveAnimByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjRemove(jobj->aobj);
            jobj->aobj = NULL;
        }
        if (union_type_dobj(jobj)) {
            HSD_DObjRemoveAnimAllByFlags(jobj->u.dobj, flags);
        }
        HSD_RObjRemoveAnimAllByFlags(jobj->robj, flags);
    }
}

static inline void HSD_JObjRemoveAnimAllByFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjRemoveAnimByFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjRemoveAnimAllByFlags(child, flags);
                child = child->next;
            }
        }
    }
}

static inline void HSD_JObjRemoveAnimAll(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimAllByFlags(jobj, 0x7FF);
}

static inline HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj)
{
    if (jobj == NULL || !union_type_dobj(jobj)) {
        return NULL;
    }
    return jobj->u.dobj;
}

static inline void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj == NULL || dobj == NULL || !union_type_dobj(jobj)) {
        return;
    }
    dobj->next = jobj->u.dobj;
    jobj->u.dobj = dobj;
}

static inline HSD_RObj* robj_set_next(HSD_RObj* robj, HSD_RObj* next)
{
    if (robj == NULL) {
        return next;
    }
    robj->next = next;
    return robj;
}

static inline void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    jobj->robj = robj_set_next(robj, jobj->robj);
}

static inline void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    if (robj != NULL) {
        HSD_RObj** cur_ptr = &jobj->robj;
        HSD_RObj* cur;
        while (*cur_ptr != NULL) {
            cur = *cur_ptr;
            if (cur == robj) {
                *cur_ptr = cur->next;
                robj->next = NULL;
                return;
            }
            cur_ptr = &cur->next;
        }
    }
}

static inline HSD_JObj* HSD_JObjGetPrev(HSD_JObj* jobj)
{
    HSD_JObj* cur;

    if (jobj == NULL || jobj->parent == NULL) {
        return NULL;
    }
    if (jobj == jobj->parent->child) {
        return NULL;
    }
    cur = jobj->parent->child;
    while (cur != NULL) {
        if (cur->next == jobj) {
            return cur;
        }
        cur = cur->next;
    }
    HSD_Panic("jobj.c", 1531,
              "can not find specified jobj. maybe jobj tree is broken.\n");
    return NULL;
}

static inline void HSD_JObjRemoveAll(HSD_JObj* jobj)
{
    HSD_JObj* prev;
    HSD_JObj* next;

    if (jobj == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        prev = HSD_JObjGetPrev(jobj);
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            jobj->parent->child = NULL;
        }
    }
    while (jobj != NULL) {
        next = jobj->next;
        jobj->parent = NULL;
        jobj->next = NULL;
        HSD_JObjUnref(jobj);
        jobj = next;
    }
}

static inline void RecalcParentTrspBits(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        HSD_JObj* child = jobj->child;
        u32 flags = ~JOBJ_ROOT_MASK;
        while (child != NULL) {
            flags |= (child->flags | child->flags << 10) & JOBJ_ROOT_MASK;
            child = child->next;
        }
        if (!(jobj->flags & ~flags)) {
            break;
        }
        jobj->flags &= flags;
        jobj = jobj->next;
    }
}

static inline void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child)
{
    u32 flags = (child->flags | (child->flags << 10)) & JOBJ_ROOT_MASK;
    while (jobj != NULL) {
        if (!(flags & ~jobj->flags)) {
            break;
        }
        jobj->flags |= flags;
        jobj = jobj->parent;
    }
}

static inline HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent)
{
    HSD_JObj* next;

    if (jobj == NULL) {
        return NULL;
    }
    next = jobj->next;
    if (jobj->parent != NULL) {
        if (jobj->parent->child == jobj) {
            jobj->parent->child = next;
        } else {
            HSD_JObj* prev = HSD_JObjGetPrev(jobj);
            HSD_ASSERT(0x57E, prev);
            prev->next = next;
        }
        RecalcParentTrspBits(jobj->parent);
        jobj->parent = NULL;
    }
    jobj->next = NULL;
    HSD_JObjAddChild(parent, jobj);
    return next;
}

static inline HSD_JObj* JObjLoadJointSub(HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_JObj* jobj;
    HSD_ClassInfo* info;
    if (joint == NULL) {
        return NULL;
    }
    if (joint->class_name == NULL ||
        !(info = hsdSearchClassInfo(joint->class_name)))
    {
        jobj = HSD_JObjAlloc();
    } else {
        jobj = hsdNew(info);
        HSD_ASSERT(980, jobj);
    }
    HSD_JOBJ_METHOD(jobj)->load(jobj, joint, parent);
    return jobj;
}

static inline HSD_JObj* jobj_get_joint2(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

static inline HSD_JObj* jobj_get_effector(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        if ((jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR) {
            return jobj;
        }
        jobj = jobj->next;
    }
    return NULL;
}

static inline HSD_JObj* jobj_get_effector_checked(HSD_JObj* eff)
{
    eff = jobj_get_effector(eff);
    HSD_ASSERT(2096, eff);
    if (HSD_RObjGetByType(eff->robj, REFTYPE_JOBJ, 1) != NULL) {
        return eff;
    } else {
        return NULL;
    }
}

void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }

    if (!HSD_JObjMtxIsDirty(jobj)) {
        if ((jobj->flags & JOBJ_USER_DEF_MTX)) {
            if (!(jobj->flags & JOBJ_MTX_INDEP_PARENT) &&
                jobj->parent != NULL && HSD_JObjMtxIsDirty(jobj->parent))
            {
                jobj->flags |= JOBJ_MTX_DIRTY;
            }
        } else if ((jobj->parent != NULL &&
                    (jobj->parent->flags & JOBJ_MTX_DIRTY)) ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT1 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR ||
                   jobj->robj != NULL)
        {
            jobj->flags |= JOBJ_MTX_DIRTY;
        }
    }
}

static void HSD_JObjWalkTree0(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                       f32** cb_args)
{
    u32 type;

    if (jobj == NULL) {
        return;
    }
    HSD_ASSERT(0xAC, jobj->parent);
    type = jobj->parent->child == jobj ? 1 : 2;
    if (cb != NULL) {
        cb(jobj, cb_args, type);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, cb_args);
            child = child->next;
        }
    }
}

void HSD_JObjWalkTree(HSD_JObj* jobj, HSD_JObjWalkTreeCallback cb,
                      f32** cb_args)
{
    if (jobj == NULL) {
        return;
    }
    if (cb != NULL) {
        cb(jobj, cb_args, 0);
    }
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            HSD_JObjWalkTree0(child, cb, cb_args);
            child = child->next;
        }
    }
}

void HSD_JObjMakeMatrix(HSD_JObj* jobj)
{
    Vec3* scl;

    HSD_JObjSetupMatrix(jobj->parent);
    if (jobj->flags & 8) {
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            if (jobj->scl == NULL) {
                jobj->scl = HSD_VecAlloc();
            }
            *jobj->scl = *jobj->parent->scl;
        } else {
            if (jobj->scl != NULL) {
                HSD_VecFree(jobj->scl);
                jobj->scl = NULL;
            }
        }
    } else {
        if (jobj->scl == NULL) {
            jobj->scl = HSD_VecAlloc();
        }
        if (jobj->parent != NULL && jobj->parent->scl != NULL) {
            jobj->scl->x = jobj->scale.x * jobj->parent->scl->x;
            jobj->scl->y = jobj->scale.y * jobj->parent->scl->y;
            jobj->scl->z = jobj->scale.z * jobj->parent->scl->z;
        } else {
            *jobj->scl = jobj->scale;
        }
    }
    if (jobj->flags & 0x20000) {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRTQuat(jobj->mtx, &jobj->scale, &jobj->rotate,
                       &jobj->translate, scl);
    } else {
        if (has_scl(jobj->parent)) {
            scl = jobj->parent->scl;
        } else {
            scl = NULL;
        }
        HSD_MtxSRT(jobj->mtx, &jobj->scale, (Vec3*) &jobj->rotate,
                   &jobj->translate, scl);
    }
    if (jobj->parent != NULL) {
        PSMTXConcat(jobj->parent->mtx, jobj->mtx, jobj->mtx);
    }
    if (jobj->aobj != NULL && jobj->aobj->hsd_obj != NULL) {
        Vec3 vec;
        HSD_JObj* aobj_jobj = (HSD_JObj*) jobj->aobj->hsd_obj;
        HSD_JObjSetupMatrix((HSD_JObj*) jobj->aobj->hsd_obj);
        MTXMultVec(aobj_jobj->mtx, &jobj->translate, &vec);
        jobj->mtx[0][3] = vec.x;
        jobj->mtx[1][3] = vec.y;
        jobj->mtx[2][3] = vec.z;
    }
}

void HSD_JObjRemoveAnim(HSD_JObj* jobj)
{
    HSD_JObjRemoveAnimByFlags(jobj, 0x7FF);
}

inline void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    bool has_dobj;
    if (jobj != NULL) {
        if (flags & 1) {
            HSD_AObjReqAnim(jobj->aobj, frame);
        }
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = false;
        } else {
            has_dobj = true;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->u.dobj, frame, flags);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, frame, flags);
    }
}

void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, u32 flags, f32 frame)
{
    if (jobj != NULL) {
        HSD_JObjReqAnimByFlags(jobj, flags, frame);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* child = jobj->child;
            while (child != NULL) {
                HSD_JObjReqAnimAllByFlags(child, flags, frame);
                child = child->next;
            }
        }
    }
}

void HSD_JObjReqAnimAll(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 0x7FF, frame);
}

void HSD_JObjReqAnim(HSD_JObj* jobj, f32 frame)
{
    HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame);
}

void JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == NULL || aobj->fobj == NULL) {
        return;
    }
    for (fobj_ptr = &aobj->fobj; *fobj_ptr != NULL; fobj_ptr = &fobj->next) {
        fobj = *fobj_ptr;
        if (fobj->obj_type == TYPE_JOBJ) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
    }
}

inline void HSD_JObjAddAnim(HSD_JObj* jobj, HSD_AnimJoint* an_joint,
                     HSD_MatAnimJoint* mat_joint, HSD_ShapeAnimJoint* sh_joint)
{
    if (jobj != NULL) {
        if (an_joint != NULL) {
            if (jobj->aobj != NULL) {
                HSD_AObjRemove(jobj->aobj);
            }
            jobj->aobj = HSD_AObjLoadDesc(an_joint->aobjdesc);
            JObjSortAnim(jobj->aobj);
            HSD_RObjAddAnimAll(jobj->robj, an_joint->robj_anim);
            if (an_joint->flags & 1) {
                HSD_JObjSetFlags(jobj, JOBJ_CLASSICAL_SCALE);
            } else {
                HSD_JObjClearFlags(jobj, JOBJ_CLASSICAL_SCALE);
            }
        }
        if (union_type_dobj(jobj)) {
            HSD_DObjAddAnimAll(
                jobj->u.dobj, mat_joint != NULL ? mat_joint->matanim : NULL,
                sh_joint != NULL ? sh_joint->shapeanimdobj : NULL);
        }
    }
}

void HSD_JObjAddAnimAll(HSD_JObj* jobj, HSD_AnimJoint* ajoint,
                        HSD_MatAnimJoint* mjoint, HSD_ShapeAnimJoint* sjoint)
{
    HSD_JObj* jp;
    HSD_AnimJoint* aj;
    HSD_MatAnimJoint* mj;
    HSD_ShapeAnimJoint* sj;

    if (jobj != NULL) {
        HSD_JObjAddAnim(jobj, ajoint, mjoint, sjoint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            jp = jobj->child;
            aj = ajoint != NULL ? ajoint->child : NULL;
            mj = mjoint != NULL ? mjoint->child : NULL;
            sj = sjoint != NULL ? sjoint->child : NULL;
            while (jp != NULL) {
                HSD_JObjAddAnimAll(jp, aj, mj, sj);
                jp = jp->next;
                aj = aj != NULL ? aj->next : NULL;
                mj = mj != NULL ? mj->next : NULL;
                sj = sj != NULL ? sj->next : NULL;
            }
        }
    }
}

static void JObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_JObj* jobj = obj;
    ufc_callback cb;
    Vec3 p;
    HSD_JObj* jp;
    HSD_RObj* robj;
    HSD_Mtx mtx;

    if (jobj != NULL) {
        switch (type) {
        case HSD_A_J_PATH:
            if (val->fv < 0.0L) {
                val->fv = 0.0F;
            }
            if (1.0L < val->fv) {
                val->fv = 1.0F;
            }
            HSD_ASSERT(0x24B, jobj->aobj);
            jp = (HSD_JObj*) jobj->aobj->hsd_obj;
            HSD_ASSERT(0x24D, jp);
            HSD_ASSERT(0x24E, jp->u.spline);
            splArcLengthPoint(&p, jp->u.spline, val->fv);
            HSD_JObjSetTranslateX(jobj, p.x);
            HSD_JObjSetTranslateY(jobj, p.y);
            HSD_JObjSetTranslateZ(jobj, p.z);
            break;
        case HSD_A_J_ROTX:
            if (jobj->flags & JOBJ_JOINT1) {
                robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    ROBJ_U(robj).ik_hint.rotate_x = val->fv;
                }
            }
            HSD_JObjSetRotationX(jobj, val->fv);
            break;
        case HSD_A_J_ROTY:
            HSD_JObjSetRotationY(jobj, val->fv);
            break;
        case HSD_A_J_ROTZ:
            HSD_JObjSetRotationZ(jobj, val->fv);
            break;
        case HSD_A_J_TRAX:
            HSD_JObjSetTranslateX(jobj, val->fv);
            break;
        case HSD_A_J_TRAY:
            HSD_JObjSetTranslateY(jobj, val->fv);
            break;
        case HSD_A_J_TRAZ:
            HSD_JObjSetTranslateZ(jobj, val->fv);
            break;
        case HSD_A_J_SCAX:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleX(jobj, val->fv);
            break;
        case HSD_A_J_SCAY:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleY(jobj, val->fv);
            break;
        case HSD_A_J_SCAZ:
            if (fabsf_bitwise(val->fv) < 1e-3F) {
                val->fv = 1e-3F;
            }
            HSD_JObjSetScaleZ(jobj, val->fv);
            break;
        case HSD_A_J_BRANCH:
            if (val->fv > 0.5) {
                HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_NODE:
            if (val->fv > 0.5) {
                HSD_JObjClearFlags(jobj, JOBJ_HIDDEN);
            } else {
                HSD_JObjSetFlags(jobj, JOBJ_HIDDEN);
            }
            break;
        case HSD_A_J_SETBYTE0:
        case HSD_A_J_SETBYTE1:
        case HSD_A_J_SETBYTE2:
        case HSD_A_J_SETBYTE3:
        case HSD_A_J_SETBYTE4:
        case HSD_A_J_SETBYTE5:
        case HSD_A_J_SETBYTE6:
        case HSD_A_J_SETBYTE7:
        case HSD_A_J_SETBYTE8:
        case HSD_A_J_SETBYTE9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->iv);
                callback_node = callback_node->next;
            }
            break;
        }
        case HSD_A_J_SETFLOAT0:
        case HSD_A_J_SETFLOAT1:
        case HSD_A_J_SETFLOAT2:
        case HSD_A_J_SETFLOAT3:
        case HSD_A_J_SETFLOAT4:
        case HSD_A_J_SETFLOAT5:
        case HSD_A_J_SETFLOAT6:
        case HSD_A_J_SETFLOAT7:
        case HSD_A_J_SETFLOAT8:
        case HSD_A_J_SETFLOAT9: {
            HSD_SList* callback_node = ufc_callbacks;
            while (callback_node != NULL) {
                cb = callback_node->data;
                cb(jobj, type, val->fv);
                callback_node = callback_node->next;
            }
            break;
        }
        case 0x28: {
            s32 iv = val->iv;
            s32 lo = iv & 0x3F;
            s32 hi = iv >> 6 & 0xFFFFFF;
            if (dptcl_callback != NULL) {
                dptcl_callback(0, lo, hi, jobj);
            }
        } break;
        case 0x29:
            if (jsound_callback != NULL) {
                jsound_callback(val->iv);
            }
            break;
        case 0x2A:
            if (ptcltgt_callback != NULL) {
                ptcltgt_callback(jobj, val->iv);
            }
            break;
        case 0x32:
            jobj->mtx[0][0] = val->p.x;
            jobj->mtx[1][0] = val->p.y;
            jobj->mtx[2][0] = val->p.z;
            break;
        case 0x33:
            jobj->mtx[0][1] = val->p.x;
            jobj->mtx[1][1] = val->p.y;
            jobj->mtx[2][1] = val->p.z;
            break;
        case 0x34:
            jobj->mtx[0][2] = val->p.x;
            jobj->mtx[1][2] = val->p.y;
            jobj->mtx[2][2] = val->p.z;
            break;
        case 0x35:
            jobj->mtx[0][3] = val->p.x;
            jobj->mtx[1][3] = val->p.y;
            jobj->mtx[2][3] = val->p.z;
            break;
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
            if (jobj->parent != NULL) {
                HSD_MtxInverseConcat(jobj->parent->mtx, jobj->mtx, mtx);
            } else {
                PSMTXCopy(jobj->mtx, mtx);
            }
            if (type == 0x36U || type == 0x38U) {
                HSD_MtxGetTranslate(mtx, &jobj->translate);
            }
            if (type == 0x36 || type == 0x37) {
                HSD_MtxGetRotation(mtx, (Vec3*) &jobj->rotate);
            }
            if (type == 0x36U || type == 0x39U) {
                HSD_MtxGetScale(mtx, &jobj->scale);
            }
            break;
        }
    }
}

void HSD_JObjAnim(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_JObjCheckDepend(jobj);
        HSD_AObjInterpretAnim(jobj->aobj, jobj, HSD_JOBJ_METHOD(jobj)->update);
        HSD_RObjAnimAll(jobj->robj);
        if (union_type_dobj(jobj)) {
            HSD_DObjAnimAll(jobj->u.dobj);
        }
    }
}

static void JObjAnimAll(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if (jobj != NULL) {
        HSD_JObjAnim(jobj);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            child = jobj->child;
            while (child != NULL) {
                JObjAnimAll(child);
                child = child->next;
            }
        }
    }
}

void HSD_JObjAnimAll(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_AObjInitEndCallBack();
        JObjAnimAll(jobj);
        HSD_AObjInvokeCallBacks();
    }
}

static inline float (*HSD_CObjGetViewingMtxPtrDirect(HSD_CObj* cobj))[4]
{
    return cobj->view_mtx;
}

static inline void setupInstanceMtx(HSD_Mtx view, HSD_JObj* jobj, HSD_Mtx out) {
    HSD_JObjSetupMatrix(jobj);
    HSD_JObjSetupMatrix(jobj->child);
    PSMTXInverse(jobj->child->mtx,out);
    PSMTXConcat(jobj->mtx,out,out);
    if (view) PSMTXConcat(view,out,out);
    else {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        if (cobj) PSMTXConcat(HSD_CObjGetViewingMtxPtrDirect(cobj),out,out);
    }
}

void HSD_JObjDispAll(HSD_JObj* jobj, HSD_Mtx view, unsigned int flags, unsigned int rendermode) {
    if (jobj) {
        if (jobj->flags & JOBJ_INSTANCE) {
            if (!(jobj->flags & JOBJ_HIDDEN)) {
                HSD_Mtx instance;
                setupInstanceMtx(view,jobj,instance);
                HSD_JObjDispAll(jobj->child,instance,flags,rendermode);
            }
        } else {
            if (jobj->flags & (flags << 18)) HSD_JObjDisp(jobj,view,flags,rendermode);
            if (jobj->flags & (flags << 28)) {
                HSD_JObj* child = jobj->child;
                while (child) {
                    HSD_JObjDispAll(child,view,flags,rendermode);
                    child = child->next;
                }
            }
        }
    }
}

static s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    jobj->child = NULL;
    jobj->next = NULL;
    jobj->parent = NULL;
    jobj->flags |= joint->flags;
    if (union_type_spline(jobj)) {
        jobj->u.spline = joint->u.spline;
    } else if (union_type_ptcl(jobj)) {
        HSD_SList* slist;
        jobj->u.ptcl = joint->u.ptcl;
        slist = joint->u.ptcl;
        while (slist != NULL) {
            *(u32*) &slist->data |= 0x80000000;
            slist = slist->next;
        }
    } else {
        jobj->u.dobj = HSD_DObjLoadDesc(joint->u.dobjdesc);
    }
    jobj->robj = HSD_RObjLoadDesc(joint->robjdesc);
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    PSMTXIdentity(jobj->mtx);
    jobj->scl = NULL;
    if (joint->mtx != NULL) {
        jobj->envelopemtx = HSD_MtxAlloc();
        memcpy(jobj->envelopemtx, joint->mtx, sizeof(HSD_Mtx));
    }
    HSD_IDInsertToTable(NULL, (HSD_IDKey) joint, jobj);
    jobj->id = (HSD_IDKey) joint;
    if (!(joint->flags & JOBJ_INSTANCE)) {
        for (joint = joint->child; joint != NULL; joint = joint->next) {
            HSD_JObj* child = JObjLoadJointSub(joint, jobj);
            if (child == NULL) return -1;
            HSD_JObjAddChild(jobj, child);
        }
    }
    return 0;
}

HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* arg0)
{
    HSD_JObj* jobj = JObjLoadJointSub(arg0, 0);
    HSD_JObjResolveRefsAll(jobj, arg0);
    return jobj;
}

static inline void* HSD_IDGetData(HSD_IDKey id, void* found)
{
    return HSD_IDGetDataFromTable(NULL, id, found);
}

static inline void ref_INC(HSD_JObj* o)
{
    ++o->object.ref_count;
    if (o->object.ref_count == 0xffff)
        __assert("object.h", 93, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
}

void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    if (jobj == NULL || joint == NULL) {
        return;
    }

    HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
    if (!!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObjUnref(jobj->child);
        jobj->child =
            HSD_IDGetData((HSD_IDKey) joint->child, NULL);
        HSD_ASSERT(1122, jobj->child);
        HSD_JObjRef(jobj->child);
    }
    if (union_type_dobj(jobj)) {
        HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
    }
}

static inline int ref_DEC(HSD_JObj* o) {
    int ret;
    if ((ret = (o->object.ref_count == 0xffff))) return ret;
    return o->object.ref_count-- == 0;
}

static inline int iref_CNT(HSD_JObj* o) { return o->object.ref_count_individual - 1; }

static inline void iref_INC(HSD_JObj* o) {
    ++o->object.ref_count_individual;
    if (!o->object.ref_count_individual) __assert("object.h",158,"HSD_OBJ(o)->ref_count_individual != 0");
}

static inline int iref_DEC(HSD_JObj* o) {
    int ret;
    if ((ret = (o->object.ref_count_individual == 0))) return ret;
    o->object.ref_count_individual -= 1;
    return o->object.ref_count_individual == 0;
}

static inline void HSD_JObjRef(HSD_JObj* o) {
    if (o) ref_INC(o);
}

void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    while (jobj != NULL && joint != NULL) {
        HSD_JObjResolveRefs(jobj, joint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObjResolveRefsAll(jobj->child, joint->child);
        }
        jobj = jobj->next;
        joint = joint->next;
    }
}

void HSD_JObjUnref(HSD_JObj* jobj)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) < 0) {
            hsdDelete(jobj);
        } else {
            iref_INC(jobj);
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                hsdDelete(jobj);
            }
        }
    }
}

void HSD_JObjUnrefThis(HSD_JObj* jobj)
{
    if (jobj != NULL && iref_DEC(jobj) && ref_CNT(jobj) < 0) {
        hsdDelete(jobj);
    }
}

HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj)
{
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* prev;

    if (jobj == NULL) {
        return 0;
    }
    child = jobj->child;
    if (child != NULL) {
        HSD_ASSERT(1230, child->next == NULL);
    }

    next = child != NULL ? child : jobj->next;

    prev = HSD_JObjGetPrev(jobj);
    if (prev != NULL) {
        prev->next = next;
    } else if (jobj->parent != NULL) {
        jobj->parent->child = next;
    }
    if (next != NULL && next == child) {
        next->next = jobj->next;
        next->parent = jobj->parent;
    }
    jobj->parent = NULL;
    jobj->child = NULL;
    jobj->next = NULL;
    HSD_JObjUnref(jobj);
    return child;
}

void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child)
{
    HSD_JObj* last;

    if (jobj == NULL || child == NULL) {
        return;
    }
    HSD_ASSERTREPORT(1365, child->parent == NULL,
                     "child should be a orphan.\n");
    HSD_ASSERTREPORT(1366, child->next == NULL,
                     "child should not have siblings");
    if (jobj->child == NULL) {
        jobj->child = child;
    } else {
        HSD_ASSERT(1372, !(jobj->flags & JOBJ_INSTANCE));
        last = jobj->child;
        while (last->next != NULL) {
            HSD_ASSERT(1375, last != child);
            last = last->next;
        }
        last->next = child;
    }
    child->parent = jobj;
    UpdateParentTrspBits(jobj, child);
}

void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next)
{
    if (!jobj || !next) return;
    HSD_JObjReparent(next, NULL);
    next->parent = jobj->parent;
    next->next = jobj->next;
    jobj->next = next;
    if (jobj->parent) UpdateParentTrspBits(jobj->parent, next);
}

u32 HSD_JObjGetFlags(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        return jobj->flags;
    }
    return 0;
}

inline void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ flags) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags |= flags;
    }
}

void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjSetFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjSetFlagsAll(i, flags);
            }
        }
    }
}

inline void HSD_JObjClearFlags(HSD_JObj* jobj, u32 arg1)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ arg1) & JOBJ_CLASSICAL_SCALE) {
            // manually inlined HSD_JObjSetMtxDirty
            if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
        jobj->flags &= ~arg1;
    }
}

void HSD_JObjClearFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjClearFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjClearFlagsAll(i, flags);
            }
        }
    }
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        switch (HSD_JObjMtxIsDirty(jobj)) {
        case false: HSD_JObjSetMtxDirtySub(jobj); break;
        }
    }
}

HSD_JObj* HSD_JObjAlloc(void)
{
    HSD_JObj* jobj =
        hsdNew(default_class != NULL ? default_class : &hsdJObj.parent);
    HSD_ASSERT(2018, jobj);
    return jobj;
}

void HSD_JObjCountVertices(HSD_JObj* jobj, unsigned int* vertices, unsigned int* triangles) {
    unsigned int total_v = 0, total_t = 0;
    HSD_JObj* child;
    if (jobj) {
        if (jobj->flags & JOBJ_INSTANCE) {
            HSD_JObjCountVertices(jobj->child, &total_v, &total_t);
        } else {
            if (!(jobj->flags & 0x10) && union_type_dobj(jobj))
                HSD_DObjCountVertices(jobj->u.dobj, &total_v, &total_t);
            for (child = jobj->child; child; child = child->next) {
                unsigned int nv, nt;
                HSD_JObjCountVertices(child, &nv, &nt);
                total_v += nv; total_t += nt;
            }
        }
    }
    if (vertices) *vertices = total_v;
    if (triangles) *triangles = total_t;
}

void HSD_JObjSetCurrent(HSD_JObj* jobj)
{
    HSD_JObjRef(jobj);
    HSD_JObjUnref(current_jobj);
    current_jobj = jobj;

}

HSD_JObj* HSD_JObjGetCurrent(void)
{
    return current_jobj;
}

static void resolveIKJoint1(HSD_JObj* jobj)
{
    HSD_JObj* robj_4;
    HSD_JObj* var_r28;
    HSD_JObj* var_r31;
    Vec3* temp_r4;
    f32 temp_f1_7;
    f32 temp_f31;
    f32 temp_f30;
    f32 temp_f5;
    f32 temp_f5_2;
    Vec3 spBC = { 1.0F, 1.0F, 1.0F };
    f32 var_f1;
    f32 var_f29;
    f32 var_f29_2;
    f32 var_f28;
    f32 var_f27;
    f32 temp_f26;
    f32 var_f4;
    f32 var_f4_2;
    Vec3 spB0;

    u8 _[4];

    f32 var_f4_3;
    f32 var_f4_4;
    f32 var_f5;
    s32 var_r30;
    HSD_RObj* robj;
    Vec3 sp98;
    Vec3 sp8C;
    Vec3 sp80;
    HSD_IKHint* new_var;
    Vec3 sp74;
    Vec3 sp68;
    Vec3 sp5C;
    Vec3 sp50;
    HSD_Mtx sp20;

    var_r30 = 0;
    var_f29 = 0.0F;
    var_r31 = jobj_get_joint2(jobj->child);
    { Vec3 origin = {0.0F,0.0F,0.0F}; spB0 = origin; }
    temp_r4 = jobj->scl;
    var_f5 = 1e-8F;
    if (temp_r4 != NULL) {
        spBC = *temp_r4;
    }
    robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x85F, robj);
    new_var = &ROBJ_U(robj).ik_hint;
    temp_f26 = new_var->rotate_x;
    temp_f30 = new_var->bone_length * spBC.x;
    if (var_r31 != NULL) {
        robj = HSD_RObjGetByType(var_r31->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x86A, robj);
        var_f29 = ROBJ_U(robj).ik_hint.bone_length * var_r31->scale.x * spBC.x;
        var_r30 = robj->flags & 4 ? 1 : 0;
        var_r28 = jobj_get_effector_checked(var_r31->child);
    } else {
        var_r28 = jobj_get_effector_checked(jobj->child);
    }
    if (var_r28 != NULL) {
        if ((HSD_RObjGetByType(jobj->robj, REFTYPE_JOBJ, 3) == NULL) &&
            (jobj != NULL))
        {
            if (jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, HSD_JOBJ_METHOD(jobj)->update);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= 0xFFFFFFBF;
                }
            }
        }
        robj_4 = jobj->parent;
        if (robj_4 != NULL) {
            HSD_MtxGetTranslate(robj_4->mtx, &spB0);
        }
        HSD_RObjGetGlobalPosition(var_r28->robj, 1, &var_r28->translate);
        VECSubtract(&var_r28->translate, &spB0, &sp8C);
        temp_f31 = VECDotProduct(&sp8C, &sp8C);

        if (temp_f31 > var_f5) {
            sp68 = sp8C;
            if (HSD_RObjGetGlobalPosition(jobj->robj, 3, &sp5C)) {
                VECSubtract(&sp5C, &spB0, &sp5C);
                if (temp_f26 != 0.0F) {
                    PSMTXRotAxisRad(sp20, &sp68, temp_f26);
                    MTXMultVec(sp20, &sp5C, &sp5C);
                }
                VECCrossProduct(&sp68, &sp5C, &sp50);
                VECCrossProduct(&sp50, &sp68, &sp5C);
            } else {
                sp50.x = jobj->mtx[0][2];
                sp50.y = jobj->mtx[1][2];
                sp50.z = jobj->mtx[2][2];
                VECCrossProduct(&sp50, &sp68, &sp5C);
                VECCrossProduct(&sp68, &sp5C, &sp50);
            }
            var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp50, &sp50)));
            VECScale(&sp50, &sp80, var_f4);
            var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp5C, &sp5C)));
            VECScale(&sp5C, &sp74, var_f4_2);
            temp_f5 = temp_f30 * temp_f30;
            var_f28 = var_f29 * var_f29;
            temp_f1_7 = temp_f5 - var_f28;
            var_f27 = 0.25F * (((2.0F * (temp_f5 + var_f28)) - temp_f31) -
                                 ((temp_f1_7 * temp_f1_7) / temp_f31));
            if (var_f27 < 0.0F) {
                var_f27 = 0.0F;
            }
            temp_f5_2 = (temp_f5 - var_f27) / temp_f31;
            var_f4_3 = sqrtf(1.0F / (1e-10F + temp_f5_2));
            var_f1 = temp_f5_2 * var_f4_3;
            var_f5 = sqrtf(1.0F / (1e-10F + var_f27));
            var_f29_2 = var_f27 * var_f5;
        } else {
            var_f1 = 0.0F;
            var_f29_2 = temp_f30;
        }
        if (var_r30 != 0) {
            var_f29_2 = -var_f29_2;
        }
        if ((var_f28 - var_f27) < temp_f31) {
            VECScale(&sp8C, &sp98, var_f1);
        } else {
            VECScale(&sp8C, &sp98, -var_f1);
        }
        VECScale(&sp74, &sp5C, var_f29_2);
        VECAdd(&sp98, &sp5C, &sp98);
        var_f4_4 = sqrtf(1.0F / (1e-10F + PSVECDotProduct(&sp98, &sp98)));
        VECScale(&sp98, &sp98, var_f4_4);
        jobj->mtx[0][0] = sp98.x * spBC.x;
        jobj->mtx[1][0] = sp98.y * spBC.x;
        jobj->mtx[2][0] = sp98.z * spBC.x;
        VECCrossProduct(&sp80, &sp98, &sp5C);
        jobj->mtx[0][1] = sp5C.x * spBC.y;
        jobj->mtx[1][1] = sp5C.y * spBC.y;
        jobj->mtx[2][1] = sp5C.z * spBC.y;
        jobj->mtx[0][2] = sp80.x * spBC.z;
        jobj->mtx[1][2] = sp80.y * spBC.z;
        jobj->mtx[2][2] = sp80.z * spBC.z;
        jobj->mtx[0][3] = spB0.x;
        jobj->mtx[1][3] = spB0.y;
        jobj->mtx[2][3] = spB0.z;
    }
}

#pragma force_active on
static const Vec3 ik_axis = {0.0F,0.0F,1.0F};
#pragma force_active reset

static void resolveIKJoint2(HSD_JObj* jobj)
{
    Vec3 spA0;
    Vec3 sp94;
    Vec3 sp88;
    Vec3 sp7C;
    Vec3 sp70;
    Vec3 sp64;
    HSD_Mtx sp34;
    Vec3 sp28;
    Vec3 sp1C;

    u8 _[4];

    HSD_JObj* var_r29;
    f32 temp_f1_4;
    f32 var_f1_2;
    f32 var_f31;
    f32 var_f4;
    f32 var_f4_2;
    s32 var_r27;
    s32 var_r30;
    HSD_RObj* temp_r28;
    HSD_RObj* temp_r29;
    HSD_RObj* robj;

    var_f31 = 1.0F;
    { Vec3 unit_scale = {1.0F,1.0F,1.0F}; spA0 = unit_scale; }
    var_r29 = jobj_get_effector_checked(jobj->child);
    if (var_r29 == NULL || jobj->parent == NULL) {
        return;
    }
    if (jobj->scl != NULL) {
        spA0 = *jobj->scl;
    }
    {
        float (*mtx)[4] = jobj->parent->mtx;
        sp88.x = mtx[0][3];
        sp88.y = mtx[1][3];
        sp88.z = mtx[2][3];
    }
    {
        float (*mtx)[4] = jobj->parent->mtx;
        sp7C.x = mtx[0][0];
        sp7C.y = mtx[1][0];
        sp7C.z = mtx[2][0];
    }
    var_f4 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp7C, &sp7C)));
    VECScale(&sp7C, &sp7C, var_f4);
    if (jobj->parent->scl != NULL) {
        var_f31 = jobj->parent->scl->x;
    }
    robj = HSD_RObjGetByType(jobj->parent->robj, REFTYPE_IKHINT, 0);
    HSD_ASSERT(0x908, robj);
    VECScale(&sp7C, &sp7C, ROBJ_U(robj).ik_hint.bone_length * var_f31);
    VECAdd(&sp88, &sp7C, &sp94);
    VECSubtract(&var_r29->translate, &sp94, &sp7C);
    VECScale(&sp7C, &sp7C,
             sqrtf(1.0F / (1e-10F + VECDotProduct(&sp7C, &sp7C))));
    temp_r28 = HSD_RObjGetByType(jobj->robj, 0x20000000, 5);
    temp_r29 = HSD_RObjGetByType(jobj->robj, 0x20000000, 6);
    if ((temp_r28 != NULL) || (temp_r29 != NULL)) {
        var_r27 = 0;
        robj = HSD_RObjGetByType(jobj->robj, REFTYPE_IKHINT, 0);
        HSD_ASSERT(0x92A, robj);
        var_r30 = robj->flags & 4 ? 1 : 0;
        {
            float (*mtx)[4] = jobj->parent->mtx;
            sp28.x = mtx[0][0];
            sp28.y = mtx[1][0];
            sp28.z = mtx[2][0];
        }
        VECNormalize(&sp28, &sp28);
        temp_f1_4 = VECDotProduct(&sp28, &sp7C);
        {
            f32 angle;
            if (temp_f1_4 >= 1.0F) angle = 0.0F;
            else if (temp_f1_4 <= -1.0F) angle = M_PI;
            else angle = (float)acos(temp_f1_4);
            var_f1_2 = angle;
            if (var_r30 == 0) var_f1_2 = -angle;
        }
        if (temp_r28 != NULL && var_f1_2 < ROBJ_U(temp_r28).limit) {
            var_f1_2 = ROBJ_U(temp_r28).limit;
            var_r27 = 1;
        } else if (temp_r29 != NULL) {
            if (ROBJ_U(temp_r29).limit < var_f1_2) {
                var_f1_2 = ROBJ_U(temp_r29).limit;
                var_r27 = 1;
            }
        }
        if (var_r27 != 0) {
            {
                float (*mtx)[4] = jobj->parent->mtx;
                sp1C.x = mtx[0][2];
                sp1C.y = mtx[1][2];
                sp1C.z = mtx[2][2];
            }
            PSMTXRotAxisRad(sp34, &sp1C, var_f1_2);
            MTXMultVec(sp34, &sp28, &sp7C);
        }
    }
    {
        float (*mtx)[4] = jobj->parent->mtx;
        sp64.x = mtx[0][2];
        sp64.y = mtx[1][2];
        sp64.z = mtx[2][2];
    }
    VECCrossProduct(&sp64, &sp7C, &sp70);
    var_f4_2 = sqrtf(1.0F / (1e-10F + VECDotProduct(&sp70, &sp70)));
    VECScale(&sp70, &sp70, var_f4_2);
    VECCrossProduct(&sp7C, &sp70, &sp64);
    jobj->mtx[0][0] = sp7C.x * spA0.x;
    jobj->mtx[1][0] = sp7C.y * spA0.x;
    jobj->mtx[2][0] = sp7C.z * spA0.x;
    jobj->mtx[0][1] = sp70.x * spA0.y;
    jobj->mtx[1][1] = sp70.y * spA0.y;
    jobj->mtx[2][1] = sp70.z * spA0.y;
    jobj->mtx[0][2] = sp64.x * spA0.z;
    jobj->mtx[1][2] = sp64.y * spA0.z;
    jobj->mtx[2][2] = sp64.z * spA0.z;
    jobj->mtx[0][3] = sp94.x;
    jobj->mtx[1][3] = sp94.y;
    jobj->mtx[2][3] = sp94.z;
}

void HSD_JObjSetupMatrixSub(HSD_JObj* jobj)
{
    Vec3 sp28;
    Vec3 sp1C;
    Vec3 sp10;
    HSD_JObj* parent;
    HSD_RObj* robj;
    f32 x_scale;

    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
    jobj->flags &= ~JOBJ_MTX_DIRTY;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX)) {
        switch (jobj->flags & JOBJ_JOINT) {
        case JOBJ_JOINT1:
            resolveIKJoint1(jobj);
            break;
        case JOBJ_JOINT2:
            resolveIKJoint2(jobj);
            break;
        case JOBJ_EFFECTOR:
            parent = jobj->parent;
            x_scale = 1.0F;
            if (parent != NULL) {
                robj = HSD_RObjGetByType(parent->robj, REFTYPE_IKHINT, 0);
                if (robj != NULL) {
                    sp1C.x = parent->mtx[0][3];
                    sp1C.y = parent->mtx[1][3];
                    sp1C.z = parent->mtx[2][3];
                    sp10.x = parent->mtx[0][0];
                    sp10.y = parent->mtx[1][0];
                    sp10.z = parent->mtx[2][0];
                    VECScale(
                        &sp10, &sp10,
                        sqrtf(1.0F / (1e-10F + VECDotProduct(&sp10, &sp10))));
                    if (parent->scl != NULL) {
                        x_scale = parent->scl->x;
                    }
                    VECScale(&sp10, &sp10,
                             ROBJ_U(robj).ik_hint.bone_length * x_scale);
                    VECAdd(&sp1C, &sp10, &sp28);
                    jobj->mtx[0][3] = sp28.x;
                    jobj->mtx[1][3] = sp28.y;
                    jobj->mtx[2][3] = sp28.z;
                }
            }
            break;
        default:
            if (jobj->robj != NULL && jobj != NULL && jobj->robj != NULL) {
                HSD_RObjUpdateAll(jobj->robj, jobj, HSD_JOBJ_METHOD(jobj)->update);
                if (HSD_JObjMtxIsDirty(jobj)) {
                    HSD_JOBJ_METHOD(jobj)->make_mtx(jobj);
                    jobj->flags &= ~JOBJ_MTX_DIRTY;
                }
            }
            break;
        }
        jobj->flags &= ~JOBJ_MTX_DIRTY;
    }
}

void HSD_JObjSetMtxDirtySub(HSD_JObj* jobj)
{
    jobj->flags |= 0x40;
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObj* child = jobj->child;
        while (child != NULL) {
            if (!(child->flags & JOBJ_MTX_INDEP_PARENT)) {
                if (!HSD_JObjMtxIsDirty(child)) {
                    HSD_JObjSetMtxDirtySub(child);
                }
            }
            child = child->next;
        }
    }
}

void HSD_JObjSetDPtclCallback(DPCtlCallback cb) { dptcl_callback = cb; }

void HSD_JObjSetPtclTargetCallback(void (*cb)(HSD_JObj*,int)) { ptcltgt_callback = cb; }

static int JObjInit(HSD_Class* o)
{
    int status = HSD_OBJECT_PARENT_INFO(&hsdJObj)->init(o);
    if (status >= 0) {
        HSD_JObj* jobj = (HSD_JObj*) o;
        status = 0;
        jobj->flags = JOBJ_MTX_DIRTY;
        jobj->scale.x = 1.0F;
        jobj->scale.y = 1.0F;
        jobj->scale.z = 1.0F;
    }
    return status;
}

static void JObjReleaseChild(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if ((child = jobj->child) != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            HSD_JObjUnref(child);
        } else {
            child->parent = NULL;
            HSD_JObjRemoveAll(jobj->child);
        }
        jobj->child = NULL;
    }
    if (jobj->parent != NULL) {
        HSD_JObjReparent(jobj, NULL);
    }
    if (union_type_dobj(jobj)) {
        if (jobj->u.dobj != NULL) {
            HSD_DObjRemoveAll(jobj->u.dobj);
            jobj->u.dobj = NULL;
        }
    }
    if (jobj->robj != NULL) {
        HSD_RObjRemoveAll(jobj->robj);
        jobj->robj = NULL;
    }
    if (jobj->aobj != NULL) {
        HSD_AObjRemove(jobj->aobj);
        jobj->aobj = NULL;
    }
}

static void JObjRelease(HSD_Class* o)
{
    HSD_JObj* jobj = (HSD_JObj*) o;
    HSD_JOBJ_METHOD(jobj)->release_child(jobj);

    if (HSD_IDGetDataFromTable(NULL, jobj->id, NULL) == jobj) {
        HSD_IDKey id = jobj->id;
        HSD_IDRemoveByIDFromTable(NULL, id);
    }
    if (jobj->scl != NULL) {
        HSD_VecFree(jobj->scl);
    }
    if (jobj->envelopemtx != NULL) {
        HSD_MtxFree(jobj->envelopemtx);
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->release(o);
}

static void JObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdJObj)) {
        ufc_callbacks = NULL;
        current_jobj = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdJObj)->amnesia(info);
}

static void JObjInfoInit(void) {
    hsdInitClassInfo((HSD_ClassInfo*)&hsdJObj,&hsdObj,"sysdolphin_base_library","hsd_jobj",sizeof(HSD_JObjInfo),sizeof(HSD_JObj));
    hsdJObj.parent.init = JObjInit;
    hsdJObj.parent.release = JObjRelease;
    hsdJObj.parent.amnesia = JObjAmnesia;
    hsdJObj.make_mtx = HSD_JObjMakeMatrix;
    hsdJObj.make_pmtx = HSD_JObjMakePositionMtx;
    hsdJObj.disp = HSD_JObjDispSub;
    hsdJObj.load = JObjLoad;
    hsdJObj.release_child = JObjReleaseChild;
    hsdJObj.update = JObjUpdateFunc;
}
