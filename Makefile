CC = gcc
CFLAGS = -Wall -O2

PROG = main
SOURCES = main.c list.c mymemory.c mainList.c
OBJECTS = $(SOURCES: .c=.o)


$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@



# main: main.o list.o mymemory.o mainlist.o 
# 	$(CC) $(CFLAGS) -o main.o list.o mymemory.o mainlist.o

# main.o: main.c
# 	$(CC) $(CFLAGS) -c main.c

# list.o: list.c
# 	$(CC) $(CFLAGS) -c list.c

# mymemory.o: mymemory.c
# 	$(CC) $(CFLAGS) -c mymemory.c

# mainlist.o: mainlist.c
# 	$(CC) $(CFLAGS) -c mainlist.c


clean:
	-@ rm -f $(OBJECTS) $(PROG)
