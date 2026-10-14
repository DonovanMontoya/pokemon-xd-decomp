/* XD constraint and expression objects. Deferred inlining preserves text order. */
#include "game/maximum/GSAPI/baselib/robj.h"
#include "game/maximum/GSAPI/baselib/jobj.h"
#include "game/maximum/GSAPI/baselib/bytecode.h"
#include "game/maximum/GSAPI/baselib/math_support.h"
#include "game/maximum/GSAPI/baselib/quatlib.h"
#include "game/maximum/GSAPI/baselib/class.h"
#define HSD_ASSERT_STRING(line, condition, label) do { if (!(condition)) __assert("robj.c", line, label); } while (0)
#define HSD_ASSERT(line, condition) HSD_ASSERT_STRING(line, condition, #condition)
#ifdef __cplusplus
extern "C" {
#endif
void* memset(void*, int, unsigned long);
void* __memcpy(void*, const void*, unsigned long);
void HSD_Panic(const char*, int, const char*);
void OSReport(const char*, ...);
void* HSD_Alloc(unsigned int);
int _HSD_MemCheckOwn(void*);
void* HSD_IDGetDataFromTable(void*, unsigned int, int*);
unsigned int HSD_GetNbBits(unsigned int);
void PSVECCrossProduct(HSD_Vec3*, HSD_Vec3*, HSD_Vec3*);
float PSVECDotProduct(HSD_Vec3*, HSD_Vec3*);
void PSVECScale(HSD_Vec3*, HSD_Vec3*, float);
void PSVECSubtract(HSD_Vec3*, HSD_Vec3*, HSD_Vec3*);
float PSVECMag(HSD_Vec3*);
void PSMTXCopy(HSD_Mtx, HSD_Mtx);
static inline float fabsf_bitwise(float v) { *(unsigned int*)&v &= ~0x80000000; return v; }
static inline void HSD_MtxColVec(HSD_Mtx m, int i, HSD_Vec3* v) { v->x = m[0][i]; v->y = m[1][i]; v->z = m[2][i]; }
static inline float HSD_MtxColMag(HSD_Mtx m, int i) { return hsdSqrt(m[0][i]*m[0][i]+m[1][i]*m[1][i]+m[2][i]*m[2][i]); }
static inline int RObjHasFlags(HSD_RObj* r) { if ((r->flags & ROBJ_TYPE_MASK)==0) return 1; return 0; }
static inline int RObjHasFlags2(HSD_RObj* r) { if ((r->flags & 0x80000000)!=0) return 1; return 0; }
static inline int RObjHasLimitReftype(HSD_RObj* r) { if ((r->flags & ROBJ_TYPE_MASK)==REFTYPE_LIMIT) return 1; return 0; }
void HSD_RObjInitAllocData(void);
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);
static inline void HSD_RObjSetFlags(HSD_RObj* robj, unsigned int flags);
HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, unsigned int type, unsigned int subtype);
static void RObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
static inline void HSD_RObjAnim(HSD_RObj* robj);
void HSD_RObjAnimAll(HSD_RObj* robj);
static inline void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, unsigned int flags);
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, unsigned int flags);
void HSD_RObjRemoveAnimAll(HSD_RObj* robj);
static inline void HSD_RObjReqAnimByFlags(HSD_RObj* robj, float startframe, unsigned int flags);
void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, float startframe, unsigned int flags);
void HSD_RObjReqAnimAll(HSD_RObj* robj, float startframe);
static inline void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim);
void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim);
static inline unsigned int HSD_RObjGetConstraintType(HSD_RObj* robj);
int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int type, HSD_Vec3* p);
static inline void set_dirup_matrix(HSD_Vec3* dir_ptr, HSD_Vec3* uv_ptr, HSD_Vec3* scale_ptr,
                             void* obj, HSD_ObjUpdateFunc update_func);
static void resolveCnsDirUp(HSD_RObj* robj, void* obj,
                            HSD_ObjUpdateFunc update_func);
static inline HSD_JObj* jobj_parent(HSD_JObj* jobj);
static inline HSD_RObj* inlined_HSD_RObjGetByType(HSD_RObj* robj, unsigned int type,
                                                  unsigned int subtype);
static void resolveCnsOrientation(HSD_RObj* robj, void* obj,
                                  void (*update_func)(void*, int,
                                                      HSD_ObjData*));
static void resolveLimits(HSD_RObj* robj, void* obj,
                          HSD_ObjUpdateFunc update_func);
void HSD_RObjUpdateAll(HSD_RObj* robj, void* obj,
                       HSD_ObjUpdateFunc update_func);
static inline void HSD_RObjResolveRefs(HSD_RObj* robj, HSD_RObjDesc* desc);
void HSD_RObjResolveRefsAll(HSD_RObj* robj, HSD_RObjDesc* desc);
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc* robjdesc);
static inline void HSD_RObjRemove(HSD_RObj* robj);
void HSD_RObjRemoveAll(HSD_RObj* robj);
HSD_RObj* HSD_RObjAlloc(void);
static inline void HSD_RObjFree(HSD_RObj* robj);
static void expEvaluate(HSD_Exp* exp, unsigned int type, void* obj,
                        HSD_ObjUpdateFunc update_func);
static float dummy_func(void* unused);
static inline HSD_Rvalue* HSD_RvalueAlloc(void);
static inline void HSD_RvalueRemove(HSD_Rvalue* rvalue);
static inline void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue);
static HSD_Rvalue* loadRvalue(HSD_RvalueList* list);
static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc);
static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc);
void HSD_RvalueResolveRefs(HSD_Rvalue* rvalue, HSD_RvalueList* list);
static inline void HSD_RvalueResolveRefsAll(HSD_Rvalue* rvalue, HSD_RvalueList* list);
void _HSD_RObjForgetMemory(void* low, void* high);
float* HSD_SetExpArgBuffer(float* ptr, unsigned int nitems);
static void dumpObjAlloc(HSD_ObjAllocData* data, const char* label);
static HSD_ObjAllocData robj_alloc_data;
static HSD_ObjAllocData rv_alloc_data;

static unsigned int arg_buf_size;
static float* arg_buf;

static int HSD_RObj_80406E74[3] = { 0x32, 0x33, 0x34 };

static void expEvaluate(HSD_Exp* exp, unsigned int type, void* obj,
                        HSD_ObjUpdateFunc update_func);

static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc);
static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc);

static inline void HSD_RObjSetFlags(HSD_RObj* robj, unsigned int flags)
{
    if (robj != 0) {
        robj->flags |= flags;
    }
}

static inline void HSD_RObjAnim(HSD_RObj* robj)
{
    if (robj == 0) {
        return;
    }

    HSD_AObjInterpretAnim(robj->aobj, robj, RObjUpdateFunc);
}

static inline void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, unsigned int flags)
{
    if (robj == 0) {
        return;
    }

    if (robj->aobj != 0 && (flags & 0x80) != 0) {
        HSD_AObjRemove(robj->aobj);
        robj->aobj = 0;
    }
}

static inline void HSD_RObjReqAnimByFlags(HSD_RObj* robj, float startframe, unsigned int flags)
{
    if (robj == 0) {
        return;
    }

    if (robj->aobj != 0 && (flags & 0x80) != 0) {
        HSD_AObjReqAnim(robj->aobj, startframe);
    }
}

static inline void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    if (robj == 0 || anim == 0) {
        return;
    }

    if (robj->aobj != 0) {
        HSD_AObjRemove(robj->aobj);
    }
    robj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
}

static inline unsigned int HSD_RObjGetConstraintType(HSD_RObj* robj)
{
    if (robj == 0) {
        return 0;
    }

    return robj->flags & 0x0FFFFFFF;
}

static inline void set_dirup_matrix(HSD_Vec3* dir_ptr, HSD_Vec3* uv_ptr, HSD_Vec3* scale_ptr,
                             void* obj, HSD_ObjUpdateFunc update_func)
{
    HSD_Vec3 z_vec;
    HSD_Vec3 v;
    float kz;
    float kdir;

    PSVECCrossProduct(dir_ptr, uv_ptr, &z_vec);
    kdir =
        hsdSqrt(1.0F / (1.00000001335e-10f + PSVECDotProduct(dir_ptr, dir_ptr)));
    PSVECScale(dir_ptr, dir_ptr, kdir);
    kz = hsdSqrt(1.0F / (1.00000001335e-10f + PSVECDotProduct(&z_vec, &z_vec)));
    PSVECScale(&z_vec, &z_vec, kz);
    PSVECCrossProduct(&z_vec, dir_ptr, uv_ptr);
    v.x = dir_ptr->x * scale_ptr->x;
    v.y = dir_ptr->y * scale_ptr->x;
    v.z = dir_ptr->z * scale_ptr->x;
    update_func(obj, 50, (HSD_ObjData*) &v);
    v.x = uv_ptr->x * scale_ptr->y;
    v.y = uv_ptr->y * scale_ptr->y;
    v.z = uv_ptr->z * scale_ptr->y;
    update_func(obj, 51, (HSD_ObjData*) &v);
    v.x = z_vec.x * scale_ptr->z;
    v.y = z_vec.y * scale_ptr->z;
    v.z = z_vec.z * scale_ptr->z;
    update_func(obj, 52, (HSD_ObjData*) &v);
    update_func(obj, 55, 0);
}

static inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == 0) {
        return 0;
    }
    return jobj->parent;
}

static inline HSD_RObj* inlined_HSD_RObjGetByType(HSD_RObj* robj, unsigned int type,
                                                  unsigned int subtype)
{
    int has_type;
    HSD_RObj* curr;

    if (robj == 0) {
        return 0;
    }

    for (curr = robj; curr != 0; curr = curr->next) {
        if (curr->flags & 0x80000000) {
            has_type = 1;
        } else {
            has_type = 0;
        }

        if (has_type) {
            if ((curr->flags & ROBJ_TYPE_MASK) == type &&
                (!subtype || subtype == (curr->flags & 0xFFFFFFF)))
            {
                return curr;
            }
        }
    }

    return 0;
}

static inline void HSD_RObjResolveRefs(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    if (robj != 0 && desc != 0) {
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(ROBJ_U(robj).jobj);
            ROBJ_U(robj).jobj = (HSD_JObj*)HSD_IDGetDataFromTable(0, (HSD_IDKey) desc->u.joint, 0);
            HSD_ASSERT_STRING(816, ROBJ_U(robj).jobj, "robj->u.jobj");
            HSD_JObjRefThis(ROBJ_U(robj).jobj);
            break;
        case 0x0:
            HSD_RvalueResolveRefsAll(ROBJ_U(robj).exp.rvalue, desc->u.exp->rvalue);
            break;
        }
    }
}

static inline void HSD_RObjRemove(HSD_RObj* robj)
{


    if (robj != 0) {
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(ROBJ_U(robj).jobj);
            break;
        case 0x0:
            HSD_RvalueRemoveAll(ROBJ_U(robj).exp.rvalue);
            break;
        }
        HSD_AObjRemove(robj->aobj);
        HSD_RObjFree(robj);
    }
}

static inline void HSD_RObjFree(HSD_RObj* robj)
{
    HSD_ObjFree(HSD_RObjGetAllocData(), robj);
}

static inline HSD_Rvalue* HSD_RvalueAlloc(void)
{
    HSD_Rvalue* rvalue = (HSD_Rvalue*)HSD_ObjAlloc(HSD_RvalueObjGetAllocData());
    HSD_ASSERT(1157, rvalue);
    memset(rvalue, 0, sizeof(HSD_Rvalue));
    return rvalue;
}

static inline void HSD_RvalueRemove(HSD_Rvalue* rvalue)
{
    if (rvalue != 0) {
        HSD_JObjUnrefThis(rvalue->jobj);
        HSD_ObjFree(HSD_RvalueObjGetAllocData(), rvalue);
    }
}

static inline void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue)
{
    HSD_Rvalue* next;

    for (; rvalue != 0; rvalue = next) {
        next = rvalue->next;
        HSD_RvalueRemove(rvalue);
    }
}

static inline void HSD_RvalueResolveRefsAll(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (list == 0) {
        return;
    }
    for (; rvalue != 0 && list->joint != 0;
         rvalue = rvalue->next, list++)
    {
        HSD_RvalueResolveRefs(rvalue, list);
    }
}

void HSD_RObjInitAllocData(void)
{
    HSD_ObjAllocInit(&robj_alloc_data, sizeof(HSD_RObj), 4);
    HSD_ObjAllocInit(&rv_alloc_data, sizeof(HSD_Rvalue), 4);
}

HSD_ObjAllocData* HSD_RObjGetAllocData(void)
{
    return &robj_alloc_data;
}

HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void)
{
    return &rv_alloc_data;
}

HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, unsigned int type, unsigned int subtype)
{
    int has_type;
    HSD_RObj* curr;

    if (robj == 0) {
        return 0;
    }

    for (curr = robj; curr != 0; curr = curr->next) {
        if (curr->flags & 0x80000000) {
            has_type = 1;
        } else {
            has_type = 0;
        }

        if (has_type) {
            if ((curr->flags & ROBJ_TYPE_MASK) == type &&
                (!subtype || subtype == (curr->flags & 0xFFFFFFF)))
            {
                return curr;
            }
        }
    }

    return 0;
}

static void RObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_RObj* robj;

    if (obj == 0) {
        return;
    }

    if (type != TYPE_ROBJ) {
        return;
    }

    robj = (HSD_RObj*) obj;
    if (val->fv >= 0.5) {
        robj->flags = robj->flags | 0x80000000;
        return;
    }
    robj->flags = robj->flags & 0x7fffffff;
}

void HSD_RObjAnimAll(HSD_RObj* robj)
{
    HSD_RObj* curr;

    if (robj == 0) {
        return;
    }

    for (curr = robj; curr != 0; curr = curr->next) {
        HSD_RObjAnim(curr);
    }
}

void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, unsigned int flags)
{
    if (robj == 0) {
        return;
    }

    for (; robj != 0; robj = robj->next) {
        HSD_RObjRemoveAnimByFlags(robj, flags);
    }
}

void HSD_RObjRemoveAnimAll(HSD_RObj* robj)
{
    HSD_RObjRemoveAnimAllByFlags(robj, 0x7FF);
}

void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, float startframe, unsigned int flags)
{
    if (robj == 0) {
        return;
    }

    for (; robj != 0; robj = robj->next) {
        HSD_RObjReqAnimByFlags(robj, startframe, flags);
    }
}

void HSD_RObjReqAnimAll(HSD_RObj* robj, float startframe)
{
    HSD_RObjReqAnimAllByFlags(robj, startframe, 0x7FF);
}

void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    HSD_RObj* i;
    HSD_RObjAnimJoint* j;

    if (robj == 0 || anim == 0) {
        return;
    }

    for (i = robj, j = anim; i != 0 && j != 0; i = i->next, j = j->next)
    {
        HSD_RObjAddAnim(i, j);
    }
}

int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int type, HSD_Vec3* p)
{
    HSD_Vec3 v = { 0, 0, 0 };
    HSD_RObj* rp;
    int n = 0;

    if (robj == 0) {
        return 0;
    }
    for (rp = robj; rp != 0; rp = rp->next) {
        if (((rp->flags & ROBJ_TYPE_MASK) == REFTYPE_JOBJ ? 1 : 0) != 0) {
            if (((rp->flags & 0x80000000) ? 1 : 0) != 0 &&
                (unsigned) type == HSD_RObjGetConstraintType(rp))
            {
                HSD_ASSERT_STRING(498, ROBJ_U(rp).jobj, "rp->u.jobj");
                HSD_JObjSetupMatrix(ROBJ_U(rp).jobj);
                n += 1;
                v.x += ROBJ_U(rp).jobj->mtx[0][3];
                v.y += ROBJ_U(rp).jobj->mtx[1][3];
                v.z += ROBJ_U(rp).jobj->mtx[2][3];
            }
        }
    }
    if (n != 0) {
        float f = (float) 1.0 / (float) n;
        p->x = f * v.x;
        p->y = f * v.y;
        p->z = f * v.z;
    }
    return n;
}

static void resolveCnsDirUp(HSD_RObj* robj, void* obj,
                            HSD_ObjUpdateFunc update_func)
{
    HSD_Vec3 this_scale = { 1.0f, 1.0f, 1.0f };
    HSD_Vec3 up = { 0.0f, 1.0f, 0.0f };
    HSD_Vec3 this_pos;
    HSD_Vec3 dir;
    float k;

    if (HSD_RObjGetGlobalPosition(robj, 2, &this_pos) != 0) {
        dir.x = ((HSD_JObj*) obj)->mtx[0][3];
        dir.y = ((HSD_JObj*) obj)->mtx[1][3];
        dir.z = ((HSD_JObj*) obj)->mtx[2][3];
        PSVECSubtract(&this_pos, &dir, &this_pos);
        if (HSD_RObjGetGlobalPosition(robj, 3, &up) != 0) {
            PSVECSubtract(&up, &dir, &up);
        } else {
            k = 1.0f - PSVECDotProduct(&this_pos, &up);
            if (__fabs(k) < 1.00000001335e-10) {
                up.x = 0.0f;
                up.y = 0.0f;
                up.z = 1.0;
            }
        }

        if (((HSD_JObj*) obj)->scl != 0) {
            __memcpy(&this_scale, ((HSD_JObj*)obj)->scl, sizeof(this_scale));
        }
        set_dirup_matrix(&this_pos, &up, &this_scale, obj, update_func);
    }
}

static void resolveCnsOrientation(HSD_RObj* robj, void* obj,
                                  void (*update_func)(void*, int,
                                                      HSD_ObjData*))
{
    HSD_Mtx mtx0;
    float sval;

    HSD_Vec3 v;

    HSD_JObj* jobj;
    int i;

    HSD_ASSERT(0x276, obj);
    jobj = (HSD_JObj*)obj;

    robj = inlined_HSD_RObjGetByType(robj, 0x10000000, 4);
    if (robj == 0) {
        return;
    }
    {
        PSMTXCopy(HSD_JObjGetMtxPtr(ROBJ_U(robj).jobj), mtx0);

        for (i = 0; i < 3; i++) {
            HSD_MtxColVec(mtx0, i, &v);
            sval = PSVECMag(&v);
            if (sval > 1e-10F) {
                sval = 1.0F / sval;
            }
            sval *= HSD_MtxColMag(jobj->mtx, i);
            v.x *= sval;
            v.y *= sval;
            v.z *= sval;
            update_func(obj, HSD_RObj_80406E74[i], (HSD_ObjData*) &v);
        }
    }
    update_func(obj, 0x37, 0);
}

static void resolveLimits(HSD_RObj* robj, void* obj,
                          HSD_ObjUpdateFunc update_func)
{
    HSD_JObj* jobj = (HSD_JObj*) obj;
    HSD_RObj* rp;
    int update_mtx = 0;

    HSD_ASSERT(0x29E, jobj);

    rp = robj;
    while (rp != 0) {
        if (RObjHasLimitReftype(rp)) {
            break;
        }
        rp = rp->next;
    }

    if (rp != 0) {
        for (rp = robj; rp != 0; rp = rp->next) {
            if (RObjHasLimitReftype(rp)) {
                switch (rp->flags & 0xFFFFFFF) {
                default:
                    continue;
                case 1:
                    if (jobj->rotate.x < ROBJ_U(rp).limit) {
                        jobj->rotate.x = ROBJ_U(rp).limit;
                    }
                    break;

                case 2:
                    if (jobj->rotate.x > ROBJ_U(rp).limit) {
                        jobj->rotate.x = ROBJ_U(rp).limit;
                    }
                    break;

                case 3:
                    if (jobj->rotate.y < ROBJ_U(rp).limit) {
                        jobj->rotate.y = ROBJ_U(rp).limit;
                    }
                    break;

                case 4:
                    if (jobj->rotate.y > ROBJ_U(rp).limit) {
                        jobj->rotate.y = ROBJ_U(rp).limit;
                    }
                    break;

                case 5:
                    if (jobj->rotate.z < ROBJ_U(rp).limit) {
                        jobj->rotate.z = ROBJ_U(rp).limit;
                    }
                    break;

                case 6:
                    if (jobj->rotate.z > ROBJ_U(rp).limit) {
                        jobj->rotate.z = ROBJ_U(rp).limit;
                    }
                    break;

                case 7:
                    if (jobj->translate.x < ROBJ_U(rp).limit) {
                        jobj->translate.x = ROBJ_U(rp).limit;
                    }
                    break;

                case 8:
                    if (jobj->translate.x > ROBJ_U(rp).limit) {
                        jobj->translate.x = ROBJ_U(rp).limit;
                    }
                    break;

                case 9:
                    if (jobj->translate.y < ROBJ_U(rp).limit) {
                        jobj->translate.y = ROBJ_U(rp).limit;
                    }
                    break;

                case 10:
                    if (jobj->translate.y > ROBJ_U(rp).limit) {
                        jobj->translate.y = ROBJ_U(rp).limit;
                    }
                    break;

                case 11:
                    if (jobj->translate.z < ROBJ_U(rp).limit) {
                        jobj->translate.z = ROBJ_U(rp).limit;
                    }
                    break;

                case 12:
                    if (jobj->translate.z > ROBJ_U(rp).limit) {
                        jobj->translate.z = ROBJ_U(rp).limit;
                    }
                    break;
                }
                update_mtx = 1;
            }
        }
        if (update_mtx) {
            HSD_JObjMakeMatrix(jobj);
        }
    }
}

void HSD_RObjUpdateAll(HSD_RObj* robj, void* obj,
                       HSD_ObjUpdateFunc update_func)
{
    HSD_RObj* rp;
    HSD_Vec3 vec;

    if (robj != 0) {
        if (HSD_RObjGetGlobalPosition(robj, 1, &vec) != 0) {
            update_func(obj, 0x35, (HSD_ObjData*) &vec);
            update_func(obj, 0x38, 0);
        }
        resolveCnsDirUp(robj, obj, update_func);
        resolveCnsOrientation(robj, obj, update_func);
        resolveLimits(robj, obj, update_func);

        for (rp = robj; rp != 0; rp = rp->next) {
            if (RObjHasFlags(rp) && RObjHasFlags2(rp)) {
                expEvaluate(&ROBJ_U(rp).exp, rp->flags & 0xFFFFFFF, obj,
                            update_func);
            }
        }
    }
}

void HSD_RObjResolveRefsAll(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    for (; robj != 0 && desc != 0; robj = robj->next, desc = desc->next)
    {
        HSD_RObjResolveRefs(robj, desc);
    }
}

static void dumpObjAlloc(HSD_ObjAllocData* data, const char* label) {}

HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc* robjdesc)
{
    HSD_RObj* robj;

    if (robjdesc != 0) {
        robj = HSD_RObjAlloc();
        robj->next = HSD_RObjLoadDesc(robjdesc->next);
        robj->flags = robjdesc->flags;
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            break;
        case REFTYPE_LIMIT: {
            switch (robj->flags & 0xFFFFFFF) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                ROBJ_U(robj).limit = 0.017453292f * robjdesc->u.limit;
                break;
            default:
                ROBJ_U(robj).limit = robjdesc->u.limit;
                break;
            }
        } break;
        case REFTYPE_EXP:
            expLoadDesc(&ROBJ_U(robj).exp, robjdesc->u.exp);
            break;
        case REFTYPE_BYTECODE:
            bcexpLoadDesc(&ROBJ_U(robj).exp, robjdesc->u.bcexp);
            robj->flags &= ~ROBJ_TYPE_MASK;
            break;
        case REFTYPE_IKHINT:
            ROBJ_U(robj).ik_hint.bone_length = robjdesc->u.ik_hint->bone_length;
            ROBJ_U(robj).ik_hint.rotate_x = robjdesc->u.ik_hint->rotate_x;
            break;
        default:
            HSD_Panic("robj.c", 0x37D, "unexpected type of robj.\n");
            break;
        }
        return robj;
    }
    return 0;
}

void HSD_RObjRemoveAll(HSD_RObj* robj)
{
    HSD_RObj* next;

    for (; robj != 0; robj = next) {
        next = robj->next;
        HSD_RObjRemove(robj);
    }
}

HSD_RObj* HSD_RObjAlloc(void)
{
    HSD_RObj* new_object = (HSD_RObj*)HSD_ObjAlloc(&robj_alloc_data);
    dumpObjAlloc(&robj_alloc_data, "robj: alloc");
    HSD_ASSERT_STRING(965, new_object, "new");
    memset(new_object, 0, sizeof(*new_object));
    return new_object;
}

float* HSD_SetExpArgBuffer(float* ptr, unsigned int nitems) {
    float* old = arg_buf;
    int valid = (ptr && nitems) || !ptr;
    if (!valid) __assert("robj.c", 1021, "(ptr && nitems) || !ptr");
    arg_buf = ptr;
    arg_buf_size = nitems;
    return old;
}

static void expEvaluate(HSD_Exp* exp, unsigned int type, void* obj,
                        HSD_ObjUpdateFunc update_func)
{
    HSD_Rvalue* rvalue;
    float* cur_arg;
    int cur_bit;
    HSD_JObj* jobj;
    HSD_Vec3 scale;
    HSD_Quaternion sp2C;
    float temp_f31;
    HSD_ObjData sp1C;

    if (exp->nb_args == -1) {
        unsigned int nb_args = 0;
        HSD_Rvalue* rvalue;
        for (rvalue = exp->rvalue; rvalue != 0; rvalue = rvalue->next) {
            nb_args += HSD_GetNbBits(rvalue->flags);
        }
        exp->nb_args = nb_args;
    }
    if (arg_buf == 0) {
        if (arg_buf_size == 0) {
            arg_buf_size = 100;
        }
        arg_buf = (float*)HSD_Alloc(arg_buf_size * sizeof(float));
    }
    if (arg_buf_size < exp->nb_args) {
        OSReport(
            "Number of argment of expression exceeds the argument buffer\n"
            "size. (requested num of arg %d, allocated %d)\n",
            exp->nb_args, arg_buf_size);
        HSD_Panic("robj.c", 0x41B, "");
    }
    cur_arg = arg_buf;
    temp_f31 = 57.29578F;
    for (rvalue = exp->rvalue; rvalue != 0; rvalue = rvalue->next) {
        jobj = rvalue->jobj;
        HSD_ASSERT(0x424, jobj);
        HSD_JObjSetupMatrix(rvalue->jobj);
        for (cur_bit = 1; cur_bit && cur_bit <= rvalue->flags; cur_bit <<= 1) {
            switch (rvalue->flags & cur_bit) {
            case 0x1:
                *cur_arg++ = temp_f31 * jobj->rotate.x;
                break;
            case 0x2:
                *cur_arg++ = temp_f31 * jobj->rotate.y;
                break;
            case 0x4:
                *cur_arg++ = temp_f31 * jobj->rotate.z;
                break;
            case 0x8:
                break;
            case 0x10:
                *cur_arg++ = jobj->translate.x;
                break;
            case 0x20:
                *cur_arg++ = jobj->translate.y;
                break;
            case 0x40:
                *cur_arg++ = jobj->translate.z;
                break;
            case 0x80:
                *cur_arg++ = jobj->scale.x;
                break;
            case 0x100:
                *cur_arg++ = jobj->scale.y;
                break;
            case 0x200:
                *cur_arg++ = jobj->scale.z;
                break;
            case 0x400:
            case 0x800:
                break;
            case 0x10000:
                HSD_MtxGetRotation(jobj->mtx, (HSD_Vec3*)&sp2C);
                *cur_arg++ = temp_f31 * sp2C.x;
                break;
            case 0x20000:
                HSD_MtxGetRotation(jobj->mtx, (HSD_Vec3*)&sp2C);
                *cur_arg++ = temp_f31 * sp2C.y;
                break;
            case 0x40000:
                HSD_MtxGetRotation(jobj->mtx, (HSD_Vec3*)&sp2C);
                *cur_arg++ = temp_f31 * sp2C.z;
                break;
            case 0x100000:
                *cur_arg++ = jobj->mtx[0][3];
                break;
            case 0x200000:
                *cur_arg++ = jobj->mtx[1][3];
                break;
            case 0x400000:
                *cur_arg++ = jobj->mtx[2][3];
                break;
            case 0x800000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.x;
                break;
            case 0x1000000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.y;
                break;
            case 0x2000000:
                HSD_MtxGetScale(jobj->mtx, &scale);
                *cur_arg++ = scale.z;
                break;
            }
        }
    }
    if (exp->is_bytecode) {
        sp1C.fv = HSD_ByteCodeEval(exp->expr.bytecode, arg_buf, exp->nb_args);
    } else {
        sp1C.fv = exp->expr.func(arg_buf);
    }
    if (type == 1 || type == 2 || type == 3) {
        sp1C.fv = sp1C.fv * 0.017453292F;
    }
    update_func(obj, type, (HSD_ObjData*)&sp1C);
}

static float dummy_func(void* unused)
{
    return 0.0f;
}

static HSD_Rvalue* loadRvalue(HSD_RvalueList* list)
{
    HSD_Rvalue* rp;
    struct { HSD_Rvalue* next; } rv;

    rv.next = 0;
    rp = (HSD_Rvalue*) &rv;
    if (list == 0) {
        return 0;
    } else {
        for (; list->joint != 0; list++) {
            rp->next = HSD_RvalueAlloc();
            rp->next->flags = list->flags;
            rp = rp->next;
        }
    }
    return (HSD_Rvalue*) rv.next;
}

static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != 0) {
        if (desc->func != 0) {
            exp->expr.func = desc->func;
        } else {
            exp->expr.func = dummy_func;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
    }
}

static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != 0) {
        if (desc->bytecode != 0) {
            exp->expr.bytecode = desc->bytecode;
        } else {
            exp->expr.bytecode = 0;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
        exp->is_bytecode = 1;
    }
}

void _HSD_RObjForgetMemory(void* low, void* high) {
    if (_HSD_MemCheckOwn(arg_buf)) { arg_buf = 0; arg_buf_size = 0; }
}
#ifdef __cplusplus
}
#endif

/* Linker-stripped in the DOL; their pooled strings still lead .rodata. */
void HSD_RvalueResolveRefs(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (rvalue != 0 && list != 0) {
        HSD_JObjUnrefThis(rvalue->jobj);
        rvalue->jobj = (HSD_JObj*)HSD_IDGetDataFromTable(0, (HSD_IDKey) list->joint, 0);
        HSD_ASSERT(1266, rvalue->jobj);
        HSD_JObjRefThis(rvalue->jobj);
    }
}

extern HSD_ClassInfo hsdJObj;

void HSD_RObjSetConstraintObj(HSD_RObj* robj, void* o)
{
    if (robj != 0) {
        if (ROBJ_U(robj).jobj != 0) {
            HSD_JObjUnrefThis(ROBJ_U(robj).jobj);
            ROBJ_U(robj).jobj = 0;
        }
        if (hsdIsDescendantOf(HSD_CLASS_METHOD(o), &hsdJObj)) {
            ROBJ_U(robj).jobj = (HSD_JObj*)o;
            HSD_JObjRefThis((HSD_JObj*)o);
        } else {
            OSReport("constraint only support jobj target.\n");
            HSD_ASSERT(1309, 0);
        }
    }
}
