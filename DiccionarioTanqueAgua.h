#ifndef UNDAVDICCIONARIOTANQUEAGUA_H
#define UNDAVDICCIONARIOTANQUEAGUA_H

#include "TanqueAgua.h"
using UndavTanqueAgua::TanqueAgua;

namespace UndavDiccionarioTanqueAgua {
	typedef int Clave;
	typedef TanqueAgua* Valor;

	struct Item;
	struct DiccionarioTanqueAgua;

	DiccionarioTanqueAgua* Crear();
	Item* CrearItem(Clave clave, Valor valor);
	void destruirItem(Item* item);

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @clave no existe, agrega el @valor asociado a la @clave
	// Si @clave existe reemplaza el valor asociado a @clave por @valor
	void Agregar(DiccionarioTanqueAgua* diccionario, Clave clave,
		Valor valor); // ADD

	// Precondicion: @diccionario es una instancia valida
	// Postcondicion: Si @clave no existe, devuelve NULL. Caso contrario devuelve el
	// valor asociado a la @clave
	Valor Obtener(const DiccionarioTanqueAgua* diccionario, Clave clave); // FIND

	bool Existe(const DiccionarioTanqueAgua* diccionario, Clave clave);
	void Quitar(DiccionarioTanqueAgua* diccionario, Clave clave);
	bool Vacio(const DiccionarioTanqueAgua* diccionario);

	void Destruir(DiccionarioTanqueAgua* diccionario);
}

#endif