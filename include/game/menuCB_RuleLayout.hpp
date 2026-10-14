#ifndef GAME_MENUCB_RULE_LAYOUT_HPP
#define GAME_MENUCB_RULE_LAYOUT_HPP
#include <dolphin/types.h>

typedef struct Pokemon { u8 data[0xC8]; } Pokemon;
typedef struct Hero Hero;

// One byte of per-pokemon error flags (most significant bit first).
typedef struct MenuCBRuleFlags0 {
    u8 legend : 1;
    u8 sameAt : 1;
    u8 levelMin : 1;
    u8 levelMax : 1;
    u8 errDark : 1;
    u8 errTamago : 1;
    u8 errWaza : 1;
    u8 errStatus : 1;
} MenuCBRuleFlags0;
typedef struct MenuCBRuleFlags1 {
    u8 item1 : 1;
    u8 item2 : 1;
    u8 itemAt : 1;
    u8 errItem : 1;
    u8 trainerLevel : 1;
    u8 trainerCount : 1;
    u8 errValid : 1;
    u8 unk0 : 1;
} MenuCBRuleFlags1;
typedef struct MenuCBRuleFlagEntry {
    MenuCBRuleFlags0 f0;
    MenuCBRuleFlags1 f1;
    u8 reserved2[2];
} MenuCBRuleFlagEntry;

typedef struct MenuCBRule {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s32 unk8;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    s16 unk14;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    s16 unk1A;
    s16 unk1C;
    u16 name[21];
    u8 unk48[8];
    u16 unk50;
    u8 itemFlags[60];
    u16 unk8E;
} MenuCBRule;

typedef struct MenuCBRuleState {
    u8 reserved0[0x8];
    s32 unk8;
    s32 unkC;
    u8 reserved10[0x9918 - 0x10];
    MenuCBRule rules[6];
    u8 reserved9C78[0xC];
    MenuCBRuleFlagEntry flags[4][6];
} MenuCBRuleState;

extern MenuCBRuleState _CB;
extern u16 itemtoolbattle[];
extern u32 itemtoolbattle_number;
extern u32 *legendPokemonData_number;
extern u16 *legendPokemonData;

#endif
