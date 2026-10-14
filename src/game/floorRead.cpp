#include <game/floorReadPrivate.hpp>

static FloorPostCallManager _postFuncManager;
static u8 _floorReadingResource;

static void _fsysLoadCallbak(s32, void *, s32);
static void _registerCamera(u32, u32, _HSD_SceneDesc *);
static _HSD_SceneDesc *_makeArchiveHeader(u32, u32, u32);
static u8 _unloadDeckData(void *, u32, u32);
static u8 _unloadTextureForAnt(void *, u32, u32);
static u8 _unloadObject(void *, u32, u32);
static u8 _unloadWZX(void *, u32, u32);
static u8 _unloadPKX(void *, u32, u32);
static u8 _unloadGSW(void *, u32, u32);
static u8 _unloadFlare(void *, u32, u32);
static u8 _unloadParticles(void *, u32, u32);
static u8 _unloadCamera(void *, u32, u32);
static u8 _unloadLight(void *, u32, u32);
static u8 _unloadScript(void *, u32, u32);
static u8 _unloadFont(void *, u32, u32);
static u8 _unloadMsg(void *, u32, u32);
static u8 _unloadColsys(void *, u32, u32);
static u8 _unloadTexture(void *, u32, u32);

extern "C" {

void floorDelayPostFunc() {
    _postFuncManager.update();
}

void *floorReadResourceID(u32 group, u32 id) {
    if (group == 0) group = floorGetCurrentGroupID();
    void *res = GSresGetResource(group, id);
    if (res != 0) return res;
    if (_floorReadingResource) {
        while (_floorReadingResource) GSthreadSwitch();
    }
    _floorReadingResource = 1;
    while (!GSfsysReadIDEXWait(group, id, _fsysLoadCallbak, 0, id)) GSthreadSwitch();
    GSfsysFree(group);
    floorAddResource(group, id);
    res = GSresGetResource(group, id);
    _floorReadingResource = 0;
    return res;
}

static void _fsysLoadCallbak(s32, void *, s32) {}

void *floorRegisterCamera(u32 group, u32 id) {
    void *res = GSresGetResource(group, id);
    if (res == 0) return 0;
    _HSD_SceneDesc *scene = (_HSD_SceneDesc *)HSD_ArchiveGetPublicAddress(res, "scene_data");
    if (scene == 0) return 0;
    _registerCamera(group, floorReadMakeCameraResID(id), scene);
    return scene;
}

void *floorRegisterLight(u32 group, u32 id) {
    _HSD_SceneDesc *scene;
    u32 index = 0;
    void *res = GSresGetResource(group, id);
    if (res == 0) return 0;
    scene = (_HSD_SceneDesc *)HSD_ArchiveGetPublicAddress(res, "scene_data");
    if (scene == 0) return 0;
    if (scene->lights) {
        u32 base = floorReadMakeLightResID(id);
        for (u32 i = 0; scene->lights[i]; ++i, ++index) {
            void *light = GSlightLoad(scene->lights[i]);
            if (light) GSresRegisterResource(light, group, base | index, _unloadLight);
        }
    }
    return scene;
}

void *floorReadDeckPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (res) deckRegister(group, id);
    return res;
}

void *floorReadDeckPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadDeckData);
    GSresLockResource(group, id);
    return res;
}

static u8 _unloadDeckData(void *, u32 group, u32 id) {
    deckUnRegister(group, id);
    return 1;
}

void *floorReadAntPostFunc(u32 group, u32 id, u32 extra) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    antReadPostFunc(res, extra);
    GStextureLoad(antGetGStexture(res));
    return res;
}

void *floorReadAntPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadTextureForAnt);
    GSresLockResource(group, id);
    return res;
}

static u8 _unloadTextureForAnt(void *p, u32, u32) {
    GStextureFree(antGetGStexture(p));
    return 1;
}

void *floorReadGSWPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    FlashSystemInit(id, res);
    return res;
}

void *floorReadGSWPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadGSW);
    GSresLockResource(group, id);
    return res;
}

void *floorReadEncodeRelPostFunc(u32 group, u32 id, u32 extra) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    GSfsysOSLinkPostFunc(group, id, extra);
    return res;
}

void *floorReadEncodeRelPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    if (res == 0) return 0;
    GSresLockResource(group, id);
    return res;
}

void *floorReadGFLPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    GSresGetResource(group, id);
    void *res = GSresGetResource(group, floorReadMakeObjResID(id));
    void *flare = GSlensFlareLoad(res);
    if (flare) GSresRegisterResource(flare, group, id, _unloadFlare);
    return res;
}

void *floorReadGFLPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

void *floorReadBGMPostFunc() {
    return 0;
}

void *floorReadBGMPreFunc(u32 group, u32 id, u32 size) {
    return floorReadNormalPreFunc(group, id, size);
}

void *floorReadNotLinkedParticlePostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, floorReadMakeObjResID(id));
    void *particle = GSparticleLoad(res);
    if (particle) GSresRegisterResource(particle, group, id, _unloadParticles);
    return res;
}

void *floorReadNotLinkedParticlePreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

void *floorReadParticlePostFunc(u32 group, u32 id, u32 extra) {
    FloorReadData *data;
    void *map;
    void *res;
    void *particle;
    u32 index = 0;
    data = floorDataBiosGetCurrentPtr();
    map = GSresGetResource(floorGetCurrentGroupID(), data->mapResourceID);
    if (map == 0) {
        _postFuncManager.add(group, id, extra, floorReadParticlePostFunc);
        return 0;
    }
    GSresUnlockResource(group, id);
    res = GSresGetResource(group, floorReadMakeObjResID(id));
    particle = GSparticleLoad(res);
    if (particle) {
        GSresRegisterResource(particle, group, id, _unloadParticles);
        data = floorDataBiosGetCurrentPtr();
        map = GSresGetResource(floorGetCurrentGroupID(), data->mapResourceID);
        if (map == 0) return 0;
        _HSD_SceneDesc *scene = (_HSD_SceneDesc *)HSD_ArchiveGetPublicAddress(map, "scene_data");
        if (scene == 0) return 0;
        if (scene->jobjs) {
            u32 base = floorReadMakeModelResID(data->mapResourceID);
            for (u32 i = 0; scene->jobjs[i]; ++i, ++index) {
                void *model = GSresGetResource(floorGetCurrentGroupID(), base | index);
                if (model) GSmodelLinkToGSparticleBank(model, particle);
            }
        }
    }
    return res;
}

void *floorReadParticlePreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, floorReadMakeObjResID(id), 0);
    GSresLockResource(group, id);
    return res;
}

void *floorReadWZXPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (res == 0) return 0;
    if (WazaSequence::Load((u8 *)res, group, id)) return res;
    return 0;
}

void *floorReadWZXPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadWZX);
    GSresLockResource(group, id);
    return res;
}

void *floorReadPKXPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (res == 0) return 0;
    if (ModelSequence_Load(res, group, id)) return res;
    return 0;
}

void *floorReadPKXPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadPKX);
    if (res == 0) return 0;
    GSresIsUniqueID(group, id, 0);
    GSresLockResource(group, id);
    return res;
}

void *floorReadTexPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    GStextureLoad(res);
    return res;
}

void *floorReadTexPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadTexture);
    GSresLockResource(group, id);
    return res;
}

void *floorReadColPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    GScolsys2LoadCCD(res);
    return res;
}

void *floorReadColPreFunc(u32 group, u32 id, u32 size) {
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadColsys);
    GSresLockResource(group, id);
    return res;
}

void *floorReadCameraPostFunc(u32 group, u32 id, u32 extra) {
    _HSD_SceneDesc *scene = _makeArchiveHeader(group, floorReadMakeObjResID(id), extra);
    _registerCamera(group, id, scene);
    return scene;
}

void *floorReadCameraPreFunc(u32 group, u32 id, u32 size) {
    u8 *res = (u8 *)GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, floorReadMakeObjResID(id), 0);
    if (res == 0) return 0;
    GSresLockResource(group, id);
    return res + 0x60;
}

void *floorReadObjPostFunc(u32 group, u32 id, u32 extra) {
    _HSD_SceneDesc *scene;
    u32 index = 0;
    scene = _makeArchiveHeader(group, id, extra);
    if (scene == 0) return 0;
    u32 base = floorReadMakeModelResID(id);
    if (scene->jobjs) {
        for (u32 i = 0; scene->jobjs[i]; ++i, ++index) {
            GSresRegisterResource(scene->jobjs[i], group, base | index, 0);
        }
    }
    return scene;
}

void *floorReadObjPreFunc(u32 group, u32 id, u32 size) {
    u8 *res = (u8 *)GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, id, _unloadObject);
    if (res == 0) return 0;
    GSresLockResource(group, id);
    return res + 0x60;
}

void *floorReadMapPostFunc(u32 group, u32 id, u32 extra) {
    _HSD_SceneDesc *scene;
    u32 modelIndex = 0;
    u32 lightIndex = 0;
    u32 base;
    u32 i;
    scene = _makeArchiveHeader(group, id, extra);
    if (scene == 0) return 0;
    if (scene->jobjs) {
        base = floorReadMakeModelResID(id);
        for (i = 0; scene->jobjs[i]; ++i, ++modelIndex) {
            GSresRegisterResource(scene->jobjs[i], group, base | modelIndex, 0);
        }
    }
    if (scene->lights) {
        base = floorReadMakeLightResID(id);
        for (i = 0; scene->lights[i]; ++i, ++lightIndex) {
            void *light = GSlightLoad(scene->lights[i]);
            if (light) GSresRegisterResource(light, group, base | lightIndex, _unloadLight);
        }
        floorSetLightInfo(base, lightIndex);
    } else {
        floorSetLightInfo(0, 0);
    }
    _registerCamera(group, floorReadMakeCameraResID(id), scene);
    if (scene->fogs && scene->fogs[0]) {
        GSresRegisterResource(scene->fogs[0], group, floorReadMakeFogResID(id), 0);
    }
    floorInitMap(group, id);
    return scene;
}

void *floorReadMapPreFunc(u32 group, u32 id, u32 size) {
    u8 *res = (u8 *)GSresAllocResourceAlign(((size + 0x1F) & ~0x1F) + 0x60, 0x20, group, id, 0);
    if (res == 0) return 0;
    floorDataBiosSetMapResID(floorDataBiosGetCurrentPtr(), id);
    GSresLockResource(group, id);
    return res + 0x60;
}

void *floorReadScriptPostFunc(u32 group, u32 id) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (!floorIsPop() && res) {
        floorMappingScript(res);
        if (!floorSound_playEnvSound(0)) soundStopEnv(0);
        floorExecSoundScript();
    }
    return res;
}

void *floorReadScriptPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop()) return 0;
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadScript);
    GSresLockResource(group, id);
    return res;
}

void *floorReadFontPostFunc(u32 group, u32 id) {
    if (floorIsPop()) return 0;
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (res) GSmsgFontOpen(res);
    return res;
}

void *floorReadFontPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop()) return 0;
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadFont);
    GSresLockResource(group, id);
    return res;
}

void *floorReadMsgPostFunc(u32 group, u32 id) {
    if (floorIsPop()) return 0;
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    if (fn_8010B208(res) != pokecoloGetLanguage()) {
        GSresFreeResource(group, id);
        return res;
    }
    if (res) GSmsgOpen(res);
    return res;
}

void *floorReadMsgPreFunc(u32 group, u32 id, u32 size) {
    if (floorIsPop()) return 0;
    void *res = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, _unloadMsg);
    GSresLockResource(group, id);
    return res;
}

void *floorReadNormalPreFunc(u32 group, u32 id, u32 size) {
    return GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
}

static void _registerCamera(u32 group, u32 id, _HSD_SceneDesc *scene) {
    if (scene) {
        void *camera = GScameraLoad(scene->cameras);
        if (camera) GSresRegisterResource(camera, group, id, _unloadCamera);
    }
}

static _HSD_SceneDesc *_makeArchiveHeader(u32 group, u32 id, u32 extra) {
    GSresUnlockResource(group, id);
    void *res = GSresGetResource(group, id);
    u8 *data = (u8 *)res;
    HSD_ArchiveParse(res, data + 0x60, extra);
    return (_HSD_SceneDesc *)HSD_ArchiveGetPublicAddress(data, "scene_data");
}

static u8 _unloadObject(void *, u32 group, u32 id) {
    u32 index = 0;
    void *res = GSresGetResource(group, id);
    if (res == 0) return 0;
    _HSD_SceneDesc *scene = (_HSD_SceneDesc *)HSD_ArchiveGetPublicAddress(res, "scene_data");
    u32 base = floorReadMakeModelResID(id);
    if (scene->jobjs) {
        for (u32 i = 0; scene->jobjs[i]; ++i, ++index) {
            GSresFreeResource(group, base | index);
        }
    }
    return scene != 0;
}

static u8 _unloadWZX(void *p, u32, u32) {
    WazaSequence::Unload((u8 *)p);
    return 1;
}

static u8 _unloadPKX(void *p, u32, u32) {
    if (p) ModelSequence::Unload((u8 *)p);
    return 1;
}

static u8 _unloadGSW(void *, u32, u32 id) {
    FlashSystemRelease(id);
    return 1;
}

static u8 _unloadFlare(void *p, u32, u32) {
    GSlensFlareFree(p);
    return 1;
}

static u8 _unloadParticles(void *p, u32, u32) {
    GSparticleFree(p);
    return 1;
}

static u8 _unloadCamera(void *p, u32, u32) {
    GScameraFree(p);
    return 1;
}

static u8 _unloadLight(void *p, u32, u32) {
    GSlightFree(p);
    return 1;
}

static u8 _unloadScript(void *p, u32, u32) {
    if (floorIsPush()) return 0;
    floorUnmappingScript(p);
    return 1;
}

static u8 _unloadFont(void *p, u32, u32) {
    if (floorIsPush()) return 0;
    GSmsgFontClose(p);
    return 1;
}

static u8 _unloadMsg(void *p, u32, u32) {
    if (floorIsPush()) return 0;
    GSmsgClose(p);
    return 1;
}

static u8 _unloadColsys(void *p, u32, u32) {
    GScolsys2UnloadCCD(p);
    return 1;
}

static u8 _unloadTexture(void *p, u32, u32) {
    GStextureFree(p);
    return 1;
}

u32 floorReadMakeFogResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1A00;
}

u32 floorReadMakeCameraResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1800;
}

u32 floorReadMakeLightResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1600;
}

u32 floorReadMakeModelResID(u32 id) {
    return (id & 0x7FFF0000) | 0x1000;
}

u32 floorReadMakeObjResID(u32 id) {
    return (id & 0x7FFF0000) | 0x400;
}

}

void FloorPostCallManager::update() {
    for (Entry *e = entries; e != entries + 8; ++e) {
        if (e->used) {
            e->func(e->a, e->b, e->c);
            memset(e, 0, sizeof(Entry));
        }
    }
}

void FloorPostCallManager::add(u32 a, u32 b, u32 c, void *(*func)(u32, u32, u32)) {
    for (Entry *e = entries; e != entries + 8; ++e) {
        if (e->used == 0) {
            e->used = 1;
            e->a = a;
            e->b = b;
            e->c = c;
            e->func = func;
            return;
        }
    }
}

FloorPostCallManager::FloorPostCallManager() {
    memset(this, 0, sizeof(*this));
}
