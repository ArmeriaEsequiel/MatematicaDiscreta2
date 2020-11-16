#include "JonSnow.h"

//Funciones para extraer información de datos del grafo

u32 NumeroDeVertices(WinterIsHere W) {
	return(W->nVertex);
}

u32 NumeroDeLados(WinterIsHere W) {
	return(W->mEdge);
}

u32 NumeroVerticesDeColor(WinterIsHere W,u32 i) {
	return(W->CountColor[i]->length);
}

u32 NumeroDeColores(WinterIsHere W) {
	return(W->chromatic);
}

u32 IesimoVerticeEnElOrden(WinterIsHere W,u32 i) {
	u32 ivertex;
	ivertex = W->mutableOrder[i];
	return(W->vertex[ivertex]->label);
}