#include <game/pxdvs/GSAPI/GScolsys/GScolsys2SunPrivate.hpp>

#pragma dont_inline on
static s32 getCpSegPolyArray(bool *blocked, GSvec *start, GSvec *ends, unsigned long count, GSvec *triangle, GSvec *normal) {
    Vec crossing;
    f32 rate;
    u32 i;
    u8 any;
    u8 all;
    GSvec *end;
    end = ends;
    any = 0;
    all = 1;
    for (i=0; i<count; i++,end++,blocked++) {
        if (!*blocked) {
            if (PSVECSquareDistance((Vec *)start,(Vec *)end) < 0.00001f) all=0;
            else if (!GScolsys2UtilGetCpPlaneLine(&crossing,&rate,(Vec *)normal,(Vec *)triangle,(Vec *)start,(Vec *)end)) all=0;
            else if (rate<0.0f || rate>1.0f) all=0;
            else if (!GScolsy2UtilChkInTri(&crossing,(Vec *)triangle,(Vec *)normal)) all=0;
            else { *blocked=true; any=1; }
        }
    }
    if(all) return -1;
    return any!=0;
}

#pragma dont_inline reset
extern "C" s32 GScolsys2SunArray(bool *blocked, GSvec *start, GSvec *ends, u32 count) {
    Mtx rotation, matrix;
    GSvec triangle[3],normal;
    u8 enabled;
    if(!GScolsys2GetCCDFileHead()) return 0;
    memset(blocked,0,count);
    s32 result=0;
    SunFile *head=GScolsys2GetCCDFileHead();
    u32 i=0;
    SunModel *model;
    SunObject *object=head->objects;
    for(;i<head->count;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if(enabled) {
            model=object->model;
            if(model) {
                GScolsys2GetObjMatrix(matrix,i);
                GScolsys2GetObjRotMatrix(rotation,i);
                s32 status;
                s32 k;
                u32 j;
                SunPolygon *polygon;
                j=0;
                polygon=model->polygons;
                status=j;
                for(;j<model->count;j++,polygon++) {
                    PSMTXMultVec(rotation,(Vec *)&polygon->normal,(Vec *)&normal);
                    GSvec *dst;
                    GSvec *src;
                    src=polygon->vertices;dst=triangle;
                    k=0;
                    do { PSMTXMultVec(matrix,(Vec *)src,(Vec *)dst); k++;dst++;src++; } while(k<3);
                    s32 hit=getCpSegPolyArray(blocked,start,ends,count,triangle,&normal);
                    if(hit<0) { status=-1;break; }
                    if(hit>0) status=1;
                }
                if(status<0) { result=1;break; }
                if(status>0) result=1;
            }
        }
    }
    return result;
}
extern "C" s32 GScolsys2Sun(GSvec *start,GSvec *end) {
    Mtx rotation,matrix;
    GSvec triangle[3],direction,normal,crossing;
    f32 rate;
    u8 enabled;
    if(!GScolsys2GetCCDFileHead()) return 0;
    if(PSVECDistance((Vec *)end,(Vec *)start)<=0.0f) return 0;
    SunFile *head=GScolsys2GetCCDFileHead();
    PSVECSubtract((Vec *)end,(Vec *)start,(Vec *)&direction);
    u32 i;
    SunModel *model;
    SunObject *object=head->objects;
    for(i=0;i<head->count;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if(enabled) {
            model=object->model;
            if(model) {
                GScolsys2GetObjMatrix(matrix,i);
                GScolsys2GetObjRotMatrix(rotation,i);
                s32 k;
                u32 j;
                SunPolygon *polygon=model->polygons;
                u8 found;
                j=0;
                for(;j<model->count;j++,polygon++) {
                    PSMTXMultVec(rotation,(Vec *)&polygon->normal,(Vec *)&normal);
                    GSvec *dst;
                    GSvec *src;
                    src=polygon->vertices;dst=triangle;
                    k=0;
                    do { PSMTXMultVec(matrix,(Vec *)src,(Vec *)dst);k++;dst++;src++; } while(k<3);
                    u8 hit;
                    if(!GScolsys2UtilGetCpPlaneLine((Vec *)&crossing,&rate,(Vec *)&normal,(Vec *)triangle,(Vec *)start,(Vec *)end)) hit=0;
                    else if(rate<0.0f || rate>1.0f) hit=0;
                    else if(!GScolsy2UtilChkInTri((Vec *)&crossing,(Vec *)triangle,(Vec *)&normal)) hit=0;
                    else hit=1;
                    if(hit) {found=1;goto modelDone;}
                }
                found=0;
modelDone:
                if(found) return 1;
            }
        }
    }
    return 0;
}
