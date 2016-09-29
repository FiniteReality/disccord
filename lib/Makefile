.PHONY: all clean install uninstall

# C compiler
CC=gcc
AR=ar
# Compiler flags
FLAGS=-std=gnu11 -I. -I../include -lpthread -lcJSON -lwebsockets -lssl -lcrypto
CFLAGS=-fPIC -Wpedantic -Wall -Wextra -march=native
LDFLAGS=-shared
ARFLAGS=-rv

SOURCES=websocket.c client.c discord.c
OBJECTS=$(SOURCES:.c=.o)
TARGET=libdisccord.so

INSTALL=/usr/local/lib/

.c.o:
	$(CC) $(FLAGS) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

install: $(TARGET)
	cp $(TARGET) $(INSTALL)$(TARGET)

uninstall: $(INSTALL)$(TARGET)
	rm $(INSTALL)$(TARGET)

clean:
	rm -rf *.o
	rm -rf *.so

all: $(SOURCES) $(TARGET)
