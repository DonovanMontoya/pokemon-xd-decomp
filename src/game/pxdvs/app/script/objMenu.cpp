#include <game/pxdvs/app/script/objMenuPrivate.hpp>
#define I(N) appScriptGetInt(&args[N])
#define R(E) appScriptSetInt(result,(E))
int AppScript::cmpMenu(int method,GSscript::tigaVariant *args,GSscript::tigaVariant *result) {
    s32 selections[128];s32 number;s8 learned;
    switch(method) {
    case 0x10:{s32 a=I(1),b=I(2),c=I(3);R(winMsgOpenField(a,(bool)b,(bool)c));break;}
    case 0x11:{s32 a=I(1),b=I(2),c=I(3),d=I(4);R(winMsgOpenFieldWithSE(a,(bool)b,(bool)c,d));break;}
    case 0x12:winMsgCloseField((bool)I(1));break;
    case 0x13:{s32 a=I(1),b=I(2),c=I(3);R(winMsgOpenFight(a,(bool)b,(bool)c));break;}
    case 0x14:winMsgCloseFight((bool)I(1));break;
    case 0x15:R(menuSubOpenYesNoField());break;
    case 0x16:{s32 a=I(1),b=I(2),c=I(3);R(menuSubOpenYesNo(a,b,c,I(4)));break;}
    case 0x17:R(menuSubOpenColosseumEnter(I(1)));break;
    case 0x18:{s32 a=I(1);R(menuOpen(a,(bool)I(2)));break;}
    case 0x19:menuClose(I(1));break;
    case 0x1A:R(menuGetCursor(I(1)));break;
    case 0x1B:{s32 a=I(1);R(menuSetCursor(a,I(2)));break;}
    case 0x1C:
        if(I(1)==0x4D) msgctrlSetValue(0x4D,(u32)GSmsgGetGSchar(I(2)));
        else switch(args[2].type) {
        case 37:{s32 a=I(1);msgctrlSetValue(a,(u32)appScriptGetPokemon(&args[2]));break;}
        case 1:{s32 a=I(1);msgctrlSetValue(a,I(2));break;}
        case 8:{s32 a=I(1);char *text;if(args[2].type==8)text=args[2].value.string;else text=args[2].getCnvString((char *)field954);msgctrlSetValue(a,(u32)text);break;}
        case 2:{s32 a=I(1);msgctrlSetValue(a,(u32)appScriptGetFloat(&args[2]));break;}
        }
        break;
    case 0x1D:
        if(I(2)>=128){R(0);return 1;}
        for(s32 i=0;i<I(2);++i)selections[i]=appScriptGetInt(menuScriptArray(&args[1])->get(i));
        {s32 count=I(2),x=I(3),y=I(4),start=I(5);R(menuSubOpenSelect2(0,selections,count,x,y,start,I(2),1));}break;
    case 0x20:R(menuPokemonOpen(6,0,0));break;
    case 0x21:R(menuPokemonOpen(6,0,0));break;
    case 0x22:R(menuPokemonStatus());break;
    case 0x23:R(menuPokemonStatusOpenWazaList(I(1)));break;
    case 0x24:{s32 a=I(1);R(menuNameEntryOpen(a,I(2)));break;}
    case 0x25:menuNameEntry();break;
    case 0x27:peopleBlock();menuShopOpen(I(1));peopleUnblock();break;
    case 0x29:menuPda();break;
    case 0x2A:currentThread->setSaveFlag(false);menuPokemonChange();break;
    case 0x32:scriptOpenItemMenu();break;
    case 0x38:if(menuSubOpenNumberInputDigit(I(1),&number)==1)R(number);else R(-1);break;
    case 0x39:R(menuScriptTutorial());break;
    case 0x3A:R(menuScriptEevee());break;
    case 0x3B:
        if(I(3)>=128){R(0);return 1;}
        for(s32 i=0;i<I(3);++i)selections[i]=appScriptGetInt(menuScriptArray(&args[2])->get(i));
        {s32 kind=I(1),count=I(3),x=I(4),y=I(5),start=I(6),limit=I(7);R(menuSubOpenSelect2(kind,selections,count,x,y,start,limit,(bool)I(8)));}break;
    case 0x3C:GSthreadSwitch();menuScriptOpenWorldMap(I(1));break;
    case 0x3D:menuIntUnderTakerMenuOpen();break;
    case 0x3E:menuIntUnderTakerMenuClose();break;
    case 0x3F:menuScriptUsohachi();break;
    case 0x40:R(menuScriptWazaMeijin(I(1)));break;
    case 0x41:GSthreadSwitch();R(menuScriptWazaBasan(&learned));break;
    case 0x42:GSthreadSwitch();menuScriptSetWazaOboetaFlag(I(1));break;
    case 0x43:{s32 a=I(1);menuScriptMoneyOpen(a,I(2));break;}
    case 0x44:menuScriptMoneyClose();break;
    case 0x45:R(menuScriptWazaBasanCheck());break;
    case 0x46:{s32 a=I(1);menuScriptCouponOpen(a,I(2));break;}
    case 0x47:menuScriptCouponClose();break;
    case 0x48:menuOrreColosseum(I(1));break;
    case 0x49:menuScriptUsohachi2();break;
    case 0x4A:R(menuOrreColosseumGetResult());break;
    case 0x4B:menuScriptPdaAddFunc(I(1));break;
    case 0x4C:{s32 a=I(1);menuPocket2AddItemScript(a,I(2));break;}
    case 0x4D:R(mewWazaSequence());break;
    case 0x4E:R(mewWazaGet(I(1)));break;
    case 0x4F:R(menuPokemonOpen(8,scriptPokemonTeachWazaIndex(I(1)),0));break;
    }
    return 0;
}
#undef I
#undef R
