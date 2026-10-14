/* Compile with deferred inlining; MW emits retained definitions in reverse order. */
#include "game/maximum/GSAPI/baselib/aobj.h"
#include "libc/stdarg.h"
#define HSD_ASSERT(line, condition) do { int check = (int)(condition); if (!check) __assert("aobj.c", line, #condition); } while (0)
#ifdef __cplusplus
extern "C" {
#endif
void __assert(const char*, int, const char*);
void HSD_Panic(const char*, int, const char*);
void* memset(void*, int, unsigned long);
void* GSmemGetSysdolAllocator(unsigned int);
int GSmemGetFreePool(void*);
void* GSmemAllocPool(void*);
unsigned char GSmemIsRegistrationPool(void*, void*);
void GSmemFreePool(void*, void*);
double fmod(double, double);
void* HSD_IDGetDataFromTable(void*, unsigned int, int*);
HSD_JObj* HSD_JObjLoadJoint(HSD_Joint*);
void HSD_JObjUnref(HSD_JObj*);
static void JObjForeachAnim(HSD_JObj* obj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg);
static void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg);
static void LObjForeachAnim(HSD_LObj* lobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg);
static void CObjForeachAnim(HSD_CObj* cobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg);
static inline void hsdRefInc(HSD_Obj* obj) {
    if (obj) {
        obj->ref_count++;
        if (obj->ref_count == 0xffff)
            __assert("object.h", 93, "HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF");
    }
}
static HSD_ObjAllocData alloc_data;

static int nb_deadanim;
static int nb_activeanim;
static HSD_SList* endcallback_list;

static inline void HSD_AObjSetRewindFrame(HSD_AObj* aobj, float frame)
{
    if (!aobj) {
        return;
    }
    aobj->rewind_frame = frame;
}

static inline void HSD_AObjSetEndFrame(HSD_AObj* aobj, float frame)
{
    if (!aobj) {
        return;
    }
    aobj->end_frame = frame;
}

static inline HSD_AObj* HSD_AObjAlloc(void)
{
    HSD_AObj* new_obj;
    void* allocator = GSmemGetSysdolAllocator(sizeof(HSD_AObj));
    if (allocator && GSmemGetFreePool(allocator)) {
        new_obj = (HSD_AObj*) GSmemAllocPool(allocator);
        if (!new_obj) __assert("aobj.c", 0x1F6, "new");
        return new_obj;
    }
    new_obj = (HSD_AObj*) HSD_ObjAlloc(&alloc_data);
    if (!new_obj) __assert("aobj.c", 0x1FD, "new");

    memset(new_obj, 0, sizeof(HSD_AObj));
    new_obj->flags = AOBJ_NO_ANIM;
    new_obj->framerate = 1.0F;
    return new_obj;
}

static inline void HSD_AObjFree(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    {
        void* allocator = GSmemGetSysdolAllocator(sizeof(HSD_AObj));
        if (allocator && GSmemIsRegistrationPool(allocator, aobj)) {
            GSmemFreePool(allocator, aobj);
        } else {
            HSD_ObjFree(&alloc_data, aobj);
        }
    }
}

static inline void HSD_AObjSetFObj(HSD_AObj* aobj, HSD_FObj* fobj)
{
    if (!aobj) {
        return;
    }

    if (aobj->fobj) {
        HSD_FObjRemoveAll(aobj->fobj);
    }
    aobj->fobj = fobj;
}

static inline void HSD_AObjStopAnim(HSD_AObj* aobj, void* obj, HSD_ObjUpdateFunc func)
{
    if (!aobj) {
        return;
    }

    HSD_FObjStopAnimAll(aobj->fobj, obj, func, aobj->framerate);
    aobj->flags |= AOBJ_NO_ANIM;
}

static inline float getLoopedFrame(HSD_AObj* aobj)
{
    float y = aobj->end_frame - aobj->rewind_frame;
    float x = aobj->curr_frame - aobj->rewind_frame;
    return fmod(x, y) + aobj->rewind_frame;
}

static inline void callbackForeachFunc(HSD_AObj* aobj, void* obj, HSD_Type type,
                                void* func, AObj_Arg_Type arg_type,
                                callbackArg* arg)
{
    switch (arg_type) {
    case AOBJ_ARG_A:
        (*(void (*)(HSD_AObj*)) func)(aobj);
        return;
    case AOBJ_ARG_AF:
        (*(void (*)(HSD_AObj*, float)) func)(aobj, arg->f);
        return;
    case AOBJ_ARG_AV:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, arg->v);
        return;
    case AOBJ_ARG_AU:
        (*(void (*)(HSD_AObj*, unsigned int)) func)(aobj, arg->d);
        return;
    case AOBJ_ARG_AO:
        (*(void (*)(HSD_AObj*, void*)) func)(aobj, obj);
        return;
    case AOBJ_ARG_AOT:
        (*(void (*)(HSD_AObj*, void*, HSD_Type)) func)(aobj, obj, type);
        return;
    case AOBJ_ARG_AOF:
        (*(void (*)(HSD_AObj*, void*, float)) func)(aobj, obj, arg->f);
        return;
    case AOBJ_ARG_AOV:
        (*(void (*)(HSD_AObj*, void*, void*)) func)(aobj, obj, arg->v);
        return;
    case AOBJ_ARG_AOU:
        (*(void (*)(HSD_AObj*, void*, unsigned int)) func)(aobj, obj, arg->d);
        return;
    case AOBJ_ARG_AOTF:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, float)) func)(aobj, obj, type,
                                                            arg->f);
        return;
    case AOBJ_ARG_AOTV:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, void*)) func)(aobj, obj, type,
                                                              arg->v);
        return;
    case AOBJ_ARG_AOTU:
        (*(void (*)(HSD_AObj*, void*, HSD_Type, unsigned int)) func)(aobj, obj, type,
                                                            arg->d);
        return;
    }
}

static inline void FogForeachAnim(HSD_Fog* fog, HSD_TypeMask mask, Event func,
                           AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mask & FOG_MASK && fog != 0 && fog->aobj != 0) {
        callbackForeachFunc(fog->aobj, fog, FOG_TYPE, func, arg_type, arg);
    }
}

static inline void TObjForeachAnim(HSD_TObj* tobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; tobj != 0; tobj = tobj->next) {
        if (mask & TOBJ_MASK && tobj->aobj != 0) {
            callbackForeachFunc(tobj->aobj, tobj, TOBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

static inline void RObjForeachAnim(HSD_RObj* robj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; robj != 0; robj = robj->next) {
        if (mask & ROBJ_MASK && robj->aobj != 0) {
            callbackForeachFunc(robj->aobj, robj, ROBJ_TYPE, func, arg_type,
                                arg);
        }
    }
}

static inline void WObjForeachAnim(HSD_WObj* wobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (wobj == 0) {
        return;
    }

    if (mask & WOBJ_MASK && wobj->aobj != 0) {
        callbackForeachFunc(wobj->aobj, wobj, WOBJ_TYPE, func, arg_type, arg);
    }
    RObjForeachAnim(wobj->robj, mask, func, arg_type, arg);
}

static inline void PObjForeachAnim(HSD_PObj* pobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; pobj != 0; pobj = pobj->next) {
        if (mask & POBJ_MASK && pobj->aobj != 0) {
            callbackForeachFunc(pobj->aobj, pobj, POBJ_TYPE, func, arg_type, arg);
        }
    }
}

static inline void MObjForeachAnim(HSD_MObj* mobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (mobj == 0) {
        return;
    }

    if (mask & MOBJ_MASK && mobj->aobj != 0) {
        callbackForeachFunc(mobj->aobj, mobj, MOBJ_TYPE, func, arg_type, arg);
    }
    TObjForeachAnim(mobj->tobj, mask, func, arg_type, arg);
}

static inline void HSD_AObjSetCurrentFrame(HSD_AObj* aobj, float frame)
{
    if (!aobj) {
        return;
    }

    if (!(aobj->flags & AOBJ_NO_ANIM) && aobj) {
        aobj->curr_frame = frame;
        aobj->flags = (aobj->flags & 0xBFFFFFFF) | AOBJ_FIRST_PLAY;
        HSD_FObjReqAnimAll(aobj->fobj, frame);
    }
}

void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&alloc_data, sizeof(HSD_AObj), 4);
}

HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &alloc_data;
}

unsigned int HSD_AObjGetFlags(HSD_AObj* aobj)
{
    return aobj ? aobj->flags : 0;
}

void HSD_AObjSetFlags(HSD_AObj* aobj, unsigned int flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE | (1 << 16));
        aobj->flags |= flags;
    }
}

void HSD_AObjClearFlags(HSD_AObj* aobj, unsigned int flags)
{
    if (aobj) {
        flags &= (AOBJ_LOOP | AOBJ_NO_UPDATE | (1 << 16));
        aobj->flags &= ~flags;
    }
}

void HSD_AObjInitEndCallBack(void)
{
    nb_deadanim = 0;
    nb_activeanim = 0;
}

void HSD_AObjInvokeCallBacks(void)
{
    HSD_SList* list;

    if (nb_deadanim != 0 && nb_activeanim == 0) {
        list = endcallback_list;
        while (list) {
            void (*func)(void) = (void (*)(void))list->data;
            (*func)();
            list = list->next;
        }
    }
}

void HSD_AObjReqAnim(HSD_AObj* aobj, float frame)
{
    unsigned int flags;

    if (!aobj) {
        return;
    }

    aobj->curr_frame = frame;

    flags = aobj->flags & ~AOBJ_NO_ANIM;
    aobj->flags = flags | AOBJ_FIRST_PLAY;

    HSD_FObjReqAnimAll(aobj->fobj, frame);
}

void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func)
{
    float rate = 0;

    if (!aobj || aobj->flags & AOBJ_NO_ANIM) {
        return;
    }

    if (aobj->flags & AOBJ_FIRST_PLAY) {
        aobj->flags &= 0xF7FFFFFF;
        rate = 0.0F;
    } else {
        rate = aobj->framerate;
        aobj->curr_frame += aobj->framerate;
    }

    if ((aobj->flags & AOBJ_LOOP) && aobj->end_frame <= aobj->curr_frame) {
        if (aobj->rewind_frame < aobj->end_frame) {
            HSD_FObjStopAnimAll(aobj->fobj, obj, update_func, rate);
            aobj->curr_frame = getLoopedFrame(aobj);
            HSD_FObjReqAnimAll(aobj->fobj, aobj->curr_frame);
        } else {
            aobj->curr_frame = aobj->end_frame;
        }
        rate = 0.0F;
        aobj->flags |= AOBJ_REWINDED;
    } else {
        aobj->flags &= 0xFBFFFFFF;
    }

    if (aobj->flags & AOBJ_NO_UPDATE) {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, 0, rate);
    } else {
        HSD_FObjInterpretAnimAll(aobj->fobj, obj, update_func, rate);
    }

    {
        unsigned int no_anim = aobj->flags & AOBJ_NO_ANIM;
        if (no_anim) {
            nb_deadanim += 1;
        }
        if (!no_anim) {
            nb_activeanim += 1;
        }
    }
}

HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc)
{
    HSD_FObjDesc* fobjdesc;
    HSD_AObj* aobj;

    unsigned char _[4];

    HSD_FObj* fobj;
    HSD_IDKey id;
    HSD_Obj* phi_r30;

    if (aobjdesc != 0) {
        aobj = HSD_AObjAlloc();
        HSD_AObjSetFlags(aobj, aobjdesc->flags);
        HSD_AObjSetRewindFrame(aobj, 0.0F);
        HSD_AObjSetEndFrame(aobj, aobjdesc->end_frame);
        fobjdesc = aobjdesc->fobjdesc;
        fobj = HSD_FObjLoadDesc(fobjdesc);
        HSD_AObjSetFObj(aobj, fobj);
        id = (HSD_IDKey) aobjdesc->obj_id;
        if (id != 0U) {
            if ((phi_r30 = (HSD_Obj*)HSD_IDGetDataFromTable(0, id, 0)) != 0) {
                hsdRefInc(phi_r30);
            } else {
                phi_r30 = (HSD_Obj*) HSD_JObjLoadJoint(
                    (HSD_Joint*) aobjdesc->obj_id);
            }
            if (aobj != 0) {
                if (aobj->hsd_obj != 0) {
                    HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
                }
                aobj->hsd_obj = phi_r30;
            }
        }
        return aobj;
    }
    return 0;
}

void HSD_AObjRemove(HSD_AObj* aobj)
{
    if (!aobj) {
        return;
    }

    if (aobj) {
        if (aobj->fobj) {
            HSD_FObjRemoveAll(aobj->fobj);
        }
        aobj->fobj = 0;
    }

    if (aobj) {
        if (aobj->hsd_obj != 0) {
            HSD_JObjUnref((HSD_JObj*) aobj->hsd_obj);
        }
        aobj->hsd_obj = 0;
    }
    HSD_AObjFree(aobj);
}

static void CObjForeachAnim(HSD_CObj* cobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    if (cobj == 0) {
        return;
    }

    if (mask & COBJ_MASK && cobj->aobj != 0) {
        callbackForeachFunc(cobj->aobj, cobj, COBJ_TYPE, func, arg_type, arg);
    }
    WObjForeachAnim(cobj->eyepos, mask, func, arg_type, arg);
    WObjForeachAnim(cobj->interest, mask, func, arg_type, arg);
}

static void LObjForeachAnim(HSD_LObj* lobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; lobj != 0; lobj = lobj->next) {
        if (mask & LOBJ_MASK && lobj->aobj != 0) {
            callbackForeachFunc(lobj->aobj, lobj, LOBJ_TYPE, func, arg_type,
                                arg);
        }
        WObjForeachAnim(lobj->position, mask, func, arg_type, arg);
        WObjForeachAnim(lobj->interest, mask, func, arg_type, arg);
    }
}

static void DObjForeachAnim(HSD_DObj* dobj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    for (; dobj != 0; dobj = dobj->next) {
        if (mask & DOBJ_MASK && dobj->aobj != 0) {
            callbackForeachFunc(dobj->aobj, dobj, DOBJ_TYPE, func, arg_type,
                                arg);
        }
        MObjForeachAnim(dobj->mobj, mask, func, arg_type, arg);
        PObjForeachAnim(dobj->pobj, mask, func, arg_type, arg);
    }
}

static void JObjForeachAnim(HSD_JObj* obj, HSD_TypeMask mask, Event func,
                            AObj_Arg_Type arg_type, callbackArg* arg)
{
    HSD_ASSERT(0x2EB, obj);

    if (mask & JOBJ_MASK && obj->aobj != 0) {
        callbackForeachFunc(obj->aobj, obj, JOBJ_TYPE, func, arg_type, arg);
    }
    if (union_type_dobj(obj)) {
        DObjForeachAnim(obj->u.dobj, mask, func, arg_type, arg);
    }
    RObjForeachAnim(obj->robj, mask, func, arg_type, arg);
    if (!(obj->flags & JOBJ_INSTANCE)) {
        for (obj = obj->child; obj != 0; obj = obj->next) {
            JObjForeachAnim((HSD_JObj*)obj, mask, (Event)func, arg_type, arg);
        }
    }
}

void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func,
                     AObj_Arg_Type arg_type, ...)
{
    va_list ap;
    callbackArg arg;

    if (obj == 0) {
        return;
    }

    va_start(ap, arg_type);
    switch (arg_type) {
    case AOBJ_ARG_A:
    case AOBJ_ARG_AO:
    case AOBJ_ARG_AOT:
        break;
    case AOBJ_ARG_AF:
    case AOBJ_ARG_AOF:
    case AOBJ_ARG_AOTF:
        arg.f = va_arg(ap, double);
        break;
    case AOBJ_ARG_AV:
    case AOBJ_ARG_AOV:
    case AOBJ_ARG_AOTV:
        arg.v = va_arg(ap, void*);
        break;
    case AOBJ_ARG_AU:
    case AOBJ_ARG_AOU:
    case AOBJ_ARG_AOTU:
        arg.d = va_arg(ap, unsigned int);
        break;
    default:
        HSD_Panic("aobj.c", 858, "unexpected argument format.\n");
        break;
    }

    switch (type) {
    case JOBJ_TYPE:
        JObjForeachAnim((HSD_JObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case DOBJ_TYPE:
        DObjForeachAnim((HSD_DObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case MOBJ_TYPE:
        MObjForeachAnim((HSD_MObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case POBJ_TYPE:
        PObjForeachAnim((HSD_PObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case TOBJ_TYPE:
        TObjForeachAnim((HSD_TObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case LOBJ_TYPE:
        LObjForeachAnim((HSD_LObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case COBJ_TYPE:
        CObjForeachAnim((HSD_CObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case ROBJ_TYPE:
        RObjForeachAnim((HSD_RObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case WOBJ_TYPE:
        WObjForeachAnim((HSD_WObj*)obj, mask, (Event)func, arg_type, &arg);
        break;
    case FOG_TYPE:
        FogForeachAnim((HSD_Fog*)obj, mask, (Event)func, arg_type, &arg);
        break;
    default:
        HSD_Panic("aobj.c", 894, "unexpected type of object.\n");
        break;
    }
    va_end(ap);
}

void HSD_AObjSetRate(HSD_AObj* aobj, float rate)
{
    if (!aobj) {
        return;
    }
    aobj->framerate = rate;
}

void _HSD_AObjForgetMemory(void* low, void* high)
{
    endcallback_list = 0;
}
#ifdef __cplusplus
}
#endif
