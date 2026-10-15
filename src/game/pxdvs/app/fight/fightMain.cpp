#include <global.h>
static u8 _fightSoundOpenPlayStart;
static u8 _fightSoundOpenPlayEnvStart;
static u16 _fight_reg_wzx_generic_data_id_ary[] = {87,0,158,0,38,0,39,0,40,0,41,0,42,0,43,0,44,0,45,0,60,0,46,3,47,3,48,3,49,3,50,3,51,3,52,3,55,3,57,3,88,3};
static u16 _fight_reg_wzx_generic_data_id_ary_num=42;
extern "C" {
u16 fightGetFightEncountDataId(); u32 fightEncountGetEnvSndDataId();u32 fightEncountGetBgmSndDataId(); void soundOpenPlayEnv(u32,s32,s32);void soundOpenPlay(u32,s32,s32);
s32 wazaSequenceSysGetWazaGroupID(u16,s32);u8 GSfsysPreReadKeepCache(s32);s32 GSfsysGetStatus(s32);void GSthreadSwitch();f32 GSgfxVideoGetLastRenderTime();
s32 battleCameraIsSimple();void battleCameraDoSimple();void battleCameraDoFull();void battleCameraStop();void battleCameraStartRandom(s32);
s32 dbgMenuGetEnable();void dbgMenuSetEnable(s32);u8 dbgMenuFightGetFightDebugMenuOpenFlag();void dbgMenuMain(s32);void menuGetKeyInfo(u16*,s32);u32 dbgMenuFightGetMsgSpeedToFrame(u32);
u8 fightFloor_GetFightType(void*);u8 fightFloor_GetFightTypeTrainerNum(void*);u8 fightFloor_GetFightTypeFightoutPokemonNum(void*);void *fightFloorGetValidFightSidePtr(void*,u16);void *fightSideGetValidFightTrainerPtr(void*,u16);void *fightTrainer_GetSequencePtr(void*);void *fightTrainerGetValidFightOutPokemonPtr(void*,u16);void *fightOutPokemon_GetSequencePtr(void*);void Sequence_SetVisibility(void*,s32);void battleGridStoreModelVisibilityFlags();
static void _fightMainWaitFrameSub__FUl(u32);
s32 fightRegWzxLoadGenric(u16 id){s32 group=wazaSequenceSysGetWazaGroupID(id,4);if(GSfsysPreReadKeepCache(group)==0)return 0;for(;;){s32 status=GSfsysGetStatus(group);if(status==0 || status<0)break;GSthreadSwitch();}return 1;}
void fightRegWzxLoadAll(s8 category){for(u16 i=0;i<_fight_reg_wzx_generic_data_id_ary_num;i+=2){if(category<0 || category==_fight_reg_wzx_generic_data_id_ary[i+1])fightRegWzxLoadGenric(_fight_reg_wzx_generic_data_id_ary[i]);}}
void fightSoundOpenPlayEnv(u8 start){if(_fightSoundOpenPlayEnvStart!=1 && start!=0 && fightGetFightEncountDataId()!=0){u32 id=fightEncountGetEnvSndDataId();if(id)soundOpenPlayEnv(id,1000,255);_fightSoundOpenPlayEnvStart=1;}}
void fightSoundOpenPlay(u8 start){if(_fightSoundOpenPlayStart!=1 && start!=0 && fightGetFightEncountDataId()!=0){u32 id=fightEncountGetBgmSndDataId();if(id)soundOpenPlay(id,0,255);_fightSoundOpenPlayStart=1;}}
void fightSoundOpenPlayInit(){_fightSoundOpenPlayStart=0;_fightSoundOpenPlayEnvStart=0;}
void fightMainSetAllDispFlag(s32 visible){
 void *side;u16 j,k,i;u32 trainers,pokemon;void *trainer;
 fightFloor_GetFightType(0);trainers=fightFloor_GetFightTypeTrainerNum(0);pokemon=fightFloor_GetFightTypeFightoutPokemonNum(0);
 for(i=0;i<2;i++){side=fightFloorGetValidFightSidePtr(0,i);if(side){for(j=0;j<trainers;j++){trainer=fightSideGetValidFightTrainerPtr(side,j);if(trainer){void *seq=fightTrainer_GetSequencePtr(trainer);if(seq){Sequence_SetVisibility(seq,visible);for(k=0;k<pokemon;k++){void *poke=fightTrainerGetValidFightOutPokemonPtr(trainer,k);if(poke){seq=fightOutPokemon_GetSequencePtr(poke);if(seq)Sequence_SetVisibility(seq,visible);}}}}}}}
 battleGridStoreModelVisibilityFlags();
}
s32 fightMainAllCamera(u8 simple,u8 stop){s32 previous=battleCameraIsSimple();if(simple==1)battleCameraDoSimple();else battleCameraDoFull();if(stop)battleCameraStop();battleCameraStartRandom(1);return previous;}
void fightMainDebugMenu(){u16 keys[16];s32 frames;s32 previous=dbgMenuGetEnable();dbgMenuSetEnable(1);if(dbgMenuFightGetFightDebugMenuOpenFlag()==1)dbgMenuMain(1);else {frames=0;while((u8)frames<4){menuGetKeyInfo(keys,1);if(keys[0]&0x800)break;GSthreadSwitch();frames=(s32)((f32)(u8)frames+GSgfxVideoGetLastRenderTime());}if((u8)frames<4)dbgMenuMain(1);}dbgMenuSetEnable(previous);}
void fightMainWaitFrameEffect(u32 frames){_fightMainWaitFrameSub__FUl(frames);}
void fightMainWaitFrame(u32 frames){_fightMainWaitFrameSub__FUl(dbgMenuFightGetMsgSpeedToFrame(frames));}
static void _fightMainWaitFrameSub__FUl(u32 frames){if(frames){for(u32 elapsed=0;elapsed<frames;) {GSthreadSwitch();elapsed=(f32)elapsed+GSgfxVideoGetLastRenderTime();}}}
}
