#ifndef GAME_PXDVS_APP_FIGHT_FIGHT_ENCOUNT_BIOS_LAYOUT_HPP
#define GAME_PXDVS_APP_FIGHT_FIGHT_ENCOUNT_BIOS_LAYOUT_HPP
#include <libc/stddef.h>
#include <dolphin/types.h>
struct FightTrainerInfoRecord { u32 trainerData; u32 inputDevice; };
struct FightEncountRecord {
    u8 kind, trainer, pokemon, entry;
    u8 zenmetu;
    u8 pad05;
    u16 floorDataId;
    u16 diskId;
    u8 pad0a[2];
    u32 fightName;
    u32 bgmSndId;
    u32 wipeId;
    u32 syoukaiWzxDataId;
    FightTrainerInfoRecord trainerInfo[4];
};
struct FightEncountWipeRecord {
    u8 snapshotUse;
    u8 pad01;
    u16 effectSndId;
    f32 effectTime;
    u32 function;
};
struct FightTypeRecord { u8 trainerCount; };
struct FightDeckRecord { u8 pad00[2]; u8 pokemonCount; u8 pad03[5]; u32 entryPokemonId; u32 fightoutPokemonId; };
typedef char FightLayoutAssert_diskId[(offsetof(FightEncountRecord, diskId)==8) ? 1 : -1];
typedef char FightLayoutAssert_fightName[(offsetof(FightEncountRecord, fightName)==0x0c) ? 1 : -1];
typedef char FightLayoutAssert_bgmSndId[(offsetof(FightEncountRecord, bgmSndId)==0x10) ? 1 : -1];
typedef char FightLayoutAssert_wipeId[(offsetof(FightEncountRecord, wipeId)==0x14) ? 1 : -1];
typedef char FightLayoutAssert_syoukaiWzxDataId[(offsetof(FightEncountRecord, syoukaiWzxDataId)==0x18) ? 1 : -1];
typedef char FightLayoutAssert_trainerInfo[(offsetof(FightEncountRecord, trainerInfo)==0x1c) ? 1 : -1];
typedef char FightLayoutAssert_FightEncountRecord_size[(sizeof(FightEncountRecord)==0x3c) ? 1 : -1];
typedef char FightLayoutAssert_effectSndId[(offsetof(FightEncountWipeRecord, effectSndId)==2) ? 1 : -1];
typedef char FightLayoutAssert_effectTime[(offsetof(FightEncountWipeRecord, effectTime)==4) ? 1 : -1];
typedef char FightLayoutAssert_function[(offsetof(FightEncountWipeRecord, function)==8) ? 1 : -1];
typedef char FightLayoutAssert_FightEncountWipeRecord_size[(sizeof(FightEncountWipeRecord)==0x0c) ? 1 : -1];
typedef char FightLayoutAssert_trainer_size[(sizeof(FightTrainerInfoRecord)==8) ? 1 : -1];
typedef char FightLayoutAssert_inputDevice[(offsetof(FightTrainerInfoRecord,inputDevice)==4) ? 1 : -1];
typedef char FightLayoutAssert_entryPokemonId[(offsetof(FightDeckRecord,entryPokemonId)==8) ? 1 : -1];
typedef char FightLayoutAssert_fightoutPokemonId[(offsetof(FightDeckRecord,fightoutPokemonId)==12) ? 1 : -1];
#endif
