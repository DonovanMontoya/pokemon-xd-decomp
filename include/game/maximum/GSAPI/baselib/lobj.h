#ifndef SYSDOLPHIN_BASELIB_LOBJ_H
#define SYSDOLPHIN_BASELIB_LOBJ_H
#include "game/maximum/GSAPI/baselib/cobj.h"
typedef struct HSD_LightPoint HSD_LightPoint;
typedef struct HSD_LightPointDesc HSD_LightPointDesc;
typedef struct HSD_LightSpot HSD_LightSpot;
typedef struct HSD_LightSpotDesc HSD_LightSpotDesc;
typedef struct HSD_LightAttn HSD_LightAttn;
typedef struct HSD_LightDesc HSD_LightDesc;
typedef struct HSD_LightAnim HSD_LightAnim;
typedef struct HSD_LObjInfo HSD_LObjInfo;

#define HSD_A_L_LITC_R 9
#define HSD_A_L_LITC_G 10
#define HSD_A_L_LITC_B 11
#define HSD_A_L_VIS 12
#define HSD_A_L_A0 13
#define HSD_A_L_A1 14
#define HSD_A_L_A2 15
#define HSD_A_L_K0 16
#define HSD_A_L_K1 17
#define HSD_A_L_K2 18
#define HSD_A_L_CUTOFF 19
#define HSD_A_L_REFDIST 20
#define HSD_A_L_REFBRIGHT 21
#define HSD_A_L_LITC_A 22
#define LOBJ_AMBIENT (0 << 0)
#define LOBJ_INFINITE (1 << 0)
#define LOBJ_POINT (2 << 0)
#define LOBJ_SPOT (3 << 0)
#define LOBJ_FLAGS_B1 (1 << 1)
#define LOBJ_DIFFUSE (1 << 2)
#define LOBJ_SPECULAR (1 << 3)
#define LOBJ_ALPHA (1 << 4)
#define LOBJ_HIDDEN (1 << 5)
#define LOBJ_RAW_PARAM (1 << 6)
#define LOBJ_DIFF_DIRTY (1 << 7)
#define LOBJ_SPEC_DIRTY (1 << 8)
#define LOBJ_TYPE_MASK (LOBJ_INFINITE | LOBJ_FLAGS_B1)
#define LOBJ_LIGHT_ATTN_NONE 0
#define LOBJ_LIGHT_ATTN 1

#define MAX_GXLIGHT 9

struct HSD_LightPoint {
    f32 cutoff;
    u32 point_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightPointDesc {
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpot {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightSpotDesc {
    f32 cutoff;
    u32 spot_func;
    f32 ref_br;
    f32 ref_dist;
    u32 dist_func;
};

struct HSD_LightAttn {
    f32 a0;
    f32 a1;
    f32 a2;
    f32 k0;
    f32 k1;
    f32 k2;
};

typedef struct HSD_LObjRuntime {
    /* 0x00 - 0x04 */ HSD_Obj parent;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 priority;
    /* 0x0C */ HSD_LObj* next;
    /* 0x10 */ GXColor color;
    /* 0x14 */ GXColor hw_color;
    /* 0x18 */ HSD_WObj* position;
    /* 0x1C */ HSD_WObj* interest;
    /* 0x20 - 0x34 */ union HSD_LObj_u {
        HSD_LightPoint point;
        HSD_LightSpot spot;
        HSD_LightAttn attn;
    } u;
    /* 0x38 */ f32 shininess;
    /* 0x3C - 0x44 */ Vec3 lvec;
    /* 0x48 */ HSD_AObj* aobj;
    /* 0x4C */ GXLightID id;
    /* 0x50 */ GXLightObj lightobj;
    /* 0x90 */ GXLightID spec_id;
    /* 0x94 */ GXLightObj spec_lightobj;
} HSD_LObjRuntime;
#define LOBJ_EXT(o) ((HSD_LObjRuntime*)(o))

struct HSD_LightDesc {
    /* 0x00 */ char* class_name;
    /* 0x04 */ HSD_LightDesc* next;
    /* 0x08 */ u16 flags;
    /* 0x0A */ u16 attnflags;
    /* 0x0C */ GXColor color;
    /* 0x10 */ HSD_WObjDesc* position;
    /* 0x14 */ HSD_WObjDesc* interest;
    union HSD_LightDesc_u { void* p; f32* shininess; HSD_LightPointDesc* point; HSD_LightSpotDesc* spot; HSD_LightAttn* attn; } u;
};

struct HSD_LightAnim {
    HSD_LightAnim* next;
    HSD_AObjDesc* aobjdesc;
    HSD_WObjAnim* position_anim;
    HSD_WObjAnim* interest_anim;
};

struct HSD_LObjInfo {
    HSD_ClassInfo parent;
    int (*load)(HSD_LObj* lobj, HSD_LightDesc* ldesc);
    HSD_ObjUpdateFunc update;
};

#define HSD_LOBJ(o) ((HSD_LObj*) (o))
#define HSD_LOBJ_INFO(i) ((HSD_LObjInfo*) (i))
#define HSD_LOBJ_METHOD(o) HSD_LOBJ_INFO((o)->parent.class_info)

#ifdef __cplusplus
extern "C" {
#endif
extern HSD_LObjInfo hsdLObj;

u32 HSD_LObjGetFlags(HSD_LObj* lobj);
void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags);
void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags);
GXLightID HSD_LObjGetLightMaskDiffuse(void);
s32 HSD_LObjGetLightMaskAttnFunc(void);
s32 HSD_LObjGetLightMaskAlpha(void);
s32 HSD_LObjGetLightMaskSpecular(void);

s32 HSD_LObjGetNbActive(void);
HSD_LObj* HSD_LObjGetActiveByID(GXLightID id);
HSD_LObj* HSD_LObjGetActiveByIndex(s32 idx);

void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim);
void HSD_LObjAnim(HSD_LObj* lobj);
void HSD_LObjAnimAll(HSD_LObj* lobj);
void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe);
void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe);
void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir);
void HSD_LObjSetup(HSD_LObj* lobj, GXColor color, f32 shininess);

int HSD_LObjGetPosition(HSD_LObj*, Vec3*);
int HSD_LObjGetInterest(HSD_LObj*, Vec3*);

void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position);
void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest);

void HSD_LObjSetupInit(HSD_CObj* arg0);

void HSD_LObjSetColor(HSD_LObj* lobj, GXColor color);
void HSD_LObjGetColor(HSD_LObj* lobj, GXColor* color);

void HSD_LObjSetupSpecularInit(Mtx pmtx);

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj);

HSD_LObj* HSD_LObjGetCurrentByType(u16 type);

HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc);

void HSD_LObjAddCurrentAll(HSD_LObj*);
void HSD_LObjRemoveAnimAll(HSD_LObj*);
#ifdef __cplusplus
}
#endif
#endif
