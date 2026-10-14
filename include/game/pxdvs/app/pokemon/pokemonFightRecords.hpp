#ifndef POKEMON_FIGHT_RECORDS_H
#define POKEMON_FIGHT_RECORDS_H
#include <game/pxdvs/app/pokemon/pokemon.hpp>

// Opaque record sizes are evidenced by the original embedded-record strides.
// Member offsets are supplied by joutaiBios getters and condition-copy behavior.
struct FightJoutai {
    u16 dataId;
    u16 userFightTargetId;
    u8 kaisuu;
    u8 nowKaisuu;
    u8 count;
    u8 reserved07;
    u32 buff;
    u16 idBuff;
};
struct FightWaza { u8 storage[0xac]; };
struct FightItem { u8 storage[0xc]; };
struct FightActionBuff { u8 storage[0x30]; };
struct FightOutPokemonEnemy { u8 storage[0xc]; };
struct FightPokemonState {
    FightJoutai joutai[1]; // 0xc8
    s16 entryId; // 0xd8
    u8 catchEntryFlag; // 0xda
    u8 levelUpFlag; // 0xdb
    u8 darkOutFlag; // 0xdc
    u8 hokakuFlag; // 0xdd
    u16 reserved0de; // 0xde
    u32 reserved0e0[8]; // 0xe0, copied as eight words
    s32 aiDamage[64][2]; // 0x100
};

struct FightPokemon {
    Pokemon* motoPokemon; // 0x0
    Pokemon pokemonBuff; // 0x4
    FightPokemonState state; // 0xc8
};

struct FightOutPokemon {
    void setComboFuncId(u8);
    FightPokemon* motoFightPokemon; // 0x0
    FightPokemon* fightPokemon; // 0x4
    FightPokemon fightPokemonHensinBuff; // 0x8
    FightJoutai joutai[52]; // 0x308
    FightWaza fightWaza; // 0x648
    FightWaza keepFightWaza; // 0x6f4
    FightItem fightItem; // 0x7a0
    void* sequence; // 0x7ac
    u8 abicntPhyAtk; // 0x7b0
    u8 abicntPhyDef; // 0x7b1
    u8 abicntSpeAtk; // 0x7b2
    u8 abicntSpeDef; // 0x7b3
    u8 abicntNimbleness; // 0x7b4
    u8 abicntAverage; // 0x7b5
    u8 abicntAvoid; // 0x7b6
    u8 reserved7b7[0x5];
    u16 fightoutTurnCount; // 0x7bc
    s16 meetEnemyFightPokemonEntryId[12]; // 0x7be
    u8 reserved7d6[0x2];
    FightActionBuff fightActionBuff; // 0x7d8
    u16 zokuseiDataId[2]; // 0x808
    u16 tokuseiDataId; // 0x80c
    u8 reserved80e[0x2];
    u32 wazaMenuCur; // 0x810
    u8 comboFuncId; // 0x814
    u8 fixAiWaza; // 0x815
    u8 fixAiDef; // 0x816
    u8 reserved817[0x1];
    u16 sketchWazaDataId; // 0x818
    u16 lastSelectWazaDataId; // 0x81a
    u16 lastUseWazaDataId; // 0x81c
    u16 lastReceiveWazaTargetDataId; // 0x81e
    u16 hitWazaDataId; // 0x820
    u16 hitWazaZokuseiDataId; // 0x822
    s16 gamanDamageValue; // 0x824
    u16 gamanDamageTargetId; // 0x826
    u16 oumuWazaDataId; // 0x828
    u16 oumuWazaAllyDataId; // 0x82a
    u8 namakeFlag; // 0x82c
    u8 successCnt; // 0x82d
    u16 usedItemDataId; // 0x82e
    u16 stockItemDataId; // 0x830
    u8 reserved832[0x2];
    s16 damageAtkValue; // 0x834
    u16 damageAtkTargetId; // 0x836
    s16 damageSpeValue; // 0x838
    u16 damageSpeTargetId; // 0x83a
    u8 mahiNoAttackFlag; // 0x83c
    u8 konranMyselfAttackFlag; // 0x83d
    u8 outWazaKoukanaiFlag; // 0x83e
    u8 tameWazaFlag; // 0x83f
    u8 itemNigeruFlag; // 0x840
    u8 huuinNoAttackFlag; // 0x841
    u8 meroMeroNoAttackFlag; // 0x842
    u8 kanashibariNoAttackFlag; // 0x843
    u8 chouhatsuNoAttackFlag; // 0x844
    u8 ichamonNoAttackFlag; // 0x845
    u8 hirumuNoAttackFlag; // 0x846
    u8 passPpdecFlag; // 0x847
    u8 fightActionFlag; // 0x848
    u8 doClearbodyFlag; // 0x849
    u8 receivesWazaHiraishinFlag; // 0x84a
    u8 vanishoffFlag; // 0x84b
    u8 doIkakuFlag; // 0x84c
    u8 doTraceFlag; // 0x84d
    u8 noPressureFlag; // 0x84e
    u8 irekaetaFlag; // 0x84f
    u8 itemKoraetaFlag; // 0x850
    u8 reserved851[0x3];
    s32 kaigaraDamageValue; // 0x854
    s16 myselfDamageAtkValue; // 0x858
    u16 myselfDamageAtkTargetId; // 0x85a
    s16 myselfDamageSpeValue; // 0x85c
    u16 myselfDamageSpeTargetId; // 0x85e
    u8 kizetuFlag; // 0x860
    u8 unknown861; // 0x861
    s16 irekaeTargetEntryId; // 0x862
    FightOutPokemonEnemy enemy[4]; // 0x864
};

extern "C" {
void fightOutPokemon_SetFixAiDef(FightOutPokemon*, u8);
void fightOutPokemon_SetFixAiWaza(FightOutPokemon*, u8);
void fightOutPokemon_SetComboFuncId(FightOutPokemon*, u8);
void fightOutPokemon_SetOumuWazaAllyDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetIrekaeTargetEntryId(FightOutPokemon*, s16);
void fn_8014718C(FightOutPokemon*, u8);
void fightOutPokemon_SetKizetuFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetMyselfDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetMyselfDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemon_SetMyselfDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetMyselfDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemon_SetKaigaraDamageValue(FightOutPokemon*, s32);
void fightOutPokemon_SetItemKoraetaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetIrekaetaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetNoPressureFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetDoTraceFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetDoIkakuFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetVanishoffFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetReceivesWazaHiraishinFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetDoClearbodyFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetPassPpdecFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetHirumuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetIchamonNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetChouhatsuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetKanashibariNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetMeroMeroNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetHuuinNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetItemNigeruFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetTameWazaFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetOutWazaKoukanaiFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetKonranMyselfAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetMahiNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemon_SetDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemon_SetDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetDamageAtkValue(FightOutPokemon*, s16);
#ifdef FIGHT_POKEMON_COMMAND_ABI
void fightOutPokemon_SetTokuseiDataId(FightOutPokemon*, u32);
#else
void fightOutPokemon_SetTokuseiDataId(FightOutPokemon*, u16);
#endif
void fightOutPokemon_SetSuccessCnt(FightOutPokemon*, u8);
void fightOutPokemon_SetStockItemDataId(FightOutPokemon*, u16);
#ifdef FIGHT_POKEMON_COMMAND_ABI
void fightOutPokemon_SetUsedItemDataId(FightOutPokemon*, u32);
#else
void fightOutPokemon_SetUsedItemDataId(FightOutPokemon*, u16);
#endif
void fightOutPokemon_SetNamakeFlag(FightOutPokemon*, u8);
#ifdef FIGHT_POKEMON_COMMAND_ABI
void fightOutPokemon_SetOumuWazaDataId(FightOutPokemon*, u32);
#else
void fightOutPokemon_SetOumuWazaDataId(FightOutPokemon*, u16);
#endif
void fightOutPokemon_SetGamanDamageTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetGamanDamageValue(FightOutPokemon*, s16);
void fightOutPokemon_SetHitWazaZokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetHitWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetLastReceiveWazaTargetDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetLastUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetLastSelectWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetSketchWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetSequencePtr(FightOutPokemon*, void*);
void fightOutPokemon_SetFightoutTurnCount(FightOutPokemon*, u16);
void fightOutPokemon_SetAbicntAverage(FightOutPokemon*, u8);
void fightOutPokemon_SetFightPokemonPtr(FightOutPokemon*, FightPokemon*);
void fightOutPokemon_SetMotoFightPokemonPtr(FightOutPokemon*, FightPokemon*);
void fightPokemon_SetHokakuFlag(FightPokemon*, u8);
void fightPokemon_SetDarkOutFlag(FightPokemon*, u8);
void fightPokemon_SetLevelUpFlag(FightPokemon*, u8);
void fightPokemon_SetCatchEntryFlag(FightPokemon*, u8);
void fightPokemon_SetEntryId(FightPokemon*, s16);
void fightPokemon_SetMotoPokemonPtr(FightPokemon*, Pokemon*);
u8 fightOutPokemon_GetFixAiDef(FightOutPokemon*);
u8 fightOutPokemon_GetFixAiWaza(FightOutPokemon*);
u8 fightOutPokemon_GetComboFuncId(FightOutPokemon*);
u16 fightOutPokemon_GetOumuWazaAllyDataId(FightOutPokemon*);
int fightOutPokemon_GetIrekaeTargetEntryId(FightOutPokemon*);
u8 fn_80148688(FightOutPokemon*);
u8 fightOutPokemon_GetKizetuFlag(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageSpeValue(FightOutPokemon*);
int fightOutPokemon_GetMyselfDamageAtkValue(FightOutPokemon*);
s32 fightOutPokemon_GetKaigaraDamageValue(FightOutPokemon*);
u8 fightOutPokemon_GetItemKoraetaFlag(FightOutPokemon*);
u8 fightOutPokemon_GetIrekaetaFlag(FightOutPokemon*);
u8 fightOutPokemon_GetNoPressureFlag(FightOutPokemon*);
u8 fightOutPokemon_GetDoTraceFlag(FightOutPokemon*);
u8 fightOutPokemon_GetDoIkakuFlag(FightOutPokemon*);
u8 fightOutPokemon_GetVanishoffFlag(FightOutPokemon*);
u8 fightOutPokemon_GetReceivesWazaHiraishinFlag(FightOutPokemon*);
u8 fightOutPokemon_GetDoClearbodyFlag(FightOutPokemon*);
u8 fightOutPokemon_GetFightActionFlag(FightOutPokemon*);
u8 fightOutPokemon_GetPassPpdecFlag(FightOutPokemon*);
u8 fightOutPokemon_GetTameWazaFlag(FightOutPokemon*);
u8 fightOutPokemon_GetKonranMyselfAttackFlag(FightOutPokemon*);
u16 fightOutPokemon_GetDamageSpeTargetId(FightOutPokemon*);
int fightOutPokemon_GetDamageSpeValue(FightOutPokemon*);
u16 fightOutPokemon_GetDamageAtkTargetId(FightOutPokemon*);
int fightOutPokemon_GetDamageAtkValue(FightOutPokemon*);
#ifdef FIGHT_POKEMON_COMMAND_ABI
u32 fightOutPokemon_GetTokuseiDataId(FightOutPokemon*);
#else
u16 fightOutPokemon_GetTokuseiDataId(FightOutPokemon*);
#endif
u8 fightOutPokemon_GetSuccessCnt(FightOutPokemon*);
u16 fightOutPokemon_GetStockItemDataId(FightOutPokemon*);
u16 fightOutPokemon_GetUsedItemDataId(FightOutPokemon*);
u8 fightOutPokemon_GetNamakeFlag(FightOutPokemon*);
u16 fightOutPokemon_GetOumuWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetGamanDamageTargetId(FightOutPokemon*);
int fightOutPokemon_GetGamanDamageValue(FightOutPokemon*);
u16 fightOutPokemon_GetHitWazaZokuseiDataId(FightOutPokemon*);
u16 fightOutPokemon_GetHitWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetLastReceiveWazaTargetDataId(FightOutPokemon*);
u16 fightOutPokemon_GetLastUseWazaDataId(FightOutPokemon*);
#ifdef FIGHT_POKEMON_COMMAND_ABI
u32 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon*);
#else
u16 fightOutPokemon_GetLastSelectWazaDataId(FightOutPokemon*);
#endif
u16 fightOutPokemon_GetSketchWazaDataId(FightOutPokemon*);
void* fightOutPokemon_GetSequencePtr(FightOutPokemon*);
u16 fightOutPokemon_GetFightoutTurnCount(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntAvoid(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntAverage(FightOutPokemon*);
#ifdef FIGHT_POKEMON_COMMAND_ABI
u32 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon*);
#else
u8 fightOutPokemon_GetAbicntNimbleness(FightOutPokemon*);
#endif
u8 fightOutPokemon_GetAbicntSpeDef(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntSpeAtk(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntPhyDef(FightOutPokemon*);
u8 fightOutPokemon_GetAbicntPhyAtk(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetFightPokemonPtr(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
u8 fightPokemon_GetHokakuFlag(FightPokemon*);
u8 fightPokemon_GetDarkOutFlag(FightPokemon*);
u8 fightPokemon_GetLevelUpFlag(FightPokemon*);
u8 fightPokemon_GetCatchEntryFlag(FightPokemon*);
int fightPokemon_GetEntryId(FightPokemon*);
Pokemon* fightPokemon_GetMotoPokemonPtr(FightPokemon*);
u32* fightOutPokemon_GetWazaMenuCurPtr(FightOutPokemon*);
FightActionBuff* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
FightWaza* fightOutPokemon_GetKeepFightWazaPtr(FightOutPokemon*);
FightItem* fightOutPokemon_GetFightItemPtr(FightOutPokemon*);
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
FightPokemon* fightOutPokemon_GetFightPokemonHensinBuffPtr(FightOutPokemon*);
Pokemon* fightPokemon_GetPokemonBuffPtr(FightPokemon*);
void fightOutPokemon_SetZokuseiDataId(FightOutPokemon*,u8,u16);
u16 fightOutPokemon_GetZokuseiDataId(FightOutPokemon*,u8);
#ifdef FIGHT_POKEMON_COMMAND_ABI
void fightOutPokemon_SetMeetEnemyFightPokemonEntryId(FightOutPokemon*,u8,s32);
#else
void fightOutPokemon_SetMeetEnemyFightPokemonEntryId(FightOutPokemon*,u8,s16);
#endif
int fightOutPokemon_GetMeetEnemyFightPokemonEntryId(FightOutPokemon*,u8);
FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon*,u16);
FightJoutai* fightOutPokemon_GetFightoutJoutaiPtr(FightOutPokemon*,u16);
FightJoutai* fightPokemon_GetFightJoutaiPtr(FightPokemon*,u16);
void fightPokemon_SetAiDamage(FightPokemon*,u16,u16,s32);
}
extern "C" {
void fightOutPokemon_SetWazaHitDamage(FightOutPokemon*,s32);
void fightOutPokemon_SetWazaTargetId(FightOutPokemon*,u16);
void fightOutPokemon_SetWazaIryoku(FightOutPokemon*,u16);
void fightOutPokemon_SetWazaDamage(FightOutPokemon*,s32);
void fightOutPokemon_SetWazaCritical(FightOutPokemon*,u8);
void fightOutPokemon_SetWazaDamageValue(FightOutPokemon*,u8);
void fightOutPokemon_SetMotoWazaDataId(FightOutPokemon*,u16);
void fightOutPokemon_SetUseWazaDataId(FightOutPokemon*,u16);
s32 fightOutPokemon_GetHitDamage(FightOutPokemon*);
u16 fightOutPokemon_GetTargetId(FightOutPokemon*);
u16 fightOutPokemon_GetIryoku(FightOutPokemon*);
s32 fightOutPokemon_GetDamage(FightOutPokemon*);
u8 fightOutPokemon_GetIsHit(FightOutPokemon*);
u8 fightOutPokemon_GetCritical(FightOutPokemon*);
u8 fightOutPokemon_GetDamageValue(FightOutPokemon*);
u16 fightOutPokemon_GetMotoWazaDataId(FightOutPokemon*);
u16 fightOutPokemon_GetUseWazaDataId(FightOutPokemon*);
void fightOutPokemon_SetWazaInitJoutaiDataId(FightOutPokemon*,u16);
void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon*,u16);
u8 fightOutPokemon_GetJoutaiDataId(FightOutPokemon*,u16);
}
#endif
