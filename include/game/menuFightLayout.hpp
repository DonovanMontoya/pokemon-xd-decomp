#ifndef GAME_MENUFIGHT_LAYOUT_HPP
#define GAME_MENUFIGHT_LAYOUT_HPP
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
    u32 color;
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

struct MenuFightKey {
    u16 unk0;
    u16 unk2;
    u16 unk4;
};

class DarkPokemon {
public:
    bool isWazaNew(u8) const;
};

struct Pokemon {
    u8 reserved[0xC4];
    bool isDarkPokemon() const;
    DarkPokemon *getDarkPokemon();
};

struct MENU_WAZA_STATUS {
    u8 raw[0x44];
};

struct MenuCursor {
    s16 x;
    s16 y;
};

// 0x18-byte secret-target record: two menu ids at +4 and +0x10.
struct FightTargetSecret {
    u8 reserved0[4];
    s32 idA;
    u8 reserved8[8];
    s32 idB;
    u8 reserved14[4];
};

// 0xC-byte target record: menu id at +4, value at +8.
struct FightTargetEntry {
    u8 reserved0[4];
    s32 id;
    u16 value;
    u8 reservedA[2];
};
struct FIGHT_TRAINER;

enum GSinputDevice { GSINPUT_DEVICE_0, GSINPUT_DEVICE_1 };

#endif
