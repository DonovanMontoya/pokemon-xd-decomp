#include <dolphin/types.h>
#include <game/pxdvs/app/fight/fightTrainerAiPrivate.hpp>
#undef NULL
#define NULL 0

#ifdef __cplusplus
extern "C" {
#endif
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef struct Pokemon Pokemon; typedef struct FightPokemon FightPokemon; typedef struct FightOutPokemon FightOutPokemon; typedef struct FightSide FightSide; typedef struct FightWaza FightWaza;
typedef struct AiAbilitySearch { s32 ability; FightOutPokemon *result; s32 side; FightOutPokemon *relative; FIGHT_TRAINER *trainer; } AiAbilitySearch;
typedef FIGHT_TRAINER FightTrainer;
typedef struct AiWazaCandidate AiWazaCandidate;
typedef struct FightActionBuff FightActionBuff;
typedef struct FightTrainerEnemyPokemon FightTrainerEnemyPokemon;
typedef struct FightTrainerKindData FightTrainerKindData;
typedef struct Hero Hero;
typedef struct AiWazaCandidate {
 FightOutPokemon *attackers[2]; FightOutPokemon *defenders[2]; u16 moves[2];
 s8 slots[2]; u8 eligible[2]; u8 probability[2]; u8 combination;
 u16 damage[2][2]; u8 result[2]; u8 reserved26; u16 threat;
} AiWazaCandidate;
typedef struct AiWazaWork { u8 count; u8 reserved[3]; } AiWazaWork;
AiWazaCandidate ai_allwaza_valid_tbl[64];
AiWazaWork ai_allwaza_valid_work;
s32 fightTrainerAiAddValue(s32, s32);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER *, void *, u8);
u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER *, u16, u8);
void * fightTargetGetPtrAsNowFightType(u8, FightOutPokemon *);
s32 fightTrainerAiCmpFightOutPokemonSubayasa(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon *);
s32 fightTrainerAiValueAddsubDB_GetValue(u16);
u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaAddKoukaAvg(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaPp(FIGHT_TRAINER *, u16);
u8 wazaDB_GetAvg(u16);
s32 fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_TRAINER *, void *, FightOutPokemon *, FightOutPokemon **);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16, u16);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *, u8);
Pokemon * fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *, u16, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *);
u16 HSD_Rand(void);
u8 fightFloor_GetFightType(void *);
u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void *, FIGHT_TRAINER *, FightOutPokemon **, u8, u8);
FightActionBuff * fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon *);
u8 fightActionCheckValid(FightActionBuff*);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonNowHpPercentage(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon *, u8);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon *, u8);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER *);
u8 fightTrainerAiDB_GetWazaAvgValue(u32);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void *, FIGHT_TRAINER *, FightPokemon **, u8, u8);
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon *);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon *, u8);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 wazaCheckDarkWaza(u16);
u8 fightTrainerAiIsFightOutPokemonPhyAtkCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonPhyDefCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonSpeAtkCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonSpeDefCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNimblenessCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonAvoidCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *, s16 *, u8);
void fightFloorSortFightOutPokemonPtrArySub(void *, FightOutPokemon **, u16, u8);
u8 fightOutPokemonCheckFightOut(FightOutPokemon *);
u8 fightSeqIsAllwaysHit(u16);
u8 fightSeqIsTenkouHit(u16);
u8 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonSketchWazaDataId(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightOutPokemonWazaNowPp(FIGHT_TRAINER *, FightOutPokemon *, u32);
u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiKie(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER *, FightOutPokemon *, s32, f32);
void pokemonGetMezamerupower(Pokemon *, u16 *, u16 *);
u8 fightOutPokemonCheckValid(FightOutPokemon *);
u32 fightTrainerDB_GetAiDataId(u16);
Pokemon * fightPokemon_GetPokemonBuffPtr(FightPokemon *);
u8 pokemonIsJoutaiNormal(Pokemon *);
u8 fightTrainerAiCheckDoFightActionItem(FIGHT_TRAINER *);
u8 fightTrainerAiCheckDoFightActionIrekae(FIGHT_TRAINER *);
s32 fightTrainerAiGetPokemonDataDefense(FIGHT_TRAINER *, u16);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiIsFightOutPokemonAllAbiCntHikui(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonAllAbiCnt(FIGHT_TRAINER *, FightOutPokemon *);
FightOutPokemon * fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_TRAINER *, void *, u16, u8, u8, FightOutPokemon *);
u8 fightTrainerAiCheckHaveFightOutPokemonWazaDataId(FIGHT_TRAINER *, FightOutPokemon *, u16, s16 *, u8);
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER *, FightPokemon *, u16 *, s16 *, u8);
u8 fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(FIGHT_TRAINER *, FightOutPokemon *, u8);
u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonBasisSubayasa(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonBasisSpeDef(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonBasisSpeAtk(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTrainerAiGetFightOutPokemonBasisPhyDef(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonBasisPhyAtk(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonBasisMaxHp(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u8);
u8 fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(FIGHT_TRAINER *, FightOutPokemon *, u32);
u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER *, FightOutPokemon *, u8);
u32 fightTrainerAiGetFightOutPokemonFriend(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiGetFightPokemonPartDataId(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonBasisSubayasa(FIGHT_TRAINER *, FightPokemon *);
u32 fightTrainerAiGetFightPokemonBasisSpeDef(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonBasisSpeAtk(FIGHT_TRAINER *, FightPokemon *);
u32 fightTrainerAiGetFightPokemonBasisPhyDef(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonBasisPhyAtk(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonBasisMaxHp(FIGHT_TRAINER *, FightPokemon *);
u32 fightTrainerAiGetFightPokemonSubayasa(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonNokoriHp(FIGHT_TRAINER *, FightPokemon *, s32, f32);
u8 fightTrainerAiIsFightPokemonNokoriHpHikui(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonMaxHp(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonNowHp(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER *, FightPokemon *);
s32 fightTrainerAiGetFightPokemonZokuseiAisyouValue(FIGHT_TRAINER *, FightPokemon *, u16);
u16 fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *, FightPokemon *, u16, u16);
u16 fightTrainerAiGetFightPokemonZokuseiDataIdAry(FIGHT_TRAINER *, FightPokemon *, u16 *);
u16 fightTrainerAiGetFightPokemonZokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u8);
u8 fightTrainerAiIsFightPokemonNokoriWazaPpHikui(FIGHT_TRAINER *, FightPokemon *, u32);
u8 fightTrainerAiGetFightPokemonWazaMaxPp(FIGHT_TRAINER *, FightPokemon *, u32);
u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER *, FightPokemon *, u32);
u16 fightTrainerAiGetFightPokemonWazaDataId(FIGHT_TRAINER *, FightPokemon *, u8);
u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightPokemonSoubiItemDataId(FIGHT_TRAINER *, FightPokemon *);
u32 fightTrainerAiGetFightPokemonFriend(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiGetWazaRiskFlag(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaRangeId(FIGHT_TRAINER *, u16);
u8 fightTrainerAiIsWazaAvgTakai(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaAvg(FIGHT_TRAINER *, u16);
u8 fightTrainerAiGetWazaTypeId(FIGHT_TRAINER *, u16, u32);
s32 fightTrainerAiGetValueAryMaxBanme(s32 *, u16, u8);
s32 fightTrainerAiReviseValueByAddsubDataId(s32, u8, FIGHT_TRAINER *, u16);
s32 fightTrainerAiReviseValue(s32, u8, s32);
void fightTrainerAiSetAllyPokemon(FIGHT_TRAINER *);
void fightTrainerAiSetEnemyPokemon(FIGHT_TRAINER *);
void fightTrainerAiSelectFightAction(FIGHT_TRAINER *, s32);
static s32 _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub__FPvUsPv(FightOutPokemon *, u16, AiAbilitySearch *);
static u16 _fightTrainerAiGetFightOutPokemonTokuseiDataId__FP13FIGHT_TRAINERP15FightOutPokemon(FIGHT_TRAINER *, FightOutPokemon *);
static u16 _fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiDB_GetAbicntMaxValue(u32);
u8 fightTrainerAiDB_GetAbicntMinValue(u32);
u8 fightTrainerAiDB_GetAvoidMaxValue(u32);
u8 fightTrainerAiDB_GetAvoidMinValue(u32);
u8 fightTrainerAiDB_GetIrekaeValue(u32);
u8 fightTrainerAiDB_GetItemValue(u32);
u8 fightTrainerAiDB_GetKeyPlayerFlag(u32);
u8 fightTrainerAiDB_GetNimblenessMaxValue(u32);
u8 fightTrainerAiDB_GetNokoriHpValue(u32);
u8 fightTrainerAiDB_GetPartFlag(u32);
u8 fightTrainerAiDB_GetPhyAtkMaxValue(u32);
u8 fightTrainerAiDB_GetPhyDefMaxValue(u32);
u8 fightTrainerAiDB_GetPokemonJoutaiFlag(u32);
u8 fightTrainerAiDB_GetSpeAtkMaxValue(u32);
u8 fightTrainerAiDB_GetSpeDefMaxValue(u32);
u8 fightTrainerAiDB_GetTokuseiCheckFlag(u32);
u8 fightTrainerAiDB_GetWazaNokoriPpValue(u32);
u8 fightTrainerAiDB_GetWazaRiskFlag(u32);
u8 fightTrainerAiDB_GetZokuseiCheckFlag(u32);
u16 pokemonDB_GetBasisMaxHp(u16);
u16 pokemonDB_GetBasisNimbleness(u16);
u16 pokemonDB_GetBasisPhyAtk(u16);
u32 pokemonDB_GetBasisPhyDef(u16);
u16 pokemonDB_GetBasisSpeAtk(u16);
u32 pokemonDB_GetBasisSpeDef(u16);
u16 pokemon_GetFightTrainerPokemonDataId(Pokemon *);
u32 pokemon_GetFriend(Pokemon *);
u16 pokemon_GetHp(Pokemon *);
u16 pokemon_GetMaxHp(Pokemon *);
u32 pokemon_GetNimbleness(Pokemon *);
u32 pokemon_GetPhyAtk(Pokemon *);
u32 pokemon_GetPhyDef(Pokemon *);
u16 pokemon_GetPokemonDataId(Pokemon *);
u32 pokemon_GetSpeAtk(Pokemon *);
u32 pokemon_GetSpeDef(Pokemon *);
Pokemon * fightPokemonGetPokemonPtr(FightPokemon *);
FightPokemon * fightOutPokemon_GetFightPokemonPtr(FightOutPokemon *);
u16 pokemonGetTokuseiDataId(Pokemon *);
u8 pokemonDB_GetTokuseiDataId(u16, u8);
u8 pokemonDB_GetZokuseiDataId(u16, u8);
u8 pokemon_GetPokemonWazaPp(Pokemon *, u8);
u16 pokemon_GetPokemonWazaDataId(Pokemon *, u32);
u8 pokemonWazaGetMaxPP(Pokemon *, u8);
u8 pokemonWazaCheckValid(Pokemon *, u8);
s8 pokemonSearchWazaDataId(Pokemon *, u16);
u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon *);
u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon *);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon *);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon *);
u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon *);
u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon *);
u16 fightOutPokemon_GetUsedItemDataId(FightOutPokemon *);
u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon *);
u32 fightOutPokemonGetNowHpPercentage(FightOutPokemon *);
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon *, u16);
u8 fightPokemonIsJoutaiDataId(FightPokemon *, u16);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon *);
u16 fightOutPokemonIsJoutaiKie(FightOutPokemon *);
u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon *, u8);
u16 fightPokemonGetSoubiItemDataId(FightPokemon *);
u16 fightPokemonGetSoubiItemSoubiDataId(FightPokemon *);
u8 fightPokemon_GetEntryId(FightPokemon *);
u8 fightTrainerIsAllyFightTargetPtr(FIGHT_TRAINER *, void *, u8);
s32 fightAbicntDoKakeWaru(s32, s32);
u8 wazaDB_GetPp(u16);
u8 wazaDB_GetRangeId(u16);
u8 wazaDB_GetTypeId(u16, u8);
u8 wazaDB_GetAddFightKoukaAvg(u16);
u8 wazaDB_GetRiskFlag(u16);
u16 wazaDB_GetIryoku(u16);
u8 wazaIsWazaTypeId(u16, u8);
u8 wazaDB_GetZokuseiDataId(u16);
s32 zokuseiGetAisyouValue(u16, u16, u16);
u16 zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16, u16 *, u16);
u16 zokuseiGetWazaJoutai(u16, u16);
void fightFloorLoopValidFightOutPokemon(void *, s32 (*)(FightOutPokemon *, u16, AiAbilitySearch *), AiAbilitySearch *, u8, u8);
u8 fightFloorGetNowTenkouDataId(void *, u8);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon *, u8, u8, u8);
u16 fightTrainer_GetEnemyExpectWazaData(FIGHT_TRAINER *, u8, u8);
u16 fightTrainer_GetEnemyStoreTokuseiData(FIGHT_TRAINER *, u8);
u16 fightTrainer_GetEnemyStoreWazaData(FIGHT_TRAINER *, u8, u8);
u8 fightTrainer_GetEnemyStoreWazaNum(FIGHT_TRAINER *, u8);
u8 fightTrainer_GetEnemyTokuseiFlag(FIGHT_TRAINER *, u8);
u8 fightTrainerPokemonDB_GetKeyPlayerFlag(u16);
u8 fightTrainerPokemonDB_GetPartDataId(u16);
FightOutPokemon ** fightAi_JudgeMoveFightOutPokemon(FIGHT_TRAINER *, FightOutPokemon **, u16 *);
void fightAi_CreateAllWazaValid(FIGHT_TRAINER *, FightOutPokemon **, u8);
void fightAi_CheckDoFightActionStroke(FIGHT_TRAINER *);
void fightTrainerAiSelectFightActionWaza(FIGHT_TRAINER *, FightOutPokemon *, s32);
void fightTrainerAiSelectFightActionIrekae(FIGHT_TRAINER *, FightOutPokemon *, s32);
void fightTrainerAiSelectFightActionItem(FIGHT_TRAINER *, FightOutPokemon *, s32);
FightOutPokemon * fightTrainerGetNoActionFightOutPokemonPtr(FIGHT_TRAINER *, u8);
FightOutPokemon * fightTrainerGetValidFightOutPokemonPtr(FIGHT_TRAINER *, u8);
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon *, u8);
u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon *, u8);
void fightOutPokemonInitFightActionBuff(FightOutPokemon *);
void fightAiCombo_Act(FIGHT_TRAINER *, FightOutPokemon **, u8, s32);
void fightAiCombo_ActContinue(FIGHT_TRAINER *, FightOutPokemon *, s32);
void fightAi_FixedAct(FIGHT_TRAINER *, s32);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void *, FightOutPokemon *, u8);
u8 fightFloor_GetFightKindUseItemFlag(void *);
void * fightTypeDataBiosGetPtr(s32);
u8 fightTypeDataBiosGetFightoutPokemonNum(void *);
FIGHT_TRAINER * fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *, FightOutPokemon *);
void fightTrainer_SetEnemyBadwazaHaveFlag(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyDefense1banhikuiFlag(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyExpectWazaData(FIGHT_TRAINER *, u8, u8, u16);
void fightTrainer_SetEnemyExpectWazaNum(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyLv1banhikuiFlag(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyNowhp1banhikuiFlag(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyParam1bantakaiFlag(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyStoreTokuseiData(FIGHT_TRAINER *, u8, u16);
void fightTrainer_SetEnemyStoreWazaData(FIGHT_TRAINER *, u8, u8, u16);
void fightTrainer_SetEnemyStoreWazaNum(FIGHT_TRAINER *, u8, u8);
void fightTrainer_SetEnemyTokuseiFlag(FIGHT_TRAINER *, u8, u8);
u8 fightAi_GetEnemyWazaAndFlag(FIGHT_TRAINER *, FightPokemon *, u16 *, u8);
u8 fightAi_GetWazaHaveFlag(FIGHT_TRAINER *, FightPokemon *, u16);
void fightAi_AddStoreTokusei(FightOutPokemon *, FIGHT_TRAINER *);
void fightAi_AddStoreWaza(FightOutPokemon *, FIGHT_TRAINER *, u16);
void fightAi_DereteExpectWaza(FightOutPokemon *, FIGHT_TRAINER *, u16);
u8 fightAi_DamageKizetsuFlag(FightOutPokemon **, s32);
u8 fightAi_PokemonTokuseiMoukaFlag(FightOutPokemon *);
u16 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16, u16);
u8 fightAi_LateDefPokeThanAllyPoke(FightOutPokemon **, FightOutPokemon *);
u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightAi_WazaSuccessProbability(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon **, u16);
u8 fightFloorCheckHuuinWazaFightOutPokemon(void *, FightOutPokemon *, u16);
u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon *, u16);
u8 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon *, u16);
u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(u16);
u8 fightAi_CreateAllWazaValid_GetDefense(u16, u8);
FIGHT_TRAINER * fightFloorGetFightPokemonPtrToFightTrainerPtr(void *, FightPokemon *);
u8 fightFloorCmpfightOutPokemonNimbleness(void *, FightOutPokemon *, FightOutPokemon *, u8);
s32 fightTrainerAiWazaDoWazaDamageFightPokemonFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightPokemon *, u8);
void fightPokemon_SetAiDamage(FightPokemon *, u16, u8, s32);
s16 fightOutPokemonGetFightEntryId(FightOutPokemon *);
void fightTrainerInitEnemyPokemonFightOutStatus(FIGHT_TRAINER *, u8);
s32 fightAi_CopyAllWazaValidTable(AiWazaCandidate *, AiWazaCandidate *);
void fightAi_InitAllWazaValidSub(AiWazaCandidate *);
void fightAi_InitAllWazaValid(void);
void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER *, AiWazaCandidate *);
s32 fightAi_CreateFightActionAttckIrekae(FightOutPokemon *, s32);
s32 fightAi_CreateFightActionAttckWaza(FightOutPokemon *, FightOutPokemon *, u16, s16);
void fightOutPokemonCreateFightAction(FightOutPokemon *, u32, u32, void *, void *, s16);
void fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon *, u32, u32, void *, void *, u16, u32, s8, u32);
FightOutPokemon * fightSeqSelectDefensePokemonPtr(FightOutPokemon *, u16, u8, void *, u8, u8, s16);
s32 fightAi_HitCheckWazaAboutJoutaiAndType(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *, u16);
FightOutPokemon * fightAi_SelectDefPoke(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon **, u16, u16, s8);
s16 fightAi_ThreatEnemyValue(FIGHT_TRAINER *, FightOutPokemon *, FightOutPokemon *, s16, u16, s8, s8);
u8 fightAi_GetWazaCombValue(FightOutPokemon **, u16 *, u8 *);
void fightTrainerAiWazaSelectDefensePokemon();
extern u8 fight_action_data_turn[64];
extern u8 fight_action_data_waza[16];
extern u16 expect_waza_data[150][9];
u32 fightFloorGetStatus(void *, void *, u32, u32);
u16 fightOutPokemonMaxHpWaruValue(FightOutPokemon *, u8);
u16 fightOutPokemonNowHpWaruValue(FightOutPokemon *, u8);
FIGHT_TRAINER *fightFloorGetFightPokemonPtrToFightTrainerPtr(void *, FightPokemon *);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon *);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon *, u8);
extern u16 expect_tokusei_data_0[8];
extern u16 expect_tokusei_data_2[68];
u8 figthPokemonGetLevel(FightPokemon *);
u16 figthPokemonGetPokemonDataId(FightPokemon *);

u8 fightTrainerAiCheckDoFightActionItem(FIGHT_TRAINER *arg0) {
    u8 temp_r31;

    temp_r31 = fightTrainerAiDB_GetItemValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0)));
    return (HSD_Rand() % 100) < (s32) temp_r31;
}

u8 fightTrainerAiCheckDoFightActionIrekae(FIGHT_TRAINER *arg0) {
    u8 temp_r31;

    temp_r31 = fightTrainerAiDB_GetIrekaeValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0)));
    return (HSD_Rand() % 100) < (s32) temp_r31;
}

s32 fightTrainerAiGetPokemonDataDefense(FIGHT_TRAINER *arg0, u16 arg1) {
    u32 temp_r31;

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = pokemonDB_GetBasisPhyDef(arg1);
    return temp_r31 + pokemonDB_GetBasisSpeDef(arg1);
}

u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntAvoid(arg1));
    return (u8) ((s32) temp_r30 <= (s32) fightTrainerAiDB_GetAvoidMinValue(temp_r31));
}

u8 fightTrainerAiIsFightOutPokemonAvoidCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntAvoid(arg1));
    return (u8) ((s32) fightTrainerAiDB_GetAvoidMaxValue(temp_r31) <= (s32) temp_r30);
}

u8 fightTrainerAiIsFightOutPokemonNimblenessCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntNimbleness(arg1));
    return (u8) ((s32) fightTrainerAiDB_GetNimblenessMaxValue(temp_r31) <= (s32) temp_r30);
}

u8 fightTrainerAiIsFightOutPokemonSpeDefCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntSpeDef(arg1));
    return (u8) ((s32) fightTrainerAiDB_GetSpeDefMaxValue(temp_r31) <= (s32) temp_r30);
}

u8 fightTrainerAiIsFightOutPokemonSpeAtkCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntSpeAtk(arg1));
    return (u8) ((s32) fightTrainerAiDB_GetSpeAtkMaxValue(temp_r31) <= (s32) temp_r30);
}

u8 fightTrainerAiIsFightOutPokemonPhyDefCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntPhyDef(arg1));
    return (u8) ((s32) fightTrainerAiDB_GetPhyDefMaxValue(temp_r31) <= (s32) temp_r30);
}

u8 fightTrainerAiIsFightOutPokemonPhyAtkCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u32 temp_r31;
    s32 temp_r30;

    temp_r31 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntPhyAtk(arg1));
    s32 r = (s32) fightTrainerAiDB_GetPhyAtkMaxValue(temp_r31) <= (s32) temp_r30;
    return (u8) r;
}

u16 fightTrainerAiIsFightOutPokemonAllAbiCntHikui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u16 temp_r31;
    u32 temp_r30;

    temp_r30 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = fightTrainerAiGetFightOutPokemonAllAbiCnt(arg0, arg1);
    return (u16) (u8) ((s32) temp_r31 <= (s32) fightTrainerAiDB_GetAbicntMinValue(temp_r30));
}

u16 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u16 temp_r31;
    u32 temp_r30;

    temp_r30 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = fightTrainerAiGetFightOutPokemonAllAbiCnt(arg0, arg1);
    return (u16) (u8) ((s32) fightTrainerAiDB_GetAbicntMaxValue(temp_r30) <= (s32) temp_r31);
}

u16 fightTrainerAiGetFightOutPokemonAllAbiCnt(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemonGetAllAbiCnt(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    u8 var_r31;

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    var_r31 = fightOutPokemon_GetAbicntAvoid(arg1);
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x19U) == 1) && (var_r31 > 6U)) {
        var_r31 = 6;
    }
    return var_r31;
}

u8 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntAverage(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntNimbleness(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntSpeDef(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntSpeAtk(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntPhyDef(arg1);
}

u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetAbicntPhyAtk(arg1);
}

u8 fightTrainerAiGetFightFloorNowTenkouDataId(FIGHT_TRAINER *arg0, void *arg1, u8 arg2) {
    u8 temp_r31;

    temp_r31 = fightFloorGetNowTenkouDataId(arg1, 0U);
    if (arg2 == 1) {
        if (fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(arg0, arg1, 0xDU, 0U, 0U, NULL) != NULL) {
            return 0U;
        }
        if (fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(arg0, arg1, 0x4DU, 0U, 0U, NULL) != NULL) {
            return 0U;
        }
        goto block_5;
    }
block_5:
    return temp_r31;
}

s32 fightTrainerAiCheckFightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_TRAINER *arg0, void *arg1, FightOutPokemon *arg2, FightOutPokemon **arg3) {
    FightOutPokemon *temp_r31;
    FightOutPokemon *temp_r30;
    FightOutPokemon *temp_r29;
    u8 var_r28;
    u8 var_r27;

    var_r28 = 0;
    var_r27 = 0;
    if (fightOutPokemonCheckValid(arg2) == 0) {
        return 0;
    }
    temp_r29 = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(arg0, arg1, 0x17U, 0U, 2U, arg2);
    temp_r30 = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(arg0, arg1, 0x47U, 0U, 2U, arg2);
    temp_r31 = fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(arg0, arg1, 0x2AU, 0U, 0U, arg2);
    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg2, 2U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg2, 0x1AU) == 1)) {
        var_r28 = 1;
    }
    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg2, 8U) == 1) {
        var_r27 = 1;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x16U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0xEU) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x25U) == 1)) {
        return 1;
    }
    if (temp_r29 != NULL) {
        if (arg3 != NULL) {
            *arg3 = temp_r29;
        }
        return 2;
    }
    if ((temp_r30 != NULL) && (var_r28 == 0)) {
        if (arg3 != NULL) {
            *arg3 = temp_r30;
        }
        return 2;
    }
    if ((temp_r31 != NULL) && (var_r27 == 1)) {
        if (arg3 != NULL) {
            *arg3 = temp_r31;
        }
        return 2;
    }
    return 0;
}

FightOutPokemon *fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_TRAINER *arg0, void *arg1, u16 arg2, u8 arg3, u8 arg4, FightOutPokemon *arg5) {
    AiAbilitySearch search;
    search.trainer = arg0;
    search.ability = arg2;
    search.result = 0;
    search.side = arg4;
    search.relative = arg5;
    fightFloorLoopValidFightOutPokemon(arg1, _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub__FPvUsPv, &search, arg3, arg4);
    return search.result;
}

static s32 _fightTrainerAiGetFightFloorFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub__FPvUsPv(FightOutPokemon *arg0, u16 arg1, AiAbilitySearch *arg2) {
    void *temp_r3;
    FightOutPokemon *temp_r30;
    void *var_r28;
    s32 temp_r0;
    s32 temp_r0_2;
    FIGHT_TRAINER *temp_r29;

    temp_r30 = arg2->relative;
    temp_r29 = arg2->trainer;
    if (fightOutPokemonCheckFightOut(arg0) == 0) {
        return 1;
    }
    if (temp_r30 == NULL) {
        var_r28 = NULL;
    } else {
        temp_r0 = arg2->side;
        if (temp_r0 == 1) {
            var_r28 = fightTargetGetPtrAsNowFightType(2U, temp_r30);
        } else if (temp_r0 == 2) {
            var_r28 = fightTargetGetPtrAsNowFightType(3U, temp_r30);
        } else {
            var_r28 = NULL;
        }
    }
    temp_r3 = fightTargetGetPtrAsNowFightType(2U, arg0);
    temp_r0_2 = arg2->side;
    if (((temp_r0_2 == 1) || (temp_r0_2 == 2)) && (var_r28 == NULL)) {
        return 1;
    }
    switch (temp_r0_2) {                            /* irregular */
    case 0:
        if ((temp_r30 != NULL) && (temp_r30 == arg0)) {
            return 1;
        }
block_22:
        if (fightTrainerAiIsFightOutPokemonTokuseiDataId(temp_r29, arg0, (u16) arg2->ability) == 1) {
            arg2->result = arg0;
            return 0;
        }
        return 1;
    case 1:
    case 2:
        if (var_r28 != temp_r3) {
            return 1;
        }
        goto block_22;
    default:
        return 1;
    }
}

u16 fightTrainerAiGetFightOutPokemonSketchWazaDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetSketchWazaDataId(arg1);
}

u16 fightTrainerAiGetFightOutPokemonLastSelectWazaDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetLastSelectWazaDataId(arg1);
}

u16 fightTrainerAiGetFightOutPokemonLastUseWazaDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetLastUseWazaDataId(arg1);
}

u8 fightTrainerAiCheckHaveFightOutPokemonWazaDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, s16 *arg3, u8 arg4) {
    u16 sp18[8];
    s16 sp8[8];
    u16 var_r7;
    u16 temp_r0;

    temp_r0 = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, arg1, sp18, sp8, arg4);
    for (var_r7 = 0; var_r7 < temp_r0; var_r7++) {
        if (arg2 == sp18[var_r7]) {
            if (arg3 != NULL) {
                *arg3 = sp8[var_r7];
            }
            return 1U;
        }
    }
    return 0U;
}

u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 *arg2, s16 *arg3, u8 arg4) {
    u16 var_r5;
    u16 var_r5_2;
    u16 temp_r3;
    u16 var_r31;
    u8 temp_r30;
    u16 temp_r3_2;
    u16 var_r24;
    u16 var_r23;
    s32 temp_r23;

    temp_r23 = fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(arg1));
    if (arg1 == NULL) {
        return 0U;
    }
    if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r23) == 0) {
        var_r31 = 0;
        var_r5 = 0;
loop_9:
        while (var_r5 < 8U) {
            if (arg2 != NULL) {
                *((u16 *)((u8 *)arg2 + ((var_r5 * 2) & 0x1FFFE))) = 0;
            }
            if (arg3 != NULL) {
                *((s16 *)((u8 *)arg3 + ((var_r5 * 2) & 0x1FFFE))) = -1;
            }
            var_r5 += 1;
        }
        var_r23 = 0;
loop_22:
        while (var_r23 < 4U) {
            temp_r3 = fightTrainer_GetEnemyStoreWazaData(arg0, temp_r30, var_r23);
            if ((temp_r3 != 0) && (temp_r3 != 0x176) && (temp_r3 != 0x163) && ((arg4 != 1) || (fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(arg0, arg1, var_r23) != 0))) {
                if (arg2 != NULL) {
                    *((u16 *)((u8 *)arg2 + ((var_r31 * 2) & 0x1FFFE))) = temp_r3;
                }
                if (arg3 != NULL) {
                    *((s16 *)((u8 *)arg3 + ((var_r31 * 2) & 0x1FFFE))) = var_r23;
                }
                var_r31 += 1;
            }
            var_r23 += 1;
        }
    } else {
        var_r5_2 = 0;
        var_r31 = 0;
loop_30:
        while (var_r5_2 < 4U) {
            if (arg2 != NULL) {
                *((u16 *)((u8 *)arg2 + ((var_r5_2 * 2) & 0x1FFFE))) = 0;
            }
            if (arg3 != NULL) {
                *((s16 *)((u8 *)arg3 + ((var_r5_2 * 2) & 0x1FFFE))) = -1;
            }
            var_r5_2 += 1;
        }
        var_r24 = 0;
loop_43:
        while (var_r24 < 4U) {
            temp_r3_2 = fightTrainerAiGetFightOutPokemonWazaDataId(arg0, arg1, var_r24);
            if ((temp_r3_2 != 0) && (temp_r3_2 != 0x176) && (temp_r3_2 != 0x163) && ((arg4 != 1) || (fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(arg0, arg1, var_r24) != 0))) {
                if (arg2 != NULL) {
                    *((u16 *)((u8 *)arg2 + ((var_r31 * 2) & 0x1FFFE))) = temp_r3_2;
                }
                if (arg3 != NULL) {
                    *((s16 *)((u8 *)arg3 + ((var_r31 * 2) & 0x1FFFE))) = var_r24;
                }
                var_r31 += 1;
            }
            var_r24 += 1;
        }
    }
    return var_r31;
}

u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 *arg2, s16 *arg3, u8 arg4) {
    u16 var_r5;
    u16 var_r5_2;
    u16 temp_r3;
    u16 var_r31;
    u8 temp_r30;
    u16 temp_r3_2;
    u16 var_r24;
    u16 var_r23;
    s32 temp_r23;

    temp_r23 = fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = fightPokemon_GetEntryId(arg1);
    if (arg1 == NULL) {
        return 0U;
    }
    if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r23) == 0) {
        var_r31 = 0;
        var_r5 = 0;
loop_9:
        while (var_r5 < 8U) {
            if (arg2 != NULL) {
                *((u16 *)((u8 *)arg2 + ((var_r5 * 2) & 0x1FFFE))) = 0;
            }
            if (arg3 != NULL) {
                *((s16 *)((u8 *)arg3 + ((var_r5 * 2) & 0x1FFFE))) = -1;
            }
            var_r5 += 1;
        }
        var_r23 = 0;
loop_22:
        while (var_r23 < 8U) {
            temp_r3 = fightTrainer_GetEnemyExpectWazaData(arg0, temp_r30, var_r23);
            if ((temp_r3 != 0) && (temp_r3 != 0x176) && (temp_r3 != 0x163) && ((arg4 != 1) || (fightTrainerAiGetFightPokemonWazaNowPp(arg0, arg1, (u8) var_r23) != 0))) {
                if (arg2 != NULL) {
                    *((u16 *)((u8 *)arg2 + ((var_r31 * 2) & 0x1FFFE))) = temp_r3;
                }
                if (arg3 != NULL) {
                    *((s16 *)((u8 *)arg3 + ((var_r31 * 2) & 0x1FFFE))) = var_r23;
                }
                var_r31 += 1;
            }
            var_r23 += 1;
        }
    } else {
        var_r5_2 = 0;
        var_r31 = 0;
loop_30:
        while (var_r5_2 < 4U) {
            if (arg2 != NULL) {
                *((u16 *)((u8 *)arg2 + ((var_r5_2 * 2) & 0x1FFFE))) = 0;
            }
            if (arg3 != NULL) {
                *((s16 *)((u8 *)arg3 + ((var_r5_2 * 2) & 0x1FFFE))) = -1;
            }
            var_r5_2 += 1;
        }
        var_r24 = 0;
loop_43:
        while (var_r24 < 4U) {
            temp_r3_2 = fightTrainerAiGetFightPokemonWazaDataId(arg0, arg1, var_r24);
            if ((temp_r3_2 != 0) && (temp_r3_2 != 0x176) && (temp_r3_2 != 0x163) && ((arg4 != 1) || (fightTrainerAiGetFightPokemonWazaNowPp(arg0, arg1, (u8) var_r24) != 0))) {
                if (arg2 != NULL) {
                    *((u16 *)((u8 *)arg2 + ((var_r31 * 2) & 0x1FFFE))) = temp_r3_2;
                }
                if (arg3 != NULL) {
                    *((s16 *)((u8 *)arg3 + ((var_r31 * 2) & 0x1FFFE))) = var_r24;
                }
                var_r31 += 1;
            }
            var_r24 += 1;
        }
    }
    return var_r31;
}

u8 fightTrainerAiCheckFightOutPokemonCanOutOkWazaBanme(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u8 arg2) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemonCheckCanOutOkWazaBanme(arg1, arg2, 0U, 0U) == 0;
}

u16 fightTrainerAiGetFightOutPokemonUsedItemDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemon_GetUsedItemDataId(arg1);
}

u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return fightOutPokemonIsJoutaiDataId(arg1, arg2);
    }
    return 0U;
}

u8 fightTrainerAiGetFightOutPokemonPartDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonPartDataId(arg0, temp_r4);
}

s32 fightTrainerAiCmpFightOutPokemonSubayasa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon *arg2) {
    s32 temp_r31;
    s32 temp_r30;
    u32 temp_r29;
    s32 temp_r28;
    u32 temp_r28_2;

    temp_r28_2 = pokemon_GetNimbleness(fightOutPokemonGetPokemonPtr(arg1));
    temp_r29 = pokemon_GetNimbleness(fightOutPokemonGetPokemonPtr(arg2));
    temp_r30 = (u8) (fightOutPokemon_GetAbicntNimbleness(arg1));
    temp_r31 = (u8) (fightOutPokemon_GetAbicntNimbleness(arg2));
    temp_r28 = (u16) (fightAbicntDoKakeWaru((s32) temp_r30, (u16) temp_r28_2));
    return temp_r28 - fightAbicntDoKakeWaru((s32) temp_r31, (u16) temp_r29);
}

u16 fightTrainerAiGetFightOutPokemonBasisSubayasa(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisSubayasa(arg0, temp_r4);
}

u32 fightTrainerAiGetFightOutPokemonBasisSpeDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisSpeDef(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonBasisSpeAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisSpeAtk(arg0, temp_r4);
}

u32 fightTrainerAiGetFightOutPokemonBasisPhyDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisPhyDef(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonBasisPhyAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisPhyAtk(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonBasisMaxHp(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonBasisMaxHp(arg0, temp_r4);
}

u8 fightTrainerAiIsFightOutPokemonJoutaiKaragenki(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return fightOutPokemonIsJoutaiKaragenki(arg1);
    }
    return 0U;
}

u8 fightTrainerAiIsFightOutPokemonJoutaiKie(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return fightOutPokemonIsJoutaiKie(arg1) != 0;
    }
    return 0U;
}

u8 fightTrainerAiIsFightOutPokemonJoutaiNormal(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiIsFightPokemonJoutaiNormal(arg0, temp_r4);
}

u8 fightTrainerAiIsFightOutPokemonNokoriHp(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, s32 arg2, f32 farg0) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiIsFightPokemonNokoriHp(arg0, temp_r4, arg2, farg0);
}

u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiIsFightPokemonNokoriHpHikui(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonMaxHp(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonMaxHp(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonNowHp(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonNowHp(arg0, temp_r4);
}

u8 fightTrainerAiGetFightOutPokemonLevel(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonLevel(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonPokemonDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonPokemonDataId(arg0, temp_r4);
}

u8 fightTrainerAiGetFightOutPokemonKeyPlayerFlag(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonKeyPlayerFlag(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3) {
    u16 sp8[2];
    u16 var_r5;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 var_r27;

    if (arg2 == 9) {
        return 0x3FU;
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x1AU) == 1) && (arg2 == 4)) {
        return 0x43U;
    }
    temp_r3 = fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(arg0, arg1, sp8);
    if (temp_r3 == 0) {
        return 0x3FU;
    }
    var_r27 = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(arg2, sp8, temp_r3);
    if (((arg2 == 0) || (arg2 == 1)) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x19U) == 1)) {
        var_r5 = 0;
loop_15:
        while (var_r5 < temp_r3) {
            temp_r3_2 = *(u16 *)((u8 *)sp8 + ((var_r5 * 2) & 0x1FFFE));
            if ((temp_r3_2 != 9) && (temp_r3_2 == 7)) {
                var_r27 = 0x3F;
            }
            var_r5 += 1;
        }
    }
    if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, 0x19U) == 1) && (var_r27 != 0x41) && ((s16) arg3 > 0)) {
        return 0x43U;
    }
    return var_r27;
}

u16 fightTrainerAiGetFightOutPokemonZokuseiDataIdAry(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 *arg2) {
    u16 temp_r3;
    u16 var_r31;
    u8 var_r30;
    s32 temp_r0;

    var_r31 = 0;
    var_r30 = 0;
loop_4:
    while (var_r30 < 2U) {
        temp_r3 = fightTrainerAiGetFightOutPokemonZokuseiDataId(arg0, arg1, var_r30);
        if (temp_r3 != 9) {
            temp_r0 = (var_r31 * 2) & 0x1FFFE;
            var_r31 += 1;
            *(u16 *)((u8 *)arg2 + temp_r0) = temp_r3;
        }
        var_r30 += 1;
    }
    return var_r31;
}

u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if ((arg2 == fightTrainerAiGetFightOutPokemonZokuseiDataId(arg0, arg1, 0U)) || (arg2 == fightTrainerAiGetFightOutPokemonZokuseiDataId(arg0, arg1, 1U))) {
        return 1U;
    }
    return 0U;
}

u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if (arg2 == 0) {
        return 0U;
    }
    return (u8) (arg2 == _fightTrainerAiGetFightOutPokemonTokuseiDataId__FP13FIGHT_TRAINERP15FightOutPokemon(arg0, arg1));
}

static u16 _fightTrainerAiGetFightOutPokemonTokuseiDataId__FP13FIGHT_TRAINERP15FightOutPokemon(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    s32 temp_r29;
    u16 var_r28;
    u8 temp_r28;
    s32 temp_r27;
    s32 temp_r26;
    u8 var_r29;
    s32 temp_r3;
    u32 temp_r30;
    Pokemon *temp_r3_2;

    temp_r29 = (u8) (fightFloor_GetFightType(NULL));
    temp_r30 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r28 = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(arg1));
    temp_r3_2 = fightOutPokemonGetPokemonPtr(arg1);
    temp_r27 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r3_2), 0U));
    temp_r26 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r3_2), 1U));
    if (fightTrainerAiDB_GetTokuseiCheckFlag(temp_r30) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r29) == 0) {
            temp_r3 = (u16) (fightTrainer_GetEnemyStoreTokuseiData(arg0, temp_r28));
            if (temp_r3 != 0) {
                return temp_r3;
            }
            var_r28 = 0;
            for (var_r29 = 0; var_r29 < 0x44U; var_r29++) {
                if (expect_tokusei_data_2[var_r29] == pokemon_GetPokemonDataId(temp_r3_2)) {
                    var_r28 = temp_r26;
                    break;
                }
            }
            if (var_r28 == 0) {
                var_r28 = temp_r27;
            }
            for (var_r29 = 0; var_r29 < 8U; var_r29++) {
                if (expect_tokusei_data_0[var_r29] == pokemon_GetPokemonDataId(temp_r3_2)) {
                    var_r28 = 0;
                    break;
                }
            }
            return var_r28;
        }
        return fightOutPokemonGetTokuseiDataId(arg1);
    }
    return 0U;
}

u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u8 arg2) {
    s32 temp_r31;

    temp_r31 = (u8) (fightFloor_GetFightType(NULL));
    if (fightTrainerAiDB_GetZokuseiCheckFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r31) == 0) {
            return fightOutPokemonGetZokuseiDataId(arg1, arg2);
        }
        return fightOutPokemonGetZokuseiDataId(arg1, arg2);
    }
    return 9U;
}

u8 fightTrainerAiIsFightOutPokemonNokoriWazaPpHikui(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u32 arg2) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiIsFightPokemonNokoriWazaPpHikui(arg0, temp_r4, arg2);
}

u8 fightTrainerAiGetFightOutPokemonWazaNowPp(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u32 arg2) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonWazaNowPp(arg0, temp_r4, arg2);
}

u16 fightTrainerAiGetFightOutPokemonWazaDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u8 arg2) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonWazaDataId(arg0, temp_r4, arg2);
}

u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(arg0, temp_r4);
}

u16 fightTrainerAiGetFightOutPokemonSoubiItemDataId(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonSoubiItemDataId(arg0, temp_r4);
}

u32 fightTrainerAiGetFightOutPokemonFriend(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg1);
    return fightTrainerAiGetFightPokemonFriend(arg0, temp_r4);
}

u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return fightPokemonIsJoutaiDataId(arg1, arg2);
    }
    return 0U;
}

u8 fightTrainerAiGetFightPokemonPartDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    u16 temp_r31;
    u32 temp_r31_2;

    fightFloor_GetFightType(NULL);
    temp_r31_2 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(arg1));
    if (fightTrainerAiDB_GetPartFlag(temp_r31_2) == 1) {
        return fightTrainerPokemonDB_GetPartDataId(temp_r31);
    }
    return 1U;
}

u8 fightTrainerAiGetFightPokemonKeyPlayerFlag(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    u16 temp_r31;
    u32 temp_r31_2;

    fightFloor_GetFightType(NULL);
    temp_r31_2 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = pokemon_GetFightTrainerPokemonDataId(fightPokemonGetPokemonPtr(arg1));
    if (fightTrainerAiDB_GetKeyPlayerFlag(temp_r31_2) == 1) {
        return fightTrainerPokemonDB_GetKeyPlayerFlag(temp_r31);
    }
    return 0U;
}

u16 fightTrainerAiGetFightPokemonBasisSubayasa(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisNimbleness(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u32 fightTrainerAiGetFightPokemonBasisSpeDef(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisSpeDef(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u16 fightTrainerAiGetFightPokemonBasisSpeAtk(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisSpeAtk(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u32 fightTrainerAiGetFightPokemonBasisPhyDef(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisPhyDef(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u16 fightTrainerAiGetFightPokemonBasisPhyAtk(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisPhyAtk(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u16 fightTrainerAiGetFightPokemonBasisMaxHp(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemonDB_GetBasisMaxHp(pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
}

u32 fightTrainerAiGetFightPokemonSubayasa(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetNimbleness(fightPokemonGetPokemonPtr(arg1));
}

u32 fightTrainerAiGetFightOutPokemonSpeDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetSpeDef(fightOutPokemonGetPokemonPtr(arg1));
}

u32 fightTrainerAiGetFightOutPokemonSpeAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetSpeAtk(fightOutPokemonGetPokemonPtr(arg1));
}

u32 fightTrainerAiGetFightOutPokemonPhyDef(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetPhyDef(fightOutPokemonGetPokemonPtr(arg1));
}

u32 fightTrainerAiGetFightOutPokemonPhyAtk(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetPhyAtk(fightOutPokemonGetPokemonPtr(arg1));
}

u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    if (fightTrainerAiDB_GetPokemonJoutaiFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return pokemonIsJoutaiNormal(fightPokemonGetPokemonPtr(arg1));
    }
    return 1U;
}

u32 fightTrainerAiGetFightOutPokemonNowHpPercentage(FIGHT_TRAINER *arg0, FightOutPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightOutPokemonGetNowHpPercentage(arg1);
}

u8 fightTrainerAiIsFightPokemonNokoriHp(FIGHT_TRAINER *arg0, FightPokemon *arg1, s32 arg2, f32 farg0) {
    u16 temp_r3;
    u16 temp_r31;
    s32 temp_r3_2;
    f32 var_f31;

    var_f31 = farg0;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = fightTrainerAiGetFightPokemonNowHp(arg0, arg1);
    temp_r3 = fightTrainerAiGetFightPokemonMaxHp(arg0, arg1);
    if (var_f31 == 0.0f) {
        var_f31 = 1.0f;
    }
    temp_r3_2 = (s32) ((f32) temp_r3 * var_f31);
    if ((s8) arg2 == 0) {
        if ((s32) temp_r31 == temp_r3_2) {
            return 1U;
        }
        goto block_11;
    }
    if ((s8) arg2 > 0) {
        if ((s32) temp_r31 >= temp_r3_2) {
            return 1U;
        }
        goto block_11;
    }
    if (((s8) arg2 < 0) && ((s32) temp_r31 <= temp_r3_2)) {
        return 1U;
    }
block_11:
    return 0U;
}

u8 fightTrainerAiIsFightPokemonNokoriHpHikui(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    s32 temp_r31;
    s32 temp_r30;
    u32 temp_r29;

    temp_r29 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u16) (fightTrainerAiGetFightPokemonNowHp(arg0, arg1));
    temp_r31 = (u16) (fightTrainerAiGetFightPokemonMaxHp(arg0, arg1));
    return (u8) (((s32) (temp_r30 * 0x64) / (s32) temp_r31) <= (s32) fightTrainerAiDB_GetNokoriHpValue(temp_r29));
}

u16 fightTrainerAiGetFightPokemonMaxHp(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetMaxHp(fightPokemonGetPokemonPtr(arg1));
}

u16 fightTrainerAiGetFightPokemonNowHp(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetHp(fightPokemonGetPokemonPtr(arg1));
}

u8 fightTrainerAiGetFightPokemonLevel(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return figthPokemonGetLevel(arg1);
}

u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return figthPokemonGetPokemonDataId(arg1);
}

s32 fightTrainerAiGetFightPokemonZokuseiAisyouValue(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2) {
    u16 temp_r3;
    u8 var_r31;
    s32 var_r30;
    u16 var_r29;

    var_r29 = 9;
    var_r30 = 0;
    for (var_r31 = 0; var_r31 < 2U; var_r31++) {
        temp_r3 = fightTrainerAiGetFightPokemonZokuseiDataId(arg0, arg1, var_r31);
        if (temp_r3 != 9) {
            if (var_r29 != temp_r3) {
                var_r29 = temp_r3;
                var_r30 += zokuseiGetAisyouValue(temp_r3, 0U, arg2);
            } else {
                break;
            }
        }
    }
    return var_r30;
}

u16 fightTrainerAiGetFightPokemonZokuseiDataIdWazaJoutaiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2, u16 arg3) {
    u16 sp8[2];
    u16 temp_r3;
    u16 temp_r31;

    if (arg2 == 9) {
        return 0x3FU;
    }
    if ((fightTrainerAiIsFightPokemonTokuseiDataId(arg0, arg1, 0x1AU) == 1) && (arg2 == 4)) {
        return 0x43U;
    }
    temp_r3 = fightTrainerAiGetFightPokemonZokuseiDataIdAry(arg0, arg1, sp8);
    if (temp_r3 == 0) {
        return 0x3FU;
    }
    temp_r31 = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(arg2, sp8, temp_r3);
    if ((fightTrainerAiIsFightPokemonTokuseiDataId(arg0, arg1, 0x19U) == 1) && (temp_r31 != 0x41) && ((s16) arg3 > 0)) {
        return 0x43U;
    }
    return temp_r31;
}

u16 fightTrainerAiGetFightPokemonZokuseiDataIdAry(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 *arg2) {
    u16 temp_r3;
    u16 var_r31;
    u8 var_r30;
    s32 temp_r0;

    var_r31 = 0;
    var_r30 = 0;
loop_4:
    while (var_r30 < 2U) {
        temp_r3 = fightTrainerAiGetFightPokemonZokuseiDataId(arg0, arg1, var_r30);
        if (temp_r3 != 9) {
            temp_r0 = (var_r31 * 2) & 0x1FFFE;
            var_r31 += 1;
            *(u16 *)((u8 *)arg2 + temp_r0) = temp_r3;
        }
        var_r30 += 1;
    }
    return var_r31;
}

u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if ((arg2 == fightTrainerAiGetFightPokemonZokuseiDataId(arg0, arg1, 0U)) || (arg2 == fightTrainerAiGetFightPokemonZokuseiDataId(arg0, arg1, 1U))) {
        return 1U;
    }
    return 0U;
}

u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if (arg2 == 0) {
        return 0U;
    }
    return (u8) (arg2 == _fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(arg0, arg1));
}

static u16 _fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    u8 temp_r31;
    u32 temp_r31_2;
    Pokemon *temp_r30;

    fightFloor_GetFightType(NULL);
    temp_r31_2 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = fightPokemonGetPokemonPtr(arg1);
    temp_r31 = fightPokemon_GetEntryId(arg1);
    if (fightTrainerAiDB_GetTokuseiCheckFlag(temp_r31_2) == 1) {
        if (fightFloorGetFightPokemonPtrToFightTrainerPtr(NULL, arg1) != arg0) {
            return fightTrainer_GetEnemyStoreTokuseiData(arg0, temp_r31);
        }
        return pokemonGetTokuseiDataId(temp_r30);
    }
    return 0U;
}

u16 fightTrainerAiGetFightPokemonZokuseiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u8 arg2) {
    s32 temp_r31;
    s32 temp_r30;
    u32 temp_r30_2;

    temp_r31 = (u8) (fightFloor_GetFightType(NULL));
    temp_r30_2 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u16) (pokemon_GetPokemonDataId(fightPokemonGetPokemonPtr(arg1)));
    if (fightTrainerAiDB_GetZokuseiCheckFlag(temp_r30_2) == 1) {
        if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r31) == 0) {
            return (u16) pokemonDB_GetZokuseiDataId(temp_r30, arg2);
        }
        return (u16) pokemonDB_GetZokuseiDataId(temp_r30, arg2);
    }
    return 9U;
}

u8 fightTrainerAiIsFightPokemonNokoriWazaPpHikui(FIGHT_TRAINER *arg0, FightPokemon *arg1, u32 arg2) {
    s32 temp_r31;
    s32 temp_r30;
    u32 temp_r29;

    temp_r29 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r30 = (u8) (fightTrainerAiGetFightPokemonWazaNowPp(arg0, arg1, arg2));
    temp_r31 = (u8) (fightTrainerAiGetFightPokemonWazaMaxPp(arg0, arg1, arg2));
    return (u8) (((s32) (temp_r30 * 0x64) / (s32) temp_r31) <= (s32) fightTrainerAiDB_GetWazaNokoriPpValue(temp_r29));
}

u8 fightTrainerAiGetFightPokemonWazaMaxPp(FIGHT_TRAINER *arg0, FightPokemon *arg1, u32 arg2) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightPokemonGetPokemonPtr(arg1);
    return pokemonWazaGetMaxPP(fightPokemonGetPokemonPtr(arg1), arg2);
}

u8 fightTrainerAiGetFightPokemonWazaNowPp(FIGHT_TRAINER *arg0, FightPokemon *arg1, u32 arg2) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightPokemonGetPokemonPtr(arg1);
    return pokemon_GetPokemonWazaPp(fightPokemonGetPokemonPtr(arg1), arg2);
}

u16 fightTrainerAiGetFightPokemonWazaDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1, u8 arg2) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightPokemonGetPokemonPtr(arg1);
    return pokemon_GetPokemonWazaDataId(fightPokemonGetPokemonPtr(arg1), arg2);
}

u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightPokemonGetSoubiItemSoubiDataId(arg1);
}

u16 fightTrainerAiGetFightPokemonSoubiItemDataId(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightFloor_GetFightType(NULL);
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return fightPokemonGetSoubiItemDataId(arg1);
}

u32 fightTrainerAiGetFightPokemonFriend(FIGHT_TRAINER *arg0, FightPokemon *arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return pokemon_GetFriend(fightPokemonGetPokemonPtr(arg1));
}

u8 fightTrainerAiGetWazaRiskFlag(FIGHT_TRAINER *arg0, u16 arg1) {
    if (fightTrainerAiDB_GetWazaRiskFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0))) == 1) {
        return wazaDB_GetRiskFlag(arg1);
    }
    return 0U;
}

u8 fightTrainerAiGetWazaPp(FIGHT_TRAINER *arg0, u16 arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaDB_GetPp(arg1);
}

u8 fightTrainerAiGetWazaRangeId(FIGHT_TRAINER *arg0, u16 arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaDB_GetRangeId(arg1);
}

u8 fightTrainerAiIsWazaAvgTakai(FIGHT_TRAINER *arg0, u16 arg1) {
    s32 temp_r31;
    u32 temp_r30;

    temp_r30 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = (u8) (fightTrainerAiGetWazaAvg(arg0, arg1));
    return (u8) (fightTrainerAiDB_GetWazaAvgValue(temp_r30) <= temp_r31);
}

u8 fightTrainerAiGetWazaAvg(FIGHT_TRAINER *arg0, u16 arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    if (fightSeqIsTenkouHit(arg1) == 1) {
        return 0x64U;
    }
    if (fightSeqIsAllwaysHit(arg1) == 1) {
        return 0x64U;
    }
    return wazaDB_GetAvg(arg1);
}

u8 fightTrainerAiIsWazaTypeId(FIGHT_TRAINER *arg0, u16 arg1, u8 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaIsWazaTypeId(arg1, arg2);
}

u8 fightTrainerAiGetWazaTypeId(FIGHT_TRAINER *arg0, u16 arg1, u32 arg2) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaDB_GetTypeId(arg1, arg2);
}

u16 fightTrainerAiGetWazaIryoku(FIGHT_TRAINER *arg0, u16 arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaDB_GetIryoku(arg1);
}

u8 fightTrainerAiGetWazaAddKoukaAvg(FIGHT_TRAINER *arg0, u16 arg1) {
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    return wazaDB_GetAddFightKoukaAvg(arg1);
}

u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *arg0, u16 arg1, FightOutPokemon *arg2) {
    u16 sp8;
    s32 temp_r31;
    u32 temp_r30;

    temp_r30 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    temp_r31 = (u8) (fightTrainerAiGetFightFloorNowTenkouDataId(arg0, NULL, 1U));
    if (fightTrainerAiDB_GetZokuseiCheckFlag(temp_r30) == 1) {
        if ((arg1 == 0xA5) || (wazaCheckDarkWaza(arg1) == 1) || (arg1 == 0xF8) || (arg1 == 0x161)) {
            return 9U;
        }
        switch (arg1) {                             /* switch 1; irregular */
        case 0xED:                                  /* switch 1 */
            pokemonGetMezamerupower(fightOutPokemonGetPokemonPtr(arg2), NULL, &sp8);
            return sp8;
        case 0x137:                                 /* switch 1 */
            switch (temp_r31) {                     /* switch 2; irregular */
            case 2:                                 /* switch 2 */
                sp8 = 0xB;
                break;
            case 3:                                 /* switch 2 */
                sp8 = 5;
                break;
            case 1:                                 /* switch 2 */
                sp8 = 0xA;
                break;
            case 4:                                 /* switch 2 */
                sp8 = 0xF;
                break;
            case 5:                                 /* switch 2 */
                sp8 = 0;
                break;
            default:                                /* switch 2 */
                sp8 = 0;
                break;
            }
            return sp8;
        default:                                    /* switch 1 */
            return (u16) wazaDB_GetZokuseiDataId(arg1);
        }
    } else {
        return 9U;
    }
}

s32 fightTrainerAiGetValueAryMaxBanme(s32 *arg0, u16 arg1, u8 arg2) {
    s32 sp8[16];
    s32 var_r9;
    u16 var_r8;
    u16 var_r7;
    s32 temp_r6;
    u16 var_r31;
    u16 var_r0;

    var_r9 = -0xC8;
    var_r31 = 0;
    for (var_r8 = 0; var_r8 < 0x10U; var_r8++) {
        sp8[var_r8] = -1;
    }
    for (var_r7 = 0; var_r7 < arg1; var_r7++) {
        temp_r6 = arg0[var_r7];
        if (var_r9 < temp_r6) {
            var_r9 = temp_r6;
        }
    }
    for (var_r8 = 0; var_r8 < arg1; var_r8++) {
        if (var_r9 <= arg0[var_r8]) {
            sp8[var_r31] = var_r8;
            var_r31 += 1;
        }
        if (var_r31 >= 0x10U) {
            break;
        }
    }
    if (var_r31 == 0) {
        return -1;
    }
    if (var_r31 == 1) {
        var_r0 = 0;
    } else if (arg2 == 1) {
        var_r0 = HSD_Rand() % var_r31;
    } else {
        var_r0 = 0;
    }
    return sp8[var_r0];
}

s32 fightTrainerAiReviseValueByAddsubDataId(s32 arg0, u8 arg1, FIGHT_TRAINER *arg2, u16 arg3) {
    return fightTrainerAiReviseValue(arg0, arg1, fightTrainerAiValueAddsubDB_GetValue(arg3));
}

s32 fightTrainerAiAddValueByAddsubDataId(s32 arg0, FIGHT_TRAINER *arg1, u16 arg2) {
    return fightTrainerAiAddValue(arg0, fightTrainerAiValueAddsubDB_GetValue(arg2));
}

s32 fightTrainerAiReviseValue(s32 arg0, u8 arg1, s32 arg2) {
    s16 temp_r4;
    s32 temp_r5;

    temp_r4 = (arg1 * 0x64) / 100;
    temp_r5 = (temp_r4 - 0x32) * arg2;
    return fightTrainerAiAddValue(arg0, (s16) (temp_r5 / 50));
}

s32 fightTrainerAiAddValue(s32 arg0, s32 arg1) {
    if (arg1 > 0) {
        if ((s32) (arg0 + arg1) > 0xC8) {
            return 0xC8;
        }
        return arg0 + arg1;
    }
    if (arg1 < 0) {
        if ((s32) (arg0 + arg1) < -0xC8) {
            return -0xC8;
        }
        return arg0 + arg1;
    }
    return arg0;
}

u8 fightAi_AppointWazaKoukaFlag(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2) {
    u16 spC[2];
    u16 sp8[2];
    u16 temp_r3;
    u16 temp_r3_0;
    u16 temp_r31;
    s32 temp_r29;
    u8 var_r28;

    if (arg0 == NULL) {
        return 0U;
    }
    if (arg1 == NULL) {
        return 0U;
    }
    for (var_r28 = 0; var_r28 < 2U; var_r28++) {
        temp_r3_0 = fightOutPokemon_GetZokuseiDataId(arg0, var_r28);
        temp_r29 = (var_r28 * 2) & 0x1FE;
        *(u16 *)((u8 *)spC + temp_r29) = temp_r3_0;
        *(u16 *)((u8 *)sp8 + temp_r29) = fightOutPokemon_GetZokuseiDataId(arg1, var_r28);
    }
    if ((sp8[0] == arg2) || (sp8[1] == arg2)) {
        temp_r31 = zokuseiGetWazaJoutai(arg2, spC[0]);
        temp_r3 = zokuseiGetWazaJoutai(arg2, spC[1]);
        if ((temp_r31 == 0x43) || (temp_r3 == 0x43)) {
            return 0x43U;
        }
        switch ((s32) temp_r31) {                   /* switch 1; irregular */
        case 0x42:                                  /* switch 1 */
            switch ((s32) temp_r3) {                /* switch 2; irregular */
            case 0x3F:                              /* switch 2 */
            case 0x42:                              /* switch 2 */
                return 0x42U;
            case 0x41:                              /* switch 2 */
                return 0x3FU;
            }
            break;
        case 0x3F:                                  /* switch 1 */
            switch ((s32) temp_r3) {                /* switch 3; irregular */
            case 0x3F:                              /* switch 3 */
                return 0x3FU;
            case 0x41:                              /* switch 3 */
                return 0x41U;
            case 0x42:                              /* switch 3 */
                return 0x42U;
            }
            break;
        case 0x41:                                  /* switch 1 */
            switch ((s32) temp_r3) {                /* switch 4; irregular */
            case 0x41:                              /* switch 4 */
            case 0x3F:                              /* switch 4 */
                return 0x41U;
            case 0x42:                              /* switch 4 */
                return 0x3FU;
            }
            break;
        }
    } else {
        return 0U;
    }
    return 0U;
}

s32 fightAi_HitCheckWazaAboutJoutaiAndType(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon *arg2, u16 arg3) {
    FightOutPokemon *sp8[8];
    FightPokemon *temp_r31;
    u16 temp_r30;
    u16 temp_r29;
    u16 temp_r28;
    FightPokemon *temp_r27;
    u32 temp_r27_2;

    if (arg0 == NULL) {
        return 0;
    }
    if (arg1 == NULL) {
        return 0;
    }
    if (arg2 == NULL) {
        return 0;
    }
    if (arg3 == 0) {
        return 0;
    }
    temp_r27 = fightOutPokemon_GetFightPokemonPtr(arg1);
    temp_r31 = fightOutPokemon_GetFightPokemonPtr(arg2);
    fightPokemon_GetPokemonBuffPtr(temp_r27);
    fightPokemon_GetPokemonBuffPtr(temp_r31);
    temp_r30 = fightOutPokemonGetZokuseiDataId(arg2, 0U);
    temp_r29 = fightOutPokemonGetZokuseiDataId(arg2, 1U);
    temp_r28 = fightTrainerAiGetWazaZokuseiDataId(arg0, arg3, arg1);
    temp_r27_2 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, sp8, 1U, 1U);
    if ((fightTrainerAiDB_GetPokemonJoutaiFlag(temp_r27_2) == 1) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x1DU) == 0) && (arg3 != 0xC3) && (fightAi_LateDefPokeThanAllyPoke(sp8, arg2) != 1)) {
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x1FU) == 1) && ((arg3 != 0x57) || (arg3 != 0x147) || (arg3 != 0x10) || (arg3 != 0xEF))) {
            return 0;
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x20U) == 1) {
            if ((arg3 != 0x59) || (arg3 != 0xDE)) {
                return 0;
            }
            if (_fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(arg0, temp_r31) == 0x1A) {
                return 0;
            }
            if ((temp_r30 == 2) || (temp_r29 == 2)) {
                return 0;
            }
            goto block_27;
        }
block_27:
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg2, 0x21U) == 1) && ((arg3 != 0xFA) || (arg3 != 0x39))) {
            return 0;
        }
        goto block_31;
    }
block_31:
    if ((fightTrainerAiDB_GetZokuseiCheckFlag(temp_r27_2) == 1) && ((zokuseiGetWazaJoutai(temp_r28, temp_r30) == 0x43) || (zokuseiGetWazaJoutai(temp_r28, temp_r29) == 0x43))) {
        return 0;
    }
    return 1;
}

FightOutPokemon *fightAi_SelectDefPoke(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon **arg2, u16 arg3, u16 arg4, s8 arg5) {
    u8 sp8[64];
    s16 temp_r3;
    u8 var_r31;
    u8 var_r25;
    s16 var_r24;
    s32 temp_r24;

    temp_r24 = (u8) (fightFloor_GetFightType(NULL));
    if (wazaDB_GetRangeId(arg4) == 0) {
        var_r24 = -0xFF;
        for (var_r25 = 0; var_r25 < arg3; var_r25++) {
            temp_r3 = fightAi_ThreatEnemyValue(arg0, arg1, arg2[var_r25], arg5, 0U, -1, -1);
            if (var_r24 < temp_r3) {
                sp8[0] = var_r25;
                var_r24 = temp_r3;
                var_r31 = 1;
            } else if (var_r24 == temp_r3 && var_r24 > -0xFF) {
                sp8[var_r31] = var_r25;
                var_r31 += 1;
            }
        }
        return arg2[sp8[HSD_Rand() % var_r31]];
    }
    return fightSeqSelectDefensePokemonPtr(arg1, arg4, temp_r24, NULL, 1U, 1U, -1);
}

void fightAi_InitAllWazaValid(void) {
    u8 var_r30;

    var_r30 = 0;
    ai_allwaza_valid_work.count = 0;
loop_2:
    while (var_r30 < 0x40U) {
        fightAi_InitAllWazaValidSub(&ai_allwaza_valid_tbl[var_r30]);
        var_r30 += 1;
    }
}

s32 fightAi_CreateFightActionAttckIrekae(FightOutPokemon *arg0, s32 arg1) {
    if (arg0 == NULL) {
        return 0;
    }
    if ((s16) arg1 < 0) {
        return 0;
    }
    fightOutPokemonCreateFightAction(arg0, 0U, 9U, NULL, &fight_action_data_turn, arg1);
    return 1;
}

s32 fightAi_CreateFightActionAttckWaza(FightOutPokemon *arg0, FightOutPokemon *arg1, u16 arg2, s16 arg3) {
    s32 sp8;
    s32 temp_r3;
    FightOutPokemon *temp_r3_2;
    u32 temp_r3_3;
    FightOutPokemon *var_r28;

    var_r28 = arg1;
    temp_r3 = (u8) (fightFloor_GetFightType(NULL));
    if (arg0 == NULL) {
        return 0;
    }
    if (var_r28 == NULL) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg3 < 0) {
        return 0;
    }
    temp_r3_2 = fightSeqSelectDefensePokemonPtr(arg0, arg2, temp_r3, (void *)&fightTrainerAiWazaSelectDefensePokemon, 1U, 0U, -1);
    if (temp_r3_2 != NULL) {
        var_r28 = temp_r3_2;
    }
    if (var_r28 == NULL) {
        return 0;
    }
    temp_r3_3 = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(var_r28, temp_r3);
    sp8 = 0;
    fightOutPokemonCreateFightActionAttackWaza(arg0, 0U, 0x13U, NULL, &fight_action_data_waza, arg2, temp_r3_3, (s8) arg3, 0U);
    return 1;
}

void fightTrainerAiSetAllyPokemon(FIGHT_TRAINER *arg0) {
    FightPokemon * sp38[24];
    FightOutPokemon * sp18[8];
    u16 sp8[8];
    FightOutPokemon *temp_r31;
    FightPokemon *temp_r30;
    u16 var_r29;
    u16 var_r28;
    u16 var_r27;
    s32 temp_r26;
    s32 temp_r25;
    s32 temp_r23;
    s32 temp_r17;
    s32 var_r15;
    s32 temp_r15;
    s32 temp_r15_2;

    temp_r17 = (u16) (fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, sp18, 0U, 1U));
    temp_r23 = (u16) (fightFloorGetFightTrainerFightPokemonPtrAry(NULL, arg0, sp38, 1U, 1U));
    var_r29 = 0;
loop_17:
    while (var_r29 < temp_r23) {
        temp_r30 = *(FightPokemon * *)((u8 *)sp38 + ((var_r29 * 4) & 0x3FFFC));
        if (temp_r30 != NULL) {
            var_r28 = 0;
loop_15:
            while (var_r28 < temp_r17) {
                temp_r31 = *(FightOutPokemon * *)((u8 *)sp18 + ((var_r28 * 4) & 0x3FFFC));
                if ((temp_r31 != NULL) && (fightOutPokemonGetFightEntryId(temp_r31) >= 0)) {
                    temp_r15 = (u16) (fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r31, sp8, NULL, 0U));
                    temp_r26 = (u16) (fightOutPokemonMaxHpWaruValue(temp_r31, 1U));
                    var_r27 = 0;
loop_13:
                    while (var_r27 < temp_r15) {
                        var_r15 = 0;
                        temp_r25 = (u16) (*(u16 *)((u8 *)sp8 + ((var_r27 * 2) & 0x1FFFE)));
                        if ((temp_r25 != 0) && (temp_r25 != 0x176) && (fightTrainerAiGetWazaZokuseiDataId(arg0, temp_r25, temp_r31) != 9)) {
                            if (fightTrainerAiIsWazaTypeId(arg0, temp_r25, 1U) == 1) {
                                var_r15 = fightTrainerAiWazaDoWazaDamageFightPokemonFunc(arg0, temp_r31, temp_r25, temp_r30, 0U);
                            }
                            temp_r15_2 = (u16) (var_r28 + var_r27);
                            fightPokemon_SetAiDamage(temp_r30, temp_r15_2, 0U, (s32) (var_r15 * 0x64) / (s32) temp_r26);
                            fightPokemon_SetAiDamage(temp_r30, temp_r15_2, 1U, (s32) temp_r25);
                        }
                        var_r27 += 1;
                    }
                }
                var_r28 += 1;
            }
        }
        var_r29 += 1;
    }
}

void fightTrainerAiSetEnemyPokemon(FIGHT_TRAINER *arg0) {
    FightOutPokemon * sp98[8];
    s32 sp78[8];
    s32 sp58[8];
    FightOutPokemon * sp38[8];
    s32 sp18[8];
    u16 sp8[8];
    s32 temp_r31;
    s32 temp_r29;
    s32 temp_r28;
    u16 var_r27;
    s32 var_r26;
    FightOutPokemon *temp_r25;
    s32 temp_r25_2;
    FightOutPokemon *temp_r24;
    s32 temp_r24_2;
    FightOutPokemon *temp_r24_3;
    u16 var_r22;
    u16 var_r22_2;
    u16 var_r21;
    u16 var_r21_2;
    u16 var_r21_3;
    u16 var_r20;
    s32 temp_r20;
    u16 var_r19;
    s32 temp_r18;
    u16 *temp_r18_2;
    u8 var_r17;
    s32 var_r16;
    s32 temp_r14;
    u16 var_r6;
    s16 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s16 temp_r3_5;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u32 spC4;
    u32 spC0;
    s32 spBC;
    s32 spB8;

    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightTrainerInitEnemyPokemonFightOutStatus(arg0, 1U);
    var_r6 = 0;
loop_2:
    while (var_r6 < 8U) {
        temp_r0 = (var_r6 * 4) & 0x3FFFC;
        var_r6 += 1;
        *(s32 *)((u8 *)sp78 + temp_r0) = 0;
        *(s32 *)((u8 *)sp18 + temp_r0) = 0;
    }
    temp_r31 = (u16) (fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, sp98, 0U, 1U));
    spB8 = fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, sp38, 1U, 1U);
    var_r20 = 0xFFFF;
    var_r26 = -0xFFFF;
    spC4 = (u32) temp_r31;
    var_r19 = 0xFFFF;
    var_r16 = -0xFFFF;
    var_r17 = 0xFF;
    var_r27 = 0;
loop_38:
    while (var_r27 < spC4) {
        temp_r28 = (var_r27 * 4) & 0x3FFFC;
        temp_r25 = *(FightOutPokemon * *)((u8 *)sp98 + temp_r28);
        if (temp_r25 != NULL) {
            temp_r3 = fightOutPokemonGetFightEntryId(temp_r25);
            if (temp_r3 >= 0) {
                temp_r14 = (u16) (fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, temp_r25));
                spBC = fightTrainerAiGetFightOutPokemonWazaDataIdAry(arg0, temp_r25, sp8, NULL, 0U);
                temp_r3_2 = (u16) (fightTrainerAiGetFightOutPokemonNowHpPercentage(arg0, temp_r25));
                if (var_r20 > temp_r3_2) {
                    var_r20 = temp_r3_2;
                }
                temp_r3_3 = (u8) (fightTrainerAiGetFightOutPokemonLevel(arg0, temp_r25));
                if (var_r17 > temp_r3_3) {
                    var_r17 = temp_r3_3;
                }
                temp_r3_4 = (u16) (fightTrainerAiGetPokemonDataDefense(arg0, temp_r14));
                if (var_r19 > temp_r3_4) {
                    var_r19 = temp_r3_4;
                }
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisMaxHp(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisPhyAtk(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisPhyDef(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisSpeAtk(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisSpeDef(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) + fightTrainerAiGetFightOutPokemonBasisSubayasa(arg0, temp_r25);
                *(s32 *)((u8 *)sp18 + temp_r28) = *(s32 *)((u8 *)sp18 + temp_r28) * fightTrainerAiGetFightOutPokemonLevel(arg0, temp_r25);
                temp_r0_2 = *(s32 *)((u8 *)sp18 + temp_r28);
                if (var_r16 < temp_r0_2) {
                    var_r16 = temp_r0_2;
                }
                fightAi_AddStoreTokusei(temp_r25, arg0);
                temp_r29 = (u16) (pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r25)));
                var_r22 = 0;
                spC0 = (u32) (u16) spB8;
loop_25:
                while (var_r22 < spC0) {
                    temp_r24 = *(FightOutPokemon * *)((u8 *)sp38 + ((var_r22 * 4) & 0x3FFFC));
                    if (temp_r24 != NULL) {
                        var_r21 = 0;
loop_23:
                        while (var_r21 < (u16) spBC) {
                            temp_r18 = (u16) (*(u16 *)((u8 *)sp8 + ((var_r21 * 2) & 0x1FFFE)));
                            if ((temp_r18 != 0) && (temp_r18 != 0x176) && (fightTrainerAiGetWazaZokuseiDataId(arg0, temp_r18, temp_r25) != 9) && (fightTrainerAiIsWazaTypeId(arg0, temp_r18, 1U) != 0)) {
                                *(s32 *)((u8 *)sp78 + temp_r28) = *(s32 *)((u8 *)sp78 + temp_r28) + fightTrainerAiWazaDoWazaDamageFunc(arg0, temp_r25, temp_r18, temp_r24, 0U);
                                *(s32 *)((u8 *)sp58 + temp_r28) = (s32) (*(s32 *)((u8 *)sp78 + temp_r28) * 0x64) / (s32) temp_r29;
                            }
                            var_r21 += 1;
                        }
                    }
                    var_r22 += 1;
                }
                temp_r0_3 = *(s32 *)((u8 *)sp58 + temp_r28);
                if (var_r26 < temp_r0_3) {
                    var_r26 = temp_r0_3;
                }
                var_r21_2 = 0;
loop_36:
                while (var_r21_2 < 0x96U) {
                    temp_r18_2 = &expect_waza_data[var_r21_2][0];
                    if ((u16) *temp_r18_2 == pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(temp_r25))) {
                        var_r22_2 = 0;
loop_34:
                        if (var_r22_2 < 8U) {
                            temp_r24_2 = (u16) (*(u16 *)((u8 *)temp_r18_2 + (((var_r22_2 * 2) & 0x1FFFE) + 2)));
                            if ((temp_r24_2 != 0) && (fightTrainer_GetEnemyExpectWazaData(arg0, (u8) temp_r3, (u8) var_r22_2) == 0)) {
                                fightTrainer_SetEnemyExpectWazaData(arg0, (u8) temp_r3, (u8) var_r22_2, temp_r24_2);
                                fightTrainer_SetEnemyExpectWazaNum(arg0, (u8) temp_r3, (u8) temp_r31);
                                var_r22_2 += 1;
                                goto loop_34;
                            }
                        }
                    }
                    var_r21_2 += 1;
                }
            }
        }
        var_r27 += 1;
    }
    var_r21_3 = 0;
loop_53:
    while (var_r21_3 < temp_r31) {
        temp_r20 = (var_r21_3 * 4) & 0x3FFFC;
        temp_r24_3 = *(FightOutPokemon * *)((u8 *)sp98 + temp_r20);
        if (temp_r24_3 != NULL) {
            temp_r3_5 = fightOutPokemonGetFightEntryId(temp_r24_3);
            if (temp_r3_5 >= 0) {
                temp_r25_2 = (u16) (fightTrainerAiGetFightOutPokemonPokemonDataId(arg0, temp_r24_3));
                if ((s32) var_r20 >= fightTrainerAiGetFightOutPokemonNowHpPercentage(arg0, temp_r24_3)) {
                    fightTrainer_SetEnemyNowhp1banhikuiFlag(arg0, (u8) temp_r3_5, 1U);
                }
                if (var_r17 >= fightTrainerAiGetFightOutPokemonLevel(arg0, temp_r24_3)) {
                    fightTrainer_SetEnemyLv1banhikuiFlag(arg0, (u8) temp_r3_5, 1U);
                }
                if (var_r19 >= fightTrainerAiGetPokemonDataDefense(arg0, temp_r25_2)) {
                    fightTrainer_SetEnemyDefense1banhikuiFlag(arg0, (u8) temp_r3_5, 1U);
                }
                if (var_r26 <= (s32) *(s32 *)((u8 *)sp58 + temp_r20)) {
                    fightTrainer_SetEnemyBadwazaHaveFlag(arg0, (u8) temp_r3_5, 1U);
                }
                if (var_r16 <= (s32) *(s32 *)((u8 *)sp18 + temp_r20)) {
                    fightTrainer_SetEnemyParam1bantakaiFlag(arg0, (u8) temp_r3_5, 1U);
                }
            }
        }
        var_r21_3 += 1;
    }
}

u8 fightAi_LateDefPokeThanAllyPoke(FightOutPokemon **arg0, FightOutPokemon *arg1) {
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;

    temp_r4 = arg0[0];
    if ((temp_r4 != NULL) || ((FightOutPokemon *) arg0[1] != NULL)) {
        if ((temp_r4 != NULL) && ((FightOutPokemon *) arg0[1] != NULL)) {
            if ((fightFloorCmpfightOutPokemonNimbleness(NULL, temp_r4, arg1, 1U) == 1) && (fightFloorCmpfightOutPokemonNimbleness(NULL, arg0[1], arg1, 1U) == 1)) {
                return 1U;
            }
            goto block_13;
        }
        if (temp_r4 != NULL) {
            if (fightFloorCmpfightOutPokemonNimbleness(NULL, temp_r4, arg1, 1U) == 1) {
                return 1U;
            }
            goto block_13;
        }
        temp_r4_2 = arg0[1];
        if ((temp_r4_2 != NULL) && (fightFloorCmpfightOutPokemonNimbleness(NULL, temp_r4_2, arg1, 1U) == 1)) {
            return 1U;
        }
        goto block_13;
    }
block_13:
    return 0U;
}

u8 fightAi_DamageKizetsuFlag(FightOutPokemon **arg0, s32 arg1) {
    FightOutPokemon *temp_r3;
    u8 var_r31;

    for (var_r31 = 0; var_r31 < 8U; var_r31++) {
        temp_r3 = arg0[var_r31];
        if (temp_r3 != NULL && arg1 >= (s32) pokemon_GetHp(fightOutPokemonGetPokemonPtr(temp_r3))) {
            return 1U;
        }
    }
    return 0U;
}

u8 fightAi_PokemonTokuseiMoukaFlag(FightOutPokemon *arg0) {
    FIGHT_TRAINER *temp_r31;
    FightPokemon *temp_r4;

    temp_r4 = fightOutPokemon_GetFightPokemonPtr(arg0);
    temp_r31 = fightFloorGetFightPokemonPtrToFightTrainerPtr(NULL, temp_r4);
    if (fightOutPokemonIsNokoriHpFollowing(arg0, 3U) == 1) {
        if ((fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x42U) == 2) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x44U) == 2) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x41U) == 2) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x43U) == 2)) {
            return 2U;
        }
        if ((fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x42U) == 1) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x44U) == 1) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x41U) == 1) || (fightAi_GetTokuseiHaveFlag(temp_r31, arg0, 0x43U) == 1)) {
            return 1U;
        }
        goto block_11;
    }
block_11:
    return 0U;
}

u16 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16 arg0, u16 arg1) {
    u8 var_r3;

    var_r3 = wazaDB_GetZokuseiDataId(arg0);
    if (arg0 == 0x137) {
        if ((s32) arg1 != 3) {
            if ((s32) arg1 < 3) {
                if ((s32) arg1 != 1) {
                    if ((s32) arg1 < 1) {
                        return (u16) var_r3;
                    }
                    return 0xBU;
                }
                return 0xAU;
            }
            if ((s32) arg1 != 5) {
                if ((s32) arg1 < 5) {
                    var_r3 = 0xF;
                }
                /* Duplicate return node #14. Try simplifying control flow for better match */
                return (u16) var_r3;
            }
            return 0U;
        }
        return 5U;
    }
    return (u16) var_r3;
}

u8 fightAi_CreateAllWazaValid_GetDefense(u16 arg0, u8 arg1) {
    s32 temp_r3;

    temp_r3 = (u8) (wazaDB_GetRangeId(arg0));
    switch (temp_r3) {
    case 0:
        return arg1;
    case 2:
    case 4:
    case 6:
        return 2;
    case 1:
    case 7:
        return 3;
    case 5:
        return 4;
    case 3:
        return 5;
    default:
        return 0;
    }
}

u8 fightAi_AttackResult(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2, u16 arg3, u16 arg4) {
    FightOutPokemon *sp8[2];
    s32 temp_r3;
    Pokemon *temp_r30;
    FightPokemon *temp_r3_2;
    s32 temp_r29;
    s32 temp_r28;
    s32 temp_r22;
    s32 temp_r21;
    u32 temp_r20;

    if (arg1 == NULL) {
        return 0U;
    }
    temp_r3_2 = fightOutPokemon_GetFightPokemonPtr(arg1);
    temp_r30 = fightPokemon_GetPokemonBuffPtr(temp_r3_2);
    temp_r29 = (u16) (fightOutPokemonGetZokuseiDataId(arg1, 0U));
    temp_r28 = (u16) (fightOutPokemonGetZokuseiDataId(arg1, 1U));
    temp_r22 = (u8) (wazaDB_GetZokuseiDataId(arg2));
    temp_r21 = (u8) (wazaDB_GetZokuseiDataId(arg3));
    temp_r20 = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(arg0));
    fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, sp8, 1U, 1U);
    if ((fightTrainerAiDB_GetZokuseiCheckFlag(temp_r20) == 1) && ((zokuseiGetWazaJoutai((u16) temp_r22, temp_r29) == 0x43) || (zokuseiGetWazaJoutai((u16) temp_r22, temp_r28) == 0x43)) && ((zokuseiGetWazaJoutai((u16) temp_r21, temp_r29) == 0x43) || (zokuseiGetWazaJoutai((u16) temp_r21, temp_r28) == 0x43))) {
        return 1U;
    }
    if ((fightTrainerAiDB_GetPokemonJoutaiFlag(temp_r20) == 1) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1DU) == 0) && (arg2 != 0xC3) && (arg3 != 0xC3) && (fightAi_LateDefPokeThanAllyPoke(sp8, arg1) != 1)) {
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1FU) == 1) && (arg2 != 0x57) && (arg2 != 0x147) && (arg2 != 0x10) && (arg2 != 0xEF) && (arg3 != 0x57) && (arg3 != 0x147) && (arg3 != 0x10) && (arg3 != 0xEF)) {
            return 2U;
        }
        if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x20U) == 1) {
            if ((arg2 != 0x59) && (arg2 != 0xDE) && (arg3 != 0x59) && (arg3 != 0xDE)) {
                return 2U;
            }
            if (_fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(arg0, temp_r3_2) == 0x1A) {
                return 2U;
            }
            if ((temp_r29 == 2) || (temp_r28 == 2)) {
                return 2U;
            }
            goto block_34;
        }
block_34:
        if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x21U) == 1) && (arg2 != 0xFA) && (arg2 != 0x39) && (arg3 != 0xFA) && (arg3 != 0x39)) {
            return 2U;
        }
        goto block_40;
    }
block_40:
    temp_r3 = (u16) (pokemon_GetHp(temp_r30));
    return arg4 >= temp_r3 ? 3 : 0;
}

u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    s32 temp_r30;
    s8 temp_r26;
    u8 var_r25;
    u8 var_r24;
    FightPokemon *temp_r3;
    Pokemon *temp_r3_2;
    s32 temp_r0;

    var_r24 = 0;
    if (arg1 == NULL) {
        return 0U;
    }
    if (arg0 == NULL) {
        return 0U;
    }
    if (arg2 == 0) {
        return 0U;
    }
    fightTrainerAiGetWazaIryoku(arg0, arg2);
    temp_r3 = fightOutPokemon_GetFightPokemonPtr(arg1);
    temp_r3_2 = fightPokemon_GetPokemonBuffPtr(temp_r3);
    temp_r26 = pokemonSearchWazaDataId(temp_r3_2, arg2);
    for (var_r25 = 0; var_r25 < 4U; var_r25++) {
        if (arg2 == fightTrainerAiGetFightPokemonWazaDataId(arg0, temp_r3, var_r25)) {
            var_r24 = 1;
            break;
        }
    }
    if (var_r24 == 0) {
        return 0U;
    }
    if (pokemon_GetPokemonWazaPp(temp_r3_2, temp_r26) == 0) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x2AU) == 1) && (arg2 != pokemon_GetPokemonWazaDataId(temp_r3_2, fightOutPokemonGetBuffJoutaiDataId(arg1, 0x2AU)))) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x29U) == 1) && ((s32) arg2 == fightOutPokemonGetBuffJoutaiDataId(arg1, 0x29U))) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x30U) == 1) && (fightTrainerAiIsWazaTypeId(arg0, arg2, 1U) == 0)) {
        return 0U;
    }
    if (fightFloorCheckHuuinWazaFightOutPokemon(NULL, arg1, arg2) == 1) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x1BU) == 1) && (arg2 == fightOutPokemon_GetMotoWazaDataId(arg1))) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 8U) == 1) && (arg2 != 0xD6) && (arg2 != 0xAD)) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 7U) == 1) && (arg2 != 0xAC) && (arg2 != 0xDD)) {
        return 0U;
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0x36U) == 1) && ((s32) arg2 != fightOutPokemonGetBuffJoutaiDataId(arg1, 0x36U))) {
        return 0U;
    }
    if ((_fightTrainerAiGetFightPokemonTokuseiDataId__FP13FIGHT_TRAINERP12FightPokemon(arg0, temp_r3) == 0x36) && (fightOutPokemon_GetNamakeFlag(arg1) == 1)) {
        return 0U;
    }
    if ((fightOutPokemon_GetFightoutTurnCount(arg1) >= 2U) && (arg2 == 0xFC)) {
        return 0U;
    }
    if (arg2 == 0x42 || arg2 == 0x26 || arg2 == 0x24) {
        return 1U;
    }
    if (arg2 == 0xAE) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, temp_r3, 7U) == 1) {
            temp_r30 = (u16) (fightOutPokemonNowHpWaruValue(arg1, 1U));
            if (fightOutPokemonMaxHpWaruValue(arg1, 2U) >= temp_r30) {
                return 1U;
            }
        }
    }
    if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 9U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 0xAU) == 1)) {
        return 2U;
    }
    return fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg1, 5U) == 1 ? 3 : 4;
}

u8 fightAi_WazaSuccessProbability(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, FightOutPokemon **arg2, u16 arg3) {
    u16 sp8[2];
    FightOutPokemon *temp_r3;
    u8 var_r31;
    u8 var_r30;
    s32 temp_r3_2;
    u8 var_r29;
    s32 temp_r23;
    Pokemon *temp_r22;

    var_r29 = 0;
    if (arg1 == NULL) {
        return 0U;
    }
    if (arg0 == NULL) {
        return 0U;
    }
    if (arg3 == 0) {
        return 0U;
    }
    temp_r22 = fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(arg1));
    var_r31 = wazaDB_GetAvg(arg3);
    temp_r23 = (u16) (pokemon_GetNimbleness(temp_r22));
    for (var_r30 = 0; var_r30 < 2U; var_r30++) {
        temp_r3 = arg2[var_r30];
        if (temp_r3 != NULL) {
            sp8[var_r30] = pokemon_GetNimbleness(fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(temp_r3)));
        } else {
            sp8[var_r30] = 0;
        }
        if (temp_r23 < sp8[var_r30]) {
            var_r29 = var_r29 + 1;
        }
    }
    if (var_r29 == 1) {
        var_r31 = (u8) ((s32) (var_r31 * 0x4B) / 100);
    } else if (var_r29 == 2) {
        var_r31 = (u8) ((s32) (var_r31 * 0x32) / 100);
    }
    temp_r3_2 = (u8) (fightAi_CanMoveAppointWaza(arg0, arg1, arg3));
    switch ((s32) temp_r3_2) {                      /* irregular */
    case 0:
        var_r31 = 0;
        break;
    default:
        var_r31 = (u8) ((s32) (var_r31 * 0x32) / 100);
        break;
    case 3:
        var_r31 = (u8) ((s32) (var_r31 * 0x4B) / 100);
        break;
    }
    return var_r31;
}

void fightAi_AddStoreTokusei(FightOutPokemon *arg0, FIGHT_TRAINER *arg1) {
    FightPokemon *temp_r3;
    u8 temp_r31;
    s32 temp_r30;
    s32 temp_r29;
    Pokemon *temp_r28;
    u16 temp_r28_2;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_r3 = fightOutPokemon_GetFightPokemonPtr(arg0);
        temp_r28 = fightPokemon_GetPokemonBuffPtr(temp_r3);
        temp_r31 = fightPokemon_GetEntryId(temp_r3);
        temp_r30 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r28), 0U));
        temp_r29 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r28), 1U));
        temp_r28_2 = fightOutPokemon_GetTokuseiDataId(arg0);
        if ((fightTrainer_GetEnemyTokuseiFlag(arg1, temp_r31) == 0) && ((temp_r29 == 0) || (temp_r30 == temp_r29))) {
            fightTrainer_SetEnemyTokuseiFlag(arg1, temp_r31, 1U);
            fightTrainer_SetEnemyStoreTokuseiData(arg1, temp_r31, temp_r28_2);
        }
    }
}

u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER *arg0, FightOutPokemon *arg1, u16 arg2) {
    s32 temp_r30;
    u16 var_r29;
    s32 temp_r24;
    s32 temp_r23;
    u8 var_r22;
    u8 var_r24;
    Pokemon *temp_r3;

    temp_r30 = (u8) (fightFloor_GetFightType(NULL));
    if (arg1 == NULL) {
        return 0U;
    }
    if (arg0 == NULL) {
        return 0U;
    }
    temp_r3 = fightPokemon_GetPokemonBuffPtr(fightOutPokemon_GetFightPokemonPtr(arg1));
    temp_r24 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r3), 0U));
    temp_r23 = (u8) (pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(temp_r3), 1U));
    fightOutPokemon_GetTokuseiDataId(arg1);
    var_r29 = 0;
    for (var_r22 = 0; var_r22 < 0x44U; var_r22++) {
        if (expect_tokusei_data_2[var_r22] == pokemon_GetPokemonDataId(temp_r3)) {
            var_r29 = temp_r23;
            break;
        }
    }
    if ((u16) var_r29 == 0) {
        var_r29 = temp_r24;
    }
    for (var_r24 = 0; var_r24 < 8U; var_r24++) {
        if (expect_tokusei_data_0[var_r24] == pokemon_GetPokemonDataId(temp_r3)) {
            var_r29 = 0;
            break;
        }
    }
    if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1, arg2) == 1) {
        return 2U;
    }
    if ((fightTrainerIsAllyFightTargetPtr(arg0, arg1, temp_r30) == 0) && ((u16) var_r29 == arg2)) {
        return 1U;
    }
    return 0U;
}

void fightAi_DereteExpectWaza(FightOutPokemon *arg0, FIGHT_TRAINER *arg1, u16 arg2) {
    s32 temp_r31;
    u8 var_r30;
    u8 var_r30_2;
    u8 temp_r29;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_r29 = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(arg0));
        for (var_r30 = 0; var_r30 < 8U; var_r30++) {
            if (arg2 == fightTrainer_GetEnemyExpectWazaData(arg1, temp_r29, var_r30)) {
                fightTrainer_SetEnemyExpectWazaData(arg1, temp_r29, var_r30, 0U);
            }
        }
        for (var_r30_2 = 0; var_r30_2 < 7U; var_r30_2++) {
            if (fightTrainer_GetEnemyExpectWazaData(arg1, temp_r29, var_r30_2) == 0) {
                temp_r31 = var_r30_2 + 1;
                fightTrainer_SetEnemyExpectWazaData(arg1, temp_r29, var_r30_2, fightTrainer_GetEnemyExpectWazaData(arg1, temp_r29, temp_r31));
                fightTrainer_SetEnemyExpectWazaData(arg1, temp_r29, temp_r31, 0U);
            }
        }
    }
}

void fightAi_AddStoreWaza(FightOutPokemon *arg0, FIGHT_TRAINER *arg1, u16 arg2) {
    u8 var_r31;
    u8 var_r30;
    u8 temp_r29;
    u8 temp_r4;

    if ((arg0 != NULL) && (arg1 != NULL)) {
        temp_r29 = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(arg0));
        for (var_r30 = 0; var_r30 < 4U; var_r30++) {
            if (arg2 == fightTrainer_GetEnemyStoreWazaData(arg1, temp_r29, var_r30)) {
                break;
            }
            if (fightTrainer_GetEnemyStoreWazaData(arg1, temp_r29, var_r30) == 0) {
                fightTrainer_SetEnemyStoreWazaData(arg1, temp_r29, var_r30, arg2);
                temp_r4 = fightTrainer_GetEnemyStoreWazaNum(arg1, temp_r29);
                fightTrainer_SetEnemyStoreWazaNum(arg1, temp_r29, (u8) (temp_r4 + 1));
                break;
            }
        }
        if (fightTrainer_GetEnemyStoreWazaNum(arg1, temp_r29) >= 4U) {
            for (var_r31 = 0; var_r31 < 8U; var_r31++) {
                fightTrainer_SetEnemyExpectWazaData(arg1, temp_r29, var_r31, 0U);
            }
        }
    }
}

u8 fightAi_GetEnemyWazaAndFlag(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 *arg2, u8 arg3) {
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    s32 temp_r3;
    s32 temp_cr0_lt;

    if (arg1 == NULL) {
        return 0U;
    }
    if (arg2 == NULL) {
        return 0U;
    }
    temp_r4_2 = (u8) (fightPokemon_GetEntryId(arg1));
    temp_cr0_lt = arg3 < 4U;
    if (temp_cr0_lt != 0) {
        *arg2 = fightTrainer_GetEnemyStoreWazaData(arg0, temp_r4_2, arg3);
        temp_r4_3 = (u16) (*arg2);
        if (temp_r4_3 == 0) {
            return 0U;
        }
        temp_r3 = 0x176 - temp_r4_3;
        return temp_r4_3 <= 0x176U ? 2 : 0;
    }
    if ((temp_cr0_lt == 0) && (arg3 < 0xCU)) {
        *arg2 = fightTrainer_GetEnemyExpectWazaData(arg0, temp_r4_2, (u8) (arg3 - 4));
        temp_r4 = (u16) (*arg2);
        if (temp_r4 == 0) {
            return 0U;
        }
        return temp_r4 <= 0x176U;
    }
    return 0U;
}

u8 fightAi_GetWazaHaveFlag(FIGHT_TRAINER *arg0, FightPokemon *arg1, u16 arg2) {
    u8 temp_r30;
    Pokemon *temp_r28;
    u8 var_r29;
    u32 temp_r0;

    if (arg0 == NULL) {
        return 0U;
    }
    if (arg1 == NULL) {
        return 0U;
    }
    if (arg2 == 0) {
        return 0U;
    }
    temp_r30 = fightPokemon_GetEntryId(arg1);
    temp_r28 = fightPokemon_GetPokemonBuffPtr(arg1);
    if (fightTrainerIsAllyFightTargetPtr(arg0, arg1, (temp_r0 = fightFloorGetStatus(0, 0, 0x14, 0), (u16) temp_r0)) == 0) {
        for (var_r29 = 0; var_r29 < 4U; var_r29++) {
            if (arg2 == fightTrainer_GetEnemyStoreWazaData(arg0, temp_r30, var_r29)) {
                return 2U;
            }
        }
        for (var_r29 = 0; var_r29 < 8U; var_r29++) {
            if (arg2 == fightTrainer_GetEnemyExpectWazaData(arg0, temp_r30, var_r29)) {
                return 1U;
            }
        }
        return 0U;
    }
    for (var_r29 = 0; var_r29 < 4U; var_r29++) {
        if (pokemonWazaCheckValid(temp_r28, var_r29) != 0 && arg2 == pokemon_GetPokemonWazaDataId(temp_r28, var_r29)) {
            return 2U;
        }
    }
    return 0U;
}

FightOutPokemon **fightAi_JudgeMoveFightOutPokemon(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 *arg2) {
    u8 var_r6;
    FightOutPokemon *temp_r4;
    s32 temp_r4_2;
    FightOutPokemon *temp_r3;
    s32 temp_r31;
    s32 temp_r30;
    u8 var_r29;

    var_r29 = 0;
    temp_r30 = (u16) (*arg2);
loop_14:
    while ((s32) var_r29 < (s32) temp_r30) {
        temp_r31 = (var_r29 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg1 + temp_r31);
        if (temp_r4 != NULL) {
            if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 0x12U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r31), 0x22U) == 1)) {
                *(FightOutPokemon **)((u8 *)arg1 + temp_r31) = 0;
                *arg2 -= 1;
            }
            if ((fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r31), 8U) == 1) || (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r31), 7U) == 1)) {
                *(FightOutPokemon **)((u8 *)arg1 + temp_r31) = 0;
                *arg2 -= 1;
            }
            if (fightFloorGetFightOutPokemonPtrToFightTrainerPtr(NULL, *(FightOutPokemon **)((u8 *)arg1 + temp_r31)) != arg0) {
                *(FightOutPokemon **)((u8 *)arg1 + temp_r31) = 0;
                *arg2 -= 1;
            }
            if ((fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r31), 0x36U) == 2) && (fightOutPokemon_GetNamakeFlag(*(FightOutPokemon **)((u8 *)arg1 + temp_r31)) == 1)) {
                *(FightOutPokemon **)((u8 *)arg1 + temp_r31) = 0;
                *arg2 -= 1;
            }
        }
        var_r29 += 1;
    }
    for (var_r6 = 0; var_r6 < temp_r30; var_r6++) {
        temp_r4_2 = (u32) var_r6 * 4 & 0x3FC;
        if (((u32) *(FightOutPokemon **)((u8 *)arg1 + temp_r4_2) == 0U) && ((s32) (var_r6 + 1) < (s32) temp_r30)) {
            temp_r3 = arg1[var_r6 + 1];
            if (temp_r3 != 0U) {
                *(FightOutPokemon **)((u8 *)arg1 + temp_r4_2) = temp_r3;
                arg1[var_r6 + 1] = 0;
            }
        }
    }
    return arg1;
}

void fightTrainerAiSelectFightAction(FIGHT_TRAINER *arg0, s32 arg1) {
    FightOutPokemon *spC[8];
    s32 temp_r31;
    u8 var_r26;
    u8 var_r26_2;
    u8 var_r26_3;
    u8 var_r26_4;
    u8 var_r25;
    u8 var_r25_2;
    u8 var_r25_3;
    u8 var_r25_4;
    u8 var_r25_5;
    u8 var_r5;
    u8 var_r5_2;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r3_3;
    FightOutPokemon *temp_r3_4;
    FightOutPokemon *temp_r3_5;
    FightOutPokemon *temp_r3_6;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    u16 sp8;

    fightTrainerAiSetEnemyPokemon(arg0);
    fightTrainerAiSetAllyPokemon(arg0);
    temp_r31 = (u8) (fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(arg1)));
    var_r26 = 0;
loop_5:
    while ((s32) var_r26 < (s32) temp_r31) {
        temp_r3 = fightTrainerGetValidFightOutPokemonPtr(arg0, var_r26);
        if ((temp_r3 != NULL) && (fightOutPokemonCheckFightActionSelect(temp_r3, 1U) != 0)) {
            fightOutPokemonInitFightActionBuff(temp_r3);
        }
        var_r26 += 1;
    }
    fightAi_FixedAct(arg0, arg1);
    sp8 = fightFloorGetFightTrainerFightOutPokemonPtrAry(NULL, arg0, spC, 1U, 1U);
    fightAi_CreateAllWazaValid(arg0, fightAi_JudgeMoveFightOutPokemon(arg0, spC, &sp8), (u8) sp8);
    var_r25 = 0;
loop_10:
    while ((s32) var_r25 < (s32) temp_r31) {
        temp_r3_2 = fightTrainerGetNoActionFightOutPokemonPtr(arg0, var_r25);
        if (temp_r3_2 != NULL) {
            fightAiCombo_ActContinue(arg0, temp_r3_2, arg1);
        }
        var_r25 += 1;
    }
    fightAi_CheckDoFightActionStroke(arg0);
    if (fightTrainerAiCheckDoFightActionIrekae(arg0) == 1) {
        var_r25_2 = 0;
loop_17:
        while ((s32) var_r25_2 < (s32) temp_r31) {
            temp_r3_3 = fightTrainerGetNoActionFightOutPokemonPtr(arg0, var_r25_2);
            if ((temp_r3_3 != NULL) && (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(NULL, temp_r3_3, 0U) == 0)) {
                fightTrainerAiSelectFightActionIrekae(arg0, temp_r3_3, arg1);
            }
            var_r25_2 += 1;
        }
    }
    if ((fightFloor_GetFightKindUseItemFlag(NULL) == 1) && (fightTrainerAiCheckDoFightActionItem(arg0) == 1)) {
        var_r25_3 = 0;
loop_24:
        while ((s32) var_r25_3 < (s32) temp_r31) {
            temp_r3_4 = fightTrainerGetNoActionFightOutPokemonPtr(arg0, var_r25_3);
            if (temp_r3_4 != NULL) {
                fightTrainerAiSelectFightActionItem(arg0, temp_r3_4, arg1);
            }
            var_r25_3 += 1;
        }
    }
    var_r5 = 0;
loop_27:
    while (var_r5 < 8U) {
        temp_r0 = (var_r5 * 4) & 0x3FC;
        var_r5 += 1;
        *(FightOutPokemon **)((u8 *)spC + temp_r0) = 0;
    }
    var_r26_2 = 0;
    var_r25_4 = 0;
loop_32:
    while ((s32) var_r25_4 < (s32) temp_r31) {
        temp_r3_5 = fightTrainerGetNoActionFightOutPokemonPtr(arg0, var_r25_4);
        if (temp_r3_5 != NULL) {
            temp_r0_2 = (var_r26_2 * 4) & 0x3FC;
            var_r26_2 += 1;
            *(FightOutPokemon **)((u8 *)spC + temp_r0_2) = temp_r3_5;
        }
        var_r25_4 += 1;
    }
    if (var_r26_2 != 0) {
        fightAiCombo_Act(arg0, spC, var_r26_2, arg1);
    }
    var_r5_2 = 0;
loop_37:
    while (var_r5_2 < 8U) {
        temp_r0_3 = (var_r5_2 * 4) & 0x3FC;
        var_r5_2 += 1;
        *(FightOutPokemon **)((u8 *)spC + temp_r0_3) = 0;
    }
    var_r26_3 = 0;
    var_r25_5 = 0;
loop_43:
    while ((s32) var_r25_5 < (s32) temp_r31) {
        temp_r3_6 = fightTrainerGetNoActionFightOutPokemonPtr(arg0, var_r25_5);
        if ((temp_r3_6 != NULL) && (fightOutPokemonCheckFightActionWazaSelect(temp_r3_6, 1U) == 0)) {
            temp_r0_4 = (var_r26_3 * 4) & 0x3FC;
            var_r26_3 += 1;
            *(FightOutPokemon **)((u8 *)spC + temp_r0_4) = temp_r3_6;
        }
        var_r25_5 += 1;
    }
    if (var_r26_3 != 0) {
        fightFloorSortFightOutPokemonPtrArySub(NULL, spC, 8U, 0U);
        var_r26_4 = 0;
loop_49:
        while (var_r26_4 < var_r26_3) {
            temp_r4 = *(FightOutPokemon **)((u8 *)spC + ((var_r26_4 * 4) & 0x3FC));
            if (temp_r4 != NULL) {
                fightTrainerAiSelectFightActionWaza(arg0, temp_r4, arg1);
            }
            var_r26_4 += 1;
        }
    }
}
s32 fightAi_CopyAllWazaValidTable(AiWazaCandidate *dst, AiWazaCandidate *src) {
    u8 i;
    if (!dst || !src) return 0;
    for (i = 0; i < 2; i++) {
        u8 j;
        for (j = 0; j < 2; j++) {
            dst->attackers[i] = src->attackers[i];
            dst->defenders[i] = src->defenders[i];
            dst->moves[i] = src->moves[i];
            dst->slots[i] = src->slots[i];
            dst->eligible[i] = src->eligible[i];
            dst->probability[i] = src->probability[i];
            dst->combination = src->combination;
            dst->damage[i][j] = src->damage[i][j];
            dst->result[j] = src->result[j];
        }
    }
    return 1;
}

void fightAi_InitAllWazaValidSub(AiWazaCandidate *entry) {
    if (entry) {
        u8 i;
        for (i = 0; i < 2; i++) {
            u8 j;
            for (j = 0; j < 2; j++) {
                entry->attackers[i] = 0;
                entry->defenders[i] = 0;
                entry->moves[i] = 0;
                entry->slots[i] = 0;
                entry->eligible[i] = 0;
                entry->probability[i] = 0;
                entry->combination = 0;
                entry->damage[i][j] = 0;
                entry->result[j] = 0;
            }
        }
    }
}

void fightAi_AllWazaValid_DelListFromSpeed(FIGHT_TRAINER *trainer, AiWazaCandidate *list, u8 *count, u16 wazaId, u8 faster) {
    AiWazaCandidate *entry;
    s8 k;
    s8 i;
    s8 j;
    u8 remove;
    u8 abiCnt[2];
    s32 nimble[2];
    s32 speed[2];
    for (i = 0; i < *count; i++) {
        remove = 0;
        entry = &list[i];
        for (j = 0; j < 2; j++) {
            nimble[j] = (u16) pokemon_GetNimbleness(fightOutPokemonGetPokemonPtr(entry->attackers[j]));
            abiCnt[j] = fightTrainerAiGetFightOutPokemonAbiCntSubayasa(trainer, entry->attackers[j]);
            if (abiCnt[j] != 6) {
                speed[j] = fightAbicntDoKakeWaru(abiCnt[j], nimble[j]);
            } else {
                speed[j] = nimble[j];
            }
        }
        if (faster == 1) {
            if (wazaId == entry->moves[0] && speed[0] < speed[1]) {
                remove = 1;
            } else if (wazaId == entry->moves[1] && speed[0] > speed[1]) {
                remove = 1;
            }
        } else if (wazaId == entry->moves[0] && speed[0] > speed[1]) {
            remove = 1;
        } else if (wazaId == entry->moves[1] && speed[0] < speed[1]) {
            remove = 1;
        }
        if (remove == 1) {
            fightAi_InitAllWazaValidSub(entry);
            k = 0;
            i -= 1;
            *count -= 1;
            while (k < *count) {
                list[k] = list[k + 1];
                fightAi_CopyAllWazaValidTable(&list[k], &list[k + 1]);
                k += 1;
            }
        }
    }
    for (k = *count; k < 0x40; k++) {
        fightAi_InitAllWazaValidSub(&list[k]);
    }
}

void fightAi_AllWazaValid_AddComboList(FIGHT_TRAINER *trainer, AiWazaCandidate *out, u8 *count, u8 kind0, s32 val0, u8 kind1, s32 val1) {
    s32 type;
    u8 kinds[2];
    s32 vals[2];
    u8 hitA;
    u8 hitB;
    u16 *move0;
    u16 *move1;
    FightOutPokemon **atk1;
    AiWazaCandidate *entry;
    u8 idx;
    u8 side;
    u8 n;
    kinds[0] = kind0;
    kinds[1] = kind1;
    vals[0] = val0;
    vals[1] = val1;
    n = *count;
    for (idx = 0; idx < 0x40; idx++) {
        hitA = 0;
        hitB = hitA;
        entry = &ai_allwaza_valid_tbl[idx];
        move0 = &entry->moves[0];
        move1 = &entry->moves[1];
        atk1 = &entry->attackers[1];
        for (side = 0; side < 2; side++) {
            switch (kinds[side]) {
            case 0:
                hitA += 1;
                hitB += 1;
                break;
            case 1:
                if (vals[side] != 0) {
                    if (*move0 == vals[side]) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (*move1 == vals[side]) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            case 2: {
                type = vals[side];
                if (type != 0) {
                    if (wazaIsWazaTypeId(*move0, type) == 1) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (wazaIsWazaTypeId(*move1, type) == 1) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            }
            case 3:
                if (vals[side] != -1) {
                    if (vals[side] == fightTrainerAiGetWazaZokuseiDataId(trainer, *move0, entry->attackers[0])) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (vals[side] == fightTrainerAiGetWazaZokuseiDataId(trainer, *move1, *atk1)) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            }
        }
        if (hitA == 2 || hitB == 2) {
            fightAi_CopyAllWazaValidTable(&out[n], entry);
            n += 1;
        }
    }
    *count = n;
}

void fightAi_AllWazaValid_DelComboList(FIGHT_TRAINER *trainer, AiWazaCandidate *list, u8 *count, u8 kind0, s32 val0, u8 kind1, s32 val1, u8 mode) {
    u8 kinds[2];
    s32 vals[2];
    AiWazaCandidate tmp[64];
    u8 hitA;
    u8 hitB;
    FightOutPokemon **atk1;
    AiWazaCandidate *cand;
    AiWazaCandidate *tblEntry;
    u8 idx;
    u8 side;
    u8 n;
    u8 k;
    kinds[0] = kind0;
    kinds[1] = kind1;
    n = 0;
    idx = 0;
    vals[0] = val0;
    vals[1] = val1;
    for (; idx < *count; idx++) {
        hitB = hitA = 0;
        fightAi_InitAllWazaValidSub(&tmp[idx]);
        tblEntry = &ai_allwaza_valid_tbl[idx];
        cand = &list[idx];
        atk1 = &tblEntry->attackers[1];
        for (side = 0; side < 2; side++) {
            switch (kinds[side]) {
            case 0:
                hitA += 1;
                hitB += 1;
                break;
            case 1:
                if (vals[side] != 0) {
                    if (cand->moves[0] == vals[side]) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (cand->moves[1] == vals[side]) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            case 2: {
                if (vals[side] != 0) {
                    if (wazaIsWazaTypeId(cand->moves[0], vals[side]) == 1) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (wazaIsWazaTypeId(cand->moves[1], vals[side]) == 1) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            }
            case 3:
                if (vals[side] != -1) {
                    if (vals[side] == fightTrainerAiGetWazaZokuseiDataId(trainer, cand->moves[0], tblEntry->attackers[0])) {
                        if (side == 0) {
                            hitA = hitA + 1;
                        }
                        if (side == 1) {
                            hitB += 1;
                        }
                    }
                    if (vals[side] == fightTrainerAiGetWazaZokuseiDataId(trainer, cand->moves[1], *atk1)) {
                        if (side == 0) {
                            hitB = hitB + 1;
                        }
                        if (side == 1) {
                            hitA += 1;
                        }
                    }
                }
                break;
            }
        }
        if (hitA == 2 || hitB == 2) {
            if (mode == 1) {
                fightAi_CopyAllWazaValidTable(&tmp[n], cand);
                n += 1;
            }
        } else if (mode == 0) {
            fightAi_CopyAllWazaValidTable(&tmp[n], cand);
            n += 1;
        }
    }
    *count = n;
    for (k = 0; k < 0x40; k++) {
        fightAi_CopyAllWazaValidTable(&list[k], &tmp[k]);
    }
}

void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER *trainer, AiWazaCandidate *entry) {
    u8 fightType = fightFloor_GetFightType(0);
    u8 i;
    for (i = 0; i < 2; i++) {
        FightOutPokemon *attacker = entry->attackers[i];
        u16 move = entry->moves[i];
        u8 slot = entry->slots[i];
        FightOutPokemon *defender = entry->defenders[i];
        if (attacker && defender && fightActionCheckValid(fightOutPokemon_GetFightActionBuffPtr(attacker)) != 1) {
            FightOutPokemon *selected = fightSeqSelectDefensePokemonPtr(attacker, move, fightType, (void *)&fightTrainerAiWazaSelectDefensePokemon, 1, 0, -1);
            if (selected) defender = selected;
            if (defender) {
                u32 target = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(defender, fightType);
                fightOutPokemonCreateFightActionAttackWaza(attacker, 0, 0x13, 0, fight_action_data_waza, move, target, (s8)slot, 0);
            }
        }
    }
}

u8 _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(u16 move) {
    u16 ignored[3] = {0x11d, 0x78, 0x99};
    u8 i;
    for (i = 0; i < 3; i++) {
        if (move == ignored[i]) return 1;
    }
    return 0;
}

u8 fightAi_GetWazaCombValue(FightOutPokemon **pokemon, u16 *damage, u8 *probability) {
    u16 total[2] = {0, 0};
    f32 fraction[2] = {0.0f, 0.0f};
    u16 average[2] = {0, 0};
    Pokemon *records[2];
    u8 defeated = 0;
    u8 i;
    for (i = 0; i < 2; i++) {
        if (pokemon[i]) {
            total[i] = damage[i] + damage[i + 2];
            records[i] = fightOutPokemonGetPokemonPtr(pokemon[i]);
            if (records[i]) {
                f32 hp = pokemon_GetHp(records[i]);
                if (hp != 0.0f) {
                    fraction[i] = total[i] / hp;
                    if (fraction[i] > 1.0f) {
                        fraction[i] = 1.0f;
                        defeated++;
                    }
                    average[i] = 0;
                    if (damage[i] != 0 && damage[i + 2] != 0)
                        average[i] = (probability[0] + probability[1]) / 2;
                    else if (damage[i] != 0)
                        average[i] = probability[0];
                    else if (damage[i + 2] != 0)
                        average[i] = probability[1];
                }
            }
        }
    }
    switch (defeated) {
    case 2: return (probability[0] + probability[1]) / 2;
    case 1: return (s32)(0.5 * (f64)fraction[0] * (f64)average[0] + 0.5 * (f64)fraction[1] * (f64)average[1]);
    default: return (s32)(0.25 * (f64)fraction[0] * (f64)average[0] + 0.25 * (f64)fraction[1] * (f64)average[1]);
    }
}

s16 fightAi_ThreatEnemyValue(FIGHT_TRAINER *trainer,FightOutPokemon *attacker,FightOutPokemon *defender,s16 weather,u16 mode,s8 canHit,s8 canKnockout) {
    FightPokemon *allyParty[24],*enemyParty[24];
    FightOutPokemon *allies[8],*enemies[8];
    u16 move;
    s16 value=0;
    u8 highestLevel=0;
    u8 trainers=fightFloor_GetFightTypeTrainerNum(0);
    u8 entries=fightFloor_GetFightTypeEntryPokemonNum(0);
    u8 outCount=fightFloor_GetFightTypeFightoutPokemonNum(0);
    if(!attacker)return 0;
    if(!defender)return 0;
    FightPokemon *attackFight=fightOutPokemon_GetFightPokemonPtr(attacker);
    FightPokemon *defendFight=fightOutPokemon_GetFightPokemonPtr(defender);
    Pokemon *attackPokemon=fightPokemon_GetPokemonBuffPtr(attackFight);
    Pokemon *defendPokemon=fightPokemon_GetPokemonBuffPtr(defendFight);
    fightFloorGetFightPokemonPtrToFightTrainerPtr(0,attackFight);
    FIGHT_TRAINER *enemyTrainer=fightFloorGetFightPokemonPtrToFightTrainerPtr(0,defendFight);
    u32 level=pokemon_GetLevel(defendPokemon);
    void *side=fightTargetGetPtrAsNowFightType(2,(FightOutPokemon*)trainer);
    u32 attackSpeed=pokemon_GetNimbleness(attackPokemon);
    u32 defendSpeed=pokemon_GetNimbleness(defendPokemon);
    u16 allyCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,allies,1,1);
    fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0,trainer,allyParty,1,1);
    fightFloorGetFightTrainerFightPokemonPtrAry(0,trainer,enemyParty,0,1);
    u16 hp=fightTrainerAiGetFightOutPokemonNowHp(trainer,defender);
    for(u8 i=0;i<4;i++){
        move=pokemon_GetPokemonWazaDataId(attackPokemon,i);
        if(move!=0x176&&move!=0&&move!=0x163){
            u8 hit=fightTrainerAiWazaDoWazaHitFunc(trainer,attacker,move,defender);
            if(hit==1&&canHit==-1)canHit=1;
            if(fightTrainerAiIsWazaTypeId(trainer,move,1)!=0){
                fightTrainerAiWazaDoWazaDamageFunc(trainer,attacker,move,defender,1);
                if((s32)hp<fightTrainerAiWazaDoWazaDamageFunc(trainer,attacker,move,defender,0)&&hit==1&&canKnockout==-1)canKnockout=1;
            }
        }
    }
    if(weather==-1)weather=fightFloorGetNowTenkouDataId(0,0);
    for(u8 i=0;i<allyCount;i++){
        if(highestLevel<pokemon_GetLevel(fightOutPokemonGetPokemonPtr(allies[i])))highestLevel=pokemon_GetLevel(fightOutPokemonGetPokemonPtr(allies[i]));
    }
    fightSideGetHikaeFightPokemonNum(side,trainers,entries,outCount);
    for(u8 i=0;i<8;i++){
        u8 flag=fightAi_GetEnemyWazaAndFlag(trainer,defendFight,&move,i);
        if(move&&fightAi_AppointWazaKoukaFlag(attacker,defender,fightAi_GetWazaZokuseiData_ThinkWeatherBall(move,(u16)weather))==0x41){
            if(flag==2)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x288);
            if(flag==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x289);
        }
    }
    for(u8 i=0;i<4;i++){
        move=pokemon_GetPokemonWazaDataId(attackPokemon,i);
        if(move&&fightAi_AppointWazaKoukaFlag(attacker,defender,fightAi_GetWazaZokuseiData_ThinkWeatherBall(move,(u16)weather))==0x41)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x28A);
    }
    value=value+(s16)(((u8)level-highestLevel)*fightTrainerAiValueAddsubDB_GetValue(0x28B));
    for(u8 i=3;i<12;i++){
        fightAi_GetEnemyWazaAndFlag(trainer,defendFight,&move,i);
        if(move==0x78||move==0x99)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x28C);
        if(move==0x59)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x28E);
    }
    for(u8 i=0;i<12;i++){
        u8 flag=fightAi_GetEnemyWazaAndFlag(trainer,defendFight,&move,i);
        if(fightAi_DamageKizetsuFlag(allies,fightTrainerAiWazaDoWazaDamageFunc(trainer,defender,move,attacker,0))==1){
            if(flag==2)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x28F);
            if(flag==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x290);
        }
    }
    if((u16)attackSpeed<(u16)defendSpeed)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x291);
    u16 abilities=fightTrainerAiGetFightOutPokemonAllAbiCnt(enemyTrainer,defender);
    s16 addition=(abilities-0x2A)*fightTrainerAiValueAddsubDB_GetValue(0x292);
    if(addition>0)value+=addition;
    if(fightAi_PokemonTokuseiMoukaFlag(defender)==2)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x293);
    if(fightAi_PokemonTokuseiMoukaFlag(defender)==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x294);
    if(canHit==0)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x295);
    if(canKnockout==1)value=fightTrainerAiAddValueByAddsubDataId(value,trainer,0x296);
    return value;
}

s32 _fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(FIGHT_TRAINER *trainer,Hero *hero,Pokemon **selected,u16 selectedCount,u8 mode,Pokemon **out) {
    AiFightPokemonRecord first,second;
    fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    for(u16 i=0;i<6;i++)out[i]=0;
    FightPokemon *firstFight=fightTrainer_GetFightPokemonPtr(trainer,0);
    if(!firstFight)return 0;
    FightPokemon *secondFight=fightTrainer_GetFightPokemonPtr(trainer,1);
    if(!secondFight)return 0;
    aiCopyFightPokemon(first,*(AiFightPokemonRecord*)firstFight);
    aiCopyFightPokemon(second,*(AiFightPokemonRecord*)secondFight);
    for(u16 i=0;i<selectedCount;i++){}
    s32 count=0;
    for(u16 i=0;i<6;i++){
        Pokemon *candidate=heroGetStatus(hero,3,i);
        if(candidate&&pokemonCheckValid(candidate)!=0&&pokemonCheckFightOut(candidate)!=0){
            u16 j;
            for(j=0;j<selectedCount;j++)if(selected[j]&&selected[j]==candidate)break;
            if(j>=selectedCount){
                fightPokemonCreate(trainer,firstFight,candidate,fightFloorGetFightPokemonEntryCntInc(0));
                switch(mode){
                case 1:if(fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight)==2)out[count++]=candidate;break;
                default:case 0:out[count++]=candidate;break;
                case 2:if(fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight)==3)out[count++]=candidate;break;
                case 3:if(fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight)!=2&&fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight)!=3)out[count++]=candidate;break;
                }
            }
        }
    }
    aiCopyFightPokemon(*(AiFightPokemonRecord*)firstFight,first);
    aiCopyFightPokemon(*(AiFightPokemonRecord*)secondFight,second);
    return count;
}

void fightTrainerAiSortFirstSelectPokemonAry(FIGHT_TRAINER *trainer,Hero *hero,Pokemon **out,u16 count,u16 aceCount) {
    AiFightPokemonRecord first,second;
    Pokemon *candidates[6];
    u8 flags[6];
    s32 ai=fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer));
    u8 hasCombo=0;
    u8 comboCount=0;
    FightPokemon *firstFight=fightTrainer_GetFightPokemonPtr(trainer,0);
    if(firstFight){
        FightPokemon *secondFight=fightTrainer_GetFightPokemonPtr(trainer,1);
        if(secondFight){
            aiCopyFightPokemon(first,*(AiFightPokemonRecord*)firstFight);
            aiCopyFightPokemon(second,*(AiFightPokemonRecord*)secondFight);
            for(u16 i=0;i<count;i++)out[i]=0;
            for(u16 i=0;i<6;i++)flags[i]=0;
            u16 selected=0;
            u16 limit=1;
            if(fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(ai)!=1)limit=aceCount;
            void *deck=getDeckTrainerObj__11DeckTrainerFUl(fightTrainer_GetFightTrainerDataId(trainer));
            for(u16 i=0;i<4;i++)if(getComboID__11DeckTrainerCFUc(deck,(u8)i)!=0){hasCombo=1;break;}
            if(fightTrainerAiDB_GetPokemonSelectRandomFlag(ai)==1){
                for(;selected<count;selected++){
                    u16 available=_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,0,candidates);
                    if(!available)break;
                    out[selected]=candidates[HSD_Rand()%available];
                    fightPokemonCreate(trainer,firstFight,out[selected],fightFloorGetFightPokemonEntryCntInc(0));
                    flags[selected]=fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight);
                }
            }else{
                if(hasCombo==1){comboCount=fightTrainerAi_SelComboPartner(candidates,out,_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,0,candidates),trainer);selected=comboCount;}
                for(u16 i=0;i<limit;i++){
                    u16 available=_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,1,candidates);
                    if(!available)break;
                    flags[selected]=2;out[selected++]=candidates[HSD_Rand()%available];
                }
                for(u16 i=0;i<limit;i++){
                    u16 available=_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,2,candidates);
                    if(!available)break;
                    flags[selected]=3;out[selected++]=candidates[HSD_Rand()%available];
                }
                for(;selected<count;selected++){
                    u16 available=_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,3,candidates);
                    if(!available)break;
                    out[selected]=candidates[HSD_Rand()%available];
                    fightPokemonCreate(trainer,firstFight,out[selected],fightFloorGetFightPokemonEntryCntInc(0));
                    flags[selected]=fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight);
                }
                for(;selected<count;selected++){
                    u16 available=_fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(trainer,hero,out,(u8)count,0,candidates);
                    if(!available)break;
                    out[selected]=candidates[HSD_Rand()%available];
                    fightPokemonCreate(trainer,firstFight,out[selected],fightFloorGetFightPokemonEntryCntInc(0));
                    flags[selected]=fightTrainerAiGetFightPokemonKeyPlayerFlag(trainer,firstFight);
                    if(flags[selected]==2)flags[selected]=3;
                }
            }
            if(fightTrainerAiDB_GetPokemonSelectRandomFlag(ai)!=1){
                if(fightTrainerAiDB_GetPokemonDataOrderOutFlag(ai)==1){
                    for(u16 i=0;i<count;i++)if(out[i]){
                        for(u16 j=i+1;j<count;j++)if(out[j]){
                            u16 data=pokemon_GetFightTrainerPokemonDataId(out[i]);
                            if(data>pokemon_GetFightTrainerPokemonDataId(out[j])){Pokemon *old=out[i];out[i]=out[j];u8 flag=flags[i];flags[i]=flags[j];out[j]=old;flags[j]=flag;}
                        }
                    }
                }else{
                    for(u8 i=comboCount;i<count;i++)if(out[i]){
                        for(u16 j=i+1;j<count;j++)if(out[j]&&flags[i]!=2&&flags[j]==2){Pokemon *old=out[i];u8 flag=flags[i];flags[i]=flags[j];out[i]=out[j];out[j]=old;flags[j]=flag;}
                    }
                }
            }
            aiCopyFightPokemon(*(AiFightPokemonRecord*)firstFight,first);
            aiCopyFightPokemon(*(AiFightPokemonRecord*)secondFight,second);
        }
    }
}

void fightAi_CreateAllWazaValid(FIGHT_TRAINER *trainer,FightOutPokemon **attackers,u8 attackerCount) {
    u16 damage[2][4][2];
    s16 slots[2][4];u16 moves[2][4];
    FightOutPokemon *enemies[2],*defense[2];
    s16 firstSlots[4],secondSlots[4];u16 firstMoves[4],secondMoves[4];
    u8 eligible[2][4];
    u16 totals[2][2],selectedMoves[2];
    u8 probability[2],result[2];
    if(trainer){
        fightAi_InitAllWazaValid();
        for(u8 i=0;i<2;i++){
            for(u8 j=0;j<4;j++){
                for(u8 k=0;k<2;k++){damage[i][j][k]=0;totals[i][k]=0;result[k]=0;}
                eligible[i][j]=0;slots[i][j]=0;moves[i][j]=0;
            }
            enemies[i]=0;probability[i]=0;selectedMoves[i]=0;defense[i]=0;
        }
        if(attackers[0])fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,attackers[0],firstMoves,firstSlots,1);
        if(attackers[1])fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer,attackers[1],secondMoves,secondSlots,1);
        u16 enemyCount=fightFloorGetFightTrainerFightOutPokemonPtrAry(0,trainer,enemies,0,1);
        for(u8 i=0;i<2;i++)if(attackers[i]){
            for(u8 j=0;j<4;j++){
                if(i==0){moves[i][j]=firstMoves[j];slots[i][j]=firstSlots[j];}
                else{moves[i][j]=secondMoves[j];slots[i][j]=secondSlots[j];}
                if(moves[i][j]){
                    probability[i]=fightAi_WazaSuccessProbability(trainer,attackers[i],enemies,moves[i][j]);
                    for(u8 k=0;k<2;k++)if(enemies[k])damage[i][j][k]=fightTrainerAiWazaDoWazaDamageFunc(trainer,attackers[i],moves[i][j],enemies[k],0);
                }
            }
        }
        ai_allwaza_valid_work.count=attackerCount;
        AiWazaCandidate *table=ai_allwaza_valid_tbl;
        for(u8 first=0;first<4;first++){
        u8 second;u8 firstTarget;
        for(firstTarget=0;firstTarget<2;firstTarget++)for(second=0;second<4;second++)for(u8 secondTarget=0;secondTarget<2;secondTarget++){
            totals[0][1]=0;totals[0][0]=0;totals[1][1]=0;totals[1][0]=0;selectedMoves[0]=0;selectedMoves[1]=0;
            if(attackers[0]&&moves[0][first]){
                eligible[0][first]=fightAi_CreateAllWazaValid_GetDefense(moves[0][first],firstTarget);
                switch(eligible[0][first]){
                case 0:totals[0][0]+=damage[0][first][0];defense[0]=enemies[0];break;
                case 1:totals[0][1]+=damage[0][first][1];defense[0]=enemies[1];break;
                case 2:totals[0][0]+=damage[0][first][0];totals[0][1]+=damage[0][first][1];defense[0]=enemies[0];break;
                case 3:defense[0]=enemies[0];break;
                case 4:defense[0]=attackers[0];break;
                case 5:defense[0]=enemies[HSD_Rand()%enemyCount];break;
                }
                if(eligible[0][first]==2){
                    u8 hitFirst;
                    AiDirectHitFunction hit=wazaDB_GetFightTrainerAiWazaHitFuncPtr(moves[0][first]);
                    hitFirst=0;u8 hitSecond=hitFirst;
                    if(enemies[0]&&hit(trainer,attackers[0],moves[0][first],enemies[0])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[0],moves[0][first],enemies[0])==1)hitFirst=1;
                    if(enemies[1]&&hit(trainer,attackers[0],moves[0][first],enemies[1])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[0],moves[0][first],enemies[1])==1)hitSecond=1;
                    if(hitFirst==1||hitSecond==1)selectedMoves[0]=moves[0][first];else selectedMoves[0]=0;
                }else{
                    AiDirectHitFunction hit=wazaDB_GetFightTrainerAiWazaHitFuncPtr(moves[0][first]);
                    if(defense[0]&&hit(trainer,attackers[0],moves[0][first],defense[0])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[0],moves[0][first],defense[0])==1)selectedMoves[0]=moves[0][first];else selectedMoves[0]=0;
                }
            }
            if(attackers[1]&&moves[1][second]){
                eligible[1][second]=fightAi_CreateAllWazaValid_GetDefense(moves[1][second],secondTarget);
                switch(eligible[1][second]){
                case 0:totals[1][0]+=damage[1][second][0];defense[1]=enemies[0];break;
                case 1:totals[1][1]+=damage[1][second][1];defense[1]=enemies[1];break;
                case 3:defense[1]=enemies[0];break;
                case 4:defense[1]=attackers[1];break;
                case 2:totals[1][0]+=damage[1][second][0];totals[1][1]+=damage[1][second][1];defense[1]=enemies[1];break;
                case 5:defense[1]=enemies[HSD_Rand()%enemyCount];break;
                }
                if(eligible[1][second]==2){
                    u8 hitFirst;
                    AiDirectHitFunction hit=wazaDB_GetFightTrainerAiWazaHitFuncPtr(moves[1][second]);
                    hitFirst=0;u8 hitSecond=hitFirst;
                    if(enemies[0]&&hit(trainer,attackers[1],moves[1][second],enemies[0])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[1],moves[1][second],enemies[0])==1)hitFirst=1;
                    if(enemies[1]&&hit(trainer,attackers[1],moves[1][second],enemies[1])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[1],moves[1][second],enemies[1])==1)hitSecond=1;
                    if(hitFirst==1||hitSecond==1)selectedMoves[1]=moves[1][second];else selectedMoves[1]=0;
                }else{
                    AiDirectHitFunction hit=wazaDB_GetFightTrainerAiWazaHitFuncPtr(moves[1][second]);
                    if(defense[1]&&hit(trainer,attackers[1],moves[1][second],defense[1])==1&&fightTrainerAiWazaDoWazaHitFunc(trainer,attackers[1],moves[1][second],defense[1])==1)selectedMoves[1]=moves[1][second];else selectedMoves[1]=0;
                }
            }
            u8 combination=fightAi_GetWazaCombValue(enemies,&totals[0][0],probability);
            result[0]=fightAi_AttackResult(trainer,enemies[0],selectedMoves[0],selectedMoves[1],totals[0][0]+totals[1][0]);
            u8 secondResult=fightAi_AttackResult(trainer,enemies[1],selectedMoves[0],selectedMoves[1],totals[0][1]+totals[1][1]);
            s16 index=firstTarget*8+first*16+second*2+secondTarget;
            FightOutPokemon *firstAttacker=attackers[0];
            AiWazaCandidate *entry=&table[index];
            entry->attackers[0]=firstAttacker;entry->attackers[1]=attackers[1];entry->defenders[0]=defense[0];entry->defenders[1]=defense[1];
            entry->moves[0]=selectedMoves[0];entry->moves[1]=selectedMoves[1];entry->slots[0]=slots[0][first];entry->slots[1]=slots[1][second];
            entry->eligible[0]=eligible[0][first];entry->eligible[1]=eligible[1][second];entry->probability[0]=probability[0];entry->probability[1]=probability[1];entry->combination=combination;
            entry->damage[0][0]=totals[0][0];entry->damage[0][1]=totals[0][1];entry->damage[1][0]=totals[1][0];entry->damage[1][1]=totals[1][1];entry->result[0]=result[0];result[1]=secondResult;entry->result[1]=secondResult;
        }}
    }
}

void fightAi_CheckDoFightActionStroke(FIGHT_TRAINER *trainer){
    u8 bestScore=0;
    u8 fightType=fightFloor_GetFightType(0);
    u8 actionCount=0;
    if(trainer){
        u8 stroke=fightTrainerAiDB_GetStrokeValue(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(trainer)));
        if(stroke){
            AiWazaCandidate best;
            fightAi_InitAllWazaValidSub(&best);
            for(u8 i=0;i<63;i++){
                AiWazaCandidate *first=&ai_allwaza_valid_tbl[i];
                for(u8 j=i+1;j<64;j++){
                    AiWazaCandidate *second=&ai_allwaza_valid_tbl[j];
                    if(first->combination<second->combination){
                        fightAi_CopyAllWazaValidTable(&best,first);
                        fightAi_CopyAllWazaValidTable(first,second);
                        fightAi_CopyAllWazaValidTable(second,&best);
                    }
                }
            }
            fightAi_InitAllWazaValidSub(&best);
            for(u8 i=0;i<64;i++){
                u8 present=0,probability=0;
                AiWazaCandidate *entry=&ai_allwaza_valid_tbl[i];
                for(u8 j=0;j<2;j++)if(entry->attackers[j]){present++;probability+=entry->probability[j];}
                if(present==ai_allwaza_valid_work.count)probability=(s32)probability/(s32)ai_allwaza_valid_work.count;
                FightActionBuff *first=fightOutPokemon_GetFightActionBuffPtr(entry->attackers[0]);
                if(first){
                    FightActionBuff *second=fightOutPokemon_GetFightActionBuffPtr(entry->attackers[1]);
                    if(second && fightActionCheckValid(first)!=1 && fightActionCheckValid(second)!=1 && entry->result[0]==3 && entry->result[1]==3 && _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(entry->moves[0])==0 && _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(entry->moves[1])==0){
                        s32 total=probability+stroke;
                        if(total>=100 && bestScore<total){fightAi_CopyAllWazaValidTable(&best,entry);bestScore=total;}
                    }
                }
            }
            if(best.attackers[0] && best.moves[0] && best.moves[0]!=0x176 && best.moves[0]!=0x163){
                FightOutPokemon *target;
                switch(best.eligible[0]){
                case 0:target=fightTargetGetPtr(0xF,best.attackers[0],fightType);break;
                case 1:target=fightTargetGetPtr(0x10,best.attackers[0],fightType);break;
                default:target=fightTargetGetPtr(0xF,best.attackers[0],fightType);break;
                }
                u32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target,fightType);
                fightOutPokemonCreateFightActionAttackWaza(best.attackers[0],0,0x13,0,fight_action_data_waza,best.moves[0],relative,best.slots[0],0);
                actionCount++;
            }
            if(best.attackers[1] && best.moves[1] && best.moves[1]!=0x176 && best.moves[1]!=0x163){
                FightOutPokemon *target;
                switch(best.eligible[1]){
                case 0:target=fightTargetGetPtr(0xF,best.attackers[1],fightType);break;
                case 1:target=fightTargetGetPtr(0x10,best.attackers[1],fightType);break;
                default:target=fightTargetGetPtr(0xF,best.attackers[1],fightType);break;
                }
                u32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target,fightType);
                fightOutPokemonCreateFightActionAttackWaza(best.attackers[1],0,0x13,0,fight_action_data_waza,best.moves[1],relative,best.slots[1],0);
                actionCount++;
            }
            if(actionCount==0){
                fightAi_InitAllWazaValidSub(&best);
                for(u8 i=0;i<64;i++){
                    u8 present=0,probability=0;
                    AiWazaCandidate *entry=&ai_allwaza_valid_tbl[i];
                    for(u8 j=0;j<2;j++)if(entry->attackers[j]){present++;probability+=entry->probability[j];}
                    if(present==ai_allwaza_valid_work.count)probability=(s32)probability/(s32)ai_allwaza_valid_work.count;
                    FightActionBuff *first=fightOutPokemon_GetFightActionBuffPtr(entry->attackers[0]);
                    if(first){
                        FightActionBuff *second=fightOutPokemon_GetFightActionBuffPtr(entry->attackers[1]);
                        if(second && fightActionCheckValid(first)!=1 && fightActionCheckValid(second)!=1 && (entry->result[0]==3 || entry->result[1]==3) && _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(entry->moves[0])==0 && _fightAi_CheckDoFightActionStrokeCheckIgnoreWaza__FUs(entry->moves[1])==0 && probability+stroke>=100){
                            fightAi_CopyAllWazaValidTable(&best,entry);
            if(best.attackers[0] && best.moves[0] && best.moves[0]!=0x176 && best.moves[0]!=0x163){
                FightOutPokemon *target;
                switch(best.eligible[0]){
                case 0:target=fightTargetGetPtr(0xF,best.attackers[0],fightType);break;
                case 1:target=fightTargetGetPtr(0x10,best.attackers[0],fightType);break;
                default:target=fightTargetGetPtr(0xF,best.attackers[0],fightType);break;
                }
                u32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target,fightType);
                fightOutPokemonCreateFightActionAttackWaza(best.attackers[0],0,0x13,0,fight_action_data_waza,best.moves[0],relative,best.slots[0],0);
                actionCount++;
            }
            if(best.attackers[1] && best.moves[1] && best.moves[1]!=0x176 && best.moves[1]!=0x163){
                FightOutPokemon *target;
                switch(best.eligible[1]){
                case 0:target=fightTargetGetPtr(0xF,best.attackers[1],fightType);break;
                case 1:target=fightTargetGetPtr(0x10,best.attackers[1],fightType);break;
                default:target=fightTargetGetPtr(0xF,best.attackers[1],fightType);break;
                }
                u32 relative=fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target,fightType);
                fightOutPokemonCreateFightActionAttackWaza(best.attackers[1],0,0x13,0,fight_action_data_waza,best.moves[1],relative,best.slots[1],0);
                actionCount++;
            }
                            break;
                        }
                    }
                }
            }
        }
    }
}

#ifdef __cplusplus
}
#endif
