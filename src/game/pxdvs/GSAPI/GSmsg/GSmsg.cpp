extern "C" {
#include <libc/string.h>
}
#include <game/pxdvs/GSAPI/GSmsg/GSchar.hpp>
#include <game/pxdvs/GSAPI/GSmsg/message_layout.hpp>
#include <game/pxdvs/GSAPI/GStexture/GStexture.hpp>
#include <game/pxdvs/GSAPI/GSmemman/poolAlloc.hpp>
#pragma dont_inline on
static MsgSystem _MsgSysWork;
static MsgSystem* _pMw = &_MsgSysWork;
extern "C" s32 pokecoloGetLanguage();
extern "C" void GSlogWrite(const char*, ...);
s32 SJIStoGSchar(u16*, char*);
#include "sjis_tables.inc"
u32 _msgGetSize(const u16*);
u32 _msgGetLength(const u16* text) { return (_msgGetSize(text) + 1) / 2 - 1; }
extern "C" {
u16* GScharCat(u16* destination, const u16* source) {
    u32 length = _msgGetLength(destination);
    memcpy(destination + length, source, _msgGetSize(source));
    return destination;
}
u16* GScharLenCpy(u16* destination, const u16* source, s32 limit) {
    if (limit <= 0) return destination;
    s32 length = (_msgGetSize(source) + 1) / 2;
    if (length >= limit) length = limit - 1;
    memcpy(destination, source, length * 2);
    s32 i = length;
    while (i < limit) destination[i++] = 0;
    return destination;
}
u16* GScharCpy(u16* destination, const u16* source) {
    if (!destination) return 0;
    if (!source) destination[0] = 0;
    else memcpy(destination, source, _msgGetSize(source));
    return destination;
}
s32 GScharCmp(const u16* left, const u16* right) {
    u32 leftLength = _msgGetLength(left);
    u32 rightLength = _msgGetLength(right);
    if (leftLength == rightLength) {
        for (u32 i = 0; i < rightLength; ++i) {
            if (left[i] != right[i]) { if (left[i] > right[i]) return 1; else return -1; }
        }
        return 0;
    } else if (leftLength > rightLength) {
        for (u32 i = 0; i < rightLength; ++i) {
            if (left[i] != right[i]) { if (left[i] > right[i]) return 1; else return -1; }
        }
        return 1;
    } else {
        for (u32 i = 0; i < leftLength; ++i) {
            if (left[i] != right[i]) { if (left[i] > right[i]) return 1; else return -1; }
        }
        return -1;
    }
}
u32 GSmsgGetCharLength(const u16* text) { return _msgGetLength(text); }
s32 GScharMakeFromSJIS(u16* destination, char* source) { return SJIStoGSchar(destination, source); }
s32 GSmsgSetCtrlFunc(void* controls) { _pMw->controls = controls; return 0; }
void fn_80108D80() {}
s32 fn_8010B208(const MsgBundle* bundle) {
    if (!bundle) return 1;
    if (bundle->country[0] == 'J' && bundle->country[1] == 'P') return 2;
    if (bundle->country[0] == 'U' && bundle->country[1] == 'S') return 2;
    if (bundle->country[0] == 'U' && bundle->country[1] == 'K') return 2;
    if (bundle->country[0] == 'G' && bundle->country[1] == 'E') return 3;
    if (bundle->country[0] == 'F' && bundle->country[1] == 'R') return 4;
    if (bundle->country[0] == 'I' && bundle->country[1] == 'T') return 5;
    if (bundle->country[0] == 'S' && bundle->country[1] == 'P') return 6;
    return 1;
}
u16* GSmsgGetGSchar(u32 identifier) {
    if (!identifier) return 0;
    u32 textID = identifier & 0xfffff;
    MsgBundle* bundle = _pMw->bundles;
    while (bundle) {
        if (identifier < 60000) {
            s32 language = pokecoloGetLanguage();
            if (fn_8010B208(bundle) != language) goto nextBundle;
        }
        if (bundle->group == (identifier >> 20)) {
            u32 upper = bundle->count;
            MsgDirectoryEntry* directory = bundle->entries;
            u32 lower = 0;
            while (lower < upper) {
                u32 middle = (lower + upper) >> 1;
                u32 candidate = directory[middle].identifier;
                if (candidate == textID) return (u16*)((u8*)bundle + directory[middle].textOffset);
                if (candidate < textID) lower = middle + 1;
                else upper = middle;
            }
        }
nextBundle:
        bundle = bundle->next;
    }
    return 0;
}
MsgBundle* GSmsgOpen(MsgBundle* added) {
    MsgBundle* first = _pMw->bundles;
    if (!first) {
        _pMw->bundles = added;
        added->next = 0;
        added->previous = 0;
        return added;
    }
    MsgBundle* bundle = first;
    for (;;) {
        if (bundle == added) return 0;
        MsgBundle* next = bundle->next;
        if (!next) {
            bundle->next = added;
            added->next = 0;
            added->previous = bundle;
            return added;
        }
        bundle = next;
    }
}
void GSmsgSetFontInfo(MsgTask* task) {
    MsgFontSlot* font;
    u16 count = _pMw->fontCount;
    s32 offset = 0;
    for (s32 i = 0; i < count; ++i) {
        font = (MsgFontSlot*)((u8*)_pMw->fonts + offset);
        if (font->identifier == task->fontID) {
            task->glyphWidth = font->width;
            task->glyphHeight = font->height;
            u16 identifier = task->fontID;
            if (identifier == 0) {
                switch (pokecoloGetLanguage()) {
                case 1: task->glyphAdvance = 15; break;
                default: task->glyphAdvance = 11; break;
                }
                return;
            }
            if (identifier == 1 || identifier == 3) { task->glyphAdvance = 6; return; }
            task->glyphAdvance = (s8)(s32)(0.5 * task->glyphHeight + 1.0);
            return;
        }
        offset += sizeof(MsgFontSlot);
    }
}
u32 GSmsgGetRect(u32);
void GSmsgAdjustAlign(MsgTask* task) {
    if (task->boxWidth != 0) {
        s16 width = GSmsgGetRect(task->messageID) >> 16;
        u8 alignment = task->alignment;
        switch (alignment) {
        case 0: task->cursorX = task->originX; return;
        case 1: task->cursorX = task->originX + (task->boxWidth - width) / 2; return;
        case 2: task->cursorX = task->originX + task->boxWidth - width; break;
        }
    }
}

s32 GSmsgInit(u16 taskCount, u16 fontCount) {
    memset(&_MsgSysWork, 0, sizeof(MsgSystem));
    _pMw->tasks = (MsgTask*)GSmemAlloc(taskCount * sizeof(MsgTask));
    if (!_pMw->tasks) { GSlogWrite("GSmsgの初期化に失敗しました\n"); return -1; }
    _pMw->fonts = (MsgFontSlot*)GSmemAlloc(fontCount * sizeof(MsgFontSlot));
    if (!_pMw->fonts) { GSlogWrite("GSmsgの初期化に失敗しました\n"); return -1; }
    MsgTask* task;
    s32 i;
    for (i = 0; i < taskCount; ++i) {
        task = &_pMw->tasks[i];
        memset(task, 0, sizeof(MsgTask));
        task->scaleX = 1.0f;
        task->scaleY = 1.0f;
    }
    _pMw->taskCount = taskCount;
    for (i = 0; i < fontCount; ++i) {
        MsgFontSlot* font = &_pMw->fonts[i];
        font->identifier = 0xffff;
        font->data = 0;
    }
    _pMw->fontCount = fontCount;
    _pMw->textures[0] = GStextureCreate(512, 512, 64, 0, 0);
    _pMw->textures[1] = GStextureCreate(512, 512, 64, 0, 0);
    return 0;
}

struct GSgfxLayer;
GSgfxLayer* _TargetLayer;
GSgfxLayer* GSgfxLayerFindByID(u32);
u8 pauseIsPause();
s32 _msgMainSub__FP13MSG_TASK_WORKUcUlb(MsgTask*, u8, u32, bool);
s32 GSmsgMain(u32 layerID, s32 identifier, u32 steps, bool paused) {
    if (pauseIsPause() && (identifier >= 106 || identifier < 101)) paused = true;
    _TargetLayer = GSgfxLayerFindByID(layerID);
    if (!_TargetLayer) return -1;
    u8 index = 0;
    MsgTask* task;
    while (index < _pMw->taskCount) {
        task = _pMw->tasks + index;
        ++index;
        if (!task->state || task->messageID != (u32)identifier) continue;
        goto found;
    }
    task = 0;
found:
    if (!task) return -1;
    return _msgMainSub__FP13MSG_TASK_WORKUcUlb(task, task->fontSelection, steps, paused);
}
struct MsgSound { u16 category, soundID; };
extern MsgSound* message_se;
extern u32* message_se_number;
void GSsndStopNow(u32);
void GSmsgKill(u32 identifier) {
    u8 index = 0;
    MsgTask* task;
    while (index < _pMw->taskCount) {
        task = _pMw->tasks + index;
        ++index;
        if (!task->state || task->messageID != identifier) continue;
        goto found;
    }
    task = 0;
found:
    if (task) {
        u16 sound = 0;
        if (message_se) {
            MsgSound* entry = message_se;
            for (u32 i = 0; i < *message_se_number; ++i, ++entry) {
                if (task->soundClass == entry->category) {
                    sound = message_se[i].soundID;
                    break;
                }
            }
        }
        if (sound) GSsndStopNow(sound);
        task->state = 0;
    }
}

s32 GSmsgIsCheck(u32 identifier) {
    u8 index = 0;
    MsgTask* task;
    while (index < _pMw->taskCount) {
        task = _pMw->tasks + index;
        ++index;
        if (!task->state || task->messageID != identifier) continue;
        goto found;
    }
    task = 0;
found:
    if (task && task->state == 1) return 1;
    return 0;
}
s32 GSmsgClose(MsgBundle* target) {
    if (!_pMw->bundles) return -1;
    MsgBundle* bundle = _pMw->bundles;
    while (bundle) {
        if (bundle == target) {
            if (bundle->previous) bundle->previous->next = bundle->next;
            else _pMw->bundles = bundle->next;
            if (bundle->next) bundle->next->previous = bundle->previous;
            break;
        }
        bundle = bundle->next;
    }
    return 0;
}
void GSmsgDaemon() {
    GStextureUnlockImage(_pMw->textures[_pMw->textureIndex]);
    _pMw->textureX = 2;
    _pMw->textureY = 1;
    _pMw->textureIndex ^= 1;
}
s32 GSmsgPrintRect(u32, s32, s16, s16, s16, u32, u32);
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(u32 mode, s32 x, s16 y, u32 flags, u32 message) {
    return GSmsgPrintRect(mode, x, y, 0, 0, flags, message);
}
s32 GSmsgPrintRight(u32 mode, s32 x, s16 y, s16 width, s16 height, u32 flags, u32 message) {
    s16 textWidth = GSmsgGetRect(message) >> 16;
    x += width - textWidth;
    return GSmsgPrintRect(mode, x, y, width, height, flags, message);
}

}

s32 SJIStoGSchar(u16* destination, char* source) {
    u8* input = (u8*)source;
    s32 bytes = 0;
    if (!input) return 0;
    if (!destination) {
        while (*input) {
            if ((*input >= 0x81 && *input <= 0x9f) || (*input >= 0xe0 && *input <= 0xfc)) { input += 2; bytes += 2; }
            else { ++input; ++bytes; }
        }
    } else {
        u16 code;
        while ((code = *input) != 0) {
            s32 width;
            if ((code >= 0x81 && code <= 0x9f) || (code >= 0xe0 && code <= 0xfc)) {
                if (code >= 0x81 && code <= 0x9f) code = sjis_81xx[(code - 0x81) * 184 + input[1] - 0x40];
                else code = sjis_e0xx[(code - 0xe0) * 184 + input[1] - 0x40];
                width = 2;
            } else {
                if (code >= 0xa1 && code <= 0xdf) code = (u16)(code + 0xfec0);
                width = 1;
            }
            *destination = code;
            ++destination;
            input += width;
            bytes += width;
        }
        *destination = 0;
    }
    return bytes;
}
