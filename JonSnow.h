#ifndef _JONSNOW_H
#define _JONSNOW_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"


#include <time.h>

typedef unsigned int u32; //tipo de dato para especificar un entero sin signo de 32 bits.

typedef struct _WinterSt *WinterSt; // Estructura del grafo.

typedef struct _WinterSt *WinterIsHere;

typedef struct _VertexSt *Vertex; // Estructura de un vertice.

typedef struct _VertexColor *VertexColor; //Guarda en el arreglo "indexVertex" los vértices que están coloreados
										 //segun el color(posición en el arreglo) que indique "CountColor".
                                        // En length guarda la cantidad de vértices coloreados con ese color.

struct _WinterSt {
    Vertex *vertex;     //Arreglo de vértices de orden fijo.
    u32 *mutableOrder;  //Arreglo de orden mutable, guarda el indice del arreglo de vertices
    u32 nVertex;        //Numero total de vertices en el grafo.
    u32 mEdge;          //Numero total de lados en el grafo.
    u32 chromatic;      //La cantidad de colores usada en el coloreo.
    u32 maxGrade;       //El grado maximo del grafo.
    list *hash;     	//Tabla hash solo usada para la carga del grafo.
    u32 sizeHash;       //Tamanio de la tabla hash. Necesaria para calcular la clave.
    VertexColor *CountColor; //Arreglo de vertices por cada color. El color esta determinado por el indice
                            //sin contar el 0
};


struct _VertexSt {
    u32 name;  	        //Nombre del vertice
    u32 grade;		    //Cantidad de vecinos
    u32 color;			//Color del vertice
    u32 label;			//Marca la posición del vértice en el arreglo de vértices.Etiqueta
    u32 *neighbour;		//Arreglo de vecinos, guarda la posicion en la q el vecino se 
    					//encuentra en el arreglo de vertices de orden fijo
    list neighbourList; //Lista enlazada de vecinos usada en la carga del grafo.
};

struct _VertexColor {
    u32 *indexVertex;   //indice de vecinos
    u32 length; 		//cantidad de vertices por color
};

//Funciones de destruccion/destruccion del grafo

WinterIsHere WinterIsComing();
/*La funcion aloca memoria, inicializa lo que haya que inicializar de una estructura 
* WinterSt, lee un grafo desde standard input en el formato indicado, lo carga a la
* estructura y devuelve un puntero a esta.
* Ademas de cargar el grafo, colorea todos los vertices con 0.
* En caso de error, la funcion devolvera un puntero a NULL.
*/

int Primavera(WinterIsHere W);
/* Destruye W y libera la memoria alocada. Retorna 1 si todo anduvo bien y 0 si no. */


//Info del Grafo
u32 NumeroDeVertices(WinterIsHere W);

u32 NumeroDeLados(WinterIsHere W);

u32 NumeroVerticesDeColor(WinterIsHere W,u32 i);

u32 NumeroDeColores(WinterIsHere W);

u32 IesimoVerticeEnElOrden(WinterIsHere W,u32 i);

//Funciondes de los vertices
u32 NombreDelVertice(WinterIsHere W, u32 x);

u32 ColorDelVertice(WinterIsHere W, u32 x);

u32 GradoDelVertice(WinterIsHere W, u32 x);

u32 IesimoVecino(WinterIsHere W, u32 x,u32 i);

// Funciones de ordenación
void OrdenNatural(WinterIsHere W);

void OrdenWelshPowell(WinterIsHere W);

void AleatorizarVertices(WinterIsHere W,u32 x);

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x);

// Funciones de coloreo
u32 Greedy(WinterIsHere W);
/* Corre Greedy en W con el orden interno que debe estar guardado de alguna forma dentro de W. 
* Devuelve el numero de colores que se obtiene.
*/

int Bipartito(WinterIsHere W);
/* Devuelve 1 si W es bipartito, 0 si no. Ademas, si devuelve 1, colorea W con un coloreo
*  propio de dos colores.
*/

//Funciones auxiliares
WinterIsHere get_nEdge_mVertex(WinterIsHere W);
/* Lee desde standard input la cantidad de vertices y aristas que contiene el grafo.
 * Guarda los valores obtenidos en la estructura del grafo.
 * Si hubo algun error, devuelve un puntero a NULL.
 */

WinterIsHere getEdges(WinterIsHere W);
/* Lee las aristas desde standard input y las guarda en la estructura del grafo. 
 * Si hubo un error, devuelve un puntero a NULL.
 */

void addVertex(WinterIsHere W, u32 vertex, u32 position);
/* Agrega e inicializa un nuevo vertice al arreglo de vertices en la posicion indicada. */

Vertex fromListToArray(Vertex V, WinterIsHere W);
/* Pasa una lista de nombres de vecinos, a un arreglo con las posiciones de dichos vecinos. */

void initializeArrayVertex(WinterIsHere W);
/* Inicializa el arreglo de vertices con NULL. */

u32 getGrade(Vertex V);
/* Obtiene el grado de un vertice. */

void initializeArrayNeighbour(u32 *neighbourPosition, u32 length);
/* Inicializa el arreglo de las posiciones de los vecinos con 0. */


//Funciones Auxiliares de ordenación
int MinorToMayor(const void * fst , const void * snd);
/* Regresa 0 si es menor el primer elemento que el segundo y 1 en caso contrario. */

int MayorToMinor(const void * fst , const void * snd);
/* Regresa 0 si es mayor el primer elemento que el segundo y 1 en caso contrario. */

void swap(WinterIsHere W, u32 first, u32 second);
/* Intercambia dos elementos del arreglo mutable. */

void createCountColor(WinterIsHere W);

void destroyCountColor(WinterIsHere W);


// Funciones para hash
list *createHash(u32 size);
/* Crea una tabla hash. Un arreglo de listas enlazadas. */

u32 getKey(u32 key, u32 size);
/* Devuelve una posicion para la tabla hash. */

bool esPrimo(u32 p);
/* Devuelve "true si p es primo. "*/

int vertexExist(WinterIsHere W, u32 vertex, u32 position);
/* Verifica si existe "vertex" en el grafo, dada una posicion.
* Si existe devuelve la posicion del arreglo de vertices en el q se encuentra.
* Si no existe devuelve -1. 
*/

#endif

// Florencia Soledad Ferreyra, mail: flor.sole.93@gmail.com
// Esequiel Armeria, mail: esequiel1308@gmail.com
// Maria Elena Quiroga, mail: sherutiny@gmail.com