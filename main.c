#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "relations.h"
#include <inttypes.h>



int main(int argc, char** argv) {

    clock_t start = clock(); //Start timer
int j;
    List_of_Tables master_table;
   /* char* name="/home/dimitris/CLionProjects/jj2019/workloads/small/r0";
    char* name2="/home/dimitris/CLionProjects/jj2019/workloads/small/r1";
    char* name3="/home/dimitris/CLionProjects/jj2019/workloads/small/r2";
    char* name4="/home/dimitris/CLionProjects/jj2019/workloads/small/r3";
    char* name5="/home/dimitris/CLionProjects/jj2019/workloads/small/r4";
    char* name6="/home/dimitris/CLionProjects/jj2019/workloads/small/r5";
    master_table.num_of_tables=5;
    master_table.tables=(Single_Table*)malloc(sizeof(Single_Table)*master_table.num_of_tables);
    master_table.tables[0]=fill(name,0);
    master_table.tables[1]=fill(name2,1);
    master_table.tables[2]=fill(name3,2);
    master_table.tables[3]=fill(name4,3);
    master_table.tables[4]=fill(name5,4);
    master_table.tables[5]=fill(name6,5);
    */





    master_table = get_data_from_file( master_table, argc, argv);
    char*str="9 1 12|0.2=1.0&1.0=2.1&2.2=1.0&0.2<2685|2.0";
    just_transfer * test;
    middle* bad_word;
    test = analise(str,&master_table);

    bad_word=run_filters(&master_table,test);

    athrisma(bad_word,test,&master_table);
    free_big(&master_table);
    clock_t stop = clock(); //End timer
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;


    printf("Time elapsed: %.5f\n", elapsed);

   // list_destruction(&join_resutl);

    return 0;
}


