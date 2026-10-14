extern "C" {
typedef unsigned int (*HashIndexCallback)(void *, void *);
typedef int (*HashCompareCallback)(void *, void *, void *);

struct HashMethods {
    void *unused[15];
    HashIndexCallback index;
    HashCompareCallback compare;
};

struct Hash {
    HashMethods *methods;
    struct HashNode **buckets;
    unsigned int table_size;
};

struct HashNode {
    HashNode *next;
    void *key;
    void *data;
};

extern void __assert(const char *, int, const char *);

void *HSD_HashSearch(Hash *hash, void *key, int *success) {
    unsigned int index = hash->methods->index(hash, key);
    HashNode *node;

    if (index >= hash->table_size) {
        __assert("hash.c", 113, "idx < hash->table_size");
    }
    node = hash->buckets[index];
    while (node != 0 && hash->methods->compare(hash, node->key, key)) {
        node = node->next;
    }
    if (success != 0) {
        *success = node != 0;
    }
    return node != 0 ? node->data : 0;
}
}
