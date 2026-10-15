#ifndef GBA_COMMAND_PRIVATE_HPP
#define GBA_COMMAND_PRIVATE_HPP
#include <global.h>
struct GbaPokemonRecord {u8 data[0x64];};
struct GbaExchangePacket {u32 status, pokemonId;GbaPokemonRecord pokemon;s8 ribbons[12];};
struct GbaWazaText {u8 text[0x780];};
typedef char GbaExchangeSize[sizeof(GbaExchangePacket)==0x78?1:-1];
struct FightOutPokemon;
#endif
