CC = gcc
CFLAGS = -Wall -Wextra

TARGETS = receiver sender

all: $(TARGETS)

receiver: receiver.o
	$(CC) $(CFLAGS) -o receiver receiver.o

sender: sender.o
	$(CC) $(CFLAGS) -o sender sender.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGETS)