.PHONY: build

CC := gcc
CFLAGS := -I.

build: read_write.o
	$(CC) $(CFLAGS) -o read_write $<

read_write.o: read_write.c
	$(CC) $(CFLAGS) -c -o $@ $<