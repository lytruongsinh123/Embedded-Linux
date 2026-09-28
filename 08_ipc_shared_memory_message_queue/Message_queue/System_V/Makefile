CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = Producer ConsumerA ConsumerB

all: $(TARGETS)

Producer: Producer.o
	$(CC) $(CFLAGS) -o Producer Producer.o

ConsumerA: ConsumerA.o
	$(CC) $(CFLAGS) -o ConsumerA ConsumerA.o

ConsumerB: ConsumerB.o
	$(CC) $(CFLAGS) -o ConsumerB ConsumerB.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)