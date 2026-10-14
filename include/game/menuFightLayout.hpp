#ifndef GAME_MENUFIGHT_LAYOUT_HPP
#define GAME_MENUFIGHT_LAYOUT_HPP
#include <dolphin/types.h>

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 unk1;
    s8 unk2;
    u8 reserved3;
    s32 unk4;
    u8 reserved8[0x60];
    void* unk68;
    u8 reserved6C[0x1C];
    s32 unk88;
    u8 reserved8C[0x17];
    u8 unkA3;
    u8 unkA4;
    u8 unkA5;
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 unk6;
};

struct MenuFightKey {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

struct Pokemon;
struct FIGHT_TRAINER;

enum GSinputDevice { GSINPUT_DEVICE_0 };

#endif
