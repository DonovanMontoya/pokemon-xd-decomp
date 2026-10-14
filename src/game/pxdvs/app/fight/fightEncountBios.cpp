#include <game/pxdvs/app/fight/fightEncountBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
extern FightEncountRecord* fight_encount_data;
extern u32* fight_encount_data_number;
extern FightEncountWipeRecord* fight_encount_wipe_data;
extern u32* fight_encount_wipe_data_number;
extern u32* fight_type_data_number;
extern FightTypeRecord* fightTypeDataBiosGetPtr(u8);
extern u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
extern u8 fightTypeDataBiosGetEntryPokemonNum(void*);
extern u8* deckDataVirtual_GetPtr__FUs(u16);
void* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountRecord*,u8);
extern u8 GScharLenCpy(void*, const void*, u32);

void fightEncountDataBiosSetDiskId(FightEncountRecord* p, u16 v) { if (p) p->diskId=v; }
u16 fightEncountDataBiosGetDiskId(FightEncountRecord* p) { return p ? p->diskId : 0; }
u16 fightEncountDataBiosGetWipeEffectSndID(FightEncountWipeRecord* p) { return p ? p->effectSndId : 0; }
f32 fightEncountDataBiosGetWipeEffectTime(FightEncountWipeRecord* p) { return p ? p->effectTime : 0.0f; }
u8 fightEncountDataBiosGetWipeSnapshotUse(FightEncountWipeRecord* p) { return p && p->snapshotUse != 0; }
void* fightEncountDataBiosGetWipeFunction(FightEncountWipeRecord* p) { return p ? (void*)p->function : 0; }
FightEncountWipeRecord* fightEncountWipeDataBiosGetPtr(u32 i) { if (i >= *fight_encount_wipe_data_number) return 0; return &fight_encount_wipe_data[i]; }
void* fightEncountDataBiosGetFightName(FightEncountRecord* p) { return p ? (void*)p->fightName : 0; }
void fightEncountDataBiosSetSyoukaiWzxDataId(FightEncountRecord* p,u32 v) { if(p)p->syoukaiWzxDataId=v; }
void fightEncountDataBiosSetZenmetuFlag(FightEncountRecord* p,u8 v) { if(p)p->zenmetu=v; }
void fightEncountDataBiosSetBgmSndId(FightEncountRecord* p,u32 v) { if(p)p->bgmSndId=v; }
void fightEncountDataBiosSetGSInputDevice(FightEncountRecord* p,u8 side,u32 v) { u32* t=(u32*)fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(t)t[1]=v; }
void fightEncountDataBiosSetFightTrainerDataId(FightEncountRecord* p,u8 side,u32 v) { u32* t=(u32*)fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(t)t[0]=(t[0]&0xffff0000)|(v&0xffff); }
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
u32 fightEncountDataBiosGetGSInputDevice(FightEncountRecord* p,u8 side) { u32* t=(u32*)fightEncountDataBiosGetFightTrainerInfoPtr(p,side); return t?t[1]:0; }
u32 fightEncountDataBiosGetFightDeckGrpId(FightEncountRecord* p,u8 side) { u32* t=(u32*)fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(!t)return 0; return p->diskId ? 4 : t[0]>>16; }
u32 fightEncountDataBiosGetFightTrainerDataId(FightEncountRecord* p,u8 side) { u32* t=(u32*)fightEncountDataBiosGetFightTrainerInfoPtr(p,side); if(!t)return 0; if(!p->diskId)return t[0]&0xffff; u8* deck=deckDataVirtual_GetPtr__FUs(p->diskId); if(!deck)return 0; if(side==0)return *(u32*)(deck+8)&0xffff; if(side==1)return *(u32*)(deck+12)&0xffff; return 0; }
void* fightEncountDataBiosGetFightTrainerInfoPtr(FightEncountRecord* p,u8 side) { if(!p || side>=4)return 0; return (u8*)p+0x1c+side*8; }
u16 fightEncountDataBiosGetFightFloorDataId(FightEncountRecord* p) { if(p==0){return 0;}else{return p->floorDataId;} }
u8 fightEncountDataBiosGetEntry(FightEncountRecord* p) { if(p==0){return 0;}else{return p->entry;} }
u8 fightEncountDataBiosGetPokemon(FightEncountRecord* p) { if(!p)return 0; if(!p->diskId)return p->pokemon; u8* deck=deckDataVirtual_GetPtr__FUs(p->diskId); return deck?deck[2]:0; }
u8 fightEncountDataBiosGetTrainer(FightEncountRecord* p) { if(p==0){return 0;}else{return p->trainer;} }
u8 fightEncountDataBiosGetFightType(FightEncountRecord* p) { if(!p)return 0; for(u8 i=0;i<*fight_type_data_number;++i){ FightTypeRecord* t=fightTypeDataBiosGetPtr(i); if(t->trainerCount==p->trainer && fightTypeDataBiosGetFightoutPokemonNum(t)==p->pokemon && fightTypeDataBiosGetEntryPokemonNum(t)==p->entry)return i; } return 3; }
u8 fightEncountDataBiosGetFightKind(FightEncountRecord* p) { if(p==0){return 0;}else{return p->kind;} }
FightEncountRecord* fightEncountDataBiosGetPtr(u16 i) { if(i>=*fight_encount_data_number)return 0; return &fight_encount_data[i]; }
}
