#ifndef PXDVS_APP_ITEM_ITEM_BIOS_LAYOUT_HPP
#define PXDVS_APP_ITEM_ITEM_BIOS_LAYOUT_HPP

#include <dolphin/types.h>
#include <libc/stddef.h>

struct ItemParamRecord {
    u8 effects[5];
    s8 friend1Up;
    s8 friend2Up;
    s8 friend3Up;
    u8 hpEffortUp;
    u8 attackEffortUp;
    u8 hpUp;
    u8 ppUp;
    u8 defenceEffortUp;
    u8 quickEffortUp;
    u8 spDefenceEffortUp;
    u8 spAttackEffortUp;
};
struct TasteDataRecord { u8 bytes[0x20]; };
struct ItemSoubiDataRecord { u16 fightKoukaDataId; };
struct ItemBiosRecord { u16 itemDataId; u16 num; };
struct ItemBallDataRecord { u16 id; u16 reserved; s32 effectIds[15]; };
struct ItemDataRecord {
    u8 kind; s8 important; s8 useful; u8 deposit; u8 effectParam; u8 reserved5[1];
    u16 price; u16 coupon; u16 itemSoubiDataId; s16 fightKoukaDataId; u8 reservedE[2];
    s32 name; s32 doc; s32 buff; s32 fieldUseFunc; s32 battleUseFunc;
    s8 useFriend[3]; u8 reserved27[1];
};
struct WazaMachineRecord { u32 reserved; u16 wazaId; u8 reservedTail[2]; };

typedef char ItemParamRecordSizeCheck[sizeof(ItemParamRecord) == 0x10 ? 1 : -1];
typedef char TasteDataRecordSizeCheck[sizeof(TasteDataRecord) == 0x20 ? 1 : -1];
typedef char ItemSoubiDataRecordSizeCheck[sizeof(ItemSoubiDataRecord) == 2 ? 1 : -1];
typedef char ItemBiosRecordSizeCheck[sizeof(ItemBiosRecord) == 4 ? 1 : -1];
typedef char ItemBiosNumOffsetCheck[offsetof(ItemBiosRecord, num) == 2 ? 1 : -1];
typedef char ItemBallDataRecordSizeCheck[sizeof(ItemBallDataRecord) == 0x40 ? 1 : -1];
typedef char ItemDataPriceOffsetCheck[offsetof(ItemDataRecord, price) == 6 ? 1 : -1];
typedef char ItemDataSoubiOffsetCheck[offsetof(ItemDataRecord, itemSoubiDataId) == 0xA ? 1 : -1];
typedef char ItemDataFightKoukaOffsetCheck[offsetof(ItemDataRecord, fightKoukaDataId) == 0xC ? 1 : -1];
typedef char ItemDataNameOffsetCheck[offsetof(ItemDataRecord, name) == 0x10 ? 1 : -1];
typedef char ItemDataDocOffsetCheck[offsetof(ItemDataRecord, doc) == 0x14 ? 1 : -1];
typedef char ItemDataBuffOffsetCheck[offsetof(ItemDataRecord, buff) == 0x18 ? 1 : -1];
typedef char ItemDataFieldUseOffsetCheck[offsetof(ItemDataRecord, fieldUseFunc) == 0x1C ? 1 : -1];
typedef char ItemDataBattleUseOffsetCheck[offsetof(ItemDataRecord, battleUseFunc) == 0x20 ? 1 : -1];
typedef char ItemDataFriendsOffsetCheck[offsetof(ItemDataRecord, useFriend) == 0x24 ? 1 : -1];
typedef char ItemDataRecordSizeCheck[sizeof(ItemDataRecord) == 0x28 ? 1 : -1];
#endif
