#include "Quicksort.h"

//=================================================================================================================
void quicksort(uint64_t **partition, int from, int to,int columns) {

    int i, j,n, pivot, idtemp;
    uint64_t temp;
//uint64_t **partition=table->TableB;
//columns=table->columns;
    if (from < to) {
        pivot = from;
        i = from;
        j = to;

        while (i < j) {

            while (partition[i][columns] <= partition[pivot][columns] && i < to) {

                i++;
            }
            while (partition[j][columns] > partition[pivot][columns]) {

                j--;
            }
            if (i < j) {


                for(n=0;n<columns;n++){
                idtemp = partition[i][n];
                partition[i][n] = partition[j][n];
                partition[j][n] = idtemp;}

                temp = partition[i][columns];
                partition[i][columns] = partition[j][columns];
                partition[j][columns] = temp;

            }
        }

        temp = partition[pivot][columns];
        partition[pivot][columns] = partition[j][columns];
        partition[j][columns] = temp;

        for(n=0;n<columns;n++){
            idtemp = partition[pivot][n];
            partition[pivot][n] = partition[j][n];
            partition[j][n] = idtemp;}

        quicksort(partition, from, j - 1,columns);
        quicksort(partition, j + 1, to,columns);
    }
}

//=================================================================================================================
//=================================================================================================================