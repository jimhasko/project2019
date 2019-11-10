#include "Radix.h"
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <inttypes.h>
#include "quicjshort.h"

#define  quick_short 10

void list_Add_Id(Head **head1, int id) {

    Listnode *temp = malloc(sizeof(Listnode));
    temp->id = id;
    temp->next = NULL;
    temp->next = (*head1)->first;
    (*head1)->first = temp;
    (*head1)->size++;
    // printf(" id %d  \n",(*head1)->first->id);


}

void list_Add_Bucket(Radix_Head **head1, int from, int to, int location) {

    Radix_List *temp = malloc(sizeof(Radix_List));
    temp->from = from;
    temp->to = to;
    temp->location = location;
    temp->next = NULL;
    temp->next = (*head1)->first;
    (*head1)->first = temp;
    (*head1)->size++;
}


Head *init_List() {
    Head *temp;
    temp = malloc(sizeof(Head));
    temp->size = 0;
    temp->first = NULL;
    return temp;

}

Radix_Head *init_radix_List() {
    Radix_Head *temp;
    temp = malloc(sizeof(Radix_Head));
    temp->size = 0;
    temp->first = NULL;
    return temp;

}

uint64_t Sto64(const char *s) {
    uint64_t i;
    char c;
    //  printf(" s: %s \n", s);
    int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);

    // printf(" i: %" PRIu64 "\n", i);
    //  if (scanned == 1) return i;
    if (scanned) return i;


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
int bithash2(uint64_t hash_value, int time) { //time starts at 0 and ads by one
    int from;
    from = time * 8;
    //to=from+8;
    //if(from==0) return   hash_value >>(64-to);
    //if(time==7) return hash_value & ((1<<8)-1);
    // return   hash_value >>(64-to-1)&((1 << from+1)-1);
    return (hash_value << from) >> (64 - 8);

    //return (hash_value>>(64-to))&((1<<from)-1);
}

/*
Table_Info* getrow(Table_Info* pi,int column){
    int i;
    Table_Info* retur=malloc(sizeof(Table_Info));
    retur->TableA=malloc(sizeof(int*)*pi->rows);
    for(i=0;i<pi->rows;i++)
        retur->TableA[i]=malloc(sizeof(int)*2);




    for(i=0;i<pi->rows;i++)
        retur->TableA[i][0]=i+1;
    retur->TableA[i][1]=pi->TableA[i][column];

    retur->columns=2;
    retur->rows=pi->rows;

    return  retur;

}*/

void print(Table_Info *table, int from, int to) {
    printf("PRINTING!!\n\n");
    int i;

    printf("TABLE A \n");
    for (i = from; i < to; i++) {

        for (i = from; i < to; i++) {
            printf("[%"PRIu64" %"PRIu64"] %d ::%d \n", table->TableA[i][0], table->TableA[i][1], i,
                   bithash2(table->TableA[i][1], table->time));
        }

    }

    printf("\n");
    printf("TABLE B\n \n \n");
    for (i = from; i < to; i++) {
        printf("[%"PRIu64" %"PRIu64"] %d ::%d \n", table->TableB[i][0], table->TableB[i][1], i,
               bithash2(table->TableB[i][1], table->time));
    }

    printf("DONE PRINTING \n\n\n\n");
}

int **radix_Sort(Table_Info *table, int time, int from, int to) {// table kai pia 8ada bits na pari kai pia kolona
    //print(table,from,to);
    int needed = 1;
    int i, hist_size = 256;

    int **hist = malloc(sizeof(int *) * hist_size);      //historylist
    for (i = 0; i < hist_size; i++)
        hist[i] = malloc(sizeof(int) * 2);


    int **sumlist = malloc(sizeof(int *) * hist_size);   //sumlist
    for (i = 0; i < hist_size; i++)
        sumlist[i] = malloc(sizeof(int) * 2);

    Head **refarray;                    //original array
    refarray = malloc(sizeof(Head) * hist_size);



    //  uint64_t ** TableB=malloc(sizeof(uint64_t*)*table->rows);   //TableB
    //for(i=0;i<table->rows;i++)
    //     TableB[i]=malloc(sizeof(uint64_t)*2);



    for (i = 0; i < hist_size; i++) {
        refarray[i] = init_List();
        hist[i][0] = i;
        hist[i][1] = 0;
        sumlist[i][0] = i;
    }


    int location = 0;
    for (i = from; i < to; i++) {

        //   printf("ADDING num  %" PRIu64  " to " ,table->TableA[i][needed]);

        location = bithash2(table->TableA[i][needed], time);

        // list_Add_Id(&refarray[location], table->TableA[i][0]);
        list_Add_Id(&refarray[location], i);
        hist[location][1]++;
    }


    // printf("%d \n", table->rows );

    // printf("REFFLIST!\n");
    Listnode *kl;                   //printing reff
    for (i = 0; i < hist_size; i++) {
        kl = refarray[i]->first;
        //  printf(" \n i= %d <  ",i);
        while (kl != NULL) {
            //    printf("  -> %d ",kl->id);
            kl = kl->next;
        }

    }
    // printf("\n////////////////////////\n HISTOGRAM\n");

    // for(i=0;i<hist_size;i++){
    //  printf("[%d %d] \n",hist[i][0], hist[i][1]);
    // }


    sumlist[0][1] = from;
    for (i = 1; i < hist_size; i++) {

        sumlist[i][1] = hist[i - 1][1] + sumlist[i - 1][1];

    }
    // printf("\n////////////////////////\n SUMMED_HISTOGRAM\n");

     /*for(i=0;i<hist_size;i++){
      printf("[%d , %d] \n",sumlist[i][0], sumlist[i][1]);
     }*/


    //listnode * kl;
    int j = from;//printing reff
    for (i = 0; i < hist_size; i++) {
        kl = refarray[i]->first;
        // printf(" \n j== %d <  ",j);
        while (kl != NULL) {
            //printf(" CHECKED IN %d \n",);



            table->TableB[j][0] = table->TableA[kl->id][0];
            table->TableB[j][1] = table->TableA[kl->id][needed];

            j++;
            kl = kl->next;
        }

    }
//print(table,from,to);
    // printf("\n////////////////////////\n");


    // printf("ORIGINAL\n");

    //for(i=from;i<to;i++){
    // printf("[%" PRIu64 "  %"PRIu64 "] \n"   ,table->TableA[i][0], table->TableA[i][needed]);
    //  }

    // printf("\n");
    // printf("REORDERED\n");
    //  for(i=from;i<to;i++){
    //  printf("[%"PRIu64" %"PRIu64"] \n",table->TableB[i][0], table->TableB[i][1]);
    //  }


/*
    Combined_Structs* hope_it_works=malloc(sizeof(Combined_Structs));
  //  hope_it_works->TableB=malloc(sizeof(Table_Info));
    hope_it_works->histogram=malloc(sizeof(Table_Info));

    hope_it_works->histogram->TableA=sumlist;
  //  hope_it_works->TableB->TableA=table->TableB;
  //  hope_it_works->TableB->rows=table->rows;
  //  hope_it_works->TableB->columns=2;
    hope_it_works->histogram->columns=2;
    hope_it_works->histogram->rows=hist_size;
*/
//int** hope_it_works;


    Listnode *deleter;                   //printing reff
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

    //rhistory free
    for (i = 0; i < hist_size; i++)
        free(hist[i]);
    free(hist);
    //sum free
   /* for(i=0;i<hist_size;i++)
         free(sumlist[i]);
     free(sumlist);*/

    return sumlist;

}


Table_Info *get_table(char *filename, int needed) {

    char ch;
    int i;
    int colum_orig, rows, one = 1;
    colum_orig = 2;
    rows = 0;
    FILE *fp = fopen(filename, "r");

    // i = fgetc(fp);
    //  printf("%d ", i);

    while (!feof(fp))//get rows and columns
    {
        ch = fgetc(fp);

        if (one == 1 && ch == ',')
            colum_orig++;
        if (ch == '\n') {
            rows++;
            one = 0;
        }
    }

    //printf("rows %d , columls %d   \n", rows, colum_orig);
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
    retur->columns = columls;
    retur->Bucket_list = malloc(sizeof(Radix_Head) * 8);//holds the buckets to re-radix
    for (i = 0; i < 8; i++) {
        retur->Bucket_list[i] = init_radix_List();

    }


    while (fgets(line, 500, fp) != NULL) {
        //printf("line: %s :",line);


        retur->location[count] = 1; //initialise possition matrix
        columls = 1;
        retur->TableA[count][0] = count;//pass id

        usless = strtok(line, ",");

        if (columls == needed)
            retur->TableA[count][1] = Sto64(usless);// pass values
        // printf( "value  %s in k: %d\n", usless,k );
        columls++;


        while (usless != NULL) {


            usless = strtok(NULL, ",");
            //    printf( " %s\n", usless );

            if (usless != NULL) {
                if (columls == needed)
                    retur->TableA[count][1] = Sto64(usless);
                columls++;
                //  printf( "value  %s in k: %d\n", usless,k );
                //  printf("in table value :[%" PRIu64 "] \n"   ,Sto64(usless));
            }
        }
        // printf("[%" PRIu64 " ,%"PRIu64 "] \n"   ,retur->TableA[count][0], retur->TableA[count][1]);
        count++;
        //   printf("count: %d \n",count);
       // if (count == 1000)
         //   printf("debug \n");
    }
    fclose(fp);
//print(retur);

    return retur;


}

Table_Info *flip_tables(Table_Info *table) {
    uint64_t **temp;
    temp = table->TableA;
    table->TableA = table->TableB;
    table->TableB = temp;
    table->time++;
    //printf("FLIPPING \n");
    return table;
}

results *big_short(char *filename, int needed) {
    // int quick_short=10;

    int from, to, i, j, hist_size = 256;

    Table_Info *table;
    table = get_table(filename, needed);
    int **sumlist;
    from = 0;
    to = table->rows;

    sumlist = radix_Sort(table, table->time, from, to);          //mandatory radix
    //printf("\n sumlist!1 \n");
    // for(i=0;i<hist_size;i++)
       //printf(" %d || %d \n",sumlist[i][0], sumlist[i][1]);

    for (i = 0; i < hist_size; i++) {

        if (i < hist_size - 1) {//get from to
            to = sumlist[i + 1][1];
        }
        if (i == hist_size - 1)
            to = table->rows;
        from = sumlist[i][1];


        if (from < to) {
            // if ((table->TableB[to - 1][1] != table->TableB[from][1])) {
            if (to - from + 1 > quick_short) {
                //printf("bigger from %d to %d with hash %d\n", from, to, i);
                list_Add_Bucket(&table->Bucket_list[0], from, to,
                                1);//add the buckets to be radixed to teh bucket list
            } else {
                //printf("quickshort from %d to %d with hash %d\n", from, to, i);
                quicksort(table->TableB, from, to - 1);
//print(table,from,to);
            }
            //  }

        }


    }

    for (i = 0; i < hist_size; i++)
        free(sumlist[i]);
    free(sumlist);

    for (j = 0; j < 8; j++) {       ////////////the rest of sumlists
        flip_tables(table);
        Radix_List *kl = table->Bucket_list[j]->first;


        while (kl != NULL) {


            //("called another sumlist at line from %d to %d  \n", kl->from, kl->to);
            //// print(table,kl->from,kl->to);
            sumlist = radix_Sort(table, table->time, kl->from, kl->to);
            ///  printf("\n sumlist!2 \n");
            /// for(i=0;i<hist_size;i++)
            ///    printf(" %d || %d \n",sumlist[i][0], sumlist[i][1]);

            for (i = kl->from; i < kl->to; i++) {
                table->location[i] = 1 - table->location[i];//change matrix location
            }


            for (i = 0; i < hist_size; i++) {

                if (i < hist_size - 1) {
                    to = sumlist[i + 1][1];
                }
                if (i == hist_size - 1)
                    to = kl->to;
                from = sumlist[i][1];


                if (from < to) {
                    //  if (((table->TableB[to - 1][1] != table->TableB[from][1])&&table->location[from] == 1)||((table->TableA[to - 1][1] != table->TableA[from][1])&&table->location[from] == 0) ) {// if it isnt the same number

                    if (((to - from + 1) > quick_short) && j < 7) {
                       // printf("add in bucket from %d to %d with hash %d\n", from, to, i);
                        list_Add_Bucket(&table->Bucket_list[j + 1], from, to, 1);
                    } else {
                        // printf("before!\n");
                        //  print(table,from,to);
                        /*
                          if (table->location[from] == 0) {
                              quicksort(table->TableA, from, to - 1);
                          } else {
                              quicksort(table->TableB, from, to - 1);
                          }
                          */
                        //printf("quickshort from %d to %d with hash %d\n", from, to, i);
                        quicksort(table->TableB, from, to - 1);
                        //  printf("not_before!\n");
                        // print(table,from,to);
                    }
                    //    }


                }

            }


            kl = kl->next;


            for (i = 0; i < hist_size; i++)
                free(sumlist[i]);
            free(sumlist);

        }


    }


    results *not_yet = (struct results *)malloc(sizeof(results));


    not_yet->rows = table->rows;

    not_yet->matrix = (uint64_t **) malloc(sizeof(uint64_t *) * table->rows);

    for (i = 0; i < table->rows; i++) {
        not_yet->matrix[i] = (uint64_t*) malloc(sizeof(uint64_t) * 2);
    }

    for (i = 0; i < table->rows; i++) {//get the data from the correct matrix
        if (table->location[i] == 0) {

            not_yet->matrix[i][0] = table->TableA[i][0];
            not_yet->matrix[i][1] = table->TableA[i][1];
        } else {

            not_yet->matrix[i][0] = table->TableB[i][0];
            not_yet->matrix[i][1] = table->TableB[i][1];

        }


    }
//print(table,0,8);
    j = 0;
    for (i = 0; i < 1000; i++)
        j = table->location[i] + j;
    //printf("loc %d \n", j);


    int zeros = 0;
    int ones = 0;
    for (i = 0; i < table->rows; i++) {


        //printf("|| %"PRIu64" , %"PRIu64" || %d ::%d loc:%d", not_yet->matrix[i][1], not_yet->matrix[i][0], i,
               //bithash2(not_yet->matrix[i][1], 0), table->location[i]);
        if (i < table->rows - 1) {
            if (not_yet->matrix[i][1] > not_yet->matrix[i + 1][1]) {
                if (table->location[i] == 0) {
                    zeros++;
                } else {
                    ones++;
                }
                //printf("  fuck ");
            }
            //printf("\n");
        }
    }
    //printf("\n zer0s %d : ones %d \n", zeros, ones);

   free_table(table);


    return not_yet;


}


void free_table(Table_Info *table) {
    int i;

    /*for (i = 0; i < table->rows; i++) {
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

info_node* join_matrices(results* A, results* B) {

    info_node* list;
    node_type* cur_node = NULL;
    int rowA,rowB,i,j;
    uint64_t targetA, targetB;
    int targetIDA, targetIDB, current_looked;

    list = list_creation();
    current_looked = 0;

    for (i = 0; i < A->rows; i++) {

        targetA = A->matrix[i][1];
        targetIDA = A->matrix[i][0];
        for (j = current_looked;  j < B->rows ; j++) {

            targetB = B->matrix[j][1];
            targetIDB = B->matrix[i][0];
            if (targetA == targetB) {

                list_insert(list, targetIDA, targetIDB, &cur_node);
            }
            else if (targetA < targetB) {

                current_looked = j;
                break;
            }
        }
    }


    return list;
}