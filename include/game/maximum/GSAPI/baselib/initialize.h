#ifndef HSD_INITIALIZE_H
#define HSD_INITIALIZE_H
typedef enum HSD_InitParam {
    HSD_INIT_HEAP_SIZE,
    HSD_INIT_HEAP_ARENA,
    HSD_INIT_MEMORY_CALLBACKS
} HSD_InitParam;
typedef void* (*HSD_AllocCallback)(unsigned int);
typedef void (*HSD_FreeCallback)(void*);
typedef void (*HSD_ClearCallback)(void);
typedef int (*HSD_RemainCallback)(void);
typedef int (*HSD_OwnCallback)(void*);
typedef struct HSD_MemoryCallbacks {
    void* (*alloc)(unsigned int);
    void (*free)(void*);
    void (*clear)(void);
    int (*get_remain)(void);
    int (*check_own)(void*);
} HSD_MemoryCallbacks;
int HSD_SetInitParameter(HSD_InitParam, ...);
void HSD_OSInit(void);
void HSD_Init(void);
#endif
