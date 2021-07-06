//5170794

#include "../include/usoTads.h"
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include "../include/iterador.h"
#include "../include/pila.h"
#include "../include/colaBinarios.h"
#include "../include/conjunto.h"

#include <limits.h> 


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//raizAvl() Hiciste un arreglo y luego de arregloAConjunto.

static nat maximoN(nat x,nat y){
    
    nat max=x;
    if (y>max) max=y;
    
    return max;
};

TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2){
	//Creo 2 iteradores los reinicio y guardo sus cardinales
	TConjunto res;
  
	TIterador iter1 = iteradorDeConjunto(c1);
	TIterador iter2 = iteradorDeConjunto(c2);

	iter1 = reiniciarIterador(iter1);
	iter2 = reiniciarIterador(iter2);
	
	nat card1 = cardinalidad(c1);
	nat card2 = cardinalidad(c2);
	
	nat cardM = maximoN(card1,card2);
	//El arreglo es para ir guardando las intersecciones
	nat *arreglo = new nat[cardM];
	
	cardM = 0;
	while (estaDefinidaActual(iter1) && estaDefinidaActual(iter2)){//iter1 y iter 2 no vacios
		if (actualEnIterador(iter1) == actualEnIterador(iter2)){//Son iguales lo agrego al arreglo y avanzo ambos
			arreglo[cardM] = actualEnIterador(iter1);
			iter1 = avanzarIterador(iter1);
			iter2 = avanzarIterador(iter2);
			cardM = cardM + 1;
		}
		else if (actualEnIterador(iter1) > actualEnIterador(iter2)){//iter1 > iter2 avanzo iter2
			iter2 = avanzarIterador(iter2);
        }
        
		else if (actualEnIterador(iter1) < actualEnIterador(iter2)){//iter2 > iter1 avanzo iter1
			iter1 = avanzarIterador(iter1);
		}
    }
	
	res = arregloAConjunto(arreglo,cardM);//Fuera del while al arreglo cargado lo cambio a un conjunto y pronto.
	liberarIterador(iter1);
	liberarIterador(iter2);
	delete[] arreglo;
	return res;
};


nat cantidadEnIterador(TIterador it){
  
  nat cantidad = 0;
  it = reiniciarIterador(it);
  
  while (estaDefinidaActual(it)){
    cantidad = cantidad + 1;
    it = avanzarIterador(it);
  }
  return cantidad;

};

TIterador enAlguno(TIterador a, TIterador b){

  TIterador res = crearIterador();
  //IMPORTANTE REINICIAR LOS ITERADORES
  a = reiniciarIterador(a);
  b = reiniciarIterador(b);
  
  
  /*
  Busco en los iteradores y voy agregando a res en funcion a si son 
  menores, mayores o iguales.
  */
  while (estaDefinidaActual(a) && estaDefinidaActual(b)){
    // elemento de a < elemento de b. Agrego el elemento de a en res y avanzo a.
    if (actualEnIterador(a) < actualEnIterador(b)){
      res = agregarAIterador(actualEnIterador(a), res);
      a = avanzarIterador(a);
    }
    // elemento de a > elemento de b. Agrego el elemento de b en res y avanzo b.
    else if (actualEnIterador(a) > actualEnIterador(b)){
      res = agregarAIterador(actualEnIterador(b), res);
      b = avanzarIterador(b);
    }
    // Son iguales. Agrego el elemento de a y avanzo ambos.
    else{
      res = agregarAIterador(actualEnIterador(a), res);
      a = avanzarIterador(a);
      b = avanzarIterador(b);
    }
  }
  /*
  Si se termina alguna de las listas antes avanzo en la que quedo agregando los elementos.
  */
  if (estaDefinidaActual(a)){
    while (estaDefinidaActual(a)){
      res = agregarAIterador(actualEnIterador(a),res);
      a = avanzarIterador(a);
    }
  }
  else if (estaDefinidaActual(b)){
    while (estaDefinidaActual(b)){
      res = agregarAIterador(actualEnIterador(b),res);
      b = avanzarIterador(b);
    }
  }
  return res;
};

TIterador soloEnA(TIterador a, TIterador b){

  TIterador res = crearIterador();
  //IMPORTANTE REINICIAR LOS ITERADORES
  a = reiniciarIterador(a);
  b = reiniciarIterador(b);
//Mientras estas definida ambas voy comparando elementos de "a" con los de "b".
  while (estaDefinidaActual(a) && estaDefinidaActual(b)){
    // Si son iguales no inserto nada y avanzo ambos.
    if (actualEnIterador(a) == actualEnIterador(b)){
      a = avanzarIterador(a);
      b = avanzarIterador(b);
    }
    //Si a < b se que no hay elementos más chico que "a" en "b" por lo tanto inserto y avanzo "a".
    else if (actualEnIterador(a) < actualEnIterador(b)){
      res = agregarAIterador(actualEnIterador(a), res);
      a = avanzarIterador(a);
    }
    //Si a > b 
    else if (actualEnIterador(a) > actualEnIterador(b)){
      //Avanzo b hasta que encuentre un b tal que b >= a.
      while (estaDefinidaActual(b) && actualEnIterador(a) > actualEnIterador(b)){
        b = avanzarIterador(b);
      }
      //Si encontre ese elemento y es más grande exclusivo se que el elemento de "a" no esta en "b".
      if (estaDefinidaActual(b) && actualEnIterador(a) < actualEnIterador(b)){
        res = agregarAIterador(actualEnIterador(a), res);
        a = avanzarIterador(a);
      }
      //Si es igual se que no lo tengo que agregar y avanzar.
      else if (estaDefinidaActual(b) && actualEnIterador(a) == actualEnIterador(b)){
        a = avanzarIterador(a);
        b = avanzarIterador(b);
      }
    }
  }
  //Si sali del while anterior y quedan elementos en "a" los agrego sin ningun criterio.
  while (estaDefinidaActual(a)){
    res = agregarAIterador(actualEnIterador(a), res);
    a = avanzarIterador(a);
  }
  return res;
};


/*
	Lo pense usando 2 estructuras auxiliares una cola de binarios y una pila de naturales.
	La forma de hacerlo es la siguiente, primero meto la raiz del arbol y un NULL en la cola
	a prepo porque se que es el primer nivel y el NULL lo uso para indicar que se termino el 
	nivel. Luego mientras la cola no este vacia, desencolo el frente de la cola y dependiendo
	que elemento sea hago cosas distinta:
	* Si es un elemento que no es hoja encolo el sub arbol izquierdo o derecho.
	* Si es NULL lo desencolo y encolo NULL.
	Voy con un contador para saber cuando parar el proceso no solo cuando la cola sea vacia
	tambien paro si hice el proceso alturaBinario(b) + cantidadBinario(b) veces.
 */
TIterador recorridaPorNiveles(TBinario b){
  
  TIterador res = crearIterador();
  if (b != NULL){
    TPila pila = crearPila(100);
    TColaBinarios cola = crearColaBinarios();
    cola = encolar(b,cola);
    cola = encolar(NULL,cola);
    int para = alturaBinario(b) + cantidadBinario(b);
    int contador = 2;
    while (!estaVaciaColaBinarios(cola) && para >= contador){
      b = frente(cola);
      contador = contador + 1;
      if (b != NULL){
        cola = desencolar(cola);
        pila = apilar(natInfo(raiz(b)), pila);
        if(derecho(b) != NULL){
          cola = encolar(derecho(b),cola);
        }
        if (izquierdo(b) != NULL){
          cola = encolar(izquierdo(b), cola);
        }
      }
      else{
        cola = desencolar(cola);
        pila = apilar(UINT_MAX, pila);
        cola = encolar(NULL,cola);
      }
    }
    
    while (!estaVaciaPila(pila)){
      nat natural = cima(pila);
      res = agregarAIterador(natural, res);
      pila = desapilar(pila);
    }
    liberarPila(pila);
	liberarColaBinarios(cola);
  }
  
  return res;
  
};







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
