//51707940


#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include "../include/colaDePrioridad.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*

  Los elementos de tipo 'TColaDePrioridad' son colas de prioridad cuyos
  elementos son de tipo 'nat' entre 1 y N, siendo N un parámetro pasado al
  crear la cola de prioridad.
  No hay elementos repetidos.
  La prioridad asociada al elemento es de tipo double y la determina un valor
  establecido al insertar el elemento. Ese valor puede ser modificado.
  Un elemento es prioritario ante otro si su valor asociado es menor.
  Si hay más de un elemento con mínimo valor asociado cualquiera de ellos es
  el prioritario.

*/
typedef struct _rep_colaDePrioridad *TColaDePrioridad;





struct _rep_colaDePrioridad{
  
  TInfo *dato;		//Arreglo de los elementos 
	nat tope;			//Tope de mi array de elementos
	nat max;			//valor maximo que puede tener un elemento
	nat *rango;			//Por las dudas

};


TColaDePrioridad crearCP(nat N){
  
  TColaDePrioridad cp = new _rep_colaDePrioridad;
	cp->dato = new TInfo[N + 1];
	cp->max = N;
	cp->tope = 0; //En 0 para que sea una referencia free

	//POR LAS DUDAS
	cp->rango = new nat[N + 2];
	for (nat i = 1; i <= N + 1; i++)
	{
		cp->rango[i] = INT_MAX;
	}
	
	return cp;

};


nat rangoCP(TColaDePrioridad cp){

  return cp->max;

};


static void filtradoAscendente(TColaDePrioridad &cp, nat pos){

  if ((pos / 2) != 0){//si tiene padre
	  if ((pos > 1) && realInfo(cp->dato[pos/2]) > realInfo(cp->dato[pos])){//si tiene padre y es mas grande que el hijo
		  TInfo swap = cp->dato[pos];										//Genero un pivote
			cp->dato[pos] = cp->dato[pos / 2];								//Hijo por padre
			cp->rango[natInfo(cp->dato[pos])] = pos;						//Actualizo la pos del padre
			cp->dato[pos / 2] = swap;										//padre por hijo
			cp->rango[natInfo(cp->dato[pos / 2])] = pos / 2;				//Actualizo la pos del hijo
		  filtradoAscendente(cp,pos/2);
		}
	}
};


static void filtradoDescendente(TInfo *datos, nat tope, nat pos, nat *&lugar){

  TInfo swap = datos[pos];
	nat hijo;
	bool bandera = true;
	while ( (2 * pos <= tope) && bandera)//mientras tengas hijo derecho
	{
		hijo = 2 * pos;
		if ((hijo + 1 <= tope) && (realInfo(datos[hijo]) > realInfo(datos[hijo + 1]))){//Si tengo hijo derecho y comparo sus prioridades
			hijo = hijo + 1;
		}
		if (realInfo(swap) > realInfo(datos[hijo])){
			lugar[natInfo(datos[pos])] = hijo;
			lugar[natInfo(datos[hijo])] = pos;
			datos[pos] = datos[hijo];
			datos[hijo]=swap;
			pos = hijo;
		}
		else{
			bandera = false;
		}
	}
	datos[pos] = swap;

};


TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp){
  
	if (!estaEnCP(elem,cp) && ((1 <= elem) && ( elem <= rangoCP(cp)))){
		TInfo info = crearInfo(elem, valor);
		cp->tope++;
		cp->dato[cp->tope] = info;
		cp->rango[elem] = cp->tope;
		filtradoAscendente(cp, cp->tope);
	}
	
	return cp;
	
};


bool estaVaciaCP(TColaDePrioridad cp){
  
  return (cp->tope == 0);
  
};


nat prioritario(TColaDePrioridad cp){
  
  return natInfo(cp->dato[1]);// o return cp->heap[1]

};

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  if (!estaVaciaCP(cp)){
		cp->rango[natInfo(cp->dato[1])] = INT_MAX;
		liberarInfo(cp->dato[1]);
		if (cp->tope != 1){
			cp->dato[1] = cp->dato[cp->tope];
			cp->rango[natInfo(cp->dato[1])] = 1;
			cp->dato[cp->tope] = NULL;
			cp->tope--;
			filtradoDescendente(cp->dato, cp->tope, 1, cp->rango);
		}
		else{
			cp->tope--;
		}
	}
	return cp;
	
};


bool estaEnCP(nat elem, TColaDePrioridad cp){

  return (cp->rango[elem] != INT_MAX);

};


double prioridad(nat elem, TColaDePrioridad cp){
  
  return (realInfo(cp->dato[cp->rango[elem]]));

};


TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp){

  if (estaEnCP(elem,cp)){	
		nat pos = cp->rango[elem];			//Tomo la posicion de elem
		TInfo aux = crearInfo(elem,valor);	//creo un nuevo info con el nuevo valor
		liberarInfo(cp->dato[pos]);			//Libero la memoria del elemento
		cp->dato[pos] = aux;				//agrego el elemento actualizado
		filtradoAscendente(cp,pos);			//Comienzo a filtrar
		filtradoDescendente(cp->dato,cp->tope,pos,cp->rango);
	}	
	
	return cp;

};


void liberarCP(TColaDePrioridad cp){

  while (cp->tope > 0){
		liberarInfo(cp->dato[cp->tope]);
		cp->tope--;
	}
	delete[] cp->dato;
	delete[] cp->rango;
	delete cp;
	cp = NULL;

};
