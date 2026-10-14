#ifndef FIGHT_POKEMON_EFFECTS_HPP
#define FIGHT_POKEMON_EFFECTS_HPP
#include <game/pxdvs/app/fight/fightPokemon.hpp>

struct FightTrainer;
struct WazaSequence;
// Only the model tracking fields accessed by the battle effects are known.
struct FightModelSequenceView {
    u8 reserved00[0x61];
    u8 trackPokemon;
    u8 reserved62[0x16];
    void* trackedPokemonSequence;
};

extern "C" {
void* fightTrainer_GetSequencePtr(FightTrainer*);
u32 fightFloor_GetFightType(void*);
u32 fightFloor_GetEnvSndId(void*);
u32 fightOutPokemonGetVoiceSndId(FightOutPokemon*);
u32 fightOutPokemon_GetKanseiSndId(FightOutPokemon*);
u32 pokemon_GetCatchBallId(Pokemon*);
u32 itemBallDB_GetOpenWzxDataId(u8);
u32 itemBallDB_GetOutWzxDataId(u8);
void Sequence_LoadWaza(void*, u16, u32, void*);
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
}
#endif
