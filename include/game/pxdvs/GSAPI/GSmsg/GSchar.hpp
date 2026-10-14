#ifndef GSCHAR_HPP
#define GSCHAR_HPP
#include <global.h>
extern "C" {
u16* GScharCat(u16*, const u16*);
u16* GScharLenCpy(u16*, const u16*, s32);
u16* GScharCpy(u16*, const u16*);
s32 GScharCmp(const u16*, const u16*);
s32 GScharMakeFromSJIS(u16*, char*);
u32 GSmsgGetCharLength(const u16*);
u16* GSmsgGetGSchar(u32);
s32 GSmsgIsCheck(u32);
s32 GSmsgSetCtrlFunc(void*);
}
#endif
