#ifndef FLOOR_READ_PRIVATE_HPP
#define FLOOR_READ_PRIVATE_HPP
#include <dolphin/types.h>

typedef u8 (*FloorReadFreeFunc)(void *, u32, u32);

struct _HSD_SceneDesc {
    void **jobjs;
    void *cameras;
    void **lights;
    void **fogs;
};

struct FloorReadData {
    u32 reserved0;
    u32 mapResourceID;
};

struct WazaSequence {
    static u8 Load(u8 *, u32, u32);
    static void Unload(u8 *);
};
struct ModelSequence {
    static void Unload(u8 *);
};

struct FloorPostCallManager {
    struct Entry {
        u32 used;
        u32 a, b, c;
        void *(*func)(u32, u32, u32);
    };
    Entry entries[8];
    void update();
    void add(u32, u32, u32, void *(*)(u32, u32, u32));
    FloorPostCallManager();
};

void antReadPostFunc(void *, u32);
void *antGetGStexture(void *);

extern "C" {
void *memset(void *, int, u32);
void GSthreadSwitch();
u32 floorGetCurrentGroupID();
void floorAddResource(u32, u32);
u8 GSfsysReadIDEXWait(u32, u32, void (*)(s32, void *, s32), u32, u32);
void GSfsysFree(u32);
void *GSresGetResource(u32, u32);
void GSresUnlockResource(u32, u32);
void GSresLockResource(u32, u32);
void GSresFreeResource(u32, u32);
void GSresIsUniqueID(u32, u32, u8);
void GSresRegisterResource(void *, u32, u32, FloorReadFreeFunc);
void *GSresAllocResourceAlign(u32, u16, u32, u32, FloorReadFreeFunc);
void *HSD_ArchiveGetPublicAddress(void *, const char *);
int HSD_ArchiveParse(void *, u8 *, u32);
void *GScameraLoad(void *);
void GScameraFree(void *);
void *GSlightLoad(void *);
void GSlightFree(void *);
void *GSlensFlareLoad(void *);
void GSlensFlareFree(void *);
void *GSparticleLoad(void *);
void GSparticleFree(void *);
void GSmodelLinkToGSparticleBank(void *, void *);
void deckRegister(u32, u32);
void deckUnRegister(u32, u32);
void *GStextureLoad(void *);
void GStextureFree(void *);
void FlashSystemInit(u32, void *);
void FlashSystemRelease(u32);
void GSfsysOSLinkPostFunc(u32, u32, u32);
u8 ModelSequence_Load(void *, u32, u32);
void *GScolsys2LoadCCD(void *);
void GScolsys2UnloadCCD(void *);
FloorReadData *floorDataBiosGetCurrentPtr();
void floorDataBiosSetMapResID(FloorReadData *, u32);
void floorSetLightInfo(u32, u32);
void floorInitMap(u32, u32);
u8 floorIsPop();
u8 floorIsPush();
void floorMappingScript(void *);
void floorUnmappingScript(void *);
u8 floorSound_playEnvSound(u32);
void soundStopEnv(u32);
void floorExecSoundScript();
void GSmsgFontOpen(void *);
void GSmsgFontClose(void *);
void GSmsgOpen(void *);
void GSmsgClose(void *);
s32 pokecoloGetLanguage();
s32 fn_8010B208(void *);

void floorDelayPostFunc();
void *floorReadResourceID(u32, u32);
void *floorRegisterCamera(u32, u32);
void *floorRegisterLight(u32, u32);
u32 floorReadMakeFogResID(u32);
u32 floorReadMakeCameraResID(u32);
u32 floorReadMakeLightResID(u32);
u32 floorReadMakeModelResID(u32);
u32 floorReadMakeObjResID(u32);
void *floorReadNormalPreFunc(u32, u32, u32);
void *floorReadParticlePostFunc(u32, u32, u32);
}
#endif
