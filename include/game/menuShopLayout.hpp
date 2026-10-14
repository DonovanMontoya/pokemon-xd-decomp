#ifndef GAME_MENUSHOP_LAYOUT_HPP
#define GAME_MENUSHOP_LAYOUT_HPP
#include <dolphin/types.h>

// Partial views of the menu window/sprite work areas shared by the shop and pocket menus.
// Every named field is tied to an original load/store width.
typedef struct ShopWindow {
    u8 reserved0;
    s8 phase;
    s8 step;
    u8 reserved3;
    s32 menu;
    u8 reserved8[0x14];
    s32 layer;
    u8 reserved20[0x48];
    void *arg;
    u8 reserved6C[0x30];
    s16 first;
    s16 selected;
    u8 reservedA0[4];
    u8 unkA4;
    u8 unkA5;
    u8 unkA6;
    u8 unkA7;
} ShopWindow;

typedef struct ShopSprite {
    u8 reserved0[6];
    s16 id;
    u8 reserved8[0x4A];
    s16 unk52;
    s16 width;
    s16 height;
    u8 reserved58[0xF];
    u8 alpha;
} ShopSprite;

#endif
