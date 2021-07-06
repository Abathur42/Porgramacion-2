//51707940

#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/avl.h"
#include "../include/info.h"

#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


struct _rep_avl
{
    nat dato;
    TAvl izq;
    TAvl der;
    nat altura;
    nat cantidad;

};
//struct auxiliar para avlMin.
struct AvlUltimo
{
	TAvl avl;
	int ultimo;
};

typedef struct _rep_avl *TAvl;


TAvl crearAvl(){

    return NULL;

};


bool estaVacioAvl(TAvl avl){

    return (avl == NULL);

};


int altura(TAvl avl){
    if (avl == NULL){
        return 0;
    }
    else{
        return avl->altura;
    }
};

static int maximo(int x,int y){
    
    int max=x;
    if (y>max) max=y;
    
    return max;
};


TAvl nuevoNodito(nat dato){
    
    TAvl nodo = new _rep_avl;
    nodo->dato = dato;
    nodo->der = NULL;
    nodo->izq = NULL;
    nodo->altura = 1;

    return nodo;

};


TAvl rotarDer(TAvl avl){
    TAvl x = avl->izq;
    TAvl y = x->der;
    // Hago la rotacion
    x->der =  avl;
    avl->izq = y;

    // Modifico las alturas
    avl->altura = maximo(altura(avl->izq),altura(avl->der)) + 1;
    x->altura = maximo(altura(x->izq),altura(x->der)) + 1;

    return x;
}


TAvl rotarIzq(TAvl avl){
    TAvl y = avl->der;
    TAvl x = y->izq;
    // Hago la rotacion
    y->izq =  avl;
    avl->der = x;

    // Modifico las alturas
    avl->altura = maximo(altura(avl->izq),altura(avl->der)) + 1;
    y->altura = maximo(altura(y->izq),altura(y->der)) + 1;

    return y;
};


int balanceo(TAvl avl){
    if (avl == NULL){
        return 0;
    }
    else{
        return (altura(avl->izq) - altura(avl->der));
    }
};


TAvl insertarEnAvl(nat elem, TAvl avl){
    //Inserto de manera normal.
    if (avl == NULL){
        return nuevoNodito(elem);
    }

    if (elem < avl->dato){
        avl->izq = insertarEnAvl( elem, avl->izq);
    }

    else if (elem > avl->dato){
        avl->der = insertarEnAvl( elem, avl->der);
    }

    else{
        return avl;
    }
    //Actualizo alturas.
    avl->altura = 1 + maximo(altura(avl->izq), altura(avl->der));
    //Veo como esta el balance.
    int balance = balanceo(avl);
    /*
    Si esta desbalanceado hago las rotaciones que corresponden.
    Tengo 4 casos posible.
    */
    //Rotacion IZQ - IZQ
    if (balance > 1 && elem < avl->izq->dato){
        return rotarDer(avl);
    }
    //Rotacion DER - DER
    if (balance < -1 && elem > avl->der->dato){
        return rotarIzq(avl);
    }
    //Rotacion IZQ - DER
    if (balance > 1 && elem > avl->izq->dato){
        avl->izq = rotarIzq(avl->izq);
        return rotarDer(avl);
    }
    //Rotacion DER - IZQ
    if (balance < -1 && elem < avl->der->dato){
        avl->der = rotarDer(avl->der);
        return rotarIzq(avl);
    }

    return avl;

};


TAvl buscarEnAvl(nat elem, TAvl avl){
    TAvl sub;
    if (avl == NULL){
        sub = crearAvl();
    }
    else{
        if (elem == avl->dato){
            sub = avl;
        }
        else if (avl->dato < elem){
            sub =  buscarEnAvl(elem, avl->der);
        }else if (avl->dato > elem){
            sub =  buscarEnAvl(elem, avl->izq);
        }
    
    }
    return sub;

};


nat raizAvl(TAvl avl){

    return avl->dato;
};


TAvl izqAvl(TAvl avl){

    return avl->izq;
};


TAvl derAvl(TAvl avl){

    return avl->der;
};


nat cantidadEnAvl(TAvl avl){

    if (estaVacioAvl(avl)){
        return 0;
    }else {
        return 1 + cantidadEnAvl(avl->der) + cantidadEnAvl(avl->izq);
    }
};


nat alturaDeAvl(TAvl avl){

    if (estaVacioAvl(avl)){
        return 0;
    }else {
        return 1 + maximo(alturaDeAvl(avl->der), alturaDeAvl(avl->izq));
    }

};


void enOrdenAvlRec(TAvl avl, TIterador &iter){

    if (avl != NULL){
        enOrdenAvlRec(avl->izq,iter);
        iter = agregarAIterador(avl->dato, iter);
        enOrdenAvlRec(avl->der,iter);
    }
};


TIterador enOrdenAvl(TAvl avl){

    TIterador iter = crearIterador();
    enOrdenAvlRec(avl,iter);
    return iter;

};


static TAvl arregloAAvlRec(ArregloNats elems, int inicio, int  fin){
    //Misma idea que en binarios solo que ahora debo ajustar alturas y cantidad tambien.
    
    TAvl res;
    if (inicio > fin){
		res = NULL;
		}
    
    else{
		
		int medio = ((inicio + fin) / 2);
		res = new _rep_avl;
		res->dato = elems[medio];
		
		res->izq = arregloAAvlRec( elems, inicio, medio - 1);
		res->der = arregloAAvlRec( elems, medio + 1, fin);
		
		res->altura = 1 + maximo(alturaDeAvl(res->izq), alturaDeAvl(res->der));
		res->cantidad = 1 + cantidadEnAvl(res->der) + cantidadEnAvl(res->izq);
	}
	
	return res;
};


TAvl arregloAAvl(ArregloNats elems, nat n){
    
	return arregloAAvlRec(elems,0,n-1);
};


int cantidadNodosMinSegunAltura(nat altura){
    // Pasos bases
    if (altura == 0)
        return 1;
    else if (altura == 1)
        return 2;
  
    // Paso recursivo
    return (1 + cantidadNodosMinSegunAltura(altura - 1) + cantidadNodosMinSegunAltura(altura - 2));
};


static AvlUltimo auxAvlMin(int h, int &primero){
	AvlUltimo res;
	if (h <= 0)
	{
		res.avl = crearAvl();
		res.ultimo = primero - 1;
		
	}
	
	else
	{
		res.avl = new _rep_avl;
		res.avl->izq = auxAvlMin(h-1, primero).avl;
		nat nuevo = primero++;
		res.avl->altura = h;
		res.avl->dato = nuevo;
		AvlUltimo atr = auxAvlMin(h-2, primero);
		res.avl->der = atr.avl;
		res.avl->cantidad = 1 + cantidadEnAvl(res.avl->der) + cantidadEnAvl(res.avl->izq);
		if (res.avl->der == NULL)
		{
			res.ultimo = primero;
		}
		else
		{
			res.ultimo = atr.ultimo;
		}
	}
	return res;
}

TAvl avlMin(nat h) {
	int i = 1;
	AvlUltimo res = auxAvlMin(h,i);
	return res.avl;
}


void liberarAvl(TAvl avl){

    if(!estaVacioAvl(avl)){
        liberarAvl(avl->izq);
        liberarAvl(avl->der);

        delete avl;
     }

};



