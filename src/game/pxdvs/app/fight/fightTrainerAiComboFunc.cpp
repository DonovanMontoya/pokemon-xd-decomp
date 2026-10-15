#include <dolphin/types.h>
#ifdef __cplusplus
extern "C" {
#endif
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
u8 wazaDB_GetZokuseiDataId(u16);
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
u16 fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(FIGHT_TRAINER *, FightPokemon *);
u16 fightTrainerAiGetFightOutPokemonZokuseiDataId(FIGHT_TRAINER *, FightOutPokemon *, u8);
u16 fightAi_GetWazaZokuseiData_ThinkWeatherBall(u16, u8);
u32 fightFloor_GetFightTypeFightoutPokemonNum(void *);
u8 fightFloor_GetFightKindDorobouFlag(void *);
u32 fightFloor_GetFightTypeEntryPokemonNum(void *);
u32 fightFloor_GetFightTypeTrainerNum(void *);
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
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r27;
    s32 temp_r23;
    u8 value26_u8;
    u8 value25_u8;
    u8 value27_u8;
    s16 var_r24;
    s16 temp_r23_2;
    s16 var_r22;
    u8 var_r21;
    u8 var_r20;
    FightOutPokemon *temp_r4;
    u8 temp_r4_2;
    FightSide *temp_r3;
    u16 temp_r3_2;
    u8 sp8;
    u8 i1;
    u8 ftype;
    u8 cnt;
    s32 rnd;

    sp8 = 0;
    ftype = fightFloor_GetFightType(0);
    var_r21 = 0;
    i1 = 0;
    while (i1 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[i1]);
        i1 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, ftype);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    cnt = 0;
    value25_u8 = 0;
    while ((s32) value25_u8 < (s32) arg4) {
        temp_r23 = (value25_u8 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r23);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r23), 0x49U) < 1U)) {
            cnt += 1;
        }
        value25_u8 += 1;
        continue;
    }
    if (cnt == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x173U, 2U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x173U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r23_2 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r24 = 0;
    for (value26_u8 = 0; value26_u8 < sp8; value26_u8++) {
        temp_r27 = &sp4C[value26_u8];
        var_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23_2, arg0, arg1, arg3, -1);
        for (value27_u8 = 0; value27_u8 < (u8) ai_allwaza_valid_work; value27_u8++) {
            temp_r3_2 = *(u16 *)((u8 *)temp_r27 + 0x10 + (value27_u8 * 2 & 0x1FE));
            if (temp_r3_2 != 0x173 && wazaDB_GetZokuseiDataId(temp_r3_2) != 1) {
                var_r22 = 0;
            }
        }
        if (var_r24 < var_r22) {
            spC[0] = value26_u8;
            var_r24 = var_r22;
            var_r21 = 1;
        } else if ((var_r24 == var_r22) && (var_r24 > 0)) {
            spC[var_r21] = value26_u8;
            var_r21 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r21]]);
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
    s32 rnd;
    u8 var_r22;
    u8 cnt;
    u8 ftype;
    u8 i1;


    sp8 = 0;
    ftype = fightFloor_GetFightType(0);
    i1 = 0;
    while (i1 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[i1]);
        i1 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, ftype);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    cnt = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) arg4) {
        temp_r24 = (var_r22 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U)) {
            cnt += 1;
        }
        var_r22 += 1;
        continue;
    }
    if (cnt == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x167U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if (temp_r3_2 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3_2 + arg6) > (s32) (u8) (rnd % 100))) {
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
    u8 var_r22;
    u8 cnt;
    u8 ftype;
    u8 i1;
    s32 rnd;

    sp8 = 0;
    ftype = fightFloor_GetFightType(0);
    i1 = 0;
    while (i1 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[i1]);
        i1 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, ftype);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    cnt = 0;
    var_r22 = 0;
    while ((s32) var_r22 < (s32) arg4) {
        temp_r24 = (var_r22 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U)) {
            cnt += 1;
        }
        var_r22 += 1;
        continue;
    }
    if (cnt == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x170U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if (temp_r3_2 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3_2 + arg6) > (s32) (u8) (rnd % 100))) {
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
    FightAiAllWazaValid spC[64];
    u8 sp8;
    FightOutPokemon *temp_r4;
    s16 temp_r3_2;
    s32 temp_r24;
    u8 var_r24;
    s32 rnd;
    u8 value22_u8;
    u8 cnt;
    u8 ftype;
    u8 i1;
    FightSide *temp_r3;

    sp8 = 0;
    ftype = fightFloor_GetFightType(0);
    i1 = 0;
    while (i1 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[i1]);
        i1 += 1;
        continue;
    }
    temp_r3 = fightTargetGetPtr(3U, arg0, ftype);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4CU) == 1) {
        return 0;
    }
    if (fightSideIsJoutaiDataId(temp_r3, 0x4BU) == 1) {
        return 0;
    }
    cnt = 0;
    value22_u8 = 0;
    while ((s32) value22_u8 < (s32) arg4) {
        temp_r24 = (value22_u8 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r24);
        if ((temp_r4 != 0) && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x1DU) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x49U) < 1U) && (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r24), 0x14U) < 1U)) {
            cnt += 1;
        }
        value22_u8 += 1;
        continue;
    }
    if (cnt == 0) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x171U, 1U, 0x172U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x171U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r3_2 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4), arg0, arg1, arg3, arg5, -1);
    if (temp_r3_2 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3_2 + arg6) > (s32) (u8) (rnd % 100))) {
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
    s32 rnd;

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
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        var_r28 = 0;
        while ((s32) var_r28 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((var_r28 * 4) & 0x3FC)), 0U);
            var_r28 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}







s32 fightAiCombo_Makibisi_Hoeru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 var_r24;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s32 rnd;
    FightSide *temp_r21;
    FightSide *temp_r3;
    s16 temp_r3_2;
    u8 temp_r31;
    u8 temp_r30;
    u8 temp_r29;
    u8 var_r21;
    u8 temp_r20;

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
    if (temp_r3_2 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3_2 + arg6) > (s32) (u8) (rnd % 100))) {
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
    s32 rnd;

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
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value23_u8 = 0;
        while ((s32) value23_u8 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((value23_u8 * 4) & 0x3FC)), 0U);
            value23_u8 += 1;
            continue;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Arare_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if (value4_FightOutPokemonPtr != 0 && (fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2)) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if (value4_FightOutPokemonPtr != 0 && (fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x102U, 1U, 0x137U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x102U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        value4_FightOutPokemonPtr = arg3[value22_u8];
        if (value4_FightOutPokemonPtr != 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xFU) == 1) {
            var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ADU);
        }
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 4);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sunaarasi_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xC9U, 1U, 0x137U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xC9U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
        if (value4_FightOutPokemonPtr != 0) {
            if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 8U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 4U) == 1)) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ABU);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 8U) >= 1U) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2ACU);
            }
        }
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 3);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 1U, 0x137U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
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
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 1U, 0x137U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
        if (value4_FightOutPokemonPtr != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A6U);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x2A7U);
            }
        }
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Mizu_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 3U, 0xBU);
    fightAi_AllWazaValid_DelComboList(arg0, spC, &sp8, 1U, 0xF0U, 2U, 1U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
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
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Kaminari_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF0U, 1U, 0x57U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF0U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
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
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 2);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Honoo_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) == 2) || (fightAi_GetTokuseiHaveFlag(arg0, arg1[value21_u8], 0xDU) == 2))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 3U, 0xAU);
    fightAi_AllWazaValid_DelComboList(arg0, spC, &sp8, 1U, 0xF1U, 2U, 1U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
        if (value4_FightOutPokemonPtr != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29EU);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29FU);
            }
        }
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Sooraabiimu_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 var_r21_4;
    u8 value22_u8;
    u8 value21_u8;
    FightOutPokemon * value4_FightOutPokemonPtr;
    FightAiAllWazaValid spC[64];
    u8 sp8;
    s16 temp_r3;
    s32 temp_r25;
    s32 rnd;

    value21_u8 = 0;
    sp8 = 0;
    while (value21_u8 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[value21_u8]);
        value21_u8 += 1;
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
    for (value21_u8 = 0; value21_u8 < arg2; value21_u8++) {
        value4_FightOutPokemonPtr = arg1[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, value4_FightOutPokemonPtr, 0x4DU) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, arg1[value21_u8], 0xDU) == 1))) {
            return 0;
        }
    }
    for (value21_u8 = 0; value21_u8 < arg4; value21_u8++) {
        value4_FightOutPokemonPtr = arg3[value21_u8];
        if ((value4_FightOutPokemonPtr != 0) && ((fightAi_GetTokuseiHaveFlag(arg0, value4_FightOutPokemonPtr, 0x4DU) >= 1U) || (fightAi_GetTokuseiHaveFlag(arg0, arg3[value21_u8], 0xDU) >= 1U))) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0xF1U, 1U, 0x4CU);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0xF1U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r21_4 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (value22_u8 = 0; value22_u8 < arg4; value22_u8++) {
        temp_r25 = (u32) value22_u8 * 4 & 0x3FC;
        value4_FightOutPokemonPtr = *(FightOutPokemon **)((u8 *)arg3 + temp_r25);
        if (value4_FightOutPokemonPtr != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, value4_FightOutPokemonPtr, 0xAU) == 1) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29CU);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r25), 0x22U) >= 1U) {
                var_r21_4 = fightTrainerAiAddValueByAddsubDataId((s32) var_r21_4, arg0, 0x29DU);
            }
        }
    }
    temp_r3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r21_4, arg0, arg1, arg3, arg5, 1);
    if (temp_r3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3 + arg6) > (s32) (u8) (rnd % 100))) {
        value21_u8 = 0;
        while (value21_u8 < arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[value21_u8], 0U);
            value21_u8 += 1;
        }
        return 1;
    }
    return 0;
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
void fightOutPokemonCreateFightAction(FightOutPokemon *, u32, u32, void *, void *, s32);
extern u8 fight_action_data_turn[];
Pokemon *getPokemonBuffPtr__12FightPokemonFv(FightPokemon *);
u16 getHp__7PokemonCFv(Pokemon *);
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
    FightOutPokemon *temp_r4_2;
    u8 var_r23;
    u8 var_r22_3;
    s16 var_r21_2;
    s16 var_r20;
    s16 var_r19_3;
    u16 temp_r3_3;
    u8 temp_r4;
    u8 var_r19;
    u8 var_r21;
    u8 var_r22;
    u8 var_r31;
    s32 rnd;

    var_r31 = 0;
    var_r21 = 0;
    sp8 = 0;
    while (var_r21 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r21]);
        var_r21 += 1;
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
    for (var_r22 = 0; var_r22 < arg2; var_r22++) {
        temp_r4_2 = arg1[var_r22];
        if (temp_r4_2 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 0x4DU) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[var_r22], 0xDU) == 2)) {
            return 0;
        }
    }
    for (var_r22 = 0; var_r22 < arg4; var_r22++) {
        temp_r4_2 = arg3[var_r22];
        if (temp_r4_2 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 0x4DU) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r22], 0xDU) >= 1U)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x16FU, 2U, 1U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0x16FU, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r20 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r19 = 0; var_r19 < arg2; var_r19++) {
        temp_r3 = arg1[var_r19];
        if (temp_r3 != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3)) == 1) {
            var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2C5U);
        }
    }
    for (var_r19 = 0; var_r19 < arg4; var_r19++) {
        temp_r3 = arg3[var_r19];
        if (temp_r3 != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r3)) == 1) {
            var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2C4U);
        }
    }
    var_r21_2 = 0;
    for (var_r23 = 0; var_r23 < sp8; var_r23++) {
        temp_r24 = &sp4C[var_r23];
        var_r19_3 = fightAiCombo_GetAllWazaValueTable(temp_r24, var_r20, arg0, arg1, arg3, -1);
        for (var_r22_3 = 0; var_r22_3 < (u8) ai_allwaza_valid_work; var_r22_3++) {
            temp_r3_3 = *(u16 *)((u8 *)temp_r24 + 0x10 + (var_r22_3 * 2 & 0x1FE));
            if (temp_r3_3 != 0x16F && wazaCheckDarkWaza(temp_r3_3) == 0) {
                var_r19_3 = 0;
            }
        }
        if (var_r21_2 < var_r19_3) {
            spC[0] = var_r23;
            var_r21_2 = var_r19_3;
            var_r31 = 1;
        } else if (var_r21_2 == var_r19_3 && var_r21_2 > 0) {
            spC[var_r31] = var_r23;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r21_2 != 0 && (s32) (var_r21_2 + arg6) > (s32) temp_r4) {
        for (var_r19 = 0; var_r19 < arg2; var_r19++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r19], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Torikku_Kodawarihatimaki_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    FightAiAllWazaValid *temp_r27;
    u8 var_r26;
    u8 var_r25;
    s16 var_r24;
    s16 temp_r23;
    s16 temp_r22;
    u8 var_r22;
    u8 temp_r3;
    s32 rnd;
    u8 var_r21;

    sp8 = 0;
    temp_r23 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    if (fightFloor_GetFightKindDorobouFlag(0) == 1) {
        return 0;
    }
    for (var_r25 = 0; var_r25 < arg2; var_r25++) {
        for (var_r22 = 0; var_r22 < 0x40U; var_r22++) {
            fightAi_InitAllWazaValidSub(&sp4C[var_r22]);
        }
        sp8 = 0;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x10FU, 0U, 0U);
        if (sp8 == 0) {
            return 0;
        }
        var_r24 = 0;
        for (var_r26 = 0; var_r26 < sp8; var_r26++) {
            temp_r27 = &sp4C[var_r26];
            temp_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23, arg0, arg1, arg3, -1);
            temp_r27->attacker[(s8) fightAi_getAnotherPokeNo(var_r25)] = 0;
            if (var_r24 < temp_r22) {
                spC[0] = var_r26;
                var_r24 = temp_r22;
                var_r21 = 1;
            } else if (var_r24 == temp_r22 && var_r24 > 0) {
                spC[var_r21] = var_r26;
                var_r21 += 1;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r21]]);
        temp_r3 = HSD_Rand() % 100;
        if (var_r24 != 0 && (s32) (var_r24 + arg6) > (s32) temp_r3) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + ((u32) var_r25 * 4 & 0x3FC)), 0U);
            fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
        }
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Horobinouta_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r27;
    u8 var_r26;
    u8 var_r25;
    s16 var_r24_2;
    s16 temp_r23;
    s16 var_r22;
    u8 var_r21;
    u8 var_r18;
    u8 var_r24;
    FightOutPokemon *temp_r4_2;
    u8 temp_r4;
    u8 sp8;
    s32 rnd;
    s32 temp_r18;

    var_r18 = 0;
    sp8 = 0;
    while (var_r18 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
        var_r18 += 1;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (var_r18 = 0; var_r18 < arg2; var_r18++) {
        temp_r4_2 = arg1[var_r18];
        if (temp_r4_2 != 0 && fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 6U) >= 1U) {
            return 0;
        }
    }
    for (var_r24 = 0; var_r24 < arg4; var_r24++) {
        temp_r4_2 = arg3[var_r24];
        if (temp_r4_2 != 0 && fightAi_GetTokuseiHaveFlag(arg0, temp_r4_2, 6U) >= 1U) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x99U, 1U, 0xC3U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0xC3U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xC3U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    temp_r23 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r24_2 = 0;
    for (var_r26 = 0; var_r26 < sp8; var_r26++) {
        temp_r27 = &sp4C[var_r26];
        var_r22 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r23, arg0, arg1, arg3, -1);
        for (var_r25 = 0; var_r25 < (u8) ai_allwaza_valid_work; var_r25++) {
            if (*(u16 *)((u8 *)temp_r27 + 0x10 + (var_r25 * 2 & 0x1FE)) == 0xC3 && (temp_r18 = var_r25 * 4, fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r27 + temp_r18), 7U) == 0) && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r27 + temp_r18), 5U) == 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r27 + temp_r18), 8U) == 0) {
                var_r22 = 0;
            }
        }
        if (var_r24_2 < var_r22) {
            spC[0] = var_r26;
            var_r24_2 = var_r22;
            var_r21 = 1;
        } else if (var_r24_2 == var_r22 && var_r24_2 > 0) {
            spC[var_r21] = var_r26;
            var_r21 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r21]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r24_2 != 0 && (s32) (var_r24_2 + arg6) > (s32) temp_r4) {
        for (var_r18 = 0; var_r18 < arg2; var_r18++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r18], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    u8 var_r24;
    u8 var_r23;
    s16 var_r22;
    s16 temp_r21;
    s16 var_r20;
    u8 var_r19;
    u8 var_r14;
    u8 temp_r3;
    u8 sp8;
    s32 rnd;
    s32 temp_r0;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r23 = 0; var_r23 < arg2; var_r23++) {
        for (var_r14 = 0; var_r14 < 0x40U; var_r14++) {
            fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        }
        sp8 = 0;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x11DU, 0U, 0U);
        if (sp8 == 0) {
            return 0;
        }
        temp_r0 = (u32) var_r23 * 2 & 0x1FE;
        temp_r25 = (u32) var_r23 * 4 & 0x3FC;
        var_r22 = 0;
        for (var_r24 = 0; var_r24 < sp8; var_r24++) {
            temp_r26 = var_r24 * 0x2C;
            temp_r27 = &sp4C[var_r24];
            var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
            temp_r27->attacker[(s8) fightAi_getAnotherPokeNo(var_r23)] = 0;
            if (*(u16 *)((u8 *)sp4C + temp_r0 + temp_r26 + 0x10) == 0x11D && fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26), 0x36U) != 2) {
                var_r20 = 0;
            }
            if (var_r22 < var_r20) {
                spC[0] = var_r24;
                var_r22 = var_r20;
                var_r19 = 1;
            } else if (var_r22 == var_r20 && var_r22 > 0) {
                spC[var_r19] = var_r24;
                var_r19 += 1;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r19]]);
        temp_r3 = HSD_Rand() % 100;
        if (var_r22 != 0 && (s32) (var_r22 + arg6) > (s32) temp_r3) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0U);
            fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
        }
    }
    return 0;
}

s32 fightAiCombo_Amaikaori_Hubuki_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    u8 var_r24;
    u8 var_r23;
    s16 var_r22;
    s16 temp_r21;
    s16 var_r20;
    u8 var_r19;
    u8 var_r14;
    u8 temp_r3;
    u16 temp_r0;
    u8 sp8;
    s32 rnd;
    s32 temp_r0b;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r23 = 0; var_r23 < arg2; var_r23++) {
        for (var_r14 = 0; var_r14 < 0x40U; var_r14++) {
            fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        }
        sp8 = 0;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xE6U, 0U, 0U);
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x171U, 0U, 0U);
        if (sp8 == 0) {
            return 0;
        }
        temp_r0b = (u32) var_r23 * 2 & 0x1FE;
        temp_r25 = (u32) var_r23 * 4 & 0x3FC;
        var_r22 = 0;
        for (var_r24 = 0; var_r24 < sp8; var_r24++) {
            temp_r26 = var_r24 * 0x2C;
            temp_r27 = &sp4C[var_r24];
            var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
            temp_r27->attacker[(s8) fightAi_getAnotherPokeNo(var_r23)] = 0;
            temp_r0 = *(u16 *)((u8 *)sp4C + temp_r0b + temp_r26 + 0x10);
            if ((temp_r0 == 0xE6 || temp_r0 == 0x171) && fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26)), 0x3BU) != 2 && fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26)), 0x9DU) != 2) {
                var_r20 = 0;
            }
            if (var_r22 < var_r20) {
                spC[0] = var_r24;
                var_r22 = var_r20;
                var_r19 = 1;
            } else if (var_r22 == var_r20 && var_r22 > 0) {
                spC[var_r19] = var_r24;
                var_r19 += 1;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r19]]);
        temp_r3 = HSD_Rand() % 100;
        if (var_r22 != 0 && (s32) (var_r22 + arg6) > (s32) temp_r3) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0x2AU);
            fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
        }
    }
    return 0;
}

s32 fightAiCombo_Amaikaori_Hubuki_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 var_r29;
    u8 var_r28;
    s16 var_r27;
    s16 temp_r26;
    s16 var_r25_2;
    u8 var_r25;
    u8 var_r24;
    u8 temp_r4;
    u8 sp8;
    s32 rnd;

    var_r25 = 0;
    sp8 = 0;
    for (var_r25 = 0; var_r25 < 0x40U; var_r25++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r25]);
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
    temp_r26 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r27 = 0;
    for (var_r29 = 0; var_r29 < sp8; var_r29++) {
        var_r25_2 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r29], temp_r26, arg0, arg1, arg3, -1);
        for (var_r28 = 0; var_r28 < (u8) ai_allwaza_valid_work; var_r28++) {
            if (sp4C[var_r29].defender[var_r28] != (FightOutPokemon *) sp4C[var_r29].defender[(s8) fightAi_getAnotherPokeNo(var_r28)] && (u8) sp4C[var_r29].kind[var_r28] != 2 && (u8) sp4C[var_r29].kind[(s8) fightAi_getAnotherPokeNo(var_r28)] != 2) {
                var_r25_2 = 0;
            }
            if (fightTrainerAiIsFightOutPokemonAvoidCntHikui(arg0, sp4C[var_r29].defender[var_r28]) == 1) {
                var_r25_2 = 0;
            }
        }
        if (var_r27 < var_r25_2) {
            spC[0] = var_r29;
            var_r27 = var_r25_2;
            var_r24 = 1;
        } else if (var_r27 == var_r25_2 && var_r27 > 0) {
            spC[var_r24] = var_r29;
            var_r24 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r24]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r27 != 0 && (s32) (var_r27 + arg6) > (s32) temp_r4) {
        for (var_r25 = 0; var_r25 < arg2; var_r25++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r25], 0x18U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Konran_DefDown_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r27;
    s32 temp_r26;
    s32 temp_r25;
    u8 var_r24;
    u8 var_r22;
    u8 var_r23;
    u8 var_r23_2;
    s16 var_r22_2;
    s16 temp_r21;
    s16 var_r20;
    u8 var_r19;
    u8 var_r14;
    FightOutPokemon *temp_r4;
    u8 temp_r3;
    u16 temp_r0;
    u8 sp8;
    s32 rnd;
    s32 temp_r0b;

    sp8 = 0;
    temp_r21 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r23 = 0;
    for (var_r22 = 0; var_r22 < arg4; var_r22++) {
        temp_r4 = arg3[var_r22];
        if (temp_r4 != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 9U) == 0) {
            var_r23 += 1;
        }
    }
    if (var_r23 == 0) {
        return 0;
    }
    for (var_r23_2 = 0; var_r23_2 < arg2; var_r23_2++) {
        for (var_r14 = 0; var_r14 < 0x40U; var_r14++) {
            fightAi_InitAllWazaValidSub(&sp4C[var_r14]);
        }
        sp8 = 0;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x12AU, 0U, 0U);
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xCFU, 0U, 0U);
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x6DU, 0U, 0U);
        if (sp8 == 0) {
            return 0;
        }
        temp_r0b = (u32) var_r23_2 * 2 & 0x1FE;
        temp_r25 = (u32) var_r23_2 * 4 & 0x3FC;
        var_r22_2 = 0;
        for (var_r24 = 0; var_r24 < sp8; var_r24++) {
            temp_r26 = var_r24 * 0x2C;
            temp_r27 = &sp4C[var_r24];
            var_r20 = fightAiCombo_GetAllWazaValueTable(temp_r27, temp_r21, arg0, arg1, arg3, -1);
            temp_r27->attacker[(s8) fightAi_getAnotherPokeNo(var_r23_2)] = 0;
            temp_r0 = *(u16 *)((u8 *)sp4C + temp_r0b + temp_r26 + 0x10);
            if ((temp_r0 == 0x12A || temp_r0 == 0xCF || temp_r0 == 0x6D) && fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26)), 0x27U) != 2 && fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26)), 0x2BU) != 2 && fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(*(FightOutPokemon **)((u8 *)sp4C + temp_r25 + temp_r26)), 0x67U) != 2) {
                var_r20 = 0;
            }
            if (var_r22_2 < var_r20) {
                spC[0] = var_r24;
                var_r22_2 = var_r20;
                var_r19 = 1;
            } else if (var_r22_2 == var_r20 && var_r22_2 > 0) {
                spC[var_r19] = var_r24;
                var_r19 += 1;
            }
        }
        rnd = HSD_Rand();
        fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r19]]);
        temp_r3 = HSD_Rand() % 100;
        if (var_r22_2 != 0 && (s32) (var_r22_2 + arg6) > (s32) temp_r3) {
            setComboFuncId__15FightOutPokemonFUc(*(FightOutPokemon **)((u8 *)arg1 + temp_r25), 0U);
            fightAi_CreateAction_FromAllWazaValid(arg0, arg5);
        }
    }
    return 0;
}

s32 fightAiCombo_Konran_DefDown_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    u8 temp_r22;
    u8 var_r21;
    u8 var_r20_2;
    u8 var_r19;
    u8 var_r20;
    s16 var_r19_2;
    s16 temp_r18;
    s16 var_r17;
    u8 var_r18;
    FightOutPokemon *temp_r4;
    u16 temp_r0;
    u8 temp_r4_2;
    s32 rnd;
    u8 var_r31;

    sp8 = 0;
    for (var_r18 = 0; var_r18 < 0x40U; var_r18++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r20 = 0;
    for (var_r19 = 0; var_r19 < arg4; var_r19++) {
        temp_r4 = arg3[var_r19];
        if (temp_r4 != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 9U) == 0) {
            var_r20 += 1;
        }
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
    temp_r18 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r19_2 = 0;
    for (var_r21 = 0; var_r21 < sp8; var_r21++) {
        var_r17 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r21], temp_r18, arg0, arg1, arg3, -1);
        for (var_r20_2 = 0; var_r20_2 < (u8) ai_allwaza_valid_work; var_r20_2++) {
            temp_r22 = var_r20_2;
            if (sp4C[var_r21].wazaId[var_r20_2] == 0x12A && fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r21].attacker[(s8) fightAi_getAnotherPokeNo(var_r20_2)], 0x14U) != 2 && fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, sp4C[var_r21].attacker[(s8) fightAi_getAnotherPokeNo(var_r20_2)]) != 8) {
                var_r17 = 0;
            }
            temp_r0 = sp4C[var_r21].wazaId[var_r20_2];
            if ((temp_r0 == 0xCF || temp_r0 == 0x6D) && sp4C[var_r21].defender[temp_r22] != sp4C[var_r21].defender[(s8) fightAi_getAnotherPokeNo(var_r20_2)] && sp4C[var_r21].kind[temp_r22] != 2 && (u8) sp4C[var_r21].kind[(s8) fightAi_getAnotherPokeNo(var_r20_2)] != 2) {
                var_r17 = 0;
            }
        }
        if (var_r19_2 < var_r17) {
            spC[0] = var_r21;
            var_r19_2 = var_r17;
            var_r31 = 1;
        } else if (var_r19_2 == var_r17 && var_r19_2 > 0) {
            spC[var_r31] = var_r21;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4_2 = HSD_Rand() % 100;
    if (var_r19_2 != 0 && (s32) (var_r19_2 + arg6) > (s32) temp_r4_2) {
        for (var_r18 = 0; var_r18 < arg2; var_r18++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r18], 0U);
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
    u8 var_r23;
    u8 var_r22;
    s16 var_r21;
    s16 var_r20;
    s16 var_r19_2;
    u8 var_r19;
    u8 var_r18;
    s32 temp_r18;
    s32 temp_r18_2;
    FightOutPokemon *temp_r4;
    u8 temp_r4_2;
    s32 rnd;
    u8 var_r31;

    var_r18 = 0;
    sp8 = 0;
    while (var_r18 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r18]);
        var_r18 += 1;
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (var_r18 = 0; var_r18 < arg2; var_r18++) {
        temp_r4 = arg1[var_r18];
        if (temp_r4 != 0 && fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 6U) == 2) {
            return 0;
        }
    }
    for (var_r18 = 0; var_r18 < arg4; var_r18++) {
        temp_r4 = arg3[var_r18];
        if (temp_r4 != 0 && fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 6U) >= 1U) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x99U, 1U, 0x99U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0x99U);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x78U, 1U, 0x78U);
    if (sp8 == 0) {
        return 0;
    }
    var_r20 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r19 = 0; var_r19 < arg4; var_r19++) {
        temp_r18 = (u32) var_r19 * 4 & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r18);
        if (temp_r4 != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r4, 7U) == 1) {
                var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2B1U);
            }
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 5U) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 8U) == 1) {
                var_r20 = fightTrainerAiAddValueByAddsubDataId((s32) var_r20, arg0, 0x2B2U);
            }
        }
    }
    var_r21 = 0;
    for (var_r23 = 0; var_r23 < sp8; var_r23++) {
        temp_r24 = &sp4C[var_r23];
        var_r19_2 = fightAiCombo_GetAllWazaValueTable(temp_r24, var_r20, arg0, arg1, arg3, -1);
        for (var_r22 = 0; var_r22 < (u8) ai_allwaza_valid_work; var_r22++) {
            temp_r18_2 = (var_r22 * 4) & 0x3FC;
            if (fightFloorCmpfightOutPokemonNimbleness(0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), temp_r24->attacker[(s8) fightAi_getAnotherPokeNo(var_r22)], 0U) == 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 7U) == 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 5U) == 0 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, *(FightOutPokemon **)((u8 *)temp_r24 + temp_r18_2), 8U) == 0) {
                var_r19_2 = 0;
            }
        }
        if (var_r21 < var_r19_2) {
            spC[0] = var_r23;
            var_r21 = var_r19_2;
            var_r31 = 1;
        } else if (var_r21 == var_r19_2 && var_r21 > 0) {
            spC[var_r31] = var_r23;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4_2 = HSD_Rand() % 100;
    if (var_r21 != 0 && (s32) (var_r21 + arg6) > (s32) temp_r4_2) {
        for (var_r18 = 0; var_r18 < arg2; var_r18++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r18], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Zisin_Mamoru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    u8 var_r31;
    u8 var_r30;
    s16 var_r29;
    s16 temp_r28;
    s16 var_r27;
    u8 var_r26;
    u8 var_r16;
    u8 var_r15_2;
    u8 var_r15;
    u16 temp_r0;
    u16 temp_r0_2;
    u8 temp_r4;
    s32 rnd;

    sp8 = 0;
    for (var_r15 = 0; var_r15 < 0x40U; var_r15++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
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
    for (var_r31 = 0; var_r31 < sp8; var_r31++) {
        var_r27 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r31], temp_r28, arg0, arg1, arg3, -1);
        for (var_r30 = 0; var_r30 < (u8) ai_allwaza_valid_work; var_r30++) {
            if (sp4C[var_r31].wazaId[var_r30] == 0xB6 && fightOutPokemon_GetLastUseWazaDataId(sp4C[var_r31].attacker[var_r30]) == 0xB6) {
                var_r27 = 0;
            }
            temp_r0 = sp4C[var_r31].wazaId[var_r30];
            if (temp_r0 == 0x59 || temp_r0 == 0xDE) {
                for (var_r15_2 = 0; var_r15_2 < arg4; var_r15_2++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r15_2], 2U) == 1) {
                        var_r27 -= 0xA;
                    }
                }
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp4C[var_r31].attacker[(s8) fightAi_getAnotherPokeNo(var_r30)], 2U) == 1) {
                    var_r27 = 0;
                }
                if (fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r31].attacker[(s8) fightAi_getAnotherPokeNo(var_r30)], 0x1AU) == 2) {
                    var_r27 = 0;
                }
            }
            temp_r0_2 = sp4C[var_r31].wazaId[var_r30];
            if (temp_r0_2 == 0x99 || temp_r0_2 == 0x78) {
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, sp4C[var_r31].attacker[var_r30], 6U) == 1 || fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, sp4C[var_r31].attacker[var_r30], 6U) == 1) {
                    var_r27 = 0;
                }
                for (var_r16 = 0; var_r16 < arg4; var_r16++) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r16], 7U) == 1) {
                        var_r27 -= 0x1E;
                    }
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r16], 5U) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r16], 8U) == 1) {
                        var_r27 -= 0xA;
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r16], 6U) >= 1U) {
                        var_r27 = 0;
                    }
                }
            }
        }
        if (var_r29 < var_r27) {
            spC[0] = var_r31;
            var_r29 = var_r27;
            var_r26 = 1;
        } else if (var_r29 == var_r27 && var_r29 > 0) {
            spC[var_r26] = var_r31;
            var_r26 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r26]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r29 != 0 && (s32) (var_r29 + arg6) > (s32) temp_r4) {
        for (var_r16 = 0; var_r16 < arg2; var_r16++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r16], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_DarkWeather_Whezaabooru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    u8 var_r22;
    u8 var_r21;
    FightOutPokemon *temp_r4;
    FightAiAllWazaValid spC[64];
    s16 var_r29;
    s16 temp_r3_3;
    u8 sp8;
    s32 rnd;

    var_r21 = 0;
    sp8 = 0;
    while (var_r21 < 0x40U) {
        fightAi_InitAllWazaValidSub(&spC[var_r21]);
        var_r21 += 1;
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
    for (var_r21 = 0; var_r21 < arg2; var_r21++) {
        temp_r4 = arg1[var_r21];
        if (temp_r4 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x4DU) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[var_r21], 0xDU) == 2)) {
            return 0;
        }
    }
    for (var_r21 = 0; var_r21 < arg4; var_r21++) {
        temp_r4 = arg3[var_r21];
        if (temp_r4 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x4DU) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r21], 0xDU) >= 1U)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, spC, &sp8, 1U, 0x16FU, 1U, 0x137U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, spC, &sp8, 0x16FU, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r29 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r22 = 0; var_r22 < arg2; var_r22++) {
        temp_r4 = arg1[var_r22];
        if (temp_r4 != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r4)) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId((s32) var_r29, arg0, 0x2AFU);
        }
    }
    for (var_r22 = 0; var_r22 < arg4; var_r22++) {
        temp_r4 = arg3[var_r22];
        if (temp_r4 != 0 && pokemonIsDarkPokemon(fightOutPokemonGetPokemonPtr(temp_r4)) == 1) {
            var_r29 = fightTrainerAiAddValueByAddsubDataId((s32) var_r29, arg0, 0x2AEU);
        }
    }
    temp_r3_3 = fightAiCombo_GetAllWazaMaxValueTable(spC, sp8, var_r29, arg0, arg1, arg3, arg5, 5);
    if (temp_r3_3 > 0 && (rnd = HSD_Rand(), (s32) (temp_r3_3 + arg6) > (s32) (u8) (rnd % 100))) {
        for (var_r21 = 0; var_r21 < arg2; var_r21++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r21], 0U);
        }
        return 1;
    }
    return 0;
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
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 var_r31;
    s16 var_r30;
    s16 temp_r29;
    s16 var_r28;
    u8 var_r27;
    u8 *temp_r20;
    s32 temp_r19;
    FightAiAllWazaValid *temp_r18;
    s32 temp_r17;
    u8 var_r16;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r15_3;
    u8 temp_r4;
    s32 spB4C;
    u8 sp8;
    s32 rnd;

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
        temp_r18->attacker[(s8) fightAi_getAnotherPokeNo(var_r31)] = 0;
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
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r27]]);
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
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 var_r22;
    u8 var_r21_2;
    u8 var_r21;
    s16 var_r20_2;
    u8 var_r20;
    s16 var_r19;
    s16 var_r18;
    u8 var_r18_2;
    u16 temp_r17;
    u8 var_r17;
    u8 var_r17_2;
    u16 temp_r0;
    u16 temp_r3;
    u8 temp_r4;
    s32 rnd;
    u8 var_r31;

    var_r17 = 0;
    sp8 = 0;
    for (var_r17 = 0; var_r17 < 0x40U; var_r17++) {
        fightAi_InitAllWazaValidSub(&sp64[var_r17]);
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
    for (var_r20 = 0; var_r20 < temp_r17; var_r20++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[var_r20], 0x16U) == 1) {
            var_r21 = 1;
            break;
        }
    }
    if (var_r21 == 0) {
        var_r19 = fightTrainerAiAddValueByAddsubDataId((s32) var_r19, arg0, 0x2C3U);
    }
    var_r20_2 = 0;
    for (var_r22 = 0; var_r22 < sp8; var_r22++) {
        for (var_r17_2 = 0; var_r17_2 < (u8) ai_allwaza_valid_work; var_r17_2++) {
            temp_r0 = sp64[var_r22].wazaId[var_r17_2];
            if (temp_r0 == 0x2E || temp_r0 == 0x12) {
                sp64[var_r22].defender[var_r17_2] = sp64[var_r22].attacker[(s8) fightAi_getAnotherPokeNo(var_r17_2)];
            }
        }
        var_r18 = fightAiCombo_GetAllWazaValueTable(&sp64[var_r22], var_r19, arg0, arg1, arg3, -1);
        for (var_r21_2 = 0; var_r21_2 < (u8) ai_allwaza_valid_work; var_r21_2++) {
            temp_r3 = sp64[var_r22].wazaId[var_r21_2];
            if (temp_r3 == 0x2E || temp_r3 == 0x12) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, sp64[var_r22].attacker[var_r21_2], sp64[var_r22].wazaId[var_r21_2], sp64[var_r22].defender[var_r21_2]) == 0) {
                    var_r18 = 0;
                }
            }
        }
        if (var_r20_2 < var_r18) {
            sp24[0] = var_r22;
            var_r20_2 = var_r18;
            var_r31 = 1;
        } else if (var_r20_2 == var_r18 && var_r20_2 > 0) {
            sp24[var_r31] = var_r22;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r20_2 != 0 && (s32) (var_r20_2 + arg6) > (s32) temp_r4) {
        for (var_r17 = 0; var_r17 < arg2; var_r17++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r17], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Dokudoku_Karagenki_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    u8 var_r20;
    u8 var_r21;
    s16 var_r19;
    s16 temp_r18;
    s16 var_r17;
    u8 var_r16;
    FightOutPokemon *temp_r16;
    u8 (*temp_r16_2)(FIGHT_TRAINER *, FightOutPokemon *, u16, FightOutPokemon *);
    u8 temp_r4;
    s32 rnd;
    u8 var_r31;

    sp8 = 0;
    for (var_r16 = 0; var_r16 < 0x40U; var_r16++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r16]);
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
    temp_r18 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r19 = 0;
    for (var_r21 = 0; var_r21 < sp8; var_r21++) {
        for (var_r20 = 0; var_r20 < (u8) ai_allwaza_valid_work; var_r20++) {
            if (sp4C[var_r21].wazaId[var_r20] == 0x107) {
                temp_r16 = sp4C[var_r21].attacker[var_r20];
                sp4C[var_r21].defender[(s8) fightAi_getAnotherPokeNo(var_r20)] = temp_r16;
            }
        }
        var_r17 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r21], temp_r18, arg0, arg1, arg3, -1);
        for (var_r20 = 0; var_r20 < (u8) ai_allwaza_valid_work; var_r20++) {
            if (sp4C[var_r21].wazaId[var_r20] == 0x107) {
                if (fightOutPokemonIsJoutaiKaragenki(sp4C[var_r21].attacker[var_r20]) == 1) {
                    var_r17 = 0;
                }
                if (fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r21].attacker[var_r20], 0x3EU) == 2 || fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r21].attacker[var_r20], 0x3FU) == 2) {
                    var_r17 += 0xA;
                }
                temp_r16_2 = wazaDB_GetFightTrainerAiWazaHitFuncPtr(sp4C[var_r21].wazaId[(s8) fightAi_getAnotherPokeNo(var_r20)]);
                if (temp_r16_2(arg0, sp4C[var_r21].attacker[(s8) fightAi_getAnotherPokeNo(var_r20)], sp4C[var_r21].wazaId[(s8) fightAi_getAnotherPokeNo(var_r20)], sp4C[var_r21].defender[(s8) fightAi_getAnotherPokeNo(var_r20)]) == 0) {
                    var_r17 = 0;
                }
            }
        }
        if (var_r19 < var_r17) {
            spC[0] = var_r21;
            var_r19 = var_r17;
            var_r31 = 1;
        } else if (var_r19 == var_r17 && var_r19 > 0) {
            spC[var_r31] = var_r21;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r19 != 0 && (s32) (var_r19 + arg6) > (s32) temp_r4) {
        for (var_r16 = 0; var_r16 < arg2; var_r16++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r16], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Konoyubitomare_StatusUp_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    FightAiAllWazaValid *temp_r21;
    u8 var_r20;
    u8 var_r19;
    u8 var_r18;
    s16 var_r17;
    s16 temp_r16;
    s16 var_r15_2;
    u8 var_r15;
    u8 temp_r4;
    u8 sp8;
    s32 rnd;
    u8 var_r31;

    var_r15 = 0;
    sp8 = 0;
    for (var_r15 = 0; var_r15 < 0x40U; var_r15++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r15]);
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
    for (var_r20 = 0; var_r20 < sp8; var_r20++) {
        temp_r21 = &sp4C[var_r20];
        var_r15_2 = fightAiCombo_GetAllWazaValueTable(temp_r21, temp_r16, arg0, arg1, arg3, -1);
        for (var_r19 = 0; var_r19 < (u8) ai_allwaza_valid_work; var_r19++) {
            for (var_r18 = 0; var_r18 < 0xEU; var_r18++) {
                if (*(u16 *)((u8 *)temp_r21 + 0x10 + (var_r19 * 2 & 0x1FE)) == *(u16 *)((u8 *)statusUpWazaTbl + (var_r18 * 6)) && fightTrainerAiIsFightOutPokemonAllAbiCntTakai(arg0, *(FightOutPokemon **)((u8 *)temp_r21 + ((var_r19 * 4) & 0x3FC))) == 1) {
                    var_r15_2 = 0;
                }
            }
        }
        if (var_r17 < var_r15_2) {
            spC[0] = var_r20;
            var_r17 = var_r15_2;
            var_r31 = 1;
        } else if (var_r17 == var_r15_2 && var_r17 > 0) {
            spC[var_r31] = var_r20;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r17 != 0 && (s32) (var_r17 + arg6) > (s32) temp_r4) {
        for (var_r15 = 0; var_r15 < arg2; var_r15++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r15], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Sukirusuwappu_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 var_r23;
    u8 var_r22;
    s16 var_r21;
    s16 temp_r20;
    s16 var_r19;
    u8 var_r18;
    u8 var_r17;
    u8 var_r16;
    u16 temp_r3;
    u8 temp_r4;
    u8 sp8;
    s32 rnd;
    u8 var_r31;

    sp8 = 0;
    for (var_r16 = 0; var_r16 < 0x40U; var_r16++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r16]);
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
    for (var_r23 = 0; var_r23 < sp8; var_r23++) {
        for (var_r18 = 0; var_r18 < (u8) ai_allwaza_valid_work; var_r18++) {
            if (sp4C[var_r23].wazaId[var_r18] == 0x11D) {
                sp4C[var_r23].defender[var_r18] = sp4C[var_r23].attacker[(s8) fightAi_getAnotherPokeNo(var_r18)];
            }
        }
        var_r19 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r23], temp_r20, arg0, arg1, arg3, -1);
        for (var_r22 = 0; var_r22 < (u8) ai_allwaza_valid_work; var_r22++) {
            if (sp4C[var_r23].wazaId[var_r22] != 0x11D) {
                if (fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r23].attacker[var_r22], 0x36U) != 2) {
                    var_r19 = 0;
                }
                if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, getFightPokemonPtr__15FightOutPokemonFv(sp4C[var_r23].attacker[var_r22]), 0x36U) == 0) {
                    var_r19 = 0;
                }
            }
            temp_r3 = sp4C[var_r23].wazaId[var_r22];
            if (temp_r3 == 0x11D) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, sp4C[var_r23].attacker[var_r22], sp4C[var_r23].wazaId[var_r22], sp4C[var_r23].defender[var_r22]) == 0) {
                    var_r19 = 0;
                }
                if (sp4C[var_r23].wazaId[(s8) fightAi_getAnotherPokeNo(var_r22)] == 0x11D) {
                    var_r19 = 0;
                }
            }
        }
        if (var_r21 < var_r19) {
            spC[0] = var_r23;
            var_r21 = var_r19;
            var_r31 = 1;
        } else if (var_r21 == var_r19 && var_r21 > 0) {
            spC[var_r31] = var_r23;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r21 != 0 && (s32) (var_r21 + arg6) > (s32) temp_r4) {
        for (var_r17 = 0; var_r17 < arg2; var_r17++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r17], 0x1DU);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Asanohizasi_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    s16 var_r30;
    u8 var_r29;
    u8 var_r21;
    u8 var_r20;
    s16 var_r19;
    s16 var_r18;
    u8 var_r17;
    u8 var_r5;
    s32 temp_r20;
    s32 temp_r20_2;
    s32 temp_r18;
    FightOutPokemon *temp_r4;
    u8 temp_r4_3;
    u8 sp8;
    s32 rnd;

    var_r17 = 0;
    sp8 = 0;
    while (var_r17 < 0x40U) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r17]);
        var_r17 += 1;
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
    for (var_r17 = 0; var_r17 < arg2; var_r17++) {
        temp_r20_2 = (var_r17 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg1 + temp_r20_2);
        if (temp_r4 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x4DU) == 2 || fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg1 + temp_r20_2), 0xDU) == 2)) {
            return 0;
        }
    }
    for (var_r17 = 0; var_r17 < arg4; var_r17++) {
        temp_r20 = (var_r17 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r20);
        if (temp_r4 != 0 && (fightAi_GetTokuseiHaveFlag(arg0, temp_r4, 0x4DU) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r20), 0xDU) >= 1U)) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xEAU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xECU);
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xF1U, 1U, 0xEBU);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xF1U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r30 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r17 = 0; var_r17 < arg4; var_r17++) {
        temp_r18 = (var_r17 * 4) & 0x3FC;
        temp_r4 = *(FightOutPokemon **)((u8 *)arg3 + temp_r18);
        if (temp_r4 != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, temp_r4, 0xAU) == 1) {
                var_r30 = fightTrainerAiAddValueByAddsubDataId((s32) var_r30, arg0, 0x2BAU);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, *(FightOutPokemon **)((u8 *)arg3 + temp_r18), 0x22U) >= 1U) {
                var_r30 = fightTrainerAiAddValueByAddsubDataId((s32) var_r30, arg0, 0x2BBU);
            }
        }
    }
    var_r19 = 0;
    for (var_r21 = 0; var_r21 < sp8; var_r21++) {
        for (var_r5 = 0; var_r5 < (u8) ai_allwaza_valid_work; var_r5++) {
            sp4C[var_r21].defender[var_r5] = sp4C[var_r21].attacker[var_r5];
        }
        var_r18 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r21], var_r30, arg0, arg1, arg3, -1);
        for (var_r20 = 0; var_r20 < (u8) ai_allwaza_valid_work; var_r20++) {
            if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(sp4C[var_r21].wazaId[var_r20])(arg0, sp4C[var_r21].attacker[var_r20], sp4C[var_r21].wazaId[var_r20], sp4C[var_r21].defender[var_r20]) == 0) {
                var_r18 = 0;
            }
            if (sp4C[var_r21].wazaId[var_r20] == 0xF1 && fightTrainerAiIsFightOutPokemonNokoriHpHikui(arg0, sp4C[var_r21].attacker[(s8) fightAi_getAnotherPokeNo(var_r20)]) == 0) {
                var_r18 = 0;
            }
        }
        if (var_r19 < var_r18) {
            spC[0] = var_r21;
            var_r19 = var_r18;
            var_r29 = 1;
        } else if (var_r19 == var_r18 && var_r19 > 0) {
            spC[var_r29] = var_r21;
            var_r29 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r29]]);
    temp_r4_3 = HSD_Rand() % 100;
    if (var_r19 != 0 && (s32) (var_r19 + arg6) > (s32) temp_r4_3) {
        for (var_r17 = 0; var_r17 < arg2; var_r17++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r17], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_StatusUp_Batontatti_1(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 var_r31;
    FightAiAllWazaValid *temp_r25;
    u8 *temp_r24;
    s32 temp_r23;
    s32 temp_r22;
    u8 var_r21;
    u8 var_r20;
    u8 var_r19;
    s16 var_r18;
    u8 temp_r17;
    s16 var_r16;
    u8 temp_r16;
    u8 temp_r15;
    u8 var_r15;
    u8 var_r15_2;
    u8 var_r15_3;
    u8 temp_r14;
    u8 temp_r4;
    u8 var_r4;
    s16 temp_r3;
    u16 temp_r3_2;
    s32 spB4C;
    u8 sp8;
    s32 rnd;

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
        temp_r25->attacker[(s8) fightAi_getAnotherPokeNo(var_r19)] = 0;
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
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
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
    u8 var_r22;
    u8 var_r21;
    s16 var_r20;
    s16 temp_r19;
    u8 var_r19;
    s16 var_r18_2;
    u8 var_r18;
    u8 temp_r4;
    FightOutPokemon *temp_r3_2;
    u16 temp_r3;
    u8 sp8;
    s32 rnd;
    u8 var_r31;

    var_r19 = 0;
    sp8 = 0;
    for (var_r19 = 0; var_r19 < 0x40U; var_r19++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r19]);
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (var_r19 = 0; var_r19 < (u8) ai_allwaza_valid_work; var_r19++) {
        temp_r3_2 = arg1[var_r19];
        if (temp_r3_2 != 0 && fightOutPokemon_GetAbicntPhyAtk(temp_r3_2) >= 0xCU) {
            return 0;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0xBBU, 1U, 0xF4U);
    fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, 0xBBU, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r20 = 0;
    temp_r19 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r22 = 0; var_r22 < sp8; var_r22++) {
        for (var_r18 = 0; var_r18 < (u8) ai_allwaza_valid_work; var_r18++) {
            if (sp4C[var_r22].wazaId[var_r18] == 0xF4) {
                sp4C[var_r22].defender[var_r18] = sp4C[var_r22].attacker[fightAi_getAnotherPokeNo(var_r18)];
            }
        }
        var_r18_2 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r22], temp_r19, arg0, arg1, arg3, -1);
        for (var_r21 = 0; var_r21 < (u8) ai_allwaza_valid_work; var_r21++) {
            temp_r3 = sp4C[var_r22].wazaId[var_r21];
            if (temp_r3 == 0xF4) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(temp_r3)(arg0, sp4C[var_r22].attacker[var_r21], sp4C[var_r22].wazaId[var_r21], sp4C[var_r22].defender[var_r21]) == 0) {
                    var_r18_2 = 0;
                }
            }
            if (sp4C[var_r22].wazaId[var_r21] == 0xBB && fightOutPokemonGetNowHpPercentage(sp4C[var_r22].attacker[var_r21]) <= 0x32) {
                var_r18_2 = 0;
            }
        }
        if (var_r20 < var_r18_2) {
            spC[0] = var_r22;
            var_r20 = var_r18_2;
            var_r31 = 1;
        } else if (var_r20 == var_r18_2 && var_r20 > 0) {
            spC[var_r31] = var_r22;
            var_r31 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r31]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r20 != 0 && (s32) (var_r20 + arg6) > (s32) temp_r4) {
        for (var_r19 = 0; var_r19 < arg2; var_r19++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r19], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Koraeru_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp9;
    u8 sp8;
    s16 temp_r14;
    s16 var_r29;
    s16 var_r30;
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
    s32 rnd;

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
        var_r31 = 0;
        var_r29 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r16], temp_r14, arg0, arg1, arg3, -1);
loop_50:
        if (var_r31 < (u8) ai_allwaza_valid_work) {
            if ((u16) sp4C[var_r16].wazaId[var_r31] == 0xCB) {
                var_r15 = 0;
loop_16:
                if (var_r15 < 4U) {
                    if (fightAi_GetTokuseiHaveFlag(arg0, sp4C[var_r16].attacker[var_r31], moukakeiTbl[var_r15]) == 2) {
                        var_r29 += 0xA;
                    }
                    var_r15 += 1;
                    goto loop_16;
                }
                if ((fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(sp4C[var_r16].attacker[var_r31]), 0xB3U) == 2) || (fightAi_GetWazaHaveFlag(arg0, getFightPokemonPtr__15FightOutPokemonFv(sp4C[var_r16].attacker[var_r31]), 0xAFU) == 2)) {
                    var_r29 += 0xA;
                }
                var_r15_2 = 0;
loop_24:
                if (var_r15_2 < 7U) {
                    if ((u16) statusUpKinomiTbl[var_r15_2] == fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, sp4C[var_r16].attacker[var_r31])) {
                        var_r29 += 0xA;
                    }
                    var_r15_2 += 1;
                    goto loop_24;
                }
                if (fightOutPokemon_GetLastUseWazaDataId(sp4C[var_r16].attacker[var_r31]) == 0xCB) {
                    var_r29 = 0;
                }
            }
            temp_r0 = sp4C[var_r16].wazaId[var_r31];
            if ((temp_r0 == 0x59) || (temp_r0 == 0xDE)) {
                var_r15_3 = 0;
loop_33:
                if ((s32) var_r15_3 < (s32) arg4) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r15_3], 2U) == 1) {
                        var_r29 -= 0xA;
                    }
                    var_r15_3 += 1;
                    goto loop_33;
                }
            }
            temp_r0_2 = sp4C[var_r16].wazaId[var_r31];
            if ((temp_r0_2 == 0x99) || (temp_r0_2 == 0x78)) {
                if ((fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, sp4C[var_r16].attacker[var_r31], 6U) == 1) || (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, sp4C[var_r16].attacker[var_r31], 6U) == 1)) {
                    var_r29 = 0;
                }
                var_r17 = 0;
loop_48:
                if ((s32) var_r17 < (s32) arg4) {
                    if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r17], 7U) == 1) {
                        var_r29 -= 0x1E;
                    }
                    if ((fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r17], 5U) == 1) || (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[var_r17], 8U) == 1)) {
                        var_r29 -= 0xA;
                    }
                    if (fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r17], 6U) >= 1U) {
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
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r28]]);
    temp_r4 = HSD_Rand() % 100;
    if ((var_r30 != 0) && ((s32) (var_r30 + sp8) > (s32) temp_r4)) {
        var_r15_4 = 0;
loop_62:
        if ((s32) var_r15_4 < (s32) arg2) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r15_4], 0U);
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
    FightAiAllWazaValid *temp_r31;
    u8 var_r30;
    u8 var_r29_3;
    u8 var_r29_2;
    s16 var_r28_2;
    s32 temp_r28;
    u8 var_r28;
    u8 var_r29;
    s16 temp_r27;
    u8 var_r27;
    s16 var_r26;
    u8 var_r25;
    u8 var_r21;
    FightOutPokemon *temp_r4;
    u8 temp_r4_2;
    u8 sp8;
    s32 rnd;

    var_r25 = 0;
    sp8 = 0;
    for (var_r27 = 0; var_r27 < 0x40U; var_r27++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r27]);
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    var_r29 = 0;
    for (var_r28 = 0; var_r28 < arg4; var_r28++) {
        temp_r4 = arg3[var_r28];
        if (temp_r4 != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, temp_r4, 8U) == 0) {
            var_r29 += 1;
        }
    }
    if (var_r29 == 0) {
        return 0;
    }
    for (var_r29_2 = 0; var_r29_2 < 6U; var_r29_2++) {
        temp_r28 = (var_r29_2 * 2) & 0x1FE;
        fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, *(u16 *)((u8 *)NemuraseWazaTbl + temp_r28), 1U, 0x8AU);
        fightAi_AllWazaValid_DelListFromSpeed(arg0, sp4C, &sp8, *(u16 *)((u8 *)NemuraseWazaTbl + temp_r28), 1U);
    }
    if (sp8 == 0) {
        return 0;
    }
    temp_r27 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    var_r28_2 = 0;
    for (var_r30 = 0; var_r30 < sp8; var_r30++) {
        temp_r31 = &sp4C[var_r30];
        var_r26 = fightAiCombo_GetAllWazaValueTable(temp_r31, temp_r27, arg0, arg1, arg3, -1);
        for (var_r29_3 = 0; var_r29_3 < (u8) ai_allwaza_valid_work; var_r29_3++) {
            if (temp_r31->defender[var_r29_3] != (FightOutPokemon *) temp_r31->defender[(s8) fightAi_getAnotherPokeNo(var_r29_3)] && (u8) temp_r31->kind[var_r29_3] != 2 && (u8) temp_r31->kind[(s8) fightAi_getAnotherPokeNo(var_r29_3)] != 2) {
                var_r26 = 0;
            }
        }
        if (var_r28_2 < var_r26) {
            spC[0] = var_r30;
            var_r28_2 = var_r26;
            var_r25 = 1;
        } else if (var_r28_2 == var_r26 && var_r28_2 > 0) {
            spC[var_r25] = var_r30;
            var_r25 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r25]]);
    temp_r4_2 = HSD_Rand() % 100;
    if (var_r28_2 != 0 && (s32) (var_r28_2 + arg6) > (s32) temp_r4_2) {
        for (var_r21 = 0; var_r21 < arg2; var_r21++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r21], 0U);
        }
        return 1;
    }
    return 0;
}





#ifdef __cplusplus
}
#endif

s32 fightAiCombo_Tedasuke_Iryoku_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    FightAiAllWazaValid sp4C[64];
    u8 spC[64];
    u8 sp8;
    s16 var_r31;
    u8 var_r30;
    u8 var_r19_2;
    u8 var_r19;
    u8 var_r18_2;
    u8 var_r18;
    s16 var_r17;
    u8 var_r17_2;
    s16 var_r16_2;
    FightAiAllWazaValid *temp_r16;
    u8 var_r16;
    u16 temp_r23_2;
    u8 temp_r4;
    s32 rnd;

    sp8 = 0;
    for (var_r16 = 0; var_r16 < 0x40U; var_r16++) {
        fightAi_InitAllWazaValidSub(&sp4C[var_r16]);
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp4C, &sp8, 1U, 0x10EU, 2U, 1U);
    if (sp8 == 0) {
        return 0;
    }
    var_r31 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r19 = 0; var_r19 < sp8; var_r19++) {
        for (var_r18 = 0; var_r18 < (u8) ai_allwaza_valid_work; var_r18++) {
            if (sp4C[var_r19].wazaId[var_r18] == 0x10E) {
                temp_r16 = &sp4C[var_r19];
                if (fightFloorCmpfightOutPokemonNimbleness(0, temp_r16->attacker[var_r18], temp_r16->defender[var_r18], 1U) == 1 && fightFloorCmpfightOutPokemonNimbleness(0, sp4C[var_r19].attacker[(s8) fightAi_getAnotherPokeNo(var_r18)], temp_r16->defender[var_r18], 1U) == 0) {
                    var_r31 = fightTrainerAiAddValueByAddsubDataId(var_r31, arg0, 0x2B0U);
                }
            }
        }
    }
    var_r17 = 0;
    for (var_r19_2 = 0; var_r19_2 < sp8; var_r19_2++) {
        var_r16_2 = fightAiCombo_GetAllWazaValueTable(&sp4C[var_r19_2], var_r31, arg0, arg1, arg3, -1);
        for (var_r18_2 = 0; var_r18_2 < (u8) ai_allwaza_valid_work; var_r18_2++) {
            if (sp4C[var_r19_2].wazaId[var_r18_2] != 0x10E) {
                temp_r23_2 = getHp__7PokemonCFv(getPokemonBuffPtr__12FightPokemonFv(getFightPokemonPtr__15FightOutPokemonFv(sp4C[var_r19_2].defender[var_r18_2])));
                if (fightTrainerAiWazaDoWazaDamageFunc(arg0, sp4C[var_r19_2].attacker[var_r18_2], sp4C[var_r19_2].wazaId[var_r18_2], sp4C[var_r19_2].defender[var_r18_2], 0U) > (s32) temp_r23_2) {
                    var_r16_2 = 0;
                }
                temp_r23_2 = getHp__7PokemonCFv(getPokemonBuffPtr__12FightPokemonFv(getFightPokemonPtr__15FightOutPokemonFv(sp4C[var_r19_2].defender[var_r18_2])));
                if ((fightTrainerAiWazaDoWazaDamageFunc(arg0, sp4C[var_r19_2].attacker[var_r18_2], sp4C[var_r19_2].wazaId[var_r18_2], sp4C[var_r19_2].defender[var_r18_2], 0U) * 0x96) / 100 < (s32) temp_r23_2) {
                    var_r16_2 = 0;
                }
            }
        }
        if (var_r17 < var_r16_2) {
            spC[0] = var_r19_2;
            var_r17 = var_r16_2;
            var_r30 = 1;
        } else if (var_r17 == var_r16_2 && var_r17 > 0) {
            spC[var_r30] = var_r19_2;
            var_r30 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp4C[spC[rnd % var_r30]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r17 != 0 && (s32) (var_r17 + arg6) > (s32) temp_r4) {
        for (var_r17_2 = 0; var_r17_2 < arg2; var_r17_2++) {
            setComboFuncId__15FightOutPokemonFUc(arg1[var_r17_2], 0U);
        }
        return 1;
    }
    return 0;
}

s32 fightAiCombo_Honoo_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s8 spB64;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 var_r30;
    u8 var_r14;
    u8 var_r29;
    s16 var_r28;
    u8 var_r26;
    s16 var_r27;
    u8 var_r25;
    u8 var_r24;
    FightAiAllWazaValid sp64[64];
    u8 var_r24_2;
    u8 var_r24_3;
    u16 temp_r23;
    u8 var_r23;
    u8 var_r20;
    u8 var_r15_2;
    u8 var_r15_4;
    s32 temp_r14;
    u8 var_r15_3;
    s32 temp_r14_2;
    s16 temp_r3;
    u8 var_r15;
    u8 temp_r4;
    s32 rnd;

    var_r15 = 0;
    sp8 = 0;
    for (var_r14 = 0; var_r14 < 0x40U; var_r14++) {
        fightAi_InitAllWazaValidSub(&sp64[var_r14]);
    }
    temp_r23 = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (var_r24 = 0; var_r24 < arg4; var_r24++) {
        if (arg3[var_r24] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r24], 0x17U) >= 1U) {
            return 0;
        }
    }
    for (var_r24_2 = 0; var_r24_2 < temp_r23; var_r24_2++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[var_r24_2], 0x12U) == 1) {
            var_r15 = 1;
            break;
        }
    }
    if (var_r15 == 0) {
        return 0;
    }
    var_r24_3 = 0;
    for (var_r15_2 = 0; var_r15_2 < arg4; var_r15_2++) {
        if (arg3[var_r15_2] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r15_2], 0x2AU) >= 1U) {
            var_r24_3 = 1;
            break;
        }
    }
    var_r23 = 0;
    for (var_r15_3 = 0; var_r15_3 < arg4; var_r15_3++) {
        if (arg3[var_r15_3] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[var_r15_3], 0x47U) >= 1U) {
            var_r23 = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 3U, 0xAU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    var_r28 = 0;
    temp_r14 = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (var_r30 = 0; var_r30 < sp8; var_r30++) {
        var_r26 = 0;
        var_r27 = fightAiCombo_GetAllWazaValueTable(&sp64[var_r30], temp_r14, arg0, arg1, arg3, -1);
        for (var_r29 = 0; var_r29 < (u8) ai_allwaza_valid_work; var_r29++) {
            if (fightTrainerAiGetWazaZokuseiDataId(arg0, sp64[var_r30].wazaId[var_r29], sp64[var_r30].attacker[var_r29]) == 0xA) {
                spB64 = fightAi_getAnotherPokeNo(var_r29);
                if (wazaIsWazaTypeId(sp64[var_r30].wazaId[var_r29], 1) == 1) {
                    var_r26 = 1;
                }
                if (fightTrainerAiGetWazaZokuseiDataId(arg0, sp64[var_r30].wazaId[(s8) fightAi_getAnotherPokeNo(var_r29)], sp64[var_r30].attacker[(s8) fightAi_getAnotherPokeNo(var_r29)]) == 0xA && wazaIsWazaTypeId(sp64[var_r30].wazaId[(s8) fightAi_getAnotherPokeNo(var_r29)], 1) == 1) {
                    var_r26 = 1;
                }
                if (var_r26 == 0) {
                    var_r27 = 0;
                }
                if (var_r24_3 == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[var_r30].attacker[(s8) fightAi_getAnotherPokeNo(var_r29)], 8U) == 1) {
                    var_r27 = 0;
                }
                if (var_r23 == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[var_r30].attacker[(s8) fightAi_getAnotherPokeNo(var_r29)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, sp64[var_r30].attacker[(s8) fightAi_getAnotherPokeNo(var_r29)], 0x1AU) != 2) {
                    var_r27 = 0;
                }
            }
        }
        if (var_r28 < var_r27) {
            sp24[0] = var_r30;
            var_r28 = var_r27;
            var_r25 = 1;
        } else if (var_r28 == var_r27 && var_r28 > 0) {
            sp24[var_r25] = var_r30;
            var_r25 += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % var_r25]]);
    temp_r4 = HSD_Rand() % 100;
    if (var_r28 != 0 && (s32) (var_r28 + arg6) > (s32) temp_r4) {
        for (var_r20 = 0; var_r20 < temp_r23; var_r20++) {
            temp_r14_2 = (var_r20 * 4) & 0x3FC;
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, *(FightPokemon **)((u8 *)spC + temp_r14_2), 0x12U) != 0) {
                temp_r3 = fightPokemon_GetEntryId(*(FightPokemon **)((u8 *)spC + temp_r14_2));
                if (temp_r3 >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) (u8) spB64], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) (u8) spB64], 0U, 9U, 0, &fight_action_data_turn, temp_r3);
                    for (var_r15_4 = 0; var_r15_4 < arg2; var_r15_4++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[var_r15_4], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Sunaarasi_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 cnt;
    u8 ties;
    u8 i0;
    u8 i;
    u8 found;
    u8 flagA;
    u8 flagB;
    s16 best;
    s16 value;
    s16 entry;
    s16 base;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    s32 off;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (i0 = 0; i0 < 0x40U; i0++) {
        fightAi_InitAllWazaValidSub(&sp64[i0]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 3) {
        return 0;
    }
    for (i = 0; i < arg2; i++) {
        if (arg1[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x4D) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0xD) >= 1U)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 8U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x17U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xC9U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        off = (i * 4) & 0x3FC;
        if (arg3[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 5U) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 8U) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 4U) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2C1);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 8U) >= 1U) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2C2);
            }
        }
    }
    best = 0;
    for (cnt = 0; cnt < sp8; cnt++) {
        cur = &sp64[cnt];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (cur->wazaId[j] == 0xC9) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 0) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = cnt;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = cnt;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (j = 0; j < irekaeNum; j++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[j], 8U) != 0) {
                entry = fightPokemon_GetEntryId(spC[j]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (i = 0; i < arg2; i++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[i], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Amagoi_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 cnt;
    u8 ties;
    u8 i0;
    u8 i;
    u8 found;
    u8 flagA;
    u8 flagB;
    s16 best;
    s16 value;
    s16 entry;
    s16 base;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    s32 off;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (i0 = 0; i0 < 0x40U; i0++) {
        fightAi_InitAllWazaValidSub(&sp64[i0]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 2) {
        return 0;
    }
    for (i = 0; i < arg2; i++) {
        if (arg1[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x4D) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0xD) >= 1U)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x21U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x17U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xF0U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        off = (i * 4) & 0x3FC;
        if (arg3[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 0xBU) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2BE);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2CU) >= 1U) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2BF);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x21U) >= 1U) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2C0);
            }
        }
    }
    best = 0;
    for (cnt = 0; cnt < sp8; cnt++) {
        cur = &sp64[cnt];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (cur->wazaId[j] == 0xF0) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x21U) == 0) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = cnt;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = cnt;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (j = 0; j < irekaeNum; j++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[j], 0x21U) != 0) {
                entry = fightPokemon_GetEntryId(spC[j]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (i = 0; i < arg2; i++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[i], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Nihonbare_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 cnt;
    u8 ties;
    u8 i0;
    u8 i;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    s16 value;
    s16 entry;
    s16 base;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    s32 off;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (i0 = 0; i0 < 0x40U; i0++) {
        fightAi_InitAllWazaValidSub(&sp64[i0]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    if (fightFloorGetNowTenkouDataId(0, 0) == 1) {
        return 0;
    }
    for (i = 0; i < arg2; i++) {
        if (arg1[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0x4D) == 2 || fightAi_GetTokuseiHaveFlag(arg0, arg1[i], 0xD) == 2)) {
            return 0;
        }
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x4D) >= 1U || fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0xD) >= 1U)) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x22U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x17U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xF1U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 0xAU) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2BC);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x22U) >= 1U) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2BD);
            }
        }
    }
    best = 0;
    for (cnt = 0; cnt < sp8; cnt++) {
        cur = &sp64[cnt];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (cur->wazaId[j] == 0xF1) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x22U) == 0) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = cnt;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = cnt;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (j = 0; j < irekaeNum; j++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[j], 0x22U) != 0) {
                entry = fightPokemon_GetEntryId(spC[j]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (i = 0; i < arg2; i++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[i], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Daibakuhatu_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 cnt;
    u8 ties;
    u8 i;
    u8 m;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    s16 value;
    s16 entry;
    s16 base;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    u16 wazaId;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    m = 0;
    sp8 = 0;
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, spC[i], 7U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x17U) >= 1U) {
            return 0;
        }
    }
    for (m = 0; m < arg2; m++) {
        if (arg1[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg1[m], 6U) == 2) {
            return 0;
        }
    }
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 6U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x99U, 0U, 0U);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x78U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 7U) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2B6);
            }
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 5U) == 1 || fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 8U) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2B7);
            }
        }
    }
    best = 0;
    for (cnt = 0; cnt < sp8; cnt++) {
        cur = &sp64[cnt];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            wazaId = cur->wazaId[j];
            if (wazaId == 0x99 || wazaId == 0x78) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 7U) == 1) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = cnt;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = cnt;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (j = 0; j < irekaeNum; j++) {
            if (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, spC[j], 7U) != 0) {
                entry = fightPokemon_GetEntryId(spC[j]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (m = 0; m < arg2; m++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[m], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Zisin_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 base;
    u8 ties;
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 i;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    s16 value;
    s16 entry;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    u16 wazaId;
    s32 rnd;
    u8 temp_r4;
    u8 m;

    found = 0;
    sp8 = 0;
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonZokuseiDataId(arg0, spC[i], 2U) == 1 || fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x1AU) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x17U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x59U, 0U, 0U);
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xDEU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0) {
            if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, arg3[i], 2U) == 1) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2B4);
            }
            if (fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x1AU) >= 1U) {
                base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2B5);
            }
        }
    }
    best = 0;
    for (i = 0; i < sp8; i++) {
        cur = &sp64[i];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            wazaId = cur->wazaId[j];
            if (wazaId == 0x59 || wazaId == 0xDE) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) == 2) {
                    value = 0;
                }
                if (fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 1) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = i;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x1AU) != 0 || fightTrainerAiIsFightPokemonZokuseiDataId(arg0, spC[i], 2U) != 0) {
                entry = fightPokemon_GetEntryId(spC[i]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (m = 0; m < arg2; m++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[m], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Hurahuradansu_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 base;
    u8 ties;
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 m;
    u8 i;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    u8 num;
    s16 value;
    s16 entry;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    FightAiAllWazaValid *cur;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    fightFloor_GetFightType(0);
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x14U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    num = 0;
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightTrainerAiIsFightOutPokemonJoutaiDataId(arg0, arg3[m], 9U) == 0) {
            num += 1;
        }
    }
    if (num == 0) {
        return 0;
    }
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x17U) >= 1U) {
            return 0;
        }
    }
    flagA = 0;
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0x12AU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x14U) >= 1U) {
            base = fightTrainerAiAddValueByAddsubDataId(base, arg0, 0x2B3);
        }
    }
    best = 0;
    for (i = 0; i < sp8; i++) {
        cur = &sp64[i];
        value = fightAiCombo_GetAllWazaValueTable(cur, base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (cur->wazaId[j] == 0x12A) {
                other = fightAi_getAnotherPokeNo(j);
                if (fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x14U) == 2) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, cur->attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = i;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x14U) != 0) {
                entry = fightPokemon_GetEntryId(spC[i]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (m = 0; m < arg2; m++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[m], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Ibaru_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 base;
    u8 ties;
    u8 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 cnt;
    u8 m;
    u8 i;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    s16 value;
    s16 entry;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    u16 wazaId;
    s32 off;
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x17U) >= 1U) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x14U) == 1 || fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(arg0, spC[i]) == 8) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (i = 0; i < arg4; i++) {
        if (arg3[i] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[i], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (m = 0; m < arg4; m++) {
        if (arg3[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[m], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xCFU, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    best = 0;
    for (cnt = 0; cnt < sp8; cnt++) {
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (sp64[cnt].wazaId[j] == 0xCF) {
                other = fightAi_getAnotherPokeNo(j);
                sp64[cnt].defender[j] = sp64[cnt].attacker[(s8) fightAi_getAnotherPokeNo(j)];
            }
        }
        value = fightAiCombo_GetAllWazaValueTable(&sp64[cnt], base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            wazaId = sp64[cnt].wazaId[j];
            if (wazaId == 0xCF) {
                if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(wazaId)(arg0, sp64[cnt].attacker[j], sp64[cnt].wazaId[j], sp64[cnt].defender[j]) == 0) {
                    value = 0;
                }
                if (fightTrainerAiIsFightOutPokemonTokuseiDataId(arg0, sp64[cnt].defender[(s8) fightAi_getAnotherPokeNo(j)], 0x14U) == 1 || fightTrainerAiGetFightOutPokemonSoubiItemSoubiDataId(arg0, sp64[cnt].defender[(s8) fightAi_getAnotherPokeNo(j)]) == 8) {
                    value = 0;
                }
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[cnt].attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[cnt].attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, sp64[cnt].attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = cnt;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = cnt;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (i = 0; i < irekaeNum; i++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x14U) != 0 || fightTrainerAiGetFightPokemonSoubiItemSoubiDataId(arg0, spC[i]) == 8) {
                entry = fightPokemon_GetEntryId(spC[i]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (m = 0; m < arg2; m++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[m], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Horobinouta_Irekae_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s32 other;
    u8 flagA;
    u8 flagB;
    u8 ties;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 m;
    u8 k;
    u8 i;
    s16 best;
    u8 found;
    s16 value;
    s16 base;
    s16 entry;
    u8 cnt;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (m = 0; m < arg2; m++) {
        if (arg1[m] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg1[m], 0x17U) == 2) {
            return 0;
        }
    }
    for (k = 0; k < arg4; k++) {
        if (arg3[k] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[k], 0x17U) >= 1U) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x17U) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (j = 0; j < arg4; j++) {
        if (arg3[j] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[j], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (j = 0; j < arg4; j++) {
        if (arg3[j] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[j], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xC3U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    best = 0;
    for (i = 0; i < sp8; i++) {
        value = fightAiCombo_GetAllWazaValueTable(&sp64[i], base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (sp64[i].wazaId[j] == 0xC3) {
                other = fightAi_getAnotherPokeNo(j);
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = i;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (m = 0; m < irekaeNum; m++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[m], 0x17U) != 0) {
                entry = fightPokemon_GetEntryId(spC[m]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (cnt = 0; cnt < arg2; cnt++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[cnt], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

s32 fightAiCombo_Horobinouta_Irekae2_2(FIGHT_TRAINER *arg0, FightOutPokemon **arg1, u16 arg2, FightOutPokemon **arg3, u16 arg4, FightAiAllWazaValid *arg5, u8 arg6) {
    s16 base;
    u8 ties;
    s32 other;
    u8 sp24[64];
    FightPokemon *spC[6];
    u8 sp8;
    u8 j;
    u8 m;
    u8 k;
    u8 i;
    u8 flagA;
    u8 flagB;
    s16 best;
    u8 found;
    s16 value;
    s16 entry;
    u8 cnt;
    u16 irekaeNum;
    FightAiAllWazaValid sp64[64];
    s32 rnd;
    u8 temp_r4;

    found = 0;
    sp8 = 0;
    for (m = 0; m < 0x40U; m++) {
        fightAi_InitAllWazaValidSub(&sp64[m]);
    }
    irekaeNum = fightTrainerGetIrekaeFightPokemonAry(arg0, spC);
    if ((u8) ai_allwaza_valid_work < 2U) {
        return 0;
    }
    if (arg2 < 2U) {
        return 0;
    }
    for (k = 0; k < arg4; k++) {
        if (arg3[k] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[k], 0x17U) >= 1U) {
            return 0;
        }
    }
    for (i = 0; i < irekaeNum; i++) {
        if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[i], 0x2BU) == 1) {
            found = 1;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    flagA = 0;
    for (j = 0; j < arg4; j++) {
        if (arg3[j] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[j], 0x2AU) >= 1U) {
            flagA = 1;
            break;
        }
    }
    flagB = 0;
    for (j = 0; j < arg4; j++) {
        if (arg3[j] != 0 && fightAi_GetTokuseiHaveFlag(arg0, arg3[j], 0x47U) >= 1U) {
            flagB = 1;
            break;
        }
    }
    fightAi_AllWazaValid_AddComboList(arg0, sp64, &sp8, 1U, 0xC3U, 0U, 0U);
    if (sp8 == 0) {
        return 0;
    }
    base = fightAiCombo_GetValidValue(arg1, arg2, arg3, arg4);
    best = 0;
    for (i = 0; i < sp8; i++) {
        value = fightAiCombo_GetAllWazaValueTable(&sp64[i], base, arg0, arg1, arg3, -1);
        for (j = 0; j < (u8) ai_allwaza_valid_work; j++) {
            if (sp64[i].wazaId[j] == 0xC3) {
                other = fightAi_getAnotherPokeNo(j);
                if (flagA == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 8U) == 1) {
                    value = 0;
                }
                if (flagB == 1 && fightTrainerAiIsFightOutPokemonZokuseiDataId(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 2U) == 0 && fightAi_GetTokuseiHaveFlag(arg0, sp64[i].attacker[(s8) fightAi_getAnotherPokeNo(j)], 0x1AU) != 2) {
                    value = 0;
                }
            }
        }
        if (best < value) {
            sp24[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            sp24[ties] = i;
            ties += 1;
        }
    }
    rnd = HSD_Rand();
    fightAi_CopyAllWazaValidTable(arg5, &sp64[sp24[rnd % ties]]);
    temp_r4 = HSD_Rand() % 100;
    if (best != 0 && (s32) (best + arg6) > (s32) temp_r4) {
        for (m = 0; m < irekaeNum; m++) {
            if (fightTrainerAiIsFightPokemonTokuseiDataId(arg0, spC[m], 0x2BU) != 0) {
                entry = fightPokemon_GetEntryId(spC[m]);
                if (entry >= 0) {
                    if (fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, arg5->attacker[(s8) other], 0U) != 0) {
                        return 0;
                    }
                    fightOutPokemonCreateFightAction(arg5->attacker[(s8) other], 0U, 9U, 0, &fight_action_data_turn, entry);
                    for (cnt = 0; cnt < arg2; cnt++) {
                        setComboFuncId__15FightOutPokemonFUc(arg1[cnt], 0U);
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

// NONMATCHING: retail selects an indeterminate tied index when every score is
// zero. Keep both random draws, but skip that undefined table copy.
extern "C" s32 fightAiCombo_Batontatti_Zikoanzi_2(FIGHT_TRAINER *trainer,
    FightOutPokemon **allies, u16 allyCount, FightOutPokemon **enemies,
    u16 enemyCount, FightAiAllWazaValid *out, u8 chance)
{
    FightAiAllWazaValid candidates[64];
    u8 indexes[64];
    FightPokemon *bench[6];
    u16 benchMoves[8];
    u16 enemyMoves[8];
    u8 ties = 0;
    FightOutPokemon *strongest = 0;
    s32 greatestDamage = 0;
    u8 candidateCount = 0;
    u32 fightType = fightFloor_GetFightType(0);
    u8 benchCount = fightTrainerGetIrekaeFightPokemonAry(trainer, bench);
    if (benchCount == 0) return 0;
    u8 immune = 0;
    u8 comparisons = 0;
    for (u8 p = 0; p < benchCount; ++p) {
        u8 moveCount = fightTrainerAiGetFightPokemonWazaDataIdAry(trainer, bench[p], benchMoves, 0, 1);
        for (u8 m = 0; m < moveCount; ++m) {
            for (u8 e = 0; e < enemyCount; ++e) {
                ++comparisons;
                u8 type = fightAi_GetWazaZokuseiData_ThinkWeatherBall(benchMoves[m], 0);
                u8 type0 = fightTrainerAiGetFightOutPokemonZokuseiDataId(trainer, enemies[e], 0);
                u8 type1 = fightTrainerAiGetFightOutPokemonZokuseiDataId(trainer, enemies[e], 1);
                if (zokuseiGetWazaJoutai(type, type0) == 0x43 ||
                    zokuseiGetWazaJoutai(type, type1) == 0x43) ++immune;
            }
        }
    }
    if (immune >= comparisons) return 0;
    u8 immuneEnemies = 0;
    for (u8 e = 0; e < enemyCount; ++e) {
        if (fightAi_GetTokuseiHaveFlag(trainer, enemies[e], 0x27) >= 1 ||
            fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[e], 7) == 1) ++immuneEnemies;
    }
    for (u8 a = 0; a < allyCount; ++a) {
        if (figthOutPokemonGetPokemonDataId(allies[a]) == 0x12E) {
            for (u8 e = 0; e < enemyCount; ++e) {
                u8 moveCount = fightTrainerAiGetFightOutPokemonWazaDataIdAry(trainer, enemies[e], enemyMoves, 0, 0);
                for (u8 m = 0; m < moveCount; ++m) {
                    s32 damage = fightTrainerAiWazaDoWazaDamageFunc(trainer, enemies[e], enemyMoves[m], allies[a], 0);
                    if (greatestDamage < damage && fightAi_GetTokuseiHaveFlag(trainer, enemies[e], 0x27) == 0 &&
                        fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[e], 7) == 0) {
                        greatestDamage = damage;
                        strongest = enemies[e];
                    }
                }
            }
        }
    }
    if (immuneEnemies >= enemyCount) {
        s16 base = fightAiCombo_GetValidValue(allies, allyCount, enemies, enemyCount);
        for (u8 a = 0; a < allyCount; ++a) {
            for (u8 i = 0; i < 64; ++i) fightAi_InitAllWazaValidSub(&candidates[i]);
            candidateCount = 0;
            fightAi_AllWazaValid_AddComboList(trainer, candidates, &candidateCount, 1, 0xB6, 0, 0);
            if (candidateCount == 0) return 0;
            s16 best = 0;
            for (u8 i = 0; i < candidateCount; ++i) {
                FightAiAllWazaValid *cur = &candidates[i];
                cur->attacker[(s8)fightAi_getAnotherPokeNo(a)] = 0;
                if (cur->wazaId[a] == 0xB6) cur->defender[a] = cur->attacker[a];
                s16 value = fightAiCombo_GetAllWazaValueTable(cur, base, trainer, allies, enemies, -1);
                u16 move = cur->wazaId[a];
                if (move == 0xB6) {
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(move)(trainer, cur->attacker[a], cur->wazaId[a], cur->defender[a]) == 0) value = 0;
                    if (fightAi_GetWazaHaveFlag(trainer, getFightPokemonPtr__15FightOutPokemonFv(cur->attacker[a]), 0xE2) != 2) value = 0;
                }
                if (best < value) {
                    indexes[0] = i;
                    best = value;
                    ties = 1;
                } else if (best == value && best > 0) {
                    indexes[ties++] = i;
                }
            }
            u16 random = HSD_Rand();
            if (ties != 0) fightAi_CopyAllWazaValidTable(out, &candidates[indexes[random % ties]]);
            u8 roll = HSD_Rand() % 100;
            if (best != 0 && best + chance > roll) {
                setComboFuncId__15FightOutPokemonFUc(allies[a], 0x15);
                fightAi_CreateAction_FromAllWazaValid(trainer, out);
            }
        }
        return 0;
    }
    for (u8 i = 0; i < 64; ++i) fightAi_InitAllWazaValidSub(&candidates[i]);
    if (ai_allwaza_valid_work < 2) return 0;
    if (allyCount < 2) return 0;
    fightAi_AllWazaValid_AddComboList(trainer, candidates, &candidateCount, 1, 0xFC, 1, 0xE);
    if (candidateCount == 0) return 0;
    s16 best = 0;
    s16 base = fightAiCombo_GetValidValue(allies, allyCount, enemies, enemyCount);
    for (u8 i = 0; i < candidateCount; ++i) {
        FightAiAllWazaValid *cur = &candidates[i];
        for (u8 a = 0; a < ai_allwaza_valid_work; ++a) {
            if (cur->wazaId[a] == 0xFC) {
                if (strongest != 0) cur->defender[a] = strongest;
                // Retail tests the corresponding enemy for type immunity here.
                if (fightAi_GetTokuseiHaveFlag(trainer, cur->defender[a], 0x27) >= 1 ||
                    fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[a], 7) == 1) {
                    FightOutPokemon *other = (FightOutPokemon *)fightTargetGetPtr(0xE, (FIGHT_TRAINER *)cur->defender[a], (u8)fightType);
                    if (other != 0 && fightAi_GetTokuseiHaveFlag(trainer, other, 0x27) == 0 &&
                        fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, other, 7) == 0) cur->defender[a] = other;
                }
            }
        }
        s16 value = fightAiCombo_GetAllWazaValueTable(cur, base, trainer, allies, enemies, -1);
        for (u8 a = 0; a < ai_allwaza_valid_work; ++a) {
            if (cur->wazaId[a] == 0xE &&
                fightAi_GetWazaHaveFlag(trainer, getFightPokemonPtr__15FightOutPokemonFv(cur->attacker[a]), 0xE2) != 2) value = 0;
            if (cur->wazaId[a] == 0xFC &&
                wazaDB_GetFightTrainerAiWazaHitFuncPtr(cur->wazaId[a])(trainer, cur->attacker[a], cur->wazaId[a], cur->defender[a]) == 0) value = 0;
        }
        if (best < value) {
            indexes[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            indexes[ties++] = i;
        }
    }
    u16 random = HSD_Rand();
    if (ties != 0) fightAi_CopyAllWazaValidTable(out, &candidates[indexes[random % ties]]);
    u8 roll = HSD_Rand() % 100;
    if (best != 0 && best + chance > roll) {
        for (u8 a = 0; a < allyCount; ++a) setComboFuncId__15FightOutPokemonFUc(allies[a], 0x15);
        return 1;
    }
    return 0;
}

// NONMATCHING: retail selects an indeterminate tied index when every score is
// zero. Keep both random draws, but skip that undefined table copy.
extern "C" s32 fightAiCombo_Batontatti_Nekodamasi_2(FIGHT_TRAINER *trainer,
    FightOutPokemon **allies, u16 allyCount, FightOutPokemon **enemies,
    u16 enemyCount, FightAiAllWazaValid *out, u8 chance)
{
    FightAiAllWazaValid candidates[64];
    u8 indexes[64];
    FightPokemon *bench[6];
    u16 benchMoves[8];

    u8 ties = 0;
    FightOutPokemon *strongest = 0;
    s32 greatestDamage = 0;
    u8 candidateCount = 0;
    u32 fightType = fightFloor_GetFightType(0);
    u8 benchCount = fightTrainerGetIrekaeFightPokemonAry(trainer, bench);
    if (benchCount == 0) return 0;
    u8 immune = 0;
    u8 comparisons = 0;
    for (u8 p = 0; p < benchCount; ++p) {
        u8 moveCount = fightTrainerAiGetFightPokemonWazaDataIdAry(trainer, bench[p], benchMoves, 0, 1);
        for (u8 m = 0; m < moveCount; ++m) {
            for (u8 e = 0; e < enemyCount; ++e) {
                ++comparisons;
                u8 type = fightAi_GetWazaZokuseiData_ThinkWeatherBall(benchMoves[m], 0);
                u8 type0 = fightTrainerAiGetFightOutPokemonZokuseiDataId(trainer, enemies[e], 0);
                u8 type1 = fightTrainerAiGetFightOutPokemonZokuseiDataId(trainer, enemies[e], 1);
                if (zokuseiGetWazaJoutai(type, type0) == 0x43 ||
                    zokuseiGetWazaJoutai(type, type1) == 0x43) ++immune;
            }
        }
    }
    if (immune >= comparisons) return 0;
    u8 immuneEnemies = 0;
    for (u8 e = 0; e < enemyCount; ++e) {
        if (fightAi_GetTokuseiHaveFlag(trainer, enemies[e], 0x27) >= 1 ||
            fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[e], 7) == 1) ++immuneEnemies;
    }
    for (u8 a = 0; a < allyCount; ++a) {
        if (figthOutPokemonGetPokemonDataId(allies[a]) == 0x12E) {
            for (u8 e = 0; e < enemyCount; ++e) {
                s16 entry = fightPokemon_GetEntryId(fightOutPokemon_GetFightPokemonPtr(enemies[e]));
                for (u8 m = 0; m < 4; ++m) {
                    s32 damage = fightTrainerAiWazaDoWazaDamageFunc(trainer, enemies[e], fightTrainer_GetEnemyStoreWazaData(trainer, entry, m), allies[a], 0);
                    if (greatestDamage < damage && fightAi_GetTokuseiHaveFlag(trainer, enemies[e], 0x27) == 0 &&
                        fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[e], 7) == 0) {
                        greatestDamage = damage;
                        strongest = enemies[e];
                    }
                }
                for (u8 m = 0; m < 8; ++m) {
                    s32 damage = fightTrainerAiWazaDoWazaDamageFunc(trainer, enemies[e], fightTrainer_GetEnemyExpectWazaData(trainer, entry, m), allies[a], 0);
                    if (greatestDamage < damage && fightAi_GetTokuseiHaveFlag(trainer, enemies[e], 0x27) == 0 &&
                        fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[e], 7) == 0) {
                        greatestDamage = damage;
                        strongest = enemies[e];
                    }
                }
            }
        }
    }
    if (immuneEnemies >= enemyCount) {
        s16 base = fightAiCombo_GetValidValue(allies, allyCount, enemies, enemyCount);
        for (u8 a = 0; a < allyCount; ++a) {
            for (u8 i = 0; i < 64; ++i) fightAi_InitAllWazaValidSub(&candidates[i]);
            candidateCount = 0;
            fightAi_AllWazaValid_AddComboList(trainer, candidates, &candidateCount, 1, 0xB6, 0, 0);
            if (candidateCount == 0) return 0;
            s16 best = 0;
            for (u8 i = 0; i < candidateCount; ++i) {
                FightAiAllWazaValid *cur = &candidates[i];
                cur->attacker[(s8)fightAi_getAnotherPokeNo(a)] = 0;
                if (cur->wazaId[a] == 0xB6) cur->defender[a] = cur->attacker[a];
                s16 value = fightAiCombo_GetAllWazaValueTable(cur, base, trainer, allies, enemies, -1);
                u16 move = cur->wazaId[a];
                if (move == 0xB6) {
                    if (wazaDB_GetFightTrainerAiWazaHitFuncPtr(move)(trainer, cur->attacker[a], cur->wazaId[a], cur->defender[a]) == 0) value = 0;
                    if (fightAi_GetWazaHaveFlag(trainer, getFightPokemonPtr__15FightOutPokemonFv(cur->attacker[a]), 0xE2) != 2) value = 0;
                }
                if (best < value) {
                    indexes[0] = i;
                    best = value;
                    ties = 1;
                } else if (best == value && best > 0) {
                    indexes[ties++] = i;
                }
            }
            u16 random = HSD_Rand();
            if (ties != 0) fightAi_CopyAllWazaValidTable(out, &candidates[indexes[random % ties]]);
            u8 roll = HSD_Rand() % 100;
            if (best != 0 && best + chance > roll) {
                setComboFuncId__15FightOutPokemonFUc(allies[a], 0x14);
                fightAi_CreateAction_FromAllWazaValid(trainer, out);
            }
        }
        return 0;
    }
    for (u8 i = 0; i < 64; ++i) fightAi_InitAllWazaValidSub(&candidates[i]);
    if (ai_allwaza_valid_work < 2) return 0;
    if (allyCount < 2) return 0;
    fightAi_AllWazaValid_AddComboList(trainer, candidates, &candidateCount, 1, 0xFC, 1, 0xE);
    if (candidateCount == 0) return 0;
    s16 best = 0;
    s16 base = fightAiCombo_GetValidValue(allies, allyCount, enemies, enemyCount);
    for (u8 i = 0; i < candidateCount; ++i) {
        FightAiAllWazaValid *cur = &candidates[i];
        for (u8 a = 0; a < ai_allwaza_valid_work; ++a) {
            if (cur->wazaId[a] == 0xFC) {
                if (strongest != 0) cur->defender[a] = strongest;
                // Retail tests the corresponding enemy for type immunity here.
                if (fightAi_GetTokuseiHaveFlag(trainer, cur->defender[a], 0x27) >= 1 ||
                    fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, enemies[a], 7) == 1) {
                    FightOutPokemon *other = (FightOutPokemon *)fightTargetGetPtr(0xE, (FIGHT_TRAINER *)cur->defender[a], (u8)fightType);
                    if (other != 0 && fightAi_GetTokuseiHaveFlag(trainer, other, 0x27) == 0 &&
                        fightTrainerAiIsFightOutPokemonZokuseiDataId(trainer, other, 7) == 0) cur->defender[a] = other;
                }
            }
        }
        s16 value = fightAiCombo_GetAllWazaValueTable(cur, base, trainer, allies, enemies, -1);
        for (u8 a = 0; a < ai_allwaza_valid_work; ++a) {
            if (cur->wazaId[a] == 0xE &&
                fightAi_GetWazaHaveFlag(trainer, getFightPokemonPtr__15FightOutPokemonFv(cur->attacker[a]), 0xE2) != 2) value = 0;
            if (cur->wazaId[a] == 0xFC &&
                wazaDB_GetFightTrainerAiWazaHitFuncPtr(cur->wazaId[a])(trainer, cur->attacker[a], cur->wazaId[a], cur->defender[a]) == 0) value = 0;
        }
        if (best < value) {
            indexes[0] = i;
            best = value;
            ties = 1;
        } else if (best == value && best > 0) {
            indexes[ties++] = i;
        }
    }
    u16 random = HSD_Rand();
    if (ties != 0) fightAi_CopyAllWazaValidTable(out, &candidates[indexes[random % ties]]);
    u8 roll = HSD_Rand() % 100;
    if (best != 0 && best + chance > roll) {
        for (u8 a = 0; a < allyCount; ++a) setComboFuncId__15FightOutPokemonFUc(allies[a], 0x14);
        return 1;
    }
    return 0;
}
