#ifndef CHANK_PRIVATE_HPP
#define CHANK_PRIVATE_HPP
#include <dolphin/types.h>
#include <libc/string.h>
struct ChankHeader {char id[4];u32 size;s32 index;u32 reserved;};
class CChank {
public:
 ChankHeader *head; char *end; s32 count;
 CChank();
 virtual ~CChank();
 u32 reserved10;
 ChankHeader *searchSubChankID(const char*);
 ChankHeader *searchChankID(const char*,s32);
};
class CChankBlock: public CChank {
public:
 u32 reserved14;
 bool loadFromMemory(char*,char*);
};
#endif
