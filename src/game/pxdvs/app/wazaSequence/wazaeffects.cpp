#include <game/pxdvs/app/wazaSequence/wazaeffectsPrivate.hpp>

struct ParticleBankOwner {
    u8 reserved[12];
    _GSparticleBank *bank;
};

struct BoneFillData {
    enumNullJointName first, second;
    f32 length;
    u32 size;
    _GSparticleBank *bank;
    u32 reserved;
};

void EffectEntry::boneFillEffectLoad(u8 **cursor) {
    BoneFillData *data;
    _GSparticleBank *bank = 0;
    data = (BoneFillData *)*cursor;
    *cursor += sizeof(BoneFillData);
    *cursor = (u8 *)(((u32)*cursor + 31) & ~31);
    *cursor += (data->size + 31) & ~31;
    if (field9) {
        SequenceEntry *entry = waza->GetEntryFromID(field9);
        if (((EffectEntry *)entry)->effect) bank = ((ParticleBankOwner *)((EffectEntry *)entry)->effect)->bank;
    } else {
        bank = data->bank;
    }
    effect = new boneFillEffect(bank, data->first, data->second, data->length);
}

void EffectEntry::blurEffectLoad(u8 **cursor) {
    u32 *data = (u32 *)*cursor;
    *cursor += 12;
    active = 1;
    table = (EffectTableEntry *)*cursor;
    count = data[0];
    effectTime = 0.0f;
    index = 0;
    *cursor += count * sizeof(EffectTableEntry);
    effect = new blurEffect(data[2] != 0);
}

void EffectEntry::envMapEffectLoad(u8 **cursor) {
    u32 *data = (u32 *)*cursor;
    *cursor += 16;
    active = 1;
    table = (EffectTableEntry *)*cursor;
    count = data[2];
    effectTime = 0.0f;
    index = 0;
    *cursor += count * sizeof(EffectTableEntry);
    effect = new envMapEffect(data[0], data[1]);
}

void EffectEntry::filterEffectLoad(u8 **cursor) {
    bool pe = false;
    bool combine = false;
    u32 *data = (u32 *)*cursor;
    *cursor += 16;
    active = 1;
    table = (EffectTableEntry *)*cursor;
    count = data[1];
    effectTime = 0.0f;
    index = 0;
    *cursor += count * sizeof(EffectTableEntry);
    switch (data[0]) {
    case 0:
        effect = new filterEffect;
        break;
    case 1:
        combine = true;
    case 2:
        if ((s32)(data[3] & 1) == 1) pe = true;
        effect = new filterEffect(pe, combine);
        break;
    }
}
