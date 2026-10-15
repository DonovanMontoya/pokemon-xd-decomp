#include <dolphin/gx.h>
#include <game/pxdvs/GSAPI/GSfilter/GSfilterPrivate.hpp>
#include <libc/string.h>
extern "C" {
void* GSmemAlloc(unsigned long);
void GSgfxVFInit(VFFormat*);
void GSgfxVFCreate(VFFormat*);
void GSgfxVFSetElement(VFFormat*, s32, s32, s32, u8);
void GSgfxVFSetArray(VFFormat*, s32, s32, void*, u8, u32);
void GSmtx44Ortho(f32*, f32, f32, f32, f32, f32, f32);
void DCFlushRange(void*, u32);
extern f32 mtxIdent[3][4];
static void _filterRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer*, s32);
struct FilterRenderModule {
    void (*init)(void*);
    void (*preUpdate)(f32);
    void (*render)(GSgfxLayer*, s32);
    void (*renderFast)();
    void (*postUpdate)(f32);
    void (*tick)();
    u32 reserved;
};
void GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(u8, FilterRenderModule*, void*);
// The final reserved word is preserved from the retail registration record.
static const FilterRenderModule filterModule = {0, 0, _filterRender__FP10GSgfxLayer14GSgfxLayerPass, 0, 0, 0, 0xB29A48E1};
static FilterData filtersData;
GSfilter* gsDefaultFilterPtr;
static u8 gModuleInited;
void GSfilterInitialise(u8 arg0) {
    FilterRenderModule module;
    s32 temp_r31;
    u8 *temp_r3;
    GSfilter *var_r4;
    GSfilter *var_r7;
    u8 var_r3;
    u8 var_r5;
    VFFormat *temp_r29;
    GXColor *temp_r4;
    GXColor *temp_r6;

    memset(&filtersData, 0, 0x45C);
    temp_r31 = arg0 * 7;
    temp_r3 = (u8*)GSmemAlloc(temp_r31);
    if (temp_r3 != 0) {
        memset(temp_r3, 0, temp_r31);
        temp_r6 = (GXColor*)(temp_r3 + arg0 * 3);
        temp_r29 = &filtersData.format;
        filtersData.handles = (GSfilter*)temp_r3;
        filtersData.colors = temp_r6;
        filtersData.vertices[0][0] = 0;
        filtersData.vertices[0][1] = 0;
        filtersData.vertices[1][0] = 0;
        filtersData.vertices[1][1] = 0x1E0;
        filtersData.vertices[2][0] = 0x280;
        filtersData.vertices[2][1] = 0x1E0;
        filtersData.vertices[3][0] = 0x280;
        filtersData.vertices[3][1] = 0;
        filtersData.capacity = arg0;
        GSgfxVFInit(temp_r29);
        GSgfxVFCreate(temp_r29);
        GSgfxVFSetElement(temp_r29, 9, 0, 2, 0);
        GSgfxVFSetElement(temp_r29, 0xB, 1, 5, 0);
        GSgfxVFSetArray(temp_r29, 9, 2, filtersData.vertices, 4, 0x10);
        var_r4 = filtersData.handles;
        var_r5 = 0;
loop_3:
        if (var_r5 < arg0) {
            var_r4->index = var_r5;
            var_r5 += 1;
            var_r4++;
            goto loop_3;
        }
        if ((u8) filtersData.allocated < (u8) filtersData.capacity) {
            var_r7 = filtersData.handles;
            var_r3 = 0;
loop_9:
            if (var_r3 >= (u8) filtersData.capacity) {
                goto block_10;
            }
            if ((u8) var_r7->allocated == 0) {
                temp_r4 = filtersData.colors + var_r3;
                temp_r4->r = 0;
                temp_r4->g = 0;
                temp_r4->b = 0;
                temp_r4->a = 0;
                var_r7->allocated = 1U;
                filtersData.allocated = (u8) (filtersData.allocated + 1);
            } else {
                var_r3 += 1;
                var_r7++;
                goto loop_9;
            }
        } else {
block_10:
            var_r7 = 0;
        }
        gsDefaultFilterPtr = var_r7;
        if ((u8) gModuleInited == 0) {
            module = filterModule;
            GSgfxRenderModuleRegister__FUcP17GSgfxRenderModulePv(0x9C, &module, 0);
            gModuleInited = 1;
        }
    }
}

static void _filterRender__FP10GSgfxLayer14GSgfxLayerPass(GSgfxLayer *arg0, s32 arg1) {
    f32 projection[4][4];
    s32 *temp_r3;
    GXColor *var_r8;
    s32 temp_r5;
    s32 temp_r8;
    u8 temp_r30;
    u8 var_r7;
    GSgfxMatrixStack *temp_r27;
    GSfilter *var_r29;

    if ((s32) arg0->field28 == 6) {
        if (arg1 != 1) {
            return;
        }
        if (((u8) filtersData.allocated != 0) && ((u8) filtersData.visible != 0)) {
            temp_r30 = filtersData.capacity;
            var_r29 = filtersData.handles;
            GSmtx44Ortho(&projection[0][0], 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -30000.0f);
            arg0->fieldD54 = 1;
            arg0->fieldD58 = projection[0][0];
            arg0->fieldD5C = projection[0][3];
            arg0->fieldD60 = projection[1][1];
            arg0->fieldD64 = projection[1][3];
            arg0->fieldD68 = projection[2][2];
            arg0->fieldD6C = projection[2][3];
            temp_r27 = arg0->field19A0;
            memcpy(temp_r27->current->matrix, &mtxIdent, 0x30);
            temp_r3 = (s32*)&temp_r27->current->flags;
            *temp_r3 |= 1;
            arg0->field1684 = 0.0f;
            arg0->field1688 = 30000.0f;
            if ((u8) arg0->field16A7 != 0) {
                if ((u8) arg0->field16A6 != 0) {
                    arg0->field170C = (s32) (arg0->field170C | 0x100);
                    arg0->field17C4 = (s32) (arg0->field17C4 | 0x100);
                }
                arg0->field170C = (s32) (arg0->field170C | 0x40);
                arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
                arg0->field17C4 = (s32) (arg0->field17C4 | 0x40);
                arg0->field1760 = (s32) (arg0->field1760 | 0x40);
            }
            arg0->field16AC = (s32) (arg0->field16AC | 0x20);
            arg0->field16A8 = (s32) (arg0->field16A8 | 1);
            arg0->field1764 = (s32) (arg0->field1764 | 0x20);
            arg0->field1760 = (s32) (arg0->field1760 | 1);
            if ((s32) arg0->field1994 != 1) {
                arg0->field1994 = 1;
                arg0->field1990 = (u8*)arg0 + arg0->field1994 * 0xBC + 0x1818;
            }
            arg0->field1644 = 1;
            arg0->field1648 = 4;
            arg0->field164C = 5;
            arg0->field1650 = 5;
            arg0->field170C = (s32) (arg0->field170C | 1);
            arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
            arg0->field17C4 = (s32) (arg0->field17C4 | 1);
            arg0->field1760 = (s32) (arg0->field1760 | 0x40);
            arg0->field1656 = 1;
            arg0->field1657 = 1;
            arg0->field1658 = 0;
            arg0->field170C = (s32) (arg0->field170C | 4);
            arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
            arg0->field17C4 = (s32) (arg0->field17C4 | 4);
            temp_r8 = arg0->field1760 | 0x40;
            arg0->field1760 = temp_r8;
            arg0->field1664 = 7;
            arg0->field1670 = 0;
            arg0->field1668 = 0;
            arg0->field166C = 7;
            arg0->field1671 = 0;
            arg0->field1672 = 1;
            arg0->field170C = (s32) (arg0->field170C | 0x10);
            arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
            arg0->field17C4 = (s32) (arg0->field17C4 | 0x10);
            arg0->field1760 = (s32) (arg0->field1760 | 0x40);
            arg0->field165C = 0;
            arg0->field1660 = 3;
            arg0->field170C = (s32) (arg0->field170C | 8);
            arg0->field16A8 = (s32) (arg0->field16A8 | 0x40);
            arg0->field17C4 = (s32) (arg0->field17C4 | 8);
            temp_r5 = arg0->field1760 | 0x40;
            arg0->field1760 = temp_r5;
            arg0->fieldD8C = 0;
            arg0->field16B8 = (s32) (arg0->field16B8 | 2);
            arg0->field16A8 = (s32) (arg0->field16A8 | 2);
            arg0->field1770 = (s32) (arg0->field1770 | 2);
            arg0->field1760 = (s32) (arg0->field1760 | 2);
            arg0->setRenderStateAndSelect((GSgfxVF*)&filtersData.format);
            arg0->field1998 = 0x80;
            arg0->beginSurface(filtersData.visible * 4);
            var_r7 = 0;
            var_r8 = filtersData.colors;
loop_15:
            if (var_r7 < temp_r30) {
                if ((u8) var_r29->visible != 0) {
                    *(volatile u8 *)0xCC008000 = 0;
                    *(volatile u32 *)0xCC008000 = *(u32*)var_r8;
                    *(volatile u8 *)0xCC008000 = 1;
                    *(volatile u32 *)0xCC008000 = *(u32*)var_r8;
                    *(volatile u8 *)0xCC008000 = 2;
                    *(volatile u32 *)0xCC008000 = *(u32*)var_r8;
                    *(volatile u8 *)0xCC008000 = 3;
                    *(volatile u32 *)0xCC008000 = *(u32*)var_r8;
                }
                var_r7 += 1;
                var_r29++;
                var_r8++;
                goto loop_15;
            }
            arg0->endSurface();
        }
    }
}

void GSfilterSetColor(GSfilter* handle, const void* input) {
    const u8* color = (const u8*)input;
    if (handle->allocated) {
        u8* output = (u8*)&filtersData.colors[handle->index];
        output[0] = color[0];
        output[1] = color[1];
        output[2] = color[2];
        output[3] = color[3];
        DCFlushRange(output, 4);
        if (color[3]) {
            if (!handle->visible) {
                handle->visible = 1;
                filtersData.visible++;
            }
        } else if (handle->visible) {
            handle->visible = 0;
            filtersData.visible--;
        }
    }
}

void GSfilterFree(GSfilter *arg0) {
    if ((u8) arg0->allocated != 0) {
        arg0->allocated = 0U;
        if ((u8) arg0->visible != 0) {
            arg0->visible = 0U;
            filtersData.visible = (u8) (filtersData.visible - 1);
        }
        filtersData.allocated = (u8) (filtersData.allocated - 1);
    }
}

GSfilter* GSfilterCreate(const void* input) {
    const u8* color = (const u8*)input;
    if (filtersData.capacity > filtersData.allocated) {
        GSfilter* handle = filtersData.handles;
        for (u8 i = 0; i < filtersData.capacity; i++, handle++) {
            if (!handle->allocated) {
                u8* output = (u8*)&filtersData.colors[i];
                output[0] = color[0];
                output[1] = color[1];
                output[2] = color[2];
                output[3] = color[3];
                if (color[3] && !handle->visible) {
                    handle->visible = 1;
                    filtersData.visible++;
                }
                handle->allocated = 1;
                filtersData.allocated++;
                return handle;
            }
        }
    }
    return 0;
}
}
