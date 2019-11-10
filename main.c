#include <stdio.h>
#include <time.h>
#include"Radix.h"
#include "Result_List.h"


int main() {

    clock_t start = clock();
    char filename1[] = "C:\\UoA\\project2019\\relA";
    char filename2[] = "C:\\UoA\\project2019\\relB";

    int i, needed_columnA, needed_columnB, j;
    needed_columnA = 2;
    needed_columnA = 2;

    /*Table_Info *table;
    table = get_table(filename, needed_column);*/
    results *not_yetA, *not_yetB;

    not_yetA = big_short(filename1, needed_columnA);
    //printf("\n \n \n");
    not_yetB = big_short(filename2, needed_columnB);

    /*j = 0;
    for (i = 0; i < table->rows - 1; i++) {

        if (not_yet->matrix[i][1] <= not_yet->matrix[i + 1][1]) {
            j++;
        } else {
            //   printf("fuuuckkkk  %d \n",i);
        }
    }

    printf("j %d rows %d", j, table->rows);*/

    i= sizeof(struct node_type);
    info_node* join_resutl;

    join_resutl = join_matrices(not_yetA, not_yetB);



    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
   // printf("not yet %d ", not_yet->rows);
    printf("\nTime elapsed: %.5f\n", elapsed);

    list_destruction(&join_resutl);

    return 0;
}


