#ifndef MENU_INTERRUPT_PRIVATE_HPP
#define MENU_INTERRUPT_PRIVATE_HPP
#include <dolphin/types.h>
struct tagWINDOW_WORK {u8 pad0;s8 mode,sub;u8 pad3;s32 id;u8 pad8[0x60];s32 *data;};
struct tagSPRITE_WORK {u8 pad0[6];s16 id;u8 pad8[0x5F];u8 alpha;};
struct UndertakerData {u8 pad[0x24];s32 flag;};
extern UndertakerData *undertakerdata;
#endif
