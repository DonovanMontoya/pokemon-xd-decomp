#include <game/maximum/GSAPI/baselib/id.h>

extern void* memset(void*, int, unsigned int);

static HSD_ObjAllocData alloc_data;
static HSD_IDTable default_table;

static unsigned int id_hash(HSD_IDKey id)
{
    return id % 0x65;
}

static IDEntry* IDEntryAlloc(void)
{
    IDEntry* entry = (IDEntry*) HSD_ObjAlloc(HSD_IDGetAllocData());
    if (entry == 0) {
        extern void __assert(const char*, int, const char*);
        __assert("id.c", 0x43, "entry");
    }
    memset(entry, 0, sizeof(IDEntry));
    return entry;
}

static void IDEntryFree(IDEntry* entry)
{
    HSD_ObjFree(HSD_IDGetAllocData(), entry);
}

HSD_ObjAllocData* HSD_IDGetAllocData(void)
{
    return &alloc_data;
}

void HSD_IDInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_IDGetAllocData(), sizeof(IDEntry), 4);
}

void HSD_IDSetup(void)
{
    memset(&default_table, 0, sizeof(default_table));
}

void HSD_IDInsertToTable(HSD_IDTable* table, HSD_IDKey id, void* data)
{
    IDEntry* entry;
    if (table == 0) {
        table = &default_table;
    }
    entry = table->table[id_hash(id)];
    while (entry != 0 && entry->id != id) {
        entry = entry->next;
    }
    if (entry != 0) {
        entry->id = id;
        entry->data = data;
    } else {
        entry = IDEntryAlloc();
        entry->id = id;
        entry->data = data;
        entry->next = table->table[id_hash(id)];
        table->table[id_hash(id)] = entry;
    }
}

void HSD_IDRemoveByIDFromTable(HSD_IDTable* table, HSD_IDKey id)
{
    IDEntry* entry;
    IDEntry* previous = 0;
    if (table == 0) {
        table = &default_table;
    }
    for (entry = table->table[id_hash(id)]; entry != 0; entry = entry->next) {
        if (entry->id == id) {
            if (previous != 0) {
                previous->next = entry->next;
            } else {
                table->table[id_hash(id)] = entry->next;
            }
            IDEntryFree(entry);
            return;
        }
        previous = entry;
    }
}

void* HSD_IDGetDataFromTable(HSD_IDTable* table, HSD_IDKey id, int* success)
{
    IDEntry* entry;
    if (table == 0) {
        table = &default_table;
    }
    entry = table->table[id_hash(id)];
    while (entry != 0) {
        if (entry->id == id) {
            if (success != 0) {
                *success = 1;
            }
            return entry->data;
        }
        entry = entry->next;
    }
    if (success != 0) {
        *success = 0;
    }
    return 0;
}

void _HSD_IDForgetMemory(void*, void*)
{
    memset(&default_table, 0, 0x194);
}
