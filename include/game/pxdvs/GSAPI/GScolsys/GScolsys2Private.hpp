#ifndef GAME_PXDVS_GSAPI_GSCOLSYS_GSCOLSYS2_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSCOLSYS_GSCOLSYS2_PRIVATE_HPP
#include <dolphin/types.h>
#include <dolphin/mtx.h>
#include <libc/stddef.h>
#include <game/pxdvs/app/floor/floorPrivate.hpp>
struct CCDGeometry { void *vertices; u32 count; void *indices, *planes; };
struct CCDReference { void *entries; };
struct CCDObject {
    f32 position[3], rotation[3], scale[3];
    CCDGeometry *geometry[3];
    CCDReference *references;
    CCDGeometry *auxGeometry;
    CCDReference *auxReferences;
    u32 reserved3c;
};
struct CCD_FILEHEAD { CCDObject *objects; u32 count; };
struct GSCOLSYS2_OBJ {
    f32 position[3], rotation[3], scale[3];
    u16 flags, padding;
    GSCOLSYS2_OBJ() {}
};
struct GSCOLSYS2_AUX { u8 data[16]; u16 flags, padding; };
struct GSCOLSYS2_FLOOR {
    GSCOLSYS2_OBJ objects[64];
    GSCOLSYS2_AUX auxiliary[48];
    GSCOLSYS2_FLOOR() {}
};
struct GSCOLSYS2_STATE {
    CCD_FILEHEAD *head;
    GSCOLSYS2_FLOOR floor[1];
    s32 currentFloor;
    void *format, *displayList;
};
struct GSCOLSYS2_FLAGS { u16 magic, reserved; u16 objects[64]; };
typedef char ColsysObjectSizeCheck[sizeof(GSCOLSYS2_OBJ) == 0x28 ? 1 : -1];
typedef char ColsysFloorSizeCheck[sizeof(GSCOLSYS2_FLOOR) == 0xdc0 ? 1 : -1];
typedef char ColsysStateSizeCheck[sizeof(GSCOLSYS2_STATE) == 0xdd0 ? 1 : -1];
typedef char ColsysCurrentFloorOffsetCheck[offsetof(GSCOLSYS2_STATE, currentFloor) == 0xdc4 ? 1 : -1];
typedef char CCDObjectSizeCheck[sizeof(CCDObject) == 0x40 ? 1 : -1];
#endif
