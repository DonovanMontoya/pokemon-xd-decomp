#include <dolphin/types.h>
struct SoundData {u8 pad[2];u8 flags;u8 rest[9];};
struct SoundWaveData {u32 pad,a,b,c,d,path;};
typedef char SoundDataSize[sizeof(SoundData)==12?1:-1];
extern SoundData *snd_data;extern u32 *snd_data_number;
extern SoundWaveData *snd_wave_data;extern u32 *snd_wave_data_number;
u32 soundPlayEnvID,soundPlayID;
extern "C" {
void GSfsysReadWait(u32);f32 GSgfxVideoGetLastRenderTime();u8 GSgfxVideoGetVsyncRate();void GSlogWrite(const char*,...);u8 GSsndCheckEnv(u32);u8 GSsndCheckSE(u32);u8 GSsndCheckStream(u32);s32 GSsndClose(u32);void GSsndContinue(u32,u32,u32);s32 GSsndCreateEmitter(u32,f32 *);s32 GSsndCreateListener(f32 *);s32 GSsndGetStatus(u32);u32 GSsndGetVolume(u32);void GSsndOpenWaveDVD(u32,u32,u32,u32,u32,u32,u32);void GSsndPause(u32,u32,u32);s32 GSsndPlayVolume(u32,s32,s32,u32);void GSsndSetOriginalVolume(u32,u32,u32);void GSsndStop(u32,u32,u32);void GSthreadSwitch();
static u8 _soundCheckActive(u32);static void _soundCloseFastFadeout(u32);static void _soundFadeout(u32,s32,s32);static s32 _soundOpenPlay(u32,s32,s32,s32);static void _soundWait(u32);
void soundPlayWait(u32);void soundSetVolumeID(u32,u32,u32);s32 soundStop(u32,u32);
u8 soundCheckEnv(u32 id){return GSsndCheckEnv(id);}
u32 soundGetEnvID(){return soundPlayEnvID;}
u32 soundGetBGMID(){return soundPlayID;}
s32 soundPlayME(u32 id,s32 a,s32 b){if(id==0 || id>=*snd_data_number)return 0;GSsndPlayVolume(id,a,b,0);soundPlayWait(id);GSsndClose(id);return 1;}
void soundPlayWait(u32 id){for(;;){if(GSsndGetStatus(id)!=2)break;GSthreadSwitch();}}
void soundContinueBGMEX(u32 id,u32 ms,u8 wait){if(id!=0xFFFFFFFF){GSsndContinue(id,ms,0);if(wait==1)_soundWait(ms);}}
u32 soundPauseBGMEX(u32 ms,u8 wait){u32 id=soundGetBGMID();if(id!=0xFFFFFFFF){GSsndPause(id,ms,0);if(wait==1)_soundWait(ms);}return id;}
void soundOpenWave(u32 id){if(*snd_wave_data_number>id){SoundWaveData *p=snd_wave_data+id;GSsndOpenWaveDVD(id,p->path,0,p->a,p->b,p->c,p->d);}}
s32 soundOpenPlayME(u32 id,s32 a,s32 b){u32 old=soundPauseBGMEX(50,1);s32 result=soundPlayME(id,a,b);soundContinueBGMEX(old,500,1);return result;}
u32 soundGetVolume(u32 id){return GSsndGetVolume(id);}
void soundSetVolume(u32 volume,u32 time){soundSetVolumeID(soundGetBGMID(),time,volume);}
void soundSetVolumeID(u32 id,u32 time,u32 volume){GSsndSetOriginalVolume(id,time,volume);}
u8 soundCreateListener(){f32 p[3];p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;s32 result=GSsndCreateListener(p);return (u32)(result|-result)>>31;}
u8 soundCreateEmitter(u32 id,f32 x,f32 y,f32 z){f32 p[3];p[0]=x;p[1]=y;p[2]=z;s32 result=GSsndCreateEmitter(id,p);return (u32)(result|-result)>>31;}
void soundStopEnv(u32 time){soundStop(soundPlayEnvID,time);}
s32 soundStop(u32 id,u32 time){
 if(id==0 || id>=*snd_data_number)return 0;
 s32 bgm=0;if(soundPlayID==id){bgm=1;soundPlayID=0;}if(soundPlayEnvID==id){bgm=0;soundPlayEnvID=0;}
 if(GSsndCheckStream(id)==1){if(GSsndCheckSE(id)==0)_soundFadeout(time,bgm,1);return GSsndClose(id);}
 if(GSsndCheckSE(id)==0){_soundFadeout(time,bgm,1);if(bgm){GSlogWrite("soundStop: Warning! BGM cannot be stopped.(snd_id=%d)\n",id);return _soundOpenPlay(8,0,255,bgm);}return GSsndClose(id);}
 GSsndStop(id,time,0);return GSsndClose(id);
}
s32 soundOpenPlayEnvFadeOutIn(u32 id,u32 time,s32 a,s32 b){if(id==0 || id>=*snd_data_number)return 0;_soundFadeout(time,0,1);return _soundOpenPlay(id,a,b,0);}
s32 soundOpenPlayFadeOutIn(u32 id,u32 time,s32 a,s32 b){if(id==0 || id>=*snd_data_number)return 0;_soundFadeout(time,1,1);return _soundOpenPlay(id,a,b,1);}
s32 soundOpenPlayEnv(u32 id,s32 a,s32 b){return _soundOpenPlay(id,a,b,0);}
s32 soundOpenPlay(u32 id,s32 a,s32 b){return _soundOpenPlay(id,a,b,1);}
static s32 _soundOpenPlay(u32 id,s32 a,s32 b,s32 bgm){if(id==0 || id>=*snd_data_number)return 0;if(bgm==0){if(soundPlayEnvID!=0xFFFFFFFF)_soundCloseFastFadeout(soundPlayEnvID);soundPlayEnvID=id;}else if(((u32)((((u8 *)snd_data)[id*12+2]>>5)&1))!=1){if(soundPlayID!=id && soundPlayID!=0xFFFFFFFF)_soundCloseFastFadeout(soundPlayID);soundPlayID=id;}return GSsndPlayVolume(id,a,b,0);}
static void _soundFadeout(u32 time,s32 bgm,s32 wait){u32 id;if(bgm)id=soundGetBGMID();else id=soundGetEnvID();if(id!=0xFFFFFFFF && _soundCheckActive(id)==1){GSsndSetOriginalVolume(id,time,0);if(wait)_soundWait(time);}}
static void _soundCloseFastFadeout(u32 id){if(_soundCheckActive(id)==1){GSsndSetOriginalVolume(id,50,0);_soundWait(50);GSsndClose(id);}}
static u8 _soundCheckActive(u32 id){s32 s=GSsndGetStatus(id);if(s!=0 && s>=0 && s<4)return 1;return 0;}
static void _soundWait(u32 ms){f32 rate;f32 elapsed=0.0f;while(elapsed<(f32)ms/1000.0f){GSthreadSwitch();rate=GSgfxVideoGetVsyncRate();elapsed+=GSgfxVideoGetLastRenderTime()/rate;}}
void soundInitBGM(){GSfsysReadWait(0x99);}
void soundInit(){soundPlayID=0;soundPlayEnvID=0;}
}
