#ifndef PXDVS_MENU_FACE_PRIVATE_HPP
#define PXDVS_MENU_FACE_PRIVATE_HPP
#include <global.h>
struct Pokemon;
typedef Pokemon* (*FacePokemonGetter)(void*);
struct FaceListEntry {
    u32 resource;
    u16 face;
    u8 state;
    s8 slot;
    FacePokemonGetter getter;
    void* context;
};
struct FaceTextureEntry {u32 reserved;void* data;};
typedef char FaceEntrySize[sizeof(FaceListEntry)==0x10?1:-1];
extern "C" {
extern s32 _menuFaceListNum;
extern FaceListEntry* pMenuFaceList;
extern FaceTextureEntry* pMenuFaceTexList;
extern u8 _menuFaceLoadCallBackFlag;
extern u8 _testType;
extern u16 uToolPokemon_faceId;
u32 menuFaceGetTexID(u16);
u16 menuFaceGetID(Pokemon*);
u16 menuFaceGetID2(Pokemon*,u8);
u16 menuFaceGetID3(Pokemon*,u8,s8);
s8 menuFaceSearchEnable(u16);
bool menuFaceCheckLoading();
s32 menuFaceLoadFromID(u16,FacePokemonGetter,void*);
s32 menuFaceLoadFromID_Tool(u16,FacePokemonGetter,void*);

u8 pokemonCheckValid(Pokemon*);
u8 pokemonBiosGetTamagoFlag(Pokemon*);
u8 pokemonCheckRare(Pokemon*);
u32 pokemonGetStatus(Pokemon*,u32,u16,u16);
u8 pokemonIsDarkPokemon(Pokemon*);
u32 pokemonBiosGetRnd(Pokemon*);
u8 pokemonGetAnnonKatati(u32);
u8 pokemonGetFightPokemonDeoxysSel(u32);
void* GSmemAlloc(u32);
void* GSmemAllocAlign(u32,u32);
void GSresFreeResource(u32,u32);
void GSfsysFree(u32);
void GSfsysReadIDEX(u32,u32,void (*)(s32,void*,s32),s32,s32);
void GSthreadSwitch();
void* GSresGetResource(u32,u32);
void* GStextureLoad(void*);
void GSresRegisterResource(void*,u32,u32,s32 (*)(void*,u32,u32));
void DCFlushRange(void*,u32);
void GXInvalidateTexAll();
struct FaceTextureFile {
    u8 header[7];u8 absolutePointers;
    s32 format;
    u8 reserved0c[0x1c];
    u32 pixels;
    u8 reserved2c[0x1c];
    u32 palette;
};
void GStextureFree(void*);
}
u32 menuFaceBiosGetTexID(u16);
#endif
