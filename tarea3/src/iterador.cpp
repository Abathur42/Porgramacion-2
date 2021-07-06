//51707940

#include "../include/iterador.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  _nodo_Iter *TNodoIter;

struct _nodo_Iter
{
    nat elem;
    TNodoIter sig;
};

struct _rep_iterador
{
    TNodoIter inicio;
    TNodoIter actual;
    TNodoIter final;
    bool block;
};

//Mi iterador consiste en una lista donde tengo conocido el inicio y el final
//y tiene una variable booleana para saber si esta o no bloqueada.


TIterador crearIterador(){
    TIterador iter = new _rep_iterador;
    iter->inicio = iter->final = iter->actual = NULL;
    iter->block = false;
    return iter;
};



TIterador agregarAIterador(nat elem, TIterador iter){
    if (!(iter->block)){
        //creo el elemento
        TNodoIter nuevo = new _nodo_Iter;
        nuevo->elem = elem;
        nuevo->sig = NULL;
        //diferencio dependiendo si esta vacio o no
        if (iter->inicio == NULL){
            iter->inicio = iter->final  = nuevo;
            
        }
        else{
            iter->final->sig = nuevo;
            iter->final = nuevo;
        }
        iter->actual = NULL;
    }
    return iter;
};


TIterador reiniciarIterador(TIterador iter){
    //dirijo el actual al inicio y lo bloqueo.
    if (iter->inicio != NULL){
        iter->actual = iter->inicio;
    }
    iter->block = true;
    return iter;
};


TIterador avanzarIterador(TIterador iter){
    //Si esta definida avanzo
    if (estaDefinidaActual(iter)){
        iter->actual = iter->actual->sig;
    }
    //sino devuelvo NULL
    else{
        iter->actual = NULL;
    }
    return iter;
};


nat actualEnIterador(TIterador iter){
    
    return (iter->actual->elem);
};


bool estaDefinidaActual(TIterador iter){
    
    return (iter->actual != NULL);
};


void liberarIterador(TIterador iter){
    
    _nodo_Iter *a_borrar;
    while (iter->inicio != NULL){
        a_borrar = iter->inicio;
        iter->inicio = iter->inicio->sig;
        delete (a_borrar);
  }
  delete iter;

};