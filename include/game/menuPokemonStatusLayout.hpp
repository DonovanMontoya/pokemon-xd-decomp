#ifndef GAME_MENUPOKEMONSTATUS_LAYOUT_HPP
#define GAME_MENUPOKEMONSTATUS_LAYOUT_HPP
#include <dolphin/types.h>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_NONE,
    MENU_POKEMON_CB_PREV,
    MENU_POKEMON_CB_NEXT
};

struct Pokemon;
struct Hero;
struct FIGHT_TRAINER;

struct CURSOR {
    s16 first;
    s16 selected;
    CURSOR() {}
} __attribute__((aligned(4)));

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 phase;               // 0x01
    s8 step;                // 0x02
    u8 reserved3;
    s32 menu;               // 0x04
    u8 reserved8[0x8B];
    u8 alpha;               // 0x93
    u8 reserved94[8];
    CURSOR pos;             // 0x9C
    u8 reservedA0[2];
    s16 prevCursor;         // 0xA2
    u8 finished;            // 0xA4
    u8 cancelled;           // 0xA5
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 id;                 // 0x06
    u8 reserved8[0x4C];
    s16 x;                  // 0x54
    s16 y;                  // 0x56
};

// State of the status screen (static _menuStatus, 0x48 bytes).
struct RIBBON_WORK {
    s32 count;              // 0x00
    s8 slots[36];           // 0x04 (9 columns x 4 rows)
};

typedef Pokemon* (*MenuPokemonStatusCb)(Pokemon*, MENU_POKEMON_CB_TYPE, long);

struct MenuPokemonStatus {
    u8 flags;               // 0x00
    u8 mode;                // 0x01
    s8 page;                // 0x02
    s8 prevPage;            // 0x03
    s32 result;             // 0x04
    FIGHT_TRAINER* trainer; // 0x08
    Pokemon* pokemon;       // 0x0C
    MenuPokemonStatusCb callback; // 0x10
    long callbackArg;       // 0x14
    u16 wazaId;             // 0x18
    s8 unk1A;               // 0x1A
    u8 reserved1B;
    RIBBON_WORK ribbon;     // 0x1C
    u8 wazaNew[4];          // 0x44
    MenuPokemonStatus() {}
};

#endif
