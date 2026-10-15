#ifndef GAME_MENUBATTLEDISK_LAYOUT_HPP
#define GAME_MENUBATTLEDISK_LAYOUT_HPP
#include <dolphin/types.h>

struct tagWINDOW_WORK {
    u8 reserved0;
    s8 phase;               // 0x01
    s8 step;                // 0x02
    u8 reserved3;
    s32 menu;               // 0x04
    u8 reserved8[0x8B];
    u8 alpha;               // 0x93
    u8 reserved94[0xA];
    s16 cursor;             // 0x9E
    u8 reservedA0[2];
    s16 prevCursor;         // 0xA2
};

struct tagSPRITE_WORK {
    u8 reserved0[6];
    s16 id;                 // 0x06
    u8 reserved8[0x44];
    s32 value4C;            // 0x4C
    u8 reserved50[4];
    s16 x;                  // 0x54
    s16 y;                  // 0x56
};

struct BDiskMenuItem {
    u8 enable : 1;
    u8 last : 1;
    u8 reserved0 : 6;
    u8 reserved1[5];
    s16 x;                  // 0x06
    s16 y;                  // 0x08
    u8 reservedA[0xE];
    s16 next;               // 0x18
};

struct BDiskMenuData {
    u8 reserved0[6];
    s16 first;              // 0x06
};

struct Hero {
    u8 reserved0[0x978];
    Hero();
    static Hero* getHeroPtr();
};


class cBattleDisk {
public:
    static s32 mItemCurIdx[8];
    static s32 mContentsCurIdx[15];
};

// Entry n of the disk list lives at gBDisk + n * 0x18 + 0x28.
struct BDiskEntry {
    u8 reserved0[0x28];
    u8 id;                  // 0x28
    u8 reserved1;
    u16 itemID;             // 0x02
    s32 name;               // 0x04
    s32 doc;                // 0x08
    s32 explain1;           // 0x0C
    s32 explain2;           // 0x10
    s32 title;              // 0x14
};

struct BDisk {
    s16 unk0;                   // 0x00
    s16 unk2;                   // 0x02
    s16 unk4;                   // 0x04
    s16 unk6;                   // 0x06
    s16 mode;                   // 0x08
    s16 count;                  // 0x0A
    s16 scroll;                 // 0x0C
    s16 unkE;                   // 0x0E
    s16 unk10;                  // 0x10
    s16 unk12;                  // 0x12
    s16 unk14;                  // 0x14
    u8 unk16;                   // 0x16
    u8 selectedID;              // 0x17
    u16 result;                 // 0x18
    u8 reserved1A[0xA];
    s32 field24;                // 0x24
    u8 entries[0x5A0];      // 0x28 (BDiskEntry rows, stride 0x18)
    Hero heroes[2];             // 0x5C8
    u8 pad[8];
    BDisk() {
        unkE = 0;
        unk12 = 0;
        unk10 = 0;
        scroll = 0;
        count = 0;
    }
};

extern BDisk gBDisk;

inline BDiskEntry* bdiskEntry(u32 n) {
    return (BDiskEntry*)((u8*)&gBDisk + n * 0x18);
}

#endif
