#include <game/pxdvs/GSAPI/GSgfxM/vfPrivate.hpp>
#include <libc/string.h>
extern "C" {
static VFFormat _vfPredefFmt[9] = {
    {0x8001, 1, 0, 7, {
        {9, 1, 4, 0},
        {11, 1, 5, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 0, 7, {
        {9, 1, 3, 0},
        {11, 1, 5, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 0, 7, {
        {9, 0, 4, 0},
        {11, 1, 5, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 0, 7, {
        {9, 0, 3, 0},
        {11, 1, 5, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 0, 1, 7, {
        {9, 1, 4, 0},
        {13, 1, 4, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {13, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 1, 7, {
        {9, 1, 4, 0},
        {11, 1, 5, 0},
        {13, 1, 4, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {13, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 1, 7, {
        {9, 0, 4, 0},
        {11, 1, 5, 0},
        {13, 1, 4, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {13, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 1, 1, 7, {
        {9, 0, 3, 0},
        {11, 1, 5, 0},
        {13, 1, 4, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {11, 1},
        {13, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
    {0x8001, 0, 1, 7, {
        {9, 0, 3, 0},
        {13, 1, 0, 0},
        {255, 0, 0, 0},
    }, {
        {9, 1},
        {13, 1},
        {255, 0},
    }, {
        {0x0, 0, 0, 255, 0, 0},
    }},
};
static s32 _vfElemTable[23] = {0,1,2,3,4,5,6,7,8,9,10,25,11,12,13,14,15,16,17,18,19,20,255};
static VFFormat _vfLocal;
static u32 _vfAllocIndex;
VFLayer *GSgfxLayerGetLayerList();
void ResetVertexFormat__10GSgfxLayerFP7GSgfxVF(VFLayer *, VFFormat *);

static inline VFDescriptor *findDescriptor(VFFormat *format, s32 attribute) {
    s32 value;
    for (VFDescriptor *p = format->descriptors; (value = p->attribute) != 255; ++p)
        if (value == attribute) return p;
    return 0;
}
static inline VFAttribute *findFormat(VFFormat *format, s32 attribute) {
    s32 value;
    for (VFAttribute *p = format->formats; (value = p->attribute) != 255; ++p)
        if (value == attribute) return p;
    return 0;
}
static inline VFArray *findArray(VFFormat *format, s32 attribute) {
    s32 value;
    for (VFArray *p = format->arrays; (value = p->attribute) != 255; ++p)
        if (value == attribute) return p;
    return 0;
}
static inline u32 elementIndex(s32 attribute) {
    u32 index = 0;
    s32 value;
    for (s32 *p = _vfElemTable; (value = *p) != 255; ++p, ++index)
        if (attribute == value) return index;
    return 0;
}
static inline void recountElements(VFFormat *format) {
    format->colors = 0;
    format->textures = 0;
    format->flags &= ~8;
    for (u8 i = 0; i < 2; ++i) {
        if (!findFormat(format, i + 11)) break;
        ++format->colors;
    }
    for (u8 i = 0; i < 8; ++i) {
        if (!findFormat(format, i + 13)) break;
        ++format->textures;
    }
    for (u8 i = 0; i < 27; ++i) {
        if (format->descriptors[i].attribute == 255) break;
        s32 type = format->descriptors[i].type;
        if (type == 2 || type == 3) { format->flags |= 8; break; }
    }
    format->flags |= 6;
}
u8 GSgfxVFGetTextureCount(VFFormat *format) { return format->textures; }
u8 GSgfxVFGetColorCount(VFFormat *format) { return format->colors; }
void GSgfxVFSetArray(VFFormat *format, s32 attribute, s32 type, void *data, u8 stride, u32 size) {
    if (data != 0 || size == 0xffffffff || (data != 0 && size != 0)) {
        findDescriptor(format, attribute)->type = type;
        VFArray *array = findArray(format, attribute);
        if (!array) {
            u32 index = elementIndex(attribute);
            s32 *element = _vfElemTable + index;
            VFArray *insert = 0;
            while (index != 0) {
                s32 previous = *--element;
                --index;
                VFArray *found = findArray(format, previous);
                if (found) { insert = found + 1; break; }
            }
            if (!insert) insert = format->arrays;
            VFArray *end = insert;
            while (end->attribute != 255) ++end;
            for (; end >= insert; --end) {
                end[1].attribute = end->attribute;
                end[1].data = end->data;
                end[1].stride = end->stride;
            }
            array = insert;
        }
        array->flags = 0;
        array->attribute = attribute;
        array->data = data;
        array->stride = stride;
        array->size = size;
        if (((u32)array->data & 0xc0000000) == 0x80000000) array->flags |= 1;
        format->flags |= 12;
    }
}
void GSgfxVFRemoveElement(VFFormat *format, s32 attribute) {
    u8 changed = 0;
    VFDescriptor *descriptor = findDescriptor(format, attribute);
    if (descriptor) {
        VFDescriptor *next = descriptor + 1;
        while (descriptor->attribute != 255) {
            descriptor->attribute = next->attribute;
            descriptor->type = next->type;
            ++next; ++descriptor;
        }
        changed = 1;
    }
    if (attribute >= 9 || attribute < 0) {
        VFAttribute *entry = findFormat(format, attribute);
        if (entry) {
            VFAttribute *next = entry + 1;
            while (entry->attribute != 255) {
                entry->attribute = next->attribute;
                entry->count = next->count;
                entry->component = next->component;
                entry->fraction = next->fraction;
                ++next; ++entry;
            }
            changed = 1;
        }
        VFArray *array = findArray(format, attribute);
        if (array) {
            VFArray *next = array + 1;
            while (array->attribute != 255) {
                array->attribute = next->attribute;
                array->data = next->data;
                array->stride = next->stride;
                ++next; ++array;
            }
            changed = 1;
        }
    }
    if (changed == 1) recountElements(format);
}
void GSgfxVFSetElement(VFFormat *format, s32 attribute, s32 count, s32 component, u8 fraction) {
    GSgfxVFRemoveElement(format, attribute);
    u32 index = elementIndex(attribute);
    s32 *element = _vfElemTable + index;
    VFDescriptor *insert = 0;
    while (index != 0) {
        s32 previous = *--element;
        --index;
        VFDescriptor *found = findDescriptor(format, previous);
        if (found) { insert = found + 1; break; }
    }
    if (!insert) insert = format->descriptors;
    VFDescriptor *end = insert;
    while (end->attribute != 255) ++end;
    for (; end >= insert; --end) {
        end[1].attribute = end->attribute;
        end[1].type = end->type;
    }
    insert->attribute = attribute;
    insert->type = 1;
    if (attribute >= 9 || attribute < 0) {
        u32 index = elementIndex(attribute);
        s32 *element = _vfElemTable + index;
        VFAttribute *insert = 0;
        while (index != 0) {
            s32 previous = *--element;
            --index;
            VFAttribute *found = findFormat(format, previous);
            if (found) { insert = found + 1; break; }
        }
        if (!insert) insert = format->formats;
        VFAttribute *end = insert;
        while (end->attribute != 255) ++end;
        for (; end >= insert; --end) {
            end[1].attribute = end->attribute;
            end[1].count = end->count;
            end[1].component = end->component;
            end[1].fraction = end->fraction;
        }
        insert->attribute = attribute;
        insert->count = count;
        insert->component = component;
        insert->fraction = fraction;
    }
    recountElements(format);
}
u8 GSgfxVFHasElement(VFFormat *format, s32 attribute) {
    if (findDescriptor(format, attribute)) return 1;
    return 0;
}
void GSgfxVFFree(VFFormat *format) {
    if (format != &_vfLocal && (format->flags & 1)) {
        format->flags &= ~1;
        for (VFLayer *layer = GSgfxLayerGetLayerList(); layer; layer = layer->next)
            ResetVertexFormat__10GSgfxLayerFP7GSgfxVF(layer, format);
    }
}
u32 GSgfxVFIsUsed(VFFormat *format) { return format->flags & 1; }
VFFormat *GSgfxVFGetPredef(s32 index) { return &_vfPredefFmt[index]; }
void GSgfxVFCreate(VFFormat *format) {
    u32 index = _vfAllocIndex;
    u32 next = index + 1;
    if (next >= 8) next = 0;
    _vfAllocIndex = next;
    format->index = index;
    format->flags |= 1;
    for (u32 i = 0; (s32)i < 27; ++i) format->formats[i].attribute = 255;
    for (u32 i = 0; (s32)i < 27; ++i) format->descriptors[i].attribute = 255;
    for (u32 i = 0; (s32)i < 27; ++i) format->arrays[i].attribute = 255;
    format->flags |= 6;
}
void GSgfxVFInit(VFFormat *format) { memset(format, 0, sizeof(*format)); }
VFFormat *GSgfxVFBuildTemp(s32 positionCount, s32 positionComponent, u8 normal, s32 normalCount, u8 colors, s32 colorComponent, u8 textures, s32 textureCount, s32 textureComponent) {
    if (normalCount == 2 || colors > 2 || textures > 8 || colorComponent < 0 || textureComponent > 4) return 0;
    _vfLocal.formats[0].attribute = 9;
    _vfLocal.formats[0].count = positionCount;
    _vfLocal.formats[0].component = positionComponent;
    _vfLocal.formats[0].fraction = 0;
    _vfLocal.descriptors[0].attribute = 9;
    _vfLocal.descriptors[0].type = 1;
    VFAttribute *entry = _vfLocal.formats + 1;
    VFDescriptor *descriptor = _vfLocal.descriptors + 1;
    if (normal == 1) {
        switch (normalCount) {
        case 0: entry->count = 0; entry->attribute = 10; descriptor->attribute = 10; break;
        case 1: entry->count = 1; entry->attribute = 25; descriptor->attribute = 25; break;
        }
        entry->component = 4;
        entry->fraction = 0;
        ++entry;
        descriptor->type = 1;
        ++descriptor;
    }
    for (s32 i = 0; i < colors; ++i) {
        if (colorComponent >= 0 && colorComponent < 2) entry->count = 0;
        else if (colorComponent >= 2 && colorComponent < 6) entry->count = 1;
        entry->attribute = i + 11;
        entry->component = colorComponent;
        entry->fraction = 0;
        ++entry;
        descriptor->attribute = i + 11;
        descriptor->type = 1;
        ++descriptor;
    }
    for (s32 i = 0; i < textures; ++i) {
        entry->attribute = i + 13;
        entry->count = textureCount;
        entry->component = textureComponent;
        entry->fraction = 0;
        ++entry;
        descriptor->attribute = i + 13;
        descriptor->type = 1;
        ++descriptor;
    }
    entry->attribute = 255;
    descriptor->attribute = 255;
    _vfLocal.arrays[0].attribute = 255;
    _vfLocal.colors = colors;
    _vfLocal.textures = textures;
    _vfLocal.flags |= 6;
    return &_vfLocal;
}
void GSgfxVFInit__Fv(void) {
    _vfAllocIndex = 0;
    GSgfxVFCreate(&_vfLocal);
}
}
