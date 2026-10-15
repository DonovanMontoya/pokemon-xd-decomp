#include <global.h>

extern "C" {
u8* fightSeq_GetWazaSeq();
void fightSeq_NextWazaSeq(u32);
void statusSetStatus(u8, s32, u8, u16, u8, s32);
s32 statusGetStatus(u8, s32, u8, u16, u8);
}

#define STATUS_ARGS \
    u8* command = fightSeq_GetWazaSeq(); \
    s32* ptr2 = *(s32**)(command + 2); \
    u8 status = command[1]; \
    u8* ptr6 = *(u8**)(command + 6); \
    u16 type = *(u16*)(command + 0xA); \
    u8* ptrC = *(u8**)(command + 0xC); \
    s32* result = *(s32**)(command + 0x10); \
    s32 value2 = ptr2 ? *ptr2 : 0; \
    u8 value6 = ptr6 ? *ptr6 : 0; \
    u8 valueC = ptrC ? *ptrC : 0

extern "C" void WS_STATUS_SET32() {
    STATUS_ARGS;
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_SET16() {
    STATUS_ARGS;
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_SET8() {
    STATUS_ARGS;
    statusSetStatus(status, value2, value6, type, valueC, *result);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_GET32() {
    STATUS_ARGS;
    *result = statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_GET16() {
    STATUS_ARGS;
    *(s16*)result = (s16)statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}
extern "C" void WS_STATUS_GET8() {
    STATUS_ARGS;
    *(s8*)result = (s8)statusGetStatus(status, value2, value6, type, valueC);
    fightSeq_NextWazaSeq(0x14);
}
