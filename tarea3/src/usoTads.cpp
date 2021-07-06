//5170794

#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static void nivelEnBinarioRec(TCadena res, int l, TBinario b){
  
  if (!esVacioBinario(b)){
    if ( l > 0){
      nivelEnBinarioRec(res,l-1,izquierdo(b));
      nivelEnBinarioRec(res,l-1,derecho(b));
    }
    else{
      res = insertarAlFinal(copiaInfo(raiz(b)),res);
    }
  }
};
//Cree una funcion auxiliar que haga toda la recursion y esta simplemente crea
//la cadena y luego la usa. Como puedo hacerlo sin usar esa funcion auxiliar?
TCadena nivelEnBinario(nat l, TBinario b){
   TCadena res = crearCadena();
   nivelEnBinarioRec(res,l-1,b);

   return res;

};


//Tuve que poner todo con enter en los pasos porque se me armo un pedo con las cosas.
//Quizas se puede hacer con menos condiciones pero con esto aseguro todo...
bool esCaminoRec(TLocalizador l, TCadena c, TBinario b){
   
  //PB
  if (esFinalCadena(l,c) && 
      b != NULL && 
      izquierdo(b) == NULL && 
      derecho(b) == NULL &&
      natInfo(raiz(b)) == natInfo(infoCadena(l,c))) {
      return true;
  }
  //PR1
  else if (!esFinalCadena(l,c) && derecho(b) != NULL &&
      natInfo(raiz(b)) < natInfo(infoCadena(siguiente(l,c),c)) && 
      natInfo(raiz(b)) == natInfo(infoCadena(l,c))){
        return esCaminoRec(siguiente(l,c),c,derecho(b));
      }
  //PR2
  else if (!esFinalCadena(l,c) && izquierdo(b) != NULL &&
      natInfo(raiz(b)) > natInfo(infoCadena(siguiente(l,c),c)) && 
      natInfo(raiz(b)) == natInfo(infoCadena(l,c))){
        return esCaminoRec(siguiente(l,c),c,izquierdo(b));
      }
  else{
    return false;
  }

};
//Uso la funcion de arriba para ayudarme a hacerlo recursivo.Necesitaba un TLocalizador para moverme
//en esCaminoRec.
bool esCamino(TCadena c, TBinario b){
  TLocalizador l = inicioCadena(c);
  bool esta = true;
  if (esVacioBinario(b) && esVaciaCadena(c)){
    esta = true;
  }else{
    esta = esCaminoRec(l,c,b);

  }
  return esta;
};

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
  if (esVaciaCadena(cad) || longitud(cad) == 1 || longitud(cad) == 0){
    bandera = false;
  }
  else 
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
  else if (longitud(c1) != longitud(c2))
  {
    return false;
  }
  else
  {
    while (l1 != NULL && l2 != NULL && !bandera)
    {
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
      {
        loc1 = inicioCadena(c1);
        loc2 = finalCadena(c1);
        res = copiarSegmento(loc1, loc2, c1);
        
        loc1 = inicioCadena(c2);
        loc2 = finalCadena(c2);
        res2 = copiarSegmento(loc1, loc2, c2);

        resultado = insertarSegmentoDespues(res2,finalCadena(res),res);

        
        
        
        //siguiente(finalCadena(res),res) = inicioCadena(res2);
        //anterior(inicioCadena(res2),res) = finalCadena(res); 

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
    nuevo = insertarAlFinal(copiaInfo(infoCadena(loc, cad)), nuevo);
    loc = siguiente(loc, cad);
  }
  return nuevo;
};
