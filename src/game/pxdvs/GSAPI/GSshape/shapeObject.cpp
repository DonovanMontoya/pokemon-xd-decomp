#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
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
