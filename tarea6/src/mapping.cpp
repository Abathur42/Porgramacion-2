//51707940


#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"
#include "../include/mapping.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/*

Los elementos de tipo 'TMapping' son mappings cuyos elementos son
asociaciones de 'nat' a 'double'.
Puede haber hasta M asociaciones, siendo M un parámetro pasado al crear
el 'TMapping'.

*/
typedef struct _rep_mapping *TMapping;


struct _rep_mapping{
	TCadena *mapping;
	int capacidad;
	int tope;
};


TMapping crearMap(nat M){

    TMapping map = new _rep_mapping;
	map->mapping = new TCadena[M];
	map->capacidad = M;
	map->tope = 0;
	
	for (nat i = 0; i < M; i++){
		map->mapping[i] = crearCadena();
	}
	
    return map;

};


static int funcionPos(nat clave, int tamanio){
	
	return ((clave > 0) ? (clave % tamanio) : (((-1)*clave) % tamanio));

};


TMapping asociarEnMap(nat clave, double valor, TMapping map){

    assert(!estaLlenoMap(map) && !existeAsociacionEnMap(clave,map));//Quizas remover luego
	TInfo info = crearInfo(clave,valor);
	int pos = funcionPos(clave,map->capacidad);
	map->mapping[pos] = insertarAlFinal(info,map->mapping[pos]);
	map->tope++;
	
    return map;

};


TMapping desasociarEnMap(nat clave, TMapping map){

    if (existeAsociacionEnMap(clave,map)){
		
        int pos = funcionPos(clave,map->capacidad);
		TLocalizador loc = inicioCadena(map->mapping[pos]);
		TLocalizador aBorrar = NULL;
		while (esLocalizador(loc)){
			if (natInfo(infoCadena(loc,map->mapping[pos])) == clave){
				aBorrar = loc;
				loc = siguiente(loc,map->mapping[pos]);
				map->mapping[pos] = removerDeCadena(aBorrar, map->mapping[pos]);
			}
			else{
				loc = siguiente(loc,map->mapping[pos]);
			}
		}
		map->tope--;
	}
	
    return map;

};


bool existeAsociacionEnMap(nat clave, TMapping map){

    bool existe = false;
	int pos = funcionPos(clave,map->capacidad);
	TLocalizador loc = inicioCadena(map->mapping[pos]);
	if (!esVaciaCadena(map->mapping[pos])){
		while (esLocalizador(loc) && natInfo(infoCadena(loc,map->mapping[pos])) != clave ){
			loc = siguiente(loc, map->mapping[pos]);
		}
		existe = esLocalizador(loc);
	}
	
	return existe;

};


double valorEnMap(nat clave, TMapping map){

    int pos = funcionPos(clave, map->capacidad);
	TLocalizador loc = inicioCadena(map->mapping[pos]);
	while (natInfo(infoCadena(loc, map->mapping[pos])) != clave){
		loc = siguiente(loc,map->mapping[pos]);
	}
	
    return realInfo(infoCadena(loc,map->mapping[pos]));

};


bool estaLlenoMap(TMapping map){

    return (map->capacidad == map->tope);

};


void liberarMap(TMapping map){

    for (int i = 0; i < map->capacidad; i++){
		liberarCadena(map->mapping[i]);
	}

	delete[] map->mapping;
	delete map;
	map = NULL;

};
