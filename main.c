#include <stdio.h>
#include"Radix.h"
#include <stdlib.h>
#include <inttypes.h>
#include "Quickshort.h"
#include <time.h>
#include "shhh.h"






int main() {
    clock_t start = clock();
char  filename1[]="/home/dimitris/CLionProjects/jj2019/relA";
    char  filename2[]="/home/dimitris/CLionProjects/jj2019/relB";



   int i,needed_column,j,k,l;
   needed_column=2;




results* one;
    results* two;
    one=big_short(filename1,needed_column);

    two=big_short(filename2,needed_column);





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


