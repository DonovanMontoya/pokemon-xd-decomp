#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonBios.hpp>
#include <game/pxdvs/app/pokemon/pokemonDB.hpp>
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#include <game/pxdvs/GSAPI/GSflag/GSflag.h>

extern "C" {

extern void GScharLenCpy(u16*,const u16*,u32);

struct WazaData;
extern u8 pokemonWazaCheckValid(Pokemon*,u16);
extern WazaData* wazaDataBiosGetPtr(u16);
extern u8 wazaDataBiosGetPp(WazaData*);

void fightWaza_SetHitDamage(FightWaza*,s32);
void fightWaza_SetTargetDataId(FightWaza*,u16);
void fightWaza_SetIryoku(FightWaza*,u16);
void fightWaza_SetDamage(FightWaza*,s32);
void fightWaza_SetCritical(FightWaza*,u8);
void fightWaza_SetDamageValue(FightWaza*,u8);
void fightWaza_SetMotoWazaDataId(FightWaza*,u16);
void fightWaza_SetUseWazaDataId(FightWaza*,u16);
s32 fightWaza_GetHitDamage(FightWaza*);
u16 fightWaza_GetTargetDataId(FightWaza*);
u16 fightWaza_GetIryoku(FightWaza*);
s32 fightWaza_GetDamage(FightWaza*);
u8 fightWazaIsHit(FightWaza*);
u8 fightWaza_GetCritical(FightWaza*);
u8 fightWaza_GetDamageValue(FightWaza*);
u16 fightWaza_GetMotoWazaDataId(FightWaza*);
u16 fightWaza_GetUseWazaDataId(FightWaza*);
u8 fightWazaIsJoutaiDataId(FightWaza*,u16);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*,u16);
void fightWazaInitJoutaiDataId(FightWaza*,u16);
void fightWazaInitJoutai(FightWaza*);
void fightWazaWriteJoutaiDataId(FightWaza*,u16,u32);

void fightOutPokemon_SetFixAiDef(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->fixAiDef = value;
}

void fightOutPokemon_SetFixAiWaza(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->fixAiWaza = value;
}

void fightOutPokemon_SetComboFuncId(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->comboFuncId = value;
}

void fightOutPokemon_SetOumuWazaAllyDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->oumuWazaAllyDataId = value;
}

void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->irekaeTargetEntryId = value;
}

void fn_8014718C(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->unknown861 = value;
}

void fightOutPokemon_SetKizetuFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->kizetuFlag = value;
}

void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->myselfDamageSpeTargetId = value;
}

void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->myselfDamageSpeValue = value;
}

void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->myselfDamageAtkTargetId = value;
}

void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->myselfDamageAtkValue = value;
}

void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon* poke, s32 value) {
    if (poke != nullptr) poke->kaigaraDamageValue = value;
}

void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->itemKoraetaFlag = value;
}

void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->irekaetaFlag = value;
}

void fightOutPokemon_SetNoPressureFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->noPressureFlag = value;
}

void fightOutPokemon_SetDoTraceFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doTraceFlag = value;
}

void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doIkakuFlag = value;
}

void fightOutPokemon_SetVanishoffFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->vanishoffFlag = value;
}

void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->receivesWazaHiraishinFlag = value;
}

void fightOutPokemon_SetDoClearbodyFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->doClearbodyFlag = value;
}

void fightOutPokemon_SetFightActionFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->fightActionFlag = value;
}

void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->passPpdecFlag = value;
}

void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->hirumuNoAttackFlag = value;
}

void fightOutPokemon_SetIchamonNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->ichamonNoAttackFlag = value;
}

void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->chouhatsuNoAttackFlag = value;
}

void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->kanashibariNoAttackFlag = value;
}

void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->meroMeroNoAttackFlag = value;
}

void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->huuinNoAttackFlag = value;
}

void fightOutPokemon_SetItemNigeruFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->itemNigeruFlag = value;
}

void fightOutPokemon_SetTameWazaFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->tameWazaFlag = value;
}

void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->outWazaKoukanaiFlag = value;
}

void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->konranMyselfAttackFlag = value;
}

void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->mahiNoAttackFlag = value;
}

void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->damageSpeTargetId = value;
}

void fightOutPokemon_SetDamageSpeValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->damageSpeValue = value;
}

void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->damageAtkTargetId = value;
}

void fightOutPokemon_SetDamageAtkValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->damageAtkValue = value;
}

void fightOutPokemon_SetTokuseiDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->tokuseiDataId = value;
}

void fightOutPokemon_SetZokuseiDataId(FightOutPokemon* poke,u8 index,u16 value) {
    if (poke == nullptr) return;
    if (index >= 2) return;
    poke->zokuseiDataId[index] = value;
}

void fightOutPokemon_SetMeetEnemyFightPokemonEntryId(FightOutPokemon* poke,u8 index,s16 value) {
    if (poke == nullptr) return;
    if (index >= 12) return;
    poke->meetEnemyFightPokemonEntryId[index] = value;
}

void fightOutPokemon_SetSuccessCnt(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->successCnt = value;
}

void fightOutPokemon_SetStockItemDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->stockItemDataId = value;
}

void fightOutPokemon_SetUsedItemDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->usedItemDataId = value;
}

void fightOutPokemon_SetNamakeFlag(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->namakeFlag = value;
}

void fightOutPokemon_SetOumuWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->oumuWazaDataId = value;
}

void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->gamanDamageTargetId = value;
}

void fightOutPokemon_SetGamanDamageValue(FightOutPokemon* poke, s16 value) {
    if (poke != nullptr) poke->gamanDamageValue = value;
}

void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->hitWazaZokuseiDataId = value;
}

void fightOutPokemon_SetHitWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->hitWazaDataId = value;
}

void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastReceiveWazaTargetDataId = value;
}

void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastUseWazaDataId = value;
}

void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->lastSelectWazaDataId = value;
}

void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->sketchWazaDataId = value;
}

void fightOutPokemon_SetSequencePtr(FightOutPokemon* poke, void* value) {
    if (poke != nullptr) poke->sequence = value;
}

void fightOutPokemon_SetFightoutTurnCount(FightOutPokemon* poke, u16 value) {
    if (poke != nullptr) poke->fightoutTurnCount = value;
}

void fightOutPokemon_SetAbicntAverage(FightOutPokemon* poke, u8 value) {
    if (poke != nullptr) poke->abicntAverage = value;
}

void fightOutPokemon_SetWazaHitDamage(FightOutPokemon* poke,s32 value) {
    if (poke != nullptr) fightWaza_SetHitDamage(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetWazaTargetId(FightOutPokemon* poke,u16 value) {
    if (poke != nullptr) fightWaza_SetTargetDataId(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetWazaIryoku(FightOutPokemon* poke,u16 value) {
    if (poke != nullptr) fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetWazaDamage(FightOutPokemon* poke,s32 value) {
    if (poke != nullptr) fightWaza_SetDamage(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetWazaInitJoutaiDataId(FightOutPokemon* poke,u16 id) {
    if (poke != nullptr) {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
        if (id != 0) {
            if (fightWazaIsJoutaiDataId(waza,id) == 1) fightWazaInitJoutaiDataId(waza,id);
        } else {
            fightWazaInitJoutai(waza);
        }
    }
}

void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon* poke,u16 id) {
    if (poke != nullptr) {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
        if (fightWazaCheckWriteJoutaiDataId(waza,id) == 2) fightWazaWriteJoutaiDataId(waza,id,0);
    }
}

void fightOutPokemon_SetWazaCritical(FightOutPokemon* poke,u8 value) {
    if (poke != nullptr) fightWaza_SetCritical(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetWazaDamageValue(FightOutPokemon* poke,u8 value) {
    if (poke != nullptr) fightWaza_SetDamageValue(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetMotoWazaDataId(FightOutPokemon* poke,u16 value) {
    if (poke != nullptr) fightWaza_SetMotoWazaDataId(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetUseWazaDataId(FightOutPokemon* poke,u16 value) {
    if (poke != nullptr) fightWaza_SetUseWazaDataId(fightOutPokemon_GetFightWazaPtr(poke),value);
}

void fightOutPokemon_SetFightPokemonPtr(FightOutPokemon* poke, FightPokemon* value) {
    if (poke != nullptr) poke->fightPokemon = value;
}

void fightOutPokemon_SetMotoFightPokemonPtr(FightOutPokemon* poke, FightPokemon* value) {
    if (poke != nullptr) poke->motoFightPokemon = value;
}

void fightPokemon_SetAiDamage(FightPokemon* poke,u16 index,u16 target,s32 value) {
    if (poke != nullptr && index < 64) poke->state.aiDamage[index][target] = value;
}

void fightPokemon_SetHokakuFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.hokakuFlag = value;
}

void fightPokemon_SetDarkOutFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.darkOutFlag = value;
}

void fightPokemon_SetLevelUpFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.levelUpFlag = value;
}

void fightPokemon_SetCatchEntryFlag(FightPokemon* poke, u8 value) {
    if (poke != nullptr) poke->state.catchEntryFlag = value;
}

void fightPokemon_SetEntryId(FightPokemon* poke, s16 value) {
    if (poke != nullptr) poke->state.entryId = value;
}

void fightPokemon_SetMotoPokemonPtr(FightPokemon* poke, Pokemon* value) {
    if (poke != nullptr) poke->motoPokemon = value;
}

void pokemon_SetComboPartnerAll(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->comboPartnerAll = data;
    }
}

void pokemon_SetPoolFriend(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        if (data > 0xFF) {
            data = 0xFF;
        }
        poke->setPoolFriendLevel(data);
    }
}

void pokemon_SetPoolExp(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->setPoolExp(data);
    }
}

void pokemon_SetDarkpokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->darkPokemonDataID = data;
    }
}

void pokemon_SetFightTrainerPokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->fightTrainerPokemonDataId = data;
    }
}

void pokemon_SetAmari(Pokemon* poke, u16 data) {
    pokemonBiosSetAmari(poke, data);
}

void pokemon_SetPara1Amari(Pokemon* poke, u16 data) {
    pokemonBiosSetPara1Amari(poke, data);
}

void pokemon_SetMailId(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->mailId = data;
    }
}

void pokemon_SetPcboxMark(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->pcboxMark = data;
    }
}

void pokemon_SetFlagAmari(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flagAmari = data;
    }
}

void pokemon_SetFuseiFlag(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flags.bits.fusei = data;
    }
}

void pokemon_SetTokuseiFlag(Pokemon* poke,u32 value) {
    if (poke != nullptr) {
        PokemonData* data = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke));
        if (pokemonDataBiosGetTokuseiDataId(data,1) == 0) value = 0;
        poke->flags.bits.tokusei = value;
    }
}

void pokemon_SetTamagoFlag(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->flags.bits.tamago = data;
    }
}

void pokemon_SetPokerus(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->pokerus = data;
    }
}

void pokemon_SetStrongMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->strong = data;
        }
    }
}

void pokemon_SetCleverMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->clever = data;
        }
    }
}

void pokemon_SetCuteMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->cute = data;
        }
    }
}

void pokemon_SetBeautifulMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->beautiful = data;
        }
    }
}

void pokemon_SetStyleMedal(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 1);
        if (status != nullptr) {
            status->style = data;
        }
    }
}

void pokemon_SetAmariRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.amari = data;
        }
    }
}

void pokemon_SetWorldRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.world = data;
        }
    }
}

void pokemon_SetEarthRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.earth = data;
        }
    }
}

void pokemon_SetNationalRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.national = data;
        }
    }
}

void pokemon_SetCountryRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.country = data;
        }
    }
}

void pokemon_SetSkyRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.sky = data;
        }
    }
}

void pokemon_SetLandRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.land = data;
        }
    }
}

void pokemon_SetMarineRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.marine = data;
        }
    }
}

void pokemon_SetGanbaRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.ganba = data;
        }
    }
}

void pokemon_SetBromideRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.bromide = data;
        }
    }
}

void pokemon_SetVictoryRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.victory = data;
        }
    }
}

void pokemon_SetWinningRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.winning = data;
        }
    }
}

void pokemon_SetChampRibbon(Pokemon* poke, u8 data) {
    if (poke) {
        Ribbon* ribbon = pokemonBiosGetRibbonPtr(poke);
        if (ribbon != nullptr) {
            ribbon->bits.champ = data;
        }
    }
}

void pokemon_SetFur(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->fur = data;
    }
}

void pokemon_SetStrong(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->strong = data;
        }
    }
}

void pokemon_SetClever(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->clever = data;
        }
    }
}

void pokemon_SetCute(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->cute = data;
        }
    }
}

void pokemon_SetBeautiful(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->beautiful = data;
        }
    }
}

void pokemon_SetStyle(Pokemon* poke, u8 data) {
    if (poke) {
        ExpandStatus* status = pokemonBiosGetExpandStatusPtr(poke, 0);
        if (status != nullptr) {
            status->style = data;
        }
    }
}

void pokemon_SetFriend(Pokemon* poke, u16 data) {
    if (poke) {
        if (data > 0xFF) {
            data = 0xFF;
        }
        poke->friendLevel = data;
    }
}

void pokemon_SetNimblenessRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetNimblenessRnd(poke, data);
}

void pokemon_SetSpeDefRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDefRnd(poke, data);
}

void pokemon_SetSpeAtkRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtkRnd(poke, data);
}

void pokemon_SetPhyDefRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDefRnd(poke, data);
}

void pokemon_SetPhyAtkRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtkRnd(poke, data);
}

void pokemon_SetMaxHpRnd(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHpRnd(poke, data);
}

void pokemon_SetNimblenessEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetNimblenessEffort(poke, data);
}

void pokemon_SetSpeDefEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDefEffort(poke, data);
}

void pokemon_SetSpeAtkEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtkEffort(poke, data);
}

void pokemon_SetPhyDefEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDefEffort(poke, data);
}

void pokemon_SetPhyAtkEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtkEffort(poke, data);
}

void pokemon_SetMaxHpEffort(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHpEffort(poke, data);
}

void pokemon_SetNimbleness(Pokemon* poke, u16 data) {
    pokemonBiosSetNimbleness(poke, data);
}

void pokemon_SetSpeDef(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeDef(poke, data);
}

void pokemon_SetSpeAtk(Pokemon* poke, u16 data) {
    pokemonBiosSetSpeAtk(poke, data);
}

void pokemon_SetPhyDef(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyDef(poke, data);
}

void pokemon_SetPhyAtk(Pokemon* poke, u16 data) {
    pokemonBiosSetPhyAtk(poke, data);
}

void pokemon_SetMaxHp(Pokemon* poke, u16 data) {
    pokemonBiosSetMaxHp(poke, data);
}

void pokemon_SetHp(Pokemon* poke, u16 data) {
    if (poke) {
        poke->hp = data;
        u16 maxHp = pokemonBiosGetMaxHp(poke);
        if (maxHp < poke->hp) {
            poke->hp = maxHp;
        }
    }
}

void pokemon_SetItemDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->itemDataID = data;
    }
}

void pokemon_SetPokemonWazaPpCount(Pokemon* poke,u16 index,u8 count) {
    if (poke != nullptr) {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke,index,0);
        if (waza != nullptr) {
            if (count > 3) count = 3;
            if (pokemonWazaCheckValid(poke,index) == 1) {
                u8 pp = wazaDataBiosGetPp(wazaDataBiosGetPtr(pokemonBiosGetPokemonWazaDataId(poke,index)));
                if (pp <= 4) return;
            }
            waza->ppCount = count;
        }
    }
}

void pokemon_SetPokemonWazaPp(Pokemon* poke, u16 wazaNum, u8 data) {
    if (poke != nullptr)
    {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
        if (waza)
        {
            u8 maxPp = pokemonWazaGetMaxPP(poke, wazaNum);
            if (maxPp < data) {
                data = maxPp;
            }

            waza->pp = data;
        }
    }
}

void pokemon_SetPokemonWazaDataId(Pokemon* poke, u16 wazaNum, u16 data) {
    if (poke != nullptr)
    {
        PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 0);
        if (waza)
        {
            waza->dataId = data;
        }
    }
}

void pokemon_SetConditionAmari(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->conditionAmari = data;
    }
}

void pokemon_SetLevel(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        if (data <= 100)
        {
            poke->level = data;
        }
    }
}

void pokemon_SetExp(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->exp = data;
    }
}

void pokemon_SetNicknamePtr(Pokemon* poke,u16* name) {
    if (poke == nullptr || name == nullptr) return;
    GScharLenCpy(reinterpret_cast<u16*>(poke->nickname),name,11);
    pokemonBiosSetNicknameOrgPtr(poke,name);
}

void pokemon_SetCatchTrainerNamePtr(Pokemon* poke,u16* name) {
    if (poke == nullptr || name == nullptr) return;
    GScharLenCpy(reinterpret_cast<u16*>(poke->catchTrainerName),name,11);
}

void pokemon_SetCatchTrainerRnd(Pokemon* poke,u32 value) {
    if (poke != nullptr) poke->catchTrainerRnd = value;
}

void pokemon_SetCatchTrainerSex(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchTrainerSex = data;
    }
}

void pokemon_SetCatchBallId(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchBallId = data;
    }
}

void pokemon_SetCatchLevel(Pokemon* poke, u8 data) {
    if (poke != nullptr)
    {
        poke->catchLevel = data;
    }
}

void pokemon_SetCatchFloorId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->catchFloorId = data;
    }
}

void pokemon_SetRnd(Pokemon* poke, u32 data) {
    if (poke != nullptr)
    {
        poke->rnd = data;
    }
}

void pokemon_SetPokemonDataId(Pokemon* poke, u16 data) {
    if (poke != nullptr)
    {
        poke->dataID = data;
    }
}

void pokemonDB_SetTukamaetaFlag(u32 id,bool value) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data != nullptr) GSflagSet(data->tukamaetaFlag,value);
}

void pokemonDB_SetMitaFlag(u32 id,bool value) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data != nullptr) GSflagSet(data->mitaFlag,value);
}

u8 fightOutPokemon_GetFixAiDef(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->fixAiDef;
}

u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->fixAiWaza;
}

u8 fightOutPokemon_GetComboFuncId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->comboFuncId;
}

u16 fightOutPokemon_GetOumuWazaAllyDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->oumuWazaAllyDataId;
}

FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 4) return nullptr;
    return &poke->enemy[index];
}

int fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon* poke) {
    if (poke == nullptr) return -1;
    return poke->irekaeTargetEntryId;
}

u8 fn_80148688(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->unknown861;
}

u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->kizetuFlag;
}

int fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->myselfDamageSpeValue;
}

int fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->myselfDamageAtkValue;
}

s32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->kaigaraDamageValue;
}

u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->itemKoraetaFlag;
}

u8 fightOutPokemon_GetIrekaetaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->irekaetaFlag;
}

u8 fightOutPokemon_GetNoPressureFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->noPressureFlag;
}

u8 fightOutPokemon_GetDoTraceFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->doTraceFlag;
}

u8 fightOutPokemon_GetDoIkakuFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->doIkakuFlag;
}

u8 fightOutPokemon_GetVanishoffFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->vanishoffFlag;
}

u8 fightOutPokemon_GetReceivesWazaHiraishinFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->receivesWazaHiraishinFlag;
}

u8 fightOutPokemon_GetDoClearbodyFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->doClearbodyFlag;
}

u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->fightActionFlag;
}

u8 fightOutPokemon_GetPassPpdecFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->passPpdecFlag;
}

u8 fightOutPokemon_GetTameWazaFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->tameWazaFlag;
}

u8 fightOutPokemon_GetKonranMyselfAttackFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->konranMyselfAttackFlag;
}

u16 fightOutPokemon_GetDamageSpeTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->damageSpeTargetId;
}

int fightOutPokemon_GetDamageSpeValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->damageSpeValue;
}

u16 fightOutPokemon_GetDamageAtkTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->damageAtkTargetId;
}

int fightOutPokemon_GetDamageAtkValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->damageAtkValue;
}

u32* fightOutPokemon_GetWazaMenuCurPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->wazaMenuCur;
}

u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->tokuseiDataId;
}

u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon* poke,u8 index) {
    if (poke == nullptr) return 0;
    if (index >= 2) return 0;
    return poke->zokuseiDataId[index];
}

FightActionBuff* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->fightActionBuff;
}

int fightOutPokemon_GetMeetEnemyFightPokemonEntryId(FightOutPokemon* poke,u8 index) {
    if (poke == nullptr) return -1;
    if (index >= 12) return -1;
    return poke->meetEnemyFightPokemonEntryId[index];
}

u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->successCnt;
}

u16 fightOutPokemon_GetStockItemDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->stockItemDataId;
}

u16 fightOutPokemon_GetUsedItemDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->usedItemDataId;
}

u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->namakeFlag;
}

FightWaza* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->keepFightWaza;
}

u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->oumuWazaDataId;
}

u16 fightOutPokemon_GetGamanDamageTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->gamanDamageTargetId;
}

int fightOutPokemon_GetGamanDamageValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->gamanDamageValue;
}

u16 fightOutPokemon_GetHitWazaZokuseiDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 9;
    return poke->hitWazaZokuseiDataId;
}

u16 fightOutPokemon_GetHitWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->hitWazaDataId;
}

u16 fightOutPokemon_GetLastReceiveWazaTargetDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->lastReceiveWazaTargetDataId;
}

u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->lastUseWazaDataId;
}

u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->lastSelectWazaDataId;
}

u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->sketchWazaDataId;
}

void* fightOutPokemon_GetSequencePtr(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->sequence;
}

u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->fightoutTurnCount;
}

u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntAvoid;
}

u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntAverage;
}

u8 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntNimbleness;
}

u8 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntSpeDef;
}

u8 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntSpeAtk;
}

u8 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntPhyDef;
}

u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->abicntPhyAtk;
}

FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->fightItem;
}

s32 fightOutPokemon_GetHitDamage(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetHitDamage(waza);
}

u16 fightOutPokemon_GetTargetId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetTargetDataId(waza);
}

u16 fightOutPokemon_GetIryoku(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetIryoku(waza);
}

s32 fightOutPokemon_GetDamage(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetDamage(waza);
}

u8 fightOutPokemon_GetIsHit(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWazaIsHit(waza);
}

u8 fightOutPokemon_GetJoutaiDataId(FightOutPokemon* poke,u16 id) {
    if (poke == nullptr) return 0;
    return fightWazaIsJoutaiDataId(fightOutPokemon_GetFightWazaPtr(poke),id);
}

u8 fightOutPokemon_GetCritical(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetCritical(waza);
}

u8 fightOutPokemon_GetDamageValue(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    return fightWaza_GetDamageValue(waza);
}

u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 0;
    return fightWaza_GetMotoWazaDataId(waza);
}

u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    FightWaza* waza = fightOutPokemon_GetFightWazaPtr(poke);
    if (waza == nullptr) return 0;
    return fightWaza_GetUseWazaDataId(waza);
}

FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->fightWaza;
}

FightJoutai* fightOutPokemon_GetFightoutJoutaiPtr(FightOutPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 52) return nullptr;
    return &poke->joutai[index];
}

FightPokemon* fightOutPokemon_GetFightPokemonHensinBuffPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->fightPokemonHensinBuff;
}

FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->fightPokemon;
}

FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->motoFightPokemon;
}

u8 fightPokemon_GetHokakuFlag(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->state.hokakuFlag;
}

u8 fightPokemon_GetDarkOutFlag(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->state.darkOutFlag;
}

u8 fightPokemon_GetLevelUpFlag(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->state.levelUpFlag;
}

u8 fightPokemon_GetCatchEntryFlag(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->state.catchEntryFlag;
}

int fightPokemon_GetEntryId(FightPokemon* poke) {
    if (poke == nullptr) return -1;
    return poke->state.entryId;
}

FightJoutai* fightPokemon_GetFightJoutaiPtr(FightPokemon* poke,u16 index) {
    if (poke == nullptr) return nullptr;
    if (index >= 1) return nullptr;
    return &poke->state.joutai[index];
}

Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon* poke) {
    if (poke == nullptr) return nullptr;
    return &poke->pokemonBuff;
}

Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon* poke) {
    if (poke == nullptr) return 0;
    return poke->motoPokemon;
}

u8 pokemon_GetComboPartner(Pokemon* poke,u8 slot,u8 side) {
    if (poke == nullptr) return 0;
    switch (static_cast<int>(side)) {
    case 0:
        switch (static_cast<int>(slot)) {
        case 0: return (poke->comboPartnerAll >> 6) & 1;
        case 1: return (poke->comboPartnerAll >> 4) & 1;
        case 2: return (poke->comboPartnerAll >> 2) & 1;
        case 3: return poke->comboPartnerAll & 1;
        default: return 0;
        }
    case 1:
        switch (static_cast<int>(slot)) {
        case 0: return (poke->comboPartnerAll >> 7) & 1;
        case 1: return (poke->comboPartnerAll >> 5) & 1;
        case 2: return (poke->comboPartnerAll >> 3) & 1;
        case 3: return (poke->comboPartnerAll >> 1) & 1;
        default: return 0;
        }
    default: return 0;
    }
}

bool pokemon_GetDarkFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return false;
    }
    return poke->isDarkPokemon();
}

u16 pokemon_GetPoolFriend(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolFriendLevel();
}

u32 pokemon_GetPoolExp(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->getPoolExp();
}

u16 pokemon_GetInitDp(Pokemon* poke) {
    if (poke == nullptr) return 0;
    u16 id = pokemonBiosGetDarkpokemonDataId(poke);
    if (id == 0) return 0;
    return darkPokemonBiosGetDarkPoint(id);
}

u16 pokemon_GetDarkpokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->darkPokemonDataID;
}

u16 pokemon_GetFightTrainerPokemonDataId(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->fightTrainerPokemonDataId;
}

u8 pokemon_GetNowExpToLevel(Pokemon* poke) {
    if (poke == nullptr) return 0;
    u8 grow = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(poke));
    u32 exp = pokemon_GetExp(poke);
    return pokemonGetExpToLevel(grow,exp);
}

u8 pokemon_GetSeikaku(Pokemon* poke) {
    if (poke == nullptr) return 0;
    return pokemonGetSeikakuAsRnd(pokemon_GetRnd(poke));
}

bool pokemon_GetFuseiFlag(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return poke->flags.bits.fusei;
}

u8 pokemon_GetTokuseiFlag(Pokemon* poke) {
    if (poke == nullptr) return 0;
    PokemonData* data = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke));
    if (pokemonDataBiosGetTokuseiDataId(data,1) == 0) return 0;
    return poke->flags.bits.tokusei != 0;
}

bool pokemon_GetTamagoFlag(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->flags.bits.tamago;
}

u8 pokemon_GetPokerus(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->pokerus;
}

u16 pokemon_GetFriend(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->friendLevel;
}

u8 pokemon_GetNimblenessRnd(Pokemon* poke) {
    return pokemonBiosGetNimblenessRnd(poke);
}

u8 pokemon_GetSpeDefRnd(Pokemon* poke) {
    return pokemonBiosGetSpeDefRnd(poke);
}

u8 pokemon_GetSpeAtkRnd(Pokemon* poke) {
    return pokemonBiosGetSpeAtkRnd(poke);
}

u8 pokemon_GetPhyDefRnd(Pokemon* poke) {
    return pokemonBiosGetPhyDefRnd(poke);
}

u8 pokemon_GetPhyAtkRnd(Pokemon* poke) {
    return pokemonBiosGetPhyAtkRnd(poke);
}

u8 pokemon_GetMaxHpRnd(Pokemon* poke) {
    return pokemonBiosGetMaxHpRnd(poke);
}

u16 pokemon_GetNimbleness(Pokemon* poke) {
    return pokemonBiosGetNimbleness(poke);
}

u16 pokemon_GetSpeDef(Pokemon* poke) {
    return pokemonBiosGetSpeDef(poke);
}

u16 pokemon_GetSpeAtk(Pokemon* poke) {
    return pokemonBiosGetSpeAtk(poke);
}

u16 pokemon_GetPhyDef(Pokemon* poke) {
    return pokemonBiosGetPhyDef(poke);
}

u16 pokemon_GetPhyAtk(Pokemon* poke) {
    return pokemonBiosGetPhyAtk(poke);
}

u16 pokemon_GetMaxHp(Pokemon* poke) {
    return pokemonBiosGetMaxHp(poke);
}

u16 pokemon_GetHp(Pokemon* poke) {
    if (poke == 0) {
        return 0;
    }
    return poke->hp;
}

u16 pokemon_GetItemDataId(Pokemon* poke) {
    if (poke == 0) {
        return 0;
    }
    return poke->itemDataID;
}

u8 pokemon_GetPokemonWazaPpCount(Pokemon* poke, u16 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->ppCount;
}

u8 pokemon_GetPokemonWazaPp(Pokemon* poke, u16 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->pp;
}

u16 pokemon_GetPokemonWazaDataId(Pokemon* poke, u16 wazaNum) {
    if (poke == nullptr) {
        return 0;
    }

    PokemonWaza* waza = pokemonBiosGetPokemonWazaPtr(poke, wazaNum, 1);
    if (waza == nullptr) {
        return 0;
    }
    return waza->dataId;
}

u16 pokemon_GetHinsi(Pokemon* poke) {
    if (poke == nullptr) {
        return 0;
    }
    return pokemon_GetHp(poke) == 0;
}

u8 pokemon_GetLevel(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->level;
}

u32 pokemon_GetExp(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->exp;
}

char* pokemon_GetNicknamePtr(Pokemon* poke) {
    if (poke == nullptr)
    {
        return nullptr;
    }
    return &poke->nickname[0];
}

u32 pokemon_GetCatchTrainerRnd(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->catchTrainerRnd;
}

u8 pokemon_GetCatchBallId(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->catchBallId;
}

Attest* pokemon_GetAttest(Pokemon* poke) {
    if (poke == nullptr)
    {
        return nullptr;
    }
    return &poke->attest;
}

u32 pokemon_GetRnd(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->rnd;
}

u32 pokemon_GetPokemonDataId(Pokemon* poke) {
    if (poke == nullptr)
    {
        return 0;
    }
    return poke->dataID;
}

u32 pokemonDB_GetPkxDataId(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->pkxDataId;
}

bool pokemonDB_GetTukamaetaFlag(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return false;
    return GSflagGet(data->tukamaetaFlag);
}

u16 pokemonDB_GetShout(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->shout;
}

u16 pokemonDB_GetVoice(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->voice;
}

u16 pokemonDB_GetWeight(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->weight;
}

u32 pokemonDB_GetPokebodyId(u32 id,u16 index) {
    PokemonDataCgData* record = pokemonDataBiosGetCgDataPtr(pokemonDataBiosGetPtr(id),index);
    if (record == nullptr) return 0;
    return record->pokebodyId;
}

u8 pokemonDB_GetTeachWaza(u32 id,u16 index) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    if (index >= 12 || static_cast<int>(index) <= -1) return 0;
    return data->teachWaza[index] != 0;
}

u16 pokemonDB_GetGetWazaDataId(u32 id,u16 index) {
    PokemonDataWaza* record = pokemonDataBiosGetGetWazaPtr(pokemonDataBiosGetPtr(id),index);
    if (record == nullptr) return 0;
    return record->dataId;
}

u8 pokemonDB_GetGetWazaLevel(u32 id,u16 index) {
    PokemonDataWaza* record = pokemonDataBiosGetGetWazaPtr(pokemonDataBiosGetPtr(id),index);
    if (record == nullptr) return 0;
    return record->level;
}

u32 pokemonDB_GetTokuseiDataId(u32 id,u16 index) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    if (index >= 2) return 0;
    return data->tokuseiDataId[index];
}

u8 pokemonDB_GetZokuseiDataId(u32 id,u16 index) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    if (index >= 2) return 0;
    return data->zokuseiDataId[index];
}

u16 pokemonDB_GetItemDataId(u32 id,u16 index) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    if (index >= 2) return 0;
    return data->itemDataId[index];
}

u16 pokemonDB_GetInitFriend(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->initFriend;
}

u8 pokemonDB_GetSexRatio(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->sexRatio;
}

u8 pokemonDB_GetGet(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->get;
}

u8 pokemonDB_GetGrowDataId(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->growDataId;
}

u16 pokemonDB_GetGiveExp(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return 0;
    return data->giveExp;
}

u16 pokemonDB_GetBasisNimbleness(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->nimbleness;
}

u16 pokemonDB_GetBasisSpeDef(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->speDef;
}

u16 pokemonDB_GetBasisSpeAtk(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->speAtk;
}

u16 pokemonDB_GetBasisPhyDef(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->phyDef;
}

u16 pokemonDB_GetBasisPhyAtk(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->phyAtk;
}

u16 pokemonDB_GetBasisMaxHp(u32 id) {
    BasisStatus* status = pokemonDataBiosGetBasisStatusPtr(pokemonDataBiosGetPtr(id),0);
    if (status == nullptr) return 0;
    return status->maxHp;
}

const char16* pokemonDB_GetName(u32 id) {
    PokemonData* data = pokemonDataBiosGetPtr(id);
    if (data == nullptr) return nullptr;
    return reinterpret_cast<const char16*>(data->name);
}

}
