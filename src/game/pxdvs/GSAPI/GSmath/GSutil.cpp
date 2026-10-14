#include <global.h>

extern "C" f64 cos(f64);

f32 gCosTable[181];

extern "C" void GSmathInitCosTable() {
    for (s32 i = 0; i < 181; i++) {
        f32 degrees = 0.5f * i;
        gCosTable[i] = cos(0.017453292f * degrees);
    }
}
