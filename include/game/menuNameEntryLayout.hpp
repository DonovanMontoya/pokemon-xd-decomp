#ifndef GAME_MENUNAMEENTRY_LAYOUT_HPP
#define GAME_MENUNAMEENTRY_LAYOUT_HPP
#include <dolphin/types.h>

struct NAME_ENTRY_ARG {
    u16 name[12];
    u16 *unk18;
    s32 unk1C;
    s32 unk20;
    s32 *unk24;
    s32 *unk28;
    s32 *unk2C;
    f32 *unk30;
    s32 *unk34;
    s32 *unk38;
    s32 *unk3C;
    s32 *unk40;
    s32 *unk44;
    s32 *unk48;
};

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 unk1;
    s8 unk2;
    u8 reserved3;
    s32 unk4;
    u8 reserved8[0x60];
    void *unk68;
    u8 reserved6C[0x27];
    u8 unk93;
    u8 reserved94[0xA];
    s16 unk9E;
    u8 reservedA0[4];
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 unk6;
    u8 reserved8[0x44];
    u32 unk4C;
    u8 reserved50[4];
    s16 unk54;
    s16 unk56;
    u8 reserved58[0xF];
    u8 unk67;
};

struct NAME_ENTRY_WORK {
    u16 name[12];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
};

#endif
