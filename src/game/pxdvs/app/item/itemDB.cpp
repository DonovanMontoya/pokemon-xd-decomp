#include <game/pxdvs/app/item/itemBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
ItemBallDataRecord* itemBallDataBiosGetPtr(u16);
ItemDataRecord* itemDataBiosGetPtr(u16);
void item_SetNum(ItemBiosRecord* item, u16 value) { if (item) item->num = value; }
void item_SetItemDataId(ItemBiosRecord* item, u16 value) { if (item) item->itemDataId = value; }
u16 item_GetNum(ItemBiosRecord* item) { if (item == 0) { return 0; } else { return item->num; } }
u16 item_GetItemDataId(ItemBiosRecord* item) { if (item == 0) { return 0; } else { return item->itemDataId; } }
s32 itemBallDB_GetYaseiPokeoutWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[14]; }
}

s32 itemBallDB_GetYaseiGetWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[13]; }
}

s32 itemBallDB_GetYaseiShakeWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[12]; }
}

s32 itemBallDB_GetYaseiBallLandWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[11]; }
}

s32 itemBallDB_GetSnatchSnatchWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[10]; }
}

s32 itemBallDB_GetSnatchShakeWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[9]; }
}

s32 itemBallDB_GetSnatchPokeoutWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[8]; }
}

s32 itemBallDB_GetSnatchMissWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[7]; }
}

s32 itemBallDB_GetSnatchBalllandWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[6]; }
}

s32 itemBallDB_GetSnatchAttackWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[5]; }
}

s32 itemBallDB_GetThrowWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[4]; }
}

s32 itemBallDB_GetDowninWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[3]; }
}

s32 itemBallDB_GetOutWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[2]; }
}

s32 itemBallDB_GetOpenWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[1]; }
}

s32 itemBallDB_GetInWzxDataId(u16 identifier) {
    ItemBallDataRecord* data = itemBallDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->effectIds[0]; }
}

s32 itemDB_GetBuff(u16 identifier) {
    ItemDataRecord* data = itemDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->buff; }
}

u16 itemDB_GetItemSoubiDataId(u16 identifier) {
    ItemDataRecord* data = itemDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (u16)data->itemSoubiDataId; }
}

u8 itemDB_GetKind(u16 identifier) {
    ItemDataRecord* data = itemDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (u8)data->kind; }
}

s32 itemDB_GetName(u16 identifier) {
    ItemDataRecord* data = itemDataBiosGetPtr(identifier);
    if (data == 0) { return 0; } else { return (s32)data->name; }
}

}
