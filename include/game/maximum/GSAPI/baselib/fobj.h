#ifndef HSD_FOBJ_H
#define HSD_FOBJ_H
#include "game/maximum/GSAPI/baselib/quatlib.h"
#include "game/maximum/GSAPI/baselib/objalloc.h"
typedef union HSD_ObjData HSD_ObjData;
typedef struct HSD_FObj HSD_FObj;
typedef void (*HSD_ObjUpdateFunc)(void*, int, HSD_ObjData*);
#ifdef __cplusplus
extern "C" {
#endif
#define HSD_A_OP_NONE 0
#define HSD_A_OP_CON 1
#define HSD_A_OP_LIN 2
#define HSD_A_OP_SPL0 3
#define HSD_A_OP_SPL 4
#define HSD_A_OP_SLP 5
#define HSD_A_OP_KEY 6

#define HSD_A_FRAC_FLOAT (0 << 5)
#define HSD_A_FRAC_S16 (1 << 5)
#define HSD_A_FRAC_U16 (2 << 5)
#define HSD_A_FRAC_S8 (3 << 5)
#define HSD_A_FRAC_U8 (4 << 5)

#define FOBJ_LOAD_DATA0 1
#define FOBJ_LOAD_DATA 2
#define FOBJ_LOAD_WAIT 3

#define TYPE_ROBJ 1
#define TYPE_JOBJ 12

/// An animation track's keyframe stream: opcodes and packed values, read by
/// HSD_FObjInterpretAnim.
typedef unsigned char HSD_FObjData;

struct HSD_FObj {
    struct HSD_FObj* next;
    unsigned char* ad;
    unsigned char* ad_head;
    unsigned int length;
    unsigned char flags;
    unsigned char op;
    unsigned char op_intrp;
    unsigned char obj_type;
    unsigned char frac_value;
    unsigned char frac_slope;
    unsigned short nb_pack;
    short startframe;
    unsigned short fterm;
    float time;
    float p0;
    float p1;
    float d0;
    float d1;
};

typedef struct _HSD_FObjDesc {
    struct _HSD_FObjDesc* next;
    unsigned int length;
    float startframe;
    unsigned char type;
    unsigned char frac_value;
    unsigned char frac_slope;
    unsigned char dummy0;
    HSD_FObjData* ad;
} HSD_FObjDesc;

union HSD_ObjData {
    float fv;
    int iv;
    HSD_Vec3 p;
};

HSD_ObjAllocData* HSD_FObjGetAllocData(void);
void HSD_FObjInitAllocData(void);
void HSD_FObjRemove(HSD_FObj* fobj);
void HSD_FObjRemoveAll(HSD_FObj* fobj);
void HSD_FObjReqAnimAll(HSD_FObj* fobj, float startframe);
void HSD_FObjStopAnimAll(HSD_FObj* fobj, void* obj,
                         HSD_ObjUpdateFunc obj_update, float rate);
void HSD_FObjInterpretAnim(HSD_FObj* fobj, void* obj,
                           HSD_ObjUpdateFunc obj_update, float rate);
void HSD_FObjInterpretAnimAll(void* fobj, void* obj,
                              HSD_ObjUpdateFunc obj_update, float rate);
HSD_FObj* HSD_FObjLoadDesc(HSD_FObjDesc* desc);
HSD_FObj* HSD_FObjAlloc(void);
void HSD_FObjFree(HSD_FObj* fobj);

#ifdef __cplusplus
}
#endif
#endif
