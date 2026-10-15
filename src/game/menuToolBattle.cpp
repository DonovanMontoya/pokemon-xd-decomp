#include <dolphin/types.h>
struct BattleControl {s32 unk0;s32 unk4;s32 unk8;u8 padC[45040];s32 unkAFFC;u8 padB000[320];s32 unkB140;u8 padB144[44];s32 unkB170;s32 unkB174;s32 unkB178;u8 padB17C[8];s32 unkB184;u8 padB188[20];s32 unkB19C;u8 padB1A0[68];s16 unkB1E4;};
struct SaveStatus {u8 pad[0x959];u8 unk959;};
extern "C" {extern BattleControl _CB;u8 FlashSystemIsLastFrame(u32);void FlashSystemSetLoopFlag(u32,s32);void FlashSystemSetNowFrameLabel(u32,const char*);void FlashSystemSetPlayFrameLabel(u32,const char*,const char*);u8 GSfloorIsFloorPushed();void GSfloorPop();void GSfsysFree(s32);void GSfsysReadWait(s32);void GSresFreeGroup(s32);void GSthreadSwitch();void fightFreeResourceID(u32,u32);u16 fightGetFightResultId();u8 fightReadResourceID(u32,u32);void menuCBBattleEndSetPokemonHP();void menuCBBattleStartInit(BattleControl*,s32);void menuCBBattleStartTrainerFaceFree();void menuCBBattleStartTrainerLoadTex();void menuCBBios_CurrentlyWorkingToolBattleSet(s32);void menuCBPokemonEntryLoadTex();void menuCBPokemonEntryPokemonFaceFree(s32);s32 menuCB_Battle(BattleControl*);u8 menuCB_BattleBA_PokemonEntryNum();s32 menuCB_BattleResult(BattleControl*);void menuCB_GBADisconnectedErrorJob();void menuCB_InitBattle(BattleControl*);void menuCB_MenuRollback(s32);s32 menuCB_PokemonEntry(BattleControl*);void menuCB_SE_Play(s32);void menuCBpokemonFaceReadWait();void menuCBtrainerFaceReadWait();void menuCloseCustom(s32,s32,s32);u8 menuIsCheck(s32);void menuOpen(s32,s32);u8 pauseIsPause();SaveStatus*savedataGetStatus(s32,s32);void toolentryCopyHero();u8 winSeqCheckMove(s32);u16*windowGetKeyInfo();}
static void _menuCB_FlashEnd_WINLOSE(void) {
    if (menuIsCheck(0x110) != 0) {
        menuCloseCustom(0x110, 0, 0);
    }
}

static void _menuCB_FlashStart_WINLOSE(void) {
    const char *temp_r3;
    u16 temp_r3_2;

    temp_r3 = "winlose_start";
    temp_r3_2 = fightGetFightResultId();
    switch(temp_r3_2){
    case 2:case 5:FlashSystemSetPlayFrameLabel(0x21543000,"winlose_start","winlose_stop");FlashSystemSetNowFrameLabel(0x21543000,"winlose_start");goto labelReady;
    case 3:case 4:FlashSystemSetPlayFrameLabel(0x21543000,"losewin_start","losewin_stop");FlashSystemSetNowFrameLabel(0x21543000,"losewin_start");goto labelReady;
    case 8:default:break;
    }
    FlashSystemSetPlayFrameLabel(0x21543000,"draw_start","draw_stop");FlashSystemSetNowFrameLabel(0x21543000,"draw_start");
labelReady:
    FlashSystemSetLoopFlag(0x21543000, 0);
    _CB.unkB178 = 1;
    menuOpen(0x110, 0);
    menuCB_SE_Play(0x5E0);
loop_10:
    GSthreadSwitch();
    if (FlashSystemIsLastFrame(0x21543000) == 0) {
        goto loop_10;
    }
    if (pauseIsPause() == 0) {
        _CB.unkB1E4 = (s16) (_CB.unkB1E4 - 1);
    }
    if (((s16) _CB.unkB1E4 != 0) && ((s32) (windowGetKeyInfo()[2] & 0x20) == 0)) {
        goto loop_10;
    }
}

static void _menuCB_FlashEnd_VS(bool arg0) {
    if (arg0 != 0) {
        menuOpen(0x113, 0);
        do {
            GSthreadSwitch();
        } while (winSeqCheckMove(0x113) != 0);
        return;
    }
    _CB.unkB174 = 1;
}

static void _menuCB_FlashStart_VS(bool arg0) {
    const char *temp_r3;

    if (arg0 != 0) {
        FlashSystemSetPlayFrameLabel(0x21533000, "start", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "start");
    } else {
        temp_r3 = "end_keep";
        FlashSystemSetPlayFrameLabel(0x21533000, "end_keep", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "end_keep");
    }
    _CB.unkB170 = 1;
    _CB.unkB174 = 0;
}

static void _menuCB_FlashEnd(void) {
    if (menuIsCheck(0x105) != 0) {
        menuCloseCustom(0x105, 0, 0);
    }
}

static void _menuCB_FlashStart(bool arg0) {
    if (arg0 != 0) {
        FlashSystemSetPlayFrameLabel(0x20093000, "start", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "start");
    } else {
        FlashSystemSetPlayFrameLabel(0x20093000, "end", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "end");
    }
    _CB.unkB140 = 1;
    menuOpen(0x105, 0);
    do {
        GSthreadSwitch();
    } while (FlashSystemIsLastFrame(0x20093000) == 0);
}

extern "C" void menuToolBattleExit(void) {
    if ((s32) _CB.unk4 == 1) {
        if (fightReadResourceID(0x842, 0x184F3400) == 0) {
            fightFreeResourceID(0x842, 0x184F3400);
        }
    } else if (fightReadResourceID(0x842, 0x195F3400) == 0) {
        fightFreeResourceID(0x842, 0x195F3400);
    }
    GSfsysFree(0x14);
    GSresFreeGroup(0x14);
}

extern "C" void menuToolBattleMain(void) {
    s32 var_r25;
    s32 var_r3;
    u8 temp_r26;
    u8 var_r27;
    SaveStatus *temp_r3;

    var_r27 = 1;
    _menuCB_FlashStart(1U);
    temp_r3 = savedataGetStatus(0, 2);
    temp_r26 = temp_r3->unk959;
    temp_r3->unk959 = 0U;
loop_46:
    if (var_r27 != 0) {
        menuCBBios_CurrentlyWorkingToolBattleSet(1);
        menuCBBattleStartInit(&_CB, 0);
        _CB.unkB19C = 0;
        _CB.unkB1E4 = 0xF;
        menuCBPokemonEntryPokemonFaceFree(0);
        menuCBPokemonEntryLoadTex();
        menuCBpokemonFaceReadWait();
        menuCBBattleStartTrainerFaceFree();
        menuCBBattleStartTrainerLoadTex();
        menuCBtrainerFaceReadWait();
        if ((s32) _CB.unk8 == 2) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(1U);
            menuOpen(0x103, 0);
            menuOpen(0xB2, 1);
            _menuCB_FlashEnd_VS(0U);
            menuCloseCustom(0xB2, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else if (menuCB_BattleBA_PokemonEntryNum() != 0) {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(1U);
            menuOpen(0x103, 0);
            menuOpen(0xB3, 1);
            _menuCB_FlashEnd_VS(0U);
            menuCloseCustom(0xB3, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else {
            menuOpen(0xB1, 0);
            _menuCB_FlashStart_VS(1U);
            menuOpen(0x103, 0);
            menuOpen(0xB4, 1);
            if ((s32) _CB.unk4 != 1) {
                _menuCB_FlashEnd_VS(0U);
                menuCloseCustom(0xB4, 0, 0);
                menuCloseCustom(0x103, 0, 0);
                menuCloseCustom(0xB1, 0, 1);
            }
        }
        if ((s32) _CB.unkB19C != 0) {
            menuCB_GBADisconnectedErrorJob();
            menuCB_MenuRollback(0xA9);
        } else {
            if ((s32) _CB.unk4 == 1) {
                var_r3 = 0;
            } else {
                var_r3 = menuCB_PokemonEntry(&_CB);
            }
            switch (var_r3) {                       /* switch 1; irregular */
            case 0xA9:                              /* switch 1 */
                menuCB_MenuRollback(0xA9);
                break;
            default:                                /* switch 1 */
            case 0xB1:                              /* switch 1 */
                GSfsysFree(0x14);
                GSresFreeGroup(0x14);
                _CB.unkB184 = 1;
                _CB.unk0 = menuCB_Battle(&_CB);
                _CB.unkB184 = 0;
                _menuCB_FlashStart(0U);
                menuCBBattleEndSetPokemonHP();
                menuCBBattleStartInit(&_CB, 1);
                _CB.unkB19C = 0;
                _CB.unkB1E4 = 0xB4;
                menuCBPokemonEntryPokemonFaceFree(0);
                menuCBPokemonEntryLoadTex();
                menuCBpokemonFaceReadWait();
                menuCBBattleStartTrainerFaceFree();
                menuCBBattleStartTrainerLoadTex();
                menuCBtrainerFaceReadWait();
                menuCB_SE_Play(0x14);
                if ((s32) _CB.unk8 == 2) {
                    menuOpen(0xB1, 0);
                    _menuCB_FlashStart_VS(0U);
                    menuOpen(0x103, 0);
                    menuOpen(0xB2, 1);
                    _menuCB_FlashStart_WINLOSE();
                    var_r25 = menuCB_BattleResult(&_CB);
                    _menuCB_FlashEnd_VS(1U);
                    _menuCB_FlashEnd_WINLOSE();
                    if (var_r25 != 0xB1) {
                        _menuCB_FlashEnd();
                    }
                    menuCloseCustom(0xB2, 0, 0);
                    menuCloseCustom(0x103, 0, 0);
                    menuCloseCustom(0xB1, 0, 1);
                } else if (menuCB_BattleBA_PokemonEntryNum() != 0) {
                    menuOpen(0xB1, 0);
                    _menuCB_FlashStart_VS(0U);
                    menuOpen(0x103, 0);
                    menuOpen(0xB3, 1);
                    _menuCB_FlashStart_WINLOSE();
                    var_r25 = menuCB_BattleResult(&_CB);
                    _menuCB_FlashEnd_VS(1U);
                    _menuCB_FlashEnd_WINLOSE();
                    if (var_r25 != 0xB1) {
                        _menuCB_FlashEnd();
                    }
                    menuCloseCustom(0xB3, 0, 0);
                    menuCloseCustom(0x103, 0, 0);
                    menuCloseCustom(0xB1, 0, 1);
                } else {
                    menuOpen(0xB1, 0);
                    _menuCB_FlashStart_VS(0U);
                    menuOpen(0x103, 0);
                    menuOpen(0xB4, 1);
                    _menuCB_FlashStart_WINLOSE();
                    var_r25 = menuCB_BattleResult(&_CB);
                    _menuCB_FlashEnd_VS(1U);
                    _menuCB_FlashEnd_WINLOSE();
                    if (var_r25 != 0xB1) {
                        _menuCB_FlashEnd();
                    }
                    menuCloseCustom(0xB4, 0, 0);
                    menuCloseCustom(0x103, 0, 0);
                    menuCloseCustom(0xB1, 0, 1);
                }
                if ((var_r25 == 0xB1) || (var_r25 == 0xAC)) {
                    if ((s32) _CB.unk4 != 1) {
                        if ((s32) _CB.unkAFFC == 6) {
                            menuCB_InitBattle(&_CB);
                        }
                    } else {
                        menuCB_InitBattle(&_CB);
                    }
                    if ((s32) _CB.unkB19C != 0) {
                        menuCB_GBADisconnectedErrorJob();
                        menuCB_MenuRollback(0xA9);
                    } else {
                        goto block_36;
                    }
                } else {
block_36:
                    switch (var_r25) {              /* switch 2; irregular */
                    case 177:                       /* switch 2 */
                        toolentryCopyHero();
                        break;
                    default:                        /* switch 2 */
                    case 172:                       /* switch 2 */
                    case 169:                       /* switch 2 */
                    case -1:                        /* switch 2 */
                        menuCB_MenuRollback(var_r25);
                        var_r27 = 0;
                        break;
                    }
                    goto loop_46;
                }
                break;
            }
        }
    }
    _menuCB_FlashEnd();
    menuCBBattleStartTrainerFaceFree();
    savedataGetStatus(0, 2)->unk959 = temp_r26;
    if (GSfloorIsFloorPushed() != 0) {
        GSfloorPop();
        return;
    }
    GSfloorPop();
}

extern "C" void menuToolBattleInit(void) {
    if ((s32) _CB.unk4 == 1) {
        fightReadResourceID(0x842, 0x184F3400);
    } else {
        fightReadResourceID(0x842, 0x195F3400);
    }
    GSfsysReadWait(0x14);
}
