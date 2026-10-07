#ifndef STACK_H
#define STACK_H

/* Stack, LIFO (slides 12-14), implemented with an array.
 * All operations are O(1). */
#define STACK_CAPACITY 100

typedef struct {
    int data[STACK_CAPACITY];
    int size;      /* number of elements = index of the next free cell */
} Stack;

void stack_init(Stack *s);
int  stack_is_empty(const Stack *s);
int  stack_is_full(const Stack *s);
int  stack_push(Stack *s, int x);
int  stack_pop(Stack *s, int *out);
int  stack_peek(const Stack *s, int *out);

#endif
