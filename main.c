#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include"Radix.h"
#include "relations.h"
#include <inttypes.h>
int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer
    char *filename1 = malloc(SizeofDataFileName * sizeof(char));
    strcpy(filename1, argv[1]);
    char *filename2 = malloc(SizeofDataFileName * sizeof(char));
    strcpy(filename2, argv[2]);
    int needed_columnA, needed_columnB;

    needed_columnA = 1;
    needed_columnB = 1;


    char* name="/home/dimitris/CLionProjects/jj2019/workloads/small/r0";
    char* name2="/home/dimitris/CLionProjects/jj2019/workloads/small/r1";
    char* name3="/home/dimitris/CLionProjects/jj2019/workloads/small/r2";
    char* name4="/home/dimitris/CLionProjects/jj2019/workloads/small/r3";
    char* name5="/home/dimitris/CLionProjects/jj2019/workloads/small/r4";
    char*str="0 2 4 1 3|0.1=1.2&1.0=2.1&0.1=0.2&3.1=4.1&4.2=0.1&3.2=2.2&0.1>3000|0.0 1.1";
    List_of_Tables master_table;
    master_table.num_of_tables=5;
    master_table.tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table.num_of_tables);
    master_table.tables[0]=fill(name,0);
    master_table.tables[1]=fill(name2,1);
    master_table.tables[2]=fill(name3,2);
    master_table.tables[3]=fill(name4,3);
    master_table.tables[4]=fill(name5,4);
just_transfer * test;
   test= analise(str,&master_table);

   run_filters(&master_table,test);
     results *not_yetA, *not_yetB;

    info_node* join_resutl;

   // not_yetA = big_short(filename1, needed_columnA);
  //  not_yetB = big_short(filename2, needed_columnB);
  //
    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    printf("Time elapsed: %.5f\n", elapsed);

   // list_destruction(&join_resutl);

    return 0;
}


