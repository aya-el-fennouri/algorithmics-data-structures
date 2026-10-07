#include <stdio.h>
#include <stdlib.h>
#include "singly_list.h"

static SNode *snode_new(int value) {
    SNode *n = malloc(sizeof(SNode));
    if (n == NULL) return NULL;
    n->value = value;
    n->next = NULL;
    return n;
}

void slist_init(SList *l) {
    l->head = NULL;
    l->size = 0;
}

int slist_push_front(SList *l, int value) {
    SNode *n = snode_new(value);
    if (n == NULL) return 0;
    n->next = l->head;
    l->head = n;
    l->size++;
    return 1;
}

int slist_push_back(SList *l, int value) {
    SNode *n = snode_new(value);
    if (n == NULL) return 0;
    if (l->head == NULL) {
        l->head = n;
    } else {
        SNode *cur = l->head;
        while (cur->next != NULL) cur = cur->next;
        cur->next = n;
    }
    l->size++;
    return 1;
}

int slist_pop_front(SList *l, int *out) {
    if (l->head == NULL) return 0;
    SNode *old = l->head;
    if (out) *out = old->value;
    l->head = old->next;
    free(old);
    l->size--;
    return 1;
}

int slist_pop_back(SList *l, int *out) {
    if (l->head == NULL) return 0;
    if (l->head->next == NULL) {            /* only one node */
        if (out) *out = l->head->value;
        free(l->head);
        l->head = NULL;
    } else {
        SNode *prev = l->head;              /* find the node before the last one */
        while (prev->next->next != NULL) prev = prev->next;
        if (out) *out = prev->next->value;
        free(prev->next);
        prev->next = NULL;
    }
    l->size--;
    return 1;
}

int slist_get(const SList *l, int index, int *out) {
    if (index < 0 || index >= l->size) return 0;
    SNode *cur = l->head;
    for (int i = 0; i < index; i++) cur = cur->next;
    *out = cur->value;
    return 1;
}

SNode *slist_search(const SList *l, int value) {
    for (SNode *cur = l->head; cur != NULL; cur = cur->next) {
        if (cur->value == value) return cur;
    }
    return NULL;
}

int slist_insert_after(SList *l, SNode *node, int value) {
    if (node == NULL) return 0;
    SNode *n = snode_new(value);
    if (n == NULL) return 0;
    n->next = node->next;     /* no shifting needed, just relink pointers */
    node->next = n;
    l->size++;
    return 1;
}

int slist_remove_value(SList *l, int value) {
    SNode *prev = NULL;
    SNode *cur = l->head;
    while (cur != NULL && cur->value != value) {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL) return 0;              /* not found */
    if (prev == NULL) l->head = cur->next;  /* removing the head */
    else prev->next = cur->next;
    free(cur);
    l->size--;
    return 1;
}

void slist_print(const SList *l) {
    for (SNode *cur = l->head; cur != NULL; cur = cur->next) {
        printf("%d -> ", cur->value);
    }
    printf("NULL\n");
}

void slist_free(SList *l) {
    while (slist_pop_front(l, NULL)) { }
}
