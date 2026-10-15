#include <game/pxdvs/GSAPI/GSgfxM/dlPrivate.hpp>
#include <libc/string.h>
extern "C" {
void *GSmemAllocAlign(u32, u32);
void GSmemShrink(void *, u32);
void GSmemFree(void *);
void GSlogWrite(const char *, ...);
static u16 _dlCalculateStride__FP7GSgfxVF(DLVertexFormat *);
static u8 *_dlParseSurface__F13GSgfxPrimTypeP16_HSD_VtxDescListPUcUsP22GSgfxParseCallbackListPv(s32, DLInputDescriptor *, u8 *, u16, DLParseCallbacks *, void *);
static u8 *_dlParseVertex__FP16_HSD_VtxDescListPUcP22GSgfxParseCallbackListPv(DLInputDescriptor *, u8 *, DLParseCallbacks *, void *);
static s32 _dlPrimType = 0x90;
static DLDisplayList *_dlCurPtr;
u8 gsgfx_dl_buildingDList;

void GSgfxParseDisplayList(DLInputDescriptor *descriptors, u8 *data, u32 size, DLParseCallbacks *callbacks, void *argument) {
    s32 primitive;
    u8 *end = data + size;
    while (data < end) {
        s32 command = *data++ & 0xf8;
        switch (command) {
        case 0x98: case 0xb0: case 0xb8: case 0xa8: case 0xa0: case 0x80: case 0x90: {
            u16 count = *reinterpret_cast<u16 *>(data);
            data += 2;
            switch (command) {
            case 0xb8: primitive = 0xb8; break;
            case 0xa8: primitive = 0xa8; break;
            case 0xb0: primitive = 0xb0; break;
            case 0x90: primitive = 0x90; break;
            case 0x98: primitive = 0x98; break;
            case 0xa0: primitive = 0xa0; break;
            case 0x80: primitive = 0x80; break;
            }
            data = _dlParseSurface__F13GSgfxPrimTypeP16_HSD_VtxDescListPUcUsP22GSgfxParseCallbackListPv(primitive, descriptors, data, count, callbacks, argument);
            break;
        }
        case 0x61: data += 4; break;
        case 0: break;
        default: return;
        }
    }
}
void GSgfxDLEndSurface(void) {}
void GSgfxDLBeginSurface(u16 count) {
    u32 primitive = _dlPrimType;
    u32 index = _dlCurPtr->format->index;
    GXWGFifo.u8 = primitive | index;
    GXWGFifo.u16 = count;
}
void GSgfxDLPrimitiveType(s32 primitive) { _dlPrimType = primitive; }
void GSgfxDLEnd(void) {
    u32 size = GXEndDisplayList();
    GSmemShrink(_dlCurPtr->data, size);
    _dlCurPtr->size = size;
    gsgfx_dl_buildingDList = 0;
    _dlCurPtr = 0;
}
void GSgfxDLBegin(DLDisplayList *list, DLVertexFormat *format, u16 surfaces, u16 vertices) {
    list->stride = _dlCalculateStride__FP7GSgfxVF(format);
    u32 surfaceBytes = surfaces << 5;
    u32 vertexBytes = vertices * list->stride;
    vertexBytes += 0x5f;
    list->size = (surfaceBytes + vertexBytes) & ~31;
    list->data = static_cast<u8 *>(GSmemAllocAlign(list->size, 32));
    memset(list->data, 0, list->size);
    DCFlushRange(list->data, list->size);
    list->format = format;
    GXBeginDisplayList(list->data, list->size);
    GXResetWriteGatherPipe();
    list->flags |= 1;
    gsgfx_dl_buildingDList = 1;
    _dlCurPtr = list;
}
void GSgfxDLFree(DLDisplayList *list) {
    if (list->flags & 1) {
        GSmemFree(list->data);
        list->data = 0;
        list->flags &= ~1;
    }
}
void GSgfxDLCreate(DLDisplayList *list, s32 primitive, DLVertexFormat *format, u16 count) {
    list->stride = _dlCalculateStride__FP7GSgfxVF(format);
    list->size = (count * list->stride + 0x22) & ~31;
    list->data = static_cast<u8 *>(GSmemAllocAlign(list->size, 32));
    if (list->data == 0) {
        GSlogWrite("GSgfxDL Warning: unable to allocate display list memory of (%d) bytes\n", list->size);
        list->size = 0;
        return;
    }
    memset(list->data, 0, list->size);
    list->format = format;
    u8 *data = list->data;
    switch (primitive) {
    case 0xb8: *data = 0xb8; break;
    case 0xa8: *data = 0xa8; break;
    case 0xb0: *data = 0xb0; break;
    case 0x90: *data = 0x90; break;
    case 0x98: *data = 0x98; break;
    case 0xa0: *data = 0xa0; break;
    case 0x80: *data = 0x80; break;
    }
    *data |= format->index;
    *reinterpret_cast<u16 *>(data + 1) = count;
    list->flags |= 7;
}
static u8 *_dlParseSurface__F13GSgfxPrimTypeP16_HSD_VtxDescListPUcUsP22GSgfxParseCallbackListPv(s32 primitive, DLInputDescriptor *descriptors, u8 *data, u16 count, DLParseCallbacks *callbacks, void *argument) {
    u32 attributes = 0;
    s32 attribute;
    for (DLInputDescriptor *descriptor = descriptors; (attribute = descriptor->attribute) != 255; ++descriptor) {
        switch (attribute) {
        case 0: attributes |= 1; break;
        case 1: attributes |= 0x40; break;
        case 9: attributes |= 2; break;
        case 10: attributes |= 4; break;
        case 25: attributes |= 8; break;
        case 11: attributes |= 0x10; break;
        case 12: attributes |= 0x20; break;
        case 13: attributes |= 0x80; break;
        case 14: attributes |= 0x100; break;
        case 15: attributes |= 0x200; break;
        case 16: attributes |= 0x400; break;
        case 17: attributes |= 0x800; break;
        case 18: attributes |= 0x1000; break;
        case 19: attributes |= 0x2000; break;
        case 20: attributes |= 0x4000; break;
        }
    }
    if (callbacks->beginSurface) callbacks->beginSurface(primitive, count, attributes, argument);
    while (count--) {
        if (callbacks->beginVertex) callbacks->beginVertex(argument);
        for (DLInputDescriptor *descriptor = descriptors; descriptor->attribute != 255; ++descriptor)
            data = _dlParseVertex__FP16_HSD_VtxDescListPUcP22GSgfxParseCallbackListPv(descriptor, data, callbacks, argument);
        if (callbacks->endVertex) callbacks->endVertex(argument);
    }
    if (callbacks->endSurface) callbacks->endSurface(argument);
    return data;
}
static u8 *_dlParseVertex__FP16_HSD_VtxDescListPUcP22GSgfxParseCallbackListPv(DLInputDescriptor *descriptor, u8 *data, DLParseCallbacks *callbacks, void *argument) {
    u8 *next = data;
    u32 attributeFlag;
    u32 componentFlag;
    u32 countFlag;
    s32 attribute = descriptor->attribute;
    if (attribute < 21) {
        if (attribute < 9) {
            if (attribute >= 0) {
                componentFlag = 0x10000;
                countFlag = 0x10000000;
                switch (attribute) {
                case 0: attributeFlag = 1; break;
                case 1: attributeFlag = 0x40; break;
                case 2: attributeFlag = 0x40; break;
                case 3: attributeFlag = 0x40; break;
                case 4: attributeFlag = 0x40; break;
                case 5: attributeFlag = 0x40; break;
                case 6: attributeFlag = 0x40; break;
                case 7: attributeFlag = 0x40; break;
                case 8: attributeFlag = 0x40; break;

                }
                ++next;
            } else goto emit;
            goto emit;
        }
    } else if (attribute != 25) goto emit;
    if (attribute == 11 || attribute == 12) {
        u32 colorFlag = 0x20;
        if (attribute == 11) colorFlag = 0x10;
        attributeFlag = colorFlag;
        countFlag = 0x10000000;
        switch (descriptor->component) {
        case 0: componentFlag = 0x200000; break;
        case 1: componentFlag = 0x400000; break;
        case 2: componentFlag = 0x800000; break;
        case 3: componentFlag = 0x1000000; break;
        case 4: componentFlag = 0x2000000; break;
        case 5: componentFlag = 0x4000000; break;
        }
    } else {
        switch (descriptor->component) {
        case 0: componentFlag = 0x10000; break;
        case 1: componentFlag = 0x20000; break;
        case 2: componentFlag = 0x40000; break;
        case 3: componentFlag = 0x80000; break;
        case 4: componentFlag = 0x100000; break;
        }
        switch (attribute) {
        case 9:
            attributeFlag = 2;
            if (descriptor->count == 0) countFlag = 0x20000000;
            else countFlag = 0x40000000;
            break;
        case 10:
            attributeFlag = 4;
            if (descriptor->count == 0) countFlag = 0x40000000;
            break;
        case 25:
            attributeFlag = 8;
            if (descriptor->count == 1) countFlag = 0x40000000;
            break;
        case 13: attributeFlag = 0x80; goto textureCount;
        case 14: attributeFlag = 0x100; goto textureCount;
        case 15: attributeFlag = 0x200; goto textureCount;
        case 16: attributeFlag = 0x400; goto textureCount;
        case 17: attributeFlag = 0x800; goto textureCount;
        case 18: attributeFlag = 0x1000; goto textureCount;
        case 19: attributeFlag = 0x2000; goto textureCount;
        case 20: attributeFlag = 0x4000;
        default:
textureCount:
            if (descriptor->count == 0) countFlag = 0x10000000;
            else countFlag = 0x20000000;
            break;
        }
    }
    if (descriptor->type == 1) {
        u32 bytes;
        switch (componentFlag) {
        case 0x10000: case 0x20000: bytes = 1; break;
        case 0x200000: case 0x1000000: case 0x40000: case 0x80000: bytes = 2; break;
        case 0x2000000: case 0x400000: bytes = 3; break;
        case 0x4000000: case 0x800000: case 0x100000: bytes = 4; break;
        }
        switch (countFlag) {
        case 0x10000000: break;
        case 0x20000000: bytes *= 2; break;
        case 0x40000000: bytes *= 3; break;
        default: bytes *= 4; break;
        }
        next += bytes;
    } else {
        u16 index;
        if (descriptor->type == 2) index = *next++;
        else { index = *reinterpret_cast<u16 *>(next); next += 2; }
        data = descriptor->data + index * descriptor->stride;
    }
emit:
    if (callbacks->attribute) callbacks->attribute(countFlag | (attributeFlag | componentFlag), data, argument);
    return next;
}
static u16 _dlCalculateStride__FP7GSgfxVF(DLVertexFormat *format) {
    DLAttributeFormat *attribute = format->formats;
    DLVertexDescriptor *descriptor = format->descriptors;
    u16 stride = 0;
    u16 components;
    for (; descriptor->attribute != 255; ++attribute, ++descriptor) {
        switch (descriptor->type) {
        case 1:
            switch (attribute->attribute) {
            case 0: ++stride; break;
            case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
            case 21: case 22: case 23: case 24: case 25: break;
            case 9:
                if (attribute->count == 0) components = 2;
                else if (attribute->count == 1) components = 3;
                switch (attribute->component) {
                case 0: case 1: stride += components; break;
                case 2: case 3: stride += components * 2; break;
                case 4: stride += components * 4; break;
                }
                break;
            case 10:
                if (attribute->count == 0) components = 3;
                switch (attribute->component) {
                case 1: stride += components; break;
                case 3: stride += components * 2; break;
                case 4: stride += components * 4; break;
                }
                break;
            case 11: case 12:
                switch (attribute->component) {
                case 0: case 3: stride += 2; break;
                case 1: case 4: stride += 3; break;
                case 2: case 5: stride += 4; break;
                }
                break;
            case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20:
                if (attribute->count == 0) components = 1;
                else if (attribute->count == 1) components = 2;
                switch (attribute->component) {
                case 0: case 1: stride += components; break;
                case 2: case 3: stride += components * 2; break;
                case 4: stride += components * 4; break;
                }
                break;
            }
            break;
        case 2: ++stride; break;
        case 3: stride += 2; break;
        }
    }
    return stride;
}
}
