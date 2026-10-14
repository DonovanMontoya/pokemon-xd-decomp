#ifndef FIGHT_POKEMON_ACTIONS_HPP
#define FIGHT_POKEMON_ACTIONS_HPP
#include <game/pxdvs/app/fight/fightPokemon.hpp>
struct FightTarget;
struct FightActionData;
struct Hero;
extern "C" {
bool fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemonInitJoutaiKeep(FightOutPokemon*);
void fightOutPokemonInitJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon*);
u32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon*);
u32 wazaDB_GetIryoku(u32);
s32 wazaDB_GetPri(u32);
u32 pokemon_GetPokemonWazaPp(Pokemon*, u16);
u8 pokemonWazaCheckValid(Pokemon*, u16);
u8 fightFloorCheckHuuinWazaFightOutPokemon(void*, FightOutPokemon*, u32);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*, u16, u8, u16*);
u8 fightOutPokemonGetOutOkWazaBanmeAry(FightOutPokemon*, s16*);
u8 fightOutPokemonCheckWaruagaki(FightOutPokemon*);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon*, u8);
u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon*, u8);
FightTarget* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u32, u8,
    FightTarget* (*)(FightOutPokemon*, u16, u16), u32, u32, s32);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightTarget*, u8);
FightTarget* fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(u32, u16);
extern FightActionData fight_action_data_waza;
FightActionBuff* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, u32, u32, u32,
    FightActionData*, u16, u32, s32, u8);
u8 fightWazaCheckValid(FightWaza*);
u32 fightWaza_GetUseWazaDataId(FightWaza*);
s32 fightWaza_GetWazaBanme(FightWaza*);
u32 fightWaza_GetTargetDataId(FightWaza*);
u32 heroGetStatus(Hero*, u32, u32);
u32 pokemon_GetNimbleness(Pokemon*);
u32 fightAbicntDoKakeWaru(u8, u32);
u32 fightOutPokemonGetNowNimbleness(FightOutPokemon*, u8, u8, u16, Hero*);
}
#endif
