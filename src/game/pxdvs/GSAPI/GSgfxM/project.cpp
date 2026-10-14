#include <dolphin/gx.h>
#include <game/pxdvs/GSAPI/GScamera/GScamera.hpp>
extern "C" f32 (*GSgfxMatrixGetPtr(s32))[4];

static f32 g_projViewPort[6] = {0, 0, 640, 480, 0, 1};
static f32 g_projProjectParams[7];
static f32 (*g_projCameraMatrix)[4];
static f32 (*g_projInvCameraMatrix)[4];
static f32 (*g_projProjectMatrix)[4];

extern "C" void GSgfxProjectSetupParameters() {
    f32 (*projection)[4] = GSgfxMatrixGetPtr(4);
    f32 (*inverse)[4] = GSgfxMatrixGetPtr(3);
    f32 (*camera)[4] = GSgfxMatrixGetPtr(2);
    g_projCameraMatrix = camera;
    g_projInvCameraMatrix = inverse;
    g_projProjectMatrix = projection;
    if (camera && projection) {
        g_projProjectParams[0] = 0;
        g_projProjectParams[1] = projection[0][0];
        g_projProjectParams[2] = projection[0][2];
        g_projProjectParams[3] = projection[1][1];
        g_projProjectParams[4] = projection[1][2];
        g_projProjectParams[5] = projection[2][2];
        f32 last = projection[2][3];
        g_projViewPort[0] = 0;
        g_projProjectParams[6] = last;
        g_projViewPort[1] = 0;
        g_projViewPort[2] = 640;
        g_projViewPort[3] = 480;
        g_projViewPort[4] = 0;
        g_projViewPort[5] = 1;
    }
}

extern "C" void GSgfxProjectSetupCameraParameters(GScamera* selected) {
    if (!selected) {
        f32 (*projection)[4] = GSgfxMatrixGetPtr(4);
        f32 (*inverse)[4] = GSgfxMatrixGetPtr(3);
        f32 (*camera)[4] = GSgfxMatrixGetPtr(2);
        g_projCameraMatrix = camera;
        g_projInvCameraMatrix = inverse;
        g_projProjectMatrix = projection;
        if (camera && projection) {
            g_projProjectParams[0] = 0;
            g_projProjectParams[1] = projection[0][0];
            g_projProjectParams[2] = projection[0][2];
            g_projProjectParams[3] = projection[1][1];
            g_projProjectParams[4] = projection[1][2];
            g_projProjectParams[5] = projection[2][2];
            f32 last = projection[2][3];
            g_projViewPort[0] = 0;
            g_projProjectParams[6] = last;
            g_projViewPort[1] = 0;
            g_projViewPort[2] = 640;
            g_projViewPort[3] = 480;
            g_projViewPort[4] = 0;
            g_projViewPort[5] = 1;
        }
    } else {
        f32 (*projection)[4] = GScameraGetProjMatrixPtr(selected);
        f32 (*inverse)[4] = GScameraGetInvMatrixPtr(selected);
        f32 (*camera)[4] = GScameraGetMatrixPtr(selected);
        g_projCameraMatrix = camera;
        g_projInvCameraMatrix = inverse;
        g_projProjectMatrix = projection;
        if (camera && projection) {
            g_projProjectParams[0] = 0;
            g_projProjectParams[1] = projection[0][0];
            g_projProjectParams[2] = projection[0][2];
            g_projProjectParams[3] = projection[1][1];
            g_projProjectParams[4] = projection[1][2];
            g_projProjectParams[5] = projection[2][2];
            f32 last = projection[2][3];
            g_projViewPort[0] = 0;
            g_projProjectParams[6] = last;
            g_projViewPort[1] = 0;
            g_projViewPort[2] = 640;
            g_projViewPort[3] = 480;
            g_projViewPort[4] = 0;
            g_projViewPort[5] = 1;
        }
    }
}

extern "C" s32 GSgfxProjectFast(Vec* position, Vec* output) {
    if (!g_projCameraMatrix || !g_projProjectMatrix) return 0;
    Vec relative;
    Vec direction;
    f32 dx = g_projInvCameraMatrix[0][2];
    f32 dy = g_projInvCameraMatrix[1][2];
    f32 dz = g_projInvCameraMatrix[2][2];
    direction.x = dx;
    direction.y = dy;
    direction.z = dz;
    f32 x = g_projInvCameraMatrix[0][3];
    f32 y = g_projInvCameraMatrix[1][3];
    f32 z = g_projInvCameraMatrix[2][3];
    relative.x = x;
    relative.y = y;
    relative.z = z;
    PSVECSubtract(position, &relative, &relative);
    f32 depth = PSVECDotProduct(&direction, &relative);
    f32 plane = g_projProjectMatrix[2][3];
    if (depth <= -plane && depth >= plane) return 1;
    GXProject(position->x, position->y, position->z, g_projCameraMatrix,
        g_projProjectParams, g_projViewPort, &output->x, &output->y, &output->z);
    if (depth > 0) {
        output->x = -output->x;
        output->y = -output->y;
        output->z = -1;
    }
    return 2;
}

extern "C" s32 GSgfxProjectFastList(Vec* positions, Vec* outputs, u32 count) {
    if (!g_projCameraMatrix || !g_projProjectMatrix) return 0;
    u32 projected = count;
    s32 result = 2;
    for (u32 i = 0; i < count; ++i, ++positions, ++outputs) {
        Vec relative;
        Vec direction;
        f32 dx = g_projInvCameraMatrix[0][2];
        f32 dy = g_projInvCameraMatrix[1][2];
        f32 dz = g_projInvCameraMatrix[2][2];
        direction.x = dx;
        direction.y = dy;
        direction.z = dz;
        f32 x = g_projInvCameraMatrix[0][3];
        f32 y = g_projInvCameraMatrix[1][3];
        f32 z = g_projInvCameraMatrix[2][3];
        relative.x = x;
        relative.y = y;
        relative.z = z;
        PSVECSubtract(positions, &relative, &relative);
        f32 depth = PSVECDotProduct(&direction, &relative);
        f32 plane = g_projProjectMatrix[2][3];
        s32 status;
        if (depth <= -plane && depth >= plane) {
            status = 1;
        } else {
            GXProject(positions->x, positions->y, positions->z, g_projCameraMatrix,
                g_projProjectParams, g_projViewPort, &outputs->x, &outputs->y, &outputs->z);
            if (depth > 0) {
                outputs->x = -outputs->x;
                outputs->y = -outputs->y;
                outputs->z = -1;
            }
            status = 2;
        }
        if (status == 1) {
            result = 3;
            --projected;
            outputs->z = 1;
            outputs->y = 1;
            outputs->x = 1;
        }
    }
    if (!projected) result = 1;
    return result;
}
