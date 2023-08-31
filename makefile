CC=gcc
CCFLAGS=-Wall -Wundef -Wshadow -Wpointer-arith -Wcast-align \
	-pedantic -O3
EXECUTABLES=blueshell \

all: $(EXECUTABLES)

blueshell: cmds.c blueshell.c
	$(CC) $(CCFLAGS) $^ -o $@ 

.PHONY: clean all

clean:
	rm -f $(EXECUTABLES)