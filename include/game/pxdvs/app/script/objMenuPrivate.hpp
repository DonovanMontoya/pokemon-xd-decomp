#ifndef APP_SCRIPT_OBJ_MENU_PRIVATE_HPP
#define APP_SCRIPT_OBJ_MENU_PRIVATE_HPP
#include <game/pxdvs/app/script/appScriptPrivate.hpp>
extern "C" {
s32 winMsgOpenField(s32,u8,u8);s32 winMsgOpenFieldWithSE(s32,u8,u8,u8);void winMsgCloseField(u8);
s32 winMsgOpenFight(s32,u8,u8);void winMsgCloseFight(u8);
s8 menuSubOpenYesNoField();s8 menuSubOpenYesNo(u8,s16,s16,s32);s32 menuSubOpenColosseumEnter(s32);
s32 menuOpen(s32,u8);void menuClose(s32);s32 menuGetCursor(s32);s32 menuSetCursor(s32,s32);
void msgctrlSetValue(s32,u32);s32 menuSubOpenSelect2(u8,s32 *,s32,s32,s32,s32,s32,u8);
s32 menuPokemonOpen(u8,u16,void *);s32 menuPokemonStatus();s32 menuPokemonStatusOpenWazaList(u8);
s32 menuNameEntryOpen(s32,s32);void menuNameEntry();void menuShopOpen(s32);void menuPda();void menuPokemonChange();
void peopleBlock();void peopleUnblock();void scriptOpenItemMenu();
u8 menuSubOpenNumberInputDigit(s32,s32 *);s32 menuScriptTutorial();s32 menuScriptEevee();
void menuScriptOpenWorldMap(u16);void menuIntUnderTakerMenuOpen();void menuIntUnderTakerMenuClose();
void menuScriptUsohachi();void menuScriptUsohachi2();s32 menuScriptWazaMeijin(s32);s32 menuScriptWazaBasan(s8 *);
void menuScriptSetWazaOboetaFlag(u16);void menuScriptMoneyOpen(s16,s16);void menuScriptMoneyClose();u8 menuScriptWazaBasanCheck();
void menuScriptCouponOpen(s8,s8);void menuScriptCouponClose();void menuOrreColosseum(u16);u16 menuOrreColosseumGetResult();
void menuScriptPdaAddFunc(s32);void menuPocket2AddItemScript(s32,s32);s32 mewWazaSequence();u16 mewWazaGet(s32);
}
static inline GSscript::tigaArrayFixed *menuScriptArray(GSscript::tigaVariant *v) {
 if(v->type==7)return (GSscript::tigaArrayFixed*)v->value.pointer;
 GSscript::tigaErrMessage("pokemon not access");return 0;
}
#endif
