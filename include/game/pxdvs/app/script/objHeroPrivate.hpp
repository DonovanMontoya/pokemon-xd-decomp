#ifndef APP_SCRIPT_OBJ_HERO_PRIVATE_HPP
#define APP_SCRIPT_OBJ_HERO_PRIVATE_HPP
#include <game/pxdvs/app/script/appScriptPrivate.hpp>
extern "C" {
Hero *getHeroPtr__4HeroFv();
void *getPointer__11CReliveHallFv();void *getPointer__5PCBOXFv();
u8 isReliveReadyPokemonExist__11CReliveHallFv(void *);
u8 isPokemonFull__5PCBOXFv(void *);
u8 getLegendPokemonSize__4HeroCFv(Hero *);
Pokemon *getPokemon__4HeroFl(Hero *,long);
u8 deletePokemon__4HeroFl(Hero *,long);
void setHeroStyle__4HeroFUcb(Hero *,u8,bool);
s32 heroMoveInit(GSvec *,GSvec *);s32 heroMoveMain();
void heroMoveInitEvent();void heroMoveTermEvent();
void heroMoveAddAutoEvent(s32,s32,s32,s32,s32);
u8 heroMoveSetNeckMode(s32,s32);void heroMoveSetSmoothFloorLink(u8);void heroMoveSlowStop();
s32 heroGetEmptySlot();s32 heroGetFollower();s32 heroGetLivingPokemonCount();s32 heroGetPokeomCount();
u8 heroIsMinePokemon(Hero *,Pokemon *);
void heroSetFollower(u32,u32,s32);void heroSetFollowerWithID(u8,u8);
void peopleChangeFollower(s32);void recoveryEventCommon(s32);void recoveryPokemon();
void recoveryEventPC(u32,u32,u32,s32 *,s32 *);
s32 scriptAddItem(s32,s32);s32 scriptGetItem(s32,s32);s32 scriptHaveItem(s32);
s32 scriptAddPokedoru(s32);s32 scriptGetPokedoru();s32 scriptGetPremium();s32 scriptAddPremium(s32);
void scriptSetPremium(s32);s32 scriptGetPoint();void scriptSetPoint(s32);void scriptAddPoint(s32);
s32 scriptBattleMountainEnd(u8);s16 scriptCatchPokemon(u8);
u8 scriptCheckHizukiFollow();u8 scriptCheckTemochiPokemon();
s32 scriptGetDarkPointZeroPokemonNum();s32 scriptGetDarkPokemonNum();s32 scriptGetEarthRibbon();s32 scriptGetPokemonNum();
char *scriptGetPokemonNickName(s32);s32 scriptHeroCtrlElevator(u16,s32,u16,s32);s32 scriptHizukiAway(u32,u32);
void scriptPartyChange(u8);void scriptStoreTemochiPokemon();
s32 darkPokemonGetReliveNum();s32 darkPokemonGetSnatchSuccessNum();u16 darkpokemonBiosGetScenarioNum();
s32 floorEventGetTresureEx(u8,s32,s32,u8);u8 pcBoxAllSearchPokemon(s32);
char *strncpy(char *,const char *,unsigned long);
}
static inline GSresID *heroScriptPeople(GSscript::tigaVariant *v) {
 if(v->type==0x23)return (GSresID*)v->value.pointer;
 GSscript::tigaErrMessage("people not access");return 0;
}
static inline GSscript::tigaArrayFixed *heroScriptArray(GSscript::tigaVariant *v) {
 if(v->type==7)return (GSscript::tigaArrayFixed*)v->value.pointer;
 GSscript::tigaErrMessage("pokemon not access");return 0;
}
#endif
