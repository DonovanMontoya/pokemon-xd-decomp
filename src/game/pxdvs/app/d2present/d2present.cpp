#include <global.h>
static void* Parameter;
extern "C" {
void GSfloorPush(u32);
void floorSetFadeScript(u32,u32);
void floorWaitForChange();
void d2presentOpen(void* parameter){Parameter=parameter;GSfloorPush(22);floorSetFadeScript(0x5960009,0);floorWaitForChange();}
}
