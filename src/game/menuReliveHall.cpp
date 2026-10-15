#include <game/menuReliveHallLayout.hpp>
#include <game/maximum/GSAPI/baselib/math_support.h>

inline void *operator new(unsigned long, void *p) {
    return p;
}

class GSgfxLayer;
struct SF32 {
    f32 v;
};
enum GSgfxLayerID { GSgfxLayerID_Default = 0 };

extern "C" {
DarkPokemon *darkPokemonGetDarkPokemon(long);
void winMsgOpen(s32, u32, s32, s32);
void GSfsysReadWait(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
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
s32 menuDrawReliveMeter3(Pokemon *, long, long, long, long, u8, GSgfxLayerID, long);
void GSprimSetBlendMode(s32);
void GSprimDraw2DPixelListC(void *, s32, void *);
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
double sin(double);
double fabs(double);
double cos(double);
extern const GSgfxColAu8 GSgfxColAu8_Black;
GSgfxColAu8 relivehallAisyou2ColorTbl[3] = {{40, 0, 255, 255}, {40, 170, 255, 255}, {200, 240, 255, 255}};
u32 pcReliveHallSoundTbl[5] = {0x459, 0x45A, 0x45B, 0x14, 0x15};
s16 lbl_8032E568[10] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 0};
void GSmodelSetVisibility(void *, s32);
void scriptModelClose(void *);
u32 floorGetCurrentGroupID();
void *scriptModelOpen(u32);
void *GSresGetResource(u32, void *);
void GSmodelStopTexAnimation(void *);
void cameraPlayAnime(u32, u32, s32, f32);
void cameraSetType(s32);
void msgctrlSetValue(s32, const void *);
GSgfxLayer *GSgfxLayerFindByID(s32);
void GSprimSetLineWidth(f32);
void GSprimDraw2DLine(GSgfxColAu8 *, GSgfxColAu8 *, SF32, SF32, SF32, SF32);
void menuDrawReliveUpdate();
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
tagWINDOW_WORK *windowSearchID(s32);
u16 zokuseiGetPokemonSpriteID(void *, u16);
void spriteSetScissor(s32, s32, s32, s32, s32);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteSetOffset(s32, s32, s32);
void winSpriteDraw(tagWINDOW_WORK *, tagSPRITE_WORK *);
}

void GSprimSetup2DRender(GSgfxLayer *);
s32 reliveHallPokemonToAisyou(Pokemon *, Pokemon *);
u8 isDirRegionIn(f32, f32, f32);
f32 dirSubOne(f32, f32);
f32 dirSubHalf(f32, f32);
void menuPtSpriteDrawAndRollScale(u16, u32, f32, f32, f32, f32);
class CMenuGlobalState;
void relivehallDrawStageInfoCursor(long, int, int, Pokemon *, bool);
long relivehallTempoToLevel(int);
long relivehallGetLastViewStage(void);
void relivehallSetLastViewStage(long);
f32 relivehallTempoToRate(int);
long degreeSubHalf(long, long);
long xyxy2dirDegree(const PocketVec<short> &, const PocketVec<short> &);
f32 xyxy2distance(const PocketVec<short> &, const PocketVec<short> &);
f32 xy2dir(f32, f32);
f32 xyxy2dir(const PocketVec<short> &, const PocketVec<short> &);

enum MENU_POKEMON_CB_TYPE { MENU_POKEMON_CB_TYPE_0, MENU_POKEMON_CB_TYPE_1, MENU_POKEMON_CB_TYPE_2 };
extern "C" s32 menuPokemonStatusOpenFromPcBox(Pokemon *, Pokemon *(*)(Pokemon *, MENU_POKEMON_CB_TYPE, long), long);

class CReliveStage {
public:
    Pokemon slots[5];
    s8 partner;
    void init();
    int getPassion();
    bool isBonusGet();
    s32 getDancerQuantity();
    int getTempo();
    Pokemon *getDancerPointer(long);
    Pokemon *getVisitorPointer();
    void exchangeDancer(Pokemon &, long);
    void exchangeVisitor(Pokemon &);
    void insertDancer(Pokemon &, long);
    void putVisitor(Pokemon &);
    void pickupDancer(Pokemon &, long);
    void pickupVisitor(Pokemon &);
};

class PCBOX {
public:
    static PCBOX *getPointer();
    bool isPokemonFull();
};

class CReliveHall {
public:
    static CReliveHall *getPointer();
    s32 getReliveGiveStageQuantity();
    bool isReliveReadyDarkLugiaExist();
    bool isReliveReadyPokemonExist();
    CReliveStage *getStage(long);
};

u8 getBitTable(u32 *, long);
void setBitTable(u32 *, long, bool);
long degreeRefresh360(long);

bool lbl_804EA7F0;

namespace {

class CStick {
public:
    u8 trigger, on, previous, reserved3;
    f32 angle;
    u32 frames;
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
    f32 outer;
    s32 radius;
    f32 inner;
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
    void init(f32, int, f32, GSgfxColAu8);
};

class SPokemonView {
public:
    u8 unk0, hidden;
    u8 reserved2[2];
    f32 unk4, targetAngle, startAngle;
    CAnt ant;
    f32 facing, targetFacing, startFacing;
    PocketVec<short> getPosition();
    Pokemon *getPokemon();
    Pokemon *getPokemonWithPickupOverride();
};

struct SHallHitEffect {
    u8 active;
    u8 reserved[3];
    f32 rate;
};

class CMenuReliveHall : public CMetaMenu {
public:
    s32 stageIndex;
    CReliveStage *stage;
    SPokemonView views[9];
    s32 cursorIndex;
    s32 *menuTable;
    s32 reserved618;
    s32 reserved61C;
    CStick stick;
    SCircle circles[3];
    void *model0;
    void *model1;
    void *model2;
    void *model3;
    CMenuPokemonCursor *cursor;
    PocketVec<short> cursorPositions[9];
    CInfoWindow infoWindow;
    s32 hallTempo;
    Pokemon visitor;
    u8 visitorFlag;
    u8 reserved81089[3];
    s32 animationState;
    s32 animationFlag;
    u8 reserved10a0[0x10];
    u8 animationWork[0x40];
    u8 reserved810e4[0x81134 - 0x810e4];
    u8 markerAlpha, effectAlpha, circleAlpha, starAlpha, lineAlpha;
    u8 reserved81139;
    PocketVec<short> markerOverride[9];
    u8 reserved8115e[0x81184 - 0x8115e];
    SHallHitEffect hitEffect;
    virtual void drawAll();
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    void unloadDatas();
    void loadDatas();
    void editAfterDp0VisitorCheck();
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
    void drawStageCursor();
    void drawStagePokemon();
    void drawMainBG();
    void drawVisitorStarLight(long, SPokemonView *);
    void drawDancerStarLight();
    void drawMarkers(bool);
    void drawVsitorLine(long, SPokemonView *);
    void drawStatusPanel();
    void drawStarLightOne(long, f32, f32, long);
    void drawVisitorHitEffect();
    void drawDancerHitEffect();
    int getQuantityMarkerDancerOnPlusDancerEmpty();
    bool animationProcessButtonInterrupt();
    void animationStateUpdate();
    void main(CMenuGlobalState &);
    int actionMenuMain();
    void actionStatus();
    void actionChange();
    void actionPut();
    void actionPickup();
    void dancerMoveAnimationKick(f32 *, f32 *, bool, f32);
    void actionDecide(u32);
    void loop();
    void init(CMenuGlobalState &);
    f32 calcStarDir(int, int);
    SPokemonView *getPokemonViewByClockwizePositionWithCatch(int);
    int getDirToAisyou(f32);
    void getCircleColorAisyou(f32 &, f32 &, int &, int);
    f32 starTimeFromBorn(f32 &, f32 &, f32);
    void drawStarHitEffect(f32, f32, f32);
    void dancerMoveAnimationOne(SPokemonView &, f32);
    void dancerMoveAnimationAll(f32);
    void setCircleSw();
    void animationDataReset();
    void makeCursorPositionTbl(PocketVec<short> *);
    int cursorMoveDirSearch(PocketVec<short> *, int, int);
    void cursorMoveDir(int);
    void setStage(int);
    void moveStage(int);
    void resetViewAll();
    void cursorPositionDecideAtStageChange(int);
    void stateDirChangeProc();
    void aButtomAction();
    void stateMainProc();
    bool catchDark();
    bool catchNotDark();
    bool catchDarkB();
    bool catchNotDarkB();
    Pokemon *getCurrentPokemonPointer();
    Pokemon *getStatusDisplayVisitorGetPointer();
    int dancerPositionQuantityWithCatch();
    void stateDirChangeWinDraw(long);
    Pokemon *actionStatusCallback(Pokemon *, MENU_POKEMON_CB_TYPE);
    GSgfxColAu8 pokemonToAisyouColor(Pokemon *, Pokemon *);
    GSgfxColAu8 positionToAisyouColor(int, int);
};

typedef char HallViewSize[sizeof(SPokemonView) == 0x50 ? 1 : -1];
typedef char HallStickSize[sizeof(CStick) == 0xc ? 1 : -1];
typedef char HallCircleSize[sizeof(SCircle) == 0x2adb8 ? 1 : -1];
typedef char HallWorkSize[sizeof(CMenuReliveHall) == 0x81190 ? 1 : -1];

static u8 blurAlphaTbl[9] = {255, 215, 175, 135, 95, 55, 0, 0, 0};
static f32 blurScaleTbl[9] = {1.0f, 0.85f, 0.7f, 0.55f, 0.4f, 0.25f, 0.0f, 0.0f, 0.0f};
static f32 starMasterScaleTbl[10] = {1.1f, 0.85f, 1.0f, 0.9f, 1.1f, 0.9f, 0.85f, 1.1f, 1.0f, 0.85f};
static f32 _markerDancerOnDirTbl[20] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f,
    0.0f, 0.0f, 0.0f, 2.0943952f, 4.1887903f, 0.0f, 5.497787f, 0.7853982f, 2.3561945f, 3.9269907f
};
static f32 _zokuseiMarkDancerOnDirTbl[20] = {
    0.0f, 0.0f, 0.0f, 0.0f, 1.4486233f, 0.0f, 0.0f, 0.0f, 1.4486233f, 1.6929694f,
    0.0f, 0.0f, 1.4486233f, 1.9373156f, 4.328417f, 0.0f, 4.82409f, 1.4590952f, 1.6824975f, 4.600688f
};
static f32 _markerDancerEmptyDirTbl[16] = {
    0.0f, 0.0f, 0.0f, 0.0f, 3.1415927f, 0.0f, 0.0f, 0.0f,
    1.5707964f, 4.712389f, 0.0f, 0.0f, 1.0471976f, 3.1415927f, 5.235988f, 0.0f
};
static PocketVec<short> _cursorPositionTblDefault[9] = {
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {320, 280}, {198, 428}, {539, 428}
};
static GSgfxColAu8 _passion2ColorTbl[13] = {
    {40, 0, 255, 255}, {40, 85, 255, 255}, {40, 170, 255, 255}, {120, 205, 255, 255},
    {200, 240, 255, 255}, {200, 240, 255, 255}, {200, 240, 255, 255}, {200, 240, 255, 255},
    {200, 240, 255, 255}, {200, 240, 255, 255}, {200, 240, 255, 255}, {200, 240, 255, 255},
    {200, 240, 255, 255}
};
static f32 _aisyou2ScaleTbl[3] = {0.6f, 0.8f, 1.0f};

struct SLineWidth {
    s32 half;
    f32 rate;
    s32 half2;
    f32 rate2;
};
static SLineWidth _aisyou2LineWidthHalfTable[3] = {
    {1, 0.75f, 1, 0.3f}, {2, 1.5f, 2, 0.6f}, {3, 2.25f, 3, 0.9f}
};
static s32 localWindowTable[8] = {0x67, 0x71, 0x72, 0x88, 0x76, 0xCF, 0xE3, 0};
static s32 actionMenuCatchVisitorOnPokemon[6] = {4, 0xD111, 0xD112, 0xD113, 0xD114, 0};
static s32 actionMenuCatchDancerOnPokemon[6] = {3, 0xD111, 0xD113, 0xD114, 0, 0};
static s32 actionMenuCatchVisitorOnNone[6] = {4, 0xD115, 0xD112, 0xD113, 0xD114, 0};
static s32 actionMenuCatchDancerOnNone[6] = {3, 0xD115, 0xD113, 0xD114, 0, 0};
static s32 actionMenuOnVisitor[6] = {4, 0xD116, 0xD112, 0xD113, 0xD114, 0};
static s32 actionMenuOnDancer[6] = {3, 0xD116, 0xD113, 0xD114, 0, 0};

s32 tbl_2419[5] = { 1, 1, 2, 3, 0 };

void menuPtSpriteDrawArrow(u16, u32, f32, int);

CMenuReliveHall *pMenuReliveHall;
s32 _lastViewStage;

void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK *, u32, int, u8, bool);
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
    new (p) CMenuReliveHall;
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

void CMenuReliveHall::init(CMenuGlobalState &gs) {
    time = 0;
    ((CState *)((u8 *)this + 0x278))->init();
    fadeTime = 0;
    fadeState = 0;
    memset(windows, 0, 0x100);
    memset(windowFuncs, 0, 0x100);
    windowTable = defautlLocalWindowOpenTable;
    if (pcReliveHallSoundTbl != 0) {
        memcpy(reserved8, pcReliveHallSoundTbl, 0x14);
    }
    tutorialActive = 0;
    flag32C = 0;
    val32E = 0;
    memset(&keyInfo, 0, 0x1A);
    repeatCount = 0;
    lastKey = 0;
    stageIndex = -1;
    stage = 0;
    memset(views, 0, 0x2D0);
    cursorIndex = 0;
    memset(&menuTable, 0, 0xC);
    memset(&stick, 0, 0xC);
    for (u32 i = 0; i < 3; i++) {
        GSgfxColAu8 color = relivehallAisyou2ColorTbl[i];
        circles[i].init(_aisyou2LineWidthHalfTable[i].rate, _aisyou2LineWidthHalfTable[i].half2,
                        _aisyou2LineWidthHalfTable[i].rate2, color);
    }
    memset(&model0, 0, 0x10);
    ((CState *)((u8 *)this + 0x278))->init();
    globalState = 0;
    cursor = 0;
    memset(cursorPositions, 0, 0x24);
    hallTempo = 0;
    pokemonInit(&visitor);
    visitorFlag = 0;
    if (gs.cursor.flag150 != 0) {
        tutorialActive = 1;
    }
    globalState = &gs;
    cursor = &globalState->cursor;
    cursor->setPositionTable(cursorPositions, 0);
    ((CState *)((u8 *)this + 0x278))->init();
    ((CState *)&animationState)->init();
    s16 *markers = (s16 *)markerOverride;
    for (unsigned int i = 0; i < 18; i++) markers[i] = -1;
    circleAlpha = 255;
    lineAlpha = 255;
    starAlpha = 255;
    effectAlpha = 255;
    markerAlpha = 255;
    memset(&hitEffect, 0, sizeof(hitEffect));
    localWindowSetTable(localWindowTable);
    loadDatas();
    infoWindow.init(0xCF, 0x5D0);
    baseInfoWindow.initTutorialTalk();
    setStage(relivehallGetLastViewStage());
}

void CMenuReliveHall::main(CMenuGlobalState &global) {
    PocketVec<short> position = global.cursor.getPosition();
    init(global);
    if (globalState->mode == 1) {
        alphaFadeInKick();
        animationFlag = 6;
        memset(animationWork, 0, 0x40);
        cursor->setPosition(position);
    } else {
        systemFadeInKick();
    }
    state = 1;
    memset(stateWork, 0, 0x40);
    loop();
    unloadDatas();
    cursor->setPositionTableDummy();
    relivehallSetLastViewStage(stageIndex);
    CAnt::allRequestCancel();
    CAnt::waitEndOfReading();
}

void CMenuReliveHall::unloadDatas() {
    localWindowDeleteAll();
    GSmodelSetVisibility(model3, 0);
    GSmodelSetVisibility(model2, 0);
    scriptModelClose(model1);
    scriptModelClose(model0);
}


void CStick::update() {
    s8 leftY;
    s8 leftX;
    s8 rightY;
    s8 rightX;
    u8 hold;
    previous = on;
    leftY = GSinputGetLeftStickYData(1, 0);
    leftX = GSinputGetLeftStickXData(1, 0);
    rightY = GSinputGetRightStickYData(1, 0);
    rightX = GSinputGetRightStickXData(1, 0);
    angle = 0.0f;
    if ((leftX < 0 ? -leftX : leftX) > 0x20 || (leftY < 0 ? -leftY : leftY) > 0x20) {
        angle = xy2dir(leftX, leftY);
        on = 1;
    } else if ((rightX < 0 ? -rightX : rightX) > 0x16 || (rightY < 0 ? -rightY : rightY) > 0x16) {
        angle = xy2dir(rightX, rightY);
        on = 1;
    } else {
        on = 0;
    }
    hold = 0;
    trigger = 0;
    if (on != 0 && previous == 0) {
        trigger = 1;
    } else if (on != 0 && on == previous) {
        if (frames >= 12) {
            trigger = on;
        } else {
            hold = 1;
        }
    }
    if (hold != 0) {
        frames = frames + 1;
        return;
    }
    frames = 0;
}

void SCircle::init(f32 outerRadius, int dotRadius, f32 innerRadius, GSgfxColAu8 color) {
    memset(this, 0, sizeof(SCircle));
    outer = outerRadius;
    radius = dotRadius;
    inner = innerRadius;
    bitTable = (u32 *)GSmemAllocClr(0x7D00);
    count = 0;
    f32 angle = 0.0f;
    int prevX = -1;
    int prevY = -1;
    int prevDeg = -1;
    while (angle < 6.2831855f) {
        int px = (int)(90.0f * (f32)sin(angle)) + 0x140;
        int py = (int)(90.0f * -(f32)cos(angle)) + 0x118;
        int deg = degreeRefresh360((long)(180.0f * angle / 3.1415927f));
        if (deg != prevDeg) {
            angleIndex[deg] = count;
        }
        if (px != prevX || py != prevY) {
            drawPixelAll(px, py, deg);
            prevX = px;
            prevY = py;
        }
        prevDeg = deg;
        angle += 0.008726646f;
    }
    angleIndex[360] = count;
    for (int i = 0; i < count; i++) {
        int dx = dots[i].x - 0x140;
        dx = dx > 0 ? dx : -dx;
        int dy = dots[i].y - 0x118;
        dy = dy > 0 ? dy : -dy;
        f32 dist = hsdSqrt((f32)(dx * dx + dy * dy));
        f32 diff = (f32)fabs(dist - 90.0f);
        if (diff <= inner) {
            dots[i].alpha = 0xFF;
        } else if (diff < outer) {
            dots[i].alpha = (u8)(255.0f * (outer - diff) / (outer - inner));
        } else {
            dots[i].alpha = 0;
        }
    }
    for (int i = 0; i < count; i++) {
        *(s16 *)&positions[i][0] = dots[i].x;
        *(s16 *)&positions[i][2] = dots[i].y;
    }
    for (int i = 0; i < count; i++) {
        colors[i][0] = color.r;
        colors[i][1] = color.g;
        colors[i][2] = color.b;
        colors[i][3] = color.a;
    }
    memset(sw, 0, 0x2800);
    if (bitTable != 0) {
        GSmemFree(bitTable);
        bitTable = 0;
    }
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

void SCircle::setSwPrime(int start, int end, bool on) {
    int i = angleIndex[start];
    int last = angleIndex[end];
    if (on) {
        for (; i < last; i++) {
            sw[i] = on;
            colors[i][3] = dots[i].alpha;
        }
    } else {
        for (; i < last; i++) {
            sw[i] = on;
            colors[i][3] = 0;
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

Pokemon *_cbMenuPokemonStatus(Pokemon *, MENU_POKEMON_CB_TYPE, long);

void CMenuReliveHall::actionStatus() {
    systemFadeOutSetAndWait(-1.0f);
    unloadDatas();
    GSfsysReadWait(0x66F);
    Pokemon *pokemon = getCurrentPokemonPointer();
    cursorIndex = cursor->index;
    menuPokemonStatusOpenFromPcBox(pokemon, _cbMenuPokemonStatus, 0);
    cursor->setPositionIndex(cursorIndex);
    GSfsysFree(0x66F);
    GSresFreeGroup(0x66F);
    loadDatas();
    systemFadeInKick();
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

void CMenuReliveHall::drawStageCursor() {
    ::relivehallDrawStageInfoCursor(stageIndex, getTempo(true), dancerPositionQuantityWithCatch(),
                                   getStatusDisplayVisitorGetPointer(), true);
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

inline bool isDancerSlot(int i) {
    bool r = false;
    if (i >= 0 && i <= 5) r = true;
    return r;
}

void CMenuReliveHall::actionChange() {
    bool isDancer;
    hallTempo = getTempo(false);
    CMenuPokemonCursor *c = cursor;
    if (c->index == 6) {
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        setStatusDisplayVisitor(p);
    }
    c = cursor;
    Pokemon *p2;
    if (c->pokemon.checkValid()) p2 = &c->pokemon;
    else p2 = 0;
    Pokemon tmp = *p2;
    int idx = cursor->index;
    isDancer = isDancerSlot(idx);
    if (isDancer) stage->exchangeDancer(tmp, idx);
    else stage->exchangeVisitor(tmp);
    cursor->setPokemon(&tmp);
    animationFlag = 7;
    memset(animationWork, 0, 0x40);
    resetViewAll();
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::dancerMoveAnimationKick(f32 *pos, f32 *face, bool pickup, f32 newAngle) {
    int n = stage->getDancerQuantity();
    for (int i = 0; i < n; i++) {
        SPokemonView *v = &views[i];
        v->targetAngle = v->unk4;
        f32 a = pos[i];
        v->startAngle = a;
        v->unk4 = a;
        v->targetFacing = v->facing;
        f32 b = face[i];
        v->startFacing = b;
        v->facing = b;
    }
    if (pickup) {
        SPokemonView *v = &views[cursor->index];
        v->targetAngle = v->unk4;
        v->startAngle = newAngle;
        v->unk4 = newAngle;
        f32 f = v->facing;
        v->startFacing = f;
        v->facing = f;
        v->targetFacing = f;
    }
    setCircleSw();
    animationFlag = 2;
    memset(animationWork, 0, 0x40);
    makeCursorPositionTbl(cursorPositions);
}

void CMenuReliveHall::resetViewAll() {
    int off, i, quantity;
    f32 *angles, *facings;
    memset(views, 0, 0x2D0);
    Pokemon *visitorPokemon = stage->getVisitorPointer();
    memset(&views[6].ant, 0, 0x34);
    if (visitorPokemon != 0) {
        views[6].ant.initByPokemonAndSetColorAnimationInReliveHallVisitor(visitorPokemon);
        views[6].ant.setAnimation(0);
    }
    quantity = stage->getDancerQuantity();
    off = quantity * 16;
    angles = (f32 *)((u8 *)_markerDancerOnDirTbl + off);
    facings = (f32 *)((u8 *)_zokuseiMarkDancerOnDirTbl + off);
    i = 0;
    for (; i < quantity; i++) {
        Pokemon *pokemon = stage->getDancerPointer(i);
        f32 a = *angles;
        views[i].unk4 = views[i].targetAngle = views[i].startAngle = a;
        f32 f = *facings;
        views[i].facing = views[i].targetFacing = views[i].startFacing = f;
        views[i].unk0 = 0;
        views[i].ant.initByPokemon(pokemon);
        views[i].ant.setAnimation(1);
        angles++;
        facings++;
    }
    int empty = getQuantityMarkerDancerEmpty();
    if (empty != 0) {
        f32 *marks = (f32 *)((u8 *)_markerDancerEmptyDirTbl + off);
        for (int k = 0; k < empty; k++) {
            SPokemonView *v = &views[i + k];
            v->unk0 = 1;
            v->unk4 = *marks++;
            v->targetAngle = v->unk4;
            v->startAngle = v->unk4;
        }
    }
    setCircleSw();
    makeCursorPositionTbl(cursorPositions);
}

inline bool CMenuReliveHall::catchDark() {
    CMenuPokemonCursor *cc;
    u8 result = 0;
    if (cursor->isCatchPokemon()) {
        cc = cursor;
        Pokemon *p;
        if (cc->pokemon.checkValid()) p = &cc->pokemon;
        else p = 0;
        if (p->isDarkPokemon()) result = 1;
    }
    return result;
}

inline bool CMenuReliveHall::catchNotDark() {
    CMenuPokemonCursor *cc;
    u8 result = 0;
    if (cursor->isCatchPokemon()) {
        cc = cursor;
        Pokemon *p;
        if (cc->pokemon.checkValid()) p = &cc->pokemon;
        else p = 0;
        if (!p->isDarkPokemon()) result = 1;
    }
    return result;
}

inline bool CMenuReliveHall::catchDarkB() {
    u8 result = 0;
    CMenuPokemonCursor *cc;
    if (cursor->isCatchPokemon()) {
        cc = cursor;
        Pokemon *p;
        if (cc->pokemon.checkValid()) p = &cc->pokemon;
        else p = 0;
        if (p->isDarkPokemon()) result = 1;
    }
    return result;
}

inline bool CMenuReliveHall::catchNotDarkB() {
    u8 result = 0;
    CMenuPokemonCursor *cc;
    if (cursor->isCatchPokemon()) {
        cc = cursor;
        Pokemon *p;
        if (cc->pokemon.checkValid()) p = &cc->pokemon;
        else p = 0;
        if (!p->isDarkPokemon()) result = 1;
    }
    return result;
}

void CMenuReliveHall::cursorPositionDecideAtStageChange(int old) {
    int position;
    int oldQuantity;
    if (old == -1 && globalState->mode == 1) {
        position = 7;
    } else {
        oldQuantity = -1;
        if (old != -1) {
            oldQuantity = CReliveHall::getPointer()->getStage(old)->getDancerQuantity();
        }
        int index = cursor->index;
        position = index;
        if (position == 6) {
            if (stage->getVisitorPointer() == 0) {
                if (!catchDark()) {
                    position = -1;
                }
            }
        } else {
            if (isDancerSlot(position) && oldQuantity != stage->getDancerQuantity()) {
                position = -1;
            }
        }
        if (position == -1) {
            if (catchNotDark() || stage->getVisitorPointer() == 0) {
                if (catchDark()) {
                six:
                    position = 6;
                } else if (catchDark() || stage->getDancerQuantity() == 0) {
                    if (catchNotDark()) {
                    zero:
                        position = 0;
                    } else {
                        position = 7;
                    }
                } else {
                    goto zero;
                }
            } else {
                goto six;
            }
        }
    }
    cursor->setPositionIndex(position);
}

void CMenuReliveHall::actionPut() {
    f32 pos[4];
    f32 face[4];
    int idx;
    int slot;
    int at;
    hallTempo = getTempo(false);
    menuPtPlaySe(0x45E);
    slot = -1;
    CMenuPokemonCursor *c = cursor;
    idx = c->index;
    if (isDancerSlot(idx)) {
        int n = stage->getDancerQuantity();
        if (n == 0) {
            slot = 0;
        } else if (n == 3 && cursor->index == 5) {
            slot = 0;
        } else {
            int cur = cursor->index;
            slot = cur - stage->getDancerQuantity();
            slot += 1;
        }
        c = cursor;
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        stage->insertDancer(*p, at = slot);
        s8 part = stage->partner;
        if (n != 0 && part >= slot) part++;
        stage->partner = part;
        cursor->setPositionIndex(at);
        for (int i = 0; i < n + 1; i++) {
            if (i != slot) {
                pos[i] = views[i].unk4;
                face[i] = views[i].facing;
            } else {
                pos[i] = views[idx].unk4;
                face[i] = 0.0f;
            }
        }
    } else if (idx == 6) {
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        stage->putVisitor(*p);
    }
    resetViewAll();
    if (slot != -1) {
        dancerMoveAnimationKick(pos, face, false, -1.0f);
        SPokemonView *v = &views[cursor->index];
        v->startFacing = v->targetFacing;
        v->facing = v->targetFacing;
    } else {
        animationFlag = 4;
        memset(animationWork, 0, 0x40);
    }
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::actionPickup() {
    f32 pos[4];
    f32 face[4];
    Pokemon dancerTmp;
    Pokemon visitorTmp;
    hallTempo = getTempo(false);
    menuPtPlaySe(0x45D);
    u8 moved = 0;
    int idx = cursor->index;
    f32 oldPos = views[idx].unk4;
    if (isDancerSlot(idx)) {
        moved = 1;
        int n = stage->getDancerQuantity();
        stage->pickupDancer(dancerTmp, cursor->index);
        cursor->setPokemon(&dancerTmp);
        u8 t = stage->partner;
        int part = t;
        if ((s8)t > cursor->index) part = t - 1;
        if ((s8)part >= stage->getDancerQuantity()) part = 0;
        stage->partner = part;
        for (int i = 0; i < n; i++) {
            if (i != cursor->index) {
                face[i] = views[i].facing;
                pos[i] = views[i].unk4;
            }
        }
    } else if (idx == 6) {
        memcpy(markerOverride, cursorPositions, 0x24);
        stage->pickupVisitor(visitorTmp);
        cursor->setPokemon(&visitorTmp);
    }
    int ci = cursor->index;
    if (isDancerSlot(ci)) {
        int slot;
        if (stage->getDancerQuantity() == 3 && ci == 0) {
            slot = 5;
        } else {
            int t = ci - 1;
            if (t < 0) t = 0;
            slot = t + stage->getDancerQuantity();
        }
        cursor->setPositionIndex(slot);
    }
    resetViewAll();
    if (moved) {
        dancerMoveAnimationKick(pos, face, true, oldPos);
    } else {
        animationFlag = 5;
        memset(animationWork, 0, 0x40);
    }
    editAfterDp0VisitorCheck();
}

void CMenuReliveHall::aButtomAction() {
    memset(&menuTable, 0, 0xC);
    reserved618 = -1;
    reserved61C = -1;
    switch (cursor->index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5: {
        if (catchNotDarkB()) {
            int idx = cursor->index;
            if (idx < stage->getDancerQuantity()) {
                if (cursor->unk14C != 0) {
                    actionChange();
                } else {
                    menuTable = actionMenuCatchDancerOnPokemon;
                }
            } else if (cursor->unk14C != 0) {
                actionPut();
            } else {
                menuTable = actionMenuCatchDancerOnNone;
            }
        } else {
            int idx = cursor->index;
            if (idx < stage->getDancerQuantity()) {
                if (cursor->unk14C != 0) {
                    actionPickup();
                } else {
                    menuTable = actionMenuOnDancer;
                }
            }
        }
        break;
    }
    case 6: {
        u8 dark = 0;
        u8 multiple = stage->getDancerQuantity() >= 2;
        if (catchDarkB()) {
            dark = 1;
        }
        if (dark != 0) {
            if (views[6].ant.unk0 != 0) {
                if (cursor->unk14C != 0) {
                    actionChange();
                } else {
                    s32 *t;
                    if (multiple != 0) t = actionMenuCatchVisitorOnPokemon;
                    else t = actionMenuCatchDancerOnPokemon;
                    menuTable = t;
                }
            } else if (cursor->unk14C != 0) {
                actionPut();
            } else {
                s32 *t;
                if (multiple != 0) t = actionMenuCatchVisitorOnNone;
                else t = actionMenuCatchDancerOnNone;
                menuTable = t;
            }
        } else if (views[6].ant.unk0 != 0) {
            if (cursor->unk14C != 0) {
                actionPickup();
            } else {
                s32 *t;
                if (multiple != 0) t = actionMenuOnVisitor;
                else t = actionMenuOnDancer;
                menuTable = t;
            }
        }
        break;
    }
    case 7:
        state = 6;
        memset(stateWork, 0, 0x40);
        break;
    case 8:
        state = 8;
        memset(stateWork, 0, 0x40);
        break;
    default:
        break;
    }
    if (menuTable != 0) {
        state = 3;
        memset(stateWork, 0, 0x40);
    }
}

void CMenuReliveHall::stateMainProc() {
    bool lugia;
    u8 *work;
    u8 done;
    MetaKeyInfo *key;
    DarkPokemon *dark;
    bool anyKey;
    u8 unhandled;
    memset(&stick, 0, 0xC);
    work = stateWork;
    done = 0;
    while (done == 0) {
        key = getKeyInfo();
        lugia = CReliveHall::getPointer()->isReliveReadyDarkLugiaExist();
        anyKey = (key->trigger | key->repeat) != 0;
        if (anyKey != 0 || stick.trigger != 0) {
            if (animationProcessButtonInterrupt()) {
                return;
            }
        }
        if (stick.trigger != 0) {
            cursorMoveDir((s32)(180.0f * stick.angle / 3.1415927f));
        } else if (stick.on == 0 && anyKey != 0) {
            unhandled = 0;
            switch (key->repeat) {
            case 1:
                cursorMoveDir(0);
                break;
            case 8:
                cursorMoveDir(90);
                break;
            case 2:
                cursorMoveDir(180);
                break;
            case 4:
                cursorMoveDir(270);
                break;
            case 9:
                cursorMoveDir(45);
                break;
            case 10:
                cursorMoveDir(135);
                break;
            case 6:
                cursorMoveDir(225);
                break;
            case 5:
                cursorMoveDir(315);
                break;
            case 0x200:
                moveStage(-1);
                break;
            case 0x400:
                moveStage(1);
                break;
            default:
                unhandled = 1;
                break;
            }
            if (unhandled != 0) {
                switch (key->trigger) {
                case 0x10:
                    if (!cursor->isCatchPokemon()) {
                        menuPtPlaySe(0x45A);
                    }
                    aButtomAction();
                    done = 1;
                    break;
                case 0x20:
                    if (!cursor->isCatchPokemon()) {
                        menuPtPlaySe(0x45B);
                    }
                    state = 8;
                    memset(work, 0, 0x40);
                    done = 1;
                    break;
                case 0x40:
                case 0x80:
                    cursor->unk14C = !cursor->unk14C;
                    break;
                case 0x100:
                    menuPtPlaySe(0x45A);
                    state = 6;
                    memset(work, 0, 0x40);
                    break;
                }
            }
        }
        updateAll();
        if (!lugia && CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
            infoMessageDisplay(0xD152);
        }
        dark = darkPokemonGetDarkPokemon(0x49);
        if (CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
            dark->setDarkPointDirect(0);
        } else if (dark->getStatus() == 4) {
            dark->setDarkPointDirect(0);
        } else {
            dark->setDarkPointDirect(dark->getInitDarkPointDirect());
        }
        if (state != -1) {
            break;
        }
    }
}

void CMenuReliveHall::loop() {
    u8 *work = stateWork;
    for (;;) {
        ((CState *)&current)->update();
        switch (current) {
        case 1:
            state = 2;
            memset(work, 0, 0x40);
            lbl_804EA7F0 = globalState->mode == 3;
            break;
        case 2:
            stateMainProc();
            break;
        case 3: {
            infoWindow.setMsgCtrlValue(0x32, (u32)getCurrentPokemonPointer()->getNicknamePtr());
            infoWindow.open(0xD110, false);
            int selected = actionMenuMain();
            infoWindow.close();
            bool lugia = CReliveHall::getPointer()->isReliveReadyDarkLugiaExist();
            actionDecide(menuTable[selected + 1]);
            if (!lugia && CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
                infoMessageDisplay(0xD152);
            }
            DarkPokemon *dark = darkPokemonGetDarkPokemon(0x49);
            if (CReliveHall::getPointer()->isReliveReadyDarkLugiaExist()) {
                dark->setDarkPointDirect(0);
            } else if (dark->getStatus() == 4) {
                dark->setDarkPointDirect(0);
            } else {
                dark->setDarkPointDirect(dark->getInitDarkPointDirect());
            }
            break;
        }
        case 4:
            actionStatus();
            state = 2;
            memset(work, 0, 0x40);
            break;
        case 5:
            stateDirChangeProc();
            state = 2;
            memset(work, 0, 0x40);
            break;
        case 6:
            alphaFadeOutAndWait();
            {
                CMenuGlobalState *gs = globalState;
                gs->mode = gs->unk8;
                gs->unk8 = 1;
            }
            return;
        case 7:
            menuPtPlaySe(0x13);
            infoMessageDisplay(0xD11B);
            state = 2;
            memset(work, 0, 0x40);
            break;
        case 8:
            if (globalState->cursor.flag151 != 0) {
                state = 9;
                memset(work, 0, 0x40);
            } else if (cursor->isCatchPokemon()) {
                state = 7;
                memset(work, 0, 0x40);
            } else {
                u32 choices[2] = {0x426A, 0x426B};
                infoWindow.open(globalState->mode == 3 ? 0xD15B : 0xD124, false);
                int selected = actionMenu(choices, 2, 0x1FB, 0x8C);
                infoWindow.close();
                if (selected == 0) {
                    state = 2;
                    memset(work, 0, 0x40);
                } else {
                    state = 9;
                    memset(work, 0, 0x40);
                }
            }
            break;
        case 9: {
            int result = 0;
            if (globalState->unk0 != 3 && CReliveHall::getPointer()->isReliveReadyPokemonExist()) {
                int previous = globalState->unk0;
                if (PCBOX::getPointer()->isPokemonFull()) {
                    infoMessageDisplay3Line(0xD12F);
                    if (previous == 2) {
                        result = 4;
                    }
                } else {
                    infoMessageDisplay3Line(0xD0FD);
                }
            }
            {
                CMenuGlobalState *gs = globalState;
                gs->mode = gs->unk8;
                gs->unk8 = result;
                systemFadeOutSetAndWait(-1.0f);
            }
            return;
        }
        }
    }
}

void CMenuReliveHall::actionDecide(u32 action) {
    switch (action) {
    case 0xD111:
        actionChange();
        break;
    case 0xD112:
        state = 5;
        memset(stateWork, 0, 0x40);
        break;
    case 0xD113:
        state = 4;
        memset(stateWork, 0, 0x40);
        break;
    case 0xD115:
        actionPut();
        break;
    case 0xD116:
        actionPickup();
        break;
    case 0xD114:
        break;
    }
    if (state == -1) {
        state = 2;
        memset(stateWork, 0, 0x40);
    }
}

int CMenuReliveHall::actionMenuMain() {
    static s32 yTbl[7] = {0, 0, 0, 0x79, 0x64, 0, 0};
    s32 *table = menuTable;
    s32 count = table[0];
    return actionMenu((u32 *)(table + 1), count, 0x1D7, yTbl[count]);
}

f32 CMenuReliveHall::calcStarDir(int a, int b) {
    f32 rate = calcAnimationTimeRate0to1(6.0f);
    f32 spin = 6.2831855f * rate;
    return 2.0f * (3.1415927f * ((f32)a / (f32)b)) + spin;
}
}

void relivehallDraw9StageInfo(int);

void relivehallDraw9StageInfo(int selected) {
    int x = 0;
    s16 *stageOffset = lbl_8032E568;
    MENU_ITEM_dd_ *item;
    for (int i = 0; i < 9; i++) {
        if (i != selected) {
            int offset = x + *stageOffset;
            CReliveStage *stage = CReliveHall::getPointer()->getStage(i);
            Pokemon *visitor = CReliveHall::getPointer()->getStage(i)->getVisitorPointer();
            if (visitor != 0) {
                item = menuItemBiosGetPtr(0x72, 0x2b2);
                _menuDrawReliveMeter(visitor, item->x + offset, item->y, item->width, item->height,
                                    255, (GSgfxLayerID)windowSearchID(0x72)->layer, i);
            }
            if (stage->getDancerQuantity() != 0) {
                menuPtItemDrawOffset(menuItemBiosGetPtr(0x72, 0x2b0), offset, 0);
                int tempo = stage->getTempo();
                u32 color = GSgfxColAu8To32(relivehallAisyou2ColorTbl[relivehallTempoToLevel(tempo)]);
                item = menuItemBiosGetPtr(0x72, 0x2b1);
                menuPtItemDrawOffsetXWColor(item, offset, (s32)(item->width * relivehallTempoToRate(tempo)), color);
            }
        }
        x += 66;
        stageOffset++;
    }
}

void relivehallDrawStageInfoCursor(long selected, int tempo, int quantity, Pokemon *pokemon, bool active) {
    long offset;
    tagWINDOW_WORK *window = windowSearchID(0x71);
    offset = selected * 66;
    window->x = offset;
    window->x += lbl_8032E568[selected];
    _relivehallTempoBarSpriteSetting(window, 0x2b4, tempo, 255, false);
    menuPtSpriteWorkSetSw(window, 0x2b3, 0, quantity != 0);
    menuPtSpriteWorkSetSw(window, 0x2ba, 0, active);
    menuPtSpriteWorkSetSw(window, 0x8e9, 0, active == 0);
    menuPtWindowWorkDraw(window);
    if (pokemon != 0) {
        int x = offset + lbl_8032E568[selected];
        MENU_ITEM_dd_ *item = menuItemBiosGetPtr(0x71, 0x2b5);
        _menuDrawReliveMeter(pokemon, item->x + x, item->y, item->width, item->height,
                            255, (GSgfxLayerID)window->layer, selected);
    }
}

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

const PocketVec<short> circlePosition = { 320, 280 };
const PocketVec<f32> fcirclePosition = { 320.0f, 280.0f };
void _antZokuseiDraw(SPokemonView &);
void _antDraw(SPokemonView &);
void _antDraw(SPokemonView &, PocketVec<short>);

void _antDraw(SPokemonView &view) {
    if (view.hidden == 0) {
        view.ant.drawAndUpdate(view.getPosition());
    }
}

void _antDraw(SPokemonView &view, PocketVec<short> position) {
    if (view.hidden == 0) {
        view.ant.drawAndUpdate(position);
    }
}

inline void copyStage(CReliveStage *dst, CReliveStage *src) {
    memcpy(&dst->slots[0], &src->slots[0], 0xC4);
    memcpy(&dst->slots[1], &src->slots[1], 0xC4);
    memcpy(&dst->slots[2], &src->slots[2], 0xC4);
    memcpy(&dst->slots[3], &src->slots[3], 0xC4);
    memcpy(&dst->slots[4], &src->slots[4], 0xC4);
    dst->partner = src->partner;
}

int CMenuReliveHall::getTempoPassion(int *bonus, bool swap, bool tempo) {
    long index;
    CReliveStage *stage = CReliveHall::getPointer()->getStage(index = stageIndex);
    CReliveStage *work = 0;
    CReliveStage *backup = 0;
    int count;
    Pokemon *dest;
    int result;
    if (swap) {
        backup = (CReliveStage *)GSmemAllocClr(0x3D8);
        work = (CReliveStage *)GSmemAllocClr(0x3D8);
        unsigned int dataId;
        int found;
        int i;
        Pokemon *partner = stage->getDancerPointer(stage->partner);
        dataId = 0;
        if (partner != 0) {
            dataId = partner->getPokemonDataId();
        }
        work->init();
        Pokemon *visitorPokemon = getStatusDisplayVisitorGetPointer();
        if (visitorPokemon != 0) {
            memcpy(&work->slots[4], visitorPokemon, 0xC4);
        }
        found = 0;
        count = dancerPositionQuantityWithCatch();
        dest = work->slots;
        for (i = 0; i < count; i++) {
            Pokemon *pokemon = getPokemonViewByClockwizePositionWithCatch(i)->getPokemonWithPickupOverride();
            memcpy(dest, pokemon, 0xC4);
            if (dataId == pokemon->getPokemonDataId()) {
                found = i;
            }
            dest++;
        }
        work->partner = (s8)found;
        copyStage(backup, stage);
        copyStage(stage, work);
    }
    CReliveStage *current = CReliveHall::getPointer()->getStage(index);
    if (tempo) {
        result = current->getTempo();
    } else {
        result = current->getPassion();
    }
    if (bonus != 0) {
        *bonus = 0;
        if (stage->isBonusGet()) {
            *bonus = CReliveHall::getPointer()->getReliveGiveStageQuantity();
        }
    }
    if (work != 0) {
        copyStage(stage, backup);
        if (work != 0) GSmemFree(work);
        if (backup != 0) GSmemFree(backup);
    }
    return result;
}

int CMenuReliveHall::getDirToAisyou(f32 direction) {
    int quantity = dancerPositionQuantityWithCatch();
    int index;
    SPokemonView *first, *second;
    for (index = 0; index < quantity; index++) {
        first = getPokemonViewByClockwizePositionWithCatch(index);
        second = getPokemonViewByClockwizePositionWithCatch((index + 1) % quantity);
        if (isDirRegionIn(direction, first->unk4, second->unk4)) {
            return pokemonToAisyou(first->getPokemonWithPickupOverride(), second->getPokemonWithPickupOverride());
        }
    }
    return -1;
}

void CMenuReliveHall::getCircleColorAisyou(f32 &start, f32 &end, int &color, int index) {
    GSgfxColAu8 selectedColor;
    int quantity = dancerPositionQuantityWithCatch();
    SPokemonView *first = getPokemonViewByClockwizePositionWithCatch(index);
    SPokemonView *second = getPokemonViewByClockwizePositionWithCatch((index + 1) % quantity);
    color = pokemonToAisyou(first->getPokemonWithPickupOverride(), second->getPokemonWithPickupOverride());
    start = first->unk4;
    selectedColor = relivehallAisyou2ColorTbl[color];
    end = second->unk4;
}

f32 CMenuReliveHall::starTimeFromBorn(f32 &x, f32 &y, f32 direction) {
    int quantity = dancerPositionQuantityWithCatch();
    int index;
    SPokemonView *first;
    for (index = 0; index < quantity; index++) {
        first = getPokemonViewByClockwizePositionWithCatch(index);
        SPokemonView *second = getPokemonViewByClockwizePositionWithCatch((index + 1) % quantity);
        if (isDirRegionIn(direction, first->unk4, second->unk4)) {
            x = 90.0f * (f32)sin(first->unk4) + 320.0f;
            f32 cosine = (f32)cos(first->unk4);
            y = 90.0f * -cosine + 280.0f;
            f32 distance = dirSubOne(direction, first->unk4);
            distance /= 6.2831855f;
            return distance * 6.0f;
        }
    }
    return 0.0f;
}

void CMenuReliveHall::drawStarLightOne(long aisyou, f32 x, f32 y, long index) {
    f32 master;
    unsigned long step = index + calcAnimationTimeRate0toX(0.32f, 10);
    GSgfxColAu8 color = relivehallAisyou2ColorTbl[aisyou];
    f32 scale = _aisyou2ScaleTbl[aisyou];
    color.a = blurAlphaTbl[index] * effectAlpha / 255;
    master = starMasterScaleTbl[step % 10];
    menuPtSpriteDrawAndRollScale(0x140, GSgfxColAu8To32(color), x, y, 0.0f, master * (scale * blurScaleTbl[index]));
}

void CMenuReliveHall::drawDancerStarLight() {
    int visible = dancerPositionQuantityWithCatch();
    if (visible != 0) {
        int quantity = stage->getDancerQuantity();
        if (quantity == 0 && visible == 1) quantity = 1;
        int index;
        for (index = 0; index < quantity; index++) {
            f32 base = calcStarDir(index, quantity);
            int j = 0;
            do {
                f32 angle = -(0.06981317f * (f32)j - base);
                f32 s = (f32)sin(angle);
                f32 c = (f32)cos(angle);
                drawStarLightOne(getDirToAisyou(angle), 90.0f * s + 320.0f, 90.0f * -c + 280.0f, j);
                j++;
            } while (j < 6);
        }
    }
}

void CMenuReliveHall::drawVsitorLine(long aisyou, SPokemonView *view) {
    if (views[6].hidden == 0) {
        GSgfxColAu8 color = relivehallAisyou2ColorTbl[aisyou];
        u8 alpha = markerAlpha;
        int width = _aisyou2LineWidthHalfTable[aisyou].half;
        color.a = color.a * alpha / 255;
        PocketVec<short> p0 = view->getPosition();
        f32 y = p0.y;
        PocketVec<short> p1 = view->getPosition();
        f32 x = p1.x;
        f32 angle = 1.5707964f + xy2dir(x - fcirclePosition.x, y - fcirclePosition.y);
        f32 w = 0.0f;
        while (w < (f32)width) {
            f32 offset = w - (f32)(width / 2);
            f32 s = offset * (f32)sin(angle);
            f32 c = (f32)cos(angle);
            GSgfxColAu8 c1 = color, c2 = color;
            SF32 bx, by, ax, ay;
            ax.v = fcirclePosition.x + s;
            bx.v = x + s;
            f32 d = offset * -c;
            ay.v = fcirclePosition.y + d;
            by.v = y + d;
            GSprimDraw2DLine(&c1, &c2, ax, ay, bx, by);
            w += 0.5f;
        }
    }
}

void CMenuReliveHall::drawMainBG() {
    tagWINDOW_WORK *window = windowSearchID(0x67);
    GSgfxColAu8 *colors;
    int level, cur, i;
    u8 hasVisitor = getVisitorWithCatch() != 0;
    int bonus;
    int passion = getPassion(&bonus);
    if (passion <= 0) {
        level = 0;
    } else if (passion <= 0x1B) {
        level = 1;
    } else if (passion <= 0x34) {
        level = 2;
    } else if (passion <= 0x5A) {
        level = 3;
    } else if (passion < 0xC0) {
        level = 4;
    } else {
        level = bonus + 4;
    }
    f32 rate = calcAnimationTimeRate0to1(0.8f);
    colors = _passion2ColorTbl;
    i = 0;
    cur = (s32)(rate / 0.03846154f);
    f32 frac = -((f32)cur * 0.03846154f - rate) * 26.0f;
    f32 inv = 1.0f - frac;
    do {
        tagSPRITE_WORK *sprite = menuPtSpriteWorkGetByItemID(window, 0x28D, i);
        GSgfxColAu8 color = *colors;
        sprite->color.value = GSgfxColAu8To32(color);
        if (i < level && hasVisitor) {
            u8 alpha;
            if (cur < 13) {
                if (i < cur) {
                    alpha = 0xFF;
                } else if (i == cur) {
                    alpha = rate01ToAlphaFrom50(frac);
                } else {
                    alpha = 0x46;
                }
            } else {
                int base = cur - 13;
                if (i < base) {
                    alpha = 0x46;
                } else if (i == base) {
                    alpha = rate01ToAlphaFrom50(inv);
                } else {
                    alpha = 0xFF;
                }
            }
            menuPtSpriteWorkSetSw(window, sprite, true);
            sprite->color.channels.alpha = alpha;
        } else {
            menuPtSpriteWorkSetSw(window, sprite, false);
        }
        colors++;
        i++;
    } while (i < 13);
    menuPtSpriteWorkSetSw(window, 0x28C, 0, hasVisitor);
    menuPtSpriteWorkSetSw(window, 0x316, 0, false);
    menuPtSpriteWorkSetSw(window, 0x28B, 0, false);
    menuPtSpriteWorkSetSw(window, 0x28A, 0, dancerPositionQuantityWithCatch() != 0);
    menuPtSpriteWorkSetSw(window, 0x4D1, 0, dancerPositionQuantityWithCatch() != 0);
    menuPtSpriteWorkSetSw(window, 0x8EE, 0, hasVisitor);
    menuPtSpriteWorkSetSw(window, 0x4D2, 0, hasVisitor);
    menuPtWindowWorkDraw(window);
}

#define HALL_ABS_DIR(a, b) (dirSubHalf(a, b) < 0.0f ? -dirSubHalf(a, b) : dirSubHalf(a, b))

void CMenuReliveHall::stateDirChangeProc() {
    int partner;
    int original;
    u8 done;
    u8 active;
    f32 angle;
    f32 best;
    int bestIndex;
    CMenuReliveHall *view;
    int i;
    MetaKeyInfo *key;
    memset(&stick, 0, 0xC);
    cursor->unk0 = 0;
    effectAlpha = 0;
    windowSearchID(0x76);
    partner = stage->partner;
    original = partner;
    memset(&stick, 0, 0xC);
    infoWindow.setMsgCtrlValue(0x32, (u32)getCurrentPokemonPointer()->getNicknamePtr());
    infoWindow.open(0xD117, false);
    localWindowEntry(0x76, 0, _stateDirChangeProcHook);
    done = 0;
    do {
        active = stick.on;
        angle = stick.angle;
        key = getKeyInfo();
        switch (key->trigger) {
        case 0x10:
            menuPtPlaySe(0x45A);
            done = 1;
            break;
        case 0x20:
            stage->partner = original;
            menuPtPlaySe(0x45B);
            done = 1;
            break;
        }
        if (done == 0) {
            switch (key->repeat) {
            case 1:
                angle = 0.0f;
                active = 1;
                break;
            case 8:
                angle = 1.5707964f;
                active = 1;
                break;
            case 2:
                angle = 3.1415927f;
                active = 1;
                break;
            case 4:
                angle = 4.712389f;
                active = 1;
                break;
            case 9:
                angle = 0.7853982f;
                active = 1;
                break;
            case 10:
                angle = 2.3561945f;
                active = 1;
                break;
            case 6:
                angle = 3.9269907f;
                active = 1;
                break;
            case 5:
                active = 1;
                angle = 5.497787f;
                break;
            }
            if (active != 0) {
                best = 3.1415927f;
                view = this;
                bestIndex = 0;
                for (i = 0; i < stage->getDancerQuantity(); i++) {
                    PocketVec<short> position = view->views[0].getPosition();
                    f32 dir = xyxy2dir(position, circlePosition);
                    f32 diff = HALL_ABS_DIR(dir, angle);
                    if (best > diff) {
                        best = diff;
                        bestIndex = i;
                    }
                    view = (CMenuReliveHall *)((u8 *)view + 0x50);
                }
                if (partner != bestIndex) {
                    menuPtPlaySe(0x459);
                }
                partner = bestIndex;
                stage->partner = bestIndex;
            }
        }
        updateAll();
    } while (done == 0);
    localWindowRemove(0x76);
    infoWindow.close();
    cursor->unk0 = 1;
    effectAlpha = 0xFF;
}

void CMenuReliveHall::drawVisitorStarLight(long aisyou, SPokemonView *view) {
    f32 radius = 90.0f * calcAnimationTimeRate0to1(1.5f);
    PocketVec<short> position = view->getPosition();
    f32 dir = xyxy2dir(position, circlePosition);
    int j = 0;
    int k = 0;
    do {
        f32 d = radius - (f32)k;
        if (!(d < 0.0f)) {
            f32 s = (f32)sin(dir);
            drawStarLightOne(aisyou, d * s + 320.0f, d * -(f32)cos(dir) + 280.0f, j);
        }
        k += 5;
        j++;
    } while (j < 6);
}

void CMenuReliveHall::stateDirChangeWinDraw(long window) {
    s8 partner;
    u32 color;
    int i;
    menuPtWindowWorkDraw(window);
    partner = stage->partner;
    color = rate01ToAlphaFrom50((f32)sin(3.1415927f * calcAnimationTimeRate0to1(0.5f))) | ~0xFF;
    for (i = 0; i < stage->getDancerQuantity(); i++) {
        PocketVec<short> position = views[i].getPosition();
        f32 dir = xyxy2dir(position, circlePosition);
        if (i == partner) {
            menuPtSpriteDrawArrow(0x13F, color, dir, 0);
        }
        GSgfxColAu8 arrow = positionToAisyouColor(6, i);
        menuPtSpriteDrawArrow(0x183, GSgfxColAu8To32(arrow), dir, -12);
    }
}

void CMenuReliveHall::drawMarkers(bool back) {
    PocketVec<short> *positions;
    if (markerOverride[0].x != -1) positions = markerOverride;
    else positions = cursorPositions;
    int i;
    for (i = 0; i <= 6; i++) {
        if (views[i].hidden == 0) {
            u16 sprite = 0x294;
            u8 alpha;
            if (i == 6) {
                alpha = circleAlpha;
            } else if (i >= stage->getDancerQuantity()) {
                sprite = 0x296;
                alpha = starAlpha;
            } else {
                alpha = lineAlpha;
            }
            if (alpha != 0 && positions[i].x != -1) {
                u32 color = alpha | ~0xFF;
                if (back) {
                    if (sprite == 0x294) menuPtSpriteDrawCenterColor(0x2E0, positions[i].x, positions[i].y, color);
                } else {
                    menuPtSpriteDrawCenterColor(sprite, positions[i].x, positions[i].y, color);
                }
            }
        }
    }
}

void CMenuReliveHall::drawStarHitEffect(f32 x, f32 y, f32 time) {
    if (time < 0.5f) {
        f32 rate = time / 0.5f;
        u8 alpha = (u8)(s32)(255.0f * (1.0f - rate));
        alpha = effectAlpha * alpha / 255;
        u32 color = alpha | ~0xff;
        menuPtSpriteDrawAndRollScale(0x297, color, x, y, 0.0f, 0.5f + rate);
    }
}

void CMenuReliveHall::drawVisitorHitEffect() {
    if (dancerPositionQuantityWithCatch() != 0) {
        if (!getVisitorWithCatch()) return;
        if (stage->partner != -1) {
            f32 time = calcAnimationTimeRate0to1(1.5f);
            time *= 1.5f;
            drawStarHitEffect(320.0f, 280.0f, time);
        }
    }
}

void CMenuReliveHall::drawDancerHitEffect() {
    int visible = dancerPositionQuantityWithCatch();
    if (visible != 0) {
        int quantity = stage->getDancerQuantity();
        if (quantity == 0 && visible == 1) quantity = 1;
        int index;
        for (index = 0; index < quantity; index++) {
            f32 x, y;
            f32 time = starTimeFromBorn(x, y, calcStarDir(index, quantity));
            drawStarHitEffect(x, y, time);
        }
    }
}

void CMenuReliveHall::dancerMoveAnimationOne(SPokemonView &view, f32 rate) {
    f32 movement = rate * dirSubHalf(view.targetAngle, view.startAngle);
    view.unk4 = movement + view.startAngle;
    f32 delta = dirSubHalf(view.targetFacing, view.startFacing);
    f32 magnitude;
    if (delta < 0.0f) magnitude = -delta;
    else magnitude = delta;
    if (magnitude > 1.5707964f) {
        view.facing = view.startFacing;
        return;
    }
    movement = rate * delta;
    view.facing = movement + view.startFacing;
}

SPokemonView *CMenuReliveHall::getPokemonViewByClockwizePositionWithCatch(int position) {
    if (position == 6) return &views[6];
    u8 notDark = 0;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        if (!p->isDarkPokemon()) notDark = 1;
    }
    if (notDark) {
        int picked = cursor->index;
        if (picked >= stage->getDancerQuantity()) {
            picked = cursor->index;
            int offset = picked - stage->getDancerQuantity() + 1;
            if (position < offset) return &views[position];
            if (position == offset) return &views[picked];
            return &views[position - 1];
        }
    }
    return &views[position];
}

void CMenuReliveHall::setCircleSw() {
    int quantity = dancerPositionQuantityWithCatch();
    if (quantity == 0) {
        for (unsigned int i = 0; i < 3; i++) circles[i].allSwOff();
        return;
    }
    for (int i = 0; i < quantity; i++) {
        f32 start, end;
        int color;
        getCircleColorAisyou(start, end, color, i);
        for (unsigned int j = 0; j < 3; j++) {
            if ((int)j == color) circles[j].setSw(start, end, true);
            else circles[j].setSw(start, end, false);
        }
    }
}

void CMenuReliveHall::dancerMoveAnimationAll(f32 rate) {
    int quantity;
    int position;
    int index;
    quantity = stage->getDancerQuantity();
    for (index = 0; index < quantity; index++) dancerMoveAnimationOne(views[index], rate);
    position = cursor->index;
    u8 isEmpty = 0;
    if (stage->getDancerQuantity() <= position && cursor->index <= 5) isEmpty = 1;
    if (isEmpty) dancerMoveAnimationOne(views[cursor->index], rate);
    setCircleSw();
    makeCursorPositionTbl(cursorPositions);
}

void CMenuReliveHall::makeCursorPositionTbl(PocketVec<short> *positions) {
    memcpy(positions, _cursorPositionTblDefault, sizeof(_cursorPositionTblDefault));
    u8 dark = 0;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        if (p->isDarkPokemon()) dark = 1;
    }
    if (!dark) {
        for (int i = 0; i < getQuantityMarkerDancerOnPlusDancerEmpty(); i++) {
            PocketVec<short> position = views[i].getPosition();
            positions[i].x = position.x;
            positions[i].y = position.y;
        }
    }
    dark = 0;
    if (cursor->isCatchPokemon()) {
        CMenuPokemonCursor *c = cursor;
        Pokemon *p;
        if (c->pokemon.checkValid()) p = &c->pokemon;
        else p = 0;
        if (!p->isDarkPokemon()) dark = 1;
    }
    if (dark || (!cursor->isCatchPokemon() && stage->getVisitorPointer() == 0)) {
        positions[6].x = -1;
        positions[6].y = -1;
    }
}

void CMenuReliveHall::animationDataReset() {
    for (unsigned int i = 0; i < 9; i++) {
        SPokemonView &view = views[i];
        view.hidden = 0;
        view.ant.unk14 = 0;
        view.startAngle = view.unk4 = view.targetAngle;
        view.startFacing = view.facing = view.targetFacing;
    }
    makeCursorPositionTbl(cursorPositions);
    s16 *markers = (s16 *)markerOverride;
    for (unsigned int i = 0; i < 18; i++) markers[i] = -1;
    circleAlpha = 255;
    lineAlpha = 255;
    starAlpha = 255;
    effectAlpha = 255;
    markerAlpha = 255;
    memset(&hitEffect, 0, sizeof(hitEffect));
}

void _antZokuseiDraw(SPokemonView &view) {
    if (view.hidden == 0) {
        u16 sprite[2];
        PocketVec<short> first = view.getPosition();
        int x = (s32)(81.0f * (f32)sin(view.facing) + first.x);
        PocketVec<short> second = view.getPosition();
        int y = (s32)(81.0f * -(f32)cos(view.facing) + second.y);
        for (u16 i = 0; i < 2; i++) sprite[i] = zokuseiGetPokemonSpriteID(view.getPokemon()->getPokemonDataPtr(), i);
        if (sprite[0] == sprite[1]) {
            menuPtSpriteDraw(sprite[0], x - 36, y - 9);
            return;
        }
        u16 drawX = x - 36;
        menuPtSpriteDraw(sprite[0], drawX, y - 20);
        menuPtSpriteDraw(sprite[1], drawX, y + 2);
    }
}

static PocketVec<short> _cursorPositionTblAddPc[2] = {{336, 428}, {379, 428}};

int CMenuReliveHall::cursorMoveDirSearch(PocketVec<short> *positions, int direction, int range) {
    f32 nearest = 1000.0f;
    int result = -1;
    int current = cursor->index;
    PocketVec<short> origin = positions[current];
    PocketVec<short> candidates[11];
    memcpy(candidates, positions, 36);
    memcpy(candidates + 9, _cursorPositionTblAddPc, 8);
    int index = 0;
    do {
        if (current == 7 && index >= 9) break;
        if (index != cursor->index && candidates[index].x != -1) {
            long delta = degreeSubHalf(direction, xyxy2dirDegree(candidates[index], origin));
            if (delta > 0) {} else delta = -delta;
            if (delta <= range) {
                f32 distance = xyxy2distance(candidates[index], origin);
                if (nearest > distance) {
                    nearest = distance;
                    result = index;
                }
            }
        }
        index++;
    } while (index < 11);
    if (result >= 9) result = 7;
    return result;
}

void CMenuReliveHall::cursorMoveDir(int direction) {
    int result;
    int range = 15;
    for (;;) {
        result = cursorMoveDirSearch(cursorPositions, direction, range + 1);
        if (result != -1) break;
        range += 15;
        if (range > 60) break;
    }
    if (result != -1) {
        menuPtPlaySe(0x459);
        cursor->setPositionIndex(result);
        animationFlag = 6;
        memset(animationWork, 0, sizeof(animationWork));
    }
}

void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK *window, u32 id, int tempo, u8 alpha, bool clip) {
    f32 rate = relivehallTempoToRate(tempo);
    GSgfxColAu8 color = relivehallAisyou2ColorTbl[relivehallTempoToLevel(tempo)];
    color.a = alpha;
    if (clip) {
        tagSPRITE_WORK *sprite = menuPtSpriteWorkGetByItemID(window, id, 0);
        menuPtSpriteWorkSetWidthRateColor(window, id, 0, 1.0f, color);
        spriteSetScissor(window->layer, sprite->x, sprite->y, (s32)(sprite->width * rate), sprite->height);
        spriteSetEnv(window->layer);
        winSpriteDraw(window, sprite);
        spriteSetOffset(window->layer, 0, 0);
        spriteClearScissor(window->layer);
        spriteSetEnv(window->layer);
        return;
    }
    menuPtSpriteWorkSetWidthRateColor(window, id, 0, rate, color);
}

void CMenuReliveHall::editAfterDp0VisitorCheck() {
    Pokemon *pokemon;
    pokemon = stage->getVisitorPointer();
    if (pokemon == 0) return;
    f32 darkPoint = pokemon->getDarkPoint();
    if (!darkPoint && stage->getDancerQuantity() == 0) {
        msgctrlSetValue(0x32, pokemon->getNicknamePtr());
        infoMessageDisplay3Line(0xD15D);
    }
}

void CMenuReliveHall::loadDatas() {
    u32 group;
    group = floorGetCurrentGroupID();
    model1 = scriptModelOpen(0x18041000);
    model3 = GSresGetResource(group, model1);
    GSmodelStopTexAnimation(model3);
    model0 = scriptModelOpen(0x18041001);
    model2 = GSresGetResource(group, model0);
    GSmodelStopTexAnimation(model2);
    cameraPlayAnime(group, 0x18031800, 1, 0.0f);
    cameraSetType(4);
    GSmodelSetVisibility(model3, 1);
    GSmodelSetVisibility(model2, 1);
    localWindowCreateAll();
}

void CMenuReliveHall::drawAll() {
    SPokemonView *partnerView;
    long compatibility;
    Pokemon *partnerPokemon;
    unsigned int i;
    animationStateUpdate();
    drawMainBG();
    drawStageCursor();
    GSprimSetup2DRender(GSgfxLayerFindByID(7));
    GSprimSetLineWidth(1.0f);
    GSprimSetBlendMode(1);
    partnerView = 0;
    compatibility = -1;
    if (dancerPositionQuantityWithCatch() != 0 && getVisitorWithCatch() != 0 && stage->partner != -1) {
        partnerView = &views[stage->partner];
        partnerPokemon = getPokemonFromPositionWithCatch(stage->partner);
        compatibility = pokemonToAisyou(getStatusDisplayVisitorGetPointer(), partnerPokemon);
    }
    if (compatibility != -1) drawVisitorStarLight(compatibility, partnerView);
    drawDancerStarLight();
    drawMarkers(true);
    for (i = 0; i < 3; i++) circles[i].draw();
    if (compatibility != -1) drawVsitorLine(compatibility, partnerView);
    drawStatusPanel();
    draw9StageInfo();
    drawMarkers(false);
    drawVisitorHitEffect();
    drawDancerHitEffect();
    drawStagePokemon();
    alphaFadeDraw();
    cursor->draw();
    localWindowDrawAll();
    CAnt::systemUpdate(true);
    menuDrawReliveUpdate();
    infoWindow.draw();
    baseInfoWindow.draw();
}

void CMenuReliveHall::drawStagePokemon() {
    int quantity;
    int index;
    SPokemonView *view;
    quantity = stage->getDancerQuantity();
    for (index = 0; index < quantity; index++) {
        view = &views[index];
        _antZokuseiDraw(*view);
        _antDraw(*view);
    }
    _antDraw(views[6], circlePosition);
}


bool CMenuReliveHall::animationProcessButtonInterrupt() {
    if (animationState != 0) {
        animationFlag = 0;
        memset(animationWork, 0, 0x40);
        animationStateUpdate();
    }
    return false;
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
