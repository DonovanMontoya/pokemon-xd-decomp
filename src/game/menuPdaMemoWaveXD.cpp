#include <game/menuPcBoxPokemonLayout.hpp>
enum GSgfxLayerID {WaveLayerDummy};
struct NakigoeDispWork {s8 *data;f32 count;u32 sound;f32 start;s32 time;f32 end;s32 samples;f32 alpha,speed;};
class pdaMemoNakigoe {public:NakigoeDispWork waves[8];u32 index;pdaMemoNakigoe(){Reset();}void Reset(){for(s32 i=0;i<8;i++)waves[i].data=0;index=0;DispInit();}void DispInit();void SetNakigoe(long);void SetSE(unsigned long);u16 GetVocie(long);s8 *GetWaveDispDataAddress(long);void DispRequest(s8*,unsigned long);void NakigoeDispFunc(tagWINDOW_WORK*,tagSPRITE_WORK*);void DispFuncSub(NakigoeDispWork*,GSgfxLayerID);u8 NakigoeCheck();};
static pdaMemoNakigoe *_nakigoe;
extern "C" {s32 GSinputButtonsChanged(s32);s32 GSinputButtonsPressed(s32);void GSthreadSwitch();void GSsndPlay(u32,s32,s32);s32 GSsndGetStatus(u32);u16 memoDataGetCount(s32);void *menuPdaMemoListGetPokemonDataPointer(s32);u16 pokemonDataBiosGetVoice(void*);s8 *pokemonNakigoeDataBiosGetDataAddress(void*);}
extern "C" void menuPdaMemoWaveHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){if(_nakigoe)_nakigoe->NakigoeDispFunc(w,s);}
extern "C" void menuPdaMemoWaveInit(){if(_nakigoe){_nakigoe->Reset();}}
extern "C" void menuPdaMemoWave(s32 pokemon){if(!_nakigoe)_nakigoe=new pdaMemoNakigoe;_nakigoe->Reset();_nakigoe->SetNakigoe(pokemon);pdaMemoNakigoe *work=_nakigoe;for(;;){if(!work->NakigoeCheck())return;s32 changed=GSinputButtonsChanged(1);s32 pressed=GSinputButtonsPressed(1);if(pressed&changed&0x100)work->SetNakigoe(pokemon);else{changed=GSinputButtonsChanged(1);pressed=GSinputButtonsPressed(1);if(pressed&changed&0x200)return;}GSthreadSwitch();}}
void pdaMemoNakigoe::SetNakigoe(long pokemon){u16 voice=GetVocie(pokemon);SetSE(voice);DispRequest(GetWaveDispDataAddress(pokemon),voice);}
void pdaMemoNakigoe::SetSE(unsigned long id){GSsndPlay(id,0,0);}
u16 pdaMemoNakigoe::GetVocie(long pokemon){if(memoDataGetCount(0)){void *p=menuPdaMemoListGetPokemonDataPointer(pokemon);if(p)return pokemonDataBiosGetVoice(p);return 0xFFFF;}return 0xFFFF;}
void pdaMemoNakigoe::DispInit(){for(s32 i=0;i<8;i++)DispRequest(0,0);}
void pdaMemoNakigoe::DispRequest(s8 *data,unsigned long sound){index++;if(index>=8)index=0;waves[index].data=data;waves[index].sound=sound;waves[index].start=0;waves[index].end=0;waves[index].time=0;waves[index].samples=1;waves[index].alpha=255.0f;waves[index].speed=0.5f;for(s32 i=index-1;i>=0;i--){waves[i].time+=waves[i].count;waves[i].speed+=0.2f;}for(u32 i=7;i>index;i--){waves[i].time+=waves[i].count;waves[i].speed+=0.2f;}}
void pdaMemoNakigoe::NakigoeDispFunc(tagWINDOW_WORK *w,tagSPRITE_WORK *){for(s32 i=0;i<8;i++)DispFuncSub(&waves[i],(GSgfxLayerID)w->layer);for(s32 i=index-1;i>=0;i--){waves[i].alpha-=10.0f;if(waves[i].alpha<0)waves[i].alpha=0;}for(u32 i=7;i>index;i--){waves[i].alpha-=10.0f;if(waves[i].alpha<0)waves[i].alpha=0;}}
u8 pdaMemoNakigoe::NakigoeCheck(){u8 playing=0;for(s32 i=0;i<8;i++)if(waves[i].data){switch(GSsndGetStatus(waves[i].sound)){case 0:case 1:break;case 2:playing=1;break;}}return playing;}
s8 *pdaMemoNakigoe::GetWaveDispDataAddress(long pokemon){if((s32)memoDataGetCount(0)){void *p=menuPdaMemoListGetPokemonDataPointer(pokemon);if(p)return pokemonNakigoeDataBiosGetDataAddress(p);return 0;}return 0;}
