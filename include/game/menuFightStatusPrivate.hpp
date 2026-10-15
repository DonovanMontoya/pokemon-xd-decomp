#ifndef MENU_FIGHT_STATUS_PRIVATE_HPP
#define MENU_FIGHT_STATUS_PRIVATE_HPP
#include <dolphin/types.h>
struct tagSPRITE_WORK {
    tagSPRITE_WORK *next;
    u8 type;
    u8 flags;
    s16 id;
    u32 texture;
    u8 sequence[0x3C];
    u32 callback;
    u32 message;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 resource;
    s16 sourceX;
    s16 sourceY;
    s16 sourceWidth;
    s16 sourceHeight;
    union {
        u32 value;
        struct {
            u8 red;
            u8 green;
            u8 blue;
            u8 alpha;
        } channels;
    } color;
    f32 scaleX;
    f32 scaleY;
    u8 reserved70[4];
    u8 drawType;
    u8 blendType;
    u8 mode;
    u8 reserved77;
};

struct tagWINDOW_WORK {
    u8 flags;
    s8 phase;
    s8 step;
    u8 reserved3;
    s32 menu;
    u8 reserved8;
    s8 priority;
    u8 closing;
    u8 port;
    tagWINDOW_WORK *parent;
    tagWINDOW_WORK *next;
    tagWINDOW_WORK *previous;
    u8 inactive;
    u8 itemCount;
    u8 kind;
    u8 openFlags;
    s32 layer;
    u8 drawKind;
    u8 reserved21[3];
    tagSPRITE_WORK *items;
    tagSPRITE_WORK *cursor;
    u8 reserved2C[0x3C];
    u32 parameters[8];
    s32 value;
    s16 x;
    s16 y;
    s16 frame;
    u8 reserved92;
    u8 alpha;
    f32 scaleX;
    f32 scaleY;
    s16 first;
    s16 selected;
    u8 reservedA0[4];
    u8 finished;
    u8 cancelled;
    u8 reservedA6[2];
    u8 freeWork[0x10];
    void *allocation;
};

class DarkPokemon {public:u16 getDarkPokemonID()const;};
class Pokemon {public:u8 isDarkPokemon()const;DarkPokemon *getDarkPokemon();};
class DeckDarkPokemon {public:u8 getPlayerLevel()const;};
#endif
