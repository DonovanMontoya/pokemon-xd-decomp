#include <global.h>
struct CursorPosition {s16 x,y;};
static CursorPosition _cursor[16];
extern "C" CursorPosition cursorBiosGetPos(u16 id){CursorPosition result={-1,-1};if(id>=16)return result;result.x=_cursor[id].x;result.y=_cursor[id].y;return result;}
extern "C" CursorPosition cursorBiosSetPos(u16 id,const CursorPosition* position){CursorPosition result={-1,-1};if(id>=16)return result;result.x=_cursor[id].x;result.y=_cursor[id].y;_cursor[id].x=position->x;_cursor[id].y=position->y;return result;}
extern "C" void cursorBiosInit(){CursorPosition* position=_cursor;for(int i=0;i<16;++i,++position){position->x=0;position->y=0;}}
