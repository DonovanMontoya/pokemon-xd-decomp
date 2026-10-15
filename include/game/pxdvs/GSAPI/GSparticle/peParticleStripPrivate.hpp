#ifndef PE_PARTICLE_STRIP_PRIVATE_HPP
#define PE_PARTICLE_STRIP_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSparticle/peShapePrivate.hpp>
struct StripAnimation {u32 count;void *textures[1];};
struct _peParticleStrip {u32 flags;f32 frameRate;void *colorSpline,*secondColorSpline;ShapeSpline *alphaSpline;f32 v0,v1;void *texture;Vec direction;f32 speedMin,speedRange;};
struct peParticleStripNode:peNode {u16 index,sortIndex;Vec segment;void UpdateRenderData(peEmitterNode*,_peParticleStrip*,char*,f32);};
struct peParticleStripContainer:peRenderContainer {_peParticleStrip *definition;f32 remaining;u8 frame,padding[3];
 peParticleStripContainer(peEmitterNode*,_peParticleStrip*,u16);virtual ~peParticleStripContainer();void RearrangeIndices();void Start();void Stop();void Render();void Update(f32);u16 Emit(u16);
};
typedef char StripNodeSize[sizeof(peParticleStripNode)==0x40?1:-1];
typedef char StripContainerSize[sizeof(peParticleStripContainer)==0x60?1:-1];
extern "C" {extern GSgfxVF g_vertex_format,g_ext_vertex_format;void GSgfxVFSetArray(GSgfxVF*,s32,s32,void*,u8,u32);void particleEngineSetupTevStages(u8,u8,u8);void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*,GSgfxDL*);void GSboundAddPoint(void*,f32,f32,f32);double fmod(double,double);}
#endif
