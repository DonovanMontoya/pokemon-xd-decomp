#include <game/menuReliveHallTutorialPrivate.hpp>
extern "C" void *memset(void*,int,unsigned long);
extern "C" {u8 GSgfxVideoGetVsyncRate();u16*windowGetKeyInfo();}
u16 CMetaMenu::tutorialManagePrime() {
    static u16 tbl2009[]={0,1024,1024,1024,1024};
    static u16 tbl2024[]={0,8,8,8,8,16,16};
    static u16 tbl2031[]={0,2,2,2,2,2};
    static u16 tbl2054[]={0,1,16,16,64};
    static u16 tbl2061[]={0,256,8,8,8,16,32};
    static u16 tbl2080[]={0,256,8,8,16,32};
    static u16 tbl2104[]={0,256,2,8,8,8,16,32};
    static u16 tbl2139[]={0,16,2,16,10,16};
    static u16 tbl2016[]={0,16};
    static u16 tbl2040[]={0,512,1024,1024};
    static u16 tbl2047[]={0,512};
    static u16 tbl2068[]={0,1,1,16};
    static u16 tbl2075[]={0,2,16};
    static u16 tbl2087[]={0,1,8};
    static u16 tbl2092[]={0,4};
    static u16 tbl2099[]={0,8,16};
    static u16 tbl2118[]={0,256,16,32};
    static u16 tbl2125[]={0,1,16};
    static u16 tbl2132[]={0,64};
    static u16 tbl2147[]={0,32,2};
    struct Sequence {u16 values[6];};
    Sequence sequence={0,1,9,1,8,16};
    u16 var_r29;
    u32 temp_r0;
    u32 temp_r0_10;
    u32 temp_r0_11;
    u32 temp_r0_12;
    u32 temp_r0_13;
    u32 temp_r0_14;
    u32 temp_r0_15;
    u32 temp_r0_16;
    u32 temp_r0_17;
    u32 temp_r0_18;
    u32 temp_r0_19;
    u32 temp_r0_20;
    u32 temp_r0_2;
    u32 temp_r0_3;
    u32 temp_r0_4;
    u32 temp_r0_5;
    u32 temp_r0_6;
    u32 temp_r0_7;
    u32 temp_r0_8;
    u32 temp_r0_9;
    u32 temp_r4_3;
    u32 temp_r4_4;
    u32 temp_r6;
    u32 temp_r6_10;
    u32 temp_r6_11;
    u32 temp_r6_12;
    u32 temp_r6_13;
    u32 temp_r6_14;
    u32 temp_r6_15;
    u32 temp_r6_16;
    u32 temp_r6_17;
    u32 temp_r6_18;
    u32 temp_r6_19;
    u32 temp_r6_20;
    u32 temp_r6_21;
    u32 temp_r6_22;
    u32 temp_r6_23;
    u32 temp_r6_2;
    u32 temp_r6_3;
    u32 temp_r6_4;
    u32 temp_r6_5;
    u32 temp_r6_6;
    u32 temp_r6_7;
    u32 temp_r6_8;
    u32 temp_r6_9;
    CState *temp_r30;
    TutorialWork *temp_r4;
    TutorialWork *temp_r4_2;
    TutorialWork *temp_r4_5;

    temp_r4 = tutorial;
    temp_r30 = &temp_r4->state;
    if ((u8) temp_r4->done != 0) {
        return 0x20U;
    }
    if ((u16) windowGetKeyInfo()[2] == 0x20) {
        temp_r4_2 = tutorial;
        temp_r4_2->done = 1U;
        temp_r4_2->cancelled = 1;
        return 0x20U;
    }
    temp_r4_3 = *(u32*)temp_r30->reservedA4;
    *(u32*)temp_r30->reservedA4 = (u32) (temp_r4_3 + 1);
    if (isAnimationStateNone() == 0) {
        return 0U;
    }
    if ((u32) *(u32*)temp_r30->reservedA4 < (u32) (0.9f * (f32) GSgfxVideoGetVsyncRate())) {
        return 0U;
    }
    *(u32*)temp_r30->reservedA4 = 0U;
    var_r29 = 0;
    temp_r30->update();
    temp_r4_4 = temp_r4->state.unk0;
    switch (temp_r4_4) {
    case 0:
        tutorialMessage(0xD138);
        temp_r6 = temp_r4->state.unk0;
        temp_r30->unk4 = (s32) (temp_r6 + 1);
        memset(temp_r30->saved,0,0x40);
        break;
    case 1:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD139);
        }
        temp_r0 = temp_r30->frames;
        if (temp_r0 < 5U) {
            var_r29 = tbl2009[temp_r0];
        } else {
            temp_r6_2 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_2 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 2:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD13A);
        }
        temp_r0_2 = temp_r30->frames;
        if (temp_r0_2 < 2U) {
            var_r29 = tbl2016[temp_r0_2];
        } else {
            temp_r6_3 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_3 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 3:
        tutorialMessage(0xD13B);
        temp_r6_4 = temp_r4->state.unk0;
        temp_r30->unk4 = (s32) (temp_r6_4 + 1);
        memset(temp_r30->saved,0,0x40);
        break;
    case 4:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD13C);
        }
        temp_r0_3 = temp_r30->frames;
        if (temp_r0_3 < 7U) {
            var_r29 = tbl2024[temp_r0_3];
        } else {
            temp_r6_5 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_5 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 5:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD13D);
        }
        temp_r0_4 = temp_r30->frames;
        if (temp_r0_4 < 6U) {
            var_r29 = tbl2031[temp_r0_4];
        } else {
            temp_r6_6 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_6 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 6:
        temp_r30->unk4 = (s32) (temp_r4_4 + 1);
        var_r29 = 0x10;
        memset(temp_r30->saved,0,0x40);
        break;
    case 7:
        tutorialMessage(0xD13E);
        temp_r6_7 = temp_r4->state.unk0;
        temp_r30->unk4 = (s32) (temp_r6_7 + 1);
        memset(temp_r30->saved,0,0x40);
        break;
    case 8:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD13F);
        }
        temp_r0_5 = temp_r30->frames;
        if (temp_r0_5 < 4U) {
            var_r29 = tbl2040[temp_r0_5];
        } else {
            temp_r6_8 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_8 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 9:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD140);
        }
        temp_r0_6 = temp_r30->frames;
        if (temp_r0_6 < 2U) {
            var_r29 = tbl2047[temp_r0_6];
        } else {
            temp_r6_9 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_9 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 10:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD141);
        }
        temp_r0_7 = temp_r30->frames;
        if (temp_r0_7 < 5U) {
            var_r29 = tbl2054[temp_r0_7];
        } else {
            temp_r6_10 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_10 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 11:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD142);
        }
        temp_r0_8 = temp_r30->frames;
        if (temp_r0_8 < 7U) {
            var_r29 = tbl2061[temp_r0_8];
        } else {
            temp_r6_11 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_11 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 12:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD143);
        }
        temp_r0_9 = temp_r30->frames;
        if (temp_r0_9 < 4U) {
            var_r29 = tbl2068[temp_r0_9];
        } else {
            temp_r6_12 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_12 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 13:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD144);
        }
        temp_r0_10 = temp_r30->frames;
        if (temp_r0_10 < 3U) {
            var_r29 = tbl2075[temp_r0_10];
        } else {
            temp_r6_13 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_13 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 14:
        temp_r0_11 = temp_r30->frames;
        if (temp_r0_11 < 6U) {
            var_r29 = tbl2080[temp_r0_11];
        } else {
            temp_r30->unk4 = (s32) (temp_r4_4 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 15:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD145);
        }
        temp_r0_12 = temp_r30->frames;
        if (temp_r0_12 < 3U) {
            var_r29 = tbl2087[temp_r0_12];
        } else {
            temp_r6_14 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_14 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 16:
        temp_r0_13 = temp_r30->frames;
        if (temp_r0_13 < 2U) {
            var_r29 = tbl2092[temp_r0_13];
        } else {
            temp_r30->unk4 = (s32) (temp_r4_4 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 17:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD146);
        }
        temp_r0_14 = temp_r30->frames;
        if (temp_r0_14 < 3U) {
            var_r29 = tbl2099[temp_r0_14];
        } else {
            temp_r6_15 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_15 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 18:
        temp_r0_15 = temp_r30->frames;
        if (temp_r0_15 < 8U) {
            var_r29 = tbl2104[temp_r0_15];
        } else {
            temp_r30->unk4 = (s32) (temp_r4_4 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 19:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD147);
        }
        temp_r6_16 = temp_r30->frames;
        if (temp_r6_16 < 6U) {
            var_r29 = sequence.values[temp_r6_16];
        } else {
            temp_r6_17 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_17 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 20:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD148);
        }
        temp_r0_16 = temp_r30->frames;
        if (temp_r0_16 < 4U) {
            var_r29 = tbl2118[temp_r0_16];
        } else {
            temp_r6_18 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_18 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 21:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD149);
        }
        temp_r0_17 = temp_r30->frames;
        if (temp_r0_17 < 3U) {
            var_r29 = tbl2125[temp_r0_17];
        } else {
            temp_r6_19 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_19 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 22:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD14A);
        }
        temp_r0_18 = temp_r30->frames;
        if (temp_r0_18 < 2U) {
            var_r29 = tbl2132[temp_r0_18];
        } else {
            temp_r6_20 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_20 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 23:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD14B);
        }
        temp_r0_19 = temp_r30->frames;
        if (temp_r0_19 < 6U) {
            var_r29 = tbl2139[temp_r0_19];
        } else {
            temp_r6_21 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_21 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 24:
        tutorialMessage(0xD14C);
        temp_r6_22 = temp_r4->state.unk0;
        temp_r30->unk4 = (s32) (temp_r6_22 + 1);
        memset(temp_r30->saved,0,0x40);
        break;
    case 25:
        if (temp_r30->time == 0.0f) {
            tutorialMessage(0xD14D);
        }
        temp_r0_20 = temp_r30->frames;
        if (temp_r0_20 < 3U) {
            var_r29 = tbl2147[temp_r0_20];
        } else {
            temp_r6_23 = temp_r4->state.unk0;
            temp_r30->unk4 = (s32) (temp_r6_23 + 1);
            memset(temp_r30->saved,0,0x40);
        }
        break;
    case 26:
        temp_r4_5 = tutorial;
        var_r29 = 0x10;
        temp_r4_5->done = 1U;
        temp_r4_5->cancelled = 0;
        break;
    }
    return var_r29;
}

void CMetaMenu::tutorialManageUpdate() {
    tutorialCached = 0;
}

u16 CMetaMenu::tutorialManage() {
    if ((u8) tutorialCached != 0) {
        return tutorialInput;
    }
    tutorialCached = 1U;
    tutorialInput = tutorialManagePrime();
    return tutorialInput;
}

void CMetaMenu::tutorialMessage(u32 arg1) {
    TutorialWork *temp_r3;

    baseInfoWindow.exec(*this,arg1,true);
    if ((u16) baseInfoWindow.key == 0x20) {
        tutorialExitKick();
        temp_r3 = tutorial;
        temp_r3->done = 1;
        temp_r3->cancelled = 1;
    }
}
