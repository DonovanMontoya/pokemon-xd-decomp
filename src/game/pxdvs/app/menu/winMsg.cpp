#include <game/pxdvs/app/menu/windowPrivate.hpp>
extern "C" {
void spriteSetOffset(s32,s16,s16);
void spriteSetEnv(s32);
void menuSubDrawMsgWindow2(s32,s32,s16,s16,s16,u8,s32);
void GSmsgMain(s32,u32,u32,s32);
void GSmsgKill(u32);
void GSmsgExec(u32,u8,u8);
u32 GSmsgGetRect(u32);
s32 GSmsgIsCheck(u32);
void winSeqSetMenu(s32,s32);
u8 winSeqIsCheck(s32,s32);
u8 menuIsCheck(s32);
void menuCloseCustom(s32,s32,u8);
s32 menuOpenCustom(s32,s32,void *,s32,u8,s32,...);
void winMsgClose(u8);
s32 winMsgCheck();
void winMsgOpen(s8,void *,bool,bool);
u8 _winMsgOpenErrWin;
static s8 _winMsgType = -1;
static s16 menuPos = -2;
}
static s32 _winMsgGetMenuID(s8);
static s32 _winMsgOpenSub(s8,void *,bool,bool,bool,u8,bool);
extern "C" {
s32 winMsgDraw(tagWINDOW_WORK *window, WindowSprite *sprite) {
    s16 width;
    s16 height;
    WindowMessageWork *work = static_cast<WindowMessageWork *>(windowGetFreeWork(window));
    s32 layer = winSpriteGetLayerID(window,sprite);
    GSgfxLayerFindByID(layer);
    if (window->menuID == 0x53) { width=work->width; height=work->height; }
    else { width=sprite->width; height=sprite->height; }
    spriteSetOffset(layer,window->x+sprite->x,window->y+(sprite->y+static_cast<s16>((sprite->height-4)-height)));
    spriteSetEnv(layer);
    switch (window->menuID) {
    case 42: break;
    case 52: case 53:
        menuSubDrawMsgWindow2(layer,0,menuPos,width,height,window->alpha,1); break;
    case 20:
        menuSubDrawMsgWindow2(layer,0,menuPos,width,height,window->alpha,1); break;
    }
    switch (window->state) {
    case 0: case 3: case 5: break;
    case 2:
        if (window->menuID != 20) { GSmsgMain(layer,work->message,work->key,(static_cast<s8>(window->flags)&4)==0); work->key=0; }
        break;
    }
    return 0;
}
s32 winMsgCtrlYesNo(tagWINDOW_WORK *window) {
    switch (window->state) {
    case 0: if (window->entered==0) { winSeqSetMenu(window->menuID,0x24);window->entered=1; } break;
    case 3: if (window->entered==0) { winSeqSetMenu(window->menuID,0x17B);window->entered=1; } break;
    }
    return 0;
}
s32 winMsgCtrl(tagWINDOW_WORK *window) {
    WindowMessageWork *work=static_cast<WindowMessageWork *>(windowGetFreeWork(window));
    u8 reset=0;
    switch (window->state) {
    case 1: break;
    case 0:
        if(work->message!=0) GSmsgKill(work->message);
        work->message=windowGetParam(window,0);
        work->wait=windowGetParam(window,1)!=0;
        work->option=windowGetParam(window,2);
        if(window->entered==0) reset=1;
        if(winSeqIsCheck(window->menuID,0x2C)==1) reset=1;
        if(window->closing!=0) reset=1;
        if(reset!=0) {
            if(window->menuID!=0x2A) {
                if(window->menuID!=0x52) winSeqSetMenu(window->menuID,0x28);
                else winSeqSetMenu(window->menuID,0x24);
            }
            window->entered=1;
        }
        if(window->menuID==0x53) { u32 rect=GSmsgGetRect(work->message);work->width=rect>>16;work->height=rect; }
        break;
    case 2:
        if(window->entered==0) { GSmsgExec(work->message,work->wait,work->option);window->entered=1; }
        if(GSmsgIsCheck(work->message)!=0) window->finished=0;else window->finished=1;
        break;
    case 3:
        if(window->entered==0) {
            if(window->menuID!=0x2A) {
                if(window->menuID!=0x52) winSeqSetMenu(window->menuID,0x2C);
                else winSeqSetMenu(window->menuID,0x17B);
            }
            window->entered=1;
        }
        break;
    case 5: GSmsgKill(work->message);work->message=0;break;
    }
    return 0;
}
void winMsgButton(tagWINDOW_WORK *window) { WindowMessageWork *work=static_cast<WindowMessageWork *>(windowGetFreeWork(window)); work->key=windowGetKeyInfo()->trigger; }
void winMsgCloseLevelUpStatus(u8 wait) { winMsgClose(wait); }
void winMsgOpenLevelUpFiledStatus(void *message,bool wait) { _winMsgOpenSub(9,message,wait,1,0,0,0); }
void winMsgOpenLevelUpStatus(void *message,bool wait) { _winMsgOpenSub(5,message,wait,1,0,0,0); }
void winMsgCloseError() { s32 menu=_winMsgGetMenuID(6);if(menuIsCheck(menu)!=0) menuCloseCustom(menu,2,0);_winMsgOpenErrWin=0; }
void winMsgOpenError(void *message,bool wait,bool option) { _winMsgOpenSub(6,message,wait,option,0,0,0); }
void winMsgCloseFight(u8 wait) { winMsgClose(wait); }
u8 winMsgCloseCheckFight() { return ((static_cast<u32>(static_cast<s8>(winMsgCheck()))>>31)^1); }
void winMsgOpenFightNoWait(void *message,bool wait,bool option) { _winMsgOpenSub(4,message,wait,option,1,0,0); }
void winMsgOpenFight2(void *message,bool wait,bool option,bool special) { _winMsgOpenSub(4,message,wait,option,0,0,special); }
void winMsgOpenFight(void *message,bool wait,bool option) { winMsgOpen(4,message,wait,option); }
s8 winMsgCheckField() { return winMsgCheck(); }
void winMsgCloseField(u8 wait) { winMsgClose(wait); }
void winMsgOpenFieldWithSE(void *message,bool wait,bool option,u8 sound) { _winMsgOpenSub(3,message,wait,option,0,sound,0); }
void winMsgOpenField(void *message,bool wait,bool option) { _winMsgOpenSub(3,message,wait,option,0,0,0); }
s32 winMsgCheck() {
    tagWINDOW_WORK *window=windowSearchID(_winMsgGetMenuID(_winMsgType));
    if(window==0) return -1;
    if(window->finished!=0) return 0;
    return window->cancelled==0 ? 1 : 0;
}
void winMsgClose(u8 wait) {
    if(_winMsgOpenErrWin!=0) {
        if(wait==0) return;
        do { GSthreadSwitch(); } while(_winMsgOpenErrWin!=0);
    }
    s32 menu=_winMsgGetMenuID(_winMsgType);
    if(menuIsCheck(menu)!=0) menuCloseCustom(menu,2,wait);
    _winMsgType=-1;
}
void winMsgOpenWithSE(s8 type,void *message,bool wait,bool option,u8 sound) { _winMsgOpenSub(type,message,wait,option,0,sound,0); }
void winMsgOpen(s8 type,void *message,bool wait,bool option) { _winMsgOpenSub(type,message,wait,option,0,0,0); }
}
static s32 _winMsgOpenSub(s8 type,void *message,bool wait,bool option,bool background,u8 sound,bool special) {
    bool blocking=wait;
    bool overlay=background;
    u8 flags=0;
    if(_winMsgGetMenuID(type)==0) return 0;
    s32 parent;
    if(type!=6) {
        if(type!=static_cast<s8>(_winMsgType)) winMsgClose(blocking);
        _winMsgType=type;
        parent=windowGetActiveID();
    } else { parent=-1;_winMsgOpenErrWin=1;blocking=0;overlay=1; }
    if(option!=0) flags|=1;
    if(overlay!=0) flags|=2;
    s32 menu=_winMsgGetMenuID(type);
    s32 mode;
    if(special!=0) mode=2;else mode=0;
    return menuOpenCustom(menu,parent,0,mode,blocking,3,message,flags,static_cast<s32>(sound));
}
static s32 _winMsgGetMenuID(s8 type) {
    s32 menu=0;
    switch(type) {
    case 0:return 0x52;case 1:return 0x34;case 2:return 0x33;case 3:return 0x52;
    case 4:return 0x53;case 5:return 0x14;case 6:return 0x2A;case 7:return 0xB6;
    case 9:menu=0x29;case 8:return menu;default:return menu;
    }
}
