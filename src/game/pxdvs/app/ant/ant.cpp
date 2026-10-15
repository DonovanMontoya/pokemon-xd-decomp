// Default flags (no extra cflags needed).
#include <game/pxdvs/app/ant/antPrivate.hpp>
#include <libc/string.h>

extern "C" {
void GSfsysFree(s32);
s32 GSfsysGetStatus(s32);
void GSfsysReadID(s32, u32);
void GSresFreeGroup(s32);
void GSresFreeResource(s32, u32);
void *GSresGetResource(s32, u32);
void GSthreadSwitch();
f32 timeGetLastFrameSec();
}

PokeDanceWork _pokeDance;

f32 CAnt::colorAnimationTimeDark;
f32 CAnt::colorAnimationTimeReliveReady;
extern "C" {
u8 pokemonCheckRare(Pokemon *);
s32 pokemonGetStatus(Pokemon *, s32, s32, s32);
s32 pokemonGetAnnonKatati(s32);
u32 pokemonDB_GetPokebodyId(u16, u8);
}

struct AnnonBody {
    u32 normal;
    u32 rare;
};

static inline s32 pokeDanceIndex(u32 id) {
    s32 idx;
    u32 i;
    for (i = 0; i < 0xF0; i++) {
        u32 cur = _pokeDance.entries[i].id;
        if (cur == 0) {
            break;
        }
        if (cur == id) {
            idx = i;
            goto found;
        }
    }
    idx = -1;
found:
    if (idx == -1) {
        for (i = 0; i < 0xF0; i++) {
            if (_pokeDance.entries[i].id == 0) {
                break;
            }
        }
        idx = i;
        PokeDanceEntry *e = &_pokeDance.entries[idx];
        memset(e, 0, sizeof(PokeDanceEntry));
        e->id = id;
    }
    return idx;
}

static inline void *pokeDanceUse(u32 id) {
    if (id == 0) {
        return 0;
    }
    s32 idx = pokeDanceIndex(id);
    PokeDanceEntry *e = &_pokeDance.entries[idx];
    e->useCount = 1;
    return e->resource;
}

extern "C" u8 GSgfxVideoGetVsyncRate();

static inline void *antResource(CAnt *ant,u32 &id) {
    id=ant->unk0;
    if(id==0)return 0;
    if(ant->unk4!=0)return (void*)ant->unk4;
    ant->unk4=(u32)pokeDanceUse(id);
    return (void*)ant->unk4;
}

static inline void antAdvance(CAnt *ant,u32 &id) {
    if(ant->unk0==0)return;
    ant->unk2C=0.0f;
    ant->unk1C=0.0f;
    u8 *resource=(u8*)antResource(ant,id);
    if(resource){
        struct AnimationResource {u8 pad[16];u16 offset;};
        AnimationResource *animation=(AnimationResource*)resource;
        s32 row=ant->unk18;
        animation=(AnimationResource*)((u8*)animation+row*2);
        u16 sequenceOffset=animation->offset;
        u8 *sequence=resource+sequenceOffset;
        u8 flags=sequence[ant->unk1A++];
        if(flags&2)ant->unk2C=(f32)((sequence[ant->unk1A++]*18)/10)/60.0f;
        if(flags&4){ant->unk20=sequence[ant->unk1A++];ant->unk24=sequence[ant->unk1A++];}
        if(flags&1)ant->unk28=sequence[ant->unk1A++];
        if(flags&8)ant->unk1A-=sequence[ant->unk1A];
    }
}

static inline void antUpdate(CAnt *ant,u32 &id) {
    if(ant->unk2C){
        ant->unk1C+=timeGetLastFrameSec();
        if(ant->unk1C<ant->unk2C-0.5f*(1.0f/GSgfxVideoGetVsyncRate()))return;
    }
    antAdvance(ant,id);
}

void CAnt::drawAndUpdateWithOffset(PocketVec<short> offset){
    u32 id;
    if(unk0){draw(offset);antUpdate(this,id);}
}
void CAnt::drawAndUpdate(PocketVec<short> position){
    u32 id;
    if(unk0){x=position.x;y=position.y;draw(PocketVec<short>::zero);antUpdate(this,id);}
}
void CAnt::drawAndUpdate(){
    u32 id;
    if(unk0){draw(PocketVec<short>::zero);antUpdate(this,id);}
}
void CAnt::setAnimation(long animation){
    u32 id;
    unk18=animation;unk1A=0;unk1C=0.0f;unk20=0;unk24=0;unk28=0;unk2C=0.0f;
    antAdvance(this,id);
}

static inline void pokeDanceRegister(u32 id) {
    if (id == 0) {
        return;
    }
    s32 idx = pokeDanceIndex(id);
    PokeDanceEntry *e = &_pokeDance.entries[idx];
    e->useCount = 1;
}

#define ANT_ANNON_TABLE \
    {0x1E4C3200, 0x1E4D3200},\
    {0x1E4E3200, 0x1E4F3200},\
    {0x1E503200, 0x1E513200},\
    {0x1E523200, 0x1E533200},\
    {0x1E543200, 0x1E573200},\
    {0x1E583200, 0x1E593200},\
    {0x1E5A3200, 0x1E5B3200},\
    {0x1E5C3200, 0x1E5D3200},\
    {0x1E5E3200, 0x1E5F3200},\
    {0x1E603200, 0x1E613200},\
    {0x1E623200, 0x1E633200},\
    {0x1E643200, 0x1E653200},\
    {0x1E663200, 0x1E673200},\
    {0x1E683200, 0x1E693200},\
    {0x1E6A3200, 0x1E6B3200},\
    {0x1E6C3200, 0x1E6D3200},\
    {0x1E6E3200, 0x1E713200},\
    {0x1E723200, 0x1E733200},\
    {0x1E743200, 0x1E753200},\
    {0x1E763200, 0x1E773200},\
    {0x1E783200, 0x1E793200},\
    {0x1E7A3200, 0x1E7B3200},\
    {0x1E7C3200, 0x1E7D3200},\
    {0x1E7E3200, 0x1E7F3200},\
    {0x1E803200, 0x1E813200},\
    {0x1E823200, 0x1E833200},\
    {0x1E553200, 0x1E563200},\
    {0x1E6F3200, 0x1E703200}

#define ANT_INIT_BY_POKEMON_BODY(self, pk) \
    memset(self, 0, 0x34); \
    (self)->unkC = 1.0f; \
    (self)->unk10 = 0xFF; \
    if ((pk)->checkValid()) { \
        u16 dataId = (pk)->getPokemonDataId(); \
        if (dataId == 0xC9) { \
            AnnonBody tbl[28] = { ANT_ANNON_TABLE }; \
            s32 k = pokemonGetAnnonKatati(pokemonGetStatus(pk, 0, 0x6F, 0)); \
            u32 body; \
            if (pokemonCheckRare(pk)) { \
                body = tbl[(u8)k].rare; \
            } else { \
                body = tbl[(u8)k].normal; \
            } \
            (self)->unk0 = body; \
        } else if (dataId == 0xF9 && (pk)->isDarkPokemon()) { \
            (self)->unk0 = 0x20083200; \
        } else { \
            u32 rare = (pk)->isRare(); \
            (self)->unk0 = pokemonDB_GetPokebodyId(dataId, rare); \
        } \
        u32 body = (self)->unk0; \
        if (body != 0 && (self)->unk4 == 0) { \
            (self)->unk4 = (u32)pokeDanceUse(body); \
        } \
    }


void CAnt::init() {
    memset(this, 0, 0x34);
    unkC = 1.0f;
    unk10 = 0xFF;
}

void CAnt::initByPokemon(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
}

void CAnt::initByPokemonAndSetColorAnimationInAny(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
    if (pk->isDarkPokemon()) {
        if (pk->getDarkPoint() > 0.0f) {
            unk30 = 1;
        } else {
            unk30 = 2;
        }
    }
}

void CAnt::initByPokemonAndSetColorAnimationInReliveHallVisitor(Pokemon *pk) {
    ANT_INIT_BY_POKEMON_BODY(this, pk)
    if (pk->isDarkPokemon()) {
        if (pk->getDarkPoint() > 0.0f) {
            unk30 = 1;
        } else {
            unk30 = 2;
        }
    }
}

void CAnt::use() {
    u32 id = unk0;
    if (id != 0) {
        pokeDanceRegister(id);
    }
}

void CAnt::systemUsecountReset() {
    u32 i;
    for (i = 0; i < 0xF0; i++) {
        _pokeDance.entries[i].useCount = 0;
    }
}

static inline void pokeDanceRelease() {
    u32 kept = 0;
    s32 off = 0;
    u32 i;
    PokeDanceEntry *src = _pokeDance.entries;
    _pokeDance.entries[_pokeDance.loading].useCount = 2;
    for (i = 0; i < 0xF0; i++, src++) {
        if (src->id == 0) {
            break;
        }
        if (src->useCount != 0) {
            kept++;
            PokeDanceEntry *dst = (PokeDanceEntry *)((u8 *)_pokeDance.entries + off);
            off += 0xC;
            dst->id = src->id;
            dst->resource = src->resource;
            dst->useCount = src->useCount;
        } else if (src->resource != 0) {
            GSresFreeResource(0x825, src->id);
        }
    }
    PokeDanceEntry *clr = &_pokeDance.entries[kept];
    for (; kept < 0xF0; kept++, clr++) {
        memset(clr, 0, 0xC);
    }
    PokeDanceEntry *q = _pokeDance.entries;
    for (u32 j = 0; j < 0xF0; q++, j++) {
        if (q->id == 0) {
            break;
        }
        if (q->useCount == 2) {
            q->useCount = 1;
            _pokeDance.loading = j;
            return;
        }
    }
}

void CAnt::systemUnUseResourceRelease() {
    pokeDanceRelease();
}

void CAnt::allRequestCancel() {
    PokeDanceEntry *entry = _pokeDance.entries;
    for (s32 i = 0; i < 0xF0; i++, entry++) {
        if (i != _pokeDance.loading && entry->id != 0 && entry->resource == 0) {
            entry->useCount = 0;
        }
    }
    pokeDanceRelease();
}

void CAnt::systemUpdate(bool request) {
    if (_pokeDance.loading != -1) {
        PokeDanceEntry *e = &_pokeDance.entries[_pokeDance.loading];
        if (GSfsysGetStatus(0x825) == 0) {
            e->resource = GSresGetResource(0x825, e->id);
            if (e->resource != 0) {
                _pokeDance.loading = -1;
            }
        }
    }
    if (_pokeDance.loading == -1 && request) {
        PokeDanceEntry *e = _pokeDance.entries;
        u32 i;
        for (i = 0; i < 0xF0 && e->id != 0; i++, e++) {
            if (e->resource == 0) {
                GSfsysReadID(0x825, e->id);
                _pokeDance.loading = i;
                break;
            }
        }
    }
    colorAnimationTimeDark += timeGetLastFrameSec();
    colorAnimationTimeReliveReady += timeGetLastFrameSec();
    if (colorAnimationTimeDark > 1.0f) {
        colorAnimationTimeDark -= 1.0f;
    }
    if (colorAnimationTimeReliveReady > 1.0f) {
        colorAnimationTimeReliveReady -= 1.0f;
    }
}

void CAnt::waitEndOfReading() {
    for (;;) {
        if (_pokeDance.loading != -1) {
            PokeDanceEntry *e = &_pokeDance.entries[_pokeDance.loading];
            if (GSfsysGetStatus(0x825) == 0) {
                e->resource = GSresGetResource(0x825, e->id);
                if (e->resource != 0) {
                    _pokeDance.loading = -1;
                }
            }
        }
        if (_pokeDance.loading == -1) {
            break;
        }
        GSthreadSwitch();
    }
}

void CAnt::systemFree() {
    waitEndOfReading();
    GSfsysFree(0x825);
    GSresFreeGroup(0x825);
    memset(&_pokeDance, 0, 0xB44);
}

void CAnt::systemInit() {
    memset(&_pokeDance, 0, 0xB44);
    _pokeDance.loading = -1;
}

void *antGetGStexture(void *p) {
    return (u8 *)p + *(s32 *)((u8 *)p + 0xC);
}

void antReadPostFunc(void *, u32) {
}

struct GStexture;
struct GSgfxColAu8 {u8 r,g,b,a;};
extern "C" {
u16 GStextureGetXsize(GStexture*);u16 GStextureGetYsize(GStexture*);
void GSgfxVFBuildTemp(s32,s32,s32,s32,s32,s32,s32,s32,s32);
void GSgfxSetupRenderAndSelect();
void GSgfxSetTUnitUserColorArg(s32,s32,s32,s32,s32);
void GSgfxSetTUnitUserColorOp(s32,s32,s32,s32,s32,s32);
void GSgfxSetTUnitUserAlphaArg(s32,s32,s32,s32,s32);
void GSgfxSetTUnitUserAlphaOp(s32,s32,s32,s32,s32,s32);
void GSprimSetBlendMode(s32);void GSgfxSelectTexture(s32,GStexture*);
void GSgfxSetPrimitiveType(s32);void GSgfxBeginSurface(s32);void GSgfxEndSurface();
void GSgfxVertex2s16(s16,s16);void GSgfxColor4u8(u8,u8,u8,u8);void GSgfxTexCoord2f(f32,f32);
void windowDrawSprite(s16,s16,void*,u16,s32,s32);
extern u16 menuRelivehallPcBoxDefaultPokemonSprite;
}
namespace {
GSgfxColAu8 colorWhite={255,255,255,255};
GSgfxColAu8 colorPurple={60,12,255,255};
GSgfxColAu8 colorNone={0,0,0,0};
void dispTexture(GStexture *texture,f32 x,f32 y,int tx,int ty,int width,int height,GSgfxColAu8 color,f32 scale,u8 alpha){
    u8 r,g,b,a;
    s16 left,top;
    s32 x2,y2;
    u16 textureWidth=GStextureGetXsize(texture);
    u16 textureHeight=GStextureGetYsize(texture);
    f32 u=(f32)tx/textureWidth;
    f32 v=(f32)ty/textureHeight;
    f32 right=u+(f32)width/textureWidth;
    f32 bottom=v+(f32)height/textureHeight;
    if(scale!=1.0f){
        s32 halfWidth=width/2;
        s32 halfHeight=height/2;
        width=(s32)(width*scale);
        height=(s32)(height*scale);
        x=(x+halfWidth)-width/2;
        y=(y+halfHeight)-height/2;
    }
    GSgfxVFBuildTemp(0,3,0,0,1,5,1,1,4);
    GSgfxSetupRenderAndSelect();
    if(alpha!=255){
        color.a=alpha;
        GSgfxSetTUnitUserColorArg(0,15,15,15,8);
        GSgfxSetTUnitUserColorOp(0,0,0,0,1,0);
        GSgfxSetTUnitUserAlphaArg(0,7,5,4,7);
        GSgfxSetTUnitUserAlphaOp(0,0,0,0,1,0);
    }else{
        GSgfxSetTUnitUserColorArg(0,8,10,11,15);
        GSgfxSetTUnitUserColorOp(0,0,0,0,1,0);
        GSgfxSetTUnitUserAlphaArg(0,7,7,7,4);
        GSgfxSetTUnitUserAlphaOp(0,0,0,0,1,0);
    }
    GSprimSetBlendMode(1);
    r=color.r;g=color.g;b=color.b;a=color.a;
    left=(s16)x;top=(s16)y;
    GSgfxSelectTexture(0,texture);GSgfxSetPrimitiveType(0x98);GSgfxBeginSurface(4);
    GSgfxVertex2s16(left,top);GSgfxColor4u8(r,g,b,a);GSgfxTexCoord2f(u,v);
    x2=left+width;
    GSgfxVertex2s16(x2,top);GSgfxColor4u8(r,g,b,a);GSgfxTexCoord2f(right,v);
    y2=top+height;
    GSgfxVertex2s16(left,y2);GSgfxColor4u8(r,g,b,a);GSgfxTexCoord2f(u,bottom);
    GSgfxVertex2s16(x2,y2);GSgfxColor4u8(r,g,b,a);GSgfxTexCoord2f(right,bottom);
    GSgfxEndSurface();
}
}
void CAnt::draw(PocketVec<short> offset){
    u32 id;
    if(unk0==0||unk14==1)return;
    PocketVec<short> position={x,y};position.x+=offset.x;position.y+=offset.y;
    if(!antResource(this,id)){
        windowDrawSprite(position.x-24,position.y-24,0,menuRelivehallPcBoxDefaultPokemonSprite,0,7);return;
    }
    GSgfxColAu8 color;
    switch(unk30){
    case 1:{
        f32 phase=colorAnimationTimeDark-0.5f;color=colorPurple;
        if(phase<0.0f)phase=-phase;
        color.a=(u8)(255.0f*(0.76f*(1.0f-2.0f*phase)+0.16f));break;
    }
    case 0:color=colorNone;break;
    case 2:{
        f32 phase=colorAnimationTimeReliveReady-0.5f;
        if(phase<0.0f)phase=-phase;
        f32 blend=1.0f-2.0f*phase;
        f32 inverse=1.0f-blend;
        if(blend>0.5)color.a=(u8)(255.0f*blend);else color.a=128;
        color.r=(u8)(colorWhite.r*blend+colorPurple.r*inverse);
        color.g=(u8)(colorWhite.g*blend+colorPurple.g*inverse);
        color.b=(u8)(colorWhite.b*blend+colorPurple.b*inverse);break;
    }
    }
    u8 *resource=(u8*)antResource(this,id);
    GStexture *texture=resource?(GStexture*)(resource+*(s32*)(resource+12)):0;
    GStextureGetXsize(texture);GStextureGetYsize(texture);
    resource=(u8*)antResource(this,id);
    struct Frame {u16 count,offset;};
    struct Quad {u16 tx,ty,width,height;s16 x,y;u8 remaining[16];};
    u8 *frames=resource+*(s32*)(resource+4);
    Frame *frame=(Frame*)(frames+unk28*4);
    Quad *quad=(Quad*)(frames+frame->offset);
    for(s32 i=0;i<frame->count;i++,quad++){
        dispTexture(texture,(f32)(position.x+(unk20+quad->x)),(f32)(position.y+(unk24+quad->y+32)),quad->tx,quad->ty,quad->width,quad->height,color,unkC,unk10);
    }
}
