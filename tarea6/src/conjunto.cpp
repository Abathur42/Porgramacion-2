//51707940
#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/conjunto.h"
#include "../include/avl.h"
#include "../include/info.h"
#include "../include/usoTads.h"

#include <stdio.h>
/*

Los elementos de tipo 'TConjunto' son conjuntos de elementos de tipo 'nat'.

*/



struct _rep_conjunto
{
    nat cardinal;
    TAvl arbol;
    nat min;
    nat max;
    

};

TConjunto crearConjunto(){

    TConjunto res = new _rep_conjunto;
    res->cardinal = 0;
    res->arbol = crearAvl();
    res->min = res->max = 0;
    
    return res;

};


TConjunto singleton(nat elem){

    TConjunto conjunto = crearConjunto();
    conjunto->arbol = insertarEnAvl(elem, conjunto->arbol);
    conjunto->cardinal = 1;
    conjunto->max = conjunto->min = elem;

    return conjunto;

};


static TConjunto deIterAConjunto(TIterador iter){
    
    TConjunto res = crearConjunto();
	iter = reiniciarIterador(iter);
	res->min = actualEnIterador(iter);
    
	while (estaDefinidaActual(iter)){

		res->arbol = insertarEnAvl(actualEnIterador(iter),res->arbol);
		res->max = actualEnIterador(iter);
		iter = avanzarIterador(iter);
		res->cardinal = res->cardinal + 1;
     }
	
	return res;

};


TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
	//Creo los 2 iteradores los reinicio y guardo en una variables su cardinal.
	TConjunto res;
	TIterador iter1 = enOrdenAvl(c1->arbol);
    TIterador iter2 = enOrdenAvl(c2->arbol);
    
    iter1 = reiniciarIterador(iter1);
    iter2 = reiniciarIterador(iter2);
    
    nat card1 = c1->cardinal;
	nat card2 = c2->cardinal;
	
	if (card1 > 0 && card2 > 0){//los iteradores no estan vacios.
		
		res = deIterAConjunto(iter1);
		iter1 = reiniciarIterador(iter1);
		iter2 = reiniciarIterador(iter2);
		if (actualEnIterador(iter1) > actualEnIterador(iter2)){//Miro cual de los dos es mas chico y lo meto como min.
			res->min = actualEnIterador(iter2);
		}
		else{
			res->min = actualEnIterador(iter1);
		}
		
		
		while (estaDefinidaActual(iter2)){//tengo elementos en iter2.
			
			if (!estaDefinidaActual(iter1)){//Esta vacio iter1 o no tiene mas elementos.
				
				nat aux = actualEnIterador(iter2);
				res->arbol = insertarEnAvl(aux, res->arbol);
				res->max = aux;
				iter2 = avanzarIterador(iter2);
			
			}
			else{//iter1 tiene elementos.
				if (actualEnIterador(iter1) > actualEnIterador(iter2)){//el elemento de iter2 no esta en iter1.
					
					nat aux = actualEnIterador(iter2);
					res->arbol = insertarEnAvl(aux, res->arbol);
					res->max = aux;
					iter2 = avanzarIterador(iter2);
				}
				else if (actualEnIterador(iter1) <= actualEnIterador(iter2)){//avanzo en iter1 buscando un proximo candidato.
					
					iter1 = avanzarIterador(iter1);
				}
			}
		}
		res->cardinal = cantidadEnAvl(res->arbol);//Actualizo la cardinalidad del resultado.
	}
	else if (card2 > 0){//Vacio iter1.
		
		res = deIterAConjunto(iter2);
		
	}
	else if (card1 > 0){//Vacio iter2.
		res = deIterAConjunto(iter1);
		
	}
	else{ //Vacio ambos
	
		res = crearConjunto();
	}
	liberarIterador(iter1);
	liberarIterador(iter2);
	
	return res;

};

TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
	//Creo los 2 iteradores los reinicio y guardo en una variables su cardinal.
	TConjunto res = crearConjunto();
	TIterador iter1 = enOrdenAvl(c1->arbol);
    TIterador iter2 = enOrdenAvl(c2->arbol);
    
    iter1 = reiniciarIterador(iter1);
    iter2 = reiniciarIterador(iter2);
    
    nat card1 = c1->cardinal;
	nat card2 = c2->cardinal;
	
	
	if (card1 > 0 && card2 > 0){//los iteradores no estan vacios.
		res->min = actualEnIterador(iter1);//Como es la diferencia puedo meter el mas chico del primero.
		
		while (estaDefinidaActual(iter1) && estaDefinidaActual(iter2)){
			if (actualEnIterador(iter1) > actualEnIterador(iter2)){//Avanzo iter2
				
				iter2 = avanzarIterador(iter2);
			}
			else if (actualEnIterador(iter1) < actualEnIterador(iter2)){//Agrego iter1 y avanzo iter1
				
				res->arbol = insertarEnAvl(actualEnIterador(iter1),res->arbol);
				res->max = actualEnIterador(iter1);
				iter1 = avanzarIterador(iter1);
			}
			else{//Son iguales avanzo ambos
				
				iter1 = avanzarIterador(iter1);
				iter2 = avanzarIterador(iter2);
			}
		}
		while(estaDefinidaActual(iter1)){//Agrego los elementos que sobren de iter1
			
			res->arbol = insertarEnAvl(actualEnIterador(iter1),res->arbol);
			res->max = actualEnIterador(iter1);
			iter1 = avanzarIterador(iter1);
		}
		res->cardinal = cantidadEnAvl(res->arbol);//Actualizo la cardinalidad del resultado.
	}
	else if (card1 > 0){//Si iter2 es vacio entra de una aca y mete todo iter1.
		while(estaDefinidaActual(iter1)){
			
			res->arbol = insertarEnAvl(actualEnIterador(iter1),res->arbol);
			res->max = actualEnIterador(iter1);
			iter1 = avanzarIterador(iter1);
		}
		res->cardinal = cantidadEnAvl(res->arbol);//Actualizo la cardinalidad del resultado.
	}
	liberarIterador(iter1);
	liberarIterador(iter2);
	return res;
};

/*PRIMERA VERSION DE UNION Y DIFERENCIA. EL TIEMPO FUE 3.6 EN LA SIGUIENTE VERSION ES 3.4.
TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2){
	
    TIterador iter1 = iteradorDeConjunto(c1);
    TIterador iter2 = iteradorDeConjunto(c2);
    iter1 = reiniciarIterador(iter1);
    iter2 = reiniciarIterador(iter2);
    
    TIterador iterUnion = enAlguno(iter1,iter2);
    
    liberarIterador(iter1);
	liberarIterador(iter2);
    iterUnion = reiniciarIterador(iterUnion);
	TConjunto res;
	if (!estaDefinidaActual(iterUnion)){
		liberarIterador(iterUnion);
		res = crearConjunto();
		return res;
	}
    else{
		res = deIterAConjunto(iterUnion);
		liberarIterador(iterUnion);
		return res;
	}
    
    
};


TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2){
    
    
    TIterador iter1 = iteradorDeConjunto(c1);
    TIterador iter2 = iteradorDeConjunto(c2);
    iter1 = reiniciarIterador(iter1);
    iter2 = reiniciarIterador(iter2);
    
	
    
    TIterador iterDiff = soloEnA(iter1,iter2);
    liberarIterador(iter1);
	liberarIterador(iter2);
	iterDiff = reiniciarIterador(iterDiff);
	TConjunto res;
	if (!estaDefinidaActual(iterDiff)){
		liberarIterador(iterDiff);
		res = crearConjunto();
		return res;
	}
    else{
		res = deIterAConjunto(iterDiff);
		liberarIterador(iterDiff);
		return res;
	}

};

*/
bool perteneceAConjunto(nat elem, TConjunto c){

    bool esta = false;
    
    if (!estaVacioConjunto(c)){
		TAvl nodo = buscarEnAvl(elem,c->arbol);
		esta = (!estaVacioAvl(nodo) && elem == raizAvl(nodo));
		
	}
	
	return esta;
    
};


bool estaVacioConjunto(TConjunto c){

    return (c->cardinal == 0);

};


nat cardinalidad(TConjunto c){

    return c->cardinal;

};


nat minimo(TConjunto c){

    return c->min;

};


nat maximo(TConjunto c){

    return c->max;

};



TConjunto arregloAConjunto(ArregloNats elems, nat n){
	
	TConjunto res = crearConjunto();
    if (n>0){//por algun motivo poner elems != NULL no funciona
		res->arbol = arregloAAvl(elems, n);
		res->cardinal = n;
		
		res->min = elems[0];
		res->max = elems[n-1];
	}
    
    return res;
};


TIterador iteradorDeConjunto(TConjunto c){
    
    
    return enOrdenAvl(c->arbol);
    
};


void liberarConjunto(TConjunto c){

    liberarAvl(c->arbol);
    c->cardinal = c->max = c->min = 0;
    c->arbol = NULL;
    delete c;
	
};
