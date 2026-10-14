#include <game/pxdvs/app/floor/floorManagerLayout.hpp>
#ifdef __cplusplus
extern "C" {
#endif

void *GSthreadCreate(s32,u32,u32,s32,s32,void (*)());
void GSthreadSetName(void *,const char *);
void GSthreadSwitch();
void GSthreadTerminateGroup(u32);
s32 floorGetLocalHeapHandle();
s32 GSmemSetCurrentHeap(s32);
void *GSmemAlloc(u32);
void *GSmemAllocClr(u32);
void GSmemFree(void *);
void *__nw__FUl(u32);
void __dl__FPv(void *);
FloorSaveHeader *savedataGetStatus(u32,u32);
void floorExecScriptIntegerByName(const char *,u32,u32,u32,u32);
u32 fn_8005C8C4();
char *tableResBiosGetResPtr(u32);
int memcmp(const void *,const void *,unsigned long);
void *memcpy(void *,const void *,unsigned long);
void floorDelayPostFunc();
void floorSetFadeScript(u32,u32);
u8 floorIsContinueMode();

FloorManagerLayout *__ct__12FloorManagerFv(FloorManagerLayout *);
FloorManagerLayout *__dt__12FloorManagerFv(FloorManagerLayout *,s16);
void init__12FloorManagerFUlUl(FloorManagerLayout *,u32,u32);
FloorModuleListLayout *__ct__15FloorModuleListFUl(FloorModuleListLayout *,u32);
FloorStackListLayout *__ct__14FloorStackListFUl(FloorStackListLayout *,u32);
void __dt__14FloorStackListFv(FloorStackListLayout *,s16);
void __ct__9AppScriptFv(FloorScriptLayout *);
void __dt__9AppScriptFv(FloorScriptLayout *,s16);
void __dt__16GSBinWriteStreamFv(FloorWriteStreamLayout *,s16);
__declspec(weak) FloorWriteStreamLayout *__ct__16GSBinWriteStreamFUl(FloorWriteStreamLayout *,u32);
void *getStateData__12FloorManagerFP12StateDataPtr(FloorManagerLayout *,FloorStateDataPtr *);
void execPostFunction__12FloorManagerFP10FloorStack14FloorEnterMode(FloorManagerLayout *,FloorStackLayout *,s32);
void execPreFunction__12FloorManagerFP10FloorStack14FloorEnterMode(FloorManagerLayout *,FloorStackLayout *,s32);
u8 update__12FloorManagerFP10FloorStack(FloorManagerLayout *,FloorStackLayout *);
void load__12FloorManagerFP11GSfloor_dd_14FloorEnterMode(FloorManagerLayout *,void *,s32);
void unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(FloorManagerLayout *,void *,u8,s32);
void *makePushState__15FloorModuleListF14FloorStateMode(FloorModuleListLayout *,s32);
s32 getStateMode__14FloorStackListFv(FloorStackListLayout *);
s32 getObjective__14FloorStackListFv(FloorStackListLayout *);
void *getGSfloor__14FloorStackListFv(FloorStackListLayout *);
void setPushState__14FloorStackListFPvUl(FloorStackListLayout *,void *,u32);
void blockModuleGroup__15FloorModuleListFUl(FloorModuleListLayout *,u32);
void unblockModuleGroup__15FloorModuleListFUl(FloorModuleListLayout *,u32);
void unregisterModuleGroup__15FloorModuleListFUl(FloorModuleListLayout *,u32);
void block__14FloorStackListFv(FloorStackListLayout *);
void unblock__14FloorStackListFv(FloorStackListLayout *);
void push__14FloorStackListFUi(FloorStackListLayout *,u32);
void pop__14FloorStackListFv(FloorStackListLayout *);
void restorePopState__15FloorModuleListFPv14FloorStateModeb(FloorModuleListLayout *,void *,s32,u8);
void executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(FloorModuleListLayout *,u32,s32,s32,s32,u32);
void waitFloorScript__15FloorModuleListF10FloorState(FloorModuleListLayout *,s32);
u32 getStateSize__Q28GSscript4TigaFv(FloorScriptLayout *);
void makeStateData__Q28GSscript4TigaFP16GSBinWriteStream(FloorScriptLayout *,FloorWriteStreamLayout *);
u8 restoreStateData__Q28GSscript4TigaFPvUl(FloorScriptLayout *,void *,u32);
void executeThread__Q28GSscript4TigaFf(FloorScriptLayout *,f32);
f32 timeGetLastFrameSec();
void GSlogWrite(const char *,...);
u32 gamedatasaveGetStatus(u32,u32);
void fn_8005C068(u8);
void floorLayerConfig(u32,u8);
void floorInitWazaSequence(u32);
void GSfsysReadWait(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void psRemoveParticle();
void psRemoveGenerator();
void psRemoveAppSRT();
void GSlightDeleteCurrentAll();
void GSmodelFreeAllShadowTextures();
void underTakerMenuResore();
void *__vt__12FloorManager[] = {0,0,(void *)__dt__12FloorManagerFv};

void floorExecFadeOut();
void floorExecFadeIn();
void floorSetContinueMode(u8);
void flooSetFrameRate();
void floorCheckFade();
u8 floorCheckFightKind(u32);
void *floorDataBiosGetPtr(u32);
u32 floorDataBiosGetFloorID(void *);
u32 floorDataBiosGetGroupID(void *);
u32 floorDataBiosGetFileGroupID(void *);
u8 floorDataBiosGetFloorKind(void *);
void mappingScript__Q28GSscript4TigaFPc(FloorScriptLayout *,char *);
void unmappingScript__Q28GSscript4TigaFv(FloorScriptLayout *);
FloorScriptLayout *getScriptModule__10FloorStackFv(FloorStackLayout *);
void setPushState__10FloorStackFPvUl(FloorStackLayout *,void *,u32);
void setFloorID__10FloorStackFUl(FloorStackLayout *,u32);
void clearFlag__10FloorStackFv(FloorStackLayout *);
void setPushFlag__10FloorStackFv(FloorStackLayout *);
void reallocPushData__10FloorStackFv(FloorStackLayout *);
void freeAllResource__10FloorStackFv(FloorStackLayout *);
void freeResource__10FloorStackFUlUl(FloorStackLayout *,u32,u32);
void addResource__10FloorStackFUlUl(FloorStackLayout *,u32,u32);
void setGroupID__14FloorStackListFUl(FloorStackListLayout *,u32);
void setUpdateState__14FloorStackListF10FloorState(FloorStackListLayout *,s32);
void killModuleGroup__15FloorModuleListFUl(FloorModuleListLayout *,u32);
void blockModule__15FloorModuleListFUl(FloorModuleListLayout *,u32);
void unblockModule__15FloorModuleListFUl(FloorModuleListLayout *,u32);
s32 registerModule__15FloorModuleListFUcUlP20FloorModuleInterface(FloorModuleListLayout *,u8,u32,void *);
s32 registerScriptModule__15FloorModuleListFUcUlUlUlUl(FloorModuleListLayout *,u8,u32,u32,u32,u32);
s32 makeSaveData__12FloorManagerFPPUcPUl(FloorManagerLayout *,void **,u32 *);
void mainThread__12FloorManagerFv(FloorManagerLayout *);
void scriptUpdate__12FloorManagerFv(FloorManagerLayout *);

static FloorManagerLayout *_floorManager;
__declspec(weak) s32 getTaskMode__12FloorManagerCFv(FloorManagerLayout *a);
u32 getNextFloorID__12FloorManagerFv(FloorManagerLayout *a);
__declspec(weak) FloorStackLayout * getTopOfStack__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) FloorStackLayout * getBottomOfStack__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) s32 getUpdateState__10FloorStackFv(FloorStackLayout *a);
__declspec(weak) void * getPushState__10FloorStackFv(FloorStackLayout *a);
__declspec(weak) u32 getGroupID__10FloorStackCFv(FloorStackLayout *a);
__declspec(weak) u32 getFloorID__10FloorStackCFv(FloorStackLayout *a);
__declspec(weak) u8 isPopFlag__10FloorStackFv(FloorStackLayout *a);
__declspec(weak) u8 isPushFlag__10FloorStackFv(FloorStackLayout *a);
__declspec(weak) s32 getType__10FloorStackFv(FloorStackLayout *a);
__declspec(weak) u8 isMapping__Q28GSscript4TigaFv(FloorScriptLayout *a);
__declspec(weak) u32 getPushStateSize__15FloorModuleListCFv(FloorModuleListLayout *a);
__declspec(weak) void * getTop__16GSBinWriteStreamCFv(FloorWriteStreamLayout *a);
__declspec(weak) s32 isFloorPushd__14FloorStackListCFv(FloorStackListLayout *a);
__declspec(weak) u8 isPopReady__14FloorStackListCFv(FloorStackListLayout *a);
__declspec(weak) u8 isPushReady__14FloorStackListCFv(FloorStackListLayout *a);
__declspec(weak) void changeTaskMode__12FloorManagerF9floorTask(FloorManagerLayout *a, s32 v);
__declspec(weak) void setNextTaskMode__12FloorManagerF9floorTask(FloorManagerLayout *a, s32 v);
__declspec(weak) void setCommonScriptType__12FloorManagerF15FloorModuleType(FloorManagerLayout *a, s32 v);
__declspec(weak) void setUpdateState__10FloorStackF10FloorState(FloorStackLayout *a, s32 v);
__declspec(weak) void setType__10FloorStackF15FloorModuleType(FloorStackLayout *a, s32 v);
__declspec(weak) u32 makeFloorGroupID__12FloorManagerFUi(FloorManagerLayout *a, u32 id);
__declspec(weak) FloorScriptLayout * getCommonScript__12FloorManagerFv(FloorManagerLayout *a);
__declspec(weak) FloorStackLayout * getCurrentStack__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void * getPushState__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) u32 getGroupID__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) u32 getFloorID__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) FloorScriptLayout * getScriptModule__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) u8 isPopFlag__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) u8 isPushFlag__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void reallocPushData__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void setPushFlag__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void clearFlag__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void freeAllResource__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void freeResource__14FloorStackListFUlUl(FloorStackListLayout *a, u32 group, u32 id);
__declspec(weak) void addResource__14FloorStackListFUlUl(FloorStackListLayout *a, u32 group, u32 id);
__declspec(weak) void setFloorID__14FloorStackListFUl(FloorStackListLayout *a, u32 id);
__declspec(weak) void clearState__14FloorStackListFv(FloorStackListLayout *a);
__declspec(weak) void freeState__14FloorStackListFv(FloorStackListLayout *a);
FloorScriptLayout * getCurrentScript__12FloorManagerFv(FloorManagerLayout *a);
s32 isFloorPushed__12FloorManagerFv(FloorManagerLayout *a);
u8 isPop__12FloorManagerFv(FloorManagerLayout *a);
u8 isPush__12FloorManagerFv(FloorManagerLayout *a);
u32 getCurrentFloorGroupID__12FloorManagerFv(FloorManagerLayout *a);
u32 getCurrentFloorID__12FloorManagerFv(FloorManagerLayout *a);
__declspec(weak) void freeResource__12FloorManagerFUlUl(FloorManagerLayout *a, u32 group, u32 id);
__declspec(weak) void addResource__12FloorManagerFUlUl(FloorManagerLayout *a, u32 group, u32 id);
__declspec(weak) void blockModule__12FloorManagerFUl(FloorManagerLayout *a, u32 id);
__declspec(weak) void unblockModule__12FloorManagerFUl(FloorManagerLayout *a, u32 id);
__declspec(weak) s32 registerModule__12FloorManagerFUcUlP20FloorModuleInterface(FloorManagerLayout *a,u8 type,u32 id,void *module);
__declspec(weak) s32 registerScriptModule__12FloorManagerFUcUlUlUlUl(FloorManagerLayout *a,u8 type,u32 id,u32 resource,u32 script,u32 param);
s32 floorGetFloorState(void);
s32 floorGetCurentScriptMode(void);
FloorScriptLayout * floorGetCommonScript__Fv(void);
FloorScriptLayout * floorGetCurentScript__Fv(void);
s32 floorIsFloorPushed(void);
u8 floorIsPop(void);
u8 floorIsPush(void);
u32 floorGetCurrentFloorGroupID(void);
u32 floorGetNextChangeID(void);
u32 floorGetCurrent(void);
s32 floorChange(u32 id);
s32 floorPopAndChange(u32 id);
s32 floorPop(void);
s32 floorPush(u32 id);
s32 floorOpen(u32 id);
void floorWaitForChange(void);
void floorFreeResource(u32 group,u32 id);
void floorAddResource(u32 group,u32 id);
u32 GSfloorGetCurrent(void);
u32 GSfloorGetCurrentFloorGroupID(void);
s32 GSfloorIsFloorPushed(void);
u8 GSfloorIsPop(void);
u8 GSfloorIsPush(void);
s32 GSfloorChange(u32 id);
s32 GSfloorPop(void);
s32 GSfloorPush(u32 id);
s32 GSfloorOpen(u32 id);
void GSfloorSetData(void);
void GSfloorStart(void);
void floorBlockModule(u32 id);
void floorUnblockModule(u32 id);
s32 floorRegisterModule(u8 type,u32 id,void *module);
s32 floorRegisterScriptModule(u8 type,u32 id,u32 resource,u32 script,u32 param);
s32 floorMakeSaveData(void **data,u32 *size);
s32 floorCheckAnywaySaveData(void);
void floorMemoryCardSaveCallback(void);
s32 floorIsCurentScriptMode(void);
void * floorCreateThread(s32 priority,u32 size,s32 mode,void (*entry)());
void * floorCreateThreadLocal(s32 priority,u32 size,s32 mode,void (*entry)());
void floorMappingCommonScript(void);
void floorUnmappingScript(char *data);
void floorMappingScript(char *data);
static void _floorMainThread__Fv(void);
static void _floorScriptThread__Fv(void);
s32 getFloorState__12FloorManagerFv(FloorManagerLayout *arg0);
s32 getCurrentScriptMode__12FloorManagerFv(FloorManagerLayout *arg0);
s32 getCurrentEnterMode__12FloorManagerFv(FloorManagerLayout *arg0);
void mappingCommonScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *arg1);
void unmappingScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *data);
void mappingScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *arg1);
s32 popAndChange__12FloorManagerFUi(FloorManagerLayout *arg0, s32 arg1);
s32 change__12FloorManagerFUi(FloorManagerLayout *arg0, u32 arg1);
s32 pop__12FloorManagerFv(FloorManagerLayout *arg0);
s32 push__12FloorManagerFUi(FloorManagerLayout *arg0, s32 arg1);
s32 close__12FloorManagerFv(FloorManagerLayout *arg0);
s32 open__12FloorManagerFUi(FloorManagerLayout *arg0, u32 arg1);
void waitForChange__12FloorManagerFv(FloorManagerLayout *arg0);
void GSfloorSetData(void) {

}

u32 GSfloorGetCurrent(void) {
return floorGetCurrent();
}

u32 GSfloorGetCurrentFloorGroupID(void) {
return floorGetCurrentFloorGroupID();
}

s32 GSfloorIsFloorPushed(void) {
return floorIsFloorPushed();
}

u8 GSfloorIsPop(void) {
return floorIsPop();
}

u8 GSfloorIsPush(void) {
return floorIsPush();
}

s32 GSfloorChange(u32 id) {
return floorChange(id);
}

s32 GSfloorPop(void) {
return floorPop();
}

s32 GSfloorPush(u32 id) {
return floorPush(id);
}

s32 GSfloorOpen(u32 id) {
return floorOpen(id);
}

void GSfloorStart(void) {

}

s32 floorCheckAnywaySaveData(void) {
return savedataGetStatus(0,0x16)->size != 0;
}

void floorMemoryCardSaveCallback(void) {
floorExecScriptIntegerByName("anywaysave_callback",GSfloorGetCurrentFloorGroupID(),0,0,0);
}

s32 floorMakeSaveData(void **data,u32 *size) {
makeSaveData__12FloorManagerFPPUcPUl(_floorManager,data,size); return 1;
}

void floorFreeResource(u32 group,u32 id) {
freeResource__12FloorManagerFUlUl(_floorManager,group,id);
}

__declspec(weak) void freeResource__12FloorManagerFUlUl(FloorManagerLayout *a, u32 group, u32 id) {
freeResource__14FloorStackListFUlUl(a->stackList,group,id);
}

void floorAddResource(u32 group,u32 id) {
addResource__12FloorManagerFUlUl(_floorManager,group,id);
}

__declspec(weak) void addResource__12FloorManagerFUlUl(FloorManagerLayout *a, u32 group, u32 id) {
addResource__14FloorStackListFUlUl(a->stackList,group,id);
}

void floorWaitForChange(void) {
waitForChange__12FloorManagerFv(_floorManager);
}

void * floorCreateThreadLocal(s32 priority,u32 size,s32 mode,void (*entry)()) {
s32 heap; void *thread; heap = GSmemSetCurrentHeap(floorGetLocalHeapHandle()); thread = floorCreateThread(priority,size,mode,entry); GSmemSetCurrentHeap(heap); return thread;
}

void * floorCreateThread(s32 priority,u32 size,s32 mode,void (*entry)()) {
if (!entry) return 0; if (!size) size=0x4000; return GSthreadCreate(priority,floorGetCurrentFloorGroupID(),size,1,mode,entry);
}

void floorUnblockModule(u32 id) {
if (_floorManager) unblockModule__12FloorManagerFUl(_floorManager,id);
}

__declspec(weak) void unblockModule__12FloorManagerFUl(FloorManagerLayout *a, u32 id) {
if (a->modules) unblockModule__15FloorModuleListFUl(a->modules,id);
}

void floorBlockModule(u32 id) {
if (_floorManager) blockModule__12FloorManagerFUl(_floorManager,id);
}

__declspec(weak) void blockModule__12FloorManagerFUl(FloorManagerLayout *a, u32 id) {
if (a->modules) blockModule__15FloorModuleListFUl(a->modules,id);
}

s32 floorRegisterScriptModule(u8 type,u32 id,u32 resource,u32 script,u32 param) {
if (_floorManager == 0) return 0; return registerScriptModule__12FloorManagerFUcUlUlUlUl(_floorManager,type,id,resource,script,param);
}

__declspec(weak) s32 registerScriptModule__12FloorManagerFUcUlUlUlUl(FloorManagerLayout *a,u8 type,u32 id,u32 resource,u32 script,u32 param) {
if (a->modules == 0) return 0; return registerScriptModule__15FloorModuleListFUcUlUlUlUl(a->modules,type,id,resource,script,param);
}

s32 floorRegisterModule(u8 type,u32 id,void *module) {
if (_floorManager == 0) return 0; return registerModule__12FloorManagerFUcUlP20FloorModuleInterface(_floorManager,type,id,module);
}

__declspec(weak) s32 registerModule__12FloorManagerFUcUlP20FloorModuleInterface(FloorManagerLayout *a,u8 type,u32 id,void *module) {
if (a->modules == 0) return 0; return registerModule__15FloorModuleListFUcUlP20FloorModuleInterface(a->modules,type,id,module);
}

s32 floorGetFloorState(void) {
return getFloorState__12FloorManagerFv(_floorManager);
}

void floorMappingCommonScript(void) {
char *data = tableResBiosGetResPtr(fn_8005C8C4()); if (data && _floorManager) { if (memcmp(data,"TCOD",4)==0) { mappingCommonScript__12FloorManagerFPc(_floorManager,data); return; } mappingCommonScript__12FloorManagerFPc(_floorManager,0); }
}

void floorUnmappingScript(char *data) {
if (_floorManager && memcmp(data,"TCOD",4)==0) unmappingScript__12FloorManagerFPc(_floorManager,0);
}

void floorMappingScript(char *data) {
if (_floorManager) { if (memcmp(data,"TCOD",4)==0) { mappingScript__12FloorManagerFPc(_floorManager,data); return; } mappingScript__12FloorManagerFPc(_floorManager,0); }
}

s32 floorIsCurentScriptMode(void) {
FloorScriptLayout *script = getCurrentScript__12FloorManagerFv(_floorManager); if (script && isMapping__Q28GSscript4TigaFv(script)) return 1; return 0;
}

s32 floorGetCurentScriptMode(void) {
return getCurrentScriptMode__12FloorManagerFv(_floorManager);
}

FloorScriptLayout * floorGetCommonScript__Fv(void) {
return getCommonScript__12FloorManagerFv(_floorManager);
}

__declspec(weak) FloorScriptLayout * getCommonScript__12FloorManagerFv(FloorManagerLayout *a) {
return &a->commonScript;
}

FloorScriptLayout * floorGetCurentScript__Fv(void) {
return getCurrentScript__12FloorManagerFv(_floorManager);
}

s32 floorIsFloorPushed(void) {
return isFloorPushed__12FloorManagerFv(_floorManager);
}

u8 floorIsPop(void) {
return isPop__12FloorManagerFv(_floorManager);
}

u8 floorIsPush(void) {
return isPush__12FloorManagerFv(_floorManager);
}

u32 floorGetCurrentFloorGroupID(void) {
return getCurrentFloorGroupID__12FloorManagerFv(_floorManager);
}

u32 floorGetNextChangeID(void) {
return getNextFloorID__12FloorManagerFv(_floorManager);
}

u32 floorGetCurrent(void) {
return getCurrentFloorID__12FloorManagerFv(_floorManager);
}

s32 floorChange(u32 id) {
return change__12FloorManagerFUi(_floorManager,id);
}

s32 floorPopAndChange(u32 id) {
return popAndChange__12FloorManagerFUi(_floorManager,id);
}

s32 floorPop(void) {
return pop__12FloorManagerFv(_floorManager);
}

s32 floorPush(u32 id) {
return push__12FloorManagerFUi(_floorManager,id);
}

s32 floorOpen(u32 id) {
return open__12FloorManagerFUi(_floorManager,id);
}

static void _floorScriptThread__Fv(void) {
for (;;) { if (_floorManager) scriptUpdate__12FloorManagerFv(_floorManager); floorDelayPostFunc(); GSthreadSwitch(); }
}

static void _floorMainThread__Fv(void) {
mainThread__12FloorManagerFv(_floorManager);
}

s32 getFloorState__12FloorManagerFv(FloorManagerLayout *arg0) {
FloorStackLayout *temp_r3;

    temp_r3 = getCurrentStack__14FloorStackListFv(arg0->stackList);
    if (temp_r3 != 0) {
        if (getTaskMode__12FloorManagerCFv(arg0) == 2) {
            return getUpdateState__10FloorStackFv(temp_r3);
        }
        return 0;
    }
    return 0;
}

__declspec(weak) s32 getTaskMode__12FloorManagerCFv(FloorManagerLayout *a) {
return a->task;
}

__declspec(weak) u32 makeFloorGroupID__12FloorManagerFUi(FloorManagerLayout *a, u32 id) {
return id + 0x5001;
}

__declspec(weak) void changeTaskMode__12FloorManagerF9floorTask(FloorManagerLayout *a, s32 v) {
a->task = v;
}

void waitForChange__12FloorManagerFv(FloorManagerLayout *arg0) {
while (arg0->changing) GSthreadSwitch();
}

s32 getCurrentScriptMode__12FloorManagerFv(FloorManagerLayout *arg0) {
return getType__10FloorStackFv(getCurrentStack__14FloorStackListFv(arg0->stackList)) == 2;
}

s32 getCurrentEnterMode__12FloorManagerFv(FloorManagerLayout *arg0) {
FloorStackLayout *temp_r31;

    temp_r31 = getCurrentStack__14FloorStackListFv(arg0->stackList);
    if (floorIsContinueMode() != 0) {
        return 3;
    }
    if (isPopFlag__10FloorStackFv(temp_r31) != 0) {
        return 2;
    }
    return isPushFlag__10FloorStackFv(temp_r31) != 0;
}

void mappingCommonScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *arg1) {
if (arg1 != 0) {
        if (memcmp(arg1, "TCOD", 4) == 0) {
            setCommonScriptType__12FloorManagerF15FloorModuleType(arg0, 2);
            mappingScript__Q28GSscript4TigaFPc(&arg0->commonScript, arg1);
            return;
        }
        setCommonScriptType__12FloorManagerF15FloorModuleType(arg0, 1);
        return;
    }
    setCommonScriptType__12FloorManagerF15FloorModuleType(arg0,1);
}

__declspec(weak) void setCommonScriptType__12FloorManagerF15FloorModuleType(FloorManagerLayout *a, s32 v) {
a->commonScriptType = v;
}

void unmappingScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *data) {
FloorStackLayout *temp_r3;

    temp_r3 = getCurrentStack__14FloorStackListFv(arg0->stackList);
    if (temp_r3 != 0) {
        if (getScriptModule__10FloorStackFv(temp_r3) != 0U) {
                    unmappingScript__Q28GSscript4TigaFv(getScriptModule__10FloorStackFv(temp_r3));
        }
        setType__10FloorStackF15FloorModuleType(temp_r3, 1);
    }
}

void mappingScript__12FloorManagerFPc(FloorManagerLayout *arg0, char *arg1) {
FloorStackLayout *temp_r3;

    temp_r3 = getCurrentStack__14FloorStackListFv(arg0->stackList);
    if ((temp_r3 != 0) && (arg1 != 0)) {
        if (memcmp(arg1, "TCOD", 4) == 0) {
            setType__10FloorStackF15FloorModuleType(temp_r3, 2);
            if (getScriptModule__10FloorStackFv(temp_r3) != 0U) {
                            mappingScript__Q28GSscript4TigaFPc(getScriptModule__10FloorStackFv(temp_r3),arg1);
            }
        } else {
            setType__10FloorStackF15FloorModuleType(temp_r3, 1);
        }
    } else {
        setType__10FloorStackF15FloorModuleType(temp_r3, 1);
    }
}

FloorScriptLayout * getCurrentScript__12FloorManagerFv(FloorManagerLayout *a) {
return getScriptModule__14FloorStackListFv(a->stackList);
}

s32 isFloorPushed__12FloorManagerFv(FloorManagerLayout *a) {
return isFloorPushd__14FloorStackListCFv(a->stackList);
}

u8 isPop__12FloorManagerFv(FloorManagerLayout *a) {
return isPopFlag__14FloorStackListFv(a->stackList);
}

u8 isPush__12FloorManagerFv(FloorManagerLayout *a) {
return isPushFlag__14FloorStackListFv(a->stackList);
}

u32 getCurrentFloorGroupID__12FloorManagerFv(FloorManagerLayout *a) {
return getGroupID__14FloorStackListFv(a->stackList);
}

u32 getNextFloorID__12FloorManagerFv(FloorManagerLayout *a) {
return a->nextFloorID;
}

u32 getCurrentFloorID__12FloorManagerFv(FloorManagerLayout *a) {
return getFloorID__14FloorStackListFv(a->stackList);
}

s32 popAndChange__12FloorManagerFUi(FloorManagerLayout *arg0, s32 arg1) {
if (getTaskMode__12FloorManagerCFv(arg0) != 2) {
        return 0;
    }
    floorSetFadeScript(0x05960009, 0x05960008);
    if (isPopReady__14FloorStackListCFv(arg0->stackList) == 0) {
        return 0;
    }
    close__12FloorManagerFv(arg0);
    setNextTaskMode__12FloorManagerF9floorTask(arg0, 6);
    arg0->nextFloorID = arg1;
    arg0->changing = 1;
    return 1;
}

__declspec(weak) void setNextTaskMode__12FloorManagerF9floorTask(FloorManagerLayout *a, s32 v) {
a->nextTask = v;
}

s32 change__12FloorManagerFUi(FloorManagerLayout *arg0, u32 arg1) {
if (getTaskMode__12FloorManagerCFv(arg0) != 2) {
        return 0;
    }
    if (floorDataBiosGetPtr(arg1) == 0U) {
        return 0;
    }
    floorSetFadeScript(0x05960009, 0x05960008);
    close__12FloorManagerFv(arg0);
    setNextTaskMode__12FloorManagerF9floorTask(arg0, 3);
    arg0->nextFloorID = arg1;
    arg0->changing = 1;
    return 1;
}

s32 pop__12FloorManagerFv(FloorManagerLayout *arg0) {
if (getTaskMode__12FloorManagerCFv(arg0) != 2) {
        return 0;
    }
    floorSetFadeScript(0x05960009, 0x05960008);
    if (isPopReady__14FloorStackListCFv(arg0->stackList) == 0) {
        return 0;
    }
    close__12FloorManagerFv(arg0);
    setNextTaskMode__12FloorManagerF9floorTask(arg0, 5);
    arg0->changing = 1;
    return 1;
}

s32 push__12FloorManagerFUi(FloorManagerLayout *arg0, s32 arg1) {
floorSetFadeScript(0x05960009, 0x05960008);
    if (isPushReady__14FloorStackListCFv(arg0->stackList) == 0) {
        return 0;
    }
    changeTaskMode__12FloorManagerF9floorTask(arg0, 4);
    arg0->nextFloorID = arg1;
    arg0->changing = 1;
    return 1;
}

s32 close__12FloorManagerFv(FloorManagerLayout *arg0) {
if (getTaskMode__12FloorManagerCFv(arg0) != 2) {
        return 0;
    }
    killModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
    setUpdateState__14FloorStackListF10FloorState(arg0->stackList, 6);
    arg0->nextFloorID = -1;
    return 1;
}

s32 open__12FloorManagerFUi(FloorManagerLayout *arg0, u32 arg1) {
if (getTaskMode__12FloorManagerCFv(arg0) != 0) {
        return 0;
    }
    if (floorDataBiosGetPtr(arg1) == 0U) {
        return 0;
    }
    setFloorID__14FloorStackListFUl(arg0->stackList, arg1);
    setGroupID__14FloorStackListFUl(arg0->stackList, makeFloorGroupID__12FloorManagerFUi(arg0, arg1));
    setUpdateState__14FloorStackListF10FloorState(arg0->stackList, 2);
    changeTaskMode__12FloorManagerF9floorTask(arg0, 1);
    return 1;
}

__declspec(weak) void freeResource__14FloorStackListFUlUl(FloorStackListLayout *a, u32 group, u32 id) {
freeResource__10FloorStackFUlUl(getCurrentStack__14FloorStackListFv(a), group, id);
}

__declspec(weak) FloorStackLayout * getCurrentStack__14FloorStackListFv(FloorStackListLayout *a) {
return getTopOfStack__14FloorStackListFv(a);
}

__declspec(weak) FloorStackLayout * getTopOfStack__14FloorStackListFv(FloorStackListLayout *a) {
return a->stacks + a->current;
}

__declspec(weak) void addResource__14FloorStackListFUlUl(FloorStackListLayout *a, u32 group, u32 id) {
addResource__10FloorStackFUlUl(getCurrentStack__14FloorStackListFv(a), group, id);
}

__declspec(weak) s32 getUpdateState__10FloorStackFv(FloorStackLayout *a) {
return a->updateState;
}

__declspec(weak) FloorStackLayout * getBottomOfStack__14FloorStackListFv(FloorStackListLayout *a) {
return a->stacks;
}

__declspec(weak) void freeState__14FloorStackListFv(FloorStackListLayout *a) {
GSmemFree(getPushState__10FloorStackFv(getCurrentStack__14FloorStackListFv(a))); clearState__14FloorStackListFv(a);
}

__declspec(weak) void * getPushState__10FloorStackFv(FloorStackLayout *a) {
return a->pushState;
}

__declspec(weak) void clearState__14FloorStackListFv(FloorStackListLayout *a) {
setPushState__10FloorStackFPvUl(getCurrentStack__14FloorStackListFv(a), 0, 0);
}

__declspec(weak) void * getPushState__14FloorStackListFv(FloorStackListLayout *a) {
return getPushState__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) void reallocPushData__14FloorStackListFv(FloorStackListLayout *a) {
reallocPushData__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) void setPushFlag__14FloorStackListFv(FloorStackListLayout *a) {
setPushFlag__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) void setFloorID__14FloorStackListFUl(FloorStackListLayout *a, u32 id) {
setFloorID__10FloorStackFUl(getCurrentStack__14FloorStackListFv(a), id);
}

__declspec(weak) void clearFlag__14FloorStackListFv(FloorStackListLayout *a) {
clearFlag__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) u32 getGroupID__14FloorStackListFv(FloorStackListLayout *a) {
return getGroupID__10FloorStackCFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) u32 getGroupID__10FloorStackCFv(FloorStackLayout *a) {
return a->groupID;
}

__declspec(weak) u32 getFloorID__10FloorStackCFv(FloorStackLayout *a) {
return a->floorID;
}

__declspec(weak) u8 isPopFlag__10FloorStackFv(FloorStackLayout *a) {
return a->popFlag;
}

__declspec(weak) void setUpdateState__10FloorStackF10FloorState(FloorStackLayout *a, s32 v) {
a->updateState = v;
}

__declspec(weak) void freeAllResource__14FloorStackListFv(FloorStackListLayout *a) {
freeAllResource__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) s32 getType__10FloorStackFv(FloorStackLayout *a) {
return a->type;
}

__declspec(weak) u8 isPushFlag__10FloorStackFv(FloorStackLayout *a) {
return a->pushFlag;
}

__declspec(weak) void setType__10FloorStackF15FloorModuleType(FloorStackLayout *a, s32 v) {
a->type = v;
}

__declspec(weak) FloorScriptLayout * getScriptModule__14FloorStackListFv(FloorStackListLayout *a) {
return getScriptModule__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) s32 isFloorPushd__14FloorStackListCFv(FloorStackListLayout *a) {
return a->current != 0;
}

__declspec(weak) u8 isPopFlag__14FloorStackListFv(FloorStackListLayout *a) {
return isPopFlag__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) u8 isPushFlag__14FloorStackListFv(FloorStackListLayout *a) {
return isPushFlag__10FloorStackFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) u32 getFloorID__14FloorStackListFv(FloorStackListLayout *a) {
return getFloorID__10FloorStackCFv(getCurrentStack__14FloorStackListFv(a));
}

__declspec(weak) u8 isPopReady__14FloorStackListCFv(FloorStackListLayout *a) {
return a->current > 0;
}

__declspec(weak) u8 isPushReady__14FloorStackListCFv(FloorStackListLayout *a) {
return (u32)a->current < a->capacity - 1;
}

__declspec(weak) u8 isMapping__Q28GSscript4TigaFv(FloorScriptLayout *a) {
return a->mapping != 0;
}

__declspec(weak) void * getTop__16GSBinWriteStreamCFv(FloorWriteStreamLayout *a) {
return a->top;
}

__declspec(weak) u32 getPushStateSize__15FloorModuleListCFv(FloorModuleListLayout *a) {
return a->pushStateSize;
}


void GSfloorInit(s32 stackCount,s32 n1,s32 n2,s32 n3) {
    FloorManagerLayout *manager = (FloorManagerLayout *)__nw__FUl(sizeof(FloorManagerLayout));
    if (manager != 0) manager = __ct__12FloorManagerFv(manager);
    _floorManager = manager;
    init__12FloorManagerFUlUl(manager,stackCount,n1+(n2+n3));
}
FloorManagerLayout *__ct__12FloorManagerFv(FloorManagerLayout *a) {
    a->vtable = __vt__12FloorManager;
    __ct__9AppScriptFv(&a->commonScript);
    a->changing = 0;
    a->modules = 0;
    a->stackList = 0;
    a->maxSaveSize = 0;
    a->maxSaveFloorID = 0;
    return a;
}
FloorManagerLayout *__dt__12FloorManagerFv(FloorManagerLayout *a,s16 destroy) {
    if (a != 0) {
        FloorModuleListLayout *modules;
        a->vtable = __vt__12FloorManager;
        modules = a->modules;
        if (modules != 0) {
            if (modules != 0) modules->vtable->destroy(modules,1);
            a->modules=0;
        }
        if (a->stackList != 0) { __dt__14FloorStackListFv(a->stackList,1); a->stackList=0; }
        __dt__9AppScriptFv(&a->commonScript,-1);
        if (destroy>0) __dl__FPv(a);
    }
    return a;
}
void init__12FloorManagerFUlUl(FloorManagerLayout *a,u32 stackCount,u32 moduleCount) {
    FloorModuleListLayout *modules;
    FloorStackListLayout *list;
    modules=a->modules;
    if (modules != 0) { if (modules != 0) modules->vtable->destroy(modules,1); a->modules=0; }
    if (a->stackList != 0) { __dt__14FloorStackListFv(a->stackList,1); a->stackList=0; }
    modules=(FloorModuleListLayout *)__nw__FUl(sizeof(FloorModuleListLayout));
    if (modules != 0) modules=__ct__15FloorModuleListFUl(modules,moduleCount);
    a->modules=modules;
    list=(FloorStackListLayout *)__nw__FUl(sizeof(FloorStackListLayout));
    if (list != 0) list=__ct__14FloorStackListFUl(list,stackCount);
    a->stackList=list;
    changeTaskMode__12FloorManagerF9floorTask(a,0);
    GSthreadSetName(GSthreadCreate(0,0x7d0,0x4000,1,1,_floorMainThread__Fv),"floorMainThread");
    GSthreadSetName(GSthreadCreate(1,0x7d0,0x1000,1,1,_floorScriptThread__Fv),"scriptUpdate");
}
__declspec(weak) FloorWriteStreamLayout *__ct__16GSBinWriteStreamFUl(FloorWriteStreamLayout *a,u32 size) {
    void *buffer=GSmemAlloc(size);
    a->buffer=buffer; a->current=buffer; a->top=buffer; a->size=size; a->ownsBuffer=1;
    return a;
}
void *getStateData__12FloorManagerFP12StateDataPtr(FloorManagerLayout *a,FloorStateDataPtr *state) {
    u32 maxSize;
    void *header;
    FloorSaveHeader *current;
    header=savedataGetStatus(0,0x16);
    if (state != 0) {
        state->header=header;
        current=state->header;
        if (current->size == 0) return 0;
        state->script=(u8 *)current + 0x20;
        state->modules=(u8 *)state->script + state->header->scriptSize;
        maxSize=state->header->maxSize;
        if (a->maxSaveSize < maxSize) { a->maxSaveSize=maxSize; a->maxSaveFloorID=state->header->maxFloorID; }
        return header;
    }
    return header;
}

void scriptUpdate__12FloorManagerFv(FloorManagerLayout *a) {
    FloorStackLayout *stack=getCurrentStack__14FloorStackListFv(a->stackList);
    if (stack != 0) {
        FloorScriptLayout *script=getScriptModule__10FloorStackFv(stack);
        if (script != 0) executeThread__Q28GSscript4TigaFf(script,timeGetLastFrameSec());
    }
}
s32 makeSaveData__12FloorManagerFPPUcPUl(FloorManagerLayout *a,void **data,u32 *size) {
    FloorWriteStreamLayout stream;
    FloorScriptLayout *script;
    void *modules;
    FloorSaveHeader *header;
    u8 *payload;
    u32 scriptSize,moduleSize,total;
    if ((data==0)||(size==0)) return 0;
    script=getScriptModule__10FloorStackFv(getBottomOfStack__14FloorStackListFv(a->stackList));
    if (script==0) return 0;
    scriptSize=getStateSize__Q28GSscript4TigaFv(script);
    __ct__16GSBinWriteStreamFUl(&stream,scriptSize);
    makeStateData__Q28GSscript4TigaFP16GSBinWriteStream(script,&stream);
    modules=makePushState__15FloorModuleListF14FloorStateMode(a->modules,3);
    moduleSize=getPushStateSize__15FloorModuleListCFv(a->modules);
    *size=scriptSize+moduleSize+0x20;
    *data=GSmemAllocClr(*size);
    total=*size;
    payload=(u8 *)*data;
    header=(FloorSaveHeader *)payload;
    if (a->maxSaveSize<total) { a->maxSaveSize=total; a->maxSaveFloorID=(u16)getCurrentFloorID__12FloorManagerFv(a); }
    memcpy(header,"ANSW",4);
    header->size=*size; payload+=0x20;
    header->scriptSize=scriptSize; header->moduleSize=moduleSize; header->reserved=0;
    header->maxSize=a->maxSaveSize; header->maxFloorID=a->maxSaveFloorID;
    memcpy(payload,getTop__16GSBinWriteStreamCFv(&stream),scriptSize);
    payload+=scriptSize;
    memcpy(payload,modules,moduleSize);
    if (modules!=0) GSmemFree(modules);
    GSlogWrite("------------------------------------\n");
    GSlogWrite("header size       = %dbytes\n",0x20);
    GSlogWrite("script state size = %dbytes\n",scriptSize);
    GSlogWrite("system state size = %dbytes\n",moduleSize);
    GSlogWrite("total             = %dbytes(max %d)\n",*size,a->maxSaveSize);
    __dt__16GSBinWriteStreamFv(&stream,-1);
    return 1;
}

void mainThread__12FloorManagerFv(FloorManagerLayout *arg0) {
    void *temp_r30_2;
    s32 temp_r30;
    s32 temp_r30_4;
    u32 temp_r30_5;
    u32 temp_r3;
    u8 temp_r30_3;

loop_1:
    temp_r3 = getTaskMode__12FloorManagerCFv(arg0);
    switch (temp_r3) {
    case 0:
        GSthreadSwitch();
        goto loop_1;
    case 1:
        temp_r30 = getObjective__14FloorStackListFv(arg0->stackList);
        load__12FloorManagerFP11GSfloor_dd_14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), temp_r30);
        setUpdateState__14FloorStackListF10FloorState(arg0->stackList, 2);
        changeTaskMode__12FloorManagerF9floorTask(arg0, 2);
        goto loop_1;
    case 2:
        if (update__12FloorManagerFP10FloorStack(arg0, getCurrentStack__14FloorStackListFv(arg0->stackList)) == 1) {
            GSthreadSwitch();
        } else {
            changeTaskMode__12FloorManagerF9floorTask(arg0, arg0->nextTask);
        }
        goto loop_1;
    case 3:
        unregisterModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
        unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), 1U, 0);
        clearFlag__14FloorStackListFv(arg0->stackList);
        if (arg0->nextFloorID != -1U) {
            setFloorID__14FloorStackListFUl(arg0->stackList,arg0->nextFloorID);
            setGroupID__14FloorStackListFUl(arg0->stackList, makeFloorGroupID__12FloorManagerFUi(arg0, arg0->nextFloorID));
            changeTaskMode__12FloorManagerF9floorTask(arg0, 1);
        } else {
            changeTaskMode__12FloorManagerF9floorTask(arg0, 0);
        }
        goto loop_1;
    case 4:
        floorExecFadeOut();
        setPushFlag__14FloorStackListFv(arg0->stackList);
        temp_r30_2 = makePushState__15FloorModuleListF14FloorStateMode(arg0->modules, getStateMode__14FloorStackListFv(arg0->stackList));
        setPushState__14FloorStackListFPvUl(arg0->stackList, temp_r30_2, getPushStateSize__15FloorModuleListCFv(arg0->modules));
        execPostFunction__12FloorManagerFP10FloorStack14FloorEnterMode(arg0, getCurrentStack__14FloorStackListFv(arg0->stackList), 1);
        temp_r30_3 = floorDataBiosGetFloorKind(getGSfloor__14FloorStackListFv(arg0->stackList));
        unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), 0U, 1);
        blockModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
        block__14FloorStackListFv(arg0->stackList);
        if (temp_r30_3 == 1) {
            reallocPushData__14FloorStackListFv(arg0->stackList);
        }
        push__14FloorStackListFUi(arg0->stackList, arg0->nextFloorID);
        changeTaskMode__12FloorManagerF9floorTask(arg0, 1);
        goto loop_1;
    case 5:
        unregisterModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
        arg0->nextFloorID = floorDataBiosGetFloorID(getGSfloor__14FloorStackListFv(arg0->stackList));
        unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), 1U, 2);
        pop__14FloorStackListFv(arg0->stackList);
        load__12FloorManagerFP11GSfloor_dd_14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), 2);
        temp_r30_4 = getStateMode__14FloorStackListFv(arg0->stackList);
        restorePopState__15FloorModuleListFPv14FloorStateModeb(arg0->modules, getPushState__14FloorStackListFv(arg0->stackList), temp_r30_4, 1);
        clearState__14FloorStackListFv(arg0->stackList);
        setUpdateState__14FloorStackListF10FloorState(arg0->stackList, 2);
        changeTaskMode__12FloorManagerF9floorTask(arg0, 2);
        goto loop_1;
    case 6:
    temp_r30_5 = arg0->nextFloorID;
    unregisterModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
    unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(arg0, getGSfloor__14FloorStackListFv(arg0->stackList), 1U, 2);
    pop__14FloorStackListFv(arg0->stackList);
    freeState__14FloorStackListFv(arg0->stackList);
    clearFlag__14FloorStackListFv(arg0->stackList);
    killModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__14FloorStackListFv(arg0->stackList));
    execPostFunction__12FloorManagerFP10FloorStack14FloorEnterMode(arg0, getCurrentStack__14FloorStackListFv(arg0->stackList), 0);
    arg0->nextFloorID = temp_r30_5;
    arg0->changing = 1;
    changeTaskMode__12FloorManagerF9floorTask(arg0, 3);
    goto loop_1;

    default: goto loop_1;
    }
}

void execPostFunction__12FloorManagerFP10FloorStack14FloorEnterMode(FloorManagerLayout *arg0, FloorStackLayout *arg1, s32 arg2) {
    floorExecFadeOut();
    if (arg2 == 1) {
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 6, 0, arg2, -1);
    } else {
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 6, 0xFF, arg2, -1);
    }
    GSthreadSwitch();
    if (arg2 != 1) {
        waitFloorScript__15FloorModuleListF10FloorState(arg0->modules, 6);
    }

}

void execPreFunction__12FloorManagerFP10FloorStack14FloorEnterMode(FloorManagerLayout *arg0, FloorStackLayout *arg1, s32 arg2) {
    FloorStateDataPtr state;
    s32 temp_r31;
    s32 temp_r31_2;
    s32 var_r29;
    u8 var_r30;

    var_r29 = arg2;
    var_r30 = 0;
    flooSetFrameRate();
    if ((var_r29 == 3) && (getStateData__12FloorManagerFP12StateDataPtr(arg0, &state) == 0)) {
        var_r29 = 0;
    }
    if ((var_r29 == 2) || (var_r29 == 3)) {
        temp_r31 = getGroupID__10FloorStackCFv(arg1);
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 2, 0, var_r29, temp_r31);
    } else {
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 2, 0xFF, var_r29, -1);
    }
    GSthreadSwitch();
    waitFloorScript__15FloorModuleListF10FloorState(arg0->modules, 2);
    if (var_r29 == 3) {
        restorePopState__15FloorModuleListFPv14FloorStateModeb(arg0->modules, state.modules, 3, 0);
        if (getScriptModule__10FloorStackFv(arg1) != 0U) {
            var_r30 = restoreStateData__Q28GSscript4TigaFPvUl(getScriptModule__10FloorStackFv(arg1), state.script, state.header->scriptSize);
        }
        if (var_r30 == 0) {
            temp_r31_2 = getGroupID__10FloorStackCFv(arg1);
            executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 2, 2, var_r29, temp_r31_2);
            GSthreadSwitch();
            waitFloorScript__15FloorModuleListF10FloorState(arg0->modules, 2);
            setUpdateState__10FloorStackF10FloorState(arg1, 4);
        } else {
            floorExecScriptIntegerByName("anywaysave_restart", GSfloorGetCurrentFloorGroupID(), 0, 0, 0);
            underTakerMenuResore();
            floorSetFadeScript(0x05960009, 0x05960019);
            setUpdateState__10FloorStackF10FloorState(arg1, 5);
        }
    } else if (isPopFlag__10FloorStackFv(arg1) != 0) {
        unblockModuleGroup__15FloorModuleListFUl(arg0->modules, getGroupID__10FloorStackCFv(arg1));
        unblock__14FloorStackListFv(arg0->stackList);
        setUpdateState__10FloorStackF10FloorState(arg1, 5);
    } else {
        setUpdateState__10FloorStackF10FloorState(arg1, 4);
    }
    floorExecFadeIn();

}

u8 update__12FloorManagerFP10FloorStack(FloorManagerLayout *arg0, FloorStackLayout *arg1) {
    s32 temp_r31;
    s32 temp_r3;

    temp_r3 = getUpdateState__10FloorStackFv(arg1);
    switch (temp_r3) {
    case 2:
        execPreFunction__12FloorManagerFP10FloorStack14FloorEnterMode(arg0, arg1, getCurrentEnterMode__12FloorManagerFv(arg0));
        clearFlag__10FloorStackFv(arg1);
block_12:
    default:
        return 1U;
    case 4:
        temp_r31 = getCurrentEnterMode__12FloorManagerFv(arg0);
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 4, 0xFF, temp_r31, -1);
        if (getUpdateState__10FloorStackFv(arg1) == 4) {
            setUpdateState__10FloorStackF10FloorState(arg1, 5);
        }
        goto block_12;
    case 5:
        floorSetContinueMode(0);
        executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, getFloorID__10FloorStackCFv(arg1), 4, 0, 0, -1);
        goto block_12;
    case 6:
        execPostFunction__12FloorManagerFP10FloorStack14FloorEnterMode(arg0, arg1, 0);
        return 0U;
    }

}

void unload__12FloorManagerFP11GSfloor_dd_b14FloorEnterMode(FloorManagerLayout *arg0, void *arg1, u8 arg2, s32 arg3) {
    if (floorCheckFightKind(arg0->nextFloorID) == 0) {
        floorCheckFade();
    }
    executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, floorDataBiosGetFloorID(arg1), 8, 0, arg3, -1);
    if (arg2 != 0) {
        GSthreadTerminateGroup(GSfloorGetCurrentFloorGroupID());
    }
    GSfsysFree(floorDataBiosGetFileGroupID(arg1));
    GSresFreeGroup(floorDataBiosGetGroupID(arg1));
    freeAllResource__14FloorStackListFv(arg0->stackList);
    psRemoveParticle();
    psRemoveGenerator();
    psRemoveAppSRT();
    GSlightDeleteCurrentAll();
    GSmodelFreeAllShadowTextures();
    arg0->changing = 0;

}

void load__12FloorManagerFP11GSfloor_dd_14FloorEnterMode(FloorManagerLayout *arg0, void *arg1, s32 arg2) {
    u32 temp_r30;
    u8 temp_r31;

    temp_r30 = floorDataBiosGetFileGroupID(arg1);
    fn_8005C068((u8)gamedatasaveGetStatus(0, 0xB));
    executeAll__15FloorModuleListFUi10FloorState15FloorModuleType14FloorEnterModeUl(arg0->modules, floorDataBiosGetFloorID(arg1), 1, 0, arg2, -1);
    temp_r31 = floorDataBiosGetFloorKind(arg1);
    floorLayerConfig(floorDataBiosGetFloorID(arg1),temp_r31);
    GSlogWrite("\n------------------>>> Floor %d loading... fsysid=[%d]\n\n", floorDataBiosGetFloorID(arg1), temp_r30);
    GSfsysReadWait(temp_r30);
    floorInitWazaSequence(floorDataBiosGetFloorID(arg1));
    GSthreadSwitch();
    GSthreadSwitch();

}
#ifdef __cplusplus
}
#endif
