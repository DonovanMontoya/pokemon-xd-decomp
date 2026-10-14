#include <game/maximum/GSAPI/baselib/random.h>

extern "C" s32 _HSD_MemCheckOwn(void*);

u32 __hsd_rand_seed_default = 1;
u32* __hsd_rand_seed_hold = &__hsd_rand_seed_default;

extern "C" {

void _HSD_RandForgetMemory() {
    if (_HSD_MemCheckOwn(__hsd_rand_seed_hold)) {
        __hsd_rand_seed_hold = &__hsd_rand_seed_default;
    }
}

s32 HSD_Randi(s32 maxValue) {
    *__hsd_rand_seed_hold = *__hsd_rand_seed_hold * 214013 + 2531011;
    return static_cast<s32>(maxValue * (*__hsd_rand_seed_hold >> 16)) / 65536;
}

f32 HSD_Randf() {
    *__hsd_rand_seed_hold = *__hsd_rand_seed_hold * 214013 + 2531011;
    return static_cast<f32>(*__hsd_rand_seed_hold >> 16) / 65536.0f;
}

u16 HSD_Rand() {
    *__hsd_rand_seed_hold = *__hsd_rand_seed_hold * 214013 + 2531011;
    return *__hsd_rand_seed_hold >> 16;
}

}
