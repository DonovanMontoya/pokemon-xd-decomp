/* Compile with deferred inlining to preserve the original function layout. */
#include "game/maximum/GSAPI/baselib/dobj.h"
#ifdef __cplusplus
extern "C" {
#endif
void __assert(const char*, int, const char*);
void HSD_Panic(const char*, int, const char*);
void OSReport(const char*, ...);
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj*, unsigned int);
void HSD_MObjRemoveAnimByFlags(HSD_MObj*, unsigned int);
void HSD_PObjAddAnimAll(HSD_PObj*, HSD_ShapeAnim*);
void HSD_MObjAddAnim(HSD_MObj*, HSD_MatAnim*);
void HSD_PObjReqAnimAllByFlags(HSD_PObj*, float, unsigned int);
void HSD_MObjReqAnimByFlags(HSD_MObj*, float, unsigned int);
void HSD_PObjAnimAll(HSD_PObj*);
void HSD_MObjAnim(HSD_MObj*);
HSD_MObj* HSD_MObjLoadDesc(void*);
HSD_PObj* HSD_PObjLoadDesc(void*);
void HSD_MObjRemove(HSD_MObj*);
void HSD_PObjRemoveAll(HSD_PObj*);
void HSD_PObjResolveRefsAll(HSD_PObj*, void*);
void HSD_MObjSetCurrent(HSD_MObj*);
void HSD_PObjCountVertices(HSD_PObj*, unsigned int*, unsigned int*);
/* XD extends the material table before unset, at offset 0x50. */
struct HSD_MObjMethods { HSD_ClassInfo parent; void (*setup)(HSD_MObj*, unsigned int); void* other[4]; void (*unset)(HSD_MObj*, unsigned int); };
struct HSD_PObjMethods { HSD_ClassInfo parent; void (*disp)(HSD_PObj*, HSD_Mtx, HSD_Mtx, unsigned int); };
#define HSD_MOBJ_METHOD(o) ((HSD_MObjMethods*)(o)->class_info)
#define HSD_POBJ_METHOD(o) ((HSD_PObjMethods*)(o)->class_info)
static void DObjInfoInit(void);
static void DObjAmnesia(HSD_ClassInfo* info);
static void DObjRelease(HSD_Class* o);
void HSD_DObjDisp(HSD_DObj* dobj, HSD_Mtx vmtx, HSD_Mtx pmtx, unsigned int rendermode);
void HSD_DObjCountVertices(HSD_DObj* dobj, unsigned int* vertices, unsigned int* triangles);
void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjRemoveAll(HSD_DObj* dobj);
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc);
static int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc);
void HSD_DObjAnimAll(HSD_DObj* dobj);
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float startframe, unsigned int flags);
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                        HSD_ShapeAnimDObj* shapeanimdobj);
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, unsigned int flags);
void HSD_DObjSetCurrent(HSD_DObj* dobj);
static void DObjInfoInit(void);
HSD_DObjInfo hsdDObj = { DObjInfoInit };

static HSD_ClassInfo* default_class = 0;

static HSD_DObj* current_dobj = 0;























































static inline unsigned int HSD_DObjGetFlags(HSD_DObj* dobj)
{
    if (dobj != 0) {
        return dobj->flags;
    }
    return 0;
}

static inline void HSD_DObjSetFlags(HSD_DObj* dobj, unsigned int flags)
{
    if (dobj != 0) {
        dobj->flags |= flags;
    }
}

static inline void HSD_DObjClearFlags(HSD_DObj* dobj, unsigned int flags)
{
    if (dobj != 0) {
        dobj->flags &= ~flags;
    }
}

static inline void HSD_DObjModifyFlags(HSD_DObj* dobj, unsigned int flags, unsigned int mask)
{
    if (dobj == 0) {
        return;
    }

    dobj->flags = (dobj->flags & ~mask) | (flags & mask);
}

static inline void HSD_DObjRemoveAnimByFlags(HSD_DObj* dobj, unsigned int flags)
{
    if (dobj == 0) {
        return;
    }

    if ((flags & 2) != 0) {
        HSD_AObjRemove(dobj->aobj);
        dobj->aobj = 0;
    }
    HSD_PObjRemoveAnimAllByFlags(dobj->pobj, flags);
    HSD_MObjRemoveAnimByFlags(dobj->mobj, flags);
}

static inline void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim,
                     HSD_ShapeAnimDObj* sh_anim)
{

    if (dobj == 0) {
        return;
    }

    HSD_PObjAddAnimAll(dobj->pobj, sh_anim != 0 ? sh_anim->shapeanim : 0);
    HSD_MObjAddAnim(dobj->mobj, mat_anim);
}

static inline void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, float startframe, unsigned int flags)
{
    if (dobj == 0) {
        return;
    }

    HSD_PObjReqAnimAllByFlags(dobj->pobj, startframe, flags);
    HSD_MObjReqAnimByFlags(dobj->mobj, startframe, flags);
}

static inline void HSD_DObjReqAnimAll(HSD_DObj* dobj, float startframe)
{
    HSD_DObj* dp;

    if (dobj == 0) {
        return;
    }

    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe, 0x7FF);
    }
}

static inline void HSD_DObjAnim(HSD_DObj* dobj)
{
    if (dobj == 0) {
        return;
    }

    HSD_AObjInterpretAnim(dobj->aobj, dobj, HSD_DOBJ_METHOD(dobj)->update);
    HSD_PObjAnimAll(dobj->pobj);
    HSD_MObjAnim(dobj->mobj);
}

static inline void HSD_DObjRemove(HSD_DObj* dobj)
{
    hsdDelete(dobj);
}

static inline HSD_DObj* HSD_DObjAlloc(void)
{
    HSD_DObj* dobj = (HSD_DObj*)hsdNew(default_class ? default_class : &hsdDObj.parent);
    if (dobj == 0) {
        __assert("dobj.c", 532, "dobj");
    }
    return dobj;
}

static inline void HSD_DObjResolveRefs(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    if (dobj == 0 || desc == 0) {
        return;
    }
    HSD_PObjResolveRefsAll(dobj->pobj, desc->pobjdesc);
}

void HSD_DObjSetCurrent(HSD_DObj* dobj)
{
    current_dobj = dobj;
}

void HSD_DObjRemoveAnimAllByFlags(HSD_DObj* dobj, unsigned int flags)
{
    HSD_DObj* dp;

    if (dobj == 0) {
        return;
    }

    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjRemoveAnimByFlags(dp, flags);
    }
}

void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                        HSD_ShapeAnimDObj* shapeanimdobj)
{
    HSD_DObj* dp;
    HSD_MatAnim* ma;
    HSD_ShapeAnimDObj* sd;

    if (dobj == 0) {
        return;
    }

    for (dp = dobj, ma = matanim, sd = shapeanimdobj; dp != 0;
         dp = dp->next, ma = next_p(ma), sd = next_p(sd))
    {
        HSD_DObjAddAnim(dp, ma, sd);
    }
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float startframe, unsigned int flags)
{
    HSD_DObj* dp;

    if (dobj == 0) {
        return;
    }

    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, startframe, flags);
    }
}

void HSD_DObjAnimAll(HSD_DObj* dobj)
{
    HSD_DObj* dp;

    if (dobj == 0) {
        return;
    }

    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjAnim(dp);
    }
}

static int DObjLoad(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    dobj->next = HSD_DObjLoadDesc(desc->next);
    dobj->mobj = HSD_MObjLoadDesc(desc->mobjdesc);
    dobj->pobj = HSD_PObjLoadDesc(desc->pobjdesc);

    if (dobj->mobj != 0) {
        switch (dobj->mobj->rendermode & 0x60000000) {
        case 0:
            HSD_DObjModifyFlags(dobj, 2, 0xE);
            break;
        case 0x40000000:
            HSD_DObjModifyFlags(dobj, 8, 0xE);
            break;
        case 0x60000000:
            HSD_DObjModifyFlags(dobj, 4, 0xE);
            break;
        default:
            OSReport("mobj has unexpected blending flags (0x%x).",
                     dobj->mobj->rendermode);
            HSD_Panic("dobj.c", 319, "");
        }
    }
    return 0;
}

HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc* desc)
{
    HSD_DObj* dobj;
    HSD_ClassInfo* info;

    if (desc == 0) {
        return 0;
    }

    if (desc->class_name == 0 ||
        (info = hsdSearchClassInfo(desc->class_name)) == 0)
    {
        dobj = HSD_DObjAlloc();
    } else {
        dobj = HSD_DOBJ(hsdNew(info));
        if (dobj == 0) {
            __assert("dobj.c", 385, "dobj");
        }
    }
    HSD_DOBJ_METHOD(dobj)->load(dobj, desc);

    return dobj;
}

void HSD_DObjRemoveAll(HSD_DObj* dobj)
{
    HSD_DObj* next;

    for (; dobj != 0; dobj = next) {
        next = dobj->next;
        HSD_DObjRemove(dobj);
    }
}

void HSD_DObjResolveRefsAll(HSD_DObj* dobj, HSD_DObjDesc* desc)
{
    for (; dobj != 0 && desc != 0; dobj = dobj->next, desc = desc->next)
    {
        HSD_DObjResolveRefs(dobj, desc);
    }
}

void HSD_DObjCountVertices(HSD_DObj* dobj, unsigned int* vertices, unsigned int* triangles) {
    unsigned int n_vertices, n_triangles;
    unsigned int total_vertices = 0, total_triangles = 0;
    for (; dobj != 0; dobj = dobj->next) {
        HSD_PObjCountVertices(dobj->pobj, &n_vertices, &n_triangles);
        total_vertices += n_vertices;
        total_triangles += n_triangles;
    }
    if (vertices) *vertices = total_vertices;
    if (triangles) *triangles = total_triangles;
}

void HSD_DObjDisp(HSD_DObj* dobj, HSD_Mtx vmtx, HSD_Mtx pmtx, unsigned int rendermode)
{
    HSD_PObj* p;

    HSD_MObjSetCurrent(dobj->mobj);
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->setup(dobj->mobj, rendermode);
    }
    for (p = dobj->pobj; p != 0; p = p->next) {
        HSD_POBJ_METHOD(p)->disp(p, vmtx, pmtx, rendermode);
    }
    if ((rendermode & 0x4000000) == 0) {
        HSD_MOBJ_METHOD(dobj->mobj)->unset(dobj->mobj, rendermode);
    }
    HSD_MObjSetCurrent(0);
}

static void DObjRelease(HSD_Class* o)
{
    HSD_DObj* dobj = HSD_DOBJ(o);

    HSD_MObjRemove(dobj->mobj);
    HSD_PObjRemoveAll(dobj->pobj);
    HSD_AObjRemove(dobj->aobj);

    HSD_PARENT_INFO(&hsdDObj)->release(o);
}

static void DObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = 0;
    }
    HSD_PARENT_INFO(&hsdDObj)->amnesia(info);
}

static void DObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdDObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_dobj",
                     sizeof(HSD_DObjInfo), sizeof(HSD_DObj));

    HSD_CLASS_INFO(&hsdDObj)->release = DObjRelease;
    HSD_CLASS_INFO(&hsdDObj)->amnesia = DObjAmnesia;
    HSD_DOBJ_INFO(&hsdDObj)->disp = HSD_DObjDisp;
    HSD_DOBJ_INFO(&hsdDObj)->load = DObjLoad;
}
#ifdef __cplusplus
}
#endif
