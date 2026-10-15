#ifndef GS_SCRIPT_TIGA_HPP
#define GS_SCRIPT_TIGA_HPP
#include <global.h>
// Local GSvec with a constructor (the original sources construct arrays of it).
#ifndef GS_VEC_H
#define GS_VEC_H
struct GSvec {
    f32 param1;
    f32 param2;
    f32 param3;
    GSvec();
};
#endif
#include <game/pxdvs/GSAPI/GSScript/tvariant.hpp>

struct GSresID {
    u32 group;
    u32 id;
};

extern "C" void GSmemFree(void*);
extern "C" void* memcpy(void*, const void*, unsigned long);
extern "C" void* GSmemAlloc(unsigned long);

struct GSBinWriteStream {
    u8* start;          // 0x0
    u8* cur;            // 0x4
    u32 size;           // 0x8
    void* buffer;       // 0xC
    u8 writing;         // 0x10

    GSBinWriteStream() {
        cur = 0;
        buffer = 0;
        start = 0;
        size = 0;
        writing = 0;
    }
    ~GSBinWriteStream() {
        if (buffer != 0) {
            GSmemFree(buffer);
        }
    }
    u32 getWriteSize() const { return cur - start; }
    void writeU8(u8 v) {
        if (writing == 0) {
            cur++;
            return;
        }
        *cur++ = v;
    }
    void writeS8(s8 v) { writeU8(v); }
    void writeBool(u32 v) {
        if (writing == 0) {
            cur++;
            return;
        }
        *cur++ = (v != 0);
    }
    void writeU16(u32 v) {
        if (writing == 0) {
            cur += 2;
            return;
        }
        *cur++ = (v >> 8) & 0xFF;
        *cur++ = v & 0xFF;
    }
    void writeU32(u32 v) {
        if (writing == 0) {
            cur += 4;
            return;
        }
        *cur++ = v >> 24;
        *cur++ = v >> 16;
        *cur++ = v >> 8;
        *cur++ = v;
    }
    void writeBytes(const void* source, u32 length) {
        if (writing != 0) {
            memcpy(cur, source, length);
        }
        cur += length;
    }
    void writeFloat(f32 v) {
        union { f32 f; u32 u; u32 pad[2]; } c;
        c.f = v;
        writeU32(c.u);
    }
};

struct GSBinWriteSizeStream : public GSBinWriteStream {
    GSBinWriteSizeStream() {
        cur = 0;
        buffer = 0;
        start = 0;
        size = 0x10000000;
        writing = 0;
    }
    ~GSBinWriteSizeStream() {}
};

struct GSBinReadStream {
    u8* start;          // 0x0
    u8* cur;            // 0x4
    u32 size;           // 0x8

    GSBinReadStream(void* data, u32 sz) {
        cur = (u8*)data;
        start = (u8*)data;
        size = sz;
    }
    u8 readU8() { return *cur++; }
    u16 readU16() {
        u16 v = (cur[0] << 8) | cur[1];
        cur += 2;
        return v;
    }
    u32 readU32() {
        u32 v = (cur[0] << 24) | (cur[1] << 16) | (cur[2] << 8) | cur[3];
        cur += 4;
        return v;
    }
    bool readBool() { return readU8() != 0; }
    f32 readFloat() {
        union { f32 f; u32 u; u32 pad[2]; } c;
        c.u = readU32();
        return c.f;
    }
};
struct TPCCode;

class CChank {
public:
    u32 chankA, chankB, chankC;
    CChank();
    virtual ~CChank() {}
    u32 chankD;
    static CChank* searchChankID(const char*, s32);
};

class CChankBlock : public CChank {
public:
    u32 blockA;
    CChankBlock() {}
    virtual ~CChankBlock() {}
    void loadFromMemory(char*, char*);
};

namespace GSscript {

class tigaCellMemory {
public:
    s32 cellA, cellB;
    tigaCellMemory();
    virtual ~tigaCellMemory();
    void freeVariant(tigaVariant*);
    void dupVariant(tigaVariant*);
};

class Tiga;

class TigaThread {
public:
    u32 state;                  // 0x00
    f32 sleepTime;              // 0x04
    TPCCode* code;              // 0x08
    tigaVariant* stackPtr0C;    // 0x0c
    tigaVariant* stackPtr10;    // 0x10
    s32* stackPtr14;            // 0x14
    tigaVariant retVar;         // 0x18
    u8 pad20[0x18];
    tigaVariant* stackBase38;   // 0x38
    s32* stackBase3C;           // 0x3c
    u8 pad40[0x10C];
    s32 field14C;               // 0x14c
    tigaVariant* stackArea;     // 0x150
    s32 stackCount;             // 0x154
    s32* stackArea2;            // 0x158
    s32 stackCount2;            // 0x15c
    u8 timerIndex;              // 0x160
    u8 pad161[3];
    f32 timerLimit;             // 0x164
    u8 waitMode;                // 0x168
    u8 flagIndex;               // 0x169
    u8 pad16A[2];
    s32 flagValue;              // 0x16c
    Tiga* owner;                // 0x170
    s32 handle;                 // 0x174
    u32 group;                  // 0x178
    void* thread;               // 0x17c

    TigaThread();
    ~TigaThread();
    void setSaveFlag(bool);
    void stop();
    bool restoreStateData(GSBinReadStream*);
    void makeStateData(GSBinWriteStream*);
    bool checkSleepEnd();
    void initTiga();
    void setStackArea(int, int);
    void free();
};

class TigaObjManager {
public:
    s8 vectorUse[0x80];         // 0x00
    s8 resourceUse[0x40];       // 0x80
    GSvec vectors[0x80];        // 0xc0
    GSresID resources[0x40];    // 0x6c0

    TigaObjManager();
    ~TigaObjManager();
    GSresID* getResource(int);
    int getResourceIdx(GSresID*);
    GSresID* newResource();
    void addVectorIdx(GSvec*);
    int getVectorIdx(GSvec*);
    void deleteVector(GSvec*);
    GSvec* newVector();
    void clear();
};

class Tiga {
public:
    CChankBlock chunk;              // 0x00
    TigaObjManager objManager;      // 0x18
    s32 field8D8;
    s32 threadCount;                // 0x8dc
    f32 timers[4];                  // 0x8e0
    TigaThread* threads[8];         // 0x8f0
    tigaCellMemory* cellMemory;     // 0x910
    u8 pad914[4];
    u8 flags[16];                   // 0x918
    s32 nextHandle;                 // 0x928
    u8 hitFlag;                     // 0x92c
    u8 pad92D[3];
    s32 field930;                   // 0x930
    s32 field934;                   // 0x934
    tigaVariant* resultVar;         // 0x938
    s32 funcCount;                  // 0x93c
    s32 field940;                   // 0x940
    s32 field944;                   // 0x944
    s32 globalCount;                // 0x948
    tigaVariant* globals;           // 0x94c
    s32 field950;                   // 0x950
    s32 field954;                   // 0x954
    s32 field958;                   // 0x958
    s32 field95C;                   // 0x95c
    s32 resIdCount;                 // 0x960
    u32* resIdTable;                // 0x964
    s32 field968;                   // 0x968
    s32 field96C;                   // 0x96c
    s32 codeCount;                  // 0x970
    u32* codeTable;                 // 0x974
    s32 field978;                   // 0x978
    u8 field97C;                    // 0x97c
    u8 pad97D[3];
    TigaThread* currentThread;      // 0x980

    Tiga();
    virtual int execExtendMethod(int, int, tigaVariant*, tigaVariant*);
    virtual int execExtendGlobalFunction(int, tigaVariant*, tigaVariant*);
    virtual int getExtendVariable(tigaVariant*, int, int);
    virtual int setExtendVariable(tigaVariant*, int, int);
    virtual void mapping() {}
    virtual void unmapping() {}
    virtual ~Tiga();

    bool isFlagIndex(int i) {
        if (i < 16 && i >= 0) {
            return true;
        }
        return false;
    }
    u8 getFlag(int i) {
        if (isFlagIndex(i)) {
            return flags[i];
        }
        return 0;
    }
    void debugDump();
    int getStateSize();
    bool restoreStateData(void*, unsigned long);
    void makeStateData(GSBinWriteStream*);
    int getNameToFuncId(const char*);
    int getResultValue(long);
    void* getIdToCodeAdress(int);
    u32* searchResID(unsigned long, unsigned long);
    int setPresetVar(tigaVariant*, int, int);
    void getPresetVar(tigaVariant*, int, int);
    int execMethod(int, int, tigaVariant*, tigaVariant*);
    int execute(TigaThread*);
    int calcExpr2(int, tigaVariant*, tigaVariant*, tigaVariant*);
    int calcExpr1(int, tigaVariant*, tigaVariant*);
    int executeOneThread(float, long);
    int executeThread(float);
    void unblockThread(long);
    void blockThread(long);
    void unblockThreadGroup(unsigned long);
    void blockThreadGroup(unsigned long);
    void deleteThreadGroup(unsigned long);
    bool isRunningThread(long);
    void deleteThread(long);
    TigaThread* getHandleToThread(long);
    bool makeThread(TPCCode*, int&, long&);
    int runParamsWait(int, tigaVariant*, int, tigaVariant*);
    long runParamsPC(TPCCode*, tigaVariant*, int, bool);
    long runParams(int, tigaVariant*, int, bool);
    int setTpcChank(CChank*);
    void unmappingScript();
    void mappingScript(char*);
    void free();

    static Tiga* m_cpCurrentObject;
};

s32 tigaErrMessage(const char*);
void _executeScriptThread(Tiga*, long);

}  // namespace GSscript

extern "C" {
f32 timeGetLastFrameSec();
void GSthreadSwitch();
void GSthreadTerminate(void*);
void* memset(void*, int, unsigned long);
s32 floorGetCurrentFloorGroupID();
}

#endif
