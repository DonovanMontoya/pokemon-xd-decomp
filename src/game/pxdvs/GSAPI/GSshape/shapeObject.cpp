#include <game/pxdvs/GSAPI/GSshape/shapeObjectPrivate.hpp>
#include <dolphin/gx.h>
u32 GsShapeObject::GetPolygonCount() { return entry->segmentsU*entry->segmentsV*2; }
bool GsShapeObject::FreeShapeDrawBuffer(s16 instance) {
    if(instance<0 || instance>=256) return false;
    if(drawBuffers[instance]) { GSmemFree(drawBuffers[instance]); drawBuffers[instance]=0; return true; }
    return false;
}
bool GsShapeObject::CreateShapeDrawBuffer(s16 instance) {
    if(instance<0 || instance>=256) return false;
    drawBuffers[instance]=(u8*)GSmemAlloc(entry->vertexCount*(entry->textureCount*8+16)*2);
    if(!drawBuffers[instance]) return false;
    u16 count=entry->vertexCount;
    for(int buffer=0;buffer<2;buffer++) {
        u32 offset=0;
        if(buffer!=0) offset=count*(entry->textureCount*8+16);
        u8* vertices=drawBuffers[instance]+offset;
        memcpy(vertices,entry->vertices,count*12);
        u8* colors=vertices+count*12;
        memcpy(colors,entry->colors,count*4);
        for(int texture=0;texture<entry->textureCount;texture++)
            memcpy(colors+count*(texture*8+4),entry->textureCoords,count*8);
    }
    return true;
}
void GsShapeObject::FreeDisplayListShape() {
    if(displayList) { GSgfxDLFree(displayList); GSmemFree(displayList); displayList=0; }
}
void GsShapeObject::SetVertexColorSpecify(const tagGScol4ub& value,bool) {
    tagGScol4ub* colors=(tagGScol4ub*)vertexArrays[1];
    if(colors) {
        int columns=entry->segmentsU+1;
        int rows=entry->segmentsV+1;
        for(int row=0;row<rows;row++) {
            for(int column=0;column<columns;column++) {
                colors->r=value.r; colors->g=value.g; colors->b=value.b; colors->a=value.a;
                colors++;
            }
        }
    }
}
void GsShapeObject::SetVertexColorAlpha(int mode,int shape,f32 alpha,bool) {
    tagGScol4ub* out=(tagGScol4ub*)vertexArrays[1];
    if(!out) return;
    const tagGScol4ub* colors=entry->colors;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(mode==0) {
        if(shape!=5) {
            u8 value=255.0f*alpha;
            for(int row=0;row<rows;row++) {
                for(int column=0;column<columns;column++) {
                    out->r=colors->r; out->g=colors->g; out->b=colors->b; out->a=value;
                    colors++; out++;
                }
            }
            return;
        }
        for(int row=0;row<rows;row++) {
            for(int column=0;column<columns;column++) {
                out->r=colors->r*alpha; out->g=colors->g*alpha; out->b=colors->b*alpha; out->a=255;
                colors++; out++;
            }
        }
        return;
    }
    if(shape!=5) {
        for(int row=0;row<rows;row++) {
            for(int column=0;column<columns;column++) {
                out->r=colors->r; out->g=colors->g; out->b=colors->b; out->a=colors->a*alpha;
                colors++; out++;
            }
        }
        return;
    }
    for(int row=0;row<rows;row++) {
        for(int column=0;column<columns;column++) {
            u8 value=colors->a;
            f32 factor=(value/255.0f)*alpha;
            out->r=colors->r*factor; out->g=colors->g*factor; out->b=colors->b*factor; out->a=value;
            colors++; out++;
        }
    }
}
void GsShapeObject::SetVertexColorGradation(u8 axis,const tagGScol4ub* colors,int shape,f32 alpha,bool) {
    tagGScol4ub* out=(tagGScol4ub*)vertexArrays[1];
    if(!out) return;
    int columns=entry->segmentsU+1,rows=entry->segmentsV+1;
    if(shape==2 || shape==4) {
        const tagGScol4ub* rowColor=colors;
        for(int row=0;row<rows;row++,rowColor++) {
            const tagGScol4ub* columnColor=colors;
            if(axis==0) {
                for(int column=0;column<columns;column++,columnColor++,out++) {
                    out->r=columnColor->r; out->g=columnColor->g; out->b=columnColor->b; out->a=alpha*columnColor->a;
                }
            } else {
                for(int column=0;column<columns;column++,out++) {
                    out->r=rowColor->r; out->g=rowColor->g; out->b=rowColor->b; out->a=alpha*rowColor->a;
                }
            }
        }
        return;
    }
    const tagGScol4ub* rowColor=colors;
    for(int row=0;row<rows;row++,rowColor++) {
        const tagGScol4ub* columnColor=colors;
        if(axis==0) {
            for(int column=0;column<columns;column++,columnColor++,out++) {
                out->r=alpha*(columnColor->r*(columnColor->a/255.0f));
                out->g=alpha*(columnColor->g*(columnColor->a/255.0f));
                out->b=alpha*(columnColor->b*(columnColor->a/255.0f)); out->a=columnColor->a;
            }
        } else {
            for(int column=0;column<columns;column++,out++) {
                out->r=alpha*(rowColor->r*(rowColor->a/255.0f));
                out->g=alpha*(rowColor->g*(rowColor->a/255.0f));
                out->b=alpha*(rowColor->b*(rowColor->a/255.0f)); out->a=rowColor->a;
            }
        }
    }
}

extern "C" {
void GSgfxDLBegin(void*, void*, u32, u32);
void GSgfxDLEnd();
void GSgfxDLPrimitiveType(u32);
void GSgfxDLBeginSurface(u16);
void GSgfxDLEndSurface();
}
void GsShapeObject::MakeShapeGfxDL() {
    u32 vertexCount;
    u16 row;
    u16 base;
    u16 textureCount;
    u16 columns;
    columns = entry->segmentsU + 1;
    textureCount = entry->textureCount;
    GSgfxDLPrimitiveType(0x98);
    vertexCount = columns * 2;
    for (row = 0; row < entry->segmentsV; ++row) {
        u16 column;
        base = row * columns;
        GSgfxDLBeginSurface(vertexCount);
        u16 next = (row + 1) * columns;
        for (column = 0; column < columns; ++column) {
            u16 first = column + base;
            u16 second = column + next;
            u16 i;
            GXWGFifo.u16 = first;
            GXWGFifo.u16 = first;
            for (i = 0; i < textureCount; ++i) GXWGFifo.u16 = first;
            GXWGFifo.u16 = second;
            GXWGFifo.u16 = second;
            for (i = 0; i < textureCount; ++i) GXWGFifo.u16 = second;
        }
        GSgfxDLEndSurface();
    }
}
void GsShapeObject::MakeDisplayListShape() {
    displayList=GSmemAlloc(16);
    if(displayList) {
        u16 indices=entry->segmentsV*((entry->segmentsU+1)*2);
        u16 rows=entry->segmentsV;
        memset(displayList,0,16);
        GSgfxDLBegin(displayList,vertexFormat,rows,indices);
        MakeShapeGfxDL();
        GSgfxDLEnd();
    }
}
bool GsShapeObject::DeformTextureCoord(u32 texture,bool deform,const f32* u,const f32* v,bool twistEnabled,const f32* twist) {
    GsShapePair* out=(GsShapePair*)vertexArrays[texture+2];
    if(!out) return false;
    const GsShapePair* original=entry->textureCoords;
    int columns=entry->segmentsU+1;
    f32 offset=0.0f;
    for(int row=0;row<entry->segmentsV+1;row++,v++,twist++) {
        if(twistEnabled==1) offset=*twist;
        if(deform==1) {
            for(int column=0;column<columns;column++,out++) {
                out->u=offset+u[column]; out->v=*v;
            }
        } else {
            for(int column=0;column<columns;column++,out++,original++) {
                out->u=original->u+offset; out->v=original->v;
            }
        }
    }
    return true;
}
#include <libc/math.h>
extern "C" double tan(double);
bool GsShapeObject::DeformVertexCoord(bool deform,const f32* u,const f32* v,bool radius,f32 radiusU,f32 radiusV,bool angle,f32 angleU,f32 angleV,bool twistEnabled,const f32* twist) {
    switch(entry->geometryType) {
    case 30: {
        Vec* out=(Vec*)vertexArrays[0];
        if(!out) return false;
        f32 width=entry->width, height=entry->height;
        f32 left=0.5f*-width, bottom=0.5f*-height;
        f32 shear=0.0f;
        int columns=entry->segmentsU+1, rows=entry->segmentsV+1;
        if(!angle) angleU=entry->shearAngle;
        if((f32)fabs(angleU)>0.00001f) shear=entry->height*(f32)tan(0.017453292f*angleU);
        for(int row=0;row<rows;row++,twist++,v++) {
            f32 z=twistEnabled?*twist:0.0f;
            f32 vertical=deform?*v:(f32)row/(f32)(rows-1);
            f32 shift=shear*vertical;
            f32 y=height*vertical+bottom;
            const f32* horizontal=u;
            if(deform) {
                for(int column=0;column<columns;column++,horizontal++,out++) {
                    out->x=width*(*horizontal)+left+shift; out->y=y; out->z=z;
                }
            } else {
                for(int column=0;column<columns;column++,out++) {
                    out->x=width*((f32)column/(f32)(columns-1))+left+shift; out->y=y; out->z=z;
                }
            }
        }
        return true;
    }
    case 31: return DeformVertexCoordCylinderEx(deform,u,v,radius,radiusU,radiusV,angle,angleU,twistEnabled,twist);
    case 32: return DeformVertexCoordSpiral(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    case 33: return DeformVertexCoordSphere(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    case 34: return DeformVertexCoordTorus(deform,u,v,radius,radiusU,radiusV,angle,angleU,angleV,twistEnabled,twist);
    default: return false;
    }
}

bool GsShapeObject::WaveTextureCoord(u32 texture,f32 offsetU,f32 offsetV,const GSmtx* matrix,bool accumulate) {
    GsShapePair* out=(GsShapePair*)vertexArrays[texture+2];
    if(!out) return false;
    if(texture==0 && entry->textureCount>=2) return false;
    const Vec* displacement=(const Vec*)entry->reserved1C;
    if(!displacement) return false;
    if(!accumulate) memcpy(out,entry->textureCoords,entry->vertexCount*sizeof(GsShapePair));
    u16 segmentsU=entry->segmentsU,segmentsV=entry->segmentsV;
    int columns=segmentsU+1,rows=segmentsV+1;
    if(offsetU>1.0f) offsetU-=(f32)(int)offsetU;
    else if(offsetU<0.0f) offsetU-=(f32)((int)offsetU-1);
    if(offsetV>1.0f) offsetV-=(f32)(int)offsetV;
    else if(offsetV<0.0f) offsetV-=(f32)((int)offsetV-1);
    int shiftU=(int)(offsetU*(f32)segmentsU)%segmentsU;
    int shiftV=(int)(offsetV*(f32)segmentsV)%segmentsV;
    f32 fractionU=(f32)segmentsU*(offsetU-(f32)shiftU/(f32)segmentsU);
    f32 fractionV=(f32)segmentsV*(offsetV-(f32)shiftV/(f32)segmentsV);
    fractionU-=(f32)(int)fractionU; fractionV-=(f32)(int)fractionV;
    f32 diagonalWeight=fractionU*fractionV;
    f32 verticalWeight=(1.0f-fractionU)*fractionV;
    f32 horizontalWeight=fractionU*(1.0f-fractionV);
    f32 originWeight=(1.0f-fractionU)*(1.0f-fractionV);
    int rowOffset=0;
    for(int row=0;row<rows;row++,rowOffset+=columns) {
        for(int column=0;column<columns;column++) {
            u16 sampleU=(column+shiftU)%entry->segmentsU;
            int sampleV=(row+shiftV)%entry->segmentsV;
            if(sampleU==0 && column==columns-1) sampleU=entry->segmentsU;
            if(sampleV==0 && row==rows-1) sampleV=entry->segmentsV;
            int sample=sampleU+sampleV*columns;
            Vec value;
            if(sampleU==columns-1 || sampleV==rows-1) {
                value.x=displacement[sample].x; value.y=displacement[sample].y; value.z=displacement[sample].z;
            } else {
                Vec result, diagonal,vertical,horizontal,origin,sumHorizontal,sumVertical;
                int nextRow=sample+columns;
                PSVECScale(&displacement[nextRow+1],&result,diagonalWeight);
                diagonal.x=result.x; diagonal.y=result.y; diagonal.z=result.z;
                PSVECScale(&displacement[nextRow],&result,verticalWeight);
                vertical.x=result.x; vertical.y=result.y; vertical.z=result.z;
                PSVECScale(&displacement[sample+1],&result,horizontalWeight);
                horizontal.x=result.x; horizontal.y=result.y; horizontal.z=result.z;
                PSVECScale(&displacement[sample],&result,originWeight);
                origin.x=result.x; origin.y=result.y; origin.z=result.z;
                PSVECAdd(&origin,&horizontal,&result);
                sumHorizontal.x=result.x; sumHorizontal.y=result.y; sumHorizontal.z=result.z;
                PSVECAdd(&sumHorizontal,&vertical,&result);
                sumVertical.x=result.x; sumVertical.y=result.y; sumVertical.z=result.z;
                PSVECAdd(&sumVertical,&diagonal,&result);
                value.x=result.x; value.y=result.y; value.z=result.z;
            }
            PSMTXMultVecSR(matrix->matrix,&value,&value);
            GsShapePair* coordinate=&out[rowOffset+column];
            coordinate->u+=value.x; coordinate->v+=value.y;
        }
    }
    return true;
}

void GSgfxLayer::tunitAlphaOp(u8 unit, GSgfxTunitOp operation, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp, GSgfxTunitReg output) {
    alphaOps[unit].operation = operation;
    alphaOps[unit].bias = bias;
    alphaOps[unit].scale = scale;
    alphaOps[unit].clamp = clamp;
    alphaOps[unit].output = output;
    alphaOpDirty |= 1 << unit;
    dirty |= 8;
    savedAlphaOpDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitAlphaArg(u8 unit, GSgfxTunitAArg a, GSgfxTunitAArg b, GSgfxTunitAArg c, GSgfxTunitAArg d) {
    alphaArgs[unit][0] = a;
    alphaArgs[unit][1] = b;
    alphaArgs[unit][2] = c;
    alphaArgs[unit][3] = d;
    alphaArgDirty |= 1 << unit;
    dirty |= 8;
    savedAlphaArgDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitColorOp(u8 unit, GSgfxTunitOp operation, GSgfxTunitBias bias, GSgfxTunitScale scale, bool clamp, GSgfxTunitReg output) {
    colorOps[unit].operation = operation;
    colorOps[unit].bias = bias;
    colorOps[unit].scale = scale;
    colorOps[unit].clamp = clamp;
    colorOps[unit].output = output;
    colorOpDirty |= 1 << unit;
    dirty |= 8;
    savedColorOpDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitColorArg(u8 unit, GSgfxTunitCArg a, GSgfxTunitCArg b, GSgfxTunitCArg c, GSgfxTunitCArg d) {
    colorArgs[unit][0] = a;
    colorArgs[unit][1] = b;
    colorArgs[unit][2] = c;
    colorArgs[unit][3] = d;
    colorArgDirty |= 1 << unit;
    dirty |= 8;
    savedColorArgDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::tunitMapping(u8 unit, u8 texture, u8 coordinate, u8 color) {
    mapping[unit].texture = texture;
    mapping[unit].coordinate = coordinate;
    if (color != 0xff) mapping[unit].color = color + 4;
    else mapping[unit].color = 0xff;
    mappingDirty |= 1 << unit;
    dirty |= 8;
    savedMappingDirty |= 1 << unit;
    savedDirty |= 8;
}
void GSgfxLayer::texSelect(u8 unit, GStexture* texture) {
    if (textures[unit] == texture && savedTextures[unit] == texture && !texture->dirty) return;
    textures[unit] = texture;
    textureDirty |= 1 << unit;
    savedTextures[unit] = texture;
    savedTextureDirty |= 1 << unit;
}

extern "C" void GSgfxVFSetArray(void*, s32, s32, void*, u8, u32);
extern "C" void dlDraw__10GSgfxLayerFP7GSgfxDL(GSgfxLayer*, void*);
extern "C" void beginSurface__10GSgfxLayerFUs(GSgfxLayer*, u16);
extern "C" void endSurface__10GSgfxLayerFv(GSgfxLayer*);
struct ShapeAttributeTable { u32 value[4]; };
static const ShapeAttributeTable kShapeAttributes = {{13, 14, 15, 16}};
extern "C" void DrawShapeGfx__13GsShapeObjectFP10GSgfxLayersUc(GsShapeObject* self, GSgfxLayer* layer, s16, u8) {
    ShapeAttributeTable attributes = kShapeAttributes;
    u16 vertexCount;
    u16 textureCount;
    u16 columns;
    s32 i;
    bool ready;
    columns = self->entry->segmentsU + 1;
    textureCount = self->entry->textureCount;
    vertexCount = self->entry->vertexCount;
    if (self->vertexArrays[0] == 0) {
        ready = false;
        goto done;
    }
    if (self->vertexArrays[0] != 0) {
        GSgfxVFSetArray(self->vertexFormat, 9, 3, self->vertexArrays[0], 12, vertexCount * 12);
    } else {
        ready = false;
        goto done;
    }
    if (self->vertexArrays[1] != 0) {
        GSgfxVFSetArray(self->vertexFormat, 11, 3, self->vertexArrays[1], 4, vertexCount * 4);
    } else {
        ready = false;
        goto done;
    }
    for (i = 0; i < self->entry->textureCount; ++i) {
        if (self->vertexArrays[2 + i] != 0) {
            GSgfxVFSetArray(self->vertexFormat, attributes.value[i], 3, self->vertexArrays[2 + i], 8, vertexCount * 8);
        } else {
            ready = false;
            goto done;
        }
    }
    ready = true;
done:
    if (ready) {
        u16 row;
        *(u32*)((u8*)layer + 0x199c) = (u32)self->vertexFormat;
        *(u32*)((u8*)layer + 0x1998) = 0x98;
        u32 vertexTotal = columns * 2;
        for (row = 0; row < self->entry->segmentsV; ++row) {
            u16 column;
            u16 base = row * columns;
            beginSurface__10GSgfxLayerFUs(layer, vertexTotal);
            u16 next = (row + 1) * columns;
            for (column = 0; column < columns; ++column) {
                u16 first = column + base;
                u16 second = column + next;
                u16 j;
                GXWGFifo.u16 = first;
                GXWGFifo.u16 = first;
                for (j = 0; j < textureCount; ++j) GXWGFifo.u16 = first;
                GXWGFifo.u16 = second;
                GXWGFifo.u16 = second;
                for (j = 0; j < textureCount; ++j) GXWGFifo.u16 = second;
            }
            endSurface__10GSgfxLayerFv(layer);
        }
    }
}

extern "C" void SetStateMode__13GsShapeObjectFP10GSgfxLayer(GsShapeObject* self, GSgfxLayer* layer) {
    u8 depth = self->entry->reserved05[0] != 0;
    u8 alpha = self->entry->reserved05[1] != 0;
    u8 type;
    if (self->entry->shapeType == 8) {
        depth = 1;
        alpha = 1;
    }
    if (depth == 1) layer->depthEnable = 1;
    else layer->depthEnable = 0;
    layer->depthFunction = 1;
    layer->markPixel(8);
    layer->colorUpdate = 1;
    layer->alphaUpdate = 1;
    if (alpha == 1) layer->destinationAlpha = 1;
    else layer->destinationAlpha = 0;
    layer->markPixel(4);
    layer->cullMode = *((u8*)self->entry + 0xd8);
    layer->transformDirty |= 2;
    layer->dirty |= 2;
    layer->savedTransformDirty |= 2;
    layer->savedDirty |= 2;
    type = self->entry->shapeType;
    if (type == 10 && self->entry->textureCount >= 2) {
        u8 blend = *((u8*)self->entry->textures[1] + 0xa);
        switch (blend) {
        case 2:
        case 4:
            type = blend;
            break;
        }
    }
    switch (type) {
    case 4:
        layer->selectShader(1);
        layer->setBlend(1, 4, 1, 5);
        break;
    case 5:
        layer->selectShader(1);
        layer->setBlend(3, 4, 1, 5);
        break;
    case 2:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    case 8:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    case 10:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    default:
        layer->selectShader(1);
        layer->setBlend(1, 4, 5, 5);
        break;
    }
}

extern "C" void CallDisplayListShape__13GsShapeObjectFP10GSgfxLayersUc(GsShapeObject* self, GSgfxLayer* layer, s16 instance, u8 flags) {
    if (self->displayList) {
        s32 vertexCount;
        tagGsFilePrimObjectEntry* entry = self->entry;
        u32 attributes[4] = {13, 14, 15, 16};
        vertexCount = entry->vertexCount;
        if (self->vertexArrays[0] != 0) {
            if (self->vertexArrays[0] != 0) {
                GSgfxVFSetArray(self->vertexFormat, 9, 3, self->vertexArrays[0], 12, vertexCount * 12);
                if (self->vertexArrays[1] != 0) {
                    GSgfxVFSetArray(self->vertexFormat, 11, 3, self->vertexArrays[1], 4, vertexCount * 4);
                    GsShapeObject* arrays = self;
                    u32* attribute = attributes;
                    u32 size = vertexCount * 8;
                    for (vertexCount = 0; vertexCount < self->entry->textureCount; arrays = (GsShapeObject*)((u8*)arrays + 4), ++attribute, ++vertexCount) {
                        if (arrays->vertexArrays[2] == 0) break;
                        GSgfxVFSetArray(self->vertexFormat, *attribute, 3, arrays->vertexArrays[2], 8, size);
                    }
                }
            }
        }
        dlDraw__10GSgfxLayerFP7GSgfxDL(layer, self->displayList);
    } else {
        DrawShapeGfx__13GsShapeObjectFP10GSgfxLayersUc(self, layer, instance, flags);
    }
}

#pragma dont_inline off
static inline u32 &shapeStateWord(GSgfxLayer *layer,u32 offset) { return *(u32*)((u8*)layer+offset); }
static inline void shapeKColorSelect(GSgfxLayer *layer,u8 stage,u32 value) {
 shapeStateWord(layer,0x1504+stage*4)=value;shapeStateWord(layer,0x16fc)|=1<<stage;layer->dirty|=0x10;shapeStateWord(layer,0x17b4)|=1<<stage;layer->savedDirty|=0x10;
}
static inline void shapeKAlphaSelect(GSgfxLayer *layer,u8 stage,u32 value) {
 shapeStateWord(layer,0x1544+stage*4)=value;shapeStateWord(layer,0x1700)|=1<<stage;layer->dirty|=0x10;shapeStateWord(layer,0x17b8)|=1<<stage;layer->savedDirty|=0x10;
}
#pragma dont_inline on
extern "C" void SetStateTexture__13GsShapeObjectFP10GSgfxLayerP14GsShapeTextureP9GStexture(GsShapeObject *self,GSgfxLayer *layer,GsShapeTexture *textures,GStexture *refract) {
 u32 colorRegisters[4]={12,13,14,15},alphaRegisters[4]={28,29,30,31};
 u8 stage=0,textureIndex=0,count=self->entry->textureCount;
 int var_r5_2,var_r5_3,var_r5_4,var_r5_5,var_r6_2,var_r6_3,var_r6_4,var_r7,var_r7_2,var_r7_3,var_r8,var_r8_10,var_r8_11,var_r8_12,var_r8_13,var_r8_14,var_r8_2,var_r8_3,var_r8_4,var_r8_5,var_r8_6,var_r8_7,var_r8_8,var_r8_9;
 while(textureIndex<count) {
  ShapeTextureBinding *binding=(ShapeTextureBinding*)self->entry->textures[textureIndex];
  GsShapeTexture *texture=&textures[binding->index];
  GStextureSetFilter(texture->texture,binding->minFilter?2:1,binding->magFilter?2:1,binding->minFilter?2:1);
  GStextureSetWrap(texture->texture,binding->wrapS,binding->wrapT);
  GStexture *selected=texture->texture;if(textureIndex==0&&refract)selected=refract;
  if(self->entry->shapeType==10&&textureIndex==0&&self->entry->textureCount>=2) {
   layer->texSelect(textureIndex,selected);
   layer->tunitMapping(stage,textureIndex,textureIndex,0);
   layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
   layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   u8 next=stage+1;
   layer->tunitMapping(next,textureIndex,textureIndex,0);
   layer->tunitColorArg(next,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
   layer->tunitColorOp(next,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(next,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(next,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   stage+=2;
   if(texture->entry->colorRange==1) {
    layer->tunitMapping(stage,textureIndex,textureIndex,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
    ++stage;
   }
  } else if(textureIndex<2) {
   if(texture->entry->colorRange) {
    u8 middle=stage+1,mixStage=stage+2;
    shapeKColorSelect(layer,stage,colorRegisters[textureIndex*2]);shapeKAlphaSelect(layer,stage,alphaRegisters[textureIndex*2]);
    shapeKColorSelect(layer,middle,colorRegisters[textureIndex*2+1]);shapeKAlphaSelect(layer,middle,alphaRegisters[textureIndex*2+1]);shapeKAlphaSelect(layer,mixStage,alphaRegisters[1]);
    layer->texSelect(textureIndex,selected);layer->tunitMapping(stage,textureIndex,textureIndex,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)15,(GSgfxTunitCArg)14);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)6,(GSgfxTunitAArg)4,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitMapping(middle,textureIndex,textureIndex,0);
    layer->tunitColorArg(middle,(GSgfxTunitCArg)14,(GSgfxTunitCArg)2,(GSgfxTunitCArg)8,(GSgfxTunitCArg)15);
    layer->tunitColorOp(middle,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)2);
    layer->tunitAlphaArg(middle,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)7,(GSgfxTunitAArg)1);
    layer->tunitAlphaOp(middle,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)2);
    layer->tunitMapping(mixStage,textureIndex,textureIndex,0);
    switch(binding->blend) {

                case 0:
                    var_r7 = 0;
                    if (textureIndex == 0) {
                        var_r7 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(var_r7), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r7_2 = 0;
                    if (textureIndex == 0) {
                        var_r7_2 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(var_r7_2), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 2:
                    var_r5_2 = 0;
                    if (textureIndex == 0) {
                        var_r5_2 = 4;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(var_r5_2), (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r5_3 = 0;
                    if (textureIndex == 0) {
                        var_r5_3 = 2;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(var_r5_3), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 3:
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(4));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 4:
                    var_r8 = 0;
                    if (textureIndex == 0) {
                        var_r8 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_2 = 0;
                    if (textureIndex == 0) {
                        var_r8_2 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_2));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 5:
                    var_r8_3 = 0;
                    if (textureIndex == 0) {
                        var_r8_3 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_3));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(textureIndex != 0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_4 = 0;
                    if (textureIndex == 0) {
                        var_r8_4 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_4));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 9:
                    var_r8_5 = 0;
                    if (textureIndex == 0) {
                        var_r8_5 = 4;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_5));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r7_3 = 0;
                    if (textureIndex == 0) {
                        var_r7_3 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(var_r7_3), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                default:
                    var_r8_6 = 0;
                    if (textureIndex == 0) {
                        var_r8_6 = 0xA;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(4), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_6));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_7 = 0;
                    if (textureIndex == 0) {
                        var_r8_7 = 5;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(2), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;

    }stage+=3;
   } else {
    u8 mixStage=stage+1;
    shapeKColorSelect(layer,stage,colorRegisters[textureIndex*2]);shapeKAlphaSelect(layer,stage,alphaRegisters[textureIndex*2]);shapeKAlphaSelect(layer,mixStage,alphaRegisters[1]);
    layer->texSelect(textureIndex,selected);layer->tunitMapping(stage,textureIndex,textureIndex,0);
    layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)14,(GSgfxTunitCArg)8,(GSgfxTunitCArg)15);
    layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)6,(GSgfxTunitAArg)4,(GSgfxTunitAArg)7);
    layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)1);
    layer->tunitMapping(mixStage,textureIndex,textureIndex,0);
    switch(binding->blend) {

                case 0:
                    var_r6_2 = 0;
                    if (textureIndex == 0) {
                        var_r6_2 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r6_2), (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r6_3 = 0;
                    if (textureIndex == 0) {
                        var_r6_3 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r6_3), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 2:
                    var_r5_4 = 0;
                    if (textureIndex == 0) {
                        var_r5_4 = 0xC;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(var_r5_4), (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r5_5 = 0;
                    if (textureIndex == 0) {
                        var_r5_5 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(var_r5_5), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 3:
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xE), (GSgfxTunitCArg)(0xF));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(6), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 4:
                    var_r8_8 = 0;
                    if (textureIndex == 0) {
                        var_r8_8 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_8));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_9 = 0;
                    if (textureIndex == 0) {
                        var_r8_9 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_9));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 5:
                    var_r8_10 = 0;
                    if (textureIndex == 0) {
                        var_r8_10 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_10));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(textureIndex != 0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_11 = 0;
                    if (textureIndex == 0) {
                        var_r8_11 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_11));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                case 9:
                    var_r8_12 = 0;
                    if (textureIndex == 0) {
                        var_r8_12 = 8;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_12));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r6_4 = 0;
                    if (textureIndex == 0) {
                        var_r6_4 = 6;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r6_4), (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;
                default:
                    var_r8_13 = 0;
                    if (textureIndex == 0) {
                        var_r8_13 = 0xF;
                    }
                    layer->tunitColorArg(mixStage, (GSgfxTunitCArg)(2), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(var_r8_13));
                    layer->tunitColorOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    var_r8_14 = 0;
                    if (textureIndex == 0) {
                        var_r8_14 = 7;
                    }
                    layer->tunitAlphaArg(mixStage, (GSgfxTunitAArg)(1), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(var_r8_14));
                    layer->tunitAlphaOp(mixStage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                    break;

    }stage+=2;
   }
  } else {
   layer->texSelect(textureIndex,selected);layer->tunitMapping(stage,textureIndex,textureIndex,0);
   switch(binding->blend) {

            case 0:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0), (GSgfxTunitCArg)(0xF));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(0), (GSgfxTunitAArg)(7));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 2:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0), (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(9), (GSgfxTunitCArg)(0xF));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 3:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(8));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 4:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 5:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(1), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            case 9:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(0), (GSgfxTunitAArg)(7));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;
            default:
                layer->tunitColorArg(stage, (GSgfxTunitCArg)(8), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0xF), (GSgfxTunitCArg)(0));
                layer->tunitColorOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                layer->tunitAlphaArg(stage, (GSgfxTunitAArg)(4), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(7), (GSgfxTunitAArg)(0));
                layer->tunitAlphaOp(stage, (GSgfxTunitOp)(0), (GSgfxTunitBias)(0), (GSgfxTunitScale)(0), 1, (GSgfxTunitReg)(0));
                break;

   }++stage;
  }
  if(textureIndex==count-1) {
   layer->tunitMapping(stage,textureIndex,textureIndex,0);
   layer->tunitColorArg(stage,(GSgfxTunitCArg)15,(GSgfxTunitCArg)10,(GSgfxTunitCArg)0,(GSgfxTunitCArg)15);
   layer->tunitColorOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   layer->tunitAlphaArg(stage,(GSgfxTunitAArg)7,(GSgfxTunitAArg)5,(GSgfxTunitAArg)0,(GSgfxTunitAArg)7);
   layer->tunitAlphaOp(stage,(GSgfxTunitOp)0,(GSgfxTunitBias)0,(GSgfxTunitScale)0,true,(GSgfxTunitReg)0);
   ++stage;
  }++textureIndex;
 }
}

#pragma dont_inline off

extern "C" f32* GSgfxMatrixGetPtr(s32);
extern "C" bool RefractTextureCoord__13GsShapeObjectFffP5GSmtxP5GSmtxP5GSmtxf(GsShapeObject *self,f32 offsetU,f32 offsetV,GSmtx *first,GSmtx *second,GSmtx *third,f32) {
 Mtx transform,projectionMatrix;f32 *sourceProjection=GSgfxMatrixGetPtr(4);
 f32 projection[7]={0.0f,sourceProjection[0],sourceProjection[2],sourceProjection[5],sourceProjection[6],sourceProjection[10],sourceProjection[11]};
 f32 viewport[6]={0.0f,0.0f,640.0f,480.0f,0.0f,1.0f};
 for(s32 texture=0;texture<self->entry->textureCount;++texture) {
  const Vec *normalGrid=(const Vec*)self->entry->reserved1C;const Vec *positions=self->entry->vertices;
  if(!normalGrid)continue;GsShapePair *out=(GsShapePair*)self->vertexArrays[texture+2];if(!out)continue;
  PSMTXCopy(second->matrix,transform);
  if(texture==0){PSMTXConcat(first->matrix,transform,transform);PSMTXConcat(third->matrix,transform,transform);memcpy(projectionMatrix,transform,sizeof(Mtx));}
  else memcpy(out,self->entry->textureCoords,self->entry->vertexCount*sizeof(GsShapePair));
  u16 segmentsU=self->entry->segmentsU,segmentsV=self->entry->segmentsV;int columns=segmentsU+1,rows=segmentsV+1;
  if(offsetU>1.0f)offsetU-=(f32)(int)offsetU;else if(offsetU<0.0f)offsetU-=(f32)((int)offsetU-1);
  if(offsetV>1.0f)offsetV-=(f32)(int)offsetV;else if(offsetV<0.0f)offsetV-=(f32)((int)offsetV-1);
  int shiftU=(int)(offsetU*(f32)segmentsU)%segmentsU,shiftV=(int)(offsetV*(f32)segmentsV)%segmentsV;
  f32 fractionU=(f32)segmentsU*(offsetU-(f32)shiftU/(f32)segmentsU),fractionV=(f32)segmentsV*(offsetV-(f32)shiftV/(f32)segmentsV);
  fractionU-=(f32)(int)fractionU;fractionV-=(f32)(int)fractionV;
  f32 diagonalWeight=fractionU*fractionV,verticalWeight=(1.0f-fractionU)*fractionV,horizontalWeight=fractionU*(1.0f-fractionV),originWeight=(1.0f-fractionU)*(1.0f-fractionV);
  int rowOffset=0;
  for(int row=0;row<rows;++row,rowOffset+=columns) {
   for(int column=0;column<columns;++column) {
    u16 sampleU=(column+shiftU)%self->entry->segmentsU;int sampleV=(row+shiftV)%self->entry->segmentsV;
    if(sampleU==0&&column==columns-1)sampleU=self->entry->segmentsU;
    if(sampleV==0&&row==rows-1)sampleV=self->entry->segmentsV;
    int sample=sampleU+sampleV*columns;Vec value;
    if(sampleU==columns-1&&sampleV==rows-1)value=normalGrid[sample];
    else {
     int diagonal,vertical,horizontal;
     if(sampleU==columns-1){diagonal=sample+columns+1;vertical=sample+columns;horizontal=sample-1;}
     else if(sampleV==rows-1){diagonal=sample-columns+1;vertical=sample-columns;horizontal=sample+1;}
     else{diagonal=sample+columns+1;vertical=sample+columns;horizontal=sample+1;}
     Vec a,b,c,d,sum;PSVECScale(&normalGrid[diagonal],&a,diagonalWeight);PSVECScale(&normalGrid[vertical],&b,verticalWeight);PSVECScale(&normalGrid[horizontal],&c,horizontalWeight);PSVECScale(&normalGrid[sample],&d,originWeight);PSVECAdd(&d,&c,&sum);PSVECAdd(&sum,&b,&sum);PSVECAdd(&sum,&a,&value);
    }
    PSMTXMultVecSR(transform,&value,&value);int index=rowOffset+column;
    if(texture==0) {
     f32 x,y,z;GXProject(positions[index].x,positions[index].y,positions[index].z,projectionMatrix,projection,viewport,&x,&y,&z);
     if((f32)fabs(value.x)>0.00001f||(f32)fabs(value.y)>0.00001f||(f32)fabs(value.z)>0.00001f) {
      PSVECNormalize(&value,&value);
      if(value.x<=0.0f)x=x*(1.0f+value.x);else x=value.x*(640.0f-x)+x;
      if(value.y<=0.0f)y+=-value.y*(480.0f-y);else y*=1.0f-value.y;
     }
     out[index].u=x/640.0f;out[index].v=y/480.0f;
    }else {out[index].u+=value.x;out[index].v+=value.y;}
   }
  }
 }
 return true;
}
#pragma dont_inline off
extern "C" double acos(double);
static inline f32 shapeAngularWeight(Vec *normal,Vec *view,f32 width) {
 f32 dot=(f32)fabs(PSVECDotProduct(normal,view));
 if(dot>1.0f||width<0.00001f)return 1.0f;
 f32 distance=sqrtf(1.0f-dot),threshold=1.0f-width;
 if(distance<=threshold)return 1.0f;
 f32 weight=(f32)cos((1.5707964f*(distance-threshold))/width);return weight*weight;
}
#pragma dont_inline on
extern "C" bool ShadeVertexColor__13GsShapeObjectFP5GSmtxP5GSmtxP5GSmtxfb(GsShapeObject *self,GSmtx *first,GSmtx *second,GSmtx *third,f32 distance,bool preserveNormal) {
 if(!self->vertexArrays[1])return false;
 Mtx transform,rotation;PSMTXCopy(second->matrix,transform);PSMTXConcat(first->matrix,transform,transform);PSMTXConcat(third->matrix,transform,transform);
 Vec *normals=(Vec*)self->entry->reserved1C,*positions=self->entry->vertices;tagGScol4ub *colors=(tagGScol4ub*)self->vertexArrays[1];u16 count=self->entry->vertexCount;
 for(int i=0;i<count;++i,++normals,++positions,++colors) {
  Vec normal=*normals,position=*positions,view;PSMTXMultVecSR(transform,&normal,&normal);PSMTXMultVec(transform,&position,&view);f32 viewZ=view.z;view.z=viewZ-distance;
  f32 weight,width=*(f32*)((u8*)self->entry+0xd0);
  switch(self->entry->colorMode) {
  case 1:normal.y=0.0f;view.y=0.0f;
   if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,width);}else weight=0.0f;break;
  case 2:normal.x=0.0f;view.x=0.0f;
   if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,width);}else weight=0.0f;break;
  case 3:
   if((self->entry->geometryType==31&&*((u8*)self->entry+0xce)==1&&!preserveNormal)||(self->entry->geometryType==32&&(*((u8*)self->entry+0xcc)%2)==0)) {
    Vec forward={0.0f,0.0f,1.0f},axis;PSMTXMultVecSR(transform,&forward,&forward);PSVECCrossProduct(&view,&forward,&axis);
    if(PSVECSquareMag(&axis)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&axis,&axis);PSVECNormalize(&view,&view);PSMTXRotAxisRad(rotation,&axis,1.5707964f-(f32)acos(PSVECDotProduct(&forward,&view)));PSMTXMultVecSR(rotation,&normal,&normal);weight=shapeAngularWeight(&normal,&view,width);}else weight=0.0f;
   }else if(PSVECSquareMag(&normal)>9.9999994e-11f&&PSVECSquareMag(&view)>9.9999994e-11f){PSVECNormalize(&normal,&normal);PSVECNormalize(&view,&view);weight=shapeAngularWeight(&normal,&view,width);}else weight=0.0f;break;
  default:weight=1.0f;break;
  }
  if(viewZ>0.0f&&distance>0.00001f){f32 attenuation;if(viewZ>distance)attenuation=0.0f;else attenuation=(distance-viewZ)/distance;weight*=attenuation;}
  switch(self->entry->shapeType){case 2:case 8:case 10:colors->a=weight*colors->a;break;default:colors->r=weight*colors->r;colors->g=weight*colors->g;colors->b=weight*colors->b;break;}
 }
 return true;
}
#pragma dont_inline off
