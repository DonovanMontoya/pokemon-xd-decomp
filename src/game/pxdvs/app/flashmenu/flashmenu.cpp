// Needs extra cflags: -opt nopeephole
#include <game/pxdvs/app/flashmenu/flashmenuPrivate.hpp>

#include <libc/string.h>

extern "C" {
void GSmemFree(void *);
void flcalcUnitCxform(FLASHCXFORM *);
void flcalcUnitMatrix2(FLASHMATRIX *);
void GSprimSetBlendMode(s32);
void GSgfxLayerSetActive(s32);
void *GSgfxLayerFindByID(s32);
s32 flcalcBlend(s32, s32, f32);
s32 winSpriteGetLayerID(tagWINDOW_WORK *, tagSPRITE_WORK *);
u32 GSgfxVideoGetVsyncRate();
u32 timeGetLastFrameTime();
}
void GSprimSetup2DRender(GSgfxLayer *);
void operator delete(void *);
void operator delete[](void *);

#define FLASH_FREE(p) \
    if (p != 0) { \
        if (p != 0) { \
            GSmemFree(p); \
        } \
        p = 0; \
    }

struct FlashDataPointer {
    u8 type;
    u8 padding[3];
    void *data;
};

GStexture *FlashMenu::GetGStexture(long id) {
    for (s32 i = 0; i < 30; i++) {
        if (textures[i].id == id) {
            return textures[i].texture;
        }
    }
    return 0;
}

FlashMenu::~FlashMenu() {
}

FlashMenu::FlashMenu() {
    field10 = 0;
    field1E = 0;
    field20 = 0;
}

void FlashMenu::Release() {
    FlashHeader *hdr = header;
    FLASH_FREE(memory)
    u16 i;
    u16 j;
    for (i = 0; i < hdr->layerCount; i++) {
        if (layers[i].items != 0) {
            for (j = 0; j < hdr->itemCount; j++) {
                if (layers[i].items[j].extra != 0) {
                    delete[] (u8 *)layers[i].items[j].extra;
                    layers[i].items[j].extra = 0;
                }
            }
            delete[] (u8 *)layers[i].items;
            layers[i].items = 0;
        }
    }
    FLASH_FREE(layers)
    for (i = 0; i < hdr->itemCount; i++) {
        if (items[i].extra != 0) {
            delete[] (u8 *)items[i].extra;
            items[i].extra = 0;
        }
    }
    FLASH_FREE(items)
    FlashMenuLabel *label = labels;
    do {
        FlashMenuLabel *cur = label;
        if (label != 0) {
            label = label->next;
            delete cur;
        }
    } while (label != 0);
}

void FlashMenu::Draw(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    u32 frame;
    u8 rate;
    if (memory != 0) {
        s32 layerId = winSpriteGetLayerID(win, sprite);
        GSgfxLayerSetActive(layerId);
        GSgfxLayerFindByID(layerId);
        DrawSub((GSgfxLayerID)layerId, win, sprite);
        frame = playFrame;
        if (paused == 0) {
            rate = GSgfxVideoGetVsyncRate();
            u32 delta = timeGetLastFrameTime();
            if (delta >= 10) {
                delta = 1;
            }
            if (delta == 0) {
                fps = rate;
            } else {
                fps = (f32)rate / (f32)delta;
            }
            frame += delta;
            if (frame > endFrame) {
                if (loop != 0) {
                    frame = loopFrame;
                    FlashItem *item = items;
                    FlashHeader *hdr = header;
                    for (s32 i = 0; i < hdr->itemCount; i++, item++) {
                        item->depth = 0.0f;
                        item->field30 = 0;
                        item->field34 = 0;
                        flcalcUnitCxform(&item->cxform);
                    }
                } else {
                    frame = endFrame;
                }
            }
            playFrame = frame;
        }
        GSgfxLayerSetActive(7);
    }
}

void FlashMenu::InitDataPointer() {
    FlashDataPointer *pointer = (FlashDataPointer *)memory;
    FlashItem *item = items;
        s32 i = 0;
        FlashHeader *hdr = header;
        for (s32 n = 0; n < 200; n++, pointer++) {
            pointer->type = 0;
            pointer->data = 0;
        }
        for (; i < hdr->itemCount; i++, item++) {
            item->field30 = 0;
            item->field34 = 0;
            item->frame = 0;
            item->depth = 0.0f;
            item->flag = 0;
            flcalcUnitCxform(&item->cxform);
            flcalcUnitMatrix2(&item->matrix);
        }
        s32 l = 0;
        s32 off = 0;
        for (; l < hdr->layerCount; l++, off += 8) {
            s32 j = 0;
            s32 ioff = 0;
            for (; j < hdr->itemCount; j++, ioff += 0x40) {
                FlashLayer *layer = (FlashLayer *)((u8 *)layers + off);
                *(s16 *)((u8 *)layer->items + ioff) = 0;
                *(f32 *)((u8 *)layer->items + (ioff + 0x1C)) = 0.0f;
                *(s32 *)((u8 *)layer->items + (ioff + 0x30)) = 0;
                *(s32 *)((u8 *)layer->items + (ioff + 0x34)) = 0;
                *(u8 *)((u8 *)layer->items + (ioff + 0x3C)) = 0;
                flcalcUnitMatrix2((FLASHMATRIX *)((u8 *)layer->items + (ioff + 4)));
                flcalcUnitCxform((FLASHCXFORM *)((u8 *)layer->items + (ioff + 0x20)));
            }
        }
}

void FlashMenu::Update() {
    if (memory != 0) {
        FlashItem *item = items;
        s32 i = 0;
        FlashHeader *hdr = header;
        for (; i < hdr->itemCount; i++, item++) {
            item->field30 = 0;
            item->field34 = 0;
            item->frame = 0;
            item->depth = 0.0f;
            flcalcUnitCxform(&item->cxform);
            flcalcUnitMatrix2(&item->matrix);
        }
        s32 l = 0;
        s32 off = 0;
        for (; l < hdr->layerCount; l++, off += 8) {
            s32 j = 0;
            FlashLayer *layer = (FlashLayer *)((u8 *)layers + off);
            for (; j < hdr->itemCount; j++) {
                layer->items[j].frame = 0;
                layer->items[j].depth = 0.0f;
                layer->items[j].field30 = 0;
                layer->items[j].field34 = 0;
                layer->items[j].flag = 0;
                flcalcUnitMatrix2(&layer->items[j].matrix);
                flcalcUnitCxform(&layer->items[j].cxform);
            }
        }
        GSprimSetup2DRender(0);
        GSprimSetBlendMode(1);
        u32 target = playFrame;
        if (header->frameCount > target) {
            pos = start;
            frameStart = target;
            field14 = 0;
            u8 *tag = (u8 *)header + pos;
            for (;;) {
                if (ParseTag(*(u32 *)tag, *(u32 *)(tag + 4), 0, 0, 0)) {
                    break;
                }
                tag = (u8 *)header + pos;
            }
        }
        field20 = 0;
    }
}

void FlashMenu::ParsePlaceObject2(bool) {
    ParsePlaceObject2Sub((_PLACEOBJECT2 *)((u32)header + pos));
}

struct _DEFINETEXT {
    u8 reserved0[0x2C];
    u32 records;
};
struct TextGlyphs {
    u8 count;
    u8 pad[3];
    u32 data;
};
struct TextRecord {
    u8 type;
    u8 pad[3];
    u32 data;
    u32 next;
};

void FlashMenu::ParaseTextRecord(_DEFINETEXT *text) {
    TextRecord *rec;
    u32 v;
    if (header->relocated == 0 && field1E != 0) {
        v = (u32)text + text->records;
        text->records = v;
    } else {
        v = text->records;
    }
    rec = (TextRecord *)v;
    for (;;) {
        switch (rec->type) {
        case 0:
            break;
        case 1:
            if (header->relocated == 0 && field1E != 0) {
                rec->data = (u32)text + rec->data;
            }
            break;
        case 2: {
            TextGlyphs *glyphs;
            s32 i;
            if (header->relocated == 0 && field1E != 0) {
                glyphs = (TextGlyphs *)((u32)text + rec->data);
                rec->data = (u32)glyphs;
            } else {
                glyphs = (TextGlyphs *)rec->data;
            }
            if (header->relocated == 0 && field1E != 0) {
                glyphs->data = (u32)text + glyphs->data;
            }
            for (i = 0; i < glyphs->count; i++) {
            }
            break;
        }
        }
        u32 n = rec->next;
        if (n == 0) {
            return;
        }
        u32 w;
        if (header->relocated == 0 && field1E != 0) {
            w = (u32)text + n;
            rec->next = w;
        } else {
            // volatile forces the reload the original emitted instead of reusing 'n'.
            w = *(volatile u32 *)&rec->next;
        }
        rec = (TextRecord *)w;
    }
}

struct _DEFINEFONT2 {
    u16 id;
    u8 reserved2[2];
    u16 glyphCount;
    u8 reserved6[0xA];
    u32 field10;
    u32 field14;
    u8 reserved18[4];
    u32 shapes;
};

void FlashMenu::ParseDefineFont2Sub(_DEFINEFONT2 *font) {
    u16 count = font->glyphCount;
    s32 i;
    u32 *shape;
    ((FlashDataPointer *)memory)[font->id].type = 8;
    FlashDataPointer *entry = &((FlashDataPointer *)memory)[font->id];
    entry->data = font;
    if (count != 0) {
        if (font->field14 != 0) {
            for (i = 0; i < count; i++) {
            }
        }
        if (header->relocated == 0 && field1E != 0) {
            shape = (u32 *)((u32)font + font->shapes);
            font->shapes = (u32)shape;
        } else {
            shape = (u32 *)font->shapes;
        }
        for (i = 0; i < count; i++, shape++) {
            u32 v;
            if (header->relocated == 0 && field1E != 0) {
                v = (u32)font + *shape;
                *shape = v;
            } else {
                v = *shape;
            }
            ParseDefineShapeSub((_DEFINESHAPE *)v);
        }
        u32 f10 = font->field10;
        if (f10 != 0) {
            if (header->relocated == 0 && field1E != 0) {
                font->field10 = (u32)font + f10;
            }
            for (i = 0; i < count; i++) {
            }
        }
    }
}

u16 FlashMenu::GetFrameFromLabel(char *name) {
    if (labels != 0) {
        FlashMenuLabel *label = labels;
        for (;;) {
            if (label == 0) {
                break;
            }
            if (strcmp(name, label->name) == 0) {
                return label->frame;
            }
            label = label->next;
        }
    }
    return 0;
}

struct _SHAPERECORD {
    u8 type;
    u8 pad[3];
    void *data;
    _SHAPERECORD *next;
};
struct SRecordStyle {
    u8 flags;
    u8 pad[3];
    s32 x;
    s32 y;
};
struct SRecordLine {
    s32 pad;
    s32 x;
    s32 y;
};
struct SRecordCurve {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
};

void FlashMenu::BlendShapeRecord(_SHAPERECORD *dst, _SHAPERECORD *a, _SHAPERECORD *b, f32 t) {
    u8 more = 1;
    u8 hold = 0;
    do {
        switch (a->type) {
        case 0:
            more = 0;
            break;
        case 1: {
            SRecordStyle *sa = (SRecordStyle *)a->data;
            SRecordStyle *sb = (SRecordStyle *)b->data;
            SRecordStyle *sd = (SRecordStyle *)dst->data;
            if ((sa->flags & 1) != 0) {
                sd->x = flcalcBlend(sa->x, sb->x, t);
                sd->y = flcalcBlend(sa->y, sb->y, t);
                if (b->type != 1) {
                    hold = 1;
                }
            } else {
                hold = 1;
            }
            break;
        }
        case 2: {
            SRecordLine *sa = (SRecordLine *)a->data;
            SRecordLine *sb = (SRecordLine *)b->data;
            SRecordLine *sd = (SRecordLine *)dst->data;
            sd->x = flcalcBlend(sa->x, sb->x, t);
            sd->y = flcalcBlend(sa->y, sb->y, t);
            break;
        }
        case 3: {
            SRecordCurve *sa = (SRecordCurve *)a->data;
            SRecordCurve *sb = (SRecordCurve *)b->data;
            SRecordCurve *sd = (SRecordCurve *)dst->data;
            sd->a = flcalcBlend(sa->a, sb->a, t);
            sd->b = flcalcBlend(sa->b, sb->b, t);
            sd->c = flcalcBlend(sa->c, sb->c, t);
            sd->d = flcalcBlend(sa->d, sb->d, t);
            break;
        }
        }
        a = a->next;
        dst = dst->next;
        if (hold == 0) {
            b = b->next;
        }
        hold = 0;
        if (a->next == 0) {
            more = 0;
        }
    } while (more != 0);
}

u32 FlashMenu::GetPlayFrame() {
    return playFrame;
}

void FlashMenu::SetPlayFrame(unsigned long frame) {
    playFrame = frame;
}
