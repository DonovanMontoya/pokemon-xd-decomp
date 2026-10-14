#include <game/maximum/GSAPI/baselib/list.h>

extern void* GSmemGetSysdolAllocator(int);
extern void* GSmemGetFreePool(void);
extern void* GSmemAllocPool(void*);
extern int GSmemIsRegistrationPool(void*);
extern void GSmemFreePool(void*, void*);
extern void __assert(const char*, int, const char*);
extern void* memset(void*, int, unsigned int);

static HSD_ObjAllocData d_alloc_data;
static HSD_ObjAllocData s_alloc_data;

void HSD_ListInitAllocData(void)
{
    HSD_ObjAllocInit(&s_alloc_data, sizeof(HSD_SList), 4);
    HSD_ObjAllocInit(&d_alloc_data, sizeof(HSD_DList), 4);
}

HSD_ObjAllocData* HSD_SListGetAllocData(void)
{
    return &s_alloc_data;
}

HSD_ObjAllocData* HSD_DListGetAllocData(void)
{
    return &d_alloc_data;
}

HSD_SList* HSD_SListAlloc(void)
{
    void* allocator = GSmemGetSysdolAllocator(8);
    HSD_SList* list;
    if (allocator != 0 && GSmemGetFreePool() != 0) {
        list = (HSD_SList*) GSmemAllocPool(allocator);
        if (list == 0) {
            __assert("list.c", 0x58, "list");
        }
        return list;
    }
    list = (HSD_SList*) HSD_ObjAlloc(&s_alloc_data);
    if (list == 0) {
        __assert("list.c", 0x60, "list");
    }
    memset(list, 0, sizeof(HSD_SList));
    return list;
}

HSD_SList* HSD_SListPrepend(HSD_SList* list, void* data)
{
    void* allocator = GSmemGetSysdolAllocator(8);
    HSD_SList* node;
    if (allocator != 0 && GSmemGetFreePool() != 0) {
        node = (HSD_SList*) GSmemAllocPool(allocator);
        if (node == 0) {
            __assert("list.c", 0x58, "list");
        }
    } else {
        node = (HSD_SList*) HSD_ObjAlloc(&s_alloc_data);
        if (node == 0) {
            __assert("list.c", 0x60, "list");
        }
        memset(node, 0, sizeof(HSD_SList));
    }
    node->data = data;
    if (node == 0) {
        __assert("list.c", 0xE7, "prev");
    }
    node->next = list;
    return node;
}

HSD_SList* HSD_SListRemove(HSD_SList* list)
{
    HSD_SList* next;
    if (list != 0) {
        next = list->next;
        {
            void* allocator = GSmemGetSysdolAllocator(8);
            if (allocator != 0 && GSmemIsRegistrationPool(list) != 0) {
                GSmemFreePool(allocator, list);
            } else {
                HSD_ObjFree(&s_alloc_data, list);
            }
        }
        return next;
    }
    return 0;
}
