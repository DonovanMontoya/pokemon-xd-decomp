#ifndef FIGHT_POKEMON_ENEMY_RECOVERY_HPP
#define FIGHT_POKEMON_ENEMY_RECOVERY_HPP
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#include <game/pxdvs/app/fight/fightPokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
extern "C" {
FightOutPokemon* fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(FightOutPokemonEnemy*);
void fightOutPokemonEnemyBiosSetTargetFightOutPokemonPtr(FightOutPokemonEnemy*, FightOutPokemon*);
void fightOutPokemonEnemyBiosSetOumuWazaDataId(FightOutPokemonEnemy*, u16);
void fightOutPokemonEnemyBiosSetInitHp(FightOutPokemonEnemy*, u16);
bool fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy*);
void fightOutPokemonEnemyInit(FightOutPokemonEnemy*);
void fightOutPokemonEnemyBiosSetDamage(FightOutPokemonEnemy*, u16);
}
#endif
