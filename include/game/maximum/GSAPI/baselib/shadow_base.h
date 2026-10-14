#ifndef HSD_SHADOW_BASE_H
#define HSD_SHADOW_BASE_H
#include "game/maximum/GSAPI/baselib/cobj.h"
#include "game/maximum/GSAPI/baselib/tobj.h"
typedef struct HSD_Shadow { HSD_SList* objects; HSD_CObj* camera; HSD_TObj* texture; float scaleS,scaleT,transS,transT; int active; unsigned char intensity; void* user_data; } HSD_Shadow;
typedef struct HSD_ViewingRect { Vec3 origin,up_v,right_v,eye_v,eye_vn; float distance,top,bottom,left,right; signed char perspective:1; signed char invalid:1; } HSD_ViewingRect;
HSD_ObjAllocData* HSD_ShadowGetAllocData(void);
void HSD_ShadowInitAllocData(void);
HSD_Shadow* HSD_ShadowAlloc(void);
void HSD_ShadowSetSize(HSD_Shadow*,unsigned short,unsigned short);
void HSD_ShadowFreeTexture(HSD_Shadow*);
void HSD_ShadowSetActive(HSD_Shadow*,int);
void HSD_ShadowAddObject(HSD_Shadow*,HSD_JObj*);
void HSD_ShadowDeleteObject(HSD_Shadow*,HSD_JObj*);
void HSD_ShadowCopyTex(HSD_Shadow*);
void HSD_ShadowRender(HSD_Shadow*);
void HSD_ShadowCopyLightPos(HSD_Shadow*,HSD_LObj*,float);
void HSD_ShadowSetViewingRect(HSD_Shadow*,float,float,float,float);
void HSD_ShadowSetDebug(unsigned char);
void HSD_ViewingRectInit(HSD_ViewingRect*,Vec3*,Vec3*,Vec3*,int);
int HSD_ViewingRectCheck(HSD_ViewingRect*);
void HSD_ViewingRectAddRect(HSD_ViewingRect*,Vec3*,float,float,float,float);
#endif
