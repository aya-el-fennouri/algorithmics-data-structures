#ifndef ARRAY_H
#define ARRAY_H

/* Fixed-size array (slides 5-8).
 * The capacity is fixed at compile time; `size` is how many cells are used. */
#define ARRAY_CAPACITY 100

typedef struct {
    int data[ARRAY_CAPACITY];
    int size;
} Array;

void array_init(Array *a);
int  array_get(const Array *a, int i, int *out);   /* O(1)  - returns 1 on success, 0 on error */
int  array_set(Array *a, int i, int x);            /* O(1) */
int  array_insert(Array *a, int i, int x);         /* O(n)  - shifts elements right */
int  array_delete(Array *a, int i);                /* O(n)  - shifts elements left  */
int  array_search(const Array *a, int x);          /* O(n)  - returns index or -1   */
void array_print(const Array *a);

#endif
