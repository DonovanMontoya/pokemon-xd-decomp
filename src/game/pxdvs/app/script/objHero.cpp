#include <game/pxdvs/app/script/objHeroPrivate.hpp>
#define I(N) appScriptGetInt(&args[N])
#define V(N) appScriptGetVec(&args[N])
#define R(EXPR) appScriptSetInt(result,(EXPR))
int AppScript::cmpHero(int method,GSscript::tigaVariant *args,GSscript::tigaVariant *result) {
    GSvec *start;
    Hero *hero=getHeroPtr__4HeroFv();
    s32 parts[6];s32 motions[7];
    switch(method) {
    case 0x10:{start=V(1);GSvec *b=V(2);R(heroMoveInit(start,b));break;}
    case 0x11:R(heroMoveMain());break;
    case 0x12:heroMoveInitEvent();break;
    case 0x13:heroMoveTermEvent();break;
    case 0x14:{s32 a=I(1),b=I(2),c=I(3),d=I(4),e=I(5);heroMoveAddAutoEvent(a,b,c,d,e);break;}
    case 0x15:scriptPartyChange((bool)I(1));break;
    case 0x16:{s32 a=I(1),b=I(2);R(heroMoveSetNeckMode(a,b));break;}
    case 0x17:R(scriptCheckHizukiFollow());break;
    case 0x18:{s32 a=I(1),b=I(2),c=I(3);R(scriptHeroCtrlElevator(a,b,c,I(4)));break;}
    case 0x19:{GSresID *p=heroScriptPeople(&args[1]);R(scriptHizukiAway(p->group,p->id));break;}
    case 0x1A:{s32 a=I(1),b=I(2);R(scriptGetItem(a,b));break;}
    case 0x1B:{s32 a=I(1),b=I(2);R(scriptAddItem(a,b));break;}
    case 0x1C:R(scriptHaveItem(I(1)));break;
    case 0x1D:R(scriptAddPokedoru(I(1)));break;
    case 0x1E:R(scriptGetPokedoru());break;
    case 0x1F:R(scriptGetPremium());break;
    case 0x20:scriptSetPremium(I(1));break;
    case 0x21:R(scriptAddPremium(I(1)));break;
    case 0x22:R(scriptGetPokemonNum());break;
    case 0x23:R(scriptGetDarkPokemonNum());break;
    case 0x24:{s32 index=I(1);strncpy((char *)workBuffer+0x38,scriptGetPokemonNickName(index),255);AppScriptWork *w=work();w->ret.value.string=(char *)w+0x38;work()->ret.type=3;break;}
    case 0x25:R(scriptCatchPokemon(I(1)));break;
    case 0x26:R(scriptGetDarkPointZeroPokemonNum());break;
    case 0x27:recoveryPokemon();break;
    case 0x28:R((bool)scriptBattleMountainEnd((bool)I(1)));break;
    case 0x29:R(heroGetLivingPokemonCount());break;
    case 0x2A:R(heroGetEmptySlot());break;
    case 0x2B:R(heroGetPokeomCount());break;
    case 0x2C:appScriptSetVar(result,0x25,getPokemon__4HeroFl(hero,(u16)I(1)));break;
    case 0x2D:R(heroIsMinePokemon(hero,appScriptGetPokemon(&args[1])));break;
    case 0x2E:peopleChangeFollower(I(1));break;
    case 0x2F:R(heroGetFollower());break;
    case 0x30:{GSresID *p=heroScriptPeople(&args[1]);s32 mode=I(2);heroSetFollower(p->group,p->id,mode);break;}
    case 0x36:{s32 a=I(1),b=I(2);heroSetFollowerWithID(a,b);}
    case 0x31:R(darkPokemonGetSnatchSuccessNum());break;
    case 0x32:heroMoveSlowStop();break;
    case 0x33:R(isReliveReadyPokemonExist__11CReliveHallFv(getPointer__11CReliveHallFv()));break;
    case 0x34:R(isPokemonFull__5PCBOXFv(getPointer__5PCBOXFv()));break;
    case 0x35:R(getLegendPokemonSize__4HeroCFv(hero));break;
    case 0x37:scriptStoreTemochiPokemon();break;
    case 0x38:R(scriptCheckTemochiPokemon());break;
    case 0x39:recoveryEventCommon(I(1));break;
    case 0x3A:
        for(u16 i=0;i<6;++i)parts[i]=appScriptGetInt(heroScriptArray(&args[2])->get(i));
        for(u16 i=0;i<7;++i)motions[i]=appScriptGetInt(heroScriptArray(&args[3])->get(i));
        recoveryEventPC(0,0,I(1),parts,motions);break;
    case 0x3B:R(darkPokemonGetReliveNum());break;
    case 0x3C:R(scriptGetEarthRibbon());break;
    case 0x3D:R(scriptGetPoint());break;
    case 0x3E:scriptSetPoint(I(1));break;
    case 0x3F:scriptAddPoint(I(1));break;
    case 0x40:R(darkpokemonBiosGetScenarioNum());break;
    case 0x41:{s32 a=I(1),b=I(2);setHeroStyle__4HeroFUcb(hero,a,(bool)b);break;}
    case 0x42:heroMoveSetSmoothFloorLink((bool)I(1));break;
    case 0x43:{s32 a=I(1),b=I(2),c=I(3),d=I(4);R(floorEventGetTresureEx(a,b,c,(bool)d));break;}
    case 0x44:R(pcBoxAllSearchPokemon(I(1)));break;
    case 0x45:R(deletePokemon__4HeroFl(hero,I(1)));break;
    }
    return 0;
}
#undef I
#undef V
#undef R
