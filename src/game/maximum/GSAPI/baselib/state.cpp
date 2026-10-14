/* XD primitive and pixel-engine state cache and material channels. */
#include "game/maximum/GSAPI/baselib/state.h"
#include "game/maximum/GSAPI/baselib/tev.h"
#include "game/maximum/GSAPI/baselib/mobj.h"
#include "game/maximum/GSAPI/baselib/lobj.h"
void HSD_ClearVtxDesc(void);
void HSD_MulColor(GXColor*, GXColor*, GXColor*);
static inline void HSD_StateSetLineWidth(u8 width, int tex_offsets);
static inline void HSD_StateSetBlendMode(int type, int src_factor, int dst_factor, int op);
static inline void HSD_StateSetZMode(u32, int, u32);
static inline void HSD_StateSetPointSize(u8, int);
static inline void HSD_StateSetAlphaCompare(int, u8, int, int, u8);
static inline void HSD_StateSetColorUpdate(u32);
static inline void HSD_StateSetAlphaUpdate(u32);
static inline void HSD_StateSetDstAlpha(u32, u8);
static inline void HSD_StateSetZCompLoc(u32);
static inline void HSD_StateSetDither(u32);
static void _HSD_StateInvalidatePrimitive(void);
static void _HSD_StateInvalidateVtxAttr(void);
static void _HSD_StateInvalidateRenderMode(void);

static u8 state_line_width;
static int state_line_tex_offsets;
static u8 state_point_size;
static int HSD_State_804D75BC;
static int state_cull_mode;
static int state_blend_type;
static int state_src_factor;
static int state_dst_factor;
static int state_logic_op;
static u8 state_z_enable;
static int state_z_func;
static u8 state_z_update;
static int state_alpha_comp0;
static u8 state_alpha_ref0;
static int state_alpha_op;
static int state_alpha_comp1;
static u8 state_alpha_ref1;
static u8 state_color_update;
static u8 state_alpha_update;
static u8 state_enable_dst_alpha;
static u8 state_dst_alpha;
static u8 state_before_tex;
static u8 state_dither;

static struct matstate_t {
    GXColor ambient;
    GXColor diffuse;
    GXColor specular;
    u8 alpha;
    f32 shininess;
} matstate;

void HSD_SetupChannelMode(u32 rendermode)
{
    int use_specular = 0;
    int use_vertex_alpha = 0;
    int diffuse = rendermode & RENDER_DIFFUSE_BITS;
    int alpha;
    if (diffuse == 0) diffuse = RENDER_DIFFUSE_MAT;
    alpha = rendermode & RENDER_ALPHA_BITS;
    if (alpha == 0) alpha = diffuse << RENDER_ALPHA_SHIFT;
    if (rendermode & RENDER_SPECULAR) {
        static HSD_Chan ch = { NULL, GX_COLOR1, 0, {0}, {255,255,255,255},
                              1, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_SPEC, NULL };
        int i;
        int max;
        ch.light_mask = HSD_LObjGetLightMaskSpecular();
        HSD_SetupChannel(&ch);
        use_specular = 1;
        max = HSD_LObjGetNbActive();
        for (i = 0; i < max; i++) {
            HSD_LObj* light = HSD_LObjGetActiveByIndex(i);
            if (light != NULL) {
                GXColor color = *(GXColor*)&light->color;
                HSD_LObjSetup(light, color, matstate.shininess);
            }
        }
    }
    if (rendermode & RENDER_DIFFUSE) {
        static HSD_Chan ch = { NULL, GX_COLOR0, 0, {0}, {255,255,255,255},
                              1, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT, NULL };
        static HSD_Chan ch_a = { NULL, GX_ALPHA0, 0, {0}, {0},
                                1, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_CLAMP, GX_AF_SPOT, NULL };
        static HSD_Chan ch_vtx_a = { NULL, GX_ALPHA0, 0, {0}, {0},
                                    0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_SPOT, NULL };
        static GXColor dark_matter = {0,0,0,255};
        HSD_LObj* ambient = HSD_LObjGetActiveByID(GX_LIGHT_NULL);
        u8 amb_alpha;
        if (ambient != NULL && (ambient->flags & 4)) {
            HSD_MulColor(&matstate.ambient, (GXColor*)&ambient->color, &ch.amb_color);
        } else {
            ch.amb_color = dark_matter;
        }
        ch.mat_src = (diffuse & RENDER_DIFFUSE_VTX) ? GX_SRC_VTX : GX_SRC_REG;
        ch.light_mask = HSD_LObjGetLightMaskDiffuse();
        HSD_SetupChannel(&ch);
        if (alpha & RENDER_ALPHA_VTX) {
            ch_a.chan = GX_ALPHA1;
            HSD_SetupChannel(&ch_vtx_a);
            use_vertex_alpha = 1;
        } else {
            ch_a.chan = GX_ALPHA0;
        }
        ch_a.light_mask = HSD_LObjGetLightMaskAlpha();
        amb_alpha = ambient != NULL && (ambient->flags & 0x10) ? ((GXColor*)&ambient->color)->a : 0;
        if (ch_a.light_mask != 0) {
            ch_a.enable = 1;
            ch_a.mat_color.a = 255;
            ch_a.amb_color.a = amb_alpha;
        } else {
            ch_a.enable = 0;
            ch_a.mat_color.a = amb_alpha;
        }
        HSD_SetupChannel(&ch_a);
    } else {
        static HSD_Chan ch = { NULL, GX_COLOR0, 0, {0}, {255,255,255,255},
                              0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE, NULL };
        static HSD_Chan ch_a = { NULL, GX_ALPHA0, 0, {0}, {0,0,0,255},
                                0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE, NULL };
        ch.mat_src = (diffuse & RENDER_DIFFUSE_VTX) ? GX_SRC_VTX : GX_SRC_REG;
        HSD_SetupChannel(&ch);
        ch_a.mat_src = (alpha & RENDER_ALPHA_VTX) ? GX_SRC_VTX : GX_SRC_REG;
        HSD_SetupChannel(&ch_a);
    }
    if (use_specular) {
        if (!use_vertex_alpha) HSD_DisableChannelLighting(GX_ALPHA1);
        HSD_StateSetNumChans(2);
    } else if (use_vertex_alpha) {
        HSD_DisableChannelLighting(GX_COLOR1);
        HSD_StateSetNumChans(2);
    } else {
        HSD_DisableChannelLighting(GX_COLOR1A1);
        HSD_StateSetNumChans(1);
    }
}

void HSD_SetupPEMode(u32 flags, HSD_PEDesc* pe)
{
    u8 var_r3_2;
    int var_r3;

    if (pe != NULL) {
        HSD_StateSetColorUpdate(pe->flags & 1);
        HSD_StateSetAlphaUpdate(pe->flags & 2);
        HSD_StateSetDstAlpha(pe->flags & 4, pe->dst_alpha);
        HSD_StateSetBlendMode(pe->type, pe->src_factor, pe->dst_factor,
                              pe->logic_op);
        HSD_StateSetZMode(pe->flags & 0x10, pe->z_comp, pe->flags & 0x20);
        HSD_StateSetZCompLoc(pe->flags & 8);
        HSD_StateSetAlphaCompare(pe->alpha_comp0, pe->ref0, pe->alpha_op,
                                 pe->alpha_comp1, pe->ref1);
        HSD_StateSetDither(pe->flags & 0x40);
        return;
    }
    HSD_StateSetColorUpdate(1);
    HSD_StateSetAlphaUpdate(0);
    HSD_StateSetDstAlpha(0, 0U);
    if (flags & 0x40000000) {
        var_r3 = 1;
    } else {
        var_r3 = 0;
    }
    HSD_StateSetBlendMode(var_r3, 4U, 5U, 0xFU);
    var_r3_2 = (flags & 0x20000000) ? GX_FALSE : GX_TRUE;
    HSD_StateSetZMode(1, (flags & 0x08000000) ? 7 : 3, var_r3_2);
    if (!(flags & 0x20000000) && (flags & 0x40000000)) {
        HSD_StateSetZCompLoc(0);
        HSD_StateSetAlphaCompare(4U, 0U, 0U, 4U, 0U);
    } else {
        HSD_StateSetZCompLoc(1);
        HSD_StateSetAlphaCompare(7U, 0U, 0U, 7U, 0U);
    }
    HSD_StateSetDither(0);
}

static inline void setupTevMode_last(void)
{
    if (!HSD_StateGetNumTevStages()) {
        HSD_TevDesc tevdesc;
        tevdesc.flags = 0;
        tevdesc.stage = HSD_StateAssignTev();
        tevdesc.coord = 0xFF;
        tevdesc.map = GX_TEXMAP_NULL;
        tevdesc.color = GX_COLOR0A0;
        tevdesc.u.tevop.tevmode = GX_PASSCLR;
        HSD_SetupTevStage(&tevdesc);
    }
}

void HSD_SetupRenderModeWithCustomPE(u32 rendermode, HSD_PEDesc* pe)
{
    setupTevMode_last();
    HSD_SetupPEMode(rendermode, pe);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_SetupChannelMode(rendermode);
}

void HSD_SetMaterialColor(GXColor ambient, GXColor diffuse, GXColor specular,
                          f32 alpha)
{
    matstate.ambient = ambient;
    matstate.diffuse = diffuse;
    matstate.specular = specular;
    alpha = alpha <= 0.0f ? 0.0f : alpha >= 1.0f ? 1.0f : alpha;
    matstate.alpha = 255.0f * alpha;
}

void HSD_SetMaterialShininess(f32 shininess)
{
    matstate.shininess = shininess;
}

static inline void HSD_StateSetLineWidth(u8 arg0, int arg1)
{
    if (state_line_width != arg0 || state_line_tex_offsets != arg1) {
        GXSetLineWidth(arg0, arg1);
        state_line_width = arg0;
        state_line_tex_offsets = arg1;
    }
}

void HSD_StateSetCullMode(int mode)
{
    if (state_cull_mode != mode) {
        GXSetCullMode(mode);
        state_cull_mode = mode;
    }
}

static inline void HSD_StateSetBlendMode(int type, int src_factor, int dst_factor, int op)
{
    if (state_blend_type != type || state_src_factor != src_factor ||
        state_dst_factor != dst_factor || state_logic_op != op)
    {
        GXSetBlendMode(type, src_factor, dst_factor, op);
        state_blend_type = type;
        state_src_factor = src_factor;
        state_dst_factor = dst_factor;
        state_logic_op = op;
    }
}

static inline void HSD_StateSetZMode(u32 arg0, int arg1, u32 arg2)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    arg2 = arg2 ? GX_TRUE : GX_FALSE;

    if (state_z_enable != arg0 || state_z_func != arg1 ||
        state_z_update != arg2)
    {
        GXSetZMode(arg0, arg1, arg2);
        state_z_enable = arg0;
        state_z_func = arg1;
        state_z_update = arg2;
    }
}

static inline void HSD_StateSetPointSize(u8 arg0, int arg1)
{
    if (state_point_size != arg0 || HSD_State_804D75BC != arg1) {
        GXSetPointSize(arg0, arg1);
        state_point_size = arg0;
        HSD_State_804D75BC = arg1;
    }
}

static inline void HSD_StateSetAlphaCompare(int arg0, u8 arg1, int arg2, int arg3, u8 arg4)
{
    if (state_alpha_comp0 != arg0 || state_alpha_ref0 != arg1 ||
        state_alpha_op != arg2 || state_alpha_comp1 != arg3 ||
        state_alpha_ref1 != arg4)
    {
        GXSetAlphaCompare(arg0, arg1, arg2, arg3, arg4);
        state_alpha_comp0 = arg0;
        state_alpha_ref0 = arg1;
        state_alpha_op = arg2;
        state_alpha_comp1 = arg3;
        state_alpha_ref1 = arg4;
    }
}

static inline void HSD_StateSetColorUpdate(u32 arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_color_update != arg0) {
        GXSetColorUpdate(arg0);
        state_color_update = arg0;
    }
}

static inline void HSD_StateSetAlphaUpdate(u32 arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_alpha_update != arg0) {
        GXSetAlphaUpdate(arg0);
        state_alpha_update = arg0;
    }
}

static inline void HSD_StateSetDstAlpha(u32 arg0, u8 arg1)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_enable_dst_alpha != arg0 || state_dst_alpha != arg1) {
        GXSetDstAlpha(arg0, arg1);
        state_enable_dst_alpha = arg0;
        state_dst_alpha = arg1;
    }
}

static inline void HSD_StateSetZCompLoc(u32 arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_before_tex != arg0) {
        GXSetZCompLoc(arg0);
        state_before_tex = (u8) arg0;
    }
}

static inline void HSD_StateSetDither(u32 arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_dither != arg0) {
        GXSetDither(arg0);
        state_dither = arg0;
    }
}

static void _HSD_StateInvalidatePrimitive(void)
{
    state_point_size = 0;
    state_cull_mode = -1;
    state_line_width = 255;
}

static void _HSD_StateInvalidateVtxAttr(void)
{
    HSD_ClearVtxDesc();
}

static void _HSD_StateInvalidateRenderMode(void)
{
    state_blend_type = -1;
    state_src_factor = -1;
    state_dst_factor = -1;
    state_logic_op = -1;
    state_z_enable = -1;
    state_z_func = -1;
    state_z_update = -1;
    state_alpha_comp0 = -1;
    state_alpha_ref0 = 0;
    state_alpha_op = -1;
    state_alpha_comp1 = -1;
    state_alpha_ref1 = 0;
    state_color_update = -1;
    state_alpha_update = -1;
    state_enable_dst_alpha = -1;
    state_dst_alpha = 0;
    state_before_tex = -1;
    state_dither = -1;
}

void HSD_StateInvalidate(int mask)
{
static struct invalidate_funcs_t {
    int mask;
    void (*func)(void);
} invalidate_funcs[] = {
    { HSD_STATE_PRIMITIVE, _HSD_StateInvalidatePrimitive },
    { HSD_STATE_VTX_ATTR, _HSD_StateInvalidateVtxAttr },
    { HSD_STATE_COLOR_CHANNEL, _HSD_StateInvalidateColorChannel },
    { HSD_STATE_TEV_STAGE, _HSD_StateInvalidateTevStage },
    { HSD_STATE_TEV_REGISTER, _HSD_StateInvalidateTevRegister },
    { HSD_STATE_TEX_COORD_GEN, _HSD_StateInvalidateTexCoordGen },
    { HSD_STATE_RENDER_MODE, _HSD_StateInvalidateRenderMode },
    { HSD_STATE_NONE }
};


    int i;
    for (i = 0; invalidate_funcs[i].mask != HSD_STATE_NONE; i++) {
        if (mask & invalidate_funcs[i].mask) {
            invalidate_funcs[i].func();
        }
    }
}
