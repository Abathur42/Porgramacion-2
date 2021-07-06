// 5170794-0 

#include "../include/pila.h"
#include "../include/utils.h"
#include <stdio.h>
#include <assert.h>


struct _rep_pila
{
    int* array;
    int tope;
    int cota;   
};

TPila crearPila(nat tamanio){
    
    TPila res = new _rep_pila ();
    res->tope = 0;
    res->array = new int [tamanio];
    res->cota = tamanio;
    return res;
    
};

TPila apilar(nat num, TPila p){
    
    if(!estaLlenaPila(p)){
        p->array [p->tope] = num;
        p->tope ++;
    }
    return p;
};

TPila desapilar(TPila p){
   
   assert(p->tope > 0);
   p->tope--;
   return p;
};

void liberarPila(TPila p){
    delete[] p->array;
    delete p;
};

bool estaVaciaPila(TPila p){
    
    return (p->tope == 0);
};

bool estaLlenaPila(TPila p){
    
    return (p->tope == p->cota);
};

nat cima(TPila p){

    assert(p->tope > 0);
    return p->array [p->tope - 1]; 
    
};



