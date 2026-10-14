#ifndef FIGHT_POKEMON_CONDITIONS_HPP
#define FIGHT_POKEMON_CONDITIONS_HPP
#include <game/pxdvs/app/fight/fightPokemon.hpp>

// The condition system dispatches these records using joutaiDataBiosGetStatus.
extern "C" {
u16 joutaiDataBiosGetStatus(u16);
void fightOutPokemonResetSeqStatus(FightOutPokemon*, u16);
void fightPokemonSetBuffJoutaiDataId(FightPokemon*, u16, u32);
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon*, u16, u32);
void joutaiSetBuff(void*, u16, u32);
u32 fightPokemonGetBuffJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetBuff(void*, u16);
void fightPokemonSetIdBuffJoutaiDataId(FightPokemon*, u16, u16);
void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon*, u16, u16);
void joutaiSetIdBuff(void*, u16, u16);
u32 fightPokemonGetIdBuffJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetIdBuff(void*, u16);
u32 fightPokemonGetUserFightTargetIdJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetUserFightTargetId(void*, u16);
void fightPokemonSetKaisuuJoutaiDataId(FightPokemon*, u16, u8);
void fightOutPokemonSetKaisuuJoutaiDataId(FightOutPokemon*, u16, u8);
void joutaiSetKaisuuJoutaiDataId(void*, u16, u8);
void pokemonSetKaisuuJoutaiDataId(Pokemon*, u16, u8);
void fightPokemonSetNowKaisuuJoutaiDataId(FightPokemon*, u16, u8);
void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon*, u16, u8);
void joutaiSetNowKaisuuJoutaiDataId(void*, u16, u8);
void pokemonSetNowKaisuuJoutaiDataId(Pokemon*, u16, u8);
u32 fightPokemonGetNowKaisuuJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetNowKaisuuJoutaiDataId(void*, u16);
u32 pokemonGetNowKaisuuJoutaiDataId(Pokemon*, u16);
u32 fightPokemonGetKaisuuJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetKaisuuJoutaiDataId(void*, u16);
u32 pokemonGetKaisuuJoutaiDataId(Pokemon*, u16);
u32 fightPokemonGetCountAsJoutaiDataId(FightPokemon*, u16);
u32 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon*, u16);
u32 joutaiGetCountAsJoutaiDataId(void*, u16);
u32 pokemonGetCountAsJoutaiDataId(Pokemon*, u16);
void fightPokemonWriteJoutaiDataId(FightPokemon*, u16, u16);
void fightOutPokemonWriteJoutaiDataId(FightOutPokemon*, u16, u16);
void joutaiWriteJoutaiDataId(void*, u16, u16);
void pokemonWriteJoutaiDataId(Pokemon*, u16, u16);
u8 fightPokemonCheckWriteJoutaiDataId(FightPokemon*, u16);
u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon*, u16);
u8 joutaiCheckWriteJoutaiDataId(void*, u16);
u8 pokemonCheckWriteJoutaiDataId(Pokemon*, u16);
u8 fightPokemonIsJoutaiDataId(FightPokemon*, u16);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u8 joutaiIsJoutaiDataId(void*, u16);
u8 pokemonIsJoutaiDataId(Pokemon*, u16);
void fightPokemonInitJoutaiDataId(FightPokemon*, u16);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
void joutaiInitJoutaiDataId(void*, u16);
void pokemonInitJoutaiDataId(Pokemon*, u16);
void fightOutPokemonCopyJoutaiDataId(FightOutPokemon*, FightOutPokemon*, u16);
void fightPokemonCopyJoutaiDataId(FightPokemon*, FightPokemon*, u16);
void pokemonCopyJoutaiDataId(Pokemon*, Pokemon*, u16);
void joutaiCopy(void*, void*, u16);
void Sequence_ResetStatus(void*, u32);
}
#endif
