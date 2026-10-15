#include <types.h>

extern u8 gTRKCPUState[];
extern u8 gTRKRestoreFlags[];

asm void TRKSaveExtended1Block() {
    // clang-format off
    nofralloc
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    mfsr r16, 0
    mfsr r17, 1
    mfsr r18, 2
    mfsr r19, 3
    mfsr r20, 4
    mfsr r21, 5
    mfsr r22, 6
    mfsr r23, 7
    mfsr r24, 8
    mfsr r25, 9
    mfsr r26, 10
    mfsr r27, 11
    mfsr r28, 12
    mfsr r29, 13
    mfsr r30, 14
    mfsr r31, 15
    stmw r16, 0x1a8(r2)
    mftb r10, 268
    mftb r11, 269
    mfspr r12, 1008
    mfspr r13, 1009
    mfsrr1 r14
    mfspr r15, 287
    mfibatu r16, 0
    mfibatl r17, 0
    mfibatu r18, 1
    mfibatl r19, 1
    mfibatu r20, 2
    mfibatl r21, 2
    mfibatu r22, 3
    mfibatl r23, 3
    mfdbatu r24, 0
    mfdbatl r25, 0
    mfdbatu r26, 1
    mfdbatl r27, 1
    mfdbatu r28, 2
    mfdbatl r29, 2
    mfdbatu r30, 3
    mfdbatl r31, 3
    stmw r10, 0x1e8(r2)
    mfsdr1 r22
    mfdar r23
    mfdsisr r24
    mfsprg r25, 0
    mfsprg r26, 1
    mfsprg r27, 2
    mfsprg r28, 3
    li r29, 0x0
    mfspr r30, 1010
    mfear r31
    stmw r22, 0x25c(r2)
    mfspr r20, 912
    mfspr r21, 913
    mfspr r22, 914
    mfspr r23, 915
    mfspr r24, 916
    mfspr r25, 917
    mfspr r26, 918
    mfspr r27, 919
    mfspr r28, 920
    mfspr r29, 921
    mfspr r30, 922
    mfspr r31, 923
    stmw r20, 0x2fc(r2)
    b L_81F0
    mfspr r16, 928
    mfspr r17, 935
    mfspr r18, 936
    mfspr r19, 937
    mfspr r20, 938
    mfspr r21, 939
    mfspr r22, 940
    mfspr r23, 941
    mfspr r24, 942
    mfspr r25, 943
    mfspr r26, 944
    mfspr r27, 951
    mfspr r28, 959
    mfspr r29, 1014
    mfspr r30, 1015
    mfspr r31, 1023
    stmw r16, 0x2b8(r2)
L_81F0:
    mfspr r19, 1013
    mfspr r20, 953
    mfspr r21, 954
    mfspr r22, 957
    mfspr r23, 958
    mfspr r24, 955
    mfspr r25, 952
    mfspr r26, 956
    mfspr r27, 1020
    mfspr r28, 1021
    mfspr r29, 1022
    mfspr r30, 1019
    mfspr r31, 1017
    stmw r19, 0x284(r2)
    blr
    mfspr r25, 976
    mfspr r26, 977
    mfspr r27, 978
    mfspr r28, 979
    mfspr r29, 980
    mfspr r30, 981
    mfspr r31, 982
    stmw r25, 0x240(r2)
    mfdec r31
    stw r31, 0x278(r2)
    blr
    // clang-format on
}

asm void TRKRestoreExtended1Block() {
    // clang-format off
    nofralloc
    lis r2, gTRKCPUState@h
    ori r2, r2, gTRKCPUState@l
    lis r5, gTRKRestoreFlags@h
    ori r5, r5, gTRKRestoreFlags@l
    lbz r3, 0x0(r5)
    lbz r6, 0x1(r5)
    li r0, 0x0
    stb r0, 0x0(r5)
    stb r0, 0x1(r5)
    cmpwi r3, 0x0
    beq L_8294
    lwz r24, 0x1e8(r2)
    lwz r25, 0x1ec(r2)
    mttbl r24
    mttbu r25
L_8294:
    lmw r20, 0x2fc(r2)
    mtspr 912, r20
    mtspr 913, r21
    mtspr 914, r22
    mtspr 915, r23
    mtspr 916, r24
    mtspr 917, r25
    mtspr 918, r26
    mtspr 919, r27
    mtspr 920, r28
    mtspr 922, r30
    mtspr 923, r31
    b L_82E0
    lmw r26, 0x2e0(r2)
    mtspr 944, r26
    mtspr 951, r27
    mtspr 1014, r29
    mtspr 1015, r30
    mtspr 1023, r31
L_82E0:
    lmw r19, 0x284(r2)
    mtspr 1013, r19
    mtspr 953, r20
    mtspr 954, r21
    mtspr 957, r22
    mtspr 958, r23
    mtspr 955, r24
    mtspr 952, r25
    mtspr 956, r26
    mtspr 1020, r27
    mtspr 1021, r28
    mtspr 1022, r29
    mtspr 1019, r30
    mtspr 1017, r31
    b L_834C
    cmpwi r6, 0x0
    beq L_832C
    lwz r26, 0x278(r2)
    mtdec r26
L_832C:
    lmw r25, 0x240(r2)
    mtspr 976, r25
    mtspr 977, r26
    mtspr 978, r27
    mtspr 979, r28
    mtspr 980, r29
    mtspr 981, r30
    mtspr 982, r31
L_834C:
    lmw r16, 0x1a8(r2)
    mtsr 0, r16
    mtsr 1, r17
    mtsr 2, r18
    mtsr 3, r19
    mtsr 4, r20
    mtsr 5, r21
    mtsr 6, r22
    mtsr 7, r23
    mtsr 8, r24
    mtsr 9, r25
    mtsr 10, r26
    mtsr 11, r27
    mtsr 12, r28
    mtsr 13, r29
    mtsr 14, r30
    mtsr 15, r31
    lmw r12, 0x1f0(r2)
    mtspr 1008, r12
    mtspr 1009, r13
    mtsrr1 r14
    mtspr 287, r15
    mtibatu 0, r16
    mtibatl 0, r17
    mtibatu 1, r18
    mtibatl 1, r19
    mtibatu 2, r20
    mtibatl 2, r21
    mtibatu 3, r22
    mtibatl 3, r23
    mtdbatu 0, r24
    mtdbatl 0, r25
    mtdbatu 1, r26
    mtdbatl 1, r27
    mtdbatu 2, r28
    mtdbatl 2, r29
    mtdbatu 3, r30
    mtdbatl 3, r31
    lmw r22, 0x25c(r2)
    mtsdr1 r22
    mtdar r23
    mtdsisr r24
    mtsprg 0, r25
    mtsprg 1, r26
    mtsprg 2, r27
    mtsprg 3, r28
    mtspr 1010, r30
    mtear r31
    blr
    // clang-format on
}
