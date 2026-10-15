#include <game/menuBattleDiskLayout.hpp>

BDisk gBDisk;

Hero::Hero() {}

s32 deckDataVirtualDB_GetExplanetion1(u16);
s32 deckDataVirtualDB_GetExplanetion2(u16);
s32 deckDataVirtualDB_GetTitle(u16);
void drawPkmPanel(u32, tagWINDOW_WORK*, tagSPRITE_WORK*);

struct GSvec2 {
    f32 x;
    f32 y;
};
struct Pokemon {
    void* getPokemonDataPtr() const;
};
s32 cBattleDisk::mItemCurIdx[8] = {0x6F9, 0x6FB, 0x6FD, 0x6FF, 0x701, 0x703, 0x705, 0x707};
s32 cBattleDisk::mContentsCurIdx[15] = {0x76F, 0x770, 0x771, 0x772, 0x773, 0x774, 0x775, 0x776,
                                        0x777, 0x778, 0x7B6, 0x7B7, 0x7B8, 0x7B9, 0x7BA};

extern "C" {
Pokemon* heroBiosGetPokemonPtr(Hero*, u16);
s32 pokemonDataBiosGetStatusFaceMenuSpriteId(void*, s32);
void menuFaceDispFromID2(tagWINDOW_WORK*, tagSPRITE_WORK*, u16, GSvec2*);
void* memcpy(void*, const void*, u32);
u16 itemBiosGetItemDataId(void*);
u8 itemCheckValid(void*);
void* itemDataBiosGetPtr(u16);
s32 itemDataBiosGetName(void*);
s32 itemDataBiosGetDoc(void*);
void* heroItemGetItemKindToItemAryPtr(Hero*, s32, u16*, s32, s32, s32);
void fightReadResourceID(s32, s32);
void menuItemBiosSetSelectFlag(s32, s32, s32);
void menuPlaySe(s32, s32);
void menuCursorNormal(tagWINDOW_WORK*, s32);
u16 windowGetKeyRepeat(void);
void GSfloorPush(s32);
BDiskMenuData* menuDataBiosGetPtr(s32);
BDiskMenuItem* menuItemBiosGetPtr(s32, s16);
BDiskMenuItem* windowGetCursorToItem(tagWINDOW_WORK*);
u16* windowGetKeyInfo(void);
u16* windowGetKeyInfo2(void);
void fn_8009E6B8(tagWINDOW_WORK*, u8);
u32 heroGetPokeomCount(Hero*);
void menuSetPosition(s32, s16, s16);
void winSeqSetMenu(s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK*, s32);
u8 winSeqCheckMove(s32);
u8 GSgfxVideoGetVsyncRate(void);
void floorSetFadeScript(s32, s32);
void floorWaitForChange(void);
void fightFreeResourceID(s32, s32);
void menuClose(s32);
void menuCreateOffScreen(u8, f32, f32);
void menuOffScreenFadeSync(s32);
void menuOffScreenSetPriority(s32);
s32 menuOpenCustom(s32, s32, ...);
void menuReleaseOffScreen(u8, f32);
s32 windowGetActiveID(void);
}

static s32 getPanelIdx(u32, u8);

extern "C" {

s32 fn_8009E664(tagWINDOW_WORK* win) {
    if (winSeqCheckMove(0xEC) != 0) {
        return 0;
    }
    fn_8009E6B8(win, 1);
    return 0;
}

void fn_8009E6B8(tagWINDOW_WORK* win, u8 useKey2) {
    BDiskMenuData* data;
    BDiskMenuItem* cur;
    BDiskMenuItem* item;
    s32 limX;
    s32 limY;
    s32 best;
    s32 diff;
    s32 d;
    s8 idx;
    u16 key;
    u16 hold;
    if (win == 0) {
        return;
    }
    data = menuDataBiosGetPtr(win->menu);
    cur = windowGetCursorToItem(win);
    if (cur == 0) {
        win->cursor = 0;
        return;
    }
    limX = 0x10;
    limY = 0xC;
    key = windowGetKeyInfo()[3];
    hold = windowGetKeyInfo()[0];
    if (useKey2 != 0) {
        if ((hold & 0xF) != 0) {
            hold = 0;
        } else {
            hold = windowGetKeyInfo2()[3];
        }
    } else {
        hold = 0;
    }
    key |= hold;
    for (;;) {
        idx = 0;
        item = menuItemBiosGetPtr(win->menu, data->first);
        if (key & 1) {
            best = 0x1E0;
            for (;;) {
                if (item->enable) {
                    diff = cur->y - item->y;
                    if (diff > 0) {
                        d = cur->x - item->x;
                        if (d < 0) d = -d;
                        if (d < limX && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 2) {
            best = 0x1E0;
            for (;;) {
                if (item->enable) {
                    diff = item->y - cur->y;
                    if (diff > 0) {
                        d = cur->x - item->x;
                        if (d < 0) d = -d;
                        if (d < limX && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 4) {
            best = 0x280;
            for (;;) {
                if (item->enable) {
                    diff = cur->x - item->x;
                    if (diff > 0x1E) {
                        d = cur->y - item->y;
                        if (d < 0) d = -d;
                        if (d < limY && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        } else if (key & 8) {
            best = 0x280;
            for (;;) {
                if (item->enable) {
                    diff = item->x - cur->x;
                    if (diff > 0x1E) {
                        d = cur->y - item->y;
                        if (d < 0) d = -d;
                        if (d < limY && best > diff) {
                            best = diff;
                            win->cursor = idx;
                        }
                    }
                    idx++;
                }
                if (item->last) break;
                item = menuItemBiosGetPtr(win->menu, item->next);
            }
        }
        if (win->prevCursor != win->cursor) break;
        limX += 0x10;
        limY += 0xC;
        if (limX >= 0x280) limX = 0x280;
        if (limY >= 0x1E0) limY = 0x1E0;
        if (limX == 0x280 && limY == 0x1E0) break;
    }
}

s32 fn_8009E9FC(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
    case 1:
    case 2:
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 fn_8009EA68(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                winSeqSetMenu(win->menu, 0x1EE);
            } else {
                winSeqSetMenu(win->menu, 0x1E6);
            }
            win->step = 1;
        }
        break;
    case 2:
        if (gBDisk.unk0 != gBDisk.unk4) {
            gBDisk.unk0 = gBDisk.unk4;
        }
        if (gBDisk.unk2 != gBDisk.unk6) {
            gBDisk.unk2 = gBDisk.unk6;
        }
        if (winSeqCheckMove(0xEC) == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                gBDisk.unk4 = 0x131;
                gBDisk.unk6 = 0;
            } else {
                gBDisk.unk4 = 0;
                gBDisk.unk6 = 0;
            }
            menuSetPosition(0xEC, gBDisk.unk0, gBDisk.unk2);
        }
        break;
    case 3:
        if (win->step == 0) {
            s16 idx = gBDisk.unk14;
            if (idx < heroGetPokeomCount(&gBDisk.heroes[0])) {
                winSeqSetMenu(win->menu, 0x1F2);
            } else {
                winSeqSetMenu(win->menu, 0x1EA);
            }
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 BattleDiskContentsDraw(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    u32 idx = 0;
    switch (sprite->id) {
    case 0x751:
        break;
    case 0x753:
        if (gBDisk.unk16 == 1) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x754:
    case 0x755:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x756:
        if (gBDisk.unk16 == 2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x76E:
        idx = 1;
    case 0x76D:
        idx += 1;
    case 0x76C:
        idx += 1;
    case 0x76B:
        idx += 1;
    case 0x76A:
        idx += 1;
    case 0x769:
        idx += 1;
    case 0x768:
        idx += 1;
    case 0x767:
        idx += 1;
    case 0x766:
        idx += 1;
    case 0x765:
        idx += 1;
    case 0x764:
        idx += 1;
    case 0x763:
        idx += 1;
    case 0x762:
        idx += 1;
    case 0x761:
        idx += 1;
    case 0x760:
        if (getPanelIdx(idx, gBDisk.unk16) >= 0) {
            drawPkmPanel(getPanelIdx(idx, gBDisk.unk16), win, sprite);
        }
        break;
    case 0x7BB:
        sprite->value4C = deckDataVirtualDB_GetExplanetion2(gBDisk.selectedID);
        break;
    case 0x7BC:
        if (win->menu != windowGetActiveID()) {
            sprite->value4C = 0xE2E2;
        } else {
            sprite->value4C = 0xE300;
        }
        break;
    case 0x7BD:
        if (win->menu == windowGetActiveID()) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    case 0x7BE:
        if (win->menu != windowGetActiveID()) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        break;
    }
    return 0;
}

}

static s32 getPanelIdx(u32 id, u8 mode) {
    s32 idx = -1;
    switch (id) {
    case 0:
        idx = 0;
        break;
    case 1:
        if (mode == 2) idx = 1;
        break;
    case 2:
        if (mode == 1) idx = 1;
        break;
    case 3:
        idx = 2;
        break;
    case 4:
        idx = 3;
        break;
    case 5:
        idx = 4;
        break;
    case 6:
        idx = 5;
        break;
    case 7:
        if (mode != 2 || heroGetPokeomCount(&gBDisk.heroes[1]) != 1) idx = 6;
        break;
    case 8:
        if (mode == 2 && heroGetPokeomCount(&gBDisk.heroes[1]) == 1) idx = 6;
        break;
    case 9:
        if (mode == 2 && heroGetPokeomCount(&gBDisk.heroes[1]) != 1) idx = 7;
        break;
    case 10:
        if (mode == 1) idx = 7;
        break;
    case 11:
        idx = 8;
        break;
    case 12:
        idx = 9;
        break;
    case 13:
        idx = 10;
        break;
    case 14:
        idx = 11;
        break;
    }
    return idx;
}

static void dispFace(u32 index, GSvec2* pos, tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, Pokemon* pokemon) {
    u8 backup[0x78];
    s32 face = pokemonDataBiosGetStatusFaceMenuSpriteId(pokemon->getPokemonDataPtr(), 0);
    memcpy(backup, sprite, 0x78);
    sprite->y = 0x2A;
    sprite->x = 0x2A;
    if (index < 6) {
        sprite->x *= -1;
    }
    menuFaceDispFromID2(win, sprite, face, pos);
    memcpy(sprite, backup, 0x78);
}

static Pokemon* loadPkmFace(void* arg) {
    Pokemon* result = 0;
    if (*(u32*)arg < 12) {
        if (*(u32*)arg < 6) {
            Hero* hero = &gBDisk.heroes[0];
            if (*(u32*)arg < heroGetPokeomCount(hero)) {
                result = heroBiosGetPokemonPtr(hero, *(u32*)arg);
            } else {
                *(u32*)arg = 6;
            }
        }
        if (*(u32*)arg >= 6) {
            u16 slot = *(u32*)arg % 6;
            Hero* hero = &gBDisk.heroes[1];
            if (slot < heroGetPokeomCount(hero)) {
                result = heroBiosGetPokemonPtr(hero, slot);
            }
        }
    }
    *(u32*)arg = *(u32*)arg + 1;
    return result;
}

extern "C" {

s32 menuBdisk_selectL_Btn(tagWINDOW_WORK* win) {
    s16 scroll;
    u16 key;
    key = windowGetKeyRepeat();
    gBDisk.unk12 = win->cursor;
    scroll = gBDisk.scroll;
    if (key & 2) {
        if (gBDisk.unk10 == gBDisk.unkE && win->cursor == 7 && gBDisk.scroll < gBDisk.count - 8) {
            gBDisk.scroll++;
            gBDisk.unkE = gBDisk.scroll * -0x1E;
            menuPlaySe(win->menu, 1);
        }
    } else if (key & 1) {
        if (gBDisk.unk10 == gBDisk.unkE && win->cursor == 0 && gBDisk.scroll != 0) {
            gBDisk.scroll--;
            gBDisk.unkE = gBDisk.scroll * -0x1E;
            menuPlaySe(win->menu, 1);
        }
    } else if (key & 4) {
        s16 pos;
        gBDisk.scroll -= 8;
        if (gBDisk.scroll < 0) {
            win->cursor = 0;
            gBDisk.unk12 = 0;
            gBDisk.scroll = 0;
        }
        if (scroll != gBDisk.scroll) {
            menuPlaySe(win->menu, 6);
        }
        pos = gBDisk.scroll * -0x1E;
        gBDisk.unkE = pos;
        gBDisk.unk10 = pos;
    } else if (key & 8) {
        s16 pos;
        if (gBDisk.count < 8) {
            s16 last;
            gBDisk.scroll = 0;
            last = gBDisk.count - 1;
            win->cursor = last;
            gBDisk.unk12 = last;
        } else {
            gBDisk.scroll += 8;
            if (gBDisk.count - 8 < gBDisk.scroll) {
                gBDisk.scroll = gBDisk.count - 8;
                win->cursor = 7;
                gBDisk.unk12 = 7;
            }
        }
        if (scroll != gBDisk.scroll) {
            menuPlaySe(win->menu, 6);
        }
        pos = gBDisk.scroll * -0x1E;
        gBDisk.unkE = pos;
        gBDisk.unk10 = pos;
    }
    menuCursorNormal(win, 1);
    return 0;
}

s32 fn_800A08C0(tagWINDOW_WORK* win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x24);
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x17B);
            win->step = 1;
        }
        break;
    }
    return 0;
}

s32 menuBattleDiskCtrl(void) {
    return 0;
}

void menuBattleDiskExit(void) {
    fightFreeResourceID(0x842, 0x18513400);
}

void menuBattleDiskInit(void) {
    u16 count;
    s32* item;
    u16 n;
    s32 i;
    item = (s32*)heroItemGetItemKindToItemAryPtr(Hero::getHeroPtr(), 7, &count, 0, 0, 0);
    n = 0;
    fightReadResourceID(0x842, 0x18513400);
    for (i = 0; i < count; i++) {
        if (itemCheckValid(item)) {
            bdiskEntry(n)->itemID = itemBiosGetItemDataId(item);
            bdiskEntry(n)->name = itemDataBiosGetName(itemDataBiosGetPtr(bdiskEntry(n)->itemID));
            bdiskEntry(n)->doc = itemDataBiosGetDoc(itemDataBiosGetPtr(bdiskEntry(n)->itemID));
            bdiskEntry(n)->id = bdiskEntry(n)->itemID - 0x215;
            bdiskEntry(n)->explain1 = deckDataVirtualDB_GetExplanetion1(bdiskEntry(n)->id);
            bdiskEntry(n)->explain2 = deckDataVirtualDB_GetExplanetion2(bdiskEntry(n)->id);
            bdiskEntry(n)->title = deckDataVirtualDB_GetTitle(bdiskEntry(n)->id);
            n++;
        }
        item++;
    }
    gBDisk.count = n;
    {
        s32 j;
        for (j = 0; j < 8; j++) {
            if (j < gBDisk.count) {
                menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 1);
            } else {
                menuItemBiosSetSelectFlag(0xE8, cBattleDisk::mItemCurIdx[j], 0);
            }
        }
    }
}

void menuBattleDiskCloseDoc(void) {
    menuClose(0xE9);
}

void menuBattleDiskOpenDoc(u8 id) {
    gBDisk.selectedID = id;
    menuOpenCustom(0xE9, windowGetActiveID(), 0, 2, 0, 0);
}

s32 menuBattleDiskOpenDocPush(u8 id) {
    gBDisk.selectedID = id;
    gBDisk.mode = 2;
    u8 rate = GSgfxVideoGetVsyncRate();
    menuCreateOffScreen(rate, 8.0f / (f32)rate, 50.0f);
    menuOffScreenSetPriority(0);
    menuOffScreenFadeSync(1);
    GSfloorPush(0x38D);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    rate = GSgfxVideoGetVsyncRate();
    menuReleaseOffScreen(rate, 8.0f / (f32)rate);
    gBDisk.mode = 1;
    return gBDisk.field24;
}

u16 menuBattleDiskGetResult(void) {
    return gBDisk.result;
}

u8 menuBattleDiskGetSelectID(void) {
    return gBDisk.selectedID;
}

void menuBattleDiskOpenFight(void) {
    if (gBDisk.selectedID != 0) {
        gBDisk.mode = 1;
        GSfloorPush(0x389);
    }
}

void menuBattleDiskOpen(void) {
    gBDisk.mode = 0;
    u8 rate = GSgfxVideoGetVsyncRate();
    menuCreateOffScreen(rate, 20.0f / (f32)rate, 50.0f);
    GSfloorPush(0x389);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    rate = GSgfxVideoGetVsyncRate();
    menuReleaseOffScreen(rate, 20.0f / (f32)rate);
}

}
