#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

/* Allocate a copy of a string (like strdup, but standard C) */
static char *copy_string(const char *s) {
    char *c = malloc(strlen(s) + 1);
    if (c != NULL) strcpy(c, s);
    return c;
}

int ht_init(HashTable *t, int size) {
    t->buckets = calloc(size, sizeof(HTEntry *));   /* all buckets start empty (NULL) */
    if (t->buckets == NULL) return 0;
    t->size = size;
    t->count = 0;
    return 1;
}

/* Simple hash function from the slides */
unsigned int ht_hash(const char *key, int size) {
    unsigned long sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += (unsigned char)key[i];
    }
    return (unsigned int)(sum % size);
}

int ht_put(HashTable *t, const char *key, const char *value) {
    unsigned int idx = ht_hash(key, t->size);

    /* key already present? -> update its value */
    for (HTEntry *e = t->buckets[idx]; e != NULL; e = e->next) {
        if (strcmp(e->key, key) == 0) {
            char *v = copy_string(value);
            if (v == NULL) return 0;
            free(e->value);
            e->value = v;
            return 1;
        }
    }

    /* new key -> add at the front of the bucket's list (chaining) */
    HTEntry *e = malloc(sizeof(HTEntry));
    if (e == NULL) return 0;
    e->key = copy_string(key);
    e->value = copy_string(value);
    if (e->key == NULL || e->value == NULL) {
        free(e->key); free(e->value); free(e);
        return 0;
    }
    e->next = t->buckets[idx];
    t->buckets[idx] = e;
    t->count++;
    return 1;
}

const char *ht_get(const HashTable *t, const char *key) {
    unsigned int idx = ht_hash(key, t->size);
    for (HTEntry *e = t->buckets[idx]; e != NULL; e = e->next) {
        if (strcmp(e->key, key) == 0) return e->value;
    }
    return NULL;
}

int ht_remove(HashTable *t, const char *key) {
    unsigned int idx = ht_hash(key, t->size);
    HTEntry *prev = NULL;
    HTEntry *e = t->buckets[idx];
    while (e != NULL && strcmp(e->key, key) != 0) {
        prev = e;
        e = e->next;
    }
    if (e == NULL) return 0;
    if (prev == NULL) t->buckets[idx] = e->next;
    else prev->next = e->next;
    free(e->key);
    free(e->value);
    free(e);
    t->count--;
    return 1;
}

void ht_print(const HashTable *t) {
    for (int i = 0; i < t->size; i++) {
        printf("  [%d]", i);
        for (HTEntry *e = t->buckets[i]; e != NULL; e = e->next) {
            printf(" -> (%s : %s)", e->key, e->value);
        }
        printf("\n");
    }
}

void ht_free(HashTable *t) {
    for (int i = 0; i < t->size; i++) {
        HTEntry *e = t->buckets[i];
        while (e != NULL) {
            HTEntry *next = e->next;
            free(e->key);
            free(e->value);
            free(e);
            e = next;
        }
    }
    free(t->buckets);
    t->buckets = NULL;
    t->size = 0;
    t->count = 0;
}
