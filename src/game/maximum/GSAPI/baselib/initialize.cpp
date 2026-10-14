#include "game/maximum/GSAPI/baselib/initialize.h"
#include "game/maximum/GSAPI/baselib/debug.h"
#include <libc/stdarg.h>
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern unsigned int OSGetPhysicalMemSize(void);
extern int OSCreateHeap(void*, void*);
extern void OSDestroyHeap(int);
extern int OSSetCurrentHeap(int);
extern void OSSetArenaLo(void*);
extern void* OSAllocFromHeap(int, unsigned int);
extern void OSFreeToHeap(int, void*);
extern int OSCheckHeap(int);
extern void OSReport(const char*, ...);
extern void _HSD_MemSetCallbacks(HSD_MemoryCallbacks*, unsigned int);
extern void HSD_ObjSetHeap(unsigned int, void*);
extern void HSD_StateInvalidate(unsigned int);
extern void HSD_IDSetup(void);
extern void HSD_ListInitAllocData(void);
extern void HSD_AObjInitAllocData(void);
extern void HSD_FObjInitAllocData(void);
extern void HSD_IDInitAllocData(void);
extern void HSD_VecInitAllocData(void);
extern void HSD_MtxInitAllocData(void);
extern void HSD_RObjInitAllocData(void);
extern void HSD_RenderInitAllocData(void);
extern void HSD_ShadowInitAllocData(void);

/* Original constant tables remain present even when their users were stripped. */
extern void _HSD_AObjForgetMemory(void*, void*);
extern void _HSD_DispForgetMemory(void*, void*);
extern void _HSD_IDForgetMemory(void*, void*);
extern void _HSD_ObjAllocForgetMemory(void*, void*);
extern void _HSD_RandForgetMemory(void*, void*);
extern void _HSD_RObjForgetMemory(void*, void*);
extern void* HSD_AObjGetAllocData(void);
extern void* HSD_FObjGetAllocData(void);
extern void* HSD_IDGetAllocData(void);
extern void* HSD_SListGetAllocData(void);
extern void* HSD_DListGetAllocData(void);
extern void* HSD_VecGetAllocData(void);
extern void* HSD_MtxGetAllocData(void);
extern void* HSD_RObjGetAllocData(void);
extern void* HSD_RvalueObjGetAllocData(void);
extern void* HSD_ShadowGetAllocData(void);
extern void* HSD_RenderGetAllocData(void);
extern void* HSD_ChanGetAllocData(void);
extern void* HSD_TevRegGetAllocData(void);
static const struct {
    void (*forget[7])(void*, void*);
    struct { void* (*get)(void); const char* label; } stats[14];
    char before_init[0x3C];
    char parameter_error[0x24];
    char invalid_callbacks[0x3C];
    char objalloc_file[0xC];
    char objalloc_format[0x28];
    char library[0x18];
} init_data = {
    { _HSD_AObjForgetMemory, _HSD_DispForgetMemory, _HSD_IDForgetMemory, _HSD_ObjAllocForgetMemory, _HSD_RandForgetMemory, _HSD_RObjForgetMemory, 0 },
    {
        { HSD_AObjGetAllocData, "aobj" },
        { HSD_FObjGetAllocData, "fobj" },
        { HSD_IDGetAllocData, "id" },
        { HSD_SListGetAllocData, "slist" },
        { HSD_DListGetAllocData, "dlist" },
        { HSD_VecGetAllocData, "vec" },
        { HSD_MtxGetAllocData, "mtx" },
        { HSD_RObjGetAllocData, "robj" },
        { HSD_RvalueObjGetAllocData, "rval" },
        { HSD_ShadowGetAllocData, "shadow" },
        { HSD_RenderGetAllocData, "render" },
        { HSD_ChanGetAllocData, "chan" },
        { HSD_TevRegGetAllocData, "tevreg" },
        { 0, 0 }
    },
    "init parameter should be set before invoking HSD_Init().\n",
    "ERROR in HSD_SetInitParameter():\n",
    "  HSD_INIT_MEMORY_CALLBACKS was given invalid arguments.\n",
    "objalloc.h",
    "objalloc: %s\tusing %d\tfreed %d\tpeak %d\n",
    "sysdolphin_base_library"
};

#pragma force_active on
static const char initialization_file[0x10] = "initialize.c";
static const char callback_assertion[0x1c] = "!iparam_memory_callbacks";
static const char missing_argument[0x18] = "missing argument.\n";
#pragma force_active reset

static int shown;
static int iparam_memory_callbacks;
static int iparam_heap_size;
static int init_done;
static void* hsd_heap_next_arena_hi;
static void* hsd_heap_next_arena_lo;
static void* hsd_heap_arena_hi;
static void* hsd_heap_arena_lo;
static int hsd_heap = -1;
static struct {
    unsigned int total, system, xfb, gxfifo, heap;
} memReport;
static void* _HSD_MemAllocDefaultCB(unsigned int);
static void _HSD_MemFreeDefaultCB(void*);
static int _HSD_MemGetRemainDefaultCB(void);
static void _HSD_MemClearDefaultCB(void);
static int _HSD_MemCheckOwnDefaultCB(void*);
void HSD_Init(void)
{
    HSD_OSInit();
    HSD_StateInvalidate(-1);
    HSD_IDSetup();
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    init_done = 1;
}
void HSD_OSInit(void)
{
    unsigned int lo, hi;
    OSGetArenaLo();
    OSGetArenaHi();
    memReport.total = OSGetPhysicalMemSize();
    memReport.system = memReport.total - (unsigned int)OSGetArenaHi() +
        (unsigned int)OSGetArenaLo() - memReport.xfb - memReport.gxfifo;
    if (!iparam_memory_callbacks) {
        HSD_MemoryCallbacks callbacks;
        callbacks.alloc = _HSD_MemAllocDefaultCB;
        callbacks.free = _HSD_MemFreeDefaultCB;
        callbacks.get_remain = _HSD_MemGetRemainDefaultCB;
        callbacks.clear = _HSD_MemClearDefaultCB;
        callbacks.check_own = _HSD_MemCheckOwnDefaultCB;
        _HSD_MemSetCallbacks(&callbacks, sizeof(callbacks));
        if (hsd_heap_next_arena_lo && hsd_heap_next_arena_hi) {
            hsd_heap_arena_lo = hsd_heap_next_arena_lo;
            hsd_heap_arena_hi = hsd_heap_next_arena_hi;
            hsd_heap_next_arena_lo = 0;
            hsd_heap_next_arena_hi = 0;
            hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
            OSSetCurrentHeap(hsd_heap);
            memReport.heap = (unsigned int)hsd_heap_arena_hi - (unsigned int)hsd_heap_arena_lo;
            HSD_ObjSetHeap(memReport.heap, 0);
        } else {
            lo = ((unsigned int)OSGetArenaLo() + 31) & ~31;
            hi = (unsigned int)OSGetArenaHi();
            hsd_heap_arena_lo = (void*)lo;
            if (iparam_heap_size > 0) {
                hsd_heap_arena_hi = (void*)(lo + iparam_heap_size);
                if ((unsigned int)hsd_heap_arena_hi > hi) hsd_heap_arena_hi = (void*)hi;
                hsd_heap_arena_hi = (void*)((unsigned int)hsd_heap_arena_hi & ~31);
            } else hsd_heap_arena_hi = (void*)(hi & ~31);
            hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
            OSSetCurrentHeap(hsd_heap);
            memReport.heap = (unsigned int)hsd_heap_arena_hi - (unsigned int)hsd_heap_arena_lo;
            HSD_ObjSetHeap(memReport.heap, 0);
            OSSetArenaLo(hsd_heap_arena_hi);
        }
    }
}
static void* _HSD_MemAllocDefaultCB(unsigned int size)
{
    void* addr;
    if (size == 0) return 0;
    if (iparam_memory_callbacks) __assert(initialization_file, 0xFF, callback_assertion);
    addr = OSAllocFromHeap(hsd_heap, size);
    if (addr == 0) __assert(initialization_file, 0xCE, "addr");
    return addr;
}
static void _HSD_MemFreeDefaultCB(void* addr)
{
    if (iparam_memory_callbacks) __assert(initialization_file, 0xFF, callback_assertion);
    OSFreeToHeap(hsd_heap, addr);
}
static int _HSD_MemGetRemainDefaultCB(void)
{
    if (iparam_memory_callbacks) __assert(initialization_file, 0xFF, callback_assertion);
    return OSCheckHeap(hsd_heap);
}
static void _HSD_MemClearDefaultCB(void)
{
    OSDestroyHeap(hsd_heap);
    if (hsd_heap_next_arena_lo && hsd_heap_next_arena_hi) {
        hsd_heap_arena_lo = hsd_heap_next_arena_lo;
        hsd_heap_arena_hi = hsd_heap_next_arena_hi;
        hsd_heap_next_arena_lo = 0;
        hsd_heap_next_arena_hi = 0;
    }
    hsd_heap = OSCreateHeap(hsd_heap_arena_lo, hsd_heap_arena_hi);
    OSSetCurrentHeap(hsd_heap);
}
static int _HSD_MemCheckOwnDefaultCB(void* addr)
{
    int own = 0;
    if (hsd_heap_arena_lo <= addr && addr < hsd_heap_arena_hi) own = 1;
    return own;
}
int HSD_SetInitParameter(HSD_InitParam param, ...)
{
    va_list ap;
    int ok = 0;
    const char* messages = (const char*)&init_data;
    if (init_done) {
        if (!shown) {
            OSReport(messages + 0x8C);
            shown = 1;
        }
        return 0;
    }
    va_start(ap, param);
    switch (param) {
    case HSD_INIT_HEAP_SIZE: {
        unsigned int size = va_arg(ap, unsigned int);
        if (size < OSGetPhysicalMemSize()) {
            iparam_heap_size = size;
            ok = 1;
        }
        break;
    }
    case HSD_INIT_HEAP_ARENA: {
        void* lo = va_arg(ap, void*);
        void* hi = va_arg(ap, void*);
        hsd_heap_next_arena_lo = lo;
        hsd_heap_next_arena_hi = hi;
        ok = 1;
        break;
    }
    case HSD_INIT_MEMORY_CALLBACKS: {
        HSD_MemoryCallbacks callbacks;
        callbacks.alloc = va_arg(ap, HSD_AllocCallback);
        callbacks.free = va_arg(ap, HSD_FreeCallback);
        callbacks.clear = va_arg(ap, HSD_ClearCallback);
        callbacks.get_remain = va_arg(ap, HSD_RemainCallback);
        callbacks.check_own = va_arg(ap, HSD_OwnCallback);
        if (va_arg(ap, void*) != 0) {
            OSReport(messages + 0xC8);
            OSReport(messages + 0xEC);
        } else {
            _HSD_MemSetCallbacks(&callbacks, sizeof(callbacks));
            iparam_memory_callbacks = 1;
            ok = 1;
        }
        break;
    }
    }
    va_end(ap);
    return ok;
}
