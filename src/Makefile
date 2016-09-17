.PHONY: all clean

# C compiler
CC=gcc
AR=ar
# Compiler flags
CFLAGS=-I.

SOURCES=discord.c
OBJECTS=$(SOURCES:.c=.o)
LIBRARY=disccord

.c.o:
	$(CC) -c -o $@ $< $(CLFAGS)

lib$(LIBRARY).a: $(OBJECTS)
	$(AR) -cvq $@ $(OBJECTS)

clean:
	rm -rf *.o
	rm -rf *.a

all: $(SOURCES) lib$(LIBRARY).a
