#include <game/pxdvs/app/fight/fightSeq/fightSeqSpActionPrivate.hpp>

static s32 _WsScaEndSetSub(void*, u16, void*);

extern "C" {
void fightSeqVanishOff(FightOutPokemon*);

void WS_TOKUSEI_SET(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    FightPokemon* fightPokemon = fightOutPokemon_GetFightPokemonPtr(pokemon);
    FIGHT_TRAINER* trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon);
    FIGHT_TRAINER* enemyA = (FIGHT_TRAINER*)fightTargetGetPtr(9, (FightOutPokemon*)trainer, fightFloor_GetFightType(0));
    FIGHT_TRAINER* enemyB = (FIGHT_TRAINER*)fightTargetGetPtr(10, (FightOutPokemon*)trainer, fightFloor_GetFightType(0));
    s32 entryId = fightPokemon_GetEntryId(fightPokemon);
    if (enemyA != 0) {
        if (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(enemyA))) == 1) {
            fightTrainer_SetEnemyTokuseiFlag(enemyA, entryId, 1);
            fightTrainer_SetEnemyStoreTokuseiData(enemyA, entryId, fightOutPokemon_GetTokuseiDataId(pokemon));
        }
    }
    if (enemyB != 0) {
        if (fightTrainerAiDB_GetParamStoreFlag(fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(enemyB))) == 1) {
            fightTrainer_SetEnemyTokuseiFlag(enemyB, entryId, 1);
            fightTrainer_SetEnemyStoreTokuseiData(enemyA, entryId, fightOutPokemon_GetTokuseiDataId(pokemon));
        }
    }
    fightSeq_NextWazaSeq(2);
}

void WS_SUBROUTINE_CALL(void) {
    u8 type = fightFloor_GetFightType(0);
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    u16 move = fightOutPokemon_GetUseWazaDataId(pokemon);
    switch (seq[2]) {
    case 0:
        fightOutPokemonInitJoutaiKeep(pokemon);
        break;
    case 1: {
        fightTargetGetPtrAsNowFightType(0x11, 0);
        FightOutPokemon* defender = fightTargetGetPtrAsNowFightType(0x12, 0);
        fightFloor_SetAttackPokemonPtr(0, defender);
        FightOutPokemon* target = fightSeqGetEnemyFightSideKonoyubitomareFightOutPokemonPtr(defender);
        if (target == 0) target = pokemon;
        fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, target);
        break;
    }
    case 2:
        ServerWork.flags[0] = EscapeNGCheck(fightTargetGetPtrAsNowFightType(0x11, 0));
        break;
    case 3: {
        FightOutPokemon* target = fightSeqSelectDefensePokemonPtr(pokemon, move, type, 0, 1, 1, -1);
        if (target != 0) fightFloor_SetDefPokemonAndAtkFightWazaTargetId(0, target);
        break;
    }
    case 4:
        if (fightOutPokemon_GetKizetuFlag(pokemon) == 1) {
            ServerWork.flags[0] = 1;
        } else {
            ServerWork.flags[0] = 0;
        }
        break;
    case 6: {
        FightPokemon* expPokemon = get_exp_fight_pokemon_ptr;
        if (expPokemon != 0) {
            FIGHT_TRAINER* trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(0, expPokemon);
            if (trainer != 0) {
                FightOutPokemon* out = fightTrainerCheckFightPokemonFightOut(trainer, expPokemon);
                if (out != 0) {
                    if (fightOutPokemonIsJoutaiDataId(out, 0x36) == 1) {
                        s32 id = fightOutPokemonGetIdBuffJoutaiDataId(out, 0x36);
                        if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(out), id) < 0) {
                            fightOutPokemonInitJoutaiDataId(out, 0x36);
                        }
                    }
                }
            }
        }
        break;
    }
    case 7:
        fightMenuFightOutPokemonOpenStatusMenu(pokemon, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
        break;
    }
    fightSeq_NextWazaSeq(3);
}

struct SpActionItemEffect {
    s32 id;
    s16 value;
};

void WS_STATUS_RECOVER(void) {
    Pokemon* poke;
    FightWaza* waza;
    s32 damage;
    s32 hp;
    FightOutPokemon* pokemon;
    FightPokemon* fightPokemon;
    FightPokemon* motoPokemon;
    s32 itemId;
    u8 itemType;
    void* sequence;
    s16 count;
    u16 i;
    SpActionItemEffect effects[32];
    damage = 0;
    fightSeq_GetWazaSeq();
    pokemon = fightTargetGetPtrAsNowFightType(0x11, 0);
    waza = fightOutPokemon_GetFightWazaPtr(pokemon);
    fightPokemon = fightOutPokemon_GetFightPokemonPtr(pokemon);
    motoPokemon = fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    poke = fightPokemonGetPokemonPtr(fightPokemon);
    hp = pokemon_GetHp(poke);
    itemId = fightItem_GetItemDataId(fightOutPokemon_GetFightItemPtr(pokemon));
    itemType = fightSeqGetItemType(pokemon);
    sequence = fightOutPokemon_GetSequencePtr(pokemon);
    count = itemUse2Pokemon(effects, 0, motoPokemon, itemId, 0);
    if (itemType == 1 || itemType == 2) {
        for (i = 0; i < count; i++) {
            if (effects[i].id == 0x15) damage = effects[i].value;
        }
        pokemon_SetHp(poke, hp);
        fightWaza_SetDamage(waza, -damage);
    }
    for (i = 0; i < count; i++) {
        if (effects[i].id == 0xf) Sequence_ResetStatus(sequence, 2);
        if (effects[i].id == 9) Sequence_ResetStatus(sequence, 1);
    }
    fightSeq_NextWazaSeq(1);
}

void WS_POKE_HPDEC_RATE(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    bool isHero = fightOutPokemonIsGcHeroFightOutPokemon(pokemon) == 1;
    bool isTuusin = fightFloorIsNowEncountTuusinTaisen(0) == 1;
    if (fightTrainerGetPrefixNamePtr(trainer) == 0 && isHero == 0) {
        isTuusin = 1;
    }
    fightMsgctrlSetValue(0x16, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    fightMsgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    fightMsgctrlSetValue(0x22, (u32)fightTrainerGetPrefixNamePtr(trainer));
    fightMsgctrlSetValue(0x23, (u32)fightTrainerGetNamePtr(trainer));
    fightMsgctrlSetValue(0x25, (u32)fightTrainerGetNamePtr(trainer));
    if (isTuusin == 1) {
        ServerWork.flags[5] = 5;
    } else if (isHero == 1) {
        s32 rate = fightFloorGetEnemyFightSideManyDamageHpRate(0, pokemon);
        if (rate < 0) {
            ServerWork.flags[5] = 1;
        } else if (rate == 0) {
            ServerWork.flags[5] = 0;
        } else if (rate < 0x1e) {
            ServerWork.flags[5] = 1;
        } else if (rate < 0x46) {
            ServerWork.flags[5] = 2;
        } else {
            ServerWork.flags[5] = 3;
        }
    } else {
        ServerWork.flags[5] = 4;
    }
    fightSeq_NextWazaSeq(2);
}

void WS_POKE_HPMAX_RATE(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    bool isHero = fightOutPokemonIsGcHeroFightOutPokemon(pokemon) == 1;
    bool isTuusin = fightFloorIsNowEncountTuusinTaisen(0) == 1;
    if (fightTrainerGetPrefixNamePtr(trainer) == 0 && isHero == 0) {
        isTuusin = 1;
    }
    fightMsgctrlSetValue(0x16, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    fightMsgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    fightMsgctrlSetValue(0x22, (u32)fightTrainerGetPrefixNamePtr(trainer));
    fightMsgctrlSetValue(0x23, (u32)fightTrainerGetNamePtr(trainer));
    fightMsgctrlSetValue(0x25, (u32)fightTrainerGetNamePtr(trainer));
    if (isTuusin == 1) {
        ServerWork.flags[5] = 5;
    } else if (isHero == 1) {
        s32 rate = fightFloorGetEnemyFightSideLittleNokoriHpRate(0, pokemon);
        if (rate >= 0x46 || rate < 0) {
            ServerWork.flags[5] = 0;
        } else if (rate >= 0x28) {
            ServerWork.flags[5] = 1;
        } else if (rate >= 10) {
            ServerWork.flags[5] = 2;
        } else {
            ServerWork.flags[5] = 3;
        }
    } else {
        ServerWork.flags[5] = 4;
    }
    fightSeq_NextWazaSeq(2);
}

void WS_ESCAPE_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}

void WS_TOKUSYUNO_SET(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_VANISH_OFF(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    if (pokemon != 0) {
        fightSeqVanishOff(pokemon);
    }
    fightSeq_NextWazaSeq(2);
}

void fightSeqVanishOff(FightOutPokemon* pokemon) {
    fightOutPokemonSetVisibility(pokemon, 1);
    void* sequence = fightOutPokemon_GetSequencePtr(pokemon);
    if (sequence != 0) {
        Sequence_ResetStatus(sequence, 3);
    }
}

void WS_GET_RESHUFFLE_CLIENT(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_EXPFLAG_CLEAR(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_STATUS_WINDOW(void) {
    u8 current[16];
    u8 previous[16];
    FightPokemon* pokemon = get_exp_fight_pokemon_ptr;
    fightSeq_GetWazaSeq();
    fightPokemonToMenuLvupStatus(pokemon, current);
    fightMenuSubMenuLvupStatus(current, old_menu_lvup_status, previous);
    fightMenuOpenLevelUpStatusMenu(previous, 1);
    fightMenuOpenLevelUpStatusMenu(current, 0);
    fightMenuCloseLevelUpStatusMenu();
    fightSeq_NextWazaSeq(1);
}

void WS_RESHUFFLE_NICKNAME(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_KILLITEM(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    fightOutPokemonDoItemSoubi(pokemon, 0, 0, 1);
    fightSeqCheckSetHensinBuffToMotoPokemon(pokemon, 0x82);
    fightSeq_NextWazaSeq(2);
}

void WS_KORAERU_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeqDamageLoss(1, 0);
    fightSeq_NextWazaSeq(1);
}

void WS_SCA_END_SET(void) {
    fightSeq_GetWazaSeq();
    fightFloorLoopValidFightOutPokemon(0, _WsScaEndSetSub, 0, 0);
    fightSeq_NextWazaSeq(1);
}

}

static s32 _WsScaEndSetSub(void* pokemon, u16, void*) {
    fightOutPokemon_SetFightActionFlag((FightOutPokemon*)pokemon, 1);
    return 1;
}

extern "C" {
void WS_YES_NO_WINDOW(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_STATUS_EFFECT_DIRECT(void) {
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    u32 kind = *(u32*)(seq + 3);
    if (!(ServerStatusFlag & 0x80) && kind == 7) {
        fightSeqFightOutPokemonEffect(0x34, pokemon, 0, 1);
    }
    fightSeq_NextWazaSeq(7);
}

void WS_STATUS_EFFECT2(void) {
    fightFloor_GetFightType(0);
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    u32 kind = *(u32*)(seq + 2);
    if (!(ServerStatusFlag & 0x80)) {
        if (kind == 9) fightSeqFightOutPokemonEffect(0x34, pokemon, 0, 1);
        if (kind == 0x18) fightSeqFightOutPokemonEffect(0x35, pokemon, 0, 1);
        if (kind == 0x17) fightSeqFightOutPokemonEffect(0x36, pokemon, 0, 1);
        if (kind == 10) fightSeqFightOutPokemonEffect(0x37, pokemon, 0, 1);
    }
    fightSeq_NextWazaSeq(6);
}

void WS_STATUS_EFFECT(void) {
    fightFloor_GetFightType(0);
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    if (!(ServerStatusFlag & 0x80)) {
        if (fightOutPokemonIsJoutaiDataId(pokemon, 8) == 1) fightSeqFightOutPokemonEffect(0x2e, pokemon, 0, 1);
        if (fightOutPokemonIsJoutaiDataId(pokemon, 5) == 1) fightSeqFightOutPokemonEffect(0x2f, pokemon, 0, 1);
        if (fightOutPokemonIsJoutaiDataId(pokemon, 7) == 1) fightSeqFightOutPokemonEffect(0x30, pokemon, 0, 1);
        if (fightOutPokemonIsJoutaiDataId(pokemon, 6) == 1) fightSeqFightOutPokemonEffect(0x31, pokemon, 0, 1);
        if (fightOutPokemonIsJoutaiDataId(pokemon, 3) == 1) fightSeqFightOutPokemonEffect(0x32, pokemon, 0, 1);
        if (fightOutPokemonIsJoutaiDataId(pokemon, 4) == 1) fightSeqFightOutPokemonEffect(0x33, pokemon, 0, 1);
    }
    fightSeq_NextWazaSeq(2);
}

void WS_WAZASEQADRS(void) {
    fightFloor_GetFightType(0);
    u8* seq = fightSeq_GetWazaSeq();
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    u16 move = PushWazaNo;
    u16 seqId = wazaDB_GetSeqId(move);
    if (seq[1] != 0) {
        fightWazaSetUseWazaStatus(waza, move);
    } else {
        fightWaza_SetMotoWazaDataId(waza, move);
        fightWazaSetUseWazaStatus(waza, move);
    }
    fightSeq_JumpWazaSeq(WazaEffectTbl[seqId]);
}

void WS_BALL_GAUGE_OFF(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2);
}

void WS_BALL_GAUGE_SET(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2);
}

void WS_INC_RECORD(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2);
}

void WS_SWITCH_A_D(void) {
    fightSeq_GetWazaSeq();
    fightFloorReplaceFightOutPokemonAttackToDefense(0);
    s32 flag = ServerStatusFlag | 0x1000;
    if (ServerStatusFlag & 0x1000) {
        flag = ServerStatusFlag & ~0x1000;
    }
    ServerStatusFlag = flag;
    fightSeq_NextWazaSeq(1);
}

void WS_WAZA_GET(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_OKODUKAI_CALC(void) {
    u16 syoukin;
    u8 okaneBai;
    u8* seq;
    FIGHT_TRAINER* trainer;
    Hero* hero;
    u8 maxLevel;
    u8 count;
    s32 j;
    FightPokemon* p1;
    FightPokemon* p2;
    FIGHT_TRAINER* enemy;
    u32 money;
    s32 i;
    u16 rate;
    seq = fightSeq_GetWazaSeq();
    count = fightFloor_GetFightTypeFightoutPokemonNum(0);
    if (fightFloor_GetFightKindGetOkaneFlag(0) == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    trainer = fightFloorGetGcHeroFightTrainerPtr(0);
    if (trainer == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    okaneBai = fightTrainer_GetOkaneBai(trainer);
    enemy = (FIGHT_TRAINER*)fightTargetGetPtrAsNowFightType(9, (FightOutPokemon*)trainer);
    syoukin = fightTrainerKindDataBiosGetSyoukinBairitu(fightTrainerKindDataBiosGetPtr(fightTrainerDB_GetKindDataId(fightTrainer_GetFightTrainerDataId(enemy))));
    maxLevel = 0;
    i = 0;
    do {
        p1 = fightTrainer_GetFightPokemonPtr(enemy, i);
        if (fightPokemonCheckValid(p1) != 0) {
            u8 level = figthPokemonGetLevel(p1);
            if (maxLevel < level) maxLevel = level;
        }
        i++;
    } while (i < 6);
    j = 0;
    do {
        p2 = fightTrainer_GetFightPokemonPtr(trainer, j);
        if (fightPokemonCheckValid(p2) != 0 && fightPokemon_GetCatchEntryFlag(p2) == 1) {
            u8 level = figthPokemonGetLevel(p2);
            if (maxLevel < level) maxLevel = level;
        }
        j++;
    } while (j < 6);
    if (fightFloor_GetFightKindOkanePoolFlag(0) == 0) {
        if (count <= 1) {
            rate = 1;
        } else {
            rate = 2;
        }
    } else {
        rate = 4;
    }
    money = rate * (syoukin * (maxLevel * okaneBai));
    if (fightFloor_GetFightKindOkanePoolFlag(0) == 1) {
        scriptAddPremium(money);
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
        return;
    }
    heroAddPokedoru(hero, money);
    fightMsgctrlSetValue(0x2f, money);
    fightMsgctrlSetValue(0x4b, money);
    fightMsgctrlSetValue(0x13, heroGetStatus(hero, 1, 0));
    fightSeq_NextWazaSeq(5);
}

void WS_POKE_BLINK(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
    if (fightWazaIsHit(waza) == 1) {
        if (ServerStatusFlag & 0x100) {
            fightSeq_NextWazaSeq(2);
            return;
        }
        if (ServerStatusFlag & 0x80) {
            fightOutPokemonDamageEffect(pokemon);
        }
    }
    fightSeq_NextWazaSeq(2);
}

void WS_WAZAAKIRAME_CHECK(void) {
    u8* seq = fightSeq_GetWazaSeq();
    if (fightMenuYesNo() == 1) {
        u8 banme = waza_oboe_banme;
        waza_oboe_banme = banme + 1;
        fightSeq_NextWazaSeq(5);
    } else {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
    }
}

void WS_WAZAWASURE_CHECK(void) {
    u8* seq;
    s32 slot;
    u16 move;
    Pokemon* pokemon;
    char* name;
    pokemon = fightPokemonGetPokemonPtr(get_exp_fight_pokemon_ptr);
    seq = fightSeq_GetWazaSeq();
    if (fightMenuYesNo() == 1) {
        while (1) {
            fightMenuCloseMsg();
            slot = fightMenuWazaWasure(pokemon, OboeWazaNo);
            if (slot == -1 || slot >= 4) break;
            move = pokemon_GetPokemonWazaDataId(pokemon, slot);
            if (wazaDB_GetHidenFlag(move) == 1) {
                if (fightMenuOpenMsg(0x4f1e) == 1) {
                    fightMenuCloseMsg();
                }
                continue;
            }
            pokemonWazaCreate(pokemon, slot, OboeWazaNo);
            name = GSmsgGetGSchar((u32)wazaDB_GetName(move));
            fightMsgctrlSetValue(0xe, (u32)name);
            fightMsgctrlSetValue(0x5d, 0x21);
            fightSeq_JumpWazaSeq(*(u8**)(seq + 1));
            return;
        }
    }
    fightSeq_NextWazaSeq(5);
}

void WS_WAZAOBOE_CHECK(void) {
    u8* learnSeq;
    u8* skipSeq;
    FightPokemon* expPokemon;
    u8 level;
    Pokemon* pokemon;
    u8* seq;
    s8 result;
    expPokemon = get_exp_fight_pokemon_ptr;
    level = figthPokemonGetLevel(expPokemon);
    pokemon = fightPokemonGetPokemonPtr(expPokemon);
    seq = fightSeq_GetWazaSeq();
    learnSeq = *(u8**)(seq + 1);
    skipSeq = *(u8**)(seq + 5);
    if (seq[9] != 0) {
        waza_oboe_banme = pokemonGetOboeWazaDataBanme(pokemon, level);
    }
    while (1) {
        result = pokemonOboeWaza(pokemon, level, 0, &waza_oboe_banme);
        if (result == -1) {
            OboeWazaNo = pokemonGetOboeWazaDataId(pokemon, level, &waza_oboe_banme);
            fightSeq_NextWazaSeq(10);
            return;
        } else if (result == -2) {
            waza_oboe_banme = waza_oboe_banme + 1;
        } else if (result == -3) {
            fightSeq_JumpWazaSeq(skipSeq);
            return;
        } else {
            waza_oboe_banme++;
            OboeWazaNo = pokemon_GetPokemonWazaDataId(pokemon, result);
            fightSeq_JumpWazaSeq(learnSeq);
            return;
        }
    }
}

void WS_OBOEWAZANO_SET(void) {
    FightPokemon* expPokemon = get_exp_fight_pokemon_ptr;
    char* name = GSmsgGetGSchar((u32)wazaDB_GetName(OboeWazaNo));
    char* nickname = fightPokemonGetNicknamePtr(expPokemon);
    fightSeq_GetWazaSeq();
    fightMsgctrlSetValue(0xd, (u32)nickname);
    fightMsgctrlSetValue(0xe, (u32)name);
    fightSeq_NextWazaSeq(1);
}

void WS_POKEDELACTOR(void) {
    FightOutPokemon* pokemon;
    u8 type;
    type = fightFloor_GetFightType(0);
    pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    if (fightOutPokemonCheckFightOut(pokemon) == 1) {
        fightOutPokemonModosuEffect(pokemon, 0);
        fightMenuFightOutPokemonOpenStatusMenu(pokemon, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
        fightOutPokemonModosuEffect(pokemon, 1);
        fightOutPokemonModosuEffect(pokemon, 2);
        fightOutPokemonModosuEffect(pokemon, 3);
        fightOutPokemonModosuEffect(pokemon, 4);
        fightMenuFightOutPokemonCloseStatusMenu(pokemon, type, 0);
    }
    fightSeq_NextWazaSeq(2);
}

void WS_END_FIGHT(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_VOICE(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    GSsndPlayVolume(fightOutPokemonGetVoiceSndId(pokemon), 0, 0xff, 0);
    fightSeq_NextWazaSeq(2);
}

void WS_ME_PLAY(void) {
    soundOpenPlayME(*(u16*)(fightSeq_GetWazaSeq() + 1), 0, 0xff);
    fightSeq_NextWazaSeq(3);
}

void WS_SE_PLAY(void) {
    GSsndPlayVolume(*(u16*)(fightSeq_GetWazaSeq() + 1), 0, 0xff, 0);
    fightSeq_NextWazaSeq(3);
}

void WS_TRAINER_APPEAR(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(2);
}

void WS_POKE_RESHUFFLE_END(void) {
    u8 saved[0xac];
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    FightSide* side = (FightSide*)fightTargetGetPtrAsNowFightType(2, pokemon);
    u16 tokusei = fightOutPokemonGetTokuseiDataId(pokemon);
    fightFloorSetMeetEnemyFightPokemonEnemySideAll(0);
    fightFloorRegistFightTrainerEnemyPokemonFightSideAll(0);
    fightOutPokemon_SetIrekaetaFlag(pokemon, 0);
    fightOutPokemon_SetIrekaeTargetEntryId(pokemon, -1);
    if (fightSide_GetMakibisiCheckFlag(side) == 0 && fightSideIsJoutaiDataId(side, 0x4a) == 1 &&
        fightOutPokemonIsZokuseiDataId(pokemon, 2) == 0 && tokusei != 0x1a) {
        fightSide_SetMakibisiCheckFlag(side, 1);
        ServerStatusFlag &= ~0x40;
        fightOutPokemonInitJoutaiDataId(pokemon, 0x15);
        u16 damage = fightOutPokemonMaxHpWaruValue(pokemon, (5 - fightSideGetCountAsJoutaiDataId(side, 0x4a)) * 2);
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(fightTargetGetPtrAsNowFightType(0x11, 0));
        fightWazaBiosCopy(saved, waza);
        fightWaza_SetDamage(waza, damage);
        fightWazaInitJoutai(waza);
        fightFloor_SetAppointPokemonPtr(0, pokemon);
        u8* callSeq;
        u8 target = seq[1];
        if (target == 0x12) {
            callSeq = WAZA_MakibishiD;
        } else if (target == 0x11 || target == 0x14) {
            callSeq = WAZA_MakibishiA;
        } else {
            callSeq = WAZA_MakibishiK;
        }
        fightSeq_CallWazaSeq(callSeq);
        fightWazaBiosCopy(waza, saved);
        if (fightSide_GetMakibisiCheckFlag(side) == 0) {
            fightSeq_NextWazaSeq(2);
            return;
        }
    }
    if (fightOutPokemonGetTokuseiDataId(pokemon) == 0x36) {
        fightOutPokemon_SetNamakeFlag(pokemon, 1);
    }
    fightSeqFightOutPokemonDarkCheckAppear(pokemon, 0);
    fightSeqFightOutPokemonTokuseiCheckAppear(pokemon);
    fightSeqPokemonSoubiItemCheckAppear(pokemon);
    fightSeqFightOutPokemonDarkCheckAppear(pokemon, 1);
    fightFloorCreateFightPokemonEnemyAryEnemySideAll(0);
    fightSide_SetMakibisiCheckFlag(side, 0);
    fightSeq_NextWazaSeq(2);
}

void WS_POKE_RESHUFFLE_WAIT(void) {
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    switch (seq[2]) {
    case 0:
    case 1:
        break;
    case 2:
        fightMsgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(pokemon));
        fightMsgctrlSetValue(0xe, (u32)fightOutPokemonGetNamePtr(pokemon));
        break;
    }
    fightSeq_NextWazaSeq(3);
}

void WS_POKE_RESHUFFLE(void) {
    u8* failSeq;
    FightOutPokemon* pokemon;
    FIGHT_TRAINER* trainer;
    s16 entry;
    u8 type;
    s16 search;
    u8* seq;
    type = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    failSeq = *(u8**)(seq + 2);
    pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    if (fightOutPokemon_GetIrekaetaFlag(pokemon) == 1) {
        fightSeq_NextWazaSeq(6);
        return;
    }
    search = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &search) == 0) {
        fightSeq_JumpWazaSeq(failSeq);
        return;
    }
    entry = fightTrainerSelectIrekaeFightPokemon(trainer, type, 0, pokemon);
    if (entry < 0) {
        if (entry == -2) {
            fightFloorSetTuusinErrorFightResult(0);
        }
        fightSeq_JumpWazaSeq(failSeq);
        return;
    }
    fightFloor_SetIrekaePokemonPtr(0, pokemon);
    fightOutPokemon_SetIrekaeTargetEntryId(pokemon, entry);
    fightOutPokemon_SetIrekaetaFlag(pokemon, 1);
    fightSeq_NextWazaSeq(6);
}

void WS_RESHUFFLE_CHECK(void) {
    s16 search;
    u8* seq = fightSeq_GetWazaSeq();
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    if (seq[6] == 1 && fightFloorCheckFightActionFightOutPokemonIrekaeSelect(0, pokemon, 0) == 1) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 2));
        return;
    }
    search = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &search) == 0) {
        fightSeq_JumpWazaSeq(*(u8**)(seq + 2));
        return;
    }
    fightSeq_NextWazaSeq(7);
}

void WS_APPEAR_EFFECT_WAIT(void) {
    u16 encount;
    FightOutPokemon* pokemon;
    FightOutPokemon* buff;
    FIGHT_TRAINER* trainer;
    u8 type;
    u8 mode;
    Pokemon* poke;
    u8* seq;
    type = fightFloor_GetFightType(0);
    seq = fightSeq_GetWazaSeq();
    mode = seq[2];
    pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    buff = fightTrainer_GetFightoutPokemonBuffPtr(trainer);
    poke = fightOutPokemonGetPokemonPtr(pokemon);
    encount = fightFloor_GetEncountDataId(0);
    if (mode != 2) {
        fightTrainerBallThrowEffect(trainer, pokemon, 2);
    }
    if (fightOutPokemonIsGcHeroFightOutPokemon(pokemon) == 0) {
        fightMenuFightOutPokemonOpenStatusMenuStart(pokemon, type, 0);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
    } else {
        fightMenuFightOutPokemonOpenStatusMenuStart(pokemon, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
    }
    if (mode != 2) {
        fightOutPokemonDasuEffect(trainer, pokemon, 1);
        fightOutPokemonDasuEffect(trainer, pokemon, 2);
    }
    fightOutPokemonDasuEffect(trainer, pokemon, 3);
    fightOutPokemonDasuEffect(trainer, pokemon, 4);
    fightMenuFightOutPokemonCloseStatusMenu(pokemon, type, 0);
    if (mode != 2) {
        fightTrainerBallThrowEffect(trainer, pokemon, 3);
    }
    fightOutPokemonDasuEffect(trainer, pokemon, 5);
    if (mode == 1 && fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) > 0) {
        fightMenuCloseMsg();
        fightWazaWzxTypeFuncMigawari(0xa4, pokemon, pokemon, 0, 0);
        while (1) {
            if (wazaSequenceSysLastWazaIsImpactPoint(4) == 1) break;
            GSthreadSwitch();
        }
        fightOutPokemonFreeAllSequenceWaza(pokemon);
    }
    if (fightFloor_GetFightKindDoZukanMitaFlag(0) == 1 && fightOutPokemonIsGcHeroFightOutPokemon(pokemon) == 0) {
        fightOutPokemonSetOnZukanFlag(pokemon, 0);
        if (encount != 0xd9 && encount != 0x15e && pokemonIsDarkPokemon(poke) == 1) {
            darkPokemonBiosSetFightFlag(pokemon_GetDarkpokemonDataId(poke), 0);
        }
    }
    fightOutPokemonInit(buff);
    fightSeq_NextWazaSeq(3);
}

void WS_APPEAR_EFFECT(void) {
    u8 mode;
    FightOutPokemon* pokemon;
    FightOutPokemon* buff;
    FIGHT_TRAINER* trainer;
    FightPokemon* moto;
    void* trainerSeq;
    s32 entryId;
    u8* seq;
    void* newSeq;
    void* pokemonSeq;
    seq = fightSeq_GetWazaSeq();
    mode = seq[2];
    pokemon = fightTargetGetPtrAsNowFightType(seq[1], 0);
    entryId = fightOutPokemon_GetIrekaeTargetEntryId(pokemon);
    moto = fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    buff = fightTrainer_GetFightoutPokemonBuffPtr(trainer);
    if (fightPokemonIsJoutaiDataId(moto, 4) == 1) {
        fightPokemonSetCountAsJoutaiDataId(moto, 4, 1);
    }
    fightPokemonReplace(fightTrainerGetEntryIdToFightPokemonPtr(trainer, entryId), moto);
    menuFaceLoadFightPokemon(moto, 0, 0);
    newSeq = pokemonCreateSequence(moto);
    fightOutPokemonCreate(pokemon, moto, newSeq);
    fightOutPokemonRegWzxLoad(pokemon);
    fightSeqIrekaeInit(pokemon, buff, mode);
    fightMsgctrlSetValue(0xd, (u32)fightOutPokemonGetNicknamePtr(pokemon));
    trainerSeq = fightTrainer_GetSequencePtr(trainer);
    if (trainerSeq != 0) {
        pokemonSeq = fightOutPokemon_GetSequencePtr(pokemon);
        if (pokemonSeq != 0) {
            battleGridAddPokemon(trainerSeq, pokemonSeq);
        }
    }
    if (mode != 2) {
        fightTrainerBallThrowEffect(trainer, pokemon, 0);
    }
    fightOutPokemonDasuEffect(trainer, pokemon, 0);
    battleGridUpdate();
    if (mode != 2) {
        fightTrainerBallThrowEffect(trainer, pokemon, 1);
    }
    fightSeq_NextWazaSeq(3);
}

void WS_APPEAR_EFFECT_INIT(void) {
    FightOutPokemon* pokemon = fightTargetGetPtrAsNowFightType(fightSeq_GetWazaSeq()[1], 0);
    FIGHT_TRAINER* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, pokemon);
    fightOutPokemonBiosCopy(fightTrainer_GetFightoutPokemonBuffPtr(trainer), pokemon);
    fightSeq_NextWazaSeq(2);
}

void WS_MODOSU_EFFECT(void) {
    FightOutPokemon* pokemon;
    u8 type;
    type = fightFloor_GetFightType(0);
    fightSeq_GetWazaSeq();
    pokemon = fightTargetGetPtrAsNowFightType(0x14, 0);
    if (fightOutPokemonCheckFightOut(pokemon) == 1) {
        if (fightOutPokemonIsJoutaiDataId(pokemon, 0x14) == 1 && fightOutPokemonGetJoutaiMigawariHp(pokemon) > 0) {
            fightOutPokemonInitJoutaiDataId(pokemon, 0x14);
            fightOutPokemonFreeAllSequenceWaza(pokemon);
            fightWazaWzxTypeFuncMigawari(0xa4, pokemon, pokemon, 0, 0);
            while (1) {
                if (wazaSequenceSysLastWazaIsImpactPoint(4) == 1) break;
                GSthreadSwitch();
            }
        }
        fightOutPokemonFreeAllSequenceWaza(pokemon);
        fightOutPokemonModosuEffect(pokemon, 0);
        fightMenuFightOutPokemonOpenStatusMenu(pokemon, type, 1);
        fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, pokemon, type, 0, 1);
        fightOutPokemonModosuEffect(pokemon, 1);
        fightOutPokemonModosuEffect(pokemon, 2);
        fightOutPokemonModosuEffect(pokemon, 3);
        fightOutPokemonModosuEffect(pokemon, 4);
        fightMenuFightOutPokemonCloseStatusMenu(pokemon, type, 0);
    }
    fightSeq_NextWazaSeq(1);
}
}
