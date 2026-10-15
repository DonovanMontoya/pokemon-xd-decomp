#include <game/pxdvs/GSAPI/GScolsys/GScolsys2ThruPrivate.hpp>
static inline void copyEvent(ThruEvent *out,Vec *vertices,Vec *normal,u16 id) {
    for(s32 i=0;i<3;i++) *(Vec *)&out->vertices[i]=vertices[i];
    out->normal=*normal;
    out->eventID=id;
}
static inline void copyEvent(ThruEvent *out,ThruEvent *in) {
    for(s32 i=0;i<3;i++) *(Vec *)&out->vertices[i]=*(Vec *)&in->vertices[i];
    out->normal=in->normal;
    out->eventID=in->eventID;
}
static inline u8 segmentContact(Vec *crossing,f32 *rate,Vec *normal,Vec *vertices,GSvec *start,GSvec *end) {
    if(!GScolsys2UtilGetCpPlaneLine(crossing,rate,normal,vertices,(Vec *)start,(Vec *)end)) return 0;
    if(*rate<0.0f || *rate>1.0f) return 0;
    if(!GScolsy2UtilChkInTri(crossing,vertices,normal)) return 0;
    return 1;
}
static s32 getMdlEventListPass(GSvec *start,GSvec *end,CCD_THRUMDL_HEAD *model,GSmtx *matrix,GSmtx *rotation,ThruEvent *events) {
    Vec triangle[3],normal,direction,crossing;
    f32 rate;
    ThruEvent *output;
    ThruPolygon *polygon;
    u32 i;
    s32 count=0;
    PSVECSubtract((Vec *)end,(Vec *)start,&direction);
    polygon=model->polygons;
    output=events;
    for(i=0;i<model->count && count<4;i++,polygon++) {
        ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
        PSMTXMultVec(rotation->m,&polygon->normal,&normal);
        if(PSVECDotProduct(&normal,&direction)>=0.0f) continue;
        Vec *src;
        Vec *dst;
        dst=triangle;src=(Vec *)polygon;
        s32 j=0;
        do { PSMTXMultVec(matrix->m,src,dst);j++;dst++;src++; } while(j<3);
        if(segmentContact(&crossing,&rate,&normal,triangle,start,end)) {
            count++;
            copyEvent(output,triangle,&normal,polygon->eventID);
            output++;
        }
    }
    return count;
}
extern "C" s32 GScolsys2ThruPassEventID(GSvec *start,GSvec *end,ThruEvent *events) {
    s32 count=0;
    ThruEvent temporary[4];
    GSmtx matrix,rotation;
    Vec direction,crossing;
    f32 rate;
    u8 enabled;
    ThruFile *head=GScolsys2GetCCDFileHead();
    if(!head) return 0;
    ThruObject *object=head->objects;
    for(u32 i=0;i<head->count && count<4;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if(enabled && object->model) {
            CCD_THRUMDL_HEAD *model=object->model;
            s32 found;
            if(object->flags&1) {
                GScolsys2GetObjMatrix(matrix.m,i);
                GScolsys2GetObjRotMatrix(rotation.m,i);
                found=getMdlEventListPass(start,end,model,&matrix,&rotation,temporary);
            } else {
                s32 used=0;
                PSVECSubtract((Vec *)end,(Vec *)start,&direction);
                ThruPolygon *polygon=model->polygons;
                ThruEvent *output=temporary;
                for(u32 j=0;j<model->count && used<4;j++,polygon++) {
                    ThruEvent *existing=temporary;
        s32 duplicate;
        for(duplicate=0;duplicate<used;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<used) continue;
                    if(PSVECDotProduct(&polygon->normal,&direction)>=0.0f) continue;
                    if(segmentContact(&crossing,&rate,&polygon->normal,polygon->vertices,start,end)) {
                        used++;
                        copyEvent(output,polygon->vertices,&polygon->normal,polygon->eventID);
                        output++;
                    }
                }
                found=used;
            }
            ThruEvent *entry=temporary;
            for(s32 j=0;j<found && count<4;j++,entry++) {
                ThruEvent *existing=events;
                s32 duplicate;
                for(duplicate=0;duplicate<count;existing++,duplicate++) if(existing->eventID==entry->eventID) break;
                if(duplicate>=count) {
                    copyEvent(&events[count],entry);
                    count++;
                }
            }
        }
    }
    return count;
}
static inline u8 faceContact(Vec *point,Vec *vertices,Vec *normal,f32 radiusSquared) {
    Vec crossing;
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    GScolsy2UtilGetCpPlanePoint(&crossing,normal,vertices,point);
    if(PSVECSquareDistance(&crossing,point)>=radiusSquared) return 0;
    if(!GScolsy2UtilChkInTri(&crossing,vertices,normal)) return 0;
    return 1;
}
static inline u8 edgeContact(Vec *point,Vec *vertices,Vec *normal,u16 flags,f32 radiusSquared) {
    const u16 masks[3]={1,2,4};
    Vec crossing;
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    Vec *vertex=vertices;
    for(s32 i=0;i<3;i++,vertex++) {
        if(flags&masks[i]) {
            s32 next=i+1;
            if(next>=3) next=0;
            f32 rate=GScolsys2UtilGetCpLinePoint(&crossing,vertex,&vertices[next],point);
            if(!(rate<0.0f) && !(rate>1.0f) && PSVECSquareDistance(&crossing,point)<radiusSquared) return 1;
        }
    }
    return 0;
}
static inline u8 vertexContact(Vec *point,Vec *vertices,Vec *normal,u16 flags,f32 radiusSquared) {
    const u16 masks[3]={1,2,4};
    if(GScolsy2UtilGetSidePlanePoint(normal,vertices,point)<0.0f) return 0;
    Vec *vertex=vertices;
    for(s32 i=0;i<3;i++,vertex++) {
        s32 previous=i+2;
        if(previous>=3) previous-=3;
        if((flags&masks[i]) && (flags&masks[previous]) && PSVECSquareDistance(vertex,point)<radiusSquared) return 1;
    }
    return 0;
}
static s32 getFixedMdlEventList(GSvec *point,GSvec *direction,f32 radius,CCD_THRUMDL_HEAD *model,ThruEvent *events) {
    s32 count=0;
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
        ThruEvent *output=events+count;
        for(s32 z=minZ;z<=maxZ && count<4;z++) {
            ThruCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && count<4;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && count<4;i++,index++) {
                    ThruPolygon *polygon=&model->polygons[*index];
                    ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
                    if(PSVECDotProduct(&polygon->normal,(Vec *)direction)>=0.0f) continue;
                    if(faceContact((Vec *)point,polygon->vertices,&polygon->normal,radiusSquared)) {
                        copyEvent(output,polygon->vertices,&polygon->normal,polygon->eventID);
                        output++;count++;
                    }
                }
            }
        }
    }
    {
        ThruEvent *output=events+count;
        for(s32 z=minZ;z<=maxZ && count<4;z++) {
            ThruCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && count<4;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && count<4;i++,index++) {
                    ThruPolygon *polygon=&model->polygons[*index];
                    if(!(polygon->edgeFlags&7)) continue;
                    ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
                    if(PSVECDotProduct(&polygon->normal,(Vec *)direction)>=0.0f) continue;
                    if(edgeContact((Vec *)point,polygon->vertices,&polygon->normal,polygon->edgeFlags,radiusSquared)) {
                        copyEvent(output,polygon->vertices,&polygon->normal,polygon->eventID);
                        output++;count++;
                    }
                }
            }
        }
    }
    {
        ThruEvent *output=events+count;
        for(s32 z=minZ;z<=maxZ && count<4;z++) {
            ThruCell *cell=&model->cells[minX+z*model->width];
            for(s32 x=minX;x<=maxX && count<4;x++,cell++) {
                u32 *index=&model->indices[cell->first];
                for(u32 i=0;i<cell->count && count<4;i++,index++) {
                    ThruPolygon *polygon=&model->polygons[*index];
                    if(!(polygon->edgeFlags&7)) continue;
                    ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
                    if(PSVECDotProduct(&polygon->normal,(Vec *)direction)>=0.0f) continue;
                    if(vertexContact((Vec *)point,polygon->vertices,&polygon->normal,polygon->edgeFlags,radiusSquared)) {
                        copyEvent(output,polygon->vertices,&polygon->normal,polygon->eventID);
                        output++;count++;
                    }
                }
            }
        }
    }
    return count;
}
static s32 getMdlEventList(GSvec *point,GSvec *direction,f32 radius,CCD_THRUMDL_HEAD *model,GSmtx *matrix,GSmtx *rotation,ThruEvent *events) {
    Vec triangle[3],normal;
    f32 radiusSquared=radius*radius;
    s32 count=0;
    {
        ThruPolygon *polygon=model->polygons;
        ThruEvent *output=events+count;
        for(u32 i=0;i<model->count && count<4;i++,polygon++) {
            ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            if(PSVECDotProduct(&normal,(Vec *)direction)>=0.0f) continue;
            Vec *dst=triangle,*src=polygon->vertices;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            if(faceContact((Vec *)point,triangle,&normal,radiusSquared)) {
                copyEvent(output,triangle,&normal,polygon->eventID);
                output++;count++;
            }
        }
    }
    {
        ThruPolygon *polygon=model->polygons;
        ThruEvent *output=events+count;
        for(u32 i=0;i<model->count && count<4;i++,polygon++) {
            if(!(polygon->edgeFlags&7)) continue;
            ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            if(PSVECDotProduct(&normal,(Vec *)direction)>=0.0f) continue;
            Vec *dst=triangle,*src=polygon->vertices;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            if(edgeContact((Vec *)point,triangle,&normal,polygon->edgeFlags,radiusSquared)) {
                copyEvent(output,triangle,&normal,polygon->eventID);
                output++;count++;
            }
        }
    }
    {
        ThruPolygon *polygon=model->polygons;
        ThruEvent *output=events+count;
        for(u32 i=0;i<model->count && count<4;i++,polygon++) {
            if(!(polygon->edgeFlags&7)) continue;
            ThruEvent *existing=events;
        s32 duplicate;
        for(duplicate=0;duplicate<count;existing++,duplicate++) if(polygon->eventID==existing->eventID) break;
        if(duplicate<count) continue;
            PSMTXMultVec(rotation->m,&polygon->normal,&normal);
            if(PSVECDotProduct(&normal,(Vec *)direction)>=0.0f) continue;
            Vec *dst=triangle,*src=polygon->vertices;
            s32 j=0;
            do {PSMTXMultVec(matrix->m,src,dst);j++;src++;dst++;} while(j<3);
            if(vertexContact((Vec *)point,triangle,&normal,polygon->edgeFlags,radiusSquared)) {
                copyEvent(output,triangle,&normal,polygon->eventID);
                output++;count++;
            }
        }
    }
    return count;
}
static s32 getEventList(GSvec *point,GSvec *direction,f32 radius,ThruEvent *events) {
    s32 count=0;
    ThruEvent temporary[4];
    GSmtx matrix,rotation;
    u8 enabled;
    ThruFile *head=GScolsys2GetCCDFileHead();
    u32 i=0;
    ThruObject *object=head->objects;
    for(;i<head->count && count<4;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if(enabled) {
            CCD_THRUMDL_HEAD *model=object->model;
            if(model) {
                s32 found;
                if(object->flags&1) {
                    GScolsys2GetObjMatrix(matrix.m,i);
                    GScolsys2GetObjRotMatrix(rotation.m,i);
                    found=getMdlEventList(point,direction,radius,model,&matrix,&rotation,temporary);
                } else found=getFixedMdlEventList(point,direction,radius,model,temporary);
                ThruEvent *entry=temporary;
                for(s32 j=0;j<found && count<4;j++,entry++) {
                    ThruEvent *existing=events;
                s32 duplicate;
                for(duplicate=0;duplicate<count;existing++,duplicate++) if(existing->eventID==entry->eventID) break;
                if(duplicate>=count) {
                        copyEvent(&events[count],entry);
                        count++;
                    }
                }
            }
        }
    }
    return count;
}
extern "C" s32 GScolsys2ThruGetEventID(GSvec *start,GSvec *end,ThruEvent *events,f32 radius) {
    ThruEvent temporary[4];
    Vec direction,point;
    s32 count=0;
    if(!GScolsys2GetCCDFileHead()) return 0;
    PSVECSubtract((Vec *)end,(Vec *)start,&direction);
    f32 length=PSVECMag(&direction);
    if(length<=0.0f) return 0;
    f32 step=radius/length;
    if(step>1.0f) step=1.0f;
    f32 progress=0.0f;
    for(;progress<1.0f && count<4;) {
        f32 t=progress+step;
        if(t>1.0f) t=1.0f;
        PSVECScale(&direction,&point,t);
        PSVECAdd(&point,(Vec *)start,&point);
        s32 found=getEventList((GSvec *)&point,(GSvec *)&direction,radius,temporary);
        ThruEvent *entry=temporary;
        for(s32 j=0;j<found && count<4;j++,entry++) {
            ThruEvent *existing=events;
                s32 duplicate;
                for(duplicate=0;duplicate<count;existing++,duplicate++) if(existing->eventID==entry->eventID) break;
                if(duplicate>=count) {
                copyEvent(&events[count],entry);
                count++;
            }
        }
        if(step<=0.0f) break;
        progress+=step;
    }
    return count;
}
