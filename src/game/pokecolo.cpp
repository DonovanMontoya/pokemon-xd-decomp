#include <global.h>
#pragma dont_inline on
#pragma force_active on
static u8 __pokecolo_CountPlayTime;
static u8 pokecolo_DVDETHMode;
static s32 _RomVer;
static u64 _frameTime;
static f32 _resettimer;
static s32 _pokecoloCurrentLanguage;
static void* _getSaveSystemDataPtr();
extern "C" {
void* savedataBiosGetNowSavedataPtr();
void* savedataBiosGetGamedataPtr(void*);
void* gamedatasaveBiosGetPtr(void*);
f64 gamedatasaveBiosGetPlaytime(void*);
void gamedatasaveBiosSetPlaytime(void*,f64);
u32 GSflagGet(u32);
s32 GSfsysGetDriveStatus();
u8 menuIsCheck(u32);
u8 pauseIsPause();
void pauseOn();
void pauseOff();
void GSsndQuit();
void GSfsysReadWait(u32);
void GSgfxRender();
void fn_8005C8EC();
void GSinputReadStart();
void GSinputReadEnd();
void GSinputRead(s32);
u8 GSinputIsConnected(s32);
u8 gbaCommandIsConnected(s32);
void gbaCommandKeyRead(s32);
void dbgMenuGSvtrCaptureUpdate();
u8 GSvtrIsActive();
u8 dbgMenuIsOpen();
u32 GSinputButtonsChanged(u32);
u32 GSinputButtonsPressed(u32);
s32 GSvtrGetState();
void GSvtrSlowPlay();
void GSvtrPause();
void GSvtrPlay();
void GSvtrSingleStep();
u8 GSvtrGetInfoDisp();
void GSvtrSetInfoDisp(bool,u32);
void menuDaemon();
void GSmsgDaemon();
u8 GSgfxResetGetStatus();
f32 timeGetLastFrameSec();
void GSgfxReset(u32);
void GSthreadExecuteAll();
u8 menuFieldIsOpen();
u8 peopleIsBlock();
void peopleDaemon(unsigned long,unsigned long);
void peopleUpdateShadow();
u8 pokecoloIsDVDETHMode(){return pokecolo_DVDETHMode;}
void fn_8005C068(s32 language){_pokecoloCurrentLanguage=language;}
s32 pokecoloGetLanguage(){if(_pokecoloCurrentLanguage==0)return 2;return _pokecoloCurrentLanguage;}
void pokecoloStartCountPlayTime(u8 active){__pokecolo_CountPlayTime=active;}
void pokecoloSetPlayTime(f64 value){void* save=_getSaveSystemDataPtr();if(save)gamedatasaveBiosSetPlaytime(save,value);}
f64 pokecoloGetPlayTime(){void* save=_getSaveSystemDataPtr();if(save)return gamedatasaveBiosGetPlaytime(save);return 0.0;}
u32 pokecoloGetPlayTimeValue(){return (u32)pokecoloGetPlayTime();}
s32 pokecoloGetCountryCode(){return 1;}
s32 pokecoloGetRomVersion(){return _RomVer;}
void pokecoloInitRomVersion(){_RomVer=0;}
f64 pokecoloGetFrameTime(){return ((f32)_frameTime/1000.0f)/1000.0f;}
void pokecoloCheckDiskTray(){
    if(menuIsCheck(0x2a)){
        if(!pauseIsPause())pauseOn();
    }else{
        switch(GSfsysGetDriveStatus()){
        case 3:case 4:case 5:case 6:case 11:
            if(!pauseIsPause())pauseOn();
            break;
        default:
            if(pauseIsPause())pauseOff();
            break;
        }
    }
}
}
static void _countPlayTime(){
    void* save=_getSaveSystemDataPtr();
    if(save && __pokecolo_CountPlayTime==1 && GSflagGet(0x30d)==0){
        f64 time=gamedatasaveBiosGetPlaytime(save);
        f64 elapsed=pokecoloGetFrameTime();
        time+=elapsed;
        if(time>=3599940.0)time=3599940.0;
        gamedatasaveBiosSetPlaytime(save,time);
    }
}
static void* _getSaveSystemDataPtr(){
    void* save=savedataBiosGetNowSavedataPtr();
    if(save){
        void* data=savedataBiosGetGamedataPtr(save);
        if(data)return gamedatasaveBiosGetPtr(data);
    }
    return 0;
}
bool _pokecoloCheckExDisc(){return pokecoloGetRomVersion()==4;}
static void _pokecoloShutdown(){GSsndQuit();}
extern "C" s32 fn_8005C8C4(){return 2;}
extern "C" void fn_8005C8CC(){fn_8005C8EC();}
extern "C" void fn_8005C8EC(){GSfsysReadWait(10);}
static void _setSystemVars(){}
static void _mainRender(unsigned long,unsigned long){
    static s32 frame=0;
    GSgfxRender();
}
static void _mainDaemon(unsigned long,unsigned long){
    dbgMenuGSvtrCaptureUpdate();
    if(GSvtrIsActive() && !dbgMenuIsOpen()){
        u32 changed=GSinputButtonsChanged(1);
        u32 pressed=GSinputButtonsPressed(1);
        if((pressed&changed&0x40)!=0){
            if(GSvtrGetState()==2)GSvtrSlowPlay();
            else if(GSvtrGetState()==4)GSvtrPause();
            else GSvtrPlay();
        }
        changed=GSinputButtonsChanged(1);
        pressed=GSinputButtonsPressed(1);
        if((pressed&changed&0x10)!=0)GSvtrSingleStep();
        changed=GSinputButtonsChanged(1);
        pressed=GSinputButtonsPressed(1);
        if((pressed&changed&8)!=0)GSvtrSetInfoDisp(!GSvtrGetInfoDisp(),0);
    }
    menuDaemon();GSmsgDaemon();_countPlayTime();
}
static void _mainThreadExec(unsigned long first,unsigned long second){
    u8 reset=GSgfxResetGetStatus();
    if((GSinputButtonsPressed(1)&0x1600)==0x1600 && reset!=0){
        _resettimer+=timeGetLastFrameSec();
        if(_resettimer>=0.5f)GSgfxReset(0);
    }else _resettimer=0.0f;
    GSthreadExecuteAll();
    if(!menuFieldIsOpen() && !peopleIsBlock())peopleDaemon(first,second);
    else peopleUpdateShadow();
}
static void _mainGBARead(unsigned long,unsigned long){
    s32 channel=1;
    do{if(!GSinputIsConnected(channel))gbaCommandKeyRead(channel);++channel;}while(channel<=4);
}
static void _mainPadRead(unsigned long,unsigned long){
    GSinputReadStart();
    s32 channel=1;
    do{if(!gbaCommandIsConnected(channel))GSinputRead(channel);++channel;}while(channel<=4);
    GSinputReadEnd();
}
#pragma force_active reset
