#include <stdio.h>
#include <time.h>
#include "relations.h"
#include <inttypes.h>



int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer


    List_of_Tables master_table;
    int this_is_fine = 0;

    this_is_fine = do_the_work(master_table, argc, argv);


    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    printf("Time elapsed: %.5f\n", elapsed);

    return 0;
}


