#ifndef HSD_STATE_H
#define HSD_STATE_H
#include "game/maximum/GSAPI/baselib/animation_objects.h"
#include <dolphin/gx.h>
struct HSD_PEDesc;
#define HSD_STATE_ALL -1
#define HSD_STATE_NONE 0
#define HSD_STATE_PRIMITIVE 0x1
#define HSD_STATE_VTX_ATTR 0x2
#define HSD_STATE_COLOR_CHANNEL 0x4
#define HSD_STATE_TEV_STAGE 0x8
#define HSD_STATE_TEV_REGISTER 0x10
#define HSD_STATE_TEX_COORD_GEN 0x20
#define HSD_STATE_RENDER_MODE 0x40

typedef struct HSD_Chan {
    struct HSD_Chan* next;
    GXChannelID chan;
    u32 flags;
    GXColor amb_color;
    GXColor mat_color;
    GXBool enable;
    GXColorSrc amb_src;
    GXColorSrc mat_src;
    GXLightID light_mask;
    GXDiffuseFn diff_fn;
    GXAttnFn attn_fn;
    HSD_AObj* aobj;
} HSD_Chan;
typedef char HSD_ChanSizeCheck[sizeof(HSD_Chan) == 0x30 ? 1 : -1];

void HSD_SetupChannelMode(u32 arg0);
void HSD_SetupPEMode(u32 flags, struct HSD_PEDesc* pe);
void HSD_SetupRenderModeWithCustomPE(u32 rendermode, struct HSD_PEDesc* pe);
void HSD_SetupRenderMode(u32);
void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          f32 alpha);
void HSD_SetMaterialShininess(f32 shininess);

void HSD_StateSetCullMode(int mode);












void HSD_StateInvalidate(int mask);



#endif
