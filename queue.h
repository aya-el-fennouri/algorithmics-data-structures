#ifndef QUEUE_H
#define QUEUE_H

/* Queues, FIFO (slides 17-19): simple, circular and priority queue. */

/* ---- 1. Simple queue (linked list with front and rear pointers -> O(1)) ---- */
typedef struct QNode {
    int value;
    struct QNode *next;
} QNode;

typedef struct {
    QNode *front;
    QNode *rear;
    int size;
} Queue;

void queue_init(Queue *q);
int  queue_is_empty(const Queue *q);
int  queue_enqueue(Queue *q, int x);
int  queue_dequeue(Queue *q, int *out);
int  queue_peek(const Queue *q, int *out);
void queue_free(Queue *q);

/* ---- 2. Circular queue (fixed-size array, the rear wraps around) ---- */
#define CQUEUE_CAPACITY 5

typedef struct {
    int data[CQUEUE_CAPACITY];
    int front;     /* index of the first element */
    int count;     /* number of elements */
} CircularQueue;

void cqueue_init(CircularQueue *q);
int  cqueue_is_empty(const CircularQueue *q);
int  cqueue_is_full(const CircularQueue *q);
int  cqueue_enqueue(CircularQueue *q, int x);
int  cqueue_dequeue(CircularQueue *q, int *out);
int  cqueue_peek(const CircularQueue *q, int *out);

/* ---- 3. Priority queue (higher priority served first; FIFO among equals) ---- */
#define PQUEUE_CAPACITY 100

typedef struct {
    int value;
    int priority;
} PQItem;

typedef struct {
    PQItem items[PQUEUE_CAPACITY];   /* kept sorted: highest priority at the END */
    int size;
} PriorityQueue;

void pqueue_init(PriorityQueue *q);
int  pqueue_is_empty(const PriorityQueue *q);
int  pqueue_enqueue(PriorityQueue *q, int value, int priority);  /* O(n) */
int  pqueue_dequeue(PriorityQueue *q, int *out);                 /* O(1) */
int  pqueue_peek(const PriorityQueue *q, int *out);

#endif
