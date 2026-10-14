#ifndef XD_HSD_LIST_H
#define XD_HSD_LIST_H

#include <game/maximum/GSAPI/baselib/objalloc.h>

typedef struct HSD_SList {
    struct HSD_SList* next;
    void* data;
} HSD_SList;

typedef struct HSD_DList {
    struct HSD_DList* next;
    struct HSD_DList* prev;
    void* data;
} HSD_DList;

#ifdef __cplusplus
extern "C" {
#endif
void HSD_ListInitAllocData(void);
HSD_ObjAllocData* HSD_SListGetAllocData(void);
HSD_ObjAllocData* HSD_DListGetAllocData(void);
HSD_SList* HSD_SListAlloc(void);
HSD_SList* HSD_SListPrepend(HSD_SList*, void*);
HSD_SList* HSD_SListRemove(HSD_SList*);
#ifdef __cplusplus
}
#endif
#endif
