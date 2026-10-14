#include <game/maximum/GSAPI/baselib/class.h>
#include <libc/string.h>
void* HSD_Alloc(int);
void HSD_Free(void*);
void* HSD_HashSearch(void*, const char*, void**);
void __assert(const char*, int, const char*);
static void _hsdClassInfoInit(void);
static HSD_Class* _hsdClassAlloc(HSD_ClassInfo*);
static int _hsdClassInit(HSD_Class*);
static void _hsdClassRelease(HSD_Class*);
static void _hsdClassDestroy(HSD_Class*);
static void _hsdClassAmnesia(HSD_ClassInfo*);
HSD_ClassInfo hsdClass = { _hsdClassInfoInit };
static void* info_hash;
static int nb_memory_list;
static void** memory_list;
void hsdInitClassInfo(HSD_ClassInfo* info, HSD_ClassInfo* parent, char* library,
                      char* name, int infoSize, int objectSize) {
    info->head.flags = 1; info->head.library_name = library; info->head.class_name = name;
    info->head.obj_size = objectSize; info->head.info_size = infoSize; info->head.parent = parent;
    info->head.child = 0; info->head.next = 0; info->head.nb_exist = 0; info->head.nb_peak = 0;
    if (parent) {
        if (!(parent->head.flags & 1)) parent->head.info_init();
        if (info->head.obj_size < parent->head.obj_size) __assert("class.c", 102, "class_info->head.obj_size >= parent_info->head.obj_size");
        if (info->head.info_size < parent->head.info_size) __assert("class.c", 103, "class_info->head.info_size >= parent_info->head.info_size");
        memcpy(&info->alloc, &parent->alloc, parent->head.info_size - sizeof(HSD_ClassInfoHead));
        info->head.next = parent->head.child; parent->head.child = info;
    }
}
void* hsdAllocMemPiece(int size) { return HSD_Alloc(size); }
void hsdFreeMemPiece(void* pointer, int size) { HSD_Free(pointer); }
static HSD_Class* _hsdClassAlloc(HSD_ClassInfo* info) {
    HSD_Class* object = HSD_Alloc(info->head.obj_size);
    if (object) {
        ++info->head.nb_exist;
        if (info->head.nb_exist > info->head.nb_peak) info->head.nb_peak = info->head.nb_exist;
    }
    return object;
}
static int _hsdClassInit(HSD_Class* object) { return 0; }
static void _hsdClassRelease(HSD_Class* object) {}
static void _hsdClassDestroy(HSD_Class* object) { --object->class_info->head.nb_exist; HSD_Free(object); }
static void _hsdClassAmnesia(HSD_ClassInfo* info) {
    info->head.nb_exist = 0; info->head.nb_peak = 0;
    if (info == &hsdClass) { nb_memory_list = 0; memory_list = 0; info_hash = 0; }
}
static void _hsdClassInfoInit(void) {
    hsdClass.head.flags = 1;
    hsdClass.head.library_name = "sysdolphin_base_library";
    hsdClass.head.class_name = "hsd_class";
    hsdClass.head.obj_size = sizeof(HSD_Class);
    hsdClass.head.info_size = sizeof(HSD_ClassInfo);
    hsdClass.head.parent = 0; hsdClass.head.child = 0; hsdClass.head.next = 0;
    hsdClass.head.nb_exist = 0; hsdClass.head.nb_peak = 0;
    hsdClass.alloc = _hsdClassAlloc; hsdClass.init = _hsdClassInit;
    hsdClass.release = _hsdClassRelease; hsdClass.destroy = _hsdClassDestroy;
    hsdClass.amnesia = _hsdClassAmnesia;
}
void* hsdNew(HSD_ClassInfo* info) {
    HSD_Class* object;
    if (!(info->head.flags & 1)) info->head.info_init();
    object = info->alloc(info);
    if (!object) return 0;
    if (!(info->head.flags & 1)) info->head.info_init();
    memset(object, 0, info->head.obj_size);
    object->class_info = info;
    if (info->init(object) < 0) { info->destroy(object); return 0; }
    return object;
}
int hsdIsDescendantOf(void* objectInfo, void* parentInfo) {
    HSD_ClassInfo* info;
    HSD_ClassInfo* parent = parentInfo;
    if (!objectInfo || !parent) return 0;
    info = objectInfo;
    if (!(info->head.flags & 1)) info->head.info_init();
    if (!(parent->head.flags & 1)) parent->head.info_init();
    for (; info; info = info->head.parent) if (info == parent) return 1;
    return 0;
}
HSD_ClassInfo* hsdSearchClassInfo(const char* name) {
    if (info_hash) return HSD_HashSearch(info_hash, name, 0);
    return 0;
}
typedef char ClassInfoSizeCheck[sizeof(HSD_ClassInfo) == 0x3c ? 1 : -1];
