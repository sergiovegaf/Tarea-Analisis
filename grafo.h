#pragma once
#include "vertice.h"
#include "arista.h"
//#include <queue>
//#include <list>
//#include <stack>
//#include <map>
//#include <unordered_set>

using std::cout;
using std::endl;
using std::string;

class Grafo
{
  Vertice* primero;
  int tamano;

public:
  Grafo()
  {
    primero = NULL;
    tamano = 0;
  }

  bool EstaVacio()
  {
    return tamano == 0;
  }

  int ObtenerTamano()
  {
    return tamano;
  }

  Vertice* ObtenerVertice(string id)
  {
    Vertice* i = primero;

    while (i != NULL)
    {
      if (i->id == id)
        return i;

      i = i->sig;
    }

    return NULL;
  }

  void InsertaVertice(string id, string nombre, string tipo, string direccion)
  {
    if (ObtenerVertice(id) == NULL)
    {
      Vertice* nuevo = new Vertice(id, nombre, tipo, direccion);

      if (EstaVacio())
        primero = nuevo;
      else
      {
        Vertice *i = primero;

        while (i->sig != NULL)
          i = i->sig;

        i->sig = nuevo;
      }

      tamano++;
    }
    else
      cout << "Error: El centro medico con ID '" << id << "' ya existe." << endl;
  }

void InsertaArista(string idOri, string idDest, float distancia, string tipoRuta)
{
  Vertice* vori = ObtenerVertice(idOri);
  Vertice* vdest = ObtenerVertice(idDest);

  if (vori == NULL)
    cout << "Error: El vertice origen '" << idOri << "' no existe" << endl;

  if (vdest == NULL)
    cout << "Error: El vertice destino '" << idDest << "' no existe" << endl;

  if (vori != NULL && vdest != NULL)
  {
    Arista* nueva = new Arista(vdest, distancia, tipoRuta);

    if (vori->ari == NULL)
      vori->ari = nueva;
    else
    {
      Arista* j = vori->ari;

      while (j->sig != NULL)
        j = j->sig;

      j->sig = nueva;
    }
    cout << "Ruta insertada: " << idOri << " -> " << idDest << " (" << distancia << "km, " << tipoRuta << ")" << endl;
  }
}


void MostrarListaAdyacencia()
{
  Vertice* i = primero;
  cout << "--- Lista de rutas medicas ---" << endl;

  while (i != NULL)
  {
    Arista* j = i->ari;
    cout << "[" << i->id << " | " << i->nombre << " (" << i->tipo << ")]" << " -> ";

    while (j != NULL)
    {
      cout <<"[" << j->dest->id << " (" << j->distancia << "km, " << j->tipoRuta << ")]" << " -> ";
        j = j->sig;
    }

    cout << "NULL" << endl;
    i = i->sig;
  }
}

bool ExisteRuta(string idOri, string idDest)
  {
    Vertice* vori = ObtenerVertice(idOri);
    if (vori == NULL)
    {
      cout << "Vertice origen " << idOri << " no existe." << endl;
      return false;
    }
    Arista* j = vori->ari;
    while (j != NULL)
    {
      if (j->dest->id == idDest) // Compara el ID del destino
        return true;
      j = j->sig;
    }
    return false;
  }


void EliminarAristas(Vertice* vertice)
{
  if (vertice == NULL)
      return;
    Arista* i = vertice->ari;
    while (vertice->ari != NULL)
    {
      i = vertice->ari;
      vertice->ari = vertice->ari->sig;
      cout << "  -> Arista de salida " << vertice->id << "->" << i->dest->id << " eliminada" << endl;
      delete(i);
  }
}

void EliminarAristasDestino(string idDest)
{
  Vertice* i = primero;
    while (i != NULL)
    {
      if (i->ari == NULL) // Si el vértice no tiene aristas, continúa
      {
        i = i->sig;
        continue;
      }

      // Caso 1: La arista a borrar es la primera de la lista
      while (i->ari != NULL && i->ari->dest->id == idDest)
      {
        Arista* j = i->ari;
        i->ari = i->ari->sig;
        cout << "  -> Arista de entrada " << i->id << "->" << idDest << " eliminada" << endl;
        delete(j);
      }

      // Caso 2: La arista a borrar está en medio o al final
      Arista* x = i->ari;
      if (x != NULL) 
      {
        Arista* y = x->sig;
        while (y != NULL)
        {
          if (y->dest->id == idDest)
          {
            x->sig = y->sig;
            cout << "  -> Arista de entrada " << i->id << "->" << idDest << " eliminada" << endl;
            delete(y);
            y = x->sig; // Reevaluar el siguiente nodo
          }
          else
          {
            x = y;
            y = y->sig;
          }
        }
      }
      i = i->sig;
    }
  }

void EliminarVertice(string id)
{
    Vertice* victima = NULL;
    Vertice* anterior = NULL;

    if (primero == NULL) {
      cout << "El grafo esta vacio" << endl;
      return;
    }

    // Caso 1: Es el primer vértice
    if (primero->id == id)
    {
      victima = primero;
      primero = primero->sig;
    }
    // Caso 2: Es cualquier otro vértice
    else
    {
      anterior = primero;
      while(anterior->sig != NULL)
      {
        if (anterior->sig->id == id)
        {
          victima = anterior->sig;
          anterior->sig = victima->sig; // Lo desconectamos de la lista
          break;
        }
        anterior = anterior->sig;
      }
    }

    // Si encontramos el vértice
    if (victima != NULL)
    {
      cout << "Eliminando vertice [" << victima->id << " | " << victima->nombre << "]" << endl;
      EliminarAristas(victima); // Elimina sus rutas de salida
      EliminarAristasDestino(victima->id); // Elimina rutas que llegan a él
      delete(victima);
      tamano--;
      cout << "Vertice eliminado." << endl;
    }
    else
    {
      cout << "Error: El vertice con ID '" << id << "' no existe" << endl;
    }
  }

void EliminarArista(string idOri, string idDest)
  {
    Vertice* vori = ObtenerVertice(idOri);
    Vertice* vdest = ObtenerVertice(idDest);

    if (vori == NULL)
    {
      cout << "Error: El vertice origen '" << idOri << "' no existe" << endl;
      return;
    }
    if (vdest == NULL)
    {
      cout << "Error: El vertice destino '" << idDest << "' no existe" << endl;
      return;
    }

    if (vori->ari == NULL)
    {
      cout << "Error: El vertice '" << idOri << "' no tiene aristas." << endl;
      return;
    }

    // Caso 1: Es la primera arista de la lista
    if (vori->ari->dest == vdest)
    {
      Arista* i = vori->ari;
      vori->ari = vori->ari->sig;
      cout << "Arista " << idOri << "->" << idDest << " eliminada" << endl;
      delete(i);
    }
    // Caso 2: Es otra arista
    else
    {
      Arista* i = vori->ari;
      Arista* j = i->sig;
      bool encontrada = false;

      while (j != NULL)
      {
        if (j->dest == vdest)
        {
          i->sig = j->sig;
          cout << "Arista " << idOri << "->" << idDest << " eliminada" << endl;
          delete(j);
          encontrada = true;
          break;
        }
        i = j;
        j = j->sig;
      }
      
      if (!encontrada)
         cout << "Error: La arista " << idOri << "->" << idDest << " no existe." << endl;
    }
  }

void EliminarTodo()
{
  Vertice* i = primero;

  while (primero != NULL)
  {
    i = primero;
    primero = primero->sig;
    EliminarAristas(i);
    EliminarAristasDestino(i->nombre);
    cout << "Vertice " << i->nombre << " eliminado" << endl;
    delete(i);
    tamano--;
  }
}

void MostrarAdyacentes(string id)
  {
    Vertice* v = ObtenerVertice(id);
    if (v == NULL)
    {
      cout << "No se encontro el centro medico con ID: " << id << endl;
      return;
    }

    cout << "Centros conectados desde: [" << v->id << " | " << v->nombre << "]" << endl;
    Arista* j = v->ari;
    if (j == NULL)
    {
      cout << "  (No tiene rutas de salida)" << endl;
      return;
    }

    while (j != NULL)
    {
      cout << "  -> Destino: " << j->dest->id << " | " << j->dest->nombre << endl;
      cout << "     Detalles: " << j->distancia << "km, " << "Ruta " << j->tipoRuta << endl;
      j = j->sig;
    }
  }

 
};
