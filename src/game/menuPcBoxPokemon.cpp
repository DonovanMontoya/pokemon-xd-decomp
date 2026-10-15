#include <game/menuPcBoxPokemonLayout.hpp>

enum MENU_POKEMON_CB_TYPE {
    MENU_POKEMON_CB_TYPE_0,
    MENU_POKEMON_CB_TYPE_PREV,
    MENU_POKEMON_CB_TYPE_NEXT
};

extern "C" {
bool pokemonCheckValid(Pokemon*);
void menuOpenCustom(s32, s32, ...);
s32 windowGetActiveID();
s32 windowGetValue(s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
void winSpriteSetDisp(tagSPRITE_WORK *, s32);
void *GSmemAllocClr(u32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s32);
MENU_SPRITE_dd_ *menuSpriteBiosGetPtr(s32);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteSetOffset(s32, s32, s32);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
u8 *savedataGetStatus(s32, s32);
void GSmemFree(void *);
void pokemonInit(Pokemon *);
void *memcpy(void *, const void *, u32);
void *memset(void *, int, u32);
tagWINDOW_WORK *windowSearchID(s32);
void GSmsgPrint2(s32, s32, s32, u32, u32);
u32 GSmsgGetRect(u32);
void msgctrlSetValue(u32, u32);
void menuModelInit(MENU_MODEL *, s16, s16);
void menuModelSetSize(MENU_MODEL *, s16, s16, s16, s16);
void menuModelTerm(MENU_MODEL *);
u8 menuModelCheck(MENU_MODEL *, s32);
u8 menuModelComparePokemon(MENU_MODEL *, Pokemon *);
void menuModelLoadPokemon(MENU_MODEL *, Pokemon *);
void menuModelAdjustCamera(MENU_MODEL *);
void menuModelSetAngle(MENU_MODEL *, f32 *);
void menuModelRender(MENU_MODEL *);
u8 menuSubGetPokemonSexForDisp(Pokemon *);
s32 pokecoloGetCountryCode(void);
void *itemDataBiosGetPtr(u16);
u32 itemDataBiosGetName(void *);
u32 GSmsgGetGSchar(u32);
u32 pokemonDataBiosGetName(void *);
s32 menuDrawReliveMeter3(Pokemon *, long, long, long, long, u8, s32);
u16 zokuseiGetPokemonSpriteID(void *, u16);
void menuDrawReliveUpdate(void);
void menuModelRenderOffAll(MENU_MODEL *);
void GSfsysRead(u32);
void GSfsysReadWait(u32);
s32 GSfsysGetStatus(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void GSthreadSwitch();
u8 GSgfxVideoGetVsyncRate();
void menuNameEntryCall(s32, s32);
s32 menuPokemonStatusOpenFromPcBox(Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), long);
}

extern "C" long actionMenu__9CMetaMenuFPUlill(CMetaMenu *, u32 *, int, long, long, long);

struct GSgfxLayer;
void GSprimSetup2DRender(GSgfxLayer *);
long relivehallGetLastViewStage(void);
void menuPcBoxSetLastViewBox(long);
long menuPcBoxGetLastViewBox(void);

inline void *operator new(unsigned long, void *p) { return p; }

class PCBOX {
public:
    static PCBOX *getPointer();
    s8 getPokemonBoxNbUsedSlot(s8);
    s8 getPokemonBoxNbEmptySlot(s8);
    void setPokemon(Pokemon *, s8, s8);
    void addPokemon(Pokemon *, s8);
    void delPokemon(s8, s8);
    Pokemon *getPokemon(s8, s8);
    char *getPokemonBoxName(s8);
    static s8 lastWatchBoxID;
};

class Hero {
public:
    static Hero *getHeroPtr();
    void setPokemon(const Pokemon *, long);
    long addPokemon(const Pokemon *);
    Pokemon *getPokemon(long);
};


class CMenuPokemonLeave;

u32 pcBoxSoundTbl[5] = {0x441, 0x442, 0x443, 0x14, 0x15};

namespace {

PocketVec<short> _cursorPositionTblDefault[4] = {{0x164, 0x3A}, {0x10F, 0x1AC}, {0x1FE, 0x1AC}, {0x162, 0x1AD}};
s32 _cursorPositionToStateTbl[4] = {5, 3, 0x10, 4};
long localWindowTable[10] = {0x8A, 0x82, 0x80, 0x84, 0x85, 0x87, 0x88, 0x89, 0xE3, 0};

class CMenuPokemonLeave : public CMetaMenu {
public:
    CState anim;
    s32 currentBox;
    s32 prevBox;
    s32 depositBox;
    CAnt pcAnt[8][30];
    s32 temochiX;
    u8 pad34B0[4];
    CAnt temochiAnt[6];
    u8 markMask;
    u8 pad35ED[3];
    f32 scroll;
    CInfoWindow infoWindow;
    MENU_MODEL model;
    u8 modelActive;
    u8 pad3715[3];
    Pokemon statusPokemon;
    u8 displayFlag;
    u8 hideFlag;
    u8 pad37DE[2];
    s32 rowY;
    s32 cursorLeft;
    s32 cursorRight;
    s32 savedIndex;
    CMenuPokemonCursor *cursor;
    s32 slotX;
    s32 slotY;
    PocketVec<short> posTbl[40];

    virtual void drawAll();
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
    Pokemon *pokemonStatusMenuCallback(Pokemon *, MENU_POKEMON_CB_TYPE);
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
    Pokemon *getStatusAndModelDisplayPokemonGetPointer();
    int currentPokemonGetArea();
    PocketVec<short> getPcBoxSlotPosition(int);
    PocketVec<short> getTemochiSlotPosition(int);
    void menuModelTerm();
    void menuModelInit();
    void resetViewAntAll();
    void drawTemochiArea();
    void drawBoxArea(int, f32);
    void drawStatusArea();
    void animationStateUpdate();
    bool animationProcessButtonInterrupt(const tagWINDOW_KEY *);
    void boxScroll(bool);
    void cursorMoveLeft(long &);
    void cursorMoveRight(long &);
    bool cursorMoveDown(long &);
    bool cursorMoveUp(long &);
    void stateBoxNameChangeExecProc();
    void stateStatusProc();
    void stateMarkingProc();
    void stateMainProc();
    void stateActionMenuMainProc();
    void stateDepositToPcBoxProc();
    void boxNameDraw(int, long, u32);
    void directActionExec();
    void actionExecByMsgID(u32);
    void main(CMenuGlobalState &);
    void init(CMenuGlobalState &);
    void loop();
};

CMenuPokemonLeave *pMenuPokemonLeave;

void _depositMenuDrawHook(CMetaMenu *, long);

bool CMenuPokemonLeave::isAnimationStateNone() {
    return anim.state == 0;
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
        return ((u8)(1 << idx) & p->getPcboxMark()) != 0;
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
    Pokemon *cur = currentPokemonGetPointer();
    if (cur != 0) {
        if (darkOut) {
            DarkPokemon *dp = cur->getDarkPokemon();
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
    Pokemon *next;
    Pokemon *cur;
    for (; slot < 5; slot++) {
        cur = temochiPokemonGetPointer(slot);
        next = temochiPokemonGetPointer(slot + 1);
        if (cur != 0) {
            if (next == 0) {
                temochiPokemonDel(slot);
            } else {
                memcpy(cur, next, 0xC4);
            }
        }
    }
    temochiPokemonDel(5);
}

void CMenuPokemonLeave::waitAnimationStateEnd() {
    for (;;) {
        updateAll();
        if (anim.state == 0 || anim.state == 1) {
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

Pokemon *CMenuPokemonLeave::getStatusAndModelDisplayPokemonGetPointer() {
    if (hideFlag != 0) {
        return 0;
    }
    if (displayFlag != 0) {
        if (pokemonCheckValid(&statusPokemon)) {
            return &statusPokemon;
        }
        return 0;
    }
    return currentPokemonGetPointer();
}

int CMenuPokemonLeave::currentPokemonGetArea() {
    if (cursor->isCatchPokemon()) {
        return 1;
    }
    s32 idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        return 2;
    }
    if (idx >= 10) {
        return 3;
    }
    return 0;
}

CAnt *CMenuPokemonLeave::cursorUnderPokemonGetAntPointer() {
    s32 idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        return &temochiAnt[idx - 4];
    }
    if (idx >= 10) {
        return &pcAnt[currentBox][idx - 10];
    }
    return 0;
}

PocketVec<short> CMenuPokemonLeave::getPcBoxSlotPosition(int i) {
    PocketVec<short> v;
    v.x = slotX + (i % 6) * 64 + 0x20;
    v.y = slotY + (i / 6) * 64 + 0x20;
    return v;
}

PocketVec<short> CMenuPokemonLeave::getTemochiSlotPosition(int i) {
    MENU_ITEM_dd_ *item = menuPtItemGetByMenuIdAndItemId(0x84, 0x417, i * 4);
    PocketVec<short> v;
    v.x = item->x + item->width;
    v.y = item->y + item->height;
    return v;
}

void CMenuPokemonLeave::menuModelTerm() {
    if (modelActive != 0) {
        menuModelCheck(&model, 1);
    }
    ::menuModelTerm(&model);
    modelActive = 0;
    memset(&model, 0, 0xEC);
}

void CMenuPokemonLeave::menuModelInit() {
    if (modelActive != 0) {
        menuModelCheck(&model, 1);
    }
    tagSPRITE_WORK *sp = menuPtSpriteWorkGetByItemID(0x80, 0x3D4, 0);
    ::menuModelInit(&model, sp->width, sp->height);
    menuModelSetSize(&model, sp->x, sp->y, sp->width, sp->height);
}

void CMenuPokemonLeave::directActionExec() {
    if (cursor->isCatchPokemon()) {
        if (cursorUnderPokemonGetPointer() != 0) {
            actionExecByMsgID(0x3BCF);
        } else {
            actionExecByMsgID(0x3BCE);
        }
    } else {
        actionExecByMsgID(0x3BC8);
    }
}

void CMenuPokemonLeave::drawTemochiArea() {
    int i;
    if (temochiX != 0x1E0) {
        tagWINDOW_WORK *w = windowSearchID(0x84);
        w->y = temochiX;
        menuPtWindowWorkDraw(0x84);
        GSprimSetup2DRender(0);
        for (i = 0; i < 6; i++) {
            CAnt *ant = &temochiAnt[i];
            if (ant->unk0 != 0) {
                PocketVec<short> v;
                v.x = 0;
                v.y = temochiX;
                ant->drawAndUpdateWithOffset(v);
            }
        }
    }
}

void CMenuPokemonLeave::animationStateUpdate() {
    scroll = 0.0f;
    anim.update();
    switch (anim.state) {
    case 0:
        if (anim.time == 0.0f) {
            if (pad34B0[0] != 0) {
                temochiX = 0;
            } else {
                temochiX = 0x1E0;
            }
            resetViewAntAll();
            cursor->setAnimationOff();
            resetStatusAndModelDisplayPokemon();
            hideFlag = 0;
        }
        break;
    case 2: {
        if (anim.time == 0.0f) {
            cursor->unk4 = 3;
        }
        f32 t = anim.time / 0.1f;
        cursor->unk8 = t < 1.0f ? t : 1.0f;
        if (t >= 1.0f) {
            anim.sub = 0;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 3: {
        if (anim.time == 0.0f) {
            cursor->unk4 = 3;
            cursor->unk8 = 0.0f;
        }
        f32 t = anim.time / 0.25f;
        f32 m = t < 1.0f ? t : 1.0f;
        temochiX = (s32)(480.0f * (1.0f - m));
        if (t >= 1.0f) {
            anim.sub = 2;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 4: {
        if (anim.time == 0.0f) {
            cursor->unk4 = 3;
            cursor->unk8 = 0.0f;
        }
        f32 t = anim.time / 0.25f;
        f32 m = t < 1.0f ? t : 1.0f;
        temochiX = (s32)(480.0f * m);
        if (t >= 1.0f) {
            anim.sub = 2;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 5: {
        u32 total = (u32)(0.5f * GSgfxVideoGetVsyncRate());
        u32 next = anim.frames + 1;
        f32 end = (f32)(next + 1) / (f32)total;
        f32 t = (f32)next / (f32)total;
        if (end >= 1.0f) {
            anim.sub = 0;
            memset(anim.saved, 0, 0x40);
        }
        scroll = t < 1.0f ? t : 1.0f;
        break;
    }
    case 6: {
        if (anim.time == 0.0f) {
            cursor->unk4 = 1;
            cursorUnderPokemonGetAntPointer()->unk14 = true;
        }
        f32 t = anim.time / 0.25f;
        cursor->unk8 = t < 1.0f ? t : 1.0f;
        if (t >= 1.0f) {
            anim.sub = 0;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 7: {
        if (anim.time == 0.0f) {
            cursor->unk4 = 2;
        }
        f32 t = anim.time / 0.5f;
        cursor->unk8 = t < 1.0f ? t : 1.0f;
        if (t >= 1.0f) {
            anim.sub = 1;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 8: {
        f32 t = anim.time / 0.2f;
        s32 idx = cursor->index;
        s32 last = temochiPokemonGetFreePosition() - 1;
        PocketVec<short> from = getTemochiSlotPosition(idx - 4);
        PocketVec<short> to = getTemochiSlotPosition(last);
        PocketVec<short> pos;
        PocketVec<short> pos2;
        CAnt *ant = &temochiAnt[last];
        pos.x = (s16)(from.x + t * (to.x - from.x));
        pos.y = (s16)(from.y + t * (to.y - from.y));
        pos2 = pos;
        ant->x = pos2.x;
        ant->y = pos2.y;
        if (t >= 1.0f) {
            anim.sub = 0;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 9: {
        if (anim.time == 0.0f) {
            resetViewAntAll();
            if (temochiPokemonIsFull()) {
                anim.sub = 0;
                memset(anim.saved, 0, 0x40);
                break;
            }
        }
        f32 t = anim.time / 0.2f;
        int i = cursor->index - 4;
        CAnt *ant = &temochiAnt[i];
        for (; i < 6; i++, ant++) {
            if (ant->unk0 != 0) {
                PocketVec<short> a = getTemochiSlotPosition(i);
                PocketVec<short> b = getTemochiSlotPosition(i + 1);
                PocketVec<short> pos;
                PocketVec<short> pos2;
                pos.x = (s16)(b.x + t * (a.x - b.x));
                pos.y = (s16)(b.y + t * (a.y - b.y));
                pos2 = pos;
                ant->x = pos2.x;
                ant->y = pos2.y;
            }
        }
        if (t >= 1.0f) {
            anim.sub = 0;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    }
}

void CMenuPokemonLeave::drawAll() {
    animationStateUpdate();
    menuPtWindowWorkDraw(0x8A);
    if (anim.state == 5) {
        int prev = prevBox;
        if ((prev + 1) % 8 == currentBox) {
            drawBoxArea(prev, -scroll);
            drawBoxArea(currentBox, 1.0f - scroll);
        } else {
            drawBoxArea(prev, scroll);
            drawBoxArea(currentBox, -1.0f + scroll);
        }
    } else {
        drawBoxArea(currentBox, 0.0f);
    }
    drawStatusArea();
    drawTemochiArea();
    alphaFadeDraw();
    cursor->draw();
    localWindowDrawAll();
    CAnt::systemUpdate(true);
    infoWindow.draw();
    baseInfo.draw();
}

bool CMenuPokemonLeave::animationProcessButtonInterrupt(const tagWINDOW_KEY *key) {
    s32 st = anim.state;
    if (st == 5) {
        if (key->trigger == 0x200 || key->trigger == 0x400) {
            return true;
        }
        s32 idx = cursor->index;
        if ((key->trigger == 4 || key->trigger == 8) && idx == 0) {
            return true;
        }
    }
    if (st != 0) {
        anim.sub = 0;
        memset(anim.saved, 0, 0x40);
        animationStateUpdate();
    }
    return false;
}

void CMenuPokemonLeave::boxScroll(bool back) {
    prevBox = currentBox;
    if (back) {
        currentBox = (currentBox + 7) % 8;
    } else {
        currentBox = (currentBox + 1) % 8;
    }
    s8 box = currentBox;
    PCBOX::getPointer();
    PCBOX::lastWatchBoxID = box;
    anim.sub = 5;
    memset(anim.saved, 0, 0x40);
    baseAnim.sub = 2;
    memset(baseAnim.saved, 0, 0x40);
    menuPtPlaySe(0x444);
}

void CMenuPokemonLeave::cursorMoveLeft(long &pos) {
    if (!cursorMoveWhenInPcBoxL(pos)) {
        long cur = pos;
        if (cur >= 1 && cur <= 2) {
            long n = cur - 1;
            if (n > 0) {
                pos = n;
            }
        } else if (pos == 0) {
            boxScroll(true);
        } else if (cur >= 6 && pos <= 9) {
            pos = cursorLeft;
        } else if (cur >= 4 && pos <= 5) {
            baseAnim.sub = 4;
            memset(baseAnim.saved, 0, 0x40);
        }
    }
}

void CMenuPokemonLeave::cursorMoveRight(long &pos) {
    if (!cursorMoveWhenInPcBoxR(pos)) {
        long cur = pos;
        if (cur >= 1 && cur <= 2) {
            long n = cur - 1;
            if (n < 1) {
                pos = cur + 1;
            }
        } else if (pos == 0) {
            boxScroll(false);
        } else if (cur >= 4 && pos <= 5) {
            pos = cursorRight;
        } else if (cur >= 6 && pos <= 9) {
            baseAnim.sub = 4;
            memset(baseAnim.saved, 0, 0x40);
        }
    }
}

Pokemon *_cbMenuPokemonStatus(Pokemon *p, MENU_POKEMON_CB_TYPE type, long) {
    return pMenuPokemonLeave->pokemonStatusMenuCallback(p, type);
}

void CMenuPokemonLeave::boxNameDraw(int box, long win, u32 item) {
    tagSPRITE_WORK *sp;
    tagWINDOW_WORK *w = windowSearchID(win);
    sp = menuPtSpriteWorkGetByItemID(w, item, 0);
    char *name = PCBOX::getPointer()->getPokemonBoxName(box);
    msgctrlSetValue(0x37, (u32)name);
    s16 width = GSmsgGetRect(0x4276) >> 16;
    s16 off = sp->width / 2 - width / 2;
    GSmsgPrint2(w->layer, w->x + (sp->x + off), w->y + sp->y, -1, 0x4276);
}

void CMenuPokemonLeave::resetViewAntAll() {
    int prev;
    int next;
    int i;
    int b;
    CAnt::systemUsecountReset();
    for (i = 0; i < 6; i++) {
        CAnt *ant = &temochiAnt[i];
        ant->init();
        Pokemon *p = temochiPokemonGetPointer(i);
        if (p != 0) {
            ant->initByPokemonAndSetColorAnimationInAny(p);
            PocketVec<short> pos = getTemochiSlotPosition(i);
            ant->x = pos.x;
            ant->y = pos.y;
            ant->setAnimation(0);
        }
    }
    prev = (currentBox + 7) % 8;
    next = (currentBox + 1) % 8;
    for (b = 0; b < 8; b++) {
        bool inRange;
        bool show = true;
        int s;
        inRange = false;
        if (prev == b || currentBox == b) {
            inRange = true;
        }
        if (!inRange && next != b) {
            show = false;
        }
        s8 box = b;
        for (s = 0; s < 30; s++) {
            CAnt *ant = &pcAnt[b][s];
            ant->init();
            if (show) {
                Pokemon *p = pcBoxPokemonGetPointer(box, (s8)s);
                if (p != 0) {
                    ant->initByPokemonAndSetColorAnimationInAny(p);
                    PocketVec<short> pos = getPcBoxSlotPosition(s);
                    ant->x = pos.x;
                    ant->y = pos.y;
                    ant->setAnimation(0);
                }
            }
        }
    }
    cursor->ant.use();
    cursor->beforeAnt.use();
    CAnt::systemUnUseResourceRelease();
}

bool CMenuPokemonLeave::cursorMoveDown(long &pos) {
    long cur = pos;
    if (cur >= 1 && cur <= 2) {
        pos = 0;
    } else if (pos >= 0x22) {
        if ((cur - 10) % 6 <= 2) {
            pos = 1;
        } else {
            pos = 2;
        }
    } else if (pos >= 10) {
        pos += 6;
    } else if (pos == 0) {
        pos = rowY + 10;
    } else if (cur >= 3 && pos <= 9) {
        pos = (pos >= 9) ? 3 : cur + 1;
    } else {
        return false;
    }
    return true;
}

bool CMenuPokemonLeave::cursorMoveUp(long &pos) {
    long cur = pos;
    if (cur == 0) {
        pos = 1;
    } else if (cur >= 10 && cur <= 15) {
        pos = 0;
    } else if (cur >= 10) {
        pos -= 6;
    } else if (cur >= 1 && cur <= 2) {
        pos = rowY + 0x22;
    } else if (cur >= 3 && cur <= 9) {
        pos = (cur <= 3) ? 9 : cur - 1;
    } else {
        return false;
    }
    return true;
}

void CMenuPokemonLeave::stateMainProc() {
    u8 *work = baseAnim.saved;
    u8 *animWork = anim.saved;
    u16 trig;
    u16 repeat;
    bool act;
    long pos;
    do {
        MetaKeyInfo *ki = getKeyInfo();
        repeat = ki->repeat;
        trig = ki->trigger;
        act = (trig | repeat) != 0;
        if (act && animationProcessButtonInterrupt((const tagWINDOW_KEY *)ki)) {
            act = false;
        }
        if (act) {
            pos = cursor->index;
            switch (repeat) {
            case 1:
                cursorMoveUp(pos);
                break;
            case 2:
                cursorMoveDown(pos);
                break;
            case 8:
                cursorMoveRight(pos);
                break;
            case 4:
                cursorMoveLeft(pos);
                break;
            case 5:
                if (cursorMoveUp(pos)) {
                    cursorMoveWhenInPcBoxL(pos);
                }
                break;
            case 9:
                if (cursorMoveUp(pos)) {
                    cursorMoveWhenInPcBoxR(pos);
                }
                break;
            case 6:
                if (cursorMoveDown(pos)) {
                    cursorMoveWhenInPcBoxL(pos);
                }
                break;
            case 0xA:
                if (cursorMoveDown(pos)) {
                    cursorMoveWhenInPcBoxR(pos);
                }
                break;
            case 0x200:
            case 0x400:
                if (pad34B0[0] == 0) {
                    boxScroll(repeat == 0x200);
                }
                break;
            }
            switch (trig) {
            case 0x10:
                if ((u32)pos < 4U) {
                    if (!cursor->isCatchPokemon() || globalState->mode == 2) {
                        menuPtPlaySe(0x442);
                    }
                    baseAnim.sub = _cursorPositionToStateTbl[pos];
                    memset(work, 0, 0x40);
                } else if (currentPokemonGetPointer() != 0) {
                    if (cursor->unk14C == 0) {
                        menuPtPlaySe(0x442);
                    }
                    baseAnim.sub = 7;
                    memset(work, 0, 0x40);
                }
                break;
            case 0x20:
                if (pad34B0[0] != 0) {
                    menuPtPlaySe(0x443);
                    baseAnim.sub = 4;
                    memset(work, 0, 0x40);
                } else {
                    if (!cursor->isCatchPokemon() || globalState->mode == 2) {
                        menuPtPlaySe(0x443);
                    }
                    baseAnim.sub = 0x10;
                    memset(work, 0, 0x40);
                }
                break;
            case 0x40:
            case 0x80:
                cursor->unk14C = !cursor->unk14C;
                break;
            case 0x100:
                if (pad34B0[0] == 0) {
                    menuPtPlaySe(0x442);
                    baseAnim.sub = 3;
                    memset(work, 0, 0x40);
                }
                break;
            }
            if (pos != cursor->index) {
                menuPtPlaySe(0x441);
                if (pos >= 10) {
                    rowY = (pos - 10) % 6;
                } else if (pos >= 4 && pos <= 5) {
                    cursorLeft = pos;
                } else if (pos >= 6 && pos <= 9) {
                    cursorRight = pos;
                }
                cursor->setPositionIndex(pos);
                anim.sub = 2;
                memset(animWork, 0, 0x40);
            }
        }
        updateAll();
    } while (baseAnim.sub == -1);
}

void CMenuPokemonLeave::actionExecByMsgID(u32 msg) {
    switch (msg) {
    case 0x3BCF: {
        CMenuPokemonCursor *c;
        Pokemon *p;
        menuPtPlaySe(0x446);
        c = cursor;
        p = c->pokemon.checkValid() ? &c->pokemon : 0;
        if (p->getHp() == 0 && currentPokemonGetArea() == 1 && temochiPokemonLiveQuantity(true) <= 0) {
            baseAnim.sub = 8;
            memset(baseAnim.saved, 0, 0x40);
            *(u32 *)baseAnim.saved = 0x3BE3;
            break;
        }
        c = cursor;
        setStatusAndModelDisplayPokemon(c->pokemon.checkValid() ? &c->pokemon : 0);
        c = cursor;
        Pokemon tmp = *(c->pokemon.checkValid() ? &c->pokemon : 0);
        cursor->setPokemon(cursorUnderPokemonGetPointer());
        cursorUnderPokemonSet(&tmp, true);
        anim.sub = 6;
        memset(anim.saved, 0, 0x40);
        resetViewAntAll();
        break;
    }
    case 0x3BCE: {
        CMenuPokemonCursor *c;
        s32 idx;
        menuPtPlaySe(0x446);
        c = cursor;
        cursorUnderPokemonSet(c->pokemon.checkValid() ? &c->pokemon : 0, false);
        cursor->deletePokemon();
        resetViewAntAll();
        idx = cursor->index;
        if (idx >= 4 && idx <= 9) {
            if (idx - 4 >= temochiPokemonGetFreePosition()) {
                anim.sub = 8;
                memset(anim.saved, 0, 0x40);
            }
        }
        break;
    }
    case 0x3BC8: {
        s32 area = currentPokemonGetArea();
        if (area == 2 && temochiPokemonLiveQuantity(true) <= 0) {
            baseAnim.sub = 8;
            memset(baseAnim.saved, 0, 0x40);
            *(u32 *)baseAnim.saved = 0x3BE3;
            break;
        }
        menuPtPlaySe(0x445);
        Pokemon *under = cursorUnderPokemonGetPointer();
        cursor->setPokemon(under);
        cursorUnderPokemonDel();
        resetViewAntAll();
        if (area == 2) {
            anim.sub = 9;
            memset(anim.saved, 0, 0x40);
        }
        break;
    }
    case 0x3BC9:
        baseAnim.sub = 0xE;
        memset(baseAnim.saved, 0, 0x40);
        break;
    case 0x3BCA:
        baseAnim.sub = 0xD;
        memset(baseAnim.saved, 0, 0x40);
        break;
    case 0x3BCD:
        if (currentPokemonGetArea() == 2 && temochiPokemonLiveQuantity(true) <= 0) {
            baseAnim.sub = 8;
            memset(baseAnim.saved, 0, 0x40);
            *(u32 *)baseAnim.saved = 0x3BE3;
            break;
        }
        baseAnim.sub = 9;
        memset(baseAnim.saved, 0, 0x40);
        break;
    case 0x3BCB:
        baseAnim.sub = 0xA;
        memset(baseAnim.saved, 0, 0x40);
        break;
    case 0x3BE8:
        baseAnim.sub = 0xB;
        memset(baseAnim.saved, 0, 0x40);
        break;
    case 0x3BCC:
        baseAnim.sub = 2;
        memset(baseAnim.saved, 0, 0x40);
        break;
    }
    if (baseAnim.sub == -1) {
        baseAnim.sub = 2;
        memset(baseAnim.saved, 0, 0x40);
    }
}

void CMenuPokemonLeave::stateActionMenuMainProc() {
    u32 items[6];
    s32 idx;
    long result;
    if (cursor->isCatchPokemon()) {
        if (cursorUnderPokemonGetPointer() != 0) {
            items[0] = 0x3BCF;
        } else {
            items[0] = 0x3BCE;
        }
    } else {
        items[0] = 0x3BC8;
    }
    items[1] = 0x3BC9;
    idx = cursor->index;
    if (idx >= 4 && idx <= 9) {
        items[2] = 0x3BCD;
    } else {
        items[2] = 0x3BCA;
    }
    items[3] = 0x3BCB;
    items[4] = 0x3BE8;
    items[5] = 0x3BCC;
    infoWindow.open(0x3BC7, false);
    infoWindow.setMsgCtrlValue(0x32, (u32)currentPokemonGetPointer()->getNicknamePtr());
    result = actionMenu__9CMetaMenuFPUlill(this, items, 6, 0x1C6, 0x8A, 0);
    actionExecByMsgID(items[result]);
    infoWindow.close();
}

void CMenuPokemonLeave::stateBoxNameChangeExecProc() {
    systemFadeOutSetAndWait(-1.0f);
    localWindowDeleteAll();
    menuModelRenderOffAll(&model);
    GSfsysRead(0x670);
    while (GSfsysGetStatus(0x670) == 1) {
        GSthreadSwitch();
    }
    menuNameEntryCall(3, currentBox);
    GSfsysFree(0x670);
    GSresFreeGroup(0x670);
    localWindowCreateAll();
    systemFadeInKick();
}

void CMenuPokemonLeave::stateStatusProc() {
    systemFadeOutSetAndWait(-1.0f);
    menuModelTerm();
    localWindowDeleteAll();
    GSfsysReadWait(0x66F);
    savedIndex = cursor->index;
    menuPokemonStatusOpenFromPcBox(currentPokemonGetPointer(), _cbMenuPokemonStatus, 0);
    cursor->setPositionIndex(savedIndex);
    GSfsysFree(0x66F);
    GSresFreeGroup(0x66F);
    localWindowCreateAll();
    menuModelInit();
    systemFadeInKick();
}

void CMenuPokemonLeave::stateMarkingProc() {
    s32 sel;
    markMask = currentPokemonPcBoxMarkGet();
    sel = 0;
    infoWindow.open(0x3BDB, false);
    localWindowEntry(0x86, 0, 0);
    menuOpenCustom(0x86, windowGetActiveID(), &sel, 0, 1, 0);
    tagWINDOW_WORK *w = windowSearchID(0x86);
    bool done = false;
    while (!done) {
        if (w->cancelled != 0) {
            done = true;
        } else if (w->finished != 0) {
            sel = windowGetValue(0x86);
            if (sel <= 3) {
                markMask ^= 1 << sel;
                w->finished = 0;
            } else if (sel == 4) {
                currentPokemonPcBoxMarkSet(markMask);
                done = true;
            } else if (sel == 5) {
                done = true;
            }
        }
        updateAll();
    }
    menuClose(0x86);
    menuCloseSync(0x86, 1);
    localWindowRemove(0x86);
    infoWindow.close();
}

void CMenuPokemonLeave::markingMenuItemCallBack(tagWINDOW_WORK *win, tagSPRITE_WORK *sp) {
    s32 id = sp->id;
    s32 idx;
    switch (id) {
    case 0x44B:
        idx = 0;
        break;
    case 0x44D:
        idx = 1;
        break;
    case 0x44F:
        idx = 2;
        break;
    case 0x451:
        idx = 3;
        break;
    case 0x453:
        idx = 4;
        break;
    case 0x455:
        idx = 5;
        break;
    default:
        idx = -1;
        break;
    }
    if (idx != -1) {
        s32 v = windowGetValue(0x86);
        winSpriteSetDisp(sp, !(idx - v));
    } else {
        switch (id) {
        case 0x45B:
            idx = 0;
            break;
        case 0x45C:
            idx = 1;
            break;
        case 0x45D:
            idx = 2;
            break;
        case 0x45E:
            idx = 3;
            break;
        default:
            idx = -1;
            break;
        }
        if (idx != -1) {
            winSpriteSetDisp(sp, (markMask & (1 << idx)) != 0);
        }
    }
}

void CMenuPokemonLeave::depositMenuDraw(long win) {
    menuPtWindowWorkDraw(win);
    boxNameDraw(depositBox, win, 0x487);
    tagWINDOW_WORK *w = windowSearchID(win);
    tagSPRITE_WORK *sp = menuPtSpriteWorkGetByItemID(w, 0x488, 0);
    msgctrlSetValue(0x34, pcBoxUsedQuantity(depositBox));
    msgctrlSetValue(0x35, 0x1E);
    GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, 0x3BD2);
}

void CMenuPokemonLeave::init(CMenuGlobalState &gs) {
    int i;
    time = 0;
    baseAnim.init();
    fadeTime = 0;
    fadeState = 0;
    memset(windows, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = defautlLocalWindowOpenTable;
    if (pcBoxSoundTbl != 0) {
        memcpy(soundTbl, pcBoxSoundTbl, 0x14);
    }
    tutorialActive = 0;
    flag32C = 0;
    val32E = 0;
    memset(&keyInfo, 0, 0x1A);
    repeatCount = 0;
    lastKey = 0;
    anim.init();
    currentBox = menuPcBoxGetLastViewBox();
    prevBox = 0;
    depositBox = 0;
    memset(pcAnt, 0, 0x30C0);
    memset(&temochiX, 0, 0x140);
    temochiX = 0x1E0;
    pad34B0[0] = 0;
    markMask = 0;
    scroll = 0.0f;
    memset(&model, 0, 0xEC);
    modelActive = 0;
    pokemonInit(&statusPokemon);
    displayFlag = 0;
    if (gs.cursor.flag150 != 0) {
        tutorialActive = 1;
    }
    rowY = 0;
    cursorLeft = 4;
    cursorRight = 6;
    savedIndex = 10;
    MENU_ITEM_dd_ *item = menuItemBiosGetPtr(0x82, 0x3EE);
    slotX = item->x;
    slotY = item->y;
    memcpy(posTbl, _cursorPositionTblDefault, 0x10);
    for (i = 0; i < 6; i++) {
        posTbl[4 + i] = getTemochiSlotPosition(i);
    }
    for (i = 0; i < 30; i++) {
        posTbl[10 + i] = getPcBoxSlotPosition(i);
    }
    globalState = &gs;
    cursor = &globalState->cursor;
    cursor->setPositionTable(posTbl, 10);
    resetViewAntAll();
    localWindowSetTable(localWindowTable);
    localWindowCreateAll();
    infoWindow.init(0x87, 0x46A);
    baseInfo.initTutorialTalk();
    menuPtSpriteWorkGetByItemID(0x80, 0x3D4, 0);
    menuModelInit();
}

void CMenuPokemonLeave::main(CMenuGlobalState &gs) {
    init(gs);
    if (globalState->mode == 2) {
        alphaFadeInKick();
        anim.sub = 2;
        memset(anim.saved, 0, 0x40);
    } else {
        systemFadeInKick();
    }
    loop();
    menuModelTerm();
    localWindowDeleteAll();
    cursor->setPositionTableDummy();
    menuPcBoxSetLastViewBox(currentBox);
    CAnt::allRequestCancel();
    CAnt::waitEndOfReading();
}

void thisNew() {
    CMenuPokemonLeave *p = (CMenuPokemonLeave *)GSmemAllocClr(0x38A0);
    new (p) CMenuPokemonLeave;
    pMenuPokemonLeave = p;
}

void thisFree() {
    if (pMenuPokemonLeave != 0) {
        GSmemFree(pMenuPokemonLeave);
        pMenuPokemonLeave = 0;
    }
}

void thisExec(CMenuGlobalState &gs) {
    thisNew();
    pMenuPokemonLeave->main(gs);
    thisFree();
}

Pokemon *CMenuPokemonLeave::pokemonStatusMenuCallback(Pokemon *cur, MENU_POKEMON_CB_TYPE type) {
    Pokemon *p;
    s32 idx;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        if (c->pokemon.checkValid()) {
            return &c->pokemon;
        }
        return 0;
    }
    idx = savedIndex;
    p = 0;
    if (idx >= 4 && idx <= 9) {
        if (type == MENU_POKEMON_CB_TYPE_PREV) {
            for (;;) {
                if (idx <= 4) {
                    idx = 4;
                } else {
                    idx--;
                }
                p = temochiPokemonGetPointer(idx - 4);
                if (p != 0) {
                    break;
                }
                if (idx <= 4) {
                    break;
                }
            }
        } else if (type == MENU_POKEMON_CB_TYPE_NEXT) {
            for (;;) {
                if (idx >= 9) {
                    idx = 9;
                } else {
                    idx++;
                }
                p = temochiPokemonGetPointer(idx - 4);
                if (p != 0) {
                    break;
                }
                if (idx >= 9) {
                    break;
                }
            }
        }
    } else if (idx >= 10) {
        if (type == MENU_POKEMON_CB_TYPE_PREV) {
            for (;;) {
                if (idx <= 10) {
                    idx = 10;
                } else {
                    idx--;
                }
                p = pcBoxPokemonGetPointer(idx - 10);
                if (p != 0) {
                    break;
                }
                if (idx <= 10) {
                    break;
                }
            }
        } else if (type == MENU_POKEMON_CB_TYPE_NEXT) {
            for (;;) {
                if (idx >= 39) {
                    idx = 39;
                } else {
                    idx++;
                }
                p = pcBoxPokemonGetPointer(idx - 10);
                if (p != 0) {
                    break;
                }
                if (idx >= 39) {
                    break;
                }
            }
        }
    }
    if (p != 0) {
        savedIndex = idx;
        return p;
    }
    return cur;
}

void CMenuPokemonLeave::drawStatusArea() {
    tagWINDOW_WORK *w;
    Pokemon *p;
    u8 loaded;
    u32 sexMsg;
    u16 item;
    int i;
    int j;
    int k;
    tagSPRITE_WORK *sp;
    u32 titleMsg;
    u32 nameMsg;
    u32 levelMsg;
    u16 sprites[2];
    f32 angle[3];
    w = windowSearchID(0x80);
    loaded = 0;
    p = getStatusAndModelDisplayPokemonGetPointer();
    if (p != 0 && !menuModelComparePokemon(&model, p) && !menuModelCheck(&model, 0)) {
        menuModelLoadPokemon(&model, p);
        loaded = 1;
        modelActive = 1;
    }
    if (p != 0 && menuModelComparePokemon(&model, p) && !menuModelCheck(&model, 0) && !loaded) {
        menuPtSpriteWorkGetByItemID(w, 0x3D4, 0);
        menuModelAdjustCamera(&model);
        angle[0] = -0.1f;
        angle[1] = 0.3f;
        angle[2] = 0.0f;
        menuModelSetAngle(&model, angle);
        menuModelRender(&model);
    } else {
        menuModelRenderOffAll(&model);
    }
    sexMsg = 0;
    if (p != 0) {
        u8 sex = menuSubGetPokemonSexForDisp(p);
        if (sex == 0) {
            sexMsg = 0x9C5;
        } else if (sex == 1) {
            sexMsg = 0x9C6;
        }
    } else {
        sexMsg = 0;
    }
    menuPtSpriteWorkSetMsgId(0x80, 0x5C2, 0, sexMsg);
    item = 0;
    if (p != 0) {
        item = p->getItemDataId();
    }
    menuPtSpriteWorkSetSw(w, 0x3CF, 0, item != 0);
    for (i = 0; i < 4; i++) {
        menuPtSpriteWorkSetSw(w, 0x3C7, i, p != 0);
    }
    for (j = 0; j < 4; j++) {
        menuPtSpriteWorkSetSw(w, 0x3CB, j, pokemonPcBoxMarkGetIndex(p, j));
    }
    menuPtSpriteWorkSetSw(w, 0x3DB, 0, p != 0);
    menuPtWindowWorkDraw(0x80);
    sp = menuPtSpriteWorkGetByItemID(w, 0x3D9, 0);
    titleMsg = 0x3BD7;
    if (globalState->mode == 2) {
        u32 stage = relivehallGetLastViewStage() + 1;
        titleMsg = 0x3C2D;
        msgctrlSetValue(0x34, stage);
    }
    {
        s16 tw = GSmsgGetRect(titleMsg) >> 16;
        s16 off = (sp->width - tw) / 2;
        GSmsgPrint2(w->layer, sp->x + off, sp->y, -1, titleMsg);
    }
    if (p != 0) {
        switch (pokecoloGetCountryCode()) {
        case 0:
            nameMsg = 0x4276;
            levelMsg = 0x427B;
            break;
        case 1:
        case 2:
            nameMsg = 0x4277;
            levelMsg = 0x4351;
            break;
        }
        if (item != 0) {
            void *itemData = itemDataBiosGetPtr(item);
            if (itemData != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(itemDataBiosGetName(itemData)));
                sp = menuPtSpriteWorkGetByItemID(w, 0x3D8, 0);
                GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameMsg);
            }
        }
        msgctrlSetValue(0x37, GSmsgGetGSchar(pokemonDataBiosGetName(p->getPokemonDataPtr())));
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DC, 0);
        GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameMsg);
        msgctrlSetValue(0x37, (u32)p->getNicknamePtr());
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DA, 0);
        GSmsgPrint2(w->layer, w->x + sp->x, w->y + sp->y, -1, nameMsg);
        sp = menuPtSpriteWorkGetByItemID(w, 0x3DB, 0);
        msgctrlSetValue(0x34, p->getLevel());
        GSmsgPrint2(w->layer, sp->x + 0x24 + w->x, w->y + sp->y, -1, levelMsg);
        if (p->isDarkPokemon()) {
            sp = menuPtSpriteWorkGetByItemID(w, 0x4CE, 0);
            menuDrawReliveMeter3(p, w->x + sp->x, w->y + sp->y, sp->width, sp->height, 0xFF, w->layer);
        }
        for (k = 0; k < 2; k++) {
            sprites[k] = zokuseiGetPokemonSpriteID(p->getPokemonDataPtr(), k);
        }
        {
            tagSPRITE_WORK *a = menuPtSpriteWorkGetByItemID(w, 0x5C0, 0);
            tagSPRITE_WORK *b = menuPtSpriteWorkGetByItemID(w, 0x5C1, 0);
            if (sprites[0] == sprites[1]) {
                menuPtSpriteDraw(sprites[0], (a->x + b->x) / 2, (a->y + b->y) / 2);
            } else {
                menuPtSpriteDraw(sprites[0], a->x, a->y);
                menuPtSpriteDraw(sprites[1], b->x, b->y);
            }
        }
        menuDrawReliveUpdate();
    }
}

void CMenuPokemonLeave::drawBoxArea(int box, f32 t) {
    tagSPRITE_WORK *spr;
    MENU_SPRITE_dd_ *ms;
    tagWINDOW_WORK *w;
    s32 x;
    w = windowSearchID(0x82);
    tagSPRITE_WORK *sp = menuPtSpriteWorkGetByItemID(w, 0x3E5, 0);
    w->x = x = (s32)(sp->width * t);
    ms = menuSpriteBiosGetPtr(box + 0x325);
    for (spr = w->items; spr != 0; spr = spr->next) {
        MENU_ITEM_dd_ *item = menuPtItemGetBySpriteWork(w, spr);
        if (item->spriteID == 0x325) {
            menuPtSpriteWorkSetMenuSprite(spr, ms);
        }
    }
    menuPtWindowWorkDraw(w);
    boxNameDraw(box, 0x82, 0x40E);
    GSprimSetup2DRender(0);
    spriteSetScissor(w->layer, 0xDA, 0, 0x1A6, 0x196);
    CAnt *ant = pcAnt[box];
    for (int i = 0; i < 30; i++) {
        if (ant->unk0 != 0) {
            PocketVec<short> v;
            v.x = x;
            v.y = 0;
            ant->drawAndUpdateWithOffset(v);
        }
        ant++;
    }
    spriteSetOffset(w->layer, 0, 0);
    spriteClearScissor(w->layer);
    spriteSetEnv(w->layer);
}

void CMenuPokemonLeave::stateDepositToPcBoxProc() {
    u8 *work;
    s32 saved;
    bool done;
    saved = depositBox;
    infoWindow.open(0x3BD3, false);
    localWindowEntry(0x89, 0, _depositMenuDrawHook);
    work = anim.saved;
    done = false;
    while (!done) {
        switch (getKeyInfo()->trigger) {
        case 4:
            depositBox = (depositBox + 7) % 8;
            menuPtPlaySe(0x441);
            break;
        case 8:
            depositBox = (depositBox + 1) % 8;
            menuPtPlaySe(0x441);
            break;
        case 0x10:
            if (pcBoxEmptyQuantity(depositBox) != 0) {
                bool catching = cursor->isCatchPokemon();
                Pokemon *p = currentPokemonGetPointer();
                menuPtPlaySe(0x442);
                pcBoxPokemonAdd(p, depositBox);
                currentPokemonDel(false);
                if (!catching) {
                    anim.sub = 9;
                    memset(work, 0, 0x40);
                }
                done = true;
            } else {
                infoWindow.close();
                menuPtPlaySe(0x13);
                infoMessageDisplay(0x3BD4);
                infoWindow.open(0x3BD3, false);
                continue;
            }
            break;
        case 0x20:
            menuPtPlaySe(0x443);
            depositBox = saved;
            done = true;
            break;
        }
        updateAll();
    }
    localWindowRemove(0x89);
    infoWindow.close();
    baseAnim.sub = 2;
    memset(baseAnim.saved, 0, 0x40);
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

void menuPcBoxPokemon(CMenuGlobalState &gs) {
    thisExec(gs);
}

void menuPcBoxSetLastViewBox(long box) {
    *(s32 *)(savedataGetStatus(0, 3) + 0xBC0C) = box;
}

long menuPcBoxGetLastViewBox(void) {
    return *(s32 *)(savedataGetStatus(0, 3) + 0xBC0C);
}
