CC := gcc

CFLAGS := -Wall -Wextra

all: datagram_server datagram_client

datagram_server: datagram_server.o
	$(CC) $(CFLAGS) -o datagram_server datagram_server.o
datagram_client: datagram_client.o
	$(CC) $(CFLAGS) -o datagram_client datagram_client.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o datagram_client datagram_server