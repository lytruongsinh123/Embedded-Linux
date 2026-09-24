.PHONY: read write clean

CC := gcc

CFLAGS := -I.
LDFLAGS := -lrt

read: read.o
	$(CC) -o read read.o $(LDFLAGS)

write: write.o
	$(CC) -o write write.o $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o read write