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
    u8 pad8[0x44];
    u32 message;
    u8 pad50[0x10];
};

struct tagWINDOW_WORK {
    u8 flags;
    s8 phase;
    s8 step;
    u8 pad3;
    s32 menu;
    u8 pad8[0x84];
    s16 x;
    u8 pad8E[5];
    u8 alpha;
};

enum darkPokemonWhere { DARK_POKEMON_WHERE_0 };

class DarkPokemon {
public:
    void setPlace(darkPokemonWhere, u8);
};

class Pokemon {
public:
    u8 reserved[0xC4];
    DarkPokemon *getDarkPokemon();
    u16 getHp() const;
    u16 getItemDataId() const;
    bool isDarkPokemon() const;
};

class CState {
public:
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 frames;
    f32 time;
    f32 lastFrame;
    u8 saved[0x40];
    u8 saved2[0x40];
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    u8 reservedA4[4];
    void init();
};

struct MENU_MODEL {
    u8 data[0xEC];
    MENU_MODEL();
};

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_TYPE_0,
    MENU_POKEMON_CB_TYPE_1,
    MENU_POKEMON_CB_TYPE_2
};

class Hero {
public:
    Pokemon *getPokemon(long);
    static Hero *getHeroPtr();
};

#endif
