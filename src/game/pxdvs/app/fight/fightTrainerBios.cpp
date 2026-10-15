#include <global.h>
extern "C" {
extern s32 fight_trainer_kind_data;
extern u32* fight_trainer_kind_data_number;
extern s32 fight_trainer_ai_value_addsub_data;
extern u32* fight_trainer_ai_value_addsub_data_number;
extern s32 fight_trainer_pokemon_part_data;
extern u32* fight_trainer_pokemon_part_data_number;
extern void* getDeckTrainerAIObj__13DeckTrainerAIFUl(u16);
s32 fightTrainerKindDataBiosGetBgmSndId(void* p) { if (!p) return 0; return *(s32*)((u8*)p+8); }
s32 fightTrainerKindDataBiosGetPrefixName(void* p) { if (!p) return 0; return *(s32*)((u8*)p+4); }
u16 fightTrainerKindDataBiosGetSyoukinBairitu(u16* p) { if (!p) return 0; return *p; }
s32 fightTrainerKindDataBiosGetPtr(u16 id) { if (id >= *fight_trainer_kind_data_number) return 0; return fight_trainer_kind_data + id*0xC; }
void fightTrainerEnemyPokemonBiosSetParam1bantakaiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x24)=v;}
void fightTrainerEnemyPokemonBiosSetBadwazaHaveFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x23)=v;}
void fightTrainerEnemyPokemonBiosSetDefense1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x22)=v;}
void fightTrainerEnemyPokemonBiosSetLv1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x21)=v;}
void fightTrainerEnemyPokemonBiosSetNowhp1banhikuiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x20)=v;}
void fightTrainerEnemyPokemonBiosSetStoreTokuseiData(void* p,s16 v){if(p)*(s16*)((u8*)p+0x1e)=v;}
void fightTrainerEnemyPokemonBiosSetTokuseiFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x1c)=v;}
void fightTrainerEnemyPokemonBiosSetExpectWazaDataId(u32 p,u8 i,s16 v){if(p&&i<=8)*(s16*)(p+i*2+0xc)=v;}
void fightTrainerEnemyPokemonBiosSetStoreWazaDataId(u32 p,u8 i,s16 v){if(p&&i<=4)*(s16*)(p+i*2+4)=v;}
void fightTrainerEnemyPokemonBiosSetExpectWazaNum(void* p,s8 v){if(p)*(s8*)((u8*)p+3)=v;}
void fightTrainerEnemyPokemonBiosSetStoreWazaNum(void* p,s8 v){if(p)*(s8*)((u8*)p+2)=v;}
void fightTrainerEnemyPokemonBiosSetFightEntryeId(s16* p,s16 v){if(p)*p=v;}
s16 fightTrainerEnemyPokemonBiosGetFightEntryeId(s16* p){if(!p)return 0;return *p;}
s32 fightTrainerAiValueAddsubDataBiosGetPtr(u16 id){if(id>=*fight_trainer_ai_value_addsub_data_number)return 0;return fight_trainer_ai_value_addsub_data+id*0x14;}
s32 fightTrainerPokemonPartDataBiosGetPtr(u16 id){if(id>=*fight_trainer_pokemon_part_data_number)return 0;return fight_trainer_pokemon_part_data+id*0x18;}
void fightTrainerAiDataBiosGetPtr(u16 id){getDeckTrainerAIObj__13DeckTrainerAIFUl(id);}
u8 fightTrainerBiosGetControllerId(void* p){if(!p)return 0;return *(u8*)((u8*)p+0x3540);}
s32 fightTrainerBiosGetFightPokemonPtr(s32 p,u16 i){if(!p||i>=6)return 0;return p+i*0x300+0x97c;}
s32 fightTrainerBiosGetHeroPtr(u32 p){if(!p)return 0;return p+4;}
}
