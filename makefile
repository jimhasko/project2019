CC=gcc
CFLAGS=-I -Wall -O2

all:  Relations Radix Quicksort Result_List main

main: Quicksort.o Radix.o Result_List.o relations.o
	$(CC)  $(CFLAGS) -o myexe main.c Quicksort.o Radix.o Result_List.o relations.o -lm -lpthread

Radix: Radix.c Radix.h
	$(CC) -c Radix.c $(CFLAGS) -lm -lpthread

Quicksort: Quicksort.c Quicksort.h
	$(CC) -c Quicksort.c $(CFLAGS) -lm -lpthread

Result_List: Result_List.c  Result_List.h
	$(CC) -c Result_List.c $(CFLAGS) -lm -lpthread

Relations: relations.c  relations.h
	$(CC) -c relations.c $(CFLAGS) -lm -lpthread

clean: 
	$(RM) myexe *.o *~
