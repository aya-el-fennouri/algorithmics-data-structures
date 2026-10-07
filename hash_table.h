#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/* Hash table (slides 20-22): string keys -> string values.
 * Collisions are resolved by CHAINING: each bucket is a linked list. */
typedef struct HTEntry {
    char *key;
    char *value;
    struct HTEntry *next;
} HTEntry;

typedef struct {
    HTEntry **buckets;   /* array of linked lists */
    int size;            /* number of buckets */
    int count;           /* number of stored key-value pairs */
} HashTable;

int          ht_init(HashTable *t, int size);
unsigned int ht_hash(const char *key, int size);   /* sum of ASCII codes % size */
int          ht_put(HashTable *t, const char *key, const char *value); /* insert or update */
const char  *ht_get(const HashTable *t, const char *key);              /* NULL if absent */
int          ht_remove(HashTable *t, const char *key);
void         ht_print(const HashTable *t);
void         ht_free(HashTable *t);

#endif
