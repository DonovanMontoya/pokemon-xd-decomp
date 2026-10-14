#ifndef HSD_DEBUG_H
#define HSD_DEBUG_H
void HSD_Panic(const char*, unsigned int, const char*);
void __assert(const char*, unsigned int, const char*);
/* CPU register capture remains in the original assembly fallback. */
void HSD_SaveContext(void);
#endif
