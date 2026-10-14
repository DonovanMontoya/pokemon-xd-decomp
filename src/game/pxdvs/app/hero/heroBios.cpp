#include <game/pxdvs/app/hero/heroBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
extern void* memcpy(void*, const void*, u32);
extern u32 GScharLenCpy(void*, const void*, u32);
void heroBiosSetMeetDarkPokemonCount(HeroBiosLayout* p,u8 v){if(p)((u8*)p)[0x938]=v;}
u8 heroBiosGetMeetDarkPokemonCount(HeroBiosLayout* p){if(p==0){return 0;}else{return ((u8*)p)[0x938];}}
void heroBiosSetHomePlace(HeroBiosLayout* p,u8 v){if(p)p->home=v;}
u8 heroBiosGetHomePlace(HeroBiosLayout* p){if(p==0){return 0;}else{return p->home;}}
u8 heroBiosGetHizukiFlag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->hizukiFlag;}}
void heroBiosSetHizukiFlag(HeroBiosLayout* p,u8 v){if(p)p->hizukiFlag=v;}
u32 heroBiosGetPokecouponAll(HeroBiosLayout* p){if(p==0){return 0;}else{return p->pokecouponAll;}}
void heroBiosSetPokecouponAll(HeroBiosLayout* p,s32 v){if(!p)return;if(v<0)v=0;if(v>0x98967f)v=0x98967f;p->pokecouponAll=v;}
u32 heroBiosGetPokecoupon(HeroBiosLayout* p){if(p==0){return 0;}else{return p->pokecoupon;}}
void heroBiosSetPokecoupon(HeroBiosLayout* p,s32 v){if(!p)return;if(v<0)v=0;if(v>0x98967f)v=0x98967f;p->pokecoupon=v;}
u32 heroBiosGetPokedoru(HeroBiosLayout* p){if(p==0){return 0;}else{return p->pokedoru;}}
void heroBiosSetPokedoru(HeroBiosLayout* p,s32 v){if(!p)return;if(v<0)v=0;if(v>0x98967f)v=0x98967f;p->pokedoru=v;}
void heroBiosSetHizukiNamePtr(HeroBiosLayout* p,const void* name){if(p&&name)GScharLenCpy(p->hizukiName,name,0xb);}
u16* heroBiosGetHizukiNamePtr(HeroBiosLayout* p){if(p==0){return 0;}else{return (u16*)p->hizukiName;}}
u8 heroBiosGetBadge08Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[7];}}
u8 heroBiosGetBadge07Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[6];}}
u8 heroBiosGetBadge06Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[5];}}
u8 heroBiosGetBadge05Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[4];}}
u8 heroBiosGetBadge04Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[3];}}
u8 heroBiosGetBadge03Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[2];}}
u8 heroBiosGetBadge02Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[1];}}
u8 heroBiosGetBadge01Flag(HeroBiosLayout* p){if(p==0){return 0;}else{return p->badges[0];}}
void heroBiosSetBadge08Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[7]=v;}
void heroBiosSetBadge07Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[6]=v;}
void heroBiosSetBadge06Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[5]=v;}
void heroBiosSetBadge05Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[4]=v;}
void heroBiosSetBadge04Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[3]=v;}
void heroBiosSetBadge03Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[2]=v;}
void heroBiosSetBadge02Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[1]=v;}
void heroBiosSetBadge01Flag(HeroBiosLayout* p,u8 v){if(p)p->badges[0]=v;}
u8 heroBiosGetSexDataId(HeroBiosLayout* p){if(p==0){return 0;}else{return p->sex;}}
void heroBiosSetSexDataId(HeroBiosLayout* p,u8 v){if(p)p->sex=v;}
void heroBiosSetRnd(HeroBiosLayout* p,u32 v){if(p)p->rnd=v;}
void heroBiosSetNamePtr(HeroBiosLayout* p,const void* name){if(p!=0){if(name!=0)GScharLenCpy(p,name,0xb);}}
void* heroBiosGetHizukiItemPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=10){return 0;}return (u8*)p+0x8fa+i*4;}
void* heroBiosGetItemKoronPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=3){return 0;}return (u8*)p+0x7e4+i*4;}
void* heroBiosGetItemSeedPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=46){return 0;}return (u8*)p+0x72c+i*4;}
void* heroBiosGetItemSkillPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=64){return 0;}return (u8*)p+0x62c+i*4;}
void* heroBiosGetItemBallPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=16){return 0;}return (u8*)p+0x5ec+i*4;}
void* heroBiosGetExtraItemPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=43){return 0;}return (u8*)p+0x540+i*4;}
void* heroBiosGetItemNormalPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=30){return 0;}return (u8*)p+0x4c8+i*4;}
void* heroBiosGetPokemonPtr(HeroBiosLayout* p,u16 i){if(p==0){return 0;}if(i>=6){return 0;}return (u8*)p+0x30+i*0xc4;}
u32 heroBiosGetRnd(HeroBiosLayout* p){if(p==0){return 0;}else{return p->rnd;}}
u16* heroBiosGetNamePtr(HeroBiosLayout* p){if(p==0){return 0;}else{return (u16*)p;}}
void heroBiosCopy(HeroBiosLayout* dst,const HeroBiosLayout* src){if(dst&&src)memcpy(dst,src,0x978);}
}
