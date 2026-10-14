#ifndef HSD_ROBJ_H
#define HSD_ROBJ_H
#include "game/maximum/GSAPI/baselib/aobj.h"
typedef union HSD_RObjPayload HSD_RObjPayload;
typedef struct HSD_RObjDesc HSD_RObjDesc;
typedef struct HSD_ByteCodeExpDesc HSD_ByteCodeExpDesc;
typedef struct HSD_ExpDesc HSD_ExpDesc;
typedef struct HSD_Exp HSD_Exp;
typedef struct HSD_IKHintDesc HSD_IKHintDesc;
typedef struct HSD_IKHint HSD_IKHint;
typedef struct HSD_RvalueList HSD_RvalueList;
typedef struct HSD_Rvalue HSD_Rvalue;
#define ROBJ_TYPE_MASK 0x70000000
#define REFTYPE_EXP 0x00000000
#define REFTYPE_JOBJ 0x10000000
#define REFTYPE_LIMIT 0x20000000
#define REFTYPE_BYTECODE 0x30000000
#define REFTYPE_IKHINT 0x40000000

struct HSD_Rvalue {
    HSD_Rvalue* next;
    unsigned int flags;
    HSD_JObj* jobj;
};

struct HSD_RvalueList {
    unsigned int flags;
    HSD_Joint* joint;
};

struct HSD_IKHint {
    float bone_length;
    float rotate_x;
};

struct HSD_IKHintDesc {
    float bone_length;
    float rotate_x;
};

struct HSD_Exp {
    union HSD_Exp_expr {
        float (*func)(void*);
        unsigned char* bytecode;
    } expr;
    HSD_Rvalue* rvalue;
    unsigned int nb_args;
    unsigned char is_bytecode;
};

struct HSD_ExpDesc {
    float (*func)(void*);
    HSD_RvalueList* rvalue;
};

struct HSD_ByteCodeExpDesc {
    unsigned char* bytecode;
    HSD_RvalueList* rvalue;
};

union HSD_RObjPayload {
    HSD_JObj* jobj;
    HSD_Exp exp;
    float limit;
    HSD_IKHint ik_hint;
};
#define ROBJ_U(o) (*(HSD_RObjPayload*)((o)->expression))

struct HSD_RObjDesc {
    HSD_RObjDesc* next;
    unsigned int flags; // 0x04
    union HSD_RObjDesc_u {
        unsigned int i;
        HSD_ExpDesc* exp;
        HSD_ByteCodeExpDesc* bcexp;
        HSD_IKHintDesc* ik_hint;
        HSD_Joint* joint;
        float limit;
    } u;
};

struct HSD_RObjAnimJoint {
    HSD_RObjAnimJoint* next;
    HSD_AObjDesc* aobjdesc;
};


#ifdef __cplusplus
extern "C" {
#endif
void _HSD_RObjForgetMemory(void*, void*);
void HSD_RObjInitAllocData(void);
HSD_ObjAllocData* HSD_RObjGetAllocData(void);
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void);
HSD_RObj* HSD_RObjAlloc(void);
HSD_RObj* HSD_RObjGetByType(HSD_RObj*, unsigned int, unsigned int);
void HSD_RObjAnimAll(HSD_RObj*);
void HSD_RObjRemoveAnimAllByFlags(HSD_RObj*, unsigned int);
void HSD_RObjRemoveAnimAll(HSD_RObj*);
void HSD_RObjReqAnimAllByFlags(HSD_RObj*, float, unsigned int);
void HSD_RObjReqAnimAll(HSD_RObj*, float);
void HSD_RObjAddAnimAll(HSD_RObj*, HSD_RObjAnimJoint*);
void HSD_RObjRemoveAll(HSD_RObj*);
void HSD_RObjResolveRefsAll(HSD_RObj*, HSD_RObjDesc*);
HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc*);
void HSD_RObjUpdateAll(HSD_RObj*, void*, HSD_ObjUpdateFunc);
int HSD_RObjGetGlobalPosition(HSD_RObj*, int, HSD_Vec3*);
float* HSD_SetExpArgBuffer(float*, unsigned int);
#ifdef __cplusplus
}
#endif
#endif
