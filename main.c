#include <stdio.h>
#include"Radix.h"
#include <stdlib.h>
#include <inttypes.h>
#include "Quickshort.h"
#include <time.h>
#include "shhh.h"



int main() {

    clock_t start = clock(); //Start timer
    char filename1[] = "C:\\UoA\\project2019\\relA";
    char filename2[] = "C:\\UoA\\project2019\\relB";
    int needed_columnA, needed_columnB;

    needed_columnA = 2;
    needed_columnB = 2;

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


