#include <game/menuCB_Sub1Layout.hpp>
#pragma dont_inline on

s32 pokecoloGetCountryCode(void);
u32 GSmsgGetRect(s32);
u16 *GSmsgGetGSchar(s32);
void GSmsgPrint2(s32,s32,s32,u32,s32);
void msgctrlSetValue(s32, const void *);
void GSsndPlay(s32,s32,s32); void GSsndStop(s32,s32,s32);
u8 menuSubAnimAlpha(void);
MenuSubPokemon *menuCBPokemonPtrGet__FUlUl(u32,u32);
void pokemonAllKaihuku(MenuSubPokemon *);
s32 pokemonGetStatus(MenuSubPokemon *, void *, s32, u16);
u8 pokemonCheckValid(MenuSubPokemon *);
u32 pokemonGetSoubiItemDataId(MenuSubPokemon *);
void GSfsysReadWait(s32); void menuTopOpenFlashBack(void); void menuCB_FlashStart(s32); void menuCB_FlashEnd(s32); void GSthreadSwitch(void);
void menuOpen(s32,s32); void menuCloseCustom(s32,s32,s32); u8 fightReadResourceID(s32,u32); void fightFreeResourceID(s32,u32); void GSfsysFree(s32); void GSresFreeGroup(s32);
void menuSetDisp(s32,s32); void winSpriteSetDisp(void *,s32);
void spriteSetScissor(s32,s32,s32,s16,s16); void spriteClearScissor(s32);
u16 *heroBiosGetNamePtr(void *);
s32 menuCBBattleStartGetStatus(void); u8 menuCBPokemonEntryGetReadFlag(void);
MenuSubPokemon *toolentryTaisenGetPokemonPtr(u32,s32); MenuSubPokemon *toolentryTaisenGetEntryPokemonPtr(u32,s32); u16 toolentryTaisenGetEntryPokemonNum(u32);
s32 menuCBBios_GetTrainerOrgImmediately(void); s32 menuCBTrainerBios_GetHomePlace(void); u8 heroBiosGetSexDataId(s32);
void fadeSet(s32,f32);
void menuCBPokemonEntryDispPokemonFace(s32,s32,s32,s32);
void *itemDataBiosGetPtr(u32); s32 itemDataBiosGetName(void *);
u32 wazaGetStatus(s32,u16,s32,s32);
void GSmsgPrintRight(s32,s32,s32,s32,s32,u32,s32);
u32 zokuseiBiosGetSmallSpriteID(u16); u32 zokuseiGetPokemonSpriteID(s32,s32);
s32 pokemonDataBiosGetPtr(u16); u8 pokemonDataBiosGetZokuseiDataId(s32,s32);
void windowDrawSprite(s16,s16,MenuSubWindow *,u16,s32,s32);
u16 pokemonGetTokuseiDataId(MenuSubPokemon *); void *pokemonTokuseiDataBiosGetPtr(u16); s32 pokemonTokuseiDataBiosGetName(void *);
u16 pokemonBiosGetHp(MenuSubPokemon *); u8 pokemonBiosGetTamagoFlag(MenuSubPokemon *);
u16 pokemon_GetPokemonDataId(MenuSubPokemon *); s32 pokemonDB_GetName(u16);
u8 menuSubGetPokemonSexForFightDisp(MenuSubPokemon *); u8 menuSubGetPokemonSexForDisp(MenuSubPokemon *);
u16 *pokemonBiosGetNicknamePtr(MenuSubPokemon *);
void _menuCB_PokemonStatusDispAfterJob__FUl(u32 arg0);
void _menuCB_PokemonStatusDispBeforeJob__FUl(u32 arg0);
s32 menuCBPokemonEntryDispPokemonFace_AFTER(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 menuCBPokemonEntryDispPokemonFace_BEFORE(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void menuCB_BattleEntryPokemonSelectDisp(MenuSubSprite *arg0, u32 arg1, u32 arg2);
s32 menuCB_GCStatusDispMode(MenuSubSprite *arg0, s32 arg1);
u8 menuCBPokemonCheck();
void menuCBPokemonItemName(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonWazaNAME(MenuSubWindow *arg0, u32 arg1, u32 arg2, u32 arg3);
void menuCBPokemonWazaTYPE(MenuSubWindow *arg0, u32 arg1, u32 arg2, u32 arg3);
void menuCBPokemonTYPE1(MenuSubWindow *arg0, u32 arg1, u32 arg2);
void menuCBPokemonTYPE2(MenuSubWindow *arg0, u32 arg1, u32 arg2);
void menuCBPokemonStatusDisp(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3, s32 arg4);
void menuCBPokemonTOKUSEI(MenuSubWindow *arg0, u32 arg1, u32 arg2);
void menuCBPokemonHP(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonLevel(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonNameOrg(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonSexOnly(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonNameOnly(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void _menuCBPokemonName__FP14tagWINDOW_WORKUlUlUlb(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3, u8 arg4);
void menuCBPokemonName(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCBPokemonName_nido(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3);
void menuCB2DPokemonItemDisp(MenuSubWindow *arg0, u32 arg1, u32 arg2);
void *memcpy(void *, const void *, u32); void *memset(void *,int,u32);
void initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(MenuSubAnt *, MenuSubPokemon *);
void setAnimation__4CAntFl(MenuSubAnt *,s32); void use__4CAntFv(void *);
void systemUsecountReset__4CAntFv(void); void systemUnUseResourceRelease__4CAntFv(void);
void winMsgOpen(s32,s32,s32,s32); void winMsgClose(s32); MenuSubKey *windowGetKeyInfo(void);
u16 toolentryTaisenGetHomePlace(u32); void *getPointer__5PCBOXFv(void); u16 *getPokemonBoxName__5PCBOXFSc(void *,s8);
u8 pauseIsPause(void); u8 menuCB_BattleStartSoundCheck(void); u8 FlashSystemIsLastFrame(u32); void winSeqSetMenu(s32,s32);
#pragma force_active on
static MenuSubAnt ant[36]; static MenuSubAnt antR[30]; static MenuSubAnt antL[30];
#pragma force_active reset
static u16 battleEndHPStartFlag; static u16 battleEndHPEndFlag;
void _menuCB_ErrorTAMAGOCheck__Fv(void);
void _menuCB2DPokemonNewSet2__FUlUlUlUc(u32 arg0, s32 arg1, u32 arg2, u8 arg3);
void _menuCB2DPokemonNewSet__FUc(u8 arg0);
void _menuCB_errorMsgDisp2__FUl(s32 arg0);
void _menuCB_errorMsgDisp__FUl(s32 arg0);
u8 menuCBPokemonEntryDisp(MenuSubWindow *arg0);
void menuCBGCEntryTypeIndex(void);
void menuCBReliveHallCursolInit(void);
void menuCBPCBOXTitleNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s8 arg2, s32 arg3);
void menuCB2DPokemonClearSHIFT(u32 arg0);
void menuCB2DPokemonALLClear(void);
void menuCB_DispEffect(MenuSubWindow *arg0);
s32 menuCBBattleBANextMenu(MenuSubWindow *arg0);
s32 menuCB_BattleBA_PokemonEntryNum(void);
void *savedataGetStatus(s32,s32); MenuSubPokemon *heroBiosGetPokemonPtr(void *,u16);
MenuSubPokemon *getPokemon__5PCBOXFScSc(void *,s8,s8);
void *getPointer__11CReliveHallFv(void); void *getStage__11CReliveHallFl(void *,u32);
MenuSubPokemon *getVisitorPointer__12CReliveStageFv(void *); MenuSubPokemon *getDancerPointer__12CReliveStageFl(void *,u32);

s32 winSpriteGetLayerID(MenuSubWindow*,MenuSubSprite*); MenuSubItem *menuItemBiosGetPtr(s32,s16);
u16 menuCBRule_RegulationItemID(s32); u8 itemDataCheckValid(u32);
void menuPokemonStatusOpenFromPokemonChange(MenuSubPokemon *,s32,s32);
void menuCB_RuleMessageTblDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void menuCB_RuleItemFlagDisp(MenuSubWindow *arg0, MenuSubSprite *arg1);
void menuCB_RuleItemNameEntry(MenuSubWindow *arg0, MenuSubSprite *arg1);
void menuCBRuleNumberDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2);
void menuCBRULE_EditNameDispLarge(MenuSubWindow *arg0, s32 arg1);
void menuCBRULE_EditNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void menuCB_GCEntry_PokemonStatusDisp(void);
s32 heroItemCheckAddItemDataId(void *,u32); void heroItemAddItemDataId(void *,u32,s32,s32);
s32 heroItemDecItemDataId(void *,u16,s32,u8); u32 pokemonDoItemSoubi(MenuSubPokemon *,u16,s32);
MenuSubRule *menuCBBios_CurrentRule(void); u16 menuPocket2Call(s32,s32,void *); u8 menuPocket2GetLastSlotID(void);
void menuCBRule_ErrorFlagSetItemGetTiming(void *,MenuSubPokemon *,u32);
s8 menuSubOpenYesNo(s32,s32,s32,s32); u16 pokemonBiosGetMaxHp(MenuSubPokemon *);
void menuCB_SetSprite(MenuSubSprite *,s32); s32 menuSpriteBiosGetPtr(s32); u16 toolentryTaisenGetBattlePlayerID(s32);
static const s32 BATTLE_BA_HP_Bar_Char[3] = {0x000002B8, 0x000002B9, 0x000002BA};
static const s32 BATTLE_BA_FACEWAKU_Char[2] = {0x00000233, 0x00000234};
static const s32 BATTLE_BA_XP_PRINT_Char[4] = {0x0000020F, 0x0000020E, 0x0000020D, 0x0000020C};
static s32 submenurule_msg1[3] = {0x4391, 0x4392, 0x4395};
static s32 submenurule_msg2[4] = {0x4391, 0x4393, 0x4394, 0x4395};
static s32 submenu_msg1[3] = {0x4398, 0x4399, 0x439A};
static s32 submenu_msg2[4] = {0x439B, 0x4399, 0x439C, 0x439A};
static s32 submenu_msg3[3] = {0x439D, 0x439E, 0x439A};
static s16 submenu1_x[30] = {
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28,
    0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28};
static s16 submenu1_y[30] = {
    0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136,
    0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136, 0x136,
    0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64};
static s32 submenu_msg1s[2] = {0x4399, 0x439A};

void menuCB_GCEntry_ItemKeepJob(void);
void menuCB_GCEntry_ItemGiveJob(void);
void menuCBBattleBABatuMark(MenuSubSprite *arg0, s32 arg1, s32 arg2);
void menuCBBattleEndSetPokemonHP(void);
void menuCB_BattleBA_HPBarDispSet(MenuSubSprite *arg0, s32 arg1, s32 arg2);
void menuCB_BattleBA_FacePanelSet(MenuSubSprite *arg0, s32 arg1, s32 arg2);
void menuCB_PrintXP(MenuSubSprite *arg0, s32 arg1);
static s32 err_msgID[14]; static s32 err_msgID2[14]; static u32 backup_type[6]; static u32 backup_index[6];
void pokemonInit(MenuSubPokemon *); void insertDancer__12CReliveStageFR7Pokemonl(void *,MenuSubPokemon *,s32); void pickupDancer__12CReliveStageFR7Pokemonl(void *,MenuSubPokemon *,u32);
void menuCBRule_ErrorFlagSetPokemonGetTiming(void *,MenuSubPokemon *,u32); void menuCBRule_ErrorFlagSet(void *,s32); void menuCBRule_ErrorFlagSetOkPushTiming(void *);
u8 GSinputIsConnected(s32); u8 gbaCommandIsConnected(s32); s32 menuCB_GetDisconnectedGBA(void);
void menuCBPokemonEntryPokemonFaceFree(void); void menuCBBattleStartSetStatus(s32); void heroBiosCopy(void *, const void *); void menuCBPokemonEntryLoadTex(void);
void menuOpenCustom(s32,s32,void *,s32,s32,s32); s32 windowGetActiveID(void);
s32 heroBiosGetRnd(void *); int sprintf(char *,const char *,...); void GScharMakeFromSJIS(u16 *, const char *);
void _menuCBGCDelPokemon__Fv(void);
u8 menuCBGCEntry_ErrorDisp__FUlUl(u32 arg0, u32 arg1);
void menuCB_GCEntry_OkPushErrorCheck(void);
s32 menuCBBios_ParticipationPokemonMax(void); u16 toolentryTaisenGetPokemonNum(s32); s32 toolentryTaisengetEtnryPokemonOrderNum(s32);
void spriteSetOffset(s32, s32, s32); void spriteSetEnv(s32); void GSprimSetup2DRender__FP10GSgfxLayer(void *); void drawAndUpdate__4CAntFv(MenuSubAnt *);
s32 menuSubOpenSelect2(s32, s32 *, s32, s32, s32, s32, s32, s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32); void winMsgOpen(s32, s32, s32, s32); void winMsgClose(s32);
void menuCB_WaitGCControler1(void);
void menuCB_GBADisconnectedErrorJob(void);
void menuCBPokemonEntryGCControlDisp(MenuSubWindow *arg0, s32 arg1);
void menuCBGCDelPokemon(void);
void menuCBGCEntryPokemon(void);
void menuCB_Trainer_Error_Disp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3);
void menuCB_Pokemon_ErrorDisp(MenuSubWindow *arg0, s32 arg1);
void toolbattle_drawHeroID(MenuSubWindow *arg0, s32 arg1);

void fn_8007E5AC(MenuSubWindow *arg0, MenuSubSprite *arg1);
s32 fn_8007E634(s32 arg0);
s32 _menuCB_NotDarkWaza__Fl(s32 arg0);
u8 _menuCBPokemonEntryGetlevel__FP7Pokemon(MenuSubPokemon *arg0);
u32 menuCBPokemonGetIndex__FUlUl(s32 arg0, u32 arg1);
void fn_8007F43C(MenuSubWindow *arg0, MenuSubSprite *arg1, u16 *arg2, s32 arg3, s32 arg4, s32 arg5);
void _drawStrings__FP14tagWINDOW_WORKPUsllUl(MenuSubWindow *arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4);
void menuCB_SE_Stop(s32 arg0);
void menuCB_SE_Play(s32 arg0);
void menuCB_Cursol_Disp_AlphaSet(MenuSubWindow *arg0, MenuSubSprite *arg1, u8 arg2);
void menuCB_AlphaGet(MenuSubWindow *arg0);
void menuCB_GCPokemonHPandWAZA_MAX(void);
void menuCB_RuleDispColorChenge_flag(MenuSubWindow *arg0, MenuSubSprite *arg1, u8 arg2);
void menuCB_RuleDispColorChenge(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2);
void menuCBMessageYCenterDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void fn_80080390(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void menuCBMessageCenterDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void menuCB_RuleNameChengeAfterJob(u8 arg0);
void menuCB_RuleNameChengeBeforeJob(u8 arg0);
void menuCB_MenuDispCheckONorOFF_RULE(MenuSubWindow *arg0, s32 arg1);
void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(MenuSubWindow *arg0, s32 arg1);
void menuCB_MenuDispCheckONorOFF(MenuSubWindow *, u32);
void menuCB_SpriteDispCheckONorOFF(MenuSubSprite *, u32);
void menuCBReliveTitleNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3);
void menuCBGCEntryTitleDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3);
void menuCBPokemonMaruWaku_ErrorSet(MenuSubSprite *arg0, u32 arg1);
void menuCBPokemonItem_ErrorSet(MenuSubSprite *arg0, u32 arg1);
u8 _menuCBPokemon_ErrorDispSet__Fl(s32 arg0);
s32 menuCBPokemon_ErrorDispSet(MenuSubWindow *arg0, u32 arg1);
s32 toolBattle_tunaideMenu02menuTempBuffGet(s32 arg0);
void toolBattle_tunaideMenu02menuTempBuffSet(s32 arg0);
void toolBattleRuleErrorFlagClear(s32 arg0, u32 arg1);
u8 menuCB_Trainer_Error_Check();
void menuCBtrainerFaceReadWait(void);
void menuCBpokemonFaceReadWait(void);
void toobattle_drawHeroName2(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2);
void toobattle_drawHeroNames(MenuSubWindow *arg0, s32 arg1);
void toobattle_drawHeroName(MenuSubWindow *arg0, s32 arg1);
s32 toolbattle_trainerFace(void);
u8 menuCBPokemonGetDataId_NULL();
u8 menuCBPokemonGetDataId();
u8 menuCBPokemonGetItemDataId();

void fn_8007E5AC(MenuSubWindow *arg0, MenuSubSprite *arg1) {
    s16 temp_r0;

    temp_r0 = arg1->unk6;
    switch (temp_r0) {
    case 0x2B7:
        menuCBMessageCenterDisp(arg0, arg1, 0xD11E);
        return;
    case 0x2B8:
        menuCBMessageCenterDisp(arg0, arg1, 0xD11F);
        return;
    case 0x4D1:
        arg1->unk4C = 0xD160;
        return;
    case 0x433:
        menuCBMessageCenterDisp(arg0, arg1, 0x3BD6);
        return;
    }
}

s32 fn_8007E634(s32 arg0) {
    switch (pokecoloGetCountryCode()) {
    case 0: return arg0;
    case 1:
    case 2:
        switch (arg0) {
        case 0x4278: return 0x4279;
        case 0x4276: return 0x4277;
        case 0x427C: return 0x4352;
        case 0x427B: return 0x4351;
        }
        break;
    }
    return 0x56C;
}

s32 _menuCB_NotDarkWaza__Fl(s32 arg0) {
    if ((arg0 < 0x176) && (arg0 >= 0x164)) {
        return 0;
    }
    return arg0;
}

u8 _menuCBPokemonEntryGetlevel__FP7Pokemon(MenuSubPokemon *arg0) {
    return pokemonGetStatus(arg0, NULL, 0x7A, 0);
}

u32 menuCBPokemonGetIndex__FUlUl(s32 arg0, u32 arg1) {
    u32 var_r4;

    var_r4 = arg1;
    switch (arg0) {
    case 4:
        break;
    case 5:
        var_r4 = (u16)var_r4;
        break;
    case 6:
        var_r4 = (u16)var_r4;
        break;
    case 7:
        var_r4 += 0x1E;
        break;
    }
    return var_r4;
}

void fn_8007F43C(MenuSubWindow *arg0, MenuSubSprite *arg1, u16 *arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 temp_r4;
    u32 temp_r0;

    msgctrlSetValue(0x37, arg2);
    temp_r0 = GSmsgGetRect(arg5) >> 0x10U;
    temp_r4 = arg1->unk54;
    GSmsgPrint2(arg0->unk1C, (s16) ((temp_r4 / 2) - ((s16)temp_r0 / 2)), arg4, arg0->unk93 | ~0xFF, arg5);
}

void _drawStrings__FP14tagWINDOW_WORKPUsllUl(MenuSubWindow *arg0, u16 *arg1, s32 arg2, s32 arg3, s32 arg4) {
    msgctrlSetValue(0x37, arg1);
    GSmsgPrint2(arg0->unk1C, arg2, arg3, arg0->unk93 | ~0xFF, arg4);
}

void menuCB_SE_Stop(s32 arg0) {
    GSsndStop(arg0, 0, 0);
}

void menuCB_SE_Play(s32 arg0) {
    GSsndPlay(arg0, 0, 0);
}

void menuCB_Cursol_Disp_AlphaSet(MenuSubWindow *arg0, MenuSubSprite *arg1, u8 arg2) {
    u8 temp_r0;
    u8 temp_r0_2;

    if (arg2 != 0) {
        temp_r0 = arg0->unk93;
        if (temp_r0 == 0xFF) {
            arg1->unk67 = (u8) _CB.unkB138;
            return;
        }
        arg1->unk67 = temp_r0;
        return;
    }
    temp_r0_2 = arg0->unk93;
    if (temp_r0_2 >= 0x7FU) {
        arg1->unk67 = 0x7FU;
        return;
    }
    arg1->unk67 = temp_r0_2;
}

void menuCB_AlphaGet(MenuSubWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk93;
    if (temp_r0 == 0xFF) {
        _CB.unkB138 = (s32) menuSubAnimAlpha();
        return;
    }
    _CB.unkB138 = (s32) temp_r0;
}

void menuCB_GCPokemonHPandWAZA_MAX(void) {
    u32 var_r31;

    var_r31 = 0;
    do {
        MenuSubPokemon *pokemon = menuCBPokemonPtrGet__FUlUl(4U, var_r31);
        if (pokemon != NULL) {
            pokemonAllKaihuku(pokemon);
        }
        var_r31 += 1;
    } while (var_r31 < 6U);
}

void menuCB_RuleDispColorChenge_flag(MenuSubWindow *arg0, MenuSubSprite *arg1, u8 arg2) {
    if (arg2 != 0) {
        arg1->unk66 = 0xFF;
        arg1->unk65 = 0xFF;
        arg1->unk64 = 0xFF;
        arg1->unk67 = (u8) _CB.unkB138;
        return;
    }
    arg1->unk66 = 0x7F;
    arg1->unk65 = 0x7F;
    arg1->unk64 = 0x7F;
    arg1->unk67 = (u8) arg0->unk93;
}

void menuCB_RuleDispColorChenge(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2) {
    if (arg2 == (u32) _CB.unkB11C) {
        arg1->unk66 = 0xFF;
        arg1->unk65 = 0xFF;
        arg1->unk64 = 0xFF;
        arg1->unk67 = (u8) _CB.unkB138;
        return;
    }
    arg1->unk66 = 0x7F;
    arg1->unk65 = 0x7F;
    arg1->unk64 = 0x7F;
    arg1->unk67 = (u8) arg0->unk93;
}

void menuCBMessageYCenterDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    s16 temp_r5;
    u16 temp_r3;

    temp_r3 = GSmsgGetRect(arg2);
    temp_r5 = arg1->unk56;
    GSmsgPrint2(arg0->unk1C, 0, (s16) ((temp_r5 / 2) - ((s16)temp_r3 / 2)), arg0->unk93 | ~0xFF, arg2);
}

void fn_80080390(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    switch (pokecoloGetCountryCode()) {
    case 0: arg1->unk4C = arg2; break;
    case 1:
    case 2: menuCBMessageCenterDisp(arg0, arg1, arg2); break;
    }
}

void menuCBMessageCenterDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    s16 temp_r5;
    u32 temp_r0;

    temp_r0 = GSmsgGetRect(arg2) >> 0x10U;
    temp_r5 = arg1->unk54;
    GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5 / 2) - ((s16)temp_r0 / 2)), 0, ((*(u32 *)&arg1->unk64) & 0xFFFFFF00) | arg0->unk93, arg2);
}

void menuCB_RuleNameChengeAfterJob(u8 arg0) {
    if (arg0 != 0) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
        GSthreadSwitch();
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xA9, 0);
    menuOpen(0xCE, 0);
    menuOpen(0xCB, 0);
    menuOpen(0xCC, 0);
    menuOpen(0xCD, 0);
    menuOpen(0xAA, 0);
    menuOpen(0xF7, 0);
}

void menuCB_RuleNameChengeBeforeJob(u8 arg0) {
    if (arg0 != 0) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xF7, 0, 0);
    menuCloseCustom(0xAA, 0, 0);
    menuCloseCustom(0xCD, 0, 0);
    menuCloseCustom(0xCC, 0, 0);
    menuCloseCustom(0xCB, 0, 0);
    menuCloseCustom(0xCE, 0, 0);
    menuCloseCustom(0xA9, 0, 1);
    if (arg0 != 0) {
        if (fightReadResourceID(0x842, 0x195F3400) == 0) {
            fightFreeResourceID(0x842, 0x195F3400);
        }
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

void menuCB_MenuDispCheckONorOFF_RULE(MenuSubWindow *arg0, s32 arg1) {
    s32 var_r4;

    if ((s32) _CB.unkB124 != -1) {
        menuSetDisp(arg0->unk4, 0);
        if ((s32) _CB.unkB124 == arg1) {
            menuSetDisp(arg0->unk4, 1);
            arg0->unk93 = (u8) _CB.unkB128;
        }
        if ((s32) _CB.unkB118 == arg1) {
            menuSetDisp(arg0->unk4, 1);
            arg0->unk93 = (u8) _CB.unkB12C;
        }
    } else {
        if (arg1 == 1) {
            var_r4 = 0;
            if (((s32) _CB.unkB118 == arg1) || ((s32) _CB.unkB118 == 5)) {
                var_r4 = 1;
            }
            menuCB_MenuDispCheckONorOFF(arg0, var_r4);
            return;
        }
        menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB118 == arg1);
    }
}

void menuCB_MenuDispCheckONorOFF_TUNAIDESUB(MenuSubWindow *arg0, s32 arg1) {
    if ((s32) _CB.unkB144 != -1) {
        menuSetDisp(arg0->unk4, 0);
        if ((s32) _CB.unkB144 == arg1) {
            menuSetDisp(arg0->unk4, 1);
            arg0->unk93 = (u8) _CB.unkB148;
        }
        if ((s32) _CB.unkAFE4 == arg1) {
            menuSetDisp(arg0->unk4, 1);
            arg0->unk93 = (u8) _CB.unkB14C;
        }
    } else {
        menuCB_MenuDispCheckONorOFF(arg0, _CB.unkAFE4 == arg1);
    }
}

void menuCB_MenuDispCheckONorOFF(MenuSubWindow *arg0, u32 arg1) {
    if ((u8)arg1 != 0) {
        menuSetDisp(arg0->unk4, 1);
        return;
    }
    menuSetDisp(arg0->unk4, 0);
}

void menuCB_SpriteDispCheckONorOFF(MenuSubSprite *arg0, u32 arg1) {
    if ((u8)arg1 != 0) {
        winSpriteSetDisp(arg0, 1);
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void menuCBReliveTitleNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3) {
    s16 temp_r5;
    u32 temp_r0;

    spriteSetScissor(arg0->unk1C, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, GSmsgGetGSchar(arg2));
    temp_r0 = GSmsgGetRect(0x4277) >> 0x10U;
    temp_r5 = arg1->unk54;
    GSmsgPrint2(arg0->unk1C, (s16) ((s16) ((temp_r5 / 2) - ((s16)temp_r0 / 2)) + arg3), 0, arg0->unk93 | ~0xFF, 0x4277);
    spriteClearScissor(arg0->unk1C);
}

void menuCBGCEntryTitleDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3) {
    s16 temp_r4;
    u32 temp_r0;

    spriteSetScissor(arg0->unk1C, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, heroBiosGetNamePtr((u8 *)&_CB + 0xA65C));
    temp_r0 = GSmsgGetRect(arg2) >> 0x10U;
    temp_r4 = arg1->unk54;
    GSmsgPrint2(arg0->unk1C, (s16) ((s16) ((temp_r4 / 2) - ((s16)temp_r0 / 2)) + arg3), 0, arg0->unk93 | ~0xFF, arg2);
    spriteClearScissor(arg0->unk1C);
}

void menuCBPokemonMaruWaku_ErrorSet(MenuSubSprite *arg0, u32 arg1) {
    if (menuCB_Trainer_Error_Check(arg1, -1) == 0) {
        winSpriteSetDisp(arg0, 0);
        return;
    }
    if (menuCBPokemonGetDataId(_CB.unkB0D8, (s32) arg1) != 0) {
        arg0->unk64 = 0xBF;
        arg0->unk65 = 0;
        arg0->unk66 = 0;
        winSpriteSetDisp(arg0, 1);
        return;
    }
    if (menuCBPokemonGetDataId_NULL(_CB.unkB0D8, arg1) != 0) {
        arg0->unk64 = 0xBF;
        arg0->unk65 = 0;
        arg0->unk66 = 0;
        winSpriteSetDisp(arg0, 1);
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void menuCBPokemonItem_ErrorSet(MenuSubSprite *arg0, u32 arg1) {
    s32 errors;
    if (menuCBPokemonGetItemDataId(_CB.unkB0D8, arg1) != 0) {
        errors = (u8)menuCB_Trainer_Error_Check(arg1, 8);
        errors += (u8)menuCB_Trainer_Error_Check(arg1, 9);
        errors += (u8)menuCB_Trainer_Error_Check(arg1, 10);
        errors += (u8)menuCB_Trainer_Error_Check(arg1, 11);
        if (errors != 0) { arg0->unk64 = 0xBF; arg0->unk65 = 0; arg0->unk66 = 0; }
        winSpriteSetDisp(arg0, 1);
    } else { winSpriteSetDisp(arg0, 0); }
}

u8 _menuCBPokemon_ErrorDispSet__Fl(s32 arg0) {
    if (menuCBPokemonGetDataId(_CB.unkB0D8, arg0) == 0) {
        return menuCBPokemonGetDataId_NULL(_CB.unkB0D8, (u32) arg0) != 0;
    }
    return 1U;
}

s32 menuCBPokemon_ErrorDispSet(MenuSubWindow *arg0, u32 arg1) {
    if (menuCBPokemonGetDataId(_CB.unkB0D8, arg1) != 0) {
        winSpriteSetDisp(arg0, 1);
        return 1;
    }
    if (menuCBPokemonGetDataId_NULL(_CB.unkB0D8, arg1) != 0) {
        winSpriteSetDisp(arg0, 1);
        return 1;
    }
    winSpriteSetDisp(arg0, 0);
    return 0;
}

s32 toolBattle_tunaideMenu02menuTempBuffGet(s32 arg0) {
    return (_CB.unkB0D4 & arg0) != 0;
}

void toolBattle_tunaideMenu02menuTempBuffSet(s32 arg0) {
    if ((u32) (_CB.unkB0D4 & arg0) == 0) {
        _CB.unkB0D4 = (s32) (_CB.unkB0D4 | arg0);
    }
}

void toolBattleRuleErrorFlagClear(s32 arg0, u32 arg1) {
    *(u32 *)((u8 *)&_CB + (arg0 * 0x18) + (arg1 * 4) + 0x9C84) = 0;
}

u8 menuCB_Trainer_Error_Check(u32 arg0, s32 arg1) {
    switch (arg1) {
    case 0:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 7U) & 1) != 0;
    case 1:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 6U) & 1) != 0;
    case 2:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 5U) & 1) != 0;
    case 3:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 4U) & 1) != 0;
    case 4:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 3U) & 1) != 0;
    case 5:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 2U) & 1) != 0;
    case 6:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 >> 1U) & 1) != 0;
    case 7:
        return (((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C84 & 1) != 0;
    case 8:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 7U) & 1) != 0;
    case 9:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 6U) & 1) != 0;
    case 10:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 5U) & 1) != 0;
    case 11:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 4U) & 1) != 0;
    case 12:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 3U) & 1) != 0;
    case 13:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 2U) & 1) != 0;
    case 14:
        return (((u8) ((MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4)))->unk9C85 >> 1U) & 1) != 0;
    case -1:
        return *(u32 *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (arg0 * 4) + 0x9C84) != 0;
    default:
        return 1U;
    }
}

void menuCBtrainerFaceReadWait(void) {
loop_1:
    if ((s32) _menuCBBattleStartWork.unk2C != (s32) _menuCBBattleStartWork.unk30) {
        GSthreadSwitch();
        goto loop_1;
    }
}

void menuCBpokemonFaceReadWait(void) {
loop_1:
    if (menuCBPokemonEntryGetReadFlag() == 0) {
        GSthreadSwitch();
        goto loop_1;
    }
}

void toobattle_drawHeroName2(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    s32 temp_r31;
    s32 temp_r31_2;
    s32 temp_r3_2;
    s32 temp_r4;
    u8 *temp_r30;
    u8 *temp_r3;

    temp_r4 = arg2 * 0x1320;
    temp_r3 = (u8 *)&_CB + temp_r4;
    temp_r30 = temp_r3 + 0x9BC;
    temp_r3_2 = pokecoloGetCountryCode();
    if (temp_r3_2 != 0) {
        if ((temp_r3_2 >= 0) && (temp_r3_2 < 3)) {
            temp_r31 = fn_8007E634(0x4276);
            fn_8007F43C(arg0, arg1, heroBiosGetNamePtr(temp_r30), 0, 0, temp_r31);
        }
        return;
    }
    temp_r31_2 = fn_8007E634(0x4276);
    _drawStrings__FP14tagWINDOW_WORKPUsllUl(arg0, heroBiosGetNamePtr(temp_r30), 0, 0, temp_r31_2);
}

void toobattle_drawHeroNames(MenuSubWindow *arg0, s32 arg1) {
    s32 temp_r31;
    s32 temp_r5;

    temp_r5 = arg1 * 0x1320;
    temp_r31 = fn_8007E634(0x4278);
    _drawStrings__FP14tagWINDOW_WORKPUsllUl(arg0, heroBiosGetNamePtr((u8 *)&_CB + temp_r5 + 0x9BC), 0, 0, temp_r31);
}

void toobattle_drawHeroName(MenuSubWindow *arg0, s32 arg1) {
    s32 temp_r31;
    s32 temp_r5;

    temp_r5 = arg1 * 0x1320;
    temp_r31 = fn_8007E634(0x4276);
    _drawStrings__FP14tagWINDOW_WORKPUsllUl(arg0, heroBiosGetNamePtr((u8 *)&_CB + temp_r5 + 0x563C), 0, 0, temp_r31);
}

s32 toolbattle_trainerFace(void) {
    s32 temp_r31;
    s32 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;
    u8 temp_r3_4;

    temp_r31 = menuCBBios_GetTrainerOrgImmediately();
    temp_r3 = menuCBTrainerBios_GetHomePlace();
    switch (temp_r3) {
    case 0:
        return 0;
    case 1:
        temp_r3_2 = heroBiosGetSexDataId(temp_r31 + 0x9A4);
        switch ((s32) temp_r3_2) {
        case 0: return 3;
        case 1: return 4;
        case 2:
        default: break;
        }
        break;
    case 2:
        temp_r3_3 = heroBiosGetSexDataId(temp_r31 + 0x9A4);
        switch ((s32) temp_r3_3) {
        case 0: return 1;
        case 1: return 2;
        case 2:
        default: break;
        }
        break;
    case 3:
        temp_r3_4 = heroBiosGetSexDataId(temp_r31 + 0x9A4);
        switch ((s32) temp_r3_4) {
        case 0: return 5;
        case 1: return 6;
        case 2:
        default: break;
        }
        break;
    default:
        return 3;
    }
    return 3;
}

u8 menuCBPokemonGetDataId_NULL(u32 arg0, s32 arg1) {
    MenuSubPokemon *var_r3;

    if (menuCBBattleStartGetStatus() == 0) {
        var_r3 = toolentryTaisenGetPokemonPtr(arg0, arg1);
    } else if ((s32) toolentryTaisenGetEntryPokemonNum(arg0) <= arg1) {
        var_r3 = NULL;
    } else {
        var_r3 = toolentryTaisenGetEntryPokemonPtr((s32) arg0, arg1);
    }
    if (var_r3 != NULL) {
        return pokemonGetStatus(var_r3, NULL, 0x6E, 0) != 0;
    }
    return 0U;
}

u8 menuCBPokemonGetDataId(u32 arg0, s32 arg1) {
    MenuSubPokemon *var_r3;

    if (menuCBBattleStartGetStatus() == 0) {
        var_r3 = toolentryTaisenGetPokemonPtr(arg0, arg1);
    } else if ((s32) toolentryTaisenGetEntryPokemonNum(arg0) <= arg1) {
        var_r3 = NULL;
    } else {
        var_r3 = toolentryTaisenGetEntryPokemonPtr((s32) arg0, arg1);
    }
    if (var_r3 != NULL) {
        return pokemonCheckValid(var_r3) != 0;
    }
    return 0U;
}

u8 menuCBPokemonGetItemDataId(u32 arg0, s32 arg1) {
    return (u16)pokemonGetSoubiItemDataId(toolentryTaisenGetPokemonPtr(arg0, arg1)) != 0;
}

void _menuCB_PokemonStatusDispAfterJob__FUl(u32 arg0) {
    if (arg0 == 0U) {
        GSfsysReadWait(0x88C);
        menuTopOpenFlashBack();
        menuCB_FlashStart(0);
        fadeSet(2, 0.5f);
    }
    menuCB_SE_Play(0x14);
    menuOpen(0xBB, 0);
    menuOpen(0xBD, 0);
    menuOpen(0xBE, 0);
    menuOpen(0xBF, 0);
    menuOpen(0x10D, 0);
    menuOpen(0x10F, 0);
    menuOpen(0x10E, 0);
    menuOpen(0xC2, 0);
}

void _menuCB_PokemonStatusDispBeforeJob__FUl(u32 arg0) {
    if (arg0 == 0U) {
        menuCB_FlashEnd(1);
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xBC, 0, 0);
    menuCloseCustom(0xC2, 0, 0);
    menuCloseCustom(0x10E, 0, 0);
    menuCloseCustom(0x10F, 0, 0);
    menuCloseCustom(0x10D, 0, 0);
    menuCloseCustom(0xBF, 0, 0);
    menuCloseCustom(0xBE, 0, 0);
    menuCloseCustom(0xBD, 0, 0);
    menuCloseCustom(0xBB, 0, 1);
    if (arg0 == 0U) {
        GSfsysFree(0x88C);
        GSresFreeGroup(0x88C);
    }
}

s32 menuCBPokemonEntryDispPokemonFace_AFTER(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (menuCBBattleStartGetStatus() != 0) {
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, arg2, arg3);
        return 1;
    }
    return 0;
}

s32 menuCBPokemonEntryDispPokemonFace_BEFORE(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (menuCBBattleStartGetStatus() == 0) {
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, arg2, arg3);
        return 1;
    }
    return 0;
}

void menuCB_BattleEntryPokemonSelectDisp(MenuSubSprite *arg0, u32 arg1, u32 arg2) {
    menuCB_SpriteDispCheckONorOFF(arg0, menuCBPokemonCheck(arg1, arg2) == 0);
}

s32 menuCB_GCStatusDispMode(MenuSubSprite *arg0, s32 arg1) {
    if ((s32) _CB.unk8 == 2) {
        if (arg1 == 0) {
            winSpriteSetDisp(arg0, 1);
            return 1;
        }
        winSpriteSetDisp(arg0, 0);
        return 0;
    }
    if (arg1 == 1) {
        winSpriteSetDisp(arg0, 1);
        return 1;
    }
    winSpriteSetDisp(arg0, 0);
    return 0;
}

u8 menuCBPokemonCheck(u32 arg0, u32 arg1) {
    MenuSubPokemon *pokemon = menuCBPokemonPtrGet__FUlUl(arg0, arg1);
    if ((pokemon != NULL) && (pokemonCheckValid(pokemon) != 0)) {
        return 1U;
    }
    return 0U;
}

void menuCBPokemonItemName(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *temp_r3;
    s32 var_r30;
    u32 item;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    var_r30 = 1;
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0) && ((u16)(item = pokemonGetSoubiItemDataId(temp_r3)) != 0)) {
        var_r30 = itemDataBiosGetName(itemDataBiosGetPtr(item));
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(var_r30));
    switch (arg3) {
    case 0:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x4278));
        return;
    case 1:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x4276));
        return;
    }
}

void menuCBPokemonWazaNAME(MenuSubWindow *arg0, u32 arg1, u32 arg2, u32 arg3) {
    MenuSubPokemon *pokemon;
    u32 move;
    u32 name;
    s32 column;
    u32 pp;
    pokemon = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if (pokemon != NULL && pokemonCheckValid(pokemon) != 0) {
        move = (u16)pokemonGetStatus(pokemon, NULL, 0x7F, (u16)arg3);
        if (move == 0) {
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x3AF4);
            return;
        }
        name = wazaGetStatus(0, move, 1, 0);
        if (name != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(name));
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4279);
            switch (pokecoloGetCountryCode()) {
            case 0:
                column = 10;
                pp = pokemonGetStatus(pokemon, NULL, 0x80, (u16)arg3);
                if (pp < 10) column = 11;
                msgctrlSetValue(0x34, (void *)pp);
                GSmsgPrint2(arg0->unk1C, column * 13, 0, arg0->unk93 | ~0xFF, 0x427C);
                break;
            case 1:
            case 2:
                msgctrlSetValue(0x34, (void *)pokemonGetStatus(pokemon, NULL, 0x80, (u16)arg3));
                GSmsgPrintRight(arg0->unk1C, 0x82, 0, 0x1A, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x427C));
                break;
            }
        }
    }
}

void menuCBPokemonWazaTYPE(MenuSubWindow *arg0, u32 arg1, u32 arg2, u32 arg3) {
    s32 temp_r3_3;
    MenuSubPokemon *temp_r3;
    u16 temp_r3_2;
    u32 var_r0;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        temp_r3_2 = pokemonGetStatus(temp_r3, 0, 0x7F, arg3);
        temp_r3_3 = _menuCB_NotDarkWaza__Fl((s32) temp_r3_2);
        switch (temp_r3_3) {
        case 0x0:
            var_r0 = 0;
            break;
        case 0x176:
            var_r0 = 0x193;
            break;
        default:
            var_r0 = zokuseiBiosGetSmallSpriteID(wazaGetStatus(0, temp_r3_2, 3, 0));
            break;
        }
        if ((u16)var_r0 != 0) {
            windowDrawSprite(0, 0, arg0, var_r0, 0, arg0->unk1C);
        }
    }
}

void menuCBPokemonTYPE1(MenuSubWindow *arg0, u32 arg1, u32 arg2) {
    MenuSubPokemon *pokemon = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    s32 data = pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, NULL, 0x6E, 0));
    u16 sprite = zokuseiGetPokemonSpriteID(data, 0);
    if (sprite != 0) {
        windowDrawSprite(0, 0, arg0, sprite, 0, arg0->unk1C);
    }
}

void menuCBPokemonTYPE2(MenuSubWindow *arg0, u32 arg1, u32 arg2) {
    s32 temp_r31;
    u8 temp_r30;
    u16 sprite;

    MenuSubPokemon *pokemon = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    temp_r31 = pokemonDataBiosGetPtr(pokemonGetStatus(pokemon, NULL, 0x6E, 0));
    temp_r30 = pokemonDataBiosGetZokuseiDataId(temp_r31, 0);
    if ((temp_r30 != pokemonDataBiosGetZokuseiDataId(temp_r31, 1)) && ((sprite = zokuseiGetPokemonSpriteID(temp_r31, 1)) != 0)) {
        windowDrawSprite(0, 0, arg0, sprite, 0, arg0->unk1C);
    }
}

void menuCBPokemonStatusDisp(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3, s32 arg4) {
    s32 temp_r3_2;
    s32 var_r3;
    MenuSubPokemon *temp_r3;
    s32 var_r28;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        switch (arg4) {
        case 0:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43F5);
            var_r28 = (u16)pokemonGetStatus(temp_r3, 0, 0x88, 0U);
            break;
        case 1:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43F6);
            var_r28 = (u16)pokemonGetStatus(temp_r3, 0, 0x89, 0U);
            break;
        case 2:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43F7);
            var_r28 = (u16)pokemonGetStatus(temp_r3, 0, 0x8A, 0U);
            break;
        case 3:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43F8);
            var_r28 = (u16)pokemonGetStatus(temp_r3, 0, 0x8B, 0U);
            break;
        case 4:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43F9);
            var_r28 = (u16)pokemonGetStatus(temp_r3, 0, 0x8C, 0U);
            break;
        }
        msgctrlSetValue(0x34, (u16 *) var_r28);
        msgctrlSetValue(0x2F, (u16 *) var_r28);
        temp_r3_2 = pokecoloGetCountryCode();
        switch (temp_r3_2) {
case 0: {
            var_r3 = 5;
            if ((s32) var_r28 < 0xA) {
                var_r3 = 6;
            }
            if ((s32) var_r28 < 0x64) {
                var_r3 += 1;
            }
            switch (arg3) {
            case 0:
                GSmsgPrint2(arg0->unk1C, var_r3 * 0xD, 0, arg0->unk93 | ~0xFF, 0x427C);
                return;
            case 1:
                GSmsgPrint2(arg0->unk1C, var_r3 * 0x12, 0, arg0->unk93 | ~0xFF, 0x427B);
                return;
            }

} break;
case 1:
case 2: {
                switch (arg3) {
                case 0:
                    GSmsgPrintRight(arg0->unk1C, 0x3A, 0, 0x27, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x427C));
                    return;
                case 1:
                    GSmsgPrintRight(arg0->unk1C, 0x51, 0, 0x36, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x427B));
                    break;
                }

} break;
}
    }
}

void menuCBPokemonTOKUSEI(MenuSubWindow *arg0, u32 arg1, u32 arg2) {
    s32 temp_r3_2;
    MenuSubPokemon *temp_r3;
    s32 var_r29;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    var_r29 = 1;
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        var_r29 = pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(pokemonGetTokuseiDataId(temp_r3)));
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(var_r29));
    switch (pokecoloGetCountryCode()) {
    case 0:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x435A);
        GSmsgPrint2(arg0->unk1C, 0x5A, 0, arg0->unk93 | ~0xFF, 0x4276);
        break;
    case 1:
    case 2:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x445B);
        GSmsgPrint2(arg0->unk1C, (s16)(GSmsgGetRect(0x445B) >> 16), 0, arg0->unk93 | ~0xFF, 0x4277);
        break;
    }
}

void menuCBPokemonHP(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *pokemon;
    u16 value;
    pokemon = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if (pokemon != NULL && pokemonCheckValid(pokemon) != 0) {

        value = pokemonBiosGetHp(pokemon);
        msgctrlSetValue(0x34, (void *)value);
        msgctrlSetValue(0x2F, (void *)value);
        switch (arg3) {
        case 0:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43EA);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2: GSmsgPrint2(arg0->unk1C, 0x1B, 0, arg0->unk93 | ~0xFF, 0x427C); break;
            }
            break;
        case 3:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x427C));
            break;
        case 1:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4397);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2: GSmsgPrint2(arg0->unk1C, 0x26, 0, arg0->unk93 | ~0xFF, 0x427B); break;
            }
            break;
        case 2: break;
        }
    }
}

void menuCBPokemonLevel(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *pokemon;
    u8 value;
    pokemon = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if (pokemon != NULL && pokemonCheckValid(pokemon) != 0) {
        switch ((u32)pokemonBiosGetTamagoFlag(pokemon)) { case 0: break; default: return; }
        value = _menuCBPokemonEntryGetlevel__FP7Pokemon(pokemon);
        msgctrlSetValue(0x34, (void *)value);
        msgctrlSetValue(0x2F, (void *)value);
        switch (arg3) {
        case 0:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43E9);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2: GSmsgPrint2(arg0->unk1C, 0x1B, 0, arg0->unk93 | ~0xFF, 0x427C); break;
            }
            break;
        case 3:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, fn_8007E634(0x427C));
            break;
        case 1:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4396);
            switch (pokecoloGetCountryCode()) {
            case 1:
            case 2: GSmsgPrint2(arg0->unk1C, 0x26, 0, arg0->unk93 | ~0xFF, 0x427B); break;
            }
            break;
        case 2: break;
        }
    }
}

void menuCBPokemonNameOrg(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *temp_r3;
    s32 var_r30;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    var_r30 = 1;
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        var_r30 = pokemonDB_GetName(pokemon_GetPokemonDataId(temp_r3));
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(var_r30));
    switch (arg3) {
    case 0:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4279);
        return;
    case 1:
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4277);
        return;
    }
}

void menuCBPokemonSexOnly(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *temp_r3;
    u32 var_r3;
    u8 temp_r3_2;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        temp_r3_2 = menuSubGetPokemonSexForFightDisp(temp_r3);
        switch ((s32) temp_r3_2) {
        case 0:
            var_r3 = 0x9C5U;
            break;
        case 1:
            var_r3 = 0x9C6U;
            break;
        case 2:
        default:
            var_r3 = 1U;
            break;
        }
        if (var_r3 != 1U) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(var_r3));
            switch (arg3) {
            case 0:
                GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4278);
                return;
            case 1:
                GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4276);
                break;
            }
        }
    }
}

void menuCBPokemonNameOnly(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    MenuSubPokemon *temp_r3;
    u16 *var_r3;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
        var_r3 = pokemonBiosGetNicknamePtr(temp_r3);
        if (var_r3 == NULL) {
            var_r3 = GSmsgGetGSchar(1);
        }
        msgctrlSetValue(0x37, var_r3);
        switch (arg3) {
        case 0:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4279);
            return;
        case 1:
            GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4277);
            break;
        }
    }
}

void _menuCBPokemonName__FP14tagWINDOW_WORKUlUlUlb(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3, u8 arg4) {
    s32 temp_r3_2;
    u16 *var_r28;
    MenuSubPokemon *temp_r3;
    u32 var_r3;
    u8 var_r0;
    u8 var_r26;

    temp_r3 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    var_r26 = 0;
    if (temp_r3 != NULL) {
        if (pokemonCheckValid(temp_r3) == 0) {
            if (pokemonGetStatus(temp_r3, 0, 0x6E, 0U) != 0) {
                var_r28 = GSmsgGetGSchar(0x56C);
                var_r26 = 1;
                goto block_8;
            }
        } else {
            var_r28 = pokemonBiosGetNicknamePtr(temp_r3);
            if (var_r28 == NULL) {
                var_r28 = GSmsgGetGSchar(1);
            }
            if (pokemonBiosGetTamagoFlag(temp_r3) == 1) {
                var_r28 = GSmsgGetGSchar(0x56B);
            }
block_8:
            msgctrlSetValue(0x37, var_r28);
            switch (arg3) {
            case 0:
                GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4279);
                break;
            case 1:
                GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x4277);
                break;
            }
            if (pokemonBiosGetTamagoFlag(temp_r3) != 1) {
                if (var_r26 != 0) {
                    return;
                }
                if (arg4 != 0) {
                    var_r0 = (u8)menuSubGetPokemonSexForDisp(temp_r3);
                } else {
                    var_r0 = menuSubGetPokemonSexForFightDisp(temp_r3);
                }
                switch ((s32) var_r0) {
                case 0:
                    var_r3 = 0x9C5U;
                    break;
                case 1:
                    var_r3 = 0x9C6U;
                    break;
                case 2:
        default:
                    var_r3 = 0U;
                    break;
                }
                if (var_r3 != 0U) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(var_r3));
                    temp_r3_2 = pokecoloGetCountryCode();
                    switch (temp_r3_2) {
case 0: {
                        switch (arg3) {
                        case 0:
                            GSmsgPrint2(arg0->unk1C, 0x46, 0, arg0->unk93 | ~0xFF, 0x4278);
                            return;
                        case 1:
                            GSmsgPrint2(arg0->unk1C, 0x5A, 0, arg0->unk93 | ~0xFF, 0x4276);
                            return;
                        }

} break;
case 1:
case 2: {
                            switch (arg3) {
                            case 0:
                                GSmsgPrint2(arg0->unk1C, 0x5A, 0, arg0->unk93 | ~0xFF, 0x4278);
                                return;
                            case 1:
                                GSmsgPrint2(arg0->unk1C, 0x6E, 0, arg0->unk93 | ~0xFF, 0x4276);
                                break;
                            }

} break;
}
                }
            }
        }
    }
}

void menuCBPokemonName(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    _menuCBPokemonName__FP14tagWINDOW_WORKUlUlUlb(arg0, arg1, arg2, arg3, 0);
}

void menuCBPokemonName_nido(MenuSubWindow *arg0, u32 arg1, u32 arg2, s32 arg3) {
    _menuCBPokemonName__FP14tagWINDOW_WORKUlUlUlb(arg0, arg1, arg2, arg3, 1);
}

void menuCB2DPokemonItemDisp(MenuSubWindow *arg0, u32 arg1, u32 arg2) {
    MenuSubPokemon *temp_r31;

    temp_r31 = menuCBPokemonPtrGet__FUlUl(arg1, arg2);
    winSpriteSetDisp(arg0, 0);
    if ((temp_r31 != NULL) && (pokemonCheckValid(temp_r31) != 0) && ((u16)pokemonGetSoubiItemDataId(temp_r31) != 0)) {
        winSpriteSetDisp(arg0, 1);
    }
}

void _menuCB_ErrorTAMAGOCheck__Fv(void) {
    s32 count;
    s32 offset = 0;
#define ENTRY_FLAGS ((MenuSubErrorFlags *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + offset + 0x9C84))
    for (count = 6; count != 0; --count) {
        if (ENTRY_FLAGS->byte0Bit2 != 0) {
            ENTRY_FLAGS->byte0Bit5 = 0;
            ENTRY_FLAGS->byte0Bit4 = 0;
            ENTRY_FLAGS->byte1Bit3 = 0;
        }
        if (ENTRY_FLAGS->byte1Bit1 != 0) {
            ENTRY_FLAGS->byte0Bit5 = 0;
            ENTRY_FLAGS->byte0Bit4 = 0;
            ENTRY_FLAGS->byte1Bit3 = 0;
            ENTRY_FLAGS->byte0Bit2 = 1;
        }
        if (ENTRY_FLAGS->byte1Bit4 != 0 && ENTRY_FLAGS->byte1Bit6 != 0) {
            ENTRY_FLAGS->byte1Bit6 = 0;
        }
        offset += 4;
    }
#undef ENTRY_FLAGS
}

void _menuCB2DPokemonNewSet2__FUlUlUlUc(u32 arg0, s32 arg1, u32 arg2, u8 arg3) {
    MenuSubAnt *var_r29;
    MenuSubAnt *var_r30;
    MenuSubAnt *var_r31;
    MenuSubPokemon *temp_r3;
    MenuSubAnt *base;
    u32 var_r26;

    var_r26 = 0;
    var_r29 = ant;
    var_r31 = antR;
    var_r30 = antL;
    while (var_r26 < arg2) {
        temp_r3 = menuCBPokemonPtrGet__FUlUl(arg0, arg1 | var_r26);
        if ((temp_r3 != NULL) && (pokemonCheckValid(temp_r3) != 0)) {
            switch ((s32) arg3) {
            case 0:
                initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(var_r31, temp_r3);
                setAnimation__4CAntFl(var_r31, 0);
                break;
            case 1:
                initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(var_r30, temp_r3);
                setAnimation__4CAntFl(var_r30, 0);
                break;
            case 2:
                initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(var_r29, temp_r3);
                setAnimation__4CAntFl(var_r29, 0);
                break;
            }
        }
        var_r31 += 1;
        var_r30 += 1;
        var_r29 += 1;
        var_r26 += 1;
    }
}

void _menuCB2DPokemonNewSet__FUc(u8 arg0) {
    if (arg0 == 2) {
        _menuCB2DPokemonNewSet2__FUlUlUlUc(4U, 0, 6U, arg0);
        return;
    }
    switch ((s32) _CB.unkB0F0) {
    case 0:
        switch ((s32) arg0) {
        case 0:
            _menuCB2DPokemonNewSet2__FUlUlUlUc(5U, 0, 0x1EU, arg0);
            return;
        case 1:
            if ((u8) _CB.unkB4A0 == 1) {
                _menuCB2DPokemonNewSet2__FUlUlUlUc(6U, 0x80000, 5U, arg0);
                return;
            }
            _menuCB2DPokemonNewSet2__FUlUlUlUc(5U, 0x70000, 0x1EU, arg0);
            return;
        }
        break;
    case 1:
        switch ((s32) arg0) {
        case 0:
            if ((s32) _CB.unkB0E8 == 7) {
                if ((u8) _CB.unkB4A0 == 1) {
                    _menuCB2DPokemonNewSet2__FUlUlUlUc(6U, 0, 5U, arg0);
                    return;
                }
                _menuCB2DPokemonNewSet2__FUlUlUlUc(4U, 0, 6U, arg0);
                return;
            }
            _menuCB2DPokemonNewSet2__FUlUlUlUc(5U, (_CB.unkB0E8 + 1) << 0x10, 0x1EU, arg0);
            return;
        case 1:
            if ((s32) _CB.unkB0E8 == 0) {
                _menuCB2DPokemonNewSet2__FUlUlUlUc(4U, 0, 6U, arg0);
                return;
            }
            _menuCB2DPokemonNewSet2__FUlUlUlUc(5U, (_CB.unkB0E8 - 1) << 0x10, 0x1EU, arg0);
            return;
        }
        break;
    case 2:
        switch ((s32) arg0) {
        case 0:
            if ((s32) _CB.unkB0EC == 8) {
                _menuCB2DPokemonNewSet2__FUlUlUlUc(4U, 0, 6U, arg0);
                return;
            }
            _menuCB2DPokemonNewSet2__FUlUlUlUc(6U, (_CB.unkB0EC + 1) << 0x10, 5U, arg0);
            return;
        case 1:
            if ((s32) _CB.unkB0EC == 0) {
                _menuCB2DPokemonNewSet2__FUlUlUlUc(5U, 0x70000, 0x1EU, arg0);
                return;
            }
            _menuCB2DPokemonNewSet2__FUlUlUlUc(6U, (_CB.unkB0EC - 1) << 0x10, 5U, arg0);
            break;
        }
        break;
    }
}

void _menuCB_errorMsgDisp2__FUl(s32 arg0) {
    winMsgOpen(2, arg0, 1, 0);
    winMsgClose(1);
}

void _menuCB_errorMsgDisp__FUl(s32 arg0) {
    winMsgOpen(2, arg0, 1, 1);
    do {
        GSthreadSwitch();
    } while ((s32) (windowGetKeyInfo()->unk4 & 0x30) == 0);
    winMsgClose(1);
}

u8 menuCBPokemonEntryDisp(MenuSubWindow *arg0) {
    u8 flag = 1;
    switch (toolentryTaisenGetHomePlace(0)) {
    case 0: winSpriteSetDisp(arg0, 1); break;
    default: winSpriteSetDisp(arg0, 0); flag = 0; break;
    }
    return flag;
}

void menuCBGCEntryTypeIndex(void) {
    switch ((s32) _CB.unkB0F0) {
    case 0:
        _CB.unkB1D4 = 4;
        _CB.unkB1D8 = (s32) _CB.unkB0F8;
        return;
    case 1:
        _CB.unkB1D4 = 5;
        _CB.unkB1D8 = (s32) ((u16) _CB.unkB0F8 | ((_CB.unkB0E8 * 0x10000) & 0xFFFF0000));
        return;
    case 2:
        _CB.unkB1D4 = 6;
        _CB.unkB1D8 = (s32) ((u16) _CB.unkB0F8 | ((_CB.unkB0EC * 0x10000) & 0xFFFF0000));
        return;
    case 3:
        _CB.unkB1D4 = 7;
        _CB.unkB1D8 = (s32) _CB.unkB0F8;
        return;
    }
}

void menuCBReliveHallCursolInit(void) {
    s32 temp_r30;
    s8 var_r29;

    if ((s32) _CB.unkB0F8 <= 4) {
        temp_r30 = (_CB.unkB0EC * 0x10000) & 0xFFFF0000;
        if (menuCBPokemonCheck(6U, _CB.unkB0F8 | temp_r30) == 0) {
            var_r29 = 0;
loop_3:
            if (menuCBPokemonCheck(6U, var_r29 | temp_r30) != 0) {
                _CB.unkB0F8 = (s32) var_r29;
            } else {
                var_r29 += 1;
                if ((u32) var_r29 < 5U) {
                    goto loop_3;
                }
            }
            if ((u32) _CB.unkB0F8 != (u32) var_r29) {
                _CB.unkB0F8 = 0x1E;
            }
        }
    }
}

void menuCBPCBOXTitleNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s8 arg2, s32 arg3) {
    s16 temp_r5;
    u32 temp_r0;

    spriteSetScissor(arg0->unk1C, 0, 0, 0xD1, 0x12);
    msgctrlSetValue(0x37, getPokemonBoxName__5PCBOXFSc(getPointer__5PCBOXFv(), arg2));
    temp_r0 = GSmsgGetRect(0x4277) >> 0x10U;
    temp_r5 = arg1->unk54;
    GSmsgPrint2(arg0->unk1C, (s16) ((s16) ((temp_r5 / 2) - ((s16)temp_r0 / 2)) + arg3), 0, arg0->unk93 | ~0xFF, 0x4277);
    spriteClearScissor(arg0->unk1C);
}

void menuCB2DPokemonClearSHIFT(u32 arg0) {
    u8 *var_r30;
    u8 *var_r30_2;
    u8 *var_r31;
    u32 var_r29;
    u32 var_r29_2;

    if (arg0 == 0U) {
        memcpy(antL, ant, 0x618);
        memcpy(ant, antR, 0x618);
        memset(antR, 0, 0x618);
    } else {
        memcpy(antR, ant, 0x618);
        memcpy(ant, antL, 0x618);
        memset(antL, 0, 0x618);
    }
    systemUsecountReset__4CAntFv();
    var_r30 = (u8 *)ant;
    var_r29 = 0U;
    do {
        use__4CAntFv(var_r30);
        var_r30 += 0x34;
        var_r29 += 1;
    } while (var_r29 < 0x24U);
    var_r30_2 = (u8 *)antR;
    var_r31 = (u8 *)antL;
    var_r29_2 = 0U;
    do {
        use__4CAntFv(var_r30_2);
        use__4CAntFv(var_r31);
        var_r30_2 += 0x34;
        var_r31 += 0x34;
        var_r29_2 += 1;
    } while (var_r29_2 < 0x1EU);
    systemUnUseResourceRelease__4CAntFv();
    _CB.unkB154 = 0;
    if (arg0 == 0U) {
        _CB.unkB150 = -0x10;
        _CB.unkB158 = 0x180;
    } else {
        _CB.unkB150 = 0x10;
        _CB.unkB158 = -0x180;
    }
    _CB.unkB15C = (s32) _CB.unkB0F0;
    _CB.unkB160 = (s32) _CB.unkB0E8;
    _CB.unkB164 = (s32) _CB.unkB0EC;
}

void menuCB2DPokemonALLClear(void) {
    u8 *var_r30;
    u8 *var_r30_2;
    u8 *var_r31;
    u32 var_r29;
    u32 var_r29_2;

    systemUsecountReset__4CAntFv();
    systemUnUseResourceRelease__4CAntFv();
    memset(ant, 0, 0x750);
    memset(antL, 0, 0x618);
    memset(antR, 0, 0x618);
    _CB.unkB0F0 = 0;
    _menuCB2DPokemonNewSet__FUc(2U);
    _menuCB2DPokemonNewSet__FUc(0U);
    _menuCB2DPokemonNewSet__FUc(1U);
    var_r30 = (u8 *)ant;
    var_r29 = 0U;
    do {
        use__4CAntFv(var_r30);
        var_r30 += 0x34;
        var_r29 += 1;
    } while (var_r29 < 0x24U);
    var_r30_2 = (u8 *)antR;
    var_r31 = (u8 *)antL;
    var_r29_2 = 0U;
    do {
        use__4CAntFv(var_r30_2);
        use__4CAntFv(var_r31);
        var_r30_2 += 0x34;
        var_r31 += 0x34;
        var_r29_2 += 1;
    } while (var_r29_2 < 0x1EU);
}

void menuCB_DispEffect(MenuSubWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk1;
    switch ((s8) temp_r0) {
    case 0:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x189);
            arg0->unk2 = 1U;
            return;
        }
        break;
    case 3:
        if ((s8) arg0->unk2 == 0) {
            if ((s32) _CB.unkB184 == 0) {
                winSeqSetMenu(arg0->unk4, 0x18D);
                arg0->unk2 = 1U;
                spriteClearScissor(arg0->unk1C);
                return;
            }
            arg0->unk2 = 1U;
            menuSetDisp(arg0->unk4, 0);
        }
        break;
    }
}

s32 menuCBBattleBANextMenu(MenuSubWindow *arg0) {
    u16 temp_r3;

    if (pauseIsPause() != 0) {
        return 0;
    }
    if (menuCBBattleStartGetStatus() == 0) {
        if ((s16) _CB.unkB1E4 == 0) {
            if (menuCB_BattleStartSoundCheck() != 0) {
                arg0->unkA4 = 1;
            }
            if (FlashSystemIsLastFrame(0x21533000) != 0) {
                return 1;
            }
            return 0;
        }
        _CB.unkB1E4 = _CB.unkB1E4 - 1;
        return 0;
    }
    if ((u16) battleEndHPEndFlag == 0) {
        arg0->unkA4 = 1;
        return 0;
    }
    battleEndHPEndFlag -= 1;
    temp_r3 = battleEndHPEndFlag;
    if ((temp_r3 == 0x37) && ((s32) _CB.unkB180 != 0)) {
        menuCB_SE_Stop(0x5D0);
    }
    return 0;
}

s32 menuCB_BattleBA_PokemonEntryNum(void) {
    s32 counts[2];
    s32 var_r28;
    s32 var_r29;
    s32 *var_r30;

    var_r30 = counts;
    var_r29 = 0;
    do {
        *var_r30 = 0;
        var_r28 = 0;
loop_2:
        if (menuCBPokemonGetDataId(var_r29, var_r28) != 0) {
            *var_r30 += 1;
        }
        var_r28 += 1;
        if (var_r28 < 6) {
            goto loop_2;
        }
        var_r30 += 1;
        var_r29 += 1;
    } while (var_r29 < 2);
    if ((counts[0] >= 4) || (counts[1] >= 4)) {
        return 1;
    }
    return 0;
}

MenuSubPokemon *menuCBPokemonPtrGet__FUlUl(u32 type, u32 index) {
    MenuSubPokemon *pokemon;
    u32 stageIndex;
    void *stage;
    s32 country;
    if ((u16)index >= 36) return NULL;
    if ((u16)index >= 30 && (u16)index <= 35) {
        type = 7;
        index = (u16)index - 30;
    }
    switch ((s32)type) {
    case 4:
        pokemon = heroBiosGetPokemonPtr(savedataGetStatus(0, 2), (u16)index);
        break;
    case 5:
        pokemon = getPokemon__5PCBOXFScSc(getPointer__5PCBOXFv(), (s8)(index >> 16), (s8)(u16)index);
        break;
    case 6:
        stageIndex = index >> 16;
        stage = getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), stageIndex);
        if ((u16)index == 4) {
            pokemon = getVisitorPointer__12CReliveStageFv(stage);
        } else {
            switch (pokecoloGetCountryCode()) {
            case 0:
                pokemon = getDancerPointer__12CReliveStageFl(stage, (u16)index);
                break;
            case 1:
            case 2:
                pokemon = *(MenuSubPokemon **)((u8 *)&_CB + 0xB524 + stageIndex * 16 + (u16)index * 4);
                break;
            }
        }
        break;
    case 7:
        pokemon = heroBiosGetPokemonPtr((u8 *)&_CB + 0xA65C, (u16)index);
        break;
    case 0:
    case 1:
    case 2:
    case 3:
        pokemon = toolentryTaisenGetPokemonPtr(type, index);
        break;
    }
    return pokemon;
}

void menuCB_RuleMessageTblDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    u16 sp8[31];
    s16 temp_r4;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_ctr;
    MenuSubWindow *temp_r30;
    u16 *var_r3;
    u16 *var_r5;
    u32 temp_r0;

    var_r3 = (u16 *)arg0;
    temp_r30 = arg0;
    if (arg2 >= 3) {
        temp_r5 = arg2 * 0x90;
        msgctrlSetValue(0x37, (u8 *)&_CB + temp_r5 + 0x9936);
    } else {
        switch (arg2) {
        case 0:
            var_r3 = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            var_r3 = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            var_r3 = GSmsgGetGSchar(0x4388);
            break;
        }
        var_r5 = sp8;
        var_ctr = 0x1F;
        do {
            if (var_r3 != NULL) {
                if ((u16) *var_r3 == 0xFFFF) {
                    var_r3 += 1;
                }
                *var_r5 = *var_r3;
                if ((u16) *var_r3 != 0) {
                    var_r3 += 1;
                }
            } else {
                *var_r5 = 0;
            }
            var_r5 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
        msgctrlSetValue(0x37, sp8);
    }
    temp_r0 = GSmsgGetRect(fn_8007E634(0x4276)) >> 0x10U;
    temp_r4 = arg1->unk54;
    temp_r5_2 = (s16)temp_r0 / 2;
    GSmsgPrint2(temp_r30->unk1C, (s16) ((temp_r4 / 2) - temp_r5_2), 0, ((*(u32 *)&arg1->unk64) & 0xFFFFFF00) | temp_r30->unk93, fn_8007E634(0x4276));
}

void menuCB_RuleItemFlagDisp(MenuSubWindow *arg0, MenuSubSprite *arg1) {
    s16 var_r30;
    s32 temp_r31;
    s32 var_r26;
    s32 var_r29;
    MenuSubItem *temp_r27;
    MenuSubItem *temp_r7;

    temp_r31 = winSpriteGetLayerID(arg0,arg1);
    temp_r27 = menuItemBiosGetPtr(arg0->unk4, 0x3AB);
    temp_r7 = menuItemBiosGetPtr(arg0->unk4, arg1->unk6);
    var_r30 = -(_CB.unkB028 * 0x18);
    if ((s32) _CB.unkB028 == 0) {
        var_r26 = 0;
    } else {
        var_r26 = _CB.unkB028 - 1;
        var_r30 += var_r26 * 0x18;
    }
    var_r29 = var_r26 + 0xD;
    if (var_r29 >= 0x3E) {
        var_r29 = 0x3E;
    }
    spriteSetScissor(temp_r31, temp_r27->unk6 - temp_r7->unk6, temp_r27->unk8 - temp_r7->unk8, temp_r7->unkA, temp_r7->unkC);
loop_12:
    if (var_r26 <= var_r29) {
        if (var_r26 == 0x3E) {
            GSmsgPrint2(arg0->unk1C, 0, var_r30, arg0->unk93 | ~0xFF, 1);
        } else if ((u8) *((u8 *)_CB.unk9C78 + (var_r26 + 0x52)) != 0) {
            GSmsgPrint2(arg0->unk1C, 0, var_r30, arg0->unk93 | 0xFF3F0000, 0x43E4);
        } else {
            GSmsgPrint2(arg0->unk1C, 0, var_r30, arg0->unk93 | ~0xFF, 0x43E3);
        }
        var_r26 += 1;
        var_r30 += 0x18;
        goto loop_12;
    }
    spriteClearScissor(temp_r31);
}

void menuCB_RuleItemNameEntry(MenuSubWindow *arg0, MenuSubSprite *arg1) {
    s16 var_r30;
    s32 temp_r31;
    s32 var_r26;
    s32 var_r27;
    s32 var_r29;
    u16 temp_r3;
    MenuSubItem *temp_r27;
    MenuSubItem *temp_r7;

    temp_r31 = winSpriteGetLayerID(arg0,arg1);
    temp_r27 = menuItemBiosGetPtr(arg0->unk4, 0x3AC);
    temp_r7 = menuItemBiosGetPtr(arg0->unk4, arg1->unk6);
    var_r30 = -(_CB.unkB028 * 0x18);
    if ((s32) _CB.unkB028 == 0) {
        var_r26 = 0;
    } else {
        var_r26 = _CB.unkB028 - 1;
        var_r30 += var_r26 * 0x18;
    }
    var_r29 = var_r26 + 0xD;
    if (var_r29 >= 0x3E) {
        var_r29 = 0x3E;
    }
    spriteSetScissor(temp_r31, temp_r27->unk6 - temp_r7->unk6, temp_r27->unk8 - temp_r7->unk8, temp_r7->unkA, temp_r7->unkC);
    var_r27 = var_r26;
loop_12:
    if (var_r27 <= var_r29) {
        temp_r3 = menuCBRule_RegulationItemID(var_r27);
        if (temp_r3 == 0) {
            GSmsgPrint2(arg0->unk1C, 0, var_r30, arg0->unk93 | ~0xFF, 0x4345);
        } else {
            if (itemDataCheckValid(temp_r3) != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemDataBiosGetPtr(temp_r3))));
            }
            GSmsgPrint2(arg0->unk1C, 0, var_r30, arg0->unk93 | ~0xFF, fn_8007E634(0x4276));
        }
        var_r27 += 1;
        var_r30 += 0x18;
        goto loop_12;
    }
    spriteClearScissor(temp_r31);
}

void menuCBRuleNumberDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2) {
    s16 centered;
    s32 message;
    s16 temp_r4;
    s16 temp_r5_2;
    s16 temp_r5_3;
    s16 temp_r5_4;
    s16 temp_r5_5;
    s16 temp_r5_6;
    s32 temp_r5;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_5;
    u32 temp_r0_6;
    u32 var_r29;

    switch (arg2) {
    case 0:
        var_r29 = _CB.unk9C78->unk0 / 100;
        goto block_26;
    case 1:
        var_r29 = (_CB.unk9C78->unk0 % 100) / 10;
        goto block_26;
    case 2:
        var_r29 = _CB.unk9C78->unk0 % 10;
        goto block_26;
    case 3:
        var_r29 = _CB.unk9C78->unk2 / 100;
        goto block_26;
    case 4:
        var_r29 = (_CB.unk9C78->unk2 % 100) / 10;
        goto block_26;
    case 5:
        var_r29 = _CB.unk9C78->unk2 % 10;
        goto block_26;
    case 6:
        var_r29 = _CB.unk9C78->unk4 / 100;
        goto block_26;
    case 7:
        var_r29 = (_CB.unk9C78->unk4 % 100) / 10;
        goto block_26;
    case 8:
        var_r29 = _CB.unk9C78->unk4 % 10;
        goto block_26;
    case 9:
        if ((s32) (_CB.unk9C78->unk14 & 0x8000) != 0) {
            temp_r0_2 = GSmsgGetRect(0x4416) >> 0x10U;
            temp_r5_2 = arg1->unk54;
            GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5_2 / 2) - ((s16)temp_r0_2 / 2)), 0, arg0->unk93 | ~0xFF, 0x4416);
            return;
        }
        var_r29 = _CB.unk9C78->unk14 / 10;
        goto block_26;
    case 10:
        if ((s32) (_CB.unk9C78->unk14 & 0x8000) != 0) {
            temp_r0_3 = GSmsgGetRect(0x4416) >> 0x10U;
            temp_r5_3 = arg1->unk54;
            GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5_3 / 2) - ((s16)temp_r0_3 / 2)), 0, arg0->unk93 | ~0xFF, 0x4416);
            return;
        }
        var_r29 = _CB.unk9C78->unk14 % 10;
        goto block_26;
    case 11:
        if ((s32) (_CB.unk9C78->unk16 & 0x8000) != 0) {
            temp_r0_4 = GSmsgGetRect(0x4416) >> 0x10U;
            temp_r5_4 = arg1->unk54;
            GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5_4 / 2) - ((s16)temp_r0_4 / 2)), 0, arg0->unk93 | ~0xFF, 0x4416);
            return;
        }
        var_r29 = _CB.unk9C78->unk16 / 10;
        goto block_26;
    case 12:
        if ((s32) (_CB.unk9C78->unk16 & 0x8000) != 0) {
            temp_r0_5 = GSmsgGetRect(0x4416) >> 0x10U;
            temp_r5_5 = arg1->unk54;
            GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5_5 / 2) - ((s16)temp_r0_5 / 2)), 0, arg0->unk93 | ~0xFF, 0x4416);
            return;
        }
        var_r29 = _CB.unk9C78->unk16 % 10;
        goto block_26;
    case 13:
        if ((s16) _CB.unk9C78->unk1C == 1) {
            temp_r0_6 = GSmsgGetRect(0x4416) >> 0x10U;
            temp_r5_6 = arg1->unk54;
            GSmsgPrint2(arg0->unk1C, (s16) ((temp_r5_6 / 2) - ((s16)temp_r0_6 / 2)), 0, arg0->unk93 | ~0xFF, 0x4416);
            return;
        }
        var_r29 = _CB.unk9C78->unk1A % 10;
        goto block_26;
    }
block_26:
        msgctrlSetValue(0x34, (u16 *) var_r29);
        msgctrlSetValue(0x2F, (u16 *) var_r29);
        temp_r0 = GSmsgGetRect(fn_8007E634(0x427B)) >> 0x10U;
        temp_r4 = arg1->unk54;
        temp_r5 = (s16)temp_r0 / 2;
        centered = (s16)((temp_r4 / 2) - temp_r5);
        message = fn_8007E634(0x427B);
        GSmsgPrint2(arg0->unk1C, centered, 0, arg0->unk93 | ~0xFF, message);
        return;

}

void menuCBRULE_EditNameDispLarge(MenuSubWindow *arg0, s32 arg1) {
    u16 sp8[31];
    s32 temp_r5;
    s32 var_ctr;
    MenuSubWindow *temp_r31;
    u16 *var_r30;
    u16 *var_r3;
    u16 *var_r5;

    var_r3 = (u16 *)arg0;
    temp_r31 = arg0;
    if (arg1 >= 3) {
        temp_r5 = arg1 * 0x90;
        msgctrlSetValue(0x37, (u8 *)&_CB + temp_r5 + 0x9936);
    } else {
        switch (arg1) {
        case 0:
            var_r3 = GSmsgGetGSchar(0x4387);
            break;
        case 1:
            var_r3 = GSmsgGetGSchar(0x4389);
            break;
        case 2:
            var_r3 = GSmsgGetGSchar(0x4388);
            break;
        }
        var_r5 = sp8;
        var_ctr = 0x1F;
        do {
            if (var_r3 != NULL) {
                if ((u16) *var_r3 == 0xFFFF) {
                    var_r3 += 1;
                }
                *var_r5 = *var_r3;
                if ((u16) *var_r3 != 0) {
                    var_r3 += 1;
                }
            } else {
                *var_r5 = 0;
            }
            var_r5 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
        msgctrlSetValue(0x37, sp8);
    }
    GSmsgPrint2(temp_r31->unk1C, 0, 0, temp_r31->unk93 | ~0xFF, 0x4275);
    if ((s32) _CB.unkB118 == 5) {
        msgctrlSetValue(0x34, (u16 *)2U);
    } else {
        msgctrlSetValue(0x34, (void *)(_CB.unkB118 + 1));
    }
    msgctrlSetValue(0x2F, (void *)_CB.unkB1E0);
    GSmsgPrint2(temp_r31->unk1C, 0x1CE, 0, temp_r31->unk93 | ~0xFF, 0x427A);
    GSmsgPrint2(temp_r31->unk1C, 0x1E4, 2, temp_r31->unk93 | ~0xFF, 0x4417);
    if ((s32) _CB.unkB014 != -1) {
        var_r30 = (u16 *)5U;
    } else {
        var_r30 = (u16 *)4U;
    }
    msgctrlSetValue(0x34, var_r30);
    msgctrlSetValue(0x2F, var_r30);
    GSmsgPrint2(temp_r31->unk1C, 0x1FA, 0, temp_r31->unk93 | ~0xFF, 0x427A);
}

void menuCBRULE_EditNameDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2) {
    s32 temp_r5;

    temp_r5 = arg2 * 0x90;
    msgctrlSetValue(0x37, (u8 *)&_CB + temp_r5 + 0x9936);
    GSmsgPrint2(arg0->unk1C, 0, 0, ((*(u32 *)&arg1->unk64) & 0xFFFFFF00) | arg0->unk93, 0x4277);
}

void menuCB_GCEntry_PokemonStatusDisp(void) {
    MenuSubPokemon *temp_r31;

    temp_r31 = menuCBPokemonPtrGet__FUlUl(_CB.unkB1D4, _CB.unkB1D8);
    _menuCB_PokemonStatusDispBeforeJob__FUl(0U);
    menuPokemonStatusOpenFromPokemonChange(temp_r31, 0, 0);
    _menuCB_PokemonStatusDispAfterJob__FUl(0U);
}

void menuCB_GCEntry_ItemKeepJob(void) {
    MenuSubPokemon *temp_r31;
    void *temp_r30;
    u32 temp_r3;
    u16 *nickname;

    temp_r31 = menuCBPokemonPtrGet__FUlUl(_CB.unkB1D4, _CB.unkB1D8);
    nickname = pokemonBiosGetNicknamePtr(temp_r31);
    temp_r30 = (u8 *)&_CB + 0xA65C;
    msgctrlSetValue(0x32, nickname);
    temp_r3 = pokemonGetSoubiItemDataId(temp_r31);
    if ((u16)temp_r3 != 0) {
        if (heroItemCheckAddItemDataId(temp_r30, temp_r3) <= 0) {
            _menuCB_errorMsgDisp2__FUl(0x3ACF);
            return;
        }
        heroItemAddItemDataId(temp_r30, temp_r3, 1, -1);
        msgctrlSetValue(0x2D, (u16 *)(u16) pokemonDoItemSoubi(temp_r31, 0U, 0));
        _menuCB_errorMsgDisp2__FUl(0x3ACD);
        return;
    }
    _menuCB_errorMsgDisp2__FUl(0x3ACE);
}

void menuCB_GCEntry_ItemGiveJob(void) {
    s32 temp_r3_2;
    s8 var_r30;
    MenuSubPokemon *temp_r31;
    u16 temp_r26;
    u16 temp_r28;
    u16 temp_r30;
    u16 temp_r3;
    u32 temp_r25;
    u8 temp_r29;
    void *temp_r27;

    temp_r31 = menuCBPokemonPtrGet__FUlUl(_CB.unkB1D4, _CB.unkB1D8);
    temp_r27 = (u8 *)&_CB + 0xA65C;
    msgctrlSetValue(0x32, pokemonBiosGetNicknamePtr(temp_r31));
    if ((s32) menuCBBios_CurrentRule()->unk8 == 1) {
        _menuCB_errorMsgDisp__FUl(0x43A9);
        return;
    }
    menuOpen(0xE6, 1);
    temp_r26 = menuPocket2Call(5, 0, temp_r27);
    temp_r29 = menuPocket2GetLastSlotID();
    menuCloseCustom(0xE6, 0, 1);
    if (temp_r26 != 0) {
        temp_r25 = (u16) _CB.unkB1D8 - 0x1E;
        toolBattleRuleErrorFlagClear(0, temp_r25);
        temp_r28 = pokemonDoItemSoubi(temp_r31, 0U, 0);
        pokemonDoItemSoubi(temp_r31, temp_r26, 1);
        menuCBRule_ErrorFlagSetItemGetTiming(temp_r27, temp_r31, temp_r25);
        pokemonDoItemSoubi(temp_r31, 0U, 0);
        pokemonDoItemSoubi(temp_r31, temp_r28, 1);
        if (menuCB_Trainer_Error_Check(temp_r25, 9) != 0) {
            _menuCB_errorMsgDisp__FUl(0x43AA);
            return;
        }
        if (menuCB_Trainer_Error_Check(temp_r25, 0xA) != 0) {
            _menuCB_errorMsgDisp__FUl(0x43AB);
            return;
        }
        if (menuCB_Trainer_Error_Check(temp_r25, 0xB) != 0) {
            _menuCB_errorMsgDisp__FUl(0x43AC);
            return;
        }
        temp_r3 = pokemonGetSoubiItemDataId(temp_r31);
        if (temp_r3 != 0) {
            msgctrlSetValue(0x2D, (void *)temp_r3);
            winMsgOpen(2, 0x3ACA, 1, 0);
            temp_r3_2 = pokecoloGetCountryCode();
            if (temp_r3_2 != 0) {
                if ((temp_r3_2 >= 0) && (temp_r3_2 < 3)) {
                    var_r30 = menuSubOpenYesNo(0, 0x3C, 0xC8, 0);
                }
            } else {
                var_r30 = menuSubOpenYesNo(0, 0x3C, 0xD2, 0);
            }
            winMsgClose(1);
            if (var_r30 == 0) {
                if (heroItemDecItemDataId(temp_r27, temp_r26, 1, temp_r29) != 0) {
                    _menuCB_errorMsgDisp2__FUl(0x3ACF);
                    return;
                }
                if (heroItemCheckAddItemDataId(temp_r27, temp_r3) <= 0) {
                    heroItemAddItemDataId(temp_r27, temp_r26, 1, -1);
                    _menuCB_errorMsgDisp2__FUl(0x3ACF);
                    return;
                }
                heroItemAddItemDataId(temp_r27, temp_r3, 1, -1);
                temp_r30 = pokemonDoItemSoubi(temp_r31, 0U, 0);
                pokemonDoItemSoubi(temp_r31, temp_r26, 1);
                msgctrlSetValue(0x2D, (u16 *) temp_r30);
                msgctrlSetValue(0x2E, (u16 *) temp_r26);
                _menuCB_errorMsgDisp2__FUl(0x3ACB);
            }
        } else if (heroItemDecItemDataId(temp_r27, temp_r26, 1, temp_r29) == 0) {
            pokemonDoItemSoubi(temp_r31, temp_r26, 1);
            msgctrlSetValue(0x2D, (u16 *) temp_r26);
            _menuCB_errorMsgDisp2__FUl(0x3ACC);
        }
    }
}

void menuCBBattleBABatuMark(MenuSubSprite *arg0, s32 arg1, s32 arg2) {
    f32 temp_f0;
    s32 temp_r30;
    s32 temp_r31;
    MenuSubState *temp_r3;
    MenuSubState *temp_r3_2;

    if ((menuCBBattleStartGetStatus() == 0) || (menuCBPokemonGetDataId(arg1, arg2) == 0)) {
        winSpriteSetDisp(arg0, 0);
        return;
    }
    temp_r31 = arg2 * 4;
    temp_r30 = arg1 * 0x18;
    temp_r3 = (MenuSubState *)((u8 *)&_CB + temp_r30 + temp_r31);
    if ((temp_r3->unkB248 == 0.0f) && (temp_r3->unkB1E8 == 0.0f)) {
        winSpriteSetDisp(arg0, 1);
        temp_r3_2 = (MenuSubState *)((u8 *)&_CB + temp_r30 + temp_r31);
        temp_r3_2->unkB368 = (f32) (temp_r3_2->unkB368 + temp_r3_2->unkB3C8);
        if (temp_r3_2->unkB368 >= 1.0f) {
            temp_r3_2->unkB368 = 1.0f;
        }
        temp_f0 = temp_r3_2->unkB368;
        arg0->unk6C = temp_f0;
        arg0->unk68 = temp_f0;
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void menuCBBattleEndSetPokemonHP(void) {
    MenuSubState *var_r30;
    MenuSubState *var_r31;
    f32 var_f31;
    s32 var_r27;
    s32 var_r28;
    MenuSubPokemon *temp_r3;

    var_f31 = 0.0f;
    var_r30 = &_CB;
    var_r28 = 0;
    do {
        var_r31 = var_r30;
        var_r27 = 0;
loop_2:
        temp_r3 = toolentryTaisenGetEntryPokemonPtr(var_r28, var_r27);
        if (temp_r3 != NULL) {
            var_r31->unkB1E8 = (f32) pokemonBiosGetHp(temp_r3);
            var_r31->unkB248 = (f32) pokemonBiosGetMaxHp(temp_r3);
            var_r31->unkB2A8 = (f32) pokemonBiosGetMaxHp(temp_r3);
            var_r31->unkB308 = (f32) ((var_r31->unkB2A8 - var_r31->unkB1E8) / 60.0f);
            var_r31->unkB368 = 0.0f;
            var_f31 += var_r31->unkB308;
            var_r31->unkB3C8 = 0.06666667f;
        } else {
            var_r31->unkB2A8 = 100.0f;
            var_r31->unkB3C8 = 0.0f;
            var_r31->unkB368 = 0.0f;
            var_r31->unkB308 = 0.0f;
            var_r31->unkB248 = 0.0f;
            var_r31->unkB1E8 = 0.0f;
        }
        var_r31 = (MenuSubState *)((u8 *)var_r31 + 4);
        var_r27 += 1;
        if (var_r27 < 6) {
            goto loop_2;
        }
        var_r30 = (MenuSubState *)((u8 *)var_r30 + 0x18);
        var_r28 += 1;
    } while (var_r28 < 4);
    if (var_f31 != 0.0f) {
        _CB.unkB180 = 0x5D0;
    } else {
        _CB.unkB180 = 0;
    }
    battleEndHPStartFlag = 0x1E;
    battleEndHPEndFlag = 0x87;
}

void menuCB_BattleBA_HPBarDispSet(MenuSubSprite *arg0, s32 arg1, s32 arg2) {
    f32 temp_f1;
    f32 temp_f4;
    f32 temp_f5;
    MenuSubState *temp_r3;
    MenuSubState *temp_r3_2;

    if ((menuCBBattleStartGetStatus() != 0) && (menuCBPokemonGetDataId(arg1, arg2) != 0)) {
        winSpriteSetDisp(arg0, 1);
        if ((u16) battleEndHPStartFlag == 0) {
            temp_r3 = (MenuSubState *)((u8 *)&_CB + (arg1 * 0x18) + (arg2 * 4));
            temp_r3->unkB248 = (f32) (temp_r3->unkB248 - temp_r3->unkB308);
            temp_f1 = temp_r3->unkB1E8;
            if (temp_r3->unkB248 < temp_f1) {
                temp_r3->unkB248 = temp_f1;
            }
        } else {
            if (pauseIsPause() == 0) {
                battleEndHPStartFlag -= 1;
            }
            if (((u16) battleEndHPStartFlag == 0) && ((s32) _CB.unkB180 != 0)) {
                menuCB_SE_Play(0x5D0);
            }
        }
        temp_r3_2 = (MenuSubState *)((u8 *)&_CB + (arg1 * 0x18) + (arg2 * 4));
        temp_f4 = temp_r3_2->unkB2A8;
        temp_f5 = temp_r3_2->unkB248;
        if (temp_f5 <= ((20.0f * temp_f4) / 100.0f)) {
            menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[2]));
        } else {
            if (temp_f5 <= ((50.0f * temp_f4) / 100.0f)) {
                menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[1]));
            } else {
                menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_HP_Bar_Char[0]));
            }
        }
        arg0->unk54 = (s16) (48.0f * ((temp_f4 - (temp_f4 - temp_f5)) / temp_f4));
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void menuCB_BattleBA_FacePanelSet(MenuSubSprite *arg0, s32 arg1, s32 arg2) {
    if (menuCBPokemonGetDataId(arg1, arg2) != 0) {
        winSpriteSetDisp(arg0, 1);
        if (menuCBBattleStartGetStatus() == 0) {
            menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_FACEWAKU_Char[1]));
            return;
        }
        menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_FACEWAKU_Char[0]));
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void menuCB_PrintXP(MenuSubSprite *arg0, s32 arg1) {
    menuCB_SetSprite(arg0, menuSpriteBiosGetPtr(BATTLE_BA_XP_PRINT_Char[toolentryTaisenGetBattlePlayerID(arg1)]));
}

void _menuCBGCDelPokemon__Fv(void) {
    s32 temp_r3;
    MenuSubPokemon *temp_r27_2;
    MenuSubPokemon *temp_r30;
    MenuSubPokemon *temp_r3_2;
    u32 *var_r29;
    u32 *var_r30;
    u32 temp_r27;
    u32 temp_r28;
    u32 temp_r5;
    u32 var_r31;

    switch ((s32) _CB.unkB0F8) {
    case 30:
        var_r31 = 0;
        break;
    case 31:
        var_r31 = 1;
        break;
    case 32:
        var_r31 = 2;
        break;
    case 33:
        var_r31 = 3;
        break;
    case 34:
        var_r31 = 4;
        break;
    case 35:
        var_r31 = 5;
        break;
    }
    temp_r27 = backup_type[var_r31];
    temp_r28 = backup_index[var_r31];
    backup_type[var_r31] = 0U;
    backup_index[var_r31] = 0;
    menuCBGCEntryTypeIndex();
    temp_r30 = menuCBPokemonPtrGet__FUlUl(_CB.unkB1D4, _CB.unkB1D8);
    temp_r3 = pokecoloGetCountryCode();
    if (temp_r3 != 0) {
        if ((temp_r3 >= 0) && (temp_r3 < 3)) {
            memcpy(menuCBPokemonPtrGet__FUlUl(temp_r27, temp_r28), temp_r30, 0xC4);
            pokemonInit(temp_r30);
        }
    } else if (temp_r27 != 6U) {
        memcpy(menuCBPokemonPtrGet__FUlUl(temp_r27, temp_r28), temp_r30, 0xC4);
        pokemonInit(temp_r30);
    } else {
        insertDancer__12CReliveStageFR7Pokemonl(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r28 >> 0x10U), temp_r30, 0);
    }
    var_r30 = &backup_type[var_r31];
    var_r29 = &backup_index[var_r31];
loop_25:
    if (var_r31 < 5U) {
        temp_r27_2 = menuCBPokemonPtrGet__FUlUl(7U, var_r31);
        temp_r5 = var_r29[1];
        var_r30[0] = var_r30[1];
        var_r29[0] = temp_r5;
        var_r30[1] = 0U;
        var_r29[1] = 0U;
        temp_r3_2 = menuCBPokemonPtrGet__FUlUl(7U, var_r31 + 1);
        memcpy(temp_r27_2, temp_r3_2, 0xC4);
        pokemonInit(temp_r3_2);
        var_r30 += 1;
        var_r29 += 1;
        var_r31 += 1;
        goto loop_25;
    }
    _CB.unkB100 = (s32) (_CB.unkB100 - 1);
}

u8 menuCBGCEntry_ErrorDisp__FUlUl(u32 arg0, u32 arg1) {
    MenuSubPokemon *temp_r31;
    u32 temp_r30;
    u8 temp_r3;
    u8 temp_r3_2;
    MenuSubState *temp_r5;

    temp_r30 = _CB.unkB100 - 1;
    temp_r31 = menuCBPokemonPtrGet__FUlUl(arg0, arg1);
    toolBattleRuleErrorFlagClear(0, temp_r30);
    menuCBRule_ErrorFlagSetPokemonGetTiming((u8 *)&_CB + 0xA65C, temp_r31, temp_r30);
    _CB.unkB0D8 = 0;
    if (menuCB_Trainer_Error_Check(temp_r30, -1) != 0) {
        menuCBGCDelPokemon();
        _CB.unkB0FC = 2;
        temp_r5 = (MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + (temp_r30 * 4));
        temp_r3 = temp_r5->unk9C84;
        if ((u32) ((temp_r3 >> 7U) & 1) != 0) {
            _CB.unkB1DC = 0x43AF;
            return 0U;
        }
        if ((u32) ((temp_r3 >> 6U) & 1) != 0) {
            _CB.unkB1DC = 0x43A2;
            return 0U;
        }
        if (((u32) ((temp_r3 >> 5U) & 1) != 0) || ((u32) ((temp_r3 >> 4U) & 1) != 0)) {
            _CB.unkB1DC = 0x43B0;
            return 0U;
        }
        if ((u32) ((temp_r3 >> 3U) & 1) != 0) {
            _CB.unkB1DC = 0x43A5;
            return 0U;
        }
        if ((u32) ((temp_r3 >> 2U) & 1) != 0) {
            _CB.unkB1DC = 0x43A6;
            return 0U;
        }
        if ((u32) ((temp_r3 >> 1U) & 1) != 0) {
            _CB.unkB1DC = 0x43A7;
            return 0U;
        }
        if (((u32) (temp_r3 & 1) != 0) || (temp_r3_2 = temp_r5->unk9C85, (((u32) ((temp_r3_2 >> 1U) & 1) == 0) == 0))) {
            _CB.unkB1DC = 0x43A8;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 7U) & 1) != 0) {
            _CB.unkB1DC = 0x43A9;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 6U) & 1) != 0) {
            _CB.unkB1DC = 0x43AA;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 5U) & 1) != 0) {
            _CB.unkB1DC = 0x43AB;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 4U) & 1) != 0) {
            _CB.unkB1DC = 0x43AC;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 3U) & 1) != 0) {
            _CB.unkB1DC = 0x43AD;
            return 0U;
        }
        if ((u32) ((temp_r3_2 >> 2U) & 1) != 0) {
            _CB.unkB1DC = 0x43AE;
            return 0U;
        }
        return 0U;
    }
    return 1U;
}

s32 menuCB_GCEntry_SubWindow_Disp(void) {
    s16 var_r5;
    s16 var_r7;
    u16 var_r4;

    if (_CB.unkAFF0 == 1) {
        winMsgOpen(2, 0x43A1, 1, 0);
        switch (pokecoloGetCountryCode()) {
        case 0:
            _CB.unkAFE0 = menuSubOpenYesNo(0, 0x3C, 0xD2, 0);
            break;
        case 1:
        case 2:
            _CB.unkAFE0 = menuSubOpenYesNo(0, 0x3C, 0xC8, 0);
            break;
        }
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 1;
        }
        winMsgClose(0);
        return _CB.unkAFE0;
    }
    menuCBGCEntryTypeIndex();
    var_r4 = _CB.unkB1D8;
    if ((var_r4 >= 0x1E) && (var_r4 <= 0x23)) {
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg2, 4, 0x28, 0x64, 0, 4, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 3;
        }
        switch (_CB.unkAFE0) {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            winMsgOpen(2, 0x43A0, 0, 0);
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg3, 3, 0x28, 0x64, 0, 3, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 2;
            }
            switch (_CB.unkAFE0) {
            case 0:
                winMsgClose(0);
                return 4;
            case 1:
                return 5;
            case 2:
                winMsgClose(0);
                return 6;
            }
            break;
        case 3:
            return 6;
        }
    } else {
        var_r5 = 0x104;
        var_r7 = 0xC8;
        switch (_CB.unkB0F0) {
        case 1:
            var_r5 = submenu1_x[var_r4];
            var_r7 = submenu1_y[var_r4];
            break;
        case 0:
        case 4:
            break;
        }
        if (_CB.unkB100 == 6) {
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg1s, 2, var_r5, var_r7, 0, 2, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 1;
            }
        } else {
            _CB.unkAFE0 = menuSubOpenSelect2(0, submenu_msg1, 3, var_r5, var_r7, 0, 3, 1);
            if (_CB.unkAFE0 == -1) {
                _CB.unkAFE0 = 2;
            }
        }
        if (_CB.unkB100 == 6) {
            switch (_CB.unkAFE0) {
            case 0:
                return 2;
            case 1:
                return 6;
            }
        } else {
            switch (_CB.unkAFE0) {
            case 0:
                return 0;
            case 1:
                return 2;
            case 2:
                return 6;
            }
        }
    }
    return 6;
}

void menuCB_TUNAIDE01_Rule_SELECT(void) {
    switch (_CB.unkB004) {
    case 0:
    case 1:
    case 2:
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenurule_msg1, 3, 0x28, 0xF4, _CB.unkAFE0, 3, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 2;
        }
        break;
    case 3:
    case 4:
    case 5:
        _CB.unkAFE0 = menuSubOpenSelect2(0, submenurule_msg2, 4, 0x28, 0xD4, _CB.unkAFE0, 4, 1);
        if (_CB.unkAFE0 == -1) {
            _CB.unkAFE0 = 3;
        }
        _CB.unkAFE0 += 0x10;
        break;
    }
    switch (_CB.unkAFE0) {
    case 0:
    case 0x10:
        _CB.unkB10C = 0;
        break;
    case 2:
    case 0x13:
        _CB.unkB10C = 1;
        break;
    }
}

typedef struct MenuSubPos { s16 x; s16 y; } MenuSubPos;

void menuCB2DPokemonDisp2(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2, u32 arg3) {
    MenuSubPokemon *pokemon;
    u32 idx;
    MenuSubPos pos;
    MenuSubPos tmp;
    MenuSubAnt *ptr;

    pokemon = menuCBPokemonPtrGet__FUlUl(arg2, arg3);
    idx = menuCBPokemonGetIndex__FUlUl(arg2, arg3);
    if ((pokemon != NULL) && (pokemonCheckValid(pokemon) != 0)) {
        spriteSetOffset(arg0->unk1C, 0, 0);
        spriteClearScissor(arg0->unk1C);
        spriteSetEnv(arg0->unk1C);
        if (idx < 0x1E) {
            spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
        }
        pos.x = 0x20 + arg1->unk50 + arg0->unk8C;
        pos.y = 0x20 + arg1->unk52;
        if (_CB.unkB150 < 0) {
            ptr = &antR[idx];
            initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(ptr, pokemon);
            tmp = pos;
            antR[idx].unk8 = tmp.x;
            antR[idx].unkA = tmp.y;
            setAnimation__4CAntFl(ptr, 0);
            GSprimSetup2DRender__FP10GSgfxLayer(0);
            if (ptr->unk0 != 0) {
                antR[idx].unk10 = arg0->unk93;
                drawAndUpdate__4CAntFv(ptr);
            }
        } else {
            ptr = &antL[idx];
            initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(ptr, pokemon);
            tmp = pos;
            antL[idx].unk8 = tmp.x;
            antL[idx].unkA = tmp.y;
            setAnimation__4CAntFl(ptr, 0);
            GSprimSetup2DRender__FP10GSgfxLayer(0);
            if (ptr->unk0 != 0) {
                antL[idx].unk10 = arg0->unk93;
                drawAndUpdate__4CAntFv(ptr);
            }
        }
    }
}

void menuCB2DPokemonDisp(MenuSubWindow *arg0, MenuSubSprite *arg1, u32 arg2, u32 arg3) {
    MenuSubAnt *ptr;
    MenuSubPokemon *pokemon;
    u32 idx;
    MenuSubPos pos;
    MenuSubPos tmp;

    pokemon = menuCBPokemonPtrGet__FUlUl(arg2, arg3);
    idx = menuCBPokemonGetIndex__FUlUl(arg2, arg3);
    if (idx == 0x1E) {
        _menuCB2DPokemonNewSet__FUc(0);
        _menuCB2DPokemonNewSet__FUc(1);
    }
    if ((pokemon != NULL) && (pokemonCheckValid(pokemon) != 0)) {
        spriteSetOffset(arg0->unk1C, 0, 0);
        spriteClearScissor(arg0->unk1C);
        spriteSetEnv(arg0->unk1C);
        if (idx < 0x1E) {
            spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
        }
        pos.x = 0x20 + arg1->unk50 + arg0->unk8C;
        pos.y = 0x20 + arg1->unk52;
        ptr = &ant[idx];
        initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(ptr, pokemon);
        tmp = pos;
        ant[idx].unk8 = tmp.x;
        ant[idx].unkA = tmp.y;
        setAnimation__4CAntFl(ptr, 0);
        GSprimSetup2DRender__FP10GSgfxLayer(0);
        if (ptr->unk0 != 0) {
            ant[idx].unk10 = arg0->unk93;
            drawAndUpdate__4CAntFv(ptr);
        }
    }
}

void menuCBPokemonEntryBallAnaDisp(MenuSubSprite *arg0, s32 arg1, u32 arg2) {
    u16 var_r31;
    u16 temp_r3;

    var_r31 = menuCBBios_ParticipationPokemonMax();
    temp_r3 = toolentryTaisenGetPokemonNum(arg1);
    _CB.unkB426[arg1][arg2] = arg0->unk50;
    if (_CB.unkB487[arg1][arg2] == 0) {
        _CB.unkB456[arg1][arg2] = 0x32;
    }
    temp_r3 = (temp_r3 < var_r31) ? temp_r3 : var_r31;
    if (arg2 > temp_r3) {
        winSpriteSetDisp(arg0, 0);
    } else {
        winSpriteSetDisp(arg0, 1);
    }
}

void menuCBPokemonEntryBallDisp(MenuSubSprite *arg0, s32 arg1, u32 arg2) {
    MenuSubPlayer *players;
    u16 var_r28;
    u16 var_r27;
    u16 temp_r3;
    u16 var_r0;

    var_r28 = menuCBBios_ParticipationPokemonMax();
    var_r27 = toolentryTaisenGetPokemonNum(arg1);
    temp_r3 = toolentryTaisengetEtnryPokemonOrderNum(arg1);
    if (var_r27 < var_r28) {
        var_r0 = var_r27;
    } else {
        var_r0 = var_r28;
    }
    if ((arg2 > var_r0) || (arg2 > temp_r3)) {
        if (pauseIsPause() != 0) {
            if (_CB.unkB487[arg1][arg2] == 0) {
                winSpriteSetDisp(arg0, 0);
                return;
            }
            winSpriteSetDisp(arg0, 1);
            return;
        }
        winSpriteSetDisp(arg0, 0);
        _CB.unkB487[arg1][arg2] = 0;
        return;
    }
    if (pauseIsPause() != 0) {
        if (_CB.unkB487[arg1][arg2] != 1) {
            winSpriteSetDisp(arg0, 0);
            _CB.unkB487[arg1][arg2] = 0;
            return;
        }
    }
    _CB.unkB487[arg1][arg2] = 1;
    arg0->unk50 = _CB.unkB426[arg1][arg2] + _CB.unkB456[arg1][arg2];
    if (_CB.unkB456[arg1][arg2] != 0) {
        _CB.unkB456[arg1][arg2] -= 5;
    }
    winSpriteSetDisp(arg0, 1);
    players = (MenuSubPlayer *)&_CB;
    if (players[arg1].unk1C[arg2] == 0xF) {
        winSpriteSetDisp(arg0, 0);
    }
}

void menuCB_GCEntry_OkPushErrorCheck(void) {
    u8 *temp_r31;
    u32 c;
    u32 i;
    u32 a;

    for (a = 0; a < 6U; a++) {
        toolBattleRuleErrorFlagClear(0, a);
    }
    temp_r31 = (u8 *)&_CB + 0xA65C;
    menuCBRule_ErrorFlagSet(temp_r31, 0);
    for (i = 0; i < 6U; i++) {
        if (menuCB_Trainer_Error_Check(i, 8) != 0) {
            _CB.unkB1DC = 0x43A9;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i, 9) != 0) {
            _CB.unkB1E0 = (s32) (i + 1);
            _CB.unkB1DC = 0x4410;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i, 0xA) != 0) {
            _CB.unkB1DC = 0x43AB;
            _CB.unkB0FC = 2;
            return;
        }
        if (menuCB_Trainer_Error_Check(i, 0xB) != 0) {
            _CB.unkB1DC = 0x43AC;
            _CB.unkB0FC = 2;
            return;
        }
    }
    for (c = 0; c < 6U; c++) {
        toolBattleRuleErrorFlagClear(0, c);
    }
    menuCBRule_ErrorFlagSetOkPushTiming(temp_r31);
    if (menuCB_Trainer_Error_Check(0U, -1) != 0) {
        _CB.unkB0FC = 2;
        if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18)))->unk9C85 >> 2U) & 1) != 0) {
            _CB.unkB1DC = 0x43AE;
        }
    }
}

void menuCB_WaitGCControler1(void) {
    s32 var_r4;

    if (GSinputIsConnected(1) == 0) {
        if (gbaCommandIsConnected(1) != 0) {
            var_r4 = 0x442D;
        } else {
            var_r4 = 0x4436;
        }
        winMsgOpen(2, var_r4, 0, 0);
loop_6:
        if (GSinputIsConnected(1) == 0) {
            GSthreadSwitch();
            goto loop_6;
        }
        winMsgClose(1);
    }
}

void menuCB_GBADisconnectedErrorJob(void) {
    s32 temp_r3;

    temp_r3 = menuCB_GetDisconnectedGBA();
    switch (temp_r3) {
    case 0:
        if (gbaCommandIsConnected(1) != 0) {
            winMsgOpen(2, 0x442D, 0, 0);
loop_7:
            if (GSinputIsConnected(1) == 0) {
                GSthreadSwitch();
                goto loop_7;
            }
        } else {
            winMsgOpen(2, 0x442C, 1, 0);
        }
        break;
    case 1:
        winMsgOpen(2, 0x4438, 0, 0);
loop_12:
        if (GSinputIsConnected(1) == 0) {
            GSthreadSwitch();
            goto loop_12;
        }
        break;
    default:
        if (gbaCommandIsConnected(1) != 0) {
            winMsgOpen(2, 0x442D, 0, 0);
loop_17:
            if (GSinputIsConnected(1) == 0) {
                GSthreadSwitch();
                goto loop_17;
            }
        } else {
            msgctrlSetValue(0x2F, (u16 *) temp_r3);
            winMsgOpen(2, 0x442B, 1, 0);
        }
        break;
    }
    winMsgClose(1);
    menuCB_WaitGCControler1();
}

void menuCBPokemonEntryGCControlDisp(MenuSubWindow *arg0, s32 arg1) {
    if ((menuCBPokemonEntryDisp(arg0) != 0) && (menuCBPokemonGetDataId(0, arg1) == 0)) {
        winSpriteSetDisp(arg0, 0);
    }
}

void menuCBGCDelPokemon(void) {
    s32 temp_r30;

    temp_r30 = _CB.unkB0F8;
    switch ((s32) _CB.unkB100) {
    case 1:
        _CB.unkB0F8 = 0x1E;
        break;
    case 2:
        _CB.unkB0F8 = 0x1F;
        break;
    case 3:
        _CB.unkB0F8 = 0x20;
        break;
    case 4:
        _CB.unkB0F8 = 0x21;
        break;
    case 5:
        _CB.unkB0F8 = 0x22;
        break;
    case 6:
        _CB.unkB0F8 = 0x23;
        break;
    }
    _menuCBGCDelPokemon__Fv();
    _CB.unkB0F8 = temp_r30;
}

void menuCBGCEntryPokemon(void) {
    s32 temp_r3;
    MenuSubPokemon *temp_r28;
    MenuSubPokemon *temp_r3_2;
    MenuSubPokemon *temp_r3_3;
    u32 temp_r29;
    u32 temp_r30;

    menuCBGCEntryTypeIndex();
    if (menuCBPokemonCheck(_CB.unkB1D4, _CB.unkB1D8) != 0) {
        if ((s32) _CB.unkB0F8 >= 0x1E) {
            _menuCBGCDelPokemon__Fv();
            return;
        }
        if ((s32) _CB.unkB100 != 6) {
            menuCBGCEntryTypeIndex();
            temp_r29 = _CB.unkB1D4;
            temp_r30 = _CB.unkB1D8;
            backup_type[_CB.unkB100] = temp_r29;
            backup_index[_CB.unkB100] = temp_r30;
            temp_r28 = menuCBPokemonPtrGet__FUlUl(7U, (u32) _CB.unkB100);
            temp_r3 = pokecoloGetCountryCode();
            if (temp_r3 != 0) {
                if ((temp_r3 >= 0) && (temp_r3 < 3)) {
                    if ((temp_r29 == 6U) && ((s32) _CB.unkB0F8 == 4)) {
                        backup_type[_CB.unkB100] = 0U;
                        backup_index[_CB.unkB100] = 0;
                        _CB.unkB0FC = 2;
                        _CB.unkB1DC = 0x43A5;
                        return;
                    }
                    temp_r3_2 = menuCBPokemonPtrGet__FUlUl(temp_r29, temp_r30);
                    memcpy(temp_r28, temp_r3_2, 0xC4);
                    pokemonInit(temp_r3_2);
                    goto block_17;
                }
                goto block_17;
            }
            if (temp_r29 != 6U) {
                temp_r3_3 = menuCBPokemonPtrGet__FUlUl(temp_r29, temp_r30);
                memcpy(temp_r28, temp_r3_3, 0xC4);
                pokemonInit(temp_r3_3);
                goto block_17;
            }
            if ((s32) _CB.unkB0F8 == 4) {
                backup_type[_CB.unkB100] = 0U;
                backup_index[_CB.unkB100] = 0;
                _CB.unkB0FC = 2;
                _CB.unkB1DC = 0x43A5;
                return;
            }
            pickupDancer__12CReliveStageFR7Pokemonl(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r30 >> 0x10U), temp_r28, (u16)temp_r30);
block_17:
            _CB.unkB100 = (s32) (_CB.unkB100 + 1);
            if ((menuCBGCEntry_ErrorDisp__FUlUl(temp_r29, _CB.unkB100 + 0x1D) != 0) && ((s32) _CB.unkB100 == 6)) {
                _CB.unkB0F8 = 0x25;
            }
        }
    }
}

void menuCB_Trainer_Error_Disp(MenuSubWindow *arg0, MenuSubSprite *arg1, s32 arg2, s32 arg3) {
    s32 temp_r0;
    s32 var_r5;
    u8 temp_r8;
    MenuSubState *temp_r7;

    var_r5 = arg2;
    {
        s32 i;
        for (i = 0; i < 14; i++) {
            err_msgID[i] = 0;
            err_msgID2[i] = 0;
        }
    }
    temp_r0 = var_r5 * 4;
    _CB.unkB0E4 = 0;
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84 >> 7U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x43FD;
        err_msgID2[_CB.unkB0E4] = 0x43AF;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84 >> 6U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x43FE;
        err_msgID2[_CB.unkB0E4] = 0x43A2;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    temp_r8 = ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84;
    if (((u32) ((temp_r8 >> 5U) & 1) != 0) || ((u32) ((temp_r8 >> 4U) & 1) != 0)) {
        err_msgID[_CB.unkB0E4] = 0x43FF;
        err_msgID2[_CB.unkB0E4] = 0x43B0;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84 >> 3U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4400;
        err_msgID2[_CB.unkB0E4] = 0x43A5;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84 >> 2U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4401;
        err_msgID2[_CB.unkB0E4] = 0x43A6;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C84 >> 1U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4402;
        err_msgID2[_CB.unkB0E4] = 0x43A7;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    temp_r7 = (MenuSubState *)((u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0);
    if (((u32) (temp_r7->unk9C84 & 1) != 0) || ((u32) (((u8) temp_r7->unk9C85 >> 1U) & 1) != 0)) {
        err_msgID[_CB.unkB0E4] = 0x4403;
        err_msgID2[_CB.unkB0E4] = 0x43A8;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 7U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4404;
        err_msgID2[_CB.unkB0E4] = 0x43A9;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 6U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4405;
        err_msgID2[_CB.unkB0E4] = 0x43AA;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 5U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4406;
        err_msgID2[_CB.unkB0E4] = 0x43AB;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 4U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4407;
        err_msgID2[_CB.unkB0E4] = 0x43AC;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 3U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4408;
        err_msgID2[_CB.unkB0E4] = 0x43AD;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    if ((u32) (((u8) ((MenuSubState *)((u8 *)(u8 *)&_CB + (_CB.unkB0D8 * 0x18) + temp_r0))->unk9C85 >> 2U) & 1) != 0) {
        err_msgID[_CB.unkB0E4] = 0x4409;
        err_msgID2[_CB.unkB0E4] = 0x43AE;
        _CB.unkB0E4 = (s32) (_CB.unkB0E4 + 1);
    }
    err_msgID[_CB.unkB0E4] = 0x435E;
    err_msgID2[_CB.unkB0E4] = 0;
    switch (arg3) {
    case 0:
        var_r5 = 0;
        break;
    case 1:
        var_r5 = 7;
        break;
    }
    arg1->unk4C = (s32) err_msgID[var_r5];
    if ((u32) err_msgID[var_r5 + 1] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0x20, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 1]);
    }
    if ((u32) err_msgID[var_r5 + 2] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0x40, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 2]);
    }
    if ((u32) err_msgID[var_r5 + 3] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0x60, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 3]);
    }
    if ((u32) err_msgID[var_r5 + 4] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0x80, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 4]);
    }
    if ((u32) err_msgID[var_r5 + 5] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0xA0, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 5]);
    }
    if ((u32) err_msgID[var_r5 + 6] != 0U) {
        GSmsgPrint2(arg0->unk1C, 0, 0xC0, arg0->unk93 | ~0xFF, err_msgID[var_r5 + 6]);
    }
}

void menuCB_Pokemon_ErrorDisp(MenuSubWindow *arg0, s32 arg1) {
    u8 *temp_r31;
    u8 *temp_r29;

    _CB.unkB0D8 = (s32) (s8) arg1;
    menuCBPokemonEntryPokemonFaceFree();
    menuCBBattleStartSetStatus(0);
    temp_r29 = (u8 *)&_CB + 0x9CE4;
    temp_r31 = (u8 *)&_CB + (arg1 * 0x1320) + 0x9BC;
    heroBiosCopy(temp_r29, temp_r31);
    heroBiosCopy(temp_r31, arg0);
    menuCBPokemonEntryLoadTex();
    menuCBpokemonFaceReadWait();
    _CB.unkB088 = 0;
    _CB.unkB008 = 0;
    _menuCB_ErrorTAMAGOCheck__Fv();
    _CB.unkB0DC = 5;
    if (_menuCBPokemon_ErrorDispSet__Fl(5) == 0) {
        _CB.unkB0DC = 4;
    }
    if (_menuCBPokemon_ErrorDispSet__Fl(4) == 0) {
        _CB.unkB0DC = 3;
    }
    if (_menuCBPokemon_ErrorDispSet__Fl(3) == 0) {
        _CB.unkB0DC = 2;
    }
    if (_menuCBPokemon_ErrorDispSet__Fl(2) == 0) {
        _CB.unkB0DC = 1;
    }
    if (_menuCBPokemon_ErrorDispSet__Fl(1) == 0) {
        _CB.unkB0DC = 0;
    }
    if (_menuCBPokemon_ErrorDispSet__Fl(0) == 0) {
        _CB.unkB0DC = -1;
    }
    menuCB_SE_Play(0x14);
loop_13:
    menuOpen(0xA6, 1);
    if (((s32) _CB.unkB008 != 6) && ((s32) _CB.unkB088 != 1)) {
        _CB.unkB08C = 0;
        _CB.unkB00C = 0;
loop_16:
        menuOpenCustom(0xA7, windowGetActiveID(), (u8 *)&_CB + 0xB00C, 0, 1, 0);
        if (((s32) _CB.unkB00C != (s32) _CB.unkB0E4) && ((s32) _CB.unkB08C != 1)) {
            _menuCB_errorMsgDisp__FUl(err_msgID2[_CB.unkB00C]);
            goto loop_16;
        }
        menuCloseCustom(0xA7, 0, 1);
        goto loop_13;
    }
    menuCB_SE_Play(0x15);
    menuCloseCustom(0xA6, 0, 1);
    menuCBPokemonEntryPokemonFaceFree();
    heroBiosCopy(temp_r31, temp_r29);
}

#pragma pool_strings off
void toolbattle_drawHeroID(MenuSubWindow *arg0, s32 arg1) {
    u16 sp88[64];
    char sp8[128];
    s32 temp_r4;
    s32 temp_ret;

    temp_r4 = arg1 * 0x1320;
    temp_ret = heroBiosGetRnd((u8 *)&_CB + temp_r4 + 0x563C);
    sprintf(sp8, "%1d%1d%1d%1d%1d", (u8) ((temp_ret / 10000) % 10), (u8) ((temp_ret / 1000) % 10), (u8) ((temp_ret / 100) % 10), (u8) ((temp_ret / 10) % 10), (u8) (temp_ret % 10));
    GScharMakeFromSJIS(sp88, sp8);
    _drawStrings__FP14tagWINDOW_WORKPUsllUl(arg0, sp88, 0, 0, 0x43C4);
}
#pragma pool_strings on

/* Trainer portrait rendering and the animated entry selection corners. */
typedef struct MenuSubTexture{u8 reserved0[7];u8 dirty;}MenuSubTexture;
typedef struct MenuSubLayer{u8 reserved0[0x173C];u32 flags0;MenuSubTexture*texture0;u8 reserved1744[0xB0];u32 flags1;MenuSubTexture*texture1;u8 reserved17FC[0x19C];u32 primitive;}MenuSubLayer;
MenuSubLayer*GSgfxLayerFindByID(s32);
void*GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void*,void*);
void beginSurface__10GSgfxLayerFUs(void*,u16);
void endSurface__10GSgfxLayerFv(void*);
void menuCBBattleStartDispTrainerFaceSub(MenuSubWindow*window,MenuSubSprite*sprite,u32 index){
    MenuSubTexture*texture;
    MenuSubLayer*layer;
    u8 alpha=window->unk93;
    layer=GSgfxLayerFindByID(window->unk1C);
    texture=(MenuSubTexture*)_menuCBBattleStartWork.faces[index].texture;
    if(texture){
        layer->primitive=0x98;
        setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer,GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));
        if(layer->texture0!=texture||layer->texture1!=texture||texture->dirty){layer->texture0=texture;layer->flags0|=1;layer->texture1=texture;layer->flags1|=1;}
        beginSurface__10GSgfxLayerFUs(layer,4);
#define SUB_POS(x,y) *(s16*)0xCC008000=(x);*(s16*)0xCC008000=(y)
#define SUB_COLOR() *(u8*)0xCC008000=255;*(u8*)0xCC008000=255;*(u8*)0xCC008000=255;*(u8*)0xCC008000=alpha
#define SUB_UV(x,y) *(f32*)0xCC008000=(x);*(f32*)0xCC008000=(y)
        SUB_POS(0,0);SUB_COLOR();SUB_UV(0.0f,0.0f);
        SUB_POS(sprite->unk54,0);SUB_COLOR();SUB_UV(1.0f,0.0f);
        SUB_POS(0,sprite->unk56);SUB_COLOR();SUB_UV(0.0f,1.0f);
        {s16 height=sprite->unk56;SUB_POS(sprite->unk54,height);SUB_COLOR();SUB_UV(1.0f,1.0f);}
#undef SUB_POS
#undef SUB_COLOR
#undef SUB_UV
        endSurface__10GSgfxLayerFv(layer);
    }
}
f32 _f_menuCB_circleAnimationTime;
f32 timeGetLastFrameSec(void);double fmod(double,double);
typedef struct MenuSubSpriteValue{u8 reserved0[4];s16 width,height;}MenuSubSpriteValue;
MenuSubSpriteValue*menuSpriteBiosGetValPtr(void*);
void menuPtSpriteDrawColor__FUsllllUl(u16,s32,s32,s32,s32,u32);
void menuPtSpriteDrawColor__FUsllUl(u16,s32,s32,u32);
void menuCB_GCEntryCursolDisp(MenuSubWindow*window,MenuSubSprite*sprite,u8 enabled){
    if(enabled){
        u32 color;MenuSubSpriteValue*value;s32 width,height,offset,nearCorner,farCorner,negativeWidth,negativeHeight;
        f32 phase=_f_menuCB_circleAnimationTime/0.5f;
        if(phase>0.5f)phase=1.0f-phase;
        phase=2.0f*phase;
        _f_menuCB_circleAnimationTime+=timeGetLastFrameSec();
        if(_f_menuCB_circleAnimationTime>=0.5f)_f_menuCB_circleAnimationTime=fmod(_f_menuCB_circleAnimationTime,0.5);
        color=window->unk93|~0xFF;
        value=menuSpriteBiosGetValPtr((void*)menuSpriteBiosGetPtr(0x216));
        width=value->width;height=value->height;
        offset=(s16)(5.0f*phase);
        if(offset>4)offset=4;
        nearCorner=(s16)(offset+4);
        menuPtSpriteDrawColor__FUsllllUl(0x216,nearCorner,nearCorner,width,height,color);
        farCorner=(s16)(0x32-offset);
        negativeWidth=-width;
        menuPtSpriteDrawColor__FUsllllUl(0x216,farCorner,nearCorner,negativeWidth,height,color);
        negativeHeight=-height;
        menuPtSpriteDrawColor__FUsllllUl(0x216,nearCorner,farCorner,width,negativeHeight,color);
        menuPtSpriteDrawColor__FUsllllUl(0x216,farCorner,farCorner,negativeWidth,negativeHeight,color);
        menuPtSpriteDrawColor__FUsllUl(0x214,7,0x23,color);
    }
}
