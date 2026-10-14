#include <game/menuPcBoxPokemonLayout.hpp>

extern "C" {
void *GSmemAllocClr(u32);
u8 *savedataGetStatus(s32, s32);
void GSmemFree(void *);
void pokemonInit(Pokemon *);
void *memcpy(void *, const void *, u32);
}

class PCBOX {
public:
    static PCBOX *getPointer();
    s8 getPokemonBoxNbUsedSlot(s8);
    s8 getPokemonBoxNbEmptySlot(s8);
    void setPokemon(Pokemon *, s8, s8);
    void addPokemon(Pokemon *, s8);
    void delPokemon(s8, s8);
    Pokemon *getPokemon(s8, s8);
};

class Hero {
public:
    static Hero *getHeroPtr();
    void setPokemon(const Pokemon *, long);
    long addPokemon(const Pokemon *);
    Pokemon *getPokemon(long);
};

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_TYPE_0
};

class CMenuPokemonLeave;

namespace {

class CMenuPokemonLeave : public CMetaMenu {
public:
    s32 animState;
    u8 pad33C[0x3E0 - 0x33C];
    s32 currentBox;
    u8 pad3E4[0x35F4 - 0x3E4];
    CInfoWindow infoWindow;
    u8 pad3628[0x3718 - 0x3628];
    Pokemon statusPokemon;
    u8 displayFlag;
    u8 pad37DD[0x37F0 - 0x37DD];
    CMenuPokemonCursor *cursor;

    virtual void drawMain();
    virtual bool isAnimationStateNone();

    bool pokemonPcBoxMarkGetIndex(Pokemon *, int);
    u8 currentPokemonPcBoxMarkGet();
    void currentPokemonPcBoxMarkSet(u8);
    CAnt *currentAntGetPointer();
    CAnt *cursorUnderPokemonGetAntPointer();
    void resetStatusAndModelDisplayPokemon();
    void setStatusAndModelDisplayPokemon(Pokemon *);
    void cursorUnderPokemonDel();
    void temochiPokemonDelShift(int);
    void waitAnimationStateEnd();
    void infoMessageDisplay(u32);
    void pokemonStatusMenuCallback(Pokemon *, MENU_POKEMON_CB_TYPE);
    void markingMenuItemCallBack(tagWINDOW_WORK *, tagSPRITE_WORK *);
    void depositMenuDraw(long);
    bool cursorMoveWhenInPcBoxR(long &);
    bool cursorMoveWhenInPcBoxL(long &);
    void currentPokemonDel(bool);
    void cursorUnderPokemonSet(Pokemon *, bool);
    int temochiPokemonLiveQuantity(bool);
    Pokemon *currentPokemonGetPointer();
    Pokemon *cursorUnderPokemonGetPointer();
    Pokemon *pcBoxPokemonGetPointer(int, int);
    Pokemon *pcBoxPokemonGetPointer(int);
    Pokemon *temochiPokemonGetPointer(int);
    int pcBoxUsedQuantity(int);
    int pcBoxEmptyQuantity(int);
    void pcBoxPokemonSet(Pokemon *, int);
    void pcBoxPokemonAdd(Pokemon *, int);
    void pcBoxPokemonDel(int);
    int temochiPokemonQuantity();
    int searchTemochiPokemonBlankSlot();
    bool temochiPokemonIsFull();
    bool temochiPokemonAddAble();
    void temochiPokemonDel(int);
    void temochiPokemonSet(Pokemon *, int);
    bool temochiPokemonAdd(Pokemon *);
    int temochiPokemonGetFreePosition();
};

CMenuPokemonLeave *pMenuPokemonLeave;

bool CMenuPokemonLeave::isAnimationStateNone() {
    return animState == 0;
}

int CMenuPokemonLeave::pcBoxUsedQuantity(int box) {
    return PCBOX::getPointer()->getPokemonBoxNbUsedSlot(box);
}

int CMenuPokemonLeave::pcBoxEmptyQuantity(int box) {
    return PCBOX::getPointer()->getPokemonBoxNbEmptySlot(box);
}

void CMenuPokemonLeave::pcBoxPokemonSet(Pokemon *p, int slot) {
    PCBOX::getPointer()->setPokemon(p, currentBox, slot);
}

void CMenuPokemonLeave::pcBoxPokemonAdd(Pokemon *p, int box) {
    if (box == -1) {
        box = currentBox;
    }
    PCBOX::getPointer()->addPokemon(p, box);
}

void CMenuPokemonLeave::pcBoxPokemonDel(int slot) {
    PCBOX::getPointer()->delPokemon(currentBox, slot);
}

Pokemon *CMenuPokemonLeave::pcBoxPokemonGetPointer(int box, int slot) {
    Pokemon *p = PCBOX::getPointer()->getPokemon(box, slot);
    if (p->checkValid()) {
        return p;
    }
    return 0;
}

Pokemon *CMenuPokemonLeave::pcBoxPokemonGetPointer(int slot) {
    return pcBoxPokemonGetPointer(currentBox, slot);
}

Pokemon *CMenuPokemonLeave::temochiPokemonGetPointer(int slot) {
    Pokemon *p = Hero::getHeroPtr()->getPokemon(slot);
    if (p->checkValid()) {
        return p;
    }
    return 0;
}

int CMenuPokemonLeave::temochiPokemonQuantity() {
    int n = 0;
    do {
        if (temochiPokemonGetPointer(n) == 0) {
            break;
        }
        n++;
    } while (n < 6);
    return n;
}

int CMenuPokemonLeave::searchTemochiPokemonBlankSlot() {
    int n = temochiPokemonQuantity();
    if (n == 6) {
        return -1;
    }
    return n;
}

bool CMenuPokemonLeave::temochiPokemonIsFull() {
    return temochiPokemonQuantity() >= 6;
}

bool CMenuPokemonLeave::temochiPokemonAddAble() {
    return temochiPokemonQuantity() < 6;
}

void CMenuPokemonLeave::temochiPokemonDel(int slot) {
    pokemonInit(temochiPokemonGetPointer(slot));
}

void CMenuPokemonLeave::temochiPokemonSet(Pokemon *p, int slot) {
    Hero::getHeroPtr()->setPokemon(p, slot);
}

bool CMenuPokemonLeave::temochiPokemonAdd(Pokemon *p) {
    return Hero::getHeroPtr()->addPokemon(p) != -1;
}

int CMenuPokemonLeave::temochiPokemonGetFreePosition() {
    int n = 0;
    do {
        if (temochiPokemonGetPointer(n) == 0) {
            break;
        }
        n++;
    } while (n < 6);
    if (n == 6) {
        return -1;
    }
    return n;
}

bool CMenuPokemonLeave::pokemonPcBoxMarkGetIndex(Pokemon *p, int idx) {
    if (p != 0) {
        u8 mark = p->getPcboxMark();
        return ((u8)(1 << idx) & mark) != 0;
    }
    return false;
}

u8 CMenuPokemonLeave::currentPokemonPcBoxMarkGet() {
    Pokemon *p = currentPokemonGetPointer();
    if (p != 0) {
        return p->getPcboxMark();
    }
    return 0;
}

void CMenuPokemonLeave::currentPokemonPcBoxMarkSet(u8 mark) {
    Pokemon *p = currentPokemonGetPointer();
    if (p != 0) {
        p->setPcboxMark(mark);
    }
}

CAnt *CMenuPokemonLeave::currentAntGetPointer() {
    if (cursor->isCatchPokemon()) {
        return &cursor->ant;
    }
    return cursorUnderPokemonGetAntPointer();
}

void CMenuPokemonLeave::resetStatusAndModelDisplayPokemon() {
    pokemonInit(&statusPokemon);
    displayFlag = 0;
}

void CMenuPokemonLeave::setStatusAndModelDisplayPokemon(Pokemon *p) {
    displayFlag = 1;
    if (p == 0) {
        pokemonInit(&statusPokemon);
    } else {
        memcpy(&statusPokemon, p, 0xC4);
    }
}

Pokemon *CMenuPokemonLeave::currentPokemonGetPointer() {
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        if (c->pokemon.checkValid()) {
            return &c->pokemon;
        }
        return 0;
    }
    return cursorUnderPokemonGetPointer();
}

void CMenuPokemonLeave::cursorUnderPokemonDel() {
    s32 idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        temochiPokemonDelShift(idx - 4);
    } else if (idx >= 10) {
        pcBoxPokemonDel(idx - 10);
    }
}

Pokemon *CMenuPokemonLeave::cursorUnderPokemonGetPointer() {
    s32 idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        return temochiPokemonGetPointer(idx - 4);
    }
    if (idx >= 10) {
        return pcBoxPokemonGetPointer(idx - 10);
    }
    return 0;
}

void CMenuPokemonLeave::currentPokemonDel(bool darkOut) {
    if (currentPokemonGetPointer() != 0) {
        if (darkOut) {
            DarkPokemon *dp = currentPokemonGetPointer()->getDarkPokemon();
            if (dp != 0) {
                dp->setPlace(DARK_POKEMON_WHERE_6, 0);
            }
        }
        if (cursor->isCatchPokemon()) {
            cursor->deletePokemon();
        } else {
            cursorUnderPokemonDel();
        }
    }
}

void CMenuPokemonLeave::cursorUnderPokemonSet(Pokemon *p, bool replace) {
    s32 idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        if (replace) {
            s32 slot = idx - 4;
            temochiPokemonDel(slot);
            temochiPokemonSet(p, slot);
        } else {
            temochiPokemonAdd(p);
        }
    } else if (idx >= 10) {
        s32 slot = idx - 10;
        pcBoxPokemonDel(slot);
        pcBoxPokemonSet(p, slot);
    }
}

int CMenuPokemonLeave::temochiPokemonLiveQuantity(bool skipCursor) {
    int skip = -1;
    int n;
    int i;
    if (skipCursor) {
        s32 idx = cursor->index;
        if (idx >= 4 && idx <= 9) {
            skip = idx - 4;
        }
    }
    n = 0;
    i = 0;
    do {
        if (i != skip) {
            Pokemon *p = temochiPokemonGetPointer(i);
            if (p == 0) {
                break;
            }
            if (p->getHp() != 0) {
                n++;
            }
        }
        i++;
    } while (i < 6);
    return n;
}

void CMenuPokemonLeave::temochiPokemonDelShift(int slot) {
    while (slot < 5) {
        Pokemon *cur = temochiPokemonGetPointer(slot);
        Pokemon *next = temochiPokemonGetPointer(slot + 1);
        if (cur != 0) {
            if (next == 0) {
                temochiPokemonDel(slot);
                break;
            }
            memcpy(cur, next, 0xC4);
        }
        slot++;
    }
}

void CMenuPokemonLeave::waitAnimationStateEnd() {
    for (;;) {
        updateAll();
        if (animState == 0 || animState == 1) {
            break;
        }
    }
}

void CMenuPokemonLeave::infoMessageDisplay(u32 msg) {
    infoWindow.exec(*this, msg, true);
}

bool CMenuPokemonLeave::cursorMoveWhenInPcBoxR(long &pos) {
    if (pos >= 10) {
        if ((pos - 10) % 6 < 5) {
            pos = pos + 1;
        } else {
            pos = pos - 5;
        }
        return true;
    }
    return false;
}

bool CMenuPokemonLeave::cursorMoveWhenInPcBoxL(long &pos) {
    if (pos >= 10) {
        if ((pos - 10) % 6 > 0) {
            pos = pos - 1;
        } else {
            pos = pos + 5;
        }
        return true;
    }
    return false;
}

void _cbMenuPokemonStatus(Pokemon *p, MENU_POKEMON_CB_TYPE type, long) {
    pMenuPokemonLeave->pokemonStatusMenuCallback(p, type);
}

void _depositMenuDrawHook(CMetaMenu *menu, long a) {
    ((CMenuPokemonLeave *)menu)->depositMenuDraw(a);
}

}  // namespace

extern "C" s32 menuPcBoxMarkingItemCallback(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    pMenuPokemonLeave->markingMenuItemCallBack(win, sprite);
    return 0;
}

extern "C" s32 menuPcBoxMarkingCtrl(tagWINDOW_WORK *win) {
    switch (win->phase) {
    case 0:
        if (win->step == 0) {
            win->step = 1;
        }
        break;
    case 3:
        if (win->step == 0) {
            win->step = 1;
        }
        break;
    }
    return 0;
}

void menuPcBoxSetLastViewBox(long box) {
    *(s32 *)(savedataGetStatus(0, 3) + 0xBC0C) = box;
}

long menuPcBoxGetLastViewBox(void) {
    return *(s32 *)(savedataGetStatus(0, 3) + 0xBC0C);
}
