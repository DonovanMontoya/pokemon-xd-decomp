#include <game/pxdvs/app/menu/windowPrivate.hpp>
#include <libc/string.h>
#include <libc/stdarg.h>
extern "C" {
void *GSmemAlloc(s32);
void GSmemFree(void *);
void GSlogWrite(const char *,...);
void *GSthreadGetCurrentThread();
MenuData *menuDataBiosGetPtr(s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32,s16);
s32 menuItemBiosGetLayerID(s32);
MenuSpriteData *menuSpriteBiosGetPtr(u16);
MenuSpriteValue *menuSpriteBiosGetValPtr(MenuSpriteData *);
s32 menuGetCursorItemID(s32);
s8 menuGetEnablePort();
s32 floorGetMenuLayerID();
void menuPlaySe(s32,s32);
void spriteGetOffset(s32,s16 *,s16 *);
void winSpriteDraw(tagWINDOW_WORK *,WindowDrawParameter *);
void winSpriteRelease(WindowSprite **);
WindowSprite *winSpriteAdd(WindowSprite **);
void winSpriteInit();
void winSetSequence(void *,u16);
u32 GSmsgGetRect(u32);
WindowCursor cursorBiosGetPos(u8);
WindowSystem winSysWork;
WindowSystem winSysWork2;
}
static tagWINDOW_WORK *_winGetNewWork();
static s32 _winInsertWork(tagWINDOW_WORK *,s8);
static bool _windowCheckParent(tagWINDOW_WORK *,tagWINDOW_WORK *);
static s32 _windowDeleteWork(tagWINDOW_WORK *);
static void _windowSetCloseFlag(tagWINDOW_WORK *,bool);
static s32 _windowCreateItemSprite(tagWINDOW_WORK *);
static void _winCalcWindowSize(long,const MENU_ITEM_dd_ *,s16 *,s16 *);
extern "C" {
WindowKeyInfo *windowGetKeyInfo2();
void windowDrawSprite2(s16,s16,s16,s16,s32,tagWINDOW_WORK *,u16,s32,s32);
void *windowGetAllocPtr(tagWINDOW_WORK *window) { if(window!=0)return window->allocation;return 0; }
void *windowAllocMemory(tagWINDOW_WORK *window,s32 size) {
    if(window==0)return 0;
    if(window->allocation!=0) { GSmemFree(window->allocation);window->allocation=0; }
    if(size<=0)return 0;
    window->allocation=GSmemAlloc(size);
    if(window->allocation==0)return 0;
    return windowGetAllocPtr(window);
}
void *windowGetFreeWork(tagWINDOW_WORK *window) { if(window!=0)return window->freeWork;return 0; }
void windowSetParam(tagWINDOW_WORK *window,s32 index,u32 value) { if(window!=0)window->parameters[index]=value; }
u32 windowGetParam(tagWINDOW_WORK *window,s32 index) { if(window!=0)return window->parameters[index];return 0; }
void windowDrawSprite(s16 x,s16 y,tagWINDOW_WORK *work,u16 spriteID,s32 flags,s32 layer) {
    if(spriteID!=0) { MenuSpriteValue *value=menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(spriteID));windowDrawSprite2(x,y,value->width,value->height,-1,work,spriteID,flags,layer); }
}
void windowDrawSpriteCursor(s16 x,s16 y,s32 color,tagWINDOW_WORK *work,u16 spriteID,s32 flags,s32 layer,const s32 *offset,s32 followingColor) {
    s32 index=0;
    tagWINDOW_WORK temporary;
    MenuSpriteData *sprite=menuSpriteBiosGetPtr(spriteID);
    for(;;) {
        MenuSpriteValue *value=menuSpriteBiosGetValPtr(sprite);
        WindowDrawParameter draw;
        memset(&draw,0,sizeof(draw));
        draw.type=7;
        if(index==0)draw.color.value=color;else draw.color.value=followingColor;
        draw.scaleX=1.0f;draw.scaleY=1.0f;
        if(layer==floorGetMenuLayerID())draw.screenRelative=1;
        switch(sprite->flags.fields.kind) {
        case 1:draw.flags|=1;draw.resource=value->resource;break;
        case 2:draw.flags|=2;draw.texture=value->resource;break;
        case 3:draw.flags|=0x10;draw.texture=value->resource;break;
        }
        if(index==0) { draw.x=x+sprite->x;draw.y=y+sprite->y; }
        else { draw.x=x+(sprite->x+offset[0]);draw.y=y+(sprite->y+offset[1]); }
        draw.width=value->width;draw.height=value->height;
        draw.sourceX=value->x;draw.sourceY=value->y;draw.sourceWidth=value->width;draw.sourceHeight=value->height;
        draw.color.channels.alpha=(sprite->alpha*draw.color.channels.alpha)/255;
        if((flags&1)!=0)draw.width=-draw.width;
        if((flags&2)!=0)draw.height=-draw.height;
        if(work==0) { work=&temporary;memset(work,0,sizeof(*work));spriteGetOffset(layer,&temporary.x,&temporary.y);temporary.layerID=layer;temporary.frame=-1; }
        winSpriteDraw(work,&draw);
        if(sprite->flags.fields.last!=0)break;
        ++index;
        sprite=menuSpriteBiosGetPtr(sprite->nextSprite);
    }
}
void windowDrawSprite2(s16 x,s16 y,s16 width,s16 height,s32 color,tagWINDOW_WORK *work,u16 spriteID,s32 flags,s32 layer) {
    tagWINDOW_WORK temporary;
    MenuSpriteData *sprite=menuSpriteBiosGetPtr(spriteID);
    for(;;) {
        MenuSpriteValue *value=menuSpriteBiosGetValPtr(sprite);
        WindowDrawParameter draw;
        memset(&draw,0,sizeof(draw));draw.color.value=color;draw.type=7;draw.scaleX=1.0f;draw.scaleY=1.0f;
        if(layer==floorGetMenuLayerID())draw.screenRelative=1;
        switch(sprite->flags.fields.kind) {
        case 1:draw.flags|=1;draw.resource=value->resource;break;
        case 2:draw.flags|=2;draw.texture=value->resource;break;
        case 3:draw.flags|=0x10;draw.texture=value->resource;break;
        }
        draw.x=x+sprite->x;draw.width=width;draw.height=height;draw.y=y+sprite->y;
        draw.sourceX=value->x;draw.sourceY=value->y;draw.sourceWidth=value->width;draw.sourceHeight=value->height;
        draw.color.channels.alpha=(sprite->alpha*draw.color.channels.alpha)/255;
        if((flags&1)!=0)draw.width=-width;
        if((flags&2)!=0)draw.height=-draw.height;
        if(work==0) { work=&temporary;memset(work,0,sizeof(*work));spriteGetOffset(layer,&temporary.x,&temporary.y);temporary.layerID=layer;temporary.frame=-1; }
        winSpriteDraw(work,&draw);
        if(sprite->flags.fields.last!=0)break;
        sprite=menuSpriteBiosGetPtr(sprite->nextSprite);
    }
}
void windowDrawSprite3(s16 x,s16 y,s16 width,s16 height,s32 color,tagWINDOW_WORK *work,u16 spriteID,s16 sourceX,s16 sourceY,s16 sourceWidth,s16 sourceHeight,s32 flags,s32 layer) {
    tagWINDOW_WORK temporary;
    MenuSpriteData *sprite=menuSpriteBiosGetPtr(spriteID);
    for(;;) {
        MenuSpriteValue *value=menuSpriteBiosGetValPtr(sprite);
        WindowDrawParameter draw;
        memset(&draw,0,sizeof(draw));draw.color.value=color;draw.type=7;draw.scaleX=1.0f;draw.scaleY=1.0f;
        if(layer==floorGetMenuLayerID())draw.screenRelative=1;
        switch(sprite->flags.fields.kind) {
        case 1:draw.flags|=1;draw.resource=value->resource;break;
        case 2:draw.flags|=2;draw.texture=value->resource;break;
        case 3:draw.flags|=0x10;draw.texture=value->resource;break;
        }
        draw.x=x+sprite->x;draw.width=width;draw.height=height;draw.y=y+sprite->y;
        draw.sourceX=value->x+sourceX;draw.sourceWidth=sourceWidth;draw.sourceY=value->y+sourceY;draw.sourceHeight=sourceHeight;
        draw.color.channels.alpha=(sprite->alpha*draw.color.channels.alpha)/255;
        if((flags&1)!=0)draw.width=-width;
        if((flags&2)!=0)draw.height=-draw.height;
        if(work==0) { work=&temporary;memset(work,0,sizeof(*work));spriteGetOffset(layer,&temporary.x,&temporary.y);temporary.layerID=layer;temporary.frame=-1; }
        winSpriteDraw(work,&draw);
        if(sprite->flags.fields.last!=0)break;
        sprite=menuSpriteBiosGetPtr(sprite->nextSprite);
    }
}
MENU_ITEM_dd_ *windowGetCursorToItem(tagWINDOW_WORK *window) {
    s32 index=0;
    MENU_ITEM_dd_ *item=menuItemBiosGetPtr(window->menuID,menuDataBiosGetPtr(window->menuID)->firstItem);
    for(;;) {
        if((item->flags&0x80)!=0) { if(window->cursorIndex==index)return item;++index; }
        if((item->flags&0x40)!=0)return 0;
        item=menuItemBiosGetPtr(window->menuID,item->nextItem);
    }
}
s32 windowGetValue(s32 menuID) {
    s32 value;
    tagWINDOW_WORK *window=windowSearchID(menuID);
    if(window!=0) {
        if(window->cancelled!=0)value=-1;
        else {
            MenuData *data=menuDataBiosGetPtr(window->menuID);
            if(data!=0) {
                switch((data->flags>>3)&3) {
                case 0:value=0;break;case 1:value=window->cursorBase+window->cursorIndex;break;
                case 2:value=window->value;break;case 3:value=menuGetCursorItemID(menuID);break;
                }
            } else value=window->cursorBase+window->cursorIndex;
        }
    } else value=-1;
    return value;
}
WindowCursor windowGetCursor(s32 menuID) {
    static const WindowCursor zero={0,0};
    WindowCursor result=zero;
    tagWINDOW_WORK *window=windowSearchID(menuID);
    if(window!=0) { result.base=window->cursorBase;result.index=window->cursorIndex; }
    return result;
}
s32 windowCheckCursor(s32 menuID,u8 wait) {
    for(;;) {
        tagWINDOW_WORK *window=windowSearchID(menuID);
        if(window==0) { GSlogWrite("%s(0x%08x)  ウィンドウが存在しない\n",__FUNCTION__,menuID);return 0; }
        if(window->finished!=0)return 0;
        if(window->cancelled!=0)return 0;
        if(wait!=0) {
            if(GSthreadGetCurrentThread()==0) { GSlogWrite("%s(0x%08x)  スレッドから呼ぶようにしてください\n",__FUNCTION__,menuID);break; }
            GSthreadSwitch();
        } else break;
    }
    return 1;
}
s32 windowGetActiveID() { return winSysWork.activeID; }
WindowSprite *windowSearchItemID(tagWINDOW_WORK *window,u16 itemID) {
    if(window==0)return 0;
    WindowSprite *sprite=window->items;
    while(sprite!=0) { if(sprite->itemID==itemID)return sprite;sprite=sprite->next; }
    return 0;
}
tagWINDOW_WORK *windowSearchID(s32 menuID) {
    if(menuID<=0)return 0;
    tagWINDOW_WORK *window=winSysWork.head;
    while(window!=0) { if(window->menuID==menuID)return window;window=window->next; }
    return 0;
}
void windowCloseMain(tagWINDOW_WORK *window) {
    MenuData *data=menuDataBiosGetPtr(window->menuID);
    if(data->control!=0) { window->state=5;data->control(window); }
    _windowDeleteWork(window);
}
s32 windowClose(tagWINDOW_WORK *window,s32 mode) {
    u32 detach=mode&2;
    u8 selected=0;
    bool force=(mode&4)!=0;
    if(detach==0)for(tagWINDOW_WORK *child=winSysWork.head;child!=0;child=child->next) if(_windowCheckParent(child,window)!=0)_windowSetCloseFlag(child,force);
    if((mode&1)==0 && window!=0) {
        _windowSetCloseFlag(window,force);
        if(detach!=0)for(tagWINDOW_WORK *child=winSysWork.head;child!=0;child=child->next) if(child->parent==window)child->parent=window->parent;
    }
    tagWINDOW_WORK *active=windowSearchID(windowGetActiveID());
    while(active!=0) {
        if(active->closing!=0 || active->inactive!=0) {
            for(tagWINDOW_WORK *child=winSysWork.head;child!=0;child=child->next) {
                if(child->closing==0 && child->inactive==0 && _windowCheckParent(child,active->parent)!=0) { selected=1;winSysWork.activeID=child->menuID; }
            }
            if(selected==0) { active=active->parent;continue; }
        } else winSysWork.activeID=active->menuID;
        break;
    }
    if(active==0)winSysWork.activeID=0;
    return 0;
}
void windowCreateCursorSprite(tagWINDOW_WORK *window) {
    MenuData *data=menuDataBiosGetPtr(window->menuID);
    MENU_ITEM_dd_ *item=windowGetCursorToItem(window);
    if(item!=0) {
        winSpriteRelease(&window->cursor);
        if(item->cursorSpriteID!=0) {
            s32 index=0;
            MenuSpriteData *record=menuSpriteBiosGetPtr(item->cursorSpriteID);
            for(;;) {
                MenuSpriteValue *value=menuSpriteBiosGetValPtr(record);
                WindowSprite *sprite=winSpriteAdd(&window->cursor);
                if(sprite==0) { winSpriteRelease(&window->cursor);return; }
                switch(record->flags.fields.kind) {
                case 1:sprite->flags|=1;sprite->resource=value->resource;break;
                case 2:sprite->flags|=2;sprite->texture=value->resource;break;
                case 3:sprite->flags|=0x10;sprite->texture=value->resource;break;
                }
                sprite->itemID=data->firstItem;
                sprite->x=item->x+record->x;sprite->y=item->y+record->y;
                sprite->width=value->width;sprite->height=value->height;
                sprite->sourceX=value->x;sprite->sourceY=value->y;sprite->sourceWidth=value->width;sprite->sourceHeight=value->height;
                sprite->color.channels.alpha=record->alpha;
                if(record->flags.fields.sequence!=0)winSetSequence(sprite->sequence,record->flags.fields.sequence);
                if(index!=0)winSetSequence(sprite->sequence,0x141);
                if(record->flags.fields.last!=0)break;
                ++index;record=menuSpriteBiosGetPtr(record->nextSprite);
            }
        }
    }
}
tagWINDOW_WORK *windowOpen(s32 *selection,s32 menuID,s32 parentID,u8 flags,s32 parameterCount,va_list parameters) {
    tagWINDOW_WORK *parent=windowSearchID(parentID);
    s32 layer;
    if(parent!=0)layer=parent->layerID;else layer=menuItemBiosGetLayerID(menuID);
    if(layer==-1)return 0;
    MenuData *data=menuDataBiosGetPtr(menuID);
    tagWINDOW_WORK *window=windowSearchID(menuID);
    if(window==0) {
        s8 priority;
        if((data->flags&2)!=0)priority=100;
        else if((flags&2)!=0)priority=100;
        else {
            if(parentID==0)parentID=windowGetActiveID();
            parent=windowSearchID(parentID);
            if(parent!=0)priority=parent->priority+1;else priority=0;
            if(priority>100)priority=100;
        }
        window=_winGetNewWork();
        if(window==0)return 0;
        window->state=0;window->menuID=menuID;window->priority=priority;
        window->kind=(data->flags1>>1)&7;window->parent=parent;window->x=data->x;window->y=data->y;
        window->layerID=layer;window->drawKind=(data->flags>>5)&7;
        MENU_ITEM_dd_ *item=menuItemBiosGetPtr(menuID,data->firstItem);
        for(;;) {
            if((item->flags&0x80)!=0)++window->itemCount;
            if((item->flags&0x40)!=0)break;
            item=menuItemBiosGetPtr(menuID,item->nextItem);
        }
        _windowCreateItemSprite(window);
        _winInsertWork(window,priority);
        menuPlaySe(menuID,4);
    } else { window->finished=0;window->cancelled=0;window->state=0;window->entered=1; }
    if(selection==0) {
        if(data->cursorID!=0) { WindowCursor cursor=cursorBiosGetPos(data->cursorID);window->cursorBase=cursor.base;window->cursorIndex=cursor.index; }
    } else { window->cursorBase=0;window->cursorIndex=static_cast<s8>(*selection); }
    windowCreateCursorSprite(window);
    window->port=menuGetEnablePort();window->openFlags=flags;
    if(parameterCount>8)parameterCount=8;
    for(s32 i=0;i<parameterCount;++i)window->parameters[i]=va_arg(parameters,u32);
    if(((data->flags2>>5)&7)==0)window->finished=1;
    else if((flags&4)==0)winSysWork.activeID=menuID;
    if(winSysWork.activeID!=menuID)window->inactive=1;
    if(data->control!=0)data->control(window);
    if(window->entered!=0) { window->closing=0;window->state=2;window->entered=0; }
    return window;
}
void windowInit(u16 capacity) {
    memset(&winSysWork,0,sizeof(winSysWork));memset(&winSysWork2,0,sizeof(winSysWork2));
    s32 size=capacity*sizeof(tagWINDOW_WORK);
    winSysWork.pool=static_cast<tagWINDOW_WORK *>(GSmemAlloc(size));
    if(winSysWork.pool==0) { GSlogWrite("windowInitの初期化に失敗しました\n");return; }
    winSysWork.capacity=capacity;memset(winSysWork.pool,0,size);winSpriteInit();
}
WindowKeyInfo *windowGetPortKeyInfo2(u8 ports) {
    const u8 masks[4]={1,2,4,8};
    static WindowKeyInfo key;
    memset(&key,0,sizeof(key));
    for(s32 i=0;i<4;++i)if((ports&masks[i])!=0) {
        WindowKeyInfo *port=&winSysWork2.portKeys[i];
        key.on|=port->on;key.off|=port->off;key.trigger|=port->trigger;key.repeat|=port->repeat;key.released|=port->released;
    }
    return &key;
}
WindowKeyInfo *windowGetPortKeyInfo(u8 ports) {
    const u8 masks[4]={1,2,4,8};
    static WindowKeyInfo key;
    memset(&key,0,sizeof(key));
    for(s32 i=0;i<4;++i)if((ports&masks[i])!=0) {
        WindowKeyInfo *port=&winSysWork.portKeys[i];
        key.on|=port->on;key.off|=port->off;key.trigger|=port->trigger;key.repeat|=port->repeat;key.released|=port->released;
    }
    return &key;
}
u32 windowGetKeyTrg() { u32 key=windowGetKeyInfo()->trigger;u32 other;if((windowGetKeyInfo()->on&0xF)!=0)other=0;else other=windowGetKeyInfo2()->trigger;return key|other; }
u32 windowGetKeyOn() { u32 key=windowGetKeyInfo()->on;u32 other;if((key&0xF)!=0)other=0;else other=windowGetKeyInfo2()->on;return key|other; }
u32 windowGetKeyRepeat() { u32 key=windowGetKeyInfo()->repeat;u32 other;if((windowGetKeyInfo()->on&0xF)!=0)other=0;else other=windowGetKeyInfo2()->repeat;return key|other; }
WindowKeyInfo *windowGetKeyInfo2() { return &winSysWork2.key; }
WindowKeyInfo *windowGetKeyInfo() { return &winSysWork.key; }
}
static void _windowSetCloseFlag(tagWINDOW_WORK *window,bool force) { if(force==0 || (menuDataBiosGetPtr(window->menuID)->flags&1)==0)window->closing=1; }
static s32 _windowCreateItemSprite(tagWINDOW_WORK *window) {
    s16 width,height;
    s16 itemID=menuDataBiosGetPtr(window->menuID)->firstItem;
    MENU_ITEM_dd_ *first=menuItemBiosGetPtr(window->menuID,itemID);
    winSpriteRelease(&window->items);
    _winCalcWindowSize(window->menuID,first,&width,&height);
    for(;;) {
        MENU_ITEM_dd_ *item=menuItemBiosGetPtr(window->menuID,itemID);
        WindowSprite *sprite=winSpriteAdd(&window->items);
        if(sprite==0) { winSpriteRelease(&window->items);return 1; }
        sprite->itemID=itemID;sprite->x=item->x;sprite->y=item->y;sprite->width=item->width;sprite->height=item->height;
        sprite->color.channels.alpha=item->alpha;sprite->blendType=(item->flags>>4)&3;sprite->drawType=item->flags&0xF;sprite->mode=(item->typeFlags>>6)&3;
        if(item->spriteID!=0) {
            MenuSpriteData *record=menuSpriteBiosGetPtr(item->spriteID);
            MenuSpriteValue *value=menuSpriteBiosGetValPtr(record);
            switch(record->flags.fields.kind) {
            case 1:sprite->flags|=1;sprite->resource=value->resource;break;
            case 2:sprite->flags|=2;sprite->texture=value->resource;break;
            case 3:sprite->flags|=0x10;sprite->texture=value->resource;break;
            }
            sprite->sourceX=value->x;sprite->sourceY=value->y;sprite->sourceWidth=value->width;sprite->sourceHeight=value->height;
            sprite->color.channels.alpha=(sprite->color.channels.alpha*record->alpha)/255;
            if(record->flags.fields.stretch!=0) { sprite->width=width;sprite->height=height; }
            if(record->flags.fields.sequence!=0)winSetSequence(sprite->sequence,record->flags.fields.sequence);
        }
        sprite->message=item->message;
        if(item->callback!=0) { sprite->flags|=8;sprite->callback=item->callback; }
        if((item->flags&0x40)!=0)break;
        itemID=item->nextItem;
    }
    return 0;
}
static bool _windowCheckParent(tagWINDOW_WORK *window,tagWINDOW_WORK *parent) {
    if(window==parent)return 0;
    while(window!=0) { window=window->parent;if(window==parent)return 1; }
    return 0;
}
static s32 _windowDeleteWork(tagWINDOW_WORK *window) {
    if(window==0)return 0;
    if(window->previous==0)winSysWork.head=window->next;else window->previous->next=window->next;
    if(window->next!=0)window->next->previous=window->previous;
    winSpriteRelease(&window->items);winSpriteRelease(&window->cursor);
    if(window->allocation!=0) { GSmemFree(window->allocation);window->allocation=0; }
    window->flags=0;window->menuID=0;return 0;
}
static s32 _winInsertWork(tagWINDOW_WORK *window,s8 priority) {
    if(winSysWork.head==0)winSysWork.head=window;
    else {
        tagWINDOW_WORK *current=winSysWork.head;
        for(;;) {
            if(current->priority>priority) {
                window->previous=current->previous;window->next=current;
                if(current->previous==0)winSysWork.head=window;else current->previous->next=window;
                current->previous=window;break;
            }
            if(current->next==0) { current->next=window;window->previous=current;window->next=0;break; }
            current=current->next;
        }
    }
    return 0;
}
static tagWINDOW_WORK *_winGetNewWork() {
    tagWINDOW_WORK *window=winSysWork.pool;
    for(s32 i=0;i<winSysWork.capacity;++i,++window) {
        if(static_cast<s8>(window->flags)==0) { memset(window,0,sizeof(*window));window->flags=7;window->scaleX=1.0f;window->scaleY=1.0f;window->frame=-1;return window; }
    }
    GSlogWrite("Error!! _winGetNewWork() [ワークの確保に失敗]\n");return 0;
}
static void _winCalcWindowSize(long menuID,const MENU_ITEM_dd_ *item,s16 *width,s16 *height) {
    s16 minX=640;*width=0;s16 minY=480;s32 maxX=0,maxY=0;*height=0;
    for(;;) {
        menuSpriteBiosGetPtr(item->spriteID);
        u32 rect;
        if(item->message!=0)rect=GSmsgGetRect(item->message);else rect=0;
        if(minX>item->x)minX=item->x;
        if(maxX<item->x+item->width)maxX=item->x+item->width;
        if(maxX<item->x+static_cast<s16>(rect>>16))maxX=item->x+static_cast<s16>(rect>>16);
        if(minY>item->y)minY=item->y;
        if(maxY<item->y+item->height)maxY=item->y+item->height;
        if(maxY<item->y+static_cast<s16>(rect))maxY=item->y+static_cast<s16>(rect);
        if((item->flags&0x40)!=0)break;
        item=menuItemBiosGetPtr(menuID,item->nextItem);
    }
    *width=maxX-minX;*height=maxY-minY;
}
