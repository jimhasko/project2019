#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
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

int64_t Sto64(const char *s) {
    int64_t i;
    char c ;
    int scanned = sscanf(s, "%" SCNd64 "%c", &i, &c);
    if (scanned == 1) return i;


    return 0;
}


int bithash3(int hash_value,int time){ //time starts at 0 and ads by one
    int from,to;
    from=time*8;
    to=from+8;
    if(from==0)
        return   hash_value >>(64-to);
    return   hash_value >>(64-to)&((1 << from)-1);
}



int bithash(int64_t hash_value,int hash_key){

  // return   hash_value & ((1<<hash_key)-1);
    return   hash_value & ((1>>(hash_key))-1);
}

int bithash2(uint64_t hash_value,int time){ //time starts at 0 and ads by one
int from,to;
    from=time*8;
    to=from+8;
    if(from==0)
        return   hash_value >>(64-to);
    return   hash_value >>(64-to)&((1 << from)-1);
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
       // location=bithash(table->Table[i][1],n);
        location=bithash3(table->Table[i][1],n);
        // list_add_id(&refarray[bithash(test[i][1],n)],test[i][0]);
        list_Add_Id(&refarray[location], table->Table[i][0]);

        hist[location][1]++;
    }

    printf("%d \n", table->rows );

    printf("REFFLIST!\n");
    Listnode * kl;                   //printing reff

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



Table_Info get_table(char* filename){

    char ch;
    int i;
    int col,lines,one=1;
    col=1;
    lines=0;
    FILE* fp = fopen (filename, "r");

  // i = fgetc(fp);
  //  printf("%d ", i);

    while(!feof(fp))
    {
        ch = fgetc(fp);
//printf("%s ", ch);
        if(one==1 && ch==',')
        col++;
        if(ch == '\n' )
        {
            lines++;
            one=0;
        }
    }

    printf("lines %d , col %d   \n",lines,col);
rewind(fp);
char line[500];
   uint64_t  big1,big2;
    uint64_t table[lines][col];
char usless[60];
    char usless2[60];
    int k,count=0;
    while (fgets(line,500,fp)!=NULL) {

        //fscanf(fp, "%30[^,],%30[^,]", usless, usless2);
        //fscanf(fp,"%lld,%lld" , &big1, &big2);
        sscanf(line,"%s,",usless);
        table[count][0]=Sto64(usless);

        for(k=0;k<col-2;k++){
            sscanf(line,"%s,",usless);
            table[count][k+1]=Sto64(usless);

        }
        sscanf(line,"%s\n",usless);
        table[count][k-1]=Sto64(usless);

    }
        fclose(fp);




}


