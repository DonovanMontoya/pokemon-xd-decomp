#include <game/pxdvs/GSAPI/GSmaterial/GSmaterial.hpp>
extern "C" {
GSimageDesc* HSD_ImageDescAlloc();
void HSD_ImageDescRemove(GSimageDesc*);
void HSD_MObjSetAlpha(HSD_MObj*, f32);
u32 HSD_MObjGetFlags(HSD_MObj*);
void HSD_MObjClearFlags(HSD_MObj*, u32);
void HSD_MObjSetFlags(HSD_MObj*, u32);
void HSD_MObjCompileTev(HSD_MObj*);
void GSlogWrite(const char*, ...);
}
// The original API uses this distinguished pointer to mean no override saved.
static inline GSimageDesc* noSavedImage() { return (GSimageDesc*)0xfefefefe; }
static inline void* noSavedPE() { return (void*)0xfefefefe; }
extern "C" void GSmaterialResetTexture(GSmaterial* m) {
    if (m->savedImage != noSavedImage()) {
        HSD_TObj* t = m->object->tobj;
        GSimageDesc* old = (GSimageDesc*)t->imagedesc;
        t->imagedesc = m->savedImage;
        HSD_ImageDescRemove(old);
        m->savedImage = noSavedImage();
    }
}
extern "C" void GSmaterialGetTexture(GSmaterial* m, GStexture* texture) {
    GSimageDesc* image;
    if (m->savedImage != noSavedImage()) image = m->savedImage;
    else image = (GSimageDesc*)m->object->tobj->imagedesc;
    texture->inUse = 0;
    if (image) {
        s32 format = GXFmtToGStextureFmt(image->format);
        GStextureCreateFromMemory(texture, image->width, image->height, image->image, format, 0, (u8)image->mipmap);
    }
}
extern "C" void GSmaterialSetTexture(GSmaterial* m, GStexture* texture) {
    GSimageDesc* image;
    if (m->savedImage == noSavedImage()) {
        m->savedImage = (GSimageDesc*)m->object->tobj->imagedesc;
        image = HSD_ImageDescAlloc();
    } else image = (GSimageDesc*)m->object->tobj->imagedesc;
    if (image) {
        image->image = GStextureLockImage(texture, 0);
        image->width = GStextureGetXsize(texture);
        image->height = GStextureGetYsize(texture);
        image->format = (GXTexFmt)GStextureGetGXformat(texture, 1);
        image->mipmap = GStextureGetMiplevels(texture) != 0;
        image->minLOD = 0.0f;
        image->maxLOD = 0.0f;
        GStextureUnlockImage(texture);
        m->object->tobj->imagedesc = image;
    }
}
extern "C" void GSmaterialGetModulate(GSmaterial* m, GXColor* color) {
    color->r = m->modulate.r; color->g = m->modulate.g;
    color->b = m->modulate.b; color->a = m->modulate.a;
}
extern "C" void GSmaterialResetAlpha(GSmaterial* m) { HSD_MObjSetAlpha(m->object, (f32)m->alpha / 255.0f); }
struct MaterialColor { GXColor ambient, diffuse, specular; f32 alpha, shininess; };
extern "C" void GSmaterialStoreAlpha(GSmaterial* m) { m->alpha = (u8)(s32)(255.0f * ((MaterialColor*)m->object->mat)->alpha); }
extern "C" void GSmaterialSetEnvMapBlendValue(GSmaterial* m, f32 blend) { HSD_TObj* t = m->environment; m->environmentBlend = blend; if (t) t->blending = blend; }
extern "C" void GSmaterialSetEnvMapParams(GSmaterial* m, s32 source, s32 mode, GStexture* t, f32 blend) { m->environmentSource = source; m->environmentMode = mode; m->environmentBlend = blend; m->environmentTexture = t; }
extern "C" void GSmaterialSetModulate(GSmaterial* m, GXColor* c) { m->modulate.r = c->r; m->modulate.g = c->g; m->modulate.b = c->b; m->modulate.a = c->a; }
extern "C" void GSmaterialSetColorChannels(GSmaterial* m, u8* c) { m->channels[0] = c[0]; m->channels[1] = c[1]; m->channels[2] = c[2]; m->channels[3] = c[3]; }
extern "C" void GSmaterialSetAlpha(GSmaterial* m, f32 alpha) { HSD_MObjSetAlpha(m->object, alpha); }
extern "C" u32 GSmaterialGetEnabledExtensions(GSmaterial* m) { return m->extensions; }
extern "C" void GSmaterialResetPEdescr(GSmaterial* m) { if (m->savedPE != noSavedPE()) { m->object->pe = m->savedPE; m->savedPE = noSavedPE(); } }
extern "C" void GSmaterialSetPEdescr(GSmaterial* m, void* pe) {
    if (m->savedPE == noSavedPE()) m->savedPE = m->object->pe;
    else GSlogWrite("GSmaterialSetPEdescr: Warning: already using a custom description!\n");
    m->object->pe = pe;
}
extern "C" void GSmaterialResetFlags(GSmaterial* m) { HSD_MObjClearFlags(m->object, 0x4000600f); HSD_MObjSetFlags(m->object, m->savedFlags); HSD_MObjCompileTev(m->object); }
extern "C" u32 GSmaterialGetFlags(GSmaterial* m) {
    u32 flags = HSD_MObjGetFlags(m->object), result = 0;
    if (flags & 1) result |= 1;
    if (flags & 2) result |= 2;
    if (flags & 4) result |= 4;
    if (flags & 8) result |= 8;
    if (flags & 0x40000000) result |= 0x10;
    if (flags & 0x2000) result |= 0x20;
    if (flags & 0x4000) result |= 0x40;
    return result;
}
extern "C" void GSmaterialSetFlags(GSmaterial* m, u32 flags) {
    m->savedFlags = HSD_MObjGetFlags(m->object);
    HSD_MObjClearFlags(m->object, 0x4000600f);
    u32 result = 0;
    if (flags & 1) result |= 1;
    if (flags & 2) result |= 2;
    if (flags & 4) result |= 4;
    if (flags & 8) result |= 8;
    if (flags & 0x10) result |= 0x40000000;
    if (flags & 0x20) result |= 0x2000;
    if (flags & 0x40) result |= 0x4000;
    HSD_MObjSetFlags(m->object, result);
    HSD_MObjCompileTev(m->object);
}

#include <game/maximum/GSAPI/baselib/class.h>
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
struct GSmatObj { HSD_MObj parent; GSmaterial* material; };
struct GStexExpression { s32 type; GStexExpression* next; };
struct GSmatClass {
    HSD_ClassInfo parent;
    void (*setup)(HSD_MObj*, u32);
    s32 (*load)(HSD_MObj*, void*);
    GStexExpression* (*makeExpression)(HSD_MObj*, HSD_TObj*, GStexExpression**);
    void (*setupExpression)(HSD_MObj*, u32);
    void (*update)(HSD_MObj*, u32, void*);
    void (*compile)(HSD_MObj*);
};
struct GStexDesc {
    char* className; GStexDesc* next; s32 id, source;
    GSvec rotation, scale, translation;
    s32 wrapS, wrapT; u8 repeatS, repeatT;
    u32 flags; f32 blending; s32 magFilter;
    GSimageDesc* image; void *palette, *lod, *tev;
};
extern "C" {
extern GSmatClass hsdMObj;
void HSD_TObjRemove(HSD_TObj*);
void HSD_ImageDescFree(GSimageDesc*);
HSD_TObj* HSD_TObjLoadDesc(GStexDesc*);
HSD_TObj* HSD_MObjGetTObj(HSD_MObj*);
void HSD_MObjAddTObjNext(HSD_MObj*, HSD_TObj*, HSD_TObj*);
void HSD_MObjAddTObj(HSD_MObj*, HSD_TObj*);
void HSD_MObjSetDefaultClass(GSmatClass*);
s32 HSD_TExpGetType(GStexExpression*);
void HSD_TExpColorSwap(GStexExpression*, u8, u8, u8, u8);
GStexExpression* HSD_TExpCnst(void*, s32, s32, GStexExpression**);
GStexExpression* HSD_TExpTev(GStexExpression**);
void HSD_TExpColorOp(GStexExpression*, s32, s32, s32, u8);
void HSD_TExpAlphaOp(GStexExpression*, s32, s32, s32, u8);
void HSD_TExpColorIn(GStexExpression*, s32, GStexExpression*, s32, GStexExpression*, s32, GStexExpression*, s32, GStexExpression*);
void HSD_TExpAlphaIn(GStexExpression*, s32, GStexExpression*, s32, GStexExpression*, s32, GStexExpression*, s32, GStexExpression*);
static void _GSmaterialObjInit();
static s32 _matGSmatObjLoad(HSD_MObj*, void*);
static GStexExpression* _matGSmatObjMakeTExp(HSD_MObj*, HSD_TObj*, GStexExpression**);
static void _matGSmatEnableEnvMapExt(GSmaterial*);
extern GSmatClass _matGSmatObj = { { { _GSmaterialObjInit } } };
}
typedef char GSmatClassSizeCheck[sizeof(GSmatClass) == 0x54 ? 1 : -1];
typedef char GSmatObjSizeCheck[sizeof(GSmatObj) == 0x24 ? 1 : -1];
typedef char GStexDescSizeCheck[sizeof(GStexDesc) == 0x5c ? 1 : -1];
static GStexDesc environmentDesc = { 0, 0, 0, 4, {0,0,0}, {1,1,1}, {0,0,0}, 0, 0, 1, 1, 0, 0.5f, 1, 0, 0, 0, 0 };
static inline void disableMaterialExtensions(GSmaterial* material, u32 mask) {
    HSD_MObj* object;
    u32 disable;
    disable = mask & material->extensions;
    object = material->object;
    if (disable & 1) material->modulate.r = material->modulate.g = material->modulate.b = material->modulate.a = 127;
    if (disable & 2) { material->channels[0] = 0; material->channels[1] = 1; material->channels[2] = 2; material->channels[3] = 3; }
    if (disable & 4) {
        HSD_MObj* owner = material->object;
        HSD_TObj* environment = material->environment;
        HSD_TObj* texture = owner->tobj;
        GSimageDesc* image = material->environmentImage;
        if (texture && environment) {
            if (texture == environment) owner->tobj = environment->next;
            else {
                for (; texture; texture = texture->next) {
                    if (texture->next == environment) texture->next = environment->next;
                }
            }
            if (image) HSD_ImageDescRemove(image);
            if (environment) HSD_TObjRemove(environment);
        }
        material->environmentTexture = 0;
    }
    material->extensions &= ~disable;
    if (material->extensions == 0) ((GSmatObj*)object)->material = 0;
    HSD_MObjCompileTev(object);
}
extern "C" void GSmaterialDisableExtension(GSmaterial* material, u32 mask) { disableMaterialExtensions(material, mask); }
extern "C" void GSmaterialEnableExtension(GSmaterial* material, u32 mask) {
    u32 enable;
    HSD_MObj* object;
    enable = mask & ~material->extensions;
    object = material->object;
    if (enable) {
        ((GSmatObj*)object)->material = material;
        if (enable & 4) _matGSmatEnableEnvMapExt(material);
        material->extensions |= enable;
        HSD_MObjCompileTev(object);
    }
}
extern "C" void GSmaterialInit() { HSD_MObjSetDefaultClass(&_matGSmatObj); }
extern "C" {
static void _GSmaterialObjInit() {
    hsdInitClassInfo((HSD_ClassInfo*)&_matGSmatObj, (HSD_ClassInfo*)&hsdMObj, "GSmaterial MObj", "GSmaterial MObj", sizeof(GSmatClass), sizeof(GSmatObj));
    _matGSmatObj.load = _matGSmatObjLoad;
    _matGSmatObj.makeExpression = _matGSmatObjMakeTExp;
}
static GStexExpression* _matGSmatObjMakeTExp(HSD_MObj* object, HSD_TObj* textures, GStexExpression** list) {
    GSmaterial* material;
    GStexExpression* result;
    GStexExpression* color;
    result = hsdMObj.makeExpression(object, textures, list);
    material = ((GSmatObj*)object)->material;
    if (!material) return result;
    if (material->extensions & 2) {
        for (GStexExpression* expression = result; expression; expression = expression->next) {
            if (HSD_TExpGetType(expression) == 1) HSD_TExpColorSwap(expression, material->channels[0], material->channels[1], material->channels[2], material->channels[3]);
        }
    }
    if (material->extensions & 1) {
        color = HSD_TExpCnst(&material->modulate.r, 1, 0, list);
        GStexExpression* alpha = HSD_TExpCnst(&material->modulate.a, 6, 0, list);
        GStexExpression* expression = HSD_TExpTev(list);
        HSD_TExpColorOp(expression, 0, 0, 1, 1);
        HSD_TExpColorIn(expression, 0, 0, 1, color, 1, result, 0, 0);
        HSD_TExpAlphaOp(expression, 0, 0, 0, 1);
        HSD_TExpAlphaIn(expression, 0, 0, 5, alpha, 5, result, 0, 0);
        result = expression;
    }
    return result;
}
static void _matGSmatEnableEnvMapExt(GSmaterial* material) {
    HSD_MObj* object;
    GStexture* texture;
    texture = material->environmentTexture;
    if (texture) {
        object = material->object;
        GSimageDesc* image = HSD_ImageDescAlloc();
        environmentDesc.flags = 0x80;
        environmentDesc.blending = material->environmentBlend;
        switch (material->environmentSource) {
        case 1: environmentDesc.flags |= 5; break;
        case 0: environmentDesc.flags |= 1; break;
        default: environmentDesc.flags |= 6; break;
        }
        if (material->environmentMode == 0) environmentDesc.flags |= 0x40000;
        else environmentDesc.flags |= 0x30000;
        image->image = GStextureLockImage(texture, 0);
        image->width = GStextureGetXsize(texture);
        image->height = GStextureGetYsize(texture);
        image->format = (GXTexFmt)GStextureGetGXformat(texture, 1);
        switch (image->format) {
        case GX_TF_I4: case GX_TF_I8: case GX_TF_IA4: case GX_TF_IA8: case GX_TF_RGB565: case GX_TF_RGB5A3: case GX_TF_RGBA8: case GX_TF_CMPR:
            break;
        default:
            GSlogWrite("GSmaterial: Unsupported texture format for environment map!\n");
            HSD_ImageDescRemove(image); HSD_ImageDescFree(image);
            disableMaterialExtensions(material, 4);
            return;
        }
        image->mipmap = GStextureGetMiplevels(texture) != 0;
        image->minLOD = 0.0f; image->maxLOD = 0.0f;
        environmentDesc.image = image;
        HSD_TObj* environment = HSD_TObjLoadDesc(&environmentDesc);
        HSD_TObj* last = HSD_MObjGetTObj(object);
        if (last) {
            while (last->next) last = last->next;
            HSD_MObjAddTObjNext(object, last, environment);
        } else HSD_MObjAddTObj(object, environment);
        material->environment = environment; material->environmentImage = image;
        GStextureUnlockImage(texture);
    } else {
        GSlogWrite("GSmaterial: Error creating environment map: no texture defined!\n");
        disableMaterialExtensions(material, 4);
    }
}
static s32 _matGSmatObjLoad(HSD_MObj* object, void* desc) {
    s32 result = hsdMObj.load(object, desc);
    if (result) return result;
    ((GSmatObj*)object)->material = 0;
    return 0;
}
}
