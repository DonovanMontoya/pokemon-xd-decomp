#ifndef WAZAEFFECTS_PRIVATE_HPP
#define WAZAEFFECTS_PRIVATE_HPP
#include <game/pxdvs/app/wazaSequence/wazaSequenceEntryPrivate.hpp>
struct GSgfxLayer;
enum GSgfxLayerPass { EffectPass };
struct _GSparticleBank;
struct GSmodel;
class GSeffect {
public:
    u32 field0, field4;
    GSeffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
    virtual void _render(GSgfxLayer *, GSgfxLayerPass);
    virtual void _fastRender();
    virtual ~GSeffect();
};
class boneFillEffect : public GSeffect {
public:
    u8 fields[0x20];
    boneFillEffect(_GSparticleBank *, enumNullJointName, enumNullJointName, f32);
    virtual ~boneFillEffect();
    virtual bool _start();
    virtual bool _update(f32);
    virtual void _stop();
};
class blurEffect : public GSeffect {
public:
    u8 fields[0x10];
    blurEffect(bool);
    virtual ~blurEffect();
    virtual bool _start();
    virtual void _stop();
    virtual void _render(GSgfxLayer *, GSgfxLayerPass);
};
class envMapEffect : public GSeffect {
public:
    GSmodel *model;
    u32 texture, type;
    f32 value;
    envMapEffect(u32 textureID, u32 effectType) : model(0), texture(textureID), type(effectType), value(0.0f) {}
    virtual ~envMapEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
};
class filterEffect : public GSeffect {
public:
    void *target;
    u8 original[4];
    u8 pe, combine, saved, pad17, modulation;
    u8 color[4];
    filterEffect() : target(0), modulation(0) {
        color[0] = color[1] = color[2] = color[3] = 0;
    }
    filterEffect(bool usePe, bool useCombine) : target(0), pe(usePe), combine(0), saved(0) {
        u8 mode = 2;
        if (useCombine) mode = 1;
        modulation = mode;
        color[0] = color[1] = color[2] = 127;
        color[3] = usePe ? 0 : 255;
    }
    virtual ~filterEffect();
    virtual bool _start();
    virtual void _stop();
    virtual bool _update(f32);
};
typedef char BoneFillSize[sizeof(boneFillEffect)==0x2c ? 1 : -1];
typedef char BlurSize[sizeof(blurEffect)==0x1c ? 1 : -1];
typedef char EnvMapSize[sizeof(envMapEffect)==0x1c ? 1 : -1];
typedef char FilterSize[sizeof(filterEffect)==0x20 ? 1 : -1];
#endif
