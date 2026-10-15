#include <game/menuReliveHallLayout.hpp>

inline void *operator new(unsigned long, void *p) {
    return p;
}

struct GSgfxLayerID {
    s32 id;
};

extern "C" {
void winMsgOpen(s32, u32, s32, s32);
void winMsgClose(s32);
void GSmemFree(void *);
void *GSmemAllocClr(u32);
void *memcpy(void *, const void *, u32);
void pokemonInit(Pokemon *);
u8 pokemonCheckValid(Pokemon *);
void GSmodelSetTexAnimIndex(void *, s32);
void GSmodelSetTexAnimType(void *, s32);
void GSmodelStartTexAnimation(void *);
void *memset(void *, int, u32);
s32 reliveHallPokemonToAisyou(Pokemon *, Pokemon *);
s32 menuDrawReliveMeter3(Pokemon *, long, long, long, long, u8, GSgfxLayerID, long);
void GSprimSetBlendMode(s32);
void GSprimDraw2DPixelListC(void *, s32, void *);
double sin(double);
double cos(double);
extern const GSgfxColAu8 GSgfxColAu8_Black;
extern const GSgfxColAu8 relivehallAisyou2ColorTbl[3];
void GSmodelSetVisibility(void *, s32);
void scriptModelClose(void *);
}

class CMenuGlobalState;

enum MENU_POKEMON_CB_TYPE { MENU_POKEMON_CB_TYPE_0, MENU_POKEMON_CB_TYPE_1, MENU_POKEMON_CB_TYPE_2 };

class CReliveStage {
public:
    s32 getDancerQuantity();
    Pokemon *getDancerPointer(long);
    Pokemon *getVisitorPointer();
};

class CReliveHall {
public:
    static CReliveHall *getPointer();
    CReliveStage *getStage(long);
};

u8 getBitTable(u32 *, long);
void setBitTable(u32 *, long, bool);
long degreeRefresh360(long);

namespace {

class CStick {
public:
    void update();
};

struct SCircleDot {
    s16 color;
    u16 x;
    u16 y;
    u8 alpha;
    u8 reserved7;
};

class SCircle {
public:
    s32 unk0;
    s32 radius;
    u8 reserved8[4];
    SCircleDot dots[0x2800];
    s32 count;
    u8 positions[0x2800][4];
    u8 colors[0x2800][4];
    u8 sw[0x2800];
    u32 *bitTable;
    s32 angleIndex[361];
    void draw();
    void allSwOff();
    void setFade(u8);
    void setSwPrime(int, int, bool);
    void setSw(f32, f32, bool);
    void drawPixelAll(int, int, int);
    void drawPixelOne(int, int, int);
};

class SPokemonView {
public:
    f32 unk0;
    f32 unk4;
    u8 reserved8[0x48];
    PocketVec<short> getPosition();
    Pokemon *getPokemon();
    Pokemon *getPokemonWithPickupOverride();
};

class CMenuReliveHall : public CMetaMenu {
public:
    s32 stageIndex;
    CReliveStage *stage;
    SPokemonView views[7];
    u8 reserved570[0x610 - 0x570];
    s32 cursorIndex;
    s32 *menuTable;
    u8 reserved618[0x620 - 0x618];
    CStick stick;
    u8 reserved621[0x80f54 - 0x621];
    void *model0;
    void *model1;
    void *model2;
    void *model3;
    CMenuPokemonCursor *cursor;
    u8 reserved80f68[0x80f8c - 0x80f68];
    CInfoWindow infoWindow;
    u8 reserved80fc0[4];
    Pokemon visitor;
    u8 visitorFlag;
    u8 reserved81089[3];
    s32 animationState;
    s32 animationFlag;
    u8 reserved10a0[0x10];
    u8 animationWork[0x40];
    virtual void drawMain();
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    void unloadDatas();
    void resetStatusDisplayVisitor();
    void setStatusDisplayVisitor(Pokemon *);
    void infoMessageDisplay(u32);
    void infoMessageDisplay3Line(u32);
    int getPassion(int *);
    int getTempo(bool);
    int getTempoPassion(int *, bool, bool);
    int pokemonToAisyou(Pokemon *, Pokemon *);
    Pokemon *getVisitorWithCatch();
    Pokemon *getPokemonFromPositionWithCatch(int);
    int getQuantityMarkerDancerEmpty();
    void draw9StageInfo();
    int getQuantityMarkerDancerOnPlusDancerEmpty();
    int animationProcessButtonInterrupt();
    void animationStateUpdate();
    void main(CMenuGlobalState &);
    void actionMenuMain();
    f32 calcStarDir(int, int);
    void setStage(int);
    void moveStage(int);
    void resetViewAll();
    void cursorPositionDecideAtStageChange(int);
    Pokemon *getCurrentPokemonPointer();
    Pokemon *getStatusDisplayVisitorGetPointer();
    int dancerPositionQuantityWithCatch();
    void stateDirChangeWinDraw(long);
    Pokemon *actionStatusCallback(Pokemon *, MENU_POKEMON_CB_TYPE);
    GSgfxColAu8 pokemonToAisyouColor(Pokemon *, Pokemon *);
    GSgfxColAu8 positionToAisyouColor(int, int);
};

CMenuReliveHall *pMenuReliveHall;
s32 _lastViewStage;

void thisExec(CMenuGlobalState &);
void thisFree();
void thisNew();

bool CMenuReliveHall::isAnimationStateNone() {
    return animationState == 0;
}

void CMenuReliveHall::updateAll() {
    if (tutorialActive == 0) {
        stick.update();
    }
    CMetaMenu::updateAll();
}

void thisFree() {
    if (pMenuReliveHall != 0) {
        GSmemFree(pMenuReliveHall);
        pMenuReliveHall = 0;
    }
}

void thisNew() {
    CMenuReliveHall *p = (CMenuReliveHall *)GSmemAllocClr(0x81190);
    if (p != 0) {
        new (p) CMenuReliveHall;
    }
    pMenuReliveHall = p;
}

void CMenuReliveHall::infoMessageDisplay3Line(u32 msg) {
    winMsgOpen(2, msg, 1, 0);
    winMsgClose(1);
}

void CMenuReliveHall::infoMessageDisplay(u32 msg) {
    infoWindow.exec(*this, msg, true);
}

int CMenuReliveHall::getPassion(int *out) {
    return getTempoPassion(out, true, false);
}

int CMenuReliveHall::getTempo(bool flag) {
    return getTempoPassion(0, flag, true);
}

int CMenuReliveHall::pokemonToAisyou(Pokemon *a, Pokemon *b) {
    int r = reliveHallPokemonToAisyou(a, b);
    if (r == -1) {
        r = 0;
    }
    return r;
}

Pokemon *CMenuReliveHall::getVisitorWithCatch() {
    return getPokemonFromPositionWithCatch(6);
}

void CMenuReliveHall::resetStatusDisplayVisitor() {
    pokemonInit(&visitor);
    visitorFlag = 0;
}

void CMenuReliveHall::setStatusDisplayVisitor(Pokemon *p) {
    visitorFlag = 1;
    if (p == 0) {
        pokemonInit(&visitor);
    } else {
        memcpy(&visitor, p, 0xC4);
    }
}

void CMenuReliveHall::unloadDatas() {
    localWindowDeleteAll();
    GSmodelSetVisibility(model3, 0);
    GSmodelSetVisibility(model2, 0);
    scriptModelClose(model1);
    scriptModelClose(model0);
}


void SCircle::draw() {
    GSprimSetBlendMode(1);
    GSprimDraw2DPixelListC(positions, count, colors);
}

void SCircle::allSwOff() {
    int i;
    for (i = 0; i < count; i++) {
        sw[i] = 0;
        colors[i][3] = 0;
    }
}

void SCircle::setFade(u8 fade) {
    int i;
    for (i = 0; i < count; i++) {
        if (sw[i] != 0) {
            colors[i][3] = dots[i].alpha * fade / 255;
        }
    }
}

void SCircle::setSw(f32 a, f32 b, bool on) {
    long start = degreeRefresh360((s32)(180.0f * a / 3.1415927f));
    long end = degreeRefresh360((s32)(180.0f * b / 3.1415927f));
    if (end == 0) {
        end = 360;
    }
    if (start > end) {
        setSwPrime(start, 360, on);
        setSwPrime(0, end, on);
    } else {
        setSwPrime(start, end, on);
    }
}

void SCircle::drawPixelAll(int cx, int cy, int color) {
    int x;
    int y;
    for (x = -radius; x <= radius; x++) {
        for (y = -radius; y <= radius; y++) {
            drawPixelOne(cx + x, cy + y, color);
        }
    }
}

void SCircle::drawPixelOne(int x, int y, int color) {
    if (!getBitTable(bitTable, x + y * 0x280)) {
        SCircleDot *dot = &dots[count++];
        dot->x = x;
        dot->y = y;
        dot->alpha = 0xFF;
        dot->color = color;
        setBitTable(bitTable, dot->x + dot->y * 0x280, true);
    }
}

PocketVec<short> _circleDirToPosition(f32 dir) {
    PocketVec<short> v;
    v.x = (s16)(90.0f * (f32)sin(dir) + 320.0f);
    v.y = (s16)(280.0f - 90.0f * (f32)cos(dir));
    return v;
}

PocketVec<short> SPokemonView::getPosition() {
    return _circleDirToPosition(unk4);
}

Pokemon *SPokemonView::getPokemon() {
    long index = this - pMenuReliveHall->views;
    if (index < pMenuReliveHall->stage->getDancerQuantity()) {
        return pMenuReliveHall->stage->getDancerPointer(index);
    }
    if (index == 6) {
        return pMenuReliveHall->stage->getVisitorPointer();
    }
    return 0;
}

Pokemon *SPokemonView::getPokemonWithPickupOverride() {
    if (pMenuReliveHall->cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = pMenuReliveHall->cursor;
        if (this - pMenuReliveHall->views == c->index) {
            if (c->pokemon.checkValid()) {
                return &c->pokemon;
            }
            return 0;
        }
    }
    return getPokemon();
}

Pokemon *CMenuReliveHall::getPokemonFromPositionWithCatch(int position) {
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        if (position == c->index) {
            if (c->pokemon.checkValid()) {
                return &c->pokemon;
            }
            return 0;
        }
    }
    if (position < stage->getDancerQuantity()) {
        return stage->getDancerPointer(position);
    }
    if (position == 6) {
        return stage->getVisitorPointer();
    }
    return 0;
}

GSgfxColAu8 CMenuReliveHall::pokemonToAisyouColor(Pokemon *a, Pokemon *b) {
    int aisyou = reliveHallPokemonToAisyou(a, b);
    if (aisyou == -1) {
        return GSgfxColAu8_Black;
    }
    return relivehallAisyou2ColorTbl[aisyou];
}

GSgfxColAu8 CMenuReliveHall::positionToAisyouColor(int a, int b) {
    Pokemon *pa = getPokemonFromPositionWithCatch(a);
    Pokemon *pb = getPokemonFromPositionWithCatch(b);
    return pokemonToAisyouColor(pa, pb);
}

Pokemon *CMenuReliveHall::actionStatusCallback(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type) {
    int quantity;
    if (cursor->isCatchPokemon()) {
        return pokemon;
    }
    quantity = stage->getDancerQuantity();
    if (type == MENU_POKEMON_CB_TYPE_1) {
        if (cursorIndex == 6) {
            if (quantity != 0) {
                cursorIndex = quantity - 1;
            }
        } else if (cursorIndex > 0) {
            cursorIndex = cursorIndex - 1;
        }
    } else if (type == MENU_POKEMON_CB_TYPE_2) {
        if (cursorIndex < quantity) {
            cursorIndex = cursorIndex + 1;
            if (cursorIndex >= quantity) {
                if (stage->getVisitorPointer() != 0) {
                    cursorIndex = 6;
                } else {
                    cursorIndex = quantity - 1;
                }
            }
        }
    }
    if (cursorIndex < quantity) {
        pokemon = stage->getDancerPointer(cursorIndex);
    } else if (cursorIndex == 6) {
        pokemon = stage->getVisitorPointer();
    }
    return pokemon;
}

Pokemon *_cbMenuPokemonStatus(Pokemon *pokemon, MENU_POKEMON_CB_TYPE type, long) {
    return pMenuReliveHall->actionStatusCallback(pokemon, type);
}

void _stateDirChangeProcHook(CMetaMenu *menu, long arg) {
    ((CMenuReliveHall *)menu)->stateDirChangeWinDraw(arg);
}

s32 _menuDrawReliveMeter(Pokemon *p, long a, long b, long c, long d, u8 e, GSgfxLayerID layer, long f) {
    return menuDrawReliveMeter3(p, a, b, c, d, e, layer, f);
}

long rate01ToAlphaFrom50(f32 rate) {
    return (s32)(205.0f * rate + 50.0f);
}

long isDirRegionInReverseClockwise(f32 a, f32 b, f32 c) {
    if (c > b) {
        if (c <= a || a <= b) {
            return 1;
        }
        return 0;
    }
    if (c <= a && a <= b) {
        return 1;
    }
    return 0;
}

void thisExec(CMenuGlobalState &state) {
    thisNew();
    pMenuReliveHall->main(state);
    thisFree();
}

Pokemon *CMenuReliveHall::getCurrentPokemonPointer() {
    Pokemon *result = 0;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        Pokemon *p;
        if (c->pokemon.checkValid()) {
            p = &c->pokemon;
        } else {
            p = 0;
        }
        result = p;
    } else {
        u8 inRange = 0;
        int index = cursor->index;
        if (index >= 0 && index <= 5) {
            inRange = 1;
        }
        if (inRange) {
            result = stage->getDancerPointer(index);
        } else if (index == 6) {
            result = stage->getVisitorPointer();
        }
    }
    return result;
}

Pokemon *CMenuReliveHall::getStatusDisplayVisitorGetPointer() {
    if (cursor->index == 6 && visitorFlag != 0) {
        if (pokemonCheckValid(&visitor)) {
            return &visitor;
        }
        return 0;
    }
    return getVisitorWithCatch();
}

int CMenuReliveHall::dancerPositionQuantityWithCatch() {
    CMenuPokemonCursor *c;
    u8 notDark;
    int quantity;
    quantity = stage->getDancerQuantity();
    notDark = 0;
    if (cursor->isCatchPokemon()) {
        Pokemon *p;
        c = cursor;
        if (c->pokemon.checkValid()) {
            p = &c->pokemon;
        } else {
            p = 0;
        }
        if (!p->isDarkPokemon()) {
            notDark = 1;
        }
    }
    if (notDark) {
        u8 add = 0;
        int index = cursor->index;
        if (stage->getDancerQuantity() <= index && cursor->index <= 5) {
            add = 1;
        }
        if (add) {
            quantity += 1;
        }
    }
    return quantity;
}

void CMenuReliveHall::setStage(int stageNo) {
    int old = stageIndex;
    stageIndex = stageNo;
    stage = CReliveHall::getPointer()->getStage(stageIndex);
    GSmodelSetTexAnimIndex(model2, stageIndex);
    GSmodelSetTexAnimType(model2, 0);
    GSmodelStartTexAnimation(model2);
    cursorPositionDecideAtStageChange(old);
    resetViewAll();
    animationFlag = 1;
    memset(animationWork, 0, 0x40);
}

void CMenuReliveHall::moveStage(int delta) {
    int next;
    menuPtPlaySe(0x45F);
    next = stageIndex + delta;
    if (next < 0) {
        next = 8;
    } else if (next >= 9) {
        next = 0;
    }
    setStage(next);
}

static const s32 yTbl_2631[7] = { 0, 0, 0, 0x79, 0x64, 0, 0 };

void CMenuReliveHall::actionMenuMain() {
    s32 *table = menuTable;
    s32 count = table[0];
    actionMenu((u32 *)(table + 1), count, 0x1D7, yTbl_2631[count]);
}

f32 CMenuReliveHall::calcStarDir(int a, int b) {
    return 2.0f * (3.1415927f * ((f32)a / (f32)b)) + 6.2831855f * calcAnimationTimeRate0to1(6.0f);
}
}

void relivehallDraw9StageInfo(int);

void relivehallDraw9StageNumber(int stage) {
    int i = 0;
    do {
        MENU_ITEM_dd_ *item = menuPtItemGetByMenuIdAndItemId(0x72, 0x2A7, i);
        u8 alpha;
        if (i == stage) {
            alpha = 0xFF;
        } else {
            alpha = 0x3C;
        }
        menuPtItemDrawAlpha(item, alpha);
        i++;
    } while (i < 9);
}

namespace {

s32 tbl_2419[5] = { 1, 1, 2, 3, 0 };

int CMenuReliveHall::getQuantityMarkerDancerEmpty() {
    int quantity;
    if (cursor->isCatchPokemon() == 0) {
        quantity = 0;
    } else {
        quantity = tbl_2419[stage->getDancerQuantity()];
    }
    return quantity;
}

int CMenuReliveHall::getQuantityMarkerDancerOnPlusDancerEmpty() {
    int q = stage->getDancerQuantity();
    return q + getQuantityMarkerDancerEmpty();
}

void CMenuReliveHall::draw9StageInfo() {
    relivehallDraw9StageNumber(stageIndex);
    relivehallDraw9StageInfo(stageIndex);
}

int CMenuReliveHall::animationProcessButtonInterrupt() {
    if (animationState != 0) {
        animationFlag = 0;
        memset(animationWork, 0, 0x40);
        animationStateUpdate();
    }
    return 0;
}

}

void menuReliveHallExecFromPcBox(CMenuGlobalState &state) {
    thisExec(state);
}

void relivehallSetLastViewStage(long stage) {
    _lastViewStage = stage;
}

long relivehallGetLastViewStage(void) {
    return _lastViewStage;
}

long relivehallTempoToLevel(int tempo) {
    if (tempo <= 26) {
        return 0;
    }
    if (tempo <= 53) {
        return 1;
    }
    return 2;
}

f32 relivehallTempoToRate(int tempo) {
    return (f32)tempo / 96.0f;
}
