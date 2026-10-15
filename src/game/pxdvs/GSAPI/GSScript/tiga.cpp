#include <game/pxdvs/GSAPI/GSScript/tiga.hpp>
#include <libc/string.h>

extern "C" {
void* floorCreateThreadLocal(int, int, int, void (*)(GSscript::Tiga*, long));
void GSthreadSetName(void*, const char*);
void GSthreadSetArgs(void*, int, ...);
}

#pragma auto_inline off
namespace GSscript {

// Makes a script the current one for the duration of a scope.
struct TigaCurrentScope {
    Tiga* previous;
    TigaCurrentScope(Tiga* tiga) {
        previous = Tiga::m_cpCurrentObject;
        Tiga::m_cpCurrentObject = tiga;
    }
    ~TigaCurrentScope() { Tiga::m_cpCurrentObject = previous; }
};



int Tiga::getStateSize() {
    GSBinWriteSizeStream stream;
    makeStateData(&stream);
    return stream.getWriteSize();
}

void Tiga::makeStateData(GSBinWriteStream* stream) {
    int i;
    stream->writeU32(0);
    stream->writeU32(field8D8);
    stream->writeU32(chunk.blockA);
    stream->writeU32(chunk.chankD);
    stream->writeU32(threadCount);
    for (i = 0; i < 4; i++) {
        stream->writeFloat(timers[i]);
    }
    for (i = 0; i < 16; i++) {
        stream->writeU8(flags[i]);
    }
    stream->writeU32(nextHandle);
    stream->writeBool(hitFlag);
    stream->writeU32(field930);
    stream->writeU32(globalCount);
    for (i = 0; i < globalCount; i++) {
        globals[i].makeStateData(stream);
    }
    stream->writeU32(field968);
    for (i = 0; i < field968; i++) {
        stream->writeBool(((tigaArrayFixed**)field96C)[i]->isDynamic);
        if (((tigaArrayFixed**)field96C)[i]->isDynamic == 0) {
            stream->writeU32(((tigaArrayFixed**)field96C)[i]->count);
            for (int j = 0; j < ((tigaArrayFixed**)field96C)[i]->count; j++) {
                ((tigaArrayFixed**)field96C)[i]->get(j)->makeStateData(stream);
            }
        }
    }
    stream->writeU32(8);
    for (i = 0; i < 8; i++) {
        threads[i]->makeStateData(stream);
    }
}

bool Tiga::restoreStateData(void* data, unsigned long size) {
    GSBinReadStream stream(data, size);
    TigaCurrentScope scope(this);
    int i;
    if (size == 0) {
        return false;
    }
    if (stream.readU32() != 0) {
        return false;
    }
    field8D8 = stream.readU32();
    u32 blockA = stream.readU32();
    if (blockA != chunk.blockA && (blockA != 0 || chunk.blockA != 0)) {
        return false;
    }
    u32 chankD = stream.readU32();
    if (chankD != chunk.chankD) {
        return false;
    }
    threadCount = stream.readU32();
    for (i = 0; i < 4; i++) {
        timers[i] = stream.readFloat();
    }
    for (i = 0; i < 16; i++) {
        flags[i] = stream.readU8();
    }
    nextHandle = stream.readU32();
    hitFlag = stream.readBool();
    field930 = stream.readU32();
    globalCount = stream.readU32();
    for (i = 0; i < globalCount; i++) {
        globals[i].restoreStateData(&stream);
    }
    field968 = stream.readU32();
    for (i = 0; i < field968; i++) {
        stream.readU8();
        if (((tigaArrayFixed**)field96C)[i]->isDynamic == 0) {
            stream.readU32();
            for (int j = 0; j < ((tigaArrayFixed**)field96C)[i]->count; j++) {
                ((tigaArrayFixed**)field96C)[i]->get(j)->restoreStateData(&stream);
            }
        }
    }
    s32 count = 8;
    s32 saved = stream.readU32();
    if (saved < 8) {
        count = saved;
    }
    for (i = 0; i < count; i++) {
        threads[i]->initTiga();
        threads[i]->restoreStateData(&stream);
        if (threads[i]->state != 0) {
            threads[i]->handle = nextHandle++;
            threads[i]->group = floorGetCurrentFloorGroupID();
            if (nextHandle == 0) {
                nextHandle = 1;
            }
        }
    }
    for (i = 0; i < count; i++) {
        if (threads[i]->state != 0) {
            s32 handle = threads[i]->handle;
            void* thread = floorCreateThreadLocal(1, 0x2000, 1, _executeScriptThread);
            GSthreadSetName(thread, "GSscript thread");
            GSthreadSetArgs(thread, 2, this, handle);
            threads[i]->thread = thread;
        }
    }
    return true;
}

int Tiga::getNameToFuncId(const char* name) {
    int index = 0;
    if (funcCount == 0) {
        return 0;
    }
    for (u32* p = codeTable; p != codeTable + codeCount * 2; p += 2, index++) {
        if (strcmp((const char*)p[1], name) == 0) {
            return index | 0x01000000;
        }
    }
    return 0;
}

int Tiga::getResultValue(long) {
    tigaVariant* v = resultVar;
    if (v != 0 && (v->type == 1 || v->type == 2)) {
        if (v->type == 1) {
            return v->value.integer;
        }
        if (v->type == 2) {
            return (int)v->value.single;
        }
        return v->getCnvInteger();
    }
    return 0;
}

void* Tiga::getIdToCodeAdress(int id) {
    u16 index = id;
    if ((int)index < 0 || (int)index > codeCount) {
        return 0;
    }
    return (void*)codeTable[index * 2];
}

u32* Tiga::searchResID(unsigned long a, unsigned long b) {
    u32* p = resIdTable;
    u32* end = resIdTable + resIdCount * 2;
    for (; p != end; p += 2) {
        if (p[0] == a && p[1] == b) {
            return p;
        }
    }
    return 0;
}

int Tiga::setPresetVar(tigaVariant* var, int a, int b) {
    return setExtendVariable(var, a, b);
}

void Tiga::getPresetVar(tigaVariant* var, int a, int b) {
    var->type = 0;
    switch (a) {
    case 5:
        var->type = 1;
        var->value.integer = currentThread ? currentThread->handle : 0;
        break;
    default:
        getExtendVariable(var, a, b);
        break;
    }
}

int Tiga::executeOneThread(float dt, long id) {
    TigaThread* prevThread;
    TigaThread* t = getHandleToThread(id);
    if (t == 0) {
        return 0;
    }
    Tiga* prev = m_cpCurrentObject;
    m_cpCurrentObject = this;
    hitFlag = 0;
    if (t->state == 0) {
        return 0;
    }
    if (t->state & 2) {
        return 1;
    }
    prevThread = currentThread;
    currentThread = t;
    if (t->sleepTime > 0.0f) {
        t->sleepTime -= dt;
    }
    if (t->checkSleepEnd()) {
        if (t->sleepTime <= 0.0f) {
            execute(t);
        }
    }
    currentThread = prevThread;
    m_cpCurrentObject = prev;
    return 1;
}

int Tiga::executeThread(float dt) {
    Tiga* prev = m_cpCurrentObject;
    m_cpCurrentObject = this;
    hitFlag = 0;
    for (f32* p = timers; p < (f32*)threads; p++) {
        *p += dt;
    }
    m_cpCurrentObject = prev;
    return 0;
}

void Tiga::unblockThread(long id) {
    TigaThread* t = getHandleToThread(id);
    if (t != 0) {
        t->state &= ~2;
    }
}


void Tiga::blockThread(long id) {
    TigaThread* t = getHandleToThread(id);
    if (t != 0 && t->state != 0) {
        t->state |= 2;
    }
}


void Tiga::unblockThreadGroup(unsigned long group) {
    TigaThread** end;
    TigaThread** p = threads;
    end = threads + 8;
    for (; p < end; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) {
            unblockThread(t->handle);
        }
    }
}

void Tiga::blockThreadGroup(unsigned long group) {
    TigaThread** end;
    TigaThread** p = threads;
    end = threads + 8;
    for (; p < end; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) {
            blockThread(t->handle);
        }
    }
}

void Tiga::deleteThreadGroup(unsigned long group) {
    TigaThread** end;
    TigaThread** p = threads;
    end = threads + 8;
    for (; p < end; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && group == t->group) {
            deleteThread(t->handle);
        }
    }
}

bool Tiga::isRunningThread(long id) {
    TigaThread* t = getHandleToThread(id);
    if (t != 0) {
        return t->state != 0;
    }
    return false;
}

void Tiga::deleteThread(long id) {
    TigaThread* t = getHandleToThread(id);
    if (t != 0) {
        t->stop();
        threadCount--;
    }
}

TigaThread* Tiga::getHandleToThread(long id) {
    TigaThread** end = (TigaThread**)&cellMemory;
    TigaThread** p = threads;
    for (; p < end; p++) {
        TigaThread* t = *p;
        if (t->state != 0 && id == t->handle) {
            return t;
        }
    }
    return 0;
}

bool Tiga::makeThread(TPCCode* code, int& index, long& handle) {
    int i = 0;
    TigaThread** p = threads;
    for (; p < (TigaThread**)&cellMemory; p++, i++) {
        if ((*p)->state == 0) {
            (*p)->initTiga();
            handle = nextHandle;
            (*p)->handle = nextHandle;
            (*p)->group = floorGetCurrentFloorGroupID();
            TigaThread* t = *p;
            t->code = code;
            t->state = 1;
            t->sleepTime = 0.0f;
            threadCount++;
            index = i;
            nextHandle++;
            if (nextHandle == 0) {
                nextHandle = 1;
            }
            return true;
        }
    }
    return false;
}

int Tiga::runParamsWait(int id, tigaVariant* params, int count, tigaVariant* result) {
    long handle = runParams(id, params, count, false);
    if (handle == 0) {
        return 0;
    }
    while (isRunningThread(handle)) {
        executeOneThread(timeGetLastFrameSec(), handle);
        if (!isRunningThread(handle)) {
            break;
        }
        GSthreadSwitch();
    }
    if (result != 0) {
        tigaVariant* v = resultVar;
        result->type = v->type;
        result->flags = v->flags;
        result->value.integer = v->value.integer;
    }
    return 1;
}

long Tiga::runParamsPC(TPCCode* code, tigaVariant* params, int count, bool threaded) {
    TigaThread* previous = currentThread;
    int index;
    long handle;
    if (makeThread(code, index, handle) != 0) {
        int i;
        currentThread = threads[index];
        TigaThread* thread = threads[index];
        tigaVariant* stack = thread->stackPtr10;
        for (i = 0; i < count; i++) {
            stack--;
            tigaVariant* source = &params[count - i];
            source--;
            stack->type = source->type;
            stack->flags = source->flags;
            stack->value.integer = source->value.integer;
            stack->flags = 0;
        }
        stack--;
        stack->type = 0x35;
        stack->flags = 0;
        stack->value.integer = 0;
        thread->stackPtr10 = stack;
        thread->stackPtr14--;
        *thread->stackPtr14 = (s32)thread->stackPtr0C;
        thread->stackPtr0C = stack;
        if (threaded) {
            void* created = floorCreateThreadLocal(1, 0x2000, 1, _executeScriptThread);
            GSthreadSetName(created, "GSscript thread");
            GSthreadSetArgs(created, 2, this, handle);
            thread->thread = created;
        } else {
            execute(thread);
        }
        currentThread = previous;
        return thread->handle;
    }
    currentThread = previous;
    return 0;
}

long Tiga::runParams(int id, tigaVariant* params, int count, bool flag) {
    if (funcCount == 0) {
        return 0;
    }
    if ((id >> 16) == 0) {
        return 0;
    }
    int index = (u16)id;
    if (index >= funcCount || index < 0) {
        return 0;
    }
    TPCCode* code = (TPCCode*)getIdToCodeAdress(index);
    return runParamsPC(code, params, count, flag);
}

void Tiga::mappingScript(char* data) {
    field934 = 0;
    for (f32* p = timers; p < (f32*)threads; p++) {
        *p = 0.0f;
    }
    chunk.loadFromMemory(data, 0);
    setTpcChank(&chunk);
}

int Tiga::execExtendMethod(int, int, tigaVariant*, tigaVariant*) { return 0; }
int Tiga::execExtendGlobalFunction(int, tigaVariant*, tigaVariant*) { return 0; }
int Tiga::getExtendVariable(tigaVariant*, int, int) { return 0; }
int Tiga::setExtendVariable(tigaVariant*, int, int) { return 0; }

void Tiga::unmappingScript() {
    funcCount = 0;
    field940 = 0;
    field944 = 0;
    globalCount = 0;
    globals = 0;
    field950 = 0;
    field954 = 0;
    field958 = 0;
    field95C = 0;
    resIdCount = 0;
    resIdTable = 0;
    codeCount = 0;
    codeTable = 0;
    chunk.loadFromMemory(0, 0);
    resultVar = 0;
    unmapping();
    objManager.clear();
}

void Tiga::free() {
    tigaVariant* v;
    int i;
    m_cpCurrentObject = this;
    for (i = 0; i < globalCount; i++) {
        v = &globals[i];
        if (v->type == 1 || v->type == 2) {
            v->type = 0;
        } else {
            m_cpCurrentObject->cellMemory->freeVariant(v);
            v->type = 0;
        }
    }
    for (i = 0; i < 8; i++) {
        delete threads[i];
    }
    resultVar = 0;
}

Tiga::~Tiga() {
    free();
    delete cellMemory;
}

Tiga::Tiga() {
    if (m_cpCurrentObject == 0) {
        m_cpCurrentObject = this;
    }
    funcCount = 0;
    globalCount = 0;
    field930 = 0;
    currentThread = 0;
    field978 = 0x200;
    field97C = 0;
    nextHandle = 1;
    cellMemory = new tigaCellMemory;
    for (int i = 0; i < 8; i++) {
        threads[i] = new TigaThread;
        threads[i]->owner = this;
    }
    for (f32* p = timers; p < (f32*)threads; p++) {
        *p = 0.0f;
    }
    memset(flags, 0, 16);
    field934 = 0;
    resultVar = 0;
}

void TigaThread::setSaveFlag(bool enable) {
    if (state != 0) {
        if (enable) {
            state &= ~0x10;
        } else {
            state |= 0x10;
        }
    }
}

void TigaThread::stop() {
    state = 0;
    if (thread != 0) {
        GSthreadTerminate(thread);
        thread = 0;
    }
}

bool TigaThread::restoreStateData(GSBinReadStream* stream) {
    int i;
    s32 codeBase = owner->field944;
    state = stream->readU32();
    sleepTime = stream->readFloat();
    u32 codeOffset = stream->readU32();
    u32 offset0C = stream->readU32();
    u32 offset10 = stream->readU32();
    u32 offset14 = stream->readU32();
    code = (TPCCode*)(codeBase + codeOffset * 4);
    stackPtr0C = stackBase38 + offset0C;
    stackPtr10 = stackBase38 + offset10;
    stackPtr14 = stackBase3C + offset14;
    for (i = 0; i < 4; i++) {
        (&retVar)[i].restoreStateData(stream);
    }
    field14C = stream->readU32();
    stackCount = stream->readU32();
    for (i = 0; i < stackCount; i++) {
        stackArea[i].restoreStateData(stream);
    }
    stackCount2 = stream->readU32();
    for (i = 0; i < stackCount2; i++) {
        ((tigaVariant**)stackArea2)[i] = stackBase38 + stream->readU32();
    }
    timerIndex = stream->readU8();
    timerLimit = stream->readFloat();
    waitMode = stream->readU8();
    flagIndex = stream->readU8();
    flagValue = stream->readU32();
    return true;
}

void TigaThread::makeStateData(GSBinWriteStream* stream) {
    int i;
    if (!(state & 0x10)) {
        stream->writeU32(state);
    } else {
        stream->writeU32(0);
    }
    stream->writeFloat(sleepTime);
    u32 offset14 = ((u32)stackPtr14 - (u32)stackBase3C) >> 2;
    u32 codeOffset = ((u32)code - owner->field944) >> 2;
    stream->writeU32(codeOffset);
    stream->writeU32(((u32)stackPtr0C - (u32)stackBase38) >> 3);
    stream->writeU32(((u32)stackPtr10 - (u32)stackBase38) >> 3);
    stream->writeU32(offset14);
    for (i = 0; i < 4; i++) {
        (&retVar)[i].makeStateData(stream);
    }
    stream->writeU32(field14C);
    stream->writeU32(stackCount);
    for (i = 0; i < stackCount; i++) {
        stackArea[i].makeStateData(stream);
    }
    stream->writeU32(stackCount2);
    for (i = 0; i < stackCount2; i++) {
        s32* slot = stackArea2 + i;
        stream->writeU32(((u32)slot - (u32)stackBase3C) >> 2);
    }
    stream->writeU8(timerIndex);
    stream->writeFloat(timerLimit);
    stream->writeU8(waitMode);
    stream->writeU8(flagIndex);
    stream->writeU32(flagValue);
}

bool TigaThread::checkSleepEnd() {
    if (state & 4) {
        if (owner->timers[timerIndex] >= timerLimit) {
            state &= ~4;
        } else {
            return false;
        }
    }
    if (waitMode != 0) {
        if (waitMode == 2) {
            if (owner->getFlag(flagIndex) != flagValue) {
                return false;
            }
        } else if (waitMode == 1) {
            if (owner->getFlag(flagIndex) >= flagValue) {
                return false;
            }
        }
        waitMode = 0;
    }
    return true;
}

void TigaThread::initTiga() {
    memset(&sleepTime + 1, 0, 0x144);
    stackPtr10 = stackArea + stackCount;
    stackPtr14 = (s32*)((u8*)stackArea2 + stackCount2 * 4);
    stackBase38 = stackArea;
    stackBase3C = stackArea2;
    stackPtr10 = stackPtr10 - 1;
    stackPtr10->type = 0x35;
    *(s32*)&stackPtr10->value = 0;
    stackPtr0C = stackPtr10;
    field14C = 0;
    state = 0;
    group = 0;
    thread = 0;
}

void TigaThread::setStackArea(int count, int count2) {
    free();
    stackArea = new tigaVariant[count];
    stackArea2 = new s32[count2];
    stackCount = count;
    stackCount2 = count2;
}


void TigaThread::free() {
    if (retVar.type == 1 || retVar.type == 2) {
        retVar.type = 0;
    } else {
        Tiga::m_cpCurrentObject->cellMemory->freeVariant(&retVar);
        retVar.type = 0;
    }
    if (stackArea != 0) {
        delete[] stackArea;
        stackArea = 0;
    }
    if (stackArea2 != 0) {
        delete[] stackArea2;
        stackArea2 = 0;
    }
    state = 0;
}


TigaThread::~TigaThread() {
    free();
}

TigaThread::TigaThread() {
    state = 0;
    stackArea = 0;
    stackArea2 = 0;
    memset(&sleepTime + 1, 0, 0x144);
    thread = 0;
    setStackArea(0x100, 0x80);
}

GSresID* TigaObjManager::getResource(int index) {
    if (index < 0 || index >= 0x40) {
        return 0;
    }
    return &resources[index];
}

int TigaObjManager::getResourceIdx(GSresID* res) {
    if (res < resources || res >= resources + 0x40) {
        return -1;
    }
    int index = res - resources;
    if (index < 0 || index >= 0x40) {
        return -1;
    }
    return index;
}

GSresID* TigaObjManager::newResource() {
    int i = 0;
    for (s8* p = resourceUse; p <= resourceUse + 0x40; p++, i++) {
        if (*p == 0) {
            *p = 1;
            resources[i].group = 0;
            resources[i].id = 0;
            return &resources[i];
        }
    }
    return 0;
}

void TigaObjManager::addVectorIdx(GSvec* vec) {
    int index = getVectorIdx(vec);
    if (index >= 0) {
        vectorUse[index]++;
    }
}

int TigaObjManager::getVectorIdx(GSvec* vec) {
    if (vec < vectors || vec >= vectors + 0x80) {
        return -1;
    }
    int index = vec - vectors;
    if (index < 0 || index >= 0x80) {
        return -1;
    }
    return index;
}


void TigaObjManager::deleteVector(GSvec* vec) {
    int index = getVectorIdx(vec);
    if (index >= 0) {
        s8 use = vectorUse[index];
        if (use > 0) {
            vectorUse[index] = use - 1;
        }
    }
}

GSvec* TigaObjManager::newVector() {
    s8* p;
    int i;
    i = 0;
    for (p = vectorUse; p <= vectorUse + 0x80; p++, i++) {
        if (*p == 0) {
            *p = 1;
            vectors[i].param1 = 0.0f;
            vectors[i].param2 = 0.0f;
            vectors[i].param3 = 0.0f;
            return &vectors[i];
        }
    }
    return 0;
}

void TigaObjManager::clear() {
    memset(vectorUse, 0, 0x80);
    memset(resourceUse, 0, 0x40);
}

TigaObjManager::~TigaObjManager() {}

TigaObjManager::TigaObjManager() {
    clear();
}

void _executeScriptThread(Tiga* tiga, long id) {
    tiga->executeOneThread(timeGetLastFrameSec(), id);
    while (tiga->isRunningThread(id)) {
        GSthreadSwitch();
        if (!tiga->isRunningThread(id)) {
            break;
        }
        tiga->executeOneThread(timeGetLastFrameSec(), id);
    }
}

Tiga* Tiga::m_cpCurrentObject;

s32 tigaErrMessage(const char* message) {
    if (Tiga::m_cpCurrentObject != 0) {
    }
    return (s32)message;
}

}  // namespace GSscript
