#ifndef FLOOR_OFFSCREEN_PRIVATE_HPP
#define FLOOR_OFFSCREEN_PRIVATE_HPP
#include <global.h>
struct FloorOffscreenData {
    u8 kind, animation;
    u16 index, width, height;
    u32 target, source, camera;
};
struct FloorOffscreenBundle {u32* count; FloorOffscreenData* records;};
struct FloorOffscreenRoot {u8 reserved00[0x28]; FloorOffscreenBundle** data;};
typedef char FloorOffscreenRecordSize[sizeof(FloorOffscreenData)==0x14?1:-1];
#endif
