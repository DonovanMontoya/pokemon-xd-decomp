#include <game/menuPcBoxPokemonLayout.hpp>
extern "C" {
u32 FlashSystemGetFrameFromLabel(u32,const char*);u32 FlashSystemGetNowFrame(u32);void FlashSystemPlayAndWait(u32,const char*,const char*);void FlashSystemSetLoopFlag(u32,s32);void FlashSystemSetNowFrameLabel(u32,const char*);void FlashSystemSetPlayFrameLabel(u32,const char*,const char*);u32 GSmsgGetRect(u32);void GSmsgPrint2(s32,s32,s32,u32,u32);void GSthreadSwitch();s32 darkPokemonGetReliveNum();s32 darkPokemonGetSnatchSuccessNum();void fadeCheck(s32);void fadeSet(s32,f32);void floorClearReturnPoint();void floorReturnSavePoint();void floorSetContinueMode(s32);void fn_800A39E4();void fn_800A3A1C();s32 heroGetObjID(s32);void heroMoveSyncWithHero();void menuCloseCustom(s32,u32,s32);void menuColosseumBattle(s32);u8 menuIsCheck(s32);MENU_ITEM_dd_ *menuItemBiosGetPtr(s32,s16);void menuModelAdjustCamera(MENU_MODEL*);u8 menuModelCheck(MENU_MODEL*,s32);void menuModelInit(MENU_MODEL*,s16,s16);void menuModelLoad(MENU_MODEL*,s32);void menuModelRender(MENU_MODEL*);void menuModelSetAngle(MENU_MODEL*,f32*);void menuModelSetMotion(MENU_MODEL*,s32);void menuModelSetSize(MENU_MODEL*,s16,s16,s16,s16);void menuModelSetZoom(MENU_MODEL*,f32);void menuModelTerm(MENU_MODEL*);void menuOpen(s32,s32);s16 menuOpenCustom(s32,s32,void*,s32,s32,s32,...);s8 menuSubOpenYesNo(s32,s32,s32,s32);void menuTitleBattlePreReadCheck();void menuTitleCursorAnime();void menuTitleCursorAnimeMain();s16 menuTitleGetSelect();void menuTitleOpenSelectAnime();void menuTitlePlayBGM();void msgctrlSetValue(s32,s32);void *peopleInfoBiosGetPtr(u32);void peopleInfoBiosGetMotion(void*,s32,s32*,s32*);u32 pokecoloGetPlayTimeValue();s32 pokecoloGetRomVersion();void pokecoloSetPlayTime(f64);void pokecoloStartCountPlayTime(s32);void savedataCreate(void*,u16*);void scriptModelClose(s32);u32 soundGetBGMID();void soundOpenPlay(u32,u32,u32);void winMsgClose(s32);void winMsgOpen(s32,u32,s32,s32);void winSeqSetMenu(s32,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);s32 windowGetActiveID();tagWINDOW_WORK *windowSearchID(s32);s32 menuTop();
}
struct MenuTopWork{s32 selected;s32 state;u8 battle;u8 pad[3];s32 battleSelect;};
static MenuTopWork _menuTopWork;
static MENU_MODEL _menuTopMenuModel;
static s32 _menuTopSelectCursor;
s32 _menuTopResID;
static s32 _menuTopMsgTable[5]={0x42E2,0x42E1,0x444E,0x42E3,0x42E6};
static s32 _menuTopMsgTableBattleSelect[3]={0x42E4,0x42E5,0xAF};
static void _menuTopClose(s32 id){menuCloseCustom(id,0,1);}
static void _menuTopClose2(s32 id,u32 flags){if(menuIsCheck(id)==1)menuCloseCustom(id,flags,1);}
static void _menuTopInitPokemon(s16 x,s16 y){menuModelInit(&_menuTopMenuModel,x,y);}
static void _menuTopExitPokemon(){menuModelTerm(&_menuTopMenuModel);}
static void _menuTopLoadPokemon(){s32 a,b;menuModelLoad(&_menuTopMenuModel,heroGetObjID(1));menuModelCheck(&_menuTopMenuModel,1);peopleInfoBiosGetMotion(peopleInfoBiosGetPtr(0x16C90400),1,&a,&b);menuModelSetMotion(&_menuTopMenuModel,a);}
static void _menuTopExit(){_menuTopClose2(0x116,2);scriptModelClose(_menuTopResID);}
static void _menuTopInit(){_menuTopWork.selected=_menuTopSelectCursor;_menuTopWork.state=0;_menuTopWork.battleSelect=0;}
static void _menuTopSetLastCursor(){s32 n=_menuTopWork.selected;if(n>=5 || n<0)n=0;_menuTopSelectCursor=n;}
static void _menuTopNewGame(u16 *name){savedataCreate(0,name);pokecoloStartCountPlayTime(1);pokecoloSetPlayTime(0.0);}
static s32 _menuTopLoadCheck(){s32 time=pokecoloGetPlayTimeValue();s32 relive=darkPokemonGetReliveNum();s32 snatch=darkPokemonGetSnatchSuccessNum();FlashSystemSetPlayFrameLabel(0x22063000,"start","end");FlashSystemSetLoopFlag(0x22063000,0);FlashSystemSetNowFrameLabel(0x22063000,"start");msgctrlSetValue(0x4C,time);msgctrlSetValue(0x2F,snatch);msgctrlSetValue(0x30,relive);menuOpen(0xDB,0);winMsgOpen(1,0x42EE,0,1);s32 result;if(menuSubOpenYesNo(0,0x1C2,0xC0,1)==0){heroMoveSyncWithHero();floorSetContinueMode(1);floorClearReturnPoint();floorReturnSavePoint();result=100;pokecoloStartCountPlayTime(1);}else{result=1;pokecoloStartCountPlayTime(1);}fn_800A3A1C();_menuTopExitPokemon();_menuTopClose(0xDB);winMsgClose(1);fadeCheck(1);return result;}
extern "C" {
void menuTopOpenFlashBack(){menuOpen(0x119,0);}
void menuTopSelectCtrl(tagWINDOW_WORK *w){u8 *data=(u8*)w->parameters[0];switch(w->phase){case 0:if(!w->step){if(*data)winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}}
void menuTopBattleSelectCtrl(tagWINDOW_WORK *w){menuTitleCursorAnimeMain();switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x24);w->step=1;}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);w->step=1;}break;}}
void menuTopPlayToolBGM(){if(soundGetBGMID()!=0x568)soundOpenPlay(0x568,0,255);}
void menuTopExit(){_menuTopExit();}
void menuTopMain(){menuTop();}
void menuTopInit(){_menuTopInit();}
u8 menuTopGetBattleMode(){return _menuTopWork.battle;}
s32 menuTopGetBattleSelectMode(){return _menuTopWork.battleSelect;}
void menuTopSetBattleSelectMode(s32 mode){_menuTopWork.battleSelect=mode;}
void menuTopSetInitCursor(s32 n){_menuTopSelectCursor=n;}
void menuTopHookMssageWindow(tagWINDOW_WORK *w){u32 value=*(u32*)&w->first;s16 selected=((s16*)&value)[1];if(pokecoloGetRomVersion()!=1 && selected>=0)GSmsgPrint2(w->layer,0,-8,0xFFFFFF00|w->alpha,_menuTopMsgTable[menuTitleGetSelect()]);}
void menuTopHookMssageBattleSelectWindow(tagWINDOW_WORK *w){u32 value=*(u32*)&w->first;s16 selected=((s16*)&value)[1];if(selected>=0)GSmsgPrint2(w->layer,0,-8,0xFFFFFF00|w->alpha,_menuTopMsgTableBattleSelect[selected]);}
void fn_8002F668(tagWINDOW_WORK *w,tagSPRITE_WORK *s,u32 msg){u32 rect=GSmsgGetRect(msg);MENU_ITEM_dd_ *p=menuItemBiosGetPtr(w->menu,s->id);s32 width=*(s16*)((u8*)p+0xA)-(s16)(rect>>16);s32 height=*(s16*)((u8*)p+0xC)-(s16)rect;GSmsgPrint2(w->layer,width/2,height/2,0xFFFFFF00|w->alpha,msg);}
void menuTopHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){u32 value=*(u32*)&w->first;s16 selected=((s16*)&value)[1];switch(s->id){case 0x70:if(selected==0){menuTitleCursorAnime();winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x71:if(selected==1){menuTitleCursorAnime();winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x72:if(selected==2){menuTitleCursorAnime();winSpriteSetDisp(s,1);}else winSpriteSetDisp(s,0);break;case 0x76:fn_8002F668(w,s,0x445A);break;case 0x77:fn_8002F668(w,s,0x4459);break;}}
void menuTopLoadHook(){struct Rect{s16 x,y;}a={250,30},b={320,400};f32 angle[3];angle[0]=0;angle[1]=-0.2f;angle[2]=0;if(!menuModelCheck(&_menuTopMenuModel,0)){menuModelSetSize(&_menuTopMenuModel,a.x,a.y,b.x,b.y);menuModelAdjustCamera(&_menuTopMenuModel);menuModelRender(&_menuTopMenuModel);menuModelSetAngle(&_menuTopMenuModel,angle);menuModelSetZoom(&_menuTopMenuModel,1.5f);}}
void __sinit_menuTop_cpp(){}
}
