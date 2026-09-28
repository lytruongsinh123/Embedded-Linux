.PHONY: build runA runB

CC := gcc
CFLAGS := -I.

build: processA.o processB.o
	$(CC) $(CFLAGS) -o processA processA.o
	$(CC) $(CFLAGS) -o processB processB.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
runA: 
	./processA
runB:
	./processB