#ifndef HSD_TEV_H
#define HSD_TEV_H
#include "game/maximum/GSAPI/baselib/objalloc.h"
#include "game/maximum/GSAPI/baselib/state.h"
#include "game/maximum/GSAPI/baselib/texp.h"
void HSD_RenderInitAllocData(void);
HSD_ObjAllocData* HSD_RenderGetAllocData(void);
HSD_ObjAllocData* HSD_TevRegGetAllocData(void);
HSD_ObjAllocData* HSD_ChanGetAllocData(void);
void HSD_SetupChannel(HSD_Chan*);
void HSD_StateSetNumChans(int num);
void HSD_SetupChannelAll(HSD_Chan*);
void HSD_StateRegisterTexGen(int);
void HSD_StateSetNumTexGens(void);
void HSD_StateInitTev(void);
int HSD_StateGetNumTevStages(void);
int HSD_StateAssignTev(void);
void HSD_StateSetNumTevStages(void);
void HSD_SetupTevStage(HSD_TevDesc*);
void HSD_SetupTevStageAll(HSD_TevDesc*);

int HSD_Index2TevStage(int idx);


void HSD_SetTevRegAll(void);
void ChanUpdateFunc(HSD_Chan*, int, const f32*);
void _HSD_StateInvalidateColorChannel(void);
void _HSD_StateInvalidateTevStage(void);
void _HSD_StateInvalidateTevRegister(void);
void _HSD_StateInvalidateTexCoordGen(void);


void HSD_DisableChannelLighting(GXChannelID);
void HSD_InitColorSwapTable(u8, u8, u8, u8, u8);
void HSD_ResetColorSwapTables(void);
#endif
