#include <dolphin/types.h>
extern "C" {
typedef struct FIGHT_TRAINER FIGHT_TRAINER; typedef struct FightOutPokemon FightOutPokemon; typedef struct FightPokemon FightPokemon; typedef struct Pokemon Pokemon; typedef struct FightSide FightSide;
typedef struct FightAiAllWazaValid {
    FightOutPokemon *attacker[2];
    FightOutPokemon *defender[2];
    u16 wazaId[2];
    u8 menu[2], kind[2], targetKind[2], flag1a, reserved1b;
    u16 values[2][2];
    u8 flags24[2], unobserved26[6];
} FightAiAllWazaValid;
u16 HSD_Rand(void);
u32 fightFloor_GetFightType(void *);
FightSide * fightTargetGetPtr(u8, FIGHT_TRAINER *, u8);
u8 fightSideIsJoutaiDataId(FightSide *, u16);
void fightAi_InitAllWazaValidSub(FightAiAllWazaValid *);
void fightAi_AllWazaValid_AddComboList(FIGHT_TRAINER *, FightAiAllWazaValid *, u8 *, u8, u16, u8, u16);
void fightAi_AllWazaValid_DelListFromSpeed(FIGHT_TRAINER *, FightAiAllWazaValid *, u8 *, u16, u8);
void fightAi_AllWazaValid_DelComboList(FIGHT_TRAINER *, FightAiAllWazaValid *, u8 *, u8, u16, u8, u16, u8);
s16 fightAiCombo_GetValidValue(FightOutPokemon **, u16, FightOutPokemon **, u16);
s16 fightAiCombo_GetAllWazaValueTable(FightAiAllWazaValid *, s16, FIGHT_TRAINER *, FightOutPokemon **, FightOutPokemon **, s8);
s16 fightAiCombo_GetAllWazaMaxValueTable(FightAiAllWazaValid *, u8, s16, FIGHT_TRAINER *, FightOutPokemon **, FightOutPokemon **, FightAiAllWazaValid *, s8);
u8 fightAi_CopyAllWazaValidTable(FightAiAllWazaValid *, FightAiAllWazaValid *);
void setComboFuncId__15FightOutPokemonFUc(FightOutPokemon *, u8);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightAi_GetWazaHaveFlag(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightFloorGetNowTenkouDataId(void *, u8);
s32 fightTrainerAiAddValueByAddsubDataId(s32, FIGHT_TRAINER *, u16);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon *);
s32 fightOutPokemonGetNowHpPercentage(FightOutPokemon *);
u16 fightTrainerAiGetWazaZokuseiDataId(FIGHT_TRAINER *, u16, FightOutPokemon *);
u16 wazaDB_GetZokuseiDataId(u16);
u8 wazaIsWazaTypeId(u16, u16);
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void *, FightOutPokemon *, u8);
void fightAi_CreateAction_FromAllWazaValid(FIGHT_TRAINER *, FightAiAllWazaValid *);
u8 fightFloorCmpfightOutPokemonNimbleness(void *, FightOutPokemon *, FightOutPokemon *, u8);
s32 fightAi_getAnotherPokeNo(u8);
u8 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon *);
u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon *);
u16 fightTrainer_GetEnemyExpectWazaData(FIGHT_TRAINER *, s16, u8);
u16 fightTrainer_GetEnemyStoreWazaData(FIGHT_TRAINER *, s16, u8);
FightPokemon * fightOutPokemon_GetFightPokemonPtr(FightOutPokemon *);
s16 fightPokemon_GetEntryId(FightPokemon *);
u16 fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *, FightOutPokemon *);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u8);
u16 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16, u8);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void *);
u8 fightFloor_GetFightKindDorobouFlag(void *);
u8 fightFloor_GetFightTypeEntryPokemonNum(void *);
u8 fightFloor_GetFightTypeTrainerNum(void *);
u16 fightSideGetHikaeFightPokemonNum(FightSide *, u8, u8, u8);
u8 fightTrainerAiIsFightOutPokemonAllAbiCntTakai(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonAvoidCntHikui(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonNokoriHpHikui(FIGHT_TRAINER *, FightOutPokemon *);
u8 fightTrainerAiIsFightOutPokemonJoutaiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonTokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
u8 fightTrainerAiIsFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u16);
s32 fightAiCombo_Darkdown_PhyatkIryoku_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Darkmist_Darkend_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Darkmist_Darkhold_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Darkmist_Darkpanic_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Darkweather_DarkIryoku_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Batontatti_Zikoanzi_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Batontatti_Nekodamasi_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Torikku_Kodawarihatimaki_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Migawari_Kisikaisei_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Daibakuhatu_Horobinouta_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Hakaikousen_Hoeru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Ibaru_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Horobinouta_Irekae2_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Honoo_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Dokudoku_Karagenki_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Horobinouta_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Konoyubitomare_Kiaipanti_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Konoyubitomare_StatusUp_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Sukirusuwappu_Irekae_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Sukirusuwappu_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Sunaarasi_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amagoi_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nihonbare_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nihonbare_Asanohizasi_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amaikaori_Hubuki_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amaikaori_Hubuki_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Konran_DefDown_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Konran_DefDown_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Makibisi_Hoeru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_StatusUp_Batontatti_1(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Daibakuhatu_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Zisin_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Hurahuradansu_Irekae_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Daibakuhatu_Daibakuhatu_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Haradaiko_Zikoanzi_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Zisin_Mamoru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Tedasuke_Iryoku_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Daibakuhatu_Koraeru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nemurase_Yumekui_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Kinokonohousi_Kiaipanti_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_DarkWeather_Whezaabooru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Arare_Whezaabooru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Sunaarasi_Whezaabooru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amagoi_Whezaabooru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nihonbare_Whezaabooru_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amagoi_Mizu_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Amagoi_Kaminari_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nihonbare_Honoo_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_Nihonbare_Sooraabiimu_2(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
s32 fightAiCombo_null(FIGHT_TRAINER *, FightOutPokemon **, u16, FightOutPokemon **, u16, FightAiAllWazaValid *, u8);
extern u8 ai_allwaza_valid_work;

s32 fightAiCombo_Darkdown_PhyatkIryoku_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value26_u8;
    u8 value25_u8;
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    FightOutPokemon *temp_r4;
    FightSide *temp_r3;
    s16 temp_r23_2;
    s16 var_r22;
    s16 var_r24;
    s32 temp_r23;
    u16 temp_r3_2;
    u8 temp_r24;
    u8 temp_r4_2;
    u8 var_r20;
    u8 var_r21;
    u8 var_r23;

    sp8 = 0;
    temp_r24 = fightFloor_GetFightType(0);
    var_r21 = 0;
    var_r23 = 0;
    while (var_r23 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r23]);
        var_r23 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, temp_r24);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    value26_u8 = 0;
    value25_u8 = 0;
    while ((s32) value25_u8 < (s32) arg4) {
        temp_r23 = (value25_u8 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r23);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r23), 0x49U) < 1U)) {
            value26_u8 += 1;
        }
        value25_u8 += 1;
        continue;
    }
    if (value26_u8 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x173U, 2U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x173U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r24 = 0;
    temp_r23_2 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    value26_u8 = 0;
    while (value26_u8 < sp8) {
        temp_r27 = &sp4C[value26_u8];
        value25_u8 = 0;
        var_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23_2, arg0, arg1, arg3, -1);
        while (value25_u8 < (u8) ai_allwaza_valid_work) {
            temp_r3_2 = *(u16 *)((u8 *)temp_r27 + (((value25_u8 * 2) & 0x1FE) + 0x10));
            if ((temp_r3_2 != 0x173) && (wazaDB_GetZokuseiDataId(temp_r3_2) != 1)) {
                var_r22 = 0;
            }
            value25_u8 += 1;
            continue;
        }
        if (var_r24 < var_r22) {
            spC[0] = value26_u8;
            var_r24 = var_r22;
            var_r21 = 1;
        } else if ((var_r24 == var_r22) && (var_r24 > 0)) {
            spC[var_r21] = value26_u8;
            var_r21 += 1;
        }
        value26_u8 += 1;
        continue;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r21]]);
    temp_r4_2 = HSD_Rand() % 100;
    if ((var_r24 != 0) && ((s32) (var_r24 + arg6) > (s32) temp_r4_2)) {
        var_r20 = 0;
        while ((s32) var_r20 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r20 * 4) & 0x3FC)), 0U);
            var_r20 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkend_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r4;
    FightSide *temp_r3;
    s16 temp_r3_2;
    s32 temp_r24;
        u8 var_r21;
    u8 var_r22;

    sp8 = 0;
    var_r21 = fightFloor_GetFightType(0);
    var_r22 = 0;
    while (var_r22 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r22]);
        var_r22 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, var_r21);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    var_r21 = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) arg4) {
        temp_r24 = (var_r22 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U)) {
            var_r21 += 1;
        }
        var_r22 += 1;
        continue;
    }
    if (var_r21 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x167U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3_2 > 0) && ((s32) (temp_r3_2 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r22 = 0;
        while ((s32) var_r22 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r22 * 4) & 0x3FC)), 0U);
            var_r22 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkhold_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r4;
    FightSide *temp_r3;
    s16 temp_r3_2;
    s32 temp_r24;
        u8 var_r21;
    u8 var_r22;

    sp8 = 0;
    var_r21 = fightFloor_GetFightType(0);
    var_r22 = 0;
    while (var_r22 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r22]);
        var_r22 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, var_r21);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    var_r21 = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) arg4) {
        temp_r24 = (var_r22 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U)) {
            var_r21 += 1;
        }
        var_r22 += 1;
        continue;
    }
    if (var_r21 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x170U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3_2 > 0) && ((s32) (temp_r3_2 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r22 = 0;
        while ((s32) var_r22 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r22 * 4) & 0x3FC)), 0U);
            var_r22 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Darkmist_Darkpanic_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r4;
    FightSide *temp_r21_2;
    FightSide *temp_r3;
    s16 temp_r3_2;
    s32 temp_r24;
    u8 var_r24;

    sp8 = 0;
    value21_u8 = fightFloor_GetFightType(0);
    value22_u8 = 0;
    while (value22_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value22_u8]);
        value22_u8 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, value21_u8);
    temp_r21_2 = temp_r3;
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r21_2, 0x4BU) == 1) {
        return 0;
    }
    value21_u8 = 0;
    value22_u8 = 0;
    while ((s32) value22_u8 < (s32) arg4) {
        temp_r24 = (value22_u8 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x14U) < 1U)) {
            value21_u8 += 1;
        }
        value22_u8 += 1;
        continue;
    }
    if (value21_u8 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x172U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3_2 > 0) && ((s32) (temp_r3_2 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r24 = 0;
        while ((s32) var_r24 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r24 * 4) & 0x3FC)), 0U);
            var_r24 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}





s32 fightAiCombo_Konoyubitomare_Kiaipanti_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    u8 var_r28;
    u8 var_r30;

    var_r28 = 0;
    sp8 = 0;
    while (var_r28 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r28]);
        var_r28 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x10AU, 1U, 0x108U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r30 = 0;
        while ((s32) var_r30 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r30 * 4) & 0x3FC)), 0U);
            var_r30 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}







s32 fightAiCombo_Makibisi_Hoeru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightSide *temp_r21;
    FightSide *temp_r3;
    s16 temp_r3_2;
    u8 temp_r20;
    u8 temp_r29;
    u8 temp_r30;
    u8 temp_r31;
    u8 var_r21;
    u8 var_r24;

    sp8 = 0;
    temp_r20 = fightFloor_GetFightType(0);
    temp_r31 = fightFloor_GetFightTypeTrainerNum(0);
    temp_r30 = fightFloor_GetFightTypeEntryPokemonNum(0);
    temp_r29 = fightFloor_GetFightTypeFightoutPokemonNum(0);
    var_r21 = 0;
    while (var_r21 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r21]);
        var_r21 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, temp_r20);
    temp_r21 = temp_r3;
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4AU) == 1) {
        return 0;
    }
    if (fightSideGetHikaeFightPokemonNum(temp_r21, temp_r31, temp_r30, temp_r29) == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xBFU, 1U, 0x2EU);
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xBFU, 1U, 0x12U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xBFU, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3_2 > 0) && ((s32) (temp_r3_2 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r24 = 0;
        while ((s32) var_r24 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r24 * 4) & 0x3FC)), 0U);
            var_r24 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}





s32 fightAiCombo_Kinokonohousi_Kiaipanti_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value23_u8;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r4;
    s16 temp_r3;
    u8 var_r22;
    u8 var_r25;

    value23_u8 = 0;
    sp8 = 0;
    while (value23_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value23_u8]);
        value23_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r22 = 0;
    value23_u8 = 0;
    while ((s32) value23_u8 < (s32) arg4) {
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + ((value23_u8 * 4) & 0x3FC));
        if ((temp_r4 != 0) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 8U) == 0)) {
            var_r22 += 1;
        }
        value23_u8 += 1;
        continue;
    }
    if (var_r22 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x93U, 1U, 0x108U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
        var_r25 = 0;
        while ((s32) var_r25 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r25 * 4) & 0x3FC)), 0U);
            var_r25 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Arare_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x102U, 1U, 0x137U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x102U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + ((value22_u8 * 4) & 0x3FC));
                if ((value4_FightOutPokemonPtr != 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xFU) == 1)) {
                    var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ADU);
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 4);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Sunaarasi_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xC9U, 1U, 0x137U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xC9U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 8U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 4U) == 1)) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ABU);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 8U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ACU);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 3);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Amagoi_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 2) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 1U, 0x137U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xBU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A8U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x2CU) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A9U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x21U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2AAU);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Nihonbare_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 1U, 0x137U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A6U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A7U);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Amagoi_Mizu_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 2) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 3U, 0xBU);
            fightAi_AllWazaValid_DelComboList(arg0, spC, &sp8, 1U, 0xF0U, 2U, 1U, 1U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xBU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A3U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x2CU) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A4U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x21U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A5U);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Amagoi_Kaminari_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 2) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 1U, 0x57U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xBU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A0U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x2CU) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A1U);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x21U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A2U);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Nihonbare_Honoo_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 3U, 0xAU);
            fightAi_AllWazaValid_DelComboList(arg0, spC, &sp8, 1U, 0xF1U, 2U, 1U, 1U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29EU);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29FU);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 2))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_Nihonbare_Sooraabiimu_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 value22_u8;
    u8 value21_u8;
    s32 value22_s32;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s16 var_r21_4;
    s32 temp_r25;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
        continue;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    value21_u8 = 0;
loop_15:
    if ((s32) value21_u8 >= (s32) arg2) {
        value21_u8 = 0;
loop_22:
        if ((s32) value21_u8 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 1U, 0x4CU);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            value22_u8 = 0;
            var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) value22_u8 < (s32) arg4) {
                temp_r25 = (value22_u8 * 4) & 0x3FC;
                value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
                if (value4_FightOutPokemonPtr != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29CU);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                        var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29DU);
                    }
                }
                value22_u8 += 1;
                continue;
            }
            temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if ((temp_r3 > 0) && ((s32) (temp_r3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                value22_u8 = 0;
                while ((s32) value22_u8 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value22_u8 * 4) & 0x3FC)), 0U);
                    value22_u8 += 1;
                    continue;
                }
                return 1;
            }
            return 0;
        }
        value22_s32 = (value21_u8 * 4) & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + value22_s32);
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + value22_s32), 0xDU) >= 1U))) {
            return 0;
        }
        value21_u8 += 1;
        goto loop_22;
    }
    value22_s32 = (value21_u8 * 4) & 0x3FC;
    value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg1 + value22_s32);
    if ((value4_FightOutPokemonPtr != 0) && ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, value4_FightOutPokemonPtr, 0x4DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg1 + value22_s32), 0xDU) == 1))) {
        return 0;
    }
    value21_u8 += 1;
    goto loop_15;
}

s32 fightAiCombo_null(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    return 0;
}




s32 fightAi_getAnotherPokeNo(u8 index) { if (index == 0) return 1; return index == 1 ? 0 : -1; }

u32 fightOutPokemonMaxHpWaruValue(FightOutPokemon *, u16);
u32 fightOutPokemonNowHpWaruValue(FightOutPokemon *, u16);
u16 fightTrainer_GetFightTrainerDataId(FIGHT_TRAINER *);
s32 fightTrainerAiDB_GetWazaAvgValue(u16);
u16 fightFloorGetFightTrainerFightPokemonPtrAry(void *, FIGHT_TRAINER *, FightPokemon **, u8, u8);
Pokemon *fightPokemonGetPokemonPtr(FightPokemon *);
u16 fightTrainerAiGetFightPokemonPokemonDataId(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiNormal(FIGHT_TRAINER *, FightPokemon *);
u8 fightTrainerAiIsFightPokemonJoutaiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonTokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
u8 fightTrainerAiIsFightPokemonZokuseiDataId(FIGHT_TRAINER *, FightPokemon *, u16);
FightPokemon *fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon *);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon *);
s16 fightSideGetCountAsJoutaiDataId(FightSide *, u16);
u16 fightTrainerAiCheckOumu(FIGHT_TRAINER *, FightOutPokemon *);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightOutPokemon *, u8);
FIGHT_TRAINER *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void *, FightOutPokemon *);
FightPokemon *fightTrainerSearchIrekaeFightPokemon(FIGHT_TRAINER *, u16 *);
u16 tikeiDataBiosGetFightKoukaId(u8);
u8 fightAi_GetTokuseiHaveFlag(FIGHT_TRAINER *, FightOutPokemon *, u16);
Pokemon *fightOutPokemonGetPokemonPtr(FightOutPokemon *);
u8 pokemonIsDarkPokemon(Pokemon *);
u8 wazaCheckDarkWaza(u16);
FightPokemon *getFightPokemonPtr__15FightOutPokemonFv(FightOutPokemon *);
u8 _fightTrainerAiWazaValueAbiCntCheck__FP13FIGHT_TRAINERP15FightOutPokemonUcUc(FIGHT_TRAINER *, FightOutPokemon *, u8, u8);
u8 _fightTrainerAiWazaValueIsFightOutPokemonNeoki__FP13FIGHT_TRAINERP15FightOutPokemon(FIGHT_TRAINER *, FightOutPokemon *);
u8 _fightTrainerAiWazaValueKuroikiriSubAbiCntCheck__FP13FIGHT_TRAINERPP15FightOutPokemonUsUcUc(FIGHT_TRAINER *, FightOutPokemon **, u16, u8, u8);
u8 _fightTrainerAiWazaValueIsAllyHaveWazaDataId__FP13FIGHT_TRAINERP15FightOutPokemonUs(FIGHT_TRAINER *, FightOutPokemon *, u16);

s32 fightAiCombo_Darkweather_DarkIryoku_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r24;
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r4_3;
    s16 var_r19_3;
    s16 var_r20;
    s16 var_r21_2;
    s32 temp_r21;
    s32 temp_r21_2;
    u16 temp_r3_3;
    u8 temp_r4;
    u8 var_r19;
    u8 var_r19_2;
    u8 var_r19_4;
    u8 var_r21;
    u8 var_r22;
    u8 var_r22_2;
    u8 var_r22_3;
    u8 var_r23;
    u8 var_r31;

    var_r31 = 0;
    var_r21 = 0;
    sp8 = 0;
    while (var_r21 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r21]);
        var_r21 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 5) {
        return 0;
    }
    var_r22 = 0;
loop_15:
    if ((s32) var_r22 >= (s32) arg2) {
        var_r22_2 = 0;
loop_22:
        if ((s32) var_r22_2 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x16FU, 2U, 1U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x16FU, 1U);
            if (sp8 == 0) {
                return 0;
            }
            var_r19 = 0;
            var_r20 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) var_r19 < (s32) arg2) {
                temp_r3 = *(FightOutPokemon **)((u8 *)arg1 + ((var_r19 * 4) & 0x3FC));
                if ((temp_r3 != 0) && (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3)) == 1)) {
                    var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2C5U);
                }
                var_r19 += 1;
                continue;

                break;
            }
            var_r19_2 = 0;
            while ((s32) var_r19_2 < (s32) arg4) {
                temp_r3_2 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r19_2 * 4) & 0x3FC));
                if ((temp_r3_2 != 0) && (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3_2)) == 1)) {
                    var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2C4U);
                }
                var_r19_2 += 1;
                continue;

                break;
            }
            var_r21_2 = 0;
            var_r23 = 0;
            while (var_r23 < sp8) {
                temp_r24 = &sp4C[var_r23];
                var_r22_3 = 0;
                var_r19_3 = fightAiCombo_GetAllWazaValueTable(temp_r24, var_r20, arg0, arg1, arg3, -1);
                while (var_r22_3 < (u8) ai_allwaza_valid_work) {
                    temp_r3_3 = *(u16 *)((u8 *)temp_r24 + (((var_r22_3 * 2) & 0x1FE) + 0x10));
                    if ((temp_r3_3 != 0x16F) && (wazaCheckDarkWaza(temp_r3_3) == 0)) {
                        var_r19_3 = 0;
                    }
                    var_r22_3 += 1;
                    continue;

                    break;
                }
                if (var_r21_2 < var_r19_3) {
                    spC[0] = var_r23;
                    var_r21_2 = var_r19_3;
                    var_r31 = 1;
                } else if ((var_r21_2 == var_r19_3) && (var_r21_2 > 0)) {
                    spC[var_r31] = var_r23;
                    var_r31 += 1;
                }
                var_r23 += 1;
                continue;

                break;
            }
            fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
            temp_r4 = HSD_Rand() % 100;
            if ((var_r21_2 != 0) && ((s32) (var_r21_2 + arg6) > (s32) temp_r4)) {
                var_r19_4 = 0;
                while ((s32) var_r19_4 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r19_4 * 4) & 0x3FC)), 0U);
                    var_r19_4 += 1;
                    continue;

                    break;
                }
                return 1;
            }
            return 0;
        }
        temp_r21 = (var_r22_2 * 4) & 0x3FC;
        temp_r4_2 = *(FightOutPokemon **)((u8 *)arg3 + temp_r21);
        if ((temp_r4_2 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r21), 0xDU) >= 1U))) {
            return 0;
        }
        var_r22_2 += 1;
        goto loop_22;
    }
    temp_r21_2 = (var_r22 * 4) & 0x3FC;
    temp_r4_3 = *(FightOutPokemon **)((u8 *)arg1 + temp_r21_2);
    if ((temp_r4_3 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4_3, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r21_2), 0xDU) == 2))) {
        return 0;
    }
    var_r22 += 1;
    goto loop_15;
}

s32 fightAiCombo_Torikku_Kodawarihatimaki_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    s16 temp_r22;
    s16 temp_r23;
    s16 var_r24;
    u8 temp_r3;
    u8 var_r21;
    u8 var_r22;
    u8 var_r25;
    u8 var_r26;

    sp8 = 0;
    temp_r23 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    if (fightFloor_GetFightKindDorobouFlag(0) == 1) {
        return 0;
    }
    var_r25 = 0;
loop_20:
    if ((s32) var_r25 >= (s32) arg2) {
        return 0;
    }
    var_r22 = 0;
    while (var_r22 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r22]);
        var_r22 += 1;
        continue;

        break;
    }
    sp8 = 0;
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x10FU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    var_r24 = 0;
    var_r26 = 0;
    while (var_r26 < sp8) {
        temp_r27 = &sp4C[var_r26];
        temp_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23, arg0, arg1, arg3, -1);
        temp_r27->attacker[fightAi_getAnotherPokeNo(var_r25)] = 0;
        if (var_r24 < temp_r22) {
            spC[0] = var_r26;
            var_r24 = temp_r22;
            var_r21 = 1;
        } else if ((var_r24 == temp_r22) && (var_r24 > 0)) {
            spC[var_r21] = var_r26;
            var_r21 += 1;
        }
        var_r26 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r21]]);
    temp_r3 = HSD_Rand() % 100;
    if ((var_r24 != 0) && ((s32) (var_r24 + arg6) > (s32) temp_r3)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r25 * 4) & 0x3FC)), 0U);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r25 += 1;
    goto loop_20;
}

s32 fightAiCombo_Daibakuhatu_Horobinouta_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    FightOutPokemon *temp_r4_2;
    FightOutPokemon *temp_r4_3;
    s16 temp_r23;
    s16 var_r22;
    s16 var_r24_2;
    u8 temp_r4;
    u8 var_r18;
    u8 var_r18_2;
    u8 var_r18_3;
    u8 var_r21;
    u8 var_r24;
    u8 var_r25;
    u8 var_r26;

    var_r18 = 0;
    sp8 = 0;
    while (var_r18 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
        var_r18 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r18_2 = 0;
loop_12:
    if ((s32) var_r18_2 >= (s32) arg2) {
        var_r24 = 0;
loop_18:
        if ((s32) var_r24 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x99U, 1U, 0xC3U);
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0xC3U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xC3U, 0U);
            if (sp8 == 0) {
                return 0;
            }
            var_r24_2 = 0;
            temp_r23 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            var_r26 = 0;
            while (var_r26 < sp8) {
                temp_r27 = &sp4C[var_r26];
                var_r25 = 0;
                var_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23, arg0, arg1, arg3, -1);
                while (var_r25 < (u8) ai_allwaza_valid_work) {
                    if (((u16) *(u16 *)((u8 *)temp_r27 + (((var_r25 * 2) & 0x1FE) + 0x10)) == 0xC3) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r27->attacker[var_r25], 7U) == 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r27->attacker[var_r25], 5U) == 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r27->attacker[var_r25], 8U) == 0)) {
                        var_r22 = 0;
                    }
                    var_r25 += 1;
                    continue;

                    break;
                }
                if (var_r24_2 < var_r22) {
                    spC[0] = var_r26;
                    var_r24_2 = var_r22;
                    var_r21 = 1;
                } else if ((var_r24_2 == var_r22) && (var_r24_2 > 0)) {
                    spC[var_r21] = var_r26;
                    var_r21 += 1;
                }
                var_r26 += 1;
                continue;

                break;
            }
            fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r21]]);
            temp_r4 = HSD_Rand() % 100;
            if ((var_r24_2 != 0) && ((s32) (var_r24_2 + arg6) > (s32) temp_r4)) {
                var_r18_3 = 0;
                while ((s32) var_r18_3 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r18_3 * 4) & 0x3FC)), 0U);
                    var_r18_3 += 1;
                    continue;

                    break;
                }
                return 1;
            }
            return 0;
        }
        temp_r4_2 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r24 * 4) & 0x3FC));
        if ((temp_r4_2 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 6U) >= 1U)) {
            return 0;
        }
        var_r24 += 1;
        goto loop_18;
    }
    temp_r4_3 = *(FightOutPokemon **)((u8 *)arg1 + ((var_r18_2 * 4) & 0x3FC));
    if ((temp_r4_3 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_3, 6U) >= 1U)) {
        return 0;
    }
    var_r18_2 += 1;
    goto loop_12;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    s16 temp_r21;
    s16 var_r20;
    s16 var_r22;
    s32 temp_r25;
    s32 temp_r26;
    u8 temp_r3;
    u8 var_r14;
    u8 var_r19;
    u8 var_r23;
    u8 var_r24;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r23 = 0;
loop_21:
    if ((s32) var_r23 >= (s32) arg2) {
        return 0;
    }
    var_r14 = 0;
    while (var_r14 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        var_r14 += 1;
        continue;

        break;
    }
    sp8 = 0;
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x11DU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r25 = (var_r23 * 4) & 0x3FC;
    var_r22 = 0;
    var_r24 = 0;
    while (var_r24 < sp8) {
        temp_r26 = var_r24 * 0x2C;
        temp_r27 = &sp4C[var_r24];
        var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
        temp_r27->attacker[fightAi_getAnotherPokeNo(var_r23)] = 0;
        if (((u16) *(u16 *)((u8 *)sp4C + ((var_r23 * 2) & 0x1FE) + temp_r26 + 0x10) == 0x11D) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26), 0x36U) != 2)) {
            var_r20 = 0;
        }
        if (var_r22 < var_r20) {
            spC[0] = var_r24;
            var_r22 = var_r20;
            var_r19 = 1;
        } else if ((var_r22 == var_r20) && (var_r22 > 0)) {
            spC[var_r19] = var_r24;
            var_r19 += 1;
        }
        var_r24 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r19]]);
    temp_r3 = HSD_Rand() % 100;
    if ((var_r22 != 0) && ((s32) (var_r22 + arg6) > (s32) temp_r3)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0U);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r23 += 1;
    goto loop_21;
}

s32 fightAiCombo_Amaikaori_Hubuki_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    s16 temp_r21;
    s16 var_r20;
    s16 var_r22;
    s32 temp_r25;
    s32 temp_r26;
    u16 temp_r0;
    u8 temp_r3;
    u8 var_r14;
    u8 var_r19;
    u8 var_r23;
    u8 var_r24;
    void *temp_r30;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r23 = 0;
loop_23:
    if ((s32) var_r23 >= (s32) arg2) {
        return 0;
    }
    var_r14 = 0;
    while (var_r14 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        var_r14 += 1;
        continue;

        break;
    }
    sp8 = 0;
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xE6U, 0U, 0U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x171U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r25 = (var_r23 * 4) & 0x3FC;
    var_r22 = 0;
    temp_r30 = (u8 *)sp4C + temp_r25;
    var_r24 = 0;
    while (var_r24 < sp8) {
        temp_r26 = var_r24 * 0x2C;
        temp_r27 = &sp4C[var_r24];
        var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
        temp_r27->attacker[fightAi_getAnotherPokeNo(var_r23)] = 0;
        temp_r0 = *(u16 *)((u8 *)sp4C + ((var_r23 * 2) & 0x1FE) + temp_r26 + 0x10);
        if (((temp_r0 == 0xE6) || (temp_r0 == 0x171)) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r30 + temp_r26)), 0x3BU) != 2) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r30 + temp_r26)), 0x9DU) != 2)) {
            var_r20 = 0;
        }
        if (var_r22 < var_r20) {
            spC[0] = var_r24;
            var_r22 = var_r20;
            var_r19 = 1;
        } else if ((var_r22 == var_r20) && (var_r22 > 0)) {
            spC[var_r19] = var_r24;
            var_r19 += 1;
        }
        var_r24 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r19]]);
    temp_r3 = HSD_Rand() % 100;
    if ((var_r22 != 0) && ((s32) (var_r22 + arg6) > (s32) temp_r3)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0x2AU);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r23 += 1;
    goto loop_23;
}

s32 fightAiCombo_Amaikaori_Hubuki_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r31;
    s16 temp_r26;
    s16 var_r25_2;
    s16 var_r27;
    s32 temp_r30;
    u8 temp_r4;
    u8 var_r20;
    u8 var_r24;
    u8 var_r25;
    u8 var_r28;
    u8 var_r29;

    var_r25 = 0;
    sp8 = 0;
    while (var_r25 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r25]);
        var_r25 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xE6U, 1U, 0x3BU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xE6U, 1U, 0x9DU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x171U, 1U, 0x3BU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x171U, 1U, 0x9DU);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xE6U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r27 = 0;
    temp_r26 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r29 = 0;
    while (var_r29 < sp8) {
        temp_r31 = &sp4C[var_r29];
        var_r28 = 0;
        var_r25_2 = fightAiCombo_GetAllWazaValueTable(temp_r31, temp_r26, arg0, arg1, arg3, -1);
        while (var_r28 < (u8) ai_allwaza_valid_work) {
            temp_r30 = ((var_r28 * 4) & 0x3FC) + 8;
            if ((*(FightOutPokemon **)((u8 *)temp_r31 + temp_r30) != (FightOutPokemon *) temp_r31->defender[fightAi_getAnotherPokeNo(var_r28)]) && ((u8) temp_r31->kind[var_r28] != 2) && ((u8) temp_r31->kind[fightAi_getAnotherPokeNo(var_r28)] != 2)) {
                var_r25_2 = 0;
            }
            if (fightTrainerAiIsFightOutPokemonAvoidCntHikui(arg0, *(FightOutPokemon **)((u8 *)temp_r31 + temp_r30)) == 1) {
                var_r25_2 = 0;
            }
            var_r28 += 1;
            continue;

            break;
        }
        if (var_r27 < var_r25_2) {
            spC[0] = var_r29;
            var_r27 = var_r25_2;
            var_r24 = 1;
        } else if ((var_r27 == var_r25_2) && (var_r27 > 0)) {
            spC[var_r24] = var_r29;
            var_r24 += 1;
        }
        var_r29 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r24]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r27 != 0) && ((s32) (var_r27 + arg6) > (s32) temp_r4)) {
        var_r20 = 0;
        while ((s32) var_r20 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r20 * 4) & 0x3FC)), 0x18U);
            var_r20 += 1;
            continue;

            break;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Konran_DefDown_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    FightOutPokemon *temp_r4;
    s16 temp_r21;
    s16 var_r20;
    s16 var_r22_2;
    s32 temp_r25;
    s32 temp_r26;
    u16 temp_r0;
    u8 temp_r3;
    u8 var_r14;
    u8 var_r19;
    u8 var_r22;
    u8 var_r23;
    u8 var_r23_2;
    u8 var_r24;
    void *temp_r30;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r23 = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) arg4) {
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r22 * 4) & 0x3FC));
        if ((temp_r4 != 0) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 9U) == 0)) {
            var_r23 += 1;
        }
        var_r22 += 1;
        continue;

        break;
    }
    if (var_r23 == 0) {
        return 0;
    }
    var_r23_2 = 0;
loop_33:
    if ((s32) var_r23_2 >= (s32) arg2) {
        return 0;
    }
    var_r14 = 0;
    while (var_r14 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        var_r14 += 1;
        continue;

        break;
    }
    sp8 = 0;
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x12AU, 0U, 0U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xCFU, 0U, 0U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x6DU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r25 = (var_r23_2 * 4) & 0x3FC;
    var_r22_2 = 0;
    temp_r30 = (u8 *)sp4C + temp_r25;
    var_r24 = 0;
    while (var_r24 < sp8) {
        temp_r26 = var_r24 * 0x2C;
        temp_r27 = &sp4C[var_r24];
        var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
        temp_r27->attacker[fightAi_getAnotherPokeNo(var_r23_2)] = 0;
        temp_r0 = *(u16 *)((u8 *)sp4C + ((var_r23_2 * 2) & 0x1FE) + temp_r26 + 0x10);
        if (((temp_r0 == 0x12A) || (temp_r0 == 0xCF) || (temp_r0 == 0x6D)) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r30 + temp_r26)), 0x27U) != 2) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r30 + temp_r26)), 0x2BU) != 2) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r30 + temp_r26)), 0x67U) != 2)) {
            var_r20 = 0;
        }
        if (var_r22_2 < var_r20) {
            spC[0] = var_r24;
            var_r22_2 = var_r20;
            var_r19 = 1;
        } else if ((var_r22_2 == var_r20) && (var_r22_2 > 0)) {
            spC[var_r19] = var_r24;
            var_r19 += 1;
        }
        var_r24 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r19]]);
    temp_r3 = HSD_Rand() % 100;
    if ((var_r22_2 != 0) && ((s32) (var_r22_2 + arg6) > (s32) temp_r3)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0U);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r23_2 += 1;
    goto loop_33;
}

s32 fightAiCombo_Konran_DefDown_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r24;
    FightOutPokemon *temp_r4;
    s16 temp_r18;
    s16 var_r17;
    s16 var_r19_2;
    s32 temp_r23;
    u16 temp_r0;
    u8 temp_r4_2;
    u8 var_r18;
    u8 var_r18_2;
    u8 var_r19;
    u8 var_r20;
    u8 var_r20_2;
    u8 var_r21;
    u8 var_r31;

    var_r18 = 0;
    sp8 = 0;
    while (var_r18 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
        var_r18 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r20 = 0;
    var_r19 = 0;
    while ((s32) var_r19 < (s32) arg4) {
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r19 * 4) & 0x3FC));
        if ((temp_r4 != 0) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 9U) == 0)) {
            var_r20 += 1;
        }
        var_r19 += 1;
        continue;

        break;
    }
    if (var_r20 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x12AU, 1U, 0x27U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x12AU, 1U, 0x2BU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x12AU, 1U, 0x67U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xCFU, 1U, 0x27U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xCFU, 1U, 0x2BU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xCFU, 1U, 0x67U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x6DU, 1U, 0x27U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x6DU, 1U, 0x2BU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x6DU, 1U, 0x67U);
    if (sp8 == 0) {
        return 0;
    }
    var_r19_2 = 0;
    temp_r18 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r21 = 0;
    while (var_r21 < sp8) {
        temp_r24 = &sp4C[var_r21];
        var_r20_2 = 0;
        var_r17 = fightAiCombo_GetAllWazaValueTable(temp_r24, temp_r18, arg0, arg1, arg3, -1);
        while (var_r20_2 < (u8) ai_allwaza_valid_work) {
            temp_r23 = ((var_r20_2 * 2) & 0x1FE) + 0x10;
            if (((u16) *(u16 *)((u8 *)temp_r24 + temp_r23) == 0x12A) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r24->attacker[fightAi_getAnotherPokeNo(var_r20_2)], 0x14U) != 2) && (fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, temp_r24->attacker[fightAi_getAnotherPokeNo(var_r20_2)]) != 8)) {
                var_r17 = 0;
            }
            temp_r0 = *(u16 *)((u8 *)temp_r24 + temp_r23);
            if (((temp_r0 == 0xCF) || (temp_r0 == 0x6D)) && ((FightOutPokemon *) temp_r24->defender[var_r20_2] != (FightOutPokemon *) temp_r24->defender[fightAi_getAnotherPokeNo(var_r20_2)]) && ((u8) temp_r24->kind[var_r20_2] != 2) && ((u8) temp_r24->kind[fightAi_getAnotherPokeNo(var_r20_2)] != 2)) {
                var_r17 = 0;
            }
            var_r20_2 += 1;
            continue;

            break;
        }
        if (var_r19_2 < var_r17) {
            spC[0] = var_r21;
            var_r19_2 = var_r17;
            var_r31 = 1;
        } else if ((var_r19_2 == var_r17) && (var_r19_2 > 0)) {
            spC[var_r31] = var_r21;
            var_r31 += 1;
        }
        var_r21 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
    temp_r4_2 = HSD_Rand() % 100;
    if ((var_r19_2 != 0) && ((s32) (var_r19_2 + arg6) > (s32) temp_r4_2)) {
        var_r18_2 = 0;
        while ((s32) var_r18_2 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r18_2 * 4) & 0x3FC)), 0U);
            var_r18_2 += 1;
            continue;

            break;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Daibakuhatu_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r24;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_3;
    FightOutPokemon *temp_r4_4;
    s16 var_r19_2;
    s16 var_r20;
    s16 var_r21;
    s32 temp_r18;
    s32 temp_r18_2;
    u8 temp_r4_2;
    u8 var_r18;
    u8 var_r18_2;
    u8 var_r18_3;
    u8 var_r18_4;
    u8 var_r19;
    u8 var_r22;
    u8 var_r23;
    u8 var_r31;

    var_r18 = 0;
    sp8 = 0;
    while (var_r18 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
        var_r18 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r18_2 = 0;
loop_12:
    if ((s32) var_r18_2 >= (s32) arg2) {
        var_r18_3 = 0;
loop_18:
        if ((s32) var_r18_3 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x99U, 1U, 0x99U);
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0x99U);
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0x78U);
            if (sp8 == 0) {
                return 0;
            }
            var_r19 = 0;
            var_r20 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) var_r19 < (s32) arg4) {
                temp_r18 = (var_r19 * 4) & 0x3FC;
                temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r18);
                if (temp_r4 != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r4, 7U) == 1) {
                        var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2B1U);
                    }
                    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 8U) == 1)) {
                        var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2B2U);
                    }
                }
                var_r19 += 1;
                continue;

                break;
            }
            var_r21 = 0;
            var_r23 = 0;
            while (var_r23 < sp8) {
                temp_r24 = &sp4C[var_r23];
                var_r22 = 0;
                var_r19_2 = fightAiCombo_GetAllWazaValueTable(temp_r24, var_r20, arg0, arg1, arg3, -1);
                while (var_r22 < (u8) ai_allwaza_valid_work) {
                    temp_r18_2 = (var_r22 * 4) & 0x3FC;
                    if ((fightFloorCmpfightOutPokemonNimbleness(0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), temp_r24->attacker[fightAi_getAnotherPokeNo(var_r22)], 0U) == 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 7U) == 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 5U) == 0) && (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 8U) == 0)) {
                        var_r19_2 = 0;
                    }
                    var_r22 += 1;
                    continue;

                    break;
                }
                if (var_r21 < var_r19_2) {
                    spC[0] = var_r23;
                    var_r21 = var_r19_2;
                    var_r31 = 1;
                } else if ((var_r21 == var_r19_2) && (var_r21 > 0)) {
                    spC[var_r31] = var_r23;
                    var_r31 += 1;
                }
                var_r23 += 1;
                continue;

                break;
            }
            fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
            temp_r4_2 = HSD_Rand() % 100;
            if ((var_r21 != 0) && ((s32) (var_r21 + arg6) > (s32) temp_r4_2)) {
                var_r18_4 = 0;
                while ((s32) var_r18_4 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r18_4 * 4) & 0x3FC)), 0U);
                    var_r18_4 += 1;
                    continue;

                    break;
                }
                return 1;
            }
            return 0;
        }
        temp_r4_3 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r18_3 * 4) & 0x3FC));
        if ((temp_r4_3 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_3, 6U) >= 1U)) {
            return 0;
        }
        var_r18_3 += 1;
        goto loop_18;
    }
    temp_r4_4 = *(FightOutPokemon **)((u8 *)arg1 + ((var_r18_2 * 4) & 0x3FC));
    if ((temp_r4_4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_4, 6U) == 2)) {
        return 0;
    }
    var_r18_2 += 1;
    goto loop_12;
}

s32 fightAiCombo_Zisin_Mamoru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r17;
    s16 temp_r28;
    s16 var_r27;
    s16 var_r29;
    s32 temp_r16;
    s32 temp_r19;
    u16 temp_r0;
    u16 temp_r0_2;
    u8 temp_r4;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r16;
    u8 var_r16_2;
    u8 var_r26;
    u8 var_r30;
    u8 var_r31;

    var_r15 = 0;
    sp8 = 0;
    while (var_r15 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
        var_r15 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x99U, 1U, 0xB6U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0xB6U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x59U, 1U, 0xB6U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xDEU, 1U, 0xB6U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r28 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r29 = 0;
    var_r31 = 0;
    while (var_r31 < sp8) {
        temp_r17 = &sp4C[var_r31];
        var_r30 = 0;
        var_r27 = fightAiCombo_GetAllWazaValueTable(temp_r17, temp_r28, arg0, arg1, arg3, -1);
        while (var_r30 < (u8) ai_allwaza_valid_work) {
            temp_r16 = ((var_r30 * 2) & 0x1FE) + 0x10;
            if (((u16) *(u16 *)((u8 *)temp_r17 + temp_r16) == 0xB6) && (fightOutPokemon_GetLastUseWazaDataId(temp_r17->attacker[var_r30]) == 0xB6)) {
                var_r27 = 0;
            }
            temp_r0 = *(u16 *)((u8 *)temp_r17 + temp_r16);
            if ((temp_r0 == 0x59) || (temp_r0 == 0xDE)) {
                var_r15_2 = 0;
                while ((s32) var_r15_2 < (s32) arg4) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + ((var_r15_2 * 4) & 0x3FC)), 2U) == 1) {
                        var_r27 -= 0xA;
                    }
                    var_r15_2 += 1;
                    continue;

                    break;
                }
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r17->attacker[fightAi_getAnotherPokeNo(var_r30)], 2U) == 1) {
                    var_r27 = 0;
                }
                if (fightAi_GetTokuseiHaveFlag(arg0, temp_r17->attacker[fightAi_getAnotherPokeNo(var_r30)], 0x1AU) == 2) {
                    var_r27 = 0;
                }
            }
            temp_r0_2 = *(u16 *)((u8 *)temp_r17 + temp_r16);
            if ((temp_r0_2 == 0x99) || (temp_r0_2 == 0x78)) {
                if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, temp_r17->attacker[var_r30], 6U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, temp_r17->attacker[var_r30], 6U) == 1)) {
                    var_r27 = 0;
                }
                var_r16 = 0;
                while ((s32) var_r16 < (s32) arg4) {
                    temp_r19 = (var_r16 * 4) & 0x3FC;
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r19), 7U) == 1) {
                        var_r27 -= 0x1E;
                    }
                    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r19), 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r19), 8U) == 1)) {
                        var_r27 -= 0xA;
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r19), 6U) >= 1U) {
                        var_r27 = 0;
                    }
                    var_r16 += 1;
                    continue;

                    break;
                }
            }
            var_r30 += 1;
            continue;

            break;
        }
        if (var_r29 < var_r27) {
            spC[0] = var_r31;
            var_r29 = var_r27;
            var_r26 = 1;
        } else if ((var_r29 == var_r27) && (var_r29 > 0)) {
            spC[var_r26] = var_r31;
            var_r26 += 1;
        }
        var_r31 += 1;
        continue;

        break;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r26]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r29 != 0) && ((s32) (var_r29 + arg6) > (s32) temp_r4)) {
        var_r16_2 = 0;
        while ((s32) var_r16_2 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r16_2 * 4) & 0x3FC)), 0U);
            var_r16_2 += 1;
            continue;

            break;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_DarkWeather_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r3;
    FightOutPokemon *temp_r3_2;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_2;
    s16 temp_r3_3;
    s16 var_r29;
    s32 temp_r22;
    s32 temp_r22_2;
    u8 var_r21;
    u8 var_r21_2;
    u8 var_r21_3;
    u8 var_r22;
    u8 var_r22_2;
    u8 var_r22_3;

    var_r21 = 0;
    sp8 = 0;
    while (var_r21 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r21]);
        var_r21 += 1;
        continue;

        break;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    var_r21_2 = 0;
loop_15:
    if ((s32) var_r21_2 >= (s32) arg2) {
        var_r21_3 = 0;
loop_22:
        if ((s32) var_r21_3 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x16FU, 1U, 0x137U);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x16FU, 1U);
            if (sp8 == 0) {
                return 0;
            }
            var_r22 = 0;
            var_r29 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
            while ((s32) var_r22 < (s32) arg2) {
                temp_r3 = *(FightOutPokemon **)((u8 *)arg1 + ((var_r22 * 4) & 0x3FC));
                if ((temp_r3 != 0) && (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3)) == 1)) {
                    var_r29 = fightTrainerAiAddValueByAddsubDataId((s32) var_r29, arg0, 0x2AFU);
                }
                var_r22 += 1;
                continue;

                break;
            }
            var_r22_2 = 0;
            while ((s32) var_r22_2 < (s32) arg4) {
                temp_r3_2 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r22_2 * 4) & 0x3FC));
                if ((temp_r3_2 != 0) && (pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3_2)) == 1)) {
                    var_r29 = fightTrainerAiAddValueByAddsubDataId((s32) var_r29, arg0, 0x2AEU);
                }
                var_r22_2 += 1;
                continue;

                break;
            }
            temp_r3_3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r29, arg0, arg1, arg3, arg5, 5);
            if ((temp_r3_3 > 0) && ((s32) (temp_r3_3 + arg6) > (s32) (u8) (HSD_Rand() % 100))) {
                var_r22_3 = 0;
                while ((s32) var_r22_3 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r22_3 * 4) & 0x3FC)), 0U);
                    var_r22_3 += 1;
                    continue;

                    break;
                }
                return 1;
            }
            return 0;
        }
        temp_r22 = (var_r21_3 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r22);
        if ((temp_r4 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r22), 0xDU) >= 1U))) {
            return 0;
        }
        var_r21_3 += 1;
        goto loop_22;
    }
    temp_r22_2 = (var_r21_2 * 4) & 0x3FC;
    temp_r4_2 = *(FightOutPokemon **)((u8 *)arg1 + temp_r22_2);
    if ((temp_r4_2 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r22_2), 0xDU) == 2))) {
        return 0;
    }
    var_r21_2 += 1;
    goto loop_15;
}






typedef u8 (*WazaHitFunc)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
WazaHitFunc wazaDB_GetFightTrainerAiWazaHitFuncPtr(u16);
u16 fightTrainerGetIrekaeFightPokemonAry(FIGHT_TRAINER *, FightPokemon **);
u16 fightTrainerAiGetFightPokemonWazaDataIdAry(FIGHT_TRAINER *, FightPokemon *, u16 *, u8, u8);
u16 fightTrainerAiGetFightOutPokemonWazaDataIdAry(FIGHT_TRAINER *, FightOutPokemon *, u16 *, u8, u8);
s32 fightTrainerAiWazaDoWazaDamageFunc(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *, u8);
u16 figthOutPokemonGetPokemonDataId(FightOutPokemon *);
u16 zokuseiGetWazaJoutai(u16, u16);
extern u16 statusUpWazaTbl[];
extern u16 moukakeiTbl[];
extern u16 statusUpKinomiTbl[];
extern u16 NemuraseWazaTbl[];



s32 fightAiCombo_Migawari_Kisikaisei_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 spB4C;
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r18;
    s16 temp_r29;
    s16 var_r28;
    s16 var_r30;
    s32 temp_r17;
    s32 temp_r19;
    u8 temp_r4;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r15_3;
    u8 var_r16;
    u8 var_r27;
    u8 var_r31;
    u8 *temp_r20;

    sp8 = 0;
    temp_r29 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    spB4C = (s32) arg6;
    var_r31 = 0;
loop_34:
    if ((s32) var_r31 >= (s32) arg2) {
        return 0;
    }
    var_r15 = 0;
loop_3:
    if (var_r15 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
        var_r15 += 1;
        goto loop_3;
    }
    sp8 = 0;
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xA4U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r19 = (var_r31 * 4) & 0x3FC;
    var_r30 = 0;
    temp_r20 = (u8 *)sp4C + temp_r19;
    var_r16 = 0;
loop_29:
    if (var_r16 < sp8) {
        temp_r17 = var_r16 * 0x2C;
        temp_r18 = &sp4C[var_r16];
        var_r28 = fightAiCombo_GetAllWazaValueTable(temp_r18, temp_r29, arg0, arg1, arg3, -1);
        temp_r18->attacker[fightAi_getAnotherPokeNo(var_r31)] = 0;
        if ((u16) *(u16 *)((u8 *)sp4C + ((var_r31 * 2) & 0x1FE) + temp_r17 + 0x10) == 0xA4) {
            if ((fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r20 + temp_r17)), 0xB3U) != 2) && (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)temp_r20 + temp_r17)), 0xAFU) != 2)) {
                var_r28 = 0;
            }
            var_r15_2 = 0;
loop_15:
            if (var_r15_2 < 4U) {
                if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)temp_r18 + temp_r19), *(u16 *)((u8 *)moukakeiTbl + ((var_r15_2 * 2) & 0x1FE))) == 2) {
                    var_r28 += 0xA;
                }
                var_r15_2 += 1;
                goto loop_15;
            }
            var_r15_3 = 0;
loop_20:
            if (var_r15_3 < 7U) {
                if ((u16) *(u16 *)((u8 *)statusUpKinomiTbl + ((var_r15_3 * 2) & 0x1FE)) == fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r18 + temp_r19))) {
                    var_r28 += 0xA;
                }
                var_r15_3 += 1;
                goto loop_20;
            }
            if (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r20 + temp_r17), 0x14U) == 1) {
                var_r28 = 0;
            }
        }
        if (var_r30 < var_r28) {
            spC[0] = var_r16;
            var_r30 = var_r28;
            var_r27 = 1;
        } else if ((var_r30 == var_r28) && (var_r30 > 0)) {
            spC[var_r27] = var_r16;
            var_r27 += 1;
        }
        var_r16 += 1;
        goto loop_29;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r27]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r30 != 0) && ((s32) (var_r30 + spB4C) > (s32) temp_r4)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r19), 0U);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r31 += 1;
    goto loop_34;
}

s32 fightAiCombo_Hakaikousen_Hoeru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp64[64];
    u8 sp24;
    FightPokemon *spC[8];
    u8 sp8;
    FightAiAllWazaValid *temp_r24;
    FightOutPokemon **temp_r6;
    s16 var_r18;
    s16 var_r19;
    s16 var_r20_2;
    s32 temp_r23;
    u16 temp_r0;
    u16 temp_r17;
    u16 temp_r3;
    u8 temp_r4;
    u8 var_r17;
    u8 var_r17_2;
    u8 var_r18_2;
    u8 var_r20;
    u8 var_r21;
    u8 var_r21_2;
    u8 var_r22;
    u8 var_r31;

    var_r17 = 0;
    sp8 = 0;
loop_2:
    if (var_r17 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp64[var_r17]);
        var_r17 += 1;
        goto loop_2;
    }
    temp_r17 = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (temp_r17 == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x3FU, 1U, 0x2EU);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x152U, 1U, 0x2EU);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x134U, 1U, 0x2EU);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x133U, 1U, 0x2EU);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x3FU, 1U, 0x12U);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x152U, 1U, 0x12U);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x134U, 1U, 0x12U);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x133U, 1U, 0x12U);
    if (sp8 == 0) {
        return 0;
    }
    var_r19 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r21 = 0;
    var_r20 = 0;
loop_15:
    if ((s32) var_r20 < (s32) temp_r17) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)spC + ((var_r20 * 4) & 0x3FC)), 0x16U) == 1) {
            var_r21 = 1;
        } else {
            var_r20 += 1;
            goto loop_15;
        }
    }
    if (var_r21 == 0) {
        var_r19 = fightTrainerAiAddValueByAddsubDataId((s32) var_r19, arg0, 0x2C3U);
    }
    var_r20_2 = 0;
    var_r22 = 0;
loop_38:
    if (var_r22 < sp8) {
        var_r17_2 = 0;
        temp_r24 = &sp64[var_r22];
loop_24:
        if (var_r17_2 < (u8) ai_allwaza_valid_work) {
            temp_r0 = *(u16 *)((u8 *)temp_r24 + (((var_r17_2 * 2) & 0x1FE) + 0x10));
            if ((temp_r0 == 0x2E) || (temp_r0 == 0x12)) {
                temp_r24->defender[var_r17_2] = temp_r24->attacker[fightAi_getAnotherPokeNo(var_r17_2)];
            }
            var_r17_2 += 1;
            goto loop_24;
        }
        var_r21_2 = 0;
        var_r18 = fightAiCombo_GetAllWazaValueTable(temp_r24, var_r19, arg0, arg1, arg3, -1);
loop_31:
        if (var_r21_2 < (u8) ai_allwaza_valid_work) {
            temp_r23 = ((var_r21_2 * 2) & 0x1FE) + 0x10;
            temp_r3 = *(u16 *)((u8 *)temp_r24 + temp_r23);
            if ((temp_r3 == 0x2E) || (temp_r3 == 0x12)) {
                temp_r6 = &temp_r24->attacker[var_r21_2];
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, *(FightOutPokemon **)(temp_r6), *(u16 *)((u8 *)temp_r24 + temp_r23), *(FightOutPokemon **)((u8 *)temp_r6 + 8)) == 0) {
                    var_r18 = 0;
                }
            }
            var_r21_2 += 1;
            goto loop_31;
        }
        if (var_r20_2 < var_r18) {
            sp24 = var_r22;
            var_r20_2 = var_r18;
            var_r31 = 1;
        } else if ((var_r20_2 == var_r18) && (var_r20_2 > 0)) {
            (&sp24)[var_r31] = var_r22;
            var_r31 += 1;
        }
        var_r22 += 1;
        goto loop_38;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp64[(&sp24)[HSD_Rand() % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r20_2 != 0) && ((s32) (var_r20_2 + arg6) > (s32) temp_r4)) {
        var_r18_2 = 0;
loop_43:
        if ((s32) var_r18_2 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r18_2 * 4) & 0x3FC)), 0U);
            var_r18_2 += 1;
            goto loop_43;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Dokudoku_Karagenki_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r22;
    FightOutPokemon *temp_r16;
    s16 temp_r18;
    s16 var_r17;
    s16 var_r19;
    s32 temp_r23;
    s32 temp_r24;
    u8 (*temp_r16_2)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    u8 temp_r4;
    u8 var_r16;
    u8 var_r17_2;
    u8 var_r20;
    u8 var_r20_2;
    u8 var_r21;
    u8 var_r31;

    var_r16 = 0;
    sp8 = 0;
loop_2:
    if (var_r16 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r16]);
        var_r16 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x5CU, 1U, 0x107U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x105U, 1U, 0x107U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x5CU, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x105U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r19 = 0;
    temp_r18 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r21 = 0;
loop_32:
    if (var_r21 < sp8) {
        var_r20 = 0;
        temp_r22 = &sp4C[var_r21];
loop_14:
        if (var_r20 < (u8) ai_allwaza_valid_work) {
            if ((u16) *(u16 *)((u8 *)temp_r22 + (((var_r20 * 2) & 0x1FE) + 0x10)) == 0x107) {
                temp_r16 = temp_r22->attacker[var_r20];
                temp_r22->defender[fightAi_getAnotherPokeNo(var_r20)] = temp_r16;
            }
            var_r20 += 1;
            goto loop_14;
        }
        var_r20_2 = 0;
        var_r17 = fightAiCombo_GetAllWazaValueTable(temp_r22, temp_r18, arg0, arg1, arg3, -1);
loop_25:
        if (var_r20_2 < (u8) ai_allwaza_valid_work) {
            if ((u16) *(u16 *)((u8 *)temp_r22 + (((var_r20_2 * 2) & 0x1FE) + 0x10)) == 0x107) {
                if (fightOutPokemonIsJoutaiKaragenki(temp_r22->attacker[var_r20_2]) == 1) {
                    var_r17 = 0;
                }
                if ((fightAi_GetTokuseiHaveFlag(arg0, temp_r22->attacker[var_r20_2], 0x3EU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, temp_r22->attacker[var_r20_2], 0x3FU) == 2)) {
                    var_r17 += 0xA;
                }
                temp_r16_2 = wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r22->wazaId[fightAi_getAnotherPokeNo(var_r20_2)]);
                temp_r23 = (fightAi_getAnotherPokeNo(var_r20_2) * 4) + 8;
                temp_r24 = (fightAi_getAnotherPokeNo(var_r20_2) * 2) + 0x10;
                if (temp_r16_2(arg0, temp_r22->attacker[fightAi_getAnotherPokeNo(var_r20_2)], *(u16 *)((u8 *)temp_r22 + temp_r24), *(FightOutPokemon **)((u8 *)temp_r22 + temp_r23)) == 0) {
                    var_r17 = 0;
                }
            }
            var_r20_2 += 1;
            goto loop_25;
        }
        if (var_r19 < var_r17) {
            spC[0] = var_r21;
            var_r19 = var_r17;
            var_r31 = 1;
        } else if ((var_r19 == var_r17) && (var_r19 > 0)) {
            spC[var_r31] = var_r21;
            var_r31 += 1;
        }
        var_r21 += 1;
        goto loop_32;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r19 != 0) && ((s32) (var_r19 + arg6) > (s32) temp_r4)) {
        var_r17_2 = 0;
loop_37:
        if ((s32) var_r17_2 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r17_2 * 4) & 0x3FC)), 0U);
            var_r17_2 += 1;
            goto loop_37;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Konoyubitomare_StatusUp_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r21;
    s16 temp_r16;
    s16 var_r15_2;
    s16 var_r17;
    u8 temp_r4;
    u8 var_r15;
    u8 var_r16;
    u8 var_r18;
    u8 var_r19;
    u8 var_r20;
    u8 var_r31;

    var_r15 = 0;
    sp8 = 0;
loop_2:
    if (var_r15 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
        var_r15 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x10AU, 2U, 4U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r16 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r17 = 0;
    var_r20 = 0;
loop_25:
    if (var_r20 < sp8) {
        temp_r21 = &sp4C[var_r20];
        var_r19 = 0;
        var_r15_2 = fightAiCombo_GetAllWazaValueTable(temp_r21, temp_r16, arg0, arg1, arg3, -1);
loop_18:
        if (var_r19 < (u8) ai_allwaza_valid_work) {
            var_r18 = 0;
loop_16:
            if (var_r18 < 0xEU) {
                if (((u16) *(u16 *)((u8 *)temp_r21 + (((var_r19 * 2) & 0x1FE) + 0x10)) == (u16) *(u16 *)((u8 *)statusUpWazaTbl + (var_r18 * 6))) && (fightTrainerAiIsFightOutPokemonAllAbiCntTakai(arg0, *(FightOutPokemon **)((u8 *)temp_r21 + ((var_r19 * 4) & 0x3FC))) == 1)) {
                    var_r15_2 = 0;
                }
                var_r18 += 1;
                goto loop_16;
            }
            var_r19 += 1;
            goto loop_18;
        }
        if (var_r17 < var_r15_2) {
            spC[0] = var_r20;
            var_r17 = var_r15_2;
            var_r31 = 1;
        } else if ((var_r17 == var_r15_2) && (var_r17 > 0)) {
            spC[var_r31] = var_r20;
            var_r31 += 1;
        }
        var_r20 += 1;
        goto loop_25;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r17 != 0) && ((s32) (var_r17 + arg6) > (s32) temp_r4)) {
        var_r16 = 0;
loop_30:
        if ((s32) var_r16 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r16 * 4) & 0x3FC)), 0U);
            var_r16 += 1;
            goto loop_30;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r25;
    FightOutPokemon **temp_r6;
    s16 temp_r20;
    s16 var_r19;
    s16 var_r21;
    s32 temp_r24;
    u16 temp_r3;
    u8 temp_r4;
    u8 var_r16;
    u8 var_r17;
    u8 var_r18;
    u8 var_r22;
    u8 var_r23;
    u8 var_r31;

    var_r16 = 0;
    sp8 = 0;
loop_2:
    if (var_r16 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r16]);
        var_r16 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x11DU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21 = 0;
    temp_r20 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r23 = 0;
loop_34:
    if (var_r23 < sp8) {
        var_r18 = 0;
        temp_r25 = &sp4C[var_r23];
loop_14:
        if (var_r18 < (u8) ai_allwaza_valid_work) {
            if ((u16) *(u16 *)((u8 *)temp_r25 + (((var_r18 * 2) & 0x1FE) + 0x10)) == 0x11D) {
                temp_r25->defender[var_r18] = temp_r25->attacker[fightAi_getAnotherPokeNo(var_r18)];
            }
            var_r18 += 1;
            goto loop_14;
        }
        var_r22 = 0;
        var_r19 = fightAiCombo_GetAllWazaValueTable(temp_r25, temp_r20, arg0, arg1, arg3, -1);
loop_27:
        if (var_r22 < (u8) ai_allwaza_valid_work) {
            temp_r24 = ((var_r22 * 2) & 0x1FE) + 0x10;
            if ((u16) *(u16 *)((u8 *)temp_r25 + temp_r24) != 0x11D) {
                if (fightAi_GetTokuseiHaveFlag(arg0, temp_r25->attacker[var_r22], 0x36U) != 2) {
                    var_r19 = 0;
                }
                if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, getFightPokemonPtr__15FightOutPokemonFv(temp_r25->attacker[var_r22]), 0x36U) == 0) {
                    var_r19 = 0;
                }
            }
            temp_r3 = *(u16 *)((u8 *)temp_r25 + temp_r24);
            if (temp_r3 == 0x11D) {
                temp_r6 = &temp_r25->attacker[var_r22];
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, *(FightOutPokemon **)(temp_r6), *(u16 *)((u8 *)temp_r25 + temp_r24), *(FightOutPokemon **)((u8 *)temp_r6 + 8)) == 0) {
                    var_r19 = 0;
                }
                if ((u16) temp_r25->wazaId[fightAi_getAnotherPokeNo(var_r22)] == 0x11D) {
                    var_r19 = 0;
                }
            }
            var_r22 += 1;
            goto loop_27;
        }
        if (var_r21 < var_r19) {
            spC[0] = var_r23;
            var_r21 = var_r19;
            var_r31 = 1;
        } else if ((var_r21 == var_r19) && (var_r21 > 0)) {
            spC[var_r31] = var_r23;
            var_r31 += 1;
        }
        var_r23 += 1;
        goto loop_34;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r21 != 0) && ((s32) (var_r21 + arg6) > (s32) temp_r4)) {
        var_r17 = 0;
loop_39:
        if ((s32) var_r17 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r17 * 4) & 0x3FC)), 0x1DU);
            var_r17 += 1;
            goto loop_39;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Asanohizasi_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r23;
    FightOutPokemon **temp_r6;
    FightOutPokemon *temp_r4;
    FightOutPokemon *temp_r4_4;
    FightOutPokemon *temp_r4_5;
    s16 var_r18;
    s16 var_r19;
    s16 var_r30;
    s32 temp_r0;
    s32 temp_r18;
    s32 temp_r20;
    s32 temp_r20_2;
    s32 temp_r22;
    u8 temp_r4_3;
    u8 var_r17;
    u8 var_r17_2;
    u8 var_r17_3;
    u8 var_r17_4;
    u8 var_r17_5;
    u8 var_r20;
    u8 var_r21;
    u8 var_r29;
    u8 var_r5;
    u8 *temp_r4_2;

    var_r17 = 0;
    sp8 = 0;
loop_2:
    if (var_r17 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r17]);
        var_r17 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0U) == 1) {
        return 0;
    }
    var_r17_2 = 0;
loop_15:
    if ((s32) var_r17_2 >= (s32) arg2) {
        var_r17_3 = 0;
loop_22:
        if ((s32) var_r17_3 >= (s32) arg4) {
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xEAU);
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xECU);
            fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xEBU);
            fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xF1U, 1U);
            if (sp8 == 0) {
                return 0;
            }
            var_r17_4 = 0;
            var_r30 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
loop_32:
            if ((s32) var_r17_4 < (s32) arg4) {
                temp_r18 = (var_r17_4 * 4) & 0x3FC;
                temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r18);
                if (temp_r4 != 0) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r4, 0xAU) == 1) {
                        var_r30 = fightTrainerAiAddValueByAddsubDataId((s32) var_r30, arg0, 0x2BAU);
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 0x22U) >= 1U) {
                        var_r30 = fightTrainerAiAddValueByAddsubDataId((s32) var_r30, arg0, 0x2BBU);
                    }
                }
                var_r17_4 += 1;
                goto loop_32;
            }
            var_r19 = 0;
            var_r21 = 0;
loop_51:
            if (var_r21 < sp8) {
                var_r5 = 0;
                temp_r23 = &sp4C[var_r21];
loop_36:
                if (var_r5 < (u8) ai_allwaza_valid_work) {
                    temp_r0 = (var_r5 * 4) & 0x3FC;
                    var_r5 += 1;
                    temp_r4_2 = (u8 *)temp_r23 + temp_r0;
                    *(FightOutPokemon **)((u8 *)temp_r4_2 + 8) = *(FightOutPokemon **)(temp_r4_2);
                    goto loop_36;
                }
                var_r20 = 0;
                var_r18 = fightAiCombo_GetAllWazaValueTable(temp_r23, var_r30, arg0, arg1, arg3, -1);
loop_44:
                if (var_r20 < (u8) ai_allwaza_valid_work) {
                    temp_r22 = ((var_r20 * 2) & 0x1FE) + 0x10;
                    temp_r6 = &temp_r23->attacker[var_r20];
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(*(u16 *)((u8 *)temp_r23 + temp_r22))(arg0, *(FightOutPokemon **)(temp_r6), *(u16 *)((u8 *)temp_r23 + temp_r22), *(FightOutPokemon **)((u8 *)temp_r6 + 8)) == 0) {
                        var_r18 = 0;
                    }
                    if (((u16) *(u16 *)((u8 *)temp_r23 + temp_r22) == 0xF1) && (fightTrainerAiIsFightOutPokemonNokoriHpHikui(arg0, temp_r23->attacker[fightAi_getAnotherPokeNo(var_r20)]) == 0)) {
                        var_r18 = 0;
                    }
                    var_r20 += 1;
                    goto loop_44;
                }
                if (var_r19 < var_r18) {
                    spC[0] = var_r21;
                    var_r19 = var_r18;
                    var_r29 = 1;
                } else if ((var_r19 == var_r18) && (var_r19 > 0)) {
                    spC[var_r29] = var_r21;
                    var_r29 += 1;
                }
                var_r21 += 1;
                goto loop_51;
            }
            fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r29]]);
            temp_r4_3 = HSD_Rand() % 100;
            if ((var_r19 != 0) && ((s32) (var_r19 + arg6) > (s32) temp_r4_3)) {
                var_r17_5 = 0;
loop_56:
                if ((s32) var_r17_5 < (s32) arg2) {
                    setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r17_5 * 4) & 0x3FC)), 0U);
                    var_r17_5 += 1;
                    goto loop_56;
                }
                return 1;
            }
            return 0;
        }
        temp_r20 = (var_r17_3 * 4) & 0x3FC;
        temp_r4_4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r20);
        if ((temp_r4_4 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4_4, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r20), 0xDU) >= 1U))) {
            return 0;
        }
        var_r17_3 += 1;
        goto loop_22;
    }
    temp_r20_2 = (var_r17_2 * 4) & 0x3FC;
    temp_r4_5 = *(FightOutPokemon **)((u8 *)arg1 + temp_r20_2);
    if ((temp_r4_5 != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, temp_r4_5, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r20_2), 0xDU) == 2))) {
        return 0;
    }
    var_r17_2 += 1;
    goto loop_15;
}

s32 fightAiCombo_StatusUp_Batontatti_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 spB4C;
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r25;
    s16 temp_r3;
    s16 var_r16;
    s16 var_r18;
    s32 temp_r22;
    s32 temp_r23;
    u16 temp_r3_2;
    u8 temp_r14;
    u8 temp_r15;
    u8 temp_r16;
    u8 temp_r17;
    u8 temp_r4;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r15_3;
    u8 var_r19;
    u8 var_r20;
    u8 var_r21;
    u8 var_r31;
    u8 var_r4;
    u8 *temp_r24;

    sp8 = 0;
    temp_r14 = fightFloor_GetFightType(0);
    temp_r15 = fightFloor_GetFightTypeTrainerNum(0);
    temp_r16 = fightFloor_GetFightTypeEntryPokemonNum(0);
    temp_r17 = fightFloor_GetFightTypeFightoutPokemonNum(0);
    if (fightSideGetHikaeFightPokemonNum(fightTargetGetPtr(2U, arg0, temp_r14), temp_r15, temp_r16, temp_r17) == 0) {
        return 0;
    }
    temp_r3 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    spB4C = (s32) arg6;
    var_r19 = 0;
loop_38:
    if ((s32) var_r19 >= (s32) arg2) {
        return 0;
    }
    var_r15 = 0;
loop_5:
    if (var_r15 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
        var_r15 += 1;
        goto loop_5;
    }
    var_r15_2 = 0;
    sp8 = 0;
loop_8:
    if (var_r15_2 < 0xEU) {
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, *(u16 *)((u8 *)statusUpWazaTbl + (var_r15_2 * 6)), 0U, 0U);
        var_r15_2 += 1;
        goto loop_8;
    }
    if (sp8 == 0) {
        return 0;
    }
    temp_r22 = (var_r19 * 4) & 0x3FC;
    var_r18 = 0;
    var_r21 = 0;
    temp_r23 = ((var_r19 * 2) & 0x1FE) + 0x10;
loop_33:
    if (var_r21 < sp8) {
        var_r15_3 = 1;
        var_r4 = 0;
        temp_r25 = &sp4C[var_r21];
        temp_r24 = (u8 *)temp_r25 + temp_r22;
loop_16:
        if (var_r4 < 0xEU) {
            if ((u16) *(u16 *)((u8 *)temp_r25 + temp_r23) == (u16) *(u16 *)((u8 *)statusUpWazaTbl + (var_r4 * 6))) {
                *(FightOutPokemon **)((u8 *)temp_r24 + 8) = (FightOutPokemon *) *(FightOutPokemon **)(temp_r24);
            }
            var_r4 += 1;
            goto loop_16;
        }
        var_r16 = fightAiCombo_GetAllWazaValueTable(temp_r25, temp_r3, arg0, arg1, arg3, -1);
        var_r20 = 0;
        temp_r25->attacker[fightAi_getAnotherPokeNo(var_r19)] = 0;
loop_24:
        if (var_r20 < 0xEU) {
            temp_r3_2 = *(u16 *)((u8 *)temp_r25 + temp_r23);
            if (temp_r3_2 == (u16) *(u16 *)((u8 *)statusUpWazaTbl + (var_r20 * 6))) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3_2)(arg0, *(FightOutPokemon **)(temp_r24), *(u16 *)((u8 *)temp_r25 + temp_r23), *(FightOutPokemon **)((u8 *)temp_r24 + 8)) == 0) {
                    var_r16 = 0;
                }
                var_r15_3 = 0;
                if (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)(temp_r24)), 0xE2U) != 2) {
                    var_r16 = 0;
                }
            }
            var_r20 += 1;
            goto loop_24;
        }
        if (var_r15_3 == 1) {
            var_r16 = 0;
        }
        if (var_r18 < var_r16) {
            spC[0] = var_r21;
            var_r18 = var_r16;
            var_r31 = 1;
        } else if ((var_r18 == var_r16) && (var_r18 > 0)) {
            spC[var_r31] = var_r21;
            var_r31 += 1;
        }
        var_r21 += 1;
        goto loop_33;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r18 != 0) && ((s32) (var_r18 + spB4C) > (s32) temp_r4)) {
        setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r22), 0U);
        fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
    }
    var_r19 += 1;
    goto loop_38;
}

s32 fightAiCombo_Haradaiko_Zikoanzi_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r25;
    FightOutPokemon **temp_r6;
    FightOutPokemon *temp_r3_2;
    s16 temp_r19;
    s16 var_r18_2;
    s16 var_r20;
    s32 temp_r23;
    u16 temp_r3;
    u8 temp_r4;
    u8 var_r18;
    u8 var_r18_3;
    u8 var_r19;
    u8 var_r19_2;
    u8 var_r21;
    u8 var_r22;
    u8 var_r31;

    var_r19 = 0;
    sp8 = 0;
loop_2:
    if (var_r19 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r19]);
        var_r19 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r19_2 = 0;
loop_12:
    if (var_r19_2 >= (u8) ai_allwaza_valid_work) {
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xBBU, 1U, 0xF4U);
        fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xBBU, 1U);
        if (sp8 == 0) {
            return 0;
        }
        var_r20 = 0;
        temp_r19 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
        var_r22 = 0;
loop_36:
        if (var_r22 < sp8) {
            var_r18 = 0;
            temp_r25 = &sp4C[var_r22];
loop_20:
            if (var_r18 < (u8) ai_allwaza_valid_work) {
                if ((u16) *(u16 *)((u8 *)temp_r25 + (((var_r18 * 2) & 0x1FE) + 0x10)) == 0xF4) {
                    temp_r25->defender[var_r18] = temp_r25->attacker[fightAi_getAnotherPokeNo(var_r18)];
                }
                var_r18 += 1;
                goto loop_20;
            }
            var_r21 = 0;
            var_r18_2 = fightAiCombo_GetAllWazaValueTable(temp_r25, temp_r19, arg0, arg1, arg3, -1);
loop_29:
            if (var_r21 < (u8) ai_allwaza_valid_work) {
                temp_r23 = ((var_r21 * 2) & 0x1FE) + 0x10;
                temp_r3 = *(u16 *)((u8 *)temp_r25 + temp_r23);
                if (temp_r3 == 0xF4) {
                    temp_r6 = &temp_r25->attacker[var_r21];
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, *(FightOutPokemon **)(temp_r6), *(u16 *)((u8 *)temp_r25 + temp_r23), *(FightOutPokemon **)((u8 *)temp_r6 + 8)) == 0) {
                        var_r18_2 = 0;
                    }
                }
                if (((u16) *(u16 *)((u8 *)temp_r25 + temp_r23) == 0xBB) && (fightOutPokemonGetNowHpPercentage(temp_r25->attacker[var_r21]) <= 0x32)) {
                    var_r18_2 = 0;
                }
                var_r21 += 1;
                goto loop_29;
            }
            if (var_r20 < var_r18_2) {
                spC[0] = var_r22;
                var_r20 = var_r18_2;
                var_r31 = 1;
            } else if ((var_r20 == var_r18_2) && (var_r20 > 0)) {
                spC[var_r31] = var_r22;
                var_r31 += 1;
            }
            var_r22 += 1;
            goto loop_36;
        }
        fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r31]]);
        temp_r4 = HSD_Rand() % 100;
        if ((var_r20 != 0) && ((s32) (var_r20 + arg6) > (s32) temp_r4)) {
            var_r18_3 = 0;
loop_41:
            if ((s32) var_r18_3 < (s32) arg2) {
                setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r18_3 * 4) & 0x3FC)), 0U);
                var_r18_3 += 1;
                goto loop_41;
            }
            return 1;
        }
        return 0;
    }
    temp_r3_2 = *(FightOutPokemon **)((u8 *)arg1 + ((var_r19_2 * 4) & 0x3FC));
    if ((temp_r3_2 != 0) && (fightOutPokemon_GetAbicntPhyAtk(temp_r3_2) >= 0xCU)) {
        return 0;
    }
    var_r19_2 += 1;
    goto loop_12;
}

s32 fightAiCombo_Daibakuhatu_Koraeru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp9;
    u8 sp8;
    FightAiAllWazaValid *temp_r19;
    s16 temp_r14;
    s16 var_r29;
    s16 var_r30;
    s32 temp_r15;
    s32 temp_r17;
    u16 temp_r0;
    u16 temp_r0_2;
    u8 temp_r4;
    u8 var_r14;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r15_3;
    u8 var_r15_4;
    u8 var_r16;
    u8 var_r17;
    u8 var_r28;
    u8 var_r31;

    sp8 = arg6;
    var_r14 = 0;
    sp9 = 0;
loop_2:
    if (var_r14 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        var_r14 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp9, 1U, 0x99U, 1U, 0xCBU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp9, 1U, 0x78U, 1U, 0xCBU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp9, 1U, 0x59U, 1U, 0xCBU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp9, 1U, 0xDEU, 1U, 0xCBU);
    if (sp9 == 0) {
        return 0;
    }
    temp_r14 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r30 = 0;
    var_r16 = 0;
loop_57:
    if (var_r16 < sp9) {
        temp_r19 = &sp4C[var_r16];
        var_r31 = 0;
        var_r29 = fightAiCombo_GetAllWazaValueTable(temp_r19, temp_r14, arg0, arg1, arg3, -1);
loop_50:
        if (var_r31 < (u8) ai_allwaza_valid_work) {
            temp_r17 = ((var_r31 * 2) & 0x1FE) + 0x10;
            if ((u16) *(u16 *)((u8 *)temp_r19 + temp_r17) == 0xCB) {
                var_r15 = 0;
loop_16:
                if (var_r15 < 4U) {
                    if (fightAi_GetTokuseiHaveFlag(arg0, temp_r19->attacker[var_r31], *(u16 *)((u8 *)moukakeiTbl + ((var_r15 * 2) & 0x1FE))) == 2) {
                        var_r29 += 0xA;
                    }
                    var_r15 += 1;
                    goto loop_16;
                }
                if ((fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(temp_r19->attacker[var_r31]), 0xB3U) == 2) || (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(temp_r19->attacker[var_r31]), 0xAFU) == 2)) {
                    var_r29 += 0xA;
                }
                var_r15_2 = 0;
loop_24:
                if (var_r15_2 < 7U) {
                    if ((u16) *(u16 *)((u8 *)statusUpKinomiTbl + ((var_r15_2 * 2) & 0x1FE)) == fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, temp_r19->attacker[var_r31])) {
                        var_r29 += 0xA;
                    }
                    var_r15_2 += 1;
                    goto loop_24;
                }
                if (fightOutPokemon_GetLastUseWazaDataId(temp_r19->attacker[var_r31]) == 0xCB) {
                    var_r29 = 0;
                }
            }
            temp_r0 = *(u16 *)((u8 *)temp_r19 + temp_r17);
            if ((temp_r0 == 0x59) || (temp_r0 == 0xDE)) {
                var_r15_3 = 0;
loop_33:
                if ((s32) var_r15_3 < (s32) arg4) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + ((var_r15_3 * 4) & 0x3FC)), 2U) == 1) {
                        var_r29 -= 0xA;
                    }
                    var_r15_3 += 1;
                    goto loop_33;
                }
            }
            temp_r0_2 = *(u16 *)((u8 *)temp_r19 + temp_r17);
            if ((temp_r0_2 == 0x99) || (temp_r0_2 == 0x78)) {
                if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, temp_r19->attacker[var_r31], 6U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, temp_r19->attacker[var_r31], 6U) == 1)) {
                    var_r29 = 0;
                }
                var_r17 = 0;
loop_48:
                if ((s32) var_r17 < (s32) arg4) {
                    temp_r15 = (var_r17 * 4) & 0x3FC;
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r15), 7U) == 1) {
                        var_r29 -= 0x1E;
                    }
                    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r15), 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r15), 8U) == 1)) {
                        var_r29 -= 0xA;
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r15), 6U) >= 1U) {
                        var_r29 = 0;
                    }
                    var_r17 += 1;
                    goto loop_48;
                }
            }
            var_r31 += 1;
            goto loop_50;
        }
        if (var_r30 < var_r29) {
            spC[0] = var_r16;
            var_r30 = var_r29;
            var_r28 = 1;
        } else if ((var_r30 == var_r29) && (var_r30 > 0)) {
            spC[var_r28] = var_r16;
            var_r28 += 1;
        }
        var_r16 += 1;
        goto loop_57;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r28]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r30 != 0) && ((s32) (var_r30 + sp8) > (s32) temp_r4)) {
        var_r15_4 = 0;
loop_62:
        if ((s32) var_r15_4 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r15_4 * 4) & 0x3FC)), 0U);
            var_r15_4 += 1;
            goto loop_62;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nemurase_Yumekui_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r31;
    FightOutPokemon *temp_r4;
    s16 temp_r27;
    s16 var_r26;
    s16 var_r28_2;
    s32 temp_r28;
    u8 temp_r4_2;
    u8 var_r21;
    u8 var_r25;
    u8 var_r27;
    u8 var_r28;
    u8 var_r29;
    u8 var_r29_2;
    u8 var_r29_3;
    u8 var_r30;

    var_r25 = 0;
    var_r27 = 0;
    sp8 = 0;
loop_2:
    if (var_r27 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r27]);
        var_r27 += 1;
        goto loop_2;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r29 = 0;
    var_r28 = 0;
loop_12:
    if ((s32) var_r28 < (s32) arg4) {
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + ((var_r28 * 4) & 0x3FC));
        if ((temp_r4 != 0) && (fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 8U) == 0)) {
            var_r29 += 1;
        }
        var_r28 += 1;
        goto loop_12;
    }
    if (var_r29 == 0) {
        return 0;
    }
    var_r29_2 = 0;
loop_17:
    if (var_r29_2 < 6U) {
        temp_r28 = (var_r29_2 * 2) & 0x1FE;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, *(NemuraseWazaTbl + temp_r28), 1U, 0x8AU);
        fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, *(NemuraseWazaTbl + temp_r28), 1U);
        var_r29_2 += 1;
        goto loop_17;
    }
    if (sp8 == 0) {
        return 0;
    }
    var_r28_2 = 0;
    temp_r27 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r30 = 0;
loop_34:
    if (var_r30 < sp8) {
        temp_r31 = &sp4C[var_r30];
        var_r29_3 = 0;
        var_r26 = fightAiCombo_GetAllWazaValueTable(temp_r31, temp_r27, arg0, arg1, arg3, -1);
loop_27:
        if (var_r29_3 < (u8) ai_allwaza_valid_work) {
            if ((*(FightOutPokemon **)((u8 *)temp_r31 + (((var_r29_3 * 4) & 0x3FC) + 8)) != (FightOutPokemon *) temp_r31->defender[fightAi_getAnotherPokeNo(var_r29_3)]) && ((u8) temp_r31->kind[var_r29_3] != 2) && ((u8) temp_r31->kind[fightAi_getAnotherPokeNo(var_r29_3)] != 2)) {
                var_r26 = 0;
            }
            var_r29_3 += 1;
            goto loop_27;
        }
        if (var_r28_2 < var_r26) {
            spC[0] = var_r30;
            var_r28_2 = var_r26;
            var_r25 = 1;
        } else if ((var_r28_2 == var_r26) && (var_r28_2 > 0)) {
            spC[var_r25] = var_r30;
            var_r25 += 1;
        }
        var_r30 += 1;
        goto loop_34;
    }
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[HSD_Rand() % var_r25]]);
    temp_r4_2 = HSD_Rand() % 100;
    if ((var_r28_2 != 0) && ((s32) (var_r28_2 + arg6) > (s32) temp_r4_2)) {
        var_r21 = 0;
loop_39:
        if ((s32) var_r21 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r21 * 4) & 0x3FC)), 0U);
            var_r21 += 1;
            goto loop_39;
        }
        return 1;
    }
    return 0;
}





}
