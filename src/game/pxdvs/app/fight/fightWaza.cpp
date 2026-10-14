#include <game/pxdvs/app/fight/fightPokemon.hpp>
#include <game/pxdvs/app/fight/fightPokemonConditions.hpp>

struct WazaSequence;
struct FightTarget;
typedef u32 (*FightWazaVariationFunc)(u32, FightOutPokemon*, FightTarget*, u32);
typedef void (*FightWazaTypeFunc)(u32, FightOutPokemon*, FightTarget*, u32, u32);

extern "C" {
u32 wazaDB_GetWazawzxdataId(u32);
WazaSequence* Sequence_GetWaza(void*, u16, u32);
void WazaSequence_Start(WazaSequence*, u32);
u8 WazaSequence_IsActive(WazaSequence*);
void WazaSequence_Free(WazaSequence*);
void GSthreadSwitch();
FightWazaTypeFunc wazaDB_GetFightWazaWzxTypeFuncPtr(u32);
FightWazaVariationFunc wazaDB_GetFightWazaWzxVariationFuncPtr(u32);
void fightWazaWzxTypeFuncNull(u32, FightOutPokemon*, FightTarget*, u32, u32);
u32 fightWazaWzxVariationFuncNull(u32, FightOutPokemon*, FightTarget*, u32);
u32 wazaDB_GetIryoku(u32);
u32 wazaDB_GetZokuseiDataId(u32);
void fightWaza_SetWazaBanme(FightWaza*, s32);
void fightWaza_SetTargetDataId(FightWaza*, u32);
void fightWaza_SetMotoWazaDataId(FightWaza*, u32);
void fightWaza_SetUseWazaDataId(FightWaza*, u32);
void fightWaza_SetAutoMakeFlag(FightWaza*, u8);
void fightWaza_SetIryoku(FightWaza*, u16);
void fightWaza_SetZokusei(FightWaza*, u8);
void fightWaza_SetDamage(FightWaza*, u32);
void fightWaza_SetHitDamage(FightWaza*, u32);
void fightWaza_SetKaisuu(FightWaza*, u32);
void fightWaza_SetCritical(FightWaza*, u32);
void fightWaza_SetDamageValue(FightWaza*, u32);
u32 fightWaza_GetMotoWazaDataId(FightWaza*);
u32 fightWaza_GetUseWazaDataId(FightWaza*);
u32 fightWaza_GetTargetDataId(FightWaza*);
FightJoutai* fightWaza_GetJoutaiPtr(FightWaza*, u32);
u8 fightWazaIsJoutaiDataId(FightWaza*, u16);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u16);
void fightWazaInitLoop(FightWaza*);
void fightWazaInitJoutai(FightWaza*);
void fightWazaSetUseWazaStatus(FightWaza*, u32);

void fightWazaDoEffect(void* sequence, u32 move, u32 slot, u8 wait) {
    u32 effect = wazaDB_GetWazawzxdataId(move);
    WazaSequence* animation = Sequence_GetWaza(sequence, static_cast<u16>(effect), slot);
    if (animation != nullptr) {
        WazaSequence_Start(animation, 1);
        if (wait == 1) {
            while (WazaSequence_IsActive(animation)) GSthreadSwitch();
            WazaSequence_Free(animation);
        }
    }
}

void fightWazaDoEffectFunc(u32 move, FightOutPokemon* attacker, FightTarget* defender, u32 phase) {
    FightWazaTypeFunc type = wazaDB_GetFightWazaWzxTypeFuncPtr(move);
    if (type == nullptr) type = fightWazaWzxTypeFuncNull;
    FightWazaVariationFunc variation = wazaDB_GetFightWazaWzxVariationFuncPtr(move);
    if (variation == nullptr) variation = fightWazaWzxVariationFuncNull;
    u32 value = variation(move, attacker, defender, phase);
    type(move, attacker, defender, phase, value);
}

u8 fightWazaIsMix(FightWaza* move) {
    u16 conditions[7] = { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47 };
    u16 i;
    u16 count = 0;
    for (i = 0; i < 7; i++) {
        if (fightWazaIsJoutaiDataId(move, conditions[i]) == 1) count++;
    }
    if (count >= 2) return 1;
    return 0;
}

bool fightWazaIsHit(FightWaza* move) {
    if (fightWazaIsJoutaiDataId(move, 0x40) == 1) return 0;
    if (fightWazaIsJoutaiDataId(move, 0x43) == 1) return 0;
    return fightWazaIsJoutaiDataId(move, 0x45) != 1;
}

void fightWazaWriteJoutaiDataId(FightWaza* move, u16 condition, u16 user) {
    if (joutaiDataBiosGetStatus(condition) == 0x2a) joutaiWriteJoutaiDataId(move, condition, user);
}

u8 fightWazaCheckWriteJoutaiDataId(FightWaza* move, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) != 0x2a) return 0;
    return joutaiCheckWriteJoutaiDataId(move, condition);
}

u8 fightWazaIsJoutaiSousai(FightWaza* move) {
    if (fightWazaIsJoutaiDataId(move, 0x41) == 1 && fightWazaIsJoutaiDataId(move, 0x42) == 1) return 1;
    return 0;
}

u8 fightWazaIsJoutaiDataId(FightWaza* move, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) != 0x2a) return 0;
    return joutaiIsJoutaiDataId(move, condition);
}

void fightWazaInitJoutaiDataId(FightWaza* move, u16 condition) {
    if (joutaiDataBiosGetStatus(condition) == 0x2a) joutaiInitJoutaiDataId(move, condition);
}

void fightWazaCreate(FightWaza* move, s32 slot, u32 id, u32 target, u8 automatic) {
    if (move != nullptr) {
        fightWazaInit(move);
        fightWaza_SetWazaBanme(move, slot);
        fightWaza_SetTargetDataId(move, target);
        fightWaza_SetMotoWazaDataId(move, id);
        fightWazaSetUseWazaStatus(move, id);
        fightWaza_SetAutoMakeFlag(move, automatic);
    }
}

void fightWazaSetUseWazaStatus(FightWaza* move, u32 id) {
    fightWaza_SetUseWazaDataId(move, id);
    fightWaza_SetIryoku(move, static_cast<u16>(wazaDB_GetIryoku(id)));
    fightWaza_SetZokusei(move, static_cast<u8>(wazaDB_GetZokuseiDataId(id)));
}

bool fightWazaCheckValid(FightWaza* move) {
    if (move == nullptr) return 0;
    if (static_cast<u16>(fightWaza_GetMotoWazaDataId(move)) == 0) return 0;
    if (static_cast<u16>(fightWaza_GetMotoWazaDataId(move)) == 0x163) return 0;
    if (static_cast<u16>(fightWaza_GetUseWazaDataId(move)) == 0) return 0;
    if (static_cast<u16>(fightWaza_GetUseWazaDataId(move)) == 0x163) return 0;
    return static_cast<u16>(fightWaza_GetTargetDataId(move)) != 0;
}

void fightWazaInit(FightWaza* move) {
    if (move != nullptr) {
        fightWaza_SetWazaBanme(move, -1);
        fightWaza_SetMotoWazaDataId(move, 0);
        fightWaza_SetUseWazaDataId(move, 0);
        fightWaza_SetTargetDataId(move, 0);
        fightWazaInitLoop(move);
        fightWaza_SetDamage(move, 0);
        fightWaza_SetHitDamage(move, 0);
        fightWaza_SetIryoku(move, 0);
        fightWaza_SetZokusei(move, 9);
        fightWaza_SetKaisuu(move, 0);
        fightWaza_SetAutoMakeFlag(move, 0);
    }
}

void fightWazaInitLoop(FightWaza* move) {
    fightWazaInitJoutai(move);
    fightWaza_SetCritical(move, 1);
    fightWaza_SetDamageValue(move, 1);
}

void fightWazaInitJoutai(FightWaza* move) {
    joutaiInitAry(fightWaza_GetJoutaiPtr(move, 0), 9);
    fightWazaWriteJoutaiDataId(move, 0x3f, 0);
}
}
