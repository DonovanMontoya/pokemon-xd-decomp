#ifndef FIGHT_POKEMON_H
#define FIGHT_POKEMON_H
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

extern "C" {
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
Pokemon* fightPokemonGetPokemonPtr(FightPokemon*);
void fightOutPokemonCopyHensinStatus(FightOutPokemon*, FightOutPokemon*);
bool fightOutPokemonUseHensinBuff(FightOutPokemon*);
void fightPokemonReplace(FightPokemon*, FightPokemon*);
void fightOutPokemonCopyAllAbiCnt(FightOutPokemon*, FightOutPokemon*);
u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon*);
void fightOutPokemonCopyStatus(FightOutPokemon*, FightOutPokemon*, u16);
void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon*, u16, u8);
void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon*, u16, u16, u8);
void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon*);
}
#endif
