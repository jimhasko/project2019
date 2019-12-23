#include <stdio.h>
#include <time.h>
#include "relations.h"
#include <inttypes.h>


int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer

    List_of_Tables* master_table;
    int this_is_fine = 0;
master_table=(List_of_Tables*)malloc(sizeof(List_of_Tables));
    this_is_fine = do_the_work(master_table, argc, argv);

    if(this_is_fine == true) {

        printf("\n\nFuck Yeah!\n\n");
    }
    else {

        printf("\n\nThis is not fine ;(\n\n");
        return 1;
    }

    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    printf("Time elapsed: %.5f\n", elapsed);

    return 0;
}


