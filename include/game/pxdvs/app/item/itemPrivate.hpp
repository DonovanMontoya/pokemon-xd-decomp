#ifndef PXDVS_APP_ITEM_ITEM_PRIVATE_HPP
#define PXDVS_APP_ITEM_ITEM_PRIVATE_HPP

#include <dolphin/types.h>

struct ITEM {
    u16 itemDataId;
    u16 num;
};

extern u32 *item_data_index_number;
extern u16 item_dougu_sort[];
extern u32 item_dougu_sort_number;
extern u16 item_ball_sort[];
extern u32 item_ball_sort_number;

extern "C" {
u32 itemDB_GetName(u16 id);
u16 item_GetItemDataId(ITEM *item);
u16 item_GetNum(ITEM *item);
void item_SetItemDataId(ITEM *item, u16 id);
void item_SetNum(ITEM *item, u16 num);

void *itemDataBiosGetPtr(u32 id);
void *itemBallDataBiosGetPtr(u32 id);
void *itemSoubiDataBiosGetPtr(u32 id);

void itemDataBiosSetName(void *p, s32 v);
void itemDataBiosSetKind(void *p, u8 v);
void itemDataBiosSetPrice(void *p, u16 v);
void itemDataBiosSetImportant(void *p, u8 v);
void itemDataBiosSetUseful(void *p, u8 v);
void itemDataBiosSetDoc(void *p, s32 v);
void itemDataBiosSetItemSoubiDataId(void *p, u16 v);
void itemDataBiosSetFightUseKoukaDataId(void *p, u16 v);
void itemDataBiosSetUseFriend(void *p, u32 idx, s8 v);
void itemDataBiosSetBuff(void *p, s32 v);
void itemBallDataBiosSetFightKoukaDataId(void *p, u16 v);
void itemBiosSetItemDataId(void *p, u16 v);
void itemBiosSetNum(void *p, u16 v);
void fightItemBiosSetItemDataId(void *p, u16 v);
void fightItemBiosSetTargetDataId(void *p, u16 v);
void fightItemBiosSetCount(void *p, s32 v);
void fightItemBiosSetBuff(void *p, s32 v);

s32 itemDataBiosGetName(void *p);
u8 itemDataBiosGetKind(void *p);
u16 itemDataBiosGetPrice(void *p);
u8 itemDataBiosGetImportant(void *p);
u8 itemDataBiosGetUseful(void *p);
s32 itemDataBiosGetDoc(void *p);
u16 itemDataBiosGetItemSoubiDataId(void *p);
u16 itemDataBiosGetFightUseKoukaDataId(void *p);
s8 itemDataBiosGetUseFriend(void *p, u32 idx);
s32 itemDataBiosGetBuff(void *p);
u16 itemBallDataBiosGetFightKoukaDataId(void *p);
s32 itemBallDataBiosGetInWzxDataId(void *p);
s32 itemBallDataBiosGetOpenWzxDataId(void *p);
s32 itemBallDataBiosGetOutWzxDataId(void *p);
s32 itemBallDataBiosGetDowninWzxDataId(void *p);
s32 itemBallDataBiosGetThrowWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchAttackWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchBalllandWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchMissWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchPokeoutWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchShakeWzxDataId(void *p);
s32 itemBallDataBiosGetSnatchSnatchWzxDataId(void *p);
u16 itemSoubiDataBiosGetFightKoukaDataId(void *p);
u16 itemBiosGetItemDataId(void *p);
u16 itemBiosGetNum(void *p);
u16 fightItemBiosGetItemDataId(void *p);
u16 fightItemBiosGetTargetDataId(void *p);
s32 fightItemBiosGetCount(void *p);
s32 fightItemBiosGetBuff(void *p);
}

#endif
