#include <game/menuBingoLayout.hpp>

// Layout views and callback contracts follow the original USA assembly.
#include <libc/stddef.h>
double sin(double x);
double cos(double x);
double __fabs(double x);
#define fabs(x) __fabs(x)

#ifdef __cplusplus
extern "C" {
#endif
extern u32 *bingo_data_number;
extern s16 lbl_804EAA00;
static BingoMsg SheetDocMsgIdx__6cBingo[0xB] = {
    { 0xDB25, 0xDB0B, 0xDAC1 },
    { 0xDB26, 0xDB0D, 0xDAC1 },
    { 0xDB27, 0xDB0F, 0xDAC1 },
    { 0xDB28, 0xDB11, 0xDAC2 },
    { 0xDB29, 0xDB13, 0xDAC2 },
    { 0xDB2A, 0xDB15, 0xDAC2 },
    { 0xDB2B, 0xDB17, 0xDAC3 },
    { 0xDB2C, 0xDB19, 0xDAC3 },
    { 0xDB2D, 0xDB1B, 0xDAC3 },
    { 0xDB2E, 0xDB1D, 0xDAC4 },
    { 0xDB2F, 0xDB1F, 0xDB21 },
};
static s32 MenuPkmMsgIdx__6cBingo[3] = { 0xDAE3, 0xDAE4, 0xDAE5 };
static BingoPokemon mPokemon__6cBingo[0xE];
static BingoState gBingo;
static s32 MenuEpMsgIdx__6cBingo[2] = { 0xDAEF, 0xDAF0 };
static u32 MenuBingoMsgIdx__6cBingo[2] = { 0xDB34, 0xDB35 };
static const u32 TopCurIdx__6cBingo[0xB] = { 0x521, 0x522, 0x523, 0x524, 0x525, 0x526, 0x527, 0x528, 0x529, 0x52A, 0x693 }; /* const */
static const u16 ClosePanelIdx__6cBingo[0x12] = {
    0x292,
    0x28E,
    0x28A,
    0x284,
    0x28D,
    0x28C,
    0x291,
    0x289,
    0x286,
    0x29E,
    0x28B,
    0x290,
    0x28F,
    0x283,
    0x288,
    0x293,
    0x285,
    0x287,
}; /* const */
static const u16 OpenPanelType__6cBingo[18] = {0x19E,0x1A0,0x19C,0x194,0x1A2,0x199,0x19D,0x19A,0x198,0x193,0x1A1,0x1A3,0x1A4,0x197,0x19B,0x195,0x196,0x19F};   /* const */


u8 menuBattleDeBingoGetMode(void) {
    return gBingo.unk122;
}

u8 menuBattleDeBingoGetMball(void) {
    return gBingo.unk129;
}

static inline s32 bingoFindPokemon(u32 player) {
    s32 index;
    for (index = 0; index < 14; index++) {
        if (mPokemon__6cBingo[index].unkC5 == player) {
            return index;
        }
    }
    return -1;
}

u8 menuBattleDeBingoGetEpoint(void) {
    s32 total = 0;
    s32 player;
    for (player = 0; player < 4; player++) {
        s32 index = bingoFindPokemon(player + 1);
        if (index == -1) break;
        total += mPokemon__6cBingo[index].unkC4;
    }
    return (u8)(total + gBingo.unk12A);
}

u8 menuBattleDeBingoGetNum(void) {
    if (getStaticSheet__10bingo_biosFv() != 0) {
        return getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, getStaticSheet__10bingo_biosFv());
    }
    return 0U;
}

s32 menuBattleDeBingoGetLine(void) {
    return getStaticResult__10bingo_biosFv() & 0xF;
}

s32 menuBattleDeBingoGetResult(void) {
    return ((u8)getStaticResult__10bingo_biosFv() >> 4U) & 0xF;
}

void menuBattleDeBingo(void) {
    GSfloorPush(0x388);
}

static inline BingoCell *bingoCell(BingoState *state, u32 panel) {
    return (BingoCell *)((u8 *)state + 8 + panel * sizeof(BingoCell));
}
static inline u8 bingoPanelOpen(BingoState *state, u32 panel) {
    return bingoCell(state, panel)->unk2;
}

static inline u8 bingoLineClear(BingoState *state, s32 line) {
    u32 i;
    switch (line) {
    case 0: case 1: case 2: case 3:
        for (i = 0; i < 4; i++) {
            if (bingoPanelOpen(state, line + i * 4) != 0) {
                if (i == 3) return 1;
            } else break;
        }
        break;
    case 4: case 5: case 6: case 7:
        for (i = 0; i < 4; i++) {
            if (bingoPanelOpen(state, (7 - line) * 4 + i) != 0) {
                if (i == 3) return 1;
            } else break;
        }
        break;
    case 8:
        for (i = 0; i < 4; i++) {
            if (bingoPanelOpen(state, 3 - i + i * 4) != 0) {
                if (i == 3) return 1;
            } else break;
        }
        break;
    case 9:
        for (i = 0; i < 4; i++) {
            if (bingoPanelOpen(state, i + i * 4) != 0) {
                if (i == 3) return 1;
            } else break;
        }
    }
    return 0;
}


static inline u8 bingoCompletedLines(BingoState *state) {
    u8 count = 0;
    s32 line;
    for (line = 0; line < 10; ++line) {
        if (bingoLineClear(state, line)) ++count;
    }
    return count;
}

s32 menuBingoPokemonDraw(BingoWindow *arg0, BingoSprite *arg1) {
    BingoPokemon *temp_r29;
    BingoPokemon *temp_r29_10;
    BingoPokemon *temp_r29_11;
    BingoPokemon *temp_r29_12;
    BingoPokemon *temp_r29_13;
    BingoPokemon *temp_r29_14;
    BingoPokemon *temp_r29_15;
    BingoPokemon *temp_r29_16;
    BingoPokemon *temp_r29_17;
    BingoPokemon *temp_r29_18;
    BingoPokemon *temp_r29_19;
    BingoPokemon *temp_r29_20;
    BingoPokemon *temp_r29_21;
    BingoPokemon *temp_r29_22;
    BingoPokemon *temp_r29_23;
    BingoPokemon *temp_r29_24;
    BingoPokemon *temp_r29_25;
    BingoPokemon *temp_r29_26;
    BingoPokemon *temp_r29_27;
    BingoPokemon *temp_r29_28;
    BingoPokemon *temp_r29_29;
    BingoPokemon *temp_r29_2;
    BingoPokemon *temp_r29_30;
    BingoPokemon *temp_r29_31;
    BingoPokemon *temp_r29_32;
    BingoPokemon *temp_r29_33;
    BingoPokemon *temp_r29_34;
    BingoPokemon *temp_r29_35;
    BingoPokemon *temp_r29_3;
    BingoPokemon *temp_r29_4;
    BingoPokemon *temp_r29_5;
    BingoPokemon *temp_r29_6;
    BingoPokemon *temp_r29_7;
    BingoPokemon *temp_r29_8;
    BingoPokemon *temp_r29_9;
    BingoPokemon *temp_r4;
    BingoPokemon *temp_r4_2;
    BingoPokemon *temp_r4_3;
    BingoPokemon *temp_r4_4;
    BingoPokemon *temp_r4_5;
    BingoPokemon *temp_r5;
    BingoPokemon *temp_r5_10;
    BingoPokemon *temp_r5_2;
    BingoPokemon *temp_r5_3;
    BingoPokemon *temp_r5_4;
    BingoPokemon *temp_r5_5;
    BingoPokemon *temp_r5_6;
    BingoPokemon *temp_r5_7;
    BingoPokemon *temp_r5_8;
    BingoPokemon *temp_r5_9;
    BingoPokemon *temp_r6;
    BingoPokemon *temp_r6_10;
    BingoPokemon *temp_r6_11;
    BingoPokemon *temp_r6_12;
    BingoPokemon *temp_r6_13;
    BingoPokemon *temp_r6_14;
    BingoPokemon *temp_r6_15;
    BingoPokemon *temp_r6_16;
    BingoPokemon *temp_r6_17;
    BingoPokemon *temp_r6_18;
    BingoPokemon *temp_r6_19;
    BingoPokemon *temp_r6_20;
    BingoPokemon *temp_r6_2;
    BingoPokemon *temp_r6_3;
    BingoPokemon *temp_r6_4;
    BingoPokemon *temp_r6_5;
    BingoPokemon *temp_r6_6;
    BingoPokemon *temp_r6_7;
    BingoPokemon *temp_r6_8;
    BingoPokemon *temp_r6_9;
    BingoPokemon *var_r29;
    BingoPokemon *var_r4_5;
    BingoPokemon *var_r5;
    BingoPokemon *var_r5_8;
    BingoPokemon *var_r6;
    BingoPokemon *var_r6_2;
    BingoPokemon *var_r6_3;
    BingoPokemon *var_r6_4;
    s16 temp_r0;
    s32 temp_r28;
    s32 var_ctr;
    s32 var_ctr_10;
    s32 var_ctr_11;
    s32 var_ctr_12;
    s32 var_ctr_13;
    s32 var_ctr_14;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_ctr_6;
    s32 var_ctr_7;
    s32 var_ctr_8;
    s32 var_ctr_9;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_4;
    s32 var_r4_6;
    s32 var_r5_10;
    s32 var_r5_11;
    s32 var_r5_14;
    s32 var_r5_5;
    s32 var_r5_7;
    u16 temp_r3_14;
    u16 temp_r3_5;
    u32 temp_r3;
    u32 temp_r3_10;
    u32 temp_r3_11;
    u32 temp_r3_12;
    u32 temp_r3_13;
    u32 temp_r3_15;
    u32 temp_r3_16;
    u32 temp_r3_17;
    u32 temp_r3_18;
    u32 temp_r3_20;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 temp_r3_4;
    u32 temp_r3_6;
    u32 temp_r3_8;
    u32 temp_r3_9;
    u32 var_r5_12;
    u32 var_r5_13;
    u32 var_r5_2;
    u32 var_r5_3;
    u32 var_r5_4;
    u32 var_r5_6;
    u32 var_r5_9;
    u8 temp_r26;
    u8 temp_r3_19;
    u8 temp_r3_7;
    u8 var_r26;

    var_r26 = 0;
    menuSubCalcColor();
    var_r29 = mPokemon__6cBingo;
    var_r4 = 0;
    var_r5 = mPokemon__6cBingo;
    temp_r3 = gBingo.unk12C + 1;
    var_ctr = 2;
loop_1:
    if (temp_r3 != (u8) var_r5->unkC5) {
        goto block_3;
    }
    goto block_17;
block_3:
    var_r4 += 1;
    if (temp_r3 != (u8) var_r5[1].unkC5) {
        goto block_5;
    }
    goto block_17;
block_5:
    temp_r5 = (BingoPokemon *)((u8 *)&var_r5[1] + 0xC8);
    var_r4 += 1;
    if (temp_r3 != (u8) temp_r5->unkC5) {
        goto block_7;
    }
    goto block_17;
block_7:
    temp_r5_2 = (BingoPokemon *)((u8 *)temp_r5 + 0xC8);
    var_r4 += 1;
    if (temp_r3 != (u8) temp_r5_2->unkC5) {
        goto block_9;
    }
    goto block_17;
block_9:
    temp_r5_3 = (BingoPokemon *)((u8 *)temp_r5_2 + 0xC8);
    var_r4 += 1;
    if (temp_r3 != (u8) temp_r5_3->unkC5) {
        goto block_11;
    }
    goto block_17;
block_11:
    temp_r5_4 = (BingoPokemon *)((u8 *)temp_r5_3 + 0xC8);
    var_r4 += 1;
    if (temp_r3 != (u8) temp_r5_4->unkC5) {
        goto block_13;
    }
    goto block_17;
block_13:
    temp_r5_5 = (BingoPokemon *)((u8 *)temp_r5_4 + 0xC8);
    var_r4 += 1;
    if (temp_r3 != (u8) temp_r5_5->unkC5) {
        goto block_15;
    }
    goto block_17;
block_15:
    var_r5 = (BingoPokemon *)((u8 *)temp_r5_5 + 0xC8);
    var_r4 += 1;
    var_ctr -= 1;
    if (var_ctr != 0) {
        goto loop_1;
    }
    var_r4 = -1;
block_17:
    temp_r0 = arg1->unk6;
    temp_r28 = winSpriteGetLayerID(arg0, arg1);
    if (temp_r0 == 0x898) {
        goto block_155;
    }
    if (temp_r0 >= 0x898) {
        goto block_36;
    }
    if (temp_r0 == 0x888) {
        goto block_208;
    }
    if (temp_r0 >= 0x888) {
        goto block_28;
    }
    if (temp_r0 == 0x5ED) {
        goto block_72;
    }
    if (temp_r0 >= 0x5ED) {
        goto block_25;
    }
    if (temp_r0 == 0x5EB) {
        goto block_91;
    }
    goto block_310;
block_25:
    if (temp_r0 >= 0x87F) {
        goto block_288;
    }
    if (temp_r0 >= 0x5EF) {
        goto block_310;
    }
    goto block_53;
block_28:
    if (temp_r0 == 0x88C) {
        goto block_310;
    }
    if (temp_r0 >= 0x88C) {
        goto block_33;
    }
    if (temp_r0 == 0x88A) {
        goto block_156;
    }
    if (temp_r0 >= 0x88A) {
        goto block_113;
    }
    goto block_310;
block_33:
    if (temp_r0 == 0x896) {
        goto block_207;
    }
    if (temp_r0 >= 0x896) {
        goto block_310;
    }
    goto block_287;
block_36:
    if (temp_r0 == 0x8A8) {
        goto block_310;
    }
    if (temp_r0 >= 0x8A8) {
        goto block_46;
    }
    if (temp_r0 == 0x8A4) {
        goto block_206;
    }
    if (temp_r0 >= 0x8A4) {
        goto block_43;
    }
    if (temp_r0 == 0x89A) {
        goto block_310;
    }
    if (temp_r0 >= 0x89A) {
        goto block_286;
    }
    goto block_112;
block_43:
    if (temp_r0 == 0x8A6) {
        goto block_154;
    }
    if (temp_r0 >= 0x8A6) {
        goto block_111;
    }
    goto block_310;
block_46:
    if (temp_r0 == 0x8B4) {
        goto block_153;
    }
    if (temp_r0 >= 0x8B4) {
        goto block_51;
    }
    if (temp_r0 == 0x8B2) {
        goto block_205;
    }
    if (temp_r0 >= 0x8B2) {
        goto block_310;
    }
    goto block_285;
block_51:
    if (temp_r0 >= 0x8B6) {
        goto block_310;
    }
    goto block_110;
block_53:
    var_r5_2 = 0;
    temp_r3_2 = gBingo.unk12C + 1;
    var_ctr_2 = 2;
loop_54:
    if (temp_r3_2 != (u8) var_r29->unkC5) {
        goto block_56;
    }
    goto block_70;
block_56:
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) var_r29[1].unkC5) {
        goto block_58;
    }
    goto block_70;
block_58:
    temp_r29 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) temp_r29->unkC5) {
        goto block_60;
    }
    goto block_70;
block_60:
    temp_r29_2 = (BingoPokemon *)((u8 *)temp_r29 + 0xC8);
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) temp_r29_2->unkC5) {
        goto block_62;
    }
    goto block_70;
block_62:
    temp_r29_3 = (BingoPokemon *)((u8 *)temp_r29_2 + 0xC8);
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) temp_r29_3->unkC5) {
        goto block_64;
    }
    goto block_70;
block_64:
    temp_r29_4 = (BingoPokemon *)((u8 *)temp_r29_3 + 0xC8);
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) temp_r29_4->unkC5) {
        goto block_66;
    }
    goto block_70;
block_66:
    temp_r29_5 = (BingoPokemon *)((u8 *)temp_r29_4 + 0xC8);
    var_r5_2 += 1;
    if (temp_r3_2 != (u8) temp_r29_5->unkC5) {
        goto block_68;
    }
    goto block_70;
block_68:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_5 + 0xC8);
    var_r5_2 += 1;
    var_ctr_2 -= 1;
    if (var_ctr_2 != 0) {
        goto loop_54;
    }
    var_r5_2 = -1U;
block_70:
    temp_r3_3 = wazaGetStatus(0, getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_2), 1, 0);
    if (temp_r3_3 == 0) {
        goto block_310;
    }
    arg1->unk4C = 0xDB39;
    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB44U));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(temp_r3_3));
    GSmsgPrint2(winSpriteGetLayerID(arg0, arg1), 0x5A, 0, arg0->unk93 | ~0xFF, 0x4277U);
    goto block_310;
block_72:
    var_r5_3 = 0;
    temp_r3_4 = gBingo.unk12C + 1;
    var_ctr_3 = 2;
loop_73:
    if (temp_r3_4 != (u8) var_r29->unkC5) {
        goto block_75;
    }
    goto block_89;
block_75:
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) var_r29[1].unkC5) {
        goto block_77;
    }
    goto block_89;
block_77:
    temp_r29_6 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) temp_r29_6->unkC5) {
        goto block_79;
    }
    goto block_89;
block_79:
    temp_r29_7 = (BingoPokemon *)((u8 *)temp_r29_6 + 0xC8);
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) temp_r29_7->unkC5) {
        goto block_81;
    }
    goto block_89;
block_81:
    temp_r29_8 = (BingoPokemon *)((u8 *)temp_r29_7 + 0xC8);
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) temp_r29_8->unkC5) {
        goto block_83;
    }
    goto block_89;
block_83:
    temp_r29_9 = (BingoPokemon *)((u8 *)temp_r29_8 + 0xC8);
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) temp_r29_9->unkC5) {
        goto block_85;
    }
    goto block_89;
block_85:
    temp_r29_10 = (BingoPokemon *)((u8 *)temp_r29_9 + 0xC8);
    var_r5_3 += 1;
    if (temp_r3_4 != (u8) temp_r29_10->unkC5) {
        goto block_87;
    }
    goto block_89;
block_87:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_10 + 0xC8);
    var_r5_3 += 1;
    var_ctr_3 -= 1;
    if (var_ctr_3 != 0) {
        goto loop_73;
    }
    var_r5_3 = -1U;
block_89:
    temp_r3_5 = zokuseiBiosGetSpriteID(wazaDB_GetZokuseiDataId(getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_3)));
    if (temp_r3_5 == 0) {
        goto block_310;
    }
    windowDrawSprite(0, 0, arg0, (BingoSprite *) temp_r3_5, 0, temp_r28);
    goto block_310;
block_91:
    var_r5_4 = 0;
    temp_r3_6 = gBingo.unk12C + 1;
    var_ctr_4 = 2;
loop_92:
    if (temp_r3_6 != (u8) var_r29->unkC5) {
        goto block_94;
    }
    goto block_108;
block_94:
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) var_r29[1].unkC5) {
        goto block_96;
    }
    goto block_108;
block_96:
    temp_r29_11 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) temp_r29_11->unkC5) {
        goto block_98;
    }
    goto block_108;
block_98:
    temp_r29_12 = (BingoPokemon *)((u8 *)temp_r29_11 + 0xC8);
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) temp_r29_12->unkC5) {
        goto block_100;
    }
    goto block_108;
block_100:
    temp_r29_13 = (BingoPokemon *)((u8 *)temp_r29_12 + 0xC8);
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) temp_r29_13->unkC5) {
        goto block_102;
    }
    goto block_108;
block_102:
    temp_r29_14 = (BingoPokemon *)((u8 *)temp_r29_13 + 0xC8);
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) temp_r29_14->unkC5) {
        goto block_104;
    }
    goto block_108;
block_104:
    temp_r29_15 = (BingoPokemon *)((u8 *)temp_r29_14 + 0xC8);
    var_r5_4 += 1;
    if (temp_r3_6 != (u8) temp_r29_15->unkC5) {
        goto block_106;
    }
    goto block_108;
block_106:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_15 + 0xC8);
    var_r5_4 += 1;
    var_ctr_4 -= 1;
    if (var_ctr_4 != 0) {
        goto loop_92;
    }
    var_r5_4 = -1U;
block_108:
    temp_r26 = getPanelTokusei__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_4);
    temp_r3_7 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(&mPokemon__6cBingo[var_r4]));
    if (temp_r3_7 == 0) {
        goto block_310;
    }
    arg1->unk4C = 0xDB3A;
    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB45U));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16) temp_r3_7))));
    GSmsgPrint2(winSpriteGetLayerID(arg0, arg1), 0x5A, 0, arg0->unk93 | ~0xFF, 0x4277U);
    goto block_310;
block_110:
    var_r26 = 1;
block_111:
    var_r26 += 1;
block_112:
    var_r26 += 1;
block_113:
    var_r4_2 = 0;
loop_114:
    var_r6 = mPokemon__6cBingo;
    var_r5_5 = 0;
    temp_r3_8 = var_r4_2 + 1;
    var_ctr_5 = 2;
loop_115:
    if (temp_r3_8 != (u8) var_r6->unkC5) {
        goto block_117;
    }
    goto block_131;
block_117:
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) var_r6[1].unkC5) {
        goto block_119;
    }
    goto block_131;
block_119:
    temp_r6 = (BingoPokemon *)((u8 *)&var_r6[1] + 0xC8);
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) temp_r6->unkC5) {
        goto block_121;
    }
    goto block_131;
block_121:
    temp_r6_2 = (BingoPokemon *)((u8 *)temp_r6 + 0xC8);
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) temp_r6_2->unkC5) {
        goto block_123;
    }
    goto block_131;
block_123:
    temp_r6_3 = (BingoPokemon *)((u8 *)temp_r6_2 + 0xC8);
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) temp_r6_3->unkC5) {
        goto block_125;
    }
    goto block_131;
block_125:
    temp_r6_4 = (BingoPokemon *)((u8 *)temp_r6_3 + 0xC8);
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) temp_r6_4->unkC5) {
        goto block_127;
    }
    goto block_131;
block_127:
    temp_r6_5 = (BingoPokemon *)((u8 *)temp_r6_4 + 0xC8);
    var_r5_5 += 1;
    if (temp_r3_8 != (u8) temp_r6_5->unkC5) {
        goto block_129;
    }
    goto block_131;
block_129:
    var_r6 = (BingoPokemon *)((u8 *)temp_r6_5 + 0xC8);
    var_r5_5 += 1;
    var_ctr_5 -= 1;
    if (var_ctr_5 != 0) {
        goto loop_115;
    }
    var_r5_5 = -1;
block_131:
    if (var_r5_5 == -1) {
        goto block_133;
    }
    var_r4_2 += 1;
    if (var_r4_2 < 4) {
        goto loop_114;
    }
block_133:
    if (var_r26 >= (u32) var_r4_2) {
        goto block_310;
    }
    var_r5_6 = 0;
    temp_r3_9 = var_r26 + 1;
    var_ctr_6 = 2;
loop_135:
    if (temp_r3_9 != (u8) var_r29->unkC5) {
        goto block_137;
    }
    goto block_151;
block_137:
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) var_r29[1].unkC5) {
        goto block_139;
    }
    goto block_151;
block_139:
    temp_r29_16 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) temp_r29_16->unkC5) {
        goto block_141;
    }
    goto block_151;
block_141:
    temp_r29_17 = (BingoPokemon *)((u8 *)temp_r29_16 + 0xC8);
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) temp_r29_17->unkC5) {
        goto block_143;
    }
    goto block_151;
block_143:
    temp_r29_18 = (BingoPokemon *)((u8 *)temp_r29_17 + 0xC8);
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) temp_r29_18->unkC5) {
        goto block_145;
    }
    goto block_151;
block_145:
    temp_r29_19 = (BingoPokemon *)((u8 *)temp_r29_18 + 0xC8);
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) temp_r29_19->unkC5) {
        goto block_147;
    }
    goto block_151;
block_147:
    temp_r29_20 = (BingoPokemon *)((u8 *)temp_r29_19 + 0xC8);
    var_r5_6 += 1;
    if (temp_r3_9 != (u8) temp_r29_20->unkC5) {
        goto block_149;
    }
    goto block_151;
block_149:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_20 + 0xC8);
    var_r5_6 += 1;
    var_ctr_6 -= 1;
    if (var_ctr_6 != 0) {
        goto loop_135;
    }
    var_r5_6 = -1U;
block_151:
    temp_r3_10 = wazaGetStatus(0, getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_6), 1, 0);
    if (temp_r3_10 == 0) {
        goto block_310;
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB44U));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(temp_r3_10));
    arg1->unk4C = 0xDB39;
    GSmsgPrint2(winSpriteGetLayerID(arg0, arg1), 0x5A, 0, arg0->unk93 | ~0xFF, 0x4277U);
    goto block_310;
block_153:
    var_r26 = 1;
block_154:
    var_r26 += 1;
block_155:
    var_r26 += 1;
block_156:
    var_r4_3 = 0;
loop_157:
    var_r6_2 = mPokemon__6cBingo;
    var_r5_7 = 0;
    temp_r3_11 = var_r4_3 + 1;
    var_ctr_7 = 2;
loop_158:
    if (temp_r3_11 != (u8) var_r6_2->unkC5) {
        goto block_160;
    }
    goto block_174;
block_160:
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) var_r6_2[1].unkC5) {
        goto block_162;
    }
    goto block_174;
block_162:
    temp_r6_6 = (BingoPokemon *)((u8 *)&var_r6_2[1] + 0xC8);
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) temp_r6_6->unkC5) {
        goto block_164;
    }
    goto block_174;
block_164:
    temp_r6_7 = (BingoPokemon *)((u8 *)temp_r6_6 + 0xC8);
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) temp_r6_7->unkC5) {
        goto block_166;
    }
    goto block_174;
block_166:
    temp_r6_8 = (BingoPokemon *)((u8 *)temp_r6_7 + 0xC8);
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) temp_r6_8->unkC5) {
        goto block_168;
    }
    goto block_174;
block_168:
    temp_r6_9 = (BingoPokemon *)((u8 *)temp_r6_8 + 0xC8);
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) temp_r6_9->unkC5) {
        goto block_170;
    }
    goto block_174;
block_170:
    temp_r6_10 = (BingoPokemon *)((u8 *)temp_r6_9 + 0xC8);
    var_r5_7 += 1;
    if (temp_r3_11 != (u8) temp_r6_10->unkC5) {
        goto block_172;
    }
    goto block_174;
block_172:
    var_r6_2 = (BingoPokemon *)((u8 *)temp_r6_10 + 0xC8);
    var_r5_7 += 1;
    var_ctr_7 -= 1;
    if (var_ctr_7 != 0) {
        goto loop_158;
    }
    var_r5_7 = -1;
block_174:
    if (var_r5_7 == -1) {
        goto block_176;
    }
    var_r4_3 += 1;
    if (var_r4_3 < 4) {
        goto loop_157;
    }
block_176:
    if (var_r26 >= (u32) var_r4_3) {
        goto block_310;
    }
    var_r5_8 = mPokemon__6cBingo;
    temp_r3_12 = var_r26 + 1;
    var_ctr_8 = 2;
loop_178:
    if (temp_r3_12 == (u8) var_r5_8->unkC5) {
        goto block_186;
    }
    if (temp_r3_12 == (u8) var_r5_8[1].unkC5) {
        goto block_186;
    }
    temp_r5_6 = (BingoPokemon *)((u8 *)&var_r5_8[1] + 0xC8);
    if (temp_r3_12 == (u8) temp_r5_6->unkC5) {
        goto block_186;
    }
    temp_r5_7 = (BingoPokemon *)((u8 *)temp_r5_6 + 0xC8);
    if (temp_r3_12 == (u8) temp_r5_7->unkC5) {
        goto block_186;
    }
    temp_r5_8 = (BingoPokemon *)((u8 *)temp_r5_7 + 0xC8);
    if (temp_r3_12 == (u8) temp_r5_8->unkC5) {
        goto block_186;
    }
    temp_r5_9 = (BingoPokemon *)((u8 *)temp_r5_8 + 0xC8);
    if (temp_r3_12 == (u8) temp_r5_9->unkC5) {
        goto block_186;
    }
    temp_r5_10 = (BingoPokemon *)((u8 *)temp_r5_9 + 0xC8);
    if (temp_r3_12 == (u8) temp_r5_10->unkC5) {
        goto block_186;
    }
    var_r5_8 = (BingoPokemon *)((u8 *)temp_r5_10 + 0xC8);
    var_ctr_8 -= 1;
    if (var_ctr_8 != 0) {
        goto loop_178;
    }
block_186:
    var_r5_9 = 0;
    temp_r3_13 = var_r26 + 1;
    var_ctr_9 = 2;
loop_187:
    if (temp_r3_13 != (u8) var_r29->unkC5) {
        goto block_189;
    }
    goto block_203;
block_189:
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) var_r29[1].unkC5) {
        goto block_191;
    }
    goto block_203;
block_191:
    temp_r29_21 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) temp_r29_21->unkC5) {
        goto block_193;
    }
    goto block_203;
block_193:
    temp_r29_22 = (BingoPokemon *)((u8 *)temp_r29_21 + 0xC8);
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) temp_r29_22->unkC5) {
        goto block_195;
    }
    goto block_203;
block_195:
    temp_r29_23 = (BingoPokemon *)((u8 *)temp_r29_22 + 0xC8);
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) temp_r29_23->unkC5) {
        goto block_197;
    }
    goto block_203;
block_197:
    temp_r29_24 = (BingoPokemon *)((u8 *)temp_r29_23 + 0xC8);
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) temp_r29_24->unkC5) {
        goto block_199;
    }
    goto block_203;
block_199:
    temp_r29_25 = (BingoPokemon *)((u8 *)temp_r29_24 + 0xC8);
    var_r5_9 += 1;
    if (temp_r3_13 != (u8) temp_r29_25->unkC5) {
        goto block_201;
    }
    goto block_203;
block_201:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_25 + 0xC8);
    var_r5_9 += 1;
    var_ctr_9 -= 1;
    if (var_ctr_9 != 0) {
        goto loop_187;
    }
    var_r5_9 = -1U;
block_203:
    temp_r3_14 = zokuseiBiosGetSpriteID(wazaDB_GetZokuseiDataId(getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_9)));
    if (temp_r3_14 == 0) {
        goto block_310;
    }
    windowDrawSprite(0, 0, arg0, (BingoSprite *) temp_r3_14, 0, temp_r28);
    goto block_310;
block_205:
    var_r26 = 1;
block_206:
    var_r26 += 1;
block_207:
    var_r26 += 1;
block_208:
    var_r4_4 = 0;
loop_209:
    var_r6_3 = mPokemon__6cBingo;
    var_r5_10 = 0;
    temp_r3_15 = var_r4_4 + 1;
    var_ctr_10 = 2;
loop_210:
    if (temp_r3_15 != (u8) var_r6_3->unkC5) {
        goto block_212;
    }
    goto block_226;
block_212:
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) var_r6_3[1].unkC5) {
        goto block_214;
    }
    goto block_226;
block_214:
    temp_r6_11 = (BingoPokemon *)((u8 *)&var_r6_3[1] + 0xC8);
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) temp_r6_11->unkC5) {
        goto block_216;
    }
    goto block_226;
block_216:
    temp_r6_12 = (BingoPokemon *)((u8 *)temp_r6_11 + 0xC8);
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) temp_r6_12->unkC5) {
        goto block_218;
    }
    goto block_226;
block_218:
    temp_r6_13 = (BingoPokemon *)((u8 *)temp_r6_12 + 0xC8);
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) temp_r6_13->unkC5) {
        goto block_220;
    }
    goto block_226;
block_220:
    temp_r6_14 = (BingoPokemon *)((u8 *)temp_r6_13 + 0xC8);
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) temp_r6_14->unkC5) {
        goto block_222;
    }
    goto block_226;
block_222:
    temp_r6_15 = (BingoPokemon *)((u8 *)temp_r6_14 + 0xC8);
    var_r5_10 += 1;
    if (temp_r3_15 != (u8) temp_r6_15->unkC5) {
        goto block_224;
    }
    goto block_226;
block_224:
    var_r6_3 = (BingoPokemon *)((u8 *)temp_r6_15 + 0xC8);
    var_r5_10 += 1;
    var_ctr_10 -= 1;
    if (var_ctr_10 != 0) {
        goto loop_210;
    }
    var_r5_10 = -1;
block_226:
    if (var_r5_10 == -1) {
        goto block_228;
    }
    var_r4_4 += 1;
    if (var_r4_4 < 4) {
        goto loop_209;
    }
block_228:
    if (var_r26 >= (u32) var_r4_4) {
        goto block_310;
    }
    var_r4_5 = mPokemon__6cBingo;
    var_r5_11 = 0;
    temp_r3_16 = var_r26 + 1;
    var_ctr_11 = 2;
loop_230:
    if (temp_r3_16 != (u8) var_r4_5->unkC5) {
        goto block_232;
    }
    goto block_246;
block_232:
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) var_r4_5[1].unkC5) {
        goto block_234;
    }
    goto block_246;
block_234:
    temp_r4 = (BingoPokemon *)((u8 *)&var_r4_5[1] + 0xC8);
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) temp_r4->unkC5) {
        goto block_236;
    }
    goto block_246;
block_236:
    temp_r4_2 = (BingoPokemon *)((u8 *)temp_r4 + 0xC8);
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) temp_r4_2->unkC5) {
        goto block_238;
    }
    goto block_246;
block_238:
    temp_r4_3 = (BingoPokemon *)((u8 *)temp_r4_2 + 0xC8);
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) temp_r4_3->unkC5) {
        goto block_240;
    }
    goto block_246;
block_240:
    temp_r4_4 = (BingoPokemon *)((u8 *)temp_r4_3 + 0xC8);
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) temp_r4_4->unkC5) {
        goto block_242;
    }
    goto block_246;
block_242:
    temp_r4_5 = (BingoPokemon *)((u8 *)temp_r4_4 + 0xC8);
    var_r5_11 += 1;
    if (temp_r3_16 != (u8) temp_r4_5->unkC5) {
        goto block_244;
    }
    goto block_246;
block_244:
    var_r4_5 = (BingoPokemon *)((u8 *)temp_r4_5 + 0xC8);
    var_r5_11 += 1;
    var_ctr_11 -= 1;
    if (var_ctr_11 != 0) {
        goto loop_230;
    }
    var_r5_11 = -1;
block_246:
    if ((s16) var_r26 >= 0) {
        goto block_265;
    }
    var_r5_12 = 0;
    temp_r3_17 = gBingo.unk12C + 1;
    var_ctr_12 = 2;
loop_248:
    if (temp_r3_17 != (u8) var_r29->unkC5) {
        goto block_250;
    }
    goto block_264;
block_250:
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) var_r29[1].unkC5) {
        goto block_252;
    }
    goto block_264;
block_252:
    temp_r29_26 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) temp_r29_26->unkC5) {
        goto block_254;
    }
    goto block_264;
block_254:
    temp_r29_27 = (BingoPokemon *)((u8 *)temp_r29_26 + 0xC8);
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) temp_r29_27->unkC5) {
        goto block_256;
    }
    goto block_264;
block_256:
    temp_r29_28 = (BingoPokemon *)((u8 *)temp_r29_27 + 0xC8);
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) temp_r29_28->unkC5) {
        goto block_258;
    }
    goto block_264;
block_258:
    temp_r29_29 = (BingoPokemon *)((u8 *)temp_r29_28 + 0xC8);
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) temp_r29_29->unkC5) {
        goto block_260;
    }
    goto block_264;
block_260:
    temp_r29_30 = (BingoPokemon *)((u8 *)temp_r29_29 + 0xC8);
    var_r5_12 += 1;
    if (temp_r3_17 != (u8) temp_r29_30->unkC5) {
        goto block_262;
    }
    goto block_264;
block_262:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_30 + 0xC8);
    var_r5_12 += 1;
    var_ctr_12 -= 1;
    if (var_ctr_12 != 0) {
        goto loop_248;
    }
    var_r5_12 = -1U;
block_264:
    getPanelTokusei__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_12);
    goto block_283;
block_265:
    var_r5_13 = 0;
    temp_r3_18 = (s16) var_r26 + 1;
    var_ctr_13 = 2;
loop_266:
    if (temp_r3_18 != (u8) var_r29->unkC5) {
        goto block_268;
    }
    goto block_282;
block_268:
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) var_r29[1].unkC5) {
        goto block_270;
    }
    goto block_282;
block_270:
    temp_r29_31 = (BingoPokemon *)((u8 *)&var_r29[1] + 0xC8);
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) temp_r29_31->unkC5) {
        goto block_272;
    }
    goto block_282;
block_272:
    temp_r29_32 = (BingoPokemon *)((u8 *)temp_r29_31 + 0xC8);
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) temp_r29_32->unkC5) {
        goto block_274;
    }
    goto block_282;
block_274:
    temp_r29_33 = (BingoPokemon *)((u8 *)temp_r29_32 + 0xC8);
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) temp_r29_33->unkC5) {
        goto block_276;
    }
    goto block_282;
block_276:
    temp_r29_34 = (BingoPokemon *)((u8 *)temp_r29_33 + 0xC8);
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) temp_r29_34->unkC5) {
        goto block_278;
    }
    goto block_282;
block_278:
    temp_r29_35 = (BingoPokemon *)((u8 *)temp_r29_34 + 0xC8);
    var_r5_13 += 1;
    if (temp_r3_18 != (u8) temp_r29_35->unkC5) {
        goto block_280;
    }
    goto block_282;
block_280:
    var_r29 = (BingoPokemon *)((u8 *)temp_r29_35 + 0xC8);
    var_r5_13 += 1;
    var_ctr_13 -= 1;
    if (var_ctr_13 != 0) {
        goto loop_266;
    }
    var_r5_13 = -1U;
block_282:
    getPanelTokusei__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, var_r5_13);
block_283:
    temp_r3_19 = pokemonDB_GetTokuseiDataId(pokemon_GetPokemonDataId(&mPokemon__6cBingo[var_r5_11]));
    if (temp_r3_19 == 0) {
        goto block_310;
    }
    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB45U));
    msgctrlSetValue(0x4D, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr((u16) temp_r3_19))));
    arg1->unk4C = 0xDB3A;
    GSmsgPrint2(winSpriteGetLayerID(arg0, arg1), 0x5A, 0, arg0->unk93 | ~0xFF, 0x4277U);
    goto block_310;
block_285:
    var_r26 = 1;
block_286:
    var_r26 += 1;
block_287:
    var_r26 += 1;
block_288:
    winSpriteSetDisp(arg1, 0);
    var_r4_6 = 0;
loop_289:
    var_r6_4 = mPokemon__6cBingo;
    var_r5_14 = 0;
    temp_r3_20 = var_r4_6 + 1;
    var_ctr_14 = 2;
loop_290:
    if (temp_r3_20 != (u8) var_r6_4->unkC5) {
        goto block_292;
    }
    goto block_306;
block_292:
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) var_r6_4[1].unkC5) {
        goto block_294;
    }
    goto block_306;
block_294:
    temp_r6_16 = (BingoPokemon *)((u8 *)&var_r6_4[1] + 0xC8);
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) temp_r6_16->unkC5) {
        goto block_296;
    }
    goto block_306;
block_296:
    temp_r6_17 = (BingoPokemon *)((u8 *)temp_r6_16 + 0xC8);
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) temp_r6_17->unkC5) {
        goto block_298;
    }
    goto block_306;
block_298:
    temp_r6_18 = (BingoPokemon *)((u8 *)temp_r6_17 + 0xC8);
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) temp_r6_18->unkC5) {
        goto block_300;
    }
    goto block_306;
block_300:
    temp_r6_19 = (BingoPokemon *)((u8 *)temp_r6_18 + 0xC8);
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) temp_r6_19->unkC5) {
        goto block_302;
    }
    goto block_306;
block_302:
    temp_r6_20 = (BingoPokemon *)((u8 *)temp_r6_19 + 0xC8);
    var_r5_14 += 1;
    if (temp_r3_20 != (u8) temp_r6_20->unkC5) {
        goto block_304;
    }
    goto block_306;
block_304:
    var_r6_4 = (BingoPokemon *)((u8 *)temp_r6_20 + 0xC8);
    var_r5_14 += 1;
    var_ctr_14 -= 1;
    if (var_ctr_14 != 0) {
        goto loop_290;
    }
    var_r5_14 = -1;
block_306:
    if (var_r5_14 == -1) {
        goto block_308;
    }
    var_r4_6 += 1;
    if (var_r4_6 < 4) {
        goto loop_289;
    }
block_308:
    if (var_r26 >= (u32) var_r4_6) {
        goto block_310;
    }
    winSpriteSetDisp(arg1, 1);
block_310:
    return 0;
}

s32 menuBingoMessageDraw(BingoWindow *arg0, BingoSprite *arg1) {
    BingoPokemon *temp_r4;
    BingoPokemon *temp_r4_2;
    BingoPokemon *temp_r4_3;
    BingoPokemon *temp_r4_4;
    BingoPokemon *temp_r4_5;
    BingoPokemon *temp_r6;
    BingoPokemon *temp_r6_2;
    BingoPokemon *temp_r6_3;
    BingoPokemon *temp_r6_4;
    BingoPokemon *temp_r6_5;
    BingoPokemon *var_r0;
    BingoPokemon *var_r31;
    BingoPokemon *var_r3;
    BingoPokemon *var_r3_2;
    BingoPokemon *var_r4;
    BingoPokemon *var_r6;
    s16 temp_r29_2;
    s16 temp_r30;
    s16 temp_r3;
    s32 temp_cr0_eq;
    s32 temp_r29;
    s32 temp_r31;
    s32 temp_r4_10;
    s32 temp_r4_11;
    s32 temp_r4_12;
    s32 temp_r4_13;
    s32 temp_r4_14;
    s32 temp_r4_15;
    s32 temp_r4_16;
    s32 temp_r4_17;
    s32 temp_r4_6;
    s32 temp_r4_7;
    s32 temp_r4_8;
    s32 temp_r4_9;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_r28;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r4_2;
    u16 *temp_r28_3;
    u16 *temp_r28_4;
    u16 *temp_r28_5;
    u32 temp_r28_8;
    u32 temp_r3_2;
    u32 temp_r3_3;
    u32 var_r29;
    u32 var_r31_2;
    u8 temp_r0;
    u8 temp_r28;
    u8 temp_r28_2;
    u8 temp_r28_6;
    u8 temp_r28_7;
    u8 var_r0_2;
    u8 var_r0_3;
    u8 var_r0_4;
    u8 var_r0_5;

    temp_r3 = arg1->unk6;
    temp_r29 = gBingo.unk13C;
    switch (temp_r3) {                              /* switch 1 */
    case 0x8D8:                                     /* switch 1 */
        var_r31 = 0;
        gBingo.unk140 += timeGetLastFrameSec();
        arg1->unk4C = 0;
        switch (temp_r29) {                         /* switch 2 */
        case -4294911222:                           /* switch 2 */
            temp_r31 = winSpriteGetLayerID(arg0, arg1);
            temp_r30 = (s16) GSmsgGetRect(0xDAD8U);
            temp_r29_2 = (s16) ((u32) (GSmsgGetRect(0xDAD8U) >> 0x10U) >> 2U);
            temp_r28 = getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4);
            msgctrlSetValue(0x37, GSmsgGetGSchar(0xDAD8U));
            GSmsgPrint2(temp_r31, 0, 0, -1U, 0x4276U);
            temp_r0 = temp_r28 - 1;
            msgctrlSetValue(0x37, GSmsgGetGSchar(SheetDocMsgIdx__6cBingo[temp_r0].unk0));
            GSmsgPrint2(temp_r31, (s16) (temp_r29_2 * 0xB), 0, -1U, 0x4277U);
            msgctrlSetValue(0x37, GSmsgGetGSchar(SheetDocMsgIdx__6cBingo[temp_r0].unk4));
            GSmsgPrint2(temp_r31, 0, temp_r30, -1U, 0x4276U);
            msgctrlSetValue(0x37, GSmsgGetGSchar(SheetDocMsgIdx__6cBingo[temp_r0].unk8));
            GSmsgPrint2(temp_r31, temp_r29_2 * 4, 0, -1U, 0x4277U);
            break;
        case -4294911250:                           /* switch 2 */
            temp_r28_2 = gBingo.unk12A;
            if ((s32) temp_r28_2 >= 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
                msgctrlSetValue(0x2F, (u32) temp_r28_2);
                arg1->unk4C = 0x4276;
            }
            break;
        case -4294911246:                           /* switch 2 */
        case -4294911245:                           /* switch 2 */
        case -4294911198:                           /* switch 2 */
            if ((u8) gBingo.cells[gBingo.unk134].unk0 != 0) {
                var_r0 = 0;
            } else {
                var_r0 = &mPokemon__6cBingo[gBingo.cells[gBingo.unk134].unk1];
            }
            if (var_r0 != 0) {
                if ((u8) gBingo.cells[gBingo.unk134].unk0 != 0) {
                    var_r3 = 0;
                } else {
                    var_r3 = &mPokemon__6cBingo[gBingo.cells[gBingo.unk134].unk1];
                }
                temp_r28_3 = getNicknamePtr__7PokemonFv(var_r3);
                msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
                msgctrlSetValue(0x32, (u32) temp_r28_3);
                arg1->unk4C = 0x4276;
            }
            break;
        case -4294911244:                           /* switch 2 */
            if ((u8) gBingo.cells[gBingo.unk138].unk0 != 0) {

            } else {
                var_r31 = &mPokemon__6cBingo[gBingo.cells[gBingo.unk138].unk1];
            }
            if (var_r31 != 0) {
                if ((u8) gBingo.cells[gBingo.unk138].unk0 != 0) {
                    var_r3_2 = 0;
                } else {
                    var_r3_2 = &mPokemon__6cBingo[gBingo.cells[gBingo.unk138].unk1];
                }
                temp_r28_4 = getNicknamePtr__7PokemonFv(var_r3_2);
                msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
                msgctrlSetValue(0x32, (u32) temp_r28_4);
                arg1->unk4C = 0x4276;
            }
            break;
        case -4294911257:                           /* switch 2 */
            var_r6 = mPokemon__6cBingo;
            var_r4 = mPokemon__6cBingo;
            temp_r3_2 = gBingo.unk12C + 1;
            var_ctr = 2;
loop_24:
            if (temp_r3_2 == (u8) var_r4->unkC5) {

            } else {
                var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                if (temp_r3_2 == (u8) var_r4[1].unkC5) {

                } else {
                    temp_r4 = (BingoPokemon *)((u8 *)&var_r4[1] + 0xC8);
                    var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                    if (temp_r3_2 == (u8) temp_r4->unkC5) {

                    } else {
                        temp_r4_2 = (BingoPokemon *)((u8 *)temp_r4 + 0xC8);
                        var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                        if (temp_r3_2 == (u8) temp_r4_2->unkC5) {

                        } else {
                            temp_r4_3 = (BingoPokemon *)((u8 *)temp_r4_2 + 0xC8);
                            var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                            if (temp_r3_2 == (u8) temp_r4_3->unkC5) {

                            } else {
                                temp_r4_4 = (BingoPokemon *)((u8 *)temp_r4_3 + 0xC8);
                                var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                                if (temp_r3_2 == (u8) temp_r4_4->unkC5) {

                                } else {
                                    temp_r4_5 = (BingoPokemon *)((u8 *)temp_r4_4 + 0xC8);
                                    var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                                    if (temp_r3_2 == (u8) temp_r4_5->unkC5) {

                                    } else {
                                        var_r4 = (BingoPokemon *)((u8 *)temp_r4_5 + 0xC8);
                                        var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                                        var_ctr -= 1;
                                        if (var_ctr == 0) {
                                            var_r31 = (BingoPokemon *)-1U;
                                        } else {
                                            goto loop_24;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (&mPokemon__6cBingo[(s32) var_r31] != 0) {
                var_r4_2 = 0;
                temp_r3_3 = gBingo.unk12C + 1;
                var_ctr_2 = 2;
loop_42:
                if (temp_r3_3 == (u8) var_r6->unkC5) {

                } else {
                    var_r4_2 += 1;
                    if (temp_r3_3 == (u8) var_r6[1].unkC5) {

                    } else {
                        temp_r6 = (BingoPokemon *)((u8 *)&var_r6[1] + 0xC8);
                        var_r4_2 += 1;
                        if (temp_r3_3 == (u8) temp_r6->unkC5) {

                        } else {
                            temp_r6_2 = (BingoPokemon *)((u8 *)temp_r6 + 0xC8);
                            var_r4_2 += 1;
                            if (temp_r3_3 == (u8) temp_r6_2->unkC5) {

                            } else {
                                temp_r6_3 = (BingoPokemon *)((u8 *)temp_r6_2 + 0xC8);
                                var_r4_2 += 1;
                                if (temp_r3_3 == (u8) temp_r6_3->unkC5) {

                                } else {
                                    temp_r6_4 = (BingoPokemon *)((u8 *)temp_r6_3 + 0xC8);
                                    var_r4_2 += 1;
                                    if (temp_r3_3 == (u8) temp_r6_4->unkC5) {

                                    } else {
                                        temp_r6_5 = (BingoPokemon *)((u8 *)temp_r6_4 + 0xC8);
                                        var_r4_2 += 1;
                                        if (temp_r3_3 == (u8) temp_r6_5->unkC5) {

                                        } else {
                                            var_r6 = (BingoPokemon *)((u8 *)temp_r6_5 + 0xC8);
                                            var_r4_2 += 1;
                                            var_ctr_2 -= 1;
                                            if (var_ctr_2 == 0) {
                                                var_r4_2 = -1;
                                            } else {
                                                goto loop_42;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                temp_r28_5 = getNicknamePtr__7PokemonFv(&mPokemon__6cBingo[var_r4_2]);
                msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
                msgctrlSetValue(0x32, (u32) temp_r28_5);
                arg1->unk4C = 0x4276;
            }
            break;
        case -4294911254:                           /* switch 2 */
            temp_cr0_eq = (u8) gBingo.cells[gBingo.unk134].unk0 == 0;
            if (temp_cr0_eq == 0) {
                var_r28 = -1;
                var_r0_2 = -1U;
                if (temp_cr0_eq == 0) {
                    var_r0_2 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, (u32) gBingo.cells[gBingo.unk134].unk1);
                }
                switch ((s32) var_r0_2) {           /* switch 3; irregular */
                case 1:                             /* switch 3 */
                    var_r28 = 0xDAED;
                    break;
                case 2:                             /* switch 3 */
                    var_r28 = 0xDAEB;
                    break;
                case 3:                             /* switch 3 */
                    var_r28 = 0xDAEC;
                    break;
                }
                if (var_r28 >= 0) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
                    msgctrlSetValue(0x4D, GSmsgGetGSchar((u32) var_r28));
                    arg1->unk4C = 0x4276;
                }
            }
            break;
        case -4294911242:                           /* switch 2 */
            temp_r28_6 = gBingo.unk12D;
            var_r3_3 = 0;
            for (; var_r3_3 < 0xA; var_r3_3++) {
                if (bingoLineClear(&gBingo, var_r3_3)) {
                    var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                }
            }
            msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
            msgctrlSetValue(0x2F, (u32)var_r31 - temp_r28_6);
            arg1->unk4C = 0x4276;
            break;
        case -4294911241:                           /* switch 2 */
            temp_r28_7 = gBingo.unk12D;
            var_r3_4 = 0;
            for (; var_r3_4 < 0xA; var_r3_4++) {
                if (bingoLineClear(&gBingo, var_r3_4)) {
                    var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                }
            }
            msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
            temp_r28_8 = (u32)var_r31 - temp_r28_7;
            msgctrlSetValue(0x2F, temp_r28_8);
            msgctrlSetValue(0x2F, temp_r28_8);
            arg1->unk4C = 0x4276;
            break;
        case -4294911266:                           /* switch 2 */
            msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
            arg1->unk4C = 0x4276;
            break;
        case -4294911173:                           /* switch 2 */
            var_r3_5 = 0;
            for (; var_r3_5 < 0xA; var_r3_5++) {
                if (bingoLineClear(&gBingo, var_r3_5)) {
                    var_r31 = (BingoPokemon *)((u8 *)var_r31 + 1);
                }
            }
            msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
            msgctrlSetValue(0x2F, (u32) var_r31);
            arg1->unk4C = 0x4276;
            break;
        case -4294911265:                           /* switch 2 */
        case -4294911264:                           /* switch 2 */
        case -4294911263:                           /* switch 2 */
        case -4294911262:                           /* switch 2 */
        case -4294911258:                           /* switch 2 */
        case -4294911247:                           /* switch 2 */
        case -4294911243:                           /* switch 2 */
        case -4294911240:                           /* switch 2 */
        case -4294911239:                           /* switch 2 */
        case -4294911238:                           /* switch 2 */
        case -4294911197:                           /* switch 2 */
        case -4294911181:                           /* switch 2 */
        case -4294911177:                           /* switch 2 */
        case -4294911165:                           /* switch 2 */
            msgctrlSetValue(0x37, GSmsgGetGSchar((u32) temp_r29));
            arg1->unk4C = 0x4276;
            break;
        }
        break;
    case 0x8DA:                                     /* switch 1 */
        winSpriteSetDisp(arg1, 0);
        if ((s32) gBingo.unk12E != 0) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    case 0x8DC:                                     /* switch 1 */
        winSpriteSetDisp(arg1, 0);
        if ((s32) gBingo.unk144 == 0xD) {
            if (isClearPlus__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) != 0) {
                winSpriteSetDisp(arg1, 1);
                msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB32U));
                arg1->unk4C = 0x4277;
            } else if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) != 0) {
                winSpriteSetDisp(arg1, 1);
                msgctrlSetValue(0x37, GSmsgGetGSchar(0xDADBU));
                arg1->unk4C = 0x4277;
            }
        } else {
            var_r31_2 = 0U;
            var_r29 = 0;
            do {
                if (isClear__10bingo_biosFUl(&gBingo, var_r29) != 0) {
                    var_r31_2 += 1;
                }
                var_r29 += 1;
            } while (var_r29 < 0xAU);
            if ((var_r31_2 == 0xAU) && ((s32) gBingo.unk144 == 7) && ((s32) gBingo.unk108 == 0)) {
                winSpriteSetDisp(arg1, 1);
                if ((u8) gBingo.unk122 != 0) {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB35U));
                } else {
                    msgctrlSetValue(0x37, GSmsgGetGSchar(0xDB34U));
                }
                arg1->unk4C = 0x4277;
            }
        }
        break;
    case 0x8DD:                                     /* switch 1 */
    case 0x8DE:                                     /* switch 1 */
    case 0x8DF:                                     /* switch 1 */
    case 0x8E0:                                     /* switch 1 */
    case 0x8E1:                                     /* switch 1 */
    case 0x8E2:                                     /* switch 1 */
    case 0x8E3:                                     /* switch 1 */
    case 0x8E4:                                     /* switch 1 */
        winSpriteSetDisp(arg1, 0);
        if (((s32) gBingo.unk144 == 7) && ((s32) gBingo.unk108 == 0) && ((s32) gBingo.unk12E == 0) && (menuIsCheck(0xF6) == 0) && (menuIsCheck(0x100) == 0) && ((u32) gBingo.unk13C == -0x2520U)) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    case 0x8E5:                                     /* switch 1 */
    case 0x8E6:                                     /* switch 1 */
    case 0x8E7:                                     /* switch 1 */
    case 0x8E8:                                     /* switch 1 */
        winSpriteSetDisp(arg1, 0);
        if (((s32) gBingo.unk144 == 0xD) && ((u32) gBingo.unk13C == -0x24F6U)) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    }
    return 0;
}

s32 menuBingoPanelDraw(BingoWindow *arg0, BingoSprite *arg1) {
    f32 var_f1;
    s16 temp_r0;
    s16 temp_r3_5;
    s32 temp_r28_5;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 var_r30;
    u32 temp_r28;
    u32 temp_r28_2;
    u32 temp_r28_3;
    u32 temp_r28_4;
    u32 temp_r29;
    u32 temp_r29_2;
    u32 temp_r29_3;
    u32 temp_r29_4;
    u32 temp_r4;
    u32 var_r29;
    u8 var_r0;
    u8 var_r0_2;

    temp_r0 = arg1->unk6;
    var_r30 = 0;
    var_r29 = 0U;
    if (temp_r0 == 0x55C) {
        goto block_172;
    }
    if (temp_r0 >= 0x55C) {
        goto block_22;
    }
    if (temp_r0 == 0x553) {
        goto block_181;
    }
    if (temp_r0 >= 0x553) {
        goto block_13;
    }
    if (temp_r0 == 0x54F) {
        goto block_185;
    }
    if (temp_r0 >= 0x54F) {
        goto block_10;
    }
    if (temp_r0 == 0x54D) {
        goto block_187;
    }
    if (temp_r0 >= 0x54D) {
        goto block_186;
    }
    if (temp_r0 >= 0x544) {
        goto block_46;
    }
    goto block_189;
block_10:
    if (temp_r0 == 0x551) {
        goto block_183;
    }
    if (temp_r0 >= 0x551) {
        goto block_182;
    }
    goto block_184;
block_13:
    if (temp_r0 == 0x558) {
        goto block_176;
    }
    if (temp_r0 >= 0x558) {
        goto block_19;
    }
    if (temp_r0 == 0x556) {
        goto block_178;
    }
    if (temp_r0 >= 0x556) {
        goto block_177;
    }
    if (temp_r0 >= 0x555) {
        goto block_179;
    }
    goto block_180;
block_19:
    if (temp_r0 == 0x55A) {
        goto block_174;
    }
    if (temp_r0 >= 0x55A) {
        goto block_173;
    }
    goto block_175;
block_22:
    if (temp_r0 >= 0x5A1) {
        goto block_35;
    }
    if (temp_r0 >= 0x595) {
        goto block_30;
    }
    if (temp_r0 >= 0x58F) {
        goto block_28;
    }
    if (temp_r0 == 0x55E) {
        goto block_54;
    }
    if (temp_r0 >= 0x55E) {
        goto block_189;
    }
    goto block_188;
block_28:
    if (temp_r0 >= 0x592) {
        goto block_74;
    }
    goto block_73;
block_30:
    if (temp_r0 >= 0x59B) {
        goto block_33;
    }
    if (temp_r0 >= 0x598) {
        goto block_76;
    }
    goto block_75;
block_33:
    if (temp_r0 >= 0x59E) {
        goto block_78;
    }
    goto block_77;
block_35:
    if (temp_r0 >= 0x5AD) {
        goto block_41;
    }
    if (temp_r0 >= 0x5A7) {
        goto block_39;
    }
    if (temp_r0 >= 0x5A4) {
        goto block_80;
    }
    goto block_79;
block_39:
    if (temp_r0 >= 0x5AA) {
        goto block_82;
    }
    goto block_81;
block_41:
    if (temp_r0 >= 0x86B) {
        goto block_44;
    }
    if (temp_r0 >= 0x862) {
        goto block_48;
    }
    goto block_189;
block_44:
    if (temp_r0 >= 0x874) {
        goto block_189;
    }
    goto block_51;
block_46:
    winSpriteSetDisp(arg1, 0);
    if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) != 0) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_48:
    winSpriteSetDisp(arg1, 0);
    if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) == 0) {
        goto block_189;
    }
    if (isClearPlus__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) != 0) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_51:
    winSpriteSetDisp(arg1, 0);
    if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) == 0) {
        goto block_189;
    }
    if (isClearPlus__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1) == 0) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_54:
    if ((s32) gBingo.unk108 == 0) {
        goto block_56;
    }
    var_r0 = 0;
    goto block_65;
block_56:
    if ((s32) gBingo.unk144 == 7) {
        goto block_62;
    }
    if ((s32) gBingo.unk144 >= 7) {
        goto block_60;
    }
    if ((s32) gBingo.unk144 == 5) {
        goto block_63;
    }
    goto block_64;
block_60:
    if ((s32) gBingo.unk144 >= 9) {
        goto block_64;
    }
    goto block_63;
block_62:
    var_r0 = 1;
    goto block_65;
block_63:
    var_r0 = 2;
    goto block_65;
block_64:
    var_r0 = 0;
block_65:
    if (var_r0 != 1) {
        goto block_72;
    }
    if ((s32) gBingo.unk12E != 0) {
        goto block_72;
    }
    { f32 sv = (f32) sin((f64) (9.424778f * gBingo.unk140)); var_f1 = 128.0f * (1.0f + sv); }
    if (!(var_f1 > 255.0f)) {
        goto block_69;
    }
    var_f1 = 255.0f;
block_69:
    if (!(var_f1 < 0.0f)) {
        goto block_71;
    }
    var_f1 = 0.0f;
block_71:
    (*(BingoSprite **)((u8 *)arg0 + 0x28))->unk67 = (s8) var_f1;
    goto block_189;
block_72:
    (*(BingoSprite **)((u8 *)arg0 + 0x28))->unk67 = 0;
    goto block_189;
block_73:
    var_r30 = 1;
block_74:
    var_r30 += 1;
block_75:
    var_r30 += 1;
block_76:
    var_r30 += 1;
block_77:
    var_r30 += 1;
block_78:
    var_r30 += 1;
block_79:
    var_r30 += 1;
block_80:
    var_r30 += 1;
block_81:
    var_r30 += 1;
block_82:
    winSpriteSetDisp(arg1, 0);
    if (var_r30 == 8) {
        goto block_115;
    }
    if (var_r30 >= 8) {
        goto block_87;
    }
    if (var_r30 >= 4) {
        goto block_102;
    }
    if (var_r30 >= 0) {
        goto block_89;
    }
    goto block_140;
block_87:
    if (var_r30 >= 0xA) {
        goto block_140;
    }
    goto block_128;
block_89:
    if ((u8) gBingo.cells[var_r30].unk2 == 0) {
        goto block_140;
    }
    if (0U != 3U) {
        goto block_92;
    }
    var_r0_2 = 1;
    goto block_141;
block_92:
    temp_r3 = (var_r30 * 8) + 0x20;
    var_r0_2 = 1;
    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r3) + 0xA) == 0) {
        goto block_140;
    }
    if (1U != 3U) {
        goto block_95;
    }
    goto block_141;
block_95:
    temp_r3_2 = temp_r3 + 0x20;
    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r3_2) + 0xA) == 0) {
        goto block_140;
    }
    if (2U != 3U) {
        goto block_98;
    }
    var_r0_2 = 1;
    goto block_141;
block_98:
    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r3_2 + 0x20)) + 0xA) == 0) {
        goto block_140;
    }
    if (3U != 3U) {
        goto block_140;
    }
    var_r0_2 = 1;
    goto block_141;
block_102:
    temp_r3_3 = (7 - var_r30) * 4;
    if ((u8) gBingo.cells[temp_r3_3].unk2 == 0) {
        goto block_140;
    }
    if (0U != 3U) {
        goto block_105;
    }
    var_r0_2 = 1;
    goto block_141;
block_105:
    var_r0_2 = 1;
    if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r3_3] + 0xA) == 0) {
        goto block_140;
    }
    if (1U != 3U) {
        goto block_108;
    }
    goto block_141;
block_108:
    temp_r3_4 = (temp_r3_3 * 8) + 8 + 8;
    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r3_4) + 0xA) == 0) {
        goto block_140;
    }
    if (2U != 3U) {
        goto block_111;
    }
    var_r0_2 = 1;
    goto block_141;
block_111:
    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r3_4 + 8)) + 0xA) == 0) {
        goto block_140;
    }
    if (3U != 3U) {
        goto block_140;
    }
    var_r0_2 = 1;
    goto block_141;
block_115:
    if ((u8) gBingo.cells[3 - 0].unk2 == 0) {
        goto block_140;
    }
    if (0U != 3U) {
        goto block_118;
    }
    var_r0_2 = 1;
    goto block_141;
block_118:
    var_r0_2 = 1;
    if ((u8) gBingo.cells[(3 - 1) + 4].unk2 == 0) {
        goto block_140;
    }
    if (1U != 3U) {
        goto block_121;
    }
    goto block_141;
block_121:
    if ((u8) gBingo.cells[(3 - 2) + 8].unk2 == 0) {
        goto block_140;
    }
    if (2U != 3U) {
        goto block_124;
    }
    var_r0_2 = 1;
    goto block_141;
block_124:
    if ((u8) gBingo.cells[(3 - 3) + 0xC].unk2 == 0) {
        goto block_140;
    }
    if (3U != 3U) {
        goto block_140;
    }
    var_r0_2 = 1;
    goto block_141;
block_128:
    if ((u8) gBingo.cells[0].unk2 == 0) {
        goto block_140;
    }
    if (0U != 3U) {
        goto block_131;
    }
    var_r0_2 = 1;
    goto block_141;
block_131:
    var_r0_2 = 1;
    if ((u8) gBingo.cells[5].unk2 == 0) {
        goto block_140;
    }
    if (1U != 3U) {
        goto block_134;
    }
    goto block_141;
block_134:
    if ((u8) gBingo.cells[0xA].unk2 == 0) {
        goto block_140;
    }
    if (2U != 3U) {
        goto block_137;
    }
    var_r0_2 = 1;
    goto block_141;
block_137:
    if ((u8) gBingo.cells[0xF].unk2 == 0) {
        goto block_140;
    }
    if (3U != 3U) {
        goto block_140;
    }
    var_r0_2 = 1;
    goto block_141;
block_140:
    var_r0_2 = 0;
block_141:
    if (var_r0_2 == 0) {
        goto block_171;
    }
    if (isChgBingoLine__6cBingoFl(&gBingo, var_r30) == 0) {
        goto block_170;
    }
    temp_r3_5 = arg1->unk6;
    if ((u32) (temp_r3_5 - 0x58F) > 0x1BU) {
        goto block_146;
    }
    switch (temp_r3_5) {                             /* jump table: jtbl_recovery_2 */
    default: goto block_146;
case 0x58F:
case 0x592:
case 0x595:
case 0x598:
case 0x59B:
case 0x59E:
case 0x5A1:
case 0x5A4:
case 0x5A7:
case 0x5AA:
    var_r29 = 1U;
block_146:
    if ((u32) var_r30 >= 4U) {
        goto block_152;
    }
    if (var_r29 == 0U) {
        goto block_150;
    }
    temp_r29 = FlashSystemGetNowFrame(0x1ECC3000U);
    if (FlashSystemGetEndFrame(0x1ECC3000U) == temp_r29) {
        goto block_150;
    }
    windowDrawSprite((s16) (var_r30 * 0x47), 0, arg0, (BingoSprite *)0x2E2, 0, winSpriteGetLayerID(arg0, arg1));
block_150:
    temp_r28 = FlashSystemGetNowFrame(0x1ECC3000U);
    if ((u32) (FlashSystemGetEndFrame(0x1ECC3000U) - 0x23) > temp_r28) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_152:
    if ((u32) var_r30 >= 8U) {
        goto block_158;
    }
    if (var_r29 == 0U) {
        goto block_156;
    }
    temp_r29_2 = FlashSystemGetNowFrame(0x1ECB3000U);
    if (FlashSystemGetEndFrame(0x1ECB3000U) == temp_r29_2) {
        goto block_156;
    }
    windowDrawSprite(0, (s16) ((7 - var_r30) * 0x44), arg0, (BingoSprite *)0x2E1, 0, winSpriteGetLayerID(arg0, arg1));
block_156:
    temp_r28_2 = FlashSystemGetNowFrame(0x1ECB3000U);
    if ((u32) (FlashSystemGetEndFrame(0x1ECB3000U) - 0x23) > temp_r28_2) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_158:
    if ((u32) var_r30 != 8U) {
        goto block_164;
    }
    if (var_r29 == 0U) {
        goto block_162;
    }
    temp_r29_3 = FlashSystemGetNowFrame(0x1ECE3000U);
    if (FlashSystemGetEndFrame(0x1ECE3000U) == temp_r29_3) {
        goto block_162;
    }
    windowDrawSprite(0, 0, arg0, (BingoSprite *)0x2E4, 0, winSpriteGetLayerID(arg0, arg1));
block_162:
    temp_r28_3 = FlashSystemGetNowFrame(0x1ECE3000U);
    if ((u32) (FlashSystemGetEndFrame(0x1ECE3000U) - 0x23) > temp_r28_3) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_164:
    if ((u32) var_r30 != 9U) {
        goto block_189;
    }
    if (var_r29 == 0U) {
        goto block_168;
    }
    temp_r29_4 = FlashSystemGetNowFrame(0x1ECD3000U);
    if (FlashSystemGetEndFrame(0x1ECD3000U) == temp_r29_4) {
        goto block_168;
    }
    windowDrawSprite(0, 0, arg0, (BingoSprite *)0x2E3, 0, winSpriteGetLayerID(arg0, arg1));
block_168:
    temp_r28_4 = FlashSystemGetNowFrame(0x1ECD3000U);
    if ((u32) (FlashSystemGetEndFrame(0x1ECD3000U) - 0x23) > temp_r28_4) {
        goto block_189;
    }
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_170:
    winSpriteSetDisp(arg1, 1);
    goto block_189;
block_171:
    winSpriteSetDisp(arg1, 0);
    goto block_189;
block_172:
    var_r30 = 1;
block_173:
    var_r30 += 1;
block_174:
    var_r30 += 1;
block_175:
    var_r30 += 1;
block_176:
    var_r30 += 1;
block_177:
    var_r30 += 1;
block_178:
    var_r30 += 1;
block_179:
    var_r30 += 1;
block_180:
    var_r30 += 1;
block_181:
    var_r30 += 1;
block_182:
    var_r30 += 1;
block_183:
    var_r30 += 1;
block_184:
    var_r30 += 1;
block_185:
    var_r30 += 1;
block_186:
    var_r30 += 1;
block_187:
    dispPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(&gBingo, (u32) var_r30, arg0, arg1);
    goto block_189;
block_188:
    temp_r28_5 = winSpriteGetLayerID(arg0, arg1);
    msgctrlSetValue(0x37, GSmsgGetGSchar(SheetDocMsgIdx__6cBingo[(u8) (getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1)].unk0));
    temp_r4 = arg1->unk54 - (u16) (GSmsgGetRect(0x4276U) >> 0x10U);
    GSmsgPrint2(temp_r28_5, (s16) ((s32) ((temp_r4 >> 0x1FU) + temp_r4) >> 1), 0, -1U, 0x4276U);
block_189:
    return 0;
    }
}

s32 menuBingoScoreDraw(BingoWindow *arg0, BingoSprite *arg1) {
    s16 temp_r3;
    s32 temp_r29;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r5_7;
    s32 temp_r5_8;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r3_2;
    s32 var_r4;
    s32 var_r4_2;
    u16 var_r28;
    u32 temp_r28;
    u32 var_r3;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r31;

    temp_r3 = arg1->unk6;
    var_r31 = 0;
    switch (temp_r3) {
    case 0x57B:
        var_r31 = 1;
        /* fallthrough */
    case 0x57C:
        var_r31 += 1;
        /* fallthrough */
    case 0x57D:
        var_r31 += 1;
        /* fallthrough */
    case 0x57E:
        var_r31 += 1;
        /* fallthrough */
    case 0x57F:
        var_r31 += 1;
        /* fallthrough */
    case 0x580:
        var_r31 += 1;
        /* fallthrough */
    case 0x581:
        var_r31 += 1;
        /* fallthrough */
    case 0x582:
        var_r31 += 1;
        /* fallthrough */
    case 0x583:
        var_r31 += 1;
        /* fallthrough */
    case 0x584:
        winSpriteSetDisp(arg1, 0);
        var_r3 = 0U;
        var_r4 = 0;
        for (; var_r4 < 0xA; var_r4++) {
            if (bingoLineClear(&gBingo, var_r4)) {
                var_r3 += 1;
            }
        }
        if ((u32) (var_r31 + 1) == var_r3) {
            if (isChgBingoLine__6cBingoFl(&gBingo, -1) != 0) {
                temp_r28 = FlashSystemGetNowFrame(0x1F583000U);
                if (FlashSystemGetEndFrame(0x1F583000U) != temp_r28) {
                    windowDrawSprite(0, (s16) (((0xA - (var_r31 + 1)) * 0x17) + 8), arg0, (BingoSprite *)0x324, 0, winSpriteGetLayerID(arg0, arg1));
                } else {
                    winSpriteSetDisp(arg1, 1);
                }
            } else {
                winSpriteSetDisp(arg1, 1);
            }
        }
        break;
    case 0x585:
        var_r31 = 1;
        /* fallthrough */
    case 0x586:
        var_r31 += 1;
        /* fallthrough */
    case 0x587:
        var_r31 += 1;
        /* fallthrough */
    case 0x588:
        var_r31 += 1;
        /* fallthrough */
    case 0x589:
        var_r31 += 1;
        /* fallthrough */
    case 0x58A:
        var_r31 += 1;
        /* fallthrough */
    case 0x58B:
        var_r31 += 1;
        /* fallthrough */
    case 0x58C:
        var_r31 += 1;
        /* fallthrough */
    case 0x58D:
        var_r31 += 1;
        /* fallthrough */
    case 0x58E:
        var_r28 = getScore__10bingo_biosFP14BINGO_DATA_dd_Uc(&gBingo, gBingo.unk4, var_r31);
        temp_r29 = winSpriteGetLayerID(arg0, arg1);
        if ((u8) gBingo.unk122 != 0) {
            var_r28 = (u16) ((f32) var_r28 * 1.5f);
        }
        msgctrlSetValue(0x34, (u32) var_r28);
        var_r3_2 = 0;
        var_r4_2 = 0;
        for (; var_r4_2 < 0xA; var_r4_2++) {
            if (bingoLineClear(&gBingo, var_r4_2)) {
                var_r3_2 += 1;
            }
        }
        if (var_r31 == (u32) (var_r3_2 - 1)) {
            GSmsgPrintRect(temp_r29, 0, 0, arg1->unk54, arg1->unk56, 0xFF, 0x4287);
        } else {
            GSmsgPrintRect(temp_r29, 0, 0, arg1->unk54, arg1->unk56, -1, 0x4287);
        }
        break;
    }
    return 0;
}

s32 menuBingoPkmDraw(BingoWindow *arg0, BingoSprite *arg1) {
    BingoPokemon *temp_r4_2;
    BingoPokemon *temp_r4_3;
    BingoPokemon *temp_r4_4;
    BingoPokemon *temp_r4_5;
    BingoPokemon *temp_r4_6;
    BingoPokemon *temp_r7;
    BingoPokemon *temp_r7_2;
    BingoPokemon *temp_r7_3;
    BingoPokemon *temp_r7_4;
    BingoPokemon *temp_r7_5;
    BingoPokemon *var_r4;
    BingoPokemon *var_r7;
    BingoState *var_r27;
    f32 var_f1;
    s16 temp_r4;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_r29;
    s32 var_r5;
    s32 var_r6;
    u32 temp_r0;
    u32 temp_r3;
    u32 temp_r3_2;
    u32 var_r28;
    u32 var_r31;
    u32 var_r3;
    u8 var_r0;
    u8 var_r0_2;

    temp_r4 = arg1->unk6;
    var_r31 = 0;
    switch (temp_r4) {                              /* switch 1 */
    case 0x53C:                                     /* switch 1 */
        var_r31 = 1;
        /* fallthrough */
    case 0x53B:                                     /* switch 1 */
        var_r31 += 1;
        /* fallthrough */
    case 0x53A:                                     /* switch 1 */
        var_r31 += 1;
        /* fallthrough */
    case 0x539:                                     /* switch 1 */
        dispPkmPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(&gBingo, var_r31, arg0, arg1);
        break;
    case 0x53F:                                     /* switch 1 */
        var_r31 = 1;
        /* fallthrough */
    case 0x53E:                                     /* switch 1 */
        var_r31 += 1;
        /* fallthrough */
    case 0x53D:                                     /* switch 1 */
        var_r29 = 0;
        var_r4 = mPokemon__6cBingo;
        var_ctr = 2;
loop_9:
        temp_r3 = var_r31 + 2;
        if (temp_r3 == (u8) var_r4->unkC5) {

        } else {
            var_r29 += 1;
            if (temp_r3 == (u8) var_r4[1].unkC5) {

            } else {
                temp_r4_2 = (BingoPokemon *)((u8 *)&var_r4[1] + 0xC8);
                var_r29 += 1;
                if (temp_r3 == (u8) temp_r4_2->unkC5) {

                } else {
                    temp_r4_3 = (BingoPokemon *)((u8 *)temp_r4_2 + 0xC8);
                    var_r29 += 1;
                    if (temp_r3 == (u8) temp_r4_3->unkC5) {

                    } else {
                        temp_r4_4 = (BingoPokemon *)((u8 *)temp_r4_3 + 0xC8);
                        var_r29 += 1;
                        if (temp_r3 == (u8) temp_r4_4->unkC5) {

                        } else {
                            temp_r4_5 = (BingoPokemon *)((u8 *)temp_r4_4 + 0xC8);
                            var_r29 += 1;
                            if (temp_r3 == (u8) temp_r4_5->unkC5) {

                            } else {
                                temp_r4_6 = (BingoPokemon *)((u8 *)temp_r4_5 + 0xC8);
                                var_r29 += 1;
                                if (temp_r3 == (u8) temp_r4_6->unkC5) {

                                } else {
                                    var_r4 = (BingoPokemon *)((u8 *)temp_r4_6 + 0xC8);
                                    var_r29 += 1;
                                    var_ctr -= 1;
                                    if (var_ctr == 0) {
                                        var_r29 = -1;
                                    } else {
                                                                }
                                }
                            }
                        }
                    }
                }
            }
        }
        winSpriteSetDisp(arg1, 0);
        if (var_r29 < 0) {
            var_r28 = 0U;
            var_r27 = &gBingo;
loop_27:
            if (((u8) var_r27->cells[0].unk2 != 0) && ((u8) var_r27->cells[0].unk0 != 0) && (getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, (u32) var_r27->cells[0].unk1) == 1)) {
                var_r0 = 1;
            } else {
                var_r27 = (BingoState *)((u8 *)var_r27 + 8);
                var_r28 += 1;
                if (var_r28 >= 0x10U) {
                    var_r0 = 0;
                } else {
                    goto loop_27;
                }
            }
            if (var_r0 != 0) {
                var_r3 = 4U;
            } else {
                var_r3 = 3U;
            }
            temp_r0 = var_r31 + 1;
            if (temp_r0 < var_r3) {
                if ((temp_r0 == 3U) && ((s32) var_r3 == 4)) {
                    if ((u8) gBingo.unk121 != 0) {
                        winSpriteSetDisp(arg1, 1);
                    }
                } else {
                    winSpriteSetDisp(arg1, 1);
                }
            }
        }
        break;
    case 0x543:                                     /* switch 1 */
        var_r31 = 1;
        /* fallthrough */
    case 0x542:                                     /* switch 1 */
        var_r31 += 1;
        /* fallthrough */
    case 0x541:                                     /* switch 1 */
        var_r31 += 1;
        /* fallthrough */
    case 0x540:                                     /* switch 1 */
        winSpriteSetDisp(arg1, 0);
        var_r5 = 0;
loop_46:
        var_r7 = mPokemon__6cBingo;
        var_r6 = 0;
        temp_r3_2 = var_r5 + 1;
        var_ctr_2 = 2;
loop_47:
        if (temp_r3_2 == (u8) var_r7->unkC5) {

        } else {
            var_r6 += 1;
            if (temp_r3_2 == (u8) var_r7[1].unkC5) {

            } else {
                temp_r7 = (BingoPokemon *)((u8 *)&var_r7[1] + 0xC8);
                var_r6 += 1;
                if (temp_r3_2 == (u8) temp_r7->unkC5) {

                } else {
                    temp_r7_2 = (BingoPokemon *)((u8 *)temp_r7 + 0xC8);
                    var_r6 += 1;
                    if (temp_r3_2 == (u8) temp_r7_2->unkC5) {

                    } else {
                        temp_r7_3 = (BingoPokemon *)((u8 *)temp_r7_2 + 0xC8);
                        var_r6 += 1;
                        if (temp_r3_2 == (u8) temp_r7_3->unkC5) {

                        } else {
                            temp_r7_4 = (BingoPokemon *)((u8 *)temp_r7_3 + 0xC8);
                            var_r6 += 1;
                            if (temp_r3_2 == (u8) temp_r7_4->unkC5) {

                            } else {
                                temp_r7_5 = (BingoPokemon *)((u8 *)temp_r7_4 + 0xC8);
                                var_r6 += 1;
                                if (temp_r3_2 == (u8) temp_r7_5->unkC5) {

                                } else {
                                    var_r7 = (BingoPokemon *)((u8 *)temp_r7_5 + 0xC8);
                                    var_r6 += 1;
                                    var_ctr_2 -= 1;
                                    if (var_ctr_2 == 0) {
                                        var_r6 = -1;
                                    } else {
                                        goto loop_47;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (var_r6 != -1) {
            var_r5 += 1;
            if (var_r5 < 4) {
                goto loop_46;
            }
        }
        if ((var_r5 > 1) && (var_r31 == (u8) gBingo.unk12C)) {
            if ((s32) gBingo.unk108 != 0) {
                var_r0_2 = 0;
            } else {
                switch ((s32) gBingo.unk144) {      /* switch 2; irregular */
                case 7:                             /* switch 2 */
                    var_r0_2 = 1;
                    break;
                case 8:                             /* switch 2 */
                case 5:                             /* switch 2 */
                    var_r0_2 = 2;
                    break;
                default:                            /* switch 2 */
                    var_r0_2 = 0;
                    break;
                }
            }
            if (var_r0_2 == 2) {
                { f32 sv = (f32) sin((f64) (9.424778f * gBingo.unk140)); var_f1 = 128.0f * (1.0f + sv); }
                if (var_f1 > 255.0f) {
                    var_f1 = 255.0f;
                }
                if (var_f1 < 0.0f) {
                    var_f1 = 0.0f;
                }
                arg1->unk67 = (u8) (s32) var_f1;
                winSpriteSetDisp(arg1, 1);
            }
        }
        break;
    }
    return 0;
}

s32 menuBingoTopDraw(BingoWindow *arg0, BingoSprite *arg1) {
    static s32 debug;
    static u8 init;
    s16 temp_r0;
    u32 var_r30;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r0_3;

    if ((s8) init == 0) {
        debug = 0;
        init = 1;
    }
    var_r30 = 0;
    winSpriteSetDisp(arg1, 0);
    temp_r0 = arg1->unk6;
    switch (temp_r0) {                              /* irregular */
    case 0x5DD:
        debug = 0;
        if (isSelect__10bingo_biosFUl(&gBingo, 0xAU) != 0) {
            winSpriteSetDisp(arg1, 1);
            if (isSelect__10bingo_biosFUl(&gBingo, 8U) != 0) {
                var_r0 = 2;
            } else if (isSelect__10bingo_biosFUl(&gBingo, 5U) != 0) {
                var_r0 = 1;
            } else {
                var_r0 = 0;
            }
            arg1->unk52 = (var_r0 * 0x65) + 0x89;
        }
        break;
    case 0x5DF:
        var_r30 = 1;
        /* fallthrough */
    case 0x5DE:
        var_r30 += 1;
        /* fallthrough */
    case 0x5DC:
        var_r30 += 1;
        /* fallthrough */
    case 0x5DB:
        if (var_r30 <= (u8) gBingo.unk128) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    case 0x5E0:
        if (isSelect__10bingo_biosFUl(&gBingo, 0xAU) != 0) {
            winSpriteSetDisp(arg1, 1);
            if (isSelect__10bingo_biosFUl(&gBingo, 8U) != 0) {
                var_r0_2 = 2;
            } else if (isSelect__10bingo_biosFUl(&gBingo, 5U) != 0) {
                var_r0_2 = 1;
            } else {
                var_r0_2 = 0;
            }
            arg1->unk52 = (var_r0_2 * 0x65) + 0x8C;
        }
        break;
    case 0x516:
        var_r30 = 1;
        /* fallthrough */
    case 0x515:
        var_r30 += 1;
        /* fallthrough */
    case 0x514:
        var_r30 += 1;
        /* fallthrough */
    case 0x513:
        if (var_r30 <= (u8) gBingo.unk128) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    case 0x694:
        var_r30 = 1;
        /* fallthrough */
    case 0x517:
        var_r30 += 1;
        /* fallthrough */
    case 0x518:
        var_r30 += 1;
        /* fallthrough */
    case 0x519:
        var_r30 += 1;
        /* fallthrough */
    case 0x51A:
        var_r30 += 1;
        /* fallthrough */
    case 0x51B:
        var_r30 += 1;
        /* fallthrough */
    case 0x51C:
        var_r30 += 1;
        /* fallthrough */
    case 0x51D:
        var_r30 += 1;
        /* fallthrough */
    case 0x51E:
        var_r30 += 1;
        /* fallthrough */
    case 0x51F:
        var_r30 += 1;
        /* fallthrough */
    case 0x520:
        if ((s32) var_r30 == 0xA) {
            if (isSelect__10bingo_biosFUl(&gBingo, 0xAU) != 0) {
                winSpriteSetDisp(arg1, 1);
                if (isSelect__10bingo_biosFUl(&gBingo, 8U) != 0) {
                    var_r0_3 = 2;
                } else if (isSelect__10bingo_biosFUl(&gBingo, 5U) != 0) {
                    var_r0_3 = 1;
                } else {
                    var_r0_3 = 0;
                }
                arg1->unk52 = (var_r0_3 * 0x65) + 0xA1;
            } else {
                winSpriteSetDisp(arg1, 0);
            }
        } else if (isSelect__10bingo_biosFUl(&gBingo, var_r30) != 0) {
            winSpriteSetDisp(arg1, 1);
        }
        break;
    case 0x695:
        var_r30 = 1;
        /* fallthrough */
    case 0x534:
        var_r30 += 1;
        /* fallthrough */
    case 0x533:
        var_r30 += 1;
        /* fallthrough */
    case 0x532:
        var_r30 += 1;
        /* fallthrough */
    case 0x531:
        var_r30 += 1;
        /* fallthrough */
    case 0x530:
        var_r30 += 1;
        /* fallthrough */
    case 0x52F:
        var_r30 += 1;
        /* fallthrough */
    case 0x52E:
        var_r30 += 1;
        /* fallthrough */
    case 0x52D:
        var_r30 += 1;
        /* fallthrough */
    case 0x52C:
        var_r30 += 1;
        /* fallthrough */
    case 0x52B:
        if (isClear__10bingo_biosFUl(&gBingo, var_r30) != 0) {
            winSpriteSetDisp(arg1, 1);
        }
        if (((s32) var_r30 == 0xA) && (isSelect__10bingo_biosFUl(&gBingo, 0xAU) != 0)) {
            if ((u8) gBingo.unk128 == 3) {
                arg1->unk52 = 0x16A;
            } else {
                arg1->unk52 = (gBingo.unk128 * 0x65) + 0xA0;
            }
        }
        break;
    case 0x861:
        var_r30 = 1;
        /* fallthrough */
    case 0x860:
        var_r30 += 1;
        /* fallthrough */
    case 0x85F:
        var_r30 += 1;
        /* fallthrough */
    case 0x85E:
        var_r30 += 1;
        /* fallthrough */
    case 0x85D:
        var_r30 += 1;
        /* fallthrough */
    case 0x85C:
        var_r30 += 1;
        /* fallthrough */
    case 0x85B:
        var_r30 += 1;
        /* fallthrough */
    case 0x85A:
        var_r30 += 1;
        /* fallthrough */
    case 0x859:
        var_r30 += 1;
        /* fallthrough */
    case 0x858:
        var_r30 += 1;
        /* fallthrough */
    case 0x857:
        if (isClearPlus__10bingo_biosFUl(&gBingo, var_r30) != 0) {
            winSpriteSetDisp(arg1, 1);
        }
        if (((s32) var_r30 == 0xA) && (isSelect__10bingo_biosFUl(&gBingo, 0xAU) != 0)) {
            if ((u8) gBingo.unk128 == 3) {
                arg1->unk52 = 0x16A;
            } else {
                arg1->unk52 = (gBingo.unk128 * 0x65) + 0xA0;
            }
        }
        break;
    }
    return 0;
}

s32 menuBingoSheetBtn(BingoWindow *arg0) {
    BingoCell *temp_r29_3;
    BingoCell *temp_r29_4;
    BingoCell *temp_r29_5;
    BingoCell *temp_r29_6;
    BingoCell *temp_r29_7;
    BingoCell *temp_r29_8;
    BingoCell *temp_r6_23;
    BingoCell *temp_r6_24;
    BingoCell *temp_r6_25;
    BingoCell *temp_r6_26;
    BingoCell *temp_r6_27;
    BingoCell *temp_r6_28;
    BingoPokemon *temp_r4;
    BingoPokemon *temp_r5_19;
    BingoPokemon *temp_r5_9;
    BingoPokemon *temp_r6;
    BingoPokemon *temp_r6_10;
    BingoPokemon *temp_r6_29;
    BingoPokemon *temp_r6_2;
    BingoPokemon *temp_r6_30;
    BingoPokemon *temp_r6_31;
    BingoPokemon *temp_r6_32;
    BingoPokemon *temp_r6_33;
    BingoPokemon *temp_r6_3;
    BingoPokemon *temp_r6_4;
    BingoPokemon *temp_r6_5;
    BingoPokemon *temp_r6_6;
    BingoPokemon *temp_r6_7;
    BingoPokemon *temp_r6_8;
    BingoPokemon *temp_r6_9;
    BingoPokemon *temp_r7;
    BingoPokemon *temp_r7_10;
    BingoPokemon *temp_r7_11;
    BingoPokemon *temp_r7_12;
    BingoPokemon *temp_r7_13;
    BingoPokemon *temp_r7_14;
    BingoPokemon *temp_r7_15;
    BingoPokemon *temp_r7_16;
    BingoPokemon *temp_r7_17;
    BingoPokemon *temp_r7_18;
    BingoPokemon *temp_r7_19;
    BingoPokemon *temp_r7_20;
    BingoPokemon *temp_r7_2;
    BingoPokemon *temp_r7_3;
    BingoPokemon *temp_r7_4;
    BingoPokemon *temp_r7_5;
    BingoPokemon *temp_r8;
    BingoPokemon *temp_r8_10;
    BingoPokemon *temp_r8_11;
    BingoPokemon *temp_r8_12;
    BingoPokemon *temp_r8_13;
    BingoPokemon *temp_r8_14;
    BingoPokemon *temp_r8_15;
    BingoPokemon *temp_r8_16;
    BingoPokemon *temp_r8_17;
    BingoPokemon *temp_r8_18;
    BingoPokemon *temp_r8_19;
    BingoPokemon *temp_r8_20;
    BingoPokemon *temp_r8_21;
    BingoPokemon *temp_r8_22;
    BingoPokemon *temp_r8_23;
    BingoPokemon *temp_r8_24;
    BingoPokemon *temp_r8_25;
    BingoPokemon *temp_r8_2;
    BingoPokemon *temp_r8_3;
    BingoPokemon *temp_r8_4;
    BingoPokemon *temp_r8_5;
    BingoPokemon *temp_r8_6;
    BingoPokemon *temp_r8_7;
    BingoPokemon *temp_r8_8;
    BingoPokemon *temp_r8_9;
    BingoPokemon *temp_r9;
    BingoPokemon *temp_r9_10;
    BingoPokemon *temp_r9_11;
    BingoPokemon *temp_r9_12;
    BingoPokemon *temp_r9_13;
    BingoPokemon *temp_r9_14;
    BingoPokemon *temp_r9_15;
    BingoPokemon *temp_r9_16;
    BingoPokemon *temp_r9_17;
    BingoPokemon *temp_r9_18;
    BingoPokemon *temp_r9_19;
    BingoPokemon *temp_r9_20;
    BingoPokemon *temp_r9_2;
    BingoPokemon *temp_r9_3;
    BingoPokemon *temp_r9_4;
    BingoPokemon *temp_r9_5;
    BingoPokemon *temp_r9_6;
    BingoPokemon *temp_r9_7;
    BingoPokemon *temp_r9_8;
    BingoPokemon *temp_r9_9;
    BingoPokemon *var_r6;
    BingoPokemon *var_r6_10;
    BingoPokemon *var_r6_2;
    BingoPokemon *var_r7;
    BingoPokemon *var_r7_3;
    BingoPokemon *var_r7_7;
    BingoPokemon *var_r8_10;
    BingoPokemon *var_r8_2;
    BingoPokemon *var_r8_4;
    BingoPokemon *var_r8_7;
    BingoPokemon *var_r8_9;
    BingoPokemon *var_r9;
    BingoPokemon *var_r9_2;
    BingoPokemon *var_r9_3;
    BingoPokemon *var_r9_4;
    BingoState *var_r29;
    BingoState *var_r6_11;
    BingoState *var_r6_8;
    s16 temp_r0_2;
    s16 temp_r3_9;
    s32 temp_r0;
    s32 temp_r0_10;
    s32 temp_r0_11;
    s32 temp_r0_12;
    s32 temp_r0_13;
    s32 temp_r0_14;
    s32 temp_r0_15;
    s32 temp_r0_16;
    s32 temp_r0_17;
    s32 temp_r0_18;
    s32 temp_r0_19;
    s32 temp_r0_21;
    s32 temp_r0_22;
    s32 temp_r0_23;
    s32 temp_r0_24;
    s32 temp_r0_25;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r0_6;
    s32 temp_r0_7;
    s32 temp_r0_8;
    s32 temp_r0_9;
    s32 temp_r27_2;
    s32 temp_r4_5;
    s32 temp_r5;
    s32 temp_r5_14;
    s32 temp_r5_16;
    s32 temp_r5_18;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 temp_r5_7;
    s32 temp_r5_8;
    s32 temp_r6_11;
    s32 temp_r6_12;
    s32 temp_r6_13;
    s32 temp_r6_14;
    s32 temp_r6_15;
    s32 temp_r6_16;
    s32 temp_r6_17;
    s32 temp_r6_18;
    s32 temp_r6_19;
    s32 temp_r6_20;
    s32 temp_r6_22;
    s32 temp_r7_22;
    s32 temp_r7_23;
    s32 temp_r7_24;
    s32 temp_r7_25;
    s32 temp_r7_26;
    s32 temp_r7_6;
    s32 temp_r7_7;
    s32 temp_r7_8;
    s32 temp_r7_9;
    s32 var_ctr;
    s32 var_ctr_10;
    s32 var_ctr_11;
    s32 var_ctr_12;
    s32 var_ctr_13;
    s32 var_ctr_14;
    s32 var_ctr_15;
    s32 var_ctr_16;
    s32 var_ctr_17;
    s32 var_ctr_18;
    s32 var_ctr_19;
    s32 var_ctr_20;
    s32 var_ctr_21;
    s32 var_ctr_22;
    s32 var_ctr_23;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_ctr_6;
    s32 var_ctr_7;
    s32 var_ctr_8;
    s32 var_ctr_9;
    s32 var_r0_2;
    s32 var_r12;
    s32 var_r3;
    s32 var_r3_2;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 var_r4_5;
    s32 var_r4_6;
    s32 var_r4_7;
    s32 var_r4_8;
    s32 var_r5_10;
    s32 var_r5_11;
    s32 var_r5_3;
    s32 var_r5_5;
    s32 var_r5_6;
    s32 var_r5_9;
    s32 var_r6_3;
    s32 var_r6_5;
    s32 var_r6_7;
    s32 var_r6_9;
    s32 var_r7_2;
    s32 var_r7_4;
    s32 var_r7_5;
    s32 var_r7_6;
    s32 var_r7_8;
    s32 var_r7_9;
    s32 var_r8_3;
    s32 var_r8_5;
    s32 var_r8_6;
    s32 var_r8_8;
    u16 temp_r29;
    u16 temp_r3;
    u32 temp_r0_20;
    u32 temp_r28;
    u32 temp_r29_2;
    u32 temp_r3_2;
    u32 temp_r3_4;
    u32 temp_r3_5;
    u32 temp_r3_6;
    u32 temp_r3_7;
    u32 temp_r3_8;
    u32 temp_r4_3;
    u32 temp_r4_4;
    u32 temp_r4_6;
    u32 temp_r4_7;
    u32 temp_r4_8;
    u32 temp_r4_9;
    u32 temp_r5_10;
    u32 temp_r5_11;
    u32 temp_r5_12;
    u32 temp_r5_13;
    u32 temp_r5_15;
    u32 temp_r5_17;
    u32 temp_r6_21;
    u32 temp_r7_21;
    u32 var_r27;
    u32 var_r3_4;
    u32 var_r4_9;
    u32 var_r5_8;
    u32 var_r6_6;
    u8 temp_r0_3;
    u8 temp_r27;
    u8 temp_r3_3;
    u8 temp_r4_10;
    u8 temp_r4_2;
    u8 var_r0;
    u8 var_r0_3;
    u8 var_r0_4;
    u8 var_r0_5;
    u8 var_r0_6;
    u8 var_r0_7;
    u8 var_r3_3;
    u8 var_r4_10;
    u8 var_r4_4;
    u8 var_r5;
    u8 var_r5_2;
    u8 var_r5_4;
    u8 var_r5_7;
    u8 var_r6_4;
    u8 var_r8;

    temp_r29 = windowGetKeyRepeat();
    temp_r3 = windowGetKeyTrg();
    if ((s32) gBingo.unk108 != 0) {
        return 0;
    }
    if ((u32) gBingo.unk144 <= 0xCU) {
        switch (gBingo.unk144) {                    /* switch 1 */
        case 0:                                     /* switch 1 */
            var_r5 = 0;
            gBingo.unk130 = 0;
            if ((u8) gBingo.cells[gBingo.unk134].unk0 == 0) {
                gBingo.unk10C = 1;
                var_r6 = mPokemon__6cBingo;
                temp_r3_2 = gBingo.unk12C + 1;
                var_ctr = 2;
loop_6:
                if (temp_r3_2 == (u8) var_r6->unkC5) {

                } else {
                    var_r5 += 1;
                    if (temp_r3_2 == (u8) var_r6[1].unkC5) {

                    } else {
                        temp_r6 = (BingoPokemon *)((u8 *)&var_r6[1] + 0xC8);
                        var_r5 += 1;
                        if (temp_r3_2 == (u8) temp_r6->unkC5) {

                        } else {
                            temp_r6_2 = (BingoPokemon *)((u8 *)temp_r6 + 0xC8);
                            var_r5 += 1;
                            if (temp_r3_2 == (u8) temp_r6_2->unkC5) {

                            } else {
                                temp_r6_3 = (BingoPokemon *)((u8 *)temp_r6_2 + 0xC8);
                                var_r5 += 1;
                                if (temp_r3_2 == (u8) temp_r6_3->unkC5) {

                                } else {
                                    temp_r6_4 = (BingoPokemon *)((u8 *)temp_r6_3 + 0xC8);
                                    var_r5 += 1;
                                    if (temp_r3_2 == (u8) temp_r6_4->unkC5) {

                                    } else {
                                        temp_r6_5 = (BingoPokemon *)((u8 *)temp_r6_4 + 0xC8);
                                        var_r5 += 1;
                                        if (temp_r3_2 == (u8) temp_r6_5->unkC5) {

                                        } else {
                                            var_r6 = (BingoPokemon *)((u8 *)temp_r6_5 + 0xC8);
                                            var_r5 += 1;
                                            var_ctr -= 1;
                                            if (var_ctr == 0) {
                                                var_r5 = -1U;
                                            } else {
                                                goto loop_6;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                setStaticIdx__10bingo_biosFUcUc(var_r5, gBingo.cells[gBingo.unk134].unk1);
                setStaticBall__10bingo_biosFUc(gBingo.unk129);
            }
            temp_r0 = gBingo.unk144 + 1;
            gBingo.unk144 = temp_r0;
            if (temp_r0 >= 0xC) {
                gBingo.unk144 = 0;
            }
            gBingo.unk124 = -1;
            if (arg0 != 0) {
                menuPlaySe(arg0->unk4);
            }
            break;
        case 1:                                     /* switch 1 */
            if (((u8) gBingo.unk10C == 0) && (winSeqCheckMove(0xC8) == 0)) {
                if (((u8) gBingo.cells[gBingo.unk134].unk0 != 0) && ((u8) gBingo.unk130 != 3) && ((u8) gBingo.unk130 != 4)) {
                    temp_r0_2 = arg0->unk9E;
                    if ((u8) gBingo.cells[temp_r0_2].unk2 != 0) {
                        var_r0 = 1;
                    } else {
                        var_r0 = 0;
                    }
                    if (var_r0 != 0) {
                        var_r0_2 = -1;
                    } else if ((u8) gBingo.cells[temp_r0_2].unk0 != 0) {
                        temp_r3_3 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(&gBingo, gBingo.unk4, (u32) gBingo.cells[temp_r0_2].unk1);
                        switch ((s32) temp_r3_3) {  /* switch 2; irregular */
                        case 0:                     /* switch 2 */
                            break;
                        case 1:                     /* switch 2 */
                            temp_r0_3 = gBingo.unk129 + 1;
                            gBingo.unk129 = temp_r0_3;
                            setStaticBall__10bingo_biosFUc(temp_r0_3);
                            break;
                        case 2:                     /* switch 2 */
                            gBingo.unk12A += 1;
                            break;
                        case 3:                     /* switch 2 */
                            gBingo.unk12A += 2;
                            break;
                        }
                        var_r0_2 = 1;
                    } else {
                        var_r0_2 = 0;
                    }
                    switch (var_r0_2) {             /* switch 3; irregular */
                    case 0:                         /* switch 3 */
                        gBingo.unk10C = 1;
                        var_r6_2 = mPokemon__6cBingo;
                        var_r5_2 = 0;
                        temp_r3_4 = gBingo.unk12C + 1;
                        var_ctr_2 = 2;
loop_57:
                        if (temp_r3_4 == (u8) var_r6_2->unkC5) {

                        } else {
                            var_r5_2 += 1;
                            if (temp_r3_4 == (u8) var_r6_2[1].unkC5) {

                            } else {
                                temp_r6_6 = (BingoPokemon *)((u8 *)&var_r6_2[1] + 0xC8);
                                var_r5_2 += 1;
                                if (temp_r3_4 == (u8) temp_r6_6->unkC5) {

                                } else {
                                    temp_r6_7 = (BingoPokemon *)((u8 *)temp_r6_6 + 0xC8);
                                    var_r5_2 += 1;
                                    if (temp_r3_4 == (u8) temp_r6_7->unkC5) {

                                    } else {
                                        temp_r6_8 = (BingoPokemon *)((u8 *)temp_r6_7 + 0xC8);
                                        var_r5_2 += 1;
                                        if (temp_r3_4 == (u8) temp_r6_8->unkC5) {

                                        } else {
                                            temp_r6_9 = (BingoPokemon *)((u8 *)temp_r6_8 + 0xC8);
                                            var_r5_2 += 1;
                                            if (temp_r3_4 == (u8) temp_r6_9->unkC5) {

                                            } else {
                                                temp_r6_10 = (BingoPokemon *)((u8 *)temp_r6_9 + 0xC8);
                                                var_r5_2 += 1;
                                                if (temp_r3_4 == (u8) temp_r6_10->unkC5) {

                                                } else {
                                                    var_r6_2 = (BingoPokemon *)((u8 *)temp_r6_10 + 0xC8);
                                                    var_r5_2 += 1;
                                                    var_ctr_2 -= 1;
                                                    if (var_ctr_2 == 0) {
                                                        var_r5_2 = -1U;
                                                    } else {
                                                        goto loop_57;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        setStaticIdx__10bingo_biosFUcUc(var_r5_2, gBingo.cells[gBingo.unk134].unk1);
                        setStaticBall__10bingo_biosFUc(gBingo.unk129);
                        temp_r0_4 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_4;
                        if (temp_r0_4 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                        if (arg0 != 0) {
                            menuPlaySe(arg0->unk4);
                        }
                        break;
                    case 1:                         /* switch 3 */
                        gBingo.cells[gBingo.unk134].unk2 = 1;
                        temp_r0_5 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_5;
                        if (temp_r0_5 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                        break;
                    case -1:                        /* switch 3 */
                        temp_r0_6 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_6;
                        if (temp_r0_6 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                        if (arg0 != 0) {
                            menuPlaySe(arg0->unk4);
                        }
                        break;
                    default:                        /* switch 3 */
                        menuPlaySe(arg0->unk4);
                        break;
                    }
                    var_r3 = 0;
                    var_r4 = 0;
                    var_ctr_3 = 0xA - 0;
                    if (0 < 0xA) {
                        do {
                            if (var_r4 != 8) {
                                if (var_r4 < 8) {
                                    if (var_r4 < 4) {
                                        if (var_r4 < 0) {
                                            goto block_144;
                                        }
                                        if ((u8) gBingo.cells[var_r4].unk2 != 0) {
                                            if (0U == 3U) {
                                                var_r8 = 1;
                                            } else {
                                                temp_r5 = (var_r4 * 8) + 0x20;
                                                var_r8 = 1;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5) + 0xA) != 0) {
                                                    if (1U == 3U) {

                                                    } else {
                                                        temp_r5_2 = temp_r5 + 0x20;
                                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5_2) + 0xA) != 0) {
                                                            if (2U == 3U) {
                                                                var_r8 = 1;
                                                            } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r5_2 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                                var_r8 = 1;
                                                            } else {
                                                                goto block_144;
                                                            }
                                                        } else {
                                                            goto block_144;
                                                        }
                                                    }
                                                } else {
                                                    goto block_144;
                                                }
                                            }
                                        } else {
                                            goto block_144;
                                        }
                                    } else {
                                        temp_r5_3 = (7 - var_r4) * 4;
                                        if ((u8) gBingo.cells[temp_r5_3].unk2 != 0) {
                                            if (0U == 3U) {
                                                var_r8 = 1;
                                            } else {
                                                var_r8 = 1;
                                                if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r5_3] + 0xA) != 0) {
                                                    if (1U == 3U) {

                                                    } else {
                                                        temp_r5_4 = (temp_r5_3 * 8) + 8 + 8;
                                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5_4) + 0xA) != 0) {
                                                            if (2U == 3U) {
                                                                var_r8 = 1;
                                                            } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r5_4 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                                var_r8 = 1;
                                                            } else {
                                                                goto block_144;
                                                            }
                                                        } else {
                                                            goto block_144;
                                                        }
                                                    }
                                                } else {
                                                    goto block_144;
                                                }
                                            }
                                        } else {
                                            goto block_144;
                                        }
                                    }
                                } else if (var_r4 < 0xA) {
                                    if ((u8) gBingo.cells[0].unk2 != 0) {
                                        if (0U == 3U) {
                                            var_r8 = 1;
                                        } else {
                                            var_r8 = 1;
                                            if ((u8) gBingo.cells[5].unk2 != 0) {
                                                if (1U == 3U) {

                                                } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                                    if (2U == 3U) {
                                                        var_r8 = 1;
                                                    } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                        var_r8 = 1;
                                                    } else {
                                                        goto block_144;
                                                    }
                                                } else {
                                                    goto block_144;
                                                }
                                            } else {
                                                goto block_144;
                                            }
                                        }
                                    } else {
                                        goto block_144;
                                    }
                                } else {
                                    goto block_144;
                                }
                            } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                                if (0U == 3U) {
                                    var_r8 = 1;
                                } else {
                                    var_r8 = 1;
                                    if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                        if (1U == 3U) {

                                        } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                            if (2U == 3U) {
                                                var_r8 = 1;
                                            } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                                var_r8 = 1;
                                            } else {
                                                goto block_144;
                                            }
                                        } else {
                                            goto block_144;
                                        }
                                    } else {
                                        goto block_144;
                                    }
                                }
                            } else {
block_144:
                                var_r8 = 0;
                            }
                            if (var_r8 != 0) {
                                var_r3 += 1;
                            }
                            var_r4 += 1;
                            var_ctr_3 -= 1;
                        } while (var_ctr_3 != 0);
                    }
                    if ((s32) (var_r3 - gBingo.unk12D) != 0) {
                        GSsndPlayNow(0x575);
                    } else {
                        GSsndPlayNow(0x574);
                    }
                } else if ((u8) gBingo.unk130 != 0) {
                    if ((u8) gBingo.unk130 == 2) {
                        temp_r27 = gBingo.unk129;
                        if (temp_r27 == getStaticBall__10bingo_biosFv()) {
                            gBingo.cells[gBingo.unk134].unk2 = 1;
                        } else {
                            var_r6_3 = 0;
                            gBingo.cells[gBingo.unk134].unk2 = 1;
loop_156:
                            var_r7 = mPokemon__6cBingo;
                            var_r5_3 = 0;
                            temp_r3_5 = var_r6_3 + 1;
                            var_ctr_4 = 2;
loop_157:
                            if (temp_r3_5 == (u8) var_r7->unkC5) {

                            } else {
                                var_r5_3 += 1;
                                if (temp_r3_5 == (u8) var_r7[1].unkC5) {

                                } else {
                                    temp_r7 = (BingoPokemon *)((u8 *)&var_r7[1] + 0xC8);
                                    var_r5_3 += 1;
                                    if (temp_r3_5 == (u8) temp_r7->unkC5) {

                                    } else {
                                        temp_r7_2 = (BingoPokemon *)((u8 *)temp_r7 + 0xC8);
                                        var_r5_3 += 1;
                                        if (temp_r3_5 == (u8) temp_r7_2->unkC5) {

                                        } else {
                                            temp_r7_3 = (BingoPokemon *)((u8 *)temp_r7_2 + 0xC8);
                                            var_r5_3 += 1;
                                            if (temp_r3_5 == (u8) temp_r7_3->unkC5) {

                                            } else {
                                                temp_r7_4 = (BingoPokemon *)((u8 *)temp_r7_3 + 0xC8);
                                                var_r5_3 += 1;
                                                if (temp_r3_5 == (u8) temp_r7_4->unkC5) {

                                                } else {
                                                    temp_r7_5 = (BingoPokemon *)((u8 *)temp_r7_4 + 0xC8);
                                                    var_r5_3 += 1;
                                                    if (temp_r3_5 == (u8) temp_r7_5->unkC5) {

                                                    } else {
                                                        var_r7 = (BingoPokemon *)((u8 *)temp_r7_5 + 0xC8);
                                                        var_r5_3 += 1;
                                                        var_ctr_4 -= 1;
                                                        if (var_ctr_4 == 0) {
                                                            var_r5_3 = -1;
                                                        } else {
                                                            goto loop_157;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            if (var_r5_3 != -1) {
                                var_r6_3 += 1;
                                if (var_r6_3 < 4) {
                                    goto loop_156;
                                }
                            }
                            temp_r4 = &mPokemon__6cBingo[gBingo.cells[gBingo.unk134].unk1];
                            temp_r4->unkC5 = var_r6_3 + 1;
                            temp_r4->unkC4 = 2;
                            temp_r4->unkC6 = 0;
                        }
                        var_r3_2 = 0;
                        var_r4_2 = 0;
                        var_ctr_5 = 0xA - 0;
                        if (0 < 0xA) {
                            do {
                                if (var_r4_2 != 8) {
                                    if (var_r4_2 < 8) {
                                        if (var_r4_2 < 4) {
                                            if (var_r4_2 < 0) {
                                                goto block_235;
                                            }
                                            if ((u8) gBingo.cells[var_r4_2].unk2 != 0) {
                                                if (0U == 3U) {
                                                    var_r5_4 = 1;
                                                } else {
                                                    temp_r6_11 = (var_r4_2 * 8) + 0x20;
                                                    var_r5_4 = 1;
                                                    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_11) + 0xA) != 0) {
                                                        if (1U == 3U) {

                                                        } else {
                                                            temp_r6_12 = temp_r6_11 + 0x20;
                                                            if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_12) + 0xA) != 0) {
                                                                if (2U == 3U) {
                                                                    var_r5_4 = 1;
                                                                } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r6_12 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                                    var_r5_4 = 1;
                                                                } else {
                                                                    goto block_235;
                                                                }
                                                            } else {
                                                                goto block_235;
                                                            }
                                                        }
                                                    } else {
                                                        goto block_235;
                                                    }
                                                }
                                            } else {
                                                goto block_235;
                                            }
                                        } else {
                                            temp_r6_13 = (7 - var_r4_2) * 4;
                                            if ((u8) gBingo.cells[temp_r6_13].unk2 != 0) {
                                                if (0U == 3U) {
                                                    var_r5_4 = 1;
                                                } else {
                                                    var_r5_4 = 1;
                                                    if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r6_13] + 0xA) != 0) {
                                                        if (1U == 3U) {

                                                        } else {
                                                            temp_r6_14 = (temp_r6_13 * 8) + 8 + 8;
                                                            if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_14) + 0xA) != 0) {
                                                                if (2U == 3U) {
                                                                    var_r5_4 = 1;
                                                                } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r6_14 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                                    var_r5_4 = 1;
                                                                } else {
                                                                    goto block_235;
                                                                }
                                                            } else {
                                                                goto block_235;
                                                            }
                                                        }
                                                    } else {
                                                        goto block_235;
                                                    }
                                                }
                                            } else {
                                                goto block_235;
                                            }
                                        }
                                    } else if (var_r4_2 < 0xA) {
                                        if ((u8) gBingo.cells[0].unk2 != 0) {
                                            if (0U == 3U) {
                                                var_r5_4 = 1;
                                            } else {
                                                var_r5_4 = 1;
                                                if ((u8) gBingo.cells[5].unk2 != 0) {
                                                    if (1U == 3U) {

                                                    } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                                        if (2U == 3U) {
                                                            var_r5_4 = 1;
                                                        } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                            var_r5_4 = 1;
                                                        } else {
                                                            goto block_235;
                                                        }
                                                    } else {
                                                        goto block_235;
                                                    }
                                                } else {
                                                    goto block_235;
                                                }
                                            }
                                        } else {
                                            goto block_235;
                                        }
                                    } else {
                                        goto block_235;
                                    }
                                } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r5_4 = 1;
                                    } else {
                                        var_r5_4 = 1;
                                        if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                            if (1U == 3U) {

                                            } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                                if (2U == 3U) {
                                                    var_r5_4 = 1;
                                                } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                                    var_r5_4 = 1;
                                                } else {
                                                    goto block_235;
                                                }
                                            } else {
                                                goto block_235;
                                            }
                                        } else {
                                            goto block_235;
                                        }
                                    }
                                } else {
block_235:
                                    var_r5_4 = 0;
                                }
                                if (var_r5_4 != 0) {
                                    var_r3_2 += 1;
                                }
                                var_r4_2 += 1;
                                var_ctr_5 -= 1;
                            } while (var_ctr_5 != 0);
                        }
                        if ((s32) (var_r3_2 - gBingo.unk12D) != 0) {
                            GSsndPlayNow(0x575);
                        } else {
                            GSsndPlayNow(0x574);
                        }
                        temp_r0_7 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_7;
                        if (temp_r0_7 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                    } else {
                        temp_r0_8 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_8;
                        if (temp_r0_8 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                        if (arg0 != 0) {
                            menuPlaySe(arg0->unk4);
                        }
                    }
                }
            }
            break;
        case 2:                                     /* switch 1 */
            if ((s32) (temp_r3 & 0x10) != 0) {
                var_r3_3 = 0;
                var_r4_3 = 0;
                var_ctr_6 = 0xA - 0;
                if (0 < 0xA) {
                    do {
                        if (var_r4_3 != 8) {
                            if (var_r4_3 < 8) {
                                if (var_r4_3 < 4) {
                                    if (var_r4_3 < 0) {
                                        goto block_309;
                                    }
                                    if ((u8) gBingo.cells[var_r4_3].unk2 != 0) {
                                        if (0U == 3U) {
                                            var_r0_3 = 1;
                                        } else {
                                            temp_r5_5 = (var_r4_3 * 8) + 0x20;
                                            var_r0_3 = 1;
                                            if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5_5) + 0xA) != 0) {
                                                if (1U == 3U) {

                                                } else {
                                                    temp_r5_6 = temp_r5_5 + 0x20;
                                                    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5_6) + 0xA) != 0) {
                                                        if (2U == 3U) {
                                                            var_r0_3 = 1;
                                                        } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r5_6 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                            var_r0_3 = 1;
                                                        } else {
                                                            goto block_309;
                                                        }
                                                    } else {
                                                        goto block_309;
                                                    }
                                                }
                                            } else {
                                                goto block_309;
                                            }
                                        }
                                    } else {
                                        goto block_309;
                                    }
                                } else {
                                    temp_r5_7 = (7 - var_r4_3) * 4;
                                    if ((u8) gBingo.cells[temp_r5_7].unk2 != 0) {
                                        if (0U == 3U) {
                                            var_r0_3 = 1;
                                        } else {
                                            var_r0_3 = 1;
                                            if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r5_7] + 0xA) != 0) {
                                                if (1U == 3U) {

                                                } else {
                                                    temp_r5_8 = (temp_r5_7 * 8) + 8 + 8;
                                                    if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r5_8) + 0xA) != 0) {
                                                        if (2U == 3U) {
                                                            var_r0_3 = 1;
                                                        } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r5_8 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                            var_r0_3 = 1;
                                                        } else {
                                                            goto block_309;
                                                        }
                                                    } else {
                                                        goto block_309;
                                                    }
                                                }
                                            } else {
                                                goto block_309;
                                            }
                                        }
                                    } else {
                                        goto block_309;
                                    }
                                }
                            } else if (var_r4_3 < 0xA) {
                                if ((u8) gBingo.cells[0].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r0_3 = 1;
                                    } else {
                                        var_r0_3 = 1;
                                        if ((u8) gBingo.cells[5].unk2 != 0) {
                                            if (1U == 3U) {

                                            } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                                if (2U == 3U) {
                                                    var_r0_3 = 1;
                                                } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                    var_r0_3 = 1;
                                                } else {
                                                    goto block_309;
                                                }
                                            } else {
                                                goto block_309;
                                            }
                                        } else {
                                            goto block_309;
                                        }
                                    }
                                } else {
                                    goto block_309;
                                }
                            } else {
                                goto block_309;
                            }
                        } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                            if (0U == 3U) {
                                var_r0_3 = 1;
                            } else {
                                var_r0_3 = 1;
                                if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                    if (1U == 3U) {

                                    } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                        if (2U == 3U) {
                                            var_r0_3 = 1;
                                        } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                            var_r0_3 = 1;
                                        } else {
                                            goto block_309;
                                        }
                                    } else {
                                        goto block_309;
                                    }
                                } else {
                                    goto block_309;
                                }
                            }
                        } else {
block_309:
                            var_r0_3 = 0;
                        }
                        if (var_r0_3 != 0) {
                            var_r3_3 += 1;
                        }
                        var_r4_3 += 1;
                        var_ctr_6 -= 1;
                    } while (var_ctr_6 != 0);
                }
                gBingo.unk129 = getStaticBall__10bingo_biosFv();
                if ((s32) var_r3_3 == 0xA) {
                    gBingo.unk108 = 2;
                    gBingo.unk12A += (u8) (var_r3_3 - gBingo.unk12D);
                } else {
                    temp_r0_9 = gBingo.unk144 + 1;
                    gBingo.unk144 = temp_r0_9;
                    if (temp_r0_9 >= 0xC) {
                        gBingo.unk144 = 0;
                    }
                    gBingo.unk124 = -1;
                    if (arg0 != 0) {
                        menuPlaySe(arg0->unk4);
                    }
                }
            }
            break;
        case 3:                                     /* switch 1 */
            var_r4_4 = 0;
            var_r5_5 = 0;
            var_ctr_7 = 0xA - 0;
            if (0 < 0xA) {
                do {
                    if (var_r5_5 != 8) {
                        if (var_r5_5 < 8) {
                            if (var_r5_5 < 4) {
                                if (var_r5_5 < 0) {
                                    goto block_378;
                                }
                                if ((u8) gBingo.cells[var_r5_5].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r0_4 = 1;
                                    } else {
                                        temp_r6_15 = (var_r5_5 * 8) + 0x20;
                                        var_r0_4 = 1;
                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_15) + 0xA) != 0) {
                                            if (1U == 3U) {

                                            } else {
                                                temp_r6_16 = temp_r6_15 + 0x20;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_16) + 0xA) != 0) {
                                                    if (2U == 3U) {
                                                        var_r0_4 = 1;
                                                    } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r6_16 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                        var_r0_4 = 1;
                                                    } else {
                                                        goto block_378;
                                                    }
                                                } else {
                                                    goto block_378;
                                                }
                                            }
                                        } else {
                                            goto block_378;
                                        }
                                    }
                                } else {
                                    goto block_378;
                                }
                            } else {
                                temp_r6_17 = (7 - var_r5_5) * 4;
                                if ((u8) gBingo.cells[temp_r6_17].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r0_4 = 1;
                                    } else {
                                        var_r0_4 = 1;
                                        if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r6_17] + 0xA) != 0) {
                                            if (1U == 3U) {

                                            } else {
                                                temp_r6_18 = (temp_r6_17 * 8) + 8 + 8;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r6_18) + 0xA) != 0) {
                                                    if (2U == 3U) {
                                                        var_r0_4 = 1;
                                                    } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r6_18 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                        var_r0_4 = 1;
                                                    } else {
                                                        goto block_378;
                                                    }
                                                } else {
                                                    goto block_378;
                                                }
                                            }
                                        } else {
                                            goto block_378;
                                        }
                                    }
                                } else {
                                    goto block_378;
                                }
                            }
                        } else if (var_r5_5 < 0xA) {
                            if ((u8) gBingo.cells[0].unk2 != 0) {
                                if (0U == 3U) {
                                    var_r0_4 = 1;
                                } else {
                                    var_r0_4 = 1;
                                    if ((u8) gBingo.cells[5].unk2 != 0) {
                                        if (1U == 3U) {

                                        } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                            if (2U == 3U) {
                                                var_r0_4 = 1;
                                            } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                var_r0_4 = 1;
                                            } else {
                                                goto block_378;
                                            }
                                        } else {
                                            goto block_378;
                                        }
                                    } else {
                                        goto block_378;
                                    }
                                }
                            } else {
                                goto block_378;
                            }
                        } else {
                            goto block_378;
                        }
                    } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                        if (0U == 3U) {
                            var_r0_4 = 1;
                        } else {
                            var_r0_4 = 1;
                            if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                if (1U == 3U) {

                                } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                    if (2U == 3U) {
                                        var_r0_4 = 1;
                                    } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                        var_r0_4 = 1;
                                    } else {
                                        goto block_378;
                                    }
                                } else {
                                    goto block_378;
                                }
                            } else {
                                goto block_378;
                            }
                        }
                    } else {
block_378:
                        var_r0_4 = 0;
                    }
                    if (var_r0_4 != 0) {
                        var_r4_4 += 1;
                    }
                    var_r5_5 += 1;
                    var_ctr_7 -= 1;
                } while (var_ctr_7 != 0);
            }
            if ((s32) var_r4_4 == 0xA) {
                gBingo.unk108 = 2;
                gBingo.unk12A += (u8) (var_r4_4 - gBingo.unk12D);
            } else {
                temp_r6_19 = var_r4_4 - gBingo.unk12D;
                gBingo.unk12F = gBingo.unk12A;
                if (temp_r6_19 == 0) {
                    temp_r0_10 = gBingo.unk144 + 1;
                    gBingo.unk144 = temp_r0_10;
                    if (temp_r0_10 >= 0xC) {
                        gBingo.unk144 = 0;
                    }
                    gBingo.unk124 = -1;
                } else if ((s32) (temp_r3 & 0x10) != 0) {
                    temp_r4_2 = gBingo.unk12A + (u8) temp_r6_19;
                    temp_r0_11 = gBingo.unk144 + 1;
                    gBingo.unk12A = temp_r4_2;
                    gBingo.unk12F = temp_r4_2;
                    gBingo.unk144 = temp_r0_11;
                    if (temp_r0_11 >= 0xC) {
                        gBingo.unk144 = 0;
                    }
                    gBingo.unk124 = -1;
                    if (arg0 != 0) {
                        menuPlaySe(arg0->unk4);
                    }
                }
            }
            break;
        case 4:                                     /* switch 1 */
            var_r4_5 = 0;
            var_r5_6 = 0;
            var_ctr_8 = 0xA - 0;
            if (0 < 0xA) {
                do {
                    if (var_r5_6 != 8) {
                        if (var_r5_6 < 8) {
                            if (var_r5_6 < 4) {
                                if (var_r5_6 < 0) {
                                    goto block_452;
                                }
                                if ((u8) gBingo.cells[var_r5_6].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r6_4 = 1;
                                    } else {
                                        temp_r7_6 = (var_r5_6 * 8) + 0x20;
                                        var_r6_4 = 1;
                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_6) + 0xA) != 0) {
                                            if (1U == 3U) {

                                            } else {
                                                temp_r7_7 = temp_r7_6 + 0x20;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_7) + 0xA) != 0) {
                                                    if (2U == 3U) {
                                                        var_r6_4 = 1;
                                                    } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r7_7 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                        var_r6_4 = 1;
                                                    } else {
                                                        goto block_452;
                                                    }
                                                } else {
                                                    goto block_452;
                                                }
                                            }
                                        } else {
                                            goto block_452;
                                        }
                                    }
                                } else {
                                    goto block_452;
                                }
                            } else {
                                temp_r7_8 = (7 - var_r5_6) * 4;
                                if ((u8) gBingo.cells[temp_r7_8].unk2 != 0) {
                                    if (0U == 3U) {
                                        var_r6_4 = 1;
                                    } else {
                                        var_r6_4 = 1;
                                        if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r7_8] + 0xA) != 0) {
                                            if (1U == 3U) {

                                            } else {
                                                temp_r7_9 = (temp_r7_8 * 8) + 8 + 8;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_9) + 0xA) != 0) {
                                                    if (2U == 3U) {
                                                        var_r6_4 = 1;
                                                    } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r7_9 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                        var_r6_4 = 1;
                                                    } else {
                                                        goto block_452;
                                                    }
                                                } else {
                                                    goto block_452;
                                                }
                                            }
                                        } else {
                                            goto block_452;
                                        }
                                    }
                                } else {
                                    goto block_452;
                                }
                            }
                        } else if (var_r5_6 < 0xA) {
                            if ((u8) gBingo.cells[0].unk2 != 0) {
                                if (0U == 3U) {
                                    var_r6_4 = 1;
                                } else {
                                    var_r6_4 = 1;
                                    if ((u8) gBingo.cells[5].unk2 != 0) {
                                        if (1U == 3U) {

                                        } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                            if (2U == 3U) {
                                                var_r6_4 = 1;
                                            } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                var_r6_4 = 1;
                                            } else {
                                                goto block_452;
                                            }
                                        } else {
                                            goto block_452;
                                        }
                                    } else {
                                        goto block_452;
                                    }
                                }
                            } else {
                                goto block_452;
                            }
                        } else {
                            goto block_452;
                        }
                    } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                        if (0U == 3U) {
                            var_r6_4 = 1;
                        } else {
                            var_r6_4 = 1;
                            if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                if (1U == 3U) {

                                } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                    if (2U == 3U) {
                                        var_r6_4 = 1;
                                    } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                        var_r6_4 = 1;
                                    } else {
                                        goto block_452;
                                    }
                                } else {
                                    goto block_452;
                                }
                            } else {
                                goto block_452;
                            }
                        }
                    } else {
block_452:
                        var_r6_4 = 0;
                    }
                    if (var_r6_4 != 0) {
                        var_r4_5 += 1;
                    }
                    var_r5_6 += 1;
                    var_ctr_8 -= 1;
                } while (var_ctr_8 != 0);
            }
            if ((s32) (var_r4_5 - gBingo.unk12D) == 0) {
                if ((u8) gBingo.unk12A != 0) {
                    temp_r0_12 = gBingo.unk144 + 1;
                    gBingo.unk144 = temp_r0_12;
                    if (temp_r0_12 >= 0xC) {
                        gBingo.unk144 = 0;
                    }
                    gBingo.unk124 = -1;
                } else {
                    gBingo.unk144 = 7;
                    gBingo.unk124 = -1;
                }
            }
            if ((s32) (temp_r3 & 0x10) != 0) {
                temp_r0_13 = gBingo.unk144 + 1;
                gBingo.unk144 = temp_r0_13;
                if (temp_r0_13 >= 0xC) {
                    gBingo.unk144 = 0;
                }
                gBingo.unk124 = -1;
                if (arg0 != 0) {
                    menuPlaySe(arg0->unk4);
                }
            }
            break;
        case 5:                                     /* switch 1 */
            if ((u8) gBingo.unk12A == 0) {
                temp_r0_14 = gBingo.unk144 + 1;
                gBingo.unk144 = temp_r0_14;
                if (temp_r0_14 >= 0xC) {
                    gBingo.unk144 = 0;
                }
                gBingo.unk124 = -1;
            } else {
                var_r6_5 = 0;
loop_472:
                var_r8_2 = mPokemon__6cBingo;
                var_r7_2 = 0;
                temp_r4_3 = var_r6_5 + 1;
                var_ctr_9 = 2;
loop_473:
                if (temp_r4_3 == (u8) var_r8_2->unkC5) {

                } else {
                    var_r7_2 += 1;
                    if (temp_r4_3 == (u8) var_r8_2[1].unkC5) {

                    } else {
                        temp_r8 = (BingoPokemon *)((u8 *)&var_r8_2[1] + 0xC8);
                        var_r7_2 += 1;
                        if (temp_r4_3 == (u8) temp_r8->unkC5) {

                        } else {
                            temp_r8_2 = (BingoPokemon *)((u8 *)temp_r8 + 0xC8);
                            var_r7_2 += 1;
                            if (temp_r4_3 == (u8) temp_r8_2->unkC5) {

                            } else {
                                temp_r8_3 = (BingoPokemon *)((u8 *)temp_r8_2 + 0xC8);
                                var_r7_2 += 1;
                                if (temp_r4_3 == (u8) temp_r8_3->unkC5) {

                                } else {
                                    temp_r8_4 = (BingoPokemon *)((u8 *)temp_r8_3 + 0xC8);
                                    var_r7_2 += 1;
                                    if (temp_r4_3 == (u8) temp_r8_4->unkC5) {

                                    } else {
                                        temp_r8_5 = (BingoPokemon *)((u8 *)temp_r8_4 + 0xC8);
                                        var_r7_2 += 1;
                                        if (temp_r4_3 == (u8) temp_r8_5->unkC5) {

                                        } else {
                                            var_r8_2 = (BingoPokemon *)((u8 *)temp_r8_5 + 0xC8);
                                            var_r7_2 += 1;
                                            var_ctr_9 -= 1;
                                            if (var_ctr_9 == 0) {
                                                var_r7_2 = -1;
                                            } else {
                                                goto loop_473;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (var_r7_2 != -1) {
                    var_r6_5 += 1;
                    if (var_r6_5 < 4) {
                        goto loop_472;
                    }
                }
                if ((s32) (temp_r3 & 0x10) != 0) {
                    gBingo.unk124 = -2;
                } else if ((s32) (temp_r29 & 1) != 0) {
                    if ((u8) gBingo.unk12C != 0) {
                        gBingo.unk12C -= 1;
                        menuPlaySe(arg0->unk4);
                    }
                } else if (((s32) (temp_r29 & 2) != 0) && ((s32) gBingo.unk12C < (s32) (var_r6_5 - 1))) {
                    gBingo.unk12C += 1;
                    menuPlaySe(arg0->unk4);
                }
                temp_r0_15 = gBingo.unk124 - 1;
                switch (temp_r0_15) {               /* switch 4; irregular */
                case 0:                             /* switch 4 */
                    var_r7_3 = mPokemon__6cBingo;
                    var_r4_6 = 0;
                    temp_r3_6 = gBingo.unk12C + 1;
                    var_ctr_10 = 2;
loop_506:
                    if (temp_r3_6 == (u8) var_r7_3->unkC5) {

                    } else {
                        var_r4_6 += 1;
                        if (temp_r3_6 == (u8) var_r7_3[1].unkC5) {

                        } else {
                            temp_r7_10 = (BingoPokemon *)((u8 *)&var_r7_3[1] + 0xC8);
                            var_r4_6 += 1;
                            if (temp_r3_6 == (u8) temp_r7_10->unkC5) {

                            } else {
                                temp_r7_11 = (BingoPokemon *)((u8 *)temp_r7_10 + 0xC8);
                                var_r4_6 += 1;
                                if (temp_r3_6 == (u8) temp_r7_11->unkC5) {

                                } else {
                                    temp_r7_12 = (BingoPokemon *)((u8 *)temp_r7_11 + 0xC8);
                                    var_r4_6 += 1;
                                    if (temp_r3_6 == (u8) temp_r7_12->unkC5) {

                                    } else {
                                        temp_r7_13 = (BingoPokemon *)((u8 *)temp_r7_12 + 0xC8);
                                        var_r4_6 += 1;
                                        if (temp_r3_6 == (u8) temp_r7_13->unkC5) {

                                        } else {
                                            temp_r7_14 = (BingoPokemon *)((u8 *)temp_r7_13 + 0xC8);
                                            var_r4_6 += 1;
                                            if (temp_r3_6 == (u8) temp_r7_14->unkC5) {

                                            } else {
                                                var_r7_3 = (BingoPokemon *)((u8 *)temp_r7_14 + 0xC8);
                                                var_r4_6 += 1;
                                                var_ctr_10 -= 1;
                                                if (var_ctr_10 == 0) {
                                                    var_r4_6 = -1;
                                                } else {
                                                    goto loop_506;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (var_r4_6 >= 0) {
                        temp_r5_9 = &mPokemon__6cBingo[var_r4_6];
                        temp_r5_9->unkC6 += 1;
                        if ((u8) gBingo.unk12A != 0) {
                            gBingo.unk12A -= 1;
                        }
                    }
                    gBingo.unk124 = -1;
                    if ((u8) gBingo.unk12A == 0) {
                        temp_r0_16 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_16;
                        if (temp_r0_16 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                    }
                    break;
                case 1:                             /* switch 4 */
                    gBingo.unk124 = -1;
                    break;
                }
            }
            break;
        case 6:                                     /* switch 1 */
            if ((u8) gBingo.unk12F != 0) {
                temp_r0_17 = gBingo.unk124 - 1;
                switch (temp_r0_17) {               /* switch 5; irregular */
                case 0:                             /* switch 5 */
                    var_r3_4 = 0U;
loop_590:
                    var_r7_4 = 0;
loop_591:
                    var_r9 = mPokemon__6cBingo;
                    var_r8_3 = 0;
                    temp_r5_10 = var_r7_4 + 1;
                    var_ctr_11 = 2;
loop_592:
                    if (temp_r5_10 == (u8) var_r9->unkC5) {

                    } else {
                        var_r8_3 += 1;
                        if (temp_r5_10 == (u8) var_r9[1].unkC5) {

                        } else {
                            temp_r9 = (BingoPokemon *)((u8 *)&var_r9[1] + 0xC8);
                            var_r8_3 += 1;
                            if (temp_r5_10 == (u8) temp_r9->unkC5) {

                            } else {
                                temp_r9_2 = (BingoPokemon *)((u8 *)temp_r9 + 0xC8);
                                var_r8_3 += 1;
                                if (temp_r5_10 == (u8) temp_r9_2->unkC5) {

                                } else {
                                    temp_r9_3 = (BingoPokemon *)((u8 *)temp_r9_2 + 0xC8);
                                    var_r8_3 += 1;
                                    if (temp_r5_10 == (u8) temp_r9_3->unkC5) {

                                    } else {
                                        temp_r9_4 = (BingoPokemon *)((u8 *)temp_r9_3 + 0xC8);
                                        var_r8_3 += 1;
                                        if (temp_r5_10 == (u8) temp_r9_4->unkC5) {

                                        } else {
                                            temp_r9_5 = (BingoPokemon *)((u8 *)temp_r9_4 + 0xC8);
                                            var_r8_3 += 1;
                                            if (temp_r5_10 == (u8) temp_r9_5->unkC5) {

                                            } else {
                                                var_r9 = (BingoPokemon *)((u8 *)temp_r9_5 + 0xC8);
                                                var_r8_3 += 1;
                                                var_ctr_11 -= 1;
                                                if (var_ctr_11 == 0) {
                                                    var_r8_3 = -1;
                                                } else {
                                                    goto loop_592;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (var_r8_3 != -1) {
                        var_r7_4 += 1;
                        if (var_r7_4 < 4) {
                            goto loop_591;
                        }
                    }
                    if (var_r3_4 < (u32) var_r7_4) {
                        var_r8_4 = mPokemon__6cBingo;
                        var_r7_5 = 0;
                        temp_r5_11 = var_r3_4 + 1;
                        var_ctr_12 = 2;
loop_539:
                        if (temp_r5_11 == (u8) var_r8_4->unkC5) {

                        } else {
                            var_r7_5 += 1;
                            if (temp_r5_11 == (u8) var_r8_4[1].unkC5) {

                            } else {
                                temp_r8_6 = (BingoPokemon *)((u8 *)&var_r8_4[1] + 0xC8);
                                var_r7_5 += 1;
                                if (temp_r5_11 == (u8) temp_r8_6->unkC5) {

                                } else {
                                    temp_r8_7 = (BingoPokemon *)((u8 *)temp_r8_6 + 0xC8);
                                    var_r7_5 += 1;
                                    if (temp_r5_11 == (u8) temp_r8_7->unkC5) {

                                    } else {
                                        temp_r8_8 = (BingoPokemon *)((u8 *)temp_r8_7 + 0xC8);
                                        var_r7_5 += 1;
                                        if (temp_r5_11 == (u8) temp_r8_8->unkC5) {

                                        } else {
                                            temp_r8_9 = (BingoPokemon *)((u8 *)temp_r8_8 + 0xC8);
                                            var_r7_5 += 1;
                                            if (temp_r5_11 == (u8) temp_r8_9->unkC5) {

                                            } else {
                                                temp_r8_10 = (BingoPokemon *)((u8 *)temp_r8_9 + 0xC8);
                                                var_r7_5 += 1;
                                                if (temp_r5_11 == (u8) temp_r8_10->unkC5) {

                                                } else {
                                                    var_r8_4 = (BingoPokemon *)((u8 *)temp_r8_10 + 0xC8);
                                                    var_r7_5 += 1;
                                                    var_ctr_12 -= 1;
                                                    if (var_ctr_12 == 0) {
                                                        var_r7_5 = -1;
                                                    } else {
                                                        goto loop_539;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        var_r9_2 = mPokemon__6cBingo;
                        var_r8_5 = 0;
                        temp_r7_15 = &mPokemon__6cBingo[var_r7_5];
                        temp_r5_12 = var_r3_4 + 1;
                        var_ctr_13 = 2;
loop_556:
                        if (temp_r5_12 == (u8) var_r9_2->unkC5) {

                        } else {
                            var_r8_5 += 1;
                            if (temp_r5_12 == (u8) var_r9_2[1].unkC5) {

                            } else {
                                temp_r9_6 = (BingoPokemon *)((u8 *)&var_r9_2[1] + 0xC8);
                                var_r8_5 += 1;
                                if (temp_r5_12 == (u8) temp_r9_6->unkC5) {

                                } else {
                                    temp_r9_7 = (BingoPokemon *)((u8 *)temp_r9_6 + 0xC8);
                                    var_r8_5 += 1;
                                    if (temp_r5_12 == (u8) temp_r9_7->unkC5) {

                                    } else {
                                        temp_r9_8 = (BingoPokemon *)((u8 *)temp_r9_7 + 0xC8);
                                        var_r8_5 += 1;
                                        if (temp_r5_12 == (u8) temp_r9_8->unkC5) {

                                        } else {
                                            temp_r9_9 = (BingoPokemon *)((u8 *)temp_r9_8 + 0xC8);
                                            var_r8_5 += 1;
                                            if (temp_r5_12 == (u8) temp_r9_9->unkC5) {

                                            } else {
                                                temp_r9_10 = (BingoPokemon *)((u8 *)temp_r9_9 + 0xC8);
                                                var_r8_5 += 1;
                                                if (temp_r5_12 == (u8) temp_r9_10->unkC5) {

                                                } else {
                                                    var_r9_2 = (BingoPokemon *)((u8 *)temp_r9_10 + 0xC8);
                                                    var_r8_5 += 1;
                                                    var_ctr_13 -= 1;
                                                    if (var_ctr_13 == 0) {
                                                        var_r8_5 = -1;
                                                    } else {
                                                        goto loop_556;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        var_r9_3 = mPokemon__6cBingo;
                        var_r8_6 = 0;
                        temp_r7_15->unkC4 += mPokemon__6cBingo[var_r8_5].unkC6;
                        temp_r5_13 = var_r3_4 + 1;
                        var_ctr_14 = 2;
loop_573:
                        if (temp_r5_13 == (u8) var_r9_3->unkC5) {

                        } else {
                            var_r8_6 += 1;
                            if (temp_r5_13 == (u8) var_r9_3[1].unkC5) {

                            } else {
                                temp_r9_11 = (BingoPokemon *)((u8 *)&var_r9_3[1] + 0xC8);
                                var_r8_6 += 1;
                                if (temp_r5_13 == (u8) temp_r9_11->unkC5) {

                                } else {
                                    temp_r9_12 = (BingoPokemon *)((u8 *)temp_r9_11 + 0xC8);
                                    var_r8_6 += 1;
                                    if (temp_r5_13 == (u8) temp_r9_12->unkC5) {

                                    } else {
                                        temp_r9_13 = (BingoPokemon *)((u8 *)temp_r9_12 + 0xC8);
                                        var_r8_6 += 1;
                                        if (temp_r5_13 == (u8) temp_r9_13->unkC5) {

                                        } else {
                                            temp_r9_14 = (BingoPokemon *)((u8 *)temp_r9_13 + 0xC8);
                                            var_r8_6 += 1;
                                            if (temp_r5_13 == (u8) temp_r9_14->unkC5) {

                                            } else {
                                                temp_r9_15 = (BingoPokemon *)((u8 *)temp_r9_14 + 0xC8);
                                                var_r8_6 += 1;
                                                if (temp_r5_13 == (u8) temp_r9_15->unkC5) {

                                                } else {
                                                    var_r9_3 = (BingoPokemon *)((u8 *)temp_r9_15 + 0xC8);
                                                    var_r8_6 += 1;
                                                    var_ctr_14 -= 1;
                                                    if (var_ctr_14 == 0) {
                                                        var_r8_6 = -1;
                                                    } else {
                                                        goto loop_573;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        var_r3_4 += 1;
                        mPokemon__6cBingo[var_r8_6].unkC6 = 0;
                        goto loop_590;
                    }
                    temp_r0_18 = gBingo.unk144 + 1;
                    gBingo.unk144 = temp_r0_18;
                    if (temp_r0_18 >= 0xC) {
                        gBingo.unk144 = 0;
                    }
                    gBingo.unk124 = -1;
                    break;
                case 1:                             /* switch 5 */
                    var_r6_6 = 0U;
                    gBingo.unk12A = gBingo.unk12F;
loop_633:
                    var_r4_7 = 0;
loop_634:
                    var_r8_7 = mPokemon__6cBingo;
                    var_r7_6 = 0;
                    temp_r3_7 = var_r4_7 + 1;
                    var_ctr_15 = 2;
loop_635:
                    if (temp_r3_7 == (u8) var_r8_7->unkC5) {

                    } else {
                        var_r7_6 += 1;
                        if (temp_r3_7 == (u8) var_r8_7[1].unkC5) {

                        } else {
                            temp_r8_11 = (BingoPokemon *)((u8 *)&var_r8_7[1] + 0xC8);
                            var_r7_6 += 1;
                            if (temp_r3_7 == (u8) temp_r8_11->unkC5) {

                            } else {
                                temp_r8_12 = (BingoPokemon *)((u8 *)temp_r8_11 + 0xC8);
                                var_r7_6 += 1;
                                if (temp_r3_7 == (u8) temp_r8_12->unkC5) {

                                } else {
                                    temp_r8_13 = (BingoPokemon *)((u8 *)temp_r8_12 + 0xC8);
                                    var_r7_6 += 1;
                                    if (temp_r3_7 == (u8) temp_r8_13->unkC5) {

                                    } else {
                                        temp_r8_14 = (BingoPokemon *)((u8 *)temp_r8_13 + 0xC8);
                                        var_r7_6 += 1;
                                        if (temp_r3_7 == (u8) temp_r8_14->unkC5) {

                                        } else {
                                            temp_r8_15 = (BingoPokemon *)((u8 *)temp_r8_14 + 0xC8);
                                            var_r7_6 += 1;
                                            if (temp_r3_7 == (u8) temp_r8_15->unkC5) {

                                            } else {
                                                var_r8_7 = (BingoPokemon *)((u8 *)temp_r8_15 + 0xC8);
                                                var_r7_6 += 1;
                                                var_ctr_15 -= 1;
                                                if (var_ctr_15 == 0) {
                                                    var_r7_6 = -1;
                                                } else {
                                                    goto loop_635;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (var_r7_6 != -1) {
                        var_r4_7 += 1;
                        if (var_r4_7 < 4) {
                            goto loop_634;
                        }
                    }
                    if (var_r6_6 < (u32) var_r4_7) {
                        var_r7_7 = mPokemon__6cBingo;
                        var_r4_8 = 0;
                        temp_r3_8 = var_r6_6 + 1;
                        var_ctr_16 = 2;
loop_616:
                        if (temp_r3_8 == (u8) var_r7_7->unkC5) {

                        } else {
                            var_r4_8 += 1;
                            if (temp_r3_8 == (u8) var_r7_7[1].unkC5) {

                            } else {
                                temp_r7_16 = (BingoPokemon *)((u8 *)&var_r7_7[1] + 0xC8);
                                var_r4_8 += 1;
                                if (temp_r3_8 == (u8) temp_r7_16->unkC5) {

                                } else {
                                    temp_r7_17 = (BingoPokemon *)((u8 *)temp_r7_16 + 0xC8);
                                    var_r4_8 += 1;
                                    if (temp_r3_8 == (u8) temp_r7_17->unkC5) {

                                    } else {
                                        temp_r7_18 = (BingoPokemon *)((u8 *)temp_r7_17 + 0xC8);
                                        var_r4_8 += 1;
                                        if (temp_r3_8 == (u8) temp_r7_18->unkC5) {

                                        } else {
                                            temp_r7_19 = (BingoPokemon *)((u8 *)temp_r7_18 + 0xC8);
                                            var_r4_8 += 1;
                                            if (temp_r3_8 == (u8) temp_r7_19->unkC5) {

                                            } else {
                                                temp_r7_20 = (BingoPokemon *)((u8 *)temp_r7_19 + 0xC8);
                                                var_r4_8 += 1;
                                                if (temp_r3_8 == (u8) temp_r7_20->unkC5) {

                                                } else {
                                                    var_r7_7 = (BingoPokemon *)((u8 *)temp_r7_20 + 0xC8);
                                                    var_r4_8 += 1;
                                                    var_ctr_16 -= 1;
                                                    if (var_ctr_16 == 0) {
                                                        var_r4_8 = -1;
                                                    } else {
                                                        goto loop_616;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        var_r6_6 += 1;
                        mPokemon__6cBingo[var_r4_8].unkC6 = 0;
                        goto loop_633;
                    }
                    gBingo.unk144 = 5;
                    gBingo.unk124 = -1;
                    break;
                }
            } else {
                temp_r0_19 = gBingo.unk144 + 1;
                gBingo.unk144 = temp_r0_19;
                if (temp_r0_19 >= 0xC) {
                    gBingo.unk144 = 0;
                }
                gBingo.unk124 = -1;
            }
            break;
        case 7:                                     /* switch 1 */
            var_r6_7 = 0;
            var_r7_8 = 0;
loop_678:
            if (var_r7_8 < 4) {
                var_r9_4 = mPokemon__6cBingo;
                var_r8_8 = 0;
                temp_r4_4 = var_r7_8 + 1;
                var_ctr_17 = 2;
loop_660:
                if (temp_r4_4 == (u8) var_r9_4->unkC5) {

                } else {
                    var_r8_8 += 1;
                    if (temp_r4_4 == (u8) var_r9_4[1].unkC5) {

                    } else {
                        temp_r9_16 = (BingoPokemon *)((u8 *)&var_r9_4[1] + 0xC8);
                        var_r8_8 += 1;
                        if (temp_r4_4 == (u8) temp_r9_16->unkC5) {

                        } else {
                            temp_r9_17 = (BingoPokemon *)((u8 *)temp_r9_16 + 0xC8);
                            var_r8_8 += 1;
                            if (temp_r4_4 == (u8) temp_r9_17->unkC5) {

                            } else {
                                temp_r9_18 = (BingoPokemon *)((u8 *)temp_r9_17 + 0xC8);
                                var_r8_8 += 1;
                                if (temp_r4_4 == (u8) temp_r9_18->unkC5) {

                                } else {
                                    temp_r9_19 = (BingoPokemon *)((u8 *)temp_r9_18 + 0xC8);
                                    var_r8_8 += 1;
                                    if (temp_r4_4 == (u8) temp_r9_19->unkC5) {

                                    } else {
                                        temp_r9_20 = (BingoPokemon *)((u8 *)temp_r9_19 + 0xC8);
                                        var_r8_8 += 1;
                                        if (temp_r4_4 == (u8) temp_r9_20->unkC5) {

                                        } else {
                                            var_r9_4 = (BingoPokemon *)((u8 *)temp_r9_20 + 0xC8);
                                            var_r8_8 += 1;
                                            var_ctr_17 -= 1;
                                            if (var_ctr_17 == 0) {
                                                var_r8_8 = -1;
                                            } else {
                                                goto loop_660;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                if (var_r8_8 != -1) {
                    var_r7_8 += 1;
                    var_r6_7 += mPokemon__6cBingo[var_r8_8].unkC4;
                    goto loop_678;
                }
            }
            if (var_r6_7 != 0) {
                if ((u8) gBingo.unk122 == 0) {
                    var_r0_5 = 1;
                } else {
                    var_r4_9 = 0;
                    var_r12 = 0;
                    temp_r7_21 = (u32) gBingo.unk134 >> 0x1FU;
                    temp_r0_20 = (gBingo.unk134 << 0x1E) - temp_r7_21;
                    temp_r6_20 = ((temp_r0_20 << 2) | (temp_r0_20 >> 0x1EU)) + temp_r7_21;
                    temp_r7_22 = (s32) gBingo.unk134 / 4;
loop_683:
                    if ((u8) gBingo.unk122 != 0) {
                        if (((u32) (gBingo.unk134 - 4) == var_r4_9) && ((s32) (temp_r7_22 - 1) >= 0)) {
                            var_r5_7 = *(u8 *)((u8 *)((u8 *)&gBingo + var_r12) + 0xA) == 0;
                        } else if (((u32) (gBingo.unk134 + 4) == var_r4_9) && ((s32) (temp_r7_22 + 1) <= 3)) {
                            var_r5_7 = *(u8 *)((u8 *)((u8 *)&gBingo + var_r12) + 0xA) == 0;
                        } else if (((u32) (gBingo.unk134 - 1) == var_r4_9) && ((s32) (temp_r6_20 - 1) >= 0)) {
                            var_r5_7 = *(u8 *)((u8 *)((u8 *)&gBingo + var_r12) + 0xA) == 0;
                        } else if (((u32) (gBingo.unk134 + 1) == var_r4_9) && ((s32) (temp_r6_20 + 1) <= 3)) {
                            var_r5_7 = *(u8 *)((u8 *)((u8 *)&gBingo + var_r12) + 0xA) == 0;
                        } else {
                            goto block_708;
                        }
                    } else {
                        temp_r27_2 = (s32) var_r4_9 / 4;
                        temp_r29_2 = var_r4_9 >> 0x1FU;
                        temp_r28 = (var_r4_9 << 0x1E) - temp_r29_2;
                        temp_r5_14 = ((temp_r28 << 2) | (temp_r28 >> 0x1EU)) + temp_r29_2;
                        if (((s32) (temp_r27_2 - 1) >= 0) && ((u8) gBingo.cells[var_r4_9 - 4].unk2 != 0)) {
                            var_r5_7 = 1;
                        } else if (((s32) (temp_r27_2 + 1) <= 3) && ((u8) gBingo.cells[var_r4_9 + 4].unk2 != 0)) {
                            var_r5_7 = 1;
                        } else if (((s32) (temp_r5_14 - 1) >= 0) && ((u8) gBingo.cells[var_r4_9 - 1].unk2 != 0)) {
                            var_r5_7 = 1;
                        } else if (((s32) (temp_r5_14 + 1) <= 3) && ((u8) gBingo.cells[var_r4_9 + 1].unk2 != 0)) {
                            var_r5_7 = 1;
                        } else {
block_708:
                            var_r27 = 0U;
                            var_r29 = &gBingo;
                            var_ctr_18 = 2;
                            do {
                                if ((u8) var_r29->cells[0].unk2 != 0) {
                                    var_r27 += 1;
                                }
                                if ((u8) var_r29->cells[1].unk2 != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_3 = (BingoCell *)((u8 *)var_r29->cells + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_3 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_4 = (BingoCell *)((u8 *)temp_r29_3 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_4 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_5 = (BingoCell *)((u8 *)temp_r29_4 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_5 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_6 = (BingoCell *)((u8 *)temp_r29_5 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_6 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_7 = (BingoCell *)((u8 *)temp_r29_6 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_7 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                temp_r29_8 = (BingoCell *)((u8 *)temp_r29_7 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r29_8 + 0xA)) != 0) {
                                    var_r27 += 1;
                                }
                                var_r29 = (BingoState *) ((BingoCell *)((u8 *)temp_r29_8 + 8));
                                var_ctr_18 -= 1;
                            } while (var_ctr_18 != 0);
                            if (var_r27 != 0U) {
                                var_r5_7 = 0;
                            } else {
                                var_r5_7 = 1;
                            }
                        }
                    }
                    if (var_r5_7 != 0) {
                        var_r0_5 = 1;
                    } else {
                        var_r4_9 += 1;
                        var_r12 += 8;
                        if ((s32) var_r4_9 >= 0x10) {
                            var_r0_5 = 0;
                        } else {
                            goto loop_683;
                        }
                    }
                }
                if (var_r0_5 == 0) {
                    goto block_734;
                }
                if ((s32) (temp_r3 & 0x10) != 0) {
                    temp_r3_9 = arg0->unk9E;
                    if ((u8) gBingo.unk122 != 0) {
                        temp_r6_21 = (u32) gBingo.unk134 >> 0x1FU;
                        temp_r5_15 = (gBingo.unk134 << 0x1E) - temp_r6_21;
                        temp_r4_5 = (s32) gBingo.unk134 / 4;
                        temp_r5_16 = ((temp_r5_15 << 2) | (temp_r5_15 >> 0x1EU)) + temp_r6_21;
                        if (((u32) (gBingo.unk134 - 4) == (u32) temp_r3_9) && ((s32) (temp_r4_5 - 1) >= 0)) {
                            var_r0_6 = gBingo.cells[temp_r3_9].unk2 == 0;
                        } else if (((u32) (gBingo.unk134 + 4) == (u32) temp_r3_9) && ((s32) (temp_r4_5 + 1) <= 3)) {
                            var_r0_6 = gBingo.cells[temp_r3_9].unk2 == 0;
                        } else if (((u32) (gBingo.unk134 - 1) == (u32) temp_r3_9) && ((s32) (temp_r5_16 - 1) >= 0)) {
                            var_r0_6 = gBingo.cells[temp_r3_9].unk2 == 0;
                        } else if (((u32) (gBingo.unk134 + 1) == (u32) temp_r3_9) && ((s32) (temp_r5_16 + 1) <= 3)) {
                            var_r0_6 = gBingo.cells[temp_r3_9].unk2 == 0;
                        } else {
                            goto block_761;
                        }
                    } else {
                        temp_r6_22 = temp_r3_9 / 4;
                        temp_r5_17 = (u32) temp_r3_9 >> 0x1FU;
                        temp_r4_6 = (temp_r3_9 << 0x1E) - temp_r5_17;
                        temp_r5_18 = ((temp_r4_6 << 2) | (temp_r4_6 >> 0x1EU)) + temp_r5_17;
                        if (((s32) (temp_r6_22 - 1) >= 0) && ((u8) gBingo.cells[temp_r3_9 - 4].unk2 != 0)) {
                            var_r0_6 = 1;
                        } else if (((s32) (temp_r6_22 + 1) <= 3) && ((u8) gBingo.cells[temp_r3_9 + 4].unk2 != 0)) {
                            var_r0_6 = 1;
                        } else if (((s32) (temp_r5_18 - 1) >= 0) && ((u8) gBingo.cells[temp_r3_9 - 1].unk2 != 0)) {
                            var_r0_6 = 1;
                        } else if (((s32) (temp_r5_18 + 1) <= 3) && ((u8) gBingo.cells[temp_r3_9 + 1].unk2 != 0)) {
                            var_r0_6 = 1;
                        } else {
block_761:
                            var_r5_8 = 0U;
                            var_r6_8 = &gBingo;
                            var_ctr_19 = 2;
                            do {
                                if ((u8) var_r6_8->cells[0].unk2 != 0) {
                                    var_r5_8 += 1;
                                }
                                if ((u8) var_r6_8->cells[1].unk2 != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_23 = (BingoCell *)((u8 *)var_r6_8->cells + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_23 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_24 = (BingoCell *)((u8 *)temp_r6_23 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_24 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_25 = (BingoCell *)((u8 *)temp_r6_24 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_25 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_26 = (BingoCell *)((u8 *)temp_r6_25 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_26 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_27 = (BingoCell *)((u8 *)temp_r6_26 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_27 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                temp_r6_28 = (BingoCell *)((u8 *)temp_r6_27 + 8);
                                if ((u8) *(u8 *)((u8 *)(BingoCell *)((u8 *)temp_r6_28 + 0xA)) != 0) {
                                    var_r5_8 += 1;
                                }
                                var_r6_8 = (BingoState *) ((BingoCell *)((u8 *)temp_r6_28 + 8));
                                var_ctr_19 -= 1;
                            } while (var_ctr_19 != 0);
                            if (var_r5_8 != 0U) {
                                var_r0_6 = 0;
                            } else {
                                var_r0_6 = 1;
                            }
                        }
                    }
                    if ((var_r0_6 != 0) && ((u8) gBingo.cells[temp_r3_9].unk2 == 0)) {
                        temp_r0_21 = gBingo.unk144 + 1;
                        gBingo.unk144 = temp_r0_21;
                        if (temp_r0_21 >= 0xC) {
                            gBingo.unk144 = 0;
                        }
                        gBingo.unk124 = -1;
                        if (arg0 != 0) {
                            menuPlaySe(arg0->unk4);
                        }
                    }
                } else if ((s32) (temp_r3 & 0x20) != 0) {
                    menuPlaySe(arg0->unk4);
                    gBingo.unk12E = 1;
                }
            } else {
block_734:
                gBingo.unk13C = 0;
                gBingo.unk108 = 1;
            }
            break;
        case 8:                                     /* switch 1 */
            var_r6_9 = 0;
loop_791:
            var_r8_9 = mPokemon__6cBingo;
            var_r7_9 = 0;
            temp_r4_7 = var_r6_9 + 1;
            var_ctr_20 = 2;
loop_792:
            if (temp_r4_7 == (u8) var_r8_9->unkC5) {

            } else {
                var_r7_9 += 1;
                if (temp_r4_7 == (u8) var_r8_9[1].unkC5) {

                } else {
                    temp_r8_16 = (BingoPokemon *)((u8 *)&var_r8_9[1] + 0xC8);
                    var_r7_9 += 1;
                    if (temp_r4_7 == (u8) temp_r8_16->unkC5) {

                    } else {
                        temp_r8_17 = (BingoPokemon *)((u8 *)temp_r8_16 + 0xC8);
                        var_r7_9 += 1;
                        if (temp_r4_7 == (u8) temp_r8_17->unkC5) {

                        } else {
                            temp_r8_18 = (BingoPokemon *)((u8 *)temp_r8_17 + 0xC8);
                            var_r7_9 += 1;
                            if (temp_r4_7 == (u8) temp_r8_18->unkC5) {

                            } else {
                                temp_r8_19 = (BingoPokemon *)((u8 *)temp_r8_18 + 0xC8);
                                var_r7_9 += 1;
                                if (temp_r4_7 == (u8) temp_r8_19->unkC5) {

                                } else {
                                    temp_r8_20 = (BingoPokemon *)((u8 *)temp_r8_19 + 0xC8);
                                    var_r7_9 += 1;
                                    if (temp_r4_7 == (u8) temp_r8_20->unkC5) {

                                    } else {
                                        var_r8_9 = (BingoPokemon *)((u8 *)temp_r8_20 + 0xC8);
                                        var_r7_9 += 1;
                                        var_ctr_20 -= 1;
                                        if (var_ctr_20 == 0) {
                                            var_r7_9 = -1;
                                        } else {
                                            goto loop_792;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (var_r7_9 != -1) {
                var_r6_9 += 1;
                if (var_r6_9 < 4) {
                    goto loop_791;
                }
            }
            if ((var_r6_9 < 2) || ((s32) (temp_r3 & 0x10) != 0)) {
                temp_r0_22 = gBingo.unk144 + 1;
                gBingo.unk144 = temp_r0_22;
                if (temp_r0_22 >= 0xC) {
                    gBingo.unk144 = 0;
                }
                gBingo.unk124 = -1;
                if (var_r6_9 >= 2) {
                    menuPlaySe(arg0->unk4);
                }
            } else if ((s32) (temp_r3 & 0x20) != 0) {
                gBingo.unk144 = 7;
                gBingo.unk124 = -1;
            } else if ((s32) (temp_r29 & 1) != 0) {
                if ((u8) gBingo.unk12C != 0) {
                    menuPlaySe(arg0->unk4);
                    gBingo.unk12C -= 1;
                }
            } else if (((s32) (temp_r29 & 2) != 0) && ((s32) gBingo.unk12C < (s32) (var_r6_9 - 1))) {
                menuPlaySe(arg0->unk4);
                gBingo.unk12C += 1;
            }
            break;
        case 9:                                     /* switch 1 */
            temp_r0_23 = gBingo.unk124 - 1;
            switch (temp_r0_23) {                   /* switch 6; irregular */
            case 0:                                 /* switch 6 */
                temp_r0_24 = gBingo.unk144 + 1;
                gBingo.unk144 = temp_r0_24;
                if (temp_r0_24 >= 0xC) {
                    gBingo.unk144 = 0;
                }
                gBingo.unk124 = -1;
                break;
            case 1:                                 /* switch 6 */
                gBingo.unk144 = 0xB;
                gBingo.unk124 = -1;
                break;
            case 2:                                 /* switch 6 */
            case -1:                                /* switch 6 */
                gBingo.unk144 = 7;
                gBingo.unk124 = -1;
                break;
            }
            break;
        case 10:                                    /* switch 1 */
            var_r8_10 = mPokemon__6cBingo;
            var_r5_9 = 0;
            var_r6_10 = mPokemon__6cBingo;
            temp_r4_8 = gBingo.unk12C + 1;
            var_ctr_21 = 2;
loop_837:
            if (temp_r4_8 == (u8) var_r6_10->unkC5) {

            } else {
                var_r5_9 += 1;
                if (temp_r4_8 == (u8) var_r6_10[1].unkC5) {

                } else {
                    temp_r6_29 = (BingoPokemon *)((u8 *)&var_r6_10[1] + 0xC8);
                    var_r5_9 += 1;
                    if (temp_r4_8 == (u8) temp_r6_29->unkC5) {

                    } else {
                        temp_r6_30 = (BingoPokemon *)((u8 *)temp_r6_29 + 0xC8);
                        var_r5_9 += 1;
                        if (temp_r4_8 == (u8) temp_r6_30->unkC5) {

                        } else {
                            temp_r6_31 = (BingoPokemon *)((u8 *)temp_r6_30 + 0xC8);
                            var_r5_9 += 1;
                            if (temp_r4_8 == (u8) temp_r6_31->unkC5) {

                            } else {
                                temp_r6_32 = (BingoPokemon *)((u8 *)temp_r6_31 + 0xC8);
                                var_r5_9 += 1;
                                if (temp_r4_8 == (u8) temp_r6_32->unkC5) {

                                } else {
                                    temp_r6_33 = (BingoPokemon *)((u8 *)temp_r6_32 + 0xC8);
                                    var_r5_9 += 1;
                                    if (temp_r4_8 == (u8) temp_r6_33->unkC5) {

                                    } else {
                                        var_r6_10 = (BingoPokemon *)((u8 *)temp_r6_33 + 0xC8);
                                        var_r5_9 += 1;
                                        var_ctr_21 -= 1;
                                        if (var_ctr_21 == 0) {
                                            var_r5_9 = -1;
                                        } else {
                                            goto loop_837;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if ((u8) mPokemon__6cBingo[var_r5_9].unkC4 != 0) {
                temp_r0_25 = gBingo.unk124 - 1;
                switch (temp_r0_25) {               /* switch 7; irregular */
                case 0:                             /* switch 7 */
                    var_r5_10 = 0;
                    temp_r4_9 = gBingo.unk12C + 1;
                    var_ctr_22 = 2;
loop_861:
                    if (temp_r4_9 == (u8) var_r8_10->unkC5) {

                    } else {
                        var_r5_10 += 1;
                        if (temp_r4_9 == (u8) var_r8_10[1].unkC5) {

                        } else {
                            temp_r8_21 = (BingoPokemon *)((u8 *)&var_r8_10[1] + 0xC8);
                            var_r5_10 += 1;
                            if (temp_r4_9 == (u8) temp_r8_21->unkC5) {

                            } else {
                                temp_r8_22 = (BingoPokemon *)((u8 *)temp_r8_21 + 0xC8);
                                var_r5_10 += 1;
                                if (temp_r4_9 == (u8) temp_r8_22->unkC5) {

                                } else {
                                    temp_r8_23 = (BingoPokemon *)((u8 *)temp_r8_22 + 0xC8);
                                    var_r5_10 += 1;
                                    if (temp_r4_9 == (u8) temp_r8_23->unkC5) {

                                    } else {
                                        temp_r8_24 = (BingoPokemon *)((u8 *)temp_r8_23 + 0xC8);
                                        var_r5_10 += 1;
                                        if (temp_r4_9 == (u8) temp_r8_24->unkC5) {

                                        } else {
                                            temp_r8_25 = (BingoPokemon *)((u8 *)temp_r8_24 + 0xC8);
                                            var_r5_10 += 1;
                                            if (temp_r4_9 == (u8) temp_r8_25->unkC5) {

                                            } else {
                                                var_r8_10 = (BingoPokemon *)((u8 *)temp_r8_25 + 0xC8);
                                                var_r5_10 += 1;
                                                var_ctr_22 -= 1;
                                                if (var_ctr_22 == 0) {
                                                    var_r5_10 = -1;
                                                } else {
                                                    goto loop_861;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (var_r5_10 >= 0) {
                        temp_r5_19 = &mPokemon__6cBingo[var_r5_10];
                        temp_r4_10 = temp_r5_19->unkC4;
                        if (temp_r4_10 != 0) {
                            temp_r5_19->unkC4 = temp_r4_10 - 1;
                        }
                    }
                    var_r6_11 = &gBingo;
                    var_r5_11 = 0;
                    var_r4_10 = 0;
                    gBingo.unk138 = gBingo.unk134;
                    gBingo.unk134 = (s32) (u8) arg0->unk9E;
                    var_ctr_23 = 0xA - 0;
                    if (0 < 0xA) {
                        do {
                            if (var_r5_11 != 8) {
                                if (var_r5_11 < 8) {
                                    if (var_r5_11 < 4) {
                                        if (var_r5_11 < 0) {
                                            goto block_939;
                                        }
                                        if ((u8) gBingo.cells[var_r5_11].unk2 != 0) {
                                            if (0U == 3U) {
                                                var_r0_7 = 1;
                                            } else {
                                                temp_r7_23 = (var_r5_11 * 8) + 0x20;
                                                var_r0_7 = 1;
                                                if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_23) + 0xA) != 0) {
                                                    if (1U == 3U) {

                                                    } else {
                                                        temp_r7_24 = temp_r7_23 + 0x20;
                                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_24) + 0xA) != 0) {
                                                            if (2U == 3U) {
                                                                var_r0_7 = 1;
                                                            } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r7_24 + 0x20)) + 0xA) != 0) && (3U == 3U)) {
                                                                var_r0_7 = 1;
                                                            } else {
                                                                goto block_939;
                                                            }
                                                        } else {
                                                            goto block_939;
                                                        }
                                                    }
                                                } else {
                                                    goto block_939;
                                                }
                                            }
                                        } else {
                                            goto block_939;
                                        }
                                    } else {
                                        temp_r7_25 = (7 - var_r5_11) * 4;
                                        if ((u8) gBingo.cells[temp_r7_25].unk2 != 0) {
                                            if (0U == 3U) {
                                                var_r0_7 = 1;
                                            } else {
                                                var_r0_7 = 1;
                                                if ((u8) *(u8 *)((u8 *)&gBingo.cells[temp_r7_25] + 0xA) != 0) {
                                                    if (1U == 3U) {

                                                    } else {
                                                        temp_r7_26 = (temp_r7_25 * 8) + 8 + 8;
                                                        if ((u8) *(u8 *)((u8 *)((u8 *)&gBingo + temp_r7_26) + 0xA) != 0) {
                                                            if (2U == 3U) {
                                                                var_r0_7 = 1;
                                                            } else if (((u8) *(u8 *)((u8 *)((u8 *)&gBingo + (temp_r7_26 + 8)) + 0xA) != 0) && (3U == 3U)) {
                                                                var_r0_7 = 1;
                                                            } else {
                                                                goto block_939;
                                                            }
                                                        } else {
                                                            goto block_939;
                                                        }
                                                    }
                                                } else {
                                                    goto block_939;
                                                }
                                            }
                                        } else {
                                            goto block_939;
                                        }
                                    }
                                } else if (var_r5_11 < 0xA) {
                                    if ((u8) gBingo.cells[0].unk2 != 0) {
                                        if (0U == 3U) {
                                            var_r0_7 = 1;
                                        } else {
                                            var_r0_7 = 1;
                                            if ((u8) gBingo.cells[5].unk2 != 0) {
                                                if (1U == 3U) {

                                                } else if ((u8) gBingo.cells[0xA].unk2 != 0) {
                                                    if (2U == 3U) {
                                                        var_r0_7 = 1;
                                                    } else if (((u8) gBingo.cells[0xF].unk2 != 0) && (3U == 3U)) {
                                                        var_r0_7 = 1;
                                                    } else {
                                                        goto block_939;
                                                    }
                                                } else {
                                                    goto block_939;
                                                }
                                            } else {
                                                goto block_939;
                                            }
                                        }
                                    } else {
                                        goto block_939;
                                    }
                                } else {
                                    goto block_939;
                                }
                            } else if ((u8) gBingo.cells[3 - 0].unk2 != 0) {
                                if (0U == 3U) {
                                    var_r0_7 = 1;
                                } else {
                                    var_r0_7 = 1;
                                    if ((u8) gBingo.cells[(3 - 1) + 4].unk2 != 0) {
                                        if (1U == 3U) {

                                        } else if ((u8) gBingo.cells[(3 - 2) + 8].unk2 != 0) {
                                            if (2U == 3U) {
                                                var_r0_7 = 1;
                                            } else if (((u8) gBingo.cells[(3 - 3) + 0xC].unk2 != 0) && (3U == 3U)) {
                                                var_r0_7 = 1;
                                            } else {
                                                goto block_939;
                                            }
                                        } else {
                                            goto block_939;
                                        }
                                    } else {
                                        goto block_939;
                                    }
                                }
                            } else {
block_939:
                                var_r0_7 = 0;
                            }
                            if (var_r0_7 != 0) {
                                var_r4_10 += 1;
                            }
                            var_r6_11->lineState[0] = var_r0_7;
                            var_r5_11 += 1;
                            var_r6_11->lineEffects[0] = 0;
                            var_r6_11 = (BingoState *)((u8 *)var_r6_11 + 1);
                            var_ctr_23 -= 1;
                        } while (var_ctr_23 != 0);
                    }
                    gBingo.unk144 = 0;
                    gBingo.unk12D = var_r4_10;
                    gBingo.unk124 = -1;
                    break;
                case 1:                             /* switch 7 */
                    gBingo.unk144 = 7;
                    gBingo.unk124 = -1;
                    break;
                }
            } else if ((s32) (temp_r3 & 0x30) != 0) {
                gBingo.unk144 = 7;
                gBingo.unk124 = -1;
            }
            break;
        }
    }
    return 0;
}

static inline u8 bingoNoClearedPanel(BingoState *state) {
    u32 count = 0;
    u32 i = count;
    for (; i < 16; i++) {
        if (state->cells[i].unk2 != 0) count++;
    }
    if (count != 0) {
        return 0;
    }
    return 1;
}

s32 menuBingoSheetCur(BingoWindow *arg0) {
    BingoCell *temp_r5_10;
    BingoCell *temp_r5_11;
    BingoCell *temp_r5_12;
    BingoCell *temp_r5_13;
    BingoCell *temp_r5_14;
    BingoCell *temp_r5_3;
    BingoCell *temp_r5_4;
    BingoCell *temp_r5_5;
    BingoCell *temp_r5_6;
    BingoCell *temp_r5_7;
    BingoCell *temp_r5_8;
    BingoCell *temp_r5_9;
    BingoState *var_r5;
    BingoState *var_r5_2;
    s32 var_r31;
    s32 temp_r3_2;
    s32 temp_r4_2;
    s32 temp_r4_4;
    s32 temp_r5_2;
    s32 var_ctr;
    s32 var_ctr_2;
    u16 temp_r3;
    u32 temp_r3_3;
    u32 temp_r4;
    u32 temp_r4_3;
    u32 temp_r5;
    u32 var_r3;
    u32 var_r4;
    u32 var_r0;
    u8 var_r0_2;

    menuSpriteBiosGetPtr(0x27FU);
    if (((s32) gBingo.unk144 != 7) || ((s32) gBingo.unk12E != 0)) {
        return 0;
    }
    if ((s32) gBingo.unk108 != 0) {
        return 0;
    }
    var_r31 = arg0->unk9E;
    temp_r3 = windowGetKeyRepeat();
    if ((s32) (temp_r3 & 1) != 0) {
        var_r31 -= 4;
    } else if ((s32) (temp_r3 & 2) != 0) {
        var_r31 += 4;
    } else if ((s32) (temp_r3 & 4) != 0) {
        var_r31 -= 1;
    } else if ((s32) (temp_r3 & 8) != 0) {
        var_r31 += 1;
    }
    if ((u8) gBingo.unk122 != 0) {
        temp_r3_2 = gBingo.unk134 / 4;
        temp_r4_2 = gBingo.unk134 % 4;
        if (((u32) (gBingo.unk134 - 4) == (u32) var_r31) && ((s32) (temp_r3_2 - 1) >= 0)) {
            var_r0 = gBingo.cells[var_r31].unk2 == 0;
        } else if (((u32) (gBingo.unk134 + 4) == (u32) var_r31) && ((s32) (temp_r3_2 + 1) <= 3)) {
            var_r0 = gBingo.cells[var_r31].unk2 == 0;
        } else if (((u32) (gBingo.unk134 - 1) == (u32) var_r31) && ((s32) (temp_r4_2 - 1) >= 0)) {
            var_r0 = gBingo.cells[var_r31].unk2 == 0;
        } else if (((u32) (gBingo.unk134 + 1) == (u32) var_r31) && ((s32) (temp_r4_2 + 1) <= 3)) {
            var_r0 = gBingo.cells[var_r31].unk2 == 0;
        } else {
            goto block_38;
        }
    } else {
        temp_r4_4 = var_r31 % 4;
        temp_r5_2 = var_r31 / 4;
        if (((s32) (temp_r5_2 - 1) >= 0) && ((u8) gBingo.cells[(u32)(var_r31 - 4)].unk2 != 0)) {
            var_r0 = 1;
        } else if (((s32) (temp_r5_2 + 1) <= 3) && ((u8) gBingo.cells[(u32)(var_r31 + 4)].unk2 != 0)) {
            var_r0 = 1;
        } else if (((s32) (temp_r4_4 - 1) >= 0) && ((u8) gBingo.cells[(u32)(var_r31 - 1)].unk2 != 0)) {
            var_r0 = 1;
        } else if (((s32) (temp_r4_4 + 1) <= 3) && ((u8) gBingo.cells[(u32)(var_r31 + 1)].unk2 != 0)) {
            var_r0 = 1;
        } else {
block_38:
            var_r0 = bingoNoClearedPanel(&gBingo);
        }
    }
    if ((var_r0 == 0) && (var_r5_2 = &gBingo, (((u8) gBingo.cells[var_r31].unk2 == 0) != 0))) {
        var_r0_2 = bingoNoClearedPanel(&gBingo);
        if (var_r0_2 != 0) {
            goto block_83;
        }
    } else {
block_83:
        menuCursorNormal(arg0, 1);
    }
    return 0;
}

s32 menuBingoSheetCtrl(BingoWindow *arg0) {
    s32 sp8;
    BingoWindow *temp_r3;
    s8 temp_r6;
    s8 var_r8;
    u32 *temp_r30;
    u32 *var_r4;
    u32 *var_r5;
    u32 temp_r31;
    u8 temp_r0;
    u8 var_r7;

    temp_r31 = floorGetCurrentGroupID();
    if (temp_r31 == fn_80091B98()) {
        if ((s8) arg0->unk1 != 2) {

        } else if (fadeCheck(0) != 0) {
            if ((fadeGetType() != 3) && ((u8) gBingo.unk10C != 0) && (menuIsCheck(0xC8) != 0)) {
                menuClose(0xC8);
            }
        } else {
            temp_r3 = windowSearchID(0xAE);
            if (temp_r3 != 0) {
                temp_r30 = (u32 *)windowGetAllocPtr(temp_r3);
                var_r5 = temp_r30;
                temp_r6 = windowGetParam(temp_r3, 2);
                var_r7 = 1;
                var_r8 = 0;
                var_r4 = MenuBingoMsgIdx__6cBingo;
loop_13:
                if (var_r8 < temp_r6) {
                    if ((u32) *var_r5 != (u32) *var_r4) {
                        var_r7 = 0;
                    } else {
                        var_r4 = (u32 *)((u8 *)var_r4 + 4);
                        var_r5 = (u32 *)((u8 *)var_r5 + 4);
                        var_r8 += 1;
                        goto loop_13;
                    }
                }
                if (var_r7 == 1) {
                    sp8 = *(u32 *)((u8 *)temp_r3 + 0x9C);
                    if ((s16)sp8 == 0) {
                        gBingo.unk122 = 0;
                    } else {
                        gBingo.unk122 = 1;
                    }
                }
            }
        }
    } else {
        temp_r0 = arg0->unk1;
        switch ((s8) temp_r0) {                     /* irregular */
        case 0:
            if ((s8) arg0->unk2 == 0) {
                winSeqSetMenu(arg0->unk4, 0x1B1);
                arg0->unk2 = 1;
            }
            break;
        case 3:
            if ((s8) arg0->unk2 == 0) {
                winSeqSetMenu(arg0->unk4, 0x1B7);
                arg0->unk2 = 1;
            }
            break;
        }
    }
    return 0;
}

s32 fn_80091B98(void) {
    s32 temp_r3;

    temp_r3 = pokecoloGetLanguage();
    switch (temp_r3) {                              /* irregular */
    case 2:
        return 0x8CF;
    case 3:
        return 0xA9E;
    case 4:
        return 0xA9F;
    case 5:
        return 0xAA0;
    case 6:
        return 0xAA1;
    default:
        return 0x8CF;
    }
}

s32 fn_80091C10(BingoWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk1;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x132);
            arg0->unk2 = 1;
        }
        break;
    case 3:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x136);
            arg0->unk2 = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091CA8(BingoWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk1;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x132);
            arg0->unk2 = 1;
        }
        break;
    case 3:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x136);
            arg0->unk2 = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091D40(BingoWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk1;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x132);
            arg0->unk2 = 1;
        }
        break;
    case 3:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x136);
            arg0->unk2 = 1;
        }
        break;
    }
    return 0;
}

s32 fn_80091DD8(BingoWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->unk1;
    switch ((s8) temp_r0) {                         /* irregular */
    case 0:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x132);
            arg0->unk2 = 1;
        }
        break;
    case 3:
        if ((s8) arg0->unk2 == 0) {
            winSeqSetMenu(arg0->unk4, 0x136);
            arg0->unk2 = 1;
        }
        break;
    }
    return 0;
}

static inline u8 bingoCanOpenPanel(BingoState *state) {
    u32 panel;
    for (panel = 0; panel < 16; ++panel) {
        s32 row, column;
        u8 available;
        if (state->unk122) {
            row = state->unk134 / 4;
            column = state->unk134 % 4;
            if ((state->unk134 - 4 == panel && row - 1 >= 0) ||
                (state->unk134 + 4 == panel && row + 1 <= 3) ||
                (state->unk134 - 1 == panel && column - 1 >= 0) ||
                (state->unk134 + 1 == panel && column + 1 <= 3)) {
                available = state->cells[panel].unk2 == 0;
            } else {
                available = bingoNoClearedPanel(state);
            }
        } else {
            row = (s32)panel / 4;
            column = (s32)panel % 4;
            if ((row - 1 >= 0 && state->cells[panel - 4].unk2) ||
                (row + 1 <= 3 && state->cells[panel + 4].unk2) ||
                (column - 1 >= 0 && state->cells[panel - 1].unk2) ||
                (column + 1 <= 3 && state->cells[panel + 1].unk2)) available = 1;
            else available = bingoNoClearedPanel(state);
        }
        if (available) return 1;
    }
    return 0;
}

void menuBingoMain(void) {
    s32 selected;
    u8 choosing = 1;
    s32 start = 0;
    s32 result;
    if (GSfloorGetCurrent() != 0x388) {
        selected = gBingo.unk134;
        menuOpenCustom(0xC8, 0, &selected, 2, 0, 0);
        while (windowGetKeyInfo()->unk4 != 0x20) GSthreadSwitch();
        menuClose(0xC8);
        menuCloseSync(0xC8, 1);
        menuOffScreenSetPriority(1);
        GSfloorPop();
        floorSetFadeScript(0, 0);
        return;
    }
    selected = 0;
    while (choosing) {
        u32 sheet;
        gBingo.unk138 = 0;
        gBingo.unk134 = 0;
        gBingo.unk12C = 0;
        gBingo.unk12B = 0;
        gBingo.unk129 = 0;
        gBingo.unk12F = 0;
        gBingo.unk12A = 0;
        gBingo.unk12E = 0;
        gBingo.unk124 = -1;
        gBingo.unk10C = 0;
        gBingo.unk108 = 0;
        gBingo.unk144 = 13;
        gBingo.unk140 = 0.0f;
        gBingo.unk128 = getClearLv__10bingo_biosFv(&gBingo);
        if (GSflagGet(0x4F2) >= 6) setSelect__10bingo_biosFUl(10);
        for (sheet = 0; sheet < *bingo_data_number; ++sheet) {
            u32 id = TopCurIdx__6cBingo[sheet];
            if (isSelect__10bingo_biosFUl(&gBingo, sheet)) menuItemBiosSetSelectFlag(0xC3, id, 1);
            else menuItemBiosSetSelectFlag(0xC3, id, 0);
            if (id == 0x693 && isSelect__10bingo_biosFUl(&gBingo, 10)) {
                u8 level;
                void *item = menuItemBiosGetPtr(0xC3, id);
                if (isSelect__10bingo_biosFUl(&gBingo, 8)) level = 2;
                else if (isSelect__10bingo_biosFUl(&gBingo, 5)) level = 1;
                else level = 0;
                *(s16 *)((u8 *)item + 8) = level * 101 + 156;
            }
        }
        fadeSet(2, 0.25f);
        FlashSystemSetNowFrameLabel(0x1EC93000, "start");
        FlashSystemSetPlayFrameLabel(0x1EC93000, "start", "select");
        menuOpen(0xDC, 0);
        selected = menuOpenCustom(0xC3, 0, &selected, 0, 1, 0);
        FlashSystemSetPlayFrameLabel(0x1EC93000, "select", "panel");
        if (selected < 0) {
            gBingo.unk129 = 0;
            gBingo.unk12A = 0;
            setStaticNo__10bingo_biosFUc(255);
            setStaticBall__10bingo_biosFUc(0);
            setStaticResult__10bingo_biosFUc(0);
            setStaticIdx__10bingo_biosFUcUc(0, 0);
            GSfloorPop();
            return;
        }
        SetupSheet__6cBingoFUl(&gBingo, selected);
        fadeCheck(1);
        for (;;) {
            u32 frame = FlashSystemGetFrameFromLabel(0x1EC93000, "panel");
            if (FlashSystemGetNowFrame(0x1EC93000) == frame) break;
            GSthreadSwitch();
        }
        menuClose(0xC3);
        menuCloseSync(0xC3, 1);
        while (menuFaceCheckLoading()) GSthreadSwitch();
        menuOpen(0xDC, 0);
        menuOpen(0xC7, 0);
        menuOpen(0xC9, 0);
        menuOpen(0xCA, 0);
        menuOpenCustom(0xC8, 0, &gBingo.unk134, 0, 0, 0);
        winSeqSetMenu(0xC7, 0x1A5);
        winSeqSetMenu(0xC9, 0x1A9);
        winSeqSetMenu(0xC8, 0x1AD);
        FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
        GSthreadSwitch();
        while (winSeqCheckMove(0xC8)) GSthreadSwitch();
        for (;;) {
            s32 direction = 0;
            gBingo.unk13C = 0xDB0A;
            GSthreadSwitch();
            if (windowGetKeyInfo()->unk4 & 0x10) { start = 1; break; }
            if (windowGetKeyInfo()->unk4 & 0x20) { start = 0; break; }
            if (windowGetKeyInfo()->unk4 & 0x200) direction = -1;
            else if (windowGetKeyInfo()->unk4 & 0x400) direction = 1;
            if (direction) {
                u8 index;
                fadeSet(3, 0.125f); fadeCheck(1);
                menuClose(0xDC); menuClose(0xC7); menuClose(0xC9); menuClose(0xCA); menuCloseCustom(0xC8, 0, 0);
                if (direction < 0) {
                    index = getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1;
                    do { if (index) --index; else index = 10; } while (!isSelect__10bingo_biosFUl(&gBingo, index));
                    SetupSheet__6cBingoFUl(&gBingo, index);
                } else {
                    index = getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1;
                    do { if (index < 10) ++index; else index = 0; } while (!isSelect__10bingo_biosFUl(&gBingo, index));
                    SetupSheet__6cBingoFUl(&gBingo, index);
                }
                menuOpen(0xDC, 0);
                menuOpen(0xC7, 0);
                menuOpen(0xC9, 0);
                menuOpen(0xCA, 0);
                menuOpenCustom(0xC8, 0, &gBingo.unk134, 0, 0, 0);
                winSeqSetMenu(0xC7, 0x1A5);
                winSeqSetMenu(0xC9, 0x1A9);
                winSeqSetMenu(0xC8, 0x1AD);
                FlashSystemSetNowFrameLabel(0x1EC93000, "panel");
                GSthreadSwitch();
                while (winSeqCheckMove(0xC8)) GSthreadSwitch();
                fadeSet(2, 0.125f); fadeCheck(1);
            }
        }
        if (start) {
            gBingo.unk144 = 14;
            gBingo.unk124 = -1;
            gBingo.unk13C = 0xDADE;
            if (menuSubOpenYesNo(0, 0x1BD, 0x104, 0) == 0) {
                u32 count = 0;
                if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1)) {
                    while (windowGetKeyInfo()->unk4 != 0x10) { gBingo.unk13C = 0xDADF; GSthreadSwitch(); }
                    makeRandomSheet__6cBingoFv(&gBingo);
                }
                gBingo.unk122 = 0;
                for (sheet = 0; sheet < 10; ++sheet) if (isClear__10bingo_biosFUl(&gBingo, sheet)) ++count;
                if (count == 10) {
                    gBingo.unk13C = 0xDB33;
                    if (menuSubOpenSelect3(0, MenuBingoMsgIdx__6cBingo, 2, 0x28, 0x12C, 0, 2, 0, 0) == 1) gBingo.unk122 = 1;
                }
                choosing = 0;
            } else start = 0;
        }
        if (!start) { menuClose(0xDC); menuClose(0xC7); menuClose(0xC9); menuClose(0xCA); menuCloseCustom(0xC8, 0, 0); }
    }
    if (start) {
        u8 retry = 1;
        while (retry) {
            gBingo.unk144 = 7;
            gBingo.unk124 = -1;
            do {
                GSthreadSwitch();
                setStepMessage__6cBingoFv(&gBingo);
                if (windowGetKeyInfo()->unk4 & 0x40) {
                    GSthreadSwitch(); menuOpen(0xF6, 0);
                    while (!(windowGetKeyInfo()->unk4 & 0xF0)) GSthreadSwitch();
                    menuClose(0xF6); menuCloseSync(0xF6, 1);
                } else if (windowGetKeyInfo()->unk4 & 0x80) {
                    GSthreadSwitch(); menuOpen(0x100, 0);
                    while (!(windowGetKeyInfo()->unk4 & 0xF0)) GSthreadSwitch();
                    menuClose(0x100); menuCloseSync(0x100, 1);
                }
                result = gBingo.unk108;
            } while (!result);
            gBingo.unk13C = 0;
            gBingo.unk144 = 14;
            gBingo.unk124 = -1;
            switch (result) {
            case 3:
                if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1)) {
                    gBingo.unk13C = bingoCompletedLines(&gBingo) < 2 ? 0xDAFA : 0xDB3B;
                    GSthreadSwitch();
                    if (menuSubOpenYesNo(0, 0x1BD, 0x104, 0)) retry = 0;
                    else { retry = 1; ResetSheet__6cBingoFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4)); }
                } else retry = 0;
                break;
            case 2: {
                u32 frame, end;
                GSsndPlayNow(0x5B6);
                FlashSystemSetNowFrameLabel(0x1F573000, "clear_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "clear_start", "clear_end");
                FlashSystemSetNowFrameLabel(0x1F573000, "clear_start");
                FlashSystemSetPlayFrameLabel(0x1F573000, "clear_start", "clear_end");
                menuOpen(0xF8, 0); menuSetPosition(0xF8, 0, 0);
                frame = FlashSystemGetFrameFromLabel(0x1F573000, "clear_start");
                end = FlashSystemGetFrameFromLabel(0x1F573000, "clear_end");
                while (frame != end) { GSthreadSwitch(); frame = FlashSystemGetNowFrame(0x1F573000); }
                menuClose(0xF8);
                while (windowGetKeyInfo()->unk4 != 0x10) { gBingo.unk13C = 0xDAF8; GSthreadSwitch(); }
                if (gBingo.unk122) fn_802967E4(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1);
                else setClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1);
                retry = 0;
                break;
            }
            case 1:
                while (windowGetKeyInfo()->unk4 != 0x10) {
                    gBingo.unk13C = gBingo.unk122 && !bingoCanOpenPanel(&gBingo) ? 0xDB37 : 0xDAF9;
                    GSthreadSwitch();
                }
                if (isClear__10bingo_biosFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4) - 1)) {
                    gBingo.unk13C = bingoCompletedLines(&gBingo) < 2 ? 0xDAFA : 0xDB3B;
                    GSthreadSwitch();
                    if (menuSubOpenYesNo(0, 0x1BD, 0x104, 0)) retry = 0;
                    else { retry = 1; ResetSheet__6cBingoFUl(&gBingo, getNo__10bingo_biosFP14BINGO_DATA_dd_(&gBingo, gBingo.unk4)); }
                } else retry = 0;
                break;
            }
        }
        fadeSet(3, 0.125f); fadeCheck(1);
        menuClose(0xDC); menuClose(0xC7); menuClose(0xC9); menuClose(0xCA); menuCloseCustom(0xC8, 0, 0); menuClose(0xDC);
    }
    {
        u8 lines = bingoCompletedLines(&gBingo);
        switch (result) { case 2: lines |= 0x10; break; case 3: lines |= 0x20; break; }
        setStaticResult__10bingo_biosFUc(lines);
    }
    GSfloorPop();
}

void menuBingoExit(void) {

}



void menuBingoInit(void) {
    if (GSfloorGetCurrent() == 0x388U) {
        gBingo.unk0 = savedataGetStatus(0, 0x1B);
    }
}

void setStepMessage__6cBingoFv(BingoState *arg0) {
    BingoPokemon *temp_r6;
    BingoPokemon *temp_r6_2;
    BingoPokemon *temp_r6_3;
    BingoPokemon *temp_r6_4;
    BingoPokemon *temp_r6_5;
    BingoPokemon *temp_r7;
    BingoPokemon *temp_r7_10;
    BingoPokemon *temp_r7_2;
    BingoPokemon *temp_r7_3;
    BingoPokemon *temp_r7_4;
    BingoPokemon *temp_r7_5;
    BingoPokemon *temp_r7_6;
    BingoPokemon *temp_r7_7;
    BingoPokemon *temp_r7_8;
    BingoPokemon *temp_r7_9;
    BingoPokemon *temp_r8;
    BingoPokemon *temp_r8_10;
    BingoPokemon *temp_r8_2;
    BingoPokemon *temp_r8_3;
    BingoPokemon *temp_r8_4;
    BingoPokemon *temp_r8_5;
    BingoPokemon *temp_r8_6;
    BingoPokemon *temp_r8_7;
    BingoPokemon *temp_r8_8;
    BingoPokemon *temp_r8_9;
    BingoPokemon *var_r6_6;
    BingoPokemon *var_r7;
    BingoPokemon *var_r7_7;
    BingoPokemon *var_r8;
    BingoPokemon *var_r8_2;
    BingoState *var_r29;
    BingoState *var_r5;
    s32 temp_cr0_eq;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_7;
    s32 temp_r0_8;
    s32 temp_r3_10;
    s32 temp_r3_4;
    s32 temp_r3_8;
    s32 temp_r3_9;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_4;
    s32 temp_r5_5;
    s32 temp_r5_6;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    s32 var_ctr_6;
    s32 var_ctr_7;
    s32 var_ctr_8;
    s32 var_ctr_9;
    s32 var_r27_2;
    s32 var_r28;
    s32 var_r3;
    s32 var_r3_3;
    s32 var_r4;
    s32 var_r4_3;
    s32 var_r6;
    s32 var_r6_2;
    s32 var_r6_3;
    s32 var_r6_4;
    s32 var_r6_5;
    s32 var_r7_4;
    s32 var_r7_5;
    u16 temp_r3_3;
    u32 temp_r25;
    u32 temp_r26;
    u32 temp_r28;
    u32 temp_r3;
    u32 temp_r3_11;
    u32 temp_r3_12;
    u32 temp_r3_5;
    u32 temp_r4;
    u32 var_r24;
    u32 var_r24_2;
    u32 var_r27;
    u32 var_r3_2;
    u8 temp_r0_5;
    u8 temp_r0_6;
    u8 temp_r24;
    u8 temp_r3_2;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r4_2;
    u8 var_r7_2;
    u8 var_r7_3;
    u8 var_r7_6;
    void *temp_r3_6;
    void *temp_r3_7;

    var_r4 = 0;
    arg0->unk13C = 0;
    temp_r5 = arg0->unk108;
    if (temp_r5 != 0) {
        goto block_416;
    }
    temp_r0 = arg0->unk144;
    if ((u32) temp_r0 > 0xBU) {
        goto block_416;
    }
    switch (temp_r0) {                               /* jump table: jtbl_recovery_6 */
case 1:
loop_4:
    var_r7 = mPokemon__6cBingo;
    var_r6 = 0;
    temp_r3 = var_r4 + 1;
    var_ctr = 2;
loop_5:
    if (temp_r3 != (u8) var_r7->unkC5) {
        goto block_7;
    }
    goto block_21;
block_7:
    var_r6 += 1;
    if (temp_r3 != (u8) var_r7[1].unkC5) {
        goto block_9;
    }
    goto block_21;
block_9:
    temp_r7 = (BingoPokemon *)((u8 *)&var_r7[1] + 0xC8);
    var_r6 += 1;
    if (temp_r3 != (u8) temp_r7->unkC5) {
        goto block_11;
    }
    goto block_21;
block_11:
    temp_r7_2 = (BingoPokemon *)((u8 *)temp_r7 + 0xC8);
    var_r6 += 1;
    if (temp_r3 != (u8) temp_r7_2->unkC5) {
        goto block_13;
    }
    goto block_21;
block_13:
    temp_r7_3 = (BingoPokemon *)((u8 *)temp_r7_2 + 0xC8);
    var_r6 += 1;
    if (temp_r3 != (u8) temp_r7_3->unkC5) {
        goto block_15;
    }
    goto block_21;
block_15:
    temp_r7_4 = (BingoPokemon *)((u8 *)temp_r7_3 + 0xC8);
    var_r6 += 1;
    if (temp_r3 != (u8) temp_r7_4->unkC5) {
        goto block_17;
    }
    goto block_21;
block_17:
    temp_r7_5 = (BingoPokemon *)((u8 *)temp_r7_4 + 0xC8);
    var_r6 += 1;
    if (temp_r3 != (u8) temp_r7_5->unkC5) {
        goto block_19;
    }
    goto block_21;
block_19:
    var_r7 = (BingoPokemon *)((u8 *)temp_r7_5 + 0xC8);
    var_r6 += 1;
    var_ctr -= 1;
    if (var_ctr != 0) {
        goto loop_5;
    }
    var_r6 = -1;
block_21:
    if (var_r6 == -1) {
        goto block_23;
    }
    var_r4 += 1;
    if (var_r4 < 4) {
        goto loop_4;
    }
block_23:
    arg0->unk148 = (u8) var_r4;
    temp_r0_2 = arg0->unk134;
    temp_cr0_eq = (u8) arg0->cells[temp_r0_2].unk0 == 0;
    if (temp_cr0_eq != 0) {
        goto block_115;
    }
    var_r0 = -1U;
    if (temp_cr0_eq != 0) {
        goto block_26;
    }
    var_r0 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[temp_r0_2].unk1);
block_26:
    if ((s32) var_r0 != 1) {
        goto block_416;
    }
    if ((s32) arg0->unk124 == 0) {
        goto block_416;
    }
    var_r4_2 = 0;
    arg0->unk13C = 0xDAEA;
    arg0->unk130 = 0;
    temp_r0_3 = arg0->unk134;
    if ((u8) arg0->cells[temp_r0_3].unk2 == 0) {
        goto block_30;
    }
    var_r4_2 = 1;
block_30:
    if (var_r4_2 != 0) {
        goto block_42;
    }
    if ((u8) arg0->cells[temp_r0_3].unk0 == 0) {
        goto block_42;
    }
    temp_r3_2 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[temp_r0_3].unk1);
    if ((s32) temp_r3_2 == 2) {
        goto block_40;
    }
    if ((s32) temp_r3_2 >= 2) {
        goto block_37;
    }
    if ((s32) temp_r3_2 == 0) {
        goto block_42;
    }
    if ((s32) temp_r3_2 >= 0) {
        goto block_39;
    }
    goto block_42;
block_37:
    if ((s32) temp_r3_2 >= 4) {
        goto block_42;
    }
    goto block_41;
block_39:
    arg0->unk129 += 1;
    setStaticBall__10bingo_biosFUc(arg0->unk129);
    goto block_42;
block_40:
    arg0->unk12A += 1;
    goto block_42;
block_41:
    arg0->unk12A += 2;
block_42:
    var_r3 = 0;
    var_r4_3 = 0;
    arg0->cells[arg0->unk134].unk2 = 1;
    for (; var_r4_3 < 0xA; var_r4_3++) {
        if (bingoLineClear(&gBingo, var_r4_3)) {
            var_r3 += 1;
        }
    }
    if ((s32) (var_r3 - arg0->unk12D) == 0) {
        goto block_107;
    }
    GSsndPlayNow(0x575);
    goto block_108;
block_107:
    GSsndPlayNow(0x574);
block_108:
    goto loop_110;
block_109:
    GSthreadSwitch();
loop_110:
    if (0.0f < arg0->cells[arg0->unk134].unk4) {
        goto block_109;
    }
    FlashSystemSetNowFrameLabel(0x1F573000U, "ball_start");
    FlashSystemSetPlayFrameLabel(0x1F573000U, "ball_start", "ball_end");
    menuOpen(0xFB, 0);
    menuSetPosition(0xFB, 0, 0);
    var_r27 = FlashSystemGetFrameFromLabel(0x1F573000U, "ball_start");
    temp_r26 = FlashSystemGetFrameFromLabel(0x1F573000U, "ball_end");
    goto loop_113;
block_112:
    GSthreadSwitch();
    var_r27 = FlashSystemGetNowFrame(0x1F573000U);
loop_113:
    if (var_r27 != temp_r26) {
        goto block_112;
    }
    menuClose(0xFB);
    arg0->unk121 = 1;
    return;
block_115:
    if ((u8) arg0->unk10C == 0) {
        goto block_416;
    }
    temp_r3_3 = fightEncount(0xC);
    arg0->unk130 = (u8) temp_r3_3;
    if ((s32) temp_r3_3 >= 5) {
        goto block_147;
    }
    if ((s32) temp_r3_3 >= 3) {
        goto block_119;
    }
    goto block_147;
block_119:
    menuOpen(0xDC, 0);
    menuOpen(0xC7, 0);
    menuOpen(0xC9, 0);
    menuOpen(0xCA, 0);
    var_r3_2 = 0U;
    var_r5 = arg0;
    var_ctr_3 = 2;
loop_120:
    if ((u8) var_r5->cells[0].unk2 == 0) {
        goto block_122;
    }
    var_r3_2 += 1;
block_122:
    if ((u8) var_r5->cells[1].unk2 == 0) {
        goto block_124;
    }
    var_r3_2 += 1;
block_124:
    if ((u8) var_r5->cells[2].unk2 == 0) {
        goto block_126;
    }
    var_r3_2 += 1;
block_126:
    if ((u8) var_r5->cells[3].unk2 == 0) {
        goto block_128;
    }
    var_r3_2 += 1;
block_128:
    if ((u8) var_r5->cells[4].unk2 == 0) {
        goto block_130;
    }
    var_r3_2 += 1;
block_130:
    if ((u8) var_r5->cells[5].unk2 == 0) {
        goto block_132;
    }
    var_r3_2 += 1;
block_132:
    if ((u8) var_r5->cells[6].unk2 == 0) {
        goto block_134;
    }
    var_r3_2 += 1;
block_134:
    if ((u8) var_r5->cells[7].unk2 == 0) {
        goto block_136;
    }
    var_r3_2 += 1;
block_136:
    var_r5 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5 + 0x40));
    var_ctr_3 -= 1;
    if (var_ctr_3 != 0) {
        goto loop_120;
    }
    if (var_r3_2 == 0U) {
        goto block_139;
    }
    var_r0_2 = 0;
    goto block_140;
block_139:
    var_r0_2 = 1;
block_140:
    if (var_r0_2 != 0) {
        goto block_142;
    }
    temp_r3_4 = arg0->unk138;
    arg0->unk138 = arg0->unk134;
    arg0->unk134 = temp_r3_4;
    goto block_143;
block_142:
    arg0->unk138 = arg0->unk134;
block_143:
    menuOpenCustom(0xC8, 0, &arg0->unk134, 0, 0, 0);
    winSeqSetMenu(0xC7, 0x1A5);
    winSeqSetMenu(0xC9, 0x1A9);
    winSeqSetMenu(0xC8, 0x1AD);
    FlashSystemSetNowFrameLabel(0x1EC93000U, "panel");
    GSthreadSwitch();
    goto loop_145;
block_144:
    GSthreadSwitch();
loop_145:
    if (winSeqCheckMove(0xC8) != 0) {
        goto block_144;
    }
    goto block_150;
block_147:
    menuOpen(0xDC, 0);
    menuOpen(0xC7, 0);
    menuOpen(0xC9, 0);
    menuOpen(0xCA, 0);
    menuOpenCustom(0xC8, 0, &arg0->unk134, 0, 0, 0);
    winSeqSetMenu(0xC7, 0x1A5);
    winSeqSetMenu(0xC9, 0x1A9);
    winSeqSetMenu(0xC8, 0x1AD);
    FlashSystemSetNowFrameLabel(0x1EC93000U, "panel");
    GSthreadSwitch();
    goto loop_149;
block_148:
    GSthreadSwitch();
loop_149:
    if (winSeqCheckMove(0xC8) != 0) {
        goto block_148;
    }
block_150:
    arg0->unk144 = 1;
    arg0->unk10C = 0;
    return;
case 2:
    if ((u8) arg0->cells[arg0->unk134].unk0 != 0) {
        goto block_159;
    }
    temp_r0_5 = arg0->unk130;
    if ((s32) temp_r0_5 == 2) {
        goto block_156;
    }
    if ((s32) temp_r0_5 < 2) {
        goto block_416;
    }
    if ((s32) temp_r0_5 >= 5) {
        goto block_416;
    }
    arg0->unk13C = 0xDAF4;
    return;
block_156:
    temp_r24 = arg0->unk129;
    if (temp_r24 != getStaticBall__10bingo_biosFv()) {
        goto block_158;
    }
    arg0->unk13C = 0xDAF3;
    return;
block_158:
    arg0->unk13C = 0xDB22;
    return;
block_159:
    temp_r0_6 = arg0->unk130;
    if ((s32) temp_r0_6 >= 5) {
        goto block_163;
    }
    if ((s32) temp_r0_6 >= 3) {
        goto block_162;
    }
    goto block_163;
block_162:
    arg0->unk13C = 0xDAF4;
    return;
block_163:
    arg0->unk13C = 0xDAEA;
    return;
case 3:
    var_r3_3 = 0;
    for (; var_r3_3 < 0xA; var_r3_3++) {
        if (bingoLineClear(&gBingo, var_r3_3)) {
            var_r4 += 1;
        }
    }
    temp_r0_7 = var_r4 - arg0->unk12D;
    if (temp_r0_7 == 0) {
        goto block_234;
    }
    if (temp_r0_7 == 1) {
        goto block_232;
    }
    if (temp_r0_7 < 1) {
        goto block_234;
    }
    if (temp_r0_7 >= 4) {
        goto block_234;
    }
    goto block_233;
block_232:
    arg0->unk13C = 0xDAF5;
    goto block_234;
block_233:
    arg0->unk13C = 0xDAF6;
block_234:
    GSthreadSwitch();
    var_r6_2 = 0;
loop_235:
    var_r8 = mPokemon__6cBingo;
    var_r7_4 = 0;
    temp_r3_5 = var_r6_2 + 1;
    var_ctr_5 = 2;
loop_236:
    if (temp_r3_5 != (u8) var_r8->unkC5) {
        goto block_238;
    }
    goto block_252;
block_238:
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) var_r8[1].unkC5) {
        goto block_240;
    }
    goto block_252;
block_240:
    temp_r8 = (BingoPokemon *)((u8 *)&var_r8[1] + 0xC8);
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) temp_r8->unkC5) {
        goto block_242;
    }
    goto block_252;
block_242:
    temp_r8_2 = (BingoPokemon *)((u8 *)temp_r8 + 0xC8);
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) temp_r8_2->unkC5) {
        goto block_244;
    }
    goto block_252;
block_244:
    temp_r8_3 = (BingoPokemon *)((u8 *)temp_r8_2 + 0xC8);
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) temp_r8_3->unkC5) {
        goto block_246;
    }
    goto block_252;
block_246:
    temp_r8_4 = (BingoPokemon *)((u8 *)temp_r8_3 + 0xC8);
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) temp_r8_4->unkC5) {
        goto block_248;
    }
    goto block_252;
block_248:
    temp_r8_5 = (BingoPokemon *)((u8 *)temp_r8_4 + 0xC8);
    var_r7_4 += 1;
    if (temp_r3_5 != (u8) temp_r8_5->unkC5) {
        goto block_250;
    }
    goto block_252;
block_250:
    var_r8 = (BingoPokemon *)((u8 *)temp_r8_5 + 0xC8);
    var_r7_4 += 1;
    var_ctr_5 -= 1;
    if (var_ctr_5 != 0) {
        goto loop_236;
    }
    var_r7_4 = -1;
block_252:
    if (var_r7_4 == -1) {
        goto block_254;
    }
    var_r6_2 += 1;
    if (var_r6_2 < 4) {
        goto loop_235;
    }
block_254:
    if (var_r6_2 == (s32) arg0->unk148) {
        goto block_416;
    }
    var_r29 = arg0;
    var_r28 = 0;
    var_r27_2 = 0;
loop_256:
    if (!(var_r29->cells[0].unk4 > 0.0f)) {
        goto block_286;
    }
    temp_r3_6 = (BingoState *)((u8 *)arg0 + var_r27_2);
    if ((u8) *(u8 *)((u8 *)temp_r3_6 + 8) != 0) {
        goto block_286;
    }
    if ((u8) *(u8 *)((u8 *)temp_r3_6 + 0xA) == 0) {
        goto block_286;
    }
    goto loop_261;
block_260:
    GSthreadSwitch();
loop_261:
    if (var_r29->cells[0].unk4 > 0.0f) {
        goto block_260;
    }
    temp_r3_7 = menuItemBiosGetPtr(0xFA, 0x7FFU);
    var_r6_3 = 0;
loop_263:
    var_r8_2 = mPokemon__6cBingo;
    var_r7_5 = 0;
    temp_r4 = var_r6_3 + 1;
    var_ctr_6 = 2;
loop_264:
    if (temp_r4 != (u8) var_r8_2->unkC5) {
        goto block_266;
    }
    goto block_280;
block_266:
    var_r7_5 += 1;
    if (temp_r4 != (u8) var_r8_2[1].unkC5) {
        goto block_268;
    }
    goto block_280;
block_268:
    temp_r8_6 = (BingoPokemon *)((u8 *)&var_r8_2[1] + 0xC8);
    var_r7_5 += 1;
    if (temp_r4 != (u8) temp_r8_6->unkC5) {
        goto block_270;
    }
    goto block_280;
block_270:
    temp_r8_7 = (BingoPokemon *)((u8 *)temp_r8_6 + 0xC8);
    var_r7_5 += 1;
    if (temp_r4 != (u8) temp_r8_7->unkC5) {
        goto block_272;
    }
    goto block_280;
block_272:
    temp_r8_8 = (BingoPokemon *)((u8 *)temp_r8_7 + 0xC8);
    var_r7_5 += 1;
    if (temp_r4 != (u8) temp_r8_8->unkC5) {
        goto block_274;
    }
    goto block_280;
block_274:
    temp_r8_9 = (BingoPokemon *)((u8 *)temp_r8_8 + 0xC8);
    var_r7_5 += 1;
    if (temp_r4 != (u8) temp_r8_9->unkC5) {
        goto block_276;
    }
    goto block_280;
block_276:
    temp_r8_10 = (BingoPokemon *)((u8 *)temp_r8_9 + 0xC8);
    var_r7_5 += 1;
    if (temp_r4 != (u8) temp_r8_10->unkC5) {
        goto block_278;
    }
    goto block_280;
block_278:
    var_r8_2 = (BingoPokemon *)((u8 *)temp_r8_10 + 0xC8);
    var_r7_5 += 1;
    var_ctr_6 -= 1;
    if (var_ctr_6 != 0) {
        goto loop_264;
    }
    var_r7_5 = -1;
block_280:
    if (var_r7_5 == -1) {
        goto block_282;
    }
    var_r6_3 += 1;
    if (var_r6_3 < 4) {
        goto loop_263;
    }
block_282:
    *(s16 *)((u8 *)temp_r3_7 + 8) = (s16) ((var_r6_3 - 2) * 0x50);
    FlashSystemSetNowFrameLabel(0x1F573000U, "poke2_start");
    FlashSystemSetPlayFrameLabel(0x1F573000U, "poke2_start", "poke2_end");
    menuOpen(0xFA, 0);
    menuSetPosition(0xFA, 0, 0);
    var_r24 = FlashSystemGetFrameFromLabel(0x1F573000U, "poke2_start");
    temp_r25 = FlashSystemGetFrameFromLabel(0x1F573000U, "poke2_end");
    goto loop_284;
block_283:
    GSthreadSwitch();
    var_r24 = FlashSystemGetNowFrame(0x1F573000U);
loop_284:
    if (var_r24 != temp_r25) {
        goto block_283;
    }
    menuClose(0xFA);
block_286:
    var_r29 = (BingoState *)((u8 *)var_r29 + 8);
    var_r28 += 1;
    var_r27_2 += 8;
    if (var_r28 < 0x10) {
        goto loop_256;
    }
    return;
case 4:
    var_r6_4 = 0;
    for (; var_r6_4 < 0xA; var_r6_4++) {
        if (bingoLineClear(&gBingo, var_r6_4)) {
            var_r4 += 1;
        }
    }
    if ((s32) (var_r4 - arg0->unk12D) == 0) {
        goto block_416;
    }
    arg0->unk13C = 0xDAF7;
    return;
case 5:
    if ((u8) arg0->unk12A == 0) {
        goto block_416;
    }
    arg0->unk13C = 0xDAEE;
    if ((s32) arg0->unk124 != -2) {
        goto block_416;
    }
    GSthreadSwitch();
    temp_r3_10 = menuSubOpenSelect2(0, MenuEpMsgIdx__6cBingo, 2, 0x1BD, 0x104, 0, 2, 0);
    if (temp_r3_10 != 0) {
        goto block_360;
    }
    *(s16 *)((u8 *)menuItemBiosGetPtr(0xF9, 0x7FDU) + 8) = (s16) (arg0->unk12C * 0x50);
    FlashSystemSetNowFrameLabel(0x1F573000U, "ep1_start");
    FlashSystemSetPlayFrameLabel(0x1F573000U, "ep1_start", "ep1_end");
    menuOpen(0xF9, 0);
    menuSetPosition(0xF9, 0, 0);
    var_r24_2 = FlashSystemGetFrameFromLabel(0x1F573000U, "ep1_start");
    temp_r28 = FlashSystemGetFrameFromLabel(0x1F573000U, "ep1_end");
    goto loop_358;
block_357:
    GSthreadSwitch();
    var_r24_2 = FlashSystemGetNowFrame(0x1F573000U);
loop_358:
    if (var_r24_2 != temp_r28) {
        goto block_357;
    }
    menuClose(0xF9);
block_360:
    arg0->unk124 = temp_r3_10 + 1;
    return;
case 6:
    if ((u8) arg0->unk12F == 0) {
        goto block_416;
    }
    arg0->unk13C = 0xDB23;
    if ((s32) arg0->unk124 != -1) {
        goto block_416;
    }
    GSthreadSwitch();
    arg0->unk124 = menuSubOpenYesNo(0, 0x1BD, 0x104, 0) + 1;
    return;
case 7:
    if (temp_r5 == 1) {
        goto block_416;
    }
    if ((s32) arg0->unk12E != 1) {
        goto block_370;
    }
    arg0->unk13C = 0xDAE1;
    GSthreadSwitch();
    if (menuSubOpenYesNo(0, 0x1BD, 0x104, 0) == 0) {
        goto block_368;
    }
    goto block_369;
block_368:
    arg0->unk12E = 0;
    arg0->unk144 = 3;
    arg0->unk124 = -1;
    arg0->unk108 = 3;
    return;
block_369:
    arg0->unk12E = 0;
    return;
block_370:
    arg0->unk13C = 0xDAE0;
    return;
case 8:
loop_372:
    var_r7_7 = mPokemon__6cBingo;
    var_r6_5 = 0;
    temp_r3_11 = var_r4 + 1;
    var_ctr_8 = 2;
loop_373:
    if (temp_r3_11 != (u8) var_r7_7->unkC5) {
        goto block_375;
    }
    goto block_389;
block_375:
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) var_r7_7[1].unkC5) {
        goto block_377;
    }
    goto block_389;
block_377:
    temp_r7_6 = (BingoPokemon *)((u8 *)&var_r7_7[1] + 0xC8);
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) temp_r7_6->unkC5) {
        goto block_379;
    }
    goto block_389;
block_379:
    temp_r7_7 = (BingoPokemon *)((u8 *)temp_r7_6 + 0xC8);
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) temp_r7_7->unkC5) {
        goto block_381;
    }
    goto block_389;
block_381:
    temp_r7_8 = (BingoPokemon *)((u8 *)temp_r7_7 + 0xC8);
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) temp_r7_8->unkC5) {
        goto block_383;
    }
    goto block_389;
block_383:
    temp_r7_9 = (BingoPokemon *)((u8 *)temp_r7_8 + 0xC8);
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) temp_r7_9->unkC5) {
        goto block_385;
    }
    goto block_389;
block_385:
    temp_r7_10 = (BingoPokemon *)((u8 *)temp_r7_9 + 0xC8);
    var_r6_5 += 1;
    if (temp_r3_11 != (u8) temp_r7_10->unkC5) {
        goto block_387;
    }
    goto block_389;
block_387:
    var_r7_7 = (BingoPokemon *)((u8 *)temp_r7_10 + 0xC8);
    var_r6_5 += 1;
    var_ctr_8 -= 1;
    if (var_ctr_8 != 0) {
        goto loop_373;
    }
    var_r6_5 = -1;
block_389:
    if (var_r6_5 == -1) {
        goto block_391;
    }
    var_r4 += 1;
    if (var_r4 < 4) {
        goto loop_372;
    }
block_391:
    if (var_r4 <= 1) {
        goto block_393;
    }
    arg0->unk13C = 0xDAE2;
    return;
block_393:
    arg0->unk13C = 0xDB43;
    return;
case 9:
    arg0->unk13C = 0xDB43;
    GSthreadSwitch();
    arg0->unk124 = menuSubOpenSelect2(0, MenuPkmMsgIdx__6cBingo, 3, 0x1BD, 0x104, 0, 3, 0) + 1;
    return;
case 10:
    var_r6_6 = mPokemon__6cBingo;
    temp_r3_12 = arg0->unk12C + 1;
    var_ctr_9 = 2;
loop_396:
    if (temp_r3_12 != (u8) var_r6_6->unkC5) {
        goto block_398;
    }
    goto block_412;
block_398:
    var_r4 += 1;
    if (temp_r3_12 != (u8) var_r6_6[1].unkC5) {
        goto block_400;
    }
    goto block_412;
block_400:
    temp_r6 = (BingoPokemon *)((u8 *)&var_r6_6[1] + 0xC8);
    var_r4 += 1;
    if (temp_r3_12 != (u8) temp_r6->unkC5) {
        goto block_402;
    }
    goto block_412;
block_402:
    temp_r6_2 = (BingoPokemon *)((u8 *)temp_r6 + 0xC8);
    var_r4 += 1;
    if (temp_r3_12 != (u8) temp_r6_2->unkC5) {
        goto block_404;
    }
    goto block_412;
block_404:
    temp_r6_3 = (BingoPokemon *)((u8 *)temp_r6_2 + 0xC8);
    var_r4 += 1;
    if (temp_r3_12 != (u8) temp_r6_3->unkC5) {
        goto block_406;
    }
    goto block_412;
block_406:
    temp_r6_4 = (BingoPokemon *)((u8 *)temp_r6_3 + 0xC8);
    var_r4 += 1;
    if (temp_r3_12 != (u8) temp_r6_4->unkC5) {
        goto block_408;
    }
    goto block_412;
block_408:
    temp_r6_5 = (BingoPokemon *)((u8 *)temp_r6_4 + 0xC8);
    var_r4 += 1;
    if (temp_r3_12 != (u8) temp_r6_5->unkC5) {
        goto block_410;
    }
    goto block_412;
block_410:
    var_r6_6 = (BingoPokemon *)((u8 *)temp_r6_5 + 0xC8);
    var_r4 += 1;
    var_ctr_9 -= 1;
    if (var_ctr_9 != 0) {
        goto loop_396;
    }
    var_r4 = -1;
block_412:
    if ((u8) mPokemon__6cBingo[var_r4].unkC4 != 0) {
        goto block_414;
    }
    arg0->unk13C = 0xDAE6;
    return;
block_414:
    arg0->unk13C = 0xDAE7;
    GSthreadSwitch();
    arg0->unk124 = menuSubOpenYesNo(0, 0x1BD, 0x104, 0) + 1;
    return;
case 11:
    menuOpen(0xD1, 0);
    menuSetPosition(0xD1, 0, (s16) (arg0->unk12C * 0x50));
    windowCheckCursor(0xD1, 1);
    menuClose(0xD1);
    menuCloseSync(0xD1, 1);
    arg0->unk144 = 8;
    arg0->unk124 = -1;
block_416:
    return;
    }
}

void dispPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(BingoState *arg0, u32 arg1, BingoWindow *arg2, BingoSprite *arg3) {
    u8 bingoPanelType;
    s32 sp8;
    BingoState *var_r5;
    BingoState *var_r5_2;
    BingoState *var_r5_3;
    BingoState *var_r5_4;
    BingoState *var_r5_5;
    s16 var_r27;
    s16 var_r28;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r29;
    s32 temp_r3;
    s32 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s32 temp_r4_3;
    s32 temp_r4_5;
    s32 temp_r4_7;
    s32 temp_r5_10;
    s32 temp_r5_12;
    s32 temp_r5_13;
    s32 temp_r5_15;
    s32 temp_r5_17;
    s32 temp_r5_18;
    s32 temp_r5_20;
    s32 temp_r5_2;
    s32 temp_r5_3;
    s32 temp_r5_5;
    s32 temp_r5_7;
    s32 temp_r5_8;
    s32 temp_r6_2;
    s32 temp_r6_4;
    s32 temp_r6_6;
    s32 temp_r6_8;
    s32 temp_r7;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_ctr_5;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_4;
    u32 temp_r4_6;
    u32 temp_r4_8;
    u32 temp_r5;
    u32 temp_r5_11;
    u32 temp_r5_14;
    u32 temp_r5_16;
    u32 temp_r5_19;
    u32 temp_r5_4;
    u32 temp_r5_6;
    u32 temp_r5_9;
    u32 temp_r6;
    u32 temp_r6_3;
    u32 temp_r6_5;
    u32 temp_r6_7;
    u32 temp_r7_2;
    u32 temp_r7_3;
    u32 temp_r7_4;
    u32 var_r3;
    u32 var_r3_2;
    u32 var_r3_3;
    u32 var_r3_4;
    u32 var_r3_5;
    u8 temp_r0_3;
    u8 var_r0;
    u8 var_r0_2;
    u8 var_r0_3;
    u8 var_r0_4;
    u8 var_r0_5;
    u8 var_r0_6;
    u8 var_r0_7;
    u8 var_r0_8;
    void *temp_r23;

    winSpriteSetDisp(arg3, 0);
    if ((s32) arg0->unk144 != 0xF) {
        goto block_2;
    }
    dispShufflePanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1, arg2, arg3);
    return;
block_2:
    if ((u8) arg0->cells[arg1].unk2 == 0) {
        goto block_4;
    }
    var_r0 = 1;
    goto block_5;
block_4:
    var_r0 = 0;
block_5:
    if (var_r0 == 0) {
        goto block_7;
    }
    dispOpenPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1, arg2, arg3);
    goto block_45;
block_7:
    var_r27 = 0;
    temp_r29 = winSpriteGetLayerID(arg2, arg3);
    var_r28 = 0;
    if ((s32) arg0->unk108 == 0) {
        goto block_9;
    }
    var_r0_2 = 0;
    goto block_18;
block_9:
    temp_r0 = arg0->unk144;
    if (temp_r0 == 7) {
        goto block_15;
    }
    if (temp_r0 >= 7) {
        goto block_13;
    }
    if (temp_r0 == 5) {
        goto block_16;
    }
    goto block_17;
block_13:
    if (temp_r0 >= 9) {
        goto block_17;
    }
    goto block_16;
block_15:
    var_r0_2 = 1;
    goto block_18;
block_16:
    var_r0_2 = 2;
    goto block_18;
block_17:
    var_r0_2 = 0;
block_18:
    if (var_r0_2 == 1) {
        goto block_23;
    }
    temp_r0_2 = arg0->unk144;
    if (temp_r0_2 == 0xD) {
        goto block_23;
    }
    if (temp_r0_2 == 0xE) {
        goto block_23;
    }
    if (arg1 != (u32) arg2->unk9E) {
        goto block_23;
    }
    var_r28 = -4;
    var_r27 = -4;
block_23:
    if (var_r27 == 0) {
        goto block_25;
    }
    sp8 = temp_r29;
    windowDrawSprite2(0, 0, 0x46, 0x43, 0x7FU, arg2, 0x2D5U, 0, sp8);
block_25:
    if ((u8) arg0->cells[arg1].unk0 == 0) {
        goto block_27;
    }
    sp8 = temp_r29;
    windowDrawSprite2(var_r27, var_r28, 0x46, 0x43, -1U, arg2, 0x29EU, 0, sp8);
    goto block_28;
block_27:
    temp_r23 = getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
    bingoPanelType = getPanelType__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[(u16) arg1].unk1);
    temp_r0_3 = pokemonDataBiosGetZokuseiDataId(temp_r23, (u16)((s32)bingoPanelType % 18));
    sp8 = temp_r29;
    windowDrawSprite2(var_r27, var_r28, 0x46, 0x43, -1U, arg2, ClosePanelIdx__6cBingo[temp_r0_3], 0, sp8);
block_28:
    if ((s32) arg0->unk108 == 0) {
        goto block_30;
    }
    var_r0_3 = 0;
    goto block_39;
block_30:
    temp_r0_4 = arg0->unk144;
    if (temp_r0_4 == 7) {
        goto block_36;
    }
    if (temp_r0_4 >= 7) {
        goto block_34;
    }
    if (temp_r0_4 == 5) {
        goto block_37;
    }
    goto block_38;
block_34:
    if (temp_r0_4 >= 9) {
        goto block_38;
    }
    goto block_37;
block_36:
    var_r0_3 = 1;
    goto block_39;
block_37:
    var_r0_3 = 2;
    goto block_39;
block_38:
    var_r0_3 = 0;
block_39:
    if (var_r0_3 == 1) {
        goto block_44;
    }
    temp_r0_5 = arg0->unk144;
    if (temp_r0_5 == 0xD) {
        goto block_44;
    }
    if (temp_r0_5 == 0xE) {
        goto block_44;
    }
    if (arg1 == (u32) arg2->unk9E) {
        goto block_44;
    }
    sp8 = temp_r29;
    windowDrawSprite2(var_r27, var_r28, 0x46, 0x43, 0x7FU, arg2, 0x2D5U, 0, sp8);
block_44:
    arg0->cells[arg1].unk4 = 1.0f;
block_45:
    if (arg1 != (u32) arg0->unk134) {
        goto block_262;
    }
    if ((u8) arg0->unk122 == 0) {
        goto block_262;
    }
    if ((s32) arg0->unk144 != 7) {
        goto block_262;
    }
    var_r3 = 0U;
    var_r5 = arg0;
    var_ctr = 2;
loop_49:
    if ((u8) var_r5->cells[0].unk2 == 0) {
        goto block_51;
    }
    var_r3 += 1;
block_51:
    if ((u8) var_r5->cells[1].unk2 == 0) {
        goto block_53;
    }
    var_r3 += 1;
block_53:
    if ((u8) var_r5->cells[2].unk2 == 0) {
        goto block_55;
    }
    var_r3 += 1;
block_55:
    if ((u8) var_r5->cells[3].unk2 == 0) {
        goto block_57;
    }
    var_r3 += 1;
block_57:
    if ((u8) var_r5->cells[4].unk2 == 0) {
        goto block_59;
    }
    var_r3 += 1;
block_59:
    if ((u8) var_r5->cells[5].unk2 == 0) {
        goto block_61;
    }
    var_r3 += 1;
block_61:
    if ((u8) var_r5->cells[6].unk2 == 0) {
        goto block_63;
    }
    var_r3 += 1;
block_63:
    if ((u8) var_r5->cells[7].unk2 == 0) {
        goto block_65;
    }
    var_r3 += 1;
block_65:
    var_r5 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5 + 0x40));
    var_ctr -= 1;
    if (var_ctr != 0) {
        goto loop_49;
    }
    if (var_r3 == 0U) {
        goto block_68;
    }
    var_r0_4 = 0;
    goto block_69;
block_68:
    var_r0_4 = 1;
block_69:
    if (var_r0_4 != 0) {
        goto block_262;
    }
    spriteSetOffset(7, arg3->unk50, arg3->unk52);
    spriteClearScissor(7);
    spriteSetEnv(7);
    temp_r3 = arg0->unk134;
    if ((u8) arg0->unk122 == 0) {
        goto block_83;
    }
    temp_r4 = temp_r3 - 4;
    temp_r6 = (u32) temp_r3 >> 0x1FU;
    temp_r5 = (temp_r3 << 0x1E) - temp_r6;
    temp_r7 = temp_r3 / 4;
    temp_r5_2 = ((temp_r5 << 2) | (temp_r5 >> 0x1EU)) + temp_r6;
    if (temp_r4 != temp_r4) {
        goto block_74;
    }
    if ((s32) (temp_r7 - 1) < 0) {
        goto block_74;
    }
    var_r0_5 = arg0->cells[temp_r4].unk2 == 0;
    goto block_116;
block_74:
    if ((u32) (temp_r3 + 4) != temp_r4) {
        goto block_77;
    }
    if ((s32) (temp_r7 + 1) > 3) {
        goto block_77;
    }
    var_r0_5 = arg0->cells[temp_r4].unk2 == 0;
    goto block_116;
block_77:
    if ((u32) (temp_r3 - 1) != temp_r4) {
        goto block_80;
    }
    if ((s32) (temp_r5_2 - 1) < 0) {
        goto block_80;
    }
    var_r0_5 = arg0->cells[temp_r4].unk2 == 0;
    goto block_116;
block_80:
    if ((u32) (temp_r3 + 1) != temp_r4) {
        goto block_95;
    }
    if ((s32) (temp_r5_2 + 1) > 3) {
        goto block_95;
    }
    var_r0_5 = arg0->cells[temp_r4].unk2 == 0;
    goto block_116;
block_83:
    temp_r5_3 = temp_r3 - 4;
    temp_r6_2 = temp_r5_3 / 4;
    temp_r5_4 = (u32) temp_r5_3 >> 0x1FU;
    temp_r4_2 = (temp_r5_3 << 0x1E) - temp_r5_4;
    temp_r5_5 = ((temp_r4_2 << 2) | (temp_r4_2 >> 0x1EU)) + temp_r5_4;
    if ((s32) (temp_r6_2 - 1) < 0) {
        goto block_86;
    }
    if ((u8) arg0->cells[temp_r3 - 8].unk2 == 0) {
        goto block_86;
    }
    var_r0_5 = 1;
    goto block_116;
block_86:
    if ((s32) (temp_r6_2 + 1) > 3) {
        goto block_89;
    }
    if ((u8) arg0->cells[temp_r3].unk2 == 0) {
        goto block_89;
    }
    var_r0_5 = 1;
    goto block_116;
block_89:
    if ((s32) (temp_r5_5 - 1) < 0) {
        goto block_92;
    }
    if ((u8) arg0->cells[temp_r3 - 5].unk2 == 0) {
        goto block_92;
    }
    var_r0_5 = 1;
    goto block_116;
block_92:
    if ((s32) (temp_r5_5 + 1) > 3) {
        goto block_95;
    }
    if ((u8) arg0->cells[temp_r3 - 3].unk2 == 0) {
        goto block_95;
    }
    var_r0_5 = 1;
    goto block_116;
block_95:
    var_r3_2 = 0U;
    var_r5_2 = arg0;
    var_ctr_2 = 2;
loop_96:
    if ((u8) var_r5_2->cells[0].unk2 == 0) {
        goto block_98;
    }
    var_r3_2 += 1;
block_98:
    if ((u8) var_r5_2->cells[1].unk2 == 0) {
        goto block_100;
    }
    var_r3_2 += 1;
block_100:
    if ((u8) var_r5_2->cells[2].unk2 == 0) {
        goto block_102;
    }
    var_r3_2 += 1;
block_102:
    if ((u8) var_r5_2->cells[3].unk2 == 0) {
        goto block_104;
    }
    var_r3_2 += 1;
block_104:
    if ((u8) var_r5_2->cells[4].unk2 == 0) {
        goto block_106;
    }
    var_r3_2 += 1;
block_106:
    if ((u8) var_r5_2->cells[5].unk2 == 0) {
        goto block_108;
    }
    var_r3_2 += 1;
block_108:
    if ((u8) var_r5_2->cells[6].unk2 == 0) {
        goto block_110;
    }
    var_r3_2 += 1;
block_110:
    if ((u8) var_r5_2->cells[7].unk2 == 0) {
        goto block_112;
    }
    var_r3_2 += 1;
block_112:
    var_r5_2 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5_2 + 0x40));
    var_ctr_2 -= 1;
    if (var_ctr_2 != 0) {
        goto loop_96;
    }
    if (var_r3_2 == 0U) {
        goto block_115;
    }
    var_r0_5 = 0;
    goto block_116;
block_115:
    var_r0_5 = 1;
block_116:
    if (var_r0_5 == 0) {
        goto block_118;
    }
    windowDrawSprite(0x15, -0x10, arg2, (BingoSprite *)0x39A, 0, 7);
block_118:
    temp_r3_2 = arg0->unk134;
    if ((u8) arg0->unk122 == 0) {
        goto block_131;
    }
    temp_r6_3 = (u32) temp_r3_2 >> 0x1FU;
    temp_r5_6 = (temp_r3_2 << 0x1E) - temp_r6_3;
    temp_r7_2 = temp_r3_2 + 4;
    temp_r4_3 = temp_r3_2 / 4;
    temp_r5_7 = ((temp_r5_6 << 2) | (temp_r5_6 >> 0x1EU)) + temp_r6_3;
    if ((u32) (temp_r3_2 - 4) != temp_r7_2) {
        goto block_122;
    }
    if ((s32) (temp_r4_3 - 1) < 0) {
        goto block_122;
    }
    var_r0_6 = arg0->cells[temp_r7_2].unk2 == 0;
    goto block_164;
block_122:
    if ((u32) (temp_r3_2 + 4) != temp_r7_2) {
        goto block_125;
    }
    if ((s32) (temp_r4_3 + 1) > 3) {
        goto block_125;
    }
    var_r0_6 = arg0->cells[temp_r7_2].unk2 == 0;
    goto block_164;
block_125:
    if ((u32) (temp_r3_2 - 1) != temp_r7_2) {
        goto block_128;
    }
    if ((s32) (temp_r5_7 - 1) < 0) {
        goto block_128;
    }
    var_r0_6 = arg0->cells[temp_r7_2].unk2 == 0;
    goto block_164;
block_128:
    if ((u32) (temp_r3_2 + 1) != temp_r7_2) {
        goto block_143;
    }
    if ((s32) (temp_r5_7 + 1) > 3) {
        goto block_143;
    }
    var_r0_6 = arg0->cells[temp_r7_2].unk2 == 0;
    goto block_164;
block_131:
    temp_r5_8 = temp_r3_2 + 4;
    temp_r6_4 = temp_r5_8 / 4;
    temp_r5_9 = (u32) temp_r5_8 >> 0x1FU;
    temp_r4_4 = (temp_r5_8 << 0x1E) - temp_r5_9;
    temp_r5_10 = ((temp_r4_4 << 2) | (temp_r4_4 >> 0x1EU)) + temp_r5_9;
    if ((s32) (temp_r6_4 - 1) < 0) {
        goto block_134;
    }
    if ((u8) arg0->cells[temp_r3_2].unk2 == 0) {
        goto block_134;
    }
    var_r0_6 = 1;
    goto block_164;
block_134:
    if ((s32) (temp_r6_4 + 1) > 3) {
        goto block_137;
    }
    if ((u8) arg0->cells[temp_r3_2 + 8].unk2 == 0) {
        goto block_137;
    }
    var_r0_6 = 1;
    goto block_164;
block_137:
    if ((s32) (temp_r5_10 - 1) < 0) {
        goto block_140;
    }
    if ((u8) arg0->cells[temp_r3_2 + 3].unk2 == 0) {
        goto block_140;
    }
    var_r0_6 = 1;
    goto block_164;
block_140:
    if ((s32) (temp_r5_10 + 1) > 3) {
        goto block_143;
    }
    if ((u8) arg0->cells[temp_r3_2 + 5].unk2 == 0) {
        goto block_143;
    }
    var_r0_6 = 1;
    goto block_164;
block_143:
    var_r3_3 = 0U;
    var_r5_3 = arg0;
    var_ctr_3 = 2;
loop_144:
    if ((u8) var_r5_3->cells[0].unk2 == 0) {
        goto block_146;
    }
    var_r3_3 += 1;
block_146:
    if ((u8) var_r5_3->cells[1].unk2 == 0) {
        goto block_148;
    }
    var_r3_3 += 1;
block_148:
    if ((u8) var_r5_3->cells[2].unk2 == 0) {
        goto block_150;
    }
    var_r3_3 += 1;
block_150:
    if ((u8) var_r5_3->cells[3].unk2 == 0) {
        goto block_152;
    }
    var_r3_3 += 1;
block_152:
    if ((u8) var_r5_3->cells[4].unk2 == 0) {
        goto block_154;
    }
    var_r3_3 += 1;
block_154:
    if ((u8) var_r5_3->cells[5].unk2 == 0) {
        goto block_156;
    }
    var_r3_3 += 1;
block_156:
    if ((u8) var_r5_3->cells[6].unk2 == 0) {
        goto block_158;
    }
    var_r3_3 += 1;
block_158:
    if ((u8) var_r5_3->cells[7].unk2 == 0) {
        goto block_160;
    }
    var_r3_3 += 1;
block_160:
    var_r5_3 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5_3 + 0x40));
    var_ctr_3 -= 1;
    if (var_ctr_3 != 0) {
        goto loop_144;
    }
    if (var_r3_3 == 0U) {
        goto block_163;
    }
    var_r0_6 = 0;
    goto block_164;
block_163:
    var_r0_6 = 1;
block_164:
    if (var_r0_6 == 0) {
        goto block_166;
    }
    windowDrawSprite(0x15, 0x37, arg2, (BingoSprite *)0x39C, 0, 7);
block_166:
    temp_r3_3 = arg0->unk134;
    if ((u8) arg0->unk122 == 0) {
        goto block_179;
    }
    temp_r6_5 = (u32) temp_r3_3 >> 0x1FU;
    temp_r5_11 = (temp_r3_3 << 0x1E) - temp_r6_5;
    temp_r7_3 = temp_r3_3 - 1;
    temp_r4_5 = temp_r3_3 / 4;
    temp_r5_12 = ((temp_r5_11 << 2) | (temp_r5_11 >> 0x1EU)) + temp_r6_5;
    if ((u32) (temp_r3_3 - 4) != temp_r7_3) {
        goto block_170;
    }
    if ((s32) (temp_r4_5 - 1) < 0) {
        goto block_170;
    }
    var_r0_7 = arg0->cells[temp_r7_3].unk2 == 0;
    goto block_212;
block_170:
    if ((u32) (temp_r3_3 + 4) != temp_r7_3) {
        goto block_173;
    }
    if ((s32) (temp_r4_5 + 1) > 3) {
        goto block_173;
    }
    var_r0_7 = arg0->cells[temp_r7_3].unk2 == 0;
    goto block_212;
block_173:
    if ((u32) (temp_r3_3 - 1) != temp_r7_3) {
        goto block_176;
    }
    if ((s32) (temp_r5_12 - 1) < 0) {
        goto block_176;
    }
    var_r0_7 = arg0->cells[temp_r7_3].unk2 == 0;
    goto block_212;
block_176:
    if ((u32) (temp_r3_3 + 1) != temp_r7_3) {
        goto block_191;
    }
    if ((s32) (temp_r5_12 + 1) > 3) {
        goto block_191;
    }
    var_r0_7 = arg0->cells[temp_r7_3].unk2 == 0;
    goto block_212;
block_179:
    temp_r5_13 = temp_r3_3 - 1;
    temp_r6_6 = temp_r5_13 / 4;
    temp_r5_14 = (u32) temp_r5_13 >> 0x1FU;
    temp_r4_6 = (temp_r5_13 << 0x1E) - temp_r5_14;
    temp_r5_15 = ((temp_r4_6 << 2) | (temp_r4_6 >> 0x1EU)) + temp_r5_14;
    if ((s32) (temp_r6_6 - 1) < 0) {
        goto block_182;
    }
    if ((u8) arg0->cells[temp_r3_3 - 5].unk2 == 0) {
        goto block_182;
    }
    var_r0_7 = 1;
    goto block_212;
block_182:
    if ((s32) (temp_r6_6 + 1) > 3) {
        goto block_185;
    }
    if ((u8) arg0->cells[temp_r3_3 + 3].unk2 == 0) {
        goto block_185;
    }
    var_r0_7 = 1;
    goto block_212;
block_185:
    if ((s32) (temp_r5_15 - 1) < 0) {
        goto block_188;
    }
    if ((u8) arg0->cells[temp_r3_3 - 2].unk2 == 0) {
        goto block_188;
    }
    var_r0_7 = 1;
    goto block_212;
block_188:
    if ((s32) (temp_r5_15 + 1) > 3) {
        goto block_191;
    }
    if ((u8) arg0->cells[temp_r3_3].unk2 == 0) {
        goto block_191;
    }
    var_r0_7 = 1;
    goto block_212;
block_191:
    var_r3_4 = 0U;
    var_r5_4 = arg0;
    var_ctr_4 = 2;
loop_192:
    if ((u8) var_r5_4->cells[0].unk2 == 0) {
        goto block_194;
    }
    var_r3_4 += 1;
block_194:
    if ((u8) var_r5_4->cells[1].unk2 == 0) {
        goto block_196;
    }
    var_r3_4 += 1;
block_196:
    if ((u8) var_r5_4->cells[2].unk2 == 0) {
        goto block_198;
    }
    var_r3_4 += 1;
block_198:
    if ((u8) var_r5_4->cells[3].unk2 == 0) {
        goto block_200;
    }
    var_r3_4 += 1;
block_200:
    if ((u8) var_r5_4->cells[4].unk2 == 0) {
        goto block_202;
    }
    var_r3_4 += 1;
block_202:
    if ((u8) var_r5_4->cells[5].unk2 == 0) {
        goto block_204;
    }
    var_r3_4 += 1;
block_204:
    if ((u8) var_r5_4->cells[6].unk2 == 0) {
        goto block_206;
    }
    var_r3_4 += 1;
block_206:
    if ((u8) var_r5_4->cells[7].unk2 == 0) {
        goto block_208;
    }
    var_r3_4 += 1;
block_208:
    var_r5_4 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5_4 + 0x40));
    var_ctr_4 -= 1;
    if (var_ctr_4 != 0) {
        goto loop_192;
    }
    if (var_r3_4 == 0U) {
        goto block_211;
    }
    var_r0_7 = 0;
    goto block_212;
block_211:
    var_r0_7 = 1;
block_212:
    if (var_r0_7 == 0) {
        goto block_214;
    }
    windowDrawSprite(-0xF, 0x14, arg2, (BingoSprite *)0x39B, 0, 7);
block_214:
    temp_r3_4 = arg0->unk134;
    if ((u8) arg0->unk122 == 0) {
        goto block_227;
    }
    temp_r6_7 = (u32) temp_r3_4 >> 0x1FU;
    temp_r5_16 = (temp_r3_4 << 0x1E) - temp_r6_7;
    temp_r7_4 = temp_r3_4 + 1;
    temp_r4_7 = temp_r3_4 / 4;
    temp_r5_17 = ((temp_r5_16 << 2) | (temp_r5_16 >> 0x1EU)) + temp_r6_7;
    if ((u32) (temp_r3_4 - 4) != temp_r7_4) {
        goto block_218;
    }
    if ((s32) (temp_r4_7 - 1) < 0) {
        goto block_218;
    }
    var_r0_8 = arg0->cells[temp_r7_4].unk2 == 0;
    goto block_260;
block_218:
    if ((u32) (temp_r3_4 + 4) != temp_r7_4) {
        goto block_221;
    }
    if ((s32) (temp_r4_7 + 1) > 3) {
        goto block_221;
    }
    var_r0_8 = arg0->cells[temp_r7_4].unk2 == 0;
    goto block_260;
block_221:
    if ((u32) (temp_r3_4 - 1) != temp_r7_4) {
        goto block_224;
    }
    if ((s32) (temp_r5_17 - 1) < 0) {
        goto block_224;
    }
    var_r0_8 = arg0->cells[temp_r7_4].unk2 == 0;
    goto block_260;
block_224:
    if ((u32) (temp_r3_4 + 1) != temp_r7_4) {
        goto block_239;
    }
    if ((s32) (temp_r5_17 + 1) > 3) {
        goto block_239;
    }
    var_r0_8 = arg0->cells[temp_r7_4].unk2 == 0;
    goto block_260;
block_227:
    temp_r5_18 = temp_r3_4 + 1;
    temp_r6_8 = temp_r5_18 / 4;
    temp_r5_19 = (u32) temp_r5_18 >> 0x1FU;
    temp_r4_8 = (temp_r5_18 << 0x1E) - temp_r5_19;
    temp_r5_20 = ((temp_r4_8 << 2) | (temp_r4_8 >> 0x1EU)) + temp_r5_19;
    if ((s32) (temp_r6_8 - 1) < 0) {
        goto block_230;
    }
    if ((u8) arg0->cells[temp_r3_4 - 3].unk2 == 0) {
        goto block_230;
    }
    var_r0_8 = 1;
    goto block_260;
block_230:
    if ((s32) (temp_r6_8 + 1) > 3) {
        goto block_233;
    }
    if ((u8) arg0->cells[temp_r3_4 + 5].unk2 == 0) {
        goto block_233;
    }
    var_r0_8 = 1;
    goto block_260;
block_233:
    if ((s32) (temp_r5_20 - 1) < 0) {
        goto block_236;
    }
    if ((u8) arg0->cells[temp_r3_4].unk2 == 0) {
        goto block_236;
    }
    var_r0_8 = 1;
    goto block_260;
block_236:
    if ((s32) (temp_r5_20 + 1) > 3) {
        goto block_239;
    }
    if ((u8) arg0->cells[temp_r3_4 + 2].unk2 == 0) {
        goto block_239;
    }
    var_r0_8 = 1;
    goto block_260;
block_239:
    var_r3_5 = 0U;
    var_r5_5 = arg0;
    var_ctr_5 = 2;
loop_240:
    if ((u8) var_r5_5->cells[0].unk2 == 0) {
        goto block_242;
    }
    var_r3_5 += 1;
block_242:
    if ((u8) var_r5_5->cells[1].unk2 == 0) {
        goto block_244;
    }
    var_r3_5 += 1;
block_244:
    if ((u8) var_r5_5->cells[2].unk2 == 0) {
        goto block_246;
    }
    var_r3_5 += 1;
block_246:
    if ((u8) var_r5_5->cells[3].unk2 == 0) {
        goto block_248;
    }
    var_r3_5 += 1;
block_248:
    if ((u8) var_r5_5->cells[4].unk2 == 0) {
        goto block_250;
    }
    var_r3_5 += 1;
block_250:
    if ((u8) var_r5_5->cells[5].unk2 == 0) {
        goto block_252;
    }
    var_r3_5 += 1;
block_252:
    if ((u8) var_r5_5->cells[6].unk2 == 0) {
        goto block_254;
    }
    var_r3_5 += 1;
block_254:
    if ((u8) var_r5_5->cells[7].unk2 == 0) {
        goto block_256;
    }
    var_r3_5 += 1;
block_256:
    var_r5_5 = (BingoState *)((u8 *)(BingoState *)((u8 *)var_r5_5 + 0x40));
    var_ctr_5 -= 1;
    if (var_ctr_5 != 0) {
        goto loop_240;
    }
    if (var_r3_5 == 0U) {
        goto block_259;
    }
    var_r0_8 = 0;
    goto block_260;
block_259:
    var_r0_8 = 1;
block_260:
    if (var_r0_8 == 0) {
        goto block_262;
    }
    windowDrawSprite(0x39, 0x14, arg2, (BingoSprite *)0x39D, 0, 7);
block_262:
    return;
}

void dispOpenPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(BingoState *arg0, u32 arg1, BingoWindow *arg2, BingoSprite *arg3) {
    u8 bingoPanelType;
    s32 temp_r30;
    BingoSprite sp98;
    BingoSprite sp20;
    f32 facePositionA[2];
    f32 facePositionB[2];
    s32 sp8;
    f32 temp_f2;
    f32 temp_f31;
    f32 temp_f31_2;
    f32 temp_f3_11;
    f32 temp_f3_13;
    f32 temp_f3_2;
    f32 temp_f3_4;
    f32 temp_f3_5;
    f32 temp_f3_7;
    f32 temp_f3_9;
    f32 temp_f4;
    f64 temp_f3;
    f64 temp_f3_10;
    f64 temp_f3_12;
    f64 temp_f3_3;
    f64 temp_f3_6;
    f64 temp_f3_8;
    s16 temp_r0;
    s16 temp_r24_3;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s16 temp_r3_5;
    s16 temp_r4;
    s16 temp_r4_2;
    s16 temp_r5;
    s16 temp_r5_2;
    s32 temp_r0_2;
    s32 temp_r0_3;
    u16 temp_r24_2;
    u16 temp_r29;
    u16 temp_r31;
    u8 temp_r25;
    u8 temp_r3_6;
    void *temp_r24;

    temp_r30 = winSpriteGetLayerID(arg2, arg3);
    temp_f2 = arg0->cells[arg1].unk4;
    if (temp_f2 > 0.0f) {
        temp_f31 = 3.14f * temp_f2;
        if (temp_f2 > 0.5f) {
            if ((u8) arg0->cells[arg1].unk0 != 0) {
                temp_f3 = fabs((f32) cos((f64) temp_f31));
                sp8 = temp_r30;
                temp_f3_2 = (f32) temp_f3;
                temp_r3 = (s16) (-35.0f * temp_f3_2);
                windowDrawSprite2((s16) (temp_r3 + 0x23), 0, (s16) ((35.0f * temp_f3_2) - (f32) temp_r3), 0x43, -1U, arg2, 0x29EU, 0, sp8);
            } else {
                temp_r24 = getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
                bingoPanelType = getPanelType__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[(u16) arg1].unk1);
                temp_r24_2 = ClosePanelIdx__6cBingo[pokemonDataBiosGetZokuseiDataId(temp_r24, (u16)((s32)bingoPanelType % 18))];
                temp_f3_3 = fabs((f32) cos((f64) temp_f31));
                sp8 = temp_r30;
                temp_f3_4 = (f32) temp_f3_3;
                temp_r3_2 = (s16) (-35.0f * temp_f3_4);
                windowDrawSprite2((s16) (temp_r3_2 + 0x23), 0, (s16) ((35.0f * temp_f3_4) - (f32) temp_r3_2), 0x43, -1U, arg2, temp_r24_2, 0, sp8);
            }
            arg0->cells[arg1].unk4 = -((4.0f * timeGetLastFrameSec()) - arg0->cells[arg1].unk4);
            return;
        }
        if ((u8) arg0->cells[arg1].unk0 != 0) {
            temp_r25 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[arg1].unk1);
            temp_f3_5 = (f32) fabs((f32) cos((f64) temp_f31));
            temp_r4 = (s16) (-35.0f * temp_f3_5);
            temp_r5 = (s16) ((35.0f * temp_f3_5) - (f32) temp_r4);
            switch ((s32) temp_r25) {               /* switch 1; irregular */
            case 0:                                 /* switch 1 */
                break;
            case 1:                                 /* switch 1 */
                sp8 = temp_r30;
                windowDrawSprite2((s16) (temp_r4 + 0x23), 0, temp_r5, 0x43, -1U, arg2, 0x281U, 0, sp8);
                temp_f3_6 = fabs((f32) cos((f64) temp_f31));
                sp8 = temp_r30;
                temp_f3_7 = (f32) temp_f3_6;
                temp_r3_3 = (s16) (-19.0f * temp_f3_7);
                windowDrawSprite2((s16) (temp_r3_3 + 0x23), 7, (s16) ((19.0f * temp_f3_7) - (f32) temp_r3_3), 0x26, -1U, arg2, 0x27CU, 0, sp8);
                break;
            case 2:                                 /* switch 1 */
                sp8 = temp_r30;
                windowDrawSprite2((s16) (temp_r4 + 0x23), 0, temp_r5, 0x43, -1U, arg2, 0x281U, 0, sp8);
                temp_f3_8 = fabs((f32) cos((f64) temp_f31));
                sp8 = temp_r30;
                temp_f3_9 = (f32) temp_f3_8;
                temp_r3_4 = (s16) (-19.0f * temp_f3_9);
                windowDrawSprite2((s16) (temp_r3_4 + 0x23), 7, (s16) ((19.0f * temp_f3_9) - (f32) temp_r3_4), 0x26, -1U, arg2, 0x27DU, 0, sp8);
                break;
            case 3:                                 /* switch 1 */
                sp8 = temp_r30;
                windowDrawSprite2((s16) (temp_r4 + 0x23), 0, temp_r5, 0x43, -1U, arg2, 0x282U, 0, sp8);
                temp_f3_10 = fabs((f32) cos((f64) temp_f31));
                sp8 = temp_r30;
                temp_f3_11 = (f32) temp_f3_10;
                temp_r3_5 = (s16) (-19.0f * temp_f3_11);
                windowDrawSprite2((s16) (temp_r3_5 + 0x23), 7, (s16) ((19.0f * temp_f3_11) - (f32) temp_r3_5), 0x26, -1U, arg2, 0x27DU, 0, sp8);
                break;
            }
            arg0->cells[arg1].unk4 = -((4.0f * timeGetLastFrameSec()) - arg0->cells[arg1].unk4);
            return;
        }
        getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
        facePositionA[0] = 14.0f;
        facePositionA[1] = 5.0f;
        temp_r31 = pokemonDataBiosGetStatusFaceMenuSpriteId(getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]), 0);
        memcpy(&sp98, arg3, 0x78U);
        arg3->unk56 = 0x2A;
        arg3->unk54 = 0x2A;
        if (temp_f31 > 0.0f) {
            temp_r0 = (s32) facePositionA[0] - 0x23;
            temp_f4 = (f32) fabs((f32) cos((f64) temp_f31));
            temp_r4_2 = (s16) (temp_f4 * (f32) temp_r0);
            arg3->unk54 = (s16) ((temp_f4 * (f32) (s16) (temp_r0 + arg3->unk54)) - (f32) temp_r4_2);
            facePositionA[0] = (f32) (s16) (temp_r4_2 + 0x23);
        }
        menuFaceDispFromID2(arg2, arg3, temp_r31, &facePositionA[0]);
        memcpy(arg3, &sp98, 0x78U);
        temp_f3_12 = fabs((f32) cos((f64) temp_f31));
        sp8 = temp_r30;
        temp_f3_13 = (f32) temp_f3_12;
        temp_r5_2 = (s16) (-35.0f * temp_f3_13);
        windowDrawSprite2((s16) (temp_r5_2 + 0x23), 0, (s16) ((35.0f * temp_f3_13) - (f32) temp_r5_2), 0x43, -1U, arg2, 0x280U, 0, sp8);
        temp_f31_2 = (f32) fabs((f32) cos((f64) temp_f31));
        temp_r24_3 = (s16) (10.0f * temp_f31_2);
        temp_r0_2 = wazaDB_GetZokuseiDataId(getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[arg1].unk1)) * 2;
        sp8 = temp_r30;
        windowDrawSprite2((s16) (temp_r24_3 + 0x23), 0x2E, (s16) ((31.0f * temp_f31_2) - (f32) temp_r24_3), 0x12, -1U, arg2, *(const u16 *)((const u8 *)OpenPanelType__6cBingo + temp_r0_2), 0, sp8);
        arg0->cells[arg1].unk4 = -((4.0f * timeGetLastFrameSec()) - arg0->cells[arg1].unk4);
        if (arg0->cells[arg1].unk4 < 0.0f) {
            arg0->cells[arg1].unk4 = 0.0f;
            arg0->cells[arg1].unk3 = 1;
        }
    } else if ((u8) arg0->cells[arg1].unk0 != 0) {
        temp_r3_6 = getGridGrid__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[arg1].unk1);
        switch ((s32) temp_r3_6) {                  /* switch 2; irregular */
        case 0:
            break;
        case 1:                                     /* switch 2 */
            sp8 = temp_r30;
            windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, 0x281U, 0, sp8);
            sp8 = temp_r30;
            windowDrawSprite2(0x10, 7, 0x26, 0x26, -1U, arg2, 0x27CU, 0, sp8);
            return;
        case 2:                                     /* switch 2 */
            sp8 = temp_r30;
            windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, 0x281U, 0, sp8);
            sp8 = temp_r30;
            windowDrawSprite2(0x10, 7, 0x26, 0x26, -1U, arg2, 0x27DU, 0, sp8);
            return;
        case 3:                                     /* switch 2 */
            sp8 = temp_r30;
            windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, 0x282U, 0, sp8);
            sp8 = temp_r30;
            windowDrawSprite2(0x10, 7, 0x26, 0x26, -1U, arg2, 0x27DU, 0, sp8);
            return;
        }
    } else {
        getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
        facePositionB[0] = 14.0f;
        facePositionB[1] = 5.0f;
        temp_r29 = pokemonDataBiosGetStatusFaceMenuSpriteId(getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]), 0);
        memcpy(&sp20, arg3, 0x78U);
        arg3->unk56 = 0x2A;
        arg3->unk54 = 0x2A;
        menuFaceDispFromID2(arg2, arg3, temp_r29, &facePositionB[0]);
        memcpy(arg3, &sp20, 0x78U);
        sp8 = temp_r30;
        windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, 0x280U, 0, sp8);
        temp_r0_3 = wazaDB_GetZokuseiDataId(getPanelWaza__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[arg1].unk1)) * 2;
        sp8 = temp_r30;
        windowDrawSprite2(0x2D, 0x2E, 0x15, 0x12, -1U, arg2, *(const u16 *)((const u8 *)OpenPanelType__6cBingo + temp_r0_3), 0, sp8);
    }
}

void dispShufflePanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(BingoState *arg0, u32 arg1, BingoWindow *arg2, BingoSprite *arg3) {
    u8 bingoPanelType;
    s32 sp8;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f3_2;
    f32 temp_f3_4;
    f32 temp_f3_6;
    f32 temp_f3_8;
    f64 temp_f3;
    f64 temp_f3_3;
    f64 temp_f3_5;
    f64 temp_f3_7;
    s16 temp_r3;
    s16 temp_r3_2;
    s16 temp_r3_3;
    s16 temp_r3_4;
    s32 temp_r0;
    s32 temp_r31;
    u16 temp_r25_3;
    u16 temp_r25_5;
    void *temp_r25;
    void *temp_r25_2;
    void *temp_r25_4;

    temp_f31 = 3.14f * arg0->backup[arg1].unk4;
    temp_f1 = arg0->backup[arg1].unk4;
    temp_r31 = winSpriteGetLayerID(arg2, arg3);
    if (temp_f1 <= 0.0f) {
        if ((u8) arg0->cells[arg1].unk0 != 0) {
            sp8 = temp_r31;
            windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, 0x29EU, 0, sp8);
        } else {
            temp_r25 = getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
            bingoPanelType = getPanelType__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[(u16) arg1].unk1);
            temp_r0 = pokemonDataBiosGetZokuseiDataId(temp_r25, (u16)((s32)bingoPanelType % 18)) * 2;
            sp8 = temp_r31;
            windowDrawSprite2(0, 0, 0x46, 0x43, -1U, arg2, *(const u16 *)((const u8 *)ClosePanelIdx__6cBingo + temp_r0), 0, sp8);
        }
        arg0->cells[arg1].unk4 = -((8.0f * timeGetLastFrameSec()) - arg0->cells[arg1].unk4);
        return;
    }
    if (temp_f1 > 0.5f) {
        if ((u8) arg0->cells[arg1].unk0 != 0) {
            temp_f3 = fabs((f32) cos((f64) temp_f31));
            sp8 = temp_r31;
            temp_f3_2 = (f32) temp_f3;
            temp_r3 = (s16) (temp_f3_2 * -35.0f);
            windowDrawSprite2((s16) (temp_r3 + 0x23), 0, (s16) ((temp_f3_2 * 35.0f) - (f32) temp_r3), 0x43, -1U, arg2, 0x29EU, 0, sp8);
        } else {
            temp_r25_2 = getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->cells[arg1].unk1]);
            bingoPanelType = getPanelType__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->cells[(u16) arg1].unk1);
            temp_r25_3 = ClosePanelIdx__6cBingo[pokemonDataBiosGetZokuseiDataId(temp_r25_2, (u16)((s32)bingoPanelType % 18))];
            temp_f3_3 = fabs((f32) cos((f64) temp_f31));
            sp8 = temp_r31;
            temp_f3_4 = (f32) temp_f3_3;
            temp_r3_2 = (s16) (temp_f3_4 * -35.0f);
            windowDrawSprite2((s16) (temp_r3_2 + 0x23), 0, (s16) ((temp_f3_4 * 35.0f) - (f32) temp_r3_2), 0x43, -1U, arg2, temp_r25_3, 0, sp8);
        }
        arg0->backup[arg1].unk4 = -((8.0f * timeGetLastFrameSec()) - arg0->backup[arg1].unk4);
        return;
    }
    if ((u8) arg0->backup[arg1].unk0 != 0) {
        temp_f3_5 = fabs((f32) cos((f64) temp_f31));
        sp8 = temp_r31;
        temp_f3_6 = (f32) temp_f3_5;
        temp_r3_3 = (s16) (temp_f3_6 * -35.0f);
        windowDrawSprite2((s16) (temp_r3_3 + 0x23), 0, (s16) ((temp_f3_6 * 35.0f) - (f32) temp_r3_3), 0x43, -1U, arg2, 0x29EU, 0, sp8);
    } else {
        temp_r25_4 = getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[arg0->backup[arg1].unk1]);
        bingoPanelType = getPanelType__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, (u32) arg0->backup[arg1].unk1);
        temp_r25_5 = ClosePanelIdx__6cBingo[pokemonDataBiosGetZokuseiDataId(temp_r25_4, (u16)((s32)bingoPanelType % 18))];
        temp_f3_7 = fabs((f32) cos((f64) temp_f31));
        sp8 = temp_r31;
        temp_f3_8 = (f32) temp_f3_7;
        temp_r3_4 = (s16) (temp_f3_8 * -35.0f);
        windowDrawSprite2((s16) (temp_r3_4 + 0x23), 0, (s16) ((temp_f3_8 * 35.0f) - (f32) temp_r3_4), 0x43, -1U, arg2, temp_r25_5, 0, sp8);
    }
    arg0->backup[arg1].unk4 = -((8.0f * timeGetLastFrameSec()) - arg0->backup[arg1].unk4);
    if (arg0->backup[arg1].unk4 < 0.0f) {
        arg0->cells[arg1].unk0 = arg0->backup[arg1].unk0;
        arg0->cells[arg1].unk1 = arg0->backup[arg1].unk1;
        arg0->cells[arg1].unk2 = arg0->backup[arg1].unk2;
        arg0->cells[arg1].unk3 = arg0->backup[arg1].unk3;
        arg0->cells[arg1].unk4 = arg0->backup[arg1].unk4;
    }
}

void dispPkmPanel__6cBingoFUlP14tagWINDOW_WORKP14tagSPRITE_WORK(BingoState *arg0, u32 arg1, BingoWindow *arg2, BingoSprite *arg3) {
    BingoSprite sp18;
    f32 sp14;
    f32 sp10;
    s32 sp8;
    BingoPokemon *temp_r28;
    BingoPokemon *temp_r5;
    BingoPokemon *temp_r5_2;
    BingoPokemon *temp_r5_3;
    BingoPokemon *temp_r5_4;
    BingoPokemon *temp_r5_5;
    BingoPokemon *temp_r5_6;
    BingoPokemon *temp_r7;
    BingoPokemon *temp_r7_10;
    BingoPokemon *temp_r7_2;
    BingoPokemon *temp_r7_3;
    BingoPokemon *temp_r7_4;
    BingoPokemon *temp_r7_5;
    BingoPokemon *temp_r7_6;
    BingoPokemon *temp_r7_7;
    BingoPokemon *temp_r7_8;
    BingoPokemon *temp_r7_9;
    BingoPokemon *var_r5;
    BingoPokemon *var_r7;
    BingoPokemon *var_r7_2;
    BingoSprite *temp_r25_2;
    BingoSprite *temp_r6;
    BingoState *var_r3;
    f32 temp_f1;
    f32 var_f1;
    s16 temp_r31;
    s32 temp_r27;
    s32 temp_r3;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    s32 var_r28;
    s32 var_r31;
    s32 var_r4;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r6;
    s32 var_r6_2;
    u16 temp_r25;
    u16 temp_r3_3;
    u16 temp_r3_4;
    u32 temp_r4;
    u32 temp_r4_2;
    u32 temp_r4_3;
    u32 var_r3_2;
    u8 temp_r3_2;

    var_r28 = 0;
    temp_r27 = winSpriteGetLayerID(arg2, arg3);
    var_r5 = mPokemon__6cBingo;
    temp_r4 = arg1 + 1;
    var_ctr = 2;
loop_1:
    if (temp_r4 == (u8) var_r5->unkC5) {

    } else {
        var_r28 += 1;
        if (temp_r4 == (u8) var_r5[1].unkC5) {

        } else {
            temp_r5 = (BingoPokemon *)((u8 *)&var_r5[1] + 0xC8);
            var_r28 += 1;
            if (temp_r4 == (u8) temp_r5->unkC5) {

            } else {
                temp_r5_2 = (BingoPokemon *)((u8 *)temp_r5 + 0xC8);
                var_r28 += 1;
                if (temp_r4 == (u8) temp_r5_2->unkC5) {

                } else {
                    temp_r5_3 = (BingoPokemon *)((u8 *)temp_r5_2 + 0xC8);
                    var_r28 += 1;
                    if (temp_r4 == (u8) temp_r5_3->unkC5) {

                    } else {
                        temp_r5_4 = (BingoPokemon *)((u8 *)temp_r5_3 + 0xC8);
                        var_r28 += 1;
                        if (temp_r4 == (u8) temp_r5_4->unkC5) {

                        } else {
                            temp_r5_5 = (BingoPokemon *)((u8 *)temp_r5_4 + 0xC8);
                            var_r28 += 1;
                            if (temp_r4 == (u8) temp_r5_5->unkC5) {

                            } else {
                                var_r5 = (BingoPokemon *)((u8 *)temp_r5_5 + 0xC8);
                                var_r28 += 1;
                                var_ctr -= 1;
                                if (var_ctr == 0) {
                                    var_r28 = -1;
                                } else {
                                    goto loop_1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (var_r28 >= 0) {
        var_r31 = 0;
        var_r5_2 = 0;
loop_19:
        var_r7 = mPokemon__6cBingo;
        var_r6 = 0;
        temp_r4_2 = var_r5_2 + 1;
        var_ctr_2 = 2;
loop_20:
        if (temp_r4_2 == (u8) var_r7->unkC5) {

        } else {
            var_r6 += 1;
            if (temp_r4_2 == (u8) var_r7[1].unkC5) {

            } else {
                temp_r7 = (BingoPokemon *)((u8 *)&var_r7[1] + 0xC8);
                var_r6 += 1;
                if (temp_r4_2 == (u8) temp_r7->unkC5) {

                } else {
                    temp_r7_2 = (BingoPokemon *)((u8 *)temp_r7 + 0xC8);
                    var_r6 += 1;
                    if (temp_r4_2 == (u8) temp_r7_2->unkC5) {

                    } else {
                        temp_r7_3 = (BingoPokemon *)((u8 *)temp_r7_2 + 0xC8);
                        var_r6 += 1;
                        if (temp_r4_2 == (u8) temp_r7_3->unkC5) {

                        } else {
                            temp_r7_4 = (BingoPokemon *)((u8 *)temp_r7_3 + 0xC8);
                            var_r6 += 1;
                            if (temp_r4_2 == (u8) temp_r7_4->unkC5) {

                            } else {
                                temp_r7_5 = (BingoPokemon *)((u8 *)temp_r7_4 + 0xC8);
                                var_r6 += 1;
                                if (temp_r4_2 == (u8) temp_r7_5->unkC5) {

                                } else {
                                    var_r7 = (BingoPokemon *)((u8 *)temp_r7_5 + 0xC8);
                                    var_r6 += 1;
                                    var_ctr_2 -= 1;
                                    if (var_ctr_2 == 0) {
                                        var_r6 = -1;
                                    } else {
                                        goto loop_20;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (var_r6 != -1) {
            var_r5_2 += 1;
            if (var_r5_2 < 4) {
                goto loop_19;
            }
        }
        lbl_804EAA00 = 0;
        temp_r3 = arg0->unk144;
        if (temp_r3 < 9) {
            if (temp_r3 < 2) {
                if (temp_r3 < 0) {
                    goto block_44;
                }
                goto block_45;
            }
            goto block_44;
        }
        if (temp_r3 < 0xC) {
block_45:
            if (arg1 == (u8) arg0->unk12C) {
                arg0->unk14C = -0x100;
                lbl_804EAA00 = 6;
            } else {
                arg0->unk14C = 0xA0A0A000;
            }
        } else {
block_44:
            arg0->unk14C = -0x100;
        }
        var_r5_3 = 0;
        arg3->unk64 = (s32) (arg0->unk14C | arg2->unk93);
loop_49:
        var_r7_2 = mPokemon__6cBingo;
        var_r6_2 = 0;
        temp_r4_3 = var_r5_3 + 1;
        var_ctr_3 = 2;
loop_50:
        if (temp_r4_3 == (u8) var_r7_2->unkC5) {

        } else {
            var_r6_2 += 1;
            if (temp_r4_3 == (u8) var_r7_2[1].unkC5) {

            } else {
                temp_r7_6 = (BingoPokemon *)((u8 *)&var_r7_2[1] + 0xC8);
                var_r6_2 += 1;
                if (temp_r4_3 == (u8) temp_r7_6->unkC5) {

                } else {
                    temp_r7_7 = (BingoPokemon *)((u8 *)temp_r7_6 + 0xC8);
                    var_r6_2 += 1;
                    if (temp_r4_3 == (u8) temp_r7_7->unkC5) {

                    } else {
                        temp_r7_8 = (BingoPokemon *)((u8 *)temp_r7_7 + 0xC8);
                        var_r6_2 += 1;
                        if (temp_r4_3 == (u8) temp_r7_8->unkC5) {

                        } else {
                            temp_r7_9 = (BingoPokemon *)((u8 *)temp_r7_8 + 0xC8);
                            var_r6_2 += 1;
                            if (temp_r4_3 == (u8) temp_r7_9->unkC5) {

                            } else {
                                temp_r7_10 = (BingoPokemon *)((u8 *)temp_r7_9 + 0xC8);
                                var_r6_2 += 1;
                                if (temp_r4_3 == (u8) temp_r7_10->unkC5) {

                                } else {
                                    var_r7_2 = (BingoPokemon *)((u8 *)temp_r7_10 + 0xC8);
                                    var_r6_2 += 1;
                                    var_ctr_3 -= 1;
                                    if (var_ctr_3 == 0) {
                                        var_r6_2 = -1;
                                    } else {
                                        goto loop_50;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (var_r6_2 != -1) {
            var_r5_3 += 1;
            if (var_r5_3 < 4) {
                goto loop_49;
            }
        }
        if (arg1 == (u32) (var_r5_3 - 1)) {
            var_r3 = arg0;
            var_r4 = 0;
            var_ctr_4 = 0x10;
loop_70:
            if ((var_r28 == (s32) var_r3->cells[0].unk1) && ((u8) var_r3->cells[0].unk0 == 0)) {
                temp_f1 = arg0->cells[var_r4].unk4;
                if (temp_f1 > 0.2f) {
                    var_f1 = 3.0f;
                } else {
                    var_f1 = 5.0f * temp_f1;
                }
                if (var_f1 < 0.0f) {
                    var_f1 = 0.0f;
                }
                var_r31 = (s32) (-128.0f * var_f1);
            } else {
                var_r3 = (BingoState *)((u8 *)var_r3 + 8);
                var_r4 += 1;
                var_ctr_4 -= 1;
                if (var_ctr_4 != 0) {
                    goto loop_70;
                }
            }
        }
        temp_r31 = var_r31 + lbl_804EAA00;
        sp14 = 14.0f;
        sp10 = (f32) (temp_r31 + 0xE);
        temp_r25 = pokemonDataBiosGetStatusFaceMenuSpriteId(getPokemonDataPtr__7PokemonCFv(&mPokemon__6cBingo[var_r28]), 0);
        memcpy(&sp18, arg3, 0x78U);
        arg3->unk56 = 0x2A;
        arg3->unk54 = 0x2A;
        menuFaceDispFromID2(arg2, arg3, temp_r25, &sp10);
        memcpy(arg3, &sp18, 0x78U);
        sp8 = temp_r27;
        windowDrawSprite2(temp_r31, 0, 0xB8, 0x46, arg0->unk14C | arg2->unk93, arg2, 0x27AU, 0, sp8);
        temp_r5_6 = &mPokemon__6cBingo[var_r28];
        msgctrlSetValue(0x34, temp_r5_6->unkC4 + temp_r5_6->unkC6);
        GSmsgPrint2(temp_r27, temp_r31 + 0x4F, 0x2D, arg0->unk14C | arg2->unk93, 0x4271U);
        msgctrlSetValue(0x37, GSmsgGetGSchar(0xDAD6U));
        GSmsgPrintRect(temp_r27, temp_r31 + 0x3F, 0x19, arg3->unk54, arg3->unk56, arg0->unk14C | arg2->unk93, 0x4278);
        temp_r28 = &mPokemon__6cBingo[var_r28];
        msgctrlSetValue(0x37, pokemonGetStatus(temp_r28, 0, 0x77, 0));
        GSmsgPrintRect(temp_r27, temp_r31 + 0x40, 9, arg3->unk54, arg3->unk56, arg0->unk14C | arg2->unk93, 0x4279);
        temp_r3_2 = menuSubGetPokemonSexForDisp(temp_r28);
        switch ((s32) temp_r3_2) {                  /* irregular */
        case 0:
            var_r3_2 = 0x9C5;
            break;
        case 1:
            var_r3_2 = 0x9C6;
            break;
        default:
            var_r3_2 = 0;
            break;
        }
        if (var_r3_2 != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(var_r3_2));
            GSmsgPrint2(temp_r27, temp_r31 + 0xA0, 9, arg0->unk14C | arg2->unk93, 0x4278U);
        }
        temp_r3_3 = zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(temp_r28));
        temp_r6 = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(temp_r3_3));
        if (temp_r3_3 != 0) {
            sp8 = temp_r27;
            windowDrawSprite2((s16) (temp_r31 + 0x66), 0x19, *(s16 *)((u8 *)temp_r6 + 4), temp_r6->unk6, arg0->unk14C | arg2->unk93, arg2, temp_r3_3, 0, sp8);
            if (temp_r3_3 != zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(temp_r28))) {
                temp_r25_2 = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(temp_r28))));
                temp_r3_4 = zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(temp_r28));
                sp8 = temp_r27;
                windowDrawSprite2((s16) (temp_r31 + 0x66), 0x2D, *(s16 *)((u8 *)temp_r25_2 + 4), temp_r25_2->unk6, arg0->unk14C | arg2->unk93, arg2, temp_r3_4, 0, sp8);
            }
        }
    }
}

// Keep the cell index separate from the record offset, as in the original accessors.
u8 isChgBingoLine__6cBingoFl(BingoState *arg0, s32 arg1) {
    u8 current;
    if (arg1 < 0) {
        s32 line;
        for (line = 0; line < 10; line++) {
            current = bingoLineClear(arg0, line);
            if (arg0->lineState[line] != current) return 1;
        }
        goto noChange;
    }
    current = bingoLineClear(arg0, arg1);
    if (arg0->lineState[arg1] != current) {
        if (arg0->lineEffects[arg1] == 0) {
            arg0->lineEffects[arg1] = 1;
            FlashSystemSetNowFrame(0x1F583000U, 0U);
            if ((u32)arg1 < 4) FlashSystemSetNowFrame(0x1ECC3000U, 0U);
            else if ((u32)arg1 < 8) FlashSystemSetNowFrame(0x1ECB3000U, 0U);
            else if ((u32)arg1 == 8) FlashSystemSetNowFrame(0x1ECE3000U, 0U);
            else if ((u32)arg1 == 9) FlashSystemSetNowFrame(0x1ECD3000U, 0U);
        }
        return 1;
    }
noChange:
    return 0;
}

void makeRandomSheet__6cBingoFv(BingoState *arg0) {
    u8 order[16] = {0,1,2,3,7,11,15,14,13,12,8,4,5,6,10,9};
    s32 var_r30;
    s32 var_r30b;
    s32 var_r31_2;
    BingoState *var_r31;
    f32 temp_f1;
    f32 temp_f28;
    s32 temp_r0_2;
    s32 temp_r3;
    u8 temp_r4;
    u8 temp_r4_2;
    u8 temp_r5;
    u8 temp_r6;
    u8 temp_r7;

    for (var_r30 = 0; var_r30 < 16; var_r30++) {
        arg0->backup[var_r30].unk0 = arg0->cells[var_r30].unk0;
        arg0->backup[var_r30].unk1 = arg0->cells[var_r30].unk1;
        arg0->backup[var_r30].unk2 = arg0->cells[var_r30].unk2;
        arg0->backup[var_r30].unk3 = arg0->cells[var_r30].unk3;
        arg0->backup[var_r30].unk4 = arg0->cells[var_r30].unk4;
        arg0->backup[var_r30].unk4 = -1.0f;
    }
    var_r31 = arg0;
    for (var_r30b = 0; var_r30b < 16; var_r30b++) {
        temp_r3 = (u16)HSD_Rand();
        temp_r4 = var_r31->backup[0].unk0;
        temp_r5 = var_r31->backup[0].unk1;
        temp_r6 = var_r31->backup[0].unk2;
        temp_r7 = var_r31->backup[0].unk3;
        temp_f1 = var_r31->backup[0].unk4;
        temp_r0_2 = temp_r3 % 16;
        var_r31->backup[0].unk0 = arg0->backup[temp_r0_2].unk0;
        var_r31->backup[0].unk1 = arg0->backup[temp_r0_2].unk1;
        var_r31->backup[0].unk2 = arg0->backup[temp_r0_2].unk2;
        var_r31->backup[0].unk3 = arg0->backup[temp_r0_2].unk3;
        var_r31->backup[0].unk4 = arg0->backup[temp_r0_2].unk4;
        var_r31 = (BingoState *)((u8 *)var_r31 + 8);
        arg0->backup[temp_r0_2].unk0 = temp_r4;
        arg0->backup[temp_r0_2].unk1 = temp_r5;
        arg0->backup[temp_r0_2].unk2 = temp_r6;
        arg0->backup[temp_r0_2].unk3 = temp_r7;
        arg0->backup[temp_r0_2].unk4 = temp_f1;
    }
    arg0->unk144 = 0xF;
    arg0->unk124 = -1;
    for (var_r31_2 = 0; var_r31_2 < 16; var_r31_2 += 2) {
        arg0->backup[order[var_r31_2]].unk4 = 1.0f;
        while (0.0f < arg0->backup[order[var_r31_2]].unk4) {
            temp_r4_2 = order[var_r31_2];
            temp_f28 = arg0->backup[temp_r4_2].unk4;
            GSthreadSwitch();
            if (0.5f < temp_f28) {
                if (arg0->backup[order[var_r31_2]].unk4 <= 0.5f) {
                    arg0->backup[order[var_r31_2 + 1]].unk4 = 1.0f;
                }
            }
        }
    }
    while (0.0f < arg0->backup[order[15]].unk4) GSthreadSwitch();
    arg0->unk144 = 0xE;
    arg0->unk124 = -1;
}

void SetupSheet__6cBingoFUl(BingoState *arg0, u32 arg1) {
    u32 sp8;
    BingoCell *temp_r3_2;
    BingoPokemon *temp_r3_3;
    BingoState *var_r31;
    s32 temp_r27;
    s32 temp_r27_2;
    s32 temp_r28;
    s32 temp_r28_2;
    s32 var_r27;
    u32 temp_r4;
    u32 var_r28;
    u32 var_r30;
    u32 var_r30_2;
    u8 temp_r0;
    u8 temp_r3;

    var_r28 = arg1;
    var_r27 = 0;
    switch ((s32) var_r28) {                        /* irregular */
    case 9:
        var_r27 = 1;
        /* fallthrough */
    case 6:
        var_r27 += 1;
        /* fallthrough */
    case 3:
        if (getClearLv__10bingo_biosFv(arg0) < (u32) (var_r27 + 1)) {
            var_r28 = 0xA;
        }
        break;
    }
    setStaticNo__10bingo_biosFUc((u8) var_r28);
    arg0->unk4 = getStaticSheet__10bingo_biosFv();
    arg0->unk130 = 0;
    arg0->unk129 = getBall__10bingo_biosFP14BINGO_DATA_dd_(arg0, arg0->unk4);
    arg0->unk121 = 0;
    arg0->unk148 = 1;
    setStaticBall__10bingo_biosFUc(arg0->unk129);
    memset(arg0->cells, 0, 0x80U);
    for (var_r30 = 0; var_r30 < 3; var_r30++) {
        temp_r3 = getGridPos__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, var_r30);
        sp8 = (u32) temp_r3;
        temp_r3_2 = &arg0->cells[temp_r3];
        temp_r3_2->unk0 = 1;
        temp_r3_2->unk1 = (u8) var_r30;
        temp_r3_2->unk2 = 0;
    }
    temp_r28 = gamedataGetStatus(0, 1);
    temp_r27 = getLevel__10bingo_biosFP14BINGO_DATA_dd_(arg0, arg0->unk4);
    pokemonCreate(mPokemon__6cBingo, getPanelNo__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, 0U), temp_r27, temp_r28);
    mPokemon__6cBingo->unkC4 = 2;
    mPokemon__6cBingo->unkC5 = 1;
    mPokemon__6cBingo->unkC6 = 0;
    sp8 = 0;
    for (var_r30_2 = 0; var_r30_2 < 0x10U; var_r30_2++) {
        if (arg0->cells[var_r30_2].unk0 == 0) {
            temp_r4 = sp8 + 1;
            sp8 = temp_r4;
            arg0->cells[var_r30_2].unk0 = 0;
            arg0->cells[var_r30_2].unk1 = (u8) temp_r4;
            arg0->cells[var_r30_2].unk2 = 0;
            getPanelNo__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, sp8);
            temp_r27_2 = gamedataGetStatus(0, 1);
            temp_r28_2 = getLevel__10bingo_biosFP14BINGO_DATA_dd_(arg0, arg0->unk4);
            pokemonCreate(&mPokemon__6cBingo[sp8], getPanelNo__10bingo_biosFP14BINGO_DATA_dd_Ul(arg0, arg0->unk4, sp8), temp_r28_2, temp_r27_2);
            temp_r3_3 = &mPokemon__6cBingo[temp_r4];
            temp_r3_3->unkC6 = 0;
            temp_r3_3->unkC4 = 0;
            temp_r3_3->unkC5 = 0;
        }
    }
    sp8 = 0;
    arg0->unk122 = 0;
    menuFaceLoad(0, (BingoPokemon *(*)(u32 *)) loadPkmFace__6cBingoFPv, (s32 *) &sp8);
}

BingoPokemon *loadPkmFace__6cBingoFPv(u32 *arg0) {
    BingoPokemon *var_r5;
    u32 temp_r0;

    temp_r0 = *arg0;
    var_r5 = 0;
    if (temp_r0 < 0xEU) {
        var_r5 = &mPokemon__6cBingo[temp_r0];
    }
    *arg0 = *(volatile u32 *)arg0 + 1;
    return var_r5;
}

void ResetSheet__6cBingoFUl(BingoState *arg0, u32 arg1) {
    s32 i;

    arg0->unk108 = 0;
    arg0->unk130 = 0;
    arg0->unk12C = 0;
    arg0->unk129 = getBall__10bingo_biosFP14BINGO_DATA_dd_(arg0, arg0->unk4);
    arg0->unk148 = 1;
    arg0->unk121 = 0;
    setStaticBall__10bingo_biosFUc(arg0->unk129);
    for (i = 0; i < 0x10; i++) {
        arg0->cells[i].unk2 = 0;
    }
    i = 1;
    mPokemon__6cBingo->unkC4 = 2;
    mPokemon__6cBingo->unkC5 = i;
    mPokemon__6cBingo->unkC6 = 0;
    for (; i < 0xE; i++) {
        mPokemon__6cBingo[i].unkC6 = 0;
        mPokemon__6cBingo[i].unkC4 = 0;
        mPokemon__6cBingo[i].unkC5 = 0;
    }
}
#ifdef __cplusplus
}
#endif
