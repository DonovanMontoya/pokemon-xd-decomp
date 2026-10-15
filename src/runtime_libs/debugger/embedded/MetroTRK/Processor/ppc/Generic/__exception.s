# __exception.s
#
# MetroTRK PowerPC interrupt vector table. The table is copied over the real
# exception vectors by __TRK_copy_vectors, so every stub is position
# independent apart from the final jump to the common handler, and the
# entries are laid out at their architectural vector offsets.

.include "macros.inc"

.section .init, "ax"
.balign 4

# Common exception entry used by every stub (TRKInterruptHandler).
.set TRK_HANDLER_HI, 0x800d
.set TRK_HANDLER_LO, 0x6534

# Save SPRG1-3 scratch, load the vector number into r3 and rfi into the handler
# with translation off.
.macro TRK_VECTOR_ENTRY vec
    mtsprg 1, r2
    mtsprg 2, r3
    mtsprg 3, r4
    mfsrr0 r2
    mfsrr1 r4
    mfmsr r3
    ori r3, r3, 0x30
    mtsrr1 r3
    lis r3, TRK_HANDLER_HI
    ori r3, r3, TRK_HANDLER_LO
    mtsrr0 r3
    li r3, \vec
    rfi
.endm

# Instruction/data TLB miss vectors: clear MSR[TGPR] (swapped GPRs) first.
.macro TRK_TLB_VECTOR vec, skip
    mtsprg 1, r2
    mfcr r2
    mtsprg 2, r2
    mfmsr r2
    andis. r2, r2, 0x2
    beq \skip
    mfmsr r2
    xoris r2, r2, 0x2
    sync
    mtmsr r2
    sync
    mtsprg 1, r2
\skip:
    mfsprg r2, 2
    mtcrf 0xff, r2
    mfsprg r2, 1
    TRK_VECTOR_ENTRY \vec
.endm

.global gTRKInterruptVectorTable
gTRKInterruptVectorTable:
    .string "Metrowerks Target Resident Kernel for PowerPC"

.org 0x100
# 0x0100 System reset
    b . + 0x1e34

.org 0x200
# 0x0200 Machine check
    mtsprg 1, r2
    mfsrr0 r2
    icbi 0, r2
    mfdar r2
    dcbi 0, r2
    mfsprg r2, 1
    TRK_VECTOR_ENTRY 0x200

.org 0x300
    TRK_VECTOR_ENTRY 0x300   # DSI
.org 0x400
    TRK_VECTOR_ENTRY 0x400   # ISI
.org 0x500
    TRK_VECTOR_ENTRY 0x500   # External interrupt
.org 0x600
    TRK_VECTOR_ENTRY 0x600   # Alignment
.org 0x700
    TRK_VECTOR_ENTRY 0x700   # Program
.org 0x800
    TRK_VECTOR_ENTRY 0x800   # FP unavailable
.org 0x900
    TRK_VECTOR_ENTRY 0x900   # Decrementer
.org 0xc00
    TRK_VECTOR_ENTRY 0xc00   # System call
.org 0xd00
    TRK_VECTOR_ENTRY 0xd00   # Trace
.org 0xe00
    TRK_VECTOR_ENTRY 0xe00   # FP assist

.org 0xf00
# 0x0f00 Performance monitor
    b .L_vec_0F00
.org 0xf20
    TRK_VECTOR_ENTRY 0xf20
.L_vec_0F00:
    TRK_VECTOR_ENTRY 0xf00

.org 0x1000
    TRK_TLB_VECTOR 0x1000, .L_tlb_1000   # Instruction translation miss
.org 0x1100
    TRK_TLB_VECTOR 0x1100, .L_tlb_1100   # Data load translation miss
.org 0x1200
    TRK_TLB_VECTOR 0x1200, .L_tlb_1200   # Data store translation miss

.org 0x1300
    TRK_VECTOR_ENTRY 0x1300   # Instruction address breakpoint
.org 0x1400
    TRK_VECTOR_ENTRY 0x1400   # System management interrupt
.org 0x1600
    TRK_VECTOR_ENTRY 0x1600
.org 0x1700
    TRK_VECTOR_ENTRY 0x1700   # Thermal management interrupt
.org 0x1c00
    TRK_VECTOR_ENTRY 0x1c00
.org 0x1d00
    TRK_VECTOR_ENTRY 0x1d00
.org 0x1e00
    TRK_VECTOR_ENTRY 0x1e00
.org 0x1f00
    TRK_VECTOR_ENTRY 0x1f00
