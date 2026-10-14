#ifndef GS_SCRIPT_VARIANT_HPP
#define GS_SCRIPT_VARIANT_HPP
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
namespace GSscript {
struct tigaVariant {
    s16 type, flags;
    union { s32 integer; f32 single; char* string; GSvec* vector; void* pointer; } value;
    s32 getCnvInteger();
    f32 getCnvSingle();
    char* getCnvString(char*);
    GSvec* getCnvVector();
    void condLe(tigaVariant*, tigaVariant*);
    void condLs(tigaVariant*, tigaVariant*);
    void condGe(tigaVariant*, tigaVariant*);
    void condGt(tigaVariant*, tigaVariant*);
};
struct tigaArrayFixed {
    s32 count; u32 cursor, reserved08, reserved0C;
    tigaVariant values[1];
    void push_back(tigaVariant*);
    void resize(int);
    tigaVariant* fe_get();
    tigaVariant* get(int);
    void set(int, const tigaVariant*);
};
typedef char VariantSizeCheck[sizeof(tigaVariant) == 8 ? 1 : -1];
extern tigaVariant _dummyValue;
s32 tigaErrMessage(const char*);
}
#endif
