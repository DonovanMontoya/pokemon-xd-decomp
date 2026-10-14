#include <game/menuPdaDPMonitorListLayout.hpp>

enum darkPokemonWhere {
    DARK_POKEMON_WHERE_0,
    DARK_POKEMON_WHERE_1
};

enum DPMSelSort {
    DPM_SEL_SORT_0,
    DPM_SEL_SORT_1,
    DPM_SEL_SORT_2
};

class DarkPokemon {
public:
    u16 getPokemonID() const;
    s32 getStatus() const;
    void getDarkPoint() const;
    void getPlace(darkPokemonWhere &, u8 &) const;
    bool isUpdate() const;
    u8 getSnatchIndex() const;
    void setUpdate(bool);
};

struct DpmMenuItem {
    u8 pad[0xA];
    s16 width;
    s16 height;
};

extern "C" {
DarkPokemon *darkPokemonGetDarkPokemon(u32);
struct DpmKeyInfo {
    u32 pad;
    u16 triggers;
};
DpmKeyInfo *windowGetKeyInfo(void);
void menuClose(s32);
void menuCloseSync(s32, s32);
CURSOR cursorBiosGetPos(s32);
void cursorBiosSetPos(s32, CURSOR *);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK *, tagSPRITE_WORK *, CURSOR *, s32, s32, s32);
void menuPdaSubCalcAlpha(void *, s32, s16);
void menuPdaSubInitAlpha(void *, s32, s16);
struct DpmSelCursor {
    s16 first;
    s16 selected;
};
DpmSelCursor *menuPdaDPMon(CURSOR *);
s32 darkPokemonGetMeetNum(void);
void *__nwa__FUl(u32);
void operator delete[](void *);
void operator delete(void *);
void *operator new(u32);
void menuPdaSubScrollBar(tagWINDOW_WORK *, tagSPRITE_WORK *, s32, s32, u32, s32, s32, CURSOR *);
u8 winSeqCheckMove(s32);
s32 menuOpen(s32, s32);
void winSeqSetMenu(s32, s32);
void menuPdaSetSubres(s32, s32);
DarkPokemon *menuPdaDPMListGetDPointer(long);
void menuPdaSubCalcPositon(f32 *, f32);
u32 pokemonDataBiosGetPtr(u16);
u32 pokemonDataBiosGetName(u32);
u32 GSmsgGetGSchar(u32);
void *memcpy(void *, const void *, u32);
void *savedataGetStatus(s32, s32);
void *heroBiosGetPokemonPtr(void *, u8);
u8 pokemonCheckValid(void *);
u16 pokemonBiosGetDarkpokemonDataId(void *);
u32 pokemonBiosGetPokemonDataId(void *);
DpmMenuItem *menuItemBiosGetPtr(s32, s16);
void menuDrawReliveMeterByDarkPokemon(DarkPokemon *, s32, s32, s16, s16, u8, s32);
void msgctrlSetValue(s32, u32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
}

class menuPdaDPMList;
extern menuPdaDPMList *pDPMList;

struct DpmEntry {
    u8 pad[6];
    u16 darkPokemonID;
};

struct SnatchSortBuff {
    u32 snatchIndex;
    u16 pokemonID;
    u16 darkID;
};

struct DpmTemp {
    u16 pokemonID;
    u16 darkID;
};

class menuPdaDPMList {
public:
    s32 count;
    u8 alpha[0x28];
    s16 cursorFirst;
    s16 cursorSelected;
    f32 posX;
    f32 posY;
    f32 targetX;
    f32 targetY;
    s32 unk40;
    s32 visible;
    s32 sortMode;
    u32 unk4C;
    DpmEntry *entries;
    u32 unk54;
    u32 unk58;
    s32 unk5C;

    menuPdaDPMList();
    ~menuPdaDPMList();
    u16 GetDarkPokemonID(long index);
    CURSOR _getCursor();
    void _setCursor(CURSOR c);
    void _menuClose(long id);
    void CalcPosition(CURSOR *c);
    void ListPosition();
    void ListMain(tagWINDOW_WORK *win);
    void DownCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void UpCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void InitWork();
    void *Main(long, CURSOR *);
    s32 Sort(DPMSelSort);
    s32 SortPokemon();
    s32 SortDP();
    s32 SortPlace();
    void SortSub(SnatchSortBuff *, long, bool);
    void SortSub2(SnatchSortBuff *, long, bool);
    void SortSetTemp(SnatchSortBuff *, SnatchSortBuff *, long);
    u32 getTemochiIndex(u16, u16);
    void ListCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void SortCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void DispList(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void SetItemColor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void ScrollBar(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite);
    void Button(tagWINDOW_WORK *win);
    void Cursor(tagWINDOW_WORK *win);
    void Ctrl(tagWINDOW_WORK *win);
};

menuPdaDPMList *pDPMList;

menuPdaDPMList::menuPdaDPMList() {
    unk4C = 0;
    entries = 0;
    unk54 = 0;
    unk58 = 0;
    count = 0;
    unk5C = 0;
}

u16 menuPdaDPMList::GetDarkPokemonID(long index) {
    return entries[index].darkPokemonID;
}

void menuPdaDPMList::DownCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    CURSOR c = _getCursor();
    menuPdaSubCheckUpDownCursor(win, sprite, &c, count, 10, 0);
}

void menuPdaDPMList::UpCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    CURSOR c = _getCursor();
    menuPdaSubCheckUpDownCursor(win, sprite, &c, count, 10, 1);
}

void menuPdaDPMList::ListMain(tagWINDOW_WORK *win) {
    CURSOR c = _getCursor();
    ListPosition();
    CalcPosition(&c);
    menuPdaSubCalcAlpha(alpha, 10, c.selected);
}

void menuPdaDPMList::CalcPosition(CURSOR *c) {
    targetY = (f32)(-c->first * 0x17);
}

void menuPdaDPMList::ListPosition() {
    if (posX != targetX) {
        menuPdaSubCalcPositon(&posX, 10.0f);
    }
    if (posY != targetY) {
        menuPdaSubCalcPositon(&posY, 10.0f);
    }
}

void menuPdaDPMList::_setCursor(CURSOR c) {
    CURSOR tmp = c;
    cursorBiosSetPos(0xC, &tmp);
}

CURSOR menuPdaDPMList::_getCursor() {
    return cursorBiosGetPos(0xC);
}

void menuPdaDPMList::_menuClose(long id) {
    menuClose(id);
    menuCloseSync(id, 1);
}

menuPdaDPMList::~menuPdaDPMList() {
    if (unk4C != 0) {
        delete[](u8 *) unk4C;
        unk4C = 0;
    }
    if (entries != 0) {
        delete[] entries;
        entries = 0;
    }
    if (unk54 != 0) {
        delete[](u8 *) unk54;
        unk54 = 0;
    }
    if (unk58 != 0) {
        delete[](u8 *) unk58;
        unk58 = 0;
    }
}

extern "C" u16 menuPdaDPMListGetDarkPokemonID(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    return pDPMList->GetDarkPokemonID(index);
}

extern "C" u16 menuPdaDPMListGetPokemonID(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    return darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index))->getPokemonID();
}

extern "C" u32 menuPdaDPMListGetPokemonName(s32 index) {
    if (pDPMList == 0) {
        return 0;
    }
    u32 ptr = pokemonDataBiosGetPtr(darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index))->getPokemonID());
    if (ptr != 0) {
        return GSmsgGetGSchar(pokemonDataBiosGetName(ptr));
    }
    return 0;
}

extern "C" u16 menuPdaDPMListGetDarkpokemonID(s32 index) {
    if (pDPMList != 0) {
        return pDPMList->GetDarkPokemonID(index);
    }
    return 0;
}

extern "C" DarkPokemon *menuPdaDPMListGetDPointer(long index) {
    return darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index));
}

extern "C" s32 menuPdaDPMListGetDPNum(void) {
    if (pDPMList == 0) {
        return 0;
    }
    return pDPMList->count;
}

extern "C" void menuPdaDPMListButton(tagWINDOW_WORK *win) {
    if (pDPMList != 0) {
        pDPMList->Button(win);
    }
}

extern "C" s32 menuPdaDPMListCursor(tagWINDOW_WORK *win) {
    if (pDPMList == 0) {
        return 0;
    }
    pDPMList->Cursor(win);
    return 0;
}

extern "C" s32 menuPdaDPMListCtrl(tagWINDOW_WORK *win) {
    if (pDPMList == 0) {
        return 0;
    }
    pDPMList->Ctrl(win);
    return 0;
}

extern "C" s32 menuPdaDPMListGetDarkPokemonPlace(long index, darkPokemonWhere *where, u8 *flag) {
    if (pDPMList == 0) {
        return 0;
    }
    DarkPokemon *dp = darkPokemonGetDarkPokemon(pDPMList->GetDarkPokemonID(index));
    s32 status = dp->getStatus();
    switch (status) {
    case 0:
    case 1:
    case 2:
        *where = (darkPokemonWhere)0;
        *flag = 0;
        break;
    case 3:
    case 4: {
        darkPokemonWhere w;
        u8 f;
        dp->getPlace(w, f);
        *where = w;
        *flag = f;
        break;
    }
    }
    return 1;
}

extern "C" u32 menuPdaDPMListGetDarkPokemonPlaceMsgID(long index, u8 *flag) {
    darkPokemonWhere w;
    u32 msg = 0;
    menuPdaDPMListGetDarkPokemonPlace(index, &w, flag);
    switch (w) {
    case 0:
        msg = 0;
        break;
    case 1:
        msg = 0x3C0C;
        break;
    case 2:
        msg = 0x3C0E;
        break;
    case 3:
        msg = 0x3C0D;
        break;
    case 4:
        msg = 0x3B7A;
        break;
    case 5:
    case 6:
        msg = 0x3C0F;
        break;
    }
    return msg;
}

extern "C" s32 menuPdaDPMListDispRelive(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite, s32 x, s32 y, long index, u8 color, u8 flag) {
    DarkPokemon *dp = menuPdaDPMListGetDPointer(index);
    s32 status = dp->getStatus();
    dp->getDarkPoint();
    switch (status) {
    case 0:
    case 1:
    case 2:
        break;
    case 3: {
        DpmMenuItem *item = menuItemBiosGetPtr(0x74, 0x4A);
        menuDrawReliveMeterByDarkPokemon(dp, x, y, item->width, item->height, WIN_ALPHA(win), win->layer);
        break;
    }
    case 4: {
        u32 str = GSmsgGetGSchar(0x3C0B);
        msgctrlSetValue(0x37, str);
        if (flag != 0) {
            GSmsgPrint2(win->layer, x, y, color | 0xEE444400, 0x4276);
        } else {
            GSmsgPrint2(win->layer, x, y, color | 0xEE444400, 0x4275);
        }
        break;
    }
    }
    return 1;
}

void menuPdaDPMList::ScrollBar(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    s32 n = count;
    CURSOR c = _getCursor();
    menuPdaSubScrollBar(win, sprite, 0x74, 0x37, 0xF2642200, n, 10, &c);
}

void menuPdaDPMList::Button(tagWINDOW_WORK *win) {
    if (win != 0) {
        s32 n = menuPdaDPMListGetDPNum();
        if (!winSeqCheckMove(win->menu)) {
            u16 trg = windowGetKeyInfo()->triggers;
            if (n != 0 && (trg & 0x10) != 0) {
                win->finished = 1;
            }
            if ((trg & 0x20) != 0) {
                win->finished = 1;
                win->cancelled = 1;
            }
        }
    }
}

void menuPdaDPMList::Ctrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x132);
            menuPdaSetSubres(0, 1);
            win->step = 1;
        }
        break;
    case 2:
        ListMain(win);
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x136);
            win->step = 1;
        }
        break;
    }
}

void menuPdaDPMList::InitWork() {
    s32 n = count;
    darkPokemonGetMeetNum();
    cursorSelected = 0;
    cursorFirst = 0;
    sortMode = 0;
    posX = 0.0f;
    posY = 0.0f;
    targetX = 0.0f;
    targetY = 0.0f;
    unk40 = 0;
    if (n >= 10) {
        visible = 10;
    } else {
        visible = n;
    }
    unk4C = (u32)__nwa__FUl(0x200);
    entries = (DpmEntry *)__nwa__FUl(0x400);
    unk54 = (u32)__nwa__FUl(0x400);
    unk58 = (u32)__nwa__FUl(0x400);
    Sort((DPMSelSort)sortMode);
    menuPdaSubInitAlpha(alpha, 10, 0);
}

void *menuPdaDPMList::Main(long, CURSOR *cursor) {
    CURSOR local;
    s32 ret;
    CURSOR c2;
    local.first = cursor->first;
    local.selected = cursor->selected;
    _setCursor(local);
    do {
        ret = menuOpen(0x74, 1);
        c2 = _getCursor();
        local.first = c2.first;
        local.selected = c2.selected;
        if (ret == -1) {
            break;
        }
    } while (local.selected >= 10);
    _menuClose(0x74);
    if (ret == -1 || count == 0) {
        return (void *)-1;
    }
    cursor->selected = local.selected;
    cursor->first = local.first;
    return (void *)(local.first + local.selected);
}

void menuPdaDPMList::SetItemColor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    switch (sprite->id) {
    case 0x4C:
        if (sortMode == 2) {
            sprite->color.value = 0xFFB400FF;
            return;
        }
        sprite->color.value = -1;
        return;
    case 0x4D:
        if (sortMode == 1) {
            sprite->color.value = 0xFFB400FF;
            return;
        }
        sprite->color.value = -1;
        return;
    case 0x4E:
        if (sortMode == 0) {
            sprite->color.value = 0xFFB400FF;
            return;
        }
        sprite->color.value = -1;
        return;
    }
}

extern "C" s32 menuPdaDPMListCallBack(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    if (pDPMList == 0) {
        return 0;
    }
    switch (sprite->id) {
    case 0x37:
        pDPMList->ScrollBar(win, sprite);
        break;
    case 0x4B:
        pDPMList->DispList(win, sprite);
        break;
    case 0x38:
    case 0x39:
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x3D:
    case 0x3E:
    case 0x3F:
    case 0x40:
    case 0x41:
        pDPMList->ListCursor(win, sprite);
        break;
    case 0x46:
        pDPMList->UpCursor(win, sprite);
        break;
    case 0x47:
        pDPMList->DownCursor(win, sprite);
        break;
    case 0x1CD:
    case 0x1CE:
    case 0x1CF:
        pDPMList->SortCursor(win, sprite);
        break;
    case 0x4C:
    case 0x4D:
    case 0x4E:
        pDPMList->SetItemColor(win, sprite);
        break;
    }
    return 0;
}

extern "C" void menuPdaDPMonList(void) {
    CURSOR c;
    s32 idx = 0;
    pDPMList = new menuPdaDPMList;
    pDPMList->InitWork();
    c.selected = 0;
    c.first = 0;
    menuOpen(0x77, 0);
    for (;;) {
        idx = (s32)pDPMList->Main(idx, &c);
        if (idx < 0) {
            break;
        }
        DarkPokemon *dp = darkPokemonGetDarkPokemon(menuPdaDPMListGetDarkPokemonID(c.selected + c.first));
        if (dp->isUpdate()) {
            dp->setUpdate(false);
        }
        DpmSelCursor *r = menuPdaDPMon(&c);
        c.selected = r->selected;
        c.first = r->first;
        menuPdaSubInitAlpha(pDPMList->alpha, 10, c.selected);
        pDPMList->CalcPosition(&c);
        pDPMList->posY = pDPMList->targetY;
    }
    pDPMList->_menuClose(0x77);
    delete pDPMList;
    pDPMList = 0;
}

s32 menuPdaDPMList::Sort(DPMSelSort mode) {
    switch (mode) {
    case 0:
        count = SortPokemon();
        break;
    case 1:
        count = SortDP();
        break;
    case 2:
        count = SortPlace();
        break;
    }
    return count;
}

void menuPdaDPMList::SortSetTemp(SnatchSortBuff *a, SnatchSortBuff *b, long n) {
    SnatchSortBuff *src = b;
    long i;
    for (i = 0; i < n; i++) {
        memcpy(a + unk5C, src, 8);
        src++;
        unk5C++;
    }
}

s32 menuPdaDPMList::SortPokemon() {
    s32 id;
    s32 n = 0;
    unk5C = 0;
    for (id = 1; id < 0x80; id++) {
        DarkPokemon *dp = darkPokemonGetDarkPokemon((u16)id);
        u16 pid = dp->getPokemonID();
        if (pid != 0 && dp->getStatus() >= 1) {
            ((DpmTemp *)unk4C)[n].pokemonID = pid;
            ((DpmTemp *)unk4C)[n].darkID = id;
            ((SnatchSortBuff *)entries)[n].snatchIndex = dp->getSnatchIndex();
            ((SnatchSortBuff *)entries)[n].pokemonID = ((DpmTemp *)unk4C)[n].pokemonID;
            ((SnatchSortBuff *)entries)[n].darkID = ((DpmTemp *)unk4C)[n].darkID;
            n++;
        }
    }
    SortSub((SnatchSortBuff *)entries, n, true);
    return n;
}

u32 menuPdaDPMList::getTemochiIndex(u16, u16 key) {
    void *p;
    void *hero = savedataGetStatus(0, 2);
    u32 i;
    for (i = 0; (u8)i < 6; i++) {
        p = heroBiosGetPokemonPtr(hero, i);
        if (pokemonCheckValid(p)) {
            u16 dark = pokemonBiosGetDarkpokemonDataId(p);
            pokemonBiosGetPokemonDataId(p);
            if (dark == key) {
                return i;
            }
        }
    }
    return 0;
}

void menuPdaDPMList::SortSub2(SnatchSortBuff *buf, long n, bool asc) {
    SnatchSortBuff tmp;
    long i;
    long j;
    SnatchSortBuff *q;
    SnatchSortBuff *p;
    if (asc) {
        q = buf + 1;
        for (i = 1; i < n; i++) {
            memcpy(&tmp, q, 8);
            j = i - 1;
            p = &buf[j];
            while (j >= 0 && (s32)p->snatchIndex > (s32)tmp.snatchIndex) {
                memcpy(&buf[j + 1], p, 8);
                p--;
                j--;
            }
            memcpy(&buf[j + 1], &tmp, 8);
            q++;
        }
        return;
    }
    long j2;
    long i2;
    SnatchSortBuff *p2;
    SnatchSortBuff *q2;
    q2 = buf + 1;
    for (i2 = 1; i2 < n; i2++) {
        memcpy(&tmp, q2, 8);
        j2 = i2 - 1;
        p2 = &buf[j2];
        while (j2 >= 0 && (s32)p2->snatchIndex < (s32)tmp.snatchIndex) {
            memcpy(&buf[j2 + 1], p2, 8);
            p2--;
            j2--;
        }
        memcpy(&buf[j2 + 1], &tmp, 8);
        q2++;
    }
}

void menuPdaDPMList::SortSub(SnatchSortBuff *buf, long n, bool asc) {
    SnatchSortBuff tmp;
    long gap;
    long i;
    long j;
    SnatchSortBuff *a;
    SnatchSortBuff *b;
    if (asc) {
        for (gap = n / 2; gap > 0; gap /= 2) {
            for (i = gap; i < n; i++) {
                j = i - gap;
                a = &buf[j];
                while (j >= 0) {
                    b = &buf[j + gap];
                    if ((s32)a->snatchIndex > (s32)b->snatchIndex) {
                        memcpy(&tmp, a, 8);
                        memcpy(a, b, 8);
                        memcpy(b, &tmp, 8);
                        a -= gap;
                        j -= gap;
                    } else {
                        break;
                    }
                }
            }
        }
        return;
    }
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            j = i - gap;
            a = &buf[j];
            while (j >= 0) {
                b = &buf[j + gap];
                if ((s32)a->snatchIndex < (s32)b->snatchIndex) {
                    memcpy(&tmp, a, 8);
                    memcpy(a, b, 8);
                    memcpy(b, &tmp, 8);
                    a -= gap;
                    j -= gap;
                } else {
                    break;
                }
            }
        }
    }
}
