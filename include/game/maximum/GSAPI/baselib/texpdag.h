#ifndef HSD_TEXPDAG_H
#define HSD_TEXPDAG_H
#include "game/maximum/GSAPI/baselib/texp.h"
typedef struct HSD_TExpDag {
    HSD_TETev* tev;
    u8 idx, nb_dep, nb_ref, dist;
    struct HSD_TExpDag* depend[8];
} HSD_TExpDag;
typedef char HSD_TExpDagSizeCheck[sizeof(HSD_TExpDag) == 0x28 ? 1 : -1];
int HSD_TExpMakeDag(HSD_TExp*, HSD_TExpDag*);
void HSD_TExpSchedule(int, HSD_TExpDag*, HSD_TExp**, HSD_TExpRes*);
#endif
