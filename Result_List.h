#ifndef __Return_List__
#define __Return_List__

#define result_size 125*1024

//=======================================================================================

typedef struct node_type {

    int size;
    int	results[result_size][2];
    struct node_type*	next_node;
    struct node_type*	previous_node;
} node_type;

typedef struct info_node {

    int           size;
    node_type*    start;
    node_type*	  end;
} info_node;


/*List Creation and Destruction*/
info_node* list_creation();
void list_destruction(info_node** list_info);

/*Null Check*/
int	list_empty(info_node* list_info);

/*Insertion-Deletion*/
void list_insert(info_node* list_info, int RowID_A, int RowID_B, node_type** current_pointer);
void list_delete(info_node* list_info, node_type** current_pointer);

void return_node_data(node_type* cur, int position, int* RowID_A, int* RowID_B);

#endif //__Return_List__
