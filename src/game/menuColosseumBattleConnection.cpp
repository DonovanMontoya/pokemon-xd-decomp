#include <dolphin/types.h>
static bool _menuMainExec;
extern "C" void menuColosseumBattleConnectionExit(){}
extern "C" void menuColosseumBattleConnectionMain(){_menuMainExec=true;}
extern "C" void menuColosseumBattleConnectionInit(){_menuMainExec=false;}
