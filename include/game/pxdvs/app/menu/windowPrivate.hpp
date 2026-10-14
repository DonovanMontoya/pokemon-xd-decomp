#ifndef WINDOW_PRIVATE_HPP
#define WINDOW_PRIVATE_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct WindowKeyInfo { u16 on, off, trigger, repeat, released; u8 reservedA[0x10]; };
struct WindowCursor { s16 base, index; };
struct WindowColor { union { u32 value; struct { u8 red, green, blue, alpha; } channels; }; };
struct tagWINDOW_WORK;
struct WindowSprite {
    WindowSprite *next;
    u8 type, flags;
    s16 itemID;
    u32 texture;
    u8 sequence[0x3C];
    u32 callback, message;
    s16 x, y, width, height;
    u32 resource;
    s16 sourceX, sourceY, sourceWidth, sourceHeight;
    WindowColor color;
    f32 scaleX, scaleY;
    u8 reserved70[4];
    u8 drawType, blendType, mode, reserved77;

};
struct WindowDrawParameter {
    u32 reserved0;
    u8 type,flags;
    s16 itemID;
    u32 texture;
    u8 sequence[0x3C];
    u32 callback,message;
    s16 x,y,width,height;
    u32 resource;
    s16 sourceX,sourceY,sourceWidth,sourceHeight;
    WindowColor color;
    f32 scaleX,scaleY;
    u8 reserved70[4];
    u8 screenRelative,blendType,mode,reserved77;
};
struct MENU_ITEM_dd_ {
    u8 flags,typeFlags,alpha,reserved3;
    s16 spriteID,x,y,width,height,cursorSpriteID;
    u32 message,callback;
    s16 nextItem;
    u8 reserved1A[2];
};
struct MenuData { u8 flags,flags1,flags2,reserved3,cursorID,reserved5; s16 firstItem,x,y; u8 reservedC[8]; s32 (*control)(tagWINDOW_WORK *); };
struct MenuSpriteValue { s16 x,y,width,height; u32 resource; };
union MenuSpriteFlags { u16 value; struct { u16 last:1, stretch:1, kind:2, sequence:12; } fields; };
struct MenuSpriteData { MenuSpriteFlags flags; u8 reserved2; s8 x,y; u8 alpha; u8 reserved6[0x3E]; u16 nextSprite; };
typedef char WindowDrawSize[sizeof(WindowDrawParameter)==0x78?1:-1];
typedef char MenuItemSize[sizeof(MENU_ITEM_dd_)==0x1C?1:-1];
typedef char MenuSpriteNextOffset[offsetof(MenuSpriteData,nextSprite)==0x44?1:-1];
struct tagWINDOW_WORK {
    u8 flags;
    s8 state, entered;
    u8 reserved3;
    s32 menuID;
    u8 reserved8;
    s8 priority;
    u8 closing, port;
    tagWINDOW_WORK *parent, *next, *previous;
    u8 inactive, itemCount, kind, openFlags;
    s32 layerID;
    u8 drawKind;
    u8 reserved21[3];
    WindowSprite *items, *cursor;
    u8 reserved2C[0x3C];
    u32 parameters[8];
    s32 value;
    s16 x, y;
    s16 frame;
    u8 reserved92, alpha;
    f32 scaleX, scaleY;
    s16 cursorBase, cursorIndex;
    u8 reservedA0[4];
    u8 finished, cancelled, reservedA6[2];
    u8 freeWork[0x10];
    void *allocation;
};
struct WindowSystem { u16 capacity; u8 reserved2[6]; s32 activeID; tagWINDOW_WORK *pool, *head; WindowKeyInfo key; WindowKeyInfo portKeys[4]; u8 reserved96[0xA]; };
struct WindowMessageWork { u32 message; u8 wait, option, reserved6[2]; u32 key; s16 width, height; };
typedef char WindowWorkSize[sizeof(tagWINDOW_WORK)==0xBC?1:-1];
typedef char WindowFreeOffset[offsetof(tagWINDOW_WORK,freeWork)==0xA8?1:-1];
typedef char WindowParameterOffset[offsetof(tagWINDOW_WORK,parameters)==0x68?1:-1];
typedef char WindowSpriteSize[sizeof(WindowSprite)==0x78?1:-1];
typedef char WindowKeySize[sizeof(WindowKeyInfo)==0x1A?1:-1];
typedef char WindowSystemSize[sizeof(WindowSystem)==0xA0?1:-1];
extern "C" {
void *windowGetFreeWork(tagWINDOW_WORK *);
u32 windowGetParam(tagWINDOW_WORK *,s32);
WindowKeyInfo *windowGetKeyInfo();
s32 windowGetActiveID();
tagWINDOW_WORK *windowSearchID(s32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *,WindowSprite *);
void *GSgfxLayerFindByID(s32);
void GSthreadSwitch();
}
#endif
