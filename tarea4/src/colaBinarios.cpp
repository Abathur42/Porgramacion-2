// 51707940

//#ifndef _COLA_BINARIOS_H
//#define _COLA_BINARIOS_H

#include "../include/binario.h"
#include "../include/utils.h"
#include "../include/colaBinarios.h"
#include <assert.h>
#include <stdio.h>
//typedef struct _rep_colaBinarios * TColaBinarios;
typedef struct nodo * Pepito; 

struct nodo
{
    TBinario binario;
    Pepito sig;

};

struct _rep_colaBinarios
{
    Pepito primero;
    Pepito ultimo;
};





TColaBinarios crearColaBinarios(){
    TColaBinarios c = new _rep_colaBinarios;
    c->primero = c->ultimo = NULL;
    return c;
    
    
};


TColaBinarios encolar(TBinario b, TColaBinarios c){
    nodo *nuevo = new nodo;
    nuevo->binario = b;
    nuevo->sig = NULL;
    if (c->primero == NULL){
        c->primero = nuevo;
    }
    else{
        c->ultimo->sig = nuevo;
    }
    c->ultimo = nuevo;
    return c;
};


TColaBinarios desencolar(TColaBinarios c){
    assert(c->primero != NULL);
    nodo *temp = c->primero;
    c->primero = c->primero->sig;
    if (c->primero == NULL){
        c->ultimo = NULL;
    }
    delete temp;
    return c;
};


void liberarColaBinarios(TColaBinarios c){
    nodo * a_Borrar;
    while (c->primero != NULL){
        a_Borrar = c->primero;
        c->primero = c->primero->sig;
        delete a_Borrar;
    }
    delete c;
};


bool estaVaciaColaBinarios(TColaBinarios c){
    return (c->primero == NULL);
};


TBinario frente(TColaBinarios c){
    assert(c->primero != NULL);
    return c->primero->binario;

};
