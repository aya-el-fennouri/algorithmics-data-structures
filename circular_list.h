#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

/* Circular linked list (slides 10-11): the last node links back to the first.
 * We only store a pointer to the LAST node (tail): the head is simply tail->next.
 * This trick makes insertion at both ends O(1). */
typedef struct CNode {
    int value;
    struct CNode *next;
} CNode;

typedef struct {
    CNode *tail;
    int size;
} CList;

void   clist_init(CList *l);
CNode *clist_head(const CList *l);
int    clist_push_front(CList *l, int value);
int    clist_push_back(CList *l, int value);
int    clist_pop_front(CList *l, int *out);
int    clist_contains(const CList *l, int value);
void   clist_rotate(CList *l);   /* first element goes to the end (round-robin) */
void   clist_print(const CList *l);
void   clist_free(CList *l);

#endif
