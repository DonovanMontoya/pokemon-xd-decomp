#include <game/pxdvs/app/menu/menuFacePrivate.hpp>
#include <libc/string.h>
s32 _menuFaceListNum;
FaceListEntry* pMenuFaceList;
FaceTextureEntry* pMenuFaceTexList;
u8 _menuFaceLoadCallBackFlag;
u8 _testType;
static tagSPRITE_WORK portraitSprite;
static tagSPRITE_WORK sizedPortraitSprite;
static s32 _menuFaceGetListNum();
static s32 _menuFaceSearchList(u16);
static s32 _menuFaceAddList(u16,FacePokemonGetter,void*);
static void _menuFaceLoadCallBack(s32,void*,s32);
static s32 _unloadTexture(void*,u32,u32);
static u16 _menuFaceGetIDSub(Pokemon*,u8,s8);
extern "C" {
s32 menuFaceLoadFightPokemon(u32 slot,FacePokemonGetter getter,void* context){
    Pokemon* pokemon=(Pokemon*)pokemonGetStatus((Pokemon*)slot,0,0xcc,0);
    u8 form=pokemonGetFightPokemonDeoxysSel(slot);
    u16 face=menuFaceGetID2(pokemon,form);
    menuFaceLoadFromID(face,getter,context);
    for(;;){if(menuFaceSearchEnable(face)!=0)break;GSthreadSwitch();}
    if((u16)(face-0x33f)<=1 || face==0x33e){
        face=0x181;menuFaceLoadFromID(face,getter,context);
        for(;;){if(menuFaceSearchEnable(face)!=0)break;GSthreadSwitch();}
    }
    if((u16)(face-0x343)<=1 || face==0x342){
        menuFaceLoadFromID(0x303,getter,context);
        for(;;){if(menuFaceSearchEnable(0x303)!=0)break;GSthreadSwitch();}
    }
    return 1;
}
void menuFaceLoad_Tool(Pokemon* pokemon,FacePokemonGetter getter,void* context){menuFaceLoadFromID_Tool(menuFaceGetID2(pokemon,0),getter,context);}
void menuFaceLoad(Pokemon* pokemon,FacePokemonGetter getter,void* context){menuFaceLoadFromID(menuFaceGetID(pokemon),getter,context);}
s32 menuFaceLoadFromID_Tool(u16 face,FacePokemonGetter getter,void* context){
    u32 resource;
    for(;;){
        if(!face){
            Pokemon* pokemon=0;
            if(getter)pokemon=getter(context);
            if(pokemon)face=uToolPokemon_faceId;
        }
        if(!face){
            if(menuFaceCheckLoading())return 0;
            s32 count=_menuFaceGetListNum();
            FaceListEntry* entry=pMenuFaceList;
            s32 i=0;
            for(;i<count;++entry,++i){if(entry->state==0){face=pMenuFaceList[i].face;break;}}
            if(i==count){GSfsysFree(0x5c0);return 0;}
        }else{
            if(_menuFaceSearchList(face)>=0){_menuFaceAddList(face,getter,context);face=0;continue;}
            _menuFaceAddList(face,getter,context);
        }
        resource=menuFaceGetTexID(face);
        if(!resource){face=0;continue;}
        if(menuFaceCheckLoading())return 1;
        pMenuFaceList[_menuFaceSearchList(face)].state=1;
        _menuFaceLoadCallBackFlag=0;
        GSfsysReadIDEX(0x5c0,resource,_menuFaceLoadCallBack,0,face);
        return 1;
    }
}
s32 menuFaceLoadFromID(u16 face,FacePokemonGetter getter,void* context){
    u32 resource;
    for(;;){
        if(!face){
            Pokemon* pokemon=0;
            if(getter)pokemon=getter(context);
            if(pokemon)face=menuFaceGetID(pokemon);
        }
        if(!face){
            if(menuFaceCheckLoading())return 0;
            s32 count=_menuFaceGetListNum();
            FaceListEntry* entry=pMenuFaceList;
            s32 i=0;
            for(;i<count;++entry,++i){if(entry->state==0){face=pMenuFaceList[i].face;break;}}
            if(i==count){GSfsysFree(0x5c0);return 0;}
        }else{
            if(_menuFaceSearchList(face)>=0){_menuFaceAddList(face,getter,context);face=0;continue;}
            _menuFaceAddList(face,getter,context);
        }
        resource=menuFaceGetTexID(face);
        if(!resource){face=0;continue;}
        if(menuFaceCheckLoading())return 1;
        pMenuFaceList[_menuFaceSearchList(face)].state=1;
        _menuFaceLoadCallBackFlag=1;
        GSfsysReadIDEX(0x5c0,resource,_menuFaceLoadCallBack,0,face);
        return 1;
    }
}
bool menuFaceCheckLoading(){
    s32 count=_menuFaceGetListNum();
    FaceListEntry* entry=pMenuFaceList;
    for(s32 i=0;i<count;++entry,++i)if(entry->state==1)return true;
    return false;
}
u32 menuFaceGetTexID(u16 face){return menuFaceBiosGetTexID(face);}
u16 menuFaceGetID3(Pokemon* pokemon,u8 form,s8 rare){return _menuFaceGetIDSub(pokemon,form,rare);}
u16 menuFaceGetID2(Pokemon* pokemon,u8 form){return _menuFaceGetIDSub(pokemon,form,-1);}
u16 menuFaceGetID(Pokemon* pokemon){return _menuFaceGetIDSub(pokemon,_testType,-1);}
s8 menuFaceSearchEnable(u16 face){s32 index=_menuFaceSearchList(face);if(index<0)return -1;return pMenuFaceList[index].state==2;}
void menuFaceAllocMemory(){}
void menuFaceInit(s32 count){
    _menuFaceListNum=count;
    if(!pMenuFaceList)pMenuFaceList=(FaceListEntry*)GSmemAlloc(count*sizeof(FaceListEntry));
    memset(pMenuFaceList,0,_menuFaceListNum*sizeof(FaceListEntry));
    if(!pMenuFaceTexList)pMenuFaceTexList=(FaceTextureEntry*)GSmemAlloc(_menuFaceListNum*sizeof(FaceTextureEntry));
    memset(pMenuFaceTexList,0,_menuFaceListNum*sizeof(FaceTextureEntry));
    for(s8 i=0;i<_menuFaceListNum;++i){
        if(!pMenuFaceTexList[i].data)pMenuFaceTexList[i].data=GSmemAllocAlign(0x1f60,0x20);
        memset(pMenuFaceTexList[i].data,0,0x1f60);
        pMenuFaceList[i].slot=i;
    }
}
}
static s32 _menuFaceGetListNum(){
    FaceListEntry* entry=pMenuFaceList;
    s32 i=0;
    for(;i<_menuFaceListNum;++entry,++i)if(!entry->resource)break;
    return i;
}
static s32 _menuFaceSearchList(u16 face){
    u32 resource=menuFaceGetTexID(face);
    FaceListEntry* entry=pMenuFaceList;
    for(s32 i=0;i<_menuFaceListNum;++entry,++i)if(resource==entry->resource)return i;
    return -1;
}
static s32 _unloadTexture(void* texture,u32,u32){GStextureFree(texture);return 1;}

static u16 _menuFaceGetIDSub(Pokemon* pokemon,u8 form,s8 rareOverride){
    static u16 unknown_face_id_tbl[28][2]={
{0x305,0x321},{0x306,0x322},{0x307,0x323},{0x308,0x324},{0x309,0x325},{0x30a,0x326},{0x30b,0x327},{0x30c,0x328},{0x30d,0x329},{0x30e,0x32a},{0x30f,0x32b},{0x310,0x32c},{0x311,0x32d},{0x312,0x32e},{0x313,0x32f},{0x314,0x330},{0x315,0x331},{0x316,0x332},{0x317,0x333},{0x318,0x334},{0x319,0x335},{0x31a,0x336},{0x31b,0x337},{0x31c,0x338},{0x31d,0x339},{0x31e,0x33a},{0x31f,0x33b},{0x320,0x33c}};
    if(!pokemon)return 0;
    if(!pokemonCheckValid(pokemon))return 0x33d;
    if(pokemonBiosGetTamagoFlag(pokemon))return 0x33d;
    u16 species;
    u8 rare=pokemonCheckRare(pokemon);
    if(rareOverride>=0)rare=rareOverride!=0;
    species=pokemonGetStatus(pokemon,0,0x6e,0);
    if(species==0x19a){
        if(!rare){
            if(form==1)return 0x340;
            if(form==2)return 0x33f;
            if(form==3)return 0x33e;
            return pokemonGetStatus(0,species,0x5b,0);
        }else{
            if(form==1)return 0x344;
            if(form==2)return 0x343;
            if(form==3)return 0x342;
            return pokemonGetStatus(0,species,0x5b,1);
        }
    }
    if(species==0xf9){
        if(pokemonIsDarkPokemon(pokemon))return 0x345;
        if(!rare){return pokemonGetStatus(0,species,0x5b,0);}
        else{return pokemonGetStatus(0,species,0x5b,1);}
    }
    if(species==0xc9){
        u32 shape=pokemonGetAnnonKatati(pokemonBiosGetRnd(pokemon));
        if(!rare){return unknown_face_id_tbl[shape][0];}
        else{return unknown_face_id_tbl[shape][1];}
    }
    if(!rare){return pokemonGetStatus(0,species,0x5b,0);}
    else{return pokemonGetStatus(0,species,0x5b,1);}
}

static s32 _menuFaceAddList(u16 face,FacePokemonGetter getter,void* context){
    u32 resource=menuFaceGetTexID(face);
    if(!resource)return -2;
    s32 count=_menuFaceGetListNum();
    s32 index=_menuFaceSearchList(face);
    if(index<0){
        if(count==_menuFaceListNum){
            u16 oldFace;
            s8 oldSlot;
            FacePokemonGetter oldGetter;
            void* oldContext;
            u8 oldState;
            u32 oldResource;
            oldState=pMenuFaceList[0].state;
            oldResource=pMenuFaceList[0].resource;
            oldFace=pMenuFaceList[0].face;
            oldSlot=pMenuFaceList[0].slot;
            oldGetter=pMenuFaceList[0].getter;
            oldContext=pMenuFaceList[0].context;
            if(oldState==2)GSresFreeResource(0x5c0,oldResource);
            for(s32 i=0;i<count-1;++i)pMenuFaceList[i]=pMenuFaceList[i+1];
            count=_menuFaceListNum-1;
            pMenuFaceList[count].resource=oldResource;
            pMenuFaceList[count].face=oldFace;
            pMenuFaceList[count].state=oldState;
            pMenuFaceList[count].slot=oldSlot;
            pMenuFaceList[count].getter=oldGetter;
            pMenuFaceList[count].context=oldContext;
        }
        pMenuFaceList[count].resource=resource;
        pMenuFaceList[count].face=face;
        pMenuFaceList[count].state=0;
        pMenuFaceList[count].getter=getter;
        pMenuFaceList[count].context=context;
        return count;
    }
    u32 oldResource=pMenuFaceList[index].resource;
    u16 oldFace=pMenuFaceList[index].face;
    u8 oldState=pMenuFaceList[index].state;
    s8 oldSlot=pMenuFaceList[index].slot;
    FacePokemonGetter oldGetter=pMenuFaceList[index].getter;
    void* oldContext=pMenuFaceList[index].context;
    for(;index<count-1;++index)pMenuFaceList[index]=pMenuFaceList[index+1];
    pMenuFaceList[index].resource=oldResource;
    pMenuFaceList[index].face=oldFace;
    pMenuFaceList[index].state=oldState;
    pMenuFaceList[index].slot=oldSlot;
    pMenuFaceList[index].getter=oldGetter;
    pMenuFaceList[index].context=oldContext;
    return index;
}

static void _menuFaceLoadCallBack(s32,void*,s32 input){
    FaceListEntry* entry;
    u16 face=input;
    u32 resource=menuFaceGetTexID(face);
    s32 index=_menuFaceSearchList(face);
    if(index<0){if(resource)GSresFreeResource(0x5c0,resource);}
    else{
        entry=&pMenuFaceList[index];
        FaceTextureFile* texture=(FaceTextureFile*)GSresGetResource(0x5c0,resource);
        texture->absolutePointers=0;
        texture->pixels-=(u32)texture;
        if(texture->format<=1)texture->palette-=(u32)texture;
        memcpy(pMenuFaceTexList[entry->slot].data,texture,0x1f60);
        GSresFreeResource(0x5c0,resource);
        void* loaded=GStextureLoad(pMenuFaceTexList[entry->slot].data);
        GSresRegisterResource(loaded,0x5c0,resource,_unloadTexture);
        DCFlushRange(loaded,0x1f60);
        GXInvalidateTexAll();
        entry->state=2;
        if(_menuFaceLoadCallBackFlag)menuFaceLoadFromID(0,entry->getter,entry->context);
        else menuFaceLoadFromID_Tool(0,entry->getter,entry->context);
    }
}

static s32 _menuFaceDispFromID3(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,u16 face,GSivec2* size,GSivec2* position){
    if(menuFaceSearchEnable(face)!=1)return 0;
    u32 resource=menuFaceGetTexID(face);
    if(!resource)return 0;
    void* texture=GSresGetResourceAllGroup(resource);
    if(!texture)return 0;
    sizedPortraitSprite=*sprite;
    sizedPortraitSprite.resource=resource;
    if(position){sizedPortraitSprite.x=position->x;sizedPortraitSprite.y=position->y;}
    else{sizedPortraitSprite.x=0;sizedPortraitSprite.y=0;}
    sizedPortraitSprite.sourceX=0;sizedPortraitSprite.sourceY=0;
    sizedPortraitSprite.sourceWidth=42;sizedPortraitSprite.sourceHeight=42;
    if(menuFaceBiosGetRareFlag(face) && GStextureGetYsize(texture)>42)sizedPortraitSprite.sourceY=42;
    sizedPortraitSprite.width=size->x;sizedPortraitSprite.height=size->y;
    if(size->x<0 && GStextureGetXsize(texture)>42){
        sizedPortraitSprite.sourceX=42;
        s32 width=size->x;
        if(width<0)width=-width;
        sizedPortraitSprite.width=width;
    }
    winSpriteDrawTexture(window,&sizedPortraitSprite);
    return 1;
}
static s32 _menuFaceDispFromID(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,u16 face,GSvec2* position){
    if(menuFaceSearchEnable(face)!=1)return 0;
    u32 resource=menuFaceGetTexID(face);
    if(!resource)return 0;
    void* texture=GSresGetResourceAllGroup(resource);
    if(!texture)return 0;
    portraitSprite=*sprite;
    portraitSprite.resource=resource;
    if(position){portraitSprite.x=position->x;portraitSprite.y=position->y;}
    else{portraitSprite.x=0;portraitSprite.y=0;}
    portraitSprite.sourceX=0;portraitSprite.sourceY=0;
    portraitSprite.sourceWidth=42;portraitSprite.sourceHeight=42;
    if(menuFaceBiosGetRareFlag(face) && GStextureGetYsize(texture)>42)portraitSprite.sourceY=42;
    if(portraitSprite.width<0 && GStextureGetXsize(texture)>42){
        s32 width=portraitSprite.width;
        portraitSprite.sourceX=42;
        if(width<0)width=-width;
        portraitSprite.width=width;
    }
    winSpriteDrawTexture(window,&portraitSprite);
    return 1;
}
extern "C" {
s32 menuFaceDispFromID3(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,u16 face,GSivec2* size,GSivec2* position){return _menuFaceDispFromID3(window,sprite,face,size,position);}
s32 menuFaceDispFromID2(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,u16 face,GSvec2* position){return _menuFaceDispFromID(window,sprite,face,position);}
s32 menuFaceDispFromID(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,u16 face){return _menuFaceDispFromID(window,sprite,face,0);}
s32 menuFaceDisp(tagWINDOW_WORK* window,tagSPRITE_WORK* sprite,Pokemon* pokemon){return menuFaceDispFromID(window,sprite,menuFaceGetID(pokemon));}
}
