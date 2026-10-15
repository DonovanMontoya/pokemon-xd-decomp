#include <game/pxdvs/GSAPI/GScolsys/GScolsys2WalkPrivate.hpp>
extern "C" s32 GScolsys2WalkGetLayer(GSvec *point,u8 *layer,u8 *floor) {
    WalkHeight heights[8];
    s32 count=GScolsys2WalkGetHeight(point,heights);
    if(count<=0) return 0;
    f32 distance=point->y-heights[0].height;
    distance=distance>0.0f ? distance : -distance;
    f32 nearest=distance;
    WalkHeight *entry=&heights[1];
    s32 i;
    s32 chosen=0;
    for(i=1;i<count;entry++,i++) {
        f32 delta=point->y-entry->height;
        delta=delta>0.0f ? delta : -delta;
        if(nearest>delta) {chosen=i;nearest=delta;}
    }
    *layer=heights[chosen].layer;
    *floor=heights[chosen].floor;
    return 1;
}
#pragma dont_inline on
static u8 getCpPolyVec(GSvec *out,GSvec *point,GSvec *triangle,GSvec *normal) {
    GSvec minimum,maximum;
    minimum.x=minimum.z=1000000.0f;
    maximum.x=maximum.z=-1000000.0f;
    for(s32 i=0;i<3;i++) {
        if(minimum.x>triangle[i].x) minimum.x=triangle[i].x;
        if(minimum.z>triangle[i].z) minimum.z=triangle[i].z;
        if(maximum.x<triangle[i].x) maximum.x=triangle[i].x;
        if(maximum.z<triangle[i].z) maximum.z=triangle[i].z;
    }
    if(minimum.x>point->x || minimum.z>point->z || maximum.x<point->x || maximum.z<point->z) return 0;
    for(s32 i=0;i<3;i++) {
        s32 next=i+1;
        if(next>=3) next=0;
        GSvec displacement,edge;
        displacement.x=point->x-triangle[i].x;
        displacement.z=point->z-triangle[i].z;
        edge.z=triangle[next].z-triangle[i].z;
        edge.x=triangle[next].x-triangle[i].x;
        f32 cross=edge.z*displacement.x;
        if(edge.x*displacement.z-cross>0.0f) return 0;
    }
    f32 ny=normal->y;
    if(ny==0.0f) return 0;
    out->x=point->x;
    out->y=point->y + -(normal->z*(point->z-triangle->z)+(normal->x*(point->x-triangle->x)+ny*(point->y-triangle->y)))/ny;
    out->z=point->z;
    return 1;
}
#pragma dont_inline reset
static inline u8 storeHeight(WalkHeight *output,WalkHeight *begin,s32 count,f32 height,WalkPolygon *polygon) {
    WalkHeight *entry=begin;
    s32 i;
    for(i=0;i<count;entry++,i++) if(height==entry->height) break;
    if(i<count) return 0;
    output->height=height;
    u16 upper=(polygon->attributes[0]>>4)&15;
    if(upper==15) output->upper=0xffff;else output->upper=upper;
    u16 lower=polygon->attributes[0]&15;
    if(lower==15) output->lower=0xffff;else output->lower=lower;
    u8 packed=polygon->attributes[1];
    output->layer=(packed>>4)&15;
    output->floor=packed&15;
    return 1;
}
extern "C" s32 GScolsys2WalkGetHeight(GSvec *point,WalkHeight *heights) {
    WalkHeight temporary[8];
    Mtx matrix,rotation;
    GSvec triangle[3],crossing,normal,gridCrossing;
    u8 enabled;
    s32 count=0;
    WalkFile *head=GScolsys2GetCCDFileHead();
    if(!head) return 0;
    WalkObject *object=head->objects;
    WalkHeight *output=heights;
    for(u32 i=0;i<head->count && count<8;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if(enabled) {
            WalkModel *model=object->model;
            if(model) {
                s32 found;
                if(object->flags&1) {
                    GScolsys2GetObjMatrix(matrix,i);
                    GScolsys2GetObjRotMatrix(rotation,i);
                    s32 used=0;
                    WalkPolygon *polygon=model->polygons;
                    WalkHeight *entry=temporary;
                    for(u32 j=0;j<model->count && used<8;j++,polygon++) {
                        GSvec *src=polygon->vertices,*dst=triangle;
                        s32 k=0;
                        do {PSMTXMultVec(matrix,(Vec *)src,(Vec *)dst);k++;src++;dst++;} while(k<3);
                        PSMTXMultVec(rotation,(Vec *)&polygon->normal,(Vec *)&normal);
                        if(getCpPolyVec(&crossing,point,triangle,&normal)) {
                            if(storeHeight(entry,temporary,used,crossing.y,polygon)) {entry++;used++;}
                        }
                    }
                    found=used;
                } else {
                    s32 used=0;
                    s32 x=(s32)((point->x-model->originX)/model->cellWidth);
                    if(x>=0 && x<model->width) {
                        s32 z=(s32)((point->z-model->originZ)/model->cellDepth);
                        if(z>=0 && z<model->depth) {
                            WalkHeight *entry=temporary;
                            WalkCell *cell=&model->cells[x+z*model->width];
                            u32 *index=&model->indices[cell->first];
                            for(u32 j=0;j<cell->count && used<8;j++,index++) {
                                WalkPolygon *polygon=&model->polygons[*index];
                                if(getCpPolyVec(&gridCrossing,point,polygon->vertices,&polygon->normal)) {
                                    if(storeHeight(entry,temporary,used,gridCrossing.y,polygon)) {entry++;used++;}
                                }
                            }
                        }
                    }
                    found=used;
                }
                WalkHeight *entry=temporary;
                for(s32 j=0;j<found && count<8;j++,entry++,output++) {
                    output->height=entry->height;
                    output->upper=entry->upper;
                    output->lower=entry->lower;
                    output->layer=entry->layer;
                    output->floor=entry->floor;
                    count++;
                }
            }
        }
    }
    return count;
}
