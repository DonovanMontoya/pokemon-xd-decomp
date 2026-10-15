#include "TRK_MINNOW_DOLPHIN/ppc/Generic/targimpl.h"
#include "TRK_MINNOW_DOLPHIN/Os/dolphin/dolphin_trk.h"

extern int OSResetSystem(int reset, u32 resetCode, int forceMenu);
extern u32 ARGetDMAStatus(void);
extern void ARStartDMA(u32 type, u32 mainmem, u32 aram, u32 length);
extern u16 __ARGetInterruptStatus(void);
extern void __ARClearInterrupt(void);
extern void* TRK_memcpy(void* dest, const void* src, unsigned long count);
extern void TRK_flush_cache(u32, int);
extern int InitMetroTRKCommTable(int);
extern void TRK_main(void);
extern void TRKSaveExtended1Block(void);
extern void EnableEXI2Interrupts(void);
extern u8 gTRKInterruptVectorTable[];
extern u8 _db_stack_addr[];
extern u32 __TRK_get_MSR(void);
u32 TRKTargetTranslate(u32 addr);

#define DCBI(ofs, ptr) asm { dcbi ofs, ptr }
#define DCBI0(ptr) asm { dcbi r0, ptr }
#define DCBF(ofs, ptr) asm { dcbf ofs, ptr }
#define DCBF0(ptr) asm { dcbf r0, ptr }

static u32 lc_base;

static const u32 TRK_ISR_OFFSETS[15] = {
    0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500,
    0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000C00,
    0x00000D00, 0x00000F00, 0x00001300, 0x00001400, 0x00001700,
};

__declspec(section ".init") void __TRK_reset(void) {
    OSResetSystem(0, 0, 0);
}

asm void InitMetroTRK() {
    // clang-format ofs
    nofralloc
    subi r1, r1, 0x4
    stw r3, 0x0(r1)
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    stmw r0, 0x0(r3)
    lwz r4, 0x0(r1)
    addi r1, r1, 0x4
    stw r1, 0x4(r3)
    stw r4, 0xc(r3)
    mflr r4
    stw r4, 0x84(r3)
    stw r4, 0x80(r3)
    mfcr r4
    stw r4, 0x88(r3)
    mfmsr r4
    ori r3, r4, 0x8000
    xori r3, r3, 0x8000
    mtmsr r3
    mtsrr1 r4
    bl TRKSaveExtended1Block
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    lmw r0, 0(r3)
    li r0, 0x0
    mtspr IABR, r0
    mtspr DABR, r0
    lis r1, _db_stack_addr@h
    ori r1, r1, _db_stack_addr@l
    mr r3, r5
    bl InitMetroTRKCommTable
    cmpwi r3, 0x1
    bne L_84A0
    lwz r4, 0x84(r3)
    mtlr r4
    lmw r0, 0(r3)
    blr
L_84A0:
    b TRK_main
    // clang-format on
}

asm void InitMetroTRK_BBA() {
    // clang-format ofs
    nofralloc
    subi r1, r1, 0x4
    stw r3, 0x0(r1)
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    stmw r0, 0x0(r3)
    lwz r4, 0x0(r1)
    addi r1, r1, 0x4
    stw r1, 0x4(r3)
    stw r4, 0xc(r3)
    mflr r4
    stw r4, 0x84(r3)
    stw r4, 0x80(r3)
    mfcr r4
    stw r4, 0x88(r3)
    mfmsr r4
    ori r3, r4, 0x8000
    mtmsr r3
    mtsrr1 r4
    bl TRKSaveExtended1Block
    lis r3, gTRKCPUState@h
    ori r3, r3, gTRKCPUState@l
    lmw r0, 0(r3)
    li r0, 0x0
    mtspr IABR, r0
    mtspr DABR, r0
    lis r1, _db_stack_addr@h
    ori r1, r1, _db_stack_addr@l
    li r3, 0x2
    bl InitMetroTRKCommTable
    cmpwi r3, 0x1
    bne L_8534
    lwz r4, 0x84(r3)
    mtlr r4
    lmw r0, 0(r3)
    blr
L_8534:
    b TRK_main
    blr
    // clang-format on
}

void TRK__write_aram(register u8* src, u32 aram, u32* len) {
    u8 buf[0x20] __attribute__((aligned(32)));
    u16 intr;
    register u8* bp;
    u32 start;
    u32 size;
    register u8* dp;
    register u32 ofs;
    u32 end;
    u32 tail;

    if (aram < 0x4000 || (aram + *len) > 0x8000000) {
        return;
    }
    start = aram & ~0x1F;
    size = *len + (aram & 0x1F);
    size = (size + 0x1F) & ~0x1F;
    ofs = 0;
    for (; ofs < size; ofs += 0x20) {
        DCBF(ofs, src);
    }
    while (ARGetDMAStatus() != 0) {
    }
    intr = __ARGetInterruptStatus();
    ofs = aram & 0x1F;
    dp = (u8*)0x8000000;
    if (ofs != 0) {
        bp = buf;
        dp = (u8*)start;
        DCBI0(bp);
        __ARClearInterrupt();
        ARStartDMA(1, (u32)bp, start, 0x20);
        while (__ARGetInterruptStatus() == 0) {
        }
        TRK_memcpy(src, buf, ofs);
        DCBF0(src);
    }
    end = aram + *len;
    ofs = end & 0x1F;
    if (ofs != 0) {
        tail = end & ~0x1F;
        if (tail != (u32)dp) {
            bp = buf;
            DCBI0(bp);
            __ARClearInterrupt();
            ARStartDMA(1, (u32)bp, tail, 0x20);
            while (__ARGetInterruptStatus() == 0) {
            }
        }
        dp = src + end;
        TRK_memcpy(dp, buf + ofs, 0x20 - ofs);
        DCBF0(dp);
    }
    __sync();
    __ARClearInterrupt();
    ARStartDMA(0, (u32)src, start, size);
    if (intr == 0) {
        while (__ARGetInterruptStatus() == 0) {
        }
        __ARClearInterrupt();
    }
}

void TRK__read_aram(register u8* dst, u32 aram, u32* len) {
    register u32 ofs;
    u32 start, size, nlines, i;
    u16 intr;

    if (aram < 0x4000 || (aram + *len) > 0x8000000) {
        return;
    }
    start = aram & ~0x1F;
    size = *len + (aram & 0x1F);
    size = (size + 0x1F) & ~0x1F;
    ofs = 0;
    for (; ofs < size; ofs += 0x20) {
            DCBI(ofs, dst);
    }
    while (ARGetDMAStatus() != 0) {
    }
    intr = __ARGetInterruptStatus();
    __ARClearInterrupt();
    ARStartDMA(1, (u32)dst, start, size);
    while (__ARGetInterruptStatus() == 0) {
    }
    if (intr == 0) {
        __ARClearInterrupt();
    }
}

int TRKInitializeTarget(void) {
    gTRKState.isStopped = 1;
    gTRKState.msr = __TRK_get_MSR();
    lc_base = 0xE0000000;
    return 0;
}

void __TRK_copy_vectors(void) {
    int i;
    u32 mask;
    u32 dest;
    u32 offset;
    u32* p;

    if (lc_base <= 0x44 && lc_base + 0x4000 > 0x44 && (gTRKCPUState.Extended1.DBAT3U & 3)) {
        p = (u32*)0x44;
    } else {
        p = (u32*)0x80000044;
    }
    mask = *p;
    for (i = 0; i <= 14; i++) {
        if ((mask & (1 << i)) && i != 4) {
            offset = TRK_ISR_OFFSETS[i];
            dest = TRKTargetTranslate(offset);
            TRK_memcpy((void*)dest, gTRKInterruptVectorTable + offset, 0x100);
            TRK_flush_cache(dest, 0x100);
        }
    }
}

u32 TRKTargetTranslate(u32 addr) {
    if (addr >= lc_base && addr < lc_base + 0x4000 && (gTRKCPUState.Extended1.DBAT3U & 3)) {
        return addr;
    }
    if (addr >= 0x7E000000 && addr <= 0x80000000) {
        return addr;
    }
    return (addr & 0x3FFFFFFF) | 0x80000000;
}

void EnableMetroTRKInterrupts(void) {
    EnableEXI2Interrupts();
}
