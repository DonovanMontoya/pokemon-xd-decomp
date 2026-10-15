#include <game/menuSaveLoadPrivate.hpp>
#include <libc/string.h>
extern "C" {
u8 GSflagTest(s32);u32 GSflagGet(s32);void fadeSet(s32,f32);s32 floorGetNextFloorID();u32 gamedatasaveGetStatus(void*,s32);void gamedatasaveSetStatus(void*,s32,s32);u32 heroGetStatus(void*,s32,s32);void *memcardMemAllocForSavedata();void memcardMemFreeForSavedata(void*);s32 memcardTaskCall(s32,s32,s32);void menuClose(s32);void menuCloseSync(s32,s32);void menuOpen(s32,s32);s8 menuSubOpenYesNo(s32,s32,s32,s32);void msgctrlSetValue(s32,u32);u32 pokecoloGetPlayTimeValue();s32 pokecoloGetRomVersion();void pokecoloSetPlayTime(f64);void *savedataGetStatus(void*,s32);void winMsgClose(s32);void winMsgOpen(s32,u32,s32,s32);void winSeqSetMenu(s32,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);s32 darkPokemonGetReliveNum();u32 darkPokemonGetSnatchSuccessNum();
}
extern u32 *flag_etc;
static menuSaveload *_saveload;
static u32 _PrevPlayTime;
static void _SaveParameterSet();
extern "C" {
void menuSaveLoadCtrl(tagWINDOW_WORK *w){if(_saveload){_saveload->Ctrl(w);return;}switch(w->mode){case 0:if(!w->sub){fadeSet(2,0.5f);w->sub=1;}break;case 3:if(!w->sub){fadeSet(3,0.5f);w->sub=1;}break;}}
void menuReport(){_saveload=new menuSaveload;_saveload->Main();delete _saveload;_saveload=0;}
s32 menuSaveLoadHook(tagWINDOW_WORK*,tagSPRITE_WORK *s){u8 ready;if(GSflagGet(0x3C4)<flag_etc[0x148/4])ready=0;else ready=1;switch(s->id){case 0x267:case 0x26F:if(!ready)winSpriteSetDisp(s,0);else winSpriteSetDisp(s,1);break;case 0x26B:if(!ready)winSpriteSetDisp(s,0);else winSpriteSetDisp(s,1);if(_saveload)_saveload->SaveParameterSet();else _SaveParameterSet();break;case 0x266:case 0x26A:case 0x26E:if(darkPokemonGetReliveNum()!=0)winSpriteSetDisp(s,1);else winSpriteSetDisp(s,0);break;}return 0;}
}
menuSaveload::~menuSaveload(){}
menuSaveload::menuSaveload(){previousTime=0;}
void menuSaveload::Main(){if(IsReport()){menuOpen(0x64,0);winMsgOpen(2,0x3BF2,1,1);if(menuSubOpenYesNo(0,0x1C2,0xC0,0)==0 && ComfirmOverwriting()){s32 next=floorGetNextFloorID();gamedatasaveSetStatus(0,5,next);memcardTaskCall(4,2,0);}winMsgClose(1);_menuClose(0x64);return;}winMsgOpen(2,0x3BE9,1,1);winMsgClose(1);}
u8 menuSaveload::ComfirmOverwriting(){s32 result=1;void *backup=memcardMemAllocForSavedata();memcpy(backup,savedataGetStatus(0,0),0x27FD0);if(memcardTaskCall(3,2,0)==3 && gamedatasaveGetStatus(0,4)!=0){u32 hero=heroGetStatus(savedataGetStatus(backup,2),2,0);if(hero==heroGetStatus(0,2,0) || gamedatasaveGetStatus(backup,4)==0){previousTime=pokecoloGetPlayTimeValue();SaveParameterSet();winMsgOpen(2,0x3BF3,1,1);if(menuSubOpenYesNo(0,0x1C2,0xC0,1)!=0)result=0;else result=1;previousTime=pokecoloGetPlayTimeValue()-previousTime;}}memcpy(savedataGetStatus(0,0),backup,0x27FD0);pokecoloSetPlayTime((f64)(previousTime+pokecoloGetPlayTimeValue()));previousTime=0;memcardMemFreeForSavedata(backup);return result!=0;}
static void _SaveParameterSet(){u32 time=pokecoloGetPlayTimeValue();if(_PrevPlayTime)time=_PrevPlayTime;msgctrlSetValue(0x4C,time);msgctrlSetValue(0x34,darkPokemonGetSnatchSuccessNum());msgctrlSetValue(0x35,darkPokemonGetReliveNum());}
void menuSaveload::SaveParameterSet(){u32 time=pokecoloGetPlayTimeValue();if(previousTime)time=previousTime;msgctrlSetValue(0x4C,time);msgctrlSetValue(0x34,darkPokemonGetSnatchSuccessNum());msgctrlSetValue(0x35,darkPokemonGetReliveNum());}
u8 menuSaveload::IsReport(){if(pokecoloGetRomVersion()==1)return 0;return GSflagTest(0x3DE);}
void menuSaveload::Ctrl(tagWINDOW_WORK *w){switch(w->mode){case 0:if(!w->sub){winSeqSetMenu(w->id,0x17F);w->sub=1;}break;case 3:if(!w->sub){winSeqSetMenu(w->id,0x185);w->sub=1;}break;}}
void menuSaveload::_menuClose(s32 id){menuClose(id);menuCloseSync(id,1);}
