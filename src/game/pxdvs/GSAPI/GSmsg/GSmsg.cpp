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
#include "gba_tables.inc"
extern "C" s32 pokecoloGetCountryCode();
u32 _msgGetSize(const u16*);
u32 _msgGetLength(const u16* text) { return (_msgGetSize(text) + 1) / 2 - 1; }
tagFONT_INFO* _msgGetCodeInfo(MSG_TASK_WORK* task, u16 code, tagFONT_INFO** group) {
    s32 i;
    u16 count = _pMw->fontCount;
    s32 offset = 0;
    MsgFontSlot* slot;
    for (i = 0; i < count; ++i) {
        slot = (MsgFontSlot*)((u8*)_pMw->fonts + offset);
        if (slot->identifier == task->fontID) break;
        offset += sizeof(MsgFontSlot);
    }
    if (i == count) return 0;
    MsgFontGroup* node = (MsgFontGroup*)slot->data;
    while (node) {
        u32 upper = node->count;
        u32 lower = 0;
        while (lower < upper) {
            u32 middle = (lower + upper) >> 1;
            tagFONT_INFO* entry = &node->entries[middle];
            if (entry->code == code) {
                if (group) *group = (tagFONT_INFO*)node;
                return entry;
            }
            if (entry->code < code) lower = middle + 1;
            else upper = middle;
        }
        if (lower < upper) return 0;
        node = node->next;
    }
    return 0;
}
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
s32 GSmsgSetCtrlFunc(void* controls) { _pMw->controls = (MsgControl*)controls; return 0; }
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
#pragma dont_inline off
u16* GSmsgGetGSchar(u32 identifier) {
    if (!identifier) return 0;
    u32 group = identifier >> 20;
    u32 textID = identifier & 0xfffff;
    MsgBundle* bundle = _pMw->bundles;
    while (bundle) {
        if (identifier < 60000) {
            s32 language = pokecoloGetLanguage();
            s32 bundleLanguage = fn_8010B208(bundle);
            if (bundleLanguage != language) goto nextBundle;
        }
        if (bundle->group == group) {
            u32 middle;
            u32 upper = bundle->count;
            u32 lower = 0;
            MsgDirectoryEntry* directory = bundle->entries;
            u32 candidate;
            while (lower < upper) {
                middle = (lower + upper) >> 1;
                candidate = directory[middle].identifier;
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
u32 GSmsgGetLength(u32 identifier) {
    if (!identifier) return 0;
    return _msgGetLength(GSmsgGetGSchar(identifier));
}
#pragma dont_inline on
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
        continue;
    }
    return added;
}
#pragma dont_inline off
void GSmsgSetFontInfo(MsgTask* task) {
    MsgSystem* system = _pMw;
    MsgFontSlot* font;
    for (s32 i = 0; i < system->fontCount; ++i) {
        font = &system->fonts[i];
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
    }
}
#pragma dont_inline on
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

void* GSmsgFontOpen(void* font) {
    MsgFontBlob* blob = (MsgFontBlob*)font;
    MsgFontSlot* slot;
    s32 i;
    u16 count;
    u16 identifier;
    s32 offset;
    for (;;) {
        identifier = blob->identifier;
        if (identifier == 0xffff) return 0;
        i = 0;
        offset = 0;
        count = _pMw->fontCount;
        for (; i < count; ++i) {
            slot = (MsgFontSlot*)((u8*)_pMw->fonts + offset);
            if (slot->data != 0 && slot->identifier == identifier) break;
            offset += sizeof(MsgFontSlot);
        }
        if (i == count) {
            i = 0;
            offset = 0;
            for (; i < count; ++i) {
                slot = (MsgFontSlot*)((u8*)_pMw->fonts + offset);
                if (slot->data == 0) {
                    MsgFontGroup* group = &blob->group;
                    slot->identifier = identifier;
                    slot->width = blob->width;
                    slot->height = blob->height;
                    slot->data = (void*)blob->nextOffset;
                    slot->data = group;
                    group->next = 0;
                    group->previous = 0;
                    break;
                }
                offset += sizeof(MsgFontSlot);
            }
            if (i == _pMw->fontCount) GSlogWrite("[GSmsgFontOpen]  FONT[%d]の登録数をオーバーしました\n", blob->identifier);
        } else {
            MsgFontGroup* group = &blob->group;
            MsgFontGroup* node = (MsgFontGroup*)slot->data;
            for (;;) {
                if (node == group) return 0;
                if (!node->next) {
                    node->next = group;
                    group->next = 0;
                    group->previous = node;
                    break;
                }
                node = node->next;
            }
        }
        if (!blob->nextOffset) break;
        blob = (MsgFontBlob*)((u8*)blob + blob->nextOffset);
    }
    return font;
}
s32 GSmsgFontClose(void* font) {
    MsgFontBlob* blob = (MsgFontBlob*)font;
    s32 i = 0;
    s32 offset = 0;
    MsgFontSlot* slot;
    for (; i < _pMw->fontCount; ++i) {
        slot = (MsgFontSlot*)((u8*)_pMw->fonts + offset);
        if (slot->data != 0 && slot->identifier == blob->identifier) break;
        offset += sizeof(MsgFontSlot);
    }
    if (i != _pMw->fontCount) {
        MsgFontGroup* group = &blob->group;
        MsgFontGroup* node = (MsgFontGroup*)slot->data;
        while (node) {
            if (node == group) {
                if (!node->previous && !node->next) {
                    slot->identifier = 0xffff;
                    slot->data = 0;
                    break;
                }
                if (node->previous) node->previous->next = node->next;
                else slot->data = node->next;
                if (node->next) node->next->previous = node->previous;
                break;
            }
            node = node->next;
        }
    }
    if (blob->nextOffset) return GSmsgFontClose((u8*)blob + blob->nextOffset);
    return 0;
}

#pragma dont_inline off
inline MsgTask* _msgFindTask(u32 identifier) {
    u8 index = 0;
    while (index < _pMw->taskCount) {
        MsgTask* task = _pMw->tasks + index;
        ++index;
        if (task->state && task->messageID == identifier) return task;
    }
    return 0;
}
extern "C" s32 GSmsgExec(u32 identifier, u8 fontSelection, u8 soundClass) {
    MsgBundle* bundle;
    MsgTask* task;
    u32 group;
    u32 textID;
    MsgBundle* found;
    u16* text;
    s32 i = 0;
    u16 count = _pMw->taskCount;
    for (; i < count; ++i) {
        task = _pMw->tasks + i;
        if (task->state == 0) break;
    }
    if (i == count) {
        GSlogWrite("GSmsgExec(%08x) 失敗（ワーク不足）\n", identifier);
        return -1;
    }
    if (identifier == 0) {
        text = 0;
    } else {
        group = identifier >> 20;
        textID = identifier & 0xfffff;
        bundle = _pMw->bundles;
        while (bundle) {
            if (identifier < 60000) {
                s32 language = pokecoloGetLanguage();
                if (fn_8010B208(bundle) != language) goto nextBundle;
            }
            if (bundle->group == group) {
                u32 upper = bundle->count;
                MsgDirectoryEntry* directory = bundle->entries;
                u32 lower = 0;
                while (lower < upper) {
                    u32 middle = (lower + upper) >> 1;
                    u32 candidate = directory[middle].identifier;
                    if (candidate == textID) {
                        if (&found != 0) found = bundle;
                        text = (u16*)((u8*)bundle + directory[middle].textOffset);
                        goto searched;
                    }
                    if (candidate < textID) lower = middle + 1;
                    else upper = middle;
                }
            }
nextBundle:
            bundle = bundle->next;
        }
        text = 0;
    }
searched:
    if (!text) {
        GSlogWrite("GSmsgExec(%08x) 失敗（データが無い）\n", identifier);
        return -1;
    }
    memset(task, 0, sizeof(MsgTask));
    task->state = 1;
    task->scaleX = 1.0f;
    task->scaleY = 1.0f;
    task->color = 0xf0f0f0ff;
    task->textStart = text;
    task->textBase = text;
    task->textCursor = text;
    task->fontID = found->font;
    task->messageID = identifier;
    task->fontSelection = fontSelection;
    task->soundClass = soundClass;
    GSmsgSetFontInfo(task);
    return 0;
}
union MsgColor { u32 word; u8 channel[4]; };
struct GSgfxLayer {
    u8 reserved0000[0x14f4];
    u32 materialColor;
    u8 reserved14f8[0x16a8 - 0x14f8];
    u32 dirty;
    u8 reserved16ac[0x16f8 - 0x16ac];
    u32 materialDirty;
    u8 reserved16fc[0x1760 - 0x16fc];
    u32 savedDirty;
    u8 reserved1764[0x17b0 - 0x1764];
    u32 savedMaterialDirty;
    inline void setMaterialColor(MsgColor value) {
        materialColor = value.word;
        materialDirty |= 1; dirty |= 0x10;
        savedMaterialDirty |= 1; savedDirty |= 0x10;
    }
};
GSgfxLayer* _TargetLayer;
GSgfxLayer* GSgfxLayerFindByID(u32);
void GSmsgSetColor(MsgTask* task) {
    MsgColor color = {0xffffffff};
    if (!_TargetLayer) _TargetLayer = GSgfxLayerFindByID(7);
    if (_TargetLayer) {
        color.channel[0] = task->color >> 24;
        color.channel[1] = (task->color >> 16) & 0xff;
        color.channel[2] = (task->color >> 8) & 0xff;
        color.channel[3] = task->color & 0xff;
        _TargetLayer->setMaterialColor(color);
    }
}
u8 pauseIsPause();
s32 _msgMainSub__FP13MSG_TASK_WORKUcUlb(MsgTask*, u8, u32, bool);
s32 GSmsgMain(u32 layerID, s32 identifier, u32 steps, bool paused) {
    if (pauseIsPause() && (identifier >= 106 || identifier < 101)) paused = true;
    _TargetLayer = GSgfxLayerFindByID(layerID);
    if (!_TargetLayer) return -1;
    MsgTask* task = _msgFindTask(identifier);
    if (!task) return -1;
    return _msgMainSub__FP13MSG_TASK_WORKUcUlb(task, task->fontSelection, steps, paused);
}
struct MsgSound { u16 category, soundID; };
extern MsgSound* message_se;
extern u32* message_se_number;
void GSsndStopNow(u32);
void GSmsgKill(u32 identifier) {
    MsgTask* task = _msgFindTask(identifier);
    if (task) {
        u32 sound = 0;
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
    MsgTask* task = _msgFindTask(identifier);
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
s32 GSmsgPrintRect(u32, s32, s32, s16, s16, u32, u32);
u32 GSmsgGetRect(u32);
s32 GSmsgPrint2(u32 mode, s32 x, s32 y, u32 flags, u32 message) {
    return GSmsgPrintRect(mode, x, y, 0, 0, flags, message);
}
s32 GSmsgPrintRight(u32 mode, s32 x, s32 y, s16 width, s16 height, u32 flags, u32 message) {
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
                if (code >= 0x81 && code <= 0x9f) code = sjis_81xx[code - 0x81][input[1] - 0x40];
                else code = sjis_e0xx[code - 0xe0][input[1] - 0x40];
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

#pragma dont_inline off
static inline s32 convertGbaCharacters(u16* destination, u8* source, s32 remaining, const u16* table) {
    s32 count = 0;
    if (!source) return 0;
    while (remaining != 0 && *source != 0xff) {
        if (destination) *destination++ = table[*source++];
        ++count;
        --remaining;
    }
    if (destination) *destination = 0;
    return count;
}
static inline s32 convertGbaQuotes(u16* destination, u8* source, s32 remaining, u16 opening, u16 closing) {
    s32 count = 0;
    if (!source) return 0;
    while (remaining != 0 && *source != 0xff) {
        if (destination) {
            switch (*source) {
            case 0xb1: *destination++ = opening; break;
            case 0xb2: *destination++ = closing; break;
            default: *destination++ = gba_international_code[*source]; break;
            }
            ++source;
        }
        ++count;
        --remaining;
    }
    if (destination) *destination = 0;
    return count;
}
extern "C" s32 GScharMakeFromGBA(u16* destination, u8* source, s32 count, s32 language) {
    u16* output = destination;
    s32 locale = language;
    s32 remaining = count;
    u8* input = source;
    switch (pokecoloGetCountryCode()) {
    case 0:
    default: return convertGbaCharacters(output, input, remaining, gba_code);
    case 1:
        switch (locale) {
        case 1: return convertGbaCharacters(output, input, remaining, gba_code);
        case 7: case 8: break;
        default: break;
        }
        return convertGbaCharacters(output, input, remaining, gba_international_code);
    case 2:
        switch (locale) {
        case 1: return convertGbaCharacters(output, input, remaining, gba_code);
        case 3: return convertGbaQuotes(output, input, remaining, 0x201e, 0x201c);
        case 4: return convertGbaQuotes(output, input, remaining, 0xab, 0xbb);
        case 0: case 2: case 5: case 6: case 7: case 8:
        default: return convertGbaCharacters(output, input, remaining, gba_international_code);
        }
    }
}
#pragma dont_inline off
static inline s32 encodeGbaCharacters(u8* destination, const u16* source, const u16* table) {
    u32 code;
    const u16* entry;
    const u16* input = source;
    u8* output = destination;
    s32 count = 0;
    if (!input) return 0;
    while ((code = *input) != 0) {
        entry = table;
        s32 index = 0;
        while (code != *entry) {
            ++index;
            ++entry;
            if (index >= 256) { index = 0xb7; break; }
        }
        if (output) *output++ = (u8)index;
        ++count;
        ++input;
    }
    return count;
}
static inline s32 encodeGbaQuotes(u8* destination, const u16* source) {
    u32 code;
    const u16* input = source;
    u8* output = destination;
    s32 count = 0;
    if (!input) return 0;
    while ((code = *input) != 0) {
        s32 index = 0;
        switch (code) {
        case 0xab: case 0x201e: index = 0xb1; break;
        case 0xbb: case 0x201c: index = 0xb2; break;
        default:
            const u16* entry = gba_international_code;
            while (code != *entry) {
                ++index;
                ++entry;
                if (index >= 256) { index = 0xb7; break; }
            }
            break;
        }
        if (output) *output++ = (u8)index;
        ++count;
        ++input;
    }
    return count;
}
extern "C" s32 GBAMakeFromGSchar(u8* destination, const u16* source, s32 language) {
    switch (pokecoloGetCountryCode()) {
    case 0: default: return encodeGbaCharacters(destination, source, gba_code);
    case 1:
        switch (language) {
        case 1: return encodeGbaCharacters(destination, source, gba_code);
        case 7: case 8: break;
        default: break;
        }
        return encodeGbaCharacters(destination, source, gba_international_code);
    case 2:
        switch (language) {
        case 1: return encodeGbaCharacters(destination, source, gba_code);
        case 3: case 4: return encodeGbaQuotes(destination, source);
        case 0: case 2: case 5: case 6: case 7: case 8:
        default: return encodeGbaCharacters(destination, source, gba_international_code);
        }
    }
}
#pragma dont_inline off
static inline u16* _msgFindText(u32 identifier, MsgBundle** found) {
    if (!identifier) return 0;
    u32 group = identifier >> 20;
    u32 textID = identifier & 0xfffff;
    MsgBundle* bundle = _pMw->bundles;
    while (bundle) {
        if (identifier < 60000) {
            s32 language = pokecoloGetLanguage();
            s32 bundleLanguage = fn_8010B208(bundle);
            if (bundleLanguage != language) goto next;
        }
        if (bundle->group == group) {
            u32 middle;
            u32 upper = bundle->count;
            u32 lower = 0;
            MsgDirectoryEntry* directory = bundle->entries;
            u32 candidate;
            while (lower < upper) {
                middle = (lower + upper) >> 1;
                candidate = directory[middle].identifier;
                if (candidate == textID) {
                    if (found) *found = bundle;
                    return (u16*)((u8*)bundle + directory[middle].textOffset);
                }
                if (candidate < textID) lower = middle + 1;
                else upper = middle;
            }
        }
next:
        bundle = bundle->next;
    }
    return 0;
}
static inline u16 _msgNextCode(MsgTask* task) {
    u32 code;
    for (;;) {
        const u16* cursor = task->textCursor;
        code = *cursor;
        if (code == 0) {
            if ((s8)task->textDepth == 0) return code;
            --task->textDepth;
            task->textCursor = task->returnText[(s8)task->textDepth];
        } else {
            task->textCursor = cursor + 1;
            break;
        }
    }
    return code;
}
static inline u32 _msgNextByte(MsgTask* task) {
    const u8* cursor = (const u8*)task->textCursor;
    task->textCursor = (const u16*)(cursor + 1);
    return *cursor;
}
static inline void _msgCallCtrlFunc(MsgTask* task, u32 code) {
    MsgControl* controls = _pMw->controls;
    if (!controls) return;
    u32 enabled;
    if (task->measuring == 0) enabled = (controls[code].flags >> 4) & 1;
    else enabled = (controls[code].flags >> 3) & 1;
    if (!enabled) return;
    MsgControl* control = controls + code;
    if (!control->callback) return;
    u32 result = control->callback(task);
    u32 kind = (control->flags >> 6) & 3;
    if (kind && result) {
        const u16* text;
        switch (kind) {
        case 1: text = (const u16*)result; break;
        case 2: text = GSmsgGetGSchar(result); break;
        }
        if ((s8)task->textDepth >= 3) {
            GSlogWrite("[%s] Error!! メッセージのネストが深すぎます\n", __FUNCTION__);
        } else {
            task->returnText[(s8)task->textDepth++] = task->textCursor;
            task->textCursor = text;
        }
    }
}
static inline void _msgInitTask(MsgTask* task, const u16* text) {
    memset(task, 0, sizeof(MsgTask));
    task->state = 1;
    task->scaleX = 1.0f;
    task->scaleY = 1.0f;
    task->color = 0xf0f0f0ff;
    task->textStart = text;
    task->textBase = text;
    task->textCursor = text;
}
u32 _msgGetSize(const u16* text) {
    if (!text) { GSlogWrite("_msgGetSize() failed.\n"); return 0; }
    static MsgTask Task;
    MsgTask* task = &Task;
    _msgInitTask(task, text);
    task->measuring = 1;
    GSmsgSetFontInfo(task);
    u16 code;
    for (;;) {
        code = _msgNextCode(task);
        if (!code) break;
        if (code == 0xffff) {
            u32 command = _msgNextByte(task);
            _msgCallCtrlFunc(task, command);
        }
    }
    return (const u8*)task->textCursor - (const u8*)text + 2;
}
extern "C" s32 GSmsgPrintRect(u32 layerID, s32 x, s32 y, s16 width, s16 height, u32 color, u32 identifier) {
    _TargetLayer = GSgfxLayerFindByID(layerID);
    if (!_TargetLayer) return -1;
    static MsgTask Task;
    MsgTask* task = &Task;
    MsgBundle* bundle;
    u16* text = _msgFindText(identifier, &bundle);
    if (!text) return -1;
    _msgInitTask(task, text);
    task->fontID = bundle->font;
    task->messageID = identifier;
    task->originX = x;
    task->originY = y;
    task->boxWidth = width;
    task->boxHeight = height;
    task->fontSelection = 3;
    task->color = color;
    task->immediate = 1;
    GSmsgSetFontInfo(task);
    return _msgMainSub__FP13MSG_TASK_WORKUcUlb(task, task->fontSelection, 0, false);
}
extern "C" u32 GSmsgGetRect(u32 identifier) {
    s16 width = 0;
    s16 height = 0;
    u8 quote = 0;
    if (!identifier) return 0;
    MsgBundle* bundle;
    u16* text = _msgFindText(identifier, &bundle);
    if (!text) return 0;
    static MsgTask Task;
    MsgTask* task = &Task;
    _msgInitTask(task, text);
    task->fontID = bundle->font;
    task->messageID = identifier;
    task->measuring = 1;
    GSmsgSetFontInfo(task);
    u16 code;
    for (;;) {
        code = _msgNextCode(task);
        if (!code) break;
        if (code == 0xffff) {
            u32 command = _msgNextByte(task);
            if (command == 3 || command == 0x6e || command == 0x6d) {
                task->cursorX += task->glyphWidth;
                if (width < task->cursorX) width = task->cursorX;
            }
            _msgCallCtrlFunc(task, command);
            if (quote && task->cursorX == task->originX) task->cursorX += task->glyphWidth;
        } else {
            if (task->rubyState == 2) continue;
            if (code == 0x20) task->charWidth = (task->glyphWidth >> 1) * task->scaleX;
            else {
                tagFONT_INFO* info = _msgGetCodeInfo(task, code, 0);
                if (!info) task->charWidth = task->glyphWidth * task->scaleX;
                else task->charWidth = info->data[0] * task->scaleX;
            }
            if (!task->quoteMode) {
                if (code == 0x300c) quote = 1;
                if (code == 0x300d) quote = 0;
            }
            task->cursorX += task->charWidth;
        }
        if (width < task->cursorX) width = task->cursorX;
        if (height < task->cursorY) height = task->cursorY;
    }
    return ((width - 1) << 16) | (s16)(height + (task->glyphHeight * task->scaleY + 1.0f));
}
extern "C" u16* GSmsgMakeGScharStr(u16* destination, s32 capacity, u32 identifier) {
    u32 bytes = 0;
    if (!identifier) return 0;
    if (!destination) return 0;
    if (capacity <= 0) return 0;
    u8* output = (u8*)destination;
    u32 limit = (capacity - 1) * 2;
    MsgBundle* bundle;
    u16* text = _msgFindText(identifier, &bundle);
    if (!text) return 0;
    static MsgTask Task;
    MsgTask* task = &Task;
    _msgInitTask(task, text);
    task->fontID = bundle->font;
    task->messageID = identifier;
    task->measuring = 1;
    for (;;) {
        u8* savedOutput = output;
        u32 savedBytes = bytes;
        u16 code = _msgNextCode(task);
        if (!code) break;
        bytes += 2;
        if (limit < bytes) break;
        *(u16*)output = code;
        output += 2;
        if (code != 0xffff) continue;
        u32 command = _msgNextByte(task);
        ++bytes;
        if (limit >= bytes) *output++ = command;
        else { output = savedOutput; break; }
        const u8* argument = (const u8*)task->textCursor;
        s8 depth = task->textDepth;
        _msgCallCtrlFunc(task, command);
        if (depth == task->textDepth) {
            bytes += (const u8*)task->textCursor - argument;
            if (limit >= bytes) {
                while ((const u8*)task->textCursor > argument) *output++ = *argument++;
            } else { output = savedOutput; break; }
        } else { output = savedOutput; bytes = savedBytes; }
    }
    *(u16*)output = 0;
    return destination;
}
extern "C" void GSmsgInitRuby(MsgTask* task) {
    s8 baseCount = 0;
    s8 rubyCount = 0;
    const u16* cursor = task->textCursor;
    s16 baseWidth = 0;
    u8 depth = task->textDepth;
    s8 rubyEnabled = task->rubyEnabled;
    u8 measuring = task->measuring;
    s16 rubyWidth = 0;
    const u16* return0 = task->returnText[0];
    u8 phase = 0;
    task->rubyText = 0;
    task->rubyIndex = 0;
    task->rubyPosition = 0;
    task->measuring = 0;
    task->rubyEnabled = 1;
    const u16* return1 = task->returnText[1];
    const u16* return2 = task->returnText[2];
    task->rubyState = 1;
    while (phase < 2) {
        u16 code = _msgNextCode(task);
        if (code) {
            if (code == 0xffff) {
                u32 command = _msgNextByte(task);
                _msgCallCtrlFunc(task, command);
                if (phase == 0) {
                    if (task->rubyState == 2) task->rubyText = task->textCursor;
                    else continue;
                } else if (task->rubyState != 0) continue;
            } else {
                tagFONT_INFO* info = _msgGetCodeInfo(task, code, 0);
                u8 width;
                if (info) width = info->data[0];
                else width = task->glyphWidth;
                if (phase == 0) {
                    ++baseCount;
                    baseWidth = baseWidth + ((s16)width * task->scaleX + 2.0f);
                } else {
                    ++rubyCount;
                    rubyWidth = rubyWidth + (0.5f * ((s16)width * task->scaleX) + 2.0f);
                }
                continue;
            }
        }
        ++phase;
    }
    task->rubyBaseCount = baseCount;
    task->rubyCount = rubyCount;
    task->rubyX = task->cursorX + (baseWidth - rubyWidth) / 2;
    task->rubyWidth = 0.5f * (task->glyphWidth * task->scaleX);
    task->rubyY = -((0.4f * task->glyphHeight) - task->cursorY);
    task->textCursor = cursor;
    task->textDepth = depth;
    task->returnText[0] = return0;
    task->returnText[1] = return1;
    task->returnText[2] = return2;
    task->rubyEnabled = rubyEnabled != 0;
    task->measuring = measuring;
}
void _msgSetChar(MSG_TASK_WORK*, u16);
struct MsgRubyAdjustment { u16 code; f32 scaleX, scaleY, x, y; };
static MsgRubyAdjustment _adjustTable[2] = {
    {0x3057, 1.0f, 0.9f, 0.0f, 1.0f},
    {0x304d, 1.0f, 1.0f, 0.0f, -1.0f}
};
void _msgDispRuby(MSG_TASK_WORK* task) {
    f32 scaleX;
    f32 scaleY;
    ++task->rubyIndex;
    u32 numerator = task->rubyCount;
    u32 index = task->rubyIndex;
    s32 denominator = task->rubyBaseCount;
    u8 previous = task->rubyPosition;
    f32 savedX = task->cursorX;
    f32 savedY = task->cursorY;
    u8 count = (s32)(numerator * index) / denominator;
    task->cursorX = task->rubyX;
    task->cursorY = task->rubyY;
    u8 remaining = count - previous;
    const u8* cursor = (const u8*)task->rubyText;
    while (remaining) {
        scaleX = task->scaleX;
        scaleY = task->scaleY;
        task->scaleX *= 0.5f;
        task->scaleY *= 0.5f;
        u32 code = *(const u16*)cursor;
        cursor += 2;
        if (code == 0xffff) ++cursor;
        else {
            for (s32 i = 0; i < 2; ++i) {
                MsgRubyAdjustment* adjustment = &_adjustTable[i];
                if (code == adjustment->code) {
                    task->scaleX *= adjustment->scaleX;
                    task->scaleY *= adjustment->scaleY;
                    task->cursorX += adjustment->x;
                    task->cursorY += adjustment->y;
                }
            }
            _msgSetChar(task, code);
            --remaining;
            task->cursorX += task->charWidth;
            task->cursorY = task->rubyY;
        }
        task->scaleX = scaleX;
        task->scaleY = scaleY;
    }
    task->rubyText = (const u16*)cursor;
    task->rubyPosition = count;
    task->rubyX = task->cursorX;
    task->rubyY = task->cursorY;
    task->cursorX = savedX;
    task->cursorY = savedY;
}

extern "C" {
void spriteSetEnv(s32);s32 timeGetLastFrameTime();u16 *windowGetKeyInfo();
void *GSgfxVFBuildTemp(s32,s32,u8,s32,u8,s32,u8,s32,s32);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(GSgfxLayer*,void*);
void beginSurface__10GSgfxLayerFUs(GSgfxLayer*,u16);void endSurface__10GSgfxLayerFv(GSgfxLayer*);
s32 GSsndPlayNow(u32);s32 menuSubGetKaiwaCsrID();s32 menuSubGetKaiwaCloseWindowID();
void windowDrawSprite(s32,s32,void*,s32,s32,s32);
double cos(double);
}
#pragma dont_inline off
static inline u32 &msgLayerWord(u32 offset) {return *(u32*)((u8*)_TargetLayer+offset);}
static inline u8 &msgLayerByte(u32 offset) {return *((u8*)_TargetLayer+offset);}
static inline u8 msgStepControl(MsgTask *task,u32 code) {
 MsgControl *controls=_pMw->controls;if(!controls)return 0;
 u32 enabled=task->measuring?((controls[code].flags>>3)&1):((controls[code].flags>>4)&1);if(!enabled)return 0;
 MsgControl *control=&controls[code];
 if(control->callback) {
  u32 result=control->callback(task);u32 kind=(control->flags>>6)&3;
  if(kind&&result) {
   const u16 *text;
   switch(kind){case 1:text=(const u16*)result;break;case 2:text=_msgFindText(result,0);break;}
   if((s8)task->textDepth>=3)GSlogWrite("[%s] Error!! メッセージのネストが深すぎます\n","_msgCallCtrlFunc");
   else {task->returnText[(s8)task->textDepth++]=task->textCursor;task->textCursor=text;}
  }
 }return(control->flags>>5)&1;
}
#pragma dont_inline on
extern "C" u8 lbl_804E834C=3;
s32 _msgMainSub__FP13MSG_TASK_WORKUcUlb(MsgTask *task,u8 mode,u32 buttons,bool paused) {
 u8 quote=0,speaking=0;MsgColor white={0xffffffff};
 if(!task||!task->state)return -1;
 spriteSetEnv(msgLayerWord(0x28));setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(_TargetLayer,GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));
 GStexture *texture=_pMw->textures[_pMw->textureIndex];
 if((GStexture*)msgLayerWord(0x1740)!=texture||(GStexture*)msgLayerWord(0x17f8)!=texture||texture->dirty) {
  msgLayerWord(0x1740)=(u32)texture;msgLayerWord(0x173c)|=1;msgLayerWord(0x17f8)=(u32)texture;msgLayerWord(0x17f4)|=1;
 }
 msgLayerByte(0xeac)=1;msgLayerWord(0x16cc)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x1784)|=1;msgLayerWord(0x1760)|=8;
 msgLayerWord(0xeb0)=0;msgLayerWord(0xeb4)=0;msgLayerWord(0xeb8)=4;msgLayerWord(0x16d0)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x1788)|=1;msgLayerWord(0x1760)|=8;
 _TargetLayer->setMaterialColor(white);
 msgLayerWord(0x1504)=12;msgLayerWord(0x16fc)|=1;msgLayerWord(0x16a8)|=0x10;msgLayerWord(0x17b4)|=1;msgLayerWord(0x1760)|=0x10;
 msgLayerWord(0xf70)=15;msgLayerWord(0xf74)=14;msgLayerWord(0xf78)=10;msgLayerWord(0xf7c)=15;msgLayerWord(0x16d4)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x178c)|=1;msgLayerWord(0x1760)|=8;
 msgLayerWord(0x1170)=0;msgLayerWord(0x1174)=0;msgLayerWord(0x1178)=0;msgLayerByte(0x117c)=1;msgLayerWord(0x1180)=0;msgLayerWord(0x16dc)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x1794)|=1;msgLayerWord(0x1760)|=8;
 msgLayerWord(0x1070)=7;msgLayerWord(0x1074)=4;msgLayerWord(0x1078)=5;msgLayerWord(0x107c)=7;msgLayerWord(0x16d8)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x1790)|=1;msgLayerWord(0x1760)|=8;
 msgLayerWord(0x12b0)=0;msgLayerWord(0x12b4)=0;msgLayerWord(0x12b8)=0;msgLayerByte(0x12bc)=1;msgLayerWord(0x12c0)=0;msgLayerWord(0x16e0)|=1;msgLayerWord(0x16a8)|=8;msgLayerWord(0x1798)|=1;msgLayerWord(0x1760)|=8;
 _pMw->image=(u8*)GStextureLockImage(_pMw->textures[_pMw->textureIndex],0);
 task->rubyEnabled=(buttons&0x30)!=0;
 u8 multiplier=(*windowGetKeyInfo()&0x30)?lbl_804E834C:1;u8 stop=0;
 task->measuring=0;task->rubyState=0;task->waitPrompt=0;task->closePrompt=0;
 s32 frames=timeGetLastFrameTime();if(frames==0)frames=1;
 if(!paused) {
  for(s32 i=0;i<frames*(s8)multiplier;++i) {
   for(;;) {
    u16 code=_msgNextCode(task);
    if(!code){task->state=2;break;}
    if(code==0xffff)stop=msgStepControl(task,_msgNextByte(task));
    else if(task->rubyState!=2){stop=1;if(mode)stop=0;speaking=1;}
    if(stop)break;
   }
  }
 }
 const u16 *end=task->textCursor;u8 depth=task->textDepth;const u16 *returns[3];returns[0]=task->returnText[0];returns[1]=task->returnText[1];returns[2]=task->returnText[2];
 task->measuring=1;task->cursorX=task->originX;task->cursorY=task->originY;task->textCursor=task->textBase;task->textDepth=0;task->rubyState=0;
 for(;;) {
  if(task->textCursor==end){s32 i=0;for(;i<(s8)task->textDepth;++i)if(task->returnText[i]!=returns[i])break;if(i==(s8)task->textDepth)break;}
  u16 code=_msgNextCode(task);if(!code)break;
  if(code==0xffff){msgStepControl(task,_msgNextByte(task));if(quote&&task->cursorX==task->originX)task->cursorX+=task->glyphWidth;}
  else if(task->rubyState!=2){_msgSetChar(task,code);task->cursorX+=task->charWidth;if(!task->quoteMode){if(code==0x300c)quote=1;if(code==0x300d)quote=0;}if(task->rubyState==1)_msgDispRuby(task);}
 }
 if(mode)speaking=0;
 if(speaking!=task->soundActive){u16 sound=0;if(message_se){for(u32 i=0;i<*message_se_number;++i)if(task->soundClass==message_se[i].category){sound=message_se[i].soundID;break;}}
  if(sound){if(speaking)GSsndPlayNow(sound);else GSsndStopNow(sound);}task->soundActive=speaking;
 }
 if(task->waitPrompt){static s32 cnt=0;s32 x=2.0f+task->cursorX;s32 y=8.0f+task->cursorY;y+=(s32)(4.0f*(f32)cos((3.1415927f*(f32)cnt)/25.0f));cnt+=timeGetLastFrameTime();cnt%=50;s32 layer=msgLayerWord(0x28);windowDrawSprite(x,y,0,(u16)menuSubGetKaiwaCsrID(),0,layer);}
 if(task->closePrompt){static s32 cnt=0;s32 y=task->cursorY;s32 x=2.0f+task->cursorX;y+=(s32)(4.0f*(f32)cos((3.1415927f*(f32)cnt)/25.0f));cnt+=timeGetLastFrameTime();cnt%=50;s32 layer=msgLayerWord(0x28);windowDrawSprite(x,y,0,(u16)menuSubGetKaiwaCloseWindowID(),0,layer);}
 task->textCursor=end;task->textDepth=depth;task->returnText[0]=returns[0];task->returnText[1]=returns[1];task->returnText[2]=returns[2];GStextureUnlockImage(_pMw->textures[_pMw->textureIndex]);return 0;
}
#pragma dont_inline off
static inline void msgShadowVertex(s16 x,s16 y,u8 alpha,f32 u,f32 v) {
 *(volatile s16*)0xcc008000=x;*(volatile s16*)0xcc008000=y;
 *(volatile u8*)0xcc008000=0;*(volatile u8*)0xcc008000=0;*(volatile u8*)0xcc008000=0;*(volatile u8*)0xcc008000=alpha;
 *(volatile f32*)0xcc008000=u;*(volatile f32*)0xcc008000=v;
}
static inline void msgShadowQuad(s16 x0,s16 y0,s16 x1,s16 y1,u8 alpha,f32 u0,f32 v0,f32 u1,f32 v1) {
 msgShadowVertex(x0,y0,alpha,u0,v0);msgShadowVertex(x1,y0,alpha,u1,v0);msgShadowVertex(x0,y1,alpha,u0,v1);msgShadowVertex(x1,y1,alpha,u1,v1);
}
static inline void msgColorVertex(s16 x,s16 y,u32 color,f32 u,f32 v) {
 *(volatile s16*)0xcc008000=x;*(volatile s16*)0xcc008000=y;*(volatile u32*)0xcc008000=color;*(volatile f32*)0xcc008000=u;*(volatile f32*)0xcc008000=v;
}
#pragma dont_inline on
void _msgMakeTexture(MSG_TASK_WORK *task,u8 *pixels,s16 width,s16 height,s16 bearing) {
 if(_pMw->textureX+width+2>=512){_pMw->textureY+=_pMw->rowHeight+2;_pMw->textureX=2;_pMw->rowHeight=task->glyphHeight+2;if(_pMw->textureY+_pMw->rowHeight>=512)_pMw->textureY=1;}
 if(_pMw->rowHeight<height)_pMw->rowHeight=task->glyphHeight;
 s32 bytes=((width+1)&~1)/2;u8 *image=_pMw->image;
 for(s32 y=-1;y<height+1;++y){s32 row=_pMw->textureY+y;for(s32 x=-2;x<width+2;x+=2){s32 column=_pMw->textureX+x;image[(((column>>3)+((row>>3)<<6))<<5)+(((column&7)+(row&7)*8)>>1)]=0;}}
 for(s32 y=0;y<height;++y){u8 *source=pixels+y*bytes;s32 row=_pMw->textureY+y;for(s32 x=0;x<width;x+=2){s32 column=_pMw->textureX+x;image[(((column>>3)+((row>>3)<<6))<<5)+(((column&7)+(row&7)*8)>>1)]=*source++;}}
 s16 x0=task->cursorX;s16 y0=task->reserved43+(bearing*task->scaleY+task->cursorY);s16 x1=width*task->scaleX+x0;s16 y1=height*task->scaleY+y0;
 f32 u0=_pMw->textureX*0.001953125f,v0=_pMw->textureY*0.001953125f,u1=(_pMw->textureX+width)*0.001953125f,v1=(_pMw->textureY+height)*0.001953125f;
 msgLayerWord(0x1998)=0x98;u8 alpha=(u8)task->color*0xc0/255;
 switch(task->immediate){default:beginSurface__10GSgfxLayerFUs(_TargetLayer,4);break;
 case 1:beginSurface__10GSgfxLayerFUs(_TargetLayer,8);msgShadowQuad(x0+1,(s16)(y0-2)+1,x1+1,(s16)(y1-2)+1,alpha,u0,v0,u1,v1);break;
 case 2:beginSurface__10GSgfxLayerFUs(_TargetLayer,20);s16 top=y0-2,bottom=y1-2;msgShadowQuad(x0-1,top,x1-1,bottom,alpha,u0,v0,u1,v1);msgShadowQuad(x0+1,top,x1+1,bottom,alpha,u0,v0,u1,v1);msgShadowQuad(x0,top-1,x1,bottom-1,alpha,u0,v0,u1,v1);msgShadowQuad(x0,top+1,x1,bottom+1,alpha,u0,v0,u1,v1);break;
 }
 msgColorVertex(x0,y0-2,task->color,u0,v0);msgColorVertex(x1,y0-2,task->color,u1,v0);msgColorVertex(x0,y1-2,task->color,u0,v1);msgColorVertex(x1,y1-2,task->color,u1,v1);endSurface__10GSgfxLayerFv(_TargetLayer);_pMw->textureX+=bytes*2+2;
}
#pragma dont_inline off
static inline void msgMissingVertex(s16 x,s16 y) {
 *(volatile s16*)0xcc008000=x;*(volatile s16*)0xcc008000=y;*(volatile u8*)0xcc008000=0xff;*(volatile u8*)0xcc008000=0xff;*(volatile u8*)0xcc008000=0xff;*(volatile u8*)0xcc008000=0xff;
}
#pragma dont_inline on
void _msgSetChar(MSG_TASK_WORK *task,u16 code) {
 tagFONT_INFO *group;
 if(code==0x20){task->charWidth=((u32)task->glyphWidth>>1)*task->scaleX;return;}
 tagFONT_INFO *info=_msgGetCodeInfo(task,code,&group);
 if(!info){s16 x0=task->cursorX,y0=(s32)task->cursorY+2,x1=task->glyphWidth*task->scaleX+x0,y1=task->glyphHeight*task->scaleY+y0;
  setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(_TargetLayer,GSgfxVFBuildTemp(0,3,0,0,1,5,0,0,0));msgLayerWord(0x1998)=0x98;beginSurface__10GSgfxLayerFUs(_TargetLayer,4);
  msgMissingVertex(x0,y0);msgMissingVertex(x1,y0);msgMissingVertex(x0,y1);msgMissingVertex(x1,y1);endSurface__10GSgfxLayerFv(_TargetLayer);
  setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(_TargetLayer,GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));task->charWidth=task->glyphWidth*task->scaleX+2.0f;return;
 }
 u32 data=*(u32*)((u8*)info+4);u8 width=info->data[0];u8 height=info->data[1];u8 *pixels=(u8*)group+*(u32*)((u8*)group+4)+(data&0xffffff);
 _msgMakeTexture(task,pixels,width,height,(s8)(data>>24));task->charWidth=(s16)width*task->scaleX;
}
#include <libc/stdarg.h>
extern "C" s32 logVsnprintf_float(char*,u32,const char*,va_list);
extern "C" s32 GSprint(u32 layer,s32 x,s32 y,u32 color,const char *format,...) {
 static MsgTask Task;static char buff[256];static u16 gcstr[512];
 _TargetLayer=GSgfxLayerFindByID(layer);if(!_TargetLayer)return -1;
 va_list args;va_start(args,format);logVsnprintf_float(buff,255,format,args);va_end(args);buff[255]=0;SJIStoGSchar(gcstr,buff);
 MsgTask *task=&Task;_msgInitTask(task,gcstr);task->originX=x;task->originY=y;task->color=color;task->immediate=1;task->fontID=2;GSmsgSetFontInfo(task);
 spriteSetEnv(msgLayerWord(0x28));setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(_TargetLayer,GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4));
 GStexture *texture=_pMw->textures[_pMw->textureIndex];
 if((GStexture*)msgLayerWord(0x1740)!=texture||(GStexture*)msgLayerWord(0x17f8)!=texture||texture->dirty){msgLayerWord(0x1740)=(u32)texture;msgLayerWord(0x173c)|=1;msgLayerWord(0x17f8)=(u32)texture;msgLayerWord(0x17f4)|=1;}
 _pMw->image=(u8*)GStextureLockImage(_pMw->textures[_pMw->textureIndex],0);task->cursorX=task->originX;task->cursorY=task->originY;
 for(;;){u16 code=_msgNextCode(task);switch(code){case 0:break;case 10:case 13:continue;default:_msgSetChar(task,code);task->cursorX+=task->charWidth;continue;}break;}
 GStextureUnlockImage(_pMw->textures[_pMw->textureIndex]);return 0;
}
