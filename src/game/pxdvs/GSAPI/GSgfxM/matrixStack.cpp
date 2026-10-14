#include <game/pxdvs/GSAPI/GSgfxM/matrixStack.hpp>
#include <game/pxdvs/GSAPI/GSmemman/poolAlloc.hpp>

extern "C" void* memcpy(void*, const void*, unsigned long);
extern Mtx mtxIdent;

void GSgfxMatrixStack::pop() {
    --current;
}


void GSgfxMatrixStack::pushMult(GSmtx* matrix) {
    ++current;
    PSMTXConcat((current - 1)->matrix, (f32(*)[4])matrix, current->matrix);
    current->flags |= 1;
}

void GSgfxMatrixStack::push(GSmtx* matrix) {
    ++current;
    if (matrix == 0) {
        PSMTXCopy((current - 1)->matrix, current->matrix);
    } else {
        PSMTXCopy((f32(*)[4])matrix, current->matrix);
    }
    current->flags |= 1;
}

GSgfxMatrixStack::~GSgfxMatrixStack() {
    GSmemFree(entries);
    entries = 0;
}

GSgfxMatrixStack::GSgfxMatrixStack(unsigned long count) {
    entries = (Entry*)GSmemAlloc(count * sizeof(Entry));
    current = entries;
    last = entries + (count - 1);
    memcpy(current->matrix, mtxIdent, sizeof(Mtx));
    current->flags |= 1;
}
