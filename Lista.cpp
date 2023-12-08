#include "Lista.h"
#include <iostream>

using namespace std;

namespace UndavLista {
	struct Nodo 
	{
		void *item;
		Nodo *siguiente;
	};

	struct Lista 
	{
		Nodo *primero;
		Nodo *ultimo;
		int cantidadItems;
	};

	struct IteradorLista::Iterador 
	{
		Nodo *nodoActual;
	};

	Lista *CrearListaVacia() 
	{
		Lista *nuevaLista = new Lista;
		nuevaLista->cantidadItems = 0;
		nuevaLista->primero = NULL;
		nuevaLista->ultimo = NULL;

		return nuevaLista;
	}

	Lista *CrearLista(void *items[], int cantidadItems) 
	{
		Lista *nuevaLista = new Lista;
		nuevaLista->cantidadItems = 0;
		nuevaLista->primero = NULL;
		nuevaLista->ultimo = NULL;
		for (int i = 0; i < cantidadItems; ++i) 
		{
			AgregarAlFinal(nuevaLista, items[i]);
		}
		return nuevaLista;
	}

	Nodo *CrearNodo(void *item, Nodo *siguiente) 
	{
		Nodo *nuevoNodo = new Nodo;
		nuevoNodo->item = item;
		nuevoNodo->siguiente = siguiente;

		return nuevoNodo;
	}

	Nodo *CrearUltimoNodo(void *item) 
	{
		return CrearNodo(item, NULL);
	}

	void DestruirNodo(Nodo *nodo) { delete nodo; }

	void AgregarAlComienzo(Lista *lista, void *item)
	{
		Nodo *nuevoPrimero = CrearNodo(item, lista->primero);
		if (EstaVacia(lista)) {
			lista->ultimo = nuevoPrimero;
		}
		lista->primero = nuevoPrimero;
		lista->cantidadItems++;
	}

	void AgregarAlFinal(Lista *lista, void *item)
	{
		Nodo *nuevoUltimo = CrearUltimoNodo(item);
		if (EstaVacia(lista)) 
		{
			lista->primero = nuevoUltimo;
		} else {
			lista->ultimo->siguiente = nuevoUltimo;
		}
		lista->ultimo = nuevoUltimo;
		lista->cantidadItems++;
	}

	void QuitarPrimero(Lista *lista) 
	{
		if (!EstaVacia(lista)) 
		{
			Nodo *nodoAEliminar = lista->primero;
			if (lista->primero->siguiente == NULL) 
			{
				lista->primero = NULL;
				lista->ultimo = NULL;
			} else 
				lista->primero = lista->primero->siguiente;
			DestruirNodo(nodoAEliminar);
			lista->cantidadItems--;
		}
	}

	void QuitarUltimo(Lista *lista) 
	{
		if (!EstaVacia(lista)) 
		{
			Nodo *nodoAEliminar = lista->ultimo;

			if (lista->primero->siguiente == NULL) 
			{
				lista->primero = NULL;
				lista->ultimo = NULL;
			} else 
			{
				Nodo *nuevoUltimoNodo = lista->primero;
				while (nuevoUltimoNodo->siguiente != lista->ultimo) 
				{
					nuevoUltimoNodo = nuevoUltimoNodo->siguiente;
				}
				lista->ultimo = nuevoUltimoNodo;
				lista->ultimo->siguiente = NULL;
			}
			DestruirNodo(nodoAEliminar);
			lista->cantidadItems--;
		}
	}

	void Vaciar(Lista *lista)
	{
		while (!EstaVacia(lista))
		{
			QuitarPrimero(lista);
		}
	}

	bool EstaVacia(const Lista *lista) 
	{
		return lista->primero == NULL;
	}

	int CantidadItems(const Lista *lista) 
	{
		return lista->cantidadItems;
	}

	namespace IteradorLista
	{
		Iterador *Comienzo(Lista *lista) 
		{
			Iterador *iterador = new Iterador;
			iterador->nodoActual = lista->primero;
			return iterador;
		}

		bool EsFin(const Iterador *iterador) 
		{
			return iterador->nodoActual == NULL;
		}

		void Siguiente(Iterador *iterador) 
		{
			if (iterador->nodoActual != NULL) 
			{
				iterador->nodoActual = iterador->nodoActual->siguiente;
			} else 
				iterador->nodoActual = NULL;
		}

		void *ObtenerItem(Iterador *iterador)
		{
			return iterador->nodoActual->item;
		}

		void Reemplazar(UndavLista::IteradorLista::Iterador *iterador, void *item) 
		{
			iterador->nodoActual->item = item;
		}

		void Destruir(UndavLista::IteradorLista::Iterador *iterador) 
		{
			delete iterador;
		}

		bool Existe(Lista *lista, void *item)
		{
			bool existe = false;
			UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(lista);
			while (!UndavLista::IteradorLista::EsFin(iterador) && !existe) 
			{
				void *itemEnLista = UndavLista::IteradorLista::ObtenerItem(iterador);
				if (itemEnLista == item) 
				{
					existe = true;
				}
				UndavLista::IteradorLista::Siguiente(iterador);
			}
			UndavLista::IteradorLista::Destruir(iterador);

			return existe;
		}
	}
	

	void Quitar(Lista *lista, IteradorLista::Iterador *iterador) 
	{
		Nodo *nodoAnterior = NULL;
		Nodo *iteradorLista = lista->primero;
		while (iteradorLista != NULL) 
		{
			void *itemEnLista = IteradorLista::ObtenerItem(iterador);
			if (iteradorLista->item == itemEnLista) 
			{
				if (nodoAnterior != NULL)
				{
					nodoAnterior->siguiente = iteradorLista->siguiente;
				} else 
					lista->primero = iteradorLista;
				UndavLista::DestruirNodo(iteradorLista);
				lista->cantidadItems--;
				return;
			}
			nodoAnterior = iteradorLista;
			iteradorLista = iteradorLista->siguiente;
		}
	}

	void Destruir(Lista *lista) 
	{
		Vaciar(lista);
		delete lista;
	}
}