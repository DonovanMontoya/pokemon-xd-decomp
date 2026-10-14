#include <game/pxdvs/app/menu/menuPrivate.hpp>

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
s32 menuCloseCustom(s32 id, s32 force, u8 sync);
s32 menuOpenCustom(s32 id, s32 parent, s32 *cursorOut, s32 flags, s32 cursor, s32 a, ...);

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
    s32 count;
    MenuData *data = menuDataBiosGetPtr(id);
    s16 item;
    MENU_ITEM_dd_ *p;
    if (data == 0) {
        return -3;
    }
    count = 0;
    item = data->firstItem;
    for (;;) {
        p = menuItemBiosGetPtr(id, item);
        if ((u32)item == itemID) {
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
        return 0;
    }
    return -1;
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
                return 0;
            }
            GSthreadSwitch();
        }
    }
    return windowSearchID(id) != 0;
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
    if (windowSearchID(id) == 0) {
        return 1;
    }
    windowClose(id, force);
    menuCloseSync(id, sync);
    return 0;
}

s32 menuIsCheck(s32 id) {
    return windowSearchID(id) != 0;
}

s32 menuOpen(s32 id, s32 cursor) {
    return menuOpenCustom(id, windowGetActiveID(), 0, 0, cursor, 0);
}

void menuSetPosition(s32 id, s16 x, s16 y) {
    tagWINDOW_WORK *w = windowSearchID(id);
    if (w != 0) {
        w->x = x;
        w->y = y;
    }
}

f32 menuGetTotalTime() {
    return _currentAddTime;
}

f32 menuGetLastTime() {
    return _currentTime;
}

}

static f32 _gettLastTime() {
    return timeGetLastFrameSec();
}

extern "C" {

void menuPlaySe(s32 id, s32 se) {
    u32 ptr;
    u16 snd;
    if (menuGetDisp(id) && (ptr = menuSeBiosGetPtr((menuDataBiosGetPtr(id)->flags1 >> 4) & 0xF)) != 0 && (snd = menuSeBiosGetSndId(ptr, se)) != 0) {
        GSsndPlayNow(snd);
    }
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

}
