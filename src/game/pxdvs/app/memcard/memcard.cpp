#include <game/pxdvs/app/memcard/memcardPrivate.hpp>

static u8 _memcardInitializeFlag;
static MemcardStatus* _memcardStatusPtr;
static u8 _memcard_anySaveOFF_Flag;
static u8 _memcardStatusBuf[0x210];

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE msg);

// Not yet recovered (declared here so the callers can be built).
void _memcardJobMain(u32, u32);
u8 _memcard_Decryption(void*);
void _memcard_Encryption(void*);
void _memcardStoreSaveData_multi(void*);
void _memcardDuplicateSaveData_multi(void*);
static void* _memcardGetMultiSaveDataToSTRUCT(void*, long);

static inline s32 _memcardPollTask(void) {
    if (_memcardStatusPtr->task == 0x30) {
        _memcardStatusPtr->msg = _memcardMsgOpen((MEMCARD_MSGTYPE)_memcardStatusPtr->msg);
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
    }
    if (_memcardStatusPtr->task != 0x32) {
        return 0;
    }
    return _memcardStatusPtr->result;
}

static inline void _memcardFinish(void) {
    if (_memcardStatusPtr->state != 0) {
        if (_memcardStatusPtr->state != 8) {
            winMsgClose(1);
        }
        GSgappTerminate(_memcardStatusPtr->gapp);
        GSmemFree(_memcardStatusPtr->buf54);
        _memcardStatusPtr->buf54 = 0;
        GSmemFree(_memcardStatusPtr->buf50);
        _memcardStatusPtr->buf50 = 0;
    }
    _memcardStatusPtr->state = 0;
}

static inline void _memcardStart(s32 state, s32 priority, s32 param) {
    if (_memcardStatusPtr->state != 0) {
        do {
            GSthreadSwitch();
        } while (_memcardPollTask() == 0);
        _memcardFinish();
    }
    if (priority == 0) {
        priority = 2;
    }
    _memcardStatusPtr->state = state;
    _memcardStatusPtr->param = param;
    _memcardStatusPtr->priority = priority;
    _memcardStatusPtr->result = 0;
    _memcardStatusPtr->task = 0;
    _memcardStatusPtr->msg = 0;
    _memcardStatusPtr->unk3E = 0;
    _memcardStatusPtr->buf50 = GSmemAllocAlign(0x28400, 0x20);
    _memcardStatusPtr->buf54 = GSmemAllocAlign(0xA000, 0x20);
    _memcardStatusPtr->gapp = GSgappCreate(1, 0x17, 0, _memcardJobMain);
    _memcardStatusPtr->saveData = savedataGetStatus(0, 0);
}

extern "C" {

void memcard_debug_Load2(void) {
    _memcardStatusPtr->valid = 1;
}

void memcard_debug_Load(void* data) {
    s32* save;
    _memcardStart(2, 2, 0);
    _memcard_Decryption(data);
    _memcardStoreSaveData_multi(data);
    _memcardStatusPtr->valid = 1;
    _memcardFinish();
    save = (s32*)savedataGetStatus(0, 1);
    if (save[4] == 0) {
        save[4] = save[4] + 1;
    }
}

void memcard_debug_Save(void* data) {
    _memcardStart(0xB, 2, 0);
    _memcardDuplicateSaveData_multi(data);
    _memcard_Encryption(data);
    _memcardFinish();
}

}

#define MEMCARD_STORE(idx, off, max)                                          \
    dst = _memcardGetMultiSaveDataToSTRUCT(arg, idx);                         \
    src = savedataGetStatus(_memcardStatusPtr->saveData, idx);                \
    size = *(u16*)((u8*)arg + (off));                                         \
    if (size > (max)) {                                                       \
        size = (max);                                                         \
    }                                                                         \
    memcpy(src, dst, size)

#define MEMCARD_STORE2(idx, off, max)                                         \
    dst2 = _memcardGetMultiSaveDataToSTRUCT(arg, idx);                        \
    src = savedataGetStatus(_memcardStatusPtr->saveData, idx);                \
    size = *(u16*)((u8*)arg + (off));                                         \
    if (size > (max)) {                                                       \
        size = (max);                                                         \
    }                                                                         \
    memcpy(src, dst2, size)

void _memcardStoreSaveData_multi(void* arg) {
    void* dst;
    u16 size16;
    void* dst2;
    void* src;
    u32 size;
    MEMCARD_STORE(1, 0x18, 0x88);
    MEMCARD_STORE(2, 0x1A, 0x978);
    dst = _memcardGetMultiSaveDataToSTRUCT(arg, 3);
    src = savedataGetStatus(_memcardStatusPtr->saveData, 3);
    size = *(u16*)((u8*)arg + 0x80);
    size = (size << 16) + *(u16*)((u8*)arg + 0x1C);
    if (size > 0xBC50) {
        size = 0xBC50;
    }
    memcpy(src, dst, size);
    MEMCARD_STORE(0xA, 0x1E, 0x4A);
    MEMCARD_STORE(0xB, 0x20, 0xCC);
    MEMCARD_STORE(0xC, 0x22, 0x1774);
    MEMCARD_STORE(0xE, 0x24, 0x364);
    MEMCARD_STORE(0xF, 0x26, 0x2400);
    dst2 = _memcardGetMultiSaveDataToSTRUCT(arg, 0x17);
    size16 = *(u16*)((u8*)arg + 0x28);
    if (size16 == 0x6B4) {
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 4), dst2, *(u16*)((u8*)arg + 0x78));
        dst2 = (u8*)dst2 + *(u16*)((u8*)arg + 0x78);
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 5), dst2, *(u16*)((u8*)arg + 0x7A));
        dst2 = (u8*)dst2 + *(u16*)((u8*)arg + 0x7A);
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 6), dst2, *(u16*)((u8*)arg + 0x7C));
        dst2 = (u8*)dst2 + *(u16*)((u8*)arg + 0x7C);
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x18), dst2, *(u16*)((u8*)arg + 0x7E));
        dst2 = (u8*)dst2 + *(u16*)((u8*)arg + 0x7E);
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x1B), dst2, *(u16*)((u8*)arg + 0x82));
    } else {
        memcpy(savedataGetStatus(_memcardStatusPtr->saveData, 0x17), dst2, size16);
    }
    MEMCARD_STORE2(0x10, 0x2A, 0xB);
    MEMCARD_STORE2(0x16, 0x36, 0xC800);
    MEMCARD_STORE2(0x15, 0x34, 0x2298);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x11);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x12);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x13);
    _memcardGetMultiSaveDataToSTRUCT(arg, 0x14);
}

static s32 _memcardMergeDataPack(void) {
    void* data;
    u8* pack = (u8*)_memcardStatusPtr->buf50 + 8;
    data = _memcardGetMultiSaveDataToSTRUCT(pack, 1);
    switch (_memcardStatusPtr->state) {
    case 9:
        _memcardDuplicateSaveData_multi(pack);
        _memcardStoreSaveData_multi(pack);
        break;
    case 13: {
        void* save = savedataGetStatus(0, 0xE);
        memcpy(_memcardGetMultiSaveDataToSTRUCT(pack, 0xE), save, 0x364);
        break;
    }
    }
    gamedatasaveSetStatus(data, 9, gamedatasaveGetStatus(0, 9));
    gamedatasaveSetStatus(data, 0xA, gamedatasaveGetStatus(0, 0xA));
    gamedatasaveSetStatus(data, 0xB, gamedatasaveGetStatus(0, 0xB));
    return 0x25;
}

#define MEMCARD_MULTI_ADD(base, off)                      \
    {                                                     \
        u32 hi = ((u16*)(base))[((off) + 2) / 2];         \
        u32 lo = ((u16*)(base))[(off) / 2];               \
        data = (hi << 16) + data;                         \
        data = lo + data;                                 \
    }

static void* _memcardGetMultiSaveDataToSTRUCT(void* base, long index) {
    u32 data = (u32)base + 0xA0;
    switch (index) {
    case 1:
        MEMCARD_MULTI_ADD(base, 0x38)
        break;
    case 2:
        MEMCARD_MULTI_ADD(base, 0x3C)
        break;
    case 3:
        MEMCARD_MULTI_ADD(base, 0x40)
        break;
    case 0x17:
        MEMCARD_MULTI_ADD(base, 0x58)
        break;
    case 0xA:
        MEMCARD_MULTI_ADD(base, 0x44)
        break;
    case 0xB:
        MEMCARD_MULTI_ADD(base, 0x48)
        break;
    case 0xC:
        MEMCARD_MULTI_ADD(base, 0x4C)
        break;
    case 0xE:
        MEMCARD_MULTI_ADD(base, 0x50)
        break;
    case 0xF:
        MEMCARD_MULTI_ADD(base, 0x54)
        break;
    case 0x10:
        MEMCARD_MULTI_ADD(base, 0x5C)
        break;
    case 0x16:
        MEMCARD_MULTI_ADD(base, 0x74)
        break;
    case 0x11:
        MEMCARD_MULTI_ADD(base, 0x60)
        break;
    case 0x12:
        MEMCARD_MULTI_ADD(base, 0x64)
        break;
    case 0x13:
        MEMCARD_MULTI_ADD(base, 0x68)
        break;
    case 0x14:
        MEMCARD_MULTI_ADD(base, 0x6C)
        break;
    case 0x15:
        MEMCARD_MULTI_ADD(base, 0x70)
        break;
    case 0:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xD:
        break;
    }
    return (void*)data;
}

static s32 _memcardExamineDataPack(void) {
    u8 valid;
    u8* pack = (u8*)_memcardStatusPtr->buf50;
    s32 sum;
    valid = _memcard_Decryption(pack + 8);
    if (valid) {
        sum = pack[0] + pack[1] + pack[2] + pack[3] + pack[4] + pack[5] + pack[6] + pack[7];
        if (*(u16*)(pack + 0x20) == 0x88) {
            if (sum == gamedatasaveGetStatus(_memcardGetMultiSaveDataToSTRUCT(pack + 8, 1), 0xD)) {
                valid = 1;
            } else {
                valid = 0;
            }
        } else {
            valid = 1;
        }
    }
    if (valid) {
        _memcardGetMultiSaveDataToSTRUCT(pack + 8, 1);
    }
    if (valid) {
        if (_memcardStatusPtr->state != 3) {
            _memcardStatusPtr->unk2C = *(s32*)(pack + 4);
            if (_memcardStatusPtr->limit > _memcardStatusPtr->unk2C) {
                _memcardStatusPtr->unk2C = _memcardStatusPtr->limit;
                _memcardStatusPtr->msg = 5;
                if (_memcardStatusPtr->state < 3 && _memcardStatusPtr->state >= 1) {
                    _memcardStoreSaveData_multi(pack + 8);
                    _memcardStatusPtr->nextTask = 0x25;
                } else {
                    _memcardStatusPtr->nextTask = 0x24;
                }
                return 0x30;
            }
        }
        if (_memcardStatusPtr->state < 4 && _memcardStatusPtr->state >= 1) {
            s32 next;
            _memcardStoreSaveData_multi(pack + 8);
            _memcardStatusPtr->msg = 0xC;
            _memcardStatusPtr->result = 3;
            next = 0x2C;
            if (_memcardStatusPtr->unk40 != 0) {
                next = 0x11;
            }
            return next;
        }
        return 0x24;
    }
    *(s32*)(pack + _memcardStatusPtr->index * 0x200 + 0x28004) = 0;
    return 0x1F;
}

struct MemcardCardStat {
    char fileName[32];
    u32 length;
    u32 time;
    u8 gameName[4];
    u8 company[2];
    u8 bannerFormat;
    u8 pad2F;
    u32 iconAddr;
    u16 iconFormat;
    u16 iconSpeed;
    u32 commentAddr;
    u32 offsetBanner;
    u32 offsetBannerTlut;
    u32 offsetIcon[8];
    u32 offsetIconTlut;
    u32 offsetData;
};

extern "C" {
s32 CARDFreeBlocks(s32, s32*, s32*);
s32 CARDFastOpen(s32, s32, void*);
s32 CARDGetStatus(s32, s32, MemcardCardStat*);
s32 pokecoloGetCountryCode(void);
int strcmp(const char*, const char*);
}

static inline u8 _memcardIsXDSave(MemcardCardStat* stat) {
    switch (pokecoloGetCountryCode()) {
    case 0:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXJ" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    case 1:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXE" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    case 2:
        if (strcmp(stat->fileName, "PokemonXD") == 0 && *(u32*)stat->gameName == *(u32*)"GXXP" && *(u16*)stat->company == *(u16*)"01") return 1;
        break;
    }
    return 0;
}

static s32 _memcardCardOpen(void) {
    s32 freeBytes;
    s32 freeFiles;
    MemcardCardStat stat2;
    s32 status;
    CARDFreeBlocks(*(s32*)((u8*)_memcardStatusPtr + 0x14), &freeBytes, &freeFiles);
    switch (pokecoloGetCountryCode()) {
    case 0: {
        s32 i;
        s32 result;
        s32 chan;
        void* info;
        MemcardCardStat stat;
        chan = *(s32*)((u8*)_memcardStatusPtr + 0x14);
        info = (u8*)_memcardStatusPtr + 0x8C;
        i = 0;
            for (;;) {
                result = CARDFastOpen(chan, i, info);
                if (result == 0) {
                    result = CARDGetStatus(chan, i, &stat);
                    u8 found;
                    if (result == 0) {
                        found = _memcardIsXDSave(&stat);
                    } else {
                        found = 0;
                    }
                    if (found) {
                        result = 0;
                        break;
                    }
                }
                ++i;
                if (i >= 0x7F) {
                    if (result == 0) result = -4;
                    break;
                }
            }
        status = result;
        break;
    }
    case 1:
    case 2: {
        void* info;
        s32 chan;
        s32 result;
        s32 i;
        MemcardCardStat stat;
        chan = *(s32*)((u8*)_memcardStatusPtr + 0x14);
        info = (u8*)_memcardStatusPtr + 0x8C;
        i = 0;
            for (;;) {
                result = CARDFastOpen(chan, i, info);
                if (result == 0) {
                    result = CARDGetStatus(chan, i, &stat);
                    u8 found;
                    if (result == 0) {
                        found = _memcardIsXDSave(&stat);
                    } else {
                        found = 0;
                    }
                    if (found) {
                        result = 0;
                        break;
                    }
                }
                ++i;
                if (i >= 0x7F) {
                    if (result == 0) result = -4;
                    break;
                }
            }
        status = result;
        break;
    }
    }
    switch (status) {
    case 0: {
        _memcardStatusPtr->unk3E = 1;
        status = CARDGetStatus(*(s32*)((u8*)_memcardStatusPtr + 0x14), *(s32*)((u8*)_memcardStatusPtr + 0x90), &stat2);
        if (status != 0) goto fail;
        if (stat2.commentAddr + 0x10000 != 0xFFFF) {
            if (_memcardStatusPtr->state == 0xC) {
                _memcardStatusPtr->msg = 2;
                _memcardStatusPtr->nextTask = 0xB;
                return 0x30;
            }
            s32 ret = 0x19;
            if (_memcardStatusPtr->state == 3) ret = 0x1C;
            return ret;
        }
        status = -4;
        freeBytes += 0x56000;
        freeFiles += 1;
    }
    // fall through
    case -4:
        switch (_memcardStatusPtr->state) {
        case 1:
            if (freeBytes < 0x56000) { status = -9; goto fail; }
            if (freeFiles < 1) { status = -8; goto fail; }
            _memcardStatusPtr->msg = 6;
            _memcardStatusPtr->nextTask = 0xA;
            return 0x30;
        case 9:
            _memcardStatusPtr->msg = 2;
            _memcardStatusPtr->nextTask = 0xB;
            return 0x30;
        }
        // fall through
    default:
    fail:
        _memcardStatusPtr->msg = status;
        return 0x2B;
    }
}

static void _memcardCallback(long, long) {
    _memcardStatusPtr->callbackDone = 1;
}

static u8 _memcardMsgOpen(MEMCARD_MSGTYPE msg) {
    u8 retry = 0;
    u8 confirm = 0;
    s32 yes;
    s32 id;
    switch (msg) {
    case 0:
        return 0;
    case 1:
        id = 0x6A;
        break;
    case 2:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x6C;
            break;
        default:
            id = 0x90;
            break;
        }
        break;
    case 3:
        id = 0x84;
        break;
    case 4:
        id = 0x73;
        break;
    case 5:
        id = 0x7B;
        break;
    case 6:
        id = 0x83;
        retry = 1;
        yes = 0;
        break;
    case 7:
        id = 0x71;
        retry = 1;
        yes = 0;
        confirm = 1;
        break;
    case 8:
        id = 0x7A;
        retry = 1;
        yes = 1;
        break;
    case 9:
        id = 0x74;
        break;
    case 10:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x6D;
            break;
        default:
            id = 0x91;
            break;
        }
        GSsndPlay(0x1D, 0, 0);
        break;
    case 11:
        id = 0x85;
        break;
    case 12:
        id = 0x81;
        GSsndPlay(0x1D, 0, 0);
        break;
    case 13:
        id = 0x79;
        break;
    case 14:
        id = 0x9B;
        break;
    case 15:
        switch (_memcardStatusPtr->state) {
        case 5:
        case 6:
        case 7:
        case 0xD:
            id = 0x9B;
            break;
        default:
            id = 0x97;
            break;
        }
        break;
    case 16:
        id = 0x72;
        break;
    case 17:
        id = 0x7C;
        if (_memcardStatusPtr->state != 2) {
            winMsgOpen(_memcardStatusPtr->priority, 0x7C, 1, 1);
            id = 0x80;
        }
        break;
    case 18:
        id = 0x7D;
        break;
    case -2:
        id = 0x77;
        break;
    case -3:
        id = 0x70;
        break;
    case -4:
        id = 0x6F;
        break;
    case -5:
        id = 0x76;
        break;
    case -13:
    case -6:
        switch (_memcardStatusPtr->state) {
        case 1:
        case 2:
            id = 0x7E;
            if (_memcardStatusPtr->unk60 == 0x32) {
                break;
            }
        default:
            id = 0x6E;
            break;
        }
        break;
    case -9:
    case -8:
        id = 0x78;
        msgctrlSetValue(0x2F, 0x2B);
        break;
    case 19:
        winMsgOpen(_memcardStatusPtr->priority, 0x7C, 1, 1);
        id = 0x80;
        break;
    default:
        id = 0x6E;
        break;
    }
    winMsgOpen(_memcardStatusPtr->priority, id, 1, 1);
    if (retry) {
        if (menuSubOpenYesNo(0, 0x3C, 0xAA, yes)) {
            retry = 0;
        } else {
            retry = 1;
            if (confirm) {
                winMsgOpen(_memcardStatusPtr->priority, 0xF3, 1, 1);
                if (menuSubOpenYesNo(0, 0x3C, 0xAA, 1)) {
                    retry = 0;
                } else {
                    retry = 1;
                }
            }
        }
    }
    return retry;
}

extern "C" {

void* memcardMemFreeForSavedata(void* p) {
    GSmemFree(p);
    return 0;
}

void* memcardMemAllocForSavedata(void) {
    return GSmemAllocAlign(0x27FD0, 0x20);
}

void memcardFinalizeTask(void) {
    _memcardFinish();
}

void memcardUnlockWaitGBA(u8 flag) {
    if (_memcardStatusPtr->task == 0x31 && flag != 0) {
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
        _memcardStatusPtr->timer = ((HSD_Rand() << 16) | HSD_Rand()) % 0x3C;
        _memcardStatusPtr->timer = _memcardStatusPtr->timer + 1;
        s32 rnd = (u16)HSD_Rand();
        _memcardStatusPtr->timer = _memcardStatusPtr->timer + rnd % 0x3C;
    } else {
        _memcardStatusPtr->msg = 0xF;
        _memcardStatusPtr->task = 0x2B;
    }
}

s32 memcardCheckTaskWaitGBA(void) {
    return _memcardStatusPtr->task == 0x31 ? 1 : 0;
}

u8 memcardIsMemCardValid(void) {
    return _memcardStatusPtr->valid;
}

s32 memcardGetTaskResult(void) {
    if (_memcardStatusPtr->task == 0x30) {
        _memcardStatusPtr->msg = _memcardMsgOpen((MEMCARD_MSGTYPE)_memcardStatusPtr->msg);
        _memcardStatusPtr->task = _memcardStatusPtr->nextTask;
    }
    if (_memcardStatusPtr->task != 0x32) {
        return 0;
    }
    return _memcardStatusPtr->result;
}

void memcardSetupTask(s32 state, s32 priority, s32 param) {
    if (_memcardStatusPtr->state != 0) {
        do {
            GSthreadSwitch();
        } while (_memcardPollTask() == 0);
        _memcardFinish();
    }
    if (priority == 0) {
        priority = 2;
    }
    _memcardStatusPtr->state = state;
    _memcardStatusPtr->param = param;
    _memcardStatusPtr->priority = priority;
    _memcardStatusPtr->result = 0;
    _memcardStatusPtr->task = 0;
    _memcardStatusPtr->msg = 0;
    _memcardStatusPtr->unk3E = 0;
    _memcardStatusPtr->buf50 = GSmemAllocAlign(0x28400, 0x20);
    _memcardStatusPtr->buf54 = GSmemAllocAlign(0xA000, 0x20);
    _memcardStatusPtr->gapp = GSgappCreate(1, 0x17, 0, _memcardJobMain);
    _memcardStatusPtr->saveData = savedataGetStatus(0, 0);
}

s32 memcardTaskCall(s32 state, s32 priority, s32 param) {
    s32 result;
    if (state == 1) {
        memset(savedataGetStatus(0, 0), 0, 0x27FD0);
        menuCBBios_RuleEditSaveON(0);
    }
    if (state == 0xE) {
        state = 4;
        _memcard_anySaveOFF_Flag = 1;
    } else {
        _memcard_anySaveOFF_Flag = 0;
    }
    _memcardStart(state, priority, param);
    do {
        GSthreadSwitch();
        result = _memcardPollTask();
    } while (result == 0);
    _memcardFinish();
    return result;
}

void memcardInitialize(void) {
    if (_memcardInitializeFlag == 0) {
        CARDInit();
        _memcardStatusPtr = (MemcardStatus*)(_memcardStatusBuf + (((HSD_Rand() << 16) | HSD_Rand()) & 0xF8));
        _memcardStatusPtr->state = 0;
        _memcardStatusPtr->buf50 = 0;
        _memcardStatusPtr->buf54 = 0;
        _memcardStatusPtr->unk2C = 0;
        _memcardInitializeFlag = 1;
    }
}

}
