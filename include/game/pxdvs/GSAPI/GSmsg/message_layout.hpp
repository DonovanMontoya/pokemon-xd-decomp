#ifndef MESSAGE_LAYOUT_HPP
#define MESSAGE_LAYOUT_HPP
#include <global.h>
#include <libc/stddef.h>
struct GStexture;
struct MsgDirectoryEntry { u32 identifier, textOffset; };
struct MsgBundle {
    u16 group;
    u8 reserved02, font;
    u16 count;
    s8 country[2];
    MsgBundle* next;
    MsgBundle* previous;
    MsgDirectoryEntry entries[1];
};
struct MSG_TASK_WORK {
    u8 state;
    u8 reserved01[2];
    u8 soundClass;
    f32 originX, originY, cursorX;
    u8 reserved10[8];
    s16 boxWidth, boxHeight;
    u32 messageID;
    u16 fontID;
    u8 glyphWidth, glyphHeight;
    u32 color;
    const u16 *textStart, *textBase, *textCursor;
    u8 reserved34[0xe];
    s8 glyphAdvance;
    u8 reserved43;
    u8 fontSelection;
    u8 reserved45[7];
    u8 alignment;
    u8 reserved4D[0x17];
    f32 scaleX, scaleY;
};
typedef MSG_TASK_WORK MsgTask;
struct MsgFontSlot { u16 identifier; u8 width, height; void* data; };
struct tagFONT_INFO { u16 code; u8 data[6]; };
struct MsgFontGroup {
    u16 count;
    u8 reserved02[6];
    MsgFontGroup* next;
    MsgFontGroup* previous;
    tagFONT_INFO entries[1];
};
struct MsgFontBlob { u16 identifier; u8 width, height; u32 nextOffset; MsgFontGroup group; };
struct MsgSystem {
    u16 taskCount, fontCount;
    MsgBundle* bundles;
    GStexture* textures[2];
    u32 reserved10;
    s16 textureX, textureY;
    u8 reserved18;
    s8 textureIndex;
    u8 reserved1A[2];
    MsgTask* tasks;
    MsgFontSlot* fonts;
    void* controls;
};
typedef char MsgBundleEntriesOffset[offsetof(MsgBundle, entries) == 0x10 ? 1 : -1];
typedef char MsgTaskFontOffset[offsetof(MsgTask, fontID) == 0x20 ? 1 : -1];
typedef char MsgTaskAlignmentOffset[offsetof(MsgTask, alignment) == 0x4c ? 1 : -1];
typedef char MsgTaskScaleOffset[offsetof(MsgTask, scaleX) == 0x64 ? 1 : -1];
typedef char MsgTaskSize[sizeof(MsgTask) == 0x6c ? 1 : -1];
typedef char MsgSystemSize[sizeof(MsgSystem) == 0x28 ? 1 : -1];
#endif
