// Needs extra cflags: -inline noauto,deferred -opt nopeephole
// Functions are written in reverse object order because "deferred" emits them reversed;
// this also reproduces the function-local static suffix numbering ($NNNN) once all bodies exist.
#include <game/pxdvs/app/menu/winSpritePrivate.hpp>
#include <libc/string.h>
#include <game/pxdvs/app/menu/menuOffScreenPrivate.hpp>

extern "C" {
void *GSmemAlloc(s32);
void GSlogWrite(const char *, ...);
MenuData *menuDataBiosGetPtr(s32);
MENU_ITEM_dd_ *menuItemBiosGetPtr(s32, s16);
u32 menuSeqBiosGetPtr(u32);
s32 menuBiosGetCursorSize();
s32 dbgMenuGetLayerID();
s32 floorGetMenuLayerID();
tagWINDOW_WORK *windowSearchID(s32);
}

static void _winSeqMoveSprite(s32 id, tagSPRITE_WORK *sprite);
static void _winSeqMoveMenu(tagWINDOW_WORK *win);
static void _winSeqMoveSub(SEQ_WORK_COMMON *common, tagSEQ_WORK *seq);

static u8 *_spriteWork;
extern "C" void winSetSequence(void *work, u16 seq);

extern "C" {
s32 winSpriteGetLayerID(tagWINDOW_WORK *win, WindowSprite *winSprite) {
    tagSPRITE_WORK *sprite = (tagSPRITE_WORK *)winSprite;
    MenuData *md = menuDataBiosGetPtr(win->menuID);
    if (win->layerID == dbgMenuGetLayerID()) {
        return dbgMenuGetLayerID();
    }
    if ((u32)((md->flags >> 5) & 7) == 3) {
        s32 layer = dbgMenuGetLayerID();
        if (win->layerID != layer) {
            win->layerID = layer;
        }
        return layer;
    }
    if (sprite->drawType == 0) {
        return 7;
    }
    return floorGetMenuLayerID();
}
}

extern "C" {
void winSpriteInit() {
    _spriteWork = (u8 *)GSmemAlloc(0xEA60);
    if (_spriteWork != 0) {
        memset(_spriteWork, 0, 0xEA60);
    }
}
}

extern "C" {
tagSPRITE_WORK *winSpriteAdd(tagSPRITE_WORK **list) {
    if (list == 0) {
        return 0;
    }
    tagSPRITE_WORK *s = (tagSPRITE_WORK *)_spriteWork;
    for (s32 i = 0; i < 500; i++, s++) {
        if (s->type == 0) {
            memset(s, 0, 0x78);
            s->type = 7;
            s->scaleX = 1.0f;
            s->scaleY = 1.0f;
            s->color = -1;
            tagSPRITE_WORK **p = list;
            while (*p != 0) {
                p = &(*p)->next;
            }
            *p = s;
            return s;
        }
    }
    GSlogWrite("Error!! winSpriteAdd() [\x83\x58\x83\x76\x83\x89\x83\x43\x83\x67\x83\x8f\x81\x5b\x83\x4e\x95\x73\x91\xab]\n\0");
    return 0;
}
}

extern "C" {
void winSpriteRelease(tagSPRITE_WORK **list) {
    if (list != 0) {
        tagSPRITE_WORK **p = list;
        while (*p != 0) {
            (*p)->type = 0;
            p = (tagSPRITE_WORK **)*p;
        }
        *list = 0;
    }
}
}

extern "C" {
void winSpriteSetDisp(tagSPRITE_WORK *sprite, u8 disp) {
    if (sprite != 0) {
        if (disp != 0) {
            sprite->type |= 2;
            return;
        }
        sprite->type &= ~2;
    }
}
}

extern "C" {
s32 winSpriteGetDisp(tagSPRITE_WORK *sprite) {
    if (sprite == 0) {
        return 0;
    }
    return (sprite->type & 2) != 0;
}
}

static void _spriteSetAlphaMode(GSgfxLayer *layer, u8 mode) {
    switch (mode) {
    case 0:
        layer->alphaCompare0 = 7;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 0;
        layer->alphaCompare1 = 7;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 1;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 4;
        layer->blendDestination = 5;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    case 1:
        layer->alphaCompare0 = 4;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 1;
        layer->alphaCompare1 = 0;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 0;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 2;
        layer->blendDestination = 0;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    case 2:
        layer->alphaCompare0 = 7;
        layer->alphaReference0 = 0;
        layer->alphaCombine = 0;
        layer->alphaCompare1 = 7;
        layer->alphaReference1 = 0;
        layer->alphaDisabled = 1;
        layer->pixelDirty |= 0x10;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 0x10;
        layer->savedDirty |= 0x40;
        if (layer->blendIndex != 1) {
            layer->blendIndex = 1;
            layer->currentBlend = &layer->blendRecords[layer->blendIndex];
        }
        layer->blendMode = 1;
        layer->blendSource = 4;
        layer->blendDestination = 1;
        layer->logicOperation = 5;
        layer->pixelDirty |= 1;
        layer->dirty |= 0x40;
        layer->savedPixelDirty |= 1;
        layer->savedDirty |= 0x40;
        return;
    }
}

extern "C" {
void winAnimeCursor(tagWINDOW_WORK *win, tagSPRITE_WORK *sprite) {
    menuBiosGetCursorSize();
    if (*(s16 *)((u8 *)win + 0xA2) != win->cursorIndex) {
        winSetSequence(sprite->sequence, 0x141);
    }
    if (win->state == 3) {
        winSetSequence(sprite->sequence, 0);
    }
}
}

extern "C" {
void winSetSequence(void *work, u16 seq) {
    if (seq == 0) {
        *(u32 *)work = 0;
        *(u16 *)((u8 *)work + 4) = 0;
        return;
    }
    memset(work, 0, 0x3C);
    *(u32 *)work = menuSeqBiosGetPtr(seq);
}
}

extern "C" {
void winSeqSetMenu(s32 id, u16 seq) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win != 0) {
        winSetSequence(win->reserved2C, seq);
        _winSeqMoveMenu(win);
    }
}
}

extern "C" {
s32 winSeqIsCheck(s32 id, u16 seq) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win != 0 && *(u32 *)win->reserved2C == menuSeqBiosGetPtr(seq)) {
        return 1;
    }
    return 0;
}
}

// TODO: sequence interpreter (tween/animation step) not recovered yet.
static void _winSeqMoveSub(SEQ_WORK_COMMON *common, tagSEQ_WORK *seq) {
}

static void _winSeqMoveMenu(tagWINDOW_WORK *win) {
    static SEQ_WORK_COMMON seqTemp;
    seqTemp.x = win->x;
    seqTemp.y = win->y;
    seqTemp.color = *(s32 *)&win->frame;
    seqTemp.type = win->flags;
    seqTemp.baseX = menuDataBiosGetPtr(win->menuID)->x;
    seqTemp.baseY = menuDataBiosGetPtr(win->menuID)->y;
    _winSeqMoveSub(&seqTemp, (tagSEQ_WORK *)win->reserved2C);
    win->x = seqTemp.x;
    win->y = seqTemp.y;
    *(s32 *)&win->frame = seqTemp.color;
    win->flags = seqTemp.type;
}

static void _winSeqMoveSprite(s32 id, tagSPRITE_WORK *sprite) {
    static SEQ_WORK_COMMON seqTemp;
    seqTemp.x = sprite->x;
    seqTemp.y = sprite->y;
    seqTemp.color = sprite->color;
    seqTemp.scaleX = sprite->scaleX;
    seqTemp.scaleY = sprite->scaleY;
    seqTemp.type = sprite->type;
    seqTemp.resource = sprite->resource;
    seqTemp.sourceX = sprite->sourceX;
    seqTemp.sourceY = sprite->sourceY;
    seqTemp.sourceWidth = sprite->sourceWidth;
    seqTemp.sourceHeight = sprite->sourceHeight;
    seqTemp.baseX = menuItemBiosGetPtr(id, sprite->itemID)->x;
    seqTemp.baseY = menuItemBiosGetPtr(id, sprite->itemID)->y;
    _winSeqMoveSub(&seqTemp, (tagSEQ_WORK *)sprite->sequence);
    sprite->x = seqTemp.x;
    sprite->y = seqTemp.y;
    sprite->color = seqTemp.color;
    sprite->scaleX = seqTemp.scaleX;
    sprite->scaleY = seqTemp.scaleY;
    sprite->type = seqTemp.type;
    sprite->resource = seqTemp.resource;
    sprite->sourceX = seqTemp.sourceX;
    sprite->sourceY = seqTemp.sourceY;
    sprite->sourceWidth = seqTemp.sourceWidth;
    sprite->sourceHeight = seqTemp.sourceHeight;
}

extern "C" {
void winSeqMoveMenu(tagWINDOW_WORK *win) {
    _winSeqMoveMenu(win);
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->items; s != 0; s = s->next) {
        _winSeqMoveSprite(win->menuID, s);
    }
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->cursor; s != 0; s = s->next) {
        _winSeqMoveSprite(win->menuID, s);
    }
}
}

extern "C" {
s32 winSeqCheckMove(s32 id) {
    tagWINDOW_WORK *win = windowSearchID(id);
    if (win == 0) {
        return 0;
    }
    if (*(u32 *)win->reserved2C != 0) {
        return 1;
    }
    for (tagSPRITE_WORK *s = (tagSPRITE_WORK *)win->items; s != 0; s = s->next) {
        if (*(u32 *)s->sequence != 0 && s->sequence[0x3A] == 0) {
            return 1;
        }
    }
    return 0;
}
}
