#ifndef APP_SCRIPT_OBJ_FLOOR_PRIVATE_HPP
#define APP_SCRIPT_OBJ_FLOOR_PRIVATE_HPP
#include <game/pxdvs/app/script/appScriptPrivate.hpp>
inline GSvec::GSvec() {}
extern "C" {
Hero *getHeroPtr__4HeroFv();
void setBattleResumeFloorID__4HeroFUi(Hero *,u32);void setBattleResumeFloorIndex__4HeroFUc(Hero *,u8);
void *getPointer__11CReliveHallFv();u8 isReliveReadyDarkLugiaExist__11CReliveHallFv(void *);s32 getReliveReadyVisitorQuantity__11CReliveHallFv(void *);
s32 GSfloorGetCurrent();void GSfloorPush(s32);
s32 floorGetNextFloorID();s32 floorGetNextPosIndex();s32 floorGetPrevFloorID();
void floorClearReturnPoint();void floorLink(s32,s32);void floorLinkWithSE(s32,s32,s32);void floorWaitForChange();
s32 floorEventCtrlDoor(s32,s32,u8);s32 floorEventCtrlElevator(s32,s32,u16,u32,u32);
void floorEventSetTresureDisp(s32,u8);s32 floorEventChangeTresure(s32,u16,u8);
s32 scriptFloorCharSetDisp(s32,s32);s32 scriptFloorCharSetPos(s32,f32,f32,f32);
void floorSetFadeScript(s32,s32);u8 floorSetOffscreenIndex(s32);void floorOffscreenPlayWait();void floorReleaseOffscreen();
void floorChangePos(s32,s16,f32,f32,f32);u8 floorDataBiosGetPosListData(s32,GSvec *,f32 *);
void floorMoviePlay(s32,u8,u8,s32,u16,u16);void floorRegisterLight(u32,s32);void floorRegisterCamera(u32,s32);
void menuTitle();void menuWorldMapMXMain();void menuBattleDeBingo();void menuBattleDiskOpen();void menuBattleDiskOpenFight();
s32 menuBattleDiskGetSelectID();s32 menuBattleDiskGetResult();void menuMoveDemo(s32);
u8 menuBattleDeBingoGetResult();u8 menuBattleDeBingoGetLine();u8 menuBattleDeBingoGetNum();u8 menuBattleDeBingoGetEpoint();u8 menuBattleDeBingoGetMball();u8 menuBattleDeBingoGetMode();
void GSmodelSetShadowDistLimits(f32,f32);
}
u8 menuReliveHallTutorialGetIsCancelExit();
static inline GSresID *floorScriptPeople(GSscript::tigaVariant *v) {
 if(v->type==0x23)return (GSresID*)v->value.pointer;
 GSscript::tigaErrMessage("people not access");return 0;
}
#endif
