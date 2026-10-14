#include <game/pxdvs/app/memcard/savedataBiosLayout.hpp>
#pragma dont_inline on
extern "C" {
extern void* now_savedata_ptr;
extern u8 pokecolo_savedata[];
#define SAVEDATA_PTR(name, offset) void* savedataBiosGet##name##Ptr(void* p) { if (p == 0) return 0; return (u8*)p + offset; }
SAVEDATA_PTR(AnywaySave, SAVEDATA_ANYWAY)
SAVEDATA_PTR(Relive, SAVEDATA_RELIVE)
SAVEDATA_PTR(Yobi4, SAVEDATA_YOBI4)
SAVEDATA_PTR(Yobi3, SAVEDATA_YOBI3)
SAVEDATA_PTR(Yobi2, SAVEDATA_YOBI2)
SAVEDATA_PTR(Yobi1, SAVEDATA_YOBI1)
SAVEDATA_PTR(FlagSavedata, SAVEDATA_FLAG_LEVEL0)
SAVEDATA_PTR(ExRibbon, SAVEDATA_EX_RIBBON)
SAVEDATA_PTR(Darkpokemon, SAVEDATA_DARKPOKEMON)
SAVEDATA_PTR(Tool, SAVEDATA_TOOL)
SAVEDATA_PTR(MemoData, SAVEDATA_MEMO_DATA)
SAVEDATA_PTR(Sodateya, SAVEDATA_SODATEYA)
SAVEDATA_PTR(Mailbox, SAVEDATA_MAILBOX)
SAVEDATA_PTR(FlagLevel2, SAVEDATA_FLAG_LEVEL2)
SAVEDATA_PTR(FlagLevel1, SAVEDATA_FLAG_LEVEL1)
SAVEDATA_PTR(FlagLevel0, SAVEDATA_FLAG_LEVEL0)
SAVEDATA_PTR(Pcbox, SAVEDATA_PCBOX)
SAVEDATA_PTR(Hero, SAVEDATA_HERO)
SAVEDATA_PTR(Gamedata, SAVEDATA_GAMEDATA)
void savedataBiosSetNowSavedataPtr(void* p) { if (p != 0) now_savedata_ptr = p; }
void* savedataBiosGetNowSavedataPtr(void) { return now_savedata_ptr; }
void* savedataBiosGetSavedataBufferPtr(void) { return pokecolo_savedata; }
}
