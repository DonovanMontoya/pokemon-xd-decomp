#ifndef HSD_CLASS_H
#define HSD_CLASS_H
typedef struct HSD_ClassInfo HSD_ClassInfo;
typedef struct HSD_Class { HSD_ClassInfo* class_info; } HSD_Class;
typedef struct HSD_ClassInfoHead {
    void (*info_init)(void);
    unsigned int flags;
    char *library_name, *class_name;
    short obj_size, info_size;
    HSD_ClassInfo *parent, *next, *child;
    unsigned int nb_exist, nb_peak;
} HSD_ClassInfoHead;
struct HSD_ClassInfo {
    HSD_ClassInfoHead head;
    HSD_Class* (*alloc)(HSD_ClassInfo*);
    int (*init)(HSD_Class*);
    void (*release)(HSD_Class*);
    void (*destroy)(HSD_Class*);
    void (*amnesia)(HSD_ClassInfo*);
};
#ifdef __cplusplus
extern "C" {
#endif
extern HSD_ClassInfo hsdClass;
void hsdInitClassInfo(HSD_ClassInfo*, HSD_ClassInfo*, char*, char*, int, int);
void* hsdNew(HSD_ClassInfo*);
HSD_ClassInfo* hsdSearchClassInfo(const char*);
int hsdIsDescendantOf(void*, void*);
#ifdef __cplusplus
}
#endif
#define HSD_CLASS_INFO(o) ((HSD_ClassInfo*)(o))
#define HSD_CLASS_METHOD(o) (((HSD_Class*)(o))->class_info)
#define HSD_PARENT_INFO(o) ((o)->parent.head.parent)
#define next_p(p) ((p) != 0 ? (p)->next : 0)
static inline void hsdDelete(void* object) {
    if (object != 0) {
        HSD_CLASS_METHOD(object)->release((HSD_Class*)object);
        HSD_CLASS_METHOD(object)->destroy((HSD_Class*)object);
    }
}
#endif
