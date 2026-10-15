#ifndef BONE_FILL_PRIVATE_HPP
#define BONE_FILL_PRIVATE_HPP
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
struct _GSparticleBank;struct _GSparticleGen;struct GSmodel;
struct BoneModelCharacter {u8 pad[0x4C];s32 joints[33];};
struct BoneOwner {u8 pad0[0x52];u8 characterIndex;u8 pad53[0x41];GSmodel*model;u8 pad98[4];BoneModelCharacter*characters;};
enum enumNullJointName {NullJointDummy};
struct GSeffectBase {u32 field0,field4;};
class GSeffect:public GSeffectBase {public:GSeffect();virtual ~GSeffect();virtual bool _start();virtual bool _update(f32);virtual void _stop();void Stop();};
class boneFillEffect:public GSeffect {public:_GSparticleBank*bank;_GSparticleGen*generator;BoneOwner*owner;enumNullJointName first,second;s32 bones[2];f32 length;boneFillEffect(_GSparticleBank*,enumNullJointName,enumNullJointName,f32);virtual ~boneFillEffect();virtual bool _start();virtual bool _update(f32);virtual void _stop();};
#endif
