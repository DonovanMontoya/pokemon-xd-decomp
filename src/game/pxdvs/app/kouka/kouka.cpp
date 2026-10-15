#include <dolphin/types.h>

extern "C" {
u16 koukaDataBiosGetLink(u32);
u16 koukaLinkDataBiosGetKouka(u32, u32);
u8 koukaDataBiosGetStatusKind(u32);
u16 koukaDataBiosGetStatus(u32);
s16 koukaDataBiosGetValue(u32, u32);
u8 koukaDataBiosGetVar(u32);
s32 statusGetStatus(u8, s32, u8, u16, u8);
s32 statusSetStatus(u8, s32, u8, u16, u8, s32);
s32 fightFloorGetStatus(u8, s32, u16, u8);
s32 fightTargetGetTragetPtrToRelativeHostSideFightTargetId(void*, u16);
}

static s32 _koukaOneExec(unsigned long, void*, void*, long*);

extern "C" void koukaExec(unsigned long id, void* target, void* data, long* result) {
    if (result != 0) _koukaOneExec(id, target, data, result);
    else _koukaOneExec(id, target, data, 0);
    u16 link = koukaDataBiosGetLink(id);
    if (link != 0) {
        u16 i = 0;
        while (i < 8) {
            if (koukaLinkDataBiosGetKouka(link, i) != 0) {
                if (result != 0) _koukaOneExec(id, target, data, result + i + 1);
                else _koukaOneExec(id, target, data, 0);
            }
            ++i;
        }
    }
}

static s32 _koukaOneExec(unsigned long id, void* target, void* data, long* result) {
    if (id == 0) return 0;
    u8 statusKind = koukaDataBiosGetStatusKind(id);
    u16 status = koukaDataBiosGetStatus(id);
    s16 value = koukaDataBiosGetValue(id, 0);
    s16 divisor = koukaDataBiosGetValue(id, 1);
    u8 operation = koukaDataBiosGetVar(id);
    s32 current = statusGetStatus(statusKind, (s32)target, 0, status, (u8)value);
    if (operation == 0 || operation == 2 || operation == 3) {
        if (value == -1) {
            s32 adjusted = statusGetStatus(statusKind, (s32)target, 0, divisor, 0);
            value = (s16)((adjusted + (adjusted >> 31)) / 2);
        }
        else if (value == -2) value = (s16)statusGetStatus(statusKind, (s32)target, 0, divisor, 0);
        else if (value < 0 || divisor < 0) return 0;
    }
    s32 calculated;
    switch (operation) {
    case 0: calculated = value; break;
    case 1: calculated = current * value / divisor; break;
    case 2: calculated = current + value; break;
    case 3: calculated = current - value; break;
    case 4: calculated = current + current * value / divisor; break;
    case 5: calculated = current - current * value / divisor; break;
    default: return 0;
    }
    u16 relative = 0;
    if (data != 0) relative = (u16)fightFloorGetStatus(0, 0, 0x14, 0);
    s32 recipient = data ? fightTargetGetTragetPtrToRelativeHostSideFightTargetId(data, relative) : 0;
    s32 set = statusSetStatus(statusKind, (s32)target, 0, status, (u8)recipient, calculated);
    if (result != 0) *result = calculated;
    return set;
}
