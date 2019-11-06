//
// Created by dimitris on 01/11/2018.
//

#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H

#include <stdint.h>
typedef struct Table_Info{

    uint64_t** Table;
    int columns;
    int rows;
}Table_Info;


typedef struct Listnode{

    int id;
    struct Listnode* next;

}Listnode;

typedef struct head{

    Listnode* first;
    int size;

}Head;




typedef struct Combined_Struct{
    Table_Info* reordered;
    Table_Info* histogram;
}Combined_Structs;


//void radix(int n,int size);


void list_Add_Id(Head **head1, int id);
Head* init_List();
int bithash2(uint64_t hash_value,int time);
int bithash(int64_t hash_value,int hash_key);
//void init(Table_Info*table,int colum,int row);
void print(Table_Info* table);
Table_Info* getrow(Table_Info* pi,int column);
Combined_Structs* radix_Sort(int n, Table_Info *table);
Table_Info* get_table(char* filename);
uint64_t Sto64(const char *s);
#endif //RADIX_RADIX_H