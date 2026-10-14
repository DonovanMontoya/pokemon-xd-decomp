/* XD texture expressions: graph ownership, constant register assignment,
 * and conversion to GX TEV stages. Deferred inlining retains the runtime ABI. */
#include "game/maximum/GSAPI/baselib/texp.h"

#ifdef __cplusplus
extern "C" {
#endif
void* memset(void*, int, unsigned long);
void __assert(const char*, int, const char*);
void HSD_Panic(const char*, int, const char*);
void* hsdAllocMemPiece(unsigned int);
void hsdFreeMemPiece(void*, unsigned int);
void HSD_StateInvalidate(unsigned int);
void HSD_StateAssignTev(void);
void HSD_SetupTevStage(HSD_TevDesc*);
int HSD_Index2TevStage(int);
typedef struct HSD_TExpDag {
    HSD_TETev* tev;
    u8 idx, nb_dep, nb_ref, dist;
    struct HSD_TExpDag* depend[8];
} HSD_TExpDag;
int HSD_TExpMakeDag(HSD_TExp*, HSD_TExpDag*);
void HSD_TExpSchedule(int, HSD_TExpDag*, HSD_TExp**, HSD_TExpRes*);
int HSD_TExpSimplify(HSD_TExp*);
int HSD_TExpSimplify2(HSD_TExp*);
/* The coordinate lives after the texture runtime state in XD. */
typedef struct HSD_TExpTextureView {
    HSD_TObj animation;
    u8 texture_state[0xA4 - sizeof(HSD_TObj)];
    GXTexCoordID coord;
} HSD_TExpTextureView;
void HSD_TExpFreeTevDesc(HSD_TExpTevDesc* tdesc);
int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc,
                    HSD_TExp** texp_list);
void HSD_TExpSetupTev(HSD_TExpTevDesc* tevdesc, HSD_TExp* texp);
static void HSD_TExpSetReg(HSD_TExp* texp);
static void TExp2TevDesc(HSD_TExp* texp, HSD_TExpTevDesc* desc,
                         int* init_cprev, int* init_aprev);
static int TExpAssignReg(HSD_TExp* texp, HSD_TExpRes* res);
static int AssignAlphaKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res);
static int AssignColorKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res);
static int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res);
void HSD_TExpOrder(HSD_TExp* texp, HSD_TObj* tex, GXChannelID chan);
void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d);
static void HSD_TExpAlphaInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx);
void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d);
static void HSD_TExpColorInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx);
void HSD_TExpAlphaOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp);
void HSD_TExpColorSwap(HSD_TExp* texp, GXTevColorChan r, GXTevColorChan g, GXTevColorChan b, GXTevColorChan a);
void HSD_TExpColorOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp);
HSD_TExp* HSD_TExpCnst(void* val, HSD_TEInput comp, HSD_TEType type,
                       HSD_TExp** texp_list);
HSD_TExp* HSD_TExpTev(HSD_TExp** texp_list);
HSD_TExp* HSD_TExpFreeList(HSD_TExp* texp_list, HSD_TExpType type, s32 all);
void HSD_TExpUnref(HSD_TExp* texp, u8 sel);
void HSD_TExpRef(HSD_TExp* texp, u8 sel);
HSD_TExpType HSD_TExpGetType(HSD_TExp* texp);

static inline unsigned int TExpDefault(unsigned int value, unsigned int fallback) {
    if (value == HSD_TE_UNDEF) value = fallback;
    return value;
}
static inline int TExpSwapDefault(int value, int fallback) {
    if (value == HSD_TE_UNDEF) value = fallback;
    return value;
}
static inline HSD_TExp* TevAlloc(void)
{
    HSD_TExp* texp = (HSD_TExp*)hsdAllocMemPiece(sizeof(HSD_TETev));
    if (!(texp)) __assert("texp.c", 63, "texp");
    return texp;
}

static inline HSD_TExp* CnstAlloc(void)
{
    HSD_TExp* texp = (HSD_TExp*)hsdAllocMemPiece(sizeof(HSD_TECnst));
    if (!(texp)) __assert("texp.c", 71, "texp");
    return texp;
}

static inline void HSD_TExpFree(HSD_TExp* texp)
{
    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        hsdFreeMemPiece(texp, sizeof(HSD_TETev));
        break;
    case HSD_TE_CNST:
        hsdFreeMemPiece(texp, sizeof(HSD_TECnst));
        break;
    default:
        break;
    }
}

HSD_TExpType HSD_TExpGetType(HSD_TExp* texp)
{
    if (texp == 0) {
        return HSD_TE_ZERO;
    }
    if (texp == HSD_TEXP_TEX) {
        return HSD_TE_TEX;
    }
    if (texp == HSD_TEXP_RAS) {
        return HSD_TE_RAS;
    }
    return texp->type;
}

void HSD_TExpRef(HSD_TExp* texp, u8 sel)
{
    HSD_TExpType type = HSD_TExpGetType(texp);
    switch (type) {
    case HSD_TE_TEV:
        if (sel == 1) {
            texp->tev.c_ref += 1;
            return;
        } else {
            texp->tev.a_ref += 1;
            return;
        }
        break;
    case HSD_TE_CNST:
        texp->cnst.ref += 1;
        break;
    default:
        break;
    }
}

void HSD_TExpUnref(HSD_TExp* texp, u8 sel)
{
    int i;
    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        if (sel == HSD_TE_RGB) {
            if (texp->tev.c_ref != 0) texp->tev.c_ref -= 1;
        } else if (texp->tev.a_ref != 0) {
            texp->tev.a_ref -= 1;
        }
        if (texp->tev.c_ref == 0 && texp->tev.a_ref == 0) {
            for (i = 0; i < 4; ++i) {
                HSD_TExpUnref(texp->tev.c_in[i].exp, texp->tev.c_in[i].sel);
                HSD_TExpUnref(texp->tev.a_in[i].exp, texp->tev.a_in[i].sel);
            }
        }
        break;
    case HSD_TE_CNST:
        if (texp->cnst.ref != 0) texp->cnst.ref -= 1;
        break;
    default:
        break;
    }
}

HSD_TExp* HSD_TExpFreeList(HSD_TExp* texp_list, HSD_TExpType type, s32 all)
{
    HSD_TExp** handle;
    HSD_TExp* ptr;
    HSD_TExp* next;

    handle = &texp_list;

    if (all != 0) {
        while (*handle != 0) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    if (!(0)) __assert("texp.c", 220, "0");
                }
            }
            handle = &(*handle)->tev.next;
        }
    } else {
        if (type == HSD_TE_ALL || type == HSD_TE_TEV) {
            for (ptr = texp_list; ptr != 0; ptr = ptr->tev.next) {
                switch (ptr->type) {
                case HSD_TE_TEV:
                    if (ptr->tev.c_ref == 0 && ptr->tev.c_ref == 0) {
                        HSD_TExpUnref(ptr, 1);
                        HSD_TExpUnref(ptr, 5);
                    }
                    break;
                default:
                    break;
                }
            }
        }

        while (*handle != 0) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    if ((*handle)->tev.c_ref != 0 || (*handle)->tev.a_ref != 0)
                    {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    if ((*handle)->cnst.ref != 0) {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    if (!(0)) __assert("texp.c", 268, "0");
                }
            }
            handle = &(*handle)->tev.next;
        }
    }

    return texp_list;
}

HSD_TExp* HSD_TExpTev(HSD_TExp** texp_list)
{
    int i;
    HSD_TExp* texp;

    if (!(texp_list)) __assert("texp.c", 295, "texp_list");
    texp = TevAlloc();
    memset(texp, 0xFF, sizeof(HSD_TETev));
    texp->type = HSD_TE_TEV;
    texp->tev.next = *texp_list;
    *texp_list = texp;
    texp->tev.c_ref = 0;
    texp->tev.a_ref = 0;
    texp->tev.swap_r = GX_CH_RED;
    texp->tev.swap_g = GX_CH_GREEN;
    texp->tev.swap_b = GX_CH_BLUE;
    texp->tev.swap_a = GX_CH_ALPHA;
    texp->tev.tex = 0;
    for (i = 0; i < 4; i++) {
        texp->tev.c_in[i].exp = 0;
        texp->tev.a_in[i].exp = 0;
    }
    return texp;
}

HSD_TExp* HSD_TExpCnst(void* val, HSD_TEInput comp, HSD_TEType type,
                       HSD_TExp** texp_list)
{
    HSD_TExp* texp;

    if (!(texp_list)) __assert("texp.c", 371, "texp_list");

    texp = *texp_list;
    do {
        while (texp) {
            if (texp->type == HSD_TE_CNST && texp->cnst.val == val &&
                texp->cnst.comp == comp)
            {
                if (!(texp->cnst.ctype == type)) __assert("texp.c", 378, "texp->cnst.ctype == type");
                return texp;
            }
            texp = texp->cnst.next;
        }

        if (comp == HSD_TE_0) {
            return 0;
        }
        texp = CnstAlloc();
        texp->cnst.type = HSD_TE_CNST;
        texp->cnst.next = (*texp_list);
        *texp_list = texp;
        texp->cnst.ref = 0;
        texp->cnst.val = val;
        texp->cnst.comp = comp;
        texp->cnst.ctype = type;
        texp->cnst.reg = 0xFF;
        texp->cnst.idx = 0xFF;
        texp->cnst.range = 0;
        return texp;
    } while (1);

    return texp;
}

void HSD_TExpColorOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    if (!(texp)) __assert("texp.c", 419, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 420, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    texp->tev.c_op = op;
    texp->tev.c_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op == GX_TEV_ADD || op == GX_TEV_SUB) {
        texp->tev.c_bias = bias;
        texp->tev.c_scale = scale;
    } else {
        texp->tev.c_bias = 0;
        texp->tev.c_scale = 0;
    }
}

void HSD_TExpColorSwap(HSD_TExp* texp, GXTevColorChan r, GXTevColorChan g, GXTevColorChan b, GXTevColorChan a) {
    if (!texp) __assert("texp.c", 443, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 444, "HSD_TExpGetType(texp) == HSD_TE_TEV");
    texp->tev.swap_r = r;
    texp->tev.swap_g = g;
    texp->tev.swap_b = b;
    texp->tev.swap_a = a;
}

void HSD_TExpAlphaOp(HSD_TExp* texp, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, u8 clamp)
{
    if (!(texp)) __assert("texp.c", 467, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 468, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    texp->tev.a_op = op;
    texp->tev.a_clamp = (clamp ? GX_ENABLE : GX_DISABLE);
    if (op == GX_TEV_ADD || op == GX_TEV_SUB) {
        texp->tev.a_bias = bias;
        texp->tev.a_scale = scale;
    } else {
        texp->tev.a_bias = 0;
        texp->tev.a_scale = 0;
    }
}

static void HSD_TExpColorInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;

    prev = tev->c_in[idx];
    tev->c_in[idx].type = HSD_TExpGetType(exp);
    tev->c_in[idx].sel = sel;
    tev->c_in[idx].exp = exp;
    tev->c_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->c_in[idx].arg = GX_CC_ZERO;
        tev->c_in[idx].type = HSD_TE_ZERO;
        tev->c_in[idx].exp = 0;
        break;
    case HSD_TE_1:
        tev->c_in[idx].arg = GX_CC_ONE;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = 0;
        break;
    case HSD_TE_4_8:
        tev->c_in[idx].arg = GX_CC_HALF;
        tev->c_in[idx].type = HSD_TE_IMM;
        tev->c_in[idx].exp = 0;
        break;
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->c_in[idx].arg = GX_CC_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KCSEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KCSEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KCSEL_3_8;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KCSEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KCSEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KCSEL_7_8;
            break;
        default:
            if (!(0)) __assert("texp.c", 531, "0");
            break;
        }

        if (tev->kcsel == HSD_TE_UNDEF) {
            tev->kcsel = ksel;
        } else if (tev->kcsel == ksel) {
            HSD_Panic("texp.c", 536,
                      "tev can't select multiple konst input.\n");
        }
        tev->c_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->c_in[idx].type) {
        case HSD_TE_ZERO:
            tev->c_in[idx].type = HSD_TE_ZERO;
            tev->c_in[idx].sel = HSD_TE_0;
            tev->c_in[idx].arg = GX_CC_ZERO;
            break;
        case HSD_TE_TEV: {
            u8 swap;
            { int valid = sel == HSD_TE_RGB || sel == HSD_TE_A; if (!valid) __assert("texp.c", 552, "sel == HSD_TE_RGB || sel == HSD_TE_A"); }
            { int valid = idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp; if (!valid) __assert("texp.c", 554, "idx == 3 || sel != HSD_TE_RGB || exp->tev.c_clamp"); }
            { int valid = idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp; if (!valid) __assert("texp.c", 555, "idx == 3 || sel != HSD_TE_A || exp->tev.a_clamp"); }
            swap = tev->c_in[idx].sel;
            switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
            case HSD_TE_TEV:
                if (swap == 1) {
                    tev->c_in[idx].exp->tev.c_ref += 1;
                } else {
                    tev->c_in[idx].exp->tev.a_ref += 1;
                }
                break;
            case HSD_TE_CNST:
                tev->c_in[idx].exp->cnst.ref += 1;
                break;
            default:
                break;
            }
        } break;
        case HSD_TE_CNST: {
            u8 swap;
            tev->c_in[idx].sel = exp->cnst.comp;
            swap = tev->c_in[idx].sel;
            switch (HSD_TExpGetType(tev->c_in[idx].exp)) {
            case HSD_TE_TEV:
                if (swap == 1) {
                    tev->c_in[idx].exp->tev.c_ref += 1;
                } else {
                    tev->c_in[idx].exp->tev.a_ref += 1;
                }
                break;
            case HSD_TE_CNST:
                tev->c_in[idx].exp->cnst.ref += 1;
                break;
            default:
                break;
            }
        } break;
        case HSD_TE_TEX: {
            u8 swap = HSD_TE_UNDEF;
            switch (sel) {
            case HSD_TE_RGB:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP0;
                break;
            case HSD_TE_R:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP1;
                break;
            case HSD_TE_G:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP2;
                break;
            case HSD_TE_B:
                tev->c_in[idx].arg = GX_CC_TEXC;
                swap = GX_TEV_SWAP3;
                break;
            case HSD_TE_A:
                tev->c_in[idx].arg = GX_CC_TEXA;
                break;
            default:
                if (!(0)) __assert("texp.c", 590, "0");
                break;
            }
            if (tev->tex_swap == HSD_TE_UNDEF) {
                tev->tex_swap = swap;
            } else {
                { int valid = swap == HSD_TE_UNDEF || tev->tex_swap == swap; if (!valid) __assert("texp.c", 595, "swap == HSD_TE_UNDEF || tev->tex_swap == swap"); }
            }
        } break;
        case HSD_TE_RAS: {
            u8 swap = HSD_TE_UNDEF;
            switch (sel) {
            case HSD_TE_RGB:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP0;
                break;
            case HSD_TE_R:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP1;
                break;
            case HSD_TE_G:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP2;
                break;
            case HSD_TE_B:
                tev->c_in[idx].arg = GX_CC_RASC;
                swap = GX_TEV_SWAP3;
                break;
            case HSD_TE_A:
                tev->c_in[idx].arg = GX_CC_RASA;
                break;
            default:
                if (!(0)) __assert("texp.c", 638, "0");
                break;
            }
            if (tev->ras_swap == HSD_TE_UNDEF) {
                tev->ras_swap = swap;
            } else {
                { int valid = swap == HSD_TE_UNDEF || tev->ras_swap == swap; if (!valid) __assert("texp.c", 643, "swap == HSD_TE_UNDEF || tev->ras_swap == swap"); }
            }
        } break;
        default:
            if (!(0)) __assert("texp.c", 661, "0");
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}

void HSD_TExpColorIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    if (!(texp)) __assert("texp.c", 724, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 725, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    tev = &texp->tev;
    HSD_TExpColorInSub(tev, sel_a, exp_a, 0);
    HSD_TExpColorInSub(tev, sel_b, exp_b, 1);
    HSD_TExpColorInSub(tev, sel_c, exp_c, 2);
    HSD_TExpColorInSub(tev, sel_d, exp_d, 3);
}

static void HSD_TExpAlphaInSub(HSD_TETev* tev, HSD_TEInput sel, HSD_TExp* exp,
                               s32 idx)
{
    HSD_TEArg prev;
    u8 ksel;

    prev = tev->a_in[idx];
    tev->a_in[idx].sel = sel;
    tev->a_in[idx].exp = exp;
    tev->a_in[idx].type = HSD_TExpGetType(exp);
    tev->a_in[idx].arg = 0xFF;

    switch (sel) {
    case HSD_TE_0:
        tev->a_in[idx].type = HSD_TE_ZERO;
        tev->a_in[idx].arg = GX_CA_ZERO;
        tev->a_in[idx].exp = 0;
        break;

    case HSD_TE_1:
    case HSD_TE_1_8:
    case HSD_TE_2_8:
    case HSD_TE_3_8:
    case HSD_TE_4_8:
    case HSD_TE_5_8:
    case HSD_TE_6_8:
    case HSD_TE_7_8:
        tev->a_in[idx].exp = 0;
        tev->a_in[idx].arg = GX_CA_KONST;
        switch (sel) {
        case HSD_TE_1_8:
            ksel = GX_TEV_KASEL_1_8;
            break;
        case HSD_TE_2_8:
            ksel = GX_TEV_KASEL_1_4;
            break;
        case HSD_TE_3_8:
            ksel = GX_TEV_KASEL_3_8;
            break;
        case HSD_TE_4_8:
            ksel = GX_TEV_KASEL_1_2;
            break;
        case HSD_TE_5_8:
            ksel = GX_TEV_KASEL_5_8;
            break;
        case HSD_TE_6_8:
            ksel = GX_TEV_KASEL_3_4;
            break;
        case HSD_TE_7_8:
            ksel = GX_TEV_KASEL_7_8;
            break;
        default:
            ksel = GX_TEV_KASEL_1;
            break;
        }

        if (tev->kasel == HSD_TE_UNDEF) {
            tev->kasel = ksel;
        } else {
            if (!(tev->kasel == ksel)) __assert("texp.c", 781, "tev->kasel == ksel");
        }
        tev->a_in[idx].type = HSD_TE_KONST;
        break;

    default: {
        switch (tev->a_in[idx].type) {
        case HSD_TE_ZERO:
            tev->a_in[idx].exp = 0;
            tev->a_in[idx].type = HSD_TE_ZERO;
            tev->a_in[idx].sel = HSD_TE_0;
            tev->a_in[idx].arg = GX_CA_ZERO;
            break;
        case HSD_TE_TEV:
            if (!(sel == HSD_TE_A)) __assert("texp.c", 804, "sel == HSD_TE_A");
            { int valid = idx == 3 || exp->tev.a_clamp; if (!valid) __assert("texp.c", 805, "idx == 3 || exp->tev.a_clamp"); }
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_CNST:
            { int valid = sel == HSD_TE_A || sel == HSD_TE_X; if (!valid) __assert("texp.c", 809, "sel == HSD_TE_A || sel == HSD_TE_X"); }
            if (!(exp->cnst.comp == HSD_TE_X)) __assert("texp.c", 810, "exp->cnst.comp == HSD_TE_X");
            tev->a_in[idx].sel = HSD_TE_X;
            HSD_TExpRef(tev->a_in[idx].exp, tev->a_in[idx].sel);
            break;
        case HSD_TE_TEX:
            if (!(sel == HSD_TE_A)) __assert("texp.c", 815, "sel == HSD_TE_A");
            tev->a_in[idx].arg = GX_CA_TEXA;
            break;
        case HSD_TE_RAS:
            if (!(sel == HSD_TE_A)) __assert("texp.c", 819, "sel == HSD_TE_A");
            tev->a_in[idx].arg = GX_CA_RASA;
            break;
        default:
            if (!(0)) __assert("texp.c", 823, "0");
            break;
        }
    }
    }
    HSD_TExpUnref(prev.exp, prev.sel);
}

void HSD_TExpAlphaIn(HSD_TExp* texp, HSD_TEInput sel_a, HSD_TExp* exp_a,
                     HSD_TEInput sel_b, HSD_TExp* exp_b, HSD_TEInput sel_c,
                     HSD_TExp* exp_c, HSD_TEInput sel_d, HSD_TExp* exp_d)
{
    HSD_TETev* tev;

    if (!(texp)) __assert("texp.c", 854, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 855, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    tev = &texp->tev;
    HSD_TExpAlphaInSub(tev, sel_a, exp_a, 0);
    HSD_TExpAlphaInSub(tev, sel_b, exp_b, 1);
    HSD_TExpAlphaInSub(tev, sel_c, exp_c, 2);
    HSD_TExpAlphaInSub(tev, sel_d, exp_d, 3);
}

void HSD_TExpOrder(HSD_TExp* texp, HSD_TObj* tex, GXChannelID chan)
{
    if (!(texp)) __assert("texp.c", 870, "texp");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 871, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    texp->tev.tex = tex;
    if (chan == GX_COLOR_NULL) {
        texp->tev.chan = GX_COLOR_NULL;
        return;
    }
    texp->tev.chan = chan;
}

static int AssignColorReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevColorArg a_in[4] = { GX_CC_A0, GX_CC_A1, GX_CC_A2,
                                     GX_CC_APREV };
    static GXTevColorArg c_in[4] = { GX_CC_C0, GX_CC_C1, GX_CC_C2,
                                     GX_CC_CPREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->c_in[idx].type = HSD_TE_IMM;
        if (cnst->comp == HSD_TE_X) {
            tev->c_in[idx].arg = a_in[cnst->reg - 4];
        } else {
            tev->c_in[idx].arg = c_in[cnst->reg - 4];
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = a_in[j - 4];
                    return 0;
                }
            }
        } else {
            for (j = 4; j < 8; ++j) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->c_in[idx].type = HSD_TE_IMM;
                    tev->c_in[idx].arg = c_in[j - 4];
                    return 0;
                }
            }
        }
    }
    return -1;
}

static inline int AssignAlphaReg(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevAlphaArg in[4] = { GX_CA_A0, GX_CA_A1, GX_CA_A2, GX_CA_APREV };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg < 4) {
            return -1;
        }
        tev->a_in[idx].type = HSD_TE_IMM;
        tev->a_in[idx].arg = in[cnst->reg - 4];
        return 0;
    } else {
        for (j = 4; j < 8; ++j) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->a_in[idx].type = HSD_TE_IMM;
                tev->a_in[idx].arg = in[j - 4];
                return 0;
            }
        }
    }
    return -1;
}

static int AssignColorKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKColorSel xsel[4][4] = {
        { GX_TEV_KCSEL_K0_R, GX_TEV_KCSEL_K0_G, GX_TEV_KCSEL_K0_B,
          GX_TEV_KCSEL_K0_A },
        { GX_TEV_KCSEL_K1_R, GX_TEV_KCSEL_K1_G, GX_TEV_KCSEL_K1_B,
          GX_TEV_KCSEL_K1_A },
        { GX_TEV_KCSEL_K2_R, GX_TEV_KCSEL_K2_G, GX_TEV_KCSEL_K2_B,
          GX_TEV_KCSEL_K2_A },
        { GX_TEV_KCSEL_K3_R, GX_TEV_KCSEL_K3_G, GX_TEV_KCSEL_K3_B,
          GX_TEV_KCSEL_K3_A }
    };

    static GXTevKColorSel csel[4] = { GX_TEV_KCSEL_K0, GX_TEV_KCSEL_K1,
                                      GX_TEV_KCSEL_K2, GX_TEV_KCSEL_K3 };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->c_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        if (cnst->comp == HSD_TE_X) {
            tev->kcsel = xsel[cnst->reg][cnst->idx];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        } else {
            tev->kcsel = csel[cnst->reg];
            tev->c_in[idx].type = HSD_TE_KONST;
            tev->c_in[idx].arg = GX_CC_KONST;
        }
        return 0;
    } else {
        if (cnst->comp == HSD_TE_X) {
            for (j = 1; j < 4; j++) {
                if (res->reg[j].alpha == 0) {
                    res->reg[j].alpha = 1;
                    cnst->reg = j;
                    cnst->idx = 3;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }

            for (j = 0; j < 4; j++) {
                if (res->reg[j].color < 3) {
                    cnst->reg = j;
                    cnst->idx = res->reg[j].color++;
                    tev->kcsel = xsel[cnst->reg][cnst->idx];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        } else {
            for (j = 0; j < 4; j++) {
                if (res->reg[j].color == 0) {
                    res->reg[j].color = 3;
                    cnst->reg = j;
                    cnst->idx = 0;
                    tev->kcsel = csel[cnst->reg];
                    tev->c_in[idx].type = HSD_TE_KONST;
                    tev->c_in[idx].arg = GX_CC_KONST;
                    return 0;
                }
            }
        }
    }
    return -1;
}

static int AssignAlphaKonst(HSD_TETev* tev, int idx, HSD_TExpRes* res)
{
    static GXTevKAlphaSel sel[4][4] = {
        { GX_TEV_KASEL_K0_R, GX_TEV_KASEL_K0_G, GX_TEV_KASEL_K0_B,
          GX_TEV_KASEL_K0_A },
        { GX_TEV_KASEL_K1_R, GX_TEV_KASEL_K1_G, GX_TEV_KASEL_K1_B,
          GX_TEV_KASEL_K1_A },
        { GX_TEV_KASEL_K2_R, GX_TEV_KASEL_K2_G, GX_TEV_KASEL_K2_B,
          GX_TEV_KASEL_K2_A },
        { GX_TEV_KASEL_K3_R, GX_TEV_KASEL_K3_G, GX_TEV_KASEL_K3_B,
          GX_TEV_KASEL_K3_A }
    };

    HSD_TECnst* cnst;
    int j;

    cnst = &tev->a_in[idx].exp->cnst;
    if (cnst->reg != HSD_TE_UNDEF) {
        if (cnst->reg >= 4) {
            return -1;
        }
        tev->kasel = sel[cnst->reg][cnst->idx];
        tev->a_in[idx].type = HSD_TE_KONST;
        tev->a_in[idx].arg = GX_CA_KONST;
        return 0;
    } else {
        for (j = 1; j < 4; j++) {
            if (res->reg[j].alpha == 0) {
                res->reg[j].alpha = 1;
                cnst->reg = j;
                cnst->idx = 3;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }

        for (j = 0; j < 4; j++) {
            if (res->reg[j].color < 3) {
                cnst->reg = j;
                cnst->idx = res->reg[j].color++;
                tev->kasel = sel[cnst->reg][cnst->idx];
                tev->a_in[idx].type = HSD_TE_KONST;
                tev->a_in[idx].arg = GX_CA_KONST;
                return 0;
            }
        }
    }
    return -1;
}

static int TExpAssignReg(HSD_TExp* texp, HSD_TExpRes* res)
{
    HSD_TETev* tev = (HSD_TETev*) texp;
    int i, val;

    if (tev->c_ref > 0) {
        if (tev->kcsel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        if (!(val >= 0)) __assert("texp.c", 1180, "val >= 0");
                        return val;
                    }
                }
            }
        } else if (IsThroughColor((HSD_TExp*) tev) &&
                   tev->c_in[3].type == HSD_TE_CNST)
        {
            if (AssignColorReg(tev, 3, res) < 0) {
                val = AssignColorKonst(tev, 3, res);
                if (val < 0) {
                    if (!(val >= 0)) __assert("texp.c", 1192, "val >= 0");
                    return val;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    if (AssignColorKonst(tev, i, res) < 0) {
                        val = AssignColorReg(tev, i, res);
                        if (val < 0) {
                            if (!(val >= 0)) __assert("texp.c", 1205, "val >= 0");
                            return val;
                        }
                    }
                }
            }
            for (; i < 4; i++) {
                if (tev->c_in[i].type == HSD_TE_CNST) {
                    val = AssignColorReg(tev, i, res);
                    if (val < 0) {
                        if (!(val >= 0)) __assert("texp.c", 1214, "val >= 0");
                        return val;
                    }
                }
            }
        }
    }

    if (tev->a_ref > 0) {
        if (tev->kasel != HSD_TE_UNDEF) {
            for (i = 0; i < 4; i++) {
                if (tev->a_in[i].type == HSD_TE_CNST) {
                    val = AssignAlphaReg(tev, i, res);
                    if (val < 0) {
                        if (!(val >= 0)) __assert("texp.c", 1230, "val >= 0");
                        return val;
                    }
                }
            }
        } else {
            if (IsThroughAlpha((HSD_TExp*) tev) &&
                tev->a_in[3].type == HSD_TE_CNST)
            {
                if (AssignAlphaReg(tev, 3, res) < 0) {
                    val = AssignAlphaKonst(tev, 3, res);
                    if (val < 0) {
                        if (!(val >= 0)) __assert("texp.c", 1242, "val >= 0");
                        return val;
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        if (AssignAlphaKonst(tev, i, res) < 0) {
                            val = AssignAlphaReg(tev, i, res);
                            if (val < 0) {
                                if (!(val >= 0)) __assert("texp.c", 1255, "val >= 0");
                                return val;
                            }
                        }
                    }
                }
                for (; i < 4; i++) {
                    if (tev->a_in[i].type == HSD_TE_CNST) {
                        val = AssignAlphaReg(tev, i, res);
                        if (val < 0) {
                            if (!(val >= 0)) __assert("texp.c", 1264, "val >= 0");
                            return val;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

static void TExp2TevDesc(HSD_TExp* texp, HSD_TExpTevDesc* desc,
                         int* init_cprev, int* init_aprev)
{
    static GXTevRegID dst[4] = { GX_TEVREG0, GX_TEVREG1, GX_TEVREG2,
                                 GX_TEVPREV };

    HSD_TETev* tev;
    HSD_TevDesc* tevdesc;

    if (!(texp)) __assert("texp.c", 1320, "texp");
    if (!(desc)) __assert("texp.c", 1321, "desc");
    if (!(HSD_TExpGetType(texp) == HSD_TE_TEV)) __assert("texp.c", 1322, "HSD_TExpGetType(texp) == HSD_TE_TEV");

    tev = &texp->tev;
    tevdesc = &desc->desc;

    tevdesc->next = 0;
    tevdesc->flags = 1;
    desc->tobj = tev->tex;
    if (tev->tex == 0) {
        tevdesc->coord = HSD_TE_UNDEF;
        tevdesc->map = HSD_TE_UNDEF;
    }
    tevdesc->color = TExpDefault(tev->chan, HSD_TE_UNDEF);
    tevdesc->u.tevconf.ras_swap = (GXTevSwapSel)(TExpDefault(tev->ras_swap, 0));
    tevdesc->u.tevconf.tex_swap = (GXTevSwapSel)(TExpDefault(tev->tex_swap, 0));
    tevdesc->u.tevconf.kcsel = (GXTevKColorSel)(TExpDefault(tev->kcsel, 0));
    tevdesc->u.tevconf.kasel = (GXTevKAlphaSel)(TExpDefault(tev->kasel, 0));

    tevdesc->u.tevconf.swap_r = (GXTevColorChan)(TExpSwapDefault(tev->swap_r, GX_CH_RED));
    tevdesc->u.tevconf.swap_g = (GXTevColorChan)(TExpSwapDefault(tev->swap_g, GX_CH_GREEN));
    tevdesc->u.tevconf.swap_b = (GXTevColorChan)(TExpSwapDefault(tev->swap_b, GX_CH_BLUE));
    tevdesc->u.tevconf.swap_a = (GXTevColorChan)(TExpSwapDefault(tev->swap_a, GX_CH_ALPHA));

    if ((tev->c_op == HSD_TE_UNDEF) ||
        (tev->c_ref == 0 && tev->a_op != 8 && tev->a_op != 9 &&
         tev->a_op != 0xA && tev->a_op != 0xB && tev->a_op != 0xC &&
         tev->a_op != 0xD))
    {
        tevdesc->u.tevconf.clr_op = (GXTevOp)(GX_TEV_ADD);
        tevdesc->u.tevconf.clr_a = (GXTevColorArg)(GX_CC_ZERO);
        tevdesc->u.tevconf.clr_b = (GXTevColorArg)(GX_CC_ZERO);
        tevdesc->u.tevconf.clr_c = (GXTevColorArg)(GX_CC_ZERO);
        if (*init_cprev != 0) {
            *init_cprev = 0;
            tevdesc->u.tevconf.clr_d = (GXTevColorArg)(GX_CC_ZERO);
        } else {
            tevdesc->u.tevconf.clr_d = (GXTevColorArg)(GX_CC_CPREV);
        }
        tevdesc->u.tevconf.clr_scale = (GXTevScale)(0);
        tevdesc->u.tevconf.clr_bias = (GXTevBias)(0);
        tevdesc->u.tevconf.clr_clamp = (u8)(0);
        tevdesc->u.tevconf.clr_out_reg = (GXTevRegID)(0);
    } else {
        tevdesc->u.tevconf.clr_op = (GXTevOp)(tev->c_op);
        tevdesc->u.tevconf.clr_a = (GXTevColorArg)(TExpDefault(tev->c_in[0].arg, GX_CC_ZERO));
        tevdesc->u.tevconf.clr_b = (GXTevColorArg)(TExpDefault(tev->c_in[1].arg, GX_CC_ZERO));
        tevdesc->u.tevconf.clr_c = (GXTevColorArg)(TExpDefault(tev->c_in[2].arg, GX_CC_ZERO));
        tevdesc->u.tevconf.clr_d = (GXTevColorArg)(TExpDefault(tev->c_in[3].arg, GX_CC_ZERO));
        tevdesc->u.tevconf.clr_scale = (GXTevScale)(TExpDefault(tev->c_scale, 0));
        tevdesc->u.tevconf.clr_bias = (GXTevBias)(TExpDefault(tev->c_bias, 0));
        tevdesc->u.tevconf.clr_clamp = (u8)(tev->c_clamp != 0 ? GX_TRUE : GX_FALSE);

        if (!(tev->c_dst != HSD_TE_UNDEF)) __assert("texp.c", 1393, "tev->c_dst != HSD_TE_UNDEF");
        tevdesc->u.tevconf.clr_out_reg = (GXTevRegID)(dst[tev->c_dst]);
        if (tevdesc->u.tevconf.clr_out_reg == 0) {
            *init_cprev = 0;
        }
    }

    if (tev->a_op == HSD_TE_UNDEF || tev->a_ref == 0) {
        tevdesc->u.tevconf.alpha_op = (GXTevOp)(GX_TEV_ADD);
        tevdesc->u.tevconf.alpha_a = (GXTevAlphaArg)(GX_CA_ZERO);
        tevdesc->u.tevconf.alpha_b = (GXTevAlphaArg)(GX_CA_ZERO);
        tevdesc->u.tevconf.alpha_c = (GXTevAlphaArg)(GX_CA_ZERO);
        if (*init_aprev != 0) {
            *init_aprev = 0;
            tevdesc->u.tevconf.alpha_d = (GXTevAlphaArg)(GX_CA_ZERO);
        } else {
            tevdesc->u.tevconf.alpha_d = (GXTevAlphaArg)(GX_CA_APREV);
        }
        tevdesc->u.tevconf.alpha_scale = (GXTevScale)(0);
        tevdesc->u.tevconf.alpha_bias = (GXTevBias)(0);
        tevdesc->u.tevconf.alpha_clamp = (u8)(0);
        tevdesc->u.tevconf.alpha_out_reg = (GXTevRegID)(0);
    } else {
        tevdesc->u.tevconf.alpha_op = (GXTevOp)(tev->a_op);
        tevdesc->u.tevconf.alpha_a = (GXTevAlphaArg)(TExpDefault(tev->a_in[0].arg, GX_CA_ZERO));
        tevdesc->u.tevconf.alpha_b = (GXTevAlphaArg)(TExpDefault(tev->a_in[1].arg, GX_CA_ZERO));
        tevdesc->u.tevconf.alpha_c = (GXTevAlphaArg)(TExpDefault(tev->a_in[2].arg, GX_CA_ZERO));
        tevdesc->u.tevconf.alpha_d = (GXTevAlphaArg)(TExpDefault(tev->a_in[3].arg, GX_CA_ZERO));
        tevdesc->u.tevconf.alpha_scale = (GXTevScale)(TExpDefault(tev->a_scale, 0));
        tevdesc->u.tevconf.alpha_bias = (GXTevBias)(TExpDefault(tev->a_bias, 0));
        tevdesc->u.tevconf.alpha_clamp = (u8)(tev->a_clamp != 0 ? GX_TRUE : GX_FALSE);

        if (!(tev->a_dst != HSD_TE_UNDEF)) __assert("texp.c", 1429, "tev->a_dst != HSD_TE_UNDEF");
        tevdesc->u.tevconf.alpha_out_reg = (GXTevRegID)(dst[tev->a_dst]);
        if (tevdesc->u.tevconf.alpha_out_reg == 0) {
            *init_aprev = 0;
        }
    }
    tevdesc->u.tevconf.mode = (GXTevClampMode)(GX_TC_LINEAR);
}

static void HSD_TExpSetReg(HSD_TExp* texp)
{
    static GXTevKColorID id1[4] = { GX_KCOLOR0, GX_KCOLOR1, GX_KCOLOR2, GX_KCOLOR3 };
    static GXTevRegID id2[3] = { GX_TEVREG0, GX_TEVREG1, GX_TEVREG2 };
    int i;
    GXColor reg[8];
    u32 changed;
    HSD_TECnst* clist;

    clist = &texp->cnst;
    changed = 0;

    while (clist != 0) {
        if (!(clist->type == HSD_TE_CNST)) __assert("texp.c", 1453, "clist->type == HSD_TE_CNST");
        if (clist->reg < 8) {
            changed |= 1 << clist->reg;
            if (clist->comp == HSD_TE_RGB) {
                switch (clist->ctype) {
                case HSD_TE_U8: {
                    GXColor col;
                    col = *(GXColor*) clist->val;
                    col.a = reg[clist->reg].a;
                    reg[clist->reg] = col;
                    break;
                }
                case HSD_TE_U32: {
                    u32* ptr = (u32*)clist->val;
                    reg[clist->reg].r = ptr[0] < 0x100 ? ptr[0] : 0xFF;
                    reg[clist->reg].g = ptr[1] < 0x100 ? ptr[1] : 0xFF;
                    reg[clist->reg].b = ptr[2] < 0x100 ? ptr[2] : 0xFF;
                    break;
                }
                default: {
                    int r;
                    int g;
                    int b;
                    switch (clist->ctype) {
                    case HSD_TE_U16: {
                        u16* ptr = (u16*)clist->val;
                        r = ptr[0];
                        g = ptr[1];
                        b = ptr[2];
                        break;
                    }
                    case HSD_TE_F32: {
                        f32* ptr = (f32*)clist->val;
                        r = 0xFF * ptr[0];
                        g = 0xFF * ptr[1];
                        b = 0xFF * ptr[2];
                        break;
                    }
                    default: {
                        f64* ptr = (f64*)clist->val;
                        r = 0xFF * ptr[0];
                        g = 0xFF * ptr[1];
                        b = 0xFF * ptr[2];
                        break;
                    }
                    }
                    reg[clist->reg].r = r > 0xFF ? 0xFF : r < 0 ? 0 : r;
                    reg[clist->reg].g = g > 0xFF ? 0xFF : g < 0 ? 0 : g;
                    reg[clist->reg].b = b > 0xFF ? 0xFF : b < 0 ? 0 : b;
                }
                }
            } else {
                int x;
                u8 val;
                switch (clist->ctype) {
                case HSD_TE_U8:
                    x = *(u8*) clist->val;
                    val = x;
                    break;
                case HSD_TE_U16: {
                    x = *(u16*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                }
                case HSD_TE_U32:
                    x = *(u32*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                case HSD_TE_F32:
                    x = 0xFF * *(f32*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                default:
                    x = 0xFF * *(f64*) clist->val;
                    val = x > 0xFF ? 0xFF : x < 0 ? 0 : x;
                    break;
                }
                if (clist->reg < 4) {
                    switch (clist->idx) {
                    case 0:
                        reg[clist->reg].r = val;
                        break;
                    case 1:
                        reg[clist->reg].g = val;
                        break;
                    case 2:
                        reg[clist->reg].b = val;
                        break;
                    default:
                        reg[clist->reg].a = val;
                        break;
                    }
                } else if (clist->idx == 3) {
                    reg[clist->reg].a = val;
                } else {
                    reg[clist->reg].r = val;
                    reg[clist->reg].g = val;
                    reg[clist->reg].b = val;
                }
            }
        }
        clist = &clist->next->cnst;
    }
    if (changed != 0) {
        GXPixModeSync();
        for (i = 0; i < 4; i++) {
            if (changed & (1 << i)) {
                GXSetTevKColor(id1[i], reg[i]);
            }
        }
        for (i = 4; i < 7; i++) {
            if (changed & (1 << i)) {
                GXSetTevColor(id2[i - 4], reg[i]);
            }
        }
        HSD_StateInvalidate(0x10);
        GXPixModeSync();
    }
}

void HSD_TExpSetupTev(HSD_TExpTevDesc* tevdesc, HSD_TExp* texp)
{
    HSD_TExpSetReg(texp);
    for (; tevdesc != 0; tevdesc = (HSD_TExpTevDesc*) tevdesc->desc.next) {
        if (tevdesc->tobj != 0) {
            tevdesc->desc.map = tevdesc->tobj->id;
            tevdesc->desc.coord = ((HSD_TExpTextureView*)tevdesc->tobj)->coord;
        }
        HSD_StateAssignTev();
        HSD_SetupTevStage(&tevdesc->desc);
    }
}

int HSD_TExpCompile(HSD_TExp* texp, HSD_TExpTevDesc** tevdesc,
                    HSD_TExp** texp_list)
{
    int num, i, val;
    HSD_TExpRes res;
    HSD_TExp* order[32];
    HSD_TExpDag list[32];
    int init_cprev = 1;
    int init_aprev = 1;

    if (!(tevdesc)) __assert("texp.c", 1655, "tevdesc");
    if (!(texp_list)) __assert("texp.c", 1656, "texp_list");

    memset(&res, 0, sizeof(HSD_TExpRes));

    HSD_TExpRef(texp, HSD_TE_RGB);
    HSD_TExpRef(texp, HSD_TE_A);
    HSD_TExpSimplify(texp);

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    for (i = 0; i < num; ++i) {
        val = TExpAssignReg(order[i], &res);
        if (!(val >= 0)) __assert("texp.c", 1688, "val >= 0");
    }

    for (i = num - 1; i >= 0; --i) {
        HSD_TExpSimplify2(order[i]);
    }

    num = HSD_TExpMakeDag(texp, list);
    HSD_TExpSchedule(num, list, order, &res);
    *tevdesc = 0;
    for (i = 0; i < num; ++i) {
        HSD_TExpTevDesc* tdesc = (HSD_TExpTevDesc*)hsdAllocMemPiece(sizeof(HSD_TExpTevDesc));
        tdesc->desc.stage = HSD_Index2TevStage(i);
        TExp2TevDesc(order[(num - i) - 1], tdesc, &init_cprev, &init_aprev);
        tdesc->desc.next = &(*tevdesc)->desc;
        *tevdesc = tdesc;
    }

    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_TEV, 1);
    *texp_list = HSD_TExpFreeList(*texp_list, HSD_TE_CNST, 0);
    return num;
}

void HSD_TExpFreeTevDesc(HSD_TExpTevDesc* tdesc)
{
    HSD_TExpTevDesc* next = tdesc;
    while (next != 0) {
        HSD_TExpTevDesc* temp = (HSD_TExpTevDesc*) next->desc.next;
        hsdFreeMemPiece(next, sizeof(HSD_TExpTevDesc));
        next = temp;
    }
}
#ifdef __cplusplus
}
#endif
