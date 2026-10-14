#ifndef FIGHT_JOUKEN_BIOS_LAYOUT_HPP
#define FIGHT_JOUKEN_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct FightJoukenLinkBiosRecord { u8 joint; u8 pad01; u16 joukenDataId; u16 nextLinkDataId; };
struct FightJoukenValueBiosRecord { u8 kind; u8 hoseiFlag; s16 kake; s16 waru; u16 target; u16 buff; };
struct FightJoukenBiosRecord { u8 form; u8 pad01; u16 link; FightJoukenValueBiosRecord value[2]; };
typedef char FightLayoutAssert_jouken_link_size[(sizeof(FightJoukenLinkBiosRecord)==6) ? 1 : -1];
typedef char FightLayoutAssert_joint[(offsetof(FightJoukenLinkBiosRecord, joint)==0) ? 1 : -1];
typedef char FightLayoutAssert_jouken_id[(offsetof(FightJoukenLinkBiosRecord, joukenDataId)==2) ? 1 : -1];
typedef char FightLayoutAssert_next_link[(offsetof(FightJoukenLinkBiosRecord, nextLinkDataId)==4) ? 1 : -1];
typedef char FightLayoutAssert_jouken_value_size[(sizeof(FightJoukenValueBiosRecord)==0xa) ? 1 : -1];
typedef char FightLayoutAssert_form[(offsetof(FightJoukenBiosRecord, form)==0) ? 1 : -1];
typedef char FightLayoutAssert_link[(offsetof(FightJoukenBiosRecord, link)==2) ? 1 : -1];
typedef char FightLayoutAssert_value[(offsetof(FightJoukenBiosRecord, value)==4) ? 1 : -1];
typedef char FightLayoutAssert_jouken_size[(sizeof(FightJoukenBiosRecord)==0x18) ? 1 : -1];
#endif
