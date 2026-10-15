#include <game/pxdvs/GSAPI/GScolsys/GScolsys2CheckPrivate.hpp>
static u8 getMdlEventList(GSvec *start, GSvec *end, GSvec *direction, CCD_CHECKMDL_HEAD *model, GSmtx *matrix, GSmtx *rotation, CCDCheckEvent *events) {
    Vec triangle[3];
    Vec normal, crossing;
    f32 rate;
    CCDCheckEvent *output = events;
    CCDCheckEvent *entry;
    u32 i;
    s32 count = 0;
    i = 0;
    entry = model->triangles;
    for (; i < model->count && count < 4; i++, entry++) {
        CCDCheckEvent *existing = events;
        s32 j;
        for (j=0; j<count; existing++, j++) if (entry->eventID == existing->eventID) break;
        if (j < count) continue;
        PSMTXMultVec(rotation->m, &entry->normal, &normal);
        if (PSVECDotProduct(&normal, (Vec *)direction) >= 0.0f) continue;
        GSvec *src = entry->vertices;
        Vec *dst = triangle;
        s32 k = 0;
        do { PSMTXMultVec(matrix->m, (Vec *)src, dst); k++; src++; dst++; } while (k<3);
        u8 hit;
        if (!GScolsys2UtilGetCpPlaneLine(&crossing,&rate,&normal,triangle,(Vec *)start,(Vec *)end)) hit=0;
        else if (rate<0.0f || rate>1.0f) hit=0;
        else if (!GScolsy2UtilChkInTri(&crossing,triangle,&normal)) hit=0;
        else hit=1;
        if (hit) {
            u16 id = entry->eventID;
            count++;
            for (s32 v=0;v<3;v++) *(Vec *)&output->vertices[v] = triangle[v];
            output->normal = normal;
            output->eventID = id;
            output++;
        }
    }
    return count != 0;
}
static s32 getEventList(GSvec *start, GSvec *end, CCDCheckEvent *events) {
    s32 count = 0;
    CCDCheckEvent temporary[4];
    GSmtx matrix, rotation;
    Vec direction;
    u8 enabled;
    CCDCheckFile *head = GScolsys2GetCCDFileHead();
    PSVECSubtract((Vec *)end,(Vec *)start,&direction);
    CCDCheckObject *object = head->objects;
    for (u32 i=0;i<head->count && count<4;i++,object++) {
        GScolsys2GetObjEnable(i,&enabled);
        if (enabled) {
            CCD_CHECKMDL_HEAD *model = object->checks;
            if (model) {
                GScolsys2GetObjMatrix(matrix.m,i);
                GScolsys2GetObjRotMatrix(rotation.m,i);
                u8 found = getMdlEventList(start,end,(GSvec *)&direction,model,&matrix,&rotation,temporary);
                CCDCheckEvent *entry=temporary;
                for (s32 j=0;j<found && count<4;entry++,j++) {
                    CCDCheckEvent *existing=events;
                    s32 k;
                    for(k=0;k<count;existing++,k++) if(existing->eventID==entry->eventID) break;
                    if(k>=count) {
                        s32 index=count;
                        count++;
                        CCDCheckEvent *output=&events[index];
                        for(s32 v=0;v<3;v++) *(Vec *)&output->vertices[v]=*(Vec *)&entry->vertices[v];
                        output->normal=entry->normal;
                        output->eventID=entry->eventID;
                    }
                }
            }
        }
    }
    return count;
}
extern "C" s32 GScolsys2CheckGetEventID(GSvec *start,GSvec *end,CCDCheckEvent *events) {
    if (!GScolsys2GetCCDFileHead()) return 0;
    if (PSVECDistance((Vec *)end,(Vec *)start) <= 0.0f) return 0;
    return getEventList(start,end,events);
}
