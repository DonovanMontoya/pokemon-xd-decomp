#ifndef JOUTAI_DATA_LAYOUT_HPP
#define JOUTAI_DATA_LAYOUT_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct JoutaiDataRecord {
    u8 statusKind;
    u8 useBanme;
    u8 writeMode;
    u8 maxCount;
    u8 kaisuuDataId;
    u8 reserved05[0x3];
    u16 status;
    u16 sameJoutai;
    u8 reserved0c[0x4];
    u32 name;
};
typedef char JoutaiDataRecordSize[sizeof(JoutaiDataRecord) == 0x14 ? 1 : -1];
typedef char JoutaiDataRecord_statusKindOffset[offsetof(JoutaiDataRecord, statusKind) == 0x0 ? 1 : -1];
typedef char JoutaiDataRecord_useBanmeOffset[offsetof(JoutaiDataRecord, useBanme) == 0x1 ? 1 : -1];
typedef char JoutaiDataRecord_writeModeOffset[offsetof(JoutaiDataRecord, writeMode) == 0x2 ? 1 : -1];
typedef char JoutaiDataRecord_maxCountOffset[offsetof(JoutaiDataRecord, maxCount) == 0x3 ? 1 : -1];
typedef char JoutaiDataRecord_kaisuuDataIdOffset[offsetof(JoutaiDataRecord, kaisuuDataId) == 0x4 ? 1 : -1];
typedef char JoutaiDataRecord_statusOffset[offsetof(JoutaiDataRecord, status) == 0x8 ? 1 : -1];
typedef char JoutaiDataRecord_sameJoutaiOffset[offsetof(JoutaiDataRecord, sameJoutai) == 0xa ? 1 : -1];
typedef char JoutaiDataRecord_nameOffset[offsetof(JoutaiDataRecord, name) == 0x10 ? 1 : -1];
extern "C" {
extern JoutaiDataRecord joutai_data[];
extern u32 joutai_data_number;
JoutaiDataRecord* joutaiDataBiosGetDataPtr(u16);
}
#endif
