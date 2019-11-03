#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list_Add_Id(Head **head1, int id){

    Listnode * temp=malloc(sizeof(Listnode));
    temp->id=id;
    temp->next=NULL;
    temp->next=(*head1)->first;
    (*head1)->first=temp;
    (*head1)->size++;
    printf(" id %d  \n",(*head1)->first->id);


}

Head* init_List(){
    Head* temp;
    temp=malloc(sizeof(Head));
    temp->size=0;
    temp->first=NULL;
    return temp;

}


int bithash(int hash_value,int hash_key){

    return   hash_value & ((1<<hash_key)-1);

}


Table_Info* getrow(Table_Info* pi,int column){
    int i;
    Table_Info* retur=malloc(sizeof(Table_Info));
    retur->Table=malloc(sizeof(int*)*pi->rows);
    for(i=0;i<pi->rows;i++)
        retur->Table[i]=malloc(sizeof(int)*2);




    for(i=0;i<pi->rows;i++)
        retur->Table[i][0]=i+1;
    retur->Table[i][1]=pi->Table[i][column];

    retur->columns=2;
    retur->rows=pi->rows;

    return  retur;

}



void print(Table_Info* table){
    printf("PRINTING!!\n");
    int i,j;
    for(i=0;i<table->rows;i++)
    {

        for(j=0;j<table->columns;j++){

            printf(" %d ",table->Table[i][j]);

        }
        printf("\n");

    }



}




Combined_Structs* radix_Sort(int n, Table_Info *table){

    // int test[10][2]={{1,3},{2,4},{3,7},{4,7},{5,2},{6,2},{7,1},{8,5},{9,5},{10,2}};
    // int test[6][3]={{12,3,67},{67,4,90},{56,5,78},{123,6,89},{67,7,78},{45,8,765}};
    int i,hist_size=1;
    for(i=0;i<n;i++)
        hist_size=hist_size*2;

    int** hist=malloc(sizeof(int*)*hist_size);      //historylist
    for(i=0;i<hist_size;i++)
        hist[i]=malloc(sizeof(int)*2);


    int** sumlist=malloc(sizeof(int*)*hist_size);   //sumlist
    for(i=0;i<hist_size;i++)
        sumlist[i]=malloc(sizeof(int)*2);

    Head** refarray;                    //original array
    refarray = malloc(sizeof(Head) * hist_size);



    int** reordered=malloc(sizeof(int*)*table->rows);   //reordered
    for(i=0;i<table->rows;i++)
        reordered[i]=malloc(sizeof(int)*2);



    for(i=0;i<hist_size;i++){
        refarray[i]= init_List();
        hist[i][0] = i;
        hist[i][1]=0;
        sumlist[i][0]=i;}
    int location=0;
    for(i=0;i<table->rows;i++){
        printf("ADDING num  %d  to ",table->Table[i][1]);
        location=bithash(table->Table[i][1],n);
        // list_add_id(&refarray[bithash(test[i][1],n)],test[i][0]);
        list_Add_Id(&refarray[location], table->Table[i][0]);

        hist[location][1]++;
    }

    printf("%d \n", table->rows );

    printf("REFFLIST!\n");
    Listnode * kl;                   //printing reff
    /*for(i=0;i<hist_size;i++) {
        kl=refarray[i]->first;
        printf(" \n i= %d <  ",i);
        while(kl!=NULL){
            printf("  -> %d ",kl->id);
            kl=kl->next;}

    }


    printf(" \n size->%d",hist_size);


    for(i=0;i<hist_size;i++) {
        //  hist[i][0] = bithash(i, n);
        //  sumlist[i][0]=bithash(i,n);
        //  printf("   <<%d >>", hist[i][0])
        // hist[i][1] = refarray[i]->size;
        // printf("   <<%d >> \n", hist[i][1]);

    }*/
    printf("\n////////////////////////\n HISTOGRAM\n");

    for(i=0;i<hist_size;i++){
        printf("[%d %d] \n",hist[i][0], hist[i][1]);
    }


    sumlist[0][1]=0;
    for(i=1;i<hist_size;i++){

        sumlist[i][1]=hist[i-1][1]+sumlist[i-1][1];

    }
    printf("\n////////////////////////\n SUMMED_HISTOGRAM\n");

    for(i=0;i<hist_size;i++){
        printf("[%d , %d] \n",sumlist[i][0], sumlist[i][1]);
    }


    //listnode * kl;
    int j=0;//printing reff
    for(i=0;i<hist_size;i++) {
        kl=refarray[i]->first;
        // printf(" \n j== %d <  ",j);
        while(kl!=NULL){
            //printf(" CHECKED IN %d \n",);

            reordered[j][0]=table->Table[kl->id][0];
            reordered[j][1]=table->Table[kl->id][1];
            j++;
            kl=kl->next;}

    }

    printf("\n////////////////////////\n");


    printf("ORIGINAL\n");

    for(i=0;i<table->rows;i++){
        printf("[%d %d] \n",table->Table[i][0], table->Table[i][1]);
    }

    printf("\n");
    printf("REORDERED\n");
    for(i=0;i<table->rows;i++){
        printf("[%d %d] \n",reordered[i][0], reordered[i][1]);
    }



    Combined_Structs* hope_it_works=malloc(sizeof(Combined_Structs));
    hope_it_works->reordered=malloc(sizeof(Table_Info));
    hope_it_works->histogram=malloc(sizeof(Table_Info));

    hope_it_works->histogram->Table=sumlist;
    hope_it_works->reordered->Table=reordered;
    hope_it_works->reordered->rows=table->rows;
    hope_it_works->reordered->columns=2;
    hope_it_works->histogram->columns=2;
    hope_it_works->histogram->rows=hist_size;



    //reordered free
    /*  for(i=0;i<table->rows;i++)
          free(reordered[i]);
      free(reordered);
  */
    //reffarray free
    Listnode * deleter;                   //printing reff
    for(i=0;i<hist_size;i++) {
        kl=refarray[i]->first;

        while(kl!=NULL){
            deleter=kl->next;
            free(kl);
            kl=deleter;
        }
        free(refarray[i]);
    }
    free(refarray);

    //rhistory free
    for(i=0;i<hist_size;i++)
        free(hist[i]);
    free(hist);
    //sum free
    /* for(i=0;i<hist_size;i++)
         free(sumlist[i]);
     free(sumlist);*/

    return hope_it_works;

}












void init(Table_Info*table,int colum,int row){
    table->columns=colum;
    table->rows=row;
    table->Table=(int**)malloc(table->rows*sizeof(int*));
    int i;


    for (i=0; i<table->rows; i++)
        table->Table[i] = (int *)malloc(table->columns * sizeof(int));




}



//void init_tables(Tables_Table lista_pinakon){
//   lista_pinakon.num_of_tables=0;
// lista_pinakon.tables=(Tables_Table_Node*)malloc(10*sizeof(Tables_Table_Node));
//}


