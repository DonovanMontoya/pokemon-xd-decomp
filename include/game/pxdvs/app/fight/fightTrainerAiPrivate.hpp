#ifndef FIGHT_TRAINER_AI_PRIVATE_HPP
#define FIGHT_TRAINER_AI_PRIVATE_HPP
#include <dolphin/types.h>
struct FIGHT_TRAINER;struct FightOutPokemon;struct Pokemon;struct FightPokemon;struct Hero;
typedef u8 (*AiDirectHitFunction)(FIGHT_TRAINER*,FightOutPokemon*,u16,FightOutPokemon*);
struct AiWordBlock20 {u32 data[8];};
struct AiWordBlock200 {u32 data[128];};
struct AiFightPokemonRecord {
    u32 entry;u8 pokemon[0xC4];u32 c8,cc,d0,d4;s16 d8;u8 da,db,dc,dd;u16 de;AiWordBlock20 extra;AiWordBlock200 work;
};
typedef char AiFightPokemonRecordSize[sizeof(AiFightPokemonRecord)==0x300?1:-1];
extern "C" {
u8 fightFloor_GetFightTypeTrainerNum(void*);u8 fightFloor_GetFightTypeEntryPokemonNum(void*);u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);
void fightSideGetHikaeFightPokemonNum(void*,u32,u32,u32);u8 pokemon_GetLevel(Pokemon*);
u8 fightTrainerAiWazaDoWazaHitFunc(FIGHT_TRAINER*,FightOutPokemon*,u16,FightOutPokemon*);
AiDirectHitFunction wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16);
u8 fightTrainerAiDB_GetStrokeValue(u32);
FightOutPokemon *fightTargetGetPtr(u8,FightOutPokemon*,u8);
void *memcpy(void*,const void*,u32);
u8 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(s32);u8 fightTrainerAiDB_GetPokemonDataOrderOutFlag(s32);u8 fightTrainerAiDB_GetPokemonSelectRandomFlag(s32);
FightPokemon *fightTrainer_GetFightPokemonPtr(FIGHT_TRAINER*,u8);void fightPokemonCreate(FIGHT_TRAINER*,FightPokemon*,Pokemon*,s32);
s32 fightFloorGetFightPokemonEntryCntInc(void*);void *getDeckTrainerObj__11DeckTrainerFUl(u32);u16 getComboID__11DeckTrainerCFUc(void*,u8);
u8 fightTrainerAi_SelComboPartner(Pokemon**,Pokemon**,u8,FIGHT_TRAINER*);
Pokemon *heroGetStatus(Hero*,u16,u16);u8 pokemonCheckValid(Pokemon*);u8 pokemonCheckFightOut(Pokemon*);
s32 _fightTrainerAiSortFirstSelectPokemonArySubSelect__FP13FIGHT_TRAINERP4HeroPP7PokemonUsUcPP7Pokemon(FIGHT_TRAINER*,Hero*,Pokemon**,u16,u8,Pokemon**);
}
static inline void aiCopyFightPokemon(AiFightPokemonRecord &dst,const AiFightPokemonRecord &src) {
    dst.entry=src.entry;memcpy(dst.pokemon,src.pokemon,0xC4);
    dst.c8=src.c8;dst.cc=src.cc;dst.d0=src.d0;dst.d4=src.d4;dst.d8=src.d8;dst.da=src.da;dst.db=src.db;dst.dc=src.dc;dst.dd=src.dd;dst.de=src.de;dst.extra=src.extra;dst.work=src.work;
}
#endif
