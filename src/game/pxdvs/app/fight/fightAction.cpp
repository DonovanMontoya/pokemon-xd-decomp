#include <game/pxdvs/app/fight/fightAction.hpp>

static FIGHT_ACTION _fight_action_fifo[32];
static u32 _fight_action_fifo_head;
static u32 _fight_action_fifo_tail;

extern "C" {
// The getter results are forwarded without narrowing at the original call sites.
u16 fightActionBiosGetKind(FIGHT_ACTION*);
s32 fightActionBiosGetBuff(FIGHT_ACTION*);
FIGHT_ACTION_DATA_dd_* fightActionBiosGetFightActionDataPtr(FIGHT_ACTION*);
u16 fightActionDataBiosGetKind(FIGHT_ACTION_DATA_dd_*);
s32 fightActionDataBiosGetBuff(FIGHT_ACTION_DATA_dd_*);
FightActionKindData* fightActionKindDataBiosGetPtr(u16);
s32 fightActionKindDataBiosGetPri(FightActionKindData*);
FightActionFunc fightActionKindDataBiosGetDispFuncPtr(FightActionKindData*);
FightActionFunc fightActionKindDataBiosGetFlowFuncPtr(FightActionKindData*);
void fightActionBiosCopy(FIGHT_ACTION*, FIGHT_ACTION*);
void fightActionBiosSetFifoBanme(FIGHT_ACTION*, s32);
void fightActionBiosSetKind(FIGHT_ACTION*, u16);
void fightActionBiosSetBuff(FIGHT_ACTION*, s32);
void fightActionBiosSetFightActionDataPtr(FIGHT_ACTION*, FIGHT_ACTION_DATA_dd_*);
void fightActionBiosSetActorFightTargetPtr(FIGHT_ACTION*, FightTarget*);
void fightActionBiosSetDispBuff(FIGHT_ACTION*, u16, s32);
void fightActionBiosSetBuffDataPtr(FIGHT_ACTION*, void*);
void fightActionBiosSetBuffDataId(FIGHT_ACTION*, s32);
void fightActionBiosSetMotoFightActionDataPtr(FIGHT_ACTION*, FIGHT_ACTION_DATA_dd_*);
}
static u8 _fightActionFlowSub(FIGHT_ACTION*);
static FIGHT_ACTION_DATA_dd_* _fightActionDataSearchDataPtr(FIGHT_ACTION_DATA_dd_*, u16, s32);

extern "C" {
u16 fightActionGetKindDataId(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) return 0;
    FIGHT_ACTION_DATA_dd_* data = fightActionBiosGetFightActionDataPtr(action);
    if (!data) return 0;
    u16 result = fightActionDataBiosGetKind(data);
    return result;
}

s32 fightActionGetPri(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) return -128;
    FIGHT_ACTION_DATA_dd_* data = fightActionBiosGetFightActionDataPtr(action);
    if (!data) return -128;
    FightActionKindData* kind = fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(data));
    if (kind == 0) return -128;
    s32 result = fightActionKindDataBiosGetPri(kind);
    return result;
}

void fightActionDispFifoAll() {
    while (true) {
        u8 result = fightActionDispFifo();
        if (result == 3) break;
        if (result != 1) break;
    }
}

u8 fightActionCreateAndFlowFifo(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* moto, FightTarget* actor, u16 kind, s32 buff, FIGHT_ACTION_DATA_dd_* data) {
    u8 result = fightActionCreate(action, moto, actor, kind, buff, data);
    if (result != 1) return result;
    return fightActionFlowFifo(action);
}

u8 fightActionDispFifo() {
    FIGHT_ACTION action;
    u8 result = fightActionFifoOut(&action);
    if (result == 0) return 3;
    result = fightActionDisp(&action);
    return result;
}

u8 fightActionFlowFifo(FIGHT_ACTION* action) {
    FIGHT_ACTION discard;
    u8 result;
    FIGHT_ACTION* queued = fightActionFifoIn(action);
    if (!queued) return 2;
    result = _fightActionFlowSub(action);
    if (result != 1) fightActionFifoOut(&discard);
    else fightActionBiosCopy(queued, action);
    return result;
}

u8 fightActionDisp(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) return 0;
    FightActionFunc func = fightActionKindDataBiosGetDispFuncPtr(fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(fightActionBiosGetFightActionDataPtr(action))));
    if (func) return func(action);
    return 1;
}

u8 fightActionFifoOut(FIGHT_ACTION* action) {
    if (_fight_action_fifo_tail != _fight_action_fifo_head) {
        *action = _fight_action_fifo[_fight_action_fifo_head];
        ++_fight_action_fifo_head;
        _fight_action_fifo_head &= 31;
    } else return 0;
    return 1;
}

FIGHT_ACTION* fightActionFifoIn(FIGHT_ACTION* action) {
    u32 index = _fight_action_fifo_tail;
    FIGHT_ACTION* queued;
    if (((index + 1) & 31) != _fight_action_fifo_head) {
        queued = &_fight_action_fifo[index];
        *queued = *action;
        ++_fight_action_fifo_tail;
        _fight_action_fifo_tail &= 31;
    } else return 0;
    fightActionBiosSetFifoBanme(action, index);
    fightActionBiosSetFifoBanme(queued, index);
    return queued;
}

void fightActionFifoInit() {
    _fight_action_fifo_head = 0;
    _fight_action_fifo_tail = 0;
    for (u16 i = 0; i < 32; ++i) fightActionInit(&_fight_action_fifo[i]);
}

bool fightActionCheckValid(FIGHT_ACTION* action) {
    if (!action) return 0;
    if (!(u16)fightActionBiosGetKind(action)) return 0;
    if (fightActionBiosGetFightActionDataPtr(action) == 0) return false;
    return true;
}

u8 fightActionCreate(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* moto, FightTarget* actor, u16 kind, s32 buff, FIGHT_ACTION_DATA_dd_* data) {
    fightActionInit(action);
    fightActionBiosSetKind(action, kind);
    fightActionBiosSetBuff(action, buff);
    fightActionBiosSetFightActionDataPtr(action, data);
    fightActionBiosSetActorFightTargetPtr(action, actor);
    if (!fightActionSearchDataPtr(action)) {
        fightActionInit(action);
        return 4;
    }
    fightActionBiosSetBuffDataId(action, buff);
    fightActionBiosSetMotoFightActionDataPtr(action, moto);
    return 1;
}

void fightActionInit(FIGHT_ACTION* action) {
    fightActionBiosSetKind(action, 0);
    fightActionBiosSetBuff(action, 0);
    fightActionBiosSetFightActionDataPtr(action, 0);
    for (u16 i = 0; i < 4; ++i) fightActionBiosSetDispBuff(action, i, 0);
    fightActionBiosSetBuffDataPtr(action, 0);
    fightActionBiosSetBuffDataId(action, 0);
    fightActionBiosSetActorFightTargetPtr(action, 0);
    fightActionBiosSetMotoFightActionDataPtr(action, 0);
    fightActionBiosSetFifoBanme(action, -1);
}

FIGHT_ACTION_DATA_dd_* fightActionSearchDataPtr(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) return 0;
    FIGHT_ACTION_DATA_dd_* data;
    u16 kind = fightActionBiosGetKind(action);
    s32 buff = fightActionBiosGetBuff(action);
    data = _fightActionDataSearchDataPtr(fightActionBiosGetFightActionDataPtr(action), kind, buff);
    if (!data) return 0;
    fightActionBiosSetFightActionDataPtr(action, data);
    return data;
}
}

static u8 _fightActionFlowSub(FIGHT_ACTION* action) {
    if (!fightActionCheckValid(action)) return 0;
    FightActionFunc func = fightActionKindDataBiosGetFlowFuncPtr(fightActionKindDataBiosGetPtr(fightActionDataBiosGetKind(fightActionBiosGetFightActionDataPtr(action))));
    if (func) return func(action);
    return 1;
}

static FIGHT_ACTION_DATA_dd_* _fightActionDataSearchDataPtr(FIGHT_ACTION_DATA_dd_* ary, u16 kind, s32 buff) {
    if (!ary) return 0;
    for (u16 i = 0; ; ++i) {
        FIGHT_ACTION_DATA_dd_* data = &ary[i];
        u16 dataKind = fightActionDataBiosGetKind(data);
        if (!dataKind) break;
        s32 dataBuff = fightActionDataBiosGetBuff(data);
        if (kind == dataKind && buff == dataBuff) return data;
    }
    return 0;
}
