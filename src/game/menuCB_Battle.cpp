#include <dolphin/types.h>
struct Hero;
struct _MENUCBWORK {u8 bytes[0xB4C0];};
extern u8 _CB[];
static const u16 VS_TRAINER_RANK_NUMBER[40]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40};
static const u16 VS_TRAINER_RANK_ENCOUNT_DATA[40]={15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54};
extern "C" {void GSflagOff(u32);u16 fightEncount(u16);void soundGetBGMID();void soundStop(s32);void menuTitleBattleSelectFree();void menuCB_SetToolBattleModeFlag(s32);void menuTitleReadWazaSelectMenu();}
extern "C" u16 menuCB_Battle(_MENUCBWORK *work){u16 id;if(*(s32*)(_CB+4)==1)id=VS_TRAINER_RANK_ENCOUNT_DATA[*(u16*)(work->bytes+0x2654)];else switch(*(s32*)(work->bytes+8)){case 0:id=5;break;case 1:id=7;break;case 2:id=8;break;}GSflagOff(0x323);soundGetBGMID();soundStop(0);menuTitleBattleSelectFree();menuCB_SetToolBattleModeFlag(1);u16 result=fightEncount(id);menuCB_SetToolBattleModeFlag(0);menuTitleReadWazaSelectMenu();return result;}
static void _menuCBBattle_DeleteAllItem(Hero*){}
