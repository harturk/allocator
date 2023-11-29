CC = gcc
CFLAGS = -Wall -O2

PROG = main
SOURCES = main.c list.c myMemory.c
OBJECTS = $(SOURCES:.c=.o)


$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@


# // remove command based on OS
ifdef OS
   RM = -del
else
   ifeq ($(shell uname), Linux)
      RM = rm
   endif
endif

clean:
	-@ $(RM) -f $(OBJECTS) $(PROG)
