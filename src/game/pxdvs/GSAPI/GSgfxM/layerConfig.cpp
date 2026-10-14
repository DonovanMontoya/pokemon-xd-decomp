#include "layer_private.h"
static LayerConfigData configData;
extern "C" {
void Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(s32 id,s32 relative,s32 offset) {
    LayerNode* layer=findConfigLayer(id);
    if (layer) {
        LayerNode* other=findConfigLayer(relative);
        if (!other) { switch(offset) { case 1: offset=3; break; case 2: offset=4; break; } }
        SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,offset,other);
    }
}
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(s32 id) {
    LayerNode* layer=findConfigLayer(id); if(layer) __dt__10GSgfxLayerFv(layer,1);
}
s32 Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(char* name,u32 opaque,u32 translucent,u32 matrices,s32 type,bool color,bool alpha,bool depth,s32 relative,s32 offset) {
    LayerNode* layer=GSgfxLayerFindByName(name);
    if (layer) {
        void* stack=layerField<void*>(layer,0x19a0);
        if (((opaque+31)&~31u)!=layerField<u32>(layer,0x181c) ||
            ((translucent+31)&~31u)!=layerField<u32>(layer,0x18d8) ||
            ((matrices+31)&~31u)!=((u32)(layerField<u8*>(stack,8)-layerField<u8*>(stack,0))/48+1)) {
            __dt__10GSgfxLayerFv(layer,1); layer=0;
        }
    }
    if (!layer) {
        s32 id=freeConfigLayerID();
        if (id!=-1) {
            void* storage=__nw__FUl(0x1a14);
            layer=storage ? __ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(storage,id,name,opaque,translucent,matrices,0) : 0;
        }
        if (!layer) return -1;
    }
    configData.id=layer->id; configData.name=name; configData.type=type;
    configData.clearColor=color; configData.clearAlpha=alpha; configData.clearDepth=depth; configData.visible=1;
    configData.opaqueSize=opaque; configData.translucentSize=translucent; configData.matrixCount=matrices;
    LayerNode* other=findConfigLayer(relative);
    SetLayerType__10GSgfxLayerF14GSgfxLayerType(layer,configData.type);
    SetWantClearFlags__10GSgfxLayerFbbb(layer,configData.clearColor,configData.clearAlpha,configData.clearDepth);
    if (other) SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,offset,other);
    else switch(offset) {
        case 1: case 3: SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,3,0); break;
        case 2: case 4: SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,4,0); break;
        default: SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,0,0); break;
    }
    SetPassVisibility__10GSgfxLayerFbb(layer,1,1); layerField<u8>(layer,0x19b3)=0;
    SetLayerVisibility__10GSgfxLayerFb(layer,configData.visible); return layer->id;
}
void Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(LayerConfigData* data) {
    LayerNode* p=GetLayerList__10GSgfxLayerFv();
    while (p) { LayerNode* next=p->next; __dt__10GSgfxLayerFv(p,1); p=next; }
    LayerNode* previous=0;
    for (;data->id!=-1;data++) {
        LayerNode* layer=findConfigLayer(data->id);
        if (!layer) {
            s32 id;
            if (data->id==255) id=freeConfigLayerID(); else id=data->id;
            if (id!=-1) {
                void* storage=__nw__FUl(0x1a14);
                layer=storage ? __ct__10GSgfxLayerF12GSgfxLayerIDPcUlUlUl14GSgfxLayerType(storage,id,data->name,data->opaqueSize,data->translucentSize,data->matrixCount,0) : 0;
            }
            if (!layer) continue;
        }
        SetLayerType__10GSgfxLayerF14GSgfxLayerType(layer,data->type);
        SetWantClearFlags__10GSgfxLayerFbbb(layer,data->clearColor,data->clearAlpha,data->clearDepth);
        if (previous) SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,2,previous);
        else SetPriority__10GSgfxLayerF16GSgfxLayerOffsetP10GSgfxLayer(layer,4,0);
        SetPassVisibility__10GSgfxLayerFbb(layer,1,1); layerField<u8>(layer,0x19b3)=0;
        SetLayerVisibility__10GSgfxLayerFb(layer,data->visible); previous=layer;
    }
    GSgfxLayerSetActive(GetLayerList__10GSgfxLayerFv()->id);
}
}
