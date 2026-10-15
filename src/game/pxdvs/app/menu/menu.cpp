#include <game/pxdvs/app/menu/menuPrivate.hpp>
#include <libc/stdarg.h>
#include <libc/string.h>

static f64 _gettLastTime();
static void _menuUpdateKeyInfo(WINDOW_SYS_WORK *, WINDOW_SYS_WORK *);

f32 _currentAddTime;
f32 _currentTime;
s32 _menuCount;

struct MenuItemBits {
    u8 selectable : 1;
    u8 last : 1;
    u8 rest : 6;
};
#define ITEM_SELECTABLE(p) (((MenuItemBits *)(p))->selectable)
#define ITEM_LAST(p) (((MenuItemBits *)(p))->last)

extern "C" {

s32 menuGetCursor(s32 id);
void menuButtonNormal(tagWINDOW_WORK *w);
void menuCursorNormal(tagWINDOW_WORK *w, u8 a);
MENU_ITEM_dd_ *windowGetCursorToItem(tagWINDOW_WORK *w);
WindowKeyInfo *windowGetKeyInfo2();
void menuPlaySe(s32 id, s32 se);
u8 menuCursorCmp(WindowCursor *a, WindowCursor *b);
s32 menuCloseCustom(s32 id, s32 force, u8 sync);
s32 menuOpenCustom(s32 id, s32 parent, s32 *selection, u32 flags, u8 sync, s32 count, ...);

void menuButtonNormal(tagWINDOW_WORK *w) {
    if (w != 0) {
        u16 trigger = windowGetKeyInfo()->trigger;
        if (trigger & 0x10) {
            w->finished = 1;
        }
        if (trigger & 0x20) {
            w->finished = 1;
            w->cancelled = 1;
        }
    }
}

s32 menuGetLastError() {
    return winSysWork.lastError;
}

u32 menuGetOffScreenFlag() {
    return menuOffScreenCheckEnable(0);
}

void menuReleaseOffScreen(f32 time) {
    menuOffScreenFadeSet(0.0f, time);
    menuOffScreenFadeSync(1);
    menuOffScreenRelease();
}

void menuCreateOffScreen(f32 time, f32 rate) {
    menuOffScreenCreate(1);
    menuOffScreenSetDisp(1);
    menuOffScreenSetPriority(1);
    menuOffScreenFadeSet(rate, time);
}

s32 menuGetSelectItemNum(s32 id) {
    s32 count = 0;
    MenuData *data = menuDataBiosGetPtr(id);
    s32 item;
    MENU_ITEM_dd_ *p;
    if (data == 0) {
        return 0;
    }
    item = data->firstItem;
    for (;;) {
        p = menuItemBiosGetPtr(id, item);
        if (ITEM_SELECTABLE(p)) {
            count++;
        }
        if (ITEM_LAST(p)) {
            break;
        }
        item = p->nextItem;
    }
    return count;
}

s32 menuGetCursorFromItemID(s32 id, u32 itemID) {
    s32 item;
    s32 count;
    MenuData *data = menuDataBiosGetPtr(id);
    MENU_ITEM_dd_ *p;
    if (data == 0) {
        return -3;
    }
    count = 0;
    item = data->firstItem;
    for (;;) {
        p = menuItemBiosGetPtr(id, item);
        if ((u32)(s16)item == itemID) {
            if (ITEM_SELECTABLE(p)) {
                return count;
            }
            return -1;
        }
        if (ITEM_SELECTABLE(p)) {
            count++;
        }
        if (ITEM_LAST(p)) {
            break;
        }
        item = p->nextItem;
    }
    return -2;
}

u8 menuGetDisp(s32 id) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w == 0) {
        return 0;
    }
    return ((s8)w->flags & 2) != 0;
}

void menuSetDisp(s32 id, u8 disp) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w != 0) {
        s8 *f = (s8 *)w;
        if (disp) {
            *f = *f | 2;
        } else {
            *f = *f & ~2;
        }
    }
}

s16 menuGetCursorItemID(s32 id) {
    s32 item;
    s32 count;
    s32 cursor = menuGetCursor(id);
    MenuData *data;
    MENU_ITEM_dd_ *p;
    if (cursor == -1) {
        return 0;
    }
    data = menuDataBiosGetPtr(id);
    if (data == 0) {
        return 0;
    }
    count = 0;
    item = data->firstItem;
    for (;;) {
        p = menuItemBiosGetPtr(id, item);
        if (ITEM_SELECTABLE(p)) {
            if (count == cursor) {
                return item;
            }
            count++;
        }
        if (ITEM_LAST(p)) {
            break;
        }
        item = p->nextItem;
    }
    return 0;
}

s32 menuSetCursor(s32 id, s8 cursor) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w != 0) {
        w->cursorIndex = cursor;
    } else {
        return -1;
    }
    return 0;
}

s32 menuGetCursor(s32 id) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w != 0) {
        return w->cursorIndex + w->cursorBase;
    }
    return -1;
}

s32 menuCloseSync(s32 id, u8 wait) {
    if (wait) {
        for (;;) {
            if (windowSearchID(id) == 0) {
                return 0;
            }
            if (GSthreadGetCurrentThread() == 0) {
                GSlogWrite("%s(0x%08x)  スレッドから呼ぶようにしてください\n", __FUNCTION__, id);
                break;
            }
            GSthreadSwitch();
        }
    } else {
        return windowSearchID(id) != 0;
    }
    return 0;
}

void menuCloseFloor() {
    windowClose(0, 4);
}

void menuClose(s32 id) {
    if (id == 0) {
        id = windowGetActiveID();
    }
    menuCloseCustom(id, 0, 0);
}

s32 menuCloseCustom(s32 id, s32 force, u8 sync) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w == 0) {
        return 1;
    }
    windowClose(w, force);
    menuCloseSync(id, sync);
    return 0;
}

s32 menuIsCheck(s32 id) {
    return windowSearchID(id) != 0;
}

s32 menuOpenCustom(s32 id, s32 parent, s32 *selection, u32 flags, u8 sync, s32 count, ...) {
    va_list args;
    tagWINDOW_WORK *w;
    s32 value = 0;
    va_start(args, count);
    w = windowOpen(selection, id, parent, flags, count, args);
    if ((u8)sync) {
        MenuData *data;
        s32 pos;
        windowCheckCursor(id, sync);
        value = windowGetValue(id);
        data = menuDataBiosGetPtr(id);
        if (data->cursorID) {
            pos = *(s32 *)&w->cursorBase;
            cursorBiosSetPos(data->cursorID, &pos);
        }
        if (selection) {
            *selection = menuGetCursor(id);
        }
    }
    if ((flags & 1) != 0) {
        menuCloseCustom(id, 0, sync);
    }
    return value;
}

s32 menuOpen(s32 id, u8 cursor) {
    return menuOpenCustom(id, windowGetActiveID(), 0, 0, cursor, 0);
}

void menuSetPosition(s32 id, s16 x, s16 y) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w != 0) {
        w->x = x;
        w->y = y;
    }
}

void menuDaemon() {
    MenuDataEx *data;
    tagWINDOW_WORK *active;
    tagWINDOW_WORK *win;
    u8 fade = 1;
    GSgfxLayerSetActive(7);
    active = windowSearchID(windowGetActiveID());
    _menuUpdateKeyInfo(&winSysWork, &winSysWork2);
    menuOffScreenDraw();
    f64 d = _gettLastTime();
    f32 t = d;
    _currentAddTime = _currentAddTime + t;
    _currentTime = d;
    _menuCount++;
    if (_currentAddTime > 1.0f) {
        _currentAddTime -= 1.0f;
    }
    for (win = winSysWork.head; win != 0; win = win->next) {
        data = (MenuDataEx *)menuDataBiosGetPtr(win->menuID);
        switch (win->state) {
        case 0:
            win->state = 1;
            win->entered = 0;
            break;
        case 1:
            if (!winSeqCheckMove(win->menuID)) {
                if ((u32)((data->flags2 >> 5) & 7) == 0) {
                    win->finished = 1;
                }
                win->state = 2;
                win->entered = 0;
            }
            break;
        case 2:
            if (win->closing) {
                menuPlaySe(win->menuID, 5);
                win->state = 3;
                win->entered = 0;
            }
            break;
        case 3:
            if (!winSeqCheckMove(win->menuID)) {
                win->state = 4;
                win->entered = 0;
            }
            break;
        case 4:
            break;
        }
        if (!pauseIsPause() && active != 0 && win == active) {
            if (!win->finished) {
                switch (win->state) {
                case 2:
                    switch ((data->flags2 >> 5) & 7) {
                    case 0:
                        win->finished = 1;
                        break;
                    case 1:
                        menuButtonNormal(win);
                        break;
                    case 2:
                        break;
                    case 3:
                        floorExecScriptIntegerByName("menu_button", 0, 0, 0, 0);
                        break;
                    case 4:
                        data->button(win);
                        break;
                    }
                    if ((win->openFlags & 8) && win->cancelled) {
                        win->cancelled = 0;
                        win->finished = 0;
                    }
                    if (win->finished) {
                        winSysWork.lastError = 0;
                        winSysWork.lastMenuID = win->menuID;
                    } else if (windowGetKeyInfo()->on & 0x8000) {
                        winSysWork.lastError = 1;
                        winSysWork.lastMenuID = win->menuID;
                        if (!(win->openFlags & 0x10)) {
                            win->finished = 1;
                            win->cancelled = 1;
                        }
                    }
                    break;
                case 3:
                    break;
                }
                if (win->cancelled) {
                    menuPlaySe(win->menuID, 3);
                } else if (win->finished) {
                    menuPlaySe(win->menuID, 2);
                }
            }
            if (!win->finished) {
                switch (win->state) {
                case 2: {
                    WindowCursor *prev = (WindowCursor *)win->reservedA0;
                    prev->base = win->cursorBase;
                    prev->index = win->cursorIndex;
                    if ((s8)win->itemCount > 0) {
                        switch (win->kind) {
                        case 1:
                        case 2:
                            menuCursorNormal(win, 1);
                            break;
                        case 3:
                            floorExecScriptIntegerByName("menu_cursor", 0, 0, 0, 0);
                            break;
                        case 4:
                            data->cursor(win);
                            break;
                        }
                        {
                            s32 old;
                            s32 now;
                            now = *(s32 *)&win->cursorBase;
                            old = *(s32 *)win->reservedA0;
                            if (menuCursorCmp((WindowCursor *)&old, (WindowCursor *)&now)) {
                                windowCreateCursorSprite(win);
                                menuPlaySe(win->menuID, 1);
                            }
                        }
                    }
                    break;
                }
                }
            }
        }
        if ((s8)win->flags & 4) {
            if (!pauseIsPause()) {
                winSeqMoveMenu(win);
            }
            if (data->control != 0) {
                data->control(win);
            }
        }
    }
    for (win = winSysWork.head; win != 0; win = win->next) {
        if (win->state == 4) {
            windowCloseMain(win);
        }
    }
    {
        s32 menuLayer = floorGetMenuLayerID();
        tagWINDOW_WORK *w;
        for (w = winSysWork.head; w != 0; w = w->next) {
            s32 layer;
            WindowSprite *sprite;
            if (fade && w->priority >= 0x50) {
                fade = 0;
                fadeDaemon();
            }
            if ((s8)w->flags & 2) {
                spriteSetOffset(layer = w->layerID, w->x, w->y);
                spriteClearScissor(layer);
                spriteSetEnv(layer);
                spriteSetOffset(menuLayer, w->x, w->y);
                spriteClearScissor(menuLayer);
                spriteSetEnv(menuLayer);
                for (sprite = w->items; sprite != 0; sprite = sprite->next) {
                    winSpriteDraw(w, sprite);
                }
                s32 index = 0;
                for (sprite = w->cursor; sprite != 0; sprite = sprite->next) {
                    menuItemBiosGetPtr(w->menuID, sprite->itemID);
                    winSpriteDraw(w, sprite);
                    if (index != 0 && w->state == 3) {
                        winSetSequence(sprite->sequence, 0);
                    }
                    index++;
                }
                {
                    void (*draw)(tagWINDOW_WORK *) = ((MenuDataEx *)menuDataBiosGetPtr(w->menuID))->draw;
                    if (draw != 0) {
                        draw(w);
                    }
                }
            }
        }
        spriteSetOffset(7, 0, 0);
        spriteClearScissor(7);
        spriteClearEnv(7);
        spriteSetOffset(menuLayer, 0, 0);
        spriteClearScissor(menuLayer);
        spriteClearEnv(menuLayer);
    }
    if (fade) {
        fadeDaemon();
    }
    GSgfxLayerSetActive(2);
}

f32 menuGetTotalTime() {
    return _currentAddTime;
}

f32 menuGetLastTime() {
    return _currentTime;
}

}

static f64 _gettLastTime() {
    return timeGetLastFrameSec();
}

extern "C" {

#define ABS_S(x) ((x) < 0 ? -(x) : (x))
#define ITEM_PREV_INDEX(w) (*(s16 *)&(w)->reservedA0[2])

#define CURSOR_SCAN(DIST, ACROSS, TOL, BESTCMP)                                  \
    for (;;) {                                                                   \
        if (ITEM_SELECTABLE(it)) {                                               \
            dist = DIST;                                                         \
            if (dist > 0) {                                                      \
                across = ACROSS;                                                 \
                if (ABS_S(across) < TOL && BESTCMP) {                            \
                    best = dist;                                                 \
                    w->cursorIndex = (s8)idx;                                    \
                }                                                                \
            }                                                                    \
            idx++;                                                               \
        }                                                                        \
        if (ITEM_LAST(it)) {                                                     \
            break;                                                               \
        }                                                                        \
        it = menuItemBiosGetPtr(w->menuID, it->nextItem);                        \
    }

void menuCursorNormal(tagWINDOW_WORK *w, u8 useKey2) {
    u16 wrap = 0;
    if (w != 0) {
        MenuDataEx *data;
        MENU_ITEM_dd_ *cur;
        MENU_ITEM_dd_ *it;
        s32 dist;
        s32 across;
        u16 keys;
        u16 extra;
        s32 up, down, left, right;
        if (w->kind == 2) {
            wrap = 1;
        }
        data = (MenuDataEx *)menuDataBiosGetPtr(w->menuID);
        cur = windowGetCursorToItem(w);
        if (cur == 0) {
            w->cursorIndex = 0;
            return;
        }
        {
            s32 tolX = 0x10;
            s32 tolY = 0xc;
            keys = windowGetKeyInfo()->repeat;
            if (useKey2) {
                if ((windowGetKeyInfo()->on & 0xF) != 0) {
                    extra = 0;
                } else {
                    extra = windowGetKeyInfo2()->repeat;
                }
            } else {
                extra = 0;
            }
            keys |= extra;
            up = keys & 1;
            down = keys & 2;
            left = keys & 4;
            right = keys & 8;
            do {
                s32 best;
                s32 idx;
                it = menuItemBiosGetPtr(w->menuID, data->firstItem);
                idx = 0;
                if (up) {
                    best = 0x1E0;
                    CURSOR_SCAN(cur->y - it->y, cur->x - it->x, tolX, best > dist)
                } else if (down) {
                    best = 0x1E0;
                    CURSOR_SCAN(it->y - cur->y, cur->x - it->x, tolX, best > dist)
                } else if (left) {
                    best = 0x280;
                    CURSOR_SCAN(cur->x - it->x, cur->y - it->y, tolY, best > dist)
                } else if (right) {
                    best = 0x280;
                    CURSOR_SCAN(it->x - cur->x, cur->y - it->y, tolY, best > dist)
                }
                if (ITEM_PREV_INDEX(w) != w->cursorIndex) {
                    break;
                }
                tolX += 0x10;
                tolY += 0xc;
                if (tolX >= 0x280) {
                    tolX = 0x280;
                }
                if (tolY >= 0x1E0) {
                    tolY = 0x1E0;
                }
            } while (tolX != 0x280 || tolY != 0x1E0);
        }
        if (wrap) {
            s32 tolX = 0x10;
            s32 tolY = 0xc;
            while (ITEM_PREV_INDEX(w) == w->cursorIndex) {
                s32 best;
                s32 idx;
                it = menuItemBiosGetPtr(w->menuID, data->firstItem);
                idx = 0;
                if (up) {
                    best = idx;
                    CURSOR_SCAN(it->y - cur->y, cur->x - it->x, tolX, best < dist)
                } else if (down) {
                    best = idx;
                    CURSOR_SCAN(cur->y - it->y, cur->x - it->x, tolX, best < dist)
                } else if (left) {
                    best = idx;
                    CURSOR_SCAN(it->x - cur->x, cur->y - it->y, tolY, best < dist)
                } else if (right) {
                    best = idx;
                    CURSOR_SCAN(cur->x - it->x, cur->y - it->y, tolY, best < dist)
                }
                tolX += 0x10;
                tolY += 0xc;
                if (tolX >= 0x280) {
                    tolX = 0x280;
                }
                if (tolY >= 0x1E0) {
                    tolY = 0x1E0;
                }
                if (tolX == 0x280 && tolY == 0x1E0) {
                    break;
                }
            }
        }
    }
}

void menuPlaySe(s32 id, s32 se) {
    u32 ptr;
    u16 snd;
    if (menuGetDisp(id) && (ptr = menuSeBiosGetPtr((menuDataBiosGetPtr(id)->flags1 >> 4) & 0xF)) != 0 && (snd = menuSeBiosGetSndId(ptr, se)) != 0) {
        GSsndPlayNow(snd);
    }
}

}

static u8 _menuGetAgbKeyInfo(s32 port, u16 *out) {
    s32 gba = port + 1;
    u16 keys = 0;
    u16 pressed;
    if (!gbaCommandIsConnected(gba)) {
        return 0;
    }
    pressed = gbaCommandKeyPressed(gba);
    if (pressed & 0x40) {
        keys |= 0x1;
    }
    if (pressed & 0x80) {
        keys |= 0x2;
    }
    if (pressed & 0x20) {
        keys |= 0x4;
    }
    if (pressed & 0x10) {
        keys |= 0x8;
    }
    if (pressed & 0x1) {
        keys |= 0x10;
    }
    if (pressed & 0x2) {
        keys |= 0x20;
    }
    if (pressed & 0x4) {
        keys |= 0x100;
    }
    if (pressed & 0x200) {
        keys |= 0x200;
    }
    if (pressed & 0x100) {
        keys |= 0x400;
    }
    if (pressed & 0x8) {
        keys |= 0x800;
    }
    *out = keys;
    return 1;
}

#define ABS_I(x) ((x) < 0 ? -(x) : (x))
#define ABS_F(x) ((x) > 0.0f ? (x) : -(x))

static u8 _menuGetGcKeyInfo(s32 port, u16 *leftOut, u16 *rightOut) {
    s32 ports[4] = {1, 2, 3, 4};
    s8 rx, ry;
    u16 left = 0;
    u16 right = 0;
    s32 pad = ports[port];
    s8 lx, ly;
    u32 buttons;
    f32 ang;
    if (!GSinputIsConnected(pad)) {
        return 0;
    }
    ly = GSinputGetLeftStickYData(pad, 0);
    lx = GSinputGetLeftStickXData(pad, 0);
    ry = GSinputGetRightStickYData(pad, 0);
    rx = GSinputGetRightStickXData(pad, 0);
    if (ABS_I(lx) > 0x20 || ABS_I(ly) > 0x20) {
        ang = atan2(lx, ly);
        if (ABS_F(ang) < 0.9599311f) {
            left |= 2;
        } else if (ABS_F(ang) > 2.1816616f) {
            left |= 1;
        }
        if (0.61086524f < ABS_F(ang) && ABS_F(ang) < 2.5307274f) {
            if (ang < 0.0f) {
                left |= 4;
            } else {
                left |= 8;
            }
        }
    }
    if (ABS_I(rx) > 0x16 || ABS_I(ry) > 0x16) {
        ang = atan2(rx, ry);
        if (ABS_F(ang) < 0.9599311f) {
            right |= 2;
        } else if (ABS_F(ang) > 2.1816616f) {
            right |= 1;
        }
        if (0.61086524f < ABS_F(ang) && ABS_F(ang) < 2.5307274f) {
            if (ang < 0.0f) {
                right |= 4;
            } else {
                right |= 8;
            }
        }
    }
    buttons = GSinputButtonsPressed(pad);
    if (buttons & 0x8) {
        left |= 0x1;
    }
    if (buttons & 0x4) {
        left |= 0x2;
    }
    if (buttons & 0x1) {
        left |= 0x4;
    }
    if (buttons & 0x2) {
        left |= 0x8;
    }
    if (buttons & 0x100) {
        left |= 0x10;
    }
    if (buttons & 0x200) {
        left |= 0x20;
    }
    if (buttons & 0x400) {
        left |= 0x40;
    }
    if (buttons & 0x800) {
        left |= 0x80;
    }
    if (buttons & 0x10) {
        left |= 0x100;
    }
    if (buttons & 0x40) {
        left |= 0x200;
    }
    if (buttons & 0x20) {
        left |= 0x400;
    }
    if (buttons & 0x1000) {
        left |= 0x800;
    }
    *leftOut = left;
    *rightOut = right;
    return 1;
}

static u8 connect_bak[4];
static u8 connect[4];

#define MENU_UPDATE_PORT(key, now)                                   \
    {                                                                \
        u16 trigger;                                                 \
        u16 repeat = 0;                                              \
        u16 released = 0;                                            \
        (key)->off = (key)->on;                                      \
        trigger = ((key)->off ^ 0xFFFF) & (now);                            \
        for (b = 0; b < 16; b++) {                                   \
            u16 bit = 1 << b;                                        \
            if (trigger & bit) {                                     \
                (key)->timers[b] = 15;                         \
                repeat |= bit;                                       \
            } else if ((now) & bit) {                                \
                (key)->timers[b] -= timeGetLastFrameTime();    \
                if ((key)->timers[b] <= 0) {                   \
                    repeat |= bit;                                   \
                    (key)->timers[b] = 5;                      \
                    released |= bit;                                 \
                } else {                                             \
                    released |= bit & (key)->released;               \
                }                                                    \
            }                                                        \
        }                                                            \
        if (trigger & 0xF) {                                         \
            (key)->timers[0] = 15;                                 \
            (key)->timers[1] = 15;                                 \
            (key)->timers[2] = 15;                                 \
            (key)->timers[3] = 15;                                 \
        }                                                            \
        (key)->on = (now);                                           \
        (key)->trigger = trigger;                                    \
        (key)->repeat = repeat;                                      \
        (key)->released = released;                                  \
    }

static void _menuUpdateKeyInfo(WINDOW_SYS_WORK *, WINDOW_SYS_WORK *) {
    s32 b;
    MenuKeyInfo *portA;
    MenuKeyInfo *portB;
    s32 i;
    u8 port;
    tagWINDOW_WORK *w;
    for (i = 0; i < 4; i++) {
        u16 keysA;
        u16 keysB;
        u8 type;
        keysA = 0;
        keysB = 0;
        portA = (MenuKeyInfo *)&winSysWork.portKeys[i];
        portB = (MenuKeyInfo *)&winSysWork2.portKeys[i];
        connect_bak[i] = connect[i];
        if (!_menuGetGcKeyInfo(i, &keysA, &keysB)) {
            if (!_menuGetAgbKeyInfo(i, &keysA)) {
                keysA = 0;
                type = 0;
            } else {
                type = 2;
            }
        } else {
            type = 1;
        }
        switch (type) {
        case 0:
            switch (connect_bak[i]) {
            case 0:
            case 1:
            default:
                connect[i] = 0;
                break;
            case 2:
            case 3:
                connect[i] = 3;
                keysA = 0x8000;
                break;
            }
            break;
        case 1:
            connect[i] = 1;
            break;
        case 2:
            switch (connect_bak[i]) {
            case 0:
            case 2:
            case 3:
            default:
                connect[i] = 2;
                break;
            case 1:
                connect[i] = 2;
                break;
            }
            break;
        default:
            connect[i] = type;
            break;
        }
        MENU_UPDATE_PORT(portA, keysA)
        MENU_UPDATE_PORT(portB, keysB)
    }
    w = windowSearchID(windowGetActiveID());
    if (w == 0) {
        port = 1;
    } else {
        port = w->port;
    }
    winSysWork.key = *windowGetPortKeyInfo(port);
    winSysWork2.key = *windowGetPortKeyInfo2(port);
}

extern "C" {

WindowKeyInfo menuGetKeyInfo(s32 port) {
    WindowKeyInfo info;
    u8 mask;
    switch (port) {
    case 1:
        mask = 1;
        break;
    case 2:
        mask = 2;
        break;
    case 3:
        mask = 4;
        break;
    case 4:
        mask = 8;
        break;
    default:
        mask = 0;
        break;
    }
    if (mask) {
        info = *windowGetPortKeyInfo(mask);
    } else {
        memset(&info, 0, sizeof(info));
    }
    return info;
}

s32 menuSetStatus(s32 id, u8 status) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w == 0) {
        return 0;
    }
    ((u8 *)w)[0x1B] = status;
    return 1;
}

u8 menuCursorCmp(WindowCursor *a, WindowCursor *b) {
    if (a->base == b->base && a->index == b->index) {
        return 0;
    }
    return 1;
}

u8 menuGetEnablePort() {
    return winSysWork.enablePort;
}

u8 menuSetEnablePort(u8 port) {
    u8 old = winSysWork.enablePort;
    winSysWork.enablePort = port;
    return old;
}


void menuInit(u16 capacity) {
    windowInit(capacity);
    cursorBiosInit();
    menuOffScreenInit();
    menuFaceInit(25);
    menuSetEnablePort(1);
    connect[0] = 0;
    connect_bak[0] = 0;
    connect[1] = 0;
    connect_bak[1] = 0;
    connect[2] = 0;
    connect_bak[2] = 0;
    connect[3] = 0;
    connect_bak[3] = 0;
    GSgfxVFInit(menuHyperModeVf);
    GSgfxVFCreate(menuHyperModeVf);
    GSgfxVFSetElement(menuHyperModeVf, 9, 0, 3, 0);
    GSgfxVFSetElement(menuHyperModeVf, 0xB, 1, 5, 0);
    GSgfxVFSetElement(menuHyperModeVf, 0xD, 1, 4, 0);
    GSgfxVFSetElement(menuHyperModeVf, 0xE, 1, 4, 0);
    GSgfxVFSetElement(menuHyperModeVf, 0xF, 1, 4, 0);
    GSresRegisterResource(GStextureLoad(uv_cmn_win_00), 0, 0x16BF1200, 0);
    GSresRegisterResource(GStextureLoad(uv_cmn_csr_00), 0, 0x16C11200, 0);
    GSresRegisterResource(GStextureLoad(uv_common_icon_00), 0, 0x21F41200, 0);
    GSresRegisterResource(GStextureLoad(tex_warning), 0, 0x21591200, 0);
    GSresRegisterResource(GStextureLoad(tex_warning_pstar), 0, 0x215A1200, 0);
    FlashSystemInitAll();
}

}
