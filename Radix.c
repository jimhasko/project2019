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

uint64_t Sto64(const char *s) {
    uint64_t i;
    char c ;
  //  printf(" s: %s \n", s);
    int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);

   // printf(" i: %" PRIu64 "\n", i);
  //  if (scanned == 1) return i;
    if (scanned ) return i;


    return 0;
}

/*
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
*/
int bithash2(uint64_t hash_value,int time){ //time starts at 0 and ads by one
int from,to;
    from=time*8;
    to=from+8;
    //if(from==0) return   hash_value >>(64-to);
    //if(time==7) return hash_value & ((1<<8)-1);
   // return   hash_value >>(64-to-1)&((1 << from+1)-1);
   return (hash_value << from) >>64-8;

    //return (hash_value>>(64-to))&((1<<from)-1);
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
    i=table->rows;
    j=table->columns;
    for(i=0;i<table->rows;i++)
    {

        for(j=0;j<table->columns;j++){

            printf(" %" PRIu64 "  ",table->Table[i][j]);

        }
        printf("\n");

    }



}

Combined_Structs *radix_Sort(Table_Info *table, int time, int needed,int from ,int to) {// table kai pia 8ada bits na pari kai pia kolona
  //  print(table);

    int i,hist_size=256;

    int** hist=malloc(sizeof(int*)*hist_size);      //historylist
    for(i=0;i<hist_size;i++)
        hist[i]=malloc(sizeof(int)*2);


    int ** sumlist=malloc(sizeof(int*)*hist_size);   //sumlist
    for(i=0;i<hist_size;i++)
        sumlist[i]=malloc(sizeof(int)*2);

    Head** refarray;                    //original array
    refarray = malloc(sizeof(Head) * hist_size);



    uint64_t ** reordered=malloc(sizeof(uint64_t*)*table->rows);   //reordered
    for(i=0;i<table->rows;i++)
        reordered[i]=malloc(sizeof(uint64_t)*2);



    for(i=0;i<hist_size;i++){
        refarray[i]= init_List();
        hist[i][0] = i;
        hist[i][1]=0;
        sumlist[i][0]=i;}


    int location=0;
    for(i=from;i<to;i++){
        uint64_t test;
        test=table->Table[i][needed];
        printf("ADDING num  %" PRIu64  " to " ,table->Table[i][needed]);
       // location=bithash(table->Table[i][1],n);
        location=bithash2(table->Table[i][needed],time);
        // list_add_id(&refarray[bithash(test[i][1],n)],test[i][0]);
        list_Add_Id(&refarray[location], table->Table[i][0]);

        hist[location][1]++;
    }


    printf("%d \n", table->rows );

   // printf("REFFLIST!\n");
    Listnode * kl;                   //printing reff
    for(i=0;i<hist_size;i++) {
        kl=refarray[i]->first;
        printf(" \n i= %d <  ",i);
        while(kl!=NULL){
            printf("  -> %d ",kl->id);
            kl=kl->next;}

    }
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
    int j=from;//printing reff
    for(i=0;i<hist_size;i++) {
        kl=refarray[i]->first;
        // printf(" \n j== %d <  ",j);
        while(kl!=NULL){
            //printf(" CHECKED IN %d \n",);
int a=kl->id;
uint64_t cc,b=table->Table[kl->id][needed];
            reordered[j][0]=table->Table[kl->id][0];
            reordered[j][1]=table->Table[kl->id][needed];
            cc=reordered[j][1];
            j++;
            kl=kl->next;}

    }

    printf("\n////////////////////////\n");


    printf("ORIGINAL\n");

    for(i=from;i<to;i++){
        printf("[%" PRIu64 "  %"PRIu64 "] \n"   ,table->Table[i][0], table->Table[i][needed]);
    }

    printf("\n");
    printf("REORDERED\n");
    for(i=from;i<to;i++){
        printf("[%"PRIu64" %"PRIu64"] \n",reordered[i][0], reordered[i][1]);
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


Table_Info* get_table(char* filename){

    char ch;
    int i;
    int col,lines,one=1;
    col=2;
    lines=0;
    FILE* fp = fopen (filename, "r");

  // i = fgetc(fp);
  //  printf("%d ", i);

    while(!feof(fp))//get lines and columns
    {
        ch = fgetc(fp);

        if(one==1 && ch==',')
        col++;
        if(ch == '\n' ){
            lines++;
             one=0;}

    }

    printf("lines %d , col %d   \n",lines,col);
rewind(fp);
char line[500];
  // uint64_t  big1,big2;
   // uint64_t table[lines][col];
char* usless;

    int64_t a;
    int k,count=0;

    Table_Info* retur=malloc(sizeof(Table_Info));
    retur->Table=malloc(sizeof(uint64_t*)*lines);
    for(i=0;i<lines;i++)
        retur->Table[i]=malloc(sizeof(int)*col);
    retur->rows=lines;
    retur->columns=col;




    while (fgets(line,500,fp)!=NULL) {
      //  printf("line: %s :",line);
        //fscanf(fp, "%30[^,],%30[^,]", usless, usless2);
        //fscanf(fp,"%lld,%lld" , &big1, &big2);
        retur->Table[count][0]=count;//pass id
        k=1;
        usless = strtok(line, ",");
        retur->Table[count][k]=Sto64(usless);// pass values
       // printf( "value  %s in k: %d\n", usless,k );
        k++;

        while( usless != NULL ) {


            usless = strtok(NULL, ",");
        //    printf( " %s\n", usless );
        if(usless!=NULL){
           retur->Table[count][k]=Sto64(usless);

          //  printf( "value  %s in k: %d\n", usless,k );
          //  printf("in table value :[%" PRIu64 "] \n"   ,Sto64(usless));
            k++;}
        }
       // printf("[%" PRIu64 " ,%"PRIu64 "] \n"   ,retur->Table[count][0], retur->Table[count][1]);
        count++;
     //   printf("count: %d \n",count);
        if(count==1000)
            printf("debug \n");
    }
        fclose(fp);
//print(retur);
return retur;


}


