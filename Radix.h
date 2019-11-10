
#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H

#include <stdint.h>
#include "Result_List.h"

#define  quick_short 100

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

    int rows;
    int time;
    int *location;
    Radix_Head **Bucket_list;
    uint64_t **TableA;
    uint64_t **TableB;

} Table_Info;

//=================================================================================================================
typedef struct results {

    int rows;
    uint64_t **matrix;
} results;

//=================================================================================================================

Radix_Head *init_radix_List();

void list_Add_Id(Head **head1, int id);

void list_Add_Bucket(Radix_Head **head1, int from, int to);

Table_Info *flip_tables(Table_Info *table);

Head *init_List();

int bithash2(uint64_t hash_value, int time);

void print(Table_Info *table, int from, int to);

int **radix_Sort(Table_Info *table, int time, int from, int to);

Table_Info *get_table(char *filename, int needed);

uint64_t Sto64(const char *s);

results *big_short(char *filename, int needed);

void free_table(Table_Info *table);

info_node* join_matrices(results* A, results* B);

//=================================================================================================================
//=================================================================================================================

#endif //RADIX_RADIX_H