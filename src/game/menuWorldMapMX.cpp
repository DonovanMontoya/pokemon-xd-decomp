#include <game/menuWorldMapMXLayout.hpp>

extern "C" {
void menuCursorNormal(tagWINDOW_WORK *, s32);
void menuClose(s32);
void menuCloseSync(s32, s32);
void menuScriptSetOpenWorldMapFlag(s32);
void msgctrlSetValue(s32, u32);
void GSfloorPop(void);
s32 windowGetActiveID(void);
s32 menuOpenCustom(s32, s32, ...);
void *floorDataBiosGetPtr(s32);
s32 floorDataBiosGetFileGroupID(void *);
void GSfsysPreRead(s32);
void menuButtonNormal(tagWINDOW_WORK *);
void windowDrawSprite(s32, s32, tagWINDOW_WORK *, u16, s32, s32);
u32 charNameBiosGetNameID(u16);
void GSmsgPrint2(s32, s32, s32, u32, s32);
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
    u32 unk10;
    u8 pad14[0x1C - 0x14];
    u32 floorId;
    u32 msgId;
};

struct GSvec {
    f32 x;
    f32 y;
    f32 z;
};

struct WorldMapCamera {
    s32 cur_;
    s32 prev_;
    f32 blendT;
    f32 accel;
    f32 speed;
    f32 unk14;
    GSvec cur;
    f32 c24;
    f32 c28;
    f32 c2C;
    f32 c30;
    f32 c34;
    f32 c38;
    f32 c3C;
    GSvec next;
    f32 n4C;
    f32 n50;
    f32 n54;
    f32 n58;
    f32 n5C;
    f32 n60;
    f32 n64;
};

struct WorldMapCameraData {
    GSvec pos;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
};

struct WorldMapIconData {
    u8 pad0[4];
    s16 motion;
    u8 pad6[2];
    GSvec pos;
    u8 pad14[0x2C - 0x14];
};

struct WorldMapMsgData {
    s32 flagIndex;
    s32 msg[18];
};

struct WorldMapFlagEtc {
    u8 pad0[8];
    u32 value;
    u8 padC[0x20 - 0xC];
};

struct GSgfxLayerID {
    s32 id;
};

void *operator new(unsigned long);
void *operator new[](unsigned long);
void operator delete(void *);
void operator delete[](void *);

class WorldMapModel {
public:
    u32 unk0;
    ~WorldMapModel() {
        if (unk0 != 0) {
            releaseOffscreenData();
        }
    }
    void releaseOffscreenData();
    void SetLayerID(u32, long, GSgfxLayerID *);
    u8 CheckMotion(u32);
    void StopMotion(u32);
    void SetMotion(u32, short, f32, bool);
};

struct WorldMapState {
    u8 flag;
    u8 pad1[0x2F];
    s32 cursor;
    s32 floorId;
};

struct WorldMapIconSubWork {
    f32 a;
    f32 b;
    WorldMapIconSubWork(f32 x = 0.0f, f32 y = 0.0f) {
        a = x;
        b = y;
    }
};

struct WorldMapIconWork {
    u8 pad0[0x14];
    s8 slots[8];
    u8 pad1C[0xC];
    WorldMapIconSubWork *subs;
    WorldMapIconWork();
    ~WorldMapIconWork();
};

class WorldMap : public WorldMapModel {
public:
    s32 unk4;
    WorldMapState *unk8;
    WorldMapIconData *icons;
    u32 cursorModel;
    s16 cursorState;
    u8 pad16[2];
    s32 cursorIndex;
    u8 flag1C;
    u8 pad1D[3];
    GSvec cursorBlend;
    GSvec cursorPos;
    f32 cursorT;
    f32 cursorBob;
    f32 cursorTime;
    WorldMapCamera *camera;

    WorldMap();
    ~WorldMap();
    void Init();
    void Release();
    void InitModel2D(f32);
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
    f32 GetAngle(long);
    s16 GetStartIconAnimIndex(u32);
    u8 IsBlending();
    void SetCameraSpeed(f32);
    void SetCameraNextWork(GSvec *, f32, f32, f32, f32);
    void SetCameraWork(GSvec *, f32, f32, f32, f32);
    long Blendf(f32 *, f32, f32, f32);
    void GetCameraData(long, GSvec *, f32 *, f32 *, f32 *, f32 *);
    long SearchFloorID(u16);
    long SearchDataFloorID(unsigned int);
    long GetInfoMsgID(long);
    long GetInfoLevel();
    void CheckCursorAnime();
    void MainControl(long);
    void PreRead(long);
    void ControlCamera(long);
    void TargetDebug(long);
    void SetCamera();
    s8 GetPadIndex3(f32, long, f32);
    void SetCursorPosition(long, bool);
    void InitCursor(long, short);
    void SelectIcon(long);
    void SetSnap(long, tagWINDOW_WORK *, tagSPRITE_WORK *);
    void SetInfo(long, tagWINDOW_WORK *, tagSPRITE_WORK *);
    void CalcModel2D(f32, bool);
    void ControlCursor(long);
    void CheckIconAnime(long);
    void ControlPad(tagWINDOW_WORK *);
    void SetIconMotion(long, u32, short, f32, bool);
};

extern "C" {
extern s32 *worldmapXD_data_number;
extern s32 *worldmapXD_msgdata_number;
extern s32 *worldmap_cameradata_number;
extern WorldMapMsgData *worldmapXD_msgdata;
extern WorldMapCameraData *worldmap_cameradata;
extern WorldMapFlagEtc *flag_etc;
extern f32 _v0;
extern u8 _cameraDebug;
f32 GSlerpGetLinearInterpolationFloat(f32, f32, f32);
struct GSvec;
void PSVECAdd(const GSvec *, const GSvec *, GSvec *);
}
static f32 _waittime = 0.7f;
static f32 _a0 = 0.0001f;
extern WorldMapData *worldmapXD_data;

static WorldMap *pWorldmap;
static u8 _DebugControl;
static s16 _cursor_index[30];

WorldMapIconWork::WorldMapIconWork() {
    long i;
    subs = new WorldMapIconSubWork[*worldmapXD_data_number];
    for (i = 0; i < 8; i++) {
        slots[i] = -1;
    }
}

WorldMapIconWork::~WorldMapIconWork() {
    delete[] subs;
}

WorldMap::~WorldMap() {
    Release();
}

void WorldMap::InitModel2D(f32 t) {
    long i;
    CalcModel2D(t, true);
    for (i = 0; i < GetDataNum(); i++) {
    }
}

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

f32 WorldMap::GetAngle(long index) {
    return 0.3926991f * (f32)index;
}

s16 WorldMap::GetStartIconAnimIndex(u32 kind) {
    switch (kind) {
    case 0:
        return 0;
    case 1:
        return 6;
    case 2:
        return 1;
    default:
        return 0;
    }
}

u8 WorldMap::IsBlending() {
    WorldMapCamera *cam = camera;
    u8 result = 0;
    if (cam->blendT >= 1.0f) {
        result = 1;
    }
    return result;
}

void WorldMap::SetCameraSpeed(f32) {
    camera->blendT = 0.0f;
    camera->speed = _v0;
    camera->accel = _a0;
    camera->unk14 = 0.0f;
}

void WorldMap::SetCameraNextWork(GSvec *pos, f32 a, f32 b, f32 c, f32 d) {
    WorldMapCamera *cam = camera;
    if (pos != 0) {
        cam->next.x = pos->x;
        cam->next.y = pos->y;
        cam->next.z = pos->z;
    }
    if (a) {
        cam->n58 = a;
    }
    cam->n5C = b;
    cam->n60 = c;
    cam->n64 = d;
    cam->n4C = 0.0f;
    cam->n50 = 1.0f;
    cam->n54 = 0.0f;
}

void WorldMap::SetCameraWork(GSvec *pos, f32 a, f32 b, f32 c, f32 d) {
    WorldMapCamera *cam = camera;
    if (pos != 0) {
        cam->cur.x = pos->x;
        cam->cur.y = pos->y;
        cam->cur.z = pos->z;
    }
    if (a) {
        cam->c30 = a;
    }
    cam->c34 = b;
    cam->c38 = c;
    cam->c3C = d;
    cam->c24 = 0.0f;
    cam->c28 = 1.0f;
    cam->c2C = 0.0f;
}

long WorldMap::Blendf(f32 *out, f32 from, f32 to, f32 t) {
    *out = GSlerpGetLinearInterpolationFloat(from, to, t);
    return 1;
}

static inline void setVec(GSvec *v, f32 x, f32 y, f32 z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

void WorldMap::GetCameraData(long index, GSvec *pos, f32 *a, f32 *b, f32 *c, f32 *d) {
    if ((u32)index < (u32)*worldmap_cameradata_number) {
        WorldMapCameraData *data = &worldmap_cameradata[index];
        setVec(pos, data->pos.x, data->pos.y, data->pos.z);
        *a = data->a;
        *b = data->b;
        *c = data->c;
        *d = data->d;
    }
}

long WorldMap::SearchFloorID(u16 id) {
    WorldMapData *data = SearchData(id);
    u32 flag = GSflagGet(data->flag);
    if (data->flag == 0 || flag != 0) {
        return data->floorId;
    }
    return SearchData(6)->floorId;
}

long WorldMap::SearchDataFloorID(unsigned int floorId) {
    long off;
    long i;
    long found;
    found = 0;
    i = 0;
    off = 0;
    while (i < GetDataNum()) {
        WorldMapData *data = SearchData(i);
        u32 flag = GSflagGet(data->flag);
        if (data->flag == 0 || flag != 0) {
            found++;
            if (floorId == *(u32 *)((u8 *)worldmapXD_data + off + 0x1C)) {
                return found - 1;
            }
        }
        off += 0x24;
        i++;
    }
    return 0;
}

long WorldMap::GetInfoLevel() {
    WorldMapMsgData *msg = worldmapXD_msgdata;
    long level = 0;
    s16 i = 0;
    while (i < *worldmapXD_msgdata_number) {
        if (msg->flagIndex != 0) {
            u32 need = flag_etc[msg->flagIndex].value;
            if (GSflagGet((void *)0x3C4) >= need) {
                level++;
            }
        }
        msg = (WorldMapMsgData *)((u8 *)msg + 0x4C);
        i++;
    }
    return level - 1;
}

long WorldMap::GetInfoMsgID(long index) {
    s16 cursor = _cursor_index[index];
    if (unk8->flag != 0) {
        return SearchData(cursor)->msgId;
    }
    return worldmapXD_msgdata[GetInfoLevel()].msg[cursor];
}

void WorldMap::CheckCursorAnime() {
    u32 model = cursorModel;
    switch (cursorState) {
    case 2:
        if (!CheckMotion(model)) {
            StopMotion(model);
        }
        break;
    }
}

void WorldMap::SetIconMotion(long index, u32 model, short motion, f32 rate, bool loop) {
    icons[index].motion = motion;
    SetMotion(model, motion, rate, loop);
}

void WorldMap::MainControl(long arg) {
    ControlCamera(arg);
    TargetDebug(arg);
    SetCamera();
    CalcModel2D(camera->c3C, false);
    ControlCursor(arg);
    CheckIconAnime(arg);
    CheckCursorAnime();
}

void WorldMap::Cursor(tagWINDOW_WORK *win) {
    if (_DebugControl) {
        menuCursorNormal(win, 1);
        return;
    }
    if (unk8->flag == 0) {
        ControlPad(win);
    }
}

void WorldMap::PreRead(long index) {
    WorldMapData *data = SearchData(_cursor_index[index]);
    WorldMapState *state = unk8;
    void *ptr;
    if (state->flag != 0) {
        ptr = floorDataBiosGetPtr(state->floorId);
    } else if (data != 0) {
        ptr = floorDataBiosGetPtr(data->floorId);
    } else {
        ptr = floorDataBiosGetPtr(state->floorId);
    }
    GSfsysPreRead(floorDataBiosGetFileGroupID(ptr));
}

void WorldMap::MainSub2() {
    menuOpenCustom(0x54, windowGetActiveID(), (u8 *)unk8 + 0x2C, 0, 1, 0);
    if (pWorldmap != 0) {
        PreRead(0);
        menuClose(0x54);
        menuCloseSync(0x54, 1);
        menuScriptSetOpenWorldMapFlag(0);
        msgctrlSetValue(0x59, 0x1772);
        GSfloorPop();
    }
}

void WorldMap::SetSnap(long index, tagWINDOW_WORK *win, tagSPRITE_WORK *) {
    WorldMapData *data = SearchData(_cursor_index[index]);
    long state = GetFlagData(_cursor_index[index]);
    switch (state) {
    case 0:
        break;
    case 1:
        windowDrawSprite(0, 0, 0, 0x33F, 0, win->layer);
        return;
    case 2:
        windowDrawSprite(0, 0, 0, (u16)data->unk10, 0, win->layer);
        return;
    }
}

void WorldMap::SetInfo(long index, tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    SearchData(_cursor_index[index]);
    if (unk8->flag != 0) {
        u32 name = charNameBiosGetNameID(GetNpcID(index));
        if (name == 0) {
            name = 0x1772;
        }
        msgctrlSetValue(0x59, name);
    }
    GSmsgPrint2(win->layer, 0, -4, sprite->color.channels.alpha | ~0xFF, GetInfoMsgID(index));
}

void WorldMap::TargetDebug(long index) {
    WorldMapCamera *cam = camera;
    s16 cursor = _cursor_index[index];
    cam->prev_ = cam->cur_;
    camera->cur_ = cursor;
    if (_cameraDebug) {
        cam = camera;
        if (cam->prev_ != cam->cur_) {
            SetCameraNextWork(&icons[cursor].pos, 51.75f, 35.31f, 0.0f, 50.0f);
            SetCameraSpeed(1.0f);
        }
    }
}

void WorldMap::ControlCamera(long) {
    f32 dt = timeGetLastFrameSec();
    WorldMapCamera *cam;
    f32 *cur;
    camera->unk14 = camera->unk14 + dt;
    camera->speed = camera->accel * dt + camera->speed;
    if (camera->speed <= 0.01f) {
        camera->speed = 0.01f;
    }
    camera->blendT = camera->blendT + camera->speed;
    if (camera->blendT > 1.0f) {
        camera->blendT = 1.0f;
    }
    cam = camera;
    cur = &cam->cur.x;
    Blendf(cur, *cur, cam->next.x, cam->blendT);
    Blendf(cur + 1, cur[1], cam->next.y, camera->blendT);
    Blendf(cur + 2, cur[2], cam->next.z, camera->blendT);
    Blendf(cur + 6, cur[6], cam->n58, camera->blendT);
    Blendf(cur + 7, cur[7], cam->n5C, camera->blendT);
    Blendf(cur + 9, cur[9], cam->n64, camera->blendT);
}

s8 WorldMap::GetPadIndex3(f32 angle, long index, f32 range) {
    u8 hit = 0;
    s8 result = -1;
    f32 center = 3.1415927f * (f32)index * 0.25f;
    if ((f32)index == 0.0f) {
        if (angle >= 6.2831855f - range || angle < range) {
            hit = 1;
        }
    } else if (angle >= center - range && angle < center + range) {
        hit = 1;
    }
    if (hit) {
        result = index;
    }
    return result;
}

void WorldMap::SetCursorPosition(long index, bool reset) {
    WorldMapIconData *icon;
    SearchData(_cursor_index[index]);
    icon = (WorldMapIconData *)((u8 *)icons + _cursor_index[index] * 0x2C);
    cursorPos.x = icon->pos.x;
    cursorPos.y = icon->pos.y;
    cursorPos.z = icon->pos.z;
    cursorIndex = index;
    if (reset) {
        flag1C = 1;
        cursorT = 0.0f;
    }
}

void WorldMap::InitCursor(long index, short state) {
    GSgfxLayerID layer = { 2 };
    cursorTime = 0.0f;
    cursorBob = 0.0f;
    cursorModel = 0x18531013;
    cursorState = state;
    cursorT = 0.0f;
    flag1C = 1;
    switch (state) {
    case 2:
        SetMotion(cursorModel, cursorState, 0.0f, 0);
        break;
    default:
        SetMotion(cursorModel, cursorState, 0.0f, 1);
        break;
    }
    SetLayerID(cursorModel, 1, &layer);
    SetCursorPosition(index, false);
    cursorBlend.x = cursorPos.x;
    cursorBlend.y = cursorPos.y;
    cursorBlend.z = cursorPos.z;
}

void WorldMap::SelectIcon(long index) {
    f32 b;
    f32 c;
    f32 d;
    f32 a;
    GSvec out;
    GSvec pos;
    s16 cursor = _cursor_index[index];
    WorldMapIconData *icon = (WorldMapIconData *)((u8 *)icons + cursor * 0x2C);
    GetCameraData(SearchData(cursor)->unk0, &pos, &a, &b, &c, &d);
    PSVECAdd(&icon->pos, &pos, &out);
    SetCameraNextWork(&out, a, b, c, d);
    SetCameraSpeed(1.0f);
    {
        u32 model = *(u32 *)((u8 *)icons + cursor * 0x2C);
        if (GetFlagData(cursor) == 1) {
            SetIconMotion(cursor, model, 9, 0.0f, false);
        } else {
            SetIconMotion(cursor, model, 5, 0.0f, false);
        }
    }
    InitCursor(index, 2);
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

extern "C" void menuWorldMapMXInit(void) {
    pWorldmap = new WorldMap;
    pWorldmap->Init();
}
