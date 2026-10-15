#ifndef FIGHT_TRAINER_AI_COMBO_PRIVATE_HPP
#define FIGHT_TRAINER_AI_COMBO_PRIVATE_HPP
#include <dolphin/types.h>
struct FIGHT_TRAINER;struct FightOutPokemon;struct Pokemon;
struct ComboWaza {FightOutPokemon* attackers[2];FightOutPokemon* defenders[2];u16 moves[2];u8 slots[2],eligible[2],probability[2],combination,reserved;u16 damage[2][2];u8 result[2];u16 reserved26;u32 threat;};
struct FixedActionShell {u8 reset,unused[3];u8* sequence[2];};
struct ComboStatusMove {u16 move,stat,amount;};
typedef u8 (*ComboHit)(FIGHT_TRAINER*,FightOutPokemon*,u16,FightOutPokemon*);
typedef u8 (*ComboAction)(FIGHT_TRAINER*,FightOutPokemon**,u16,FightOutPokemon**,u16,ComboWaza*,u8);
typedef u8 (*ComboContinue)(FIGHT_TRAINER*,FightOutPokemon*,FightOutPokemon**,u16);
struct ComboDispatch {u8 count,reserved[3];ComboAction action;ComboContinue continuation;};
typedef char ComboWazaSize[sizeof(ComboWaza)==0x2C?1:-1];
#define ComboStatusUp _GetAllWazaTableValue_StatusUpWaza__FP13FIGHT_TRAINERP20AI_ALLWAZA_VALID_TBLPs
#define ComboStatusDown _GetAllWazaTableValue_StatusDownWaza__FP13FIGHT_TRAINERPP15FightOutPokemonP20AI_ALLWAZA_VALID_TBLPs
#define ComboStatusChangeSub _GetAllWazaTableValue_JoutaiChangeWazaSub__FP13FIGHT_TRAINERPP15FightOutPokemonP20AI_ALLWAZA_VALID_TBLPsUc
#define ComboStatusChange _GetAllWazaTableValue_JoutaiChangeWaza__FP13FIGHT_TRAINERPP15FightOutPokemonP20AI_ALLWAZA_VALID_TBLPs
#define ComboPower _GetAllWazaTableValue_IryokuWaza__FP13FIGHT_TRAINERPP15FightOutPokemonP20AI_ALLWAZA_VALID_TBLPs
extern "C" {
extern ComboDispatch comboid[];
extern ComboStatusMove statusUpWazaTbl[],statusDownWazaTbl[];
extern u16 NemuraseWazaTbl[],MahiWazaTbl[],KonranWazaTbl[],DokuWazaTbl[],YakedoWazaTbl[];
u16 HSD_Rand();u16 fightFloor_GetEncountDataId(void*);u32 fightFloor_GetFightType(void*);u8 fightFloor_GetTurnCount(void*);u8 fightFloorIsNowEncountVirtualBattle(void*);
void *fightEncountDataBiosGetPtr(u16);u16 fightEncountDataBiosGetDiskId(void*);u16 fightEncountDataBiosGetFightTrainerDataId(void*,u8);u16 deckDataVirtualDB_GetEnemyDeck__FUs(u16);
void *getDeckTrainerObj__11DeckTrainerFUl(u32);u8 getFixedActionID__11DeckTrainerCFv(void*);u16 getComboID__11DeckTrainerCFUc(void*,u8);u8 getComboActive__11DeckTrainerCFUc(void*,u8);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER*);FightOutPokemon *fightTrainer_GetFightoutPokemonPtr(FIGHT_TRAINER*,u8);
u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon*);void fightOutPokemon_SetFixAiWaza(FightOutPokemon*,u8);void fightOutPokemon_SetFixAiDef(FightOutPokemon*,u8);
Pokemon *fightOutPokemonGetPokemonPtr(FightOutPokemon*);u16 pokemon_GetPokemonWazaDataId(Pokemon*,u16);u16 pokemon_GetHp(Pokemon*);u8 fightOutPokemonIsHinsi(FightOutPokemon*);
FightOutPokemon *fightTargetGetPtr(u16,FightOutPokemon*,u16);u16 fightFloorGetFightTrainerFightOutPokemonPtrAry(void*,FIGHT_TRAINER*,FightOutPokemon**,u8,u8);
FIGHT_TRAINER *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*,FightOutPokemon*);u8 fightFloorCmpfightOutPokemonNimbleness(void*,FightOutPokemon*,FightOutPokemon*,u8);s8 fightAi_getAnotherPokeNo(u8);
u8 getComboFuncId__15FightOutPokemonFv(FightOutPokemon*);void setComboFuncId__15FightOutPokemonFUc(FightOutPokemon*,u8);
ComboHit wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16);u8 fightAi_CanMoveAppointWaza(FIGHT_TRAINER*,FightOutPokemon*,u16);u8 wazaIsWazaTypeId(u16,u16);
s32 fightAi_CopyAllWazaValidTable(ComboWaza*,ComboWaza*);void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER*,ComboWaza*);
s32 fightTrainerAiAddValueByAddsubDataId(s32,FIGHT_TRAINER*,u32);s32 fightAi_ThreatEnemyValue(FIGHT_TRAINER*,FightOutPokemon*,FightOutPokemon*,s16,u16,s8,s8);
u8 fightAi_HitCheckWazaAboutJoutaiAndType(FIGHT_TRAINER*,FightOutPokemon*,FightOutPokemon*,u16);u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER*,FightOutPokemon*,u16);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER*,FightOutPokemon*,u16);
u8 fightTrainerAiGetFightOutPokemonAbiCntPhyAtk(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntPhyDef(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntSubayasa(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntSpeAtk(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntSpeDef(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntAvg(FIGHT_TRAINER*,FightOutPokemon*);u8 fightTrainerAiGetFightOutPokemonAbiCntAvd(FIGHT_TRAINER*,FightOutPokemon*);
s16 fightAiCombo_GetAllWazaTableDefValue(FIGHT_TRAINER*,FightOutPokemon**,ComboWaza*,s16,s16);
void ComboStatusUp(FIGHT_TRAINER*,ComboWaza*,s16*);
void ComboStatusDown(FIGHT_TRAINER*,FightOutPokemon**,ComboWaza*,s16*);
void ComboStatusChangeSub(FIGHT_TRAINER*,FightOutPokemon**,ComboWaza*,s16*,u8);
void ComboStatusChange(FIGHT_TRAINER*,FightOutPokemon**,ComboWaza*,s16*);
void ComboPower(FIGHT_TRAINER*,FightOutPokemon**,ComboWaza*,s16*);
}
#endif
