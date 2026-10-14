#ifndef POKEMON_STATUS_DISPATCH_H
#define POKEMON_STATUS_DISPATCH_H
struct PokemonData;
#include <game/pxdvs/app/pokemon/pokemonFightRecords.hpp>
#include <game/pxdvs/app/pokemon/pokemonBiosRecords.hpp>

// Property IDs select species records below 0x6d, then instance and battle records.
// The command layer transports pointer and scalar results as a full register word.
enum PokemonStatusProperty {
    STATUS_SPECIES_NAME = 0x1,
    STATUS_SPECIES_BASIS_MAX_HP = 0x3,
    STATUS_SPECIES_BASIS_PHY_ATK = 0x4,
    STATUS_SPECIES_BASIS_PHY_DEF = 0x5,
    STATUS_SPECIES_BASIS_SPE_ATK = 0x6,
    STATUS_SPECIES_BASIS_SPE_DEF = 0x7,
    STATUS_SPECIES_BASIS_NIMBLENESS = 0x8,
    STATUS_SPECIES_GIVE_MAX_HP_EFFORT = 0xa,
    STATUS_SPECIES_GIVE_PHY_ATK_EFFORT = 0xb,
    STATUS_SPECIES_GIVE_PHY_DEF_EFFORT = 0xc,
    STATUS_SPECIES_GIVE_SPE_ATK_EFFORT = 0xd,
    STATUS_SPECIES_GIVE_SPE_DEF_EFFORT = 0xe,
    STATUS_SPECIES_GIVE_NIMBLENESS_EFFORT = 0xf,
    STATUS_SPECIES_GIVE_EXP = 0x10,
    STATUS_SPECIES_GROW_DATA_ID = 0x11,
    STATUS_SPECIES_ = 0x12,
    STATUS_SPECIES_SEX_RATIO = 0x13,
    STATUS_SPECIES_INIT_FRIEND = 0x14,
    STATUS_SPECIES_ITEM_DATA_ID = 0x15,
    STATUS_SPECIES_ZOKUSEI_DATA_ID = 0x16,
    STATUS_SPECIES_TOKUSEI_DATA_ID = 0x17,
    STATUS_SPECIES_SINKA_KIND = 0x19,
    STATUS_SPECIES_SINKA_BUFF = 0x1a,
    STATUS_SPECIES_SINKA_POKEMON_DATA_ID = 0x1b,
    STATUS_SPECIES_WAZA_LEVEL = 0x1d,
    STATUS_SPECIES_WAZA_DATA_ID = 0x1e,
    STATUS_SPECIES_POKEBODY_ID = 0x5a,
    STATUS_SPECIES_STATUS_FACE_MENU_SPRITE_ID = 0x5b,
    STATUS_SPECIES_COLOR = 0x5c,
    STATUS_SPECIES_TYPE_NAME = 0x5d,
    STATUS_SPECIES_HEIGHT = 0x5e,
    STATUS_SPECIES_WEIGHT = 0x5f,
    STATUS_SPECIES_DOC = 0x60,
    STATUS_SPECIES_VOICE = 0x61,
    STATUS_SPECIES_MITA_FLAG = 0x62,
    STATUS_SPECIES_TUKAMAETA_FLAG = 0x63,
    STATUS_SPECIES_NUM_ZUKAN = 0x64,
    STATUS_SPECIES_NUM_POKEMON = 0x65,
    STATUS_SPECIES_PKX_DATA_ID = 0x66,
    STATUS_SPECIES_KOWAZA = 0x68,
    STATUS_SPECIES_POKEMON_DATA_ID = 0x69,
    STATUS_SPECIES_POKEMON_DATA_ID_6A = 0x6a,
    STATUS_SPECIES_POKEMON_DATA_ID_6B = 0x6b,
    STATUS_SPECIES_POKEMON_DATA_ID_6C = 0x6c,
    STATUS_POKEMON_POKEMON_DATA_ID = 0x6e,
    STATUS_POKEMON_RND = 0x6f,
    STATUS_POKEMON_ATTEST = 0x70,
    STATUS_POKEMON_CATCH_FLOOR_ID = 0x71,
    STATUS_POKEMON_CATCH_LEVEL = 0x72,
    STATUS_POKEMON_CATCH_BALL_ID = 0x73,
    STATUS_POKEMON_CATCH_TRAINER_SEX = 0x74,
    STATUS_POKEMON_CATCH_TRAINER_RND = 0x75,
    STATUS_POKEMON_CATCH_TRAINER_NAME_PTR = 0x76,
    STATUS_POKEMON_NICKNAME_PTR = 0x77,
    STATUS_POKEMON_NICKNAME_ORG_PTR = 0x78,
    STATUS_POKEMON_EXP = 0x79,
    STATUS_POKEMON_LEVEL = 0x7a,
    STATUS_POKEMON_POKEMON_GET_HINSI = 0x7b,
    STATUS_POKEMON_CONDITION_AMARI = 0x7d,
    STATUS_POKEMON_POKEMON_WAZA_DATA_ID = 0x7f,
    STATUS_POKEMON_POKEMON_WAZA_PP = 0x80,
    STATUS_POKEMON_POKEMON_WAZA_PP_COUNT = 0x81,
    STATUS_POKEMON_ITEM_DATA_ID = 0x82,
    STATUS_POKEMON_HP = 0x83,
    STATUS_POKEMON_MAX_HP = 0x87,
    STATUS_POKEMON_PHY_ATK = 0x88,
    STATUS_POKEMON_PHY_DEF = 0x89,
    STATUS_POKEMON_SPE_ATK = 0x8a,
    STATUS_POKEMON_SPE_DEF = 0x8b,
    STATUS_POKEMON_NIMBLENESS = 0x8c,
    STATUS_POKEMON_MAX_HP_EFFORT = 0x8d,
    STATUS_POKEMON_PHY_ATK_EFFORT = 0x8e,
    STATUS_POKEMON_PHY_DEF_EFFORT = 0x8f,
    STATUS_POKEMON_SPE_ATK_EFFORT = 0x90,
    STATUS_POKEMON_SPE_DEF_EFFORT = 0x91,
    STATUS_POKEMON_NIMBLENESS_EFFORT = 0x92,
    STATUS_POKEMON_MAX_HP_RND = 0x93,
    STATUS_POKEMON_PHY_ATK_RND = 0x94,
    STATUS_POKEMON_PHY_DEF_RND = 0x95,
    STATUS_POKEMON_SPE_ATK_RND = 0x96,
    STATUS_POKEMON_SPE_DEF_RND = 0x97,
    STATUS_POKEMON_NIMBLENESS_RND = 0x98,
    STATUS_POKEMON_FRIEND = 0x99,
    STATUS_POKEMON_STYLE = 0x9c,
    STATUS_POKEMON_BEAUTIFUL = 0x9d,
    STATUS_POKEMON_CUTE = 0x9e,
    STATUS_POKEMON_CLEVER = 0x9f,
    STATUS_POKEMON_STRONG = 0xa0,
    STATUS_POKEMON_FUR = 0xa1,
    STATUS_POKEMON_CHAMP_RIBBON = 0xa3,
    STATUS_POKEMON_WINNING_RIBBON = 0xa4,
    STATUS_POKEMON_VICTORY_RIBBON = 0xa5,
    STATUS_POKEMON_BROMIDE_RIBBON = 0xa6,
    STATUS_POKEMON_GANBA_RIBBON = 0xa7,
    STATUS_POKEMON_MARINE_RIBBON = 0xa8,
    STATUS_POKEMON_LAND_RIBBON = 0xa9,
    STATUS_POKEMON_SKY_RIBBON = 0xaa,
    STATUS_POKEMON_COUNTRY_RIBBON = 0xab,
    STATUS_POKEMON_NATIONAL_RIBBON = 0xac,
    STATUS_POKEMON_EARTH_RIBBON = 0xad,
    STATUS_POKEMON_WORLD_RIBBON = 0xae,
    STATUS_POKEMON_AMARI_RIBBON = 0xaf,
    STATUS_POKEMON_STYLE_MEDAL = 0xb0,
    STATUS_POKEMON_BEAUTIFUL_MEDAL = 0xb1,
    STATUS_POKEMON_CUTE_MEDAL = 0xb2,
    STATUS_POKEMON_CLEVER_MEDAL = 0xb3,
    STATUS_POKEMON_STRONG_MEDAL = 0xb4,
    STATUS_POKEMON_POKERUS = 0xb5,
    STATUS_POKEMON_TAMAGO_FLAG = 0xb6,
    STATUS_POKEMON_TOKUSEI_FLAG = 0xb7,
    STATUS_POKEMON_FUSEI_FLAG = 0xb8,
    STATUS_POKEMON_FLAG_AMARI = 0xb9,
    STATUS_POKEMON_POKEMON_GET_SEX = 0xba,
    STATUS_POKEMON_PCBOX_MARK = 0xbb,
    STATUS_POKEMON_MAIL_ID = 0xbc,
    STATUS_POKEMON_PARA1_AMARI = 0xbd,
    STATUS_POKEMON_AMARI = 0xbe,
    STATUS_POKEMON_POKEMON_GET_SEIKAKU = 0xbf,
    STATUS_POKEMON_POKEMON_GET_NOW_EXP_TO_LEVEL = 0xc0,
    STATUS_POKEMON_POKEMON_CHECK_RARE = 0xc1,
    STATUS_POKEMON_DARK_FLAG = 0xc2,
    STATUS_POKEMON_DARKPOKEMON_DATA_ID = 0xc3,
    STATUS_POKEMON_INIT_DP = 0xc4,
    STATUS_POKEMON_DP = 0xc5,
    STATUS_POKEMON_POOL_EXP = 0xc6,
    STATUS_POKEMON_POOL_FRIEND = 0xc7,
    STATUS_POKEMON_FIGHT_TRAINER_POKEMON_DATA_ID = 0xc9,
    STATUS_FIGHT_MOTO_POKEMON_PTR = 0xcb,
    STATUS_FIGHT_POKEMON_BUFF_PTR = 0xcc,
    STATUS_FIGHT_CONDITION_COPY = 0xcd,
    STATUS_FIGHT_ENTRY_ID = 0xce,
    STATUS_FIGHT_CATCH_ENTRY_FLAG = 0xcf,
    STATUS_FIGHT_LEVEL_UP_FLAG = 0xd0,
    STATUS_FIGHT_DARK_OUT_FLAG = 0xd1,
    STATUS_FIGHT_HOKAKU_FLAG = 0xd2,
    STATUS_FIGHT_OUT_MOTO_FIGHT_POKEMON_PTR = 0xd5,
    STATUS_FIGHT_OUT_FIGHT_POKEMON_PTR = 0xd6,
    STATUS_FIGHT_OUT_FIGHT_POKEMON_HENSIN_BUFF_PTR = 0xd7,
    STATUS_FIGHT_OUT_FIGHTOUT_JOUTAI_PTR = 0xd8,
    STATUS_FIGHT_OUT_FIGHT_WAZA_PTR = 0xd9,
    STATUS_FIGHT_OUT_USE_WAZA_DATA_ID = 0xda,
    STATUS_FIGHT_OUT_MOTO_WAZA_DATA_ID = 0xdb,
    STATUS_FIGHT_OUT_DAMAGE_VALUE = 0xdc,
    STATUS_FIGHT_OUT_CRITICAL = 0xdd,
    STATUS_FIGHT_OUT_WRITE_MOVE_CONDITION = 0xde,
    STATUS_FIGHT_OUT_INIT_MOVE_CONDITION = 0xdf,
    STATUS_FIGHT_OUT_IS_HIT = 0xe0,
    STATUS_FIGHT_OUT_DAMAGE = 0xe1,
    STATUS_FIGHT_OUT_IRYOKU = 0xe2,
    STATUS_FIGHT_OUT_TARGET_DATA_ID = 0xe3,
    STATUS_FIGHT_OUT_HIT_DAMAGE = 0xe4,
    STATUS_FIGHT_OUT_FIGHT_ITEM_PTR = 0xe5,
    STATUS_FIGHT_OUT_ABICNT_PHY_ATK = 0xe6,
    STATUS_FIGHT_OUT_ABICNT_PHY_DEF = 0xe7,
    STATUS_FIGHT_OUT_ABICNT_SPE_ATK = 0xe8,
    STATUS_FIGHT_OUT_ABICNT_SPE_DEF = 0xe9,
    STATUS_FIGHT_OUT_ABICNT_NIMBLENESS = 0xea,
    STATUS_FIGHT_OUT_ABICNT_AVERAGE = 0xeb,
    STATUS_FIGHT_OUT_ABICNT_AVOID = 0xec,
    STATUS_FIGHT_OUT_FIGHTOUT_TURN_COUNT = 0xed,
    STATUS_FIGHT_OUT_SEQUENCE_PTR = 0xee,
    STATUS_FIGHT_OUT_SKETCH_WAZA_DATA_ID = 0xef,
    STATUS_FIGHT_OUT_LAST_SELECT_WAZA_DATA_ID = 0xf0,
    STATUS_FIGHT_OUT_LAST_USE_WAZA_DATA_ID = 0xf1,
    STATUS_FIGHT_OUT_LAST_RECEIVE_WAZA_TARGET_DATA_ID = 0xf2,
    STATUS_FIGHT_OUT_HIT_WAZA_DATA_ID = 0xf3,
    STATUS_FIGHT_OUT_HIT_WAZA_ZOKUSEI_DATA_ID = 0xf4,
    STATUS_FIGHT_OUT_GAMAN_DAMAGE_VALUE = 0xf5,
    STATUS_FIGHT_OUT_GAMAN_DAMAGE_TARGET_ID = 0xf6,
    STATUS_FIGHT_OUT_OUMU_WAZA_DATA_ID = 0xf7,
    STATUS_FIGHT_OUT_KEEP_FIGHT_WAZA_PTR = 0xf8,
    STATUS_FIGHT_OUT_NAMAKE_FLAG = 0xf9,
    STATUS_FIGHT_OUT_USED_ITEM_DATA_ID = 0xfa,
    STATUS_FIGHT_OUT_STOCK_ITEM_DATA_ID = 0xfb,
    STATUS_FIGHT_OUT_SUCCESS_CNT = 0xfc,
    STATUS_FIGHT_OUT_MEET_ENEMY_FIGHT_POKEMON_ENTRY_ID = 0xfd,
    STATUS_FIGHT_OUT_FIGHT_ACTION_BUFF_PTR = 0xfe,
    STATUS_FIGHT_OUT_ZOKUSEI_DATA_ID = 0xff,
    STATUS_FIGHT_OUT_TOKUSEI_DATA_ID = 0x100,
    STATUS_FIGHT_OUT_WAZA_MENU_CUR_PTR = 0x101,
    STATUS_FIGHT_OUT_DAMAGE_ATK_VALUE = 0x102,
    STATUS_FIGHT_OUT_DAMAGE_ATK_TARGET_ID = 0x103,
    STATUS_FIGHT_OUT_DAMAGE_SPE_VALUE = 0x104,
    STATUS_FIGHT_OUT_DAMAGE_SPE_TARGET_ID = 0x105,
    STATUS_FIGHT_OUT_MAHI_NO_ATTACK_FLAG = 0x106,
    STATUS_FIGHT_OUT_KONRAN_MYSELF_ATTACK_FLAG = 0x107,
    STATUS_FIGHT_OUT_OUT_WAZA_KOUKANAI_FLAG = 0x108,
    STATUS_FIGHT_OUT_TAME_WAZA_FLAG = 0x109,
    STATUS_FIGHT_OUT_ITEM_NIGERU_FLAG = 0x10a,
    STATUS_FIGHT_OUT_HUUIN_NO_ATTACK_FLAG = 0x10b,
    STATUS_FIGHT_OUT_MERO_MERO_NO_ATTACK_FLAG = 0x10c,
    STATUS_FIGHT_OUT_KANASHIBARI_NO_ATTACK_FLAG = 0x10d,
    STATUS_FIGHT_OUT_CHOUHATSU_NO_ATTACK_FLAG = 0x10e,
    STATUS_FIGHT_OUT_ICHAMON_NO_ATTACK_FLAG = 0x10f,
    STATUS_FIGHT_OUT_HIRUMU_NO_ATTACK_FLAG = 0x110,
    STATUS_FIGHT_OUT_PASS_PPDEC_FLAG = 0x111,
    STATUS_FIGHT_OUT_FIGHT_ACTION_FLAG = 0x112,
    STATUS_FIGHT_OUT_DO_CLEARBODY_FLAG = 0x113,
    STATUS_FIGHT_OUT_RECEIVES_WAZA_HIRAISHIN_FLAG = 0x114,
    STATUS_FIGHT_OUT_VANISHOFF_FLAG = 0x115,
    STATUS_FIGHT_OUT_DO_IKAKU_FLAG = 0x116,
    STATUS_FIGHT_OUT_DO_TRACE_FLAG = 0x117,
    STATUS_FIGHT_OUT_NO_PRESSURE_FLAG = 0x118,
    STATUS_FIGHT_OUT_IREKAETA_FLAG = 0x119,
    STATUS_FIGHT_OUT_ITEM_KORAETA_FLAG = 0x11a,
    STATUS_FIGHT_OUT_KAIGARA_DAMAGE_VALUE = 0x11b,
    STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_VALUE = 0x11c,
    STATUS_FIGHT_OUT_MYSELF_DAMAGE_ATK_TARGET_ID = 0x11d,
    STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_VALUE = 0x11e,
    STATUS_FIGHT_OUT_MYSELF_DAMAGE_SPE_TARGET_ID = 0x11f,
    STATUS_FIGHT_OUT_KIZETU_FLAG = 0x120,
    STATUS_FIGHT_OUT_IREKAE_TARGET_ENTRY_ID = 0x121,
    STATUS_FIGHT_OUT_FIGHT_OUT_POKEMON_ENEMY_PTR = 0x122,
    STATUS_FIGHT_OUT_CHECK_FIGHT_OUT = 0x123,
};

extern "C" {
u8 fightOutPokemonBiosGetAbicntAverage(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntAvoid(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntNimbleness(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntPhyAtk(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntPhyDef(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntSpeAtk(FightOutPokemon*);
u8 fightOutPokemonBiosGetAbicntSpeDef(FightOutPokemon*);
u8 fightOutPokemonBiosGetChouhatsuNoAttackFlag(FightOutPokemon*);
u16 fightOutPokemonBiosGetDamageAtkTargetId(FightOutPokemon*);
s16 fightOutPokemonBiosGetDamageAtkValue(FightOutPokemon*);
u16 fightOutPokemonBiosGetDamageSpeTargetId(FightOutPokemon*);
s16 fightOutPokemonBiosGetDamageSpeValue(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoClearbodyFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoIkakuFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetDoTraceFlag(FightOutPokemon*);
FightActionBuff* fightOutPokemonBiosGetFightActionBuffPtr(FightOutPokemon*);
u8 fightOutPokemonBiosGetFightActionFlag(FightOutPokemon*);
FightItem* fightOutPokemonBiosGetFightItemPtr(FightOutPokemon*);
FightOutPokemonEnemy* fightOutPokemonBiosGetFightOutPokemonEnemyPtr(FightOutPokemon*, u16);
FightPokemon* fightOutPokemonBiosGetFightPokemonHensinBuffPtr(FightOutPokemon*);
FightPokemon* fightOutPokemonBiosGetFightPokemonPtr(FightOutPokemon*);
FightWaza* fightOutPokemonBiosGetFightWazaPtr(FightOutPokemon*);
FightJoutai* fightOutPokemonBiosGetFightoutJoutaiPtr(FightOutPokemon*, u16);
u16 fightOutPokemonBiosGetFightoutTurnCount(FightOutPokemon*);
u16 fightOutPokemonBiosGetGamanDamageTargetId(FightOutPokemon*);
s16 fightOutPokemonBiosGetGamanDamageValue(FightOutPokemon*);
u8 fightOutPokemonBiosGetHirumuNoAttackFlag(FightOutPokemon*);
u16 fightOutPokemonBiosGetHitWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetHitWazaZokuseiDataId(FightOutPokemon*);
u8 fightOutPokemonBiosGetHuuinNoAttackFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetIchamonNoAttackFlag(FightOutPokemon*);
s16 fightOutPokemonBiosGetIrekaeTargetEntryId(FightOutPokemon*);
u8 fightOutPokemonBiosGetIrekaetaFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetItemKoraetaFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetItemNigeruFlag(FightOutPokemon*);
u32 fightOutPokemonBiosGetKaigaraDamageValue(FightOutPokemon*);
u8 fightOutPokemonBiosGetKanashibariNoAttackFlag(FightOutPokemon*);
FightWaza* fightOutPokemonBiosGetKeepFightWazaPtr(FightOutPokemon*);
u8 fightOutPokemonBiosGetKizetuFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetKonranMyselfAttackFlag(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastReceiveWazaTargetDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastSelectWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetLastUseWazaDataId(FightOutPokemon*);
u8 fightOutPokemonBiosGetMahiNoAttackFlag(FightOutPokemon*);
s16 fightOutPokemonBiosGetMeetEnemyFightPokemonEntryId(FightOutPokemon*, u8);
u8 fightOutPokemonBiosGetMeroMeroNoAttackFlag(FightOutPokemon*);
FightPokemon* fightOutPokemonBiosGetMotoFightPokemonPtr(FightOutPokemon*);
u16 fightOutPokemonBiosGetMyselfDamageAtkTargetId(FightOutPokemon*);
s16 fightOutPokemonBiosGetMyselfDamageAtkValue(FightOutPokemon*);
u16 fightOutPokemonBiosGetMyselfDamageSpeTargetId(FightOutPokemon*);
s16 fightOutPokemonBiosGetMyselfDamageSpeValue(FightOutPokemon*);
u8 fightOutPokemonBiosGetNamakeFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetNoPressureFlag(FightOutPokemon*);
u16 fightOutPokemonBiosGetOumuWazaDataId(FightOutPokemon*);
u8 fightOutPokemonBiosGetOutWazaKoukanaiFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetPassPpdecFlag(FightOutPokemon*);
u8 fightOutPokemonBiosGetReceivesWazaHiraishinFlag(FightOutPokemon*);
void* fightOutPokemonBiosGetSequencePtr(FightOutPokemon*);
u16 fightOutPokemonBiosGetSketchWazaDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetStockItemDataId(FightOutPokemon*);
u8 fightOutPokemonBiosGetSuccessCnt(FightOutPokemon*);
u8 fightOutPokemonBiosGetTameWazaFlag(FightOutPokemon*);
u16 fightOutPokemonBiosGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonBiosGetUsedItemDataId(FightOutPokemon*);
u8 fightOutPokemonBiosGetVanishoffFlag(FightOutPokemon*);
u32* fightOutPokemonBiosGetWazaMenuCurPtr(FightOutPokemon*);
u16 fightOutPokemonBiosGetZokuseiDataId(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntAverage(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntAvoid(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntNimbleness(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntPhyAtk(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntPhyDef(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntSpeAtk(FightOutPokemon*, u8);
void fightOutPokemonBiosSetAbicntSpeDef(FightOutPokemon*, u8);
void fightOutPokemonBiosSetChouhatsuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetDoClearbodyFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetDoIkakuFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetDoTraceFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetFightActionFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetFightPokemonPtr(FightOutPokemon*, u32);
void fightOutPokemonBiosSetFightoutTurnCount(FightOutPokemon*, u16);
void fightOutPokemonBiosSetGamanDamageTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetGamanDamageValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetHirumuNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetHitWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetHitWazaZokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetHuuinNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetIchamonNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetIrekaeTargetEntryId(FightOutPokemon*, s16);
void fightOutPokemonBiosSetIrekaetaFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetItemKoraetaFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetItemNigeruFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetKaigaraDamageValue(FightOutPokemon*, u32);
void fightOutPokemonBiosSetKanashibariNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetKizetuFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetKonranMyselfAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetLastReceiveWazaTargetDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetLastSelectWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetLastUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMahiNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetMeetEnemyFightPokemonEntryId(FightOutPokemon*, u8, s16);
void fightOutPokemonBiosSetMeroMeroNoAttackFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetMotoFightPokemonPtr(FightOutPokemon*, u32);
void fightOutPokemonBiosSetMyselfDamageAtkTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMyselfDamageAtkValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetMyselfDamageSpeTargetId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetMyselfDamageSpeValue(FightOutPokemon*, s16);
void fightOutPokemonBiosSetNamakeFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetNoPressureFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetOumuWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetOutWazaKoukanaiFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetPassPpdecFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetReceivesWazaHiraishinFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetSequencePtr(FightOutPokemon*, u32);
void fightOutPokemonBiosSetSketchWazaDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetStockItemDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetSuccessCnt(FightOutPokemon*, u8);
void fightOutPokemonBiosSetTameWazaFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetTokuseiDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetUsedItemDataId(FightOutPokemon*, u16);
void fightOutPokemonBiosSetVanishoffFlag(FightOutPokemon*, u8);
void fightOutPokemonBiosSetZokuseiDataId(FightOutPokemon*, u8, u16);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
u16 fightOutPokemonGetMotoWazaDataId(FightOutPokemon*);
u16 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u8 fightPokemonBiosGetCatchEntryFlag(FightPokemon*);
u8 fightPokemonBiosGetDarkOutFlag(FightPokemon*);
s16 fightPokemonBiosGetEntryId(FightPokemon*);
FightJoutai* fightPokemonBiosGetFightJoutaiPtr(FightPokemon*, u16);
u8 fightPokemonBiosGetHokakuFlag(FightPokemon*);
u8 fightPokemonBiosGetLevelUpFlag(FightPokemon*);
Pokemon* fightPokemonBiosGetMotoPokemonPtr(FightPokemon*);
Pokemon* fightPokemonBiosGetPokemonBuffPtr(FightPokemon*);
void fightPokemonBiosSetCatchEntryFlag(FightPokemon*, u8);
void fightPokemonBiosSetDarkOutFlag(FightPokemon*, u8);
void fightPokemonBiosSetEntryId(FightPokemon*, s16);
void fightPokemonBiosSetHokakuFlag(FightPokemon*, u8);
void fightPokemonBiosSetLevelUpFlag(FightPokemon*, u8);
void fightPokemonBiosSetMotoPokemonPtr(FightPokemon*, u32);
u8 fightWazaCheckWriteJoutaiDataId(FightWaza*, u16);
void fightWazaInitJoutai(FightWaza*);
void fightWazaInitJoutaiDataId(FightWaza*, u16);
u8 fightWazaIsHit(FightWaza*);
u8 fightWazaIsJoutaiDataId(FightWaza*, u16);
void fightWazaWriteJoutaiDataId(FightWaza*, u16, u32);
u8 fightWaza_GetCritical(FightWaza*);
u32 fightWaza_GetDamage(FightWaza*);
u8 fightWaza_GetDamageValue(FightWaza*);
u32 fightWaza_GetHitDamage(FightWaza*);
u16 fightWaza_GetIryoku(FightWaza*);
u16 fightWaza_GetTargetDataId(FightWaza*);
void fightWaza_SetCritical(FightWaza*, u8);
void fightWaza_SetDamage(FightWaza*, u32);
void fightWaza_SetDamageValue(FightWaza*, u8);
void fightWaza_SetHitDamage(FightWaza*, u32);
void fightWaza_SetIryoku(FightWaza*, u16);
void fightWaza_SetMotoWazaDataId(FightWaza*, u16);
void fightWaza_SetTargetDataId(FightWaza*, u16);
void fightWaza_SetUseWazaDataId(FightWaza*, u16);
u16 pokemonBiosGetAmari(Pokemon*);
u8 pokemonBiosGetAmariRibbon(Pokemon*);
Attest* pokemonBiosGetAttest(Pokemon*);
u8 pokemonBiosGetBeautiful(Pokemon*);
u8 pokemonBiosGetBeautifulMedal(Pokemon*);
u8 pokemonBiosGetBromideRibbon(Pokemon*);
u8 pokemonBiosGetCatchBallId(Pokemon*);
u16 pokemonBiosGetCatchFloorId(Pokemon*);
u8 pokemonBiosGetCatchLevel(Pokemon*);
char* pokemonBiosGetCatchTrainerNamePtr(Pokemon*);
u32 pokemonBiosGetCatchTrainerRnd(Pokemon*);
u8 pokemonBiosGetCatchTrainerSex(Pokemon*);
u8 pokemonBiosGetChampRibbon(Pokemon*);
u8 pokemonBiosGetClever(Pokemon*);
u8 pokemonBiosGetCleverMedal(Pokemon*);
u32 pokemonBiosGetConditionAmari(Pokemon*);
u8 pokemonBiosGetCountryRibbon(Pokemon*);
u8 pokemonBiosGetCute(Pokemon*);
u8 pokemonBiosGetCuteMedal(Pokemon*);
u8 pokemonBiosGetDarkFlag(Pokemon*);
u16 pokemonBiosGetDarkpokemonDataId(Pokemon*);
u32 pokemonBiosGetDp(Pokemon*);
u8 pokemonBiosGetEarthRibbon(Pokemon*);
u32 pokemonBiosGetExp(Pokemon*);
u16 pokemonBiosGetFightTrainerPokemonDataId(Pokemon*);
u8 pokemonBiosGetFlagAmari(Pokemon*);
u16 pokemonBiosGetFriend(Pokemon*);
u8 pokemonBiosGetFur(Pokemon*);
u8 pokemonBiosGetFuseiFlag(Pokemon*);
u8 pokemonBiosGetGanbaRibbon(Pokemon*);
u16 pokemonBiosGetHp(Pokemon*);
u16 pokemonBiosGetInitDp(Pokemon*);
u16 pokemonBiosGetItemDataId(Pokemon*);
u8 pokemonBiosGetLandRibbon(Pokemon*);
u8 pokemonBiosGetLevel(Pokemon*);
u8 pokemonBiosGetMailId(Pokemon*);
u8 pokemonBiosGetMarineRibbon(Pokemon*);
u16 pokemonBiosGetMaxHp(Pokemon*);
u16 pokemonBiosGetMaxHpEffort(Pokemon*);
u16 pokemonBiosGetMaxHpRnd(Pokemon*);
u8 pokemonBiosGetNationalRibbon(Pokemon*);
char* pokemonBiosGetNicknameOrgPtr(Pokemon*);
char* pokemonBiosGetNicknamePtr(Pokemon*);
u16 pokemonBiosGetNimbleness(Pokemon*);
u16 pokemonBiosGetNimblenessEffort(Pokemon*);
u16 pokemonBiosGetNimblenessRnd(Pokemon*);
u16 pokemonBiosGetPara1Amari(Pokemon*);
u8 pokemonBiosGetPcboxMark(Pokemon*);
u16 pokemonBiosGetPhyAtk(Pokemon*);
u16 pokemonBiosGetPhyAtkEffort(Pokemon*);
u16 pokemonBiosGetPhyAtkRnd(Pokemon*);
u16 pokemonBiosGetPhyDef(Pokemon*);
u16 pokemonBiosGetPhyDefEffort(Pokemon*);
u16 pokemonBiosGetPhyDefRnd(Pokemon*);
u16 pokemonBiosGetPokemonDataId(Pokemon*);
u16 pokemonBiosGetPokemonWazaDataId(Pokemon*, u16);
u8 pokemonBiosGetPokemonWazaPp(Pokemon*, u16);
u8 pokemonBiosGetPokemonWazaPpCount(Pokemon*, u16);
u8 pokemonBiosGetPokerus(Pokemon*);
u32 pokemonBiosGetPoolExp(Pokemon*);
u16 pokemonBiosGetPoolFriend(Pokemon*);
u32 pokemonBiosGetRnd(Pokemon*);
u8 pokemonBiosGetSkyRibbon(Pokemon*);
u16 pokemonBiosGetSpeAtk(Pokemon*);
u16 pokemonBiosGetSpeAtkEffort(Pokemon*);
u16 pokemonBiosGetSpeAtkRnd(Pokemon*);
u16 pokemonBiosGetSpeDef(Pokemon*);
u16 pokemonBiosGetSpeDefEffort(Pokemon*);
u16 pokemonBiosGetSpeDefRnd(Pokemon*);
u8 pokemonBiosGetStrong(Pokemon*);
u8 pokemonBiosGetStrongMedal(Pokemon*);
u8 pokemonBiosGetStyle(Pokemon*);
u8 pokemonBiosGetStyleMedal(Pokemon*);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 pokemonBiosGetTokuseiFlag(Pokemon*);
u8 pokemonBiosGetVictoryRibbon(Pokemon*);
u8 pokemonBiosGetWinningRibbon(Pokemon*);
u8 pokemonBiosGetWorldRibbon(Pokemon*);
void pokemonBiosSetAmari(Pokemon*, u16);
void pokemonBiosSetAmariRibbon(Pokemon*, u8);
void pokemonBiosSetBeautiful(Pokemon*, u8);
void pokemonBiosSetBeautifulMedal(Pokemon*, u8);
void pokemonBiosSetBromideRibbon(Pokemon*, u8);
void pokemonBiosSetCatchBallId(Pokemon*, u8);
void pokemonBiosSetCatchFloorId(Pokemon*, u16);
void pokemonBiosSetCatchLevel(Pokemon*, u8);
void pokemonBiosSetCatchTrainerNamePtr(Pokemon*, u16*);
void pokemonBiosSetCatchTrainerRnd(Pokemon*, u32);
void pokemonBiosSetCatchTrainerSex(Pokemon*, u8);
void pokemonBiosSetChampRibbon(Pokemon*, u8);
void pokemonBiosSetClever(Pokemon*, u8);
void pokemonBiosSetCleverMedal(Pokemon*, u8);
void pokemonBiosSetConditionAmari(Pokemon*, u32);
void pokemonBiosSetCountryRibbon(Pokemon*, u8);
void pokemonBiosSetCute(Pokemon*, u8);
void pokemonBiosSetCuteMedal(Pokemon*, u8);
void pokemonBiosSetDarkpokemonDataId(Pokemon*, u16);
void pokemonBiosSetDp(Pokemon*, u32);
void pokemonBiosSetEarthRibbon(Pokemon*, u8);
void pokemonBiosSetExp(Pokemon*, u32);
void pokemonBiosSetFightTrainerPokemonDataId(Pokemon*, u16);
void pokemonBiosSetFlagAmari(Pokemon*, u8);
void pokemonBiosSetFriend(Pokemon*, u16);
void pokemonBiosSetFur(Pokemon*, u8);
void pokemonBiosSetFuseiFlag(Pokemon*, u8);
void pokemonBiosSetGanbaRibbon(Pokemon*, u8);
void pokemonBiosSetHp(Pokemon*, u16);
void pokemonBiosSetItemDataId(Pokemon*, u16);
void pokemonBiosSetLandRibbon(Pokemon*, u8);
void pokemonBiosSetLevel(Pokemon*, u8);
void pokemonBiosSetMailId(Pokemon*, u8);
void pokemonBiosSetMarineRibbon(Pokemon*, u8);
void pokemonBiosSetMaxHp(Pokemon*, u16);
void pokemonBiosSetMaxHpEffort(Pokemon*, u16);
void pokemonBiosSetMaxHpRnd(Pokemon*, u16);
void pokemonBiosSetNationalRibbon(Pokemon*, u8);
void pokemonBiosSetNicknameOrgPtr(Pokemon*, u16*);
void pokemonBiosSetNicknamePtr(Pokemon*, u16*);
void pokemonBiosSetNimbleness(Pokemon*, u16);
void pokemonBiosSetNimblenessEffort(Pokemon*, u16);
void pokemonBiosSetNimblenessRnd(Pokemon*, u16);
void pokemonBiosSetPara1Amari(Pokemon*, u16);
void pokemonBiosSetPcboxMark(Pokemon*, u8);
void pokemonBiosSetPhyAtk(Pokemon*, u16);
void pokemonBiosSetPhyAtkEffort(Pokemon*, u16);
void pokemonBiosSetPhyAtkRnd(Pokemon*, u16);
void pokemonBiosSetPhyDef(Pokemon*, u16);
void pokemonBiosSetPhyDefEffort(Pokemon*, u16);
void pokemonBiosSetPhyDefRnd(Pokemon*, u16);
void pokemonBiosSetPokemonDataId(Pokemon*, u16);
void pokemonBiosSetPokemonWazaDataId(Pokemon*, u16, u16);
void pokemonBiosSetPokemonWazaPp(Pokemon*, u16, u8);
void pokemonBiosSetPokemonWazaPpCount(Pokemon*, u16, u8);
void pokemonBiosSetPokerus(Pokemon*, u8);
void pokemonBiosSetPoolExp(Pokemon*, u32);
void pokemonBiosSetPoolFriend(Pokemon*, u16);
void pokemonBiosSetRnd(Pokemon*, u32);
void pokemonBiosSetSkyRibbon(Pokemon*, u8);
void pokemonBiosSetSpeAtk(Pokemon*, u16);
void pokemonBiosSetSpeAtkEffort(Pokemon*, u16);
void pokemonBiosSetSpeAtkRnd(Pokemon*, u16);
void pokemonBiosSetSpeDef(Pokemon*, u16);
void pokemonBiosSetSpeDefEffort(Pokemon*, u16);
void pokemonBiosSetSpeDefRnd(Pokemon*, u16);
void pokemonBiosSetStrong(Pokemon*, u8);
void pokemonBiosSetStrongMedal(Pokemon*, u8);
void pokemonBiosSetStyle(Pokemon*, u8);
void pokemonBiosSetStyleMedal(Pokemon*, u8);
void pokemonBiosSetTamagoFlag(Pokemon*, u8);
void pokemonBiosSetTokuseiFlag(Pokemon*, u8);
void pokemonBiosSetVictoryRibbon(Pokemon*, u8);
void pokemonBiosSetWinningRibbon(Pokemon*, u8);
void pokemonBiosSetWorldRibbon(Pokemon*, u8);
u16 pokemonDataBiosGetBasisMaxHp(PokemonData*);
u16 pokemonDataBiosGetBasisNimbleness(PokemonData*);
u16 pokemonDataBiosGetBasisPhyAtk(PokemonData*);
u16 pokemonDataBiosGetBasisPhyDef(PokemonData*);
u16 pokemonDataBiosGetBasisSpeAtk(PokemonData*);
u16 pokemonDataBiosGetBasisSpeDef(PokemonData*);
u8 pokemonDataBiosGetColor(PokemonData*, u16);
u32 pokemonDataBiosGetDoc(PokemonData*);
u8 pokemonDataBiosGetGet(PokemonData*);
u16 pokemonDataBiosGetGetWazaDataId(PokemonData*, u16);
u8 pokemonDataBiosGetGetWazaLevel(PokemonData*, u16);
u16 pokemonDataBiosGetGiveExp(PokemonData*);
u16 pokemonDataBiosGetGiveMaxHpEffort(PokemonData*);
u16 pokemonDataBiosGetGiveNimblenessEffort(PokemonData*);
u16 pokemonDataBiosGetGivePhyAtkEffort(PokemonData*);
u16 pokemonDataBiosGetGivePhyDefEffort(PokemonData*);
u16 pokemonDataBiosGetGiveSpeAtkEffort(PokemonData*);
u16 pokemonDataBiosGetGiveSpeDefEffort(PokemonData*);
u8 pokemonDataBiosGetGrowDataId(PokemonData*);
u16 pokemonDataBiosGetHeight(PokemonData*);
u16 pokemonDataBiosGetInitFriend(PokemonData*);
u16 pokemonDataBiosGetItemDataId(PokemonData*, u16);
u16 pokemonDataBiosGetKowaza(PokemonData*, u16);
u32 pokemonDataBiosGetMitaFlag(PokemonData*);
const char* pokemonDataBiosGetName(PokemonData*);
u16 pokemonDataBiosGetNumPokemon(PokemonData*);
u16 pokemonDataBiosGetNumZukan(PokemonData*);
u32 pokemonDataBiosGetPkxDataId(PokemonData*);
u32 pokemonDataBiosGetPokebodyId(PokemonData*, u16);
u8 pokemonDataBiosGetSexRatio(PokemonData*);
u16 pokemonDataBiosGetSinkaBuff(PokemonData*, u16);
u8 pokemonDataBiosGetSinkaKind(PokemonData*, u16);
u16 pokemonDataBiosGetSinkaPokemonDataId(PokemonData*, u16);
u32 pokemonDataBiosGetStatusFaceMenuSpriteId(PokemonData*, u16);
u8 pokemonDataBiosGetTokuseiDataId(PokemonData*, u16);
u32 pokemonDataBiosGetTukamaetaFlag(PokemonData*);
u32 pokemonDataBiosGetTypeName(PokemonData*);
u16 pokemonDataBiosGetVoice(PokemonData*);
u16 pokemonDataBiosGetWeight(PokemonData*);
u8 pokemonDataBiosGetZokuseiDataId(PokemonData*, u16);
void pokemonDataBiosSetBasisMaxHp(PokemonData*, u16);
void pokemonDataBiosSetBasisNimbleness(PokemonData*, u16);
void pokemonDataBiosSetBasisPhyAtk(PokemonData*, u16);
void pokemonDataBiosSetBasisPhyDef(PokemonData*, u16);
void pokemonDataBiosSetBasisSpeAtk(PokemonData*, u16);
void pokemonDataBiosSetBasisSpeDef(PokemonData*, u16);
void pokemonDataBiosSetColor(PokemonData*, u16, u8);
void pokemonDataBiosSetDoc(PokemonData*, u32);
void pokemonDataBiosSetGet(PokemonData*, u8);
void pokemonDataBiosSetGetWazaDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetGetWazaLevel(PokemonData*, u16, u8);
void pokemonDataBiosSetGiveExp(PokemonData*, u16);
void pokemonDataBiosSetGiveMaxHpEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveNimblenessEffort(PokemonData*, u16);
void pokemonDataBiosSetGivePhyAtkEffort(PokemonData*, u16);
void pokemonDataBiosSetGivePhyDefEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveSpeAtkEffort(PokemonData*, u16);
void pokemonDataBiosSetGiveSpeDefEffort(PokemonData*, u16);
void pokemonDataBiosSetGrowDataId(PokemonData*, u8);
void pokemonDataBiosSetHeight(PokemonData*, u16);
void pokemonDataBiosSetInitFriend(PokemonData*, u16);
void pokemonDataBiosSetItemDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetKowaza(PokemonData*, u16, u16);
void pokemonDataBiosSetMitaFlag(PokemonData*, u32);
void pokemonDataBiosSetName(PokemonData*, const char*);
void pokemonDataBiosSetNumPokemon(PokemonData*, u16);
void pokemonDataBiosSetNumZukan(PokemonData*, u16);
void pokemonDataBiosSetPkxDataId(PokemonData*, u32);
void pokemonDataBiosSetPokebodyId(PokemonData*, u16, u32);
void pokemonDataBiosSetSexRatio(PokemonData*, u8);
void pokemonDataBiosSetSinkaBuff(PokemonData*, u16, u16);
void pokemonDataBiosSetSinkaKind(PokemonData*, u16, u8);
void pokemonDataBiosSetSinkaPokemonDataId(PokemonData*, u16, u16);
void pokemonDataBiosSetStatusFaceMenuSpriteId(PokemonData*, u16, u16);
void pokemonDataBiosSetTokuseiDataId(PokemonData*, u16, u8);
void pokemonDataBiosSetTukamaetaFlag(PokemonData*, u32);
void pokemonDataBiosSetTypeName(PokemonData*, u32);
void pokemonDataBiosSetVoice(PokemonData*, u16);
void pokemonDataBiosSetWeight(PokemonData*, u16);
void pokemonDataBiosSetZokuseiDataId(PokemonData*, u16, u8);
PokemonData* pokemonDataBiosGetPtr(u32);
}
extern "C" u32 pokemonSeikakuDataBiosGetName(PokemonSeikakuDataBios*);
extern "C" int pokemonSeikakuDataBiosGetReliveFightout(PokemonSeikakuDataBios*);
extern "C" int pokemonSeikakuDataBiosGetReliveWalk(PokemonSeikakuDataBios*);
extern "C" int pokemonSeikakuDataBiosGetReliveCall(PokemonSeikakuDataBios*);
extern "C" int pokemonSeikakuDataBiosGetReliveSodateya(PokemonSeikakuDataBios*);
extern "C" int pokemonSeikakuDataBiosGetReliveNadenade(PokemonSeikakuDataBios*);
extern "C" u32 pokemonSeikakuRateDataBiosGetWaru(PokemonSeikakuRateBios*);
extern "C" u32 pokemonSeikakuRateDataBiosGetKake(PokemonSeikakuRateBios*);
extern "C" PokemonSeikakuRateBios* pokemonSeikakuRateDataBiosGetPtr(u32);
extern "C" u32 pokemonSeikakuDataBiosGetNimblenessRateDataId(PokemonSeikakuDataBios*);
extern "C" u32 pokemonSeikakuDataBiosGetSpeDefRateDataId(PokemonSeikakuDataBios*);
extern "C" u32 pokemonSeikakuDataBiosGetSpeAtkRateDataId(PokemonSeikakuDataBios*);
extern "C" u32 pokemonSeikakuDataBiosGetPhyDefRateDataId(PokemonSeikakuDataBios*);
extern "C" u32 pokemonSeikakuDataBiosGetPhyAtkRateDataId(PokemonSeikakuDataBios*);
extern "C" PokemonSeikakuDataBios* pokemonSeikakuDataBiosGetPtr(u32);
extern "C" PokemonGrowDataBios* pokemonGrowDataBiosGetPtr(u8);
extern "C" int pokemonGrowDataBiosGetExp(PokemonGrowDataBios*, unsigned char);
extern "C" void pokemonDataBiosSetWazaMcn(PokemonData*,u16,u8);
extern "C" bool pokemonDataBiosGetWazaMcn(PokemonData*,u16);
extern "C" u8 pokemonGetSex(Pokemon*);
extern "C" void pokemon_SetPoolFriend(Pokemon*, u16);
extern "C" void pokemon_SetPoolExp(Pokemon*, u32);
extern "C" void pokemon_SetDarkpokemonDataId(Pokemon*, u16);
extern "C" void pokemon_SetTokuseiFlag(Pokemon* , u32);
extern "C" void pokemon_SetMaxHp(Pokemon*, u16);
extern "C" void pokemon_SetHp(Pokemon*, u16);
extern "C" void pokemon_SetPokemonWazaPpCount(Pokemon*, u32, u8);
extern "C" void pokemon_SetPokemonWazaPp(Pokemon*, u32, u8);
extern "C" void pokemon_SetPokemonWazaDataId(Pokemon*, u32, u16);
extern "C" void pokemon_SetLevel(Pokemon*, u8);
extern "C" void pokemon_SetExp(Pokemon*, u32);
extern "C" u8 pokemon_GetNowExpToLevel(Pokemon*);
extern "C" u32 pokemon_GetSeikaku(Pokemon*);
extern "C" u16 pokemon_GetMaxHp(Pokemon*);
extern "C" u16 pokemon_GetHp(Pokemon*);
extern "C" u32 pokemon_GetExp(Pokemon*);
extern "C" u32 pokemon_GetCatchTrainerRnd(Pokemon*);
extern "C" u32 pokemon_GetRnd(Pokemon*);
extern "C" u32 pokemon_GetPokemonDataId(Pokemon*);
extern "C" u32 pokemonDB_GetTokuseiDataId(u32, u16);
extern "C" u8 pokemonDB_GetGrowDataId(u32);
#endif
