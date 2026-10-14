#ifndef FSYS_BLOCK_HPP
#define FSYS_BLOCK_HPP
#include <global.h>
struct GSfsysBlock { GSfsysBlock *previous, *next; void* data; u32 length; };
extern "C" {
void _fsysMoveBlock(GSfsysBlock**, GSfsysBlock**);
void _fsysAddBlock(GSfsysBlock**, GSfsysBlock*);
void _fsysFreeBlockAll(GSfsysBlock**);
s32 _fsysFreeBlock(GSfsysBlock**, u8);
GSfsysBlock* _fsysAllocBlock();
s32 _fsysInitBlock(u32);
}
#endif
