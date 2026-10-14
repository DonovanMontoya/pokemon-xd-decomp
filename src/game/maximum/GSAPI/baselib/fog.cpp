#include "game/maximum/GSAPI/baselib/fog.h"

#include <libc/string.h>
#include "game/maximum/GSAPI/baselib/debug.h"
typedef struct { unsigned char r, g, b, a; } FogColor;
extern void GXSetFog(int, float, float, float, float, FogColor);
extern void* HSD_CObjGetCurrent(void);
extern float HSD_CObjGetFar(void*);
extern float HSD_CObjGetNear(void*);
extern void GXGetViewportv(float*);
extern void GXGetProjectionv(float*);
extern void GXInitFogAdjTable(void*, unsigned short, float (*)[4]);
extern void GXSetFogRangeAdj(unsigned char, unsigned short, void*);
static inline HSD_FogAdj* FogGetAdj(HSD_Fog* fog) { return fog ? fog->fog_adj : 0; }
static inline unsigned int AdjGetFlags(HSD_FogAdj* adj) { return adj ? adj->flags : 0; }
static inline int AdjGetCenter(HSD_FogAdj* adj) { return adj ? adj->center : -1; }
static inline int AdjGetWidth(HSD_FogAdj* adj) { return adj ? adj->width : -1; }
void HSD_FogSet(HSD_Fog* fog)
{
    float mtx[4][4];
    unsigned short tbl[10];
    float viewport[6];
    float proj[7];
    HSD_FogAdj* adj;
    unsigned int flags;
    float (*matrix)[4];
    void* cobj;
    int center;
    int width;
    if (fog == 0) {
        FogColor black = {0};
        GXSetFog(0, 0.0F, 0.0F, 0.0F, 0.0F, black);
        return;
    }
    cobj = HSD_CObjGetCurrent();
    if (cobj == 0) HSD_Panic("fog.c", 0x57, "You must specify CObj first.\n");
    GXSetFog(fog->type, fog->start, fog->end, HSD_CObjGetNear(cobj), HSD_CObjGetFar(cobj), *(FogColor*)fog->color);
    adj = FogGetAdj(fog);
    flags = AdjGetFlags(adj);
    if (adj && (flags & 7)) {
        GXGetViewportv(viewport);
        if (flags & 1) center = viewport[0] + viewport[2] * (AdjGetCenter(adj) + 320) / 640.0F;
        else center = (viewport[2] / 2.0F) + viewport[0];
        if (flags & 2) width = AdjGetWidth(adj);
        else width = viewport[2];
        if (flags & 4) {
            if (adj) matrix = adj->mtx;
            else matrix = 0;
        }
        else {
            matrix = mtx;
            memset(matrix, 0, sizeof(mtx));
            GXGetProjectionv(proj);
            switch ((int)proj[0]) {
            case 0:
                mtx[0][0] = proj[1]; mtx[0][2] = proj[2];
                mtx[1][1] = proj[3]; mtx[1][2] = proj[4];
                mtx[2][2] = proj[5]; mtx[2][3] = proj[6];
                mtx[3][2] = -1.0F;
                break;
            default:
                mtx[0][0] = proj[1]; mtx[0][3] = proj[2];
                mtx[1][1] = proj[3]; mtx[1][3] = proj[4];
                mtx[2][2] = proj[5]; mtx[2][3] = proj[6];
                mtx[3][3] = 1.0F;
                break;
            }
        }
        GXInitFogAdjTable(tbl, width, matrix);
        GXSetFogRangeAdj(1, center, tbl);
    } else GXSetFogRangeAdj(0, 0, 0);
}
