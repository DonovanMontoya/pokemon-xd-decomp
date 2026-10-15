#ifndef FIGHT_TRAINER_AI_IREKAE_PRIVATE_HPP
#define FIGHT_TRAINER_AI_IREKAE_PRIVATE_HPP
#include <global.h>
struct ComboId {u8 unk0,unk1,data[10];};
struct FightOutSnapshot {u32 data[0x894/4];};
typedef char ComboIdSize[sizeof(ComboId)==12?1:-1];
typedef char FightOutSnapshotSize[sizeof(FightOutSnapshot)==0x894?1:-1];
extern "C" {
extern ComboId comboid[];extern u8 fight_action_data_turn[];extern u32 *zokusei_data_number;
u16 HSD_Rand();u8 dbgMenuFightGetFightTrainerAiLastValueReviseFlag();
void *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*,void*);void *fightFloorGetFightPokemonPtrToFightTrainerPtr(void*,void*);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*,void*,void**,u8,u8);u16 fightFloorGetFightTrainerFightPokemonPtrAry(void*,void*,void**,u8,u8);
void fightOutPokemonBiosCopy(void*,void*);u8 fightOutPokemonCheckFightOut(void*);void fightOutPokemonCreate(void*,void*,u8);void fightOutPokemonCreateFightAction(void*,u32,u32,u32,void*,s32);
s8 fightOutPokemonGetKaisuuJoutaiDataId(void*,u16);s8 fightOutPokemonGetNowKaisuuJoutaiDataId(void*,u16);void *fightOutPokemonGetPokemonPtr(void*);void fightOutPokemonIsFightActionAttackWazaOut(void*,u16,u8);u16 fightOutPokemonNowHpWaruValue(void*,u16);u16 fightOutPokemon_GetMotoWazaDataId(void*);
void *fightPokemonGetPokemonPtr(void*);s16 fightPokemon_GetEntryId(void*);void *fightPokemon_GetPokemonBuffPtr(void*);
s32 fightTrainerAiAddValue(s32,s32);s32 fightTrainerAiAddValueByAddsubDataId(s32,void*,u32);
u8 fightTrainerAiDB_GetLastValueRevise();u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(s32);u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(s32);u8 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(s32);
s32 fightTrainerAiDB_GetZokuseiReviseValue(s32,u8);u8 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(s32,u8);s32 fightTrainerAiGetFightFloorNowTenkouDataId(void*,u8,u8);
u16 fightTrainerAiGetFightOutPokemonBasisPhyAtk(void*,void*);u16 fightTrainerAiGetFightOutPokemonBasisSpeAtk(void*,void*);u16 fightTrainerAiGetFightOutPokemonBasisSubayasa(void*,void*);u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(void*,void*);u16 fightTrainerAiGetFightOutPokemonNowHp(void*,void*);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(void*,void*,u16*,u8,u8);u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(void*,void*,u16,s32);u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(void*,void*);u16 fightTrainerAiGetFightPokemonSubayasa(void*,void*);s32 fightTrainerAiGetFightPokemonWazaDataIdAry(void*,void*,u16*,u8,u8);s32 fightTrainerAiGetFightPokemonZokuseiAisyouValue(void*,void*,u8);u16 fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(void*,void*,u16,s32);
s32 fightTrainerAiGetValueAryMaxBanme(s32*,u16,u8);s32 fightTrainerAiGetWazaIryoku(void*,u16);u16 fightTrainerAiGetWazaZokuseiDataId(void*,u16,void*);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntHikui(void*,void*);u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(void*,void*);u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(void*,void*,u16);u8 fightTrainerAiIsFightOutPokemonJoutaiKie(void*,void*);u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(void*,void*);u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(void*,void*,u16);
u8 fightTrainerAiIsFightPokemonNokoriHpHikui(void*,void*);u8 fightTrainerAiIsFightPokemonTokuseiDataId(void*,void*,u16);u8 fightTrainerAiIsFightPokemonZokuseiDataId(void*,void*,u16);u8 fightTrainerAiIsWazaTypeId(void*,u16,u8);
s32 fightTrainerAiReviseValueByAddsubDataId(s32,s32,void*,u16);s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(void*,void*,u16,void*,u8);s32 fightTrainerAiWazaDoWazaDamageFunc(void*,void*,u16,void*,u8);u8 fightTrainerAiWazaDoWazaHitFunc(void*,void*,u16,void*);
u8 fightTrainerCheckCanIrekaeFightPokemon(void*);s32 fightTrainerDB_GetAiDataId(u16);u16 fightTrainerGetIrekaeFightPokemonAry(void*,void**);u16 fightTrainer_GetFightTrainerDataId(void*);
u16 getComboID__11DeckTrainerCFUc(void*,u8);void *getDeckTrainerObj__11DeckTrainerFUl(u32);u8 pokemon_GetComboPartner(void*,u8,u8);u16 pokemon_GetFightTrainerPokemonDataId(void*);u16 pokemon_GetHp(void*);
u8 fightTrainerAiIrekae_SelComboPartner(void*,void*,void*);s32 fightTrainerAiSelectFightActionIrekae(void*,void*,void*);s16 fightTrainerAiSelectIrekaeDasuFightPokemon(void*,void*,u8,void*);s32 fightTrainerAiGetFightPokemonIrekaeModosuValue(void*,void*,void*);u16 fightTrainerAiGetFightPokemonIrekaeDasuTokuseiAddsubDataId(void*,void*);u32 fightTrainerAiGetFightOutPokemonIrekaeJoutaiBadJoutaiAddsbuDataId(void*,void*);
}
#endif
