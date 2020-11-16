#ifndef _LIST_H
#define _LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef unsigned int u32;

typedef struct _NodeSt *Node; 

typedef struct _ListSt *list;


struct _NodeSt {
    u32 index;
    Node next;
};

struct _ListSt {
    Node firstNode;
    Node lastNode;
    u32 length;
};


list addToList(list List, u32 index);
/* Agrega un elemento a una lista. */

list createList(void);
/* Crea una lista vacia. */

list DestroyList(list List);
/* Destruye una lista, devuelve NULL. */

bool empty(list List);
/* Devuelve true si la lista es vacia. Sino false. */

u32 first(list List);
/* Devuelve el primer elemento de la lista. */

list pop(list List);
/* Elimina el primer elemento de la lista.*/

Node initialize(Node new, u32 name);
/* Función que inicializa los campos de la estructura del nodo de la lista.*/

#endif