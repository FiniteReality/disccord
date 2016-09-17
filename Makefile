.PHONY: all clean

clean:
	make -C src clean 

src:
	make -C src

all: src
