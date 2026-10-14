#ifndef XD_HSD_ID_H
#define XD_HSD_ID_H

#include <game/maximum/GSAPI/baselib/objalloc.h>

typedef unsigned int HSD_IDKey;
typedef struct IDEntry {
    struct IDEntry* next;
    HSD_IDKey id;
    void* data;
} IDEntry;
typedef struct HSD_IDTable {
    IDEntry* table[101];
} HSD_IDTable;

#ifdef __cplusplus
extern "C" {
#endif
HSD_ObjAllocData* HSD_IDGetAllocData(void);
void HSD_IDInitAllocData(void);
void HSD_IDSetup(void);
void HSD_IDInsertToTable(HSD_IDTable*, HSD_IDKey, void*);
void HSD_IDRemoveByIDFromTable(HSD_IDTable*, HSD_IDKey);
void* HSD_IDGetDataFromTable(HSD_IDTable*, HSD_IDKey, int*);
void _HSD_IDForgetMemory(void*, void*);
#ifdef __cplusplus
}
#endif
#endif
