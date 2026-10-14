#include <dolphin/types.h>

struct FightItemBios {
    u16 itemDataId;
    u16 targetDataId;
    s32 count;
    s32 buff;
};

extern "C" {
void fightItemBiosSetBuff(FightItemBios *item, s32 buff) {
    if (item != NULL) {
        item->buff = buff;
    }
}

void fightItemBiosSetCount(FightItemBios *item, s32 count) {
    if (item != NULL) {
        item->count = count;
    }
}

void fightItemBiosSetTargetDataId(FightItemBios *item, s16 targetDataId) {
    if (item != NULL) {
        item->targetDataId = targetDataId;
    }
}

void fightItemBiosSetItemDataId(FightItemBios *item, s16 itemDataId) {
    if (item != NULL) {
        item->itemDataId = itemDataId;
    }
}

s32 fightItemBiosGetBuff(FightItemBios *item) {
    if (item == NULL) {
        return 0;
    }
    return item->buff;
}

s32 fightItemBiosGetCount(FightItemBios *item) {
    if (item == NULL) {
        return 0;
    }
    return item->count;
}

u16 fightItemBiosGetTargetDataId(FightItemBios *item) {
    if (item == NULL) {
        return 0;
    }
    return item->targetDataId;
}

u16 fightItemBiosGetItemDataId(FightItemBios *item) {
    if (item == NULL) {
        return 0;
    }
    return item->itemDataId;
}
}
