.PHONY: all static link

all:
	gcc -c main.c -o obj/main.o -I./inc
	gcc -c src/hello.c -o obj/hello.o -I./inc
	gcc -c src/sum.c -o obj/sum.o -I./inc
static:
	ar rcs lib/static/libsum.a obj/sum.o obj/hello.o
link:
	gcc obj/main.o -Llib/static -lsum -o bin/exe