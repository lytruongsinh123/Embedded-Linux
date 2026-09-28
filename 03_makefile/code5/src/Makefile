.PHONY: rule1 all clean build1 build2

CC:=gcc
CFLAGS:=-I.
INC_FILES:=hello.h

build1: hello.c
	$(CC) $(CFLAGS) -c -o hello.o hello.c
build2: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c
rule1: hello.o main.o
	$(CC) -o hello hello.o main.o $(CFLAGS)
all:
	$(CC) -o hello hello.c main.c $(CFLAGS)
clean:
	rm -rf hello