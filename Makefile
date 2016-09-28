.PHONY: all lib clean test install

clean:
	make -C lib clean
	make -C test clean

lib:
	make -C lib all

all: lib

test: all
	make -C test all

install:
	make -C src install

uninstall:
	make -C src uninstall