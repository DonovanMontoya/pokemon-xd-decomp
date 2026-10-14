#ifndef MENU_PDA_DP_MONITOR_LAYOUT_HPP
#define MENU_PDA_DP_MONITOR_LAYOUT_HPP
#include <dolphin/types.h>
typedef struct DpmCursor {
    s16 first, selected;
} DpmCursor;
typedef struct DpmContents {
    DpmCursor *cursor;
} DpmContents;
typedef struct DpmPokemon {
    u8 data[0xc4];
} DpmPokemon;
typedef struct DpmModel {
    u8 data[0xec];
} DpmModel;
typedef struct DpmWork {
    u32 rnd;
    DpmPokemon pokemon;
    DpmModel model;
} DpmWork;
typedef struct DpmWindow {
    u8 reserved0;
    s8 phase, step;
    u8 reserved3;
    s32 menu;
    u8 reserved8[0x14];
    s32 layer;
    u8 reserved20[0x48];
    DpmContents *content;
    u8 reserved6C[0x27];
    u8 alpha;
    u8 reserved94[0x10];
    u8 accepted, cancelled;
} DpmWindow;
typedef struct DpmSprite {
    u8 reserved0[4];
    u8 flags;
    u8 reserved5;
    s16 id;
    u8 reserved8[0x4c];
    s16 width, height;
} DpmSprite;
typedef struct DpmItem {
    u8 reserved0[6];
    s16 x, y, width, height;
} DpmItem;
typedef struct DpmKey {
    u32 reserved0;
    u16 triggers;
} DpmKey;
typedef struct DpmDarkPokemon DpmDarkPokemon;
typedef struct DpmTexture {
    u8 reserved0[7];
    u8 dirty;
} DpmTexture;
typedef struct DpmLayer {
    u8 reserved0[0x173c];
    u32 dirtyA;
    DpmTexture *textureA;
    u8 reserved1744[0xb0];
    u32 dirtyB;
    DpmTexture *textureB;
    u8 reserved17FC[0x19c];
    u32 primitive;
} DpmLayer;
typedef union DpmFifo {
    u8 byte;
    u16 shortValue;
    f32 floatValue;
} DpmFifo;
typedef char DpmWorkSize[(sizeof(DpmWork) == 0x1b4) ? 1 : -1];
typedef char DpmModelOffset[((u32) & ((DpmWork *)0)->model == 0xc8) ? 1 : -1];
typedef char DpmWindowContentOffset[((u32) & ((DpmWindow *)0)->content == 0x68) ? 1 : -1];
typedef char DpmWindowAlphaOffset[((u32) & ((DpmWindow *)0)->alpha == 0x93) ? 1 : -1];
typedef char DpmLayerPrimitiveOffset[((u32) & ((DpmLayer *)0)->primitive == 0x1998) ? 1 : -1];
#endif
