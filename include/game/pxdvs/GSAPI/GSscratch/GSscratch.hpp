#ifndef GSSCRATCH_HPP
#define GSSCRATCH_HPP
#include <dolphin/types.h>
typedef void (*GSscratchCallback)(u8 valid, void* block, u8 blockCount);
extern "C" {
void GSscratchSetValid();
void GSscratchSetInvalid();
u8 GSscratchIsPtr(void*);
void GSscratchWaitForCompletion();
s32 GSscratchStore(void* destination, void* source, u32 bytes);
void GSscratchFree(void*);
void* GSscratchAlloc(u8 blocks, GSscratchCallback callback);
}
#endif
