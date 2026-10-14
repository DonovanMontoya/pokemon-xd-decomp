#include <game/pxdvs/app/waza/wazaStatusAPI.hpp>
#pragma dont_inline on
extern "C" {
u8 wazaCheckDarkWaza(u32 identifier) {
    switch ((u16)identifier) {
    case 0x164:
    case 0x165:
    case 0x166:
    case 0x167:
    case 0x168:
    case 0x169:
    case 0x16a:
    case 0x16b:
    case 0x16c:
    case 0x16d:
    case 0x16e:
    case 0x16f:
    case 0x170:
    case 0x171:
    case 0x172:
    case 0x173:
    case 0x174:
    case 0x175:
        return 1;
    default:
        return 0;
    }
}

s32 wazaGetWazaTypeIdName(u8 type) {
    s32 message = 0;
    switch (type) {
    case 0: message = 0x0; break;
    case 1: message = 0xec50; break;
    case 2: message = 0xec51; break;
    case 3: message = 0xec52; break;
    case 4: message = 0xed09; break;
    case 5: message = 0xec53; break;
    case 6: message = 0xec54; break;
    case 7: message = 0xec55; break;
    case 8: message = 0xec56; break;
    case 9: message = 0xec57; break;
    case 10: message = 0xec58; break;
    case 13: message = 0xec59; break;
    }
    return message;
}

s32 wazaIsWazaTypeId(u32 identifier, u8 type) {
    u8 index;

    if (((u16)identifier == 0) && ((u16)identifier == 0x163) && ((u16)identifier == 0x176)) {
        return 0;
    }
    if (type == 0) {
        return 0;
    }
    for (index = 0; index < 3; ++index) {
        if (type == wazaDB_GetTypeId(identifier, index)) return 1;
    }
    return 0;
}

u8 wazaGetMaxPP(u32 identifier, u8 ppUps) {
    u8 basePP;

    basePP = wazaDB_GetPp(identifier);
    return (u8) (basePP + ((ppUps * (basePP * 0x14)) / 100));
}

void wazaSetStatus(void *target, u32 identifier, u16 status, u16 element, u32 value) {
    WazaDataRecord *data;

    data = (WazaDataRecord*)target;
    if (status != 0) {
        if (status >= 0x35U) {
            return;
        }
        if (status < 0x25U) {
            data = wazaDataBiosGetPtr(identifier);
            if (data == NULL) {
                return;
            }
            goto block_7;
        }
        if (data != NULL) {
block_7:
            switch (status) {
            case 1:
                wazaDataBiosSetName(data, value);
                return;
            case 2:
                wazaDataBiosSetPp(data, (u8) value);
                return;
            case 3:
                wazaDataBiosSetZokuseiDataId(data, (u8) value);
                return;
            case 4:
                wazaDataBiosSetPri(data, (s8) value);
                return;
            case 5:
                wazaDataBiosSetRangeId(data, (u8) value);
                return;
            case 6:
                wazaDataBiosSetAvg(data, (u8) value);
                return;
            case 7:
                wazaDataBiosSetIryoku(data, (s16) value);
                return;
            case 8:
                wazaDataBiosSetFightKoukaDataId(data, (u16) value);
                return;
            case 9:
                wazaDataBiosSetSeqId(data, (u16) value);
                return;
            case 10:
                wazaDataBiosSetFightAttackTunagiMsgId(data, (u32) (u16) value);
                return;
            case 11:
                wazaDataBiosSetFightAttackMsgId(data, (u32) (u16) value);
                return;
            case 12:
                wazaDataBiosSetAddFightKoukaAvg(data, (u8) value);
                return;
            case 13:
                wazaDataBiosSetDageki(data, (u8) value);
                return;
            case 14:
                wazaDataBiosSetMamoru(data, (u8) value);
                return;
            case 15:
                wazaDataBiosSetMajikku(data, (u8) value);
                return;
            case 16:
                wazaDataBiosSetYokodori(data, (u8) value);
                return;
            case 17:
                wazaDataBiosSetOumugaesi(data, (u8) value);
                return;
            case 18:
                wazaDataBiosSetOujanosirusi(data, (u8) value);
                return;
            case 19:
                wazaDataBiosSetYubiwohuru(data, (u8) value);
                return;
            case 20:
                wazaDataBiosSetMonomane(data, (u8) value);
                return;
            case 21:
                wazaDataBiosSetNekonote(data, (u8) value);
                return;
            case 22:
                wazaDataBiosSetNegoto(data, (u8) value);
                return;
            case 23:
                wazaDataBiosSetBouon(data, (u8) value);
                return;
            case 24:
                wazaDataBiosSetPressure(data, (u8) value);
                return;
            case 25:
                wazaDataBiosSetHidenFlag(data, (u8) value);
                return;
            case 26:
                wazaDataBiosSetTypeId(data, element, (u8) value);
                return;
            case 27:
                wazaDataBiosSetRiskFlag(data, (u8) value);
                return;
            case 28:
                wazaDataBiosSetFightTrainerAiWazaValueFuncPtr(data, (void *) value);
                return;
            case 29:
                wazaDataBiosSetFightTrainerAiWazaHitFuncPtr(data, (void *) value);
                return;
            case 30:
                wazaDataBiosSetFightTrainerAiWazaDamageFuncPtr(data, (void *) value);
                return;
            case 32:
                wazaDataBiosSetFightWazaWzxTypeFuncPtr(data, (void *) value);
                return;
            case 33:
                wazaDataBiosSetFightWazaWzxVariationFuncPtr(data, (void *) value);
                return;
            case 31:
                wazaDataBiosSetWazawzxdataId(data, value);
                return;
            case 34:
                wazaDataBiosSetDoc(data, value);
                return;
            case 38:
                fightWazaBiosSetWazaBanme((FightWazaRecord *) data, (s8) value);
                return;
            case 39:
                fightWazaBiosSetMotoWazaDataId((FightWazaRecord *) data, (u16) value);
                return;
            case 40:
                fightWazaBiosSetUseWazaDataId((FightWazaRecord *) data, (u16) value);
                return;
            case 41:
                fightWazaBiosSetTargetDataId((FightWazaRecord *) data, (u16) value);
                return;
            case 43:
                fightWazaBiosSetCritical((FightWazaRecord *) data, (u8) value);
                return;
            case 44:
                fightWazaBiosSetDamageValue((FightWazaRecord *) data, (u8) value);
                return;
            case 45:
                fightWazaBiosSetDamage((FightWazaRecord *) data, value);
                return;
            case 46:
                fightWazaBiosSetHitDamage((FightWazaRecord *) data, value);
                return;
            case 47:
                fightWazaBiosSetIryoku((FightWazaRecord *) data, (u16) value);
                return;
            case 48:
                fightWazaBiosSetZokusei((FightWazaRecord *) data, (u16) value);
                return;
            case 49:
                fightWazaBiosSetKaisuu((FightWazaRecord *) data, (u8) value);
                return;
            case 50:
                fightWazaBiosSetAutoMakeFlag((FightWazaRecord *) data, (u8) value);
                break;
            }
        }
    }
}

u32 wazaGetStatus(void *target, u32 identifier, u16 status, u16 element) {
    WazaDataRecord *data;

    data = (WazaDataRecord*)target;
    if ((status == 0) || (status >= 0x35U)) {
        return 0U;
    }
    if (status < 0x25U) {
        data = wazaDataBiosGetPtr(identifier);
        if (data == NULL) {
            return 0U;
        }
        goto block_8;
    }
    if (data == NULL) {
        return 0U;
    }
block_8:
    switch (status) {
    case 0x1:
        return wazaDataBiosGetName(data);
    case 0x2:
        return (u32) wazaDataBiosGetPp(data);
    case 0x3:
        return (u32) wazaDataBiosGetZokuseiDataId(data);
    case 0x4:
        return (u32) wazaDataBiosGetPri(data);
    case 0x5:
        return (u32) wazaDataBiosGetRangeId(data);
    case 0x6:
        return (u32) wazaDataBiosGetAvg(data);
    case 0x7:
        return (u32) wazaDataBiosGetIryoku(data);
    case 0x8:
        return (u32) wazaDataBiosGetFightKoukaDataId(data);
    case 0x9:
        return (u32) wazaDataBiosGetSeqId(data);
    case 0xA:
        return wazaDataBiosGetFightAttackTunagiMsgId(data);
    case 0xB:
        return wazaDataBiosGetFightAttackMsgId(data);
    case 0xC:
        return (u32) wazaDataBiosGetAddFightKoukaAvg(data);
    case 0xD:
        return (u32) wazaDataBiosGetDageki(data);
    case 0xE:
        return (u32) wazaDataBiosGetMamoru(data);
    case 0xF:
        return (u32) wazaDataBiosGetMajikku(data);
    case 0x10:
        return (u32) wazaDataBiosGetYokodori(data);
    case 0x11:
        return (u32) wazaDataBiosGetOumugaesi(data);
    case 0x12:
        return (u32) wazaDataBiosGetOujanosirusi(data);
    case 0x13:
        return (u32) wazaDataBiosGetYubiwohuru(data);
    case 0x14:
        return (u32) wazaDataBiosGetMonomane(data);
    case 0x15:
        return (u32) wazaDataBiosGetNekonote(data);
    case 0x16:
        return (u32) wazaDataBiosGetNegoto(data);
    case 0x17:
        return (u32) wazaDataBiosGetBouon(data);
    case 0x18:
        return (u32) wazaDataBiosGetPressure(data);
    case 0x19:
        return (u32) wazaDataBiosGetHidenFlag(data);
    case 0x1A:
        return (u32) wazaDataBiosGetTypeId(data, element);
    case 0x1B:
        return (u32) wazaDataBiosGetRiskFlag(data);
    case 0x1C:
        return (u32)wazaDataBiosGetFightTrainerAiWazaValueFuncPtr(data);
    case 0x1D:
        return (u32)wazaDataBiosGetFightTrainerAiWazaHitFuncPtr(data);
    case 0x1E:
        return (u32)wazaDataBiosGetFightTrainerAiWazaDamageFuncPtr(data);
    case 0x20:
        return (u32)wazaDataBiosGetFightWazaWzxTypeFuncPtr(data);
    case 0x21:
        return (u32)wazaDataBiosGetFightWazaWzxVariationFuncPtr(data);
    case 0x1F:
        return wazaDataBiosGetWazawzxdataId(data);
    case 0x22:
        return wazaDataBiosGetDoc(data);
    case 0x26:
        return (u32) (s8) fightWazaBiosGetWazaBanme((FightWazaRecord *) data);
    case 0x27:
        return (u32) fightWazaBiosGetMotoWazaDataId((FightWazaRecord *) data);
    case 0x28:
        return (u32) fightWazaBiosGetUseWazaDataId((FightWazaRecord *) data);
    case 0x29:
        return (u32) fightWazaBiosGetTargetDataId((FightWazaRecord *) data);
    case 0x2A:
        return (u32)fightWazaBiosGetJoutaiPtr((FightWazaRecord *) data, element);
    case 0x2B:
        return (u32) fightWazaBiosGetCritical((FightWazaRecord *) data);
    case 0x2C:
        return (u32) fightWazaBiosGetDamageValue((FightWazaRecord *) data);
    case 0x2D:
        return fightWazaBiosGetDamage((FightWazaRecord *) data);
    case 0x2E:
        return fightWazaBiosGetHitDamage((FightWazaRecord *) data);
    case 0x2F:
        return (u32) fightWazaBiosGetIryoku((FightWazaRecord *) data);
    case 0x30:
        return (u32) fightWazaBiosGetZokusei((FightWazaRecord *) data);
    case 0x31:
        return (u32) fightWazaBiosGetKaisuu((FightWazaRecord *) data);
    case 0x32:
        return (u32) fightWazaBiosGetAutoMakeFlag((FightWazaRecord *) data);
    case 0x33:
        return (u32) wazaDB_GetZokuseiDataId(fightWaza_GetMotoWazaDataId((FightWazaRecord *) data));
    case 0x34:
        return (u32) wazaDB_GetZokuseiDataId(fightWaza_GetUseWazaDataId((FightWazaRecord *) data));
    default:
        return 0U;
    }
}
}
