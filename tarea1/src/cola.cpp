// 5170794-0

#include "../include/cola.h"
#include "../include/lista.h"
#include "../include/utils.h"
#include <stdio.h>

struct _rep_cola
{
    TLista lst;
};


TCola crearCola(){
    TCola res = new _rep_cola;
    res->lst = crearLista();
    return res;
};

bool esVaciaCola(TCola cola){
    return (longitud((*cola).lst) == 0);
};


TCola encolar(info_t nuevo, TCola cola){
    cola->lst = insertar(longitud(cola->lst)+1,nuevo,cola->lst);
    //inserto en la longitud + 1 de la  cola
    return cola;
};

info_t frente(TCola cola){
    
    return infoLista(1,cola->lst);
};

TCola desencolar(TCola cola){
    cola->lst = remover(1,cola->lst);
    return cola;
};
