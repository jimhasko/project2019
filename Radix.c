#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <stdint.h>


int cur = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int cur_join = 0;
pthread_cond_t cond_join = PTHREAD_COND_INITIALIZER;

//=================================================================================================================
void list_Add_Id(Head **head1, int id) {

    Listnode *temp = malloc(sizeof(Listnode));
    temp->id = id;
    temp->next=NULL;
    temp->prev=NULL;



    if((*head1)->first!=NULL){




    (*head1)->last->next=temp;

    temp->prev=(*head1)->last;
    (*head1)->last=temp;}
    //temp->next = (*head1)->first;
    // (*head1)->first = temp;

    if((*head1)->first==NULL){
        (*head1)->last=temp;
        (*head1)->first=temp;
    }


    (*head1)->size++;
}

//=================================================================================================================

void list_Add_Id2(Head **head1,Head **from, int location,Listnode *temp) {

    // Listnode *temp = malloc(sizeof(Listnode));
    // temp->id = id;
    if(temp==(*from)->first){
        (*from)->first=(*from)->first->next;
    }
    if(temp==(*from)->last){
        //temp->prev->next=NULL;
        (*from)->last=temp->prev;
    }
    if(temp->next!=NULL)
        temp->next->prev=temp->prev;

    if(temp->prev!=NULL)
        temp->prev->next=temp->next;


    temp->were=location;
    temp->next = NULL;
    temp->prev = NULL;
    if((*head1)->first==NULL){
        (*head1)->last = temp;
        (*head1)->first = temp;
    }else{
    temp->prev=(*head1)->last;
    (*head1)->last->next=temp;
    (*head1)->last=temp;}


  //  (*head1)->first = temp;
    (*head1)->size++;
}
//=================================================================================================================
void list_Add_Bucket(Radix_Head **head1, int from, int to) {

    Radix_List *temp = malloc(sizeof(Radix_List));
    temp->from = from;
    temp->to = to;
    temp->next = NULL;
    temp->next = (*head1)->first;
    (*head1)->first = temp;
    (*head1)->size++;
}

//=================================================================================================================
Head *init_List() {

    Head *temp;
    temp = malloc(sizeof(Head));
    temp->size = 0;
    temp->first = NULL;
    return temp;
}

//=================================================================================================================
Radix_Head *init_radix_List() {

    Radix_Head *temp;
    temp = malloc(sizeof(Radix_Head));
    temp->size = 0;
    temp->first = NULL;
    return temp;

}

//=================================================================================================================


int bithash2(uint64_t hash_value, int time) { //time starts at 0 and ads by one

    int from;
    from = time * 8;

    return hash_value << from >> (64 - 8);
}

//=================================================================================================================
void print(Table_Info *table, int from, int to,int columns) {
    printf("PRINTING!! from %d, to %d \n\n",from,to);
    int i;

    printf("TABLE A \n \n");
    for (i = from; i < to; i++) {

        for (i = from; i < to; i++) {
            printf("[%"PRIu64" %"PRIu64"|| %"PRIu64"] %d ::%d location::%d \n", table->TableA[i][0], table->TableA[i][1],table->TableA[i][columns], i,
                   bithash2(table->TableA[i][1], table->time),table->location[i]);
        }
    }

    printf("\n");
    printf("TABLE B\n \n");
    for (i = from; i < to; i++) {
        printf("[%"PRIu64" %"PRIu64"|| %"PRIu64"] %d ::%d location::%d\n", table->TableB[i][0], table->TableB[i][1],table->TableB[i][columns], i,
               bithash2(table->TableB[i][1], table->time),table->location[i]);
    }

    printf("DONE PRINTING!! \n\n\n\n");
}

//=================================================================================================================
usefull* radix_Sort(Table_Info *table, int time, int from, int to) { // table kai pia 8ada bits na pari kai pia kolona

    int needed,columns ;//= 1;
    int i, k,hist_size = 256;
    needed=table->needed;
    columns=table->columns;
    int **hist = malloc(sizeof(int *) * hist_size);      //History list
    for (i = 0; i < hist_size; i++)
        hist[i] = malloc(sizeof(int) * 2);


    int **sumlist = malloc(sizeof(int *) * hist_size);   //Summed history list
    for (i = 0; i < hist_size; i++)
        sumlist[i] = malloc(sizeof(int) * 2);

    Head **refarray;
    refarray = malloc(sizeof(Head) * hist_size);


    for (i = 0; i < hist_size; i++) {
        refarray[i] = init_List();
        hist[i][0] = i;
        hist[i][1] = 0;
        sumlist[i][0] = i;
    }


    int location = 0;
    for (i = from; i < to; i++) {

        location = bithash2(table->TableA[columns][i], time);//itan needed anti columns
        list_Add_Id(&refarray[location], i);
        hist[location][1]++;
    }

    Listnode *kl;
    for (i = 0; i < hist_size; i++) {
        kl = refarray[i]->first;

        while (kl != NULL) {

            kl = kl->next;
        }
    }

    sumlist[0][1] = from;
    for (i = 1; i < hist_size; i++) {

        sumlist[i][1] = hist[i - 1][1] + sumlist[i - 1][1];
    }

    int j = from;
    for (i = 0; i < hist_size; i++) {
        kl = refarray[i]->first;

        while (kl != NULL) {
          //  table->TableB[j]=(uint64_t*) malloc( sizeof(uint64_t) * (columns+1));
            for(k=0;k<columns+1;k++){
            table->TableB[k][j] = table->TableA[k][kl->id];}

            //table->TableB[j][columns] = table->TableA[kl->id][columns];
           // free(table->TableA[kl->id]);
            j++;
            kl = kl->next;
        }
    }

/*
    Listnode *deleter;
    for (i = 0; i < hist_size; i++) {

        kl = refarray[i]->first;
        while (kl != NULL) {

            deleter = kl->next;
            free(kl);
            kl = deleter;
        }
        free(refarray[i]);
    }
    free(refarray);
*/
    for (i = 0; i < hist_size; i++)
        free(hist[i]);
    free(hist);

    usefull* test;
    test=(usefull*)malloc(sizeof(usefull));
    test->sumlist=sumlist;
    test->refarray=refarray;

    return test;
}

//=================================================================================================================
void radix_Sort2(Table_Info *table, int time,Head* use_this, int from, int to) { // table kai pia 8ada bits na pari kai pia kolona
    int is_first = 0;
    int needed, columns;//= 1;
    int i, j, k, hist_size = 256;
    needed = table->needed;
    columns = table->columns;
    Listnode* temp;
int max=to;
  /*  Listnode *safekeep;
    safekeep = temp->prev;
    if (safekeep == NULL)
        is_first = 1;*/


    int **hist = malloc(sizeof(int *) * hist_size);      //History list
    for (i = 0; i < hist_size; i++)
        hist[i] = malloc(sizeof(int) * 2);


    int **sumlist = malloc(sizeof(int *) * hist_size);   //Summed history list
    for (i = 0; i < hist_size; i++)
        sumlist[i] = malloc(sizeof(int) * 2);

    Head **refarray;
    refarray = malloc(sizeof(Head) * hist_size);


    for (i = 0; i < hist_size; i++) {
        refarray[i] = init_List();
        hist[i][0] = i;
        hist[i][1] = 0;
        sumlist[i][0] = i;
    }


    int location = 0;
    int count = 0;
    Listnode *more_temp;
    // temp=use_this->first;

    if(time==5){
        int brakk=0;
    }
    temp=use_this->first;
    while (count < to - from) {

        location = bithash2(table->TableA[columns][temp->id], time);//itan needed anti columns
        more_temp = temp->next;

        list_Add_Id2(&refarray[location], &use_this, location, temp);
        hist[location][1]++;
        if(location==18){
            int brakagin=0;
        }
        temp = more_temp;
        count++;

    }
   // if(time==6)
     //   printf("%d \n",hist[18][1]);
    sumlist[0][1] = from;
    for (i = 1; i < hist_size; i++) {

        sumlist[i][1] = hist[i - 1][1] + sumlist[i - 1][1];
       // if(refarray[i]->size>0)
        // printf("%d : %d :i %d \n",sumlist[i][1],refarray[i]->size,i);
    }

    /*  int j = from;
      for (i = 0; i < hist_size; i++) {
          kl = refarray[i]->first;

          while (kl != NULL) {
              for(k=0;k<columns;k++){
                  table->TableB[k][j] = table->TableA[k][kl->id];}
              table->TableB[columns][j] = table->TableA[columns][kl->id];

              j++;
              kl = kl->next;
          }
      }*/


    Listnode *kl;

    if(time==6){
        int brak=0;
    }
    for (i = 0; i < hist_size; i++) {
        kl = refarray[i]->first;
        if (kl != NULL){

        from = sumlist[i][1];
        if (i < hist_size - 1) {
            to = sumlist[i + 1][1];
        } else {
            to = max;
        }
        if (to - from > quick_short && time != 7) {
          /*  if (is_first == 1) {
                use_this->first = refarray[i]->first;
                use_this->last = refarray[i]->last;
                safekeep = use_this->last;
                is_first = 0;
            } else {
                safekeep->next = refarray[i]->first;
                refarray[i]->first->prev = safekeep;
                safekeep->next = refarray[i]->first;
                safekeep = refarray[i]->last;
            }*/


            radix_Sort2(table, time + 1, refarray[i], from, to);
        } else {
            for (k = from; k < to; k++) {
                Listnode * deleter,*temp;
             //   table->TableB[k] =(uint64_t*)  malloc(sizeof(uint64_t) * (columns + 1));
                for (j = 0; j < columns+1 ; j++) {
                    table->TableB[j][k] = table->TableA[j][kl->id];
                }
              //  table->TableB[k][columns] = table->TableA[kl->id][columns];
               // free(table->TableA[kl->id]);
                deleter=kl;
                kl=kl->next;
                refarray[i]->first=kl;

                free(deleter);

            }
            quicksort(table->TableB, from, to - 1, columns);

        }
    }
}
    for (i = 0; i < hist_size; i++) {

        free(refarray[i]);
    }
    free(refarray);

    for (i = 0; i < hist_size; i++)
        free(hist[i]);
    free(hist);

    for (i = 0; i < hist_size; i++) {

        free(sumlist[i]);
    }
    free(sumlist);
}
//=================================================================================================================
Table_Info *get_table(uint64_t* col,int** idlist,int colums,int rows,int needed ) {// initialises a table from filename

    char ch;
    int i,j;
    int colum_orig,  one = 1;
    colum_orig = 2;
    //rows = size;

    int columls, count = 0;
    columls = colums+1;

    Table_Info *retur = malloc(sizeof(Table_Info));
    retur->TableA = (uint64_t **)malloc(sizeof(uint64_t *) * columls);
    retur->TableB = (uint64_t **)malloc(sizeof(uint64_t *) * columls);
    retur->location = malloc(sizeof(int *) * rows);

    for (i = 0; i < columls; i++) {
        retur->TableA[i] = malloc(sizeof(uint64_t) * rows);
        if(retur->TableA[i]==NULL)
        {
            printf("Error! memory not allocated at get table. row %d \n",i);
            exit(0);
        }
        retur->TableB[i] = malloc( sizeof(uint64_t) * rows);
        if(retur->TableB[i]==NULL)
        {
            printf("Error! memory not allocated at get table.row %d \n",i);
            exit(0);
        }
    }

    retur->rows = rows;
    retur->time = 0;
    retur->Bucket_list = malloc(sizeof(Radix_Head) * 8);//holds the buckets to re-radix

    for (i = 0; i < 8; i++) {

        retur->Bucket_list[i] = init_radix_List();
    }
    for(i=0;i<rows;i++){


        retur->location[i] = 1; //initialise possition matrix
        for(j=0;j<colums;j++) {

            retur->TableA[j][i] = idlist[j][i];

        }
       retur->TableA[colums][i]=col[idlist[needed][i]];//retur->TableA[i][colums]=col[i];
      //  printf(",%"PRIu64 "\n",retur->TableA[i][colums]);


    }
    retur->columns=colums;
    retur->needed=needed;


    return retur;

}

//=================================================================================================================
Table_Info *flip_tables(Table_Info *table) {

    uint64_t **temp;
    temp = table->TableA;
    table->TableA = table->TableB;
    table->TableB = temp;
    table->time++;
    return table;
}

//=================================================================================================================
results *big_short(uint64_t* col,int** idlist,int colums,int rows,int needed ) {

    int from, to, i, j, k,hist_size = 256;
//needed=colums;
    Table_Info *table;
    table = get_table(col,idlist,colums,rows,needed);
   usefull* test;
    from = 0;
    to = table->rows;
    Listnode* kl;
    test = radix_Sort(table, table->time, from, to);          //initial mandatory radix
    table=flip_tables(table);

  int wut;

    jobqueue_sort* jobquery;

    jobquery=(jobqueue_sort*)malloc(sizeof(jobqueue_sort));
    jobquery->jobs=(job_r2*)malloc(sizeof(job_r2)*255);
    jobquery->size=0;
    jobquery->used=0;
    jobquery->thread_num=0;
    pthread_t* thread_matrix;
    thread_matrix=(pthread_t*)malloc(sizeof(pthread_t)*sort_threads);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutexsum, NULL);
    pthread_cond_init(&cond, NULL);


    for (i = 0; i < hist_size; i++) {

        if (i < hist_size - 1) {
            to = test->sumlist[i + 1][1];
        }

        if (i == hist_size - 1)
            to = table->rows;
        from = test->sumlist[i][1];

        if(to-from>quick_short){
            jobquery->jobs[i].table=table;
            jobquery->jobs[i].time=table->time;
            jobquery->jobs[i].use_this=test->refarray[i];
            jobquery->jobs[i].from=from;
            jobquery->jobs[i].to=to;
            jobquery->size++;

          //  radix_Sort2(table,table->time,test->refarray[i],from,to);
        }else{
            kl=test->refarray[i]->first;
            for (k = from; k < to; k++) {
                Listnode * deleter,*temp;
              //  table->TableB[k] =(uint64_t*)  malloc(sizeof(uint64_t) * (colums + 1));
                for (j = 0; j < (colums+1) ; j++) {
                    table->TableB[j][k] = table->TableA[j][kl->id];
                }
                //  table->TableB[k][columns] = table->TableA[kl->id][columns];
              //  free(table->TableA[kl->id]);
                deleter=kl;
                kl=kl->next;
                test->refarray[i]->first=kl;

                free(deleter);

            }
            quicksort(table->TableB, from, to - 1, colums);
            if(kl!=NULL){
                int  i_beg_you_work=0;
            }
        }

    }



    for(i=0;i<sort_threads;i++) {

        wut = pthread_create(&thread_matrix[i], NULL, short_thread, (void *) jobquery);
    }



    for(i=0;i<sort_threads;i++)
        pthread_join(thread_matrix[i], NULL);


    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutexsum);
    pthread_cond_destroy(&cond);


    for (i = 0; i < hist_size; i++)         //free the last radix result
        free(test->sumlist[i]);
    free(test->sumlist);

    for (i = 0; i < hist_size; i++) {

        free(test->refarray[i]);
    }
    free(test->refarray);
    free(test);
    /*
       for (j = 0; j < 8; j++) {                //runs the list of to do radix_short
           flip_tables(table);
           Radix_List *kl = table->Bucket_list[j]->first;


          while (kl != NULL) {                 //for all the radix shorts to be done in that table state & bits

               sumlist = radix_Sort(table, table->time, kl->from, kl->to);
            //   print(table,10,70,colums);
               for (i = kl->from; i < kl->to; i++) {
                   table->location[i] = 1 - table->location[i];            //save data matrix location
               }


               for (i = 0; i < hist_size; i++) {

                   if (i < hist_size - 1) {
                       to = sumlist[i + 1][1];
                   }
                   if (i == hist_size - 1)
                       to = kl->to;
                   from = sumlist[i][1];       // get from to


                   if (from < to) {

                       if (((to - from + 1) > quick_short) && j < 7) {

                           list_Add_Bucket(&table->Bucket_list[j + 1], from, to);  //if its over the limit add to radix to do list
                       }
                       else {

                           quicksort(table->TableB, from, to - 1,colums);     //if not quickshort it

                           //printf("quickshorted hash: %d \n",sumlist[i][0]);
                            //print(table,from,to,colums);
                       }
                   }
               }

            kl = kl->next;

            for (i = 0; i < hist_size; i++)
                free(sumlist[i]);
            free(sumlist);          //free last radix

        }
    }
*/
table=flip_tables(table);

        results *not_yet = (struct results *)malloc(sizeof(results));       //malloc the results
    not_yet->rows = table->rows;
    not_yet->matrix = (uint64_t **) malloc(sizeof(uint64_t *) * table->rows);

    for (i = 0; i < table->rows; i++) {

        not_yet->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * (colums+1));
    }

    for (i = 0; i < table->rows; i++) {                     //get the data from the correct matrix






            for(j=0;j<colums;j++)
                not_yet->matrix[i][j] = table->TableA[j][i];
            not_yet->matrix[i][colums] = table->TableA[colums][i];


    }


/*
    int zeros = 0;
    int ones = 0;

    for (i = 0; i < table->rows; i++) {

        if (i < table->rows - 1) {

            if (not_yet->matrix[i][colums] > not_yet->matrix[i + 1][colums]) {

                if (table->location[i] == 0) {

                    zeros++;
                }
                else {

                    ones++;
                }
            }
        }
    }
    printf(" zer0s : %d , ones : %d \n",zeros,ones);
*/
    free(thread_matrix);
    free(jobquery->jobs);
    free(jobquery);
    free_table(table);
    not_yet->columns=colums;
    return not_yet;
}

//=================================================================================================================
void free_table(Table_Info *table) {            // self explanatory
    int i;
    //printf("rows %d\n",table->rows);
    for (i = 0; i < table->columns+1; i++) {   // <-- THAT WORKS .FIX YOUR PC!!! and get some bloody linux
        free(table->TableA[i]);
       free(table->TableB[i]);

    }

    free(table->TableB);
    free(table->TableA);
    free(table->location);

    Radix_List *deleter;
    Radix_List *kl;

    for (i = 0; i < 8; i++) {
        kl = table->Bucket_list[i]->first;

        while (kl != NULL) {
            deleter = kl->next;
            free(kl);
            kl = deleter;
        }
        free(table->Bucket_list[i]);
    }
    free(table->Bucket_list); ///<<--- this thing

    free(table);

}

//=================================================================================================================
int** join_matrices(results* A, results* B,int needed,int middle_matrix_size ,int* size) {  //join_matrices


    int i,j,k,wtf,wut;
    int* test;
int added=0;
    middle* midle;
   // midle=(middle*)malloc(sizeof(middle));
   // midle->table=NULL;





wtf=A->rows/10;

    jobqueue_join* jobquery;

    jobquery=(jobqueue_join*)malloc(sizeof(jobqueue_join));
    jobquery->jobs=(job_join*)malloc(sizeof(job_join)*10);
    jobquery->size=0;
    jobquery->used=0;
    jobquery->thread_num=0;
    pthread_t* thread_matrix;
    thread_matrix=(pthread_t*)malloc(sizeof(pthread_t)*join_threads);
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutexsum, NULL);
    pthread_cond_init(&cond, NULL);


    for(i=0;i<10;i++){

        jobquery->jobs[i].middle_matrix_size=middle_matrix_size/10;
        jobquery->jobs[i].needed=needed;
        jobquery->jobs[i].A=A;
        jobquery->jobs[i].B=B;
        jobquery->jobs[i].from=i*wtf;
        jobquery->jobs[i].to=(i+1)*wtf;


    }

//////////////
 /*
    int added=0;
    uint64_t targetIDA, targetIDB,targetA, targetB;
    int  current_looked;
    current_looked = 0;
int** table;
   for (i = 0; i < A->rows; i++) {

        targetA = A->matrix[i][A->columns];
        targetIDA = A->matrix[i][needed];
        for (j = current_looked;  j < B->rows ; j++) {

            targetB = B->matrix[j][B->columns];
            targetIDB = B->matrix[j][0];
            if (targetA == targetB) {

                if(added<middle_matrix_size){   ///add all the columns
                    for(k=0;k<A->columns;k++){

                        table[k][added]=(int)A->matrix[i][k];

                    }
                   // for(k=A->columns;k<(A->columns+B->columns);k++)
                    //    table[k][added]=(int)B->matrix[j][k];
                   // for(k=A->columns;k<(A->columns+1);k++)
                        table[A->columns][added]=(int)B->matrix[j][0];

                }else{
                                            ///realloc if no space////////
                    middle_matrix_size=2*middle_matrix_size;
                     for(k=0;k<(A->columns+B->columns);k++){
                    test=(int*)realloc(table[k],(size_t)middle_matrix_size*sizeof(int));
                    if(test==0){
                        printf("MIDLE MATRIX REALLOC=NULL \n");
                        exit(1);
                    }
                    table[k]=test;
                     }



                    for(k=0;k<A->columns;k++)
                        table[k][added]=(int)A->matrix[i][k];     // add all the columns
                    for(k=A->columns;k<(A->columns+1);k++)
                        table[A->columns][added]=(int)B->matrix[j][0];


                }
                added++;
               // list_insert(list, targetIDA, targetIDB, &cur_node);
                //printf("%d \n",list->start->size);
            }
            else if ((targetA < targetB)&&(i<A->rows-1)) {
                 if(A->matrix[i][A->columns]<A->matrix[i+1][A->columns]){
                 current_looked = j;
             //   printf(" looked :%d \n", j);
                 break;}
                    else{

                    break;
                }
            }else if((targetA > targetB)&&(j==current_looked)){
                current_looked++;

            }
        }
    }*/
///////////////////


    for(i=0;i<sort_threads;i++) {

        wut = pthread_create(&thread_matrix[i], NULL, join_thread, (void *) jobquery);
    }



    for(i=0;i<sort_threads;i++)
        pthread_join(thread_matrix[i], NULL);



    free_results(A);
    free_results(B);


    for(i=0;i<10;i++){

        added+=jobquery->jobs[i].added;

    }
    *size=added;

    int columns=A->columns+B->columns;
    int** table;
    table=(int**)malloc(sizeof(int*)*columns);

    for(i=0;i<(A->columns+B->columns);i++)
        table[i]=(int*)malloc(sizeof(int)*added);//middle [columns][rows]

    for(i=0;i<10;i++){
for(j=0;j<jobquery->jobs[i].added;j++) {
    for(k=0;k<(A->columns+B->columns);k++)
    table[k][j]=jobquery->jobs[i].new_middle[k][j];

        }


    }

for(i=0;i<10;i++){
    for(k=0;k<jobquery->jobs[i].added;k++){
        free(jobquery->jobs[i].new_middle[k]);
    }
    free(jobquery->jobs[i].new_middle);
}
free(jobquery->jobs);
free(jobquery);
free(thread_matrix);

    return table;
}

//=================================================================================================================

void free_results(results * A){
    int i;
    for(i=0;i<A->rows;i++){
        free(A->matrix[i]);
    }
    free(A->matrix);
    free(A);

}

//=================================================================================================================

results* get_old_results(uint64_t* col,int** idlist,int colums,int rows,int needed){
    int i,j;
    Table_Info *table;
    table = get_table(col,idlist,colums,rows,needed);
    results *not_yet = (struct results *)malloc(sizeof(results));       //malloc the results
    not_yet->rows = table->rows;
    not_yet->matrix = (uint64_t **) malloc(sizeof(uint64_t *) * table->rows);

    for (i = 0; i < table->rows; i++) {

        not_yet->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * (colums+1));
    }

    for (i = 0; i < table->rows; i++) {                     //get the data from the correct matrix


            for(j=0;j<colums;j++)
                not_yet->matrix[i][j] = table->TableA[j][i];
            not_yet->matrix[i][colums] = table->TableA[colums][i];


    }

    free_table(table);
    not_yet->columns=colums;
    return  not_yet;


}



//=================================================================================================================



void* short_thread(void* kk){
    int i;


    pthread_mutex_lock(&mutex);
    int self = cur++;
    pthread_t tid = pthread_self();

    jobqueue_sort* Queue;
    Queue=(jobqueue_sort*)kk;
   // printf("got \"%02x\"\n", (unsigned)tid);
    // numn++;
    Queue->thread_num++;

    if(Queue->thread_num==sort_threads) {
      //  printf("%d awaken \n", Queue->thread_num);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);

    }

    while(Queue->thread_num<sort_threads) {
       // printf("got \"%d\"\n", self);

        pthread_cond_wait(&cond, &mutex);
    }
    pthread_mutex_unlock(&mutex);


   // printf("got more \"%d\"\n", self);

    //if(Queue->thread==Queue->thread_num)
    //  pthread_cond_signal(&cond);

    while(1) {
        pthread_mutex_lock (&mutexsum);
        i = Queue->used;
        Queue->used++;
        pthread_mutex_unlock (&mutexsum);
        if (i< Queue->size) {

           // pthread_mutex_lock (&mutexsum);
           // i = Queue->used;
          //  Queue->used++;


            radix_Sort2(Queue->jobs[i].table,Queue->jobs[i].time,Queue->jobs[i].use_this,Queue->jobs[i].from,Queue->jobs[i].to);

           // pthread_mutex_unlock (&mutexsum);

        } else {
            break;
        }
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}



//=================================================================================================================



void* join_thread(void* kk){
    int i;


    pthread_mutex_lock(&mutex_join);
    int self = cur_join++;
    pthread_t tid = pthread_self();

    jobqueue_join* Queue;
    Queue=(jobqueue_join*)kk;
    // printf("got \"%02x\"\n", (unsigned)tid);
    // numn++;
    Queue->thread_num++;

    if(Queue->thread_num==join_threads) {
        //  printf("%d awaken \n", Queue->thread_num);
        pthread_cond_broadcast(&cond_join);
        pthread_mutex_unlock(&mutex_join);

    }

    while(Queue->thread_num<join_threads) {
        // printf("got \"%d\"\n", self);

        pthread_cond_wait(&cond_join, &mutex_join);
    }
    pthread_mutex_unlock(&mutex_join);


    // printf("got more \"%d\"\n", self);

    //if(Queue->thread==Queue->thread_num)
    //  pthread_cond_signal(&cond);

    while(1) {
        pthread_mutex_lock (&mutexsum_join);
        i = Queue->used;
        Queue->used++;
        pthread_mutex_unlock (&mutexsum_join);
        if (i< Queue->size) {

            // pthread_mutex_lock (&mutexsum);
            // i = Queue->used;
            //  Queue->used++;
join_test(&Queue->jobs[i]);

         //   radix_Sort2(Queue->jobs[i].table,Queue->jobs[i].time,Queue->jobs[i].use_this,Queue->jobs[i].from,Queue->jobs[i].to);

            // pthread_mutex_unlock (&mutexsum);

        } else {
            break;
        }
    }

    pthread_cond_signal(&cond_join);
    pthread_mutex_unlock(&mutex_join);
    pthread_exit(NULL);
}




void*join_test(job_join* join){
    results* A=join->A;
    results* B=join->B;
    int needed=join->needed;
    int middle_matrix_size =join->middle_matrix_size;

    int i,j,k,from,to;
    to=join->to;
    from=join->from;
    uint64_t targetIDA, targetIDB,targetA, targetB;
    int  current_looked;
    current_looked = 0;
    int** table;
    int* test;
    int added=0;

    int columns=A->columns+B->columns;
    table=(int**)malloc(sizeof(int*)*columns);

    for(i=0;i<(A->columns+B->columns);i++)
        table[i]=(int*)malloc(sizeof(int)*middle_matrix_size);//middle [columns][rows]
    for (i = from; i < to; i++) {

        targetA = A->matrix[i][A->columns];
        targetIDA = A->matrix[i][needed];
        for (j = current_looked;  j < B->rows ; j++) {

            targetB = B->matrix[j][B->columns];
            targetIDB = B->matrix[j][0];
            if (targetA == targetB) {

                if(added<middle_matrix_size){   ///add all the columns
                    for(k=0;k<A->columns;k++){

                        table[k][added]=(int)A->matrix[i][k];
                       }
                    // for(k=A->columns;k<(A->columns+B->columns);k++)
                    //    table[k][added]=(int)B->matrix[j][k];
                    // for(k=A->columns;k<(A->columns+1);k++)
                    table[A->columns][added]=(int)B->matrix[j][0];

                }else{
                    ///realloc if no space////////
                    middle_matrix_size=2*middle_matrix_size;
                    for(k=0;k<(A->columns+B->columns);k++){
                        test=(int*)realloc(table[k],(size_t)middle_matrix_size*sizeof(int));
                        if(test==0){
                            printf("MIDLE MATRIX REALLOC=NULL \n");
                            exit(1);
                        }
                        table[k]=test;
                    }



                    for(k=0;k<A->columns;k++)
                        table[k][added]=(int)A->matrix[i][k];     // add all the columns
                    for(k=A->columns;k<(A->columns+1);k++)
                        table[A->columns][added]=(int)B->matrix[j][0];


                }
                added++;
                // list_insert(list, targetIDA, targetIDB, &cur_node);
                //printf("%d \n",list->start->size);
            }
            else if ((targetA < targetB)&&(i<A->rows-1)) {
                if(A->matrix[i][A->columns]<A->matrix[i+1][A->columns]){
                    current_looked = j;
                    //   printf(" looked :%d \n", j);
                    break;}
                else{

                    break;
                }
            }else if((targetA > targetB)&&(j==current_looked)){
                current_looked++;

            }
        }
    }

join->new_middle=table;
join->added=added;
}









