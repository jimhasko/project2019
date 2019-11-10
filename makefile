CC=gcc
CFLAGS=-I -Wall -O2

all:  Radix  Quicksort Result_List main

main: Quicksort.o Radix.o Result_List.o 
	$(CC)  $(CFLAGS) -o myexe main.c Quicksort.o Radix.o Result_List.o 

Radix: Radix.c Radix.h
	$(CC) -c Radix.c $(CFLAGS)

Quicksort: Quicksort.c Quicksort.h
	$(CC) -c Quicksort.c $(CFLAGS)

Result_List: Result_List.c  Result_List.h
	$(CC) -c Result_List.c $(CFLAGS)
	
clean: 
	$(RM) myexe *.o *~
