#include <game/pxdvs/GSAPI/GSScript/chankPrivate.hpp>
bool CChankBlock::loadFromMemory(char *data,char *id) {
 head=(ChankHeader*)data;
 ChankHeader *header=head;
 if(!header) return true;
 if(id&&memcmp(header,id,4)!=0) return false;
 count=0;
 u32 size;
 char *p=(char*)head+16;
 char *limit=(char*)head+header->size;
 end=limit;
 while(limit>p) {
  s32 n=count;
  size=((ChankHeader*)p)->size;
  count=n+1;
  p+=size;
 }
 return true;
}
ChankHeader *CChank::searchSubChankID(const char *id) {
 if(!head) return 0;
 ChankHeader *p=(ChankHeader*)((char*)head+16);
 for(s32 i=0;i<count;++i) {
  if(memcmp(p,id,4)==0) return p;
  p=(ChankHeader*)((char*)p+p->size);
 }
 return 0;
}
ChankHeader *CChank::searchChankID(const char *id,s32 index) {
 if(!head) return 0;
 ChankHeader *p=(ChankHeader*)((char*)head+16);
 for(s32 i=0;i<count;++i) {
  if(p->index==index&&memcmp(p,id,4)==0) return p;
  p=(ChankHeader*)((char*)p+p->size);
 }
 return 0;
}
CChank::CChank() {head=0;}
