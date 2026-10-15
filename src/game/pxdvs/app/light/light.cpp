#include <dolphin/types.h>
enum FloorEnterMode { FloorEnterDummy };
class LightEditor { public:u8 work[12];LightEditor();void init();void editUpdate();};
struct FloorModule {void *unused;void (*init)(unsigned int,FloorEnterMode);void (*update)(unsigned int,FloorEnterMode);void *unusedC;void (*finalize)(unsigned int,FloorEnterMode);void *unused14;const char *(*name)();u8 tail[0x10];};
static FloorModule _floorModuleLight;
static u32 _hModuleLight;
static u8 _eventLightSize;
static void *_eventGSlight;
static u8 _debugMode;
static LightEditor *_lightEditor;
extern "C" {
void floorGetLightInfo(u32*,int*);void *GSresGetResourceAllGroup(u32);u32 GSfloorGetCurrentFloorGroupID();void GSthreadBlockGroup(u32);void GSthreadUnblockGroup(u32);void GSlightFree(void*);u32 GSinputButtonsChanged(u32);u32 GSinputButtonsPressed(u32);void GSinputClearButtonData(u32,u32);void FloorModuleInterface_clear(FloorModule*);u32 floorRegisterModule(u32,u32);
void *lightGetLight(int index){u32 id;int count;floorGetLightInfo(&id,&count);if(index<count)return GSresGetResourceAllGroup(id|index);if(index==count)return _eventGSlight;return 0;}
int lightGetLightSize(){int count=0;floorGetLightInfo(0,&count);if(_eventGSlight)count++;return count;}
u8 lightIsDebugMode(){return _debugMode;}
void lightSetDebugMode(u8 on){_debugMode=on;if(on)GSthreadBlockGroup(GSfloorGetCurrentFloorGroupID());else GSthreadUnblockGroup(GSfloorGetCurrentFloorGroupID());}
}
static const char *_lightGetModuleName(){return "light";}
static void _lightFinalize(unsigned int,FloorEnterMode){if(_eventGSlight){GSlightFree(_eventGSlight);_eventGSlight=0;}_eventLightSize=0;_debugMode=0;}
static void _lightUpdate(unsigned int,FloorEnterMode){u32 changed=GSinputButtonsChanged(1);u32 pressed=GSinputButtonsPressed(1);if((pressed&changed&0x200) && _debugMode){GSinputClearButtonData(1,0x200);_debugMode=0;GSthreadUnblockGroup(GSfloorGetCurrentFloorGroupID());}if(_debugMode)_lightEditor->editUpdate();}
static void _lightInitialize(unsigned int,FloorEnterMode){_eventLightSize=0;_debugMode=0;_lightEditor->init();}
extern "C" void lightInit(){FloorModuleInterface_clear(&_floorModuleLight);_floorModuleLight.init=_lightInitialize;_floorModuleLight.update=_lightUpdate;_floorModuleLight.finalize=_lightFinalize;_floorModuleLight.name=_lightGetModuleName;_hModuleLight=floorRegisterModule(0x80,0);_debugMode=0;_eventLightSize=0;_eventGSlight=0;_lightEditor=new LightEditor;}
