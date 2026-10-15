/* XD light lifecycle, animation and hardware-light setup. */
#include "game/maximum/GSAPI/baselib/lobj.h"
#include "game/maximum/GSAPI/baselib/math_support.h"
typedef int bool; typedef int enum_t;
#define true 1
#define false 0
#define FILE_NAME "lobj.c"
#define HSD_ASSERT(line, cond) do { if (!(cond)) __assert(FILE_NAME, line, #cond); } while (0)
void __assert(const char*,int,const char*); void OSReport(const char*,...); void HSD_Panic(const char*,int,const char*);
void PSVECNormalize(Vec3*,Vec3*); void PSVECSubtract(Vec3*,Vec3*,Vec3*); void PSVECAdd(Vec3*,Vec3*,Vec3*);
void PSMTXMultVec(Mtx,Vec3*,Vec3*); void PSMTXMultVecSR(Mtx,Vec3*,Vec3*);
#define MTXMultVec PSMTXMultVec
#define VECNormalize PSVECNormalize
double __fabs(double);
static inline int vec_normalize_check(Vec3* src,Vec3* dst) { if (!src || !dst) return -1; if (__fabs(src->x)<=__float_min[0] && __fabs(src->y)<=__float_min[0] && __fabs(src->z)<=__float_min[0]) return -1; PSVECNormalize(src,dst); return 0; }
static inline int ref_DEC(HSD_LObj* o) { int ret; if ((ret = (o->parent.ref_count == 0xffff))) return ret; return o->parent.ref_count-- == 0; }
static inline void ref_INC(HSD_LObj* o) { if (o) { ++o->parent.ref_count; if (o->parent.ref_count == 0xffff) __assert("object.h",93,"HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF"); } }
static inline int WObjRefDec(HSD_WObj* o) { int ret; if ((ret = (o->parent.ref_count == 0xffff))) return ret; return o->parent.ref_count-- == 0; }
static inline void HSD_WObjUnref(HSD_WObj* o) { if (o && WObjRefDec(o)) hsdDelete(o); }
#define HSD_OBJECT_METHOD(o) ((HSD_ClassInfo*)(o)->parent.class_info)
static inline u8 HSD_LObjGetPriority(HSD_LObj* lobj) { if (!lobj) __assert("lobj.h",355,"lobj"); return lobj->priority; }
static HSD_LObjInfo* default_class;
static HSD_SList* current_lights;
static HSD_LObj* active_lights[MAX_GXLIGHT];
static s32 nb_active_lights;
static s32 lightmask_diffuse,lightmask_specular,lightmask_attnfunc,lightmask_alpha;
static void LObjInfoInit(void);
HSD_LObjInfo hsdLObj = { LObjInfoInit };
HSD_SList* HSD_SListPrepend(HSD_SList*,void*); HSD_SList* HSD_SListRemove(HSD_SList*);
typedef char LObjRuntimeSizeCheck[sizeof(HSD_LObjRuntime)==0xD4?1:-1];
typedef char LObjPrefixSizeCheck[sizeof(HSD_LObj)==0x4C?1:-1];
typedef char LObjInfoSizeCheck[sizeof(HSD_LObjInfo)==0x44?1:-1];
static inline float clamp_unit(float v) { if (v <= 0.0F) return 0.0F; if (v >= 1.0F) return 1.0F; return v; }
static inline u32 HSD_LObjGetType(HSD_LObj* lobj);
static inline void HSD_LObjSetActive(HSD_LObj* lobj);
static inline void HSD_LObjClearActive(void);
static inline void setup_diffuse_lightobj(HSD_LObj* lobj);
static inline void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id);
static inline void setup_infinite_lightobj(HSD_LObj* lobj, MtxPtr vmtx);
static inline void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx);
static inline void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx);
static inline void HSD_LObjAddCurrent(HSD_LObj* lobj);
static inline void HSD_LObjUnrefThis(HSD_LObj* lobj);
static inline void HSD_LObjDeleteCurrent(HSD_LObj* lobj);
static inline void LObjRemoveAll(void);
static inline u32 HSD_LightID2Index(GXLightID id);
static inline s32 HSD_Index2LightID(u32 index);
static inline void HSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func);
static inline void HSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func);
static inline void HSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2);
static inline void HSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2);
static inline void HSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2);
static inline HSD_LObjInfo* HSD_LObjGetDefaultClass(void);
static inline HSD_LObj* HSD_LObjAlloc(void);
static inline HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj);
static inline HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj);
static inline void HSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj);
static inline void HSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj);
static inline void HSD_LObjAddAnim(HSD_LObj* lobj, HSD_LightAnim* lanim);
static inline void HSD_LObjRemoveAnim(HSD_LObj* lobj);
static inline void HSD_LObjRemoveAnimByFlags(HSD_LObj* lobj);
static void LObjInfoInit(void);
static void LObjAmnesia(HSD_ClassInfo* info);
static void LObjRelease(HSD_Class* o);
void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim);
HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc);
static int LObjLoad(HSD_LObj* lobj, HSD_LightDesc* ldesc);
bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest);
void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest);
bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position);
void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position);
void HSD_LObjGetColor(HSD_LObj* lobj, GXColor* color);
void HSD_LObjSetColor(HSD_LObj* lobj, GXColor color);
HSD_LObj* HSD_LObjGetCurrentByType(u16 flags);
void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj);
void HSD_LObjAddCurrentAll(HSD_LObj* lobj);
void HSD_LObjSetupInit(HSD_CObj* cobj);
void HSD_LObjSetupSpecularInit(Mtx pmtx);
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess);
void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjAnimAll(HSD_LObj* lobj);
void HSD_LObjAnim(HSD_LObj* lobj);
static void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);
void HSD_LObjRemoveAnimAll(HSD_LObj* lobj);
HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx);
HSD_LObj* HSD_LObjGetActiveByID(GXLightID id);
s32 HSD_LObjGetNbActive(void);
s32 HSD_LObjGetLightMaskSpecular(void);
s32 HSD_LObjGetLightMaskAlpha(void);
s32 HSD_LObjGetLightMaskAttnFunc(void);
GXLightID HSD_LObjGetLightMaskDiffuse(void);
void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags);
void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags);
u32 HSD_LObjGetFlags(HSD_LObj* lobj);


static inline u32 HSD_LObjGetType(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

static inline void HSD_LObjSetActive(HSD_LObj* lobj)
{
    int idx;

    if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        idx = MAX_GXLIGHT - 1;
        if (active_lights[idx]) {
            return;
        }
    } else {
        idx = nb_active_lights++;
    }
    active_lights[idx] = lobj;
    LOBJ_EXT(lobj)->id = HSD_Index2LightID(idx);
}

static inline void HSD_LObjClearActive(void)
{
    int i;

    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
}

static inline void setup_diffuse_lightobj(HSD_LObj* lobj)
{


    GXInitLightColor(&LOBJ_EXT(lobj)->lightobj, LOBJ_EXT(lobj)->color);
    LOBJ_EXT(lobj)->hw_color = LOBJ_EXT(lobj)->color;
    lobj->flags |= LOBJ_DIFF_DIRTY;

    switch (HSD_LObjGetType(lobj)) {
    case LOBJ_SPOT:
    case LOBJ_POINT:
        lightmask_attnfunc |= LOBJ_EXT(lobj)->id;
        break;
    case LOBJ_INFINITE:
        break;
    default:
        HSD_ASSERT(664, 0);
    }

    if (lobj->flags & LOBJ_DIFFUSE) lightmask_diffuse |= LOBJ_EXT(lobj)->id;
    if (lobj->flags & LOBJ_ALPHA) {
        lightmask_alpha |= LOBJ_EXT(lobj)->id;
    }
}

static inline void setup_spec_lightobj(HSD_LObj* lobj, Mtx mtx, s32 spec_id)
{
    f32 x;

    LOBJ_EXT(lobj)->spec_id = spec_id;
    if (spec_id != 0) {
        GXInitLightColor(&LOBJ_EXT(lobj)->spec_lightobj, LOBJ_EXT(lobj)->color);
        lobj->shininess = 50.0F;

        x =
#ifdef MUST_MATCH
            x =
#endif
                lobj->shininess;

        x *= 0.5F;
        GXInitLightAttn(&LOBJ_EXT(lobj)->spec_lightobj, 0.0F, 0.0F, 1.0F, x, 0.0F,
                        1.0F - x);
        switch (HSD_LObjGetType(lobj)) {
        case 2:
        case 3:
            HSD_LObjGetPosition(lobj, &lobj->lvec);
            MTXMultVec(mtx, &lobj->lvec, &lobj->lvec);
            break;
        case 1:
            HSD_LObjGetLightVector(lobj, &lobj->lvec);
            PSMTXMultVecSR(mtx, &lobj->lvec, &lobj->lvec);
            if (vec_normalize_check(&lobj->lvec, &lobj->lvec)) { lobj->lvec.x=0.0F; lobj->lvec.y=0.0F; lobj->lvec.z=-1.0F; }
            break;
        default:
            HSD_ASSERT(704, 0);
        }
        lobj->flags |= 0x100;
        lightmask_specular |= spec_id;
    }
}

static inline void setup_infinite_lightobj(HSD_LObj* lobj, MtxPtr vmtx)
{
    Vec3 lpos;

    HSD_LObjGetPosition(lobj, &lpos);
    lpos.x *= 1048576.0F;
    lpos.y *= 1048576.0F;
    lpos.z *= 1048576.0F;
    MTXMultVec(vmtx, &lpos, &lpos);
    if (lobj->flags & LOBJ_DIFFUSE) {
        GXInitLightPos(&LOBJ_EXT(lobj)->lightobj, lpos.x, lpos.y, lpos.z);
        GXInitLightAttn(&LOBJ_EXT(lobj)->lightobj, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    }
    if (lobj->flags & LOBJ_SPECULAR) {
        GXInitLightPos(&LOBJ_EXT(lobj)->spec_lightobj, lpos.x, lpos.y, lpos.z);
    }
}

static inline void setup_point_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;

    GXInitLightColor(&LOBJ_EXT(lobj)->lightobj, LOBJ_EXT(lobj)->color);
    LOBJ_EXT(lobj)->hw_color = LOBJ_EXT(lobj)->color;
    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    GXInitLightPos(&LOBJ_EXT(lobj)->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&LOBJ_EXT(lobj)->spec_lightobj, lpos.x, lpos.y, lpos.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&LOBJ_EXT(lobj)->lightobj, 1.0F, 0.0F, 0.0F, LOBJ_EXT(lobj)->u.attn.k0,
                        LOBJ_EXT(lobj)->u.attn.k1, LOBJ_EXT(lobj)->u.attn.k2);
    } else {
        f32 ref_br = LOBJ_EXT(lobj)->u.spot.ref_br;
        f32 ref_dist = LOBJ_EXT(lobj)->u.spot.ref_dist;
        s32 dist_func = LOBJ_EXT(lobj)->u.spot.dist_func;
        if (ref_dist < __float_epsilon[0]) ref_dist=__float_epsilon[0];
        if (ref_br < __float_epsilon[0]) ref_br=__float_epsilon[0];
        GXInitLightDistAttn(&LOBJ_EXT(lobj)->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&LOBJ_EXT(lobj)->lightobj, 0.0F, 0);
        GXInitLightDistAttn(&LOBJ_EXT(lobj)->spec_lightobj, ref_dist, ref_br, dist_func);
    }
}

static inline void setup_spot_lightobj(HSD_LObj* lobj, Mtx mtx)
{
    Vec3 lpos;
    Vec3 ldir;

    HSD_LObjGetPosition(lobj, &lpos);
    MTXMultVec(mtx, &lpos, &lpos);
    HSD_LObjGetLightVector(lobj, &ldir);
    PSMTXMultVecSR(mtx, &ldir, &ldir);
    PSVECNormalize(&ldir, &ldir);
    GXInitLightPos(&LOBJ_EXT(lobj)->lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightPos(&LOBJ_EXT(lobj)->spec_lightobj, lpos.x, lpos.y, lpos.z);
    GXInitLightDir(&LOBJ_EXT(lobj)->lightobj, ldir.x, ldir.y, ldir.z);
    if (lobj->flags & 0x40) {
        GXInitLightAttn(&LOBJ_EXT(lobj)->lightobj, LOBJ_EXT(lobj)->u.attn.a0, LOBJ_EXT(lobj)->u.attn.a1,
                        LOBJ_EXT(lobj)->u.attn.a2, LOBJ_EXT(lobj)->u.attn.k0, LOBJ_EXT(lobj)->u.attn.k1,
                        LOBJ_EXT(lobj)->u.attn.k2);
    } else {
        f32 ref_br = LOBJ_EXT(lobj)->u.point.ref_br;
        f32 ref_dist = LOBJ_EXT(lobj)->u.point.ref_dist;
        f32 cutoff = LOBJ_EXT(lobj)->u.point.cutoff;
        s32 spot_func = LOBJ_EXT(lobj)->u.spot.spot_func;
        s32 dist_func = LOBJ_EXT(lobj)->u.spot.dist_func;

        if (ref_dist < __float_epsilon[0]) ref_dist=__float_epsilon[0];
        if (ref_br < __float_epsilon[0]) ref_br=__float_epsilon[0];
        GXInitLightDistAttn(&LOBJ_EXT(lobj)->lightobj, ref_dist, ref_br, dist_func);
        GXInitLightDistAttn(&LOBJ_EXT(lobj)->spec_lightobj, ref_dist, ref_br, dist_func);
        GXInitLightSpot(&LOBJ_EXT(lobj)->lightobj, cutoff, spot_func);
    }
}

static inline void HSD_LObjAddCurrent(HSD_LObj* lobj)
{
    HSD_SList* node;
    HSD_SList** p;

    if (lobj != NULL) {
        node = current_lights;
        while (node != NULL) {
            if (node->data == lobj) {
                HSD_LObjDeleteCurrent(lobj);
                break;
            }
            node = node->next;
        }
        ref_INC(lobj);
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if (HSD_LObjGetPriority((*p)->data) > HSD_LObjGetPriority(lobj)) {
                break;
            }
        }
        *p = HSD_SListPrepend(*p, lobj);
    }
}

static inline void HSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        if (lobj != NULL) {
            HSD_OBJECT_METHOD(lobj)->release((HSD_Class*) lobj);
            HSD_OBJECT_METHOD(lobj)->destroy((HSD_Class*) lobj);
        }
    }
}

static inline void HSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < MAX_GXLIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                HSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

static inline void LObjRemoveAll(void)
{
    int i;
    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
}

static inline u32 HSD_LightID2Index(GXLightID id)
{
    u32 index;
    switch (id) {
    case GX_LIGHT0:
        index = 0;
        break;
    case GX_LIGHT1:
        index = 1;
        break;
    case GX_LIGHT2:
        index = 2;
        break;
    case GX_LIGHT3:
        index = 3;
        break;
    case GX_LIGHT4:
        index = 4;
        break;
    case GX_LIGHT5:
        index = 5;
        break;
    case GX_LIGHT6:
        index = 6;
        break;
    case GX_LIGHT7:
        index = 7;
        break;
    case GX_MAX_LIGHT:
        index = 8;
        break;
    default:
        HSD_ASSERT(1192, 0);
        break;
    }
    return index;
}

static inline s32 HSD_Index2LightID(u32 index)
{
    switch (index) {
    case 0:
        return GX_LIGHT0;
    case 1:
        return GX_LIGHT1;
    case 2:
        return GX_LIGHT2;
    case 3:
        return GX_LIGHT3;
    case 4:
        return GX_LIGHT4;
    case 5:
        return GX_LIGHT5;
    case 6:
        return GX_LIGHT6;
    case 7:
        return GX_LIGHT7;
    case 8:
        return GX_MAX_LIGHT;
    default:
        return GX_LIGHT_NULL;
    }
}

static inline void HSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func)
{
    if (lobj != NULL) {
        LOBJ_EXT(lobj)->u.point.cutoff = cutoff;
        LOBJ_EXT(lobj)->u.point.point_func = point_func;
    }
}

static inline void HSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func)
{
    if (lobj != NULL) {
        LOBJ_EXT(lobj)->u.point.ref_dist = ref_dist;
        LOBJ_EXT(lobj)->u.point.ref_br = ref_br;
        LOBJ_EXT(lobj)->u.point.dist_func = dist_func;
    }
}

static inline void HSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2)
{
    if (lobj == NULL) {
        return;
    }

    LOBJ_EXT(lobj)->u.attn.a0 = a0;
    LOBJ_EXT(lobj)->u.attn.a1 = a1;
    LOBJ_EXT(lobj)->u.attn.a2 = a2;
}

static inline void HSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2)
{
    if (lobj == NULL) {
        return;
    }

    LOBJ_EXT(lobj)->u.attn.k0 = k0;
    LOBJ_EXT(lobj)->u.attn.k1 = k1;
    LOBJ_EXT(lobj)->u.attn.k2 = k2;
}

static inline void HSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2)
{
    HSD_LObjSetAttnA(lobj, a0, a1, a2);
    HSD_LObjSetAttnK(lobj, k0, k1, k2);
}

static inline HSD_LObjInfo* HSD_LObjGetDefaultClass(void)
{
    return default_class ? default_class : &hsdLObj;
}

static inline HSD_LObj* HSD_LObjAlloc(void)
{
    HSD_LObj* new = hsdNew(&HSD_LObjGetDefaultClass()->parent);
    HSD_ASSERT(1500, new);
    return new;
}

static inline HSD_WObj* HSD_LObjGetPositionWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->position;
    }
    return NULL;
}

static inline HSD_WObj* HSD_LObjGetInterestWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->interest;
    }
    return NULL;
}

static inline void HSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->position);
    lobj->position = wobj;
}

static inline void HSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->interest);
    lobj->interest = wobj;
}

static inline void HSD_LObjAddAnim(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    if (lobj == NULL) {
        return;
    }

    if (lanim != NULL) {
        if (lobj->aobj) {
            HSD_AObjRemove(lobj->aobj);
        }
        lobj->aobj = HSD_AObjLoadDesc(lanim->aobjdesc);
        HSD_WObjAddAnim(HSD_LObjGetPositionWObj(lobj), lanim->position_anim);
        HSD_WObjAddAnim(HSD_LObjGetInterestWObj(lobj), lanim->interest_anim);
    }
}

static inline void HSD_LObjRemoveAnim(HSD_LObj* lobj) { if (!lobj) return; HSD_AObjRemove(lobj->aobj); lobj->aobj = NULL; HSD_WObjRemoveAnim(HSD_LObjGetPositionWObj(lobj)); HSD_WObjRemoveAnim(HSD_LObjGetInterestWObj(lobj)); }

static inline void HSD_LObjRemoveAnimByFlags(HSD_LObj* lobj) { HSD_LObj* cur; if (!lobj) return; for (cur=lobj; cur; cur=cur->next) HSD_LObjRemoveAnim(cur); }

static void LObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdLObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_lobj",
                     sizeof(HSD_LObjInfo), sizeof(HSD_LObjRuntime));
    HSD_CLASS_INFO(&hsdLObj)->release = LObjRelease;
    HSD_CLASS_INFO(&hsdLObj)->amnesia = LObjAmnesia;
    HSD_LOBJ_INFO(&hsdLObj)->load = LObjLoad;
    HSD_LOBJ_INFO(&hsdLObj)->update = LObjUpdateFunc;
}

static void LObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdLObj)) {
        current_lights = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdLObj)->amnesia(info);
}

static void LObjRelease(HSD_Class* o)
{
    HSD_LObj* lobj = HSD_LOBJ(o);
    ///@todo Unused stack


    HSD_AObjRemove(lobj->aobj);
    HSD_WObjUnref(HSD_LObjGetPositionWObj(lobj));
    HSD_WObjUnref(HSD_LObjGetInterestWObj(lobj));

    HSD_OBJECT_PARENT_INFO(&hsdLObj)->release(o);
}

void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    HSD_LObj* lp;
    HSD_LightAnim* la;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj, la = lanim; lp; lp = next_p(lp), la = next_p(la)) {
        HSD_LObjAddAnim(lp, la);
    }
}

HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc)
{
    HSD_LObj *top, **p = &top;

    for (; ldesc; ldesc = ldesc->next) {
        HSD_ClassInfo* info;

        if (!ldesc->class_name ||
            !(info = hsdSearchClassInfo(ldesc->class_name)))
        {
            *p = HSD_LObjAlloc();
        } else {
            *p = hsdNew(info);
            HSD_ASSERT(1666, *p);
        }
        HSD_LOBJ_METHOD(*p)->load(*p, ldesc);
        p = &(*p)->next;
    }
    *p = NULL;

    return top;
}

static int LObjLoad(HSD_LObj* lobj, HSD_LightDesc* ldesc)
{
    HSD_LObjSetColor(lobj, ldesc->color);
    HSD_LObjSetFlags(lobj, ldesc->flags);
    switch (ldesc->flags & LOBJ_TYPE_MASK) {
    case LOBJ_AMBIENT:
        break;
    case LOBJ_INFINITE:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        break;
    case LOBJ_POINT:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            HSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            HSD_LObjSetAttnK(lobj, ldesc->u.attn->k0, ldesc->u.attn->k1,
                             ldesc->u.attn->k2);
        } else {
            HSD_LObjSetDistAttn(lobj, ldesc->u.point->ref_dist,
                                ldesc->u.point->ref_br,
                                ldesc->u.point->dist_func);
        }
        break;
    case LOBJ_SPOT:
        HSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        HSD_LObjSetInterestWObj(lobj, HSD_WObjLoadDesc(ldesc->interest));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            HSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            HSD_LObjSetAttn(lobj, ldesc->u.attn->a0, ldesc->u.attn->a1,
                            ldesc->u.attn->a2, ldesc->u.attn->k0,
                            ldesc->u.attn->k1, ldesc->u.attn->k2);
        } else {
            HSD_LObjSetDistAttn(lobj, ldesc->u.spot->ref_dist,
                                ldesc->u.spot->ref_br,
                                ldesc->u.spot->dist_func);
            HSD_LObjSetSpot(lobj, ldesc->u.spot->cutoff,
                            ldesc->u.spot->spot_func);
        }
        break;
    default:
        OSReport("unexpected lightdesc flags (%x)\n", ldesc->flags);
        HSD_Panic(FILE_NAME, 1632, "");
        break;
    }
    return 0;
}

bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}

void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest)
{
    HSD_ASSERT(1427, lobj);
    if (lobj->interest == NULL) {
        lobj->interest = HSD_WObjAlloc();
        HSD_ASSERT(1430, lobj->interest);
    }
    HSD_WObjSetPosition(lobj->interest, interest);
}

bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position)
{
    HSD_ASSERT(1391, lobj);
    if (lobj->position == NULL) {
        lobj->position = HSD_WObjAlloc();
        HSD_ASSERT(1394, lobj->position);
    }
    HSD_WObjSetPosition(lobj->position, position);
}

void HSD_LObjGetColor(HSD_LObj* lobj, GXColor* color)
{
    *color = LOBJ_EXT(lobj)->color;
}

void HSD_LObjSetColor(HSD_LObj* lobj, GXColor color)
{
    LOBJ_EXT(lobj)->color = color;
}

HSD_LObj* HSD_LObjGetCurrentByType(u16 flags)
{
    u32 type = flags & LOBJ_TYPE_MASK;
    HSD_SList* cur = current_lights;
    while (cur != NULL) {
        HSD_LObj* lobj = cur->data;
        if (type == (lobj->flags & LOBJ_TYPE_MASK)) {
            return lobj;
        }
        cur = cur->next;
    }
    return NULL;
}

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        while (lobj != NULL) {
            HSD_LObjDeleteCurrent(lobj);
            lobj = lobj->next;
        }
        return;
    }
    LObjRemoveAll();
}

void HSD_LObjAddCurrentAll(HSD_LObj* lobj) { for (; lobj; lobj = lobj->next) HSD_LObjAddCurrent(lobj); }

void HSD_LObjSetupInit(HSD_CObj* cobj)
{
    MtxPtr vmtx;
    int i, num, idx;
    HSD_SList* list;

    idx = 0;
    num = 0;

    lightmask_diffuse = GX_LIGHT_NULL;
    lightmask_specular = GX_LIGHT_NULL;
    lightmask_attnfunc = GX_LIGHT_NULL;
    lightmask_alpha = GX_LIGHT_NULL;
    vmtx = cobj->view_mtx;

    HSD_LObjClearActive();

    for (list = current_lights; idx < MAX_GXLIGHT - 1 && list;
         list = list->next)
    {
        HSD_LObj* lobj = list->data;
        u32 flags;
        u32 type;
        int ref_type;

        if (!lobj) continue;
        flags = lobj->flags;

        if (flags & LOBJ_HIDDEN) {
            continue;
        }

        type = HSD_LObjGetType(lobj);
        ref_type = flags & (LOBJ_DIFFUSE | LOBJ_SPECULAR | LOBJ_ALPHA);

        if (!ref_type) continue;

        HSD_LObjSetActive(lobj);
        idx = HSD_LObjGetNbActive();

        LOBJ_EXT(lobj)->spec_id = GX_LIGHT_NULL;

        switch (type) {
        case LOBJ_INFINITE:
            setup_infinite_lightobj(lobj, vmtx);
            break;
        case LOBJ_POINT:
            setup_point_lightobj(lobj, vmtx);
            break;
        case LOBJ_SPOT:
            setup_spot_lightobj(lobj, vmtx);
            break;
        case LOBJ_AMBIENT:
            continue;
        }

        if (ref_type & (LOBJ_DIFFUSE | LOBJ_ALPHA)) { setup_diffuse_lightobj(lobj); } else if (ref_type & LOBJ_SPECULAR) { setup_spec_lightobj(lobj,vmtx,LOBJ_EXT(lobj)->id); }
    }

    if (!active_lights[8]) {
        for (; list; list = list->next) {
            HSD_LObj* lobj = list->data;
            if (!lobj) continue;

            if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT &&
                !(lobj->flags & LOBJ_HIDDEN) && (lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA)))
            {
                HSD_LObjSetActive(lobj);
                break;
            }
        }
    }

    num = HSD_LObjGetNbActive();
    for (i=0; idx < MAX_GXLIGHT-1 && i<num; i++) {
        HSD_LObj* lobj=HSD_LObjGetActiveByIndex(i);
        if (!lobj || !(lobj->flags & LOBJ_SPECULAR) || !(lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA))) continue;
        setup_spec_lightobj(lobj,vmtx,HSD_Index2LightID(idx++));
    }

    for (i = 0; i < num; i++) {
        HSD_LObj* lobj;

        if (!(lobj = HSD_LObjGetActiveByIndex(i))) {
            return;
        }
        HSD_LObjSetup(lobj, LOBJ_EXT(lobj)->color, lobj->shininess);
    }
}

void HSD_LObjSetupSpecularInit(Mtx pmtx)
{
    int i;
    s32 num;
    Vec3 cdir;
    Vec3 jpos;

    jpos.x = pmtx[0][3];
    jpos.y = pmtx[1][3];
    jpos.z = pmtx[2][3];
    if (vec_normalize_check(&jpos, &cdir)) { cdir.x=0.0F; cdir.y=0.0F; cdir.z=-1.0F; }

    num = HSD_LObjGetNbActive();
    for (i = 0; i < num; i++) {
        Vec3 half, ldir;
        HSD_LObj* lobj = HSD_LObjGetActiveByIndex(i);

        if (LOBJ_EXT(lobj)->spec_id == GX_LIGHT_NULL) {
            continue;
        }

        switch (HSD_LObjGetType(lobj)) {
        case LOBJ_POINT:
        case LOBJ_SPOT:
            PSVECSubtract(&jpos, &lobj->lvec, &ldir);
            if (!vec_normalize_check(&ldir, &ldir)) { PSVECAdd(&ldir,&cdir,&half); } else { half.x=0.0F; half.y=0.0F; half.z=1.0F; goto set_specular_direction; }
            break;

        case LOBJ_INFINITE:
            PSVECAdd(&lobj->lvec, &cdir, &half);
            break;

        default:
            HSD_ASSERT(634, 0);
        }
        if (vec_normalize_check(&half, &half)) { half.x=0.0F; half.y=0.0F; half.z=1.0F; }
set_specular_direction:
        GXInitLightDir(&LOBJ_EXT(lobj)->spec_lightobj, half.x, half.y, half.z);
        lobj->flags |= LOBJ_SPEC_DIRTY;
    }
}

void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess)
{
    f32 k0 = shininess;

    if (lobj->flags & LOBJ_HIDDEN || HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        return;
    }

    if ((lobj->flags & (LOBJ_DIFFUSE | LOBJ_ALPHA)) != 0) {
        if (LOBJ_EXT(lobj)->hw_color.r != color.r || LOBJ_EXT(lobj)->hw_color.g != color.g ||
            LOBJ_EXT(lobj)->hw_color.b != color.b || LOBJ_EXT(lobj)->hw_color.a != color.a)
        {
            GXInitLightColor(&LOBJ_EXT(lobj)->lightobj, color);
            LOBJ_EXT(lobj)->hw_color = color;
            lobj->flags |= LOBJ_DIFF_DIRTY;
        }

        if (lobj->flags & LOBJ_DIFF_DIRTY) {
            GXLoadLightObjImm(&LOBJ_EXT(lobj)->lightobj, LOBJ_EXT(lobj)->id);
            lobj->flags &= ~LOBJ_DIFF_DIRTY;
        }
    }

    if (LOBJ_EXT(lobj)->spec_id != GX_LIGHT_NULL) {
        if (lobj->shininess != shininess) {
            lobj->shininess = shininess;
            k0 *= 0.5F;
            GXInitLightAttn(&LOBJ_EXT(lobj)->spec_lightobj, 0.0F, 0.0F, 1.0F, k0, 0.0F,
                            1.0F - k0);
            lobj->flags |= LOBJ_SPEC_DIRTY;
        }

        if (lobj->flags & LOBJ_SPEC_DIRTY) {
            GXLoadLightObjImm(&LOBJ_EXT(lobj)->spec_lightobj, LOBJ_EXT(lobj)->spec_id);
            lobj->flags &= ~LOBJ_SPEC_DIRTY;
        }
    }
}

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = {0.0F,0.0F,0.0F};
    Vec3 interest = {0.0F,0.0F,0.0F};

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    if (vec_normalize_check(dir,dir)) { dir->x = 0.0F; dir->y = 0.0F; dir->z = 1.0F; }
}

void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjReqAnim(lp, startframe);
    }
}

void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe)
{
    if (lobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjAnimAll(HSD_LObj* lobj)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjAnim(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, HSD_LOBJ_METHOD(lobj)->update);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

static void LObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_LObj* lobj = obj;

    if (lobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_L_VIS:
        if (val->fv >= 0.5) {
            lobj->flags &= ~LOBJ_HIDDEN;
        } else {
            lobj->flags |= LOBJ_HIDDEN;
        }
        break;
    case HSD_A_L_A0:
    case HSD_A_L_CUTOFF:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.a0 = val->fv;
        } else {
            LOBJ_EXT(lobj)->u.spot.cutoff = val->fv;
        }
        break;
    case HSD_A_L_A1:
    case HSD_A_L_REFDIST:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.a1 = val->fv;
        } else {
            LOBJ_EXT(lobj)->u.spot.ref_dist = val->fv;
        }
        break;
    case HSD_A_L_A2:
    case HSD_A_L_REFBRIGHT:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.a2 = val->fv;
        } else {
            LOBJ_EXT(lobj)->u.spot.ref_br = val->fv;
        }
        break;
    case HSD_A_L_K0:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.k0 = val->fv;
        }
        break;
    case HSD_A_L_K1:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.k1 = val->fv;
        }
        break;
    case HSD_A_L_K2:
        if (lobj->flags & LOBJ_RAW_PARAM) {
            LOBJ_EXT(lobj)->u.attn.k2 = val->fv;
        }
        break;
    case HSD_A_L_LITC_R:
        { float v = clamp_unit(val->fv); LOBJ_EXT(lobj)->color.r = 255.0F * v; }
        break;
    case HSD_A_L_LITC_G:
        { float v = clamp_unit(val->fv); LOBJ_EXT(lobj)->color.g = 255.0F * v; }
        break;
    case HSD_A_L_LITC_B:
        { float v = clamp_unit(val->fv); LOBJ_EXT(lobj)->color.b = 255.0F * v; }
        break;
    case HSD_A_L_LITC_A:
        { float v = clamp_unit(val->fv); LOBJ_EXT(lobj)->color.a = 255.0F * v; }
        break;
    }
}

void HSD_LObjRemoveAnimAll(HSD_LObj* lobj) { HSD_LObj* cur; if (!lobj) return; for (cur=lobj; cur; cur=cur->next) HSD_LObjRemoveAnimByFlags(cur); }

HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx)
{
    if (0 <= idx && idx < MAX_GXLIGHT - 1) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

HSD_LObj* HSD_LObjGetActiveByID(GXLightID id)
{
    s32 idx = HSD_LightID2Index(id);
    if (0 <= idx && idx < MAX_GXLIGHT) {
        return active_lights[idx];
    } else {
        return NULL;
    }
}

s32 HSD_LObjGetNbActive(void)
{
    return nb_active_lights;
}

s32 HSD_LObjGetLightMaskSpecular(void)
{
    return lightmask_specular;
}

s32 HSD_LObjGetLightMaskAlpha(void)
{
    return lightmask_alpha;
}

s32 HSD_LObjGetLightMaskAttnFunc(void)
{
    return lightmask_attnfunc;
}

GXLightID HSD_LObjGetLightMaskDiffuse(void)
{
    return lightmask_diffuse;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags &= ~flags;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return lobj ? lobj->flags : 0;
}
