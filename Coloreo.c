#include "JonSnow.h"

u32 Greedy(WinterIsHere W){
	u32 i, j, k, h, t;
	u32 labelVertex, labelNeighbour; //etiquetas
	u32 size;
	u32 colorNeighbour;
	bool findColor = false;
	u32 newColor = 0; 
	u32 *forbiddenColors; //arreglo de colores prohibidos para un vertice
	u32 numberOfVertex = W->nVertex; //cantidad de vertices

    //pido memoria para el arreglo de colores prohibidos
    if (W->chromatic == 0) {
    	//inicialmente es del tamanio de vertices + 1 xq no cuenta el color 0
    	size = numberOfVertex + 1;
        forbiddenColors = calloc(size, sizeof(u32));
    } else {
    	//sino le doy el tamanio de la candidad de colores usados + 2, 
    	//porque no uso el 0 y uno mas por si se necesita un color mayor a la cantidad anterior
        size = W->chromatic + 2;
        forbiddenColors = calloc(size, sizeof(u32));
    }

	//descolorea los vertices
    for (i = 0; i < numberOfVertex; i++) {		
        W->vertex[i]->color = 0;
    }

    //coloreo el primer vertice del arreglo de orden mutable con el color 1
    labelVertex = W->mutableOrder[0];
    W->vertex[labelVertex]->color = 1;
    
    //aumento la cantidad de colores usados
	W->chromatic = 1;

	//comienzo a iterar a partir del segundo vertice
    for (j=1; j < numberOfVertex; j++) {
    	//obtengo la posicion del vertice en el arreglo de orden mutable
        labelVertex = W->mutableOrder[j];

       	//seteo los valores del arreglo de colores prohibidos a cero
        for (k = 1; k <= W->chromatic + 1; k++) {
            forbiddenColors[k] = 0;
        }
        
		//completo el arreglo de colores prohibidos con el color de cada vecino,
		// poniendo 1 en la posicion dependiendo el color
        for (h = 0; h < W->vertex[labelVertex]->grade; h++) {
        	labelNeighbour = W->vertex[labelVertex]->neighbour[h];
        	colorNeighbour = W->vertex[labelNeighbour]->color;
        	forbiddenColors[colorNeighbour] = 1;
        }
      
        //busco la primer posicion donde haya un 0
        for (t = 1; t <= W->chromatic+1 && !findColor; t++) {
            if (forbiddenColors[t] == 0){
            	findColor = true;
            	newColor = t;
            }
        }

        //seteo la variable para la proxima vuelta del for
        findColor = false;
        //asigno al vertice el color permitido encontrado
        W->vertex[labelVertex]->color = newColor;

        //actualizo la cantidad de colores
		if(W->chromatic < newColor){
			W->chromatic = newColor;
		}

    }
								
    free(forbiddenColors);
    
	return(W->chromatic);
}


	
int Bipartito(WinterIsHere W){
	u32 i, j, k, h;
	list queue = NULL;
	u32 labelVertex, labelNeighbour;
	u32 color;

	//Descolorea los vertices si estan coloreados
	if (W->chromatic != 0){
		for(i=0; i<W->nVertex; i++){
			W->vertex[i]->color = 0;
		}
	}

	//BFS coloreando los vertices que aparecen con 1 si su nivel es par
	//con 2 si su nivel es impar

	//tomamos el primer vertice, el nodo raiz, y lo coloreamos con 2(nivel impar)
	W->vertex[0]->color = 2;
	
	//creamos una cola basada en listas enlazadas y lo enconlamos
	queue = addToList(queue, W->vertex[0]->label);

	//mientras la cola no este vacia
	while(!empty(queue)){
		//saco el primero
		labelVertex = first(queue);
		//lo elimino de la cola
		queue = pop(queue);

		//recorro sus vecinos
		for(j=0; j < W->vertex[labelVertex]->grade; j++){
			labelNeighbour = W->vertex[labelVertex]->neighbour[j];
			if(W->vertex[labelNeighbour]->color == 0){
				//si no esta coloreado, lo agrego a la cola
				queue = addToList(queue, labelNeighbour);
				//le doy el color dependiendo su nivel (contrario a su padre)
				W->vertex[labelNeighbour]->color = 3 - W->vertex[labelVertex]->color;
			}
		}
	}
	//destruir la cola
	queue = DestroyList(queue);

	//veo si el coloreo es propio
	for(k=0; k < W->nVertex; k++) {
		color = W->vertex[k]->color;
		for(h=0; h < W->vertex[k]->grade; h++){
			labelNeighbour = W->vertex[k]->neighbour[h];
			if(W->vertex[labelNeighbour]->color == color){
				//si dos vertices vecinos tienen el mismo color, no es 2-coloreable
				return 0;
			}
		}
	}
	//es 2-coloreable
	W->chromatic = 2;
	return 1;
}