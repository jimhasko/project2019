//
// Created by dimitris on 07/11/2019.
//

#include "quicjshort.h"
#include <inttypes.h>

void quicksort(uint64_t partition[1000],int first,int last){

    int i, j, pivot;
    uint64_t temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(partition[i]<=partition[pivot]&&i<last)
                i++;
            while(partition[j]>partition[pivot])
                j--;
            if(i<j){
                temp=partition[i];
                partition[i]=partition[j];
                partition[j]=temp;
            }
        }

        temp=partition[pivot];
        partition[pivot]=partition[j];
        partition[j]=temp;
        quicksort(partition,first,j-1);
        quicksort(partition,j+1,last);

    }
}