#pragma force_active on
#include <dolphin/types.h>
extern "C" {s32 floorGetCurrentGroupID();void*GSresGetResource(s32,u32);void menuKeyDiscExit(){}void menuKeyDiscMain(){GSresGetResource(floorGetCurrentGroupID(),0x117F0000);}void menuKeyDiscInit(){}}

#pragma force_active reset
