#ifndef GAME_MENUPOKEMONCHANGE_LAYOUT_HPP
#define GAME_MENUPOKEMONCHANGE_LAYOUT_HPP
#ifndef _DOLPHIN_TYPES_H_
#define _DOLPHIN_TYPES_H_
typedef signed char s8;
typedef unsigned char u8;
typedef signed short int s16;
typedef unsigned short int u16;
typedef signed long s32;
typedef unsigned long u32;
typedef float f32;
typedef double f64;
#endif

struct tagSPRITE_WORK {
    u8 pad0[6];
    s16 id;
    u8 pad8[0x58];
};

struct tagWINDOW_WORK {
    u8 pad0[0x4];
    s32 menu;
};

class Pokemon {
public:
    u16 getHp() const;
};

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_TYPE_0
};

class Hero {
public:
    Pokemon *getPokemon(long);
};

#endif
