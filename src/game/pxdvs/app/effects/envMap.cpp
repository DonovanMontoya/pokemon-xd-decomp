#include <game/pxdvs/app/wazaSequence/wazaeffectsPrivate.hpp>
#include <game/pxdvs/GSAPI/GSmodel/GSmodel.hpp>

void Stop__8GSeffectFv(GSeffect*);

bool envMapEffect::_start() {
    if (model == 0) return false;
    GSmodelEnableEnvMap(model, texture, type, value);
    return true;
}

void envMapEffect::_stop() {
    if (model != 0) GSmodelDisableEnvMap(model);
}

bool envMapEffect::_update(f32) {
    if (model == 0) return false;
    if (!GSmodelIsEnvMapEnabled(model)) GSmodelEnableEnvMap(model, texture, type, value);
    else GSmodelSetEnvMapBlendValue(model, value);
    return true;
}

envMapEffect::~envMapEffect() { Stop__8GSeffectFv(this); }
