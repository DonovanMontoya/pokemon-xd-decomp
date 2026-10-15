#include <game/menuDataBiosPrivate.hpp>
extern "C" {
extern MenuDataRecord _menu_data[];
extern u32 _menu_data_number;
extern MenuItemRecord _menu_item[], _menu_itemmx[], _menu_item_tool[], _menu_item_debug[], _menu_item_pda[], _menu_itembt[], _menu_item_xd[];
extern MenuSpriteRecord _menu_sprite[];
extern u32 _menu_sprite_number;
extern MenuSequenceRecord _menu_seq[];
extern u32 _menu_seq_number;
extern MenuSoundRecord* menu_se;
extern u32* menu_se_number;
s32 pokecoloGetLanguage();
u32 dbgMenuGetLayerID();
MenuItemRecord* windowGetCursorToItem(s32);
MenuDataRecord* menuDataBiosGetPtr(s32);
MenuItemRecord* menuItemBiosGetPtr(s32, s32);
MenuSpriteRecord* menuSpriteBiosGetPtr(u32);
MenuSpriteValue* menuSpriteBiosGetValPtr(MenuSpriteRecord*);
#pragma dont_inline on
u32 menuBiosGetCursorSize(s32 menu) {
    MenuItemRecord* item = windowGetCursorToItem(menu);
    menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(item->sprite));
    u32 size = 0;
    switch (item->sprite) {
    case 0x7d: case 0xbe: size=0x147; break;
    case 0xc1: case 0xc2: size=0x14d; break;
    }
    return size;
}
u32 menuSeBiosGetSndId(MenuSoundRecord* sound, u8 type) {
    u32 id = 0;
    switch (type) {
    case 1: id=sound->sounds[2]; break;
    case 2: id=sound->sounds[3]; break;
    case 3: id=sound->sounds[4]; break;
    case 4: id=sound->sounds[0]; break;
    case 5: id=sound->sounds[1]; break;
    case 6: id=sound->sounds[5]; break;
    }
    return id;
}
MenuSoundRecord* menuSeBiosGetPtr(u32 index) {
    if (!menu_se) return 0;
    if (index>=*menu_se_number) return 0;
    return menu_se+index;
}
MenuSequenceRecord* menuSeqBiosGetPtr(u32 index) {
    if (index>=_menu_seq_number) return 0;
    return _menu_seq+index;
}
MenuSpriteValue* menuSpriteBiosGetValPtr(MenuSpriteRecord* sprite) {
    s32 index;
    switch(pokecoloGetLanguage()) {
    case 2: index=0; break;
    case 3: index=1; break;
    case 4: index=2; break;
    case 5: index=3; break;
    case 6: index=4; break;
    default:index=0; break;
    }
    return &sprite->values[index];
}
MenuSpriteRecord* menuSpriteBiosGetPtr(u32 index) {
    if (index>=_menu_sprite_number) return 0;
    return _menu_sprite+index;
}
void menuItemBiosSetXY(s32 menu, s32 index, s16 x, s16 y) {
    MenuItemRecord* item=menuItemBiosGetPtr(menu,index);
    if(item) {item->x=x;item->y=y;}
}
u32 menuItemBiosGetSelectFlag(s32 menu,s32 index) {
    MenuItemRecord* item=menuItemBiosGetPtr(menu,index);
    if(item) return item->selected!=0;
    return 0;
}
void menuItemBiosSetSelectFlag(s32 menu,s32 index,u32 selected) {
    MenuItemRecord* item=menuItemBiosGetPtr(menu,index);
    if(item) item->selected=(u8)selected;
}
u32 menuItemBiosGetLayerID(s32 menu) {
    MenuDataRecord* data=menuDataBiosGetPtr(menu);
    if(data->kind==3) return dbgMenuGetLayerID();
    return 7;
}
MenuItemRecord* menuItemBiosGetPtr(s32 menu,s32 index) {
    u32 kind=menuDataBiosGetPtr(menu)->kind;
    if(kind==0) return _menu_item+index;
    if(kind==1) return _menu_itemmx+index;
    if(kind==2) return _menu_item_tool+index;
    if(kind==3) return _menu_item_debug+index;
    if(kind==4) return _menu_item_pda+index;
    if(kind==5) return _menu_itembt+index;
    if(kind==6) return _menu_item_xd+index;
    return 0;
}
void menuDataBiosGetXY(s32 menu,s16* x,s16* y) {
    MenuDataRecord* data=menuDataBiosGetPtr(menu);
    if(x)*x=data->x;
    if(y)*y=data->y;
}
void menuDataBiosSetXY(s32 menu,s16 x,s16 y) {
    MenuDataRecord* data=menuDataBiosGetPtr(menu);
    data->x=x;data->y=y;
}
u8 menuDataBiosGetDispMax(s32 menu) {return menuDataBiosGetPtr(menu)->displayMax;}
MenuDataRecord* menuDataBiosGetPtr(s32 menu) {
    if(menu<0)menu=0;
    if((u32)menu>=_menu_data_number)menu=1;
    return _menu_data+menu;
}
}
