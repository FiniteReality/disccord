.PHONY: all clean

# C compiler
CC=gcc
FLAGS=-I../include -ldisccord
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native

SOURCES=client_create.c client_connect.c
TESTS=$(SOURCES:.c=_test)

%_test: %.c
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $<
	valgrind ./$@

clean:
	rm -rf *.test
	rm -rf *.so

all: $(TESTS)