#include <dolphin/types.h>

struct FIGHT_FLOOR;
struct FightActionData;
struct FightEncountData;
struct FightFloorData;
struct FightKindData;
struct FightOutPokemon;
struct FightPokemon;
struct FightSide;
struct FightTrainer;
struct FightTypeData;
struct FightWaza;
struct Joutai;
struct TrainerInventoryItem;

enum FightFloorStatus {
    FLOOR_STATUS_DATA_NAME = 0x1,
    FLOOR_STATUS_DATA_FLOOR_DATA_ID = 0x2,
    FLOOR_STATUS_DATA_FIGHT_SIDE_DATA_ID = 0x3,
    FLOOR_STATUS_DATA_TIKEI_DATA_ID = 0x4,
    FLOOR_STATUS_DATA_SYOUKAI_WZX_DATA_ID = 0x5,
    FLOOR_STATUS_DATA_BGM_SND_ID = 0x6,
    FLOOR_STATUS_DATA_ENV_SND_ID = 0x7,
    FLOOR_STATUS_JOUTAI_PTR = 0x9,
    FLOOR_STATUS_IS_JOUTAI_DATA_ID = 0xa,
    FLOOR_STATUS_CHECK_WRITE_JOUTAI_DATA_ID = 0xb,
    FLOOR_STATUS_TURN_COUNT = 0xc,
    FLOOR_STATUS_ENCOUNT_DATA_ID = 0xd,
    FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_FLOOR_DATA_ID = 0xe,
    FLOOR_STATUS_D_B__TIKEI_DATA_ID = 0xf,
    FLOOR_STATUS_D_B__SYOUKAI_WZX_DATA_ID = 0x10,
    FLOOR_STATUS_BGM_SND_DATA_ID = 0x11,
    FLOOR_STATUS_FIGHT_ENCOUNT_ENV_SND_DATA_ID = 0x12,
    FLOOR_STATUS_NOW_TENKOU_DATA_ID = 0x13,
    FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_TYPE = 0x14,
    FLOOR_STATUS_FIGHT_TYPE_DATA_NAME = 0x15,
    FLOOR_STATUS_FIGHT_TYPE_DATA_TRAINER_NUM = 0x16,
    FLOOR_STATUS_FIGHT_TYPE_DATA_ENTRY_POKEMON_NUM = 0x17,
    FLOOR_STATUS_FIGHT_TYPE_DATA_FIGHTOUT_POKEMON_NUM = 0x18,
    FLOOR_STATUS_FIGHT_TYPE_FIGHT_SIDE_FIGHT_OUT_POKEMON_MAX = 0x19,
    FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_KIND = 0x1a,
    FLOOR_STATUS_FIGHT_KIND_DATA_NAME = 0x1b,
    FLOOR_STATUS_FIGHT_KIND_DATA_BACK_SAVE_DATA_FLAG = 0x1c,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_BADGE_CHECK_FLAG = 0x1d,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_ZUKAN_MITA_FLAG = 0x1e,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_ZUKAN_TUKAMAETA_FLAG = 0x1f,
    FLOOR_STATUS_FIGHT_KIND_DATA_USE_ITEM_FLAG = 0x20,
    FLOOR_STATUS_FIGHT_KIND_DATA_CALL_FLAG = 0x21,
    FLOOR_STATUS_FIGHT_KIND_DATA_NIGERU_FLAG = 0x22,
    FLOOR_STATUS_FIGHT_KIND_DATA_DRAW_FLAG = 0x23,
    FLOOR_STATUS_FIGHT_KIND_DATA_EXP_FLAG = 0x24,
    FLOOR_STATUS_FIGHT_KIND_DATA_OKANE_POOL_FLAG = 0x26,
    FLOOR_STATUS_FIGHT_KIND_DATA_OKANE_FLAG = 0x25,
    FLOOR_STATUS_FIGHT_KIND_DATA_FRIEND_FLAG = 0x27,
    FLOOR_STATUS_FIGHT_KIND_DATA_INFECT_POKERUS_FLAG = 0x28,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_CRITICAL_ATTACK_FLAG = 0x29,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_HIZUKI_AI_FLAG = 0x2a,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_HIZUKI_MIYABURI_FLAG = 0x2b,
    FLOOR_STATUS_FIGHT_KIND_DATA_DO_ITEM_SOUBI_TOKUKOUTOKUBOUUP_FLAG = 0x2c,
    FLOOR_STATUS_FIGHT_KIND_DATA_KEIKENTIHUERU_FLAG = 0x2d,
    FLOOR_STATUS_FIGHT_KIND_DATA_BOSS_FLAG = 0x2e,
    FLOOR_STATUS_FIGHT_KIND_DATA_DOROBOU_FLAG = 0x2f,
    FLOOR_STATUS_FIGHT_KIND_DATA_MONOHIROI_FLAG = 0x30,
    FLOOR_STATUS_FIGHT_KIND_DATA_DARKPOKEMON_HYPERMODE_FLAG = 0x31,
    FLOOR_STATUS_FIGHT_KIND_DATA_POKEMON_STATUS_MENU_SUBBAR_FLAG = 0x32,
    FLOOR_STATUS_FIGHT_KIND_DATA_HOST_ENEMY_MSG_FLAG = 0x33,
    FLOOR_STATUS_FIGHT_KIND_DATA_REGULATION_FLAG = 0x34,
    FLOOR_STATUS_FIGHT_SIDE_PTR = 0x35,
    FLOOR_STATUS_ATTACK_POKEMON_PTR = 0x36,
    FLOOR_STATUS_FIGHT_OUT_POKEMON_USE_WAZA_DATA_ID = 0x37,
    FLOOR_STATUS_FIGHT_OUT_POKEMON_MOTO_WAZA_DATA_ID = 0x38,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__DAMAGE_VALUE = 0x39,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__CRITICAL = 0x3a,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__JOUTAI_DATA_ID = 0x3b,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__IS_HIT = 0x3d,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__DAMAGE = 0x3e,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__IRYOKU = 0x3f,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__TARGET_ID = 0x40,
    FLOOR_STATUS_FIGHT_OUT_POKEMON__HIT_DAMAGE = 0x41,
    FLOOR_STATUS_DEFENSE_POKEMON_PTR = 0x42,
    FLOOR_STATUS_ESCAPE_POKEMON_PTR = 0x44,
    FLOOR_STATUS_IREKAE_POKEMON_PTR = 0x45,
    FLOOR_STATUS_KIZETU_POKEMON_PTR = 0x46,
    FLOOR_STATUS_TUIKAKOUKA_POKEMON_PTR = 0x47,
    FLOOR_STATUS_TOKUSEI_POKEMON_PTR = 0x48,
    FLOOR_STATUS_ITEM_POKEMON_PTR = 0x49,
    FLOOR_STATUS_ENCOUNT_FLOOR_ID = 0x4a,
    FLOOR_STATUS_APPOINT_POKEMON_PTR = 0x4b,
    FLOOR_STATUS_APPOINT_TRAINER_PTR = 0x4c,
    FLOOR_STATUS_APPOINT_WAZA_PTR = 0x4d,
    FLOOR_STATUS_APPOINT_SIDE_PTR = 0x4e,
    FLOOR_STATUS_APPOINT_ITEM_PTR = 0x4f,
    FLOOR_STATUS_APPOINT_MSG_ID = 0x50,
    FLOOR_STATUS_ATTACK_MSG_ID = 0x51,
    FLOOR_STATUS_CRITICAL_MSG_ID = 0x52,
    FLOOR_STATUS_WAZAKOUKA_MSG_ID = 0x53,
    FLOOR_STATUS_APPOINT_POKEMON_DATA_ID = 0x54,
    FLOOR_STATUS_APPOINT_WAZA_DATA_ID = 0x55,
    FLOOR_STATUS_APPOINT_ITEM_DATA_ID = 0x56,
    FLOOR_STATUS_APPOINT_TOKUSEI_DATA_ID = 0x57,
    FLOOR_STATUS_FIGHT_POKEMON_ENTRY_CNT = 0x58,
    FLOOR_STATUS_FIGHT_OUT_POKEMON_PTR_ARY = 0x59,
    FLOOR_STATUS_FIGHT_OUT_POKEMON_PTR_ARY_PTR = 0x5a,
    FLOOR_STATUS_FIRST_ATTACK_RND = 0x5b,
    FLOOR_STATUS_FIGHT_FIGHT_RESULT_ID = 0x5c,
    FLOOR_STATUS_FIGHT_OUT_BANME_TO_VALID_FIGHT_OUT_POKEMON = 0x5d,
};
extern "C" {
u32 fightFloorDataBiosGetName(FightFloorData*);
u32 fightFloorDataBiosGetFloorDataId(FightFloorData*);
u32 fightFloorDataBiosGetFightSideDataId(FightFloorData*, u8);
u32 fightFloorDataBiosGetTikeiDataId(FightFloorData*);
u32 fightFloorDataBiosGetSyoukaiWzxDataId(FightFloorData*);
u32 fightFloorDataBiosGetBgmSndId(FightFloorData*);
u32 fightFloorDataBiosGetEnvSndId(FightFloorData*);
Joutai* fightFloorBiosGetJoutaiPtr(FIGHT_FLOOR*, u16);
u32 fightFloorIsJoutaiDataId(FIGHT_FLOOR*, u16);
u32 fightFloorCheckWriteJoutaiDataId(FIGHT_FLOOR*, u16);
u32 fightFloorBiosGetTurnCount(FIGHT_FLOOR*);
u32 fightFloorBiosGetEncountDataId(FIGHT_FLOOR*);
u32 fightFloor_GetEncountDataId(FIGHT_FLOOR*);
FightEncountData* fightEncountDataBiosGetPtr(u32);
u32 fightEncountDataBiosGetFightFloorDataId(FightEncountData*);
u32 fightFloor_GetFightFloorDataId(FIGHT_FLOOR*);
u32 fightFloorDB_GetTikeiDataId(u32);
u32 fightFloorDB_GetSyoukaiWzxDataId(u32);
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR*);
u32 fightEncountGetEnvSndDataId(u32);
u32 fightFloorGetNowTenkouDataId(FIGHT_FLOOR*, u8);
u32 fightEncountDataBiosGetFightType(FightEncountData*);
u8 fightFloor_GetFightType(FIGHT_FLOOR*);
FightTypeData* fightTypeDataBiosGetPtr(u8);
u32 fightTypeDataBiosGetName(FightTypeData*);
u32 fightTypeDataBiosGetTrainerNum(FightTypeData*);
u32 fightTypeDataBiosGetEntryPokemonNum(FightTypeData*);
u32 fightTypeDataBiosGetFightoutPokemonNum(FightTypeData*);
u32 fightTypeGetFightSideFightOutPokemonMax(u8);
u32 fightEncountDataBiosGetFightKind(FightEncountData*);
u32 fightFloor_GetFightKind(FIGHT_FLOOR*);
FightKindData* fightKindDataBiosGetPtr(u8);
u32 fightKindDataBiosGetName(FightKindData*);
u32 fightKindDataBiosGetBackSaveDataFlag(FightKindData*);
u32 fightKindDataBiosGetDoBadgeCheckFlag(FightKindData*);
u32 fightKindDataBiosGetDoZukanMitaFlag(FightKindData*);
u32 fightKindDataBiosGetDoZukanTukamaetaFlag(FightKindData*);
u32 fightKindDataBiosGetUseItemFlag(FightKindData*);
u32 fightKindDataBiosGetCallFlag(FightKindData*);
u32 fightKindDataBiosGetNigeruFlag(FightKindData*);
u32 fightKindDataBiosGetDrawFlag(FightKindData*);
u32 fightKindDataBiosGetGetExpFlag(FightKindData*);
u32 fightKindDataBiosGetOkanePoolFlag(FightKindData*);
u32 fightKindDataBiosGetGetOkaneFlag(FightKindData*);
u32 fightKindDataBiosGetGetFriendFlag(FightKindData*);
u32 fightKindDataBiosGetGetInfectPokerusFlag(FightKindData*);
u32 fightKindDataBiosGetDoCriticalAttackFlag(FightKindData*);
u32 fightKindDataBiosGetDoHizukiAiFlag(FightKindData*);
u32 fightKindDataBiosGetDoHizukiMiyaburiFlag(FightKindData*);
u32 fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(FightKindData*);
u32 fightKindDataBiosGetKeikentihueruFlag(FightKindData*);
u32 fightKindDataBiosGetBossFlag(FightKindData*);
u32 fightKindDataBiosGetDorobouFlag(FightKindData*);
u32 fightKindDataBiosGetMonohiroiFlag(FightKindData*);
u32 fightKindDataBiosGetDarkpokemonHypermodeFlag(FightKindData*);
u32 fightKindDataBiosGetPokemonStatusMenuSubbarFlag(FightKindData*);
u32 fightKindDataBiosGetHostEnemyMsgFlag(FightKindData*);
u32 fightKindDataBiosGetRegulationFlag(FightKindData*);
FightSide* fightFloorBiosGetFightSidePtr(FIGHT_FLOOR*, u16);
FightOutPokemon* fightFloorBiosGetAttackPokemonPtr(FIGHT_FLOOR*);
u32 fightOutPokemonGetUseWazaDataId(FightOutPokemon*);
u32 fightOutPokemonGetMotoWazaDataId(FightOutPokemon*);
u32 fightOutPokemon_GetDamageValue(FightOutPokemon*);
u32 fightOutPokemon_GetCritical(FightOutPokemon*);
u32 fightOutPokemon_GetJoutaiDataId(FightOutPokemon*, u16);
u32 fightOutPokemon_GetIsHit(FightOutPokemon*);
u32 fightOutPokemon_GetDamage(FightOutPokemon*);
u32 fightOutPokemon_GetIryoku(FightOutPokemon*);
u32 fightOutPokemon_GetTargetId(FightOutPokemon*);
u32 fightOutPokemon_GetHitDamage(FightOutPokemon*);
FightOutPokemon* fightFloorBiosGetDefensePokemonPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetEscapePokemonPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetIrekaePokemonPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetKizetuPokemonPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetTuikakoukaPokemonPtr(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetTokuseiPokemonPtr(FIGHT_FLOOR*);
TrainerInventoryItem* fightFloorBiosGetItemPokemonPtr(FIGHT_FLOOR*);
u32 fightFloorBiosGetEncountFloorId(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetAppointPokemonPtr(FIGHT_FLOOR*);
FightTrainer* fightFloorBiosGetAppointTrainerPtr(FIGHT_FLOOR*);
FightWaza* fightFloorBiosGetAppointWazaPtr(FIGHT_FLOOR*);
FightSide* fightFloorBiosGetAppointSidePtr(FIGHT_FLOOR*);
TrainerInventoryItem* fightFloorBiosGetAppointItemPtr(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAttackMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetCriticalMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetWazakoukaMsgId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointPokemonDataId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointWazaDataId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointItemDataId(FIGHT_FLOOR*);
u32 fightFloorBiosGetAppointTokuseiDataId(FIGHT_FLOOR*);
u32 fightFloorBiosGetFightPokemonEntryCnt(FIGHT_FLOOR*);
FightOutPokemon* fightFloorBiosGetFightOutPokemonPtrAry(FIGHT_FLOOR*, u16);
FightOutPokemon** fightFloorBiosGetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*);
u32 fightFloorBiosGetFirstAttackRnd(FIGHT_FLOOR*);
u32 fightGetFightResultId();
u32 fightFloorGetFightOutBanmeToValidFightOutPokemon(FIGHT_FLOOR*, u16);
FIGHT_FLOOR* fightFloorBiosGetFightFloorPtr();
FightFloorData* fightFloorDataBiosGetPtr(u16);

u32 fightFloorGetStatus(FIGHT_FLOOR* floor, u16 dataId, u16 property, u16 index) {
    void* object = floor;
    if (property >= 0x60) return 0;
    if (property == 0) return reinterpret_cast<u32>(fightFloorBiosGetFightFloorPtr());
    if (property < 8) {
        object = fightFloorDataBiosGetPtr(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0x5f) {
        if (object == nullptr) {
            object = fightFloorBiosGetFightFloorPtr();
            if (object == nullptr) return 0;
        }
    }
    switch (property) {
    case FLOOR_STATUS_DATA_NAME: return fightFloorDataBiosGetName(static_cast<FightFloorData*>(object));
    case FLOOR_STATUS_DATA_FLOOR_DATA_ID: return static_cast<u16>(fightFloorDataBiosGetFloorDataId(static_cast<FightFloorData*>(object)));
    case FLOOR_STATUS_DATA_FIGHT_SIDE_DATA_ID: return static_cast<u16>(fightFloorDataBiosGetFightSideDataId(static_cast<FightFloorData*>(object), static_cast<u8>(index)));
    case FLOOR_STATUS_DATA_TIKEI_DATA_ID: return static_cast<u8>(fightFloorDataBiosGetTikeiDataId(static_cast<FightFloorData*>(object)));
    case FLOOR_STATUS_DATA_SYOUKAI_WZX_DATA_ID: return fightFloorDataBiosGetSyoukaiWzxDataId(static_cast<FightFloorData*>(object));
    case FLOOR_STATUS_DATA_BGM_SND_ID: return fightFloorDataBiosGetBgmSndId(static_cast<FightFloorData*>(object));
    case FLOOR_STATUS_DATA_ENV_SND_ID: return fightFloorDataBiosGetEnvSndId(static_cast<FightFloorData*>(object));
    case FLOOR_STATUS_JOUTAI_PTR: return reinterpret_cast<u32>(fightFloorBiosGetJoutaiPtr(static_cast<FIGHT_FLOOR*>(object), index));
    case FLOOR_STATUS_IS_JOUTAI_DATA_ID: return static_cast<u8>(fightFloorIsJoutaiDataId(static_cast<FIGHT_FLOOR*>(object), index));
    case FLOOR_STATUS_CHECK_WRITE_JOUTAI_DATA_ID: return static_cast<u8>(fightFloorCheckWriteJoutaiDataId(static_cast<FIGHT_FLOOR*>(object), index));
    case FLOOR_STATUS_TURN_COUNT: return static_cast<u16>(fightFloorBiosGetTurnCount(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_ENCOUNT_DATA_ID: return static_cast<u16>(fightFloorBiosGetEncountDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_FLOOR_DATA_ID: return static_cast<u16>(fightEncountDataBiosGetFightFloorDataId(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_D_B__TIKEI_DATA_ID: return static_cast<u8>(fightFloorDB_GetTikeiDataId(fightFloor_GetFightFloorDataId(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_D_B__SYOUKAI_WZX_DATA_ID: return fightFloorDB_GetSyoukaiWzxDataId(fightFloor_GetFightFloorDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_BGM_SND_DATA_ID: return fightFloorGetBgmSndDataId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_FIGHT_ENCOUNT_ENV_SND_DATA_ID: return fightEncountGetEnvSndDataId(fightFloor_GetEncountDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_NOW_TENKOU_DATA_ID: return static_cast<u8>(fightFloorGetNowTenkouDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(index) != 0));
    case FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_TYPE: return static_cast<u8>(fightEncountDataBiosGetFightType(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_FIGHT_TYPE_DATA_NAME: return fightTypeDataBiosGetName(fightTypeDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_FIGHT_TYPE_DATA_TRAINER_NUM: return static_cast<u8>(fightTypeDataBiosGetTrainerNum(fightTypeDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_TYPE_DATA_ENTRY_POKEMON_NUM: return static_cast<u8>(fightTypeDataBiosGetEntryPokemonNum(fightTypeDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_TYPE_DATA_FIGHTOUT_POKEMON_NUM: return static_cast<u8>(fightTypeDataBiosGetFightoutPokemonNum(fightTypeDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_TYPE_FIGHT_SIDE_FIGHT_OUT_POKEMON_MAX: return static_cast<u16>(fightTypeGetFightSideFightOutPokemonMax(static_cast<u8>(fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_FIGHT_ENCOUNT_DATA_FIGHT_KIND: return static_cast<u8>(fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_NAME: return fightKindDataBiosGetName(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object)))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_BACK_SAVE_DATA_FLAG: return static_cast<u8>(fightKindDataBiosGetBackSaveDataFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_BADGE_CHECK_FLAG: return static_cast<u8>(fightKindDataBiosGetDoBadgeCheckFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_ZUKAN_MITA_FLAG: return static_cast<u8>(fightKindDataBiosGetDoZukanMitaFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_ZUKAN_TUKAMAETA_FLAG: return static_cast<u8>(fightKindDataBiosGetDoZukanTukamaetaFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_USE_ITEM_FLAG: return static_cast<u8>(fightKindDataBiosGetUseItemFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_CALL_FLAG: return static_cast<u8>(fightKindDataBiosGetCallFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_NIGERU_FLAG: return static_cast<u8>(fightKindDataBiosGetNigeruFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DRAW_FLAG: return static_cast<u8>(fightKindDataBiosGetDrawFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_EXP_FLAG: return static_cast<u8>(fightKindDataBiosGetGetExpFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_OKANE_POOL_FLAG: return static_cast<u8>(fightKindDataBiosGetOkanePoolFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_OKANE_FLAG: return static_cast<u8>(fightKindDataBiosGetGetOkaneFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_FRIEND_FLAG: return static_cast<u8>(fightKindDataBiosGetGetFriendFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_INFECT_POKERUS_FLAG: return static_cast<u8>(fightKindDataBiosGetGetInfectPokerusFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_CRITICAL_ATTACK_FLAG: return static_cast<u8>(fightKindDataBiosGetDoCriticalAttackFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_HIZUKI_AI_FLAG: return static_cast<u8>(fightKindDataBiosGetDoHizukiAiFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_HIZUKI_MIYABURI_FLAG: return static_cast<u8>(fightKindDataBiosGetDoHizukiMiyaburiFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DO_ITEM_SOUBI_TOKUKOUTOKUBOUUP_FLAG: return static_cast<u8>(fightKindDataBiosGetDoItemSoubiTokukoutokubouupFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_KEIKENTIHUERU_FLAG: return static_cast<u8>(fightKindDataBiosGetKeikentihueruFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_BOSS_FLAG: return static_cast<u8>(fightKindDataBiosGetBossFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DOROBOU_FLAG: return static_cast<u8>(fightKindDataBiosGetDorobouFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_MONOHIROI_FLAG: return static_cast<u8>(fightKindDataBiosGetMonohiroiFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_DARKPOKEMON_HYPERMODE_FLAG: return static_cast<u8>(fightKindDataBiosGetDarkpokemonHypermodeFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_POKEMON_STATUS_MENU_SUBBAR_FLAG: return static_cast<u8>(fightKindDataBiosGetPokemonStatusMenuSubbarFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_HOST_ENEMY_MSG_FLAG: return static_cast<u8>(fightKindDataBiosGetHostEnemyMsgFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_KIND_DATA_REGULATION_FLAG: return static_cast<u8>(fightKindDataBiosGetRegulationFlag(fightKindDataBiosGetPtr(static_cast<u8>(fightFloor_GetFightKind(static_cast<FIGHT_FLOOR*>(object))))));
    case FLOOR_STATUS_FIGHT_SIDE_PTR: return reinterpret_cast<u32>(fightFloorBiosGetFightSidePtr(static_cast<FIGHT_FLOOR*>(object), index));
    case FLOOR_STATUS_ATTACK_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON_USE_WAZA_DATA_ID: return static_cast<u16>(fightOutPokemonGetUseWazaDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON_MOTO_WAZA_DATA_ID: return static_cast<u16>(fightOutPokemonGetMotoWazaDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__DAMAGE_VALUE: return static_cast<u8>(fightOutPokemon_GetDamageValue(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__CRITICAL: return static_cast<u8>(fightOutPokemon_GetCritical(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__JOUTAI_DATA_ID: return static_cast<u8>(fightOutPokemon_GetJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), index));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__IS_HIT: return static_cast<u8>(fightOutPokemon_GetIsHit(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__DAMAGE: return fightOutPokemon_GetDamage(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__IRYOKU: return static_cast<u16>(fightOutPokemon_GetIryoku(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__TARGET_ID: return static_cast<u16>(fightOutPokemon_GetTargetId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object))));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON__HIT_DAMAGE: return fightOutPokemon_GetHitDamage(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_DEFENSE_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetDefensePokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_ESCAPE_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetEscapePokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_IREKAE_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetIrekaePokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_KIZETU_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetKizetuPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_TUIKAKOUKA_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetTuikakoukaPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_TOKUSEI_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetTokuseiPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_ITEM_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetItemPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_ENCOUNT_FLOOR_ID: return fightFloorBiosGetEncountFloorId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_APPOINT_POKEMON_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAppointPokemonPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_TRAINER_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAppointTrainerPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_WAZA_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAppointWazaPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_SIDE_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAppointSidePtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_ITEM_PTR: return reinterpret_cast<u32>(fightFloorBiosGetAppointItemPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_MSG_ID: return fightFloorBiosGetAppointMsgId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_ATTACK_MSG_ID: return fightFloorBiosGetAttackMsgId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_CRITICAL_MSG_ID: return fightFloorBiosGetCriticalMsgId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_WAZAKOUKA_MSG_ID: return fightFloorBiosGetWazakoukaMsgId(static_cast<FIGHT_FLOOR*>(object));
    case FLOOR_STATUS_APPOINT_POKEMON_DATA_ID: return static_cast<u16>(fightFloorBiosGetAppointPokemonDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_WAZA_DATA_ID: return static_cast<u16>(fightFloorBiosGetAppointWazaDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_ITEM_DATA_ID: return static_cast<u16>(fightFloorBiosGetAppointItemDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_APPOINT_TOKUSEI_DATA_ID: return static_cast<u16>(fightFloorBiosGetAppointTokuseiDataId(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_POKEMON_ENTRY_CNT: return static_cast<s16>(fightFloorBiosGetFightPokemonEntryCnt(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON_PTR_ARY: return reinterpret_cast<u32>(fightFloorBiosGetFightOutPokemonPtrAry(static_cast<FIGHT_FLOOR*>(object), index));
    case FLOOR_STATUS_FIGHT_OUT_POKEMON_PTR_ARY_PTR: return reinterpret_cast<u32>(fightFloorBiosGetFightOutPokemonPtrAryPtr(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIRST_ATTACK_RND: return static_cast<u16>(fightFloorBiosGetFirstAttackRnd(static_cast<FIGHT_FLOOR*>(object)));
    case FLOOR_STATUS_FIGHT_FIGHT_RESULT_ID: return static_cast<u16>(fightGetFightResultId());
    case FLOOR_STATUS_FIGHT_OUT_BANME_TO_VALID_FIGHT_OUT_POKEMON: return fightFloorGetFightOutBanmeToValidFightOutPokemon(static_cast<FIGHT_FLOOR*>(object), index);
    default: return 0;
    }
}
}

extern "C" {
u32 joutaiDataBiosGetStatus(u16);
void joutaiSetNowKaisuuJoutaiDataId(Joutai*, u16, u32);
s32 joutaiGetNowKaisuuJoutaiDataId(Joutai*, u16);
s32 joutaiGetKaisuuJoutaiDataId(Joutai*, u16);
void joutaiWriteJoutaiDataId(Joutai*, u16, u32);
u32 joutaiCheckWriteJoutaiDataId(Joutai*, u16);
u32 joutaiIsJoutaiDataId(Joutai*, u16);
void joutaiInitJoutaiDataId(Joutai*, u16);
FightSide* fightFloor_GetFightSidePtr(FIGHT_FLOOR*, u16);
u8 fightSideCheckValid(FightSide*);
s32 fightFloor_GetFightPokemonEntryCnt(FIGHT_FLOOR*);
void fightFloor_SetfightPokemonEntryCnt(FIGHT_FLOOR*, s16);

void fightFloorSetNowKaisuuJoutaiDataId(FIGHT_FLOOR* floor, u16 id, u32 count) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) == 9)
        joutaiSetNowKaisuuJoutaiDataId(reinterpret_cast<Joutai*>(floor), id, count);
}
s32 fightFloorGetNowKaisuuJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) != 9) return -1;
    return joutaiGetNowKaisuuJoutaiDataId(reinterpret_cast<Joutai*>(floor), id);
}
s32 fightFloorGetKaisuuJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) != 9) return -1;
    return joutaiGetKaisuuJoutaiDataId(reinterpret_cast<Joutai*>(floor), id);
}
void fightFloorWriteJoutaiDataId(FIGHT_FLOOR* floor, u16 id, u32 value) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) == 9)
        joutaiWriteJoutaiDataId(reinterpret_cast<Joutai*>(floor), id, value);
}
u32 fightFloorCheckWriteJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) != 9) return 0;
    return joutaiCheckWriteJoutaiDataId(reinterpret_cast<Joutai*>(floor), id);
}
u32 fightFloorIsJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) != 9) return 0;
    return joutaiIsJoutaiDataId(reinterpret_cast<Joutai*>(floor), id);
}
void fightFloorInitJoutaiDataId(FIGHT_FLOOR* floor, u16 id) {
    if (static_cast<u16>(joutaiDataBiosGetStatus(id)) == 9)
        joutaiInitJoutaiDataId(reinterpret_cast<Joutai*>(floor), id);
}
FightSide* fightFloorGetValidFightSidePtr(FIGHT_FLOOR* floor, u16 side) {
    FightSide* record = fightFloor_GetFightSidePtr(floor, side);
    if (fightSideCheckValid(record) == 0) return nullptr;
    return record;
}
s32 fightFloorGetFightPokemonEntryCntInc(FIGHT_FLOOR* floor) {
    s32 count = fightFloor_GetFightPokemonEntryCnt(floor);
    fightFloor_SetfightPokemonEntryCnt(floor, count + 1);
    return count;
}
FIGHT_FLOOR* fightFloorGetNowPtr() {
    return reinterpret_cast<FIGHT_FLOOR*>(fightFloorGetStatus(nullptr, 0, 0, 0));
}
}

struct Pokemon;
extern "C" {
u32 fightGetFightEncountDataId();
u32 fightEncountDataBiosGetDiskId(FightEncountData*);
u32 fightFloor_GetFightKindRegulationFlag(FIGHT_FLOOR*);
s32 menuCBRule_GetCommandTimeLimit();
s32 menuCBRule_GetBattleTimeLimit();
u32 fightEncountGetBgmSndDataId(u32);
FightOutPokemon* fightFloor_GetDefensePokemonPtr(FIGHT_FLOOR*);
Pokemon* fightOutPokemonGetPokemonPtr(FightOutPokemon*);
FightTrainer* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR*);
u8 fightTargetIsHostSide(void*, u8);
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR*, u16, u8, void*);
u8 fightFloor_GetIsJoutaiDataId(FIGHT_FLOOR*, u16);

u8 fightFloorIsUseFightTimerCommand(FIGHT_FLOOR* floor) {
    u32 regulation = fightFloor_GetFightKindRegulationFlag(floor);
    s32 limit = menuCBRule_GetCommandTimeLimit();
    if (static_cast<u8>(regulation) == 1 && limit > 0) return 1;
    return 0;
}
u8 fightFloorIsUseFightTimerAll(FIGHT_FLOOR* floor) {
    u32 regulation = fightFloor_GetFightKindRegulationFlag(floor);
    s32 limit = menuCBRule_GetBattleTimeLimit();
    if (static_cast<u8>(regulation) == 1 && limit > 0) return 1;
    return 0;
}
u8 fightFloorIsNowEncountOpeningVirtualBattle(FIGHT_FLOOR* floor) {
    u8 kind = fightFloor_GetFightKind(floor);
    u32 disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
    if (kind == 15 && static_cast<u16>(disk) == 0) return 1;
    return 0;
}
u8 fightFloorIsNowEncountVirtualBattle(FIGHT_FLOOR* floor) {
    u8 kind = fightFloor_GetFightKind(floor);
    u32 disk = fightEncountDataBiosGetDiskId(fightEncountDataBiosGetPtr(fightGetFightEncountDataId()));
    if ((kind == 15 || kind == 14) && static_cast<u16>(disk) != 0) return 1;
    return 0;
}
u8 fightFloorIsNowEncountHostPokemonKime(FIGHT_FLOOR* floor) {
    fightEncountDataBiosGetPtr(fightFloor_GetEncountDataId(floor));
    return 0;
}
u8 fightFloorIsNowEncountHostEnemyPokemonKime(FIGHT_FLOOR* floor) {
    u32 encounter = fightFloor_GetEncountDataId(floor);
    switch (static_cast<u8>(fightEncountDataBiosGetFightKind(fightEncountDataBiosGetPtr(encounter)))) {
    case 12: case 13: return 1;
    }
    if (static_cast<u16>(encounter) == 0xd9) return 1;
    return static_cast<u16>(encounter) == 0x191;
}
u8 fightFloorIsNowEncountSnatchOnly(FIGHT_FLOOR* floor) {
    return static_cast<u16>(fightFloor_GetEncountDataId(floor)) == 0xe0;
}
u8 fightFloorIsNowEncountTuusinTaisen(FIGHT_FLOOR* floor) {
    return static_cast<u8>(fightFloor_GetFightKind(floor)) == 11;
}
u32 fightFloorGetBgmSndDataId(FIGHT_FLOOR* floor) {
    return fightEncountGetBgmSndDataId(fightFloor_GetEncountDataId(floor));
}
Pokemon* fightFloorGetDefPokemonPtr(FIGHT_FLOOR* floor) {
    if (floor == nullptr) {
        floor = fightFloorBiosGetFightFloorPtr();
        if (floor == nullptr) return nullptr;
    }
    FightOutPokemon* pokemon = fightFloor_GetDefensePokemonPtr(floor);
    if (pokemon == nullptr) return nullptr;
    return fightOutPokemonGetPokemonPtr(pokemon);
}
u8 fightFloorIsGcHeroHostSide(FIGHT_FLOOR* floor) {
    u32 type = fightFloor_GetFightType(floor);
    FightTrainer* trainer = fightFloorGetGcHeroFightTrainerPtr(floor);
    if (trainer != nullptr && fightTargetIsHostSide(trainer, type) == 1) return 1;
    return 0;
}
u8 fightFloorIsGcHeroWin(FIGHT_FLOOR* floor, u16 result) {
    if (result == 2 || result == 3) {
        if (fightFloorIsGcHeroHostSide(floor) == 1) {
            if (result == 2) return 1;
        } else {
            if (result == 3) return 1;
        }
    }
    return 0;
}
u32 fightFloorGetNowTenkouDataId(FIGHT_FLOOR* floor, u8 checkAbilities) {
    if (checkAbilities == 1) {
        if (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(floor, 13, 0, 0)) return 0;
        if (fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(floor, 77, 0, 0)) return 0;
    }
    if (fightFloor_GetIsJoutaiDataId(floor, 0x4e) == 1) return 0;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x4f) == 1) return 1;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x50) == 1) return 2;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x51) == 1) return 3;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x52) == 1) return 5;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x53) == 1) return 4;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x54) == 1) return 1;
    if (fightFloor_GetIsJoutaiDataId(floor, 0x55) == 1) return 2;
    return fightFloor_GetIsJoutaiDataId(floor, 0x56) == 1 ? 3 : 0;
}
}

extern "C" {
Joutai* fightFloor_GetJoutaiPtr(FIGHT_FLOOR*, u16);
void joutaiInitAry(Joutai*, u16);
void fightFloor_SetTurnCount(FIGHT_FLOOR*, u16);
void fightFloor_SetEncountDataId(FIGHT_FLOOR*, u16);
void fightSideInitAry(FightSide*, u16);
void fightFloorInitFightTarget(FIGHT_FLOOR*);
void fightFloorInitFightOutPokemonPtrAry(FIGHT_FLOOR*);
void fightFloor_SetFisstAttackRnd(FIGHT_FLOOR*, u16);
void fightFloor_SetStockPokemonNum(FIGHT_FLOOR*, u8);
void fightFloor_SetStockPokemonPtr(FIGHT_FLOOR*, u8, Pokemon*);
void fightFloor_SetStockPokemonBallID(FIGHT_FLOOR*, u8, u16);
FightOutPokemon** fightFloor_GetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*);
u32 fightFloorSetStatus(void*, u16, u16, u32, u32);
void fightFloor_SetAppointMsgPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetCriticakMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloor_SetAppointPokemonDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointPokemonWazaDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointItemDataId(FIGHT_FLOOR*, u16);
void fightFloor_SetAppointTokuseiDataId(FIGHT_FLOOR*, u16);
extern u8 wildPokemonDownFlag;
u8 statusMenuCnt[4] = {255, 255, 255, 255};
}
static void _fightFloorInitFightOutPokemonPtrAry(FightOutPokemon** pokemon) {
    for (u16 i = 0; i < 8; i++) pokemon[i] = nullptr;
}
extern "C" {
void fightFloorInitFightOutPokemonPtrAry(FIGHT_FLOOR* floor) {
    FightOutPokemon** pokemon = fightFloor_GetFightOutPokemonPtrAryPtr(floor);
    if (pokemon != nullptr) _fightFloorInitFightOutPokemonPtrAry(pokemon);
}
void fightFloorInitFightTarget(FIGHT_FLOOR* floor) {
    u16 properties[13] = {0x36, 0x42, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f};
    for (u16 i = 0; i < 13; i++) fightFloorSetStatus(floor, 0, properties[i], 0, 0);
    fightFloor_SetAppointMsgPtr(floor, nullptr);
    fightFloor_SetAttackMsgId(floor, 0);
    fightFloor_SetCriticakMsgId(floor, 0);
    fightFloor_SetWazakoukaMsgId(floor, 0);
    fightFloor_SetAppointPokemonDataId(floor, 0);
    fightFloor_SetAppointPokemonWazaDataId(floor, 0);
    fightFloor_SetAppointItemDataId(floor, 0);
    fightFloor_SetAppointTokuseiDataId(floor, 0);
}
void fightFloorInit(FIGHT_FLOOR* floor) {
    joutaiInitAry(fightFloor_GetJoutaiPtr(floor, 0), 1);
    fightFloor_SetTurnCount(floor, 0);
    fightFloor_SetEncountDataId(floor, 0);
    fightSideInitAry(fightFloor_GetFightSidePtr(floor, 0), 2);
    fightFloorInitFightTarget(floor);
    fightFloor_SetfightPokemonEntryCnt(floor, 0);
    fightFloorInitFightOutPokemonPtrAry(floor);
    fightFloor_SetFisstAttackRnd(floor, 0);
    fightFloor_SetStockPokemonNum(floor, 0);
    for (u8 i = 0; i < 6; i++) {
        fightFloor_SetStockPokemonPtr(floor, i, nullptr);
        fightFloor_SetStockPokemonBallID(floor, i, 0);
    }
    wildPokemonDownFlag = 0;
}
void fightFloorCreate(FIGHT_FLOOR* floor, u16 encounter) {
    if (floor != nullptr) {
        fightFloorInit(floor);
        fightFloor_SetEncountDataId(floor, encounter);
        fightFloor_SetTurnCount(floor, 1);
    }
}
void fightFloor_SetStatusMenuCnt(s32 property, u8 count) {
    switch (property) {
    case 0x37: statusMenuCnt[0] = count; break;
    case 0x38: statusMenuCnt[1] = count; break;
    case 0x40: statusMenuCnt[2] = count; break;
    case 0x41: statusMenuCnt[3] = count; break;
    }
}
s32 fightFloor_GetStatusMenuCnt(s32 property) {
    s32 count = -1;
    switch (property) {
    case 0x37: count = statusMenuCnt[0]; break;
    case 0x38: count = statusMenuCnt[1]; break;
    case 0x40: count = statusMenuCnt[2]; break;
    case 0x41: count = statusMenuCnt[3]; break;
    }
    return count;
}
}

extern "C" {
struct PokemonTokuseiData;
u8 fightOutPokemonCheckValid(FightOutPokemon*);
u32 fightOutPokemonGetTokuseiDataId(FightOutPokemon*);
u16 fightOutPokemonGetSoubiItemDataId(FightOutPokemon*);
PokemonTokuseiData* pokemonTokuseiDataBiosGetPtr(u32);
u32 pokemonTokuseiDataBiosGetName(PokemonTokuseiData*);
u32 GSmsgGetGSchar(u32);
void fightMsgctrlSetValue(u32, u32);
u32 itemDB_GetName(u16);
void pokemonSetStatus(void*,u16,u16,u16,u32);
u32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void*,u8);
void fightFloor_SetAttackPokemonFightWazaTargetId(FIGHT_FLOOR*,u32);
void fightFloor_SetDefensePokemonPtr(FIGHT_FLOOR*,void*);
void fightFloorBiosSetAttackPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetDefensePokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetTuikakoukaPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetAppointPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloorBiosSetItemPokemonPtr(FIGHT_FLOOR*,void*);
void fightFloorBiosSetAppointItemDataId(FIGHT_FLOOR*,u16);
void fightFloorBiosSetAppointTokuseiDataId(FIGHT_FLOOR*,u16);
void fightFloorDataBiosSetName(FightFloorData*, u32);
void fightFloorDataBiosSetFloorDataId(FightFloorData*, u16);
void fightFloorDataBiosSetFightSideDataId(FightFloorData*, u8, u16);
void fightFloorDataBiosSetTikeiDataId(FightFloorData*, u8);
void fightFloorDataBiosSetSyoukaiWzxDataId(FightFloorData*, u32);
void fightFloorDataBiosSetBgmSndId(FightFloorData*, u32);
void fightFloorDataBiosSetEnvSndId(FightFloorData*, u32);
void fightFloorBiosSetTurnCount(FIGHT_FLOOR*, u16);
void fightFloorBiosSetEncountDataId(FIGHT_FLOOR*, u16);
void fightOutPokemon_SetUseWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetMotoWazaDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaDamageValue(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaCritical(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaJoutaiDataId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaInitJoutaiDataId(FightOutPokemon*, u8);
void fightOutPokemon_SetWazaDamage(FightOutPokemon*, u32);
void fightOutPokemon_SetWazaIryoku(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaTargetId(FightOutPokemon*, u16);
void fightOutPokemon_SetWazaHitDamage(FightOutPokemon*, u32);
void fightFloorBiosSetEscapePokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetIrekaePokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetKizetuPokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetTokuseiPokemonPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetEncountFloorId(u32);
void fightFloorBiosSetAppointTrainerPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointWazaPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointSidePtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointItemPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAttackMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetCriticalMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetWazakoukaMsgId(FIGHT_FLOOR*, u32);
void fightFloorBiosSetAppointPokemonDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetAppointWazaDataId(FIGHT_FLOOR*, u16);
void fightFloorBiosSetFightPokemonEntryCnt(FIGHT_FLOOR*, s16);
void fightFloorBiosSetFightOutPokemonPtrAry(FIGHT_FLOOR*, u32, u32);
void fightFloorBiosSetFightOutPokemonPtrAryPtr(FIGHT_FLOOR*, u32);
void fightFloorBiosSetFirstAttackRnd(FIGHT_FLOOR*, u16);
u8 fightFloorSetFightResultId(FIGHT_FLOOR*, u16);
u32 fightFloorSetStatus(void* object, u16 dataId, u16 property, u32 index, u32 value) {
    u32 result = 0;
    u32 type = fightFloor_GetFightType(static_cast<FIGHT_FLOOR*>(object));
    if (property == 0 || property >= 0x60) return 0;
    if (property < 8) {
        object = fightFloorDataBiosGetPtr(dataId);
        if (object == nullptr) return 0;
    } else if (property < 0x5f) {
        if (object == nullptr) {
            object = fightFloorBiosGetFightFloorPtr();
            if (object == nullptr) return 0;
        }
    }
    switch (property) {
    case 0x1: { fightFloorDataBiosSetName(static_cast<FightFloorData*>(object), value); break; }
    case 0x2: { fightFloorDataBiosSetFloorDataId(static_cast<FightFloorData*>(object), static_cast<u16>(value)); break; }
    case 0x3: { fightFloorDataBiosSetFightSideDataId(static_cast<FightFloorData*>(object), static_cast<u8>(index), static_cast<u16>(value)); break; }
    case 0x4: { fightFloorDataBiosSetTikeiDataId(static_cast<FightFloorData*>(object), static_cast<u8>(value)); break; }
    case 0x5: { fightFloorDataBiosSetSyoukaiWzxDataId(static_cast<FightFloorData*>(object), value); break; }
    case 0x6: { fightFloorDataBiosSetBgmSndId(static_cast<FightFloorData*>(object), value); break; }
    case 0x7: { fightFloorDataBiosSetEnvSndId(static_cast<FightFloorData*>(object), value); break; }
    case 0xa: { result = fightFloorCheckWriteJoutaiDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value));
        if (static_cast<u8>(result) == 2) fightFloorWriteJoutaiDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value), index); break; }
    case 0xc: { fightFloorBiosSetTurnCount(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0xd: { fightFloorBiosSetEncountDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x36: { if (value != 0) {
        if (fightOutPokemonCheckValid(reinterpret_cast<FightOutPokemon*>(value)) == 1) {
            fightMsgctrlSetValue(15, value);
            fightMsgctrlSetValue(26, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(value))))));
            fightMsgctrlSetValue(31, value);
            fightMsgctrlSetValue(33, value);
            fightMsgctrlSetValue(32, value);
        } else {
            fightMsgctrlSetValue(15, 0);
            fightMsgctrlSetValue(26, 0);
            fightMsgctrlSetValue(31, 0);
            fightMsgctrlSetValue(33, 0);
            fightMsgctrlSetValue(32, 0);
        }
    } else {
            fightMsgctrlSetValue(15, 0);
            fightMsgctrlSetValue(26, 0);
            fightMsgctrlSetValue(31, 0);
            fightMsgctrlSetValue(33, 0);
            fightMsgctrlSetValue(32, 0);
    }
    fightFloorBiosSetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x37: { fightOutPokemon_SetUseWazaDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u16>(value)); break; }
    case 0x38: { fightOutPokemon_SetMotoWazaDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u16>(value)); break; }
    case 0x39: { fightOutPokemon_SetWazaDamageValue(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u8>(value)); break; }
    case 0x3a: { fightOutPokemon_SetWazaCritical(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u8>(value)); break; }
    case 0x3b: { fightOutPokemon_SetWazaJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u16>(value)); break; }
    case 0x3c: { fightOutPokemon_SetWazaInitJoutaiDataId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u8>(value)); break; }
    case 0x3d: { pokemonSetStatus(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), 0, 0xe0, 0, value); break; }
    case 0x3e: { fightOutPokemon_SetWazaDamage(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), value); break; }
    case 0x3f: { fightOutPokemon_SetWazaIryoku(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u16>(value)); break; }
    case 0x40: { fightOutPokemon_SetWazaTargetId(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), static_cast<u16>(value)); break; }
    case 0x41: { fightOutPokemon_SetWazaHitDamage(fightFloorBiosGetAttackPokemonPtr(static_cast<FIGHT_FLOOR*>(object)), value); break; }
    case 0x42: { if (value != 0) {
        if (fightOutPokemonCheckValid(reinterpret_cast<FightOutPokemon*>(value)) == 1) {
            fightMsgctrlSetValue(16, value);
            fightMsgctrlSetValue(27, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(value))))));
            fightMsgctrlSetValue(66, value);
            fightMsgctrlSetValue(68, value);
            fightMsgctrlSetValue(67, value);
        } else {
            fightMsgctrlSetValue(16, 0);
            fightMsgctrlSetValue(27, 0);
            fightMsgctrlSetValue(66, 0);
            fightMsgctrlSetValue(68, 0);
            fightMsgctrlSetValue(67, 0);
        }
    } else {
            fightMsgctrlSetValue(16, 0);
            fightMsgctrlSetValue(27, 0);
            fightMsgctrlSetValue(66, 0);
            fightMsgctrlSetValue(68, 0);
            fightMsgctrlSetValue(67, 0);
    }
    fightFloorBiosSetDefensePokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x43: { fightFloor_SetDefensePokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value));
        fightFloor_SetAttackPokemonFightWazaTargetId(static_cast<FIGHT_FLOOR*>(object), fightTargetGetTragetPtrToRelativeHostSideFightTargetId(reinterpret_cast<void*>(value), type)); break; }
    case 0x44: { fightFloorBiosSetEscapePokemonPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x45: { fightFloorBiosSetIrekaePokemonPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x46: { fightFloorBiosSetKizetuPokemonPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x47: { if (value != 0) {
        if (fightOutPokemonCheckValid(reinterpret_cast<FightOutPokemon*>(value)) == 1) {
            fightMsgctrlSetValue(18, value);
            fightMsgctrlSetValue(29, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(value))))));
        } else {
            fightMsgctrlSetValue(18, 0);
            fightMsgctrlSetValue(29, 0);
        }
    } else {
            fightMsgctrlSetValue(18, 0);
            fightMsgctrlSetValue(29, 0);
    }
    fightFloorBiosSetTuikakoukaPokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x48: { fightFloorBiosSetTokuseiPokemonPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x49: { if (value != 0 && fightOutPokemonCheckValid(reinterpret_cast<FightOutPokemon*>(value)) == 1) fightFloor_SetAppointItemDataId(static_cast<FIGHT_FLOOR*>(object), fightOutPokemonGetSoubiItemDataId(reinterpret_cast<FightOutPokemon*>(value)));
        fightFloorBiosSetItemPokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x4a: { fightFloorBiosSetEncountFloorId(value); break; }
    case 0x4b: { if (value != 0) {
        if (fightOutPokemonCheckValid(reinterpret_cast<FightOutPokemon*>(value)) == 1) {
            fightMsgctrlSetValue(30, value);
            fightMsgctrlSetValue(28, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(fightOutPokemonGetTokuseiDataId(reinterpret_cast<FightOutPokemon*>(value))))));
        } else {
            fightMsgctrlSetValue(30, 0);
            fightMsgctrlSetValue(28, 0);
        }
    } else {
            fightMsgctrlSetValue(30, 0);
            fightMsgctrlSetValue(28, 0);
    }
    fightFloorBiosSetAppointPokemonPtr(static_cast<FIGHT_FLOOR*>(object), reinterpret_cast<void*>(value)); break; }
    case 0x4c: { fightFloorBiosSetAppointTrainerPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x4d: { fightFloorBiosSetAppointWazaPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x4e: { fightFloorBiosSetAppointSidePtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x4f: { fightFloorBiosSetAppointItemPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x50: { fightFloorBiosSetAppointMsgId(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x51: { fightFloorBiosSetAttackMsgId(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x52: { fightFloorBiosSetCriticalMsgId(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x53: { fightFloorBiosSetWazakoukaMsgId(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x54: { fightFloorBiosSetAppointPokemonDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x55: { fightFloorBiosSetAppointWazaDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x56: { fightMsgctrlSetValue(0x29, GSmsgGetGSchar(itemDB_GetName(static_cast<u16>(value))));
        fightFloorBiosSetAppointItemDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x57: { fightMsgctrlSetValue(0x1c, GSmsgGetGSchar(pokemonTokuseiDataBiosGetName(pokemonTokuseiDataBiosGetPtr(static_cast<u16>(value)))));
        fightFloorBiosSetAppointTokuseiDataId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x58: { fightFloorBiosSetFightPokemonEntryCnt(static_cast<FIGHT_FLOOR*>(object), static_cast<s16>(value)); break; }
    case 0x59: { fightFloorBiosSetFightOutPokemonPtrAry(static_cast<FIGHT_FLOOR*>(object), index, value); break; }
    case 0x5a: { fightFloorBiosSetFightOutPokemonPtrAryPtr(static_cast<FIGHT_FLOOR*>(object), value); break; }
    case 0x5b: { fightFloorBiosSetFirstAttackRnd(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x5c: { fightFloorSetFightResultId(static_cast<FIGHT_FLOOR*>(object), static_cast<u16>(value)); break; }
    case 0x5e: { fightMsgctrlSetValue(0x2f, value); break; }
    default: break;
    }
    return static_cast<u8>(result);
}
}

// Iteration callbacks receive the battle type as a halfword and an opaque context.
typedef u8 (*FightFloorCallback)(void*, u16, void*);
extern "C" {
u8 fightFloor_GetFightTypeTrainerNum(FIGHT_FLOOR*);
u8 fightFloor_GetFightTypeFightoutPokemonNum(FIGHT_FLOOR*);
u32 fightFloor_GetFightTypeEntryPokemonNum(FIGHT_FLOOR*);
FightOutPokemon* fightFloor_GetFightOutPokemonPtrAry(FIGHT_FLOOR*, u16);
FightTrainer* fightSideGetValidFightTrainerPtr(FightSide*, u16);
FightOutPokemon* fightTrainerGetValidFightOutPokemonPtr(FightTrainer*, u16);
FightPokemon* fightTrainerGetValidFightPokemonPtr(FightTrainer*, u16);
u8 fightTrainerCheckValid(FightTrainer*);
u8 fightTrainerIsAllyFightTargetPtr(FightTrainer*, void*, u16);
u8 fightPokemonCheckFightOut(FightPokemon*);
u8 fightOutPokemonCheckFightOut(FightOutPokemon*);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR*, FightFloorCallback, void*, u8);
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR*, FightFloorCallback, void*, u8);
void* fightTargetGetPtr(u16, void*, u16);
void fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(FightOutPokemon*, FightSide*);
void fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(FightOutPokemon*, FightSide*);
void fightSideRegistFightSideEnemyPokemonFightAll(FightSide*, FightTrainer*, u16, u16, u16);
}
static FightOutPokemon* _fightFloorLoopValidFightOutPokemonSub(FIGHT_FLOOR* floor, u16 side, u16 trainer, u16 pokemon) {
    FightSide* sidePtr = fightFloorGetValidFightSidePtr(floor, side);
    if (sidePtr == nullptr) return nullptr;
    FightTrainer* trainerPtr = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
    if (trainerPtr == nullptr) return nullptr;
    FightOutPokemon* pokemonPtr = fightTrainerGetValidFightOutPokemonPtr(trainerPtr, pokemon);
    if (pokemonPtr == nullptr) return nullptr;
    return pokemonPtr;
}
extern "C" {
u8 fightFloorLoopValidFightOutPokemon(FIGHT_FLOOR* floor, FightFloorCallback callback, void* context, u8 useArray) {
    u8 success = 1;
    u16 type = fightFloor_GetFightType(floor);
    u16 trainers = fightFloor_GetFightTypeTrainerNum(floor);
    u16 pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    if (useArray == 1) {
        for (u16 i = 0; i < 8; i++) {
            FightOutPokemon* pokemon = fightFloor_GetFightOutPokemonPtrAry(floor, i);
            if (pokemon != nullptr && fightOutPokemonCheckValid(pokemon)) {
                if (callback(pokemon, type, context) == 0) { success = 0; goto done; }
            }
        }
    } else {
        for (u16 pokemon = 0; static_cast<u32>(pokemon) < pokemonCount; pokemon++) {
            for (u16 trainer = 0; static_cast<u32>(trainer) < trainers; trainer++) {
                for (u16 side = 0; side < 2; side++) {
                    FightOutPokemon* record = _fightFloorLoopValidFightOutPokemonSub(floor, side, trainer, pokemon);
                    if (record != nullptr) {
                        if (callback(record, type, context) == 0) { success = 0; goto done; }
                    }
                }
            }
        }
    }
done:
    return success;
}
void fightFloorCreateFightPokemonEnemyAryEnemySideAll(FIGHT_FLOOR* floor) {
    FightSide* sidePtr;
    u16 trainer;
    u16 pokemon;
    u16 side;
    u32 type;
    u32 trainers;
    u32 pokemonCount;
    FightTrainer* trainerPtr;
    FightOutPokemon* record;

    type = fightFloor_GetFightType(floor);
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr != nullptr) {
            for (trainer = 0; trainer < trainers; trainer++) {
                trainerPtr = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (trainerPtr != nullptr) {
                    for (pokemon = 0; pokemon < pokemonCount; pokemon++) {
                        record = fightTrainerGetValidFightOutPokemonPtr(trainerPtr, pokemon);
                        if (record != nullptr && fightOutPokemonCheckFightOut(record)) {
                            FightSide* enemy = static_cast<FightSide*>(fightTargetGetPtr(3, record, type));
                            fightOutPokemonCreateFightPokemonEnemyAryEnemySideAll(record, enemy);
                        }
                    }
                }
            }
        }
    }
}
void fightFloorSetMeetEnemyFightPokemonEnemySideAll(FIGHT_FLOOR* floor) {
    FightSide* sidePtr;
    u16 trainer;
    u16 pokemon;
    u16 side;
    u32 type;
    u32 trainers;
    u32 pokemonCount;
    FightTrainer* trainerPtr;
    FightOutPokemon* record;

    type = fightFloor_GetFightType(floor);
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr != nullptr) {
            for (trainer = 0; trainer < trainers; trainer++) {
                trainerPtr = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (trainerPtr != nullptr) {
                    for (pokemon = 0; pokemon < pokemonCount; pokemon++) {
                        record = fightTrainerGetValidFightOutPokemonPtr(trainerPtr, pokemon);
                        if (record != nullptr && fightOutPokemonCheckFightOut(record)) {
                            FightSide* enemy = static_cast<FightSide*>(fightTargetGetPtr(3, record, type));
                            fightOutPokemonSetMeetEnemyFightPokemonEnemySideAll(record, enemy);
                        }
                    }
                }
            }
        }
    }
}
void fightFloorRegistFightTrainerEnemyPokemonFightSideAll(FIGHT_FLOOR* floor) {
    FightSide* sidePtr;
    u16 trainer;
    u16 side;
    u32 type;
    u32 trainers;
    u32 pokemonCount;
    FightTrainer* trainerPtr;

    type = fightFloor_GetFightType(floor);
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr != nullptr) {
            for (trainer = 0; trainer < trainers; trainer++) {
                trainerPtr = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (trainerPtr != nullptr) {
                    FightSide* enemy = static_cast<FightSide*>(fightTargetGetPtr(3, trainerPtr, type));
                    fightSideRegistFightSideEnemyPokemonFightAll(enemy, trainerPtr, type, trainers, pokemonCount);
                }
            }
        }
    }
}
}

struct FightFloorConditionCount {
    u32 condition;
    u32 count;
};
struct FightFloorAbilitySearch {
    u32 ability;
    u32 countOrPokemon;
    s32 relation;
    void* target;
};
extern "C" {
u8 fightOutPokemonIsJoutaiDataId(FightOutPokemon*,u16);
void* fightTargetGetPtrAsNowFightType(u16,void*);
}
static u8 _fightFloorCheckFightOutPokemonPtrAryJoutaiDataIdSub(void* object, u16 type, void* context) {
    FightFloorConditionCount* search = static_cast<FightFloorConditionCount*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    if (!fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (fightOutPokemonIsJoutaiDataId(pokemon, search->condition) == 1) search->count++;
    return 1;
}
static u8 _fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub(void* object, u16 type, void* context) {
    FightFloorAbilitySearch* search = static_cast<FightFloorAbilitySearch*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    void* target = search->target;
    void* side;
    if (!fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (target == nullptr) side = nullptr;
    else if (search->relation == 1) side = fightTargetGetPtrAsNowFightType(2, target);
    else if (search->relation == 2) side = fightTargetGetPtrAsNowFightType(3, target);
    else side = nullptr;
    void* ownSide = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((search->relation == 1 || search->relation == 2) && side == nullptr) return 1;
    if (search->relation == 0) {
        if (target != nullptr && target == pokemon) return 1;
    } else if (search->relation == 1 || search->relation == 2) {
        if (side != ownSide) return 1;
    } else return 1;
    u32 ability = static_cast<u16>(fightOutPokemonGetTokuseiDataId(pokemon));
    if (static_cast<u16>(search->ability) == ability) {
        search->countOrPokemon = reinterpret_cast<u32>(pokemon);
        return 0;
    }
    return 1;
}
static u8 _fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataIdSub(void* object, u16 type, void* context) {
    FightFloorAbilitySearch* search = static_cast<FightFloorAbilitySearch*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    void* target = search->target;
    void* side;
    if (!fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (target == nullptr) side = nullptr;
    else if (search->relation == 1) side = fightTargetGetPtrAsNowFightType(2, target);
    else if (search->relation == 2) side = fightTargetGetPtrAsNowFightType(3, target);
    else side = nullptr;
    void* ownSide = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((search->relation == 1 || search->relation == 2) && side == nullptr) return 1;
    if (search->relation == 0) {
        if (target != nullptr && target == pokemon) return 1;
    } else if (search->relation == 1 || search->relation == 2) {
        if (side != ownSide) return 1;
    } else return 1;
    u32 ability = static_cast<u16>(fightOutPokemonGetTokuseiDataId(pokemon));
    if (static_cast<u16>(search->ability) == ability) search->countOrPokemon++;
    return 1;
}
extern "C" {
u16 fightFloorCheckFightOutPokemonPtrAryJoutaiDataId(FIGHT_FLOOR* floor, u16 condition) {
    FightFloorConditionCount search;
    search.condition = condition;
    search.count = 0;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorCheckFightOutPokemonPtrAryJoutaiDataIdSub, &search, 0);
    return search.count;
}
FightOutPokemon* fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(FIGHT_FLOOR* floor, u16 ability, u8 useArray, u8 relation, void* target) {
    FightFloorAbilitySearch search;
    search.ability = ability;
    search.countOrPokemon = 0;
    search.relation = relation;
    search.target = target;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirstSub, &search, useArray);
    return reinterpret_cast<FightOutPokemon*>(search.countOrPokemon);
}
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR* floor, u16 ability, u8 relation, void* target) {
    FightFloorAbilitySearch search;
    search.ability = ability;
    search.countOrPokemon = 0;
    search.relation = relation;
    search.target = target;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataIdSub, &search, 0);
    return search.countOrPokemon;
}
}

struct FightFloorTrainerPokemonSearch {
    void* target;
    s32 ally;
    u32 count;
    FightPokemon** output;
    u32 pokemonCount;
    s32 fightOutOnly;
};
struct FightFloorTrainerOutPokemonSearch {
    void* target;
    FightOutPokemon** output;
    u32 count;
    s32 ally;
    s32 fightOutOnly;
};
static u8 _fightFloorGetFightTrainerFightPokemonPtrArySub(void* object, u16 type, void* context) {
    FightFloorTrainerPokemonSearch* search;
    void* target;
    FightTrainer* trainer;
    FightPokemon** output;
    u16 i;
    u16 count;
    search = static_cast<FightFloorTrainerPokemonSearch*>(context);
    trainer = static_cast<FightTrainer*>(object);
    target = search->target;
    output = search->output;
    if (!fightTrainerCheckValid(trainer)) return 1;
    if (search->ally == 0) {
        if (fightTrainerIsAllyFightTargetPtr(trainer, target, type) == 1) return 1;
    } else {
        if (!fightTrainerIsAllyFightTargetPtr(trainer, target, type)) return 1;
    }
    count = search->pokemonCount;
    for (i = 0; static_cast<u32>(i) < count; i++) {
        FightPokemon* pokemon = fightTrainerGetValidFightPokemonPtr(trainer, i);
        if (pokemon != nullptr) {
            if (search->fightOutOnly == 1 && !fightPokemonCheckFightOut(pokemon)) continue;
            output[search->count] = pokemon;
            search->count++;
        }
    }
    return 1;
}
static u8 _fightFloorGetFightTrainerFightOutPokemonPtrArySub(void* object, u16 type, void* context) {
    FightFloorTrainerOutPokemonSearch* search = static_cast<FightFloorTrainerOutPokemonSearch*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    void* target = search->target;
    FightOutPokemon** output = search->output;
    if (search->fightOutOnly == 1 && !fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (search->ally == 0) {
        if (fightTrainerIsAllyFightTargetPtr(static_cast<FightTrainer*>(target), pokemon, type) == 1) return 1;
    } else {
        if (!fightTrainerIsAllyFightTargetPtr(static_cast<FightTrainer*>(target), pokemon, type)) return 1;
    }
    output[search->count] = pokemon;
    search->count++;
    return 1;
}
extern "C" {
u16 fightFloorGetFightTrainerFightPokemonPtrAry(FIGHT_FLOOR* floor, void* target, FightPokemon** output, u8 ally, u8 fightOutOnly) {
    for (u16 i = 0; i < 24; i++) output[i] = nullptr;
    FightFloorTrainerPokemonSearch search;
    search.target = target;
    search.ally = ally;
    search.count = 0;
    search.output = output;
    search.pokemonCount = static_cast<u8>(fightFloor_GetFightTypeEntryPokemonNum(nullptr));
    search.fightOutOnly = fightOutOnly;
    fightFloorLoopValidFightTrainer(floor, _fightFloorGetFightTrainerFightPokemonPtrArySub, &search, 0);
    return search.count;
}
u32 fightFloorGetFightTrainerFightOutPokemonPtrAry(FIGHT_FLOOR* floor, void* target, FightOutPokemon** output, u8 ally, u8 fightOutOnly) {
    _fightFloorInitFightOutPokemonPtrAry(output);
    FightFloorTrainerOutPokemonSearch search;
    search.target = target;
    search.output = output;
    search.count = 0;
    search.ally = ally;
    search.fightOutOnly = fightOutOnly;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorGetFightTrainerFightOutPokemonPtrArySub, &search, 0);
    return static_cast<u16>(search.count);
}
}

extern "C" {
u32 fightFloor_GetFightKindDrawFlag(FIGHT_FLOOR*);
void fightSetFightResultId(u16);
u8 fightTrainerIsGcHero(FightTrainer*);
FightTrainer* fightSide_GetFightTrainerPtr(FightSide*,u16);
FightOutPokemon* fightTrainer_GetFightoutPokemonPtr(FightTrainer*,u16);
void fightOutPokemon_SetUsedItemDataId(FightOutPokemon*,u16);
u8 fightFloorSetFightResultId(FIGHT_FLOOR* floor, u16 result) {
    u32 old = fightGetFightResultId();
    u32 draw = fightFloor_GetFightKindDrawFlag(floor);
    if (static_cast<u16>(old) == result) return 0;
    if (static_cast<u16>(old) == 1) return 1;
    if (result == 0 || result == 1) {
        fightSetFightResultId(result);
        return 1;
    }
    if (static_cast<u8>(draw) == 0) {
        if (static_cast<u16>(old) == 3 || static_cast<u16>(old) == 5) return 0;
        if (result == 7) { fightSetFightResultId(3); return 1; }
        if (result == 6) { fightSetFightResultId(5); return 1; }
    } else {
        if (static_cast<u16>(old) == 7 || static_cast<u16>(old) == 6) return 0;
        if (static_cast<u16>(old) == 3 && result == 2) { fightSetFightResultId(7); return 1; }
        if (static_cast<u16>(old) == 2 && result == 3) { fightSetFightResultId(7); return 1; }
        if (static_cast<u16>(old) == 4 && result == 5) { fightSetFightResultId(6); return 1; }
        if (static_cast<u16>(old) == 5 && result == 4) { fightSetFightResultId(6); return 1; }
    }
    fightSetFightResultId(result);
    return 1;
}
FightTrainer* fightFloorGetGcHeroFightTrainerPtr(FIGHT_FLOOR* floor) {
    FightSide* sidePtr;
    u16 trainer;
    u16 side;
    u32 trainers;
    FightTrainer* record;
    fightFloor_GetFightType(floor);
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr != nullptr) {
            for (trainer = 0; trainer < trainers; trainer++) {
                record = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (record != nullptr && fightTrainerIsGcHero(record) == 1) return record;
            }
        }
    }
    return nullptr;
}
void fightFloorInitFightStart(FIGHT_FLOOR* floor) {
    FightSide* sidePtr;
    FightTrainer* trainerPtr;
    u16 trainer;
    u16 pokemon;
    u16 side;
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloor_GetFightSidePtr(floor, side);
        if (sidePtr != nullptr) {
            for (trainer = 0; trainer < 2; trainer++) {
                trainerPtr = fightSide_GetFightTrainerPtr(sidePtr, trainer);
                if (trainerPtr != nullptr) {
                    for (pokemon = 0; pokemon < 2; pokemon++) {
                        FightOutPokemon* record = fightTrainer_GetFightoutPokemonPtr(trainerPtr, pokemon);
                        if (record != nullptr) fightOutPokemon_SetUsedItemDataId(record, 0);
                    }
                }
            }
        }
    }
}
}

struct FightFloorValidPokemonCount {
    void* target;
    u32 count;
    s32 relation;
    u32 fightOutOnly;
};
struct FightFloorSealedMoveSearch {
    FightOutPokemon* target;
    u32 move;
    u32 found;
};
extern "C" {
FightWaza* fightOutPokemon_GetFightWazaPtr(FightOutPokemon*);
void fightWazaInitJoutai(FightWaza*);
u8 fightOutPokemonIsAlly(FightOutPokemon*,FightOutPokemon*);
s8 pokemonSearchWazaDataId(Pokemon*,u16);
}
static u8 _fightFloorInitFightOutPokemonPtrAryFightWazaJoutaiSub(void* object, u16 type, void* context) {
    fightWazaInitJoutai(fightOutPokemon_GetFightWazaPtr(static_cast<FightOutPokemon*>(object)));
    return 1;
}
static u8 _fightFloorCheckHuuinWazaFightOutPokemonSub(void* object, u16 type, void* context) {
    FightFloorSealedMoveSearch* search = static_cast<FightFloorSealedMoveSearch*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    FightOutPokemon* target = search->target;
    u16 move = search->move;
    if (!fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (!fightOutPokemonIsAlly(pokemon, target)) {
        if (fightOutPokemonIsJoutaiDataId(pokemon, 0x27) == 1) {
            if (pokemonSearchWazaDataId(fightOutPokemonGetPokemonPtr(pokemon), move) >= 0) {
                search->found = 1;
                return 0;
            }
        }
    }
    return 1;
}
static u8 _fightFloorGetValidFightOutPokemonCountSub(void* object, u16 type, void* context) {
    FightFloorValidPokemonCount* search = static_cast<FightFloorValidPokemonCount*>(context);
    FightOutPokemon* pokemon = static_cast<FightOutPokemon*>(object);
    void* target = search->target;
    void* side;
    if (static_cast<u8>(search->fightOutOnly != 0) == 1 && !fightOutPokemonCheckFightOut(pokemon)) return 1;
    if (target == nullptr) side = nullptr;
    else if (search->relation == 1) side = fightTargetGetPtrAsNowFightType(2, target);
    else if (search->relation == 2) side = fightTargetGetPtrAsNowFightType(3, target);
    else side = nullptr;
    void* ownSide = fightTargetGetPtrAsNowFightType(2, pokemon);
    if ((search->relation == 1 || search->relation == 2) && side == nullptr) return 1;
    if (search->relation == 0) {
        if (target != nullptr && target == pokemon) return 1;
    } else if (search->relation == 1 || search->relation == 2) {
        if (side != ownSide) return 1;
    } else return 1;
    search->count++;
    return 1;
}
extern "C" {
void fightFloorInitFightOutPokemonPtrAryFightWazaJoutai(FIGHT_FLOOR* floor) {
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorInitFightOutPokemonPtrAryFightWazaJoutaiSub, nullptr, 0);
}
u8 fightFloorCheckHuuinWazaFightOutPokemon(FIGHT_FLOOR* floor, FightOutPokemon* target, u16 move) {
    FightFloorSealedMoveSearch search;
    search.target = target;
    search.move = move;
    search.found = 0;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorCheckHuuinWazaFightOutPokemonSub, &search, 0);
    return search.found != 0;
}
u16 fightFloorGetValidFightOutPokemonCount(FIGHT_FLOOR* floor, u8 relation, void* target, u8 fightOutOnly) {
    FightFloorValidPokemonCount search;
    search.target = target;
    search.count = 0;
    search.relation = relation;
    search.fightOutOnly = fightOutOnly;
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorGetValidFightOutPokemonCountSub, &search, 0);
    return search.count;
}
}

struct FightActionBuff;
// The action menu begins with an eleven-character name and its escape lock.
struct FightFloorActionMenu { u16 name[11]; u8 escapeDisabled; };
struct FightOutPokemonEnemy { u8 reserved[12]; };
extern "C" {
u8 fightOutPokemonIsFightActionAttackWazaOut(FightOutPokemon*, u32, u32);
void fightOutPokemon_SetFightActionFlag(FightOutPokemon*, u8);
u32 fightOutPokemon_GetFightActionFlag(FightOutPokemon*);
FightActionBuff* fightOutPokemon_GetFightActionBuffPtr(FightOutPokemon*);
u8 fightActionCheckValid(FightActionBuff*);
u16* fightOutPokemonGetNicknamePtr(FightOutPokemon*);
void GScharCpy(u16*, const u16*);
u32 fightFloor_GetFightKindNigeruFlag(FIGHT_FLOOR*);
void fightFloor_SetAttackPokemonPtr(FIGHT_FLOOR*, void*);
void fightFloor_SetDefPokemonAndAtkFightWazaTargetId(FIGHT_FLOOR*, void*);
u32 fightSideGetNokoriFightPokemonNum(FightSide*, u16, u16);
u32 fightSideGetFightPokemonNokoriHp(FightSide*, u16, u16);
u32 fightSideGetFightPokemonMaxHp(FightSide*, u16, u16);
FightOutPokemonEnemy* fightOutPokemon_GetFightOutPokemonEnemyPtr(FightOutPokemon*, u16);
u8 fightOutPokemonEnemyCheckValid(FightOutPokemonEnemy*);
FightOutPokemon* fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(FightOutPokemonEnemy*);
u32 fightOutPokemonEnemyBiosGetInitHp(FightOutPokemonEnemy*);
u32 fightOutPokemonEnemyBiosGetDamage(FightOutPokemonEnemy*);
u32 fightOutPokemonNowHpWaruValue(FightOutPokemon*, u16);
u32 fightOutPokemonMaxHpWaruValue(FightOutPokemon*, u16);
u32 HSD_Rand();
}
static u8 _fightFloorSetTuusinErrorFightResultSub(void* object, u16 type, void* context) {
    fightOutPokemon_SetFightActionFlag(static_cast<FightOutPokemon*>(object), 1);
    return 1;
}
static s16 _fightFloorSetFightOutPokemonPtrAry(FightOutPokemon** output, FightOutPokemon* pokemon) {
    for (u16 i = 0; i < 8; i++) {
        if (output[i] == nullptr) { output[i] = pokemon; return i; }
    }
    return -1;
}
static u32 _fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor, FightOutPokemon** output, bool fightOutOnly, u8 relation, FightOutPokemon* target) {
    FightSide* sidePtr;
    FightSide* targetSide;
    u16 trainer;
    u16 slot;
    u16 side;
    u32 trainers;
    u32 pokemonCount;
    u32 count;
    u32 type;
    FightTrainer* trainerPtr;
    FightOutPokemon* pokemon;
    _fightFloorInitFightOutPokemonPtrAry(output);
    count = 0;
    type = static_cast<u8>(fightFloor_GetFightType(floor));
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    if (relation != 0) {
        if (!fightOutPokemonCheckValid(target)) return 0;
        targetSide = static_cast<FightSide*>(fightTargetGetPtr(2, target, type));
    } else targetSide = nullptr;
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr == nullptr) continue;
        if (relation == 1) { if (targetSide != sidePtr) continue; }
        else if (relation == 2) { if (targetSide == sidePtr) continue; }
        for (trainer = 0; trainer < trainers; trainer++) {
            trainerPtr = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
            if (trainerPtr == nullptr) continue;
            for (slot = 0; slot < pokemonCount; slot++) {
                pokemon = fightTrainerGetValidFightOutPokemonPtr(trainerPtr, slot);
                if (pokemon == nullptr) continue;
                if (fightOutOnly == 1 && !fightOutPokemonCheckFightOut(pokemon)) continue;
                if (relation == 3 && pokemon == target) continue;
                if (_fightFloorSetFightOutPokemonPtrAry(output, pokemon) >= 0) count++;
            }
        }
    }
    return count;
}
extern "C" {
void fightFloorSetTuusinErrorFightResult(FIGHT_FLOOR* floor) {
    fightFloorLoopValidFightOutPokemon(floor, _fightFloorSetTuusinErrorFightResultSub, nullptr, 0);
    fightFloorSetFightResultId(floor, 1);
}
void fightFloorSetTimeOutAllFightResult(FIGHT_FLOOR* floor) {
    u32 enemyHp;
    u32 allyHp;
    u32 allyCount;
    u32 enemyRate;
    u32 allyRate;
    u32 trainers;
    u32 pokemonCount;
    FightSide* enemy;
    FightSide* ally;
    u32 allyMax;
    u32 enemyCount;
    u32 enemyMax;
    if (static_cast<u16>(fightGetFightResultId()) == 1) return;
    trainers = static_cast<u8>(fightFloor_GetFightTypeTrainerNum(floor));
    pokemonCount = static_cast<u8>(fightFloor_GetFightTypeEntryPokemonNum(floor));
    ally = static_cast<FightSide*>(fightTargetGetPtrAsNowFightType(4, nullptr));
    allyCount = fightSideGetNokoriFightPokemonNum(ally, trainers, pokemonCount);
    allyHp = fightSideGetFightPokemonNokoriHp(ally, trainers, pokemonCount);
    allyMax = fightSideGetFightPokemonMaxHp(ally, trainers, pokemonCount);
    allyRate = allyHp * 100 / allyMax;
    enemy = static_cast<FightSide*>(fightTargetGetPtrAsNowFightType(5, nullptr));
    enemyCount = fightSideGetNokoriFightPokemonNum(enemy, trainers, pokemonCount);
    enemyHp = fightSideGetFightPokemonNokoriHp(enemy, trainers, pokemonCount);
    enemyMax = fightSideGetFightPokemonMaxHp(enemy, trainers, pokemonCount);
    enemyRate = enemyHp * 100 / enemyMax;
    fightFloorSetFightResultId(floor, 0);
    if (static_cast<u16>(allyCount) > static_cast<u16>(enemyCount)) fightFloorSetFightResultId(floor, 2);
    if (static_cast<u16>(allyCount) < static_cast<u16>(enemyCount)) fightFloorSetFightResultId(floor, 3);
    if (static_cast<u16>(fightGetFightResultId()) == 0) {
        if (allyRate >= enemyRate) fightFloorSetFightResultId(floor, 2);
        if (allyRate <= enemyRate) fightFloorSetFightResultId(floor, 3);
    }
}
void fightFloorSetMenuFightAction(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightFloorActionMenu* menu) {
    GScharCpy(menu->name, fightOutPokemonGetNicknamePtr(pokemon));
    if (static_cast<u8>(fightFloor_GetFightKindNigeruFlag(floor)) == 1) menu->escapeDisabled = 0;
    else menu->escapeDisabled = 1;
}
u8 fightFloorGetFightTrainerFightOutPokemonIsFightActionAttackWazaOut(FIGHT_FLOOR* floor, void* target, u8 ally, u8 fightOutOnly, u32 move, u32 mode) {
    FightOutPokemon* output[8];
    u32 count;
    FightOutPokemon** array;
    count = fightFloorGetFightTrainerFightOutPokemonPtrAry(floor, target, output, ally, fightOutOnly);
    array = output;
    for (u16 i = 0; i < static_cast<u16>(count); i++) {
        if (fightOutPokemonIsFightActionAttackWazaOut(array[i], move, mode) == 1) return 1;
    }
    return 0;
}
u32 fightFloorGetFightOutPokemonPtrAry(FIGHT_FLOOR* floor, bool fightOutOnly, u8 relation, FightOutPokemon* target, FightOutPokemon** output) {
    _fightFloorInitFightOutPokemonPtrAry(output);
    return _fightFloorCreateFightOutPokemonPtrAry(floor, output, fightOutOnly, relation, target);
}
u8 fightFloorIsLastActionFightOutPokemon(FIGHT_FLOOR* floor) {
    FightOutPokemon* pokemon;
    u16 i;
    u8 last = 1;
    for (i = 0; i < 8; i++) {
        pokemon = fightFloor_GetFightOutPokemonPtrAry(floor, i);
        if (pokemon == nullptr || !fightOutPokemonCheckFightOut(pokemon)) continue;
        FightActionBuff* action = fightOutPokemon_GetFightActionBuffPtr(pokemon);
        if (action == nullptr || !fightActionCheckValid(action)) continue;
        if (static_cast<u8>(fightOutPokemon_GetFightActionFlag(pokemon)) == 0) { last = 0; break; }
    }
    return last;
}
void fightFloorReplaceFightOutPokemonAttackToDefense(FIGHT_FLOOR* floor) {
    void* attack = fightTargetGetPtrAsNowFightType(0x11, floor);
    void* defense = fightTargetGetPtrAsNowFightType(0x12, floor);
    fightFloor_SetAttackPokemonPtr(floor, defense);
    fightFloor_SetDefPokemonAndAtkFightWazaTargetId(floor, attack);
}
u32 fightFloorGetFightOutBanmeToValidFightOutPokemon(FIGHT_FLOOR* floor, u16 index) {
    u16 trainer;
    u16 slot;
    u16 side;
    u32 trainers;
    u32 pokemonCount;
    u16 count;
    fightFloor_GetFightType(floor);
    trainers = fightFloor_GetFightTypeTrainerNum(floor);
    pokemonCount = fightFloor_GetFightTypeFightoutPokemonNum(floor);
    count = 0;
    for (slot = 0; slot < pokemonCount; slot++) {
        for (trainer = 0; trainer < trainers; trainer++) {
            for (side = 0; side < 2; side++) {
                FightOutPokemon* pokemon = _fightFloorLoopValidFightOutPokemonSub(floor, side, trainer, slot);
                if (pokemon != nullptr && count == index) return reinterpret_cast<u32>(pokemon);
                count++;
            }
        }
    }
    return 0;
}
s32 fightFloorGetEnemyFightSideManyDamageHpRate(FIGHT_FLOOR*, FightOutPokemon* pokemon) {
    FightOutPokemonEnemy* enemies;
    s32 maximum;
    FightOutPokemonEnemy* enemy;
    u32 hp;
    u16 i;
    if (pokemon == nullptr) return -1;
    enemies = fightOutPokemon_GetFightOutPokemonEnemyPtr(pokemon, 0);
    maximum = -1;
    for (i = 0; i < 4; i++) {
        enemy = &enemies[i];
        if (!fightOutPokemonEnemyCheckValid(enemy)) continue;
        FightOutPokemon* target = fightOutPokemonEnemyBiosGetTargetFightOutPokemonPtr(enemy);
        if (target == nullptr || !fightOutPokemonCheckValid(target)) continue;
        hp = fightOutPokemonEnemyBiosGetInitHp(enemy);
        u32 damage = fightOutPokemonEnemyBiosGetDamage(enemy);
        if (static_cast<u16>(hp) == 0) hp = 1;
        s32 rate = static_cast<u16>(damage) * 100 / static_cast<u16>(hp);
        if (rate > maximum) maximum = rate;
    }
    return maximum;
}
s32 fightFloorGetEnemyFightSideLittleNokoriHpRate(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    s32 minimum;
    u32 bound;
    u32 count;
    u32 hp;
    FightOutPokemon** array;
    u16 i;
    FightOutPokemon* target;
    u32 maxHp;
    if (pokemon == nullptr) return -1;
    FightOutPokemon* output[8];
    _fightFloorInitFightOutPokemonPtrAry(output);
    count = _fightFloorCreateFightOutPokemonPtrAry(floor, output, true, 2, pokemon);
    if (static_cast<u16>(count) == 0) return -1;
    for (i = 0; i < static_cast<u16>(count); i++) {
        target = output[i];
        if (target != nullptr) {
            hp = fightOutPokemonNowHpWaruValue(target, 1);
            maxHp = fightOutPokemonMaxHpWaruValue(target, 1);
            if (static_cast<u16>(maxHp) == 0) maxHp = 1;
            minimum = static_cast<u16>(hp) * 100 / static_cast<u16>(maxHp);
            break;
        }
    }
    array = output;
    bound = static_cast<u16>(count);
    for (i = 0; i < bound; i++) {
        target = array[i];
        if (target != nullptr) {
            hp = fightOutPokemonNowHpWaruValue(target, 1);
            maxHp = fightOutPokemonMaxHpWaruValue(target, 1);
            if (static_cast<u16>(maxHp) == 0) maxHp = 1;
            s32 rate = static_cast<u16>(hp) * 100 / static_cast<u16>(maxHp);
            if (rate < minimum) minimum = rate;
        }
    }
    return minimum;
}
FightOutPokemon* fightFloorGetFightOutPokemonPtrRandom(FIGHT_FLOOR* floor, bool fightOutOnly, u8 relation, FightOutPokemon* target) {
    FightOutPokemon* output[8];
    _fightFloorInitFightOutPokemonPtrAry(output);
    u32 count = _fightFloorCreateFightOutPokemonPtrAry(floor, output, fightOutOnly, relation, target);
    if (static_cast<u16>(count) == 0) return nullptr;
    u16 index = static_cast<u16>(HSD_Rand()) % static_cast<u16>(count);
    if (index >= 8) return nullptr;
    FightOutPokemon* pokemon = output[index];
    if (pokemon == nullptr) return nullptr;
    return pokemon;
}
}

extern "C" {
FightPokemon* fightTrainerSearchIrekaeFightPokemon(FightTrainer*, u16*);
u8 fightOutPokemonIsZokuseiDataId(FightOutPokemon*, u16);
u32 fightOutPokemonGetFightActionPri(FightOutPokemon*);
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR*, FightOutPokemon*, FightOutPokemon*, u8);
void fightFloor_SetfightoutPokemonPtrAryPtr(FIGHT_FLOOR*, FightOutPokemon**);
}
static u8 _fightFloorIsIrekaeFightOutPokemonSub(void* object, u16 type, void* context) {
    FightTrainer* trainer = static_cast<FightTrainer*>(object);
    u16 i;
    u32 count;
    u8* result = static_cast<u8*>(context);
    if (!fightTrainerCheckValid(trainer)) return 1;
    u16 index = 0;
    if (fightTrainerSearchIrekaeFightPokemon(trainer, &index) == nullptr) return 1;
    count = fightFloor_GetFightTypeFightoutPokemonNum(nullptr);
    for (i = 0; i < count; i++) {
        FightOutPokemon* pokemon = fightTrainer_GetFightoutPokemonPtr(trainer, i);
        if (pokemon == nullptr || fightOutPokemonCheckFightOut(pokemon)) continue;
        if (result != nullptr && *result != 2) {
            if (fightTrainerIsGcHero(trainer) == 1) *result = 2;
            else *result = 1;
        }
    }
    return 1;
}
extern "C" {
u8 fightFloorIsIrekaeFightOutPokemon(FIGHT_FLOOR* floor) {
    u8 result = 0;
    fightFloorLoopValidFightTrainer(floor, _fightFloorIsIrekaeFightOutPokemonSub, &result, 0);
    return result;
}
u8 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(FIGHT_FLOOR* floor, FightOutPokemon* pokemon, FightOutPokemon** blocker) {
    FightOutPokemon* magnet;
    FightOutPokemon* arena;
    FightOutPokemon* shadow;
    u8 airborne = 0;
    u8 steel = 0;
    if (!fightOutPokemonCheckValid(pokemon)) return 0;
    shadow = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x17, 0, 2, pokemon);
    arena = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x47, 0, 2, pokemon);
    magnet = fightFloorGetFightOutPokemonPtrAryPokemonTokuseiDataIdFirst(floor, 0x2a, 0, 0, pokemon);
    if (fightOutPokemonIsZokuseiDataId(pokemon, 2) == 1 || static_cast<u16>(fightOutPokemonGetTokuseiDataId(pokemon)) == 0x1a) airborne = 1;
    if (fightOutPokemonIsZokuseiDataId(pokemon, 8) == 1) steel = 1;
    if (fightOutPokemonIsJoutaiDataId(pokemon, 0x16) == 1 || fightOutPokemonIsJoutaiDataId(pokemon, 0xe) == 1 || fightOutPokemonIsJoutaiDataId(pokemon, 0x25) == 1) return 1;
    if (shadow != nullptr) {
        if (blocker != nullptr) *blocker = shadow;
        return 2;
    }
    if (arena != nullptr && airborne == 0) {
        if (blocker != nullptr) *blocker = arena;
        return 2;
    }
    if (magnet != nullptr && steel == 1) {
        if (blocker != nullptr) *blocker = magnet;
        return 2;
    }
    return 0;
}
u8 fightFloorSortFightOutPokemonDefault(FightOutPokemon* first, FightOutPokemon* second) {
    u8 order[4] = {0xc, 0xf, 0xd, 0x10};
    u8* orderPtr;
    u32 target;
    void* floor;
    u8 i;
    u8 firstIndex;
    u8 secondIndex;
    floor = fightTargetGetPtrAsNowFightType(0xb, nullptr);
    orderPtr = order;
    for (i = 0; i < 4; i++) {
        target = orderPtr[i];
        if (first == fightTargetGetPtrAsNowFightType(target, floor)) firstIndex = i;
        if (second == fightTargetGetPtrAsNowFightType(target, floor)) secondIndex = i;
    }
    return firstIndex > secondIndex;
}
void fightFloorSortFightOutPokemonPtrArySub(FIGHT_FLOOR* floor, FightOutPokemon** output, u16 count, u8 useActions) {
    u32 bound = count;
    s32 last = bound - 1;
    u16 i;
    u16 j;
    for (i = 0; static_cast<int>(i) < last; i++) {
        for (j = i + 1; static_cast<u32>(j) < bound; j++) {
            if (output[i] == nullptr && output[j] == nullptr) continue;
            if (output[i] == nullptr) {
                FightOutPokemon* temp = output[i];
                output[i] = output[j];
                output[j] = temp;
            } else if (output[j] != nullptr) {
                u32 firstPri;
                u32 secondPri;
                if (useActions == 0) { firstPri = 0; secondPri = 0; }
                else { firstPri = fightOutPokemonGetFightActionPri(output[i]); secondPri = fightOutPokemonGetFightActionPri(output[j]); }
                if (static_cast<s8>(firstPri) < static_cast<s8>(secondPri)) continue;
                if (static_cast<s8>(firstPri) > static_cast<s8>(secondPri)) {
                    FightOutPokemon* temp = output[i];
                    output[i] = output[j];
                    output[j] = temp;
                } else if ((static_cast<s8>(firstPri) == 2 && static_cast<s8>(secondPri) == 2) || (static_cast<s8>(firstPri) == 3 && static_cast<s8>(secondPri) == 3)) {
                    if (fightFloorSortFightOutPokemonDefault(output[i], output[j])) {
                        FightOutPokemon* temp = output[i];
                        output[i] = output[j];
                        output[j] = temp;
                    }
                } else if (!fightFloorCmpfightOutPokemonNimbleness(floor, output[i], output[j], useActions)) {
                    FightOutPokemon* temp = output[i];
                    output[i] = output[j];
                    output[j] = temp;
                }
            }
        }
    }
}
void fightFloorSortFightOutPokemonPtrAry(FIGHT_FLOOR* floor, u8 useActions) {
    FightOutPokemon* output[8];
    for (u16 i = 0; i < 8; i++) output[i] = fightFloor_GetFightOutPokemonPtrAry(floor, i);
    fightFloorSortFightOutPokemonPtrArySub(floor, output, 8, useActions);
    fightFloor_SetfightoutPokemonPtrAryPtr(floor, output);
}
FightOutPokemon* fightFloor_GetFightOutPokemonFromDefaultSortData(u8 index) {
    FightOutPokemon* output[8];
    fightTargetGetPtrAsNowFightType(0xb, nullptr);
    for (u16 i = 0; static_cast<int>(i) < 8; i++) output[i] = fightFloor_GetFightOutPokemonPtrAry(nullptr, i);
    for (u16 i = 0; static_cast<int>(i) < 7; i++) {
        for (u16 j = i + 1; static_cast<int>(j) < 8; j++) {
            if (output[i] == nullptr && output[j] == nullptr) continue;
            if (output[i] == nullptr) {
                FightOutPokemon* temp = output[i];
                output[i] = output[j];
                output[j] = temp;
            } else if (output[j] != nullptr && fightFloorSortFightOutPokemonDefault(output[i], output[j])) {
                FightOutPokemon* temp = output[i];
                output[i] = output[j];
                output[j] = temp;
            }
        }
    }
    return output[index];
}
}

struct Hero;
extern "C" {
FightPokemon* fightOutPokemon_GetMotoFightPokemonPtr(FightOutPokemon*);
FightPokemon* fightTrainer_GetFightPokemonPtr(FightTrainer*, u16);
Hero* fightTrainer_GetHeroPtr(FightTrainer*);
FightTrainer* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR*, FightPokemon*);
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR*, FightOutPokemon*);
Hero* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR*, FightOutPokemon*);
u32 fightFloor_GetFightKindDoBadgeCheckFlag(FIGHT_FLOOR*);
u32 fightFloor_GetFirstAttackRnd(FIGHT_FLOOR*);
u32 fightOutPokemonGetNowNimbleness(FightOutPokemon*, u32, u32, u32, Hero*);
u32 fightOutPokemonGetCmpNimblenessWazaDataId(FightOutPokemon*);
u32 wazaDB_GetPri(u32);

Hero* fightFloorGetFightOutPokemonPtrToHeroPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FightTrainer* trainer = fightFloorGetFightOutPokemonPtrToFightTrainerPtr(floor, pokemon);
    if (trainer == nullptr) return nullptr;
    Hero* hero = fightTrainer_GetHeroPtr(trainer);
    if (hero == nullptr) return nullptr;
    return hero;
}
FightTrainer* fightFloorGetFightOutPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightOutPokemon* pokemon) {
    FightPokemon* original = fightOutPokemon_GetMotoFightPokemonPtr(pokemon);
    if (original == nullptr) return nullptr;
    FightTrainer* trainer = fightFloorGetFightPokemonPtrToFightTrainerPtr(floor, original);
    if (trainer == nullptr) return nullptr;
    return trainer;
}
FightTrainer* fightFloorGetFightPokemonPtrToFightTrainerPtr(FIGHT_FLOOR* floor, FightPokemon* target) {
    FightSide* sidePtr;
    u16 trainer;
    u16 pokemon;
    u16 side;
    FightTrainer* trainerPtr;
    for (side = 0; side < 2; side++) {
        sidePtr = fightFloor_GetFightSidePtr(floor, side);
        if (sidePtr == nullptr) continue;
        for (trainer = 0; trainer < 2; trainer++) {
            trainerPtr = fightSide_GetFightTrainerPtr(sidePtr, trainer);
            if (trainerPtr == nullptr) continue;
            for (pokemon = 0; pokemon < 6; pokemon++) {
                FightPokemon* record = fightTrainer_GetFightPokemonPtr(trainerPtr, pokemon);
                if (record != nullptr && target == record) return trainerPtr;
            }
        }
    }
    return nullptr;
}
u8 fightFloorCmpfightOutPokemonNimbleness(FIGHT_FLOOR* floor, FightOutPokemon* first, FightOutPokemon* second, u8 useActions) {
    u32 weather;
    u32 badge;
    u32 firstSpeed;
    u32 random;
    u32 firstMove;
    u32 secondMove;
    u32 secondSpeed;
    u32 firstPri;
    u32 secondPri;
    if (first == nullptr || second == nullptr) return 1;
    weather = fightFloorGetNowTenkouDataId(floor, 1);
    badge = fightFloor_GetFightKindDoBadgeCheckFlag(floor);
    random = fightFloor_GetFirstAttackRnd(floor);
    Hero* hero = fightFloorGetFightOutPokemonPtrToHeroPtr(floor, first);
    firstSpeed = fightOutPokemonGetNowNimbleness(first, badge, weather, random, hero);
    hero = fightFloorGetFightOutPokemonPtrToHeroPtr(floor, second);
    secondSpeed = fightOutPokemonGetNowNimbleness(second, badge, weather, random, hero);
    if (useActions == 0) { firstMove = 0; secondMove = 0; }
    else {
        firstMove = fightOutPokemonGetCmpNimblenessWazaDataId(first);
        secondMove = fightOutPokemonGetCmpNimblenessWazaDataId(second);
    }
    firstPri = wazaDB_GetPri(firstMove);
    secondPri = wazaDB_GetPri(secondMove);
    if (static_cast<s8>(firstPri) != 0 || static_cast<s8>(secondPri) != 0) {
        if (static_cast<s8>(firstPri) > static_cast<s8>(secondPri)) return 1;
        if (static_cast<s8>(firstPri) < static_cast<s8>(secondPri)) return 0;
    }
    if (firstSpeed > secondSpeed) return 1;
    if (firstSpeed < secondSpeed) return 0;
    if (HSD_Rand() & 1) return 1;
    return 0;
}
}

struct GSThread;
extern "C" {
u32 fightTrainer_GetFightTrainerDataId(FightTrainer*);
u32 fightTrainerDB_GetAiDataId(u32);
u32 fightTrainer_GetControllerId(FightTrainer*);
u32 GSfloorGetCurrentFloorGroupID();
GSThread* GSthreadCreate(u32, u32, u32, u32, u32, FightFloorCallback);
void GSthreadSetArgs(GSThread*, u32, ...);
void GSthreadSetName(GSThread*, const char*);
void GSthreadSwitch();
u8 GSthreadIsRunning(GSThread*);
void GSthreadClose(GSThread*);
void fightFloorLoopValidFightTrainer(FIGHT_FLOOR* floor, FightFloorCallback callback, void* context, u8 concurrent) {
    u32 trainers;
    u16 type;
    type = static_cast<u8>(fightFloor_GetFightType(nullptr));
    trainers = fightFloor_GetFightTypeTrainerNum(nullptr);
    GSThread* threads[4];
    for (u16 i = 0; i < 4; i++) threads[i] = nullptr;
    if (concurrent == 1) {
        u16 threadType = type;
        u16 side;
        FightSide* sidePtr;
        u16 trainer;
        u16 count = 0;
        FightTrainer* record;
        u32 ai;
        for (side = 0; side < 2; side++) {
            sidePtr = fightFloorGetValidFightSidePtr(floor, side);
            if (sidePtr == nullptr) continue;
            for (trainer = 0; trainer < trainers; trainer++) {
                record = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (record == nullptr) continue;
                ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(record));
                fightTrainer_GetControllerId(record);
                if (static_cast<u16>(ai) != 0 || count >= 4) continue;
                threads[count] = GSthreadCreate(0x12, GSfloorGetCurrentFloorGroupID(), 0x2000, 1, 0, callback);
                if (threads != nullptr) {
                    GSthreadSetArgs(threads[count], 3, record, threadType, context);
                    GSthreadSetName(threads[count], "fightInput");
                    count++;
                }
            }
        }
        u16 i;
        do {
            GSthreadSwitch();
            if (static_cast<u16>(fightGetFightResultId()) == 4 || static_cast<u16>(fightGetFightResultId()) == 5) return;
            for (i = 0; i < 4; i++) {
                if (threads[i] != nullptr && GSthreadIsRunning(threads[i]) == 1) break;
            }
        } while (i < 4);
        for (i = 0; i < 4; i++) {
            if (threads[i] != nullptr) {
                GSthreadClose(threads[i]);
                threads[i] = nullptr;
            }
        }
    } else {
        for (u16 side = 0; side < 2; side++) {
            FightSide* sidePtr = fightFloorGetValidFightSidePtr(floor, side);
            if (sidePtr == nullptr) continue;
            for (u16 trainer = 0; trainer < trainers; trainer++) {
                FightTrainer* record = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
                if (record == nullptr) continue;
                u32 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(record));
                fightTrainer_GetControllerId(record);
                if (static_cast<u16>(ai) == 0) callback(record, type, context);
            }
        }
    }
    for (u16 side = 0; side < 2; side++) {
        FightSide* sidePtr = fightFloorGetValidFightSidePtr(floor, side);
        if (sidePtr == nullptr) continue;
        for (u16 trainer = 0; trainer < trainers; trainer++) {
            FightTrainer* record = fightSideGetValidFightTrainerPtr(sidePtr, trainer);
            if (record == nullptr) continue;
            u32 ai = fightTrainerDB_GetAiDataId(fightTrainer_GetFightTrainerDataId(record));
            fightTrainer_GetControllerId(record);
            if (static_cast<u16>(ai) != 0) callback(record, type, context);
        }
    }
}
}

extern "C" u32 fightFloorCreateFightOutPokemonPtrAry(FIGHT_FLOOR* floor) {
    fightFloorInitFightOutPokemonPtrAry(floor);
    FightOutPokemon** output = fightFloor_GetFightOutPokemonPtrAryPtr(floor);
    if (output == nullptr) return 0;
    return _fightFloorCreateFightOutPokemonPtrAry(floor, output, false, 0, nullptr);
}
