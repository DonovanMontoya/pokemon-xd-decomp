#ifndef PE_MODEL_PRIVATE_HPP
#define PE_MODEL_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>
struct ModelJObj {u8 prefix[0x14];u32 flags;u8 reserved18[0x2c];Mtx matrix;};
struct ModelCamera {u8 reserved00[8];void *camera;};
struct _peModel {u32 flags;Vec rotation,angularSpeed,scale,scaleRange;ShapeSpline *rotationSpline[3],*scaleSpline[3];union {ModelJObj *jobj;u32 primitive;} resource;f32 duration;};
struct peModelNode:peNode {
 Vec worldPosition;Quaternion worldRotation;Vec worldScale;u16 flips;s16 instance;
 Quaternion randomRotation,localRotation;Vec baseScale,angularSpeed;f32 depth;
 void Start(peEmitterNode*,_peModel*,_EmitParams*);u8 Update(peEmitterNode*,_peModel*,f32);
};
struct peModelContainer:peContainer {
 _peModel *model;
 peModelContainer(peEmitterNode*,_peModel*,u16);virtual ~peModelContainer();
 void Stop();void Render();void Update(f32);u16 Emit(u16);
};
typedef char ModelNodeSize[sizeof(peModelNode)==0x98?1:-1];
extern "C" {
double fmod(double,double);
void __assert(const char*,int,const char*);
s16 shapeCreatePrimitiveInstance(u16);void shapeFreePrimitiveInstance(u16,s16);u32 shapeGetInstancedMemorySizeAll();
void shapeUpdate(u16,s16,f32);void shapeRender(u16,s16,s32);
ModelCamera *GScameraGetActiveCamera();void GSlightSetupLights(void*);void HSD_CObjSetCurrent(void*);
void HSD_StateInvalidate(s32);void HSD_JObjSetMtxDirtySub(ModelJObj*);void HSD_JObjReqAnimAll(ModelJObj*,f32);void HSD_JObjAnimAll(ModelJObj*);void HSD_JObjDispAll(ModelJObj*,void*,u32,u32);
void InvalidateState__10GSgfxLayerFv(GSgfxLayer*);u8 GSgfxVideoGetVsyncRate();
}
#endif
