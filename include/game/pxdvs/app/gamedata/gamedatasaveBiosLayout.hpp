#ifndef GAMEDATASAVE_BIOS_LAYOUT_HPP
#define GAMEDATASAVE_BIOS_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct GamedataSavePayload {
    u32 saveCount;
    u32 saveRandom;
    u32 parChecksum;
    u32 floorId;
    u32 copiedWord18;
    u32 previousFloorId;
    union {
        u32 copiedWords20[2];
        f32 copiedFloat20;
        struct { u8 floorPositionIndex, noVibration, audioOption, flag23; } flagBytes;
    } flags20;
    union {
        f64 playtime;
        struct { u8 copiedByte28; u8 copiedBytes29to2b[3]; u32 copiedWord2c; } raw28;
    };
    union {
        u64 copiedAggregate30;
        f64 copiedAggregateDouble30;
        struct { u32 sysHeadChecksum; u32 copiedWord34; } checksumWords;
    };
    u32 copiedWord38;
    u32 reserved3c;
};
struct GamedataSaveRecord {
    u64 memcardId;
    GamedataSavePayload payload;
    u8 playdata[1];
};
typedef char GamedataSaveAssert_memcard[(offsetof(GamedataSaveRecord, memcardId)==0)?1:-1];
typedef char GamedataSaveAssert_payload[(offsetof(GamedataSaveRecord, payload)==8)?1:-1];
typedef char GamedataSaveAssert_save_count[(offsetof(GamedataSaveRecord, payload.saveCount)==8)?1:-1];
typedef char GamedataSaveAssert_checksum[(offsetof(GamedataSaveRecord, payload.parChecksum)==0x10)?1:-1];
typedef char GamedataSaveAssert_floor[(offsetof(GamedataSaveRecord, payload.floorId)==0x14)?1:-1];
typedef char GamedataSaveAssert_previous_floor[(offsetof(GamedataSaveRecord, payload.previousFloorId)==0x1c)?1:-1];
typedef char GamedataSaveAssert_floor_position[(offsetof(GamedataSaveRecord, payload.flags20.flagBytes.floorPositionIndex)==0x20)?1:-1];
typedef char GamedataSaveAssert_no_vibration[(offsetof(GamedataSaveRecord, payload.flags20.flagBytes.noVibration)==0x21)?1:-1];
typedef char GamedataSaveAssert_audio[(offsetof(GamedataSaveRecord, payload.flags20.flagBytes.audioOption)==0x22)?1:-1];
typedef char GamedataSaveAssert_flag23[(offsetof(GamedataSaveRecord, payload.flags20.flagBytes.flag23)==0x23)?1:-1];
typedef char GamedataSaveAssert_playtime[(offsetof(GamedataSaveRecord, payload.playtime)==0x28)?1:-1];
typedef char GamedataSaveAssert_sys_checksum[(offsetof(GamedataSaveRecord, payload.checksumWords.sysHeadChecksum)==0x30)?1:-1];
typedef char GamedataSaveAssert_copied_word38[(offsetof(GamedataSaveRecord, payload.copiedWord38)==0x38)?1:-1];
typedef char GamedataSaveAssert_playdata[(offsetof(GamedataSaveRecord, playdata)==0x40)?1:-1];
typedef char GamedataSaveAssert_payload_size[(sizeof(GamedataSavePayload)==0x38)?1:-1];
#endif
