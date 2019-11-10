#include <stdio.h>
#include <stdlib.h>

#include "Result_List.h"


void insert_first(info_node* list_info, int RowID_A, int RowID_B);
void insert_rest(info_node* list_info, int RowID_A, int RowID_B, node_type** current_pointer);

//=================================================================================================================
info_node* list_creation() {

	info_node* list_info;
	list_info = malloc(sizeof(info_node));
	list_info->size = 0;
	list_info->start = NULL;
	list_info->end = NULL;
	return list_info;
}

//=================================================================================================================
void list_destruction(info_node** list_info) {

	node_type *todel, *todel2;
	todel = (*list_info)->start;

	if (todel == NULL) {
		free(*list_info);
		(*list_info) = NULL;
		return;
	}

	do
	{
		todel2 = todel;
		todel = (todel)->next_node;
		free(todel2);
	} while (todel != (*list_info)->start);

	(*list_info)->start = NULL;
	(*list_info)->end = NULL;
	free(*list_info);
	(*list_info) = NULL;
}

//=================================================================================================================
int list_empty(info_node* list_info) {

	return (list_info->start == NULL);
}

//=================================================================================================================

void return_node_data(node_type* cur, int position, int* RowID_A, int* RowID_B) {

	cur->results[position][0] = *RowID_A;
    cur->results[position][1] = *RowID_B;

}


//=================================================================================================================
void list_insert(info_node* list_info, int RowID_A, int RowID_B, node_type** current_pointer) {

    int position;

	if ((*current_pointer) == NULL) {

		insert_first(list_info, RowID_A, RowID_B);
        (*current_pointer) = list_info->start;
	}
	else if ((*current_pointer)->size < result_size) {

        position = (*current_pointer)->size;
        (*current_pointer)->results[position][0] = RowID_A;
        (*current_pointer)->results[position][1] = RowID_B;
        (*current_pointer)->size++;

	}
	else {

	    insert_rest(list_info, RowID_A, RowID_B, current_pointer);
        (*current_pointer) =  (*current_pointer)->next_node;
	}
}

//=================================================================================================================
void insert_first(info_node* list_info, int RowID_A, int RowID_B) {

	node_type *current, *tmp, *last;

	current = malloc(sizeof(node_type));
	if (current == NULL) {

	    printf("Allocation Problem Insert First");
		return;
	}

    current->results[0][0] = RowID_A;
    current->results[0][1] = RowID_B;
	current->size = 1;


	if (list_empty(list_info)) {
		current->previous_node = current;
		current->next_node = current;
	}
	else {

		tmp = list_info->start;
		last = tmp->previous_node;

		current->next_node = tmp;
		current->previous_node = tmp->previous_node;
		tmp->previous_node = current;
		if (tmp->next_node == tmp) tmp->next_node = current;
		last->next_node = current;
	}

	list_info->start = current;
	list_info->end = current->previous_node;
	list_info->size++;
}

//=================================================================================================================
void insert_rest(info_node* list_info, int RowID_A, int RowID_B, node_type** current_pointer) {

    int position;
	node_type* current;

	current = malloc(sizeof(node_type));
	if (current == NULL) {

        printf("Allocation Problem Insert Rest");
		return;
	}
	else {

        current->results[0][0] = RowID_A;
        current->results[0][1] = RowID_B;
        current->size = 1;

		current->next_node = (*current_pointer)->next_node;
		current->previous_node = *current_pointer;
		if (current->next_node != list_info->start)
			current->next_node->previous_node = current;
		else {
			list_info->start->previous_node = current;
			list_info->end = current;
		}

        (*current_pointer)->next_node = current;
		list_info->size++;
	}
}

//=================================================================================================================
void list_delete(info_node* list_info, node_type** current_pointer) {

	node_type *previous, *next;

	if (list_empty (list_info) || current_pointer == NULL) {

        printf("Nothing to delete");
		return;
	}

	previous = (*current_pointer)->previous_node;
	next = (*current_pointer)->next_node;
	previous->next_node = next;
	next->previous_node = previous;

	if (list_info->start == current_pointer) {

		list_info->start = next;
	}

	if (list_info->end == current_pointer) {

		list_info->end = previous;
	}

	current_pointer = previous;
	list_info->size--;
	if (list_info->size == 0) {

		current_pointer = NULL;
		list_info->start = NULL;
		list_info->end = NULL;
	}
}

//=================================================================================================================
void LIST_next_node(node_type* p) {

	if (p != NULL)
		p = p->next_node;

}

//=================================================================================================================
void LIST_proigoymenos(node_type* p) {

	if (p != NULL)
		p = p->previous_node;

}

//=================================================================================================================
//=================================================================================================================
