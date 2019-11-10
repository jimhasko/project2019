#include <stdlib.h>
#include <stdio.h>
#include "shhh.h"
#include <inttypes.h>

# define size_mb 120


void list_Add_Join(Head_join **head1, int id1,int id2){
    int i;



    if((*head1)->size==size_mb){
        List_join * temp=malloc(sizeof(List_join));
        temp->id_matrix=malloc(sizeof(int*)*size_mb);
        for(i=0;i<size_mb;i++){
            temp->id_matrix[i]=malloc(sizeof(int)*2);

        }
        temp->id_matrix[0][0]=id1;
        temp->id_matrix[0][1]=id1;

         temp->next=(*head1)->first;
         (*head1)->first=temp;
        (*head1)->size=1;
        (*head1)->buckets++;}
    else{
        i=(*head1)->size;
        (*head1)->first->id_matrix[i][0]=id1;
        (*head1)->first->id_matrix[i][1]=id2;
        (*head1)->size++;


    }

}

Head_join* init_join_List(){
    int i;
    Head_join* temp;
    temp=malloc(sizeof(Head_join));
    temp->size=0;



    List_join * temp2=malloc(sizeof(List_join));
    temp2->id_matrix=malloc(sizeof(int*)*size_mb);
    for(i=0;i<size_mb;i++){
        temp2->id_matrix[i]=malloc(sizeof(int)*2);

    }
    temp->first=temp2;
    temp->buckets=1;
    temp2->next=NULL;
    return temp;

}


Head_join* join(results* table1,results* table2){
    int max,not_max,i,j,founds=0;
    uint64_t a,b;
   if(table2->rows>table1->rows){
       results* temp;
       temp=table1;
       table1=table2;
       table2=temp;
   }
    Head_join* test=init_join_List();
    max=table1->rows;
   not_max=table2->rows;



    for(i=0;i<max;i++){
        for(j=0;j<not_max;j++){
            a=table1->matrix[i][1];
            b=table2->matrix[j][1];
            if(table1->matrix[i][1]<table2->matrix[j][1])
                break;
            if(table1->matrix[i][1]==table2->matrix[j][1]){
                    list_Add_Join(&test,table2->matrix[i][0],table1->matrix[i][0]);
                    founds++;
            }else{
              //  printf(" id %d : %d\n",i,j);
            }




        }




    }
    free_results(table1);
    free_results(table2);

printf(" founds %d",founds);

//    printf(" { %d , %d } \n { %d , %d } \n",test->first->id_matrix[39][0],test->first->id_matrix[39][1],test->first->id_matrix[40][0],test->first->id_matrix[40][0]);
return test;
}


void free_results(results* die){


    int i;
    for(i=0;i<die->rows;i++)
        free(die->matrix[i]);
    free(die->matrix);
    free(die);


}