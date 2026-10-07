#include "stack.h"

void stack_init(Stack *s) { s->size = 0; }

int stack_is_empty(const Stack *s) { return s->size == 0; }

int stack_is_full(const Stack *s) { return s->size == STACK_CAPACITY; }

/* NOTE: the top element is at S[n-1], so a NEW element goes to S[n]
 * (writing to S[n-1] would overwrite the current top). */
int stack_push(Stack *s, int x) {
    if (stack_is_full(s)) return 0;      /* stack overflow */
    s->data[s->size] = x;
    s->size++;
    return 1;
}

int stack_pop(Stack *s, int *out) {
    if (stack_is_empty(s)) return 0;     /* stack underflow */
    *out = s->data[s->size - 1];
    s->size--;
    return 1;
}

int stack_peek(const Stack *s, int *out) {
    if (stack_is_empty(s)) return 0;
    *out = s->data[s->size - 1];
    return 1;
}
