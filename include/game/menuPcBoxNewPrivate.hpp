#ifndef MENU_PCBOX_NEW_PRIVATE_HPP
#define MENU_PCBOX_NEW_PRIVATE_HPP
#include <dolphin/types.h>
struct tagWINDOW_WORK {u8 pad0;s8 mode,sub;u8 pad3;s32 id;};
struct tagSPRITE_WORK {u8 pad0[0x4C];u32 message;};
struct Pokemon {u8 data[0xC4];};
struct MenuPtWorkSound {u32 bgm,env;u8 volume[4];};
class CMenuGlobalState {public:enum enumCallFrom {Pc,Relive,Hologram,Tutorial};enumCallFrom from;u8 data[0x204];void init();};
class CMetaMenuBase {public:union{u8 bytes[0x330];u64 alignment;};};
class CMetaMenu:public CMetaMenuBase {public:virtual void drawAll()=0;virtual bool isAnimationStateNone();virtual void updateAll();virtual void tutorialExitKick();void localWindowSetTable(long*);void localWindowCreateAll();void localWindowDeleteAll();static long defautlLocalWindowOpenTable[];};
class PCBOX {public:static PCBOX *getPointer();void init();void setPokemon(Pokemon*,signed char,signed char);};
class CReliveHall {public:static CReliveHall *getPointer();void init();void allocMakeBackup();void checkWithBackupSet();};
#endif
