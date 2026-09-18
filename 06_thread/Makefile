.PHONY: clean create_thread

CC := gcc

CFLAGS := -I. -pthread

create_thread: create_thread.o
	$(CC) $(CFLAGS) -o create_thread create_thread.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o
	rm -f create_thread
