#ifndef GAME_MENUPOKEMON_LAYOUT_HPP
#define GAME_MENUPOKEMON_LAYOUT_HPP
#include <dolphin/types.h>

struct Pokemon;
struct Hero;
struct FIGHT_TRAINER;

struct MENU_POKEMON_WORK {
    u8 unk0;
    bool unk1;
    u8 unk2;
    u8 unk3;
    s8 unk4;
    s8 unk5;
    u8 unk6;
    s8 unk7;
    s8 unk8;
    u8 reserved9[3];
    s32 unkC;
    FIGHT_TRAINER *unk10;
    u8 unk14;
    u8 unk15;
    u16 unk16;
    u8 unk18;
    u8 unk19;
    u8 reserved1A[2];
    void *unk1C;
    s32 unk20;
    u8 unk24;
    u8 reserved25[3];
};

struct MENU_POKEMON_STATUS_TBL {
    u16 unk0;
    u8 reserved2[0x18];
    s16 unk1A;
    u8 reserved1C[8];
    u16 unk24;
    u8 reserved26[0xA];
};

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 unk1;
    s8 unk2;
    u8 reserved3;
    s32 unk4;
    u8 reserved8[0x8B];
    u8 unk93;
    u8 reserved94[0xA];
    s16 unk9E;
    u8 reservedA0[2];
    s16 unkA2;
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 unk6;
    u8 reserved8[0x5C];
    s32 unk64;
};

#endif
