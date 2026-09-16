.PHONY: argu fork execl

CC := gcc
CFLAGS := -I.

argu: arguments.o
	$(CC) $(CFLAGS) -o arguments arguments.o
fork: fork.o
	$(CC) $(CFLAGS) -o fork fork.o
execl: execl.o
	$(CC) $(CFLAGS) -o execl execl.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
