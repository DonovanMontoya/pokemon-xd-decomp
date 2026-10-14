#include <global.h>

extern "C" {
s32 heroGetStatus(s32, s32, s32);
u8 pokemonIsDarkPokemon(s32);
void pokemonSetDp(s32, f32);
void preReliveSetParameter(s32, s32, s32);

s32 dbgMenuRelive(void) {
    s32 pokemon = heroGetStatus(0, 3, 0);
    if (!pokemonIsDarkPokemon(pokemon)) {
        return 0;
    }
    pokemonSetDp(pokemon, 0.0f);
    preReliveSetParameter(0, 0, 1);
    return 0;
}
}
