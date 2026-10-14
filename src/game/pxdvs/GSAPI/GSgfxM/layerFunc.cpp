#include "layer_private.h"

extern "C" {
void tunitFunc__10GSgfxLayerFUc14GSgfxTunitFunc(u8 *arg0, u8 arg1, u32 arg2) {
    s32 temp_r0;
    s32 temp_r0_2;
    s32 temp_r0_3;
    s32 temp_r0_4;
    s32 temp_r0_5;
    s32 temp_r4;
    s32 temp_r4_2;
    s32 temp_r4_3;
    u8 *temp_r10;
    u8 *temp_r10_2;
    u8 *temp_r11;
    u8 *temp_r11_2;
    u8 *temp_r12;
    u8 *temp_r12_2;
    u8 *temp_r29;
    u8 *temp_r29_2;
    u8 *temp_r30;
    u8 *temp_r31;
    u8 *temp_r7;
    u8 *temp_r7_2;
    u8 *temp_r8;
    u8 *temp_r8_2;
    u8 *temp_r9;
    u8 *temp_r9_2;

    switch (arg2) {
    case 0:
        temp_r0 = 1 << arg1;
        temp_r29 = arg0 + (arg1 * 0x14);
        temp_r9 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r29, 0x1170) = 0;
        layerField<s32>(temp_r29, 0x1174) = 0;
        layerField<s32>(temp_r29, 0x1178) = 0;
        layerField<s32>(temp_r29, 0x117C) = 1;
        layerField<s32>(temp_r29, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r0);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r0);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r9, 0xF70) = 0xF;
        layerField<s32>(temp_r9, 0xF74) = 0xA;
        layerField<s32>(temp_r9, 0xF78) = 8;
        layerField<s32>(temp_r9, 0xF7C) = 0xF;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r0);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r0);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r29, 0x12B0) = 0;
        layerField<s32>(temp_r29, 0x12B4) = 0;
        layerField<s32>(temp_r29, 0x12B8) = 0;
        layerField<s32>(temp_r29, 0x12BC) = 1;
        layerField<s32>(temp_r29, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r0);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r0);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r9, 0x1070) = 7;
        layerField<s32>(temp_r9, 0x1074) = 5;
        layerField<s32>(temp_r9, 0x1078) = 4;
        layerField<s32>(temp_r9, 0x107C) = 7;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r0);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r0);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 1:
        temp_r0_2 = 1 << arg1;
        temp_r29_2 = arg0 + (arg1 * 0x14);
        temp_r9_2 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r29_2, 0x1170) = 0;
        layerField<s32>(temp_r29_2, 0x1174) = 0;
        layerField<s32>(temp_r29_2, 0x1178) = 0;
        layerField<s32>(temp_r29_2, 0x117C) = 1;
        layerField<s32>(temp_r29_2, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r0_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r0_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r9_2, 0xF70) = 0xA;
        layerField<s32>(temp_r9_2, 0xF74) = 8;
        layerField<s32>(temp_r9_2, 0xF78) = 9;
        layerField<s32>(temp_r9_2, 0xF7C) = 0xF;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r0_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r0_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r29_2, 0x12B0) = 0;
        layerField<s32>(temp_r29_2, 0x12B4) = 0;
        layerField<s32>(temp_r29_2, 0x12B8) = 0;
        layerField<s32>(temp_r29_2, 0x12BC) = 1;
        layerField<s32>(temp_r29_2, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r0_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r0_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r9_2, 0x1070) = 7;
        layerField<s32>(temp_r9_2, 0x1074) = 7;
        layerField<s32>(temp_r9_2, 0x1078) = 7;
        layerField<s32>(temp_r9_2, 0x107C) = 5;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r0_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r0_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 2:
        temp_r0_3 = 1 << arg1;
        temp_r31 = arg0 + (arg1 * 0x14);
        temp_r10 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r31, 0x1170) = 0;
        layerField<s32>(temp_r31, 0x1174) = 0;
        layerField<s32>(temp_r31, 0x1178) = 0;
        layerField<s32>(temp_r31, 0x117C) = 1;
        layerField<s32>(temp_r31, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r0_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r0_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r10, 0xF70) = 0xA;
        layerField<s32>(temp_r10, 0xF74) = 0xC;
        layerField<s32>(temp_r10, 0xF78) = 8;
        layerField<s32>(temp_r10, 0xF7C) = 0xF;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r0_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r0_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r31, 0x12B0) = 0;
        layerField<s32>(temp_r31, 0x12B4) = 0;
        layerField<s32>(temp_r31, 0x12B8) = 0;
        layerField<s32>(temp_r31, 0x12BC) = 1;
        layerField<s32>(temp_r31, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r0_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r0_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r10, 0x1070) = 7;
        layerField<s32>(temp_r10, 0x1074) = 5;
        layerField<s32>(temp_r10, 0x1078) = 4;
        layerField<s32>(temp_r10, 0x107C) = 7;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r0_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r0_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 3:
        temp_r0_4 = 1 << arg1;
        temp_r11 = arg0 + (arg1 * 0x14);
        temp_r7 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r11, 0x1170) = 0;
        layerField<s32>(temp_r11, 0x1174) = 0;
        layerField<s32>(temp_r11, 0x1178) = 0;
        layerField<s32>(temp_r11, 0x117C) = 1;
        layerField<s32>(temp_r11, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r0_4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r0_4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r7, 0xF70) = 8;
        layerField<s32>(temp_r7, 0xF74) = 0xF;
        layerField<s32>(temp_r7, 0xF78) = 0xF;
        layerField<s32>(temp_r7, 0xF7C) = 0xF;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r0_4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r0_4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r11, 0x12B0) = 0;
        layerField<s32>(temp_r11, 0x12B4) = 0;
        layerField<s32>(temp_r11, 0x12B8) = 0;
        layerField<s32>(temp_r11, 0x12BC) = 1;
        layerField<s32>(temp_r11, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r0_4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r0_4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r7, 0x1070) = 4;
        layerField<s32>(temp_r7, 0x1074) = 7;
        layerField<s32>(temp_r7, 0x1078) = 7;
        layerField<s32>(temp_r7, 0x107C) = 7;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r0_4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r0_4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 4:
        temp_r0_5 = 1 << arg1;
        temp_r11_2 = arg0 + (arg1 * 0x14);
        temp_r7_2 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r11_2, 0x1170) = 0;
        layerField<s32>(temp_r11_2, 0x1174) = 0;
        layerField<s32>(temp_r11_2, 0x1178) = 0;
        layerField<s32>(temp_r11_2, 0x117C) = 1;
        layerField<s32>(temp_r11_2, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r0_5);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r0_5);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r7_2, 0xF70) = 0xA;
        layerField<s32>(temp_r7_2, 0xF74) = 0xF;
        layerField<s32>(temp_r7_2, 0xF78) = 0xF;
        layerField<s32>(temp_r7_2, 0xF7C) = 0xF;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r0_5);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r0_5);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r11_2, 0x12B0) = 0;
        layerField<s32>(temp_r11_2, 0x12B4) = 0;
        layerField<s32>(temp_r11_2, 0x12B8) = 0;
        layerField<s32>(temp_r11_2, 0x12BC) = 1;
        layerField<s32>(temp_r11_2, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r0_5);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r0_5);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r7_2, 0x1070) = 5;
        layerField<s32>(temp_r7_2, 0x1074) = 7;
        layerField<s32>(temp_r7_2, 0x1078) = 7;
        layerField<s32>(temp_r7_2, 0x107C) = 7;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r0_5);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r0_5);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 5:
        temp_r4 = 1 << arg1;
        temp_r12 = arg0 + (arg1 * 0x14);
        temp_r8 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r12, 0x1170) = 0;
        layerField<s32>(temp_r12, 0x1174) = 0;
        layerField<s32>(temp_r12, 0x1178) = 0;
        layerField<s32>(temp_r12, 0x117C) = 1;
        layerField<s32>(temp_r12, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r8, 0xF70) = 8;
        layerField<s32>(temp_r8, 0xF74) = 0xF;
        layerField<s32>(temp_r8, 0xF78) = 0xF;
        layerField<s32>(temp_r8, 0xF7C) = 0;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r12, 0x12B0) = 0;
        layerField<s32>(temp_r12, 0x12B4) = 0;
        layerField<s32>(temp_r12, 0x12B8) = 0;
        layerField<s32>(temp_r12, 0x12BC) = 1;
        layerField<s32>(temp_r12, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r8, 0x1070) = 4;
        layerField<s32>(temp_r8, 0x1074) = 7;
        layerField<s32>(temp_r8, 0x1078) = 7;
        layerField<s32>(temp_r8, 0x107C) = 0;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r4);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r4);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 6:
        temp_r4_2 = 1 << arg1;
        temp_r12_2 = arg0 + (arg1 * 0x14);
        temp_r8_2 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r12_2, 0x1170) = 0;
        layerField<s32>(temp_r12_2, 0x1174) = 0;
        layerField<s32>(temp_r12_2, 0x1178) = 0;
        layerField<s32>(temp_r12_2, 0x117C) = 1;
        layerField<s32>(temp_r12_2, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r4_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r4_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r8_2, 0xF70) = 0xA;
        layerField<s32>(temp_r8_2, 0xF74) = 0xF;
        layerField<s32>(temp_r8_2, 0xF78) = 0xF;
        layerField<s32>(temp_r8_2, 0xF7C) = 0;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r4_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r4_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r12_2, 0x12B0) = 0;
        layerField<s32>(temp_r12_2, 0x12B4) = 0;
        layerField<s32>(temp_r12_2, 0x12B8) = 0;
        layerField<s32>(temp_r12_2, 0x12BC) = 1;
        layerField<s32>(temp_r12_2, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r4_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r4_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r8_2, 0x1070) = 5;
        layerField<s32>(temp_r8_2, 0x1074) = 7;
        layerField<s32>(temp_r8_2, 0x1078) = 7;
        layerField<s32>(temp_r8_2, 0x107C) = 0;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r4_2);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r4_2);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        return;
    case 7:
        temp_r4_3 = 1 << arg1;
        temp_r30 = arg0 + (arg1 * 0x14);
        temp_r10_2 = arg0 + ((arg1 * 0x10) & 0xFF0);
        layerField<s32>(temp_r30, 0x1170) = 0;
        layerField<s32>(temp_r30, 0x1174) = 0;
        layerField<s32>(temp_r30, 0x1178) = 0;
        layerField<s32>(temp_r30, 0x117C) = 1;
        layerField<s32>(temp_r30, 0x1180) = 0;
        layerField<s32>(arg0, 0x16DC) = (s32) (layerField<s32>(arg0, 0x16DC) | temp_r4_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1794) = (s32) (layerField<s32>(arg0, 0x1794) | temp_r4_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r10_2, 0xF70) = 0xF;
        layerField<s32>(temp_r10_2, 0xF74) = 0xA;
        layerField<s32>(temp_r10_2, 0xF78) = 8;
        layerField<s32>(temp_r10_2, 0xF7C) = 0;
        layerField<s32>(arg0, 0x16D4) = (s32) (layerField<s32>(arg0, 0x16D4) | temp_r4_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x178C) = (s32) (layerField<s32>(arg0, 0x178C) | temp_r4_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r30, 0x12B0) = 0;
        layerField<s32>(temp_r30, 0x12B4) = 0;
        layerField<s32>(temp_r30, 0x12B8) = 0;
        layerField<s32>(temp_r30, 0x12BC) = 1;
        layerField<s32>(temp_r30, 0x12C0) = 0;
        layerField<s32>(arg0, 0x16E0) = (s32) (layerField<s32>(arg0, 0x16E0) | temp_r4_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1798) = (s32) (layerField<s32>(arg0, 0x1798) | temp_r4_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        layerField<s32>(temp_r10_2, 0x1070) = 7;
        layerField<s32>(temp_r10_2, 0x1074) = 5;
        layerField<s32>(temp_r10_2, 0x1078) = 4;
        layerField<s32>(temp_r10_2, 0x107C) = 0;
        layerField<s32>(arg0, 0x16D8) = (s32) (layerField<s32>(arg0, 0x16D8) | temp_r4_3);
        layerField<s32>(arg0, 0x16A8) = (s32) (layerField<s32>(arg0, 0x16A8) | 8);
        layerField<s32>(arg0, 0x1790) = (s32) (layerField<s32>(arg0, 0x1790) | temp_r4_3);
        layerField<s32>(arg0, 0x1760) = (s32) (layerField<s32>(arg0, 0x1760) | 8);
        /* fallthrough */
    default:
        return;
    }
}


}

extern "C" {
void SetDistortionParams__10GSgfxLayerFPA3_fSc(void* layer, float (*matrix)[3], s8 exponent) {
    float* out = &layerField<float>(layer, 0x19bc);
    out[0] = matrix[0][0]; out[1] = matrix[0][1]; out[2] = matrix[0][2];
    out[3] = matrix[1][0]; out[4] = matrix[1][1]; out[5] = matrix[1][2];
    layerField<s8>(layer, 0x19b8) = exponent;
}
void tokenMark__10GSgfxLayerFv(void* layer) {
    SetupFifo__10GSgfxLayerFv(layer); GSgfxTokenMark_Sub__Fv();
}
void tunitIndTexMtx__10GSgfxLayerF16GSgfxIndTexMtxIDPA3_fSc(GraphicsLayerState* layer, s32 id, float (*matrix)[3], s8 exponent) {
    SetupFifo__10GSgfxLayerFv(layer); GSgfx_GCWriteIndTexMtx(id,matrix,exponent);
    s32 saved = layer->blendIndex; u8 other = saved == 0;
    if (layerField<u32>(&layer->blendRecords[other],0) != 0) {
        selectLayerPass(layer,other); SetupFifo__10GSgfxLayerFv(layer);
        GSgfx_GCWriteIndTexMtx(id,matrix,exponent);
        selectLayerPass(layer,saved); SetupFifo__10GSgfxLayerFv(layer);
    }
}
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(GraphicsLayerState* layer,u8 unit,s32 function,s32 source,float (*matrix)[4],bool normalize,float (*post)[4]) {
    LayerTexGen& gen = layerField<LayerTexGen>(layer,0xc74+unit*0x18);
    u8 load=0; gen.function=function; gen.source=source; gen.normalize=normalize; gen.reserved=0;
    if (!matrix) gen.matrix=0x3c; else { load=1; gen.matrix=unit*3+0x1e; }
    if (!post) gen.postMatrix=0x7d; else { load=1; gen.postMatrix=unit*3+0x40; }
    if (load==1) {
        SetupFifo__10GSgfxLayerFv(layer);
        if (matrix) GXLoadTexMtxImm(matrix,gen.matrix,function==1 ? GX_MTX2x4 : GX_MTX3x4);
        // The original intentionally passes matrix for the post-matrix load too.
        if (post) GXLoadTexMtxImm(matrix,gen.postMatrix,GX_MTX3x4);
        s32 saved=layer->blendIndex; u8 other=saved==0;
        if (layerField<u32>(&layer->blendRecords[other],0)!=0) {
            selectLayerPass(layer,other); SetupFifo__10GSgfxLayerFv(layer);
            if (matrix) GXLoadTexMtxImm(matrix,gen.matrix,function==1 ? GX_MTX2x4 : GX_MTX3x4);
            if (post) GXLoadTexMtxImm(matrix,gen.postMatrix,GX_MTX3x4);
            selectLayerPass(layer,saved); SetupFifo__10GSgfxLayerFv(layer);
        }
    }
    s32 mask=1<<unit;
    layerField<u32>(layer,0x16b0)|=mask; layer->dirty|=1;
    layerField<u32>(layer,0x1768)|=mask; layer->savedDirty|=1;
}
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(GraphicsLayerState* layer,u8 unit,s32 alpha,s32 ambient,s32 material,u32 count,void** lights,s32 attenuation,s32 diffuse) {
    s32 alphaUnit=unit+2; u8 enabled=0;
    if (lights && count) enabled=1;
    if (!enabled) { attenuation=2; diffuse=0; } else if (!attenuation) diffuse=0;
    if (alpha==0 || alpha==2) {
        LayerChannel& channel=layerField<LayerChannel>(layer,0xdbc+unit*0x38);
        channel.enabled=enabled; channel.ambient=ambient; channel.material=material;
        channel.mask=0; channel.diffuse=diffuse; channel.attenuation=attenuation;
        if (enabled) for (u32 i=0;i<8;i++) channel.lights[i]=i<count ? lights[i] : 0;
        else memset(channel.lights,0,0x20);
        s32 mask=1<<unit; layerField<u32>(layer,0x16c0)|=mask; layerField<u32>(layer,0x1778)|=mask;
    }
    if (alpha==1 || alpha==2) {
        LayerChannel& channel=layerField<LayerChannel>(layer,0xdbc+alphaUnit*0x38);
        channel.enabled=enabled; channel.ambient=ambient; channel.material=material;
        channel.mask=0; channel.diffuse=diffuse; channel.attenuation=attenuation;
        // Both branches write the light list for the color unit in the original.
        LayerChannel& color=layerField<LayerChannel>(layer,0xdbc+unit*0x38);
        if (enabled) for (u32 i=0;i<8;i++) color.lights[i]=i<count ? lights[i] : 0;
        else memset(color.lights,0,0x20);
        s32 mask=1<<alphaUnit; layerField<u32>(layer,0x16c0)|=mask; layerField<u32>(layer,0x1778)|=mask;
    }
    layer->dirty|=4; layer->savedDirty|=4;
}
void drawSphere__10GSgfxLayerFUc(void* layer,u8 rings) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawSphere1(rings); InvalidateState__10GSgfxLayerFv(layer);
}
void drawSphere__10GSgfxLayerFUcUc(void* layer,u8 a,u8 b) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawSphere(b,a); InvalidateState__10GSgfxLayerFv(layer);
}
void drawTorus__10GSgfxLayerFfUcUc(void* layer,float radius,u8 a,u8 b) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawTorus(radius,a,b); InvalidateState__10GSgfxLayerFv(layer);
}
void drawCylinder__10GSgfxLayerFUc(void* layer,u8 sides) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawCylinder(sides); InvalidateState__10GSgfxLayerFv(layer);
}
void drawOctahedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawOctahedron(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawIcosahedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawIcosahedron(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawDodecaedron__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawDodeca(); InvalidateState__10GSgfxLayerFv(layer);
}
void drawCube__10GSgfxLayerFv(void* layer) {
    FlushState__10GSgfxLayerFv(layer);
    GXSetVtxDescv(layerField<LayerVertexFormat*>(layer,0x199c)->descriptors);
    GXDrawCube(); InvalidateState__10GSgfxLayerFv(layer);
}
void dlDraw__10GSgfxLayerFP7GSgfxDL(void* layer,LayerDisplayList* list) {
    if (list->flags&2) { DCStoreRange(list->data,list->size); list->flags&=~2; }
    LayerVertexFormat* saved=layerField<LayerVertexFormat*>(layer,0x199c);
    layerField<LayerVertexFormat*>(layer,0x199c)=list->format;
    FlushState__10GSgfxLayerFv(layer);
    u32 size=list->size; void* data=list->data;
    *(volatile u8*)0xcc008000=0x40;
    *(void* volatile*)0xcc008000=data;
    *(volatile u32*)0xcc008000=size;
    layerField<LayerVertexFormat*>(layer,0x199c)=saved;
}
void dlDrawExt__10GSgfxLayerFPUcUl(void* layer,u8* data,u32 size) {
    layerField<LayerVertexFormat*>(layer,0x199c)->format=0;
    FlushState__10GSgfxLayerFv(layer);
    *(volatile u8*)0xcc008000=0x40;
    *(volatile u32*)0xcc008000=(u32)data;
    *(volatile u32*)0xcc008000=size;
}
void endSurface__10GSgfxLayerFv(void*) { gsgfx_layer_inPrimitive=0; }
void beginSurface__10GSgfxLayerFUs(GraphicsLayerState* layer,u16 vertices) {
    FlushState__10GSgfxLayerFv(layer);
    *(volatile u8*)0xcc008000=layer->primitiveType|layerField<LayerVertexFormat*>(layer,0x199c)->format;
    *(volatile u16*)0xcc008000=vertices; gsgfx_layer_inPrimitive=1;
}
}
