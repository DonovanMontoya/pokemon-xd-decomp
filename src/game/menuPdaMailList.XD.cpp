#include <game/menuPdaMailListLayout.hpp>
#ifdef __cplusplus
extern "C" {
#endif

u16 *GSmemAlloc(u32);
void GSmemFree(void *);
s32 mailGetNbMailInMailbox(void);
u16 mailGetMailIDInMailbox(s32);
u32 mailGetSenderName(u16);
u32 mailGetSubject(u16);
u32 mailGetSortMode(void);
u32 cursorBiosGetPos(s32);
void cursorBiosSetPos(s32, PdaMailCursor *);
PdaMailKey *windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
u8 winSeqCheckMove(s32);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(PdaMailSprite *, s32);
u32 GSmsgGetGSchar(u32);
u32 GSmsgGetRect(u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
void GSsndPlayNow(u32);
void msgctrlSetValue(s32, u32);
PdaMailItem *menuItemBiosGetPtr(s32, s16);
s32 menuOpen(s32, s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
PdaMailCursor *menuPdaMailXD(PdaMailCursor *, s32, s32);
void spriteClearScissor(s32);
void spriteSetScissor(s32, s32, s32, s16, s16);
void menuPdaSubInitAlpha(f32 *, s32, s16);
void menuPdaSubCalcAlpha(f32 *, s32, s16);
void menuPdaSubCalcPositon(f32 *, f32, f32);
void menuPdaSubCheckUpDownCursor(PdaMailWindow *, PdaMailSprite *, PdaMailCursor *, s32, s32, s32);
void menuPdaSubScrollBar(PdaMailWindow *, PdaMailSprite *, s32, s32, u32, s32, s32,
                         PdaMailCursor *);

static u16 *_sortwork;
PdaMailWork _maillistwork;
static f32 _menuPdaMailAlpha[5];
void menuPdaMailListSortExit(void);
s32 menuPdaMailListSortInit(s32 arg0);
void menuPdaMailListButtonXD(PdaMailWindow *arg0);
s32 menuPdaMailListCursorXD(PdaMailWindow *arg0);
s32 menuPdaMailListCallBack(PdaMailWindow *arg0, PdaMailSprite *arg1);
static void _pdaMailListDownCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                        PdaMailSprite *arg1);
static void _pdaMailListUpCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                      PdaMailSprite *arg1);
static void _pdaMailListCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                    PdaMailSprite *arg1);
static void _pdaMailListScrollBar__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                       PdaMailSprite *arg1);
s32 menuPdaMailListCtrlXD(PdaMailWindow *arg0);
s32 menuPdaMailListSubXD(s32 arg0, PdaMailCursor *arg1);
void menuPdaMailListXD(void);
static void _menuPdaMailListXDInit__Fv(void);
static void _menuPdaMailListMain__FP14tagWINDOW_WORK(PdaMailWindow *arg0);
static void _menuPdaMailListCalcPosition__FP6CURSOR(PdaMailCursor *arg0);
static void _menuPdaMailListPosition__Fv(void);
static void _menuPdaMailCalc__FPfff(f32 *position, f32 target, f32 speed);
static s32 _pdaMailListDraw__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                 PdaMailSprite *arg1);
static s32 _pdaMailListPageBunbo__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                      PdaMailSprite *arg1);
static s32 _pdaMailListPageBunshi__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                       PdaMailSprite *arg1);
static void _pdaMailListPage__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                  PdaMailSprite *arg1);
static void _menuClose__Fl(s32 arg0);
static void _sortReceive__FPUs(u16 *arg0);
static void _pdaMailSort__Fv(void);
static void _setCursor__F6CURSOR(const PdaMailCursor *arg0);
static u32 _getCursor__Fv(void);
static u32 _getSenderName__Fl(s32 index);
static u32 _getSubject__Fl(s32 index);
static u16 _getMailID__Fl(s32 index);
u16 pdaMailGetMailID(s32 arg0);
void menuPdaMailListSortExit(void) {
    if (_sortwork != 0) {
        if (_sortwork != 0) {
            GSmemFree(_sortwork);
            _sortwork = 0;
        }
    }
}

s32 menuPdaMailListSortInit(s32 arg0) {
    s32 temp_r3;
    s32 var_ctr;
    s32 var_r3;
    u16 *var_r3_2;
    u16 *var_r4;

    temp_r3 = mailGetNbMailInMailbox();
    if (temp_r3 > 0) {
        var_r3_2 = GSmemAlloc(temp_r3 * 2);
    } else {
        var_r3_2 = 0;
    }
    _sortwork = var_r3_2;
    if (var_r3_2 != 0) {
        _pdaMailSort__Fv();
        var_r4 = _sortwork;
        var_r3 = 0;
        var_ctr = temp_r3;
        if (temp_r3 > 0) {
        loop_5:
            if (arg0 == (s32)*var_r4) {
                return var_r3;
            }
            var_r4 += 1;
            var_r3 += 1;
            var_ctr -= 1;
            if (var_ctr == 0) {
                goto block_8;
            }
            goto loop_5;
        }
    block_8:
        return -1;
    }
    return -1;
}

void menuPdaMailListButtonXD(PdaMailWindow *arg0) {
    s32 temp_r31;
    u16 temp_r3;

    if (arg0 != 0) {
        temp_r31 = mailGetNbMailInMailbox();
        if (winSeqCheckMove(arg0->menu) == 0) {
            temp_r3 = windowGetKeyInfo()->triggers;
            if ((temp_r31 != 0) && ((s32)(temp_r3 & 0x10) != 0)) {
                arg0->accepted = 1;
            }
            if ((s32)(temp_r3 & 0x20) != 0) {
                arg0->accepted = 1;
                arg0->cancelled = 1;
            }
        }
    }
}

s32 menuPdaMailListCursorXD(PdaMailWindow *arg0) {
    PdaMailCursor cursor, copy;
    s32 count, visible = 5;
    u16 repeat;
    s16 selected;
    windowGetKeyInfo();
    cursor.packed = _getCursor__Fv();
    cursor.pos.first = arg0->first;
    cursor.pos.selected = arg0->selected;
    count = mailGetNbMailInMailbox();
    if (count < 5)
        visible = count;
    repeat = windowGetKeyRepeat();
    if (visible != 0) {
        if (repeat & 1) {
            if (cursor.pos.selected + cursor.pos.first != 0)
                GSsndPlayNow(0x450);
            cursor.pos.selected--;
        } else if (repeat & 2) {
            if (count - 1 != cursor.pos.selected + cursor.pos.first)
                GSsndPlayNow(0x450);
            cursor.pos.selected++;
        } else if (repeat & 8) {
            if (count - 1 != cursor.pos.selected + cursor.pos.first)
                GSsndPlayNow(0x453);
            cursor.pos.selected += visible;
        } else if (repeat & 4) {
            if (cursor.pos.selected + cursor.pos.first != 0)
                GSsndPlayNow(0x453);
            cursor.pos.selected -= visible;
        }
        selected = cursor.pos.selected;
        if (selected < 0) {
            cursor.pos.selected = 0;
            cursor.pos.first += selected;
            if (cursor.pos.first < 0) {
                cursor.pos.first = 0;
                cursor.pos.selected = 0;
            }
        } else if (selected >= visible) {
            s8 last = visible - 1;
            cursor.pos.selected = last;
            cursor.pos.first += selected - last;
            if (cursor.pos.first + last >= count) {
                cursor.pos.selected = last;
                cursor.pos.first = (s8)(count - visible);
            }
        }
    }
    copy.packed = cursor.packed;
    _setCursor__F6CURSOR(&copy);
    arg0->first = cursor.pos.first;
    arg0->selected = cursor.pos.selected;
    return 0;
}

s32 menuPdaMailListCallBack(PdaMailWindow *arg0, PdaMailSprite *arg1) {
    s16 temp_r5;

    temp_r5 = arg1->id;
    switch (temp_r5) {
    case 0x8D:
        _pdaMailListScrollBar__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x9C:
        _pdaMailListPageBunshi__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x9B:
        _pdaMailListPage__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x9A:
        _pdaMailListPageBunbo__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x97:
        _pdaMailListDraw__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x98:
        arg1->red = 0xF0;
        arg1->green = 0xF0;
        arg1->blue = 0xF0;
        break;
    case 0x99:
        arg1->red = 0xD5;
        arg1->green = 0xAA;
        arg1->blue = 0x33;
        break;
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
        _pdaMailListCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x8B:
        _pdaMailListUpCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    case 0x8C:
        _pdaMailListDownCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(arg0, arg1);
        break;
    }
    return 0;
}

static void _pdaMailListDownCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                        PdaMailSprite *arg1) {
    PdaMailCursor cursor;
    cursor.packed = _getCursor__Fv();
    menuPdaSubCheckUpDownCursor(arg0, arg1, &cursor, mailGetNbMailInMailbox(), 5, 0);
}

static void _pdaMailListUpCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                      PdaMailSprite *arg1) {
    PdaMailCursor cursor;
    cursor.packed = _getCursor__Fv();
    menuPdaSubCheckUpDownCursor(arg0, arg1, &cursor, mailGetNbMailInMailbox(), 5, 1);
}

static void _pdaMailListCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                    PdaMailSprite *arg1) {
    struct MailCursorIds {
        s32 a, b, c, d, e;
    } ids = {0x81, 0x82, 0x83, 0x84, 0x85};
    s32 id0 = ids.a, id1 = ids.b, id2 = ids.c, id3 = ids.d, id4 = ids.e;
    s16 selected;
    s32 index = 0;
    selected = arg0->selected;
    if (mailGetNbMailInMailbox() == 0)
        selected = 0;
    if (arg1->id != id0) {
        index = 1;
        if (arg1->id != id1) {
            index = 2;
            if (arg1->id != id2) {
                index = 3;
                if (arg1->id != id3) {
                    index = 4;
                    if (arg1->id != id4)
                        index = 5;
                }
            }
        }
    }
    arg1->alpha = _menuPdaMailAlpha[index];
    if (selected == index) {
        winSpriteSetDisp(arg1, 1);
        return;
    }
    if (_menuPdaMailAlpha[index] == 0.0f)
        winSpriteSetDisp(arg1, 0);
}

static void _pdaMailListScrollBar__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                       PdaMailSprite *arg1) {
    PdaMailCursor cursor;
    s32 count = mailGetNbMailInMailbox();
    cursor.packed = _getCursor__Fv();
    menuPdaSubScrollBar(arg0, arg1, 0x6e, 0x8d, 0xf2642200, count, 5, &cursor);
}

s32 menuPdaMailListCtrlXD(PdaMailWindow *arg0) {
    u8 temp_r0;

    temp_r0 = arg0->phase;
    switch ((s8)temp_r0) { /* irregular */
    case 0:
        if ((s8)arg0->step == 0) {
            winSeqSetMenu(arg0->menu, 0x132);
            arg0->step = 1U;
        }
        break;
    case 2:
        _menuPdaMailListMain__FP14tagWINDOW_WORK(arg0);
        break;
    case 3:
        if ((s8)arg0->step == 0) {
            winSeqSetMenu(arg0->menu, 0x136);
            arg0->step = 1U;
        }
        break;
    }
    return 0;
}

s32 menuPdaMailListSubXD(s32 arg0, PdaMailCursor *arg1) {
    PdaMailCursor cursor, copy, returned;
    s32 result;
    cursor.pos.first = arg1->pos.first;
    cursor.pos.selected = arg1->pos.selected;
    copy.packed = cursor.packed;
    _setCursor__F6CURSOR(&copy);
    do {
        result = menuOpen(0x6e, 1);
        returned.packed = _getCursor__Fv();
        cursor.pos.first = returned.pos.first;
        cursor.pos.selected = returned.pos.selected;
    } while (result != -1 && cursor.pos.selected >= 5);
    _menuClose__Fl(0x6e);
    if (result == -1 || mailGetNbMailInMailbox() == 0)
        return -1;
    arg1->pos.selected = cursor.pos.selected;
    arg1->pos.first = cursor.pos.first;
    return cursor.pos.first + cursor.pos.selected;
}

void menuPdaMailListXD(void) {
    PdaMailCursor cursor;
    s32 selected = 0;
    s32 count = mailGetNbMailInMailbox();
    u16 *sort;
    if (count > 0)
        sort = GSmemAlloc(count * 2);
    else
        sort = 0;
    _sortwork = sort;
    _menuPdaMailListXDInit__Fv();
    _pdaMailSort__Fv();
    cursor.pos.selected = 0;
    cursor.pos.first = 0;
    menuOpen(0x77, 0);
    while ((selected = menuPdaMailListSubXD(selected, &cursor)) >= 0) {
        PdaMailCursor *returned = menuPdaMailXD(&cursor, 1, 0);
        cursor.pos.selected = returned->pos.selected;
        cursor.pos.first = returned->pos.first;
        menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, cursor.pos.selected);
        _menuPdaMailListCalcPosition__FP6CURSOR(&cursor);
        _maillistwork.y = _maillistwork.targetY;
    }
    _menuClose__Fl(0x77);
    if (count > 0 && _sortwork != 0) {
        GSmemFree(_sortwork);
        _sortwork = 0;
    }
}

static void _menuPdaMailListXDInit__Fv(void) {
    s32 temp_r3;

    temp_r3 = mailGetNbMailInMailbox();
    _maillistwork.cursor.pos.selected = 0;
    _maillistwork.cursor.pos.first = 0;
    _maillistwork.x = 0.0f;
    _maillistwork.y = 0.0f;
    _maillistwork.targetX = 0.0f;
    _maillistwork.targetY = 0.0f;
    _maillistwork.state = 0;
    if (temp_r3 >= 5) {
        _maillistwork.visible = 5;
    } else {
        _maillistwork.visible = temp_r3;
    }
    menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, 0);
}

static void _menuPdaMailListMain__FP14tagWINDOW_WORK(PdaMailWindow *arg0) {
    PdaMailCursor cursor;
    cursor.packed = _getCursor__Fv();
    _menuPdaMailListPosition__Fv();
    _menuPdaMailListCalcPosition__FP6CURSOR(&cursor);
    menuPdaSubCalcAlpha(_menuPdaMailAlpha, 5, cursor.pos.selected);
}

static void _menuPdaMailListCalcPosition__FP6CURSOR(PdaMailCursor *arg0) {
    _maillistwork.targetY = (f32)(-arg0->pos.first * 47);
}

static void _menuPdaMailListPosition__Fv(void) {
    if (_maillistwork.x != _maillistwork.targetX)
        _menuPdaMailCalc__FPfff(&_maillistwork.x, _maillistwork.targetX, 20.0f);
    if (_maillistwork.y != _maillistwork.targetY)
        _menuPdaMailCalc__FPfff(&_maillistwork.y, _maillistwork.targetY, 20.0f);
}

static void _menuPdaMailCalc__FPfff(f32 *position, f32 target, f32 speed) {
    menuPdaSubCalcPositon(position, target, speed);
}

static s32 _pdaMailListDraw__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                 PdaMailSprite *arg1) {
    PdaMailCursor sp8;
    u32 subject, sender;
    f32 var_f30;
    s32 temp_r24;
    s32 temp_r25;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;
    s32 var_r23;
    u8 temp_r0;
    PdaMailItem *temp_r27;
    PdaMailItem *temp_r3;

    sp8.packed = _getCursor__Fv();
    temp_r31 = mailGetNbMailInMailbox();
    temp_r0 = arg0->alpha;
    temp_r30 = temp_r0 | 0xD5AA0000 | 0x3300;
    temp_r29 = temp_r0 | 0xF0F00000 | 0xF000;
    temp_r27 = menuItemBiosGetPtr(0x6E, 0x70);
    temp_r3 = menuItemBiosGetPtr(0x6E, arg1->id);
    spriteSetScissor(arg0->layer, temp_r27->x - temp_r3->x, temp_r27->y - temp_r3->y,
                     temp_r27->width, temp_r27->height);
    var_f30 = _maillistwork.y;
    var_r23 = 0;
    temp_r25 = (s32)_maillistwork.x;
    temp_r24 = (s32)(47.0f + _maillistwork.x);
    for (var_r23 = 0; var_r23 < temp_r31; var_r23++) {
        if ((var_r23 >= (s32)(sp8.pos.first - 1)) && (var_r23 < (s32)(sp8.pos.first + 6))) {
            if ((subject = _getSubject__Fl(var_r23)) != 0U) {
                subject = GSmsgGetGSchar(subject);
                msgctrlSetValue(0x37, subject);
                GSmsgPrint2(arg0->layer, temp_r25, (s32)var_f30, temp_r30 | arg0->alpha, 0x4276);
            } else {
                GSmsgPrint2(arg0->layer, temp_r25, (s32)var_f30, temp_r30 | arg0->alpha, 0);
            }
            if ((sender = _getSenderName__Fl(var_r23)) != 0U) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(sender));
                GSmsgPrint2(arg0->layer, temp_r24, (s32)(21.0f + var_f30), temp_r29 | arg0->alpha,
                            0x4276);
            } else {
                GSmsgPrint2(arg0->layer, temp_r24, (s32)(21.0f + var_f30), temp_r29 | arg0->alpha,
                            0);
            }
        }
        var_f30 += 47.0f;
    }
    spriteClearScissor(arg0->layer);
    return 0;
}

static s32 _pdaMailListPageBunbo__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                      PdaMailSprite *arg1) {
    s32 temp_r3;

    temp_r3 = mailGetNbMailInMailbox();
    if (temp_r3 != 0) {
        msgctrlSetValue(0x34, temp_r3);
        GSmsgPrint2(arg0->layer, arg1->width - (GSmsgGetRect(0x426F) >> 0x10U), 0,
                    arg0->alpha | ~0xFF, 0x426F);
    }
    return 0;
}

static s32 _pdaMailListPageBunshi__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                       PdaMailSprite *arg1) {
    if (mailGetNbMailInMailbox() != 0) {
        msgctrlSetValue(0x34, arg0->first + (arg0->selected + 1));
        GSmsgPrint2(arg0->layer, arg1->width - (GSmsgGetRect(0x426F) >> 0x10U), 0,
                    arg0->alpha | ~0xFF, 0x426F);
    }
    return 0;
}

static void _pdaMailListPage__FP14tagWINDOW_WORKP14tagSPRITE_WORK(PdaMailWindow *arg0,
                                                                  PdaMailSprite *arg1) {
    if (mailGetNbMailInMailbox() != 0) {
        winSpriteSetDisp(arg1, 1);
        return;
    }
    winSpriteSetDisp(arg1, 0);
}

static void _menuClose__Fl(s32 arg0) {
    menuClose(arg0);
    menuCloseSync(arg0, 1);
}

static void _sortReceive__FPUs(u16 *arg0) {
    s32 var_r31;
    u16 *var_r30;
    u16 temp_r0;

    var_r30 = arg0;
    var_r31 = mailGetNbMailInMailbox() - 1;
    while (var_r31 >= 0) {
        temp_r0 = mailGetMailIDInMailbox(var_r31);
        var_r31 -= 1;
        *var_r30 = temp_r0;
        var_r30 += 1;
    }
}

static void _pdaMailSort__Fv(void) {
    u16 *temp_r31;

    temp_r31 = _sortwork;
    mailGetSortMode();
    _sortReceive__FPUs(temp_r31);
}

static void _setCursor__F6CURSOR(const PdaMailCursor *arg0) {
    PdaMailCursor cursor;
    cursor.packed = arg0->packed;
    cursorBiosSetPos(10, &cursor);
}

static u32 _getCursor__Fv(void) { return cursorBiosGetPos(10); }

static u32 _getSenderName__Fl(s32 index) { return mailGetSenderName(_getMailID__Fl(index)); }

static u32 _getSubject__Fl(s32 index) { return mailGetSubject(_getMailID__Fl(index)); }

static u16 _getMailID__Fl(s32 index) { return pdaMailGetMailID(index); }

u16 pdaMailGetMailID(s32 arg0) {
    if ((arg0 < 0) || (arg0 >= mailGetNbMailInMailbox())) {
        return -1U;
    }
    return _sortwork[arg0];
}

#ifdef __cplusplus
}
#endif
