#include <game/pxdvs/app/floor/floorPrivate.hpp>

extern "C" {
void *memset(void *, int, u32);
void GSlogWrite(const char *, ...);
void GSprint(s32, s32, s32, u32, const char *, ...);
s32 dbgMenuGetLayerID();

GSfloor_dd_ *floorDataBiosGetPtr(u32);
GSfloor_dd_ *floorDataBiosGetCurrentPtr();
u32 floorDataBiosGetGroupID(GSfloor_dd_ *);
u32 floorDataBiosGetMapResID(GSfloor_dd_ *);
u8 floorDataBiosGetFloorKind(GSfloor_dd_ *);
u32 floorDataBiosGetFileGroupID(GSfloor_dd_ *);
u32 floorDataBiosGetArea(GSfloor_dd_ *);
u32 floorDataBiosGetCharNum(GSfloor_dd_ *);
u32 floorDataBiosGetLensFlareResID(GSfloor_dd_ *);
u32 floorDataBiosGetSunResID(GSfloor_dd_ *);
s32 floorDataBiosGetSecondaryRenderNum(GSfloor_dd_ *);
u32 floorDataBiosGetSecondaryRenderID(GSfloor_dd_ *, u32);
FloorPositionList *floorDataBiosGetPosListPtr(GSfloor_dd_ *);
u32 floorDataBiosGetPlaceName(GSfloor_dd_ *);
void (*floorDataBiosGetPreFunc(GSfloor_dd_ *))(GSfloor_dd_ *, u32);
void (*floorDataBiosGetMainFunc(GSfloor_dd_ *))();
void (*floorDataBiosGetPostFunc(GSfloor_dd_ *))(GSfloor_dd_ *, u32);
s32 floorDataBiosModelIDGetFogState(u32);

floorCharacter_dd_ *floorCharacterBiosGetCurrentPtr(u32);
void *floorCharacterBiosGetPeopleInfoPtr(floorCharacter_dd_ *);
u32 peopleInfoBiosGetModelResID(void *);
u8 floorCharacterBiosGetLoadInit(floorCharacter_dd_ *);
u32 floorCharacterBiosGetVisibility(floorCharacter_dd_ *);
u32 floorCharacterBiosGetIsHit(floorCharacter_dd_ *);
u8 floorCharacterBiosGetMoveType(floorCharacter_dd_ *);
u8 floorCharacterBiosGetTalkStartType(floorCharacter_dd_ *);
u8 floorCharacterBiosGetTalkEndType(floorCharacter_dd_ *);
void floorCharacterBiosGetPos(floorCharacter_dd_ *, GSvec *);
void floorCharacterBiosGetRot(floorCharacter_dd_ *, GSvec *);
void floorCharacterBiosInitGlobalCharacter();

extern FloorTresureEntry *floor_tresure_list;
extern u32 *floor_tresure_list_number;
extern FloorDoorEntry *floor_door_list;
extern u32 *floor_door_list_number;
extern u8 pokecoloWaitVSync;

s32 pokecoloGetRomVersion();
s32 pokecoloGetLanguage();
s32 pokecoloGetCountryCode();
u8 pokecoloIsDVDETHMode();

u32 GSfloorGetCurrent();
u32 GSfloorGetCurrentFloorGroupID();
void GSfloorOpen(u32);
void GSfloorStart(u32);
void GSfloorChange(u32);
u32 floorGetCurrent();
u32 floorGetNextChangeID();
u32 floorGetCurrentGroupID();
s32 floorGetCurentScriptMode();
u8 floorIsContinueMode();
u8 floorCheckAnywaySaveData();
u8 floorIsPop();
u8 floorIsPush();
u8 floorIsFloorPushed();
u8 floorIsDispScriptInfo();
u8 floorGetHumanColision();
void floorClearReturnPoint();
void floorChange(u32);
u32 floorReadMakeModelResID(u32);
u32 floorReadMakeLightResID(u32);
u32 floorReadMakeFogResID(u32);
u32 floorReadMakeCameraResID(u32);
void *floorReadResourceID(u32, u32);
u32 floorRegisterModule(u32, u32, FloorModuleInterface *);
u32 floorRegisterScriptModule(u32, u32, s32, s32, s32);
void floorUnblockModule(u32);
void floorBlockModule(u32);
void floorExecScriptIntegerByName(const char *, u32, s32, s32, s32);
void floorExecScriptInteger(u32, s32, s32, s32, s32);
void floorExecScriptIntegerThread(u32, s32, s32, s32, s32);
void floorEventCtrlDoor(u32, u32, u32);
void floorEventCtrlTresure(u32, u32, u32);
void floorOffscreenMainInit();
void floorInitOffscreen(GSfloor_dd_ *);
void floorReleaseOffscreen();
void floorUpdateOffscreen();
void floorUpdateFieldCamera();
FloorModuleInterface *effectViewerGetFloorModule();
FloorModuleInterface *fightGetFloorModule();
void FloorModuleInterface_clear(FloorModuleInterface *);
FloorBgmMask *floorSound_getBgmMaskObj();
void floorSound_playSound();
void floorSound_playEnvSound(u32);

u32 peopleOpen(u32, u32, u32);
u32 peopleGetHumanID(u32, u32);
void *peopleGet(u32, u32);
u32 peopleGetMoveSctID(u32, u32);
void peopleAllClose(u32);
void peopleSetPos(u32, u32, GSvec *);
void peopleSetRot(u32, u32, GSvec *);
void peopleAddCollision(u32, u32);
void peopleSetCollision(u32, u32, u32);
void peopleSetFlagOn(u32, u32, u32);
void peopleSetFlagOff(u32, u32, u32);
void peopleSetDisp(u32, u32, s32);
void peopleManualAnimation(u32, u32);
void peopleBiosSetTresureID(void *, u16);
void peopleExecMoveScript(u32, u32, u32, u32, u32);
void peopleStartWalkRandom(u32, u32, f32);
void peopleStartRotRandom(u32, u32, f32, f32);
void peopleMoveNeckTargetHero(u32, u32, f32);

void *GSresGetResource(u32, u32);
void *GSresGetResourceAllGroup(u32);
void GSresFreeResource(u32, u32);
void GSresFreeGroup(u32);
void GSresRegisterResource(void *, u32, u32, s32 (*)(void *, u32, u32));
void *HSD_ArchiveGetPublicAddress(void *, const char *);
s32 GSfsysGetStatus(u32);
void GSfsysFree(u32);
void GSfsysPreRead(u32);
void GSfsysReadWait(u32);
void GSfsysReadIDWait(u32, u32);
void GSthreadSwitch();
void GSsndPlayNow(u32);
u8 GSflagTest(u16);
void GSflagClear(u32);

_GSmodel *GSmodelLoad(void *, s32);
void GSmodelFree(void *);
void GSmodelSetVisibility(void *, s32);
u8 GSmodelCanAnimate(void *);
u8 GSmodelCanTexAnimate(void *);
void GSmodelSetBoundCheck(void *, s32);
void GSmodelSetRenderLayer(void *, s32, const void *);
void GSmodelLinkTexAnimToAnim(void *, s32);
void GSmodelSetTexAnimRate(void *, f32);
void GSmodelSetTexAnimIndex(void *, s32);
void GSmodelStartTexAnimation(void *);
void GSmodelSetAnimIndex(void *, s32);
void GSmodelSetAnimRate(void *, f32);
void GSmodelStartAnimation(void *);
void GSmodelSetFogState(void *, s32, s32);
void GSmodelClearShadowFlags(void *, s32);
void GSmodelGetPosition(void *, GSvec *);
void GSmodelSetShadowToCameraHeightCheck(s32);
void GSmodelSetShadowBoundExpansion(f32);
void GSmodelSetShadowDistLimits(f32, f32);
void GSmodelSetShadowCutoffDist(f32);
void GSmodelSetShadowTextureSize(s32, s32);
void GSmodelPushState(void *, void *);
void GSmodelPopState(void *, void *);
void GSlightSetActive(void *, s32);
u8 GSlightCanAnimate(void *);
void GSlightSetAnimIndex(void *, s32);
void GSlightSetAnimRate(void *, f32);
void GSlightStartAnimation(void *);
void GSlightPushState(void *, void *);
void GSlightPopState(void *, void *);
void GSlensFlareSetVisible(void *, s32);
void GSlensFlareSetSunPosition(void *, GSvec *);
GSgfxLayer *GSgfxLayerFindByID(s32);
void GSgfxVideoSetClearColor(GSgfxColAu8);
void GSgfxVideoSetLockFrameRate(s32);
void *GScameraGetActiveCamera();
void GScameraGetPerspective(void *, f32 *, f32 *, f32 *, f32 *);
void GScameraSetPerspective(void *, f32, f32, f32, f32);
void GSinputResetLeftSmoothing(s32, s32, s32);
void GSinputResetRightSmoothing(s32, s32, s32);
void GScolsys2Draw(GSmtx *);
void GScolsys2HumanDispColision();
s32 GSmemGetCurrentHeap();
void GSmemGetHeapFreeSize(s32, u32 *, u32 *);
s32 GSmemCreateHeap(void *, void *);
void *OSGetArenaLo();
void OSSetArenaLo(void *);

s32 soundGetBGMID();
s32 soundGetEnvID();
s32 soundGetVolume(s32);
void soundOpenPlay(s32, s32, s32);
void soundOpenPlayEnv(s32, s32, s32);
void soundSetVolumeID(s32, s32, s32);

void cameraSetType(s32);
void cameraUpdate();
f32 cameraGetDistance();
void cameraSetDistance(f32);
void cameraSetTarget(s32, s32);
void cameraSetTargetOfs(GSvec *);
void cameraSetGScamera(void *);
void battleCameraInit(GSfloor_dd_ *);
void battleCameraStop();
void battleCameraUpdate();
void battleGridReset();
void wazaSequenceSysInit();
void wazaSequenceSysInitExtras();
void wazaSequenceSysRelease();
void wazaSequenceSysUpdate();
void heroMoveInit(GSvec *, GSvec *);
u32 heroMoveGetKenObjID();
u32 heroGetObjID(u32);
void menuCloseFloor();
void menuPocketClearItemScript();
void scriptGlowEnd();
void scriptModelInit();
void msgctrlInitValue();
void mailMainReceiveTerminate();
FIGHT_ENCOUNT *fightEncountGetStrObj();
f32 timeGetLastFrameSec();
void fadeCheck(s32);
u32 gamedatasaveGetStatus(s32, s32);
void floorMapResourceDataIterate(void (*)(u32, u32, u32, void *, void *), void *);
void *floorOpenObject(u32);
void floorLinkWithSE(u32, u32, s32);
u32 fn_8011E5D8();
u32 fn_8011E650();
}

GSscript::Tiga *floorGetCurentScript();
void EvlogPrint();

struct MapStateEntry {
    u32 id;
    u32 type;
    u8 state[0x6c];
};
struct MapStateCursor {
    MapStateEntry *cur;
    u32 count;
};
struct MapCount {
    s32 models;
    s32 lights;
};

static FloorModuleInterface _floorModuleCommon;
static FloorModuleInterface _floorModuleField;
static FloorModuleInterface _floorModuleWazaViewer;
static FloorModuleInterface _floorModuleUniqueFunc;
static struct {
    void (*pre)(GSfloor_dd_ *, u32);
    void (*main)();
    void (*post)(GSfloor_dd_ *, u32);
} _floorUniqueFunc;
static FLOOR_CHANGE_INFO _floorChangeInfo;

static u32 _hModuleCommon;
static u32 _hModuleField;
static u32 _hModuleWazaViewer;
static u32 _hModuleUniqueFunc;
static u32 _hModuleFloorScript;
static void (*_floorUniqueFuncThread)();
static s32 _floorLocalHeap;
static s8 evlog_start;

static EvLogEntry EvLog[10] = {
    {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}, {-1, 0},
};

static void _floorMapPushCB(u32, u32, u32, void *, void *);
static void _floorMapPopCB(u32, u32, u32, void *, void *);
static void _floorMapGetResourceCounts(int *, int *);
static void _floorMapGetCountCB(u32, u32, u32, void *, void *);
static void _floorMapSetDispCB(u32, u32, u32, void *, void *);
static void _floorFsysFree(u32);
static void _floorInitCharactor(u32, u32, u32);
static void _floorReleaseWazaSequence(GSfloor_dd_ *);
static void _floorUpdateWazaSequence(GSfloor_dd_ *);
static void _floorInitShadow(GSfloor_dd_ *);
static void _floorInitScene(GSfloor_dd_ *);
static void _floorInitMapFog(GSfloor_dd_ *);
static void _floorInitTresure(GSfloor_dd_ *);
static void _floorInitDoor(GSfloor_dd_ *);
static void _floorInitCharacters(GSfloor_dd_ *);
static void _floorSetInitPosition();
static void _floorClearFlag();
static s32 _floorUnloadModel(void *, u32, u32);
static const char *_floorGetModuleName();
static u32 _floorGetUID();
static u32 _floorGetStateSize(FloorStateMode);
static void _floorRestoreStateData(FloorStateMode, void *, u32);
static void _floorMakeStateData(FloorStateMode, void *, u32);
static void _floorCreateCommon(unsigned int, FloorEnterMode);
static void _floorUniqueFinalize(unsigned int, FloorEnterMode);
static void _floorUniqueUpdate();
static void _floorUniqueInitialize(unsigned int, FloorEnterMode);
static void _floorFreeCommon(unsigned int, FloorEnterMode);
static void _floorFinalizeCommon(unsigned int, FloorEnterMode);
static void _floorUpdateCommon(unsigned int, FloorEnterMode);
static void _floorInitializeCommon(unsigned int, FloorEnterMode);
static void _floorFinalize(unsigned int, FloorEnterMode);
static void _floorUpdate(unsigned int, FloorEnterMode);
static void _floorInitialize(unsigned int, FloorEnterMode);
static const char *_floorGetUniqueModuleName();
static const char *_floorGetMenuModuleName();
static const char *_floorGetFieldModuleName();

extern "C" {

void floorGetLightInfo(u32 *a, u32 *b) {
    if (a) *a = _floorChangeInfo.lightA;
    if (b) *b = _floorChangeInfo.lightB;
}

void floorSetLightInfo(u32 a, u32 b) {
    _floorChangeInfo.lightA = a;
    _floorChangeInfo.lightB = b;
}

void floorUnblockMainScript() {
    floorUnblockModule(_hModuleFloorScript);
}

void floorBlockMainScript() {
    floorBlockModule(_hModuleFloorScript);
}
}

static void _floorMapPushCB(u32 type, u32 group, u32 resID, void *res, void *user) {
    MapStateEntry **cursor = (MapStateEntry **)user;
    MapStateEntry *e = *cursor;
    e->id = resID;
    e->type = type;
    switch (type) {
    case 1:
        GSmodelPushState(res, e->state);
        break;
    case 2:
        GSlightPushState(res, e->state);
        break;
    }
    *cursor = e + 1;
}

static const char *_floorGetModuleName() {
    return "floorModuleCommon";
}

static u32 _floorGetUID() {
    static const char *id = "FLOR";
    return (id[0] << 24) | (id[1] << 16) | (id[2] << 8) | id[3];
}

static u32 _floorGetStateSize(FloorStateMode mode) {
    if (mode != 1 && mode != 2) return 0;
    int models, lights;
    _floorMapGetResourceCounts(&models, &lights);
    return (models + lights) * sizeof(MapStateEntry) + 0x10;
}

static void _floorRestoreStateData(FloorStateMode mode, void *buf, u32 size) {
    u32 *words = (u32 *)buf;
    if (mode == 1 || mode == 2) {
        if (_floorChangeInfo.playBgm) {
            if (words[0] != soundGetBGMID()) {
                soundOpenPlay(words[0], 1000, 0x7f);
                soundSetVolumeID(words[0], 1000, (u8)words[1]);
            }
        }
        if (_floorChangeInfo.playEnv) {
            if (words[2] != soundGetEnvID()) {
                soundOpenPlayEnv(words[2], 1000, 0x7f);
                soundSetVolumeID(words[2], 1000, (u8)words[3]);
            }
        }
        MapStateCursor cursor;
        cursor.cur = (MapStateEntry *)(words + 4);
        cursor.count = (size - 0x10) / sizeof(MapStateEntry);
        floorMapResourceDataIterate(_floorMapPopCB, &cursor);
    }
}

static void _floorMakeStateData(FloorStateMode mode, void *buf, u32 size) {
    u32 *words = (u32 *)buf;
    if (mode == 1 || mode == 2) {
        if (mode == 1) floorReleaseOffscreen();
        memset(buf, 0, 0x10);
        words[0] = soundGetBGMID();
        words[1] = soundGetVolume(words[0]);
        words[2] = soundGetEnvID();
        words[3] = soundGetVolume(words[2]);
        MapStateEntry *cursor = (MapStateEntry *)(words + 4);
        floorMapResourceDataIterate(_floorMapPushCB, &cursor);
    }
}

static void _floorMapPopCB(u32 type, u32 group, u32 resID, void *res, void *user) {
    MapStateCursor *cursor = (MapStateCursor *)user;
    MapStateEntry *e = cursor->cur;
    for (u32 n = cursor->count; n != 0; n--, e++) {
        if (resID == e->id) {
            switch (e->type) {
            case 1:
                GSmodelPopState(res, e->state);
                break;
            case 2:
                GSlightPopState(res, e->state);
                break;
            }
            break;
        }
    }
}

static void _floorMapGetResourceCounts(int *models, int *lights) {
    MapCount count;
    count.models = 0;
    count.lights = 0;
    floorMapResourceDataIterate(_floorMapGetCountCB, &count);
    *models = count.models;
    *lights = count.lights;
}

static void _floorMapGetCountCB(u32 type, u32 group, u32 resID, void *res, void *user) {
    MapCount *count = (MapCount *)user;
    switch (type) {
    case 1:
        count->models++;
        break;
    case 2:
        count->lights++;
        break;
    }
}

extern "C" {
void floorMapResourceDataIterate(void (*callback)(u32, u32, u32, void *, void *), void *user) {
    u32 group;
    u32 base;
    u32 j = 0;
    u32 i = 0;
    void *res;
    SceneData *scene;
    u32 resID;
    u32 mapRes = floorDataBiosGetMapResID(floorDataBiosGetCurrentPtr());
    if (mapRes != 0) {
        group = floorGetCurrentGroupID();
        scene = (SceneData *)HSD_ArchiveGetPublicAddress(GSresGetResource(group, mapRes), "scene_data");
        if (scene != 0) {
            if (scene->models != 0) {
                base = floorReadMakeModelResID(mapRes);
                for (; scene->models[i] != 0; i++) {
                    resID = base | i;
                    res = GSresGetResource(group, resID);
                    if (res != 0) callback(1, group, resID, res, user);
                }
            }
            if (scene->lights != 0) {
                base = floorReadMakeLightResID(mapRes);
                for (; scene->lights[j] != 0; j++) {
                    resID = base | j;
                    res = GSresGetResource(group, resID);
                    if (res != 0) callback(2, group, resID, res, user);
                }
            }
        }
    }
}

void floorMapSetDisp(u32 visible) {
    floorMapResourceDataIterate(_floorMapSetDispCB, (void *)(u8)visible);
}
}

static void _floorMapSetDispCB(u32 type, u32 group, u32 resID, void *res, void *user) {
    s32 visible = user != 0;
    switch (type) {
    case 1:
        GSmodelSetVisibility(res, visible);
        break;
    case 2:
        GSlightSetActive(res, visible);
        break;
    }
}

extern "C" {
u8 floorGetHumanColision() {
    return _floorChangeInfo.humanCollision;
}

void floorSetHumanColision(u8 v) {
    _floorChangeInfo.humanCollision = v;
}

u32 floorCheckFightKind(u32 floorID) {
    u32 result = 0;
    if (floorID != (u32)-1) {
        switch (floorDataBiosGetFloorKind(floorDataBiosGetPtr(floorID))) {
        case 2:
            result = 1;
            break;
        }
    }
    return result;
}
}

static void _floorCreateCommon(unsigned int a, FloorEnterMode mode) {
    GSgfxColAu8 black = {0, 0, 0, 0};
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    cameraSetType(3);
    GSgfxVideoSetClearColor(black);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 6:
        _floorFsysFree(0x9a);
        if (GSfsysGetStatus(fn_8011E5D8()) != 0) GSfsysReadWait(fn_8011E5D8());
        _floorFsysFree(fn_8011E650());
        break;
    case 1: {
        if (pokecoloGetRomVersion() != 2) {
            _floorFsysFree(fn_8011E650());
            u32 total, free;
            GSmemGetHeapFreeSize(GSmemGetCurrentHeap(), &total, &free);
            if (free * 100 / total < 80) {
                _floorFsysFree(fn_8011E5D8());
                _floorFsysFree(0x9a);
            }
            u32 ken = heroMoveGetKenObjID();
            if (ken != heroGetObjID(0)) GSfsysReadIDWait(0x9a, ken);
            if (GSfsysGetStatus(fn_8011E5D8()) != 0) GSfsysReadWait(fn_8011E5D8());
        }
        break;
    }
    case 2:
        if (pokecoloGetRomVersion() != 2) {
            _floorFsysFree(fn_8011E5D8());
            _floorFsysFree(0x9a);
            if (GSfsysGetStatus(fn_8011E650()) != 0) GSfsysReadWait(fn_8011E650());
        }
        break;
    }
}

extern "C" {
u32 fn_8011E5D8() {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0xb;
    case 3:
        return 0xa95;
    case 4:
        return 0xa96;
    case 5:
        return 0xa97;
    case 6:
        return 0xa98;
    default:
        return 0xb;
    }
}

u32 fn_8011E650() {
    switch (pokecoloGetLanguage()) {
    case 2:
        return 0xc;
    case 3:
        return 0xa99;
    case 4:
        return 0xa9a;
    case 5:
        return 0xa9b;
    case 6:
        return 0xa9c;
    default:
        return 0xc;
    }
}
}

static void _floorFsysFree(u32 id) {
    switch (GSfsysGetStatus(id)) {
    case -1:
        break;
    case 1:
        while (GSfsysGetStatus(id) == 1) GSthreadSwitch();
    case 0:
        GSresFreeGroup(id);
        GSfsysFree(id);
        break;
    }
}

extern "C" {
u32 floorReadCharacter(u32 group, u32 idx, u32 res) {
    GSvec a;
    GSvec b;
    floorCharacter_dd_ *c = floorCharacterBiosGetCurrentPtr(idx);
    void *info = floorCharacterBiosGetPeopleInfoPtr(c);
    if (res == 0) res = peopleInfoBiosGetModelResID(info);
    u32 h = peopleOpen(group, idx, res);
    if (h == 0) {
        GSlogWrite("Error! [%s] \x90\x6C\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n", __FUNCTION__);
        return 0;
    }
    _floorInitCharactor(group, idx, h);
    return 1;
}

void floorExecSoundScript() {
    if (floorGetCurentScriptMode() == 1) {
        u32 flag = 0;
        if (floorIsContinueMode()) flag = 3;
        floorExecScriptIntegerByName("sound", GSfloorGetCurrentFloorGroupID(), flag, 0, 0);
    }
}

void floorCheckFade() {
    fadeCheck(1);
    pokecoloWaitVSync = 0;
    GSgfxVideoSetLockFrameRate(0);
}

void floorExecFadeOut() {
    if (_floorChangeInfo.fadeOutScript != 0) floorExecScriptInteger(_floorChangeInfo.fadeOutScript, 0, 0, 0, 0);
}

void floorExecFadeIn() {
    if (_floorChangeInfo.fadeInScript != 0) {
        if (_floorChangeInfo.fadeInScript != 0) _floorChangeInfo.fadeInRequest = 1;
    }
}

void flooSetFrameRate() {
    pokecoloWaitVSync = 1;
    switch (floorDataBiosGetFloorKind(floorDataBiosGetCurrentPtr())) {
    case 5:
    case 6:
        GSgfxVideoSetLockFrameRate(0);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    default:
        GSgfxVideoSetLockFrameRate(1);
        break;
    }
}

void floorSetFadeScript(u32 outScript, u32 inScript) {
    _floorChangeInfo.fadeInScript = inScript;
    _floorChangeInfo.fadeOutScript = outScript;
}

void floorInit() {
    FloorModuleInterface_clear(&_floorModuleCommon);
    FloorModuleInterface_clear(&_floorModuleField);
    FloorModuleInterface_clear(&_floorModuleWazaViewer);
    _floorModuleCommon.create = _floorCreateCommon;
    _floorModuleCommon.pre = _floorInitializeCommon;
    _floorModuleCommon.normal = _floorUpdateCommon;
    _floorModuleCommon.post = _floorFinalizeCommon;
    _floorModuleCommon.free = _floorFreeCommon;
    _floorModuleCommon.saveState = _floorMakeStateData;
    _floorModuleCommon.loadState = _floorRestoreStateData;
    _floorModuleCommon.getStateSize = _floorGetStateSize;
    _floorModuleCommon.getStateID = _floorGetUID;
    _floorModuleCommon.getName = _floorGetModuleName;
    _hModuleCommon = floorRegisterModule(0, 0x5000, &_floorModuleCommon);
    u32 floorID;
    switch (pokecoloGetRomVersion()) {
    case 5:
        floorID = 0x3e4;
        break;
    case 1:
        floorID = 0x3e6;
        break;
    case 2:
        floorID = 0xae;
        break;
    case 6:
        floorID = 0x399;
        break;
    default:
        if (pokecoloIsDVDETHMode()) {
            floorID = 0x384;
        } else {
            floorID = 0x399;
        }
        break;
    }
    _floorChangeInfo.prevFloorID = 0;
    _floorChangeInfo.nextFloorID = floorID;
    _floorChangeInfo.useInitPosition = 1;
    _floorChangeInfo.nextPosIndex = 0;
    _floorChangeInfo.fadeInRequest = 0;
    _floorChangeInfo.continueMode = 0;
    _floorChangeInfo.playBgm = 0;
    _floorChangeInfo.playEnv = 1;
    GSfloorOpen(floorID);
    GSfloorStart(floorID);
    floorOffscreenMainInit();
    floorCharacterBiosInitGlobalCharacter();
}
}

static void _floorUniqueFinalize(unsigned int a, FloorEnterMode mode) {
    if (mode != 1) {
        GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
        if (_floorUniqueFunc.post != 0) _floorUniqueFunc.post(floor, floorDataBiosGetGroupID(floor));
    }
}

static void _floorUniqueUpdate() {
    if (_floorUniqueFuncThread != 0) _floorUniqueFuncThread();
}

static void _floorUniqueInitialize(unsigned int a, FloorEnterMode mode) {
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    if (_floorUniqueFunc.pre != 0) _floorUniqueFunc.pre(floor, floorDataBiosGetGroupID(floor));
}

static void _floorFreeCommon(unsigned int a, FloorEnterMode mode) {
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    floorDataBiosGetPtr(floorGetNextChangeID());
    AppScript *script = floorGetCurentScript();
    if (script != 0) script->unload();
    _floorReleaseWazaSequence(floor);
    floorReleaseOffscreen();
    if (mode == 1) {
        peopleAllClose(0);
    } else {
        peopleAllClose(1);
    }
    menuCloseFloor();
    scriptGlowEnd();
}

static void _floorFinalizeCommon(unsigned int a, FloorEnterMode mode) {
    FloorBgmMask *mask = floorSound_getBgmMaskObj();
    if (mask != 0) mask->finalize();
    if (mode == 1) {
        floorExecScriptIntegerByName("pushpop_postprocess", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
    } else {
        mailMainReceiveTerminate();
    }
}

static void _floorUpdateCommon(unsigned int a, FloorEnterMode mode) {
    _floorUpdateWazaSequence(floorDataBiosGetPtr(a));
    if (_floorChangeInfo.fadeInScript != 0) {
        if (_floorChangeInfo.fadeInRequest != 0) {
            _floorChangeInfo.fadeInRequest = 0;
            floorExecScriptIntegerThread(_floorChangeInfo.fadeInScript, 0, 0, 0, 0);
        }
    }
    if (floorIsDispScriptInfo()) floorGetCurentScript()->debugDump();
    FloorBgmMask *mask = floorSound_getBgmMaskObj();
    if (mask != 0) mask->update(timeGetLastFrameSec());
}

static void _floorInitializeCommon(unsigned int a, FloorEnterMode mode) {
    u32 group;
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    _floorClearFlag();
    msgctrlInitValue();
    scriptModelInit();
    _floorSetInitPosition();
    FIGHT_ENCOUNT *encount = fightEncountGetStrObj();
    if (encount != 0) encount->setDirtyFlag(true);
    _floorInitScene(floor);
    floorInitOffscreen(floor);
    _floorInitShadow(floor);
    _floorInitMapFog(floor);
    if (floorGetCurentScriptMode() == 1) {
        floorExecScriptIntegerByName("modify_floor", GSfloorGetCurrentFloorGroupID(), mode, 0, 0);
    }
    group = GSfloorGetCurrentFloorGroupID();
    if (mode != 2) {
        switch (floorDataBiosGetFloorKind(floor)) {
        case 1:
            if (pokecoloGetRomVersion() == 2) {
                _hModuleField = floorRegisterModule(0x14, group, effectViewerGetFloorModule());
            } else {
                FloorModuleInterface_clear(&_floorModuleField);
                _floorModuleField.pre = _floorInitialize;
                _floorModuleField.normal = _floorUpdate;
                _floorModuleField.post = _floorFinalize;
                _floorModuleField.getName = _floorGetFieldModuleName;
                _hModuleField = floorRegisterModule(10, group, &_floorModuleField);
            }
            if (mode != 2 && mode != 1) menuPocketClearItemScript();
            break;
        case 2:
            if (pokecoloGetRomVersion() == 2) {
                _hModuleField = floorRegisterModule(0x14, group, effectViewerGetFloorModule());
            } else {
                _hModuleField = floorRegisterModule(0x14, group, fightGetFloorModule());
            }
            break;
        case 4:
            _hModuleWazaViewer = floorRegisterModule(0x14, group, effectViewerGetFloorModule());
            break;
        case 5:
        case 6:
            FloorModuleInterface_clear(&_floorModuleField);
            _floorModuleField.normal = _floorUpdate;
            _floorModuleField.getName = _floorGetMenuModuleName;
            _hModuleField = floorRegisterModule(0x14, group, &_floorModuleField);
            break;
        }
        if (pokecoloGetRomVersion() != 2 && floorGetCurentScriptMode() == 1) {
            s32 pre = floorGetCurentScript()->getNameToFuncId("preprocess");
            s32 main = floorGetCurentScript()->getNameToFuncId("hero_main");
            s32 post = floorGetCurentScript()->getNameToFuncId("postprocess");
            _hModuleFloorScript = floorRegisterScriptModule(0xf, group, pre, main, post);
        }
        FloorModuleInterface_clear(&_floorModuleUniqueFunc);
        _floorUniqueFunc.pre = floorDataBiosGetPreFunc(floor);
        _floorUniqueFuncThread = floorDataBiosGetMainFunc(floor);
        _floorUniqueFunc.main = 0;
        _floorUniqueFunc.post = floorDataBiosGetPostFunc(floor);
        _floorModuleUniqueFunc.pre = _floorUniqueInitialize;
        _floorModuleUniqueFunc.thread = _floorUniqueUpdate;
        _floorModuleUniqueFunc.post = _floorUniqueFinalize;
        _floorModuleUniqueFunc.getName = _floorGetUniqueModuleName;
        _hModuleUniqueFunc = floorRegisterModule(0xf, group, &_floorModuleUniqueFunc);
        floorSound_playEnvSound(1);
        floorSound_playSound();
    } else {
        _floorUniqueFunc.pre = floorDataBiosGetPreFunc(floor);
        _floorUniqueFuncThread = floorDataBiosGetMainFunc(floor);
        _floorUniqueFunc.main = 0;
        _floorUniqueFunc.post = floorDataBiosGetPostFunc(floor);
    }
    FloorBgmMask *mask = floorSound_getBgmMaskObj();
    if (mask != 0) mask->initialize();
}

static void _floorReleaseWazaSequence(GSfloor_dd_ *floor) {
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        battleCameraStop();
        battleGridReset();
        wazaSequenceSysRelease();
        break;
    }
}

static void _floorUpdateWazaSequence(GSfloor_dd_ *floor) {
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        wazaSequenceSysUpdate();
        battleCameraUpdate();
        cameraUpdate();
        break;
    }
}

extern "C" {
void floorInitWazaSequence(u32 a) {
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4:
    case 5:
    case 6:
        battleGridReset();
        wazaSequenceSysInit();
        if (floorDataBiosGetFloorKind(floor) == 2) wazaSequenceSysInitExtras();
        battleCameraInit(floor);
        break;
    }
}
}

static void _floorInitShadow(GSfloor_dd_ *floor) {
    GSmodelSetShadowToCameraHeightCheck(0);
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
        if (floor->floorID == 0x84) GSmodelSetShadowToCameraHeightCheck(1);
        GSmodelSetShadowBoundExpansion(4.0f);
        GSmodelSetShadowDistLimits(400.0f, 350.0f);
        switch (floor->floorID) {
        case 0x3b:
        case 0x3c:
        case 0x3d:
            GSmodelSetShadowCutoffDist(1000.0f);
            GSmodelSetShadowTextureSize(0x280, 0x1e0);
            return;
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x47:
        case 0xad:
            GSmodelSetShadowDistLimits(700.0f, 650.0f);
        default:
            GSmodelSetShadowCutoffDist(70.0f);
            GSmodelSetShadowTextureSize(0x180, 0x180);
            break;
        }
        break;
    case 2:
        GSmodelSetShadowTextureSize(0x200, 0x200);
        GSmodelSetShadowCutoffDist(90.0f);
        GSmodelSetShadowBoundExpansion(7.0f);
        GSmodelSetShadowDistLimits(20000.0f, 10000.0f);
        break;
    case 4:
        GSmodelSetShadowTextureSize(0x200, 0x200);
        GSmodelSetShadowCutoffDist(80.0f);
        GSmodelSetShadowBoundExpansion(3.0f);
        GSmodelSetShadowDistLimits(20000.0f, 10000.0f);
        break;
    case 3:
    case 5:
    case 6:
        break;
    }
}

static void _floorInitScene(GSfloor_dd_ *floor) {
    f32 fov, aspect, near, far;
    void *camera2;
    floorDataBiosGetGroupID(floor);
    if (floorDataBiosGetMapResID(floor) != 0) {
        u32 i = 0;
        GSfloor_dd_ *cur = floorDataBiosGetCurrentPtr();
        SceneData *scene = (SceneData *)HSD_ArchiveGetPublicAddress(GSresGetResource(floorGetCurrentGroupID(), cur->mapResourceID), "scene_data");
        if (scene != 0) {
            if (scene->models != 0) {
                u32 base = floorReadMakeModelResID(cur->mapResourceID);
                for (; scene->models[i] != 0; i++) {
                    void *m = GSresGetResource(floorGetCurrentGroupID(), base | i);
                    if (m != 0) GSmodelSetVisibility(m, 1);
                }
            }
        }
    }
    u32 lensFlareID = floorDataBiosGetLensFlareResID(floor);
    if (lensFlareID != 0) {
        void *flare = GSresGetResource(floorGetCurrentGroupID(), lensFlareID);
        if (flare != 0) {
            u32 sunID = floorDataBiosGetSunResID(floor);
            GSlensFlareSetVisible(flare, 0);
            if (sunID != 0) {
                GSvec sunPos;
                void *sun = GSresGetResource(floorGetCurrentGroupID(), sunID);
                if (sun != 0) {
                    GSmodelGetPosition(sun, &sunPos);
                    GSlensFlareSetSunPosition(flare, &sunPos);
                    GSlensFlareSetVisible(flare, 1);
                }
            }
        }
    }
    void *camera = GScameraGetActiveCamera();
    if (camera != 0) {
        GScameraGetPerspective(camera, &fov, &aspect, &near, &far);
        aspect = 1.18f;
        GScameraSetPerspective(camera, fov, aspect, near, far);
    }
    camera2 = GSresGetResource(0, 0);
    if (camera2 != 0) {
        GScameraGetPerspective(camera2, &fov, &aspect, &near, &far);
        aspect = 1.18f;
        GScameraSetPerspective(camera2, fov, aspect, near, far);
    }
}

static void _floorInitMapFog(GSfloor_dd_ *floor) {
    GSgfxColAu8 black = {0, 0, 0, 0};
    u32 group;
    u32 mapRes;
    FogRange *range;
    GSgfxFogType type;
    FogData *fog;
    GSgfxLayer *layer0;
    GSgfxLayer *layer2;
    fog = 0;
    switch (floorDataBiosGetFloorKind(floor)) {
    case 1:
    case 2:
    case 4: {
        group = floorDataBiosGetGroupID(floor);
        mapRes = floorDataBiosGetMapResID(floor);
        u32 fogID = floorReadMakeFogResID(mapRes);
        if (fogID != 0) fog = (FogData *)GSresGetResource(group, fogID);
        layer0 = GSgfxLayerFindByID(0);
        layer2 = GSgfxLayerFindByID(2);
        if (fog != 0) {
            switch (fog->type) {
            case 2:
            case 10:
                type = (GSgfxFogType)2;
                break;
            case 4:
            case 12:
                type = (GSgfxFogType)4;
                break;
            case 5:
            case 13:
                type = (GSgfxFogType)5;
                break;
            case 6:
            case 14:
                type = (GSgfxFogType)6;
                break;
            case 7:
            case 15:
                type = (GSgfxFogType)7;
                break;
            default:
                return;
            }
            range = fog->range;
            layer0->setFog(type, fog->start, fog->end, fog->color);
            layer2->setFog(type, fog->start, fog->end, fog->color);
            if (range != 0) {
                layer0->setFogRange(true, range->range);
                layer2->setFogRange(true, range->range);
            } else {
                layer0->setFogRange(false, 0xFFFF);
                layer2->setFogRange(false, 0xFFFF);
            }
            layer0->fog(true);
            layer2->fog(true);
            GSgfxVideoSetClearColor(fog->color);
            u32 j = 0;
            SceneData *scene = (SceneData *)HSD_ArchiveGetPublicAddress(GSresGetResource(group, mapRes), "scene_data");
            if (scene != 0) {
                if (scene->models != 0) {
                    u32 base = floorReadMakeModelResID(mapRes);
                    for (u32 i = 0; scene->models[i] != 0; i++, j++) {
                        u32 id = base | j;
                        void *m = GSresGetResource(group, id);
                        if (m != 0) {
                            s32 state = floorDataBiosModelIDGetFogState(id);
                            GSmodelSetFogState(m, state, state);
                        }
                    }
                }
            }
        } else {
            layer0->setFog((GSgfxFogType)2, 0.0f, 5000.0f, black);
            layer0->setFogRange(false, 0xFFFF);
            layer0->fog(false);
            layer2->setFog((GSgfxFogType)2, 0.0f, 5000.0f, black);
            layer2->setFogRange(false, 0xFFFF);
            layer2->fog(false);
            GSgfxVideoSetClearColor(black);
        }
        break;
    }
    case 3:
    case 5:
    case 6:
        break;
    }
}

static void _floorInitTresure(GSfloor_dd_ *floor) {
    GSvec pos;
    GSvec rot;
    void *p;
    FloorTresureEntry *t;
    u32 i;
    u32 group;
    u32 human;
    u32 objID;
    u32 res;
    u32 count;
    count = 0;
    group = floorDataBiosGetGroupID(floor);
    for (i = 0; i < *floor_tresure_list_number; i++) {
        t = &floor_tresure_list[i];
        if (t->floorID == floor->floorID) {
            switch (t->kind) {
            case 1:
                res = 0x2f80400;
                break;
            case 2:
                res = 0x2f90400;
                break;
            case 3:
                res = 0x2fa0400;
                break;
            }
            objID = count++ | 0x7fff0000;
            if (floorIsPop() == 0) {
                human = peopleOpen(group, objID, res);
            } else {
                human = peopleGetHumanID(group, objID);
            }
            if (human != 0 && floorIsPop() != 1) {
                p = peopleGet(group, objID);
                pos.set(t->x, t->y, t->z);
                peopleSetPos(group, objID, &pos);
                rot.set(0.0f, 0.017453292f * t->rotation, 0.0f);
                peopleSetRot(group, objID, &rot);
                peopleAddCollision(group, objID);
                peopleSetFlagOn(group, objID, 4);
                peopleSetDisp(group, objID, 1);
                peopleManualAnimation(group, objID);
                if (p != 0) peopleBiosSetTresureID(p, (u16)i);
                if (t->kind == 2) {
                    void *m = GSresGetResource(group, objID);
                    if (m != 0) GSmodelClearShadowFlags(m, 1);
                }
                if (t->flagA != 0) {
                    if (GSflagTest(t->flagA)) {
                        floorEventCtrlTresure(group, objID, 0);
                    } else {
                        floorEventCtrlTresure(group, objID, 1);
                        if (t->flagB != 0) {
                            if (!GSflagTest(t->flagB)) peopleSetDisp(group, objID, 0);
                            peopleExecMoveScript(group, objID, 0x596000b, t->flagA, t->flagB);
                        }
                    }
                }
            }
        }
    }
}

static void _floorInitDoor(GSfloor_dd_ *floor) {
    u32 i;
    for (i = 0; i < *floor_door_list_number; i++) {
        FloorDoorEntry *d = &floor_door_list[i];
        if (d->floorID == floor->floorID) {
            switch (d->type) {
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                if (GSflagTest(d->flag)) {
                    floorEventCtrlDoor(floor->floorID, i, 1);
                } else {
                    floorEventCtrlDoor(floor->floorID, i, 3);
                }
                break;
            case 2:
                floorEventCtrlDoor(floor->floorID, i, 3);
                break;
            }
        }
    }
}

static void _floorInitCharacters(GSfloor_dd_ *floor) {
    GSvec a;
    GSvec b;
    u32 group = floorDataBiosGetGroupID(floor);
    u32 count = floorDataBiosGetCharNum(floor);
    for (u32 i = 0; i < count; i++) {
        floorCharacter_dd_ *c = floorCharacterBiosGetCurrentPtr(i);
        u32 res = peopleInfoBiosGetModelResID(floorCharacterBiosGetPeopleInfoPtr(c));
        if (floorCharacterBiosGetLoadInit(c)) {
            u32 h;
            if (floorIsPop() == 0) {
                h = peopleOpen(group, i, res);
            } else {
                h = peopleGetHumanID(group, i);
            }
            if (h == 0) {
                GSlogWrite("Error! [%s] \x90\x6C\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n", __FUNCTION__);
            } else if (floorIsPop() != 1) {
                _floorInitCharactor(group, i, h);
            }
        }
    }
}

static void _floorInitCharactor(u32 group, u32 idx, u32 arg) {
    GSvec pos;
    GSvec rot;
    u32 script;
    floorCharacter_dd_ *c = floorCharacterBiosGetCurrentPtr(idx);
    script = peopleGetMoveSctID(group, idx);
    if (!floorIsContinueMode()) peopleExecMoveScript(group, idx, script, arg, 0);
    peopleSetFlagOn(group, idx, 4);
    peopleSetFlagOn(group, idx, 8);
    floorCharacterBiosGetPos(c, &pos);
    peopleSetPos(group, idx, &pos);
    floorCharacterBiosGetRot(c, &rot);
    peopleSetRot(group, idx, &rot);
    peopleAddCollision(group, idx);
    peopleSetDisp(group, idx, floorCharacterBiosGetVisibility(c));
    peopleSetCollision(group, idx, floorCharacterBiosGetIsHit(c));
    switch (floorCharacterBiosGetMoveType(c)) {
    case 2:
        peopleStartWalkRandom(group, idx, 15.0f);
        break;
    case 3:
        peopleStartRotRandom(group, idx, 5.0f, 3.0f);
        break;
    case 0:
    case 1:
    default:
        break;
    }
    switch (floorCharacterBiosGetTalkStartType(c)) {
    case 1:
        peopleSetFlagOn(group, idx, 0x10);
        break;
    case 2:
        peopleSetFlagOn(group, idx, 0x20);
        break;
    case 0:
    default:
        break;
    }
    switch (floorCharacterBiosGetTalkEndType(c)) {
    case 0:
        peopleSetFlagOff(group, idx, 0x40);
        break;
    case 1:
        peopleSetFlagOn(group, idx, 0x40);
        break;
    }
    if (c->neckTarget) peopleMoveNeckTargetHero(group, idx, 1.0f);
}

extern "C" {
void floorInitMap(u32 group, u32 mapRes) {
    const struct {
        u32 v;
    } layerA = {0};
    const struct {
        u32 v;
    } layerB = {4};
    u32 i = 0;
    u32 j = 0;
    if (mapRes != 0) {
        SceneData *scene = (SceneData *)HSD_ArchiveGetPublicAddress(GSresGetResource(group, mapRes), "scene_data");
        if (scene != 0) {
            if (scene->models != 0) {
                u32 base = floorReadMakeModelResID(mapRes);
                for (; scene->models[i] != 0; i++) {
                    u32 resID = base | i;
                    void *m = floorOpenObject(resID);
                    if (m == 0) {
                        GSlogWrite("Error! %s: couldn't load model %d\n", __FUNCTION__, i);
                        GSlogWrite("\x83\x7D\x83\x62\x83\x76\x83\x82\x83\x66\x83\x8B\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n");
                    } else {
                        GSresFreeResource(group, resID);
                        GSresRegisterResource(m, group, resID, _floorUnloadModel);
                        GSmodelSetVisibility(m, 0);
                        if (!GSmodelCanAnimate(m)) GSmodelSetBoundCheck(m, 1);
                        GSmodelSetRenderLayer(m, 1, &layerA);
                        if (pokecoloGetCountryCode() == 1) {
                            switch (GSfloorGetCurrent()) {
                            case 0x3a:
                            case 0x3b:
                            case 0x5e:
                            case 0x5f:
                            case 0x64:
                            case 0x69:
                            case 0x6a:
                            case 0x74:
                            case 0x7d:
                            case 0x7e:
                            case 0x84:
                            case 0x1f6:
                            case 0x1fc:
                            case 0x20a:
                                if (GSmodelCanAnimate(m)) {
                                    GSmodelLinkTexAnimToAnim(m, 0);
                                    GSmodelSetTexAnimRate(m, 0.35f);
                                }
                                break;
                            }
                        }
                    }
                }
            }
            if (scene->lights != 0) {
                u32 base = floorReadMakeLightResID(mapRes);
                for (; scene->lights[j] != 0; j++) {
                    void *l = GSresGetResource(group, base | j);
                    if (l != 0) {
                        GSlightSetActive(l, 1);
                        if (GSlightCanAnimate(l)) {
                            GSlightSetAnimIndex(l, 0);
                            GSlightSetAnimRate(l, 0.5f);
                            GSlightStartAnimation(l);
                        }
                    }
                }
            }
            u32 camID = floorReadMakeCameraResID(mapRes);
            void *cam = GSresGetResource(group, camID);
            if (cam != 0) cameraSetGScamera(cam);
            GSfloor_dd_ *fd = floorDataBiosGetPtr(floorGetCurrent());
            if (fd != 0) {
                u32 n = floorDataBiosGetSecondaryRenderNum(fd);
                for (u32 k = 0; k < n; k++) {
                    u32 id = floorDataBiosGetSecondaryRenderID(fd, k);
                    if (id != 0) GSmodelSetRenderLayer(GSresGetResource(group, id), 1, &layerB);
                }
            }
        }
    }
}

void floorChangePos(u32 floorID, s32 rotation, f32 x, f32 y, f32 z) {
    if (floorID != 0) {
        _floorChangeInfo.position.set(x, y, z);
        _floorChangeInfo.rotation.set(0.0f, 0.017453292f * (s16)rotation, 0.0f);
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        _floorChangeInfo.useInitPosition = 0;
        GSfloorChange(floorID);
    }
}

void floorLink(u32 floorID, u32 posIndex) {
    floorLinkWithSE(floorID, posIndex, 0);
}

void floorLinkWithSE(u32 floorID, u32 posIndex, s32 se) {
    GSfloor_dd_ *next;
    GSfloor_dd_ *cur;
    Hero *hero;
    u32 snd;
    if (floorID != 0) {
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        if (floorIsContinueMode() && floorCheckAnywaySaveData()) {
            hero = Hero::getHeroPtr();
            GSvec p;
            s16 r;
            hero->getRestertPos(&p, r);
            _floorChangeInfo.position.set(p.x, p.y, p.z);
            _floorChangeInfo.rotation.set(0.0f, 0.017453292f * r, 0.0f);
            _floorChangeInfo.useInitPosition = 0;
        } else {
            _floorChangeInfo.useInitPosition = 1;
            _floorChangeInfo.nextPosIndex = posIndex;
        }
        cur = floorDataBiosGetPtr(GSfloorGetCurrent());
        next = floorDataBiosGetPtr(floorID);
        if (floorDataBiosGetFileGroupID(next) != floorDataBiosGetFileGroupID(cur)) GSfsysPreRead(floorDataBiosGetFileGroupID(next));
        switch (se) {
        case 0:
            snd = 0;
            break;
        case 1:
        default:
            snd = 0x1c;
            break;
        }
        if (snd != 0) GSsndPlayNow(snd);
        floorChange(floorID);
    }
}

u32 floorGetNextPosIndex() {
    return _floorChangeInfo.nextPosIndex;
}

u32 floorGetNextFloorID() {
    return _floorChangeInfo.nextFloorID;
}

u32 floorGetPrevFloorID() {
    return _floorChangeInfo.prevFloorID;
}

void floorSetPrevFloorID(u32 id) {
    _floorChangeInfo.prevFloorID = id;
}

u32 floorGetPlaceName(u32 floorID) {
    switch (floorID) {
    case 0xff:
    case 0x258:
    case 0x259:
        return 0;
    }
    GSfloor_dd_ *fd = floorDataBiosGetPtr(floorID);
    if (fd == 0) return 0;
    return floorDataBiosGetPlaceName(fd);
}
}

static void _floorSetInitPosition() {
    FloorPosition *p = 0;
    if (_floorChangeInfo.useInitPosition) {
        FloorPositionList *list = floorDataBiosGetPosListPtr(floorDataBiosGetCurrentPtr());
        if (list != 0) {
            if (_floorChangeInfo.nextPosIndex < *list->count) p = &list->entries[_floorChangeInfo.nextPosIndex];
        }
        if (p != 0) {
            _floorChangeInfo.position.set(p->x, p->y, p->z);
            _floorChangeInfo.rotation.set(0.0f, 0.017453292f * p->rotation, 0.0f);
        } else {
            _floorChangeInfo.position.clear();
            _floorChangeInfo.rotation.clear();
        }
        _floorChangeInfo.useInitPosition = 0;
    }
}

static void _floorClearFlag() {
    u32 a = 0;
    u32 b = 0;
    if (floorIsPop() != 1 && floorIsPush() != 1 && !floorIsFloorPushed() && !floorIsContinueMode() && _floorChangeInfo.prevFloorID != 0x384) {
        GSflagClear(1);
        GSfloor_dd_ *prev = floorDataBiosGetPtr(_floorChangeInfo.prevFloorID);
        if (prev != 0) a = floorDataBiosGetArea(prev);
        if (prev->kind != 2) {
            GSfloor_dd_ *next = floorDataBiosGetPtr(_floorChangeInfo.nextFloorID);
            if (next != 0) b = floorDataBiosGetArea(next);
            if ((u8)a != (u8)b) GSflagClear(2);
        }
    }
}

static void _floorFinalize(unsigned int a, FloorEnterMode mode) {
    if (mode == 1) return;
}

static void _floorUpdate(unsigned int a, FloorEnterMode mode) {
    u8 drawn = 0;
    GSmtx m1;
    GSmtx::makeIdentity();
    floorUpdateFieldCamera();
    floorUpdateOffscreen();
    u8 *flag = (u8 *)GSresGetResource(0, 2);
    if (flag != 0 && *flag != 0) {
        EvlogPrint();
        GScolsys2Draw(&m1);
        drawn = 1;
    }
    if (floorGetHumanColision() && !drawn) GScolsys2HumanDispColision();
}

static void _floorInitialize(unsigned int a, FloorEnterMode mode) {
    GSfloor_dd_ *floor = floorDataBiosGetPtr(a);
    heroMoveInit(&_floorChangeInfo.position, &_floorChangeInfo.rotation);
    if (mode != 2) {
        _floorInitCharacters(floor);
        _floorInitDoor(floor);
        _floorInitTresure(floor);
        GSvec ofs;
        ofs.set(0.0f, 14.0f, 0.0f);
        cameraSetType(0);
        if (cameraGetDistance() < 0.00001f) {
            if (cameraGetDistance() > -0.00001f) cameraSetDistance(89.5f);
        }
        cameraSetTarget(0, 100);
        cameraSetTargetOfs(&ofs);
    }
    cameraUpdate();
    GSinputResetLeftSmoothing(1, 0, 0);
    GSinputResetRightSmoothing(1, 0, 0);
    if (mode == 2) {
        floorExecScriptIntegerByName("pushpop_preprocess", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
    }
}

static const char *_floorGetUniqueModuleName() {
    return "floorUniqueModule";
}

static const char *_floorGetMenuModuleName() {
    return "floorMenuModule";
}

static const char *_floorGetFieldModuleName() {
    return "floorFiledModule";
}

static s32 _floorUnloadModel(void *model, u32 a, u32 b) {
    GSmodelFree(model);
    return 1;
}

extern "C" {
void *floorOpenModel(u32 a, u32 objID) {
    return floorOpenObject(objID);
}

void *floorOpenObject(u32 objID) {
    u8 isScene = 0;
    switch (objID) {
    case 3:
    case 0x64:
        objID = (u32)GSresGetResource(0, 0x64);
        break;
    case 4:
    case 0x65:
        objID = (u32)GSresGetResource(0, 0x65);
        break;
    default:
        if (((objID >> 9) & 0x3f) == 2) isScene = 1;
        break;
    }
    if (objID == 0) {
        GSlogWrite("Error!! %s: objID is zero\n", __FUNCTION__);
        return 0;
    }
    void *archive = GSresGetResourceAllGroup(objID);
    if (archive == 0) archive = floorReadResourceID(0x9a, objID);
    if (archive == 0) return 0;
    if (isScene) {
        if (archive == 0) {
            GSlogWrite("%s: got NULL pointer archive\n", __FUNCTION__);
            GSlogWrite("objID : %08x\n", objID);
            while (1) GSthreadSwitch();
        }
        SceneData *scene = (SceneData *)HSD_ArchiveGetPublicAddress(archive, "scene_data");
        if (scene == 0) {
            GSlogWrite("%s: got NULL pointer scene descriptor\n", __FUNCTION__);
            GSlogWrite("objID : %08x\n", objID);
            while (1) GSthreadSwitch();
        }
        archive = scene->models[0];
        if (archive == 0) {
            GSlogWrite("%s: couldn't load model\n", __FUNCTION__);
            GSlogWrite("objID : %d\n", objID);
            while (1) GSthreadSwitch();
        }
    }
    void *model = GSmodelLoad(archive, 0);
    if (model == 0) {
        GSlogWrite("Error! %s: couldn't load model %d\n", __FUNCTION__);
        GSlogWrite("\x83\x82\x83\x66\x83\x8B\x82\xCC\x8F\x89\x8A\xFA\x89\xBB\x82\xC9\x8E\xB8\x94\x73\n");
    } else {
        GSmodelSetVisibility(model, 1);
        if (GSmodelCanAnimate(model)) {
            GSmodelSetAnimIndex(model, 0);
            GSmodelSetAnimRate(model, 0.5f);
            GSmodelStartAnimation(model);
        }
        if (GSmodelCanTexAnimate(model)) {
            GSmodelSetTexAnimIndex(model, 0);
            GSmodelSetTexAnimRate(model, 0.5f);
            GSmodelStartTexAnimation(model);
        }
    }
    return model;
}

u32 floorGetCurrentGroupID() {
    return floorDataBiosGetGroupID(floorDataBiosGetCurrentPtr());
}

void *floorGetResource(u32 floorID, u32 resID) {
    GSfloor_dd_ *fd = floorDataBiosGetPtr(floorID);
    if (fd == 0) return 0;
    return GSresGetResource(floorDataBiosGetGroupID(fd), resID);
}

void floorReturnSavePoint() {
    u32 floor;
    u32 prev;
    u8 pos;
    if (_floorChangeInfo.returnValid) {
        floor = _floorChangeInfo.returnFloorID;
        prev = _floorChangeInfo.returnPrevFloorID;
        pos = _floorChangeInfo.returnPosIndex;
    } else {
        floor = gamedatasaveGetStatus(0, 5);
        prev = gamedatasaveGetStatus(0, 7);
        pos = gamedatasaveGetStatus(0, 8);
    }
    floorLinkWithSE(floor, pos, 0);
    _floorChangeInfo.prevFloorID = prev;
    floorClearReturnPoint();
}

u8 floorIsDispScriptInfo() {
    return _floorChangeInfo.dispScriptInfo;
}

void floorSetDispScriptInfo(u8 v) {
    _floorChangeInfo.dispScriptInfo = v;
}

u8 floorIsContinueMode() {
    return _floorChangeInfo.continueMode;
}

void floorSetContinueMode(u8 v) {
    _floorChangeInfo.continueMode = v;
}

void floorSetFloorChangeInfo(u32 floorID, u32 posIndex) {
    if (floorID != 0) {
        _floorChangeInfo.prevFloorID = GSfloorGetCurrent();
        _floorChangeInfo.nextFloorID = floorID;
        _floorChangeInfo.useInitPosition = 1;
        _floorChangeInfo.nextPosIndex = posIndex;
    }
}

void floorClearReturnPoint() {
    _floorChangeInfo.returnValid = 0;
}

s32 floorGetLocalHeapHandle() {
    return _floorLocalHeap;
}

u32 floorCreateLocalHeap() {
    void *lo = OSGetArenaLo();
    void *hi = (void *)((u32)lo + 0x18000);
    _floorLocalHeap = GSmemCreateHeap(lo, hi);
    if (_floorLocalHeap == -1) return 0;
    OSSetArenaLo(hi);
    return 1;
}
}

void EvlogPrint() {
    u8 *flag = (u8 *)GSresGetResource(0, 2);
    if (flag != 0 && *flag != 0) {
        s32 i;
        s32 y = 0x1e;
        for (i = 0; i < 10; i++) {
            EvLogEntry *e = &EvLog[(evlog_start + i) % 10];
            switch (e->type) {
            case 1:
                GSprint(dbgMenuGetLayerID(), 0x1e, y, 0x8080ffff, "PASS EVENT = %d", e->value);
                break;
            case 2:
                GSprint(dbgMenuGetLayerID(), 0x1e, y, 0x8080ffff, "TOUCH EVENT = %d", e->value);
                break;
            case 3:
                GSprint(dbgMenuGetLayerID(), 0x1e, y, 0x8080ffff, "CHECK EVENT = %d", e->value);
                break;
            }
            y += 12;
        }
    }
}

void EvlogSet(s8 type, u32 value) {
    EvLog[evlog_start].type = type;
    EvLog[evlog_start].value = value;
    evlog_start++;
    evlog_start = evlog_start % 10;
}
