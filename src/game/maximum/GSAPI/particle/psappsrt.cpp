#include "game/maximum/GSAPI/particle/psappsrt.h"
#define NULL ((void*)0)
static u16 psSizeofAppSRT;
static PSAppSRT *freeAppSRT;


s32 psRemoveGeneratorAppSRT(PSGenerator *arg0) {
    PSAppSRT *temp_r31;
    PSAppSRT *temp_r3;
    PSAppSRT *temp_r4;
    u16 temp_r0;
    void (*temp_r12)(PSAppSRT *);

    temp_r3 = arg0->appsrt;
    if (temp_r3 == NULL) {
        return -1;
    }
    if ((PSGenerator *) temp_r3->generator == arg0) {
        temp_r3->generator = NULL;
    }
    temp_r4 = arg0->appsrt;
    temp_r0 = temp_r4->references - 1;
    temp_r4->references = temp_r0;
    if (temp_r0 == 0) {
        temp_r31 = arg0->appsrt;
        temp_r12 = temp_r31->freefunc;
        if (temp_r12 != NULL) {
            temp_r12(temp_r31);
        }
        temp_r31->next = freeAppSRT;
        freeAppSRT = temp_r31;
        numActivePSAppSRT -= 1;
    }
    arg0->appsrt = NULL;
    return temp_r0;
}

s32 psRemoveParticleAppSRT(PSParticle *arg0) {
    PSAppSRT *temp_r31;
    PSAppSRT *temp_r4;
    u16 temp_r0;
    void (*temp_r12)(PSAppSRT *);

    temp_r4 = arg0->appsrt;
    if (temp_r4 == NULL) {
        return -1;
    }
    temp_r0 = temp_r4->references - 1;
    temp_r4->references = temp_r0;
    if (temp_r0 == 0) {
        temp_r31 = arg0->appsrt;
        temp_r12 = temp_r31->freefunc;
        if (temp_r12 != NULL) {
            temp_r12(temp_r31);
        }
        temp_r31->next = freeAppSRT;
        freeAppSRT = temp_r31;
        numActivePSAppSRT -= 1;
    }
    arg0->appsrt = NULL;
    return temp_r0;
}

s32 psChangeGeneratorAppSRT(PSGenerator* gp, PSAppSRT* srt) {
    if (srt == NULL || gp == NULL) return -1;
    if (gp->appsrt != NULL) psRemoveGeneratorAppSRT(gp);
    gp->appsrt = srt;
    return ++srt->references;
}

s32 psChangeParticleAppSRT(PSParticle* pp, PSAppSRT* srt) {
    if (srt == NULL || pp == NULL) return -1;
    if (pp->appsrt != NULL) psRemoveParticleAppSRT(pp);
    pp->appsrt = srt;
    return ++srt->references;
}

s32 psAttachGeneratorAppSRT(PSGenerator *arg0, PSAppSRT *arg1) {
    u16 temp_r0;

    if ((arg1 == NULL) || (arg0 == NULL) || ((PSAppSRT *) arg0->appsrt != NULL)) {
        return -1;
    }
    arg0->appsrt = arg1;
    temp_r0 = arg1->references + 1;
    arg1->references = temp_r0;
    return temp_r0;
}

s32 psAttachParticleAppSRT(PSParticle *arg0, PSAppSRT *arg1) {
    u16 temp_r0;

    if ((arg1 == NULL) || (arg0 == NULL) || ((PSAppSRT *) arg0->appsrt != NULL)) {
        return -1;
    }
    arg0->appsrt = arg1;
    temp_r0 = arg1->references + 1;
    arg1->references = temp_r0;
    return temp_r0;
}

static PSAppSRT* psNewAppSRT(s8 arg1, u16 temp_r31) {
    PSAppSRT *temp_r3;
    PSAppSRT *temp_r3_2;
    u16 temp_r4;

    if ((PSAppSRT *) freeAppSRT == NULL) {
        temp_r3 = HSD_Alloc((u32) psSizeofAppSRT);
        freeAppSRT = temp_r3;
        if (temp_r3 != NULL) {
            memset(temp_r3, 0, (u32) psSizeofAppSRT);
        }
    }
    temp_r3_2 = freeAppSRT;
    if (temp_r3_2 != NULL) {
        freeAppSRT = temp_r3_2->next;
        temp_r3_2->next = NULL;
        temp_r3_2->references = 1;
        temp_r3_2->frame = 0;
        temp_r3_2->status = (u8) arg1;
        temp_r3_2->translate.z = 0.0f;
        temp_r3_2->translate.y = 0.0f;
        temp_r3_2->translate.x = 0.0f;
        temp_r3_2->rotation.z = 0.0f;
        temp_r3_2->rotation.y = 0.0f;
        temp_r3_2->rotation.x = 0.0f;
        temp_r3_2->scale.z = 1.0f;
        temp_r3_2->scale.y = 1.0f;
        temp_r3_2->scale.x = 1.0f;
        temp_r3_2->freefunc = NULL;
        temp_r3_2->generatorOwned = 0;
        temp_r3_2->generator = NULL;
        temp_r3_2->id = temp_r31;
        temp_r4 = numActivePSAppSRT + 1;
        numActivePSAppSRT = temp_r4;
        if (temp_r4 > (u16) numPeakPSAppSRT) {
            numPeakPSAppSRT = temp_r4;
        }
    }
    return temp_r3_2;
}

void psAddGeneratorAppSRT(PSGenerator *gp, s8 status) { gp->appsrt = psNewAppSRT(status, gp->id); }

void psRemoveAppSRT(void) {
    PSAppSRT *temp_r31;
    PSAppSRT *var_r3;

    var_r3 = freeAppSRT;
while (var_r3 != NULL) {
        temp_r31 = var_r3->next;
        HSD_Free(var_r3);
        var_r3 = temp_r31;
}
    freeAppSRT = NULL;
}

s32 psInitAppSRT(s32 count, s32 size) {
    s32 i; PSAppSRT* srt;
    numActivePSAppSRT = 0; numPeakPSAppSRT = 0;
    psSizeofAppSRT = size; freeAppSRT = NULL;
    for (i = 0; i < count; i++) {
        srt = HSD_Alloc(size);
        if (srt == NULL) return i;
        memset(srt, 0, size);
        srt->next = freeAppSRT; freeAppSRT = srt;
    }
    return i;
}
