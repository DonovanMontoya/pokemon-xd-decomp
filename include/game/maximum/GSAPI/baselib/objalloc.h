#ifndef HSD_OBJALLOC_H
#define HSD_OBJALLOC_H
typedef struct HSD_ObjAllocData {
    unsigned int num_limit_flag : 1;
    unsigned int heap_limit_flag : 1;
    void* freehead;
    unsigned int used, free, peak, num_limit;
    unsigned int heap_limit_size, heap_limit_num, size, align;
    struct HSD_ObjAllocData* next;
} HSD_ObjAllocData;
#ifdef __cplusplus
extern "C" {
#endif
void* HSD_ObjAlloc(HSD_ObjAllocData*);
void HSD_ObjFree(HSD_ObjAllocData*, void*);
void HSD_ObjAllocInit(HSD_ObjAllocData*, unsigned int, unsigned int);
#ifdef __cplusplus
}
#endif
#endif
