#ifndef MENU_PDA_MAIL_LIST_LAYOUT_HPP
#define MENU_PDA_MAIL_LIST_LAYOUT_HPP
#include <dolphin/types.h>
typedef union PdaMailCursor {
    struct {
        s16 first, selected;
    } pos;
    u32 packed;
} PdaMailCursor;
typedef struct PdaMailWork {
    PdaMailCursor cursor;
    f32 x, y, targetX, targetY;
    s32 state, visible;
} PdaMailWork;
typedef struct PdaMailWindow {
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
    u8 reservedA6[2];
} PdaMailWindow;
typedef struct PdaMailSprite {
    u8 reserved0[6];
    s16 id;
    u8 reserved8[0x4c];
    s16 width;
    u8 reserved56[0xe];
    u8 red, green, blue, alpha;
} PdaMailSprite;
typedef struct PdaMailItem {
    u8 reserved0[6];
    s16 x, y, width, height;
} PdaMailItem;
typedef struct PdaMailKey {
    u32 reserved0;
    u16 triggers;
} PdaMailKey;
typedef char PdaMailCursorSize[(sizeof(PdaMailCursor) == 4) ? 1 : -1];
typedef char PdaMailWorkSize[(sizeof(PdaMailWork) == 0x1c) ? 1 : -1];
typedef char PdaMailWindowSelectedOffset[((u32) & ((PdaMailWindow *)0)->selected == 0x9e) ? 1 : -1];
typedef char PdaMailSpriteAlphaOffset[((u32) & ((PdaMailSprite *)0)->alpha == 0x67) ? 1 : -1];
#endif
