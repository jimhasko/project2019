//
// Created by dimitris on 01/11/2018.
//

#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H

#include <stdint.h>


typedef struct Listnode{

    int id;
    struct Listnode* next;

}Listnode;

typedef struct head{

    Listnode* first;
    int size;

}Head;


typedef struct Radix_List{

    int from,to,location;

    struct Radix_List* next;

}Radix_List;

typedef struct Radix_Head{

    Radix_List* first;
    int size;

}Radix_Head;


typedef struct Table_Info{
    uint64_t** TableA;
    uint64_t** TableB;
    int columns;
    int rows;
    int * location;
    Radix_Head** Bucket_list;
    int time;
}Table_Info;


typedef struct Combined_Struct{
   // Table_Info* TableB;
    Table_Info* histogram;
}Combined_Structs;


//void radix(int n,int size);


void list_Add_Id(Head **head1, int id);
void list_Add_Bucket(Radix_Head **head1, int from,int to, int location);
Table_Info* flip_tables(Table_Info * table);
Head* init_List();
int bithash2(uint64_t hash_value,int time);
//int bithash(int64_t hash_value,int hash_key);
//void init(Table_Info*table,int colum,int row);
void print(Table_Info* table,int from, int to);
Table_Info* getrow(Table_Info* pi,int column);
int ** radix_Sort(Table_Info *table, int time, int from,int to);
Table_Info* get_table(char* filename,int needed);
uint64_t Sto64(const char *s);
uint64_t ** big_short(char* filename,int needed);
void free_table(Table_Info* table);
#endif //RADIX_RADIX_H