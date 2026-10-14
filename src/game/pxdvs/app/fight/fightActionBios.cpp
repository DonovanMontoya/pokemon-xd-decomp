#include <game/pxdvs/app/fight/fightAction.hpp>

extern "C" {
extern u32 fight_action_kind_data_number;
extern FightActionKindData fight_action_kind_data[];

void fightActionBiosSetFifoBanme(FIGHT_ACTION* action, s32 index) {
    if (action) action->fifoIndex = index;
}
FightActionFunc fightActionKindDataBiosGetDispFuncPtr(FightActionKindData* kind) {
    if (kind == 0) return 0;
    FightActionFunc result = kind->disp;
    return result;
}
FightActionFunc fightActionKindDataBiosGetFlowFuncPtr(FightActionKindData* kind) {
    if (kind == 0) return 0;
    FightActionFunc result = kind->flow;
    return result;
}
s32 fightActionKindDataBiosGetPri(FightActionKindData* kind) {
    if (kind == 0) return -128;
    s32 result = static_cast<s8>(kind->priority);
    return result;
}
FightActionKindData* fightActionKindDataBiosGetPtr(u16 id) {
    if (id >= fight_action_kind_data_number) return 0;
    return &fight_action_kind_data[id];
}
s32 fightActionDataBiosGetBuff(FIGHT_ACTION_DATA_dd_* data) {
    if (data == 0) return 0;
    s32 result = data->buff;
    return result;
}
u16 fightActionDataBiosGetKind(FIGHT_ACTION_DATA_dd_* data) {
    if (data == 0) return 0;
    u16 result = data->kind;
    return result;
}
void fightActionBiosSetDispBuff(FIGHT_ACTION* action, u16 index, s32 buff) {
    if (action && index < 4) action->dispBuff[index] = buff;
}
void fightActionBiosSetMotoFightActionDataPtr(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* data) {
    if (action) action->motoData = data;
}
void fightActionBiosSetBuffDataId(FIGHT_ACTION* action, s32 id) {
    if (action) action->buffDataId = id;
}
void fightActionBiosSetBuffDataPtr(FIGHT_ACTION* action, void* data) {
    if (action) action->buffData = data;
}
void fightActionBiosSetActorFightTargetPtr(FIGHT_ACTION* action, FightTarget* actor) {
    if (action) action->actor = actor;
}
void fightActionBiosSetFightActionDataPtr(FIGHT_ACTION* action, FIGHT_ACTION_DATA_dd_* data) {
    if (action) action->data = data;
}
void fightActionBiosSetBuff(FIGHT_ACTION* action, s32 buff) {
    if (action) action->buff = buff;
}
void fightActionBiosSetKind(FIGHT_ACTION* action, u16 kind) {
    if (action) action->kind = kind;
}
s32 fightActionBiosGetBuffDataId(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    s32 result = action->buffDataId;
    return result;
}
void* fightActionBiosGetBuffDataPtr(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    void* result = action->buffData;
    return result;
}
FightTarget* fightActionBiosGetActorFightTargetPtr(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    FightTarget* result = action->actor;
    return result;
}
FIGHT_ACTION_DATA_dd_* fightActionBiosGetFightActionDataPtr(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    FIGHT_ACTION_DATA_dd_* result = action->data;
    return result;
}
s32 fightActionBiosGetBuff(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    s32 result = action->buff;
    return result;
}
u16 fightActionBiosGetKind(FIGHT_ACTION* action) {
    if (action == 0) return 0;
    u16 result = action->kind;
    return result;
}
void fightActionBiosCopy(FIGHT_ACTION* dst, FIGHT_ACTION* src) {
    if (dst && src) *dst = *src;
}
}
