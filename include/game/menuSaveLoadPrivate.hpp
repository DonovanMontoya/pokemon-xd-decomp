#ifndef MENU_SAVELOAD_PRIVATE_HPP
#define MENU_SAVELOAD_PRIVATE_HPP
#include <dolphin/types.h>
struct tagWINDOW_WORK {u8 pad0;s8 mode,sub;u8 pad3;s32 id;};
struct tagSPRITE_WORK {u8 pad0[6];s16 id;};
class menuSaveload {public:u32 previousTime;menuSaveload();~menuSaveload();void Main();u8 ComfirmOverwriting();void SaveParameterSet();u8 IsReport();void Ctrl(tagWINDOW_WORK*);void _menuClose(s32);};
typedef char MenuSaveLoadSize[sizeof(menuSaveload)==4?1:-1];
#endif
