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
void cameraSetType(s32);
void cameraUpdate(void);
void *memcpy(void *, const void *, u32);
void windowGetKeyInfo(void);
u16 windowGetKeyRepeat(void);
s8 fadeCheck(s32);
void GSgfxLayerFindByID(u32);
void GScameraIsAnimating(u32);
void GScameraGetAnimFrame(u32);
void GSmodelSetRenderCamera(void *, u32);
void GSparticleGeneratorSetCamera(void *, u32);
void *GSresGetResource(u32, u32);
void GScameraGetMatrixPtr(void *);
void GScameraGetPerspective(void *, f32 *, f32 *, f32 *, f32 *);
void GScameraSetPerspective(void *, f32, f32, f32, f32);
void GScameraLookAt(void *, void *, void *);
void PSMTXRotRad(f32 (*)[4], char, f32);
void PSMTXMultVec(f32 (*)[4], void *, void *);
void cameraSetPosition(void *);
void cameraSetTargetPos(void *);
void cameraSetRotation(void *);
void cameraSetFov(f32);
double atan2(double, double);
double sin(double);
void GSmodelSetPosition(void *, void *);
void GSfsysReadID(u32, u32);
struct Hero;
Hero *savedataGetStatus(s32, s32);
void GSmemFree(void *);
void GSthreadSwitch(void);
u8 GSfsysWait(u32);
void GSresFreeResource(u32, u32);
void GSresFreeResourceAllGroup(void *);
void GScameraSetAnimIndex(void *, u32);
void GScameraSetAnimType(void *, s32);
void GScameraSetAnimRate(void *, f32);
void GScameraSetAnimFrame(void *, f32);
void GScameraStartAnimation(void *);
u32 floorGetCurrentGroupID(void);
void GSmodelSetBoundCheck(void *, u8);
u32 GSflagGet(void *);
}

struct WorldMapData {
    s16 unk0;
    u8 pad2[2];
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
    s8 nbr[8];
    u8 pad1C[0x2C - 0x1C];
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

struct Hero {
    u8 getFollowerID();
    u8 getHeroStyle() const;
};

struct _GSparticleGen;

class WorldMapModel {
public:
    u32 unk0;
    ~WorldMapModel() {
        if (unk0 != 0) {
            releaseOffscreenData();
        }
    }
    void releaseOffscreenData();
    void *SetModel(u32, u32, bool);
    void *GetModelPtr(u32);
    void renderOffscreenData(f32);
    void DetachModelPartPaticle(_GSparticleGen *, bool);
    s32 ModelDetach(u32);
    void UnloadModel(u32, u32);
    void SetLayerID(u32, long, GSgfxLayerID *);
    u8 CheckMotion(u32);
    void StopMotion(u32);
    void SetMotion(u32, short, f32, bool);
};

struct GlowObj {
    u8 pad0[0xC];
    f32 glow;
};

struct MapScooterData {
    u32 id;
    u32 pad[4];
};

struct WorldMapState {
    u8 flag;
    u8 pad1[0x2B];
    s32 field2c;
    s32 cursor;
    s32 floorId;
    u8 pad38[4];
    f32 f3c;
    u32 *modelPair;
    u32 camId;
    u8 flag48;
    u8 pad49[0x54 - 0x49];
    u32 model54;
    u32 model58;
    u8 pad5c[4];
    s32 scooterType;
    void *res64;
    u32 model68;
    u32 modelA;
    u32 modelB;
    MapScooterData *resList;
    u32 ids78[3];
    _GSparticleGen *particles[3];
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
    GlowObj *unk4;
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
    void setNullModel();
    void InitCamera(long);
    void RenderMoveDemoModel();
    s32 getScooterType();
    void Release();
    void InitModel2D(f32);
    s32 Ctrl(tagWINDOW_WORK *);
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
    u32 GetFlagData(long);
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

static MapScooterData _mapScooterData[7] = {
    { 0x206D0400, { 0x206D1000, 0x51, 0x55, 0 } },
    { 0x206E0400, { 0x206E1000, 0xA6, 0xAA, 0 } },
    { 0x206F0400, { 0x206F1000, 0x56, 0x5A, 0 } },
    { 0x20700400, { 0x20701000, 0xAA, 0xAE, 0 } },
    { 0x20710400, { 0x20711000, 0x50, 0x51, 0x52 } },
    { 0x20720400, { 0x20721000, 0x54, 0x55, 0x56 } },
    { 0x20730400, { 0x20731000, 0x57, 0x58, 0x59 } },
};
static f32 _glowstrngth = 0.0f;
static u8 _release_flag = 1;
static WorldMap *pWorldmap;
static u8 _DebugControl;
static s16 _cursor_index_num;
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

u32 WorldMap::GetFlagData(long index) {
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

void WorldMap::Release() {
    s32 off;
    s32 i;
    if (unk8->model68 != 0) {
        i = 0;
        off = 0;
        for (; i < 3; i++) {
            _GSparticleGen *p = *(_GSparticleGen **)((u8 *)unk8 + off + 0x84);
            if (p != 0) {
                DetachModelPartPaticle(p, 1);
            }
            off += 4;
        }
        ModelDetach(unk8->model68);
        if (_release_flag != 0 && GSresGetResourceAllGroup(unk8->model68) != 0) {
            UnloadModel(0x9E6, unk8->resList->id);
            GSresFreeResourceAllGroup(unk8->res64);
        }
    } else if (unk8->flag == 0) {
        while (GSfsysWait(0x9E6) == 0) {
            GSthreadSwitch();
        }
        GSresFreeResource(0x9E6, unk8->resList->id);
    }
    if (unk8 != 0) {
        GSmemFree(unk8);
        unk8 = 0;
    }
    if (icons != 0) {
        delete[] (WorldMapIconWork *)icons;
    }
    if (camera != 0) {
        delete camera;
    }
}

s32 WorldMap::getScooterType() {
    Hero *hero;
    s32 result;
    result = 0;
    hero = savedataGetStatus(0, 2);
    if (hero != 0) {
        u32 a;
        u8 follower;
        if (GSflagGet((void *)0x3C4) < flag_etc[0x44].value) {
            a = 0;
        } else {
            a = 1;
        }
        if (hero->getFollowerID() != 1) {
            follower = 0;
        } else {
            follower = 1;
        }
        switch (hero->getHeroStyle()) {
        case 0:
            if (a != 0) {
                result = 4;
            } else if (follower != 0) {
                result = 1;
            } else {
                result = 0;
            }
            break;
        case 2:
            if (a != 0) {
                result = 5;
            } else if (follower != 0) {
                result = 3;
            } else {
                result = 2;
            }
            break;
        case 1:
            if (a != 0) {
                result = 6;
            }
            break;
        }
    }
    return result;
}

s32 WorldMap::Ctrl(tagWINDOW_WORK *win) {
    long cursor = GetNowCursor(win);
    switch (win->phase) {
    case 0:
        if (unk8->flag == 0) {
            unk8->scooterType = getScooterType();
            unk8->resList = &_mapScooterData[unk8->scooterType];
            GSfsysReadID(0x9E6, unk8->resList->id);
        }
        break;
    case 2:
        MainControl(cursor);
        break;
    case 4:
        break;
    }
    return 0;
}

void WorldMap::SetCamera() {
    GSvec rot;
    GSvec tmp;
    GSvec out;
    f32 mtx[3][4];
    f32 aspect, near_, far_, fov;
    void *cam;
    f32 *cp;
    rot.x = 0.0f;
    rot.y = 0.0f;
    rot.z = 0.0f;
    timeGetLastFrameSec();
    cp = &camera->cur.x;
    cam = GSresGetResource(0, 0);
    GScameraGetMatrixPtr(cam);
    GScameraGetPerspective(cam, &fov, &aspect, &near_, &far_);
    GScameraSetPerspective(cam, cp[9], aspect, near_, far_);
    {
        f32 a = cp[6];
        f32 b = cp[7];
        tmp.y = b;
        tmp.x = 0.0f;
        tmp.z = a;
    }
    PSMTXRotRad(mtx, 0x59, cp[8]);
    PSMTXMultVec(mtx, &tmp, &tmp);
    PSVECAdd((GSvec *)cp, &tmp, &out);
    rot.y = cp[8];
    {
        f32 r = (f32)atan2(cp[7], cp[6]);
        rot.z = 0.0f;
        rot.x = -r;
    }
    GScameraLookAt(cam, cp + 3, cp);
    cameraSetPosition(&out);
    cameraSetTargetPos(cp);
    cameraSetRotation(&rot);
    cameraSetFov(cp[9]);
}

void WorldMap::ControlCursor(long) {
    void *model = GSresGetResourceAllGroup(cursorModel);
    f32 dt = GetLastTime();
    if (flag1C != 0) {
        cursorT += 2.0f * dt;
        if (cursorT >= _waittime) {
            cursorT = 1.0f;
            flag1C = 0;
        }
        Blendf(&cursorBlend.x, cursorBlend.x, cursorPos.x, cursorT);
        Blendf(&cursorBlend.y, cursorBlend.y, cursorPos.y, cursorT);
        Blendf(&cursorBlend.z, cursorBlend.z, cursorPos.z, cursorT);
    }
    if (unk8->flag != 0) {
        cursorTime += dt;
        cursorBob = 5.0f * (f32)sin(6.2831855f * cursorTime) + 5.0f;
        cursorBlend.y = cursorBob;
    }
    GSmodelSetPosition(model, &cursorBlend);
}

void WorldMap::RenderMoveDemoModel() {
    if (pWorldmap != 0) {
        u32 cam = unk8->camId;
        s32 i;
        if (unk8->model54 == 0x1B4A1001) {
            if (unk4 != 0) {
                unk4->glow = _glowstrngth;
            }
        }
        renderOffscreenData(unk8->f3c);
        GSgfxLayerFindByID(0);
        GScameraIsAnimating(cam);
        GSmodelSetRenderCamera(GetModelPtr(unk8->model54), cam);
        GSmodelSetRenderCamera(GetModelPtr(unk8->model58), cam);
        GSmodelSetRenderCamera(GetModelPtr(unk8->model68), cam);
        GSmodelSetRenderCamera(GetModelPtr(unk8->modelB), cam);
        for (i = 0; i < 3; i++) {
            if (unk8->particles[i] != 0) {
                GSresGetResourceAllGroup(unk8->ids78[i]);
                GSparticleGeneratorSetCamera(unk8->particles[i], cam);
            }
        }
        GScameraGetAnimFrame(cam);
    }
}

void WorldMap::ControlPad(tagWINDOW_WORK *win) {
    u16 key = (windowGetKeyInfo(), windowGetKeyRepeat());
    s32 dir = -1;
    s16 cursor;
    cursor = _cursor_index[unk8->cursor];
    if (fadeCheck(0) == 0 && flag1C != 1 && unk8->flag48 != 1) {
        GetModelID(cursor);
        if (key == 8) {
            dir = 0;
        } else if (key == 0xA) {
            dir = 1;
        } else if (key == 2) {
            dir = 2;
        } else if (key == 6) {
            dir = 3;
        } else if (key == 4) {
            dir = 4;
        } else if (key == 5) {
            dir = 5;
        } else if (key == 1) {
            dir = 6;
        } else if (key == 9) {
            dir = 7;
        }
        {
            WorldMapIconData *icon = &icons[cursor];
            if (dir >= 0) {
                s8 n = icon->nbr[dir];
                if (n >= 0) {
                    s16 i = 0;
                    s16 *p;
                    for (p = _cursor_index; i < _cursor_index_num; p++, i++) {
                        if (n == *p) {
                            unk8->cursor = i;
                            win->pos.selected = i;
                            SetCursorPosition(i, 1);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void WorldMap::CheckIconAnime(long index) {
    u32 model;
    s16 cursor;
    s32 i;
    s32 off = 0;
    cursor = _cursor_index[index];
    i = 0;
    unk8->flag48 = off;
    for (; i < GetDataNum(); i++, off += 0x2C) {
        WorldMapIconData *ic = (WorldMapIconData *)((u8 *)icons + off);
        s16 motion = ic->motion;
        model = *(u32 *)ic;
        switch (motion) {
        case 0:
        case 3:
        default:
            break;
        case 1:
            if (!CheckMotion(model)) {
                SetIconMotion(i, model, 2, 0.0f, 1);
            } else {
                unk8->flag48 = 1;
            }
            break;
        case 6:
            if (!CheckMotion(model)) {
                SetIconMotion(i, model, 7, 0.0f, 1);
            }
            break;
        case 2:
            if (cursor == i) {
                SetIconMotion(i, model, 4, 0.0f, 1);
            }
            break;
        case 7:
            if (cursor == i) {
                SetIconMotion(i, model, 8, 0.0f, 1);
            }
            break;
        case 4:
            if (cursor != i) {
                SetIconMotion(i, model, 2, 0.0f, 1);
            }
            break;
        case 8:
            if (cursor != i) {
                SetIconMotion(i, model, 7, 0.0f, 1);
            }
            break;
        case 5:
            if (!CheckMotion(model)) {
                StopMotion(model);
            }
            break;
        case 9:
            if (!CheckMotion(model)) {
                StopMotion(model);
            }
            break;
        }
    }
}

void WorldMap::InitCamera(long) {
    GSvec pos;
    f32 d;
    f32 a;
    f32 b;
    f32 c;
    f32 aspect;
    f32 near_;
    f32 far_;
    f32 saved;
    void *cam;
    cameraSetType(3);
    camera->blendT = 0.0f;
    camera->speed = 0.0f;
    if (_cameraDebug != 0) {
        GetCameraData(0x13, &pos, &a, &b, &c, &d);
    } else if (GetFlagData(5) != 0) {
        GetCameraData(0x13, &pos, &a, &b, &c, &d);
    } else {
        GetCameraData(0x12, &pos, &a, &b, &c, &d);
    }
    SetCameraNextWork(&pos, a, b, c, d);
    memcpy(&camera->cur, &camera->next, 0x28);
    SetCamera();
    cameraUpdate();
    saved = d;
    cam = GSresGetResource(0, 0);
    GScameraGetMatrixPtr(cam);
    GScameraGetPerspective(cam, &d, &aspect, &near_, &far_);
    GScameraSetPerspective(cam, saved, aspect, near_, far_);
    InitModel2D(d);
    if (unk8->flag == 0) {
        s16 cursor = _cursor_index[unk8->field2c];
        WorldMapData *data = SearchData(cursor);
        GetCameraData(data->unk0, &pos, &a, &b, &c, &d);
        SetCameraWork(&icons[cursor].pos, a, b, c, d);
        SetCameraSpeed(1.0f);
        SetCamera();
    }
}

void WorldMap::setNullModel() {
    u32 b = unk8->modelPair[1];
    u32 a = unk8->modelPair[0];
    u32 gid = floorGetCurrentGroupID();
    unk8->modelA = a;
    unk8->modelB = b;
    SetModel(gid, a, 0);
    GSgfxLayerID layer = { 2 };
    SetLayerID(unk8->modelB, 1, &layer);
    GSmodelSetBoundCheck(GSresGetResourceAllGroup(unk8->modelB), 0);
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
    f32 upper = 6.2831855f - range;
    u8 hit = 0;
    s8 result = -1;
    f32 center;
    center = 3.1415927f * (f32)index * 0.25f;
    if ((f32)index == 0.0f) {
        if (angle >= upper || angle < range) {
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
    GSvec pos;
    GSvec out;
    f32 a;
    f32 d;
    f32 c;
    f32 b;
    u32 model;
    s16 cursor = _cursor_index[index];
    WorldMapData *data = SearchData(cursor);
    GetCameraData(data->unk0, &pos, &a, &b, &c, &d);
    PSVECAdd(&icons[cursor].pos, &pos, &out);
    SetCameraNextWork(&out, a, b, c, d);
    SetCameraSpeed(1.0f);
    {
        model = *(u32 *)&icons[cursor];
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

void *_cameraPlayAnime(u32 id, long frame, bool loop);
void *_cameraPlayAnime(u32 id, long frame, bool loop) {
    void *cam = GSresGetResourceAllGroup(id);
    GScameraSetAnimIndex(cam, 0);
    if (loop) {
        GScameraSetAnimType(cam, 1);
    } else {
        GScameraSetAnimType(cam, 0);
    }
    GScameraSetAnimRate(cam, 0.5f);
    GScameraSetAnimFrame(cam, (f32)frame);
    GScameraStartAnimation(cam);
    return cam;
}

extern "C" void menuWorldMapMXDebug(void) {
    s32 off;
    s32 i;
    i = 0;
    off = 0;
    for (; i < *worldmapXD_data_number; i++) {
        if (*(void **)((u8 *)worldmapXD_data + off + 4) != 0) {
            GSflagSet(*(void **)((u8 *)worldmapXD_data + off + 4), 2);
        }
        off += 0x24;
    }
}
