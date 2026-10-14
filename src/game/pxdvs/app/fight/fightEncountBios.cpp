#include <game/pxdvs/app/fight/fightEncountBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
extern FightEncountRecord* fight_encount_data;
extern u32* fight_encount_data_number;
extern FightEncountWipeRecord fight_encount_wipe_data[];
extern u32 fight_encount_wipe_data_number;
extern u32* fight_type_data_number;
extern FightTypeRecord* fightTypeDataBiosGetPtr(u32);
extern u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
extern u8 fightTypeDataBiosGetEntryPokemonNum(void*);
extern FightDeckRecord* deckDataVirtual_GetPtr__FUs(u16);
FightTrainerInfoRecord* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountRecord*,u8);
extern u8 GScharLenCpy(void*, const void*, u32);

void fightEncountDataBiosSetDiskId(FightEncountRecord* p, u16 v) { if (p) p->diskId=v; }
u16 fightEncountDataBiosGetDiskId(FightEncountRecord* p) { if (p==0) return 0; else return p->diskId; }
u16 fightEncountDataBiosGetWipeEffectSndID(FightEncountWipeRecord* p) { if (p==0) return 0; else return p->effectSndId; }
f32 fightEncountDataBiosGetWipeEffectTime(FightEncountWipeRecord* p) { if (p==0) return 0.0f; else return p->effectTime; }
u8 fightEncountDataBiosGetWipeSnapshotUse(FightEncountWipeRecord* p) { if(p==0)return 0; else return p->snapshotUse > 0u; }
void* fightEncountDataBiosGetWipeFunction(FightEncountWipeRecord* p) { if (p==0) return 0; else return (void*)p->function; }
FightEncountWipeRecord* fightEncountWipeDataBiosGetPtr(u32 i) { if (i >= fight_encount_wipe_data_number) return 0; return &fight_encount_wipe_data[i]; }
void* fightEncountDataBiosGetFightName(FightEncountRecord* p) { if (p==0) return 0; else return (void*)p->fightName; }
void fightEncountDataBiosSetSyoukaiWzxDataId(FightEncountRecord* p,u32 v) { if(p)p->syoukaiWzxDataId=v; }
void fightEncountDataBiosSetZenmetuFlag(FightEncountRecord* p,u8 v) { if(p)p->zenmetu=v; }
void fightEncountDataBiosSetBgmSndId(FightEncountRecord* p,u32 v) { if(p)p->bgmSndId=v; }
void fightEncountDataBiosSetGSInputDevice(FightEncountRecord* p,u8 side,u32 v) { FightTrainerInfoRecord* t=fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(t)t->inputDevice=v; }
void fightEncountDataBiosSetFightTrainerDataId(FightEncountRecord* p,u8 side,u32 v) { FightTrainerInfoRecord* t=fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(t)t->trainerData=(t->trainerData&0xffff0000)|(v&0xffff); }
void fightEncountDataBiosSetFightFloorDataId(FightEncountRecord* p,u16 v) { if(p)p->floorDataId=v; }
void fightEncountDataBiosSetEntry(FightEncountRecord* p,u8 v) { if(p)p->entry=v; }
void fightEncountDataBiosSetPokemon(FightEncountRecord* p,u8 v) { if(p)p->pokemon=v; }
void fightEncountDataBiosSetTrainer(FightEncountRecord* p,u8 v) { if(p)p->trainer=v; }
void fightEncountDataBiosSetFightType(FightEncountRecord* p,u8 v) { if(p==0)return; (void)v; }
void fightEncountDataBiosSetFightKind(FightEncountRecord* p,u8 v) { if(p)p->kind=v; }
u32 fightEncountDataBiosGetSyoukaiWzxDataId(FightEncountRecord* p) { if(p==0){return 0;}else{return p->syoukaiWzxDataId;} }
u8 fightEncountDataBiosGetZenmetuFlag(FightEncountRecord* p) { if(p==0){return 0;}else{return p->zenmetu;} }
u32 fightEncountDataBiosGetWipeId(FightEncountRecord* p) { if(p==0){return 0;}else{return p->wipeId;} }
u32 fightEncountDataBiosGetBgmSndId(FightEncountRecord* p) { if(p==0){return 0;}else{return p->bgmSndId;} }
u32 fightEncountDataBiosGetGSInputDevice(FightEncountRecord* p,u8 side) { FightTrainerInfoRecord* t=fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(t==0)return 0; else return t->inputDevice; }
u32 fightEncountDataBiosGetFightDeckGrpId(FightEncountRecord* p,u8 side) { FightTrainerInfoRecord* t=fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(!t)return 0; if(p->diskId==0)return t->trainerData>>16; else return 4; }
u32 fightEncountDataBiosGetFightTrainerDataId(FightEncountRecord* p,u8 side) { FightTrainerInfoRecord* t=fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(!t)return 0; if(!p->diskId)return t->trainerData&0xffff; FightDeckRecord* deck=deckDataVirtual_GetPtr__FUs(p->diskId); if(!deck)return 0; switch(side){case 0:return deck->entryPokemonId&0xffff; case 1:return deck->fightoutPokemonId&0xffff;default:return 0;} }
FightTrainerInfoRecord* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountRecord* p,u8 side) { if(!p)return 0; if(side>=4)return 0; return &p->trainerInfo[side]; }
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountRecord* p) { if(p==0){return 0;}else{return p->floorDataId;} }
u8 fightEncountDataBiosGetEntry(FightEncountRecord* p) { if(p==0){return 0;}else{return p->entry;} }
u8 fightEncountDataBiosGetPokemon(FightEncountRecord* p) { if(!p)return 0; if(!p->diskId)return p->pokemon; FightDeckRecord* deck=deckDataVirtual_GetPtr__FUs(p->diskId); if(deck==0)return 0;else return deck->pokemonCount; }
u8 fightEncountDataBiosGetTrainer(FightEncountRecord* p) { if(p==0){return 0;}else{return p->trainer;} }
u8 fightEncountDataBiosGetFightType(FightEncountRecord* p) { if(!p)return 0; FightTypeRecord* t; for(u8 i=0;i<*fight_type_data_number;++i){ t=fightTypeDataBiosGetPtr(i); if(p->trainer==t->trainerCount && p->pokemon==fightTypeDataBiosGetFightoutPokemonNum(t) && p->entry==fightTypeDataBiosGetEntryPokemonNum(t))return i; } return 3; }
u8 fightEncountDataBiosGetFightKind(FightEncountRecord* p) { if(p==0){return 0;}else{return p->kind;} }
FightEncountRecord* fightEncountDataBiosGetPtr(u16 i) { if(i>=*fight_encount_data_number)return 0; return &fight_encount_data[i]; }
}
