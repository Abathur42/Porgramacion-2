// 5170794

#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

bool pertenece(nat elem, TCadena cad)
{
  nat a;
  TLocalizador loc;
  bool bandera = false;
  if (!esVaciaCadena(cad))
  {
    loc = inicioCadena(cad);
    a = natInfo(infoCadena(loc, cad));
    while (esLocalizador(loc) && (a != elem))
    {
      a = natInfo(infoCadena(loc, cad));
      loc = siguiente(loc, cad);
    }
    if (a == elem)
    {
      bandera = true;
    }
  }
  return bandera;
};

nat longitud(TCadena cad)
{
  TLocalizador loc;
  nat largo = 0;
  if (esVaciaCadena(cad))//Si es vacia es 0
  {
    return largo;
  }
  else//Sino voy avanzando y sumando 1 a largo
  {
    loc = inicioCadena(cad);
    while (siguiente(loc, cad) != NULL)
    {
      largo = largo + 1;
      loc = siguiente(loc, cad);
    }
    //como siempre veo que es siguiente(loc,cad) != NULL al final solo tengo que sumarle 1
    largo = largo + 1;
  }
  return largo;
};

bool estaOrdenadaPorNaturales(TCadena cad)
{
  bool orden;
  TLocalizador loc;

  if (esVaciaCadena(cad) || longitud(cad) == 1)//Si tiene 0 o 1 elementos esta ordenada trivialmente
  {
    orden = true;
  }

  else
  {
    loc = inicioCadena(cad);

    
    while (siguiente(loc, cad) != NULL && natInfo(infoCadena(loc, cad)) <= natInfo(infoCadena(siguiente(loc, cad), cad)))
    {
      loc = siguiente(loc, cad);
    }
    orden = !esLocalizador(siguiente(loc, cad));
  }

  return orden;
}

bool hayNatsRepetidos(TCadena cad)
{

  bool bandera = false;
  if (esVaciaCadena(cad) || longitud(cad) == 1 || longitud(cad) == 0){ //Si es vacia o su longitud es 1 es falso.
    bandera = false;
  }
  else 
  //Sino voy buscando y comparando  son 2 while porque uno avanza para buscar si son iguales y el otro avanza en cad.
  {
    TLocalizador loc = inicioCadena(cad);
    TLocalizador loc2 = siguiente(loc, cad);
    nat dato = natInfo(infoCadena(loc, cad));
    while (loc2 != NULL && !bandera)
    {
      while (siguiente(loc,cad) != NULL  && dato != natInfo(infoCadena(siguiente(loc, cad), cad)))
      {
        loc = siguiente(loc, cad);
      }
      if (esLocalizador(siguiente(loc,cad)))
      {
        bandera = true;
      }
      else
      {
        loc = loc2;
        dato = natInfo(infoCadena(loc, cad));
        loc2 = siguiente(loc2, cad);
      }
      
    }
  }
  return bandera;
};

bool sonIgualesCadena(TCadena c1, TCadena c2)
{
  bool bandera = false;
  TLocalizador l1, l2;
  l1 = inicioCadena(c1);
  l2 = inicioCadena(c2);
  
  if (esVaciaCadena(c1) && esVaciaCadena(c2))
  {
    return true;
  }
  else if (longitud(c1) != longitud(c2))//Si sus longitudes son distintas ya se que no son iguales
  {
    return false;
  }
  else
  {
    while (l1 != NULL && l2 != NULL && !bandera)
    {
      //Se ve mejor en la comparación del if si defino todo por separado
      nat natc1 = natInfo(infoCadena(l1, c1));
      nat natc2 = natInfo(infoCadena(l2, c2));
      double realc1 = realInfo(infoCadena(l1, c1));
      double realc2 = realInfo(infoCadena(l2, c2));
      if (natc1 != natc2 || realc1 != realc2)
      {
        bandera = true;
      }
      l1 = siguiente(l1, c1);
      l2 = siguiente(l2, c2);
    }
    return !bandera;
  }
};

TCadena concatenar(TCadena c1, TCadena c2)
{
  TLocalizador loc1, loc2;
  TCadena res,res2,resultado;

  if (esVaciaCadena(c1) && esVaciaCadena(c2))
  {
    res = crearCadena();
    return res;
  }
  else
  {
    if (esVaciaCadena(c1)) //La primer cadena es vacia
    {
      loc1 = inicioCadena(c2);
      loc2 = finalCadena(c2);
      resultado = copiarSegmento(loc1, loc2, c2);
    }
    else
    {
      if (esVaciaCadena(c2)) //La segunda cadena es vacia
      {
        loc1 = inicioCadena(c1);
        loc2 = finalCadena(c1);
        resultado = copiarSegmento(loc1, loc2, c1);
      }
      else
      //Caso general: copio ambas cadenas por separado y las junto con un insertarSegmentoDespues.
      {
        loc1 = inicioCadena(c1);
        loc2 = finalCadena(c1);
        res = copiarSegmento(loc1, loc2, c1);
        
        loc1 = inicioCadena(c2);
        loc2 = finalCadena(c2);
        res2 = copiarSegmento(loc1, loc2, c2);

        resultado = insertarSegmentoDespues(res2,finalCadena(res),res);
      }
    }
  }
  return resultado;
};

TCadena ordenar(TCadena cad) 
{
  TLocalizador loc, loc2;

  if (esVaciaCadena(cad))
  {
    return cad;
  }
  else
  //Con loc me paro al principio y mientras el siguiente de loc no sea NULL busco el menor de la cadena con loc2
  //e intercambio ambos, luego avanzo loc.
  {
  
    loc = inicioCadena(cad);
    while (siguiente(loc, cad) != NULL)
    {
      loc2 = menorEnCadena(loc, cad);
      intercambiar(loc, loc2, cad);
      loc = siguiente(loc, cad);
    }
  }
  return cad;
};

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad)
{
  TLocalizador loc;
  loc = inicioCadena(cad);
  if (!esVaciaCadena(cad))
  {

    while (loc != NULL)
    {
      if (natInfo(infoCadena(loc, cad)) == original)
      {
        
        
        double real = realInfo(infoCadena(loc, cad));
        TInfo elemento = crearInfo(nuevo,real);
        //RECORDAR PRIMERO LIBERO LA INFO Y LUEGO HAGO EL CAMBIO.
        liberarInfo(infoCadena(loc,cad)); 
        cambiarEnCadena(elemento, loc, cad);
        
        
      }
      loc = siguiente(loc,cad);
    }
  }

  return cad;
};

TCadena subCadena(nat menor, nat mayor, TCadena cad)
{
  TCadena nuevo = crearCadena();
  TLocalizador loc = siguienteClave(menor, inicioCadena(cad), cad);
  while (loc != NULL && natInfo(infoCadena(loc, cad)) <= mayor)
  {
    //Tengo que usar copiarInfo porque sino me tira
    nuevo = insertarAlFinal(copiaInfo(infoCadena(loc, cad)), nuevo);
    loc = siguiente(loc, cad);
  }
  return nuevo;
};
