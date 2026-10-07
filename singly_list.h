#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

/* Singly linked list (slides 9-11): each node has a value and a pointer to the next node. */
typedef struct SNode {
    int value;
    struct SNode *next;
} SNode;

typedef struct {
    SNode *head;
    int size;
} SList;

void   slist_init(SList *l);
int    slist_push_front(SList *l, int value);              /* O(1) */
int    slist_push_back(SList *l, int value);               /* O(n) - must walk to the end */
int    slist_pop_front(SList *l, int *out);                /* O(1) */
int    slist_pop_back(SList *l, int *out);                 /* O(n) */
int    slist_get(const SList *l, int index, int *out);     /* O(n) - no direct access */
SNode *slist_search(const SList *l, int value);            /* O(n) */
int    slist_insert_after(SList *l, SNode *node, int value); /* O(1) when the pointer is known */
int    slist_remove_value(SList *l, int value);            /* O(n) */
void   slist_print(const SList *l);
void   slist_free(SList *l);

#endif
