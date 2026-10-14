#ifndef FIGHT_KIND_BIOS_LAYOUT_HPP
#define FIGHT_KIND_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
typedef struct FightKindBiosLayout {
    u8 backSaveDataFlag;
    u8 doBadgeCheckFlag;
    u8 doZukanMitaFlag;
    u8 doZukanTukamaetaFlag;
    u8 useItemFlag;
    u8 callFlag;
    u8 nigeruFlag;
    u8 drawFlag;
    u8 getExpFlag;
    u8 getOkaneFlag;
    u8 okanePoolFlag;
    u8 getNekoniKobanFlag;
    u8 getFriendFlag;
    u8 getInfectPokerusFlag;
    u8 doCriticalAttackFlag;
    u8 doHizukiAiFlag;
    u8 doHizukiMiyaburiFlag;
    u8 doItemSoubiTokukoutokubouupFlag;
    u8 keikentihueruFlag;
    u8 bossFlag;
    u8 dorobouFlag;
    u8 monohiroiFlag;
    u8 darkpokemonHypermodeFlag;
    u8 pokemonStatusMenuSubbarFlag;
    u8 hostEnemyMsgFlag;
    u8 regulationFlag;
    u8 reserved1a[2];
    u32 name;
} FightKindBiosLayout;
typedef char FightKindBiosSize[(sizeof(FightKindBiosLayout)==0x20)?1:-1];
typedef char FightKindBiosNameOffset[(offsetof(FightKindBiosLayout,name)==0x1c)?1:-1];
#endif
