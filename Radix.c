#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <stdint.h>

//=================================================================================================================
void list_Add_Id(Head **head1, int id) {

    Listnode *temp = malloc(sizeof(Listnode));
    temp->id = id;
    temp->next = NULL;
    temp->next = (*head1)->first;
    (*head1)->first = temp;
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
int **radix_Sort(Table_Info *table, int time, int from, int to) { // table kai pia 8ada bits na pari kai pia kolona

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

        location = bithash2(table->TableA[i][columns], time);//itan needed anti columns
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
            for(k=0;k<columns;k++){
            table->TableB[j][k] = table->TableA[kl->id][k];}
            table->TableB[j][columns] = table->TableA[kl->id][columns];

            j++;
            kl = kl->next;
        }
    }


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

    for (i = 0; i < hist_size; i++)
        free(hist[i]);
    free(hist);

    /*
    printf("RADIX TIME:%d \n",table->time);
    for(i=0;i<table->rows;i++)
        printf("{ %d , %d } \n",sumlist[i][0],sumlist[i][1]);
    */

    return sumlist;
}

//=================================================================================================================
/*
Table_Info *get_table(char *filename, int needed) {// initialises a table from filename

    char ch;
    int i;
    int colum_orig, rows, one = 1;
    colum_orig = 2;
    rows = 0;
    FILE *fp = fopen(filename, "r");

    while (!feof(fp))//get rows and columns
    {
        ch = (char)fgetc(fp);

        if (one == 1 && ch == ',')
            colum_orig++;
        if (ch == '\n') {
            rows++;
            one = 0;
        }
    }

    rewind(fp);
    char line[500];
    char *usless;
    int columls, count = 0;
    columls = 2;

    Table_Info *retur = malloc(sizeof(Table_Info));
    retur->TableA = malloc(sizeof(uint64_t *) * rows);
    retur->TableB = malloc(sizeof(uint64_t *) * rows);
    retur->location = malloc(sizeof(int *) * rows);

    for (i = 0; i < rows; i++) {
        retur->TableA[i] = malloc(sizeof(int) * columls);
        retur->TableB[i] = malloc(sizeof(int) * columls);
    }

    retur->rows = rows;
    retur->time = 0;
    retur->Bucket_list = malloc(sizeof(Radix_Head) * 8);//holds the buckets to re-radix

    for (i = 0; i < 8; i++) {

        retur->Bucket_list[i] = init_radix_List();
    }


    while (fgets(line, 500, fp) != NULL) {

        retur->location[count] = 1; //initialise possition matrix
        columls = 1;
        retur->TableA[count][0] = count;//pass id

        usless = strtok(line, ",");

        if (columls == needed)
            retur->TableA[count][1] = Sto64(usless);// pass values

        columls++;

        while (usless != NULL) {

            usless = strtok(NULL, ",");

            if (usless != NULL) {
                if (columls == needed)
                    retur->TableA[count][1] = Sto64(usless);

                columls++;
            }
        }


        count++;
    }

    fclose(fp);
    return retur;

}
*/
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
    retur->TableA = (uint64_t **)malloc(sizeof(uint64_t *) * rows);
    retur->TableB = (uint64_t **)malloc(sizeof(uint64_t *) * rows);
    retur->location = malloc(sizeof(int *) * rows);

    for (i = 0; i < rows; i++) {
        retur->TableA[i] = malloc(sizeof(uint64_t) * columls);
        retur->TableB[i] = malloc( sizeof(uint64_t) * columls);
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

            retur->TableA[i][j] = idlist[j][i];

        }
       retur->TableA[i][colums]=col[idlist[needed][i]];//retur->TableA[i][colums]=col[i];
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

    int from, to, i, j, hist_size = 256;
//needed=colums;
    Table_Info *table;
    table = get_table(col,idlist,colums,rows,needed);
    int **sumlist;
    from = 0;
    to = table->rows;

    sumlist = radix_Sort(table, table->time, from, to);          //initial mandatory radix

    for (i = 0; i < hist_size; i++) {

        if (i < hist_size - 1) {
            to = sumlist[i + 1][1];
        }

        if (i == hist_size - 1)
            to = table->rows;
        from = sumlist[i][1];


        if (from < to) {
            if (to - from + 1 > quick_short) {


                list_Add_Bucket(&table->Bucket_list[0], from, to);//add the buckets to be radixed to the bucket list

            }
            else {


                quicksort(table->TableB, from, to - 1,colums);  // else quickshort it

               // printf("quickshorted");
               // print(table,from,to);
            }
        }
    }

    for (i = 0; i < hist_size; i++)         //free the last radix result
        free(sumlist[i]);
    free(sumlist);

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


    results *not_yet = (struct results *)malloc(sizeof(results));       //malloc the results
    not_yet->rows = table->rows;
    not_yet->matrix = (uint64_t **) malloc(sizeof(uint64_t *) * table->rows);

    for (i = 0; i < table->rows; i++) {

        not_yet->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * (colums+1));
    }

    for (i = 0; i < table->rows; i++) {                     //get the data from the correct matrix

        if (table->location[i] == 0) {
            for(j=0;j<colums;j++)
                not_yet->matrix[i][j] = table->TableA[i][j];
           not_yet->matrix[i][colums] = table->TableA[i][colums];
        }
        else {

            for(j=0;j<colums;j++)
                not_yet->matrix[i][j] = table->TableB[i][j];
            not_yet->matrix[i][colums] = table->TableB[i][colums];

        }
    }

    j = 0;

    for (i = 0; i < 1000; i++)
        j = table->location[i] + j;


    /*int zeros = 0;
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
    printf(" zer0s : %d , ones : %d \n",zeros,ones);*/

    free_table(table);
not_yet->columns=colums;
    return not_yet;
}

//=================================================================================================================
void free_table(Table_Info *table) {            // self explanatory
    int i;
    //printf("rows %d\n",table->rows);
    for (i = 0; i < table->rows; i++) {   // <-- THAT WORKS .FIX YOUR PC!!! and get some bloody linux
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

    info_node* list;
    node_type* cur_node = NULL;
    int i,j,k,wtf;
    int* test;
    uint64_t targetIDA, targetIDB,targetA, targetB;
    int  current_looked;
    middle* midle;
   // midle=(middle*)malloc(sizeof(middle));
   // midle->table=NULL;
    int columns=A->columns+B->columns;
    int** table;
    table=(int**)malloc(sizeof(int*)*columns);

    for(i=0;i<(A->columns+B->columns);i++)
        table[i]=(int*)malloc(sizeof(int)*middle_matrix_size);//middle [columns][rows]


    current_looked = 0;
int added=0;
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
                    wtf=table[k][added];}
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

    free_results(A);
    free_results(B);
    //printf("\n  added: %d\n", added);

    //midle->columns=columns;
    *size=added;

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
                not_yet->matrix[i][j] = table->TableA[i][j];
            not_yet->matrix[i][colums] = table->TableA[i][colums];


    }

    free_table(table);
    not_yet->columns=colums;
    return  not_yet;


}