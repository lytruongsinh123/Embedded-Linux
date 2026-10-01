CC := gcc

CFLAGS := -Wall -Wextra

all: stream_client stream_server

stream_server: stream_server.o
	$(CC) $(CFLAGS) -o stream_server stream_server.o
stream_client: stream_client.o
	$(CC) $(CFLAGS) -o stream_client stream_client.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o stream_client stream_server