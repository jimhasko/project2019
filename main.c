#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include"Radix.h"


int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer
    char *filename1 = malloc(SizeofDataFileName * sizeof(char));
    strcpy(filename1, argv[1]);
    char *filename2 = malloc(SizeofDataFileName * sizeof(char));
    strcpy(filename2, argv[2]);
    int needed_columnA, needed_columnB;

    needed_columnA = 1;
    needed_columnB = 1;

    results *not_yetA, *not_yetB;

    info_node* join_resutl;

    not_yetA = big_short(filename1, needed_columnA);
    not_yetB = big_short(filename2, needed_columnB);

    join_resutl = join_matrices(not_yetA, not_yetB);

    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;



    printf("Time elapsed: %.5f\n", elapsed);

    list_destruction(&join_resutl);

    return 0;
}


