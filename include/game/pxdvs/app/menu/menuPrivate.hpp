#ifndef MENU_PRIVATE_H
#define MENU_PRIVATE_H

#include <game/pxdvs/app/menu/windowPrivate.hpp>

struct WINDOW_SYS_WORK {
    u16 capacity;
    u8 reserved2[6];
    s32 activeID;
    tagWINDOW_WORK *pool, *head;
    WindowKeyInfo key;
    WindowKeyInfo portKeys[4];
    u8 enablePort;          // 0x96
    u8 reserved97;
    s32 lastError;          // 0x98
    s32 lastMenuID;         // 0x9C
};

struct MENU_SE_DATA;

extern "C" {
extern WINDOW_SYS_WORK winSysWork;
extern WINDOW_SYS_WORK winSysWork2;
MenuData *menuDataBiosGetPtr(s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
u32 menuSeBiosGetPtr(s32);
u16 menuSeBiosGetSndId(u32, s32);
void GSsndPlayNow(u32);
void GSlogWrite(const char *, ...);
u32 GSthreadGetCurrentThread();
void windowClose(s32, s32);
f32 timeGetLastFrameSec();
void menuOffScreenFadeSet(f32, f32);
void menuOffScreenFadeSync(u32);
void menuOffScreenRelease();
void menuOffScreenCreate(u32);
void menuOffScreenSetDisp(u32);
void menuOffScreenSetPriority(u32);
u32 menuOffScreenCheckEnable(u32);
}

#endif
