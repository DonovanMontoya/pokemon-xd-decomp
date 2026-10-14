#ifndef HSD_DOBJ_H
#define HSD_DOBJ_H
#include "game/maximum/GSAPI/baselib/class.h"
#include "game/maximum/GSAPI/baselib/aobj.h"
#include "game/maximum/GSAPI/baselib/mtx_base.h"
typedef struct HSD_DObjDesc {
    char* class_name;
    struct HSD_DObjDesc* next;
    void *mobjdesc, *pobjdesc;
} HSD_DObjDesc;
typedef struct HSD_DObjInfo {
    HSD_ClassInfo parent;
    void (*disp)(HSD_DObj*, HSD_Mtx, HSD_Mtx, unsigned int);
    int (*load)(HSD_DObj*, HSD_DObjDesc*);
    HSD_ObjUpdateFunc update;
} HSD_DObjInfo;
typedef struct HSD_MatAnim { struct HSD_MatAnim* next; void *aobjdesc, *texanim, *renderanim; } HSD_MatAnim;
typedef struct HSD_ShapeAnim HSD_ShapeAnim;
typedef struct HSD_ShapeAnimDObj { struct HSD_ShapeAnimDObj* next; HSD_ShapeAnim* shapeanim; } HSD_ShapeAnimDObj;
#ifdef __cplusplus
extern "C" {
#endif
extern HSD_DObjInfo hsdDObj;
void HSD_DObjSetCurrent(HSD_DObj*);
void HSD_DObjRemoveAnimAllByFlags(HSD_DObj*, unsigned int);
void HSD_DObjAddAnimAll(HSD_DObj*, HSD_MatAnim*, HSD_ShapeAnimDObj*);
void HSD_DObjReqAnimAllByFlags(HSD_DObj*, float, unsigned int);
void HSD_DObjAnimAll(HSD_DObj*);
HSD_DObj* HSD_DObjLoadDesc(HSD_DObjDesc*);
void HSD_DObjRemoveAll(HSD_DObj*);
void HSD_DObjResolveRefsAll(HSD_DObj*, HSD_DObjDesc*);
void HSD_DObjDisp(HSD_DObj*, HSD_Mtx, HSD_Mtx, unsigned int);
void HSD_DObjCountVertices(HSD_DObj*, unsigned int*, unsigned int*);
#ifdef __cplusplus
}
#endif
#define HSD_DOBJ(o) ((HSD_DObj*)(o))
#define HSD_DOBJ_INFO(o) ((HSD_DObjInfo*)(o))
#define HSD_DOBJ_METHOD(o) HSD_DOBJ_INFO((o)->class_info)
#endif
