#ifndef GAME_MENUPOCKET_LAYOUT_HPP
#define GAME_MENUPOCKET_LAYOUT_HPP
#include <dolphin/types.h>
#include <game/menuPocketToolLayout.hpp>

// Partial views of the pocket menu work data; every named member is tied to an
// original load/store width.
struct CURSOR {
    s16 first;
    s16 selected;
};

struct SActionMenuItem {
    u32 msg;
    int (*func)(int, int, int *);
    u16 flags;
    u16 reserved;
};

enum GSgfxLayerID { GSGFX_LAYER_ID_DUMMY };

struct PocketTab {
    u8 kind;
    u8 irekae;
    u8 sortable;
    u8 reserved3;
    s32 unk4;
    s32 unk8;
    void (*print)(GSgfxLayerID, int, int, int, int);
    u16 cursorId;
    u8 reserved12[2];
    u32 unk14;
    const SActionMenuItem *field;
    const SActionMenuItem *battle;
};

class Hero {
public:
    void itemSort(u8);
};

struct PocketData {
    u8 floorPop;
    u8 reserved1[3];
    s32 mode;
    s32 fightId;
    Hero *hero;
    s32 pokemonSlot;
    s32 pokemonSlot2;
    f32 tabScroll;
    f32 curPos;
    u8 isScroll;
    u8 reserved21[3];
    f32 rollTime;
    u32 msg;
    s32 result;
    s32 shop;
    s32 num;
    s32 swapIndex;
    u8 selecting;
    u8 reserved3D[3];
    s32 tab;
    s32 lastSlot;
    f32 anim;
    u8 resizeInit;
    u8 reserved4D[3];
};

#endif
