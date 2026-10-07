CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRC = $(wildcard *.c)

all: test_runner

test_runner: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

test: test_runner
	./test_runner

clean:
	rm -f test_runner test_runner.exe

.PHONY: all test clean
