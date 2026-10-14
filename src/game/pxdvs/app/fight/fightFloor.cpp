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
u32 fightFloor_GetFightType(FIGHT_FLOOR*);
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
u16 fightFloorCheckFightOutPokemonPtrAryPokemonTokuseiDataId(FIGHT_FLOOR*, u16, u8, u8);
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
    u8 type = fightFloor_GetFightType(floor);
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
u32 fightFloorSetStatus(FIGHT_FLOOR*, u16, u16, u16, u32);
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
