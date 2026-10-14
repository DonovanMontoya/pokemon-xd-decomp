#include <game/pxdvs/app/fight/fightSeq/fightSeqWSWazaPrivate.hpp>

extern "C" {
u32 fightSeqGetEffectAminFlag(void) {
    return !(ServerStatusFlag & 0x80);
}

void fightSeqSetEffectAminFlag(u8 on) {
    if (on == 1) {
        ServerStatusFlag &= ~0x80;
    } else {
        ServerStatusFlag |= 0x80;
    }
}
}

static s32 _fightSeqInitSubFightOutPokemon(void* pokemon, u16, void*) {
    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    return 1;
}

extern "C" {
u8 fightSeqFightActionCreateAndFlowFifo(void* a, void* b, u16 c, s32 d, void* e, void* f) {
    WSFightAction action;
    u8 r = fightSeqFightActionCreate(&action, a, b, c, d, e, f);
    if (r != 1) {
        return r;
    }
    return fightActionFlowFifo(&action);
}

u8 fightSeqFightActionCreate(void* out, void* a, void* b, u16 c, s32 d, void* e, void* f) {
    u8 r = fightActionCreate(out, a, b, c, d, e);
    if (r != 1) {
        return r;
    }
    fightActionBiosSetBuffDataPtr(out, f);
    return 1;
}
}

static s32 _fightSeqClearOneSelfTurnCountSub(void* pokemon, u16, void*) {
    fightOutPokemonInitOneSelfTurn(pokemon);
    return 1;
}

extern "C" {
void SCA_EndCheck(void) {
    fightSeqGetExpCheck();
    ActionSeqNo = 2;
}

void fightSeqClearOneSelfTurnCount(void) {
    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneSelfTurnCountSub, 0, 0);
}

void fightSeqSpecificationActionCounterInit(void* pokemon) {
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x2E) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2E);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x15) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x15);
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x28) == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x28);
    }
}

void fightSeqIrekaeExec(void* arg) {
    void* pokemon = fightFloor_GetIrekaePokemonPtr(0);
    fightFloor_SetAttackPokemonPtr(0, pokemon);
    fightMsgctrlSetValue(0xD, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    ActionSeqNo = 0;
    fightSeqSpecificationActionCounterInit(pokemon);
    fightSeq_CallWazaSeqCustom(arg, WAZA_PokeReshuffle, 1);
    wazaSequenceSysFreeAllWaza();
    fightMenuAllFightTrainerCloseStatusMenu(0);
    fightMenuAllFightOutPokemonCloseStatusMenu(0);
    fightMenuCloseMsg();
}

s32 fightSeqGetItemType(u16 item) {
    void* param = itemParamGetPtr(itemDataBiosGetItemEffectParam(itemDataBiosGetPtr(item)));
    if (param == 0) {
        return 7;
    }
    if (item == 0x13) {
        return 1;
    }
    if (itemParamGetHPUp(param) != 0) {
        return 2;
    }
    if (itemParamGetSleepFlag(param) == 1 || itemParamGetPoisonFlag(param) == 1 || itemParamGetBurnFlag(param) == 1 ||
        itemParamGetFreezeFlag(param) == 1 || itemParamGetParalyzeFlag(param) == 1 ||
        itemParamGetConfuseFlag(param) == 1) {
        return 3;
    }
    if (itemParamGetCriticalFlag(param) == 1) {
        return 4;
    }
    if (itemParamGetAttackUp(param) != 0 || itemParamGetDefenceUp(param) != 0 || itemParamGetQuickUp(param) != 0 ||
        itemParamGetHitUp(param) != 0 || itemParamGetSpAttackUp(param) != 0) {
        return 5;
    }
    if (itemParamGetGuardFlag(param) == 1) {
        return 6;
    }
    return 7;
}
}

static s32 _fightSeqClearOneTurnCountSub(void* pokemon, u16, void* data) {
    s8 count;
    u16 turn;
    if (*(u8*)data == 1) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2B);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x2C);
    } else {
        fightOutPokemonInitOneTurn(pokemon);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x32);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x37);
        fightOutPokemonInitJoutaiDataId(pokemon, 0x33);
        turn = fightOutPokemon_GetFightoutTurnCount(pokemon);
        if (turn != 0) {
            fightOutPokemon_SetFightoutTurnCount(pokemon, turn - 1);
        }
        if (fightOutPokemonIsJoutaiDataId(pokemon, 0x12) == 1) {
            count = fightOutPokemonGetNowKaisuuJoutaiDataId(pokemon, 0x12);
            if ((s8)(count + 1) >= fightOutPokemonGetKaisuuJoutaiDataId(pokemon, 0x12)) {
                fightOutPokemonInitJoutaiDataId(pokemon, 0x12);
            } else {
                fightOutPokemonSetNowKaisuuJoutaiDataId(pokemon, 0x12, count + 1);
            }
        }
    }
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) <= 0) {
        fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
    }
    return 1;
}

extern "C" {
void fightSeqClearOneTurnCount(s8 flag) {
    u16 i;
    void* side;
    fightFloorLoopValidFightOutPokemon(0, _fightSeqClearOneTurnCountSub, &flag, 0);
    for (i = 0; i < 2; i++) {
        side = fightFloorGetValidFightSidePtr(0, i);
        if (side != 0) {
            fightSideInitJoutaiDataId((u8*)side, 0x4D);
        }
    }
}
}

static s32 _fightSeqTurnCheckSubFightOutPokemon(void* pokemon, u16, void*) {
    if (!fightOutPokemonCheckFightOut(pokemon)) {
        return 1;
    }
    fightOutPokemonInitJoutaiDataId(pokemon, 0x11);
    if (fightOutPokemonIsJoutaiDataId(pokemon, 8) == 1 && fightOutPokemonIsJoutaiDataId(pokemon, 0x22) == 1) {
        fightOutPokemonInitJoutaiKeep(pokemon);
    }
    return 1;
}
