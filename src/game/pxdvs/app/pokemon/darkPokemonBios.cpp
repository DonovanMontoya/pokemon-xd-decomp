#include <global.h>
extern "C" {
extern u32 darkPokemonGetDarkPokemon(u32);
extern u32 deckGetDeckDarkPokemon(u32);
extern u32 deckGetDarkPokemonSize(void);
extern u16 fightFloorGetStatus(u32,u32,u32,u32);
extern u16 getCatchFloorId__11DarkPokemonCFv(u32);
extern s32 getDarkWaza__15DeckDarkPokemonCFSc(u32,s32);
extern s32 getInitDarkPoint__15DeckDarkPokemonCFv(u32);
extern s32 getMeetDarkPokemonCount__4HeroCFv(u32);
extern s32 getPlayerLevel__15DeckDarkPokemonCFv(u32);
extern s32 getRnd__11DarkPokemonCFv(u32);
extern s32 getSnatchRatio__15DeckDarkPokemonCFv(u32);
extern s32 getStatusRnd__11DarkPokemonCFUc(u32,u32);
extern s32 getStatus__11DarkPokemonCFv(u32);
extern s32 getWalkCount__11DarkPokemonCFv(u32);
extern s32 isInformation__11DarkPokemonCFv(u32);
extern u8 isScenarioPokemon__15DeckDarkPokemonCFv(u32);
extern s32 savedataGetStatus(u32,u32);
extern void setCatchFloorId__11DarkPokemonFUs(u32,u32);
extern void setInformation__11DarkPokemonFb(u32,s32);
extern void setMeetDarkPokemonCount__4HeroFUc(u32,u32);
extern void setRnd__11DarkPokemonFUl(u32,u32);
extern void setSnatchIndex__11DarkPokemonFUc(u32,u32);
extern void setSnatchInfoLevel__11DarkPokemonFUc(u32,u32);
extern void setStatusRnd__11DarkPokemonFUcUc(u32,u32,u32);
extern void setStatus__11DarkPokemonF17darkPokemonStatus(u32,s32);
extern void setUpdate__11DarkPokemonFb(u32,s32);
extern void setWalkCount__11DarkPokemonFUl(u32,u32);
extern void addStatus__11DarkPokemonF17darkPokemonStatus(u32,s32);
extern s32 darkPokemonBiosGetInitDarkPoint(u16);
u16* darkPokemonListBiosGetDPList(u16);
extern u32 darkPokemonList[]; extern u32 darkPokemonList_number;
u16* darkPokemonListBiosGetDPList(u16 i){if(i>=darkPokemonList_number)return 0;return (u16*)darkPokemonList+i;}
u16 darkPokemonListBiosGetPokemonID(u16 id){u16* (*getList)(u32)=(u16*(*)(u32))darkPokemonListBiosGetDPList;u16* p=getList(id);if(p!=0)return *p;return 0;}
s32 darkpokemonBiosGetScenarioNum(void){s32 n=0;for(u16 i=0;i<deckGetDarkPokemonSize();i++){u32 p=deckGetDeckDarkPokemon(i);if(p!=0&&isScenarioPokemon__15DeckDarkPokemonCFv(p)!=0)n++;}return n;}
u16 darkPokemonBiosGetSteps(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p==0)return 0;return getWalkCount__11DarkPokemonCFv(p);}
void darkPokemonBiosSetSteps(u16 i,u16 v){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setWalkCount__11DarkPokemonFUl(p,v);}
void darkPokemonBiosSetInfomation(u16 i,u8 v){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setSnatchInfoLevel__11DarkPokemonFUc(p,v);}
s32 darkPokemonBiosGetRnd(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)return getRnd__11DarkPokemonCFv(p);return 0;}
void darkPokemonBiosSetRnd(u16 i,s32 v){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setRnd__11DarkPokemonFUl(p,v);}
s8 darkPokemonBiosGetStatusRnd(u16 i,u8 n){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)return getStatusRnd__11DarkPokemonCFUc(p,n);return 0;}
void darkPokemonBiosSetStatusRnd(u16 i,u8 n,u8 v){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setStatusRnd__11DarkPokemonFUcUc(p,n,v);}
s32 darkPokemonBiosGetFightFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0&&getStatus__11DarkPokemonCFv(p)>=1)return 1;return 0;}
void darkPokemonBiosSetFightFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p){u16 floor=fightFloorGetStatus(0,0,0x4a,0);u16 catchId=getCatchFloorId__11DarkPokemonCFv(p);if(getStatus__11DarkPokemonCFv(p)==0&&catchId!=0xb5){s32 player=savedataGetStatus(0,2);s32 count=getMeetDarkPokemonCount__4HeroCFv((u32)player);setMeetDarkPokemonCount__4HeroFUc(player,(u8)(count+1));setSnatchIndex__11DarkPokemonFUc(p,count);addStatus__11DarkPokemonF17darkPokemonStatus(p,1);setCatchFloorId__11DarkPokemonFUs(p,floor);setUpdate__11DarkPokemonFb(p,1);}if(catchId==0xb5){addStatus__11DarkPokemonF17darkPokemonStatus(p,1);setCatchFloorId__11DarkPokemonFUs(p,floor);setUpdate__11DarkPokemonFb(p,1);}}}
s32 darkPokemonBiosGetSnatchSuccessFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0&&getStatus__11DarkPokemonCFv(p)>=3)return 1;return 0;}
s32 darkPokemonBiosGetReliveFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0&&getStatus__11DarkPokemonCFv(p)==4)return 1;return 0;}
void darkPokemonBiosSetReliveFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setStatus__11DarkPokemonF17darkPokemonStatus(p,4);}
s32 darkPokemonBiosGetInformationFlag(u16 i){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)return isInformation__11DarkPokemonCFv(p);return 0;}
void darkPokemonBiosSetInformationFlag(u16 i,s32 v){u32 p=darkPokemonGetDarkPokemon(i);if(p!=0)setInformation__11DarkPokemonFb(p,v);}
s32 darkPokemonBiosGetTemotiDarkWaza(u16 i,s8 w){u32 p=deckGetDeckDarkPokemon(i);if(p!=0)return getDarkWaza__15DeckDarkPokemonCFSc(p,w);return 0;}
s32 darkPokemonBiosGetLevel(u16 i){u32 p=deckGetDeckDarkPokemon(i);if(p!=0)return getPlayerLevel__15DeckDarkPokemonCFv(p);return 0;}
s32 darkPokemonBiosGetHokakuritu(u16 i){u32 p=deckGetDeckDarkPokemon(i);if(p!=0)return getSnatchRatio__15DeckDarkPokemonCFv(p);return 0;}
u16 darkPokemonBiosGetDarkPoint(u16 id){return (u16)((s32(*)(u32))darkPokemonBiosGetInitDarkPoint)(id);}
s32 darkPokemonBiosGetInitDarkPoint(u16 i){u32 p=deckGetDeckDarkPokemon(i);if(p!=0)return getInitDarkPoint__15DeckDarkPokemonCFv(p);return 0;}
}
