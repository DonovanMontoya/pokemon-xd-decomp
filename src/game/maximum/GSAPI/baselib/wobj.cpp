/* World-position animation, spline following, and constraint ownership. */
#include "game/maximum/GSAPI/baselib/wobj.h"
#include "game/maximum/GSAPI/baselib/jobj.h"
#include "game/maximum/GSAPI/baselib/spline.h"
#define HSD_ASSERT(line, condition) do { if (!(condition)) __assert("wobj.c", line, #condition); } while (0)
#ifdef __cplusplus
extern "C" {
#endif
void* __memcpy(void*, const void*, unsigned long);
void PSMTXMultVec(HSD_Mtx, HSD_Vec3*, HSD_Vec3*);
void HSD_WObjRemoveAnim(HSD_WObj* wobj);
void HSD_WObjReqAnim(HSD_WObj* wobj, float frame);
void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim);
static void WObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
void HSD_WObjInterpretAnim(HSD_WObj* wobj);
static int WObjLoad(HSD_WObj* wobj, HSD_WObjDesc* desc);
void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc);
HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc);
void HSD_WObjSetPosition(HSD_WObj* wobj, HSD_Vec3* pos);
static inline void HSD_WObjSetPositionX(HSD_WObj* wobj, float val);
static inline void HSD_WObjSetPositionY(HSD_WObj* wobj, float val);
static inline void HSD_WObjSetPositionZ(HSD_WObj* wobj, float val);
void HSD_WObjGetPosition(HSD_WObj* wobj, HSD_Vec3* vec);
HSD_WObj* HSD_WObjAlloc(void);
static void WObjRelease(HSD_Class* o);
static void WObjAmnesia(HSD_ClassInfo* info);
static void WObjInfoInit(void);
static void WObjInfoInit(void);

HSD_WObjInfo hsdWObj = { WObjInfoInit };

static HSD_ClassInfo* default_class = 0;

static inline void HSD_WObjSetPositionX(HSD_WObj* wobj, float val)
{
    HSD_JObj* jp;

    if (wobj != 0) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != 0 && wobj->aobj->hsd_obj != 0) {
                jp = (HSD_JObj*) wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*) wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.x = val;
        wobj->flags |= 0x2;
    }
}

static inline void HSD_WObjSetPositionY(HSD_WObj* wobj, float val)
{
    HSD_JObj* jp;

    if (wobj != 0) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != 0 && wobj->aobj->hsd_obj != 0) {
                jp = (HSD_JObj*) wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*) wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.y = val;
        wobj->flags |= 0x2;
    }
}

static inline void HSD_WObjSetPositionZ(HSD_WObj* wobj, float val)
{
    HSD_JObj* jp;

    if (wobj != 0) {
        if ((wobj->flags & 1) != 0) {
            if (wobj->aobj != 0 && wobj->aobj->hsd_obj != 0) {
                jp = (HSD_JObj*) wobj->aobj->hsd_obj;
                HSD_JObjSetupMatrix((HSD_JObj*) wobj->aobj->hsd_obj);
                PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
            }
            wobj->flags &= 0xFFFFFFFE;
        }
        wobj->pos.z = val;
        wobj->flags |= 0x2;
    }
}

void HSD_WObjRemoveAnim(HSD_WObj* wobj)
{
    if (wobj != 0) {
        HSD_AObjRemove(wobj->aobj);
        wobj->aobj = 0;
        HSD_RObjRemoveAnimAll(wobj->robj);
    }
}

void HSD_WObjReqAnim(HSD_WObj* wobj, float frame)
{
    if (wobj != 0) {
        HSD_AObjReqAnim(wobj->aobj, frame);
        HSD_RObjReqAnimAll(wobj->robj, frame);
    }
}

void HSD_WObjAddAnim(HSD_WObj* wobj, HSD_WObjAnim* anim)
{
    if (wobj != 0 && anim != 0) {
        if (wobj->aobj != 0) {
            HSD_AObjRemove(wobj->aobj);
        }
        wobj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
        HSD_RObjAddAnimAll(wobj->robj, anim->robjanim);
    }
}

static void WObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_WObj* wobj;
    HSD_Vec3 p;
    HSD_JObj* jp;

    wobj = (HSD_WObj*)obj;
    if (wobj != 0) {
        switch (type) {
        case 4: {
            if (val->fv < 0.0f) {
                val->fv = 0.0;
            }
            if (1.0f < val->fv) {
                val->fv = 1.0;
            }

            HSD_ASSERT(152, wobj->aobj);
            jp = (HSD_JObj*) wobj->aobj->hsd_obj;
            HSD_ASSERT(154, jp);
            HSD_ASSERT(155, jp->u.spline);

            splArcLengthPoint(&p, (HSD_Spline*)jp->u.spline, val->fv);
            HSD_WObjSetPosition(wobj, &p);
            wobj->flags |= 1;
        } break;

        case 5:
            HSD_WObjSetPositionX(wobj, val->fv);
            break;

        case 6:
            HSD_WObjSetPositionY(wobj, val->fv);
            break;

        case 7:
            HSD_WObjSetPositionZ(wobj, val->fv);
            break;
        }
    }
}

void HSD_WObjInterpretAnim(HSD_WObj* wobj)
{
    if (wobj != 0) {
        HSD_AObjInterpretAnim(wobj->aobj, wobj, HSD_WOBJ_METHOD(wobj)->update);
        HSD_RObjAnimAll(wobj->robj);
    }
}

static int WObjLoad(HSD_WObj* wobj, HSD_WObjDesc* desc)
{
    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != 0) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
    return 0;
}

void HSD_WObjInit(HSD_WObj* wobj, HSD_WObjDesc* desc)
{
    if (wobj == 0 || desc == 0) {
        return;
    }

    HSD_WObjSetPosition(wobj, &desc->pos);
    if (wobj->robj != 0) {
        HSD_RObjRemoveAll(wobj->robj);
    }
    wobj->robj = HSD_RObjLoadDesc(desc->robjdesc);
    HSD_RObjResolveRefsAll(wobj->robj, desc->robjdesc);
}

HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc* desc)
{
    if (desc != 0) {
        HSD_WObj* wobj;
        HSD_ClassInfo* info;
        if (desc->class_name == 0 ||
            !(info = hsdSearchClassInfo(desc->class_name)))
        {
            wobj = HSD_WObjAlloc();
        } else {
            wobj = (HSD_WObj*)hsdNew(info);
            HSD_ASSERT(260, wobj);
        }
        HSD_WOBJ_METHOD(wobj)->load(wobj, desc);
        return wobj;
    }
    return 0;
}

void HSD_WObjSetPosition(HSD_WObj* wobj, HSD_Vec3* pos)
{
    if (wobj == 0 || pos == 0) {
        return;
    }

    __memcpy(&wobj->pos, pos, sizeof(HSD_Vec3));
    wobj->flags |= 0x2;
    wobj->flags &= 0xFFFFFFFE;
}

void HSD_WObjGetPosition(HSD_WObj* wobj, HSD_Vec3* vec)
{
    HSD_JObj* jp;

    if (wobj == 0 || vec == 0) {
        return;
    }
    if ((wobj->flags & 1) != 0) {
        if (wobj->aobj != 0 && wobj->aobj->hsd_obj != 0) {
            jp = (HSD_JObj*) wobj->aobj->hsd_obj;
            HSD_JObjSetupMatrix((HSD_JObj*) wobj->aobj->hsd_obj);
            PSMTXMultVec(jp->mtx, &wobj->pos, &wobj->pos);
        }
        wobj->flags &= 0xFFFFFFFE;
    }
    __memcpy(vec, &wobj->pos, sizeof(HSD_Vec3));
}

HSD_WObj* HSD_WObjAlloc(void)
{
    HSD_WObj* wobj =
        (HSD_WObj*)hsdNew(default_class ? default_class : &hsdWObj.parent);
    HSD_ASSERT(599, wobj);
    return wobj;
}

static void WObjRelease(HSD_Class* o)
{
    HSD_WObj* wobj = (HSD_WObj*) o;
    HSD_RObjRemoveAll(wobj->robj);
    HSD_AObjRemove(wobj->aobj);
    HSD_OBJECT_PARENT_INFO(&hsdWObj)->release(o);
}

static void WObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = 0;
    }
    HSD_OBJECT_PARENT_INFO(&hsdWObj)->amnesia(info);
}

static void WObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdWObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "had_wobj",
                     sizeof(HSD_WObjInfo), sizeof(HSD_WObj));
    HSD_CLASS_INFO(&hsdWObj)->release = WObjRelease;
    HSD_CLASS_INFO(&hsdWObj)->amnesia = WObjAmnesia;
    HSD_WOBJ_INFO(&hsdWObj)->load = WObjLoad;
    HSD_WOBJ_INFO(&hsdWObj)->update = WObjUpdateFunc;
}
#ifdef __cplusplus
}
#endif
