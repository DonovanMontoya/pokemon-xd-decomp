#include <game/pxdvs/GSAPI/GSflag/GSflag.hpp>

extern "C" {
void GSlogWrite(const char* format, ...);
extern GSflagData* flag_data;
extern u32* flag_data_number;
extern GSflagLevel* flag_level;

static u32 _flagGet(u32* words, const GSflagData* data, s32 id);
static void _flagSet(u32* words, const GSflagData* data, s32 id, u32 value);
static u32 _flagGetBitLength(u32 value);

static u32 _flagAND[33] = {
    0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f,
    0xff, 0x1ff, 0x3ff, 0x7ff, 0xfff, 0x1fff, 0x3fff, 0x7fff,
    0xffff, 0x1ffff, 0x3ffff, 0x7ffff, 0xfffff, 0x1fffff, 0x3fffff, 0x7fffff,
    0xffffff, 0x1ffffff, 0x3ffffff, 0x7ffffff, 0xfffffff, 0x1fffffff,
    0x3fffffff, 0x7fffffff, 0xffffffff
};

bool GSflagTest(s32 id) { return GSflagGet(id) != 0; }
void GSflagOff(s32 id) { GSflagSet(id, 0); }
void GSflagOn(s32 id) { GSflagSet(id, 1); }
u32 GSflagGet(s32 id) {
    return _flagGet(flag_level[flag_data[id].level].words, flag_data, id);
}
void GSflagSet(s32 id, u32 value) {
    _flagSet(flag_level[flag_data[id].level].words, flag_data, id, value);
}

static u32 _flagGet(u32* words, const GSflagData* data, s32 id) {
    if (words == 0) {
        GSlogWrite("ERROR[GSflagGet]:Initialization has not finished.\n");
        return 0;
    }
    u16 position = data[id].bitPosition;
    u32 width = data[id].bitLength;
    u32 word = (u32)position >> 5;
    s32 shift = position & 31;
    if (width > 1) {
        u32 low = words[word];
        s32 high = words[word + 1];
        low >>= shift;
        high <<= 32 - shift;
        return (high | low) & _flagAND[width];
    }
    return (words[word] >> shift) & 1;
}

static void _flagSet(u32* words, const GSflagData* data, s32 id, u32 value) {
    if (words == 0) {
        GSlogWrite("ERROR[GSflagSet]:Initialization has not finished.\n");
        return;
    }
    u32 position = data[id].bitPosition;
    u32 width = data[id].bitLength;
    s32 valueWidth = _flagGetBitLength(value);
    if (valueWidth > width) {
        GSlogWrite("ERROR[GSflagSet]:Overflow BitValue FlagID=%d Value=%d (%d BitLength=%d)>(Limit=%dBit).\n", id, value, value, valueWidth, width);
        value &= _flagAND[width];
    }
    u32 word = (u32)position >> 5;
    s32 shift = position & 31;
    if (width > 1) {
        u32 end = width + shift;
        s32* ptr = (s32*)&words[word];
        ptr[0] = (value << shift) | (ptr[0] & ~(_flagAND[width] << shift));
        if (end >= 32) {
            s32 extra = end - 32;
            ptr[1] = (value >> (width - extra)) | (ptr[1] & ~_flagAND[extra]);
        }
    } else if (value == 0) {
        words[word] &= ~(1 << shift);
    } else {
        words[word] |= 1 << shift;
    }
}

static u32 _flagGetBitLength(u32 value) { return 32 - __cntlzw(value); }

void GSflagClear(s32 level) {
    u32* words = flag_level[level].words;
    if (words == 0) {
        GSlogWrite("ERROR[GSflagClear]:Initialization has not finished.\n");
        return;
    }
    u32 count = flag_level[level].wordCount;
    for (u32 i = 0; i < count; ++i) {
        words[i] = 0;
    }
}

void GSflagInit(u32* level1, u32 size1, u32* level2, u32 size2, u32* level3, u32 size3) {
    GSflagInitBitPos(flag_data, *flag_data_number, size1, size2, size3);
    flag_level[1].words = level1;
    flag_level[2].words = level2;
    flag_level[3].words = level3;
    flag_level[1].wordCount = size1;
    flag_level[2].wordCount = size2;
    flag_level[3].wordCount = size3;
    GSflagClear(1);
    GSflagClear(2);
    GSflagClear(3);
}

void GSflagInitBitPos(GSflagData* data, u32 count, u32 size1, u32 size2, u32 size3) {
    GSflagData* cursor = data;
    u16 position1 = 0;
    u16 position2 = 0;
    u16 position3 = 0;
    for (u32 i = 0; i < count; ++cursor, ++i) {
        u32 width = cursor->bitLength;
        if (width > 32) {
            GSlogWrite("ERROR[GSflagInit]:Overflow BitLength FlagID=%d (Length=%d)>(Limit=%dBit).\n", i, width, 32);
            cursor->bitLength = 32;
        } else if (width == 0) {
            GSlogWrite("ERROR[GSflagInit]:Zero BitLength FlagID=%d (Length=%d)>(Limit=%dBit).\n", i, width, 32);
            cursor->bitLength = 1;
        }
        switch (cursor->level) {
        case 1:
            cursor->bitPosition = position1;
            position1 += cursor->bitLength;
            break;
        case 2:
            cursor->bitPosition = position2;
            position2 += cursor->bitLength;
            break;
        case 3:
            cursor->bitPosition = position3;
            position3 += cursor->bitLength;
            break;
        }
    }
    s32 words1 = (position1 + 31) / 32;
    if (size1 <= (u32)words1) GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel0 (Use Bytes=%d)>=(Limit Bytes=%d).\n", words1, size1);
    s32 words2 = (position2 + 31) / 32;
    if (size2 <= (u32)words2) GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel1 (Use Bytes=%d)>=(Limit Bytes=%d).\n", words2, size2);
    s32 words3 = (position3 + 31) / 32;
    if (size3 <= (u32)words3) GSlogWrite("ERROR[GSflagInit]:Overflow FlagLevel2 (Use Bytes=%d)>=(Limit Bytes=%d).\n", words3, size3);
}
}
