.PHONY: build clean

PATH_OUTPUT := output
PRO_DIR := .
INCLUDE_DIRS := $(PRO_DIR)/include
build: main.o sum.o
	gcc $(PATH_OUTPUT)/main.o $(PATH_OUTPUT)/sum.o -o $(PATH_OUTPUT)/app.exe
	./$(PATH_OUTPUT)/app.exe
main.o: source/main.c 
	gcc -I$(INCLUDE_DIRS) -c $< -o $(PATH_OUTPUT)/$@
sum.o: source/sum.c
	gcc -I$(INCLUDE_DIRS) -c $< -o $(PATH_OUTPUT)/$@
clean:
	rm -rf $(PATH_OUTPUT)/*