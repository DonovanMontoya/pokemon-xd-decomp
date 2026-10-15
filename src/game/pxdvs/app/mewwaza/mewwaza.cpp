#include <game/pxdvs/app/mewwaza/mewwazaPrivate.hpp>
extern "C" {
static s32 mewans1[3] = { 0xC6FC, 0xC6FD, 0xC6FE };
static s32 mewans2[4] = { 0xC700, 0xC701, 0xC702, 0xC703 };
static s32 mewans3[4] = { 0xC705, 0xC706, 0xC707, 0xC708 };
static s32 mewques4[3] = { 0xC709, 0xC70C, 0xC70F };
static s32 mewques5[5] = { 0xC712, 0xC715, 0xC718, 0xC71B, 0xC71E };
static AnswerPair mewans4[3] = { { 0xC70B, 0xC70A }, { 0xC70D, 0xC70E }, { 0xC710, 0xC711 } };
static AnswerPair mewans5[5] = {
    { 0xC713, 0xC714 },
    { 0xC716, 0xC717 },
    { 0xC71A, 0xC719 },
    { 0xC71C, 0xC71D },
    { 0xC71F, 0xC720 },
};
static WazaTemplate _wrktmplt;
MEWPOINTS mewPoints;


u16 mewWazaGet(s32 arg0) {
    return _wrktmplt.moves[arg0];
}

s8 mewWazaSequence(void) {
    s8 temp_r31;
    u32 temp_r3;

    temp_r3 = GSfloorGetCurrent();
    if (temp_r3 != 0x15U) {
        GSfsysReadWait(0x9EF);
        msgctrlSetValue(0x59, 0x1772);
    }
    temp_r31 = _mewSequence__FP9MEWPOINTS(&mewPoints);
    if (temp_r3 != 0x15U) {
        GSresFreeGroup(0x9EF);
    }
    return temp_r31;
}

s32 _searchwaza__FP5MWAZAlPUsll(MWAZA *arg0, s32 arg1, u16 *arg2, s32 arg3, s32 arg4) {
    u16 temp_r8;
    u16 var_r9;
    s32 var_r10;
    s32 var_r8;
    MWAZA *var_r3;

    var_r3 = arg0;
    var_r9 = 0;
    var_r10 = 0;
loop_1:
    temp_r8 = var_r3->unk0;
    if (temp_r8 == 0) {
        return var_r10;
    }
    switch (arg1) {                                 /* irregular */
    case 0x800F:
        var_r9 = temp_r8;
        break;
    case 0x800C:
        if (var_r3->unk2 & 0xC) {
            var_r9 = temp_r8;
        }
        break;
    case 0x8008:
        if (var_r3->unk2 & 8) {
            var_r9 = temp_r8;
        }
        break;
    case 0x8004:
        if (var_r3->unk2 & 4) {
            var_r9 = temp_r8;
        }
        break;
    case 0x8002:
        if (var_r3->unk2 & 2) {
            var_r9 = temp_r8;
        }
        break;
    case 0x8102:
        if (!(var_r3->unk2 & 2)) {
            var_r9 = temp_r8;
        }
        break;
    case 0x8001:
        if (var_r3->unk2 & 1) {
            var_r9 = temp_r8;
        }
        break;
    }
    if (var_r9 != 0) {
        var_r8=0;
        for(s32 i=0;i<arg3;i++){
            if(var_r9==*(u16*)((u8*)arg2+var_r8)){var_r9=0;break;}
            var_r8+=2;
        }
        if (var_r9 != 0) {
            var_r10 += 1;
            if ((arg4 != 0) && (var_r10 == arg4)) {
                return var_r9;
            }
        }
        goto block_40;
    }
block_40:
    var_r9 = 0;
    var_r3 += 1;
    goto loop_1;
}

void fn_802A4BF0(void) {

}

s32 _fillTmplate__FPUsP9MEWPOINTS(u16 *arg0, MEWPOINTS *arg1) {
    s16 temp_r4;
    s32 var_r0;
    s32 var_r23;
    s32 var_r25;
    s32 var_r27;
    s32 var_r30;
    s32 var_r31;
    s32 var_r31_2;
    u16 temp_r3;
    MWAZA *var_r28;
    MWAZA *var_r29;

    temp_r4 = arg1->unk0;
    if (temp_r4 > 0xC) {
        var_r31 = temp_r4 - 0xC;
        var_r0 = 0x30;
    } else {
        var_r0 = temp_r4 * 4;
        var_r31 = 0;
    }
    var_r31_2 = var_r31 * 4;
    var_r27 = 0;
    var_r29 = mWazaTbl + (0x30 - var_r0);
    var_r30 = 0;
    var_r28 = var_r29;
    var_r25 = 0;
    do {
        if (*(u16*)((u8*)arg0 + var_r25) & 0x8000) {
loop_6:
            temp_r3 = _searchwaza__FP5MWAZAlPUsll(var_r28, (s32) *(u16*)((u8*)arg0 + var_r25), arg0, var_r30, 0);
            if (temp_r3 == 0) {
                if (var_r27 < 2) {
                    var_r28 = var_r29;
                    var_r27 += 1;
                } else {
                    *(u16*)((u8*)arg0 + var_r25) = 0x800F;
                    if (var_r29 != mWazaTbl) {
                        var_r29 -= 1;
                    }
                    var_r28 = var_r29;
                }
                goto loop_6;
            }
            var_r23 = (u32)HSD_Rand() % (((s32) temp_r3 / 2) + (((s32) temp_r3 / 8) + 1));
            if (var_r23 >= (s32) temp_r3) {
                var_r23 = 0;
            }
            if (var_r31_2 != 0) {
                if (var_r31_2 <= var_r23) {
                    var_r23 -= var_r31_2;
                    var_r31_2 = 0;
                } else {
                    var_r31_2 -= var_r23;
                    var_r23 = 0;
                }
            }
            *(u16*)((u8*)arg0 + var_r25) = _searchwaza__FP5MWAZAlPUsll(var_r28, (s32) *(u16*)((u8*)arg0 + var_r25), arg0, var_r30, var_r23 + 1);
            var_r28 += var_r23 + 1;
        }
        var_r30 += 1;
        var_r25 += 2;
    } while (var_r30 < 4);
    return 0;
}

WazaTemplate *_getWazaFromTmpl__FlP9MEWPOINTS(s32 arg0, MEWPOINTS *arg1) {
    s16 temp_r3;
    s32 temp_r5;
    s32 temp_r5_2;
    s32 var_r29;
    s32 var_r29_2;
    s32 var_r29_3;
    s32 var_r6;
    s32 var_r6_2;
    u16 var_r30;
    WazaTemplate *temp_r31;
    WazaTemplate *var_r3;
    WazaTemplate *var_r3_2;
    WazaTemplate *var_r4;
    WazaTemplate *var_r4_2;

    temp_r31 = wazaTmplTbl[arg0];
    switch (arg0) {                                 /* irregular */
    case 0:
        temp_r3 = arg1->unk2;
        if ((temp_r3 > (s16) arg1->unk6) && (temp_r3 >= 0)) {
            var_r30 = 3;
        } else if (temp_r3 >= 0) {
            var_r30 = 2;
        } else {
            var_r30 = 1;
        }
        var_r29 = 0x64;
        if (((s32) arg1->unk8 == 1) && ((u32) ((u32)HSD_Rand() % 100) < 0x1EU)) {
            return temp_r31 + (((u32)HSD_Rand() % 3) + 10);
        }
        if (((s32) arg1->unk8 == 2) && ((u32) ((u32)HSD_Rand() % 100) < 0x1EU)) {
            return temp_r31 + (((u32)HSD_Rand() % 3) + 7);
        }
    default:
block_25:
        if ((var_r29 == 0x64) || (var_r29 > (s32) ((u32)HSD_Rand() % 100))) {
            var_r4 = temp_r31;
            var_r29_2 = 0;
loop_31:
            if ((u16) var_r4->unk0 != 0) {
                if ((u16) var_r4->unk2 == var_r30) {
                    var_r29_2 += 1;
                }
                var_r4 += 1;
                goto loop_31;
            }
            if (var_r29_2 == 0) {
                return 0;
            }
            var_r3_2 = temp_r31;
            var_r6 = 0;
            temp_r5 = (u32)HSD_Rand() % var_r29_2;
loop_40:
            if ((u16) var_r3_2->unk0 == 0) {
                return 0;
            }
            if ((u16) var_r3_2->unk2 == var_r30) {
                if (var_r6 == temp_r5) {
                    return var_r3_2;
                }
                var_r6 += 1;
                goto block_39;
            }
block_39:
            var_r3_2 += 1;
            goto loop_40;
        }
        var_r4_2 = temp_r31;
        var_r29_3 = 0;
loop_46:
        if ((u16) var_r4_2->unk0 != 0) {
            if ((u16) var_r4_2->unk2 != var_r30) {
                var_r29_3 += 1;
            }
            var_r4_2 += 1;
            goto loop_46;
        }
        if (var_r29_3 == 0) {
            return 0;
        }
        var_r3 = temp_r31;
        var_r6_2 = 0;
        temp_r5_2 = (u32)HSD_Rand() % var_r29_3;
loop_55:
        if ((u16) var_r3->unk0 == 0) {
            return 0;
        }
        if ((u16) var_r3->unk2 != var_r30) {
            if (var_r6_2 == temp_r5_2) {
                return var_r3;
            }
            var_r6_2 += 1;
            goto block_54;
        }
block_54:
        var_r3 += 1;
        goto loop_55;
    case 1:
        var_r30 = 1;
        var_r29 = 0x3C;
        goto block_25;
    case 5:
    case 2:
        var_r30 = 1;
        var_r29 = 0x64;
        goto block_25;
    case 3:
        var_r30 = 1;
        var_r29 = 0x46;
        goto block_25;
    case 4:
        var_r30 = 1;
        var_r29 = 0x46;
        goto block_25;
    }
}

s32 _tmplSelect__FP9MEWPOINTS(MEWPOINTS *arg0) {
    s32 first,second,third;
    u8 order[3];
    s32 points[3];
    order[0]='A';
    first=arg0->unk2;second=arg0->unk4;third=arg0->unk6;
    points[0]=first;points[1]=second;points[2]=third;
    order[1]='S';
    order[2]='B';
    s32 var_r4_2,var_r4_3,var_r4_4;
    for(s32 i=0;i<2;i++)for(s32 j=i+1;j<3;j++)if(points[i]<points[j]){s32 t=points[i];points[i]=points[j];points[j]=t;u8 c=order[i];order[i]=order[j];order[j]=c;}
    if(order[0]=='S'&&points[0]!=points[1])return 0;
    if(order[0]=='B'&&points[0]!=points[1])return 1;
    if(order[0]=='A'&&points[0]!=points[1]){if(order[2]=='B'&&points[1]>points[2]&&points[2]<=0)return 2;return 3;}
    if(order[2]=='S'&&points[0]==points[1]&&points[0]>points[2])return 3;
    if(order[2]=='B'&&points[0]==points[1]&&points[0]>points[2])return 2;
    if(order[2]=='A'&&points[0]==points[1]&&points[0]>points[2])return 4;
            var_r4_2 = arg0->unk2;
            if ((s16)var_r4_2 < 0) {
                var_r4_2 = -var_r4_2;
            }
            arg0->unk0 += var_r4_2;
            var_r4_3 = arg0->unk4;
            if ((s16)var_r4_3 < 0) {
                var_r4_3 = -var_r4_3;
            }
            arg0->unk0 += var_r4_3;
            var_r4_4 = arg0->unk6;
            if ((s16)var_r4_4 < 0) {
                var_r4_4 = -var_r4_4;
            }
            arg0->unk0 += var_r4_4;
            return 5;
}

void _question_5__FP9MEWPOINTS(MEWPOINTS *arg0) {
    s32 answers[2];
    s16 temp_r4;
    s16 temp_r4_2;
    s16 temp_r4_3;
    s16 temp_r4_4;
    s16 temp_r4_5;
    s32 var_r0;
    s32 var_r0_10;
    s32 var_r0_11;
    s32 var_r0_12;
    s32 var_r0_13;
    s32 var_r0_14;
    s32 var_r0_15;
    s32 var_r0_16;
    s32 var_r0_17;
    s32 var_r0_18;
    s32 var_r0_19;
    s32 var_r0_20;
    s32 var_r0_2;
    s32 var_r0_3;
    s32 var_r0_4;
    s32 var_r0_5;
    s32 var_r0_6;
    s32 var_r0_7;
    s32 var_r0_8;
    s32 var_r0_9;
    s32 var_r3;
    s32 var_r3_10;
    s32 var_r3_11;
    s32 var_r3_12;
    s32 var_r3_13;
    s32 var_r3_14;
    s32 var_r3_15;
    s32 var_r3_2;
    s32 var_r3_3;
    s32 var_r3_4;
    s32 var_r3_5;
    s32 var_r3_6;
    s32 var_r3_7;
    s32 var_r3_8;
    s32 var_r3_9;
    s32 var_r5;
    s32 var_r5_2;
    s32 var_r5_3;
    s32 var_r5_4;
    s32 var_r5_5;
    s32 temp_r28;
    s32 temp_r3;
    s32 temp_r6;
    s32 temp_r6_2;
    s32 temp_r6_3;
    s32 temp_r6_4;
    s32 temp_r6_5;
    u32 temp_ret;

    temp_ret = (u32)HSD_Rand();
    temp_r28 = temp_ret % 5;
    winMsgOpenFieldWithSE(mewques5[temp_r28], 1, 0, 1);
    answers[0] = mewans5[temp_r28].unk0;
    answers[1] = mewans5[temp_r28].unk4;
    do {
        temp_r3 = menuSubOpenSelect3(0, &answers[0], 2, 0x34, 0xD1, 0, 2, 1, 0);
    } while (temp_r3 < 0);
    winMsgClose(1);
    switch (temp_r28) {                             /* irregular */
    case 0:
        temp_r6 = (u32)HSD_Rand() % 487;
        if ((u8) temp_r3 == 0) {
            arg0->unk0 = (s16) ((s32) ((temp_r6 + 0x99) * arg0->unk0) >> 8);
        } else {
            temp_r4 = arg0->unk4;
            var_r3 = temp_r4;
            if (temp_r4 < 0) {
                var_r3 = -temp_r4;
            }
            var_r5 = arg0->unk2;
            var_r0 = var_r5;
            if (var_r5 < 0) {
                var_r0 = -var_r5;
            }
            if (var_r0 > var_r3) {
                var_r3_2 = arg0->unk6;
                if (var_r3_2 < 0) {
                    var_r3_2 = -var_r3_2;
                }
                var_r0_2 = var_r5;
                if (var_r5 < 0) {
                    var_r0_2 = -var_r5;
                }
                if (var_r0_2 > var_r3_2) {
                    arg0->unk2 = (s16) ((s32) ((temp_r6 + 0x99) * var_r5) >> 8);
                } else {
                    goto block_23;
                }
            } else {
block_23:
                if (var_r5 < 0) {
                    var_r5 = -var_r5;
                }
                var_r0_3 = temp_r4;
                if (temp_r4 < 0) {
                    var_r0_3 = -temp_r4;
                }
                if (var_r0_3 > var_r5) {
                    var_r3_3 = arg0->unk6;
                    if (var_r3_3 < 0) {
                        var_r3_3 = -var_r3_3;
                    }
                    var_r0_4 = temp_r4;
                    if (temp_r4 < 0) {
                        var_r0_4 = -temp_r4;
                    }
                    if (var_r0_4 > var_r3_3) {
                        arg0->unk4 = (s16) ((s32) ((temp_r6 + 0x99) * temp_r4) >> 8);
                    } else {
                        goto block_34;
                    }
                } else {
block_34:
                    arg0->unk6 = (s16) ((s32) ((temp_r6 + 0x99) * arg0->unk6) >> 8);
                }
            }
        }
        if ((u8) temp_r3 == 0) {
            arg0->unk8 = 1;
            return;
        }
        arg0->unk8 = 2;
        return;
    case 1:
        temp_r6_2 = (u32)HSD_Rand() % 384;
        if ((u8) temp_r3 == 0) {
            arg0->unk0 = (s16) ((s32) ((temp_r6_2 + 0xB3) * arg0->unk0) >> 8);
            return;
        }
        temp_r4_2 = arg0->unk4;
        var_r3_4 = temp_r4_2;
        if (temp_r4_2 < 0) {
            var_r3_4 = -temp_r4_2;
        }
        var_r5_2 = arg0->unk2;
        var_r0_5 = var_r5_2;
        if (var_r5_2 < 0) {
            var_r0_5 = -var_r5_2;
        }
        if (var_r0_5 > var_r3_4) {
            var_r3_5 = arg0->unk6;
            if (var_r3_5 < 0) {
                var_r3_5 = -var_r3_5;
            }
            var_r0_6 = var_r5_2;
            if (var_r5_2 < 0) {
                var_r0_6 = -var_r5_2;
            }
            if (var_r0_6 > var_r3_5) {
                arg0->unk2 = (s16) ((s32) ((temp_r6_2 + 0xB3) * var_r5_2) >> 8);
                return;
            }
            goto block_51;
        }
block_51:
        if (var_r5_2 < 0) {
            var_r5_2 = -var_r5_2;
        }
        var_r0_7 = temp_r4_2;
        if (temp_r4_2 < 0) {
            var_r0_7 = -temp_r4_2;
        }
        if (var_r0_7 > var_r5_2) {
            var_r3_6 = arg0->unk6;
            if (var_r3_6 < 0) {
                var_r3_6 = -var_r3_6;
            }
            var_r0_8 = temp_r4_2;
            if (temp_r4_2 < 0) {
                var_r0_8 = -temp_r4_2;
            }
            if (var_r0_8 > var_r3_6) {
                arg0->unk4 = (s16) ((s32) ((temp_r6_2 + 0xB3) * temp_r4_2) >> 8);
                return;
            }
            goto block_62;
        }
block_62:
        arg0->unk6 = (s16) ((s32) ((temp_r6_2 + 0xB3) * arg0->unk6) >> 8);
        return;
    case 2:
        temp_r6_3 = (u32)HSD_Rand() % 308;
        if ((u8) temp_r3 == 0) {
            arg0->unk0 = (s16) ((s32) ((temp_r6_3 + 0xCC) * arg0->unk0) >> 8);
            return;
        }
        temp_r4_3 = arg0->unk4;
        var_r3_7 = temp_r4_3;
        if (temp_r4_3 < 0) {
            var_r3_7 = -temp_r4_3;
        }
        var_r5_3 = arg0->unk2;
        var_r0_9 = var_r5_3;
        if (var_r5_3 < 0) {
            var_r0_9 = -var_r5_3;
        }
        if (var_r0_9 > var_r3_7) {
            var_r3_8 = arg0->unk6;
            if (var_r3_8 < 0) {
                var_r3_8 = -var_r3_8;
            }
            var_r0_10 = var_r5_3;
            if (var_r5_3 < 0) {
                var_r0_10 = -var_r5_3;
            }
            if (var_r0_10 > var_r3_8) {
                arg0->unk2 = (s16) ((s32) ((temp_r6_3 + 0xCC) * var_r5_3) >> 8);
                return;
            }
            goto block_76;
        }
block_76:
        if (var_r5_3 < 0) {
            var_r5_3 = -var_r5_3;
        }
        var_r0_11 = temp_r4_3;
        if (temp_r4_3 < 0) {
            var_r0_11 = -temp_r4_3;
        }
        if (var_r0_11 > var_r5_3) {
            var_r3_9 = arg0->unk6;
            if (var_r3_9 < 0) {
                var_r3_9 = -var_r3_9;
            }
            var_r0_12 = temp_r4_3;
            if (temp_r4_3 < 0) {
                var_r0_12 = -temp_r4_3;
            }
            if (var_r0_12 > var_r3_9) {
                arg0->unk4 = (s16) ((s32) ((temp_r6_3 + 0xCC) * temp_r4_3) >> 8);
                return;
            }
            goto block_87;
        }
block_87:
        arg0->unk6 = (s16) ((s32) ((temp_r6_3 + 0xCC) * arg0->unk6) >> 8);
        return;
    case 3:
        temp_r6_4 = (u32)HSD_Rand() % 204;
        if ((u8) temp_r3 == 0) {
            arg0->unk0 = (s16) ((s32) ((temp_r6_4 + 0x100) * arg0->unk0) >> 8);
            return;
        }
        temp_r4_4 = arg0->unk4;
        var_r3_10 = temp_r4_4;
        if (temp_r4_4 < 0) {
            var_r3_10 = -temp_r4_4;
        }
        var_r5_4 = arg0->unk2;
        var_r0_13 = var_r5_4;
        if (var_r5_4 < 0) {
            var_r0_13 = -var_r5_4;
        }
        if (var_r0_13 > var_r3_10) {
            var_r3_11 = arg0->unk6;
            if (var_r3_11 < 0) {
                var_r3_11 = -var_r3_11;
            }
            var_r0_14 = var_r5_4;
            if (var_r5_4 < 0) {
                var_r0_14 = -var_r5_4;
            }
            if (var_r0_14 > var_r3_11) {
                arg0->unk2 = (s16) ((s32) ((temp_r6_4 + 0x100) * var_r5_4) >> 8);
                return;
            }
            goto block_101;
        }
block_101:
        if (var_r5_4 < 0) {
            var_r5_4 = -var_r5_4;
        }
        var_r0_15 = temp_r4_4;
        if (temp_r4_4 < 0) {
            var_r0_15 = -temp_r4_4;
        }
        if (var_r0_15 > var_r5_4) {
            var_r3_12 = arg0->unk6;
            if (var_r3_12 < 0) {
                var_r3_12 = -var_r3_12;
            }
            var_r0_16 = temp_r4_4;
            if (temp_r4_4 < 0) {
                var_r0_16 = -temp_r4_4;
            }
            if (var_r0_16 > var_r3_12) {
                arg0->unk4 = (s16) ((s32) ((temp_r6_4 + 0x100) * temp_r4_4) >> 8);
                return;
            }
            goto block_112;
        }
block_112:
        arg0->unk6 = (s16) ((s32) ((temp_r6_4 + 0x100) * arg0->unk6) >> 8);
        return;
    case 4:
        temp_r6_5 = (u32)HSD_Rand() % 51;
        if ((u8) temp_r3 == 0) {
            arg0->unk0 = (s16) ((s32) ((temp_r6_5 + 0x133) * arg0->unk0) >> 8);
            return;
        }
        temp_r4_5 = arg0->unk4;
        var_r3_13 = temp_r4_5;
        if (temp_r4_5 < 0) {
            var_r3_13 = -temp_r4_5;
        }
        var_r5_5 = arg0->unk2;
        var_r0_17 = var_r5_5;
        if (var_r5_5 < 0) {
            var_r0_17 = -var_r5_5;
        }
        if (var_r0_17 > var_r3_13) {
            var_r3_14 = arg0->unk6;
            if (var_r3_14 < 0) {
                var_r3_14 = -var_r3_14;
            }
            var_r0_18 = var_r5_5;
            if (var_r5_5 < 0) {
                var_r0_18 = -var_r5_5;
            }
            if (var_r0_18 > var_r3_14) {
                arg0->unk2 = (s16) ((s32) ((temp_r6_5 + 0x133) * var_r5_5) >> 8);
                return;
            }
            goto block_126;
        }
block_126:
        if (var_r5_5 < 0) {
            var_r5_5 = -var_r5_5;
        }
        var_r0_19 = temp_r4_5;
        if (temp_r4_5 < 0) {
            var_r0_19 = -temp_r4_5;
        }
        if (var_r0_19 > var_r5_5) {
            var_r3_15 = arg0->unk6;
            if (var_r3_15 < 0) {
                var_r3_15 = -var_r3_15;
            }
            var_r0_20 = temp_r4_5;
            if (temp_r4_5 < 0) {
                var_r0_20 = -temp_r4_5;
            }
            if (var_r0_20 > var_r3_15) {
                arg0->unk4 = (s16) ((s32) ((temp_r6_5 + 0x133) * temp_r4_5) >> 8);
                return;
            }
            goto block_137;
        }
block_137:
        arg0->unk6 = (s16) ((s32) ((temp_r6_5 + 0x133) * arg0->unk6) >> 8);
        return;
    }
}

void _question_4__FP9MEWPOINTS(MEWPOINTS *arg0) {
    s16 factor;
    s16 base;
    s32 answers[2];
    s16 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3_4;
    s16 temp_r4_2;
    s16 temp_r4_3;
    s32 temp_r28;
    s32 temp_r3;
    u32 temp_ret;
    u32 temp_ret_2;
    u32 temp_ret_3;
    void *temp_r4;

    s32 interlude[5]={0xC727,0xC728,0xC729,0xC72A,0xC72C};
    temp_ret = (u32)HSD_Rand();
    winMsgOpenFieldWithSE(interlude[temp_ret % 5], 1, 0, 1);
    temp_ret_2 = (u32)HSD_Rand();
    temp_r28 = temp_ret_2 % 3;
    winMsgOpenFieldWithSE(mewques4[temp_r28], 1, 0, 1);
    answers[0] = mewans4[temp_r28].unk0;
    answers[1] = mewans4[temp_r28].unk4;
    do {
        temp_r3 = menuSubOpenSelect3(0, &answers[0], 2, 0x34, 0xD1, 0, 2, 1, 0);
    } while (temp_r3 < 0);
    winMsgClose(1);
    switch (temp_r28) {                             /* irregular */
    case 0:
        if ((u8) temp_r3 == 0) {
            arg0->unk6 = (s16) (arg0->unk6 - 3);
            arg0->unk0 *= 2;
            return;
        }
        temp_r3_2 = arg0->unk6;
        arg0->unk6 = (s16) (temp_r3_2 + 3);
        factor=(u32)HSD_Rand()%3;
        base=arg0->unk0;
        arg0->unk0 = base*(factor+1);
        return;
    case 1:
        if ((u8) temp_r3 == 0) {
            arg0->unk6 = (s16) (arg0->unk6 - ((s16) ((u32)HSD_Rand() % 3) + 2));
            arg0->unk0 *= 2;
            return;
        }
        temp_ret_3 = (u32)HSD_Rand();
        temp_r4_2 = arg0->unk6;
        temp_r3_3 = (s16) (temp_ret_3 % 3) + (s32)temp_r4_2;
        arg0->unk6 = (s16) (temp_r3_3 + 2);
        factor=(u32)HSD_Rand()%3;
        base=arg0->unk0;
        arg0->unk0 = base*(factor+1);
        return;
    case 2:
        if ((u8) temp_r3 == 0) {
            arg0->unk6 = (s16) (arg0->unk6 - (((u32)HSD_Rand() & 3) + 1));
            arg0->unk0 *= 2;
            return;
        }
        temp_r3_4 = ((u32)HSD_Rand() & 3) + arg0->unk6;
        arg0->unk6 = (s16) (temp_r3_4 + 1);
        factor=(u32)HSD_Rand()%3;
        base=arg0->unk0;
        arg0->unk0 = base*(factor+1);
        return;
    }
}

void _question_3__FP9MEWPOINTS(MEWPOINTS *arg0) {
    s32 answers[2];
    s32 temp_r3;
    u32 temp_ret;
    u32 temp_r29;
    u32 var_r28;
    u32 var_r30;
    void *temp_r4;

    s32 interlude[5]={0xC727,0xC728,0xC729,0xC72A,0xC72C};
    temp_ret = (u32)HSD_Rand();
    winMsgOpenFieldWithSE(interlude[temp_ret % 5], 1, 0, 1);
    winMsgOpenFieldWithSE(0xC704, 1, 0, 1);
    temp_r29 = (u32)HSD_Rand() & 3;
    var_r28 = temp_r29;
loop_2:
    if (var_r28 == temp_r29) {
        var_r28 = (u32)HSD_Rand() & 3;
        goto loop_2;
    }
    answers[0] = mewans3[temp_r29];
    answers[1] = mewans3[var_r28];
    do {
        temp_r3 = menuSubOpenSelect3(0, &answers[0], 2, 0x34, 0xD1, 0, 2, 1, 0);
    } while (temp_r3 < 0);
    var_r30 = var_r28;
    if (temp_r3 == 0) {
        var_r30 = temp_r29;
    }
    winMsgClose(1);
    switch ((s32) var_r30) {                        /* irregular */
    case 0:
        arg0->unk2 = (s16) (arg0->unk2 + 2);
        return;
    case 1:
        arg0->unk2 = (s16) ((s16) ((u32)HSD_Rand() % 3) + arg0->unk2 + 1);
        return;
    case 2:
        arg0->unk4 = (s16) ((s16) ((u32)HSD_Rand() % 3) + arg0->unk4 + 1);
        return;
    case 3:
        if ((u32) ((u32)HSD_Rand() % 10) < 5U) {
            arg0->unk2 = (s16) (arg0->unk2 - 2);
            return;
        }
        arg0->unk4 = (s16) (((s16) ((u32)HSD_Rand() % 5) + arg0->unk4) - 1);
        return;
    }
}

s8 _mewSequence__FP9MEWPOINTS(MEWPOINTS *arg0) {
    s32 firstAnswers[2];
    s32 secondAnswers[2];
    s16 temp_r28_3;
    s16 temp_r3_2;
    s32 temp_r3_3;
    s32 temp_r3;
    s32 temp_r3_4;
    s32 temp_r5;
    s8 temp_r29;
    u16 temp_r31;
    u32 temp_ret;
    u32 temp_r28;
    u32 temp_r28_2;
    u32 var_r29;
    u32 var_r29_2;
    WazaTemplate *temp_r3_5;
    void *temp_r4;

    heroMoveInitEvent();
    GSthreadSwitch();
    arg0->unk0 = 0;
    arg0->unk2 = 0;
    arg0->unk4 = 0;
    arg0->unk6 = 0;
    arg0->unk8 = 0;
    winMsgOpenFieldWithSE(0xC6FB, 1, 0, 1);
    temp_r28 = (u32)HSD_Rand() % 3;
    var_r29 = temp_r28;
loop_2:
    if (var_r29 == temp_r28) {
        var_r29 = (u32)HSD_Rand() % 3;
        goto loop_2;
    }
    firstAnswers[0] = mewans1[temp_r28];
    firstAnswers[1] = mewans1[var_r29];
    do {
        temp_r3 = menuSubOpenSelect3(0, &firstAnswers[0], 2, 0x34, 0xD1, 0, 2, 1, 0);
    } while (temp_r3 < 0);
    if (temp_r3 == 0) {
        var_r29 = temp_r28;
    }
    winMsgClose(1);
    switch ((s32) var_r29) {                        /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        temp_r3_2 = arg0->unk0;
        arg0->unk0 = temp_r3_2 + 2;
        arg0->unk4 = (s16) (((u32)HSD_Rand() % 3) + 1);
        break;
    case 1:                                         /* switch 1 */
        arg0->unk0 += 3;
        arg0->unk4 = 1;
        break;
    case 2:                                         /* switch 1 */
        temp_r3_3 = arg0->unk0;
        arg0->unk0 = temp_r3_3 + 4;
        arg0->unk4 = (s16) -(((u32)HSD_Rand() % 3) - 1);
        break;
    }
    s32 interlude[5]={0xC727,0xC728,0xC729,0xC72A,0xC72C};
    temp_ret = (u32)HSD_Rand();
    winMsgOpenFieldWithSE(interlude[temp_ret % 5], 1, 0, 1);
    winMsgOpenFieldWithSE(0xC6FF, 1, 0, 1);
    temp_r28_2 = (u32)HSD_Rand() & 3;
    var_r29_2 = temp_r28_2;
loop_18:
    if (var_r29_2 == temp_r28_2) {
        var_r29_2 = (u32)HSD_Rand() & 3;
        goto loop_18;
    }
    secondAnswers[0] = mewans2[temp_r28_2];
    secondAnswers[1] = mewans2[var_r29_2];
    do {
        temp_r3_4 = menuSubOpenSelect3(0, &secondAnswers[0], 2, 0x34, 0xD1, 0, 2, 1, 0);
    } while (temp_r3_4 < 0);
    if (temp_r3_4 == 0) {
        var_r29_2 = temp_r28_2;
    }
    winMsgClose(1);
    switch ((s32) var_r29_2) {                      /* switch 2; irregular */
    case 0:                                         /* switch 2 */
        arg0->unk2 = (s16) (arg0->unk2 + 2);
        break;
    case 1:                                         /* switch 2 */
        arg0->unk2 = (s16) (arg0->unk2 - 2);
        break;
    case 2:                                         /* switch 2 */
        arg0->unk6 = (s16) (arg0->unk6 + 3);
        break;
    case 3:                                         /* switch 2 */
        arg0->unk2 = (s16) (((u32)HSD_Rand() % 7) - 3);
        break;
    }
    _question_3__FP9MEWPOINTS(arg0);
    _question_4__FP9MEWPOINTS(arg0);
    _question_5__FP9MEWPOINTS(arg0);
    temp_r28_3 = arg0->unk6;
    if (temp_r28_3 > 0) {
        arg0->unk0 += ((u32)HSD_Rand() % ((temp_r28_3 * 2) + 1)) - arg0->unk6;
        if ((s16) arg0->unk0 < 0) {
            arg0->unk0 = 0;
        }
    }
    s32 selected=_tmplSelect__FP9MEWPOINTS(arg0);
    temp_r3_5 = _getWazaFromTmpl__FlP9MEWPOINTS(selected,arg0);
    if (temp_r3_5 == NULL) {
        return -1;
    }
    _wrktmplt = *temp_r3_5;
    if (_fillTmplate__FPUsP9MEWPOINTS(_wrktmplt.moves,arg0) != 0) {
        return -1;
    }
    winMsgOpenFieldWithSE(0xC721, 1, 0, 1);
    temp_r31 = menuMewWazaGetMenuDataID();
    winMsgClose(1);
    menuOpen(temp_r31, 0);
    temp_r29 = menuSubOpenYesNo(1, 0x196, 0xC0, 0);
    menuClose(temp_r31);
    menuCloseSync(temp_r31, 1);
    heroMoveTermEvent();
    return temp_r29;
}

}
