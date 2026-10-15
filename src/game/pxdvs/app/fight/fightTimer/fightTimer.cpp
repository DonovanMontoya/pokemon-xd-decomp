#include <global.h>
struct FightTimer { u8 over; u8 special; u8 pad[2]; f32 elapsed; f32 limit; u32 thread; };
extern "C" {
extern s32 GSfloorGetCurrentFloorGroupID(void);
extern f32 GSgfxVideoGetLastRenderTime(void);
extern u8 GSgfxVideoGetVsyncRate(void);
extern void GSthreadBlock(void);
extern u32 GSthreadCreate(u32,s32,u32,u32,u32,void (*)(void*));
extern void GSthreadSetArgs(u32,void*);
extern void GSthreadSwitch(void);
extern void GSthreadTerminate(void);
extern s32 menuCBRule_GetBattleTimeLimit(void);
extern s32 menuCBRule_GetCommandTimeLimit(void);
static void fightTimerThreadFunc(void*);
static FightTimer gCommandTimer;
static FightTimer gBattleTimer;
static u8 fightTimerIsOver(FightTimer* p){if(p->special==1)return 0;if(p->thread==0)return 1;return p->over;}
static f32 fightTimerGetNokoriTime(FightTimer* p){if(p->special==1)return -3600.0f;if(p->thread==0)return 0.0f;return p->limit-(p->elapsed/(f32)GSgfxVideoGetVsyncRate());}
static s32 fightTimerBlock(FightTimer* p){if(p->special==1)return 0;if(p->thread==0)return 0;GSthreadBlock();return 1;}
static void fightTimerStart(FightTimer* p){if(p->special!=1){u32 t=GSthreadCreate(1,GSfloorGetCurrentFloorGroupID(),0x4000,1,0,fightTimerThreadFunc);if(t!=0){p->thread=t;GSthreadSetArgs(1,p);}}}
static void fightTimerTerminate(FightTimer* p){if(p->thread!=0)GSthreadTerminate();p->over=0;p->elapsed=0.0f;p->limit=0.0f;p->thread=0;p->special=0;}
static void fightTimerInit(FightTimer* p,f32 t){if(p->thread!=0)fightTimerTerminate(p);p->over=0;p->elapsed=0.0f;if(t<0.0f){p->special=1;p->limit=-3600.0f;}else{p->special=0;p->limit=t;}p->thread=0;}
static void fightTimerThreadFunc(void* arg){FightTimer* p=(FightTimer*)arg;p->elapsed=0.0f;for(;;){if(!(p->elapsed<60.0f*p->limit))break;GSthreadSwitch();p->elapsed=p->elapsed+GSgfxVideoGetLastRenderTime();}p->over=1;for(;;)GSthreadSwitch();}
void fightTimerCommandTerminate(){fightTimerTerminate(&gCommandTimer);}
void fightTimerCommandIsOver(){fightTimerIsOver(&gCommandTimer);}
void fightTimerCommandGetNokoriTime(){fightTimerGetNokoriTime(&gCommandTimer);}
void fightTimerCommandBlock(){fightTimerBlock(&gCommandTimer);}
void fightTimerCommandStart(){fightTimerStart(&gCommandTimer);}
void fightTimerCommandInit(){fightTimerInit(&gCommandTimer,(f32)menuCBRule_GetCommandTimeLimit());}
void fightTimerAllIsOver(){fightTimerIsOver(&gBattleTimer);}
void fightTimerAllGetNokoriTime(){fightTimerGetNokoriTime(&gBattleTimer);}
void fightTimerAllBlock(){fightTimerBlock(&gBattleTimer);}
void fightTimerAllStart(){fightTimerStart(&gBattleTimer);}
void fightTimerAllInit(){fightTimerInit(&gBattleTimer,(f32)menuCBRule_GetBattleTimeLimit());}
void fightTimerAllTerminate(){fightTimerTerminate(&gBattleTimer);}
}
