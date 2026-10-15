#ifndef GAME_MENURELIVEHALL_LAYOUT_HPP
#define GAME_MENURELIVEHALL_LAYOUT_HPP
#include <dolphin/types.h>

// Partial views of the pocket-menu helper types. Every named member is tied to an
// original load/store width.
struct MenuPtWorkSound {
    u32 bgm;
    u32 env;
    u8 bgmVolume;
    u8 envVolume;
};

template <class T>
struct PocketVec {
    T x;
    T y;
    static const PocketVec zero;
};

class DarkPokemon;

class Pokemon {
public:
    u8 reserved[0xC4];
    bool checkValid() const;
    void setDarkPoint(f32);
    bool isDarkPokemon() const;
    u8 getLevel() const;
    f32 getDarkPoint() const;
    u16 *getNicknamePtr();
    DarkPokemon *getDarkPokemon();
    void *getPokemonDataPtr() const;
};

enum darkPokemonStatus {
    DARK_POKEMON_STATUS_0,
    DARK_POKEMON_STATUS_1,
    DARK_POKEMON_STATUS_2,
    DARK_POKEMON_STATUS_3
};

class DarkPokemon {
public:
    u16 getPokemonID() const;
    void setStatus(darkPokemonStatus);
    void setSnatchIndex(u8);
};

class CAnt {
public:
    static void systemUpdate(bool);
    u32 unk0;
    u32 unk4;
    u32 unk8;
    f32 unkC;
    u8 unk10;
    u32 unk14;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    u32 unk20;
    u32 unk24;
    u32 unk28;
    f32 unk2C;
    u32 unk30;
    void init();
    void initByPokemonAndSetColorAnimationInAny(Pokemon *);
    void setAnimation(long);
    void drawAndUpdate(PocketVec<short>);
};

class CMenuPokemonCursor {
public:
    u8 unk0;
    s32 unk4;
    f32 unk8;
    s32 index;
    s32 prevIndex;
    s16 x;
    s16 y;
    PocketVec<short> *table;
    u8 reserved1C[4];
    Pokemon pokemon;
    CAnt ant;
    CAnt beforeAnt;
    u8 unk14C;
    u8 reserved14D[7];
    static PocketVec<short> defaultPositionTbl;
    void draw();
    bool isCatchPokemon();
    void deletePokemon();
    void setBeforAnt(CAnt &);
    void setPokemon(Pokemon *);
    void setPositionTableDummy();
    void setPositionIndex(long);
    void setPositionTable(PocketVec<short> *, long);
    void setAnimationOff();
    void init();
};

class CState {
public:
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 frames;
    f32 time;
    f32 lastFrame;
    u8 saved[0x40];
    u8 saved2[0x40];
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    u8 reservedA4[4];
    void update();
    void addTime();
    void init();
};

class CMenuGlobalState {
public:
    u8 reserved0[0xC];
    CMenuPokemonCursor cursor;
    CState state;
    void init();
};

struct tagSPRITE_WORK {
    tagSPRITE_WORK *next;
    u8 type;
    u8 flags;
    s16 id;
    u32 texture;
    u8 sequence[0x3C];
    u32 callback;
    u32 message;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 resource;
    s16 sourceX;
    s16 sourceY;
    s16 sourceWidth;
    s16 sourceHeight;
    union {
        u32 value;
        struct {
            u8 red;
            u8 green;
            u8 blue;
            u8 alpha;
        } channels;
    } color;
    f32 scaleX;
    f32 scaleY;
    u8 reserved70[4];
    u8 drawType;
    u8 blendType;
    u8 mode;
    u8 reserved77;
};

struct tagWINDOW_WORK {
    u8 flags;
    s8 phase;
    s8 step;
    u8 reserved3;
    s32 menu;
    u8 reserved8;
    s8 priority;
    u8 closing;
    u8 port;
    tagWINDOW_WORK *parent;
    tagWINDOW_WORK *next;
    tagWINDOW_WORK *previous;
    u8 inactive;
    u8 itemCount;
    u8 kind;
    u8 openFlags;
    s32 layer;
    u8 drawKind;
    u8 reserved21[3];
    tagSPRITE_WORK *items;
    tagSPRITE_WORK *cursor;
    u8 reserved2C[0x3C];
    u32 parameters[8];
    s32 value;
    s16 x;
    s16 y;
    s16 frame;
    u8 reserved92;
    u8 alpha;
    f32 scaleX;
    f32 scaleY;
    s16 first;
    s16 selected;
    u8 reservedA0[4];
    u8 finished;
    u8 cancelled;
    u8 reservedA6[2];
    u8 freeWork[0x10];
    void *allocation;
};

struct MENU_ITEM_dd_ {
    u8 flags;
    u8 typeFlags;
    u8 alpha;
    u8 reserved3;
    s16 spriteID;
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 cursorSpriteID;
    u32 message;
    u32 callback;
    s16 nextItem;
    u8 reserved1A[2];
};

struct MENU_SPRITE_dd_;

struct MenuSpriteValue {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    u32 resource;
};

struct GSgfxColAu8 {
    u8 r, g, b, a;
};

struct MetaKeyInfo {
    u16 on;
    u16 off;
    u16 trigger;
    u16 repeat;
    u16 released;
    u8 reserved[0x10];
};

class CMetaMenu;

class CInfoWindow {
public:
    s32 unk0;
    s32 unk4;
    u8 open_;
    bool wait;
    u8 reservedA[2];
    u32 msg;
    u32 keys[4][2];
    u16 key;
    u8 reserved32[2];
    void exec(CMetaMenu &, u32, bool);
    void draw();
    void setMsgCtrlValue(u32, u32);
    bool isMsgEnd();
    void open(u32, bool);
    void close();
    void initTutorialTalk();
    void init(long, u32);
};

class CMetaMenuBase;
class CMetaMenuBase {
public:
    s32 fadeTime;
    s32 fadeState;
    u8 reserved8[4];
    u32 seId;
    u8 reserved10[0xC];
    long windows[64];
    void (*windowFuncs[64])(CMetaMenu *, long);
    long *windowTable;
    MetaKeyInfo keyInfo;
    u8 reserved23A[2];
    s32 repeatCount;
    u16 lastKey;
    u8 tutorialActive;
    u8 reserved243;
    CInfoWindow baseInfoWindow;
    u8 reserved278[0x320 - 0x278];
    u64 time;
    u8 reserved328[8];
};

class CMetaMenu : public CMetaMenuBase {
public:
    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    virtual void tutorialExitKick();
    void waitAtTime(f32);
    long calcAnimationTimeRate0toX(f32, long);
    f32 calcAnimationTimeRate0to1to0(f32);
    f32 calcAnimationTimeRate0to1(f32);
    void drawHook();
    void vsyncUpdate();
    void systemFadeWaitToEnd();
    void systemFadeOutSetAndWait(f32);
    void systemFadeOutKick(f32);
    void systemFadeInKick();
    void systemFadeOutKeepAfterFloorPush();
    void alphaFadeDraw();
    u8 getAlphaFadeAlpha() const;
    long actionMenu(u32 *, int, long, long);
    void localWindowRemove(long);
    void localWindowDrawAll(long, long);
    void localWindowDrawAll();
    void localWindowEntry(long, long, void (*)(CMetaMenu *, long));
    int localWindowSearch(long);
    void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(long *);
    static CMetaMenu *pCurrentMenu;
    void alphaFadeOutAndWait();
    void alphaFadeUpdate();
    void alphaFadeOutKick();
    void alphaFadeInKick();
    MetaKeyInfo *getKeyInfo();
    void aButtonWait();
    u16 tutorialManage();
    void tutorialManageUpdate();
};

void menuPtPlaySe(u32);
void menuPtWindowWorkDraw(long);
void menuPtWindowWorkDraw(tagWINDOW_WORK *);
void menuPtWindowWorkDrawPrime(tagWINDOW_WORK *);
void menuPtMenuLoad(long);
void menuPtSpriteDrawCenterColor(u16, long, long, u32);
void menuPtSpriteDrawColor(u16, long, long, long, long, u32);
void menuPtSpriteDrawColor(u16, long, long, u32);
void menuPtSpriteDraw(u16, long, long);
void menuPtItemDrawOffsetXWColor(MENU_ITEM_dd_ *, long, long, u32);
void menuPtItemDrawOffset(MENU_ITEM_dd_ *, long, long);
void menuPtItemDrawAlpha(MENU_ITEM_dd_ *, u8);
void menuPtSpriteWorkSetWidthRateColor(tagWINDOW_WORK *, u32, long, f32, GSgfxColAu8);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK *, tagSPRITE_WORK *, bool);
void menuPtSpriteWorkSetSw(tagWINDOW_WORK *, u32, long, bool);
void menuPtSpriteWorkSetSpriteId(tagSPRITE_WORK *, u32);
void menuPtSpriteWorkSetMenuSprite(tagSPRITE_WORK *, MENU_SPRITE_dd_ *);
void menuPtSpriteWorkSetMenuItem(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);
tagSPRITE_WORK *menuPtGetSpriteWorkByHookFunction(tagWINDOW_WORK *, void *, u32, long);
MENU_ITEM_dd_ *menuPtItemGetBySpriteWork(tagWINDOW_WORK *, tagSPRITE_WORK *);
long menuPtSpriteWorkGetIndexFromId(tagWINDOW_WORK *, tagSPRITE_WORK *, u32);
tagSPRITE_WORK *menuPtSpriteWorkGetByItemID(tagWINDOW_WORK *, u32, long);
tagSPRITE_WORK *menuPtSpriteWorkGetByItemID(long, u32, long);
void menuPtSpriteWorkSetMsgId(long, u32, long, u32);
MENU_ITEM_dd_ *menuPtItemGetByMenuIdAndItemId(long, u32, long);
u32 GSgfxColAu8To32(GSgfxColAu8);

#endif
