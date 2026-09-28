.PHONY: rule1 all clean

CC:=gcc
CFLAGS:=-I.
INC_FILES:=hello.h

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
rule1: hello.o main.o
	$(CC) $(CFLAGS) -o hello hello.o main.o
clean:
	rm -rf hello hello.o hello.o main.o