#ifndef MENU_DATA_BIOS_PRIVATE_HPP
#define MENU_DATA_BIOS_PRIVATE_HPP
#include <global.h>
#include <libc/stddef.h>
struct MenuDataRecord {
    u8 kind : 3;
    u8 flags : 5;
    u8 reserved01[2];
    u8 displayMax;
    u8 reserved04[4];
    s16 x, y;
    u8 reserved0C[16];
};
struct MenuItemRecord {
    u8 selected : 1;
    u8 flags : 7;
    u8 reserved01[5];
    s16 x, y;
    u8 reserved0A[4];
    s16 sprite;
    u8 reserved10[12];
};
struct MenuSpriteValue { u8 data[12]; };
struct MenuSpriteRecord { u8 header[8]; MenuSpriteValue values[5]; u8 tail[4]; };
struct MenuSequenceRecord { u8 data[12]; };
struct MenuSoundRecord { u16 sounds[6]; };
typedef char MenuDataRecordSize[sizeof(MenuDataRecord)==28?1:-1];
typedef char MenuItemRecordSize[sizeof(MenuItemRecord)==28?1:-1];
typedef char MenuSpriteRecordSize[sizeof(MenuSpriteRecord)==72?1:-1];
#endif
