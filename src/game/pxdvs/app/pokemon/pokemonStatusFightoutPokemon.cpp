#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

extern "C" {
void fightOutPokemon_SetComboFuncId(FightOutPokemon*, u8);
u8 fightOutPokemon_GetComboFuncId(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon*);
}

void FightOutPokemon::setComboFuncId(u8 id) {
    fightOutPokemon_SetComboFuncId(this, id);
}

extern "C" u8 getComboFuncId__15FightOutPokemonFv(FightOutPokemon* pokemon) {
    return fightOutPokemon_GetComboFuncId(pokemon);
}

extern "C" FightPokemon* getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon* pokemon) {
    return fightOutPokemon_GetFightPokemonPtr(pokemon);
}
