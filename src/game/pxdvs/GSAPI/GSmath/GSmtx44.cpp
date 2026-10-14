#include <dolphin/mtx.h>

extern "C" void GSmtx44Perspective(Mtx44 matrix, f32 fieldOfView, f32 aspect,
                                     f32 nearPlane, f32 farPlane) {
    C_MTXPerspective(matrix, fieldOfView, aspect, nearPlane, farPlane);
}

extern "C" void GSmtx44Ortho(Mtx44 matrix, f32 top, f32 bottom, f32 left,
                              f32 right, f32 nearPlane, f32 farPlane) {
    C_MTXOrtho(matrix, top, bottom, left, right, nearPlane, farPlane);
}
