.PHONY: all clean

# C compiler
CC=gcc
AR=ar
# Compiler flags
FLAGS=-std=gnu99 -I../include
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native
LDFLAGS=-shared
ARFLAGS=-rv

SOURCES=client.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=libdisccord.so

.c.o:
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -rf *.o
	rm -rf *.so

all: $(SOURCES) $(TARGET)
