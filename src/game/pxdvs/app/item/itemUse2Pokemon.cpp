#include <game/pxdvs/app/item/itemUse2PokemonPrivate.hpp>

extern "C" {
// The special seed item expands this persistent original-format parameter block.
static u32 origRamSeedParam[2] = { 0, 0 };

s16 itemUse2PokemonSimulation(ITEMUSE2POKEMON_LOG1 *arg0, void *arg1, void *arg2, u16 arg3, u8 arg4) {
    void *temp_r3_2;
    void *temp_r3;
    s16 temp_r29;

    temp_r3 = fightFloorGetNowPtr();
    if (temp_r3 == 0) {
        return 0;
    }
    temp_r3_2 = GSmemAlloc(0xE318U);
    memcpy(temp_r3_2, temp_r3, 0xE318U);
    temp_r29 = itemUse2Pokemon(arg0, arg1, arg2, arg3, arg4);
    memcpy(temp_r3, temp_r3_2, 0xE318U);
    GSmemFree(temp_r3_2);
    return temp_r29;
}

static s16 friendXUp__FP7PokemonP12FightPokemonScUsUs(void* pokemon, void* fightPokemon, s8 adjustment, u16 minimum, u16 maximum) {
    s32 value;
    u32 original;
    if (pokemonIsDarkPokemon(pokemon) && pokemonGetDarkPokemonLevel(pokemon) < 3) return 0;
    if (pokemonIsDarkPokemon(pokemon)) original = (u16)pokemon_GetPoolFriend(pokemon);
    else original = (u16)pokemonBiosGetFriend(pokemon);
    if (pokemonIsDarkPokemon(pokemon)) value = (u16)pokemon_GetPoolFriend(pokemon);
    else value = 0;
    s32 total = value + (u16)pokemonBiosGetFriend(pokemon);
    if (total < minimum || total >= maximum) return 0;
    value = adjustment;
    if (value > 0) {
        void* data = itemDataBiosGetPtr(pokemonBiosGetItemDataId(pokemon));
        u16 held;
        if (data == 0) held = 0;
        else held = itemDataBiosGetItemSoubiDataId(data);
        if (held == 0x1b) value = value * 150 / 100;
        if (pokemonBiosGetCatchBallId(pokemon) == 11) value++;
    }
    if (pokemonIsDarkPokemon(pokemon)) value = value * 80 / 100;
    value = original + value;
    if (value > 255) value = 255;
    if (value < 0) value = 0;
    if (pokemonIsDarkPokemon(pokemon)) {
        pokemonSetStatus(pokemon,0,0xc7,0,value);
        void* out;
        if (fightPokemon == 0) out = 0;
        else out = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0,fightPokemon),fightPokemon);
        if (out) fightSeqCheckSetMotoPokemonToHensinBuff(out,0xc7);
    } else {
        pokemonBiosSetFriend(pokemon,(u16)value);
        void* out;
        if (fightPokemon == 0) out = 0;
        else out = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0,fightPokemon),fightPokemon);
        if (out) fightSeqCheckSetMotoPokemonToHensinBuff(out,0x99);
    }
    return (s16)(value-original);
}

static void hpRecover__FP20ITEMUSE2POKEMON_LOG1PsP7PokemonUcbUsP12FightPokemon(ITEMUSE2POKEMON_LOG1 *arg0, s16 *arg1, void *arg2, u8 arg3, u8 arg4, u16 arg5, void *arg6) {
    LogEntry *temp_r3_3;
    LogEntry *temp_r4;
    s16 temp_r3_2;
    s16 temp_r3_4;
    u16 temp_r0;
    u16 temp_r30;
    u16 temp_r3;
    u16 var_r30;
    u16 var_r4;
    u8 var_r29;
    void *var_r3;

    var_r29 = 0;
    temp_r30 = pokemonBiosGetHp(arg2);
    temp_r3 = pokemonBiosGetMaxHp(arg2);
    if (temp_r30 < temp_r3) {
        switch ((s32) arg3) {                       /* irregular */
        case 0xFF:
            var_r4 = temp_r3;
            break;
        case 0xFE:
            temp_r0 = (temp_r3 >> 1U) & 0x7FFF;
            var_r4 = temp_r0;
            if (temp_r0 == 0) {
                var_r4 = 1;
            }
            break;
        case 0xFD:
            var_r4 = arg5;
            break;
        default:
            var_r4 = (u16) arg3;
            break;
        }
        if (var_r4 != 0) {
            if (temp_r30 == 0) {
                if (arg4 != 0) {
                    var_r29 = 1;
                    goto block_16;
                }
            } else if (arg4 == 0) {
block_16:
                var_r30 = temp_r30 + var_r4;
                if (var_r30 > temp_r3) {
                    var_r30 = temp_r3;
                }
                pokemonBiosSetHp(arg2, var_r30);
                if (arg6 == 0) {
                    var_r3 = 0;
                } else {
                    var_r3 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg6), arg6);
                }
                if (var_r3 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3, 0x83U);
                }
                if (var_r29 != 0) {
                    temp_r3_2 = *arg1;
                    if (temp_r3_2 < 0x20) {
                        arg0->e[temp_r3_2].key = 0x16;
                        temp_r3_3 = &arg0->e[temp_r3_2];
                        temp_r3_3->a = 0;
                        temp_r3_3->b = 0;
                        *arg1 = temp_r3_2 + 1;
                    }
                }
                temp_r3_4 = *arg1;
                if (temp_r3_4 < 0x20) {
                    arg0->e[temp_r3_4].key = 0x15;
                    temp_r4 = &arg0->e[temp_r3_4];
                    temp_r4->a = (s16) (u16) (var_r30 - temp_r30);
                    temp_r4->b = 0;
                    *arg1 = temp_r3_4 + 1;
                }
            }
        }
    }
}

s16 itemUse2Pokemon(ITEMUSE2POKEMON_LOG1 *arg0, void *arg1, void *arg2, u16 arg3, u8 arg4) {
    ItemParam sp10;
    EvolutionInfo spC;
    s16 spA;
    // Preserve the count used by each append before writing its entry.
    s16 logIndex;
    u16 sp8;
    ItemParam *var_r28;
    ItemParam *var_r3;
    LogEntry *temp_r3_18;
    LogEntry *temp_r3_19;
    LogEntry *temp_r3_20;
    LogEntry *temp_r3_21;
    LogEntry *temp_r3_22;
    LogEntry *temp_r3_23;
    LogEntry *temp_r3_24;
    LogEntry *temp_r3_25;
    LogEntry *temp_r3_39;
    LogEntry *temp_r3_3;
    LogEntry *temp_r3_4;
    LogEntry *temp_r4;
    LogEntry *temp_r4_10;
    LogEntry *temp_r4_11;
    LogEntry *temp_r4_12;
    LogEntry *temp_r4_13;
    LogEntry *temp_r4_14;
    LogEntry *temp_r4_15;
    LogEntry *temp_r4_16;
    LogEntry *temp_r4_2;
    LogEntry *temp_r4_3;
    LogEntry *temp_r4_4;
    LogEntry *temp_r4_5;
    LogEntry *temp_r4_6;
    LogEntry *temp_r4_7;
    LogEntry *temp_r4_8;
    LogEntry *temp_r4_9;
    LogEntry *temp_r5;
    LogEntry *temp_r5_2;
    LogEntry *temp_r5_3;
    LogEntry *temp_r5_4;
    s16 temp_r3_52;
    s16 var_r19_10;
    s16 var_r3_26;
    s16 var_r3_27;
    s16 var_r5;
    s16 var_r5_2;
    s16 var_r5_3;
    s16 var_r5_4;
    s16 var_r5_5;
    s16 var_r5_6;
    s32 temp_cr0_eq;
    s32 temp_r19;
    s32 temp_r19_2;
    s32 temp_r19_3;
    s32 temp_r19_4;
    s32 temp_r19_6;
    s32 temp_r19_7;
    s32 temp_r19_8;
    s32 temp_r19_9;
    s32 temp_r21_11;
    s32 temp_r21_12;
    s32 temp_r21_13;
    s32 temp_r21_14;
    s32 temp_r21_16;
    s32 temp_r21_17;
    s32 temp_r21_18;
    s32 temp_r21_19;
    s32 temp_r21_21;
    s32 temp_r21_22;
    s32 temp_r21_23;
    s32 temp_r21_24;
    s32 temp_r21_4;
    s32 temp_r21_5;
    s32 temp_r21_6;
    s32 temp_r21_7;
    s32 temp_r21_8;
    s32 temp_r21_9;
    s32 temp_r22;
    s32 temp_r22_2;
    s32 temp_r22_3;
    s32 temp_r22_4;
    s8 temp_r3_49;
    s8 temp_r3_50;
    s8 temp_r3_51;
    u16 temp_r0;
    u16 temp_r0_2;
    u16 temp_r0_3;
    u16 temp_r0_4;
    u16 temp_r0_5;
    u16 temp_r0_6;
    u16 temp_r19_10;
    u16 temp_r19_5;
    u16 temp_r21;
    u16 temp_r21_10;
    u16 temp_r21_15;
    u16 temp_r21_20;
    u16 temp_r21_25;
    u16 temp_r3_17;
    u16 temp_r3_26;
    u16 temp_r3_29;
    u16 temp_r3_31;
    u16 temp_r3_34;
    u16 temp_r3_36;
    u16 temp_r3_38;
    u16 temp_r3_41;
    u16 temp_r3_43;
    u16 temp_r3_45;
    u16 temp_r3_47;
    u16 temp_r3_48;
    u16 var_r0_6;
    u16 var_r19_6;
    u16 var_r19_7;
    u16 var_r19_8;
    u16 var_r19_9;
    u16 var_r21_11;
    u16 var_r21_12;
    u16 var_r25;
    u8 temp_r0_7;
    u8 temp_r19_11;
    u8 temp_r20;
    u8 temp_r21_2;
    u8 temp_r21_3;
    u8 temp_r22_5;
    u8 temp_r3_10;
    u8 temp_r3_11;
    u8 temp_r3_12;
    u8 temp_r3_13;
    u8 temp_r3_14;
    u8 temp_r3_16;
    u8 temp_r3_27;
    u8 temp_r3_28;
    u8 temp_r3_2;
    u8 temp_r3_30;
    u8 temp_r3_32;
    u8 temp_r3_33;
    u8 temp_r3_35;
    u8 temp_r3_37;
    u8 temp_r3_40;
    u8 temp_r3_42;
    u8 temp_r3_44;
    u8 temp_r3_46;
    u8 temp_r3_5;
    u8 temp_r3_6;
    u8 temp_r3_7;
    u8 temp_r3_8;
    u8 temp_r3_9;
    u8 var_r0;
    u8 var_r0_10;
    u8 var_r0_11;
    u8 var_r0_12;
    u8 var_r0_13;
    u8 var_r0_14;
    u8 var_r0_2;
    u8 var_r0_3;
    u8 var_r0_4;
    u8 var_r0_5;
    u8 var_r0_7;
    u8 var_r0_8;
    u8 var_r0_9;
    u8 var_r20;
    u8 var_r21_3;
    u8 var_r21_4;
    u8 var_r21_5;
    u8 var_r21_6;
    u8 var_r21_7;
    u8 var_r21_8;
    u8 var_r21_9;
    u8 var_r22;
    u8 var_r24;
    u8 var_r24_2;
    u8 var_r25_2;
    void *temp_r3;
    void *temp_r3_15;
    void *var_r19;
    void *var_r19_2;
    void *var_r19_3;
    void *var_r19_4;
    void *var_r19_5;
    void *var_r21;
    void *var_r21_10;
    void *var_r21_2;
    void *var_r23;
    void *var_r31;
    void *var_r3_10;
    void *var_r3_11;
    void *var_r3_12;
    void *var_r3_13;
    void *var_r3_14;
    void *var_r3_15;
    void *var_r3_16;
    void *var_r3_17;
    void *var_r3_18;
    void *var_r3_19;
    void *var_r3_20;
    void *var_r3_21;
    void *var_r3_22;
    void *var_r3_23;
    void *var_r3_24;
    void *var_r3_25;
    void *var_r3_2;
    void *var_r3_3;
    void *var_r3_4;
    void *var_r3_5;
    void *var_r3_6;
    void *var_r3_7;
    void *var_r3_8;
    void *var_r3_9;

    var_r31 = arg1;
    var_r25 = 0;
    spA = 0;
    if (arg3 != 0xAF) {
        temp_r3 = itemDataBiosGetPtr(arg3);
        if (temp_r3 == 0) {
            var_r3 = 0;
        } else {
            temp_r3_2 = itemDataBiosGetItemEffectParam(temp_r3);
            if (temp_r3_2 == 0) {
                var_r3 = 0;
            } else {
                var_r3 = itemParamGetPtr(temp_r3_2);
            }
        }
        var_r28 = var_r3;
    } else {
        itemParamConvertOrigFormat(&sp10, origRamSeedParam);
        var_r28 = &sp10;
    }
    if (var_r28 == 0) {
        return 0;
    }
    if (arg2 != 0) {
        if (arg2 == 0) {
            var_r3_2 = 0;
        } else {
            var_r3_2 = fightPokemonGetPokemonPtr(arg2);
        }
        var_r31 = var_r3_2;
    }
    if (itemParamGetMeromeroFlag(var_r28) != 0) {
        if (arg2 == 0) {
            var_r21 = 0;
        } else {
            var_r21 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if ((var_r21 != 0) && (fightOutPokemonIsJoutaiDataId(var_r21, 0xAU) != 0)) {
            fightOutPokemonInitJoutaiDataId(var_r21, 0xAU);
            if (arg2 == 0) {
                var_r3_3 = 0;
            } else {
                var_r3_3 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_3 != 0) {
                fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_3, 0x7CU);
            }
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0;
                temp_r3_3 = &arg0->e[logIndex];
                temp_r3_3->a = 0;
                temp_r3_3->b = 0;
                spA = logIndex + 1;
            }
        }
    }
    if (itemParamGetCriticalFlag(var_r28) != 0) {
        if (arg2 == 0) {
            var_r21_2 = 0;
        } else {
            var_r21_2 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if ((var_r21_2 != 0) && (fightOutPokemonCheckWriteJoutaiDataId(var_r21_2, 0xFU) == 2)) {
            fightOutPokemonWriteJoutaiDataId(var_r21_2, 0xFU, 0U);
            if (arg2 == 0) {
                var_r3_4 = 0;
            } else {
                var_r3_4 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_4 != 0) {
                fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_4, 0x7CU);
            }
            if (arg2 == 0) {
                var_r3_5 = 0;
            } else {
                var_r3_5 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_5 != 0) {
                fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_5, 0x99U);
            }
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 1;
                temp_r3_4 = &arg0->e[logIndex];
                temp_r3_4->a = 0;
                temp_r3_4->b = 0;
                spA = logIndex + 1;
            }
        }
    }
    temp_r3_5 = itemParamGetAttackUp(var_r28);
    if (temp_r3_5 != 0) {
        if (arg2 == 0) {
            var_r19 = 0;
        } else {
            var_r19 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r19 == 0) {
            var_r0 = 0;
        } else {
            temp_r3_6 = pokemonGetStatus(var_r19, 0U, 0xE6U, 0U);
            if (temp_r3_6 >= 0xCU) {
                var_r0 = 0;
            } else {
                var_r21_3 = temp_r3_6 + temp_r3_5;
                if (var_r21_3 > 0xCU) {
                    var_r21_3 = 0xC;
                }
                pokemonSetStatus(var_r19, 0U, 0xE6U, 0U, (u32) var_r21_3);
                if (arg2 == 0) {
                    var_r3_6 = 0;
                } else {
                    var_r3_6 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_6 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_6, 0x99U);
                }
                var_r0 = var_r21_3 - temp_r3_6;
            }
        }
        if ((var_r0 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 2;
            temp_r4 = &arg0->e[logIndex];
            temp_r4->a = (s16) var_r0;
            temp_r4->b = 0;
            spA = logIndex + 1;
        }
    }
    temp_r3_7 = itemParamGetDefenceUp(var_r28);
    if (temp_r3_7 != 0) {
        if (arg2 == 0) {
            var_r19_2 = 0;
        } else {
            var_r19_2 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r19_2 == 0) {
            var_r0_2 = 0;
        } else {
            temp_r3_8 = pokemonGetStatus(var_r19_2, 0U, 0xE7U, 0U);
            if (temp_r3_8 >= 0xCU) {
                var_r0_2 = 0;
            } else {
                var_r21_4 = temp_r3_8 + temp_r3_7;
                if (var_r21_4 > 0xCU) {
                    var_r21_4 = 0xC;
                }
                pokemonSetStatus(var_r19_2, 0U, 0xE7U, 0U, (u32) var_r21_4);
                if (arg2 == 0) {
                    var_r3_7 = 0;
                } else {
                    var_r3_7 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_7 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_7, 0x99U);
                }
                var_r0_2 = var_r21_4 - temp_r3_8;
            }
        }
        if ((var_r0_2 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 3;
            temp_r4_2 = &arg0->e[logIndex];
            temp_r4_2->a = (s16) var_r0_2;
            temp_r4_2->b = 0;
            spA = logIndex + 1;
        }
    }
    temp_r3_9 = itemParamGetQuickUp(var_r28);
    if (temp_r3_9 != 0) {
        if (arg2 == 0) {
            var_r19_3 = 0;
        } else {
            var_r19_3 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r19_3 == 0) {
            var_r0_3 = 0;
        } else {
            temp_r3_10 = pokemonGetStatus(var_r19_3, 0U, 0xEAU, 0U);
            if (temp_r3_10 >= 0xCU) {
                var_r0_3 = 0;
            } else {
                var_r21_5 = temp_r3_10 + temp_r3_9;
                if (var_r21_5 > 0xCU) {
                    var_r21_5 = 0xC;
                }
                pokemonSetStatus(var_r19_3, 0U, 0xEAU, 0U, (u32) var_r21_5);
                if (arg2 == 0) {
                    var_r3_8 = 0;
                } else {
                    var_r3_8 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_8 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_8, 0x99U);
                }
                var_r0_3 = var_r21_5 - temp_r3_10;
            }
        }
        if ((var_r0_3 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 4;
            temp_r4_3 = &arg0->e[logIndex];
            temp_r4_3->a = (s16) var_r0_3;
            temp_r4_3->b = 0;
            spA = logIndex + 1;
        }
    }
    temp_r3_11 = itemParamGetHitUp(var_r28);
    if (temp_r3_11 != 0) {
        if (arg2 == 0) {
            var_r19_4 = 0;
        } else {
            var_r19_4 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r19_4 == 0) {
            var_r0_4 = 0;
        } else {
            temp_r3_12 = pokemonGetStatus(var_r19_4, 0U, 0xEBU, 0U);
            if (temp_r3_12 >= 0xCU) {
                var_r0_4 = 0;
            } else {
                var_r21_6 = temp_r3_12 + temp_r3_11;
                if (var_r21_6 > 0xCU) {
                    var_r21_6 = 0xC;
                }
                pokemonSetStatus(var_r19_4, 0U, 0xEBU, 0U, (u32) var_r21_6);
                if (arg2 == 0) {
                    var_r3_9 = 0;
                } else {
                    var_r3_9 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_9 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_9, 0x99U);
                }
                var_r0_4 = var_r21_6 - temp_r3_12;
            }
        }
        if ((var_r0_4 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 5;
            temp_r4_4 = &arg0->e[logIndex];
            temp_r4_4->a = (s16) var_r0_4;
            temp_r4_4->b = 0;
            spA = logIndex + 1;
        }
    }
    temp_r3_13 = itemParamGetSpAttackUp(var_r28);
    if (temp_r3_13 != 0) {
        if (arg2 == 0) {
            var_r19_5 = 0;
        } else {
            var_r19_5 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r19_5 == 0) {
            var_r0_5 = 0;
        } else {
            temp_r3_14 = pokemonGetStatus(var_r19_5, 0U, 0xE8U, 0U);
            if (temp_r3_14 >= 0xCU) {
                var_r0_5 = 0;
            } else {
                var_r21_7 = temp_r3_14 + temp_r3_13;
                if (var_r21_7 > 0xCU) {
                    var_r21_7 = 0xC;
                }
                pokemonSetStatus(var_r19_5, 0U, 0xE8U, 0U, (u32) var_r21_7);
                if (arg2 == 0) {
                    var_r3_10 = 0;
                } else {
                    var_r3_10 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_10 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_10, 0x99U);
                }
                var_r0_5 = var_r21_7 - temp_r3_14;
            }
        }
        if ((var_r0_5 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 6;
            temp_r4_5 = &arg0->e[logIndex];
            temp_r4_5->a = (s16) var_r0_5;
            temp_r4_5->b = 0;
            spA = logIndex + 1;
        }
    }
    if (itemParamGetGuardFlag(var_r28) != 0) {
        if (arg2 == 0) {
            var_r3_11 = 0;
        } else {
            var_r3_11 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r3_11 != 0) {
            temp_r3_15 = fightTargetGetPtrAsNowFightType(2U, var_r3_11);
            if (fightSideCheckWriteJoutaiDataId(temp_r3_15, 0x4CU) == 2) {
                fightSideWriteJoutaiDataId(temp_r3_15, 0x4CU, 0U);
                if (arg2 == 0) {
                    var_r3_12 = 0;
                } else {
                    var_r3_12 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_12 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_12, 0x99U);
                }
                if ((logIndex = spA) < 0x20) {
                    arg0->e[logIndex].key = 7;
                    temp_r4_6 = &arg0->e[logIndex];
                    temp_r4_6->a = 5;
                    temp_r4_6->b = 0;
                    spA = logIndex + 1;
                }
            }
        }
    }
    if (itemParamGetLevelUpFlag(var_r28) != 0) {
        if (pokemonIsDarkPokemon(var_r31) != 0) {
            var_r0_6 = 0;
        } else {
            temp_r3_16 = pokemonBiosGetLevel(var_r31);
            if (temp_r3_16 >= 0x64U) {
                var_r0_6 = 0;
            } else {
                temp_r21 = pokemonBiosGetMaxHp(var_r31);
                pokemonBiosSetExp(var_r31, pokemonGrowDataBiosGetExp(pokemonGrowDataBiosGetPtr(pokemonDataBiosGetGrowDataId(pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(var_r31)))), (u8) (temp_r3_16 + 1)));
                pokemonResetBasisStatus(var_r31);
                temp_r3_17 = pokemonBiosGetMaxHp(var_r31);
                if ((logIndex = spA) < 0x20) {
                    arg0->e[logIndex].key = 8;
                    temp_r4_7 = &arg0->e[logIndex];
                    temp_r4_7->a = 0;
                    temp_r4_7->b = 0;
                    spA = logIndex + 1;
                }
                var_r0_6 = temp_r3_17 - temp_r21;
            }
        }
        var_r25 = var_r0_6;
    }
    if (itemParamGetSleepFlag(var_r28) != 0) {
        var_r21_8 = 0;
        if (pokemonIsJoutaiDataId(var_r31, 8U) != 0) {
            pokemonInitJoutaiDataId(var_r31, 8U);
            if (arg2 == 0) {
                var_r3_13 = 0;
            } else {
                var_r3_13 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_13 != 0) {
                fightOutPokemonInitJoutaiDataId(var_r3_13, 0x17U);
                var_r21_8 = 1;
            }
            if (arg2 == 0) {
                var_r3_14 = 0;
            } else {
                var_r3_14 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_14 != 0) {
                fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_14, 0x7CU);
            }
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 9;
                temp_r3_18 = &arg0->e[logIndex];
                temp_r3_18->a = 0;
                temp_r3_18->b = 0;
                spA = logIndex + 1;
            }
            if ((var_r21_8 != 0) && ((logIndex = spA) < 0x20)) {
                arg0->e[logIndex].key = 0xA;
                temp_r3_19 = &arg0->e[logIndex];
                temp_r3_19->a = 0;
                temp_r3_19->b = 0;
                spA = logIndex + 1;
            }
        }
    }
    if (itemParamGetPoisonFlag(var_r28) != 0) {
        var_r22 = 0;
        var_r21_9 = 0;
        if (pokemonIsJoutaiDataId(var_r31, 3U) != 0) {
            pokemonInitJoutaiDataId(var_r31, 3U);
            var_r22 = 1;
        }
        if (pokemonIsJoutaiDataId(var_r31, 4U) != 0) {
            pokemonInitJoutaiDataId(var_r31, 4U);
            var_r21_9 = 1;
        }
        if (arg2 == 0) {
            var_r3_15 = 0;
        } else {
            var_r3_15 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r3_15 != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_15, 0x7CU);
        }
        if ((var_r22 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 0xB;
            temp_r3_20 = &arg0->e[logIndex];
            temp_r3_20->a = 0;
            temp_r3_20->b = 0;
            spA = logIndex + 1;
        }
        if ((var_r21_9 != 0) && ((logIndex = spA) < 0x20)) {
            arg0->e[logIndex].key = 0xC;
            temp_r3_21 = &arg0->e[logIndex];
            temp_r3_21->a = 0;
            temp_r3_21->b = 0;
            spA = logIndex + 1;
        }
    }
    if ((itemParamGetBurnFlag(var_r28) != 0) && (pokemonIsJoutaiDataId(var_r31, 6U) != 0)) {
        pokemonInitJoutaiDataId(var_r31, 6U);
        if (arg2 == 0) {
            var_r3_16 = 0;
        } else {
            var_r3_16 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r3_16 != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_16, 0x7CU);
        }
        if ((logIndex = spA) < 0x20) {
            arg0->e[logIndex].key = 0xE;
            temp_r3_22 = &arg0->e[logIndex];
            temp_r3_22->a = 0;
            temp_r3_22->b = 0;
            spA = logIndex + 1;
        }
    }
    if ((itemParamGetFreezeFlag(var_r28) != 0) && (pokemonIsJoutaiDataId(var_r31, 7U) != 0)) {
        pokemonInitJoutaiDataId(var_r31, 7U);
        if (arg2 == 0) {
            var_r3_17 = 0;
        } else {
            var_r3_17 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r3_17 != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_17, 0x7CU);
        }
        if ((logIndex = spA) < 0x20) {
            arg0->e[logIndex].key = 0xF;
            temp_r3_23 = &arg0->e[logIndex];
            temp_r3_23->a = 0;
            temp_r3_23->b = 0;
            spA = logIndex + 1;
        }
    }
    if ((itemParamGetParalyzeFlag(var_r28) != 0) && (pokemonIsJoutaiDataId(var_r31, 5U) != 0)) {
        pokemonInitJoutaiDataId(var_r31, 5U);
        if (arg2 == 0) {
            var_r3_18 = 0;
        } else {
            var_r3_18 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if (var_r3_18 != 0) {
            fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_18, 0x7CU);
        }
        if ((logIndex = spA) < 0x20) {
            arg0->e[logIndex].key = 0x10;
            temp_r3_24 = &arg0->e[logIndex];
            temp_r3_24->a = 0;
            temp_r3_24->b = 0;
            spA = logIndex + 1;
        }
    }
    if (itemParamGetConfuseFlag(var_r28) != 0) {
        if (arg2 == 0) {
            var_r21_10 = 0;
        } else {
            var_r21_10 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
        }
        if ((var_r21_10 != 0) && (fightOutPokemonIsJoutaiDataId(var_r21_10, 9U) != 0)) {
            fightOutPokemonInitJoutaiDataId(var_r21_10, 9U);
            if (arg2 == 0) {
                var_r3_19 = 0;
            } else {
                var_r3_19 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
            }
            if (var_r3_19 != 0) {
                fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_19, 0x7CU);
            }
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x11;
                temp_r3_25 = &arg0->e[logIndex];
                temp_r3_25->a = 0;
                temp_r3_25->b = 0;
                spA = logIndex + 1;
            }
        }
    }
    if (itemParamGetPPMaxUpFlag(var_r28) != 0) {
        temp_r3_26 = pokemonBiosGetPokemonWazaDataId(var_r31, arg4);
        if ((temp_r3_26 != 0x176) && (wazaCheckDarkWaza(temp_r3_26) == 0) && (pokemonWazaCheckValid(var_r31, arg4) != 0) && (wazaDB_GetPp(temp_r3_26) >= 5U)) {
            temp_r3_27 = pokemonBiosGetPokemonWazaPpCount(var_r31, arg4);
            if (temp_r3_27 < 3U) {
                temp_r21_2 = pokemonWazaGetMaxPP(var_r31, arg4);
                pokemonBiosSetPokemonWazaPpCount(var_r31, arg4, (u8) (temp_r3_27 + 1));
                temp_r21_3 = pokemonWazaGetMaxPP(var_r31, arg4) - temp_r21_2;
                pokemonBiosSetPokemonWazaPp(var_r31, arg4, pokemonBiosGetPokemonWazaPp(var_r31, arg4) + temp_r21_3);
                if ((logIndex = spA) < 0x20) {
                    arg0->e[logIndex].key = 0x12;
                    temp_r4_8 = &arg0->e[logIndex];
                    temp_r4_8->a = (s16) temp_r21_3;
                    temp_r4_8->b = (s16) arg4;
                    spA = logIndex + 1;
                }
            }
        }
    }
    temp_r3_28 = itemParamGetHPEffortUp(var_r28);
    if (temp_r3_28 != 0) {
        if (pokemonBiosGetPokemonDataId(var_r31) == 0x12F) {
            var_r0_7 = 1;
        } else {
            temp_r21_4 = pokemonBiosGetMaxHpEffort(var_r31);
            temp_r19 = temp_r21_4 + pokemonBiosGetPhyAtkEffort(var_r31);
            temp_r19_2 = temp_r19 + pokemonBiosGetPhyDefEffort(var_r31);
            temp_r19_3 = temp_r19_2 + pokemonBiosGetSpeAtkEffort(var_r31);
            temp_r19_4 = temp_r19_3 + pokemonBiosGetSpeDefEffort(var_r31);
            temp_r19_5 = temp_r19_4 + pokemonBiosGetNimblenessEffort(var_r31);
            if (temp_r19_5 >= 0x1FEU) {
                var_r5 = -1;
            } else {
                temp_r3_29 = pokemonGetStatus(var_r31, 0U, 0x8DU, 0U);
                if (temp_r3_29 >= 0x64U) {
                    var_r5 = 0;
                } else {
                    var_r21_11 = temp_r3_29 + temp_r3_28;
                    if (var_r21_11 > 0x64U) {
                        var_r21_11 = 0x64;
                    }
                    temp_r0 = (u16) (temp_r19_5 - temp_r3_29) + var_r21_11;
                    if (temp_r0 > 0x1FEU) {
                        var_r21_11 -= temp_r0 - 0x1FE;
                    }
                    pokemonSetStatus(var_r31, 0U, 0x8DU, 0U, (u32) var_r21_11);
                    pokemonResetBasisStatus(var_r31);
                    if (arg2 == 0) {
                        var_r3_20 = 0;
                    } else {
                        var_r3_20 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                    }
                    if (var_r3_20 != 0) {
                        fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_20, 0x8DU);
                    }
                    var_r5 = (s16) (u16) (var_r21_11 - temp_r3_29);
                }
            }
            if (var_r5 < 0) {
                var_r0_7 = 0;
            } else if (var_r5 == 0) {
                var_r0_7 = 1;
            } else {
                if ((logIndex = spA) < 0x20) {
                    arg0->e[logIndex].key = 0x13;
                    temp_r4_9 = &arg0->e[logIndex];
                    temp_r4_9->a = var_r5;
                    temp_r4_9->b = 0;
                    spA = logIndex + 1;
                }
                var_r0_7 = 1;
            }
        }
        if (var_r0_7 == 0) {
            return 0;
        }
        goto block_270;
    }
block_270:
    temp_r3_30 = itemParamGetAttackEffortUp(var_r28);
    if (temp_r3_30 != 0) {
        temp_r21_5 = pokemonBiosGetMaxHpEffort(var_r31);
        temp_r19_6 = temp_r21_5 + pokemonBiosGetPhyAtkEffort(var_r31);
        temp_r19_7 = temp_r19_6 + pokemonBiosGetPhyDefEffort(var_r31);
        temp_r19_8 = temp_r19_7 + pokemonBiosGetSpeAtkEffort(var_r31);
        temp_r19_9 = temp_r19_8 + pokemonBiosGetSpeDefEffort(var_r31);
        temp_r19_10 = temp_r19_9 + pokemonBiosGetNimblenessEffort(var_r31);
        if (temp_r19_10 >= 0x1FEU) {
            var_r5_2 = -1;
        } else {
            temp_r3_31 = pokemonGetStatus(var_r31, 0U, 0x8EU, 0U);
            if (temp_r3_31 >= 0x64U) {
                var_r5_2 = 0;
            } else {
                var_r21_12 = temp_r3_31 + temp_r3_30;
                if (var_r21_12 > 0x64U) {
                    var_r21_12 = 0x64;
                }
                temp_r0_2 = (u16) (temp_r19_10 - temp_r3_31) + var_r21_12;
                if (temp_r0_2 > 0x1FEU) {
                    var_r21_12 -= temp_r0_2 - 0x1FE;
                }
                pokemonSetStatus(var_r31, 0U, 0x8EU, 0U, (u32) var_r21_12);
                pokemonResetBasisStatus(var_r31);
                if (arg2 == 0) {
                    var_r3_21 = 0;
                } else {
                    var_r3_21 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_21 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_21, 0x8EU);
                }
                var_r5_2 = (s16) (u16) (var_r21_12 - temp_r3_31);
            }
        }
        if (var_r5_2 < 0) {
            var_r0_8 = 0;
        } else if (var_r5_2 == 0) {
            var_r0_8 = 1;
        } else {
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x14;
                temp_r4_10 = &arg0->e[logIndex];
                temp_r4_10->a = var_r5_2;
                temp_r4_10->b = 0;
                spA = logIndex + 1;
            }
            var_r0_8 = 1;
        }
        if (var_r0_8 == 0) {
            return 0;
        }
        goto block_294;
    }
block_294:
    temp_r3_32 = itemParamGetHPUp(var_r28);
    if (temp_r3_32 != 0) {
        hpRecover__FP20ITEMUSE2POKEMON_LOG1PsP7PokemonUcbUsP12FightPokemon(arg0, &spA, var_r31, temp_r3_32, itemParamGetReviveFlag(var_r28), var_r25, arg2);
    }
    temp_r3_33 = itemParamGetPPUp(var_r28);
    if (temp_r3_33 != 0) {
        var_r25_2 = 0xFF;
        if (itemParamGetPPSelectFlag(var_r28) != 0) {
            var_r25_2 = arg4;
        }
        var_r23 = var_r31;
        if ((pokemonIsJoutaiDataId(var_r31, 0x10U) != 0) || (pokemonIsJoutaiDataId(var_r31, 0x31U) != 0)) {
            var_r23 = fightPokemonBiosGetMotoPokemonPtr(arg2);
        }
        if (var_r25_2 != 0xFF) {
            temp_r3_34 = pokemonBiosGetPokemonWazaDataId(var_r23, var_r25_2);
            if (temp_r3_34 == 0x176) {
                var_r0_9 = 0;
            } else if (wazaCheckDarkWaza(temp_r3_34) != 0) {
                var_r0_9 = 0;
            } else {
                temp_r20 = pokemonWazaGetMaxPP(var_r23, var_r25_2);
                temp_r3_35 = pokemonBiosGetPokemonWazaPp(var_r23, var_r25_2);
                if (temp_r3_35 >= temp_r20) {
                    var_r0_9 = 0;
                } else {
                    var_r24 = temp_r3_35 + temp_r3_33;
                    if (var_r24 > temp_r20) {
                        var_r24 = temp_r20;
                    }
                    pokemonBiosSetPokemonWazaPp(var_r23, var_r25_2, var_r24);
                    var_r0_9 = var_r24 - temp_r3_35;
                }
            }
            if ((var_r0_9 != 0) && ((logIndex = spA) < 0x20)) {
                arg0->e[logIndex].key = 0x17;
                temp_r4_11 = &arg0->e[logIndex];
                temp_r4_11->a = (s16) var_r0_9;
                temp_r4_11->b = (s16) var_r25_2;
                spA = logIndex + 1;
            }
        } else {
            var_r24_2 = 0;
loop_329:
            if (var_r24_2 < 4U) {
                temp_r3_36 = pokemonBiosGetPokemonWazaDataId(var_r23, var_r24_2);
                if (temp_r3_36 == 0x176) {
                    var_r0_10 = 0;
                } else if (wazaCheckDarkWaza(temp_r3_36) != 0) {
                    var_r0_10 = 0;
                } else {
                    temp_r19_11 = pokemonWazaGetMaxPP(var_r23, var_r24_2);
                    temp_r3_37 = pokemonBiosGetPokemonWazaPp(var_r23, var_r24_2);
                    if (temp_r3_37 >= temp_r19_11) {
                        var_r0_10 = 0;
                    } else {
                        var_r20 = temp_r3_37 + temp_r3_33;
                        if (var_r20 > temp_r19_11) {
                            var_r20 = temp_r19_11;
                        }
                        pokemonBiosSetPokemonWazaPp(var_r23, var_r24_2, var_r20);
                        var_r0_10 = var_r20 - temp_r3_37;
                    }
                }
                if ((var_r0_10 != 0) && ((logIndex = spA) < 0x20)) {
                    temp_r5 = &arg0->e[logIndex];
                    temp_r5->key = 0x17;
                    temp_r5->a = (s16) var_r0_10;
                    temp_r5->b = (s16) var_r24_2;
                    spA = logIndex + 1;
                }
                var_r24_2 += 1;
                goto loop_329;
            }
        }
    }
    if ((itemParamGetEvolutionFlag(var_r28) != 0) && (pokemonIsDarkPokemon(var_r31) == 0) && ((temp_r3_38 = pokemonEvolutionCheck(var_r31, 1, arg3, &sp8, &spC), ((temp_r3_38 == 0) == 0)) || (sp8 != 0)) && ((logIndex = spA) < 0x20)) {
        arg0->e[logIndex].key = 0x18;
        temp_r3_39 = &arg0->e[logIndex];
        temp_r3_39->a = (s16) temp_r3_38;
        temp_r3_39->b = (s16) sp8;
        spA = logIndex + 1;
    }
    temp_r3_40 = itemParamGetDefenceEffortUp(var_r28);
    if (temp_r3_40 != 0) {
        temp_r22 = pokemonBiosGetMaxHpEffort(var_r31);
        temp_r21_6 = temp_r22 + pokemonBiosGetPhyAtkEffort(var_r31);
        temp_r21_7 = temp_r21_6 + pokemonBiosGetPhyDefEffort(var_r31);
        temp_r21_8 = temp_r21_7 + pokemonBiosGetSpeAtkEffort(var_r31);
        temp_r21_9 = temp_r21_8 + pokemonBiosGetSpeDefEffort(var_r31);
        temp_r21_10 = temp_r21_9 + pokemonBiosGetNimblenessEffort(var_r31);
        if (temp_r21_10 >= 0x1FEU) {
            var_r5_3 = -1;
        } else {
            temp_r3_41 = pokemonGetStatus(var_r31, 0U, 0x8FU, 0U);
            if (temp_r3_41 >= 0x64U) {
                var_r5_3 = 0;
            } else {
                var_r19_6 = temp_r3_41 + temp_r3_40;
                if (var_r19_6 > 0x64U) {
                    var_r19_6 = 0x64;
                }
                temp_r0_3 = (u16) (temp_r21_10 - temp_r3_41) + var_r19_6;
                if (temp_r0_3 > 0x1FEU) {
                    var_r19_6 -= temp_r0_3 - 0x1FE;
                }
                pokemonSetStatus(var_r31, 0U, 0x8FU, 0U, (u32) var_r19_6);
                pokemonResetBasisStatus(var_r31);
                if (arg2 == 0) {
                    var_r3_22 = 0;
                } else {
                    var_r3_22 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_22 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_22, 0x8FU);
                }
                var_r5_3 = (s16) (u16) (var_r19_6 - temp_r3_41);
            }
        }
        if (var_r5_3 < 0) {
            var_r0_11 = 0;
        } else if (var_r5_3 == 0) {
            var_r0_11 = 1;
        } else {
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x19;
                temp_r4_12 = &arg0->e[logIndex];
                temp_r4_12->a = var_r5_3;
                temp_r4_12->b = 0;
                spA = logIndex + 1;
            }
            var_r0_11 = 1;
        }
        if (var_r0_11 == 0) {
            return 0;
        }
        goto block_360;
    }
block_360:
    temp_r3_42 = itemParamGetQuickEffortUp(var_r28);
    if (temp_r3_42 != 0) {
        temp_r22_2 = pokemonBiosGetMaxHpEffort(var_r31);
        temp_r21_11 = temp_r22_2 + pokemonBiosGetPhyAtkEffort(var_r31);
        temp_r21_12 = temp_r21_11 + pokemonBiosGetPhyDefEffort(var_r31);
        temp_r21_13 = temp_r21_12 + pokemonBiosGetSpeAtkEffort(var_r31);
        temp_r21_14 = temp_r21_13 + pokemonBiosGetSpeDefEffort(var_r31);
        temp_r21_15 = temp_r21_14 + pokemonBiosGetNimblenessEffort(var_r31);
        if (temp_r21_15 >= 0x1FEU) {
            var_r5_4 = -1;
        } else {
            temp_r3_43 = pokemonGetStatus(var_r31, 0U, 0x92U, 0U);
            if (temp_r3_43 >= 0x64U) {
                var_r5_4 = 0;
            } else {
                var_r19_7 = temp_r3_43 + temp_r3_42;
                if (var_r19_7 > 0x64U) {
                    var_r19_7 = 0x64;
                }
                temp_r0_4 = (u16) (temp_r21_15 - temp_r3_43) + var_r19_7;
                if (temp_r0_4 > 0x1FEU) {
                    var_r19_7 -= temp_r0_4 - 0x1FE;
                }
                pokemonSetStatus(var_r31, 0U, 0x92U, 0U, (u32) var_r19_7);
                pokemonResetBasisStatus(var_r31);
                if (arg2 == 0) {
                    var_r3_23 = 0;
                } else {
                    var_r3_23 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_23 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_23, 0x92U);
                }
                var_r5_4 = (s16) (u16) (var_r19_7 - temp_r3_43);
            }
        }
        if (var_r5_4 < 0) {
            var_r0_12 = 0;
        } else if (var_r5_4 == 0) {
            var_r0_12 = 1;
        } else {
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x1A;
                temp_r4_13 = &arg0->e[logIndex];
                temp_r4_13->a = var_r5_4;
                temp_r4_13->b = 0;
                spA = logIndex + 1;
            }
            var_r0_12 = 1;
        }
        if (var_r0_12 == 0) {
            return 0;
        }
        goto block_384;
    }
block_384:
    temp_r3_44 = itemParamGetSpDefenceEffortUp(var_r28);
    if (temp_r3_44 != 0) {
        temp_r22_3 = pokemonBiosGetMaxHpEffort(var_r31);
        temp_r21_16 = temp_r22_3 + pokemonBiosGetPhyAtkEffort(var_r31);
        temp_r21_17 = temp_r21_16 + pokemonBiosGetPhyDefEffort(var_r31);
        temp_r21_18 = temp_r21_17 + pokemonBiosGetSpeAtkEffort(var_r31);
        temp_r21_19 = temp_r21_18 + pokemonBiosGetSpeDefEffort(var_r31);
        temp_r21_20 = temp_r21_19 + pokemonBiosGetNimblenessEffort(var_r31);
        if (temp_r21_20 >= 0x1FEU) {
            var_r5_5 = -1;
        } else {
            temp_r3_45 = pokemonGetStatus(var_r31, 0U, 0x91U, 0U);
            if (temp_r3_45 >= 0x64U) {
                var_r5_5 = 0;
            } else {
                var_r19_8 = temp_r3_45 + temp_r3_44;
                if (var_r19_8 > 0x64U) {
                    var_r19_8 = 0x64;
                }
                temp_r0_5 = (u16) (temp_r21_20 - temp_r3_45) + var_r19_8;
                if (temp_r0_5 > 0x1FEU) {
                    var_r19_8 -= temp_r0_5 - 0x1FE;
                }
                pokemonSetStatus(var_r31, 0U, 0x91U, 0U, (u32) var_r19_8);
                pokemonResetBasisStatus(var_r31);
                if (arg2 == 0) {
                    var_r3_24 = 0;
                } else {
                    var_r3_24 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_24 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_24, 0x91U);
                }
                var_r5_5 = (s16) (u16) (var_r19_8 - temp_r3_45);
            }
        }
        if (var_r5_5 < 0) {
            var_r0_13 = 0;
        } else if (var_r5_5 == 0) {
            var_r0_13 = 1;
        } else {
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x1B;
                temp_r4_14 = &arg0->e[logIndex];
                temp_r4_14->a = var_r5_5;
                temp_r4_14->b = 0;
                spA = logIndex + 1;
            }
            var_r0_13 = 1;
        }
        if (var_r0_13 == 0) {
            return 0;
        }
        goto block_408;
    }
block_408:
    temp_r3_46 = itemParamGetSpAttackEffortUp(var_r28);
    if (temp_r3_46 != 0) {
        temp_r22_4 = pokemonBiosGetMaxHpEffort(var_r31);
        temp_r21_21 = temp_r22_4 + pokemonBiosGetPhyAtkEffort(var_r31);
        temp_r21_22 = temp_r21_21 + pokemonBiosGetPhyDefEffort(var_r31);
        temp_r21_23 = temp_r21_22 + pokemonBiosGetSpeAtkEffort(var_r31);
        temp_r21_24 = temp_r21_23 + pokemonBiosGetSpeDefEffort(var_r31);
        temp_r21_25 = temp_r21_24 + pokemonBiosGetNimblenessEffort(var_r31);
        if (temp_r21_25 >= 0x1FEU) {
            var_r5_6 = -1;
        } else {
            temp_r3_47 = pokemonGetStatus(var_r31, 0U, 0x90U, 0U);
            if (temp_r3_47 >= 0x64U) {
                var_r5_6 = 0;
            } else {
                var_r19_9 = temp_r3_47 + temp_r3_46;
                if (var_r19_9 > 0x64U) {
                    var_r19_9 = 0x64;
                }
                temp_r0_6 = (u16) (temp_r21_25 - temp_r3_47) + var_r19_9;
                if (temp_r0_6 > 0x1FEU) {
                    var_r19_9 -= temp_r0_6 - 0x1FE;
                }
                pokemonSetStatus(var_r31, 0U, 0x90U, 0U, (u32) var_r19_9);
                pokemonResetBasisStatus(var_r31);
                if (arg2 == 0) {
                    var_r3_25 = 0;
                } else {
                    var_r3_25 = fightTrainerCheckFightPokemonFightOut(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, arg2), arg2);
                }
                if (var_r3_25 != 0) {
                    fightSeqCheckSetMotoPokemonToHensinBuff(var_r3_25, 0x90U);
                }
                var_r5_6 = (s16) (u16) (var_r19_9 - temp_r3_47);
            }
        }
        if (var_r5_6 < 0) {
            var_r0_14 = 0;
        } else if (var_r5_6 == 0) {
            var_r0_14 = 1;
        } else {
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x1C;
                temp_r4_15 = &arg0->e[logIndex];
                temp_r4_15->a = var_r5_6;
                temp_r4_15->b = 0;
                spA = logIndex + 1;
            }
            var_r0_14 = 1;
        }
        if (var_r0_14 == 0) {
            return 0;
        }
        goto block_432;
    }
block_432:
    if (itemParamGetPPMaxFullFlag(var_r28) != 0) {
        temp_r3_48 = pokemonBiosGetPokemonWazaDataId(var_r31, arg4);
        if ((temp_r3_48 != 0x176) && (wazaCheckDarkWaza(temp_r3_48) == 0) && (wazaDB_GetPp(temp_r3_48) >= 5U) && (pokemonBiosGetPokemonWazaPpCount(var_r31, arg4) < 3U)) {
            temp_r22_5 = pokemonWazaGetMaxPP(var_r31, arg4);
            pokemonBiosSetPokemonWazaPpCount(var_r31, arg4, 3U);
            temp_r0_7 = pokemonWazaGetMaxPP(var_r31, arg4) - temp_r22_5;
            if (temp_r0_7 != 0) {
                pokemonBiosSetPokemonWazaPp(var_r31, arg4, pokemonBiosGetPokemonWazaPp(var_r31, arg4) + temp_r0_7);
            }
            if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x1D;
                temp_r4_16 = &arg0->e[logIndex];
                temp_r4_16->a = (s16) temp_r0_7;
                temp_r4_16->b = (s16) arg4;
                spA = logIndex + 1;
            }
        }
    }
    var_r19_10 = 0;
    temp_r3_49 = itemParamGetFriend1Up(var_r28);
    if (temp_r3_49 != 0) {
        if (spA <= 0) {
            var_r3_26 = 0;
        } else {
            var_r3_26 = friendXUp__FP7PokemonP12FightPokemonScUsUs(var_r31, arg2, temp_r3_49, 0U, 0x64U);
            if (var_r3_26 == 0) {
                var_r3_26 = 0;
            } else if ((logIndex = spA) < 0x20) {
                arg0->e[logIndex].key = 0x1E;
                temp_r5_2 = &arg0->e[logIndex];
                temp_r5_2->a = var_r3_26;
                temp_r5_2->b = 0;
                spA = logIndex + 1;
            }
        }
        var_r19_10 = var_r3_26;
    }
    if (var_r19_10 == 0) {
        temp_r3_50 = itemParamGetFriend2Up(var_r28);
        if (temp_r3_50 != 0) {
            if (spA <= 0) {
                var_r3_27 = 0;
            } else {
                var_r3_27 = friendXUp__FP7PokemonP12FightPokemonScUsUs(var_r31, arg2, temp_r3_50, 0x64U, 0xC8U);
                if (var_r3_27 == 0) {
                    var_r3_27 = 0;
                } else if ((logIndex = spA) < 0x20) {
                    arg0->e[logIndex].key = 0x1E;
                    temp_r5_3 = &arg0->e[logIndex];
                    temp_r5_3->a = var_r3_27;
                    temp_r5_3->b = 0;
                    spA = logIndex + 1;
                }
            }
            var_r19_10 = var_r3_27;
        }
    }
    if (var_r19_10 == 0) {
        temp_r3_51 = itemParamGetFriend3Up(var_r28);
        if ((temp_r3_51 != 0) && (spA > 0)) {
            temp_r3_52 = friendXUp__FP7PokemonP12FightPokemonScUsUs(var_r31, arg2, temp_r3_51, 0xC8U, 0xFFFFU);
            if ((temp_r3_52 != 0) && ((logIndex = spA) < 0x20)) {
                arg0->e[logIndex].key = 0x1E;
                temp_r5_4 = &arg0->e[logIndex];
                temp_r5_4->a = temp_r3_52;
                temp_r5_4->b = 0;
                spA = logIndex + 1;
            }
        }
    }
    return spA;
}
}
