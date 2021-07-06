//51707940
#include "../include/info.h"
#include "../include/colCadenas.h"
#include "../include/utils.h"
#include "../include/cadena.h"
/*
 Un elemento de tipo 'TColCadenas' es una colección acotada de 'TCadena's.

  La cantidad de elementos que mantiene, M, se establece en el parámetro
  de 'crearColCadenas'.
  Cada cadena se identifica con una posición entre 0 y M - 1.
   
  Los elementos de tipo 'TCadena' son lista doblemente enlazada de elementos
  de tipo 'Tinfo', con cabezal con punteros al inicio y al final.

*/


struct _rep_colCadenas
{
    TCadena *hash;
    nat tamano;
    nat cantActual;
};

typedef struct  _rep_colCadenas *TColCadenas;



TColCadenas crearColCadenas(nat M){

   TColCadenas cad = new _rep_colCadenas;
   
   cad->tamano = M;
   cad->cantActual = 0; 
   cad->hash = new TCadena[M];
   for (nat i = 0; i< M; i++){
       cad->hash[i] = crearCadena();
       
       
   }
  
   return cad;

};


TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col){

	if (pos <= col->tamano){
		col->hash[pos] = insertarAntes(info, inicioCadena(col->hash[pos]),col->hash[pos]);
	}
    return col;
};


bool estaEnColCadenas(nat dato, nat pos, TColCadenas col){
	
	TLocalizador iter = inicioCadena(col->hash[pos]);
	while ((esLocalizador(iter)) && (natInfo(infoCadena(iter,col->hash[pos])) != dato)){
       iter = siguiente(iter,col->hash[pos]);
   }

   return esLocalizador(iter);
};


TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col){

    TLocalizador iter = inicioCadena(col->hash[pos]);
	while (natInfo(infoCadena(iter,col->hash[pos])) != dato){
       iter = siguiente(iter,col->hash[pos]);
   }

   return infoCadena(iter,col->hash[pos]);


};


TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col){

    TCadena cad = col->hash[pos];
    TLocalizador iter = inicioCadena(cad);
	while (natInfo(infoCadena(iter,col->hash[pos])) != dato){
       iter = siguiente(iter,cad);
   }
   
   cad = removerDeCadena(iter,cad);

    return col;

};


void liberarColCadenas(TColCadenas col){
    
    for(nat i = 0; i < col->tamano; i++){
        liberarCadena(col->hash[i]);
    }
    delete[] col->hash;
    delete col;

};
