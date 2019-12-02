#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Quicksort.h"

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
uint64_t Sto64(const char *s) { // string to number

    uint64_t i;
    char c;

    int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);
    if (scanned) return i;

    return 0;
}

//=================================================================================================================
int bithash2(uint64_t hash_value, int time) { //time starts at 0 and ads by one

    int from;
    from = time * 8;

    return hash_value << from >> (64 - 8);
}

//=================================================================================================================
void print(Table_Info *table, int from, int to) {
    printf("PRINTING!! from %d, to %d \n\n",from,to);
    int i;

    printf("TABLE A \n \n");
    for (i = from; i < to; i++) {

        for (i = from; i < to; i++) {
            printf("[%"PRIu64" %"PRIu64"] %d ::%d \n", table->TableA[i][0], table->TableA[i][1], i,
                   bithash2(table->TableA[i][1], table->time));
        }
    }

    printf("\n");
    printf("TABLE B\n \n");
    for (i = from; i < to; i++) {
        printf("[%"PRIu64" %"PRIu64"] %d ::%d \n", table->TableB[i][0], table->TableB[i][1], i,
               bithash2(table->TableB[i][1], table->time));
    }

    printf("DONE PRINTING!! \n\n\n\n");
}

//=================================================================================================================
int **radix_Sort(Table_Info *table, int time, int from, int to) { // table kai pia 8ada bits na pari kai pia kolona

    int needed = 1;
    int i, hist_size = 256;

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

        location = bithash2(table->TableA[i][needed], time);
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

            table->TableB[j][0] = table->TableA[kl->id][0];
            table->TableB[j][1] = table->TableA[kl->id][needed];

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
results *big_short(char *filename, int needed) {

    int from, to, i, j, hist_size = 256;

    Table_Info *table;
    table = get_table(filename, needed);
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


                quicksort(table->TableB, from, to - 1);  // else quickshort it

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

                        quicksort(table->TableB, from, to - 1);     //if not quickshort it

                       // printf("quickshorted hash: %d \n",sumlist[i][0]);
                       //  print(table,from,to);
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

        not_yet->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * 2);
    }

    for (i = 0; i < table->rows; i++) {                     //get the data from the correct matrix

        if (table->location[i] == 0) {

            not_yet->matrix[i][0] = table->TableA[i][0];
            not_yet->matrix[i][1] = table->TableA[i][1];
        }
        else {

            not_yet->matrix[i][0] = table->TableB[i][0];
            not_yet->matrix[i][1] = table->TableB[i][1];

        }
    }

    j = 0;

    for (i = 0; i < 1000; i++)
        j = table->location[i] + j;


    int zeros = 0;
    int ones = 0;
    for (i = 0; i < table->rows; i++) {

        if (i < table->rows - 1) {

            if (not_yet->matrix[i][1] > not_yet->matrix[i + 1][1]) {

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

    free_table(table);

    return not_yet;
}

//=================================================================================================================
void free_table(Table_Info *table) {            // self explanatory
    int i;
    printf("rows %d\n",table->rows);
    /*for (i = 0; i < table->rows; i++) {   // <-- THAT WORKS .FIX YOUR PC!!! and get some bloody linux
        free(table->TableA[i]);
        free(table->TableB[i]);

    }*/

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
    free(table->Bucket_list);

    free(table);

}

//=================================================================================================================
info_node* join_matrices(results* A, results* B) {  //join_matrices

    info_node* list;
    node_type* cur_node = NULL;
    int i,j;
    uint64_t targetA, targetB;
    int targetIDA, targetIDB, current_looked;

    list = list_creation();
    current_looked = 0;
int added=0;
   for (i = 0; i < A->rows; i++) {

        targetA = A->matrix[i][1];
        targetIDA = A->matrix[i][0];
        for (j = current_looked;  j < B->rows ; j++) {

            targetB = B->matrix[j][1];
            targetIDB = B->matrix[j][0];
            if (targetA == targetB) {
added++;
                list_insert(list, targetIDA, targetIDB, &cur_node);
                //printf("%d \n",list->start->size);
            }
            else if ((targetA < targetB)&&(i<A->rows-1)) {
            if(A->matrix[i][1]<A->matrix[i+1][1]){
                current_looked = j;
                printf(" looked :%d \n", j);
                break;}
                else{
                    break;
                }
            }else if((targetA > targetB)&&(j==current_looked)){
                current_looked++;

            }
        }
    }

    int res=0;
    struct node_type* cur= list->start;

    for(int i=0; i<list->size; i++) {

        res += cur->size;
        cur = cur->next_node;
        printf(" res size %d\n",cur->size);
    }
    printf("\n result: %d added: %d\n",res, added);

    return list;
}

//=================================================================================================================



results *  simple_mesure(results* A,uint64_t num,char operator){
int i;
results *croped = (struct results *)malloc(sizeof(results));       //malloc the results
    croped->rows = 0;
    croped->matrix = (uint64_t **) malloc(sizeof(uint64_t *) * A->rows);
    for (i = 0; i < A->rows; i++) {

        croped->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * 2);
    }
    switch(operator){

        case '>':
            for(i=0;i<A->rows;i++){
                if(A->matrix[i][1]>num){
                    croped->rows++;
                    croped->matrix[i][0]=A->matrix[i][0];
                    croped->matrix[i][1]=A->matrix[i][1];
                }

            }
            return croped;
         case '<':
            for(i=0;i<A->rows;i++){
                if(A->matrix[i][1]<num){
                    croped->rows++;
                    croped->matrix[i][0]=A->matrix[i][0];
                    croped->matrix[i][1]=A->matrix[i][1];
                }

            }
            return croped;
        case '=':
            for(i=0;i<A->rows;i++){
                if(A->matrix[i][1]==num){
                    croped->rows++;
                    croped->matrix[i][0]=A->matrix[i][0];
                    croped->matrix[i][1]=A->matrix[i][1];
                }

            }

            return croped;

        default:
            printf("wront character");
            return NULL;
    }




}


//=================================================================================================================