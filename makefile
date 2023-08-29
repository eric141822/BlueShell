CC=gcc
FLAGS=-Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align \
	-pedantic -O3
EXECUTABLES=blueshell \

all: $(EXECUTABLES)

blueshell: blueshell.c
	$(CC) $(FLAGS) -o $@ $^

.PHONY: clean all

clean:
	rm -f $(EXECUTABLES)