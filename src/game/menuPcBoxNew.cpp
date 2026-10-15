#include <game/menuPcBoxNewPrivate.hpp>
#include <libc/string.h>
extern "C" {void *memcardMemAllocForSavedata();void *memcardMemFreeForSavedata(void*);void *savedataGetStatus(void*,s32);s32 gamedataGetStatus(void*,s32);void pokemonCreate(Pokemon*,u16,u32,s32);void winSeqSetMenu(s32,s32);s32 windowGetValue(s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);}
void menuPocketSetDarkPokemon(Pokemon&,f32,u16);
void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK*,tagSPRITE_WORK*,u32);
namespace {
struct PcBoxConfig {u32 kind,title,info,items[4];};
class CmenuPcBox:public CMetaMenu {public:PcBoxConfig *config;u8 reliveLoaded,boxLoaded;u8 pad33E[2];void *backup;u32 field344,field348;MenuPtWorkSound sound;void main(CMenuGlobalState::enumCallFrom);void loop();void ctrl(tagWINDOW_WORK*);void drawItemText(tagWINDOW_WORK*,tagSPRITE_WORK*,long);void drawInfo(tagWINDOW_WORK*,tagSPRITE_WORK*);void drawTitle(tagWINDOW_WORK*,tagSPRITE_WORK*);void drawRedBar(tagWINDOW_WORK*,tagSPRITE_WORK*,long);void tutorialPokemonSetup();void tutorialPokemonRecover();virtual void drawAll();};
typedef char PcBoxObjectSize[sizeof(CmenuPcBox)==0x358?1:-1];
typedef char MenuGlobalStateSize[sizeof(CMenuGlobalState)==0x208?1:-1];
static CMenuGlobalState _menuGlobalState;
static CmenuPcBox _menuPcBox;
static long localWindowTable[]={0};
void CmenuPcBox::tutorialPokemonRecover(){memcpy(savedataGetStatus(0,0),backup,0x27FD0);backup=memcardMemFreeForSavedata(backup);}
void CmenuPcBox::tutorialPokemonSetup(){static u16 _darkPokemonTbl[]={10,1};static u16 _pokemonTbl[]={0x14A,0x173,0x141,0x148,0x132,0x151,0x15A,0x14F,0x16F,0x14C,0x130,0x15F,0x122,0x140,0x169,0x18B,0x178,0x163};Pokemon p;backup=memcardMemAllocForSavedata();memcpy(backup,savedataGetStatus(0,0),0x27FD0);PCBOX::getPointer()->init();CReliveHall::getPointer()->init();u32 i=0;u16 *normal=_pokemonTbl;u16 *dark=_darkPokemonTbl;do{pokemonCreate(&p,*normal,25,gamedataGetStatus(0,1));if(i<2)menuPocketSetDarkPokemon(p,0.5f,*dark);PCBOX::getPointer()->setPokemon(&p,0,i);normal++;dark++;i++;}while(i<18);}
void CmenuPcBox::ctrl(tagWINDOW_WORK *w){switch(w->mode){case 0:if(!w->sub){winSeqSetMenu(w->id,0x1C4);w->sub=1;}break;case 3:if(!w->sub){winSeqSetMenu(w->id,0x1C8);w->sub=1;}break;}}
void CmenuPcBox::drawItemText(tagWINDOW_WORK*,tagSPRITE_WORK *s,long index){s->message=config->items[index];}
void CmenuPcBox::drawInfo(tagWINDOW_WORK*,tagSPRITE_WORK *s){s->message=config->info;}
void CmenuPcBox::drawTitle(tagWINDOW_WORK *w,tagSPRITE_WORK *s){menuPtSpriteWorkSetMenuItem(w,s,config->title);}
void CmenuPcBox::drawRedBar(tagWINDOW_WORK *w,tagSPRITE_WORK *s,long index){winSpriteSetDisp(s,index==windowGetValue(w->id));}
void CmenuPcBox::drawAll(){}
}
u8 menuReliveHallTutorialGetIsCancelExit(){return ((u8*)&_menuGlobalState)[0x15E];}
extern "C" {
void menuReliveHallTutorialExit(){}void menuReliveHallTutorialMain(){_menuPcBox.main(CMenuGlobalState::Tutorial);}void menuReliveHallTutorialInit(){}
void menuHologramExit(){}void menuHologramMain(){_menuPcBox.main(CMenuGlobalState::Hologram);}void menuHologramInit(){}
void menuReliveHallExit(){}void menuReliveHallMain(){_menuPcBox.main(CMenuGlobalState::Relive);}void menuReliveHallInit(){}
void menuPcBoxExit(){}void menuPcBoxMain(){_menuPcBox.main(CMenuGlobalState::Pc);}void menuPcBoxInit(){}
s32 menuPcBoxSelectMenuItem(){return 0;}
s32 menuPcBoxCtrl(tagWINDOW_WORK *w){_menuPcBox.ctrl(w);return 0;}
s32 menuPcBoxItem3(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,3);return 0;}
s32 menuPcBoxItem2(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,2);return 0;}
s32 menuPcBoxItem1(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,1);return 0;}
s32 menuPcBoxItem0(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawItemText(w,s,0);return 0;}
s32 menuPcBoxInfo(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawInfo(w,s);return 0;}
s32 menuPcBoxTitle(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawTitle(w,s);return 0;}
s32 menuPcBoxBarRed3(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,3);return 0;}
s32 menuPcBoxBarRed2(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,2);return 0;}
s32 menuPcBoxBarRed1(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,1);return 0;}
s32 menuPcBoxBarRed0(tagWINDOW_WORK *w,tagSPRITE_WORK *s){_menuPcBox.drawRedBar(w,s,0);return 0;}
}
