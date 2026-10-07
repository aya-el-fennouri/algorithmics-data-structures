#include <stdlib.h>
#include "queue.h"

/* ================= 1. Simple queue ================= */
void queue_init(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

int queue_is_empty(const Queue *q) { return q->front == NULL; }

int queue_enqueue(Queue *q, int x) {
    QNode *n = malloc(sizeof(QNode));
    if (n == NULL) return 0;
    n->value = x;
    n->next = NULL;
    if (q->rear != NULL) q->rear->next = n;
    else q->front = n;                 /* queue was empty */
    q->rear = n;
    q->size++;
    return 1;
}

int queue_dequeue(Queue *q, int *out) {
    if (queue_is_empty(q)) return 0;
    QNode *old = q->front;
    if (out) *out = old->value;
    q->front = old->next;
    if (q->front == NULL) q->rear = NULL;   /* queue became empty */
    free(old);
    q->size--;
    return 1;
}

int queue_peek(const Queue *q, int *out) {
    if (queue_is_empty(q)) return 0;
    *out = q->front->value;
    return 1;
}

void queue_free(Queue *q) {
    while (queue_dequeue(q, NULL)) { }
}

/* ================= 2. Circular queue ================= */
void cqueue_init(CircularQueue *q) {
    q->front = 0;
    q->count = 0;
}

int cqueue_is_empty(const CircularQueue *q) { return q->count == 0; }

int cqueue_is_full(const CircularQueue *q) { return q->count == CQUEUE_CAPACITY; }

int cqueue_enqueue(CircularQueue *q, int x) {
    if (cqueue_is_full(q)) return 0;
    int rear = (q->front + q->count) % CQUEUE_CAPACITY;   /* wrap around */
    q->data[rear] = x;
    q->count++;
    return 1;
}

int cqueue_dequeue(CircularQueue *q, int *out) {
    if (cqueue_is_empty(q)) return 0;
    *out = q->data[q->front];
    q->front = (q->front + 1) % CQUEUE_CAPACITY;          /* wrap around */
    q->count--;
    return 1;
}

int cqueue_peek(const CircularQueue *q, int *out) {
    if (cqueue_is_empty(q)) return 0;
    *out = q->data[q->front];
    return 1;
}

/* ================= 3. Priority queue ================= */
void pqueue_init(PriorityQueue *q) { q->size = 0; }

int pqueue_is_empty(const PriorityQueue *q) { return q->size == 0; }

/* Insert in sorted position (like insertion in an array).
 * Elements with priority >= the new one move right, so among equal
 * priorities the oldest stays closer to the end and is served first. */
int pqueue_enqueue(PriorityQueue *q, int value, int priority) {
    if (q->size >= PQUEUE_CAPACITY) return 0;
    int i = q->size - 1;
    while (i >= 0 && q->items[i].priority >= priority) {
        q->items[i + 1] = q->items[i];
        i--;
    }
    q->items[i + 1].value = value;
    q->items[i + 1].priority = priority;
    q->size++;
    return 1;
}

int pqueue_dequeue(PriorityQueue *q, int *out) {
    if (pqueue_is_empty(q)) return 0;
    *out = q->items[q->size - 1].value;
    q->size--;
    return 1;
}

int pqueue_peek(const PriorityQueue *q, int *out) {
    if (pqueue_is_empty(q)) return 0;
    *out = q->items[q->size - 1].value;
    return 1;
}
