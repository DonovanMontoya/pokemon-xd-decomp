#include <global.h>
extern "C" f64 sqrt(f64);
extern "C" {
extern s8 ActionSeqNo,WildPokemonCatchFlag;extern u8 ServerWork[8];extern u32 GetFailMsgTbl[5],GetYaseiFailMsgTbl[5];extern u8 ITEM_MonsGetFail[],ITEM_MonsGetSuccess[];
const u16 *GSmsgGetGSchar(u32);u32 GSthreadGetCurrentThread();u16 HSD_Rand();u8 darkPokemonBiosGetHokakuritu(u16);u8 darkPokemonBiosGetSnatchSuccessFlag(u16);u8 darkPokemonBiosGetLevel(u16);void *darkPokemonGetDarkPokemon(u16);
void *fightFloorGetFightOutPokemonPtrToFightTrainerPtr(void*,void*);void *fightFloorGetFightOutPokemonPtrToHeroPtr(void*,void*);s32 fightFloorGetFightPokemonEntryCntInc(void*);u32 fightFloor_GetEncountDataId(void*);u32 fightFloor_GetEncountFloorId();u8 fightFloor_GetFightKind(void*);u8 fightFloor_GetFightKindBossFlag(void*);u8 fightFloor_GetFightKindDoZukanTukamaetaFlag(void*);u8 fightFloor_GetFightKindGetFriendFlag(void*);u8 fightFloor_GetFightType(void*);u8 fightFloor_GetFightTypeEntryPokemonNum(void*);s32 fightFloor_GetStockPokemonNum(void*);u8 fightFloor_GetTikeiDataId(void*);u8 fightFloor_GetTrainer(void*);u32 fightFloor_GetTurnCount(void*);
void fightFloor_SetStockPokemonBallID(void*,s32,u8);void fightFloor_SetStockPokemonNum(void*,u8);void fightFloor_SetStockPokemonPtr(void*,s32,void*);u32 fightItem_GetCount(void*);u16 fightItem_GetItemDataId(void*);
void fightMainAllCamera(s32,s32);void fightMenuCloseMsg();u32 fightMenuGetFightOutPokemonPtrToStatusMenuId(void*,u32,s32);void fightMenuOpenMsg(u32);void fightMsgctrlSetValue(u32,u32);
const u16 *fightOutPokemonGetNicknamePtr(void*);void *fightOutPokemonGetPokemonPtr(void*);void fightOutPokemonHokakuEffect(void*,u8,u32,u8,u8*);u8 fightOutPokemonIsJoutaiDataId(void*,u16);u8 fightOutPokemonIsZokuseiDataId(void*,u16);void *fightOutPokemon_GetFightItemPtr(void*);void *fightOutPokemon_GetFightPokemonPtr(void*);void *fightOutPokemon_GetMotoFightPokemonPtr(void*);
void fightPokemonCreate(void*,void*,void*,s32);void fightPokemonGetFriendFormPokemonFriendFilterId(void*,s32);void *fightPokemonGetPokemonPtr(void*);void fightPokemon_SetCatchEntryFlag(void*,u8);void fightPokemon_SetHokakuFlag(void*,u8);void fightSeqCheckSetHensinBuffToMotoFightPokemon(void*,u16);void fightSeqKizetuInit(void*);void fightSeqOpenMsg(u32);u8 *fightSeq_GetWazaSeq();void fightSeq_JumpWazaSeq(const u8*);void fightSeq_NextWazaSeq(u32);
void *fightTargetGetPtrAsNowFightType(u32,s32);void fightTrainerHokakuThrowEffect(void*,u32,u8);u8 fightTrainerIsGcHero(void*);void *fightTrainerSearchInvalidFightPokemonPtr(void*,u8);void fightTrainer_SetNigeruCount(void*,u32);u8 figthOutPokemonGetLevel(void*);
void *getDeckDarkPokemonObj__15DeckDarkPokemonFUl(u32);u8 getRevers__15DeckDarkPokemonCFv(void*);s32 heroCatchPokemon(void*,void*,u32,u32,u8);void *heroGetStatus(void*,u16,u16);s32 itemDB_GetBuff(u16);u32 itemDB_GetName(u16);void menuCloseCustom(u32,u32,s32);void menuNameEntryOpen(u32,void*);s8 menuSubOpenYesNoField();u8 pokemonCheckValid(void*);u8 pokemonDB_GetGet(u32);u32 pokemonDB_GetTukamaetaFlag(u32);
u32 pokemonGetLevelToExp(void*,u8);u8 pokemonIsDarkPokemon(void*);u8 pokemonIsJoutaiDataId(void*,u16);void pokemonResetBasisStatus(void*);void pokemonSetCountAsJoutaiDataId(void*,u16,u32);void pokemonSetOnDarkPokemonFlag(void*,u8);void pokemonSetOnZukanFlag(void*,u8);u16 pokemon_GetDarkpokemonDataId(void*);u16 pokemon_GetHp(void*);u16 pokemon_GetMaxHp(void*);const u16 *pokemon_GetNicknamePtr(void*);u32 pokemon_GetPokemonDataId(void*);void pokemon_SetExp(void*,u32);void pokemon_SetFightTrainerPokemonDataId(void*,u16);void pokemon_SetHp(void*,u16);void pokemon_SetLevel(void*,u8);void setPlace__11DarkPokemonF16darkPokemonWhereUc(void*,s32,u8);void setReversPattern__11DarkPokemonFUc(void*,u8);void soundOpenPlayME(u32,u32,u32);void winMsgOpenField(u32,s32,s32);
u8 fightSeqItemSeq_AddPoke__FP7PokemonUcP13FIGHT_TRAINERP4Hero(void*,u8,void*,void*);
void WS_GETEND(void) {
    ActionSeqNo = 1;
}

void WS_ITEMEND(void) {
    ActionSeqNo = 1;
}

void WS_ITEM_CONDITION_RECOVER(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_ITEM_HP_KAIFUKU(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_NICKNAME(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}

void WS_ZUKAN(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(1);
}

void WS_ZUKAN_CHECK(void) {
    fightSeq_GetWazaSeq();
    fightSeq_NextWazaSeq(5);
}

void WS_ADD_POKE(void) {
    void *temp_r23;
    void *temp_r24;
    void *temp_r26;
    void *temp_r27;
    void *temp_r28;
    void *temp_r28_2;
    s32 temp_r3;
    u8 temp_r23_2;
    u8 temp_r25;
    u8 temp_r29;
    u8 var_r31;
    u8 *temp_r30;

    var_r31 = 0;
    temp_r29 = fightFloor_GetFightType(0);
    temp_r30 = fightSeq_GetWazaSeq();
    temp_r28 = fightTargetGetPtrAsNowFightType(0x11, 0);
    void *item=fightOutPokemon_GetFightItemPtr(temp_r28);
    u16 itemId=fightItem_GetItemDataId(item);
    temp_r25 = itemDB_GetBuff(itemId);
    temp_r27 = fightTargetGetPtrAsNowFightType(0x12, 0);
    void *original=fightOutPokemon_GetMotoFightPokemonPtr(temp_r27);
    temp_r26 = fightPokemonGetPokemonPtr(original);
    temp_r24 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, temp_r27);
    temp_r28_2 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, temp_r28);
    temp_r23 = fightFloorGetFightOutPokemonPtrToHeroPtr(0, temp_r28);
    if (fightFloor_GetFightKind(0) == 0xC) {
        var_r31 = fightSeqItemSeq_AddPoke__FP7PokemonUcP13FIGHT_TRAINERP4Hero(temp_r26, temp_r25, temp_r28_2, temp_r23);
    } else if (pokemonIsDarkPokemon(temp_r26) == 1) {
        temp_r3 = fightFloor_GetStockPokemonNum(0);
        fightFloor_SetStockPokemonBallID(0, temp_r3, temp_r25);
        fightFloor_SetStockPokemonPtr(0, temp_r3, temp_r26);
        fightFloor_SetStockPokemonNum(0, (u8) (temp_r3 + 1));
        temp_r23_2 = fightMenuGetFightOutPokemonPtrToStatusMenuId(temp_r27, temp_r29, 0);
        if (GSthreadGetCurrentThread() != 0U) {
            menuCloseCustom(temp_r23_2, 2, 1);
        } else {
            menuCloseCustom(temp_r23_2, 2, 0);
        }
    }
    pokemon_SetHp(temp_r26, 0U);
    pokemon_SetHp(fightOutPokemonGetPokemonPtr(temp_r27),0);
    fightSeqKizetuInit(temp_r27);
    fightPokemon_SetHokakuFlag(fightOutPokemon_GetFightPokemonPtr(temp_r27),1);
    fightSeqCheckSetHensinBuffToMotoFightPokemon(temp_r27, 0xD2);
    fightTrainer_SetNigeruCount(temp_r24, 1);
    if (var_r31 == 1) {
        fightMainAllCamera(1, 0);
        fightSeq_NextWazaSeq(5);
        return;
    }
    if (fightFloor_GetFightKind(0) == 0xC) {
        fightSeqOpenMsg(0x5002);
        fightMenuCloseMsg();
    }
    fightSeq_JumpWazaSeq(*(const u8**)(temp_r30+1));
}

u8 fightSeqItemSeq_AddPoke__FP7PokemonUcP13FIGHT_TRAINERP4Hero(void *arg0, u8 arg1, void *arg2, void *arg3) {
    s16 temp_r3_2;
    void *temp_r25;
    s32 temp_r28;
    s32 temp_r3;
    void *temp_r3_3;
    void *temp_r3_4;
    s32 temp_r4;
    u16 temp_r20;
    u16 temp_r30;
    u16 var_r4;
    void *temp_r26;
    u8 temp_r27;
    u8 var_r29;

    var_r29 = 0;
    temp_r28 = fightFloor_GetEncountFloorId();
    temp_r25 = getDeckDarkPokemonObj__15DeckDarkPokemonFUl(pokemon_GetDarkpokemonDataId(arg0));
    temp_r26 = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(arg0));
    temp_r27 = fightFloor_GetFightTypeEntryPokemonNum(0);
    if (fightFloor_GetFightKind(0) == 0xC) {
        WildPokemonCatchFlag = 1;
        fightMsgctrlSetValue(0x16, (u32)pokemon_GetNicknamePtr(arg0));
        winMsgOpenField(0x4F85, 1, 1);
        if (menuSubOpenYesNoField() == 0) {
            menuNameEntryOpen(4,0);
        }
    }
    if (pokemonIsDarkPokemon(arg0) == 1) {
        temp_r30 = pokemon_GetHp(arg0);
        temp_r4 = temp_r30 * 0x64;
        temp_r20 = (u16) (temp_r4 / (s32) pokemon_GetMaxHp(arg0));
        temp_r3 = darkPokemonBiosGetLevel(pokemon_GetDarkpokemonDataId(arg0));
        pokemon_SetLevel(arg0, temp_r3);
        pokemon_SetExp(arg0, pokemonGetLevelToExp(arg0, temp_r3));
        pokemonResetBasisStatus(arg0);
        var_r4 = (u16) ((s32) (temp_r20 * pokemon_GetMaxHp(arg0)) / 100);
        if ((var_r4 == 0) && (temp_r30 != 0)) {
            var_r4 = 1;
        }
        pokemon_SetHp(arg0, var_r4);
    }
    setReversPattern__11DarkPokemonFUc(temp_r26, getRevers__15DeckDarkPokemonCFv(temp_r25));
    pokemon_SetFightTrainerPokemonDataId(arg0, 0);
    temp_r3_2 = heroCatchPokemon(arg3, arg0, temp_r28, arg1, 1);
    if (temp_r3_2 == -1) {
        var_r29 = 1;
    }
    if ((var_r29 == 0) && (temp_r3_2 >= 0)) {
        temp_r3_3 = fightTrainerSearchInvalidFightPokemonPtr(arg2, temp_r27);
        if (temp_r3_3 != 0) {
            temp_r3_4 = heroGetStatus(arg3, 3, (u16) temp_r3_2);
            if ((temp_r3_4 != 0) && (pokemonCheckValid(temp_r3_4) == 1)) {
                if (temp_r26 != 0U) {
                    setPlace__11DarkPokemonF16darkPokemonWhereUc(temp_r26, 1, 0);
                }
                if (pokemonIsJoutaiDataId(temp_r3_4, 4) == 1) {
                    pokemonSetCountAsJoutaiDataId(temp_r3_4, 4, 1);
                }
                fightPokemonCreate(arg2, temp_r3_3, temp_r3_4, fightFloorGetFightPokemonEntryCntInc(0));
                fightPokemon_SetCatchEntryFlag(temp_r3_3, 1);
                if ((fightFloor_GetFightKindGetFriendFlag(0) == 1) && (fightFloor_GetFightKindBossFlag(0) == 1) && (fightTrainerIsGcHero(arg2) == 1)) {
                    fightPokemonGetFriendFormPokemonFriendFilterId(temp_r3_3, 3);
                }
            }
        }
    }
    if ((fightFloor_GetFightKindDoZukanTukamaetaFlag(0) == 1) && (fightTrainerIsGcHero(arg2) == 1)) {
        pokemonSetOnZukanFlag(arg0, 1);
        pokemonSetOnDarkPokemonFlag(arg0, 1);
    }
    return var_r29;
}

void WS_BALL_THROW(void) {
    u8 sp8;
    void *temp_r19;
    s32 temp_r19_2;
    void *temp_r26;
    void *temp_r27;
    void *temp_r29;
    void *temp_r30;
    s32 temp_r5;
    s32 temp_r6;
    s32 var_r20;
    u16 temp_r20;
    u16 temp_r21;
    u16 temp_r24;
    u16 temp_r25;
    u32 temp_r20_2;
    u32 temp_r3;
    u32 temp_r3_2;
    u8 temp_r22;
    u8 temp_r23;
    u8 var_r28;
    u8 var_r28_2;
    u8 var_r29;
    u8 var_r31;
    u8 *temp_r20_3;

    var_r28 = 0;
    var_r31 = 0;
    fightFloor_GetEncountDataId(0);
    fightSeq_GetWazaSeq();
    temp_r23 = fightFloor_GetTikeiDataId(0);
    temp_r29 = fightTargetGetPtrAsNowFightType(0x11, 0);
    temp_r19 = fightOutPokemon_GetFightItemPtr(temp_r29);
    fightItem_GetCount(temp_r19);
    temp_r24 = fightItem_GetItemDataId(temp_r19);
    temp_r27 = fightTargetGetPtrAsNowFightType(0x12, 0);
    temp_r26 = fightOutPokemonGetPokemonPtr(temp_r27);
    temp_r25 = pokemon_GetDarkpokemonDataId(temp_r26);
    temp_r19_2 = pokemon_GetPokemonDataId(temp_r26);
    temp_r22 = figthOutPokemonGetLevel(temp_r27);
    temp_r21 = pokemon_GetHp(temp_r26);
    temp_r20 = pokemon_GetMaxHp(temp_r26);
    temp_r30 = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(0, temp_r29);
    if (pokemonIsDarkPokemon(temp_r26) == 1) {
        var_r29 = darkPokemonBiosGetHokakuritu(temp_r25);
    } else {
        var_r29 = pokemonDB_GetGet(temp_r19_2);
    }
    switch (temp_r24) {
    case 2:
        var_r28 = 0x14;
        break;
    case 3:
        var_r28 = 0xF;
        break;
    case 4:
    case 5:
        var_r28 = 0xA;
        break;
    case 6:
        if ((fightOutPokemonIsZokuseiDataId(temp_r27, 0xB) == 1) || (fightOutPokemonIsZokuseiDataId(temp_r27, 6) == 1)) {
            var_r28 = 0x1E;
        } else {
            var_r28 = 0xA;
        }
        break;
    case 7:
        if (((u16) (temp_r23 - 3) <= 1U) || (temp_r23 == 5)) {
            var_r28 = 0x23;
        } else {
            var_r28 = 0xA;
        }
        break;
    case 8:
        if (temp_r22 < 0x28U) {
            var_r28 = 0x28 - temp_r22;
            if (var_r28 < 0xAU) {
                var_r28 = 0xA;
            }
        } else {
            var_r28 = 0xA;
        }
        break;
    case 9:
        if (pokemonIsDarkPokemon(temp_r26) == 1) {
            if (darkPokemonBiosGetSnatchSuccessFlag(temp_r25) == 1) {
                var_r31 = 1;
            }
        } else if ((u8) (pokemonDB_GetTukamaetaFlag(0) != 0) == 1) {
            var_r31 = 1;
        }
        if (var_r31 == 1) {
            var_r28 = 0x1E;
        } else {
            var_r28 = 0xA;
        }
        break;
    case 10:
        var_r28 = fightFloor_GetTurnCount(0) + 0xA;
        if (var_r28 > 0x28U) {
            var_r28 = 0x28;
        }
        break;
    case 11:
    case 12:
        var_r28 = 0xA;
        break;
    }
    if ((temp_r24 == 1) || (temp_r25 == 1)) {
        var_r28_2 = 4;
    } else {
        temp_r5 = (s32) (var_r29 * var_r28) / 10;
        temp_r6 = temp_r20 * 3;
        var_r20 = (s32) (temp_r5 * (temp_r6 - (temp_r21 * 2))) / temp_r6;
        if ((fightOutPokemonIsJoutaiDataId(temp_r27, 8) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r27, 7) == 1)) {
            var_r20 *= 2;
        }
        if ((fightOutPokemonIsJoutaiDataId(temp_r27, 3) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r27, 4) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r27, 5) == 1) || (fightOutPokemonIsJoutaiDataId(temp_r27, 6) == 1)) {
            var_r20 = (s32) ((u32) (var_r20 * 0xF) / 10U);
        }
        if ((u32) var_r20 >= 0xFFU) {
            var_r28_2 = 4;
        } else {
            temp_r3 = 0xFF0000U / (u32) var_r20;
            temp_r3_2 = (u32) sqrt((f64) temp_r3);
            var_r28_2 = 0;
            temp_r20_2 = 0xFFFF0U / (u32) sqrt((f64) temp_r3_2);
loop_47:
            if (var_r28_2 < 4U) {
                if (HSD_Rand() < temp_r20_2) {
                    var_r28_2 += 1;
                    goto loop_47;
                }
            }
        }
    }
    fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 0);
    fightOutPokemonHokakuEffect(temp_r27, var_r28_2, temp_r24, 0, &sp8);
    if (fightFloor_GetTrainer(0) == 0) {
        fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 3);
    }
    if ((fightFloor_GetFightKind(0) == 0xC) || (fightFloor_GetFightKind(0) == 0xD)) {
        fightMsgctrlSetValue(0x5D, 0);
        fightMsgctrlSetValue(0x29,(u32)GSmsgGetGSchar(itemDB_GetName(temp_r24)));
        fightMenuOpenMsg(0x4FFC);
    } else {
        fightMsgctrlSetValue(0x5D, 0);
        fightMenuOpenMsg(0x4FD9);
    }
    fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 1);
    fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 2);
    if (fightFloor_GetTrainer(0) != 0) {
        fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 3);
    }
    fightOutPokemonHokakuEffect(temp_r27, var_r28_2, temp_r24, 1, &sp8);
    fightMsgctrlSetValue(0x16, (u32)fightOutPokemonGetNicknamePtr(temp_r27));
    if (var_r28_2 >= 4U) {
        fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 4);
        if ((fightFloor_GetFightKind(0) == 0xC) || (fightFloor_GetFightKind(0) == 0xD)) {
            fightMsgctrlSetValue(0x5D, 0);
            fightMenuOpenMsg(0x4FF9);
        } else {
            fightMsgctrlSetValue(0x5D, 0);
            fightMenuOpenMsg(0x4FE0);
        }
        soundOpenPlayME(0x36B, 0, 0xFF);
        fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 5);
        fightMenuCloseMsg();
        fightSeq_JumpWazaSeq(ITEM_MonsGetSuccess);
    } else {
        fightOutPokemonHokakuEffect(temp_r27, var_r28_2, temp_r24, 2, &sp8);
        temp_r20_3 = ServerWork;
        temp_r20_3[5] = var_r28_2;
        if ((fightFloor_GetFightKind(0) == 0xC) || (fightFloor_GetFightKind(0) == 0xD)) {
            fightMenuOpenMsg(GetYaseiFailMsgTbl[temp_r20_3[5]]);
        } else {
            fightMenuOpenMsg(GetFailMsgTbl[temp_r20_3[5]]);
        }
        fightOutPokemonHokakuEffect(temp_r27, var_r28_2, temp_r24, 3, &sp8);
        fightMenuCloseMsg();
        fightSeq_JumpWazaSeq(ITEM_MonsGetFail);
    }
    fightTrainerHokakuThrowEffect(temp_r30, temp_r24, 6);
    fightOutPokemonHokakuEffect(temp_r27, var_r28_2, temp_r24, 4, &sp8);
}

}
