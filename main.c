#include <stdio.h>
#include"Radix.h"
#include <stdlib.h>
#include <inttypes.h>
#include "quicjshort.h"
#include <time.h>







int main() {
    clock_t start = clock();
char  filename[]="/home/dimitris/CLionProjects/jj2019/relA";




   int i,needed_column,j;
   needed_column=2;




Table_Info* table;
table=get_table(filename,needed_column);
results* not_yet;

    not_yet=big_short(filename,needed_column);
//printf("\n \n \n");



j=0;
for(i=0;i<table->rows-1;i++){
    if(not_yet->matrix[i][1]<=not_yet->matrix[i+1][1]){
        j++;
    }else{
     //   printf("fuuuckkkk  %d \n",i);
    }


}

printf("j %d rows %d",j,table->rows);

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("not yet %d ",not_yet->rows);
    printf("\nTime elapsed: %.5f\n", elapsed*10);


    return 0;
}


