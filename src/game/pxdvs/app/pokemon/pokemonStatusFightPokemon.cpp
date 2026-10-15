#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

extern "C" Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);

extern "C" Pokemon* getPokemonBuffPtr__12FightPokemonFv(FightPokemon*);

extern "C" Pokemon* getPokemonBuffPtr__12FightPokemonFv(FightPokemon* pokemon) {
    return fightPokemon_GetPokemonBuffPtr(pokemon);
}
