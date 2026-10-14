#include <game/pxdvs/app/fight/fightPokemon.hpp>

inline void copyFightPokemonRecord(FightPokemon* target, const FightPokemon* source) {
    target->motoPokemon = source->motoPokemon;
    memcpy(&target->pokemonBuff, &source->pokemonBuff, sizeof(Pokemon));
    target->state = source->state;
}

extern "C" {
u32 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
void pokemon_SetPokemonWazaDataId(Pokemon*, u16, u16);
void pokemon_SetPokemonWazaPp(Pokemon*, u16, u8);
u8 wazaDB_GetPp(u16);
u16 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon*, u16);
u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon*, u8);
void fightOutPokemonSetZokuseiDataId(FightOutPokemon*, u8, u16);

void fightOutPokemonSetHensinStatusAfterLevelUp(FightOutPokemon* poke) {
    u16 properties[18] = {
        0x7a, 0x83, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d,
        0x8e, 0x8f, 0x90, 0x91, 0x92, 0x99, 0xc7, 0x79, 0xc6
    };
    for (u8 i = 0; i < 18; i++) {
        fightOutPokemonSetHensinPokemonStatusId(poke, properties[i], 0, 1);
    }
}

void fightOutPokemonSetHensinFightPokemonStatusId(FightOutPokemon* poke, u16 property, u8 direction) {
    FightPokemon* source;
    FightPokemon* target;
    if (direction == 1) {
        source = fightOutPokemon_GetMotoFightPokemonPtr(poke);
        target = fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
    } else {
        source = fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
        target = fightOutPokemon_GetMotoFightPokemonPtr(poke);
    }
    if (source != nullptr && target != nullptr) {
        u32 value = pokemonGetStatus(reinterpret_cast<Pokemon*>(source), 0, property, 0);
        pokemonSetStatus(reinterpret_cast<Pokemon*>(target), 0, property, 0, value);
    }
}

void fightOutPokemonSetHensinPokemonStatusId(FightOutPokemon* poke, u16 property, u16 index, u8 direction) {
    FightPokemon* sourceFight;
    FightPokemon* targetFight;
    if (direction == 1) {
        sourceFight = fightOutPokemon_GetMotoFightPokemonPtr(poke);
        targetFight = fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
    } else {
        sourceFight = fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
        targetFight = fightOutPokemon_GetMotoFightPokemonPtr(poke);
    }
    if (sourceFight != nullptr && targetFight != nullptr) {
        Pokemon* source = fightPokemonGetPokemonPtr(sourceFight);
        Pokemon* target = fightPokemonGetPokemonPtr(targetFight);
        if (property == 0x7c) {
            target->copyCondition(source);
        } else if (property == 0xc8) {
            target->setReversMode(source->isReversMode());
        } else {
            u32 value = pokemonGetStatus(source, 0, property, index);
            pokemonSetStatus(target, 0, property, index, value);
        }
    }
}

void fightOutPokemonCopyHensinStatus(FightOutPokemon* sourceFight, FightOutPokemon* targetFight) {
    u16 properties[14] = { 0x6e, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0xb6, 0xb7 };
    u16 stages[7] = { 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec };
    if (sourceFight != nullptr && targetFight != nullptr) {
        Pokemon* source = fightOutPokemonGetPokemonPtr(sourceFight);
        Pokemon* target = fightOutPokemonGetPokemonPtr(targetFight);
        u16 property;
        u8 i;
        for (i = 0; i < 14; i++) {
            property = properties[i];
            u32 value = pokemonGetStatus(source, 0, property, 0);
            pokemonSetStatus(target, 0, property, 0, value);
        }
        for (i = 0; i < 4; i++) {
            u16 move = pokemon_GetPokemonWazaDataId(source, i);
            pokemon_SetPokemonWazaDataId(target, i, move);
            if (wazaDB_GetPp(move) < 5) {
                pokemon_SetPokemonWazaPp(target, i, wazaDB_GetPp(move));
            } else {
                pokemon_SetPokemonWazaPp(target, i, 5);
            }
        }
        for (i = 0; i < 7; i++) {
            property = stages[i];
            pokemonSetStatus(reinterpret_cast<Pokemon*>(targetFight), 0, property, 0,
                pokemonGetStatus(reinterpret_cast<Pokemon*>(sourceFight), 0, property, 0));
        }
        fightOutPokemonSetTokuseiDataId(targetFight, fightOutPokemonGetTokuseiDataId(sourceFight));
        for (u8 i = 0; i < 2; i++) {
            fightOutPokemonSetZokuseiDataId(targetFight, i, fightOutPokemonGetZokuseiDataId(sourceFight, i));
        }
    }
}

bool fightOutPokemonUseHensinBuff(FightOutPokemon* poke) {
    if (poke == nullptr) return false;
    FightPokemon* source = fightOutPokemon_GetMotoFightPokemonPtr(poke);
    FightPokemon* target = fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
    if (source == nullptr) return false;
    if (target == nullptr) return false;
    copyFightPokemonRecord(target, source);
    fightOutPokemon_SetFightPokemonPtr(poke, target);
    return true;
}

u16 fightOutPokemonGetAllAbiCnt(FightOutPokemon* poke) {
    u16 properties[7] = { 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec };
    u8 i;
    u16 total = 0;
    for (i = 0; i < 7; i++) {
        total += pokemonGetStatus(reinterpret_cast<Pokemon*>(poke), 0, properties[i], 0);
    }
    return total;
}

void fightOutPokemonCopyAllAbiCnt(FightOutPokemon* target, FightOutPokemon* source) {
    u16 properties[7] = { 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec };
    for (u8 i = 0; i < 7; i++) {
        fightOutPokemonCopyStatus(target, source, properties[i]);
    }
}

void fightOutPokemonCopyStatus(FightOutPokemon* target, FightOutPokemon* source, u16 property) {
    u32 value = pokemonGetStatus(reinterpret_cast<Pokemon*>(source), 0, property, 0);
    pokemonSetStatus(reinterpret_cast<Pokemon*>(target), 0, property, 0, value);
}

void fightPokemonReplace(FightPokemon* first, FightPokemon* second) {
    if (first != nullptr && second != nullptr) {
        FightPokemon temporary;
        copyFightPokemonRecord(&temporary, first);
        copyFightPokemonRecord(first, second);
        copyFightPokemonRecord(second, &temporary);
    }
}
}

#include <game/pxdvs/app/fight/fightPokemonEffects.hpp>

extern "C" void fightOutPokemonDarkPokemonKaijoEffect(FightOutPokemon* poke,
    u8 reverse, u8 dark, u8 release, void* message, u8 phase) {
    void* sequence;
    WazaSequence* animation;
    u16 animationId;
    u8 fightType = fightFloor_GetFightType(nullptr);
    sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    if (phase == 0) {
        if (reverse == 1) Sequence_LoadWaza(sequence, 0xa3, 4, nullptr);
        if (dark == 1) Sequence_LoadWaza(sequence, 0x9f, 4, nullptr);
        if (release == 1) {
            Sequence_LoadWaza(sequence, 0x9f, 4, nullptr);
            Sequence_LoadWaza(sequence, 0x2c, 4, nullptr);
        }
        if (reverse == 0 && dark == 0 && release == 0)
            Sequence_LoadWaza(sequence, 0x57, 4, nullptr);
    } else if (phase == 1) {
        if (reverse == 1) {
            WazaSequence_Start(Sequence_GetWaza(sequence, 0xa3, 4), 1);
            GSsndPlayVolume(static_cast<u16>(fightOutPokemonGetVoiceSndId(poke)), 0, 255, 0);
            fightMenuOpenMsg(message);
            if (dark == 0) fightMenuFightOutPokemonRenewStatusMenu(poke, fightType, 1);
        }
        if (dark == 1) {
            if (reverse == 1) {
                animation = Sequence_GetWaza(sequence, 0xa3, 4);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
            }
            WazaSequence_Start(Sequence_GetWaza(sequence, 0x9f, 4), 1);
            if (reverse == 0) {
                GSsndPlayVolume(static_cast<u16>(fightOutPokemonGetVoiceSndId(poke)), 0, 255, 0);
                fightMenuOpenMsg(message);
            }
            fightMenuFightOutPokemonRenewStatusMenu(poke, fightType, 1);
        }
        if (release == 1) {
            WazaSequence_Start(Sequence_GetWaza(sequence, 0x2c, 4), 1);
            fightMenuOpenMsg(message);
            if (dark == 0) fightMenuFightOutPokemonRenewStatusMenu(poke, fightType, 1);
        }
        if (reverse == 0 && dark == 0 && release == 0) {
            WazaSequence_Start(Sequence_GetWaza(sequence, 0x57, 4), 1);
            fightMenuOpenMsg(message);
        }
    } else if (phase == 2) {
        if (reverse == 1) animationId = 0xa3;
        if (dark == 1) animationId = 0x9f;
        if (release == 1) animationId = 0x2c;
        if (reverse == 0 && dark == 0 && release == 0) animationId = 0x57;
        animation = Sequence_GetWaza(sequence, animationId, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        if (reverse == 1) WazaSequence_Free(Sequence_GetWaza(sequence, 0xa3, 4));
        if (dark == 1) WazaSequence_Free(Sequence_GetWaza(sequence, 0x9f, 4));
        if (release == 1) WazaSequence_Free(Sequence_GetWaza(sequence, 0x2c, 4));
        if (reverse == 0 && dark == 0 && release == 0)
            WazaSequence_Free(Sequence_GetWaza(sequence, 0x57, 4));
    }
}

extern "C" void fightOutPokemonDasuEffect(FightTrainer* trainer, FightOutPokemon* poke, u8 phase) {
    WazaSequence* animation;
    void* trainerSequence = fightTrainer_GetSequencePtr(trainer);
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    fightOutPokemonGetPokemonPtr(poke);
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    u8 ball = pokemon_GetCatchBallId(pokemon);
    u32 openId = itemBallDB_GetOpenWzxDataId(ball);
    u32 outId = itemBallDB_GetOutWzxDataId(ball);
    FightModelSequenceView* trainerModel = static_cast<FightModelSequenceView*>(fightTrainer_GetSequencePtr(trainer));
    void* pokemonModel = fightOutPokemon_GetSequencePtr(poke);
    if (phase == 0) {
        Sequence_LoadWaza(trainerSequence, openId, 4, nullptr);
        Sequence_LoadWaza(sequence, outId, 4, nullptr);
        if (static_cast<u8>(pokemonCheckRare(fightOutPokemonGetPokemonPtr(poke))) == 1)
            Sequence_LoadWaza(sequence, 0x67, 4, nullptr);
    } else if (phase == 1) {
        WazaSequence_Start(Sequence_GetWaza(trainerSequence, openId, 4), 1);
    } else if (phase == 2) {
        animation = Sequence_GetWaza(trainerSequence, openId, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        WazaSequence_Start(Sequence_GetWaza(sequence, outId, 4), 1);
        if (trainerModel != nullptr && trainerModel->trackPokemon != 0)
            trainerModel->trackedPokemonSequence = pokemonModel;
    } else if (phase == 4) {
        if (trainerSequence != nullptr) Sequence_SetLookTarget(trainerSequence, sequence);
        Sequence_GetWaza(sequence, outId, 4);
        for (;;) {
            if (wazaSequenceSysLastWazaIsImpactPoint(nullptr) == 1) break;
            GSthreadSwitch();
        }
        GSsndPlayVolume(static_cast<u16>(fightOutPokemonGetVoiceSndId(poke)), 0, 255, 0);
        if (fightFloor_GetEnvSndId(nullptr) != 0)
            GSsndPlayVolume(fightOutPokemon_GetKanseiSndId(poke), 0, 127, 0);
        animation = Sequence_GetWaza(sequence, outId, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
        if (trainerSequence != nullptr) Sequence_SetLookTarget(trainerSequence, nullptr);
        if (static_cast<u8>(pokemonCheckRare(pokemon)) == 1) {
            animation = Sequence_GetWaza(sequence, 0x67, 4);
            WazaSequence_Start(animation, 1);
            while (WazaSequence_IsActive(animation)) GSthreadSwitch();
        }
    } else if (phase == 5) {
        if (trainerModel != nullptr && trainerModel->trackPokemon != 0)
            trainerModel->trackedPokemonSequence = nullptr;
        WazaSequence_Free(Sequence_GetWaza(trainerSequence, openId, 4));
        WazaSequence_Free(Sequence_GetWaza(sequence, outId, 4));
        WazaSequence_Free(Sequence_GetWaza(sequence, 0x67, 4));
    }
}

extern "C" void fightOutPokemonHokakuEffect(FightOutPokemon* poke, u8 shakes,
    u32 ballId, u8 phase, u8* savedFlags) {
    WazaSequence* animation;
    WazaSequence* shakeAnimation;
    u8 shake;
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    u32 catchId = itemBallDB_GetSnatchSnatchWzxDataId(ballId);
    u32 landId = itemBallDB_GetSnatchBalllandWzxDataId(ballId);
    u32 shakeId = itemBallDB_GetSnatchShakeWzxDataId(ballId);
    u32 missId = itemBallDB_GetSnatchMissWzxDataId(ballId);
    u32 outId = itemBallDB_GetSnatchPokeoutWzxDataId(ballId);
    if (static_cast<u8>(fightFloor_GetTrainer(nullptr)) == 0) {
        catchId = itemBallDB_GetYaseiGetWzxDataId(ballId);
        outId = itemBallDB_GetYaseiPokeoutWzxDataId(ballId);
        landId = itemBallDB_GetYaseiBallLandWzxDataId(ballId);
        shakeId = itemBallDB_GetYaseiShakeWzxDataId(ballId);
        missId = 0;
    }
    if (static_cast<u8>(fightFloor_GetFightKind(nullptr)) == 0xd) shakeId = 0;
    if (static_cast<u8>(fightFloor_GetTrainer(nullptr)) == 0) {
        if (phase == 0) {
            if (outId != 0) Sequence_LoadWaza(sequence, outId, 4, nullptr);
            if (catchId != 0) Sequence_LoadWaza(sequence, catchId, 4, nullptr);
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, nullptr);
            if (shakeId != 0) Sequence_LoadWaza(sequence, shakeId, 4, nullptr);
            if (missId != 0) Sequence_LoadWaza(sequence, missId, 4, nullptr);
            if (savedFlags != nullptr) {
                *savedFlags = Sequence_GetFlags(sequence);
                Sequence_SetDefaultFlags(sequence);
            }
        } else if (phase == 1) {
            if (catchId != 0) {
                animation = Sequence_GetWaza(sequence, catchId, 4);
                WazaSequence_Start(animation, 1);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
            }
            if (shakeId != 0) {
                animation = Sequence_GetWaza(sequence, landId, 4);
                WazaSequence_Start(animation, 1);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                shake = 0;
                do {
                    shakeAnimation = Sequence_GetWaza(sequence, shakeId, 4);
                    WazaSequence_Start(shakeAnimation, 1);
                    while (WazaSequence_IsActive(shakeAnimation)) GSthreadSwitch();
                    shake++;
                } while (shake < 3 && shake < shakes);
                WazaSequence_Free(shakeAnimation);
            }
            if (shakes < 4 && missId != 0) {
                animation = Sequence_GetWaza(sequence, missId, 4);
                WazaSequence_Start(animation, 1);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
            }
        } else if (phase == 2) {
            if (shakes < 4 && outId != 0)
                WazaSequence_Start(Sequence_GetWaza(sequence, outId, 4), 1);
        } else if (phase == 3) {
            if (shakes < 4) {
                if (savedFlags != nullptr) Sequence_SetFlags(sequence, *savedFlags);
                if (outId != 0) {
                    animation = Sequence_GetWaza(sequence, outId, 4);
                    while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                }
            }
        } else if (phase == 4) {
            if (outId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, outId, 4));
            if (catchId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, catchId, 4));
            if (landId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, landId, 4));
            if (shakeId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, shakeId, 4));
            if (missId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, missId, 4));
            if (shakes >= 4) {
                fightOutPokemonFreeSequence(poke);
                u8 fightType = fightFloor_GetFightType(nullptr);
                fightMenuFightOutPokemonCloseStatusMenu(poke, fightType, 1);
            } else {
                if (savedFlags != nullptr) Sequence_SetFlags(sequence, *savedFlags);
            }
        }
    } else {
        if (phase == 0) {
            if (outId != 0) Sequence_LoadWaza(sequence, outId, 4, nullptr);
            if (catchId != 0) Sequence_LoadWaza(sequence, catchId, 4, nullptr);
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, nullptr);
            if (shakeId != 0) Sequence_LoadWaza(sequence, shakeId, 4, nullptr);
            if (missId != 0) Sequence_LoadWaza(sequence, missId, 4, nullptr);
            if (savedFlags != nullptr) {
                *savedFlags = Sequence_GetFlags(sequence);
                Sequence_SetDefaultFlags(sequence);
            }
        } else if (phase == 1) {
            if (catchId != 0) {
                Sequence_LoadWaza(sequence, catchId, 4, nullptr);
                animation = Sequence_GetWaza(sequence, catchId, 4);
                WazaSequence_Start(animation, 1);
                battleGridRestoreModelVisibilityFlags();
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                WazaSequence_Free(animation);
            }
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, nullptr);
            if (shakeId != 0) {
                Sequence_LoadWaza(sequence, shakeId, 4, nullptr);
                animation = Sequence_GetWaza(sequence, landId, 4);
                WazaSequence_Start(animation, 1);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                WazaSequence_Free(animation);
                WazaSequence* snatchShakeAnimation;
                u8 snatchShake = 0;
                do {
                    snatchShakeAnimation = Sequence_GetWaza(sequence, shakeId, 4);
                    WazaSequence_Start(snatchShakeAnimation, 1);
                    while (WazaSequence_IsActive(snatchShakeAnimation)) GSthreadSwitch();
                    snatchShake++;
                } while (snatchShake < 3 && snatchShake < shakes);
                WazaSequence_Free(snatchShakeAnimation);
            }
            if (shakes < 4 && missId != 0) {
                Sequence_LoadWaza(sequence, missId, 4, nullptr);
                animation = Sequence_GetWaza(sequence, missId, 4);
                WazaSequence_Start(animation, 1);
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                WazaSequence_Free(animation);
            }
        } else if (phase == 2) {
            if (shakes < 4 && outId != 0)
                WazaSequence_Start(Sequence_GetWaza(sequence, outId, 4), 1);
        } else if (phase == 3) {
            if (shakes < 4) {
                if (savedFlags != nullptr) Sequence_SetFlags(sequence, *savedFlags);
                if (outId != 0) {
                    animation = Sequence_GetWaza(sequence, outId, 4);
                    while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                }
            }
        } else if (phase == 4) {
            if (outId != 0) WazaSequence_Free(Sequence_GetWaza(sequence, outId, 4));
            if (shakes >= 4) {
                fightOutPokemonFreeSequence(poke);
                u8 fightType = fightFloor_GetFightType(nullptr);
                fightMenuFightOutPokemonCloseStatusMenu(poke, fightType, 1);
            } else {
                if (savedFlags != nullptr) Sequence_SetFlags(sequence, *savedFlags);
            }
        }
    }
}
