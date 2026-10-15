#include <game/pxdvs/GSAPI/GSlensFlare/GSlensFlarePrivate.hpp>
#include <libc/string.h>

static LensFlareWork* _lfLensFlarePtrs[4];
static u8 gModuleInited;
static inline Vec* lensVec(GSvec* value) { return (Vec*)value; }
static inline void lensCopy(GSvec* out,const GSvec* in) {
    out->param1=in->param1; out->param2=in->param2; out->param3=in->param3;
}
// Quantized unsigned-byte stores clamp before truncating the fractional part.
static inline u8 lensByte(f32 value) {
    if (!(value > 0.0f)) return 0;
    if (value >= 255.0f) return 255;
    return (u8)value;
}
static inline f32 lensClamp(f32 value) {
    if (value < 0.0f) value=0.0f;
    else if (value > 1.0f) value=1.0f;
    return value;
}
static inline void lensIdentity(GSgfxLayer* layer) {
    GSgfxMatrixStack::Entry* current=layer->matrixStack->current;
    memcpy(current->matrix,mtxIdent,0x30);
    current->flags |= 1;
}
static inline void lensVertex(f32 x,f32 y,const u8* color) {
    *(volatile f32*)0xCC008000=x;
    *(volatile f32*)0xCC008000=y;
    *(volatile f32*)0xCC008000=0.0f;
    *(volatile u8*)0xCC008000=color[0];
    *(volatile u8*)0xCC008000=color[1];
    *(volatile u8*)0xCC008000=color[2];
    *(volatile u8*)0xCC008000=color[3];
}
static void lensPrepare(GSgfxLayer* layer) {
    Mtx44 projection;
    GScameraLoadActiveCameraMatrix(layer->id);
    GSmtx44Ortho(projection,0.0f,480.0f,0.0f,640.0f,0.0f,-30000.0f);
    layer->projectionType=1;
    layer->p0=projection[0][0]; layer->p1=projection[0][3];
    layer->p2=projection[1][1]; layer->p3=projection[1][3];
    layer->p4=projection[2][2]; layer->p5=projection[2][3];
    lensIdentity(layer);
    layer->field1684=0.0f; layer->field1688=30000.0f;
    if (layer->field16A7) {
        if (layer->field16A6) { layer->field170C|=0x100; layer->field17C4|=0x100; }
        layer->field170C|=0x40; layer->field16A8|=0x40;
        layer->field17C4|=0x40; layer->field1760|=0x40;
    }
    layer->field16AC|=0x20; layer->field16A8|=1;
    layer->field1764|=0x20; layer->field1760|=1;
    layer->field1656=1; layer->field1657=1; layer->field1658=0;
    layer->field170C|=4; layer->field16A8|=0x40;
    layer->field17C4|=4; layer->field1760|=0x40;
    layer->field165C=0; layer->field1660=3;
    layer->field170C|=8; layer->field16A8|=0x40;
    layer->field17C4|=8; layer->field1760|=0x40;
    layer->fieldD8C=2;
    layer->field16B8|=2; layer->field16A8|=2;
    layer->field1770|=2; layer->field1760|=2;
    layer->field1998=0x98;
    if (layer->field1994 != 1) {
        layer->field1994=1;
        layer->field1990=(u8*)layer + 0x1818 + layer->field1994*0xBC;
    }
    layer->field1644=1; layer->field1648=4; layer->field164C=1; layer->field1650=5;
    layer->field170C|=1; layer->field16A8|=0x40;
    layer->field17C4|=1; layer->field1760|=0x40;
}
static void lensTint(GSgfxLayer* layer,LensFlareWork* flare,f32 occlusion,f32 distance,f32 strength) {
    LensHeader* header=flare->header;
    if (distance >= (f32)header->fadeStart) return;
    f32 fade;
    if (distance < (f32)header->fadePeak) fade=strength;
    else {
        u32 span=header->fadeStart-header->fadePeak;
        fade=lensClamp(strength * (((f32)span-(distance-(f32)header->fadePeak))/(f32)span));
    }
    u8 intensity=(u8)(s32)(255.0f*fade);
    layer->setRenderStateAndSelect(GSgfxVFGetPredef(0));
    lensIdentity(layer);
    layer->beginSurface(4);
    u8 color[4]; color[0]=intensity; color[1]=intensity; color[2]=intensity;
    color[3]=lensByte((255.0f*flare->alpha*occlusion)+0.5f);
    lensVertex(0.0f,0.0f,color);
    color[3]=lensByte((255.0f*flare->alpha*occlusion)+0.5f);
    lensVertex(640.0f,0.0f,color);
    color[3]=lensByte((255.0f*flare->alpha*occlusion)+0.5f);
    lensVertex(0.0f,480.0f,color);
    color[3]=lensByte((255.0f*flare->alpha*occlusion)+0.5f);
    lensVertex(640.0f,480.0f,color);
    layer->endSurface();
}
extern "C" {
void GSlensFlareSetVisible(u32 id,bool visible) {
    if (gModuleInited && id) {
        s32 index=id-1;
        LensFlareWork* flare=_lfLensFlarePtrs[index];
        if (flare && visible != flare->visible) {
            flare->visible=visible;
            if (_lfLensFlarePtrs[index]->header->flags & 8) {
                GSgfxLayer* layer=GSgfxLayerFindByID(5);
                if (layer) layer->SetLayerVisibility(visible);
            }
        }
    }
}
void GSlensFlareSetSunPosition(u32 id,GSvec* position) {
    if (gModuleInited && id) {
        s32 index=id-1;
        LensFlareWork* flare=_lfLensFlarePtrs[index];
        if (flare) lensCopy(&flare->sun,position);
    }
}
void GSlensFlareFree(u32 id) {
    if (gModuleInited && id) {
        s32 index=id-1;
        if (_lfLensFlarePtrs[index]) {
            delete _lfLensFlarePtrs[index];
            _lfLensFlarePtrs[index]=0;
        }
    }
}
u32 GSlensFlareLoad(LensHeader* data) {
    s32 textureIndex;
    GStexture* texture;
    s32 index;
    LensTextureRecord* record;
    LensFlareWork* flare;
    if (!gModuleInited) return 0;
    for (index=0;index<4;index++) {
        if (_lfLensFlarePtrs[index]==0) {
            flare=new LensFlareWork;
            if (flare==0) { flare=0; goto loaded; }
            flare->header=data;
            if (flare->header->magic != 0x7B1EE3F2) { delete flare; flare=0; goto loaded; }
            flare->elements=(LensElement*)((u8*)flare->header+0x2C);
            record=(LensTextureRecord*)(flare->elements+flare->header->elementCount);
            for (textureIndex=0;textureIndex<flare->header->textureCount;record++,textureIndex++) {
                record->data += (u32)data;
                texture=GStextureLoad((void*)record->data);
                GStextureSetFilter(texture,2,2,0);
                if (texture==0) { delete flare; flare=0; goto loaded; }
                flare->textures[record->index]=texture;
            }
            flare->alpha=1.0f;
loaded:
            _lfLensFlarePtrs[index]=flare;
            return _lfLensFlarePtrs[index] ? index+1 : 0;
        }
    }
    return 0;
}

void GSlensFlareInit() {
    memset(_lfLensFlarePtrs,0,sizeof(_lfLensFlarePtrs));
    if (!gModuleInited) {
        LensRenderModule module={0,0,_lensFlareRender__FP10GSgfxLayer14GSgfxLayerPass,0,0,0,0xB29A48E1};
        GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(0x80,&module,0);
        gModuleInited=1;
    }
}
static void _lensFlareRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer* layer,s32 pass) {
    s32 layerID=layer->id;
    u8 cameraReady=0, layerReady=0;
    GSvec cameraPosition,up,right;
    if (pass!=1 || (layerID!=6 && layerID!=5)) return;
    for (u16 i=0;i<4;i++) {
        LensFlareWork* flare=_lfLensFlarePtrs[i];
        if (!flare || !flare->visible) continue;
        LensHeader* header=flare->header;
        if (layer->mode==1 && !(header->flags&8)) continue;
        if (!cameraReady) {
            void* camera=GScameraGetActiveCamera();
            if (!camera) return;
            GScameraLoadActiveCameraMatrix(-1);
            f32 (*matrix)[4]=GScameraGetMatrixPtr(camera);
            GScameraGetPosition(camera,&cameraPosition);
            up.param1=matrix[0][1]; up.param2=matrix[1][1]; up.param3=matrix[2][1];
            right.param1=matrix[0][0]; right.param2=matrix[1][0]; right.param3=matrix[2][0];
            GSgfxProjectSetupParameters(); cameraReady=1;
        }
        GSvec projected,screen;
        s32 projection=GSgfxProjectFast(&flare->sun,&projected);
        if (!projection) continue;
        screen.param1=projected.param1-320.0f; screen.param2=projected.param2-240.0f; screen.param3=0.0f;
        f32 distance=PSVECMag(lensVec(&screen));
        if (distance>(f32)header->outerRadius) continue;
        f32 occlusion=1.0f;
        if (header->flags&0x10) {
            if (header->flags&0x20) {
                GSvec points[21]; u8 blocked[21];
                __construct_array(points,__ct__5GSvecFv,0,12,21);
                f32 step=0.2f*header->sampleRadius;
                for (u16 j=0;j<5;j++) {
                    GSvec offset;
                    f32 spread=step*(f32)j;
                    PSVECScale(lensVec(&up),lensVec(&offset),spread);
                    PSVECSubtract(lensVec(&flare->sun),lensVec(&offset),lensVec(&points[j]));
                    PSVECScale(lensVec(&up),lensVec(&offset),spread);
                    PSVECAdd(lensVec(&flare->sun),lensVec(&offset),lensVec(&points[j+5]));
                    PSVECScale(lensVec(&right),lensVec(&offset),spread);
                    PSVECSubtract(lensVec(&flare->sun),lensVec(&offset),lensVec(&points[j+10]));
                    PSVECScale(lensVec(&right),lensVec(&offset),spread);
                    PSVECAdd(lensVec(&flare->sun),lensVec(&offset),lensVec(&points[j+15]));
                }
                lensCopy(&points[20],&flare->sun);
                if (GScolsys2SunArray(blocked,&cameraPosition,points,21)==1) {
                    f32 visible=blocked[20] ? 0.0f : 2.0f;
                    for (u16 j=0;j<20;j++) visible += blocked[j] ? 0.0f : 1.0f;
                    occlusion=visible/22.0f;
                }
            } else if (GScolsys2Sun(&flare->sun,&cameraPosition)==1) continue;
        }
        if (!layerReady) { lensPrepare(layer); layerReady=1; }
        if (projection==2) {
            f32 sunScale=1.0f;
            for (u16 j=0;j<header->elementCount;j++) {
                if (flare->elements[j].flags&1) { sunScale=flare->elements[j].scale; break; }
            }
            f32 scaleDistance=distance;
            if (distance<header->minDistance) scaleDistance=header->minDistance;
            f32 radialFade;
            if (distance<(f32)header->fadeStart) radialFade=1.0f;
            else {
                u32 span=header->outerRadius-header->fadeStart;
                radialFade=lensClamp(((f32)span-(distance-(f32)header->fadeStart))/(f32)span);
            }
            f32 scaleFactor=header->scaleFactor;
            u32 perspective=header->flags&1;
            layer->setRenderStateAndSelect(GSgfxVFGetPredef(5));
            LensElement* element=flare->elements;
            for (u16 remaining=header->elementCount;remaining!=0;remaining--,element++) {
                if (layer->mode==1 && !(element->flags&2)) continue;
                GStexture* texture=flare->textures[element->texture];
                lensIdentity(layer);
                f32 scale=element->scale;
                GSgfxMatrixStack::Entry* current;
                if (element->flags&1) {
                    current=layer->matrixStack->current;
                    PSMTXTransApply(current->matrix,current->matrix,projected.param1,projected.param2,0.0f);
                    current->flags|=1;
                } else {
                    GSvec offset;
                    PSVECScale(lensVec(&screen),lensVec(&offset),1.0f/element->divisor);
                    if (perspective) {
                        f32 adjustment;
                        if (element->divisor>0.0f && element->divisor<1.0f) adjustment=(1.0f/element->divisor)-1.0f;
                        else adjustment=1.0f-(1.0f/element->divisor);
                        scale *= 1.0f+(adjustment*(800.0f/scaleDistance)*((scaleFactor/sunScale)-1.0f));
                    } else scale *= 1.0f+(((scaleFactor-1.0f)*PSVECMag(lensVec(&offset)))/800.0f);
                    current=layer->matrixStack->current;
                    PSMTXTransApply(current->matrix,current->matrix,offset.param1+320.0f,offset.param2+240.0f,0.0f);
                    current->flags|=1;
                }
                f32 left=-(scale*(f32)(GStextureGetXsize(texture)>>1));
                f32 top=-(scale*(f32)(GStextureGetYsize(texture)>>1));
                f32 rightEdge=scale*(f32)(GStextureGetXsize(texture)>>1);
                f32 bottom=scale*(f32)(GStextureGetYsize(texture)>>1);
                if (header->flags&2) {
                    f32 rotation=(f32)atan2(screen.param2,screen.param1);
                    if (header->flags&4) rotation=-rotation;
                    GSgfxMatrixStack* stack=layer->matrixStack;
                    Mtx matrix;
                    PSMTXRotRad(matrix,'X',0.0f); current=stack->current;
                    PSMTXConcat(current->matrix,matrix,current->matrix);
                    PSMTXRotRad(matrix,'Y',0.0f); current=stack->current;
                    PSMTXConcat(current->matrix,matrix,current->matrix);
                    PSMTXRotRad(matrix,'Z',rotation); current=stack->current;
                    PSMTXConcat(current->matrix,matrix,current->matrix);
                    current->flags|=1;
                }
                u8 color[4];
                color[0]=lensByte(radialFade*(f32)element->color[0]);
                color[1]=lensByte(radialFade*(f32)element->color[1]);
                color[2]=lensByte(radialFade*(f32)element->color[2]);
                color[3]=lensByte(occlusion*(flare->alpha*(radialFade*(f32)element->color[3]))+0.5f);
                if (layer->field1740!=texture || layer->field17F8!=texture || texture->dirty) {
                    layer->field1740=texture; layer->field173C|=1;
                    layer->field17F8=texture; layer->field17F4|=1;
                }
                layer->beginSurface(4);
                lensVertex(left,top,color); *(volatile f32*)0xCC008000=0.0f; *(volatile f32*)0xCC008000=0.0f;
                lensVertex(rightEdge,top,color); *(volatile f32*)0xCC008000=1.0f; *(volatile f32*)0xCC008000=0.0f;
                lensVertex(left,bottom,color); *(volatile f32*)0xCC008000=0.0f; *(volatile f32*)0xCC008000=1.0f;
                lensVertex(rightEdge,bottom,color); *(volatile f32*)0xCC008000=1.0f; *(volatile f32*)0xCC008000=1.0f;
                layer->endSurface();
            }
            if (layer->mode==0) lensTint(layer,flare,occlusion,distance,header->frontTint);
        } else if (layer->mode==0) {
            PSVECSubtract(lensVec(&cameraPosition),lensVec(&flare->sun),lensVec(&screen));
            PSVECAdd(lensVec(&cameraPosition),lensVec(&screen),lensVec(&screen));
            if (GSgfxProjectFast(&screen,&projected)==2) {
                screen.param1=projected.param1-320.0f; screen.param2=projected.param2-240.0f; screen.param3=0.0f;
                f32 backDistance=PSVECMag(lensVec(&screen));
                if (backDistance>0.00001f && backDistance<(f32)header->outerRadius)
                    lensTint(layer,flare,occlusion,backDistance,header->backTint);
            }
        }
    }
}
}
