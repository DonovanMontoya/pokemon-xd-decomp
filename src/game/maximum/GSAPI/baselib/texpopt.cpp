/* XD TEV expression simplification, merging, and range propagation. */
#include "game/maximum/GSAPI/baselib/texpopt.h"
#define bool int
#define false 0
#define true 1
static int SimplifySrc(HSD_TExp*);
static int SimplifyThis(HSD_TExp*);
int SimplifyByMerge(HSD_TExp*);
static void CalcTevRange(HSD_TExp*);
static HSD_TEArg TE_ARG_ZERO = { 0x00, 0x07, 0xFF };

static int SimplifySrc(HSD_TExp* arg0)
{
    int i;
    bool result;

    result = false;
    i = 0;

    for (; i < 4; i++) {
        if (arg0->tev.c_in[i].type == HSD_TE_TEV) {
            HSD_TExp* src = arg0->tev.c_in[i].exp;
            u8 sel = arg0->tev.c_in[i].sel;
            if (HSD_TExpSimplify(src) != 0) {
                result = true;
            }
            if (sel == HSD_TE_RGB) {
                switch (src->tev.c_op) {
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = true;
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                    break;
                case GX_TEV_ADD:
                    if (src->tev.c_in[0].sel == HSD_TE_0 &&
                        src->tev.c_in[1].sel == HSD_TE_0 &&
                        src->tev.c_bias == 0 && src->tev.c_scale == 0)
                    {
                        switch (src->tev.c_in[3].type) {
                        case HSD_TE_IMM:
                            arg0->tev.c_in[i] = src->tev.c_in[3];
                            HSD_TExpRef(arg0->tev.c_in[i].exp, arg0->tev.c_in[i].sel);
                            HSD_TExpUnref(src, sel);
                            result = true;
                            break;
                        case HSD_TE_TEV:
                            if (i == 3 && src->tev.c_clamp != 0 && src->tev.c_range == 1) break;
                            arg0->tev.c_in[i] = src->tev.c_in[3];
                            HSD_TExpRef(arg0->tev.c_in[i].exp, arg0->tev.c_in[i].sel);
                            HSD_TExpUnref(src, sel);
                            result = true;
                            break;
                        case HSD_TE_TEX:
                            if ((arg0->tev.tex == NULL ||
                                 arg0->tev.tex == src->tev.tex) &&
                                (arg0->tev.tex_swap == 0xFF ||
                                 src->tev.tex_swap == 0xFF ||
                                 arg0->tev.tex_swap == src->tev.tex_swap))
                            {
                                arg0->tev.c_in[i] = src->tev.c_in[3];
                                arg0->tev.tex = src->tev.tex;
                                if (arg0->tev.tex_swap == 0xFF) {
                                    arg0->tev.tex_swap = src->tev.tex_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = true;
                            }
                            break;
                        case HSD_TE_RAS:
                            if ((arg0->tev.chan == 0xFF ||
                                 arg0->tev.chan == src->tev.chan) &&
                                (arg0->tev.ras_swap == 0xFF ||
                                 src->tev.ras_swap == 0xFF ||
                                 arg0->tev.ras_swap == src->tev.ras_swap))
                            {
                                arg0->tev.c_in[i] = src->tev.c_in[3];
                                arg0->tev.chan = src->tev.chan;
                                if (arg0->tev.ras_swap == 0xFF) {
                                    arg0->tev.ras_swap = src->tev.ras_swap;
                                }
                                HSD_TExpUnref(src, sel);
                                result = true;
                            }
                            break;
                        }
                    }
                    break;
                }
            } else {
                switch (src->tev.a_op) {
                case GX_TEV_ADD:
                    break;
                case 0xFF:
                    HSD_TExpUnref(src, sel);
                    result = true;
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                    break;
                }
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (arg0->tev.a_in[i].type == HSD_TE_TEV) {
            HSD_TExp* src = arg0->tev.a_in[i].exp;
            u8 sel = arg0->tev.a_in[i].sel;
            HSD_TExpSimplify(src);
            switch (src->tev.a_op) {
            case 0xFF:
                HSD_TExpUnref(src, sel);
                result = true;
                arg0->tev.a_in[i] = TE_ARG_ZERO;
                break;
            case GX_TEV_ADD:
                if (src->tev.a_in[0].sel == HSD_TE_0 &&
                    src->tev.a_in[1].sel == HSD_TE_0 && src->tev.a_bias == 0 &&
                    src->tev.a_scale == 0)
                {
                    switch (src->tev.a_in[3].type) {
                    case HSD_TE_IMM:
                        arg0->tev.a_in[i] = src->tev.a_in[3];
                        HSD_TExpRef(arg0->tev.a_in[i].exp, arg0->tev.a_in[i].sel);
                        HSD_TExpUnref(src, sel);
                        result = true;
                        /* fall through */
                    case HSD_TE_TEV:
                        if (i == 3 && src->tev.a_clamp != 0 && src->tev.a_range == 1) break;
                        arg0->tev.a_in[i] = src->tev.a_in[3];
                        HSD_TExpRef(arg0->tev.a_in[i].exp,
                                    arg0->tev.a_in[i].sel);
                        HSD_TExpUnref(src, sel);
                        result = true;
                        break;
                    case HSD_TE_TEX:
                        if (arg0->tev.tex == NULL ||
                            arg0->tev.tex == src->tev.tex)
                        {
                            arg0->tev.a_in[i] = src->tev.a_in[3];
                            arg0->tev.tex = src->tev.tex;
                            HSD_TExpUnref(src, sel);
                            result = true;
                        }
                        break;
                    case HSD_TE_RAS:
                        if (arg0->tev.chan == 0xFF ||
                            arg0->tev.chan == src->tev.chan)
                        {
                            arg0->tev.a_in[i] = src->tev.a_in[3];
                            arg0->tev.chan = src->tev.chan;
                            HSD_TExpUnref(src, sel);
                            result = true;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    return result;
}

#define CLEAR_ARG(arg)                                                        \
    do {                                                                      \
        (arg) = TE_ARG_ZERO;                                         \
    } while (0)

#define BIAS_TO_INT(bias) ((bias) == 1 ? 1 : ((bias) == 2 ? -1 : 0))
#define INT_TO_BIAS(v) ((v) == 1 ? 1 : ((v) == -1 ? 2 : 0))
#define RESOURCE_CONFLICT(tex_obj, chan_id, src_exp)                          \
    ((((tex_obj) != NULL) && ((src_exp)->tev.tex != NULL) &&                  \
      ((tex_obj) != (src_exp)->tev.tex)) ||                                   \
     (((chan_id) != 0xFF) && ((src_exp)->tev.chan != 0xFF) &&                 \
      ((chan_id) != (src_exp)->tev.chan)))

static int SimplifyThis(HSD_TExp* arg0)
{
    int i;
    int color_tex;
    int alpha_tex;
    int color_ras;
    int alpha_ras;
    int result;
    int changed;
    int op;

    result = 0;
    do {
        color_tex = -1;
        alpha_tex = -1;
        color_ras = -1;
        alpha_ras = -1;

        for (i = 0; i < 4; i++) {
            switch (arg0->tev.c_in[i].type) {
            case HSD_TE_TEX:
                color_tex = i;
                break;
            case HSD_TE_RAS:
                color_ras = i;
                break;
            }
            switch (arg0->tev.a_in[i].type) {
            case HSD_TE_TEX:
                alpha_tex = i;
                break;
            case HSD_TE_RAS:
                alpha_ras = i;
                break;
            }
        }

        if (color_tex == -1 && alpha_tex == -1) {
            arg0->tev.tex = NULL;
            arg0->tev.tex_swap = 0xFF;
        }
        if (color_ras == -1 && alpha_ras == -1) {
            arg0->tev.chan = 0xFF;
            arg0->tev.ras_swap = 0xFF;
        }

        changed = 0;
        if (arg0->tev.a_op == 0xFF || arg0->tev.a_op == 0xE ||
            arg0->tev.a_op == 0xF || (arg0->tev.a_op == 0 || arg0->tev.a_op == 1))
        {
            if (arg0->tev.c_op != 0xFF && arg0->tev.c_ref == 0) {
                arg0->tev.c_op = 0xFF;
                for (i = 0; i < 4; i++) {
                    HSD_TExpUnref(arg0->tev.c_in[i].exp,
                                  arg0->tev.c_in[i].sel);
                    arg0->tev.c_in[i] = TE_ARG_ZERO;
                }
                changed = 1;
            }

            switch (arg0->tev.c_op) {
            case 0:
            case 1:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    if (arg0->tev.c_in[1].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                      arg0->tev.c_in[1].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[1]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[0];
                        CLEAR_ARG(arg0->tev.c_in[0]);
                        arg0->tev.c_clamp = 1;
                    }
                }
                if (arg0->tev.c_in[2].sel == HSD_TE_1) {
                    if (arg0->tev.c_in[0].sel != HSD_TE_0) {
                        HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                      arg0->tev.c_in[0].sel);
                        changed = 1;
                        CLEAR_ARG(arg0->tev.c_in[0]);
                    }
                    if (arg0->tev.c_op == 0 &&
                        arg0->tev.c_in[3].sel == HSD_TE_0)
                    {
                        changed = 1;
                        arg0->tev.c_in[3] = arg0->tev.c_in[1];
                        CLEAR_ARG(arg0->tev.c_in[1]);
                        CLEAR_ARG(arg0->tev.c_in[2]);
                    }
                }
                if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                arg0->tev.c_in[1].sel == HSD_TE_1) {
                arg0->tev.c_in[0] = arg0->tev.c_in[2];
                CLEAR_ARG(arg0->tev.c_in[1]);
                CLEAR_ARG(arg0->tev.c_in[2]);
                changed = 1;
            }
            if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                    arg0->tev.c_in[1].sel == HSD_TE_0 &&
                    arg0->tev.c_in[3].sel == HSD_TE_0 && arg0->tev.c_bias == 0)
                {
                    arg0->tev.c_op = 0xFF;
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 8:
            case 10:
            case 12:
            case 14:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    CLEAR_ARG(arg0->tev.c_in[1]);
                    HSD_TExpUnref(arg0->tev.c_in[2].exp,
                                  arg0->tev.c_in[2].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            case 9:
            case 11:
            case 13:
            case 15:
                if (arg0->tev.c_in[2].sel == HSD_TE_0) {
                    arg0->tev.c_op = 0;
                    HSD_TExpUnref(arg0->tev.c_in[0].exp,
                                  arg0->tev.c_in[0].sel);
                    CLEAR_ARG(arg0->tev.c_in[0]);
                    HSD_TExpUnref(arg0->tev.c_in[1].exp,
                                  arg0->tev.c_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.c_in[1]);
                } else if (arg0->tev.c_in[0].sel == HSD_TE_0 &&
                           arg0->tev.c_in[1].sel == HSD_TE_0)
                {
                    arg0->tev.c_op = 0;
                    changed = 1;
                    arg0->tev.c_in[0] = arg0->tev.c_in[2];
                    CLEAR_ARG(arg0->tev.c_in[2]);
                }
                break;
            }
        }

        if (arg0->tev.a_op != 0xFF && arg0->tev.a_ref == 0) {
            arg0->tev.a_op = 0xFF;
            for (i = 0; i < 4; i++) {
                HSD_TExpUnref(arg0->tev.a_in[i].exp, arg0->tev.a_in[i].sel);
                CLEAR_ARG(arg0->tev.a_in[i]);
            }
            changed = 1;
        }

        switch (arg0->tev.a_op) {
        case 0:
        case 1:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                if (arg0->tev.a_in[1].sel != HSD_TE_0) {
                    HSD_TExpUnref(arg0->tev.a_in[1].exp,
                                  arg0->tev.a_in[1].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.a_in[1]);
                }
                if (arg0->tev.a_op == 0 && arg0->tev.a_in[3].sel == HSD_TE_0) {
                    changed = 1;
                    arg0->tev.a_in[3] = arg0->tev.a_in[0];
                    CLEAR_ARG(arg0->tev.a_in[0]);
                }
            }
            if (arg0->tev.a_in[2].sel == HSD_TE_1) {
                if (arg0->tev.a_in[0].sel != HSD_TE_0) {
                    HSD_TExpUnref(arg0->tev.a_in[0].exp,
                                  arg0->tev.a_in[0].sel);
                    changed = 1;
                    CLEAR_ARG(arg0->tev.a_in[0]);
                }
                if (arg0->tev.a_op == 0 && arg0->tev.a_in[3].sel == HSD_TE_0) {
                    changed = 1;
                    arg0->tev.a_in[3] = arg0->tev.a_in[1];
                    CLEAR_ARG(arg0->tev.a_in[1]);
                    CLEAR_ARG(arg0->tev.a_in[2]);
                }
            }
            if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                arg0->tev.a_in[1].sel == HSD_TE_0 &&
                arg0->tev.a_in[3].sel == HSD_TE_0)
            {
                arg0->tev.a_op = 0xFF;
                changed = 1;
            }
            break;

        case 8:
        case 9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            }
            break;

        case 0xE:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            } else if (arg0->tev.a_in[0].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                CLEAR_ARG(arg0->tev.a_in[1]);
                HSD_TExpUnref(arg0->tev.a_in[2].exp, arg0->tev.a_in[2].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[2]);
            }
            break;

        case 0xF:
            if (arg0->tev.a_in[2].sel == HSD_TE_0) {
                arg0->tev.a_op = 0;
                HSD_TExpUnref(arg0->tev.a_in[0].exp, arg0->tev.a_in[0].sel);
                CLEAR_ARG(arg0->tev.a_in[0]);
                HSD_TExpUnref(arg0->tev.a_in[1].exp, arg0->tev.a_in[1].sel);
                changed = 1;
                CLEAR_ARG(arg0->tev.a_in[1]);
            } else if (arg0->tev.a_in[0].sel == HSD_TE_0 &&
                       arg0->tev.a_in[1].sel == HSD_TE_0)
            {
                arg0->tev.a_op = 0;
                changed = 1;
                arg0->tev.a_in[0] = arg0->tev.a_in[2];
                CLEAR_ARG(arg0->tev.a_in[2]);
            }
            break;
        }

        if (changed != 0) {
            result = 1;
        }
    } while (changed != 0);

    return result;
}

/* XD merges color and alpha inputs after checking range, resource, bias,
 * and scale compatibility. Argument copies retain reference counts. */
int SimplifyByMerge(HSD_TExp *arg0) {
    HSD_TEArg tmp_arg;
    HSD_TExp *temp_r20_2;
    HSD_TExp *temp_r20_3;
    HSD_TExp *temp_r21;
    HSD_TExp *temp_r23;
    HSD_TExp *temp_r3_11;
    HSD_TExp *temp_r4;
    HSD_TExp *var_r23;
    HSD_TExp *var_r23_2;
    HSD_TExp *var_r23_3;
    HSD_TExp *var_r23_4;
    HSD_TExp *var_r24;
    HSD_TExp *var_r24_2;
    HSD_TExp *var_r24_3;
    HSD_TExp *var_r24_4;
    HSD_TExp *var_r24_5;
    HSD_TExp *var_r25;
    HSD_TExp *var_r26_2;
    HSD_TExp *var_r26_3;
    HSD_TExp *var_r26_4;
    HSD_TExp *var_r30_2;
    HSD_TObj *temp_r0_16;
    HSD_TObj *temp_r0_5;
    HSD_TObj *temp_r3_14;
    HSD_TObj *temp_r3_4;
    HSD_TObj *temp_r4_5;
    HSD_TObj *temp_r4_7;
    HSD_TObj *temp_r5;
    HSD_TObj *temp_r5_10;
    HSD_TObj *temp_r5_4;
    HSD_TObj *temp_r5_8;
    HSD_TObj *temp_r6;
    HSD_TObj *temp_r6_3;
    s32 temp_r0_11;
    s32 temp_r0_15;
    s32 temp_r0_19;
    s32 temp_r0_22;
    s32 temp_r0_4;
    s32 temp_r0_8;
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_11;
    s32 var_r0_12;
    s32 var_r0_13;
    s32 var_r0_14;
    s32 var_r0_15;
    s32 var_r0_16;
    s32 var_r0_17;
    s32 var_r0_18;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 var_r22;
    s32 var_r22_2;
    s32 var_r22_3;
    s32 var_r22_4;
    s32 var_r22_5;
    s32 var_r22_6;
    s32 var_r30;
    s32 var_r31;
    s32 var_r3;
    s32 var_r3_10;
    s32 var_r3_11;
    s32 var_r3_12;
    s32 var_r3_13;
    s32 var_r3_14;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r3_6;
    s32 var_r3_7;
    s32 var_r3_8;
    s32 var_r3_9;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r5;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r6;
    s32 var_r6_2;
    s32 var_r6_3;
    s32 var_r6_4;
    u32 temp_r3_10;
    u32 temp_r3_13;
    u32 temp_r3_17;
    u32 temp_r3_19;
    u32 temp_r3_3;
    u32 temp_r3_7;
    u8 temp_r0;
    u8 temp_r0_10;
    u8 temp_r0_12;
    u8 temp_r0_13;
    u8 temp_r0_14;
    u8 temp_r0_17;
    u8 temp_r0_18;
    u8 temp_r0_20;
    u8 temp_r0_21;
    u8 temp_r0_2;
    u8 temp_r0_3;
    u8 temp_r0_6;
    u8 temp_r0_7;
    u8 temp_r0_9;
    u8 temp_r20;
    u8 temp_r21_2;
    u8 temp_r21_3;
    u8 temp_r25;
    u8 temp_r25_2;
    u8 temp_r25_3;
    u8 temp_r3;
    u8 temp_r3_12;
    u8 temp_r3_15;
    u8 temp_r3_16;
    u8 temp_r3_18;
    u8 temp_r3_2;
    u8 temp_r3_5;
    u8 temp_r3_6;
    u8 temp_r3_8;
    u8 temp_r3_9;
    u8 temp_r4_10;
    u8 temp_r4_11;
    u8 temp_r4_3;
    u8 temp_r4_4;
    u8 temp_r4_6;
    u8 temp_r4_8;
    u8 temp_r5_11;
    u8 temp_r5_13;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_5;
    u8 temp_r5_7;
    u8 temp_r5_9;
    u8 temp_r6_2;
    u8 temp_r6_4;
    u8 temp_r6_5;
    u8 temp_r6_6;
    u8 temp_r7;
    u8 temp_r7_2;
    u8 var_r25_2;
    u8 var_r26;
    u8 var_r28;
    u8 var_r29;

    var_r31 = 0;
    do {
        temp_r7 = arg0->tev.c_op;
        var_r30 = 0;
        if (((temp_r7 == 0) || (temp_r7 == 1)) && ((u8) arg0->tev.c_in[2].sel == 7)) {
            temp_r3 = arg0->tev.c_in[0].type;
            temp_r4 = arg0->tev.c_in[0].exp;
            temp_r0 = arg0->tev.c_in[0].sel;
            var_r25 = temp_r4;
            var_r26 = temp_r0;
            if ((temp_r3 == 1) && (temp_r0 == 1) && ((u8) temp_r4->tev.c_range == 0) && ((u8) temp_r4->tev.c_in[3].sel == 7)) {
                temp_r6 = arg0->tev.tex;
                if ((temp_r6 != NULL) && (temp_r5 = temp_r4->tev.tex, ((temp_r5 == NULL) == 0)) && (temp_r6 != temp_r5)) {
                    var_r5 = 1;
                } else {
                    temp_r6_2 = arg0->tev.chan;
                    if ((temp_r6_2 != 0xFF) && (temp_r5_2 = var_r25->tev.chan, ((temp_r5_2 == 0xFF) == 0)) && (temp_r6_2 != temp_r5_2)) {
                        var_r5 = 1;
                    } else {
                        var_r5 = 0;
                    }
                }
                if (var_r5 == 0) {
                    var_r6 = 0;
                    if ((temp_r3 == 4) || ((u8) arg0->tev.c_in[1].type == 4) || ((u8) arg0->tev.c_in[2].type == 4) || ((u8) arg0->tev.c_in[3].type == 4)) {
                        var_r6 = 1;
                    }
                    if (var_r6 != 0) {
                        var_r6_2 = 0;
                        if (((u8) var_r25->tev.c_in[0].type == 4) || ((u8) var_r25->tev.c_in[1].type == 4) || ((u8) var_r25->tev.c_in[2].type == 4) || ((u8) var_r25->tev.c_in[3].type == 4)) {
                            var_r6_2 = 1;
                        }
                        if (var_r6_2 != 0) {
                            goto block_30;
                        }
                        goto block_65;
                    }
                    goto block_65;
                }
                goto block_30;
            }
block_30:
            temp_r5_3 = arg0->tev.c_in[3].sel;
            var_r25 = arg0->tev.c_in[3].exp;
            var_r26 = temp_r5_3;
            if (temp_r7 == 0) {
                temp_r7_2 = arg0->tev.c_in[3].type;
                if ((temp_r7_2 == 1) && (temp_r5_3 == 1) && ((u8) var_r25->tev.c_range == 0) && ((u8) var_r25->tev.c_in[3].sel == 7)) {
                    temp_r6_3 = arg0->tev.tex;
                    if ((temp_r6_3 != NULL) && (temp_r5_4 = var_r25->tev.tex, ((temp_r5_4 == NULL) == 0)) && (temp_r6_3 != temp_r5_4)) {
                        var_r5_2 = 1;
                    } else {
                        temp_r6_4 = arg0->tev.chan;
                        if ((temp_r6_4 != 0xFF) && (temp_r5_5 = var_r25->tev.chan, ((temp_r5_5 == 0xFF) == 0)) && (temp_r6_4 != temp_r5_5)) {
                            var_r5_2 = 1;
                        } else {
                            var_r5_2 = 0;
                        }
                    }
                    if (var_r5_2 == 0) {
                        var_r6_3 = 0;
                        if ((temp_r3 == 4) || ((u8) arg0->tev.c_in[1].type == 4) || ((u8) arg0->tev.c_in[2].type == 4) || (temp_r7_2 == 4)) {
                            var_r6_3 = 1;
                        }
                        if (var_r6_3 != 0) {
                            var_r6_4 = 0;
                            if (((u8) var_r25->tev.c_in[0].type == 4) || ((u8) var_r25->tev.c_in[1].type == 4) || ((u8) var_r25->tev.c_in[2].type == 4) || ((u8) var_r25->tev.c_in[3].type == 4)) {
                                var_r6_4 = 1;
                            }
                            if (var_r6_4 == 0) {
                                goto block_57;
                            }
                        } else {
block_57:
                            if (temp_r3 == 1) {
                                if (temp_r0 == 1) {
                                    if ((u8) temp_r4->tev.c_range != 0) {
                                        if ((u8) temp_r4->tev.c_clamp == 1) {
                                            goto block_64;
                                        }
                                    } else {
                                        goto block_64;
                                    }
                                } else if (((u8) temp_r4->tev.a_range == 0) || ((u8) temp_r4->tev.a_clamp == 1)) {
                                    goto block_64;
                                }
                            } else {
block_64:
                                tmp_arg = arg0->tev.c_in[0];
                                arg0->tev.c_in[0] = arg0->tev.c_in[3];
                                arg0->tev.c_in[3] = tmp_arg;
block_65:
                                temp_r3_2 = var_r25->tev.c_scale;
                                if (temp_r3_2 == 0) {
                                    temp_r0_2 = var_r25->tev.c_bias;
                                    temp_r5_7 = arg0->tev.c_bias;
                                    switch ((s32) temp_r0_2) {
                                    case 1:
                                        var_r3 = 1;
                                        break;
                                    case 2:
                                        var_r3 = -1;
                                        break;
                                    default:
                                        var_r3 = 0;
                                        break;
                                    }
                                    if ((s32) arg0->tev.c_op == 1) {
                                        var_r3 = -var_r3;
                                    }
                                    switch ((s32) temp_r5_7) {
                                    case 1:
                                        var_r3 += 1;
                                        break;
                                    case 2:
                                        var_r3 -= 1;
                                        break;
                                    }
                                    switch (var_r3) {
                                    case 0:
                                        var_r29 = 0;
                                        var_r0 = 1;
                                        break;
                                    case 1:
                                        var_r29 = 1;
                                        var_r0 = 1;
                                        break;
                                    case -1:
                                        var_r29 = 2;
                                        var_r0 = 1;
                                        break;
                                    default:
                                        var_r0 = 0;
                                        break;
                                    }
                                    if (var_r0 != 0) {
                                        var_r28 = arg0->tev.c_scale;
                                        goto block_135;
                                    }
                                } else if (((u8) arg0->tev.c_in[3].sel == 7) && ((u8) arg0->tev.c_bias == 0)) {
                                    temp_r0_3 = arg0->tev.c_scale;
                                    switch ((s32) temp_r0_3) {
                                    case 0:
                                        var_r0_2 = 2;
                                        break;
                                    case 1:
                                        var_r0_2 = 4;
                                        break;
                                    case 2:
                                        var_r0_2 = 8;
                                        break;
                                    case 3:
                                        var_r0_2 = 1;
                                        break;
                                    default:
                                        var_r0_2 = 2;
                                        break;
                                    }
                                    switch ((s32) temp_r3_2) {
                                    case 0:
                                        var_r3_2 = 2;
                                        break;
                                    case 1:
                                        var_r3_2 = 4;
                                        break;
                                    case 2:
                                        var_r3_2 = 8;
                                        break;
                                    case 3:
                                        var_r3_2 = 1;
                                        break;
                                    default:
                                        var_r3_2 = 2;
                                        break;
                                    }
                                    temp_r3_3 = var_r0_2 * var_r3_2;
                                    temp_r0_4 = (s32) ((temp_r3_3 >> 0x1FU) + temp_r3_3) >> 1;
                                    switch (temp_r0_4) {
                                    case 1:
                                        var_r28 = 3;
block_132:
                                        var_r0_3 = 1;
                                        break;
                                    case 2:
                                        var_r28 = 0;
                                        goto block_132;
                                    case 4:
                                        var_r28 = 1;
                                        goto block_132;
                                    case 8:
                                        var_r28 = 2;
                                        goto block_132;
                                    default:
                                        var_r0_3 = 0;
                                        break;
                                    }
                                    if (var_r0_3 != 0) {
                                        var_r29 = var_r25->tev.c_bias;
block_135:
                                        if ((u8) arg0->tev.c_op == 1) {
                                            arg0->tev.c_op = var_r25->tev.c_op == 0;
                                        } else {
                                            arg0->tev.c_op = var_r25->tev.c_op;
                                        }
                                        var_r30_2 = var_r25;
                                        var_r24 = arg0;
                                        var_r22 = 0;
                                        do {
                                            var_r24->tev.c_in[0] = var_r30_2->tev.c_in[0];
                                            HSD_TExpRef(var_r24->tev.c_in[0].exp, var_r24->tev.c_in[0].sel);
                                            var_r22 += 1;
                                            var_r24 = (HSD_TExp*) ((char*) var_r24 + 8);
                                            var_r30_2 = (HSD_TExp*) ((char*) var_r30_2 + 8);
                                        } while (var_r22 < 3);
                                        arg0->tev.c_bias = var_r29;
                                        arg0->tev.c_scale = var_r28;
                                        HSD_TExpUnref(var_r25, var_r26);
                                        if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                            arg0->tev.tex = var_r25->tev.tex;
                                        }
                                        if ((u8) arg0->tev.chan == 0xFF) {
                                            arg0->tev.chan = var_r25->tev.chan;
                                        }
                                        if ((u8) arg0->tev.tex_swap == 0xFF) {
                                            arg0->tev.tex_swap = var_r25->tev.tex_swap;
                                        }
                                        if ((u8) arg0->tev.ras_swap == 0xFF) {
                                            arg0->tev.ras_swap = var_r25->tev.ras_swap;
                                        }
                                        var_r30 = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        temp_r4_3 = arg0->tev.c_in[3].type;
        var_r26_2 = arg0->tev.c_in[3].exp;
        temp_r25 = arg0->tev.c_in[3].sel;
        if ((temp_r4_3 == 1) && (temp_r25 == 1)) {
            temp_r3_4 = arg0->tev.tex;
            if ((temp_r3_4 != NULL) && (temp_r0_5 = var_r26_2->tev.tex, ((temp_r0_5 == NULL) == 0)) && (temp_r3_4 != temp_r0_5)) {
                var_r0_4 = 1;
            } else {
                temp_r3_5 = arg0->tev.chan;
                if ((temp_r3_5 != 0xFF) && (temp_r0_6 = var_r26_2->tev.chan, ((temp_r0_6 == 0xFF) == 0)) && (temp_r3_5 != temp_r0_6)) {
                    var_r0_4 = 1;
                } else {
                    var_r0_4 = 0;
                }
            }
            if (var_r0_4 == 0) {
                var_r3_3 = 0;
                if (((u8) arg0->tev.c_in[0].type == 4) || ((u8) arg0->tev.c_in[1].type == 4) || ((u8) arg0->tev.c_in[2].type == 4) || (temp_r4_3 == 4)) {
                    var_r3_3 = 1;
                }
                if (var_r3_3 != 0) {
                    var_r3_4 = 0;
                    if (((u8) var_r26_2->tev.c_in[0].type == 4) || ((u8) var_r26_2->tev.c_in[1].type == 4) || ((u8) var_r26_2->tev.c_in[2].type == 4) || ((u8) var_r26_2->tev.c_in[3].type == 4)) {
                        var_r3_4 = 1;
                    }
                    if (var_r3_4 == 0) {
                        goto block_173;
                    }
                } else {
block_173:
                    if (((u8) var_r26_2->tev.c_range != 0) && ((u8) var_r26_2->tev.c_clamp == 1)) {
                        if (((u8) arg0->tev.c_in[0].sel == 7) && ((u8) arg0->tev.c_in[2].sel == 7) && ((u8) arg0->tev.c_bias == 0)) {
                            temp_r3_6 = arg0->tev.c_scale;
                            if (temp_r3_6 != 3) {
                                temp_r0_7 = var_r26_2->tev.c_scale;
                                switch ((s32) temp_r3_6) {
                                case 0:
                                    var_r3_5 = 2;
                                    break;
                                case 1:
                                    var_r3_5 = 4;
                                    break;
                                case 2:
                                    var_r3_5 = 8;
                                    break;
                                case 3:
                                    var_r3_5 = 1;
                                    break;
                                default:
                                    var_r3_5 = 2;
                                    break;
                                }
                                switch ((s32) temp_r0_7) {
                                case 0:
                                    var_r0_5 = 2;
                                    break;
                                case 1:
                                    var_r0_5 = 4;
                                    break;
                                case 2:
                                    var_r0_5 = 8;
                                    break;
                                case 3:
                                    var_r0_5 = 1;
                                    break;
                                default:
                                    var_r0_5 = 2;
                                    break;
                                }
                                temp_r3_7 = var_r3_5 * var_r0_5;
                                temp_r0_8 = (s32) ((temp_r3_7 >> 0x1FU) + temp_r3_7) >> 1;
                                switch (temp_r0_8) {
                                case 1:
                                    var_r28 = 3;
block_216:
                                    var_r0_6 = 1;
                                    break;
                                case 2:
                                    var_r28 = 0;
                                    goto block_216;
                                case 4:
                                    var_r28 = 1;
                                    goto block_216;
                                case 8:
                                    var_r28 = 2;
                                    goto block_216;
                                default:
                                    var_r0_6 = 0;
                                    break;
                                }
                                if (var_r0_6 != 0) {
                                    var_r30 = 1;
                                    arg0->tev.c_bias = var_r26_2->tev.c_bias;
                                    arg0->tev.c_scale = var_r28;
                                    if ((u8) arg0->tev.c_clamp != 1) {
                                        arg0->tev.c_clamp = var_r26_2->tev.c_clamp;
                                    }
                                    if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                        arg0->tev.tex = var_r26_2->tev.tex;
                                    }
                                    if ((u8) arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = var_r26_2->tev.chan;
                                    }
                                    if ((u8) arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap = var_r26_2->tev.tex_swap;
                                    }
                                    if ((u8) arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap = var_r26_2->tev.ras_swap;
                                    }
                                    var_r24_2 = arg0;
                                    var_r22_2 = 0;
                                    do {
                                        temp_r23 = var_r24_2->tev.c_in[0].exp;
                                        temp_r25_2 = var_r24_2->tev.c_in[0].sel;
                                        var_r24_2->tev.c_in[0] = var_r26_2->tev.c_in[0];
                                        HSD_TExpRef(var_r24_2->tev.c_in[0].exp, var_r24_2->tev.c_in[0].sel);
                                        HSD_TExpUnref(temp_r23, temp_r25_2);
                                        var_r22_2 += 1;
                                        var_r26_2 = (HSD_TExp*) ((char*) var_r26_2 + 8);
                                        var_r24_2 = (HSD_TExp*) ((char*) var_r24_2 + 8);
                                    } while (var_r22_2 < 4);
                                }
                            }
                        }
                    } else {
                        temp_r3_8 = arg0->tev.a_op;
                        if ((temp_r3_8 == 0xFF) || ((u8) (temp_r3_8 - 0xE) <= 1U) || (temp_r3_8 <= 1U) || (((u8) var_r26_2->tev.c_in[0].sel == 7) && ((u8) var_r26_2->tev.c_in[1].sel == 7) && ((u8) var_r26_2->tev.c_in[2].sel == 7))) {
                            temp_r3_9 = var_r26_2->tev.c_scale;
                            if (temp_r3_9 == 0) {
                                if ((((u8) arg0->tev.c_in[0].sel == 7) && ((u8) arg0->tev.c_in[2].sel == 7)) || (((u8) var_r26_2->tev.c_in[0].sel == 7) && ((u8) var_r26_2->tev.c_in[2].sel == 7))) {
                                    temp_r0_9 = var_r26_2->tev.c_bias;
                                    temp_r4_4 = arg0->tev.c_bias;
                                    switch ((s32) temp_r0_9) {
                                    case 1:
                                        var_r3_6 = 1;
                                        break;
                                    case 2:
                                        var_r3_6 = -1;
                                        break;
                                    default:
                                        var_r3_6 = 0;
                                        break;
                                    }
                                    switch ((s32) temp_r4_4) {
                                    case 1:
                                        var_r3_6 += 1;
                                        break;
                                    case 2:
                                        var_r3_6 -= 1;
                                        break;
                                    }
                                    switch (var_r3_6) {
                                    case 0:
                                        var_r29 = 0;
                                        var_r0_7 = 1;
                                        break;
                                    case 1:
                                        var_r29 = 1;
                                        var_r0_7 = 1;
                                        break;
                                    case -1:
                                        var_r29 = 2;
                                        var_r0_7 = 1;
                                        break;
                                    default:
                                        var_r0_7 = 0;
                                        break;
                                    }
                                    if (var_r0_7 != 0) {
                                        var_r28 = arg0->tev.c_scale;
                                        goto block_311;
                                    }
                                }
                            } else if (((u8) arg0->tev.c_in[0].sel == 7) && ((u8) arg0->tev.c_in[1].sel == 7) && ((u8) arg0->tev.c_in[2].sel == 7) && ((u8) arg0->tev.c_bias == 0)) {
                                temp_r0_10 = arg0->tev.c_scale;
                                switch ((s32) temp_r0_10) {
                                case 0:
                                    var_r0_8 = 2;
                                    break;
                                case 1:
                                    var_r0_8 = 4;
                                    break;
                                case 2:
                                    var_r0_8 = 8;
                                    break;
                                case 3:
                                    var_r0_8 = 1;
                                    break;
                                default:
                                    var_r0_8 = 2;
                                    break;
                                }
                                switch ((s32) temp_r3_9) {
                                case 0:
                                    var_r3_7 = 2;
                                    break;
                                case 1:
                                    var_r3_7 = 4;
                                    break;
                                case 2:
                                    var_r3_7 = 8;
                                    break;
                                case 3:
                                    var_r3_7 = 1;
                                    break;
                                default:
                                    var_r3_7 = 2;
                                    break;
                                }
                                temp_r3_10 = var_r0_8 * var_r3_7;
                                temp_r0_11 = (s32) ((temp_r3_10 >> 0x1FU) + temp_r3_10) >> 1;
                                switch (temp_r0_11) {
                                case 1:
                                    var_r28 = 3;
block_308:
                                    var_r0_9 = 1;
                                    break;
                                case 2:
                                    var_r28 = 0;
                                    goto block_308;
                                case 4:
                                    var_r28 = 1;
                                    goto block_308;
                                case 8:
                                    var_r28 = 2;
                                    goto block_308;
                                default:
                                    var_r0_9 = 0;
                                    break;
                                }
                                if (var_r0_9 != 0) {
                                    var_r29 = var_r26_2->tev.c_bias;
block_311:
                                    var_r30 = 1;
                                    *(u32*) &arg0->tev.c_in[3] = (s32) *(u32*) &var_r26_2->tev.c_in[3];
                                    arg0->tev.c_in[3].exp = var_r26_2->tev.c_in[3].exp;
                                    HSD_TExpRef(arg0->tev.c_in[3].exp, arg0->tev.c_in[3].sel);
                                    arg0->tev.c_bias = var_r29;
                                    arg0->tev.c_scale = var_r28;
                                    if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                        arg0->tev.tex = var_r26_2->tev.tex;
                                    }
                                    if ((u8) arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = var_r26_2->tev.chan;
                                    }
                                    if ((u8) arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap = var_r26_2->tev.tex_swap;
                                    }
                                    if ((u8) arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap = var_r26_2->tev.ras_swap;
                                    }
                                    if (((u8) var_r26_2->tev.c_in[0].sel != 7) || ((u8) var_r26_2->tev.c_in[1].sel != 7) || ((u8) var_r26_2->tev.c_in[2].sel != 7)) {
                                        var_r24_3 = arg0;
                                        var_r23 = var_r26_2;
                                        var_r22_3 = 0;
                                        do {
                                            temp_r21 = var_r24_3->tev.c_in[0].exp;
                                            temp_r20 = var_r24_3->tev.c_in[0].sel;
                                            var_r24_3->tev.c_in[0] = var_r23->tev.c_in[0];
                                            HSD_TExpRef(var_r24_3->tev.c_in[0].exp, var_r24_3->tev.c_in[0].sel);
                                            HSD_TExpUnref(temp_r21, temp_r20);
                                            var_r22_3 += 1;
                                            var_r23 = (HSD_TExp*) ((char*) var_r23 + 8);
                                            var_r24_3 = (HSD_TExp*) ((char*) var_r24_3 + 8);
                                        } while (var_r22_3 < 3);
                                    }
                                    HSD_TExpUnref(var_r26_2, temp_r25);
                                }
                            }
                        }
                    }
                }
            }
        }
        temp_r6_5 = arg0->tev.a_op;
        if (((temp_r6_5 == 0) || (temp_r6_5 == 1)) && ((u8) arg0->tev.a_in[2].sel == 7)) {
            temp_r0_12 = arg0->tev.a_in[0].type;
            temp_r3_11 = arg0->tev.a_in[0].exp;
            var_r25_2 = arg0->tev.a_in[0].sel;
            var_r26_3 = temp_r3_11;
            if ((temp_r0_12 == 1) && ((u8) temp_r3_11->tev.a_range == 0) && ((u8) temp_r3_11->tev.a_in[3].sel == 7)) {
                temp_r5_8 = arg0->tev.tex;
                if ((temp_r5_8 != NULL) && (temp_r4_5 = temp_r3_11->tev.tex, ((temp_r4_5 == NULL) == 0)) && (temp_r5_8 != temp_r4_5)) {
                    var_r4 = 1;
                } else {
                    temp_r5_9 = arg0->tev.chan;
                    if ((temp_r5_9 != 0xFF) && (temp_r4_6 = var_r26_3->tev.chan, ((temp_r4_6 == 0xFF) == 0)) && (temp_r5_9 != temp_r4_6)) {
                        var_r4 = 1;
                    } else {
                        var_r4 = 0;
                    }
                }
                if (var_r4 == 0) {
                    var_r5_3 = 0;
                    if ((temp_r0_12 == 4) || ((u8) arg0->tev.a_in[1].type == 4) || ((u8) arg0->tev.a_in[2].type == 4) || ((u8) arg0->tev.a_in[3].type == 4)) {
                        var_r5_3 = 1;
                    }
                    if (var_r5_3 != 0) {
                        var_r5_4 = 0;
                        if (((u8) var_r26_3->tev.a_in[0].type == 4) || ((u8) var_r26_3->tev.a_in[1].type == 4) || ((u8) var_r26_3->tev.a_in[2].type == 4) || ((u8) var_r26_3->tev.a_in[3].type == 4)) {
                            var_r5_4 = 1;
                        }
                        if (var_r5_4 != 0) {
                            goto block_353;
                        }
                        goto block_383;
                    }
                    goto block_383;
                }
                goto block_353;
            }
block_353:
            var_r26_3 = arg0->tev.a_in[3].exp;
            var_r25_2 = arg0->tev.a_in[3].sel;
            if ((temp_r6_5 == 0) && ((u8) arg0->tev.a_in[3].type == 1) && ((u8) var_r26_3->tev.a_range == 0) && ((u8) var_r26_3->tev.a_in[3].sel == 7)) {
                temp_r5_10 = arg0->tev.tex;
                if ((temp_r5_10 != NULL) && (temp_r4_7 = var_r26_3->tev.tex, ((temp_r4_7 == NULL) == 0)) && (temp_r5_10 != temp_r4_7)) {
                    var_r4_2 = 1;
                } else {
                    temp_r5_11 = arg0->tev.chan;
                    if ((temp_r5_11 != 0xFF) && (temp_r4_8 = var_r26_3->tev.chan, ((temp_r4_8 == 0xFF) == 0)) && (temp_r5_11 != temp_r4_8)) {
                        var_r4_2 = 1;
                    } else {
                        var_r4_2 = 0;
                    }
                }
                if (var_r4_2 == 0) {
                    temp_r6_6 = var_r26_3->tev.a_in[0].type;
                    var_r5_5 = 0;
                    if ((temp_r6_6 == 4) || ((u8) var_r26_3->tev.a_in[1].type == 4) || ((u8) var_r26_3->tev.a_in[2].type == 4) || ((u8) var_r26_3->tev.a_in[3].type == 4)) {
                        var_r5_5 = 1;
                    }
                    if (var_r5_5 != 0) {
                        var_r5_6 = 0;
                        if ((temp_r6_6 == 4) || ((u8) var_r26_3->tev.a_in[1].type == 4) || ((u8) var_r26_3->tev.a_in[2].type == 4) || ((u8) var_r26_3->tev.a_in[3].type == 4)) {
                            var_r5_6 = 1;
                        }
                        if (var_r5_6 == 0) {
                            goto block_379;
                        }
                    } else {
block_379:
                        if ((temp_r0_12 != 1) || ((u8) temp_r3_11->tev.a_range == 0) || ((u8) temp_r3_11->tev.a_clamp == 1)) {
                            tmp_arg = arg0->tev.a_in[0];
                                arg0->tev.a_in[0] = arg0->tev.a_in[3];
                                arg0->tev.a_in[3] = tmp_arg;
block_383:
                            temp_r3_12 = var_r26_3->tev.a_scale;
                            if (temp_r3_12 == 0) {
                                temp_r0_13 = var_r26_3->tev.a_bias;
                                temp_r5_13 = arg0->tev.a_bias;
                                switch ((s32) temp_r0_13) {
                                case 1:
                                    var_r3_8 = 1;
                                    break;
                                case 2:
                                    var_r3_8 = -1;
                                    break;
                                default:
                                    var_r3_8 = 0;
                                    break;
                                }
                                if ((s32) arg0->tev.a_op == 1) {
                                    var_r3_8 = -var_r3_8;
                                }
                                switch ((s32) temp_r5_13) {
                                case 1:
                                    var_r3_8 += 1;
                                    break;
                                case 2:
                                    var_r3_8 -= 1;
                                    break;
                                }
                                switch (var_r3_8) {
                                case 0:
                                    var_r29 = 0;
                                    var_r0_10 = 1;
                                    break;
                                case 1:
                                    var_r29 = 1;
                                    var_r0_10 = 1;
                                    break;
                                case -1:
                                    var_r29 = 2;
                                    var_r0_10 = 1;
                                    break;
                                default:
                                    var_r0_10 = 0;
                                    break;
                                }
                                if (var_r0_10 != 0) {
                                    var_r28 = arg0->tev.a_scale;
                                    goto block_453;
                                }
                            } else if (((u8) arg0->tev.a_in[3].sel == 7) && ((u8) arg0->tev.a_bias == 0)) {
                                temp_r0_14 = arg0->tev.a_scale;
                                switch ((s32) temp_r0_14) {
                                case 0:
                                    var_r0_11 = 2;
                                    break;
                                case 1:
                                    var_r0_11 = 4;
                                    break;
                                case 2:
                                    var_r0_11 = 8;
                                    break;
                                case 3:
                                    var_r0_11 = 1;
                                    break;
                                default:
                                    var_r0_11 = 2;
                                    break;
                                }
                                switch ((s32) temp_r3_12) {
                                case 0:
                                    var_r3_9 = 2;
                                    break;
                                case 1:
                                    var_r3_9 = 4;
                                    break;
                                case 2:
                                    var_r3_9 = 8;
                                    break;
                                case 3:
                                    var_r3_9 = 1;
                                    break;
                                default:
                                    var_r3_9 = 2;
                                    break;
                                }
                                temp_r3_13 = var_r0_11 * var_r3_9;
                                temp_r0_15 = (s32) ((temp_r3_13 >> 0x1FU) + temp_r3_13) >> 1;
                                switch (temp_r0_15) {
                                case 1:
                                    var_r28 = 3;
block_450:
                                    var_r0_12 = 1;
                                    break;
                                case 2:
                                    var_r28 = 0;
                                    goto block_450;
                                case 4:
                                    var_r28 = 1;
                                    goto block_450;
                                case 8:
                                    var_r28 = 2;
                                    goto block_450;
                                default:
                                    var_r0_12 = 0;
                                    break;
                                }
                                if (var_r0_12 != 0) {
                                    var_r29 = var_r26_3->tev.a_bias;
block_453:
                                    if ((u8) arg0->tev.a_op == 1) {
                                        arg0->tev.a_op = var_r26_3->tev.a_op == 0;
                                    } else {
                                        arg0->tev.a_op = var_r26_3->tev.a_op;
                                    }
                                    var_r23_2 = var_r26_3;
                                    var_r24_4 = arg0;
                                    var_r22_4 = 0;
                                    do {
                                        var_r24_4->tev.a_in[0] = var_r23_2->tev.a_in[0];
                                        HSD_TExpRef(var_r24_4->tev.a_in[0].exp, var_r24_4->tev.a_in[0].sel);
                                        var_r22_4 += 1;
                                        var_r24_4 = (HSD_TExp*) ((char*) var_r24_4 + 8);
                                        var_r23_2 = (HSD_TExp*) ((char*) var_r23_2 + 8);
                                    } while (var_r22_4 < 3);
                                    arg0->tev.a_bias = var_r29;
                                    arg0->tev.a_scale = var_r28;
                                    HSD_TExpUnref(var_r26_3, var_r25_2);
                                    if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                        arg0->tev.tex = var_r26_3->tev.tex;
                                    }
                                    if ((u8) arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = var_r26_3->tev.chan;
                                    }
                                    if ((u8) arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap = var_r26_3->tev.tex_swap;
                                    }
                                    if ((u8) arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap = var_r26_3->tev.ras_swap;
                                    }
                                    var_r30 = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        temp_r4_10 = arg0->tev.a_in[3].type;
        var_r26_4 = arg0->tev.a_in[3].exp;
        temp_r25_3 = arg0->tev.a_in[3].sel;
        if (temp_r4_10 == 1) {
            temp_r3_14 = arg0->tev.tex;
            if ((temp_r3_14 != NULL) && (temp_r0_16 = var_r26_4->tev.tex, ((temp_r0_16 == NULL) == 0)) && (temp_r3_14 != temp_r0_16)) {
                var_r0_13 = 1;
            } else {
                temp_r3_15 = arg0->tev.chan;
                if ((temp_r3_15 != 0xFF) && (temp_r0_17 = var_r26_4->tev.chan, ((temp_r0_17 == 0xFF) == 0)) && (temp_r3_15 != temp_r0_17)) {
                    var_r0_13 = 1;
                } else {
                    var_r0_13 = 0;
                }
            }
            if (var_r0_13 == 0) {
                var_r3_10 = 0;
                if (((u8) arg0->tev.a_in[0].type == 4) || ((u8) arg0->tev.a_in[1].type == 4) || ((u8) arg0->tev.a_in[2].type == 4) || (temp_r4_10 == 4)) {
                    var_r3_10 = 1;
                }
                if (var_r3_10 != 0) {
                    var_r3_11 = 0;
                    if (((u8) var_r26_4->tev.a_in[0].type == 4) || ((u8) var_r26_4->tev.a_in[1].type == 4) || ((u8) var_r26_4->tev.a_in[2].type == 4) || ((u8) var_r26_4->tev.a_in[3].type == 4)) {
                        var_r3_11 = 1;
                    }
                    if (var_r3_11 == 0) {
                        goto block_490;
                    }
                } else {
block_490:
                    if (((u8) var_r26_4->tev.a_range != 0) && ((u8) var_r26_4->tev.a_clamp == 1)) {
                        if (((u8) arg0->tev.a_in[0].sel == 7) && ((u8) arg0->tev.a_in[2].sel == 7) && ((u8) arg0->tev.a_bias == 0)) {
                            temp_r3_16 = arg0->tev.a_scale;
                            if (temp_r3_16 != 3) {
                                temp_r0_18 = var_r26_4->tev.a_scale;
                                switch ((s32) temp_r3_16) {
                                case 0:
                                    var_r3_12 = 2;
                                    break;
                                case 1:
                                    var_r3_12 = 4;
                                    break;
                                case 2:
                                    var_r3_12 = 8;
                                    break;
                                case 3:
                                    var_r3_12 = 1;
                                    break;
                                default:
                                    var_r3_12 = 2;
                                    break;
                                }
                                switch ((s32) temp_r0_18) {
                                case 0:
                                    var_r0_14 = 2;
                                    break;
                                case 1:
                                    var_r0_14 = 4;
                                    break;
                                case 2:
                                    var_r0_14 = 8;
                                    break;
                                case 3:
                                    var_r0_14 = 1;
                                    break;
                                default:
                                    var_r0_14 = 2;
                                    break;
                                }
                                temp_r3_17 = var_r3_12 * var_r0_14;
                                temp_r0_19 = (s32) ((temp_r3_17 >> 0x1FU) + temp_r3_17) >> 1;
                                switch (temp_r0_19) {
                                case 1:
                                    var_r28 = 3;
block_533:
                                    var_r0_15 = 1;
                                    break;
                                case 2:
                                    var_r28 = 0;
                                    goto block_533;
                                case 4:
                                    var_r28 = 1;
                                    goto block_533;
                                case 8:
                                    var_r28 = 2;
                                    goto block_533;
                                default:
                                    var_r0_15 = 0;
                                    break;
                                }
                                if (var_r0_15 != 0) {
                                    var_r30 = 1;
                                    arg0->tev.a_bias = var_r26_4->tev.a_bias;
                                    arg0->tev.a_scale = var_r28;
                                    if ((u8) arg0->tev.a_clamp != 1) {
                                        arg0->tev.a_clamp = var_r26_4->tev.a_clamp;
                                    }
                                    if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                        arg0->tev.tex = var_r26_4->tev.tex;
                                    }
                                    if ((u8) arg0->tev.chan == 0xFF) {
                                        arg0->tev.chan = var_r26_4->tev.chan;
                                    }
                                    if ((u8) arg0->tev.tex_swap == 0xFF) {
                                        arg0->tev.tex_swap = var_r26_4->tev.tex_swap;
                                    }
                                    if ((u8) arg0->tev.ras_swap == 0xFF) {
                                        arg0->tev.ras_swap = var_r26_4->tev.ras_swap;
                                    }
                                    var_r23_3 = arg0;
                                    var_r22_5 = 0;
                                    do {
                                        temp_r20_2 = var_r23_3->tev.a_in[0].exp;
                                        temp_r21_2 = var_r23_3->tev.a_in[0].sel;
                                        var_r23_3->tev.a_in[0] = var_r26_4->tev.a_in[0];
                                        HSD_TExpRef(var_r23_3->tev.a_in[0].exp, var_r23_3->tev.a_in[0].sel);
                                        HSD_TExpUnref(temp_r20_2, temp_r21_2);
                                        var_r22_5 += 1;
                                        var_r26_4 = (HSD_TExp*) ((char*) var_r26_4 + 8);
                                        var_r23_3 = (HSD_TExp*) ((char*) var_r23_3 + 8);
                                    } while (var_r22_5 < 4);
                                }
                            }
                        }
                    } else {
                        temp_r3_18 = var_r26_4->tev.a_scale;
                        if (temp_r3_18 == 0) {
                            if ((((u8) arg0->tev.a_in[0].sel == 7) && ((u8) arg0->tev.a_in[2].sel == 7)) || (((u8) var_r26_4->tev.a_in[0].sel == 7) && ((u8) var_r26_4->tev.a_in[2].sel == 7))) {
                                temp_r0_20 = var_r26_4->tev.a_bias;
                                temp_r4_11 = arg0->tev.a_bias;
                                switch ((s32) temp_r0_20) {
                                case 1:
                                    var_r3_13 = 1;
                                    break;
                                case 2:
                                    var_r3_13 = -1;
                                    break;
                                default:
                                    var_r3_13 = 0;
                                    break;
                                }
                                switch ((s32) temp_r4_11) {
                                case 1:
                                    var_r3_13 += 1;
                                    break;
                                case 2:
                                    var_r3_13 -= 1;
                                    break;
                                }
                                switch (var_r3_13) {
                                case 0:
                                    var_r29 = 0;
                                    var_r0_16 = 1;
                                    break;
                                case 1:
                                    var_r29 = 1;
                                    var_r0_16 = 1;
                                    break;
                                case -1:
                                    var_r29 = 2;
                                    var_r0_16 = 1;
                                    break;
                                default:
                                    var_r0_16 = 0;
                                    break;
                                }
                                if (var_r0_16 != 0) {
                                    var_r28 = arg0->tev.a_scale;
                                    goto block_622;
                                }
                            }
                        } else if (((u8) arg0->tev.a_in[0].sel == 7) && ((u8) arg0->tev.a_in[1].sel == 7) && ((u8) arg0->tev.a_in[2].sel == 7) && ((u8) arg0->tev.a_bias == 0)) {
                            temp_r0_21 = arg0->tev.a_scale;
                            switch ((s32) temp_r0_21) {
                            case 0:
                                var_r0_17 = 2;
                                break;
                            case 1:
                                var_r0_17 = 4;
                                break;
                            case 2:
                                var_r0_17 = 8;
                                break;
                            case 3:
                                var_r0_17 = 1;
                                break;
                            default:
                                var_r0_17 = 2;
                                break;
                            }
                            switch ((s32) temp_r3_18) {
                            case 0:
                                var_r3_14 = 2;
                                break;
                            case 1:
                                var_r3_14 = 4;
                                break;
                            case 2:
                                var_r3_14 = 8;
                                break;
                            case 3:
                                var_r3_14 = 1;
                                break;
                            default:
                                var_r3_14 = 2;
                                break;
                            }
                            temp_r3_19 = var_r0_17 * var_r3_14;
                            temp_r0_22 = (s32) ((temp_r3_19 >> 0x1FU) + temp_r3_19) >> 1;
                            switch (temp_r0_22) {
                            case 1:
                                var_r28 = 3;
block_619:
                                var_r0_18 = 1;
                                break;
                            case 2:
                                var_r28 = 0;
                                goto block_619;
                            case 4:
                                var_r28 = 1;
                                goto block_619;
                            case 8:
                                var_r28 = 2;
                                goto block_619;
                            default:
                                var_r0_18 = 0;
                                break;
                            }
                            if (var_r0_18 != 0) {
                                var_r29 = var_r26_4->tev.a_bias;
block_622:
                                var_r30 = 1;
                                *(u32*) &arg0->tev.a_in[3] = (s32) *(u32*) &var_r26_4->tev.a_in[3];
                                arg0->tev.a_in[3].exp = var_r26_4->tev.a_in[3].exp;
                                HSD_TExpRef(arg0->tev.a_in[3].exp, arg0->tev.a_in[3].sel);
                                arg0->tev.a_bias = var_r29;
                                arg0->tev.a_scale = var_r28;
                                if ((HSD_TObj *) arg0->tev.tex == NULL) {
                                    arg0->tev.tex = var_r26_4->tev.tex;
                                }
                                if ((u8) arg0->tev.chan == 0xFF) {
                                    arg0->tev.chan = var_r26_4->tev.chan;
                                }
                                if ((u8) arg0->tev.tex_swap == 0xFF) {
                                    arg0->tev.tex_swap = var_r26_4->tev.tex_swap;
                                }
                                if ((u8) arg0->tev.ras_swap == 0xFF) {
                                    arg0->tev.ras_swap = var_r26_4->tev.ras_swap;
                                }
                                if (((u8) var_r26_4->tev.a_in[0].sel != 7) || ((u8) var_r26_4->tev.a_in[1].sel != 7) || ((u8) var_r26_4->tev.a_in[2].sel != 7)) {
                                    var_r23_4 = arg0;
                                    var_r24_5 = var_r26_4;
                                    var_r22_6 = 0;
                                    do {
                                        temp_r20_3 = var_r23_4->tev.a_in[0].exp;
                                        temp_r21_3 = var_r23_4->tev.a_in[0].sel;
                                        var_r23_4->tev.a_in[0] = var_r24_5->tev.a_in[0];
                                        HSD_TExpRef(var_r23_4->tev.a_in[0].exp, var_r23_4->tev.a_in[0].sel);
                                        HSD_TExpUnref(temp_r20_3, temp_r21_3);
                                        var_r22_6 += 1;
                                        var_r24_5 = (HSD_TExp*) ((char*) var_r24_5 + 8);
                                        var_r23_4 = (HSD_TExp*) ((char*) var_r23_4 + 8);
                                    } while (var_r22_6 < 3);
                                }
                                HSD_TExpUnref(var_r26_4, temp_r25_3);
                            }
                        }
                    }
                }
            }
        }
        if (var_r30 != 0) {
            var_r31 = 1;
        }
    } while (var_r30 != 0);
    return var_r31;
}


int HSD_TExpSimplify(HSD_TExp* texp_)
{
    HSD_TExp* texp = (HSD_TExp*) texp_;
    int res = false;
    if (HSD_TExpGetType(texp) != HSD_TE_TEV) {
        return false;
    }
    if (SimplifySrc(texp) != 0) {
        res = true;
    }
    if (SimplifyThis(texp) != 0) {
        res = true;
    }
    if (SimplifyByMerge(texp) != 0) {
        res = true;
    }
    CalcTevRange(texp);
    return res;
}

int HSD_TExpSimplify2(HSD_TExp* texp_)
{
    HSD_TExp* texp = texp_;
    HSD_TExp* src_exp;
    u8 src_sel;
    int i;

    for (i = 0; i < 4; i++) {
        src_exp = texp->tev.c_in[i].exp;
        src_sel = texp->tev.c_in[i].sel;
        if (texp->tev.c_in[i].type == HSD_TE_TEV && src_sel == 1 &&
            IsThroughColor(src_exp))
        {
            switch (src_exp->tev.c_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kcsel == 0xFF) {
                    texp->tev.kcsel = src_exp->tev.kcsel;
                } else if (texp->tev.kcsel != src_exp->tev.kcsel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                texp->tev.c_in[i] = src_exp->tev.c_in[3];
                HSD_TExpRef(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        src_exp = texp->tev.a_in[i].exp;
        src_sel = texp->tev.a_in[i].sel;
        if (texp->tev.a_in[i].type == HSD_TE_TEV && IsThroughAlpha(src_exp)) {
            switch (src_exp->tev.a_in[3].type) {
            case HSD_TE_KONST:
                if (texp->tev.kasel == 0xFF) {
                    texp->tev.kasel = src_exp->tev.kasel;
                } else if (texp->tev.kasel != src_exp->tev.kasel) {
                    break;
                }
                /* fallthrough */
            case HSD_TE_IMM:
                texp->tev.a_in[i] = src_exp->tev.a_in[3];
                HSD_TExpRef(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
                HSD_TExpUnref(src_exp, src_sel);
                break;
            }
        }
    }
    return 0;
}

static void CalcTevRange(HSD_TExp* texp)
{
    int range = 0;
    int i;
    HSD_TExp* src;
    if (texp->tev.c_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(texp->tev.c_in[3].exp)) {
        case HSD_TE_TEV:
            if (texp->tev.c_in[3].sel == HSD_TE_RGB) {
                src = texp->tev.c_in[3].exp;
                if (src->tev.c_clamp != 1 && src->tev.c_range == 1) {
                    texp->tev.c_range = 1;
                    goto alpha;
                }
                range = 256;
                break;
            } else {
                src = texp->tev.c_in[3].exp;
                if (src->tev.a_clamp != 1 && src->tev.a_range == 1) {
                    texp->tev.c_range = 1;
                    goto alpha;
                }
            }
            range = 256;
            break;
        default:
            range = 256;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (texp->tev.c_in[i].sel != HSD_TE_0) {
            if (texp->tev.c_op == GX_TEV_SUB) {
                texp->tev.c_range = 1;
                goto alpha;
            }
            range += 256;
            break;
        }
    }
    switch (texp->tev.c_bias) {
    case GX_TB_ADDHALF: range += 128; break;
    case GX_TB_SUBHALF: texp->tev.c_range = 1; goto alpha;
    }
    switch (texp->tev.c_scale) {
    case GX_CS_SCALE_2: range *= 2; break;
    case GX_CS_SCALE_4: range *= 4; break;
    case GX_CS_DIVIDE_2: range /= 2; break;
    }
    texp->tev.c_range = range > 256;
alpha:
    range = 0;
    if (texp->tev.a_in[3].sel != HSD_TE_0) {
        switch (HSD_TExpGetType(texp->tev.a_in[3].exp)) {
        case HSD_TE_TEV:
            src = texp->tev.a_in[3].exp;
            if (src->tev.a_clamp != 1 && src->tev.a_range == 1) {
                texp->tev.a_range = 1;
                return;
            }
            range = 256;
            break;
        default:
            range = 256;
            break;
        }
    }
    for (i = 0; i < 3; i++) {
        if (texp->tev.a_in[i].sel != HSD_TE_0) {
            if (texp->tev.a_op == GX_TEV_SUB) {
                texp->tev.a_range = 1;
                return;
            }
            range += 256;
            break;
        }
    }
    switch (texp->tev.a_bias) {
    case GX_TB_ADDHALF: range += 128; break;
    case GX_TB_SUBHALF: texp->tev.a_range = 1; return;
    }
    switch (texp->tev.a_scale) {
    case GX_CS_SCALE_2: range *= 2; break;
    case GX_CS_SCALE_4: range *= 4; break;
    case GX_CS_DIVIDE_2: range /= 2; break;
    }
    texp->tev.a_range = range > 256;
}
