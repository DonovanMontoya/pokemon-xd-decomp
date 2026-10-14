#ifndef HSD_AOBJ_H
#define HSD_AOBJ_H
#include "game/maximum/GSAPI/baselib/fobj.h"
#include "game/maximum/GSAPI/baselib/animation_objects.h"
typedef struct HSD_AObjDesc HSD_AObjDesc;
typedef struct HSD_AnimJoint HSD_AnimJoint;
#ifdef __cplusplus
extern "C" {
#endif
#define AOBJ_REWINDED (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE (1 << 28)
#define AOBJ_LOOP (1 << 29)
#define AOBJ_NO_ANIM (1 << 30)

typedef enum _AObj_Arg_Type {
    AOBJ_ARG_A,
    AOBJ_ARG_AF,
    AOBJ_ARG_AV,
    AOBJ_ARG_AU,
    AOBJ_ARG_AO,
    AOBJ_ARG_AOF,
    AOBJ_ARG_AOV,
    AOBJ_ARG_AOU,
    AOBJ_ARG_AOT,
    AOBJ_ARG_AOTF,
    AOBJ_ARG_AOTV,
    AOBJ_ARG_AOTU,
} AObj_Arg_Type;

typedef union _callbackArg {
    float f;
    unsigned int d;
    void* v;
} callbackArg;

struct HSD_AObj {
    unsigned int flags;
    float curr_frame;
    float rewind_frame;
    float end_frame;
    float framerate;
    HSD_FObj* fobj;
    struct HSD_Obj* hsd_obj;
};

struct HSD_AObjDesc {
    unsigned int flags;
    float end_frame;
    HSD_FObjDesc* fobjdesc;
    /// The descriptor of the object to animate, whose address is the key
    /// that object is registered under once loaded (#HSD_IDGetDataFromTable):
    /// a joint, a material, or another kind. Loaded as a joint if nothing is
    /// registered under it yet.
    void* obj_id;
};

struct HSD_AnimJoint {
    HSD_AnimJoint* child;
    HSD_AnimJoint* next;
    HSD_AObjDesc* aobjdesc;
    HSD_RObjAnimJoint* robj_anim;
    unsigned int flags;
};

void HSD_AObjInitAllocData(void);
HSD_ObjAllocData* HSD_AObjGetAllocData(void);
unsigned int HSD_AObjGetFlags(HSD_AObj* aobj);
void HSD_AObjSetFlags(HSD_AObj* aobj, unsigned int flags);
void HSD_AObjClearFlags(HSD_AObj* aobj, unsigned int flags);
void HSD_AObjInitEndCallBack(void);
void HSD_AObjInvokeCallBacks(void);
void HSD_AObjReqAnim(HSD_AObj* aobj, float frame);

void HSD_AObjInterpretAnim(HSD_AObj* aobj, void* obj,
                           HSD_ObjUpdateFunc update_func);

HSD_AObj* HSD_AObjLoadDesc(HSD_AObjDesc* aobjdesc);
void HSD_AObjRemove(HSD_AObj* aobj);
void HSD_ForeachAnim(void* obj, HSD_Type type, HSD_TypeMask mask, void* func,
                     AObj_Arg_Type arg_type, ...);
void HSD_AObjSetRate(HSD_AObj* aobj, float rate);
void _HSD_AObjForgetMemory(void* low, void* high);


#ifdef __cplusplus
}
#endif
#endif
