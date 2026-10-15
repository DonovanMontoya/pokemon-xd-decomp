#ifndef MENU_CB_COMMON_PRIVATE_HPP
#define MENU_CB_COMMON_PRIVATE_HPP
#include <game/menuCB_BiosLayout.hpp>
#include <libc/stddef.h>
struct MenuCBStackEntry {s32 menu; u32 state;};
struct MenuCBStack {MenuCBStackEntry entries[8]; s32 depth;};
struct MenuCBSpriteValue {s16 x,y,width,height; u32 color;};
struct MenuCBSprite {u8 reserved00[0x54];s16 width,height;u32 color;s16 x,y;};
typedef char MenuCBStackSize[sizeof(MenuCBStack)==0x44?1:-1];
typedef char MenuCBTrainerSize[sizeof(MenuCBBiosTrainer)==0x1320?1:-1];
typedef char MenuCBTrainerSourceOffset[offsetof(_MENUCBWORK,orgTrainers)==0x4c98?1:-1];
#endif
