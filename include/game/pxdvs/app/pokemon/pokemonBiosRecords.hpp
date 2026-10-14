#ifndef POKEMON_BIOS_RECORDS_H
#define POKEMON_BIOS_RECORDS_H
#include <global.h>
// Record strides and member offsets verified against GXXE01 BIOS accessors.
struct PokemonGrowDataBios { s32 exp[101]; };
struct PokemonSeikakuRateBios { u8 kake; u8 waru; };
struct PokemonSeikakuDataBios {
    u8 reliveFightout, reliveWalk, reliveCall, reliveSodateya, reliveNadenade;
    u8 phyAtkRateDataId, phyDefRateDataId, speAtkRateDataId, speDefRateDataId, nimblenessRateDataId;
    u8 reserved0a[10];
    u32 name;
    u8 reserved18[16];
};
struct PokemonTokuseiDataBios { u32 reserved; u32 name; u32 doc; };
struct PokemonFriendFilterDataBios { u8 value[3]; };
struct PokemonDpFilterDataBios { u8 value; };
#endif
