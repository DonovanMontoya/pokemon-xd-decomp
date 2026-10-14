extern "C" {
#include <libc/stdio.h>
}
#include <game/pxdvs/GSAPI/GSScript/tvariant.hpp>
#include <libc/string.h>
extern "C" int atoi(const char*);
extern "C" double atof(const char*);
namespace GSscript {
tigaVariant _dummyValue;
#pragma dont_inline on
s32 tigaVariant::getCnvInteger() {
    if (type == 3) return atoi(value.string);
    tigaErrMessage("integer convert error"); return 0;
}
f32 tigaVariant::getCnvSingle() {
    if (type == 3) return atof(value.string);
    tigaErrMessage("single convert error"); return 0.0f;
}
char* tigaVariant::getCnvString(char* destination) {
    if (type == 1) { ::sprintf(destination, "%d", value.integer); return destination; }
    if (type == 2) { ::sprintf(destination, "%.3f", value.single); return destination; }
    if (type == 4) { ::sprintf(destination, "<%.3f,%.3f,%.3f>", value.vector->param1, value.vector->param2, value.vector->param3); return destination; }
    tigaErrMessage("string convert error"); destination[0] = 0; return destination;
}
struct VariantVector : GSvec { VariantVector() {} };
GSvec* tigaVariant::getCnvVector() {
    static VariantVector vTemp;
    if (type == 4) return value.vector;
    f32 scalar;
    if (type == 1) scalar = value.integer;
    else if (type == 2) scalar = value.single;
    else scalar = getCnvSingle();
    // The original writes x twice and leaves z unchanged.
    vTemp.param1 = scalar; vTemp.param2 = scalar; vTemp.param1 = scalar;
    return &vTemp;
}
// The fixed array cannot resize or append in the original release.
void tigaArrayFixed::push_back(tigaVariant*) {}
void tigaArrayFixed::resize(int) {}
tigaVariant* tigaArrayFixed::fe_get() {
    u32 index = cursor;
    if (index >= (u32)count) { _dummyValue.type = 1; _dummyValue.value.integer = 0; return &_dummyValue; }
    cursor = index + 1;
    return (tigaVariant*)((u8*)this + cursor * 8 + 8);
}
tigaVariant* tigaArrayFixed::get(int index) {
    if (index < 0 || index >= count) { _dummyValue.type = 1; _dummyValue.value.integer = 0; return &_dummyValue; }
    return &values[index];
}
void tigaArrayFixed::set(int index, const tigaVariant* source) {
    if (index < 0) return;
    if (index >= count) return;
    values[index].type = source->type; values[index].flags = source->flags; values[index].value.integer = source->value.integer;
}
// Comparisons promote numeric operands; strings compare their lengths.
#define DEFINE_VARIANT_COMPARISON(name, operation, message) \
void tigaVariant::name(tigaVariant* result, tigaVariant* other) { \
    s32 common; \
    bool sameType = other->type == type; \
    result->type = 1; result->value.integer = 0; \
    common = other->type; s32 leftType = type; if (leftType > common) common = leftType; \
    switch (common) { \
    case 1: { \
        s32 left; if (leftType == 1) left = value.integer; else if (leftType == 2) left = (s32)value.single; else left = getCnvInteger(); \
        s32 right; if (other->type == 1) right = other->value.integer; else if (other->type == 2) right = (s32)other->value.single; else right = other->getCnvInteger(); \
        if (left operation right) result->value.integer = 1; \
        break; \
    } \
    case 2: { \
        f32 left; if (leftType == 1) left = value.integer; else if (leftType == 2) left = value.single; else left = getCnvSingle(); \
        f32 right; if (other->type == 1) right = other->value.integer; else if (other->type == 2) right = other->value.single; else right = other->getCnvSingle(); \
        if (left operation right) result->value.integer = 1; \
        break; \
    } \
    case 3: { \
        if (sameType) { \
            u32 right = strlen(other->value.string); \
            if (strlen(value.string) operation right) result->value.integer = 1; \
        } \
        break; \
    } \
    default: tigaErrMessage(message); break; \
    } \
}
DEFINE_VARIANT_COMPARISON(condLe, <=, "le convert error")
DEFINE_VARIANT_COMPARISON(condLs, <, "ls convert error")
DEFINE_VARIANT_COMPARISON(condGe, >=, "ge convert error")
DEFINE_VARIANT_COMPARISON(condGt, >, "gt convert error")
#undef DEFINE_VARIANT_COMPARISON
#pragma dont_inline reset
}
