#include <global.h>
struct FightItem { s16 item; u16 target; s32 count; s32 buff; };
extern "C" {
void fightItem_SetBuff(FightItem* p, s32 v) { if (p) p->buff=v; }
void fightItem_SetCount(FightItem* p, s32 v) { if (p) p->count=v; }
void fightItem_SetTargetDataId(FightItem* p, s16 v) { if (p) p->target=v; }
void fightItem_SetItemDataId(s16* p, s16 v) { if (p) *p=v; }
s32 fightItem_GetBuff(FightItem* p) { if (p == 0) return 0; return p->buff; }
s32 fightItem_GetCount(FightItem* p) { if (p == 0) return 0; return p->count; }
u16 fightItem_GetTargetDataId(FightItem* p) { if (p == 0) return 0; return p->target; }
u16 fightItem_GetItemDataId(u16* p) { if (p == 0) return 0; return *p; }
}
