/* Debug menu entries for saving/loading save data to/from the debug file system. */
#include <global.h>

extern u8 GSdvdOpenTest(const char*);
extern u32 GSdvdOpen(const char*);
extern u32 GSdvdCreate(const char*);
extern void GSdvdRead(u32, void*, s32, s32);
extern void GSdvdWrite(u32, void*, s32, s32);
extern void GSdvdClose(u32);
extern void* GSmemAllocAlign(s32, s32);
extern void GSmemFree(void*);
extern void __assert(const char*, int, const char*);
extern void gamedataSetStatus(void*, s32, s32);
extern void* memcardMemAllocForSavedata(void);
extern void* memcardMemFreeForSavedata(void*);
extern s32 memcardTaskCall(s32, s32, s32);
extern void memcard_debug_Load(void*);
extern void memcard_debug_Load2(void);
extern void memcard_debug_Save(void*);
extern void* memcpy(void*, const void*, u32);
extern s32 pokecoloGetCountryCode(void);
extern void* savedataGetStatus(s32, s32);
extern void winMsgClose(s32);
extern void winMsgOpen(s32, s32, s32, s32);

extern void* now_savedata_ptr;

static void* dbgMenuSaveData;
static void* bk_savedataPtr;

static const char* saveFileName[10] = {
    "HDSaveData1.DSV1",
    "HDSaveData2.DSV1",
    "HDSaveData3.DSV1",
    "HDSaveData4.DSV1",
    "HDSaveData5.DSV1",
    "HDSaveData_1.DSV2",
    "HDSaveData_2.DSV2",
    "HDSaveData_3.DSV2",
    "HDSaveData_4.DSV2",
    "HDSaveData_5.DSV2",
};

static u8 _memcard_debug_type_check(s32 index) {
    switch (index) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return 1;
    }
    return 0;
}

s32 dbgMenuMemcardDebugLoad(s32 unused, s32 index) {
    u32 file;
    void* status;

    if (GSdvdOpenTest(saveFileName[index])) {
        file = GSdvdOpen(saveFileName[index]);
        if (file == 0) {
            return 0;
        }
    } else {
        return 0;
    }
    if (_memcard_debug_type_check(index)) {
        dbgMenuSaveData = GSmemAllocAlign(0x28000, 0x20);
        GSdvdRead(file, dbgMenuSaveData, 0x28000, 0);
        GSdvdClose(file);
        memcard_debug_Load((u8*)dbgMenuSaveData + 8);
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = 0;
    } else {
        GSdvdRead(file, now_savedata_ptr, 0x27FC0, 0);
        GSdvdClose(file);
        memcard_debug_Load2();
    }
    status = savedataGetStatus(0, 1);
    switch (pokecoloGetCountryCode()) {
    case 0:
        gamedataSetStatus(status, 2, 0xB);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 1);
        gamedataSetStatus(status, 5, 1);
        break;
    case 1:
        gamedataSetStatus(status, 2, 0xB);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 2);
        gamedataSetStatus(status, 5, 2);
        break;
    case 2:
        gamedataSetStatus(status, 2, 0xB);
        gamedataSetStatus(status, 3, 3);
        gamedataSetStatus(status, 4, 3);
        gamedataSetStatus(status, 5, 8);
        break;
    }
    return 0;
}

s32 dbgMenuMemcardDebugSave(s32 unused, s32 index) {
    u32 file;

    if (_memcard_debug_type_check(index)) {
        dbgMenuSaveData = GSmemAllocAlign(0x28000, 0x20);
        memcard_debug_Save((u8*)dbgMenuSaveData + 8);
        if (GSdvdOpenTest(saveFileName[index])) {
            file = GSdvdOpen(saveFileName[index]);
        } else {
            file = GSdvdCreate(saveFileName[index]);
        }
        if (file != 0) {
            GSdvdWrite(file, dbgMenuSaveData, 0x28000, 0);
            GSdvdClose(file);
        }
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = 0;
    } else {
        bk_savedataPtr = memcardMemAllocForSavedata();
        if (bk_savedataPtr == 0) {
            __assert("dbgMenuMemcard.c", 501, "bk_savedataPtr &&\"\x83\x81\x83\x82\x83\x8A\x81\x5B\x95\x73\x91\xAB\"");
        }
        memcpy(bk_savedataPtr, savedataGetStatus(0, 0), 0x27FD0);
        if (memcardTaskCall(2, 2, 0) == 3) {
            if (GSdvdOpenTest(saveFileName[index])) {
                file = GSdvdOpen(saveFileName[index]);
            } else {
                file = GSdvdCreate(saveFileName[index]);
            }
            if (file != 0) {
                GSdvdWrite(file, now_savedata_ptr, 0x27FC0, 0);
                GSdvdClose(file);
            }
        }
        memcpy(savedataGetStatus(0, 0), bk_savedataPtr, 0x27FD0);
        bk_savedataPtr = memcardMemFreeForSavedata(bk_savedataPtr);
        if (bk_savedataPtr != 0) {
            __assert("dbgMenuMemcard.c", 534, "!bk_savedataPtr &&\"\x83\x81\x83\x82\x83\x8A\x81\x5B\x89\xF0\x95\xFA\x8E\xB8\x94\x73\"");
        }
    }
    return 0;
}

s32 dbgMenuMemcardDelete(void) {
    memcardTaskCall(0xC, 2, 0);
    return 0;
}

s32 dbgMenuMemcardLoad(void) {
    memcardTaskCall(2, 2, 0);
    winMsgOpen(2, 0xF2, 1, 1);
    winMsgClose(1);
    return 0;
}

s32 dbgMenuMemcardSave(void) {
    memcardTaskCall(0xB, 2, 0);
    return 0;
}
