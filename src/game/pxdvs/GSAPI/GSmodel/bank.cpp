#include <game/pxdvs/GSAPI/GSmodel/runtime.hpp>
extern "C" void* memset(void*, int, unsigned long);
typedef GSmodelRuntime GSmodelBankSlot;
struct GSmodelBank { u32 flags; GSmodelBank* next; GSmodelBankSlot slots[8]; };
typedef char GSmodelBankSizeCheck[sizeof(GSmodelBank) == 0x3148 ? 1 : -1];
extern "C" {
static GSmodelBank* _modelBankList;
GSmodel* _modelTopPtr;
void* GSmemAllocClr(u32);
void GSmemFree(void*);
}
static inline GSmodelBank* createBank() {
    GSmodelBank* bank = (GSmodelBank*)GSmemAllocClr(sizeof(GSmodelBank));
    if (!bank) return 0;
    bank->flags = 2; bank->next = 0;
    for (u32 i = 0; i < 8; ++i) {
        bank->slots[i].model.flags = 0;
        bank->slots[i].model.renderToken = 0;
        bank->slots[i].model.next = 0;
    }
    return bank;
}
static inline u8 containsBank(GSmodelBank* bank) {
    for (GSmodelBank* item = _modelBankList; item; item = item->next) if (item == bank) return 1;
    return 0;
}
static inline void addBank(GSmodelBank* bank) {
    if (containsBank(bank) != 1) {
        bank->next = _modelBankList; _modelBankList = bank; bank->flags |= 1;
    }
}
static inline void updateBank(GSmodelBank* bank) {
    s32 used = 0, free = 0;
    bank->flags &= ~6;
    for (s32 i = 0; i < 8; ++i) {
        u32 inUse = bank->slots[i].model.flags & 1;
        if (inUse) ++used;
        if (!inUse) ++free;
    }
    if (used == 8) bank->flags |= 4;
    else if (free == 8) bank->flags |= 2;
}
static inline GSmodelBank* findBank(GSmodel* model) {
    for (GSmodelBank* bank = _modelBankList; bank; bank = bank->next) {
        if (!(bank->flags & 2)) {
            for (s32 i = 0; i < 8; ++i) if (&bank->slots[i].model == model) return bank;
        }
    }
    return 0;
}
static inline GSmodel* findFreeModel(GSmodelBank* bank) {
    for (s32 i = 0; i < 8; ++i) {
        GSmodel* model = &bank->slots[i].model;
        if (!(model->flags & 1)) return model;
    }
    return 0;
}
extern "C" void modelBankInit__Fv() { addBank(createBank()); }
extern "C" GSmodel* modelBankGetFreeModel__Fv() {
    GSmodelBank* bank = _modelBankList;
    while (bank && (bank->flags & 4)) bank = bank->next;
    if (!bank) { bank = createBank(); if (!bank) return 0; addBank(bank); }
    GSmodel* model = findFreeModel(bank);
    memset(model, 0, sizeof(GSmodelBankSlot));
    model->flags = 1;
    updateBank(bank);
    model->next = 0;
    if (!_modelTopPtr) _modelTopPtr = model;
    else {
        GSmodel* tail = _modelTopPtr;
        while (tail->next) tail = tail->next;
        tail->next = model;
    }
    return model;
}
extern "C" void modelBankReleaseModel__FP8_GSmodel(GSmodel* model) {
    GSmodelBank* bank = findBank(model);
    if (_modelTopPtr == model) _modelTopPtr = model->next;
    else {
        GSmodel* previous = _modelTopPtr;
        while (previous && previous->next != model) previous = previous->next;
        previous->next = model->next;
    }
    model->flags = 0; model->next = 0;
    updateBank(bank);
    GSmodelBank* item = _modelBankList;
    GSmodelBank* previous = item;
    for (; item; item = item->next) {
        if ((item->flags & 2) && item->next) {
            GSmodelBank* next = item->next;
            if (containsBank(item)) {
                if (previous == item) {
                    item->flags &= ~1; _modelBankList = item->next;
                } else {
                    while (previous) {
                        if (previous->next == item) {
                            previous->next = next; item->flags &= ~1; break;
                        }
                        previous = previous->next;
                    }
                }
            }
            GSmemFree(item); break;
        }
    }
}
