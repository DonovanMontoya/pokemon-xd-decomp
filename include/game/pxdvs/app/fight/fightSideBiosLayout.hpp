#ifndef FIGHT_SIDE_BIOS_LAYOUT_HPP
#define FIGHT_SIDE_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct FightSideDataBiosRecord {
    u16 yrot;
    u16 reserved02;
    u32 trainerStatusMenuDataId[2];
    u32 fightoutPokemonStatusMenuDataId[2];
};
struct FightSideBiosObject {
    u8 reserved00[0x64];
    u8 fightTrainer[2][0x3744];
    u8 makibisiCheckFlag;
};
typedef char FightLayoutAssert_yrot[(offsetof(FightSideDataBiosRecord, yrot)==0) ? 1 : -1];
typedef char FightLayoutAssert_trainer_status[(offsetof(FightSideDataBiosRecord, trainerStatusMenuDataId)==4) ? 1 : -1];
typedef char FightLayoutAssert_fightout_status[(offsetof(FightSideDataBiosRecord, fightoutPokemonStatusMenuDataId)==0xc) ? 1 : -1];
typedef char FightLayoutAssert_side_data_size[(sizeof(FightSideDataBiosRecord)==0x14) ? 1 : -1];
typedef char FightLayoutAssert_makibisi_flag[(offsetof(FightSideBiosObject, makibisiCheckFlag)==0x6eec) ? 1 : -1];
typedef char FightLayoutAssert_fight_trainer[(offsetof(FightSideBiosObject, fightTrainer)==0x64) ? 1 : -1];
typedef char FightLayoutAssert_fight_trainer_stride[(sizeof(((FightSideBiosObject*)0)->fightTrainer[0])==0x3744) ? 1 : -1];
#endif
