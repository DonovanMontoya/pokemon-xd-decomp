#ifndef PE_SHAPE_PRIVATE_HPP
#define PE_SHAPE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
struct _EmitParams {u8 data[0x48];};
struct _peShape {u32 flags;};
struct peShapeNode:peNode {u8 reserved30[0x54];f32 depth;u8 reserved88[0x14];bool Update(peEmitterNode*,_peShape*,f32);void Start(peEmitterNode*,_peShape*,_EmitParams*);void Render(_peShape*);};
struct peShapeContainer:peContainer {
    _peShape* shape;
    peShapeContainer(peEmitterNode*,_peShape*,u16);virtual ~peShapeContainer();void Start();void Stop();void Update(f32);u16 Emit(u16);void Render();
};
extern "C" {extern _EmitParams* g_emitParams;extern void* g_currentBound;void GSboundAlwaysInView(void*,s32);}
#endif
