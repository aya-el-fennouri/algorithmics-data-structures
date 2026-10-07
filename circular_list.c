#include <stdio.h>
#include <stdlib.h>
#include "circular_list.h"

void clist_init(CList *l) {
    l->tail = NULL;
    l->size = 0;
}

CNode *clist_head(const CList *l) {
    return (l->tail == NULL) ? NULL : l->tail->next;
}

int clist_push_front(CList *l, int value) {
    CNode *n = malloc(sizeof(CNode));
    if (n == NULL) return 0;
    n->value = value;
    if (l->tail == NULL) {          /* empty: the node points to itself */
        n->next = n;
        l->tail = n;
    } else {
        n->next = l->tail->next;    /* new node points to the old head */
        l->tail->next = n;          /* last node now points to the new head */
    }
    l->size++;
    return 1;
}

int clist_push_back(CList *l, int value) {
    if (!clist_push_front(l, value)) return 0;
    l->tail = l->tail->next;        /* the new head becomes the tail */
    return 1;
}

int clist_pop_front(CList *l, int *out) {
    if (l->tail == NULL) return 0;
    CNode *head = l->tail->next;
    if (out) *out = head->value;
    if (head == l->tail) l->tail = NULL;   /* it was the only node */
    else l->tail->next = head->next;
    free(head);
    l->size--;
    return 1;
}

/* Traversal stops when we come back to the starting point */
int clist_contains(const CList *l, int value) {
    if (l->tail == NULL) return 0;
    CNode *start = l->tail->next;
    CNode *cur = start;
    do {
        if (cur->value == value) return 1;
        cur = cur->next;
    } while (cur != start);
    return 0;
}

void clist_rotate(CList *l) {
    if (l->tail != NULL) l->tail = l->tail->next;
}

void clist_print(const CList *l) {
    if (l->tail == NULL) { printf("(empty)\n"); return; }
    CNode *start = l->tail->next;
    CNode *cur = start;
    do {
        printf("%d -> ", cur->value);
        cur = cur->next;
    } while (cur != start);
    printf("(back to %d)\n", start->value);
}

void clist_free(CList *l) {
    while (clist_pop_front(l, NULL)) { }
}
