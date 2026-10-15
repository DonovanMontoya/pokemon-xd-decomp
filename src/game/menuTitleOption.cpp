#include <game/menuPcBoxPokemonLayout.hpp>
struct OptionWork {s32 field0,field4,cycles,direction;f32 rotation,field14,amplitude,dt,timer,frame,frequency;};
static OptionWork _menuTitleOptionWork;
static f32 _atable[3];
static u32 _menuOptionMsgTable[3]={0x42E7,0x42E8,0x42E9};
extern "C" {void winSpriteSetDisp(tagSPRITE_WORK*,s32);void menuTitleCursorAnime(tagWINDOW_WORK*,tagSPRITE_WORK*);void GSmsgPrint2(s32,s32,s32,u32,u32);}
extern "C" {void GSinputMotorStart(s32,s32,s32,s32,s32);s32 GSsndGetOutputMode();void GSsndSetOutputMode(s32);void fadeCheck(s32);void fadeSet(s32,f32);void fn_800A3A1C();s32 gamedatasaveGetStatus(void*,s32);void gamedatasaveSetStatus(void*,s32,s32);u8 memcardIsMemCardValid();void memcardTaskCall(s32,s32,s32);void menuButtonNormal(tagWINDOW_WORK*);void menuCloseCustom(s32,s32,s32);void menuCursorNormal(tagWINDOW_WORK*,s32);s32 menuOpen(s32,s32);void menuPdaSubCalcAlpha(void*,s32,s16);void menuPdaSubInitAlpha(void*,s32,s32,void*,f32,f32);void menuPlaySe(s32,s32);s8 menuSubOpenYesNo(s32,s32,s32,s32);void menuTitleCursorAnimeMain();void menuToolSetSelect(s32);f64 sin(f64);f32 timeGetLastFrameSec();void winMsgClose(s32);void winMsgOpen(s32,u32,s32,s32);void winSeqSetMenu(s32,s32);u16 *windowGetKeyInfo();u16 windowGetKeyRepeat();tagWINDOW_WORK *windowSearchID(s32);}

static void _menuTitleOptionSetFrameSec();
static void _menuTitleOptionCalcRot();
static void _menuTitleOptionClose(s32 id);
static void _menuTitleOptionExit();
static void _menuTitleOptionInit();
extern "C" void menuTitleOptionCtrl(tagWINDOW_WORK *w){menuTitleCursorAnimeMain();u32 value=*(u32*)&w->first;switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x24);fadeSet(2,0.5f);w->step=1;}break;case 2:menuPdaSubCalcAlpha(_atable,3,((s16*)&value)[1]);break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x17B);fadeSet(3,0.5f);w->step=1;}break;}}
extern "C" s32 menuTitleOptionCursorControl(tagWINDOW_WORK *w){u32 value=*(u32*)&w->first;windowGetKeyInfo();u16 keys=windowGetKeyRepeat();_menuTitleOptionSetFrameSec();_menuTitleOptionCalcRot();menuCursorNormal(w,1);switch(((s16*)&value)[1]){case 0:if(keys&4){menuPlaySe(w->menu,1);GSsndSetOutputMode(1);}if(keys&8){menuPlaySe(w->menu,1);GSsndSetOutputMode(0);}break;case 1:if(keys&4){menuPlaySe(w->menu,1);if(gamedatasaveGetStatus(0,9)!=0)GSinputMotorStart(1,0,255,30,0);gamedatasaveSetStatus(0,9,0);_menuTitleOptionWork.cycles=1;_menuTitleOptionWork.timer=1.0f;_menuTitleOptionWork.direction=1;}if(keys&8){menuPlaySe(w->menu,1);gamedatasaveSetStatus(0,9,1);_menuTitleOptionWork.amplitude=0.0f;}break;}return 0;}
static void _menuTitleOptionSetFrameSec(){_menuTitleOptionWork.dt=timeGetLastFrameSec();_menuTitleOptionWork.frame+=_menuTitleOptionWork.dt;if(_menuTitleOptionWork.frame>=1.0f)_menuTitleOptionWork.frame=0.0f;if(gamedatasaveGetStatus(0,9)==1){if(_menuTitleOptionWork.timer!=0.0f){_menuTitleOptionWork.timer+=_menuTitleOptionWork.dt;if(_menuTitleOptionWork.timer>=1.0f){_menuTitleOptionWork.timer=0.0f;_menuTitleOptionWork.cycles=0;}}}else{_menuTitleOptionWork.timer+=_menuTitleOptionWork.dt;if(_menuTitleOptionWork.timer>=1.0f){_menuTitleOptionWork.timer=0.0f;_menuTitleOptionWork.cycles++;if(_menuTitleOptionWork.cycles%2==0){_menuTitleOptionWork.direction^=1;if(_menuTitleOptionWork.direction)_menuTitleOptionWork.amplitude=0.0f;else _menuTitleOptionWork.amplitude=0.20943952f;}}}}
static void _menuTitleOptionCalcRot(){_menuTitleOptionWork.rotation=_menuTitleOptionWork.amplitude*(f32)sin(6.2831855f*_menuTitleOptionWork.timer*_menuTitleOptionWork.frequency);}
extern "C" void menuTitleOptionHook(tagWINDOW_WORK *w,tagSPRITE_WORK *sprite){u32 value=*(u32*)&w->first;if(w->phase>=3)return;switch(sprite->id){
case 0x5B:if((u32)GSsndGetOutputMode()!=0){winSpriteSetDisp(sprite,1);if(((s16*)&value)[1]==0)menuTitleCursorAnime(w,sprite);else sprite->color.channels.alpha=255;}else winSpriteSetDisp(sprite,0);break;
case 0x5C:if((u32)GSsndGetOutputMode()!=0)winSpriteSetDisp(sprite,0);else{winSpriteSetDisp(sprite,1);if(((s16*)&value)[1]==0)menuTitleCursorAnime(w,sprite);else sprite->color.channels.alpha=255;}break;
case 0x5D:if(gamedatasaveGetStatus(0,9)!=1){winSpriteSetDisp(sprite,1);if(((s16*)&value)[1]==1)menuTitleCursorAnime(w,sprite);else sprite->color.channels.alpha=255;}else winSpriteSetDisp(sprite,0);break;
case 0x5E:if(gamedatasaveGetStatus(0,9)!=1)winSpriteSetDisp(sprite,0);else{winSpriteSetDisp(sprite,1);if(((s16*)&value)[1]==1)menuTitleCursorAnime(w,sprite);else sprite->color.channels.alpha=255;}break;
case 0x5F:if(((s16*)&value)[1]==2){winSpriteSetDisp(sprite,1);menuTitleCursorAnime(w,sprite);}else winSpriteSetDisp(sprite,0);break;
case 0x56:sprite->color.channels.alpha=_atable[0];break;
case 0x57:sprite->color.channels.alpha=_atable[1];break;
case 0x58:sprite->color.channels.alpha=_atable[2];break;
case 0x68:if(((s16*)&value)[1]>=0)GSmsgPrint2(w->layer,0,-8,w->alpha|0xFFFFFF00,_menuOptionMsgTable[((s16*)&value)[1]]);break;
}}
extern "C" void menuTitleOption(){s32 state=0,run=1,oldOutput,oldVibration;_menuTitleOptionInit();do{switch(state){case 0:{oldOutput=GSsndGetOutputMode();oldVibration=gamedatasaveGetStatus(0,9);for(;;){s32 result=menuOpen(0x117,1);tagWINDOW_WORK *w=windowSearchID(0x117);s16 selected=w->selected;if(result<0){GSsndSetOutputMode(oldOutput);gamedatasaveSetStatus(0,9,oldVibration);}else if(w && selected!=2)continue;break;}state=100;break;}case 100:if(oldVibration!=gamedatasaveGetStatus(0,9) && memcardIsMemCardValid()){winMsgOpen(1,0x4457,1,1);if(menuSubOpenYesNo(0,0x3C,0xDC,1)==0)memcardTaskCall(7,2,0);winMsgClose(1);}run=0;break;}}while(run);fn_800A3A1C();_menuTitleOptionClose(0x117);fadeCheck(1);_menuTitleOptionExit();}
extern "C" void menuTitleOptionButton(tagWINDOW_WORK *w){if(w->selected==2){menuButtonNormal(w);return;}if(windowGetKeyInfo()[2]&0x20){w->finished=1;w->cancelled=1;}}
static void _menuTitleOptionClose(s32 id){menuCloseCustom(id,0,1);}
static void _menuTitleOptionExit(){}
static void _menuTitleOptionInit(){menuToolSetSelect(0);_menuTitleOptionWork.field0=0;_menuTitleOptionWork.field14=0.0f;_menuTitleOptionWork.rotation=0.0f;_menuTitleOptionWork.field4=0;_menuTitleOptionWork.timer=0.0f;_menuTitleOptionWork.frequency=3.0f;_menuTitleOptionWork.amplitude=0.20943952f;_menuTitleOptionWork.cycles=0;_menuTitleOptionWork.direction=0;menuPdaSubInitAlpha(_atable,3,0,&_menuTitleOptionWork,3.0f,0.0f);}
