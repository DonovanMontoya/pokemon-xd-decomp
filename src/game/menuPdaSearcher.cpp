#include <game/menuPcBoxPokemonLayout.hpp>
#include <game/menuPdaSearcherPrivate.hpp>
s32 _esaMeterIndex0[10]={0x198,0x199,0x19A,0x19B,0x19C,0x19D,0x19E,0x19F,0x1A0,0x1A1};
s32 _esaMeterIndex1[10]={0x1A2,0x1A3,0x1A4,0x1A7,0x1A5,0x1A6,0x1A8,0x1A9,0x1AA,0x1AB};
s32 _esaMeterIndex2[10]={0x1AC,0x1AD,0x1AE,0x1AF,0x1B0,0x1B1,0x1B2,0x1B3,0x1B4,0x1B5};
s32 *_esaMeterIndex[3]={_esaMeterIndex0,_esaMeterIndex1,_esaMeterIndex2};
static f32 _esaTimer[3];
extern u32 *esabadata_number;extern u8 *worldmapXD_data;
extern "C" {s32 GSflagGet(u32);u32 GSmsgGetRect(u32);void GSmsgPrintRect(s32,s16,s16,s16,s16,u32,u32);s32 esabaGetDigestRate();s32 esabaGetEsaNum(u32);void menuClose(s32);void menuCloseSync(s32,s32);s32 menuOpen(s32,s32);f32 timeGetLastFrameSec();void winSeqSetMenu(s32,s32);void winSpriteSetDisp(tagSPRITE_WORK*,s32);u16 *windowGetKeyInfo();f64 cos(f64);}
static f32 _gettLastTime(){return timeGetLastFrameSec();}
static void _menuClose(s32 id){menuClose(id);menuCloseSync(id,1);}
static void _esaMonInit(){for(u32 i=0;i<*esabadata_number;i++)_esaTimer[i]=0.0f;}
static u8 _getWorldMapFlag(u16 index){u16 table[3]={15,16,17};if(index>2)return 0;return GSflagGet(*(u32*)(worldmapXD_data+table[index]*0x24+4))!=0;}
static void _updateTimer(u16 index){f32 rate=esabaGetDigestRate();f32 delta=_gettLastTime();f32 divisor=rate/100.0f;_esaTimer[index]+=(3.1415927f*(2.0f*delta))/divisor;f32 time=_esaTimer[index];if(time>6.2831855f)_esaTimer[index]=time-6.2831855f;}
static void _animMojiCursor(tagWINDOW_WORK *w,tagSPRITE_WORK *s,u16 index){f32 alpha=255.0f*((1.0f+(f32)cos(_esaTimer[index]))/2.0f);if(alpha>=255.0f)alpha=255.0f;((u8*)s)[0x67]=(w->alpha*(u8)(s32)alpha)/255;}
static void _esaPrintMsg(tagWINDOW_WORK *w,tagSPRITE_WORK *s,unsigned long msg){u32 color=w->alpha|0xFFFFFF00;u32 rect=GSmsgGetRect(msg);s16 width=s->width;GSmsgPrintRect(w->layer,(s16)((u32)(width-(rect>>16))>>1),0,width,s->height,color,msg);}
static void _esaNumSet(tagSPRITE_WORK *s,u16 index){s32 *ids=_esaMeterIndex[index];s32 number=esabaGetEsaNum(index);if(number==0)winSpriteSetDisp(s,0);s32 match=0;for(;match<10;match++)if(s->id==ids[match])break;if(number>=match+1){winSpriteSetDisp(s,1);return;}winSpriteSetDisp(s,0);}
extern "C" {
s32 menuPdaSearcherCtrl(tagWINDOW_WORK *w){switch(w->phase){case 0:if(!w->step){winSeqSetMenu(w->menu,0x132);w->step=1;_esaMonInit();}break;case 3:if(!w->step){winSeqSetMenu(w->menu,0x136);w->step=1;}break;}return 0;}
void fn_80042BDC(tagWINDOW_WORK *w){if(w && (windowGetKeyInfo()[2]&0x20)){w->finished=1;w->cancelled=1;}}
void menuPdaSearcher(){menuOpen(0x77,0);do{}while(menuOpen(0x6D,1)>=0);_menuClose(0x6D);_menuClose(0x77);}
}

static void _animCursor(tagWINDOW_WORK*,tagSPRITE_WORK*,u16);
extern "C" u16 esabaGetPokemonID(s32);
extern "C" s32 menuPdaSeatcherHook(tagWINDOW_WORK *w,tagSPRITE_WORK *s){switch(s->id){
case 0x1B7:if(_getWorldMapFlag(0))_esaPrintMsg(w,s,0x3C17);break;
case 0x1B8:if(_getWorldMapFlag(1))_esaPrintMsg(w,s,0x3C18);break;
case 0x1B9:if(_getWorldMapFlag(2))_esaPrintMsg(w,s,0x3C19);break;
case 0x1BA:if(_getWorldMapFlag(0))_esaPrintMsg(w,s,0x3C17);break;
case 0x1BB:if(_getWorldMapFlag(1))_esaPrintMsg(w,s,0x3C18);break;
case 0x1BC:if(_getWorldMapFlag(2))_esaPrintMsg(w,s,0x3C19);break;
case 0x1BD:if(_getWorldMapFlag(0))winSpriteSetDisp(s,1);else winSpriteSetDisp(s,0);break;
case 0x1BE:if(_getWorldMapFlag(1))winSpriteSetDisp(s,1);else winSpriteSetDisp(s,0);break;
case 0x1BF:if(_getWorldMapFlag(2))winSpriteSetDisp(s,1);else winSpriteSetDisp(s,0);break;
case 0x1C0:if(_getWorldMapFlag(0) && esabaGetPokemonID(0)){winSpriteSetDisp(s,1);_animCursor(w,s,0);}else winSpriteSetDisp(s,0);break;
case 0x1C1:if(_getWorldMapFlag(1) && esabaGetPokemonID(1)){winSpriteSetDisp(s,1);_animCursor(w,s,1);}else winSpriteSetDisp(s,0);break;
case 0x1C2:if(_getWorldMapFlag(2) && esabaGetPokemonID(2)){winSpriteSetDisp(s,1);_animCursor(w,s,2);}else winSpriteSetDisp(s,0);break;
case 0x1C3:if(_getWorldMapFlag(0) && esabaGetPokemonID(0)){winSpriteSetDisp(s,1);_animMojiCursor(w,s,0);}else winSpriteSetDisp(s,0);break;
case 0x1C4:if(_getWorldMapFlag(1) && esabaGetPokemonID(1)){winSpriteSetDisp(s,1);_animMojiCursor(w,s,1);}else winSpriteSetDisp(s,0);break;
case 0x1C5:if(_getWorldMapFlag(2) && esabaGetPokemonID(2)){winSpriteSetDisp(s,1);_animMojiCursor(w,s,2);}else winSpriteSetDisp(s,0);break;
case 0x198:case 0x199:case 0x19A:case 0x19B:case 0x19C:case 0x19D:case 0x19E:case 0x19F:case 0x1A0:case 0x1A1:_esaNumSet(s,0);break;
case 0x1A2:case 0x1A3:case 0x1A4:case 0x1A5:case 0x1A6:case 0x1A7:case 0x1A8:case 0x1A9:case 0x1AA:case 0x1AB:_esaNumSet(s,1);break;
case 0x1AC:case 0x1AD:case 0x1AE:case 0x1AF:case 0x1B0:case 0x1B1:case 0x1B2:case 0x1B3:case 0x1B4:case 0x1B5:_esaNumSet(s,2);break;
}return 0;}

static f32 _maxscale[2]={0.5f,1.5f};static f32 _startangle;
extern "C" {f32 GSlerpGetLinearInterpolationFloat(f32,f32,f32);s32 winSpriteGetLayerID(tagWINDOW_WORK*,tagSPRITE_WORK*);GSgfxLayer *GSgfxLayerFindByID(s32);void *menuSpriteBiosGetPtr(u32);MenuSpriteValue *menuSpriteBiosGetValPtr(void*);SearchTexture *GSresGetResourceAllGroup(u32);u16 GStextureGetXsize(SearchTexture*);u16 GStextureGetYsize(SearchTexture*);void *menuItemBiosGetPtr(s32,s16);GSgfxVF *GSgfxVFGetPredef(u32);f64 sin(f64);}
union SearchFifo {s16 position;u8 color;f32 texture;};
static void _animCursor(tagWINDOW_WORK *w,tagSPRITE_WORK *s,u16 index){
 f32 coordinates[4][3];_updateTimer(index);f32 progress=_esaTimer[index]/6.2831855f;f32 alpha=255.0f*(1.0f-progress);if(alpha>=255.0f)alpha=255.0f;s->color.channels.alpha=(w->alpha*(u8)(s32)alpha)/255;
 f32 scale=GSlerpGetLinearInterpolationFloat(_maxscale[0],_maxscale[1],progress);GSgfxLayer *layer=GSgfxLayerFindByID(winSpriteGetLayerID(w,s));MenuSpriteValue *sprite=menuSpriteBiosGetValPtr(menuSpriteBiosGetPtr(0x2DE));SearchTexture *texture=GSresGetResourceAllGroup(sprite->resource);u16 textureWidth=GStextureGetXsize(texture);u16 textureHeight=GStextureGetYsize(texture);f32 angle=_startangle;f32 radius=scale*(sprite->width/2);menuItemBiosGetPtr(w->menu,s->id);
 f32 centerX=sprite->width/2,centerY=sprite->height/2;coordinates[0][0]=coordinates[3][0]=(f32)sprite->x/(f32)textureWidth;coordinates[1][0]=coordinates[2][0]=(f32)(sprite->x+sprite->width)/(f32)textureWidth;coordinates[0][1]=coordinates[1][1]=(f32)sprite->y/(f32)textureHeight;coordinates[2][1]=coordinates[3][1]=(f32)(sprite->y+sprite->height)/(f32)textureHeight;
    layer->colorUpdate = 1;
    layer->alphaUpdate = 0;
    layer->depthBeforeTexture = 0;
    layer->pixelDirty = (s32) (layer->pixelDirty | 4);
    layer->dirty = (s32) (layer->dirty | 0x40);
    layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 4);
    layer->savedDirty = (s32) (layer->savedDirty | 0x40);
    layer->depthEnable = 0;
    layer->depthCompare = 7;
    layer->pixelDirty = (s32) (layer->pixelDirty | 8);
    layer->dirty = (s32) (layer->dirty | 0x40);
    layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 8);
    layer->savedDirty = (s32) (layer->savedDirty | 0x40);
    if ((s32) layer->blendIndex != 1) {
        layer->blendIndex = 1;
        layer->currentBlend = &layer->blendRecords[layer->blendIndex];
    }
    layer->blendMode = 1;
    layer->blendSource = 4;
    layer->blendDestination = 5;
    layer->logicOperation = 5;
    layer->pixelDirty = (s32) (layer->pixelDirty | 1);
    layer->dirty = (s32) (layer->dirty | 0x40);
    layer->savedPixelDirty = (s32) (layer->savedPixelDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 0x40);
    layer->texGenCount = 1;
    layer->lineDirty = (s32) (layer->lineDirty | 1);
    layer->dirty = (s32) (layer->dirty | 1);
    layer->savedLineDirty = (s32) (layer->savedLineDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 1);
    layer->tgenFunc(0,(GSgfxTgenFunc)1,(GSgfxTgenSrc)4,0,false,0);
    layer->channelCount = 1;
    layer->channelDirty = (s32) (layer->channelDirty | 1);
    layer->dirty = (s32) (layer->dirty | 4);
    layer->savedChannelDirty = (s32) (layer->savedChannelDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 4);
    layer->cunitChannelGen(0,(GSgfxCunitAlpha)2,(GSgfxCunitSrc)1,(GSgfxCunitSrc)1,0,0,(GSgfxLightType)2,(GSgfxDiffuseFunc)0);
    layer->texCoordCount = 1;
    layer->texCoordDirty = (s32) (layer->texCoordDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedTexCoordDirty = (s32) (layer->savedTexCoordDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 8);
    layer->texCoordMap = 0;
    layer->texCoordUnit = 0;
    layer->texCoordChannel = 4;
    layer->texMapDirty = (s32) (layer->texMapDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedTexMapDirty = (s32) (layer->savedTexMapDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 8);
    layer->colorOp = 0;
    layer->colorBias = 0;
    layer->colorScale = 0;
    layer->colorClamp = 1;
    layer->colorOutput = 0;
    layer->colorOpDirty = (s32) (layer->colorOpDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedColorOpDirty = (s32) (layer->savedColorOpDirty | 1);
    layer->savedDirty = layer->savedDirty | 8;
    layer->colorArgA = 0xF;
    layer->colorArgB = 0xF;
    layer->colorArgC = 0xF;
    layer->colorArgD = 8;
    layer->colorArgDirty = (s32) (layer->colorArgDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedColorArgDirty = (s32) (layer->savedColorArgDirty | 1);
    layer->savedDirty = layer->savedDirty | 8;
    layer->alphaOp = 0;
    layer->alphaBias = 0;
    layer->alphaScale = 0;
    layer->alphaClamp = 1;
    layer->alphaOutput = 0;
    layer->alphaOpDirty = (s32) (layer->alphaOpDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedAlphaOpDirty = (s32) (layer->savedAlphaOpDirty | 1);
    layer->savedDirty = (s32) (layer->savedDirty | 8);
    layer->alphaArgA = 7;
    layer->alphaArgB = 5;
    layer->alphaArgC = 4;
    layer->alphaArgD = 7;
    layer->alphaArgDirty = (s32) (layer->alphaArgDirty | 1);
    layer->dirty = (s32) (layer->dirty | 8);
    layer->savedAlphaArgDirty = (s32) (layer->savedAlphaArgDirty | 1);
    layer->savedDirty = layer->savedDirty | 8;
    layer->primitiveType = 0x80;
    GSgfxVF *vf=GSgfxVFGetPredef(7);
    layer->primitiveType = 0xA0;
    layer->setRenderStateAndSelect(vf);
    if ((layer->texture != texture) || (layer->savedTexture != texture) || (texture->dirty != 0)) {
        layer->texture = texture;
        layer->textureDirty = (s32) (layer->textureDirty | 1);
        layer->savedTexture = texture;
        layer->savedTextureDirty = (s32) (layer->savedTextureDirty | 1);
    }

 layer->beginSurface(4);f32 *uv=coordinates[0];for(s32 i=0;i<4;i++){f32 sine=(f32)sin(angle);f32 cosine=(f32)cos(angle);f32 u=uv[0],v=uv[1];angle+=1.5707964f;uv+=3;volatile SearchFifo *fifo=(volatile SearchFifo*)0xCC008000;fifo->position=(s16)(radius*sine+centerX);fifo->position=(s16)(radius*cosine+centerY);fifo->color=255;fifo->color=255;fifo->color=255;fifo->color=s->color.channels.alpha;fifo->texture=u;fifo->texture=v;}layer->endSurface();}
