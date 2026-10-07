/* Tests for all data structures of Session 2.
 * Each CHECK prints FAIL if the condition is false. */
#include <stdio.h>
#include <string.h>
#include "array.h"
#include "singly_list.h"
#include "doubly_list.h"
#include "circular_list.h"
#include "stack.h"
#include "queue.h"
#include "hash_table.h"
#include "person.h"

static int tests_run = 0;
static int tests_failed = 0;

#define CHECK(cond) do {                                              \
        tests_run++;                                                  \
        if (!(cond)) {                                                \
            tests_failed++;                                           \
            printf("  FAIL (%s:%d): %s\n", __FILE__, __LINE__, #cond); \
        }                                                             \
    } while (0)

/* ------------------------------------------------------------ */
static void test_primitive_types(void) {
    printf("\n== Primitive types (sizes on this machine) ==\n");
    printf("  char=%lu short=%lu int=%lu long=%lu long long=%lu\n",
           (unsigned long)sizeof(char), (unsigned long)sizeof(short), (unsigned long)sizeof(int),
           (unsigned long)sizeof(long), (unsigned long)sizeof(long long));
    printf("  float=%lu double=%lu long double=%lu _Bool=%lu\n",
           (unsigned long)sizeof(float), (unsigned long)sizeof(double),
           (unsigned long)sizeof(long double), (unsigned long)sizeof(_Bool));
    CHECK(sizeof(char) == 1);
    CHECK(sizeof(short) <= sizeof(int));
    CHECK(sizeof(int) <= sizeof(long));
    CHECK(sizeof(float) <= sizeof(double));
}

/* ------------------------------------------------------------ */
static void test_array(void) {
    printf("\n== Array ==\n");
    Array a;
    array_init(&a);
    int values[] = {52, -8, 11, 0, 2, -7};          /* example from slide 6 */
    for (int i = 0; i < 6; i++) array_insert(&a, a.size, values[i]);
    printf("  start:            "); array_print(&a);

    int x;
    CHECK(array_get(&a, 2, &x) && x == 11);          /* direct access a[2] = 11 */
    CHECK(!array_get(&a, 6, &x));                    /* out of bounds refused */
    CHECK(!array_get(&a, -1, &x));

    CHECK(array_insert(&a, 3, 3));                   /* insert 3 at index 3 */
    printf("  insert 3 at [3]:  "); array_print(&a);
    CHECK(a.size == 7);
    CHECK(array_get(&a, 3, &x) && x == 3);
    CHECK(array_get(&a, 4, &x) && x == 0);           /* 0 was shifted right */

    CHECK(array_delete(&a, 3));                      /* remove the 3 */
    CHECK(array_delete(&a, 2));                      /* remove 11 (slide 6) */
    printf("  delete [3], [2]:  "); array_print(&a);
    CHECK(a.size == 5);
    CHECK(array_get(&a, 2, &x) && x == 0);
    CHECK(array_search(&a, -7) == 4);
    CHECK(array_search(&a, 999) == -1);
    CHECK(array_set(&a, 0, 100) && array_get(&a, 0, &x) && x == 100);

    /* insertion at the beginning and at the end */
    CHECK(array_insert(&a, 0, -1) && array_get(&a, 0, &x) && x == -1);
    CHECK(array_insert(&a, a.size, 42) && array_get(&a, a.size - 1, &x) && x == 42);
    CHECK(!array_insert(&a, a.size + 1, 5));         /* gap not allowed */

    /* full array */
    Array full;
    array_init(&full);
    for (int i = 0; i < ARRAY_CAPACITY; i++) array_insert(&full, i, i);
    CHECK(!array_insert(&full, 0, 1));               /* fixed size! */
}

/* ------------------------------------------------------------ */
static void test_singly_list(void) {
    printf("\n== Singly linked list ==\n");
    SList l;
    slist_init(&l);
    int x;
    CHECK(!slist_pop_front(&l, &x));                 /* empty list */
    CHECK(!slist_pop_back(&l, &x));

    slist_push_back(&l, 32);
    slist_push_back(&l, 11);
    slist_push_front(&l, -2);                        /* -2 -> 32 -> 11 (slide 9) */
    printf("  "); slist_print(&l);
    CHECK(l.size == 3);
    CHECK(slist_get(&l, 0, &x) && x == -2);
    CHECK(slist_get(&l, 2, &x) && x == 11);
    CHECK(!slist_get(&l, 3, &x));

    SNode *n = slist_search(&l, 32);
    CHECK(n != NULL && n->value == 32);
    CHECK(slist_search(&l, 999) == NULL);

    CHECK(slist_insert_after(&l, n, 50));            /* O(1) since we have the pointer */
    printf("  insert 50 after 32: "); slist_print(&l);
    CHECK(slist_get(&l, 2, &x) && x == 50);

    CHECK(slist_remove_value(&l, -2));               /* remove head */
    CHECK(slist_remove_value(&l, 50));               /* remove middle */
    CHECK(!slist_remove_value(&l, 999));
    printf("  after removals:     "); slist_print(&l);
    CHECK(l.size == 2);

    CHECK(slist_pop_back(&l, &x) && x == 11);
    CHECK(slist_pop_front(&l, &x) && x == 32);
    CHECK(l.size == 0 && l.head == NULL);

    for (int i = 0; i < 10; i++) slist_push_back(&l, i);
    slist_free(&l);
    CHECK(l.size == 0 && l.head == NULL);
}

/* ------------------------------------------------------------ */
static void test_doubly_list(void) {
    printf("\n== Doubly linked list ==\n");
    DList l;
    dlist_init(&l);
    int x;
    CHECK(!dlist_pop_back(&l, &x));

    dlist_push_back(&l, 2);    /* B */
    dlist_push_front(&l, 1);   /* A */
    dlist_push_back(&l, 3);    /* C */
    printf("  forward:  "); dlist_print_forward(&l);
    printf("  backward: "); dlist_print_backward(&l);
    CHECK(l.size == 3);
    CHECK(l.head->value == 1 && l.tail->value == 3);
    CHECK(l.head->prev == NULL && l.tail->next == NULL);
    CHECK(l.head->next->prev == l.head);             /* links are consistent */

    DNode *mid = dlist_search(&l, 2);
    CHECK(mid != NULL);
    dlist_remove_node(&l, mid);                      /* O(1) removal */
    CHECK(l.size == 2 && l.head->next == l.tail && l.tail->prev == l.head);

    CHECK(dlist_pop_back(&l, &x) && x == 3);         /* O(1) at the tail */
    CHECK(dlist_pop_front(&l, &x) && x == 1);
    CHECK(l.head == NULL && l.tail == NULL && l.size == 0);

    for (int i = 0; i < 10; i++) dlist_push_front(&l, i);
    dlist_free(&l);
    CHECK(l.size == 0);
}

/* ------------------------------------------------------------ */
static void test_circular_list(void) {
    printf("\n== Circular linked list ==\n");
    CList l;
    clist_init(&l);
    int x;
    CHECK(clist_head(&l) == NULL);
    CHECK(!clist_contains(&l, 1));

    clist_push_back(&l, 1);
    CHECK(l.tail->next == l.tail);                   /* single node points to itself */
    clist_push_back(&l, 2);
    clist_push_back(&l, 3);
    clist_push_front(&l, 0);
    printf("  "); clist_print(&l);
    CHECK(l.size == 4);
    CHECK(clist_head(&l)->value == 0);
    CHECK(l.tail->value == 3);
    CHECK(l.tail->next == clist_head(&l));           /* last links back to first */
    CHECK(clist_contains(&l, 2));
    CHECK(!clist_contains(&l, 42));

    clist_rotate(&l);                                /* 1 2 3 0 */
    printf("  after rotate: "); clist_print(&l);
    CHECK(clist_head(&l)->value == 1 && l.tail->value == 0);

    CHECK(clist_pop_front(&l, &x) && x == 1);
    CHECK(l.size == 3);
    clist_free(&l);
    CHECK(l.tail == NULL && l.size == 0);
}

/* ------------------------------------------------------------ */
static void test_stack(void) {
    printf("\n== Stack (LIFO) ==\n");
    Stack s;
    stack_init(&s);
    int x;
    CHECK(stack_is_empty(&s));
    CHECK(!stack_pop(&s, &x));                       /* underflow */
    CHECK(!stack_peek(&s, &x));

    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);
    CHECK(stack_peek(&s, &x) && x == 30);
    CHECK(s.size == 3);                              /* peek does not remove */
    CHECK(stack_pop(&s, &x) && x == 30);             /* last in, first out */
    CHECK(stack_pop(&s, &x) && x == 20);
    CHECK(stack_pop(&s, &x) && x == 10);
    CHECK(stack_is_empty(&s));
    printf("  pushed 10,20,30 -> popped 30,20,10\n");

    for (int i = 0; i < STACK_CAPACITY; i++) stack_push(&s, i);
    CHECK(stack_is_full(&s));
    CHECK(!stack_push(&s, 1));                       /* overflow */

    /* Application: reverse a word with a stack */
    const char *word = "ENSISA";
    char reversed[16];
    Stack cs;
    stack_init(&cs);
    for (int i = 0; word[i]; i++) stack_push(&cs, word[i]);
    int k = 0;
    while (stack_pop(&cs, &x)) reversed[k++] = (char)x;
    reversed[k] = '\0';
    printf("  reverse(\"%s\") = \"%s\"\n", word, reversed);
    CHECK(strcmp(reversed, "ASISNE") == 0);
}

/* ------------------------------------------------------------ */
static void test_queues(void) {
    int x;

    printf("\n== Simple queue (FIFO) ==\n");
    Queue q;
    queue_init(&q);
    CHECK(queue_is_empty(&q));
    CHECK(!queue_dequeue(&q, &x));
    queue_enqueue(&q, 1);
    queue_enqueue(&q, 2);
    queue_enqueue(&q, 3);
    CHECK(queue_peek(&q, &x) && x == 1);
    CHECK(queue_dequeue(&q, &x) && x == 1);          /* first in, first out */
    CHECK(queue_dequeue(&q, &x) && x == 2);
    queue_enqueue(&q, 4);
    CHECK(queue_dequeue(&q, &x) && x == 3);
    CHECK(queue_dequeue(&q, &x) && x == 4);
    CHECK(queue_is_empty(&q) && q.rear == NULL);
    printf("  enqueued 1,2,3,4 -> dequeued 1,2,3,4\n");
    queue_enqueue(&q, 5);
    queue_free(&q);
    CHECK(q.size == 0);

    printf("\n== Circular queue ==\n");
    CircularQueue cq;
    cqueue_init(&cq);
    for (int i = 1; i <= CQUEUE_CAPACITY; i++) CHECK(cqueue_enqueue(&cq, i));
    CHECK(cqueue_is_full(&cq));
    CHECK(!cqueue_enqueue(&cq, 99));                 /* full */
    CHECK(cqueue_dequeue(&cq, &x) && x == 1);
    CHECK(cqueue_dequeue(&cq, &x) && x == 2);
    CHECK(cqueue_enqueue(&cq, 6));                   /* rear wraps around to index 0 */
    CHECK(cqueue_enqueue(&cq, 7));
    CHECK(cqueue_is_full(&cq));
    printf("  order after wrap-around: ");
    int expected[] = {3, 4, 5, 6, 7};
    for (int i = 0; i < 5; i++) {
        CHECK(cqueue_dequeue(&cq, &x) && x == expected[i]);
        printf("%d ", x);
    }
    printf("\n");
    CHECK(cqueue_is_empty(&cq));

    printf("\n== Priority queue ==\n");
    PriorityQueue pq;
    pqueue_init(&pq);
    CHECK(!pqueue_dequeue(&pq, &x));
    pqueue_enqueue(&pq, 100, 1);   /* normal client */
    pqueue_enqueue(&pq, 200, 5);   /* VIP */
    pqueue_enqueue(&pq, 300, 1);   /* normal client, arrived after 100 */
    pqueue_enqueue(&pq, 400, 3);
    CHECK(pqueue_peek(&pq, &x) && x == 200);
    printf("  served: ");
    int order[] = {200, 400, 100, 300};
    for (int i = 0; i < 4; i++) {
        CHECK(pqueue_dequeue(&pq, &x) && x == order[i]);
        printf("%d ", x);
    }
    printf("\n");
    CHECK(pqueue_is_empty(&pq));
}

/* ------------------------------------------------------------ */
static void test_hash_table(void) {
    printf("\n== Hash table (chaining) ==\n");
    HashTable t;
    CHECK(ht_init(&t, 4));

    /* Same example as slides 20-21 */
    CHECK(ht_hash("Maxime", 4) == 1);
    CHECK(ht_hash("Ali", 4) == 2);
    CHECK(ht_hash("Ken", 4) == 2);                   /* collision with "Ali"! */

    ht_put(&t, "Maxime", "Mulhouse");
    ht_put(&t, "Ali", "Metz");
    ht_put(&t, "Ken", "Strasbourg");
    ht_print(&t);
    CHECK(t.count == 3);
    CHECK(strcmp(ht_get(&t, "Maxime"), "Mulhouse") == 0);
    CHECK(strcmp(ht_get(&t, "Ali"), "Metz") == 0);     /* both survive the collision */
    CHECK(strcmp(ht_get(&t, "Ken"), "Strasbourg") == 0);
    CHECK(ht_get(&t, "Nobody") == NULL);

    ht_put(&t, "Ali", "Colmar");                     /* update existing key */
    CHECK(t.count == 3);
    CHECK(strcmp(ht_get(&t, "Ali"), "Colmar") == 0);

    CHECK(ht_remove(&t, "Ken"));
    CHECK(ht_get(&t, "Ken") == NULL);
    CHECK(strcmp(ht_get(&t, "Ali"), "Colmar") == 0);   /* other key in bucket still there */
    CHECK(!ht_remove(&t, "Ken"));
    CHECK(t.count == 2);

    ht_free(&t);
    CHECK(t.buckets == NULL);
}

/* ------------------------------------------------------------ */
static void test_structs(void) {
    printf("\n== Structs ==\n");
    struct Person p = {"Lina", 26, {1999, 7, 15}};
    printf("  "); person_print(&p);
    CHECK(p.dob.year == 1999);                       /* dot access + nested member */

    p.age = 27;                                      /* direct access with . */
    struct Person *pp = &p;
    pp->dob.year = 2000;                             /* pointer -> then nested member */
    (*pp).dob.month = 8;                             /* equivalent, less readable */
    CHECK(p.age == 27 && p.dob.year == 2000 && p.dob.month == 8);

    person_birthday(&p);                             /* modified through a pointer */
    CHECK(p.age == 28);

    person_set_name(&p, "A very very very long name that does not fit");
    CHECK(strlen(p.name) == 31);                     /* truncated safely */
    person_set_name(&p, "Ben");
    CHECK(strcmp(p.name, "Ben") == 0);
    printf("  "); person_print(&p);

    struct Person group[3] = {
        {"Alice", 30, {1995, 1, 1}},
        {"Bob",   20, {2005, 2, 2}},
        {"Chloe", 25, {2000, 3, 3}},
    };
    CHECK(person_average_age(group, 3) == 25.0);
    printf("  average age of group = %.1f\n", person_average_age(group, 3));
}

/* ------------------------------------------------------------ */
int main(void) {
    printf("Algorithmics and Data Structures - Session 2 tests\n");
    test_primitive_types();
    test_array();
    test_singly_list();
    test_doubly_list();
    test_circular_list();
    test_stack();
    test_queues();
    test_hash_table();
    test_structs();

    printf("\n==============================\n");
    printf("%d checks run, %d failed\n", tests_run, tests_failed);
    printf(tests_failed == 0 ? "ALL TESTS PASSED\n" : "SOME TESTS FAILED\n");
    return tests_failed == 0 ? 0 : 1;
}
