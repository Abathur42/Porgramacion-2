//51707940


#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include "../include/grafo.h"
#include "../include/mapping.h"



/*
Los elementos de tipo 'TGrafo' son grafos cuya cantidad de nodos se determina
  con un parámetro, N, y se identifican con naturales desde 1 hasta N.
  La cantidad de aristas está acotada por un parámetro, M, y tienen costo de
  tipo double.
  Los valores N y M son parámetros pasados al crear el grafo.
  El espacio ocupado para representar un grafo debe ser O(N + M).
*/



struct  _rep_grafo {
	TMapping grafo;//Aqui van los vertices (parejas) y su "distancia"
	TAvl *vecinos;//Arreglo de AVL donde guardo los vecinos
	nat maxVecino;
	nat cantVecino;//Quizas no lo tengo que usar
	
};


typedef struct _rep_grafo *TGrafo;
//Funciones auxiliares las primeras 2 son para poder usarlas en la funcion id.
static nat max(nat x, nat y){ 
  
  return ((x >= y) ? x : y);

};


static nat min(nat x, nat y){ 
  
  return ((x <= y) ? x : y);
  
};


static nat id(nat v1, nat v2, nat n){ 
  
  return ((min(v1, v2) - 1)*n + (max(v1, v2) - 1) );
  
};



TGrafo crearGrafo(nat N, nat M){

  TGrafo g = new _rep_grafo;
	g->vecinos = new TAvl[N + 1];
	
  for (nat i = 1; i < N + 1; i++){
		g->vecinos[i] = crearAvl();
	}
	g->grafo = crearMap(M);
	g->cantVecino = M;//Cantidad maxima de vecinos
	g->maxVecino = N;//Cantidad de vertices
	
	return g;

};


nat cantidadVertices(TGrafo g){

  return g->maxVecino;

};


bool hayMParejas(TGrafo g){
  
  return (estaLlenoMap(g->grafo));

};


TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g){

	if (!hayMParejas(g) && !sonVecinos(v1,v2,g)){ //No esta lleno, no son vecinos y es una distancia válida.
		nat v = id(v1,v2,g->maxVecino);// = id(v2,v1)
		g->grafo = asociarEnMap(v,d,g->grafo);//Agrego la asociacion v1 y v2 con su distancia
		g->vecinos[v1] = insertarEnAvl(v2, g->vecinos[v1]);//Agrego v2 como vecino de v1 
		g->vecinos[v2] = insertarEnAvl(v1, g->vecinos[v2]);//Agrego v1 como vecino de v2 
	}
	return g;

};


bool sonVecinos(nat v1, nat v2, TGrafo g){

  return (existeAsociacionEnMap(id(v1,v2,g->maxVecino),g->grafo));

};


double distancia(nat v1, nat v2, TGrafo g){

  return (valorEnMap(id(v1,v2,g->maxVecino),g->grafo));

};


TIterador vecinos(nat v, TGrafo g){

  return (enOrdenAvl(g->vecinos[v]));

};


void liberarGrafo(TGrafo g){

  nat n = g->maxVecino;
	
	//Primero liberamos la memoria donde se guarda la amistad
  for (nat i = 1; i < n + 1; i++){
		liberarAvl(g->vecinos[i]);
	}
  //Luego el resto
	liberarMap(g->grafo);
	delete[] g->vecinos;
	delete g;

};
