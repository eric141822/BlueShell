CC=gcc

EXECUTABLES=shell \

all: $(EXECUTABLES)

shell: shell.c
	$(CC) -o $@ $^

.PHONY: clean all

clean:
	rm -f $(EXECUTABLES)