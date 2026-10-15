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
    for (u16 i = 0; i < hdr->layerCount; i++) {
        if (layers[i].items != 0) {
            for (u16 j = 0; j < hdr->itemCount; j++) {
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
    for (u16 i = 0; i < hdr->itemCount; i++) {
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

struct FlashDataPointer {
    u8 type;
    u8 padding[3];
    void *data;
};

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

u32 FlashMenu::GetPlayFrame() {
    return playFrame;
}

void FlashMenu::SetPlayFrame(unsigned long frame) {
    playFrame = frame;
}
