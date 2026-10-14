#ifndef FLOOR_BIOS_PRIVATE_HPP
#define FLOOR_BIOS_PRIVATE_HPP
#include <dolphin/types.h>
#include <libc/stddef.h>
struct GSvec { f32 x, y, z; void set(f32, f32, f32); };
struct floorCharacter_dd_ {
    u8 visibility:1, loadInit:1, isHit:1, flag4:1, talkWallThrough:1, flag2:1, reservedFlags:2;
    u8 moveType:3, talkStartType:2, talkEndType:2, reservedType:1;
    u8 parameter2, parameter3;
    s16 rotation;
    u16 peopleIndex, nameID;
    u32 resourceID, moveScriptID, talkScriptID;
    f32 x, y, z;
};
struct FloorRenderData { u32 sunID, shadowLightID, shadowReceiverIDs[8], secondaryRenderIDs[3], noFogModelIDs[3]; };
struct FloorPosition { s16 rotation; u16 reserved2; f32 x, y, z; };
struct FloorPositionList { u32 *count; FloorPosition *entries; };
struct FloorCharacterList { u32 *count; floorCharacter_dd_ *entries; };
struct FloorData {
    u8 area, kind;
    u16 floorID;
    u32 mapResourceID;
    FloorRenderData **render;
    FloorCharacterList **characters;
    FloorPositionList **positions;
    void **fieldCameras;
    u32 placeNameID;
    void (*preFunction)();
    void (*mainFunction)();
    void (*postFunction)();
    u32 reserved28;
    u32 languageGroupIDs[5];
};
struct FloorTreasure { u8 reserved0[4]; u16 floorID; u8 reserved6[0x16]; };
typedef char FloorDataSizeCheck[sizeof(FloorData) == 0x40 ? 1 : -1];
typedef char FloorCharacterSizeCheck[sizeof(floorCharacter_dd_) == 0x24 ? 1 : -1];
typedef char FloorRenderSizeCheck[sizeof(FloorRenderData) == 0x40 ? 1 : -1];
typedef char FloorPositionSizeCheck[sizeof(FloorPosition) == 0x10 ? 1 : -1];
typedef char FloorTreasureSizeCheck[sizeof(FloorTreasure) == 0x1C ? 1 : -1];
typedef char FloorCharacterPositionOffset[offsetof(floorCharacter_dd_, x) == 0x18 ? 1 : -1];
typedef char FloorDataGroupOffset[offsetof(FloorData, languageGroupIDs) == 0x2C ? 1 : -1];
extern "C" {
u32 GSfloorGetCurrent();
FloorData *floorDataBiosGetCurrentPtr();
FloorData *floorDataBiosGetPtr(u32);
FloorPositionList *floorDataBiosGetPosListPtr(FloorData *);
floorCharacter_dd_ *floorDataBiosGetCharInfo(FloorData *, u32);
u32 floorDataBiosGetGroupID(FloorData *);
s32 fn_801231D4();
}
#endif
