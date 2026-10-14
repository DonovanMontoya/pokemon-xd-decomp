#ifndef FIGHT_TRAINER_ENEMY_HPP
#define FIGHT_TRAINER_ENEMY_HPP
#include <dolphin/types.h>

struct FightTrainerEnemyPokemon {
    s16 entryId;
    u8 storeWazaNum;
    u8 expectWazaNum;
    u16 storeWaza[4];
    u16 expectWaza[8];
    u8 tokuseiFlag;
    u16 storeTokusei;
    u8 nowhpLowest;
    u8 levelLowest;
    u8 defenseLowest;
    u8 badWaza;
    u8 paramHighest;
};

extern "C" {
u8 fightTrainerEnemyPokemonEraseAry(FightTrainerEnemyPokemon*, u16, s16);
u8 fightTrainerEnemyPokemonRegistAry(FightTrainerEnemyPokemon*, u16, s16);
FightTrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(FightTrainerEnemyPokemon*, u16, s16);
bool fightTrainerEnemyPokemonCheckValid(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonCreate(FightTrainerEnemyPokemon*, s16);
void fightTrainerEnemyPokemonInitAry(FightTrainerEnemyPokemon*, u16);
void fightTrainerEnemyPokemonInit(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonInitFightOutStatus(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonInitFightStatus(FightTrainerEnemyPokemon*);
}
#endif
