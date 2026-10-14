// This caller retains getter words until the original comparison narrows them.
#define FIGHT_POKEMON_COMMAND_ABI
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
u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
void fightOutPokemonSetTokuseiDataId(FightOutPokemon*, u32);
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
        if (reverse == 1) Sequence_LoadWaza(sequence, 0xa3, 4, 0);
        if (dark == 1) Sequence_LoadWaza(sequence, 0x9f, 4, 0);
        if (release == 1) {
            Sequence_LoadWaza(sequence, 0x9f, 4, 0);
            Sequence_LoadWaza(sequence, 0x2c, 4, 0);
        }
        if (reverse == 0 && dark == 0 && release == 0)
            Sequence_LoadWaza(sequence, 0x57, 4, 0);
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
        Sequence_LoadWaza(trainerSequence, openId, 4, 0);
        Sequence_LoadWaza(sequence, outId, 4, 0);
        if (static_cast<u8>(pokemonCheckRare(fightOutPokemonGetPokemonPtr(poke))) == 1)
            Sequence_LoadWaza(sequence, 0x67, 4, 0);
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
            if (outId != 0) Sequence_LoadWaza(sequence, outId, 4, 0);
            if (catchId != 0) Sequence_LoadWaza(sequence, catchId, 4, 0);
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, 0);
            if (shakeId != 0) Sequence_LoadWaza(sequence, shakeId, 4, 0);
            if (missId != 0) Sequence_LoadWaza(sequence, missId, 4, 0);
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
            if (outId != 0) Sequence_LoadWaza(sequence, outId, 4, 0);
            if (catchId != 0) Sequence_LoadWaza(sequence, catchId, 4, 0);
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, 0);
            if (shakeId != 0) Sequence_LoadWaza(sequence, shakeId, 4, 0);
            if (missId != 0) Sequence_LoadWaza(sequence, missId, 4, 0);
            if (savedFlags != nullptr) {
                *savedFlags = Sequence_GetFlags(sequence);
                Sequence_SetDefaultFlags(sequence);
            }
        } else if (phase == 1) {
            if (catchId != 0) {
                Sequence_LoadWaza(sequence, catchId, 4, 0);
                animation = Sequence_GetWaza(sequence, catchId, 4);
                WazaSequence_Start(animation, 1);
                battleGridRestoreModelVisibilityFlags();
                while (WazaSequence_IsActive(animation)) GSthreadSwitch();
                WazaSequence_Free(animation);
            }
            if (landId != 0) Sequence_LoadWaza(sequence, landId, 4, 0);
            if (shakeId != 0) {
                Sequence_LoadWaza(sequence, shakeId, 4, 0);
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
                Sequence_LoadWaza(sequence, missId, 4, 0);
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

extern "C" void fightOutPokemonKizetuEffect(FightOutPokemon* poke, u8 phase) {
    void* sequence;
    u32 downId;
    u8 wild = 0;
    u32 messageId;
    WazaSequence* animation;
    sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    downId = itemBallDB_GetDowninWzxDataId(static_cast<u8>(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(poke))));
    FightTrainer* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(nullptr, poke);
    ModelSequence* trainerModel = static_cast<ModelSequence*>(fightTrainer_GetSequencePtr(trainer));
    void* pokemonModel = fightOutPokemon_GetSequencePtr(poke);
    if (static_cast<u8>(fightTrainerIsGcHero(trainer)) == 0 &&
        (static_cast<u8>(fightFloor_GetTrainer(nullptr)) == 0 ||
         static_cast<u16>(fightFloor_GetEncountDataId(nullptr)) == 0x191)) {
        wild = 1;
        downId = 0xdb;
    }
    if (phase == 0) {
        Sequence_LoadWaza(sequence, downId, 4, 0);
    } else if (phase == 1) {
        animation = Sequence_GetWaza(sequence, downId, 4);
        wazaSequenceSysFreeAllWazaExcept(sequence, animation);
        WazaSequence_Start(animation, 1);
        if (trainerModel != nullptr) {
            if (trainerModel->trackPokemon != 0) trainerModel->trackedPokemonSequence = pokemonModel;
            trainerModel->DoModelAnimation(4);
        }
    } else if (phase == 2) {
        Sequence_GetWaza(sequence, downId, 4);
        if (wild == 1) {
            for (;;) {
                if (wazaSequenceSysLastWazaIsImpactPoint(reinterpret_cast<void*>(2)) == 1) break;
                GSthreadSwitch();
            }
            u8 fightType = fightFloor_GetFightType(nullptr);
            fightMenuFightOutPokemonCloseStatusMenu(poke, fightType, 1);
            fightPokemonSetNonTrainerPokemonIsActiveFlag(0);
            fadeSet(3, 0.5f);
            fadeCheck(1);
            animation = Sequence_GetWaza(sequence, downId, 4);
            while (WazaSequence_IsActive(animation)) {
                animation = Sequence_GetWaza(sequence, downId, 4);
                GSthreadSwitch();
            }
            if (static_cast<u16>(fightFloor_GetEncountDataId(nullptr)) == 0x191) {
                fightMainAllCamera(1, 0);
                fadeSet(2, 0.5f);
            } else {
                GSsndPlayVolume(0x4a6, 0, 127, 0);
                fightMainAllCamera(1, 0);
                fadeSet(2, 0.5f);
                if (static_cast<u8>(fightFloor_GetFightKind(nullptr)) == 0xc) messageId = 0x4ff7;
                if (static_cast<u8>(fightFloor_GetFightKind(nullptr)) == 0xd) messageId = 0x4ffe;
                fightMsgctrlSetValue(0x16, fightOutPokemonGetNamePtr(poke));
                fightMenuOpenMsg2(messageId, 1);
            }
        } else {
            animation = Sequence_GetWaza(sequence, downId, 4);
            while (WazaSequence_IsActive(animation)) {
                animation = Sequence_GetWaza(sequence, downId, 4);
                GSthreadSwitch();
            }
        }
        WazaSequence_Free(animation);
        if (wild == 0) {
            u8 fightType = fightFloor_GetFightType(nullptr);
            fightMenuFightOutPokemonCloseStatusMenu(poke, fightType, 1);
        }
        if (wild == 1) {
            wildPokemonDownFlag = 1;
            fightMenuCloseMsg();
        }
    } else if (phase == 3) {
        if (trainerModel != nullptr && trainerModel->trackPokemon != 0)
            trainerModel->trackedPokemonSequence = nullptr;
        fightOutPokemonFreeSequence(poke);
    }
}

extern "C" void fightOutPokemonDarkPokemonEffect(FightOutPokemon* poke, u8 openMenu, u8 kind, u8 phase) {
    WazaSequence* animation;
    u16 animationId;
    u8 fightType = fightFloor_GetFightType(nullptr);
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    if (kind == 0) animationId = 0x3a;
    else if (kind == 1) animationId = 0x88;
    else if (kind == 2) animationId = 0x57;
    else animationId = 0xd9;
    if (phase == 0) {
        Sequence_LoadWaza(sequence, animationId, 4, 0);
    } else if (phase == 1) {
        WazaSequence_Start(Sequence_GetWaza(sequence, animationId, 4), 1);
        if (openMenu == 1) {
            fightMenuFightOutPokemonOpenStatusMenu(poke, fightType, 1);
            fightMenuFightOutPokemonCloseStatusMenuAnotherMine(0, poke, fightType, 0, 1);
        }
    } else if (phase == 2) {
        animation = Sequence_GetWaza(sequence, animationId, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        WazaSequence_Free(Sequence_GetWaza(sequence, animationId, 4));
    } else if (phase == 4) {
        WazaSequence_Stop(Sequence_GetWaza(sequence, animationId, 4));
    }
}

extern "C" void fightOutPokemonModosuEffect(FightOutPokemon* poke, u8 phase) {
    WazaSequence* animation;
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return;
    u32 inId = itemBallDB_GetInWzxDataId(static_cast<u8>(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(poke))));
    if (phase == 0) {
        Sequence_LoadWaza(sequence, inId, 4, 0);
    } else if (phase == 1) {
        animation = Sequence_GetWaza(sequence, inId, 4);
        Sequence_SetDefaultFlags(sequence);
        WazaSequence_Start(animation, 1);
    } else if (phase == 2) {
        animation = Sequence_GetWaza(sequence, inId, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        WazaSequence_Free(Sequence_GetWaza(sequence, inId, 4));
    } else if (phase == 4) {
        fightOutPokemonFreeSequence(poke);
        u8 fightType = fightFloor_GetFightType(nullptr);
        fightMenuFightOutPokemonCloseStatusMenu(poke, fightType, 1);
    }
}

extern "C" void fightOutPokemonDamageEffect(FightOutPokemon* poke) {
    void* model = fightOutPokemonGetGsmodelPtr(poke);
    if (model == nullptr) return;
    if (static_cast<u8>(GSmodelGetVisibility(model)) == 0) return;
    for (u8 i = 0; i < 8; i++) {
        fightOutPokemonSetVisibility(poke, 1);
        GSmodelSetVisibility(model, 1);
        fightMainWaitFrame(3);
        fightOutPokemonSetVisibility(poke, 0);
        fightMainWaitFrame(2);
    }
    fightOutPokemonSetVisibility(poke, 1);
}

#include <game/pxdvs/app/fight/fightPokemonActions.hpp>

extern "C" u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon* poke, u16 index, u8 clearKeep, u16* choiceMove) {
    u8 result = 0;
    u16 power;
    u32 move;
    Pokemon* pokemon;
    u32 pp;
    u32 item;
    u32 lastMove;
    if (poke == nullptr) return 6;
    pokemon = fightOutPokemonGetPokemonPtr(poke);
    move = pokemon_GetPokemonWazaDataId(pokemon, index);
    power = wazaDB_GetIryoku(move);
    pp = pokemon_GetPokemonWazaPp(pokemon, index);
    item = fightOutPokemonGetSoubiItemSoubiDataId(poke);
    lastMove = fightOutPokemon_GetLastSelectWazaDataId(poke);
    if (fightOutPokemonIsJoutaiDataId(poke, 0x29) == 1) {
        u16 disabled = fightOutPokemonGetIdBuffJoutaiDataId(poke, 0x29);
        if (disabled != 0 && disabled == static_cast<u16>(move) && disabled != 0x176) result = 1;
    }
    if (fightOutPokemonIsJoutaiDataId(poke, 0x1b) == 1 &&
        static_cast<u16>(move) == static_cast<u16>(lastMove) && static_cast<u16>(move) != 0xa5) {
        if (clearKeep == 1) fightOutPokemonInitJoutaiKeep(poke);
        result = 2;
    }
    if (fightOutPokemonIsJoutaiDataId(poke, 0x30) == 1 && power == 0) result = 3;
    if (fightFloorCheckHuuinWazaFightOutPokemon(nullptr, poke, move) == 1) result = 4;
    if (static_cast<u16>(item) == 0x1d) {
        u32 lockedMove;
        if (fightOutPokemonIsJoutaiDataId(poke, 0x36) == 1)
            lockedMove = fightOutPokemonGetIdBuffJoutaiDataId(poke, 0x36);
        else lockedMove = 0;
        u16 locked = lockedMove;
        if (locked != 0 && locked != 0x176 && locked != 0xffff && locked != static_cast<u16>(move)) result = 5;
        if (choiceMove != nullptr) *choiceMove = lockedMove;
    }
    if (pokemonWazaCheckValid(pokemon, index) == 0 || static_cast<u8>(pp) == 0) result = 6;
    return result;
}

extern "C" u8 fightOutPokemonGetOutOkWazaBanmeAry(FightOutPokemon* poke, s16* indices) {
    if (poke == nullptr) return 0;
    for (u8 i = 0; i < 4; i++) {
        if (indices != nullptr) indices[i] = -1;
    }
    u8 i;
    u8 count = 0;
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(fightOutPokemonGetPokemonPtr(poke), i)) {
            u16 move = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(poke), i);
            if (move != 0 && move != 0x176 && move != 0x163 &&
                fightOutPokemonCheckCanOutOkWazaBanme(poke, i, 0, nullptr) == 0) {
                if (indices != nullptr) indices[count] = i;
                count++;
            }
        }
    }
    return count;
}

extern "C" u8 fightOutPokemonCheckWaruagaki(FightOutPokemon* poke) {
    if (fightOutPokemonGetOutOkWazaBanmeAry(poke, nullptr) == 0) return 1;
    if (fightOutPokemonIsJoutaiDataId(poke, 0x2a) == 1) {
        u32 index = fightOutPokemonGetBuffJoutaiDataId(poke, 0x2a);
        if (fightOutPokemonCheckCanOutOkWazaBanme(poke, static_cast<u16>(index), 0, nullptr) != 0) return 1;
    }
    return 0;
}

extern "C" u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon* poke, u8 createAction) {
    u8 fightType = fightFloor_GetFightType(nullptr);
    if (poke == nullptr) return 0;
    if (fightOutPokemonCheckFightOut(poke) == 0) return 0;
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (fightOutPokemonCheckWaruagaki(poke) == 1) {
        if (createAction != 0) {
            FightTarget* target = fightSeqSelectDefensePokemonPtr(poke, 0xa5, fightType, nullptr, 1, 1, -1);
            u32 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, fightType);
            fightOutPokemonCreateFightActionAttackWaza(poke, 0, 0x13, 0, &fight_action_data_waza, 0xa5, targetId, -1, 1);
        }
        return 1;
    }
    if (fightOutPokemonIsJoutaiDataId(poke, 0x2a) == 1) {
        u32 encoreMove = fightOutPokemonGetIdBuffJoutaiDataId(poke, 0x2a);
        u32 index = fightOutPokemonGetBuffJoutaiDataId(poke, 0x2a);
        u32 move = pokemon_GetPokemonWazaDataId(pokemon, static_cast<u16>(index));
        wazaDB_GetPri(move);
        if (createAction != 0) {
            if (static_cast<u16>(encoreMove) != static_cast<u16>(move)) fightOutPokemonInitJoutaiDataId(poke, 0x2a);
            FightTarget* target = fightSeqSelectDefensePokemonPtr(poke, move, fightType, nullptr, 1, 1, -1);
            u32 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, fightType);
            fightOutPokemonCreateFightActionAttackWaza(poke, 0, 0x13, 0, &fight_action_data_waza, move, targetId, static_cast<s8>(index), 1);
        }
        return 2;
    }
    return 0;
}

static FightTarget* _fightOutPokemonCheckFightActionSelectSub(FightOutPokemon* poke, u16 move, u16 fightType) {
    return fightTargetGetRelativeHostSideFightTargetIdToTragetPtr(
        fightWaza_GetTargetDataId(fightOutPokemon_GetKeepFightWazaPtr(poke)), fightType);
}

extern "C" u8 fightOutPokemonCheckFightActionSelect(FightOutPokemon* poke, u8 createAction) {
    u8 fightType = fightFloor_GetFightType(nullptr);
    if (poke == nullptr) return 0;
    if (fightOutPokemonCheckFightOut(poke) == 0) return 0;
    if (fightOutPokemonIsJoutaiDataId(poke, 0x12) == 1 || fightOutPokemonIsJoutaiDataId(poke, 0x22) == 1) {
        if (createAction != 0) {
            FightWaza* keep = fightOutPokemon_GetKeepFightWazaPtr(poke);
            if (fightWazaCheckValid(keep)) {
                u32 move = fightWaza_GetUseWazaDataId(keep);
                s32 index = fightWaza_GetWazaBanme(keep);
                FightTarget* target = fightSeqSelectDefensePokemonPtr(poke, move, fightType, _fightOutPokemonCheckFightActionSelectSub, 1, 0, -1);
                u32 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, fightType);
                fightOutPokemonCreateFightActionAttackWaza(poke, 0, 0x13, 0, &fight_action_data_waza, move, targetId, index, 1);
            }
        }
        return 0;
    }
    return 1;
}

extern "C" u32 fightOutPokemonGetNowNimbleness(FightOutPokemon* poke, u8 useBadge, u8 weather, u16 random, Hero* hero) {
    s32 itemBuff;
    u32 item;
    u8 badge;
    u32 stage;
    u32 ability;
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    ability = fightOutPokemonGetTokuseiDataId(poke);
    item = fightOutPokemonGetSoubiItemSoubiDataId(poke);
    itemBuff = figthOutPokemonGetSoubiItemBuff(poke);
    stage = fightOutPokemon_GetAbicntNimbleness(poke);
    if (hero != nullptr) badge = static_cast<u8>(heroGetStatus(hero, 0x11, 0) != 0);
    else badge = 0;
    u32 speed = pokemon_GetNimbleness(pokemon);
    speed = static_cast<u16>(speed);
    if (static_cast<u16>(ability) == 0x21 && weather == 2) speed *= 2;
    else if (static_cast<u16>(ability) == 0x22 && weather == 1) speed *= 2;
    speed = fightAbicntDoKakeWaru(stage, speed);
    if (useBadge == 1 && badge == 1) speed = speed * 110 / 100;
    if (static_cast<u16>(item) == 0x18) speed /= 2;
    if (fightOutPokemonIsJoutaiDataId(poke, 5) == 1) speed /= 4;
    if (static_cast<u16>(item) == 0x1a && random < itemBuff * 65535 / 100) speed = 0xffffffff;
    return speed;
}

extern "C" void fightOutPokemonInitOneTurn(FightOutPokemon* poke) {
    fightOutPokemon_SetDamageAtkValue(poke, 0);
    fightOutPokemon_SetDamageAtkTargetId(poke, 0);
    fightOutPokemon_SetDamageSpeValue(poke, 0);
    fightOutPokemon_SetDamageSpeTargetId(poke, 0);
    fightOutPokemon_SetMahiNoAttackFlag(poke, 0);
    fightOutPokemon_SetKonranMyselfAttackFlag(poke, 0);
    fightOutPokemon_SetOutWazaKoukanaiFlag(poke, 0);
    fightOutPokemon_SetTameWazaFlag(poke, 0);
    fightOutPokemon_SetItemNigeruFlag(poke, 0);
    fightOutPokemon_SetHuuinNoAttackFlag(poke, 0);
    fightOutPokemon_SetMeroMeroNoAttackFlag(poke, 0);
    fightOutPokemon_SetKanashibariNoAttackFlag(poke, 0);
    fightOutPokemon_SetChouhatsuNoAttackFlag(poke, 0);
    fightOutPokemon_SetIchamonNoAttackFlag(poke, 0);
    fightOutPokemon_SetHirumuNoAttackFlag(poke, 0);
    fightOutPokemon_SetPassPpdecFlag(poke, 0);
    fightOutPokemon_SetFightActionFlag(poke, 0);
}

extern "C" void fightOutPokemonInitOneSelfTurn(FightOutPokemon* poke) {
    fightOutPokemon_SetDoClearbodyFlag(poke, 0);
    fightOutPokemon_SetReceivesWazaHiraishinFlag(poke, 0);
    fightOutPokemon_SetVanishoffFlag(poke, 0);
    fightOutPokemon_SetDoIkakuFlag(poke, 0);
    fightOutPokemon_SetDoTraceFlag(poke, 0);
    fightOutPokemon_SetNoPressureFlag(poke, 0);
    fightOutPokemon_SetIrekaetaFlag(poke, 0);
    fightOutPokemon_SetItemKoraetaFlag(poke, 0);
    fightOutPokemon_SetKaigaraDamageValue(poke, 0);
    fightOutPokemon_SetMyselfDamageAtkValue(poke, 0);
    fightOutPokemon_SetMyselfDamageAtkTargetId(poke, 0);
    fightOutPokemon_SetMyselfDamageSpeValue(poke, 0);
    fightOutPokemon_SetMyselfDamageSpeTargetId(poke, 0);
}

extern "C" void fightPokemonInit(FightPokemon* poke) {
    if (poke == nullptr) return;
    fightPokemon_SetMotoPokemonPtr(poke, nullptr);
    pokemonInit(reinterpret_cast<u32>(fightPokemon_GetPokemonBuffPtr(poke)));
    joutaiInitAry(fightPokemon_GetFightJoutaiPtr(poke, 0), 1);
    fightPokemon_SetEntryId(poke, -1);
    fightPokemon_SetCatchEntryFlag(poke, 0);
    fightPokemon_SetLevelUpFlag(poke, 0);
    fightPokemon_SetDarkOutFlag(poke, 0);
    fightPokemon_SetHokakuFlag(poke, 0);
    for (u8 i = 0; i < 64; i++) {
        fightPokemon_SetAiDamage(poke, i, 0, 0);
        fightPokemon_SetAiDamage(poke, i, 1, 0);
    }
}

extern "C" void fightOutPokemonInitAbiCntAll(FightOutPokemon* poke) {
    u16 properties[7] = {0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec};
    for (u8 i = 0; i < 7; i++)
        pokemonSetStatus(reinterpret_cast<Pokemon*>(poke), 0, properties[i], 0, 6);
}

extern "C" void fightOutPokemonInitFightActionBuff(FightOutPokemon* poke) {
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action != nullptr) {
        fightActionInit(action);
        fightWazaInit(fightOutPokemon_GetFightWazaPtr(poke));
        fightItemInit(fightOutPokemon_GetFightItemPtr(poke));
    }
}

extern "C" void fightOutPokemonInitFightOutPokemonEnemyAry(FightOutPokemon* poke) {
    fightOutPokemonEnemyInitAry(fightOutPokemon_GetFightOutPokemonEnemyPtr(poke, 0), 4);
}

extern "C" void fightOutPokemonInit(FightOutPokemon* poke) {
    if (poke == nullptr) return;
    fightOutPokemon_SetMotoFightPokemonPtr(poke, nullptr);
    fightOutPokemon_SetFightPokemonPtr(poke, nullptr);
    fightPokemonInit(fightOutPokemon_GetFightPokemonHensinBuffPtr(poke));
    joutaiInitAry(fightOutPokemon_GetFightoutJoutaiPtr(poke, 0), 52);
    fightOutPokemonInitAbiCntAll(poke);
    fightOutPokemonBiosSetHensinMotoPkxId(poke, 0);
    fightOutPokemon_SetFightoutTurnCount(poke, 2);
    fightOutPokemon_SetSequencePtr(poke, nullptr);
    u8 i;
    for (i = 0; i < 12; i++) fightOutPokemon_SetMeetEnemyFightPokemonEntryId(poke, i, -1);
    fightOutPokemonInitFightActionBuff(poke);
    fightWazaInit(fightOutPokemon_GetKeepFightWazaPtr(poke));
    for (i = 0; i < 2; i++) fightOutPokemonSetZokuseiDataId(poke, i, 9);
    fightOutPokemonSetTokuseiDataId(poke, 0);
    u32* cursor = fightOutPokemon_GetWazaMenuCurPtr(poke);
    if (cursor != nullptr) *cursor = 0;
    fightOutPokemon_SetSketchWazaDataId(poke, 0);
    fightOutPokemon_SetLastSelectWazaDataId(poke, 0);
    fightOutPokemon_SetLastUseWazaDataId(poke, 0);
    fightOutPokemon_SetLastReceiveWazaTargetDataId(poke, 0);
    fightOutPokemon_SetHitWazaDataId(poke, 0);
    fightOutPokemon_SetHitWazaZokuseiDataId(poke, 9);
    fightOutPokemon_SetGamanDamageValue(poke, 0);
    fightOutPokemon_SetGamanDamageTargetId(poke, 0);
    fightOutPokemon_SetOumuWazaDataId(poke, 0);
    fightOutPokemon_SetOumuWazaAllyDataId(poke, 0);
    fightOutPokemon_SetComboFuncId(poke, 0);
    fightOutPokemon_SetFixAiWaza(poke, 0);
    fightOutPokemon_SetFixAiDef(poke, 0);
    poke->setComboFuncId(0);
    fightOutPokemon_SetNamakeFlag(poke, 0);
    fightOutPokemon_SetSuccessCnt(poke, 0);
    fightOutPokemon_SetStockItemDataId(poke, 0);
    fightOutPokemonInitOneTurn(poke);
    fightOutPokemonInitOneSelfTurn(poke);
    fightOutPokemon_SetKizetuFlag(poke, 0);
    fn_8014718C(poke, 0);
    fightOutPokemon_SetIrekaeTargetEntryId(poke, -1);
    fightOutPokemonInitFightOutPokemonEnemyAry(poke);
}

#include <game/pxdvs/app/fight/fightPokemonConditions.hpp>

// Persistent conditions use the Pokemon or FightPokemon record; volatile
// conditions use FightOutPokemon. Keep the original repeated status queries.
extern "C" {
void fightOutPokemonSetBuffJoutaiDataId(FightOutPokemon* poke, u16 condition, u32 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonSetBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiSetBuff(poke, condition, value);
    }
}

void fightPokemonSetBuffJoutaiDataId(FightPokemon* poke, u16 condition, u32 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c) {
    } else if (joutaiDataBiosGetStatus(condition) == 0xc8) {
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiSetBuff(poke, condition, value);
    }
}

u32 fightOutPokemonGetBuffJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0;
    return joutaiGetBuff(poke, condition);
}

u32 fightPokemonGetBuffJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        // These permanent conditions have no auxiliary battle-condition payload.
    }
    if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0;
    return joutaiGetBuff(poke, condition);
}

void fightOutPokemonSetIdBuffJoutaiDataId(FightOutPokemon* poke, u16 condition, u16 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonSetIdBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiSetIdBuff(poke, condition, value);
    }
}

void fightPokemonSetIdBuffJoutaiDataId(FightPokemon* poke, u16 condition, u16 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c) {
    } else if (joutaiDataBiosGetStatus(condition) == 0xc8) {
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiSetIdBuff(poke, condition, value);
    }
}

u32 fightOutPokemonGetIdBuffJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetIdBuffJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0;
    return joutaiGetIdBuff(poke, condition);
}

u32 fightPokemonGetIdBuffJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        // These permanent conditions have no auxiliary battle-condition payload.
    }
    if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0;
    return joutaiGetIdBuff(poke, condition);
}

u32 fightOutPokemonGetUserFightTargetIdJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetUserFightTargetIdJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0;
    return joutaiGetUserFightTargetId(poke, condition);
}

u32 fightPokemonGetUserFightTargetIdJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        // These permanent conditions have no auxiliary battle-condition payload.
    }
    if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0;
    return joutaiGetUserFightTargetId(poke, condition);
}

void fightOutPokemonSetKaisuuJoutaiDataId(FightOutPokemon* poke, u16 condition, u8 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonSetKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiSetKaisuuJoutaiDataId(poke, condition, value);
    }
}

void fightPokemonSetKaisuuJoutaiDataId(FightPokemon* poke, u16 condition, u8 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        pokemonSetKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiSetKaisuuJoutaiDataId(poke, condition, value);
    }
}

void fightOutPokemonSetNowKaisuuJoutaiDataId(FightOutPokemon* poke, u16 condition, u8 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonSetNowKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiSetNowKaisuuJoutaiDataId(poke, condition, value);
    }
}

void fightPokemonSetNowKaisuuJoutaiDataId(FightPokemon* poke, u16 condition, u8 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        pokemonSetNowKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiSetNowKaisuuJoutaiDataId(poke, condition, value);
    }
}

u32 fightOutPokemonGetNowKaisuuJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetNowKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0xffffffff;
    return joutaiGetNowKaisuuJoutaiDataId(poke, condition);
}

u32 fightPokemonGetNowKaisuuJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        return pokemonGetNowKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0xffffffff;
    return joutaiGetNowKaisuuJoutaiDataId(poke, condition);
}

u32 fightOutPokemonGetKaisuuJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetKaisuuJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0xffffffff;
    return joutaiGetKaisuuJoutaiDataId(poke, condition);
}

u32 fightPokemonGetKaisuuJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        return pokemonGetKaisuuJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0xffffffff;
    return joutaiGetKaisuuJoutaiDataId(poke, condition);
}

u32 fightOutPokemonGetCountAsJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonGetCountAsJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0xffffffff;
    return joutaiGetCountAsJoutaiDataId(poke, condition);
}

u32 fightPokemonGetCountAsJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        return pokemonGetCountAsJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0xffffffff;
    return joutaiGetCountAsJoutaiDataId(poke, condition);
}

void fightOutPokemonWriteJoutaiDataId(FightOutPokemon* poke, u16 condition, u16 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonWriteJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiWriteJoutaiDataId(poke, condition, value);
    }
}

void fightPokemonWriteJoutaiDataId(FightPokemon* poke, u16 condition, u16 value) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        pokemonWriteJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition, value);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiWriteJoutaiDataId(poke, condition, value);
    }
}

u8 fightOutPokemonCheckWriteJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonCheckWriteJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0;
    return joutaiCheckWriteJoutaiDataId(poke, condition);
}

u8 fightPokemonCheckWriteJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        return pokemonCheckWriteJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0;
    return joutaiCheckWriteJoutaiDataId(poke, condition);
}

u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    if (poke == nullptr) return 0;
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        return fightPokemonIsJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xd8) return 0;
    return joutaiIsJoutaiDataId(poke, condition);
}

u8 fightPokemonIsJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (poke == nullptr) return 0;
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        return pokemonIsJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) != 0xcd) return 0;
    return joutaiIsJoutaiDataId(poke, condition);
}

void fightOutPokemonInitJoutaiDataId(FightOutPokemon* poke, u16 condition) {
    fightOutPokemonResetSeqStatus(poke, condition);
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        fightPokemonInitJoutaiDataId(fightOutPokemon_GetFightPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiInitJoutaiDataId(poke, condition);
    }
}

void fightPokemonInitJoutaiDataId(FightPokemon* poke, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        pokemonInitJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiInitJoutaiDataId(poke, condition);
    }
}

void fightOutPokemonCopyJoutaiDataId(FightOutPokemon* target, FightOutPokemon* source, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8 ||
        joutaiDataBiosGetStatus(condition) == 0xcd) {
        FightPokemon* sourceRecord = fightOutPokemon_GetFightPokemonPtr(source);
        FightPokemon* targetRecord = fightOutPokemon_GetFightPokemonPtr(target);
        fightPokemonCopyJoutaiDataId(targetRecord, sourceRecord, condition);
    } else if (joutaiDataBiosGetStatus(condition) == 0xd8) {
        joutaiCopy(target, source, condition);
    }
}

void fightPokemonCopyJoutaiDataId(FightPokemon* target, FightPokemon* source, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        Pokemon* sourceRecord = fightPokemonGetPokemonPtr(source);
        Pokemon* targetRecord = fightPokemonGetPokemonPtr(target);
        pokemonCopyJoutaiDataId(targetRecord, sourceRecord, condition);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiCopy(target, source, condition);
    }
}

void fightOutPokemonResetSeqStatus(FightOutPokemon* poke, u16 condition) {
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (condition == 0) {
        if (sequence != nullptr) {
            Sequence_ResetStatus(sequence, 1);
            Sequence_ResetStatus(sequence, 2);
        }
    } else if (sequence != nullptr) {
        if (condition == 8) Sequence_ResetStatus(sequence, 1);
        if (condition == 7) Sequence_ResetStatus(sequence, 2);
    }
}
}

extern "C" {
u16 fightGetFightResultId();
u8 pokemonCheckValid(Pokemon*);
u8 pokemonCheckFightOut(Pokemon*);
bool fightPokemonCheckValid(FightPokemon*);
bool fightOutPokemonCheckValid(FightOutPokemon*);
bool fightPokemonCheckFightOut(FightPokemon*);
u32 pokemon_GetCatchTrainerRnd(Pokemon*);
u32 pokemon_GetRnd(Pokemon*);

Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return fightPokemonGetPokemonPtr(fightOutPokemon_GetFightPokemonPtr(poke));
}

Pokemon* fightPokemonGetPokemonPtr(FightPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return fightPokemon_GetPokemonBuffPtr(poke);
}

s32 fightOutPokemonGetFightEntryId(FightOutPokemon* poke) {
    if (poke == nullptr) return -1;
    FightPokemon* original = fightOutPokemon_GetMotoFightPokemonPtr(poke);
    if (original == nullptr) return -1;
    return fightPokemon_GetEntryId(original);
}

bool fightPokemonCheckValid(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    if (fightGetFightResultId() == 1) return 0;
    Pokemon* original = fightPokemon_GetMotoPokemonPtr(poke);
    if (original == nullptr) return 0;
    if (pokemonCheckValid(original) == 0) return 0;
    Pokemon* current = fightPokemonGetPokemonPtr(poke);
    if (current == nullptr) return 0;
    if (pokemonCheckValid(current) == 0) return 0;
    return static_cast<s16>(fightPokemon_GetEntryId(poke)) >= 0;
}

bool fightOutPokemonCheckValid(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    if (fightGetFightResultId() == 1) return 0;
    FightPokemon* current = fightOutPokemon_GetFightPokemonPtr(poke);
    if (current == nullptr) return 0;
    return fightPokemonCheckValid(current) != 0;
}

bool fightPokemonCheckFightOut(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    if (fightPokemonCheckValid(poke) == 0) return 0;
    if (fightPokemon_GetHokakuFlag(poke) == 1) return 0;
    Pokemon* current = fightPokemonGetPokemonPtr(poke);
    if (current == nullptr) return 0;
    return pokemonCheckFightOut(current) != 0;
}

bool fightOutPokemonCheckFightOut(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    if (fightOutPokemonCheckValid(poke) == 0) return 0;
    if (fightOutPokemon_GetKizetuFlag(poke) == 1) return 0;
    return fightPokemonCheckFightOut(fightOutPokemon_GetFightPokemonPtr(poke)) != 0;
}

void fightOutPokemonInitAry(FightOutPokemon* pokes, u16 count) {
    if (pokes != nullptr) {
        for (u16 i = 0; i < count; i++) fightOutPokemonInit(&pokes[i]);
    }
}

void fightPokemonInitAry(FightPokemon* pokes, u16 count) {
    if (pokes != nullptr) {
        for (u16 i = 0; i < count; i++) fightPokemonInit(&pokes[i]);
    }
}

void fightOutPokemonSetZokuseiDataId(FightOutPokemon* poke, u8 index, u16 type) {
    fightOutPokemon_SetZokuseiDataId(poke, index, type);
}

u16 fightOutPokemonGetZokuseiDataId(FightOutPokemon* poke, u8 index) {
    return fightOutPokemon_GetZokuseiDataId(poke, index);
}

void fightOutPokemonSetTokuseiDataId(FightOutPokemon* poke, u32 ability) {
    fightOutPokemon_SetTokuseiDataId(poke, ability);
}

u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon* poke) {
    return fightOutPokemon_GetTokuseiDataId(poke);
}

u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon* poke, u16 type) {
    if (type == fightOutPokemonGetZokuseiDataId(poke, 0) ||
        type == fightOutPokemonGetZokuseiDataId(poke, 1)) return 1;
    return 0;
}

void fightOutPokemonGetRndStatus(FightOutPokemon* poke, u32* personality, u32* trainerRnd) {
    u32 rnd;
    u32 trainer;
    if (fightOutPokemonIsJoutaiDataId(poke, 0x10) == 1) {
        rnd = fightOutPokemonGetBuffJoutaiDataId(poke, 0x10);
        u8 low = fightOutPokemonGetKaisuuJoutaiDataId(poke, 0x10);
        u8 high = fightOutPokemonGetNowKaisuuJoutaiDataId(poke, 0x10);
        u16 id = fightOutPokemonGetIdBuffJoutaiDataId(poke, 0x10);
        trainer = (high << 8) | low;
        trainer |= id << 16;
    } else {
        Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
        trainer = pokemon_GetCatchTrainerRnd(pokemon);
        rnd = pokemon_GetRnd(pokemon);
    }
    if (personality != nullptr) *personality = rnd;
    if (trainerRnd != nullptr) *trainerRnd = trainer;
}
}

// Battle-facing accessors retain the original getter word until its use site.
extern "C" {
u32 pokemonGetSex(Pokemon*);
u32 pokemonIsHpMantan(Pokemon*);
u32 pokemon_GetExp(Pokemon*);
u32 pokemon_GetLevel(Pokemon*);
u32 pokemon_GetPokemonDataId(Pokemon*);
u32 pokemon_GetHinsi(Pokemon*);
u16* pokemon_GetNicknamePtr(Pokemon*);
u32 pokemonGetNowHpPercentage(Pokemon*);
u32 pokemonIsJoutaiKaragenki(Pokemon*);
u32 pokemonIsJoutaiNormal(Pokemon*);
s32 pokemonGetTasteLike(Pokemon*, u8);
u32 pokemonDoItemSoubi(Pokemon*, u16, u8);
u32 pokemonGetSoubiItemBuff(Pokemon*);
u32 pokemonGetSoubiItemSoubiDataId(Pokemon*);
u32 pokemonGetSoubiItemDataId(Pokemon*);
u32 pokemonGetNowHpWaruValue(Pokemon*, u16, u16);
u32 pokemonGetMaxHpWaruValue(Pokemon*, u16);
u32 pokemonIsNokoriHpFollowing(Pokemon*, u16);
u32 pokemonGetLevelToExp(Pokemon*, u8);
void pokemon_SetExp(Pokemon*, u32);

void pokemonBiosCopy(Pokemon*, const Pokemon*);
FightOutPokemonEnemy* fightOutPokemonEnemySearchAry(FightOutPokemonEnemy*, u16, FightOutPokemon*);
u32 fightOutPokemonEnemyBiosGetDamage(FightOutPokemonEnemy*);
void fightOutPokemonEnemyBiosSetDamage(FightOutPokemonEnemy*, u32);
u8 fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy*);
u32 fightOutPokemonEnemyBiosGetOumuWazaDataId(FightOutPokemonEnemy*);
void fightOutPokemonEnemyBiosSetOumuWazaDataId(FightOutPokemonEnemy*, u16);
FightTarget* fightTargetGetPtr(u8, void*, u8);
u8 nonTrainerPokemonisActive;

void fightPokemonSetNonTrainerPokemonIsActiveFlag(u8 active) {
    nonTrainerPokemonisActive = active;
}

u8 fightPokemonGetNonTrainerPokemonIsActiveFlag() {
    return nonTrainerPokemonisActive;
}

u8 fightOutPokemonIsUseHensinBuff(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightPokemon* current = fightOutPokemon_GetFightPokemonPtr(poke);
    return current == fightOutPokemon_GetFightPokemonHensinBuffPtr(poke);
}

void fightOutPokemonSetJoutaiMigawariHp(FightOutPokemon* poke, u32 hp) {
    if (poke != nullptr && fightOutPokemonIsJoutaiDataId(poke, 0x14) == 1)
        fightOutPokemonSetBuffJoutaiDataId(poke, 0x14, hp);
}

u32 fightOutPokemonGetJoutaiMigawariHp(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    if (fightOutPokemonIsJoutaiDataId(poke, 0x14) == 1)
        return fightOutPokemonGetBuffJoutaiDataId(poke, 0x14);
    return 0;
}

u8 fightOutPokemonCheckNoAttackFlag(FightOutPokemon* poke) {
    u16 properties[9] = { 0x106, 0x108, 0x10b, 0x10c, 0x10d, 0x10e, 0x10f, 0x110, 0x107 };
    if (poke == nullptr) return 0;
    for (u8 i = 0; i < 9; i++) {
        if (static_cast<s32>(pokemonGetStatus(reinterpret_cast<Pokemon*>(poke), 0, properties[i], 0)) == 1) return 1;
    }
    return 0;
}

void fightOutPokemonInitJoutaiKie(FightOutPokemon* poke) {
    u16 conditions[3] = { 0x1f, 0x20, 0x21 };
    if (poke != nullptr) {
        u16 condition;
        for (u8 i = 0; i < 3; i++) {
            condition = conditions[i];
            if (fightOutPokemonIsJoutaiDataId(poke, condition) == 1)
                fightOutPokemonInitJoutaiDataId(poke, condition);
        }
    }
}

u16 fightOutPokemonIsJoutaiKie(FightOutPokemon* poke) {
    u16 conditions[3] = { 0x1f, 0x20, 0x21 };
    if (poke == nullptr) return 0;
    u16 condition;
    for (u8 i = 0; i < 3; i++) {
        condition = conditions[i];
        if (fightOutPokemonIsJoutaiDataId(poke, condition) == 1) return condition;
    }
    return 0;
}

void fightOutPokemonAddFightOutPokemonEnemyDamage(FightOutPokemon* attacker,
    FightOutPokemon* defender, u32 damage) {
    if (attacker != nullptr && defender != nullptr && attacker != defender) {
        FightOutPokemonEnemy* enemy = fightOutPokemonEnemySearchAry(
            fightOutPokemon_GetFightOutPokemonEnemyPtr(defender, 0), 4, attacker);
        if (enemy != nullptr)
            {
            u32 previous = fightOutPokemonEnemyBiosGetDamage(enemy);
            fightOutPokemonEnemyBiosSetDamage(enemy, previous + damage);
        }
    }
}

u8 fightOutPokemonIsAlly(FightOutPokemon* first, FightOutPokemon* second) {
    u8 type = fightFloor_GetFightType(nullptr);
    if (first == nullptr) return 0;
    if (second == nullptr) return 0;
    FightTarget* firstSide = fightTargetGetPtr(2, first, type);
    return firstSide == fightTargetGetPtr(2, second, type);
}

void fightOutPokemonSetOumuWazaDataId(FightOutPokemon* poke, FightOutPokemon* attacker, u16 move) {
    fightFloor_GetFightType(nullptr);
    if (poke == nullptr) return;
    if (fightOutPokemonIsAlly(poke, attacker) != 0 && attacker != poke) {
        fightOutPokemon_SetOumuWazaAllyDataId(poke, move);
        fightOutPokemon_SetOumuWazaDataId(poke, move);
    } else {
        fightOutPokemon_SetOumuWazaDataId(poke, move);
    }
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(poke, 0);
    if (attacker != nullptr) {
        FightOutPokemonEnemy* enemy = fightOutPokemonEnemySearchAry(enemies, 4, attacker);
        if (enemy != nullptr) fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy, move);
    } else {
        FightOutPokemonEnemy* enemy;
        for (u32 i = 0; i < 4; i++) {
            enemy = &enemies[i];
            if (fightOutPokemonEnemyCheckValid(enemy) != 0)
                fightOutPokemonEnemyBiosSetOumuWazaDataId(enemy, move);
        }
    }
}

s32 fightPokemonGetTasteLike(FightPokemon* poke, u8 taste) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return -1;
    return pokemonGetTasteLike(pokemon, taste);
}

s32 fightOutPokemonGetTasteLike(FightOutPokemon* poke, u8 taste) {
    FightPokemon* pokemon = fightOutPokemon_GetFightPokemonPtr(poke);
    if (pokemon == nullptr) return -1;
    return fightPokemonGetTasteLike(pokemon, taste);
}

u32 fightPokemonDoItemSoubi(FightPokemon* poke, u16 item, u8 operation) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonDoItemSoubi(pokemon, item, operation);
}

u32 fightOutPokemonDoItemSoubi(FightOutPokemon* poke, u16 item, u8 operation, u8 trackUsed) {
    FightPokemon* pokemon = fightOutPokemon_GetFightPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    u32 previous = fightPokemonDoItemSoubi(pokemon, item, operation);
    if (trackUsed == 1) {
        if (operation == 0 && static_cast<u16>(previous) != 0)
            fightOutPokemon_SetUsedItemDataId(poke, previous);
        if (operation == 1 && item != 0)
            fightOutPokemon_SetUsedItemDataId(poke, 0);
    }
    return previous;
}

u32 fightOutPokemonIsHinsi(FightOutPokemon* poke) {
    if (static_cast<u8>(fightOutPokemonCheckValid(poke)) == 0) return 1;
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 1;
    return pokemon_GetHinsi(pokemon);
}

u32 fightOutPokemonNowHpWaruValue(FightOutPokemon* poke, u16 divisor) {
    u16 move = fightOutPokemon_GetUseWazaDataId(poke);
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonGetNowHpWaruValue(pokemon, divisor, move);
}

u32 fightOutPokemonMaxHpWaruValue(FightOutPokemon* poke, u16 divisor) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonGetMaxHpWaruValue(pokemon, divisor);
}

u32 fightOutPokemonIsNokoriHpFollowing(FightOutPokemon* poke, u16 divisor) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonIsNokoriHpFollowing(pokemon, divisor);
}

u32 fightPokemonGetLevelToExp(FightPokemon* poke, u8 level) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonGetLevelToExp(pokemon, level);
}

void figthPokemonSetExp(FightPokemon* poke, u32 experience) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon != nullptr) pokemon_SetExp(pokemon, experience);
}

void fightPokemonGrowBasisStatus(FightPokemon* poke, u32 mode) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon != nullptr) pokemonGrowBasisStatus(pokemon, mode);
}

void fightPokemonCreate(void* context, FightPokemon* poke, Pokemon* source, s16 entry) {
    if (poke != nullptr && source != nullptr) {
        fightPokemonInit(poke);
        fightPokemon_SetMotoPokemonPtr(poke, source);
        pokemonBiosCopy(fightPokemon_GetPokemonBuffPtr(poke), source);
        fightPokemon_SetEntryId(poke, entry);
    }
}

u32 fightPokemonGetSex(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonGetSex(pokemon);
}

u32 fightOutPokemonGetSex(FightOutPokemon* poke) {
    return fightPokemonGetSex(fightOutPokemon_GetFightPokemonPtr(poke));
}

u32 fightPokemonIsHpMantan(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonIsHpMantan(pokemon);
}

u32 fightOutPokemonIsHpMantan(FightOutPokemon* poke) {
    return fightPokemonIsHpMantan(fightOutPokemon_GetFightPokemonPtr(poke));
}

u16* fightPokemonGetNicknamePtr(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemon_GetNicknamePtr(pokemon);
}

u16* fightOutPokemonGetNicknamePtr(FightOutPokemon* poke) {
    return fightPokemonGetNicknamePtr(fightOutPokemon_GetFightPokemonPtr(poke));
}

u32 figthPokemonGetExp(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemon_GetExp(pokemon);
}

u32 figthPokemonGetPokemonDataId(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemon_GetPokemonDataId(pokemon);
}

u32 figthPokemonGetLevel(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemon_GetLevel(pokemon);
}

u32 fightOutPokemonGetNowHpPercentage(FightOutPokemon* poke) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonGetNowHpPercentage(pokemon);
}

u32 fightOutPokemonIsJoutaiKaragenki(FightOutPokemon* poke) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonIsJoutaiKaragenki(pokemon);
}

u32 fightOutPokemonIsJoutaiNormal(FightOutPokemon* poke) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return pokemonIsJoutaiNormal(pokemon);
}

u32 figthOutPokemonGetPokemonDataId(FightOutPokemon* poke) {
    return figthPokemonGetPokemonDataId(fightOutPokemon_GetFightPokemonPtr(poke));
}

u32 figthOutPokemonGetLevel(FightOutPokemon* poke) {
    return figthPokemonGetLevel(fightOutPokemon_GetFightPokemonPtr(poke));
}

u32 fightPokemonGetSoubiItemBuff(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    if (fightPokemonIsJoutaiDataId(poke, 0x3d) == 1) return 0;
    return static_cast<u16>(pokemonGetSoubiItemBuff(pokemon));
}

u32 fightPokemonGetSoubiItemSoubiDataId(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    if (fightPokemonIsJoutaiDataId(poke, 0x3d) == 1) return 0;
    return pokemonGetSoubiItemSoubiDataId(pokemon);
}

u32 fightPokemonGetSoubiItemDataId(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    if (fightPokemonIsJoutaiDataId(poke, 0x3d) == 1) return 0;
    return pokemonGetSoubiItemDataId(pokemon);
}

u32 fightOutPokemonGetSoubiItemDataId(FightOutPokemon* poke) {
    return fightPokemonGetSoubiItemDataId(fightOutPokemon_GetFightPokemonPtr(poke));
}
}

extern "C" {
struct FightSide;
u8 fightFloor_GetFightTypeTrainerNum(void*);
u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);
FightTrainer* fightSide_GetFightTrainerPtr(FightSide*, u16);
u8 fightTrainerCheckValid(FightTrainer*);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FightTrainer*, u16);
void fightOutPokemonEnemyInit(FightOutPokemonEnemy*);
void fightOutPokemonEnemyCreate(FightOutPokemonEnemy*, FightOutPokemon*);
u8 fightActionCheckValid(FightActionBuff*);
u32 fightActionBiosGetKind(FightActionBuff*);
u32 fightActionBiosGetBuffDataId(FightActionBuff*);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*, FightOutPokemon*);


u8 fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(FightOutPokemon* poke, u16* moves) {
    if (poke == nullptr) return 0;
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(poke, 0);
    for (u8 i = 0; i < 4; i++) {
        if (moves != nullptr) moves[i] = 0;
    }
    u8 count = 0;
    for (u8 i = 0; i < 4; i++) {
        FightOutPokemonEnemy* enemy = &enemies[i];
        if (fightOutPokemonEnemyCheckValid(enemy) != 0) {
            u32 move = fightOutPokemonEnemyBiosGetOumuWazaDataId(enemy);
            if (static_cast<u16>(move) != 0 && static_cast<u16>(move) != 0x176) {
                if (moves != nullptr) moves[count] = move;
                count++;
            }
        }
    }
    return count;
}

void fightOutPokemonInitFightPokemonEnemyAry(FightOutPokemon* poke, FightOutPokemon* attacker) {
    if (poke != nullptr) {
        FightOutPokemonEnemy* enemy = fightOutPokemonEnemySearchAry(
            fightOutPokemon_GetFightOutPokemonEnemyPtr(poke, 0), 4, attacker);
        if (enemy != nullptr) {
            u32 move = fightOutPokemonEnemyBiosGetOumuWazaDataId(enemy);
            fightOutPokemonEnemyInit(enemy);
            if (static_cast<u16>(move) != 0 && static_cast<u16>(move) != 0x176 &&
                static_cast<u16>(move) != 0xffff &&
                fightOutPokemon_GetOumuWazaDataId(poke) == 0 &&
                fightOutPokemonGetFightOutPokemonEnemyOumuWazaDataIdAry(poke, nullptr) == 0)
                fightOutPokemon_SetOumuWazaDataId(poke, move);
        }
    }
}

FightOutPokemonEnemy* fightOutPokemonCreateFightPokemonEnemyAry(FightOutPokemon* poke, FightOutPokemon* attacker) {
    if (poke == nullptr) return nullptr;
    if (static_cast<u8>(fightOutPokemonCheckValid(attacker)) == 0) return nullptr;
    FightOutPokemonEnemy* enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(poke, 0);
    FightOutPokemonEnemy* existing = fightOutPokemonEnemySearchAry(enemies, 4, attacker);
    if (existing != nullptr) return existing;
    FightOutPokemonEnemy* enemy;
    for (u16 i = 0; i < 4; i++) {
        enemy = &enemies[i];
        if (fightOutPokemonEnemyCheckValid(enemy) == 0) {
            fightOutPokemonEnemyCreate(enemy, attacker);
            return enemy;
        }
    }
    return nullptr;
}

void fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(FightOutPokemon* poke, FightSide* side) {
    fightFloor_GetFightType(nullptr);
    u32 trainerCount = static_cast<u8>(fightFloor_GetFightTypeTrainerNum(nullptr));
    u32 pokemonCount = static_cast<u8>(fightFloor_GetFightTypeFightoutPokemonNum(nullptr));
    for (u16 trainerIndex = 0; trainerIndex < trainerCount; trainerIndex++) {
        FightTrainer* trainer = fightSide_GetFightTrainerPtr(side, trainerIndex);
        if (fightTrainerCheckValid(trainer) != 0) {
            for (u16 pokemonIndex = 0; pokemonIndex < pokemonCount; pokemonIndex++) {
                FightOutPokemon* enemy = fightTrainer_GetFightoutPokemonPtr(trainer, pokemonIndex);
                if (static_cast<u8>(fightOutPokemonCheckFightOut(enemy)) != 0)
                    fightOutPokemonCreateFightPokemonEnemyAry(poke, enemy);
            }
        }
    }
}

u8 fightOutPokemonCheckMeetEnemyFightPokemon(FightOutPokemon* poke, FightPokemon* enemy) {
    if (poke == nullptr) return 0;
    if (static_cast<u8>(fightPokemonCheckValid(enemy)) == 0) return 0;
    s16 entry = fightPokemon_GetEntryId(enemy);
    for (u8 i = 0; i < 12; i++) {
        int recorded = fightOutPokemon_GetMeetEnemyFightPokemonEntryId(poke, i);
        if (static_cast<s16>(recorded) >= 0 && static_cast<s16>(recorded) == entry) return 1;
    }
    return 0;
}

s32 fightOutPokemonSetMeetEnemyFightPokemon(FightOutPokemon* poke, FightPokemon* enemy) {
    if (poke == nullptr) return -1;
    if (static_cast<u8>(fightPokemonCheckValid(enemy)) == 0) return -1;
    if (fightOutPokemonCheckMeetEnemyFightPokemon(poke, enemy) == 1) return -1;
    int entry = fightPokemon_GetEntryId(enemy);
    for (u8 i = 0; i < 12; i++) {
        if (static_cast<s16>(fightOutPokemon_GetMeetEnemyFightPokemonEntryId(poke, i)) < 0) {
            fightOutPokemon_SetMeetEnemyFightPokemonEntryId(poke, i, entry);
            return static_cast<s8>(i);
        }
    }
    return -1;
}

void fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(FightOutPokemon* poke, FightSide* side) {
    fightFloor_GetFightType(nullptr);
    u32 trainerCount = static_cast<u8>(fightFloor_GetFightTypeTrainerNum(nullptr));
    u32 pokemonCount = static_cast<u8>(fightFloor_GetFightTypeFightoutPokemonNum(nullptr));
    for (u16 trainerIndex = 0; trainerIndex < trainerCount; trainerIndex++) {
        FightTrainer* trainer = fightSide_GetFightTrainerPtr(side, trainerIndex);
        if (fightTrainerCheckValid(trainer) != 0) {
            for (u16 pokemonIndex = 0; pokemonIndex < pokemonCount; pokemonIndex++) {
                FightOutPokemon* enemy = fightTrainer_GetFightoutPokemonPtr(trainer, pokemonIndex);
                if (static_cast<u8>(fightOutPokemonCheckFightOut(enemy)) != 0)
                    fightOutPokemonSetMeetEnemyFightPokemon(poke, fightOutPokemon_GetMotoFightPokemonPtr(enemy));
            }
        }
    }
}

u8 fightOutPokemonCheckIrekaeReserveFightPokemon(FightOutPokemon* poke, FightPokemon* reserve) {
    int entry = fightPokemon_GetEntryId(reserve);
    if (static_cast<s16>(entry) < 0) return 0;
    if (static_cast<s16>(entry) == static_cast<s16>(fightOutPokemon_GetIrekaeTargetEntryId(poke))) return 1;
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action != nullptr && fightActionCheckValid(action) == 1 &&
        static_cast<u16>(fightActionBiosGetKind(action)) == 9 &&
        static_cast<s16>(entry) == static_cast<s16>(fightActionBiosGetBuffDataId(action))) return 1;
    return 0;
}

u8 fightPokemonCheckMotoFightPokemon(FightPokemon* poke, FightOutPokemon* active) {
    return fightOutPokemon_GetMotoFightPokemonPtr(active) == poke;
}

u8 fightOutPokemonIsGcHeroFightOutPokemon(FightOutPokemon* poke) {
    FightTrainer* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(nullptr, poke);
    if (trainer == nullptr) return 0;
    return static_cast<u8>(fightTrainerIsGcHero(trainer)) == 1;
}
}

#include <game/pxdvs/app/fight/fightPokemonMenus.hpp>
extern "C" {
void fightOutPokemonToMenuPokemonStatus(FightOutPokemon* poke, FightMenuPokemonStatus* menu) {
    FightPokemon* current;
    s8 rare = -1;
    current = fightOutPokemon_GetFightPokemonPtr(poke);
    Pokemon temporary;
    pokemonBiosCopy(&temporary, fightPokemonGetPokemonPtr(current));
    if (fightOutPokemonIsJoutaiDataId(poke, 0x10) == 1) {
        u32 personality;
        u32 trainer;
        fightOutPokemonGetRndStatus(poke, &personality, &trainer);
        pokemon_SetRnd(&temporary, personality);
        pokemon_SetCatchTrainerRnd(&temporary, trainer);
        rare = static_cast<s8>(pokemonCheckRare(
            fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(poke))));
    }
    pokemonToMenuPokemonStatus(&temporary, current, menu, rare);
    Pokemon* original = fightPokemonGetPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(poke));
    if (original != nullptr) {
        pokemonToMenuPokemonStatusSubBar(original, menu);
        menu->sex = menuSubGetPokemonSexForFightDisp(original);
    }
    menu->hideSubbar = 1;
    if (fightOutPokemonIsGcHeroFightOutPokemon(poke) == 1) menu->hideSubbar = 0;
    if (fightFloor_GetFightKindPokemonStatusMenuSubbarFlag(nullptr) == 0) menu->hideSubbar = 1;
    menu->reserved2d = 0;
}

void fightPokemonToMenuWazaStatus(FightPokemon* poke, FightMenuWazaStatus* menu) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon != nullptr) pokemonToMenuWazaStatus(pokemon, menu);
}

void fightOutPokemonToMenuWazaStatus(FightOutPokemon* poke, FightMenuWazaStatus* menu) {
    fightPokemonToMenuWazaStatus(fightOutPokemon_GetFightPokemonPtr(poke), menu);
    menu->fightPokemon = poke;
}

void fightPokemonToMenuLvupStatus(FightPokemon* poke, FightMenuLvupStatus* menu) {
    if (poke != nullptr && menu != nullptr) {
        Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
        menu->maxHp = pokemon_GetMaxHp(pokemon);
        menu->physicalAttack = pokemon_GetPhyAtk(pokemon);
        menu->physicalDefense = pokemon_GetPhyDef(pokemon);
        menu->specialAttack = pokemon_GetSpeAtk(pokemon);
        menu->specialDefense = pokemon_GetSpeDef(pokemon);
        menu->speed = pokemon_GetNimbleness(pokemon);
        menu->mode = 0;
    }
}

u32 fightActionGetKindDataId(FightActionBuff*);
u32 fightItem_GetItemDataId(FightItem*);
u32 fightItem_GetTargetDataId(FightItem*);
u32 fightWaza_GetMotoWazaDataId(FightWaza*);
u32 fightWaza_GetZokusei(FightWaza*);
u32 wazaDB_GetSeqId(u32);
FightTarget* fightTargetGetPtrAsNowFightType(u8, void*);
s32 fightActionGetPri(FightActionBuff*);
u8 itemDataCheckValid(u16);
u8 itemDB_GetKind(u16);
extern u32* item_data_index_number;
u8 fightOutPokemonIsFightActionUseItem(FightOutPokemon*, u16, FightTarget*);
u32 zokuseiGetWazaJoutai(u16, u16);
void pokemonSetOnZukanFlag(Pokemon*, u8);
void pokemonSetCountAsJoutaiDataId(Pokemon*, u16, u8);
void joutaiSetCountAsJoutaiDataId(void*, u16, u8);

u8 fightOutPokemonIsFightActionUseItemKind(FightOutPokemon* poke, u8 kind, u8 equal) {
    for (u16 item = 0; item < *item_data_index_number; item++) {
        if (itemDataCheckValid(item) != 0) {
            if (equal == 1) {
                if (kind != itemDB_GetKind(item)) continue;
            } else {
                if (kind == itemDB_GetKind(item)) continue;
            }
            if (fightOutPokemonIsFightActionUseItem(poke, item, nullptr) == 1) return 1;
        }
    }
    return 0;
}

u8 fightOutPokemonIsFightActionUseItem(FightOutPokemon* poke, u16 item, FightTarget* target) {
    u8 type = fightFloor_GetFightType(nullptr);
    if (poke == nullptr) return 0;
    u32 targetId;
    if (target == nullptr) targetId = 0;
    else targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, type);
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return 0;
    if (fightActionCheckValid(action) == 0) return 0;
    if (static_cast<u16>(fightActionGetKindDataId(action)) != 0x12) return 0;
    FightItem* itemRecord = fightOutPokemon_GetFightItemPtr(poke);
    if (itemRecord == nullptr) return 0;
    u32 selectedItem = fightItem_GetItemDataId(itemRecord);
    u32 selectedTarget = fightItem_GetTargetDataId(itemRecord);
    if (item != 0 && static_cast<u16>(selectedItem) != item) return 0;
    if (static_cast<u16>(targetId) != 0 && static_cast<u16>(selectedTarget) != static_cast<u16>(targetId)) return 0;
    return 1;
}

u32 fightOutPokemonGetFightActionUseItemDataId(FightOutPokemon* poke) {
    fightFloor_GetFightType(nullptr);
    if (poke == nullptr) return 0;
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return 0;
    if (fightActionCheckValid(action) == 0) return 0;
    if (static_cast<u16>(fightActionGetKindDataId(action)) != 0x12) return 0;
    FightItem* item = fightOutPokemon_GetFightItemPtr(poke);
    if (item == nullptr) return 0;
    return fightItem_GetItemDataId(item);
}

u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon* poke, u16 move, FightTarget* target) {
    u32 type = static_cast<u8>(fightFloor_GetFightType(nullptr));
    if (poke == nullptr) return 0;
    u32 targetId;
    if (target == nullptr) targetId = 0;
    else targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, type);
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return 0;
    if (fightActionCheckValid(action) == 0) return 0;
    if (static_cast<u16>(fightActionGetKindDataId(action)) != 0x13) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 0;
    u32 selectedMove = fightWaza_GetMotoWazaDataId(waza);
    u32 sequence = wazaDB_GetSeqId(selectedMove);
    if (move != 0 && static_cast<u16>(selectedMove) != move) return 0;
    u32 selectedTarget = fightWaza_GetTargetDataId(waza);
    if (static_cast<u16>(sequence) == 0xb0) {
        selectedTarget = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(
            fightTargetGetPtrAsNowFightType(0xe, poke), type);
    }
    if (static_cast<u16>(targetId) != 0 && static_cast<u16>(selectedTarget) != static_cast<u16>(targetId)) return 0;
    return 1;
}

s32 fightOutPokemonGetFightActionPri(FightOutPokemon* poke) {
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return -128;
    return fightActionGetPri(action);
}

u32 fightOutPokemonGetWazaZokuseiDataId(FightOutPokemon* poke) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 9;
    return fightWaza_GetZokusei(waza);
}

u32 fightOutPokemonGetUseWazaDataId(FightOutPokemon* poke) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 0;
    return fightWaza_GetUseWazaDataId(waza);
}

u32 fightOutPokemonGetMotoWazaDataId(FightOutPokemon* poke) {
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 0;
    return fightWaza_GetMotoWazaDataId(waza);
}

u32 fightOutPokemonGetCmpNimblenessWazaDataId(FightOutPokemon* poke) {
    return fightOutPokemonGetMotoWazaDataId(poke);
}

u16 fightOutPokemonGetTeikouZokuseiDataIdAry(FightOutPokemon* poke, u16 attackType, s32* types) {
    for (u16 i = 0; i < 18; i++) types[i] = -1;
    u16 type;
    u16 count = 0;
    for (type = 0; type < 18; type++) {
        if (fightOutPokemonIsZokuseiDataId(poke, type) != 1) {
            u32 effect = zokuseiGetWazaJoutai(attackType, type);
            if (static_cast<u16>(effect) == 0x42 || static_cast<u16>(effect) == 0x43) {
                types[count] = type;
                count++;
            }
        }
    }
    return count;
}

void fightOutPokemonSetOnZukanFlag(FightOutPokemon* poke, u8 flag) {
    if (poke != nullptr)
        pokemonSetOnZukanFlag(fightPokemon_GetMotoPokemonPtr(fightOutPokemon_GetMotoFightPokemonPtr(poke)), flag);
}

void fightPokemonSetCountAsJoutaiDataId(FightPokemon* poke, u16 condition, u8 count) {
    if (joutaiDataBiosGetStatus(condition) == 0x7c || joutaiDataBiosGetStatus(condition) == 0xc8) {
        pokemonSetCountAsJoutaiDataId(fightPokemonGetPokemonPtr(poke), condition, count);
    } else if (joutaiDataBiosGetStatus(condition) == 0xcd) {
        joutaiSetCountAsJoutaiDataId(poke, condition, count);
    }
}

void fightOutPokemonInitJoutaiKeep(FightOutPokemon* poke) {
    u16 conditions[9] = { 0x22, 0xd, 0xb, 0xc, 0x1f, 0x20, 0x21, 0x2e, 0x2f };
    u16 condition;
    if (poke != nullptr) {
        for (u8 i = 0; i < 9; i++) {
            condition = conditions[i];
            if (fightOutPokemonIsJoutaiDataId(poke, condition) == 1)
                fightOutPokemonInitJoutaiDataId(poke, condition);
        }
    }
}
}

extern "C" {
u32 pokemonDB_GetVoice(u32);
u32 pokemonDB_GetName(u32);
void* GSmsgGetGSchar(u32);
void* Sequence_GetGSmodel(void*);
void Sequence_SetVisibility(void*, u8);
void Sequence_SetDownFlag(void*, u8);
void Sequence_FreeAllWaza(void*);
void Sequence_Free(void*);
void battleGridRemovePokemon(void*);
u32 wazaDB_GetWazawzxdataId(u16);
void fightOutPokemonRegWzxFree(FightOutPokemon*);
u32 fightOutPokemonRegWzxLoad(FightOutPokemon*);
u32 pokemonDB_GetPkxDataId(u32);
u8 pokemonGetAnnonKatati(u32);
u8 pokemonGetFightPokemonDeoxysSel(FightPokemon*);
u8 pokemonIsDarkPokemon(Pokemon*);
void* Sequence_LoadPokemon(u16, u32, u8);
void pokemonSetSequenceStatus(Pokemon*, void*);
void fightFloorLoopValidFightOutPokemon(void*, u8 (*)(void*, u16, void*), void*, u32);

u32 fightOutPokemonGetVoiceSndId(FightOutPokemon* poke) {
    return pokemonDB_GetVoice(pokemon_GetPokemonDataId(fightOutPokemonGetPokemonPtr(poke)));
}

void* fightPokemonGetNamePtr(FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return nullptr;
    return GSmsgGetGSchar(pokemonDB_GetName(pokemon_GetPokemonDataId(pokemon)));
}

void* fightOutPokemonGetNamePtr(FightOutPokemon* poke) {
    return fightPokemonGetNamePtr(fightOutPokemon_GetFightPokemonPtr(poke));
}

void* fightOutPokemonGetGsmodelPtr(FightOutPokemon* poke) {
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence == nullptr) return nullptr;
    return Sequence_GetGSmodel(sequence);
}

void fightOutPokemonSetVisibility(FightOutPokemon* poke, u8 visible) {
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) Sequence_SetVisibility(sequence, visible);
}

void fightOutPokemonSetWazaEffectDownFlag(FightOutPokemon* poke, u8 down) {
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) Sequence_SetDownFlag(sequence, down);
}

void fightOutPokemonFreeAllSequenceWaza(FightOutPokemon* poke) {
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) Sequence_FreeAllWaza(sequence);
}

void fightOutPokemonFreeWazaEffect(FightOutPokemon* poke, u16 move, u32 slot) {
    u32 effect = wazaDB_GetWazawzxdataId(move);
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) WazaSequence_Free(Sequence_GetWaza(sequence, effect, slot));
}

void fightOutPokemonFreeSequence(FightOutPokemon* poke) {
    fightOutPokemonRegWzxFree(poke);
    void* sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) {
        fightOutPokemonSetVisibility(poke, 0);
        fightOutPokemon_SetSequencePtr(poke, nullptr);
        battleGridRemovePokemon(sequence);
        Sequence_Free(sequence);
    }
}

u32 fightOutPokemonRegWzxLoad(FightOutPokemon* poke) {
    return itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(poke)));
}
}

struct FightBallEffectReferences {
    FightOutPokemon* owner;
    u32 effect;
    u32 count;
};
static u8 _fightOutPokemonRegWzxFreeSub(void* record, u16 index, void* context) {
    FightBallEffectReferences* references = static_cast<FightBallEffectReferences*>(context);
    FightOutPokemon* poke = static_cast<FightOutPokemon*>(record);
    FightOutPokemon* owner = references->owner;
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    if (poke == owner) return 1;
    u32 effect = itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(pokemon));
    if (effect == 0) return 1;
    if (references->effect == effect) references->count++;
    return 1;
}

extern "C" void fightOutPokemonRegWzxFree(FightOutPokemon* poke) {
    u32 effect = itemBallDB_GetDowninWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(poke)));
    if (effect != 0) {
        FightBallEffectReferences references;
        references.owner = poke;
        references.effect = effect;
        references.count = 0;
        fightFloorLoopValidFightOutPokemon(nullptr, _fightOutPokemonRegWzxFreeSub, &references, 0);
    }
}

static u32 _fightOutPokemonGetTenkiyaPkxDataId(u16 weather) {
    switch (weather) {
    case 1: return 0x19f;
    case 2: return 0x19e;
    case 4: return 0x1a0;
    default: return 0x181;
    }
}

extern "C" void* fightOutPokemonCreateSequence(FightOutPokemon* poke, u16 weather, s8 rare) {
    Pokemon* pokemon = fightOutPokemonGetPokemonPtr(poke);
    FightPokemon* current = fightOutPokemon_GetFightPokemonPtr(poke);
    Pokemon temporary;
    pokemonBiosCopy(&temporary, pokemon);
    u32 species = pokemon_GetPokemonDataId(&temporary);
    u32 model = pokemonDB_GetPkxDataId(species);
    if (static_cast<u16>(species) == 0x181) model = _fightOutPokemonGetTenkiyaPkxDataId(weather);
    if (fightOutPokemonIsJoutaiDataId(poke, 0x14) == 1) model = 0x19d;
    if (model == 0) return nullptr;
    u32 personality;
    u32 trainer;
    fightOutPokemonGetRndStatus(poke, &personality, &trainer);
    pokemon_SetRnd(&temporary, personality);
    pokemon_SetCatchTrainerRnd(&temporary, trainer);
    if (rare == -1) rare = static_cast<s8>(pokemonCheckRare(&temporary));
    u32 form;
    switch (static_cast<s32>(model)) {
    case 0xc9:
        form = pokemonGetAnnonKatati(personality);
        break;
    case 0x19a:
        form = pokemonGetFightPokemonDeoxysSel(current);
        break;
    case 0xf9:
        if (pokemonIsDarkPokemon(pokemon) == 1) model = 0x1a1;
        form = personality;
        break;
    default:
        form = personality;
        break;
    }
    void* sequence = Sequence_LoadPokemon(model, form, rare != 0);
    pokemonSetSequenceStatus(&temporary, sequence);
    fightOutPokemonRegWzxLoad(poke);
    return sequence;
}

extern "C" {
void pokemonGetFriendFormPokemonFriendFilterId(Pokemon*, u32, u16);
void pokemonGetEffortFromPokemon(Pokemon*, u32, Pokemon*, u8);
u8 fightActionCreate(FightActionBuff*, u32, FightOutPokemon*, u32, u32, FightActionData*);
void fightActionBiosSetBuffDataId(FightActionBuff*, u32);
void fightItemCreate(FightItem*, u32, u32, s32);
void fightItem_SetBuff(FightItem*, u8);
void fightWazaCreate(FightWaza*, s32, u32, u32, u8);
void fightFloorSetShadow();
u8 pokemonDB_GetZokuseiDataId(u32, u16);
u32 pokemonGetTokuseiDataId(Pokemon*);

void fightPokemonGetFriendFormPokemonFriendFilterId(FightPokemon* poke, u16 filter) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon != nullptr) {
        u32 itemEffect = fightPokemonGetSoubiItemSoubiDataId(poke);
        pokemonGetFriendFormPokemonFriendFilterId(pokemon, itemEffect, filter);
    }
}

void fightPokemonGetEffortFromPokemon(FightPokemon* poke, Pokemon* defeated, u8 multiplier) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon != nullptr) {
        u32 itemEffect = fightPokemonGetSoubiItemSoubiDataId(poke);
        pokemonGetEffortFromPokemon(pokemon, itemEffect, defeated, multiplier);
    }
}

u32 figthOutPokemonGetSoubiItemBuff(FightOutPokemon* poke) {
    return fightPokemonGetSoubiItemBuff(fightOutPokemon_GetFightPokemonPtr(poke));
}

u32 fightOutPokemonGetSoubiItemSoubiDataId(FightOutPokemon* poke) {
    return fightPokemonGetSoubiItemSoubiDataId(fightOutPokemon_GetFightPokemonPtr(poke));
}

FightActionBuff* fightOutPokemonCreateFightAction(FightOutPokemon* poke, u32 kind,
    u32 priority, u32 speed, FightActionData* data, u32 value) {
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return nullptr;
    if (fightActionCreate(action, kind, poke, priority, speed, data) == 1) {
        fightActionBiosSetBuffDataId(action, value);
        return action;
    }
    return nullptr;
}

FightActionBuff* fightOutPokemonCreateFightActionUseItem(FightOutPokemon* poke, u32 kind,
    u32 priority, u32 speed, FightActionData* data, u32 itemId, u32 target, s32 slot, u8 value) {
    FightItem* itemRecord;
    u16 item = itemId;
    itemRecord = fightOutPokemon_GetFightItemPtr(poke);
    if (itemRecord == nullptr) return nullptr;
    fightItemCreate(itemRecord, item, target, slot);
    fightItem_SetBuff(itemRecord, value);
    FightActionBuff* action = fightOutPokemonCreateFightAction(poke, kind, priority, speed, data, itemId);
    if (action == nullptr) return nullptr;
    return action;
}

FightActionBuff* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon* poke, u32 kind,
    u32 priority, u32 speed, FightActionData* data, u16 moveId, u32 target, s32 slot, u8 value) {
    u16 move = moveId;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return nullptr;
    fightWazaCreate(waza, slot, move, target, value);
    FightActionBuff* action = fightOutPokemonCreateFightAction(poke, kind, priority, speed, data, moveId);
    if (action == nullptr) return nullptr;
    return action;
}

void fightOutPokemonCreate(FightOutPokemon* poke, FightPokemon* source, void* sequence) {
    if (poke != nullptr && source != nullptr) {
        Pokemon* pokemon = fightPokemonGetPokemonPtr(source);
        fightOutPokemonInit(poke);
        fightOutPokemon_SetMotoFightPokemonPtr(poke, source);
        fightOutPokemon_SetFightPokemonPtr(poke, source);
        if (sequence != nullptr) {
            fightOutPokemon_SetSequencePtr(poke, sequence);
            fightFloorSetShadow();
        }
        u32 species = pokemon_GetPokemonDataId(pokemon);
        for (u16 i = 0; i < 2; i++)
            fightOutPokemonSetZokuseiDataId(poke, i, pokemonDB_GetZokuseiDataId(species, i));
        fightOutPokemonSetTokuseiDataId(poke, pokemonGetTokuseiDataId(pokemon));
    }
}
}

u16 wazaSequenceSysGetResourceID(ModelSequence*, u16, u16, u8);
struct FightWazaResource {
    u32 fsysGroupId;
    u32 resourceId;
};
extern "C" {
extern FightWazaResource waza_resource_data[];
extern u32 dbgEffLoadFsysGroupID;

void fightOutPokemonLoadWazaEffect(FightOutPokemon* poke, u16 move, u32 slot, u8 variation) {
    u32 effect = wazaDB_GetWazawzxdataId(move);
    ModelSequence* sequence = static_cast<ModelSequence*>(fightOutPokemon_GetSequencePtr(poke));
    if (sequence != nullptr) {
        Sequence_LoadWaza(sequence, effect, static_cast<u8>(slot), variation);
        ModelSequence* model;
        if (sequence->type == 1) model = sequence;
        else model = nullptr;
        u16 resource = wazaSequenceSysGetResourceID(model, effect, static_cast<u8>(slot), variation);
        if (resource != 0) dbgEffLoadFsysGroupID = waza_resource_data[resource].fsysGroupId;
    }
}
}

extern "C" {
s32 fightMenuGetFightOutPokemonPtrToStatusMenuId(FightOutPokemon*, u32, u32);
u8 dbgMenuFightGetFightPokeStMenuOpenFlag(s32);
void menuOpenCustom(s32, u32, u32, u32, u32, u32, ...);
void fightFloor_SetStatusMenuCnt(s32, s32);
void fightWazaDoEffect(void*, u32, u32, u8);
void fightMenuCloseCustom(s32, u32, u32);

void fightOutPokemonWazaEffect(FightOutPokemon* poke, u32 effect, u32 slot, u8 phase, s32 menuId) {
    void* sequence;
    u8 type = fightFloor_GetFightType(nullptr);
    sequence = fightOutPokemon_GetSequencePtr(poke);
    if (sequence != nullptr) {
        FightMenuPokemonStatus menu;
        fightOutPokemonToMenuPokemonStatus(poke, &menu);
        if (menuId >= 0) {
            menuId = fightMenuGetFightOutPokemonPtrToStatusMenuId(poke, type, 1);
            if (dbgMenuFightGetFightPokeStMenuOpenFlag(menuId) == 1) {
                menuOpenCustom(menuId, 0, 0, 0, 0, 1, &menu);
                fightMenuFightOutPokemonCloseStatusMenuAnotherMine(menuId, poke, type, 0, 1);
                fightFloor_SetStatusMenuCnt(menuId, -1);
            }
        }
        fightWazaDoEffect(sequence, effect, slot, phase);
        if (phase == 1 && menuId >= 0) fightMenuCloseCustom(menuId, 0, 0);
    }
}
}
