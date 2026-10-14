#ifndef FIGHT_POKEMON_EFFECTS_HPP
#define FIGHT_POKEMON_EFFECTS_HPP
#include <game/pxdvs/app/fight/fightPokemon.hpp>

struct FightTrainer;
struct WazaSequence;
// Only the model tracking fields accessed by the battle effects are known.
struct ModelSequence {
    u8 reserved00[8];
    s32 type; // 0x8: model sequence when equal to 1
    u8 reserved0c[0x55];
    u8 trackPokemon;
    u8 reserved62[0x16];
    void* trackedPokemonSequence;
    void DoModelAnimation(int);
};
typedef ModelSequence FightModelSequenceView;

extern "C" {
void* fightTrainer_GetSequencePtr(FightTrainer*);
u32 fightFloor_GetFightType(void*);
u32 fightFloor_GetEnvSndId(void*);
u32 fightOutPokemonGetVoiceSndId(FightOutPokemon*);
u32 fightOutPokemon_GetKanseiSndId(FightOutPokemon*);
u32 pokemon_GetCatchBallId(Pokemon*);
u32 itemBallDB_GetOpenWzxDataId(u8);
u32 itemBallDB_GetOutWzxDataId(u8);
void Sequence_LoadWaza(void*, u16, u32, u8);
WazaSequence* Sequence_GetWaza(void*, u16, u32);
void Sequence_SetLookTarget(void*, void*);
void WazaSequence_Start(WazaSequence*, u32);
u8 WazaSequence_IsActive(WazaSequence*);
void WazaSequence_Free(WazaSequence*);
u8 wazaSequenceSysLastWazaIsImpactPoint(void*);
void GSthreadSwitch();
void GSsndPlayVolume(u32, u32, u32, u32);
void fightMenuOpenMsg(void*);
void fightMenuFightOutPokemonRenewStatusMenu(FightOutPokemon*, u8, u32);
void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon*, u8, u8, u8, void*, u8);
void fightOutPokemonDasuEffect(FightTrainer*, FightOutPokemon*, u8);
u32 fightFloor_GetTrainer(void*);
u32 fightFloor_GetFightKind(void*);
u32 itemBallDB_GetSnatchSnatchWzxDataId(u32);
u32 itemBallDB_GetSnatchBalllandWzxDataId(u32);
u32 itemBallDB_GetSnatchShakeWzxDataId(u32);
u32 itemBallDB_GetSnatchMissWzxDataId(u32);
u32 itemBallDB_GetSnatchPokeoutWzxDataId(u32);
u32 itemBallDB_GetYaseiGetWzxDataId(u32);
u32 itemBallDB_GetYaseiPokeoutWzxDataId(u32);
u32 itemBallDB_GetYaseiBallLandWzxDataId(u32);
u32 itemBallDB_GetYaseiShakeWzxDataId(u32);
u32 Sequence_GetFlags(void*);
void Sequence_SetFlags(void*, u8);
void Sequence_SetDefaultFlags(void*);
void battleGridRestoreModelVisibilityFlags();
void fightOutPokemonFreeSequence(FightOutPokemon*);
void fightMenuFightOutPokemonCloseStatusMenu(FightOutPokemon*, u8, u32);
void fightOutPokemonHokakuEffect(FightOutPokemon*, u8, u32, u8, u8*);
u32 itemBallDB_GetDowninWzxDataId(u8);
u32 itemBallDB_GetInWzxDataId(u8);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);
u32 fightTrainerIsGcHero(FightTrainer*);
u32 fightFloor_GetEncountDataId(void*);
void wazaSequenceSysFreeAllWazaExcept(void*, WazaSequence*);
void fightPokemonSetNonTrainerPokemonIsActiveFlag(u8);
void fadeSet(u32, float);
void fadeCheck(u32);
void fightMainAllCamera(u32, u32);
void* fightOutPokemonGetNamePtr(FightOutPokemon*);
void fightMsgctrlSetValue(u32, void*);
void fightMenuOpenMsg2(u32, u32);
void fightMenuCloseMsg();
extern u8 wildPokemonDownFlag;
void WazaSequence_Stop(WazaSequence*);
void fightMenuFightOutPokemonOpenStatusMenu(FightOutPokemon*, u8, u32);
void fightMenuFightOutPokemonCloseStatusMenuAnotherMine(s32, FightOutPokemon*, u8, u32, u32);
void* fightOutPokemonGetGsmodelPtr(FightOutPokemon*);
u32 GSmodelGetVisibility(void*);
void GSmodelSetVisibility(void*, u32);
void fightOutPokemonSetVisibility(FightOutPokemon*, u8);
void fightMainWaitFrame(u32);
void fightOutPokemonKizetuEffect(FightOutPokemon*, u8);
void fightOutPokemonDarkPokemonEffect(FightOutPokemon*, u8, u8, u8);
void fightOutPokemonModosuEffect(FightOutPokemon*, u8);
void fightOutPokemonDamageEffect(FightOutPokemon*);
}
#endif
