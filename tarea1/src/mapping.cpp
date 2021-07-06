// 5170794-0

#include "../include/mapping.h"
#include "../include/lista.h"
#include "../include/utils.h"
#include <stdio.h>
#include <assert.h>

struct _rep_mapping
{
     TLista lst;
};


TMapping crearMapping(){
    
    TMapping res = new _rep_mapping;
    res->lst = crearLista();
   
    return res;
};

TMapping asociar(nat clave, double valor, TMapping map){
    // Miro si el mapping no llego al tamaño MAX
    if (longitud(map->lst) < MAX){

        //SI entro y veo que la long es 0 entonces solo lo agrego
        if (longitud(map->lst) == 0){
            info_t aux;
            aux.natural = clave;
            aux.real = valor;
            map->lst = insertar(longitud(map->lst)+1,aux,map->lst);    
        }
        else
        {//SINO miro que la clave no este ya dentro del mapping, si esta no lo agrega
            nat natu = posNat(clave,map->lst);
            if ((natu == 0)){
                info_t aux;
                aux.natural = clave;
                aux.real = valor;
                map->lst = insertar(longitud(map->lst)+1,aux,map->lst);
            }
        }
    }
    return map;
    
        
    
};

bool esClave(nat clave, TMapping map){
    
        bool bandera = (posNat(clave,map->lst) == 0);
        if (bandera){
            return false;
        }
        else{
            return true;
        }
    
    
};

double valor(nat clave, TMapping map){
    
    assert(esClave(clave,map));
    return infoLista(posNat(clave,map->lst),map->lst).real;
    
       
    
};

TMapping desasociar(nat clave, TMapping map){
    map->lst = remover(posNat(clave,map->lst),map->lst);

    return map;
};