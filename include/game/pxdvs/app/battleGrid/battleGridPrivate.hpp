#ifndef BATTLE_GRID_PRIVATE_HPP
#define BATTLE_GRID_PRIVATE_HPP
#include <global.h>
struct GSvec {f32 x,y,z;};
class NullSequence {
public:
    virtual ~NullSequence();virtual void Update(f32);virtual void GetPosition(GSvec*);virtual void GetRotation(GSvec*);virtual void GetScale(GSvec*);
    virtual void SetPosition(GSvec*);virtual void SetRotation(GSvec*);virtual void SetScale(GSvec*);virtual void SetVisibility(bool);
    u16 id;bool visible,failed;s32 type;GSvec position,rotation,scale;void *wazaList;s32 camera;NullSequence *next;
};
class ModelSequence:public NullSequence {
public:
    u8 pad3C[0x14];s8 modelSize;u8 pad51[4];u8 flipped;bool isPokemon;u8 pad57[0x21];ModelSequence *lookTarget,*lookSource;
};
struct BattleGridTrainer {ModelSequence *trainer,*pokemon[2];u16 count;u8 side;s8 lane;};
struct BattleGrid {BattleGridTrainer trainers[4];u16 trainerCount,pokemonCount;};
typedef char BattleGridSize[sizeof(BattleGrid)==0x44?1:-1];
typedef char BattleGridTrainerSize[sizeof(BattleGridTrainer)==16?1:-1];
typedef char ModelSequenceSize[sizeof(ModelSequence)==0x80?1:-1];
#endif
