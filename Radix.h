
#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H
#include "Quicksort.h"
#include <stdint.h>
#include "Result_List.h"
#include <pthread.h>
//#include "relations.h"
#define  quick_short 500
#define  SizeofDataFileName 100
#define  middle__size 1000
#define sort_threads 0//<-
#define join_threads 0//<- really slow
#define big_threads 4
#define do_big_thread 1//if is 1 sort threads and join threads must be 0
#define join_pieces 1
#define total_threads 10// for skedjuler
#define print_in_line 1//only if big thread =1
pthread_mutex_t mutexsum;
pthread_mutex_t mutex;

pthread_mutex_t mutexsum_join;
pthread_mutex_t mutex_join;



//=================================================================================================================
typedef struct Listnode {

    int id,were;
    struct Listnode *next;
    struct Listnode *prev;

} Listnode;

//=================================================================================================================
typedef struct head {

    int size;
    Listnode *first;
    Listnode *last;

} Head;

//=================================================================================================================
typedef struct Radix_List {

    int from;
    int to;
    struct Radix_List *next;

} Radix_List;

//=================================================================================================================
typedef struct Radix_Head {

    int size;
    Radix_List *first;

} Radix_Head;

//=================================================================================================================

typedef struct Table_Info {

    int rows,needed,columns;
    int time;
    int *location;
    Radix_Head **Bucket_list;
    uint64_t **TableA;
    uint64_t **TableB;

} Table_Info;
//=================================================================================================================
typedef struct results {
    int columns;
    int rows;
    uint64_t **matrix;
} results;

//=================================================================================================================

typedef struct statistics{
    uint64_t upper,lower,distinct,full,table,row;
}statistics;



typedef struct tableid{

    int** id_list;
    int size;
    statistics* stats;

}tableid;



typedef struct usefull{

    int** sumlist;
    Head **refarray;

}usefull;



typedef struct middle_struct{
    int ** table;
    info_node* start;
    int* inserted;
    int num_inserted;
    int columns,size,matrix_size;

}middle;



typedef struct job_r2{
    Table_Info *table;
    int time;
    Head* use_this;
    int from;
    int to;



}job_sort;



typedef struct Row_Table{

    uint64_t *Column;

}Row_table;





typedef struct Single_Table{
    uint64_t column_num;
    uint64_t tube_num;
    Row_table* Full_Table;
    //  int* id_table;
    int table_name;
    statistics* stats;
}Single_Table;


typedef struct jobqueue_sort{
    job_sort* first;//skedj
    job_sort* last;//skedj
    job_sort* jobs;
    int size;
    int used;
    int thread_num;
}jobqueue_sort;

typedef struct hold_more{
    int** holl_up;
    struct hold_more*  next;
    int id;
}hold_more;

typedef struct result{
    int result_numb;
    uint64_t * result;
    int empty;
}result;

typedef struct Tables_Table{
    int num_of_tables;
    int work_file;
    struct Single_Table* tables;

}List_of_Tables;

typedef struct job_big{
    char * line;
    List_of_Tables* master_table;
    result* res;
}job_big;
typedef struct job_join{
    results* A;
    results* B;
    int needed;
    int middle_matrix_size;
    int added;
    int to;
    int from;
    int** new_middle;
}job_join;

typedef struct jobqueue_join{
    job_join* jobs;
    int size;
    int used;
    int thread_num;
    job_sort* first;//skedj
    job_sort* last;//skedj
}jobqueue_join;

typedef struct main_struct{

    jobqueue_join* join_queue;
    jobqueue_sort* sort_queue;
    job_big* big_queue;
    int big_jobs;
    int sort_jobs;
    int join_jobs;
    pthread_mutex_t mutex1;
    pthread_mutex_t mutex2;
    pthread_cond_t cond1;
    pthread_cond_t cond2;
    int mut1;
    int mut2;
    int used;
    int start_together;
    int totaljobs;
    pthread_t tid ;
    int done;
}main_struct;



Radix_Head *init_radix_List();

void list_Add_Id(Head **head1, int id);

void list_Add_Bucket(Radix_Head **head1, int from, int to);

Table_Info *flip_tables(Table_Info *table);

Head *init_List();

int bithash2(uint64_t hash_value, int time);

void print(Table_Info *table, int from, int to,int columns);

usefull* radix_Sort(Table_Info *table, int time, int from, int to);
void radix_Sort2(Table_Info *table, int time,Head* use_this, int from, int to);
//Table_Info *get_table(char *filename, int needed);
Table_Info *get_table(uint64_t* col,int** idlist,int colums,int rows,int needed );
//uint64_t Sto64(const char *s);

//results *big_short(char *filename, int needed);
results *big_short(uint64_t* col,int** idlist,int colums,int rows,int needed );

void free_table(Table_Info *table);

int** join_matrices(results* A, results* B,int needed,int middle_matrix_size,int * size);
//results *  simple_mesure(results* A,uint64_t num,char operator);
void list_Add_Id2(Head **head1,Head **from, int location,Listnode *temp);
void free_results(results * A);
results* get_old_results(uint64_t* col,int** idlist,int colums,int rows,int needed);
void* short_thread(void* kk);
void* join_thread(void* kk);
void*join_test(job_join* join);
//=================================================================================================================

//=================================================================================================================

#endif //RADIX_RADIX_H