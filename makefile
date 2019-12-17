CC=gcc
CFLAGS=-I -Wall -O2 -g

all:  Relations Radix Quicksort Result_List main

main: Quicksort.o Radix.o Result_List.o relations.o
	$(CC)  $(CFLAGS) -o myexe main.c Quicksort.o Radix.o Result_List.o relations.o

Radix: Radix.c Radix.h
	$(CC) -c Radix.c $(CFLAGS)

Quicksort: Quicksort.c Quicksort.h
	$(CC) -c Quicksort.c $(CFLAGS)

Result_List: Result_List.c  Result_List.h
	$(CC) -c Result_List.c $(CFLAGS)

Relations: relations.c  relations.h
	$(CC) -c relations.c $(CFLAGS)

clean: 
	$(RM) myexe *.o *~
