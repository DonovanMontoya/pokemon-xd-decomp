/* Debug menu entry for creating items in the bag. */
#include <global.h>

typedef struct DbgMenuKeyInfo {
    u8 unk0[6];
    u16 trigger;
} DbgMenuKeyInfo;

typedef struct DbgMenuWindow {
    u8 unk0[0x9E];
    s16 cursor;
} DbgMenuWindow;

extern void heroItemAddItemDataId(s32, u16, u16, s32);
extern u8 itemDataCheckValid(u16);
extern void menuClose(s32);
extern void menuCloseCustom(s32, s32, s32);
extern void menuCloseSync(s32, s32);
extern s32 menuOpen(s32, s32);
extern DbgMenuKeyInfo* windowGetKeyInfo(void);

extern s32* item_data_index_number;

static s32 Num;
static s32 ItemID;

static void nbItemCtrl(void) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();

    if (key->trigger & 8) {
        if ((Num += 1) > 999) {
            Num = 999;
        }
    }
    if (key->trigger & 0x400) {
        if ((Num += 10) > 999) {
            Num = 999;
        }
    }
    if (key->trigger & 4) {
        if ((Num -= 1) < 0) {
            Num = 0;
        }
    }
    if (key->trigger & 0x200) {
        if ((Num -= 10) < 0) {
            Num = 0;
        }
    }
}

static void itemNameCtrl(void) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();

    if (key->trigger & 8) {
        if ((ItemID += 1) >= *item_data_index_number) {
            ItemID = *item_data_index_number - 1;
        }
    }
    if (key->trigger & 0x400) {
        if ((ItemID += 10) >= *item_data_index_number) {
            ItemID = *item_data_index_number - 1;
        }
    }
    if (key->trigger & 4) {
        if ((ItemID -= 1) < 0) {
            ItemID = 0;
        }
    }
    if (key->trigger & 0x200) {
        if ((ItemID -= 10) < 0) {
            ItemID = 0;
        }
    }
}

s32 menuDbgItemCreateCursor(DbgMenuWindow* window) {
    DbgMenuKeyInfo* key = windowGetKeyInfo();

    if (key->trigger & 1) {
        if (--window->cursor < 0) {
            window->cursor = 0;
        }
    }
    if (key->trigger & 2) {
        if (++window->cursor > 1) {
            window->cursor = 1;
        }
    }
    switch (window->cursor) {
    case 0:
        itemNameCtrl();
        break;
    case 1:
        nbItemCtrl();
        break;
    }
    return 0;
}

void menuDbgItemCreate(void) {
    static s32 initFlag;
    s32 result;

    if (initFlag == 0) {
        ItemID = 1;
        initFlag = 1;
    }
    Num = 1;
    for (;;) {
        if (menuOpen(0x24, 1) == -1) {
            break;
        }
        if (itemDataCheckValid(ItemID) && Num >= 1 && Num <= 999) {
            result = menuOpen(0x55, 1);
            menuCloseCustom(0x55, 0, 1);
            if (result == 0) {
                heroItemAddItemDataId(0, ItemID, Num, -1);
            }
        }
    }
    menuClose(0x24);
    menuCloseSync(0x24, 1);
}
