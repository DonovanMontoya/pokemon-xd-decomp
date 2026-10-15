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

extern "C" {
int sprintf(char*, const char*, ...);
double acos(double);
void PSVECNormalize(const GSvec*, GSvec*);
void PSVECCrossProduct(const GSvec*, const GSvec*, GSvec*);
f32 PSVECDotProduct(const GSvec*, const GSvec*);
f32 PSVECMag(const GSvec*);
f32 PSVECSquareMag(const GSvec*);
}

namespace GSscript {

struct TigaWorkFull : TigaWorkPrefix {
    GSvec vec;
};
#define WORKVEC(self) (((TigaWorkFull*)(self)->workBuffer)->vec)

static inline s32 expressionInteger(tigaVariant* value) {
    if (value->type == 1) return value->value.integer;
    if (value->type == 2) return (s32)value->value.single;
    return value->getCnvInteger();
}
static inline f32 expressionSingle(tigaVariant* value) {
    if (value->type == 1) return (f32)value->value.integer;
    if (value->type == 2) return value->value.single;
    return value->getCnvSingle();
}
static inline void expressionSetInteger(tigaVariant* result, s32 value) {
    result->type = 1;
    result->value.integer = value;
}
static inline bool vectorIsZero(GSvec* v) {
    if (v->param1 < 0.00001f && v->param1 > -0.00001f && v->param2 < 0.00001f && v->param2 > -0.00001f &&
        v->param3 < 0.00001f && v->param3 > -0.00001f) {
        return true;
    }
    return false;
}
static inline f32 absSingle(f32 x) {
    if (x >= 0.0f) return x;
    return -x;
}
static inline void expressionSetSingle(tigaVariant* result, f32 value) {
    result->type = 2;
    result->value.single = value;
}
static inline GSvec* expressionVector(tigaVariant* value) {
    if (value->type == 4) return value->value.vector;
    return value->getCnvVector();
}
static inline void releaseVariant(tigaVariant* value) {
    if (value->type == 1 || value->type == 2) {
        value->type = 0;
    } else {
        Tiga::m_cpCurrentObject->cellMemory->freeVariant(value);
        value->type = 0;
    }
}
static inline void returnString(Tiga* self, const char* text) {
    strncpy(self->workBuffer->string, text, 255);
    self->workBuffer->result.value.string = self->workBuffer->string;
    self->workBuffer->result.type = 3;
}
static inline void returnVariant(Tiga* self, tigaVariant* source, tigaVariant* result) {
    if (source->type == 3) {
        returnString(self, source->value.string);
    } else if (source->type == 4) {
        GSvec* from = source->value.vector;
        TigaWorkFull* work = (TigaWorkFull*)self->workBuffer;
        work->vec.param1 = from->param1;
        work->vec.param2 = from->param2;
        work->vec.param3 = from->param3;
        self->workBuffer->result.value.vector = &WORKVEC(self);
        self->workBuffer->result.type = 4;
    } else {
        result->type = source->type;
        result->flags = source->flags;
        result->value.integer = source->value.integer;
    }
}

int Tiga::cmpArray(int operation, tigaVariant* args, tigaVariant* result) {
    char buffer[256];
    tigaArrayFixed* array = 0;
    if (operation != 1) {
        s16 type = args->type;
        array = (tigaArrayFixed*)args->value.pointer;
        if (type != 7 || array == 0) return 0;
    }
    switch (operation) {
    case 0:
        break;
    case 3:
        sprintf(buffer, "tarray: size=%d", array->count);
        returnString(this, buffer);
        break;
    case 0x10: {
        s32 size = array->count;
        s32 index = expressionInteger(&args[1]);
        if (index >= size) {
            result->type = 1;
            result->value.integer = 0;
            break;
        }
        returnVariant(this, array->get(index), result);
        break;
    }
    case 0x11: {
        s32 index = expressionInteger(&args[1]);
        array->set(index, &args[2]);
        break;
    }
    case 0x12:
        expressionSetInteger(result, ((tigaArrayFixed*)args->value.pointer)->count);
        break;
    case 0x13: {
        s32 size = expressionInteger(&args[1]);
        array->resize(size);
        break;
    }
    case 0x19: {
        s32 count = expressionInteger(&args[1]);
        tigaVariant* p = args;
        for (s32 i = 0; i < count; p++, i++) {
            array->push_back(p + 2);
        }
        break;
    }
    case 0x14:
        array->push_back(&args[1]);
        break;
    case 0x16:
        array->cursor = 0;
        break;
    case 0x17:
        returnVariant(this, array->fe_get(), result);
        break;
    case 0x18:
        result->type = 1;
        if (array->count <= (s32)array->cursor) {
            result->value.integer = 1;
        } else {
            result->value.integer = 0;
        }
        break;
    case 0x1a:
        break;
    }
    return 0;
}

int Tiga::cmpVector(int operation, tigaVariant* args, tigaVariant* result) {
    char buffer[256];
    GSvec temp;
    GSvec normA;
    GSvec normB;
    temp.param1 = 0.0f;
    temp.param2 = 0.0f;
    temp.param3 = 0.0f;
    GSvec* vec = 0;
    if (operation != 1) {
        if (args->type != 4) {
            releaseVariant(args);
            args->type = 4;
            args->flags = 0;
            args->value.vector = &temp;
            if (args->type != 1 && args->type != 2) Tiga::m_cpCurrentObject->cellMemory->dupVariant(args);
        }
        vec = args->value.vector;
    }
    switch (operation) {
    case 3:
        sprintf(buffer, "<%.3f,%.3f,%.3f>", vec->param1, vec->param2, vec->param3);
        returnString(this, buffer);
        break;
    case 0x10:
        vec->param3 = 0.0f;
        vec->param2 = 0.0f;
        vec->param1 = 0.0f;
        break;
    case 0x11:
        PSVECNormalize(vec, vec);
        break;
    case 0x12:
        vec->param1 = expressionSingle(&args[1]);
        vec->param2 = expressionSingle(&args[2]);
        vec->param3 = expressionSingle(&args[3]);
        break;
    case 0x13:
        vec->param1 = expressionSingle(&args[1]);
        vec->param2 = expressionSingle(&args[2]);
        vec->param3 = expressionSingle(&args[3]);
        break;
    case 0x14: {
        f32 value = expressionSingle(&args[1]);
        vec->param3 = value;
        vec->param2 = value;
        vec->param1 = value;
        break;
    }
    case 0x15:
        vec->param1 = absSingle(vec->param1);
        vec->param2 = absSingle(vec->param2);
        vec->param3 = absSingle(vec->param3);
        break;
    case 0x16:
        vec->param1 = -vec->param1;
        vec->param2 = -vec->param2;
        vec->param3 = -vec->param3;
        break;
    case 0x17: {
        bool zero = vectorIsZero(vec);
        if (zero) {
            result->type = 1;
            result->value.integer = 1;
        } else {
            result->type = 1;
            result->value.integer = 0;
        }
        break;
    }
    case 0x18:
        if (args[1].type == 4) {
            PSVECCrossProduct(vec, expressionVector(&args[1]), &temp);
            TigaWorkFull* work = (TigaWorkFull*)workBuffer;
            work->vec.param1 = temp.param1;
            work->vec.param2 = temp.param2;
            work->vec.param3 = temp.param3;
            workBuffer->result.value.vector = &WORKVEC(this);
            workBuffer->result.type = 4;
        }
        break;
    case 0x19:
        if (args[1].type == 4) {
            expressionSetSingle(result, PSVECDotProduct(vec, expressionVector(&args[1])));
        } else {
            result->type = 2;
            result->value.single = 0.0f;
        }
        break;
    case 0x1a:
        expressionSetSingle(result, PSVECMag(vec));
        break;
    case 0x1b:
        expressionSetSingle(result, PSVECSquareMag(vec));
        break;
    case 0x1c:
        if (args[1].type == 4) {
            PSVECNormalize(vec, &normA);
            PSVECNormalize(expressionVector(&args[1]), &normB);
            f32 degrees = 57.29578f * (f32)acos(PSVECDotProduct(&normA, &normB));
            while (degrees > 360.0f) degrees -= 360.0f;
            while (degrees < 0.0f) degrees += 360.0f;
            result->type = 2;
            result->value.single = degrees;
        } else {
            result->type = 2;
            result->value.single = 0.0f;
        }
        break;
    }
    return 0;
}

int Tiga::cmpThread(int operation, tigaVariant* args, tigaVariant* result) {
    s32 spawnArg = 0;
    s32 handle;
    int wait = 0;
    switch (operation) {
    case 0x10: {
        s32 index = expressionInteger(&args[1]);
        if (makeThread((TPCCode*)(field944 + index * 4), (int&)spawnArg, (long&)handle)) {
            expressionSetInteger(result, handle);
        }
        break;
    }
    case 0x11:
        result->type = 1;
        result->value.integer = 0;
        break;
    case 0x12:
        expressionSetInteger(result, threadCount);
        break;
    case 0x13:
        deleteThread(expressionInteger(&args[1]));
        break;
    case 0x14: {
        u8 value = expressionInteger(&args[2]);
        s32 index = expressionInteger(&args[1]);
        if (isFlagIndex(index)) flags[index] = value;
        break;
    }
    case 0x15: {
        s32 index = expressionInteger(&args[1]);
        expressionSetInteger(result, getFlag(index));
        break;
    }
    case 0x16: {
        if (isFlagIndex(expressionInteger(&args[1]))) {
            s32 value = expressionInteger(&args[2]);
            s32 index = expressionInteger(&args[1]);
            TigaThread* thread = currentThread;
            thread->waitMode = 1;
            thread->flagIndex = index;
            thread->flagValue = value;
            wait = 1;
        }
        break;
    }
    case 0x17: {
        if (isFlagIndex(expressionInteger(&args[1]))) {
            s32 value = expressionInteger(&args[2]);
            s32 index = expressionInteger(&args[1]);
            TigaThread* thread = currentThread;
            thread->waitMode = 2;
            thread->flagIndex = index;
            thread->flagValue = value;
            wait = 1;
        }
        break;
    }
    case 0x18:
        break;
    }
    return wait;
}

}  // namespace GSscript
