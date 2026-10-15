// Needs extra cflags: -inline auto,deferred (inline helpers are defined after their callers in the object).
#include "game/pxdvs/app/item/itemPrivate.hpp"

u16 *currentPriorityTbl;
u32 currentPriorityTblQuantity;

extern "C" {
void itemReplace(ITEM *a, ITEM *b);
u8 itemDataCheckValid(u16 id);
u8 itemCheckValid(ITEM *item);
ITEM *itemSearchItemDataIdAry(ITEM *ary, u16 count, u16 id, u8 mode, u16 num);
}
static void _itemSortAry(ITEM *ary, u16 count, u8 type);

static inline u8 itemDataValid(u16 id) {
    u8 r;
    if (itemDB_GetName(id) == 0) {
        r = 0;
    } else if (id >= *item_data_index_number) {
        r = 0;
    } else {
        r = 1;
    }
    return r;
}

static inline u8 itemValid(ITEM *p) {
    if (p == NULL) {
        return 0;
    }
    u16 id = item_GetItemDataId(p);
    if (id == 0) {
        return 0;
    }
    if (!itemDataValid(id)) {
        return 0;
    }
    return 1;
}

static inline s32 itemPriorityIndex(s32 id) {
    u16 *t = currentPriorityTbl;
    for (s32 i = 0; i < currentPriorityTblQuantity; i++) {
        if (id == t[i]) {
            return i;
        }
    }
    return 0;
}

static inline s32 itemPriorityDiff(s32 b, s32 a) {
    return itemPriorityIndex(a) - itemPriorityIndex(b);
}

static inline void itemSwap(ITEM *a, ITEM *b) {
    if (a != NULL && b != NULL) {
        u16 t1;
        u16 t0;
        t0 = a->itemDataId;
        t1 = a->num;
        a->itemDataId = b->itemDataId;
        a->num = b->num;
        b->itemDataId = t0;
        b->num = t1;
    }
}

static inline u8 itemIsSame(ITEM *p, u16 id) {
    if (p == NULL) {
        return 0;
    }
    if (!itemValid(p)) {
        return 0;
    }
    if (id == item_GetItemDataId(p)) {
        return 1;
    }
    return 0;
}

static inline s32 itemAddInner(ITEM *p, u16 num, u16 max) {
    if (p == NULL) {
        return -1;
    }
    if (!itemValid(p)) {
        return -1;
    }
    s32 n = item_GetNum(p) + num;
    s32 over;
    if (n > (s32)max) {
        over = n - max;
        n = max;
    } else {
        over = 0;
    }
    item_SetNum(p, n);
    return over;
}

static inline s32 itemAddNum(ITEM *p, u16 id, u16 num, u16 max) {
    if (p == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    if (!itemIsSame(p, id)) {
        return -1;
    }
    return itemAddInner(p, num, max);
}

static inline s32 itemAddNew(ITEM *p, u16 id, u16 num, u16 max) {
    if (p == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    if (p != NULL) {
        item_SetItemDataId(p, 0);
        item_SetNum(p, 0);
    }
    item_SetItemDataId(p, id);
    return itemAddInner(p, num, max);
}

static inline s32 itemDecNum(ITEM *p, u16 id, u16 num) {
    if (p == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    if (!itemIsSame(p, id)) {
        return -1;
    }
    if (p == NULL) {
        return -1;
    }
    if (!itemValid(p)) {
        return -1;
    }
    s32 n = item_GetNum(p);
    s32 over;
    n -= num;
    if (n < 0) {
        over = num - n;
        n = 0;
    } else {
        over = 0;
    }
    item_SetNum(p, n);
    if (n <= 0 && p != NULL) {
        item_SetItemDataId(p, 0);
        item_SetNum(p, 0);
    }
    return over;
}

extern "C" {
void itemSortAryByPriority(ITEM *ary, u16 count, s32 type) {
    s32 j;
    s32 i;
    ITEM *q;
    ITEM *p;
    s32 n;
    if (type == 2) {
        currentPriorityTbl = item_dougu_sort;
        currentPriorityTblQuantity = item_dougu_sort_number;
    } else if (type == 1) {
        currentPriorityTbl = item_ball_sort;
        currentPriorityTblQuantity = item_ball_sort_number;
    }
    if (ary != NULL && count != 0) {
        p = ary;
        n = count - 1;
        for (i = 0; i < n; p++, i++) {
            if (itemValid(p)) {
                j = i + 1;
                q = ary + j;
                for (; j < (s32)count; q++, j++) {
                    if (itemValid(q)) {
                        if (itemPriorityDiff(item_GetItemDataId(q), item_GetItemDataId(p)) > 0) {
                            itemSwap(p, q);
                        }
                    }
                }
            }
        }
    }
}

s32 itemCheckAddItemDataIdAry(ITEM *ary, u16 count, u16 id, u16 max, u8 flag) {
    if (ary == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    ITEM *p;
    s32 result;
    u16 i;
    if (flag == 0) {
        p = itemSearchItemDataIdAry(ary, count, id, 0, 0);
        if (p != NULL) {
            result = max - item_GetNum(p);
        } else {
            if (itemSearchItemDataIdAry(ary, count, id, 2, 0) != NULL) {
                result = max;
            } else {
                result = 0;
            }
        }
    } else {
        result = 0;
        for (i = 0; i < count; i++) {
            p = ary + i;
            if (!itemValid(p)) {
                result += max;
            } else if (itemIsSame(p, id) == 1) {
                result += max - item_GetNum(p);
            }
        }
    }
    return result;
}

void itemReplace(ITEM *a, ITEM *b) {
    if (a != NULL && b != NULL) {
        u16 t0 = a->itemDataId;
        u16 t1 = a->num;
        a->itemDataId = b->itemDataId;
        a->num = b->num;
        b->itemDataId = t0;
        b->num = t1;
    }
}

s32 itemDecItemDataIdAry(ITEM *ary, u16 count, u16 id, u16 num, s16 idx, u16 unused, u8 sortType) {
    if (ary == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    s32 rem;
    u8 needSort = 0;
    if (idx < 0) {
        rem = num;
        for (;;) {
            ITEM *p = itemSearchItemDataIdAry(ary, count, id, 0, 0);
            if (p == NULL) {
                break;
            }
            s32 over = itemDecNum(p, id, rem);
            if (over < 0) {
                return over;
            }
            if (!itemValid(p)) {
                needSort = 1;
            }
            rem = over;
            if (over > 0) {
                continue;
            }
            break;
        }
    } else {
        ITEM *p = ary + idx;
        rem = itemDecNum(p, id, num);
        if (!itemValid(p)) {
            needSort = 1;
        }
    }
    if (needSort == 1) {
        _itemSortAry(ary, count, sortType);
    }
    return rem;
}

s32 itemAddItemDataIdAry(ITEM *ary, u16 count, u16 id, u16 num, s16 idx, u16 max, u8 sortType, u8 mode) {
    if (ary == NULL) {
        return -1;
    }
    if (!itemDataValid(id)) {
        return -1;
    }
    s32 rem = num;
    u8 needSort = 0;
    if (mode == 0) {
        ITEM *p = itemSearchItemDataIdAry(ary, count, id, 0, 0);
        if (p != NULL) {
            if (item_GetNum(p) < max) {
                s32 over = itemAddNum(p, id, rem, max);
                if (over < 0) {
                    return over;
                }
                rem = over;
            }
        } else {
            p = itemSearchItemDataIdAry(ary, count, id, 2, 0);
            if (p != NULL) {
                s32 over = itemAddNew(p, id, rem, max);
                if (over < 0) {
                    return over;
                }
                rem = over;
                needSort = 1;
            }
        }
    } else if (idx < 0) {
        for (;;) {
            ITEM *p = itemSearchItemDataIdAry(ary, count, id, 1, max);
            if (p != NULL) {
                s32 over = itemAddNum(p, id, rem, max);
                if (over < 0) {
                    return over;
                }
                rem = over;
            } else {
                p = itemSearchItemDataIdAry(ary, count, id, 2, 0);
                if (p == NULL) {
                    break;
                }
                s32 over = itemAddNew(p, id, rem, max);
                if (over < 0) {
                    return over;
                }
                needSort = 1;
                rem = over;
            }
            if ((s32)rem <= 0) {
                break;
            }
        }
    } else {
        ITEM *p = ary + idx;
        rem = itemAddNum(p, id, rem, max);
    }
    if (needSort == 1) {
        _itemSortAry(ary, count, sortType);
    }
    return rem;
}

s32 itemGetQuantityInAry(ITEM *ary, u16 count, u16 id) {
    if (ary == NULL) {
        return 0;
    }
    if (!itemDataValid(id)) {
        return 0;
    }
    ITEM *p = ary;
    s32 n = count;
    s32 total = 0;
    for (s32 i = 0; i < n; p++, i++) {
        if (itemIsSame(p, id)) {
            total += item_GetNum(p);
        }
    }
    return total;
}

ITEM *itemSearchItemDataIdAry(ITEM *ary, u16 count, u16 id, u8 mode, u16 num) {
    ITEM *p;
    u16 i;
    if (ary == 0) {
        return 0;
    }
    if (!itemDataValid(id)) {
        return 0;
    }
    for (i = 0; i < count; i++) {
        if (mode == 2) {
            if (!itemValid(ary + i)) {
                return ary + i;
            }
        } else {
            p = ary + i;
            if (itemIsSame(p, id)) {
                if (mode == 1) {
                    if (item_GetNum(p) < num) {
                        return ary + i;
                    }
                } else {
                    return ary + i;
                }
            }
        }
    }
    return 0;
}
}

static void _itemSortAry(ITEM *ary, u16 count, u8 type) {
    if (ary != NULL && count != 0) {
        if (type == 0 || type == 1) {
            ITEM *p;
            s32 n;
            s32 cnt;
            s32 j;
            s32 i;
            ITEM *q;
            cnt = count;
            p = ary;
            n = cnt - 1;
            for (i = 0; i < n; p++, i++) {
                if (!itemValid(p)) {
                    j = i + 1;
                    q = ary + j;
                    for (; j < cnt; q++, j++) {
                        if (itemValid(q) == 1) {
                            itemReplace(p, ary + j);
                            break;
                        }
                    }
                }
            }
        }
        if (type == 1) {
            ITEM *p;
            ITEM *q;
            s32 n;
            s32 cnt;
            s32 i;
            s32 j;
            cnt = count;
            p = ary;
            n = cnt - 1;
            for (i = 0; i < n; p++, i++) {
                if (itemValid(p)) {
                    j = i + 1;
                    q = ary + j;
                    for (; j < cnt; q++, j++) {
                        if (itemValid(q)) {
                            u16 a = item_GetItemDataId(p);
                            u16 b = item_GetItemDataId(q);
                            if (a > b) {
                                itemReplace(p, q);
                            }
                        }
                    }
                }
            }
        }
    }
}

extern "C" {
u8 itemDataCheckValid(u16 id) {
    if (itemDB_GetName(id) == 0) {
        return 0;
    }
    return id < *item_data_index_number;
}

u8 itemCheckValid(ITEM *item) {
    if (item == NULL) {
        return 0;
    }
    u16 id = item_GetItemDataId(item);
    if (id == 0) {
        return 0;
    }
    return itemDataValid(id) != 0;
}

void itemInitAry(ITEM *ary, u16 count) {
    if (ary != NULL) {
        ITEM *p;
        for (u16 i = 0; i < count; i++) {
            p = ary + i;
            if (p != NULL) {
                item_SetItemDataId(p, 0);
                item_SetNum(p, 0);
            }
        }
    }
}
}

extern "C" {
void itemSetStatus(void *ptr, u32 id, u16 type, u32 idx, s32 val) {
    if (type == 0 || type >= 0x23) {
        return;
    }
    if (type < 0xB) {
        ptr = itemDataBiosGetPtr(id);
        if (ptr == NULL) {
            return;
        }
    } else if (type < 0x18) {
        ptr = itemBallDataBiosGetPtr(id);
        if (ptr == NULL) {
            return;
        }
    } else if (ptr == NULL) {
        return;
    }
    switch (type) {
    case 1:
        itemDataBiosSetName(ptr, val);
        break;
    case 2:
        itemDataBiosSetKind(ptr, val);
        break;
    case 3:
        itemDataBiosSetPrice(ptr, val);
        break;
    case 4:
        itemDataBiosSetImportant(ptr, val != 0);
        break;
    case 5:
        itemDataBiosSetUseful(ptr, val != 0);
        break;
    case 6:
        itemDataBiosSetDoc(ptr, val);
        break;
    case 7:
        itemDataBiosSetItemSoubiDataId(ptr, val);
        break;
    case 8:
        itemDataBiosSetFightUseKoukaDataId(ptr, val);
        break;
    case 9:
        itemDataBiosSetUseFriend(ptr, idx, val);
        break;
    case 10:
        itemDataBiosSetBuff(ptr, val);
    case 12:
        itemBallDataBiosSetFightKoukaDataId(ptr, val);
        break;
    case 27:
        itemBiosSetItemDataId(ptr, val);
        break;
    case 28:
        itemBiosSetNum(ptr, val);
        break;
    case 30:
        fightItemBiosSetItemDataId(ptr, val);
        break;
    case 31:
        fightItemBiosSetTargetDataId(ptr, val);
        break;
    case 32:
        fightItemBiosSetCount(ptr, val);
        break;
    case 33:
        fightItemBiosSetBuff(ptr, val);
        break;
    }
}

s32 itemGetStatus(void *ptr, u32 id, u16 type, u32 idx) {
    if (type == 0 || type >= 0x23) {
        return 0;
    }
    if (type < 0xB) {
        ptr = itemDataBiosGetPtr(id);
        if (ptr == NULL) {
            return 0;
        }
    } else if (type < 0x18) {
        ptr = itemBallDataBiosGetPtr(id);
        if (ptr == NULL) {
            return 0;
        }
    } else if (type < 0x1A) {
        ptr = itemSoubiDataBiosGetPtr(id);
        if (ptr == NULL) {
            return 0;
        }
    } else if (ptr == NULL) {
        return 0;
    }
    switch (type) {
    case 1:
        return itemDataBiosGetName(ptr);
    case 2:
        return itemDataBiosGetKind(ptr);
    case 3:
        return itemDataBiosGetPrice(ptr);
    case 4:
        return itemDataBiosGetImportant(ptr);
    case 5:
        return itemDataBiosGetUseful(ptr);
    case 6:
        return itemDataBiosGetDoc(ptr);
    case 7:
        return itemDataBiosGetItemSoubiDataId(ptr);
    case 8:
        return itemDataBiosGetFightUseKoukaDataId(ptr);
    case 9:
        return itemDataBiosGetUseFriend(ptr, idx);
    case 10:
        return itemDataBiosGetBuff(ptr);
    case 12:
        return itemBallDataBiosGetFightKoukaDataId(ptr);
    case 13:
        return itemBallDataBiosGetInWzxDataId(ptr);
    case 14:
        return itemBallDataBiosGetOpenWzxDataId(ptr);
    case 15:
        return itemBallDataBiosGetOutWzxDataId(ptr);
    case 16:
        return itemBallDataBiosGetDowninWzxDataId(ptr);
    case 17:
        return itemBallDataBiosGetThrowWzxDataId(ptr);
    case 18:
        return itemBallDataBiosGetSnatchAttackWzxDataId(ptr);
    case 19:
        return itemBallDataBiosGetSnatchBalllandWzxDataId(ptr);
    case 20:
        return itemBallDataBiosGetSnatchMissWzxDataId(ptr);
    case 21:
        return itemBallDataBiosGetSnatchPokeoutWzxDataId(ptr);
    case 22:
        return itemBallDataBiosGetSnatchShakeWzxDataId(ptr);
    case 23:
        return itemBallDataBiosGetSnatchSnatchWzxDataId(ptr);
    case 25:
        return itemSoubiDataBiosGetFightKoukaDataId(ptr);
    case 27:
        return itemBiosGetItemDataId(ptr);
    case 28:
        return itemBiosGetNum(ptr);
    case 30:
        return fightItemBiosGetItemDataId(ptr);
    case 31:
        return fightItemBiosGetTargetDataId(ptr);
    case 32:
        return fightItemBiosGetCount(ptr);
    case 33:
        return fightItemBiosGetBuff(ptr);
    }
    return 0;
}
}
