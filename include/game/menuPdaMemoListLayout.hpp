#ifndef MENU_PDA_MEMO_LIST_LAYOUT_HPP
#define MENU_PDA_MEMO_LIST_LAYOUT_HPP
#include <dolphin/types.h>
typedef union MemoCursor {
    struct {
        s16 first, selected;
    } pos;
    u32 packed;
} MemoCursor;
typedef struct MemoModel {
    u8 data[0xec];
} MemoModel;
typedef struct MemoPokemon {
    u8 data[0xc4];
} MemoPokemon;
typedef struct MemoWork {
    u8 reserved0[0x3c];
    u16 *ids;
    MemoPokemon *pokemon;
    MemoModel model;
    MemoModel hero;
    f32 alpha[8];
    u8 terminating, heroLoaded, heroMotion;
    u8 reserved23F;
    MemoCursor cursor;
    f32 x, y, targetX, targetY;
    s32 state, visible, sort;
    u32 thread;
} MemoWork;
typedef struct MemoWindow {
    u8 reserved0;
    s8 phase, step;
    u8 reserved3;
    s32 menu;
    u8 reserved8[0x14];
    s32 layer;
    u8 reserved20[0x73];
    u8 alpha;
    u8 reserved94[8];
    s16 first, selected;
    u8 reservedA0[4];
    u8 accepted, cancelled;
} MemoWindow;
typedef struct MemoSprite {
    u8 reserved0[6];
    s16 id;
    u8 reserved8[0x4c];
    s16 width, height;
    u8 reserved58[0xf];
    u8 alpha;
} MemoSprite;
typedef struct MemoItem {
    u8 reserved0[6];
    s16 x, y, width, height;
} MemoItem;
typedef struct MemoKey {
    u32 reserved0;
    u16 triggers;
} MemoKey;
typedef struct MemoSortBuff {
    u16 index, key;
    u16 name[12];
} MemoSortBuff;
typedef char MemoWorkSize[(sizeof(MemoWork) == 0x264) ? 1 : -1];
typedef char MemoModelOffset[((u32) & ((MemoWork *)0)->model == 0x44) ? 1 : -1];
typedef char MemoHeroOffset[((u32) & ((MemoWork *)0)->hero == 0x130) ? 1 : -1];
typedef char MemoAlphaOffset[((u32) & ((MemoWork *)0)->alpha == 0x21c) ? 1 : -1];
typedef char MemoCursorOffset[((u32) & ((MemoWork *)0)->cursor == 0x240) ? 1 : -1];
typedef char MemoThreadOffset[((u32) & ((MemoWork *)0)->thread == 0x260) ? 1 : -1];
typedef char MemoSortBuffSize[(sizeof(MemoSortBuff) == 0x1c) ? 1 : -1];
#endif
