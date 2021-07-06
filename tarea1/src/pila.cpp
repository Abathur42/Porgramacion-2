// 5170794-0 

#include "../include/pila.h"
#include "../include/lista.h"
#include "../include/utils.h"
#include <stdio.h>
#include <assert.h>


struct _rep_pila
{
    TLista lst;
};

TPila crearPila(){
    
    TPila res = new _rep_pila;
    (*res).lst = crearLista();
    // (*res).lst es lo mismo que res->lst
    return res;
};

bool esVaciaPila(TPila pila){
    
    return (longitud((*pila).lst) == 0);
};

TPila apilar(info_t nuevo, TPila pila){
    pila->lst = insertar(longitud(pila->lst)+1,nuevo,pila->lst);
    //inserto en la longitud + 1 de la pila
    return pila;
};

info_t cima(TPila pila){
   
    return infoLista(longitud(pila->lst), pila->lst);
};

TPila desapilar(TPila pila){
   pila->lst = remover(longitud(pila->lst), pila->lst);

   return pila;
};