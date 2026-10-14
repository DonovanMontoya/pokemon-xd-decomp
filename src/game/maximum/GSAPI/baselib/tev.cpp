/* XD GX TEV stage and color-channel state cache. */
#include "game/maximum/GSAPI/baselib/tev.h"
void* memcpy(void*, const void*, unsigned long);
void __assert(const char*, int, const char*);
#define HSD_ASSERT(line, cond) ((cond) ? (void)0 : __assert("tev.c", line, #cond))
#define bool int
static inline int HSD_Channel2Num(int);
static inline int HSD_TevStage2Num(int);
static inline int HSD_TexCoordID2Num(int);
static inline int HSD_TevStage2Index(int);
static struct TevReg_t {
    GXColorS10 a;
    int c;
} TevReg[4] = { 0 };

static HSD_Chan prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
};

static HSD_ObjAllocData rd_alloc_data;
static HSD_ObjAllocData reg_alloc_data;
static HSD_ObjAllocData ch_alloc_data;
static u8 _def_swap_tables[4][4];
static u8 _cur_swap_tables[4][4];

static int current_tev;
static int num_tex_gens;
static int prev_num_chans;

static int prev_mat_invalid[2];
static int prev_amb_invalid[2];

void HSD_RenderInitAllocData(void)
{
    HSD_ObjAllocInit(&rd_alloc_data, 28, 4);
    HSD_ObjAllocInit(&reg_alloc_data, 20, 4);
    HSD_ObjAllocInit(&ch_alloc_data, sizeof(HSD_Chan), 4);
}

HSD_ObjAllocData* HSD_RenderGetAllocData(void)
{
    return &rd_alloc_data;
}

HSD_ObjAllocData* HSD_TevRegGetAllocData(void)
{
    return &reg_alloc_data;
}

HSD_ObjAllocData* HSD_ChanGetAllocData(void)
{
    return &ch_alloc_data;
}

static inline bool CompareRGB(GXColor* c0, GXColor* c1)
{
    u32* d0 = (u32*) c0;
    u32* d1 = (u32*) c1;
    return ((*d0 ^ *d1) & 0xFFFFFF00) != 0;
}

static inline bool CompareRGBA(GXColor* c0, GXColor* c1)
{
    u32* d0 = (u32*) c0;
    u32* d1 = (u32*) c1;
    return *d0 != *d1;
}

static inline void CopyRGB(GXColor* dst, GXColor* src)
{
    u32* d = (u32*) dst;
    u32* s = (u32*) src;
    *d = (*d & 0xff) | (*s & 0xffffff00);
}

void HSD_SetupChannel(HSD_Chan* ch)
{
    int idx;
    GXChannelID chan;
    int no;

    if (ch == NULL || ch->chan == GX_COLOR_NULL) {
        return;
    }

    chan = ch->chan;
    idx = chan & 3;
    no = chan & 1;
    if (ch->enable != GX_DISABLE && ch->amb_src == GX_SRC_REG) {
        if (prev_amb_invalid[no] != 0) {
            prev_amb_invalid[no] = 0;
            GXSetChanAmbColor(no + 4, ch->amb_color);
            prev_ch[no].amb_color = ch->amb_color;
        } else if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            if (CompareRGBA(&ch->amb_color, &prev_ch[no].amb_color)) {
                prev_ch[no].amb_color = ch->amb_color;
                goto set_amb;
            }
        } else if (chan == GX_COLOR0 || chan == GX_COLOR1) {
            if (CompareRGB(&ch->amb_color, &prev_ch[no].amb_color)) {
                CopyRGB(&prev_ch[no].amb_color, &ch->amb_color);
                goto set_amb;
            }
        } else if (ch->amb_color.a != prev_ch[no].amb_color.a) {
            prev_ch[no].amb_color.a = ch->amb_color.a;
        set_amb:
            GXSetChanAmbColor(chan, ch->amb_color);
        }
    }

    if (ch->mat_src == GX_SRC_REG) {
        if (prev_mat_invalid[no] != 0) {
            prev_mat_invalid[no] = 0;
            GXSetChanMatColor(no + 4, ch->mat_color);
            prev_ch[no].mat_color = ch->mat_color;
        } else if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            if (CompareRGBA(&ch->mat_color, &prev_ch[no].mat_color)) {
                prev_ch[no].mat_color = ch->mat_color;
                goto set_mat;
            }
        } else if (chan == GX_COLOR0 || chan == GX_COLOR1) {
            if (CompareRGB(&ch->mat_color, &prev_ch[no].mat_color)) {
                CopyRGB(&prev_ch[no].mat_color, &ch->mat_color);
                goto set_mat;
            }
        } else if (ch->mat_color.a != prev_ch[no].mat_color.a) {
            prev_ch[no].mat_color.a = ch->mat_color.a;
        set_mat:
            GXSetChanMatColor(chan, ch->mat_color);
        }
    }

    if ((ch->enable != prev_ch[idx].enable) ||
        (ch->amb_src != prev_ch[idx].amb_src) ||
        (ch->mat_src != prev_ch[idx].mat_src) ||
        (ch->light_mask != prev_ch[idx].light_mask) ||
        (ch->diff_fn != prev_ch[idx].diff_fn) ||
        (ch->attn_fn != prev_ch[idx].attn_fn))
    {
        GXSetChanCtrl(chan, ch->enable, ch->amb_src, ch->mat_src,
                      ch->light_mask, ch->diff_fn, ch->attn_fn);
        prev_ch[idx].enable = ch->enable;
        prev_ch[idx].amb_src = ch->amb_src;
        prev_ch[idx].mat_src = ch->mat_src;
        prev_ch[idx].light_mask = ch->light_mask;
        prev_ch[idx].diff_fn = ch->diff_fn;
        prev_ch[idx].attn_fn = ch->attn_fn;
        if (chan == GX_COLOR0A0 || chan == GX_COLOR1A1) {
            prev_ch[idx + 2].enable = ch->enable;
            prev_ch[idx + 2].amb_src = ch->amb_src;
            prev_ch[idx + 2].mat_src = ch->mat_src;
            prev_ch[idx + 2].light_mask = ch->light_mask;
            prev_ch[idx + 2].diff_fn = ch->diff_fn;
            prev_ch[idx + 2].attn_fn = ch->attn_fn;
        }
    }
}

void HSD_StateSetNumChans(int num)
{
    if (prev_num_chans != num) {
        GXSetNumChans(num);
        prev_num_chans = num;
    }
}

void HSD_SetupChannelAll(HSD_Chan* channel)
{
    int num = 0;
    while (channel != NULL) {
        int temp = HSD_Channel2Num(channel->chan);
        if (temp > num) {
            num = temp;
        }
        HSD_SetupChannel(channel);
        channel = channel->next;
    }
    HSD_StateSetNumChans((u8) num);
}

static inline int HSD_TexCoordID2Num(int);

void HSD_StateRegisterTexGen(int coord)
{
    int temp_r3 = HSD_TexCoordID2Num(coord);
    if (temp_r3 > num_tex_gens) {
        num_tex_gens = temp_r3;
    }
}

void HSD_StateSetNumTexGens(void)
{
    GXSetNumTexGens(num_tex_gens);
    num_tex_gens = 0;
}

void HSD_StateInitTev(void)
{
    current_tev = 0;
}

int HSD_StateGetNumTevStages(void)
{
    return current_tev;
}

int HSD_StateAssignTev(void)
{
    return HSD_Index2TevStage(current_tev++);
}

void HSD_StateSetNumTevStages(void)
{
    GXSetNumTevStages(current_tev);
    current_tev = 0;
}

void HSD_SetupTevStage(HSD_TevDesc* desc)
{
    GXSetTevOrder(desc->stage, desc->coord, desc->map, desc->color);
    if (desc->flags == 0) {
        GXSetTevOp(desc->stage, (GXTevMode) desc->u.tevconf.clr_op);
        GXSetTevSwapMode(desc->stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        return;
    }
    GXSetTevColorOp(desc->stage, desc->u.tevconf.clr_op,
                    desc->u.tevconf.clr_bias, desc->u.tevconf.clr_scale,
                    desc->u.tevconf.clr_clamp, desc->u.tevconf.clr_out_reg);
    GXSetTevColorIn(desc->stage, desc->u.tevconf.clr_a, desc->u.tevconf.clr_b,
                    desc->u.tevconf.clr_c, desc->u.tevconf.clr_d);
    GXSetTevAlphaOp(desc->stage, desc->u.tevconf.alpha_op,
                    desc->u.tevconf.alpha_bias, desc->u.tevconf.alpha_scale,
                    desc->u.tevconf.alpha_clamp,
                    desc->u.tevconf.alpha_out_reg);
    GXSetTevAlphaIn(desc->stage, desc->u.tevconf.alpha_a,
                    desc->u.tevconf.alpha_b, desc->u.tevconf.alpha_c,
                    desc->u.tevconf.alpha_d);
    GXSetTevSwapModeTable(desc->u.tevconf.ras_swap, desc->u.tevconf.swap_r,
                          desc->u.tevconf.swap_g, desc->u.tevconf.swap_b,
                          desc->u.tevconf.swap_a);
    _cur_swap_tables[desc->u.tevconf.ras_swap][0] = desc->u.tevconf.swap_r;
    _cur_swap_tables[desc->u.tevconf.ras_swap][1] = desc->u.tevconf.swap_g;
    _cur_swap_tables[desc->u.tevconf.ras_swap][2] = desc->u.tevconf.swap_b;
    _cur_swap_tables[desc->u.tevconf.ras_swap][3] = desc->u.tevconf.swap_a;
    if (desc->u.tevconf.tex_swap != desc->u.tevconf.ras_swap) {
        GXSetTevSwapModeTable(desc->u.tevconf.tex_swap, desc->u.tevconf.swap_r,
                              desc->u.tevconf.swap_g, desc->u.tevconf.swap_b,
                              desc->u.tevconf.swap_a);
        _cur_swap_tables[desc->u.tevconf.ras_swap][0] = desc->u.tevconf.swap_r;
        _cur_swap_tables[desc->u.tevconf.ras_swap][1] = desc->u.tevconf.swap_g;
        _cur_swap_tables[desc->u.tevconf.ras_swap][2] = desc->u.tevconf.swap_b;
        _cur_swap_tables[desc->u.tevconf.ras_swap][3] = desc->u.tevconf.swap_a;
    }
    GXSetTevSwapMode(desc->stage, desc->u.tevconf.ras_swap,
                     desc->u.tevconf.tex_swap);
    GXSetTevKColorSel(desc->stage, desc->u.tevconf.kcsel);
    GXSetTevKAlphaSel(desc->stage, desc->u.tevconf.kasel);
}

void HSD_SetupTevStageAll(HSD_TevDesc* desc)
{
    int num = 0;

    while (desc != NULL) {
        int temp = HSD_TevStage2Num(desc->stage);
        if (temp > num) {
            num = temp;
        }

    GXSetTevOrder(desc->stage, desc->coord, desc->map, desc->color);
    if (desc->flags == 0) {
        GXSetTevOp(desc->stage, (GXTevMode) desc->u.tevconf.clr_op);
        GXSetTevSwapMode(desc->stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
        goto stage_done;
    }
    GXSetTevColorOp(desc->stage, desc->u.tevconf.clr_op,
                    desc->u.tevconf.clr_bias, desc->u.tevconf.clr_scale,
                    desc->u.tevconf.clr_clamp, desc->u.tevconf.clr_out_reg);
    GXSetTevColorIn(desc->stage, desc->u.tevconf.clr_a, desc->u.tevconf.clr_b,
                    desc->u.tevconf.clr_c, desc->u.tevconf.clr_d);
    GXSetTevAlphaOp(desc->stage, desc->u.tevconf.alpha_op,
                    desc->u.tevconf.alpha_bias, desc->u.tevconf.alpha_scale,
                    desc->u.tevconf.alpha_clamp,
                    desc->u.tevconf.alpha_out_reg);
    GXSetTevAlphaIn(desc->stage, desc->u.tevconf.alpha_a,
                    desc->u.tevconf.alpha_b, desc->u.tevconf.alpha_c,
                    desc->u.tevconf.alpha_d);
    GXSetTevSwapModeTable(desc->u.tevconf.ras_swap, desc->u.tevconf.swap_r,
                          desc->u.tevconf.swap_g, desc->u.tevconf.swap_b,
                          desc->u.tevconf.swap_a);
    _cur_swap_tables[desc->u.tevconf.ras_swap][0] = desc->u.tevconf.swap_r;
    _cur_swap_tables[desc->u.tevconf.ras_swap][1] = desc->u.tevconf.swap_g;
    _cur_swap_tables[desc->u.tevconf.ras_swap][2] = desc->u.tevconf.swap_b;
    _cur_swap_tables[desc->u.tevconf.ras_swap][3] = desc->u.tevconf.swap_a;
    if (desc->u.tevconf.tex_swap != desc->u.tevconf.ras_swap) {
        GXSetTevSwapModeTable(desc->u.tevconf.tex_swap, desc->u.tevconf.swap_r,
                              desc->u.tevconf.swap_g, desc->u.tevconf.swap_b,
                              desc->u.tevconf.swap_a);
        _cur_swap_tables[desc->u.tevconf.ras_swap][0] = desc->u.tevconf.swap_r;
        _cur_swap_tables[desc->u.tevconf.ras_swap][1] = desc->u.tevconf.swap_g;
        _cur_swap_tables[desc->u.tevconf.ras_swap][2] = desc->u.tevconf.swap_b;
        _cur_swap_tables[desc->u.tevconf.ras_swap][3] = desc->u.tevconf.swap_a;
    }
    GXSetTevSwapMode(desc->stage, desc->u.tevconf.ras_swap,
                     desc->u.tevconf.tex_swap);
    GXSetTevKColorSel(desc->stage, desc->u.tevconf.kcsel);
    GXSetTevKAlphaSel(desc->stage, desc->u.tevconf.kasel);

stage_done:;
        desc = desc->next;
    }
    current_tev = num;
    HSD_StateSetNumTevStages();
}



static inline int HSD_Channel2Num(int chan)
{
    switch (chan) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 1;
    case 3:
        return 2;
    case 4:
        return 1;
    case 5:
        return 2;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(0x31B, 0);
        return 0;
    }
}

int HSD_Index2TevStage(int idx)
{
    switch (idx) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    case 13:
        return 13;
    case 14:
        return 14;
    case 15:
        return 15;
    default:
        HSD_ASSERT(0x350, 0);
        return 15;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
#endif
static inline int HSD_TevStage2Index(int stage)
{
    switch (stage) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 7:
        return 7;
    case 8:
        return 8;
    case 9:
        return 9;
    case 10:
        return 10;
    case 11:
        return 11;
    case 12:
        return 12;
    case 13:
        return 13;
    case 14:
        return 14;
    case 15:
        return 15;
    default:
        HSD_ASSERT(762, 0);
        return 0;
    }
}
#ifdef MUST_MATCH
#pragma pop
#endif

static inline int HSD_TevStage2Num(int stage)
{
    switch (stage) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 8:
        return 9;
    case 9:
        return 10;
    case 10:
        return 11;
    case 11:
        return 12;
    case 12:
        return 13;
    case 13:
        return 14;
    case 14:
        return 15;
    case 15:
        return 16;
    default:
        HSD_ASSERT(0x3A4, 0);
        return 0;
    }
}

void HSD_SetTevRegAll(void)
{
    u32 i;
    for (i = 0; i < 4; i++) {
        if (TevReg[i].c != 0) {
            GXColorS10 color = TevReg[i].a;
            int reg;
            switch (i) {
            case 0:
                reg = 1;
                break;
            case 1:
                reg = 2;
                break;
            case 2:
                reg = 3;
                break;
            case 3:
                reg = 0;
                break;
            default:
                reg = 1;
                break;
            }
            GXSetTevColorS10(reg, color);
            TevReg[i].c = 0;
        }
    }
}

static inline int HSD_TexCoordID2Num(int id)
{
    switch (id) {
    case 0:
        return 1;
    case 1:
        return 2;
    case 2:
        return 3;
    case 3:
        return 4;
    case 4:
        return 5;
    case 5:
        return 6;
    case 6:
        return 7;
    case 7:
        return 8;
    case 0xFF:
        return 0;
    default:
        HSD_ASSERT(0x47D, 0);
        return 0;
    }
}

void _HSD_StateInvalidateColorChannel(void)
{
static HSD_Chan invalid_prev_ch[4] = {
    { NULL, 0, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 1, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 2, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
    { NULL, 3, 0, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, 255, 0, 0, 0, 0, 2, NULL },
};


    memcpy(&prev_ch, &invalid_prev_ch, sizeof(prev_ch));
    prev_amb_invalid[0] = 1;
    prev_amb_invalid[1] = 1;
    prev_mat_invalid[0] = 1;
    prev_mat_invalid[1] = 1;
    prev_num_chans = -1;
}

void _HSD_StateInvalidateTevStage(void)
{
    int i;
    for (i = 0; i < 16; i++) GXSetTevDirect(i);
    GXSetNumIndStages(0);
    current_tev = 0;
}

void _HSD_StateInvalidateTevRegister(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        TevReg[i].c = 0;
    }
}

void _HSD_StateInvalidateTexCoordGen(void)
{
    num_tex_gens = 0;
}


void HSD_InitColorSwapTable(u8 idx, u8 r, u8 g, u8 b, u8 a)
{
    _cur_swap_tables[idx][0] = r;
    _def_swap_tables[idx][0] = r;
    _cur_swap_tables[idx][1] = g;
    _def_swap_tables[idx][1] = g;
    _cur_swap_tables[idx][2] = b;
    _def_swap_tables[idx][2] = b;
    _cur_swap_tables[idx][3] = a;
    _def_swap_tables[idx][3] = a;
}
void HSD_ResetColorSwapTables(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        int value = *(int*)_def_swap_tables[i];
        if (value != *(int*)_cur_swap_tables[i]) {
            GXSetTevSwapModeTable(i, _def_swap_tables[i][0], _def_swap_tables[i][1],
                                 _def_swap_tables[i][2], _def_swap_tables[i][3]);
            *(int*)_cur_swap_tables[i] = value;
        }
    }
}
void HSD_DisableChannelLighting(GXChannelID chan)
{
    int idx = chan & 3;
    switch (chan) {
    case GX_COLOR0A0:
    case GX_COLOR1A1:
        if (prev_ch[idx].enable || prev_ch[idx + 2].enable) {
            prev_ch[idx + 2].enable = prev_ch[idx].enable = 0;
            prev_ch[idx + 2].light_mask = prev_ch[idx].light_mask = 0;
            prev_ch[idx + 2].amb_src = prev_ch[idx].amb_src;
            prev_ch[idx + 2].mat_src = prev_ch[idx].mat_src;
            prev_ch[idx + 2].diff_fn = prev_ch[idx].diff_fn;
            prev_ch[idx + 2].attn_fn = prev_ch[idx].attn_fn;
            GXSetChanCtrl(chan, 0, prev_ch[idx].amb_src, prev_ch[idx].mat_src,
                           0, prev_ch[idx].diff_fn, prev_ch[idx].attn_fn);
        }
        break;
    default:
        if (prev_ch[idx].enable) {
            prev_ch[idx].enable = 0;
            prev_ch[idx].light_mask = 0;
            GXSetChanCtrl(chan, 0, prev_ch[idx].amb_src, prev_ch[idx].mat_src,
                           0, prev_ch[idx].diff_fn, prev_ch[idx].attn_fn);
        }
        break;
    }
}
