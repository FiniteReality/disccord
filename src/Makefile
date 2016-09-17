.PHONY: all clean install

# C compiler
CC=gcc
AR=ar
# Compiler flags
FLAGS=-std=gnu99 -I../include -lpthread
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native
LDFLAGS=-shared
ARFLAGS=-rv

SOURCES=client.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=libdisccord.so

INSTALL=../bin/

.c.o:
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS) -o $@ $<

install: $(TARGET)
	if [ ! -d "$(INSTALL)" ]; then mkdir $(INSTALL); fi
	cp $(TARGET) $(INSTALL)$(TARGET)

clean:
	rm -rf *.o
	rm -rf *.so
	rm -rf $(INSTALL)

all: $(SOURCES) $(TARGET) install
