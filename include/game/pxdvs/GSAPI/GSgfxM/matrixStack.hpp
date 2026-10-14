#ifndef GSGFX_MATRIX_STACK_HPP
#define GSGFX_MATRIX_STACK_HPP

#include <global.h>
#include <dolphin/mtx.h>

struct GSmtx;
class GSgfxMatrixStack {
public:
    struct Entry {
        u32 flags;
        Mtx matrix;
        Mtx inverse;
    };
    Entry* entries;
    Entry* current;
    Entry* last;

    GSgfxMatrixStack(unsigned long count);
    ~GSgfxMatrixStack();
    void push(GSmtx* matrix);
    void pushMult(GSmtx* matrix);
    void pop();
};
typedef char GSgfxMatrixEntrySize[sizeof(GSgfxMatrixStack::Entry) == 0x64 ? 1 : -1];
typedef char GSgfxMatrixStackSize[sizeof(GSgfxMatrixStack) == 0xc ? 1 : -1];

#endif
