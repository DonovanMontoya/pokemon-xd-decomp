#include <dolphin/types.h>
#include <game/pxdvs/app/fight/fightPokemon.hpp>
#include <game/pxdvs/app/fight/fightTrainerEnemy.hpp>
struct Hero;
struct FightTrainer {
    u16 dataId;
    u16 reserved02;
    u8 heroStorage[0x978];
    FightPokemon pokemon[6];
    FightOutPokemon outPokemon[2];
    FightOutPokemon outPokemonBuff;
    u8 okaneBai, nigeruCount;
    u16 reserved353a;
    s32 koban;
    u8 controllerId;
    u8 reserved3541[3];
    void *sequence;
    FightActionBuff actionBuff;
    FightTrainerEnemyPokemon enemy[12];
};
struct FightTrainerAiValueAddsubData { s32 value; u32 koudouName, prefixName, name; };


typedef struct DeckPokemon { u16 pokemonId; u8 level,friendLevel; u16 holdItem; u8 role,keyPlayer; u8 statusRnd[6],statusEffort[6]; u16 waza[4]; u8 reserved1c[2]; union { u8 flags; struct { u8 seikaku : 5; u8 sex : 2; u8 tokusei : 1; } flagBits; }; } DeckPokemon;
typedef struct PokemonPart { u32 name; u32 reserved4; u8 wazaTypeRevise[14]; } PokemonPart;

extern "C" {
FightTrainerEnemyPokemon *fightTrainerGetFightEntryIdToEnemyPokemonPtr(FightTrainer *, s16);
FightTrainerEnemyPokemon *fightTrainer_GetFightTrainerEnemyPokemonAryPtr(FightTrainer *, u8);
FightTrainerAiValueAddsubData *fightTrainerAiValueAddsubDataBiosGetPtr(u16);

































































































DeckPokemon *getDeckPokemonObj__11DeckPokemonFUl(u32); void *getDeckTrainerObj__11DeckTrainerFUl(u32); void *getDeckTrainerAIObj__13DeckTrainerAIFUl(u32); void *fightTrainerDataBiosGetPtr(u16); PokemonPart *fightTrainerPokemonPartDataBiosGetPtr(u16);
s32 getAIID__11DeckTrainerCFv(void *);
s32 getAbilityDetermination__13DeckTrainerAICFv(void *);
s32 getAnnihilateDetermRate__13DeckTrainerAICFv(void *);
s32 getAttrDetermination__13DeckTrainerAICFv(void *);
s32 getAttrTypeID__13DeckTrainerAICFUc(void *, u8);
s32 getAttrTypeParam__13DeckTrainerAICFUc(void *, u8);
s32 getCalcWazaDamage__13DeckTrainerAICFv(void *);
s32 getFriendLevel__11DeckPokemonCFv(void *);
s32 getHitRate__13DeckTrainerAICFv(void *);
s32 getHoldItem__11DeckPokemonCFv(void *);
s32 getIntroWZX__11DeckTrainerCFv(void *);
s32 getItemUseRate__13DeckTrainerAICFv(void *);
s32 getKeyPlayer__11DeckPokemonCFv(void *);
s32 getLastPPDetermRate__13DeckTrainerAICFv(void *);
s32 getLevel__11DeckPokemonCFv(void *);
s32 getLowHPDetermRate__13DeckTrainerAICFv(void *);
s32 getNotSameWeekPoint__13DeckTrainerAICFv(void *);
s32 getOrder__13DeckTrainerAICFv(void *);
s32 getPokeChgRate__13DeckTrainerAICFv(void *);
s32 getPokemonDataID__11DeckTrainerCFUc(void *, u8);
s32 getPokemonID__11DeckPokemonCFv(void *);
s32 getRespectKeyPlayer__13DeckTrainerAICFv(void *);
s32 getRespectPokemonCondJuge__13DeckTrainerAICFv(void *);
s32 getRespectRole__13DeckTrainerAICFv(void *);
s32 getRespectWazaAssmntVal__13DeckTrainerAICFv(void *);
s32 getRespectWazaHit__13DeckTrainerAICFv(void *);
s32 getRespectWazaRiskJudge__13DeckTrainerAICFv(void *);
s32 getRole__11DeckPokemonCFv(void *);
s32 getSeikakuID__11DeckPokemonCFv(void *);
s32 getSelectAceBoss__13DeckTrainerAICFv(void *);
s32 getSelectRandomDefence__13DeckTrainerAICFv(void *);
s32 getSelectRandomPokemon__13DeckTrainerAICFv(void *);
s32 getSelectRandomWaza__13DeckTrainerAICFv(void *);
s32 getSex__11DeckPokemonCFv(void *);
s32 getStatusDetermValMax__13DeckTrainerAICFUc(void *, u8);
s32 getStatusDetermValMin__13DeckTrainerAICFUc(void *, u8);
s32 getStatusDetermValTotalMax__13DeckTrainerAICFv(void *);
s32 getStatusDetermValTotalMin__13DeckTrainerAICFv(void *);
s32 getStatusEffort__11DeckPokemonCFUc(void *, u8);
s32 getStatusRnd__11DeckPokemonCFUc(void *, u8);
s32 getTokuseiFlag__11DeckPokemonCFv(void *);
s32 getTotalCorrection__13DeckTrainerAICFv(void *);
s32 getTrainerItem__11DeckTrainerCFUc(void *, u8);
s32 getTrainerKind__11DeckTrainerCFv(void *);
s32 getTrainerMsg__11DeckTrainerCFUc(void *, u8);
s32 getTrainerName__11DeckTrainerCFv(void *);
s32 getTrainerPKX__11DeckTrainerCFv(void *);
s32 getWazaID__11DeckPokemonCFUc(void *, u8);
s32 getWazaKindID__13DeckTrainerAICFUc(void *, u8);
s32 getWazaKindParam__13DeckTrainerAICFUc(void *, u8);
void setAIID__11DeckTrainerFUs(void *, u16);
void setAbilityDetermination__13DeckTrainerAIFb(void *, u8);
void setAttrDetermination__13DeckTrainerAIFb(void *, u8);
void setAttrTypeID__13DeckTrainerAIFUcUc(void *, u8, u8);
void setAttrTypeParam__13DeckTrainerAIFUcUc(void *, u8, u8);
void setCalcWazaDamage__13DeckTrainerAIFb(void *, u8);
void setHitRate__13DeckTrainerAIFUc(void *, u8);
void setIntroWZX__11DeckTrainerFUs(void *, u16);
void setItemUseRate__13DeckTrainerAIFUc(void *, u8);
void setLastPPDetermRate__13DeckTrainerAIFUc(void *, u8);
void setLowHPDetermRate__13DeckTrainerAIFUc(void *, u8);
void setNotSameWeekPoint__13DeckTrainerAIFb(void *, u8);
void setOrder__13DeckTrainerAIFb(void *, u8);
void setPokeChgRate__13DeckTrainerAIFUc(void *, u8);
void setPokemonDataID__11DeckTrainerFUcUs(void *, u8, u16);
void setRespectKeyPlayer__13DeckTrainerAIFb(void *, u8);
void setRespectPokemonCondJuge__13DeckTrainerAIFb(void *, u8);
void setRespectRole__13DeckTrainerAIFb(void *, u8);
void setRespectWazaAssmntVal__13DeckTrainerAIFb(void *, u8);
void setRespectWazaHit__13DeckTrainerAIFb(void *, u8);
void setRespectWazaRiskJudge__13DeckTrainerAIFb(void *, u8);
void setSelectAceBoss__13DeckTrainerAIFb(void *, u8);
void setSelectRandomDefence__13DeckTrainerAIFb(void *, u8);
void setSelectRandomPokemon__13DeckTrainerAIFb(void *, u8);
void setSelectRandomWaza__13DeckTrainerAIFb(void *, u8);
void setStatusDetermValTotalMax__13DeckTrainerAIFUc(void *, u8);
void setStatusDetermValTotalMin__13DeckTrainerAIFUc(void *, u8);
void setTotalCorrection__13DeckTrainerAIFUc(void *, u8);
void setTrainerItem__11DeckTrainerFUcUs(void *, u8, u16);
void setTrainerKind__11DeckTrainerFUc(void *, u8);
void setTrainerMsg__11DeckTrainerFUcUs(void *, u8, u16);
void setTrainerName__11DeckTrainerFUs(void *, u16);
void setTrainerPKX__11DeckTrainerFUs(void *, u16);
void setWazaKindID__13DeckTrainerAIFUcUs(void *, u8, u16);
void setWazaKindParam__13DeckTrainerAIFUcUc(void *, u8, u8);

















































































































































































































































Hero *savedataGetStatus(void *, u16);
u8 getHeroStyle__4HeroCFv(Hero *);




void fightTrainer_SetEnemyPokemonRegist(FightTrainer *arg0, s16 arg1) {
    if (arg0 != 0) {
        FightTrainerEnemyPokemon *enemy = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(arg0, 0);
        if (enemy != 0) fightTrainerEnemyPokemonRegistAry(enemy, 12, arg1);
    }
}

void fightTrainer_SetEnemyParam1bantakaiFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->paramHighest = arg2;
        }
    }
}

void fightTrainer_SetEnemyBadwazaHaveFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->badWaza = arg2;
        }
    }
}

void fightTrainer_SetEnemyDefense1banhikuiFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->defenseLowest = arg2;
        }
    }
}

void fightTrainer_SetEnemyLv1banhikuiFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->levelLowest = arg2;
        }
    }
}

void fightTrainer_SetEnemyNowhp1banhikuiFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->nowhpLowest = arg2;
        }
    }
}

void fightTrainer_SetEnemyStoreTokuseiData(FightTrainer *arg0, s16 arg1, s16 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->storeTokusei = arg2;
        }
    }
}

void fightTrainer_SetEnemyTokuseiFlag(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->tokuseiFlag = arg2;
        }
    }
}

void fightTrainer_SetEnemyExpectWazaData(FightTrainer *arg0, s16 arg1, s32 arg2, s16 arg3) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->expectWaza[(u8)arg2] = arg3;
        }
    }
}

void fightTrainer_SetEnemyStoreWazaData(FightTrainer *arg0, s16 arg1, s32 arg2, s16 arg3) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->storeWaza[(u8)arg2] = arg3;
        }
    }
}

void fightTrainer_SetEnemyExpectWazaNum(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->expectWazaNum = arg2;
        }
    }
}

void fightTrainer_SetEnemyStoreWazaNum(FightTrainer *arg0, s16 arg1, s8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 != 0) {
        temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
        if (temp_r3 != 0) {
            temp_r3->storeWazaNum = arg2;
        }
    }
}

void fightTrainer_SetSequencePtr(FightTrainer *arg0, void * arg1) {
    if (arg0 != 0) arg0->sequence = arg1;
}

void fightTrainer_SetControllerId(FightTrainer *arg0, u8 arg1) {
    if (arg0 != 0) arg0->controllerId = arg1;
}

void fightTrainer_SetNigeruCount(FightTrainer *arg0, u8 arg1) {
    if (arg0 != 0) arg0->nigeruCount = arg1;
}

void fightTrainer_SetKoban(FightTrainer *arg0, s32 arg1) {
    if (arg0 != 0) arg0->koban = arg1;
}

void fightTrainer_SetOkaneBai(FightTrainer *arg0, u8 arg1) {
    if (arg0 != 0) arg0->okaneBai = arg1;
}

void fightTrainer_SetFightTrainerDataId(FightTrainer *arg0, u16 arg1) {
    if (arg0 != 0) arg0->dataId = arg1;
}

void fightTrainerAiValueAddsubDB_SetPrefixName(u16 id, s32 value) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data != 0) data->prefixName = value;
}

void fightTrainerAiValueAddsubDB_SetKoudouName(u16 id, s32 value) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data != 0) data->koudouName = value;
}

void fightTrainerAiValueAddsubDB_SetName(u16 id, s32 value) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data != 0) data->name = value;
}

void fightTrainerAiValueAddsubDB_SetValue(u16 id, s32 value) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data != 0) data->value = value;
}

u8 fightTrainer_GetEnemyParam1bantakaiFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->paramHighest;
}

u8 fightTrainer_GetEnemyBadwazaHaveFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->badWaza;
}

u8 fightTrainer_GetEnemyDefense1banhikuiFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->defenseLowest;
}

u8 fightTrainer_GetEnemyLv1banhikuiFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->levelLowest;
}

u8 fightTrainer_GetEnemyNowhp1banhikuiFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->nowhpLowest;
}

u16 fightTrainer_GetEnemyStoreTokuseiData(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->storeTokusei;
}

u8 fightTrainer_GetEnemyTokuseiFlag(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->tokuseiFlag;
}

u16 fightTrainer_GetEnemyExpectWazaData(FightTrainer *arg0, s16 arg1, u8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    if (arg2 > 8U) {
        return 0U;
    }
    return temp_r3->expectWaza[(u8)arg2];
}

u16 fightTrainer_GetEnemyStoreWazaData(FightTrainer *arg0, s16 arg1, u8 arg2) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    if (arg2 >= 4U) {
        return 0U;
    }
    return temp_r3->storeWaza[(u8)arg2];
}

u8 fightTrainer_GetEnemyStoreWazaNum(FightTrainer *arg0, s16 arg1) {
    FightTrainerEnemyPokemon *temp_r3;

    if (arg0 == 0) {
        return 0U;
    }
    temp_r3 = fightTrainerGetFightEntryIdToEnemyPokemonPtr(arg0, arg1);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->storeWazaNum;
}

FightTrainerEnemyPokemon * fightTrainer_GetFightTrainerEnemyPokemonAryPtr(FightTrainer *arg0, u8 arg1) {
    if (arg0 == 0) return 0;
    if (arg1 >= 12) return 0;
    return &arg0->enemy[arg1];
}

void * fightTrainer_GetSequencePtr(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->sequence;
}

FightActionBuff * fightTrainer_GetFightActionBuffPtr(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return &arg0->actionBuff;
}

u8 fightTrainer_GetControllerId(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->controllerId;
}

u8 fightTrainer_GetNigeruCount(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->nigeruCount;
}

s32 fightTrainer_GetKoban(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->koban;
}

u8 fightTrainer_GetOkaneBai(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->okaneBai;
}

FightOutPokemon * fightTrainer_GetFightoutPokemonBuffPtr(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return &arg0->outPokemonBuff;
}

FightOutPokemon * fightTrainer_GetFightoutPokemonPtr(FightTrainer *arg0, u16 arg1) {
    if (arg0 == 0) return 0;
    if (arg1 >= 2) return 0;
    return &arg0->outPokemon[arg1];
}

FightPokemon * fightTrainer_GetFightPokemonPtr(FightTrainer *arg0, u16 arg1) {
    if (arg0 == 0) return 0;
    if (arg1 >= 6) return 0;
    return &arg0->pokemon[arg1];
}

u16 fightTrainer_GetFightTrainerDataId(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return arg0->dataId;
}

Hero * fightTrainer_GetHeroPtr(FightTrainer *arg0) {
    if (arg0 == 0) return 0;
    return (Hero *)arg0->heroStorage;
}

s32 fightTrainerAiValueAddsubDB_GetPrefixName(u16 id) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data == 0) return 0;
    return data->prefixName;
}

s32 fightTrainerAiValueAddsubDB_GetKoudouName(u16 id) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data == 0) return 0;
    return data->koudouName;
}

s32 fightTrainerAiValueAddsubDB_GetName(u16 id) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data == 0) return 0;
    return data->name;
}

s32 fightTrainerAiValueAddsubDB_GetValue(u16 id) {
    FightTrainerAiValueAddsubData *data = fightTrainerAiValueAddsubDataBiosGetPtr(id);
    if (data == 0) return 0;
    return data->value;
}

void fightTrainerAiDB_SetParamStoreFlag(void) {

}

s32 fightTrainerAiDB_GetParamStoreFlag(void) {
    return 1;
}

void fightTrainerAiDB_SetParamExpectFlag(void) {

}

s32 fightTrainerAiDB_GetParamExpectFlag(void) {
    return 1;
}

void fightTrainerAiDB_SetComboValue(void) {

}

s32 fightTrainerAiDB_GetComboValue(void) {
    return 0x64;
}

void fightTrainerAiDB_SetLastValueRevise(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setTotalCorrection__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetLastValueRevise(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getTotalCorrection__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaTypeReviseValue(u16 arg0, u8 arg1, u8 arg2) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 2U)) {
        setWazaKindParam__13DeckTrainerAIFUcUc(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerAiDB_GetWazaTypeReviseValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 2U) {
        return 0;
    }
    return getWazaKindParam__13DeckTrainerAICFUc(temp_r3, arg1);
}

void fightTrainerAiDB_SetWazaTypeReviseTypeDataId(u16 arg0, u8 arg1, u8 arg2) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 2U)) {
        setWazaKindID__13DeckTrainerAIFUcUs(temp_r3, arg1, (u16) arg2);
    }
}

u8 fightTrainerAiDB_GetWazaTypeReviseTypeDataId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0U;
    }
    if (arg1 >= 2U) {
        return 0U;
    }
    return getWazaKindID__13DeckTrainerAICFUc(temp_r3, arg1);
}

void fightTrainerAiDB_SetZokuseiReviseValue(u16 arg0, u8 arg1, u8 arg2) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 2U)) {
        setAttrTypeParam__13DeckTrainerAIFUcUc(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerAiDB_GetZokuseiReviseValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 2U) {
        return 0;
    }
    return getAttrTypeParam__13DeckTrainerAICFUc(temp_r3, arg1);
}

void fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(u16 arg0, u8 arg1, u8 arg2) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 2U)) {
        setAttrTypeID__13DeckTrainerAIFUcUc(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 2U) {
        return 0;
    }
    return getAttrTypeID__13DeckTrainerAICFUc(temp_r3, arg1);
}

void fightTrainerAiDB_SetWazaNokoriPpValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setLastPPDetermRate__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaNokoriPpValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getLastPPDetermRate__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetNokoriHpValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setLowHPDetermRate__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetNokoriHpValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getLowHPDetermRate__13DeckTrainerAICFv(temp_r3);
}

s32 fightTrainerAiDB_GetStrokeValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getAnnihilateDetermRate__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaAvgValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setHitRate__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaAvgValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getHitRate__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetItemValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setItemUseRate__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetItemValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getItemUseRate__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetIrekaeValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setPokeChgRate__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetIrekaeValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getPokeChgRate__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetAbicntMinValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setStatusDetermValTotalMin__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetAbicntMinValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValTotalMin__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetAbicntMaxValue(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setStatusDetermValTotalMax__13DeckTrainerAIFUc(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetAbicntMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValTotalMax__13DeckTrainerAICFv(temp_r3);
}

s32 fightTrainerAiDB_GetAvoidMinValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMin__13DeckTrainerAICFUc(temp_r3, 6U);
}

s32 fightTrainerAiDB_GetAvoidMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 6U);
}

s32 fightTrainerAiDB_GetNimblenessMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 4U);
}

s32 fightTrainerAiDB_GetSpeDefMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 3U);
}

s32 fightTrainerAiDB_GetSpeAtkMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 2U);
}

s32 fightTrainerAiDB_GetPhyDefMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 1U);
}

s32 fightTrainerAiDB_GetPhyAtkMaxValue(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getStatusDetermValMax__13DeckTrainerAICFUc(temp_r3, 0U);
}

void fightTrainerAiDB_SetPokemonJoutaiFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectPokemonCondJuge__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPokemonJoutaiFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectPokemonCondJuge__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaRiskFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectWazaRiskJudge__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaRiskFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectWazaRiskJudge__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaHitFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectWazaHit__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaHitFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectWazaHit__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetPartFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectRole__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPartFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectRole__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaInitValueFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectWazaAssmntVal__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaInitValueFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectWazaAssmntVal__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaRndSelectFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setSelectRandomWaza__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaRndSelectFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSelectRandomWaza__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetDefensePokemonRndSelectFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setSelectRandomDefence__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetDefensePokemonRndSelectFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSelectRandomDefence__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetWazaDamageFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setCalcWazaDamage__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetWazaDamageFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getCalcWazaDamage__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetTokuseiCheckFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setAbilityDetermination__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetTokuseiCheckFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getAbilityDetermination__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetZokuseiCheckFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setAttrDetermination__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetZokuseiCheckFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getAttrDetermination__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetKeyPlayerFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setRespectKeyPlayer__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetKeyPlayerFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRespectKeyPlayer__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setSelectAceBoss__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSelectAceBoss__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetPokemonDataOrderOutFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setOrder__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getOrder__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetPokemonSelectWeakPointFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setNotSameWeekPoint__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getNotSameWeekPoint__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerAiDB_SetPokemonSelectRandomFlag(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 != 0) {
        setSelectRandomPokemon__13DeckTrainerAIFb(temp_r3, arg1);
    }
}

s32 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerAIObj__13DeckTrainerAIFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSelectRandomPokemon__13DeckTrainerAICFv(temp_r3);
}

void fightTrainerPokemonPartDB_SetWazaTypeRevise(u16 arg0, u8 arg1, u8 arg2) {
    PokemonPart *temp_r3;

    temp_r3 = fightTrainerPokemonPartDataBiosGetPtr(arg0);
    if ((temp_r3 != 0) && (arg1 < 0xEU)) {
        temp_r3->wazaTypeRevise[arg1] = arg2;
    }
}

u8 fightTrainerPokemonPartDB_GetWazaTypeRevise(u16 arg0, u8 arg1) {
    PokemonPart *temp_r3;

    temp_r3 = fightTrainerPokemonPartDataBiosGetPtr(arg0);
    if (temp_r3 == 0) {
        return 0U;
    }
    if (arg1 >= 0xEU) {
        return 0U;
    }
    return temp_r3->wazaTypeRevise[arg1];
}

void fightTrainerPokemonPartDB_SetName(u16 arg0, u32 arg1) {
    PokemonPart *temp_r3;

    temp_r3 = fightTrainerPokemonPartDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        temp_r3->name = arg1;
    }
}

u32 fightTrainerPokemonPartDB_GetName(u16 arg0) {
    PokemonPart *temp_r3;

    temp_r3 = fightTrainerPokemonPartDataBiosGetPtr(arg0);
    if (temp_r3 == 0) {
        return 0U;
    }
    return temp_r3->name;
}

void fightTrainerPokemonDB_SetPpCnt(void) {

}

s32 fightTrainerPokemonDB_GetPpCnt(void) {
    return 0;
}

void fightTrainerPokemonDB_SetDarkPokemonFlag(void) {

}

s32 fightTrainerPokemonDB_GetDarkPokemonFlag(void) {
    return 0;
}

void fightTrainerPokemonDB_SetItemBallId(void) {

}

s32 fightTrainerPokemonDB_GetItemBallId(void) {
    return 0;
}

void fightTrainerPokemonDB_SetNickname(void) {

}

s32 fightTrainerPokemonDB_GetNickname(void) {
    return 0;
}

void fightTrainerPokemonDB_SetPartDataId(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->role = arg1;
    }
}

s32 fightTrainerPokemonDB_GetPartDataId(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getRole__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetKeyPlayerFlag(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->keyPlayer = arg1;
    }
}

s32 fightTrainerPokemonDB_GetKeyPlayerFlag(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getKeyPlayer__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetWazaDataId(u16 arg0, s32 arg1, s16 arg2) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->waza[(u8)arg1] = arg2;
    }
}

s32 fightTrainerPokemonDB_GetWazaDataId(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getWazaID__11DeckPokemonCFUc(temp_r3, arg1);
}

void fightTrainerPokemonDB_SetStatusEffort(u16 arg0, u8 arg1, u8 arg2) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 6U)) {
        temp_r3->statusEffort[arg1] = arg2;
    }
}

s32 fightTrainerPokemonDB_GetStatusEffort(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 6U) {
        return 0;
    }
    return getStatusEffort__11DeckPokemonCFUc(temp_r3, arg1);
}

void fightTrainerPokemonDB_SetStatusRnd(u16 arg0, u8 arg1, u8 arg2) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if ((temp_r3 != 0) && (arg1 < 6U)) {
        temp_r3->statusRnd[arg1] = arg2;
    }
}

s32 fightTrainerPokemonDB_GetStatusRnd(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 6U) {
        return 0;
    }
    return getStatusRnd__11DeckPokemonCFUc(temp_r3, arg1);
}

void fightTrainerPokemonDB_SetItemDataId(u16 arg0, u16 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->holdItem = arg1;
    }
}

s32 fightTrainerPokemonDB_GetItemDataId(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getHoldItem__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetTokuseiFlag(u16 arg0, s32 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->flagBits.tokusei = arg1;
    }
}

s32 fightTrainerPokemonDB_GetTokuseiFlag(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getTokuseiFlag__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetSeikakuDataId(u16 arg0, s32 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->flagBits.seikaku = arg1;
    }
}

s32 fightTrainerPokemonDB_GetSeikakuDataId(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSeikakuID__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetSexDataId(u16 arg0, s32 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->flags = (temp_r3->flags & ~6) | ((arg1 << 1) & 6);
    }
}

s32 fightTrainerPokemonDB_GetSexDataId(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getSex__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetFriend(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->friendLevel = arg1;
    }
}

s32 fightTrainerPokemonDB_GetFriend(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getFriendLevel__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetLevel(u16 arg0, u8 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->level = arg1;
    }
}

s32 fightTrainerPokemonDB_GetLevel(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getLevel__11DeckPokemonCFv(temp_r3);
}

void fightTrainerPokemonDB_SetPokemonDataId(u16 arg0, u16 arg1) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 != 0) {
        temp_r3->pokemonId = arg1;
    }
}

s32 fightTrainerPokemonDB_GetPokemonDataId(u16 arg0) {
    DeckPokemon *temp_r3;

    temp_r3 = getDeckPokemonObj__11DeckPokemonFUl((u32) arg0);
    if (temp_r3 == 0) {
        return 0;
    }
    return getPokemonID__11DeckPokemonCFv(temp_r3);
}

s32 fightTrainerDB_GetSexDataId(void) {
    return 0;
}

void fightTrainerDB_SetTemotiItemDataId(u16 arg0, u8 arg1, u16 arg2) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if ((temp_r3 != 0) && (arg1 < 4U)) {
        setTrainerItem__11DeckTrainerFUcUs(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerDB_GetTemotiItemDataId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 4U) {
        return 0;
    }
    return getTrainerItem__11DeckTrainerCFUc(temp_r3, arg1);
}

void fightTrainerDB_SetAiDataId(u16 arg0, u16 arg1) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        setAIID__11DeckTrainerFUs(temp_r3, arg1);
    }
}

s32 fightTrainerDB_GetAiDataId(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    return getAIID__11DeckTrainerCFv(temp_r3);
}

void fightTrainerDB_SetTemotiPokemonId(u16 arg0, u8 arg1, u16 arg2) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if ((arg0 < 0x1388U) && (temp_r3 != 0)) {
        setPokemonDataID__11DeckTrainerFUcUs(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerDB_GetTemotiPokemonId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    return getPokemonDataID__11DeckTrainerCFUc(temp_r3, arg1);
}

void fightTrainerDB_SetSerihuMsgId(u16 arg0, u8 arg1, u16 arg2) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if ((temp_r3 != 0) && (arg1 < 4U)) {
        setTrainerMsg__11DeckTrainerFUcUs(temp_r3, arg1, arg2);
    }
}

s32 fightTrainerDB_GetSerihuMsgId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    if (arg1 >= 4U) {
        return 0;
    }
    return getTrainerMsg__11DeckTrainerCFUc(temp_r3, arg1);
}

void fightTrainerDB_SetSyoukaiWzxDataId(u16 arg0, u16 arg1) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        setIntroWZX__11DeckTrainerFUs(temp_r3, arg1);
    }
}

s32 fightTrainerDB_GetSyoukaiWzxDataId(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    return getIntroWZX__11DeckTrainerCFv(temp_r3);
}

void fightTrainerDB_SetPkxDataId(u16 arg0, u16 arg1) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        setTrainerPKX__11DeckTrainerFUs(temp_r3, arg1);
    }
}

s32 fightTrainerDB_GetPkxDataId(u16 id) {
    void *trainer = getDeckTrainerObj__11DeckTrainerFUl(id);
    if (((u8)getTrainerKind__11DeckTrainerCFv(trainer) == 1 || id == 5000)) {
        Hero *hero = savedataGetStatus(0, 2);
        if (hero != 0) {
            switch ((u8)getHeroStyle__4HeroCFv(hero)) {
            case 0: return 1;
            case 1: return 3;
            case 2: return 2;
            }
        }
    }
    switch (id) {
    case 5001: return 9;
    case 5002: return 8;
    case 5003: return 7;
    case 5004: return 6;
    case 5005: return 5;
    case 5006: return 4;
    default:
        if (trainer == 0) return 0;
        return getTrainerPKX__11DeckTrainerCFv(trainer);
    }
}

void fightTrainerDB_SetKindDataId(u16 arg0, u8 arg1) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        setTrainerKind__11DeckTrainerFUc(temp_r3, arg1);
    }
}

s32 fightTrainerDB_GetKindDataId(u16 id) {
    void *trainer = getDeckTrainerObj__11DeckTrainerFUl(id);
    switch (id) {
    case 5000: return 1;
    case 5001: case 5003: case 5005: return 2;
    case 5002: case 5004: case 5006: return 3;
    default:
        if (trainer == 0) return 0;
        return getTrainerKind__11DeckTrainerCFv(trainer);
    }
}

void fightTrainerDB_SetName(u16 arg0, u16 arg1) {
    void *temp_r3;

    temp_r3 = fightTrainerDataBiosGetPtr(arg0);
    if (temp_r3 != 0) {
        setTrainerName__11DeckTrainerFUs(temp_r3, arg1);
    }
}

s32 fightTrainerDB_GetName(u16 arg0) {
    void *temp_r3;

    temp_r3 = getDeckTrainerObj__11DeckTrainerFUl((u32) arg0);
    if (arg0 >= 0x1388U) {
        return 0;
    }
    if (temp_r3 == 0) {
        return 0;
    }
    return getTrainerName__11DeckTrainerCFv(temp_r3);
}
}
