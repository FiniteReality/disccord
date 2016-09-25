.PHONY: all clean

# C compiler
CC=gcc
FLAGS=-I../include -L../src -ldisccord -lssl -lcrypto
CFLAGS=-std=gnu11 -fPIC -Wpedantic -Wall -Wextra -march=native

SOURCES=client_create.c client_connect.c
TESTS=$(SOURCES:.c=_test)

%_test: %.c
	$(CC) $(FLAGS) $(CFLAGS) -o $@ $<
	export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:../src && valgrind $(VALGRIND_OPTS) ./$@

clean:
	rm -rf *_test
	rm -rf *.so

all: clean $(TESTS)