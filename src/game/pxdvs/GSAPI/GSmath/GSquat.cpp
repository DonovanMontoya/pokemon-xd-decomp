#include <dolphin/mtx.h>

struct GSzeroQuaternion {
    f32 x;
    f32 y;
    f32 z;
    f32 w;

    GSzeroQuaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
};

GSzeroQuaternion zeroQuaternion;
