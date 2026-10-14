/* Debug menu entries for viewing and editing game flags. */
#include <global.h>

typedef struct DbgFlagData {
    s16 unk0;
    s16 unk2;
    s16 next;
} DbgFlagData;

typedef struct DbgFlagDataHeader {
    u32 count;
    s16 first;
} DbgFlagDataHeader;

typedef struct DbgFlagEtc {
    u8 follower;
    u8 unk1;
    u16 floor;
    u16 money;
    u16 unk6;
    s32 flag;
    u32 script;
    f32 x;
    f32 y;
    f32 z;
    u32 name;
} DbgFlagEtc;

typedef struct DbgFlagCursor {
    s16 base;
    s16 sel;
} DbgFlagCursor;

typedef struct DbgMenuKeyInfo {
    u16 hold;
    u16 unk2;
    u16 unk4;
    u16 trigger;
} DbgMenuKeyInfo;

typedef struct DbgMenuWindow {
    u8 unk0[4];
    s32 menu;
    u8 unk8[0x14];
    s32 layer;
    u8 unk20[0x68];
    s32 result;
    u8 unk8C[0x10];
    DbgFlagCursor cursor;
} DbgMenuWindow;

extern s32 GSflagGet(s32);
extern void GSflagOff(s32);
extern void GSflagOn(s32);
extern void GSflagSet(s32, s32);
extern s32 GSfloorGetCurrent(void);
extern u8 GSfloorIsFloorPushed(void);
extern u32 GSinputButtonsPressed(s32);
extern u32 GSmsgGetRect(u32);
extern void GSprint(s32, s32, s32, u32, const char*, ...);
extern void GSsndPlayNow(s32);
extern void GSthreadSwitch(void);
extern void appScriptCommonCall(u32);
extern s32 dbgMenuGetLayerID(void);
extern void floorChangePos(s32, s32, f32, f32, f32);
extern void heroBiosSetPokedoru(void*, u16);
extern void heroSetFollowerWithID(s32, s32);
extern void menuClose(s32);
extern u8 menuDataBiosGetDispMax(s32);
extern s32 menuOpen(s32, s32);
extern void menuSubDrawSimpleWindow(s32, s32, s32, s32, s32);
extern void menuSubDrawTriangle(s32, s32, s32, s32, s32, s32, s32);
extern u8 menuSubOpenNumberInputDigit(s32, s32*);
extern void* savedataGetStatus(s32, s32);
extern int sprintf(char*, const char*, ...);
extern DbgMenuKeyInfo* windowGetKeyInfo(void);

extern DbgFlagData* flag_data;
extern DbgFlagDataHeader* flag_data_number;
extern DbgFlagEtc* flag_etc;
extern u32* flag_etc_number;

static DbgFlagCursor _dbgMenuFlagCursor = { 0, 0 };

void dbgMenuFlagSetEtc(s32 index);
static u16 _dbgMenuFlagGetID(s32 index);
static const char* _dbgMenuFlagInfoGetMsg(s32 index);
static s8 _dbgMenuFlagGetMenuNum(void* window, s32* width);

void dbgMenuFlagInfoDraw(DbgMenuWindow* window) {
    s32 y;
    s32 height;
    u8 dispMax = menuDataBiosGetDispMax(window->menu);
    s32 count = flag_data_number->count;
    s32 i;
    u32 color;

    if (count > dispMax) {
        count = dispMax;
    }
    height = count * 13;
    menuSubDrawSimpleWindow(window->layer, 0x1E, 0x28, 0x7D, height);
    if (_dbgMenuFlagCursor.base > 0) {
        menuSubDrawTriangle(window->layer, 0x46, 0x21, 0x5A, 0x21, 0x50, 0x17);
    }
    if ((u32)(flag_data_number->count - _dbgMenuFlagCursor.base) > dispMax) {
        menuSubDrawTriangle(window->layer, 0x46, height + 0x2F, 0x5A, height + 0x2F, 0x50, height + 0x39);
    }
    y = 0x28;
    for (i = 0; i < count; i++) {
        if (_dbgMenuFlagCursor.sel == i) {
            color = 0xFF0000FF;
        } else {
            color = 0xFFFFFFFF;
        }
        GSprint(window->layer, 0x1E, y, color, _dbgMenuFlagInfoGetMsg(i + _dbgMenuFlagCursor.base));
        GSprint(window->layer, 0x82, y, color, "%d", GSflagGet(i + _dbgMenuFlagCursor.base));
        y += 13;
    }
}

void dbgMenuFlagInfoCursor(DbgMenuWindow* window) {
    u16 trigger = windowGetKeyInfo()->trigger;
    u16 hold = windowGetKeyInfo()->hold;
    s16 total = flag_data_number->count;
    s16 dispMax;
    DbgFlagCursor cursor;

    dispMax = menuDataBiosGetDispMax(window->menu);
    if (total < dispMax) {
        dispMax = total;
    }
    cursor = _dbgMenuFlagCursor;
    if (trigger & 1) {
        cursor.sel -= 1;
    } else if (trigger & 2) {
        cursor.sel += 1;
    }
    if (trigger & 4) {
        cursor.sel -= menuDataBiosGetDispMax(window->menu) - 1;
    } else if (trigger & 8) {
        cursor.sel = menuDataBiosGetDispMax(window->menu) + cursor.sel - 1;
    }
    if (cursor.sel < 0) {
        cursor.sel = 0;
        cursor.base += cursor.sel;
        cursor.base = cursor.base;
        if (cursor.base < 0) {
            cursor.sel = dispMax - 1;
            cursor.base = total - dispMax;
        }
    } else if (cursor.sel >= dispMax) {
        s16 last = dispMax - 1;
        cursor.base += cursor.sel - last;
        cursor.sel = last;
        if (cursor.base + last >= total) {
            cursor.base = 0;
            cursor.sel = 0;
        }
    }
    if (hold & 0x80) {
        GSflagOn(cursor.base + cursor.sel);
    } else if (hold & 0x40) {
        GSflagOff(cursor.base + cursor.sel);
    }
    _dbgMenuFlagCursor = cursor;
    window->result = cursor.base + cursor.sel;
}

static const char* _dbgMenuFlagInfoGetMsg(s32 index) {
    static char buff[0x80];

    _dbgMenuFlagGetID(index);
    sprintf(buff, "[%4d]", index);
    return buff;
}

static u16 _dbgMenuFlagGetID(s32 index) {
    s16 id;
    s32 i;

    if (index < 0) {
        return 0;
    }
    if ((u32)index >= flag_data_number->count) {
        return 0;
    }
    id = flag_data_number->first;
    if (index != 0) {
        for (i = 0; i < index - 1; i++) {
            id = flag_data[id].next;
        }
        id = flag_data[id].next;
    }
    return id;
}

void dbgMenuFlagCursor(DbgMenuWindow* window) {
    u16 trigger = windowGetKeyInfo()->trigger;
    s8 total = _dbgMenuFlagGetMenuNum(window, 0);
    s8 dispMax;
    DbgFlagCursor cursor;

    dispMax = menuDataBiosGetDispMax(window->menu);
    if (total < dispMax) {
        dispMax = total;
    }
    cursor = window->cursor;
    if (trigger & 1) {
        cursor.sel -= 1;
    } else if (trigger & 2) {
        cursor.sel += 1;
    }
    if (trigger & 4) {
        cursor.sel -= dispMax - 1;
    } else if (trigger & 8) {
        cursor.sel = dispMax + cursor.sel - 1;
    }
    if (cursor.sel < 0) {
        cursor.sel = 0;
        cursor.base += cursor.sel;
        if (cursor.base < 0) {
            cursor.sel = dispMax - 1;
            cursor.base = total - dispMax;
        }
    } else if (cursor.sel >= dispMax) {
        s8 last = dispMax - 1;
        cursor.base += cursor.sel - last;
        cursor.sel = last;
        if (cursor.base + last >= total) {
            cursor.base = 0;
            cursor.sel = 0;
        }
    }
    window->cursor = cursor;
    window->result = cursor.base + (cursor.sel + 1);
}

s32 dbgMenuFlagCheck(void) {
    s32 value;
    s32 result;
    s32 selected;
    s32 i;

    if (GSfloorIsFloorPushed()) {
        GSsndPlayNow(0x13);
        i = 0;
        do {
            GSprint(dbgMenuGetLayerID(), 0xC8, 0xF0, -1, "\x82\xB1\x82\xCC\x83\x74\x83\x8D\x83\x41\x82\xA9\x82\xE7\x83\x74\x83\x8D\x83\x41\x83\x60\x83\x46\x83\x93\x83\x57\x82\xCD\x82\xA8\x82\xB1\x82\xC8\x82\xA6\x82\xDC\x82\xB9\x82\xF1");
            GSthreadSwitch();
            i++;
        } while ((u32)i < 0xF);
        return -1;
    }
    if (GSinputButtonsPressed(1) & 0x20) {
        for (;;) {
            result = menuOpen(0x27, 1);
            if (result < 0) {
                break;
            }
            selected = result;
            if (menuSubOpenNumberInputDigit(GSflagGet(selected), &value)) {
                GSflagSet(selected, value);
            }
        }
        if (result == -1) {
            menuClose(0x27);
            return -1;
        }
    } else {
        result = menuOpen(0xB, 1);
        menuClose(0xB);
        if (result > 0) {
            dbgMenuFlagSetEtc(result);
        } else if (result == -1) {
            return -1;
        }
    }
    return 0;
}

void dbgMenuFlagSetEtc(s32 index) {
    u32 floor;

    GSflagSet(0x3C4, flag_etc[index].flag);
    GSflagSet(0x3DE, 1);
    switch (flag_etc[index].follower) {
    case 0:
        heroSetFollowerWithID(0, 0);
        break;
    case 1:
        heroSetFollowerWithID(1, 0);
        break;
    case 2:
        heroSetFollowerWithID(2, 0);
        break;
    case 3:
        heroSetFollowerWithID(3, 0);
        break;
    }
    heroBiosSetPokedoru(savedataGetStatus(0, 2), flag_etc[index].money);
    if (flag_etc[index].script != 0) {
        appScriptCommonCall(flag_etc[index].script);
    }
    floor = flag_etc[index].floor;
    if (floor == 0) {
        floor = GSfloorGetCurrent();
    }
    floorChangePos(floor, 0, flag_etc[index].x, flag_etc[index].y, flag_etc[index].z);
}

static s8 _dbgMenuFlagGetMenuNum(void* window, s32* width) {
    u32 i;
    s8 count;
    u32 rect;
    u32 name;

    if (width != 0) {
        *width = 0;
    }
    count = 0;
    for (i = 0; i < *flag_etc_number; i++) {
        name = flag_etc[i].name;
        if (name != 0 && name != 0) {
            count++;
            if (width != 0) {
                rect = GSmsgGetRect(name) >> 16;
                if (*width < (s32)rect) {
                    *width = rect;
                }
            }
        }
    }
    return count;
}
