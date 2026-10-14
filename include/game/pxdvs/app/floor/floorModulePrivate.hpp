#ifndef FLOOR_MODULE_PRIVATE_HPP
#define FLOOR_MODULE_PRIVATE_HPP
#include <dolphin/types.h>

namespace GSscript {
struct tigaVariant {
    s16 type, flags;
    s32 value;
    void setInteger(s32 v) {
        type = 1;
        value = v;
    }
};
struct Tiga {
    s32 runParams(int, tigaVariant *, int, bool);
    bool isRunningThread(s32);
    void deleteThread(s32);
    void deleteThreadGroup(u32);
    void unblockThread(s32);
    void unblockThreadGroup(u32);
    void blockThread(s32);
    void blockThreadGroup(u32);
};
}

enum FloorState {
    FloorStateUnused,
    FloorStateCreate,
    FloorStatePre,
    FloorStatePreWait,
    FloorStateNormal,
    FloorStateNormalWait,
    FloorStatePost,
    FloorStatePostWait,
    FloorStateFree
};
enum FloorModuleType {
    FloorTypeFunc = 0,
    FloorTypeGSvm = 1,
    FloorTypeTpc = 2,
    FloorTypeSingleGSvm = 3,
    FloorTypeSingleTpc = 4,
    FloorTypeAny = 0xFF
};
enum FloorStateMode { FloorStateModeNone };
enum FloorEnterMode { FloorEnterModeNone };

struct GSthread;

struct FloorModuleInterface {
    void (*create)(u32, FloorEnterMode);
    void (*pre)(u32, FloorEnterMode);
    void (*normal)(u32, FloorEnterMode);
    s32 (*thread)(GSthread *);
    void (*post)(u32, FloorEnterMode);
    void (*free)(u32, FloorEnterMode);
    const char *(*getName)();
    void (*saveState)(FloorStateMode, void *, u32);
    void (*loadState)(FloorStateMode, void *, u32);
    u32 (*getStateSize)(FloorStateMode);
    u32 (*getStateID)();
};

struct ScriptTpcNode {
    u32 id;
    s32 thread;
    bool isRunning();
    void exec(u8, u32, FloorEnterMode);
    void terminate();
    void unblock();
    void block();
    GSscript::Tiga *getScript();
    void setID(u32);
};

struct FloorScriptModule {
    ScriptTpcNode nodes[3];
    bool isRunning(FloorState);
    void kill();
    void terminate();
    void unblock();
    void block();
    void exec(FloorState, u8, u32, FloorEnterMode);
    ScriptTpcNode *stateToNode(FloorState);
    void setIDs(u32 a, u32 b, u32 c) {
        nodes[0].setID(a);
        nodes[1].setID(b);
        nodes[2].setID(c);
    }
};

struct FloorModuleEntry {
    FloorModuleEntry *prev;
    FloorModuleEntry *next;
    u32 handle;
    FloorState state;
    FloorModuleType type;
    u32 groupID;
    u8 priority;
    u8 blocked;
    u8 entered;
    union {
        FloorModuleInterface module;
        FloorScriptModule script;
        ScriptTpcNode tpc;
    };

    FloorModuleEntry();
    void init();
    bool isScriptRunning(FloorState);
    void exec(FloorState, unsigned int, FloorEnterMode);
    void terminate();
    void kill();
    void unblock();
    void block();
    void setScriptModule(u8, u32, u32, u32, u32);
    void setModule(u8, u32, FloorModuleInterface *);
    FloorModuleEntry *getNext() const { return next; }
    u8 isBlock() const { return blocked; }
    FloorModuleType getType() const { return type; }
    u32 getGroupID() const { return groupID; }
    FloorModuleEntry *getPrev() const { return prev; }
    FloorModuleInterface *getModuleInterface() {
        if (type == FloorTypeFunc) return &module;
        return 0;
    }
    u32 getHandle() const { return handle; }
    void setHandle(u32 h) { handle = h; }
    void setPrev(FloorModuleEntry *p) { prev = p; }
    void setNext(FloorModuleEntry *n) { next = n; }
    u8 getPriority() const { return priority; }
    bool isEmpty() const { return handle == 0; }
    bool isTpcScript() const { return type == FloorTypeTpc; }
};

struct FloorModuleList {
    FloorModuleEntry *entries;
    u32 count;
    u32 handleCounter;
    FloorModuleEntry *head;
    u32 size;
    virtual ~FloorModuleList();
    FloorModuleList(u32);
    void dumpModule();
    void waitFloorScript(FloorState);
    bool executeIsDone(FloorState);
    void executeAll(unsigned int, FloorState, FloorModuleType, FloorEnterMode, u32);
    void restorePopState(void *, FloorStateMode, bool);
    void *makePushState(FloorStateMode);
    void killModuleGroup(u32);
    void unblockModuleGroup(u32);
    void blockModuleGroup(u32);
    void unregisterModuleGroup(u32);
    void killModule(u32);
    void unblockModule(u32);
    void blockModule(u32);
    void unregisterModule(u32);
    u32 registerScriptModule(u8, u32, u32, u32, u32);
    u32 registerModule(u8, u32, FloorModuleInterface *);
    void removeFuncFromList(FloorModuleEntry *);
    void insertFuncIntoList(FloorModuleEntry *);
    FloorModuleEntry *findHandle(u32);
    FloorModuleEntry *findFree();
    FloorModuleEntry *getFMEEnd();
    u32 getNewHandle() {
        handleCounter = handleCounter + 1;
        if (handleCounter == 0) handleCounter = handleCounter + 1;
        return handleCounter;
    }
};

extern "C" {
u8 FloorModuleInterface_exec(FloorModuleInterface *, FloorState, u32, FloorEnterMode, bool);
void FloorModuleInterface_clear(FloorModuleInterface *);
}
#endif
