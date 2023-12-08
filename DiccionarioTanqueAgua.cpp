#include "DiccionarioTanqueAgua.h"
#include "Lista.h"
#include "TanqueAgua.h"
#include <iostream>

using namespace std;

namespace UndavDiccionarioTanqueAgua{
	struct Item {
		Clave id;
		Valor valor;
	};

	struct DiccionarioTanqueAgua {
		UndavLista::Lista *lista;
	};

	DiccionarioTanqueAgua *Crear() 
	{
		DiccionarioTanqueAgua *nuevoDiccionario = new DiccionarioTanqueAgua;
		nuevoDiccionario->lista = UndavLista::CrearListaVacia();
		return nuevoDiccionario;
	}

	Item *CrearItem(Clave clave, Valor valor) 
	{
		Item *item = new Item;
		item->id = clave;
		item->valor = valor;
		return item;
	}

	void destruirItem(Item *item) {
		UndavTanqueAgua::Destruir(item->valor);
		delete item;
	}

	void Agregar(DiccionarioTanqueAgua *diccionario, Clave clave, Valor valor) 
	{
		bool existe = false;
		UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(diccionario->lista);
		void *itemActual; 
		while (!UndavLista::IteradorLista::EsFin(iterador) && !existe) 
		{
			itemActual = UndavLista::IteradorLista::ObtenerItem(iterador);
			if (((Item *)itemActual)->id == clave) 
			{
				UndavLista::IteradorLista::Reemplazar(iterador, (Item *)valor);
				existe = true;
			}
			UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);

		if (!existe) 
		{
			Item *item = CrearItem(clave, valor);
			UndavLista::AgregarAlFinal(diccionario->lista, item);
		}
	} // ADD

	Valor Obtener(const DiccionarioTanqueAgua *diccionario, Clave clave) 
	{
		bool existe = false;
		UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(diccionario->lista);
		void *itemActual = NULL;

		while (!UndavLista::IteradorLista::EsFin(iterador) && !existe) 
		{
			itemActual = UndavLista::IteradorLista::ObtenerItem(iterador);
			if (((Item *)itemActual)->id == clave) 
			{
				existe = true;
			} 
			else UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);

		if (existe) return ((Item *)itemActual)->valor;
		else return NULL;
	} // FIND

	bool Existe(const DiccionarioTanqueAgua *diccionario, Clave clave) 
	{
		bool existe = false;
		UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(diccionario->lista);

		while (!UndavLista::IteradorLista::EsFin(iterador) && !existe) 
		{
			void *itemActual = UndavLista::IteradorLista::ObtenerItem(iterador);
			if (((Item *)itemActual)->id == clave) 
			{
				existe = true;
			} 
			else UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);

		return existe;
	}

	void Quitar(DiccionarioTanqueAgua *diccionario, Clave clave) {
		bool existe = false;
		UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(diccionario->lista);

		while (!UndavLista::IteradorLista::EsFin(iterador) && !existe) 
		{
			void *itemActual = UndavLista::IteradorLista::ObtenerItem(iterador);
			if (((UndavDiccionarioTanqueAgua::Item *)itemActual)->id == clave) 
			{
				Quitar(diccionario->lista, iterador);
				existe = true;
			} 
			else UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);
	}

	bool Vacio(const DiccionarioTanqueAgua *diccionario) {
		return EstaVacia(diccionario->lista);
	}

	void Destruir(DiccionarioTanqueAgua *diccionario) {
		UndavLista::IteradorLista::Iterador *iterador = UndavLista::IteradorLista::Comienzo(diccionario->lista);
		Item *itemActual;

		while (!UndavLista::IteradorLista::EsFin(iterador)) 
		{
			itemActual = (Item *)UndavLista::IteradorLista::ObtenerItem(iterador);
			destruirItem(itemActual);
			UndavLista::IteradorLista::Siguiente(iterador);
		}
		UndavLista::IteradorLista::Destruir(iterador);
		UndavLista::Destruir(diccionario->lista);
		delete diccionario;
	}
}