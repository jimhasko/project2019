#include <stdio.h>
#include"Radix.h"
#include <stdlib.h>
#include <inttypes.h>
#include "quicjshort.h"
#include <time.h>
#include "shhh.h"






int main() {

char  filename1[]="/home/dimitris/CLionProjects/jj2019/relA";
    char  filename2[]="/home/dimitris/CLionProjects/jj2019/relB";



   int i,needed_column,j,k,l;
   needed_column=2;




//Table_Info* table;
//table=get_table(filename1,needed_column);
results* one;
    results* two;
    one=big_short(filename1,needed_column);
    printf("\n A \n");
    two=big_short(filename2,needed_column);
    printf("\n B \n");
//printf("\n \n \n");

/*

j=0;
for(i=0;i<table->rows-1;i++){
    if(not_yet->matrix[i][1]<=not_yet->matrix[i+1][1]){
        j++;
    }
}
    printf("j %d rows %d \n",j,table->rows);
j=0;
uint64_t a,b,c;
    for(i=0;i<table->rows-1;i++) {
        a=not_yet->matrix[i][1];
        b=table->TableA[not_yet->matrix[i][0]][1];
        c=table->TableA[1948][1];
      //  print(table,1945,1955);
        k=not_yet->matrix[i][0];
        k=table->TableA[not_yet->matrix[i][0]][0];

        if(not_yet->matrix[i][1]==table->TableA[not_yet->matrix[i][0]][needed_column-1]){

                    j++;}
    }
printf("j %d ples %d",j,table->rows);
*/
//free_table(table);

   // printf("not yet %d ",not_yet->rows);


    clock_t start = clock();

Head_join* test;
test=join(one,two);

    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;

    printf("\nTime elapsed: %.5f\n", elapsed*10);


j=1;
int max;
List_join* kl;
kl=test->first;
max=test->size;
while(kl!=NULL){
    if(j>1)
        max=120;
    for(i=0;i<max;i++){
       printf("::: %d | %d \n ",kl->id_matrix[i][0],kl->id_matrix[i][1]);

    }
    j++;
printf("\n next bucket is %d\n",j);
    kl=kl->next;
}
printf(" %d ",test->size);




    return 0;
}


