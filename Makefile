CC = gcc
CFLAGS = -Wall -O2

all: main

main: main.o list.o mymemory.o
	$(CC) $(CFLAGS) -o main main.o list.o mymemory.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

mymemory.o: mymemory.c
	$(CC) $(CFLAGS) -c mymemory.c

clean:
	rm -f *.o main
