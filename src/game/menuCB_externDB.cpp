#include <game/menuCB_externDB.hpp>
#pragma auto_inline off

// Field views describe only offsets accessed by this module.
// Callback symbols retain the original C linkage.

#ifdef __cplusplus
extern "C" {
#endif
MenuDBCursor _ruleCursol;
static MenuDBFieldAnime field_anime;
// The 0x7c named buffer and its following 0x14-byte padding form the 0x90-byte rule copy.
static MenuDBRule _ruleTempBuff_DB;
static const s32 Port_Icon_Char[2] = {0x3C8, 0x3C9};
static s16 tool_gba_x_anime[4] = { -1, 0, 1, 0 };

static const s32 PlayerNumber[5] = { 0x20F, 0x20E, 0x20D, 0x20C, 0x20B }; /* const */
static const s32 Small_Face_Char[7] = { 0x208, 0x209, 0x20A, 0x210, 0x211, 0x212, 0x213 }; /* const */
static const s32 Big_Face_Char[7] = { 0x201, 0x202, 0x203, 0x204, 0x205, 0x206, 0x207 }; /* const */
static const s32 PCBOXBG_Char[8] = { 0x325, 0x326, 0x327, 0x328, 0x329, 0x32A, 0x32B, 0x32C }; /* const */
static const s32 BATTLE_FIELD_Char[7] = { 0x2A7, 0x2A9, 0x2A8, 0x2A6, 0x2A5, 0x2A4, 0x2D7 }; /* const */
static const u32 MENU_ITEM_TOOL_IMASUGU00_SETUMEI_Tbl[3] = { 0x43B8, 0x43B9, 0x4364 }; /* const */
static const u32 MENU_ITEM_TOOL_IMASUGU01_SETUMEI_Tbl[5] = { 0x443E, 0x443F, 0x4440, 0x4441, 0x4442 }; /* const */
static const u32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_Tbl[6] = {0x00004360, 0x00004361, 0x00004362, 0x00004363, 0x00004364, 0x00004418};
static const u32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_1_Tbl[4] = {0x0000436A, 0x0000436B, 0x0000436C, 0x0000436D};
static const u32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_3_Tbl[7] = {0x0000437D, 0x0000437E, 0x00004380, 0x00004382, 0x00004383, 0x00004384, 0x00004385};
static const u32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_4_Tbl[6] = {0x0000438D, 0x0000438F, 0x0000438E, 0x00004390, 0x00004390, 0x00004390};
static const u32 lbl_802EB774[4] = {0x00004366, 0x00004367, 0x00004368, 0x00004369};
static const u32 MENU_ITEM_TOOL_TUNAIDE01_FIELD_A_Tbl[7] = {0x00004374, 0x00004375, 0x00004377, 0x00004379, 0x0000437A, 0x0000437B, 0x0000437C};
static const u32 MENU_ITEM_TOOL_TUNAIDE01_RULE_A_Tbl[3] = {0x00004387, 0x00004389, 0x00004388};
static const s32 MENU_ITEM_TOOL_SANKA00_RELIVE_TITLE_Tbl[9] = { 0x43EC, 0x43ED, 0x43EE, 0x43EF, 0x43F0, 0x43F1, 0x43F2, 0x43F3, 0x43F4 }; /* const */
static const s32 _error01_cursol_item_tbl[0xE] = {
    0x4DD,
    0x4DE,
    0x4DF,
    0x4E0,
    0x4E1,
    0x4E2,
    0x4E3,
    0x4E4,
    0x4E5,
    0x4E6,
    0x4E7,
    0x4E8,
    0x4E9,
    0x4EA,
}; /* const */
static const u32 GCEntryStatusDispPosition[0x26] = {
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    0U,
    2U,
    2U,
}; /* const */
static const u32 MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_2_Tbl[2] = { 0x4371, 0x4372 }; /* const */
static const u32 MENU_ITEM_TOOL_TUNAIDE01_BATTLE_A_Tbl[2] = { 0x436F, 0x4370 }; /* const */

s32 _ruleCursol2;
s32 tunaide02_last_kakunin_flag;

void menuTool_tunaideGCEntry03_1_Ctrl(MenuDBWindow *arg0) {
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB150 != 0);
    arg0->unk8C = 0x180;
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 0)) {
        arg0->unk8C = (s16) _CB.unkB154;
    }
}

void menuTool_tunaideGCEntry04_1_Ctrl(MenuDBWindow *arg0) {
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB150 != 0);
    arg0->unk8C = 0x180;
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 2)) {
        arg0->unk8C = (s16) _CB.unkB154;
    }
}

void menuTool_tunaideGCEntry02_1_Ctrl(MenuDBWindow *arg0) {
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB150 != 0);
    arg0->unk8C = 0x180;
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 1)) {
        arg0->unk8C = (s16) _CB.unkB154;
    }
}

void menuCB_tunaideGCEntry04_Disp_1(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r4;
    s32 temp_r29;
    s32 temp_r3;

    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetEnv(arg0->unk1C);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 2)) {
        temp_r29 = _CB.unkB164;
        temp_r3 = getDancerQuantity__12CReliveStageFv(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r29));
        temp_r4 = arg1->unk6;
        switch (temp_r4) {
        case 0x5E2:
            menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 4);
            return;
        case 0x5E3:
            if (temp_r3 == 1) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, (temp_r29 * 0x10000) & 0xFFFF0000);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E4:
            if (temp_r3 == 2) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, (temp_r29 * 0x10000) & 0xFFFF0000);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E5:
            if (temp_r3 == 2) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 1);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E6:
            if (temp_r3 == 3) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, (temp_r29 * 0x10000) & 0xFFFF0000);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E8:
            if (temp_r3 == 3) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 1);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E7:
            if (temp_r3 == 3) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 2);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5EB:
            if (temp_r3 == 4) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, (temp_r29 * 0x10000) & 0xFFFF0000);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5EC:
            if (temp_r3 == 4) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 1);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5E9:
            if (temp_r3 == 4) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 2);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            return;
        case 0x5EA:
            if (temp_r3 == 4) {
                menuCB2DPokemonDisp2(arg0, arg1, 6, ((temp_r29 * 0x10000) & 0xFFFF0000) | 3);
                return;
            }
            winSpriteSetDisp(arg1, 0);
            break;
        }
    }
}

void menuCB_tunaideGCEntry03_Disp_1(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;

    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetEnv(arg0->unk1C);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 0)) {
        temp_r0 = arg1->unk6;
        switch (temp_r0) {                          /* irregular */
        case 0x59D:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 0);
            return;
        case 0x59E:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 1);
            return;
        case 0x59F:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 2);
            return;
        case 0x5A0:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 3);
            return;
        case 0x5A1:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 4);
            return;
        case 0x5A2:
            menuCB2DPokemonDisp2(arg0, arg1, 4, 5);
            break;
        }
    }
}

void menuCB_tunaideGCEntry02_Disp_1(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r3;
    s32 var_r4;

    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetEnv(arg0->unk1C);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB15C == 1)) {
        temp_r3 = arg1->unk6;
        var_r4 = _CB.unkB160;
        switch (temp_r3) {
        case 0x5A3:
        case 0x5A4:
        case 0x5A5:
        case 0x5A6:
        case 0x5A7:
        case 0x5A8:
        case 0x5A9:
        case 0x5AA:
        case 0x5AB:
        case 0x5AC:
        case 0x5AD:
        case 0x5AE:
        case 0x5AF:
        case 0x5B0:
        case 0x5B1:
        case 0x5B2:
        case 0x5B3:
        case 0x5B4:
        case 0x5B5:
        case 0x5B6:
        case 0x5B7:
        case 0x5B8:
        case 0x5B9:
        case 0x5BA:
        case 0x5BB:
        case 0x5BC:
        case 0x5BD:
        case 0x5BE:
        case 0x5BF:
        case 0x5C0:
            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PCBOXBG_Char[var_r4]));
            return;
        case 0x5C1:
            menuCB2DPokemonDisp2(arg0, arg1, 5, (var_r4 * 0x10000) & 0xFFFF0000);
            return;
        case 0x5C2:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 1);
            return;
        case 0x5C3:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 2);
            return;
        case 0x5C4:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 3);
            return;
        case 0x5C5:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 4);
            return;
        case 0x5C6:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 5);
            return;
        case 0x5C7:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 6);
            return;
        case 0x5C8:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 7);
            return;
        case 0x5C9:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 8);
            return;
        case 0x5CA:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 9);
            return;
        case 0x5CB:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xA);
            return;
        case 0x5CC:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xB);
            return;
        case 0x5CD:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xC);
            return;
        case 0x5CE:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xD);
            return;
        case 0x5CF:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xE);
            return;
        case 0x5D0:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0xF);
            return;
        case 0x5D1:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x10);
            return;
        case 0x5D2:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x11);
            return;
        case 0x5D3:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x12);
            return;
        case 0x5D4:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x13);
            return;
        case 0x5D5:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x14);
            return;
        case 0x5D6:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x15);
            return;
        case 0x5D7:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x16);
            return;
        case 0x5D8:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x17);
            return;
        case 0x5D9:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x18);
            return;
        case 0x5DA:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x19);
            return;
        case 0x5DB:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x1A);
            return;
        case 0x5DC:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x1B);
            return;
        case 0x5DD:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x1C);
            return;
        case 0x5DE:
            menuCB2DPokemonDisp2(arg0, arg1, 5, ((var_r4 * 0x10000) & 0xFFFF0000) | 0x1D);
            break;
        }
    }
}

void menuCB_Flash_WINLOSE_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    switch ((s16) arg1->unk6) {
    case 0x5EE:
    menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB178 == 0);
    if ((s32) _CB.unkB178 != 0) {
        _CB.unkB178 -= 1;
    }
        break;
    }
}


#pragma pool_strings off
void menuCB_Flash_VS_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    if ((s32) _CB.unkB174 != 0) {
        FlashSystemSetPlayFrameLabel(0x21533000U, "end_keep", "end");
        FlashSystemSetNowFrameLabel(0x21533000U, "end_keep");
        _CB.unkB174 = 0;
    }
    switch (arg1->unk6) {
    case 0x5F2:
    case 0x5F3:
    case 0x5F4:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB170 == 0);
        if ((s32) _CB.unkB170 != 0) {
            _CB.unkB170 -= 1;
        }
        break;
    }
}

void menuCB_Flash_gba_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 temp_r0;

    if ((s32) _CB.unkB168 == 2) {
        switch ((s32) _CB.unkB16C) {                /* irregular */
        case 0:
            FlashSystemSetPlayFrameLabel(0x214D3000U, "01", "01");
            FlashSystemSetNowFrameLabel(0x214D3000U, "01");
            _CB.unkB168 -= 1;
            break;
        case 1:
            FlashSystemSetPlayFrameLabel(0x214D3000U, "02", "02");
            FlashSystemSetNowFrameLabel(0x214D3000U, "02");
            _CB.unkB168 -= 1;
            break;
        case 2:
            FlashSystemSetPlayFrameLabel(0x214D3000U, "03", "03");
            FlashSystemSetNowFrameLabel(0x214D3000U, "03");
            _CB.unkB168 -= 1;
            break;
        case 3:
            FlashSystemSetPlayFrameLabel(0x214D3000U, "04", "04");
            FlashSystemSetNowFrameLabel(0x214D3000U, "04");
            _CB.unkB168 -= 1;
            break;
        default:
            winSpriteSetDisp(arg1, 0);
            return;
        }
        FlashSystemSetLoopFlag(0x214D3000U, 1);
    }
    {
        temp_r0 = ((s32 *)&gbaConectGBA_Connect_WORK)[_CB.unkB16C];
        if ((temp_r0 != 3) && (temp_r0 != 4)) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        switch ((s16) arg1->unk6) {
        case 0x5ED:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB168 == 0);
        if ((s32) _CB.unkB168 != 0) {
            _CB.unkB168 -= 1;
        }
        break;
        }
    }
}

void menuCB_Flash02_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    switch ((s16) arg1->unk6) {
    case 0x4C5:
    menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB140 == 0);
    if ((s32) _CB.unkB140 != 0) {
        _CB.unkB140 -= 1;
    }
        break;
    }
}

void menuCB_Flash01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    switch ((s16) arg1->unk6) {
    case 0x4C4:
    menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB13C == 0);
    if ((s32) _CB.unkB13C != 0) {
        _CB.unkB13C -= 1;
    }
        break;
    }
}


#pragma pool_strings on
void menuTool_FlashCtrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
}

void menuTool_MASK_Ctrl(MenuDBWindow *arg0) {
    u8 temp_r0;

    temp_r0 = (u8) arg0->unk1;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) (u8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x189);
            arg0->unk2 = 1;
        }
        break;
    case 3:
        if ((s8) (u8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x191);
            arg0->unk2 = 1;
            spriteClearScissor(arg0->unk1C);
        }
        break;
    }
}

void menuCB_Rule06_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x39A:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB028 != 0);
        return;
    case 0x39B:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((0x34 - _CB.unkB028) | (_CB.unkB028 - 0x34)) >> 0x1FU));
        return;
    case 0x39C:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 0);
        return;
    case 0x39D:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 1);
        return;
    case 0x39E:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 2);
        return;
    case 0x39F:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 3);
        return;
    case 0x3A0:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 4);
        return;
    case 0x3A1:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 5);
        return;
    case 0x3A2:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 6);
        return;
    case 0x3A3:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 7);
        return;
    case 0x3A4:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 8);
        return;
    case 0x3A5:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 9);
        return;
    case 0x3A6:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB02C == 0xA);
        return;
    case 0x3AD:
        menuCB_RuleItemFlagDisp(arg0, arg1);
        return;
    case 0x3AF:
        menuCB_RuleItemNameEntry(arg0, arg1);
        return;
    case 0x3AE:
        menuCBMessageCenterDisp(arg0, arg1, 0x4415U);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_Rule06_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule06_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if ((s32) _CB.unkB130 != 0) {
        _CB.unkB134 += _CB.unkB130;
        // This control path reloads the animated position after storing it.
        if (*(volatile s32 *)&_CB.unkB134 <= 0) {
            _CB.unkB134 = 0;
            _CB.unkB130 = 0;
        }
        if ((s32) _CB.unkB134 >= 0x1F4) {
            _CB.unkB134 = 0x1F4;
            _CB.unkB130 = 0;
        }
    }
    arg0->unk8C = (s16) _CB.unkB134;
}

void menuCB_Rule05_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x387:
        menuCBMessageCenterDisp(arg0, arg1, 0x4414U);
        return;
    case 0x388:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43DBU);
        return;
    case 0x389:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43DCU);
        return;
    case 0x38A:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x38B:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x38C:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x38D:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x37C:
    case 0x37D:
    case 0x37E:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB024 == 0);
        return;
    case 0x37F:
    case 0x380:
    case 0x381:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB024 == 1);
        return;
    case 0x386:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB024 == 2);
        menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
        return;
    case 0x382:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x50);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB030 == 0);
        return;
    case 0x383:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x50);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB030 == 1);
        return;
    case 0x384:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x51);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB034 == 0);
        return;
    case 0x385:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x51);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB034 == 1);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_Rule05_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule05_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(arg0, 4);
}

void menuCB_Rule04_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;
    u8 temp_r5_5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x36D:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D8U);
        return;
    case 0x36E:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D9U);
        return;
    case 0x36F:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D6U);
        return;
    case 0x370:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43DAU);
        return;
    case 0x371:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x372:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x373:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x374:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x375:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E1U);
        return;
    case 0x376:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E2U);
        return;
    case 0x377:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x378:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x359:
    case 0x35A:
    case 0x35B:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB020 == 0);
        return;
    case 0x35C:
    case 0x35D:
    case 0x35E:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB020 == 1);
        return;
    case 0x35F:
    case 0x360:
    case 0x361:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB020 == 2);
        return;
    case 0x362:
    case 0x363:
    case 0x364:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB020 == 3);
        return;
    case 0x365:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x40);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk11 == 1);
        return;
    case 0x366:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x40);
        temp_r5_2 = _CB.unk9C78->unk11;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1)) >> 0x1FU));
        return;
    case 0x367:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x41);
        temp_r5_3 = _CB.unk9C78->unk12;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_3) | (temp_r5_3 - 1)) >> 0x1FU));
        return;
    case 0x368:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x41);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk12 == 1);
        return;
    case 0x369:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x42);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkF == 1);
        return;
    case 0x36A:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x42);
        temp_r5_4 = _CB.unk9C78->unkF;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_4) | (temp_r5_4 - 1)) >> 0x1FU));
        return;
    case 0x36B:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x43);
        temp_r5_5 = _CB.unk9C78->unk13;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_5) | (temp_r5_5 - 1)) >> 0x1FU));
        return;
    case 0x36C:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x43);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk13 == 1);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_Rule04_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule04_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(arg0, 3);
}

void menuCB_Rule03_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;
    u8 temp_r5_2;
    u8 temp_r5_3;
    u8 temp_r5_4;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x34C:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D4U);
        return;
    case 0x34D:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D5U);
        return;
    case 0x34E:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D7U);
        return;
    case 0x34F:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E5U);
        return;
    case 0x350:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E6U);
        return;
    case 0x351:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E1U);
        return;
    case 0x352:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E2U);
        return;
    case 0x353:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E7U);
        return;
    case 0x354:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E8U);
        return;
    case 0x33D:
    case 0x33E:
    case 0x33F:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB01C == 0);
        return;
    case 0x340:
    case 0x341:
    case 0x342:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB01C == 1);
        return;
    case 0x343:
    case 0x344:
    case 0x345:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB01C == 2);
        return;
    case 0x346:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x30);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk19 == 1);
        return;
    case 0x347:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x30);
        temp_r5_2 = _CB.unk9C78->unk19;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1)) >> 0x1FU));
        return;
    case 0x348:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x31);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkE == 1);
        return;
    case 0x349:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x31);
        temp_r5_3 = _CB.unk9C78->unkE;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_3) | (temp_r5_3 - 1)) >> 0x1FU));
        return;
    case 0x34A:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x32);
        temp_r5_4 = _CB.unk9C78->unk10;
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - temp_r5_4) | (temp_r5_4 - 1)) >> 0x1FU));
        return;
    case 0x34B:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x32);
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk10 == 1);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_Rule03_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule03_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(arg0, 2);
}

void menuCB_Rule02_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    u8 temp_r5;
    u8 temp_r5_2;
    switch (arg1->unk6) {
    case 0x330:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D0U);
        break;
    case 0x331:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D1U);
        break;
    case 0x332:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43D2U);
          return;
        break;
    case 0x333:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E1U);
          return;
        break;
    case 0x334:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E2U);
          return;
        break;
    case 0x335:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          winSpriteSetDisp(arg1, 1);
          menuCBMessageCenterDisp(arg0, arg1, 0x43E3U);
          return;
        break;
    case 0x336:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          winSpriteSetDisp(arg1, 1);
          menuCBMessageCenterDisp(arg0, arg1, 0x43E4U);
          return;
        break;
    case 0x337:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          winSpriteSetDisp(arg1, 1);
          menuCBMessageCenterDisp(arg0, arg1, 0x43DEU);
          return;
        break;
    case 0x689:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 1);
            menuCBMessageCenterDisp(arg0, arg1, 0x43DEU);
            return;
          }
          winSpriteSetDisp(arg1, 0);
          return;
        break;
    case 0x68A:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 1);
            menuCBMessageCenterDisp(arg0, arg1, 0x4458U);
            return;
          }
          winSpriteSetDisp(arg1, 0);
          return;
        break;
    case 0x338:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E3U);
          return;
        break;
    case 0x339:
        menuCBMessageCenterDisp(arg0, arg1, 0x43E4U);
          return;
        break;
    case 0x320:
    case 0x321:
    case 0x322:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 0);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 1);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          temp_r5 = _CB.unk9C78->unkC;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5) | (temp_r5 - 1))) >> 0x1FU));
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkC == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x323:
    case 0x324:
    case 0x325:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 1);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          temp_r5 = _CB.unk9C78->unkC;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5) | (temp_r5 - 1))) >> 0x1FU));
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkC == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x326:
    case 0x327:
    case 0x328:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB018 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          temp_r5 = _CB.unk9C78->unkC;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5) | (temp_r5 - 1))) >> 0x1FU));
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkC == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x329:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkC == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x32A:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          temp_r5 = _CB.unk9C78->unkC;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5) | (temp_r5 - 1))) >> 0x1FU));
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x20);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkC == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x32B:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 0);
        break;
    case 0x32C:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 1);
          return;
          if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x32D:
        if ((((s32) _CB.unk9C78->unk8) == 2) && (((s32) _CB.unkB014) == (-1)))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge(arg0, arg1, 0x21);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unk8 == 2);
          return;
          menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    case 0x32E:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk9C78->unkD == 1);
        break;
    case 0x32F:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x22);
          temp_r5_2 = _CB.unk9C78->unkD;
          menuCB_SpriteDispCheckONorOFF(arg1, (s32) (((u32) ((1 - temp_r5_2) | (temp_r5_2 - 1))) >> 0x1FU));
        break;
    default:
        return;
    }
}

void menuTool_Rule02_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule02_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(arg0, 1);
}

void menuCB_Rule01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 var_r4;
    s32 var_r4_10;
    s32 var_r4_11;
    s32 var_r4_12;
    s32 var_r4_13;
    s32 var_r4_14;
    s32 var_r4_15;
    s32 var_r4_16;
    s32 var_r4_17;
    s32 var_r4_18;
    s32 var_r4_19;
    s32 var_r4_20;
    s32 var_r4_21;
    s32 var_r4_22;
    s32 var_r4_23;
    s32 var_r4_24;
    s32 var_r4_25;
    s32 var_r4_26;
    s32 var_r4_27;
    s32 var_r4_28;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r4_6;
    s32 var_r4_7;
    s32 var_r4_8;
    s32 var_r4_9;
    switch (arg1->unk6) {
    case 0x690:
    case 0x691:
        arg1->unk4C = 0x4396;
        break;
    case 0x310:
        arg1->unk4C = 0x4413;
          return;
        break;
    case 0x313:
        arg1->unk4C = 0x43DF;
          return;
        break;
    case 0x314:
        menuCBMessageCenterDisp(arg0, arg1, 0x43DDU);
          return;
        break;
    case 0x317:
        arg1->unk4C = 0x43E0;
          return;
        break;
    case 0x3B7:
        menuCBMessageCenterDisp(arg0, arg1, 0x43DDU);
        break;
    case 0x318:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43CBU);
          return;
        break;
    case 0x319:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43CCU);
          return;
        break;
    case 0x31A:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43CDU);
          return;
        break;
    case 0x31C:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43CEU);
          return;
        break;
    case 0x31B:
        menuCBMessageYCenterDisp(arg0, arg1, 0x43CFU);
          return;
        break;
    case 0x3BC:
        menuCBMessageCenterDisp(arg0, arg1, 0x441BU);
          return;
        break;
    case 0x3BE:
        arg1->unk4C = 0x441A;
          return;
        break;
    case 0x307:
        menuCBRuleNumberDisp(arg0, arg1, 0);
          return;
        break;
    case 0x308:
        menuCBRuleNumberDisp(arg0, arg1, 1);
          return;
        break;
    case 0x309:
        menuCBRuleNumberDisp(arg0, arg1, 2);
          return;
        break;
    case 0x30A:
        menuCBRuleNumberDisp(arg0, arg1, 3);
          return;
        break;
    case 0x30B:
        menuCBRuleNumberDisp(arg0, arg1, 4);
          return;
        break;
    case 0x30C:
        menuCBRuleNumberDisp(arg0, arg1, 5);
        break;
    case 0x30D:
        menuCBRuleNumberDisp(arg0, arg1, 6);
          return;
        break;
    case 0x30E:
        menuCBRuleNumberDisp(arg0, arg1, 7);
          return;
        break;
    case 0x30F:
        menuCBRuleNumberDisp(arg0, arg1, 8);
          return;
        break;
    case 0x311:
        menuCBRuleNumberDisp(arg0, arg1, 9);
          return;
        break;
    case 0x312:
        menuCBRuleNumberDisp(arg0, arg1, 0xA);
          return;
        break;
    case 0x315:
        menuCBRuleNumberDisp(arg0, arg1, 0xB);
          return;
        break;
    case 0x316:
        menuCBRuleNumberDisp(arg0, arg1, 0xC);
          return;
        break;
    case 0x3BD:
        menuCBRuleNumberDisp(arg0, arg1, 0xD);
          return;
        break;
    case 0x2ED:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 0)) && (((s16) _CB.unk9C78->unk0) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2EE:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 0)) && (((s16) _CB.unk9C78->unk0) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2EF:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 1)) && (((s16) _CB.unk9C78->unk0) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F0:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 1)) && (((s16) _CB.unk9C78->unk0) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F1:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 2)) && (((s16) _CB.unk9C78->unk0) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F2:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 2)) && (((s16) _CB.unk9C78->unk0) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F3:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 3)) && (((s16) _CB.unk9C78->unk2) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F4:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 3)) && (((s16) _CB.unk9C78->unk2) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F5:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 4)) && (((s16) _CB.unk9C78->unk2) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F6:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 4)) && (((s16) _CB.unk9C78->unk2) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F7:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 5)) && (((s16) _CB.unk9C78->unk2) != 0x64)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F8:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x10) && (((s32) _ruleCursol.unk0) == 5)) && (((s16) _CB.unk9C78->unk2) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2F9:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 0)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk2) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FA:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 0)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk0) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FB:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 1)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk2) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FC:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 1)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk0) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FD:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 2)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk2) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FE:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x11) && (((s32) _ruleCursol.unk4) == 2)) && (((s16) _CB.unk9C78->unk4) != ((s32) (((s16) _CB.unk9C78->unk0) * 6)))));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2FF:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x12) && (((s32) _ruleCursol.unk8) == 0)) && (((s16) _CB.unk9C78->unk14) != 0x63)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x300:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x12) && (((s32) _ruleCursol.unk8) == 0)) && (((s16) _CB.unk9C78->unk14) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x301:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x12) && (((s32) _ruleCursol.unk8) == 1)) && (((s16) _CB.unk9C78->unk14) != 0x63)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x302:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x12) && (((s32) _ruleCursol.unk8) == 1)) && (((s16) _CB.unk9C78->unk14) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2EB:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x12);
          menuCB_SpriteDispCheckONorOFF(arg1, (((s16) _CB.unk9C78->unk14) & 0x8000) != 0);
          return;
        break;
    case 0x303:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x13) && (((s32) _ruleCursol.unkC) == 0)) && (((s16) _CB.unk9C78->unk16) != 0x63)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x304:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x13) && (((s32) _ruleCursol.unkC) == 0)) && (((s16) _CB.unk9C78->unk16) != 0xA)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x305:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x13) && (((s32) _ruleCursol.unkC) == 1)) && (((s16) _CB.unk9C78->unk16) != 0x63)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x306:
          menuCB_SpriteDispCheckONorOFF(arg1, (((((s32) _CB.unkB11C) == 0x13) && (((s32) _ruleCursol.unkC) == 1)) && (((s16) _CB.unk9C78->unk16) != 0xA)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x2EC:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x13);
          menuCB_SpriteDispCheckONorOFF(arg1, (((s16) _CB.unk9C78->unk16) & 0x8000) != 0);
          return;
        break;
    case 0x3B9:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x14);
          menuCB_SpriteDispCheckONorOFF(arg1, ((s16) _CB.unk9C78->unk1C) == 1);
          return;
        break;
    case 0x3BA:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x14);
          menuCB_SpriteDispCheckONorOFF(arg1, ((((((s32) _CB.unkB11C) == 0x14) && (((s16) _CB.unk9C78->unk1C) != 1)) && (((s32) _ruleCursol.unk10) == 0)) && (((s16) _CB.unk9C78->unk1A) != 6)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x3BB:
        menuCB_RuleDispColorChenge(arg0, arg1, 0x14);
          menuCB_SpriteDispCheckONorOFF(arg1, ((((((s32) _CB.unkB11C) == 0x14) && (((s16) _CB.unk9C78->unk1C) != 1)) && (((s32) _ruleCursol.unk10) == 0)) && (((s16) _CB.unk9C78->unk1A) != 1)));
          menuCB_RuleDispColorChenge_flag(arg0, arg1, 1);
          return;
        break;
    case 0x67A:
    case 0x67B:
    case 0x67C:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 0);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 1);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 2);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 3);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 4);
        break;
    case 0x67D:
    case 0x67E:
    case 0x67F:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 1);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 2);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 3);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 4);
        break;
    case 0x680:
    case 0x681:
    case 0x682:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 2);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 3);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 4);
        break;
    case 0x683:
    case 0x684:
    case 0x685:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 3);
          return;
          menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 4);
        break;
    case 0x686:
    case 0x687:
    case 0x688:
        menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(arg1);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB014 == 4);
        break;
    default:
        return;
    }
}

void menuTool_Rule01_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_Rule01_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_RULE(arg0, 0);
}

void menuCB_RuleCustomMainCursolColorChenge__FP14tagSPRITE_WORK(MenuDBSprite *arg0) {
    if ((s32) _CB.unkB11C != 0) {
        arg0->unk66 = 0x7F;
        arg0->unk65 = 0x7F;
        arg0->unk64 = 0x7F;
        return;
    }
    arg0->unk66 = 0xFF;
    arg0->unk65 = 0xFF;
    arg0->unk64 = 0xFF;
}

void _menuCB_Rule_Page_Chenge_Init__Fv(void) {
    volatile MenuDBState *state = &_CB;
    state->unkB124 = state->unkB118;
    state->unkB128 = 0xFF;
    state->unkB12C = 0xF;
}

void menuCB_Rule00_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r5;
    switch (arg1->unk6) {
    case 0x3AA:
        arg1->unk4C = 0;
          menuCBRULE_EditNameDispLarge(arg0, _CB.unkB004);
          return;
        break;
    case 0x3B6:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, _CB.unkB11C == 0);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB118 == 0);
          return;
        break;
    case 0x3B0:
    case 0x3F0:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, (((s32) _CB.unkB118) == 1) && (((s32) _CB.unkB11C) == 0));
          menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB118) == 1) || (((s32) _CB.unkB118) == 5));
          return;
        break;
    case 0x3B2:
    case 0x3B3:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, _CB.unkB11C == 0);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB118 == 2);
          return;
        break;
    case 0x3B4:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, _CB.unkB11C == 0);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB118 == 3);
          return;
        break;
    case 0x3B1:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, _CB.unkB11C == 0);
          menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB118) == 3) && (((s32) _CB.unkB014) != (-1)));
          return;
        break;
    case 0x3B5:
        if (((s32) _CB.unkB124) != (-1))
          {
            winSpriteSetDisp(arg1, 0);
            return;
          }
          menuCB_RuleDispColorChenge_flag(arg0, arg1, _CB.unkB11C == 0);
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB118 == 4);
          return;
        break;
    default:
        return;
    }
}

void menuTool_Rule00_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuCB_Cursol_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s16 temp_r29;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 var_r29;
    s16 temp_r28;
    s32 temp_r3;

    temp_r3 = pokecoloGetCountryCode();
    if ((temp_r3 != 0) && (temp_r3 >= 0) && (temp_r3 < 3)) {
        var_r29 = (s16) (GSmsgGetRect(0x42FBU) >> 0x10U);
        temp_r28 = (s16) (GSmsgGetRect(0x426AU) >> 0x10U);
        temp_r3_2 = (s16) (GSmsgGetRect(0x3B2AU) >> 0x10U);
        if (var_r29 < temp_r28) {
            var_r29 = temp_r28;
        }
        if (var_r29 < temp_r3_2) {
            var_r29 = temp_r3_2;
        }
        temp_r3_3 = arg1->unk6;
        switch (temp_r3_3) {                        /* switch 1 */
        case 0x4C7:                                 /* switch 1 */
        case 0x4CA:                                 /* switch 1 */
        case 0x4CD:                                 /* switch 1 */
            arg1->unk54 = var_r29 + 0x14;
            break;
        case 0x4C8:                                 /* switch 1 */
        case 0x4CB:                                 /* switch 1 */
        case 0x4CE:                                 /* switch 1 */
            arg1->unk50 = var_r29 + 0x5E;
            break;
        }
    }
    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* switch 2; irregular */
    case 0x4CF:                                     /* switch 2 */
        winSpriteSetDisp(arg1, 0);
        temp_r29 = arg0->unk9E;
        if (temp_r29 >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(arg0, winSpriteGetLayerID(arg0, arg1), 0, temp_r29 * 0x23, arg1->unk54, arg1->unk56, arg0->unk93, 1);
        }
        /* fallthrough */
    case 0x4D1:                                     /* switch 2 */
        arg1->unk4C = 0x426A;
        return;
    case 0x4D2:                                     /* switch 2 */
        arg1->unk4C = 0x3B2A;
        return;
    case 0x4D0:                                     /* switch 2 */
        arg1->unk4C = 0x42FB;
        return;
    }
}

void menuTool_Cursol_Button(MenuDBWindow *arg0) {
    if ((s32) _CB.unkB108 == 1) {
        if ((s32) _CB.unkB110 != 0) {
            _CB.unkB110 -= 1;
            return;
        }
        _CB.unkAFE0 = (s32) arg0->unk9E;
        if (pauseIsPause() == 0) {
            if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                _CB.unkB060 = 1;
                return;
            }
            if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                _CB.unkAFE0 = 1;
                _CB.unkB060 = 1;
            }
        }
    }
}

void menuTool_Cursol_Ctrl(MenuDBWindow *arg0) {
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB108 == 1);
}

void menuCB_tunaidePokemonSelect1_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(MenuDBWindow *arg0, MenuDBSprite *arg1, u32 arg2) {
    s16 temp_r4;

    temp_r4 = arg1->unk6;
    switch (temp_r4) {
    case 0x3FA:
    case 0x427:
    case 0x454:
    case 0x481:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 0);
        return;
    case 0x3FB:
    case 0x428:
    case 0x455:
    case 0x482:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 1);
        return;
    case 0x3FC:
    case 0x429:
    case 0x456:
    case 0x483:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 2);
        return;
    case 0x3FD:
    case 0x42A:
    case 0x457:
    case 0x484:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 3);
        return;
    case 0x3FE:
    case 0x42B:
    case 0x458:
    case 0x485:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 4);
        return;
    case 0x3FF:
    case 0x42C:
    case 0x459:
    case 0x486:
        menuCB_BattleEntryPokemonSelectDisp(arg1, (s32) arg2, 5);
        return;
    case 0x400:
    case 0x42D:
    case 0x45A:
    case 0x487:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 0);
        return;
    case 0x401:
    case 0x42E:
    case 0x45B:
    case 0x488:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 1);
        return;
    case 0x402:
    case 0x42F:
    case 0x45C:
    case 0x489:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 2);
        return;
    case 0x403:
    case 0x430:
    case 0x45D:
    case 0x48A:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 3);
        return;
    case 0x404:
    case 0x431:
    case 0x45E:
    case 0x48B:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 4);
        return;
    case 0x405:
    case 0x432:
    case 0x45F:
    case 0x48C:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, (s32) arg2, 5);
        return;
    case 0x407:
    case 0x434:
    case 0x461:
    case 0x48E:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 1);
        return;
    case 0x408:
    case 0x435:
    case 0x462:
    case 0x48F:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 2);
        return;
    case 0x409:
    case 0x436:
    case 0x463:
    case 0x490:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 3);
        return;
    case 0x40A:
    case 0x437:
    case 0x464:
    case 0x491:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 4);
        return;
    case 0x40B:
    case 0x438:
    case 0x465:
    case 0x492:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 5);
        return;
    case 0x40C:
    case 0x439:
    case 0x466:
    case 0x493:
        menuCBPokemonEntryBallAnaDisp(arg1, (s32) arg2, 6);
        return;
    case 0x40D:
    case 0x43A:
    case 0x467:
    case 0x494:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 1);
        return;
    case 0x40E:
    case 0x43B:
    case 0x468:
    case 0x495:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 2);
        return;
    case 0x40F:
    case 0x43C:
    case 0x469:
    case 0x496:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 3);
        return;
    case 0x410:
    case 0x43D:
    case 0x46A:
    case 0x497:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 4);
        return;
    case 0x411:
    case 0x43E:
    case 0x46B:
    case 0x498:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 5);
        return;
    case 0x412:
    case 0x43F:
    case 0x46C:
    case 0x499:
        menuCBPokemonEntryBallDisp(arg1, (s32) arg2, 6);
        return;
    case 0x413:
    case 0x440:
    case 0x46D:
    case 0x49A:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 5));
        return;
    case 0x414:
    case 0x441:
    case 0x46E:
    case 0x49B:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 4));
        return;
    case 0x415:
    case 0x442:
    case 0x46F:
    case 0x49C:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 3));
        return;
    case 0x416:
    case 0x443:
    case 0x470:
    case 0x49D:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 2));
        return;
    case 0x417:
    case 0x444:
    case 0x471:
    case 0x49E:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 1));
        return;
    case 0x418:
    case 0x445:
    case 0x472:
    case 0x49F:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId((s32) arg2, 0));
        return;
    case 0x419:
    case 0x446:
    case 0x473:
    case 0x4A0:
    {
        MenuDBPlayer *players = (MenuDBPlayer *)&_CB;
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PlayerNumber[players[arg2].control]));
    }
        return;
    case 0x41A:
    case 0x447:
    case 0x474:
    case 0x4A1:
        menuCBPokemonSexOnly(arg0, arg2, 5U, 1);
        return;
    case 0x41B:
    case 0x448:
    case 0x475:
    case 0x4A2:
        menuCBPokemonSexOnly(arg0, arg2, 4U, 1);
        return;
    case 0x41C:
    case 0x449:
    case 0x476:
    case 0x4A3:
        menuCBPokemonSexOnly(arg0, arg2, 3U, 1);
        return;
    case 0x41D:
    case 0x44A:
    case 0x477:
    case 0x4A4:
        menuCBPokemonSexOnly(arg0, arg2, 2U, 1);
        return;
    case 0x41E:
    case 0x44B:
    case 0x478:
    case 0x4A5:
        menuCBPokemonSexOnly(arg0, arg2, 1U, 1);
        return;
    case 0x41F:
    case 0x44C:
    case 0x479:
    case 0x4A6:
        menuCBPokemonSexOnly(arg0, arg2, 0U, 1);
        return;
    case 0x420:
    case 0x44D:
    case 0x47A:
    case 0x4A7:
        menuCBPokemonNameOnly(arg0, arg2, 5U, 0);
        return;
    case 0x421:
    case 0x44E:
    case 0x47B:
    case 0x4A8:
        menuCBPokemonNameOnly(arg0, arg2, 4U, 0);
        return;
    case 0x422:
    case 0x44F:
    case 0x47C:
    case 0x4A9:
        menuCBPokemonNameOnly(arg0, arg2, 3U, 0);
        return;
    case 0x423:
    case 0x450:
    case 0x47D:
    case 0x4AA:
        menuCBPokemonNameOnly(arg0, arg2, 2U, 0);
        return;
    case 0x424:
    case 0x451:
    case 0x47E:
    case 0x4AB:
        menuCBPokemonNameOnly(arg0, arg2, 1U, 0);
        return;
    case 0x425:
    case 0x452:
    case 0x47F:
    case 0x4AC:
        menuCBPokemonNameOnly(arg0, arg2, 0U, 0);
        return;
    case 0x426:
    case 0x453:
    case 0x480:
    case 0x4AD:
        toobattle_drawHeroNames(arg0, (s32) arg2);
        /* fallthrough */
    default:
        return;
    }
}

void menuCB_tunaidePokemonSelect1_Disp_RD(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    if (menuCB_GCStatusDispMode(arg1, 0) != 0) {
        menuCB_tunaidePokemonSelect1_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(arg0, arg1, 3U);
    }
}

void menuCB_tunaidePokemonSelect1_Disp_RU(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    if (menuCB_GCStatusDispMode(arg1, 0) != 0) {
        menuCB_tunaidePokemonSelect1_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(arg0, arg1, 2U);
    }
}

void menuCB_tunaidePokemonSelect1_Disp_LD(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    menuCB_tunaidePokemonSelect1_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(arg0, arg1, 1U);
}

void menuCB_tunaidePokemonSelect1_Disp_LU(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    menuCB_tunaidePokemonSelect1_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(arg0, arg1, 0U);
}

void menuTool_tunaidePokemonSelect1_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaidePokemonSelect1_Ctrl(MenuDBWindow *arg0) {
    s32 temp_r3_2;
    u16 temp_r3;
    u16 var_r30;

    menuCB_DispEffect(arg0);
    _CB.unkB104 = -1;
    menuSetStatus(arg0->unk4, 0x10);
    if (menuCB_GetDisconnectedGBA() != 0) {
        _CB.unkB1A0 = 1;
        return;
    }
    menuCBPokemonEntryButtonTask_20041006();
    if (((s32) _CB.unkB108 < 1) && (pauseIsPause() == 0)) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            var_r30 = menuCBPokemonEntryPokemonNumMin(0);
            if ((toolentryTaisengetEtnryPokemonOrderNum(0) >= (s32) var_r30) && (toolentryTaisenGetHomePlace(0) == 0)) {
                _CB.unkB108 = 1;
                return;
            }
        }
        if (toolentryTaisenGetHomePlace(0) == 0) {
            var_r30 = menuCBBios_ParticipationPokemonMax();
            temp_r3 = toolentryTaisenGetPokemonNum(0);
            if (temp_r3 < var_r30) {
                var_r30 = temp_r3;
            }
            if ((s32) var_r30 == toolentryTaisengetEtnryPokemonOrderNum(0)) {
                _CB.unkB108 = 1;
                return;
            }
            goto block_13;
        }
block_13:
        if ((s32) (windowGetKeyInfo()->unk0 & 0x400) != 0) {
            temp_r3_2 = GSinputButtonsPressed(1);
            if ((u32) (temp_r3_2 & 0x400) != 0) {
                _CB.unkB104 = 5;
            }
            if ((u32) (temp_r3_2 & 2) != 0) {
                _CB.unkB104 = 4;
            }
            if ((u32) (temp_r3_2 & 4) != 0) {
                _CB.unkB104 = 3;
            }
            if ((u32) (temp_r3_2 & 0x800) != 0) {
                _CB.unkB104 = 2;
            }
            if ((u32) (temp_r3_2 & 8) != 0) {
                _CB.unkB104 = 1;
            }
            if ((u32) (temp_r3_2 & 1) != 0) {
                _CB.unkB104 = 0;
            }
        }
    }
}

void menuCB_tunaidePokemonSelect0_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKl(MenuDBWindow *arg0, MenuDBSprite *arg1, s32 arg2) {
    s16 temp_r4;

    temp_r4 = arg1->unk6;
    switch (temp_r4) {
    case 0x256:
    case 0x291:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, 0, arg2);
        return;
    case 0x266:
    case 0x288:
        menuCBPokemonWazaTYPE(arg0, 0, arg2, 0);
        return;
    case 0x265:
    case 0x289:
        menuCBPokemonWazaTYPE(arg0, 0, arg2, 1);
        return;
    case 0x264:
    case 0x28B:
        menuCBPokemonWazaTYPE(arg0, 0, arg2, 2);
        return;
    case 0x263:
    case 0x27E:
        menuCBPokemonWazaTYPE(arg0, 0, arg2, 3);
        return;
    case 0x268:
    case 0x286:
        menuCBPokemonTYPE1(arg0, 0, arg2);
        return;
    case 0x267:
    case 0x287:
        menuCBPokemonTYPE2(arg0, 0, arg2);
        return;
    case 0x269:
    case 0x27D:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId(0, arg2));
        return;
    case 0x26A:
    case 0x296:
        menuCBPokemonStatusDisp(arg0, 0, arg2, 0, 4);
        return;
    case 0x26B:
    case 0x27C:
        menuCBPokemonStatusDisp(arg0, 0, arg2, 0, 3);
        return;
    case 0x26C:
    case 0x28D:
        menuCBPokemonStatusDisp(arg0, 0, arg2, 0, 2);
        return;
    case 0x26D:
    case 0x299:
        menuCBPokemonStatusDisp(arg0, 0, arg2, 0, 1);
        return;
    case 0x26E:
    case 0x27B:
        menuCBPokemonStatusDisp(arg0, 0, arg2, 0, 0);
        return;
    case 0x26F:
    case 0x293:
        menuCBPokemonWazaNAME(arg0, 0, arg2, 3);
        return;
    case 0x270:
    case 0x298:
        menuCBPokemonWazaNAME(arg0, 0, arg2, 2);
        return;
    case 0x271:
    case 0x28A:
        menuCBPokemonWazaNAME(arg0, 0, arg2, 1);
        return;
    case 0x272:
    case 0x295:
        menuCBPokemonWazaNAME(arg0, 0, arg2, 0);
        return;
    case 0x273:
    case 0x297:
        menuCBPokemonTOKUSEI(arg0, 0, arg2);
        return;
    case 0x274:
    case 0x27A:
        menuCBPokemonItemName(arg0, 0U, (u32) arg2, 1);
        return;
    case 0x275:
    case 0x290:
        menuCBPokemonHP(arg0, 0, arg2, 1);
        return;
    case 0x276:
    case 0x279:
        menuCBPokemonLevel(arg0, 0, arg2, 1);
        return;
    case 0x278:
    case 0x294:
        menuCBPokemonName(arg0, 0, arg2, 1);
        /* fallthrough */
    default:
        return;
    }
}

void menuCB_tunaidePokemonSelect0_Disp_R(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 temp_r31;

    temp_r31 = _CB.unkB104;
    if (temp_r31 == -1) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (menuCBPokemonCheck(0, temp_r31) == 0) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (toolentryTaisenGetHomePlace(0) != 0) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (menuCB_GCStatusDispMode(arg1, 1) != 0) {
        menuCB_tunaidePokemonSelect0_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKl(arg0, arg1, temp_r31);
    }
}

void menuCB_tunaidePokemonSelect0_Disp_L(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 temp_r31;

    temp_r31 = _CB.unkB104;
    if (temp_r31 == -1) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (menuCBPokemonCheck(0, temp_r31) == 0) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (toolentryTaisenGetHomePlace(0) != 0) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    if (menuCB_GCStatusDispMode(arg1, 0) != 0) {
        menuCB_tunaidePokemonSelect0_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKl(arg0, arg1, temp_r31);
    }
}

void menuTool_tunaidePokemonSelect0_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaidePokemonSelect0_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_tunaideGCEntry04_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s32 temp_r28;
    s32 temp_r29;

    temp_r28 = _CB.unkB0EC;
    temp_r29 = getDancerQuantity__12CReliveStageFv(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r28));
    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetEnv(arg0->unk1C);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x1CC:
        menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 4);
        return;
    case 0x21E:
        if (temp_r29 == 1) {
            menuCB2DPokemonDisp(arg0, arg1, 6, (temp_r28 * 0x10000) & 0xFFFF0000);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x21D:
        if (temp_r29 == 2) {
            menuCB2DPokemonDisp(arg0, arg1, 6, (temp_r28 * 0x10000) & 0xFFFF0000);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x21C:
        if (temp_r29 == 2) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 1);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1CD:
        if (temp_r29 == 3) {
            menuCB2DPokemonDisp(arg0, arg1, 6, (temp_r28 * 0x10000) & 0xFFFF0000);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1CF:
        if (temp_r29 == 3) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 1);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1CE:
        if (temp_r29 == 3) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 2);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1D2:
        if (temp_r29 == 4) {
            menuCB2DPokemonDisp(arg0, arg1, 6, (temp_r28 * 0x10000) & 0xFFFF0000);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1D3:
        if (temp_r29 == 4) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 1);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1D0:
        if (temp_r29 == 4) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 2);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    case 0x1D1:
        if (temp_r29 == 4) {
            menuCB2DPokemonDisp(arg0, arg1, 6, ((temp_r28 * 0x10000) & 0xFFFF0000) | 3);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        return;
    }
}

void menuTool_tunaideGCEntry04_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaideGCEntry04_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB0F0 == 2);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB0F0 == 2)) {
        arg0->unk8C = (s16) _CB.unkB158;
    }
}

void menuCB_tunaideGCEntry03_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;

    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    spriteSetEnv(arg0->unk1C);
    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x1C3:
        menuCB2DPokemonDisp(arg0, arg1, 4, 0);
        return;
    case 0x1C4:
        menuCB2DPokemonDisp(arg0, arg1, 4, 1);
        return;
    case 0x1C5:
        menuCB2DPokemonDisp(arg0, arg1, 4, 2);
        return;
    case 0x1C6:
        menuCB2DPokemonDisp(arg0, arg1, 4, 3);
        return;
    case 0x1C7:
        menuCB2DPokemonDisp(arg0, arg1, 4, 4);
        return;
    case 0x1C8:
        menuCB2DPokemonDisp(arg0, arg1, 4, 5);
        return;
    }
}

void menuTool_tunaideGCEntry03_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaideGCEntry03_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB0F0 == 0);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB0F0 == 0)) {
        arg0->unk8C = (s16) _CB.unkB158;
    }
}

void menuCB_tunaideGCEntry02_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s32 temp_r29;

    temp_r29 = _CB.unkB0E8;
    spriteSetOffset(arg0->unk1C, 0, 0);
    spriteSetEnv(arg0->unk1C);
    spriteSetScissor(arg0->unk1C, 0x12, 0x51, 0x180, 0x140);
    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x199:
    case 0x19A:
    case 0x19B:
    case 0x19C:
    case 0x19D:
    case 0x19E:
    case 0x19F:
    case 0x1A0:
    case 0x1A1:
    case 0x1A2:
    case 0x1A3:
    case 0x1A4:
    case 0x1A5:
    case 0x1A6:
    case 0x1A7:
    case 0x1A8:
    case 0x1A9:
    case 0x1AA:
    case 0x1AB:
    case 0x1AC:
    case 0x1AD:
    case 0x1AE:
    case 0x1AF:
    case 0x1B0:
    case 0x1B1:
    case 0x1B2:
    case 0x1B3:
    case 0x1B4:
    case 0x1B5:
    case 0x1B6:
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PCBOXBG_Char[temp_r29]));
        return;
    case 0x1FE:
        menuCB2DPokemonDisp(arg0, arg1, 5, (temp_r29 * 0x10000) & 0xFFFF0000);
        return;
    case 0x1FF:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 1);
        return;
    case 0x200:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 2);
        return;
    case 0x201:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 3);
        return;
    case 0x202:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 4);
        return;
    case 0x203:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 5);
        return;
    case 0x204:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 6);
        return;
    case 0x205:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 7);
        return;
    case 0x206:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 8);
        return;
    case 0x207:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 9);
        return;
    case 0x208:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xA);
        return;
    case 0x209:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xB);
        return;
    case 0x20A:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xC);
        return;
    case 0x20B:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xD);
        return;
    case 0x20C:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xE);
        return;
    case 0x20D:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0xF);
        return;
    case 0x20E:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x10);
        return;
    case 0x20F:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x11);
        return;
    case 0x210:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x12);
        return;
    case 0x211:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x13);
        return;
    case 0x212:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x14);
        return;
    case 0x213:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x15);
        return;
    case 0x214:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x16);
        return;
    case 0x215:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x17);
        return;
    case 0x216:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x18);
        return;
    case 0x217:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x19);
        return;
    case 0x218:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x1A);
        return;
    case 0x219:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x1B);
        return;
    case 0x21A:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x1C);
        return;
    case 0x21B:
        menuCB2DPokemonDisp(arg0, arg1, 5, ((temp_r29 * 0x10000) & 0xFFFF0000) | 0x1D);
        return;
    }
}

void menuTool_tunaideGCEntry02_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaideGCEntry02_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF(arg0, _CB.unkB0F0 == 1);
    if (((s32) _CB.unkB150 != 0) && ((s32) _CB.unkB0F0 == 1)) {
        arg0->unk8C = (s16) _CB.unkB158;
    }
}

void menuCB_tunaideGCEntry01_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUlUl(MenuDBWindow *arg0, MenuDBSprite *arg1, u32 arg2, u32 arg3) {
    s16 temp_r7;

    temp_r7 = arg1->unk6;
    switch (temp_r7) {
    case 0x57B:
    case 0x57C:
        menuCB2DPokemonItemDisp(arg1, arg2, arg3);
        return;
    case 0x57D:
    case 0x582:
        menuCBPokemonName_nido(arg0, arg2, arg3, 0);
        return;
    case 0x57E:
    case 0x583:
        menuCBPokemonNameOrg(arg0, arg2, arg3, 0);
        return;
    case 0x580:
    case 0x585:
        menuCBPokemonHP(arg0, (s32) arg2, (s32) arg3, 0);
        return;
    case 0x57F:
    case 0x584:
        menuCBPokemonLevel(arg0, (s32) arg2, (s32) arg3, 0);
        return;
    case 0x581:
    case 0x586:
        menuCBPokemonItemName(arg0, arg2, arg3, 0);
        /* fallthrough */
    case 0x575:
    case 0x576:
    case 0x577:
    case 0x578:
    case 0x579:
    case 0x57A:
        return;
    default:
        return;
    }
}

void menuCB_tunaideGCEntry01_Disp_DOWN(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 var_r31;
    s32 var_r30;
    u32 var_r29;

    if (((s32) _CB.unkB0F4 == 1) || ((s32) _CB.unkB150 != 0)) {
        var_r29 = 2U;
    } else {
        menuCBGCEntryTypeIndex();
        var_r31 = _CB.unkB1D4;
        var_r30 = _CB.unkB1D8;
        if ((u32) var_r31 == 5U) {
            var_r29 = GCEntryStatusDispPosition[_CB.unkB0F8];
        } else {
            var_r29 = 0U;
        }
        if (menuCBPokemonCheck(var_r31, var_r30) == 0) {
            var_r29 = 3U;
        }
    }
    if (var_r29 == 1U) {
        winSpriteSetDisp(arg1, 1);
        menuCB_tunaideGCEntry01_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUlUl(arg0, arg1, (u32) var_r31, (u32) var_r30);
        return;
    }
    winSpriteSetDisp(arg1, 0);
}

void menuCB_tunaideGCEntry01_Disp_UP(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 var_r31;
    s32 var_r30;
    u32 var_r29;

    if (((s32) _CB.unkB0F4 == 1) || ((s32) _CB.unkB150 != 0)) {
        var_r29 = 2U;
    } else {
        menuCBGCEntryTypeIndex();
        var_r31 = _CB.unkB1D4;
        var_r30 = _CB.unkB1D8;
        if ((u32) var_r31 == 5U) {
            var_r29 = GCEntryStatusDispPosition[_CB.unkB0F8];
        } else {
            var_r29 = 0U;
        }
        if (menuCBPokemonCheck(var_r31, var_r30) == 0) {
            var_r29 = 3U;
        }
    }
    if (var_r29 == 0U) {
        winSpriteSetDisp(arg1, 1);
        menuCB_tunaideGCEntry01_Disp_Sub__FP14tagWINDOW_WORKP14tagSPRITE_WORKUlUl(arg0, arg1, (u32) var_r31, (u32) var_r30);
        return;
    }
    winSpriteSetDisp(arg1, 0);
}

void menuCB_tunaideGCEntry01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    if (((s32) _CB.unkB0F4 != 1) && ((s32) _CB.unkB150 == 0)) {
        menuCBGCEntryTypeIndex();
        menuCBPokemonCheck(_CB.unkB1D4, _CB.unkB1D8);
    }
    switch (arg1->unk6) {
    case 0x587:
    case 0x588:
    case 0x589:
    case 0x58A:
    case 0x58B:
    case 0x58C:
    case 0x58D:
    case 0x58E:
    case 0x58F:
        if ((s32) _CB.unkB0FC >= 2) {
            _CB.unkB0FC = 3;
            winSpriteSetDisp(arg1, 1);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        break;
    case 0x590:
        if ((s32) _CB.unkB0FC >= 2) {
            msgctrlSetValue(0x34, _CB.unkB1E0);
            msgctrlSetValue(0x2F, _CB.unkB1E0);
            arg1->unk4C = (u32) _CB.unkB1DC;
            winSpriteSetDisp(arg1, 1);
            return;
        }
        winSpriteSetDisp(arg1, 0);
        break;
    }
}

void menuTool_tunaideGCEntry01_Button(MenuDBWindow *arg0) {
    if (pauseIsPause() == 0) {
        if (((s32) _CB.unkB0FC == 3) && ((s32) (windowGetKeyInfo()->unk4 & 0x30) != 0)) {
            _CB.unkB0FC = 0;
            return;
        }
        if ((s32) _CB.unkB0F4 == 1) {
            arg0->unkA4 = 1;
            return;
        }
        if ((s32) _CB.unkB0FC == 1) {
            arg0->unkA4 = 1;
        }
    }
}

void menuTool_tunaideGCEntry01_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_tunaideGCEntry00_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {                              /* switch 1 */
    case 0x54E:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 0);
        return;
    case 0x54F:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 1);
        return;
    case 0x550:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 2);
        return;
    case 0x551:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 3);
        return;
    case 0x552:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 4);
        return;
    case 0x553:                                     /* switch 1 */
        menuCB2DPokemonDisp(arg0, arg1, 7, 5);
        return;
    case 0x554:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 0U);
        return;
    case 0x555:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 1U);
        return;
    case 0x556:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 2U);
        return;
    case 0x557:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 3U);
        return;
    case 0x558:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 4U);
        return;
    case 0x559:                                     /* switch 1 */
        menuCB2DPokemonItemDisp(arg1, 7U, 5U);
        return;
    case 0x55A:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 0, 0);
        return;
    case 0x55E:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 1, 0);
        return;
    case 0x562:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 2, 0);
        return;
    case 0x566:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 3, 0);
        return;
    case 0x56A:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 4, 0);
        return;
    case 0x56E:                                     /* switch 1 */
        menuCBPokemonName(arg0, 7, 5, 0);
        return;
    case 0x55B:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 0, 0);
        return;
    case 0x55F:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 1, 0);
        return;
    case 0x563:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 2, 0);
        return;
    case 0x567:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 3, 0);
        return;
    case 0x56B:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 4, 0);
        return;
    case 0x56F:                                     /* switch 1 */
        menuCBPokemonLevel(arg0, 7, 5, 0);
        return;
    case 0x55C:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 0, 0);
        return;
    case 0x560:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 1, 0);
        return;
    case 0x564:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 2, 0);
        return;
    case 0x568:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 3, 0);
        return;
    case 0x56C:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 4, 0);
        return;
    case 0x570:                                     /* switch 1 */
        menuCBPokemonHP(arg0, 7, 5, 0);
        return;
    case 0x55D:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 0U, 0);
        return;
    case 0x561:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 1U, 0);
        return;
    case 0x565:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 2U, 0);
        return;
    case 0x569:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 3U, 0);
        return;
    case 0x56D:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 4U, 0);
        return;
    case 0x571:                                     /* switch 1 */
        menuCBPokemonItemName(arg0, 7U, 5U, 0);
        return;
    case 0x572:                                     /* switch 1 */
        fn_80080390(arg0, arg1, 0x435E);
        return;
    case 0x573:                                     /* switch 1 */
        fn_80080390(arg0, arg1, 0x435F);
        return;
    case 0x574:                                     /* switch 1 */
        switch ((s32) _CB.unkB0F0) {                /* switch 2; irregular */
        case 3:                                     /* switch 2 */
        case 0:                                     /* switch 2 */
            menuCBGCEntryTitleDisp(arg0, arg1, 0x43EBU, _CB.unkB158);
            break;
        case 1:                                     /* switch 2 */
            menuCBPCBOXTitleNameDisp(arg0, arg1, _CB.unkB0E8, _CB.unkB158);
            break;
        case 2:                                     /* switch 2 */
            menuCBReliveTitleNameDisp(arg0, arg1, MENU_ITEM_TOOL_SANKA00_RELIVE_TITLE_Tbl[_CB.unkB0EC], _CB.unkB158);
            break;
        }
        if ((s32) _CB.unkB150 != 0) {
            switch ((s32) _CB.unkB15C) {            /* switch 3; irregular */
            case 3:                                 /* switch 3 */
            case 0:                                 /* switch 3 */
                menuCBGCEntryTitleDisp(arg0, arg1, 0x43EBU, _CB.unkB154);
                return;
            case 1:                                 /* switch 3 */
                menuCBPCBOXTitleNameDisp(arg0, arg1, _CB.unkB160, _CB.unkB154);
                return;
            case 2:                                 /* switch 3 */
                menuCBReliveTitleNameDisp(arg0, arg1, MENU_ITEM_TOOL_SANKA00_RELIVE_TITLE_Tbl[_CB.unkB164], _CB.unkB154);
                break;
            }
        } else {
        default:                                    /* switch 1 */
            return;
        }
        break;
    }
}

void menuTool_tunaideGCEntry00_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaideGCEntry00_Ctrl(MenuDBWindow *arg0) {
    s32 temp_r28;
    s32 temp_r29;
    s32 var_r29;

    temp_r28 = _CB.unkB0F8;
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (((s8) (u8) arg0->unk1 == 2) && (pauseIsPause() == 0)) {
        if ((s32) _CB.unkB150 != 0) {
            if ((s32) _CB.unkB158 == 0) {
                _CB.unkB150 = 0;
                return;
            }
            _CB.unkB154 += _CB.unkB150;
            _CB.unkB158 += _CB.unkB150;
            return;
        }
        if (((s32) _CB.unkB0FC < 2) && ((s32) _CB.unkB0FC != 1) && ((s32) _CB.unkB0F4 != 1)) {
            if (((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) || (((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) && ((s32) _CB.unkB0F8 == 0x24))) {
                menuCB_SE_Play(0x443);
                if ((s32) _CB.unkB100 == 0) {
                    _CB.unkAFF0 = 1;
                    _CB.unkB070 = 1;
                    _CB.unkB0F4 = 1;
                    return;
                }
                menuCBGCDelPokemon();
                return;
            }
            if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                if ((s32) _CB.unkB0F8 == 0x25) {
                    menuCB_SE_Play(0x442);
                    menuCB_GCEntry_OkPushErrorCheck();
                    if ((s32) _CB.unkB0FC < 2) {
                        _CB.unkAFF0 = 1;
                        _CB.unkB0F4 = 1;
                    }
                } else {
                    menuCBGCEntryTypeIndex();
                    if ((menuCBPokemonCheck(_CB.unkB1D4, _CB.unkB1D8) != 0) && ((s32) _CB.unkB0F8 <= 0x23)) {
                        _CB.unkB0FC = 1;
                    }
                }
            } else if ((s32) (windowGetKeyInfo()->unk6 & 0x400) != 0) {
                menuCB2DPokemonClearSHIFT(0);
                menuCB_SE_Play(0x444);
                switch ((s32) _CB.unkB0F0) {        /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    _CB.unkB0F0 = 1;
                    _CB.unkB0E8 = 0;
                    _CB.unkB0F8 = 0;
                    break;
                case 1:                             /* switch 1 */
                    _CB.unkB0E8 += 1;
                    if ((s32) _CB.unkB0E8 == 8) {
                        if ((u8) _CB.unkB4A0 == 1) {
                            _CB.unkB0F0 = 2;
                            _CB.unkB0EC = 0;
                        } else {
                            _CB.unkB0F0 = 0;
                        }
                        _CB.unkB0F8 = 0;
                        _CB.unkB0E8 -= 1;
                    }
                    break;
                case 2:                             /* switch 1 */
                    _CB.unkB0EC += 1;
                    if ((s32) _CB.unkB0EC == 9) {
                        _CB.unkB0F0 = 0;
                        _CB.unkB0F8 = 0;
                        _CB.unkB0EC -= 1;
                    }
                    break;
                }
                if ((s32) _CB.unkB0F0 == 2) {
                    menuCBReliveHallCursolInit();
                }
                if ((temp_r28 >= 0x1E) && (temp_r28 != (s32) _CB.unkB0F8)) {
                    _CB.unkB0F8 = temp_r28;
                }
            } else if ((s32) (windowGetKeyInfo()->unk6 & 0x200) != 0) {
                menuCB2DPokemonClearSHIFT(1);
                menuCB_SE_Play(0x444);
                switch ((s32) _CB.unkB0F0) {        /* switch 2; irregular */
                case 0:                             /* switch 2 */
                    if ((u8) _CB.unkB4A0 == 1) {
                        _CB.unkB0F0 = 2;
                        _CB.unkB0EC = 8;
                    } else {
                        _CB.unkB0F0 = 1;
                        _CB.unkB0E8 = 7;
                    }
                    _CB.unkB0F8 = 0;
                    break;
                case 1:                             /* switch 2 */
                    if ((s32) _CB.unkB0E8 == 0) {
                        _CB.unkB0F0 = 0;
                        _CB.unkB0F8 = 0;
                    } else {
                        _CB.unkB0E8 -= 1;
                    }
                    break;
                case 2:                             /* switch 2 */
                    if ((s32) _CB.unkB0EC == 0) {
                        _CB.unkB0F0 = 1;
                        _CB.unkB0E8 = 7;
                        _CB.unkB0F8 = 0;
                    } else {
                        _CB.unkB0EC -= 1;
                    }
                    break;
                }
                if ((s32) _CB.unkB0F0 == 2) {
                    menuCBReliveHallCursolInit();
                }
                if ((temp_r28 >= 0x1E) && (temp_r28 != (s32) _CB.unkB0F8)) {
                    _CB.unkB0F8 = temp_r28;
                }
            } else {
                if ((s32) _CB.unkB0F0 == 2) {
                    temp_r29 = _CB.unkB0EC;
                    var_r29 = getDancerQuantity__12CReliveStageFv(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r29));
                }
                if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                    switch ((s32) _CB.unkB0F0) {    /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                            switch (_CB.unkB0F8) {  /* switch 4 */
  /* switch 4 */
                            case 37:                /* switch 4 */
                                _CB.unkB0F8 = 5;
                                break;
                            case 36:                /* switch 4 */
                                _CB.unkB0F8 = 1;
                                break;
                            case 31:                /* switch 4 */
                                _CB.unkB0F8 = 0x1E;
                                break;
                            case 32:                /* switch 4 */
                                _CB.unkB0F8 = 0x1F;
                                break;
                            case 33:                /* switch 4 */
                                _CB.unkB0F8 = 0x20;
                                break;
                            case 34:                /* switch 4 */
                                _CB.unkB0F8 = 0x21;
                                break;
                            case 35:                /* switch 4 */
                                _CB.unkB0F8 = 0x22;
                                break;

                        case 1:                     /* switch 4 */
                        case 3:                     /* switch 4 */
                        case 4:                     /* switch 4 */
                        case 5:                     /* switch 4 */
                        case 6:                     /* switch 4 */
                        case 7:                     /* switch 4 */
                        case 8:                     /* switch 4 */
                        case 9:                     /* switch 4 */
                        case 10:                    /* switch 4 */
                        case 11:                    /* switch 4 */
                        case 12:                    /* switch 4 */
                        case 13:                    /* switch 4 */
                        case 14:                    /* switch 4 */
                        case 15:                    /* switch 4 */
                        case 16:                    /* switch 4 */
                        case 17:                    /* switch 4 */
                        case 18:                    /* switch 4 */
                        case 19:                    /* switch 4 */
                        case 20:                    /* switch 4 */
                        case 21:                    /* switch 4 */
                        case 22:                    /* switch 4 */
                        case 23:                    /* switch 4 */
                        case 24:                    /* switch 4 */
                        case 25:                    /* switch 4 */
                        case 26:                    /* switch 4 */
                        case 27:                    /* switch 4 */
                        case 28:                    /* switch 4 */
                        case 29:                    /* switch 4 */
                            _CB.unkB0F8 -= 1;
                        }
                        break;
                    case 1:                         /* switch 3 */
                        if ((s32) _CB.unkB0F8 != 0x1E) {
                            if ((s32) _CB.unkB0F8 < 0x1E) {
                                if ((s32) _CB.unkB0F8 < 6) {
                                    if ((s32) _CB.unkB0F8 < 0) {
                                        goto block_95;
                                    }
                                } else {
block_95:
                                    _CB.unkB0F8 -= 6;
                                }
                            } else {
                                switch ((s32) _CB.unkB0F8) { /* switch 5; irregular */
                                case 37:            /* switch 5 */
                                    _CB.unkB0F8 = 0x1D;
                                    break;
                                case 36:            /* switch 5 */
                                    _CB.unkB0F8 = 0x18;
                                    break;
                                default:            /* switch 5 */
                                    _CB.unkB0F8 -= 1;
                                    break;
                                }
                            }
                        }
                        break;
                    case 2:                         /* switch 3 */
                        if ((u32) _CB.unkB0F8 <= 0x25U) {
                            switch (_CB.unkB0F8) {  /* switch 6 */
                            case 37:                /* switch 6 */
                                if (var_r29 != 4) {
                                    if (var_r29 < 4) {
                                        if (var_r29 < 2) {
                                            if (var_r29 < 0) {

                                            } else if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                                _CB.unkB0F8 = 4;
                                            } else if (var_r29 == 1) {
                                                _CB.unkB0F8 = 0;
                                            }
                                        } else {
                                            _CB.unkB0F8 = 1;
                                        }
                                    }
                                } else {
                                    _CB.unkB0F8 = 2;
                                }
                                break;
                            case 36:                /* switch 6 */
                                switch (var_r29) {  /* switch 7; irregular */
                                default:            /* switch 7 */
                                    if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                        _CB.unkB0F8 = 4;
                                    } else if (var_r29 == 1) {
                                        _CB.unkB0F8 = 0;
                                    }
                                    break;
                                case 2:             /* switch 7 */
                                    _CB.unkB0F8 = 1;
                                    break;
                                case 3:             /* switch 7 */
                                    _CB.unkB0F8 = 2;
                                    break;
                                case 4:             /* switch 7 */
                                    _CB.unkB0F8 = 3;
                                    break;
                                }
                                break;
                            case 1:                 /* switch 6 */
                                if (var_r29 < 4) {
                                    if (var_r29 < 2) {

                                    } else if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                        _CB.unkB0F8 = 4;
                                    } else {
                                        _CB.unkB0F8 = 0;
                                    }
                                }
                                break;
                            case 2:                 /* switch 6 */
                                if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                    _CB.unkB0F8 = 4;
                                } else if (var_r29 == 3) {
                                    _CB.unkB0F8 = 0;
                                } else {
                                    _CB.unkB0F8 = 1;
                                }
                                break;
                            case 3:                 /* switch 6 */
                                if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                    _CB.unkB0F8 = 4;
                                } else {
                                    _CB.unkB0F8 = 0;
                                }
                                break;
                            case 4:                 /* switch 6 */
                                if ((var_r29 != 0) && (var_r29 >= 0) && (var_r29 < 5)) {
                                    _CB.unkB0F8 = 0;
                                }
                                break;
                            case 31:                /* switch 6 */
                            case 32:                /* switch 6 */
                            case 33:                /* switch 6 */
                            case 34:                /* switch 6 */
                            case 35:                /* switch 6 */
                                _CB.unkB0F8 -= 1;
                                break;
                            }
                        }
                        break;
                    }
                    if (temp_r28 != (s32) _CB.unkB0F8) {
                        menuCB_SE_Play(0x441);
                    }
                } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                    switch ((s32) _CB.unkB0F0) {    /* switch 8; irregular */
                    case 0:                         /* switch 8 */
                        switch ((s32) _CB.unkB0F8) { /* switch 9; irregular */
                        case 1:                     /* switch 9 */
                            _CB.unkB0F8 = 0x24;
                            break;
                        case 5:                     /* switch 9 */
                            _CB.unkB0F8 = 0x25;
                            break;
                        default:                    /* switch 9 */
                            _CB.unkB0F8 += 1;
                            break;
                        }
                        break;
                    case 1:                         /* switch 8 */
                        if ((s32) _CB.unkB0F8 < 0x1E) {
                            if ((s32) _CB.unkB0F8 < 0x1B) {
                                if ((s32) _CB.unkB0F8 < 0x18) {
                                    goto block_173;
                                }
                                _CB.unkB0F8 = 0x24;
                            } else {
                                _CB.unkB0F8 = 0x25;
                            }
                        } else if ((s32) _CB.unkB0F8 < 0x26) {
                            if ((s32) _CB.unkB0F8 < 0x23) {
                                _CB.unkB0F8 += 1;
                            }
                        } else {
block_173:
                            _CB.unkB0F8 += 6;
                        }
                        break;
                    case 2:                         /* switch 8 */
                        switch ((s32) _CB.unkB0F8) { /* switch 10; irregular */
                        case 0:                     /* switch 10 */
                            if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                _CB.unkB0F8 = 4;
                            } else {
                                switch (var_r29) {  /* switch 11; irregular */
                                case 1:             /* switch 11 */
                                    _CB.unkB0F8 = 0x25;
                                    break;
                                case 2:             /* switch 11 */
                                    _CB.unkB0F8 = 1;
                                    break;
                                case 3:             /* switch 11 */
                                    _CB.unkB0F8 = 2;
                                    break;
                                case 4:             /* switch 11 */
                                    _CB.unkB0F8 = 3;
                                    break;
                                }
                            }
                            break;
                        case 1:                     /* switch 10 */
                            if (var_r29 != 4) {
                                if (var_r29 < 4) {
                                    if (var_r29 < 2) {

                                    } else {
                                        _CB.unkB0F8 = 0x25;
                                    }
                                }
                            } else if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                _CB.unkB0F8 = 4;
                            } else {
                                _CB.unkB0F8 = 2;
                            }
                            break;
                        case 2:                     /* switch 10 */
                            switch (var_r29) {      /* switch 12; irregular */
                            case 3:                 /* switch 12 */
                                _CB.unkB0F8 = 0x24;
                                break;
                            case 4:                 /* switch 12 */
                                _CB.unkB0F8 = 0x25;
                                break;
                            }
                            break;
                        case 3:                     /* switch 10 */
                            _CB.unkB0F8 = 0x24;
                            break;
                        case 4:                     /* switch 10 */
                            switch (var_r29) {      /* switch 13; irregular */
                            default:                /* switch 13 */
                                _CB.unkB0F8 = 0x25;
                                break;
                            case 2:                 /* switch 13 */
                                _CB.unkB0F8 = 1;
                                break;
                            case 3:                 /* switch 13 */
                                _CB.unkB0F8 = 2;
                                break;
                            case 4:                 /* switch 13 */
                                _CB.unkB0F8 = 3;
                                break;
                            }
                            break;
                        default:                    /* switch 10 */
                            _CB.unkB0F8 += 1;
                            break;
                        }
                        break;
                    }
                    if (temp_r28 != (s32) _CB.unkB0F8) {
                        menuCB_SE_Play(0x441);
                    }
                }
                if ((s32) (windowGetKeyRepeat() & 4) != 0) {
                    switch ((s32) _CB.unkB0F0) {    /* switch 14; irregular */
                    case 0:                         /* switch 14 */
                        if ((u32) _CB.unkB0F8 <= 0x25U) {
                            switch (_CB.unkB0F8) {  /* switch 15 */
                            case 37:                /* switch 15 */
                                _CB.unkB0F8 = 0x24;
                                break;
                            case 30:                /* switch 15 */
                                _CB.unkB0F8 = 2;
                                break;
                            case 31:                /* switch 15 */
                                _CB.unkB0F8 = 3;
                                break;
                            case 32:                /* switch 15 */
                                _CB.unkB0F8 = 4;
                                break;
                            case 33:                /* switch 15 */
                                _CB.unkB0F8 = 5;
                                break;
                            case 34:                /* switch 15 */
                            case 35:                /* switch 15 */
                                _CB.unkB0F8 = 0x25;
                                break;
                            case 2:                 /* switch 15 */
                                _CB.unkB0F8 = 0;
                                break;
                            case 3:                 /* switch 15 */
                                _CB.unkB0F8 = 0;
                                break;
                            case 4:                 /* switch 15 */
                                _CB.unkB0F8 = 1;
                                break;
                            case 5:                 /* switch 15 */
                                _CB.unkB0F8 = 1;
                                break;
                            }
                        }
                        break;
                    case 1:                         /* switch 14 */
                            switch (_CB.unkB0F8) {  /* switch 16 */
  /* switch 16 */
                            case 37:                /* switch 16 */
                                _CB.unkB0F8 = 0x24;
                                break;
                            case 30:                /* switch 16 */
                                _CB.unkB0F8 = 5;
                                break;
                            case 31:                /* switch 16 */
                                _CB.unkB0F8 = 0xB;
                                break;
                            case 32:                /* switch 16 */
                                _CB.unkB0F8 = 0x11;
                                break;
                            case 33:                /* switch 16 */
                                _CB.unkB0F8 = 0x17;
                                break;
                            case 34:                /* switch 16 */
                                _CB.unkB0F8 = 0x1D;
                                break;
                            case 35:                /* switch 16 */
                                _CB.unkB0F8 = 0x25;
                                break;

                        case 1:                     /* switch 16 */
                        case 2:                     /* switch 16 */
                        case 3:                     /* switch 16 */
                        case 4:                     /* switch 16 */
                        case 5:                     /* switch 16 */
                        case 7:                     /* switch 16 */
                        case 8:                     /* switch 16 */
                        case 9:                     /* switch 16 */
                        case 10:                    /* switch 16 */
                        case 11:                    /* switch 16 */
                        case 13:                    /* switch 16 */
                        case 14:                    /* switch 16 */
                        case 15:                    /* switch 16 */
                        case 16:                    /* switch 16 */
                        case 17:                    /* switch 16 */
                        case 19:                    /* switch 16 */
                        case 20:                    /* switch 16 */
                        case 21:                    /* switch 16 */
                        case 22:                    /* switch 16 */
                        case 23:                    /* switch 16 */
                        case 25:                    /* switch 16 */
                        case 26:                    /* switch 16 */
                        case 27:                    /* switch 16 */
                        case 28:                    /* switch 16 */
                        case 29:                    /* switch 16 */
                            _CB.unkB0F8 -= 1;
                        }
                        break;
                    case 2:                         /* switch 14 */
                        switch ((s32) _CB.unkB0F8) { /* switch 17; irregular */
                        case 1:                     /* switch 17 */
                            switch (var_r29) {      /* switch 18; irregular */
                            case 3:                 /* switch 18 */
                                _CB.unkB0F8 = 2;
                                break;
                            case 4:                 /* switch 18 */
                                _CB.unkB0F8 = 0;
                                break;
                            }
                            break;
                        case 2:                     /* switch 17 */
                            if (var_r29 != 4) {

                            } else {
                                _CB.unkB0F8 = 3;
                            }
                            break;
                        case 4:                     /* switch 17 */
                            switch (var_r29) {      /* switch 19; irregular */
                            case 3:                 /* switch 19 */
                                _CB.unkB0F8 = 2;
                                break;
                            case 4:                 /* switch 19 */
                                _CB.unkB0F8 = 0;
                                break;
                            }
                            break;
                        case 37:                    /* switch 17 */
                            _CB.unkB0F8 = 0x24;
                            break;
                        default:                    /* switch 17 */
                            if (menuCBPokemonCheck(6, ((_CB.unkB0EC * 0x10000) & 0xFFFF0000) | 4) != 0) {
                                _CB.unkB0F8 = 4;
                            } else {
                                _CB.unkB0F8 = 0x25;
                            }
                            break;
                        }
                        break;
                    }
                    if (temp_r28 != (s32) _CB.unkB0F8) {
                        menuCB_SE_Play(0x441);
                    }
                } else if ((s32) (windowGetKeyRepeat() & 8) != 0) {
                    switch ((s32) _CB.unkB0F0) {    /* switch 20; irregular */
                    case 0:                         /* switch 20 */
                        if ((u32) _CB.unkB0F8 <= 0x25U) {
                            switch (_CB.unkB0F8) {  /* switch 21 */
                            case 0:                 /* switch 21 */
                                _CB.unkB0F8 = 2;
                                break;
                            case 1:                 /* switch 21 */
                                _CB.unkB0F8 = 4;
                                break;
                            case 2:                 /* switch 21 */
                                _CB.unkB0F8 = 0x1E;
                                break;
                            case 3:                 /* switch 21 */
                                _CB.unkB0F8 = 0x1F;
                                break;
                            case 4:                 /* switch 21 */
                                _CB.unkB0F8 = 0x20;
                                break;
                            case 5:                 /* switch 21 */
                                _CB.unkB0F8 = 0x21;
                                break;
                            case 37:                /* switch 21 */
                                _CB.unkB0F8 = 0x22;
                                break;
                            case 36:                /* switch 21 */
                                _CB.unkB0F8 = 0x25;
                                break;
                            }
                        }
                        break;
                    case 1:                         /* switch 20 */
                        switch (_CB.unkB0F8) {      /* switch 22 */
                        case 5:                     /* switch 22 */
                            _CB.unkB0F8 = 0x1E;
                            break;
                        case 11:                    /* switch 22 */
                            _CB.unkB0F8 = 0x1F;
                            break;
                        case 17:                    /* switch 22 */
                            _CB.unkB0F8 = 0x20;
                            break;
                        case 23:                    /* switch 22 */
                            _CB.unkB0F8 = 0x21;
                            break;
                        case 29:                    /* switch 22 */
                            _CB.unkB0F8 = 0x22;
                            break;
                        case 37:                    /* switch 22 */
                            _CB.unkB0F8 = 0x23;
                            break;
                        case 36:                    /* switch 22 */
                            _CB.unkB0F8 = 0x25;
                            break;
                        default:                    /* switch 22 */
                            _CB.unkB0F8 += 1;
                            break;
                        }
                        break;
                    case 2:                         /* switch 20 */
                        switch ((s32) _CB.unkB0F8) { /* switch 23; irregular */
                        case 0:                     /* switch 23 */
                            if (var_r29 != 4) {
                                if (var_r29 < 4) {
                                    if (var_r29 < 1) {

                                    } else {
                                        _CB.unkB0F8 = 0x1E;
                                    }
                                }
                            } else {
                                _CB.unkB0F8 = 1;
                            }
                            break;
                        case 1:                     /* switch 23 */
                            if (var_r29 < 5) {
                                if (var_r29 < 2) {

                                } else {
                                    _CB.unkB0F8 = 0x1E;
                                }
                            }
                            break;
                        case 2:                     /* switch 23 */
                            switch (var_r29) {      /* switch 24; irregular */
                            case 3:                 /* switch 24 */
                                _CB.unkB0F8 = 1;
                                break;
                            case 4:                 /* switch 24 */
                                _CB.unkB0F8 = 0x1E;
                                break;
                            }
                            break;
                        case 3:                     /* switch 23 */
                            _CB.unkB0F8 = 2;
                            break;
                        case 4:                     /* switch 23 */
                            if (var_r29 < 3) {
                                if (var_r29 < 0) {

                                } else {
                                    _CB.unkB0F8 = 0x1E;
                                }
                            } else if (var_r29 < 5) {
                                _CB.unkB0F8 = 1;
                            }
                            break;
                        case 37:                    /* switch 23 */
                            _CB.unkB0F8 = 0x23;
                            break;
                        case 36:                    /* switch 23 */
                            _CB.unkB0F8 = 0x25;
                            break;
                        }
                        break;
                    }
                    if (temp_r28 != (s32) _CB.unkB0F8) {
                        menuCB_SE_Play(0x441);
                    }
                }
                if (((s32) (windowGetKeyInfo()->unk4 & 0x800) != 0) && ((s32) _CB.unkB0F8 != 0x25)) {
                    _CB.unkB0F8 = 0x25;
                    menuCB_SE_Play(0x441);
                }
            }
        }
    }
}

void menuTool_tunaideGCEntry_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaideGCEntry_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    systemUpdate__4CAntFb(1U);
    menuCB_AlphaGet(arg0);
}

void menuCB_BattleBeforeAfter6_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0x4B8:
    case 0x4B9:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 0);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 1);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 2);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 5);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 3);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    case 0x4BA:
    case 0x4BB:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 1);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 2);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 5);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 3);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    case 0x4BC:
    case 0x4BD:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 2);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 5);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 3);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    case 0x4BE:
    case 0x4BF:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 5);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 3);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    case 0x4C0:
    case 0x4C1:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 3);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    case 0x4C2:
    case 0x4C3:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk10 == 4);
        break;
    default:
        return;
    }
}

void menuTool_BattleBA06_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_BattleBA06_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_BattleBeforeAfter5_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0x2D2:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 0);
          return;
        break;
    case 0x2D3:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 1);
          return;
        break;
    case 0x2D4:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 2);
          return;
        break;
    case 0x2D5:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 0);
          return;
        break;
    case 0x2D6:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 1);
          return;
        break;
    case 0x2D7:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 2);
          return;
        break;
    case 0x179:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 0);
          return;
        break;
    case 0x17A:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 1);
          return;
        break;
    case 0x17B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 2);
          return;
        break;
    case 0x17F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 0);
          return;
        break;
    case 0x180:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 1);
          return;
        break;
    case 0x181:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 2);
          return;
        break;
    case 0x18F:
        toobattle_drawHeroName2(arg0, arg1, 0x0);
        return;
    case 0x190:
        toobattle_drawHeroName2(arg0, arg1, 0x1);
        return;

    case 0x185:
        menuCBBattleBABatuMark(arg1, 1, 0);
          return;
        break;
    case 0x186:
        menuCBBattleBABatuMark(arg1, 1, 1);
          return;
        break;
    case 0x187:
        menuCBBattleBABatuMark(arg1, 1, 2);
          return;
        break;
    case 0x188:
        menuCBBattleBABatuMark(arg1, 0, 0);
          return;
        break;
    case 0x189:
        menuCBBattleBABatuMark(arg1, 0, 1);
          return;
        break;
    case 0x18A:
        menuCBBattleBABatuMark(arg1, 0, 2);
          return;
        break;
    case 0x18B:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 0);
          return;
        break;
    case 0x18C:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 1);
          return;
        break;
    case 0x17C:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 0);
          return;
        break;
    case 0x17D:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 1);
          return;
        break;
    case 0x17E:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 2);
          return;
        break;
    case 0x182:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 0);
          return;
        break;
    case 0x183:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 1);
          return;
        break;
    case 0x184:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 2);
          return;
        break;
    case 0x1F8:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 0);
          return;
        break;
    case 0x1F9:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 1);
          return;
        break;
    case 0x1FA:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 2);
          return;
        break;
    case 0x1FB:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 0);
          return;
        break;
    case 0x1FC:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 1);
          return;
        break;
    case 0x1FD:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 2);
          return;
        break;
    case 0x18D:
        menuCB_PrintXP(arg1, 0);
          return;
        break;
    case 0x18E:
        if ((((s32) _CB.unk4) == 1) && (((s32) _CB.unkAFD4) == 0))
          {
            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PlayerNumber[4]));
            return;
          }
          menuCB_PrintXP(arg1, 1);
          return;
        break;
    default:
        return;
    }
}

void menuTool_BattleBA05_Button(MenuDBWindow *arg0) {
    if ((pauseIsPause() == 0) && (menuCBBattleBANextMenu(arg0) != 0) && ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0)) {
        arg0->unkA4 = 1;
    }
}

void menuTool_BattleBA05_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (((s32) _CB.unk4 == 0) && (menuCBBattleStartGetStatus() == 0) && (menuCB_GetDisconnectedGBA() != 0)) {
        _CB.unkB19C = 1;
        arg0->unkA4 = 1;
        arg0->unkA5 = 1;
    }
}

void menuCB_BattleBeforeAfter4_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0x2C6:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 0);
          return;
        break;
    case 0x2C7:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 1);
          return;
        break;
    case 0x2C8:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 2);
          return;
        break;
    case 0x2C9:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 3);
          return;
        break;
    case 0x2CA:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 4);
          return;
        break;
    case 0x2CB:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 5);
          return;
        break;
    case 0x2CC:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 0);
          return;
        break;
    case 0x2CD:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 1);
          return;
        break;
    case 0x2CE:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 2);
          return;
        break;
    case 0x2CF:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 3);
          return;
        break;
    case 0x2D0:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 4);
          return;
        break;
    case 0x2D1:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 5);
          return;
        break;
    case 0x14F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 0);
          return;
        break;
    case 0x150:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 1);
          return;
        break;
    case 0x151:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 2);
          return;
        break;
    case 0x155:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 3);
          return;
        break;
    case 0x156:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 4);
          return;
        break;
    case 0x157:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 5);
          return;
        break;
    case 0x15B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 0);
          return;
        break;
    case 0x15C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 1);
          return;
        break;
    case 0x15D:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 2);
          return;
        break;
    case 0x161:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 3);
          return;
        break;
    case 0x162:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 4);
          return;
        break;
    case 0x163:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 5);
          return;
        break;
    case 0x177:
        toobattle_drawHeroName2(arg0, arg1, 0x0);
        return;
    case 0x178:
        toobattle_drawHeroName2(arg0, arg1, 0x1);
        return;

    case 0x167:
        menuCBBattleBABatuMark(arg1, 1, 3);
          return;
        break;
    case 0x168:
        menuCBBattleBABatuMark(arg1, 1, 4);
          return;
        break;
    case 0x169:
        menuCBBattleBABatuMark(arg1, 1, 5);
          return;
        break;
    case 0x16A:
        menuCBBattleBABatuMark(arg1, 1, 0);
          return;
        break;
    case 0x16B:
        menuCBBattleBABatuMark(arg1, 1, 1);
          return;
        break;
    case 0x16C:
        menuCBBattleBABatuMark(arg1, 1, 2);
          return;
        break;
    case 0x16D:
        menuCBBattleBABatuMark(arg1, 0, 3);
          return;
        break;
    case 0x16E:
        menuCBBattleBABatuMark(arg1, 0, 4);
          return;
        break;
    case 0x16F:
        menuCBBattleBABatuMark(arg1, 0, 5);
          return;
        break;
    case 0x170:
        menuCBBattleBABatuMark(arg1, 0, 0);
          return;
        break;
    case 0x171:
        menuCBBattleBABatuMark(arg1, 0, 1);
          return;
        break;
    case 0x172:
        menuCBBattleBABatuMark(arg1, 0, 2);
          return;
        break;
    case 0x173:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 0);
          return;
        break;
    case 0x174:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 1);
          return;
        break;
    case 0x152:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 0);
          return;
        break;
    case 0x153:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 1);
          return;
        break;
    case 0x154:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 2);
          return;
        break;
    case 0x158:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 3);
          return;
        break;
    case 0x159:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 4);
          return;
        break;
    case 0x15A:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 5);
          return;
        break;
    case 0x15E:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 0);
          return;
        break;
    case 0x15F:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 1);
          return;
        break;
    case 0x160:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 2);
          return;
        break;
    case 0x164:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 3);
          return;
        break;
    case 0x165:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 4);
          return;
        break;
    case 0x166:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 5);
          return;
        break;
    case 0x1EC:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 0);
          return;
        break;
    case 0x1ED:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 1);
          return;
        break;
    case 0x1EE:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 2);
          return;
        break;
    case 0x1EF:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 3);
          return;
        break;
    case 0x1F0:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 4);
          return;
        break;
    case 0x1F1:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 5);
          return;
        break;
    case 0x1F2:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 0);
          return;
        break;
    case 0x1F3:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 1);
          return;
        break;
    case 0x1F4:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 2);
          return;
        break;
    case 0x1F5:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 3);
          return;
        break;
    case 0x1F6:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 4);
          return;
        break;
    case 0x1F7:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 5);
          return;
        break;
    case 0x175:
        menuCB_PrintXP(arg1, 0);
          return;
        break;
    case 0x176:
        menuCB_PrintXP(arg1, 1);
          return;
        break;
    default:
        return;
    }
}

void menuTool_BattleBA04_Button(MenuDBWindow *arg0) {
    if ((pauseIsPause() == 0) && (menuCBBattleBANextMenu(arg0) != 0) && ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0)) {
        arg0->unkA4 = 1;
    }
}

void menuTool_BattleBA04_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (((s32) _CB.unk4 == 0) && (menuCBBattleStartGetStatus() == 0) && (menuCB_GetDisconnectedGBA() != 0)) {
        _CB.unkB19C = 1;
        arg0->unkA4 = 1;
        arg0->unkA5 = 1;
    }
}

void menuCB_BattleBeforeAfter3_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0xFF:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 0);
          return;
        break;
    case 0x100:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 1);
          return;
        break;
    case 0x101:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 2);
          return;
        break;
    case 0x102:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 3);
          return;
        break;
    case 0x103:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 4);
          return;
        break;
    case 0x104:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 0, 5);
          return;
        break;
    case 0x2B4:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 0);
          return;
        break;
    case 0x2B5:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 1);
          return;
        break;
    case 0x2B6:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 2);
          return;
        break;
    case 0x2B7:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 3);
          return;
        break;
    case 0x2B8:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 4);
          return;
        break;
    case 0x2B9:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 1, 5);
          return;
        break;
    case 0x2BA:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 0);
          return;
        break;
    case 0x2BB:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 1);
          return;
        break;
    case 0x2BC:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 2);
          return;
        break;
    case 0x2BD:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 3);
          return;
        break;
    case 0x2BE:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 4);
          return;
        break;
    case 0x2BF:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 2, 5);
          return;
        break;
    case 0x2C0:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 0);
          return;
        break;
    case 0x2C1:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 1);
          return;
        break;
    case 0x2C2:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 2);
          return;
        break;
    case 0x2C3:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 3);
          return;
        break;
    case 0x2C4:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 4);
          return;
        break;
    case 0x2C5:
        menuCBPokemonEntryDispPokemonFace_AFTER(arg0, arg1, 3, 5);
          return;
        break;
    case 0x2AE:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 0);
          return;
        break;
    case 0x2AF:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 1);
          return;
        break;
    case 0x2B0:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 2);
          return;
        break;
    case 0x2B1:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 3);
          return;
        break;
    case 0x2B2:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 4);
          return;
        break;
    case 0x2B3:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 0, 5);
          return;
        break;
    case 0x10B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 0);
          return;
        break;
    case 0x10C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 1);
          return;
        break;
    case 0x10D:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 2);
          return;
        break;
    case 0x10E:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 3);
          return;
        break;
    case 0x10F:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 4);
          return;
        break;
    case 0x110:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 1, 5);
          return;
        break;
    case 0x117:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 0);
          return;
        break;
    case 0x118:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 1);
          return;
        break;
    case 0x119:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 2);
          return;
        break;
    case 0x11A:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 3);
          return;
        break;
    case 0x11B:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 4);
          return;
        break;
    case 0x11C:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 2, 5);
          return;
        break;
    case 0x123:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 0);
          return;
        break;
    case 0x124:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 1);
          return;
        break;
    case 0x125:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 2);
          return;
        break;
    case 0x126:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 3);
          return;
        break;
    case 0x127:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 4);
          return;
        break;
    case 0x128:
        menuCBPokemonEntryDispPokemonFace_BEFORE(arg0, arg1, 3, 5);
          return;
        break;
    case 0x14E:
        toobattle_drawHeroName2(arg0, arg1, 3);
        return;

    case 0x14D:
        toobattle_drawHeroName2(arg0, arg1, 2);
        return;
    case 0x14C:
        toobattle_drawHeroName2(arg0, arg1, 1);
        return;
    case 0x14B:
        toobattle_drawHeroName2(arg0, arg1, 0);
        return;
    case 0x12F:
        menuCBBattleBABatuMark(arg1, 3, 0);
          return;
        break;
    case 0x130:
        menuCBBattleBABatuMark(arg1, 3, 1);
          return;
        break;
    case 0x131:
        menuCBBattleBABatuMark(arg1, 3, 2);
          return;
        break;
    case 0x132:
        menuCBBattleBABatuMark(arg1, 3, 3);
          return;
        break;
    case 0x133:
        menuCBBattleBABatuMark(arg1, 3, 4);
          return;
        break;
    case 0x134:
        menuCBBattleBABatuMark(arg1, 3, 5);
          return;
        break;
    case 0x135:
        menuCBBattleBABatuMark(arg1, 2, 0);
          return;
        break;
    case 0x136:
        menuCBBattleBABatuMark(arg1, 2, 1);
          return;
        break;
    case 0x137:
        menuCBBattleBABatuMark(arg1, 2, 2);
          return;
        break;
    case 0x138:
        menuCBBattleBABatuMark(arg1, 2, 3);
          return;
        break;
    case 0x139:
        menuCBBattleBABatuMark(arg1, 2, 4);
          return;
        break;
    case 0x13A:
        menuCBBattleBABatuMark(arg1, 2, 5);
          return;
        break;
    case 0x13B:
        menuCBBattleBABatuMark(arg1, 1, 0);
          return;
        break;
    case 0x13C:
        menuCBBattleBABatuMark(arg1, 1, 1);
          return;
        break;
    case 0x13D:
        menuCBBattleBABatuMark(arg1, 1, 2);
          return;
        break;
    case 0x13E:
        menuCBBattleBABatuMark(arg1, 1, 3);
          return;
        break;
    case 0x13F:
        menuCBBattleBABatuMark(arg1, 1, 4);
          return;
        break;
    case 0x140:
        menuCBBattleBABatuMark(arg1, 1, 5);
          return;
        break;
    case 0x141:
        menuCBBattleBABatuMark(arg1, 0, 0);
          return;
        break;
    case 0x142:
        menuCBBattleBABatuMark(arg1, 0, 1);
          return;
        break;
    case 0x143:
        menuCBBattleBABatuMark(arg1, 0, 2);
          return;
        break;
    case 0x144:
        menuCBBattleBABatuMark(arg1, 0, 3);
          return;
        break;
    case 0x145:
        menuCBBattleBABatuMark(arg1, 0, 4);
          return;
        break;
    case 0x146:
        menuCBBattleBABatuMark(arg1, 0, 5);
          return;
        break;
    case 0x148:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 3);
          return;
        break;
    case 0x147:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 2);
          return;
        break;
    case 0x149:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 1);
          return;
        break;
    case 0x14A:
        menuCBBattleStartDispTrainerFaceSub(arg0, arg1, 0);
          return;
        break;
    case 0x105:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 0);
          return;
        break;
    case 0x106:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 1);
          return;
        break;
    case 0x107:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 2);
          return;
        break;
    case 0x108:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 3);
          return;
        break;
    case 0x109:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 4);
          return;
        break;
    case 0x10A:
        menuCB_BattleBA_FacePanelSet(arg1, 0, 5);
          return;
        break;
    case 0x111:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 0);
          return;
        break;
    case 0x112:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 1);
          return;
        break;
    case 0x113:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 2);
          return;
        break;
    case 0x114:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 3);
          return;
        break;
    case 0x115:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 4);
          return;
        break;
    case 0x116:
        menuCB_BattleBA_FacePanelSet(arg1, 1, 5);
          return;
        break;
    case 0x11D:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 0);
          return;
        break;
    case 0x11E:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 1);
          return;
        break;
    case 0x11F:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 2);
          return;
        break;
    case 0x120:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 3);
          return;
        break;
    case 0x121:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 4);
          return;
        break;
    case 0x122:
        menuCB_BattleBA_FacePanelSet(arg1, 2, 5);
          return;
        break;
    case 0x129:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 0);
          return;
        break;
    case 0x12A:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 1);
          return;
        break;
    case 0x12B:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 2);
          return;
        break;
    case 0x12C:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 3);
          return;
        break;
    case 0x12D:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 4);
          return;
        break;
    case 0x12E:
        menuCB_BattleBA_FacePanelSet(arg1, 3, 5);
          return;
        break;
    case 0x1D4:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 0);
          return;
        break;
    case 0x1D5:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 1);
          return;
        break;
    case 0x1D6:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 2);
          return;
        break;
    case 0x1D7:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 3);
          return;
        break;
    case 0x1D8:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 4);
          return;
        break;
    case 0x1D9:
        menuCB_BattleBA_HPBarDispSet(arg1, 0, 5);
          return;
        break;
    case 0x1DA:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 0);
          return;
        break;
    case 0x1DB:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 1);
          return;
        break;
    case 0x1DC:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 2);
          return;
        break;
    case 0x1DD:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 3);
          return;
        break;
    case 0x1DE:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 4);
          return;
        break;
    case 0x1DF:
        menuCB_BattleBA_HPBarDispSet(arg1, 1, 5);
          return;
        break;
    case 0x1E0:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 0);
          return;
        break;
    case 0x1E1:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 1);
          return;
        break;
    case 0x1E2:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 2);
          return;
        break;
    case 0x1E3:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 3);
          return;
        break;
    case 0x1E4:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 4);
          return;
        break;
    case 0x1E5:
        menuCB_BattleBA_HPBarDispSet(arg1, 2, 5);
          return;
        break;
    case 0x1E6:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 0);
          return;
        break;
    case 0x1E7:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 1);
          return;
        break;
    case 0x1E8:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 2);
          return;
        break;
    case 0x1E9:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 3);
          return;
        break;
    case 0x1EA:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 4);
          return;
        break;
    case 0x1EB:
        menuCB_BattleBA_HPBarDispSet(arg1, 3, 5);
          return;
        break;
    case 0x2AA:
        menuCB_PrintXP(arg1, 0);
          return;
        break;
    case 0x2AB:
        menuCB_PrintXP(arg1, 1);
          return;
        break;
    case 0x2AC:
        menuCB_PrintXP(arg1, 2);
          return;
        break;
    case 0x2AD:
        menuCB_PrintXP(arg1, 3);
          return;
        break;
    default:
        return;
    }
}

void menuTool_BattleBA03_Button(MenuDBWindow *arg0) {
    if ((pauseIsPause() == 0) && (menuCBBattleBANextMenu(arg0) != 0) && ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0)) {
        arg0->unkA4 = 1;
    }
}

void menuTool_BattleBA03_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (((s32) _CB.unk4 == 0) && (menuCBBattleStartGetStatus() == 0) && (menuCB_GetDisconnectedGBA() != 0)) {
        _CB.unkB19C = 1;
        arg0->unkA4 = 1;
        arg0->unkA5 = 1;
    }
}

void menuTool_BattleBA01_Button(MenuDBWindow *arg0) {
    if ((pauseIsPause() == 0) && ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0)) {
        arg0->unkA4 = 1;
    }
}

void menuTool_BattleBA01_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuTool_GBAConnect_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuCB_error01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s16 temp_r31;
    s32 var_r30;

    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x4DC:
        winSpriteSetDisp(arg1, 0);
        temp_r31 = arg0->unk9E;
        if (temp_r31 >= 0) {
            var_r30 = 0;
            if (temp_r31 >= 7) {
                var_r30 = 0xA0;
            }
            menuSubDrawCursorBackAnimeOnOffAuto(arg0, winSpriteGetLayerID(arg0, arg1), var_r30, (arg0->unk9E % 7) << 5, arg1->unk54, arg1->unk56, arg0->unk93, 1);
        }
        return;
    case 0x4EC:
        menuCB_Trainer_Error_Disp(arg0, arg1, _CB.unkB008, 0);
        return;
    case 0x4EB:
        menuCB_Trainer_Error_Disp(arg0, arg1, _CB.unkB008, 1);
        return;
    case 0x4ED:
        arg1->unk4C = 0x43C3;
        break;
    }
}

void menuTool_error01_Button(MenuDBWindow *arg0) {
    _CB.unkB00C = (s32) arg0->unk9E;
    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            arg0->unkA4 = 1;
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            _CB.unkB08C = 1;
            arg0->unkA4 = 1;
            arg0->unkA5 = 1;
        }
    }
}

void menuTool_error01_Ctrl(MenuDBWindow *arg0) {
    s32 i;

    if ((s8) (u8) arg0->unk1 == 2) {
        for (i = 0; i <= (s32) _CB.unkB0E4; i++) {
            menuItemBiosSetSelectFlag(0xA7, _error01_cursol_item_tbl[i], 1);
        }
        for (; i < 0xE; i++) {
            menuItemBiosSetSelectFlag(0xA7, _error01_cursol_item_tbl[i], 0);
        }
    }
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_error00_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    switch (arg1->unk6) {
    case 0x5:
        menuCBPokemon_ErrorDispSet(arg1, 0);
        break;
    case 0x2DC:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0x4:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 0);
        break;
    case 0x12:
    case 0x13:
    case 0x14:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 0);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 0) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x2A:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 0, 1);
        break;
    case 0x2B:
        menuCBPokemonName(arg0, _CB.unkB0D8, 0, 1);
        break;
    case 0x38:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 0);
        break;
    case 0x24:
        menuCBPokemonItem_ErrorSet(arg1, 0);
        break;
    case 0x7:
        menuCBPokemon_ErrorDispSet(arg1, 1);
        break;
    case 0x2DD:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0x6:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 1);
        break;
    case 0x15:
    case 0x16:
    case 0x17:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 1);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 1) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x2C:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 1, 1);
        break;
    case 0x2D:
        menuCBPokemonName(arg0, _CB.unkB0D8, 1, 1);
        break;
    case 0xCB:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 1);
        break;
    case 0x26:
        menuCBPokemonItem_ErrorSet(arg1, 1);
        break;
    case 0x9:
        menuCBPokemon_ErrorDispSet(arg1, 2);
        break;
    case 0x2DE:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0x8:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 2);
        break;
    case 0x18:
    case 0x19:
    case 0x1A:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 2);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 2) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x2E:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 2, 1);
        break;
    case 0x2F:
        menuCBPokemonName(arg0, _CB.unkB0D8, 2, 1);
        break;
    case 0xCC:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 2);
        break;
    case 0x27:
        menuCBPokemonItem_ErrorSet(arg1, 2);
        break;
    case 0xB:
        menuCBPokemon_ErrorDispSet(arg1, 3);
        break;
    case 0x2DF:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0xA:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 3);
        break;
    case 0x1B:
    case 0x1C:
    case 0x1D:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 3);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 3) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x30:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 3, 1);
        break;
    case 0x31:
        menuCBPokemonName(arg0, _CB.unkB0D8, 3, 1);
        break;
    case 0xCD:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 3);
        break;
    case 0x28:
        menuCBPokemonItem_ErrorSet(arg1, 3);
        break;
    case 0xD:
        menuCBPokemon_ErrorDispSet(arg1, 4);
        break;
    case 0x2E0:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0xC:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 4);
        break;
    case 0x1E:
    case 0x1F:
    case 0x20:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 4);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 4) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x33:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 4, 1);
        break;
    case 0x34:
        menuCBPokemonName(arg0, _CB.unkB0D8, 4, 1);
        break;
    case 0xCE:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 4);
        break;
    case 0x32:
        menuCBPokemonItem_ErrorSet(arg1, 4);
        break;
    case 0xF:
        menuCBPokemon_ErrorDispSet(arg1, 5);
        break;
    case 0x2E1:
        winSpriteSetDisp(arg1, 0);
        break;
    case 0xE:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, _CB.unkB0D8, 5);
        break;
    case 0x21:
    case 0x22:
    case 0x23:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 5);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 5) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x35:
        menuCBPokemonLevel(arg0, _CB.unkB0D8, 5, 1);
        break;
    case 0x36:
        menuCBPokemonName(arg0, _CB.unkB0D8, 5, 1);
        break;
    case 0xCF:
        menuCBPokemonMaruWaku_ErrorSet(arg1, 5);
        break;
    case 0x29:
        menuCBPokemonItem_ErrorSet(arg1, 5);
        break;
    case 0x11:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkB008 == 6);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkB008) == 6) && (((u8) arg0->unkA4) == 0));
        break;
    case 0x25:
        if (windowSearchID(0xA7) != 0) {
            arg1->unk4C = 0;
            break;
        }
        fn_80080390(arg0, arg1, 0x43C2);
        break;
    case 0x10:
        menuCB_SpriteDispCheckONorOFF(arg1, windowSearchID(0xA7) == 0);
        break;
    case 0x37:
        arg1->unk4C = 0x43C1;
        break;
    }
}

void menuTool_error00_Button(MenuDBWindow *arg0) {
    u32 combinedKeys;
    u16 temp_r31;

    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            arg0->unkA4 = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            arg0->unkA4 = 1;
            _CB.unkB088 = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        if ((s32) _CB.unkB0DC != -1) {
            if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                if ((s32) _CB.unkB008 == 6) {
                    _CB.unkB008 = _CB.unkB0DC;
                    menuCB_SE_Play(0x10);
                    return;
                }
                if ((s32) _CB.unkB008 != 0) {
                    _CB.unkB008 -= 1;
                    menuCB_SE_Play(0x10);
                    return;
                }
                goto block_11;
            }
block_11:
            if (((s32) (windowGetKeyRepeat() & 2) != 0) && ((s32) _CB.unkB008 < (s32) _CB.unkB0DC)) {
                _CB.unkB008 += 1;
                menuCB_SE_Play(0x10);
                return;
            }
            temp_r31 = windowGetKeyInfo2()->unk4;
            combinedKeys = windowGetKeyInfo()->unk4;
        combinedKeys |= temp_r31;
        if ((s32) (combinedKeys & 0xC) != 0) {
                if ((s32) _CB.unkB008 == 6) {
                    _CB.unkB008 = 0;
                    menuCB_SE_Play(0x10);
                    return;
                }
                _CB.unkB008 = 6;
                menuCB_SE_Play(0x10);
            }
        } else {
            _CB.unkB008 = 6;
        }
    }
}

void menuTool_error00_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_AlphaGet(arg0);
}

void menuCB_Tunaide03_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x63D:
        arg1->unk4C = 0x440E;
        return;
    case 0x64A:
        fn_80080390(arg0, arg1, 0x435E);
        return;
    case 0x5FB:
    case 0x60D:
    case 0x61F:
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(0)]));
        return;
    case 0x5FC:
    case 0x616:
    case 0x628:
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(1)]));
        return;
    case 0x604:
    case 0x60E:
    case 0x629:
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(2)]));
        return;
    case 0x605:
    case 0x617:
    case 0x620:
        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Small_Face_Char[toolbattle_trainerFace(3)]));
        return;
    case 0x62D:
    case 0x62E:
    case 0x62F:
    case 0x630:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFEC == 0);
        return;
    case 0x631:
    case 0x632:
    case 0x633:
    case 0x634:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFEC == 1);
        return;
    case 0x635:
    case 0x636:
    case 0x637:
    case 0x638:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFEC == 2);
        return;
    case 0x639:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFEC == 3);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, 1);
        return;
    case 0x63E:
    case 0x642:
    case 0x646:
        toobattle_drawHeroName(arg0, 0);
        return;
    case 0x63F:
    case 0x644:
    case 0x648:
        toobattle_drawHeroName(arg0, 1);
        return;
    case 0x640:
    case 0x643:
    case 0x649:
        toobattle_drawHeroName(arg0, 2);
        return;
    case 0x641:
    case 0x645:
    case 0x647:
        toobattle_drawHeroName(arg0, 3);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_tunaide03_Button(MenuDBWindow *arg0) {
    u32 combinedKeys;
    u16 temp_r31;
    u16 temp_r31_2;

    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            arg0->unkA4 = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            arg0->unkA4 = 1;
            arg0->unkA5 = 1;
            _CB.unkB06C = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        temp_r31 = windowGetKeyInfo2()->unk4;
        combinedKeys = windowGetKeyInfo()->unk4;
        combinedKeys |= temp_r31;
        if ((s32) (combinedKeys & 3) != 0) {
            switch ((s32) _CB.unkAFEC) {            /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                _CB.unkAFEC = 2;
                break;
            case 1:                                 /* switch 1 */
                _CB.unkAFEC = 3;
                break;
            case 2:                                 /* switch 1 */
                _CB.unkAFEC = 0;
                break;
            case 3:                                 /* switch 1 */
                _CB.unkAFEC = 1;
                break;
            }
            menuCB_SE_Play(0x10);
        }
        temp_r31_2 = windowGetKeyInfo2()->unk4;
        combinedKeys = windowGetKeyInfo()->unk4;
        combinedKeys |= temp_r31_2;
        if ((s32) (combinedKeys & 0xC) != 0) {
            switch ((s32) _CB.unkAFEC) {            /* switch 2; irregular */
            case 0:                                 /* switch 2 */
                _CB.unkAFEC = 1;
                break;
            case 1:                                 /* switch 2 */
                _CB.unkAFEC = 0;
                break;
            case 2:                                 /* switch 2 */
                _CB.unkAFEC = 3;
                break;
            case 3:                                 /* switch 2 */
                _CB.unkAFEC = 2;
                break;
            }
            menuCB_SE_Play(0x10);
        }
    }
}

void menuTool_tunaide03_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (menuCB_GetDisconnectedGBA() != 0) {
        _CB.unkB198 = 1;
        arg0->unkA4 = 1;
        arg0->unkA5 = 1;
    }
    menuCB_AlphaGet(arg0);
}

void menuTool_tunaide02_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (menuCB_GetDisconnectedGBA() != 0) {
        _CB.unkB194 = 1;
        arg0->unkA4 = 1;
        arg0->unkA5 = 1;
    }
}

void menuCB_Tunaide01_4_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r3;
    s32 var_r4;
    s32 var_r4_10;
    s32 var_r4_11;
    s32 var_r4_12;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r4_6;
    s32 var_r4_7;
    s32 var_r4_8;
    s32 var_r4_9;

    temp_r3 = arg1->unk6;
    switch (temp_r3) {
    case 0x3DB:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 0)));
        return;
    case 0x3DC:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 1)));
        return;
    case 0x3DD:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 2)));
        return;
    case 0x3DE:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 3)));
        return;
    case 0x3DF:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 4)));
        return;
    case 0x3E0:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C == 1) && ((s32) _CB.unkB004 == 5)));
        return;
    case 0x3E1:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 0)));
        return;
    case 0x3E2:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 1)));
        return;
    case 0x3E3:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 2)));
        return;
    case 0x3E4:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 3)));
        return;
    case 0x3E5:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 4)));
        return;
    case 0x3E6:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unkB10C != 1) && ((s32) _CB.unkB004 == 5)));
        return;
    case 0x3E7:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 0);
        menuCB_RuleMessageTblDisp(arg0, arg1, 0);
        return;
    case 0x3E8:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 1);
        menuCB_RuleMessageTblDisp(arg0, arg1, 1);
        return;
    case 0x3E9:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 2);
        menuCB_RuleMessageTblDisp(arg0, arg1, 2);
        return;
    case 0x3EA:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 3);
        menuCB_RuleMessageTblDisp(arg0, arg1, 3);
        return;
    case 0x3EB:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 4);
        menuCB_RuleMessageTblDisp(arg0, arg1, 4);
        return;
    case 0x3EC:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkB004 == 5);
        menuCB_RuleMessageTblDisp(arg0, arg1, 5);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_tunaide01_4_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide01_4_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(arg0, 3);
}

void menuTool_tunaide01_3_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide01_3_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(arg0, 2);
}

void menuCB_Tunaide01_2_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0x29A:
    case 0x29B:
    case 0x29C:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF8 == 0);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF8 == 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
          return;
          return;
          _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 0);
          return;
          _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 1);
        break;
    case 0x29D:
    case 0x29E:
    case 0x29F:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF8 == 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
          return;
          return;
          _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 0);
          return;
          _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 1);
        break;
    case 0x679:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 0);
          return;
          _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 1);
        break;
    case 0x2A0:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF8 == 1);
        break;
    default:
        return;
    }
}

void menuTool_tunaide01_2_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide01_2_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(arg0, 1);
}

void menuCB_Tunaide01_1_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r3;

    temp_r3 = arg1->unk6;
    switch (temp_r3) {
    case 0x3CF:
    case 0x3D0:
    case 0x3D1:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF4 == 0);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
        return;
    case 0x3D2:
    case 0x3D3:
    case 0x3D4:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF4 == 1);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
        return;
    case 0x3D5:
    case 0x3D6:
    case 0x3D7:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF4 == 2);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
        return;
    case 0x3D8:
    case 0x3D9:
    case 0x3DA:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFF4 == 3);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
        return;
    case 0x3BF:
    case 0x3CC:
    case 0x3CE:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF4 == 0);
        return;
    case 0x3C0:
    case 0x3C3:
    case 0x3C4:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF4 == 1);
        return;
    case 0x3C1:
    case 0x3C5:
    case 0x3C6:
    case 0x3C7:
    case 0x3CD:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF4 == 2);
        return;
    case 0x3C2:
    case 0x3C8:
    case 0x3C9:
    case 0x3CA:
    case 0x3CB:
        _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(arg1, _CB.unkAFF4 == 3);
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_tunaide01_1_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide01_1_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_MenuDispCheckONorOFF_TUNAIDESUB(arg0, 0);
}

void menuTool_tunaide_back_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_Tunaide01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 var_r5;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    switch (arg1->unk6) {
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
    case 0x47:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 0);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 0);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 0) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x48:
    case 0x49:
    case 0x4A:
    case 0x4B:
    case 0x4C:
        _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 0);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 0);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 0) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x4D:
    case 0x4E:
    case 0x4F:
        _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 0);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 0) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5A:
        _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x5B:
    case 0x5C:
    case 0x5D:
        _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 1) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x5E:
    case 0x5F:
    case 0x60:
    case 0x61:
    case 0x62:
    case 0x63:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x64:
    case 0x65:
    case 0x66:
    case 0x67:
    case 0x68:
        _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x69:
    case 0x6A:
    case 0x6B:
        _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 2) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x6C:
    case 0x6D:
    case 0x6E:
    case 0x6F:
    case 0x70:
    case 0x71:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
    case 0x76:
        _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
          _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x77:
    case 0x78:
    case 0x79:
        _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 3);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 3) && (((s32) _CB.unkB10C) == 0));
          return;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x7C:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x7A:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
          menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 4);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 4) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x7D:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFE4 == 5);
          menuCB_Cursol_Disp_AlphaSet(arg0, arg1, (((s32) _CB.unkAFE4) == 5) && (((s32) _CB.unkB064) == 0));
          return;
        break;
    case 0x7B:
        _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 5);
        break;
    case 0x7E:
        arg1->unk4C = 0x4365;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
          return;
        break;
    case 0x68B:
        arg1->unk4C = lbl_802EB774[_CB.unkAFF4];
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
          return;
        break;
    case 0x7F:
        arg1->unk4C = 0x436E;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
        break;
    case 0x80:
        arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE01_BATTLE_A_Tbl[_CB.unkAFF8];
          if (((s32) _CB.unkAFF4) >= 2)
          {
            arg1->unk4C = 0x440F;
          }
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
          return;
        break;
    case 0x81:
        arg1->unk4C = 0x4373;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
        break;
    case 0x82:
        arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE01_FIELD_A_Tbl[_CB.unkAFFC];
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 2);
          return;
        break;
    case 0x83:
        arg1->unk4C = 0x4386;
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
        break;
    case 0x84:
        if (((s32) _CB.unkB004) >= 3)
          {
            arg1->unk4C = 0;
            menuCBRULE_EditNameDisp(arg0, arg1, _CB.unkB004);
          }
          else
          {
            arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE01_RULE_A_Tbl[_CB.unkB004];
          }
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 3);
          return;
        break;
    case 0x85:
        fn_80080390(arg0, arg1, 0x435E);
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 4);
          return;
        break;
    case 0x86:
        fn_80080390(arg0, arg1, 0x435F);
          _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 5);
          return;
        break;
    default:
        return;
    }
}

void _menuCB_tunaide01_disp_sub3__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    if ((s32) _CB.unkAFE4 != arg1) {
        _menuCB_tunaide01_disp_sub_color__FP14tagSPRITE_WORKUc(arg0, 0x7FU);
    }
}

void _menuCB_tunaide01_disp_sub2__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    _menuCB_tunaide01_disp_sub__FP14tagSPRITE_WORKScUc(arg0, arg1, 0xFFU);
}

void _menuCB_tunaide01_disp_sub1__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    _menuCB_tunaide01_disp_sub__FP14tagSPRITE_WORKScUc(arg0, arg1, 0xFFU);
}

void _menuCB_tunaide01_disp_sub__FP14tagSPRITE_WORKScUc(MenuDBSprite *arg0, s8 arg1, u8 arg2) {
    if ((s32) _CB.unkAFE4 == arg1) {
        winSpriteSetDisp(arg0, 1);
        _menuCB_tunaide01_disp_sub_color__FP14tagSPRITE_WORKUc(arg0, arg2);
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void _menuCB_tunaide01_disp_sub_color2__FP14tagSPRITE_WORKb(MenuDBSprite *arg0, s32 arg1) {
    if (((s32) _CB.unkB10C != 1) && ((u8) arg1 == 0)) {
        arg0->unk66 = 0x7F;
        arg0->unk65 = 0x7F;
        arg0->unk64 = 0x7F;
        return;
    }
    arg0->unk66 = 0xFF;
    arg0->unk65 = 0xFF;
    arg0->unk64 = 0xFF;
}

void _menuCB_tunaide01_disp_sub_color__FP14tagSPRITE_WORKUc(MenuDBSprite *arg0, u8 arg1) {
    if ((s32) _CB.unkB10C != 0) {
        arg0->unk66 = arg1;
        arg0->unk65 = arg1;
        arg0->unk64 = arg1;
        return;
    }
    arg0->unk66 = 0xFF;
    arg0->unk65 = 0xFF;
    arg0->unk64 = 0xFF;
}

void menuTool_tunaide01_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide01_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    systemUpdate__4CAntFb(1U);
    menuCB_AlphaGet(arg0);
}

void menuCB_Tunaide00_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {

    switch (arg1->unk6) {
    case 0x41:
        arg1->unk4C = 0x435C;
          return;
        break;
    case 0x3F:
        arg1->unk4C = 0x435D;
          return;
        break;
    case 0x40:
        if (((s32) _CB.unkB10C) == 0)
          {
            arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_Tbl[_CB.unkAFE4];
            return;
          }
          switch ((s32) _CB.unkAFE4)
          {
            case 0:
              arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_1_Tbl[_CB.unkAFF4];
              return;

            case 1:
              arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_2_Tbl[_CB.unkAFF8];
              return;

            case 2:
              arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_3_Tbl[_CB.unkAFFC];
              return;

            case 3:
              arg1->unk4C = MENU_ITEM_TOOL_TUNAIDE00_SETUMEI_4_Tbl[_CB.unkB004];
              break;

          }
        break;
    }
}

void menuTool_tunaide00_Button(MenuDBWindow *arg0) {
    // The original callback contains only blr.
}

void menuTool_tunaide00_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (((s32) _CB.unkB114 == 0) && ((s32) _CB.unkB10C < 2) && (pauseIsPause() == 0)) {
        if ((s32) _CB.unkB144 != -1) {
            if ((s32) _CB.unkB14C == 0xFF) {
                _CB.unkB144 = -1;
                goto block_8;
            }
            _CB.unkB148 -= 0x28;
            _CB.unkB14C += 0x28;
            if ((s32) _CB.unkB14C >= 0xFF) {
                _CB.unkB14C = 0xFF;
                _CB.unkB148 = 0xF;
            }
        } else {
block_8:
            if ((s32) _CB.unkB10C == 1) {
                switch ((s32) _CB.unkAFE4) {        /* switch 1; irregular */
                case 0:                             /* switch 1 */
                    if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                        if ((s32) _CB.unkAFF4 != 0) {
                            _CB.unkAFF4 -= 1;
                        } else {
                            _CB.unkAFF4 = 3;
                        }
                        menuCB_SE_Play(0x10);
                    } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                        if ((s32) _CB.unkAFF4 != 3) {
                            _CB.unkAFF4 += 1;
                        } else {
                            _CB.unkAFF4 = 0;
                        }
                        menuCB_SE_Play(0x10);
                    }
                    break;
                case 1:                             /* switch 1 */
                    if ((s32) (windowGetKeyRepeat() & 3) != 0) {
                        _CB.unkAFF8 ^= 1;
                        menuCB_SE_Play(0x10);
                    }
                    break;
                case 2:                             /* switch 1 */
                    if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                        _CB.unkB000 = _CB.unkAFFC;
                        if ((s32) _CB.unkAFFC != 0) {
                            _CB.unkAFFC -= 1;
                        }
                        if ((s32) _CB.unkB000 != (s32) _CB.unkAFFC) {
                            _CB.unkB114 = 1;
                            menuCB_SE_Play(0x10);
                        }
                    }
                    if (((s32) (windowGetKeyRepeat() & 2) != 0) && ((s32) _CB.unkB114 == 0)) {
                        _CB.unkB000 = _CB.unkAFFC;
                        if ((s32) _CB.unkAFFC != 6) {
                            _CB.unkAFFC += 1;
                        }
                        if ((s32) _CB.unkB000 != (s32) _CB.unkAFFC) {
                            _CB.unkB114 = 3;
                            menuCB_SE_Play(0x10);
                        }
                    }
                    break;
                case 3:                             /* switch 1 */
                    if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                        if ((s32) _CB.unkB004 != 0) {
                            _CB.unkB004 -= 1;
                        } else {
                            _CB.unkB004 = 5;
                        }
                        menuCB_SE_Play(0x10);
                    } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                        if ((s32) _CB.unkB004 != 5) {
                            _CB.unkB004 += 1;
                        } else {
                            _CB.unkB004 = 0;
                        }
                        menuCB_SE_Play(0x10);
                    }
                    break;
                }
                if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                    menuCB_SE_Play(0x11);
                    if ((s32) _CB.unkAFE4 == 3) {
                        _CB.unkB10C = 2;
                        return;
                    }
                    _CB.unkB10C = 0;
                    return;
                }
                if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                    menuCB_SE_Play(0x12);
                    switch ((s32) _CB.unkAFE4) {    /* switch 2; irregular */
                    case 0:                         /* switch 2 */
                        _CB.unkAFF4 = _CB.unkB074;
                        break;
                    case 1:                         /* switch 2 */
                        _CB.unkAFF8 = _CB.unkB078;
                        break;
                    case 2:                         /* switch 2 */
                        _CB.unkAFFC = _CB.unkB07C;
                        break;
                    case 3:                         /* switch 2 */
                        _CB.unkB004 = _CB.unkB084;
                        break;
                    }
                    _CB.unkB10C = 0;
                }
            } else if ((s32) _CB.unkB064 == 0) {
                if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                    menuCB_SE_Play(0x12);
                    _CB.unkB064 = 2;
                    return;
                }
                if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                    menuCB_SE_Play(0x11);
                    switch ((s32) _CB.unkAFE4) {    /* switch 3; irregular */
                    case 4:                         /* switch 3 */
                        _CB.unkB064 = 2;
                        return;
                    case 5:                         /* switch 3 */
                        _CB.unkB064 = 1;
                        return;
                    case 0:                         /* switch 3 */
                        _CB.unkB074 = _CB.unkAFF4;
                    default:                        /* switch 3 */
block_86:
                        _CB.unkB10C = 1;
                        return;
                    case 1:                         /* switch 3 */
                        _CB.unkB078 = _CB.unkAFF8;
                        goto block_86;
                    case 2:                         /* switch 3 */
                        _CB.unkB07C = _CB.unkAFFC;
                        goto block_86;
                    case 3:                         /* switch 3 */
                        _CB.unkB084 = _CB.unkB004;
                        goto block_86;
                    }
                } else if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                    _menuCB_TunaideSub_Page_Chenge_Init__Fv();
                    if ((s32) _CB.unkAFE4 == 0) {
                        _CB.unkAFE4 = 5;
                    } else {
                        _CB.unkAFE4 -= 1;
                    }
                    if (((s32) _CB.unkAFE4 == 1) && ((s32) _CB.unkAFF4 >= 2)) {
                        _CB.unkAFE4 = 0;
                    }
                } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                    _menuCB_TunaideSub_Page_Chenge_Init__Fv();
                    if ((s32) _CB.unkAFE4 == 5) {
                        _CB.unkAFE4 = 0;
                    } else {
                        _CB.unkAFE4 += 1;
                    }
                    if (((s32) _CB.unkAFE4 == 1) && ((s32) _CB.unkAFF4 >= 2)) {
                        _CB.unkAFE4 = 2;
                    }
                } else if ((s32) (windowGetKeyRepeat() & 8) != 0) {
                    _menuCB_TunaideSub_Page_Chenge_Init__Fv();
                    switch ((s32) _CB.unkAFE4) {    /* switch 4; irregular */
                    default:                        /* switch 4 */
                        _CB.unkAFE4 = 4;
                        return;
                    case 4:                         /* switch 4 */
                        _CB.unkAFE4 = 5;
                        return;
                    case 5:                         /* switch 4 */
                        _CB.unkAFE4 = 0;
                        return;
                    }
                } else if ((s32) (windowGetKeyRepeat() & 4) != 0) {
                    _menuCB_TunaideSub_Page_Chenge_Init__Fv();
                    switch ((s32) _CB.unkAFE4) {    /* switch 5; irregular */
                    default:                        /* switch 5 */
                        _CB.unkAFE4 = 5;
                        return;
                    case 4:                         /* switch 5 */
                        _CB.unkAFE4 = 0;
                        return;
                    case 5:                         /* switch 5 */
                        _CB.unkAFE4 = 4;
                        break;
                    }
                }
            }
        }
    }
}

void _menuCB_TunaideSub_Page_Chenge_Init__Fv(void) {
    volatile MenuDBState *state = &_CB;
    state->unkB144 = state->unkAFE4;
    state->unkB148 = 0xFF;
    state->unkB14C = 0xF;
    menuCB_SE_Play(0x10);
}

void menuCB_Imasugu02_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r31;
    s16 temp_r5;

    temp_r5 = arg1->unk6;
    switch (temp_r5) {
    case 0x512:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFD4 != 0);
        return;
    case 0x511:
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFD4 == 0);
        return;
    case 0x529:
        arg1->unk4C = 0x43B4;
        return;
    case 0x527:
        arg1->unk4C = 0x426C;
        return;
    case 0x526:
        arg1->unk4C = 0x426D;
        return;
    case 0x528:
        arg1->unk4C = 0x43C0;
        return;
    case 0x4FC:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, 0, 0);
        return;
    case 0x4FD:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, 0, 1);
        return;
    case 0x4FE:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, 1, 0);
        return;
    case 0x4FF:
        menuCBPokemonEntryDispPokemonFace(arg0, arg1, 1, 1);
        return;
    case 0x516:
        menuCBPokemonName(arg0, 0, 0, 1);
        return;
    case 0x517:
        menuCBPokemonLevel(arg0, 0, 0, 1);
        return;
    case 0x518:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId(0, 0));
        return;
    case 0x519:
        menuCBPokemonHP(arg0, 0, 0, 1);
        return;
    case 0x51A:
        menuCBPokemonName(arg0, 0, 1, 1);
        return;
    case 0x51B:
        menuCBPokemonLevel(arg0, 0, 1, 1);
        return;
    case 0x51C:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId(0, 1));
        return;
    case 0x51D:
        menuCBPokemonHP(arg0, 0, 1, 1);
        return;
    case 0x51E:
        menuCBPokemonName(arg0, 1, 0, 1);
        return;
    case 0x51F:
        menuCBPokemonLevel(arg0, 1, 0, 1);
        return;
    case 0x520:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId(1, 0));
        return;
    case 0x521:
        menuCBPokemonHP(arg0, 1, 0, 1);
        return;
    case 0x522:
        menuCBPokemonName(arg0, 1, 1, 1);
        return;
    case 0x523:
        menuCBPokemonLevel(arg0, 1, 1, 1);
        return;
    case 0x524:
        menuCB_SpriteDispCheckONorOFF(arg1, menuCBPokemonGetItemDataId(1, 1));
        return;
    case 0x525:
        menuCBPokemonHP(arg0, 1, 1, 1);
        return;
    case 0x513:
        winSpriteSetDisp(arg1, 0);
        temp_r31 = arg0->unk9E;
        if (temp_r31 >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(arg0, winSpriteGetLayerID(arg0, arg1), 0, temp_r31 * 0x25, arg1->unk54, arg1->unk56, arg0->unk93, 0);
        }
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_imasugu02_Button(MenuDBWindow *arg0) {
    _CB.unkAFDC = (s32) arg0->unk9E;
    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            arg0->unkA4 = 1;
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            arg0->unkA4 = 1;
            arg0->unkA5 = 1;
            _CB.unkB05C = 1;
        }
    }
}

void menuTool_imasugu02_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_Imasugu01_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s16 temp_r31;

    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x537:
        arg1->unk4C = 0;
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, 0x43BBU);
        GSmsgPrint2(arg0->unk1C, 0, 0x25, arg0->unk93 | ~0xFF, 0x43BCU);
        GSmsgPrint2(arg0->unk1C, 0, 0x4A, arg0->unk93 | ~0xFF, 0x43BDU);
        GSmsgPrint2(arg0->unk1C, 0, 0x6F, arg0->unk93 | ~0xFF, 0x43BEU);
        GSmsgPrint2(arg0->unk1C, 0, 0x94, arg0->unk93 | ~0xFF, 0x43BFU);
        return;
    case 0x531:
        winSpriteSetDisp(arg1, 0);
        temp_r31 = arg0->unk9E;
        if (temp_r31 >= 0) {
            menuSubDrawCursorBackAnimeOnOffAuto(arg0, winSpriteGetLayerID(arg0, arg1), 0, temp_r31 * 0x25, arg1->unk54, arg1->unk56, arg0->unk93, 1);
        }
        return;
    }
}

void menuTool_imasugu01_Button(MenuDBWindow *arg0) {
    _CB.unkAFD8 = (s32) arg0->unk9E;
    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            arg0->unkA4 = 1;
            menuCBPokemonEntryPokemonFaceFree();
            if ((s32) _CB.unkAFD4 == 1) {
                if (GSinputIsConnected(2) != 0) {
                    _CB.unkB0E0 = 2;
                    return;
                }
                _CB.unkB0E0 = 1;
                return;
            }
            _CB.unkB0E0 = 0;
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            arg0->unkA4 = 1;
            arg0->unkA5 = 1;
            _CB.unkB058 = 1;
        }
    }
}

void menuTool_imasugu01_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
}

void menuCB_Imasugu00_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r3;

    temp_r3 = arg1->unk6;
    switch (temp_r3) {
    case 0x64E:
    case 0x64F:
    case 0x650:
    case 0x651:
    case 0x652:
    case 0x653:
    case 0x654:
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
        return;
    case 0x65C:
    case 0x65D:
    case 0x65E:
    case 0x65F:
    case 0x660:
        _menuCB_imasugu00_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 0);
        return;
    case 0x666:
    case 0x667:
    case 0x668:
        _menuCB_imasugu00_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 0);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, windowSearchID(0x106) == 0);
        return;
    case 0x655:
    case 0x656:
    case 0x657:
    case 0x658:
    case 0x659:
    case 0x65A:
    case 0x65B:
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
        return;
    case 0x661:
    case 0x662:
    case 0x663:
    case 0x664:
    case 0x665:
        _menuCB_imasugu00_disp_sub2__FP14tagSPRITE_WORKSc(arg1, 1);
        return;
    case 0x669:
    case 0x66A:
    case 0x66B:
        _menuCB_imasugu00_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 1);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, windowSearchID(0x106) == 0);
        return;
    case 0x671:
        arg1->unk4C = 0x43B4;
        return;
    case 0x673:
        if (windowSearchID(0x106) != 0) {
            arg1->unk4C = 0x43BA;
            return;
        }
        arg1->unk4C = 0x43B5;
        return;
    case 0x674:
        arg1->unk4C = 0x43B6;
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
        return;
    case 0x675:
        arg1->unk4C = 0x43B7;
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
        return;
    case 0x672:
        if (windowSearchID(0x106) != 0) {
            arg1->unk4C = MENU_ITEM_TOOL_IMASUGU01_SETUMEI_Tbl[_CB.unkAFD8];
            return;
        }
        arg1->unk4C = MENU_ITEM_TOOL_IMASUGU00_SETUMEI_Tbl[_CB.unkAFD4];
        return;
    case 0x676:
        if (windowSearchID(0x106) != 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        return;
    case 0x677:
        if (windowSearchID(0x106) != 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        _menuCB_imasugu00_disp_sub1__FP14tagSPRITE_WORKSc(arg1, 2);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, 1);
        return;
    case 0x678:
        if (windowSearchID(0x106) != 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        fn_80080390(arg0, arg1, 0x435E);
        return;
    case 0x66D:
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 0);
        return;
    case 0x66C:
        _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(arg1, 1);
        /* fallthrough */
    default:
        return;
    }
}

void _menuCB_imasugu00_disp_sub3__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    if ((s32) _CB.unkAFD4 != arg1) {
        _menuCB_imasugu00_disp_sub_color__FP14tagSPRITE_WORKUc(arg0, 0x7FU);
    }
}

void _menuCB_imasugu00_disp_sub2__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    _menuCB_imasugu00_disp_sub__FP14tagSPRITE_WORKScUc(arg0, arg1, 0xFFU);
}

void _menuCB_imasugu00_disp_sub1__FP14tagSPRITE_WORKSc(MenuDBSprite *arg0, s8 arg1) {
    _menuCB_imasugu00_disp_sub__FP14tagSPRITE_WORKScUc(arg0, arg1, 0x7FU);
}

void _menuCB_imasugu00_disp_sub__FP14tagSPRITE_WORKScUc(MenuDBSprite *arg0, s8 arg1, u8 arg2) {
    if ((s32) _CB.unkAFD4 == arg1) {
        winSpriteSetDisp(arg0, 1);
        _menuCB_imasugu00_disp_sub_color__FP14tagSPRITE_WORKUc(arg0, arg2);
        return;
    }
    winSpriteSetDisp(arg0, 0);
}

void _menuCB_imasugu00_disp_sub_color__FP14tagSPRITE_WORKUc(MenuDBSprite *arg0, u8 arg1) {
    if (windowSearchID(0x106) != 0) {
        arg0->unk66 = arg1;
        arg0->unk65 = arg1;
        arg0->unk64 = arg1;
        return;
    }
    arg0->unk66 = 0xFF;
    arg0->unk65 = 0xFF;
    arg0->unk64 = 0xFF;
}

void menuTool_imasugu00_Button(MenuDBWindow *arg0) {
    u32 combinedKeys;
    u16 temp_r31;

    if (pauseIsPause() == 0) {
        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
            if ((s32) _CB.unkAFD4 == 2) {
                _CB.unkB054 = 1;
            }
            arg0->unkA4 = 1;
            menuCB_SE_Play(0x11);
            return;
        }
        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
            arg0->unkA4 = 1;
            _CB.unkB054 = 1;
            menuCB_SE_Play(0x12);
            return;
        }
        if ((s32) (windowGetKeyRepeat() & 1) != 0) {
            if ((s32) _CB.unkAFD4 == 0) {
                _CB.unkAFD4 = 2;
            } else {
                _CB.unkAFD4 -= 1;
            }
            menuCB_SE_Play(0x10);
            return;
        }
        if ((s32) (windowGetKeyRepeat() & 2) != 0) {
            if ((s32) _CB.unkAFD4 == 2) {
                _CB.unkAFD4 = 0;
            } else {
                _CB.unkAFD4 += 1;
            }
            menuCB_SE_Play(0x10);
            return;
        }
        temp_r31 = windowGetKeyInfo2()->unk4;
        combinedKeys = windowGetKeyInfo()->unk4;
        combinedKeys |= temp_r31;
        if ((s32) (combinedKeys & 0xC) != 0) {
            switch ((s32) _CB.unkAFD4) {            /* irregular */
            case 0:
                _CB.unkAFD4 = 2;
                break;
            case 1:
                _CB.unkAFD4 = 2;
                break;
            case 2:
                _CB.unkAFD4 = 0;
                break;
            }
            menuCB_SE_Play(0x10);
        }
    }
}

void menuTool_imasugu00_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    menuCB_AlphaGet(arg0);
}

void menuCB_tunaidePokemonSelect1_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    u32 var_r7;
    MenuDBEntry *temp_r3;

    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x4B7:
        if ((s16) pGCB->entries[pGCB->selected].unk4 == 0) {
            msgctrlSetValue(0x2F, pGCB->entries[pGCB->selected].unk2);
            var_r7 = 0x443B;
        } else {
            var_r7 = 0x43B3;
        }
        GSmsgPrint2(arg0->unk1C, 0, 0, arg0->unk93 | ~0xFF, var_r7);
        return;
    case 0x4B4:
        arg1->unk4C = 0x43FB;
        menuCBPokemonEntryDisp(arg1);
        return;
    case 0x4B5:
        arg1->unk4C = 0x43FA;
        menuCBPokemonEntryDisp(arg1);
        if ((s16) pGCB->entries[pGCB->selected].unk4 == 0) {
            winSpriteSetDisp(arg1, 0);
        }
        return;
    case 0x4B6:
        arg1->unk4C = 0x43FC;
        menuCBPokemonEntryDisp(arg1);
        return;
    case 0x3F4:
    case 0x3F5:
    case 0x3F6:
    case 0x3F8:
    case 0x3F9:
        menuCBPokemonEntryDisp(arg1);
        return;
    case 0x3F7:
        menuCBPokemonEntryDisp(arg1);
        if ((s16) pGCB->entries[pGCB->selected].unk4 == 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        break;
    case 0x4B3:
        menuCBPokemonEntryGCControlDisp(arg1, 0);
        return;
    case 0x4B2:
        menuCBPokemonEntryGCControlDisp(arg1, 1);
        return;
    case 0x4B1:
        menuCBPokemonEntryGCControlDisp(arg1, 2);
        return;
    case 0x4B0:
        menuCBPokemonEntryGCControlDisp(arg1, 3);
        return;
    case 0x4AF:
        menuCBPokemonEntryGCControlDisp(arg1, 4);
        return;
    case 0x4AE:
        menuCBPokemonEntryGCControlDisp(arg1, 5);
        break;
    }
}

void menuCB_tunaideGCEntry_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s32 entryType;
    s16 temp_r3;
    s32 temp_r28;
    s32 temp_r31;
    s32 var_r5;
    s32 var_r5_10;
    s32 var_r5_11;
    s32 var_r5_12;
    s32 var_r5_13;
    s32 var_r5_14;
    s32 var_r5_15;
    s32 var_r5_16;
    s32 var_r5_17;
    s32 var_r5_18;
    s32 var_r5_19;
    s32 var_r5_20;
    s32 var_r5_21;
    s32 var_r5_22;
    s32 var_r5_23;
    s32 var_r5_24;
    s32 var_r5_25;
    s32 var_r5_26;
    s32 var_r5_27;
    s32 var_r5_28;
    s32 var_r5_29;
    s32 var_r5_2;
    s32 var_r5_30;
    s32 var_r5_31;
    s32 var_r5_32;
    s32 var_r5_33;
    s32 var_r5_34;
    s32 var_r5_35;
    s32 var_r5_36;
    s32 var_r5_37;
    s32 var_r5_38;
    s32 var_r5_39;
    s32 var_r5_3;
    s32 var_r5_40;
    s32 var_r5_41;
    s32 var_r5_42;
    s32 var_r5_43;
    s32 var_r5_44;
    s32 var_r5_45;
    s32 var_r5_46;
    s32 var_r5_47;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r5_7;
    s32 var_r5_8;
    s32 var_r5_9;

    temp_r31 = _CB.unkB0F8;
    if (((s32) _CB.unkB0F4 == 1) || ((s32) _CB.unkB150 != 0)) {
        winSpriteSetDisp(arg1, 0);
        return;
    }
    switch ((s32) _CB.unkB0F0) {                    /* switch 1; irregular */
    case 0:
        entryType = 0;
        break;
    case 1:                                         /* switch 1 */
        entryType = 1;
        break;
    case 2:                                         /* switch 1 */
        temp_r28 = _CB.unkB0EC;
        entryType = 2 + getDancerQuantity__12CReliveStageFv(getStage__11CReliveHallFl(getPointer__11CReliveHallFv(), temp_r28));
        break;
    }
    temp_r3 = arg1->unk6;
    switch (temp_r3) {                              /* switch 2 */
    case 0x21F:                                     /* switch 2 */
        menuCB_SpriteDispCheckONorOFF(arg1, temp_r31 == 0x24);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, 1);
        return;
    case 0x220:                                     /* switch 2 */
        menuCB_SpriteDispCheckONorOFF(arg1, temp_r31 == 0x25);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, 1);
        return;
    case 0x221:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x1E);
        return;
    case 0x222:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x1F);
        return;
    case 0x223:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x20);
        return;
    case 0x224:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x21);
        return;
    case 0x225:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x22);
        return;
    case 0x226:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, temp_r31 == 0x23);
        return;
    case 0x227:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType >= 2) && ((s32) entryType <= 6) && (temp_r31 == 4)));
        return;
    case 0x228:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 3) && (temp_r31 == 0)));
        return;
    case 0x229:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 4) && (temp_r31 == 0)));
        return;
    case 0x22A:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 4) && (temp_r31 == 1)));
        return;
    case 0x22B:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 5) && (temp_r31 == 0)));
        return;
    case 0x22D:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 5) && (temp_r31 == 1)));
        return;
    case 0x22C:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 5) && (temp_r31 == 2)));
        return;
    case 0x230:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 6) && (temp_r31 == 0)));
        return;
    case 0x231:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 6) && (temp_r31 == 1)));
        return;
    case 0x22E:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 6) && (temp_r31 == 2)));
        return;
    case 0x22F:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 6) && (temp_r31 == 3)));
        return;
    case 0x232:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 0)));
        return;
    case 0x233:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 1)));
        return;
    case 0x234:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 2)));
        return;
    case 0x235:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 3)));
        return;
    case 0x236:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 4)));
        return;
    case 0x237:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 0) && (temp_r31 == 5)));
        return;
    case 0x238:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0)));
        return;
    case 0x239:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 1)));
        return;
    case 0x23A:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 2)));
        return;
    case 0x23B:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 3)));
        return;
    case 0x23C:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 4)));
        return;
    case 0x23D:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 5)));
        return;
    case 0x23E:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 6)));
        return;
    case 0x23F:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 7)));
        return;
    case 0x240:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 8)));
        return;
    case 0x241:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 9)));
        return;
    case 0x242:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xA)));
        return;
    case 0x243:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xB)));
        return;
    case 0x244:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xC)));
        return;
    case 0x245:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xD)));
        return;
    case 0x246:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xE)));
        return;
    case 0x247:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0xF)));
        return;
    case 0x248:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x10)));
        return;
    case 0x249:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x11)));
        return;
    case 0x24A:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x12)));
        return;
    case 0x24B:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x13)));
        return;
    case 0x24C:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x14)));
        return;
    case 0x24D:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x15)));
        return;
    case 0x24E:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x16)));
        return;
    case 0x24F:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x17)));
        return;
    case 0x250:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x18)));
        return;
    case 0x251:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x19)));
        return;
    case 0x252:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x1A)));
        return;
    case 0x253:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x1B)));
        return;
    case 0x254:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x1C)));
        return;
    case 0x255:                                     /* switch 2 */
        menuCB_GCEntryCursolDisp(arg0, arg1, (((s32) entryType == 1) && (temp_r31 == 0x1D)));
        /* fallthrough */
    default:                                        /* switch 2 */
        return;
    }
}

void menuCB_GBAConnect_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r3;
    s32 var_r4;
    s32 var_r4_10;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_5;
    s32 var_r4_6;
    s32 var_r4_7;
    s32 var_r4_8;
    s32 var_r4_9;

    temp_r3 = arg1->unk6;
    switch (temp_r3) {
    case 0xF1:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) gbaConectGBA_Connect_WORK.unk0 == 0xA) || ((s32) gbaConectGBA_Connect_WORK.unk0 == 5)));
        return;
    case 0xF2:
        menuCB_SpriteDispCheckONorOFF(arg1, gbaConectGBA_Connect_WORK.unk4 == 5);
        return;
    case 0xF3:
        menuCB_SpriteDispCheckONorOFF(arg1, gbaConectGBA_Connect_WORK.unk8 == 5);
        return;
    case 0xF4:
        menuCB_SpriteDispCheckONorOFF(arg1, gbaConectGBA_Connect_WORK.unkC == 5);
        return;
    case 0xF5:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) gbaConectGBA_Connect_WORK.unk0 == 0xB) || ((s32) gbaConectGBA_Connect_WORK.unk0 == 6) || ((s32) gbaConectGBA_Connect_WORK.unk0 == 7)));
        return;
    case 0xF6:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) gbaConectGBA_Connect_WORK.unk4 == 6) || ((s32) gbaConectGBA_Connect_WORK.unk4 == 7)));
        return;
    case 0xF7:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) gbaConectGBA_Connect_WORK.unk8 == 6) || ((s32) gbaConectGBA_Connect_WORK.unk8 == 7)));
        return;
    case 0xF8:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) gbaConectGBA_Connect_WORK.unkC == 6) || ((s32) gbaConectGBA_Connect_WORK.unkC == 7)));
        return;
    case 0xDE:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s8) gbaConectGBA_Connect_WORK.unk30 != 1) && ((s8) gbaConectGBA_Connect_WORK.unk30 != 4)));
        return;
    case 0xE2:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s8) gbaConectGBA_Connect_WORK.unk30 != 1) && ((s8) gbaConectGBA_Connect_WORK.unk30 != 4)));
        return;
    case 0xE6:
        if (((s8) gbaConectGBA_Connect_WORK.unk30 == 1) || ((s8) gbaConectGBA_Connect_WORK.unk30 == 4)) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        if ((u8) gbaConectGBA_Connect_WORK.unk48 != 0) {
            gbaConectGBA_Connect_WORK.unk34 = (s16) arg1->unk50;
            gbaConectGBA_Connect_WORK.unk3C = (s16) arg1->unk52;
            gbaConectGBA_Connect_WORK.unk48 = 0U;
        }
        if ((s32) gbaConectGBA_Connect_WORK.unk0 == 2) {
            if (pauseIsPause() == 0) {
                gbaConectGBA_Connect_WORK.unk44 += 1;
            }
            arg1->unk50 = gbaConectGBA_Connect_WORK.unk34 + tool_gba_x_anime[(s8) gbaConectGBA_Connect_WORK.unk44 & 3];
            arg1->unk52 = gbaConectGBA_Connect_WORK.unk3C;
            return;
        }
        arg1->unk50 = gbaConectGBA_Connect_WORK.unk34;
        arg1->unk52 = gbaConectGBA_Connect_WORK.unk3C;
        return;
    case 0xEA:
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((1 - (s8) gbaConectGBA_Connect_WORK.unk30) | ((s8) gbaConectGBA_Connect_WORK.unk30 - 1)) >> 0x1FU));
        return;
    case 0xEE:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s8) gbaConectGBA_Connect_WORK.unk30 == 1) || ((s8) gbaConectGBA_Connect_WORK.unk30 == 4)));
        return;
    case 0xEF:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s8) gbaConectGBA_Connect_WORK.unk30 == 1) || ((s8) gbaConectGBA_Connect_WORK.unk30 == 4)));
        return;
    case 0xF0:
        menuCB_SpriteDispCheckONorOFF(arg1, (((s8) gbaConectGBA_Connect_WORK.unk30 == 1) || ((s8) gbaConectGBA_Connect_WORK.unk30 == 4)));
        return;
    case 0xE7:
        if ((u8) gbaConectGBA_Connect_WORK.unk49 != 0) {
            gbaConectGBA_Connect_WORK.unk36 = (s16) arg1->unk50;
            gbaConectGBA_Connect_WORK.unk3E = (s16) arg1->unk52;
            gbaConectGBA_Connect_WORK.unk49 = 0U;
        }
        if ((s32) gbaConectGBA_Connect_WORK.unk4 == 2) {
            if (pauseIsPause() == 0) {
                gbaConectGBA_Connect_WORK.unk45 += 1;
            }
            arg1->unk50 = gbaConectGBA_Connect_WORK.unk36 + tool_gba_x_anime[(s8) gbaConectGBA_Connect_WORK.unk45 & 3];
            arg1->unk52 = gbaConectGBA_Connect_WORK.unk3E;
            return;
        }
        arg1->unk50 = gbaConectGBA_Connect_WORK.unk36;
        arg1->unk52 = gbaConectGBA_Connect_WORK.unk3E;
        return;
    case 0xE0:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk32 != 0);
        return;
    case 0xE4:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk32 != 0);
        return;
    case 0xE8:
        if ((s8) gbaConectGBA_Connect_WORK.unk32 == 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        if ((u8) gbaConectGBA_Connect_WORK.unk4A != 0) {
            gbaConectGBA_Connect_WORK.unk38 = (s16) arg1->unk50;
            gbaConectGBA_Connect_WORK.unk40 = (s16) arg1->unk52;
            gbaConectGBA_Connect_WORK.unk4A = 0U;
        }
        if ((s32) gbaConectGBA_Connect_WORK.unk8 == 2) {
            if (pauseIsPause() == 0) {
                gbaConectGBA_Connect_WORK.unk46 += 1;
            }
            arg1->unk50 = gbaConectGBA_Connect_WORK.unk38 + tool_gba_x_anime[(s8) gbaConectGBA_Connect_WORK.unk46 & 3];
            arg1->unk52 = gbaConectGBA_Connect_WORK.unk40;
            return;
        }
        arg1->unk50 = gbaConectGBA_Connect_WORK.unk38;
        arg1->unk52 = gbaConectGBA_Connect_WORK.unk40;
        return;
    case 0xEC:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk32 != 0);
        return;
    case 0xE1:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk33 != 0);
        return;
    case 0xE5:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk33 != 0);
        return;
    case 0xE9:
        if ((s8) gbaConectGBA_Connect_WORK.unk33 == 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        if ((u8) gbaConectGBA_Connect_WORK.unk4B != 0) {
            gbaConectGBA_Connect_WORK.unk3A = (s16) arg1->unk50;
            gbaConectGBA_Connect_WORK.unk42 = (s16) arg1->unk52;
            gbaConectGBA_Connect_WORK.unk4B = 0U;
        }
        if ((s32) gbaConectGBA_Connect_WORK.unkC == 2) {
            if (pauseIsPause() == 0) {
                gbaConectGBA_Connect_WORK.unk47 += 1;
            }
            arg1->unk50 = gbaConectGBA_Connect_WORK.unk3A + tool_gba_x_anime[(s8) gbaConectGBA_Connect_WORK.unk47 & 3];
            arg1->unk52 = gbaConectGBA_Connect_WORK.unk42;
            return;
        }
        arg1->unk50 = gbaConectGBA_Connect_WORK.unk3A;
        arg1->unk52 = gbaConectGBA_Connect_WORK.unk42;
        return;
    case 0xED:
        menuCB_SpriteDispCheckONorOFF(arg1, (s8) gbaConectGBA_Connect_WORK.unk33 != 0);
        return;
    case 0xFB:
        arg1->unk4C = 0x441C;
        return;
    case 0xFC:
        arg1->unk4C = 0x441D;
        return;
    case 0xFD:
        arg1->unk4C = 0x435E;
        /* fallthrough */
    default:
        return;
    }
}

void menuTool_GBAConnect_Ctrl(MenuDBWindow *arg0) {
    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if ((s8) (u8) arg0->unk1 == 2) {
        if (((s32) gbaConectGBA_Connect_WORK.unk0 == 5) && (gbaCommandIsConnected(1) == 0)) {
            gbaConectGBA_Connect_WORK.unk0 = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (((s32) gbaConectGBA_Connect_WORK.unk4 == 5) && (gbaCommandIsConnected(2) == 0)) {
            gbaConectGBA_Connect_WORK.unk4 = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (((s32) gbaConectGBA_Connect_WORK.unk8 == 5) && (gbaCommandIsConnected(3) == 0)) {
            gbaConectGBA_Connect_WORK.unk8 = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
        if (((s32) gbaConectGBA_Connect_WORK.unkC == 5) && (gbaCommandIsConnected(4) == 0)) {
            gbaConectGBA_Connect_WORK.unkC = 7;
            gbaConectGBA_Connect_WORK.unk28 = 8;
        }
    }
}

void menuCB_Tunaide02_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s32 var_r30;
    s32 var_r30_2;
    s32 var_r30_3;
    s32 var_r30_4;
    s32 var_r4;
    s32 var_r4_2;

    temp_r0 = arg1->unk6;
    if (temp_r0 != 0xB6) {
        if (temp_r0 < 0xB6) {
            if (temp_r0 != 0xA6) {
                if (temp_r0 < 0xA6) {
                    switch (temp_r0) {              /* switch 1; irregular */
                    default:                        /* switch 1 */
                        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) == 0)));
                        return;
                    case 0xA2:                      /* switch 1 */
                        if (toolbattle_trainerFace(0) == 0) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Port_Icon_Char[1]));
                            return;
                        }
                        if ((s32) _CB.unk8 == 2) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Port_Icon_Char[0]));
                            return;
                        }
                        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Port_Icon_Char[1]));
                        return;
                    case 0x9E:                      /* switch 1 */
                        if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(0)]));
                            return;
                        }
                        winSpriteSetDisp(arg1, 0);
                        return;
                    case 0x9F:                      /* switch 1 */
                        if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(1)]));
                            return;
                        }
                        menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(0)]));
                        return;
                    case 0xA4:                      /* switch 1 */
                        menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) != 0)));
                        return;
                    case 0xA0:                      /* switch 1 */
                        if ((s32) _CB.unk8 == 2) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(2)]));
                            return;
                        }
                        if (toolbattle_trainerFace(0) != 0) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(1)]));
                            return;
                        }
                        winSpriteSetDisp(arg1, 0);
                        return;
                    case 0xA1:                      /* switch 1 */
                        if ((s32) _CB.unk8 == 2) {
                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(Big_Face_Char[toolbattle_trainerFace(3)]));
                            return;
                        }
                        winSpriteSetDisp(arg1, 0);
                        return;
                    }
                } else {
                    if (temp_r0 != 0xAF) {
                        if (temp_r0 < 0xAF) {
                            if (temp_r0 != 0xA9) {
                                if (temp_r0 < 0xA9) {
                                    if (temp_r0 < 0xA8) {
                                        if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) == 0)) {
                                            menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 1) == 0);
                                            return;
                                        }
                                        winSpriteSetDisp(arg1, 0);
                                        return;
                                    }
                                    if ((s32) tunaide02_last_kakunin_flag == 2) {
                                        winSpriteSetDisp(arg1, 1);
                                        return;
                                    }
                                    menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 2) == 0);
                                    return;
                                }
                                if (temp_r0 < 0xAE) {
                                    if (temp_r0 < 0xAC) {
                                        if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) != 0)) {
                                            menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 4) == 0);
                                            return;
                                        }
                                        winSpriteSetDisp(arg1, 0);
                                        return;
                                    }
                                    if ((s32) _CB.unk8 == 2) {
                                        menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 8) == 0);
                                        return;
                                    }
                                    winSpriteSetDisp(arg1, 0);
                                    return;
                                }
                                menuCB_SpriteDispCheckONorOFF(arg1, ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)));
                                return;
                            }
                            menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 2) == 0);
                            return;
                        }
                        if (temp_r0 != 0xB3) {
                            if (temp_r0 < 0xB3) {
                                if (temp_r0 != 0xB1) {
                                    if (temp_r0 < 0xB1) {
                                        if ((s32) _CB.unk8 == 2) {
                                            winSpriteSetDisp(arg1, 1);
                                            return;
                                        }
                                        if (toolbattle_trainerFace(0) != 0) {
                                            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PlayerNumber[1]));
                                            return;
                                        }
                                        winSpriteSetDisp(arg1, 0);
                                        return;
                                    }
                                    if ((s32) tunaide02_last_kakunin_flag == 1) {
                                        arg1->unk4C = 0x43C8;
                                        return;
                                    }
                                    if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                                        if ((s32) (_CB.unkB0D4 & 1) != 0) {
                                            arg1->unk4C = 0;
                                            return;
                                        }
                                        arg1->unk4C = 0x43C6;
                                        return;
                                    }
                                    arg1->unk4C = 0;
                                    return;
                                }
                                menuCB_SpriteDispCheckONorOFF(arg1, _CB.unk8 == 2);
                                return;
                            }
                            if (temp_r0 < 0xB5) {
                                if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) != 0)) {
                                    if ((s32) (_CB.unkB0D4 & 4) != 0) {
                                        arg1->unk4C = 0;
                                        return;
                                    }
                                    arg1->unk4C = 0x43C6;
                                    return;
                                }
                                arg1->unk4C = 0;
                                return;
                            }
                            if ((s32) _CB.unk8 == 2) {
                                if ((s32) (_CB.unkB0D4 & 8) != 0) {
                                    arg1->unk4C = 0;
                                    return;
                                }
                                arg1->unk4C = 0x43C6;
                                return;
                            }
                            arg1->unk4C = 0;
                            return;
                        }
                        if ((s32) tunaide02_last_kakunin_flag == 2) {
                            arg1->unk4C = 0x43C8;
                            return;
                        }
                        if ((s32) (_CB.unkB0D4 & 2) != 0) {
                            arg1->unk4C = 0;
                            return;
                        }
                        arg1->unk4C = 0x43C6;
                        return;
                    }
                    if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                        winSpriteSetDisp(arg1, 1);
                        return;
                    }
                    menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(PlayerNumber[0]));
                }
            } else {
                if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) == 0)) {
                    if ((s32) tunaide02_last_kakunin_flag == 1) {
                        winSpriteSetDisp(arg1, 1);
                        return;
                    }
                    menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 1) == 0);
                    return;
                }
                winSpriteSetDisp(arg1, 0);
            }
        } else if (temp_r0 != 0xC4) {
            if (temp_r0 < 0xC4) {
                if (temp_r0 != 0xBD) {
                    if (temp_r0 < 0xBD) {
                        if (temp_r0 != 0xBA) {
                            if (temp_r0 < 0xBA) {
                                if (temp_r0 != 0xB8) {
                                    if (temp_r0 < 0xB8) {
                                        if ((s32) tunaide02_last_kakunin_flag == 2) {
                                            arg1->unk4C = 0x43C7;
                                            return;
                                        }
                                        if ((s32) (_CB.unkB0D4 & 2) != 0) {
                                            arg1->unk4C = 0;
                                            return;
                                        }
                                        arg1->unk4C = 0x43C5;
                                        return;
                                    }
                                    if ((s32) _CB.unk8 == 2) {
                                        if ((s32) (_CB.unkB0D4 & 8) != 0) {
                                            arg1->unk4C = 0;
                                            return;
                                        }
                                        arg1->unk4C = 0x43C5;
                                        return;
                                    }
                                    arg1->unk4C = 0;
                                    return;
                                }
                                if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) != 0)) {
                                    if ((s32) (_CB.unkB0D4 & 4) != 0) {
                                        arg1->unk4C = 0;
                                        return;
                                    }
                                    arg1->unk4C = 0x43C5;
                                    return;
                                }
                                arg1->unk4C = 0;
                                return;
                            }
                            if (temp_r0 < 0xBC) {
                                if ((s32) _CB.unk8 == 2) {
                                    toolbattle_drawHeroID(arg0, 2);
                                    return;
                                }
                                if (toolbattle_trainerFace(0) != 0) {
                                    toolbattle_drawHeroID(arg0, 1);
                                }
                            } else {
                                if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                                    toolbattle_drawHeroID(arg0, 1);
                                    return;
                                }
                                toolbattle_drawHeroID(arg0, 0);
                            }
                        } else if ((s32) _CB.unk8 == 2) {
                            toolbattle_drawHeroID(arg0, 3);
                        }
                    } else if (temp_r0 != 0xC1) {
                        if (temp_r0 < 0xC1) {
                            if (temp_r0 != 0xBF) {
                                if (temp_r0 < 0xBF) {
                                    if ((s32) _CB.unk8 == 2) {
                                        toobattle_drawHeroName(arg0, 3);
                                    }
                                } else {
                                    if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                                        toobattle_drawHeroName(arg0, 1);
                                        return;
                                    }
                                    toobattle_drawHeroName(arg0, 0);
                                }
                            } else {
                                if ((s32) _CB.unk8 == 2) {
                                    toobattle_drawHeroName(arg0, 2);
                                    return;
                                }
                                if (toolbattle_trainerFace(0) != 0) {
                                    toobattle_drawHeroName(arg0, 1);
                                }
                            }
                        } else {
                            if (temp_r0 < 0xC3) {
                                arg1->unk4C = 0x440A;
                                return;
                            }
                            arg1->unk4C = 0x440B;
                        }
                    } else if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                        toobattle_drawHeroName(arg0, 0);
                    }
                } else if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
                    toolbattle_drawHeroID(arg0, 0);
                }
            } else if (temp_r0 != 0xCA) {
                if (temp_r0 < 0xCA) {
                    if (temp_r0 != 0xC7) {
                        if (temp_r0 < 0xC7) {
                            if (temp_r0 < 0xC6) {
                                if ((s32) _CB.unk8 == 2) {
                                    arg1->unk4C = 0x440D;
                                    return;
                                }
                                arg1->unk4C = 0;
                                return;
                            }
                            if ((s32) tunaide02_last_kakunin_flag == 0) {
                                arg1->unk4C = 0x43C9;
                                return;
                            }
                            arg1->unk4C = 0x43CA;
                            return;
                        }
                        if (temp_r0 < 0xC9) {
                            menuCB_SpriteDispCheckONorOFF(arg1, (((s32) (_CB.unkB0D4 & 2) != 0) && ((s32) tunaide02_last_kakunin_flag != 2)));
                            return;
                        }
                        menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 4) != 0);
                        return;
                    }
                    menuCB_SpriteDispCheckONorOFF(arg1, (((s32) (_CB.unkB0D4 & 1) != 0) && ((s32) tunaide02_last_kakunin_flag != 1)));
                    return;
                }
                switch (temp_r0) {                  /* switch 2; irregular */
                case 0x2DA:                         /* switch 2 */
                    menuCB_SpriteDispCheckONorOFF(arg1, tunaide02_last_kakunin_flag == 1);
                    return;
                case 0x2DB:                         /* switch 2 */
                    menuCB_SpriteDispCheckONorOFF(arg1, tunaide02_last_kakunin_flag == 2);
                    return;
                default:                            /* switch 2 */
                    menuCB_SpriteDispCheckONorOFF(arg1, (((s32) _CB.unk8 != 2) && (toolbattle_trainerFace(0) != 0)));
                    return;
                }
            } else {
                menuCB_SpriteDispCheckONorOFF(arg1, (_CB.unkB0D4 & 8) != 0);
            }
        } else {
            if (((s32) _CB.unk8 == 2) || (toolbattle_trainerFace(0) != 0)) {
                arg1->unk4C = 0x440C;
                return;
            }
            arg1->unk4C = 0;
        }
    } else {
        if ((s32) tunaide02_last_kakunin_flag == 1) {
            arg1->unk4C = 0x43C7;
            return;
        }
        if ((toolbattle_trainerFace(0) == 0) || ((s32) _CB.unk8 == 2)) {
            if ((s32) (_CB.unkB0D4 & 1) != 0) {
                arg1->unk4C = 0;
                return;
            }
            arg1->unk4C = 0x43C5;
            return;
        }
        arg1->unk4C = 0;
    }
}

void menuTool_tunaide02_Button(MenuDBWindow *arg0) {
    u8 portBits[4] = {1, 2, 4, 8};
    u16 keys[4];

    if ((s32) _CB.unk8 == 2) {
        s32 i;
        for (i = 0; i < 4; i++) {
            keys[i] = windowGetPortKeyInfo(portBits[toolentryTaisenGetControlerType(i) - 1])->unk4;
        }
        if ((s32) _CB.unkB0D4 == 0xF) {
            tunaide02_last_kakunin_flag = 1;
            if ((s32) (keys[0] & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if ((s32) (keys[0] & 0x800) != 0) {
                arg0->unkA4 = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if (((s32) (keys[0] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(1) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(1);
                menuCB_SE_Play(0x11);
            }
            if (((s32) (keys[1] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(2) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if (((s32) (keys[2] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(4) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(4);
                menuCB_SE_Play(0x11);
            }
            if (((s32) (keys[3] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(8) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(8);
                menuCB_SE_Play(0x11);
            }
            if ((s32) ((keys[3] | (keys[2] | (keys[0] | keys[1]))) & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    } else if (toolbattle_trainerFace(0) != 0) {
        keys[1] = windowGetPortKeyInfo(portBits[toolentryTaisenGetControlerType(1) - 1])->unk4;
        keys[2] = windowGetPortKeyInfo(portBits[toolentryTaisenGetControlerType(2) - 1])->unk4;
        if ((s32) _CB.unkB0D4 == 6) {
            tunaide02_last_kakunin_flag = 2;
            if ((s32) (keys[1] & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if ((s32) (keys[1] & 0x800) != 0) {
                arg0->unkA4 = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if (((s32) (keys[1] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(2) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if (((s32) (keys[2] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(4) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(4);
                menuCB_SE_Play(0x11);
            }
            if ((s32) ((keys[1] | keys[2]) & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    } else {
        keys[0] = windowGetPortKeyInfo(portBits[toolentryTaisenGetControlerType(0) - 1])->unk4;
        keys[1] = windowGetPortKeyInfo(portBits[toolentryTaisenGetControlerType(1) - 1])->unk4;
        if ((s32) _CB.unkB0D4 == 3) {
            tunaide02_last_kakunin_flag = 1;
            if ((s32) (keys[0] & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
                return;
            }
            if ((s32) (keys[0] & 0x800) != 0) {
                arg0->unkA4 = 1;
                menuCB_SE_Play(0x11);
            }
        } else {
            tunaide02_last_kakunin_flag = 0;
            if (((s32) (keys[0] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(1) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(1);
                menuCB_SE_Play(0x11);
            }
            if (((s32) (keys[1] & 0x10) != 0) && (toolBattle_tunaideMenu02menuTempBuffGet(2) == 0)) {
                toolBattle_tunaideMenu02menuTempBuffSet(2);
                menuCB_SE_Play(0x11);
            }
            if ((s32) ((keys[0] | keys[1]) & 0x20) != 0) {
                arg0->unkA4 = 1;
                arg0->unkA5 = 1;
                _CB.unkB068 = 1;
                menuCB_SE_Play(0x12);
            }
        }
    }
}

void menuCB_Tunaide01_3_Disp(MenuDBWindow *arg0, MenuDBSprite *arg1) {
    s16 temp_r0;
    s16 temp_r3;
    s16 temp_r3_2;

    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* switch 1; irregular */
    case 0x2A3:                                     /* switch 1 */
        if ((s32) _CB.unkB114 == 0) {
            menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(BATTLE_FIELD_Char[_CB.unkAFFC]));
            return;
        }
        winSpriteSetDisp(arg1, 0);
        if (_CB.unkB114 != 0)
        switch ((s32) _CB.unkB114) {                /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            field_anime.unk0 = 0;
            field_anime.unk2 = 0;
            field_anime.unk4 = 0x116;
            field_anime.unk6 = 0;
            field_anime.unk8 = -1;
            field_anime.unkE = 0;
            field_anime.unk10 = 0xA7;
            field_anime.unkC = (u16) BATTLE_FIELD_Char[_CB.unkAFFC];
            field_anime.unk14 = 0;
            field_anime.unk18 = 0;
            field_anime.unk1A = 0;
            field_anime.unk1C = 0x116;
            field_anime.unk1E = 0xA7;
            field_anime.unk20 = -1;
            field_anime.unk26 = 0;
            field_anime.unk28 = 0;
            field_anime.unk24 = (u16) BATTLE_FIELD_Char[_CB.unkB000];
            field_anime.unk2C = 0;
            _CB.unkB114 = 2;
            return;
        case 3:                                     /* switch 2 */
            field_anime.unk0 = 0;
            field_anime.unk2 = 0xA7;
            field_anime.unk4 = 0x116;
            field_anime.unk6 = 0;
            field_anime.unk8 = -1;
            field_anime.unkE = 0;
            field_anime.unk10 = 0;
            field_anime.unkC = (u16) BATTLE_FIELD_Char[_CB.unkAFFC];
            field_anime.unk14 = 0;
            field_anime.unk18 = 0;
            field_anime.unk1A = 0;
            field_anime.unk1C = 0x116;
            field_anime.unk1E = 0xA7;
            field_anime.unk20 = -1;
            field_anime.unk26 = 0;
            field_anime.unk28 = 0;
            field_anime.unk24 = (u16) BATTLE_FIELD_Char[_CB.unkB000];
            field_anime.unk2C = 0;
            _CB.unkB114 = 4;
            return;
        case 2:                                     /* switch 2 */
            temp_r3 = field_anime.unk6 + 0xF;
            field_anime.unk6 = temp_r3;
            if (temp_r3 >= 0xA7) {
                field_anime.unk6 = 0;
                _CB.unkB114 = 0;
                winSpriteSetDisp(arg1, 1);
                menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(BATTLE_FIELD_Char[_CB.unkAFFC]));
            }
            field_anime.unk1A = (s16) field_anime.unk6;
            field_anime.unk10 = (s16) (0xA7 - field_anime.unk6);
            field_anime.unk1E = (s16) (0xA7 - field_anime.unk6);
            return;
        case 4:                                     /* switch 2 */
            temp_r3_2 = field_anime.unk6 + 0xF;
            field_anime.unk6 = temp_r3_2;
            if (temp_r3_2 >= 0xA7) {
                field_anime.unk6 = 0;
                _CB.unkB114 = 0;
                winSpriteSetDisp(arg1, 1);
                menuCB_SetSprite(arg1, menuSpriteBiosGetPtr(BATTLE_FIELD_Char[_CB.unkAFFC]));
            }
            field_anime.unk28 = (s16) field_anime.unk6;
            field_anime.unk2 = (s16) (0xA7 - field_anime.unk6);
            field_anime.unk1E = (s16) (0xA7 - field_anime.unk6);
            return;
        }
        break;
    case 0x2D9:                                     /* switch 1 */
        if ((s32) _CB.unkB114 != 0) {
            windowDrawSprite3(field_anime.unk0, field_anime.unk2, field_anime.unk4, field_anime.unk6, field_anime.unk8, arg0, field_anime.unkC, field_anime.unkE, field_anime.unk10, field_anime.unk4, field_anime.unk6, field_anime.unk14, arg0->unk1C);
            return;
        }
        break;
    case 0x2D8:                                     /* switch 1 */
        if ((s32) _CB.unkB114 != 0) {
            windowDrawSprite3(field_anime.unk18, field_anime.unk1A, field_anime.unk1C, field_anime.unk1E, field_anime.unk20, arg0, field_anime.unk24, field_anime.unk26, field_anime.unk28, field_anime.unk1C, field_anime.unk1E, field_anime.unk2C, arg0->unk1C);
            return;
        }
        break;
    case 0x2A1:                                     /* switch 1 */
        if ((s32) _CB.unkB10C != 1) {
            arg1->unk67 = 0x7F;
        }
        menuCB_SpriteDispCheckONorOFF(arg1, (s32) ((u32) ((6 - _CB.unkAFFC) | (_CB.unkAFFC - 6)) >> 0x1FU));
        return;
    case 0x2A2:                                     /* switch 1 */
        if ((s32) _CB.unkB10C != 1) {
            arg1->unk67 = 0x7F;
        }
        menuCB_SpriteDispCheckONorOFF(arg1, _CB.unkAFFC != 0);
        return;
    case 0x3ED:
    case 0x3EE:
    case 0x3EF:
        if ((s32) _CB.unkB114 != 0) {
            winSpriteSetDisp(arg1, 0);
            return;
        }
        winSpriteSetDisp(arg1, 1);
        menuCB_Cursol_Disp_AlphaSet(arg0, arg1, _CB.unkB10C == 1);
        break;
    }
}

void menuTool_Rule00_Ctrl(MenuDBWindow *arg0) {
    s16 temp_r0_5;
    s16 temp_r0_6;
    s16 temp_r0_7;
    s16 temp_r0_8;
    s16 temp_r29;
    s16 temp_r29_2;
    s16 temp_r29_3;
    s16 temp_r29_4;
    s16 temp_r30;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r4;
    s16 temp_r4_2;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r10;
    s32 temp_r11;
    s32 temp_r3_4;
    s32 temp_r3_5;
    s32 temp_r6;
    s32 temp_r7;
    s32 temp_r8;
    s32 temp_r9;
    s32 var_ctr;
    s32 var_ctr_2;
    u16 temp_r29_10;
    u16 temp_r29_11;
    u16 temp_r29_12;
    u16 temp_r29_13;
    u16 temp_r29_14;
    u16 temp_r29_15;
    u16 temp_r29_16;
    u16 temp_r29_17;
    u16 temp_r29_18;
    u16 temp_r29_19;
    u16 temp_r29_20;
    u16 temp_r29_21;
    u16 temp_r29_5;
    u16 temp_r29_6;
    u16 temp_r29_7;
    u16 temp_r29_8;
    u16 temp_r29_9;
    u32 var_r5;
    u8 temp_r6_2;
    u8 temp_r7_2;
    u8 *temp_r3;
    u8 *var_r7;

    menuCB_DispEffect(arg0);
    menuSetStatus(arg0->unk4, 0x10);
    if (pauseIsPause() == 0) {
        menuCB_AlphaGet(arg0);
        _CB.unkB120 += 1;
        if ((s32) _CB.unkB124 != -1) {
            _CB.unkB128 -= 0x10;
            _CB.unkB12C += 0x10;
            if ((s32) _CB.unkB12C >= 0xFF) {
                _CB.unkB12C = 0xFF;
                _CB.unkB128 = 0xF;
                _CB.unkB124 = -1;
            }
        } else if ((s32) _CB.unkB010 < 1) {
            if ((s32) _CB.unkB090 >= 1) {
                return;
            }
            if ((s32) _CB.unkB0B0 != 0) {
                if ((s32) _CB.unkB0B4 == 0) {
                    return;
                }
                if ((s32) _CB.unkB118 == 5) {
                    if ((s32) _ruleCursol2 != -1) {
                        if ((s32) _ruleCursol2 != (s32) _CB.unkB028) {
                            if ((s32) _ruleCursol2 > (s32) _CB.unkB028) {
                                _CB.unkB028 += 1;
                                return;
                            }
                            _CB.unkB028 -= 1;
                            return;
                        }
                        _ruleCursol2 = -1;
                        goto block_17;
                    }
block_17:
                    if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                        for (var_r5 = 0; var_r5 < 0x3E; ++var_r5) {
                            _CB.unk9C78->itemFlags[var_r5] = _ruleTempBuff_DB.itemFlags[var_r5];
                        }
                        _CB.unkB118 = 1;
                        _CB.unkB02C = 0;
                        _CB.unkB028 = 0;
                        _CB.unkB130 = 0x37;
                        menuCB_SE_Play(0x15);
                        return;
                    }
                    if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                        if ((s32) (_CB.unkB028 + _CB.unkB02C) >= 0x3E) {
                            _CB.unkB118 = 1;
                            _CB.unkB02C = 0;
                            _CB.unkB028 = 0;
                            _CB.unkB11C = 0;
                            _CB.unkB130 = 0x37;
                            menuCB_SE_Play(0x15);
                            return;
                        }
                        menuCB_SE_Play(0x11);
                        temp_r3 = _CB.unk9C78->itemFlags + _CB.unkB02C;
                        *(_CB.unkB028 + temp_r3) = *(_CB.unkB028 + temp_r3) ^ 1;
                        goto block_27;
                    }
block_27:
                    if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                        if ((s32) _CB.unkB02C != 0) {
                            _CB.unkB02C -= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if ((s32) _CB.unkB028 != 0) {
                            _CB.unkB028 -= 1;
                            menuCB_SE_Play(0x10);
                        }
                    } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                        if ((s32) _CB.unkB02C != 0xA) {
                            _CB.unkB02C += 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if ((s32) _CB.unkB028 != 0x34) {
                            _CB.unkB028 += 1;
                            menuCB_SE_Play(0x10);
                        }
                    } else if ((s32) (windowGetKeyRepeat() & 4) != 0) {
                        temp_r0_3 = _CB.unkB028 - 0xA;
                        _ruleCursol2 = temp_r0_3;
                        if (temp_r0_3 <= 0) {
                            _ruleCursol2 = 0;
                        }
                        if ((s32) _ruleCursol2 != (s32) _CB.unkB028) {
                            menuCB_SE_Play(0x10);
                        }
                    } else if ((s32) (windowGetKeyRepeat() & 8) != 0) {
                        temp_r0_4 = _CB.unkB028 + 0xA;
                        _ruleCursol2 = temp_r0_4;
                        if (temp_r0_4 >= 0x34) {
                            _ruleCursol2 = 0x34;
                        }
                        if ((s32) _ruleCursol2 != (s32) _CB.unkB028) {
                            menuCB_SE_Play(0x10);
                        }
                    }
                } else {
                    switch ((s32) _CB.unkB11C) {    /* switch 1; irregular */
                    case 0x10:                      /* switch 1 */
                        temp_r30 = (s16) _CB.unk9C78->unk0;
                        temp_r29 = (s16) _CB.unk9C78->unk2;
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk0 = (u16) _ruleTempBuff_DB.unk0;
                            _CB.unk9C78->unk2 = (u16) _ruleTempBuff_DB.unk2;
                            _CB.unk9C78->unk4 = (u16) _ruleTempBuff_DB.unk4;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        if (((s32) (windowGetKeyRepeat() & 4) != 0) && ((s32) _ruleCursol.unk0 != 0)) {
                            _ruleCursol.unk0 -= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if (((s32) (windowGetKeyRepeat() & 8) != 0) && ((s32) _ruleCursol.unk0 != 5)) {
                            _ruleCursol.unk0 += 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                            switch ((s32) _ruleCursol.unk0) { /* switch 2; irregular */
                            case 0:                 /* switch 2 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 + 0x64;
                                break;
                            case 1:                 /* switch 2 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 + 0xA;
                                break;
                            case 2:                 /* switch 2 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 + 1;
                                break;
                            case 3:                 /* switch 2 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 + 0x64;
                                break;
                            case 4:                 /* switch 2 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 + 0xA;
                                break;
                            case 5:                 /* switch 2 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 + 1;
                                break;
                            }
                            if ((s16) _CB.unk9C78->unk0 >= 0x64) {
                                _CB.unk9C78->unk0 = 0x64;
                            }
                            if ((s16) _CB.unk9C78->unk2 >= 0x64) {
                                _CB.unk9C78->unk2 = 0x64;
                            }
                            temp_r4 = (s16) _CB.unk9C78->unk0;
                            if (temp_r4 >= (s16) _CB.unk9C78->unk2) {
                                _CB.unk9C78->unk2 = (u16) temp_r4;
                            }
                            _CB.unk9C78->unk4 = (u16) (s16) ((s16) _CB.unk9C78->unk2 * 6);
                        }
                        if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                            switch ((s32) _ruleCursol.unk0) { /* switch 3; irregular */
                            case 0:                 /* switch 3 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 - 0x64;
                                break;
                            case 1:                 /* switch 3 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 - 0xA;
                                break;
                            case 2:                 /* switch 3 */
                                _CB.unk9C78->unk0 = (s16) _CB.unk9C78->unk0 - 1;
                                break;
                            case 3:                 /* switch 3 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 - 0x64;
                                break;
                            case 4:                 /* switch 3 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 - 0xA;
                                break;
                            case 5:                 /* switch 3 */
                                _CB.unk9C78->unk2 = (s16) _CB.unk9C78->unk2 - 1;
                                break;
                            }
                            if ((s16) _CB.unk9C78->unk0 <= 1) {
                                _CB.unk9C78->unk0 = 1;
                            }
                            if ((s16) _CB.unk9C78->unk2 <= 1) {
                                _CB.unk9C78->unk2 = 1;
                            }
                            temp_r4_2 = (s16) _CB.unk9C78->unk2;
                            if ((s16) _CB.unk9C78->unk0 >= temp_r4_2) {
                                _CB.unk9C78->unk0 = (u16) temp_r4_2;
                            }
                            _CB.unk9C78->unk4 = (u16) (s16) ((s16) _CB.unk9C78->unk2 * 6);
                        }
                        if ((temp_r30 != (s16) _CB.unk9C78->unk0) || (temp_r29 != (s16) _CB.unk9C78->unk2)) {
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x11:                      /* switch 1 */
                        temp_r29_2 = (s16) _CB.unk9C78->unk4;
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk4 = (u16) _ruleTempBuff_DB.unk4;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        if (((s32) (windowGetKeyRepeat() & 4) != 0) && ((s32) _ruleCursol.unk4 != 0)) {
                            _ruleCursol.unk4 -= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if (((s32) (windowGetKeyRepeat() & 8) != 0) && ((s32) _ruleCursol.unk4 != 2)) {
                            _ruleCursol.unk4 += 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                            switch ((s32) _ruleCursol.unk4) { /* switch 4; irregular */
                            case 0:                 /* switch 4 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 + 0x64;
                                break;
                            case 1:                 /* switch 4 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 + 0xA;
                                break;
                            case 2:                 /* switch 4 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 + 1;
                                break;
                            }
                            temp_r0_5 = (s16) _CB.unk9C78->unk0 * 6;
                            if ((s16) _CB.unk9C78->unk4 <= temp_r0_5) {
                                _CB.unk9C78->unk4 = (u16) temp_r0_5;
                            }
                            temp_r0_6 = (s16) _CB.unk9C78->unk2 * 6;
                            if ((s16) _CB.unk9C78->unk4 >= temp_r0_6) {
                                _CB.unk9C78->unk4 = (u16) temp_r0_6;
                            }
                        }
                        if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                            switch ((s32) _ruleCursol.unk4) { /* switch 5; irregular */
                            case 0:                 /* switch 5 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 - 0x64;
                                break;
                            case 1:                 /* switch 5 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 - 0xA;
                                break;
                            case 2:                 /* switch 5 */
                                _CB.unk9C78->unk4 = (s16) _CB.unk9C78->unk4 - 1;
                                break;
                            }
                            temp_r0_7 = (s16) _CB.unk9C78->unk0 * 6;
                            if ((s16) _CB.unk9C78->unk4 <= temp_r0_7) {
                                _CB.unk9C78->unk4 = (u16) temp_r0_7;
                            }
                            temp_r0_8 = (s16) _CB.unk9C78->unk2 * 6;
                            if ((s16) _CB.unk9C78->unk4 >= temp_r0_8) {
                                _CB.unk9C78->unk4 = (u16) temp_r0_8;
                            }
                        }
                        if (temp_r29_2 != (s16) _CB.unk9C78->unk4) {
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x12:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk14 = (u16) _ruleTempBuff_DB.unk14;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        if ((s32) (windowGetKeyRepeat() & 4) != 0) {
                            if ((s32) _ruleCursol.unk8 != 0) {
                                _ruleCursol.unk8 -= 1;
                                menuCB_SE_Play(0x10);
                            }
                            _CB.unk9C78->unk14 = (u16) abs((s16) _CB.unk9C78->unk14);
                            if ((s32) _ruleCursol.unk8 == 2) {
                                _CB.unk9C78->unk14 = (u16) (s16) (abs((s16) _CB.unk9C78->unk14) * -1);
                                return;
                            }
                        } else if ((s32) (windowGetKeyRepeat() & 8) != 0) {
                            if ((s32) _ruleCursol.unk8 != 2) {
                                _ruleCursol.unk8 += 1;
                                menuCB_SE_Play(0x10);
                            }
                            _CB.unk9C78->unk14 = (u16) abs((s16) _CB.unk9C78->unk14);
                            if ((s32) _ruleCursol.unk8 == 2) {
                                _CB.unk9C78->unk14 = (u16) (s16) (abs((s16) _CB.unk9C78->unk14) * -1);
                                return;
                            }
                        } else {
                            temp_r29_3 = (s16) _CB.unk9C78->unk14;
                            if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                                switch ((s32) _ruleCursol.unk8) { /* switch 6; irregular */
                                case 0:             /* switch 6 */
                                    _CB.unk9C78->unk14 = (s16) _CB.unk9C78->unk14 + 0xA;
                                    if ((s16) _CB.unk9C78->unk14 >= 0x63) {
                                        _CB.unk9C78->unk14 = 0x63;
                                    }
                                    break;
                                case 1:             /* switch 6 */
                                    _CB.unk9C78->unk14 = (s16) _CB.unk9C78->unk14 + 1;
                                    if ((s16) _CB.unk9C78->unk14 >= 0x63) {
                                        _CB.unk9C78->unk14 = 0x63;
                                    }
                                    break;
                                }
                            }
                            if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                                switch ((s32) _ruleCursol.unk8) { /* switch 7; irregular */
                                case 0:             /* switch 7 */
                                    _CB.unk9C78->unk14 = (s16) _CB.unk9C78->unk14 - 0xA;
                                    if ((s16) _CB.unk9C78->unk14 <= 1) {
                                        _CB.unk9C78->unk14 = 1;
                                    }
                                    break;
                                case 1:             /* switch 7 */
                                    _CB.unk9C78->unk14 = (s16) _CB.unk9C78->unk14 - 1;
                                    if ((s16) _CB.unk9C78->unk14 <= 1) {
                                        _CB.unk9C78->unk14 = 1;
                                    }
                                    break;
                                }
                            }
                            if (temp_r29_3 != (s16) _CB.unk9C78->unk14) {
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        break;
                    case 0x13:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk16 = (u16) _ruleTempBuff_DB.unk16;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        if ((s32) (windowGetKeyRepeat() & 4) != 0) {
                            if ((s32) _ruleCursol.unkC != 0) {
                                _ruleCursol.unkC -= 1;
                                menuCB_SE_Play(0x10);
                            }
                            _CB.unk9C78->unk16 = (u16) abs((s16) _CB.unk9C78->unk16);
                            if ((s32) _ruleCursol.unkC == 2) {
                                _CB.unk9C78->unk16 = (u16) (s16) (abs((s16) _CB.unk9C78->unk16) * -1);
                                return;
                            }
                        } else if ((s32) (windowGetKeyRepeat() & 8) != 0) {
                            if ((s32) _ruleCursol.unkC != 2) {
                                _ruleCursol.unkC += 1;
                                menuCB_SE_Play(0x10);
                            }
                            _CB.unk9C78->unk16 = (u16) abs((s16) _CB.unk9C78->unk16);
                            if ((s32) _ruleCursol.unkC == 2) {
                                _CB.unk9C78->unk16 = (u16) (s16) (abs((s16) _CB.unk9C78->unk16) * -1);
                                return;
                            }
                        } else {
                            temp_r29_4 = (s16) _CB.unk9C78->unk16;
                            if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                                switch ((s32) _ruleCursol.unkC) { /* switch 8; irregular */
                                case 0:             /* switch 8 */
                                    _CB.unk9C78->unk16 = (s16) _CB.unk9C78->unk16 + 0xA;
                                    if ((s16) _CB.unk9C78->unk16 >= 0x63) {
                                        _CB.unk9C78->unk16 = 0x63;
                                    }
                                    break;
                                case 1:             /* switch 8 */
                                    _CB.unk9C78->unk16 = (s16) _CB.unk9C78->unk16 + 1;
                                    if ((s16) _CB.unk9C78->unk16 >= 0x63) {
                                        _CB.unk9C78->unk16 = 0x63;
                                    }
                                    break;
                                }
                            }
                            if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                                switch ((s32) _ruleCursol.unkC) { /* switch 9; irregular */
                                case 0:             /* switch 9 */
                                    _CB.unk9C78->unk16 = (s16) _CB.unk9C78->unk16 - 0xA;
                                    if ((s16) _CB.unk9C78->unk16 <= 0xA) {
                                        _CB.unk9C78->unk16 = 0xA;
                                    }
                                    break;
                                case 1:             /* switch 9 */
                                    _CB.unk9C78->unk16 = (s16) _CB.unk9C78->unk16 - 1;
                                    if ((s16) _CB.unk9C78->unk16 <= 0xA) {
                                        _CB.unk9C78->unk16 = 0xA;
                                    }
                                    break;
                                }
                            }
                            if (temp_r29_4 != (s16) _CB.unk9C78->unk16) {
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        break;
                    case 0x14:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk1A = (u16) _ruleTempBuff_DB.unk1A;
                            _CB.unk9C78->unk1C = (u16) _ruleTempBuff_DB.unk1C;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_5 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_5) & 4) != 0) {
                            _ruleCursol.unk10 = 0;
                            if ((s16) _CB.unk9C78->unk1C != 0) {
                                _CB.unk9C78->unk1C = 0;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        temp_r29_6 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_6) & 8) != 0) {
                            _ruleCursol.unk10 = 1;
                            if ((s16) _CB.unk9C78->unk1C != 1) {
                                _CB.unk9C78->unk1C = 1;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        if (((s32) (windowGetKeyRepeat() & 1) != 0) && ((s32) _ruleCursol.unk10 == 0)) {
                            temp_r3_2 = (s16) _CB.unk9C78->unk1A;
                            if (temp_r3_2 != 6) {
                                _CB.unk9C78->unk1A = temp_r3_2 + 1;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        if (((s32) (windowGetKeyRepeat() & 2) != 0) && ((s32) _ruleCursol.unk10 == 0)) {
                            temp_r3_3 = (s16) _CB.unk9C78->unk1A;
                            if (temp_r3_3 != 1) {
                                _CB.unk9C78->unk1A = temp_r3_3 - 1;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                        }
                        break;
                    case 0x20:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unkC = _ruleTempBuff_DB.unkC;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_7 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_7) & 3) != 0) {
                            _CB.unk9C78->unkC ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x21:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk8 = _ruleTempBuff_DB.unk8;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            if ((s32) _CB.unk9C78->unk8 != 2) {
                                _CB.unkB11C = 0;
                                menuCB_SE_Play(0x11);
                                return;
                            }
                            _CB.unkB118 = 5;
                            _CB.unkB130 = -0x37;
                            _ruleCursol2 = -1;
                            menuCB_SE_Play(0x11);
                            menuCB_SE_Play(0x14);
                            return;
                        }
                        temp_r29_8 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_8) & 1) != 0) {
                            temp_r3_4 = _CB.unk9C78->unk8;
                            if (temp_r3_4 != 0) {
                                _CB.unk9C78->unk8 = temp_r3_4 - 1;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                            _CB.unk9C78->unk8 = 2;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        temp_r29_9 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_9) & 2) != 0) {
                            temp_r3_5 = _CB.unk9C78->unk8;
                            if (temp_r3_5 != 2) {
                                _CB.unk9C78->unk8 = temp_r3_5 + 1;
                                menuCB_SE_Play(0x10);
                                return;
                            }
                            _CB.unk9C78->unk8 = 0;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x22:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unkD = _ruleTempBuff_DB.unkD;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_10 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_10) & 3) != 0) {
                            _CB.unk9C78->unkD ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x30:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk19 = _ruleTempBuff_DB.unk19;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_11 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_11) & 3) != 0) {
                            _CB.unk9C78->unk19 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x31:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unkE = _ruleTempBuff_DB.unkE;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_12 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_12) & 3) != 0) {
                            _CB.unk9C78->unkE ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x32:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk10 = _ruleTempBuff_DB.unk10;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_13 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_13) & 3) != 0) {
                            _CB.unk9C78->unk10 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x40:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk11 = _ruleTempBuff_DB.unk11;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_14 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_14) & 3) != 0) {
                            _CB.unk9C78->unk11 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x41:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk12 = _ruleTempBuff_DB.unk12;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_15 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_15) & 3) != 0) {
                            _CB.unk9C78->unk12 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x42:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unkF = _ruleTempBuff_DB.unkF;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_16 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_16) & 3) != 0) {
                            _CB.unk9C78->unkF ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x43:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unk9C78->unk13 = _ruleTempBuff_DB.unk13;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_17 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_17) & 3) != 0) {
                            _CB.unk9C78->unk13 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x50:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unkB030 = 1;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            if ((s32) _CB.unkB030 == 0) {
                                _CB.unkB0B0 = 0;
                            }
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_18 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_18) & 3) != 0) {
                            _CB.unkB030 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x51:                      /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x20) != 0) {
                            _CB.unkB11C = 0;
                            _CB.unkB034 = 1;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                            _CB.unkB11C = 0;
                            if ((s32) _CB.unkB034 == 0) {
                                _CB.unkB0B4 = 0;
                            }
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        temp_r29_19 = windowGetKeyInfo2()->unk4;
                        if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_19) & 3) != 0) {
                            _CB.unkB034 ^= 1;
                            menuCB_SE_Play(0x10);
                            return;
                        }
                        break;
                    case 0x0:                       /* switch 1 */
                        if ((s32) (windowGetKeyInfo()->unk4 & 0x820) != 0) {
                            _CB.unkB010 = 1;
                            menuCB_SE_Play(0x12);
                            return;
                        }
                        if (((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) && ((s32) _CB.unkB118 == 4) && ((s32) _CB.unkB024 == 2)) {
                            _CB.unkB010 = 2;
                            menuCB_SE_Play(0x11);
                            return;
                        }
                        if ((s32) _CB.unkB014 == -1) {
                            temp_r29_20 = windowGetKeyInfo2()->unk4;
                            if ((s32) ((windowGetKeyInfo()->unk4 | temp_r29_20) & 1) != 0) {
                                if ((s32) _CB.unkB118 != 0) {
                                    _menuCB_Rule_Page_Chenge_Init__Fv();
                                    _CB.unkB118 -= 1;
                                    menuCB_SE_Play(0x15);
                                    menuCB_SE_Play(0x14);
                                    return;
                                }
                            } else {
                                temp_r29_21 = windowGetKeyInfo2()->unk4;
                                if (((s32) ((windowGetKeyInfo()->unk4 | temp_r29_21) & 2) != 0) && ((s32) _CB.unkB118 != 3)) {
                                    _menuCB_Rule_Page_Chenge_Init__Fv();
                                    _CB.unkB118 += 1;
                                    menuCB_SE_Play(0x15);
                                    menuCB_SE_Play(0x14);
                                    return;
                                }
                            }
                        } else {
                            if ((s32) (windowGetKeyInfo()->unk4 & 0x10) != 0) {
                                menuCBRule_Copy(&_ruleTempBuff_DB, _CB.unk9C78);
                                _CB.unkB11C = (_CB.unkB118 + 1) * 0x10;
                                switch ((s32) _CB.unkB118) { /* switch 10; irregular */
                                case 0:             /* switch 10 */
                                    _CB.unkB11C += _CB.unkB014;
                                    switch ((s32) _CB.unkB014) { /* switch 11; irregular */
                                    default:        /* switch 11 */
                                        _ruleCursol.unk0 = 0;
                                        _ruleCursol.unk4 = 0;
                                        break;
                                    case 2:         /* switch 11 */
                                        if ((s32) ((s16) _CB.unk9C78->unk14 & 0x8000) != 0) {
                                            _ruleCursol.unk8 = 2;
                                        } else {
                                            _ruleCursol.unk8 = 0;
                                        }
                                        break;
                                    case 3:         /* switch 11 */
                                        if ((s32) ((s16) _CB.unk9C78->unk16 & 0x8000) != 0) {
                                            _ruleCursol.unkC = 2;
                                        } else {
                                            _ruleCursol.unkC = 0;
                                        }
                                        break;
                                    case 4:         /* switch 11 */
                                        if ((s16) _CB.unk9C78->unk1C == 1) {
                                            _ruleCursol.unk10 = 1;
                                        } else {
                                            _ruleCursol.unk10 = 0;
                                        }
                                        break;
                                    }
                                    break;
                                case 1:             /* switch 10 */
                                    _CB.unkB11C += _CB.unkB018;
                                    break;
                                case 2:             /* switch 10 */
                                    _CB.unkB11C += _CB.unkB01C;
                                    break;
                                case 3:             /* switch 10 */
                                    _CB.unkB11C += _CB.unkB020;
                                    break;
                                case 4:             /* switch 10 */
                                    _CB.unkB11C += _CB.unkB024;
                                    break;
                                }
                                menuCB_SE_Play(0x11);
                            }
                            if ((s32) (windowGetKeyRepeat() & 1) != 0) {
                                switch ((s32) _CB.unkB118) { /* switch 12; irregular */
                                case 0:             /* switch 12 */
                                    if ((s32) _CB.unkB014 != 0) {
                                        _CB.unkB014 -= 1;
                                        menuCB_SE_Play(0x10);
                                        return;
                                    }
                                    break;
                                case 1:             /* switch 12 */
                                    if ((s32) _CB.unkB018 == 0) {
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 -= 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    _CB.unkB018 -= 1;
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 2:             /* switch 12 */
                                    if ((s32) _CB.unkB01C == 0) {
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 -= 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    _CB.unkB01C -= 1;
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 3:             /* switch 12 */
                                    if ((s32) _CB.unkB020 == 0) {
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 -= 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    _CB.unkB020 -= 1;
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 4:             /* switch 12 */
                                    if ((s32) _CB.unkB024 == 0) {
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 -= 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    _CB.unkB024 -= 1;
                                    menuCB_SE_Play(0x10);
                                    return;
                                }
                            } else if ((s32) (windowGetKeyRepeat() & 2) != 0) {
                                switch ((s32) _CB.unkB118) { /* switch 13; irregular */
                                case 0:             /* switch 13 */
                                    _CB.unkB014 += 1;
                                    if ((s32) _CB.unkB014 == 5) {
                                        _CB.unkB014 -= 1;
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 += 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 1:             /* switch 13 */
                                    _CB.unkB018 += 1;
                                    if ((s32) _CB.unkB018 == 3) {
                                        _CB.unkB018 -= 1;
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 += 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 2:             /* switch 13 */
                                    _CB.unkB01C += 1;
                                    if ((s32) _CB.unkB01C == 3) {
                                        _CB.unkB01C -= 1;
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 += 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 3:             /* switch 13 */
                                    _CB.unkB020 += 1;
                                    if ((s32) _CB.unkB020 == 4) {
                                        _CB.unkB020 -= 1;
                                        _menuCB_Rule_Page_Chenge_Init__Fv();
                                        _CB.unkB118 += 1;
                                        menuCB_SE_Play(0x15);
                                        menuCB_SE_Play(0x14);
                                        return;
                                    }
                                    menuCB_SE_Play(0x10);
                                    return;
                                case 4:             /* switch 13 */
                                    _CB.unkB024 += 1;
                                    if ((s32) _CB.unkB024 == 3) {
                                        _CB.unkB024 -= 1;
                                        return;
                                    }
                                    menuCB_SE_Play(0x10);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
#ifdef __cplusplus
}
#endif
