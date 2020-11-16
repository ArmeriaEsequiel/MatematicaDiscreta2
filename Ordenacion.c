#include "JonSnow.h"

typedef struct _Values *Values;

struct _Values {
    u32 value;
    u32 index;
};

// Regresa 0 si es menor el primer elemento que el segundo y 1 en caso contrario.
int MinorToMayor(const void * fst , const void * snd) {
    u32 first = (u32)((*(Values*)fst)->value);
    u32 second = (u32)((*(Values*)snd)->value);
    int result;
    if (first < second) {
        result = 0;
    } else {
        result = 1;
    }
    return(result);
}
void OrdenNatural(WinterIsHere W) {
    u32 index; // variable para indexar un arreglo.
    u32 lengthArray; // Cantidad de número de vértices.
    lengthArray = NumeroDeVertices(W);
    Values *array; // Array del tipo Values que tiene en value el nombre del vértice y en index
                // su posición en el arreglo de vértices.
    array = calloc(lengthArray, sizeof(struct _Values));

    // En este "for" se cargan los valores value e index según el arreglo de vértices de orden fijo.
    for(index = 0; index < lengthArray; index ++){
        array[index] = calloc(1, sizeof(struct _Values));
        array[index]->value = W->vertex[index]->name;
        array[index]->index = index;
    }

    // se ordena "array" de menor a mayor según "value".
    qsort(array, lengthArray, sizeof(Values), MinorToMayor);

    // Se actualiza orden mutable, según los valores de "index" en cada posición de "array".
    for(index = 0; index < lengthArray; index ++){
        W->mutableOrder[index] = array[index]->index;
    }

    // Se libera memoria
    for(u32 i = 0; i < lengthArray; i++){
        free(array[i]);
    }
    free(array);
}

// Regresa 0 si es mayor el primer elemento que el segundo y 1 en caso contrario.
int MayorToMinor(const void * fst , const void * snd) {
    u32 first = (u32)((*(Values*)fst)->value);
    u32 second = (u32)((*(Values*)snd)->value);
    int result;
    if (first > second) {
        result = 0;
    } else {
        result = 1;
    }
    return(result);
}

void OrdenWelshPowell(WinterIsHere W) {
    u32 index; // variable para indexar un arreglo.
    u32 lengthArray; // Cantidad de número de vértices.
    lengthArray = NumeroDeVertices(W);
    Values *array;  // Array del tipo Values que tiene en value el grado del vértice y en index
                // su posición en el arreglo de vértices.
    array = calloc(lengthArray, sizeof(struct _Values));

    // En este "for" se cargan los valores value e index según el arreglo de vértices de orden fijo.
    for(index = 0; index < lengthArray; index ++){
        array[index] = calloc(1, sizeof(struct _Values));
        array[index]->value = W->vertex[index]->grade;
        array[index]->index = index;
    }

    // se ordena "array" de mayor a menor según "value".
    qsort(array, lengthArray, sizeof(struct _Values), MayorToMinor);

    // Se actualiza orden mutable, según los valores de "index" en cada posición de "array".
    for(index = 0; index < lengthArray; index ++){
        W->mutableOrder[index] = array[index]->index;
    }

    // Se libera memoria
    for(u32 i = 0; i < lengthArray; i++){ 
       free(array[i]);
    }
    free(array);
}

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x) {
    createCountColor(W);

    if (x == 0) {
        u32 NumColors, i, vertexCount, j, k, vertexlastColorCount;
        i = 0;
        j = 0;
        k = 0;
        vertexCount = 0;
        vertexlastColorCount = 0;
        NumColors = W->chromatic; //Cantidad de colores usados
        vertexlastColorCount = W->CountColor[NumColors]->length;// Cantidad vertices en el color R
        for(i=0; i<vertexlastColorCount; i++){
            W->mutableOrder[i] = W->CountColor[NumColors]->indexVertex[i];// Se pone al principio el color R
        }
        for (j= 1; j <= NumColors - 1; j++){ // Por cada color sin contar el ultimo
            vertexCount= W->CountColor[j]->length; // Cantidad de vertices del color;
            for(k = 0; k < vertexCount; k++){ 
                W->mutableOrder[vertexlastColorCount] = W->CountColor[j]->indexVertex[k];//Empezando por el color J, pongo todos los vertices
                vertexlastColorCount++;//posicion del ultimo vertice agregado en el arreglo
            }

        }
    } else if (x == 1) {
        u32 NumColors,vertexCount, j, k, vertexCountLast;
        k = 0;
        j = 0;
        vertexCount = 0;
        vertexCountLast = 0;
        NumColors = W->chromatic; //Cantidad de colores usados
        //vertexlastColorCount = W->CountColor[NumColors]->length;// Cantidad vertices en el color R
        for (j= NumColors ; j > 0; j--){
            vertexCount= W->CountColor[j]->length;
            for(k = 0; k < vertexCount; k++){
                W->mutableOrder[vertexCountLast] = W->CountColor[j]->indexVertex[k];
                vertexCountLast++;
            }

        }
    } else if (x == 2) {
        u32 index; // variable para recorrer el arreglo "array"
        u32 jindex; // variable para recorrer el arreglo "indexVertex" de CountColor.
        u32 position; // posicion en countColor.
        u32 stop; // Se usa como cota superior en el for que recorre CountColor
        u32 lengthArray; // Largo de "array" que es el coloreo máximo del grafo.
        lengthArray = W->chromatic;
        Values *array; // Arreglo del tipo "Values".
        array = calloc(lengthArray, sizeof(struct _Values));

        // Se recorre "array" y en cada posición se guarda, en "value" la cantidad de vértices que están coloreados
        // con el color "index + 1" según CountColor y en index la posición de CountColor para ese color.
        for(index = 0; index < lengthArray; index ++){
            array[index] = calloc(1, sizeof(struct _Values));
            array[index]->value = W->CountColor[index + 1]->length;
            array[index]->index = index + 1;
        }

        // Se ordena "array" de menor a mayor.
        qsort(array, lengthArray, sizeof(struct _Values), MinorToMayor);


        u32 vindex = 0; //  Se utiliza para marcar la última posición de "mutableOrder" modificada a medida que
                        // se va recorriendo "indexVertex" de " CountColor".

        // Se carga en "mutableOrder" los índices de los vértices en el arreglo de vértices de orden fijo.
        for(index = 0; index < lengthArray; index ++){
            position = array[index]->index;
            stop = W->CountColor[position]->length;
            for (jindex = 0; jindex < stop; jindex ++){
                W->mutableOrder[vindex] = W->CountColor[position]->indexVertex[jindex];
                vindex = vindex + 1;
            }
        }

        // Se libera memoria.
        for(u32 i = 0; i < lengthArray; i++){
            free(array[i]);
        }
        free(array);
    } else if (x == 3){
        u32 index; // variable para recorrer el arreglo "array"
        u32 jindex; // variable para recorrer el arreglo "indexVertex" de CountColor.
        u32 position;// posicion en countColor.
        u32 stop; // Se usa como cota superior en el for que recorre CountColor.
        u32 lengthArray; // Largo de "array" que es el coloreo máximo del grafo.
        lengthArray = W->chromatic;
        Values *array;
        array = calloc(lengthArray, sizeof(struct _Values));

        // Se recorre "array" y en cada posición se guarda, en "value" la cantidad de vértices que están coloreados
        // con el color "index + 1" según CountColor y en index la posición de CountColor para ese color.
        for(index = 0; index < lengthArray; index ++){
            array[index] = calloc(1, sizeof(struct _Values));
            array[index]->value = W->CountColor[index + 1]->length;
            array[index]->index = index + 1;
        }

        // Se ordena "array" de mayor a menor.
        qsort(array, lengthArray, sizeof(struct _Values), MayorToMinor);

        u32 vindex = 0; //  Se utiliza para marcar la última posición de "mutableOrder" modificada a medida que
                        // se va recorriendo "indexVertex" de " CountColor".

        // Se carga en "mutableOrder" los índices de los vértices en el arreglo de vértices de orden fijo.
        for(index = 0; index < lengthArray; index ++){
            position = array[index]->index;
            stop = W->CountColor[position]->length;
            for (jindex = 0; jindex < stop; jindex ++){
                W->mutableOrder[vindex] = W->CountColor[position]->indexVertex[jindex];
                vindex = vindex + 1;
            }
        }
        // Se libera memoria.
        for(u32 i = 0; i < lengthArray; i++){
            free(array[i]);
        }
        free(array);
    } else if ( x > 3) {
        u32 seed = x;
        u32 lengthArrayColors;
        u32 i, firstPosition, secondPosition, index, NumColors, j, k, temp, vertexlastColorCount, ColorIndex;
        index = 0;
        temp = 0;
        ColorIndex = 0;
        vertexlastColorCount = 0;
        NumColors = W->chromatic;
        //printf("Numero colores %i\n", NumColors);
        u32 ColorArray[NumColors];
        srand(seed);
        for(i = 0; i < NumColors ; i++){ // Llenamos el arreglo con cantidad de colores
            ColorArray[i] = i + 1;
           // printf("%i\n", i +1);
        }
        for(index = 0; index < NumColors; index ++){
            firstPosition = rand() % NumColors; // se elige un random
            secondPosition = rand() % NumColors; // se elige un random
            //printf("Primera posicion %i\n", firstPosition);
            //printf("segunda posicion %i\n", secondPosition);     
            temp = ColorArray[firstPosition];
            ColorArray[firstPosition] = ColorArray[secondPosition];
            ColorArray[secondPosition] = temp;
        }
        /*printf("Color 1: %i\n", ColorArray[1]);
        printf("Color 2: %i\n", ColorArray[2]);
        printf("Color 3: %i\n", ColorArray[3]);
        printf("Color 4: %i\n", ColorArray[4]);*/
        for (j= 0; j < NumColors ; j++){ // Por cada color
            lengthArrayColors = W->CountColor[ColorArray[j]]->length; // Cantidad de vertices del color
            ColorIndex = ColorArray[j];
            //printf("%i\n", ColorIndex);
            for(k = 0; k < lengthArrayColors; k++){ 
                W->mutableOrder[vertexlastColorCount] = W->CountColor[ColorIndex]->indexVertex[k];//Empezando por el color J, pongo todos los vertices
                vertexlastColorCount++;//posicion del ultimo vertice agregado en el arreglo
            }
        }
    }
    destroyCountColor(W);
}

// Se carga la estructura de CountColor.
void createCountColor(WinterIsHere W) {
    // index se usa para recorrer los arreglos.
    // color guarda el color de un vértice.
    // length es el largo de cada posición del arreglo "counter".
    // posColor se usa como indice en counter.
    // label es el grado de un vértice.
    u32 index, color, length, posColor, label ;
    u32 lengthVertex; // Cota superior para recorrer counter y el largo de CountColor.
    u32 counter[W->chromatic + 1]; // Arrelgo que cuenta cuantos vertices hay coloreados por cada color,
                                // cada posición determina un color, por eso se utiliza desde la posición 1.
    posColor = 0;

    lengthVertex = W->chromatic + 1;

    // Inicializa counter en 0.
    for (index = 1; index < lengthVertex; index ++) {
        counter[index] = 0;
    }    

    // Cargo counter utilizando como posición en counter, la variable color y voy sumando cuantos 
    // vértices hay coloreados para cada color.
    for (index = 0; index < NumeroDeVertices(W); index ++) {
        color = W->vertex[index]->color;
        counter[color] = counter[color] + 1;
    }


    // Pido memoria para roda la estructura de CountColor y para sus campos.
    W->CountColor = calloc(lengthVertex, sizeof(struct _VertexColor));
    for (index = 1; index < lengthVertex; index ++) {
        length = counter[index];
        W->CountColor[index] = calloc(1, sizeof(struct _VertexColor));
        W->CountColor[index]->indexVertex = calloc(length, sizeof(u32));
        W->CountColor[index]->length = length;

    }

    // Cargo el arreglo "indexVertex" en cada posición de CountColor, según 
    for (index = 0; index < NumeroDeVertices(W); index ++) {
        posColor = W->vertex[index]->color; // Para usar como índice según cada solor en "counter".
        label = W->vertex[index]->label; // saco la etiqueta de este vértice.

        length = counter[posColor]; // cuantos colores tengo en esta posición.
        W->CountColor[posColor]->indexVertex[length - 1] = label; // voy guardando las etiquetas de los vértices
        // para ese color y voy disminuyendo length para ir moviendome de posición en el arreglo.
        counter[posColor] = counter[posColor] - 1; // Voy disminuyendo la cantidad de vértices en cada posición 
                                                // a medida que ya las fui cargando en "indexVertex".

    }
}

// Funcíon para liberar memoria pedida por "createCountColor".
void destroyCountColor(WinterIsHere W) {
    u32 lengthVertex, index;
    lengthVertex = W->chromatic + 1;

    for (index = 1; index < lengthVertex; index ++) {
        free(W->CountColor[index]->indexVertex);
        free(W->CountColor[index]);

    }
    free(W->CountColor);
}

void AleatorizarVertices(WinterIsHere W,u32 x){ // 
    u32 seed = x;
    u32 lengthArray;
    u32 i, firstPosition, secondPosition, index;
    index = 0;
    lengthArray = NumeroDeVertices(W);
    srand(seed);
    for(i = 0; i< lengthArray; i++){ // Llenamos el arreglo con cantidad de vertices
        W->mutableOrder[i] = i;
    }

    for(index = 0; index < lengthArray; index ++){
        firstPosition = rand() % lengthArray; // se elige un random
        secondPosition = rand() % lengthArray; // se elige un random
        swap(W, firstPosition, secondPosition); // Se hace shuffle del arreglo
    }
}

void swap(WinterIsHere W, u32 first, u32 second){
    u32 temp;
    temp = 0;

    temp = W->mutableOrder[first];
    W->mutableOrder[first] = W->mutableOrder[second];
    W->mutableOrder[second] = temp;
}