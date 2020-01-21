
#ifndef RELATIONS_H
#define RELATIONS_H

#include <inttypes.h>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include <stdbool.h>
#include "Radix.h"
#include <math.h>
#define max_line_length 500
#define work_slave "mywork.txt"


pthread_mutex_t mutexsumbig;
pthread_mutex_t mutexbig;


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


typedef struct neibour_node{
    int bol;
    int priority_line;



}neibour_node;



typedef struct Tables_Table{
    int num_of_tables;
    int work_file;
    struct Single_Table* tables;

}List_of_Tables;

typedef struct priority {
    char *command;
    uint64_t size,number;
    int type;
    int col1,col2,master_table1,master_table2,here_table1,here_table2;
}priority;


typedef struct summa {

    int col,master_table,here_table;
}summa;


typedef struct just_transfer {
    priority* priority1;
    int priority_number;
    summa* suma;
    int num_of_tables,suma_size;    //posa ine ta from tables
    int* tables;                    // pia einai ta from tables
    tableid* tables_ids;

} just_transfer;

typedef struct result{
    int result_numb;
    uint64_t * result;
    int empty;
}result;

typedef struct job_big{
    char * line;
    List_of_Tables* master_table;
    result* res;
}job_big;

typedef struct jobqueue_big{
    job_big* jobs;
    int size;
    int used;
    int thread_num;
}jobqueue_big;



uint64_t Sto64(const char *s);
void priority_tree(priority* prior,int priority_number,just_transfer* just,List_of_Tables* master_table);
int min_priority(priority* prior,int priority_number);
void swap_priority(priority* prior,int from,int to);
void short_priority(priority* prior,int prior_num);
Single_Table fill(char* filename,int name);
Single_Table*  simple_mesure(Single_Table* table,uint64_t num,int type,int column);
int read_init(char *filename);
List_of_Tables init_Tables(char*initfile);
just_transfer* analise(char* str,List_of_Tables* master_table);
//void quicksort(priority* number,int first,int last);
//middle* run_filters(List_of_Tables temp_table,priority* priority_series,int priority_number, int max_priority);
middle* run_filters(List_of_Tables* master_table,just_transfer* transfer);


List_of_Tables run_joins(List_of_Tables* temp_table,middle* mid_table,int priority_number,int max_priority,priority* priority_series);
int parag(int input);
List_of_Tables* cost(int table1,int table2,int column1,int column2 ,List_of_Tables* temp_table);
int max(int* from,int from_num,List_of_Tables* master_table);
void permute(int *array,int i,int length,int** test);
void get_size(priority* prior,int priority_number,just_transfer* just, int now);
int** get_id_list(tableid * idlist);
void midle_scan(middle* midle,priority* prior,List_of_Tables* master_table);
List_of_Tables* get_data_from_file( List_of_Tables* master_table, int argc, char* argv[]);
int do_the_work(List_of_Tables* master_table, int argc, char* argv[]);


void free_list(int** list,int size);
void free_midle_table(middle* midle);
result* athrisma(middle* midle,just_transfer* transfer,List_of_Tables* master_table,int print);
void free_midle(middle* midle);
void free_big(List_of_Tables* master);
void free_transfer(just_transfer* transfer);
List_of_Tables *cost(int table1,int table2,int column1,int column2 ,List_of_Tables* temp_table);
float power(float basi,float pano);
uint64_t min_num(uint64_t a,uint64_t b);
uint64_t max_num(uint64_t a,uint64_t b);


void run_stats_filters(List_of_Tables* master_table,just_transfer* transfer,int priority_number);
void run_stats_joins(List_of_Tables* master_table,just_transfer* transfer,int prior);
void test_run_stats_joins(List_of_Tables* master_table,just_transfer* transfer,int priority_number);
void* big_thread(void* kk);
#endif //RELATIONS_H