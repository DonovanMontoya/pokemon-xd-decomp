#ifndef FIGHT_WAZA_BIOS_LAYOUT_HPP
#define FIGHT_WAZA_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/waza/wazaLayout.hpp>
struct FightWazaHitKakurituBiosRecord { u8 kake; u8 waru; };
struct FightWazaCriticalBiosRecord { u8 bunbo; };
typedef char FightWazaHitKakurituBiosRecordSize[sizeof(FightWazaHitKakurituBiosRecord)==2?1:-1];
typedef char FightWazaCriticalBiosRecordSize[sizeof(FightWazaCriticalBiosRecord)==1?1:-1];
#endif
