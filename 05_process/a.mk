.PHONY: argu fork execl kill wait waitstatus zombie

CC := gcc
CFLAGS := -I.

argu: arguments.o
	$(CC) $(CFLAGS) -o arguments arguments.o
fork: fork.o
	$(CC) $(CFLAGS) -o fork fork.o
execl: execl.o
	$(CC) $(CFLAGS) -o execl execl.o
kill: kill.o
	$(CC) $(CFLAGS) -o kill kill.o
wait: wait.o
	$(CC) $(CFLAGS) -o wait wait.o
waitstatus: waitstatus.o
	$(CC) $(CFLAGS) -o waitstatus waitstatus.o
zombie: zombie.o
	$(CC) $(CFLAGS) -o zombie zombie.o
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
