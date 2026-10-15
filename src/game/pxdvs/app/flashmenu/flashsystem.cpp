#include <game/pxdvs/app/flashmenu/flashmenuPrivate.hpp>

struct FlashSystemSlot {
    FlashMenu *menu;
    u32 id;
};
static FlashSystemSlot _flashmenu[10];

extern "C" {
void GSthreadSwitch();
s32 Init__9FlashMenuFPvUl(FlashMenu *, void *, unsigned long);
}

static inline s32 FlashSystemFindIndex(u32 id) {
    for (s32 i = 0; i < 10; ++i) {
        if (_flashmenu[i].menu != 0 && _flashmenu[i].id == id) return i;
    }
    return -1;
}
static inline FlashSystemSlot *FlashSystemGetSlot(u32 id) {
    s32 index = FlashSystemFindIndex(id);
    if (index >= 0) {
        FlashSystemSlot *slot = &_flashmenu[index];
        if (slot->menu != 0) return slot;
        return 0;
    }
    return 0;
}
static inline FlashSystemSlot *FlashSystemGetEmptySlot() {
    for (s32 i = 0; i < 10; ++i) {
        if (_flashmenu[i].menu == 0) return &_flashmenu[i];
    }
    return 0;
}
extern "C" {
s32 FlashSystemSetPlayFrameLabel(u32 id, char *start, char *end);
void FlashSystemSetLoopFlag(u32 id, u8 loop);
s32 FlashSystemSetNowFrameLabel(u32 id, char *label);
u32 FlashSystemGetFrameFromLabel(u32 id, char *label);
u32 FlashSystemGetNowFrame(u32 id);
void FlashSystemPlayAndWait(u32 id, char *start, char *end);
s32 FlashSystemIsLastFrame(u32 id);
s32 FlashSystemSetNowFrame(u32 id, unsigned long frame);
u32 FlashSystemGetEndFrame(u32 id);
GStexture *FlashSystemGetGStexture(u32 id, long index);
void FlashSystemRelease(u32 id);
void FlashSystemDraw(u32 id, tagWINDOW_WORK *window, tagSPRITE_WORK *sprite);
void FlashSystemPlay(u32 id);
s32 FlashSystemInit(u32 id, void *data);
s32 FlashSystemInitAll();

s32 FlashSystemInitAll() {
    for (s32 i = 0; i < 10; ++i) {
        _flashmenu[i].menu = 0;
        _flashmenu[i].id = 0;
    }
    return 1;
}

s32 FlashSystemInit(u32 id, void *data) {
    FlashSystemSlot *slot = FlashSystemGetEmptySlot();
    if (slot != 0) {
        slot->menu = new FlashMenu;
        s32 result = Init__9FlashMenuFPvUl(slot->menu, data, id);
        slot->id = id;
        return result;
    }
    return 0;
}

void FlashSystemPlay(u32 id) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) slot->menu->Update();
}

void FlashSystemDraw(u32 id, tagWINDOW_WORK *window, tagSPRITE_WORK *sprite) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) slot->menu->Draw(window, sprite);
}

void FlashSystemRelease(u32 id) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) {
        slot->menu->Release();
        delete slot->menu;
        slot->menu = 0;
        slot->id = 0;
    }
}

GStexture *FlashSystemGetGStexture(u32 id, long index) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) return slot->menu->GetGStexture(index);
    return 0;
}

u32 FlashSystemGetNowFrame(u32 id) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) return slot->menu->GetPlayFrame();
    return 0;
}

u32 FlashSystemGetEndFrame(u32 id) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) return slot->menu->endFrame;
    return 0;
}

s32 FlashSystemSetNowFrame(u32 id, unsigned long frame) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) slot->menu->SetPlayFrame(frame);
    return 0;
}

void FlashSystemSetLoopFlag(u32 id, u8 loop) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) slot->menu->loop = loop;
}

s32 FlashSystemSetPlayFrameLabel(u32 id, char *start, char *end) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) {
        slot->menu->loopFrame = slot->menu->GetFrameFromLabel(start);
        slot->menu->endFrame = slot->menu->GetFrameFromLabel(end);
    }
    return 1;
}

s32 FlashSystemSetNowFrameLabel(u32 id, char *label) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) slot->menu->SetPlayFrame(slot->menu->GetFrameFromLabel(label));
    return 0;
}

u32 FlashSystemGetFrameFromLabel(u32 id, char *label) {
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    if (slot != 0) return slot->menu->GetFrameFromLabel(label);
    return 0;
}

s32 FlashSystemIsLastFrame(u32 id) {
    s32 result = 0;
    FlashSystemSlot *slot = FlashSystemGetSlot(id);
    u8 loop = slot != 0 ? slot->menu->loop : 0;
    if (loop == 0) {
        u32 now = FlashSystemGetNowFrame(id);
        slot = FlashSystemGetSlot(id);
        u32 end = slot != 0 ? slot->menu->endFrame : 0;
        if (now >= end) result = 1;
    }
    return result;
}

void FlashSystemPlayAndWait(u32 id, char *start, char *end) {
    FlashSystemSetPlayFrameLabel(id, start, end);
    FlashSystemSetLoopFlag(id, 0);
    FlashSystemSetNowFrameLabel(id, start);
    u32 endFrame = FlashSystemGetFrameFromLabel(id, end);
    u32 frame;
    do {
        frame = FlashSystemGetNowFrame(id);
        GSthreadSwitch();
    } while (frame < endFrame);
}
}
