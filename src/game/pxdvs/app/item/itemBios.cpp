#include <dolphin/types.h>
#include "game/pxdvs/app/item/itemBiosLayout.hpp"

extern u8 item_param[]; extern u32 item_param_number;
extern u8 taste_data[]; extern u32 taste_data_number;
extern u8 item_soubi_data[]; extern u32 item_soubi_data_number;
extern u8 item_ball_data[]; extern u32 item_ball_data_number;
extern u8 item_waza_machine_no[]; extern u32 item_waza_machine_no_number;
extern u8 item_data_index[]; extern u32 *item_data_index_number;
extern u8 item_data_prime[]; extern u32 *item_data_prime_number;
#define ITEM_FIELD(T, P, O) (*((T *)((u8 *)(P) + (O))))

extern "C" {
s32 itemParamGetRecoverType(void *arg0) {
    u8 *data = (u8 *)arg0;
    s32 count = 0;
    s32 type = 0;

    if (data == NULL) {
        return 0x16;
    }
    if ((data[0] & 0x20) != 0 || (data[0] & 0x1E) != 0 ||
        (data[1] & 0xF0) != 0 || (data[1] & 0x0F) != 0 ||
        (data[2] & 0xF0) != 0 || (data[2] & 0x0F) != 0 ||
        (data[3] & 0x80) != 0) {
        return 0;
    }
    if ((data[0] & 0x40) != 0) {
        return 1;
    }
    if ((data[3] & 0x40) != 0) {
        return 2;
    }
    if ((data[3] & 0x20) != 0) { type = 3; ++count; }
    if ((data[3] & 0x10) != 0) { type = 4; ++count; }
    if ((data[3] & 0x08) != 0) { type = 5; ++count; }
    if ((data[3] & 0x04) != 0) { type = 6; ++count; }
    if ((data[3] & 0x02) != 0) { type = 7; ++count; }
    if ((data[3] & 0x01) != 0) { type = 8; ++count; }
    if ((data[0] & 0x80) != 0) { type = 9; ++count; }
    if (count > 1) {
        return 0xA;
    }
    if (count == 1) {
        return type;
    }
    if (data[0xA] != 0) return 0xB;
    if (data[9] != 0) return 0xC;
    if (data[8] != 0) return 0xD;
    if (data[0xF] != 0) return 0xE;
    if (data[0xE] != 0) return 0xF;
    if (data[0xD] != 0) return 0x10;
    if (data[0xC] != 0) return 0x11;
    if ((data[4] & 0x10) != 0) return 0x12;
    if ((data[4] & 0x80) != 0) return 0x13;
    if ((data[4] & 0x08) != 0) return 0x14;
    if ((data[4] & 0x20) != 0) return 0x15;
    return data[0xB] != 0 ? 0x15 : 0x16;
}
s8 itemParamGetFriend3Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend3Up;
}


s8 itemParamGetFriend2Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend2Up;
}


s8 itemParamGetFriend1Up(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (s8) ((ItemParamRecord *)arg0)->friend1Up;
}


s32 itemParamGetPPMaxFullFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 3U) & 1) != 0;
}


u8 itemParamGetSpAttackEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->spAttackEffortUp;
}


u8 itemParamGetSpDefenceEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->spDefenceEffortUp;
}


u8 itemParamGetQuickEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->quickEffortUp;
}


u8 itemParamGetDefenceEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->defenceEffortUp;
}


s32 itemParamGetEvolutionFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 4U) & 1) != 0;
}


u8 itemParamGetPPUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->ppUp;
}


s32 itemParamGetPPSelectFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 5U) & 1) != 0;
}


u8 itemParamGetHPUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->hpUp;
}


s32 itemParamGetReviveFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 6U) & 1) != 0;
}


u8 itemParamGetAttackEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->attackEffortUp;
}


u8 itemParamGetHPEffortUp(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemParamRecord *)arg0)->hpEffortUp;
}


s32 itemParamGetPPMaxUpFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x4) >> 7U) & 1) != 0;
}


s32 itemParamGetConfuseFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (ITEM_FIELD(u8, arg0, 0x3) & 1) != 0;
}


s32 itemParamGetParalyzeFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 1U) & 1) != 0;
}


s32 itemParamGetFreezeFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 2U) & 1) != 0;
}


s32 itemParamGetBurnFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 3U) & 1) != 0;
}


s32 itemParamGetPoisonFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 4U) & 1) != 0;
}


s32 itemParamGetSleepFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 5U) & 1) != 0;
}


s32 itemParamGetLevelUpFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 6U) & 1) != 0;
}


s32 itemParamGetGuardFlag(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) ITEM_FIELD(u8, arg0, 0x3) >> 7U) & 1) != 0;
}


s32 itemParamGetSpAttackUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ITEM_FIELD(u8, arg0, 0x2) & 0xF;
}


s32 itemParamGetHitUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) ITEM_FIELD(u8, arg0, 0x2) >> 4U) & 0xF;
}


s32 itemParamGetQuickUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ITEM_FIELD(u8, arg0, 0x1) & 0xF;
}


s32 itemParamGetDefenceUp(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) ITEM_FIELD(u8, arg0, 0x1) >> 4U) & 0xF;
}


s32 itemParamGetAttackUp(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((u8) *arg0 >> 1U) & 0xF;
}


s32 itemParamGetCriticalFlag(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) *arg0 >> 5U) & 1) != 0;
}


s32 itemParamGetMeromeroFlag(u8 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return (((u8) *arg0 >> 7U) & 1) != 0;
}

void *itemParamGetPtr(u8 arg0) {
    if (arg0 >= (u32) item_param_number) {
        return NULL;
    }
    return item_param + ((arg0 * 0x10) & 0xFF0);
}


s8 tasteDataGetAisyou(u32 arg0, u16 arg1) {
    if (arg0 == 0U) {
        return 0;
    }
    if (arg1 >= 0x19U) {
        return 0;
    }
    return (s8) ITEM_FIELD(s8, (u8 *)arg0 + arg1, 0x4);
}


s32 tasteDataGetNigateMsgDataId(s32 *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return *arg0;
}

void *tasteDataGetPtr(u16 arg0) {
    if (arg0 >= (u32) taste_data_number) {
        return NULL;
    }
    return taste_data + ((arg0 << 5) & 0x1FFFE0);
}


u16 itemSoubiDataBiosGetFightKoukaDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}

void *itemSoubiDataBiosGetPtr(u16 arg0) {
    if (arg0 >= (u32) item_soubi_data_number) {
        return NULL;
    }
    return item_soubi_data + ((arg0 * 2) & 0x1FFFE);
}


void itemBiosSetNum(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ITEM_FIELD(s16, arg0, 0x2) = arg1;
    }
}


void itemBiosSetItemDataId(s16 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemBallDataBiosSetFightKoukaDataId(s16 *arg0, s16 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemDataBiosSetBuff(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->buff = arg1;
    }
}


void itemDataBiosSetUseFriend(u32 arg0, u16 arg1, s8 arg2) {
    if ((arg0 != 0U) && (arg1 < 3U)) {
        ((ItemDataRecord *)((u8 *)arg0 + arg1))->useFriend[0] = arg2;
    }
}


void itemDataBiosSetFightUseKoukaDataId(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->fightKoukaDataId = arg1;
    }
}


void itemDataBiosSetItemSoubiDataId(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->itemSoubiDataId = arg1;
    }
}


void itemDataBiosSetDoc(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->doc = arg1;
    }
}


void itemDataBiosSetUseful(void *arg0, s8 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->useful = arg1;
    }
}


void itemDataBiosSetImportant(void *arg0, s8 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->important = arg1;
    }
}


void itemDataBiosSetPrice(void *arg0, s16 arg1) {
    if (arg0 != NULL) {
        ITEM_FIELD(s16, arg0, 0x6) = arg1;
    }
}


void itemDataBiosSetKind(s8 *arg0, s8 arg1) {
    if (arg0 != NULL) {
        *arg0 = arg1;
    }
}


void itemDataBiosSetName(void *arg0, s32 arg1) {
    if (arg0 != NULL) {
        ((ItemDataRecord *)arg0)->name = arg1;
    }
}


u16 itemBiosGetNum(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0x2);
}


u16 itemBiosGetItemDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}


s32 itemBallDataBiosGetSnatchSnatchWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[10];
}


s32 itemBallDataBiosGetSnatchShakeWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[9];
}


s32 itemBallDataBiosGetSnatchPokeoutWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[8];
}


s32 itemBallDataBiosGetSnatchMissWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[7];
}


s32 itemBallDataBiosGetSnatchBalllandWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[6];
}


s32 itemBallDataBiosGetSnatchAttackWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[5];
}


s32 itemBallDataBiosGetThrowWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[4];
}


s32 itemBallDataBiosGetDowninWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[3];
}


s32 itemBallDataBiosGetOutWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[2];
}


s32 itemBallDataBiosGetOpenWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[1];
}


s32 itemBallDataBiosGetInWzxDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemBallDataRecord *)arg0)->effectIds[0];
}


u16 itemBallDataBiosGetFightKoukaDataId(u16 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}

void *itemBallDataBiosGetPtr(u16 arg0) {
    if (arg0 >= (u32) item_ball_data_number) {
        return NULL;
    }
    return item_ball_data + ((arg0 << 6) & 0x3FFFC0);
}


s32 itemDataBiosGetBattleUseFunc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->battleUseFunc;
}


s32 itemDataBiosGetFieldUseFunc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->fieldUseFunc;
}


u8 itemDataBiosGetItemEffectParam(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->effectParam;
}


s32 itemDataBiosGetBuff(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->buff;
}


s8 itemDataBiosGetUseFriend(u32 arg0, u16 arg1) {
    if (arg0 == 0U) {
        return 0;
    }
    if (arg1 >= 3U) {
        return 0;
    }
    return ((ItemDataRecord *)((u8 *)arg0 + arg1))->useFriend[0];
}


u8 itemDataBiosGetKinomiNo(u16 arg0) {
    if ((arg0 < 0x85U) || (arg0 > 0xAFU)) {
        return 0xFFU;
    }
    return (u8) (arg0 - 0x85);
}


u8 itemDataBiosGetHidenMachineNo(void *arg0) {
    u8 var_r0;

    if (arg0 == NULL) {
        var_r0 = 0;
    } else if ((u8) ((ItemDataRecord *)arg0)->kind != 4) {
        var_r0 = 0xFF;
    } else {
        var_r0 = ITEM_FIELD(u8, arg0, 0x18);
    }
    if (var_r0 == 0xFF) {
        return 0xFFU;
    }
    if ((var_r0 < 0x32U) || (var_r0 >= (u32) item_waza_machine_no_number)) {
        return 0xFFU;
    }
    return (u8) (var_r0 - 0x32);
}


u16 itemDataBiosGetWazaIDByWazaMachineNo(u8 arg0) {
    if (arg0 >= (u32) item_waza_machine_no_number) {
        return 0U;
    }
    return ITEM_FIELD(u16, item_waza_machine_no + ((arg0 * 8) & 0x7F8), 4);
}


u8 itemDataBiosGetWazaMachineNo(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    if ((u8) ((ItemDataRecord *)arg0)->kind != 4) {
        return 0xFFU;
    }
    return (u8) ((ItemDataRecord *)arg0)->buff;
}


u16 itemDataBiosGetFightUseKoukaDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0xC);
}


u16 itemDataBiosGetItemSoubiDataId(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ITEM_FIELD(u16, arg0, 0xA);
}


s32 itemDataBiosGetDoc(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->doc;
}


s32 itemDataBiosGetDeposit(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->deposit != 0;
}


s32 itemDataBiosGetUseful(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->useful != 0;
}


s32 itemDataBiosGetImportant(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->important != 0;
}


u16 itemDataBiosGetCoupon(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->coupon;
}


u16 itemDataBiosGetPrice(void *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return ((ItemDataRecord *)arg0)->price;
}


u8 itemDataBiosGetKind(u8 *arg0) {
    if (arg0 == NULL) {
        return 0U;
    }
    return *arg0;
}


s32 itemDataBiosCheckExportable(void *arg0) {
    s32 temp_cr0_eq;
    u8 var_r0;

    temp_cr0_eq = arg0 == NULL;
    if (temp_cr0_eq != 0) {
        return 0;
    }
    if (temp_cr0_eq != 0) {
        var_r0 = 0;
    } else {
        var_r0 = ((ItemDataRecord *)arg0)->important != 0;
    }
    if (var_r0 != 0) {
        return 0;
    }
    return 1;
}


s32 itemDataBiosCheckImportable(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->name != 0;
}


s32 itemDataBiosGetName(void *arg0) {
    if (arg0 == NULL) {
        return 0;
    }
    return ((ItemDataRecord *)arg0)->name;
}


s32 itemDataBiosGetPtr(u16 arg0) {
    u16 temp_r3;

    if (arg0 >= (u32) *item_data_index_number) {
        return 0;
    }
    temp_r3 = *(item_data_index + ((arg0 * 2) & 0x1FFFE));
    if (temp_r3 >= (u32) *item_data_prime_number) {
        return 0;
    }
    return (s32)(item_data_prime + (temp_r3 * 0x28));
}

}
