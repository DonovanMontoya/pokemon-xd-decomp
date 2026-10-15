#include "layer_private.h"
extern "C" {
void* GStextureCreate(u16,u16,s32,void*,u32);
void GStextureFree(void*);
int stricmp(const char*,const char*);
void PrepareNextFrame__10GSgfxLayerFv(void*);
void BuildRenderList__10GSgfxLayerFv(void*);
void Prerender__10GSgfxLayerFv(void*);
extern void* fbTexPtr__10GSgfxLayer;
extern u16 fbTexRefCount__10GSgfxLayer;
extern void* distTexPtr__10GSgfxLayer;
extern u16 distTexRefCount__10GSgfxLayer;
u8 gsgfx_layer_inPrimitive;
void* gsgfx_layer_activeFifo;
}
static LayerNode* _layerBottom;
static LayerNode* _layerIDTable[16];
static u8 _layerRenderStats;
extern "C" {
void GetFifoSize__10GSgfxLayerFPUlPUl(void *arg0, s32 *arg1, s32 *arg2) {
    if (arg1 != NULL) {
        *arg1 = layerField<u32>(arg0, 0x181C);
    }
    if (arg2 != NULL) {
        *arg2 = layerField<u32>(arg0, 0x18D8);
    }
}

void* GetTextureCopy__10GSgfxLayerFv(void *arg0) {
    if (layerField<u32>(arg0, 0x4) & 0x200) {
        return layerField<void*>(arg0, 0x19A4);
    }
    return 0;
}

void SetWantClearFlags__10GSgfxLayerFbbb(void *arg0, bool arg1, bool arg2, bool arg3) {
    layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) & 0xFFFFFE3F);
    if (arg1 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x40);
    }
    if (arg2 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x80);
    }
    if (arg3 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x100);
    }
}

void SetClearFlags__10GSgfxLayerFbbb(void *arg0, u8 arg1, u8 arg2, u8 arg3) {
    layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) & 0xFFFFFFC7);
    if (arg1 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 8);
    }
    if (arg2 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x10);
    }
    if (arg3 != 0) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 0x20);
    }
}

void SetPassVisibility__10GSgfxLayerFbb(void *arg0, bool arg1, bool arg2) {
    if (arg1 == 1) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 2);
    } else {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) & 0xFFFFFFFD);
    }
    if (arg2 == 1) {
        layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) | 4);
        return;
    }
    layerField<u32>(arg0, 0x4) = (s32) (layerField<u32>(arg0, 0x4) & 0xFFFFFFFB);
}

s32 IsLayerVisible__10GSgfxLayerFv(void *arg0) {
    return layerField<u32>(arg0, 0x4) & 1;
}

void SetLayerVisibility__10GSgfxLayerFb(void *arg0, bool arg1) {
    u8 temp_r4;

    if (arg1 == 1) {
        layerField<u8>(arg0, 0x19B3) = (u8) (layerField<u8>(arg0, 0x19B3) + 1);
        return;
    }
    temp_r4 = layerField<u8>(arg0, 0x19B3);
    if (temp_r4 != 0) {
        layerField<u8>(arg0, 0x19B3) = (u8) (temp_r4 - 1);
    }
}

void SetLayerType__10GSgfxLayerF14GSgfxLayerType(void *arg0, s32 arg1) {
    s32 temp_r0;
    u16 temp_r3;
    u16 temp_r3_2;
    u16 temp_r3_4;
    u16 temp_r3_5;
    u16 temp_r3_7;
    void* temp_r3_3;
    void* temp_r3_6;
    u8 var_r31;
    u8 var_r30;
    u8 var_r3;
    u8 var_r4;

    var_r31 = 0;
    var_r30 = 0;
    var_r4 = 0;
    temp_r0 = layerField<u32>(arg0, 0x2C);
    var_r3 = 0;
    if (arg1 != temp_r0) {
        switch (temp_r0) {                          /* switch 1; irregular */
        case 1:                                     /* switch 1 */
            var_r31 = 1;
            var_r3 = 1;
            break;
        case 4:                                     /* switch 1 */
            var_r3 = 1;
            break;
        }
        switch (arg1) {                             /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            var_r30 = 1;
            layerField<float>(arg0, 0x19BC) = 0.0f;
            var_r4 = 1;
            layerField<float>(arg0, 0x19C0) = 0.5f;
            layerField<float>(arg0, 0x19C4) = 0.0f;
            layerField<float>(arg0, 0x19C8) = 0.0f;
            layerField<float>(arg0, 0x19CC) = 0.5f;
            layerField<float>(arg0, 0x19D0) = 0.0f;
            layerField<u8>(arg0, 0x19B8) = 0;
            break;
        case 4:                                     /* switch 2 */
            var_r4 = 1;
            break;
        }
        if ((var_r3 != 0) && (var_r4 == 0)) {
            if (--fbTexRefCount__10GSgfxLayer == 0) {
                GStextureFree(fbTexPtr__10GSgfxLayer);
                fbTexPtr__10GSgfxLayer = 0;
            }
            goto block_22;
        }
        if ((var_r3 == 0) && (var_r4 != 0)) {
            if (++fbTexRefCount__10GSgfxLayer == 1) {
                temp_r3_3 = GStextureCreate(0, 0, 0x45, 0, 0);
                fbTexPtr__10GSgfxLayer = temp_r3_3;
                if (temp_r3_3 == 0) {
                    layerField<u32>(arg0, 0x2C) = 0;
                    fbTexRefCount__10GSgfxLayer = 0;
                    return;
                }
            }
        }
block_22:
        if ((var_r31 != 0) && (var_r30 == 0)) {
            if (--distTexRefCount__10GSgfxLayer == 0) {
                GStextureFree(distTexPtr__10GSgfxLayer);
                distTexPtr__10GSgfxLayer = 0;
            }
            goto block_32;
        }
        if ((var_r31 == 0) && (var_r30 != 0) && (++distTexRefCount__10GSgfxLayer == 1) && (temp_r3_6 = GStextureCreate(0, 0, 0xA3, 0, 0), distTexPtr__10GSgfxLayer = temp_r3_6, ((temp_r3_6 == 0) != 0))) {
            layerField<u32>(arg0, 0x2C) = 0;
            distTexRefCount__10GSgfxLayer = 0;
            if (--fbTexRefCount__10GSgfxLayer == 0) {
                GStextureFree(fbTexPtr__10GSgfxLayer);
                fbTexPtr__10GSgfxLayer = 0;
            }
        } else {
block_32:
            layerField<u32>(arg0, 0x2C) = arg1;
        }
    }
}

u8 GSgfxLayerGetStatsRenderMode() { return _layerRenderStats; }
void GSgfxLayerSetStatsRenderMode(u8 enabled) { _layerRenderStats=enabled; }
void GSgfxLayerInvalidateAll__Fv() {
    for (LayerNode* p=_layerBottom;p;p=p->next) InvalidateState__10GSgfxLayerFv(p);
}
void GSgfxLayerPrepareNextFrame__Fv() {
    if (_layerBottom) for (LayerNode* p=_layerBottom;p;p=p->next) PrepareNextFrame__10GSgfxLayerFv(p);
}
LayerNode* GetLayerList__10GSgfxLayerFv() { return _layerBottom; }
LayerNode* GSgfxLayerGetLayerList() { return _layerBottom; }
void* GetFBTexture__10GSgfxLayerFv() { return fbTexPtr__10GSgfxLayer; }
s32 GSgfxLayerGetActive() {
    for (s32 i=0;i<16;i++) if (_layerIDTable[i]==gsgfxState->layer) return i;
    return -1;
}
void GSgfxLayerSetActive(s32 id) { if (id<16) gsgfxState->layer=_layerIDTable[id]; }
LayerNode* GSgfxLayerFindByID(s32 id) {
    if (id==-1) return 0;
    if (id<16) return _layerIDTable[id];
    return reinterpret_cast<LayerNode*>(id);
}
LayerNode* GSgfxLayerFindByName(char* name) {
    for (LayerNode* p=_layerBottom;p;p=p->next) {
        char local[32]; char* source=reinterpret_cast<char*>(p)+8;
        if ((s32)((u8)strlen(source)+1)<=32) memcpy(local,source,(u8)strlen(source)+1);
        else { memcpy(local,source,31); local[31]=0; }
        if (stricmp(local,name)==0) return p;
    }
    return 0;
}
s32 GSgfxLayerFindByName_C(char* name) {
    LayerNode* p=_layerBottom;
    for (;p;p=p->next) {
        char local[32]; char* source=reinterpret_cast<char*>(p)+8;
        if ((s32)((u8)strlen(source)+1)<=32) memcpy(local,source,(u8)strlen(source)+1);
        else { memcpy(local,source,31); local[31]=0; }
        if (stricmp(local,name)==0) break;
    }
    return p ? p->id : -1;
}
void GSgfxLayerInit__Fv() {
    for (s32 i=0;i<15;i++) _layerIDTable[i]=0;
    _layerBottom=0; _layerIDTable[15]=0; gsgfx_layer_inPrimitive=0;
}
void SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(void* object,s32 offset,void* relative) {
    LayerNode* layer=static_cast<LayerNode*>(object); LayerNode* other=static_cast<LayerNode*>(relative);
    if (_layerBottom==layer) _layerBottom=layer->next;
    else for (LayerNode* p=_layerBottom;p;p=p->next) if (p->next==layer) { p->next=layer->next; break; }
    switch (offset) {
    case 1: {
        LayerNode* p=_layerBottom;
        if (!p || p==other) { _layerBottom=layer; layer->next=p; return; }
        while (p->next && p->next!=other) p=p->next;
        layer->next=p->next; p->next=layer; return;
    }
    case 2:
        for (LayerNode* p=_layerBottom;p;p=p->next) if (p==other) { layer->next=p->next; p->next=layer; return; }
        return;
    case 3: layer->next=_layerBottom; _layerBottom=layer; return;
    case 4: {
        LayerNode* p=_layerBottom; layer->next=0;
        if (!p) { _layerBottom=layer; return; }
        while (p->next) p=p->next;
        p->next=layer; return;
    }
    case 0: return;
    }
}
void SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(void* layer,void* texture,bool copy,u8* params) {
    if (!texture) {
        layerField<u32>(layer,4)&=~0x200;
        if (fbTexPtr__10GSgfxLayer && layerField<void*>(layer,0x19a4)==fbTexPtr__10GSgfxLayer) {
            if (--fbTexRefCount__10GSgfxLayer==0) { GStextureFree(fbTexPtr__10GSgfxLayer); fbTexPtr__10GSgfxLayer=0; }
        }
        layerField<void*>(layer,0x19a4)=0;
    } else {
        if ((u32)texture==0xfefefefe) {
            if (++fbTexRefCount__10GSgfxLayer==1) {
                fbTexPtr__10GSgfxLayer=GStextureCreate(0,0,0x45,0,0);
                if (!fbTexPtr__10GSgfxLayer) { fbTexRefCount__10GSgfxLayer=0; return; }
            }
            texture=fbTexPtr__10GSgfxLayer;
        }
        layerField<u32>(layer,4)|=0x200; layerField<void*>(layer,0x19a4)=texture;
    }
    if (!copy) layerField<u32>(layer,0x19a8)=0;
    else if (!params) layerField<u32>(layer,0x19a8)=1;
    else { layerField<u32>(layer,0x19a8)=2; memcpy(&layerField<u8>(layer,0x19ac),params,7); }
}
}

extern "C" {
void GSlogWrite(const char*,...);
void GXResetWriteGatherPipe();
void MarkAndInvalidate__10GSgfxLayerFv(void*);
void PrepareDistortion__10GSgfxLayerFv(void*);
void PrepareFBCopy__10GSgfxLayerFv(void*);
void SendFifoToRenderer__10GSgfxLayerFP15_gsgfxLayerFifo(void*,void*);
void PrepareNextFrame__10GSgfxLayerFv(void* layer) {
    MarkAndInvalidate__10GSgfxLayerFv(layer);
    switch (layerField<s32>(layer,0x2c)) {
    case 1: PrepareDistortion__10GSgfxLayerFv(layer); break;
    case 4: PrepareFBCopy__10GSgfxLayerFv(layer); break;
    }
    layerField<void*>(layer,0x19dc)=0; layerField<void*>(layer,0x19ec)=0;
    layerField<void*>(layer,0x19fc)=0; layerField<void*>(layer,0x1a0c)=0;
}
void BuildRenderListPass__10GSgfxLayerF14GSgfxLayerPass(void* layer,s32 pass) {
    u8* fifo=static_cast<u8*>(layer)+0x1818+pass*0xbc;
    if (layerField<void*>(fifo,0xa4)) SendFifoToRenderer__10GSgfxLayerFP15_gsgfxLayerFifo(layer,layerField<void*>(fifo,0xa4));
    if (layerField<void*>(fifo,0) && !layerField<u8>(fifo,0x94)) SendFifoToRenderer__10GSgfxLayerFP15_gsgfxLayerFifo(layer,fifo);
    if (layerField<void*>(fifo,0xa8)) SendFifoToRenderer__10GSgfxLayerFP15_gsgfxLayerFifo(layer,layerField<void*>(fifo,0xa8));
}
void BuildRenderList__10GSgfxLayerFv(void* layer) {
    BuildRenderListPass__10GSgfxLayerF14GSgfxLayerPass(layer,0);
    BuildRenderListPass__10GSgfxLayerF14GSgfxLayerPass(layer,1);
}
}
static void updateLayerFifoUsage(u8* f) {
    u8* start=layerField<u8*>(f,0x88); u32 used;
    if (!start) used=0;
    else {
        u8* write=layerField<u8*>(f,0x20);
        if (write>=start) used=(write-start)+layerField<u16>(f,0xac)*layerField<u32>(f,4);
        else {
            u8* base=layerField<u8*>(f,0);
            s32 bytes=(base+layerField<u32>(f,4)-start)+(write-base);
            if (layerField<u16>(f,0xac)==0) {
                GSlogWrite("fifo wrap check flag failure!\n");
                GSlogWrite("ptr  =%08X, size =%08X\n",base,layerField<u32>(f,4));
                GSlogWrite("start=%08X, write=%08X\n",start,write);
                GSlogWrite("reg  =%08X\n",*(volatile u32*)0xcc003014);
                ++layerField<u16>(f,0xac);
            }
            used=bytes+(layerField<u16>(f,0xac)-1)*layerField<u32>(f,4);
        }
    }
    layerField<u32>(f,0xb4)=used;
    if (layerField<u32>(f,0xb4)>layerField<u32>(f,0xb8)) layerField<u32>(f,0xb8)=layerField<u32>(f,0xb4);
    if (layerField<u32>(f,0xb4)>=layerField<u32>(f,4)) layerField<u16>(f,0xae)=1;
}
static void updateLayerFifo(void* fifo) {
    u8* f=static_cast<u8*>(fifo);
    GXFifoObj* sdkFifo=reinterpret_cast<GXFifoObj*>(f+8);
    GXSaveCPUFifo(sdkFifo);
    volatile u32 status=*(volatile u32*)0xcc003014;
    u32 wrapped=(status>>26)&1;
    if (wrapped==1) { GXSetCPUFifo(sdk(GSgfxGPUGetImmediateFifo__Fv())); GXSetCPUFifo(sdkFifo); }
    if (wrapped==1) ++layerField<u16>(f,0xac);
    updateLayerFifoUsage(f);
    GXResetWriteGatherPipe(); GSgfxRenderWaitData wait; GSgfxRenderWaitInit__FP19GSgfxRenderWaitData(&wait);
    for (;;) {
        u8 full;
        if (layerField<u32>(f,0x54)==1) full=0;
        else {
            u8* write=layerField<u8*>(f,0x20); u8* read=layerField<u8*>(f,0x1c); u32 count;
            if (write>=read) count=write-read;
            else count=(layerField<u8*>(f,0xc)-read)+(write-layerField<u8*>(f,8));
            full=layerField<u32>(f,0x14)<=count;
        }
        if (full!=1) break;
        GSgfxRenderWaitTick__FP19GSgfxRenderWaitData(&wait);
    }
    GSgfxRenderWaitExit__FP19GSgfxRenderWaitData(&wait);
}
extern "C" {
void GSgfxLayerUpdateActiveFifoStats__Fv() {
    if (gsgfx_gpu_mode!=1) {
        void* fifo=gsgfx_layer_activeFifo; if (!fifo) return;
        updateLayerFifo(fifo);
    }
}
void SetupFifo__10GSgfxLayerFv(void* layer) {
    if (gsgfx_gpu_mode==2) {
        void* fifo=gsgfx_layer_activeFifo;
        if (fifo!=layerField<void*>(layer,0x1990)) {
            if (gsgfx_gpu_mode!=1 && fifo) updateLayerFifo(fifo);
            GXSetCPUFifo(reinterpret_cast<GXFifoObj*>(layerField<u8*>(layer,0x1990)+8));
            gsgfx_layer_activeFifo=layerField<void*>(layer,0x1990); gsgfxState->layer=layer;
        }
    }
}
}
extern "C" {
void GSgfxGPUSetFifoWritePtr__FP15GSgfx_GCFifoObjPv(void*,void*);
void GSgfxRenderAddToFifoList__FP15GSgfx_GCFifoObjPvPvUlPFPv_vPv(void*,void*,void*,u32,void(*)(void*),void*);
void GSgfxRenderModuleDoRender__FP10GSgfxLayer14GSgfxLayerPass(void*,s32);
void EffectDistortion__10GSgfxLayerFv(void*);
void EffectTextureCopy__10GSgfxLayerFP9GStexturebPUcbbb(void*,void*,bool,u8*,bool,bool,bool);
void EffectScreenClear__10GSgfxLayerFbbb(void*,bool,bool,bool);
void MarkAndInvalidate__10GSgfxLayerFv(void* layer) {
    for (s32 i=0;i<2;i++) {
        u8* fifo=static_cast<u8*>(layer)+0x1818+i*0xbc;
        if (layerField<void*>(fifo,0)) {
            if (reinterpret_cast<GXFifoObj*>(fifo+8)==GXGetCPUFifo()) updateLayerFifo(fifo);
            layerField<void*>(fifo,0x88)=layerField<void*>(fifo,0x20);
        }
    }
    layerField<u32>(layer,0x18c8)=layerField<u32>(layer,0x18cc);
    layerField<u32>(layer,0x1984)=layerField<u32>(layer,0x1988);
    layerField<u16>(layer,0x18c4)=0; layerField<u16>(layer,0x18c6)=0;
    layerField<u16>(layer,0x1980)=0; layerField<u16>(layer,0x1982)=0;
    InvalidateState__10GSgfxLayerFv(layer);
    u8 value=layerField<s32>(layer,0x2c)!=1 ? layerField<u8>(layer,0x16a7)!=0 : 0;
    layerField<u8>(layer,0x16a7)=value;
    layerField<u32>(layer,0x170c)|=0x40; layerField<u32>(layer,0x17c4)|=0x40;
    if (value) {
        layerField<u32>(layer,0x170c)|=0x200; layerField<u32>(layer,0x17c4)|=0x200;
        if (layerField<u8>(layer,0x16a6)) { layerField<u32>(layer,0x170c)|=0x100; layerField<u32>(layer,0x17c4)|=0x100; }
    }
    layerField<u32>(layer,0x16a8)|=0x40; layerField<u32>(layer,0x1760)|=0x40;
}
void SendFifoToRenderer__10GSgfxLayerFP15_gsgfxLayerFifo(void* layer,void* object) {
    u8* fifo=static_cast<u8*>(object);
    if (layerField<void*>(fifo,0)) {
        if (reinterpret_cast<GXFifoObj*>(fifo+8)==GXGetCPUFifo()) updateLayerFifo(fifo);
        layerField<void*>(fifo,0x8c)=layerField<void*>(fifo,0x20);
    }
    u32* begin=layerField<u32*>(fifo,0x88);
    u32 bytes=(u8*)layerField<void*>(fifo,0x8c)-(u8*)begin;
    u8 empty;
    if (!bytes) empty=1;
    else if (bytes!=32) empty=0;
    else empty=(begin[0]|begin[1]|begin[2]|begin[3]|begin[4]|begin[5]|begin[6]|begin[7])==0;
    if (empty==1) {
        GSgfxGPUSetFifoWritePtr__FP15GSgfx_GCFifoObjPv(fifo+8,layerField<void*>(fifo,0x88));
        layerField<void*>(fifo,0x8c)=layerField<void*>(fifo,0x88);
        layerField<u16>(fifo,0xac)=0; layerField<u16>(fifo,0xae)=0;
    }
    updateLayerFifoUsage(fifo);
    if (layerField<u16>(fifo,0xae)==1) {
        const char* pass="xluc"; if (layerField<s32>(layer,0x1994)==0) pass="opaque";
        GSlogWrite("fifo overflow in [%s]: %s pass",static_cast<u8*>(layer)+8,pass); return;
    }
    void* start=layerField<void*>(fifo,0x88);
    for (s32 i=0;i<4;i++) {
        u8* entry=static_cast<u8*>(layer)+0x19d4+i*0x10;
        void (*callback)(void*)=layerField<void(*)(void*)>(entry,8);
        if (!callback) break;
        if (static_cast<u8*>(layer)+0x1818+layerField<s32>(entry,0)*0xbc==fifo) {
            GSgfxRenderAddToFifoList__FP15GSgfx_GCFifoObjPvPvUlPFPv_vPv(fifo+8,start,layerField<void*>(entry,4),layerField<u32>(fifo,0x90),callback,layerField<void*>(entry,0xc));
            start=layerField<void*>(entry,4);
        }
    }
    GSgfxRenderAddToFifoList__FP15GSgfx_GCFifoObjPvPvUlPFPv_vPv(fifo+8,start,layerField<void*>(fifo,0x8c),layerField<u32>(fifo,0x90),0,0);
}
void SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(void* layer,s32 pass,bool enabled,LayerNode* other,s32 otherPass,s32 offset) {
    u8* fifo=static_cast<u8*>(layer)+0x1818+pass*0xbc;
    if (enabled==1) {
        u8* target=reinterpret_cast<u8*>(other)+0x1818+otherPass*0xbc;
        void** link=&layerField<void*>(target,offset==1 ? 0xa4 : 0xa8);
        layerField<u8>(fifo,0x94)=1; layerField<s32>(fifo,0x98)=other->id;
        layerField<s32>(fifo,0x9c)=otherPass; layerField<s32>(fifo,0xa0)=offset; *link=fifo; return;
    }
    if (layerField<void*>(fifo,0) && layerField<u8>(fifo,0x94)) {
        LayerNode* targetLayer=GSgfxLayerFindByID(layerField<s32>(fifo,0x98));
        u8* target=reinterpret_cast<u8*>(targetLayer)+0x1818+layerField<s32>(fifo,0x9c)*0xbc;
        void** link=&layerField<void*>(target,layerField<s32>(fifo,0xa0)==1 ? 0xa4 : 0xa8);
        layerField<u8>(fifo,0x94)=0; layerField<s32>(fifo,0x98)=-1;
        layerField<s32>(fifo,0x9c)=2; layerField<s32>(fifo,0xa0)=0; *link=0;
    }
}
void PrerenderPass__10GSgfxLayerF14GSgfxLayerPass(void* layer,s32 pass) {
    u8* fifo=static_cast<u8*>(layer)+0x1818+pass*0xbc;
    if (layerField<void*>(fifo,0)) {
        u32 visible=pass==0 ? 3 : 5;
        if (visible==(visible&layerField<u32>(layer,4))) {
            selectLayerPass(static_cast<GraphicsLayerState*>(layer),pass);
            SetupFifo__10GSgfxLayerFv(layer);
            GSgfxRenderModuleDoRender__FP10GSgfxLayer14GSgfxLayerPass(layer,pass); return;
        }
        if (fifo==gsgfx_layer_activeFifo) updateLayerFifo(fifo);
        GSgfxGPUSetFifoWritePtr__FP15GSgfx_GCFifoObjPv(fifo+8,layerField<void*>(fifo,0x88));
        layerField<void*>(fifo,0x8c)=layerField<void*>(fifo,0x88);
        layerField<u16>(fifo,0xac)=0; layerField<u16>(fifo,0xae)=0;
        InvalidateState__10GSgfxLayerFv(layer);
    }
}
void Prerender__10GSgfxLayerFv(void* layer) {
    PrerenderPass__10GSgfxLayerF14GSgfxLayerPass(layer,0);
    PrerenderPass__10GSgfxLayerF14GSgfxLayerPass(layer,1);
    LayerNode* next=layerField<LayerNode*>(layer,0);
    u8 color,alpha,depth;
    if (!next) { color=0; alpha=0; depth=0; }
    else {
        u32 want=layerField<u32>(next,4); u32 flags=layerField<u32>(layer,4);
        color=((flags&8) || ((want>>6)&1))!=0;
        alpha=((flags&0x10) || ((want>>7)&1))!=0;
        depth=((flags&0x20) || ((want>>8)&1))!=0;
    }
    if (layerField<void*>(layer,0x18d4)) selectLayerPass(static_cast<GraphicsLayerState*>(layer),1);
    else selectLayerPass(static_cast<GraphicsLayerState*>(layer),0);
    if (layerField<u32>(layer,4)&1) switch (layerField<s32>(layer,0x2c)) {
    case 4: break;
    case 1: EffectDistortion__10GSgfxLayerFv(layer); break;
    }
    if (layerField<u32>(layer,4)&0x200) switch (layerField<s32>(layer,0x19a8)) {
    case 0: EffectTextureCopy__10GSgfxLayerFP9GStexturebPUcbbb(layer,layerField<void*>(layer,0x19a4),0,0,color,alpha,depth); return;
    case 1: EffectTextureCopy__10GSgfxLayerFP9GStexturebPUcbbb(layer,layerField<void*>(layer,0x19a4),1,0,color,alpha,depth); return;
    case 2: EffectTextureCopy__10GSgfxLayerFP9GStexturebPUcbbb(layer,layerField<void*>(layer,0x19a4),1,static_cast<u8*>(layer)+0x19ac,color,alpha,depth); return;
    }
    else EffectScreenClear__10GSgfxLayerFbbb(layer,color,alpha,depth);
}
}
static u32 _layerPerfColor[8]={0x000000ff,0x00008000,0x00800000,0x00008080,0x00800080,0x00808000,0x000080ff,0x00808080};
static u32 _layerPerfUserColor=0x00ff8000;
extern "C" {
void GSgfxGPUEnterBufferedMode__FP15GSgfx_GCFifoObj(void*);
void GSmemFree(void*);
void __dl__FPv(void*);
void GSgfxRenderWaitForDrawComplete__Fv();
void LoadHWState__10GSgfxLayerFv(void*);
extern void* _layerStateLastHWState;
void GSgfxRenderModuleDoRenderFast__Fv();
void GSgfxLayerBuildRenderList__Fv() {
    if (_layerBottom) {
        if (gsgfx_gpu_mode!=1 && gsgfx_layer_activeFifo) updateLayerFifo(gsgfx_layer_activeFifo);
        for (LayerNode* p=_layerBottom;p;p=p->next) BuildRenderList__10GSgfxLayerFv(p);
    }
}
LayerNode* GSgfxLayerPrerender__Fv() {
    // No value is assigned for an empty list in the original implementation.
    LayerNode* p;
    LayerNode* last;
    GSgfxRenderModuleDoRenderFast__Fv();
    for (p=_layerBottom;p;p=p->next) {
        if (layerField<u8>(p,0x19b3)) layerField<u32>(p,4)|=1;
        else layerField<u32>(p,4)&=~1;
    }
    for (p=_layerBottom;p;p=p->next) { Prerender__10GSgfxLayerFv(p); last=p; }
    return last;
}
void CreateFifo__10GSgfxLayerF14GSgfxLayerPassUl(void* layer,s32 pass,u32 bytes) {
    u8* fifo=static_cast<u8*>(layer)+0x1818+pass*0xbc;
    layerField<void*>(fifo,0)=0; layerField<u32>(fifo,4)=0; memset(fifo+8,0,0x80);
    s32 id=layerField<s32>(layer,0x28);
    layerField<u32>(fifo,0x90)=id<8 ? _layerPerfColor[id] : _layerPerfUserColor;
    layerField<u16>(fifo,0xac)=0; layerField<u16>(fifo,0xae)=0;
    layerField<u32>(fifo,0xb0)=0; layerField<u32>(fifo,0xb4)=0; layerField<u32>(fifo,0xb8)=0;
    layerField<void*>(fifo,0x88)=0; layerField<void*>(fifo,0x8c)=0;
    layerField<u8>(fifo,0x94)=0; layerField<s32>(fifo,0x98)=-1;
    layerField<s32>(fifo,0x9c)=2; layerField<s32>(fifo,0xa0)=0;
    layerField<void*>(fifo,0xa4)=0; layerField<void*>(fifo,0xa8)=0;
    if (bytes) {
        layerField<u32>(fifo,4)=(bytes+31)&~31u;
        layerField<void*>(fifo,0)=GSmemAlloc(layerField<u32>(fifo,4));
        DCFlushRange(layerField<void*>(fifo,0),layerField<u32>(fifo,4));
        GSgfxGPUInitFifoBase__FP15GSgfx_GCFifoObjPvUl(reinterpret_cast<GSgfx_GCFifoObj*>(fifo+8),layerField<void*>(fifo,0),layerField<u32>(fifo,4));
        GXInitFifoPtrs(reinterpret_cast<GXFifoObj*>(fifo+8),layerField<void*>(fifo,0),layerField<void*>(fifo,0));
        if (gsgfx_gpu_mode==0) { gsgfx_layer_activeFifo=fifo; GSgfxGPUEnterBufferedMode__FP15GSgfx_GCFifoObj(fifo+8); }
    }
}
LayerNode* __ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(void* object,s32 id,char* name,u32 opaque,u32 translucent,u32 matrices,s32 type) {
    LayerNode* layer=static_cast<LayerNode*>(object);
    if (!opaque && !translucent) return layer;
    if (!name || GSgfxLayerFindByName(name) || !matrices) return layer;
    layer->id=id; layerField<u32>(layer,4)=7; layerField<u8>(layer,0x19b3)=1; layerField<s32>(layer,0x2c)=0;
    SetLayerType__10GSgfxLayerF14GSgfxLayerType(layer,type);
    layerField<s32>(layer,0x1994)=2;
    u32 count=strlen(name)+1; if (count>32) count=32;
    memcpy(reinterpret_cast<u8*>(layer)+8,name,count); layerField<u8>(layer,count+7)=0;
    CreateFifo__10GSgfxLayerF14GSgfxLayerPassUl(layer,0,opaque);
    CreateFifo__10GSgfxLayerF14GSgfxLayerPassUl(layer,1,translucent);
    LoadHWState__10GSgfxLayerFv(layer); GSgfx_GCInitState(); memset(reinterpret_cast<u8*>(layer)+0x30,0,0x1678);
    layerField<GSgfxMatrixStack*>(layer,0x19a0)=new GSgfxMatrixStack(matrices);
    if (!_layerBottom) { _layerBottom=layer; layer->next=0; }
    else { LayerNode* p=_layerBottom; while (p->next) p=p->next; layer->next=p->next; p->next=layer; }
    layerField<void*>(layer,0x199c)=0; layerField<s32>(layer,0x1998)=0x98;
    layerField<void*>(layer,0x19a4)=0; layerField<s32>(layer,0x19a8)=0;
    memset(reinterpret_cast<u8*>(layer)+0x19b4,0,0x20);
    PrepareNextFrame__10GSgfxLayerFv(layer);
    selectLayerPass(static_cast<GraphicsLayerState*>(object),layerField<void*>(layer,0x1818) ? 0 : 1);
    _layerIDTable[layer->id]=layer; return layer;
}
void* __dt__10GSgfxLayerFv(void* object,s16 release) {
    LayerNode* layer=static_cast<LayerNode*>(object);
    if (layer) {
        GSgfxRenderWaitForDrawComplete__Fv();
        SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(layer,0,0,0,0,0);
        SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(layer,1,0,0,0,0);
        SetLayerType__10GSgfxLayerF14GSgfxLayerType(layer,0);
        SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer,0,0,0);
        if (_layerBottom==layer) _layerBottom=layer->next;
        else {
            LayerNode* p=_layerBottom;
            while (p && p->next!=layer) p=p->next;
            p->next=layer->next;
        }
        void* fifo=gsgfx_layer_activeFifo;
        if (fifo && (fifo==reinterpret_cast<u8*>(layer)+0x1818 || fifo==reinterpret_cast<u8*>(layer)+0x18d4)) {
            updateLayerFifo(fifo); GXSetCPUFifo(sdk(GSgfxGPUGetImmediateFifo__Fv())); gsgfx_layer_activeFifo=0;
        }
        if (_layerStateLastHWState==reinterpret_cast<u8*>(layer)+0x30) _layerStateLastHWState=0;
        delete layerField<GSgfxMatrixStack*>(layer,0x19a0); _layerIDTable[layer->id]=0;
        if (layerField<void*>(layer,0x1818)) { GSmemFree(layerField<void*>(layer,0x1818)); layerField<void*>(layer,0x1818)=0; }
        if (layerField<void*>(layer,0x18d4)) { GSmemFree(layerField<void*>(layer,0x18d4)); layerField<void*>(layer,0x18d4)=0; }
        if (release>0) __dl__FPv(layer);
    }
    return layer;
}
}

extern "C" {
void GSprimSetRenderLayer__FP10GSgfxLayer(void*);
void GSprimSetQuadVertexOrder(s32);
void GSprimSetLineWidth(float);
void GSprimSetTextSize(float,float);
void GSprimSetTextWidth(float);
void GSprimSetTextColor(const u8*);
void GSprimDraw2DQuadWH(float,float,float,float,const GXColor*);
void GSprimDraw2DHLine(float,float,float,const GXColor*);
void GSprimWriteStr(float,float,const char*,...);
void GSprimWriteChar(float,float,char);
void GSmtx44Ortho(Mtx44,float,float,float,float,float,float);
}
extern Mtx mtxIdent;
extern "C" inline GXColor* GSgfxPerfColorToGSgfxCol(u32 packed) {
    static GXColor c;
    c.r=static_cast<u8>(packed>>16); c.g=static_cast<u8>(packed>>8);
    c.b=static_cast<u8>(packed); c.a=255;
    return &c;
}
struct LayerStatsRedirect { char marker; u8 pad[3]; LayerNode* target; s32 pass,order; };
ABI_SIZE(LayerStatsRedirect,0x10);
static const LayerStatsRedirect layerStatsRedirects[4]={
    {'#',{0,0,0},0,2,0}, {'$',{0,0,0},0,2,0},
    {'=',{0,0,0},0,2,0}, {'+',{0,0,0},0,2,0}
};
// Direct offset views keep this large overlay below the compiler's inline budget.
#define STATS_FIELD(type, base, offset) (*reinterpret_cast<type*>(reinterpret_cast<u8*>(base)+(offset)))
extern "C" void GSgfxLayerRenderStats__FP10GSgfxLayer(void* layer) {
    LayerStatsRedirect redirects[4];
    memcpy(redirects,layerStatsRedirects,sizeof(redirects));
    const GXColor background={32,32,32,192};
    const GXColor inactive={96,96,96,255};
    const GXColor empty={160,160,160,255};
    const GXColor white={255,255,255,255};
    const GXColor yellow={255,255,0,255};
    const GXColor red={224,64,64,255};
    if (!_layerRenderStats) return;
    s32 redirectCount=0;
    GSprimSetRenderLayer__FP10GSgfxLayer(layer);
    GSprimSetQuadVertexOrder(0);
    GSprimSetLineWidth(1.0f);
    GSprimSetTextSize(10.0f,10.0f);
    GSprimSetTextWidth(1.0f);
    GraphicsLayerState* state=static_cast<GraphicsLayerState*>(layer);
    state->blendMode=1; state->blendSource=4; state->blendDestination=5; state->logicOperation=5;
    state->pixelDirty|=1; state->dirty|=0x40; state->savedPixelDirty|=1; state->savedDirty|=0x40;
    Mtx44 projection;
    GSmtx44Ortho(projection,0.0f,480.0f,0.0f,640.0f,0.0f,-30000.0f);
    STATS_FIELD(s32,layer,0xD54)=1;
    STATS_FIELD(float,layer,0xD58)=projection[0][0];
    STATS_FIELD(float,layer,0xD5C)=projection[0][3];
    STATS_FIELD(float,layer,0xD60)=projection[1][1];
    STATS_FIELD(float,layer,0xD64)=projection[1][3];
    STATS_FIELD(float,layer,0xD68)=projection[2][2];
    STATS_FIELD(float,layer,0xD6C)=projection[2][3];
    memcpy(state->matrixStack->current->matrix,mtxIdent,sizeof(Mtx));
    state->matrixStack->current->flags|=1;
    STATS_FIELD(float,layer,0x1684)=0.0f;
    STATS_FIELD(float,layer,0x1688)=30000.0f;
    if (STATS_FIELD(u8,layer,0x16A7)) {
        if (STATS_FIELD(u8,layer,0x16A6)) { state->pixelDirty|=0x100; state->savedPixelDirty|=0x100; }
        state->pixelDirty|=0x40; state->dirty|=0x40; state->savedPixelDirty|=0x40; state->savedDirty|=0x40;
    }
    state->lineDirty|=0x20; state->dirty|=1; state->savedLineDirty|=0x20; state->savedDirty|=1;
    state->colorUpdate=1; state->alphaUpdate=0; state->depthBeforeTexture=0;
    state->pixelDirty|=4; state->dirty|=0x40; state->savedPixelDirty|=4; state->savedDirty|=0x40;
    state->depthEnable=0; state->depthCompare=3;
    state->pixelDirty|=8; state->dirty|=0x40; state->savedPixelDirty|=8; state->savedDirty|=0x40;
    state->alphaCompare0=7; state->alphaReference0=0; state->alphaCombine=0;
    state->alphaCompare1=7; state->alphaReference1=0; state->alphaDisabled=1;
    state->pixelDirty|=0x10; state->dirty|=0x40; state->savedPixelDirty|=0x10; state->savedDirty|=0x40;
    state->cullMode=0; state->cullDirty|=2; state->dirty|=2; state->savedCullDirty|=2; state->savedDirty|=2;
    STATS_FIELD(s32,layer,0xD90)=1; state->cullDirty|=4; state->dirty|=2; state->savedCullDirty|=4; state->savedDirty|=2;
    s32 count=0;
    for (LayerNode* p=_layerBottom;p;p=p->next) ++count;
    GSprimDraw2DQuadWH(10.0f,22.0f,620.0f,12.0f*count+28.0f,&background);
    GSprimSetTextColor(reinterpret_cast<const u8*>(&white));
    GSprimSetTextSize(10.0f,10.0f);
    GSprimWriteStr(25.0f,29.0f,"#"); GSprimWriteStr(50.0f,29.0f,"ID");
    GSprimWriteStr(85.0f,29.0f,"Name"); GSprimWriteStr(245.0f,29.0f,"TCAZ");
    GSprimWriteStr(295.0f,29.0f,"Opaque"); GSprimWriteStr(470.0f,29.0f,"Xluc");
    GSprimDraw2DHLine(20.0f,620.0f,42.0f,&yellow);
    s32 row=0;
    float y;
    char name[19];
    for (LayerNode* p=_layerBottom;p;p=p->next,++row) {
        s32 id=p->id;
        LayerNode* next=p->next;
        y=12.0f*row+47.0f;
        u32 packed=id<8 ? _layerPerfColor[id] : _layerPerfUserColor;
        GXColor tint=*GSgfxPerfColorToGSgfxCol(packed);
        GSprimDraw2DQuadWH(20.0f,y-1.0f,50.0f,12.0f,&tint);
        GSprimSetTextColor(reinterpret_cast<const u8*>(&white));
        GSprimWriteStr(25.0f,y,"%d",row); GSprimWriteStr(55.0f,y,"%d",id);
        u32 flags=STATS_FIELD(u32,p,4);
        u8 opaqueVisible=(flags>>1)&1, xlucVisible=(flags>>2)&1;
        if ((flags&1)!=1) { GSprimSetTextColor(reinterpret_cast<const u8*>(&inactive)); opaqueVisible=xlucVisible=0; }
        GSprimSetTextSize(8.5f,10.0f);
        if (static_cast<s32>(strlen(reinterpret_cast<char*>(p)+8)+1)<=19)
            memcpy(name,reinterpret_cast<char*>(p)+8,strlen(reinterpret_cast<char*>(p)+8)+1);
        else { memcpy(name,reinterpret_cast<char*>(p)+8,18); name[18]=0; }
        GSprimWriteStr(85.0f,y,"%s",name);
        GSprimSetTextSize(10.0f,10.0f);
        char status[5];
        status[0]=((flags&0x200) && STATS_FIELD(void*,p,0x19A4)) ? 'O':'X';
        u8 clearColor=0,clearAlpha=0,clearDepth=0;
        if (next) {
            u32 nextFlags=STATS_FIELD(u32,next,4);
            clearColor=(flags&8) || ((nextFlags>>6)&1);
            clearAlpha=(flags&0x10) || ((nextFlags>>7)&1);
            clearDepth=(flags&0x20) || ((nextFlags>>8)&1);
        }
        status[1]=clearColor==1?'O':'X'; status[2]=clearAlpha==1?'O':'X'; status[3]=clearDepth==1?'O':'X';
        if (next && ((STATS_FIELD(u32,next,4)&1)==1)) {
            switch (STATS_FIELD(s32,next,0x2C)) {
            case 1: status[1]='+'; status[2]='+';
            case 4: status[0]='+'; break;
            }
        }
        status[4]=0;
        GSprimWriteStr(245.0f,y,status);
        u32 used[2],peak[2],size[2];
        used[0]=STATS_FIELD(void*,p,0x1818)?STATS_FIELD(u32,p,0x18C8):0;
        used[1]=STATS_FIELD(void*,p,0x18D4)?STATS_FIELD(u32,p,0x1984):0;
        peak[0]=STATS_FIELD(void*,p,0x1818)?STATS_FIELD(u32,p,0x18D0):0;
        peak[1]=STATS_FIELD(void*,p,0x18D4)?STATS_FIELD(u32,p,0x198C):0;
        size[0]=STATS_FIELD(u32,p,0x181C); size[1]=STATS_FIELD(u32,p,0x18D8);
        for (s32 pass=0;pass<2;pass++) {
            float x=pass?470.0f:295.0f;
            u32 fifoOffset=pass?0x18D4:0x1818;
            if (STATS_FIELD(void*,p,fifoOffset) && STATS_FIELD(u8,p,fifoOffset+0x94)) {
                LayerStatsRedirect* redirect=&redirects[redirectCount];
                s32 targetID=STATS_FIELD(s32,p,fifoOffset+0x98);
                if (targetID==-1) redirect->target=0;
                else if (targetID<16) redirect->target=_layerIDTable[targetID];
                redirect->pass=STATS_FIELD(s32,p,fifoOffset+0x9C);
                redirect->order=STATS_FIELD(s32,p,fifoOffset+0xA0);
                GSprimSetTextColor(reinterpret_cast<const u8*>(&red));
                GSprimWriteChar(x,y,redirect->marker);
                ++redirectCount; x+=11.0f;
            }
            GSprimSetTextColor(reinterpret_cast<const u8*>(&white));
            if (size[pass]) {
                if ((pass?xlucVisible:opaqueVisible)==0) GSprimSetTextColor(reinterpret_cast<const u8*>(&inactive));
                else if (!used[pass]) GSprimSetTextColor(reinterpret_cast<const u8*>(&empty));
                if (used[pass]) GSprimWriteStr(x,y,"%.1f/%dK (%dK)",used[pass]*0.0009765625f,static_cast<u32>(size[pass]*0.0009765625f),static_cast<u32>(peak[pass]*0.0009765625f+0.5f));
                else GSprimWriteStr(x,y,"---/%dK (%dK)",static_cast<u32>(size[pass]*0.0009765625f),static_cast<u32>(peak[pass]*0.0009765625f+0.5f));
            }
        }
    }
    if (redirectCount>0) {
        GSprimDraw2DQuadWH(10.0f,12.0f*row+50.0f,620.0f,12.0f*redirectCount+4.0f,&background);
        y+=18.0f;
        for (s32 i=0;i<redirectCount;i++,y+=12.0f) {
            GSprimSetTextColor(reinterpret_cast<const u8*>(&red)); GSprimWriteChar(40.0f,y,redirects[i].marker);
            GSprimSetTextColor(reinterpret_cast<const u8*>(&white));
            LayerNode* target=redirects[i].target;
            if (static_cast<s32>(strlen(reinterpret_cast<char*>(target)+8)+1)<=19)
                memcpy(name,reinterpret_cast<char*>(target)+8,strlen(reinterpret_cast<char*>(target)+8)+1);
            else { memcpy(name,reinterpret_cast<char*>(target)+8,18); name[18]=0; }
            const char* pass=redirects[i].pass==0?"opaque":"xluc";
            const char* order=redirects[i].order==1?"before":"after";
            GSprimWriteStr(60.0f,y,"redirected %s: %s %s pass",order,name,pass);
        }
    }
}
#undef STATS_FIELD
