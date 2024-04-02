CC ?= clang
CFLAGS ?= -std=c11 -g -Wall -Wextra -Wpedantic

SRC = $(wildcard src/*.c)

.PHONY: run clean

build:
	$(CC) $(CFLAGS) $(SRC) -o bin/main

run:
	bin/main $(ARGS)

clean:
	rm -rf $(wildcard bin/*)

