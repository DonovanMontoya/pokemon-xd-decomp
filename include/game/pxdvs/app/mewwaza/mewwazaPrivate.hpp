#ifndef MEWWAZA_PRIVATE_HPP
#define MEWWAZA_PRIVATE_HPP
#include <global.h>
struct MWAZA {u16 unk0,unk2;};
struct MEWPOINTS {s16 unk0,unk2,unk4,unk6,unk8,padding;};
struct WazaTemplate {u16 unk0,unk2,moves[4];};
struct AnswerPair {s32 unk0,unk4;};
extern "C" {
u32 GSfloorGetCurrent();void GSfsysReadWait(u32);void GSresFreeGroup(u32);void GSthreadSwitch();u16 HSD_Rand();
void heroMoveInitEvent();void heroMoveTermEvent();void menuClose(u16);void menuCloseSync(u16,u32);u16 menuMewWazaGetMenuDataID();void menuOpen(u16,u32);
s32 menuSubOpenSelect3(u32,s32*,u32,u32,u32,u32,u32,u32,u8);s8 menuSubOpenYesNo(u32,u32,u32,u32);void msgctrlSetValue(u32,u32);void winMsgClose(u32);void winMsgOpenFieldWithSE(s32,u32,u32,u32);
extern MWAZA mWazaTbl[];extern WazaTemplate *wazaTmplTbl[];
s32 _searchwaza__FP5MWAZAlPUsll(MWAZA*,s32,u16*,s32,s32);
s32 _fillTmplate__FPUsP9MEWPOINTS(u16*,MEWPOINTS*);
WazaTemplate *_getWazaFromTmpl__FlP9MEWPOINTS(s32,MEWPOINTS*);
s32 _tmplSelect__FP9MEWPOINTS(MEWPOINTS*);
void _question_5__FP9MEWPOINTS(MEWPOINTS*);void _question_4__FP9MEWPOINTS(MEWPOINTS*);void _question_3__FP9MEWPOINTS(MEWPOINTS*);s8 _mewSequence__FP9MEWPOINTS(MEWPOINTS*);
}
#endif
