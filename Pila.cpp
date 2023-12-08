#include "Pila.h"
#include <iostream>

namespace UndavPila{
	struct NodoPila 
	{
		int item;
		NodoPila *siguiente;
	};

	struct Pila 
	{
		NodoPila *cima;
	};

	NodoPila *CrearNodo(int item, NodoPila *siguiente) 
	{
		NodoPila *nuevoNodo = new NodoPila;
		nuevoNodo->item = item;
		nuevoNodo->siguiente = siguiente;

		return nuevoNodo;
	}

	Pila *CrearPila() 
	{
		Pila *nuevaPila = new Pila;
		nuevaPila->cima = NULL;

		return nuevaPila;
	}

	void Apilar(Pila *pila, int item)
	{
		NodoPila *nuevaCima = CrearNodo(item, pila->cima);
		pila->cima = nuevaCima;
	}

	// O(1)
	int Desapilar(Pila *pila) 
	{
		int item = pila->cima->item;
		NodoPila *cimaAnterior = pila->cima;
		pila->cima = pila->cima->siguiente;
		delete cimaAnterior;
		return item;
	}

	bool EstaVacia(const Pila *pila) { return pila->cima == NULL; }

	void DestruirPila(Pila *pila)
	{
		while (!EstaVacia(pila)) Desapilar(pila);
		delete pila;
	}
}

