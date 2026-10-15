#include <game/pxdvs/app/fight/fightPokemon.hpp>
#include <game/pxdvs/app/fight/fightPokemonConditions.hpp>

struct FightTrainer;
struct FightTrainerEnemyPokemon;
struct Hero;
struct FightTrainerKindData;
struct ModelSequence;
struct WazaSequence;

extern "C" {
u8 fightPokemonCheckValid(FightPokemon*);
u8 fightPokemonCheckFightOut(FightPokemon*);
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u8 fightPokemonCheckMotoFightPokemon(FightPokemon*, FightOutPokemon*);
u8 fightOutPokemonCheckIrekaeReserveFightPokemon(FightOutPokemon*, FightPokemon*);
u16 fightTrainer_GetFightTrainerDataId(FightTrainer*);
Hero* fightTrainer_GetHeroPtr(FightTrainer*);
FightPokemon* fightTrainer_GetFightPokemonPtr(FightTrainer*, u16);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FightTrainer*, u16);
FightOutPokemon* fightTrainer_GetFightoutPokemonBuffPtr(FightTrainer*);
FightActionBuff* fightTrainer_GetFightActionBuffPtr(FightTrainer*);
FightTrainerEnemyPokemon* fightTrainer_GetFightTrainerEnemyPokemonAryPtr(FightTrainer*, u8);
void* fightTrainer_GetSequencePtr(FightTrainer*);
u8 fightTrainer_GetControllerId(FightTrainer*);
void fightTrainer_SetFightTrainerDataId(FightTrainer*, u32);
void fightTrainer_SetControllerId(FightTrainer*, u8);
void fightTrainer_SetSequencePtr(FightTrainer*, void*);
void fightTrainer_SetOkaneBai(FightTrainer*, u32);
void fightTrainer_SetKoban(FightTrainer*, u32);
void fightTrainer_SetNigeruCount(FightTrainer*, u32);
u32 fightTrainerDB_GetKindDataId(u16);
u32 fightTrainerDB_GetPkxDataId(u16);
u32 fightTrainerDB_GetAiDataId(u16);
FightTrainerKindData* fightTrainerKindDataBiosGetPtr(u8);
u32 fightTrainerKindDataBiosGetPrefixName(FightTrainerKindData*);
u16* GSmsgGetGSchar(u32);
u32 heroGetStatus(Hero*, u32, u32);
u8 heroIsMinePokemon(Hero*, Pokemon*);
u8 heroCheckValid(Hero*);
void heroInit(Hero*);
void heroBiosCopy(Hero*, Hero*);
u16 fightGetFightResultId();
Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
void fightPokemonInitAry(FightPokemon*, u16);
void fightOutPokemonInitAry(FightOutPokemon*, u16);
u8 fightActionCheckValid(FightActionBuff*);
u32 fightOutPokemonGetFightActionUseItemDataId(FightOutPokemon*);
u8 fightOutPokemonIsFightActionUseItemKind(FightOutPokemon*, u32, u32, u32);
u8 fightTrainerEnemyPokemonCheckValid(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonInitFightOutStatus(FightTrainerEnemyPokemon*);
void fightTrainerEnemyPokemonInitAry(FightTrainerEnemyPokemon*, u8);
FightTrainerEnemyPokemon* fightTrainerEnemyPokemonSearchAry(FightTrainerEnemyPokemon*, u8, s16);
u8 pokemonCheckValid(Pokemon*);
u8 pokemonIsJoutaiNormal(Pokemon*);
u32 pokemonGetSoubiItemDataId(Pokemon*);
void pokemonBiosCopy(Pokemon*, Pokemon*);
void pokemonSetCountAsJoutaiDataId(Pokemon*, u16, u8);
void pokemon_SetItemDataId(Pokemon*, u32);
void* Sequence_LoadTrainer(u16);
void Sequence_SetVisibility(void*, u8);
void fightFloorSetShadow();
void fightTrainerInit(FightTrainer*);
void fightTrainerInitFightActionBuff(FightTrainer*);
bool fightTrainerCheckValid(FightTrainer*);
u32 fightTrainerCheckCanIrekaeFightPokemon(FightTrainer*, FightPokemon*);
u8 fightTrainerCheckIrekaeReserveFightPokemon(FightTrainer*, FightPokemon*);
FightOutPokemon* fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(FightTrainer*, FightPokemon*);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer*, u16);
FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer*, u16);
FightPokemon* fightTrainerSearchIrekaeFightPokemon(FightTrainer*, u16*);
FightPokemon* fightTrainerCheckTemotiPokemonFightEntry(FightTrainer*, Pokemon*);
u8 fightTrainerIsMinePokemon(FightTrainer*, Pokemon*);
u8 fightTrainerIsGcHero(FightTrainer*);
u32 fightTrainerGetDoFightOutFightPokemonCount(FightTrainer*);
}

static u8 _fightTrainerGetHeroKind(u16 id) {
    u8 kind = fightTrainerDB_GetKindDataId(id);
    if (kind == 1) return 0;
    if (kind == 2 || kind == 3) return 1;
    return 2;
}

extern "C" {
u16 fightTrainerGetSelectedItemDataId(FightTrainer* trainer, u16* items) {
    u16 i;
    FightOutPokemon* poke;
    u16 count;
    for (i = 0; i < 2; i++) items[i] = 0;
    count = 0;
    for (i = 0; i < 2; i++) {
        poke = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fightOutPokemonCheckFightOut(poke)) {
            u32 item = fightOutPokemonGetFightActionUseItemDataId(poke);
            if (static_cast<u16>(item) != 0) items[count++] = item;
        }
    }
    return count;
}

u8 fightTrainerIsUsedItem(FightTrainer* trainer) {
    FightOutPokemon* poke;
    u16 i;
    for (i = 0; i < 2; i++) {
        poke = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fightOutPokemonCheckFightOut(poke) && fightOutPokemonIsFightActionUseItemKind(poke, 1, 0, 0) == 1) return 1;
    }
    return 0;
}

u8 fightTrainerIsSelectedItemBall(FightTrainer* trainer) {
    FightOutPokemon* poke;
    u16 i;
    for (i = 0; i < 2; i++) {
        poke = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (fightOutPokemonCheckFightOut(poke) && fightOutPokemonIsFightActionUseItemKind(poke, 1, 1, 0) == 1) return 1;
    }
    return 0;
}

FightPokemon* fightTrainerSearchInvalidFightPokemonPtr(FightTrainer* trainer, u16 count) {
    if (trainer == nullptr) return nullptr;
    for (u16 i = 0; i < count; i++) {
        FightPokemon* poke = fightTrainer_GetFightPokemonPtr(trainer, i);
        if (fightPokemonCheckValid(poke) == 0) return poke;
    }
    return nullptr;
}

u16* fightTrainerGetPrefixNamePtr(FightTrainer* trainer) {
    if (trainer == nullptr) return nullptr;
    if (fightTrainerCheckValid(trainer) == 0) return nullptr;
    u32 kind = fightTrainerDB_GetKindDataId(fightTrainer_GetFightTrainerDataId(trainer));
    return GSmsgGetGSchar(fightTrainerKindDataBiosGetPrefixName(fightTrainerKindDataBiosGetPtr(kind)));
}

u16* fightTrainerGetNamePtr(FightTrainer* trainer) {
    if (trainer == nullptr) return nullptr;
    if (fightTrainerCheckValid(trainer) == 0) return nullptr;
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == nullptr) return nullptr;
    return reinterpret_cast<u16*>(heroGetStatus(hero, 1, 0));
}

u16 fightTrainerGetHikaeFightPokemonNum(FightTrainer* trainer, u16 count, u16 activeCount) {
    if (trainer == nullptr) return 0;
    u16 i;
    u16 available = 0;
    u16 active = 0;
    for (i = 0; i < count; i++) {
        FightPokemon* poke = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (poke != nullptr) {
            u8 state = fightTrainerCheckCanIrekaeFightPokemon(trainer, poke);
            if (state == 1) {
            } else if (state == 2) {
                active++;
            } else {
                available++;
            }
        }
    }
    while (true) {
        if (active >= activeCount) break;
        if (available < 1) break;
        available--;
        active++;
    }
    return available;
}

void fightTrainerInitEnemyPokemonFightOutStatus(FightTrainer* trainer, u8 validOnly) {
    if (trainer != nullptr) {
        FightTrainerEnemyPokemon* enemy;
        u8 i;
        for (i = 0; i < 12; i++) {
            enemy = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, i);
            if (validOnly == 1 && !fightTrainerEnemyPokemonCheckValid(enemy)) continue;
            fightTrainerEnemyPokemonInitFightOutStatus(enemy);
        }
    }
}

FightOutPokemon* fightTrainerGetNoActionFightOutPokemonPtr(FightTrainer* trainer, u16 slot) {
    FightOutPokemon* poke = fightTrainerGetValidFightOutPokemonPtr(trainer, slot);
    if (poke == nullptr) return nullptr;
    FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(poke);
    if (action == nullptr) return nullptr;
    if (fightActionCheckValid(action) == 1) return nullptr;
    return poke;
}

s16 fightTrainerGetFightOutPokemonToTemotiBanme(FightTrainer* trainer, FightOutPokemon* poke) {
    if (trainer == nullptr) return -1;
    if (poke == nullptr) return -1;
    for (s16 i = 0; i < 2; i++) {
        if (poke == fightTrainer_GetFightoutPokemonPtr(trainer, i)) return i;
    }
    return -1;
}

s16 fightTrainerGetFightPokemonToTemotiBanme(FightTrainer* trainer, FightPokemon* poke) {
    if (trainer == nullptr) return -1;
    if (poke == nullptr) return -1;
    for (s16 i = 0; i < 6; i++) {
        if (poke == fightTrainer_GetFightPokemonPtr(trainer, i)) return i;
    }
    return -1;
}

void fightTrainerBackFightPokemonToTemotiPokemon(FightTrainer* trainer, u8 restoreItem) {
    if (trainer != nullptr) {
        for (u16 i = 0; i < 6; i++) {
            FightPokemon* record = fightTrainerGetValidFightPokemonPtr(trainer, i);
            if (record == nullptr) continue;
            Pokemon* buff = fightPokemon_GetPokemonBuffPtr(record);
            if (buff == nullptr) continue;
            u32 item = pokemonGetSoubiItemDataId(buff);
            Pokemon* original = fightPokemon_GetMotoPokemonPtr(record);
            if (original == nullptr) continue;
            pokemonBiosCopy(original, buff);
            if (pokemonIsJoutaiDataId(original, 4) == 1) pokemonSetCountAsJoutaiDataId(original, 4, 1);
            if (restoreItem == 1) pokemon_SetItemDataId(original, item);
        }
    }
}

u16 fightTrainerGetIrekaeFightPokemonAry(FightTrainer* trainer, FightPokemon** records) {
    u16 index;
    for (index = 0; index < 6; index++) records[index] = nullptr;
    index = 0;
    u16 count = 0;
    while (true) {
        FightPokemon* poke = fightTrainerSearchIrekaeFightPokemon(trainer, &index);
        if (poke == nullptr) break;
        records[count++] = poke;
        index++;
    }
    return count;
}

FightPokemon* fightTrainerSearchIrekaeFightPokemon(FightTrainer* trainer, u16* index) {
    if (trainer == nullptr) return nullptr;
    if (index == nullptr) return nullptr;
    FightPokemon* poke;
    for (; *index < 6; (*index)++) {
        poke = fightTrainer_GetFightPokemonPtr(trainer, *index);
        if (!(u8)fightTrainerCheckCanIrekaeFightPokemon(trainer, poke)) break;
    }
    if (*index >= 6) return nullptr;
    return poke;
}

u32 fightTrainerCheckCanIrekaeFightPokemon(FightTrainer* trainer, FightPokemon* poke) {
    if (!fightPokemonCheckFightOut(poke)) return 1;
    if (fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, poke) != nullptr) return 2;
    return fightTrainerCheckIrekaeReserveFightPokemon(trainer, poke) == 1 ? 3 : 0;
}

u8 fightTrainerCheckIrekaeReserveFightPokemon(FightTrainer* trainer, FightPokemon* poke) {
    if (trainer == nullptr) return 0;
    if (poke == nullptr) return 0;
    for (u16 i = 0; i < 2; i++) {
        FightOutPokemon* active = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (active != nullptr && fightOutPokemonCheckIrekaeReserveFightPokemon(active, poke) == 1) return 1;
    }
    return 0;
}

FightOutPokemon* fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(FightTrainer* trainer, FightPokemon* poke) {
    if (trainer == nullptr) return nullptr;
    if (poke == nullptr) return nullptr;
    for (u16 i = 0; i < 2; i++) {
        FightOutPokemon* active = fightTrainerGetValidFightOutPokemonPtr(trainer, i);
        if (active != nullptr && fightPokemonCheckMotoFightPokemon(poke, active) == 1) return active;
    }
    return nullptr;
}

FightOutPokemon* fightTrainerCheckFightPokemonFightOut(FightTrainer* trainer, FightPokemon* poke) {
    if (trainer == nullptr) return nullptr;
    if (poke == nullptr) return nullptr;
    FightOutPokemon* active = fightTrainerGetFightPokemonPtrToFightOutPokemonPtr(trainer, poke);
    if (active != nullptr && !fightOutPokemonCheckFightOut(active)) active = nullptr;
    return active;
}

FightPokemon* fightTrainerGetEntryIdToFightPokemonPtr(FightTrainer* trainer, s16 entry) {
    if (entry < 0) return nullptr;
    for (u16 i = 0; i < 6; i++) {
        FightPokemon* poke = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (poke != nullptr && entry == static_cast<s16>(fightPokemon_GetEntryId(poke))) return poke;
    }
    return nullptr;
}

void* fightTrainerCreateSequence(u16 id) {
    void* sequence = Sequence_LoadTrainer(fightTrainerDB_GetPkxDataId(id));
    if (sequence == nullptr) return nullptr;
    Sequence_SetVisibility(sequence, 0);
    return sequence;
}

u8 fightTrainerCheckCanGetExp(FightTrainer* trainer) {
    return fightTrainerIsGcHero(trainer) == 1;
}

u8 fightTrainerIsMineFightPokemon(FightTrainer* trainer, FightPokemon* poke) {
    Pokemon* pokemon = fightPokemonGetPokemonPtr(poke);
    if (pokemon == nullptr) return 0;
    return fightTrainerIsMinePokemon(trainer, pokemon);
}

u8 fightTrainerIsMinePokemon(FightTrainer* trainer, Pokemon* poke) {
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == nullptr) return 0;
    return heroIsMinePokemon(hero, poke);
}

s32 fightTrainerTimeOutSelectIrekaeFightPokemon(FightTrainer* trainer) {
    u16 index = 0;
    FightPokemon* poke = fightTrainerSearchIrekaeFightPokemon(trainer, &index);
    if (poke != nullptr) return fightPokemon_GetEntryId(poke);
    return -1;
}

void fightTrainerAllInitFightActionBuff(FightTrainer* trainer) {
    fightTrainerInitFightActionBuff(trainer);
    for (u16 i = 0; i < 2; i++) fightOutPokemonInitFightActionBuff(fightTrainer_GetFightoutPokemonPtr(trainer, i));
    fightOutPokemonInitFightActionBuff(fightTrainer_GetFightoutPokemonBuffPtr(trainer));
}

FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer* trainer, u16 slot) {
    FightOutPokemon* poke = fightTrainer_GetFightoutPokemonPtr(trainer, slot);
    if (fightOutPokemonCheckValid(poke) == 0) return nullptr;
    return poke;
}

FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer* trainer, u16 slot) {
    FightPokemon* poke = fightTrainer_GetFightPokemonPtr(trainer, slot);
    if (fightPokemonCheckValid(poke) == 0) return nullptr;
    return poke;
}

u32 fightTrainerGetDoFightOutFightOutPokemonCount(FightTrainer* trainer) {
    u8 i;
    u32 count = 0;
    for (i = 0; i < 2; i++) {
        if (fightOutPokemonCheckFightOut(fightTrainer_GetFightoutPokemonPtr(trainer, i))) count++;
    }
    return count;
}

u32 fightTrainerGetDoFightOutFightPokemonCount(FightTrainer* trainer) {
    u8 i;
    u32 count = 0;
    for (i = 0; i < 6; i++) {
        if (fightPokemonCheckFightOut(fightTrainer_GetFightPokemonPtr(trainer, i))) count++;
    }
    return count;
}

FightPokemon* fightTrainerCheckTemotiPokemonFightEntry(FightTrainer* trainer, Pokemon* pokemon) {
    for (u16 i = 0; i < 6; i++) {
        FightPokemon* poke = fightTrainer_GetFightPokemonPtr(trainer, i);
        if (fightPokemonCheckValid(poke)) {
            Pokemon* original = fightPokemon_GetMotoPokemonPtr(poke);
            if (original != nullptr && pokemon == original) return poke;
        }
    }
    return nullptr;
}

u8 fightTrainerCheckTrainerDataIdValid(u16 id, s32 controller) {
    u32 ai = fightTrainerDB_GetAiDataId(id);
    if (static_cast<u16>(id) == 0) return 0;
    if (static_cast<u16>(ai) == 0 && controller == 0) return 0;
    return 1;
}

bool fightTrainerCheckDoFight(FightTrainer* trainer) {
    if (fightTrainerCheckValid(trainer) == 0) return false;
    return static_cast<u8>(fightTrainerGetDoFightOutFightPokemonCount(trainer)) != 0;
}

bool fightTrainerCheckValid(FightTrainer* trainer) {
    if (trainer == nullptr) return false;
    if (fightGetFightResultId() == 1) return false;
    if (static_cast<u16>(fightTrainer_GetFightTrainerDataId(trainer)) == 0) return false;
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == nullptr) return false;
    return heroCheckValid(hero) != 0;
}

void fightTrainerCreate(FightTrainer* trainer, Hero* source, u32 id, u32 controller, void* sequence) {
    if (trainer != nullptr && source != nullptr) {
        fightTrainerInit(trainer);
        Hero* hero = fightTrainer_GetHeroPtr(trainer);
        if (hero != nullptr) {
            heroBiosCopy(hero, source);
            fightTrainer_SetFightTrainerDataId(trainer, id);
            fightTrainer_SetControllerId(trainer, controller);
            if (sequence != nullptr) {
                fightTrainer_SetSequencePtr(trainer, sequence);
                fightFloorSetShadow();
            }
        }
    }
}

void fightTrainerInit(FightTrainer* trainer) {
    if (trainer != nullptr) {
        heroInit(fightTrainer_GetHeroPtr(trainer));
        fightTrainer_SetFightTrainerDataId(trainer, 0);
        fightPokemonInitAry(fightTrainer_GetFightPokemonPtr(trainer, 0), 6);
        fightOutPokemonInitAry(fightTrainer_GetFightoutPokemonPtr(trainer, 0), 2);
        fightOutPokemonInit(fightTrainer_GetFightoutPokemonBuffPtr(trainer));
        fightTrainer_SetOkaneBai(trainer, 1);
        fightTrainer_SetKoban(trainer, 0);
        fightTrainer_SetNigeruCount(trainer, 0);
        fightTrainer_SetControllerId(trainer, 0);
        fightTrainer_SetSequencePtr(trainer, nullptr);
        fightTrainerInitFightActionBuff(trainer);
        fightTrainerEnemyPokemonInitAry(fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, 0), 12);
    }
}

void fightTrainerInitFightActionBuff(FightTrainer* trainer) {
    FightActionBuff* action = fightTrainer_GetFightActionBuffPtr(trainer);
    if (action != nullptr) fightActionInit(action);
}

u8 fightTrainerIsGcHero(FightTrainer* trainer) {
    return _fightTrainerGetHeroKind(fightTrainer_GetFightTrainerDataId(trainer)) == 0;
}

FightTrainerEnemyPokemon* fightTrainerGetFightEntryIdToEnemyPokemonPtr(FightTrainer* trainer, s16 entry) {
    if (entry < 0) return nullptr;
    FightTrainerEnemyPokemon* enemies = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(trainer, 0);
    if (enemies == nullptr) return nullptr;
    return fightTrainerEnemyPokemonSearchAry(enemies, 12, entry);
}
}

struct FightEncountData;
struct FightKindData;
struct FightTrainerData;
struct FightTarget;
struct FightActionData;
extern "C" {
FightEncountData* fightEncountDataBiosGetPtr(u32);
u32 fightEncountDataBiosGetFightKind(FightEncountData*);
FightKindData* fightKindDataBiosGetPtr(u8);
u8 fightKindDataBiosGetHostEnemyMsgFlag(FightKindData*);
u32 fightEncountDataBiosGetFightTrainerDataId(FightEncountData*, u32);
FightTrainerData* fightTrainerDataBiosGetPtr(u16);
u32 fightTrainerDB_GetName(u16);
u32 charNameBiosSearchIndex(u16);
u32 charNameBiosGetHearFlag(u32);
void GSflagOn(u16);
void fightMsgctrlSetValue(u32, u32);
void fightTrainerAiSelectFightAction(FightTrainer*, u32);
void fightMenuFightTrainerGcHeroOpenMenu(FightTrainer*, u32, u32);
u8 fightMenuFightTrainerAgbHeroOpenMenu(FightTrainer*, u32);
u8 dbgMenuFightGetAllFightTrainerOperateFlag();
s32 fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(FightTrainer*, u32, u32, u32, u32);
s32 fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(FightTrainer*, u32, u32, u32);
s32 fightTrainerAiSelectIrekaeDasuFightPokemon(FightTrainer*, u32, u32, u32);
void Sequence_LoadWaza(void*, u16, u32, u32);
WazaSequence* Sequence_GetWaza(void*, u16, u32);
void WazaSequence_Start(WazaSequence*, u32);
u8 WazaSequence_IsActive(WazaSequence*);
void WazaSequence_Free(WazaSequence*);
void GSthreadSwitch();
u32 pokemon_GetCatchBallId(Pokemon*);
u32 itemBallDB_GetThrowWzxDataId(u8);

void fightTrainerSetNameHearFlag(u32 encounterId) {
    FightEncountData* encounter = fightEncountDataBiosGetPtr(encounterId);
    FightKindData* kind = fightKindDataBiosGetPtr(fightEncountDataBiosGetFightKind(encounter));
    if (kind != nullptr && fightKindDataBiosGetHostEnemyMsgFlag(kind)) {
        u16 id = fightEncountDataBiosGetFightTrainerDataId(encounter, 1);
        if (fightTrainerDataBiosGetPtr(id) != nullptr) {
            u16 name = fightTrainerDB_GetName(id);
            u32 index = charNameBiosSearchIndex(name);
            if (static_cast<u16>(index) != 0) {
                u16 flag = charNameBiosGetHearFlag(index);
                if (flag != 0) GSflagOn(flag);
            }
            fightMsgctrlSetValue(0x59, name);
        }
    }
}

void fightTrainerToMenuBallStatus(FightTrainer* trainer, u8* status) {
    if (trainer != nullptr && fightTrainerCheckValid(trainer)) {
        Hero* hero = fightTrainer_GetHeroPtr(trainer);
        for (u16 i = 0; i < 6; i++) status[i] = 0;
        u16 i;
        for (i = 0; i < 6; i++) {
            Pokemon* pokemon = reinterpret_cast<Pokemon*>(heroGetStatus(hero, 3, i));
            if (!pokemonCheckValid(pokemon)) continue;
            FightPokemon* poke = fightTrainerCheckTemotiPokemonFightEntry(trainer, pokemon);
            if (poke == nullptr) continue;
            if (!fightPokemonCheckValid(poke)) continue;
            if (fightPokemon_GetHokakuFlag(poke) == 1) continue;
            if (!fightPokemonCheckFightOut(poke)) status[i] = 3;
            else if (!pokemonIsJoutaiNormal(fightPokemonGetPokemonPtr(poke))) status[i] = 2;
            else status[i] = 1;
        }
    }
}

u8 fightTrainerSelectFightAction(FightTrainer* trainer, u32 fightType) {
    fightTrainerAllInitFightActionBuff(trainer);
    if (fightGetFightResultId() == 1) return 0;
    u16 id = fightTrainer_GetFightTrainerDataId(trainer);
    u32 ai = fightTrainerDB_GetAiDataId(id);
    s32 controller = fightTrainer_GetControllerId(trainer);
    if (static_cast<u16>(ai) != 0 && controller == 0) {
        fightTrainerAiSelectFightAction(trainer, fightType);
    } else if (_fightTrainerGetHeroKind(id) == 0) {
        fightMenuFightTrainerGcHeroOpenMenu(trainer, fightType, 0);
    } else if (_fightTrainerGetHeroKind(id) == 1) {
        if (!fightMenuFightTrainerAgbHeroOpenMenu(trainer, fightType)) return 0;
    } else {
        fightMenuFightTrainerGcHeroOpenMenu(trainer, fightType, 0);
    }
    return 1;
}

s32 fightTrainerSelectIrekaeFightPokemon(FightTrainer* trainer, u32 first, u32 second, u32 third) {
    u16 id;
    s32 entry = -1;
    id = fightTrainer_GetFightTrainerDataId(trainer);
    u32 ai = fightTrainerDB_GetAiDataId(id);
    if (dbgMenuFightGetAllFightTrainerOperateFlag() == 1) {
        entry = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(trainer, 0, first, second, 0);
    } else {
        s32 controller = fightTrainer_GetControllerId(trainer);
        if (static_cast<u16>(ai) != 0 && controller == 0) {
            entry = fightTrainerAiSelectIrekaeDasuFightPokemon(trainer, first, second, third);
        } else if (_fightTrainerGetHeroKind(id) == 0) {
            entry = fightMenuFightTrainerGcHeroSelectIrekaeFightPokemon(trainer, 0, first, second, 0);
        } else if (_fightTrainerGetHeroKind(id) == 1) {
            entry = fightMenuFightTrainerAgbHeroSelectIrekaeFightPokemon(trainer, first, second, third);
        }
    }
    return entry;
}

void fightTrainerCallEffect(FightTrainer* trainer, u8 phase) {
    void* sequence = fightTrainer_GetSequencePtr(trainer);
    if (sequence == nullptr) return;
    if (phase == 0) {
        Sequence_LoadWaza(sequence, 0x57, 4, 0);
    } else if (phase == 1) {
        WazaSequence_Start(Sequence_GetWaza(sequence, 0x57, 4), 1);
    } else if (phase == 2) {
        WazaSequence* animation = Sequence_GetWaza(sequence, 0x57, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        WazaSequence_Free(Sequence_GetWaza(sequence, 0x57, 4));
    }
}

void fightTrainerBallThrowEffect(FightTrainer* trainer, FightOutPokemon* poke, u8 phase) {
    void* sequence = fightTrainer_GetSequencePtr(trainer);
    if (sequence == nullptr) return;
    u32 effect = itemBallDB_GetThrowWzxDataId(pokemon_GetCatchBallId(fightOutPokemonGetPokemonPtr(poke)));
    if (phase == 0) {
        Sequence_LoadWaza(sequence, effect, 4, 0);
    } else if (phase == 1) {
        WazaSequence_Start(Sequence_GetWaza(sequence, effect, 4), 1);
    } else if (phase == 2) {
        WazaSequence* animation = Sequence_GetWaza(sequence, effect, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 3) {
        WazaSequence_Free(Sequence_GetWaza(sequence, effect, 4));
    }
}
}

struct FightVector { f32 x, y, z; };
extern "C" {
void* snatchSequencePtr;
u8 fightFloor_GetFightKind(void*);
u32 itemBallDB_GetSnatchAttackWzxDataId(u8);
void battleGridBackupModelVisibilityFlags();
void battleGridStoreModelVisibilityFlags();
void Sequence_GetPosition(void*, FightVector*);
void Sequence_GetRotation(void*, FightVector*);
void Sequence_SetPosition(void*, const FightVector*);
void Sequence_SetRotation(void*, const FightVector*);
void Sequence_Free(void*);

void fightTrainerHokakuThrowEffect(FightTrainer* trainer, u8 ball, u8 phase) {
    void* sequence = fightTrainer_GetSequencePtr(trainer);
    if (sequence == nullptr) return;
    WazaSequence* animation;
    u32 effect;
    u8 snatch;
    if (fightFloor_GetFightKind(nullptr) == 0xc || fightFloor_GetFightKind(nullptr) == 0xd) {
        effect = itemBallDB_GetThrowWzxDataId(ball);
        snatchSequencePtr = sequence;
        snatch = 0;
    } else {
        effect = itemBallDB_GetSnatchAttackWzxDataId(ball);
        snatch = 1;
    }
    if (phase == 0) {
        if (snatch != 0) snatchSequencePtr = Sequence_LoadTrainer(0x42);
        Sequence_LoadWaza(snatchSequencePtr, effect, 4, 0);
    } else if (phase == 1) {
        if (snatch != 0) {
            FightVector position;
            FightVector rotation;
            battleGridBackupModelVisibilityFlags();
            Sequence_GetPosition(sequence, &position);
            Sequence_GetRotation(sequence, &rotation);
            Sequence_SetPosition(snatchSequencePtr, &position);
            Sequence_SetRotation(snatchSequencePtr, &rotation);
            Sequence_SetVisibility(sequence, 0);
            battleGridStoreModelVisibilityFlags();
            Sequence_SetVisibility(snatchSequencePtr, 1);
        }
        animation = Sequence_GetWaza(snatchSequencePtr, effect, 4);
        WazaSequence_Start(animation, 1);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 2) {
        WazaSequence_Free(Sequence_GetWaza(snatchSequencePtr, effect, 4));
        if (snatch != 0) {
            Sequence_SetVisibility(snatchSequencePtr, 0);
            Sequence_Free(snatchSequencePtr);
            Sequence_SetVisibility(sequence, 1);
        }
    } else if (phase == 3) {
        Sequence_LoadWaza(sequence, 0x57, 4, 0);
    } else if (phase == 4) {
        WazaSequence_Start(Sequence_GetWaza(sequence, 0x57, 4), 1);
    } else if (phase == 5) {
        animation = Sequence_GetWaza(sequence, 0x57, 4);
        while (WazaSequence_IsActive(animation)) GSthreadSwitch();
    } else if (phase == 6) {
        WazaSequence_Free(Sequence_GetWaza(sequence, 0x57, 4));
    }
}
}

// Trainer database and runtime properties share the original status dispatch.
// The property range selects the record; each case preserves its field width.
struct FightTrainerPokemonPartData;
struct FightTrainerAiValueAddsubData;
class DeckPokemon { public: static DeckPokemon* getDeckPokemonObj(u32); u32 getPokemonID() const; };
class DeckTrainerAI { public: static DeckTrainerAI* getDeckTrainerAIObj(u32); };
enum FightTrainerStatus {
    TRAINER_STATUS_DB_AI_DATA_ID = 0x2,
    TRAINER_STATUS_DB_NAME = 0x3,
    TRAINER_STATUS_DB_KIND_DATA_ID = 0x4,
    TRAINER_STATUS_DB_TEMOTI_POKEMON_ID = 0x5,
    TRAINER_STATUS_DB_TEMOTI_ITEM_DATA_ID = 0x6,
    TRAINER_STATUS_DB_SYOUKAI_WZX_DATA_ID = 0x7,
    TRAINER_STATUS_DB_SERIHU_MSG_ID = 0x8,
    TRAINER_STATUS_DB_PKX_DATA_ID = 0x9,
    TRAINER_STATUS_POKEMON_PART_DB_NAME = 0xb,
    TRAINER_STATUS_POKEMON_PART_DB_WAZA_TYPE_REVISE = 0xc,
    TRAINER_STATUS_POKEMON_DB_NICKNAME = 0xe,
    TRAINER_STATUS_POKEMON_DB_STATUS_RND = 0xf,
    TRAINER_STATUS_POKEMON_DB_STATUS_EFFORT = 0x10,
    TRAINER_STATUS_POKEMON_DB_LEVEL = 0x11,
    TRAINER_STATUS_POKEMON_DB_ITEM_BALL_ID = 0x12,
    TRAINER_STATUS_POKEMON_DB_DARK_POKEMON_FLAG = 0x13,
    TRAINER_STATUS_POKEMON_DB_TOKUSEI_FLAG = 0x14,
    TRAINER_STATUS_POKEMON_DB_POKEMON_DATA_ID = 0x15,
    TRAINER_STATUS_POKEMON_DB_ITEM_DATA_ID = 0x16,
    TRAINER_STATUS_POKEMON_DB_WAZA_DATA_ID = 0x17,
    TRAINER_STATUS_POKEMON_DB_PP_CNT = 0x18,
    TRAINER_STATUS_POKEMON_DB_FRIEND = 0x19,
    TRAINER_STATUS_POKEMON_DB_SEX_DATA_ID = 0x1a,
    TRAINER_STATUS_POKEMON_DB_SEIKAKU_DATA_ID = 0x1b,
    TRAINER_STATUS_POKEMON_DB_KEY_PLAYER_FLAG = 0x1c,
    TRAINER_STATUS_POKEMON_DB_PART_DATA_ID = 0x1d,
    TRAINER_STATUS_AI_DB_POKEMON_SELECT_RANDOM_FLAG = 0x1f,
    TRAINER_STATUS_AI_DB_POKEMON_SELECT_WEAK_POINT_FLAG = 0x20,
    TRAINER_STATUS_AI_DB_POKEMON_DATA_ORDER_OUT_FLAG = 0x21,
    TRAINER_STATUS_AI_DB_POKEMON_DATA_ORDER_ACE_BOSS_FLAG = 0x22,
    TRAINER_STATUS_AI_DB_KEY_PLAYER_FLAG = 0x23,
    TRAINER_STATUS_AI_DB_POKEMON_JOUTAI_FLAG = 0x24,
    TRAINER_STATUS_AI_DB_COMBO_VALUE = 0x25,
    TRAINER_STATUS_AI_DB_IREKAE_VALUE = 0x26,
    TRAINER_STATUS_AI_DB_ITEM_VALUE = 0x27,
    TRAINER_STATUS_AI_DB_PARAM_EXPECT_FLAG = 0x28,
    TRAINER_STATUS_AI_DB_PARAM_STORE_FLAG = 0x29,
    TRAINER_STATUS_AI_DB_ZOKUSEI_CHECK_FLAG = 0x2a,
    TRAINER_STATUS_AI_DB_TOKUSEI_CHECK_FLAG = 0x2b,
    TRAINER_STATUS_AI_DB_NOKORI_HP_VALUE = 0x2c,
    TRAINER_STATUS_AI_DB_WAZA_DAMAGE_FLAG = 0x2d,
    TRAINER_STATUS_AI_DB_ABICNT_MAX_VALUE = 0x2e,
    TRAINER_STATUS_AI_DB_ABICNT_MIN_VALUE = 0x2f,
    TRAINER_STATUS_AI_DB_DEFENSE_POKEMON_RND_SELECT_FLAG = 0x30,
    TRAINER_STATUS_AI_DB_WAZA_RND_SELECT_FLAG = 0x31,
    TRAINER_STATUS_AI_DB_WAZA_INIT_VALUE_FLAG = 0x32,
    TRAINER_STATUS_AI_DB_PART_FLAG = 0x33,
    TRAINER_STATUS_AI_DB_WAZA_HIT_FLAG = 0x34,
    TRAINER_STATUS_AI_DB_WAZA_AVG_VALUE = 0x35,
    TRAINER_STATUS_AI_DB_WAZA_RISK_FLAG = 0x36,
    TRAINER_STATUS_AI_DB_WAZA_NOKORI_PP_VALUE = 0x37,
    TRAINER_STATUS_AI_DB_LAST_VALUE_REVISE = 0x38,
    TRAINER_STATUS_AI_DB_ZOKUSEI_REVISE_ZOKUSEI_DATA_ID = 0x39,
    TRAINER_STATUS_AI_DB_ZOKUSEI_REVISE_VALUE = 0x3a,
    TRAINER_STATUS_AI_DB_WAZA_TYPE_REVISE_TYPE_DATA_ID = 0x3b,
    TRAINER_STATUS_AI_DB_WAZA_TYPE_REVISE_VALUE = 0x3c,
    TRAINER_STATUS_AI_VALUE_ADDSUB_DB_VALUE = 0x3e,
    TRAINER_STATUS_AI_VALUE_ADDSUB_DB_NAME = 0x3f,
    TRAINER_STATUS_AI_VALUE_ADDSUB_DB_KOUDOU_NAME = 0x40,
    TRAINER_STATUS_AI_VALUE_ADDSUB_DB_PREFIX_NAME = 0x41,
    TRAINER_STATUS___HERO_PTR = 0x44,
    TRAINER_STATUS___FIGHT_TRAINER_DATA_ID = 0x43,
    TRAINER_STATUS___FIGHT_POKEMON_PTR = 0x45,
    TRAINER_STATUS___FIGHTOUT_POKEMON_PTR = 0x46,
    TRAINER_STATUS___FIGHTOUT_POKEMON_BUFF_PTR = 0x47,
    TRAINER_STATUS___OKANE_BAI = 0x48,
    TRAINER_STATUS___KOBAN = 0x49,
    TRAINER_STATUS___NIGERU_COUNT = 0x4a,
    TRAINER_STATUS___CONTROLLER_ID = 0x4b,
    TRAINER_STATUS___FIGHT_ACTION_BUFF_PTR = 0x4d,
    TRAINER_STATUS___SEQUENCE_PTR = 0x4c,
    TRAINER_STATUS___FIGHT_TRAINER_ENEMY_POKEMON_ARY_PTR = 0x4e,
    TRAINER_STATUS___ENEMY_NOWHP1BANHIKUI_FLAG = 0x52,
    TRAINER_STATUS___ENEMY_LV1BANHIKUI_FLAG = 0x53,
    TRAINER_STATUS___ENEMY_DEFENSE1BANHIKUI_FLAG = 0x54,
    TRAINER_STATUS___ENEMY_BADWAZA_HAVE_FLAG = 0x55,
    TRAINER_STATUS___ENEMY_PARAM1BANTAKAI_FLAG = 0x56,
};
extern "C" {
FightTrainerPokemonPartData* fightTrainerPokemonPartDataBiosGetPtr(u16);
FightTrainerAiValueAddsubData* fightTrainerAiValueAddsubDataBiosGetPtr(u16);
u32 fightTrainerDB_GetTemotiPokemonId(u16, u8);
u32 fightTrainerDB_GetTemotiItemDataId(u16, u8);
u32 fightTrainerDB_GetSyoukaiWzxDataId(u16);
u32 fightTrainerDB_GetSerihuMsgId(u16, u8);
u32 fightTrainerPokemonPartDB_GetName(u16);
u32 fightTrainerPokemonPartDB_GetWazaTypeRevise(u16, u8);
u32 fightTrainerPokemonDB_GetNickname(u16);
u32 fightTrainerPokemonDB_GetStatusRnd(u16, u8);
u32 fightTrainerPokemonDB_GetStatusEffort(u16, u8);
u32 fightTrainerPokemonDB_GetLevel(u16);
u32 fightTrainerPokemonDB_GetItemBallId(u16);
u32 fightTrainerPokemonDB_GetDarkPokemonFlag(u16);
u32 fightTrainerPokemonDB_GetTokuseiFlag(u16);
u32 fightTrainerPokemonDB_GetPokemonDataId(u16);
u32 fightTrainerPokemonDB_GetItemDataId(u16);
u32 fightTrainerPokemonDB_GetWazaDataId(u16, u8);
u32 fightTrainerPokemonDB_GetPpCnt(u16, u8);
u32 fightTrainerPokemonDB_GetFriend(u16);
u32 fightTrainerPokemonDB_GetSexDataId(u16);
u32 fightTrainerPokemonDB_GetSeikakuDataId(u16);
u32 fightTrainerPokemonDB_GetKeyPlayerFlag(u16);
u32 fightTrainerPokemonDB_GetPartDataId(u16);
u32 fightTrainerAiDB_GetPokemonSelectRandomFlag(u16);
u32 fightTrainerAiDB_GetPokemonSelectWeakPointFlag(u16);
u32 fightTrainerAiDB_GetPokemonDataOrderOutFlag(u16);
u32 fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(u16);
u32 fightTrainerAiDB_GetKeyPlayerFlag(u16);
u32 fightTrainerAiDB_GetPokemonJoutaiFlag(u16);
u32 fightTrainerAiDB_GetComboValue(u16);
u32 fightTrainerAiDB_GetIrekaeValue(u16);
u32 fightTrainerAiDB_GetItemValue(u16);
u32 fightTrainerAiDB_GetParamExpectFlag(u16);
u32 fightTrainerAiDB_GetParamStoreFlag(u16);
u32 fightTrainerAiDB_GetZokuseiCheckFlag(u16);
u32 fightTrainerAiDB_GetTokuseiCheckFlag(u16);
u32 fightTrainerAiDB_GetNokoriHpValue(u16);
u32 fightTrainerAiDB_GetWazaDamageFlag(u16);
u32 fightTrainerAiDB_GetAbicntMaxValue(u16);
u32 fightTrainerAiDB_GetAbicntMinValue(u16);
u32 fightTrainerAiDB_GetDefensePokemonRndSelectFlag(u16);
u32 fightTrainerAiDB_GetWazaRndSelectFlag(u16);
u32 fightTrainerAiDB_GetWazaInitValueFlag(u16);
u32 fightTrainerAiDB_GetPartFlag(u16);
u32 fightTrainerAiDB_GetWazaHitFlag(u16);
u32 fightTrainerAiDB_GetWazaAvgValue(u16);
u32 fightTrainerAiDB_GetWazaRiskFlag(u16);
u32 fightTrainerAiDB_GetWazaNokoriPpValue(u16);
u32 fightTrainerAiDB_GetLastValueRevise(u16);
u32 fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(u16, u8);
u32 fightTrainerAiDB_GetZokuseiReviseValue(u16, u8);
u32 fightTrainerAiDB_GetWazaTypeReviseTypeDataId(u16, u8);
u32 fightTrainerAiDB_GetWazaTypeReviseValue(u16, u8);
u32 fightTrainerAiValueAddsubDB_GetValue(u16);
u32 fightTrainerAiValueAddsubDB_GetName(u16);
u32 fightTrainerAiValueAddsubDB_GetKoudouName(u16);
u32 fightTrainerAiValueAddsubDB_GetPrefixName(u16);
u32 fightTrainer_GetOkaneBai(FightTrainer*);
u32 fightTrainer_GetKoban(FightTrainer*);
u32 fightTrainer_GetNigeruCount(FightTrainer*);
u32 fightTrainer_GetEnemyNowhp1banhikuiFlag(FightTrainer*, s16);
u32 fightTrainer_GetEnemyLv1banhikuiFlag(FightTrainer*, s16);
u32 fightTrainer_GetEnemyDefense1banhikuiFlag(FightTrainer*, s16);
u32 fightTrainer_GetEnemyBadwazaHaveFlag(FightTrainer*, s16);
u32 fightTrainer_GetEnemyParam1bantakaiFlag(FightTrainer*, s16);

u32 fightTrainerGetStatus(FightTrainer* trainer, u16 dataId, u16 property, u16 index) {
    void* object = trainer;
    if (property == 0 || property >= 0x5b) return 0;
    if (property < 0xa) {
        object = fightTrainerDataBiosGetPtr(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0xd) {
        object = fightTrainerPokemonPartDataBiosGetPtr(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0x1e) {
        object = DeckPokemon::getDeckPokemonObj(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0x3d) {
        object = DeckTrainerAI::getDeckTrainerAIObj(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0x42) {
        object = fightTrainerAiValueAddsubDataBiosGetPtr(dataId);
        if (object == nullptr) return 0;
    }
    if (object == nullptr) return 0;
    switch (property) {
    case TRAINER_STATUS_DB_AI_DATA_ID: return static_cast<u16>(fightTrainerDB_GetAiDataId(dataId));
    case TRAINER_STATUS_DB_NAME: return static_cast<u16>(fightTrainerDB_GetName(dataId));
    case TRAINER_STATUS_DB_KIND_DATA_ID: return static_cast<u8>(fightTrainerDB_GetKindDataId(dataId));
    case TRAINER_STATUS_DB_TEMOTI_POKEMON_ID: return static_cast<u16>(fightTrainerDB_GetTemotiPokemonId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_DB_TEMOTI_ITEM_DATA_ID: return static_cast<u16>(fightTrainerDB_GetTemotiItemDataId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_DB_SYOUKAI_WZX_DATA_ID: return static_cast<u16>(fightTrainerDB_GetSyoukaiWzxDataId(dataId));
    case TRAINER_STATUS_DB_SERIHU_MSG_ID: return static_cast<u16>(fightTrainerDB_GetSerihuMsgId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_DB_PKX_DATA_ID: return static_cast<u16>(fightTrainerDB_GetPkxDataId(dataId));
    case TRAINER_STATUS_POKEMON_PART_DB_NAME: return fightTrainerPokemonPartDB_GetName(dataId);
    case TRAINER_STATUS_POKEMON_PART_DB_WAZA_TYPE_REVISE: return static_cast<u8>(fightTrainerPokemonPartDB_GetWazaTypeRevise(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_POKEMON_DB_NICKNAME: return fightTrainerPokemonDB_GetNickname(dataId);
    case TRAINER_STATUS_POKEMON_DB_STATUS_RND: return static_cast<u8>(fightTrainerPokemonDB_GetStatusRnd(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_POKEMON_DB_STATUS_EFFORT: return static_cast<u8>(fightTrainerPokemonDB_GetStatusEffort(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_POKEMON_DB_LEVEL: return static_cast<u8>(fightTrainerPokemonDB_GetLevel(dataId));
    case TRAINER_STATUS_POKEMON_DB_ITEM_BALL_ID: return static_cast<u16>(fightTrainerPokemonDB_GetItemBallId(dataId));
    case TRAINER_STATUS_POKEMON_DB_DARK_POKEMON_FLAG: return static_cast<u8>(fightTrainerPokemonDB_GetDarkPokemonFlag(dataId));
    case TRAINER_STATUS_POKEMON_DB_TOKUSEI_FLAG: return static_cast<u8>(fightTrainerPokemonDB_GetTokuseiFlag(dataId));
    case TRAINER_STATUS_POKEMON_DB_POKEMON_DATA_ID: return static_cast<u16>(fightTrainerPokemonDB_GetPokemonDataId(dataId));
    case TRAINER_STATUS_POKEMON_DB_ITEM_DATA_ID: return static_cast<u16>(fightTrainerPokemonDB_GetItemDataId(dataId));
    case TRAINER_STATUS_POKEMON_DB_WAZA_DATA_ID: return static_cast<u16>(fightTrainerPokemonDB_GetWazaDataId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_POKEMON_DB_PP_CNT: return static_cast<u8>(fightTrainerPokemonDB_GetPpCnt(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_POKEMON_DB_FRIEND: return static_cast<u8>(fightTrainerPokemonDB_GetFriend(dataId));
    case TRAINER_STATUS_POKEMON_DB_SEX_DATA_ID: return static_cast<u8>(fightTrainerPokemonDB_GetSexDataId(dataId));
    case TRAINER_STATUS_POKEMON_DB_SEIKAKU_DATA_ID: return static_cast<u8>(fightTrainerPokemonDB_GetSeikakuDataId(dataId));
    case TRAINER_STATUS_POKEMON_DB_KEY_PLAYER_FLAG: return static_cast<u8>(fightTrainerPokemonDB_GetKeyPlayerFlag(dataId));
    case TRAINER_STATUS_POKEMON_DB_PART_DATA_ID: return static_cast<u8>(fightTrainerPokemonDB_GetPartDataId(dataId));
    case TRAINER_STATUS_AI_DB_POKEMON_SELECT_RANDOM_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPokemonSelectRandomFlag(dataId));
    case TRAINER_STATUS_AI_DB_POKEMON_SELECT_WEAK_POINT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPokemonSelectWeakPointFlag(dataId));
    case TRAINER_STATUS_AI_DB_POKEMON_DATA_ORDER_OUT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPokemonDataOrderOutFlag(dataId));
    case TRAINER_STATUS_AI_DB_POKEMON_DATA_ORDER_ACE_BOSS_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPokemonDataOrderAceBossFlag(dataId));
    case TRAINER_STATUS_AI_DB_KEY_PLAYER_FLAG: return static_cast<u8>(fightTrainerAiDB_GetKeyPlayerFlag(dataId));
    case TRAINER_STATUS_AI_DB_POKEMON_JOUTAI_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPokemonJoutaiFlag(dataId));
    case TRAINER_STATUS_AI_DB_COMBO_VALUE: return static_cast<u8>(fightTrainerAiDB_GetComboValue(dataId));
    case TRAINER_STATUS_AI_DB_IREKAE_VALUE: return static_cast<u8>(fightTrainerAiDB_GetIrekaeValue(dataId));
    case TRAINER_STATUS_AI_DB_ITEM_VALUE: return static_cast<u8>(fightTrainerAiDB_GetItemValue(dataId));
    case TRAINER_STATUS_AI_DB_PARAM_EXPECT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetParamExpectFlag(dataId));
    case TRAINER_STATUS_AI_DB_PARAM_STORE_FLAG: return static_cast<u8>(fightTrainerAiDB_GetParamStoreFlag(dataId));
    case TRAINER_STATUS_AI_DB_ZOKUSEI_CHECK_FLAG: return static_cast<u8>(fightTrainerAiDB_GetZokuseiCheckFlag(dataId));
    case TRAINER_STATUS_AI_DB_TOKUSEI_CHECK_FLAG: return static_cast<u8>(fightTrainerAiDB_GetTokuseiCheckFlag(dataId));
    case TRAINER_STATUS_AI_DB_NOKORI_HP_VALUE: return static_cast<u8>(fightTrainerAiDB_GetNokoriHpValue(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_DAMAGE_FLAG: return static_cast<u8>(fightTrainerAiDB_GetWazaDamageFlag(dataId));
    case TRAINER_STATUS_AI_DB_ABICNT_MAX_VALUE: return static_cast<u8>(fightTrainerAiDB_GetAbicntMaxValue(dataId));
    case TRAINER_STATUS_AI_DB_ABICNT_MIN_VALUE: return static_cast<u8>(fightTrainerAiDB_GetAbicntMinValue(dataId));
    case TRAINER_STATUS_AI_DB_DEFENSE_POKEMON_RND_SELECT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetDefensePokemonRndSelectFlag(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_RND_SELECT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetWazaRndSelectFlag(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_INIT_VALUE_FLAG: return static_cast<u8>(fightTrainerAiDB_GetWazaInitValueFlag(dataId));
    case TRAINER_STATUS_AI_DB_PART_FLAG: return static_cast<u8>(fightTrainerAiDB_GetPartFlag(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_HIT_FLAG: return static_cast<u8>(fightTrainerAiDB_GetWazaHitFlag(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_AVG_VALUE: return static_cast<u8>(fightTrainerAiDB_GetWazaAvgValue(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_RISK_FLAG: return static_cast<u8>(fightTrainerAiDB_GetWazaRiskFlag(dataId));
    case TRAINER_STATUS_AI_DB_WAZA_NOKORI_PP_VALUE: return static_cast<u8>(fightTrainerAiDB_GetWazaNokoriPpValue(dataId));
    case TRAINER_STATUS_AI_DB_LAST_VALUE_REVISE: return static_cast<u8>(fightTrainerAiDB_GetLastValueRevise(dataId));
    case TRAINER_STATUS_AI_DB_ZOKUSEI_REVISE_ZOKUSEI_DATA_ID: return static_cast<u8>(fightTrainerAiDB_GetZokuseiReviseZokuseiDataId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_AI_DB_ZOKUSEI_REVISE_VALUE: return static_cast<u8>(fightTrainerAiDB_GetZokuseiReviseValue(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_AI_DB_WAZA_TYPE_REVISE_TYPE_DATA_ID: return static_cast<u8>(fightTrainerAiDB_GetWazaTypeReviseTypeDataId(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_AI_DB_WAZA_TYPE_REVISE_VALUE: return static_cast<u8>(fightTrainerAiDB_GetWazaTypeReviseValue(dataId, static_cast<u8>(index)));
    case TRAINER_STATUS_AI_VALUE_ADDSUB_DB_VALUE: return fightTrainerAiValueAddsubDB_GetValue(dataId);
    case TRAINER_STATUS_AI_VALUE_ADDSUB_DB_NAME: return fightTrainerAiValueAddsubDB_GetName(dataId);
    case TRAINER_STATUS_AI_VALUE_ADDSUB_DB_KOUDOU_NAME: return fightTrainerAiValueAddsubDB_GetKoudouName(dataId);
    case TRAINER_STATUS_AI_VALUE_ADDSUB_DB_PREFIX_NAME: return fightTrainerAiValueAddsubDB_GetPrefixName(dataId);
    case TRAINER_STATUS___HERO_PTR: return reinterpret_cast<u32>(fightTrainer_GetHeroPtr(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___FIGHT_TRAINER_DATA_ID: return static_cast<u16>(fightTrainer_GetFightTrainerDataId(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___FIGHT_POKEMON_PTR: return reinterpret_cast<u32>(fightTrainer_GetFightPokemonPtr(static_cast<FightTrainer*>(object), index));
    case TRAINER_STATUS___FIGHTOUT_POKEMON_PTR: return reinterpret_cast<u32>(fightTrainer_GetFightoutPokemonPtr(static_cast<FightTrainer*>(object), index));
    case TRAINER_STATUS___FIGHTOUT_POKEMON_BUFF_PTR: return reinterpret_cast<u32>(fightTrainer_GetFightoutPokemonBuffPtr(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___OKANE_BAI: return static_cast<u8>(fightTrainer_GetOkaneBai(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___KOBAN: return fightTrainer_GetKoban(static_cast<FightTrainer*>(object));
    case TRAINER_STATUS___NIGERU_COUNT: return static_cast<u8>(fightTrainer_GetNigeruCount(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___CONTROLLER_ID: return static_cast<u8>(fightTrainer_GetControllerId(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___FIGHT_ACTION_BUFF_PTR: return reinterpret_cast<u32>(fightTrainer_GetFightActionBuffPtr(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___SEQUENCE_PTR: return reinterpret_cast<u32>(fightTrainer_GetSequencePtr(static_cast<FightTrainer*>(object)));
    case TRAINER_STATUS___FIGHT_TRAINER_ENEMY_POKEMON_ARY_PTR: return reinterpret_cast<u32>(fightTrainer_GetFightTrainerEnemyPokemonAryPtr(static_cast<FightTrainer*>(object), static_cast<u8>(index)));
    case TRAINER_STATUS___ENEMY_NOWHP1BANHIKUI_FLAG: return static_cast<u8>(fightTrainer_GetEnemyNowhp1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId)));
    case TRAINER_STATUS___ENEMY_LV1BANHIKUI_FLAG: return static_cast<u8>(fightTrainer_GetEnemyLv1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId)));
    case TRAINER_STATUS___ENEMY_DEFENSE1BANHIKUI_FLAG: return static_cast<u8>(fightTrainer_GetEnemyDefense1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId)));
    case TRAINER_STATUS___ENEMY_BADWAZA_HAVE_FLAG: return static_cast<u8>(fightTrainer_GetEnemyBadwazaHaveFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId)));
    case TRAINER_STATUS___ENEMY_PARAM1BANTAKAI_FLAG: return static_cast<u8>(fightTrainer_GetEnemyParam1bantakaiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId)));
    default: return 0;
    }
}
}

extern "C" {
void fightTrainerDB_SetAiDataId(u16, u16);
void fightTrainerDB_SetName(u16, u16);
void fightTrainerDB_SetKindDataId(u16, u8);
void fightTrainerDB_SetTemotiPokemonId(u16, u8, u16);
void fightTrainerDB_SetTemotiItemDataId(u16, u8, u16);
void fightTrainerDB_SetSyoukaiWzxDataId(u16, u16);
void fightTrainerDB_SetSerihuMsgId(u16, u8, u16);
void fightTrainerDB_SetPkxDataId(u16, u16);
void fightTrainerPokemonPartDB_SetName(u16, u32);
void fightTrainerPokemonPartDB_SetWazaTypeRevise(u16, u8, u8);
void fightTrainerPokemonDB_SetNickname(u16, u32);
void fightTrainerPokemonDB_SetStatusRnd(u16, u8, u8);
void fightTrainerPokemonDB_SetStatusEffort(u16, u8, u8);
void fightTrainerPokemonDB_SetLevel(u16, u8);
void fightTrainerPokemonDB_SetItemBallId(u16, u16);
void fightTrainerPokemonDB_SetDarkPokemonFlag(u16, u8);
void fightTrainerPokemonDB_SetTokuseiFlag(u16, u8);
void fightTrainerPokemonDB_SetPokemonDataId(u16, u16);
void fightTrainerPokemonDB_SetItemDataId(u16, u16);
void fightTrainerPokemonDB_SetWazaDataId(u16, u8, u16);
void fightTrainerPokemonDB_SetPpCnt(u16, u8, u8);
void fightTrainerPokemonDB_SetFriend(u16, u8);
void fightTrainerPokemonDB_SetSexDataId(u16, u8);
void fightTrainerPokemonDB_SetSeikakuDataId(u16, u8);
void fightTrainerPokemonDB_SetKeyPlayerFlag(u16, u8);
void fightTrainerPokemonDB_SetPartDataId(u16, u8);
void fightTrainerAiDB_SetPokemonSelectRandomFlag(u16, u8);
void fightTrainerAiDB_SetPokemonSelectWeakPointFlag(u16, u8);
void fightTrainerAiDB_SetPokemonDataOrderOutFlag(u16, u8);
void fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(u16, u8);
void fightTrainerAiDB_SetKeyPlayerFlag(u16, u8);
void fightTrainerAiDB_SetPokemonJoutaiFlag(u16, u8);
void fightTrainerAiDB_SetComboValue(u16, u8);
void fightTrainerAiDB_SetIrekaeValue(u16, u8);
void fightTrainerAiDB_SetItemValue(u16, u8);
void fightTrainerAiDB_SetParamExpectFlag(u16, u8);
void fightTrainerAiDB_SetParamStoreFlag(u16, u8);
void fightTrainerAiDB_SetZokuseiCheckFlag(u16, u8);
void fightTrainerAiDB_SetTokuseiCheckFlag(u16, u8);
void fightTrainerAiDB_SetNokoriHpValue(u16, u8);
void fightTrainerAiDB_SetWazaDamageFlag(u16, u8);
void fightTrainerAiDB_SetAbicntMaxValue(u16, u8);
void fightTrainerAiDB_SetAbicntMinValue(u16, u8);
void fightTrainerAiDB_SetDefensePokemonRndSelectFlag(u16, u8);
void fightTrainerAiDB_SetWazaRndSelectFlag(u16, u8);
void fightTrainerAiDB_SetWazaInitValueFlag(u16, u8);
void fightTrainerAiDB_SetPartFlag(u16, u8);
void fightTrainerAiDB_SetWazaHitFlag(u16, u8);
void fightTrainerAiDB_SetWazaAvgValue(u16, u8);
void fightTrainerAiDB_SetWazaRiskFlag(u16, u8);
void fightTrainerAiDB_SetWazaNokoriPpValue(u16, u8);
void fightTrainerAiDB_SetLastValueRevise(u16, u8);
void fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(u16, u8, u8);
void fightTrainerAiDB_SetZokuseiReviseValue(u16, u8, u8);
void fightTrainerAiDB_SetWazaTypeReviseTypeDataId(u16, u8, u8);
void fightTrainerAiDB_SetWazaTypeReviseValue(u16, u8, u8);
void fightTrainerAiValueAddsubDB_SetValue(u16, u32);
void fightTrainerAiValueAddsubDB_SetName(u16, u32);
void fightTrainerAiValueAddsubDB_SetKoudouName(u16, u32);
void fightTrainerAiValueAddsubDB_SetPrefixName(u16, u32);
void fightTrainer_SetEnemyNowhp1banhikuiFlag(FightTrainer*, s16, u8);
void fightTrainer_SetEnemyLv1banhikuiFlag(FightTrainer*, s16, u8);
void fightTrainer_SetEnemyDefense1banhikuiFlag(FightTrainer*, s16, u8);
void fightTrainer_SetEnemyBadwazaHaveFlag(FightTrainer*, s16, u8);
void fightTrainer_SetEnemyParam1bantakaiFlag(FightTrainer*, s16, u8);
void fightTrainerEnemyPokemonRegistAry(FightTrainerEnemyPokemon*, u8, s16);
void fightTrainerEnemyPokemonEraseAry(FightTrainerEnemyPokemon*, u8, s16);

void fightTrainerSetStatus(FightTrainer* trainer, u16 dataId, u16 property, u16 index, u32 value) {
    void* object = trainer;
    if (property == 0 || property >= 0x5b) return;
    if (property < 0xa) {
        object = fightTrainerDataBiosGetPtr(dataId);
        if (object == nullptr) return;
    } else if (property < 0xd) {
        object = fightTrainerPokemonPartDataBiosGetPtr(dataId);
        if (object == nullptr) return;
    } else if (property < 0x1e) {
        object = DeckPokemon::getDeckPokemonObj(dataId);
        if (object == nullptr) return;
    } else if (property < 0x3d) {
        object = DeckTrainerAI::getDeckTrainerAIObj(dataId);
        if (object == nullptr) return;
    } else if (property < 0x42) {
        object = fightTrainerAiValueAddsubDataBiosGetPtr(dataId);
        if (object == nullptr) return;
    }
    if (object == nullptr) return;
    switch (property) {
    case 0x2: { fightTrainerDB_SetAiDataId(dataId, static_cast<u16>(value)); break; }
    case 0x3: { fightTrainerDB_SetName(dataId, static_cast<u16>(value)); break; }
    case 0x4: { fightTrainerDB_SetKindDataId(dataId, static_cast<u8>(value)); break; }
    case 0x5: { fightTrainerDB_SetTemotiPokemonId(dataId, static_cast<u8>(index), static_cast<u16>(value)); break; }
    case 0x6: { fightTrainerDB_SetTemotiItemDataId(dataId, static_cast<u8>(index), static_cast<u16>(value)); break; }
    case 0x7: { fightTrainerDB_SetSyoukaiWzxDataId(dataId, static_cast<u16>(value)); break; }
    case 0x8: { fightTrainerDB_SetSerihuMsgId(dataId, static_cast<u8>(index), static_cast<u16>(value)); break; }
    case 0x9: { fightTrainerDB_SetPkxDataId(dataId, static_cast<u16>(value)); break; }
    case 0xb: { fightTrainerPokemonPartDB_SetName(dataId, value); break; }
    case 0xc: { fightTrainerPokemonPartDB_SetWazaTypeRevise(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0xe: { fightTrainerPokemonDB_SetNickname(dataId, value); break; }
    case 0xf: { fightTrainerPokemonDB_SetStatusRnd(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x10: { fightTrainerPokemonDB_SetStatusEffort(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x11: { fightTrainerPokemonDB_SetLevel(dataId, static_cast<u8>(value)); break; }
    case 0x12: { fightTrainerPokemonDB_SetItemBallId(dataId, static_cast<u16>(value)); break; }
    case 0x13: { fightTrainerPokemonDB_SetDarkPokemonFlag(dataId, static_cast<u8>(value)); break; }
    case 0x14: { fightTrainerPokemonDB_SetTokuseiFlag(dataId, static_cast<u8>(value)); break; }
    case 0x15: { fightTrainerPokemonDB_SetPokemonDataId(dataId, static_cast<u16>(value)); break; }
    case 0x16: { fightTrainerPokemonDB_SetItemDataId(dataId, static_cast<u16>(value)); break; }
    case 0x17: { fightTrainerPokemonDB_SetWazaDataId(dataId, static_cast<u8>(index), static_cast<u16>(value)); break; }
    case 0x18: { fightTrainerPokemonDB_SetPpCnt(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x19: { fightTrainerPokemonDB_SetFriend(dataId, static_cast<u8>(value)); break; }
    case 0x1a: { fightTrainerPokemonDB_SetSexDataId(dataId, static_cast<u8>(value)); break; }
    case 0x1b: { fightTrainerPokemonDB_SetSeikakuDataId(dataId, static_cast<u8>(value)); break; }
    case 0x1c: { fightTrainerPokemonDB_SetKeyPlayerFlag(dataId, static_cast<u8>(value)); break; }
    case 0x1d: { fightTrainerPokemonDB_SetPartDataId(dataId, static_cast<u8>(value)); break; }
    case 0x1f: { fightTrainerAiDB_SetPokemonSelectRandomFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x20: { fightTrainerAiDB_SetPokemonSelectWeakPointFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x21: { fightTrainerAiDB_SetPokemonDataOrderOutFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x22: { fightTrainerAiDB_SetPokemonDataOrderAceBossFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x23: { fightTrainerAiDB_SetKeyPlayerFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x24: { fightTrainerAiDB_SetPokemonJoutaiFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x25: { fightTrainerAiDB_SetComboValue(dataId, static_cast<u8>(value)); break; }
    case 0x26: { fightTrainerAiDB_SetIrekaeValue(dataId, static_cast<u8>(value)); break; }
    case 0x27: { fightTrainerAiDB_SetItemValue(dataId, static_cast<u8>(value)); break; }
    case 0x28: { fightTrainerAiDB_SetParamExpectFlag(dataId, static_cast<u8>(value)); break; }
    case 0x29: { fightTrainerAiDB_SetParamStoreFlag(dataId, static_cast<u8>(value)); break; }
    case 0x2a: { fightTrainerAiDB_SetZokuseiCheckFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x2b: { fightTrainerAiDB_SetTokuseiCheckFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x2c: { fightTrainerAiDB_SetNokoriHpValue(dataId, static_cast<u8>(value)); break; }
    case 0x2d: { fightTrainerAiDB_SetWazaDamageFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x2e: { fightTrainerAiDB_SetAbicntMaxValue(dataId, static_cast<u8>(value)); break; }
    case 0x2f: { fightTrainerAiDB_SetAbicntMinValue(dataId, static_cast<u8>(value)); break; }
    case 0x30: { fightTrainerAiDB_SetDefensePokemonRndSelectFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x31: { fightTrainerAiDB_SetWazaRndSelectFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x32: { fightTrainerAiDB_SetWazaInitValueFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x33: { fightTrainerAiDB_SetPartFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x34: { fightTrainerAiDB_SetWazaHitFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x35: { fightTrainerAiDB_SetWazaAvgValue(dataId, static_cast<u8>(value)); break; }
    case 0x36: { fightTrainerAiDB_SetWazaRiskFlag(dataId, static_cast<u8>(value) != 0); break; }
    case 0x37: { fightTrainerAiDB_SetWazaNokoriPpValue(dataId, static_cast<u8>(value)); break; }
    case 0x38: { fightTrainerAiDB_SetLastValueRevise(dataId, static_cast<u8>(value)); break; }
    case 0x39: { fightTrainerAiDB_SetZokuseiReviseZokuseiDataId(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x3a: { fightTrainerAiDB_SetZokuseiReviseValue(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x3b: { fightTrainerAiDB_SetWazaTypeReviseTypeDataId(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x3c: { fightTrainerAiDB_SetWazaTypeReviseValue(dataId, static_cast<u8>(index), static_cast<u8>(value)); break; }
    case 0x3e: { fightTrainerAiValueAddsubDB_SetValue(dataId, value); break; }
    case 0x3f: { fightTrainerAiValueAddsubDB_SetName(dataId, value); break; }
    case 0x40: { fightTrainerAiValueAddsubDB_SetKoudouName(dataId, value); break; }
    case 0x41: { fightTrainerAiValueAddsubDB_SetPrefixName(dataId, value); break; }
    case 0x43: { fightTrainer_SetFightTrainerDataId(static_cast<FightTrainer*>(object), static_cast<u16>(value)); break; }
    case 0x48: { fightTrainer_SetOkaneBai(static_cast<FightTrainer*>(object), static_cast<u8>(value)); break; }
    case 0x49: { fightTrainer_SetKoban(static_cast<FightTrainer*>(object), value); break; }
    case 0x4a: { fightTrainer_SetNigeruCount(static_cast<FightTrainer*>(object), static_cast<u8>(value)); break; }
    case 0x4b: { fightTrainer_SetControllerId(static_cast<FightTrainer*>(object), static_cast<u8>(value)); break; }
    case 0x4c: { fightTrainer_SetSequencePtr(static_cast<FightTrainer*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x52: { fightTrainer_SetEnemyNowhp1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId), value != 0); break; }
    case 0x53: { fightTrainer_SetEnemyLv1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId), value != 0); break; }
    case 0x54: { fightTrainer_SetEnemyDefense1banhikuiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId), value != 0); break; }
    case 0x55: { fightTrainer_SetEnemyBadwazaHaveFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId), value != 0); break; }
    case 0x56: { fightTrainer_SetEnemyParam1bantakaiFlag(static_cast<FightTrainer*>(object), static_cast<s16>(dataId), value != 0); break; }
    case 0x57: { FightTrainerEnemyPokemon* enemies = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(static_cast<FightTrainer*>(object), 0);
        if (enemies != nullptr) fightTrainerEnemyPokemonRegistAry(enemies, 12, static_cast<s16>(value)); break; }
    case 0x58: { FightTrainerEnemyPokemon* enemies = fightTrainer_GetFightTrainerEnemyPokemonAryPtr(static_cast<FightTrainer*>(object), 0);
        if (enemies != nullptr) fightTrainerEnemyPokemonEraseAry(enemies, 12, static_cast<s16>(value)); break; }
    case 0x59: { FightTrainerEnemyPokemon* enemy = fightTrainerGetFightEntryIdToEnemyPokemonPtr(static_cast<FightTrainer*>(object), static_cast<s16>(dataId));
        if (enemy != nullptr) fightTrainerEnemyPokemonInitFightOutStatus(enemy); break; }
    default: break;
    }
}
}

// Inventory records contain a data id and quantity, each stored as a halfword.
struct TrainerInventoryItem { u16 dataId; u16 quantity; };
// Record stride from fightTrainerInitAry; member access remains in the bios API.
struct FightTrainer { u8 reserved[0x3744]; };
class FIGHT_ENCOUNT { public: u32 getSwapDeckNO() const; u32 getSwapMode() const; u32 getFightMode() const; u32 getAddMode() const; u32 getAddPlace() const; u32 getAddID() const; };
extern "C" {
TrainerInventoryItem* heroItemGetItemKindToItemAryPtr(Hero*, u32, u16*, u32, u32, u32);
u8 itemCheckValid(TrainerInventoryItem*);
u32 item_GetItemDataId(TrainerInventoryItem*);
u32 item_GetNum(TrainerInventoryItem*);
FightTarget* fightTargetGetPtr(u32, void*, u32);
FIGHT_ENCOUNT* fightEncountGetStrObj();
void fightTrainerAiSortFirstSelectPokemonAry(FightTrainer*, Hero*, Pokemon**, u16, u32);
void* memcpy(void*, const void*, unsigned long);

u16 fightTrainerGetTemotiNormalItemDataIdAry(FightTrainer* trainer, u16* ids, u16 capacity, u8 excludeSelected) {
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == nullptr) return 0;
    u16 itemCount;
    TrainerInventoryItem* items = heroItemGetItemKindToItemAryPtr(hero, 2, &itemCount, 0, 0, 0);
    if (items == nullptr) return 0;
    u16 selected[2];
    u16 selectedCount = fightTrainerGetSelectedItemDataId(trainer, selected);
    for (u16 i = 0; i < capacity; i++) ids[i] = 0;
    u16 i;
    u16 count = 0;
    for (i = 0; i < itemCount; i++) {
        TrainerInventoryItem* item = &items[i];
        if (!itemCheckValid(item)) continue;
        u32 id = item_GetItemDataId(item);
        if (static_cast<u16>(id) == 0) continue;
        u32 quantity = item_GetNum(item);
        if (static_cast<u16>(quantity) == 0) continue;
        if (excludeSelected == 1) {
            for (u16 j = 0; j < selectedCount; j++) {
                if (static_cast<u16>(id) == selected[j] && static_cast<u16>(quantity) != 0) quantity--;
            }
            if (static_cast<u16>(quantity) == 0) continue;
        }
        if (count < capacity) ids[count++] = id;
    }
    return count;
}

u8 fightTrainerIsAllyFightTargetPtr(FightTrainer* trainer, FightTarget* target, u32 side) {
    if (trainer == nullptr) return 0;
    if (target == nullptr) return 0;
    FightTarget* ownTarget = fightTargetGetPtr(2, trainer, side);
    return ownTarget == fightTargetGetPtr(2, target, side);
}

void fightTrainerInitAry(FightTrainer* trainers, u16 count) {
    if (trainers != nullptr) {
        for (u16 i = 0; i < count; i++) fightTrainerInit(&trainers[i]);
    }
}

void fightTrainerSortFightTrainerDataIdToHeroTemotiPokemon(FightTrainer* trainer, u16 count, u32 mode) {
    u16 swapDeck = fightEncountGetStrObj()->getSwapDeckNO();
    if (trainer == nullptr || !fightTrainerCheckValid(trainer)) return;
    u16 id = fightTrainer_GetFightTrainerDataId(trainer);
    u32 ai = fightTrainerDB_GetAiDataId(id);
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (static_cast<u16>(ai) == 0) return;
    if (_fightTrainerGetHeroKind(id) == 0) return;
    if (_fightTrainerGetHeroKind(id) == 1) return;
    if (swapDeck != 0 && static_cast<u8>(fightTrainerAiDB_GetPokemonDataOrderOutFlag(ai)) == 1) return;
    Pokemon* selected[6];
    Pokemon roster[6];
    for (u8 i = 0; i < 6; i++) {
        selected[i] = nullptr;
        pokemonInit(reinterpret_cast<u32>(&roster[i]));
    }
    if (count > 6) count = 6;
    fightTrainerAiSortFirstSelectPokemonAry(trainer, hero, selected, count, mode);
    u8 used = 0;
    for (u8 i = 0; i < static_cast<int>(count); i++) {
        Pokemon* pokemon = selected[i];
        if (pokemon != nullptr && pokemonCheckValid(pokemon)) {
            memcpy(&roster[used], pokemon, sizeof(Pokemon));
            used++;
        }
    }
    for (u8 i = 0; i < 6; i++) {
        Pokemon* pokemon = reinterpret_cast<Pokemon*>(heroGetStatus(hero, 3, i));
        if (pokemon != nullptr) memcpy(pokemon, &roster[i], sizeof(Pokemon));
    }
}
}

extern "C" {
u8 fightOutPokemonCheckFightActionWazaSelect(FightOutPokemon*, u8);
u8 fightOutPokemonCheckCanOutOkWazaBanme(FightOutPokemon*, u16, u8, u16*);
FightTarget* fightSeqSelectDefensePokemonPtr(FightOutPokemon*, u32, u8,
    FightTarget* (*)(FightOutPokemon*, u16, u16), u32, u32, s32);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(FightTarget*, u8);
extern FightActionData fight_action_data_waza;
FightActionBuff* fightOutPokemonCreateFightActionAttackWaza(FightOutPokemon*, u32, u32, u32,
    FightActionData*, u16, u32, s32, u8);
u32 pokemon_GetPokemonWazaDataId(Pokemon*, u16);
void fightTrainerTimeOutSelectFightAction(FightTrainer*, FightOutPokemon* poke, u8 side) {
    if (!fightOutPokemonCheckFightActionWazaSelect(poke, 1)) {
        u32 move;
        s32 slot;
        for (slot = 0; static_cast<s8>(slot) < 4; slot++) {
            move = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(poke), 0);
            if (!fightOutPokemonCheckCanOutOkWazaBanme(poke, static_cast<s8>(slot), 1, nullptr)) {
                move = pokemon_GetPokemonWazaDataId(fightOutPokemonGetPokemonPtr(poke), static_cast<s8>(slot));
                break;
            }
        }
        FightTarget* target = fightSeqSelectDefensePokemonPtr(poke, move, side, nullptr, 1, 0, -1);
        u32 targetId = fightTargetGetTragetPtrToRelativeHostSideFightTargetId(target, side);
        fightOutPokemonCreateFightActionAttackWaza(poke, 0, 0x13, 0, &fight_action_data_waza,
            static_cast<u16>(move), targetId, slot, 0);
    }
}
}

extern "C" {
Pokemon* heroBiosGetPokemonPtr(Hero*, u32);
u16* heroBiosGetNamePtr(Hero*);
void heroSetStatus(Hero*, u32, u32);
u32 heroCreateRnd();
void heroCreate(Hero*, u16*, u32);
u32 pokemon_GetPokemonDataId(Pokemon*);
u32 pokemon_GetRnd(Pokemon*);
u32 pokemon_GetLevel(Pokemon*);
void pokemon_SetCatchTrainerRnd(Pokemon*, u32);
void pokemon_SetLevel(Pokemon*, u32);
void pokemon_SetExp(Pokemon*, u32);
u32 pokemonGetLevelToExp(Pokemon*, u32);
u32 fightGetFightEncountDataId();
u32 fightEncountDataBiosGetDiskId(FightEncountData*);
u32 fightTrainerDB_GetSexDataId(u16);
u32 savedataGetStatus(u32, u32);
s32 heroItemAddItemDataId(Hero*, u32, u8, s32);
}
u32 deckDataVirtualDB_GetItemID(u16, u8);
u32 deckDataVirtualDB_GetItemNum(u16, u8);
void _fightTrainerCreateDeckBingo(u16, Hero*);
void _fightTrainerCreateDeckVirtual(u16, Hero*, u16);
void _fightTrainerCreateDeckUnderTakerInColosseum(u16, Hero*, u16);
void _fightTrainerCreateDeckUnderTaker(u16, Hero*, u16);
void _fightTrainerCreateDeckWildPoke(u16, Hero*);
void _fightTrainerCreateDeckNormal(u16, Hero*, u16);

static void _fightTrainerCreateRndCheckRare(Hero* hero, bool rare) {
    Pokemon* roster[6];
    u16 attempts = 10000;
    for (u8 i = 0; i < 6; i++) roster[i] = nullptr;
    u32 rnd = heroGetStatus(hero, 2, 0);
    do {
        u8 mismatch = 0;
        for (u8 i = 0; i < 6; i++) {
            roster[i] = heroBiosGetPokemonPtr(hero, i);
            Pokemon* poke = roster[i];
            if (poke == nullptr) continue;
            if (static_cast<u16>(pokemon_GetPokemonDataId(poke)) == 0) continue;
            u32 personality = pokemon_GetRnd(poke);
            if (personality == 0) continue;
            if (static_cast<u8>(rare) != static_cast<u8>(pokemonCheckRareRnd(rnd, personality))) {
                mismatch = 1;
                break;
            }
        }
        if (!mismatch) break;
        rnd = heroCreateRnd();
        attempts--;
        if (attempts == 0) {
            rnd = heroGetStatus(nullptr, 2, 0);
            break;
        }
    } while (true);
    heroSetStatus(hero, 2, rnd);
    for (u8 i = 0; i < 6; i++) {
        roster[i] = heroBiosGetPokemonPtr(hero, i);
        if (roster[i] != nullptr) pokemon_SetCatchTrainerRnd(roster[i], rnd);
    }
}

extern "C" void fightTrainerCreateFightTrainerDataIdToHero(u16 trainerId, s32 controller, Hero* hero, u16 encounterId) {
    if (static_cast<u16>(encounterId) == 0) encounterId = fightGetFightEncountDataId();
    u32 kind = fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(encounterId));
    if (hero == nullptr) return;
    if (!fightTrainerCheckTrainerDataIdValid(trainerId, controller)) return;
    Hero* savedHero = reinterpret_cast<Hero*>(savedataGetStatus(0, 2));
    u32 maxLevel;
    if (savedHero != nullptr) {
        maxLevel = 0;
        for (u8 i = 0; i < 6; i++) {
            u32 level = pokemon_GetLevel(heroBiosGetPokemonPtr(savedHero, i));
            if (static_cast<u8>(maxLevel) < static_cast<u8>(level)) maxLevel = level;
        }
    }
    if (_fightTrainerGetHeroKind(trainerId) == 0) {
        if (savedHero == nullptr) return;
        if (static_cast<u8>(kind) == 13) {
            u16* name = heroBiosGetNamePtr(savedHero);
            heroCreate(hero, name, 0);
            _fightTrainerCreateDeckBingo(trainerId, hero);
            _fightTrainerCreateRndCheckRare(hero, false);
        } else if (static_cast<u8>(kind) == 15 || static_cast<u8>(kind) == 14) {
            heroCreate(hero, heroBiosGetNamePtr(savedHero), 0);
            _fightTrainerCreateDeckVirtual(trainerId, hero, encounterId);
            u16 disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(encounterId));
            for (u8 i = 0; i < 4; i++) {
                u32 item = deckDataVirtualDB_GetItemID(disk, i);
                if (static_cast<u16>(item) == 0) continue;
                u32 quantity = deckDataVirtualDB_GetItemNum(disk, i);
                if (static_cast<u8>(quantity) == 0) continue;
                if (heroItemAddItemDataId(hero, item, quantity, -1) < 0) break;
            }
        } else {
            heroBiosCopy(hero, savedHero);
        }
        return;
    }
    _fightTrainerGetHeroKind(trainerId);
    u32 sex = fightTrainerDB_GetSexDataId(trainerId);
    u16* name = GSmsgGetGSchar(static_cast<u16>(fightTrainerDB_GetName(trainerId)));
    heroCreate(hero, name, sex);
    if (static_cast<u16>(encounterId) == 0x73) {
        _fightTrainerCreateDeckUnderTakerInColosseum(trainerId, hero, encounterId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (static_cast<u8>(kind) == 16) {
        _fightTrainerCreateDeckUnderTaker(trainerId, hero, encounterId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (static_cast<u8>(kind) == 13) {
        _fightTrainerCreateDeckBingo(trainerId, hero);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (static_cast<u8>(kind) == 12) {
        _fightTrainerCreateDeckWildPoke(trainerId, hero);
    } else if (static_cast<u8>(kind) == 15 || static_cast<u8>(kind) == 14) {
        _fightTrainerCreateDeckVirtual(trainerId, hero, encounterId);
        _fightTrainerCreateRndCheckRare(hero, false);
    } else if (static_cast<u8>(kind) == 6 || static_cast<u8>(kind) == 7) {
        _fightTrainerCreateDeckNormal(trainerId, hero, encounterId);
        _fightTrainerCreateRndCheckRare(hero, false);
        if (static_cast<u8>(maxLevel) > 60) {
            for (u8 i = 0; i < 6; i++) {
                Pokemon* poke = heroBiosGetPokemonPtr(hero, i);
                if (poke != nullptr) {
                    pokemon_SetLevel(poke, maxLevel);
                    pokemon_SetExp(poke, pokemonGetLevelToExp(poke, maxLevel));
                    pokemonResetBasisStatus(poke);
                }
            }
        }
    } else {
        _fightTrainerCreateDeckNormal(trainerId, hero, encounterId);
        _fightTrainerCreateRndCheckRare(hero, false);
    }
    if (static_cast<u8>(kind) == 15 || static_cast<u8>(kind) == 14) {
        u16 disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(encounterId));
        for (u8 i = 0; i < 4; i++) {
            u32 item = deckDataVirtualDB_GetItemID(disk, i);
            if (static_cast<u16>(item) == 0) continue;
            u32 quantity = deckDataVirtualDB_GetItemNum(disk, i);
            if (static_cast<u8>(quantity) == 0) continue;
            if (heroItemAddItemDataId(hero, item, quantity, -1) < 0) break;
        }
    } else {
        for (u8 i = 0; i < 4; i++) {
            u32 item = fightTrainerDB_GetTemotiItemDataId(trainerId, i);
            if (static_cast<u16>(item) != 0 && heroItemAddItemDataId(hero, item, 1, -1) < 0) break;
        }
    }
    heroSetStatus(hero, 15, 0);
    heroSetStatus(hero, 16, 0);
    heroSetStatus(hero, 17, 0);
    heroSetStatus(hero, 18, 0);
    heroSetStatus(hero, 19, 0);
    heroSetStatus(hero, 20, 0);
    heroSetStatus(hero, 21, 0);
    heroSetStatus(hero, 22, 0);
}

class DeckTrainer { public: static DeckTrainer* getDeckTrainerObj(u32); u32 getDarkPokemonDataID(u8) const; };
extern "C" {
DarkPokemon* darkPokemonGetDarkPokemon(u32);
void fightEncountDataBiosSetFightTrainerDataId(FightEncountData*, u32, u16);
void fightEncountDataBiosSetPokemon(FightEncountData*, u32);
u32 fightTrainerPokemonDB_GetItemBallId(u16);
}
u32 deckDataVirtualDB_GetAllyDeck(u16);
u32 deckDataVirtualDB_GetEnemyDeck(u16);
u32 deckDataVirtualDB_GetPokemonNum(u16);
u8 _fightTrainerCreateDeckPokemon(Hero*, u16, u16, u16, Pokemon*, u8, u16);

void _fightTrainerCreateDeckNormal(u16 trainerId, Hero* hero, u16 encounterId) {
    u8 caught = 0;
    FIGHT_ENCOUNT* encounter = fightEncountGetStrObj();
    u8 swapMode = encounter->getSwapMode();
    u16 swapDeck = encounter->getSwapDeckNO();
    for (u8 i = 0; i < 6; i++) {
        fightTrainerDB_GetTemotiPokemonId(trainerId, i);
        DarkPokemon* dark = darkPokemonGetDarkPokemon(static_cast<u16>(DeckTrainer::getDeckTrainerObj(trainerId)->getDarkPokemonDataID(i)));
        if (dark != nullptr && dark->getStatus() >= 2) {
            caught = 1;
            break;
        }
    }
    Pokemon pokemon;
    for (u8 i = 0; ; i++) {
        u16 dataId;
        u16 darkId;
        if (swapMode == 2 && caught == 1) {
            dataId = fightTrainerDB_GetTemotiPokemonId(static_cast<u16>(swapDeck), i);
            darkId = DeckTrainer::getDeckTrainerObj(static_cast<u16>(swapDeck))->getDarkPokemonDataID(i);
        } else {
            dataId = fightTrainerDB_GetTemotiPokemonId(trainerId, i);
            darkId = DeckTrainer::getDeckTrainerObj(trainerId)->getDarkPokemonDataID(i);
        }
        u16 ball = fightTrainerPokemonDB_GetItemBallId(dataId);
        if (!_fightTrainerCreateDeckPokemon(hero, dataId, darkId, ball, &pokemon, i, encounterId)) break;
    }
}

void _fightTrainerCreateDeckVirtual(u16 trainerId, Hero* hero, u16 encounterId) {
    if (encounterId == 0) encounterId = fightGetFightEncountDataId();
    FightEncountData* encounter = fightEncountDataBiosGetPtr(encounterId);
    u16 disk = fightEncountDataBiosGetDiskId(encounter);
    u16 deck;
    if (_fightTrainerGetHeroKind(trainerId) == 0) {
        deck = deckDataVirtualDB_GetAllyDeck(disk);
        fightEncountDataBiosSetFightTrainerDataId(encounter, 0, deck);
    } else {
        deck = deckDataVirtualDB_GetEnemyDeck(disk);
        fightEncountDataBiosSetFightTrainerDataId(encounter, 1, deck);
    }
    fightEncountDataBiosSetPokemon(encounter, deckDataVirtualDB_GetPokemonNum(disk));
    Pokemon pokemon;
    for (u8 i = 0; ; i++) {
        u16 dataId = fightTrainerDB_GetTemotiPokemonId(deck, i);
        u16 darkId = DeckTrainer::getDeckTrainerObj(static_cast<u16>(deck))->getDarkPokemonDataID(i);
        u16 ball = fightTrainerPokemonDB_GetItemBallId(dataId);
        if (!_fightTrainerCreateDeckPokemon(hero, dataId, darkId, ball, &pokemon, i, encounterId)) break;
    }
}

class DeckDarkPokemon { public: static DeckDarkPokemon* getDeckDarkPokemonObj(u32); u16 getDeckPokemonID() const; u32 getWorth() const; };
extern "C" {
u8 fightTrainerCreateFightTrainerPokemonDataIdToPokemon(u16, Pokemon*, u32, u16, u16);
void deckCreate(u16, u16, Pokemon*);
void pokemon_SetFightTrainerPokemonDataId(Pokemon*, u32);
s32 heroCatchPokemon(Hero*, Pokemon*, u32, u16, u32);
}

u8 _fightTrainerCreateDeckPokemon(Hero* hero, u16 dataId, u16 darkId, u16 ball, Pokemon* pokemon, u8 slot, u16 encounterId) {
    DarkPokemon* dark = darkPokemonGetDarkPokemon(darkId);
    FIGHT_ENCOUNT* encounter = fightEncountGetStrObj();
    u8 fightMode = encounter->getFightMode();
    u8 addMode = encounter->getAddMode();
    u32 addPlace = encounter->getAddPlace();
    u32 addId = encounter->getAddID();
    u8 swapMode = encounter->getSwapMode();
    u32 swapDeck = encounter->getSwapDeckNO();
    if (dark != nullptr && dark->getStatus() >= 2) {
        if (fightMode == 1) return 1;
        if (swapMode == 1) {
            darkId = static_cast<u16>(swapDeck);
            if (darkId == 0) return 1;
            dataId = fightTrainerDB_GetTemotiPokemonId(darkId, slot);
            darkId = DeckTrainer::getDeckTrainerObj(darkId)->getDarkPokemonDataID(0);
        }
    }
    if (addMode == 1 && static_cast<u8>(addPlace) == slot) {
        u8 id = addId;
        DeckDarkPokemon* deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(id);
        DarkPokemon* addedDark = darkPokemonGetDarkPokemon(id);
        dataId = deckDark->getDeckPokemonID();
        darkId = addedDark->getDarkPokemonID();
    } else if (addMode == 2 && static_cast<u8>(addPlace) == slot) {
        u8 id = addId;
        DeckDarkPokemon* deckDark = DeckDarkPokemon::getDeckDarkPokemonObj(id);
        DarkPokemon* addedDark = darkPokemonGetDarkPokemon(id);
        dataId = deckDark->getDeckPokemonID();
        darkId = addedDark->getDarkPokemonID();
    }
    if (!fightTrainerCreateFightTrainerPokemonDataIdToPokemon(dataId, pokemon, heroGetStatus(hero, 2, 0), darkId, encounterId)) return 0;
    deckCreate(dataId, DeckPokemon::getDeckPokemonObj(dataId)->getPokemonID(), pokemon);
    pokemon_SetFightTrainerPokemonDataId(pokemon, dataId);
    return heroCatchPokemon(hero, pokemon, 0, ball, 0) >= 0;
}

void _fightTrainer_SortUnderTakerDarkPoke(u8* list, u8 count) {
    u32 escapeJ;
    u8 tmp;
    s32 worthI;
    s32 worthJ;
    u8 j;
    u8 i;
    u32 escapeI;
    u8 a;
    u8 b;
    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            worthI = DeckDarkPokemon::getDeckDarkPokemonObj(list[i])->getWorth();
            worthJ = DeckDarkPokemon::getDeckDarkPokemonObj(list[j])->getWorth();
            escapeI = darkPokemonGetDarkPokemon(list[i])->getEscapeTime();
            escapeJ = darkPokemonGetDarkPokemon(list[j])->getEscapeTime();
            a = 0;
            if (((worthI << 16) & 0xFF0000) || escapeI != 0) a = 1;
            b = 0;
            if (((worthJ << 16) & 0xFF0000) || escapeJ != 0) b = 1;
            if (a > b) {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
        }
    }
}

u8 _fightTrainer_GetListUnderTakerDarkPoke(u8* list) {
    DarkPokemon* dark;
    u8 count;
    u8 i;
    DeckDarkPokemon* deck;
    count = 0;
    for (i = 0; i < 0x80; i++) {
        deck = DeckDarkPokemon::getDeckDarkPokemonObj(i);
        dark = darkPokemonGetDarkPokemon(i);
        if (dark->getStatus() == 2 && (s32)dark->getSnatchFromWho() == 0 && (u8)deck->getWorth() != 0 && deck->getDeckPokemonID() != 0) {
            list[count++] = i;
        }
    }
    return count;
}
