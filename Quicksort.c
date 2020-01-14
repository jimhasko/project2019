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

            while (partition[columns][i] <= partition[columns][pivot] && i < to) {

                i++;
            }
            while (partition[columns][j] > partition[columns][pivot]) {

                j--;
            }
            if (i < j) {


                for(n=0;n<columns;n++){
                idtemp = partition[n][i];
                partition[n][i] = partition[n][j];
                partition[n][j] = idtemp;}

                temp = partition[columns][i];
                partition[columns] [i]= partition[columns] [j];
                partition[columns] [j] = temp;

            }
        }

        temp = partition[columns][pivot];
        partition[columns][pivot]= partition[columns][j];
        partition[columns][j] = temp;

        for(n=0;n<columns;n++){
            idtemp = partition[n][pivot];
            partition[n][pivot] = partition[n][j];
            partition[n][j] = idtemp;}

        quicksort(partition, from, j - 1,columns);
        quicksort(partition, j + 1, to,columns);
    }
}

//=================================================================================================================
//=================================================================================================================