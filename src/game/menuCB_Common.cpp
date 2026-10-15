#include <game/menuCB_CommonPrivate.hpp>
extern "C" {
s32 winMsgCheck(u32);
void winMsgClose(u32);
void winMsgOpen(u32,u32,u32,u32);
s32 menuCBTrainerBios_GetHomePlace(MenuCBBiosTrainer*);
u8 gbaCommandIsConnected(s32);
MenuCBSpriteValue* menuSpriteBiosGetValPtr(void*);
s32 windowGetActiveID();
void menuCloseCustom(s32,u32,u32);
s32 menuCB_CurrentMenuID();
s32 menuCB_MenuPop();
static MenuCBStack _CBC;
#pragma dont_inline on
s32 menuCB_MessageDispCheck(u32 id){return winMsgCheck(id);}
void menuCB_MessageDispOff(){winMsgClose(0);}
void menuCB_MessageDispOn(u32 message,u32 flags){winMsgOpen(7,message,flags,0);}
s32 menuCB_GetDisconnectedGBA(){
    _MENUCBWORK* work;
    u32 i=0;
    work=&_CB;
    do {
        s32 gba=work->orgTrainers[0].unk24;
        if(gba!=0 && menuCBTrainerBios_GetHomePlace(&work->orgTrainers[0])!=0 && !gbaCommandIsConnected(gba))return gba;
        work=(_MENUCBWORK*)((u8*)work+sizeof(MenuCBBiosTrainer));
        ++i;
    }while(i<4);
    return 0;
}
void menuCB_SetSprite(MenuCBSprite* sprite,void* data){
    MenuCBSpriteValue* value=menuSpriteBiosGetValPtr(data);
    sprite->width=value->width;
    sprite->height=value->height;
    sprite->color=value->color;
    sprite->x=value->x;
    sprite->y=value->y;
}
s32 menuCB_MenuRollback(s32 menu){
    menuCB_MenuPop();
    while(menuCB_CurrentMenuID()!=menu){
        if(_CBC.depth==0)break;
        --_CBC.depth;
    }
    return menuCB_CurrentMenuID();
}
s32 menuCB_MenuPop(){
    s32 menu=menuCB_CurrentMenuID();
    s32 active=windowGetActiveID();
    if(active==menu)menuCloseCustom(menuCB_CurrentMenuID(),0,0);
    _CBC.entries[_CBC.depth].state=0;
    if(_CBC.depth==0)return -1;
    --_CBC.depth;
    return menuCB_CurrentMenuID();
}
void menuCB_MenuPush(s32 menu){
    if((u32)_CBC.depth<8){
        ++_CBC.depth;
        _CBC.entries[_CBC.depth].menu=menu;
        _CBC.entries[_CBC.depth].state=0;
    }
}
s32 menuCB_CurrentMenuID(){return _CBC.entries[_CBC.depth].menu;}
void menuCB_InitMenu(s32 menu){
    for(s32 i=0;i<8;i++){
        _CBC.entries[i].menu=0;
        _CBC.entries[i].state=0;
    }
    _CBC.entries[0].menu=menu;
    _CBC.depth=0;
}
}
