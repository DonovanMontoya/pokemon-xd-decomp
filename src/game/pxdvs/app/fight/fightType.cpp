#include <global.h>
extern "C" {
extern s32 fight_type_data;
extern u32* fight_type_data_number;
s32 fightTypeDataBiosGetPtr(u16);
u8 fightTypeDataBiosGetFightoutPokemonNum(void*);
u8 fightTypeDataBiosGetTrainerNum(u8*);
u16 fightTypeGetFightSideFightOutPokemonMax(u16 id){void* first=(void*)fightTypeDataBiosGetPtr(id);u8 n=fightTypeDataBiosGetTrainerNum((u8*)first);void* p=(void*)fightTypeDataBiosGetPtr(id);return n*fightTypeDataBiosGetFightoutPokemonNum(p);}
u8 fightTypeDataBiosGetFightoutPokemonNum(void* p){if(p==0)return 0;return *((u8*)p+2);}
u8 fightTypeDataBiosGetEntryPokemonNum(void* p){if(p==0)return 0;return *((u8*)p+1);}
u8 fightTypeDataBiosGetTrainerNum(u8* p){if(p==0)return 0;u8 n=*p;switch(n){case 0:return 1;case 1:return 1;case 2:return 2;default:return 0;}}
s32 fightTypeDataBiosGetName(void* p){if(p==0)return 0;return *(s32*)((u8*)p+4);}
s32 fightTypeDataBiosGetPtr(u16 id){if(id>*fight_type_data_number)return 0;return fight_type_data+((id*8)&0x7fff8);}
}
