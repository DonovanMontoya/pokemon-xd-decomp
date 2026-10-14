#include <game/menuPocketToolLayout.hpp>

inline void *operator new(unsigned long, void *p) {
    return p;
}

extern "C" {
void winMsgOpen(s32, u32, s32, s32);
void winMsgClose(s32);
void GSmemFree(void *);
void *GSmemAllocClr(u32);
void *memcpy(void *, const void *, u32);
void pokemonInit(Pokemon *);
void *memset(void *, int, u32);
s32 reliveHallPokemonToAisyou(Pokemon *, Pokemon *);
s32 menuDrawReliveMeter3(Pokemon *, long, long, long, long, u8, s32, long);
void GSmodelSetVisibility(void *, s32);
void scriptModelClose(void *);
}

class CMenuGlobalState;

class CReliveStage {
public:
    s32 getDancerQuantity();
};

namespace {

class CStick {
public:
    void update();
};

class SPokemonView {
public:
    f32 unk0;
    f32 unk4;
    PocketVec<short> getPosition();
};

class CMenuReliveHall : public CMetaMenu {
public:
    s32 stageIndex;
    CReliveStage *stage;
    u8 reserved340[0x620 - 0x340];
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
    u8 reserved10a0[4];
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
    if (cursor->isCatchPokemon()) {
        return tbl_2419[stage->getDancerQuantity()];
    }
    return 0;
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
