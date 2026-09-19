.PHONY: clean create_thread exit_thread detaching_thread multil_thread

CC := gcc

CFLAGS := -I. -pthread

create_thread: create_thread.o
	$(CC) $(CFLAGS) -o create_thread create_thread.o
exit_thread: exit_thread.o
	$(CC) $(CFLAGS) -o exit_thread exit_thread.o
detaching_thread: detaching_thread.o
	$(CC) $(CFLAGS) -o detaching_thread detaching_thread.o
multil_thread: multil_thread.o
	$(CC) $(CFLAGS) -o multil_thread multil_thread.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o
	rm -f create_thread
	rm -f exit_thread
