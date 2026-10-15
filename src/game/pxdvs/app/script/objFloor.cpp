#include <game/pxdvs/app/script/objFloorPrivate.hpp>
#define I(N) appScriptGetInt(&args[N])
#define F(N) appScriptGetFloat(&args[N])
#define V(N) appScriptGetVec(&args[N])
#define R(E) appScriptSetInt(result,(E))
int AppScript::cmpFloor(int method,GSscript::tigaVariant *args,GSscript::tigaVariant *result) {
    GSvec position;f32 rotation;
    Hero *hero=getHeroPtr__4HeroFv();
    switch(method) {
    case 0x10:R(GSfloorGetCurrent());break;
    case 0x11:R(floorGetCurrentGroupID());break;
    case 0x12:R(floorGetPrevFloorID());break;
    case 0x13:R(floorGetNextFloorID());break;
    case 0x14:R(floorGetNextPosIndex());break;
    case 0x15:setBattleResumeFloorID__4HeroFUi(hero,I(1));setBattleResumeFloorIndex__4HeroFUc(hero,I(3));break;
    case 0x16:{s32 a=I(1);floorLink(a,I(2));floorWaitForChange();break;}
    case 0x17:{s32 a=I(1),b=I(2);floorLinkWithSE(a,b,I(3));floorWaitForChange();break;}
    case 0x18:{s32 a=I(1),b=I(2);R(floorEventCtrlDoor(a,b,I(3)));break;}
    case 0x19:{s32 a=I(1),b=I(2);R(floorEventCtrlElevator(a,b,I(3),0,0));break;}
    case 0x29:{GSresID *p=floorScriptPeople(&args[4]);s32 a=I(1),b=I(2);R(floorEventCtrlElevator(a,b,I(3),p->group,p->id));break;}
    case 0x1A:{s32 a=I(1);floorEventSetTresureDisp(a,(bool)I(2));break;}
    case 0x1B:{s32 a=I(1),b=I(2);R(floorEventChangeTresure(a,b,I(3)));break;}
    case 0x1C:{s32 a=I(1);R(scriptFloorCharSetDisp(a,I(2)));break;}
    case 0x1D:{s32 a=I(1);f32 x=F(2),y=F(3);R(scriptFloorCharSetPos(a,x,y,F(4)));break;}
    case 0x1E:{s32 a=I(1);floorSetFadeScript(a,I(2));break;}
    case 0x1F:setBattleResumeFloorID__4HeroFUi(hero,I(1));setBattleResumeFloorIndex__4HeroFUc(hero,I(3));break;
    case 0x20:setBattleResumeFloorID__4HeroFUi(hero,I(1));setBattleResumeFloorIndex__4HeroFUc(hero,I(3));break;
    case 0x21:floorClearReturnPoint();break;
    case 0x22:R(floorSetOffscreenIndex(I(1)));floorOffscreenPlayWait();break;
    case 0x23:{GSvec *v=V(1);R(scriptFloorCharSetPos(I(1),v->param1,v->param2,v->param3));break;}
    case 0x25:menuTitle();break;
    case 0x24:menuWorldMapMXMain();break;
    case 0x26:GSfloorPush(I(1));floorWaitForChange();break;
    case 0x27:GSfloorPush(0x3A6);floorWaitForChange();break;
    case 0x28:GSfloorPush(0x3A3);floorWaitForChange();break;
    case 0x2A:{s32 a=I(1);f32 x=F(2),y=F(3),z=F(4);floorChangePos(a,I(5),x,y,z);break;}
    case 0x2B:GSfloorPush(0x3A7);floorWaitForChange();break;
    case 0x2C:menuBattleDeBingo();floorWaitForChange();break;
    case 0x2D:R(menuBattleDeBingoGetResult());break;
    case 0x2E:R(menuBattleDeBingoGetLine());break;
    case 0x2F:
        if(floorDataBiosGetPosListData(I(1),&position,0)==0){R(0);return 1;}
        appScriptCopyVec(&work()->vec,&position.param1);
        work()->ret.value.vector=&work()->vec;work()->ret.type=4;break;
    case 0x30:
        if(floorDataBiosGetPosListData(I(1),0,&rotation)==0){R(0);return 1;}
        appScriptSetFloat(result,rotation);break;
    case 0x31:{s32 a=I(1);floorLink(a,I(2));s32 b=I(3);floorSetFadeScript(b,I(4));floorWaitForChange();break;}
    case 0x32:{s32 a=I(1),b=I(2),c=I(3),d=I(4),e=I(5);floorMoviePlay(a,(bool)b,(bool)c,d,e,I(6));floorOffscreenPlayWait();break;}
    case 0x33:menuBattleDiskOpen();floorWaitForChange();break;
    case 0x34:R(menuBattleDiskGetSelectID());break;
    case 0x35:R(menuBattleDiskGetResult());break;
    case 0x36:R(menuBattleDeBingoGetNum());break;
    case 0x37:R(menuBattleDeBingoGetEpoint());break;
    case 0x38:R(menuBattleDeBingoGetMball());break;
    case 0x39:R(isReliveReadyDarkLugiaExist__11CReliveHallFv(getPointer__11CReliveHallFv()));break;
    case 0x3A:{s32 id=I(1);floorRegisterLight(floorGetCurrentGroupID(),id);break;}
    case 0x3B:{s32 id=I(1);floorRegisterCamera(floorGetCurrentGroupID(),id);break;}
    case 0x3C:menuBattleDiskOpenFight();floorWaitForChange();break;
    case 0x3D:floorReleaseOffscreen();break;
    case 0x3E:R(menuReliveHallTutorialGetIsCancelExit());break;
    case 0x3F:menuMoveDemo(I(1));break;
    case 0x40:R(isReliveReadyDarkLugiaExist__11CReliveHallFv(getPointer__11CReliveHallFv()));break;
    case 0x41:R(menuBattleDeBingoGetMode());break;
    case 0x42:R(getReliveReadyVisitorQuantity__11CReliveHallFv(getPointer__11CReliveHallFv()));break;
    case 0x43:{f32 a=F(1);GSmodelSetShadowDistLimits(a,F(2));break;}
    }
    return 0;
}
#undef I
#undef F
#undef V
#undef R
