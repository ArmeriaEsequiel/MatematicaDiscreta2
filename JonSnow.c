#include "JonSnow.h"


WinterIsHere WinterIsComing() {
	WinterIsHere W = NULL;
	WinterIsHere error = NULL; //solo para verificar si se produjo un error
	u32 i, j;

	W = calloc(1, sizeof(struct _WinterSt));

    //obtengo el numero de aristas y vertices, y lo guarda en la estructura del grafo
    error = get_nEdge_mVertex(W);

    //si hubo un error, devuelvo null
    if(error == NULL){
    	//libero el grafo
    	free(W);
    	return error;
    }
    
    //pido memoria para el arreglo de vertices
    W->vertex = calloc(NumeroDeVertices(W), sizeof(Vertex));
	//inicializo el arreglo
    initializeArrayVertex(W);

	//leo aristas, guardo en el arreglo los vertices y en la lista sus vecinos
    error = getEdges(W);

    if(error == NULL){
    	//elimino lo que tengo en el grafo hasta el momento
    	free(W->vertex);
    	free(W);
    	return error;
    }

    //paso la lista de vecinos al arreglo d indices de vecinos
    for (i=0; i<W->nVertex; i++) {
        W->vertex[i] = fromListToArray(W->vertex[i], W);
    }

    //creo el arreglo mutable
    W->mutableOrder = calloc(W->nVertex, sizeof(u32));

    for(j=0; j<W->nVertex; j++){
    	W->mutableOrder[j] = j;
    }

	return(W);
}

int Primavera(WinterIsHere W){
	int result = 0;
	u32 j,i;

	//Destruccion de los vertices
    for(j=0; j<NumeroDeVertices(W); j++){
    	free(W->vertex[j]->neighbour);
    	W->vertex[j]->neighbour = NULL;
    	W->vertex[j]->neighbourList = DestroyList(W->vertex[j]->neighbourList);
    	free(W->vertex[j]);
    	W->vertex[j] = NULL;
    }
    //libero arreglo de vertices en el grafo
    free(W->vertex);
    W->vertex = NULL;
    
    //libero arreglo de orden mutable
    free(W->mutableOrder);
    W->mutableOrder = NULL;
    
  	//libero la tabla hash
    for(i=0; i<W->sizeHash; i++){
    	W->hash[i] = DestroyList(W->hash[i]);
    	free(W->hash[i]);
    	W->hash[i] = NULL;
    }

    free(W->hash);
    W->hash = NULL;

    //libero el grafo
    free(W);
	W = NULL;

    if(W == NULL){
    	result = 1;
    }

    return (result);
}


//FUNCIONES AUXILIARES
WinterIsHere get_nEdge_mVertex(WinterIsHere W){
 	char c;
 	char chain[80]; //cadena a leer
 	char edge[20]; //cadena "edge"
 	char *line = NULL; //cadena leida
 	u32 result = 0;
    u32 nVertex = 0;
    u32 mEdge = 0;
 	
 	while(true) {
	 	//obtengo el primer char de estandar input
	 	c = fgetc(stdin);
	 	if (c == 'p'){ //senala la cantidad de vertides y aristas
	 		result = scanf("%s %u %u\n", edge, &nVertex, &mEdge);
	 		if(result < 1){
	 			printf("Error en la lectura.\n");
	 			return NULL;
	 		}
	 		break;
	 	}
	 	if(c != 'p'){
	 		line = fgets(chain, 80, stdin);
	 		if(line == NULL){
	 			printf("Error en la lectura.\n");
	 			return NULL;
	 		}
	 	}
	 }

	 W->nVertex = nVertex;
	 W->mEdge = mEdge;
	 return W;
}

WinterIsHere getEdges(WinterIsHere W){
	u32 vertex1 = 0;
	u32 vertex2 = 0;
	u32 result = 0;
 	u32 index = 0;
 	u32 k = 1;
 	u32 position1, position2, pos;
 	u32 numberOfVertex;
	char c;
	char chain[80]; //cadena a leer
 	char *line = NULL;
 	bool esprimo = false;
 	int i, cleanBuffer;
 	

 	//creo tabla hash
 	numberOfVertex = W->nVertex;
 	
    //asigno el tamaño para el hash, busco que sea de tamaño primo
    if (esPrimo(numberOfVertex)){
		W->hash = createHash(numberOfVertex);
	} else {
		numberOfVertex += 1;
		while(!esprimo){
			if (esPrimo(numberOfVertex)) {
				esprimo = true;
			} else {
				numberOfVertex += 1;
			}
		}
		W->hash = createHash(numberOfVertex);
	}
	W->sizeHash = numberOfVertex;

	while(k <= W->mEdge){//mientras haya aristas por leer
		k++;
 		c = '\0';
 		c = fgetc(stdin);
 		if(c == 'e'){ //leo arista
 			result = scanf("%d %d\n", &vertex1, &vertex2);
 			if (result >= 1){
 				//vertice 1
 				position1 = getKey(vertex1, numberOfVertex);
 				i = vertexExist(W, vertex1, position1);
 				if(i == -1){
 					//si el vertice no existe, agrego el indice a la lista
 					W->hash[position1] = addToList(W->hash[position1], index);
 					//lo agrego en el arreglo de vertices
 					addVertex(W, vertex1, index);
 					//agrego su vecino
 					W->vertex[index]->neighbourList = addToList(W->vertex[index]->neighbourList, vertex2);
 					index++;
 				} else {
 					//si el vertice existe agrego al vecino
 					//el indice del vertice es i
 					pos = (u32)i;
 					W->vertex[pos]->neighbourList = addToList(W->vertex[pos]->neighbourList, vertex2);
 				}

 				//vertice 2
 				position2 = getKey(vertex2, numberOfVertex);
 				i = vertexExist(W, vertex2, position2);
 				if(i == -1){
 					//si el vertice no existe, agrego el indice a la lista
 					W->hash[position2] = addToList(W->hash[position2], index);
 					//lo agrego en el arreglo
 					addVertex(W, vertex2, index);
 					//agrego su vecino
 					W->vertex[index]->neighbourList= addToList(W->vertex[index]->neighbourList, vertex1);
 					index++;
 				} else {
 					//si el vertice existe agrego su vecino
 					pos = (u32)i;
 					W->vertex[pos]->neighbourList = addToList(W->vertex[pos]->neighbourList, vertex1);	
 				}
 			}
 		} else { //ignoro comentarios y cant d vertices
 			line = fgets(chain, 80, stdin);	

 			//limpio el buffer de lectura
			while((cleanBuffer = getchar()) != '\n' && cleanBuffer != EOF);

			if(line == NULL){
				printf("Error en la lectura\n");
				free(W->hash);
				return NULL;
			}
 			
 		}
 	}
 	return W;
}

// Funciones auxiliares
u32 getGrade(Vertex V){
	return(V->neighbourList->length);
}

void initializeArrayNeighbour(u32 *neighbourPosition, u32 length){
	u32 i;
	for(i=0; i<length; i++){
		neighbourPosition[i] = 0;
	}
}

void initializeArrayVertex(WinterIsHere W){
	u32 j;

	for(j=0;j<W->nVertex; j++){
		W->vertex[j] = NULL;
	}
}	

void addVertex(WinterIsHere W, u32 vertex, u32 position){
	W->vertex[position] = calloc(1, sizeof(struct _VertexSt));
	W->vertex[position]->name = vertex;
	W->vertex[position]->grade = 0;
	W->vertex[position]->color = 0;
	W->vertex[position]->label = position;
	W->vertex[position]->neighbour = NULL;
	W->vertex[position]->neighbourList = NULL;
}


Vertex fromListToArray(Vertex V, WinterIsHere W){
	Node temp1 = NULL;
	u32 grade = 0; //grado de un vertice
	u32 i = 0;
	u32 position, key;

	V->grade = getGrade(V);
	grade = V->grade;

	V->neighbour = malloc(grade * sizeof(u32)); 
	initializeArrayNeighbour(V->neighbour, grade);


	if (V->neighbourList != NULL) {
		temp1 = V->neighbourList->firstNode;
	
		while(i<grade && temp1 != NULL) {
			key = getKey(temp1->index, W->sizeHash);
			position = (u32)vertexExist(W, temp1->index, key);
			V->neighbour[i] = position;
			i++;		
			temp1 = temp1->next;
		}
	}
	return (V);
}



//FUNCIONES PARA HASH
list *createHash(u32 size){
	list *hash = calloc(1,size * sizeof(list));
	if (hash != NULL){
		for(u32 i = 0; i < size; ++i){
			hash[i] = NULL;
		}
	}
	return (hash);
}


u32 getKey(u32 key, u32 size) {
	u32 pos = 0;
	pos = key % size;
	return pos;
}

bool esPrimo(u32 p){
	u32 i;
	if (p == 2){
		return true;
	}
	if (p % 2 == 0){
		//si no es dos y es par, no es primo
		return false;
	}
	//recorro los impares hasta la raiz de p
	for(i = 3; i*i <= p; i = i + 2){
		if (p % i == 0){
			//encontre uno que lo divide
			return false;
		}
	}
	//si llegue aca entonces es primo
	return true;
}


int vertexExist(WinterIsHere W, u32 vertex, u32 position){
	bool exist = false;
	u32 pos;
	int i = -1;
	Node aux = NULL;
	Node aux2 = NULL;
	if(W->hash[position] != NULL){
		aux = W->hash[position]->firstNode;
		//si en la posicion hay mas de un elemento, recorro la lista
		while(aux != NULL && !exist){
			pos = aux->index;
			if(W->vertex[pos]->name == vertex){
				exist = true;
				i = (int)pos;
			}
			aux2 = aux->next; 
			aux = aux2;
		}
	}
	return (i);
}
