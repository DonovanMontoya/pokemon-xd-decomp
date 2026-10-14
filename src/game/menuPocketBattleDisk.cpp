#include <game/menuSubLayout.hpp>
#include <libc/string.h>

struct BattleDiskMenuItem {
    u8 reserved0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
};

struct BattleDiskSpriteVal {
    u8 reserved0[4];
    s16 width;
    s16 height;
};

extern "C" {
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
s32 heroItemGetItemKindToItemAryPtr(s32, s32, u16*, s32, s32, s32);
u16 itemBiosGetItemDataId(s32);
u8 itemCheckValid(s32);
u32 itemDataBiosGetName(void*);
void* itemDataBiosGetPtr(u16);
void menuBattleDiskCloseDoc(void);
void menuBattleDiskOpenDoc(u8);
void menuCloseCustom(s32, s32, s32);
BattleDiskMenuItem* menuItemBiosGetPtr(s32, s16);
s32 menuOpenCustom(s32, s32, ...);
void menuPdaSubScrollBar(tagWINDOW_WORK*, tagSPRITE_WORK*, s32, s32, u32, s32, s32, void*);
s32 menuSpriteBiosGetPtr(u16);
BattleDiskSpriteVal* menuSpriteBiosGetValPtr(s32);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeValGet(s32*, s32*);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteSetOffset(s32, s32, s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void winSeqSetMenu(s32, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
void windowDrawSprite2(s16, s16, s16, s16, u32, tagWINDOW_WORK*, u16, s32, s32);
void windowDrawSpriteCursor(s32, s16, s32, tagWINDOW_WORK*, s32, s32, s32, s32*, s32);
s32 windowGetActiveID(void);
u16 windowGetKeyRepeat(void);
}

void menuPocketButtonWait(void);
void menuPocketToolFloatToZero(f32&, f32);
void menuPtPlaySe(unsigned long);
u8 deckDataVirtualDB_GetFlagData(unsigned short);

namespace {

struct BattleDiskData {
    s32 hero;
    s32 owner;
    s32 itemCount;
    s16 scroll;
    s16 cursor;
    f32 offset;
    u8 moveDown;
    f32 blink;
    u8 active;
    s32 selected;
};

BattleDiskData Data;

void _controlCursor(void);
void printItemList(tagWINDOW_WORK*, tagSPRITE_WORK*);
void diskUsedMarkDisplay(tagWINDOW_WORK*, tagSPRITE_WORK*, int);
u16 selectItem(void);
u16 getItemIDFromMenuPos(int);
int getNbItemSlot(void);
u32 getItemNameMsg(unsigned long);

}

static s32 getCursorPositionY(void);

extern "C" {

s32 menuPocketBattleDiskDrawLineCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    BattleDiskMenuItem* item = menuItemBiosGetPtr(win->menu, sprite->id);
    sprite->y = item->y + getCursorPositionY();
    return 0;
}

s32 menuPocketBattleDiskDrawBallCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 color;
    s32 pos[2] = {0, 0};
    s32 layer;
    color = -1;
    if (win->menu == windowGetActiveID()) {
        menuSubCursorAnimeValGet(pos, &color);
    }
    layer = winSpriteGetLayerID(win, sprite);
    windowDrawSpriteCursor(0, getCursorPositionY(), -1, win, 0xC2, 0, layer, pos, color);
    winSpriteSetDisp(sprite, 0);
    return 0;
}

}

static s32 getCursorPositionY(void) {
    s32 y = (s16)(Data.cursor * 0x1E);
    if (Data.moveDown == 0) {
        y += (s16)Data.offset;
    }
    return y;
}

extern "C" {

s32 menuPocketBattleDiskDrawRollDown(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    if (Data.active == 0) {
        return 0;
    }
    if (Data.scroll + 8 < Data.itemCount + 1) {
        sprite->color.channels.alpha = (u8)(255.0f * (1.0f - Data.blink));
    } else {
        sprite->color.channels.alpha = 0;
    }
    return 0;
}

s32 menuPocketBattleDiskDrawRollUp(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    if (Data.active == 0) {
        return 0;
    }
    if (Data.scroll > 0) {
        sprite->color.channels.alpha = (u8)(255.0f * (1.0f - Data.blink));
    } else {
        sprite->color.channels.alpha = 0;
    }
    return 0;
}

s32 menuPocketBattleDiskPageBar(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    menuPdaSubScrollBar(win, sprite, win->menu, 0x110, 0xF06422FF, Data.itemCount + 1, 8, &Data.scroll);
    winSpriteSetDisp(sprite, 0);
    return 0;
}

s32 menuPocketBattleDiskCtrl(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(0x3B, 0x60);
            win->step = 1;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        _controlCursor();
        menuPocketToolFloatToZero(Data.offset, 7.0f);
        Data.blink += 0.033333335f;
        if (Data.blink > 1.0f) {
            Data.blink = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x3B, 0x64);
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 menuPocketBattleDiskPrintItemKind(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s16 width = GSmsgGetRect(0x14D3) >> 16;
    GSmsgPrint2(winSpriteGetLayerID(win, sprite), (sprite->width - width) / 2, 0, -1, 0x14D3);
    return 0;
}

s32 menuPocketBattleDiskPrintItemList(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    BattleDiskMenuItem* list = menuItemBiosGetPtr(win->menu, 0x11B);
    BattleDiskMenuItem* self = menuItemBiosGetPtr(win->menu, sprite->id);
    spriteSetScissor(winSpriteGetLayerID(win, sprite), list->x - self->x, list->y - self->y, list->width, list->height);
    spriteSetEnv(winSpriteGetLayerID(win, sprite));
    printItemList(win, sprite);
    spriteSetOffset(winSpriteGetLayerID(win, sprite), 0, 0);
    spriteClearScissor(winSpriteGetLayerID(win, sprite));
    spriteSetEnv(winSpriteGetLayerID(win, sprite));
    return 0;
}

s32 menuPocketBattleDiskCursor(void) {
    return 0;
}

u16 menuPocketBattleDiskMain(s32 unused, s32 hero, s32 owner) {
    u16 item;
    memset(&Data, 0, 0x24);
    Data.hero = hero;
    Data.owner = owner;
    Data.itemCount = getNbItemSlot();
    for (;;) {
        Data.active = 1;
        item = selectItem();
        Data.active = 0;
        if (item == 0) {
            break;
        }
        menuBattleDiskOpenDoc(item - 0x215);
        menuPocketButtonWait();
        menuBattleDiskCloseDoc();
    }
    menuCloseCustom(0x3B, 0, 1);
    return item;
}

}

namespace {

void _controlCursor(void) {
    s16 old[2];
    u16 keys = windowGetKeyRepeat();
    u32 se = 0;
    s32 count = Data.itemCount + 1;
    s32 pages = (count + 7) / 8;
    if (Data.offset == 0.0f) {
        if (Data.active == 0) {
            return;
        }
        *(s32*)old = *(s32*)&Data.scroll;
        if (keys & 8) {
            s16 last = count - 8;
            if (pages == 1) {
                Data.cursor = count - 1;
            } else if (Data.scroll == last) {
                Data.cursor = 7;
            } else {
                s16 next = Data.scroll + 8;
                Data.scroll = next;
                if (next > last) {
                    Data.scroll = last;
                }
            }
            if (old[0] != Data.scroll || old[1] != Data.cursor) {
                menuPtPlaySe(0x44D);
            }
        } else if (keys & 4) {
            if (Data.scroll == 0) {
                Data.cursor = 0;
            } else {
                s16 prev = Data.scroll - 8;
                Data.scroll = prev;
                if (prev < 0) {
                    Data.scroll = 0;
                }
            }
            if (old[0] != Data.scroll || old[1] != Data.cursor) {
                menuPtPlaySe(0x44D);
            }
        } else if (keys & 2) {
            s16 next = Data.cursor + 1;
            Data.cursor = next;
            if (next + Data.scroll >= count) {
                Data.cursor = next - 1;
            } else {
                if (next >= 8) {
                    Data.scroll = Data.scroll + 1;
                    se = 0x10;
                    Data.cursor = next - 1;
                    Data.moveDown = 1;
                } else {
                    se = 0x10;
                    Data.moveDown = 0;
                }
                Data.offset = -30.0f;
            }
        }
        if ((keys & 1) && (Data.cursor > 0 || Data.scroll > 0)) {
            s16 prev = Data.cursor - 1;
            Data.cursor = prev;
            if (prev < 0) {
                Data.cursor = 0;
                se = 0x10;
                Data.scroll = Data.scroll - 1;
                Data.moveDown = 1;
            } else {
                se = 0x10;
                Data.moveDown = 0;
            }
            Data.offset = 30.0f;
        }
        if (old[0] != Data.scroll || old[1] != Data.cursor) {
            menuSubCursorAnimeStart();
        }
        if (se != 0) {
            menuPtPlaySe(se);
        }
    }
}

void printItemList(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s32 y;
    s32 count;
    s32 index;
    s32 rowEnd;
    s32 shift;
    s32 row;
    s32 drawY;
    s32 rowStart;
    rowStart = 0;
    rowEnd = 8;
    count = Data.itemCount;
    shift = 0;
    index = Data.scroll;
    if (Data.offset != 0.0f && Data.moveDown != 0) {
        if (Data.offset < 0.0f) {
            index -= 1;
            rowStart = -1;
        } else {
            rowEnd = 9;
        }
        shift = (s32)Data.offset;
    }
    y = rowStart * 0x1E;
    row = rowStart;
    while (row < rowEnd && index < count) {
        if (index >= 0) {
            u16 item;
            u32 msg;
            drawY = y - shift;
            item = getItemIDFromMenuPos(index);
            msg = getItemNameMsg(item);
            if (msg != 0) {
                if (deckDataVirtualDB_GetFlagData(item - 0x215) != 0) {
                    diskUsedMarkDisplay(win, sprite, drawY);
                }
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, drawY, -1, msg);
            }
        }
        y += 0x1E;
        row++;
        index++;
    }
    if (row < rowEnd) {
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, row * 0x1E - shift, -1, 0x3A9E);
    }
}

void diskUsedMarkDisplay(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, int y) {
    BattleDiskMenuItem* item = menuItemBiosGetPtr(win->menu, sprite->id);
    BattleDiskMenuItem* mark = menuItemBiosGetPtr(win->menu, 0x117);
    BattleDiskSpriteVal* val;
    s32 dx;
    s16 iy;
    s32 dy;
    dx = mark->x - item->x;
    iy = item->y;
    dy = mark->y - iy;
    val = menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0xD9));
    windowDrawSprite2(dx, dy + y, val->width, val->height, -1, win, 0xD9, 0, winSpriteGetLayerID(win, sprite));
}

u16 selectItem(void) {
    s32 pos;
    if (menuOpenCustom(0x3B, windowGetActiveID(), 0, 0, 1, 0) == -1) {
        return 0;
    }
    pos = Data.scroll + Data.cursor;
    Data.selected = pos;
    return getItemIDFromMenuPos(pos);
}

u16 getItemIDFromMenuPos(int pos) {
    u16 count;
    s32 item = heroItemGetItemKindToItemAryPtr(Data.owner, 7, &count, 0, 0, 0);
    s32 index = -1;
    s32 i;
    for (i = 0; i < count; i++, item += 4) {
        if (itemCheckValid(item)) {
            index++;
            if (index >= pos) {
                return itemBiosGetItemDataId(item);
            }
        }
    }
    return 0;
}

int getNbItemSlot(void) {
    u16 count;
    s32 item = heroItemGetItemKindToItemAryPtr(Data.owner, 7, &count, 0, 0, 0);
    s32 total = 0;
    s32 i;
    for (i = 0; i < count; i++, item += 4) {
        if (itemCheckValid(item)) {
            total++;
        }
    }
    return total;
}

u32 getItemNameMsg(unsigned long id) {
    return itemDataBiosGetName(itemDataBiosGetPtr(id));
}

}
