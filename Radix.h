
#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H
#include "Quicksort.h"
#include <stdint.h>
#include "Result_List.h"
//#include "relations.h"
#define  quick_short 500
#define  SizeofDataFileName 100
#define  middle__size 500
//=================================================================================================================
typedef struct Listnode {

    int id;
    struct Listnode *next;

} Listnode;

//=================================================================================================================
typedef struct head {

    int size;
    Listnode *first;

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

typedef struct tableid{

    int* id_list;
    int size;


}tableid;

typedef struct middle_struct{
    int ** table;
    info_node* start;
    int* inserted;
    int num_inserted;
    int columns,size,matrix_size;

}middle;


Radix_Head *init_radix_List();

void list_Add_Id(Head **head1, int id);

void list_Add_Bucket(Radix_Head **head1, int from, int to);

Table_Info *flip_tables(Table_Info *table);

Head *init_List();

int bithash2(uint64_t hash_value, int time);

void print(Table_Info *table, int from, int to,int columns);

int **radix_Sort(Table_Info *table, int time, int from, int to);

//Table_Info *get_table(char *filename, int needed);
Table_Info *get_table(uint64_t* col,int** idlist,int colums,int rows,int needed );
//uint64_t Sto64(const char *s);

//results *big_short(char *filename, int needed);
results *big_short(uint64_t* col,int** idlist,int colums,int rows,int needed );

void free_table(Table_Info *table);

int** join_matrices(results* A, results* B,int needed,int middle_matrix_size,int * size);
//results *  simple_mesure(results* A,uint64_t num,char operator);
void free_results(results * A);
results* get_old_results(uint64_t* col,int** idlist,int colums,int rows,int needed);
//=================================================================================================================
//=================================================================================================================

#endif //RADIX_RADIX_H