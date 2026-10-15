#ifndef BILLBOARD_PRIVATE_HPP
#define BILLBOARD_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
struct GSmodel;struct GScamera;struct GSbound;struct GSgfxLayer;enum GSgfxLayerPass{BillboardPass};struct _GSparticleBank;struct _GSparticleGen;
struct GSeffectBase{u32 field0,field4;};
class GSeffect:public GSeffectBase{public:GSeffect();virtual bool _start();virtual void _stop();virtual bool _update(f32);virtual void _render(GSgfxLayer*,GSgfxLayerPass);virtual void _fastRender();virtual ~GSeffect();void Stop();};
class billboardEffect:public GSeffect{public:u32 modelResource,particleResource;GSmodel*model;_GSparticleBank*bank;s32 type;u16 animation,generatorIndex;_GSparticleGen*generator;billboardEffect(u8**);virtual ~billboardEffect();virtual bool _start();virtual void _stop();virtual bool _update(f32);};
#endif
