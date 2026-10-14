#ifndef FIGHT_ACTION_HPP
#define FIGHT_ACTION_HPP
#include <dolphin/types.h>

struct FIGHT_ACTION_DATA_dd_ {
    u16 kind;
    s32 buff;
};
struct FightTarget;
struct FIGHT_ACTION {
    u16 kind;
    s32 buff;
    FIGHT_ACTION_DATA_dd_* data;
    void* buffData;
    s32 buffDataId;
    FightTarget* actor;
    FIGHT_ACTION_DATA_dd_* motoData;
    s32 fifoIndex;
    s32 dispBuff[4];
};
typedef u8 (*FightActionFunc)(FIGHT_ACTION*);
struct FightActionKindData {
    u8 priority;
    FightActionFunc flow;
    FightActionFunc disp;
};
extern "C" {
u16 fightActionGetKindDataId(FIGHT_ACTION*);
s32 fightActionGetPri(FIGHT_ACTION*);
void fightActionDispFifoAll();
u8 fightActionCreateAndFlowFifo(FIGHT_ACTION*, FIGHT_ACTION_DATA_dd_*, FightTarget*, u16, s32, FIGHT_ACTION_DATA_dd_*);
u8 fightActionDispFifo();
u8 fightActionFlowFifo(FIGHT_ACTION*);
u8 fightActionDisp(FIGHT_ACTION*);
u8 fightActionFifoOut(FIGHT_ACTION*);
FIGHT_ACTION* fightActionFifoIn(FIGHT_ACTION*);
void fightActionFifoInit();
bool fightActionCheckValid(FIGHT_ACTION*);
u8 fightActionCreate(FIGHT_ACTION*, FIGHT_ACTION_DATA_dd_*, FightTarget*, u16, s32, FIGHT_ACTION_DATA_dd_*);
void fightActionInit(FIGHT_ACTION*);
FIGHT_ACTION_DATA_dd_* fightActionSearchDataPtr(FIGHT_ACTION*);
}
#endif
