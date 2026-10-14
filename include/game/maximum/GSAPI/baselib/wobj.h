#ifndef HSD_WOBJ_H
#define HSD_WOBJ_H
#include "game/maximum/GSAPI/baselib/class.h"
#include "game/maximum/GSAPI/baselib/robj.h"
typedef struct HSD_WObjDesc { char* class_name; HSD_Vec3 pos; HSD_RObjDesc* robjdesc; } HSD_WObjDesc;
typedef struct HSD_WObjInfo { HSD_ClassInfo parent; int (*load)(HSD_WObj*, HSD_WObjDesc*); HSD_ObjUpdateFunc update; } HSD_WObjInfo;
typedef struct HSD_WObjAnim { HSD_AObjDesc* aobjdesc; HSD_RObjAnimJoint* robjanim; } HSD_WObjAnim;
#define HSD_WOBJ_INFO(i) ((HSD_WObjInfo*)(i))
#define HSD_WOBJ_METHOD(o) HSD_WOBJ_INFO((o)->parent.class_info)
#define HSD_OBJECT_PARENT_INFO(o) ((o)->parent.head.parent)
#ifdef __cplusplus
extern "C" {
#endif
extern HSD_ClassInfo hsdObj;
extern HSD_WObjInfo hsdWObj;
void HSD_WObjRemoveAnim(HSD_WObj*);
void HSD_WObjReqAnim(HSD_WObj*, float);
void HSD_WObjAddAnim(HSD_WObj*, HSD_WObjAnim*);
void HSD_WObjInterpretAnim(HSD_WObj*);
void HSD_WObjInit(HSD_WObj*, HSD_WObjDesc*);
HSD_WObj* HSD_WObjLoadDesc(HSD_WObjDesc*);
void HSD_WObjSetPosition(HSD_WObj*, HSD_Vec3*);
void HSD_WObjGetPosition(HSD_WObj*, HSD_Vec3*);
HSD_WObj* HSD_WObjAlloc(void);
#ifdef __cplusplus
}
#endif
#endif
