#include <global.h>
struct Joutai { u16 unk0,unk2; u8 unk4,unk5,unk6,unk7; s32 unk8; u16 unkC; u16 pad; };
extern "C" {
u8 joutaiDataBiosGetWriteMode(u16); u8 joutaiDataBiosGetKaisuuDataId(u16); s32 kaisuuGetKaisuu(u32); u8 joutaiDataBiosGetMaxCount(u16); u16 joutaiDataBiosGetSameJoutai(u16); u8 joutaiDataBiosGetUseBanme(u16); s32 joutaiDataBiosGetStatusKind(u16); s32 joutaiDataBiosGetStatus(u16); Joutai *statusGetStatus(s32,void*,s32,s32,s32);
u8 joutaiBiosGetCount(Joutai*); u16 joutaiBiosGetJoutaiDataId(Joutai*);
s32 joutaiBiosGetBuff(Joutai*); s32 joutaiBiosGetIdBuff(Joutai*); s32 joutaiBiosGetUserFightTargetId(Joutai*); s32 joutaiBiosGetNowKaisuu(Joutai*); s32 joutaiBiosGetKaisuu(Joutai*);
void joutaiBiosSetBuff(Joutai*,s32); void joutaiBiosSetIdBuff(Joutai*,s32); void joutaiBiosSetNowKaisuu(Joutai*,s32);
void init__7_JOUTAIFv(Joutai*); u8 isValid__7_JOUTAIFv(Joutai*); u8 joutaiIsJoutaiDataId(void*,u16);
static Joutai *_joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(void*,u16); static void _joutaiInit__FP7_JOUTAI(Joutai*);
void writeJoutaiDataId__7_JOUTAIFUsUs(Joutai *arg0, u16 arg1, u16 arg2) {
    u8 temp_r3;
    u8 temp_r3_2;
    u8 var_r30;
    u8 var_r31;

    if (arg1 != 0) {
        temp_r3 = joutaiDataBiosGetWriteMode(arg1);
        if (temp_r3 == 4) {
            var_r31 = joutaiBiosGetCount(arg0);
        } else {
            var_r31 = 0;
        }
        init__7_JOUTAIFv(arg0);
        arg0->unk0 = arg1;
        arg0->unk2 = arg2;
        arg0->unk4 = kaisuuGetKaisuu(joutaiDataBiosGetKaisuuDataId(arg1));
        if (temp_r3 == 4) {
            var_r30 = var_r31 + 1;
            temp_r3_2 = joutaiDataBiosGetMaxCount(arg1);
            if (temp_r3_2 < var_r30) {
                var_r30 = temp_r3_2;
            }
            arg0->unk6 = var_r30;
        }
    }
}

s32 checkWriteJoutaiDataId__7_JOUTAIFUs(Joutai *arg0, u16 arg1) {
    u16 temp_r31;
    u8 temp_r3;

    if (arg1 == 0) {
        return 1;
    }
    temp_r31 = arg0->unk0;
    temp_r3 = joutaiDataBiosGetWriteMode(arg1);
    switch ((s32) temp_r3) {                        /* irregular */
    case 0:
        return 2;
    case 1:
        return 2;
    case 2: {
        u32 valid=isValid__7_JOUTAIFv(arg0);return (valid==0)+1; }
    case 3:
        if (isValid__7_JOUTAIFv(arg0) == 0) {
            return 2;
        }
        if ((temp_r31 != arg1) && (arg1 != joutaiDataBiosGetSameJoutai(temp_r31))) {
            return 2;
        }
        return 1;
    case 4:
        if (isValid__7_JOUTAIFv(arg0) == 0) {
            return 2;
        }
        if ((temp_r31 == arg1) || (arg1 == joutaiDataBiosGetSameJoutai(temp_r31))) {
            return 2;
        }
        return 1;
    default:
        return 0;
    }
}

u8 isValid__7_JOUTAIFv(Joutai *arg0) {
    return joutaiBiosGetJoutaiDataId(arg0) != 0;
}

void init__7_JOUTAIFv(Joutai *arg0) {
    arg0->unk0 = 0;
    arg0->unk2 = 0;
    arg0->unk4 = 0;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
}

void joutaiCopy(void *arg0, void *arg1, u16 arg2) {
    Joutai *temp_r3;
    Joutai *temp_r3_2;

    if (arg2 != 0) {
        temp_r3 = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg2);
        if ((temp_r3 != NULL) && (joutaiIsJoutaiDataId(arg1, arg2) != 0)) {
            temp_r3_2 = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg1, arg2);
            if (temp_r3_2 != NULL) {
                temp_r3->unk0 = (u16) temp_r3_2->unk0;
                temp_r3->unk2 = (u16) temp_r3_2->unk2;
                temp_r3->unk4 = (u8) temp_r3_2->unk4;
                temp_r3->unk5 = (u8) temp_r3_2->unk5;
                temp_r3->unk6 = (u8) temp_r3_2->unk6;
                temp_r3->unk7 = (u8) temp_r3_2->unk7;
                temp_r3->unk8 = (s32) temp_r3_2->unk8;
                temp_r3->unkC = (u16) temp_r3_2->unkC;
            }
        }
    }
}

void joutaiSetBuff(void *arg0, u16 arg1, s32 arg2) {
    Joutai *target;
    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0) && ((target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1)) != NULL)) {
        joutaiBiosSetBuff(target, arg2);
    }
}

s32 joutaiGetBuff(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return 0;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return 0;
    }
    return joutaiBiosGetBuff(target);
}

void joutaiSetIdBuff(void *arg0, u16 arg1, s32 arg2) {
    Joutai *target;
    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0) && ((target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1)) != NULL)) {
        joutaiBiosSetIdBuff(target, arg2);
    }
}

s32 joutaiGetIdBuff(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return 0;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return 0;
    }
    return joutaiBiosGetIdBuff(target);
}

s32 joutaiGetUserFightTargetId(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return 0;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return 0;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return 0;
    }
    return joutaiBiosGetUserFightTargetId(target);
}

void joutaiSetKaisuuJoutaiDataId(void *arg0, u16 arg1, s8 arg2) {
    Joutai *temp_r3;

    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0)) {
        temp_r3 = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
        if (temp_r3 != NULL) {
            temp_r3->unk4 = arg2;
        }
    }
}

void joutaiSetNowKaisuuJoutaiDataId(void *arg0, u16 arg1, s32 arg2) {
    Joutai *target;
    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0) && ((target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1)) != NULL)) {
        joutaiBiosSetNowKaisuu(target, arg2);
    }
}

s32 joutaiGetNowKaisuuJoutaiDataId(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return -1;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return -1;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return -1;
    }
    return joutaiBiosGetNowKaisuu(target);
}

s32 joutaiGetKaisuuJoutaiDataId(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return -1;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return -1;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return -1;
    }
    return joutaiBiosGetKaisuu(target);
}

void joutaiSetCountAsJoutaiDataId(void *arg0, u16 arg1, s8 arg2) {
    Joutai *temp_r3;

    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0)) {
        temp_r3 = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
        if (temp_r3 != NULL) {
            temp_r3->unk6 = arg2;
        }
    }
}

s32 joutaiGetCountAsJoutaiDataId(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return -1U;
    }
    if (joutaiIsJoutaiDataId(arg0, arg1) == 0) {
        return -1U;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return -1U;
    }
    return joutaiBiosGetCount(target);
}

void joutaiWriteJoutaiDataId(void *arg0, u16 arg1, u16 arg2) {
 Joutai *target;
    if ((arg1 != 0) && ((target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1)) != NULL)) {
        writeJoutaiDataId__7_JOUTAIFUsUs(target, arg1, arg2);
    }
}

s32 joutaiCheckWriteJoutaiDataId(void *arg0, u16 arg1) {
    if (arg1 == 0) {
        return 1;
    }
    Joutai *target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (target == NULL) {
        return 0;
    }
    return checkWriteJoutaiDataId__7_JOUTAIFUs(target, arg1);
}

u8 joutaiIsJoutaiDataId(void *arg0, u16 arg1) {
    Joutai *temp_r3;

    if (arg1 == 0) {
        return 0U;
    }
    temp_r3 = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1);
    if (temp_r3 == NULL) {
        return 0U;
    }
    if ((isValid__7_JOUTAIFv(temp_r3) == 1) && (arg1 == joutaiBiosGetJoutaiDataId(temp_r3))) {
        return 1U;
    }
    return 0U;
}

void joutaiInitJoutaiDataId(void *arg0, u16 arg1) {
 Joutai *target;
    if ((arg1 != 0) && (joutaiIsJoutaiDataId(arg0, arg1) != 0) && ((target = _joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(arg0, arg1)) != NULL)) {
        _joutaiInit__FP7_JOUTAI(target);
    }
}

void joutaiInitAry(Joutai *arg0, u16 arg1) {
 if(arg0 != 0) { for(u16 i=0; i<arg1; i++) _joutaiInit__FP7_JOUTAI(arg0+i); }
}

void _joutaiInit__FP7_JOUTAI(Joutai *arg0) {
    if (arg0 != 0) {
        init__7_JOUTAIFv(arg0);
    }
}

Joutai *_joutaiGetTargetJoutaiPtrAsJoutaiDataId__FPvUs(void *arg0, u16 arg1) {
    u16 temp_r31;
    s32 temp_r30;
    Joutai *temp_r3;
    s32 status;

    temp_r31 = joutaiDataBiosGetUseBanme(arg1);
    temp_r30 = joutaiDataBiosGetStatusKind(arg1);
    status = joutaiDataBiosGetStatus(arg1);
    temp_r3 = statusGetStatus(temp_r30, arg0, 0, status, 0);
    if (temp_r3 == 0U) {
        return 0;
    }
    return temp_r3 + (u16)temp_r31;
}
}
