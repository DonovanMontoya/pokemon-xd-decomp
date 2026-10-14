#ifndef XD_HSD_HASH_H
#define XD_HSD_HASH_H

#include <game/maximum/GSAPI/baselib/class.h>

typedef struct HSD_Hash HSD_Hash;
typedef struct HSD_HashEntry {
    struct HSD_HashEntry* next;
    void* key;
    void* value;
} HSD_HashEntry;
typedef struct HSD_HashClassInfo {
    HSD_ClassInfo parent;
    unsigned int (*getidx)(HSD_Hash*, void*);
    int (*keycheck)(HSD_Hash*, void*, void*);
} HSD_HashClassInfo;
struct HSD_Hash {
    HSD_HashClassInfo* class_info;
    HSD_HashEntry** table;
    unsigned int table_size;
};

#ifdef __cplusplus
extern "C" {
#endif
void* HSD_HashSearch(HSD_Hash*, void*, int*);
#ifdef __cplusplus
}
#endif
#endif
