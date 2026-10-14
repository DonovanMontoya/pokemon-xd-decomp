#include <game/menuWorldMapMXLayout.hpp>

extern "C" {
void menuButtonNormal(tagWINDOW_WORK *);
u8 menuScriptGetOpenWorldMapFlag(void);
f32 timeGetLastFrameSec(void);
void *GSresGetResourceAllGroup(u32);
void GSflagSet(void *, s32);
u32 GSflagGet(void *);
}

struct WorldMapData {
    u32 unk0;
    void *flag;
    u32 pad8;
    u32 modelID;
    u8 pad10[0x24 - 0x10];
};

struct WorldMapState {
    u8 flag;
    u8 pad1[0x2F];
    s32 cursor;
};

class WorldMap {
public:
    s32 unk0;
    s32 unk4;
    WorldMapState *unk8;
    u8 pad0C[0x1C - 0xC];
    u8 flag1C;

    WorldMap();
    ~WorldMap();
    void Ctrl(tagWINDOW_WORK *);
    void Button(tagWINDOW_WORK *);
    void Cursor(tagWINDOW_WORK *);
    void CallBackFunc(tagWINDOW_WORK *, tagSPRITE_WORK *);
    long GetNowCursor(tagWINDOW_WORK *);
    void Main();
    void MainSub();
    void MainSub2();
    u8 IsFloorPush();
    f32 GetLastTime();
    void InitRenderModule();
    long GetDataNum();
    WorldMapData *SearchData(long);
    long GetModelID(long);
    void *GetModelPointer(long);
    void SetFlagData(long);
    long GetFlagData(long);
    u16 GetNpcID(long);
};

extern "C" {
extern s32 *worldmapXD_data_number;
}
extern WorldMapData *worldmapXD_data;

static WorldMap *pWorldmap;
static u8 _DebugControl;
static s16 _cursor_index[30];

WorldMap::WorldMap() {
    unk0 = 0;
    unk8 = 0;
    unk4 = 0;
}

void WorldMap::Button(tagWINDOW_WORK *win) {
    if (flag1C != 1) {
        menuButtonNormal(win);
    }
}

long WorldMap::GetNowCursor(tagWINDOW_WORK *win) {
    if (_DebugControl) {
        return win->pos.selected;
    }
    return unk8->cursor;
}

void WorldMap::Main() {
    if (unk8->flag != 0) {
        MainSub2();
    } else {
        MainSub();
    }
}

u8 WorldMap::IsFloorPush() {
    return menuScriptGetOpenWorldMapFlag();
}

f32 WorldMap::GetLastTime() {
    return timeGetLastFrameSec();
}

void WorldMap::InitRenderModule() {
}

long WorldMap::GetDataNum() {
    return *worldmapXD_data_number;
}

WorldMapData *WorldMap::SearchData(long index) {
    if (index >= GetDataNum()) {
        return 0;
    }
    return &worldmapXD_data[index];
}

long WorldMap::GetModelID(long index) {
    return SearchData(index)->modelID;
}

void *WorldMap::GetModelPointer(long index) {
    return GSresGetResourceAllGroup(GetModelID(index));
}

u16 WorldMap::GetNpcID(long index) {
    return *(u16 *)((u8 *)SearchData(_cursor_index[index]) + 2);
}

void WorldMap::SetFlagData(long index) {
    void *flag = SearchData(index)->flag;
    if (flag != 0) {
        GSflagSet(flag, 2);
    }
}

long WorldMap::GetFlagData(long index) {
    void *flag = SearchData(index)->flag;
    if (flag == 0) {
        return 2;
    }
    return GSflagGet(flag);
}

extern "C" s32 menuWorldMapMXCtrl(tagWINDOW_WORK *win) {
    if (pWorldmap != 0) {
        pWorldmap->Ctrl(win);
    }
    return 0;
}

extern "C" void menuWorldMapMXExit(void) {
    delete pWorldmap;
    pWorldmap = 0;
}

extern "C" void menuWorldMapMXMain(void) {
    pWorldmap->Main();
}

extern "C" void menuWorldMapButton(tagWINDOW_WORK *win) {
    if (pWorldmap != 0) {
        pWorldmap->Button(win);
    }
}

extern "C" void menuWorldMapCursor(tagWINDOW_WORK *win) {
    if (pWorldmap != 0) {
        pWorldmap->Cursor(win);
    }
}

extern "C" s32 menuWorldMapMX(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    if (pWorldmap != 0) {
        pWorldmap->CallBackFunc(win, sprite);
    }
    return 0;
}
