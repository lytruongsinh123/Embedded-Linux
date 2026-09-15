.PHONY: argu fork

CC := gcc
CFLAGS := -I.

argu: arguments.o
	$(CC) $(CFLAGS) -o arguments arguments.o
fork: fork.o
	$(CC) $(CFLAGS) -o fork fork.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
