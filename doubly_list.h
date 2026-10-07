#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

/* Doubly linked list (slides 10-11): pointers to next AND previous node.
 * We keep a tail pointer so head/tail operations are all O(1). */
typedef struct DNode {
    int value;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    DNode *head;
    DNode *tail;
    int size;
} DList;

void   dlist_init(DList *l);
int    dlist_push_front(DList *l, int value);   /* O(1) */
int    dlist_push_back(DList *l, int value);    /* O(1) */
int    dlist_pop_front(DList *l, int *out);     /* O(1) */
int    dlist_pop_back(DList *l, int *out);      /* O(1) */
DNode *dlist_search(const DList *l, int value); /* O(n) */
void   dlist_remove_node(DList *l, DNode *node);/* O(1) when the pointer is known */
void   dlist_print_forward(const DList *l);
void   dlist_print_backward(const DList *l);
void   dlist_free(DList *l);

#endif
