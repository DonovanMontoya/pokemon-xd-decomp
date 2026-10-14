/* Debug menu window that displays the GS log. */
#include <global.h>

typedef struct DbgMenuKeyInfo {
    u8 unk0[4];
    u16 hold;
    u16 trigger;
} DbgMenuKeyInfo;

typedef struct DbgMenuWindow {
    u8 unk0[0x1C];
    s32 layer;
} DbgMenuWindow;

typedef struct DbgLogColor {
    u8 r, g, b, a;
} DbgLogColor;

extern void GSgfxZCompare(s32, s32);
extern const char* GSlogGetLine(s32);
extern s32 GSlogGetLineCount(void);
extern void GSprint(s32, s32, s32, u32, ...);
extern void menuClose(s32);
extern u8 menuIsCheck(s32);
extern s32 menuOpenCustom(s32, s32, s32, s32, s32, s32, ...);
extern void menuSubDrawTile(s32, s32, s32, s32, s32, DbgLogColor);
extern DbgMenuKeyInfo* windowGetKeyInfo(void);
extern s32 windowGetParam(DbgMenuWindow*, s32);
extern void windowSetParam(DbgMenuWindow*, s32, s32);

static s32 _viewStartLine;
static u8 _calcStartLine;

s32 dbgMenuLogDraw(DbgMenuWindow* window) {
    DbgLogColor color = { 0, 0, 0, 0x80 };
    DbgMenuKeyInfo* key = windowGetKeyInfo();
    s32 next;
    s32 y;
    s32 lines;
    s32 height;
    s32 maxStart;
    s32 i;

    if (key->hold & 0x100) {
        next = windowGetParam(window, 0) + 1;
        if (next >= 3) {
            next = 0;
        }
        windowSetParam(window, 0, next);
    }
    switch (windowGetParam(window, 0)) {
    case 0:
    default:
        lines = 10;
        height = 0x82;
        y = 0x145;
        break;
    case 1:
        lines = 10;
        height = 0x82;
        y = 0x27;
        break;
    case 2:
        lines = 1;
        height = 0xD;
        y = 0x1BA;
        break;
    }
    GSgfxZCompare(0, 7);
    menuSubDrawTile(window->layer, 0xF, y - 5, 0x25D, height + 0x12, color);
    if (_calcStartLine) {
        _viewStartLine = GSlogGetLineCount() - lines;
        _calcStartLine = 0;
    }
    if (key->trigger & 1) {
        _viewStartLine -= 1;
    }
    if (key->trigger & 2) {
        _viewStartLine += 1;
    }
    if (key->trigger & 8) {
        _viewStartLine += lines;
    }
    if (key->trigger & 4) {
        _viewStartLine -= lines;
    }
    maxStart = GSlogGetLineCount() - lines;
    if (_viewStartLine < 0) {
        _viewStartLine = 0;
    }
    if (_viewStartLine > maxStart) {
        _viewStartLine = maxStart;
    }
    for (i = 0; i < lines; i++) {
        if (i + _viewStartLine >= 0) {
            GSprint(window->layer, 0x14, y, 0xC0C0C0FF, GSlogGetLine(i + _viewStartLine));
        }
        y += 0xD;
    }
    return 0;
}

s32 dbgMenuLogChangeDisp(void) {
    if (menuIsCheck(0x22)) {
        menuClose(0x22);
    } else {
        _calcStartLine = 1;
        menuOpenCustom(0x22, 0, 0, 0, 1, 0);
    }
    return 0;
}
