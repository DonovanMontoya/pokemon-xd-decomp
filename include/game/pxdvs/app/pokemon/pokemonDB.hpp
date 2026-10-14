#ifndef POKEMONDB_H
#define POKEMONDB_H

#include <global.h>
#include <game/pxdvs/app/pokemon/pokemon.hpp>

struct BasisStatus {
    u16 maxHp; // 0x0
    u16 phyAtk; // 0x2
    u16 phyDef; // 0x4
    u16 speAtk; // 0x6
    u16 speDef; // 0x8
    u16 nimbleness; // 0xa
};

// AKA Evolution
struct Sinka {
    u8 kind;
    // padding byte
    u16 buff;
    u16 pokemonDataId;
};

// AKA Move
struct PokemonDataWaza {
    u8 level;
    // padding byte
    u16 dataId;
};

struct PokemonDataCgData {
    u8 color;
    // padding byte
    u16 spriteId;
    u32 pokebodyId;
};

struct PokemonData {
    u8 growDataId; // 0x0
    u8 get; // 0x1
    u8 sexRatio; // 0x2
    u8 unk0[1];
    u16 giveExp; // 0x4
    u16 initFriend; // 0x6
    u16 height; // 0x8
    u16 weight; // 0xa
    u16 voice; // 0xc
    u16 cryDataId; // 0xe, index into the cry data table
    u16 shout; // 0x10
    u16 numPokemon; // 0x12
    u16 numZukan; // 0x14
    u8 unk2[2];
    const char* name; // 0x18
    u32 typeName; // 0x1c
    u32 doc; // 0x20, type unk
    u32 mitaFlag; // 0x24
    u32 tukamaetaFlag; // 0x28
    u32 pkxDataId; // 0x2c
    u8 zokuseiDataId[2]; // 0x30
    u8 tokuseiDataId[2]; // 0x32
    u8 wazaMcn[58]; // 0x34
    u8 teachWaza[12]; // 0x6e
    u16 itemDataId[2]; // 0x7a
    u16 kowaza[8]; // 0x7e
    BasisStatus basisStatus[2]; // 0x8e
    Sinka sinka[5]; // 0xa6
    PokemonDataWaza waza[20]; // 0xc4
    PokemonDataCgData cgData[2]; // 0x114
    // 292 bytes total
};

extern "C" void pokemon_SetPoolFriend(Pokemon*, u16);
extern "C" void pokemon_SetPoolExp(Pokemon*, u32);
extern "C" void pokemon_SetDarkpokemonDataId(Pokemon*, u16);
extern "C" void pokemon_SetTokuseiFlag(Pokemon* , u32);
extern "C" void pokemon_SetMaxHp(Pokemon*, u16);
extern "C" void pokemon_SetHp(Pokemon*, u16);
extern "C" void pokemon_SetPokemonWazaPpCount(Pokemon*, u16, u8);
extern "C" void pokemon_SetPokemonWazaPp(Pokemon*, u16, u8);
extern "C" void pokemon_SetPokemonWazaDataId(Pokemon*, u16, u16);
extern "C" void pokemon_SetLevel(Pokemon*, u8);
extern "C" void pokemon_SetExp(Pokemon*, u32);
extern "C" u8 pokemon_GetNowExpToLevel(Pokemon*);
extern "C" u8 pokemon_GetSeikaku(Pokemon*);
extern "C" u16 pokemon_GetMaxHp(Pokemon*);
extern "C" u16 pokemon_GetHp(Pokemon*);
extern "C" u32 pokemon_GetExp(Pokemon*);
extern "C" u32 pokemon_GetCatchTrainerRnd(Pokemon*);
extern "C" u32 pokemon_GetRnd(Pokemon*);
extern "C" u32 pokemon_GetPokemonDataId(Pokemon*);
extern "C" u32 pokemonDB_GetTokuseiDataId(u32, u16);
extern "C" u8 pokemonDB_GetGrowDataId(u32);
extern "C" {
u32 pokemonDB_GetPkxDataId(u32);
u16 pokemonDB_GetShout(u32);
u16 pokemonDB_GetVoice(u32);
u16 pokemonDB_GetWeight(u32);
u16 pokemonDB_GetInitFriend(u32);
u8 pokemonDB_GetSexRatio(u32);
u8 pokemonDB_GetGet(u32);
u16 pokemonDB_GetGiveExp(u32);
u16 pokemonDB_GetBasisNimbleness(u32);
u16 pokemonDB_GetBasisSpeDef(u32);
u16 pokemonDB_GetBasisSpeAtk(u32);
u16 pokemonDB_GetBasisPhyDef(u32);
u16 pokemonDB_GetBasisPhyAtk(u32);
u16 pokemonDB_GetBasisMaxHp(u32);
u32 pokemonDB_GetPokebodyId(u32,u16);
u16 pokemonDB_GetGetWazaDataId(u32,u16);
u8 pokemonDB_GetGetWazaLevel(u32,u16);
u8 pokemonDB_GetZokuseiDataId(u32,u16);
u16 pokemonDB_GetItemDataId(u32,u16);
void pokemonDB_SetTukamaetaFlag(u32,bool);
void pokemonDB_SetMitaFlag(u32,bool);
}
#endif
