/* Compile with deferred inlining; MW emits retained definitions in reverse order. */
#include "game/maximum/GSAPI/baselib/fobj.h"
#include "game/maximum/GSAPI/baselib/spline.h"
#define HSD_ASSERT(line, condition) do { int check = (condition); if (!check) __assert("fobj.c", line, #condition); } while (0)
#ifdef __cplusplus
extern "C" {
#endif
void __assert(const char*, int, const char*);
void* memset(void*, int, unsigned long);
void* GSmemGetSysdolAllocator(unsigned int);
int GSmemGetFreePool(void*);
void* GSmemAllocPool(void*);
unsigned char GSmemIsRegistrationPool(void*, void*);
void GSmemFreePool(void*, void*);
static void dumpObjAlloc(HSD_ObjAllocData* data, const char* label);
static unsigned int FObjLoadData(HSD_FObj* fobj);
static HSD_ObjAllocData alloc_data;

static inline unsigned int HSD_FObjSetState(HSD_FObj* fobj, unsigned int state)
{
    if (fobj) {
        fobj->flags = (fobj->flags & 0xF0) | (state & 0xF);
    }
    return state;
}

static inline unsigned int HSD_FObjGetState(HSD_FObj* fobj)
{
    if (fobj == 0) return 0;
    return fobj->flags & 0xF;
}

static inline void HSD_FObjReqAnim(HSD_FObj* fobj, float startframe)
{
    if (fobj == 0) {
        return;
    }

    fobj->ad = fobj->ad_head;
    fobj->time = (float) fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.f;
    fobj->p1 = 0.f;
    fobj->d0 = 0.f;
    fobj->d1 = 0.f;
    HSD_FObjSetState(fobj, 1);
}

static inline void FObj_FlushKeyData(HSD_FObj* fobj, void* obj,
                                     HSD_ObjUpdateFunc obj_update, float rate)
{
    if (fobj->op_intrp == HSD_A_OP_KEY) {
        HSD_FObjInterpretAnim(fobj, obj, obj_update, rate);
    }
}

static inline void HSD_FObjStopAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update,
                      float rate)
{
    if (fobj == 0) {
        return;
    }

    FObj_FlushKeyData(fobj, obj, obj_update, rate);
    HSD_FObjSetState(fobj, 0);
}

union parseFloat_u {
    float f;
    unsigned int d;
};

static inline float parseFloat(unsigned char** pos, unsigned char frac)
{
    union parseFloat_u u;
    float numer;
    int denom;

    if (frac == HSD_A_FRAC_FLOAT) {
        u.d = (int) ((*pos)++)[0];
        u.d |= ((*pos)++)[0] << 8;
        u.d |= ((*pos)++)[0] << 16;
        u.d |= ((*pos)++)[0] << 24;
        return u.f;
    }

    denom = (1 << (frac & 0x1F));
    switch (frac & 0xE0) {
    case HSD_A_FRAC_S8:
        numer = (signed char) (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_U8:
        numer = (*pos)[0];
        *pos += 1;
        break;
    case HSD_A_FRAC_S16:
        numer = ((signed char) (*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    case HSD_A_FRAC_U16:
        numer = ((*pos)[1] << 8) | (*pos)[0];
        *pos += 2;
        break;
    default:
        return 0.0f;
    }
    return numer / denom;
}

static inline unsigned char parseOpCode(unsigned char** curr_parse)
{
    return (**curr_parse) & 0xF;
}

static inline unsigned int parsePackInfo(unsigned char** adp)
{
    unsigned char d;
    unsigned int nb_pack;
    int shift;

    d = *(*adp)++;
    nb_pack = ((d >> 4) & 7) + 1;
    shift = 3;
    if (!(d & 0x80)) {
        return nb_pack;
    }
    do {
        d = *(*adp)++;
        nb_pack += (d & 0x7F) << shift;
        shift += 7;
    } while (d & 0x80);
    return nb_pack;
}

static inline void FObjLaunchKeyData(HSD_FObj* fobj)
{
    if ((fobj->flags & 0x40) != 0) {
        fobj->op_intrp = fobj->op;
        fobj->flags &= ~0x40;
        fobj->flags |= 0x80;
        fobj->p0 = fobj->p1;
    }
}

static inline int parseWait(unsigned char** adp)
{
    unsigned char d;
    int wait = 0;
    int shift = 0;

    do {
        d = *(*adp)++;
        wait |= (d & 0x7f) << shift;
        shift += 7;
    } while (d & 0x80);

    return wait;
}

static inline unsigned int FObjLoadWait(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x171, st == FOBJ_LOAD_WAIT);

    if ((unsigned) (fobj->ad - fobj->ad_head) >= fobj->length) {
        return 6;
    } else {
        fobj->fterm = parseWait(&fobj->ad);
        fobj->flags |= 0x20;
        return HSD_FObjSetState(fobj, 2);
    }
}

static inline unsigned int FObjAnimCON(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x184, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    if (fobj->op_intrp != 5) {
        fobj->d0 = fobj->d1;
        fobj->d1 = 0.0F;
    }

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

static inline unsigned int FObjAnimLinear(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x198, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    if (fobj->op_intrp != 5) {
        fobj->d0 = fobj->d1;
        fobj->d1 = 0.0F;
    }

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

static inline unsigned int FObjAnimSPL0(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1ac, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->d0 = fobj->d1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->d1 = 0.0F;

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

static inline unsigned int FObjAnimSPL(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1be, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->p0 = fobj->p1;
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->d0 = fobj->d1;
    fobj->d1 = parseFloat(&fobj->ad, fobj->frac_slope);

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

static inline unsigned int FObjAnimSLP(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1d1, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    fobj->d0 = fobj->d1;
    fobj->d1 = parseFloat(&fobj->ad, fobj->frac_slope);

    return HSD_FObjGetState(fobj);
}

static inline unsigned int FObjAnimKey(HSD_FObj* fobj)
{
    unsigned int st = HSD_FObjGetState(fobj);
    HSD_ASSERT(0x1ee, st == FOBJ_LOAD_DATA0 || st == FOBJ_LOAD_DATA);

    FObjLaunchKeyData(fobj);
    fobj->p1 = parseFloat(&fobj->ad, fobj->frac_value);
    fobj->flags |= 0x40;

    return HSD_FObjSetState(fobj, st == FOBJ_LOAD_DATA0 ? 3 : 4);
}

static inline void FObjUpdateAnim(HSD_FObj* fobj, void* obj, HSD_ObjUpdateFunc obj_update)
{
    float phi_f0;
    HSD_ObjData fobjdata;

    if (obj_update == 0) {
        return;
    }
    switch (fobj->op_intrp) {
    case HSD_A_OP_KEY:
        if (fobj->flags & 0x80) {
            fobjdata.fv = fobj->p0;
            fobj->flags &= 0xFFFFFF7F;
        } else {
            return;
        }
        break;
    case HSD_A_OP_CON:
        if (fobj->time >= fobj->fterm) {
            phi_f0 = fobj->p1;
        } else {
            phi_f0 = fobj->p0;
        }
        fobjdata.fv = phi_f0;
        break;
    case HSD_A_OP_LIN:
        if (fobj->flags & 0x20) {
            fobj->flags = fobj->flags & 0xFFFFFFDF;
            if (fobj->fterm != 0) {
                fobj->d0 = (fobj->p1 - fobj->p0) / fobj->fterm;
            } else {
                fobj->d0 = 0;
                fobj->p0 = fobj->p1;
            }
        }
        fobjdata.fv = fobj->d0 * fobj->time + fobj->p0;
        break;
    case HSD_A_OP_SPL0:
    case HSD_A_OP_SPL:
    case HSD_A_OP_SLP:
        if (fobj->fterm != 0) {
            fobjdata.fv =
                splGetHelmite(1.0 / fobj->fterm, fobj->time, fobj->p0,
                              fobj->p1, fobj->d0, fobj->d1);
        } else {
            fobjdata.fv = fobj->p1;
        }
        break;
    default:
        break;
    }
    obj_update(obj, fobj->obj_type, &fobjdata);
}

HSD_ObjAllocData* HSD_FObjGetAllocData(void)
{
    return &alloc_data;
}

void HSD_FObjInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_FObjGetAllocData(), sizeof(HSD_FObj), 4);
}

void HSD_FObjRemove(HSD_FObj* fobj)
{
    if (!fobj) {
        return;
    }

    HSD_FObjFree(fobj);
}

void HSD_FObjRemoveAll(HSD_FObj* fobj)
{
    if (fobj == 0) {
        return;
    }
    HSD_FObjRemoveAll(fobj->next);
    HSD_FObjRemove(fobj);
}

void HSD_FObjReqAnimAll(HSD_FObj* fobj, float startframe)
{
    HSD_FObj* fp;

    if (fobj == 0) {
        return;
    }

    for (fp = fobj; fp != 0; fp = fp->next) {
        HSD_FObjReqAnim(fp, startframe);
    }
}

void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj,
                         HSD_ObjUpdateFunc obj_update, float rate)
{
    for (; fobj != 0; fobj = fobj->next) {
        HSD_FObjStopAnim(fobj, obj, obj_update, rate);
    }
}

static unsigned int FObjLoadData(HSD_FObj* fobj)
{
    if ((unsigned) (fobj->ad - fobj->ad_head) >= fobj->length) {
        return 6;
    } else {
        fobj->op_intrp = fobj->op;
        if (fobj->nb_pack == 0) {
            fobj->op = parseOpCode(&fobj->ad);
            fobj->nb_pack = parsePackInfo(&fobj->ad);
        }

        fobj->nb_pack -= 1;

        switch (fobj->op) {
        case HSD_A_OP_CON:
            return FObjAnimCON(fobj);

        case HSD_A_OP_LIN:
            return FObjAnimLinear(fobj);

        case HSD_A_OP_SPL0:
            return FObjAnimSPL0(fobj);

        case HSD_A_OP_SPL:
            return FObjAnimSPL(fobj);

        case HSD_A_OP_SLP:
            return FObjAnimSLP(fobj);

        case HSD_A_OP_KEY:
            return FObjAnimKey(fobj);

        default:
            return 0;
        }
    }
}

void HSD_FObjInterpretAnim(HSD_FObj* fobj, void* obj,
                           HSD_ObjUpdateFunc obj_update, float rate)
{
    float fterm;
    unsigned int state;

    fterm = 0.0F;
    state = fobj != 0 ? HSD_FObjGetState(fobj) : 0;
    if (state != 0 && !(fobj->time += rate, (fobj->time < 0.0))) {
        for (;;) {
            switch (state) {
            case 6: {
                fobj->time += fterm;
                FObjLaunchKeyData(fobj);
                FObjUpdateAnim(fobj, obj, obj_update);
                return;
            }
            case 1:
            case 2: {
                state = FObjLoadData(fobj);
                break;
            }
            case 3: {
                if ((fobj->flags & 0x80) != 0) {
                    FObjUpdateAnim(fobj, obj, obj_update);
                }
                state = FObjLoadWait(fobj);
                break;
            }
            case 4: {
                if (fobj->fterm <= fobj->time) {
                    unsigned char _[8];
                    state =
#ifdef MUST_MATCH
                        state =
#endif
                            3;

                    fterm = fobj->fterm;
                    fobj->time -= fobj->fterm;
                    HSD_FObjSetState(fobj, state);
                    break;
                }
                FObjUpdateAnim(fobj, obj, obj_update);
                state =
#ifdef MUST_MATCH
                    state =
#endif
                        5;
                HSD_FObjSetState(fobj, state);
                return;
            }
            case 5: {
                state =
#ifdef MUST_MATCH
                    state =
#endif
                        4;
                HSD_FObjSetState(fobj, state);
                break;
            }
            case 0:
                return;
            }
        }
    }
}

void HSD_FObjInterpretAnimAll(void* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, float rate)
{
    HSD_FObj* fobjNew = (HSD_FObj*) fobj;
    while (fobjNew != 0) {
        HSD_FObjInterpretAnim(fobjNew, obj, obj_update, rate);
        fobjNew = fobjNew->next;
    }
}

static void dumpObjAlloc(HSD_ObjAllocData* data, const char* label) { }

HSD_FObj* HSD_FObjLoadDesc(HSD_FObjDesc* desc)
{
    if (desc != 0) {
        HSD_FObj* fobj = HSD_FObjAlloc();
        fobj->next = HSD_FObjLoadDesc(desc->next);
        fobj->startframe = desc->startframe;
        fobj->obj_type = desc->type;
        fobj->frac_value = desc->frac_value;
        fobj->frac_slope = desc->frac_slope;
        fobj->ad_head = desc->ad;
        fobj->length = desc->length;
        fobj->flags = 0;
        return fobj;
    }
    return 0;
}

HSD_FObj* HSD_FObjAlloc(void)
{
    HSD_FObj* new_obj;
    void* allocator = GSmemGetSysdolAllocator(sizeof(HSD_FObj));
    if (allocator && GSmemGetFreePool(allocator)) {
        new_obj = (HSD_FObj*)GSmemAllocPool(allocator);
        if (!new_obj) __assert("fobj.c", 0x2ff, "new");
        return new_obj;
    }
    new_obj = (HSD_FObj*)HSD_ObjAlloc(&alloc_data);
    dumpObjAlloc(&alloc_data, "fobj: alloc");
    if (!new_obj) __assert("fobj.c", 0x306, "new");
    memset(new_obj, 0, sizeof(HSD_FObj));
    return new_obj;
}

void HSD_FObjFree(HSD_FObj* fobj)
{
    void* allocator = GSmemGetSysdolAllocator(sizeof(HSD_FObj));
    if (allocator && GSmemIsRegistrationPool(allocator, fobj)) {
        GSmemFreePool(allocator, fobj);
    } else {
        HSD_ObjFree(&alloc_data, fobj);
        dumpObjAlloc(&alloc_data, "fobj: free");
    }
}
#ifdef __cplusplus
}
#endif
