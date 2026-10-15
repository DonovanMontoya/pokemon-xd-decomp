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

struct MenuKeyInfo {
    u16 on, off, trigger, repeat, released;
    s8 timers[16];
};

struct MenuDataEx {
    u8 flags, flags1, flags2, reserved3, cursorID, reserved5;
    s16 firstItem, x, y;
    void (*cursor)(tagWINDOW_WORK *);
    void (*button)(tagWINDOW_WORK *);
    void (*control)(tagWINDOW_WORK *);
    void (*draw)(tagWINDOW_WORK *);
};

struct MENU_SE_DATA;

#include <libc/stdarg.h>

extern "C" {
void GSgfxLayerSetActive(u32);
void menuOffScreenDraw();
u8 winSeqCheckMove(s32);
u8 pauseIsPause();
void windowCloseMain(tagWINDOW_WORK *);
s32 floorGetMenuLayerID();
void fadeDaemon();
void spriteSetOffset(s32, s16, s16);
void spriteClearScissor(s32);
void spriteSetEnv(s32);
void spriteClearEnv(s32);
void winSpriteDraw(tagWINDOW_WORK *, WindowSprite *);
void winSetSequence(void *, u16);
void windowCreateCursorSprite(tagWINDOW_WORK *);
void winSeqMoveMenu(tagWINDOW_WORK *);
void floorExecScriptIntegerByName(const char *, s32, s32, s32, s32);
void windowInit(u16);
void cursorBiosInit();
void menuOffScreenInit();
void menuFaceInit(s32);
u8 menuSetEnablePort(u8);
void GSgfxVFInit(void *);
void GSgfxVFCreate(void *);
void GSgfxVFSetElement(void *, s32, s32, s32, u8);
void *GStextureLoad(void *);
void GSresRegisterResource(void *, u32, u32, void *);
void FlashSystemInitAll();
extern u8 menuHyperModeVf[0x440];
extern u8 uv_cmn_win_00[];
extern u8 uv_cmn_csr_00[];
extern u8 uv_common_icon_00[];
extern u8 tex_warning[];
extern u8 tex_warning_pstar[];
u8 GSinputIsConnected(s32);
s8 GSinputGetLeftStickYData(s32, s32);
s8 GSinputGetLeftStickXData(s32, s32);
s8 GSinputGetRightStickYData(s32, s32);
s8 GSinputGetRightStickXData(s32, s32);
u32 GSinputButtonsPressed(s32);
f64 atan2(f64, f64);
u8 gbaCommandIsConnected(s32);
u16 gbaCommandKeyPressed(s32);
WindowKeyInfo *windowGetPortKeyInfo(u8);
WindowKeyInfo *windowGetPortKeyInfo2(u8);
u32 timeGetLastFrameTime();
tagWINDOW_WORK *windowOpen(s32 *, s32, s32, u32, s32, va_list);
s32 windowCheckCursor(s32, u8);
s32 windowGetValue(s32);
void cursorBiosSetPos(u8, s32 *);
extern WINDOW_SYS_WORK winSysWork;
extern WINDOW_SYS_WORK winSysWork2;
MenuData *menuDataBiosGetPtr(s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
u32 menuSeBiosGetPtr(s32);
u16 menuSeBiosGetSndId(u32, s32);
void GSsndPlayNow(u32);
void GSlogWrite(const char *, ...);
u32 GSthreadGetCurrentThread();
s32 windowClose(tagWINDOW_WORK *, s32);
f64 timeGetLastFrameSec();
void menuOffScreenFadeSet(f32, f32);
void menuOffScreenFadeSync(u32);
void menuOffScreenRelease();
void menuOffScreenCreate(u32);
void menuOffScreenSetDisp(u32);
void menuOffScreenSetPriority(u32);
u32 menuOffScreenCheckEnable(u32);
}

#endif
