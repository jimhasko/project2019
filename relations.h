//
// Created by dimitris on 06/01/2019.
//

#ifndef PROJECT2018_RELATIONS_H
#define PROJECT2018_RELATIONS_H

#endif //PROJECT2018_RELATIONS_H



#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include "Radix.h"

typedef struct Row_Table{

    uint64_t *Column;

}Row_table;


typedef struct statistics{
    uint64_t upper,lower,distinct,full,table,row;
}statistics;


typedef struct Single_Table{
    uint64_t column_num,tube_num;
    Row_table* Full_Table;
    int* id_table;
    int table_name;
    statistics* stats;
}Single_Table;

typedef struct middle_struct{

    int** id_lists;
    uint64_t size;

}middle;

typedef struct neibour_node{
    int bol;
    int priority_line;


}neibour_node;



typedef struct Tables_Table{
    int num_of_tables;
    struct Single_Table* tables;

}List_of_Tables;

typedef struct priority {
    char *command;
    uint64_t size,number;
    int type;
    int col1,col2,master_table1,master_table2,here_table1,here_table2;
}priority;


typedef struct tableid{

    int* id_list;
    int size;


}tableid;

typedef struct just_transfer{
    priority* priority1;
    int priority_number;
   // List_of_Tables temp_table;
    int num_of_tables;//posa ine ta from tables
    int* tables;// pia einai ta from tables
    tableid* tables_ids;
}just_transfer;





Single_Table fill(char* filename,int name);
Single_Table*  simple_mesure(Single_Table* table,uint64_t num,int type,int column);
int read_init(char *filename);
List_of_Tables init_Tables(char*initfile);
just_transfer* analise(char* str,List_of_Tables* master_table);
//void quicksort(priority* number,int first,int last);
//middle* run_filters(List_of_Tables temp_table,priority* priority_series,int priority_number, int max_priority);
middle* run_filters(List_of_Tables* master_table,just_transfer* transfer);
int power(int basi,int pano);
List_of_Tables run_joins(List_of_Tables* temp_table,middle* mid_table,int priority_number,int max_priority,priority* priority_series);
int parag(int input);
List_of_Tables* cost(int table1,int table2,int column1,int column2 ,List_of_Tables* temp_table);
int max(int* from,int from_num,List_of_Tables* master_table);
void permute(int *array,int i,int length,int** test);