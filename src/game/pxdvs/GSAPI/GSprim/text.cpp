extern "C" {
#include <libc/stdio.h>
}
#include <game/pxdvs/GSAPI/GSprim/GSprim.hpp>
#include <libc/string.h>
#include <dolphin/gx/GXVert.h>
#include "lineFont.inc"



static f32 _primTextXpel = 6.0f;
static f32 _primTextYpel = 6.0f;
static u8 _primTextColor[4] = {0xFF, 0xFF, 0xFF, 0xFF};

static u32 _primRenderBuf(f32, f32, char*, unsigned long, bool);
static u8* _primChar2Ptr(char);
static inline void textState() {
    if (primData.lineState != 2) {
        GSprimLayer()->setLineWidth((s32)(6.0f * primData.textWidth), 0);
        primData.lineState = 2;
    }
}
extern "C" void GSprimWriteStr(f32 x, f32 y, const char* format, ...) {
    static char buf[256];
    va_list args;
    va_start(args, format);
    vsprintf(buf, format, args);
    va_end(args);
    u32 length = strlen(buf);
    textState();
    GSgfxVF* vf = GSgfxVFGetPredef(2);
    GSprimLayer()->setRenderStateAndSelect(vf);
    GSprimLayer()->primitive = 0xa8;
    u32 count = _primRenderBuf(x, y, buf, length, false);
    GSprimLayer()->beginSurface(count * 2);
    _primRenderBuf(x, y, buf, length, true);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimWriteChar(f32 x, f32 y, char character) {
    textState();
    GSgfxVF* vf = GSgfxVFGetPredef(2);
    GSprimLayer()->setRenderStateAndSelect(vf);
    GSprimLayer()->primitive = 0xa8;
    u32 count = _primRenderBuf(x, y, &character, 1, false);
    GSprimLayer()->beginSurface(count * 2);
    _primRenderBuf(x, y, &character, 1, true);
    GSprimLayer()->endSurface();
}
extern "C" void GSprimSetTextWidth(f32 width) {
    primData.textWidth = width;
    primData.lineState = 0;
}

extern "C" void GSprimSetTextColor(const u8* color) {
    _primTextColor[0] = color[0];
    _primTextColor[1] = color[1];
    _primTextColor[2] = color[2];
    _primTextColor[3] = color[3];
}

extern "C" void GSprimSetTextSize(f32 x, f32 y) {
    _primTextXpel = x;
    _primTextYpel = y;
}

static inline u8 hexDigit(char c) {
    switch (c) {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': return c - '0' + 0;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': return c - 'a' + 10;
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': return c - 'A' + 10;
    default: return 0;
    }
}
static u32 _primRenderBuf(f32 x, f32 y, char* text, unsigned long length, bool draw) {
    u32 total = 0;
    while (length--) {
        switch (*text) {
        case '\n': case '\r': break;
        case '|':
            if (draw == true) {
                _primTextColor[0] = (hexDigit(text[1]) << 4) | hexDigit(text[2]);
                _primTextColor[1] = (hexDigit(text[3]) << 4) | hexDigit(text[4]);
                _primTextColor[2] = (hexDigit(text[5]) << 4) | hexDigit(text[6]);
            }
            length -= 6;
            text += 6;
            break;
        default: {
            u8* glyph = _primChar2Ptr(*text);
            s32 count = *glyph++;
            total += count;
            if (draw == true) {
                while (count--) {
                    s32 first = glyph[0], second = glyph[1];
                    glyph += 2;
                    GXPosition2f32((0.11f * (first >> 4)) * _primTextXpel + x,
                                   (0.11f * (first & 15)) * _primTextYpel + y);
                    GXColor4u8(_primTextColor[0], _primTextColor[1], _primTextColor[2], _primTextColor[3]);
                    GXPosition2f32((0.11f * (second >> 4)) * _primTextXpel + x,
                                   (0.11f * (second & 15)) * _primTextYpel + y);
                    GXColor4u8(_primTextColor[0], _primTextColor[1], _primTextColor[2], _primTextColor[3]);
                }
            }
        }
        case ' ':
            x += _primTextXpel;
            break;
        }
        ++text;
    }
    return total;
}
static u8* _primChar2Ptr(char c) {
    s32 index;
    if (c >= '0' && c <= '9') index = c - '0';
    else if (c >= 'A' && c <= 'Z') index = c - 'A' + 10;
    else if (c >= 'a' && c <= 'z') index = c - 'a' + 10;
    else switch (c) {
    case '-': index = 36; break;
    case '_': index = 37; break;
    case '~': index = 38; break;
    case '>': index = 39; break;
    case '/': index = 40; break;
    case '(': index = 41; break;
    case ')': index = 42; break;
    case ',': index = 43; break;
    case '<': index = 44; break;
    case '+': index = 45; break;
    case '$': index = 46; break;
    case '.': index = 47; break;
    case ':': index = 48; break;
    case '[': index = 49; break;
    case ']': index = 50; break;
    case '=': index = 51; break;
    case '#': index = 52; break;
    case '!': index = 53; break;
    case 0x27: index = 54; break;
    case '"': index = 55; break;
    default: index = 37; break;
    }
    return _primLineFont[index];
}
