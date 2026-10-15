#include <dolphin/types.h>
static u8 _DBG=1;
extern "C" void menuCBDebug_SkipAGBConnection(bool skip){_DBG=!skip;}
