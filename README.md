# Algorithmics and Data Structures - Session 2

Implementation in C of all the data structures seen in Session 2 (ENSISA, Université Haute-Alsace),
with a test program that checks every operation.

## Contents

| Structure | Files | Main operations |
|---|---|---|
| Primitive types | `test_main.c` | prints `sizeof` of each type |
| Array (fixed size) | `array.h / array.c` | get O(1), insert O(n), delete O(n), search |
| Singly linked list | `singly_list.h / .c` | push/pop front & back, get, search, insert after, remove |
| Doubly linked list | `doubly_list.h / .c` | push/pop front & back in O(1), remove node, print both ways |
| Circular linked list | `circular_list.h / .c` | push front/back, pop front, contains, rotate |
| Stack (LIFO) | `stack.h / stack.c` | push, pop, peek (all O(1)) |
| Queues (FIFO) | `queue.h / queue.c` | simple queue, circular queue, priority queue |
| Hash table | `hash_table.h / .c` | put, get, remove, collision handling by chaining |
| Structs | `person.h / person.c` | nested structs, `.` vs `->`, arrays of structs |

## Project layout

Each structure has a header file (`.h`, type definitions and function prototypes)
and an implementation file (`.c`). `test_main.c` contains the tests for every structure.

## Build and run the tests

With `make`:

```bash
make test
```

Without `make` (works on Windows with MinGW too):

```bash
gcc -Wall -Wextra -std=c99 *.c -o test_runner
./test_runner
```

Expected end of output:

```
133 checks run, 0 failed
ALL TESTS PASSED
```

## Notes

- **Stack push:** the slide writes `S[n-1] <- x`, but `S[n-1]` is the current top.
  The new element must go to `S[n]`, then `n <- n+1` (this is what `stack_push` does).
- **Circular list:** only a pointer to the last node is stored; the first node is `tail->next`,
  which makes insertion at both ends O(1).
- **Hash table:** uses the hash function from the slides (sum of ASCII codes % size).
  With 4 buckets, `"Ali"` and `"Ken"` both go to index 2, exactly like the collision example in the slides.
