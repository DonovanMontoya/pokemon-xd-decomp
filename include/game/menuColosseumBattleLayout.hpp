#ifndef GAME_MENUCOLOSSEUMBATTLE_LAYOUT_HPP
#define GAME_MENUCOLOSSEUMBATTLE_LAYOUT_HPP
#include <dolphin/types.h>

struct Pokemon {
    u8 data[0xC8];
};

struct Hero {
    u8 data[0x978];
};

struct CBRule {
    u8 reserved0[0x1E];
    u16 name[21];               // 0x1E
    u8 reserved48[0x90 - 0x48];
};

struct _MENUCBTRAINER {
    u8 reserved0[4];
    s32 unk4;                   // 0x04
    u8 reserved8[0x20];
    s32 unk28;                  // 0x28
    u8 reserved2C[0x1320 - 0x2C];
    _MENUCBTRAINER();
};

struct _MENUCBWORK {
    u8 reserved0[4];
    s32 mode;                   // 0x04
    s32 unk8;                   // 0x08
    s32 unkC;                   // 0x0C
    s32 unk10;                  // 0x10
    s32 unk14;                  // 0x14
    _MENUCBTRAINER trainers[4];     // 0x18
    _MENUCBTRAINER orgTrainers[4];  // 0x4C98
    CBRule rules[6];            // 0x9918
    CBRule* unk9C78;            // 0x9C78
    u8 reserved9C7C[4];
    s32 unk9C80;                // 0x9C80
    u8 reserved9C84[0xA65C - 0x9C84];
    Hero gcHero;                // 0xA65C
    s32 w[128];                 // 0xAFD4 (menu result / state words)
    u8 reservedB1D4[0xB4A0 - 0xB1D4];
    s8 unkB4A0;                 // 0xB4A0
    s8 unkB4A1;                 // 0xB4A1
    u8 reservedB4A2[0xB524 - 0xB4A2];
    Pokemon* dancers[9][4];     // 0xB524
    u8 reservedB5B4[0xB5F8 - 0xB5B4];
};

// Word at byte offset `off` of the _CB state words.
#define CBW(off) (_CB.w[((off) - 0xAFD4) / 4])

extern _MENUCBWORK _CB;

#endif
