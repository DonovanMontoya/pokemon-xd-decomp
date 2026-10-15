#ifndef GS_SCRIPT_VARIANT_HPP
#define GS_SCRIPT_VARIANT_HPP
#include <game/pxdvs/GSAPI/GSmath/GSvec.hpp>
struct GSBinReadStream;
struct GSBinWriteStream;
namespace GSscript {
struct tigaVariant {
    s16 type, flags;
    union { s32 integer; f32 single; char* string; GSvec* vector; void* pointer; } value;
    s32 getCnvInteger();
    f32 getCnvSingle();
    char* getCnvString(char*);
    GSvec* getCnvVector();
    static const char* getTypeString(int);
    void restoreStateData(GSBinReadStream*);
    void makeStateData(GSBinWriteStream*);
    void setVectorIdx(int, tigaVariant*);
    void condLe(tigaVariant*, tigaVariant*);
    void condLs(tigaVariant*, tigaVariant*);
    void condGe(tigaVariant*, tigaVariant*);
    void condGt(tigaVariant*, tigaVariant*);
    void condNot(tigaVariant*, tigaVariant*);
    void condEqu(tigaVariant*, tigaVariant*);
    void mod(tigaVariant*, tigaVariant*);
    void div(tigaVariant*, tigaVariant*);
    void mul(tigaVariant*, tigaVariant*);
    void sub(tigaVariant*, tigaVariant*);
    void add(tigaVariant*, tigaVariant*);
};
struct tigaArrayFixed {
    s32 count; u32 cursor; u8 isDynamic; u8 pad09[3]; u32 reserved0C;
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
