.PHONY: all clean

# C compiler
CC=gcc
FLAGS=-I../include -L../bin -ldisccord
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native

SOURCES=create_client.c
TESTS=$(SOURCES:.c=_test)


clean:
	rm -rf *_test
	rm -rf *.so

$(TESTS): $(SOURCES)
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $<
	export LD_LIBRARY_PATH=../bin && valgrind ./$@

all: $(TESTS)