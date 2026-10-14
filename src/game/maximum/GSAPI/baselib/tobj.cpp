/* XD texture animation and descriptor lifecycle. */
#include "game/maximum/GSAPI/baselib/tobj.h"
typedef char tobj_repeat_s_offset_check[(unsigned long)&((HSD_TObj*)0)->repeat_s == 0x48 ? 1 : -1];
typedef char tobj_imagetbl_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->imagetbl == 0x68 ? 1 : -1];
typedef char tobj_tluttbl_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->tluttbl == 0x6C ? 1 : -1];
typedef char tobj_tlut_no_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->tlut_no == 0x70 ? 1 : -1];
typedef char tobj_mtx_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->mtx == 0x74 ? 1 : -1];
typedef char tobj_coord_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->coord == 0xA4 ? 1 : -1];
typedef char tobj_tev_offset_check[(unsigned long)&((HSD_TObjRuntime*)0)->tev == 0xA8 ? 1 : -1];
typedef char TObjRuntimeSizeCheck[sizeof(HSD_TObjRuntime) == 0xAC ? 1 : -1];
typedef char TObjPrefixSizeCheck[sizeof(HSD_TObj) == 0x68 ? 1 : -1];
typedef char TObjTevSizeCheck[sizeof(HSD_TObjTev) == 0x20 ? 1 : -1];
#define TEX_MTX_DIRTY (1U << 31)
#include "game/maximum/GSAPI/baselib/texp.h"
/* XD stores the animation ID in the two bytes after wrap repeat counts. */
typedef struct HSD_TObjPackedRepeat { unsigned char repeat_s,repeat_t; unsigned short anim_id; } HSD_TObjPackedRepeat;
#define TOBJ_PACKED(o) ((HSD_TObjPackedRepeat*)&(o)->repeat_s)
#define TOBJ_TEV_CC_KONST_RGB (0x01 << 7 | 0)
#define TOBJ_TEV_CC_KONST_RRR (0x01 << 7 | 1)
#define TOBJ_TEV_CC_KONST_GGG (0x01 << 7 | 2)
#define TOBJ_TEV_CC_KONST_BBB (0x01 << 7 | 3)
#define TOBJ_TEV_CC_KONST_AAA (0x01 << 7 | 4)
#define TOBJ_TEV_CC_TEX0_RGB (0x01 << 7 | 5)
#define TOBJ_TEV_CC_TEX0_AAA (0x01 << 7 | 6)
#define TOBJ_TEV_CC_TEX1_RGB (0x01 << 7 | 7)
#define TOBJ_TEV_CC_TEX1_AAA (0x01 << 7 | 8)

#define TOBJ_TEV_CA_KONST_R (0x01 << 6 | 0)
#define TOBJ_TEV_CA_KONST_G (0x01 << 6 | 1)
#define TOBJ_TEV_CA_KONST_B (0x01 << 6 | 2)
#define TOBJ_TEV_CA_KONST_A (0x01 << 6 | 3)
#define TOBJ_TEV_CA_TEX0_A (0x01 << 6 | 4)
#define TOBJ_TEV_CA_TEX1_A (0x01 << 6 | 5)

#define TOBJ_TEVREG_ACTIVE_KONST_R (0x01 << 0)
#define TOBJ_TEVREG_ACTIVE_KONST_G (0x01 << 1)
#define TOBJ_TEVREG_ACTIVE_KONST_B (0x01 << 2)
#define TOBJ_TEVREG_ACTIVE_KONST_A (0x01 << 3)
#define TOBJ_TEVREG_ACTIVE_KONST                                              \
    (TOBJ_TEVREG_ACTIVE_KONST_R | TOBJ_TEVREG_ACTIVE_KONST_G |                \
     TOBJ_TEVREG_ACTIVE_KONST_B | TOBJ_TEVREG_ACTIVE_KONST_A)
#define TOBJ_TEVREG_ACTIVE_TEV0_R (0x01 << 4)
#define TOBJ_TEVREG_ACTIVE_TEV0_G (0x01 << 5)
#define TOBJ_TEVREG_ACTIVE_TEV0_B (0x01 << 6)
#define TOBJ_TEVREG_ACTIVE_TEV0_A (0x01 << 7)
#define TOBJ_TEVREG_ACTIVE_TEV0                                               \
    (TOBJ_TEVREG_ACTIVE_TEV0_R | TOBJ_TEVREG_ACTIVE_TEV0_G |                  \
     TOBJ_TEVREG_ACTIVE_TEV0_B | TOBJ_TEVREG_ACTIVE_TEV0_A)
#define TOBJ_TEVREG_ACTIVE_TEV1_R (0x01 << 8)
#define TOBJ_TEVREG_ACTIVE_TEV1_G (0x01 << 9)
#define TOBJ_TEVREG_ACTIVE_TEV1_B (0x01 << 10)
#define TOBJ_TEVREG_ACTIVE_TEV1_A (0x01 << 11)
#define TOBJ_TEVREG_ACTIVE_TEV1                                               \
    (TOBJ_TEVREG_ACTIVE_TEV1_R | TOBJ_TEVREG_ACTIVE_TEV1_G |                  \
     TOBJ_TEVREG_ACTIVE_TEV1_B | TOBJ_TEVREG_ACTIVE_TEV1_A)
#define TOBJ_TEVREG_ACTIVE_COLOR_TEV (0x01 << 30)
#define TOBJ_TEVREG_ACTIVE_ALPHA_TEV (0x01U << 31)

#define TEX_COORD_UV 0
#define TEX_COORD_REFLECTION 1
#define TEX_COORD_HILIGHT 2
#define TEX_COORD_SHADOW 3
#define TEX_COORD_TOON 4
#define TEX_COORD_GRADATION 5
#define TEX_COORD_BACKLIGHT 6
#define TEX_COORD_MASK (0x0f)
#define tobj_coord(T) ((T)->flags & TEX_COORD_MASK)

#define TEX_COLORMAP_NONE (0 << 16)
#define TEX_COLORMAP_ALPHA_MASK (1 << 16)
#define TEX_COLORMAP_RGB_MASK (2 << 16)
#define TEX_COLORMAP_BLEND (3 << 16)
#define TEX_COLORMAP_MODULATE (4 << 16)
#define TEX_COLORMAP_REPLACE (5 << 16)
#define TEX_COLORMAP_PASS (6 << 16)
#define TEX_COLORMAP_ADD (7 << 16)
#define TEX_COLORMAP_SUB (8 << 16)
#define TEX_COLORMAP_MASK (0x0f << 16)
#define tobj_colormap(T) ((T)->flags & TEX_COLORMAP_MASK)

#define TEX_ALPHAMAP_NONE (0 << 20)
#define TEX_ALPHAMAP_ALPHA_MASK (1 << 20)
#define TEX_ALPHAMAP_BLEND (2 << 20)
#define TEX_ALPHAMAP_MODULATE (3 << 20)
#define TEX_ALPHAMAP_REPLACE (4 << 20)
#define TEX_ALPHAMAP_PASS (5 << 20)
#define TEX_ALPHAMAP_ADD (6 << 20)
#define TEX_ALPHAMAP_SUB (7 << 20)
#define TEX_ALPHAMAP_MASK (0x0f << 20)
#define tobj_alphamap(T) ((T)->flags & TEX_ALPHAMAP_MASK)

#define TEX_LIGHTMAP_DIFFUSE (0x1 << 4)
#define TEX_LIGHTMAP_SPECULAR (0x1 << 5)
#define TEX_LIGHTMAP_AMBIENT (0x1 << 6)
#define TEX_LIGHTMAP_EXT (0x1 << 7)
#define TEX_LIGHTMAP_SHADOW (0x1 << 8)
#define TEX_LIGHTMAP_MASK                                                     \
    (TEX_LIGHTMAP_DIFFUSE | TEX_LIGHTMAP_SPECULAR | TEX_LIGHTMAP_AMBIENT |    \
     TEX_LIGHTMAP_EXT | TEX_LIGHTMAP_SHADOW)
#define tobj_lightmap(T) ((T)->flags & TEX_LIGHTMAP_MASK)

#define TEX_BUMP (0x1 << 24)
#define tobj_bump(T) ((T)->flags & TEX_BUMP)

HSD_LObj* HSD_LObjGetCurrentByType(unsigned int);
HSD_CObj* HSD_CObjGetCurrent(void);
int HSD_CObjGetProjectionType(HSD_CObj*);
void C_MTXLightPerspective(HSD_Mtx,float,float,float,float,float,float);
void C_MTXLightFrustum(HSD_Mtx,float,float,float,float,float,float,float,float,float);
void C_MTXLightOrtho(HSD_Mtx,float,float,float,float,float,float,float,float);
static inline float (*HSD_CObjGetViewingMtxPtrDirect(HSD_CObj* cobj))[4] { return cobj->view_mtx; }
float (*HSD_CObjGetInvViewingMtxPtrDirect(HSD_CObj*))[4];
void HSD_LObjGetLightVector(HSD_LObj*,HSD_Vec3*);
void PSMTXMultVecSR(HSD_Mtx,HSD_Vec3*,HSD_Vec3*);
void PSVECNormalize(HSD_Vec3*,HSD_Vec3*);
unsigned int HSD_LObjGetLightMaskDiffuse(void);
unsigned int HSD_StateAssignTev(void);
void HSD_SetupTevStage(HSD_TevDesc*);
void HSD_StateRegisterTexGen(int);
static void TObjSetupMtx(HSD_TObj* tobj);
static inline void setupTextureCoordGen(HSD_TObj* tobj);
static inline void setupTextureCoordGenBump(HSD_TObj* bump);
static inline void setupTextureCoordGenToon(HSD_TObj* toon);
void HSD_TObjSetupTextureCoordGen(HSD_TObj* tobj);
static inline void TObjSetupTevModulateShadow(HSD_TObj* shadow);
static inline void SetupEmbossBumpTev(HSD_TObj* bump);
void HSD_TObjSetupVolatileTev(HSD_TObj* tobj, u32 rendermode);
static inline int DifferentTluts(HSD_Tlut* t0, HSD_Tlut* t1);
void HSD_TObjSetup(HSD_TObj* tobj);
static inline GXTexGenSrc HSD_TexCoordID2TexGenSrc(GXTexCoordID coord);

void OSReport(const char*,...);
double __fabs(double);
#define fabsf(value) ((float)__fabs(value))
void PSMTXTrans(HSD_Mtx,float,float,float);
void PSMTXScale(HSD_Mtx,float,float,float);
void PSMTXConcat(HSD_Mtx,HSD_Mtx,HSD_Mtx);
static void MakeColorGenTExp(u32 lightmap, HSD_TObj* tobj, HSD_TExp** c,
                             HSD_TExp** a, HSD_TExp** list, int repeat);
static void TObjMakeTExp(HSD_TObj* tobj, u32 lightmap, u32 lightmap_done,
                         HSD_TExp** c, HSD_TExp** a, HSD_TExp** list);
s32 HSD_TObjAssignResources(HSD_TObj* tobj_top);
static inline u32 HSD_TexMapID2PTTexMtx(GXTexMapID id);
static inline GXTexMapID HSD_Index2TexMap(u32 index);
static inline GXTexCoordID HSD_Index2TexCoord(u32 index);
GXTexMtx HSD_Index2TexMtx(u32 index);
static void MakeTextureMtx(HSD_TObj* tobj);
#define FILE_NAME "tobj.c"
void* hsdAllocMemPiece(int);
void __assert(const char*,int,const char*);
typedef int bool;
#define false 0
#define true 1
void HSD_Panic(const char*, int, const char*);
void* memcpy(void*, const void*, unsigned long);
void* memset(void*, int, unsigned long);
#define HSD_ASSERT(line, cond) do { if (!(cond)) __assert(FILE_NAME, line, #cond); } while (0)

typedef int enum_t;

void HSD_Free(void*); void* HSD_Alloc(int); void hsdFreeMemPiece(void*,int);

HSD_TObj* HSD_TObjAlloc(void);
static HSD_TObjInfo* default_class;
HSD_TObj* tobj_head;
static void TObjInfoInit(void);
static int TObjInit(HSD_Class*);
static void TObjRelease(HSD_Class*);
static void TObjAmnesia(HSD_ClassInfo*);
HSD_TObjInfo hsdTObj = { TObjInfoInit };
extern HSD_ClassInfo hsdObj;

#define TOBJ_ANIM 0x10
#define GX_IDENTITY 60
#define HSD_A_T_TIMG 1
#define HSD_A_T_TRAU 2
#define HSD_A_T_TRAV 3
#define HSD_A_T_SCAU 4
#define HSD_A_T_SCAV 5
#define HSD_A_T_ROTX 6
#define HSD_A_T_ROTY 7
#define HSD_A_T_ROTZ 8
#define HSD_A_T_BLEND 9
#define HSD_A_T_TCLT 10
#define HSD_A_T_LOD_BIAS 11
#define HSD_A_T_KONST_R 12
#define HSD_A_T_KONST_G 13
#define HSD_A_T_KONST_B 14
#define HSD_A_T_KONST_A 15
#define HSD_A_T_TEV0_R 16
#define HSD_A_T_TEV0_G 17
#define HSD_A_T_TEV0_B 18
#define HSD_A_T_TEV0_A 19
#define HSD_A_T_TEV1_R 20
#define HSD_A_T_TEV1_G 21
#define HSD_A_T_TEV1_B 22
#define HSD_A_T_TEV1_A 23
#define HSD_A_T_TS_BLEND 24
void HSD_TObjRemoveAnim(HSD_TObj* tobj);
void HSD_TObjRemoveAnimAll(HSD_TObj* tobj);
static HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim);
void HSD_TObjAddAnim(HSD_TObj* tobj, HSD_TexAnim* texanim);
void HSD_TObjAddAnimAll(HSD_TObj* tobj, HSD_TexAnim* texanim);
void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags);
void HSD_TObjReqAnimAllByFlags(HSD_TObj* tobj, f32 startframe, u32 flags);
void HSD_TObjReqAnim(HSD_TObj* tobj, f32 startframe);
static void TObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val);
void HSD_TObjAnim(HSD_TObj* tobj);
void HSD_TObjAnimAll(HSD_TObj* tobj);
static int TObjLoad(HSD_TObj* tobj, HSD_TObjDesc* td);
HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc* td);
HSD_Tlut* HSD_TlutLoadDesc(HSD_TlutDesc* tlutdesc);
HSD_TObjTev* HSD_TObjTevLoadDesc(HSD_TObjTevDesc* tevdesc);
HSD_TObj* _HSD_TObjGetCurrentByType(HSD_TObj* from, u32 mapping);
void HSD_TObjRemove(HSD_TObj* tobj);
void HSD_TObjRemoveAll(HSD_TObj* tobj);
void HSD_TObjFree(HSD_TObj* tobj);
void HSD_TlutFree(HSD_Tlut* tlut);
void HSD_TlutRemove(HSD_Tlut* tlut);
void HSD_TObjTevFree(HSD_TObjTev* tev);
void HSD_TObjTevRemove(HSD_TObjTev* tev);
void HSD_ImageDescFree(HSD_ImageDesc* idesc);

static inline float clamp_unit(float value);
static inline HSD_Tlut* HSD_TlutAlloc(void);
static inline HSD_TObjTev* HSD_TObjTevAlloc(void);
static inline HSD_TObjInfo* HSD_TObjGetDefaultClass(void);
static inline HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim);
static inline void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags);
static inline void HSD_TObjAnim(HSD_TObj* tobj);
static inline HSD_Tlut* HSD_TlutLoadDesc(HSD_TlutDesc* tlutdesc);
static inline HSD_TObjTev* HSD_TObjTevLoadDesc(HSD_TObjTevDesc* tevdesc);
static inline void HSD_TObjFree(HSD_TObj* tobj);
static inline void HSD_TlutFree(HSD_Tlut* tlut);
static inline void HSD_TlutRemove(HSD_Tlut* tlut);
static inline void HSD_TObjTevFree(HSD_TObjTev* tev);
static inline void HSD_TObjTevRemove(HSD_TObjTev* tev);
static void TObjRelease(HSD_Class* o);
static void TObjAmnesia(HSD_ClassInfo* info);
HSD_TObj* HSD_TObjAlloc(void);
HSD_ImageDesc* HSD_ImageDescAlloc(void);
static int TObjInit(HSD_Class* o);
void HSD_ImageDescRemove(HSD_ImageDesc* idesc);
void HSD_TObjAddNext(HSD_TObj* tobj, HSD_TObj* next);

static inline float clamp_unit(float value) {
    return value <= 0.0F ? 0.0F : value >= 1.0F ? 1.0F : value;
}

static inline u8 Float2Color(float value) {
    float clamped;
    if (value <= 0.0F) clamped = 0.0F;
    else if (value >= 1.0F) clamped = 1.0F;
    else clamped = value;
    return 255.0F * clamped;
}

static inline HSD_Tlut* HSD_TlutAlloc(void) {
    HSD_Tlut* tlut = hsdAllocMemPiece(sizeof(HSD_Tlut));
    HSD_ASSERT(2204, tlut);
    memset(tlut, 0, sizeof(HSD_Tlut));
    return tlut;
}

static inline HSD_TObjTev* HSD_TObjTevAlloc(void) {
    HSD_TObjTev* tev = hsdAllocMemPiece(sizeof(HSD_TObjTev));
    HSD_ASSERT(2247, tev);
    memset(tev, 0, sizeof(HSD_TObjTev));
    return tev;
}

static inline HSD_TObjInfo* HSD_TObjGetDefaultClass(void) { return default_class ? default_class : &hsdTObj; }

static inline HSD_TexAnim* lookupTextureAnim(s32 id, HSD_TexAnim* texanim)
{
    HSD_TexAnim* ta;
    for (ta = texanim; ta; ta = ta->next) {
        if (ta->id == (int) id) {
            return ta;
        }
    }
    return NULL;
}

static inline void HSD_TObjReqAnimByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    if (tobj != NULL) {
        if (flags & TOBJ_ANIM) {
            HSD_AObjReqAnim(tobj->aobj, startframe);
        }
    }
}

static inline void HSD_TObjAnim(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(tobj->aobj, tobj, HSD_TOBJ_METHOD(tobj)->update);
}

static inline HSD_Tlut* HSD_TlutLoadDesc(HSD_TlutDesc* tlutdesc)
{
    if (tlutdesc != NULL) {
        HSD_Tlut* tlut = HSD_TlutAlloc();
        memcpy(tlut, tlutdesc, sizeof(HSD_Tlut));
        return tlut;
    }
    return NULL;
}

static inline HSD_TObjTev* HSD_TObjTevLoadDesc(HSD_TObjTevDesc* tevdesc)
{
    if (tevdesc != NULL) {
        HSD_TObjTev* result = HSD_TObjTevAlloc();
        memcpy(result, tevdesc, sizeof(HSD_TObjTev));
        return result;
    }
    return NULL;
}

static inline void HSD_TObjFree(HSD_TObj* tobj)
{
    if (tobj) {
        HSD_CLASS_METHOD(tobj)->destroy((HSD_Class*) tobj);
    }
}

static inline void HSD_TlutFree(HSD_Tlut* tlut)
{
    hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
}

static inline void HSD_TlutRemove(HSD_Tlut* tlut)
{
    if (tlut) {
        hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
    }
}

static inline void HSD_TObjTevFree(HSD_TObjTev* tev)
{
    hsdFreeMemPiece(tev, sizeof(HSD_TObjTev));
}

static inline void HSD_TObjTevRemove(HSD_TObjTev* tev)
{
    if (tev) {
        HSD_TObjTevFree(tev);
    }
}

static inline u32 HSD_TexMapID2PTTexMtx(GXTexMapID id)
{
    switch (id) {
    case GX_TEXMAP0:
        return GX_PTTEXMTX0;
    case GX_TEXMAP1:
        return GX_PTTEXMTX1;
    case GX_TEXMAP2:
        return GX_PTTEXMTX2;
    case GX_TEXMAP3:
        return GX_PTTEXMTX3;
    case GX_TEXMAP4:
        return GX_PTTEXMTX4;
    case GX_TEXMAP5:
        return GX_PTTEXMTX5;
    case GX_TEXMAP6:
        return GX_PTTEXMTX6;
    case GX_TEXMAP7:
        return GX_PTTEXMTX7;
    default:
        HSD_Panic("tobj.c", 595, "unexpected texmap id.\n");
    }
    return 0;
}

static inline GXTexMapID HSD_Index2TexMap(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMAP0;
    case 1:
        return GX_TEXMAP1;
    case 2:
        return GX_TEXMAP2;
    case 3:
        return GX_TEXMAP3;
    case 4:
        return GX_TEXMAP4;
    case 5:
        return GX_TEXMAP5;
    case 6:
        return GX_TEXMAP6;
    case 7:
        return GX_TEXMAP7;
    default:
        HSD_ASSERT(2050, 0);
    }
    return GX_TEXMAP0;
}

static inline GXTexCoordID HSD_Index2TexCoord(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXCOORD0;
    case 1:
        return GX_TEXCOORD1;
    case 2:
        return GX_TEXCOORD2;
    case 3:
        return GX_TEXCOORD3;
    case 4:
        return GX_TEXCOORD4;
    case 5:
        return GX_TEXCOORD5;
    case 6:
        return GX_TEXCOORD6;
    case 7:
        return GX_TEXCOORD7;
    default:
        HSD_ASSERT(1935, 0);
    }
    return GX_TEXCOORD0;
}

static inline void setupTextureCoordGen(HSD_TObj* tobj)
{
    u32 mtxid;
    GXTexGenSrc src;

    switch (tobj_coord(tobj)) {
    case TEX_COORD_SHADOW:
        GXSetTexCoordGen2(TOBJ_EXT(tobj)->coord, GX_TG_MTX3x4, GX_TG_POS, GX_PNMTX0,
                          GX_DISABLE, tobj->mtxid);
        break;
    case TEX_COORD_REFLECTION:
    case TEX_COORD_HILIGHT:
    case TEX_COORD_GRADATION:
        GXSetTexCoordGen2(TOBJ_EXT(tobj)->coord, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0,
                          GX_ENABLE, tobj->mtxid);
        break;
    case TEX_COORD_BACKLIGHT:
        GXSetTexCoordGen2(TOBJ_EXT(tobj)->coord, GX_TG_MTX3x4, GX_TG_POS,
            GX_IDENTITY, GX_ENABLE, tobj->mtxid);
        break;
    default:
        if (tobj_bump(tobj)) {
            GXSetTexCoordGen(TOBJ_EXT(tobj)->coord, GX_TG_MTX2x4, tobj->src,
                             tobj->mtxid);
        } else {
            GXSetTexCoordGen2(TOBJ_EXT(tobj)->coord, GX_TG_MTX2x4, tobj->src,
                              GX_IDENTITY, GX_DISABLE, tobj->mtxid);
        }
    }
}

static inline void setupTextureCoordGenBump(HSD_TObj* bump)
{
    u32 mask;
    int i;
    static GXTexGenType func[] = {
        GX_TG_BUMP0, GX_TG_BUMP1, GX_TG_BUMP2, GX_TG_BUMP3,
        GX_TG_BUMP4, GX_TG_BUMP5, GX_TG_BUMP6, GX_TG_BUMP7,
    };

    mask = HSD_LObjGetLightMaskDiffuse();

    for (i = 0; i < 8; i++) {
        if (mask & (1 << i)) {
            break;
        }
    }
    if (i >= 8) {
        i = 0;
    }

    GXSetTexCoordGen((GXTexCoordID) (TOBJ_EXT(bump)->coord + 1), func[i],
                     HSD_TexCoordID2TexGenSrc(TOBJ_EXT(bump)->coord), GX_IDENTITY);
}

static inline void setupTextureCoordGenToon(HSD_TObj* toon)
{
    GXTexGenSrc src = toon->src;
    GXSetTexCoordGen(TOBJ_EXT(toon)->coord, GX_TG_SRTG, src, GX_IDENTITY);
}

static inline void TObjSetupTevModulateShadow(HSD_TObj* shadow)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE,  (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR_NULL, GX_TEV_ADD,          GX_CC_ZERO,
        GX_CC_CPREV,    GX_CC_TEXC,    GX_CC_ZERO,          GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,     GX_TEVPREV,          GX_TEV_ADD,
        GX_CA_ZERO,     GX_CA_ZERO,    GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,    GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR, GX_TEV_SWAP0, GX_TEV_SWAP0,
        (GXTevKColorSel) 0, (GXTevKAlphaSel) 0,
        GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA,
    };

    for (; shadow && tobj_coord(shadow) == TEX_COORD_SHADOW;
         shadow = shadow->next)
    {
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = TOBJ_EXT(shadow)->coord;
        tevdesc.map = shadow->id;
        HSD_SetupTevStage(&tevdesc);
    }
}

static inline void SetupEmbossBumpTev(HSD_TObj* bump)
{
    static HSD_TevDesc tevdesc = {
        NULL,           TEVCONF_MODE, (GXTevStageID) (-1), GX_TEXCOORD_NULL,
        GX_TEXMAP_NULL, GX_COLOR0A0,  GX_TEV_SUB,          GX_CC_ZERO,
        GX_CC_TEXC,     GX_CC_RASC,   GX_CC_CPREV,         GX_CS_SCALE_1,
        GX_TB_ZERO,     GX_ENABLE,    GX_TEVPREV,          GX_TEV_SUB,
        GX_CA_ZERO,     GX_CA_ZERO,   GX_CA_ZERO,          GX_CA_APREV,
        GX_CS_SCALE_1,  GX_TB_ZERO,   GX_ENABLE,           GX_TEVPREV,
        GX_TC_LINEAR, GX_TEV_SWAP0, GX_TEV_SWAP0,
        (GXTevKColorSel) 0, (GXTevKAlphaSel) 0,
        GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA,
    };

    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = TOBJ_EXT(bump)->coord;
    tevdesc.map = bump->id;
    tevdesc.u.tevconf.clr_op = GX_TEV_ADD;
    tevdesc.u.tevconf.alpha_op = GX_TEV_ADD;
    tevdesc.u.tevconf.clr_clamp = GX_DISABLE;
    HSD_SetupTevStage(&tevdesc);
    tevdesc.stage = HSD_StateAssignTev();
    tevdesc.coord = (GXTexCoordID) (TOBJ_EXT(bump)->coord + 1);
    tevdesc.u.tevconf.clr_op = GX_TEV_SUB;
    tevdesc.u.tevconf.alpha_op = GX_TEV_SUB;
    tevdesc.u.tevconf.clr_clamp = GX_ENABLE;
    HSD_SetupTevStage(&tevdesc);
}

static inline int DifferentTluts(HSD_Tlut* t0, HSD_Tlut* t1)
{
    int different = 1;
    if (t0->n_entries == t1->n_entries) different = 0;
    return different;
}

static inline GXTexGenSrc HSD_TexCoordID2TexGenSrc(GXTexCoordID coord)
{
    switch (coord) {
    case GX_TEXCOORD0:
        return GX_TG_TEXCOORD0;
    case GX_TEXCOORD1:
        return GX_TG_TEXCOORD1;
    case GX_TEXCOORD2:
        return GX_TG_TEXCOORD2;
    case GX_TEXCOORD3:
        return GX_TG_TEXCOORD3;
    case GX_TEXCOORD4:
        return GX_TG_TEXCOORD4;
    case GX_TEXCOORD5:
        return GX_TG_TEXCOORD5;
    case GX_TEXCOORD6:
        return GX_TG_TEXCOORD6;
    case GX_TEXCOORD7:
    default:
        HSD_ASSERT(1873, 0);
    }
    return GX_TG_TEXCOORD0;
}

void HSD_TObjRemoveAnim(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return;
    }

    HSD_AObjRemove(tobj->aobj);
    tobj->aobj = NULL;
}

void HSD_TObjRemoveAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjRemoveAnim(tp);
        }
    }
}

void HSD_TObjAddAnim(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    s32 i;
    HSD_TexAnim* ta;

    if (tobj != NULL) {
        if ((ta = lookupTextureAnim(TOBJ_PACKED(tobj)->anim_id, texanim)) != NULL) {
            if (tobj->aobj != NULL) {
                HSD_AObjRemove(tobj->aobj);
            }
            tobj->aobj = HSD_AObjLoadDesc(ta->aobjdesc);
            TOBJ_EXT(tobj)->imagetbl = ta->imagetbl;

            if (TOBJ_EXT(tobj)->tluttbl != NULL) {
                for (i = 0; TOBJ_EXT(tobj)->tluttbl[i]; i++) {
                    HSD_TlutRemove(TOBJ_EXT(tobj)->tluttbl[i]);
                }
                HSD_Free(TOBJ_EXT(tobj)->tluttbl);
            }

            if (ta->n_tluttbl) {
                TOBJ_EXT(tobj)->tluttbl = HSD_Alloc((s32) sizeof(HSD_Tlut*) *
                                             (ta->n_tluttbl + 1));
                for (i = 0; i < ta->n_tluttbl; i++) {
                    TOBJ_EXT(tobj)->tluttbl[i] = HSD_TlutLoadDesc(ta->tluttbl[i]);
                }
                TOBJ_EXT(tobj)->tluttbl[i] = NULL;
            } else {
                TOBJ_EXT(tobj)->tluttbl = NULL;
            }
            TOBJ_EXT(tobj)->tlut_no = -1;
        }
    }
}

void HSD_TObjAddAnimAll(HSD_TObj* tobj, HSD_TexAnim* texanim)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp; tp = tp->next) {
            HSD_TObjAddAnim(tp, texanim);
        }
    }
}

void HSD_TObjReqAnimAllByFlags(HSD_TObj* tobj, f32 startframe, u32 flags)
{
    HSD_TObj* tp;

    if (tobj != NULL) {
        for (tp = tobj; tp != NULL; tp = tp->next) {
            HSD_TObjReqAnimByFlags(tp, startframe, flags);
        }
    }
}

void HSD_TObjReqAnim(HSD_TObj* tobj, f32 startframe)
{
    HSD_TObjReqAnimByFlags(tobj, startframe, TOBJ_ANIM);
}

static void TObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_TObj* tobj = obj;

    if (tobj == NULL) {
        return;
    }

    switch (type) {
    case HSD_A_T_TIMG: {
        int n;
        if (!TOBJ_EXT(tobj)->imagetbl) __assert("tobj.c",278,"tobj->imagetbl");
        n = (int) val->fv;
        if (TOBJ_EXT(tobj)->imagetbl[n]) {
            tobj->imagedesc = TOBJ_EXT(tobj)->imagetbl[n];
        }
    } break;
    case HSD_A_T_TCLT: {
        if (TOBJ_EXT(tobj)->tluttbl) {
            TOBJ_EXT(tobj)->tlut_no = (u8) val->fv;
        }
    } break;
    case HSD_A_T_BLEND:
        tobj->blending = clamp_unit(val->fv);
        break;
    case HSD_A_T_ROTX:
        tobj->rotate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTY:
        tobj->rotate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_ROTZ:
        tobj->rotate.z = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAU:
        tobj->translate.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_TRAV:
        tobj->translate.y = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAU:
        tobj->scale.x = val->fv;
        goto mtxdirty;
    case HSD_A_T_SCAV:
        tobj->scale.y = val->fv;
        goto mtxdirty;
    mtxdirty:
        tobj->flags |= TEX_MTX_DIRTY;
        break;
    case HSD_A_T_LOD_BIAS:
        if (tobj->lod) ((HSD_TexLODDesc*)tobj->lod)->LODBias = val->fv;
        break;
    case HSD_A_T_KONST_R:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->konst.r = Float2Color(val->fv);
        break;
    case HSD_A_T_KONST_G:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->konst.g = Float2Color(val->fv);
        break;
    case HSD_A_T_KONST_B:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->konst.b = Float2Color(val->fv);
        break;
    case HSD_A_T_KONST_A:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->konst.a = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV0_R:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev0.r = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV0_G:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev0.g = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV0_B:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev0.b = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV0_A:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev0.a = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV1_R:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev1.r = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV1_G:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev1.g = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV1_B:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev1.b = Float2Color(val->fv);
        break;
    case HSD_A_T_TEV1_A:
        if (TOBJ_EXT(tobj)->tev) TOBJ_EXT(tobj)->tev->tev1.a = Float2Color(val->fv);
        break;
    case HSD_A_T_TS_BLEND:
        tobj->blending = clamp_unit(val->fv);
        break;
    }
}

void HSD_TObjAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* i;

    if (tobj == NULL) {
        return;
    }

    for (i = tobj; i != NULL; i = i->next) {
        HSD_TObjAnim(i);
    }
}

static int TObjLoad(HSD_TObj* tobj, HSD_TObjDesc* td)
{
    tobj->next = HSD_TObjLoadDesc(td->next);
    TOBJ_PACKED(tobj)->anim_id = td->id;
    tobj->src = td->src;
    tobj->mtxid = GX_IDENTITY;
    tobj->rotate.x = td->rotate.x;
    tobj->rotate.y = td->rotate.y;
    tobj->rotate.z = td->rotate.z;
    tobj->scale = td->scale;
    tobj->translate = td->translate;
    tobj->wrap_s = td->wrap_s;
    tobj->wrap_t = td->wrap_t;
    tobj->repeat_s = td->repeat_s;
    tobj->repeat_t = td->repeat_t;
    tobj->flags = td->blend_flags;
    tobj->blending = td->blending;
    tobj->magFilt = td->magFilt;
    tobj->imagedesc = td->imagedesc;
    tobj->tlut = HSD_TlutLoadDesc(td->tlutdesc);
    tobj->lod = td->lod;
    tobj->aobj = NULL;
    tobj->flags |= TEX_MTX_DIRTY;
    TOBJ_EXT(tobj)->tlut_no = (u8) -1;
    TOBJ_EXT(tobj)->tev = HSD_TObjTevLoadDesc(td->tev);

    return 0;
}

HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc* td)
{
    if (td != NULL) {
        HSD_TObj* tobj;
        HSD_ClassInfo* info;

        if (!td->class_name || !(info = hsdSearchClassInfo(td->class_name))) {
            tobj = HSD_TObjAlloc();
        } else {
            tobj = hsdNew(info);
            HSD_ASSERT(488, tobj);
        }
        HSD_TOBJ_METHOD(tobj)->load(tobj, td);
        return tobj;
    } else {
        return NULL;
    }
}

HSD_TObj* _HSD_TObjGetCurrentByType(HSD_TObj* from, u32 mapping)
{
    HSD_TObj* tp;

    if (from == NULL) {
        tp = tobj_head;
    } else {
        tp = from->next;
    }

    for (; tp != NULL; tp = tp->next) {
        if (tobj_coord(tp) == mapping) {
            return tp;
        }
    }
    return NULL;
}

static void MakeTextureMtx(HSD_TObj* tobj)
{
    HSD_Vec3 scale;
    HSD_Mtx m;
    HSD_Vec3 trans;
    HSD_Quaternion rot;


    { int valid = 0;
      if (tobj->repeat_s && tobj->repeat_t) valid = 1;
      if (!valid) __assert("tobj.c",610,"tobj->repeat_s && tobj->repeat_t");
    }

    scale.x = fabsf(tobj->scale.x) < 1.00000001335e-10F
                  ? 0.0F
                  : (f32) tobj->repeat_s / tobj->scale.x;
    scale.y = fabsf(tobj->scale.y) < 1.00000001335e-10F
                  ? 0.0F
                  : (f32) tobj->repeat_t / tobj->scale.y;
    scale.z = tobj->scale.z;
    rot.x = tobj->rotate.x;
    rot.y = tobj->rotate.y;
    rot.z = -tobj->rotate.z;
    trans.x = -tobj->translate.x;
    trans.y =
        -(tobj->translate.y + (tobj->wrap_t == GX_MIRROR
                                   ? 1.0F / (tobj->repeat_t / tobj->scale.y)
                                   : 0.0F));
    trans.z = tobj->translate.z;

    PSMTXTrans(TOBJ_EXT(tobj)->mtx, trans.x, trans.y, trans.z);
    HSD_MkRotationMtx(m, (HSD_Vec3*) &rot);
    PSMTXConcat(m, TOBJ_EXT(tobj)->mtx, TOBJ_EXT(tobj)->mtx);
    PSMTXScale(m, scale.x, scale.y, scale.z);
    PSMTXConcat(m, TOBJ_EXT(tobj)->mtx, TOBJ_EXT(tobj)->mtx);
}

static void TObjSetupMtx(HSD_TObj* tobj)
{
    int i;

    if (tobj_coord(tobj) == TEX_COORD_TOON) {
        return;
    }

    if (tobj->flags & TEX_MTX_DIRTY) {
        HSD_TOBJ_METHOD(tobj)->make_mtx(tobj);
        tobj->flags &= ~TEX_MTX_DIRTY;
    }

    switch (tobj_coord(tobj)) {
    case TEX_COORD_REFLECTION: {
        HSD_Mtx mtx;

        for (i = 0; i < 3; i++) {
            mtx[i][0] = 0.5F * TOBJ_EXT(tobj)->mtx[i][0];
            mtx[i][1] = -0.5F * TOBJ_EXT(tobj)->mtx[i][1];
            mtx[i][2] = 0.0F;
            mtx[i][3] = 0.5F * TOBJ_EXT(tobj)->mtx[i][0] + 0.5F * TOBJ_EXT(tobj)->mtx[i][1] +
                        TOBJ_EXT(tobj)->mtx[i][2] + TOBJ_EXT(tobj)->mtx[i][3];
        }
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    case TEX_COORD_GRADATION: {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        HSD_Mtx mtx, projection;
        for (i = 0; i < 3; ++i) {
            mtx[i][0] = 0.5F * TOBJ_EXT(tobj)->mtx[i][0];
            mtx[i][1] = -0.5F * TOBJ_EXT(tobj)->mtx[i][1];
            mtx[i][2] = 0.0F;
            mtx[i][3] = 0.5F * TOBJ_EXT(tobj)->mtx[i][0] + 0.5F * TOBJ_EXT(tobj)->mtx[i][1] + TOBJ_EXT(tobj)->mtx[i][2] + TOBJ_EXT(tobj)->mtx[i][3];
        }
        switch (HSD_CObjGetProjectionType(cobj)) {
        case 1:
            C_MTXLightPerspective(projection,cobj->projection_param[0],cobj->projection_param[1],0.5F,-0.5F,0.5F,0.5F);
            break;
        case 2:
            C_MTXLightFrustum(projection,cobj->projection_param[0],cobj->projection_param[1],cobj->projection_param[2],cobj->projection_param[3],cobj->near,0.5F,-0.5F,0.5F,0.5F);
            break;
        case 3:
        default:
            C_MTXLightOrtho(projection,cobj->projection_param[0],cobj->projection_param[1],cobj->projection_param[2],cobj->projection_param[3],0.5F,-0.5F,0.5F,0.5F);
            break;
        }
        PSMTXConcat(mtx,projection,mtx);
        GXLoadTexMtxImm(mtx,tobj->mtxid,GX_MTX3x4);
        break;
    }
    case TEX_COORD_BACKLIGHT: {
        HSD_Mtx mtx;
        mtx[0][0]=1.0F; mtx[0][1]=0.0F; mtx[0][2]=0.0F; mtx[0][3]=0.0F;
        mtx[1][0]=0.0F; mtx[1][1]=1.0F; mtx[1][2]=0.0F; mtx[1][3]=0.0F;
        mtx[2][2]=0.0F; mtx[2][1]=0.0F; mtx[2][0]=0.0F; mtx[2][3]=1.0F;
        GXLoadTexMtxImm(mtx,tobj->mtxid,GX_MTX3x4);
        break;
    }
    case TEX_COORD_HILIGHT: {
        HSD_LObj* lobj;

        if ((lobj = HSD_LObjGetCurrentByType(1)) != NULL) {
            HSD_CObj* cobj;
            HSD_Vec3 ldir, half;
            HSD_Mtx mtx;
            float (*vmtx)[4];

            cobj = HSD_CObjGetCurrent();
            HSD_ASSERT(0x30D, cobj);
            vmtx = HSD_CObjGetViewingMtxPtrDirect(cobj);
            HSD_LObjGetLightVector(lobj, &ldir);
            PSMTXMultVecSR(vmtx, &ldir, &ldir);
            ldir.z += -1.0F;

            PSVECNormalize(&ldir, &half);

            half.x *= -0.5;
            half.y *= -0.5;
            half.z *= -0.5;

            mtx[0][0] = TOBJ_EXT(tobj)->mtx[0][0] * half.x;
            mtx[0][1] = TOBJ_EXT(tobj)->mtx[0][0] * half.y;
            mtx[0][2] = TOBJ_EXT(tobj)->mtx[0][0] * half.z;
            mtx[0][3] = TOBJ_EXT(tobj)->mtx[0][0] * 0.5F + TOBJ_EXT(tobj)->mtx[0][3];
            mtx[1][0] = TOBJ_EXT(tobj)->mtx[1][0] * half.x;
            mtx[1][1] = TOBJ_EXT(tobj)->mtx[1][0] * half.y;
            mtx[1][2] = TOBJ_EXT(tobj)->mtx[1][0] * half.z;
            mtx[1][3] = TOBJ_EXT(tobj)->mtx[1][0] * 0.5F + TOBJ_EXT(tobj)->mtx[1][3];
            mtx[2][0] = mtx[2][1] = mtx[2][2] = 0.0F;
            mtx[2][3] = 1.0F;

            GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
        } else {
            static HSD_Mtx zero = { 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F,
                                0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F };
            GXLoadTexMtxImm(zero, tobj->mtxid, GX_MTX3x4);
        }
    } break;

    case TEX_COORD_SHADOW: {
        HSD_CObj* cobj = HSD_CObjGetCurrent();
        HSD_Mtx mtx;

        PSMTXConcat(TOBJ_EXT(tobj)->mtx, HSD_CObjGetInvViewingMtxPtrDirect(cobj), mtx);
        GXLoadTexMtxImm(mtx, tobj->mtxid, GX_MTX3x4);
    } break;

    default:
        if (tobj_bump(tobj)) {
            GXLoadTexMtxImm(TOBJ_EXT(tobj)->mtx, tobj->mtxid, GX_MTX2x4);
        } else {
            GXLoadTexMtxImm(TOBJ_EXT(tobj)->mtx, tobj->mtxid, GX_MTX3x4);
        }
        break;
    }
}

void HSD_TObjSetupTextureCoordGen(HSD_TObj* tobj)
{
    for (; tobj != NULL; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }
        if (tobj_bump(tobj)) {
            setupTextureCoordGen(tobj);
            setupTextureCoordGenBump(tobj);
        } else if (tobj_coord(tobj) == TEX_COORD_TOON) {
            setupTextureCoordGenToon(tobj);
        } else {
            setupTextureCoordGen(tobj);
        }
    }
}

void HSD_TObjSetupVolatileTev(HSD_TObj* tobj, u32 rendermode)
{
    for (; tobj; tobj = tobj->next) {
        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        if (tobj_bump(tobj)) {
            SetupEmbossBumpTev(tobj);
        }

        if (tobj_lightmap(tobj) & TEX_LIGHTMAP_SHADOW) {
            TObjSetupTevModulateShadow(tobj);
            break;
        }
    }
}

static void MakeColorGenTExp(u32 lightmap, HSD_TObj* tobj, HSD_TExp** c,
                             HSD_TExp** a, HSD_TExp** list, int repeat)
{
    HSD_TObjTev* tev = TOBJ_EXT(tobj)->tev;
    u8* in;
    HSD_TExp *e0, *tmp;
    int i;

    HSD_TExp* konst_rgb;
    HSD_TExp* konst_r;
    HSD_TExp* konst_g;
    HSD_TExp* konst_b;
    HSD_TExp* konst_a;
    HSD_TExp* reg0_rgb;
    HSD_TExp* reg0_a;
    HSD_TExp* reg1_rgb;
    HSD_TExp* reg1_a;

    int use_k_rgb = 0;
    int use_k_r = 0;
    int use_k_g = 0;
    int use_k_b = 0;
    int use_k_a = 0;
    int use_reg0_rgb = 0;
    int use_reg0_a = 0;
    int use_reg1_rgb = 0;
    int use_reg1_a = 0;

    in = &tev->color_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CC_KONST_RGB:
            use_k_rgb = 1;
            break;
        case TOBJ_TEV_CC_KONST_RRR:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CC_KONST_GGG:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CC_KONST_BBB:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CC_KONST_AAA:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CC_TEX0_RGB:
            use_reg0_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX0_AAA:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CC_TEX1_RGB:
            use_reg1_rgb = 1;
            break;
        case TOBJ_TEV_CC_TEX1_AAA:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }
    in = &tev->alpha_a;
    for (i = 0; i < 4; i++) {
        switch (in[i]) {
        case TOBJ_TEV_CA_KONST_R:
            use_k_r = 1;
            break;
        case TOBJ_TEV_CA_KONST_G:
            use_k_g = 1;
            break;
        case TOBJ_TEV_CA_KONST_B:
            use_k_b = 1;
            break;
        case TOBJ_TEV_CA_KONST_A:
            use_k_a = 1;
            break;
        case TOBJ_TEV_CA_TEX0_A:
            use_reg0_a = 1;
            break;
        case TOBJ_TEV_CA_TEX1_A:
            use_reg1_a = 1;
            break;
        default:
            break;
        }
    }

    if (use_k_rgb) {
        konst_rgb =
            HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->konst, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_k_r) {
        konst_r = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->konst.r, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_g) {
        konst_g = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->konst.g, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_b) {
        konst_b = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->konst.b, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_k_a) {
        konst_a = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->konst.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg0_rgb) {
        reg0_rgb = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->tev0, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg0_a) {
        reg0_a = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->tev0.a, HSD_TE_X, HSD_TE_U8, list);
    }
    if (use_reg1_rgb) {
        reg1_rgb = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->tev1, HSD_TE_RGB, HSD_TE_U8, list);
    }
    if (use_reg1_a) {
        reg1_a = HSD_TExpCnst(&TOBJ_EXT(tobj)->tev->tev1.a, HSD_TE_X, HSD_TE_U8, list);
    }

    e0 = HSD_TExpTev(list);
    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    if (tev->active & TOBJ_TEVREG_ACTIVE_COLOR_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->color_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CC_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_ONE:
                sel[i] = HSD_TE_1;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_HALF:
                sel[i] = HSD_TE_4_8;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CC_TEXC:
                sel[i] = HSD_TE_RGB;
                exp[i] = HSD_TEXP_TEX;
                break;
            case GX_CC_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CC_KONST_RGB:
                sel[i] = HSD_TE_RGB;
                exp[i] = konst_rgb;
                break;
            case TOBJ_TEV_CC_KONST_RRR:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CC_KONST_GGG:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CC_KONST_BBB:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CC_KONST_AAA:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CC_TEX0_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg0_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX0_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_RGB:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_RGB, reg1_rgb);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CC_TEX1_AAA:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpColorOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpColorIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_RGB;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(0x52A, 0);
                break;
            }
        }

        HSD_TExpColorOp(e0, (GXTevOp) tev->color_op,
                        (GXTevBias) tev->color_bias,
                        (GXTevScale) tev->color_scale, tev->color_clamp);
        HSD_TExpColorIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);
        *c = e0;
    }

    if (tev->active & TOBJ_TEVREG_ACTIVE_ALPHA_TEV) {
        HSD_TEInput sel[4];
        HSD_TExp* exp[4];
        int i;

        in = &tev->alpha_a;
        for (i = 0; i < 4; i++) {
            switch (in[i]) {
            case GX_CA_ZERO:
                sel[i] = HSD_TE_0;
                exp[i] = HSD_TEXP_ZERO;
                break;
            case GX_CA_TEXA:
                sel[i] = HSD_TE_A;
                exp[i] = HSD_TEXP_TEX;
                break;
            case TOBJ_TEV_CA_KONST_R:
                sel[i] = HSD_TE_X;
                exp[i] = konst_r;
                break;
            case TOBJ_TEV_CA_KONST_G:
                sel[i] = HSD_TE_X;
                exp[i] = konst_g;
                break;
            case TOBJ_TEV_CA_KONST_B:
                sel[i] = HSD_TE_X;
                exp[i] = konst_b;
                break;
            case TOBJ_TEV_CA_KONST_A:
                sel[i] = HSD_TE_X;
                exp[i] = konst_a;
                break;
            case TOBJ_TEV_CA_TEX0_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg0_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            case TOBJ_TEV_CA_TEX1_A:
                tmp = HSD_TExpTev(list);
                HSD_TExpOrder(tmp, NULL, GX_COLOR_NULL);
                HSD_TExpAlphaOp(tmp, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                                GX_ENABLE);
                HSD_TExpAlphaIn(tmp, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                                HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                                HSD_TE_X, reg1_a);
                sel[i] = HSD_TE_A;
                exp[i] = tmp;
                break;
            default:
                HSD_ASSERT(0x573, 0);
                break;
            }
        }

        HSD_TExpAlphaOp(e0, (GXTevOp) tev->alpha_op,
                        (GXTevBias) tev->alpha_bias,
                        (GXTevScale) tev->alpha_scale, tev->alpha_clamp);
        HSD_TExpAlphaIn(e0, sel[0], exp[0], sel[1], exp[1], sel[2], exp[2],
                        sel[3], exp[3]);

        *a = e0;
    }
}

static void TObjMakeTExp(HSD_TObj* tobj, u32 lightmap, u32 lightmap_done,
                         HSD_TExp** c, HSD_TExp** a, HSD_TExp** list)
{
    HSD_TExp *e0, *e1;
    HSD_TExp *c_src, *a_src;
    HSD_TEInput c_sel, a_sel;
    int repeat = (lightmap_done & tobj_lightmap(tobj)) != 0;

    c_src = HSD_TEXP_TEX;
    c_sel = HSD_TE_RGB;

    a_src = HSD_TEXP_TEX;
    a_sel = HSD_TE_A;

    e0 = HSD_TExpTev(list);

    if (TOBJ_EXT(tobj)->tev && (TOBJ_EXT(tobj)->tev->active & (TOBJ_TEVREG_ACTIVE_COLOR_TEV |
                                           TOBJ_TEVREG_ACTIVE_ALPHA_TEV)))
    {
        MakeColorGenTExp(lightmap, tobj, &c_src, &a_src, list, repeat);
    }

    HSD_TExpOrder(e0, tobj, GX_COLOR_NULL);

    switch (tobj_colormap(tobj)) {
    case TEX_COLORMAP_ALPHA_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, a_sel, a_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_RGB_MASK:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, c_sel, c_src,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_BLEND:
        e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_RGB, *c, c_sel, c_src, HSD_TE_X, e1,
                        HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_MODULATE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c, c_sel,
                        c_src, HSD_TE_0, HSD_TEXP_ZERO);
        break;
    case TEX_COLORMAP_REPLACE:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, c_sel, c_src);
        break;
    case TEX_COLORMAP_NONE:
    case TEX_COLORMAP_PASS:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO,
                        HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_ADD:
        HSD_TExpColorOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    case TEX_COLORMAP_SUB:
        HSD_TExpColorOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE);
        HSD_TExpColorIn(e0, c_sel, c_src, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                        HSD_TEXP_ZERO, HSD_TE_RGB, *c);
        break;
    default:
        HSD_ASSERT(1503, 0);
    }
    *c = e0;

    if (!repeat) {
        switch (tobj_alphamap(tobj)) {
        case TEX_ALPHAMAP_ALPHA_MASK:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, a_sel, a_src,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_BLEND:
            e1 = HSD_TExpCnst(&tobj->blending, HSD_TE_X, HSD_TE_F32, list);
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_A, *a, a_sel, a_src, HSD_TE_X, e1,
                            HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_MODULATE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a, a_sel,
                            a_src, HSD_TE_0, HSD_TEXP_ZERO);
            break;
        case TEX_ALPHAMAP_REPLACE:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, a_sel,
                            a_src);
            break;
        case TEX_ALPHAMAP_NONE:
        case TEX_ALPHAMAP_PASS:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_0,
                            HSD_TEXP_ZERO, HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A,
                            *a);
            break;
        case TEX_ALPHAMAP_ADD:
            HSD_TExpAlphaOp(e0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        case TEX_ALPHAMAP_SUB:
            HSD_TExpAlphaOp(e0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1,
                            GX_ENABLE);
            HSD_TExpAlphaIn(e0, a_sel, a_src, HSD_TE_0, HSD_TEXP_ZERO,
                            HSD_TE_0, HSD_TEXP_ZERO, HSD_TE_A, *a);
            break;
        default:
            HSD_ASSERT(1561, 0);
        }
        *a = e0;
    }
}

s32 HSD_TObjAssignResources(HSD_TObj* tobj_top)
{
    HSD_TObj* tobj;
    u32 texmap_no = 0;
    u32 texcoord_no = 0;
    u32 limit = 8;
    HSD_TObj* bump = NULL;
    HSD_TObj* toon = NULL;

    if (tobj_top == NULL) {
        return 0;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            toon = tobj;
        } else if (tobj_bump(tobj)) {
            bump = tobj;
        }
    }

    if (toon) {
        limit -= 1;
    }
    if (bump) {
        limit -= 2;
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj_coord(tobj) == TEX_COORD_TOON) {
            if (tobj != toon) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (tobj_bump(tobj)) {
            if (tobj != bump) {
                tobj->id = GX_TEXMAP_NULL;
            }
        } else if (texmap_no < limit) {
            tobj->id = HSD_Index2TexMap(texmap_no++);
            tobj->mtxid = HSD_TexMapID2PTTexMtx(tobj->id);
            switch (tobj_coord(tobj)) {
            case TEX_COORD_REFLECTION:
            case TEX_COORD_HILIGHT:
            case TEX_COORD_SHADOW:
            case TEX_COORD_GRADATION:
            case TEX_COORD_BACKLIGHT:
                TOBJ_EXT(tobj)->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        } else {
            tobj->id = GX_TEXMAP_NULL;
        }
    }

    for (tobj = tobj_top; tobj; tobj = tobj->next) {
        if (tobj->id != GX_TEXMAP_NULL && !tobj_bump(tobj)) {
            switch (tobj_coord(tobj)) {
            case TEX_COORD_UV:
                TOBJ_EXT(tobj)->coord = HSD_Index2TexCoord(texcoord_no++);
                break;
            default:
                break;
            }
        }
    }

    if (bump) {
        bump->id = HSD_Index2TexMap(texmap_no++);
        bump->mtxid = GX_TEXMTX9;
        TOBJ_EXT(bump)->coord = HSD_Index2TexCoord(texcoord_no);
        texcoord_no += 2;
    }
    if (toon) {
        toon->id = HSD_Index2TexMap(texmap_no++);
        TOBJ_EXT(toon)->coord = HSD_Index2TexCoord(texcoord_no++);
    }

    return (int) texcoord_no;
}

void HSD_TObjSetup(HSD_TObj* tobj)
{
    GXTlutObj tlutobj;
    GXTexObj texobj;
    int num;
    HSD_Tlut* tluts[8];
    int nb_tluts = 0;
    u32 tlut_name = GX_TLUT0;
    u32 big_tlut_name = GX_BIGTLUT0;
    int i;

    tobj_head = tobj;

    if (tobj == NULL) {
        return;
    }

    num = HSD_TObjAssignResources(tobj);
    if (num > 0) {
        HSD_StateRegisterTexGen(HSD_Index2TexCoord(num - 1));
    }

    for (; tobj; tobj = tobj->next) {
        static HSD_TexLODDesc default_lod = {
            GX_LIN_MIP_LIN, 0.0F, GX_FALSE, GX_FALSE, GX_ANISO_1,
        };
        HSD_TexLODDesc* lod;
        HSD_ImageDesc* imagedesc = tobj->imagedesc;
        GXTexFilter min_filter;

        if (tobj->id == GX_TEXMAP_NULL) {
            continue;
        }

        TObjSetupMtx(tobj);
        HSD_ASSERT(1713, imagedesc);
        HSD_ASSERT(1714, imagedesc->image_ptr);

        lod = tobj->lod != NULL ? tobj->lod : &default_lod;
        min_filter = lod->minFilt;

        switch ((GXTexFmt)imagedesc->format) {
        case GX_TF_C4:
        case GX_TF_C8:
        case GX_TF_C14X2: {
            HSD_Tlut* tlut;

            if (TOBJ_EXT(tobj)->tlut_no != (u8) -1) {
                tlut = TOBJ_EXT(tobj)->tluttbl[TOBJ_EXT(tobj)->tlut_no];
            } else {
                tlut = tobj->tlut;
            }

            HSD_ASSERT(1730, tlut);

            for (i = 0; i < nb_tluts; i++) {
                if (!DifferentTluts(tluts[i], tlut)) {
                    break;
                }
            }
            if (i < nb_tluts) {
                tlut->tlut_name = tluts[i]->tlut_name;
            } else if (nb_tluts < 8) {
                if (tlut->n_entries > 256) {
                    tlut->tlut_name = big_tlut_name++;
                } else {
                    tlut->tlut_name = tlut_name++;
                }
                GXInitTlutObj(&tlutobj, tlut->lut, tlut->fmt, tlut->n_entries);
                GXLoadTlut(&tlutobj, tlut->tlut_name);
                tluts[nb_tluts++] = tlut;
            } else {
                tlut->tlut_name = GX_TLUT0;
            }

            GXInitTexObjCI(&texobj, imagedesc->image_ptr, imagedesc->width,
                           imagedesc->height, imagedesc->format, tobj->wrap_s,
                           tobj->wrap_t,
                           imagedesc->mipmap ? GX_TRUE : GX_FALSE,
                           tlut->tlut_name);
            if (min_filter == GX_LIN_MIP_LIN) {
                min_filter = GX_LIN_MIP_NEAR;
            }
        } break;

        case GX_TF_I4:
        case GX_TF_I8:
        case GX_TF_IA4:
        case GX_TF_IA8:
        case GX_TF_RGB565:
        case GX_TF_RGB5A3:
        case GX_TF_RGBA8:
        case GX_TF_CMPR:
            GXInitTexObj(&texobj, imagedesc->image_ptr, imagedesc->width,
                         imagedesc->height, imagedesc->format, tobj->wrap_s,
                         tobj->wrap_t, imagedesc->mipmap ? GX_TRUE : GX_FALSE);
            break;

        default:
            HSD_ASSERT(0x6fe, 0);
        }

        if (!imagedesc->mipmap) {
            min_filter &= 0x01;
        }
        GXInitTexObjLOD(&texobj, min_filter, tobj->magFilt, imagedesc->minLOD,
                        imagedesc->maxLOD, lod->LODBias, lod->bias_clamp,
                        lod->edgeLODEnable, lod->max_anisotropy);

        GXLoadTexObj(&texobj, tobj->id);
    }
}

GXTexMtx HSD_Index2TexMtx(u32 index)
{
    switch (index) {
    case 0:
        return GX_TEXMTX0;
    case 1:
        return GX_TEXMTX1;
    case 2:
        return GX_TEXMTX2;
    case 3:
        return GX_TEXMTX3;
    case 4:
        return GX_TEXMTX4;
    case 5:
        return GX_TEXMTX5;
    case 6:
        return GX_TEXMTX6;
    case 7:
        return GX_TEXMTX7;
    case 8:
        return GX_TEXMTX8;
    case 9:
        return GX_TEXMTX9;
    case 10:
        return GX_IDENTITY;
    default:
        OSReport("texmtx index exceed hardware limit (%d).\n", index);
        HSD_Panic("tobj.c", 2012, "");
    }
    return GX_IDENTITY;
}

void HSD_TObjRemove(HSD_TObj* tobj)
{
    hsdDelete(tobj);
}

void HSD_TObjRemoveAll(HSD_TObj* tobj)
{
    while (tobj) {
        HSD_TObj* next = tobj->next;
        HSD_TObjRemove(tobj);
        tobj = next;
    }
}

void HSD_TObjAddNext(HSD_TObj* tobj, HSD_TObj* next) {
    if (!tobj || !next) return;
    next->next = tobj->next;
    tobj->next = next;
}

HSD_TObj* HSD_TObjAlloc(void)
{
    HSD_TObj* new = hsdNew(&HSD_TObjGetDefaultClass()->parent);
    HSD_ASSERT(2175, new);
    return new;
}

HSD_ImageDesc* HSD_ImageDescAlloc(void)
{
    HSD_ImageDesc* idesc = hsdAllocMemPiece(sizeof(HSD_ImageDesc));
    HSD_ASSERT(2290, idesc);
    memset(idesc, 0, sizeof(HSD_ImageDesc));
    return idesc;
}

void HSD_ImageDescFree(HSD_ImageDesc* idesc)
{
    hsdFreeMemPiece(idesc, sizeof(HSD_ImageDesc));
}

void HSD_ImageDescRemove(HSD_ImageDesc* idesc) { hsdFreeMemPiece(idesc,sizeof(HSD_ImageDesc)); }

static int TObjInit(HSD_Class* o) {
    int status = HSD_PARENT_INFO(&hsdTObj)->init(o);
    if (status >= 0) {
        HSD_TObj* tobj = (HSD_TObj*)o;
        status = 0;
        TOBJ_PACKED(tobj)->anim_id = 0xffff;
    }
    return status;
}

static void TObjRelease(HSD_Class* o)
{
    HSD_TObj* tobj = ((HSD_TObj*)o);

    HSD_AObjRemove(tobj->aobj);
    HSD_TlutRemove(tobj->tlut);
    HSD_TObjTevRemove(TOBJ_EXT(tobj)->tev);
    if (TOBJ_EXT(tobj)->tluttbl) {
        int i;
        for (i = 0; TOBJ_EXT(tobj)->tluttbl[i]; i++) {
            HSD_TlutRemove(TOBJ_EXT(tobj)->tluttbl[i]);
        }
        HSD_Free(TOBJ_EXT(tobj)->tluttbl);
    }

    HSD_PARENT_INFO(&hsdTObj)->release(o);
}

static void TObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdTObj)) {
        tobj_head = NULL;
    }
    HSD_PARENT_INFO(&hsdTObj)->amnesia(info);
}

static void TObjInfoInit(void) {
    hsdInitClassInfo((HSD_ClassInfo*)&hsdTObj,&hsdObj,"sysdolphin_base_library","hsd_tobj",sizeof(HSD_TObjInfo),sizeof(HSD_TObjRuntime));
    hsdTObj.parent.init = TObjInit;
    hsdTObj.parent.release = TObjRelease;
    hsdTObj.parent.amnesia = TObjAmnesia;
    hsdTObj.load = TObjLoad;
    hsdTObj.make_texp = TObjMakeTExp;
    hsdTObj.make_mtx = MakeTextureMtx;
    hsdTObj.update = TObjUpdateFunc;
}
