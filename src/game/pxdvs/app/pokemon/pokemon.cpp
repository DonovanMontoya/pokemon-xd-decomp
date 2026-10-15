#include <game/pxdvs/app/pokemon/pokemon.hpp>
#include <game/pxdvs/app/pokemon/pokemonStatusDispatch.hpp>
#include <game/pxdvs/app/pokemon/pokemonPrivate.hpp>

//TODO this is simply a first pass through this class many things might need changed and or cleaned up even if the function already matches
const f32 zero = 0.0f;
const f32 oneHundred = 100.0f;
const f32 nintyNinePointNine = 99.9f;
const f32 eighty = 80.0f;
const f32 sixty = 60.0f;
const f32 fourty = 40.0f;
const f32 twenty = 20.0f;
const f64 unkDouble = 4503599627370496.0;
const f32 negOne = -1.0f;
const f32 negThree = -3.0f;
const f64 unkDouble2 = 4503601774854144.0;

struct PokemonEffortEntry {
    u16 effortStat;
    u16 giveProperty;
    u16 value;
};

extern "C" {
void pokemonGetEffortFromPokemon(Pokemon* poke, u16 itemEffect, u8 doubleFlag, u32 species)
{
    PokemonEffortEntry table[6] = {{0x8D, 0x0A, 0}, {0x8E, 0x0B, 0}, {0x8F, 0x0C, 0}, {0x90, 0x0D, 0}, {0x91, 0x0E, 0}, {0x92, 0x0F, 0}};
    if (poke && pokemonCheckFightOut(poke)) {
        s32 multiplier = 1;
        u32 total = 0;
        {
            u8 i;
            for (i = 0; i < 6; i++) {
                PokemonEffortEntry* entry = &table[i];
                entry->value = pokemonGetStatus(poke, 0, entry->effortStat, 0);
                total += entry->value;
            }
        }
        if (doubleFlag == 1) multiplier = 2;
        {
            u32 m = (u8)multiplier;
            u32 item = itemEffect;
            u8 j;
            for (j = 0; j < 6; j++) {
                PokemonEffortEntry* entry;
                u16 gain;
                if ((u16)total >= 0x1FE) break;
                entry = &table[j];
                gain = m * (u16)pokemonGetStatus(0, species, entry->giveProperty, 0);
                if (item == 0x18) gain = gain << 1;
                if ((u16)total + gain > 0x1FE) gain = gain - ((u16)total + gain - 0x1FE);
                if (gain + entry->value > 0xFF) gain = gain - (gain + entry->value - 0xFF);
                total += gain;
                entry->value = entry->value + gain;
                pokemonSetStatus(poke, 0, entry->effortStat, 0, entry->value);
            }
        }
    }
}
}

const u8 lbl_802F374C[12] = {0x00, 0x3E, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xFF};

extern "C" {
u32 fightOutPokemon_GetKanseiSndId(void* fightOut)
{
    return pokemonDB_GetShout(figthOutPokemonGetPokemonDataId(fightOut));
}

u32 pokemonGetWazaCount(Pokemon* poke)
{
    s32 i;
    s32 count = 0;
    if (!pokemonCheckValid(poke)) return 0;
    for (i = 0; i < 4; i++) {
        if (pokemonWazaCheckValid(poke, i)) count++;
    }
    return count;
}

void pokemonWazaForget(Pokemon* poke, u16 index)
{
    s32 next;
    u16 i;
    pokemonWazaInit(poke, index);
    for (i = index; i < 3; i++) {
        next = i + 1;
        if (!pokemonWazaCheckValid(poke, next)) break;
        pokemonWazaCopy(poke, i, next);
    }
    pokemonWazaInit(poke, i);
}

void pokemonWazaCopy(Pokemon* poke, u16 dst, u16 src)
{
    if (poke) {
        PokemonWaza* to = pokemonBiosGetPokemonWazaPtr(poke, dst, 0);
        PokemonWaza* from = pokemonBiosGetPokemonWazaPtr(poke, src, 0);
        pokemonWazaBiosCopy(to, from);
    }
}

void pokemonPlayVoice(Pokemon* poke)
{
    if (poke) {
        PokemonData* data = pokemonDataBiosGetPtr(pokemonBiosGetPokemonDataId(poke));
        if (data) GSsndPlay(pokemonDataBiosGetVoice(data), 0, 0);
    }
}

u32 pokemonGetDarkPokemonCallKakuritu()
{
    return 100;
}

bool pokemonCheckSetMonohiroi(Pokemon* poke)
{
    u32 roll;
    u16 found;
    u16 commonItems[18] = {0x0D, 0x0E, 0x16, 0x03, 0x12, 0x0F, 0x4B, 0x17, 0x02, 0x15, 0x44, 0x40, 0x18, 0x3F, 0x13, 0x19, 0x45, 0x25};
    u16 rareItems[11] = {0x15, 0x6E, 0xBB, 0x13, 0x22, 0xB4, 0x14C, 0x24, 0x121, 0xC8, 0x13A};
    u8 chance[9] = {30, 40, 50, 60, 70, 80, 90, 94, 98};
    if ((u16)pokemonGetTokuseiDataId(poke) == 0x35) {
        if ((u16)pokemonGetSoubiItemDataId(poke) == 0) {
            if ((u16)HSD_Rand() % 10 == 0) {
                u16 index;
                u8 tier;
                roll = (u16)HSD_Rand() % 100;
                found = 0;
                tier = (pokemon_GetLevel(poke) - 1) / 10;
                if (tier >= 10) tier = 9;
                for (index = 0; index < 9; index++) {
                    if (chance[index] > roll) {
                        found = commonItems[tier + index];
                        break;
                    }
                    if (roll >= 98 && roll <= 99) {
                        found = rareItems[tier + (99 - roll)];
                        break;
                    }
                }
                if (found != 0) {
                    pokemonDoItemSoubi(poke, found, 1);
                    return 1;
                }
            }
        }
    }
    return 0;
}

u32 pokemonGetDarkPokemonHyperJoutaiKakuritu(Pokemon* poke)
{
    u8 table[5][5] = {{0, 0, 0, 0, 0}, {10, 10, 10, 5, 2}, {20, 15, 15, 10, 5}, {35, 25, 20, 15, 10}, {50, 40, 30, 20, 15}};
    u8 level;
    u8 revers;
    revers = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(poke))->getReversPattern();
    level = pokemonGetDarkPokemonLevel(poke);
    if (!poke) return 0;
    if (!pokemonIsDarkPokemon(poke)) return 0;
    if (level > 4) level = 4;
    if (revers > 4) revers = 4;
    if (level <= 4 && revers < 5) return table[level][revers];
    return 0;
}

u8 pokemonGetDarkPokemonLevel(Pokemon* poke)
{
    u32 initDp;
    if (!poke) return 7;
    if (pokemonIsDarkPokemon(poke) == 1) {
        initDp = pokemon_GetInitDp(poke);
        if ((u16)initDp == 0) initDp = 1;
        f32 dp = pokemonGetDp(poke);
        f32 ratio;
        if (dp < 0.0f) ratio = 0.0f;
        else ratio = 100.0f * dp / (f32)(u16)initDp;
        if (ratio >= 99.9f) return 0;
        if (ratio >= 80.0f) return 1;
        if (ratio >= 60.0f) return 2;
        if (ratio >= 40.0f) return 3;
        if (ratio >= 20.0f) return 4;
        if (ratio > 0.0f) return 5;
        if (ratio == 0.0f) return 6;
        return 7;
    }
    return 7;
}

void pokemonAddDpFormPokemonDpFilterId(Pokemon* poke, u16 itemId, u16 filterId)
{
    f32 dp;
    s32 relive = 0;
    if (pokemonIsDarkPokemon(poke)) {
        PokemonSeikakuDataBios* seikaku = pokemonSeikakuDataBiosGetPtr(pokemon_GetSeikaku(poke));
        if (seikaku) {
            dp = (f32)(s8)pokemonDpFilterDataBiosGetValue(pokemonDpFilterDataBiosGetPtr(filterId));
            if (filterId == 4) {
                ItemDataBios* item = itemDataBiosGetPtr(itemId);
                if (!item) return;
                if (itemDataBiosGetKind(item) != 6) return;
                dp *= (f32)itemDataBiosGetBuff(item);
            }
            if (filterId == 5) dp = -1.0f * pokemonGetDp(poke);
            if (filterId == 0) relive = pokemonSeikakuDataBiosGetReliveFightout(seikaku);
            else if (filterId == 1) relive = pokemonSeikakuDataBiosGetReliveWalk(seikaku);
            else if (filterId == 3) relive = pokemonSeikakuDataBiosGetReliveSodateya(seikaku);
            else if (filterId == 4) relive = pokemonSeikakuDataBiosGetReliveNadenade(seikaku);
            else if (filterId == 2) {
                dp = -3.0f;
                relive = pokemonSeikakuDataBiosGetReliveCall(seikaku);
            }
            if ((s8)relive != 0) {
                relive = (s32)pokemonSeikakuRateDataBiosGetPtr((u8)relive);
                if (!relive) return;
                u32 kake = pokemonSeikakuRateDataBiosGetKake((PokemonSeikakuRateBios*)relive);
                u8 waru = pokemonSeikakuRateDataBiosGetWaru((PokemonSeikakuRateBios*)relive);
                if (waru != 0) {
                    dp *= (f32)(u8)kake;
                    dp /= (f32)waru;
                } else {
                    return;
                }
            }
            dp *= 100.0f;
            pokemonAddDp(poke, dp);
        }
    }
}

void pokemonAddDp(Pokemon* poke, f32 delta)
{
    if (poke) {
        f32 dp = pokemonGetDp(poke);
        dp += delta;
        if (dp < 0.0f) dp = 0.0f;
        pokemonSetDp(poke, dp);
    }
}

void pokemonSetDp(Pokemon* poke, f32 dp)
{
    if (poke) pokemonBiosSetDp(poke, (s32)dp);
}

f32 pokemonGetDp(Pokemon* poke)
{
    return poke == 0 ? 0.0f : (f32)pokemonBiosGetDp(poke);
}

u8 pokemonIsDarkPokemon(Pokemon* poke)
{
    return pokemon_GetDarkFlag(poke);
}

void pokemonSetDarkPokemonStatus(Pokemon* poke, u16 darkId)
{
    u8 index;
    u32 i;
    if (poke) {
        pokemonInitDarkPokemon(poke);
        pokemon_SetDarkpokemonDataId(poke, darkId);
        pokemonSetDp(poke, (f32)(u16)darkPokemonBiosGetDarkPoint(darkId));
        for (i = 0; (u8)i < 4; i++) {
            index = i;
            pokemonWazaCreate(poke, index, 0x176);
            u16 waza = darkPokemonBiosGetTemotiDarkWaza(darkId, index);
            if (waza != 0 && waza != 0x176) pokemonWazaCreate(poke, index, waza);
        }
        poke->setReversMode(false);
        DarkPokemon* dark = poke->getDarkPokemon();
        if (dark) dark->setDarkPokemonID(darkId);
    }
}

bool pokemonDataCheckValid(void* unused, u32 idArg)
{
    u16 id = idArg;
    bool result;
    if (id == 0) result = false;
    else if (!pokemonDB_GetName(id)) result = false;
    else result = id < *pokemon_data_number;
    return result;
}

u32 pokemonGetNowLevelToExp(Pokemon* poke)
{
    u8 grow = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(poke));
    u8 level = pokemon_GetLevel(poke);
    return _pokemonGetLevelToExp(grow, level);
}

s32 pokemonGetTasteLike(Pokemon* poke, u32 tasteId)
{
    u32 seikaku;
    if (!poke) return -1;
    seikaku = pokemon_GetSeikaku(poke);
    return tasteDataGetAisyou(tasteDataGetPtr(tasteId), seikaku);
}

u32 pokemonGetJoutaiMsgId(Pokemon* poke)
{
    u32 result;
    if (!poke) result = 0;
    else if (!poke->getCondition()) result = 0;
    else result = joutaiDataBiosGetName(poke->getCondition());
    return result;
}

u16 pokemonGetJoutaiMenuSpriteId(Pokemon* poke)
{
    s32 i;
    if (!poke) return 0;
    for (i = 0; spriteTbl[i].condition != 0; i++) {
        if (spriteTbl[i].condition == poke->getCondition()) return spriteTbl[i].sprite;
    }
    return 0;
}

u32 pokemonGetJoutaiDataId(Pokemon* poke)
{
    if (poke == 0) {
        return 0;
    } else {
        return poke->getCondition();
    }
}

u8 pokemonIsHpMantan(Pokemon* poke)
{
    u16 hp;
    if (!poke) return 0;
    hp = pokemon_GetHp(poke);
    u16 max = pokemon_GetMaxHp(poke);
    return hp == max;
}

void pokemonCopyJoutaiDataId(Pokemon* dst, Pokemon* src, u16 id)
{
    if (dst) {
        if (!src) return;
        u16 status = joutaiDataBiosGetStatus(id);
        if (status == 200) dst->setReversMode(src->isReversMode());
        else if (status == 0x7c) dst->copyCondition(src);
    }
}

void pokemonSetKaisuuJoutaiDataId(Pokemon* poke, u16 id, u32 kaisuu)
{
    if (poke) {
        if (joutaiDataBiosGetStatus(id) == 0x7c) poke->setConditionTurn(kaisuu);
    }
}

void pokemonSetNowKaisuuJoutaiDataId(Pokemon* poke, u16 id, u32 kaisuu)
{
    if (poke) {
        if (joutaiDataBiosGetStatus(id) == 0x7c) poke->setConditionTurnNow(kaisuu);
    }
}

s8 pokemonGetNowKaisuuJoutaiDataId(Pokemon* poke, u16 id)
{
    if (!poke) return -1;
    if (joutaiDataBiosGetStatus(id) == 0x7c) return poke->getConditionTurnNow();
    return -1;
}

s8 pokemonGetKaisuuJoutaiDataId(Pokemon* poke, u16 id)
{
    if (!poke) return 0;
    if (joutaiDataBiosGetStatus(id) == 0x7c) return poke->getConditionTurn();
    return -1;
}

void pokemonSetCountAsJoutaiDataId(Pokemon* poke, u16 id, u32 count)
{
    if (poke) {
        if (joutaiDataBiosGetStatus(id) == 0x7c) poke->setConditionCount(count);
    }
}

s32 pokemonGetCountAsJoutaiDataId(Pokemon* poke, u16 id)
{
    if (!poke) return -1;
    if (joutaiDataBiosGetStatus(id) == 0x7c) return poke->getConditionCount();
    return -1;
}

void pokemonWriteJoutaiDataId(Pokemon* poke, u16 id)
{
    u32 count;
    u16 status;
    if (poke) {
        status = joutaiDataBiosGetStatus(id);
        if (status == 200) poke->setReversMode(id == 0x3e);
        if (status == 0x7c) {
            count = 0;
            if (id == 4) count = poke->getConditionCount();
            poke->initCondition();
            poke->setCondition(id);
            if (id == 8) poke->setConditionTurn(kaisuuGetKaisuu(joutaiDataBiosGetKaisuuDataId(id)));
            if (id == 4) {
                s32 n = (u8)count + 1;
                if ((u8)joutaiDataBiosGetMaxCount(id) < n) n = (u8)joutaiDataBiosGetMaxCount(id);
                poke->setConditionCount(n);
            }
        }
    }
}

u32 pokemonCheckWriteJoutaiDataId(Pokemon* poke, u16 id)
{
    const u8* p;
    if (!poke) return 1;
    for (p = lbl_802F374C; *p != 0xff; p++) {
        if (id == *p) return 2;
    }
    return 1;
}

bool pokemonIsJoutaiDataId(Pokemon* poke, u16 id)
{
    if (!poke) return 0;
    u16 status = joutaiDataBiosGetStatus(id);
    if (status == 200) {
        u16 expect = poke->isReversMode() ? 0x3e : 0;
        if (id == expect) return 1;
        return 0;
    }
    if (status == 0x7c) return poke->getCondition() == id;
    return 0;
}

void pokemonInitJoutaiDataId(Pokemon* poke, u16 id)
{
    if (poke) {
        u16 status = joutaiDataBiosGetStatus(id);
        if (status == 200) poke->setReversMode(false);
        else if (status == 0x7c) poke->initCondition();
    }
}

u8 pokemonCheckInfectPokerus(Pokemon* poke, u8 flag)
{
    u8 value;
    if (flag == 0) value = pokemon_GetPokerus(poke);
    else value = pokemon_GetPokerus(poke) & 0xf;
    if (value) return 1;
    return 0;
}

void pokemonReplace(Pokemon* a, Pokemon* b)
{
    Pokemon tmp;
    if (a && b) {
        pokemonBiosCopy(&tmp, a);
        pokemonBiosCopy(a, b);
        pokemonBiosCopy(b, &tmp);
    }
}

u8 pokemonGetFightPokemonDeoxysSel(void* fightPokemon)
{
    return pokemonGetDeoxysSel(fightTrainer_GetControllerId(fightFloorGetFightPokemonPtrToFightTrainerPtr(0, fightPokemon)));
}

u8 pokemonGetDeoxysSel(u8 controller)
{
    if (!fightFloor_GetFightKindRegulationFlag(0)) return 0;
    if (!menuCBRule_DEOKISISUCamouflage()) return 0;
    switch (menuGBACGetRomVer((u16)(controller - 1))) {
    case 1:
    case 2: return 0;
    case 3: return 1;
    case 4: return 2;
    case 5: return 3;
    default: return 0;
    }
}

u8 pokemonGetAnnonKatati(u32 rnd)
{
    u32 value = ((rnd >> 18) & 0xC0) | ((rnd >> 12) & 0x30) | ((rnd >> 6) & 0x0C) | (rnd & 3);
    return value % 28;
}

u8 pokemonIsNokoriHpFollowing(Pokemon* poke, u16 divisor)
{
    u16 hp;
    if (divisor == 0) return 0;
    if (!poke) return 0;
    hp = pokemon_GetHp(poke);
    return pokemon_GetMaxHp(poke) / divisor >= hp;
}

u8 pokemonIsJoutaiKaragenki(Pokemon* poke)
{
    if (!poke) return 0;
    if (pokemonIsJoutaiDataId(poke, 3) == 1) return 1;
    if (pokemonIsJoutaiDataId(poke, 5) == 1) return 1;
    if (pokemonIsJoutaiDataId(poke, 6) == 1) return 1;
    return pokemonIsJoutaiDataId(poke, 4) == 1;
}

bool pokemonIsJoutaiNormal(Pokemon* poke)
{
    if (!poke) return 0;
    if (pokemonIsJoutaiDataId(poke, 3) == 1) return 0;
    if (pokemonIsJoutaiDataId(poke, 4) == 1) return 0;
    if (pokemonIsJoutaiDataId(poke, 5) == 1) return 0;
    if (pokemonIsJoutaiDataId(poke, 6) == 1) return 0;
    if (pokemonIsJoutaiDataId(poke, 7) == 1) return 0;
    return pokemonIsJoutaiDataId(poke, 8) != 1;
}

u16 pokemonGetSoubiItemBuff(Pokemon* poke)
{
    u16 item = pokemonGetSoubiItemDataId(poke);
    if (item == 0) return 0;
    if (dbgMenuFightGetSoubikoukaFlag() == 1) {
        u16 soubi = itemDB_GetItemSoubiDataId(item);
        if (soubi == 0x1a || soubi == 0x1e) return 99;
    }
    return itemDB_GetBuff(item);
}

u16 pokemonGetSoubiItemSoubiDataId(Pokemon* poke)
{
    u16 item = pokemonGetSoubiItemDataId(poke);
    if (item == 0) return 0;
    return itemDB_GetItemSoubiDataId(item);
}

u16 pokemonGetSoubiItemDataId(Pokemon* poke)
{
    return pokemon_GetItemDataId(poke);
}

u16 pokemonDoItemSoubi(Pokemon* poke, u16 item, u8 set)
{
    if (!poke) return 0;
    if (set == 0) {
        item = pokemonGetSoubiItemDataId(poke);
        pokemon_SetItemDataId(poke, 0);
    } else {
        pokemon_SetItemDataId(poke, item);
    }
    return item;
}

u8 pokemonGetSex(Pokemon* poke)
{
    if (poke == 0) {
        return 2;
    } else {
        u32 rnd = pokemon_GetRnd(poke);
        return _pokemonGetSexSub(poke, rnd);
    }
}

} // extern "C"

static u8 _pokemonGetSexSub(Pokemon* poke, u32 rnd)
{
    u32 ratio = pokemonDB_GetSexRatio(poke->getPokemonDataId());
    s8 sex = pokemonCheckSexKotei(poke);
    if (sex < 0) {
        if (ratio > (u8)rnd) sex = 1;
        else sex = 0;
    }
    return sex;
}

static void _pokemonWazaCopy(Pokemon* poke, u16 dst, u16 src)
{
    if (poke) {
        PokemonWaza* to = pokemonBiosGetPokemonWazaPtr(poke, dst, 0);
        PokemonWaza* from = pokemonBiosGetPokemonWazaPtr(poke, src, 0);
        pokemonWazaBiosCopy(to, from);
    }
}

extern "C" {
s8 pokemonCheckSexKotei(Pokemon* poke)
{
    s32 ratio;
    if (!poke) return 2;
    ratio = pokemonDB_GetSexRatio(pokemon_GetPokemonDataId(poke));
    if (ratio == sexGetPokemonSexRaitoKotei(0)) return 0;
    if (ratio == sexGetPokemonSexRaitoKotei(1)) return 1;
    if (ratio == sexGetPokemonSexRaitoKotei(2)) return 2;
    return -1;
}

void pokemonSetOnDarkPokemonFlag(Pokemon* poke, u8 flag)
{
    if (poke) {
        if (pokemonIsDarkPokemon(poke)) {
            DarkPokemon* dark = darkPokemonGetDarkPokemon(pokemon_GetDarkpokemonDataId(poke));
            if (dark) {
                if (flag) dark->addStatus(darkStatus3);
                else dark->addStatus(darkStatus1);
            }
        }
    }
}

void pokemonSetOnZukanFlag(Pokemon* poke, u8 caught)
{
    if (poke) {
        pokemon_GetPokemonDataId(poke);
        memoDataSet(0, poke);
        pokemonDB_SetMitaFlag(0, 1);
        if (caught) pokemonDB_SetTukamaetaFlag(0, 1);
    }
}

bool pokemonCheckFightOut(Pokemon* poke)
{
    if (!pokemonCheckValid(poke)) return 0;
    if ((u16)pokemon_GetPokemonDataId(poke) == 0x19c) return 0;
    if (pokemon_GetTamagoFlag(poke) == 1) return 0;
    return pokemon_GetHinsi(poke) != 1;
}

u32 pokemonGetOboeWazaDataBanme(Pokemon* poke, u8 level)
{
    u8 target;
    u32 id;
    u32 i;
    if (poke == 0) return 0;
    id = pokemon_GetPokemonDataId(poke);
    target = level;
    for (i = 0; (u8)i < 20; i++) {
        if (target == pokemonDB_GetGetWazaLevel(id, i & 0xff)) break;
    }
    return i;
}

s32 pokemonOboeWaza(Pokemon* poke, u8 level, u8 slot, u8* counter)
{
    u32 waza;
    if (!poke) return -2;
    waza = pokemonGetOboeWazaDataId(poke, level, counter);
    if ((u16)waza == 0) return -3;
    return pokemonSetWazaStatus(poke, waza, slot);
}

u16 pokemonGetOboeWazaDataId(Pokemon* poke, u8 level, u8* counter)
{
    u32 id;
    u8 target;
    if (poke == 0 || counter == 0) return 0;
    id = pokemon_GetPokemonDataId(poke);
    target = level;
    for (; *counter < 20; (*counter)++) {
        if (target == pokemonDB_GetGetWazaLevel(id, *counter)) return pokemonDB_GetGetWazaDataId(id, *counter);
    }
    return 0;
}

s8 pokemonSearchWazaDataId(Pokemon* poke, u16 dataId)
{
    u32 id;
    s8 index;
    s8 i;
    if (!poke) return -1;
    id = dataId;
    for (i = 0; (s8)i < 4; i++) {
        index = i;
        if (pokemonWazaCheckValid(poke, index) && id == pokemon_GetPokemonWazaDataId(poke, index)) return i;
    }
    return -1;
}

void pokemonWazaReplace(Pokemon* poke, u16 first, u16 second)
{
    PokemonWaza tmp;
    PokemonWaza* a;
    PokemonWaza* b;
    if (poke) {
        a = pokemonBiosGetPokemonWazaPtr(poke, first, 0);
        b = pokemonBiosGetPokemonWazaPtr(poke, second, 0);
        pokemonWazaBiosCopy(&tmp, a);
        pokemonWazaBiosCopy(a, b);
        pokemonWazaBiosCopy(b, &tmp);
    }
}

bool pokemonWazaCheckValid(Pokemon* poke, u16 index)
{
    if (!poke) return 0;
    if (pokemon_GetPokemonWazaDataId(poke, index) == 0) return 0;
    return pokemon_GetPokemonWazaDataId(poke, index) != 0x163;
}

void pokemonWazaCreate(Pokemon* poke, u32 index, u16 dataId)
{
    if (poke) {
        pokemonWazaInit(poke, index);
        pokemon_SetPokemonWazaDataId(poke, index, dataId);
        u8 pp = pokemonWazaGetMaxPP(poke, index);
        pokemon_SetPokemonWazaPp(poke, index, pp);
    }
}

u8 pokemonWazaGetMaxPP(Pokemon* poke, u16 index)
{
    s32 n;
    u16 dataId;
    if (!poke) return 0;
    n = index + 4;
    dataId = pokemon_GetPokemonWazaDataId(poke, n);
    u8 count = pokemon_GetPokemonWazaPpCount(poke, n);
    return wazaGetMaxPP(dataId, count);
}

u8 pokemonWazaGetZokusei(Pokemon* poke, u16 index)
{
    if (poke == 0) {
        return 0;
    } else {
        return wazaDB_GetZokuseiDataId(pokemon_GetPokemonWazaDataId(poke, (u16)(index + 4)));
    }
}

void pokemonSetCatchStatus(Pokemon* poke, u32 floorId, u8 level, u32 ballId, u8 sex, u32 trainerRnd, u16* trainerName)
{
    if (poke) {
        pokemon_SetCatchFloorId(poke, floorId);
        pokemon_SetCatchLevel(poke, level);
        pokemon_SetCatchBallId(poke, ballId);
        pokemon_SetCatchTrainerSex(poke, sex);
        pokemon_SetCatchTrainerRnd(poke, trainerRnd);
        pokemon_SetCatchTrainerNamePtr(poke, trainerName);
    }
}

bool pokemonCheckValid(Pokemon* poke)
{
    u32 id;
    if (poke == 0) return 0;
    id = pokemon_GetPokemonDataId(poke);
    if ((u16)id == 0) return 0;
    if (pokemonDataCheckValid(0, id) == 0) return 0;
    if (gamedataAttestCheckValid(pokemon_GetAttest(poke)) == 0) return 0;
    return pokemon_GetFuseiFlag(poke) != 1;
}

u32 pokemonGetTokuseiDataId(Pokemon* poke)
{
    u32 id;
    if (poke == 0) return 0;
    id = pokemon_GetPokemonDataId(poke);
    if (pokemonDB_GetTokuseiDataId(id, 1) == 0) {
        return pokemonDB_GetTokuseiDataId(id, 0);
    } else {
        u8 flag = pokemon_GetTokuseiFlag(poke);
        return pokemonDB_GetTokuseiDataId(id, flag);
    }
}

u32 pokemonCreateRnd()
{
    u32 high = HSD_Rand() & 0xFFFF;
    u32 low = HSD_Rand() & 0xFFFF;
    return (high << 16) | low;
}

bool pokemonCheckCanGetFriend(Pokemon* poke, u16 kind)
{
    if (!pokemonCheckValid(poke)) return 0;
    if ((u16)pokemon_GetPokemonDataId(poke) == 0x19c) return 0;
    if (pokemon_GetTamagoFlag(poke) == 1) return 0;
    if (kind != 6 && kind != 7 && kind != 8) {
        if (pokemon_GetHinsi(poke) == 1) return 0;
    }
    return 1;
}

s32 pokemonGetNowHpPercentage(Pokemon* poke)
{
    u16 hp;
    u16 max;
    if (poke == 0) {
        return 0;
    } else {
        hp = pokemon_GetHp(poke);
        max = pokemon_GetMaxHp(poke);
        return hp * 100 / max;
    }
}

u16 pokemonGetNowHpWaruValue(Pokemon* poke, u16 divisor, u16 wazaId)
{
    u16 value;
    if (!poke) return 0;
    if (divisor == 0) return 0;
    value = pokemon_GetHp(poke) / divisor;
    if (value == 0) {
        if (wazaId != 0x175 && wazaId != 0x167) value = 1;
    }
    return value;
}

u16 pokemonGetMaxHpWaruValue(Pokemon* poke, u16 divisor)
{
    u16 value;
    if (!poke) return 0;
    if (divisor == 0) return 0;
    value = pokemon_GetMaxHp(poke) / divisor;
    if (value == 0) value = 1;
    return value;
}

u32 pokemonGetLevelToExp(Pokemon* poke, u8 level)
{
    if (poke == 0) {
        return 0;
    } else {
        return _pokemonGetLevelToExp(pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(poke)), level);
    }
}

void pokemonAllKaihuku(Pokemon* poke)
{
    u8 index;
    u32 i;
    if (poke) {
        u16 max = pokemon_GetMaxHp(poke);
        pokemon_SetHp(poke, max);
        for (i = 0; (u8)i < 4; i++) {
            index = i;
            if (pokemonWazaCheckValid(poke, index) == 1) {
                u8 pp = pokemonWazaGetMaxPP(poke, index);
                pokemon_SetPokemonWazaPp(poke, index, pp);
            }
        }
        pokemonInitJoutaiDataId(poke, 3);
        pokemonInitJoutaiDataId(poke, 4);
        pokemonInitJoutaiDataId(poke, 5);
        pokemonInitJoutaiDataId(poke, 6);
        pokemonInitJoutaiDataId(poke, 7);
        pokemonInitJoutaiDataId(poke, 8);
    }
}

void pokemonSetSequenceStatus(Pokemon* poke, void* sequence)
{
    if (pokemonIsJoutaiDataId(poke, 8) == 1) Sequence_SetStatus(sequence, 1);
    if (pokemonIsJoutaiDataId(poke, 7) == 1) Sequence_SetStatus(sequence, 2);
    if (pokemonIsJoutaiNormal(poke) == 1) {
        Sequence_ResetStatus(sequence, 1);
        Sequence_ResetStatus(sequence, 2);
    }
}

u32 pokemonCreateSequence(void* fightPokemon)
{
    Pokemon* poke = fightPokemonGetPokemonPtr(fightPokemon);
    u32 rnd = pokemon_GetRnd(poke);
    u32 id = pokemon_GetPokemonDataId(poke);
    if (!pokemonDataCheckValid(0, id)) return 0;
    id = pokemonDB_GetPkxDataId(id);
    switch (id) {
    case 0xC9:
        rnd = pokemonGetAnnonKatati(rnd);
        break;
    case 0x19A:
        rnd = pokemonGetFightPokemonDeoxysSel(fightPokemon);
        break;
    case 0xF9:
        if (pokemonIsDarkPokemon(poke) == 1) id = 0x1A1;
        break;
    }
    pokemonSetSequenceStatus(poke, (void*)(id = Sequence_LoadPokemon(id, rnd, pokemonCheckRare(poke))));
    return id;
}

s32 pokemonSetWazaStatus(Pokemon* poke, u16 wazaId, u8 force)
{
    s8 index;
    s32 i;
    if (!poke) return -2;
    if (pokemonSearchWazaDataId(poke, wazaId) >= 0) return -2;
    for (i = 0; (s8)i < 4; i++) {
        index = i;
        if (!pokemonWazaCheckValid(poke, index)) {
            pokemonWazaCreate(poke, index, wazaId);
            return i;
        }
    }
    if (force == 0) return -1;
    for (index = 1; index < 4; index++) {
        _pokemonWazaCopy(poke, index - 1, index);
    }
    pokemonWazaCreate(poke, 3, wazaId);
    return 3;
}

void pokemonInit(u32 address)
{
    Pokemon* poke = (Pokemon*)address;
    u16 emptyName = 0;
    if (poke) {
        pokemon_SetFightTrainerPokemonDataId(poke, 0);
        pokemonInitDarkPokemon(poke);
        pokemon_SetPokemonDataId(poke, 0);
        pokemon_SetRnd(poke, 0);
        gamedataAttestInit(pokemon_GetAttest(poke));
        pokemonSetCatchStatus(poke, 0, 0, 0, 2, 0, &emptyName);
        pokemon_SetNicknamePtr(poke, &emptyName);
        pokemon_SetExp(poke, 0);
        pokemon_SetLevel(poke, 0);
        pokemonInitJoutai(poke);
        pokemon_SetConditionAmari(poke, 0);
        pokemonWazaInitAry(poke, 4);
        pokemonDoItemSoubi(poke, 0, 0);
        pokemon_SetHp(poke, 0);
        pokemon_SetMaxHp(poke, 0);
        pokemon_SetPhyAtk(poke, 0);
        pokemon_SetPhyDef(poke, 0);
        pokemon_SetSpeAtk(poke, 0);
        pokemon_SetSpeDef(poke, 0);
        pokemon_SetNimbleness(poke, 0);
        pokemon_SetMaxHpEffort(poke, 0);
        pokemon_SetPhyAtkEffort(poke, 0);
        pokemon_SetPhyDefEffort(poke, 0);
        pokemon_SetSpeAtkEffort(poke, 0);
        pokemon_SetSpeDefEffort(poke, 0);
        pokemon_SetNimblenessEffort(poke, 0);
        pokemon_SetMaxHpRnd(poke, 0);
        pokemon_SetPhyAtkRnd(poke, 0);
        pokemon_SetPhyDefRnd(poke, 0);
        pokemon_SetSpeAtkRnd(poke, 0);
        pokemon_SetSpeDefRnd(poke, 0);
        pokemon_SetNimblenessRnd(poke, 0);
        pokemon_SetFriend(poke, 0);
        pokemon_SetStyle(poke, 0);
        pokemon_SetBeautiful(poke, 0);
        pokemon_SetCute(poke, 0);
        pokemon_SetClever(poke, 0);
        pokemon_SetStrong(poke, 0);
        pokemon_SetFur(poke, 0);
        pokemon_SetChampRibbon(poke, 0);
        pokemon_SetWinningRibbon(poke, 0);
        pokemon_SetVictoryRibbon(poke, 0);
        pokemon_SetBromideRibbon(poke, 0);
        pokemon_SetGanbaRibbon(poke, 0);
        pokemon_SetMarineRibbon(poke, 0);
        pokemon_SetLandRibbon(poke, 0);
        pokemon_SetSkyRibbon(poke, 0);
        pokemon_SetCountryRibbon(poke, 0);
        pokemon_SetNationalRibbon(poke, 0);
        pokemon_SetEarthRibbon(poke, 0);
        pokemon_SetWorldRibbon(poke, 0);
        pokemon_SetAmariRibbon(poke, 0);
        pokemon_SetStyleMedal(poke, 0);
        pokemon_SetBeautifulMedal(poke, 0);
        pokemon_SetCuteMedal(poke, 0);
        pokemon_SetCleverMedal(poke, 0);
        pokemon_SetStrongMedal(poke, 0);
        pokemon_SetPokerus(poke, 0);
        pokemon_SetTamagoFlag(poke, 0);
        pokemon_SetTokuseiFlag(poke, 0);
        pokemon_SetFuseiFlag(poke, 0);
        pokemon_SetFlagAmari(poke, 0);
        pokemon_SetPcboxMark(poke, 0);
        pokemon_SetMailId(poke, 0xFF);
        pokemon_SetPara1Amari(poke, 0);
        pokemon_SetAmari(poke, 0);
    }
}

void pokemonGetMezamerupower(Pokemon* poke, u16* power, u16* type)
{
    u8 hp = pokemon_GetMaxHpRnd(poke);
    u8 atk = pokemon_GetPhyAtkRnd(poke);
    u8 def = pokemon_GetPhyDefRnd(poke);
    u8 spa = pokemon_GetSpeAtkRnd(poke);
    u8 spd = pokemon_GetSpeDefRnd(poke);
    u8 spe = pokemon_GetNimblenessRnd(poke);
    u8 powerBits = ((hp >> 1) & 1) | (atk & 2) | (((def >> 1) & 1) << 2) | (((spe >> 1) & 1) << 3) | (((spa >> 1) & 1) << 4) | (((spd >> 1) & 1) << 5);
    u8 typeBits = (hp & 1) | ((atk & 1) << 1) | ((def & 1) << 2) | ((spe & 1) << 3) | ((spa & 1) << 4) | ((spd & 1) << 5);
    u16 kind = (u8)(typeBits * 15 / 63 + 1);
    u16 value = powerBits * 40 / 63 + 30;
    if (kind >= 9) kind = kind + 1;
    if (power) *power = value;
    if (type) *type = kind;
}

void pokemonCreate(Pokemon* poke, u32 id, u8 level, void* attest)
{
    u16 rnd;
    u32 limit;
    u32 i;
    u8 counter;
    if (poke && pokemonDataCheckValid(0, id) && attest) {
        pokemonInit((u32)poke);
        pokemon_SetPokemonDataId(poke, id);
        pokemon_SetRnd(poke, pokemonCreateRnd());
        gamedataAttestBiosCopy(pokemon_GetAttest(poke), attest);
        pokemon_SetNicknamePtr(poke, GSmsgGetGSchar(pokemonDB_GetName(id)));
        pokemon_SetLevel(poke, level);
        rnd = HSD_Rand();
        pokemon_SetMaxHpRnd(poke, rnd & 0x1F);
        pokemon_SetPhyAtkRnd(poke, (rnd >> 5) & 0x1F);
        pokemon_SetPhyDefRnd(poke, (rnd >> 10) & 0x1F);
        rnd = HSD_Rand();
        pokemon_SetNimblenessRnd(poke, rnd & 0x1F);
        pokemon_SetSpeAtkRnd(poke, (rnd >> 5) & 0x1F);
        pokemon_SetSpeDefRnd(poke, (rnd >> 10) & 0x1F);
        pokemon_SetExp(poke, pokemonGetNowLevelToExp(poke));
        pokemon_SetFriend(poke, pokemonDB_GetInitFriend(id));
        if (HSD_Rand() & 1) pokemonSetTokuseiFlag(poke, 1);
        limit = level;
        for (i = 1; i <= limit; i++) {
            counter = 0;
            while ((s8)pokemonOboeWaza(poke, i, 1, &counter) != -3) {
                counter++;
            }
        }
        pokemonResetBasisStatus(poke);
    }
}

u32 pokemonCreateRndFit(Pokemon* poke, s8 sex, s8 seikaku, s8 rare, u32 trainerRnd)
{
    s32 sexValue;
    s32 seikakuValue;
    u32 rnd;
    s32 tries = 0x300000;
    if (poke == 0) return pokemonCreateRnd();
    sexValue = sex;
    seikakuValue = seikaku;
    do {
        rnd = pokemonCreateRnd();
        tries--;
        if (sex >= 0 && pokemonCheckSexKotei(poke) < 0) {
            if (sex != 2) {
                if (sexValue != _pokemonGetSexSub(poke, rnd)) continue;
            } else {
                u32 expected = _pokemonGetSexSub(poke, rnd);
                if (pokemonGetSex(poke) != expected) continue;
            }
        }
        if (seikaku >= 0) {
            if (seikakuValue != pokemonGetSeikakuAsRnd(rnd)) continue;
        }
        if (rare >= 0) {
            if (rare != 0) {
                if (!(u8)_pokemonCheckRare(trainerRnd, rnd)) continue;
            } else {
                if ((u8)_pokemonCheckRare(trainerRnd, rnd) == 1) continue;
            }
        }
        break;
    } while (tries > 0);
    return rnd;
}

void pokemonGetFriendFormPokemonFriendFilterId(Pokemon* poke, u16 itemKind, u16 filterId)
{
    s32 friendLevel;
    s32 value;
    u8 tier;
    if (poke && pokemonCheckCanGetFriend(poke, filterId)) {
        friendLevel = pokemon_GetFriend(poke);
        if (pokemonIsDarkPokemon(poke) == 1) friendLevel += pokemon_GetPoolFriend(poke);
        tier = 0;
        if (friendLevel >= 100) tier = 1;
        if (friendLevel >= 200) tier = (u8)tier + 1;
        if (filterId == 5) {
            if ((HSD_Rand() & 1) != 0) return;
        }
        value = pokemonFriendFilterDataBiosGetValue(pokemonFriendFilterDataBiosGetPtr(filterId), tier);
        if (value > 0 && itemKind == 0x1B) value = value * 150 / 100;
        if (value > 0 && pokemon_GetCatchBallId(poke) == 0xB) value++;
        if (pokemonIsDarkPokemon(poke) == 1) {
            s32 pool;
            if (pokemonGetDarkPokemonLevel(poke) < 2) return;
            pool = pokemon_GetPoolFriend(poke);
            pool += value * 80 / 100;
            if (pool < 0) pool = 0;
            if (pool > 0xFF) pool = 0xFF;
            pokemon_SetPoolFriend(poke, pool);
        } else {
            friendLevel += value;
            if (friendLevel < 0) friendLevel = 0;
            if (friendLevel > 0xFF) friendLevel = 0xFF;
            pokemon_SetFriend(poke, friendLevel);
        }
    }
}

struct PokemonMenuStatus {
    u16 name[11];
    u8 pad16;
    u8 level;
    u16 maxHp;
    u16 hp;
    union {
        s32 nextExp;
        f32 darkMax;
    };
    union {
        s32 nowExp;
        f32 darkNow;
    };
    u16 joutaiSprite;
    u16 faceId;
    u8 sex;
    u8 darkState;
    u16 itemId;
};

struct PokemonMenuWaza {
    u32 name;
    u32 zokuseiName;
    u16 zokusei;
    u8 maxPp;
    u8 pp;
};

struct PokemonMenuWazaStatus {
    u32 nickname;
    PokemonMenuWaza waza[4];
};

void pokemonToMenuPokemonStatusSubBar(Pokemon* poke, PokemonMenuStatus* out)
{
    u8 level = pokemon_GetLevel(poke);
    s32 base = pokemonGetLevelToExp(poke, level);
    if (!pokemonIsDarkPokemon(poke)) {
        out->nextExp = pokemonGetLevelToExp(poke, level + 1) - base;
        out->nowExp = pokemon_GetExp(poke) - base;
    } else {
        out->darkMax = (f32)(u16)darkPokemonBiosGetDarkPoint(pokemon_GetDarkpokemonDataId(poke));
        out->darkNow = pokemonGetDp(poke);
    }
}

void pokemonToMenuPokemonStatus(Pokemon* poke, void* fightPokemon, PokemonMenuStatus* out, u32 extra)
{
    pokemon_GetPokemonDataId(poke);
    GScharCpy(out, pokemon_GetNicknamePtr(poke));
    out->level = pokemon_GetLevel(poke);
    out->maxHp = pokemon_GetMaxHp(poke);
    out->hp = pokemon_GetHp(poke);
    pokemonToMenuPokemonStatusSubBar(poke, out);
    out->joutaiSprite = pokemonGetJoutaiMenuSpriteId(poke);
    if (fightPokemon == 0) {
        out->faceId = menuFaceGetID(poke);
    } else {
        out->faceId = menuFaceGetID3(poke, pokemonGetFightPokemonDeoxysSel(fightPokemon), extra);
    }
    out->sex = menuSubGetPokemonSexForFightDisp(poke);
    if (!pokemonIsDarkPokemon(poke)) {
        out->darkState = 0;
    } else if (!pokemonIsJoutaiDataId(poke, 0x3E)) {
        out->darkState = 1;
    } else {
        out->darkState = 2;
    }
    out->itemId = pokemon_GetItemDataId(poke);
}

void pokemonToMenuWazaStatus(Pokemon* poke, PokemonMenuWazaStatus* out)
{
    u8 index;
    u16 waza;
    u32 zokusei;
    u32 i;
    PokemonMenuWaza* entry;
    memset(out, 0, 0x48);
    out->nickname = (u32)pokemon_GetNicknamePtr(poke);
    for (i = 0; (u8)i < 4; i++) {
        index = i;
        entry = &out->waza[index];
        if (!pokemonWazaCheckValid(poke, index)) {
            entry->name = 0;
            entry->zokuseiName = 0;
            entry->zokusei = 0;
            entry->maxPp = 0;
            entry->pp = 0;
        } else {
            waza = pokemon_GetPokemonWazaDataId(poke, index);
            zokusei = wazaDB_GetZokuseiDataId(waza);
            entry->name = (u32)GSmsgGetGSchar(wazaDB_GetName(waza));
            entry->zokuseiName = (u32)GSmsgGetGSchar(zokuseiBiosGetName(zokusei));
            entry->zokusei = pokemonWazaGetZokusei(poke, index);
            entry->maxPp = pokemonWazaGetMaxPP(poke, index);
            entry->pp = pokemon_GetPokemonWazaPp(poke, index);
        }
    }
}

} // extern "C" (new functions)

void pokemonSetTokuseiFlag(Pokemon* param_1, u32 param_2)
{
  u32 uVar1;
  u8 cVar2;

  if (param_1 != 0) {
    uVar1 = pokemon_GetPokemonDataId(param_1);
    cVar2 = pokemonDB_GetTokuseiDataId(uVar1,1);
    if (cVar2 == '\0') {
      param_2 = 0;
    }
    pokemon_SetTokuseiFlag(param_1,param_2);
  }
  return;
}

void pokemonInitAry(u32 param_1, u16 param_2)
{
  if (param_1 != 0) {
    for (u16 uVar1 = 0; uVar1 < param_2; uVar1++) {
      pokemonInit(param_1 + uVar1 * 0xc4);
    }
  }
}

//TODO later needs a decent number of functions defined
//void pokemonInit(u32 param_1){}

//sdata2 mismatch 99.76% match as a result
void pokemonInitDarkPokemon(Pokemon* poke)
{
	pokemon_SetDarkpokemonDataId(poke,0);
	pokemonSetDp(poke, negOne);
	pokemon_SetPoolExp(poke,0);
	pokemon_SetPoolFriend(poke,0);
}

void pokemonInitJoutai(Pokemon* param_1)
{
	param_1->initCondition();
}

void pokemonWazaInitAry(Pokemon* poke, u16 wazaCount)
{
  if (poke) {
    for (u32 wazaNum = 0; (u16)wazaNum < wazaCount; wazaNum = wazaNum + 1) {
      pokemonWazaInit(poke, wazaNum);
    }
  }
}

void pokemonWazaInit(Pokemon* poke, u32 wazaNum)
{
  if (poke) {
    pokemon_SetPokemonWazaDataId(poke,wazaNum,0);
    pokemon_SetPokemonWazaPp(poke,wazaNum,0);
    pokemon_SetPokemonWazaPpCount(poke,wazaNum,0);
  }
}

u32 pokemonCheckRare(Pokemon* param_1)
{
  u32 uVar1;
  u32 uVar2;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = pokemon_GetCatchTrainerRnd(param_1);
    uVar2 = pokemon_GetRnd(param_1);
    uVar1 = _pokemonCheckRare(uVar1,uVar2);
  }
  return uVar1;
}

void pokemonGrowBasisStatus(Pokemon* poke, u32 exp)
{
  if (poke) {
    pokemon_SetExp(poke, exp);
    pokemonResetBasisStatus(poke);
  }
}

void pokemonResetBasisStatus(Pokemon* param_1)
{
  u8 uVar1;

  if (param_1 != 0) {
    uVar1 = pokemon_GetNowExpToLevel(param_1);
    _pokemonSetLevelBasisStatus(param_1, uVar1);
  }
}

//TODO much later needs a ton of functions defined
//void pokemonSetStatus(Pokemon*, u32, u16, u32, u32){}

//TODO much later needs a ton of functions defined
//u16 pokemonGetStatus(Pokemon*, u32, u16, u32){}

u32 pokemonAdjustValueBySeikaku(u32 param1, u16 param2, u32 baseValue)
{
    PokemonSeikakuDataBios* seikakuPtr;
    PokemonSeikakuRateBios* ratePtr;
    u32 rateId;
    s32 result;
    u32 stat;
    u32 kake;
    u32 waru;

    seikakuPtr = pokemonSeikakuDataBiosGetPtr(param1);

    if (seikakuPtr == NULL)
        return baseValue;

    stat = param2;

    switch (stat)
    {
		case STATUS_POKEMON_PHY_ATK:
			rateId = pokemonSeikakuDataBiosGetPhyAtkRateDataId(seikakuPtr);
			break;
		case STATUS_POKEMON_PHY_DEF:
			rateId = pokemonSeikakuDataBiosGetPhyDefRateDataId(seikakuPtr);
			break;
		case 0x8A:
			rateId = pokemonSeikakuDataBiosGetSpeAtkRateDataId(seikakuPtr);
			break;
		case 0x8B:
			rateId = pokemonSeikakuDataBiosGetSpeDefRateDataId(seikakuPtr);
			break;
		case 0x8C:
			rateId = pokemonSeikakuDataBiosGetNimblenessRateDataId(seikakuPtr);
			break;
		default:
			return baseValue;
    }

    ratePtr = pokemonSeikakuRateDataBiosGetPtr(rateId);
    if (ratePtr == NULL)
        return 0;

    kake = pokemonSeikakuRateDataBiosGetKake(ratePtr);
    waru = pokemonSeikakuRateDataBiosGetWaru(ratePtr);

    result = baseValue * (u8)kake;

    if ((u8)waru != 0)
        result = result / (u8)waru;

    return result;
}

u8 _pokemonGetSeikaku(Pokemon* a)
{
	return pokemonGetSeikakuAsRnd(pokemon_GetRnd(a));
}

u8 pokemonGetSeikakuAsRnd(u32 a)
{
  return a % 25;
}

u8 _pokemonGetHinsi(Pokemon* a)
{
	return pokemon_GetHp(a) == 0;
}

void _pokemonSetLevelBasisStatus(Pokemon* a , u8 b)
{
	u16 sVar1;
	u32 sVar2;
	u16 sVar3;
	u16 sVar4;
	u16 sVar5;

	sVar2 = pokemon_GetPokemonDataId(a);
	sVar3 = pokemon_GetMaxHp(a);
	pokemon_SetLevel(a,b);
	if ((u16)sVar2 == 0x12f)
	{
		sVar4 = 1;
		pokemon_SetMaxHp(a,1);
	}
	else
	{
		sVar4 = _pokemonGetLevelOneStatus(a,b,0x87,3,0x93,0x8d,(b & 0xff) + 10);
	}
	_pokemonGetLevelOneStatus(a,b,0x88,4,0x94,0x8e,5);
	_pokemonGetLevelOneStatus(a,b,0x89,5,0x95,0x8f,5);
	_pokemonGetLevelOneStatus(a,b,0x8c,8,0x98,0x92,5);
	_pokemonGetLevelOneStatus(a,b,0x8a,6,0x96,0x90,5);
	_pokemonGetLevelOneStatus(a,b,0x8b,7,0x97,0x91,5);
	sVar5 = pokemon_GetHp(a);
	if ((sVar5 != 0) || (sVar3 == 0))
	{
		sVar1 = 1;
		if ((u16)sVar2 != 0x12f)
		{
			sVar1 = sVar5 + (sVar4 - sVar3);
		}
		pokemon_SetHp(a,sVar1);
	}
}

u16 _pokemonGetLevelOneStatus(Pokemon* poke, u8 level, u16 stat, u16 basisStat, u16 randomStat, u16 effortStat, long bonus)
{
    u32 speciesId = pokemon_GetPokemonDataId(poke);
    u32 nature = pokemon_GetSeikaku(poke);
    u16 basis = pokemonGetStatus(nullptr, speciesId, basisStat, 0);
    u16 random = pokemonGetStatus(poke, 0, randomStat, 0);
    u16 effort = pokemonGetStatus(poke, 0, effortStat, 0);
    u16 value = pokemonCreateBasisStatus(basis, random, effort, level, bonus);
    u32 adjusted = pokemonAdjustValueBySeikaku(nature, stat, value);
    pokemonSetStatus(poke, 0, stat, 0, adjusted);
    return adjusted;
}

u16 pokemonCreateBasisStatus(u16 a, u8 b, u16 c, u8 d, s32 e)
{
	return e + (s32)((d & 0xff) * ((b & 0xff) + (a & 0xffff) * 2 + (c >> 2 & 0x3fff))) / 100 & 0xffff;
}

u8 _pokemonGetNowExpToLevel(Pokemon* a)
{
  u8 growDataId;
  u32 exp;

  growDataId = pokemonDB_GetGrowDataId(pokemon_GetPokemonDataId(a));
  exp = pokemon_GetExp(a);
  return pokemonGetExpToLevel(growDataId,exp);
}

u8 pokemonGetExpToLevel(u8 a, u32 b)
{
    s32 level = 0;

    PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(a);
    if (!ptr)
        return level;

    for (level = 1; level < 101; level++) {
        if (pokemonGrowDataBiosGetExp(ptr, level) > b)
            break;
    }

    return (level - 1);
}

static int _pokemonGetLevelToExp(u8 a, u8 b)
{
	PokemonGrowDataBios* ptr = pokemonGrowDataBiosGetPtr(a);
    if (ptr == 0) {
        return 0;
    }
    return pokemonGrowDataBiosGetExp(ptr, b);
}

int pokemonCheckRareRnd(unsigned long a, unsigned long b)
{
	return _pokemonCheckRare(a, b);
}

static int _pokemonCheckRare(unsigned long a, unsigned long b)
{
	int x = 8 > (a >> 0x10 ^ a & 0xFFFF ^ b >> 0x10 ^ b & 0xFFFF);
	int y = x ? -1 : 0;
	return -y;
}

void pokemonSetStatus(Pokemon* object, u32 speciesId, u16 property, u16 index, u32 value) {
    if (property == 0 || property >= 0x124) return;
    if (property < 0x6d) {
        pokemonDataBiosGetPtr(speciesId);
        object = reinterpret_cast<Pokemon*>(pokemonDataBiosGetPtr(speciesId));
        if (object == nullptr) return;
    } else if (object == nullptr) {
        return;
    }
    switch (property) {
    case STATUS_SPECIES_NAME: pokemonDataBiosSetName(reinterpret_cast<PokemonData*>(object), reinterpret_cast<const char*>(value)); break;
    case STATUS_SPECIES_BASIS_MAX_HP: pokemonDataBiosSetBasisMaxHp(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_PHY_ATK: pokemonDataBiosSetBasisPhyAtk(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_PHY_DEF: pokemonDataBiosSetBasisPhyDef(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_SPE_ATK: pokemonDataBiosSetBasisSpeAtk(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_SPE_DEF: pokemonDataBiosSetBasisSpeDef(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_BASIS_NIMBLENESS: pokemonDataBiosSetBasisNimbleness(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_MAX_HP_EFFORT: pokemonDataBiosSetGiveMaxHpEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_PHY_ATK_EFFORT: pokemonDataBiosSetGivePhyAtkEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_PHY_DEF_EFFORT: pokemonDataBiosSetGivePhyDefEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_SPE_ATK_EFFORT: pokemonDataBiosSetGiveSpeAtkEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_SPE_DEF_EFFORT: pokemonDataBiosSetGiveSpeDefEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_NIMBLENESS_EFFORT: pokemonDataBiosSetGiveNimblenessEffort(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GIVE_EXP: pokemonDataBiosSetGiveExp(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_GROW_DATA_ID: pokemonDataBiosSetGrowDataId(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_: pokemonDataBiosSetGet(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_SEX_RATIO: pokemonDataBiosSetSexRatio(reinterpret_cast<PokemonData*>(object), static_cast<u8>(value)); break;
    case STATUS_SPECIES_INIT_FRIEND: pokemonDataBiosSetInitFriend(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_ITEM_DATA_ID: pokemonDataBiosSetItemDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_ZOKUSEI_DATA_ID: pokemonDataBiosSetZokuseiDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_TOKUSEI_DATA_ID: pokemonDataBiosSetTokuseiDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_SINKA_KIND: pokemonDataBiosSetSinkaKind(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_SINKA_BUFF: pokemonDataBiosSetSinkaBuff(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_SINKA_POKEMON_DATA_ID: pokemonDataBiosSetSinkaPokemonDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_WAZA_LEVEL: pokemonDataBiosSetGetWazaLevel(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_WAZA_DATA_ID: pokemonDataBiosSetGetWazaDataId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case 0x20: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 0, static_cast<u8>(value != 0)); break;
    case 0x21: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 1, static_cast<u8>(value != 0)); break;
    case 0x22: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 2, static_cast<u8>(value != 0)); break;
    case 0x23: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 3, static_cast<u8>(value != 0)); break;
    case 0x24: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 4, static_cast<u8>(value != 0)); break;
    case 0x25: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 5, static_cast<u8>(value != 0)); break;
    case 0x26: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 6, static_cast<u8>(value != 0)); break;
    case 0x27: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 7, static_cast<u8>(value != 0)); break;
    case 0x28: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 8, static_cast<u8>(value != 0)); break;
    case 0x29: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 9, static_cast<u8>(value != 0)); break;
    case 0x2a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 10, static_cast<u8>(value != 0)); break;
    case 0x2b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 11, static_cast<u8>(value != 0)); break;
    case 0x2c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 12, static_cast<u8>(value != 0)); break;
    case 0x2d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 13, static_cast<u8>(value != 0)); break;
    case 0x2e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 14, static_cast<u8>(value != 0)); break;
    case 0x2f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 15, static_cast<u8>(value != 0)); break;
    case 0x30: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 16, static_cast<u8>(value != 0)); break;
    case 0x31: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 17, static_cast<u8>(value != 0)); break;
    case 0x32: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 18, static_cast<u8>(value != 0)); break;
    case 0x33: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 19, static_cast<u8>(value != 0)); break;
    case 0x34: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 20, static_cast<u8>(value != 0)); break;
    case 0x35: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 21, static_cast<u8>(value != 0)); break;
    case 0x36: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 22, static_cast<u8>(value != 0)); break;
    case 0x37: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 23, static_cast<u8>(value != 0)); break;
    case 0x38: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 24, static_cast<u8>(value != 0)); break;
    case 0x39: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 26, static_cast<u8>(value != 0)); break;
    case 0x3a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 27, static_cast<u8>(value != 0)); break;
    case 0x3b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 28, static_cast<u8>(value != 0)); break;
    case 0x3c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 29, static_cast<u8>(value != 0)); break;
    case 0x3d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 30, static_cast<u8>(value != 0)); break;
    case 0x3e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 31, static_cast<u8>(value != 0)); break;
    case 0x3f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 32, static_cast<u8>(value != 0)); break;
    case 0x40: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 33, static_cast<u8>(value != 0)); break;
    case 0x41: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 34, static_cast<u8>(value != 0)); break;
    case 0x42: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 35, static_cast<u8>(value != 0)); break;
    case 0x43: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 36, static_cast<u8>(value != 0)); break;
    case 0x44: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 37, static_cast<u8>(value != 0)); break;
    case 0x45: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 38, static_cast<u8>(value != 0)); break;
    case 0x46: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 39, static_cast<u8>(value != 0)); break;
    case 0x47: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 40, static_cast<u8>(value != 0)); break;
    case 0x48: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 41, static_cast<u8>(value != 0)); break;
    case 0x49: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 42, static_cast<u8>(value != 0)); break;
    case 0x4a: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 43, static_cast<u8>(value != 0)); break;
    case 0x4b: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 44, static_cast<u8>(value != 0)); break;
    case 0x4c: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 45, static_cast<u8>(value != 0)); break;
    case 0x4d: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 46, static_cast<u8>(value != 0)); break;
    case 0x4e: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 47, static_cast<u8>(value != 0)); break;
    case 0x4f: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 48, static_cast<u8>(value != 0)); break;
    case 0x50: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 49, static_cast<u8>(value != 0)); break;
    case 0x51: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 50, static_cast<u8>(value != 0)); break;
    case 0x52: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 51, static_cast<u8>(value != 0)); break;
    case 0x53: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 52, static_cast<u8>(value != 0)); break;
    case 0x54: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 53, static_cast<u8>(value != 0)); break;
    case 0x55: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 54, static_cast<u8>(value != 0)); break;
    case 0x56: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 55, static_cast<u8>(value != 0)); break;
    case 0x57: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 56, static_cast<u8>(value != 0)); break;
    case 0x58: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 57, static_cast<u8>(value != 0)); break;
    case 0x59: pokemonDataBiosSetWazaMcn(reinterpret_cast<PokemonData*>(object), 58, static_cast<u8>(value != 0)); break;
    case STATUS_SPECIES_POKEBODY_ID: pokemonDataBiosSetPokebodyId(reinterpret_cast<PokemonData*>(object), index, value); break;
    case STATUS_SPECIES_STATUS_FACE_MENU_SPRITE_ID: pokemonDataBiosSetStatusFaceMenuSpriteId(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_SPECIES_COLOR: pokemonDataBiosSetColor(reinterpret_cast<PokemonData*>(object), index, static_cast<u8>(value)); break;
    case STATUS_SPECIES_TYPE_NAME: pokemonDataBiosSetTypeName(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_HEIGHT: pokemonDataBiosSetHeight(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_WEIGHT: pokemonDataBiosSetWeight(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_DOC: pokemonDataBiosSetDoc(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_VOICE: pokemonDataBiosSetVoice(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_MITA_FLAG: pokemonDataBiosSetMitaFlag(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_TUKAMAETA_FLAG: pokemonDataBiosSetTukamaetaFlag(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_NUM_ZUKAN: pokemonDataBiosSetNumZukan(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_NUM_POKEMON: pokemonDataBiosSetNumPokemon(reinterpret_cast<PokemonData*>(object), static_cast<u16>(value)); break;
    case STATUS_SPECIES_PKX_DATA_ID: pokemonDataBiosSetPkxDataId(reinterpret_cast<PokemonData*>(object), value); break;
    case STATUS_SPECIES_KOWAZA: pokemonDataBiosSetKowaza(reinterpret_cast<PokemonData*>(object), index, static_cast<u16>(value)); break;
    case STATUS_POKEMON_POKEMON_DATA_ID: pokemonBiosSetPokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_RND: pokemonBiosSetRnd(object, value); break;
    case STATUS_POKEMON_CATCH_FLOOR_ID: pokemonBiosSetCatchFloorId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_CATCH_LEVEL: pokemonBiosSetCatchLevel(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_BALL_ID: pokemonBiosSetCatchBallId(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_TRAINER_SEX: pokemonBiosSetCatchTrainerSex(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CATCH_TRAINER_RND: pokemonBiosSetCatchTrainerRnd(object, value); break;
    case STATUS_POKEMON_CATCH_TRAINER_NAME_PTR: pokemonBiosSetCatchTrainerNamePtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_NICKNAME_PTR: pokemonBiosSetNicknamePtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_NICKNAME_ORG_PTR: pokemonBiosSetNicknameOrgPtr(object, reinterpret_cast<u16*>(value)); break;
    case STATUS_POKEMON_EXP: pokemonBiosSetExp(object, value); break;
    case STATUS_POKEMON_LEVEL: pokemonBiosSetLevel(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CONDITION_AMARI: pokemonBiosSetConditionAmari(object, value); break;
    case STATUS_POKEMON_POKEMON_WAZA_DATA_ID: pokemonBiosSetPokemonWazaDataId(object, index, static_cast<u16>(value)); break;
    case STATUS_POKEMON_POKEMON_WAZA_PP: pokemonBiosSetPokemonWazaPp(object, index, static_cast<u8>(value)); break;
    case STATUS_POKEMON_POKEMON_WAZA_PP_COUNT: pokemonBiosSetPokemonWazaPpCount(object, index, static_cast<u8>(value)); break;
    case STATUS_POKEMON_ITEM_DATA_ID: pokemonBiosSetItemDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_HP: pokemonBiosSetHp(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP: pokemonBiosSetMaxHp(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK: pokemonBiosSetPhyAtk(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF: pokemonBiosSetPhyDef(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK: pokemonBiosSetSpeAtk(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF: pokemonBiosSetSpeDef(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS: pokemonBiosSetNimbleness(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP_EFFORT: pokemonBiosSetMaxHpEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK_EFFORT: pokemonBiosSetPhyAtkEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF_EFFORT: pokemonBiosSetPhyDefEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK_EFFORT: pokemonBiosSetSpeAtkEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF_EFFORT: pokemonBiosSetSpeDefEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS_EFFORT: pokemonBiosSetNimblenessEffort(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_MAX_HP_RND: pokemonBiosSetMaxHpRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_ATK_RND: pokemonBiosSetPhyAtkRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_PHY_DEF_RND: pokemonBiosSetPhyDefRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_ATK_RND: pokemonBiosSetSpeAtkRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_SPE_DEF_RND: pokemonBiosSetSpeDefRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_NIMBLENESS_RND: pokemonBiosSetNimblenessRnd(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_FRIEND: pokemonBiosSetFriend(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_STYLE: pokemonBiosSetStyle(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_BEAUTIFUL: pokemonBiosSetBeautiful(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CUTE: pokemonBiosSetCute(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CLEVER: pokemonBiosSetClever(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STRONG: pokemonBiosSetStrong(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_FUR: pokemonBiosSetFur(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CHAMP_RIBBON: pokemonBiosSetChampRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_WINNING_RIBBON: pokemonBiosSetWinningRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_VICTORY_RIBBON: pokemonBiosSetVictoryRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_BROMIDE_RIBBON: pokemonBiosSetBromideRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_GANBA_RIBBON: pokemonBiosSetGanbaRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_MARINE_RIBBON: pokemonBiosSetMarineRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_LAND_RIBBON: pokemonBiosSetLandRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_SKY_RIBBON: pokemonBiosSetSkyRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_COUNTRY_RIBBON: pokemonBiosSetCountryRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_NATIONAL_RIBBON: pokemonBiosSetNationalRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_EARTH_RIBBON: pokemonBiosSetEarthRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_WORLD_RIBBON: pokemonBiosSetWorldRibbon(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_AMARI_RIBBON: pokemonBiosSetAmariRibbon(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STYLE_MEDAL: pokemonBiosSetStyleMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_BEAUTIFUL_MEDAL: pokemonBiosSetBeautifulMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CUTE_MEDAL: pokemonBiosSetCuteMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_CLEVER_MEDAL: pokemonBiosSetCleverMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_STRONG_MEDAL: pokemonBiosSetStrongMedal(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_POKERUS: pokemonBiosSetPokerus(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_TAMAGO_FLAG: pokemonBiosSetTamagoFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_TOKUSEI_FLAG: pokemonBiosSetTokuseiFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_FUSEI_FLAG: pokemonBiosSetFuseiFlag(object, static_cast<u8>(value != 0)); break;
    case STATUS_POKEMON_FLAG_AMARI: pokemonBiosSetFlagAmari(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_PCBOX_MARK: pokemonBiosSetPcboxMark(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_MAIL_ID: pokemonBiosSetMailId(object, static_cast<u8>(value)); break;
    case STATUS_POKEMON_PARA1_AMARI: pokemonBiosSetPara1Amari(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_AMARI: pokemonBiosSetAmari(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_FIGHT_TRAINER_POKEMON_DATA_ID: pokemonBiosSetFightTrainerPokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_DARKPOKEMON_DATA_ID: pokemonBiosSetDarkpokemonDataId(object, static_cast<u16>(value)); break;
    case STATUS_POKEMON_DP: pokemonBiosSetDp(object, value); break;
    case STATUS_POKEMON_POOL_EXP: pokemonBiosSetPoolExp(object, value); break;
    case STATUS_POKEMON_POOL_FRIEND: pokemonBiosSetPoolFriend(object, static_cast<u16>(value)); break;
    case STATUS_FIGHT_MOTO_POKEMON_PTR: fightPokemonBiosSetMotoPokemonPtr(reinterpret_cast<FightPokemon*>(object), value); break;
    case STATUS_FIGHT_CONDITION_COPY: {
        FightJoutai* target = fightPokemon_GetFightJoutaiPtr(reinterpret_cast<FightPokemon*>(object), 0);
        if (target != nullptr) {
            const FightJoutai* source = reinterpret_cast<const FightJoutai*>(value);
            for (u8 i = 0; i < 1; i++) {
                target[i].dataId = source[i].dataId;
                target[i].userFightTargetId = source[i].userFightTargetId;
                target[i].kaisuu = source[i].kaisuu;
                target[i].nowKaisuu = source[i].nowKaisuu;
                target[i].count = source[i].count;
                target[i].reserved07 = source[i].reserved07;
                target[i].buff = source[i].buff;
                target[i].idBuff = source[i].idBuff;
            }
        }
        break;
    }
    case STATUS_FIGHT_ENTRY_ID: fightPokemonBiosSetEntryId(reinterpret_cast<FightPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_CATCH_ENTRY_FLAG: fightPokemonBiosSetCatchEntryFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_LEVEL_UP_FLAG: fightPokemonBiosSetLevelUpFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_DARK_OUT_FLAG: fightPokemonBiosSetDarkOutFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_HOKAKU_FLAG: fightPokemonBiosSetHokakuFlag(reinterpret_cast<FightPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_MOTO_FIGHT_POKEMON_PTR: fightOutPokemonBiosSetMotoFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_PTR: fightOutPokemonBiosSetFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_USE_WAZA_DATA_ID: fightWaza_SetUseWazaDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MOTO_WAZA_DATA_ID: fightWaza_SetMotoWazaDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_VALUE: fightWaza_SetDamageValue(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_CRITICAL: fightWaza_SetCritical(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_WRITE_MOVE_CONDITION: {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object));
        if (fightWazaCheckWriteJoutaiDataId(waza, static_cast<u16>(value)) == 2)
            fightWazaWriteJoutaiDataId(waza, static_cast<u16>(value), 0);
        break;
    }
    case STATUS_FIGHT_OUT_INIT_MOVE_CONDITION: {
        FightWaza* waza = fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object));
        if (static_cast<u16>(value) != 0) {
            if (fightWazaIsJoutaiDataId(waza, static_cast<u16>(value)) == 1)
                fightWazaInitJoutaiDataId(waza, static_cast<u16>(value));
        } else {
            fightWazaInitJoutai(waza);
        }
        break;
    }
    case STATUS_FIGHT_OUT_DAMAGE: fightWaza_SetDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), value); break;
    case STATUS_FIGHT_OUT_IRYOKU: fightWaza_SetIryoku(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_TARGET_DATA_ID: fightWaza_SetTargetDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_DAMAGE: fightWaza_SetHitDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), value); break;
    case STATUS_FIGHT_OUT_ABICNT_PHY_ATK: fightOutPokemonBiosSetAbicntPhyAtk(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_PHY_DEF: fightOutPokemonBiosSetAbicntPhyDef(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_SPE_ATK: fightOutPokemonBiosSetAbicntSpeAtk(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_SPE_DEF: fightOutPokemonBiosSetAbicntSpeDef(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_NIMBLENESS: fightOutPokemonBiosSetAbicntNimbleness(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_AVERAGE: fightOutPokemonBiosSetAbicntAverage(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_ABICNT_AVOID: fightOutPokemonBiosSetAbicntAvoid(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_FIGHTOUT_TURN_COUNT: fightOutPokemonBiosSetFightoutTurnCount(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_SEQUENCE_PTR: fightOutPokemonBiosSetSequencePtr(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_SKETCH_WAZA_DATA_ID: fightOutPokemonBiosSetSketchWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_SELECT_WAZA_DATA_ID: fightOutPokemonBiosSetLastSelectWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_USE_WAZA_DATA_ID: fightOutPokemonBiosSetLastUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_LAST_RECEIVE_WAZA_TARGET_DATA_ID: fightOutPokemonBiosSetLastReceiveWazaTargetDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_WAZA_DATA_ID: fightOutPokemonBiosSetHitWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_HIT_WAZA_ZOKUSEI_DATA_ID: fightOutPokemonBiosSetHitWazaZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_VALUE: fightOutPokemonBiosSetGamanDamageValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_TARGET_ID: fightOutPokemonBiosSetGamanDamageTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_OUMU_WAZA_DATA_ID: fightOutPokemonBiosSetOumuWazaDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_NAMAKE_FLAG: fightOutPokemonBiosSetNamakeFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_USED_ITEM_DATA_ID: fightOutPokemonBiosSetUsedItemDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_STOCK_ITEM_DATA_ID: fightOutPokemonBiosSetStockItemDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_SUCCESS_CNT: fightOutPokemonBiosSetSuccessCnt(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value)); break;
    case STATUS_FIGHT_OUT_MEET_ENEMY_FIGHT_POKEMON_ENTRY_ID: {
        s8 entry = static_cast<s8>(value);
        fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index), entry);
        break;
    }
    case STATUS_FIGHT_OUT_ZOKUSEI_DATA_ID: fightOutPokemonBiosSetZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_TOKUSEI_DATA_ID: fightOutPokemonBiosSetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_ATK_VALUE: fightOutPokemonBiosSetDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_ATK_TARGET_ID: fightOutPokemonBiosSetDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_SPE_VALUE: fightOutPokemonBiosSetDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_DAMAGE_SPE_TARGET_ID: fightOutPokemonBiosSetDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MAHI_NO_ATTACK_FLAG: fightOutPokemonBiosSetMahiNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KONRAN_MYSELF_ATTACK_FLAG: fightOutPokemonBiosSetKonranMyselfAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_OUT_WAZA_KOUKANAI_FLAG: fightOutPokemonBiosSetOutWazaKoukanaiFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_TAME_WAZA_FLAG: fightOutPokemonBiosSetTameWazaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ITEM_NIGERU_FLAG: fightOutPokemonBiosSetItemNigeruFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_HUUIN_NO_ATTACK_FLAG: fightOutPokemonBiosSetHuuinNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_MERO_MERO_NO_ATTACK_FLAG: fightOutPokemonBiosSetMeroMeroNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KANASHIBARI_NO_ATTACK_FLAG: fightOutPokemonBiosSetKanashibariNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_CHOUHATSU_NO_ATTACK_FLAG: fightOutPokemonBiosSetChouhatsuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ICHAMON_NO_ATTACK_FLAG: fightOutPokemonBiosSetIchamonNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_HIRUMU_NO_ATTACK_FLAG: fightOutPokemonBiosSetHirumuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_PASS_PPDEC_FLAG: fightOutPokemonBiosSetPassPpdecFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_FIGHT_ACTION_FLAG: fightOutPokemonBiosSetFightActionFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_CLEARBODY_FLAG: fightOutPokemonBiosSetDoClearbodyFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_RECEIVES_WAZA_HIRAISHIN_FLAG: fightOutPokemonBiosSetReceivesWazaHiraishinFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_VANISHOFF_FLAG: fightOutPokemonBiosSetVanishoffFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_IKAKU_FLAG: fightOutPokemonBiosSetDoIkakuFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_DO_TRACE_FLAG: fightOutPokemonBiosSetDoTraceFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_NO_PRESSURE_FLAG: fightOutPokemonBiosSetNoPressureFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_IREKAETA_FLAG: fightOutPokemonBiosSetIrekaetaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_ITEM_KORAETA_FLAG: fightOutPokemonBiosSetItemKoraetaFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_KAIGARA_DAMAGE_VALUE: fightOutPokemonBiosSetKaigaraDamageValue(reinterpret_cast<FightOutPokemon*>(object), value); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_VALUE: fightOutPokemonBiosSetMyselfDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_TARGET_ID: fightOutPokemonBiosSetMyselfDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_VALUE: fightOutPokemonBiosSetMyselfDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_TARGET_ID: fightOutPokemonBiosSetMyselfDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u16>(value)); break;
    case STATUS_FIGHT_OUT_KIZETU_FLAG: fightOutPokemonBiosSetKizetuFlag(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(value != 0)); break;
    case STATUS_FIGHT_OUT_IREKAE_TARGET_ENTRY_ID: fightOutPokemonBiosSetIrekaeTargetEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<s16>(value)); break;
    default: break;
    }
}

u32 pokemonGetStatus(Pokemon* object, u32 speciesId, u16 property, u16 index) {
    if (property == 0 || property >= 0x124) return 0;
    if (property < 0x6d) {
        object = reinterpret_cast<Pokemon*>(pokemonDataBiosGetPtr(speciesId));
        if (object == nullptr) return 0;
    } else if (object == nullptr) {
        return 0;
    }
    switch (property) {
    case STATUS_SPECIES_NAME: return reinterpret_cast<u32>(pokemonDataBiosGetName(reinterpret_cast<PokemonData*>(object)));
    case STATUS_SPECIES_BASIS_MAX_HP: return pokemonDataBiosGetBasisMaxHp(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_PHY_ATK: return pokemonDataBiosGetBasisPhyAtk(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_PHY_DEF: return pokemonDataBiosGetBasisPhyDef(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_SPE_ATK: return pokemonDataBiosGetBasisSpeAtk(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_SPE_DEF: return pokemonDataBiosGetBasisSpeDef(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_BASIS_NIMBLENESS: return pokemonDataBiosGetBasisNimbleness(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_MAX_HP_EFFORT: return pokemonDataBiosGetGiveMaxHpEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_PHY_ATK_EFFORT: return pokemonDataBiosGetGivePhyAtkEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_PHY_DEF_EFFORT: return pokemonDataBiosGetGivePhyDefEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_SPE_ATK_EFFORT: return pokemonDataBiosGetGiveSpeAtkEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_SPE_DEF_EFFORT: return pokemonDataBiosGetGiveSpeDefEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_NIMBLENESS_EFFORT: return pokemonDataBiosGetGiveNimblenessEffort(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GIVE_EXP: return pokemonDataBiosGetGiveExp(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_GROW_DATA_ID: return pokemonDataBiosGetGrowDataId(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_: return pokemonDataBiosGetGet(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_SEX_RATIO: return pokemonDataBiosGetSexRatio(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_INIT_FRIEND: return pokemonDataBiosGetInitFriend(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_ITEM_DATA_ID: return pokemonDataBiosGetItemDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_ZOKUSEI_DATA_ID: return pokemonDataBiosGetZokuseiDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_TOKUSEI_DATA_ID: return pokemonDataBiosGetTokuseiDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_KIND: return pokemonDataBiosGetSinkaKind(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_BUFF: return pokemonDataBiosGetSinkaBuff(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_SINKA_POKEMON_DATA_ID: return pokemonDataBiosGetSinkaPokemonDataId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_WAZA_LEVEL: return pokemonDataBiosGetGetWazaLevel(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_WAZA_DATA_ID: return pokemonDataBiosGetGetWazaDataId(reinterpret_cast<PokemonData*>(object), index);
    case 0x20: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 0);
    case 0x21: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 1);
    case 0x22: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 2);
    case 0x23: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 3);
    case 0x24: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 4);
    case 0x25: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 5);
    case 0x26: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 6);
    case 0x27: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 7);
    case 0x28: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 8);
    case 0x29: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 9);
    case 0x2a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 10);
    case 0x2b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 11);
    case 0x2c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 12);
    case 0x2d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 13);
    case 0x2e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 14);
    case 0x2f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 15);
    case 0x30: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 16);
    case 0x31: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 17);
    case 0x32: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 18);
    case 0x33: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 19);
    case 0x34: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 20);
    case 0x35: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 21);
    case 0x36: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 22);
    case 0x37: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 23);
    case 0x38: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 24);
    case 0x39: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 26);
    case 0x3a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 27);
    case 0x3b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 28);
    case 0x3c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 29);
    case 0x3d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 30);
    case 0x3e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 31);
    case 0x3f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 32);
    case 0x40: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 33);
    case 0x41: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 34);
    case 0x42: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 35);
    case 0x43: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 36);
    case 0x44: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 37);
    case 0x45: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 38);
    case 0x46: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 39);
    case 0x47: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 40);
    case 0x48: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 41);
    case 0x49: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 42);
    case 0x4a: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 43);
    case 0x4b: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 44);
    case 0x4c: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 45);
    case 0x4d: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 46);
    case 0x4e: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 47);
    case 0x4f: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 48);
    case 0x50: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 49);
    case 0x51: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 50);
    case 0x52: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 51);
    case 0x53: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 52);
    case 0x54: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 53);
    case 0x55: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 54);
    case 0x56: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 55);
    case 0x57: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 56);
    case 0x58: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 57);
    case 0x59: return pokemonDataBiosGetWazaMcn(reinterpret_cast<PokemonData*>(object), 58);
    case STATUS_SPECIES_POKEBODY_ID: return pokemonDataBiosGetPokebodyId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_STATUS_FACE_MENU_SPRITE_ID: return pokemonDataBiosGetStatusFaceMenuSpriteId(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_COLOR: return pokemonDataBiosGetColor(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_TYPE_NAME: return pokemonDataBiosGetTypeName(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_HEIGHT: return pokemonDataBiosGetHeight(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_WEIGHT: return pokemonDataBiosGetWeight(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_DOC: return pokemonDataBiosGetDoc(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_VOICE: return pokemonDataBiosGetVoice(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_MITA_FLAG: return pokemonDataBiosGetMitaFlag(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_TUKAMAETA_FLAG: return pokemonDataBiosGetTukamaetaFlag(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_NUM_ZUKAN: return pokemonDataBiosGetNumZukan(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_NUM_POKEMON: return pokemonDataBiosGetNumPokemon(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_PKX_DATA_ID: return pokemonDataBiosGetPkxDataId(reinterpret_cast<PokemonData*>(object));
    case STATUS_SPECIES_KOWAZA: return pokemonDataBiosGetKowaza(reinterpret_cast<PokemonData*>(object), index);
    case STATUS_SPECIES_POKEMON_DATA_ID:
    case STATUS_SPECIES_POKEMON_DATA_ID_6A:
    case STATUS_SPECIES_POKEMON_DATA_ID_6B:
    case STATUS_SPECIES_POKEMON_DATA_ID_6C:
    case STATUS_POKEMON_POKEMON_DATA_ID: return (u16)pokemonBiosGetPokemonDataId(object);
    case STATUS_POKEMON_RND: return pokemonBiosGetRnd(object);
    case STATUS_POKEMON_ATTEST: return reinterpret_cast<u32>(pokemonBiosGetAttest(object));
    case STATUS_POKEMON_CATCH_FLOOR_ID: return pokemonBiosGetCatchFloorId(object);
    case STATUS_POKEMON_CATCH_LEVEL: return pokemonBiosGetCatchLevel(object);
    case STATUS_POKEMON_CATCH_BALL_ID: return pokemonBiosGetCatchBallId(object);
    case STATUS_POKEMON_CATCH_TRAINER_SEX: return pokemonBiosGetCatchTrainerSex(object);
    case STATUS_POKEMON_CATCH_TRAINER_RND: return pokemonBiosGetCatchTrainerRnd(object);
    case STATUS_POKEMON_CATCH_TRAINER_NAME_PTR: return reinterpret_cast<u32>(pokemonBiosGetCatchTrainerNamePtr(object));
    case STATUS_POKEMON_NICKNAME_PTR: return reinterpret_cast<u32>(pokemonBiosGetNicknamePtr(object));
    case STATUS_POKEMON_NICKNAME_ORG_PTR: return reinterpret_cast<u32>(pokemonBiosGetNicknameOrgPtr(object));
    case STATUS_POKEMON_EXP: return pokemonBiosGetExp(object);
    case STATUS_POKEMON_LEVEL: return pokemonBiosGetLevel(object);
    case STATUS_POKEMON_POKEMON_GET_HINSI: return _pokemonGetHinsi(object);
    case 0x7c: return 0;
    case STATUS_POKEMON_CONDITION_AMARI: return pokemonBiosGetConditionAmari(object);
    case STATUS_POKEMON_POKEMON_WAZA_DATA_ID: return pokemonBiosGetPokemonWazaDataId(object, index);
    case STATUS_POKEMON_POKEMON_WAZA_PP: return pokemonBiosGetPokemonWazaPp(object, index);
    case STATUS_POKEMON_POKEMON_WAZA_PP_COUNT: return pokemonBiosGetPokemonWazaPpCount(object, index);
    case STATUS_POKEMON_ITEM_DATA_ID: return pokemonBiosGetItemDataId(object);
    case STATUS_POKEMON_HP: return pokemonBiosGetHp(object);
    case STATUS_POKEMON_MAX_HP: return pokemonBiosGetMaxHp(object);
    case STATUS_POKEMON_PHY_ATK: return pokemonBiosGetPhyAtk(object);
    case STATUS_POKEMON_PHY_DEF: return pokemonBiosGetPhyDef(object);
    case STATUS_POKEMON_SPE_ATK: return pokemonBiosGetSpeAtk(object);
    case STATUS_POKEMON_SPE_DEF: return pokemonBiosGetSpeDef(object);
    case STATUS_POKEMON_NIMBLENESS: return pokemonBiosGetNimbleness(object);
    case STATUS_POKEMON_MAX_HP_EFFORT: return pokemonBiosGetMaxHpEffort(object);
    case STATUS_POKEMON_PHY_ATK_EFFORT: return pokemonBiosGetPhyAtkEffort(object);
    case STATUS_POKEMON_PHY_DEF_EFFORT: return pokemonBiosGetPhyDefEffort(object);
    case STATUS_POKEMON_SPE_ATK_EFFORT: return pokemonBiosGetSpeAtkEffort(object);
    case STATUS_POKEMON_SPE_DEF_EFFORT: return pokemonBiosGetSpeDefEffort(object);
    case STATUS_POKEMON_NIMBLENESS_EFFORT: return pokemonBiosGetNimblenessEffort(object);
    case STATUS_POKEMON_MAX_HP_RND: return pokemonBiosGetMaxHpRnd(object);
    case STATUS_POKEMON_PHY_ATK_RND: return pokemonBiosGetPhyAtkRnd(object);
    case STATUS_POKEMON_PHY_DEF_RND: return pokemonBiosGetPhyDefRnd(object);
    case STATUS_POKEMON_SPE_ATK_RND: return pokemonBiosGetSpeAtkRnd(object);
    case STATUS_POKEMON_SPE_DEF_RND: return pokemonBiosGetSpeDefRnd(object);
    case STATUS_POKEMON_NIMBLENESS_RND: return pokemonBiosGetNimblenessRnd(object);
    case STATUS_POKEMON_FRIEND: return pokemonBiosGetFriend(object);
    case STATUS_POKEMON_STYLE: return pokemonBiosGetStyle(object);
    case STATUS_POKEMON_BEAUTIFUL: return pokemonBiosGetBeautiful(object);
    case STATUS_POKEMON_CUTE: return pokemonBiosGetCute(object);
    case STATUS_POKEMON_CLEVER: return pokemonBiosGetClever(object);
    case STATUS_POKEMON_STRONG: return pokemonBiosGetStrong(object);
    case STATUS_POKEMON_FUR: return pokemonBiosGetFur(object);
    case STATUS_POKEMON_CHAMP_RIBBON: return pokemonBiosGetChampRibbon(object);
    case STATUS_POKEMON_WINNING_RIBBON: return pokemonBiosGetWinningRibbon(object);
    case STATUS_POKEMON_VICTORY_RIBBON: return pokemonBiosGetVictoryRibbon(object);
    case STATUS_POKEMON_BROMIDE_RIBBON: return pokemonBiosGetBromideRibbon(object);
    case STATUS_POKEMON_GANBA_RIBBON: return pokemonBiosGetGanbaRibbon(object);
    case STATUS_POKEMON_MARINE_RIBBON: return pokemonBiosGetMarineRibbon(object);
    case STATUS_POKEMON_LAND_RIBBON: return pokemonBiosGetLandRibbon(object);
    case STATUS_POKEMON_SKY_RIBBON: return pokemonBiosGetSkyRibbon(object);
    case STATUS_POKEMON_COUNTRY_RIBBON: return pokemonBiosGetCountryRibbon(object);
    case STATUS_POKEMON_NATIONAL_RIBBON: return pokemonBiosGetNationalRibbon(object);
    case STATUS_POKEMON_EARTH_RIBBON: return pokemonBiosGetEarthRibbon(object);
    case STATUS_POKEMON_WORLD_RIBBON: return pokemonBiosGetWorldRibbon(object);
    case STATUS_POKEMON_AMARI_RIBBON: return pokemonBiosGetAmariRibbon(object);
    case STATUS_POKEMON_STYLE_MEDAL: return pokemonBiosGetStyleMedal(object);
    case STATUS_POKEMON_BEAUTIFUL_MEDAL: return pokemonBiosGetBeautifulMedal(object);
    case STATUS_POKEMON_CUTE_MEDAL: return pokemonBiosGetCuteMedal(object);
    case STATUS_POKEMON_CLEVER_MEDAL: return pokemonBiosGetCleverMedal(object);
    case STATUS_POKEMON_STRONG_MEDAL: return pokemonBiosGetStrongMedal(object);
    case STATUS_POKEMON_POKERUS: return pokemonBiosGetPokerus(object);
    case STATUS_POKEMON_TAMAGO_FLAG: return pokemonBiosGetTamagoFlag(object);
    case STATUS_POKEMON_TOKUSEI_FLAG: return pokemonBiosGetTokuseiFlag(object);
    case STATUS_POKEMON_FUSEI_FLAG: return pokemonBiosGetFuseiFlag(object);
    case STATUS_POKEMON_FLAG_AMARI: return pokemonBiosGetFlagAmari(object);
    case STATUS_POKEMON_POKEMON_GET_SEX: return pokemonGetSex(object);
    case STATUS_POKEMON_PCBOX_MARK: return pokemonBiosGetPcboxMark(object);
    case STATUS_POKEMON_MAIL_ID: return pokemonBiosGetMailId(object);
    case STATUS_POKEMON_PARA1_AMARI: return pokemonBiosGetPara1Amari(object);
    case STATUS_POKEMON_AMARI: return pokemonBiosGetAmari(object);
    case STATUS_POKEMON_POKEMON_GET_SEIKAKU: return _pokemonGetSeikaku(object);
    case STATUS_POKEMON_POKEMON_GET_NOW_EXP_TO_LEVEL: return _pokemonGetNowExpToLevel(object);
    case STATUS_POKEMON_POKEMON_CHECK_RARE: return static_cast<u8>(pokemonCheckRare(object));
    case STATUS_POKEMON_FIGHT_TRAINER_POKEMON_DATA_ID: return pokemonBiosGetFightTrainerPokemonDataId(object);
    case STATUS_POKEMON_DARKPOKEMON_DATA_ID: return pokemonBiosGetDarkpokemonDataId(object);
    case STATUS_POKEMON_INIT_DP: return pokemonBiosGetInitDp(object);
    case STATUS_POKEMON_DP: return pokemonBiosGetDp(object);
    case STATUS_POKEMON_POOL_EXP: return pokemonBiosGetPoolExp(object);
    case STATUS_POKEMON_POOL_FRIEND: return pokemonBiosGetPoolFriend(object);
    case STATUS_POKEMON_DARK_FLAG: return pokemonBiosGetDarkFlag(object);
    case 0xc8: return 0;
    case STATUS_FIGHT_MOTO_POKEMON_PTR: return reinterpret_cast<u32>(fightPokemonBiosGetMotoPokemonPtr(reinterpret_cast<FightPokemon*>(object)));
    case STATUS_FIGHT_POKEMON_BUFF_PTR: return reinterpret_cast<u32>(fightPokemonBiosGetPokemonBuffPtr(reinterpret_cast<FightPokemon*>(object)));
    case STATUS_FIGHT_CONDITION_COPY: return reinterpret_cast<u32>(fightPokemonBiosGetFightJoutaiPtr(reinterpret_cast<FightPokemon*>(object), index));
    case STATUS_FIGHT_ENTRY_ID: return fightPokemonBiosGetEntryId(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_CATCH_ENTRY_FLAG: return fightPokemonBiosGetCatchEntryFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_LEVEL_UP_FLAG: return fightPokemonBiosGetLevelUpFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_DARK_OUT_FLAG: return fightPokemonBiosGetDarkOutFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_HOKAKU_FLAG: return fightPokemonBiosGetHokakuFlag(reinterpret_cast<FightPokemon*>(object));
    case STATUS_FIGHT_OUT_MOTO_FIGHT_POKEMON_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetMotoFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightPokemonPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_POKEMON_HENSIN_BUFF_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightPokemonHensinBuffPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHTOUT_JOUTAI_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightoutJoutaiPtr(reinterpret_cast<FightOutPokemon*>(object), index));
    case STATUS_FIGHT_OUT_FIGHT_WAZA_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_USE_WAZA_DATA_ID: return fightOutPokemonGetUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MOTO_WAZA_DATA_ID: return fightOutPokemonGetMotoWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_VALUE: return fightWaza_GetDamageValue(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_CRITICAL: return fightWaza_GetCritical(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_WRITE_MOVE_CONDITION: return fightWazaIsJoutaiDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)), index);
    case STATUS_FIGHT_OUT_IS_HIT: return fightWazaIsHit(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_DAMAGE: return fightWaza_GetDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_IRYOKU: return fightWaza_GetIryoku(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_TARGET_DATA_ID: return fightWaza_GetTargetDataId(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_HIT_DAMAGE: return fightWaza_GetHitDamage(fightOutPokemon_GetFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_FIGHT_ITEM_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightItemPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_ABICNT_PHY_ATK: return fightOutPokemonBiosGetAbicntPhyAtk(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_PHY_DEF: return fightOutPokemonBiosGetAbicntPhyDef(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_SPE_ATK: return fightOutPokemonBiosGetAbicntSpeAtk(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_SPE_DEF: return fightOutPokemonBiosGetAbicntSpeDef(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_NIMBLENESS: return fightOutPokemonBiosGetAbicntNimbleness(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_AVERAGE: return fightOutPokemonBiosGetAbicntAverage(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ABICNT_AVOID: return fightOutPokemonBiosGetAbicntAvoid(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHTOUT_TURN_COUNT: return fightOutPokemonBiosGetFightoutTurnCount(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_SEQUENCE_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetSequencePtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_SKETCH_WAZA_DATA_ID: return fightOutPokemonBiosGetSketchWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_SELECT_WAZA_DATA_ID: return fightOutPokemonBiosGetLastSelectWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_USE_WAZA_DATA_ID: return fightOutPokemonBiosGetLastUseWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_LAST_RECEIVE_WAZA_TARGET_DATA_ID: return fightOutPokemonBiosGetLastReceiveWazaTargetDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIT_WAZA_DATA_ID: return fightOutPokemonBiosGetHitWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIT_WAZA_ZOKUSEI_DATA_ID: return fightOutPokemonBiosGetHitWazaZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_VALUE: return fightOutPokemonBiosGetGamanDamageValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_GAMAN_DAMAGE_TARGET_ID: return fightOutPokemonBiosGetGamanDamageTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_OUMU_WAZA_DATA_ID: return fightOutPokemonBiosGetOumuWazaDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KEEP_FIGHT_WAZA_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetKeepFightWazaPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_NAMAKE_FLAG: return fightOutPokemonBiosGetNamakeFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_USED_ITEM_DATA_ID: return fightOutPokemonBiosGetUsedItemDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_STOCK_ITEM_DATA_ID: return fightOutPokemonBiosGetStockItemDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_SUCCESS_CNT: return fightOutPokemonBiosGetSuccessCnt(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MEET_ENEMY_FIGHT_POKEMON_ENTRY_ID: return fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index));
    case STATUS_FIGHT_OUT_FIGHT_ACTION_BUFF_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightActionBuffPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_ZOKUSEI_DATA_ID: return fightOutPokemonBiosGetZokuseiDataId(reinterpret_cast<FightOutPokemon*>(object), static_cast<u8>(index));
    case STATUS_FIGHT_OUT_TOKUSEI_DATA_ID: return fightOutPokemonBiosGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_WAZA_MENU_CUR_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetWazaMenuCurPtr(reinterpret_cast<FightOutPokemon*>(object)));
    case STATUS_FIGHT_OUT_DAMAGE_ATK_VALUE: return fightOutPokemonBiosGetDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_ATK_TARGET_ID: return fightOutPokemonBiosGetDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_SPE_VALUE: return fightOutPokemonBiosGetDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DAMAGE_SPE_TARGET_ID: return fightOutPokemonBiosGetDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MAHI_NO_ATTACK_FLAG: return fightOutPokemonBiosGetMahiNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KONRAN_MYSELF_ATTACK_FLAG: return fightOutPokemonBiosGetKonranMyselfAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_OUT_WAZA_KOUKANAI_FLAG: return fightOutPokemonBiosGetOutWazaKoukanaiFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_TAME_WAZA_FLAG: return fightOutPokemonBiosGetTameWazaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ITEM_NIGERU_FLAG: return fightOutPokemonBiosGetItemNigeruFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HUUIN_NO_ATTACK_FLAG: return fightOutPokemonBiosGetHuuinNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MERO_MERO_NO_ATTACK_FLAG: return fightOutPokemonBiosGetMeroMeroNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KANASHIBARI_NO_ATTACK_FLAG: return fightOutPokemonBiosGetKanashibariNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_CHOUHATSU_NO_ATTACK_FLAG: return fightOutPokemonBiosGetChouhatsuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ICHAMON_NO_ATTACK_FLAG: return fightOutPokemonBiosGetIchamonNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_HIRUMU_NO_ATTACK_FLAG: return fightOutPokemonBiosGetHirumuNoAttackFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_PASS_PPDEC_FLAG: return fightOutPokemonBiosGetPassPpdecFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHT_ACTION_FLAG: return fightOutPokemonBiosGetFightActionFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_CLEARBODY_FLAG: return fightOutPokemonBiosGetDoClearbodyFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_RECEIVES_WAZA_HIRAISHIN_FLAG: return fightOutPokemonBiosGetReceivesWazaHiraishinFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_VANISHOFF_FLAG: return fightOutPokemonBiosGetVanishoffFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_IKAKU_FLAG: return fightOutPokemonBiosGetDoIkakuFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_DO_TRACE_FLAG: return fightOutPokemonBiosGetDoTraceFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_NO_PRESSURE_FLAG: return fightOutPokemonBiosGetNoPressureFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_IREKAETA_FLAG: return fightOutPokemonBiosGetIrekaetaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_ITEM_KORAETA_FLAG: return fightOutPokemonBiosGetItemKoraetaFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KAIGARA_DAMAGE_VALUE: return fightOutPokemonBiosGetKaigaraDamageValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_VALUE: return fightOutPokemonBiosGetMyselfDamageAtkValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_TARGET_ID: return fightOutPokemonBiosGetMyselfDamageAtkTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_VALUE: return fightOutPokemonBiosGetMyselfDamageSpeValue(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_TARGET_ID: return fightOutPokemonBiosGetMyselfDamageSpeTargetId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_KIZETU_FLAG: return fightOutPokemonBiosGetKizetuFlag(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_IREKAE_TARGET_ENTRY_ID: return fightOutPokemonBiosGetIrekaeTargetEntryId(reinterpret_cast<FightOutPokemon*>(object));
    case STATUS_FIGHT_OUT_FIGHT_OUT_POKEMON_ENEMY_PTR: return reinterpret_cast<u32>(fightOutPokemonBiosGetFightOutPokemonEnemyPtr(reinterpret_cast<FightOutPokemon*>(object), index));
    case STATUS_FIGHT_OUT_CHECK_FIGHT_OUT: return fightOutPokemonCheckFightOut(reinterpret_cast<FightOutPokemon*>(object));
    default: return 0;
    }
}
