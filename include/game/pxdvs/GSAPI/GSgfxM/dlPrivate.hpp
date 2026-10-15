#ifndef GAME_PXDVS_GSAPI_GSGFXM_DL_PRIVATE_HPP
#define GAME_PXDVS_GSAPI_GSGFXM_DL_PRIVATE_HPP
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <libc/stddef.h>
struct DLAttributeFormat { s32 attribute, count, component; u8 fraction; u8 padding[3]; };
struct DLVertexDescriptor { s32 attribute, type; };
struct DLVertexFormat { u32 flags, index; DLAttributeFormat formats[27]; DLVertexDescriptor descriptors[27]; };
struct DLDisplayList { u16 flags, stride; u8 *data; u32 size; DLVertexFormat *format; };
struct DLInputDescriptor { s32 attribute, type, count, component; u8 fraction, padding; u16 stride; u8 *data; };
struct DLParseCallbacks {
    void (*beginSurface)(s32, u16, u32, void *);
    void (*beginVertex)(void *);
    void (*attribute)(u32, const void *, void *);
    void (*endVertex)(void *);
    void (*endSurface)(void *);
};
typedef char DLDisplayListSizeCheck[sizeof(DLDisplayList) == 0x10 ? 1 : -1];
typedef char DLInputDescriptorSizeCheck[sizeof(DLInputDescriptor) == 0x18 ? 1 : -1];
typedef char DLVertexFormatDescriptorsOffsetCheck[offsetof(DLVertexFormat, descriptors) == 0x1b8 ? 1 : -1];
#endif
