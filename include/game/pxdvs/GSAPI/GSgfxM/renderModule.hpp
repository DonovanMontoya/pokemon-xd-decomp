#ifndef GSGFX_RENDER_MODULE_HPP
#define GSGFX_RENDER_MODULE_HPP
#include <global.h>
class GSgfxLayer;
enum GSgfxLayerPass { GSgfxLayerPassDefault = 0 };
struct GSgfxRenderModule {
    void (*init)(void*);
    void (*preUpdate)(f32);
    void (*render)(GSgfxLayer*, GSgfxLayerPass);
    void (*renderFast)();
    void (*postUpdate)(f32);
    void (*tick)();
    void (*reserved)();
};
void GSgfxRenderModuleInit();
void GSgfxRenderModuleRegister(u8, GSgfxRenderModule*, void*);
void GSgfxRenderModuleDoPreUpdate(f32);
void GSgfxRenderModuleDoRenderFast();
void GSgfxRenderModuleDoRender(GSgfxLayer*, GSgfxLayerPass);
void GSgfxRenderModuleDoPostUpdate(f32);
bool GSgfxRenderModuleIsRendering();
#endif
