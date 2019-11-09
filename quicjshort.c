//
// Created by dimitris on 07/11/2019.
//
#include "Radix.h"
#include "quicjshort.h"
#include <inttypes.h>
#include <stdio.h>

void quicksort(uint64_t ** partition,int from,int to){

    int i, j, pivot,idtemp;
    uint64_t temp;

    if(from<to){
        pivot=from;
        i=from;
        j=to;

        while(i<j){

            while(partition[i][1]<=partition[pivot][1]&&i<to){

                i++;

            }
            while(partition[j][1]>partition[pivot][1]){

                j--;

            }
            if(i<j){

                temp=partition[i][1];
                idtemp=partition[i][0];
                partition[i][1]=partition[j][1];
                partition[i][0]=partition[j][0];
                partition[j][1]=temp;
                partition[j][0]=idtemp;
            }
        }

        temp=partition[pivot][1];
        partition[pivot][1]=partition[j][1];
        partition[j][1]=temp;
        idtemp=partition[pivot][0];
        partition[pivot][0]=partition[j][0];
        partition[j][0]=idtemp;
        quicksort(partition,from,j-1);
        quicksort(partition,j+1,to);

    }

   // for(i=from;i<=to;i++){
    //    printf("%d : %"PRIu64 " || %d  \n",partition[i][0],partition[i][1],i);
  //  }
printf("\n");
}