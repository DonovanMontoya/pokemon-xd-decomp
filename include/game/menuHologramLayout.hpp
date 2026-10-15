#ifndef GAME_MENUHOLOGRAM_LAYOUT_HPP
#define GAME_MENUHOLOGRAM_LAYOUT_HPP
#include <dolphin/types.h>

// Partial views of the relive-hall helper types used by the hologram menu.
class Pokemon {
public:
    u8 data[0xC4];
    u16 getPokemonDataId() const;
    bool isDarkPokemon() const;
    u16 *getNicknamePtr();
};
class CMenuGlobalState {
public:
    s32 reserved0;
    s32 previous;
    s32 current;
};

struct GSgfxColAu8 {
    u32 rgba;
};

class CReliveStage {
public:
    bool isReliveReady();
    s32 getState();
    s32 getTempo();
    Pokemon *getVisitorPointer();
    Pokemon *getDancerPointer(long);
    s32 getDancerQuantity();
    void pickupVisitor(Pokemon &);
};

class PCBOX {
public:
    static PCBOX *getPointer();
    void addPokemonLastWatchBox(Pokemon *);
    bool isPokemonFull();
};

class CReliveHall {
public:
    static CReliveHall *getPointer();
    CReliveStage *getStage(long);
    bool isReliveReadyPokemonExist();
};

struct GStexture;
enum GSgfxLayerID { GSGFX_LAYER_0 };
enum GSgfxLayerOffset { GSGFX_OFFSET_0 };
enum GSgfxLayerType { GSGFX_TYPE_0 };

class GSgfxLayer {
public:
    void SetClearFlags(bool, bool, bool);
    void SetTextureCopy(GStexture *, bool, unsigned char *);
};

class GSgfxLayerConfig {
public:
    static void Remove(GSgfxLayerID);
    static long Add(char *, unsigned long, unsigned long, unsigned long, GSgfxLayerType, bool, bool, bool, GSgfxLayerID, GSgfxLayerOffset);
    static void Move(GSgfxLayerID, GSgfxLayerID, GSgfxLayerOffset);
};

class CMetaMenu;

class CInfoWindow {
public:
    u8 reserved0[0x34];
    void exec(CMetaMenu &, u32, bool);
    void draw();
    void open(u32, bool);
    void close();
    void init(long, u32);
    void setMsgCtrlValue(u32, u32);
};

class CState {
public:
    s32 current;
    s32 next;
    u8 reserved8[0x10];
    u8 work[0x40];
    u8 reserved58[0x50];
    void init();
    void update();
    void change(s32);
};

struct MetaKeyInfo {
    u16 on, off, trigger, repeat, released;
};

class CMetaMenu {
public:
    s32 fadeTime;
    s32 fadeState;
    u8 sound[0x14];
    long windows[64];
    void *windowFuncs[64];
    long *windowTable;
    u8 keyInfo[0x1A];
    u8 reserved23A[2];
    s32 repeatCount;
    u16 lastKey;
    u8 tutorialActive;
    u8 reserved243[0x278 - 0x243];
    CState state;
    u32 time0;
    u32 time1;
    u8 reserved328[4];
    u8 unk32C;
    u8 reserved32D;
    u16 unk32E;
    static long defautlLocalWindowOpenTable[];
    virtual void drawAll() = 0;
    virtual bool isAnimationStateNone();
    virtual void updateAll();
    virtual void tutorialExitKick();
    MetaKeyInfo *getKeyInfo();
    void aButtonWait();
    f32 calcAnimationTimeRate0to1(f32);
    void localWindowDrawAll();
    void waitAtTime(f32);
    void systemFadeWaitToEnd();
    void systemFadeOutSetAndWait(f32);
    static void systemFadeInKick();
    static void systemFadeOutKeepAfterFloorPush();
    int actionMenu(u32 *, int, long, long);
    static void localWindowDeleteAll();
    void localWindowCreateAll();
    void localWindowSetTable(long *);
};

struct ModelSlot {
    s32 script;
    void *model;
    u32 sequence;
    s32 getAnimIndex();
    void setAnim(s32);
};

namespace {

class CMenuHologram : public CMetaMenu {
public:
    u8 reserved334[4];
    s32 stageIndex;
    s32 stageIndex2;
    CReliveStage *stage;
    u8 unk344;
    u8 reserved345[3];
    s32 lights[8];
    s32 lightCount;
    GStexture *offscreenTexture;
    u32 resGroup;
    u8 stageLoaded;
    u8 unk375;
    u8 reserved376[2];
    void *stageModel;
    u32 unk37C;
    u32 unk380;
    u32 unk384;
    ModelSlot slots[7];
    CInfoWindow infoWindow;
    CMenuGlobalState *globalState;
    u8 reserved414[4];

    virtual void drawAll();
    void stateReliveCeremony();
    void stateMainProc();
    void renderOffscreenData();
    void setStage(int);
    void setStageToReliveReady();
    void moveStageWait(int);
    void reloadDatas(bool);
    void unloadDatas();
    GSgfxColAu8 pokemonToAisyouColor(Pokemon *, Pokemon *);
    static s32 model_z_layer;
    void releaseOffscreenData();
    void initializeOffscreenData();
    void bgmStop();
    void bgmKick();
    void stageAllModelLoad();
    void stageAllModelUnLoad();
    void modelVisitorSetYPosition(long);
    ModelSlot *modelPokemonSetScale(long);
    ModelSlot *modelPokemonLoad(long);
    int actionYesNo(u32, bool);
    void init(CMenuGlobalState &);
    void main(CMenuGlobalState &);
    void loop();
};

}

#endif
