#ifndef PE_PARTICLE_PRIVATE_HPP
#define PE_PARTICLE_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peContainerPrivate.hpp>
struct _EmitParams {u8 data[0x48];};
struct _peParticle {u32 flags;u8 reserved04[0x40];s16 u0,v0,u1,v1;};
struct peParticleNode:peNode {
    u16 index,sortIndex;u8 texture,reserved35,live,reserved37;u8 reserved38[0xc];f32 angle,angularSpeed,depth;
    void Start(peEmitterNode*,_peParticle*,GSgfxDL*,_EmitParams*);void Render(_peParticle*,GSgfxDL*,char*);void UpdateRenderData(peEmitterNode*,_peParticle*,char*,f32);
};
struct peParticleContainer:peRenderContainer {
    peParticleNode** sorted;_peParticle* particle;f32 uv[8];
    peParticleContainer(peEmitterNode*,_peParticle*,u16);virtual ~peParticleContainer();void Start();void Stop();u16 Emit(u16);void Update(f32);void Render();void DepthSort();
};
extern "C" {extern _EmitParams* g_emitParams;}
#endif
