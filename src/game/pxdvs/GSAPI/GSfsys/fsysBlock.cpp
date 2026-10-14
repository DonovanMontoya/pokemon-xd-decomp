#include <game/pxdvs/GSAPI/GSfsys/fsysBlock.hpp>
#include <dolphin/os.h>
extern "C" {
u32 ARQGetChunkSize();
void* _fsysDoMalloc(u32);
}
static u8* _fsysBlock;
static GSfsysBlock* _fsysBlockManage;
static u32 _fsysBlockIndex, _fsysBlockSize, _fsysBlockBufferSize;
u32 _fsysBlockByteSize;
#pragma dont_inline on
extern "C" {
void _fsysMoveBlock(GSfsysBlock** source, GSfsysBlock** destination) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBlock* block = *source;
    if (block) {
        while (block->next) block = block->next;
        if (block->previous) block->previous->next = 0;
        if (*source == block) *source = 0;
        block->previous = 0;
        block->next = 0;
        GSfsysBlock* tail = *destination;
        if (tail) {
            while (tail->next) tail = tail->next;
            tail->next = block;
            block->previous = tail;
        } else *destination = block;
    }
    OSRestoreInterrupts(interrupts);
}
void _fsysAddBlock(GSfsysBlock** list, GSfsysBlock* block) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBlock* old = *list;
    if (old) {
        if (block->next) {
            GSfsysBlock* tail = block->next;
            while (tail->next) tail = tail->next;
            tail->next = old;
            old->previous = tail;
        } else {
            block->next = old;
            old->previous = block;
        }
    }
    *list = block;
    OSRestoreInterrupts(interrupts);
}
void _fsysFreeBlockAll(GSfsysBlock** list) {
    for (;;) {
        if (!*list) return;
        _fsysFreeBlock(list, 1);
    }
}
s32 _fsysFreeBlock(GSfsysBlock** list, u8 first) {
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBlock* block = *list;
    if (block) {
        if (!first) {
            while (block->next) block = block->next;
            if (block->previous) block->previous->next = 0;
            if (*list == block) *list = 0;
            block->data = 0;
        } else {
            if (block->previous) block->previous->next = block->next;
            if (block->next) block->next->previous = block->previous;
            block->data = 0;
            *list = block->next;
        }
    }
    OSRestoreInterrupts(interrupts);
    return 1;
}
GSfsysBlock* _fsysAllocBlock() {
    GSfsysBlock* result = 0;
    BOOL interrupts = OSDisableInterrupts();
    GSfsysBlock* block;
    u32 index = _fsysBlockIndex;
    while (!result) {
        block = &_fsysBlockManage[index];
        if (!block->data) {
            result = block;
            block->data = _fsysBlock + index * _fsysBlockByteSize;
            block->previous = 0;
            block->next = 0;
            block->length = 0;
        }
        ++index;
        if (index >= _fsysBlockSize) index = 0;
    if (_fsysBlockIndex == index) break;
    }
    _fsysBlockIndex = index;
    OSRestoreInterrupts(interrupts);
    return result;
}
s32 _fsysInitBlock(u32 size) {
    _fsysBlockIndex = 0;
    _fsysBlockByteSize = ARQGetChunkSize();
    _fsysBlockBufferSize = size;
    if (!size) _fsysBlockBufferSize = 0x80000;
    _fsysBlockSize = _fsysBlockBufferSize / _fsysBlockByteSize;
    if (!_fsysBlockSize) return 0;
    _fsysBlock = (u8*)_fsysDoMalloc(_fsysBlockByteSize * _fsysBlockSize);
    if (!_fsysBlock) return 0;
    _fsysBlockManage = (GSfsysBlock*)_fsysDoMalloc(_fsysBlockSize * sizeof(GSfsysBlock));
    if (!_fsysBlockManage) return 0;
    for (u32 i = 0; i < _fsysBlockSize; ++i) {
        _fsysBlockManage[i].previous = 0;
        _fsysBlockManage[i].next = 0;
        _fsysBlockManage[i].data = 0;
        _fsysBlockManage[i].length = 0;
    }
    return 1;
}
}
#pragma dont_inline reset
