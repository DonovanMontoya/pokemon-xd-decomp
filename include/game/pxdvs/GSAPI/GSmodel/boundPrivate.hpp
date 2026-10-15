#ifndef MODEL_BOUND_PRIVATE_HPP
#define MODEL_BOUND_PRIVATE_HPP
#include <dolphin/mtx.h>
#include <libc/stddef.h>
struct GSmtx {Mtx m;};
struct BoundPoint: Vec {BoundPoint(f32 a,f32 b,f32 c) {x=a;y=b;z=c;}};
struct _HSD_PObj {void *next,*classInfo,*attributes;u16 flags,displayListSize;void *displayList;};
struct BoundModel {u8 reserved00[0x18];Vec position,rotation,scale;u8 bound[0x59c];void *animation;};
enum GSgfxPrimType {BOUND_PRIMITIVE_DEFAULT};
struct BoundContext {BoundModel *model;GSmtx *matrix,*matrices;u32 mask;};
struct BoundCallbacks {
 void (*beginSurface)(GSgfxPrimType,u16,u32,void*);
 void (*beginVertex)(void*);
 void (*attribute)(u32,void*,void*);
 void (*endVertex)(void*);
 void (*endSurface)(void*);
};
typedef char BoundModelAnimation[offsetof(BoundModel,animation)==0x5d8?1:-1];
extern "C" {
u8 GSboundHasAnimData(void*);void GSboundReset(void*);
void GSmodelForceAnimTransformUpdate(BoundModel*);
void GSmodelParse(BoundModel*,s32,void(*)(_HSD_PObj*,GSmtx*,GSmtx*,GSmtx*,void*),void*);
void GSgfxParseDisplayList(void*,void*,u32,BoundCallbacks*,void*);
void *GSmodelGetBound(BoundModel*);
void GSboundAddPoint(void*,f32,f32,f32);
}
#endif
