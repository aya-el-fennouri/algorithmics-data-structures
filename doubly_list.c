#include <stdio.h>
#include <stdlib.h>
#include "doubly_list.h"

static DNode *dnode_new(int value) {
    DNode *n = malloc(sizeof(DNode));
    if (n == NULL) return NULL;
    n->value = value;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

void dlist_init(DList *l) {
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

int dlist_push_front(DList *l, int value) {
    DNode *n = dnode_new(value);
    if (n == NULL) return 0;
    n->next = l->head;
    if (l->head != NULL) l->head->prev = n;
    else l->tail = n;                 /* list was empty */
    l->head = n;
    l->size++;
    return 1;
}

int dlist_push_back(DList *l, int value) {
    DNode *n = dnode_new(value);
    if (n == NULL) return 0;
    n->prev = l->tail;
    if (l->tail != NULL) l->tail->next = n;
    else l->head = n;                 /* list was empty */
    l->tail = n;
    l->size++;
    return 1;
}

void dlist_remove_node(DList *l, DNode *node) {
    if (node->prev != NULL) node->prev->next = node->next;
    else l->head = node->next;
    if (node->next != NULL) node->next->prev = node->prev;
    else l->tail = node->prev;
    free(node);
    l->size--;
}

int dlist_pop_front(DList *l, int *out) {
    if (l->head == NULL) return 0;
    if (out) *out = l->head->value;
    dlist_remove_node(l, l->head);
    return 1;
}

int dlist_pop_back(DList *l, int *out) {
    if (l->tail == NULL) return 0;
    if (out) *out = l->tail->value;
    dlist_remove_node(l, l->tail);
    return 1;
}

DNode *dlist_search(const DList *l, int value) {
    for (DNode *cur = l->head; cur != NULL; cur = cur->next) {
        if (cur->value == value) return cur;
    }
    return NULL;
}

void dlist_print_forward(const DList *l) {
    printf("NULL <-> ");
    for (DNode *cur = l->head; cur != NULL; cur = cur->next) printf("%d <-> ", cur->value);
    printf("NULL\n");
}

void dlist_print_backward(const DList *l) {
    printf("NULL <-> ");
    for (DNode *cur = l->tail; cur != NULL; cur = cur->prev) printf("%d <-> ", cur->value);
    printf("NULL\n");
}

void dlist_free(DList *l) {
    while (dlist_pop_front(l, NULL)) { }
}
