#include "List.h"



list createList(void){
    list List = NULL;
    List = calloc(1, sizeof(struct _ListSt));
    List->firstNode = NULL;
    List->lastNode = NULL;
    List->length = 0;
    return(List);
}

bool empty(list List){
	return(List->firstNode == NULL);
}

u32 first(list List){
	return(List->firstNode->index);
}

list pop(list List){
	Node aux = NULL;

	if(List->length > 1){
		aux = List->firstNode;
		List->firstNode = List->firstNode->next;
		free(aux);
	} else {
		free(List->firstNode);
		free(List);
		List = NULL;

	}
	return(List);
}

list addToList(list List, u32 index) {
    Node new_node = NULL;
    Node last_node = NULL;
    new_node= calloc(1, sizeof(struct _NodeSt));
    initialize(new_node, index);

    if (List == NULL) { // Si la lista está vacía agrega directamente el vecino.
    	List = createList();
        List->firstNode = new_node;
        List->lastNode = new_node;        
    } else {
        last_node = List->lastNode;
        List->lastNode = new_node;
        last_node->next = new_node;
    }

    List->length = List->length + 1;

    return(List);
}

Node initialize(Node new, u32 name){
    new->index = name;
    new->next = NULL;
    return(new);
}

list DestroyList(list List){
    Node temp1 = NULL;
    Node temp2 = NULL;

    if(List != NULL){
        temp1 = List->firstNode;
        while( temp1 != NULL){
            temp2 = temp1->next;
            temp1->index = 0;
            temp1->next = NULL;
            free(temp1);
            temp1 = temp2;
        }
        free(List);
        List = NULL;
    }
    return(List);
}