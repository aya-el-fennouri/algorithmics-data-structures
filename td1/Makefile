CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: fibonacci primes

fibonacci: fibonacci.c
	$(CC) $(CFLAGS) -o $@ $<

primes: primes.c
	$(CC) $(CFLAGS) -o $@ $<

run: all
	./fibonacci
	./primes

clean:
	rm -f fibonacci primes fibonacci.exe primes.exe

.PHONY: all run clean
