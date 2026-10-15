#include <dolphin/types.h>

struct CURSOR {
    s16 first, selected;
};

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 phase, step;
    u8 reserved3;
    s32 menu;
    u8 reserved8[0x14];
    s32 layer;
    u8 reserved20[0x73];
    u8 alpha;
    u8 reserved94[0x10];
    u8 accepted, cancelled;
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 id;
    u8 reserved8[0x5c];
    u8 col[3];
};

struct MEMO_CONTENTS {
    CURSOR *cursor;
    s32 reserved4;
};

struct tagKEY {
    u32 reserved0;
    u16 triggers;
};

extern "C" {
void *__nw__FUl(u32);
void __dl__FPv(void *);
void menuClose(long);
void menuCloseSync(long, bool);
u8 winSeqCheckMove(long);
void winSeqSetMenu(long, long);
void menuPdaSetSubres(long, long);
tagKEY *windowGetKeyInfo(void);
void menuPdaGetRes(void);
void menuPdaGetSubres(void);
void *menuPdaMemoListGetMenuModelWork(void);
void menuModelSetZoom(void *, f32);
void menuPdaMemoListLoadPokemon(long);
u8 menuPdaMemoListIsLoadHero(void);
void menuPdaMemoListSetHeroMotion(void);
void windowDrawSprite(long, long, tagWINDOW_WORK *, long, long, long);
long zokuseiGetPokemonSpriteID(long, u16);
long menuPdaMemoListGetPokemonID(long, CURSOR *);
long pokemonDataBiosGetPtr(long);
void menuPdaMemoWave(long);
void menuPdaMemoWaveInit(void);
void menuPdaMemoListLoadHero(long);
void *menuModelGetModelPtr(void *);
void GSmodelDestroyLinkedParticles(void *);
long menuOpenCustom(long, long, ...);
long windowGetActiveID(void);
void winSpriteSetDisp(tagSPRITE_WORK *, long);
void menuPdaMemoListDispPokemonModel(tagWINDOW_WORK *, tagSPRITE_WORK *, long);
u16 memoDataGetCount(long);
const u16 *menuPdaMemoListGetPokemonName(long, CURSOR *);
const u16 *GSmsgGetGSchar(u32);
void msgctrlSetValue(long, const void *);
void GSmsgPrint2(long, long, long, u32, u32);
long menuPdaMemoListGetPokemonDataPointer(long, CURSOR *);
const void *pokemonDataBiosGetTypeName(long);
}

class menuPdaMemoXD : public MEMO_CONTENTS {
public:
    s32 item;
    s32 itemPrev;
    s32 state;
    f32 f14, f18, f1c, f20;
    u8 reserved24[0xe8 - 0x24];

    void PokemonHeight(tagWINDOW_WORK *, tagSPRITE_WORK *, MEMO_CONTENTS *);
    void PokemonWeight(tagWINDOW_WORK *, tagSPRITE_WORK *, MEMO_CONTENTS *);
    void PokemonSyuzoku(tagWINDOW_WORK *, tagSPRITE_WORK *, MEMO_CONTENTS *);
    void PokemonName(tagWINDOW_WORK *, tagSPRITE_WORK *, MEMO_CONTENTS *);
    void Button(tagWINDOW_WORK *);
    void Ctrl(tagWINDOW_WORK *);
    void Cursor(tagWINDOW_WORK *);
    void SetModelAngle(s16);
    void Release();
    void LoadPokemon(CURSOR *);
    void Init(CURSOR *);
    void _menuClose(long, bool);
    bool TaskCloseCheck();
    u16 GetAisyouIndex(u16);
    void SetJoutaiSprite(tagWINDOW_WORK *, u16);
    void PokemonType(tagWINDOW_WORK *, tagSPRITE_WORK *, MEMO_CONTENTS *, u16);
    CURSOR *Main(CURSOR *);
    s32 TaskOpen();
    void TaskClose(tagWINDOW_WORK *, bool);
};

void *operator new(unsigned long);
void operator delete(void *);

extern "C" s32 menuPdaMemoXDGetItem(void);
extern "C" void menuPdaMemoXDHeight(tagWINDOW_WORK *, tagSPRITE_WORK *);
extern "C" void menuPdaMemoXDWeight(tagWINDOW_WORK *, tagSPRITE_WORK *);
menuPdaMemoXD *pMemo;
static CURSOR _cursor;

extern "C" s32 menuPdaMemoXDGetItem(void) {
    if (pMemo == 0) {
        return 0;
    }
    return pMemo->item;
}

extern "C" void menuPdaMemoXDHeight(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    if (pMemo) {
        spr->col[0] = 0xD5;
        spr->col[1] = 0xAA;
        spr->col[2] = 0x33;
        pMemo->PokemonHeight(win, spr, pMemo);
    }
}

extern "C" void menuPdaMemoXDWeight(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    if (pMemo) {
        spr->col[0] = 0xD5;
        spr->col[1] = 0xAA;
        spr->col[2] = 0x33;
        pMemo->PokemonWeight(win, spr, pMemo);
    }
}

void menuPdaMemoXD::PokemonSyuzoku(tagWINDOW_WORK *win, tagSPRITE_WORK *spr, MEMO_CONTENTS *c) {
    CURSOR *cur = c->cursor;
    msgctrlSetValue(0x31, pokemonDataBiosGetTypeName(menuPdaMemoListGetPokemonDataPointer(cur->selected + cur->first, cur)));
    GSmsgPrint2(win->layer, 0, 0, win->alpha | 0xFFFFFF00, 0x3B9B);
}

void menuPdaMemoXD::PokemonName(tagWINDOW_WORK *win, tagSPRITE_WORK *spr, MEMO_CONTENTS *c) {
    CURSOR *cur = c->cursor;
    const u16 *name = menuPdaMemoListGetPokemonName(cur->selected + cur->first, cur);
    if (name == 0) {
        name = GSmsgGetGSchar(1);
    }
    msgctrlSetValue(0x37, name);
    GSmsgPrint2(win->layer, 0, 0, win->alpha | 0xFFFFFF00, 0x4275);
}

void menuPdaMemoXD::Release() {
}

void menuPdaMemoXD::LoadPokemon(CURSOR *c) {
    menuPdaMemoListLoadPokemon(c->selected + c->first);
}

void menuPdaMemoXD::_menuClose(long id, bool sync) {
    menuClose(id);
    menuCloseSync(id, sync);
}

extern "C" void menuPdaMemoXDButton(tagWINDOW_WORK *win) {
    if (pMemo) {
        pMemo->Button(win);
    }
}

extern "C" s32 menuPdaMemoXDCursor(tagWINDOW_WORK *win) {
    if (pMemo == 0) {
        return 0;
    }
    pMemo->Cursor(win);
    return 0;
}

extern "C" s32 menuPdaMemoXDCtrl(tagWINDOW_WORK *win) {
    if (pMemo == 0) {
        return 0;
    }
    pMemo->Ctrl(win);
    return 0;
}

void menuPdaMemoXD::Init(CURSOR *) {
    itemPrev = item;
    item = 0;
    itemPrev = 0;
    state = 0x7C;
    cursor = &_cursor;
    f1c = 0.0f;
    f18 = 0.0f;
    f14 = 0.0f;
    f20 = 0.75f;
    SetModelAngle(0);
    menuModelSetZoom(menuPdaMemoListGetMenuModelWork(), f20);
}

extern "C" CURSOR *menuPdaMemoXDMain(CURSOR *c) {
    menuPdaMemoXD *p = new menuPdaMemoXD;
    if (p) {
        p->Init(c);
    }
    pMemo = p;
    p->Main(c);
    p = pMemo;
    if (p) {
        p->Release();
        delete p;
    }
    pMemo = 0;
    return &_cursor;
}

u16 menuPdaMemoXD::GetAisyouIndex(u16 x) {
    u16 tbl[18] = {0, 1, 3, 4, 2, 6, 5, 7, 8, 10, 11, 13, 12, 15, 14, 16, 17, 9};
    if ((s32)x > 0x12) {
        return 0;
    }
    return tbl[x];
}

bool menuPdaMemoXD::TaskCloseCheck() {
    s32 id = 0;
    switch (item) {
    case 0:
        id = 0x7C;
        break;
    case 1:
        id = 0x7D;
        break;
    case 2:
        id = 0x7D;
        break;
    case 3:
        id = 0x7E;
        break;
    }
    u16 m = id;
    if (m == 0) {
        return true;
    }
    return winSeqCheckMove(m) == 0;
}

void menuPdaMemoXD::SetJoutaiSprite(tagWINDOW_WORK *win, u16 joutai) {
    u16 a[4] = {0x43, 0x42, 0x3F, 0x41};
    u16 b[4] = {0x16A, 0x16B, 0x16C, 0x16D};
    for (u16 i = 0; i < 4; i++) {
        if (joutai == a[i]) {
            windowDrawSprite(0, 0, win, b[i], 0, win->layer);
        }
    }
}

void menuPdaMemoXD::PokemonType(tagWINDOW_WORK *win, tagSPRITE_WORK *spr, MEMO_CONTENTS *c, u16 idx) {
    CURSOR *cur = c->cursor;
    long data = pokemonDataBiosGetPtr(menuPdaMemoListGetPokemonID(cur->selected + cur->first, cur));
    if (idx == 0) {
        windowDrawSprite(0, 0, win, zokuseiGetPokemonSpriteID(data, idx), 0, win->layer);
        return;
    }
    long first = zokuseiGetPokemonSpriteID(data, 0);
    long second = zokuseiGetPokemonSpriteID(data, idx);
    if ((u16)second != 0 && (u16)first != (u16)second) {
        windowDrawSprite(0, 0, win, second, 0, win->layer);
    }
}

void menuPdaMemoXD::Button(tagWINDOW_WORK *win) {
    if (win) {
        u16 trig = windowGetKeyInfo()->triggers;
        menuPdaGetRes();
        menuPdaGetSubres();
        if (winSeqCheckMove(win->menu) == 0) {
            if (trig & 0x10) {
                s32 i = item;
                if (i == 1) {
                    itemPrev = i;
                    item = i;
                    win->accepted = 1;
                }
            }
            if (trig & 0x20) {
                win->accepted = 1;
                win->cancelled = 1;
            }
        }
    }
}

void menuPdaMemoXD::Ctrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x132);
            win->step = 1;
            menuPdaSetSubres(-1, 2);
        }
        break;
    case 2:
        if (item == 2 && menuPdaMemoListIsLoadHero() == 0) {
            menuPdaMemoListSetHeroMotion();
        }
        break;
    case 3:
        if (win->step == 0) {
            winSeqSetMenu(win->menu, 0x136);
            win->step = 1;
        }
        break;
    }
}

CURSOR *menuPdaMemoXD::Main(CURSOR *c) {
    _cursor.selected = c->selected;
    _cursor.first = c->first;
    while (1) {
        cursor = &_cursor;
        if (TaskOpen() == -1) {
            break;
        }
        s32 i = item;
        if (i == itemPrev && i == 1) {
            menuPdaMemoWave(_cursor.selected + _cursor.first);
        }
    }
    TaskClose(0, true);
    menuPdaSetSubres(-1, 1);
    menuPdaMemoListLoadHero(0);
    return &_cursor;
}

s32 menuPdaMemoXD::TaskOpen() {
    s32 r = -1;
    switch (item) {
    case 0:
        menuCloseSync(0x7C, true);
        r = menuOpenCustom(0x7C, windowGetActiveID(), 0, 0, 1, 1, this);
        break;
    case 1:
        r = menuOpenCustom(0x7D, windowGetActiveID(), 0, 0, 1, 1, this);
        break;
    case 2:
        r = menuOpenCustom(0x7D, windowGetActiveID(), 0, 0, 1, 1, this);
        break;
    case 3:
        menuCloseSync(0x7E, true);
        r = menuOpenCustom(0x7E, windowGetActiveID(), 0, 0, 1, 1, this);
        break;
    }
    return r;
}

void menuPdaMemoXD::TaskClose(tagWINDOW_WORK *win, bool sync) {
    s32 i = item;
    if (win) {
        win->accepted = 1;
    }
    void *model = menuModelGetModelPtr(menuPdaMemoListGetMenuModelWork());
    if (model) {
        GSmodelDestroyLinkedParticles(model);
    }
    switch (i) {
    case 0:
        if (winSeqCheckMove(0x7C) == 0) {
            _menuClose(0x7C, sync);
        }
        break;
    case 1:
        if (winSeqCheckMove(0x7D) == 0) {
            _menuClose(0x7D, sync);
            menuPdaMemoWaveInit();
        }
        break;
    case 2:
        if (winSeqCheckMove(0x7D) == 0) {
            _menuClose(0x7D, sync);
        }
        break;
    case 3:
        if (winSeqCheckMove(0x7E) == 0) {
            _menuClose(0x7E, sync);
        }
        break;
    }
}

extern "C" void menuPdaMemoBackHook(tagWINDOW_WORK *win, tagSPRITE_WORK *spr) {
    menuPdaGetRes();
    menuPdaGetSubres();
    switch (spr->id) {
    case 0xB5:
    case 0xB6:
    case 0xB7:
    case 0xB8:
        if (menuPdaMemoXDGetItem() == 3) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0xB1:
    case 0xB2:
    case 0xB3:
    case 0xB4:
        if (menuPdaMemoXDGetItem() == 0) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0xAD:
    case 0xAE:
    case 0xAF:
    case 0xB0:
        if (menuPdaMemoXDGetItem() == 1 || menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0xBC:
    case 0xBD:
    case 0xBE:
    case 0xBF:
    case 0xC0:
    case 0xC1:
    case 0xC2:
    case 0xC3:
        if (menuPdaMemoXDGetItem() == 1) {
            winSpriteSetDisp(spr, 1);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0xC4:
        if (menuPdaMemoXDGetItem() == 0) {
            winSpriteSetDisp(spr, 1);
            msgctrlSetValue(0x34, (const void *)memoDataGetCount(0));
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0xBA:
        if (menuPdaMemoXDGetItem() == 1) {
            menuPdaMemoListDispPokemonModel(win, spr, 2);
        }
        break;
    case 0x1C7:
        if (menuPdaMemoXDGetItem() == 2) {
            menuPdaMemoListDispPokemonModel(win, spr, 3);
        }
        break;
    case 0xB9:
        if (menuPdaMemoXDGetItem() == 3) {
            menuPdaMemoListDispPokemonModel(win, spr, 0);
        }
        break;
    case 0xBB:
        if (menuPdaMemoXDGetItem() == 0) {
            menuPdaMemoListDispPokemonModel(win, spr, 1);
        }
        break;
    case 0x16A:
        if (menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(spr, 1);
            menuPdaMemoXDWeight(win, spr);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    case 0x16B:
        if (menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(spr, 1);
            menuPdaMemoXDHeight(win, spr);
        } else {
            winSpriteSetDisp(spr, 0);
        }
        break;
    }
}
