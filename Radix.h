//
// Created by dimitris on 01/11/2018.
//

#ifndef RADIX_RADIX_H
#define RADIX_RADIX_H

typedef struct Table_Info{

    int** Table;
    int columns;
    int rows;
}Table_Info;


typedef struct listnode{

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
int bithash(int hash_value,int hash_key);
void init(Table_Info*table,int colum,int row);
void print(Table_Info* table);
Table_Info* getrow(Table_Info* pi,int column);
Combined_Structs* radix_Sort(int n, Table_Info *table);

#endif //RADIX_RADIX_H