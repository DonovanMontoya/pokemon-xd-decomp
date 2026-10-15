#include <global.h>
struct GSgfxLayer;
enum GSgfxLayerPass { EFFECT_PASS_DEFAULT };
class GSeffect {
public:
    bool active, visible; u8 reserved02[2]; GSeffect* next;
    virtual bool _start(); virtual void _stop(); virtual bool _update(f32); virtual void _render(GSgfxLayer*,GSgfxLayerPass); virtual void _fastRender(); virtual ~GSeffect();
    GSeffect(); void Stop(); bool Start();
};
static GSeffect* g_effects_list;
static void _effectUpdate(f32);
static void _effectRender(GSgfxLayer*,GSgfxLayerPass);
static void _effectFastRender();
struct GSgfxRenderModule { void* reserved00; void (*update)(f32); void (*render)(GSgfxLayer*,GSgfxLayerPass); void (*fastRender)(); void* reserved10; void* reserved14; u32 id; };
extern void GSgfxRenderModuleRegister(u8,GSgfxRenderModule*,void*);
extern "C" u8 GSgfxVideoGetVsyncRate();
extern "C" void GSeffectInitSystem() {
    GSgfxRenderModule module = {0,_effectUpdate,_effectRender,_effectFastRender,0,0,0xb29a48e1};
    GSgfxRenderModuleRegister(0x60,&module,0);
}
static void _effectFastRender() {
    for (GSeffect* effect = g_effects_list; effect; effect=effect->next)
        if (effect->active && effect->visible) effect->_fastRender();
}
static void _effectRender(GSgfxLayer* layer,GSgfxLayerPass pass) {
    for (GSeffect* effect = g_effects_list; effect; effect=effect->next)
        if (effect->active && effect->visible) effect->_render(layer,pass);
}

static inline void stopEffect(GSeffect* effect) { if(effect->active) { effect->_stop(); effect->active=0; effect->visible=0; } }
static void _effectUpdate(f32 delta) {
    for (GSeffect* effect=g_effects_list; effect; effect=effect->next) {
        f32 step = delta / GSgfxVideoGetVsyncRate();
        if (effect->active && !effect->_update(step)) stopEffect(effect);
    }
}
GSeffect::~GSeffect() {
    GSeffect* current = g_effects_list;
    if (this == current) { g_effects_list = next; next=0; }
    else {
        while (current) {
            if (current->next == this) { current->next = next; next=0; break; }
            current = current->next;
        }
    }
}
void GSeffect::Stop() { if(active) { _stop(); active=0; visible=0; } }
bool GSeffect::Start() {
    if (_start()) { active=1; visible=1; }
    else { active=0; visible=0; }
    return active;
}
void GSeffect::_fastRender() {}
void GSeffect::_render(GSgfxLayer*,GSgfxLayerPass) {}
bool GSeffect::_update(f32) { return true; }
void GSeffect::_stop() {}
bool GSeffect::_start() { return true; }
GSeffect::GSeffect() { active=0; visible=0; next=0; next=g_effects_list; g_effects_list=this; }
