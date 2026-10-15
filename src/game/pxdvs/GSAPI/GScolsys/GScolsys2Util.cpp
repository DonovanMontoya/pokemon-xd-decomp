#include <dolphin/mtx.h>
extern "C" {
u8 GScolsys2UtilGetCpPlaneLine(Vec *out, f32 *rate, Vec *normal, Vec *plane, Vec *start, Vec *end) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 ny = normal->y;
    f32 nx = normal->x;
    f32 nz = normal->z;
    f32 dot = nz * delta.z + (nx * delta.x + ny * delta.y);
    if (0.0f == dot) return 0;
    f32 t = (normal->z * (plane->z - start->z) + (normal->x * (plane->x - start->x) + normal->y * (plane->y - start->y))) / dot;
    PSVECScale(&delta, &delta, t);
    PSVECAdd(&delta, start, out);
    *rate = t;
    return 1;
}
f32 GScolsys2UtilGetCpLinePoint(Vec *out, Vec *start, Vec *end, Vec *point) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 dot = delta.z * delta.z + (delta.x * delta.x + delta.y * delta.y);
    if (dot == 0.0f) { *out = *start; return 0.0f; }
    f32 t = (delta.z * (point->z - start->z) + (delta.x * (point->x - start->x) + delta.y * (point->y - start->y))) / dot;
    PSVECScale(&delta, &delta, t);
    PSVECAdd(&delta, start, out);
    return t;
}
void GScolsy2UtilGetPointExtentionLine(Vec *out, Vec *start, Vec *end, f32 distance) {
    Vec delta;
    PSVECSubtract(end, start, &delta);
    f32 length = PSVECMag(&delta);
    if (length != 0.0f) {
        PSVECScale(&delta, &delta, distance / length);
        PSVECAdd(&delta, start, out);
    }
}
u8 GScolsy2UtilChkInTri(Vec *point, Vec *triangle, Vec *normal) {
    Vec projected[3];
    f32 ax = normal->x > 0.0f ? normal->x : -normal->x;
    f32 ay = normal->y > 0.0f ? normal->y : -normal->y;
    f32 az = normal->z > 0.0f ? normal->z : -normal->z;
    f32 orientation;
    s32 a, b;
    if (ax < ay) {
        if (ay < az) { orientation = normal->z; a = 0; b = 1; }
        else { orientation = normal->y; a = 2; b = 0; }
    } else if (ax > az) { orientation = -normal->x; a = 2; b = 1; }
    else { orientation = normal->z; a = 0; b = 1; }
    if (orientation < 0.0f) {
        projected[0].x = ((f32 *)&triangle[0])[a]; projected[0].y = ((f32 *)&triangle[0])[b];
        projected[1].x = ((f32 *)&triangle[1])[a]; projected[1].y = ((f32 *)&triangle[1])[b];
        projected[2].x = ((f32 *)&triangle[2])[a]; projected[2].y = ((f32 *)&triangle[2])[b];
    } else {
        projected[0].x = ((f32 *)&triangle[2])[a]; projected[0].y = ((f32 *)&triangle[2])[b];
        projected[1].x = ((f32 *)&triangle[1])[a]; projected[1].y = ((f32 *)&triangle[1])[b];
        projected[2].x = ((f32 *)&triangle[0])[a]; projected[2].y = ((f32 *)&triangle[0])[b];
    }
    Vec minimum, maximum;
    minimum.x = minimum.y = 1000000.0f;
    maximum.x = maximum.y = -1000000.0f;
    Vec query;
    query.x = ((f32 *)point)[a];
    query.y = ((f32 *)point)[b];
    for (s32 i=0; i<3; i++) {
        if (minimum.x > projected[i].x) minimum.x = projected[i].x;
        if (minimum.y > projected[i].y) minimum.y = projected[i].y;
        if (maximum.x < projected[i].x) maximum.x = projected[i].x;
        if (maximum.y < projected[i].y) maximum.y = projected[i].y;
    }
    if (minimum.x > query.x || minimum.y > query.y || maximum.x < query.x || maximum.y < query.y) return 0;
    for (s32 i=0; i<3; i++) {
        s32 next = i+1;
        if (next >= 3) next = 0;
        Vec displacement, edge;
        displacement.x = query.x - projected[i].x;
        displacement.y = query.y - projected[i].y;
        edge.y = projected[next].y - projected[i].y;
        edge.x = projected[next].x - projected[i].x;
        f32 cross = edge.y * displacement.x;
        if (edge.x * displacement.y - cross > 0.0f) return 0;
    }
    return 1;
}
void GScolsy2UtilGetCpPlanePoint(Vec *out, Vec *normal, Vec *plane, Vec *point) {
    f32 t = (normal->z*(plane->z-point->z) + (normal->x*(plane->x-point->x)+normal->y*(plane->y-point->y))) / (normal->z*normal->z+(normal->x*normal->x+normal->y*normal->y));
    PSVECScale(normal, out, t);
    PSVECAdd(out, point, out);
}
}
