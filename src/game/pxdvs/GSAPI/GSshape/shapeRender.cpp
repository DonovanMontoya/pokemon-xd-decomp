#include <game/pxdvs/GSAPI/GSshape/GSshape.hpp>
u32 g_instancedMemorySizeAll;

void GsShapeRender::SwapBuffers() {
    currentBuffer=!currentBuffer;
    ExecuteFreeInstance();
}
GSgfxLayerID GsShapeRender::GetLayerId() const { return layer; }
u32 GsShapeRender::GetInstancedMemorySizeAll() { return instancedMemory; }
u32 GsShapeRender::GetUsedMemorySizeAll() { return usedMemory; }

void GsShapeRender::InitShapeRender() {
    active=0; frame=0; instance=-1; animation=0;
    keyCount=0; keys=0; objectCount=0; objects=0; textureCount=0; textures=0;
    deformCountU=0; deformU=0; deformCountV=0; deformV=0;
    twistCount=0; twist=0; gradationCount=0; gradation=0;
    refractTexture=0; flags=0; instanceCount=0; nextInstance=0;
    memset(instances,0,256);
    lastBuffer=255; currentBuffer=0;
    for(int buffer=0;buffer<2;buffer++)
        for(int i=0;i<256;i++) tokens[buffer][i]=0;
    polygonCount=0; usedMemory=0; instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
}
void GsShapeRender::FreeShapeRender() {
    int i,j;
    active=0; frame=0; instance=-1; animation=0;
    for(j=0;j<2;j++) {
        for(i=0;i<256;i++) {
            if(tokens[j][i]) { GSgfxTokenWaitForClear(tokens[j][i]); tokens[j][i]=0; }
        }
    }
    for(i=0;i<objectCount;i++) {
        GsShapeObject* object=&objects[i];
        GSgfxVFFree(object->vertexFormat);
        object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
        object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        object->FreeDisplayListShape();
    }
    for(j=0;j<256;j++) {
        if(instances[j]==1) {
            for(i=0;i<objectCount;i++) {
                if(objects[i].FreeShapeDrawBuffer(j)==1) {
                    u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
                    instancedMemory-=size; g_instancedMemorySizeAll-=size;
                }
                instances[j]=0;
            }
        }
        instanceCount=0;
    }
    if(keys) { GSmemFree(keys); keyCount=0; keys=0; }
    if(objects) { GSmemFree(objects); objectCount=0; objects=0; }
    if(textures) { GSmemFree(textures); textureCount=0; textures=0; }
    if(deformU) { GSmemFree(deformU); deformCountU=0; deformU=0; }
    if(deformV) { GSmemFree(deformV); deformCountV=0; deformV=0; }
    if(twist) { GSmemFree(twist); twistCount=0; twist=0; }
    if(gradation) { GSmemFree(gradation); gradationCount=0; gradation=0; }
    if(refractTexture) { GStextureFree(refractTexture); refractTexture=0; }
    polygonCount=0; usedMemory=0; instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
}

static inline void shapeFreeQueuedInstances(GsShapeRender* render) {
    for(s16 i=0;i<render->freeCount[render->currentBuffer];i++) {
        s16 id=render->freeInstances[render->currentBuffer][i];
        if(render->tokens[!render->currentBuffer][id]) GSgfxTokenWaitForClear(render->tokens[!render->currentBuffer][id]);
        if(render->tokens[render->currentBuffer][id]) GSgfxTokenWaitForClear(render->tokens[render->currentBuffer][id]);
        render->tokens[0][id]=0; render->tokens[1][id]=0;
        for(u16 j=0;j<render->objectCount;j++) {
            if(render->objects[j].FreeShapeDrawBuffer(id)==1) {
                u32 size=render->objects[0].entry->vertexCount*(render->objects[0].entry->textureCount*8+16)*2;
                render->instancedMemory-=size; g_instancedMemorySizeAll-=size;
            }
        }
        render->instanceCount--; render->instances[id]=0;
    }
    render->freeCount[render->currentBuffer]=0;
}
void GsShapeRender::ExecuteFreeInstance() {
    if(lastBuffer==currentBuffer) {
        currentBuffer=!currentBuffer;
        shapeFreeQueuedInstances(this);
        currentBuffer=!currentBuffer;
    }
    shapeFreeQueuedInstances(this);
    lastBuffer=currentBuffer;
}
void GsShapeRender::FreeShapeRenderDrawBuffer(s16 id) {
    if(id<0 || id>=256) return;
    u8 next=!currentBuffer;
    if(freeCount[next]>=256) {
        currentBuffer=next;
        shapeFreeQueuedInstances(this);
        currentBuffer=!currentBuffer;
    }
    freeInstances[next][freeCount[next]]=id;
    freeCount[next]++;
}
s16 GsShapeRender::CreateShapeRenderDrawBuffer() {
    shapeFreeQueuedInstances(this);
    u16 tries=0;
    for(;tries<256;tries++) {
        if(instances[nextInstance]==0) { instances[nextInstance]=1; break; }
        nextInstance++;
        if(nextInstance>=256) nextInstance=0;
    }
    if(tries==256) return -1;
    if(instanceCount>=256) return -1;
    instanceCount++;
    for(u16 i=0;i<objectCount;i++) {
        if(objects[i].CreateShapeDrawBuffer(nextInstance)==0) {
            for(int j=0;j<i;j++) {
                if(objects[j].FreeShapeDrawBuffer(nextInstance)==1) {
                    u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
                    instancedMemory-=size; g_instancedMemorySizeAll-=size;
                }
            }
            return -1;
        }
        u32 size=objects[0].entry->vertexCount*(objects[0].entry->textureCount*8+16)*2;
        instancedMemory+=size; g_instancedMemorySizeAll+=size;
    }
    return nextInstance;
}

struct GsShapeFileHeader {
    u8 reserved00[10], layer, reserved0B;
    u32 animationOffset, objectsOffset, texturesOffset;
};
struct GsShapeFileTable { u32 reserved; u16 count, reserved06; u32 entriesOffset; };
struct GsShapeFileTexture { u32 reserved00[3]; u8 reserved0C[2], usesExtraStage, reserved0F[5]; u32 imageOffset; };
struct GsShapeTextureLink { GsShapeFileTexture* entry; GStexture* texture; };
struct GSgfxVF;
extern "C" {
void GSgfxVFInit(GSgfxVF*);
void GSgfxVFCreate(GSgfxVF*);
void GSgfxVFSetElement(GSgfxVF*,s32,s32,s32,u8);
GStexture* GStextureLoad(void*);
void GStextureSetWrap(GStexture*,s32,s32);
GStexture* GStextureCreate(u16,u16,s32,s32,u8);
}
static inline void* shapeFilePointer(u8* base,u32 offset) { return base+offset; }
static inline void shapeRelocateCurve(u8* base,GsShapeCurvePoint*& curve) { curve=(GsShapeCurvePoint*)shapeFilePointer(base,(u32)curve); }
bool GsShapeRender::LoadShapeRender(void* file) {
    u8* base=(u8*)file;
    GsShapeFileHeader* header=(GsShapeFileHeader*)file;
    active=0; FreeShapeRender();
    switch(header->layer) {
    case 0: layer=GS_SHAPE_LAYER_DEFAULT; break;
    case 1: layer=GS_SHAPE_LAYER_ALTERNATE; break;
    default: layer=GS_SHAPE_LAYER_DEFAULT; break;
    }
    animation=(GsShapeFileAnimation*)shapeFilePointer(base,header->animationOffset);
    u32* keyOffsets=(u32*)shapeFilePointer(base,animation->keysOffset);
    keyCount=animation->keyCount;
    keys=(GsKeyObject*)GSmemAlloc(keyCount*sizeof(GsKeyObject));
    u16 maxU=0,maxV=0,maxTwist=0,maxGradation=0;
    for(int i=0;i<keyCount;i++) {
        GsKeyObject* key=&keys[i];
        key->entry=(GsShapeKeyEntry*)shapeFilePointer(base,keyOffsets[i]);
        key->frames=(tagGsFilePrimKeyFrame**)shapeFilePointer(base,(u32)key->entry->frames);
        GsShapeKeyEntry* entry=key->entry;
        for(int j=0;j<key->entry->frameCount;j++) {
            tagGsFilePrimKeyFrame* frame=(tagGsFilePrimKeyFrame*)shapeFilePointer(base,(u32)key->frames[j]);
            key->frames[j]=frame;
            shapeRelocateCurve(base,frame->transformCurves[0]); shapeRelocateCurve(base,frame->transformCurves[1]);
            shapeRelocateCurve(base,frame->transformCurves[2]); shapeRelocateCurve(base,frame->transformCurves[3]);
            shapeRelocateCurve(base,frame->transformCurves[4]); shapeRelocateCurve(base,frame->transformCurves[5]);
            shapeRelocateCurve(base,frame->transformCurves[6]); shapeRelocateCurve(base,frame->transformCurves[7]);
            shapeRelocateCurve(base,frame->transformCurves[8]); shapeRelocateCurve(base,frame->transformCurves[9]);
            shapeRelocateCurve(base,frame->transformCurves[10]); shapeRelocateCurve(base,frame->transformCurves[11]);
            shapeRelocateCurve(base,frame->colorCurves[0]); shapeRelocateCurve(base,frame->colorCurves[1]);
            shapeRelocateCurve(base,frame->colorCurves[2]); shapeRelocateCurve(base,frame->colorCurves[3]);
            shapeRelocateCurve(base,frame->radiusCurves[0]); shapeRelocateCurve(base,frame->radiusCurves[1]);
            shapeRelocateCurve(base,frame->radiusCurves[2]); shapeRelocateCurve(base,frame->radiusCurves[3]);
            shapeRelocateCurve(base,frame->showAngleCurves[0]); shapeRelocateCurve(base,frame->showAngleCurves[1]);
            for(int texture=0;texture<4;texture++) {
                shapeRelocateCurve(base,frame->textureScaleCurves[texture*2]); shapeRelocateCurve(base,frame->textureScaleCurves[texture*2+1]);
                shapeRelocateCurve(base,frame->textureOffsetCurves[texture*2]); shapeRelocateCurve(base,frame->textureOffsetCurves[texture*2+1]);
                shapeRelocateCurve(base,frame->textureColorCurves[texture*4]); shapeRelocateCurve(base,frame->textureColorCurves[texture*4+1]);
                shapeRelocateCurve(base,frame->textureColorCurves[texture*4+2]); shapeRelocateCurve(base,frame->textureColorCurves[texture*4+3]);
                shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4]); shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+1]);
                shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+2]); shapeRelocateCurve(base,frame->textureColorLowCurves[texture*4+3]);
            }
            frame->deformU=(f32*)shapeFilePointer(base,(u32)frame->deformU);
            frame->deformV=(f32*)shapeFilePointer(base,(u32)frame->deformV);
            frame->twist=(f32*)shapeFilePointer(base,(u32)frame->twist);
            frame->gradationU=(tagGScol4ub*)shapeFilePointer(base,(u32)frame->gradationU);
            frame->gradationV=(tagGScol4ub*)shapeFilePointer(base,(u32)frame->gradationV);
            if(entry->channelFlags[9]==1 || entry->channelFlags[5]==1 || entry->channelFlags[2]==1 || entry->channelFlags[4]==1) {
                if(maxU<frame->deformCountU) maxU=frame->deformCountU;
                if(maxV<frame->deformCountV) maxV=frame->deformCountV;
            }
            if(entry->channelFlags[5] && maxTwist<frame->twistCount) maxTwist=frame->twistCount;
            if(entry->channelFlags[7] && entry->channelFlags[8]==1) {
                if(frame->gradationType==0) { if(maxGradation<frame->gradationCountU) maxGradation=frame->gradationCountU; }
                else if(maxGradation<frame->gradationCountV) maxGradation=frame->gradationCountV;
            }
        }
    }
    GsShapeFileTable* objectTable=(GsShapeFileTable*)shapeFilePointer(base,header->objectsOffset);
    u32* objectOffsets=(u32*)shapeFilePointer(base,objectTable->entriesOffset);
    objectCount=objectTable->count;
    objects=(GsShapeObject*)GSmemAlloc(objectCount*sizeof(GsShapeObject));
    u8 needsRefraction=0;
    for(int i=0;i<objectCount;i++) {
        tagGsFilePrimObjectEntry* entry=(tagGsFilePrimObjectEntry*)shapeFilePointer(base,objectOffsets[i]);
        objects[i].entry=entry;
        entry->vertices=(Vec*)shapeFilePointer(base,(u32)entry->vertices);
        entry->colors=(tagGScol4ub*)shapeFilePointer(base,(u32)entry->colors);
        entry->textureCoords=(GsShapePair*)shapeFilePointer(base,(u32)entry->textureCoords);
        if(entry->reserved1C) entry->reserved1C=shapeFilePointer(base,(u32)entry->reserved1C);
        for(int j=0;j<entry->textureCount;j++) if(entry->textures[j]) entry->textures[j]=shapeFilePointer(base,(u32)entry->textures[j]);
        if(entry->dynamic==1 && entry->shapeType==8) needsRefraction=1;
        memset(objects[i].drawBuffers,0,sizeof(objects[i].drawBuffers));
    }
    GsShapeFileTable* textureTable=(GsShapeFileTable*)shapeFilePointer(base,header->texturesOffset);
    u32* textureOffsets=(u32*)shapeFilePointer(base,textureTable->entriesOffset);
    textureCount=textureTable->count;
    if(textureCount) textures=GSmemAlloc(textureCount*sizeof(GsShapeTextureLink));
    else textures=0;
    GsShapeTextureLink* textureLinks=(GsShapeTextureLink*)textures;
    for(int i=0;i<textureCount;i++) {
        GsShapeFileTexture* entry=(GsShapeFileTexture*)shapeFilePointer(base,textureOffsets[i]);
        textureLinks[i].entry=entry;
        textureLinks[i].texture=GStextureLoad(shapeFilePointer(base,entry->imageOffset));
        GStextureSetWrap(textureLinks[i].texture,1,1);
    }
    for(int i=0;i<objectCount;i++) {
        u8 stages=0;
        for(int j=0;j<objects[i].entry->textureCount;j++) {
            stages++;
            if(j<2) {
                u32 texture=*(u32*)((u8*)objects[i].entry->textures[j]+4);
                if(textureLinks[texture].entry->usesExtraStage) stages+=2;
                else stages++;
            }
        }
        if(stages) stages++;
        objects[i].reserved45C[0]=stages;
    }
    for(int i=0;i<objectCount;i++) {
        GsShapeObject* object=&objects[i]; tagGsFilePrimObjectEntry* entry=object->entry;
        int attributes[4]={13,14,15,16};
        object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
        object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        GSgfxVF* vf=(GSgfxVF*)object->vertexFormat;
        GSgfxVFInit(vf); GSgfxVFCreate(vf);
        GSgfxVFSetElement(vf,9,1,4,0); GSgfxVFSetElement(vf,11,1,5,0);
        for(int j=0;j<entry->textureCount;j++) GSgfxVFSetElement(vf,attributes[j],1,4,0);
        object->displayList=0; object->MakeDisplayListShape();
    }
    if(maxU) { deformCountU=maxU; deformU=(f32*)GSmemAlloc(deformCountU*4); }
    if(maxV) { deformCountV=maxV; deformV=(f32*)GSmemAlloc(deformCountV*4); }
    if(maxTwist) { twistCount=maxTwist; twist=(f32*)GSmemAlloc(twistCount*4); }
    if(maxGradation) { gradationCount=maxGradation; gradation=(tagGScol4ub*)GSmemAlloc(gradationCount*4); }
    if(needsRefraction==1) refractTexture=GStextureCreate(0,0,0x45,0,0);
    polygonCount=0;
    for(int i=0;i<objectCount;i++) polygonCount+=objects[i].GetPolygonCount();
    active=1;
    usedMemory=0; usedMemory+=sizeof(GsShapeRender); usedMemory+=keyCount*sizeof(GsKeyObject);
    usedMemory+=objectCount*sizeof(GsShapeObject); usedMemory+=textureCount*sizeof(GsShapeTextureLink);
    if(refractTexture) usedMemory+=0x12C080;
    instancedMemory=0; freeCount[0]=0; freeCount[1]=0;
    return true;
}

// Per-object texture mapping data stored in the primitive file.
struct GsShapeTextureMapping {
    u8 reserved00[0xB], scaleBeforeOffset;
    f32 minU,maxU,minV,maxV;
};
extern "C" GSmtx mtxIdent;
void GsShapeRender::Update(f32 time,s16 id) {
    if(!active) return;
    GsShapeFileAnimation* sequence=animation;
    if(!sequence) return;
    u32 nextFrame;
    if(!sequence) nextFrame=0;
    else {
        nextFrame=(u32)(time*(f32)sequence->frameRate);
        if(sequence->loop==1) nextFrame%=sequence->frameCount-1;
        else if(sequence->loop==2 && nextFrame>sequence->frameCount-1) nextFrame=sequence->frameCount-1;
    }
    frame=nextFrame;
    if(frame>=animation->frameCount) return;
    if(id>=0 && id<256 && tokens[currentBuffer][id]) {
        GSgfxTokenWaitForClear(tokens[currentBuffer][id]);
        tokens[currentBuffer][id]=0;
    }
    for(int i=0;i<keyCount;i++) {
        GsKeyObject* key=&keys[i];
        GsShapeKeyEntry* channel=key->entry;
        GsShapeObject* object=&objects[channel->objectIndex];
        tagGsFilePrimObjectEntry* primitive=object->entry;
        tagGsFilePrimKeyFrame *first,*second;
        f32 t;
        if(!primitive->dynamic || !key->GetFrameInterval(frame,first,second,t)) continue;
        key->visible=first->visible!=0;
        if(!first->visible) continue;
        if(id>=0 && id<256 && object->drawBuffers[id]) {
            u32 offset=0;
            u16 count=primitive->vertexCount;
            if(currentBuffer) offset=count*(primitive->textureCount*8+16);
            u8* vertices=object->drawBuffers[id]+offset;
            object->vertexArrays[0]=vertices;
            u8* colors=vertices+count*12;
            object->vertexArrays[1]=colors;
            if(0<primitive->textureCount) object->vertexArrays[2]=colors+count*4;
            if(1<primitive->textureCount) object->vertexArrays[3]=colors+count*12;
            if(2<primitive->textureCount) object->vertexArrays[4]=colors+count*20;
            if(3<primitive->textureCount) object->vertexArrays[5]=colors+count*28;
        } else {
            object->vertexArrays[0]=0; object->vertexArrays[1]=0; object->vertexArrays[2]=0;
            object->vertexArrays[3]=0; object->vertexArrays[4]=0; object->vertexArrays[5]=0;
        }
        int vertexDeform=channel->channelFlags[9]==1 && channel->channelFlags[10]==1;
        int vertexTwist=channel->channelFlags[5]==1 && channel->channelFlags[6]==1;
        if(vertexDeform==1 || vertexTwist==1 || channel->channelFlags[2]==1 || channel->channelFlags[4]==1) {
            if(vertexDeform==1) {
                key->GetDeformParameterU(deformU,first,second,t);
                key->GetDeformParameterV(deformV,first,second,t);
            } else {
                key->GetLinearParameterU(deformU,first);
                key->GetLinearParameterV(deformV,second);
            }
            f32 radiusU=0.0f,radiusV=0.0f,angleU=0.0f,angleV=0.0f;
            if(channel->channelFlags[2]==1) key->GetShapeRadius(&radiusU,&radiusV,first,second,t);
            if(channel->channelFlags[4]==1) key->GetShapeShowAngle(&angleU,&angleV,first,second,t);
            if(vertexTwist==1) key->GetTwistParameter(twist,first,second,t);
            object->DeformVertexCoord(vertexDeform!=0,deformU,deformV,channel->channelFlags[2]!=0,radiusU,radiusV,
                channel->channelFlags[4]!=0,angleU,angleV,vertexTwist!=0,twist);
        }
        key->GetShapeMatrix(&key->shapeMatrix,&key->transformMatrix,primitive,animation->transformCount,animation->transformOrder,first,second,t);
        int textureDeform=channel->channelFlags[9]==1 && channel->channelFlags[10]==0;
        int textureTwist=channel->channelFlags[5]==1 && channel->channelFlags[6]==0;
        for(u8 texture=0;texture<primitive->textureCount;texture++) {
            if((textureDeform==1 || textureTwist==1) && (!refractTexture || texture!=0)) {
                if(textureDeform) {
                    key->GetDeformParameterU(deformU,first,second,t);
                    key->GetDeformParameterV(deformV,first,second,t);
                }
                if(textureTwist) key->GetTwistParameter(twist,first,second,t);
                object->DeformTextureCoord(texture,textureDeform!=0,deformU,deformV,textureTwist!=0,twist);
            }
            if(primitive->shapeType==10 && primitive->textureCount) {
                GsShapePair offset=key->GetTextureOffset(first,second,t,0);
                GsShapePair scale=key->GetTextureScale(first,second,t,0);
                offset.u*=scale.u; offset.v*=scale.v;
                object->WaveTextureCoord(texture,offset.u,offset.v,&key->shapeMatrix,false);
            }
            GsShapeTextureMapping* mapping=(GsShapeTextureMapping*)object->entry->textures[texture];
            GSmtx* matrix=&key->textureMatrices[texture];
            if(primitive->shapeType==8 && texture==0) memcpy(matrix,&mtxIdent,sizeof(GSmtx));
            else if(channel->channelFlags[12+texture]==1) {
                GsShapePair offset=key->GetTextureOffset(first,second,t,texture);
                GsShapePair scale=key->GetTextureScale(first,second,t,texture);
                if(first->textureSwapAxes[texture]) {
                    matrix->matrix[0][0]=0.0f; matrix->matrix[0][1]=1.0f; matrix->matrix[0][2]=0.0f; matrix->matrix[0][3]=0.0f;
                    matrix->matrix[1][0]=1.0f; matrix->matrix[1][1]=0.0f; matrix->matrix[1][2]=0.0f; matrix->matrix[1][3]=0.0f;
                    matrix->matrix[2][0]=0.0f; matrix->matrix[2][1]=0.0f; matrix->matrix[2][2]=1.0f; matrix->matrix[2][3]=0.0f;
                    if(!mapping->scaleBeforeOffset) {
                        PSMTXTransApply(matrix->matrix,matrix->matrix,-offset.u,-offset.v,0.0f);
                        PSMTXScaleApply(matrix->matrix,matrix->matrix,scale.u,scale.v,0.0f);
                    } else {
                        PSMTXScaleApply(matrix->matrix,matrix->matrix,scale.u,scale.v,0.0f);
                        PSMTXTransApply(matrix->matrix,matrix->matrix,-offset.u,-offset.v,0.0f);
                    }
                } else if(!mapping->scaleBeforeOffset) {
                    PSMTXTrans(matrix->matrix,-offset.u,-offset.v,0.0f);
                    PSMTXScaleApply(matrix->matrix,matrix->matrix,scale.u,scale.v,0.0f);
                } else {
                    PSMTXScale(matrix->matrix,scale.u,scale.v,0.0f);
                    PSMTXTransApply(matrix->matrix,matrix->matrix,-offset.u,-offset.v,0.0f);
                }
            } else {
                PSMTXScale(matrix->matrix,mapping->maxU-mapping->minU,mapping->maxV-mapping->minV,0.0f);
                PSMTXTransApply(matrix->matrix,matrix->matrix,mapping->minU,mapping->minV,0.0f);
            }
        }
        if(primitive->colorMode==0) {
            if(channel->channelFlags[7]==1) {
                if(channel->channelFlags[8]==0) {
                    tagGScol4ub color=key->GetShapeColor(first,second,t);
                    object->SetVertexColorSpecify(color,true);
                } else {
                    f32 alpha=key->GetShapeColorAlpha(first,second,t);
                    u8 axis;
                    key->GetGradationParameter(&axis,gradation,first,second,t);
                    object->SetVertexColorGradation(axis,gradation,primitive->shapeType,alpha,true);
                }
            } else {
                f32 alpha=key->GetShapeColorAlpha(first,second,t);
                object->SetVertexColorAlpha(channel->channelFlags[8],primitive->shapeType,alpha,true);
            }
        }
        tagGScol4ub color=key->GetTextureColor(first,second,t,0);
        object->reserved45C[1]=color.r; object->reserved45C[2]=color.g; object->reserved45C[3]=color.b; object->reserved45C[4]=color.a;
        color=key->GetTextureColorLow(first,second,t,0);
        object->reserved45C[5]=color.r; object->reserved45C[6]=color.g; object->reserved45C[7]=color.b; object->reserved45C[8]=color.a;
        object->reserved45C[8]=255;
        if(primitive->textureCount>1) {
            color=key->GetTextureColor(first,second,t,1);
            object->reserved45C[9]=color.r; object->reserved45C[10]=color.g; object->reserved45C[11]=color.b; object->reserved45C[12]=color.a;
            color=key->GetTextureColorLow(first,second,t,1);
            object->reserved45C[13]=color.r; object->reserved45C[14]=color.g; object->reserved45C[15]=color.b; object->reserved45C[16]=color.a;
        }
    }
}
