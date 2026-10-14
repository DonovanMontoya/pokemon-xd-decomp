/* XD USA camera/material implementation adapted from the baselib reference. */
#include "game/maximum/GSAPI/baselib/mobj.h"
typedef int enum_t;
#define FILE_NAME "mobj.c"
void __assert(const char*,int,const char*);
void* memcpy(void*,const void*,unsigned long);
void* memset(void*,int,unsigned long);
void* hsdAllocMemPiece(int); void hsdFreeMemPiece(void*,int);
#define HSD_ASSERT(line, cond) do { if (!(cond)) __assert(FILE_NAME, line, #cond); } while (0)
void HSD_TObjRemoveAnimAll(HSD_TObj*); void HSD_TObjAddAnimAll(HSD_TObj*,HSD_TexAnim*); void HSD_TObjReqAnimAllByFlags(HSD_TObj*,float,u32);
void HSD_TObjAnimAll(HSD_TObj*); HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc*); void HSD_TObjRemoveAll(HSD_TObj*); void HSD_TObjAddNext(HSD_TObj*,HSD_TObj*);
s32 HSD_TObjAssignResources(HSD_TObj*); void HSD_TObjSetupVolatileTev(HSD_TObj*,u32); void HSD_TObjSetup(HSD_TObj*); void HSD_TObjSetupTextureCoordGen(HSD_TObj*);
void HSD_StateInitTev(void); void HSD_SetMaterialColor(GXColor,GXColor,GXColor,float); void HSD_SetMaterialShininess(float); void HSD_SetupRenderModeWithCustomPE(u32,HSD_PEDesc*);
static HSD_ClassInfo* default_class; static HSD_MObj* current_mobj;
HSD_TObj *tobj_toon, *tobj_shadows;
static void MObjInfoInit(void);
HSD_MObjInfo hsdMObj = { MObjInfoInit };
typedef char MObjSizeCheck[sizeof(HSD_MObj)==0x20?1:-1];
typedef char MObjInfoSizeCheck[sizeof(HSD_MObjInfo)==0x54?1:-1];
static inline float clamp01(float v) { return v <= 0.0F ? 0.0F : v >= 1.0F ? 1.0F : v; }
static inline u8 material_byte(float v) { v = clamp01(v); return (u8)(v * 255.0F); }
#define TEX_COORD_UV 0
#define TEX_COORD_REFLECTION 1
#define TEX_COORD_HILIGHT 2
#define TEX_COORD_SHADOW 3
#define TEX_COORD_TOON 4
#define TEX_COORD_GRADATION 5
#define TEX_COORD_BACKLIGHT 6
#define TEX_COORD_MASK (0x0f)
#define tobj_coord(T) ((T)->flags & TEX_COORD_MASK)
#define TEX_LIGHTMAP_DIFFUSE (0x1 << 4)
#define TEX_LIGHTMAP_SPECULAR (0x1 << 5)
#define TEX_LIGHTMAP_AMBIENT (0x1 << 6)
#define TEX_LIGHTMAP_EXT (0x1 << 7)
#define TEX_LIGHTMAP_SHADOW (0x1 << 8)
#define TEX_LIGHTMAP_MASK                                                     \
static inline HSD_MObj* HSD_MObjAlloc(void);
static inline HSD_Material* HSD_MaterialAlloc(void);
static inline HSD_MObj* HSD_MObjAlloc(void);
static inline HSD_Material* HSD_MaterialAlloc(void);
static void MObjInfoInit(void);
static void MObjAmnesia(HSD_ClassInfo* info);
static void MObjRelease(HSD_Class* o);
void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj);
void HSD_MObjAddShadowTexture(HSD_TObj* tobj);
void HSD_MObjRemove(HSD_MObj* mobj);
void HSD_MObjAddTObjNext(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TObj* next);
void HSD_MObjAddTObj(HSD_MObj* mobj, HSD_TObj* tobj);
HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj);
void HSD_MObjSetAlpha(HSD_MObj* mobj, f32 alpha);
void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode);
void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode);
static void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2);
void HSD_MObjCompileTev(HSD_MObj* mobj);
static HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list);
HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc);
void HSD_MObjSetDefaultClass(HSD_ClassInfo* info);
static int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc);
void HSD_MObjAnim(HSD_MObj* mobj);
static void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);
void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags);
void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim);
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags);
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags);
u32 HSD_MObjGetFlags(HSD_MObj* mobj);
void HSD_MObjSetCurrent(HSD_MObj* mobj);


static inline HSD_MObj* HSD_MObjAlloc(void)
{
    HSD_MObj* mobj =
        hsdNew(default_class != NULL ? default_class : &hsdMObj.parent);
    HSD_ASSERT(1098, mobj);
    return mobj;
}

static inline HSD_Material* HSD_MaterialAlloc(void)
{
    HSD_Material* mat = hsdAllocMemPiece(sizeof(HSD_Material));
    HSD_ASSERT(1126, mat);
    memset(mat, 0, sizeof(HSD_Material));
    mat->alpha = 1.0F;
    return mat;
}

static void MObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdMObj), HSD_CLASS_INFO(&hsdClass),
                     "sysdolphin_base_library", "hsd_mobj",
                     sizeof(HSD_MObjInfo), sizeof(HSD_MObj));

    HSD_CLASS_INFO(&hsdMObj)->release = MObjRelease;
    HSD_CLASS_INFO(&hsdMObj)->amnesia = MObjAmnesia;
    HSD_MOBJ_INFO(&hsdMObj)->setup = HSD_MObjSetup;
    HSD_MOBJ_INFO(&hsdMObj)->unset = HSD_MObjUnset;
    HSD_MOBJ_INFO(&hsdMObj)->load = MObjLoad;
    HSD_MOBJ_INFO(&hsdMObj)->make_texp = MObjMakeTExp;
    HSD_MOBJ_INFO(&hsdMObj)->setup_tev = MObjSetupTev;
    HSD_MOBJ_INFO(&hsdMObj)->update = MObjUpdateFunc;
}

static void MObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdMObj)) {
        tobj_toon = NULL;
        tobj_shadows = NULL;
    }
    HSD_PARENT_INFO(&hsdMObj)->amnesia(info);
}

static void MObjRelease(HSD_Class* o)
{
    HSD_MObj* mobj = HSD_MOBJ(o);

    HSD_AObjRemove(mobj->aobj);
    hsdFreeMemPiece(mobj->mat, sizeof(HSD_Material));
    HSD_TObjRemoveAll(mobj->tobj);

    if (mobj->tevdesc != NULL) {
        HSD_TExpFreeTevDesc(mobj->tevdesc);
    }
    if (mobj->texp != NULL) {
        HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
    }
    if (mobj->pe != NULL) {
        hsdFreeMemPiece(mobj->pe, sizeof(HSD_PEDesc));
    }
    HSD_PARENT_INFO(&hsdMObj)->release(o);
}

void HSD_MObjDeleteShadowTexture(HSD_TObj* tobj)
{
    if (tobj != NULL) {
        HSD_TObj** cur = &tobj_shadows;
        while (*cur != NULL) {
            if (*cur == tobj) {
                *cur = tobj->next;
                tobj->next = NULL;
                return;
            }
            cur = &(*cur)->next;
        }
    } else {
        HSD_TObj* next;
        for (next = NULL; tobj_shadows != NULL; tobj_shadows = next) {
            next = tobj_shadows->next;
            tobj_shadows->next = NULL;
        }
    }
}

void HSD_MObjAddShadowTexture(HSD_TObj* tobj)
{
    HSD_TObj* cur;
    HSD_ASSERT(1173, tobj);
    for (cur = tobj_shadows; cur != NULL; cur = cur->next) {
        if (cur == tobj) {
            return;
        }
    }
    tobj->next = tobj_shadows;
    tobj_shadows = tobj;
}

void HSD_MObjRemove(HSD_MObj* mobj)
{
    if (mobj != NULL) {
        HSD_CLASS_METHOD(mobj)->release((HSD_Class*) mobj);
        HSD_CLASS_METHOD(mobj)->destroy((HSD_Class*) mobj);
    }
}

void HSD_MObjAddTObjNext(HSD_MObj* mobj, HSD_TObj* tobj, HSD_TObj* next) { if (mobj == NULL || tobj == NULL || next == NULL) return; HSD_TObjAddNext(tobj, next); }

void HSD_MObjAddTObj(HSD_MObj* mobj, HSD_TObj* tobj) { if (mobj == NULL || tobj == NULL) return; tobj->next = mobj->tobj; mobj->tobj = tobj; }

HSD_TObj* HSD_MObjGetTObj(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return NULL;
    }
    return mobj->tobj;
}

void HSD_MObjSetAlpha(HSD_MObj* mobj, float alpha) { if (!mobj || !mobj->mat) return; MOBJ_MAT(mobj)->alpha = alpha; }

void HSD_MObjUnset(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObjSetup(NULL);
}

void HSD_MObjSetup(HSD_MObj* mobj, u32 rendermode)
{
    HSD_TObj *tobj, **tail;

    HSD_StateInitTev();
    rendermode = mobj->rendermode;
    HSD_SetMaterialColor(MOBJ_MAT(mobj)->ambient, MOBJ_MAT(mobj)->diffuse,
                         MOBJ_MAT(mobj)->specular, MOBJ_MAT(mobj)->alpha);
    if (rendermode & RENDER_SPECULAR) {
        HSD_SetMaterialShininess(MOBJ_MAT(mobj)->shininess);
    }

    tobj = mobj->tobj;
    tail = NULL;

    if ((rendermode & RENDER_SHADOW) && tobj_shadows != NULL) {
        tail = &tobj;
        while (*tail != NULL) {
            tail = &(*tail)->next;
        }
        *tail = tobj_shadows;
    }
    if ((rendermode & RENDER_TOON) && tobj_toon != NULL &&
        tobj_toon->imagedesc != NULL)
    {
        tobj_toon->next = tobj;
        tobj = tobj_toon;
    }
    HSD_TObjSetup(tobj);
    HSD_TObjSetupTextureCoordGen(tobj);
    HSD_MOBJ_METHOD(mobj)->setup_tev(mobj, tobj, rendermode);
    HSD_SetupRenderModeWithCustomPE(rendermode, mobj->pe);
    if (tail != NULL) {
        *tail = NULL;
    }
}

static void MObjSetupTev(HSD_MObj* mobj, HSD_TObj* tobj, u32 arg2)
{
    HSD_ASSERT(798, mobj->tevdesc);
    HSD_TExpSetupTev(mobj->tevdesc, mobj->texp);
    HSD_TObjSetupVolatileTev(tobj, arg2);
}

void HSD_MObjCompileTev(HSD_MObj* mobj)
{
    HSD_TObj *tobj, **tail;
    HSD_TExp* texp;

    tail = NULL;
    if (mobj != NULL) {
        if (mobj->tevdesc != NULL) {
            HSD_TExpFreeTevDesc(mobj->tevdesc);
            mobj->tevdesc = NULL;
        }
        if (mobj->texp != NULL) {
            HSD_TExpFreeList(mobj->texp, HSD_TE_ALL, 1);
            mobj->texp = NULL;
        }
        tobj = mobj->tobj;
        if (mobj->rendermode & RENDER_SHADOW) {
            if (tobj_shadows != NULL) {
                tail = &tobj;
                while (*tail != NULL) {
                    tail = &(*tail)->next;
                }
                *tail = tobj_shadows;
            }
        }
        if (mobj->rendermode & RENDER_TOON) {
            if (tobj_toon != NULL && tobj_toon->imagedesc != NULL) {
                tobj_toon->next = tobj;
                tobj = tobj_toon;
            }
        }
        HSD_TObjAssignResources(tobj);
        texp = HSD_MOBJ_METHOD(mobj)->make_texp(mobj, tobj, (HSD_TExp**)&mobj->texp);
        HSD_TExpCompile(texp, (HSD_TExpTevDesc**)&mobj->tevdesc, (HSD_TExp**)&mobj->texp);
        if (tail != NULL) {
            *tail = NULL;
        }
    }
}

static HSD_TExp* MObjMakeTExp(HSD_MObj* mobj, HSD_TObj* tobj_top, HSD_TExp** list)
{
    HSD_TExp *diff, *spec, *ext, *alpha;
    HSD_TExp *exp, *exp_2, *exp_3;
    HSD_TObj *tobj, *tobj_2, *tobj_3, *tobj_4, *toon = NULL;
    u32 done = 0;
    int diffuse_mode, alpha_mode;
    static u8 one = 255;
    HSD_ASSERT(395, list);
    *list = NULL;
    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) toon = tobj;
    }
    diffuse_mode = mobj->rendermode & RENDER_DIFFUSE_BITS;
    if (diffuse_mode == 0) diffuse_mode = RENDER_DIFFUSE_MAT;
    alpha_mode = mobj->rendermode & RENDER_ALPHA_BITS;
    if (alpha_mode == 0) alpha_mode = diffuse_mode << RENDER_ALPHA_SHIFT;
    exp = HSD_TExpTev(list);
    if (mobj->rendermode & RENDER_DIFFUSE) {
        switch (diffuse_mode) {
        case RENDER_DIFFUSE_VTX:
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_1, HSD_TEXP_ZERO);
            break;
        default: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
            break;
        } }
        switch (alpha_mode) {
        case RENDER_ALPHA_VTX: {
            HSD_TExp* cnst = HSD_TExpCnst(&one, HSD_TE_X, HSD_TE_U8, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        }
        default: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        } }
    } else {
        switch (diffuse_mode) {
        case RENDER_DIFFUSE_MAT: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
            break;
        }
        case RENDER_DIFFUSE_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, toon ? HSD_TEXP_TEX : HSD_TEXP_RAS);
            break;
        default: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->diffuse, HSD_TE_RGB, HSD_TE_U8, list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp, HSD_TE_RGB, toon ? HSD_TEXP_TEX : HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, cnst);
            break;
        } }
        switch (alpha_mode) {
        case RENDER_ALPHA_MAT: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_X, cnst);
            break;
        }
        case RENDER_ALPHA_VTX:
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS);
            break;
        default: {
            HSD_TExp* cnst = HSD_TExpCnst(&MOBJ_MAT(mobj)->alpha, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpOrder(exp, toon, GX_COLOR0A0);
            HSD_TExpAlphaOp(exp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS, HSD_TE_X, cnst, HSD_TE_0, HSD_TEXP_ZERO);
            break;
        } }
    }
    diff = exp;
    alpha = exp;
    for (tobj_2 = tobj_top; tobj_2 != NULL; tobj_2 = tobj_2->next) {
        if ((tobj_2->flags & (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT)) &&
            tobj_2->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(tobj_2)->make_texp(
                tobj_2, (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT), done,
                &diff, &alpha, list);
        }
    }
    done |= (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_AMBIENT);

    if (mobj->rendermode & RENDER_DIFFUSE) {
        diffuse_mode = alpha_mode & RENDER_ALPHA_VTX;
        if (diffuse_mode) {
            exp_2 = HSD_TExpTev(list);
            HSD_TExpOrder(exp_2, NULL, GX_COLOR1A1);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
            diff = exp_2;
            alpha = exp_2;
        }
        exp_2 = HSD_TExpTev(list);
        if (toon != NULL) {
            HSD_TExpOrder(exp_2, toon, GX_COLOR0A0);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_TEX, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpOrder(exp_2, NULL, GX_COLOR0A0);
            HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff,
                            HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        diff = exp_2;
        if (diffuse_mode) {
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, alpha, HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        } else {
            HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
            HSD_TExpAlphaIn(exp_2, HSD_TE_A, alpha, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        }
        alpha = exp_2;
    }

    if (mobj->rendermode & RENDER_SPECULAR) {
        HSD_TExp* cnst =
            HSD_TExpCnst(&MOBJ_MAT(mobj)->specular, HSD_TE_RGB, HSD_TE_U8, list);
        exp_3 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        cnst);
        spec = exp_3;

        for (tobj_3 = tobj_top; tobj_3 != NULL; tobj_3 = tobj_3->next) {
            if ((tobj_3->flags & TEX_LIGHTMAP_SPECULAR) &&
                tobj_3->id != GX_TEXMAP_NULL)
            {
                HSD_TOBJ_METHOD(tobj_3)->make_texp(
                    tobj_3, TEX_LIGHTMAP_SPECULAR, done, &spec, &alpha, list);
            }
        }
        done |= TEX_LIGHTMAP_SPECULAR;

        exp_3 = HSD_TExpTev(list);
        HSD_TExpOrder(exp_3, NULL, GX_COLOR1A1);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, spec,
                        HSD_TE_RGB, HSD_TEXP_RAS, HSD_TE_0, HSD_TEXP_ZERO);
        spec = exp_3;

        exp_3 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_3, HSD_TE_RGB, spec, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, diff);
        diff = exp_3;
    }

    ext = diff;

    for (tobj_4 = tobj_top; tobj_4 != NULL; tobj_4 = tobj_4->next) {
        if ((tobj_4->flags & TEX_LIGHTMAP_EXT) && tobj_4->id != GX_TEXMAP_NULL)
        {
            HSD_TOBJ_METHOD(tobj_4)->make_texp(tobj_4, TEX_LIGHTMAP_EXT, done,
                                               &ext, &alpha, list);
        }
    }

    if (ext != alpha || HSD_TExpGetType(ext) != HSD_TE_TEV ||
        HSD_TExpGetType(alpha) != HSD_TE_TEV)
    {
        exp_2 = HSD_TExpTev(list);
        HSD_TExpColorOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpColorIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB,
                        ext);
        HSD_TExpAlphaOp(exp_2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                        GX_ENABLE);
        HSD_TExpAlphaIn(exp_2, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                        alpha);
        return exp_2;
    }

    return ext;
}

HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name ||
            !(info = hsdSearchClassInfo(mobjdesc->class_name)))
        {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            HSD_ASSERT(373, mobj);
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}

void HSD_MObjSetDefaultClass(HSD_ClassInfo* info) { if (info) { HSD_ASSERT(334, hsdIsDescendantOf(info, &hsdMObj)); } default_class = info; }

static int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

void HSD_MObjAnim(HSD_MObj* mobj)
{
    if (mobj == NULL) {
        return;
    }
    HSD_AObjInterpretAnim(mobj->aobj, mobj, HSD_MOBJ_METHOD(mobj)->update);
    HSD_TObjAnimAll(mobj->tobj);
}

static void MObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_MObj* mobj = obj;

    if (mobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_M_AMBIENT_R:
        if (mobj->mat) MOBJ_MAT(mobj)->ambient.r = material_byte(val->fv);
        break;
    case HSD_A_M_AMBIENT_G:
        if (mobj->mat) MOBJ_MAT(mobj)->ambient.g = material_byte(val->fv);
        break;
    case HSD_A_M_AMBIENT_B:
        if (mobj->mat) MOBJ_MAT(mobj)->ambient.b = material_byte(val->fv);
        break;
    case HSD_A_M_DIFFUSE_R:
        if (mobj->mat) MOBJ_MAT(mobj)->diffuse.r = material_byte(val->fv);
        break;
    case HSD_A_M_DIFFUSE_G:
        if (mobj->mat) MOBJ_MAT(mobj)->diffuse.g = material_byte(val->fv);
        break;
    case HSD_A_M_DIFFUSE_B:
        if (mobj->mat) MOBJ_MAT(mobj)->diffuse.b = material_byte(val->fv);
        break;
    case HSD_A_M_ALPHA:
        if (mobj->mat) MOBJ_MAT(mobj)->alpha = clamp01(1.0F - val->fv);
        break;
    case HSD_A_M_SPECULAR_R:
        if (mobj->mat) MOBJ_MAT(mobj)->specular.r = material_byte(val->fv);
        break;
    case HSD_A_M_SPECULAR_G:
        if (mobj->mat) MOBJ_MAT(mobj)->specular.g = material_byte(val->fv);
        break;
    case HSD_A_M_SPECULAR_B:
        if (mobj->mat) MOBJ_MAT(mobj)->specular.b = material_byte(val->fv);
        break;
    case HSD_A_M_PE_REF0:
        if (mobj->pe) {
            MOBJ_PE(mobj)->ref0 = material_byte(val->fv);
        }
        break;
    case HSD_A_M_PE_REF1:
        if (mobj->pe) {
            MOBJ_PE(mobj)->ref1 = material_byte(val->fv);
        }
        break;
    case HSD_A_M_PE_DSTALPHA:
        if (mobj->pe) {
            MOBJ_PE(mobj)->dst_alpha = material_byte(val->fv);
        }
        break;
    }
}

void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL) {
        return;
    }
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL) {
        return;
    }

    if (matanim != NULL) {
        if (mobj->aobj != NULL) {
            HSD_AObjRemove(mobj->aobj);
        }
        mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
    }
}

void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj == NULL) {
        return;
    }

    if (flags & MOBJ_ANIM) {
        HSD_AObjRemove(mobj->aobj);
        mobj->aobj = NULL;
    }
    if (flags & TOBJ_ANIM) {
        HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}

void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode &= ~flags;
    }
}

void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode |= flags;
    }
}

u32 HSD_MObjGetFlags(HSD_MObj* mobj) { return mobj ? mobj->rendermode : 0; }

void HSD_MObjSetCurrent(HSD_MObj* mobj)
{
    current_mobj = mobj;
}
