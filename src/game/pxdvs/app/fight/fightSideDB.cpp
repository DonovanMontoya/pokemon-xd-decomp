#include <global.h>
extern "C" {
extern u16* fightSideDataBiosGetPtr(u16);
void fightSide_SetMakibisiCheckFlag(void* p,s8 v){if(p)*(s8*)((u8*)p+0x6eec)=v;}
void fightSide_SetFightSideDataId(s16* p,s16 v){if(p)*p=v;}
u8 fightSide_GetMakibisiCheckFlag(void* p){if(p==0)return 0;return *(u8*)((u8*)p+0x6eec);}
s32 fightSide_GetFightTrainerPtr(s32 p,u16 i){if(!p)return 0;if(i>=2)return 0;return p+i*0x3744+0x64;}
s32 fightSide_GetJoutaiPtr(s32 p,u16 i){if(!p)return 0;if(i>=6)return 0;return p+((i*0x10)&0xffff0)+4;}
u16 fightSide_GetFightSideDataId(u16* p){if(p==0)return 0;return *p;}
u16 fightSideDB_GetYrot(u16 id){u16* p=fightSideDataBiosGetPtr(id);if(p==0)return 0;return *p;}
}
