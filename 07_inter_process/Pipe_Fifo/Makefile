.PHONY: createpipe creatpipe1 processpipe customer_process producer_process

CC := gcc

CFLAGS := -I.

createpipe1: createpipe1.o
	$(CC) $(CFLAGS) -o createpipe1 createpipe1.o
createpipe0: createpipe0.o
	$(CC) $(CFLAGS) -o createpipe0 createpipe0.o
processpipe0: processpipe0.o
	$(CC) $(CFLAGS) -o processpipe0 processpipe0.o
customer_process: customer_process.o
	$(CC) $(CFLAGS) -o customer_process customer_process.o
producer_process: producer_process.o
	$(CC) $(CFLAGS) -o producer_process producer_process.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	rm -f *.o

