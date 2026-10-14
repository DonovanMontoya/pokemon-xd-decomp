#ifndef HSD_UTIL_H
#define HSD_UTIL_H
#include <dolphin/gx.h>
#ifdef __cplusplus
extern "C" {
#endif
void HSD_MulColor(GXColor*, GXColor*, GXColor*);
unsigned int HSD_GetNbBits(unsigned int);
int HSD_Index2PosNrmMtx(unsigned int);
#ifdef __cplusplus
}
#endif
#endif
