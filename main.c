#include <stdio.h>
#include"Radix.h"
//#include "Hashed_Index.h"
#include <stdlib.h>
//#include "relations.h"
#define BUF_SIZE 33
#include <inttypes.h>







int main() {
char  filename[]="/home/dimitris/CLionProjects/jj2019/relA";
int size;
size= sizeof(uint64_t);

 //  get_table(filename);

    int rows,nedded_column,columns,n;

    n=0;
    rows=10;
    nedded_column=1;
    columns=2;
    char buffer[BUF_SIZE];
    buffer[BUF_SIZE - 1] = '\0';


 /*   int i;

    Table_Info* retur=malloc(sizeof(Table_Info));
    retur->Table=malloc(sizeof(int*)*rows);
    for(i=0;i<rows;i++)
        retur->Table[i]=malloc(sizeof(int)*columns);
    retur->rows=rows;
    retur->columns=2;


    int test[10][2]={{1,3},{2,4},{3,7},{4,7},{5,2},{6,2},{7,1},{8,5},{9,5},{10,2}};





    for(i=0;i<rows;i++){
        retur->Table[i][1]=test[i][nedded_column];
        retur->Table[i][0]=i;
    }
*/
 Table_Info* table;
    Combined_Structs* combined_structs;
    combined_structs = radix_Sort(n, get_table(filename));





    return 0;
}


