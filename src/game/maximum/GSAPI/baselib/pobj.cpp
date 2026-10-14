/* XD polygon loading, shape blending, display decoding, and matrix setup. */
#include "game/maximum/GSAPI/baselib/pobj.h"
#include "game/maximum/GSAPI/baselib/displayfunc.h"
#include "game/maximum/GSAPI/baselib/state.h"
#include "game/maximum/GSAPI/baselib/util.h"
#include "game/maximum/GSAPI/baselib/tobj.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <libc/string.h>
#define HSD_ASSERT(line,expr) ((expr)?(void)0:__assert("pobj.c",line,#expr))
#define POBJ_ANIM 8
#define POBJ_SKIN 0
#define POBJ_ENVELOPE 0x2000
#define POBJ_CULLFRONT 0x4000
#define POBJ_CULLBACK 0x8000
#define SHAPESET_ADDITIVE 2
#define SHAPESET_AVERAGE 1
#define HSD_A_S_W0 2
#define HSD_DEFAULT_MAX_SHAPE_VERTICES 2000
#define HSD_DEFAULT_MAX_SHAPE_NORMALS 2000
#define MAX(a,b) ((a)>(b)?(a):(b))
#define HSD_MTX_RIGID 1
#define HSD_MTX_ENVELOPE 2
#define JOBJ_LIGHTING 0x80
#define TEX_COORD_REFLECTION 1
#define TEX_COORD_HILIGHT 2
#define FLT_EPSILON 1.192092896e-7F
typedef enum { SETUP_NONE=0, SETUP_NORMAL=1, SETUP_REFLECTION=2, SETUP_HIGHLIGHT=4, SETUP_NORMAL_PROJECTION=6, SETUP_JOINT0=1, SETUP_JOINT1=2 } PObjSetupFlag;
void* hsdAllocMemPiece(unsigned int);
void hsdFreeMemPiece(void*,unsigned int);
void* HSD_Alloc(unsigned int);
void HSD_Free(void*);
int _HSD_MemCheckOwn(void*);
HSD_SList* HSD_SListAlloc(void);
HSD_SList* HSD_SListRemove(HSD_SList*);
void* HSD_IDGetDataFromTable(void*,unsigned int,void*);
static inline void* HSD_IDGetData(unsigned int key,void* data) { return HSD_IDGetDataFromTable(0,key,data); }
void HSD_Panic(const char*,int,const char*);
HSD_JObj* HSD_JObjGetCurrent(void);
HSD_TObj* _HSD_TObjGetCurrentByType(HSD_TObj*,unsigned int);
static inline void HSD_MtxInverseTranspose(Mtx src,Mtx dst) { if (!PSMTXInvXpose(src,dst)) PSMTXCopy(src,dst); }
int HSD_Index2TexMtx(unsigned int);
static inline unsigned int HSD_PObjGetFlags(HSD_PObj* pobj);
static inline void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, unsigned int flags);
void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, unsigned int flags);
static inline void HSD_PObjAddAnim(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim);
void HSD_PObjAddAnimAll(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim);
static inline void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, float startframe, unsigned int flags);
void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, float startframe, unsigned int flags);
static inline void ShapeSetSetAnimResult(HSD_ShapeSet* shape_set, unsigned int type,
                                  HSD_ObjData* val);
static void PObjUpdateFunc(void* obj, int type, HSD_ObjData* val);
static inline void HSD_PObjAnim(HSD_PObj* pobj);
void HSD_PObjAnimAll(HSD_PObj* pobj);
static inline HSD_Envelope* HSD_EnvelopeAlloc(void);
static inline void HSD_EnvelopeFree(HSD_Envelope* env);
static inline void HSD_EnvelopeListFree(HSD_SList* list);
static inline HSD_SList* loadEnvelopeDesc(HSD_EnvelopeDesc** edesc_p);
static inline void HSD_ShapeSetFree(HSD_ShapeSet* shape_set);
static inline void HSD_ShapeSetRemove(HSD_ShapeSet* shape_set);
static inline HSD_ShapeSet* loadShapeSetDesc(HSD_ShapeSetDesc* sdesc);
static int PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc);
HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc* pobjdesc);
static inline void HSD_PObjRemove(HSD_PObj* pobj);
void HSD_PObjRemoveAll(HSD_PObj* pobj);
static inline HSD_PObjInfo* HSD_PObjGetDefaultClass(void);
static inline void HSD_PObjSetDefaultClass(HSD_PObjInfo* info);
static inline HSD_PObj* HSD_PObjAlloc(void);
static inline void HSD_PObjFree(HSD_PObj* pobj);
static inline void resolveEnvelope(HSD_SList* list, HSD_EnvelopeDesc** edesc_p);
static inline void HSD_PObjResolveRefs(HSD_PObj* pobj, HSD_PObjDesc* pdesc);
void HSD_PObjResolveRefsAll(HSD_PObj* pobj, HSD_PObjDesc* pdesc);
void HSD_ClearVtxDesc(void);
static inline void setupArrayDesc(HSD_VtxDescList* desc_list);
static inline void setupVtxDesc(HSD_PObj* pobj);
static inline void setupShapeAnimArrayDesc(HSD_VtxDescList* desc_list);
static inline void setupShapeAnimVtxDesc(HSD_PObj* pobj);
static inline void decode_u8_xyz(void* src_base, float dst[3], int scale);
static inline void decode_s8_xyz(void* src_base, float dst[3], int scale);
static inline void decode_u16_xyz(void* src_base, float dst[3], int scale);
static inline void decode_s16_xyz(void* src_base, float dst[3], int scale);
static void get_shape_vertex_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, float dst[3]);
static void get_shape_normal_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, float dst[3]);
static void get_shape_nbt_xyz(HSD_ShapeSet* shape_set, int shape_id,
                              int arrayidx, float* dst);
static void interpretShapeAnimDisplayList(HSD_PObj* pobj, float (*vertex)[3],
                                          float (*normal)[3]);
static void drawShapeAnim(HSD_PObj* pobj);
void HSD_PObjClearMtxMark(void* obj, unsigned int mark);
void HSD_PObjSetMtxMark(int idx, void* obj, unsigned int mark);
void HSD_PObjGetMtxMark(int idx, void** obj, unsigned int* mark);
static inline PObjSetupFlag GetSetupFlags(HSD_JObj* jobj, unsigned int rendermode);
static inline void SetupRigidModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                               unsigned int rendermode);
static void SetupSharedVtxModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                   unsigned int rendermode);
static void SetupEnvelopeModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                  unsigned int rendermode);
static void PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, unsigned int rendermode);
static inline void PObjDispSimplePrimitive(HSD_PObj* pobj, unsigned int rendermode);
static inline void PObjDispShapeAnim(HSD_PObj* pobj, unsigned int rendermode);
void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, unsigned int rendermode);
static void PObjRelease(HSD_Class* o);
static void PObjAmnesia(HSD_ClassInfo* info);
static void PObjInfoInit(void);

HSD_PObjInfo hsdPObj = { PObjInfoInit };

static HSD_PObjInfo* default_class = NULL;

static float (*vertex_buffer)[3] = NULL;
static float (*normal_buffer)[3] = NULL;
static unsigned int vertex_buffer_size = 0;
static unsigned int normal_buffer_size = 0;

static HSD_VtxDescList* prev_vtxdesclist_array = NULL;
static HSD_VtxDescList* prev_vtxdesc = NULL;

static struct mtx_mark_t {
    void* obj;
    unsigned int mark;
} mtx_mark[2];

static inline unsigned int HSD_PObjGetFlags(HSD_PObj* pobj)
{
    if (pobj != NULL) {
        return pobj->flags;
    }
    return 0;
}

static inline void HSD_PObjRemoveAnimByFlags(HSD_PObj* pobj, unsigned int flags)
{
    if (pobj == NULL) {
        return;
    }

    if (flags & POBJ_ANIM) {
        HSD_AObjRemove(pobj->aobj);
        pobj->aobj = NULL;
    }
}

void HSD_PObjRemoveAnimAllByFlags(HSD_PObj* pobj, unsigned int flags)
{
    HSD_PObj* pp;

    if (pobj == NULL) {
        return;
    }

    for (pp = pobj; pp != NULL; pp = pp->next) {
        HSD_PObjRemoveAnimByFlags(pp, flags);
    }
}

static inline void HSD_PObjAddAnim(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim)
{
    if (pobj == NULL) {
        return;
    }

    if (pobj->aobj) { HSD_AObjRemove(pobj->aobj); }
    pobj->aobj = HSD_AObjLoadDesc(shapeanim->aobjdesc);
}

void HSD_PObjAddAnimAll(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim)
{
    HSD_PObj* po;
    HSD_ShapeAnim* sa;

    if (pobj == NULL || shapeanim == NULL) {
        return;
    }

    for (po = pobj, sa = shapeanim; po != NULL; po = po->next, sa = next_p(sa))
    {
        HSD_PObjAddAnim(po, sa);
    }
}

static inline void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, float startframe, unsigned int flags)
{
    if (pobj == NULL) {
        return;
    }

    if (flags & POBJ_ANIM) {
        HSD_AObjReqAnim(pobj->aobj, startframe);
    }
}

void HSD_PObjReqAnimAllByFlags(HSD_PObj* pobj, float startframe, unsigned int flags)
{
    HSD_PObj* pp;

    if (pobj == NULL) {
        return;
    }

    for (pp = pobj; pp; pp = pp->next) {
        HSD_PObjReqAnimByFlags(pp, startframe, flags);
    }
}

static inline void ShapeSetSetAnimResult(HSD_ShapeSet* shape_set, unsigned int type,
                                  HSD_ObjData* val)
{
    if (shape_set->flags & SHAPESET_ADDITIVE) {
        shape_set->blend.bp[type - HSD_A_S_W0] = val->fv;
    } else {
        shape_set->blend.bl = val->fv;
    }
}

static void PObjUpdateFunc(void* obj, int type, HSD_ObjData* val)
{
    HSD_PObj* pobj = HSD_POBJ(obj);
    if (pobj == NULL) {
        return;
    }

    if (pobj_type(pobj) == POBJ_SHAPEANIM) {
        ShapeSetSetAnimResult(pobj->u.shape_set, type, val);
    }
}

static inline void HSD_PObjAnim(HSD_PObj* pobj)
{
    if (pobj != NULL) {
        HSD_AObjInterpretAnim(pobj->aobj, pobj, HSD_POBJ_METHOD(pobj)->update);
    }
}

void HSD_PObjAnimAll(HSD_PObj* pobj)
{
    HSD_PObj* pp;

    if (pobj != NULL) {
        for (pp = pobj; pp != NULL; pp = pp->next) {
            HSD_PObjAnim(pp);
        }
    }
}

static inline HSD_Envelope* HSD_EnvelopeAlloc(void)
{
    HSD_Envelope* envelope = hsdAllocMemPiece(sizeof(HSD_Envelope));
    if (!(envelope)) __assert("pobj.c", 424, "envelope");
    memset(envelope, 0, sizeof(HSD_Envelope));
    return envelope;
}

static inline void HSD_EnvelopeFree(HSD_Envelope* env)
{
    if (env != NULL) {
        hsdFreeMemPiece(env, sizeof(HSD_Envelope));
    }
}

static inline void HSD_EnvelopeListFree(HSD_SList* list)
{
    while (list) {
        HSD_Envelope* env = list->data;
        while (env) {
            HSD_Envelope* next = env->next;
            HSD_JObjUnrefThis(env->jobj);
            HSD_EnvelopeFree(env);
            env = next;
        }
        list = HSD_SListRemove(list);
    }
}

static inline HSD_SList* loadEnvelopeDesc(HSD_EnvelopeDesc** edesc_p)
{
    HSD_SList* list = NULL;
    HSD_SList** list_p = &list;

    if (edesc_p == NULL) {
        return NULL;
    }

    while (*edesc_p) {
        HSD_Envelope* envelope = NULL;
        HSD_Envelope** env_p = &envelope;
        HSD_EnvelopeDesc* edesc = *edesc_p;

        while (edesc->joint) {
            *env_p = HSD_EnvelopeAlloc();
            (*env_p)->weight = edesc->weight;
            env_p = &(*env_p)->next;
            edesc++;
        }

        (*list_p) = HSD_SListAlloc();
        (*list_p)->data = envelope;
        list_p = &(*list_p)->next;
        edesc_p++;
    }
    return list;
}

static inline void HSD_ShapeSetFree(HSD_ShapeSet* shape_set)
{
    if (!shape_set) {
        return;
    }
    hsdFreeMemPiece(shape_set, sizeof(HSD_ShapeSetDesc) + sizeof(float));
}

static inline void HSD_ShapeSetRemove(HSD_ShapeSet* shape_set)
{
    if (shape_set == NULL) {
        return;
    }

    if (shape_set->flags & SHAPESET_ADDITIVE) {
        HSD_Free(shape_set->blend.bp);
    }

    HSD_ShapeSetFree(shape_set);
}

static inline HSD_ShapeSet* loadShapeSetDesc(HSD_ShapeSetDesc* sdesc)
{
    int i;

    HSD_ShapeSet* shape_set = hsdAllocMemPiece(sizeof(HSD_ShapeSetDesc) + sizeof(float));
    if (!(shape_set)) __assert("pobj.c", 481, "shape_set");
    memset(shape_set, 0, sizeof(HSD_ShapeSetDesc) + sizeof(float));
    shape_set->flags = sdesc->flags;
    shape_set->nb_shape = sdesc->nb_shape;
    shape_set->nb_vertex_index = sdesc->nb_vertex_index;
    shape_set->vertex_desc = sdesc->vertex_desc;
    shape_set->vertex_idx_list = sdesc->vertex_idx_list;
    shape_set->nb_normal_index = sdesc->nb_normal_index;
    shape_set->normal_desc = sdesc->normal_desc;
    shape_set->normal_idx_list = sdesc->normal_idx_list;
    if (shape_set->flags & SHAPESET_ADDITIVE) {
        shape_set->blend.bp = HSD_Alloc(shape_set->nb_shape * sizeof(float));
        for (i = 0; i < shape_set->nb_shape; i++) {
            shape_set->blend.bp[i] = 0.0f;
        }
    } else {
        shape_set->blend.bl = 0.0f;
    }
    return shape_set;
}

static int PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc)
{
    pobj->next = HSD_PObjLoadDesc(desc->next);
    pobj->verts = desc->verts;
    pobj->flags = desc->flags;
    pobj->n_display = desc->n_display;
    pobj->display = desc->display;
    switch (pobj_type(pobj)) {
    case POBJ_SHAPEANIM:
        pobj->u.shape_set = loadShapeSetDesc(desc->u.shape_set);
        break;

    case POBJ_ENVELOPE:
        pobj->u.envelope_list = loadEnvelopeDesc(desc->u.envelope_p);
        break;

    case POBJ_SKIN:
        break;

    default:
        HSD_Panic("pobj.c", 553, "pobj: unexected type.\n");
    }


    return 0;
}

HSD_PObj* HSD_PObjLoadDesc(HSD_PObjDesc* pobjdesc)
{
    if (pobjdesc != NULL) {
        HSD_PObj* pobj;
        HSD_ClassInfo* info;

        if (!pobjdesc->class_name ||
            !(info = hsdSearchClassInfo(pobjdesc->class_name)))
        {
            pobj = HSD_PObjAlloc();
        } else {
            pobj = hsdNew(info);
            if (!(pobj)) __assert("pobj.c", 578, "pobj");
        }
        HSD_POBJ_METHOD(pobj)->load(pobj, pobjdesc);
        return pobj;
    } else {
        return NULL;
    }
}

static inline void HSD_PObjRemove(HSD_PObj* pobj)
{
    hsdDelete(pobj);
}

void HSD_PObjRemoveAll(HSD_PObj* pobj)
{
    HSD_PObj* next;

    while (pobj != NULL) {
        next = pobj->next;
        HSD_PObjRemove(pobj);
        pobj = next;
    }
}

static inline HSD_PObjInfo* HSD_PObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdPObj;
}

static inline void HSD_PObjSetDefaultClass(HSD_PObjInfo* info)
{
    if (info != NULL) {
        if (!(hsdIsDescendantOf(info, &hsdPObj))) __assert("pobj.c", 644, "hsdIsDescendantOf(info, &hsdPObj)");
    }
    default_class = info;
}

static inline HSD_PObj* HSD_PObjAlloc(void)
{
    HSD_PObj* pobj = hsdNew(&HSD_PObjGetDefaultClass()->parent);
    if (!(pobj)) __assert("pobj.c", 676, "pobj");
    return pobj;
}

static inline void HSD_PObjFree(HSD_PObj* pobj)
{
    if (pobj) {
        HSD_CLASS_METHOD(pobj)->destroy((HSD_Class*) pobj);
    }
}

static inline void resolveEnvelope(HSD_SList* list, HSD_EnvelopeDesc** edesc_p)
{
    if (list == NULL || edesc_p == NULL) {
        return;
    }

    for (; list && *edesc_p; list = list->next, edesc_p++) {
        HSD_Envelope* env = list->data;
        HSD_EnvelopeDesc* edesc = *edesc_p;

        while (env && edesc->joint) {
            HSD_JObjUnrefThis(env->jobj);
            env->jobj = HSD_IDGetData((HSD_IDKey) edesc->joint, NULL);
            if (!(env->jobj)) __assert("pobj.c", 709, "env->jobj");
            HSD_JObjRefThis(env->jobj);
            env = env->next;
            edesc++;
        }
    }
}

static inline void HSD_PObjResolveRefs(HSD_PObj* pobj, HSD_PObjDesc* pdesc)
{
    if (!pobj || !pdesc) {
        return;
    }

    switch (pobj_type(pobj)) {
    case POBJ_ENVELOPE:
        resolveEnvelope(pobj->u.envelope_list, pdesc->u.envelope_p);
        break;

    case POBJ_SKIN:
        HSD_JObjUnrefThis(pobj->u.jobj);
        pobj->u.jobj = NULL;
        if (pdesc->u.joint != NULL) {
            pobj->u.jobj = HSD_IDGetData((HSD_IDKey) pdesc->u.joint, NULL);
            if (!(pobj->u.jobj)) __assert("pobj.c", 736, "pobj->u.jobj");
            HSD_JObjRefThis(pobj->u.jobj);
        }
        break;

    default:
        break;
    }
}

void HSD_PObjResolveRefsAll(HSD_PObj* pobj, HSD_PObjDesc* pdesc)
{
    for (; pobj != NULL && pdesc != NULL;
         pobj = pobj->next, pdesc = pdesc->next)
    {
        HSD_PObjResolveRefs(pobj, pdesc);
    }
}

void HSD_ClearVtxDesc(void)
{
    GXClearVtxDesc();
    prev_vtxdesclist_array = 0;
    prev_vtxdesc = 0;
}

static inline void setupArrayDesc(HSD_VtxDescList* desc_list)
{
    HSD_VtxDescList* desc;

    if (prev_vtxdesclist_array != desc_list) {
        for (desc = desc_list; desc->attr != GX_VA_NULL; desc++) {
            if (desc->attr_type != GX_DIRECT) {
                GXSetArray(desc->attr, desc->vertex, desc->stride);
            }
        }
        prev_vtxdesclist_array = desc_list;
    }
}

static inline void setupVtxDesc(HSD_PObj* pobj)
{
    HSD_VtxDescList* desc;

    if (prev_vtxdesc != pobj->verts) {
        GXClearVtxDesc();
        for (desc = pobj->verts; desc->attr != GX_VA_NULL; desc++) {
            GXSetVtxDesc(desc->attr, desc->attr_type);
            switch (desc->attr) {
            case GX_VA_PNMTXIDX:
            case GX_VA_TEX0MTXIDX:
            case GX_VA_TEX1MTXIDX:
            case GX_VA_TEX2MTXIDX:
            case GX_VA_TEX3MTXIDX:
            case GX_VA_TEX4MTXIDX:
            case GX_VA_TEX5MTXIDX:
            case GX_VA_TEX6MTXIDX:
            case GX_VA_TEX7MTXIDX:
                break;
            default:
                GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt,
                                desc->comp_type, desc->frac);
            }
        }
        prev_vtxdesc = pobj->verts;
    }
}

static inline void setupShapeAnimArrayDesc(HSD_VtxDescList* desc_list)
{
    HSD_VtxDescList* desc;

    for (desc = desc_list; desc->attr != GX_VA_NULL; desc++) {
        if (desc->attr_type != GX_DIRECT) {
            switch (desc->attr) {
            case GX_VA_POS:
            case GX_VA_NRM:
            case GX_VA_NBT:
                break;
            default:
                GXSetArray(desc->attr, desc->vertex, desc->stride);
            }
        }
    }
    prev_vtxdesclist_array = NULL;
}

static inline void setupShapeAnimVtxDesc(HSD_PObj* pobj)
{
    HSD_VtxDescList* desc;

    GXClearVtxDesc();
    for (desc = pobj->verts; desc->attr != GX_VA_NULL; desc++) {
        switch (desc->attr) {
        case GX_VA_NRM:
        case GX_VA_POS:
        case GX_VA_NBT:
            GXSetVtxDesc(desc->attr, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt, GX_F32, 0);
            break;

        case GX_VA_PNMTXIDX:
        case GX_VA_TEX0MTXIDX:
        case GX_VA_TEX1MTXIDX:
        case GX_VA_TEX2MTXIDX:
        case GX_VA_TEX3MTXIDX:
        case GX_VA_TEX4MTXIDX:
        case GX_VA_TEX5MTXIDX:
        case GX_VA_TEX6MTXIDX:
        case GX_VA_TEX7MTXIDX:
            GXSetVtxDesc(desc->attr, desc->attr_type);
            break;

        default:
            GXSetVtxDesc(desc->attr, desc->attr_type);
            GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt,
                            desc->comp_type, desc->frac);
        }
    }
    prev_vtxdesc = NULL;
}

static inline void decode_u8_xyz(void* src_base, float dst[3], int scale)
{
    u8* src = src_base;
    dst[0] = (float) src[0] / scale;
    dst[1] = (float) src[1] / scale;
    dst[2] = (float) src[2] / scale;
}

static inline void decode_s8_xyz(void* src_base, float dst[3], int scale)
{
    s8* src = src_base;
    dst[0] = (float) src[0] / scale;
    dst[1] = (float) src[1] / scale;
    dst[2] = (float) src[2] / scale;
}

static inline void decode_u16_xyz(void* src_base, float dst[3], int scale)
{
    u16* src = src_base;
    dst[0] = (float) src[0] / scale;
    dst[1] = (float) src[1] / scale;
    dst[2] = (float) src[2] / scale;
}

static inline void decode_s16_xyz(void* src_base, float dst[3], int scale)
{
    s16* src = src_base;
    dst[0] = (float) src[0] / scale;
    dst[1] = (float) src[1] / scale;
    dst[2] = (float) src[2] / scale;
}

#pragma dont_inline on
static void get_shape_vertex_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, float dst[3])
{
    u8* index_array = shape_set->vertex_idx_list[shape_id];
    int idx;
    void* src_base;

    if (((HSD_VtxDescList*)shape_set->vertex_desc)->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    if (!(((HSD_VtxDescList*)shape_set->vertex_desc)->comp_cnt == GX_POS_XYZ)) __assert("pobj.c", 1077, "shape_set->vertex_desc->comp_cnt == GX_POS_XYZ");
    src_base = ((u8*) ((HSD_VtxDescList*)shape_set->vertex_desc)->vertex) +
               idx * ((HSD_VtxDescList*)shape_set->vertex_desc)->stride;

    if (((HSD_VtxDescList*)shape_set->vertex_desc)->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(float[3]));
    } else {
        int decimal_point = 1 << ((HSD_VtxDescList*)shape_set->vertex_desc)->frac;
        switch (((HSD_VtxDescList*)shape_set->vertex_desc)->comp_type) {
        case GX_U8:
            decode_u8_xyz(src_base, dst, decimal_point);
            break;

        case GX_S8:
            decode_s8_xyz(src_base, dst, decimal_point);
            break;

        case GX_U16:
            decode_u16_xyz(src_base, dst, decimal_point);
            break;

        case GX_S16:
            decode_s16_xyz(src_base, dst, decimal_point);
            break;

        default:
            HSD_Panic("pobj.c", 1120, "unexpected vertex type.\n");
        }
    }
}
#pragma dont_inline reset


#pragma dont_inline on
static void get_shape_normal_xyz(HSD_ShapeSet* shape_set, int shape_id,
                                 int arrayidx, float dst[3])
{
    u8* index_array = shape_set->normal_idx_list[shape_id];
    int idx;
    void* src_base;

    if (((HSD_VtxDescList*)shape_set->normal_desc)->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    if (!(((HSD_VtxDescList*)shape_set->normal_desc)->comp_cnt == GX_NRM_XYZ)) __assert("pobj.c", 1140, "shape_set->normal_desc->comp_cnt == GX_NRM_XYZ");
    src_base = ((u8*) ((HSD_VtxDescList*)shape_set->normal_desc)->vertex) +
               idx * ((HSD_VtxDescList*)shape_set->normal_desc)->stride;

    if (((HSD_VtxDescList*)shape_set->normal_desc)->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(float[3]));
    } else {
        int decimal_point = 1 << ((HSD_VtxDescList*)shape_set->normal_desc)->frac;
        switch (((HSD_VtxDescList*)shape_set->normal_desc)->comp_type) {
        case GX_U8:
            decode_u8_xyz(src_base, dst, decimal_point);
            break;
        case GX_S8:
            decode_s8_xyz(src_base, dst, decimal_point);
            break;
        case GX_U16:
            decode_u16_xyz(src_base, dst, decimal_point);
            break;
        case GX_S16:
            decode_s16_xyz(src_base, dst, decimal_point);
            break;
        default:
            HSD_Panic("pobj.c", 1183, "unexpected normal type.");
        }
    }
}
#pragma dont_inline reset


#pragma dont_inline on
static void get_shape_nbt_xyz(HSD_ShapeSet* shape_set, int shape_id,
                              int arrayidx, float* dst)
{
    u8* index_array = shape_set->normal_idx_list[shape_id];
    int i, idx;
    void* src_base;

    if (!(((HSD_VtxDescList*)shape_set->normal_desc)->attr == GX_VA_NBT)) __assert("pobj.c", 1196, "shape_set->normal_desc->attr == GX_VA_NBT");

    if (((HSD_VtxDescList*)shape_set->normal_desc)->attr_type == GX_INDEX16) {
        idx = index_array[arrayidx * 2];
        idx = (idx << 8) + index_array[arrayidx * 2 + 1];
    } else {
        idx = index_array[arrayidx];
    }

    if (!(((HSD_VtxDescList*)shape_set->normal_desc)->comp_cnt == GX_NRM_XYZ)) __assert("pobj.c", 1205, "shape_set->normal_desc->comp_cnt == GX_NRM_XYZ");

    src_base = ((u8*) ((HSD_VtxDescList*)shape_set->normal_desc)->vertex) +
               idx * ((HSD_VtxDescList*)shape_set->normal_desc)->stride;

    if (((HSD_VtxDescList*)shape_set->normal_desc)->comp_type == GX_F32) {
        memcpy(dst, src_base, sizeof(float[9]));
    } else {
        int decimal_point = 1 << ((HSD_VtxDescList*)shape_set->normal_desc)->frac;
        switch (((HSD_VtxDescList*)shape_set->normal_desc)->comp_type) {
        case GX_U8:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((u8*) src_base)[i] / decimal_point;
            }
            break;
        case GX_S8:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((s8*) src_base)[i] / decimal_point;
            }
            break;
        case GX_U16:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((u16*) src_base)[i] / decimal_point;
            }
            break;
        case GX_S16:
            for (i = 0; i < 9; i++) {
                dst[i] = (float) ((s16*) src_base)[i] / decimal_point;
            }
            break;
        default:
            HSD_Panic("pobj.c", 1236, "unexpected normal type.");
        }
    }
}
#pragma dont_inline reset


#pragma dont_inline on
static void interpretShapeAnimDisplayList(HSD_PObj* pobj, float (*vertex)[3],
                                          float (*normal)[3])
{
    u8* dl = pobj->display;
    int length = pobj->n_display << 5;
    int l;

    for (l = 0; l + 3 < length;) {
        int n = dl[1] << 8 | dl[2];
        int m = 3;
        int i, j;

        if ((dl[0] & GX_OPCODE_MASK) == GX_NOP) {
            break;
        }
        GXBegin((GXPrimitive) (dl[0] & GX_OPCODE_MASK),
                (GXVtxFmt) (dl[0] & GX_VAT_MASK), n);
        for (i = 0; i < n; i++) {
            for (j = 0;; j++) {
                HSD_VtxDescList* desc = &((HSD_VtxDescList*)pobj->verts)[j];
                if (desc->attr == GX_VA_NULL) {
                    break;
                } else {
                    u16 idx = dl[m++];
                    switch (desc->attr) {
                    case GX_VA_PNMTXIDX:
                    case GX_VA_TEX0MTXIDX:
                    case GX_VA_TEX1MTXIDX:
                    case GX_VA_TEX2MTXIDX:
                    case GX_VA_TEX3MTXIDX:
                    case GX_VA_TEX4MTXIDX:
                    case GX_VA_TEX5MTXIDX:
                    case GX_VA_TEX6MTXIDX:
                    case GX_VA_TEX7MTXIDX:
                        GXTexCoord1u8(idx);
                        break;

                    case GX_VA_POS:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        GXPosition3f32(vertex[idx][0], vertex[idx][1],
                                       vertex[idx][2]);
                        break;

                    case GX_VA_NRM:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        GXNormal3f32(normal[idx][0], normal[idx][1],
                                     normal[idx][2]);
                        break;

                    case GX_VA_NBT:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        idx *= 3;
                        GXNormal3f32(normal[idx + 0][0], normal[idx + 0][1],
                                     normal[idx + 0][2]);
                        GXNormal3f32(normal[idx + 1][0], normal[idx + 1][1],
                                     normal[idx + 1][2]);
                        GXNormal3f32(normal[idx + 2][0], normal[idx + 2][1],
                                     normal[idx + 2][2]);
                        break;

                    case GX_VA_TEX0:
                    case GX_VA_TEX1:
                    case GX_VA_TEX2:
                    case GX_VA_TEX3:
                    case GX_VA_TEX4:
                    case GX_VA_TEX5:
                    case GX_VA_TEX6:
                    case GX_VA_TEX7:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                            GXTexCoord1x16(idx);
                        } else {
                            GXTexCoord1x8(idx);
                        }
                        break;

                    case GX_VA_CLR0:
                    case GX_VA_CLR1:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                            GXColor1x16(idx);
                        } else if (desc->attr_type == GX_INDEX8) {
                            GXColor1x8(idx);
                        } else {
                            switch (desc->comp_type) {
                            case GX_RGB565:
                            case GX_RGBA4:
                                GXColor1u16((idx << 8) | dl[m++]);
                                break;
                            case GX_RGB8:
                            case GX_RGBA6:
                                GXColor3u8(idx, dl[m], dl[m + 1]);
                                m += 2;
                                break;
                            case GX_RGBA8:
                            case GX_RGBX8:
                                GXColor4u8(idx, dl[m], dl[m + 1], dl[m + 2]);
                                m += 3;
                                break;
                            }
                        }
                        break;
                    default:
                        if (desc->attr_type == GX_INDEX16) {
                            idx = (idx << 8) | dl[m++];
                        }
                        OSReport("attr(%d) is not supported by sysdolphin\n",
                                 desc->attr);
                        break;
                    }
                }
            }
        }
        GXEnd();
        l += m;
        dl += m;
    }
}
#pragma dont_inline reset


#define pobj_min(x, y) (x < y ? x : y)

static void drawShapeAnim(HSD_PObj* pobj)
{
    HSD_ShapeSet* shape_set = pobj->u.shape_set;
    float blend;
    int shape_id, i;
    int blend_nbt;

    if (vertex_buffer_size == 0) {
        vertex_buffer_size = HSD_DEFAULT_MAX_SHAPE_VERTICES;
        vertex_buffer = HSD_Alloc(vertex_buffer_size * sizeof(float[3]));
    }
    if (!(vertex_buffer_size >= shape_set->nb_vertex_index)) __assert("pobj.c", 1382, "vertex_buffer_size >= shape_set->nb_vertex_index");
    if (shape_set->normal_desc && normal_buffer_size == 0) {
        normal_buffer_size = HSD_DEFAULT_MAX_SHAPE_NORMALS;
        normal_buffer = HSD_Alloc(normal_buffer_size * sizeof(float[3]));
    }

    if (shape_set->normal_desc) {
        if (((HSD_VtxDescList*)shape_set->normal_desc)->attr == GX_VA_NRM) {
            if (!(normal_buffer_size >= shape_set->nb_normal_index)) __assert("pobj.c", 1391, "normal_buffer_size >= shape_set->nb_normal_index");
            blend_nbt = 0;
        } else {
            if (!(normal_buffer_size >= shape_set->nb_normal_index * 3)) __assert("pobj.c", 1394, "normal_buffer_size >= shape_set->nb_normal_index * 3");
            blend_nbt = 1;
        }
    }

    if (shape_set->flags & SHAPESET_AVERAGE) {
        blend = shape_set->blend.bl;
        shape_id = pobj_min(MAX(0, (int) blend), shape_set->nb_shape - 1);
        blend = pobj_min(MAX(0.0, blend - (float) shape_id), 1.0f);
        for (i = 0; i < shape_set->nb_vertex_index; i++) {
            float s0[3], s1[3];

            get_shape_vertex_xyz(shape_set, shape_id, i, s0);
            get_shape_vertex_xyz(
                shape_set, pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                s1);
            vertex_buffer[i][0] = (s1[0] - s0[0]) * blend + s0[0];
            vertex_buffer[i][1] = (s1[1] - s0[1]) * blend + s0[1];
            vertex_buffer[i][2] = (s1[2] - s0[2]) * blend + s0[2];
        }
        if (shape_set->nb_normal_index) {
            if (blend_nbt) {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    float s0[9], s1[9];
                    int j, idx = i * 3;

                    get_shape_nbt_xyz(shape_set, shape_id, i, s0);
                    get_shape_nbt_xyz(
                        shape_set,
                        pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                        s1);
                    for (j = 0; j < 9; j++) {
                        normal_buffer[idx][j] =
                            (s1[j] - s0[j]) * blend + s0[j];
                    }
                }
            } else {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    float s0[3], s1[3];

                    get_shape_normal_xyz(shape_set, shape_id, i, s0);
                    get_shape_normal_xyz(
                        shape_set,
                        pobj_min(shape_id + 1, shape_set->nb_shape - 1), i,
                        s1);
                    normal_buffer[i][0] = (s1[0] - s0[0]) * blend + s0[0];
                    normal_buffer[i][1] = (s1[1] - s0[1]) * blend + s0[1];
                    normal_buffer[i][2] = (s1[2] - s0[2]) * blend + s0[2];
                }
            }
        }
    } else {
        int j;
        float* blend_bp;
        blend_bp = shape_set->blend.bp;
        for (i = 0; i < shape_set->nb_vertex_index; i++) {
            get_shape_vertex_xyz(shape_set, 0, i, vertex_buffer[i]);
            for (j = 0; j < shape_set->nb_shape; j++) {
                float b = MAX(0.0, blend_bp[j]);
                float s[3];

                get_shape_vertex_xyz(shape_set, j + 1, i, s);
                vertex_buffer[i][0] += s[0] * b;
                vertex_buffer[i][1] += s[1] * b;
                vertex_buffer[i][2] += s[2] * b;
            }
        }
        if (shape_set->nb_normal_index) {
            if (blend_nbt) {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    int idx = i * 3;
                    get_shape_nbt_xyz(shape_set, 0, i, normal_buffer[idx]);
                    for (j = 0; j < shape_set->nb_shape; j++) {
                        float b = MAX(0.0, blend_bp[j]);
                        float s[9];
                        int k;

                        get_shape_nbt_xyz(shape_set, j + 1, i, s);
                        for (k = 0; k < 9; k++) {
                            normal_buffer[idx][k] += s[k] * b;
                        }
                    }
                }
            } else {
                for (i = 0; i < shape_set->nb_normal_index; i++) {
                    get_shape_normal_xyz(shape_set, 0, i, normal_buffer[i]);
                    for (j = 0; j < shape_set->nb_shape; j++) {
                        float b = MAX(0.0, blend_bp[j]);
                        float s[3];

                        get_shape_normal_xyz(shape_set, j + 1, i, s);
                        normal_buffer[i][0] += s[0] * b;
                        normal_buffer[i][1] += s[1] * b;
                        normal_buffer[i][2] += s[2] * b;
                    }
                }
            }
        }
    }
    interpretShapeAnimDisplayList(pobj, vertex_buffer, normal_buffer);
}

void HSD_PObjClearMtxMark(void* obj, unsigned int mark)
{
    int i;

    for (i = 0; i < 2; i++) {
        mtx_mark[i].obj = obj;
        mtx_mark[i].mark = mark;
    }
}

void HSD_PObjSetMtxMark(int idx, void* obj, unsigned int mark)
{
    if (idx >= 2) {
        return;
    }

    if (0 <= idx && idx < 2) {
    } else {
        mtx_mark[idx].obj = obj;
        mtx_mark[idx].mark = mark;
    }
}

void HSD_PObjGetMtxMark(int idx, void** obj, unsigned int* mark)
{
    if (!(obj)) __assert("pobj.c", 1630, "obj");
    if (!(mark)) __assert("pobj.c", 1631, "mark");

    if (idx < 0 || 2 <= idx) {
        *obj = NULL;
        *mark = 0;
    } else {
        *obj = mtx_mark[idx].obj;
        *mark = mtx_mark[idx].mark;
    }
}

static inline PObjSetupFlag GetSetupFlags(HSD_JObj* jobj, unsigned int rendermode)
{
    PObjSetupFlag flags = SETUP_NONE;
    if (jobj->flags & JOBJ_LIGHTING) flags |= SETUP_NORMAL;
    if (_HSD_TObjGetCurrentByType(NULL, 1)) flags |= SETUP_NORMAL | SETUP_REFLECTION;
    if (_HSD_TObjGetCurrentByType(NULL, 5)) flags |= SETUP_NORMAL | SETUP_REFLECTION;
    if (_HSD_TObjGetCurrentByType(NULL, 2)) flags |= SETUP_NORMAL | SETUP_HIGHLIGHT;
    return flags;
}

static inline void SetupRigidModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                               unsigned int rendermode)
{
    HSD_JObj* jobj;
    Mtx n;
    PObjSetupFlag flags;

    jobj = HSD_JObjGetCurrent();

    {
        void* obj;
        unsigned int mark;

        obj = mtx_mark[0].obj;
        mark = mtx_mark[0].mark;
        if (obj == jobj && mark == HSD_MTX_RIGID) {
            return;
        }
        HSD_PObjSetMtxMark(0, jobj, HSD_MTX_RIGID);
    }

    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadPosMtxImm(pmtx, GX_PNMTX0);


    flags = GetSetupFlags(jobj, rendermode);

    if (flags & SETUP_NORMAL) {
        HSD_MtxInverseTranspose(pmtx, n);
        if (jobj->flags & JOBJ_LIGHTING) {
            GXLoadNrmMtxImm(n, GX_PNMTX0);

        }
        if (flags & SETUP_NORMAL_PROJECTION) {
            GXLoadTexMtxImm(n, GX_TEXMTX0, GX_MTX3x4);

        }
    }
}

static void SetupSharedVtxModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                   unsigned int rendermode)
{
    HSD_JObj* jobj;
    Mtx n0, n1, m;
    PObjSetupFlag flags = SETUP_NONE;

    jobj = HSD_JObjGetCurrent();
    {
        void* obj;
        unsigned int mark;

        obj = mtx_mark[0].obj;
        mark = mtx_mark[0].mark;
        if (obj != jobj && mark != HSD_MTX_RIGID) {
            flags |= SETUP_JOINT0;
        }

        obj = mtx_mark[1].obj;
        mark = mtx_mark[1].mark;
        if (obj != pobj->u.jobj && mark != HSD_MTX_RIGID) {
            flags |= SETUP_JOINT1;
        }
    }

    if (flags == SETUP_NONE) {
        return;
    }

    flags |= GetSetupFlags(jobj, rendermode);

    if (flags | SETUP_JOINT0)
    {
        GXSetCurrentMtx(GX_PNMTX0);
        GXLoadPosMtxImm(pmtx, GX_PNMTX0);


        if (flags & SETUP_NORMAL) {
            HSD_MtxInverseTranspose(pmtx, n0);
            if (jobj->flags & 0x80) {
                GXLoadNrmMtxImm(n0, GX_PNMTX0);

            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(n0, GX_TEXMTX0, GX_MTX3x4);

            }
        }
    }
    if (flags | SETUP_JOINT1)
    {
        HSD_JObjSetupMatrix(pobj->u.jobj);
        PSMTXConcat(vmtx, pobj->u.jobj->mtx, m);
        GXLoadPosMtxImm(m, GX_PNMTX1);


        if (flags & SETUP_NORMAL) {
            HSD_MtxInverseTranspose(m, n1);
            if (jobj->flags & 0x80) {
                GXLoadNrmMtxImm(n1, GX_PNMTX1);

            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(n1, GX_TEXMTX1, GX_MTX3x4);

            }
        }
    }
}

static void SetupEnvelopeModelMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                  unsigned int rendermode)
{
    HSD_JObj* jobj;
    HSD_SList* list;
    int MtxIdx = 0;
    MtxPtr right;
    Mtx mtx;
    PObjSetupFlag flags = SETUP_NONE;

    jobj = HSD_JObjGetCurrent();
    HSD_PObjClearMtxMark(NULL, HSD_MTX_ENVELOPE);
    flags = GetSetupFlags(jobj, rendermode);
    right = _HSD_mkEnvelopeModelNodeMtx(jobj, mtx);

    for (MtxIdx = 0, list = pobj->u.envelope_list; MtxIdx < 10 && list;
         MtxIdx++, list = list->next)
    {
        Mtx mtx, tmp;
        MtxPtr mtxp;
        HSD_Envelope* envelope = list->data;
        int mtx_no = HSD_Index2PosNrmMtx(MtxIdx);
        int perf = 0;

        if (!(envelope)) __assert("pobj.c", 1813, "envelope");
        if (envelope->weight >= 1.0f) {
            HSD_JObjSetupMatrix(envelope->jobj);
            if (right) {
                MTXConcat(envelope->jobj->mtx, envelope->jobj->envelopemtx,
                          mtx);
                mtxp = mtx;
            } else {
                mtxp = envelope->jobj->mtx;
            }
        } else {
            mtx[0][0] = mtx[0][1] = mtx[0][2] = mtx[0][3] = mtx[1][0] =
                mtx[1][1] = mtx[1][2] = mtx[1][3] = mtx[2][0] = mtx[2][1] =
                    mtx[2][2] = mtx[2][3] = 0.0f;
            while (envelope) {
                HSD_JObj* jp;

                if (!(envelope->jobj)) __assert("pobj.c", 1833, "envelope->jobj");
                jp = envelope->jobj;
                HSD_JObjSetupMatrix(jp);
                if (!(jp->mtx)) __assert("pobj.c", 1836, "jp->mtx");
                if (!(jp->envelopemtx)) __assert("pobj.c", 1837, "jp->envelopemtx");

                MTXConcat(jp->mtx, jp->envelopemtx, tmp);
                HSD_MtxScaledAdd(tmp, mtx, mtx, envelope->weight);
                perf++;
                envelope = envelope->next;
            }
            mtxp = mtx;
        }

        if (right) {
            MTXConcat(mtxp, right, mtx);
        }
        MTXConcat(vmtx, mtxp, tmp);
        GXLoadPosMtxImm(tmp, mtx_no);


        if (!(rendermode & 0x4000000) && (flags & SETUP_NORMAL)) {
            HSD_MtxInverseTranspose(tmp, mtx);
            if (jobj->flags & JOBJ_LIGHTING) {
                GXLoadNrmMtxImm(mtx, mtx_no);

            }
            if (flags & SETUP_NORMAL_PROJECTION) {
                GXLoadTexMtxImm(mtx, HSD_Index2TexMtx(MtxIdx), GX_MTX3x4);

            }
        }
    }
}

static void PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, unsigned int rendermode)
{
    switch (pobj_type(pobj)) {
    case POBJ_SKIN:
        if (!pobj->u.jobj) {
            SetupRigidModelMtx(pobj, vmtx, pmtx, rendermode);
        } else {
            SetupSharedVtxModelMtx(pobj, vmtx, pmtx, rendermode);
        }
        break;
    case POBJ_SHAPEANIM:
        SetupRigidModelMtx(pobj, vmtx, pmtx, rendermode);
        break;
    case POBJ_ENVELOPE:
        SetupEnvelopeModelMtx(pobj, vmtx, pmtx, rendermode);
        break;
    }
}

static inline void PObjDispSimplePrimitive(HSD_PObj* pobj, unsigned int rendermode)
{
    setupArrayDesc(pobj->verts);
    setupVtxDesc(pobj);

    GXCallDisplayList(pobj->display, pobj->n_display << 5);
}

static inline void PObjDispShapeAnim(HSD_PObj* pobj, unsigned int rendermode)
{
    setupShapeAnimArrayDesc(pobj->verts);
    setupShapeAnimVtxDesc(pobj);

    if (!(pobj->u.shape_set)) __assert("pobj.c", 1913, "pobj->u.shape_set");
    drawShapeAnim(pobj);
}

void HSD_PObjDisp(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx, unsigned int rendermode)
{
    if (pobj->flags & 0x800) return;
    switch (pobj->flags & (POBJ_CULLFRONT | POBJ_CULLBACK)) {
    case 0x0:
        HSD_StateSetCullMode(GX_CULL_NONE);
        break;
    case POBJ_CULLFRONT:
        HSD_StateSetCullMode(GX_CULL_FRONT);
        break;
    case POBJ_CULLBACK:
        HSD_StateSetCullMode(GX_CULL_BACK);
        break;
    case POBJ_CULLFRONT | POBJ_CULLBACK:
        return;
    }

    HSD_POBJ_METHOD(pobj)->setup_mtx(pobj, vmtx, pmtx, rendermode);
    if (pobj_type(pobj) == POBJ_SHAPEANIM) {
        PObjDispShapeAnim(pobj, rendermode);
    } else {
        PObjDispSimplePrimitive(pobj, rendermode);
    }
}

static void PObjRelease(HSD_Class* o)
{
    HSD_PObj* pobj = HSD_POBJ(o);
    if (pobj->aobj) HSD_AObjRemove(pobj->aobj);
    switch (pobj_type(pobj)) {
    case POBJ_SHAPEANIM:
        HSD_ShapeSetRemove(pobj->u.shape_set);
        break;
    case POBJ_ENVELOPE:
        HSD_EnvelopeListFree(pobj->u.envelope_list);
        break;
    case POBJ_SKIN:
        HSD_JObjUnrefThis(pobj->u.jobj);
        break;
    default:
        break;
    }
    HSD_PARENT_INFO(&hsdPObj)->release(o);
}

static void PObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdPObj)) {
        if (_HSD_MemCheckOwn(vertex_buffer)) { vertex_buffer = NULL; vertex_buffer_size = 0; }
        if (_HSD_MemCheckOwn(normal_buffer)) { normal_buffer = NULL; normal_buffer_size = 0; }
        prev_vtxdesclist_array = NULL;
        prev_vtxdesc = NULL;
    }
    HSD_PARENT_INFO(&hsdPObj)->amnesia(info);
}

static void PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdPObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_pobj",
                     sizeof(HSD_PObjInfo), sizeof(HSD_PObj));
    HSD_CLASS_INFO(&hsdPObj)->release = PObjRelease;
    HSD_CLASS_INFO(&hsdPObj)->amnesia = PObjAmnesia;
    HSD_POBJ_INFO(&hsdPObj)->disp = HSD_PObjDisp;
    HSD_POBJ_INFO(&hsdPObj)->setup_mtx = PObjSetupMtx;
    HSD_POBJ_INFO(&hsdPObj)->load = PObjLoad;
    HSD_POBJ_INFO(&hsdPObj)->update = PObjUpdateFunc;
}

void* HSD_SetNormalBuffer(void* buffer, unsigned int size) { void* old=normal_buffer; normal_buffer_size=size; normal_buffer=buffer; return old; }
void* HSD_SetVertexBuffer(void* buffer, unsigned int size) { void* old=vertex_buffer; vertex_buffer_size=size; vertex_buffer=buffer; return old; }

/* Count display-list vertices and polygons using the configured attribute width. */
void HSD_PObjCountVertices(HSD_PObj* pobj, unsigned int* vertices, unsigned int* polygons)
{
    unsigned int nv=0, np=0;
    for (; pobj; pobj=pobj->next) {
        HSD_VtxDescList* desc;
        int stride=0, width;
        for (desc=pobj->verts; desc->attr!=GX_VA_NULL; desc++) {
            switch(desc->attr_type) {
            case GX_INDEX8: stride++; break;
            case GX_INDEX16: stride+=2; break;
            case GX_DIRECT:
                if (desc->attr==GX_VA_CLR0 || desc->attr==GX_VA_CLR1) {
                    switch(desc->comp_type) {
                    case GX_RGB565: case GX_RGBA4: width=2; break;
                    case GX_RGB8: case GX_RGBA6: width=3; break;
                    case GX_RGBX8: case GX_RGBA8: width=4; break;
                    }
                } else {
                    switch(desc->comp_type) {
                    case GX_U8: case GX_S8: width=1; break;
                    case GX_U16: case GX_S16: width=2; break;
                    case GX_F32: width=4; break;
                    default: goto next_pobj;
                    }
                }
                switch(desc->attr) {
                case GX_VA_PNMTXIDX: stride++; break;
                case GX_VA_POS: if (desc->comp_cnt==GX_POS_XY) stride+=2*width; else stride+=3*width; break;
                case GX_VA_NRM: if (desc->comp_cnt==GX_NRM_XYZ) stride+=3*width; break;
                case GX_VA_CLR0: case GX_VA_CLR1: stride+=width; break;
                case GX_VA_TEX0: case GX_VA_TEX1: case GX_VA_TEX2: case GX_VA_TEX3:
                case GX_VA_TEX4: case GX_VA_TEX5: case GX_VA_TEX6: case GX_VA_TEX7:
                    if (desc->comp_cnt==GX_TEX_S) stride+=width; else stride+=2*width; break;
                default: goto next_pobj;
                }
                break;
            }
        }
        if (pobj->display) {
            int offset=0, length=pobj->n_display<<5;
            unsigned char* dl=pobj->display;
            while(offset<length) {
                int primitive=dl[offset++] & GX_OPCODE_MASK;
                if (primitive) {
                    unsigned int count=(unsigned short)dl[offset];
                    count=(count<<8)+dl[offset+1];
                    nv+=count;
                    offset+=count*stride+2;
                    switch(primitive) {
                    case GX_TRIANGLES: np+=count/3; break;
                    case GX_TRIANGLESTRIP: case GX_TRIANGLEFAN: np+=count-2; break;
                    case GX_QUADS: np+=count/2; break;
                    }
                }
            }
        }
next_pobj:;
    }
    if(vertices) *vertices=nv;
    if(polygons) *polygons=np;
}
