#include <game/menuWorldMapModelPrivate.hpp>
void *operator new(unsigned long);void operator delete(void*);
extern "C" {s32 floorGetCurrentGroupID();u16 HSD_Rand();void cameraPlayAnime(s32,u32,s32,f32);void GSthreadSwitch();void GSfloorPop();}
struct MoveAnimation {s16 motion;s16 pad;u32 camera;};
static MoveAnimation _animeTable[15]={{0,0,0x1B491800},{1,0,0x1B781800},{2,0,0x1B791800},{3,0,0x1B7A1800},{4,0,0x1B7B1800},{5,0,0x1B7C1800},{6,0,0x1B7D1800},{7,0,0x1B7E1800},{8,0,0x1B7F1800},{9,0,0x1B801800},{10,0,0x1B811800},{11,0,0x1B821800},{12,0,0x1B831800},{13,0,0x1B841800},{14,0,0x1B851800}};
class WorldMapMoveDemo:public WorldMapModel {public:void Main();};
WorldMapMoveDemo *pMoveDemo;
extern "C" void menuWorldMapMoveDemoExit(){if(pMoveDemo){delete pMoveDemo;pMoveDemo=0;}}
extern "C" void menuWorldMapMoveDemoMain(){if(pMoveDemo)pMoveDemo->Main();}
extern "C" void menuWorldMapMoveDemoInit(){pMoveDemo=new WorldMapMoveDemo;}
void WorldMapMoveDemo::Main(){s32 group=floorGetCurrentGroupID();SetModel(group,0x1B4A0400,false);MoveAnimation*animation=&_animeTable[(u16)(HSD_Rand()%15)];cameraPlayAnime(group,animation->camera,0,0.0f);SetMotion(0x1B4A1000,animation->motion,0.0f,false);f32 end=GetAnimeFrameCount(0x1B4A1000,animation->motion);u32 modelId=0x1B4A1000;end-=30.0f;for(;;){if(end<GetAnimeFrame(modelId))break;GSthreadSwitch();}GSfloorPop();}
