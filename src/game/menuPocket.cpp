#include <game/menuPocketLayout.hpp>

extern "C" {
u32 cursorBiosGetPos(u16);
void cursorBiosSetPos(u16, s32 *);
void winMsgOpen(s32, u32, s32, s32);
void winMsgOpenWithSE(s32, s32, s32, s32, u8);
void winMsgClose(s32);
void msgctrlSetValue(s32, s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, u32);
s32 heroGetStatus(Hero *, s32, s32);
u32 *heroItemGetItemKindToItemAryPtr(Hero *, u8, u16 *, u16 *, s32, s32);
u32 *heroHizukiItemGetItemAryPtr(Hero *, u16 *, s32, s32, s32);
void heroItemDecItemDataId(Hero *, u16, u16, s16);
u32 itemDataBiosGetPtr(u16);
u16 itemDataBiosGetPrice(u32);
u8 itemDataBiosGetKind(u32);
u8 itemDataBiosGetDeposit(u32);
u32 itemDataBiosGetName(u32);
u32 itemDataBiosGetDoc(u32);
u32 itemDataBiosGetBattleUseFunc(u32);
u32 itemDataBiosGetFieldUseFunc(u32);
u8 itemDataBiosGetImportant(u32);
u8 itemDataBiosGetHidenMachineNo(u32);
u32 itemDataBiosGetWazaMachineNo(u32);
s32 itemDataBiosGetKinomiNo(u16);
u32 itemDataBiosGetWazaIDByWazaMachineNo(u8);
u32 wazaDataBiosGetPtr(u16);
u32 wazaDataBiosGetName(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, s32, u32);
void GSmsgPrintRight(s32, s32, s32, s16, s16, s32, u32);
void GSsndPlay(s32, s32, s32);
void heroAddPokedoru(Hero *, s32);
s8 menuSubOpenYesNo(s32, s32, s32, s32);
void pcboxAddItem(s32, u16, u16);
u16 pcboxGetItemCapacity(s32, u16);
void menuPokemonClose(void);
s32 menuPokemonOpenItemGive(u8, u8, u16, s32);
s32 menuPokemonOpenItemUse(s32, s32, s32, s32);
void menuOffScreenSetPriority(s32);
void menuCloseCustom(s32, s32, s32);
void fadeSet(s32, f32);
void fadeCheck(s32);
void GSfloorPop(void);
void GSfloorPush(s32, void *);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
u8 winSeqCheckMove(s32);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
void menuButtonNormal(tagWINDOW_WORK *);
void spriteSetScissor(s32, s32, s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
f32 timeGetLastFrameSec(void);
void menuSubCursorAnimeInit(void);
void menuSubCursorAnimeMain(void);
void menuSubCursorAnimeStart(void);
void menuSubCursorAnimeValGet(void *, s32 *);
void menuSubDrawCursorBack2(s32, s32, s32, s16, s16, u8, s32, s32);
void windowDrawSpriteCursor(s32, s16, s32, tagWINDOW_WORK *, s32, s32, s32, void *, s32);
void *fightTrainerBiosGetFightPokemonPtr(s32, s32);
void *fightPokemonGetPokemonPtr(void *);
Hero *fightTrainerBiosGetHeroPtr(s32);
void *memset(void *, int, u32);
void *memmove(void *, const void *, u32);
u16 menuPocketCologne(s32);
void menuPocketBattleDiskMain(s32, s32, Hero *);
s32 menuPocketInputNumber(tagWINDOW_WORK *, s32, s32, u16, s32, s32, s32);
u8 itemCheckValid(u32 *);
u16 itemBiosGetNum(u32 *);
u16 itemBiosGetItemDataId(u32 *);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, void *, s32, s32, s32, ...);
void menuClose(s32);
void menuCloseSync(s32, s32);
}

void menuPocketToolFloatToZero(f32 &, f32);

PocketData Data;
struct PocketScriptEntry {
    u16 id;
    u16 reserved;
    u32 value;
};
struct PocketScriptWork {
    PocketScriptEntry entries[8];
    s32 count;
};
static PocketScriptWork menuPocketWork;

void menuPtPlaySe(u32);

namespace {

u16 _getItemIDFromMenuPos(int tab, int pos);
void _printItemDouguBall(GSgfxLayerID, int, int, int, int);
void _printItemWazaMachine(GSgfxLayerID, int, int, int, int);
void _printItemKinomi(GSgfxLayerID, int, int, int, int);
void _printItemTaisetsu(GSgfxLayerID, int, int, int, int);
int _actTukauNormal(int, int, int *);
int _actMotaseruNormal(int, int, int *);
int _actSuteruNormal(int, int, int *);
u8 _getItemDeposit(u16 item);

const SActionMenuItem ActionMenuDouguField[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4293, _actMotaseruNormal, 2, 0 },
    { 0x4294, _actSuteruNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuBallField[] = {
    { 0x4293, _actMotaseruNormal, 0, 0 },
    { 0x4294, _actSuteruNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuWazaMachineField[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4293, _actMotaseruNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuKinomiField[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4293, _actMotaseruNormal, 0, 0 },
    { 0x4294, _actSuteruNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuTaisetuField[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuDouguBattle[] = {
    { 0x4292, _actTukauNormal, 1, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuBallBattle[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuWazaMachineBattle[] = {
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuKinomiBattle[] = {
    { 0x4292, _actTukauNormal, 0, 0 },
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const SActionMenuItem ActionMenuTaisetuBattle[] = {
    { 0x4295, 0, 0, 0 },
    { 0, 0, 0, 0 }
};

const PocketTab TabTbl[5] = {
    { 2, 1, 1, 0, 0x97, 0x9F, _printItemDouguBall, 3, { 0, 0 }, 0x3A99, ActionMenuDouguField, ActionMenuDouguBattle },
    { 1, 1, 1, 0, 0x98, 0x9E, _printItemDouguBall, 4, { 0, 0 }, 0x3A9A, ActionMenuBallField, ActionMenuBallBattle },
    { 4, 0, 0, 0, 0x99, 0x9D, _printItemWazaMachine, 5, { 0, 0 }, 0x3A9B, ActionMenuWazaMachineField, ActionMenuWazaMachineBattle },
    { 3, 0, 0, 0, 0x9A, 0x9C, _printItemKinomi, 6, { 0, 0 }, 0x3A9C, ActionMenuKinomiField, ActionMenuKinomiBattle },
    { 5, 1, 0, 0, 0x158, 0x9B, _printItemTaisetsu, 7, { 0, 0 }, 0x3A9D, ActionMenuTaisetuField, ActionMenuTaisetuBattle }
};

}

extern "C" {
bool fn_8002208C(tagWINDOW_WORK *);
bool fn_80022128(tagWINDOW_WORK *);
}

bool fn_8002208C(tagWINDOW_WORK *win) {
    CURSOR cursor;
    s32 index;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    if (Data.swapIndex >= 0) {
        return false;
    }
    index = cursor.first + cursor.selected;
    if (_getItemIDFromMenuPos(win->selected, index) == 0 && index == 0) {
        return false;
    }
    return true;
}

bool fn_80022128(tagWINDOW_WORK *win) {
    CURSOR cursor;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    if (_getItemIDFromMenuPos(win->selected, cursor.first + cursor.selected) == 0 && Data.swapIndex < 0) {
        return false;
    }
    return true;
}

namespace {

void _infoOnly(u32 msg) {
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

void _infoBeep(u32 msg) {
    menuPtPlaySe(0x13);
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

struct ActMenuResizeWorkEntry {
    u32 id;
    s16 width;
    s16 height;
    u8 flag;
    u8 reserved9[3];
};

ActMenuResizeWorkEntry ActMenuResizeWork[7] = {
    { 0xCF, 0, 0, 1 },
    { 0xD0, 0, 0, 0 },
    { 0xD1, 0, 0, 0 },
    { 0xD5, 0, 0, 1 },
    { 0xD4, 0, 0, 1 },
    { 0xD6, 0, 0, 0 },
    { 0xD9, 0, 0, 0 }
};

void _setActMenuResizeWork() {
    u32 i;
    for (i = 0; i < 7; i++) {
        ActMenuResizeWork[i].width = menuItemBiosGetPtr(0x2C, ActMenuResizeWork[i].id)->y;
        ActMenuResizeWork[i].height = menuItemBiosGetPtr(0x2C, ActMenuResizeWork[i].id)->height;
    }
}

s32 _getMoney() {
    return heroGetStatus(Data.hero, 0xC, 0);
}

void _sortItemsThisTab(u8 tab) {
    Data.hero->itemSort(tab);
}

void _decItem(u16 item, int tab, int index, int num) {
    heroItemDecItemDataId(Data.hero, item, num, index);
}

s32 _getItemPrice(int item) {
    return itemDataBiosGetPrice(itemDataBiosGetPtr(item));
}

u32 (*_getUseFunc(u32 item))(u32) {
    u32 data = itemDataBiosGetPtr(item);
    if (Data.mode == 0) {
        return (u32 (*)(u32))itemDataBiosGetFieldUseFunc(data);
    }
    return (u32 (*)(u32))itemDataBiosGetBattleUseFunc(data);
}

int _makeActMenu(SActionMenuItem *dst, int max, int tab, int index) {
    u32 data;
    u8 battleUse;
    const PocketTab *tabEntry;
    const SActionMenuItem *src;
    const SActionMenuItem *p;
    const SActionMenuItem *q;
    SActionMenuItem *out;
    int n;
    int count;
    int i;
    data = itemDataBiosGetPtr(_getItemIDFromMenuPos(tab, index));
    if (itemDataBiosGetBattleUseFunc(data) != 0) {
        battleUse = 1;
    } else {
        battleUse = 0;
    }
    tabEntry = &TabTbl[Data.tab];
    if (Data.mode == 1 || Data.mode == 6) {
        src = tabEntry->battle;
    } else if (Data.mode == 0) {
        src = tabEntry->field;
    }
    q = src;
    n = 0;
    while (q->func != 0) {
        q++;
        n++;
    }
    p = src;
    out = dst;
    count = 0;
    for (i = 0; i < n + 1; i++, p++) {
        if (((p->flags & 1) == 0 || battleUse != 0) && (itemDataBiosGetImportant(data) == 0 || (p->flags & 2) == 0)) {
            count++;
            out->msg = p->msg;
            out->func = p->func;
            out->flags = p->flags;
            out->flags = 0;
            out++;
        }
    }
    return count;
}

void _setExplanationMsgID(u32 msg) {
    Data.msg = msg;
}

u32 _getItemNameMsg(u32 item) {
    return itemDataBiosGetName(itemDataBiosGetPtr(item));
}

u32 _getItemInstMsg(u32 item) {
    return itemDataBiosGetDoc(itemDataBiosGetPtr(item));
}

}

namespace {

u16 _getItemIDFromMenuPos(int tab, int pos) {
    u16 count;
    u32 *ary;
    int found;
    int i;
    ary = heroItemGetItemKindToItemAryPtr(Data.hero, TabTbl[tab].kind, &count, 0, 0, 0);
    found = -1;
    for (i = 0; i < count; i++, ary++) {
        if (itemCheckValid(ary) != 0) {
            found++;
            if (found >= pos) {
                return itemBiosGetItemDataId(ary);
            }
        }
    }
    return 0;
}

u16 _getItemNumFromMenuPos(int tab, int pos) {
    u16 count;
    u32 *ary;
    int i;
    int found;
    int kind = TabTbl[tab].kind;
    if (kind >= 0) {
        ary = heroItemGetItemKindToItemAryPtr(Data.hero, kind, &count, 0, 0, 0);
    } else {
        ary = heroHizukiItemGetItemAryPtr(Data.hero, &count, 0, 0, 0);
    }
    found = -1;
    for (i = 0; i < count; i++, ary++) {
        if (itemCheckValid(ary) != 0) {
            found++;
            if (found >= pos) {
                return itemBiosGetNum(ary);
            }
        }
    }
    return 0;
}

int _getStockMaxFromTagID(int tab) {
    u16 stock;
    heroItemGetItemKindToItemAryPtr(Data.hero, TabTbl[tab].kind, 0, &stock, 0, 0);
    return stock;
}

int _getNbItemSlot(int tab) {
    u16 count;
    u32 *ary;
    int i;
    int n;
    int kind = TabTbl[tab].kind;
    if (kind >= 0) {
        ary = heroItemGetItemKindToItemAryPtr(Data.hero, kind, &count, 0, 0, 0);
    } else {
        ary = heroHizukiItemGetItemAryPtr(Data.hero, &count, 0, 0, 0);
    }
    n = 0;
    for (i = 0; i < count; i++, ary++) {
        if (itemCheckValid(ary) != 0) {
            n++;
        }
    }
    return n;
}

int _actionMenuOpen(const SActionMenuItem *items, int count) {
    const SActionMenuItem *args[2];
    int result;
    args[0] = items;
    *(int *)&args[1] = count;
    result = menuOpenCustom(0x2D, windowGetActiveID(), 0, 0, 1, 1, args);
    menuClose(0x2D);
    menuCloseSync(0x2D, 1);
    if (result == -1) {
        return -1;
    }
    if (result < 0 || result >= count) {
        return -1;
    }
    return result;
}

int _openNumberInputMenu(int init, int max, int digits, int price) {
    s32 params[3];
    s32 mode[1];
    s32 menu;
    s32 result;
    s32 num;
    if (max < 0) {
        return 0;
    }
    if (price > 0) {
        if (digits == 2) {
            menu = 0x30;
            mode[0] = 1;
        } else {
            menu = 0x31;
            mode[0] = 2;
        }
    } else if (digits == 2) {
        menu = 0x2E;
        mode[0] = 1;
    } else {
        menu = 0x2F;
        mode[0] = 2;
    }
    params[0] = menu;
    params[1] = max;
    params[2] = price;
    Data.num = init;
    result = menuOpenCustom(menu, windowGetActiveID(), mode, 0, 1, 1, params);
    menuClose(menu);
    menuCloseSync(menu, 1);
    if (result == -1 || (num = Data.num) == 0) {
        num = -1;
    }
    return num;
}

}

namespace {

int _execDeposit(int tab, u16 item, int index);
u8 _depositPC(u16 item, int num);
u8 _IsSortAble(tagWINDOW_WORK *win);
u8 _IsIrekaeAble(tagWINDOW_WORK *win);
int _swapItemSlot(int, int, int);

u8 _depositPC(u16 item, int num) {
    if (pcboxGetItemCapacity(0, item) < num) {
        return 0;
    }
    pcboxAddItem(0, item, num);
    return 1;
}

int _execDeposit(int tab, u16 item, int index) {
    int digits;
    int num;
    if (_getItemDeposit(item) == 0) {
        msgctrlSetValue(0x2D, item);
        _infoBeep(0xC37B);
        return 0;
    }
    if ((u8)TabTbl[Data.tab].kind != 5) {
        _setExplanationMsgID(0x3AAC);
        if (_getStockMaxFromTagID(tab) > 0x64) {
            digits = 3;
        } else {
            digits = 2;
        }
        num = _openNumberInputMenu(1, _getItemNumFromMenuPos(tab, index), digits, 0);
    } else {
        num = 1;
    }
    if (num < 0) {
        return 0;
    }
    if (_depositPC(item, num) == 0) {
        msgctrlSetValue(0x2D, item);
        _infoBeep(0x3AC0);
        return 0;
    }
    _decItem(item, TabTbl[Data.tab].kind, index, num);
    msgctrlSetValue(0x2D, item);
    msgctrlSetValue(0x2F, num);
    _infoOnly(0xC37C);
    return 1;
}

}

extern "C" s32 menuShopGetMsgID(u8 *, s32, s32, s32, ...);

namespace {

int _execSell(int tab, u16 item, int index) {
    u8 sprite;
    int shop = Data.shop;
    int price = _getItemPrice(item);
    int digits;
    int half;
    int num;
    int cost;
    int answer;
    if (price <= 0) {
        menuPtPlaySe(0x13);
        winMsgOpenWithSE(2, menuShopGetMsgID(&sprite, shop, 0xB, 0x2D, item, -1), 1, 0, sprite);
        winMsgClose(1);
        return 0;
    }
    _setExplanationMsgID(menuShopGetMsgID(&sprite, shop, 0xD, 0x2D, item, -1));
    if (_getStockMaxFromTagID(tab) > 0x64) {
        digits = 3;
    } else {
        digits = 2;
    }
    num = _openNumberInputMenu(1, _getItemNumFromMenuPos(tab, index), digits, half = price / 2);
    if (num < 0) {
        return 0;
    }
    cost = half * num;
    winMsgOpenWithSE(2, menuShopGetMsgID(&sprite, shop, 9, 0x4B, cost, -1), 1, 0, sprite);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    if (answer == 1 || answer == -1) {
        winMsgClose(1);
        return 0;
    }
    _decItem(item, TabTbl[Data.tab].kind, index, num);
    GSsndPlay(0x1A, 0, 0);
    heroAddPokedoru(Data.hero, cost);
    _infoOnly(menuShopGetMsgID(&sprite, shop, 0xA, 0x2D, item, 0x4B, cost, -1));
    return 1;
}

int _execGive(int tab, u16 item, int index) {
    if (itemDataBiosGetImportant(itemDataBiosGetPtr(item)) != 0) {
        msgctrlSetValue(0x2D, item);
        _infoBeep(0xC37A);
        return 0;
    }
    Data.lastSlot = index;
    return 1;
}

int _swapItemSlot(int kind, int from, int to) {
    u16 count;
    u16 saved[2];
    u32 *ary;
    u32 *src;
    u32 *dst;
    if (from != to) {
        if (from == to - 1) {
            return 0;
        }
        ary = heroItemGetItemKindToItemAryPtr(Data.hero, kind, &count, 0, 0, 0);
        src = ary + from;
        *(u32 *)saved = *src;
        if (from != count - 1) {
            memmove(src, src + 1, (count - from - 1) * 4);
        }
        if (from < to) {
            to--;
        }
        dst = ary + to;
        memmove(dst + 1, dst, (count - to - 1) * 4);
        ((u16 *)dst)[0] = saved[0];
        ((u16 *)dst)[1] = saved[1];
    }
    return 0;
}

bool _openPokemonMenuForGiveItem(u16 item, u8 kind, u8 index) {
    menuCloseCustom(0x2C, 0, 1);
    Data.pokemonSlot = menuPokemonOpenItemGive(kind, index, item, 0);
    menuOffScreenSetPriority(0);
    menuPokemonClose();
    return Data.pokemonSlot >= 0;
}

u8 _getItemKind(int item) {
    return itemDataBiosGetKind(itemDataBiosGetPtr(item));
}

u8 _getItemDeposit(u16 item) {
    return itemDataBiosGetDeposit(itemDataBiosGetPtr(item));
}

int _actSuteruNormal(int tab, int index, int *dec) {
    const SActionMenuItem yesNo[2] = { { 0x426A, 0, 0, 0 }, { 0x426B, 0, 0, 0 } };
    int digits;
    int num;
    u16 item;
    int answer;
    _setExplanationMsgID(0x3AAA);
    if (_getStockMaxFromTagID(tab) > 0x64) {
        digits = 3;
    } else {
        digits = 2;
    }
    num = _openNumberInputMenu(1, _getItemNumFromMenuPos(tab, index), digits, 0);
    if (num < 0) {
        *dec = 0;
        return 0;
    }
    item = _getItemIDFromMenuPos(tab, index);
    msgctrlSetValue(0x2D, item);
    msgctrlSetValue(0x2F, num);
    _setExplanationMsgID(0x3AAB);
    answer = _actionMenuOpen(yesNo, 2);
    if (answer == 1 || answer == -1) {
        *dec = 0;
        return 0;
    }
    msgctrlSetValue(0x2D, item);
    msgctrlSetValue(0x2F, num);
    _infoOnly(0xC379);
    *dec = num;
    return 0;
}

int _actMotaseruNormal(int tab, int index, int *dec) {
    u16 item = _getItemIDFromMenuPos(tab, index);
    if (itemDataBiosGetHidenMachineNo(itemDataBiosGetPtr(item)) != 0xFF) {
        msgctrlSetValue(0x2D, item);
        _infoBeep(0xC37A);
        *dec = 0;
        return 0;
    }
    u8 kind = _getItemKind(item);
    if (_openPokemonMenuForGiveItem(item, kind, index) == 0) {
        return 1;
    }
    *dec = 0;
    return 0;
}

int _actTukauNormal(int tab, int index, int *dec) {
    int result;
    u16 item = _getItemIDFromMenuPos(tab, index);
    int (*func)(u16, int *) = (int (*)(u16, int *))_getUseFunc(item);
    int ret;
    if (func == 0) {
        _infoBeep(0xC374);
        *dec = 0;
        return 1;
    }
    result = func(item, dec);
    switch (result) {
    case 0:
        ret = 0;
        break;
    case 1:
        ret = 1;
        break;
    case 2:
        if (tab == 4 && item != 0x1F6) {
            ret = 0;
        } else {
            ret = 2;
        }
        break;
    }
    return ret;
}

}

namespace {

int _execActionMenu(int tab, u16 item, int index, u16 *used) {
    SActionMenuItem items[5];
    int dec;
    int count;
    int sel;
    int result;
    u16 cologne;
    u32 id;
    int (*func)(u16, int *);
    *used = 0;
    if (Data.mode == 0) {
        if (item == 0x215) {
            _setExplanationMsgID(0x3C1B);
            menuPocketBattleDiskMain(-1, Data.fightId, Data.hero);
            return 1;
        }
        if (item == 0x200) {
            _setExplanationMsgID(0x3AB8);
            cologne = menuPocketCologne(-1);
            id = cologne;
            if (id == 0) {
                return 1;
            }
            *used = cologne;
            func = (int (*)(u16, int *))_getUseFunc(id);
            if (func == 0) {
                _infoBeep(0xC374);
                return 0;
            }
            if (func(id, &dec) == 2) {
                if (dec > 0) {
                    _decItem(cologne, 6, -1, dec);
                }
                return 2;
            }
            return 1;
        }
    }
    count = _makeActMenu(items, 4, tab, index);
    _setExplanationMsgID(0x4296);
    sel = _actionMenuOpen(items, count);
    if (sel < 0) {
        return 1;
    }
    if (items[sel].func == 0) {
        return 1;
    }
    result = items[sel].func(tab, index, &dec);
    switch (result) {
    case 0:
        if (dec > 0) {
            _decItem(item, TabTbl[Data.tab].kind, index, dec);
        }
        Data.lastSlot = index;
        return 0;
    case 1:
        return 1;
    case 2:
        if (dec > 0) {
            _decItem(item, TabTbl[Data.tab].kind, index, dec);
        }
        return 2;
    default:
        return 0;
    }
}

int _afterDecideItem(int mode, int tab, u16 item, int index, u16 *used) {
    u16 cologne = 0;
    int result;
    switch (mode) {
    default:
        result = _execActionMenu(tab, item, index, &cologne);
        if (result == 2) {
            mode = 1;
        } else if (mode == 0) {
            mode = 0;
        } else if (result == 0) {
            mode = 1;
        } else {
            mode = 0;
        }
        break;
    case 5:
    case 2:
        if (_execGive(tab, item, index) != 0) {
            mode = 1;
        } else {
            mode = 0;
        }
        break;
    case 3:
        _execSell(tab, item, index);
        mode = 0;
        break;
    case 4:
        _execDeposit(tab, item, index);
        mode = 0;
        break;
    }
    *used = cologne;
    return mode;
}

u8 _IsSortAble(tagWINDOW_WORK *win) {
    if (Data.mode == 3 || Data.mode == 4 || Data.mode == 5) {
        return 0;
    }
    return TabTbl[win->selected].sortable;
}

u8 _IsIrekaeAble(tagWINDOW_WORK *win) {
    if (Data.mode == 3 || Data.mode == 4 || Data.mode == 5) {
        return 0;
    }
    return TabTbl[win->selected].irekae;
}

u16 _selectItem(int &index, long *param) {
    CURSOR cursor;
    int tab;
    Data.swapIndex = -1;
    tab = menuOpenCustom(0x2C, windowGetActiveID(), param, 0, 1, 0);
    if (tab == -1) {
        return 0;
    }
    Data.tab = tab;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[tab].cursorId);
    index = cursor.first + cursor.selected;
    return _getItemIDFromMenuPos(tab, index);
}

}

namespace {

void _printItemDouguBall(GSgfxLayerID layer, int x, int y, int tab, int index) {
    s16 w;
    s32 stock;
    u32 msg = _getItemNameMsg(_getItemIDFromMenuPos(tab, index));
    if (msg != 0) {
        GSmsgPrint2(layer, x, y, -1, msg);
    }
    stock = _getStockMaxFromTagID(tab);
    msgctrlSetValue(0x34, stock);
    w = GSmsgGetRect(0x4270) >> 16;
    w += (s16)(GSmsgGetRect(0x428F) >> 16);
    GSmsgPrint2(layer, (x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w, y, -1, 0x428F);
    msgctrlSetValue(0x34, _getItemNumFromMenuPos(tab, index));
    w = GSmsgGetRect(0x4270) >> 16;
    GSmsgPrint2(layer, ((x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w) + 1, y, -1, 0x4270);
}

void _printItemWazaMachine(GSgfxLayerID layer, int x, int y, int tab, int index) {
    u32 data;
    u8 hiden;
    int pos;
    u8 machineNo;
    int number;
    u8 hidenNo;
    u32 msg;
    u32 nameMsg;
    s32 stock;
    s16 w;
    data = itemDataBiosGetPtr(_getItemIDFromMenuPos(tab, index));
    machineNo = itemDataBiosGetWazaMachineNo(data);
    number = machineNo + 1;
    hiden = itemDataBiosGetHidenMachineNo(data);
    hidenNo = hiden + 1;
    if (hiden != 0xFF) {
        msg = 0x3AA0;
    } else {
        msg = 0x3A9F;
    }
    GSmsgPrint2(layer, x, y, -1, msg);
    pos = x + (GSmsgGetRect(msg) >> 16);
    if (hiden != 0xFF) {
        msgctrlSetValue(0x34, hidenNo);
        GSmsgPrint2(layer, pos, y, -1, 0x4270);
        pos += GSmsgGetRect(0x4270) >> 16;
    } else {
        if (number < 10) {
            msgctrlSetValue(0x34, 0);
            GSmsgPrint2(layer, pos, y, -1, 0x4270);
            pos += GSmsgGetRect(0x4270) >> 16;
        }
        msgctrlSetValue(0x34, number);
        GSmsgPrint2(layer, pos, y, -1, 0x4270);
        pos += GSmsgGetRect(0x4270) >> 16;
    }
    nameMsg = wazaDataBiosGetName(wazaDataBiosGetPtr(itemDataBiosGetWazaIDByWazaMachineNo(machineNo)));
    GSmsgPrint2(layer, pos + 9, y, -1, nameMsg);
    stock = _getStockMaxFromTagID(tab);
    msgctrlSetValue(0x34, stock);
    w = GSmsgGetRect(0x4270) >> 16;
    w += (s16)(GSmsgGetRect(0x428F) >> 16);
    GSmsgPrint2(layer, (x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w, y, -1, 0x428F);
    msgctrlSetValue(0x34, _getItemNumFromMenuPos(tab, index));
    w = GSmsgGetRect(0x4270) >> 16;
    GSmsgPrint2(layer, ((x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w) + 1, y, -1, 0x4270);
}

void _printItemKinomi(GSgfxLayerID layer, int x, int y, int tab, int index) {
    int pos;
    s32 stock;
    u32 nameMsg;
    u16 item;
    u8 number;
    s16 w;
    GSmsgPrint2(layer, x, y, -1, 0x3A9F);
    pos = x + (GSmsgGetRect(0x3A9F) >> 16);
    item = _getItemIDFromMenuPos(tab, index);
    number = itemDataBiosGetKinomiNo(item) + 1;
    if (number < 10) {
        msgctrlSetValue(0x34, 0);
        GSmsgPrint2(layer, pos, y, -1, 0x4270);
        pos += GSmsgGetRect(0x4270) >> 16;
    }
    msgctrlSetValue(0x34, number);
    GSmsgPrint2(layer, pos, y, -1, 0x4270);
    pos += GSmsgGetRect(0x4270) >> 16;
    nameMsg = _getItemNameMsg(item);
    GSmsgPrint2(layer, pos + 9, y, -1, nameMsg);
    stock = _getStockMaxFromTagID(tab);
    msgctrlSetValue(0x34, stock);
    w = GSmsgGetRect(0x4270) >> 16;
    w += (s16)(GSmsgGetRect(0x428F) >> 16);
    GSmsgPrint2(layer, (x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w, y, -1, 0x428F);
    msgctrlSetValue(0x34, _getItemNumFromMenuPos(tab, index));
    w = GSmsgGetRect(0x4270) >> 16;
    GSmsgPrint2(layer, ((x + menuItemBiosGetPtr(0x2C, 0xB4)->width) - w) + 1, y, -1, 0x4270);
}

void _printItemTaisetsu(GSgfxLayerID layer, int x, int y, int tab, int index) {
    u32 msg = _getItemNameMsg(_getItemIDFromMenuPos(tab, index));
    if (msg != 0) {
        GSmsgPrint2(layer, x, y, -1, msg);
    }
}

void _printItemList(GSgfxLayerID layer, int x, int tab, CURSOR &cursor) {
    int nb;
    int y;
    const PocketTab *entry;
    int pos;
    int limit;
    int scroll;
    int i;
    int start;
    entry = &TabTbl[tab];
    nb = _getNbItemSlot(tab);
    pos = cursor.first;
    start = 0;
    limit = 9;
    scroll = 0;
    if (Data.curPos != 0.0f && Data.isScroll != 0) {
        if (Data.curPos < 0.0f) {
            pos--;
            start = -1;
        } else {
            limit = 10;
        }
        scroll = (int)Data.curPos;
    }
    y = start * 30;
    for (i = start; i < limit && pos < nb; y += 30, i++, pos++) {
        if (pos >= 0) {
            entry->print(layer, x, y - scroll, tab, pos);
        }
    }
    if (i < limit) {
        GSmsgPrint2(layer, x, i * 30 - scroll, -1, Data.mode == 4 ? 0x3BBA : 0x3A9E);
    }
}

u16 _menuPocketLoop() {
    s16 cursorState[2];
    s32 params[1];
    CURSOR cursor;
    int index;
    s16 raw[2];
    u16 used;
    u16 item;
    int result;
    s32 *param;
    int i;
    const PocketTab *tab;
    memset(cursorState, 0, 4);
    if (Data.mode == 6) {
        cursorState[1] = 1;
    } else {
        *(u32 *)raw = cursorBiosGetPos(2);
        cursorState[0] = raw[0];
        cursorState[1] = raw[1];
    }
    param = params;
    params[0] = cursorState[1];
    for (tab = TabTbl, i = 0; i < 5; i++, tab++) {
        *(u32 *)&cursor = cursorBiosGetPos(tab->cursorId);
        if (cursor.first + cursor.selected >= _getNbItemSlot(i) + 1) {
            static CURSOR czero = { 0, 0 };
            CURSOR zero = czero;
            cursorBiosSetPos(tab->cursorId, (s32 *)&zero);
        }
    }
    if (Data.resizeInit == 0) {
        _setActMenuResizeWork();
    }
    index = 0;
    for (;;) {
        Data.selecting = 1;
        item = _selectItem(index, (long *)param);
        Data.selecting = 0;
        param = 0;
        if (item == 0) {
            break;
        }
        result = _afterDecideItem(Data.mode, Data.tab, item, index, &used);
        if (used != 0) {
            item = used;
        }
        switch (result) {
        case 1:
            goto done;
        case 0:
        case 2:
            break;
        }
    }
done:
    menuCloseCustom(0x2C, 0, 1);
    if (Data.mode == 4) {
        fadeSet(3, 0.5f);
        fadeCheck(1);
    }
    if (Data.floorPop != 0) {
        menuOffScreenSetPriority(1);
        GSfloorPop();
        floorSetFadeScript(0, 0);
    }
    return item;
}

}

struct MenuPocket2NumEntry {
    s32 menu;
    const s32 *items;
    s32 count;
};

namespace {

const s32 NumWinItem2[6] = { 0xE7, 0xE5, 0, 0xE8, 0xE6, 0 };
const s32 NumWinItem3[9] = { 0xF1, 0xEE, 0, 0xF2, 0xEF, 0, 0xF3, 0xF0, 0 };
const s32 NumPriceWinItem2[6] = { 0x100, 0xFE, 0, 0x101, 0xFF, 0 };
const s32 NumPriceWinItem3[9] = { 0x3AA, 0x3A7, 0, 0x3AB, 0x3A8, 0, 0x3AC, 0x3A9, 0 };
const MenuPocket2NumEntry MenuPocket2Num[4] = {
    { 0x2E, NumWinItem2, 2 },
    { 0x2F, NumWinItem3, 3 },
    { 0x30, NumPriceWinItem2, 2 },
    { 0x31, NumPriceWinItem3, 3 }
};

}

int _actionMenuLineHeight(tagWINDOW_WORK *win);

struct PocketNumArg {
    s32 menu;
    s32 max;
    s32 price;
};

struct PocketActArg {
    const SActionMenuItem *items;
    s32 count;
};

extern "C" {

s32 menuPocket2PrintExplanation(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    u32 msg;
    cursorBiosGetPos(TabTbl[win->selected].cursorId);
    msg = Data.msg;
    if (msg != 0) {
        GSmsgPrint2(winSpriteGetLayerID(win, spr), 0, 0, -1, msg);
    }
    return 0;
}

void menuPocket2GetHero(Hero **hero, s32 *fightId) {
    *hero = Data.hero;
    *fightId = Data.fightId;
}

s32 menuPocket2GetCurrentTemochiPokemonSlotID(void) {
    return Data.pokemonSlot = Data.pokemonSlot2;
}

void menuPocket2GetTemochiPokemon(u16 slot, void **pokemon, void **fight) {
    void *f;
    void *p;
    if (Data.mode == 1 || Data.mode == 6) {
        f = fightTrainerBiosGetFightPokemonPtr(Data.fightId, slot);
        p = fightPokemonGetPokemonPtr(f);
    } else {
        p = (void *)heroGetStatus(Data.hero, 3, slot);
        f = 0;
    }
    *pokemon = p;
    *fight = f;
}

void menuPocket2ClosePokemonMenu(s32 slot) {
    Data.pokemonSlot = slot;
    menuPokemonClose();
}

s32 menuPocket2OpenPokemonMenu(u16 item, s32 use) {
    s32 kind;
    s32 result;
    menuCloseCustom(0x2C, 0, 1);
    if (Data.mode == 1 || Data.mode == 6) {
        kind = 4;
    } else {
        kind = 3;
    }
    result = menuPokemonOpenItemUse(kind, use != 0, item, Data.fightId);
    if (use == 0) {
        result = -1;
    }
    return result;
}

s32 menuPocket2PrintPrice(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    s16 w;
    s32 price = ((PocketNumArg *)(void *)win->parameters[0])->price;
    if (price <= 0) {
        return 0;
    }
    msgctrlSetValue(0x50, price * Data.num);
    w = GSmsgGetRect(0x434F) >> 16;
    GSmsgPrint2(winSpriteGetLayerID(win, spr), spr->width - w, 0, -1, 0x434F);
    return 0;
}

s32 menuPocket2NumCtrl(tagWINDOW_WORK *win) {
    s32 *arg = (s32 *)(void *)win->parameters[0];
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(*arg, 0x70);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(*arg, 0x74);
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 menuPocket2DrawTitleLR(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    winSpriteSetDisp(spr, (u32)((6 - Data.mode) | (Data.mode - 6)) >> 31);
    return 0;
}

void menuPocket2Button(tagWINDOW_WORK *win) {
    if (Data.swapIndex >= 0) {
        return;
    }
    if (winSeqCheckMove(win->menu) != 0) {
        return;
    }
    if ((windowGetKeyTrg() & 0x10) != 0) {
        menuPtPlaySe(0x11);
    }
    menuButtonNormal(win);
}

s32 menuPocket2DrawRHelpText(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    u32 disp = 0;
    if (_IsSortAble(win) != 0 && Data.selecting != 0 && fn_8002208C(win) != 0) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuPocket2DrawXHelpText(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    u32 disp = 0;
    if (_IsIrekaeAble(win) != 0 && Data.selecting != 0 && fn_80022128(win) != 0) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuPocket2DrawRHelp(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    u32 disp = 0;
    if (_IsSortAble(win) != 0 && Data.selecting != 0 && fn_8002208C(win) != 0) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuPocket2DrawXHelp(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    u32 disp = 0;
    if (_IsIrekaeAble(win) != 0 && Data.selecting != 0 && fn_80022128(win) != 0) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuPocket2PrintMoney(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    s16 w;
    s32 money = _getMoney();
    if (Data.mode != 3) {
        return 0;
    }
    msgctrlSetValue(0x50, money);
    w = GSmsgGetRect(0x434E) >> 16;
    GSmsgPrint2(winSpriteGetLayerID(win, spr), spr->width - w, 0, -1, 0x434E);
    return 0;
}

s32 menuPocket2DrawMoneyBack(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    if (Data.mode != 3) {
        spr->color.channels.alpha = 0;
    } else {
        spr->color.channels.alpha = 0xFF;
    }
    return 0;
}

s32 menuPocket2DrawMoney(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    if (Data.mode != 3) {
        spr->color.channels.alpha = 0;
    } else {
        spr->color.channels.alpha = 0xFF;
    }
    return 0;
}

s32 menuPocket2PrintNumMenu(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    s32 *arg = (s32 *)win->parameters[0];
    u32 i;
    const s32 *p;
    s32 idx;
    s32 j;
    s32 div;
    for (i = 0; i < 4; i++) {
        if (arg[0] == MenuPocket2Num[i].menu) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    p = MenuPocket2Num[i].items;
    for (idx = 0; idx < MenuPocket2Num[i].count; idx++, p += 3) {
        if ((s16)spr->id == *p) {
            break;
        }
    }
    if (idx >= MenuPocket2Num[i].count) {
        return 0;
    }
    div = 1;
    for (j = 0; j < MenuPocket2Num[i].count - idx - 1; j++) {
        div *= 10;
    }
    {
        s32 digit = Data.num / div % 10;
        msgctrlSetValue(0x34, digit);
    }
    GSmsgPrintRight(winSpriteGetLayerID(win, spr), 0, 0, spr->width, spr->height, -1, 0x4270);
    return 0;
}

s32 menuPocket2PrintItemKind(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    MENU_ITEM_dd_ *area;
    MENU_ITEM_dd_ *self;
    s16 w;
    s32 msg;
    s32 half;
    s16 tw;
    area = menuItemBiosGetPtr(win->menu, 0xB7);
    self = menuItemBiosGetPtr(win->menu, spr->id);
    spriteSetScissor(winSpriteGetLayerID(win, spr), area->x - self->x, area->y - self->y, area->width, area->height);
    w = spr->width;
    msg = TabTbl[win->selected].unk14;
    half = w / 2;
    tw = GSmsgGetRect(msg) >> 16;
    GSmsgPrint2(winSpriteGetLayerID(win, spr), (s32)Data.tabScroll + (half - tw / 2), 0, -1, msg);
    if (Data.tabScroll != 0.0f) {
        s32 idx;
        f32 off;
        s32 msg2;
        s16 tw2;
        if (Data.tabScroll > 0.0f) {
            idx = win->selected - 1;
            if (idx < 0) {
                idx = 4;
            }
            off = Data.tabScroll - (f32)menuItemBiosGetPtr(0x2C, 0xB6)->width;
        } else {
            idx = win->selected + 1;
            if ((u32)idx >= 5) {
                idx = 0;
            }
            off = Data.tabScroll + (f32)menuItemBiosGetPtr(0x2C, 0xB6)->width;
        }
        const PocketTab *tab2 = TabTbl + idx;
        msg2 = tab2->unk14;
        tw2 = GSmsgGetRect(msg2) >> 16;
        GSmsgPrint2(winSpriteGetLayerID(win, spr), (s32)off + (half - tw2 / 2), 0, -1, msg2);
    }
    spriteClearScissor(winSpriteGetLayerID(win, spr));
    spriteSetEnv(winSpriteGetLayerID(win, spr));
    return 0;
}

s32 menuPocket2PrintItemList(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    CURSOR cursor2;
    MENU_ITEM_dd_ *area;
    MENU_ITEM_dd_ *self;
    area = menuItemBiosGetPtr(win->menu, 0xB6);
    self = menuItemBiosGetPtr(win->menu, spr->id);
    spriteSetScissor(winSpriteGetLayerID(win, spr), area->x - self->x, area->y - self->y, area->width, area->height);
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    _printItemList((GSgfxLayerID)winSpriteGetLayerID(win, spr), (s32)Data.tabScroll, win->selected, cursor);
    if (Data.tabScroll != 0.0f) {
        s32 idx;
        f32 off;
        if (Data.tabScroll > 0.0f) {
            idx = win->selected - 1;
            if (idx < 0) {
                idx = 4;
            }
            off = Data.tabScroll - (f32)menuItemBiosGetPtr(0x2C, 0xB6)->width;
        } else {
            idx = win->selected + 1;
            if ((u32)idx >= 5) {
                idx = 0;
            }
            off = Data.tabScroll + (f32)menuItemBiosGetPtr(0x2C, 0xB6)->width;
        }
        const PocketTab *tab = TabTbl + idx;
        *(u32 *)&cursor2 = cursorBiosGetPos(tab->cursorId);
        _printItemList((GSgfxLayerID)winSpriteGetLayerID(win, spr), (s32)off, idx, cursor2);
    }
    spriteClearScissor(winSpriteGetLayerID(win, spr));
    spriteSetEnv(winSpriteGetLayerID(win, spr));
    return 0;
}

s32 menuPocket2DrawActionMenu(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    PocketActArg *arg = (PocketActArg *)win->parameters[0];
    u32 i;
    if (arg->count < 4) {
        for (i = 0; i < 7; i++) {
            if ((u32)spr->id == ActMenuResizeWork[i].id) {
                break;
            }
        }
        if (i < 7) {
            ActMenuResizeWorkEntry *e;
            s32 off;
            off = (4 - arg->count) * _actionMenuLineHeight(win);
            spr->y = off + ActMenuResizeWork[i].width;
            if (ActMenuResizeWork[i].flag != 0) {
                spr->height = ActMenuResizeWork[i].height - off;
            }
        }
    }
    return 0;
}

s32 menuPocket2DrawActionCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    const s32 ids[4] = {0xDC, 0xDB, 0xDA, 0xD9};
    s32 idx = win->selected + (4 - ((PocketActArg *)win->parameters[0])->count);
    if (idx < 0 || idx >= 4) {
        return 0;
    }
    if ((s16)spr->id == ids[idx]) {
        PocketVec<s32> pos = {0, 0};
        s32 anim = -1;
        if (win->menu == windowGetActiveID()) {
            menuSubCursorAnimeValGet(&pos, &anim);
        }
        windowDrawSpriteCursor(0, 0, -1, win, 0xC2, 0, winSpriteGetLayerID(win, spr), &pos, anim);
    }
    winSpriteSetDisp(spr, 0);
    return 0;
}

s32 menuPocket2DrawNumMenuCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    s32 *arg = (s32 *)win->parameters[0];
    u32 i;
    for (i = 0; i < 4; i++) {
        if (arg[0] == MenuPocket2Num[i].menu) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    s16 sel = win->selected;
    if (sel < 0 || !(sel < MenuPocket2Num[i].count)) {
        return 0;
    }
    s16 id = spr->id;
    const s32 *p = MenuPocket2Num[i].items + sel * 3;
    if (p[1] == id || p[2] == id) {
        spr->color.channels.alpha = 0xFF;
    } else {
        spr->color.channels.alpha = 0;
    }
    return 0;
}

s32 menuPocket2DrawLineCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    s32 y;
    u8 visible;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    if (Data.swapIndex >= 0) {
        y = (Data.swapIndex - cursor.first) * 0x1E;
        if (Data.isScroll != 0) {
            y -= (s32)Data.curPos;
        }
        visible = 0;
        if (y >= 0 && y < 0x10E) {
            visible = 1;
        }
    } else {
        y = cursor.selected * 0x1E;
        if (Data.isScroll == 0) {
            y += (s32)Data.curPos;
        }
        visible = 1;
    }
    if (Data.tabScroll != 0.0f) {
        visible = 0;
    }
    if (visible != 0) {
        s32 iy = menuItemBiosGetPtr(win->menu, spr->id)->y;
        spr->y = iy + y;
        if (Data.swapIndex >= 0) {
            MENU_ITEM_dd_ *item;
            winSpriteSetDisp(spr, 0);
            item = menuItemBiosGetPtr(win->menu, spr->id);
            menuSubDrawCursorBack2(winSpriteGetLayerID(win, spr), 0, 0, item->width, item->height,
                                   spr->color.channels.alpha, 1, 1);
        } else {
            winSpriteSetDisp(spr, 1);
        }
    } else {
        winSpriteSetDisp(spr, 0);
    }
    return 0;
}

s32 menuPocket2DrawBallCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    s32 y;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    y = cursor.selected * 0x1E;
    if (Data.isScroll == 0) {
        y += (s16)Data.curPos;
    }
    if (((Data.swapIndex >= 0) ^ (spr->id == 0xB1)) != 0 && Data.tabScroll == 0.0f) {
        PocketVec<s32> pos = {0, 0};
        s32 anim = -1;
        if (win->menu == windowGetActiveID()) {
            menuSubCursorAnimeValGet(&pos, &anim);
        }
        windowDrawSpriteCursor(0, y, -1, win, 0xC2, 0, winSpriteGetLayerID(win, spr), &pos, anim);
    }
    winSpriteSetDisp(spr, 0);
    return 0;
}

s32 menuPocket2DrawExchangeCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    s32 y = cursor.selected * 0x1E;
    f32 t;
    if (Data.isScroll == 0) {
        y += (s16)Data.curPos;
    }
    if (Data.swapIndex >= 0) {
        s32 iy = menuItemBiosGetPtr(win->menu, spr->id)->y;
        spr->y = iy + y;
        winSpriteSetDisp(spr, 1);
        static f32 duration = 0.5f;
        Data.anim += timeGetLastFrameSec();
        if (Data.anim > duration) {
            Data.anim = 0.0f;
        }
        t = Data.anim / duration;
        if (t > 0.5f) {
            t = 1.0f - t;
        }
        spr->color.channels.alpha = (u8)(155.0f * (t * 2.0f) + 100.0f);
    } else {
        winSpriteSetDisp(spr, 0);
    }
    return 0;
}

s32 menuPocket2Cursor(tagWINDOW_WORK *win) {
    s32 pos;
    u8 moved;
    u32 se;
    s16 cursorArr[2];
    s16 beforeArr[2];
    s16 raw1[2];
    s16 raw2[2];
    s32 total;
    s32 msg;
    s32 packedA;
    s32 packedB;
    s16 raw3[2];
    CURSOR *cursor = (CURSOR *)cursorArr;
    CURSOR *before = (CURSOR *)beforeArr;
    u16 key = windowGetKeyRepeat();
    u16 trg = windowGetKeyTrg();
    s32 msgs[7] = { 0x3AA1, 0x3AA2, 0x3AA7, 0x3AA8, 0x3AB7, 0x3AA7, 0x3AA2 };
    moved = 0;
    se = 0;
    if (Data.tabScroll != 0.0f || Data.curPos != 0.0f || winSeqCheckMove(win->menu)) {
        return 0;
    }
    *(u32 *)raw1 = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    cursor->first = raw1[0];
    cursor->selected = raw1[1];
    _getNbItemSlot(win->selected);
    pos = cursor->first + cursor->selected;
    if (Data.swapIndex < 0) {
        if ((trg & 0xC0) != 0) {
            if (_IsIrekaeAble(win) && _getItemIDFromMenuPos(win->selected, pos) != 0) {
                Data.swapIndex = pos;
                se = 0x11;
            }
        }
    } else if ((trg & 0xD0) != 0) {
        _swapItemSlot(TabTbl[win->selected].kind, Data.swapIndex, pos);
        Data.swapIndex = -1;
        se = 0x11;
    } else if ((trg & 0xE0) != 0) {
        Data.swapIndex = -1;
        se = 0x12;
    }
    *(u32 *)raw2 = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    cursor->first = raw2[0];
    cursor->selected = raw2[1];
    *(s32 *)before = *(s32 *)cursor;
    total = _getNbItemSlot(win->selected) + 1;
    if ((key & 2) != 0) {
        if (++cursor->selected + cursor->first >= total) {
            cursor->selected--;
        } else {
            if (cursor->selected >= 9) {
                cursor->first++;
                cursor->selected--;
                se = 0x10;
                Data.isScroll = 1;
            } else {
                se = 0x10;
                Data.isScroll = 0;
            }
            Data.curPos = -30.0f;
        }
        moved = 1;
    }
    if ((key & 1) != 0) {
        if (cursor->selected > 0 || cursor->first > 0) {
            if (--cursor->selected < 0) {
                cursor->selected = 0;
                cursor->first--;
                se = 0x10;
                Data.isScroll = 1;
            } else {
                se = 0x10;
                Data.isScroll = 0;
            }
            Data.curPos = 30.0f;
        }
        moved = 1;
    }
    packedA = *(s32 *)cursor;
    cursorBiosSetPos(TabTbl[win->selected].cursorId, &packedA);
    if (before->selected != cursor->selected || before->first != cursor->first) {
        menuSubCursorAnimeStart();
    }
    if (Data.swapIndex < 0 && moved == 0) {
        if ((key & 8) != 0 && Data.mode != 6) {
            if ((u32)++win->selected >= 5) {
                win->selected = 0;
            }
            Data.tabScroll = menuItemBiosGetPtr(0x2C, 0xB6)->width;
            se = 0x44D;
        } else if ((key & 4) != 0 && Data.mode != 6) {
            if (--win->selected < 0) {
                win->selected = 4;
            }
            Data.tabScroll = -menuItemBiosGetPtr(0x2C, 0xB6)->width;
            se = 0x44D;
        } else if ((trg & 0x600) != 0 && _IsSortAble(win)) {
            se = 0x11;
            _sortItemsThisTab(TabTbl[win->selected].kind);
        }
        packedB = *(s32 *)&win->first;
        cursorBiosSetPos(2, &packedB);
    }
    if (se != 0) {
        menuPtPlaySe(se);
    }
    if (Data.swapIndex >= 0) {
        msg = 0x3AAD;
    } else {
        u16 id;
        *(u32 *)raw3 = cursorBiosGetPos(TabTbl[win->selected].cursorId);
        cursor->first = raw3[0];
        cursor->selected = raw3[1];
        id = _getItemIDFromMenuPos(win->selected, cursor->first + cursor->selected);
        if (id != 0) {
            msg = _getItemInstMsg(id);
        } else {
            msg = msgs[Data.mode];
        }
    }
    _setExplanationMsgID(msg);
    return 0;
}

s32 menuPocket2DrawActiveTab(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    if (spr->id == TabTbl[win->selected].unk8) {
        spr->color.value = 0xFFFFFFFF;
    } else {
        spr->color.channels.alpha = 0;
    }
    return 0;
}

void menuPocketMain(void) {
    Data.result = _menuPocketLoop();
}

void menuPocket2Call(s32 mode, s32 shop, Hero *hero) {
    memset(&Data, 0, 0x4C);
    Data.mode = mode;
    Data.hero = hero;
    Data.shop = shop;
    _menuPocketLoop();
}

u8 menuPocket2GetLastSlotID(void) {
    return Data.lastSlot;
}

}

int _actionMenuLineHeight(tagWINDOW_WORK *win) {
    MENU_ITEM_dd_ *a = menuItemBiosGetPtr(win->menu, 0xDA);
    int h = a->y - menuItemBiosGetPtr(win->menu, 0xD9)->y;
    if (h < 0) {
        h = -h;
    }
    return h;
}

extern "C" {

s32 menuPocket2DrawActionCursorLine(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    int offset = 4 - ((PocketActArg *)win->parameters[0])->count;
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(win->menu, spr->id);
    spr->y = item->y + (win->selected + offset) * _actionMenuLineHeight(win);
    return 0;
}

s32 menuPocket2ActionCursor(tagWINDOW_WORK *win) {
    PocketActArg *arg = (PocketActArg *)win->parameters[0];
    u16 key = windowGetKeyRepeat();
    int count = arg->count;
    CURSOR before = *(CURSOR *)&win->first;
    s8 pos;
    if ((key & 2) != 0) {
        pos = win->selected + 1;
        if (pos >= count) {
            pos = 0;
        }
        win->selected = pos;
    }
    if ((key & 1) != 0) {
        pos = win->selected - 1;
        if (pos < 0) {
            pos = count - 1;
        }
        win->selected = pos;
    }
    if (before.selected != win->selected || before.first != win->first) {
        menuSubCursorAnimeStart();
    }
    return 0;
}

s32 menuPocket2ActionCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(0x2D, 0x68);
            Data.anim = 0.0f;
            win->step = 1;
            menuSubCursorAnimeInit();
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x2D, 0x6C);
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 menuPocket2DrawRollDown(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    if (Data.selecting == 0) {
        return 0;
    }
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    if (cursor.first + 9 < _getNbItemSlot(win->selected) + 1) {
        spr->color.channels.alpha = (u8)(255.0f * (1.0f - Data.rollTime));
    } else {
        spr->color.channels.alpha = 0;
    }
    return 0;
}

s32 menuPocket2DrawRollUp(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    CURSOR cursor;
    if (Data.selecting == 0) {
        return 0;
    }
    *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
    if (cursor.first > 0) {
        spr->color.channels.alpha = (u8)(255.0f * (1.0f - Data.rollTime));
    } else {
        spr->color.channels.alpha = 0;
    }
    return 0;
}

s32 menuPocketInputNumber(tagWINDOW_WORK *win, s32 num, s32 max, u16 key, s32 digits, s32 se, s32 unused) {
    s32 e;
    s32 orig;
    s32 p;
    s32 d0, d1, d2;
    s32 i;
    u16 k = key;
    e = digits - win->selected - 1;
    if ((k & 0xF) != 0) {
    orig = num;
    p = 1;
    for (i = 0; i < e; i++) {
        p *= 10;
    }
    d0 = (num / p) % 10;
    d1 = (num / (p * 10)) % 10;
    d2 = (num / (p * 100)) % 10;
    if (k & 1) {
        if (max != 0) {
            if (num == max) {
                num = 0;
            } else if (d0 < 9) {
                num += p;
            } else if (e >= digits - 1) {
                num = 0;
                for (i = 0; i < digits; i++) {
                    num *= 10;
                    num += 9;
                }
            } else if (d1 < 9) {
                num += p;
            } else if (e >= digits - 2) {
                num = 0;
                for (i = 0; i < digits; i++) {
                    num *= 10;
                    num += 9;
                }
            } else if (d2 < 9) {
                num += p;
            } else {
                num = 0;
            }
            if (num > max) {
                num = max;
            }
        }
    } else if (k & 2) {
        if (max != 0) {
            if (num == 0) {
                num = max;
            } else if (d0 >= 1) {
                num -= p;
            } else if (e >= digits - 1) {
                num = 0;
            } else if (d1 >= 1) {
                num -= p;
            } else if (e >= digits - 2) {
                num = 0;
            } else if (d2 >= 1) {
                num -= p;
            } else {
                num = max;
            }
        }
    } else if (k & 8) {
        if (++win->selected >= digits) {
            win->selected = (s8)(digits - 1);
        }
    } else if (k & 4) {
        if (--win->selected < 0) {
            win->selected = 0;
        }
    }
    if (orig != num) {
        menuPtPlaySe(se);
    }
    }
    return num;
}

s32 menuPocket2NumCursor(tagWINDOW_WORK *win) {
    s32 *arg = (s32 *)win->parameters[0];
    u16 key = windowGetKeyRepeat();
    u32 i;
    for (i = 0; i < 4; i++) {
        if (arg[0] == MenuPocket2Num[i].menu) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    Data.num = menuPocketInputNumber(win, Data.num, arg[1], key, MenuPocket2Num[i].count, 0x10, 0x44D);
    return 0;
}

void menuPocketClearItemScript(void) {
    memset(&menuPocketWork, 0, 0x40);
    menuPocketWork.count = 0;
}

s32 menuPocket2GetItemScript(u16 id) {
    s32 result = -1;
    PocketScriptEntry *p = menuPocketWork.entries;
    s32 i;
    for (i = 0; i < menuPocketWork.count; p++, i++) {
        if (id == p->id) {
            result = menuPocketWork.entries[i].value;
            break;
        }
    }
    return result;
}

void menuPocket2AddItemScript(u16 id, u32 value) {
    PocketScriptEntry *p;
    s32 i;
    for (p = menuPocketWork.entries, i = 0; i < 8; i++, p++) {
        if (p->id == id && p->value == value) {
            return;
        }
    }
    if (menuPocketWork.count < 7) {
        menuPocketWork.entries[menuPocketWork.count].id = id;
        menuPocketWork.entries[menuPocketWork.count].value = value;
        menuPocketWork.count++;
    }
}

}

extern "C" {

s32 menuPocket2DrawActionText(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    const s32 ids[4] = { 0xE0, 0xDF, 0xDE, 0xDD };
    PocketActArg *arg = (PocketActArg *)win->parameters[0];
    int i = 0;
    int index;
    for (; i < 4; i++) {
        if (spr->id == ids[i]) {
            break;
        }
    }
    index = i - (4 - arg->count);
    if (index < 0 || index >= arg->count) {
        return 0;
    }
    GSmsgPrint2(winSpriteGetLayerID(win, spr), 0, 0, -1, arg->items[i].msg);
    return 0;
}

s32 menuPocket2Ctrl(tagWINDOW_WORK *win) {
    CURSOR cursor;
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            menuPtPlaySe(0x14);
            winSeqSetMenu(0x2C, 0x60);
            *(u32 *)&cursor = cursorBiosGetPos(TabTbl[win->selected].cursorId);
            _setExplanationMsgID(_getItemInstMsg(_getItemIDFromMenuPos(win->selected, cursor.first + cursor.selected)));
            win->step = 1;
            menuSubCursorAnimeInit();
        }
        break;
    case 2:
        menuPocketToolFloatToZero(Data.tabScroll, 23.0f);
        menuPocketToolFloatToZero(Data.curPos, 7.0f);
        Data.rollTime += 0.033333335f;
        if (Data.rollTime > 1.0f) {
            Data.rollTime = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (win->step == 0) {
            menuPtPlaySe(0x15);
            winSeqSetMenu(0x2C, 0x64);
            win->step = 1;
        }
        break;
    }
    return 0;
}

u16 menuPocket2Open(s32 mode, s32 *slot, s32 arg) {
    s32 value;
    memset(&Data, 0, 0x4C);
    Data.mode = mode;
    if (mode == 1 || mode == 6) {
        Data.fightId = arg;
        Data.hero = fightTrainerBiosGetHeroPtr(arg);
        value = *slot;
        Data.pokemonSlot = value;
        Data.pokemonSlot2 = value;
        if (value < 0 || value >= 5) {
            Data.pokemonSlot = 0;
        }
    } else {
        Data.hero = (Hero *)arg;
        Data.pokemonSlot = -1;
    }
    Data.floorPop = 1;
    GSfloorPush(0x38F, &Data);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    if (Data.result == 0) {
        return 0;
    }
    if (slot != 0) {
        *slot = Data.pokemonSlot;
    }
    return Data.result;
}

}
