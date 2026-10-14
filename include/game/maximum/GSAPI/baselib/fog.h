#ifndef HSD_FOG_H
#define HSD_FOG_H
typedef struct HSD_FogAdj {
    void* class_info;
    unsigned short ref_count, ref_count_individual;
    unsigned int flags;
    short center;
    unsigned short width;
    float mtx[4][4];
} HSD_FogAdj;
typedef struct HSD_Fog {
    void* class_info;
    unsigned short ref_count, ref_count_individual;
    int type;
    HSD_FogAdj* fog_adj;
    float start, end;
    unsigned char color[4];
} HSD_Fog;
void HSD_FogSet(HSD_Fog*);
#endif
