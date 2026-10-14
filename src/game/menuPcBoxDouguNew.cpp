#include <game/menuPcBoxDouguNewLayout.hpp>

enum MENU_PCBOX_DOUGU_HIKIDASHI_MODE {
    MENU_PCBOX_DOUGU_HIKIDASHI_MODE_0,
    MENU_PCBOX_DOUGU_HIKIDASHI_MODE_1
};

extern "C" {
void *itemDataBiosGetPtr(u16);
u8 itemDataBiosGetKind(void *);
u32 itemDataBiosGetDoc(void *);
u32 itemDataBiosGetName(void *);
u16 pcboxGetNbItemSlot(s32);
void *pcboxGetItem(s32, s16);
void pcboxSwapItemSlot(s32, s16, s16);
void pcboxDelItem(s32, u16, u16);
u8 itemCheckValid(void *);
u16 itemBiosGetNum(void *);
u16 itemBiosGetItemDataId(void *);
void msgctrlSetValue(s32, u32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
void GSmsgPrintRight(s32, s32, s32, s16, s16, s32, u32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
u32 GSmsgGetRect(u32);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
s32 menuPocketInputNumber(tagWINDOW_WORK *, s32, s32, u16, s32, s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK *, bool);
void winSeqSetMenu(s32, s32);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
s32 menuOpen(s32, s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuButtonNormal(void);
void menuSubCursorAnimeInit(s32);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeValGet(s32 *, s32 *);
void spriteSetScissor(s32, s32, s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void windowDrawSpriteCursor(s32, s16, s32, tagWINDOW_WORK *, s32, s32, s32, s32 *, s32);
void winMsgOpen(s32, s32, s32, s32);
void winMsgClose(s32);
s32 heroItemCheckAddItemDataId(s32, u16);
void heroItemAddItemDataId(s32, u16, u16, s32);
void fadeSet(s32, f32);
void fadeCheck(s32);
}

void menuPtPlaySe(u32);
MENU_ITEM_dd_ *menuPtItemGetBySpriteWork(tagWINDOW_WORK *, tagSPRITE_WORK *);
tagSPRITE_WORK *menuPtSpriteWorkGetByItemID(tagWINDOW_WORK *, u32, long);

static s32 beforCursorPosition;
static f32 CurPos;
static s32 IsScroll;
static s32 IrekaeSlotID;
static u32 ExplanationMsgID;
static s32 Mode;
static s32 CursorOfs;
static s32 CursorPos;
static f32 _RollUpTime;
static s32 NumValue;

static s32 menuPcBoxDouguConfirm(void);
static s32 _getItemListLineHeight(void);
static void setExplanationMsgID(u32);
static int menuPcBoxDouguNum(int, int);
static u8 getItemKind(u16);
static void swapItemSlot(int, int);
static u32 getItemInstMsg(u32);
static u16 getItemNumFromMenuPos(int);
static u32 getItemNameMsg(u16);
static u16 getItemIDFromMenuPos(int);
static s32 getNbItemSlot(void);
static s32 printItemListDougu(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);

extern "C" s32 menuPcBoxDouguNumDrawNum(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    const s32 ids[3] = {0x4B0, 0x4AF, 0x4AE};
    s32 i;
    s32 j;
    s32 div;
    for (i = 0; i < 3; i++) {
        if (sprite->id == ids[i]) {
            break;
        }
    }
    if (i >= 3) {
        return 0;
    }
    div = 1;
    for (j = 0; j < i; j++) {
        div *= 10;
    }
    s32 v = NumValue / div % 10;
    msgctrlSetValue(0x34, v);
    GSmsgPrintRight(winSpriteGetLayerID(win, sprite), 0, 0, sprite->width, sprite->height, win->color90, 0x4270);
    return 0;
}

extern "C" s32 menuPcBoxDouguNumCursor(tagWINDOW_WORK *win) {
    s32 *limit = win->numLimit;
    s32 i;
    NumValue = menuPocketInputNumber(win, NumValue, *limit, windowGetKeyRepeat(), 3, 0x441, 0x444);
    for (i = 0; i < 3; i++) {
        winSpriteSetDisp(menuPtSpriteWorkGetByItemID(win, 0x4AB, 2 - i), i == win->selected);
    }
    return 0;
}

extern "C" s32 menuPcBoxDouguNumCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(0x8C, 0x70);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x8C, 0x74);
            win->step = 1;
        }
        break;
    }
    return 0;
}

static int menuPcBoxDouguNum(int value, int limit) {
    s32 args[2];
    s32 ret;
    NumValue = value;
    args[0] = 2;
    args[1] = limit;
    ret = menuOpenCustom(0x8C, windowGetActiveID(), &args[0], 0, 1, 1, &args[1]);
    menuClose(0x8C);
    menuCloseSync(0x8C, 1);
    if (ret == -1 || NumValue == 0) {
        return -1;
    }
    return NumValue;
}

static u8 getItemKind(u16 id) {
    return itemDataBiosGetKind(itemDataBiosGetPtr(id));
}

static void swapItemSlot(int a, int b) {
    pcboxSwapItemSlot(0, a, b);
}

static u32 getItemInstMsg(u32 id) {
    return itemDataBiosGetDoc(itemDataBiosGetPtr(id));
}

static u16 getItemNumFromMenuPos(int pos) {
    u16 count = pcboxGetNbItemSlot(0);
    void *item;
    int i;
    s32 n = -1;
    for (i = 0; i < count; i++) {
        item = pcboxGetItem(0, i);
        if (itemCheckValid(item)) {
            n++;
            if (n >= pos) {
                return itemBiosGetNum(item);
            }
        }
    }
    return 0;
}

static u32 getItemNameMsg(u16 id) {
    return itemDataBiosGetName(itemDataBiosGetPtr(id));
}

static u16 getItemIDFromMenuPos(int pos) {
    u16 count = pcboxGetNbItemSlot(0);
    void *item;
    int i;
    s32 n = -1;
    for (i = 0; i < count; i++) {
        item = pcboxGetItem(0, i);
        if (itemCheckValid(item)) {
            n++;
            if (n >= pos) {
                return itemBiosGetItemDataId(item);
            }
        }
    }
    return 0;
}

static s32 getNbItemSlot(void) {
    int i;
    s32 n = 0;
    u16 count = pcboxGetNbItemSlot(0);
    for (i = 0; i < count; i++) {
        if (itemCheckValid(pcboxGetItem(0, i))) {
            n++;
        }
    }
    return n;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawTitleText(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    u32 msg;
    s16 halfW;
    MENU_ITEM_dd_ *item;
    if (Mode == 0) {
        msg = 0x3BC0;
    } else {
        msg = 0x3BC1;
    }
    sprite->message = msg;
    item = menuPtItemGetBySpriteWork(win, sprite);
    halfW = sprite->width / 2;
    s16 textW = GSmsgGetRect(msg) >> 16;
    sprite->x = item->x + (s16)(halfW - textW / 2);
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawRollDown(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 ofs = CursorOfs + 8;
    bool disp;
    if (ofs < getNbItemSlot() + 1) {
        disp = true;
    } else {
        disp = false;
    }
    sprite->color.channels.alpha = (u8)(255.0f * (1.0f - _RollUpTime));
    winSpriteSetDisp(sprite, disp);
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawRollUp(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    bool disp;
    if (CursorOfs > 0) {
        disp = true;
    } else {
        disp = false;
    }
    sprite->color.channels.alpha = (u8)(255.0f * (1.0f - _RollUpTime));
    winSpriteSetDisp(sprite, disp);
    return 0;
}

static s32 printItemListDougu(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, u32 color) {
    s32 start = 0;
    s32 end = 8;
    s32 scroll = 0;
    s32 count = getNbItemSlot();
    s32 pos = CursorOfs;
    s32 i;
    msgctrlSetValue(0x34, 999);
    s16 w1 = GSmsgGetRect(0x4270) >> 16;
    s32 base = w1 + (s16)(GSmsgGetRect(0x428F) >> 16);
    if (CurPos != 0.0f && IsScroll != 0) {
        if (CurPos < 0.0f) {
            pos--;
            start = -1;
        } else {
            end = 9;
        }
        scroll = (s32)CurPos;
    }
    for (i = start;; i++, pos++) {
        if (!(i < end && pos < count)) {
            break;
        }
        if (pos >= 0) {
            s32 y = i * _getItemListLineHeight() - scroll;
            u16 id = getItemIDFromMenuPos(pos);
            u32 name = getItemNameMsg(id);
            if (name != 0) {
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, y, color, name);
            }
            if (getItemKind(id) != 5) {
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0x11A - base, y, color, 0x428F);
                msgctrlSetValue(0x34, getItemNumFromMenuPos(pos));
                s16 w3 = GSmsgGetRect(0x4270) >> 16;
                GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0x11A - w3, y, color, 0x4270);
            }
        }
    }
    if (i < end) {
        s32 y = i * _getItemListLineHeight() - scroll;
        GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, y, color, 0x3BBA);
    }
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawItemText(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    tagSPRITE_WORK *area = menuPtSpriteWorkGetByItemID(win, 0x4A7, 0);
    spriteSetScissor(winSpriteGetLayerID(win, sprite), area->x - sprite->x, area->y - sprite->y, area->width,
                     area->height);
    printItemListDougu(win, sprite, win->color90);
    spriteClearScissor(winSpriteGetLayerID(win, sprite));
    spriteSetEnv(winSpriteGetLayerID(win, sprite));
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 y;
    s32 anim;
    y = CursorPos * _getItemListLineHeight();
    if (IsScroll == 0) {
        y += (s32)CurPos;
    }
    s32 pair[2] = {0, 0};
    anim = -1;
    if (win->menu == windowGetActiveID()) {
        menuSubCursorAnimeValGet(pair, &anim);
    }
    windowDrawSpriteCursor(0, y, -1, win, 0xC2, 0, winSpriteGetLayerID(win, sprite), pair, anim);
    winSpriteSetDisp(sprite, false);
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawLineCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    MENU_ITEM_dd_ *item = menuPtItemGetBySpriteWork(win, sprite);
    s32 y;
    if (IrekaeSlotID >= 0) {
        s32 line = IrekaeSlotID - CursorOfs;
        y = item->y + line * _getItemListLineHeight();
        if (IsScroll != 0) {
            y -= (s32)CurPos;
        }
        bool disp = false;
        if (line >= 0 && line < 8) {
            disp = true;
        }
        winSpriteSetDisp(sprite, disp);
    } else {
        y = item->y + CursorPos * _getItemListLineHeight();
        if (IsScroll == 0) {
            y += (s32)CurPos;
        }
        winSpriteSetDisp(sprite, true);
    }
    sprite->y = y;
    return 0;
}

extern "C" s32 menuPcBoxDouguHikidasuDrawExplanationText(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    GSmsgPrint2(winSpriteGetLayerID(win, sprite), 0, 0, win->color90, ExplanationMsgID);
    return 0;
}

static void setExplanationMsgID(u32 id) {
    ExplanationMsgID = id;
}

extern "C" s32 menuPcBoxDouguHikidashiCursor(void) {
    u16 repeat = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    s32 sel;
    s32 total;
    s32 pos;
    s32 ofs;
    s32 pages;
    if (CurPos != 0.0f) {
        return 0;
    }
    sel = CursorOfs + CursorPos;
    if (IrekaeSlotID < 0) {
        if ((trg & 0xC0) != 0 && getItemIDFromMenuPos(sel) != 0) {
            IrekaeSlotID = sel;
            menuPtPlaySe(0x442);
        }
    } else if ((trg & 0xD0) != 0) {
        if (getItemIDFromMenuPos(sel) != 0) {
            swapItemSlot(IrekaeSlotID, sel);
            menuPtPlaySe(0x442);
        } else {
            menuPtPlaySe(0x443);
        }
        IrekaeSlotID = -1;
    } else if ((trg & 0x20) != 0) {
        IrekaeSlotID = -1;
        menuPtPlaySe(0x443);
    }
    total = getNbItemSlot() + 1;
    ofs = CursorOfs;
    pos = CursorPos;
    pages = (total + 7) / 8;
    if ((repeat & 2) != 0) {
        s32 np = pos + 1;
        CursorPos = np;
        if (np + ofs >= total) {
            CursorPos = np - 1;
        } else {
            if (np >= 8) {
                CursorOfs = ofs + 1;
                CursorPos = np - 1;
                IsScroll = 1;
            } else {
                IsScroll = 0;
            }
            CurPos = -_getItemListLineHeight();
            menuPtPlaySe(0x441);
        }
    } else if ((repeat & 1) != 0) {
        if (pos > 0 || ofs > 0) {
            s32 np = CursorPos - 1;
            CursorPos = np;
            if (np < 0) {
                CursorPos = 0;
                CursorOfs = CursorOfs - 1;
                IsScroll = 1;
            } else {
                IsScroll = 0;
            }
            CurPos = _getItemListLineHeight();
            menuPtPlaySe(0x441);
        }
    } else if ((repeat & 8) != 0) {
        s16 last = total - 8;
        if (pages == 1) {
            CursorPos = (s16)(total - 1);
        } else if (ofs == last) {
            CursorPos = 7;
        } else {
            s32 no = ofs + 8;
            CursorOfs = no;
            if (no > last) {
                CursorOfs = last;
            }
        }
        if (ofs != CursorOfs || pos != CursorPos) {
            menuPtPlaySe(0x444);
        }
    } else if ((repeat & 4) != 0) {
        if (ofs == 0) {
            CursorPos = 0;
        } else {
            s32 no = ofs - 8;
            CursorOfs = no;
            if (no < 0) {
                CursorOfs = 0;
            }
        }
        if (ofs != CursorOfs || pos != CursorPos) {
            menuPtPlaySe(0x444);
        }
    }
    if (ofs != CursorOfs || pos != CursorPos) {
        menuSubCursorAnimeStart();
    }
    u32 msg;
    if (IrekaeSlotID >= 0) {
        msg = 0x3BBC;
    } else if (getItemIDFromMenuPos(CursorOfs + CursorPos) != 0) {
        msg = getItemInstMsg(getItemIDFromMenuPos(CursorOfs + CursorPos));
    } else {
        msg = 0x3BBB;
    }
    setExplanationMsgID(msg);
    return 0;
}

extern "C" void menuPcBoxDouguHikidashiButton(void) {
    if (IrekaeSlotID < 0) {
        menuButtonNormal();
    }
}

extern "C" s32 menuPcBoxDouguHikidashiCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            u32 msg;
            winSeqSetMenu(0x8B, 0x90);
            u16 id = getItemIDFromMenuPos(CursorOfs + CursorPos);
            if (id != 0) {
                msg = getItemInstMsg(id);
            } else {
                msg = 0x3BBB;
            }
            setExplanationMsgID(msg);
            s32 none = -1;
            IsScroll = 0;
            CurPos = 0.0f;
            IrekaeSlotID = none;
            win->step = 1;
            menuSubCursorAnimeInit(none);
        }
        break;
    case 2:
        if (CurPos > 0.0f) {
            CurPos = CurPos - (f32)(_getItemListLineHeight() / 4);
            if (CurPos < 0.0f) {
                CurPos = 0.0f;
            }
        }
        if (CurPos < 0.0f) {
            CurPos = CurPos + (f32)(_getItemListLineHeight() / 4);
            if (CurPos > 0.0f) {
                CurPos = 0.0f;
            }
        }
        _RollUpTime = _RollUpTime + 0.033333335f;
        if (_RollUpTime > 1.0f) {
            _RollUpTime = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x8B, 0x94);
            win->step = 1;
        }
        break;
    }
    return 0;
}

static void suteru(int pos) {
    s32 num;
    u16 id;
    id = getItemIDFromMenuPos(pos);
    if (getItemKind(id) == 5) {
        menuPtPlaySe(0x13);
        winMsgOpen(2, 0x3BC5, 1, 0);
        winMsgClose(1);
        return;
    }
    setExplanationMsgID(0x3BBE);
    num = menuPcBoxDouguNum(1, getItemNumFromMenuPos(pos));
    if (num > 0) {
        msgctrlSetValue(0x2D, id);
        msgctrlSetValue(0x2F, num);
        setExplanationMsgID(0x3BBF);
        if (menuPcBoxDouguConfirm() != 0) {
            pcboxDelItem(0, id, num);
            msgctrlSetValue(0x2D, id);
            msgctrlSetValue(0x2F, num);
            winMsgOpen(2, 0x3BC4, 1, 0);
            winMsgClose(1);
        }
    }
}

static void hikidasu(int pos) {
    u16 id = getItemIDFromMenuPos(pos);
    s32 num;
    setExplanationMsgID(0x3BBD);
    if (getItemKind(id) != 5) {
        num = menuPcBoxDouguNum(1, getItemNumFromMenuPos(pos));
    } else {
        num = 1;
    }
    if (num > 0) {
        if (heroItemCheckAddItemDataId(0, id) < num) {
            menuPtPlaySe(0x13);
            winMsgOpen(2, 0x3BC2, 1, 0);
            winMsgClose(1);
            return;
        }
        heroItemAddItemDataId(0, id, num, -1);
        pcboxDelItem(0, id, num);
        msgctrlSetValue(0x2D, id);
        msgctrlSetValue(0x2F, num);
        winMsgOpen(2, 0x3BC3, 1, 0);
        winMsgClose(1);
    }
}

void menuPcBoxDouguHikidashi(MENU_PCBOX_DOUGU_HIKIDASHI_MODE mode) {
    s32 sel;
    Mode = mode;
    menuOpen(0x8A, 0);
    fadeSet(2, 0.5f);
    fadeCheck(1);
    for (;;) {
        if (menuOpen(0x8B, 1) == -1) {
            break;
        }
        sel = CursorOfs + CursorPos;
        if (getItemIDFromMenuPos(sel) == 0) {
            break;
        }
        switch (mode) {
        case MENU_PCBOX_DOUGU_HIKIDASHI_MODE_0:
            hikidasu(sel);
            break;
        case MENU_PCBOX_DOUGU_HIKIDASHI_MODE_1:
            suteru(sel);
            break;
        }
    }
    menuClose(0x8B);
    menuCloseSync(0x8B, 1);
    fadeSet(3, 0.5f);
    fadeCheck(1);
    menuClose(0x8A);
}

static s32 _getItemListLineHeight(void) {
    return 0x22;
}

extern "C" s32 menuPcBoxDouguConfirmDrawCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 y = win->selected * 0x22;
    MENU_ITEM_dd_ *item = menuPtItemGetBySpriteWork(win, sprite);
    if (sprite->id == 0x4BA) {
        s32 anim;
        if (beforCursorPosition != win->selected) {
            menuSubCursorAnimeStart();
        }
        s32 pair[2] = {0, 0};
        anim = -1;
        if (win->menu == windowGetActiveID()) {
            menuSubCursorAnimeValGet(pair, &anim);
        }
        windowDrawSpriteCursor(0, y, -1, win, 0xC2, 0, winSpriteGetLayerID(win, sprite), pair, anim);
        winSpriteSetDisp(sprite, false);
        beforCursorPosition = win->selected;
    } else {
        sprite->y = item->y + y;
    }
    return 0;
}

static s32 menuPcBoxDouguConfirm(void) {
    s32 ret;
    ((void (*)(void))menuSubCursorAnimeInit)();
    beforCursorPosition = 0;
    ret = menuOpen(0x8D, 1);
    menuClose(0x8D);
    menuCloseSync(0x8D, 1);
    s32 result;
    if (ret == -1) {
        result = 0;
    } else if (ret == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

extern "C" s32 fn_8006A84C(void) {
    return 0;
}
