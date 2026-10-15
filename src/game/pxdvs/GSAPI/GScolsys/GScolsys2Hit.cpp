#include <game/pxdvs/GSAPI/GScolsys/GScolsys2HitPrivate.hpp>
static inline u8 faceContact(Vec *closest,Vec *point,Vec *vertices,Vec *normal,f32 radiusSquared) {
    Vec crossing;
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    GScolsy2UtilGetCpPlanePoint(&crossing,normal,vertices,point);
    if(PSVECSquareDistance(&crossing,point)>=radiusSquared) return 0;
    if(!GScolsy2UtilChkInTri(&crossing,vertices,normal)) return 0;
    *closest=crossing;
    return 1;
}
static inline u8 edgeContact(Vec *closest,Vec *point,Vec *vertices,Vec *normal,u16 flags,f32 radiusSquared) {
    const u16 masks[3]={1,2,4};
    Vec crossing;
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    Vec *vertex=vertices;
    for(s32 i=0;i<3;i++,vertex++) {
        if(flags&masks[i]) {
            s32 next=i+1;
            if(next>=3) next=0;
            f32 rate=GScolsys2UtilGetCpLinePoint(&crossing,vertex,&vertices[next],point);
            if(!(rate<0.0f) && !(rate>1.0f) && PSVECSquareDistance(&crossing,point)<radiusSquared) {
                *closest=crossing;
                return 1;
            }
        }
    }
    return 0;
}
static inline u8 vertexContact(Vec *closest,Vec *point,Vec *vertices,Vec *normal,u16 flags,f32 radiusSquared) {
    const u16 masks[3]={1,2,4};
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    Vec *vertex=vertices;
    for(s32 i=0;i<3;i++,vertex++) {
        s32 previous=i+2;
        if(previous>=3) previous-=3;
        if((flags&masks[i]) && (flags&masks[previous]) && PSVECSquareDistance(vertex,point)<radiusSquared) {
            *closest=vertices[i];
            return 1;
        }
    }
    return 0;
}
static u8 checkHitFixedMdl(GSvec *point,f32 radius,CCD_HITMDL_HEAD *model,GSvec *out) {
    Vec closest;
    s32 minX=(s32)(((point->x-radius)-model->originX)/model->cellWidth);
    if(minX<0) minX=0;
    s32 minZ=(s32)(((point->z-radius)-model->originZ)/model->cellDepth);
    if(minZ<0) minZ=0;
    s32 maxX=(s32)(((point->x+radius)-model->originX)/model->cellWidth);
    if(maxX>model->width-1) maxX=model->width-1;
    s32 maxZ=(s32)(((point->z+radius)-model->originZ)/model->cellDepth);
    if(maxZ>model->depth-1) maxZ=model->depth-1;
    f32 radiusSquared=radius*radius;
    {
        u8 hit=0;
        for(s32 z=minZ;z<=maxZ && !hit;z++) {
            HitCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && !hit;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && !hit;i++,index++) {
                    HitPolygon *polygon=&model->polygons[*index];
                    hit=faceContact(&closest,(Vec *)point,polygon->vertices,&polygon->normal,radiusSquared);
                }
            }
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    {
        u8 hit=0;
        for(s32 z=minZ;z<=maxZ && !hit;z++) {
            HitCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && !hit;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && !hit;i++,index++) {
                    HitPolygon *polygon=&model->polygons[*index];
                    if(!(polygon->edgeFlags&7)) continue;
                    hit=edgeContact(&closest,(Vec *)point,polygon->vertices,&polygon->normal,polygon->edgeFlags,radiusSquared);
                }
            }
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    {
        u8 hit=0;
        for(s32 z=minZ;z<=maxZ && !hit;z++) {
            HitCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && !hit;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && !hit;i++,index++) {
                    HitPolygon *polygon=&model->polygons[*index];
                    if(!(polygon->edgeFlags&7)) continue;
                    hit=vertexContact(&closest,(Vec *)point,polygon->vertices,&polygon->normal,polygon->edgeFlags,radiusSquared);
                }
            }
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    return 0;
}
static u8 checkHitMdl(GSvec *point,f32 radius,CCD_HITMDL_HEAD *model,GSmtx *matrix,GSmtx *rotation,GSvec *out) {
    Vec triangle[3],normal,closest;
    f32 radiusSquared=radius*radius;
    {
        HitPolygon *polygon=model->polygons;
        u8 hit=0;
        for(u32 i=0;i<model->count && !hit;i++,polygon++) {
            Vec *src=polygon->vertices,*dst=triangle;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            hit=faceContact(&closest,(Vec *)point,triangle,&normal,radiusSquared);
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    {
        HitPolygon *polygon=model->polygons;
        u8 hit=0;
        for(u32 i=0;i<model->count && !hit;i++,polygon++) {
            if(!(polygon->edgeFlags&7)) continue;
            Vec *src=polygon->vertices,*dst=triangle;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            hit=edgeContact(&closest,(Vec *)point,triangle,&normal,polygon->edgeFlags,radiusSquared);
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    {
        HitPolygon *polygon=model->polygons;
        u8 hit=0;
        for(u32 i=0;i<model->count && !hit;i++,polygon++) {
            if(!(polygon->edgeFlags&7)) continue;
            Vec *src=polygon->vertices,*dst=triangle;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            hit=vertexContact(&closest,(Vec *)point,triangle,&normal,polygon->edgeFlags,radiusSquared);
        }
        if(hit) {
            if(!out) return 1;
            GScolsy2UtilGetPointExtentionLine((Vec *)out,&closest,(Vec *)point,0.0001f+radius);
            return 1;
        }
    }
    return 0;
}
static u8 checkHitCollision(GSvec *start,GSvec *end,f32 radius,GSvec *out,bool npc) {
    s32 passes,contacts;
    u32 i;
    GSvec *adjusted;
    HitFile *head;
    HitObject *object;
    CCD_HITMDL_HEAD *model;
    GSmtx matrix,rotation;
    GSvec point,correction;
    point.x=end->x;point.y=end->y;point.z=end->z;
    u8 enabled;
    head=GScolsys2GetCCDFileHead();
    adjusted=&correction;
    if(!out) adjusted=0;
    passes=0;
    for(;;) {
        object=head->objects;
        contacts=0;
        for(i=0;i<head->count;i++,object++) {
            GScolsys2GetObjEnable(i,&enabled);
            if(enabled) {
                if(npc) {model=object->npcModel;if(!model) continue;}
                else {model=object->model;if(!model) continue;}
                u8 hit;
                if(object->flags&1) {
                    GScolsys2GetObjMatrix(matrix.m,i);
                    GScolsys2GetObjRotMatrix(rotation.m,i);
                    hit=checkHitMdl(&point,radius,model,&matrix,&rotation,adjusted);
                } else hit=checkHitFixedMdl(&point,radius,model,adjusted);
                if(hit) {
                    if(!out) return 1;
                    contacts++;
                    if(adjusted) {
                        f32 x=adjusted->x,y=adjusted->y,z=adjusted->z;
                        point.x=x;point.y=y;point.z=z;
                    }
                }
            }
        }
        if(contacts<=0 || ++passes>=10) break;
    }
    if(passes<=0) return 0;
    *out=point;
    return 1;
}
extern "C" s32 GScolsys2HitNpcCollision(GSvec *start,GSvec *end,GSvec *out,f32 radius) {
    Vec last,first,direction;
    if(!GScolsys2GetCCDFileHead()) return 0;
    f32 length=PSVECDistance((Vec *)start,(Vec *)end);
    f32 step=0.0f;
    if(length>0.0f) {
        step=radius/length;
        if(step>1.0f) step=1.0f;
    }
    PSVECSubtract((Vec *)end,(Vec *)start,&direction);
    f32 next;
    f32 progress=0.0f;
    for(;progress<1.0f;) {
        next=progress+step;
        if(next>1.0f) next=1.0f;
        PSVECScale(&direction,&first,progress);
        PSVECAdd(&first,(Vec *)start,&first);
        PSVECScale(&direction,&last,next);
        PSVECAdd(&last,(Vec *)start,&last);
        if(checkHitCollision((GSvec *)&first,(GSvec *)&last,radius,out,true)) return 1;
        if(step<=0.0f) break;
        progress+=step;
    }
    return 0;
}
extern "C" s32 GScolsys2HitCollision(GSvec *start,GSvec *end,GSvec *out,f32 radius) {
    Vec last,first,direction;
    if(!GScolsys2GetCCDFileHead()) return 0;
    f32 length=PSVECDistance((Vec *)start,(Vec *)end);
    f32 step=0.0f;
    if(length>0.0f) {
        step=radius/length;
        if(step>1.0f) step=1.0f;
    }
    PSVECSubtract((Vec *)end,(Vec *)start,&direction);
    f32 next;
    f32 progress=0.0f;
    for(;progress<1.0f;) {
        next=progress+step;
        if(next>1.0f) next=1.0f;
        PSVECScale(&direction,&first,progress);
        PSVECAdd(&first,(Vec *)start,&first);
        PSVECScale(&direction,&last,next);
        PSVECAdd(&last,(Vec *)start,&last);
        if(checkHitCollision((GSvec *)&first,(GSvec *)&last,radius,out,false)) return 1;
        if(step<=0.0f) break;
        progress+=step;
    }
    return 0;
}
