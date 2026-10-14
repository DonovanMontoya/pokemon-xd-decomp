#ifndef AGB_COMMUNICATION_PRIVATE_HPP
#define AGB_COMMUNICATION_PRIVATE_HPP
#include <dolphin/types.h>

#define AGB_BUS_CLOCK (*(u32 *)0x800000F8)
#define AGB_TIMER_CLOCK (AGB_BUS_CLOCK / 4)
#define AGB_MSEC_TO_TICKS(ms) ((ms) * (AGB_TIMER_CLOCK / 1000))
#define AGB_SEC_TO_TICKS(sec) ((sec) * AGB_TIMER_CLOCK)

struct OSAlarm;
struct OSContext;
struct OSThread;

typedef void (*GBACallback)(s32 chan, s32 ret);

// per-channel work area of the GBA communication state machine
struct AgbWork {
    s32 active;      // 0x00
    u8 gbaStatus;    // 0x04
    u8 pad5[3];
    s32 step;        // 0x08
    s32 busy;        // 0x0C
    s32 job;         // 0x10
    s32 ret;         // 0x14
    s32 status;      // 0x18
    u32 w1c;         // 0x1C
    u32 w20;         // 0x20
    u32 w24;         // 0x24
    u32 w28;         // 0x28
    u32 w2c;         // 0x2C
    u32 w30;         // 0x30
    u32 w34;         // 0x34
    u32 w38;         // 0x38
    u32 w3c;         // 0x3C
    u32 w40;         // 0x40
    u32 w44;         // 0x44
    u32 w48;         // 0x48
    u32 w4c;         // 0x4C
    u32 w50;         // 0x50
    u32 w54;         // 0x54
    u32 w58;         // 0x58
    u32 idx;         // 0x5C
    u32 w60;         // 0x60
    u32 w64;         // 0x64
    u32 w68;         // 0x68
    u32 t0;          // 0x6C
    u32 len0;        // 0x70
    u32 t1;          // 0x74
    u32 len1;        // 0x78
    u32 t2;          // 0x7C
    u32 len2;        // 0x80
    u32 w84;         // 0x84
    u32 w88;         // 0x88
    u8 *buf;         // 0x8C
    u32 size;        // 0x90
    void *pokemon;   // 0x94
    u32 *result;     // 0x98
};

struct GSdvdWork;

extern "C" {
void *memcpy(void *, const void *, u32);
u32 strlen(const char *);
char *strcpy(char *, const char *);
u32 OSGetTick();
void OSReport(const char *, ...);
s32 GBAInit();
s32 GBAReset(s32, u8 *);
s32 GBAGetStatus(s32, u8 *);
s32 GBARead(s32, u8 *, u8 *);
s32 GBAWrite(s32, u8 *, u8 *);
s32 GBAResetAsync(s32, u8 *, GBACallback);
s32 GBAGetStatusAsync(s32, u8 *, GBACallback);
s32 GBAReadAsync(s32, u8 *, u8 *, GBACallback);
s32 GBAWriteAsync(s32, u8 *, u8 *, GBACallback);
u32 SIProbe(s32);
u32 gba_SIProbe(s32);
void gbaCommandSetKeyState(s32, s32);
void pokeconv(void *, u8 *);
void GSthreadSwitch();
void *GSmemAllocAlign(u32, u16);
void GSmemFree(void *);
GSdvdWork *GSdvdOpen(const char *);
u32 GSdvdGetLength(GSdvdWork *);
u8 GSdvdReadAsync(GSdvdWork *, void *, s32, s32, void *);
s32 GSdvdGetFileInfoStatus(GSdvdWork *);
s32 GSdvdClose(GSdvdWork *);
s32 PKJB_GetKey(s32, u16 *);
}
#endif
