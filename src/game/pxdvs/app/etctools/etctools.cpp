#include <global.h>
extern "C" {
void* pokemonDataBiosGetPtr(u32);
u16 pokemonDataBiosGetVoice(void*);
s32 GSsndPlay(u32,u16,u32);
void etctoolSetPokemonNakigoe(u32 species){void* data=pokemonDataBiosGetPtr(species);if(data)GSsndPlay((u16)pokemonDataBiosGetVoice(data),0,0);}
}
