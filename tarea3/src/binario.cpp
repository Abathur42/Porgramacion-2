//51707940

#include "../include/binario.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/cadena.h"



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct _rep_binario 
{
    TInfo dato;
    TBinario izq;
    TBinario der;

};

typedef struct _rep_binario *TBinario;


TBinario crearBinario(){

    return NULL;
};


TBinario insertarEnBinario(TInfo i, TBinario b){
    
    if (esVacioBinario(b)){

        b = new _rep_binario;
        b->dato = i;
        b->der = b->izq = NULL;
    }    
    else if (natInfo(b->dato) < natInfo(i)){
        b->der = insertarEnBinario(i,b->der);
    }
    else if (natInfo(b->dato) > natInfo(i)){
        b->izq = insertarEnBinario(i,b->izq);
    }
    
    return b;
};

TInfo mayor(TBinario b){
    
    TInfo res;
    if (b->der == NULL){
        res = b->dato;
        
    }else{
        res = mayor(b->der);
    }
    return res;
};

TBinario removerMayor(TBinario b){
    
    if (b->der == NULL){
        TBinario aux = b->izq;
        b->izq = NULL;
        delete b;
        b = aux;
    }else {
        b->der = removerMayor(b->der);
    }

    return b;



};

TBinario removerDeBinario(nat elem, TBinario b){

    TBinario aux;
    if (!esVacioBinario(b)){
        if (natInfo(b->dato) == elem){
            //PB1
            if (b->izq == NULL){
                aux = b->der;
                b->der  = NULL;
                liberarInfo(b->dato);
                delete b;
                b = aux;
            }
            //PB2
            else if (b->der == NULL){
                aux = b->izq;
                b->izq = NULL;
                liberarInfo(b->dato);
                delete b;
                b = aux;
            }
            //PB3
            else{
                TInfo auxI = b->dato;
                b->dato = mayor(b->izq);
                liberarInfo(auxI);
                b->izq = removerMayor(b->izq);
            }
        }
        //PR1
        else if (elem < natInfo(b->dato)){
            b->izq = removerDeBinario(elem, b->izq);
        }
        //PR2
        else{
            b->der = removerDeBinario(elem,b->der);
        }
    }


    return b;

};

void liberarBinario(TBinario b){
    
    if (!esVacioBinario(b)){
        liberarBinario(b->izq);
        liberarBinario(b->der);
        liberarInfo(b->dato);
        delete b;
        b = NULL;
    }
};

bool esVacioBinario(TBinario b){

    return (b == NULL);
};

static int auxEsAvl(TBinario b){

    if (esVacioBinario(b)){
        return 0;
    }
    int der = auxEsAvl(b->der);
    if (der == -1) {
        return -1;
    }
    int izq = auxEsAvl(b->izq);
    if (izq == -1){
        return -1;
    }
    int balance = izq - der;
    if (balance > 1 || balance < -1){
        return -1;
    }
    if (der >= izq){
        return (1 + der);
    }
    else{
        return (1 + izq);
    }
};

// Cree una funcion auxiliar para que no tuviera que recorre dos veces cada nodo!!
//Asi no tengo problemas con los tiempos.
bool esAvl(TBinario b){

    bool cumple = true;
    if (!esVacioBinario(b)){
        cumple = (auxEsAvl(b) > 0);
    }
    return cumple;
}

TInfo raiz(TBinario b){
    
    return b->dato;
};

TBinario izquierdo(TBinario b){
    
    return b->izq;
};

TBinario derecho(TBinario b){
    
    return b->der;
};

TBinario buscarSubarbol(nat elem, TBinario b){
    
    TBinario sub;
    if (b == NULL){
        sub = crearBinario();
    }
    else{
        if (elem == natInfo(b->dato)){
            sub = b;
        }
        else if (natInfo(b->dato) < elem){
            sub =  buscarSubarbol(elem,b->der);  
        }else if (natInfo(b->dato) > elem){
            sub =  buscarSubarbol(elem,b->izq);
        }
    
    }
    return sub;
    
    
};
//C++ no tiene una funcion maximo implementada por defecto?
int maximo(int x,int y){
    
    int max=x;
    if (y>max) max=y;
    
    return max;
};

nat alturaBinario(TBinario b){
    
    if (esVacioBinario(b)){
        return 0;
    }else {
        return 1 + maximo(alturaBinario(b->der), alturaBinario(b->izq));
    }

};

nat cantidadBinario(TBinario b){
    
    if (esVacioBinario(b)){
        return 0;
    }else{
        return 1 + cantidadBinario(b->der) + cantidadBinario(b->izq);
    }

};
//funcion auxiliar creada porque no se me ocurria como meter el sum en la recursion correctamente.
//Asi que esta funcion solamente hace la recursion con los dato ya cargados.
static void sumaRec(TBinario b, nat &cont, double &suma){
    
    if (!esVacioBinario(b)){
        sumaRec(b->der,cont,suma);
        if (cont > 0 && realInfo(b->dato) > 0){
            suma = suma + realInfo(b->dato);
            cont = cont - 1;
        }
        sumaRec(b->izq,cont,suma);
    }
};


double sumaUltimosPositivos(nat i, TBinario b){
    
    double sum = 0;
    sumaRec(b,i,sum);
    return sum;

};

void linealizacionRec(TBinario b, TCadena &c){
    
    if(b != NULL){
        linealizacionRec(b->izq,c);
        c = insertarAlFinal(copiaInfo(b->dato),c);
        //use copiaInfo porque no debe compartir memoria.
        linealizacionRec(b->der,c);
    }

}
TCadena linealizacion(TBinario b){

// Tiene que ser recorrido EnOrden esto
    TCadena res = crearCadena();
    linealizacionRec(b,res);
    return res;

};
TBinario menores(double cota, TBinario b){
 // Creo el res al principio y lo voy eliminando a medida que no lo necesito.   
    TBinario res;
    if (b != NULL){
        res = new _rep_binario;
        res->izq = menores(cota,b->izq);
        res->der = menores(cota,b->der);
        bool cumple = (realInfo(b->dato) < cota);
        //PB1
        if (cumple){
            res->dato = copiaInfo(b->dato);
        }
        //PB2
        else if (res->izq == NULL && res->der == NULL && !cumple){
            delete res;
            res = NULL;
        }
        //PB3
        else if (res->izq == NULL && res->der != NULL && !cumple){
            TBinario aux = res->der;
            res->der = NULL;
            delete res;
            res = aux;
        }
        //PB4
        else if  (res->izq != NULL && res->der == NULL && !cumple){
            TBinario aux = res->izq;
            res->izq = NULL;
            delete res;
            res = aux;
        }
        //PB5
        else if  (res->izq != NULL && res->der != NULL && !cumple){
            res->dato = copiaInfo(mayor(res->izq));
            res->izq = removerMayor(res->izq);
        }
        else{
            delete res;
            res = NULL;
        }
    }
    else{
        res = NULL;
    }
    return res;    
};
//funcion auxiliar usada en imprimirBinario para hacerla más elegante.
static void imprimirRec(TBinario b, int cont) {
    
    if (b != NULL){
        imprimirRec(b->der,cont + 1);
        // for para imprimir los "-"
        for (int i = 1; i <= cont;i++){
            printf("-");
        }
        //formato que ellos piden
        printf("(%d,%.2f)",natInfo(b->dato),realInfo(b->dato));
        imprimirRec(b->izq, cont + 1);
    }else{
        printf("\n");   
    }
}

void imprimirBinario(TBinario b){
    
    nat cont = 0;
    imprimirRec(b, cont);
};