#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>

extern "C" {
void fightItem_SetItemDataId(FightItem*, u16);
void fightItem_SetTargetDataId(FightItem*, u16);
void fightItem_SetCount(FightItem*, s32);
void fightItem_SetBuff(FightItem*, s32);
void fightItemInit(FightItem*);

void fightItemCreate(FightItem* item, u16 dataId, u16 target, s32 count) {
    if (item) {
        fightItemInit(item);
        fightItem_SetItemDataId(item, dataId);
        fightItem_SetTargetDataId(item, target);
        fightItem_SetCount(item, count);
    }
}

void fightItemInit(FightItem* item) {
    if (item) {
        fightItem_SetItemDataId(item, 0);
        fightItem_SetTargetDataId(item, 0);
        fightItem_SetCount(item, -1);
        fightItem_SetBuff(item, 0);
    }
}
}
