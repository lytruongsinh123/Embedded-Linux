.PHONY: reader writer

CC := gcc

CFLAGS := -I.

reader: reader.o
	$(CC) $(CFLAGS) -o reader reader.o
writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o