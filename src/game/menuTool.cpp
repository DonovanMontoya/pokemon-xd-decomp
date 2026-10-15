#include <dolphin/types.h>
s32 _menuToolSelect;
extern "C" void menuToolSetSelect(s32 selected){_menuToolSelect=selected;}
extern "C" void menuToolInit(){_menuToolSelect=0;}
