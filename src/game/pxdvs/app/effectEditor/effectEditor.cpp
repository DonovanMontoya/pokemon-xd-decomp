#include <global.h>
extern "C" {
static u8 _floorModuleEffectViewer[0x2C];
void* effectViewerGetFloorModule() { return _floorModuleEffectViewer; }
}
