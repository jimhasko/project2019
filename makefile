CC=gcc
CFLAGS=-I -Wall -O2

all:  Relations Radix Quicksort Result_List main

main: Quicksort.o Radix.o Result_List.o relations.o
	$(CC)  $(CFLAGS) -o myexe main.c Quicksort.o Radix.o Result_List.o relations.o -lm

Radix: Radix.c Radix.h
	$(CC) -c Radix.c $(CFLAGS) -lm

Quicksort: Quicksort.c Quicksort.h
	$(CC) -c Quicksort.c $(CFLAGS) -lm

Result_List: Result_List.c  Result_List.h
	$(CC) -c Result_List.c $(CFLAGS) -lm

Relations: relations.c  relations.h
	$(CC) -c relations.c $(CFLAGS) -lm

clean: 
	$(RM) myexe *.o *~
