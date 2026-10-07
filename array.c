#include <stdio.h>
#include "array.h"

void array_init(Array *a) {
    a->size = 0;
}

/* Direct access: return a[i] */
int array_get(const Array *a, int i, int *out) {
    if (i < 0 || i >= a->size) return 0;
    *out = a->data[i];
    return 1;
}

int array_set(Array *a, int i, int x) {
    if (i < 0 || i >= a->size) return 0;
    a->data[i] = x;
    return 1;
}

/* Insertion: for j from n-1 down to i: a[j+1] <- a[j]; a[i] <- x; n <- n+1 */
int array_insert(Array *a, int i, int x) {
    if (a->size >= ARRAY_CAPACITY) return 0;   /* array is full */
    if (i < 0 || i > a->size) return 0;        /* invalid position */
    for (int j = a->size - 1; j >= i; j--) {
        a->data[j + 1] = a->data[j];
    }
    a->data[i] = x;
    a->size++;
    return 1;
}

/* Deletion: for j from i to n-2: a[j] <- a[j+1]; n <- n-1 */
int array_delete(Array *a, int i) {
    if (i < 0 || i >= a->size) return 0;
    for (int j = i; j <= a->size - 2; j++) {
        a->data[j] = a->data[j + 1];
    }
    a->size--;
    return 1;
}

int array_search(const Array *a, int x) {
    for (int i = 0; i < a->size; i++) {
        if (a->data[i] == x) return i;
    }
    return -1;
}

void array_print(const Array *a) {
    printf("[");
    for (int i = 0; i < a->size; i++) {
        printf("%d%s", a->data[i], (i < a->size - 1) ? ", " : "");
    }
    printf("]\n");
}
