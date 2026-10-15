#include <game/pxdvs/app/fight/fightSeq/fightSeqWSWazaPrivate.hpp>

extern "C" {
void DamageCalcHikaePokemon(void* defPokemon) {
    FightSide* side;
    u32 zokusei;
    FightOutPokemon* attacker;
    u16 useWaza;
    u16 iryoku;
    FightWaza* waza;
    void* arg;
    s32 damage;


    arg = defPokemon;
    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    side = (FightSide*)fightTargetGetPtrAsNowFightType(3, attacker);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    iryoku = fightWaza_GetIryoku(waza);
    zokusei = fightWaza_GetZokusei(waza);
    side = (FightSide*)(u32)fightSeqWazaDamageCalcHikaePokemon(attacker, arg, side, useWaza, iryoku, zokusei);
    damage = (s32)side * fightWaza_GetCritical(waza);
    damage = damage * fightWaza_GetDamageValue(waza);
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x24) == 1 && (u16)zokusei == 0xd) {
        damage *= 2;
    }
    if (fightOutPokemonIsJoutaiDataId(attacker, 0x32) == 1) {
        damage = damage * 15 / 10;
    }
    fightWaza_SetDamage(waza, damage);
}

void CriticalCheckHikaePokemon(void* arg) {
    FightOutPokemon* attacker;
    u32 item;
    FightWaza* waza;
    u16 useWaza;
    u16 defId;
    u8 tokuseiFlag;
    u32 pokeId;
    s32 var30;
    s32 var29;
    s32 sum;
    u8 seqFlag;
    u16 level;
    u16 maxIdx;
    u16 rnd;



    attacker = (FightOutPokemon*)fightTargetGetPtrAsNowFightType(0x11, 0);
    fightOutPokemonGetTokuseiDataId(attacker);
    item = fightOutPokemonGetSoubiItemSoubiDataId(attacker);
    waza = fightOutPokemon_GetFightWazaPtr(attacker);
    useWaza = fightOutPokemon_GetUseWazaDataId(attacker);
    pokeId = figthOutPokemonGetPokemonDataId(attacker);
    defId = pokemon_GetPokemonDataId(fightPokemon_GetPokemonBuffPtr(arg));
    tokuseiFlag = pokemon_GetTokuseiFlag(fightPokemon_GetPokemonBuffPtr(arg));
    var29 = 0;
    if ((u16)item == 0x3f && (u16)pokeId == 0x71) {
        var29 = 1;
    }
    var30 = 0;
    if ((u16)item == 0x42 && (u16)pokeId == 0x53) {
        var30 = 1;
    }
    sum = (fightOutPokemonIsJoutaiDataId(attacker, 0xf) == 1) * 2;
    seqFlag = wazaDB_GetSeqId(useWaza) == 0x2b;
    sum = sum + (u8)(wazaDB_GetSeqId(useWaza) == 0x4b);
    sum = sum + (u8)(wazaDB_GetSeqId(useWaza) == 0xc8);
    maxIdx = fight_waza_critical_data_number - 1;
    level = seqFlag + (sum + (u8)(wazaDB_GetSeqId(useWaza) == 0xd1) + (u8)((u16)item == 0x29) + var29 * 2 + var30 * 2);
    if (level > maxIdx) {
        level = maxIdx;
    }
    if (pokemonDB_GetTokuseiDataId(defId, tokuseiFlag) != 4 && pokemonDB_GetTokuseiDataId(defId, tokuseiFlag) != 0x4b && fightFloor_GetFightKindDoCriticalAttackFlag(0) == 1) {
        rnd = HSD_Rand();
        if (rnd % fightWazaCriticalDataBiosGetBunbo(fightWazaCriticalDataBiosGetPtr(level)) == 0) {
            fightWaza_SetCritical(waza, 2);
        } else {
            fightWaza_SetCritical(waza, 1);
        }
    } else {
        fightWaza_SetCritical(waza, 1);
    }
}
}

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

extern "C" {
void fightSeqPost(void) {
    ServerStatusFlag &= 0xFFEFFFFF;
    fightSeqTurnCheck();
}
}

static s32 _fightSeqPreSub(void* pokemon, u16, void*) {
    if (fightOutPokemonCheckFightOut(pokemon) == 0) {
        return 1;
    }
    void* action = fightOutPokemon_GetFightActionBuffPtr(pokemon);
    if (action == 0) {
        return 1;
    }
    if (fightActionCheckValid(action) == 0) {
        return 1;
    }
    if ((u16)fightOutPokemon_GetMotoWazaDataId(pokemon) == 0x108 && fightOutPokemonIsJoutaiDataId(pokemon, 8) == 0 && fightOutPokemon_GetNamakeFlag(pokemon) == 0) {
        fightSeqFightActionCreateAndFlowFifo(fightActionBiosGetFightActionDataPtr(fight_seq_now_fight_action_ptr), pokemon, 0xc, 0, fight_action_data_turn, WAZA_KiaiPunch);
    }
    return 1;
}

extern "C" {
void fightSeqExec(void* actionPtr, u8* seq, u8 flag) {
    void* savedAction;
    u8 savedSeqNo;
    u8* savedSeq;

    savedAction = fight_seq_now_fight_action_ptr;
    savedSeqNo = ActionSeqNo;
    savedSeq = fightSeq_GetWazaSeq();
    fightSeq_JumpWazaSeq(seq);
    if (flag == 0) {
        ActionSeqNo = 0;
    }
    fight_seq_now_fight_action_ptr = actionPtr;
    for (;;) {
        WazaSequenceTbl[(u16)*fightSeq_GetWazaSeq()]();
        if (flag != 0) {
            if (ActionSeqNo == 1) {
                SCA_EndCheck();
            }
            if (ActionSeqNo == 2) {
                SCA_End();
                break;
            }
        } else if (ActionSeqNo == 1 || ActionSeqNo == 2) {
            break;
        }
    }
    if (flag != 0) {
        ServerStatusFlag &= 0xFFFFFDFF;
        ServerStatusFlag &= 0xFFF7FFFF;
    }
    fight_seq_now_fight_action_ptr = savedAction;
    ActionSeqNo = savedSeqNo;
    fightSeq_JumpWazaSeq(savedSeq);
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
