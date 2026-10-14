#include <game/menuShopLayout.hpp>
#include <libc/stdarg.h>

typedef struct VPC_BOX {
    u8 reserved0[0x3AC];
    u8 reserved3AC[0x3AC];
    s32 unk758;
    s32 unk75C;
    u8 unk760;
    u8 reserved761[3];
} VPC_BOX;

typedef struct ShopDataEntry {
    u8 index;
    u8 mode;
    u16 goods;
} ShopDataEntry;

typedef struct ShopExchanger {
    u8 sprite;
    s32 msg[18];
} ShopExchanger;

typedef struct ShopSalesman {
    u8 sprite;
    s32 msg[14];
} ShopSalesman;

typedef struct ShopMenuArg {
    s32 index;
    u16 item;
    u16 *goods;
    s32 nbItem;
    f32 *curPos;
    s32 *isScroll;
    f32 *rollUpTime;
    u8 mode;
    u8 flags;
    u8 reserved1E[2];
    VPC_BOX vpc;
} ShopMenuArg;

typedef struct ShopNumArg {
    s32 max;
    s32 count;
    s32 *value;
    s32 flag;
} ShopNumArg;

typedef struct ShopMenuItem {
    s32 id;
    s16 y;
} ShopMenuItem;

typedef struct ShopCursorPos {
    s16 first;
    s16 selected;
} ShopCursorPos;

typedef struct ShopCursorAnime {
    void *a;
    void *b;
} ShopCursorAnime;

typedef struct ShopItemInfo {
    u8 reserved0[6];
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} ShopItemInfo;

s32 memcardTaskCall(s32, s32, s32);
void itemInitAry(void *, s32);
void *savedataGetStatus(s32, s32);
void *memcpy(void *, const void *, u32);
s32 heroGetStatus(s32, s32, s32);
void heroSetStatus(s32, s32, s32);
void winMsgOpenWithSE(s32, s32, s32, s32, u8);
void winMsgClose(s32);
s32 menuSubOpenYesNo(s32, s32, s32, s32);
f32 GSgfxVideoGetLastRenderTime(void);
u8 GSgfxVideoGetVsyncRate(void);
void GSthreadSwitch(void);
void heroDecPokecoupon(s32, s32);
void pcboxAddItem(s32, u16, u16);
s32 heroItemCheckAddItemDataId(s32, u16);
u16 pcboxGetItemCapacity(s32, u16);
void heroItemAddItemDataId(s32, u16, u16, s32);
void msgctrlSetValue(s32, s32);
void menuPtPlaySe__FUl(u32);
u32 itemDataBiosGetPtr(u16);
u8 itemDataBiosGetKind(u32);
u32 itemDataBiosGetWazaMachineNo(u32);
u16 itemDataBiosGetWazaIDByWazaMachineNo(u8);
u16 itemDataBiosGetCoupon(u32);
u32 itemDataBiosGetPrice(u32);
u32 itemDataBiosGetDoc(u32);
u32 itemDataBiosGetName(u32);
u32 *heroItemGetItemKindToItemAryPtr(s32, u8, u16 *, s32, s32, s32);
s32 itemGetStatus(void *, s32, s32, s32);
u32 GSmsgGetRect(s32);
void GSmsgPrint2(s32, s32, s32, s32, s32);
void GSmsgPrintRight(s32, s32, s32, s16, s16, s32, s32);
s32 menuPocketInputNumber(void *, s32, s32, u16, s32, s32, s32);
u16 windowGetKeyRepeat(void);
u16 windowGetKeyTrg(void);
void winSeqSetMenu(s32, s32);
ShopItemInfo *menuItemBiosGetPtr(s32, s32);
void spriteSetScissor(s32, s32, s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void menuSubCursorAnimeValGet(ShopCursorAnime *, s32 *);
s32 winSpriteGetLayerID(ShopWindow *, ShopSprite *);
void windowDrawSpriteCursor(s32, s16, s32, ShopWindow *, s32, s32, s32, ShopCursorAnime *, s32);
void menuSubCursorAnimeInit(f32 *, u32);
void menuSubCursorAnimeMain(void);
u8 winSeqCheckMove(s32);
void menuButtonNormal(ShopWindow *);
void menuSubCursorAnimeStart(void);
void menuCloseCustom(s32, s32, s32);
void heroDecPokedoru(s32, u16);
void GSsndPlay(s32, s32, s32);
s32 menuSubOpenSelect(s32, void *, s32, s32, s32, s32);
void *GSmemAlloc(s32);
void GSmemFree(void *);
void menuPocket2Call(s32, s32, s32);
u8 deckDataVirtualDB_GetFlagData__FUs(u16);
u8 heroItemCheckHaveItemDataId(s32, u16);
void mailMainReceiveTerminate(void);
void GSfloorPush(s32, void *);
void GSfloorPop(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void menuCreateOffScreen(u8, f32, f32);
void menuReleaseOffScreen(u8, f32);
u8 savedataGetBattleDiskSellOut(s32);
void savedataSetBattleDiskSellOut(s32);
s32 menuOpenCustom(s32, s32, void *, s32, s32, s32, ...);
s32 windowGetActiveID(void);
void menuClose(s32);
void menuCloseSync(s32, s32);

extern ShopDataEntry *shopData;
extern u16 *shopGoods;
extern ShopExchanger *shopExchanger;
extern ShopSalesman *shopSalesman;

s32 menuShopGetCouponMsgID(u8 *, s32, s32, s32, ...);
s32 menuShopGetMsgID(u8 *, s32, s32, s32, ...);

static void addItem__FUsi(u16, s32);
static u16 *getGoodsList__FiPi(s32, s32 *);
static s32 getItemCouponPoint__FUs(u16);
static s32 _msgIdWazaMachineChange__FUsUl(u16, u32);
static s32 getNbItem__FP13SHOP_MENU_ARG(ShopMenuArg *);
static u16 getItem__FP13SHOP_MENU_ARGi(ShopMenuArg *, s32);
static void setExplanationMsgID__FUl(u32);
static s32 getMoney__Fv(void);
static s32 getCouponPoint__FUc(u8);
static s32 getNbHaveItem__FUs(u16);
static u16 getItemPrice__FUs(u16);
static u32 getItemExplanationMsg__FUs(u16);
static u32 getItemNameMsg__FUs(u16);
static u8 _getIsBattleDiskSellOut__Fi(s32);
static void setDefMenuItem__Fv(void);
static s32 _getIsBattleDiskShopAllSelWithAllSellOutYet__Fv(void);
static s32 _getBattleDiskShopID__Fv(void);
static void _setBattleDiskSellOut__Fi(s32);
static u8 _isBattleDiskShop__Fv(void);
static s32 _getBattleDiskShopLevel__Fv(void);
s32 shopmode[7] = { 0xC5E2, 0xC5E4, 0xC5E9, 0xC5E9, 0xC5E9, 0xC5F1, 0xC5E3 };
static ShopMenuItem DefMenuItem = { 0x64, 0 };
s32 _shopDataBattleDiskTbl[3] = { 0x10, 0x11, 0x12 };
static const s32 NumWinItem[2][2] = { { 0x94, 0x92 }, { 0x1A6, 0x93 } };

typedef struct ShopWorkData {
    s32 id;
    s32 pop;
} ShopWorkData;

static ShopWorkData ShopWork;
static f32 CurPos;
static s32 IsScroll;
static f32 RollUpTime;
static s32 ExplanationMsgID;
static s32 NumValue;
static void *PPcboxBackup;
static s32 CouponBackup;

static s32 memCardSave__FP7VPC_BOX(VPC_BOX *box) {
    return memcardTaskCall(4, 2, 0) == 4;
}

static void memCardDecCouponAddItem__FiUsiP7VPC_BOX(s32 a, u16 b, s32 c, VPC_BOX *box) {
    if (box != 0) {
        box->unk760 = 1;
    }
}

static s32 memCardConnect__FP7VPC_BOX(VPC_BOX *box) {
    void *save;
    itemInitAry(box, 0xEB);
    itemInitAry(box->reserved3AC, 0xEB);
    box->unk758 = 0;
    box->unk75C = 0;
    box->unk760 = 0;
    save = savedataGetStatus(0, 3);
    memcpy(PPcboxBackup, save, 0xBC50);
    CouponBackup = heroGetStatus(0, 0xD, 0);
    return 1;
}

static u8 checkExchangeVpc__FP7VPC_BOX(VPC_BOX *box) {
    return box->unk760 != 0;
}

static s32 writeBackPcBox__FiUcP7VPC_BOX(s32 shop, u8 mode, VPC_BOX *box) {
    u8 sprite;
    s8 answer;
    if (checkExchangeVpc__FP7VPC_BOX(box) == 0) {
        winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 0xD, -1), 1, 0, sprite);
        answer = menuSubOpenYesNo(0, -1, -1, 0);
        winMsgClose(1);
        if (answer == 1 || answer == -1) {
            return 0;
        }
        return 1;
    }
    winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 0xF, -1), 1, 0, sprite);
    answer = menuSubOpenYesNo(0, -1, -1, 0);
    winMsgClose(1);
    if (answer == 1 || answer == -1) {
        return 0;
    }
    if (memCardSave__FP7VPC_BOX(box) == 0) {
        memcpy(savedataGetStatus(0, 3), PPcboxBackup, 0xBC50);
        heroSetStatus(0, 0xD, CouponBackup);
    }
    return 1;
}

static void waitTime__Ff(f32 seconds) {
    s32 elapsed;
    u32 limit;
    limit = (u32)(seconds * (f32)GSgfxVideoGetVsyncRate());
    elapsed = 0;
    while (elapsed < (s32)limit) {
        GSthreadSwitch();
        elapsed = (s32)((f32)elapsed + GSgfxVideoGetLastRenderTime());
    }
}

static void decCouponAddItem__FiUsiUcP7VPC_BOX(s32 point, u16 item, s32 num, u8 mode, VPC_BOX *box) {
    switch (mode) {
    case 2:
        heroDecPokecoupon(0, point);
        pcboxAddItem(0, item, num);
        memCardDecCouponAddItem__FiUsiP7VPC_BOX(point, item, num, box);
        break;
    default:
        heroDecPokecoupon(0, point);
        addItem__FUsi(item, num);
        break;
    }
}

static s32 checkAddItem__FUsUc(u16 item, u8 mode) {
    switch (mode) {
    case 2:
        return pcboxGetItemCapacity(0, item);
    default:
        return heroItemCheckAddItemDataId(0, item);
    }
}

static s32 getMinPoint__Fi(s32 shop) {
    s32 count;
    u16 *goods;
    s32 min;
    min = 9999999;
    goods = getGoodsList__FiPi(shop, &count);
    while (*goods != 0) {
        s32 point = getItemCouponPoint__FUs(*goods);
        if (point < min) {
            min = point;
        }
        goods++;
    }
    return min;
}

static u16 *getGoodsList__FiPi(s32 shop, s32 *count) {
    u16 *goods = shopGoods + shopData[shop].goods;
    u16 *p = goods;
    s32 n = 0;
    while (*p != 0) {
        p++;
        n++;
    }
    *count = n;
    return goods;
}

static s32 getCouponMsgID__FPUci20MENU_COUPON_MSG_CODEiP16__va_list_struct(u8 *sprite, s32 shop, s32 code, s32 value, va_list args) {
    s32 key;
    s32 wait = 1;
    u16 item = 0;
    s32 idx = shopData[shop].index;
    s32 *msgs;
    s32 off = code * 4;
    *sprite = shopExchanger[idx].sprite;
    msgs = shopExchanger[idx].msg;
    while (value >= 0) {
        if (wait != 0) {
            key = value;
            wait = 0;
        } else {
            wait = 1;
            msgctrlSetValue(key, value);
            if (key == 0x2D) {
                item = value;
            }
        }
        value = va_arg(args, s32);
    }
    return _msgIdWazaMachineChange__FUsUl(item, *(s32 *)((u8 *)msgs + off));
}

static s32 getMsgID__FPUci18MENU_SHOP_MSG_CODEiP16__va_list_struct(u8 *sprite, s32 shop, s32 code, s32 value, va_list args) {
    s32 key;
    s32 wait = 1;
    u16 item = 0;
    s32 idx = shopData[shop].index;
    s32 *msgs;
    s32 off = code * 4;
    *sprite = shopSalesman[idx].sprite;
    msgs = shopSalesman[idx].msg;
    while (value >= 0) {
        if (wait != 0) {
            key = value;
            wait = 0;
        } else {
            wait = 1;
            msgctrlSetValue(key, value);
            if (key == 0x2D) {
                item = value;
            }
        }
        value = va_arg(args, s32);
    }
    return _msgIdWazaMachineChange__FUsUl(item, *(s32 *)((u8 *)msgs + off));
}

static s32 _msgIdWazaMachineChange__FUsUl(u16 item, u32 msg) {
    u32 data;
    if (item != 0) {
        data = itemDataBiosGetPtr(item);
        if (data != 0 && itemDataBiosGetKind(data) == 4) {
            msgctrlSetValue(0x39, itemDataBiosGetWazaIDByWazaMachineNo(itemDataBiosGetWazaMachineNo(data)));
            switch (msg) {
            case 0xC5AC:
                msg = 0xC5EC;
                break;
            case 0xC5B5:
                msg = 0xC5EE;
                break;
            case 0xC5BC:
                msg = 0xC5EF;
                break;
            }
        }
    }
    return msg;
}

s32 menuShopGetCouponMsgID(u8 *sprite, s32 shop, s32 code, s32 value, ...) {
    va_list args;
    va_start(args, value);
    return getCouponMsgID__FPUci20MENU_COUPON_MSG_CODEiP16__va_list_struct(sprite, shop, code, value, args);
}

s32 menuShopGetMsgID(u8 *sprite, s32 shop, s32 code, s32 value, ...) {
    va_list args;
    va_start(args, value);
    return getMsgID__FPUci18MENU_SHOP_MSG_CODEiP16__va_list_struct(sprite, shop, code, value, args);
}

static void openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(s32 shop, s32 code, s32 value, ...) {
    va_list args;
    u8 sprite;
    switch (code) {
    case 4:
    case 8:
    case 9:
        menuPtPlaySe__FUl(0x13);
        break;
    }
    va_start(args, value);
    winMsgOpenWithSE(2, getCouponMsgID__FPUci20MENU_COUPON_MSG_CODEiP16__va_list_struct(&sprite, shop, code, value, args), 1, 0, sprite);
    winMsgClose(1);
}

static void openMsgWin__Fi18MENU_SHOP_MSG_CODEie(s32 shop, s32 code, s32 value, ...) {
    va_list args;
    u8 sprite;
    switch (code) {
    case 5:
    case 6:
    case 8:
    case 11:
        menuPtPlaySe__FUl(0x13);
        break;
    }
    va_start(args, value);
    winMsgOpenWithSE(2, getMsgID__FPUci18MENU_SHOP_MSG_CODEiP16__va_list_struct(&sprite, shop, code, value, args), 1, 0, sprite);
    winMsgClose(1);
}

s32 menuShopNumDrawPriceText(ShopWindow *win, ShopSprite *spr) {
    ShopNumArg *arg = (ShopNumArg *)win->arg;
    s32 msg;
    msgctrlSetValue(0x50, arg->count * *arg->value);
    if (arg->flag != 0) {
        msg = 0x4359;
    } else {
        msg = 0x434F;
    }
    GSmsgPrint2(win->layer, spr->width - (GSmsgGetRect(msg) >> 16), 0, -1, msg);
    return 0;
}

s32 menuShopNumDrawBuyNum(ShopWindow *win, ShopSprite *spr) {
    ShopNumArg *arg = (ShopNumArg *)win->arg;
    s32 i;
    s32 j;
    s32 div;
    s32 num;
    const s32 *p = NumWinItem[0];
    for (i = 0; i < 2; i++, p += 2) {
        if (spr->id == *p) {
            break;
        }
    }
    if (i >= 2) {
        return 0;
    }
    div = 1;
    for (j = 0; j < 1 - i; j++) {
        div *= 10;
    }
    num = *arg->value / div;
    msgctrlSetValue(0x34, num % 10);
    GSmsgPrintRight(win->layer, 0, 0, spr->width, spr->height, -1, 0x4270);
    return 0;
}

s32 menuShopNumDrawCursor(ShopWindow *win, ShopSprite *spr) {
    s16 sel = win->selected;
    if (sel < 0 || sel >= 2) {
        return 0;
    }
    if (spr->id == NumWinItem[sel][1]) {
        spr->alpha = 0xFF;
    } else {
        spr->alpha = 0;
    }
    return 0;
}

s32 menuShopNumCursor(ShopWindow *win) {
    ShopNumArg *arg = (ShopNumArg *)win->arg;
    *arg->value = menuPocketInputNumber(win, *arg->value, arg->max, windowGetKeyRepeat(), 2, 0x10, 0x44D);
    return 0;
}

s32 menuShopNumCtrl(ShopWindow *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(0x3D, 0x70);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x3D, 0x74);
            win->step = 1;
        }
        break;
    }
    return 0;
}

static s32 inputBuyNum__Fiiii(s32 init, s32 max, s32 unit, s32 flag) {
    s32 params[4];
    s32 ret;
    s32 num;
    if (max < 0) {
        return 0;
    }
    params[0] = max;
    params[1] = unit;
    NumValue = init;
    params[2] = (s32)&NumValue;
    params[3] = flag;
    {
        s32 mode = 1;
        ret = menuOpenCustom(0x3D, windowGetActiveID(), &mode, 0, 1, 1, params);
    }
    menuClose(0x3D);
    menuCloseSync(0x3D, 1);
    if (ret == -1 || (num = NumValue) == 0) {
        num = -1;
    }
    return num;
}

static void addItem__FUsi(u16 item, s32 num) {
    heroItemAddItemDataId(0, item, num, -1);
}

static s32 getCouponPoint__FUc(u8 mode) {
    switch (mode) {
    case 2:
        return heroGetStatus(0, 0xD, 0);
    default:
        return heroGetStatus(0, 0xD, 0);
    }
}

static s32 getMoney__Fv(void) {
    return heroGetStatus(0, 0xC, 0);
}

static s32 getItemCouponPoint__FUs(u16 item) {
    return itemDataBiosGetCoupon(itemDataBiosGetPtr(item));
}

static u16 getItemPrice__FUs(u16 item) {
    return itemDataBiosGetPrice(itemDataBiosGetPtr(item));
}

static s32 getNbHaveItem__FUs(u16 item) {
    u16 count;
    u32 *ary;
    s32 i;
    s32 total = 0;
    if (item == 0) {
        return 0;
    }
    ary = heroItemGetItemKindToItemAryPtr(0, itemDataBiosGetKind(itemDataBiosGetPtr(item)), &count, 0, 0, 0);
    for (i = 0; i < count; i++, ary++) {
        u16 id = itemGetStatus(ary, 0, 0x1B, 0);
        if (id == item) {
            total += itemGetStatus(ary, 0, 0x1C, 0);
        }
    }
    return total;
}

static void setExplanationMsgID__FUl(u32 id) {
    ExplanationMsgID = id;
}

static u32 getItemExplanationMsg__FUs(u16 item) {
    return itemDataBiosGetDoc(itemDataBiosGetPtr(item));
}

static u32 getItemNameMsg__FUs(u16 item) {
    return itemDataBiosGetName(itemDataBiosGetPtr(item));
}

static s32 getNbItem__FP13SHOP_MENU_ARG(ShopMenuArg *arg) {
    return arg->nbItem;
}

static u16 getItem__FP13SHOP_MENU_ARGi(ShopMenuArg *arg, s32 idx) {
    if (idx < 0 || idx >= getNbItem__FP13SHOP_MENU_ARG(arg)) {
        return 0;
    }
    return arg->goods[idx];
}

s32 menuShopDrawTitleText(ShopWindow *win, ShopSprite *spr) {
    s32 msg = shopmode[shopData[ShopWork.id].mode];
    s16 w = GSmsgGetRect(msg) >> 16;
    GSmsgPrint2(win->layer, (spr->width - w) / 2, 0, -1, msg);
    return 0;
}

s32 menuShopDrawPointEmblem(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    s32 disp = 0;
    if (spr->id == 0x6F && (arg->flags & 1) == 0 && (arg->mode == 2 || arg->mode == 3 || arg->mode == 4)) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuShopDrawMoneyText(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    s16 w;
    s32 value;
    s32 point;
    if ((arg->flags & 1) != 0) {
        spr->alpha = 0;
        return 0;
    }
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
        value = getMoney__Fv();
        msgctrlSetValue(0x50, value);
    } else {
        point = getCouponPoint__FUc(arg->mode);
        msgctrlSetValue(0x50, point);
    }
    w = GSmsgGetRect(0x434E) >> 16;
    GSmsgPrint2(win->layer, spr->width - w, 0, -1, 0x434E);
    return 0;
}

s32 menuShopDrawMoneyWaku(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    winSpriteSetDisp(spr, (arg->flags & 1) == 0);
    return 0;
}

s32 menuShopDrawHaveWakuBack(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg;
    s32 disp;
    arg = (ShopMenuArg *)win->arg;
    disp = 0;
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuShopDrawHaveWaku(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg;
    s32 disp;
    arg = (ShopMenuArg *)win->arg;
    disp = 0;
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) {
        disp = 1;
    }
    winSpriteSetDisp(spr, disp);
    return 0;
}

s32 menuShopDrawHaveText2(ShopWindow *win) {
    u16 item;
    s32 have;
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    if (arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) {
        item = getItem__FP13SHOP_MENU_ARGi(arg, win->selected + win->first);
        if (item != 0) {
            have = getNbHaveItem__FUs(item);
            msgctrlSetValue(0x34, have);
            msgctrlSetValue(0x2D, item);
            GSmsgPrint2(win->layer, 0, 0, -1, 0x3AB1);
        }
    }
    return 0;
}

s32 menuShopDrawHaveText1(ShopWindow *win) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    u16 item;
    if ((arg->mode == 0 || arg->mode == 1 || arg->mode == 4 || arg->mode == 6) && (item = getItem__FP13SHOP_MENU_ARGi(arg, win->selected + win->first)) != 0) {
        msgctrlSetValue(0x2D, item);
        GSmsgPrint2(win->layer, 0, 0, -1, 0x3AB0);
    }
    return 0;
}

s32 menuShopDrawExpText(ShopWindow *win) {
    GSmsgPrint2(win->layer, 0, 0, -1, ExplanationMsgID);
    return 0;
}

s32 menuShopDrawRollDown(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg;
    s32 pos;
    pos = win->first + 10;
    arg = (ShopMenuArg *)win->arg;
    if (pos < getNbItem__FP13SHOP_MENU_ARG(arg) + 1 && arg->item == 0) {
        spr->alpha = (u8)(255.0f * (1.0f - RollUpTime));
    } else {
        spr->alpha = 0;
    }
    return 0;
}

s32 menuShopDrawRollUp(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    if (win->first > 0 && arg->item == 0) {
        spr->alpha = (u8)(255.0f * (1.0f - RollUpTime));
    } else {
        spr->alpha = 0;
    }
    return 0;
}

s32 menuShopDrawListText(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg;
    s32 start;
    s32 limit;
    s32 scroll;
    ShopItemInfo *view;
    ShopItemInfo *info;
    s32 idx;
    s32 nb;
    s32 i;
    s32 y;
    s32 x;
    s32 rowY;
    u32 w;
    u16 item;
    u32 msg;
    arg = (ShopMenuArg *)win->arg;
    start = 0;
    limit = 10;
    scroll = 0;
    view = menuItemBiosGetPtr(win->menu, 0x66);
    info = menuItemBiosGetPtr(win->menu, spr->id);
    spriteSetScissor(win->layer, view->x - info->x, view->y - info->y, view->width, view->height);
    idx = win->first;
    nb = getNbItem__FP13SHOP_MENU_ARG(arg);
    msgctrlSetValue(0x50, 99999);
    w = GSmsgGetRect(0x434E) >> 16;
    x = (spr->width - w) - (GSmsgGetRect(0x42AF) >> 16);
    if (*arg->curPos != 0.0f && *arg->isScroll != 0) {
        if (*arg->curPos < 0.0f) {
            idx--;
            start = -1;
        } else {
            limit = 11;
        }
        scroll = (s32)*arg->curPos;
    }
    y = start * 30;
    i = start;
    for (; i < limit && idx < nb; y += 30, i++, idx++) {
        if (idx >= 0) {
            rowY = y - scroll;
            item = getItem__FP13SHOP_MENU_ARGi(arg, idx);
            msg = getItemNameMsg__FUs(item);
            if (msg != 0) {
                GSmsgPrint2(win->layer, 0, rowY, -1, msg);
            }
            if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
                if (_getIsBattleDiskSellOut__Fi(i) != 0) {
                    GSmsgPrint2(win->layer, x, rowY, -1, 0xC5EB);
                } else {
                    s32 price;
                    GSmsgPrint2(win->layer, x, rowY, -1, 0x42AF);
                    price = getItemPrice__FUs(item);
                    msgctrlSetValue(0x50, price);
                    GSmsgPrint2(win->layer, spr->width - (GSmsgGetRect(0x434E) >> 16), rowY, -1, 0x434E);
                }
            } else {
                s32 point = getItemCouponPoint__FUs(item);
                msgctrlSetValue(0x50, point);
                GSmsgPrint2(win->layer, spr->width - (GSmsgGetRect(0x4359) >> 16), rowY, -1, 0x4359);
            }
        }
    }
    if (i < limit) {
        s32 text;
        if ((arg->flags & 1) != 0) {
            text = 0x3ABE;
        } else {
            text = 0x3AAE;
        }
        if (arg->mode == 1) {
            text = 0x3C3F;
        }
        GSmsgPrint2(win->layer, 0, i * 30 - scroll, -1, text);
    }
    spriteClearScissor(win->layer);
    spriteSetEnv(win->layer);
    return 0;
}

s32 menuShopDrawBallCursor(ShopWindow *win, ShopSprite *spr) {
    ShopMenuArg *arg;
    ShopCursorPos pos;
    s32 y;
    s32 val;
    arg = (ShopMenuArg *)win->arg;
    pos = *(ShopCursorPos *)&win->first;
    y = pos.selected * 30;
    if (*arg->isScroll == 0) {
        y = (s32)((f32)y + *arg->curPos);
    }
    {
        ShopCursorAnime anime = { 0, 0 };
        val = -1;
        if (win->menu == windowGetActiveID()) {
            menuSubCursorAnimeValGet(&anime, &val);
        }
        windowDrawSpriteCursor(0, y, -1, win, 0xC2, 0, winSpriteGetLayerID(win, spr), &anime, val);
    }
    winSpriteSetDisp(spr, 0);
    return 0;
}

s32 menuShopDrawLineCursor(ShopWindow *win, ShopSprite *spr) {
    ShopItemInfo *info;
    ShopMenuArg *arg;
    ShopCursorPos pos;
    s32 y;
    arg = (ShopMenuArg *)win->arg;
    pos = *(ShopCursorPos *)&win->first;
    y = pos.selected * 30;
    if (*arg->isScroll == 0) {
        y += (s32)*arg->curPos;
    }
    info = menuItemBiosGetPtr(win->menu, spr->id);
    spr->unk52 = info->y + y;
    return 0;
}

s32 menuShopCursor(ShopWindow *win) {
    ShopMenuArg *arg;
    u16 key;
    ShopCursorPos prev;
    s32 total;
    u16 item;
    s32 msg;
    arg = (ShopMenuArg *)win->arg;
    key = windowGetKeyRepeat();
    windowGetKeyTrg();
    if (*arg->curPos != 0.0f) {
        return 0;
    }
    if (winSeqCheckMove(win->menu) != 0) {
        return 0;
    }
    prev = *(ShopCursorPos *)&win->first;
    total = getNbItem__FP13SHOP_MENU_ARG(arg) + 1;
    if ((key & 2) != 0) {
        win->selected++;
        if (win->selected + win->first >= total) {
            win->selected--;
        } else {
            if (win->selected >= 10) {
                win->first++;
                win->selected--;
                *arg->isScroll = 1;
            } else {
                *arg->isScroll = 0;
            }
            *arg->curPos = -30.0f;
        }
    }
    if ((key & 1) != 0 && (win->selected > 0 || win->first > 0)) {
        if (--win->selected < 0) {
            win->selected = 0;
            win->first--;
            *arg->isScroll = 1;
        } else {
            *arg->isScroll = 0;
        }
        *arg->curPos = 30.0f;
    }
    if (prev.selected != win->selected || prev.first != win->first) {
        menuSubCursorAnimeStart();
    }
    item = getItem__FP13SHOP_MENU_ARGi(arg, win->first + win->selected);
    if (item != 0) {
        msg = getItemExplanationMsg__FUs(item);
    } else if (arg->mode == 0 || arg->mode == 1 || arg->mode == 5 || arg->mode == 6) {
        msg = 0x3AAF;
    } else if ((arg->flags & 1) != 0) {
        msg = 0x3ABD;
    } else {
        msg = 0x3AB2;
    }
    setExplanationMsgID__FUl(msg);
    return 0;
}

s32 menuShopButton(ShopWindow *win) {
    ShopMenuArg *arg;
    u16 key;
    s32 index;
    u16 item;
    arg = (ShopMenuArg *)win->arg;
    key = windowGetKeyTrg();
    index = win->first + win->selected;
    if (winSeqCheckMove(win->menu) == 0) {
        if (_getIsBattleDiskSellOut__Fi(index) != 0) {
            if ((key & 0x20) != 0) {
                menuButtonNormal(win);
            }
        } else {
            item = 0;
            if ((key & 0x10) != 0) {
                item = getItem__FP13SHOP_MENU_ARGi(arg, win->first + win->selected);
                if ((arg->flags & 1) != 0 && item != 0) {
                    return 0;
                }
            }
            if (item != 0) {
                arg->index = win->first + win->selected;
                arg->item = item;
            }
            menuButtonNormal(win);
        }
    }
    return 0;
}

s32 menuShopCtrl(ShopWindow *win) {
    ShopMenuArg *arg = (ShopMenuArg *)win->arg;
    f32 *p;
    f32 v;
    f32 n;
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(0x3C, 0x78);
            *arg->curPos = 0.0f;
            *arg->isScroll = 0;
            p = arg->rollUpTime;
            *p = 0.0f;
            win->step = 1;
            menuSubCursorAnimeInit(p, 0);
        }
        break;
    case 2:
        p = arg->curPos;
        v = *p;
        if (v > 0.0f) {
            n = v - 7.0f;
            *p = n;
            if (n < 0.0f) {
                *arg->curPos = 0.0f;
            }
        }
        p = arg->curPos;
        v = *p;
        if (v < 0.0f) {
            n = v + 7.0f;
            *p = n;
            if (n > 0.0f) {
                *arg->curPos = 0.0f;
            }
        }
        p = arg->rollUpTime;
        *p += 0.06666667f;
        p = arg->rollUpTime;
        if (*p > 1.0f) {
            *p = 0.0f;
        }
        menuSubCursorAnimeMain();
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(0x3C, 0x7C);
            win->step = 1;
        }
        break;
    }
    return 0;
}

static u16 selectItem__FiUcUcP13SHOP_MENU_ARG(s32 shop, u8 mode, u8 flags, ShopMenuArg *arg) {
    static s32 first;
    static s8 init;
    if (init == 0) {
        first = 1;
        init = 1;
    }
    if (first != 0) {
        setDefMenuItem__Fv();
        first = 0;
    }
    arg->item = 0;
    arg->goods = getGoodsList__FiPi(shop, &arg->nbItem);
    arg->curPos = &CurPos;
    arg->isScroll = &IsScroll;
    arg->rollUpTime = &RollUpTime;
    arg->mode = mode;
    arg->flags = flags;
    if (menuOpenCustom(0x3C, windowGetActiveID(), 0, 0, 1, 1, arg) == -1) {
        return 0;
    }
    return arg->item;
}

static void setDefMenuItem__Fv(void) {
    ShopMenuItem *item = &DefMenuItem;
    item->y = menuItemBiosGetPtr(0x3C, item->id)->y;
}

static s32 getExchangeMax__FUsUc(u16 item, u8 mode) {
    s32 point = getItemCouponPoint__FUs(item);
    s32 max;
    if (point > 0) {
        max = getCouponPoint__FUc(mode) / point;
        if (max > 99) {
            return 99;
        }
        return max;
    }
    return 99;
}

static s32 getBuyMax__FUs(u16 item) {
    s32 price = getItemPrice__FUs(item);
    s32 max;
    if (price > 0) {
        max = getMoney__Fv() / price;
        if (max > 99) {
            return 99;
        }
        return max;
    }
    return 99;
}

static void couponExplanationMain__FiUc(s32 shop, u8 mode) {
    openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 0xB, -1);
}

static void couponListMain__FiUc(s32 shop, u8 mode) {
    ShopMenuArg arg;
    if (mode != 2) {
        openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 0xA, -1);
    }
    selectItem__FiUcUcP13SHOP_MENU_ARG(shop, mode, 1, &arg);
    menuCloseCustom(0x3C, 0, 1);
}

static void couponExchangeMain__FiUc(s32 shop, u8 mode) {
    ShopMenuArg arg;
    u8 sprite;
    VPC_BOX *boxp;
    u8 m;
    s32 ok;
    s32 done;
    s32 min;
    u16 item;
    s32 max;
    s32 point;
    s32 num;
    s32 cost;
    s32 answer;
    boxp = &arg.vpc;
    m = mode;
    done = 0;
    switch (mode) {
    case 2:
        ok = memCardConnect__FP7VPC_BOX(&arg.vpc);
        break;
    default:
        ok = 1;
        break;
    }
    if (ok != 0) {
        if (mode == 4) {
            min = getMinPoint__Fi(shop);
            if (getCouponPoint__FUc(mode) < min) {
                openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 4, -1);
                return;
            }
        }
        while (done == 0) {
            for (;;) {
                item = selectItem__FiUcUcP13SHOP_MENU_ARG(shop, mode, 0, &arg);
                if (item == 0) {
                    break;
                }
                max = getExchangeMax__FUsUc(item, mode);
                if (max <= 0) {
                    openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 8, -1);
                    continue;
                }
                point = getItemCouponPoint__FUs(item);
                setExplanationMsgID__FUl(menuShopGetCouponMsgID(&sprite, shop, 0xC, 0x2D, item, -1));
                num = inputBuyNum__Fiiii(1, max, point, 1);
                if (num < 0) {
                    continue;
                }
                cost = num * point;
                winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 5, 0x2D, item, 0x2F, num, 0x4B, cost, -1), 1, 0, sprite);
                answer = menuSubOpenYesNo(0, -1, -1, 0);
                winMsgClose(1);
                if (answer == 1 || answer == -1) {
                    continue;
                }
                if (checkAddItem__FUsUc(item, mode) < num) {
                    openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 9, -1);
                    continue;
                }
                openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 6, -1);
                decCouponAddItem__FiUsiUcP7VPC_BOX(cost, item, num, mode, boxp);
                GSsndPlay(0x1B, 0, 0);
                if (mode != 4) {
                    continue;
                }
                winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 7, -1), 1, 0, sprite);
                answer = menuSubOpenYesNo(0, -1, -1, 0);
                winMsgClose(1);
                if (answer == -1 || answer == 1) {
                    break;
                }
            }
            if (m == 2) {
                done = writeBackPcBox__FiUcP7VPC_BOX(shop, mode, boxp);
            } else {
                done = 1;
            }
        }
        menuCloseCustom(0x3C, 0, 1);
    }
}

static s32 selectExchangeMode__Fv(void) {
    static s32 msgIDTbl[4] = { 0x3AB9, 0x3ABA, 0x3ABB, 0x3ABC };
    s32 sel = menuSubOpenSelect(0, msgIDTbl, 4, 0x46, 0x3C, 0);
    switch (sel) {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    default:
        return 3;
    }
}

static void couponProc__FiUc(s32 shop, u8 mode) {
    u8 sprite;
    s32 sel;
    s32 done = 0;
    PPcboxBackup = GSmemAlloc(0xBC50);
    msgctrlSetValue(0x59, 0x1772);
    winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 0, -1), 1, 0, sprite);
    while ((sel = selectExchangeMode__Fv()) != 3) {
        winMsgClose(1);
        switch (sel) {
        case 0:
            couponExchangeMain__FiUc(shop, mode);
            break;
        case 1:
            couponListMain__FiUc(shop, mode);
            break;
        case 2:
            couponExplanationMain__FiUc(shop, mode);
            break;
        case 3:
            done = 1;
            break;
        }
        if (done != 0) {
            break;
        }
        winMsgOpenWithSE(2, menuShopGetCouponMsgID(&sprite, shop, 1, -1), 1, 0, sprite);
    }
    if (mode != 2) {
        openCouponMsgWin__Fi20MENU_COUPON_MSG_CODEie(shop, 2, -1);
    } else {
        winMsgClose(1);
    }
    if (PPcboxBackup != 0) {
        GSmemFree(PPcboxBackup);
        PPcboxBackup = 0;
    }
}

static void vendingMachineProc__FiUc(s32 shop, u8 mode) {
    ShopMenuArg arg;
    u16 item;
    u16 price;
    s32 money;
    for (;;) {
        menuCloseCustom(0x3C, 0, 1);
        money = getMoney__Fv();
        openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 0, 0x4B, money, -1);
        waitTime__Ff(0.5f);
        item = selectItem__FiUcUcP13SHOP_MENU_ARG(shop, mode, 0, &arg);
        if (item == 0) {
            openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 2, -1);
            break;
        }
        price = getItemPrice__FUs(item);
        if (getBuyMax__FUs(item) <= 0) {
            openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 5, -1);
            break;
        }
        if (heroItemCheckAddItemDataId(0, item) < 1) {
            openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 6, -1);
            break;
        }
        GSsndPlay(0x1A, 0, 0);
        heroDecPokedoru(0, price);
        addItem__FUsi(item, 1);
        openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 4, 0x2D, item, -1);
    }
    menuCloseCustom(0x3C, 0, 1);
}

static void shopBuyMain__FiUc(s32 shop, u8 mode) {
    ShopMenuArg arg;
    u8 sprite;
    u16 item;
    s32 max;
    u16 price;
    s32 num;
    s32 cost;
    s32 answer;
    u32 data;
    if (_getIsBattleDiskShopAllSelWithAllSellOutYet__Fv() != 0) {
        winMsgOpenWithSE(2, 0xC5EA, 1, 0, shopSalesman[shopData[shop].index].sprite);
        winMsgClose(1);
    }
    for (;;) {
        item = selectItem__FiUcUcP13SHOP_MENU_ARG(shop, mode, 0, &arg);
        if (item == 0) {
            break;
        }
        data = itemDataBiosGetPtr(item);
        if (data != 0) {
            if (itemDataBiosGetKind(data) == 6 && heroItemCheckHaveItemDataId(0, 0x200) == 0) {
                openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 8, -1);
            } else {
                max = getBuyMax__FUs(item);
                if (max <= 0) {
                    openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 5, -1);
                } else {
                    price = getItemPrice__FUs(item);
                    if (_isBattleDiskShop__Fv() != 0) {
                        num = 1;
                    } else {
                        setExplanationMsgID__FUl(menuShopGetMsgID(&sprite, shop, 0xC, 0x2D, item, -1));
                        num = inputBuyNum__Fiiii(1, max, price, 0);
                    }
                    if (num >= 0) {
                        cost = num * price;
                        winMsgOpenWithSE(2, menuShopGetMsgID(&sprite, shop, 3, 0x2D, item, 0x2F, num, 0x4B, cost, -1), 1, 0, sprite);
                        answer = menuSubOpenYesNo(0, -1, -1, 0);
                        winMsgClose(1);
                        if (answer != 1 && answer != -1) {
                            if (heroItemCheckAddItemDataId(0, item) < num) {
                                openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 6, -1);
                            } else {
                                GSsndPlay(0x1A, 0, 0);
                                heroDecPokedoru(0, cost);
                                addItem__FUsi(item, num);
                                _setBattleDiskSellOut__Fi(arg.index);
                                openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 4, -1);
                                if (item == 4 && num >= 10 && heroItemCheckAddItemDataId(0, 0xC) >= 1) {
                                    openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 7, -1);
                                    addItem__FUsi(0xC, 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    menuCloseCustom(0x3C, 0, 1);
}

static s32 selectDealMode__Fv(void) {
    static s32 msgIDTbl[3] = { 0x3AB3, 0x3AB4, 0x3AB5 };
    s32 sel = menuSubOpenSelect(0, msgIDTbl, 3, 0x46, 0x3C, 0);
    if (sel == -1 || sel == 2) {
        return 2;
    }
    return sel != 0;
}

static void shopProc__FiUc(s32 shop, u8 mode) {
    u8 sprite;
    s32 msg;
    s32 sel;
    msg = menuShopGetMsgID(&sprite, shop, 0, 0x4B, getMoney__Fv(), -1);
    msgctrlSetValue(0x59, 0x1772);
    winMsgOpenWithSE(2, msg, 1, 0, sprite);
    while ((sel = selectDealMode__Fv()) != 2) {
        winMsgClose(1);
        switch (sel) {
        case 0:
            shopBuyMain__FiUc(shop, mode);
            break;
        case 1:
            menuPocket2Call(3, shop, 0);
            break;
        }
        winMsgOpenWithSE(2, menuShopGetMsgID(&sprite, shop, 1, -1), 1, 0, sprite);
    }
    openMsgWin__Fi18MENU_SHOP_MSG_CODEie(shop, 2, -1);
}

void menuShopMain(void) {
    u8 mode;
    if (ShopWork.id == 0x10) {
        ShopWork.id = _getBattleDiskShopID__Fv();
    }
    mode = shopData[ShopWork.id].mode;
    switch (mode) {
    case 0:
        shopProc__FiUc(ShopWork.id, mode);
        break;
    case 1:
        vendingMachineProc__FiUc(ShopWork.id, mode);
        break;
    case 5:
        shopProc__FiUc(ShopWork.id, mode);
        break;
    case 6:
        shopProc__FiUc(ShopWork.id, mode);
        break;
    default:
        couponProc__FiUc(ShopWork.id, mode);
        break;
    }
    if (ShopWork.pop != 0) {
        GSfloorPop();
        floorSetFadeScript(0, 0);
    }
}

void menuShopOpen(s32 shop) {
    u8 rate;
    mailMainReceiveTerminate();
    rate = GSgfxVideoGetVsyncRate();
    menuCreateOffScreen(rate, 20.0f / (f32)rate, 50.0f);
    ShopWork.id = shop;
    ShopWork.pop = 1;
    GSfloorPush(0x3A4, &ShopWork);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    rate = GSgfxVideoGetVsyncRate();
    menuReleaseOffScreen(rate, 20.0f / (f32)rate);
}

static s32 _getIsBattleDiskShopAllSelWithAllSellOutYet__Fv(void) {
    s32 level;
    s32 base;
    s32 i;
    level = _getBattleDiskShopLevel__Fv();
    if (level == 0 || level == 1) {
        base = level * 3;
        i = 0;
        do {
            if (savedataGetBattleDiskSellOut(base) == 0) {
                return 0;
            }
            base++;
            i++;
        } while (i < 3);
        return 1;
    }
    return 0;
}

static s32 _getBattleDiskShopID__Fv(void) {
    s32 count;
    u16 ids[9];
    s32 *tbl;
    s32 j;
    u32 i;
    u16 *goods;
    tbl = _shopDataBattleDiskTbl;
    j = 0;
    i = 0;
    do {
        goods = getGoodsList__FiPi(*tbl, &count);
        ids[j] = goods[0] - 0x215;
        ids[j + 1] = goods[1] - 0x215;
        tbl++;
        ids[j + 2] = goods[2] - 0x215;
        j += 3;
        i++;
    } while (i < 3);
    if (deckDataVirtualDB_GetFlagData__FUs(ids[0]) == 0 || deckDataVirtualDB_GetFlagData__FUs(ids[1]) == 0 || deckDataVirtualDB_GetFlagData__FUs(ids[2]) == 0) {
        return 0x10;
    }
    if (deckDataVirtualDB_GetFlagData__FUs(ids[3]) == 0 || deckDataVirtualDB_GetFlagData__FUs(ids[4]) == 0 || deckDataVirtualDB_GetFlagData__FUs(ids[5]) == 0) {
        return 0x11;
    }
    return 0x12;
}

static void _setBattleDiskSellOut__Fi(s32 index) {
    s32 level = _getBattleDiskShopLevel__Fv();
    if (level != -1) {
        savedataSetBattleDiskSellOut(index + level * 3);
    }
}

static u8 _getIsBattleDiskSellOut__Fi(s32 index) {
    s32 level = _getBattleDiskShopLevel__Fv();
    if (level == -1) {
        return 0;
    }
    return savedataGetBattleDiskSellOut(index + level * 3);
}

static u8 _isBattleDiskShop__Fv(void) {
    return _getBattleDiskShopLevel__Fv() != -1;
}

static s32 _getBattleDiskShopLevel__Fv(void) {
    switch (ShopWork.id) {
    case 16:
        return 0;
    case 17:
        return 1;
    case 18:
        return 2;
    default:
        return -1;
    }
}
