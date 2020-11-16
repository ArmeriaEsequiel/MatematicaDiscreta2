#include "JonSnow.h"

//Funciones de los vertices

//Función que devuelve el nombre del vértice. 
u32 NombreDelVertice(WinterIsHere W, u32 x) {
    u32 vertex_name;
    vertex_name = W->vertex[x]->name;
    return (vertex_name);
}

//Función que devuelve el color del vértice y 0 si no tiene color.
u32 ColorDelVertice(WinterIsHere W, u32 x) {
    u32 vertex_color;
    vertex_color = W->vertex[x]->color;
    return (vertex_color);
}

//Función que devuelve el grado del vértice. (Cantidad de vecinos)
u32 GradoDelVertice(WinterIsHere W, u32 x) {//VER, ME PARECE Q NO CORRESPONDE CON EL ENUNCIADO
    u32 vertex_grade;
    vertex_grade = W->vertex[x]->grade;
    return (vertex_grade);
}

// Función que devuelve la etiqueta del vecino i del vértice x y en el caso en que ese vecino
// no exista, se devuelve 0.
u32 IesimoVecino(WinterIsHere W, u32 x,u32 i) {
	u32 neighbourLabel;
	
	if(i < W->vertex[x]->grade) { // Verificamos que i esté dentro del rango de vecinos del vértice x.
		neighbourLabel = W->vertex[x]->neighbour[i];	
	} else {
		printf("No existe un vecino en la posicion %u.\n", i);
		neighbourLabel = 0;						
	}	

	return (neighbourLabel);
}

