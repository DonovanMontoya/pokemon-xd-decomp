#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
#include <libc/string.h>

struct GSmtxInitializer {
    GSmtx matrix;
    GSmtxInitializer() {
        Mtx identity;
        PSMTXIdentity(identity);
        memcpy(matrix.matrix, identity, 0x30);
    }
};
GSmtxInitializer mtxIdent;
