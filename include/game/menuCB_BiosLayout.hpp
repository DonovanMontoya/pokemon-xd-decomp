#ifndef GAME_MENUCB_BIOS_LAYOUT_HPP
#define GAME_MENUCB_BIOS_LAYOUT_HPP
#include <dolphin/types.h>

typedef struct Hero {
    u8 data[0x978];
} Hero;
typedef struct Pokemon Pokemon;

typedef struct MenuCBBiosRule {
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
} MenuCBBiosRule;

typedef struct MenuCBBiosTrainer {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    u8 reserved8[0x1C];
    s32 unk24;
    s32 unk28;
    Hero hero;
    Hero heroCopy;
    u8 reserved131C[4];
} MenuCBBiosTrainer;

typedef struct _MENUCBWORK {
    u8 reserved0[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 reserved10[4];
    s32 unk14;
    MenuCBBiosTrainer trainers[4];
    MenuCBBiosTrainer orgTrainers[4];
    MenuCBBiosRule rules[6];
    u8 reserved9C78[0xB0E0 - 0x9C78];
    s32 unkB0E0;
    u8 reservedB0E4[0xB5F4 - 0xB0E4];
} _MENUCBWORK;

typedef struct _TOOL_SAVEDATA {
    MenuCBBiosRule rules[6];
    s8 unk360;
    u8 reserved361[3];
} _TOOL_SAVEDATA;

extern _MENUCBWORK _CB;
extern _MENUCBWORK *pGCB;
#endif
