#include <game/maximum/GSAPI/baselib/hash.h>

extern void __assert(const char*, int, const char*);

void* HSD_HashSearch(HSD_Hash* hash, void* key, int* success)
{
    unsigned int index = hash->class_info->getidx(hash, key);
    HSD_HashEntry* entry;

    if (index >= hash->table_size) {
        __assert("hash.c", 0x71, "idx < hash->table_size");
    }
    entry = hash->table[index];
    if (entry == 0) {
        entry = 0;
    } else {
        while (hash->class_info->keycheck(hash, entry->key, key) != 0) {
            entry = entry->next;
            if (entry == 0) {
                break;
            }
        }
    }
    if (success != 0) {
        *success = entry != 0;
    }
    return entry != 0 ? entry->value : 0;
}
