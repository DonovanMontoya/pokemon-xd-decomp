#include <game/pxdvs/GSAPI/GSScript/tiga.hpp>

#pragma auto_inline off
namespace GSscript {



int Tiga::getStateSize() {
    GSBinWriteSizeStream stream;
    makeStateData(&stream);
    return stream.getWriteSize();
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

int Tiga::makeThread(TPCCode* code, int& index, long& handle) {
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
            return 1;
        }
    }
    return 0;
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
