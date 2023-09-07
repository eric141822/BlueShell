CC=gcc
CCFLAGS=-Wall -Wundef -Wshadow -Wpointer-arith -Wcast-align \
	-pedantic -O3

EXECUTABLES=build \
build/blueshell.out \

build/blueshell.out: src/cmds.c src/blueshell.c
	$(CC) $(CCFLAGS) $^ -o $@

build:
	mkdir -p build

.PHONY: clean all

clean:
	$(RM) -r build/*.out
	rmdir build