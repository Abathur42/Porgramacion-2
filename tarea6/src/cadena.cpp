//5170794

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena
{
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena
{
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; };

TCadena crearCadena()
{
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
};

void liberarCadena(TCadena cad)
{
  nodoCadena *a_borrar;
  while (cad->inicio != NULL)
  {
    a_borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(a_borrar->dato);
    delete (a_borrar);
  }
  delete cad;
};

bool esVaciaCadena(TCadena cad)
{
  return ((cad->inicio == NULL) && (cad->final == NULL));
};

TLocalizador inicioCadena(TCadena cad)
{

  TLocalizador res;
  if (esVaciaCadena(cad))
  {
    res = NULL;
  }
  else
  {
    res = cad->inicio;
  }
  return res;

  // versión conociendo la implementación:
  // esVaciaCadena(cad) => cad->inicio == NUL
  //assert(!esVaciaCadena(cad) || cad->inicio == NULL);
  //return cad->inicio;
};

TLocalizador finalCadena(TCadena cad)
{
  if (esVaciaCadena(cad))
  {
    return NULL;
  }
  else
  {
    return cad->final;
  }
};

TInfo infoCadena(TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  TInfo aux;
  if (localizadorEnCadena(loc, cad))
  {
    aux = loc->dato;
  }

  return aux;
};

TLocalizador siguiente(TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  if (esFinalCadena(loc, cad))
  {
    return NULL;
  }
  else
  {
    return loc->siguiente;
  }
};

TLocalizador anterior(TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  if (esInicioCadena(loc, cad))
  {
    return NULL;
  }
  else
  {
    return loc->anterior;
  }
};

bool esFinalCadena(TLocalizador loc, TCadena cad)
{
  if (esVaciaCadena(cad))
  {
    return false;
  }
  else if (loc == cad->final)
  {
    return true;
  }
  else
  {
    return false;
  }
};

bool esInicioCadena(TLocalizador loc, TCadena cad)
{
  if (esVaciaCadena(cad))
  {
    return false;
  }
  else if (loc == cad->inicio)
  {
    return true;
  }
  else
  {
    return false;
  }
};

TCadena insertarAlFinal(TInfo i, TCadena cad)
{
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato = i;
  nuevo->siguiente = NULL;
  nuevo->anterior = NULL;
  if (esVaciaCadena(cad))
  {
    //assert(cad->inicio == NULL);
    cad->inicio = nuevo;
  }
  else
  {
    //assert(cad->inicio != NULL);
    nuevo->anterior = cad->final;
    cad->final->siguiente = nuevo;
  }
  cad->final = nuevo;
  return cad;
};

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad)
{
  //assert(localizadorEnCadena(loc, cad));
  TLocalizador nuevo = new nodoCadena;
  nuevo->dato = i;

  if (esVaciaCadena(cad))
  {
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    cad->inicio = nuevo;
    cad->final = nuevo;
  }
  else if (esInicioCadena(loc, cad))
  {
    loc->anterior = nuevo;
    nuevo->siguiente = loc;
    nuevo->anterior = NULL;
    cad->inicio = nuevo;
  }
  else
  {
    nuevo->anterior = loc->anterior;
    loc->anterior->siguiente = nuevo;
    loc->anterior = nuevo;
    nuevo->siguiente = loc;
  }

  return cad;
};

TCadena removerDeCadena(TLocalizador loc, TCadena cad)
{
  //assert(localizadorEnCadena(loc, cad));
  nodoCadena *a_borrar;
  a_borrar = loc;
  if (a_borrar == cad->inicio && a_borrar == cad->final)
  {
    cad->inicio = cad->final = NULL;
    liberarInfo(a_borrar->dato);
    delete (a_borrar);
  }
  else if (loc == cad->final) //SI estoy parado en el final
  {
    cad->final = loc->anterior;
    cad->final->siguiente = NULL;
    liberarInfo(a_borrar->dato);
    delete (a_borrar);
  }
  else if (loc == cad->inicio) //SI estoy parado en el inicio
  {
    cad->inicio = loc->siguiente;
    cad->inicio->anterior = NULL;
    liberarInfo(a_borrar->dato);
    delete (a_borrar);
  }
  else // SI estoy en el medio
  {
    loc->anterior->siguiente = loc->siguiente;
    loc->siguiente->anterior = loc->anterior;
    liberarInfo(a_borrar->dato);
    delete (a_borrar);
  }

  return cad;
};

void imprimirCadena(TCadena cad)
{
  TLocalizador loc;
  nat a;
  double b;
  loc = inicioCadena(cad);
  if (esVaciaCadena(cad))
  {
    printf("\n");
  }
  else
  {
    while (loc != cad->final)
    {
      a = natInfo(loc->dato);
      b = realInfo(loc->dato);
      printf("(%d,%.2f)", a, b);
      loc = loc->siguiente;
    }
    a = natInfo(loc->dato);
    b = realInfo(loc->dato);
    printf("(%d,%.2f)", a, b);
    printf("\n");
  }
};

TLocalizador kesimo(nat k, TCadena cad)
{
  TLocalizador loc;
  loc = cad->inicio;
  unsigned int c = 0;
  if (cad->inicio == cad->final)
    if (k != 1)
    {
      loc = NULL;
    }
    else
    {
      loc = cad->inicio;
    }
  else
  {
    while (loc->siguiente != NULL)
    {
      c = c + 1;
      loc = loc->siguiente;
    }
    c = c + 1;
    if (k == 0 || k > c)
    {
      loc = NULL;
    }
    else
    {
      loc = cad->inicio;
      for (unsigned int x = 1; x < k; x++)
      {
        loc = loc->siguiente;
      }
    }
  }

  return loc;
};

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad)
{
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  if (esVaciaCadena(cad)) //si cad es vacia solo redirijo cad a sgm
  {
    cad->inicio = sgm->inicio;
    cad->final = sgm->final;
  }
  else//sino inserto normalmente
  {
    if (!esVaciaCadena(sgm))
    {
      sgm->inicio->anterior = loc;
      sgm->final->siguiente = loc->siguiente;
      if (esFinalCadena(loc, cad))
        cad->final = sgm->final;
      else
        loc->siguiente->anterior = sgm->final;

      loc->siguiente = sgm->inicio;
    }
  }
  sgm->inicio = sgm->final = NULL;
  delete sgm;
  return cad;
};

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
  assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
  TCadena res = crearCadena();
  if (!esVaciaCadena(cad))
  {
    TLocalizador loc = desde;
    while (loc != siguiente(hasta, cad))
    {
      // ERROR: compartiria memoria
      // TInfo info = loc->dato;
      TInfo info = copiaInfo((loc->dato));
      insertarAlFinal(info, res);
      loc = siguiente(loc, cad);
    }
  }
  return res;
};

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad)
{
  assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
  TLocalizador loc, loc1;

  if (esVaciaCadena(cad)) //Si la cadena es vacia no hago nada.
  {
    return cad;
  }
  else 
  {
    loc = desde;
    if (desde == hasta) // si desde = hasta solo remuevo ese.
    {
      cad = removerDeCadena(loc, cad);
    }
    else
    {
      while (loc != hasta) //sino sigo buscando e eliminando
      {
        loc1 = loc->siguiente;
        cad = removerDeCadena(loc, cad);
        loc = loc1;
      }
      cad = removerDeCadena(loc, cad);
    }
  }

  return cad;
};

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  loc->dato = i;
  return cad;
};

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
  assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
  //Cargo el dato y enlazo
  TInfo aux;
  aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
};

bool localizadorEnCadena(TLocalizador loc, TCadena cad)
{
  TLocalizador cursor = inicioCadena(cad);
  while (esLocalizador(cursor) && (cursor != loc))
    cursor = siguiente(cursor, cad);
  return esLocalizador(cursor);
};

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad)
{
  bool precede;
  if (localizadorEnCadena(loc1, cad))
  //Si es localizador tengo que ir avanzando hasta que llegue a loc2 y si salgo del while consulto si aux es localizador.
  {
    TLocalizador aux = loc1;
    while (esLocalizador(aux) && aux != loc2)
    {
      aux = aux->siguiente;
    }
    precede = esLocalizador(aux);
  }
  else
  {
    precede = false;
  }
  return precede;
};

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad)
{
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  TLocalizador res = loc;
  if (esVaciaCadena(cad))
    res = NULL;
  else
  {
    while (esLocalizador(res) && natInfo(infoCadena(res, cad)) != clave)
      res = siguiente(res, cad);
  }

  return res;
};

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad)
{
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  TLocalizador res = loc;
  if (esVaciaCadena(cad))
    res = NULL;
  else
  {
    while (esLocalizador(res) && natInfo(infoCadena(res, cad)) != clave)
      res = anterior(res, cad);
  }

  return res;
};

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad)
{
  assert(localizadorEnCadena(loc, cad));
  TLocalizador res = loc;
  while (esLocalizador(siguiente(loc, cad)))// mientras sea localizador, avanzo y pregunto.
  {
    loc = siguiente(loc, cad);
    if (natInfo(infoCadena(loc, cad)) < natInfo(infoCadena(res, cad)))
      res = loc;
  }

  return res;
};
