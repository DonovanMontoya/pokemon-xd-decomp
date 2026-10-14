#include <game/pxdvs/GSAPI/GSscratch/GSscratch.hpp>
#include <dolphin/os.h>

struct ScratchBlock {
    u8 start, count;
    GSscratchCallback callback;
};
static ScratchBlock _blockTable[32];
static u32 _blockMap;
static u32 _entriesQueued;
static u8* _scratchPadBase;
static u8 _scratchInvalid;

extern "C" void GSscratchSetValid() {
    if (_scratchInvalid) {
        s32 i = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->start != 255 && block->callback)
                block->callback(1, _scratchPadBase + (block->start << 9), block->count);
        } while (++block, i--);
        _scratchInvalid = 0;
    }
}
extern "C" void GSscratchSetInvalid() {
    if (_scratchInvalid != 1) {
        s32 i = 31;
        ScratchBlock* block = _blockTable;
        do {
            if (block->start != 255 && block->callback)
                block->callback(0, _scratchPadBase + (block->start << 9), block->count);
        } while (++block, i--);
        _scratchInvalid = 1;
    }
}
extern "C" u8 GSscratchIsPtr(void* pointer) {
    return ((u32)pointer & 0xf0000000) == ((u32)_scratchPadBase & 0xf0000000);
}
extern "C" void GSscratchWaitForCompletion() {
    LCQueueWait(_entriesQueued);
    _entriesQueued = 0;
}
extern "C" s32 GSscratchStore(void* destination, void* source, u32 bytes) {
    if (LCQueueLength() >= 15) return 1;
    if (((u32)source & 31) || ((u32)destination & 31)) return 2;
    if (bytes & 31) return 2;
    _entriesQueued += LCStoreData(destination, source, bytes);
    return 0;
}

static inline ScratchBlock* scratchFindBlock(u8 start) {
    ScratchBlock* block = _blockTable;
    for (s32 i = 0; i < 32; ++block, ++i) {
        if (block->start == start) return block;
    }
    return 0;
}
static inline u32 scratchRangeMask(u8 start, u8 count) {
    u32 occupied = 0;
    u32 bit = 0x80000000;
    while (start--) bit >>= 1;
    while (count--) {
        occupied <<= 1;
        if (bit) {
            if (_blockMap & bit) occupied |= 1;
            bit >>= 1;
        } else occupied |= 1;
    }
    return occupied;
}
extern "C" void GSscratchFree(void* pointer) {
    u8 start = ((u32)pointer - (u32)_scratchPadBase) >> 9;
    ScratchBlock* block = scratchFindBlock(start);
    if (block) {
        u32 bit;
        u8 index;
        u8 count;
        count = block->count;
        bit = 0x80000000;
        index = block->start;
        while (index--) bit >>= 1;
        u32 map = _blockMap;
        while (count--) {
            map &= ~bit;
            bit >>= 1;
        }
        _blockMap = map;
        block->start = 255;
    }
}
static inline void scratchSetRange(u8 index, u8 count) {
    u32 bit = 0x80000000;
    while (index--) bit >>= 1;
    u32 map = _blockMap;
    while (count--) {
        map |= bit;
        bit >>= 1;
    }
    _blockMap = map;
}
extern "C" void* GSscratchAlloc(u8 blocks, GSscratchCallback callback) {
    if (_scratchInvalid == 1) return 0;
    if (blocks == 0 || blocks > 32) return 0;
    for (u8 start = 0; start < 32; ++start) {
        if (scratchRangeMask(start, blocks) == 0) {
            ScratchBlock* block = scratchFindBlock(255);
            if (!block) return 0;
            block->start = start;
            block->count = blocks;
            block->callback = callback;
            scratchSetRange(start, blocks);
            return _scratchPadBase + (block->start << 9);
        }
    }
    return 0;
}
