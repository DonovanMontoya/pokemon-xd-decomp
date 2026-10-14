#ifndef GSFLAG_HPP
#define GSFLAG_HPP
#include <global.h>

struct GSflagData {
    u8 level : 2;
    u8 bitLength : 6;
    u8 reserved;
    u16 bitPosition;
    u16 reserved2;
};

struct GSflagLevel {
    u32 wordCount;
    u32* words;
};

extern "C" {
bool GSflagTest(s32 id);
void GSflagOff(s32 id);
void GSflagOn(s32 id);
u32 GSflagGet(s32 id);
void GSflagSet(s32 id, u32 value);
void GSflagClear(s32 level);
void GSflagInit(u32* level1, u32 size1, u32* level2, u32 size2, u32* level3, u32 size3);
void GSflagInitBitPos(GSflagData* data, u32 count, u32 size1, u32 size2, u32 size3);
}
#endif
