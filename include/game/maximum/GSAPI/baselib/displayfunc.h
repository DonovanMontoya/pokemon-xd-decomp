#ifndef HSD_DISPLAYFUNC_H
#define HSD_DISPLAYFUNC_H
#include "game/maximum/GSAPI/baselib/jobj.h"
void HSD_JObjMakePositionMtx(HSD_JObj*,HSD_Mtx,HSD_Mtx);
float (*_HSD_mkEnvelopeModelNodeMtx(HSD_JObj*,HSD_Mtx))[4];
void HSD_JObjDisp(HSD_JObj*,HSD_Mtx,unsigned int,unsigned int);
void HSD_JObjDispSub(HSD_JObj*,HSD_Mtx,HSD_Mtx,unsigned int,unsigned int);
void HSD_JObjSetSPtclCallback(void (*)(int,int,int,HSD_JObj*));
void _HSD_DispForgetMemory(void*,void*);
#endif
