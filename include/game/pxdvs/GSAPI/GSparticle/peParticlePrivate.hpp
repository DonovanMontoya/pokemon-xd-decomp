#ifndef PE_PARTICLE_PRIVATE_HPP
#define PE_PARTICLE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
struct _EmitParams {u8 data[0x48];};
struct ParticleSpline {u8 flags;u8 reserved01[3];f32 value,time;};
struct _peParticle {u32 flags;f32 sizeX,sizeY,rangeX,rangeY;u8 reserved14[0x10];f32 angle,angularMin,angularRange,frameDuration;ParticleSpline* angleSpline;u8 reserved38[0xc];s16 u0,v0,u1,v1;u8 reserved4c[8];void* texture;};
struct peParticleNode:peNode {
    u16 index,sortIndex;u8 texture,reserved35,live,reserved37;f32 width,height,rotation,angle,angularSpeed,depth;
    void Start(peEmitterNode*,_peParticle*,GSgfxDL*,_EmitParams*);void Render(_peParticle*,GSgfxDL*,char*);void UpdateRenderData(peEmitterNode*,_peParticle*,char*,f32);
};
struct peParticleContainer:peRenderContainer {
    peParticleNode** sorted;_peParticle* particle;f32 uv[8];
    peParticleContainer(peEmitterNode*,_peParticle*,u16);virtual ~peParticleContainer();void Start();void Stop();u16 Emit(u16);void Update(f32);void Render();void DepthSort();
};
extern "C" {extern _EmitParams* g_emitParams;}
extern "C" {f32 peSplineGetValue(ParticleSpline*,f32);}
#endif
