#ifndef FLOOR_MANAGER_LAYOUT_HPP
#define FLOOR_MANAGER_LAYOUT_HPP
#include <dolphin/types.h>
typedef struct FloorStackLayout FloorStackLayout;
typedef struct FloorStackListLayout FloorStackListLayout;
typedef struct FloorScriptLayout FloorScriptLayout;
typedef struct FloorModuleListLayout FloorModuleListLayout;
typedef struct FloorManagerLayout FloorManagerLayout;
typedef struct FloorSaveHeader FloorSaveHeader;
typedef struct FloorStateDataPtr FloorStateDataPtr;
typedef struct FloorWriteStreamLayout FloorWriteStreamLayout;
struct FloorStackLayout {
    u32 groupID;
    u32 floorID;
    void *pushState;
    u32 pushStateSize;
    u8 pushFlag;
    u8 popFlag;
    u8 reserved12[6];
    s32 type;
    u8 reserved1C[0x204];
    s32 updateState;
};
struct FloorStackListLayout {
    FloorStackLayout *stacks;
    s32 current;
    u32 capacity;
};
struct FloorScriptLayout {
    u8 reserved0[0x93c];
    u32 mapping;
    u8 reserved940[0x80];
};
struct FloorModuleListLayout {
    u8 reserved0[0x10];
    u32 pushStateSize;
    struct FloorModuleVirtualTable { void *reserved[2]; void (*destroy)(FloorModuleListLayout *, s16); } *vtable;
};
struct FloorManagerLayout {
    FloorModuleListLayout *modules;
    FloorStackListLayout *stackList;
    s32 task;
    s32 nextTask;
    u32 nextFloorID;
    u8 changing;
    u8 reserved15[3];
    s32 commonScriptType;
    FloorScriptLayout commonScript;
    u32 maxSaveSize;
    u16 maxSaveFloorID;
    u8 reserved9E2[2];
    void *vtable;
};
struct FloorSaveHeader {
    char magic[4];
    u32 size;
    u32 scriptSize;
    u32 moduleSize;
    u32 reserved;
    u32 maxSize;
    u16 maxFloorID;
    u8 reserved1A[6];
};
struct FloorStateDataPtr { FloorSaveHeader *header; void *script; void *modules; };
struct FloorWriteStreamLayout { void *top; void *buffer; u32 size; void *current; u8 ownsBuffer; u8 reserved11[3]; };
#define FLOOR_OFFSET(T,F,O) typedef char T##_##F##_offset[((u32)&((T*)0)->F == O) ? 1 : -1]
FLOOR_OFFSET(FloorStackLayout, groupID, 0);
FLOOR_OFFSET(FloorStackLayout, floorID, 4);
FLOOR_OFFSET(FloorStackLayout, pushState, 8);
FLOOR_OFFSET(FloorStackLayout, pushFlag, 0x10);
FLOOR_OFFSET(FloorStackLayout, popFlag, 0x11);
FLOOR_OFFSET(FloorStackListLayout, current, 4);
FLOOR_OFFSET(FloorStackListLayout, capacity, 8);
FLOOR_OFFSET(FloorScriptLayout, mapping, 0x93c);
FLOOR_OFFSET(FloorModuleListLayout, vtable, 0x14);
FLOOR_OFFSET(FloorManagerLayout, task, 8);
FLOOR_OFFSET(FloorManagerLayout, nextTask, 0xc);
FLOOR_OFFSET(FloorManagerLayout, nextFloorID, 0x10);
FLOOR_OFFSET(FloorManagerLayout, changing, 0x14);
FLOOR_OFFSET(FloorManagerLayout, commonScriptType, 0x18);
FLOOR_OFFSET(FloorSaveHeader, maxFloorID, 0x18);
FLOOR_OFFSET(FloorWriteStreamLayout, ownsBuffer, 0x10);
FLOOR_OFFSET(FloorStackLayout, updateState, 0x220);
FLOOR_OFFSET(FloorStackLayout, type, 0x18);
FLOOR_OFFSET(FloorManagerLayout, commonScript, 0x1c);
FLOOR_OFFSET(FloorManagerLayout, maxSaveSize, 0x9dc);
FLOOR_OFFSET(FloorManagerLayout, maxSaveFloorID, 0x9e0);
FLOOR_OFFSET(FloorManagerLayout, vtable, 0x9e4);
typedef char FloorStackSize[(sizeof(FloorStackLayout)==0x224)?1:-1];
typedef char FloorManagerSize[(sizeof(FloorManagerLayout)==0x9e8)?1:-1];
typedef char FloorModuleListSize[(sizeof(FloorModuleListLayout)==0x18)?1:-1];
typedef char FloorWriteStreamSize[(sizeof(FloorWriteStreamLayout)==0x14)?1:-1];
#undef FLOOR_OFFSET
#endif
