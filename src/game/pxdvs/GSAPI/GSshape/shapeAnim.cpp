#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
#include <libc/math.h>

bool GsKeyObject::GetGradationParameter(u8* type, tagGScol4ub* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    *type=a->gradationType;
    tagGScol4ub *first, *second;
    u32 count;
    if(a->gradationType==0) { first=a->gradationU; second=b->gradationU; count=a->gradationCountU; }
    else { first=a->gradationV; second=b->gradationV; count=a->gradationCountV; }
    for(u32 i=0;i<count;i++) {
        out[i].r=(1.0f-t)*first[i].r+t*second[i].r;
        out[i].g=(1.0f-t)*first[i].g+t*second[i].g;
        out[i].b=(1.0f-t)*first[i].b+t*second[i].b;
        out[i].a=(1.0f-t)*first[i].a+t*second[i].a;
    }
    return true;
}
bool GsKeyObject::GetTwistParameter(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    u16 count=a->twistCount;
    f32 *first=a->twist, *second=b->twist;
    for(u32 i=0;i<count;i++) out[i]=(1.0f-t)*first[i]+t*second[i];
    return true;
}
bool GsKeyObject::GetDeformParameterU(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    u16 count=a->deformCountU;
    f32 *first=a->deformU, *second=b->deformU;
    for(u32 i=0;i<count;i++) out[i]=(1.0f-t)*first[i]+t*second[i];
    return true;
}
bool GsKeyObject::GetDeformParameterV(f32* out, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    u16 count=a->deformCountV;
    f32 *first=a->deformV, *second=b->deformV;
    for(u32 i=0;i<count;i++) out[i]=(1.0f-t)*first[i]+t*second[i];
    return true;
}
bool GsKeyObject::GetLinearParameterU(f32* out, const tagGsFilePrimKeyFrame* a) {
    u32 i=0;
    u16 count=a->deformCountU;
    f32 denominator=(u32)(count-1);
    for(;i<count;i++) out[i]=(f32)i/denominator;
    return true;
}
bool GsKeyObject::GetLinearParameterV(f32* out, const tagGsFilePrimKeyFrame* a) {
    u32 i=0;
    u16 count=a->deformCountV;
    f32 denominator=(u32)(count-1);
    for(;i<count;i++) out[i]=(f32)i/denominator;
    return true;
}
bool GsKeyObject::GetFrameInterval(u32 frame, tagGsFilePrimKeyFrame*& a, tagGsFilePrimKeyFrame*& b, f32& t) {
    for(u32 i=0;i<entry->frameCount;i++) {
        if(frame<=frames[i]->frame) {
            u32 previous=i;
            if(i!=0) previous=i-1;
            a=frames[previous]; b=frames[i];
            if(i!=previous) t=(f32)(frame-a->frame)/(f32)(b->frame-a->frame);
            else t=0.0f;
            return true;
        }
    }
    return false;
}

// Curves store cubic Bezier control points; successive segments share their endpoint.
static inline f32 shapeCurve(const GsShapeCurvePoint* points, u8 count, f32 time) {
    const GsShapeCurvePoint* cursor=points;
    int segment=0;
    int segments=(count-1)/3+1;
    for(;segment<segments;cursor+=3,segment++) {
        if(time<cursor->time) break;
    }
    if(segment==0) return points[0].value;
    if(segment==segments) return points[(segments-1)*3].value;
    const GsShapeCurvePoint* first=points+(segment-1)*3;
    f32 square, remaining, remainingSquare, t;
    t=(time-first[0].time)/(points[segment*3].time-first[0].time);
    remaining=1.0f-t; square=t*t; remainingSquare=remaining*remaining;
    return first[3].value*(square*t)+(first[2].value*(3.0f*square*remaining)+(first[0].value*(remainingSquare*remaining)+first[1].value*(3.0f*t*remainingSquare)));
}
f32 GsKeyObject::GetShapeColorAlpha(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32 alpha;
    if(a->colorCurveCount[3]) {
        alpha=255.0f*shapeCurve(a->colorCurves[3],a->colorCurveCount[3],t);
        if(alpha<0.0f) alpha=0.0f;
        else if(alpha>255.0f) alpha=255.0f;
    } else alpha=(1.0f-t)*a->color.a+t*b->color.a;
    return alpha/255.0f;
}
tagGScol4ub GsKeyObject::GetShapeColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32 values[4];
    const u8* first=&a->color.r;
    const u8* second=&b->color.r;
    for(int i=0;i<4;i++) {
        if(a->colorCurveCount[i]) {
            values[i]=255.0f*shapeCurve(a->colorCurves[i],a->colorCurveCount[i],t);
            if(values[i]<0.0f) values[i]=0.0f;
            else if(values[i]>255.0f) values[i]=255.0f;
        } else values[i]=(1.0f-t)*first[i]+t*second[i];
    }
    tagGScol4ub color;
    color.r=values[0]; color.g=values[1]; color.b=values[2]; color.a=values[3];
    return color;
}
bool GsKeyObject::GetShapeRadius(f32* u, f32* v, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32* outputs[2]={0,0}; outputs[0]=u; outputs[1]=v;
    for(int i=0;i<2;i++) {
        if(a->radiusCurveCount[i]) {
            *outputs[i]=entry->radiusScale*shapeCurve(a->radiusCurves[i],a->radiusCurveCount[i],t);
            if(*outputs[i]<0.0f) *outputs[i]=0.0f;
        } else *outputs[i]=a->radius[i]*(1.0f-t)+b->radius[i]*t;
    }
    return true;
}
bool GsKeyObject::GetShapeShowAngle(f32* u, f32* v, const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t) const {
    f32* outputs[2]={0,0}; outputs[0]=u; outputs[1]=v;
    for(int i=0;i<2;i++) {
        if(a->showAngleCurveCount[i]) *outputs[i]=entry->angleScale*shapeCurve(a->showAngleCurves[i],a->showAngleCurveCount[i],t);
        else *outputs[i]=a->showAngle[i]*(1.0f-t)+b->showAngle[i]*t;
    }
    return true;
}
GsShapePair GsKeyObject::GetTextureScale(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 texture) const {
    GsShapePair value; f32* out=&value.u;
    const f32 *first=&a->textureScale[texture].u, *second=&b->textureScale[texture].u;
    for(int i=0;i<2;i++) {
        u8 count=a->textureScaleCurveCount[texture*2+i];
        if(count) out[i]=entry->textureScaleScale*shapeCurve(a->textureScaleCurves[texture*2+i],count,t);
        else out[i]=(1.0f-t)*first[i]+t*second[i];
    }
    return value;
}
GsShapePair GsKeyObject::GetTextureOffset(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 texture) const {
    GsShapePair value; f32* out=&value.u;
    const f32 *first=&a->textureOffset[texture].u, *second=&b->textureOffset[texture].u;
    for(int i=0;i<2;i++) {
        u8 count=a->textureOffsetCurveCount[texture*2+i];
        if(count) out[i]=entry->textureOffsetScale*shapeCurve(a->textureOffsetCurves[texture*2+i],count,t);
        else out[i]=(1.0f-t)*first[i]+t*second[i];
    }
    return value;
}
tagGScol4ub GsKeyObject::GetTextureColor(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 texture) const {
    if(!entry->textureColorAnimated[texture]) return frames[0]->textureColor[texture];
    f32 values[4];
    const u8* first=&a->textureColor[texture].r;
    const u8* second=&b->textureColor[texture].r;
    for(int i=0;i<4;i++) {
        u8 count=a->textureColorCurveCount[texture*4+i];
        if(count) {
            values[i]=255.0f*shapeCurve(a->textureColorCurves[texture*4+i],count,t);
            if(values[i]<0.0f) values[i]=0.0f;
            else if(values[i]>255.0f) values[i]=255.0f;
        } else values[i]=(1.0f-t)*first[i]+t*second[i];
    }
    tagGScol4ub color;
    color.r=values[0]; color.g=values[1]; color.b=values[2]; color.a=values[3];
    return color;
}
tagGScol4ub GsKeyObject::GetTextureColorLow(const tagGsFilePrimKeyFrame* a, const tagGsFilePrimKeyFrame* b, f32 t, u32 texture) const {
    if(!entry->textureColorAnimated[texture]) return frames[0]->textureColorLow[texture];
    f32 values[4];
    const u8* first=&a->textureColorLow[texture].r;
    const u8* second=&b->textureColorLow[texture].r;
    for(int i=0;i<4;i++) {
        u8 count=a->textureColorLowCurveCount[texture*4+i];
        if(count) {
            values[i]=255.0f*shapeCurve(a->textureColorLowCurves[texture*4+i],count,t);
            if(values[i]<0.0f) values[i]=0.0f;
            else if(values[i]>255.0f) values[i]=255.0f;
        } else values[i]=(1.0f-t)*first[i]+t*second[i];
    }
    tagGScol4ub color;
    color.r=values[0]; color.g=values[1]; color.b=values[2]; color.a=values[3];
    return color;
}

extern "C" GSmtx mtxIdent;
bool GsKeyObject::GetShapeMatrix(GSmtx* shape,GSmtx* transform,const tagGsFilePrimObjectEntry* object,u8 count,const u8* order,const tagGsFilePrimKeyFrame* a,const tagGsFilePrimKeyFrame* b,f32 t) const {
    Vec scale,position,pivot,rotation;
    f32* output=&scale.x;
    const f32 *first=&a->scale.x,*second=&b->scale.x;
    for(int i=0;i<3;i++) {
        if(a->transformCurveCount[i]) output[i]=entry->transformScales[0]*shapeCurve(a->transformCurves[i],a->transformCurveCount[i],t);
        else output[i]=(1.0f-t)*first[i]+t*second[i];
    }
    output=&position.x; first=&a->position.x; second=&b->position.x;
    for(int i=0;i<3;i++) {
        if(a->transformCurveCount[i+3]) output[i]=entry->transformScales[1]*shapeCurve(a->transformCurves[i+3],a->transformCurveCount[i+3],t);
        else output[i]=(1.0f-t)*first[i]+t*second[i];
    }
    output=&pivot.x; first=&a->pivot.x; second=&b->pivot.x;
    for(int i=0;i<3;i++) {
        if(a->transformCurveCount[i+6]) output[i]=entry->transformScales[2]*shapeCurve(a->transformCurves[i+6],a->transformCurveCount[i+6],t);
        else output[i]=(1.0f-t)*first[i]+t*second[i];
    }
    output=&rotation.x; first=&a->rotation.x; second=&b->rotation.x;
    for(int i=0;i<3;i++) {
        if(a->transformCurveCount[i+9]) output[i]=entry->transformScales[3]*shapeCurve(a->transformCurves[i+9],a->transformCurveCount[i+9],t);
        else output[i]=(1.0f-t)*first[i]+t*second[i];
    }
    f32 nx=-pivot.x,ny=-pivot.y,nz=-pivot.z;
    u8 scaleInShape=1;
    memcpy(transform,&mtxIdent,sizeof(GSmtx));
    for(int i=0;i<count;i++) {
        switch(order[i]) {
        case 4:
            if(i!=0 && ((f32)fabs(scale.x-1.0f)>0.00001f || (f32)fabs(scale.y-1.0f)>0.00001f || (f32)fabs(scale.z-1.0f)>0.00001f)) {
                PSMTXTransApply(transform->matrix,transform->matrix,nx,ny,nz);
                PSMTXScaleApply(transform->matrix,transform->matrix,scale.x,scale.y,scale.z);
                PSMTXTransApply(transform->matrix,transform->matrix,pivot.x,pivot.y,pivot.z);
                scaleInShape=0;
            }
            break;
        case 0:
            PSMTXTransApply(transform->matrix,transform->matrix,position.x,position.y,position.z); break;
        case 1:
            if((f32)fabs(rotation.x)>0.00001f) {
                Mtx matrix;
                PSMTXTransApply(transform->matrix,transform->matrix,nx,ny,nz);
                PSMTXRotRad(matrix,'x',0.017453292f*rotation.x);
                PSMTXConcat(matrix,transform->matrix,transform->matrix);
                PSMTXTransApply(transform->matrix,transform->matrix,pivot.x,pivot.y,pivot.z);
            }
            break;
        case 2:
            if((f32)fabs(rotation.y)>0.00001f) {
                Mtx matrix;
                PSMTXTransApply(transform->matrix,transform->matrix,nx,ny,nz);
                PSMTXRotRad(matrix,'y',0.017453292f*rotation.y);
                PSMTXConcat(matrix,transform->matrix,transform->matrix);
                PSMTXTransApply(transform->matrix,transform->matrix,pivot.x,pivot.y,pivot.z);
            }
            break;
        case 3:
            if((f32)fabs(rotation.z)>0.00001f) {
                Mtx matrix;
                PSMTXTransApply(transform->matrix,transform->matrix,nx,ny,nz);
                PSMTXRotRad(matrix,'z',0.017453292f*rotation.z);
                PSMTXConcat(matrix,transform->matrix,transform->matrix);
                PSMTXTransApply(transform->matrix,transform->matrix,pivot.x,pivot.y,pivot.z);
            }
            break;
        }
    }
    if(scaleInShape==1) PSMTXScale(shape->matrix,scale.x,scale.z,scale.y);
    else memcpy(shape,&mtxIdent,sizeof(GSmtx));
    if(object->transformEnabled) {
        if(object->rotation2Enabled) {
            Vec axis; axis.x=object->rotationAxis2.x; axis.y=object->rotationAxis2.y; axis.z=object->rotationAxis2.z;
            Mtx matrix; PSMTXRotAxisRad(matrix,&axis,object->rotationAngle2);
            PSMTXConcat(matrix,shape->matrix,shape->matrix);
        }
        if(object->rotation1Enabled) {
            Vec axis; axis.x=object->rotationAxis1.x; axis.y=object->rotationAxis1.y; axis.z=object->rotationAxis1.z;
            Mtx matrix; PSMTXRotAxisRad(matrix,&axis,object->rotationAngle1);
            PSMTXConcat(matrix,shape->matrix,shape->matrix);
        }
        PSMTXTransApply(shape->matrix,shape->matrix,object->position.x,object->position.y,object->position.z);
    }
    return true;
}
