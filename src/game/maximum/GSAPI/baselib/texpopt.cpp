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

int HSD_TExpSimplify(HSD_TExp* texp_)
{
    int res = false;
    HSD_TExp* texp = (HSD_TExp*) texp_;
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
/// @todo Redundant cast and assignment matches
#ifdef MUST_MATCH
    HSD_TExp* texp = (HSD_TExp*) texp_;
#else
    HSD_TExp* texp = (HSD_TExp*) texp_;
#endif
    int i;
    HSD_TExp* src_exp;
    u8 src_sel;

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
