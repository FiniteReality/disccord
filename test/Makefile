.PHONY: all clean

# C compiler
CC=gcc
FLAGS=-I../include -L../src -ldisccord
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native

SOURCES=get_user.c
TESTS=$(SOURCES:.c=)

clean:
	rm -rf *.test

$(TESTS): $(SOURCES)
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $<
	valgrind ./$@

all: $(SOURCES) $(TESTS)