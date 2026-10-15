#ifndef FIGHT_SEQ_WSWAZA_PRIVATE_HPP
#define FIGHT_SEQ_WSWAZA_PRIVATE_HPP
#include <game/pxdvs/app/fight/fightSeq/fightSeqWazaseqPrivate.hpp>

struct WSFightAction { u8 data[0x38]; };

extern "C" {
extern u8 ActionSeqNo;
extern s32 ServerStatusFlag;
extern void* fight_seq_now_fight_action_ptr;
extern u8 fight_seq_server_work3_temp;
extern u8 fight_action_data_turn[];
extern u8 WAZA_KiaiPunch[];
extern u8 WAZA_PokeReshuffle[];

extern s32 fight_waza_critical_data_number;
u8 fightWaza_GetCritical(void*);
void fightWaza_SetCritical(void*, u8);
u8 fightWaza_GetDamageValue(void*);
s32 fightSeqWazaDamageCalcHikaePokemon(void*, void*, void*, u16, u16, u16);
void* fightPokemon_GetPokemonBuffPtr(void*);
u16 pokemon_GetPokemonDataId(void*);
u8 pokemon_GetTokuseiFlag(void*);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 fightFloor_GetFightKindDoCriticalAttackFlag(s32);
u8 fightWazaCriticalDataBiosGetBunbo(void*);
void* fightWazaCriticalDataBiosGetPtr(u16);
extern void (*WazaSequenceTbl[])(void);
void SCA_EndCheck(void);
void SCA_End(void);
void fightSeqTurnCheck(void);
void fightSeq_JumpWazaSeq(u8*);
void fightOutPokemonInitOneSelfTurn(void*);
void fightOutPokemonInitOneTurn(void*);
void fightSeqGetExpCheck(void);
void* fightFloor_GetIrekaePokemonPtr(void*);
void* fightFloor_GetAttackPokemonPtr(void*);
void* fightActionBiosGetFightActionDataPtr(void*);
u8 fightActionFlowFifo(void*);
u8 fightActionCreate(void*, void*, void*, u16, s32, void*);
void fightActionBiosSetBuffDataPtr(void*, void*);
void* fightOutPokemonGetNicknamePtr(void*);
void fightSeq_CallWazaSeqCustom(void*, void*, u8);
void wazaSequenceSysFreeAllWaza(void);
void fightMenuAllFightTrainerCloseStatusMenu(u8);
void fightMenuAllFightOutPokemonCloseStatusMenu(u8);
void fightMenuCloseMsg(void);
u8 fightMenuOpenMsg(u32);
u8 fightSeqFightActionCreateAndFlowFifo(void*, void*, u16, s32, void*, void*);
u8 fightSeqFightActionCreate(void*, void*, void*, u16, s32, void*, void*);
void fightSeqSpecificationActionCounterInit(void*);
void* itemDataBiosGetPtr(u16);
void* itemDataBiosGetItemEffectParam(void*);
void* itemParamGetPtr(void*);
u8 itemParamGetHPUp(void*);
u8 itemParamGetSleepFlag(void*);
u8 itemParamGetPoisonFlag(void*);
u8 itemParamGetBurnFlag(void*);
u8 itemParamGetFreezeFlag(void*);
u8 itemParamGetParalyzeFlag(void*);
u8 itemParamGetConfuseFlag(void*);
u8 itemParamGetCriticalFlag(void*);
u8 itemParamGetAttackUp(void*);
u8 itemParamGetDefenceUp(void*);
u8 itemParamGetQuickUp(void*);
u8 itemParamGetHitUp(void*);
u8 itemParamGetSpAttackUp(void*);
u8 itemParamGetGuardFlag(void*);
u8 fightOutPokemon_GetAbicntAverage(void*);
void fightOutPokemon_SetAbicntAverage(void*, u8);
u8 pokemonGetDarkPokemonCallKakuritu(void*);
void fightTrainerCallEffect(void*, u8);
void fightOutPokemonDarkPokemonKaijoEffect(void*, u8, u8, u8, u32, u8);
void* fightTrainerGetNamePtr(void*);
void fightMainAllCamera(u32, u32);
void fightMainWaitFrame(s16);
void fightMenuFightOutPokemonOpenStatusMenu(void*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32, void*, u8, u32, u32);
void fightMenuFightOutPokemonCloseStatusMenu(void*, u8, u32);
u8 fightOutPokemonIsGcHeroFightOutPokemon(void*);
void pokemonAddDpFormPokemonDpFilterId(s32, s32);
u32 fightOutPokemon_GetMotoWazaDataId(void*);
u8 fightOutPokemon_GetNamakeFlag(void*);
void fightOutPokemon_SetFightoutTurnCount(void*, u16);
s8 fightOutPokemonGetNowKaisuuJoutaiDataId(void*, u16);
s8 fightOutPokemonGetKaisuuJoutaiDataId(void*, u16);
s32 fightOutPokemonGetJoutaiMigawariHp(void*);
void* fightFloorGetValidFightSidePtr(void*, u16);
}
#endif
