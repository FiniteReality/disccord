.PHONY: all src clean test install

clean:
	make -C src clean
	make -C test clean 

src:
	make -C src all

all: src

test: all
	make -C test all

install:
	make -C src install

uninstall:
	make -C src uninstall