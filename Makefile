.PHONY: all src clean test

clean:
	make -C src clean
	make -C test clean 

src:
	make -C src all

all: src

test: all
	make -C test all