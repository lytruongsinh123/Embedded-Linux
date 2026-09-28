.PHONY: sigint sigkill sigterm kill_func block

CC := gcc

CFLAGS := -I.

sigint: sigint.o
	$(CC) $(CFLAGS) -o sigint sigint.o
sigkill: sigkill.o
	$(CC) $(CFLAGS) -o sigkill sigkill.o
sigterm: sigterm.o
	$(CC) $(CFLAGS) -o sigterm sigterm.o
kill_func: kill_func.o
	$(CC) $(CFLAGS) -o kill_func kill_func.o
block: block.o
	$(CC) $(CFLAGS) -o block block.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o

