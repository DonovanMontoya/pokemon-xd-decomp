extern "C" {
#include <libc/stdio.h>
}
#include <global.h>
// The original GSvec has an empty inline constructor in this unit.
#ifndef GS_VEC_H
#define GS_VEC_H
struct GSvec {
    f32 param1;
    f32 param2;
    f32 param3;
    GSvec() {}
};
#endif
#include <game/pxdvs/GSAPI/GSScript/tiga.hpp>
#include <libc/string.h>
extern "C" char* strcat(char*, const char*);
extern "C" int atoi(const char*);
extern "C" double atof(const char*);
namespace GSscript {
tigaVariant _dummyValue;
struct varPool_t {
    void* slot[0x100];
};
extern "C" void PSVECSubtract(const GSvec*, const GSvec*, GSvec*);
extern "C" void PSVECScale(const GSvec*, GSvec*, f32);
extern "C" void PSVECAdd(const GSvec*, const GSvec*, GSvec*);
static int strcmpw(const char* a, const char* b);
static void** checkAllocedMemory(varPool_t* pool, void* ptr);
static void** varPoolSearchFree(varPool_t* pool);
GSvec nullVec;
varPool_t l_stringPool;
varPool_t l_vectorPool;
static char _tempString[0x100];
const char* tigaVariant::getTypeString(int type) {
    static const char* commType[] = {
        "type_nodef", "type_integer", "type_single", "type_string", "type_vector",
        "type_matrix", "type_object", "type_tarray", "type_funcptr",
    };
    static const char* extendType[] = {
        "cmp_task", "cmp_frame", "cmp_model", "cmp_light", "cmp_texture", "cmp_switch",
        "cmp_frame_motion", "cmp_pad", "cmp_player", "cmp_map", "cmp_enemy", "cmp_camera",
        "cmp_chara", "cmp_adpcm", "cmp_text", "cmp_fog", "cmp_menu", "cmp_blight",
        "cmp_radio", "cmp_item", "cmp_effect", "cmp_sound", "cmp_last",
    };
    if (type < 0) return "type_unknown";
    if (type <= 0x35) return commType[type];
    if (type >= 0x37 && type < 0x38) return extendType[type - 0x40];
    return "type_unknown";
}
static inline GSresID* findResource(Tiga* tiga, u32 group, u32 id) {
    for (s32 i = 0; i < tiga->resIdCount; i++) {
        GSresID* table = (GSresID*)tiga->resIdTable;
        GSresID* entry = &table[i];
        if (group == entry->group && id == entry->id) return &table[i];
    }
    return 0;
}
void tigaVariant::restoreStateData(GSBinReadStream* stream) {
    type = 1;
    value.integer = 0;
    type = stream->readU16();
    switch (type) {
    case 0x35: {
        u32 index = stream->readU32();
        if (index != 0) {
            value.integer = Tiga::m_cpCurrentObject->field944 + index * 4;
        } else {
            value.integer = index;
        }
        break;
    }
    case 1:
        value.integer = stream->readU32();
        break;
    case 2:
        value.single = stream->readFloat();
        break;
    case 7: {
        Tiga* tiga = Tiga::m_cpCurrentObject;
        s32 index = stream->readU32();
        s32 entry;
        if (index < 0 || index >= tiga->field968) {
            entry = 0;
        } else {
            entry = ((s32*)tiga->field96C)[index];
        }
        value.integer = entry;
        if (value.pointer == 0) {
            type = 1;
            value.integer = 0;
        }
        break;
    }
    case 4: {
        GSvec* vec = Tiga::m_cpCurrentObject->objManager.newVector();
        if (vec != 0) {
            vec->param1 = stream->readFloat();
            vec->param2 = stream->readFloat();
            vec->param3 = stream->readFloat();
            value.vector = vec;
        } else {
            stream->cur += 12;
        }
        break;
    }
    case 5:
        memcpy(value.pointer, stream->cur, 0x30);
        stream->cur += 0x30;
        break;
    case 0x23: {
        u32 group = stream->readU32();
        u32 id = stream->readU32();
        value.pointer = findResource(Tiga::m_cpCurrentObject, group, id);
        if (value.pointer == 0) {
            type = 1;
            value.integer = 0;
        }
        break;
    }
    case 3: {
        u16 length = stream->readU16();
        memcpy(_tempString, stream->cur, length);
        stream->cur += length;
        value.string = _tempString;
        if (type != 1 && type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
        break;
    }
    case 6:
        break;
    }
}
void tigaVariant::makeStateData(GSBinWriteStream* stream) {
    stream->writeU16(type);
    switch (type) {
    case 0x35: {
        u32 pointer = value.integer;
        if (pointer != 0) {
            stream->writeU32((pointer - Tiga::m_cpCurrentObject->field944) >> 2);
        } else {
            stream->writeU32(0);
        }
        break;
    }
    case 1:
        stream->writeU32(value.integer);
        break;
    case 2:
        stream->writeFloat(value.single);
        break;
    case 7:
        stream->writeU32(*(u16*)((u8*)value.pointer + 0xA));
        break;
    case 4:
        stream->writeFloat(value.vector->param1);
        stream->writeFloat(value.vector->param2);
        stream->writeFloat(value.vector->param3);
        break;
    case 5:
        stream->writeBytes(value.pointer, 0x30);
        break;
    case 0x23:
        stream->writeU32(((GSresID*)value.pointer)->group);
        stream->writeU32(((GSresID*)value.pointer)->id);
        break;
    case 3: {
        u32 length = strlen(value.string) + 1;
        stream->writeU16(length);
        stream->writeBytes(value.string, length);
        break;
    }
    case 6:
        break;
    }
}
void tigaVariant::setVectorIdx(int index, tigaVariant* source) {
    if (type == 0 || type == 1 || type == 2) {
        GSvec zero;
        zero.param1 = 0.0f; zero.param2 = 0.0f; zero.param3 = 0.0f;
        type = 4; flags = 0; value.vector = &zero;
        if (type != 1 && type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(this);
    }
    if (type != 4) { tigaErrMessage("vector set error"); return; }
    GSvec* vec = value.vector;
    if (vec == 0) { tigaErrMessage("vector error"); return; }
    if (index < 0 || index >= 4) { tigaErrMessage("vector index error"); return; }
    f32 element;
    if (source->type == 1) element = source->value.integer;
    else if (source->type == 2) element = source->value.single;
    else element = source->getCnvSingle();
    ((f32*)vec)[index] = element;
}
// Comparisons promote numeric operands; strings compare their lengths.
#define DEFINE_VARIANT_COMPARISON(name, operation, message) \
void tigaVariant::name(tigaVariant* result, tigaVariant* other) { \
    s32 common; \
    bool sameType = other->type == type; \
    result->type = 1; result->value.integer = 0; \
    s32 otherType = other->type; s32 thisType = type; common = otherType; if (thisType > common) common = thisType; \
    switch (common) { \
    case 1: { \
        s32 left; if (type == 1) left = value.integer; else if (type == 2) left = (s32)value.single; else left = getCnvInteger(); \
        s32 right; if (other->type == 1) right = other->value.integer; else if (other->type == 2) right = (s32)other->value.single; else right = other->getCnvInteger(); \
        if (left operation right) result->value.integer = 1; \
        break; \
    } \
    case 2: { \
        f32 left; if (type == 1) left = value.integer; else if (type == 2) left = value.single; else left = getCnvSingle(); \
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
// Vector comparison used by condNot/condEqu: component-wise absolute difference below an epsilon.
static inline bool vectorNearlyEqual(GSvec* a, GSvec* b) {
    GSvec diff;
    PSVECSubtract(a, b, &diff);
    diff.param1 = diff.param1 >= 0.0f ? diff.param1 : -diff.param1;
    diff.param2 = diff.param2 >= 0.0f ? diff.param2 : -diff.param2;
    diff.param3 = diff.param3 >= 0.0f ? diff.param3 : -diff.param3;
    if (diff.param1 < 0.00001f && diff.param1 > -0.00001f && diff.param2 < 0.00001f && diff.param2 > -0.00001f &&
        diff.param3 < 0.00001f && diff.param3 > -0.00001f) return true;
    return false;
}
#define DEFINE_VARIANT_EQUALITY(name, numeric, stringTest, vectorTest, message) \
void tigaVariant::name(tigaVariant* result, tigaVariant* other) { \
    s32 common; \
    bool sameType = other->type == type; \
    result->type = 1; result->value.integer = 0; \
    s32 thisType = type; s32 otherType = other->type; common = thisType > otherType ? thisType : otherType; \
    switch (common) { \
    case 1: { \
        s32 left; if (type == 1) left = value.integer; else if (type == 2) left = (s32)value.single; else left = getCnvInteger(); \
        s32 right; if (other->type == 1) right = other->value.integer; else if (other->type == 2) right = (s32)other->value.single; else right = other->getCnvInteger(); \
        if (left numeric right) result->value.integer = 1; \
        break; \
    } \
    case 2: { \
        f32 left; if (type == 1) left = value.integer; else if (type == 2) left = value.single; else left = getCnvSingle(); \
        f32 right; if (other->type == 1) right = other->value.integer; else if (other->type == 2) right = other->value.single; else right = other->getCnvSingle(); \
        if (left numeric right) result->value.integer = 1; \
        break; \
    } \
    case 3: \
        if (sameType && stringTest) result->value.integer = 1; \
        break; \
    case 4: { \
        GSvec* right = other->type == 4 ? other->value.vector : other->getCnvVector(); \
        GSvec* left = type == 4 ? value.vector : getCnvVector(); \
        if (vectorTest vectorNearlyEqual(left, right)) result->value.integer = 1; \
        break; \
    } \
    default: tigaErrMessage(message); break; \
    } \
}
DEFINE_VARIANT_EQUALITY(condNot, !=, strcmp(value.string, other->value.string) != 0, !, "not convert error")
DEFINE_VARIANT_EQUALITY(condEqu, ==, strcmpw(value.string, other->value.string) == 0, , "equ convert error")
#undef DEFINE_VARIANT_EQUALITY
static int strcmpw(const char* a, const char* b) {
    while (*a != 0 && *b != 0) {
        if (*a != *b && *a != '?' && *b != '?') {
            if (*a == '*' || *b == '*') return 0;
            return 1;
        }
        a++; b++;
    }
    if (*a == 0 && *b == 0) return 0;
    if (*a != 0) return 1;
    return -1;
}
// Result type of a binary operation: numeric types win over strings, anything unknown counts as a string.
// *scalar receives the operand that takes the scalar role when a vector or string is combined with a number
// and *primary the other one.
static inline s32 resultType(tigaVariant* left, tigaVariant* right, tigaVariant** scalar, tigaVariant** primary) {
    if (left->type == right->type) {
        *primary = left;
        *scalar = right;
        return left->type;
    }
    s32 x = 3;
    if (left->type < 0x40) x = left->type;
    s32 y = 3;
    if (right->type < 0x40) y = right->type;
    if (x == 3) x = 0x20;
    if (y == 3) y = 0x20;
    if (x > y) {
        *primary = left;
        *scalar = right;
        if (x == 0x20) return 3;
        return x;
    }
    *scalar = left;
    *primary = right;
    if (y == 0x20) y = 3;
    return y;
}
#define OPERAND_INTEGER(name, operand) \
    s32 name; \
    if ((operand)->type == 1) name = (operand)->value.integer; \
    else if ((operand)->type == 2) name = (s32)(operand)->value.single; \
    else name = (operand)->getCnvInteger();
#define OPERAND_SINGLE(name, operand) \
    f32 name; \
    if ((operand)->type == 1) name = (operand)->value.integer; \
    else if ((operand)->type == 2) name = (operand)->value.single; \
    else name = (operand)->getCnvSingle();
#define STORE_VECTOR_RESULT(vec) \
    result->value.vector = vec; \
    if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
// One vector component combined with a scalar operand.
#define VECTOR_SCALAR_COMPONENT(out, field, op, message) \
    f32 left##field; \
    if (type == 4) left##field = value.vector->field; else { tigaErrMessage(message); left##field = 0.0f; } \
    OPERAND_SINGLE(right##field, scalar) \
    out = left##field op right##field;
static inline s32 resultTypeAdd(tigaVariant* left, tigaVariant* right, tigaVariant** scalar) {
    if (left->type == right->type) {
        *scalar = right;
        return left->type;
    }
    s32 x = 3;
    if (left->type < 0x40) x = left->type;
    s32 y = 3;
    if (right->type < 0x40) y = right->type;
    if (x == 3) x = 0x20;
    if (y == 3) y = 0x20;
    s32 common;
    if (x > y) {
        *scalar = right;
        if (x == 0x20) common = 3;
        else common = x;
    } else {
        *scalar = left;
        if (y == 0x20) common = 3;
        else common = y;
    }
    return common;
}
void tigaVariant::mod(tigaVariant* result, tigaVariant* other) {
    tigaVariant* scalar;
    tigaVariant* primary;
    s32 common = resultType(this, other, &scalar, &primary);
    switch (common) {
    case 1:
    case 2: {
        s32 divisor;
        if (other->type == 1) divisor = other->value.integer;
        else if (other->type == 2) divisor = (s32)other->value.single;
        else divisor = other->getCnvInteger();
        if (divisor == 0) tigaErrMessage("integer mod 0");
        s32 dividend;
        if (type == 1) dividend = value.integer;
        else if (type == 2) dividend = (s32)value.single;
        else dividend = getCnvInteger();
        result->type = 1;
        result->value.integer = dividend % divisor;
        break;
    }
    default:
        tigaErrMessage("mod convert error");
        break;
    }
}
void tigaVariant::div(tigaVariant* result, tigaVariant* other) {
    bool sameType = other->type == type;
    tigaVariant* scalar;
    tigaVariant* primary;
    s32 common = resultType(this, other, &scalar, &primary);
    switch (common) {
    case 1: {
        result->type = 1;
        s32 divisor;
        if (other->type == 1) divisor = other->value.integer;
        else if (other->type == 2) divisor = (s32)other->value.single;
        else divisor = other->getCnvInteger();
        if (divisor == 0) {
            tigaErrMessage("integer div 0");
            result->value.integer = 0;
            return;
        }
        s32 dividend;
        if (type == 1) dividend = value.integer;
        else if (type == 2) dividend = (s32)value.single;
        else dividend = getCnvInteger();
        result->value.integer = dividend / divisor;
        break;
    }
    case 2: {
        result->type = 2;
        f32 divisor;
        if (other->type == 1) divisor = other->value.integer;
        else if (other->type == 2) divisor = other->value.single;
        else divisor = other->getCnvSingle();
        if (divisor == 0.0f) {
            tigaErrMessage("single div 0");
            result->value.single = 0.0f;
            return;
        }
        f32 dividend;
        if (type == 1) dividend = value.integer;
        else if (type == 2) dividend = value.single;
        else dividend = getCnvSingle();
        result->value.single = dividend / divisor;
        break;
    }
    case 4: {
        result->type = 4;
        GSvec quotient;
        if (sameType) {
            f32 left, right;
            if (type == 4) left = value.vector->param1; else { tigaErrMessage("vec.vx not access"); left = 0.0f; }
            if (other->type == 4) right = other->value.vector->param1; else { tigaErrMessage("vec.vx not access"); right = 0.0f; }
            quotient.param1 = left / right;
            if (type == 4) left = value.vector->param2; else { tigaErrMessage("vec.vy not access"); left = 0.0f; }
            if (other->type == 4) right = other->value.vector->param2; else { tigaErrMessage("vec.vy not access"); right = 0.0f; }
            quotient.param2 = left / right;
            if (type == 4) left = value.vector->param3; else { tigaErrMessage("vec.vz not access"); left = 0.0f; }
            if (other->type == 4) right = other->value.vector->param3; else { tigaErrMessage("vec.vz not access"); right = 0.0f; }
            quotient.param3 = left / right;
            result->value.vector = &quotient;
            if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
        } else {
            f32 divisor;
            if (scalar->type == 1) divisor = scalar->value.integer;
            else if (scalar->type == 2) divisor = scalar->value.single;
            else divisor = scalar->getCnvSingle();
            GSvec* source = value.vector;
            if (divisor != 0.0f) PSVECScale(source, &quotient, 1.0f / divisor);
            result->value.vector = &quotient;
            if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
        }
        break;
    }
    default:
        tigaErrMessage("div convert error");
        break;
    }
}
void tigaVariant::mul(tigaVariant* result, tigaVariant* other) {
    bool sameType = other->type == type;
    tigaVariant* scalar;
    tigaVariant* primary;
    s32 common = resultType(this, other, &scalar, &primary);
    switch (common) {
    case 1: {
        result->type = 1;
        OPERAND_INTEGER(left, this)
        OPERAND_INTEGER(right, other)
        result->value.integer = left * right;
        break;
    }
    case 2: {
        result->type = 2;
        OPERAND_SINGLE(left, this)
        OPERAND_SINGLE(right, other)
        result->value.single = left * right;
        break;
    }
    case 3: {
        static char szDest[0x400];
        char buffer[0x100];
        szDest[0] = 0;
        char* text;
        if (primary->type == 3) text = primary->value.string; else text = primary->getCnvString(buffer);
        OPERAND_INTEGER(count, scalar)
        if ((u32)(count * strlen(text)) > 0xFA) {
            result->type = 3;
            result->value.string = "null";
            if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
        } else {
            for (s32 i = 0; i < count; i++) strcat(szDest, text);
            result->type = 3;
            result->value.string = szDest;
            if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
        }
        break;
    }
    case 4: {
        result->type = 4;
        GSvec product;
        if (sameType) {
            GSvec* right = other->value.vector;
            product.param1 = value.vector->param1 * right->param1;
            product.param2 = value.vector->param2 * right->param2;
            product.param3 = value.vector->param3 * right->param3;
            STORE_VECTOR_RESULT(&product)
        } else {
            VECTOR_SCALAR_COMPONENT(product.param1, param1, *, "vec.vx not access")
            VECTOR_SCALAR_COMPONENT(product.param2, param2, *, "vec.vy not access")
            VECTOR_SCALAR_COMPONENT(product.param3, param3, *, "vec.vz not access")
            STORE_VECTOR_RESULT(&product)
        }
        break;
    }
    default:
        tigaErrMessage("mul convert error");
        break;
    }
}
void tigaVariant::sub(tigaVariant* result, tigaVariant* other) {
    bool sameType = other->type == type;
    tigaVariant* scalar;
    tigaVariant* primary;
    s32 common = resultType(this, other, &scalar, &primary);
    switch (common) {
    case 1: {
        result->type = 1;
        OPERAND_INTEGER(left, this)
        OPERAND_INTEGER(right, other)
        result->value.integer = left - right;
        break;
    }
    case 2: {
        result->type = 2;
        OPERAND_SINGLE(left, this)
        OPERAND_SINGLE(right, other)
        result->value.single = left - right;
        break;
    }
    case 4: {
        result->type = 4;
        GSvec difference;
        if (sameType) {
            PSVECSubtract(value.vector, other->value.vector, &difference);
            STORE_VECTOR_RESULT(&difference)
        } else {
            VECTOR_SCALAR_COMPONENT(difference.param1, param1, -, "vec.vx not access")
            VECTOR_SCALAR_COMPONENT(difference.param2, param2, -, "vec.vy not access")
            VECTOR_SCALAR_COMPONENT(difference.param3, param3, -, "vec.vz not access")
            STORE_VECTOR_RESULT(&difference)
        }
        break;
    }
    default:
        tigaErrMessage("sub convert error");
        result->type = 1;
        result->value.integer = 0;
        break;
    }
}
void tigaVariant::add(tigaVariant* result, tigaVariant* other) {
    bool sameType = other->type == type;
    tigaVariant* scalar;
    s32 common = resultTypeAdd(this, other, &scalar);
    switch (common) {
    case 1: {
        result->type = 1;
        OPERAND_INTEGER(left, this)
        OPERAND_INTEGER(right, other)
        result->value.integer = left + right;
        break;
    }
    case 2: {
        result->type = 2;
        OPERAND_SINGLE(left, this)
        OPERAND_SINGLE(right, other)
        result->value.single = left + right;
        break;
    }
    case 3: {
        static char szDest[0x100];
        char buffer[0x100];
        char* text;
        if (type == 3) text = value.string; else text = getCnvString(buffer);
        strcpy(szDest, text);
        if (other->type == 3) text = other->value.string; else text = other->getCnvString(buffer);
        strcat(szDest, text);
        result->type = 3;
        result->value.string = szDest;
        if (result->type != 1 && result->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(result);
        break;
    }
    case 4: {
        result->type = 4;
        GSvec sum;
        if (sameType) {
            PSVECAdd(value.vector, other->value.vector, &sum);
            STORE_VECTOR_RESULT(&sum)
        } else {
            VECTOR_SCALAR_COMPONENT(sum.param1, param1, +, "vec.vx not access")
            VECTOR_SCALAR_COMPONENT(sum.param2, param2, +, "vec.vy not access")
            VECTOR_SCALAR_COMPONENT(sum.param3, param3, +, "vec.vz not access")
            STORE_VECTOR_RESULT(&sum)
        }
        break;
    }
    default:
        tigaErrMessage("add convert error");
        break;
    }
}
char* tigaVariant::getCnvString(char* destination) {
    if (type == 1) { ::sprintf(destination, "%d", value.integer); return destination; }
    if (type == 2) { ::sprintf(destination, "%.3f", value.single); return destination; }
    if (type == 4) { ::sprintf(destination, "<%.3f,%.3f,%.3f>", value.vector->param1, value.vector->param2, value.vector->param3); return destination; }
    tigaErrMessage("string convert error"); destination[0] = 0; return destination;
}

GSvec* tigaVariant::getCnvVector() {
    static GSvec vTemp;
    if (type == 4) return value.vector;
    f32 scalar;
    if (type == 1) scalar = value.integer;
    else if (type == 2) scalar = value.single;
    else scalar = getCnvSingle();
    // The original writes x twice and leaves z unchanged.
    vTemp.param1 = scalar; vTemp.param2 = scalar; vTemp.param1 = scalar;
    return &vTemp;
}
f32 tigaVariant::getCnvSingle() {
    if (type == 3) return atof(value.string);
    tigaErrMessage("single convert error"); return 0.0f;
}
s32 tigaVariant::getCnvInteger() {
    if (type == 3) return atoi(value.string);
    tigaErrMessage("integer convert error"); return 0;
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
void tigaArrayFixed::set(int index, const tigaVariant* source) {
    if (index < 0 || index >= count) return;
    values[index].type = source->type; values[index].flags = source->flags; values[index].value.integer = source->value.integer;
}
tigaVariant* tigaArrayFixed::get(int index) {
    if (index < 0 || index >= count) { _dummyValue.type = 1; _dummyValue.value.integer = 0; return &_dummyValue; }
    return &values[index];
}
void tigaCellMemory::freeVariant(tigaVariant* v) {
    if (v->type == 3) {
        void** slot = checkAllocedMemory(&l_stringPool, v->value.string);
        if (slot) {
            *slot = 0;
        } else {
            v->value.pointer = 0; v->type = 0;
            return;
        }
        if (v->value.string) {
            cellA--;
            GSmemFree(v->value.string);
        }
        v->value.pointer = 0; v->type = 0;
    } else if (v->type != 7 && v->type == 4) {
        Tiga::m_cpCurrentObject->objManager.deleteVector(v->value.vector);
        v->value.pointer = 0; v->type = 0;
    }
}
void tigaCellMemory::dupVariant(tigaVariant* v) {
    if (v->type == 3) {
        cellA++;
        char* copy = (char*)GSmemAlloc(0x100);
        strncpy(copy, v->value.string, 0xFF);
        v->value.string = copy;
        *varPoolSearchFree(&l_stringPool) = copy;
    } else if (v->type != 7 && v->type == 4) {
        GSvec* vec = Tiga::m_cpCurrentObject->objManager.newVector();
        if (vec) {
            GSvec* src = v->value.vector;
            vec->param1 = src->param1; vec->param2 = src->param2; vec->param3 = src->param3;
            v->value.vector = vec;
        }
    }
}
tigaCellMemory::~tigaCellMemory() {
    if (cellA != 0 || cellB != 0) {
        if (cellA != 0) {
            for (int i = 0; i < 0x100; i++) {
                if (l_stringPool.slot[i]) {
                    if (l_stringPool.slot[i]) { GSmemFree(l_stringPool.slot[i]); l_stringPool.slot[i] = 0; }
                }
            }
        }
    }
}
tigaCellMemory::tigaCellMemory() {
    nullVec.param1 = 0.0f; nullVec.param2 = 0.0f; nullVec.param3 = 0.0f;
    cellA = 0; cellB = 0;
    memset(&l_stringPool, 0, 0x400);
    memset(&l_vectorPool, 0, 0x400);
}
static void** checkAllocedMemory(varPool_t* pool, void* ptr) {
    for (int i = 0; i < 0x100; i++) {
        if (pool->slot[i] == ptr) return &pool->slot[i];
    }
    return 0;
}
static void** varPoolSearchFree(varPool_t* pool) {
    for (int i = 0; i < 0x100; i++) {
        if (pool->slot[i] == 0) return &pool->slot[i];
    }
    return 0;
}
}
