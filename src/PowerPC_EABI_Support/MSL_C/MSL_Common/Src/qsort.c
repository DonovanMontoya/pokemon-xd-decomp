#include "global.h"

// In-place heap sort used by the original runtime.
void qsort(void* base, unsigned long count, unsigned long width,
           int (*compare)(const void*, const void*)) {
    unsigned long root, limit, child;
    char *rootEntry, *lastEntry, *parent, *entry, *next;
    if (count >= 2) {
    root = (count >> 1) + 1;
    limit = count;
    rootEntry = (char*)base + width * (root - 1);
    lastEntry = (char*)base + width * (count - 1);
    for (;;) {
        if (root > 1) { rootEntry -= width; --root; }
        else {
            char* a = lastEntry - 1;
            char* b = rootEntry - 1;
            unsigned long bytes = width + 1;
            while (--bytes) { char value = *(b + 1); *(b + 1) = *(a + 1); *(a + 1) = value; ++b; ++a; }
            if (--limit == 1) return;
            lastEntry -= width;
        }
        child = root;
        entry = (char*)base + width * (root - 1);
        while (child * 2 <= limit) {
            child *= 2;
            parent = entry;
            entry = (char*)base + width * (child - 1);
            if (child < limit) {
                next = entry + width;
                if (compare(entry, next) < 0) { entry = next; ++child; }
            }
            if (compare(parent, entry) >= 0) break;
            {
                char* a = entry - 1;
                char* b = parent - 1;
                unsigned long bytes = width + 1;
                while (--bytes) { char value = *(b + 1); *(b + 1) = *(a + 1); *(a + 1) = value; ++b; ++a; }
            }
        }
    }
    }
}
