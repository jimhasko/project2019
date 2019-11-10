
#ifndef JJ2019_SHHH_H
#define JJ2019_SHHH_H
#include "Radix.h"
#include <inttypes.h>
#endif //JJ2019_SHHH_H


typedef struct List_join{

    int** id_matrix;
    struct List_join* next;

}List_join;

typedef struct head_join{

    List_join* first;
    int size,buckets;

}Head_join;



Head_join* init_join_List();

void list_Add_Join(Head_join **head1, int id1,int id2);
Head_join* join(results* table1,results* table2);
void free_results(results* die);